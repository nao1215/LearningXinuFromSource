/**
 * @file semreset.c
 * @brief セマフォカウントをリセットし、待機中のプロセスを全て解放する。
 */
#include <xinu.h>

/**
 * @brief セマフォカウントをリセットし、待機中のプロセスを全て解放する。
 * @details Step1. 割り込みを禁止する。<br>
 * Step2. 以下のいずれかを満たす場合、割り込みを許可状態に復元し、処理を終了する。<br>
 * 　・引数で渡されたセマフォカウンタのリセット値が負の値の場合<br>
 * 　・引数で渡されたセマフォIDが不整値の場合<br>
 * 　・セマフォがFREE状態の場合<br>
 * Step3. 待機状態プロセスを全てREADY状態に移行するまで、再スケジューリングを遅延（Defer）させる。<br>
 * Step4. キュー操作API（getfirst()）でキューの先頭から順番にプロセスIDを取り出し、READY状態にする。<br>
 * Step5. 再スケジューリングの遅延を解除する。<br>
 * Step6. 割り込みを許可状態に戻す。<br>
 * @param[in] sem リセット対象のセマフォID
 * @param[in] count 新しいセマフォカウント（0以上の値）
 * @return セマフォカウンタがリセットできた場合はOK、以下の場合はSYSERRを返す。<br>
 * 　・引数で渡されたセマフォカウンタのリセット値が負の値の場合<br>
 * 　・引数で渡されたセマフォIDが不整値の場合<br>
 * 　・セマフォがFREE状態の場合
 */
syscall semreset(sid32 sem, int32 count)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct sentry *semptr; /* Ptr to semaphore table entry */
	qid16 semqueue;		   /* Semaphore's process queue ID	*/
	pid32 pid;			   /* ID of a waiting process	*/

	mask = disable();

	if (count < 0 || isbadsem(sem) || semtab[sem].sstate == S_FREE)
	{
		restore(mask);
		return SYSERR;
	}

	semptr = &semtab[sem];
	semqueue = semptr->squeue; /* Free any waiting processes */
	resched_cntl(DEFER_START);
	while ((pid = getfirst(semqueue)) != EMPTY)
		ready(pid);
	semptr->scount = count; /* Reset count as specified */
	resched_cntl(DEFER_STOP);
	restore(mask);
	return OK;
}
