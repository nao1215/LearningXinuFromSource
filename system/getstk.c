/**
 * @file getstk.c
 * @brief スタックメモリを割り当て、最上位のワードアドレスを返す。
 */
#include <xinu.h>

/**
 * @brief スタックメモリを割り当て、最上位のワードアドレスを返す。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 要求メモリサイズが0の場合は、割り込み状態を復元し、処理を終了する。<br>
 * Step3. 要求メモリサイズを8の倍数で丸める。<br>
 * Step4. フリーメモリリストの先頭から、要求メモリサイズ以上のメモリブロックを探索する。<br>
 * Step5. 要求メモリサイズを満たすメモリブロックがない場合は、割り込み状態を復元し、処理を終了する。<br>
 * Step6. 要求メモリサイズとメモリブロックサイズが一致する場合は、そのブロックをメモリフリーリストから除く<br>
 * Step7.要求メモリサイズよりメモリブロックサイズが大きい場合は、2つに分割し、<br>
 * 要求サイズと一致するブロックをスタックとし、残りをメモリフリーリストに残す。<br>
 * Step8. 割り込み状態を復元する。<br>
 * Step9. スタック（メモリブロックの最上位アドレス）を返す。
 * @param[in] nbytes 要求メモリサイズ（byte）
 * @return 成功時はスタック（メモリブロックの最上位アドレス）を返し、以下の場合はSYSERRを返す。<br>
 * 　・要求メモリサイズが0の場合<br>
 * 　・要求メモリサイズを確保できなかった場合
 */
char *getstk(uint32 nbytes)
{
	intmask mask;					/* Saved interrupt mask		*/
	struct memblk *prev, *curr;		/* Walk through memory list	*/
	struct memblk *fits, *fitsprev; /* Record block that fits	*/

	mask = disable();
	if (nbytes == 0)
	{
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32)roundmb(nbytes); /* Use mblock multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	fits = NULL;
	fitsprev = NULL; /* Just to avoid a compiler warning */

	while (curr != NULL)
	{ /* Scan entire list	*/
		if (curr->mlength >= nbytes)
		{				 /* Record block address	*/
			fits = curr; /*   when request fits	*/
			fitsprev = prev;
		}
		prev = curr;
		curr = curr->mnext;
	}

	if (fits == NULL)
	{ /* No block was found	*/
		restore(mask);
		return (char *)SYSERR;
	}
	if (nbytes == fits->mlength)
	{ /* Block is exact match	*/
		fitsprev->mnext = fits->mnext;
	}
	else
	{ /* Remove top section	*/
		fits->mlength -= nbytes;
		fits = (struct memblk *)((uint32)fits + fits->mlength);
	}
	memlist.mlength -= nbytes;
	restore(mask);
	return (char *)((uint32)fits + nbytes - sizeof(uint32));
}
