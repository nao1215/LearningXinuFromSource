/**
 * @file meminit.c
 * @brief BeagleBone Black向けのフリーメモリリストを初期化する。
 */
#include <xinu.h>

//! ヒープの開始アドレス
void *minheap;
//! ヒープの終了アドレス
void *maxheap;

/**
 * @brief BeagleBone Black向けのフリーメモリリストを初期化する。
 * @details
 * Step1. ヒープ開始アドレスとヒープ終了アドレスを設定する。<br>
 * Step2. メモリリストの先頭に、ヒープ開始から終了までのメモリブロックをセットする。
 * @note RAMサイズは512MB。
 */
void meminit(void)
{
	struct memblk *memptr; /* Memory block pointer	*/

	/* Initialize the minheap and maxheap variables */

	minheap = (void *)&end;
	maxheap = (void *)MAXADDR;

	/* Initialize the memory list as one big block */

	memlist.mnext = (struct memblk *)minheap;
	memptr = memlist.mnext;

	memptr->mnext = (struct memblk *)NULL;
	memlist.mlength = memptr->mlength =
		(uint32)maxheap - (uint32)minheap;
}
