/**
 * @file receive.c
 * @brief メッセージの受信を待ち、受信後にreceive()の呼び出し者にメッセージを返す。
 */
#include <xinu.h>

/**
 * @brief メッセージの受信を待ち、受信後にreceive()の呼び出し者にメッセージを返す。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 現在のプロセスが有効なメッセージを受信していない場合は受信待ち状態に移行し、<br>
 * 再スケジューリングを行う。<br>
 * Step3. プロセスが復帰後、メッセージを取得し、メッセージフラグをリセットする。<br>
 * Step4. 割り込み状態を復元する。
 * @return 取得したメッセージを返す。
 */
umsg32 receive(void)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process's table entry	*/
	umsg32 msg;			   /* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE)
	{
		prptr->prstate = PR_RECV;
		resched(); /* Block until message arrives	*/
	}
	msg = prptr->prmsg;		 /* Retrieve message		*/
	prptr->prhasmsg = FALSE; /* Reset message flag		*/
	restore(mask);
	return msg;
}
