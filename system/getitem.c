/**
 * @file getitem.c
 * @brief キュー内のプロセスを操作するAPI（プロセス取得API）を提供する。
 */
#include <xinu.h>

/**
 * @brief キューの先頭からプロセスを取り出す。
 * @param[in] q プロセスを取り出すためのキューID（チェックなしで有効）
 * @return キューにプロセスがある場合はキューの先頭にあるプロセスID、<br>
 * キューが空の場合はEMPTYを返す。
 */
pid32 getfirst(qid16 q)
{
	pid32 head;

	if (isempty(q))
	{
		return EMPTY;
	}

	head = queuehead(q);
	return getitem(queuetab[head].qnext);
}

/**
 * @brief キューの末尾からプロセスを取り出す。
 * @param[in] q プロセスを取り出すためのキューID（チェックなしで有効）
 * @return キューにプロセスがある場合はキューの末尾にあるプロセスID、<br>
 * キューが空の場合はEMPTYを返す。
 */
pid32 getlast(qid16 q)
{
	pid32 tail;

	if (isempty(q))
	{
		return EMPTY;
	}

	tail = queuetail(q);
	return getitem(queuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32 getitem(
	pid32 pid /* ID of process to remove	*/
)
{
	pid32 prev, next;

	next = queuetab[pid].qnext; /* Following node in list	*/
	prev = queuetab[pid].qprev; /* Previous node in list	*/
	queuetab[prev].qnext = next;
	queuetab[next].qprev = prev;
	return pid;
}
