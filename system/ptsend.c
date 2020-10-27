/**
 * @file ptsend.c
 * @brief メッセージをキューに追加する事によってポートへメッセージを送信する。
 */
#include <xinu.h>

/**
 * @brief メッセージをキューに追加する事によってポートへメッセージを送信する。
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
 * @param[in] msg 送信するメッセージ
 * @return メッセージ送信時はOKを返し、以下の場合はSYSERRを返す。<br>
 * 　・引数のポートIDが不正<br>
 *   ・セマフォ待機結果がエラー<br>
 * 　・ポートがALLOC状態以外<br>
 * 　・シーケンス番号が変化した場合
 * @note ポートのメッセージノードが枯渇した場合は、システム再起動が必要となる。
 */
syscall ptsend(int32 portid, umsg32 msg)
{
	intmask mask;			 /* Saved interrupt mask		*/
	struct ptentry *ptptr;	 /* Pointer to table entry	*/
	int32 seq;				 /* Local copy of sequence num.	*/
	struct ptnode *msgnode;	 /* Allocated message node 	*/
	struct ptnode *tailnode; /* Last node in port or NULL	*/

	mask = disable();
	if (isbadport(portid) ||
		(ptptr = &porttab[portid])->ptstate != PT_ALLOC)
	{
		restore(mask);
		return SYSERR;
	}

	/* Wait for space and verify port has not been reset */
	seq = ptptr->ptseq; /* Record original sequence	*/
	if (wait(ptptr->ptssem) == SYSERR || ptptr->ptstate != PT_ALLOC || ptptr->ptseq != seq)
	{
		restore(mask);
		return SYSERR;
	}
	if (ptfree == NULL)
	{
		panic("Port system ran out of message nodes");
	}

	/* Obtain node from free list by unlinking */

	msgnode = ptfree;		  /* Point to first free node	*/
	ptfree = msgnode->ptnext; /* Unlink from the free list	*/
	msgnode->ptnext = NULL;	  /* Set fields in the node	*/
	msgnode->ptmsg = msg;

	/* Link into queue for the specified port */

	tailnode = ptptr->pttail;
	if (tailnode == NULL)
	{ /* Queue for port was empty	*/
		ptptr->pttail = ptptr->pthead = msgnode;
	}
	else
	{ /* Insert new node at tail	*/
		tailnode->ptnext = msgnode;
		ptptr->pttail = msgnode;
	}
	signal(ptptr->ptrsem);
	restore(mask);
	return OK;
}
