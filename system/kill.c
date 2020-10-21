/**
 * @file kill.c
 * @brief 指定のプロセスを終了させ、システムから終了させたプロセス情報を取り除く。
 */
#include <xinu.h>

/**
 * @brief 指定のプロセスを終了させ、システムから終了させたプロセス情報を取り除く。
 * @details Step1. 割り込み禁止状態に移行する。<br>
 * Step2. プロセスが以下の状態であれば、割り込み許可状態に復元してから処理を終了する。<br>
 * 　・引数のPIDが不正<br>
 * 　・引数のPIDがNULLプロセス<br>
 * 　・引数のPIDで指定されるプロセスがFREE状態<br>
 * Step3. 現在アクティブのプロセス数が1以下（NULLプロセスのみ動作中）の場合、<br>
 * 　　　 全ユーザプロセスが終了したため、システム終了メッセージを表示する。<br>
 * Step4. 親プロセスに終了させるプロセスのIDを通知する。<br>
 * Step5. XINU Shell用に確保したSTDIN(標準入力)／STDOUT(標準出力)／STDERR(標準エラー)用のディスクリプタを閉じる。<br>
 * Step6. 終了させるプロセスが使用していたスタックメモリを解放する。<br>
 * Step7. 終了させるプロセスの状態に応じて、以下の処理を行う。<br>
 * 　・実行中の場合、FREE状態に移行し、再スケジューリングを行う（二度と戻ってこない）。<br>
 * 　・SLEEP状態やタイムアウト／メッセージ到着待ちの場合、休眠キューから終了させるプロセスを取り除く。<br>
 * 　・WAIT状態の場合、終了させるプロセス分（1個分）だけセマフォカウンタを増やす。次に、READY状態用の処理を行う。<br>
 * 　・READY状態の場合、終了させるプロセスをキューから取り出し、終了させるプロセス状態のをFREE状態に遷移する。<br>
 * Step8. 割り込み許可状態に復元してから、OKを返す。
 * @param[in] pid 終了させたいプロセスのID
 * @return プロセスを終了させた場合はOKを返す。以下の場合はSYSERRを返す。<br>
 * ・引数のPIDが不正<br>
 * ・引数のPIDがNULLプロセスbr>
 * ・引数のPIDで指定されるプロセスがFREE状態
 */
syscall kill(pid32 pid)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process's table entry	*/
	int32 i;			   /* Index into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC) || ((prptr = &proctab[pid])->prstate) == PR_FREE)
	{
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1)
	{ /* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i = 0; i < 3; i++)
	{
		close(prptr->prdesc[i]);
	}
	freestk(prptr->prstkbase, prptr->prstklen);

	switch (prptr->prstate)
	{
	case PR_CURR:
		prptr->prstate = PR_FREE; /* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid); /* Remove from queue */
					  /* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
