/**
 * @file signal.c
 * @brief セマフォにシグナルを送り、待機プロセスがある場合は解除する。
 */
#include <xinu.h>

/**
 * @brief セマフォにシグナルを送り、待機プロセスがある場合は解除する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 不正なセマフォIDの場合は、割り込みを許可状態に復元し、処理を終了する。<br>
 * Step3. 引数で渡されたセマフォがFREE状態の場合は、割り込みを許可状態に復元し、処理を終了する。<br>
 * Step4. セマフォ待ち状態のプロセスがある場合、キューの先頭にあるプロセスをREADY状態にする。<br>
 * Step5. 割り込みを許可状態に復元する。
 * @param[in] sem シグナルを送信したいセマフォのID
 * @return シグナルを送信した場合はOK、「セマフォIDが不正な場合」や「引数で渡されたセマフォがFREE状態の場合」はSYSERRを返す。
 */
syscall signal(sid32 sem)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct sentry *semptr; /* Ptr to sempahore table entry	*/

	mask = disable();
	if (isbadsem(sem))
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
	if ((semptr->scount++) < 0)
	{ /* Release a waiting process */
		ready(dequeue(semptr->squeue));
	}
	restore(mask);
	return OK;
}
