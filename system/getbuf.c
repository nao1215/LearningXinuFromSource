/**
 * @file getbuf.c
 * @brief 事前に確保されたバッファプールからバッファを取得する。
 */
#include <xinu.h>

/**
 * @brief 事前に確保されたバッファプールからバッファを取得する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. バッファプールIDが不正値の場合は、割り込み状態を復元し、処理を終了する。<br>
 * Step3. バッファプールに使用できるバッファが用意されるまで、待機する。<br>
 * Step4. 提供するバッファをプール（リスト）から切り離す。<br>
 * Step5. 提供するバッファの先頭4byteにバッファプールIDを記録し、4Byte分だけバッファのポインタを進める。<br>
 * Step6. 割り込み状態を復元する。
 * @param[in] poolid バッファテーブル中のバッファプールID
 * @return 成功時はバッファへのポインタ、バッファプールIDが不正の場合はSYSERRを返す。
 */
char *getbuf(bpid32 poolid)
{
	intmask mask;			/* Saved interrupt mask		*/
	struct bpentry *bpptr;	/* Pointer to entry in buftab	*/
	struct bpentry *bufptr; /* Pointer to a buffer		*/

	mask = disable();

	/* Check arguments */

	if ((poolid < 0 || poolid >= nbpools))
	{
		restore(mask);
		return (char *)SYSERR;
	}
	bpptr = &buftab[poolid];

	/* Wait for pool to have > 0 buffers and allocate a buffer */

	wait(bpptr->bpsem);
	bufptr = bpptr->bpnext;

	/* Unlink buffer from pool */

	bpptr->bpnext = bufptr->bpnext;

	/* Record pool ID in first four bytes of buffer	and skip */

	*(bpid32 *)bufptr = poolid;
	bufptr = (struct bpentry *)(sizeof(bpid32) + (char *)bufptr);
	restore(mask);
	return (char *)bufptr;
}
