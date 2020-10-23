/**
 * @file recvclr.c
 * @brief 受信メッセージをクリアし、待機している場合はメッセージを返す。
 */

#include <xinu.h>

/**
 * @brief 受信メッセージをクリアし、待機している場合はメッセージを返す。
 * @return 現在のプロセスが有効なメッセージを持っている場合はその内容を返し、<br>
 * 現在のプロセスが有効なメッセージを持っていない場合はOKを返す。
 * @note receive()と異なり、メッセージ受信を待ち続けず、即座にリターンする。
 */
umsg32 recvclr(void)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process's table entry	*/
	umsg32 msg;			   /* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == TRUE)
	{
		msg = prptr->prmsg;		 /* Retrieve message		*/
		prptr->prhasmsg = FALSE; /* Reset message flag		*/
	}
	else
	{
		msg = OK;
	}
	restore(mask);
	return msg;
}
