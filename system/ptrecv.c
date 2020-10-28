/**
 * @file ptrecv.c
 * @brief ポートからメッセージを受信する。受信前にメッセージが空の場合はブロッキングする。
 */
#include <xinu.h>

/**
 * @brief ポートからメッセージを受信する。受信前にメッセージが空の場合はブロッキングする。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. ポートIDが不正、もしくはポートがALLOC状態でなければ割り込み状態を復元し、処理を終了する。<br>
 * Step3.  送信側セマフォに空きが出るまで待機する。<br>
 * セマフォ待機後、以下の状態のいずれかであれば割り込み状態を復元し、処理を終了する。<br>
 * 　・セマフォ待機結果がエラー<br>
 * 　・ポートがALLOC状態以外<br>
 * 　・シーケンス番号が変化した場合<br>
 *  Step4. ポートフリーノードがNULL状態であれば（メッセージを使い果たした場合）、Panic状態とする。<br>
 *  Step5. ポートフリーノードからメッセージノード1個を切り出し、メッセージノードにメッセージを追加する。<br>
 *  Step6. メッセージノードをメッセージリストの末尾に追加する。<br>
 *  Step7. 受信セマフォにシグナルを送る。<br>
 *  Step8. 割り込み状態を復元する。
 * @param[in] portid 使用するポートのID
 * @return メッセージ送信時はOKを返し、以下の場合はSYSERRを返す。<br>
 * 　・引数のポートIDが不正<br>
 *   ・セマフォ待機結果がエラー<br>
 * 　・ポートがALLOC状態以外<br>
 * 　・シーケンス番号が変化した場合
 */
uint32 ptrecv(int32 portid)
{
	intmask mask;			/* Saved interrupt mask		*/
	struct ptentry *ptptr;	/* Pointer to table entry	*/
	int32 seq;				/* Local copy of sequence num.	*/
	umsg32 msg;				/* Message to return		*/
	struct ptnode *msgnode; /* First node on message list	*/

	mask = disable();
	if (isbadport(portid) ||
		(ptptr = &porttab[portid])->ptstate != PT_ALLOC)
	{
		restore(mask);
		return (uint32)SYSERR;
	}

	/* Wait for message and verify that the port is still allocated */

	seq = ptptr->ptseq; /* Record orignal sequence	*/
	if (wait(ptptr->ptrsem) == SYSERR || ptptr->ptstate != PT_ALLOC || ptptr->ptseq != seq)
	{
		restore(mask);
		return (uint32)SYSERR;
	}

	/* Dequeue first message that is waiting in the port */

	msgnode = ptptr->pthead;
	msg = msgnode->ptmsg;
	if (ptptr->pthead == ptptr->pttail) /* Delete last item	*/
		ptptr->pthead = ptptr->pttail = NULL;
	else
		ptptr->pthead = msgnode->ptnext;
	msgnode->ptnext = ptfree; /* Return to free list	*/
	ptfree = msgnode;
	signal(ptptr->ptssem);
	restore(mask);
	return msg;
}
