/**
 * @file ready.c
 * @brief プロセスをCPUサービスの対象にする。
 */

#include <xinu.h>

//! READYリストのインデックス
qid16 readylist;

/**
 * @brief プロセスをCPUサービスの対象にする。
 * @details
 * Step1. PIDが正常値かどうかを確認する。<br>
 * Step2. プロセス情報を取得し、ステータスをREADY状態に移行する。<br>
 * Step3. プロセスをREADYリストに挿入する。<br>
 * Step4. 再スケジューリングを行う。<br>
 * @param[in] pid READY状態に遷移させるプロセスのID
 * @return プロセスがREADY状態となった場合はOK、引数が不正なPIDの場合はSYSERRを返す。
 */
status ready(
	pid32 pid /* ID of process to make ready	*/
)
{
	register struct procent *prptr;

	if (isbadpid(pid))
	{
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio);
	resched();

	return OK;
}
