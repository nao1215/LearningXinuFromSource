/**
 * @file send.c
 * @brief プロセスにメッセージを送信し、受信側が待機状態の場合はREADY状態にする。
 */
#include <xinu.h>

/**
 * @brief プロセスにメッセージを送信し、受信側が待機状態の場合はREADY状態にする。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 引数で渡されたプロセスのIDが不正値の場合は、割り込みを許可状態に復元し、処理を終了する。<br>
 * Step3. 受信側プロセスが過去のメッセージを未処理の場合は、割り込みを許可状態に復元し、処理を終了する。<br>
 * Step4. メッセージを受信側プロセスに送信（セット）し、受信側プロセスのメッセージ所持フラグを有効化する。<br>
 * Step5. 受信側プロセスが受信待ち状態の場合はREADY状態とし、<br>
 * 受信待ちかタイムアウト待ちの場合はプロセスの休眠状態を解除してからREADY状態に変更する。<br>
 * Step6. 割り込みを許可状態に復元する。
 * @param[in] pid メッセージを受信するプロセスのID
 * @param[in] msg メッセージ内容（整数かポインタ）
 * @return メッセージを送信した場合はOK、受信側プロセスIDが不正値の場合や受信側プロセスが過去メッセージ未処理の場合はSYSERRを返す。
 */
syscall send(pid32 pid, umsg32 msg)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process's table entry	*/

	mask = disable();
	if (isbadpid(pid))
	{
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg)
	{
		restore(mask);
		return SYSERR;
	}
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE; /* Indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV)
	{
		ready(pid);
	}
	else if (prptr->prstate == PR_RECTIM)
	{
		unsleep(pid);
		ready(pid);
	}
	restore(mask); /* Restore interrupts */
	return OK;
}
