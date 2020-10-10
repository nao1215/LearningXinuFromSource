/**
 * @file newqueue.c
 * @brief グローバルキューテーブルにキューを割り当て、テーブルを初期化する。
 */
#include <xinu.h>

/**
 * @brief グローバルキューテーブルにキューを割り当て、テーブルを初期化する。
 * @details newqueue()は、キューテーブルのインデックスNPROC以降にリストの先頭／末尾を作成し、<br>
 * そのリストに要素を追加できる状態にする。<br>
 * 次にnewqueue()を呼び出された時、キューテーブルの位置に新しいリストの先頭／末尾を配置すべきかは、<br>
 * newqueue()内のstatic変数nextqidを参照すれば判断できる。
 * @return 成功時はリストの先頭ノードインデックス、キューテーブルがオーバフローした場合はSYSERRを返す。
 */
qid16 newqueue(void)
{
	static qid16 nextqid = NPROC; /* Next list in queuetab to use	*/
	qid16 q;					  /* ID of allocated queue 	*/

	q = nextqid;
	if (q >= NQENT)
	{ /* Check for table overflow	*/
		return SYSERR;
	}

	nextqid += 2; /* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */

	queuetab[queuehead(q)].qnext = queuetail(q);
	queuetab[queuehead(q)].qprev = EMPTY;
	queuetab[queuehead(q)].qkey = MAXKEY;
	queuetab[queuetail(q)].qnext = EMPTY;
	queuetab[queuetail(q)].qprev = queuehead(q);
	queuetab[queuetail(q)].qkey = MINKEY;
	return q;
}
