/**
 * @file freemem.c
 * @brief メモリブロックを解放し、ブロックを空きリストに戻す。
 */
#include <xinu.h>

/**
 * @brief メモリブロックを解放し、ブロックを空きリストに戻す。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 以下のいずれかの場合は、割り込み状態を復元し、処理を終了する。<br>
 * 	・メモリブロックのサイズが0の場合<br>
 * 	・メモリブロックのポインタがヒープ開始アドレスより小さい場合<br>
 * 	・メモリブロックのポインタがヒープ終了アドレスより大きい場合<br>
 * Step4. メモリブロックのサイズを8の倍数で丸める。<br>
 * Step5. フリーメモリリストから空きメモリブロックの位置を探す。<br>
 * Step6. 「一つ前のメモリブロック」と「解放対象メモリブロック」の結合を試みるため、<br>
 * 一つ前のメモリブロックの最終アドレスを算出する（このアドレスはTOPとして扱う）。<br>
 * Step7. 解放対象メモリブロックが前後のメモリブロックと重なっていた場合は、<br>
 * 割り込み状態を復元し、処理を終了する。<br>
 * Step8. フリーメモリリストの使用可能メモリサイズに対して、今回解放するメモリブロックのサイズを加算する。<br>
 * Step9. 解放対象のメモリブロックを一つ前のメモリブロックと結合するか、フリーメモリリストに追加する。<br>
 * Step10. 解放対象のメモリブロックが次のメモリブロックと隣接している場合は、結合する。<br>
 * Step11. 割り込み状態を復元する。
 * @param[in] blkaddr メモリブロックのポインタ
 * @param[in] nbytes メモリブロックのサイズ（Byte）
 * @return メモリ解放時はOKを返し、以下のいずれかの場合はSYSERRを返す。<br>
 * 	・メモリブロックのサイズが0の場合<br>
 * 	・メモリブロックのポインタがヒープ開始アドレスより小さい場合<br>
 * 	・メモリブロックのポインタがヒープ終了アドレスより大きい場合<br>
 *  ・解放対象メモリブロックが前後のメモリブロックと重なっていた場合<br>
 */
syscall freemem(char *blkaddr, uint32 nbytes)
{
	intmask mask; /* Saved interrupt mask		*/
	struct memblk *next, *prev, *block;
	uint32 top;

	mask = disable();
	if ((nbytes == 0) || ((uint32)blkaddr < (uint32)minheap) || ((uint32)blkaddr > (uint32)maxheap))
	{
		restore(mask);
		return SYSERR;
	}

	nbytes = (uint32)roundmb(nbytes); /* Use memblk multiples	*/
	block = (struct memblk *)blkaddr;

	prev = &memlist; /* Walk along free list	*/
	next = memlist.mnext;
	while ((next != NULL) && (next < block))
	{
		prev = next;
		next = next->mnext;
	}

	if (prev == &memlist)
	{ /* Compute top of previous block*/
		top = (uint32)NULL;
	}
	else
	{
		top = (uint32)prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != &memlist) && (uint32)block < top) || ((next != NULL) && (uint32)block + nbytes > (uint32)next))
	{
		restore(mask);
		return SYSERR;
	}

	memlist.mlength += nbytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (uint32)block)
	{ /* Coalesce with previous block	*/
		prev->mlength += nbytes;
		block = prev;
	}
	else
	{ /* Link into list as new node	*/
		block->mnext = next;
		block->mlength = nbytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((uint32)block + block->mlength) == (uint32)next)
	{
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}
	restore(mask);
	return OK;
}
