/**
 * @file resched.c
 * @brief プロセスを再スケジューリングする。
 */
#include <xinu.h>

//! 遅延リスケジューリングに関連する項目を集約した構造体
struct defer Defer;

/**
 * @brief 最優先の適切なプロセスにCPU実行権を渡す。
 * @details resched()は、割り込みが禁止された区間で使用される事を想定している。<br>
 * Step1. 再スケジューリングを遅延させられている場合、再スケジュールを試みた事を記録して終了する。<br>
 * Step2. カレント（古い）プロセスのプロセステーブルを取得する<br>
 * Step3. 「カレントプロセスが現在動作中」かつ「READYリスト先頭プロセスより高優先度」の場合は終了する。<br>
 * Step4. カレントプロセスの状態を実行中からREADY状態に遷移させ、READYリストに挿入する。<br>
 * Step5. カレントPIDをREADYリストの先頭プロセスとし、そのプロセスをREADY状態から実行状態に遷移させる。<br>
 * Step6. プリエンプション（実行中のタスクを一時的に中断する動作）のためのタイムスライスを設定する。<br>
 * Step7. 古いプロセスから新しいプロセスへコンテキストスイッチを行う。<br>
 * Step8. 古いプロセスはresume()後に、resched()を即座にリターンする。
 */
void resched(void)
{
	struct procent *ptold; /* Ptr to table entry for old process	*/
	struct procent *ptnew; /* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0)
	{
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR)
	{ /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist))
		{
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM; /* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
/**
 * @brief 再スケジューリングを延期させるか、もしくは許可させるかを制御する。
 * @param[in] defer DEFER_START（延期開始）か、DEFER_STOP（延期終了）を指定する。
 * @details resched_cntl()は、割り込みが禁止された区間で使用される事を想定している。<br>
 * 引数がDEFER_STARTの場合、以下を実行後にOKを返して終了する。<br>
 * 　・延期されたプロセス数が0の場合は、その数を1に変更<br>
 * 　・延期されたプロセス数が0の場合は、延期中の再スケジューリングは未実施に変更<br>
 * 引数がDEFER_STOPの場合、以下を実行する。<br>
 * 　・延期されたプロセス数が負の値の場合は、SYSERRを返す。<br>
 * 　・「延期されたプロセスが1の場合」かつ「延期中に再スケジューリング実施済み」の場合は再スケジューリングを実施し、OKを返す。
 * 引数が不正な値の場合は、SYSERRを返す。
 */
status resched_cntl(int32 defer)
{
	switch (defer)
	{

	case DEFER_START: /* Handle a deferral request */

		if (Defer.ndefers++ == 0)
		{
			Defer.attempt = FALSE;
		}
		return OK;

	case DEFER_STOP: /* Handle end of deferral */
		if (Defer.ndefers <= 0)
		{
			return SYSERR;
		}
		if ((--Defer.ndefers == 0) && Defer.attempt)
		{
			resched();
		}
		return OK;

	default:
		return SYSERR;
	}
}
