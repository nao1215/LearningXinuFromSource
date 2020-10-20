/**
 * @file chprio.c
 * @brief プロセスのスケジューリング優先度を変更する。
 */
#include <xinu.h>

/**
 * @brief プロセスのスケジューリング優先度を変更する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 不正なPIDの場合は割り込み許可状態に戻し、処理を終了する。
 * Step3. 引数で指定されたPIDからプロセス情報を取得し、新しい優先度に変更する。
 * Step4. 割り込み許可状態に戻し、処理を終了する。
 * @param[in] pid 優先度を変更したいプロセスのID
 * @param[in] newprio 新しい優先度
 * @return 優先度が変更できた場合は古い優先度、PIDが不正な場合はSYSERRを返す。
 */
pri16 chprio(pid32 pid, pri16 newprio)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process's table entry	*/
	pri16 oldprio;		   /* Priority to return		*/

	mask = disable();
	if (isbadpid(pid))
	{
		restore(mask);
		return (pri16)SYSERR;
	}
	prptr = &proctab[pid];
	oldprio = prptr->prprio;
	prptr->prprio = newprio;
	restore(mask);
	return oldprio;
}
