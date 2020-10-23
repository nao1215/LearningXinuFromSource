/**
 * @file semdelete.c
 * @brief セマフォテーブルエントリを解放し、セマフォを削除する。
 */
#include <xinu.h>

/**
 * @brief セマフォテーブルエントリを解放し、セマフォを削除する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. セマフォIDが不正の場合は割り込みを許可状態に復元し、処理を終了する。<br>
 * Step3. 削除したいセマフォの状態がFREEの場合は、割り込みを許可状態に復元し、処理を終了する。<br>
 * Step4. セマフォの状態をFREEにする。<br>
 * Step5. 待機状態プロセスを全てREADY状態に移行するまで、再スケジューリングを遅延（Defer）させる。<br>
 * Step6. キュー操作API（getfirst()）でキューの先頭から順番にプロセスIDを取り出し、READY状態にする。<br>
 * Step7. 再スケジューリングの遅延を解除する。<br>
 * Step8. 割り込みを許可状態に戻す。
 * @param[in] sem 削除したいセマフォのID
 * @return セマフォの削除を成功した時はOK、<br>
 * 「セマフォIDが不正の場合」や「セマフォ削除前にセマフォがFREE状態の場合」はSYSERRを返す。
 */
syscall semdelete(sid32 sem)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct sentry *semptr; /* Ptr to semaphore table entry	*/

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
	semptr->sstate = S_FREE;

	resched_cntl(DEFER_START);
	while (semptr->scount++ < 0)
	{ /* Free all waiting processes	*/
		ready(getfirst(semptr->squeue));
	}
	resched_cntl(DEFER_STOP);
	restore(mask);
	return OK;
}
