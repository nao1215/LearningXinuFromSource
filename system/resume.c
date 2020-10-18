/**
 * @file resume.c
 * @brief プロセスを休止状態（サスペンド）からREADY状態に遷移させる。
 */
#include <xinu.h>

/**
 * @brief プロセスを休止状態（サスペンド）からREADY状態に遷移させる。
 * @details
 * Step1.割り込み禁止状態とし、割り込みマスクを保持する。<br>
 * Step2. PIDが正常値かどうかを確認する。<br>
 * Step3. レジューム対象プロセス情報を取得する。<br>
 * Step4. レジューム対象プロセス情報は、休止状態（サスペンド状態）かどうかを確認する。<br>
 * Step5. 現在の優先度を取得する。<br>
 * Step6. プロセスをREADY状態（CPUサービス対象）にする。<br>
 * Step7. 割り込み状態（割り込みマスク）を元に戻す。
 * @param[in] pid  休止状態からREADY状態に遷移させるプロセスのID
 * @return READY状態となったプロセスの優先度
 */
pri16 resume(pid32 pid)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process's table entry	*/
	pri16 prio;			   /* Priority to return		*/

	mask = disable();
	if (isbadpid(pid))
	{
		restore(mask);
		return (pri16)SYSERR;
	}
	prptr = &proctab[pid];
	if (prptr->prstate != PR_SUSP)
	{
		restore(mask);
		return (pri16)SYSERR;
	}
	prio = prptr->prprio; /* Record priority to return	*/
	ready(pid);
	restore(mask);
	return prio;
}
