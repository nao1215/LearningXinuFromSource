/**
 * @file getmem.c
 * @brief ヒープ領域を割り当て、最下位のワードアドレスを返す。
 */
#include <xinu.h>

/**
 * @brief ヒープ領域を割り当て、最下位のワードアドレスを返す。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 要求されたメモリのByte数が0の場合は、割り込み状態を復元し、処理を終了する。<br>
 * Step3. 要求されたメモリのByte数を8の倍数で丸める。<br>
 * Step4. フリーメモリリスト先頭の次のブロックから順番に、最適なメモリブロック探索を始める。<br>
 * メモリブロック探索では、以下の3通りいずれかを行う。<br>
 * ・現在のメモリブロックがユーザの要求サイズと一致する場合、そのメモリブロックを返す。<br>
 * ・ユーザの要求よりメモリブロックサイズが大きい場合、必要なメモリブロックサイズ分だけを返す。<br>
 * ・ユーザの要求よりメモリブロックサイズが小さい場合、次のメモリブロックを探索対象とする。<br>
 * メモリブロック提供時は、フリーメモリリストを連結し直し、メモリブロック合計サイズから提供サイズ分を引く。<br>
 * また、割り込み状態を許可状態に復元する。
 * @param[in] nbytes 必要なメモリサイズ（Byte）
 * @return 成功時はユーザ要求サイズ分のメモリへのアドレスを返し、「要求されたメモリのByte数が0の場合」や<br>
 * 「メモリに空きがない場合」はSYSERRを返す。
 * @note フリーメモリブロックはリンクリストで保持され、各ブロックはアドレスの昇順で管理されている。
 */
char *getmem(uint32 nbytes)
{
	intmask mask; /* Saved interrupt mask		*/
	struct memblk *prev, *curr, *leftover;

	mask = disable();
	if (nbytes == 0)
	{
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32)roundmb(nbytes); /* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL)
	{ /* Search free list	*/

		if (curr->mlength == nbytes)
		{ /* Block is exact match	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;
			restore(mask);
			return (char *)(curr);
		}
		else if (curr->mlength > nbytes)
		{ /* Split big block	*/
			leftover = (struct memblk *)((uint32)curr +
										 nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;
			restore(mask);
			return (char *)(curr);
		}
		else
		{ /* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
