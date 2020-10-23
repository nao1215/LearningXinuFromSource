/**
 * @file signal.c
 * @brief セマフォにシグナルをN回送り、N個の待機プロセスがある場合はそれらをREADY状態にする。
 */
#include <xinu.h>

/**
 * @brief セマフォにシグナルをN回送り、N個の待機プロセスがある場合はそれらをREADY状態にする。
 * @details 基本的な仕様は signal()と同様であり、差異は以下の通りである。<br>
 * 　・待機プロセスがある限り、シグナル送信を続ける事（送信上限は引数で指定された回数）<br>
 * 　・プロセスをREADY状態にする間は再スケジューリングを遅延（Defer）させる事
 * @param[in] sem シグナルを送信したいセマフォのID
 * @param[in] count シグナルを送信する数（最大）
 * @return シグナルを送信した場合はOK、「セマフォIDが不正な場合」や「引数で渡されたセマフォがFREE状態の場合」はSYSERRを返す。
 */
syscall signaln(sid32 sem, int32 count)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct sentry *semptr; /* Ptr to sempahore table entry */

	mask = disable();
	if (isbadsem(sem) || (count < 0))
	{
		restore(mask);
		return SYSERR;
	}
	semptr = &semtab[sem];
	if (semptr->sstate == S_FREE)
	{
		restore(mask);
		return SYSERR;
	}

	resched_cntl(DEFER_START);
	for (; count > 0; count--)
	{
		if ((semptr->scount++) < 0)
		{
			ready(dequeue(semptr->squeue));
		}
	}
	resched_cntl(DEFER_STOP);
	restore(mask);
	return OK;
}
