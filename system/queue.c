/**
 * @file queue.c
 * @brief キュー操作API（キューの追加、キューの削除）を提供する。
 * @note プロセスキューテーブルは、リストとも呼ばれる。
 */
#include <xinu.h>

/**
 * プロセスキューテーブル（全てのプロセスがアクセス可能な変数）。<br>
 * NPROC-1より小さいインデックスは、プロセスIDに対応する。<br>
 * queuetab[NPROC]〜queuetab[NQENT]の範囲は、キューIDと呼ばれ、<br>
 * ・リスト先頭<br>
 * ・リスト末尾<br>
 * のポインタを保持するために使用される。<br>
 * @image html "queue_table.png"
 * @note 以下はテーブルイメージ図であるが、Doxygenドキュメント上ではコメント表記が崩れるため、<br>
 * note部分のスクショ画像も併記している。
 *          ------------------------------------------------------------------<br>
 *          |     KEY     |     PREV     |     NEXT     |↓１行がプロセスに対応する<br>
 *          ---------------------------------------------<br>
 * 0        |     XXX     |     XXXX     |     XXXX     |<br>
 *          ---------------------------------------------<br>
 * 1        |     XXX     |     XXXX     |     XXXX     |<br>
 *          ---------------------------------------------<br>
 * :        |                     :                     |<br>
 *          ---------------------------------------------<br>
 * NPROC-1  |     XXX     |     XXXX     |     XXXX     |↓ ここまでがプロセス情報
 *          --------------------------------------------------------------<br>
 * NPROC    |                     :                     |↑ここから下はリスト先頭／末尾の組み合わせ<br>
 *          ---------------------------------------------<br>
 * :        |                     :                     |<br>
 *          ---------------------------------------------<br>
 * :        |    MAXKEY    |      -      |     XXXX     |リストの先頭<br>
 *          ---------------------------------------------リストの末尾<br>
 * :        |    MINKEY    |    XXXX     |      -       |<br>
 *          ---------------------------------------------<br>
 * :        |                     :                     |<br>
 *          ---------------------------------------------<br>
 */
struct qentry queuetab[NQENT];

/**
 * @brief プロセスをプロセスキューテーブルの末尾に挿入する。
 * @param[in] pid 挿入するプロセスID
 * @param[in] q 使用するキューID
 * @return 成功時はキューに挿入したプロセスID、引数不正時はSYSERRを返す。
 */
pid32 enqueue(pid32 pid, qid16 q)
{
	qid16 tail, prev; /* Tail & previous node indexes	*/

	if (isbadqid(q) || isbadpid(pid))
	{
		return SYSERR;
	}

	tail = queuetail(q);
	prev = queuetab[tail].qprev;

	queuetab[pid].qnext = tail; /* Insert just before tail node	*/
	queuetab[pid].qprev = prev;
	queuetab[prev].qnext = pid;
	queuetab[tail].qprev = pid;
	return pid;
}

/**
 * @brief プロセスキューテーブルからキューを削除し、リスト先頭のプロセスIDを返す。
 * @param[in] q 使用するキューID
 * @return  キューを削除した場合はリスト先頭のプロセスID、キューIDが不正の場合はSYSERR、<br>
 * キューが空の場合はEMPTYを返す。
 */
pid32 dequeue(
	qid16 q /* ID of queue to use		*/
)
{
	pid32 pid; /* ID of process removed	*/

	if (isbadqid(q))
	{
		return SYSERR;
	}
	else if (isempty(q))
	{
		return EMPTY;
	}

	pid = getfirst(q);
	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;
	return pid;
}
