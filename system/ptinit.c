/**
 * @file ptinit.c
 * @brief ポートを用いたメッセージ送受信機能を初期化する。
 */
#include <xinu.h>

//! フリーメッセージノードのリスト
struct ptnode *ptfree;
//! ポートテーブルエントリ
struct ptentry porttab[NPORTS];
//! 次に試みるテーブルエントリ
int32 ptnextid;

/**
 * @brief 全てのポートを初期化する。
 * @details
 * Step1. 全てのポート中の最大メッセージ数分だけメモリを確保する。<br>
 * メモリが確保できなかった場合はpanic状態となり、再起動が必要となる。<br>
 * Step2. 全てのポートテーブルエントリをFREE状態として初期化する。<br>
 * Step3. フリーメッセージリストをリンクさせる。
 * @param[in] maxmsgs 全てのポート中の最大メッセージ数
 * @return 初期化成功時はOK、メモリ確保失敗時はpanic状態となって再起動が必須となる。
 */
syscall ptinit(int32 maxmsgs)
{
	int32 i;					/* Runs through the port table	*/
	struct ptnode *next, *curr; /* Used to build a free list	*/

	/* Allocate memory for all messages on all ports */

	ptfree = (struct ptnode *)getmem(maxmsgs * sizeof(struct ptnode));
	if (ptfree == (struct ptnode *)SYSERR)
	{
		panic("ptinit - insufficient memory");
	}

	/* Initialize all port table entries to free */

	for (i = 0; i < NPORTS; i++)
	{
		porttab[i].ptstate = PT_FREE;
		porttab[i].ptseq = 0;
	}
	ptnextid = 0;

	/* Create a free list of message nodes linked together */

	for (curr = next = ptfree; --maxmsgs > 0; curr = next)
	{
		curr->ptnext = ++next;
	}

	/* Set the pointer in the final node to NULL */

	curr->ptnext = NULL;
	return OK;
}
