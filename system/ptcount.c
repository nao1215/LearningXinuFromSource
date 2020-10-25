/**
 * @file ptcount.c
 * @brief ポートを用いたメッセージ送受信において、メッセージ数を数える。
 */
#include <xinu.h>

/**
 * @brief ポートを用いたメッセージ送受信において、メッセージ数を数える。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. ポートIDが不正値もしくはポートが未割り当ての場合は、割り込み状態を復元し、<br>
 * 処理を終了する。
 * Step3. 受信メッセージ数（受信用セマフォ数）を数える。<br>
 * Step4. 受信メッセージ数が0以上の場合は、送信メッセージ数（送信用セマフォ数）を数える。<br>
 * Step5. 送信メッセージが0以下の場合は、受信メッセージ数にその数（送信者がブロックされた数）を<br>
 * 加算する。<br>
 * Step6. 割り込み状態を復元する。
 * @param[in] portid ポートID
 * @return 成功時は現在ポートで待機中のメッセージ数を返し、ポートIDが不正値もしくは<br>
 * ポートが未割り当ての場合はSYSERRを返す。
 * @note 正の値Kは、ポートにK個のメッセージ（送信者がブロックされて送信待機中のメッセージ含む）が<br>
 * ある事を意味する。負の値Kはポートが空であり、K個のプロセスがメッセージ受信のために<br>
 * 大気中である事を意味する。
 */
int32 ptcount(int32 portid)
{
	intmask mask;		   /* Saved interrupt mask		*/
	int32 count;		   /* Count of messages available	*/
	int32 sndcnt;		   /* Count of sender semaphore	*/
	struct ptentry *ptptr; /* Pointer to port table entry	*/

	mask = disable();
	if (isbadport(portid) ||
		(ptptr = &porttab[portid])->ptstate != PT_ALLOC)
	{
		restore(mask);
		return SYSERR;
	}

	/* Get count of messages available */

	count = semcount(ptptr->ptrsem);

	/* If messages are waiting, check for blocked senders */

	if (count >= 0)
	{
		sndcnt = semcount(ptptr->ptssem);
		if (sndcnt < 0)
		{ /* -sndcnt senders blocked */
			count += -sndcnt;
		}
	}
	restore(mask);
	return count;
}
