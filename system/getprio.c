/**
 * @file getprio.c
 * @brief プロセスのスケジューリング優先度を取得する。
 */
#include <xinu.h>

/**
 * @brief プロセスのスケジューリング優先度を取得する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 不正なPIDの場合は割り込み許可状態に戻し、処理を終了する。<br>
 * Step3. 引数で指定されたPIDからプロセス情報を取得し、そこから優先度を取得する。<br>
 * Step4. 割り込み許可状態に戻し、処理を終了する。<br>
 * @param[in] pid 優先度を取得したいプロセスのID
 * @return 処理が成功した場合は引数で指定したPIDの優先度、PIDが不正な場合はSYSERRを返す。
 */
syscall getprio(pid32 pid)
{
	intmask mask; /* Saved interrupt mask		*/
	uint32 prio;  /* Priority to return		*/

	mask = disable();
	if (isbadpid(pid))
	{
		restore(mask);
		return SYSERR;
	}
	prio = proctab[pid].prprio;
	restore(mask);
	return prio;
}
