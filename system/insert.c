/**
 * @file insert.c
 * @brief 優先度に基づいてキューにプロセスを挿入するAPIを提供する。
 */
#include <xinu.h>

/**
 * @brief 優先度に基づいて、キューにプロセスを挿入する。
 * @details  優先度の降順に並べたキューに対して、以下を行う。
 * Step1. キューを先頭から走査（whileループ部）<br>
 * Step2. 挿入しようとしているプロセスIDの優先度より低い優先度を持つプロセスを探す。<br>
 * Step3.「より低優先度なプロセスノード（Step2で見つけたノード）」と「その前にあるノード」との間に、
 * 挿入したいプロセスを配置する。
 * なお、キューの末尾は有効な最小キーを下回るため、ループは必ず停止する。
 * @param[in] pid 挿入するプロセスID
 * @param[in] q 使用するキューID
 * @param[in] 挿入するプロセスの優先度（キー）
 * @return 成功時はOK、キューIDもしくはプロセスIDが不正の場合はSYSERRを返す。
 */
status insert(pid32 pid, qid16 q, int32 key)
{
	qid16 curr; /* Runs through items in a queue*/
	qid16 prev; /* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid))
	{
		return SYSERR;
	}

	curr = firstid(q);
	while (queuetab[curr].qkey >= key)
	{
		curr = queuetab[curr].qnext;
	}

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev; /* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}
