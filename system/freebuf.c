/**
 * @file freebuf.c
 * @brief バッファプールから取得したバッファを解放する。
 */
#include <xinu.h>

/**
 * @brief バッファプールから取得したバッファを解放する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 解放対象バッファアドレスの4Byte前に埋め込んだバッファプールIDが不正値かどうかを確認し、<br>
 * 不正値であれば割り込み状態を復元し、処理を終了する。<br>
 * Step3. 解放対象バッファをバッファプールに戻す。<br>
 * Step4. セマフォにシグナルを送り、待機プロセスがいれば待機解除とする。<br>
 * Step5. 割り込み状態を復元する。
 * @param[in] bufaddr getbuf()で取得したバッファアドレス
 * @return バッファを解放した場合はOK、バッファプールIDが不正値の場合はSYSERRを返す。
 */
syscall freebuf(char *bufaddr)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct bpentry *bpptr; /* Pointer to entry in buftab	*/
	bpid32 poolid;		   /* ID of buffer's pool		*/

	mask = disable();

	/* Extract pool ID from integer prior to buffer address */

	bufaddr -= sizeof(bpid32);
	poolid = *(bpid32 *)bufaddr;
	if (poolid < 0 || poolid >= nbpools)
	{
		restore(mask);
		return SYSERR;
	}

	/* Get address of correct pool entry in table */

	bpptr = &buftab[poolid];

	/* Insert buffer into list and signal semaphore */

	((struct bpentry *)bufaddr)->bpnext = bpptr->bpnext;
	bpptr->bpnext = (struct bpentry *)bufaddr;
	signal(bpptr->bpsem);
	restore(mask);
	return OK;
}
