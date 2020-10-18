/**
 * @file suspend.c
 * @brief プロセスを一時停止し、休止状態（サスペンド）に遷移させる。
 */
#include <xinu.h>

/**
 * @brief プロセスを一時停止し、休止状態（サスペンド）に遷移させる。
 * @details
 * Step1.割り込み禁止状態とし、割り込みマスクを保持する。<br>
 * Step2. PIDが正常値か、NULLプロセスではないかを確認する。<br>
 *        NULLプロセスが休止状態になった場合、動かすプロセスがREADYリストから無くなる可能性がある。<br>
 * Step3. サスペンド対象プロセス情報を取得する。<br>
 * Step4. サスペンド可能なプロセスは、現在実行中かREADY状態のプロセスだけである。<br>
 *        READY状態の場合：READYリストからサスペンド対象プロセスを除外し、サスペンド状態とする。<br>
 *        実行中の場合：サスペンド状態とし、再スケジューリングを行う。<br>
 *        それ以外：割り込み状態（割り込みマスク）を元に戻し、エラー終了<br>
 * Step5. 現在の優先度を取得する。
 * Step6. 割り込み状態（割り込みマスク）を元に戻す。
 * @param[in] pid  休止状態に移行させるプロセスのID
 * @return 一時休止（サスペンド）されたプロセスの優先度
 */
syscall suspend(pid32 pid)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process's table entry	*/
	pri16 prio;			   /* Priority to return		*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC))
	{
		restore(mask);
		return SYSERR;
	}

	/* Only suspend a process that is current or ready */

	prptr = &proctab[pid];
	if ((prptr->prstate != PR_CURR) && (prptr->prstate != PR_READY))
	{
		restore(mask);
		return SYSERR;
	}
	if (prptr->prstate == PR_READY)
	{
		getitem(pid); /* Remove a ready process	*/
					  /*   from the ready list	*/
		prptr->prstate = PR_SUSP;
	}
	else
	{
		prptr->prstate = PR_SUSP; /* Mark the current process	*/
		resched();				  /*   suspended and resched.	*/
	}
	prio = prptr->prprio;
	restore(mask);
	return prio;
}
