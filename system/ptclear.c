/**
 * @file ptclear.c
 * @brief ポートを用いたメッセージと待機中プロセスを解放する。
 */
#include <xinu.h>

/**
 * @brief ポートを用いたメッセージと待機中プロセスを解放する。
 * @details
 * Step1. ポートの状態をLIMBOとし、他のプロセスからポート使用不可とする。<br>
 * Step2. ポートシーケンス番号をリセットする。<br>
 * Step3. メッセージリストが空になるまで、各メッセージを処分する。<br>
 * Step4. メッセージリスト全体をフリーリストとする。<br>
 * Step5. 引数で指定されたポートクリア後の状態に応じて、処理を切り替える。<br>
 * 　・PT_ALLOCの場合：ポートテーブルエントリの先頭と末尾をNULLを指す状態とし、送受信用セマフォをリセットする。<br>
 * 　・上記以外の場合：送受信用セマフォを削除する。<br>
 * Step6. ポート状態を引数で指定された状態に変更する。
 * @param[in] ptptr クリア対象のポートテーブルエントリ
 * @param[in] newstate ポートをクリアした後の新しい状態
 * @param[in] dispose メッセージ処分用の関数ポインタ
 * @note ポート内部の関数をクリアまたはリセットするために、ptdeleteおよびreset経由で_ptclear()は使用される。<br>
 * _ptclear()の呼び出しは、割り込みが無効であり、引数の有効性がチェックされている事を前提としている。
 */
void _ptclear(struct ptentry *ptptr, uint16 newstate, int32 (*dispose)(int32))
{
	struct ptnode *walk; /* Pointer to walk message list	*/

	/* Place port in limbo state while waiting processes are freed */

	ptptr->ptstate = PT_LIMBO;

	ptptr->ptseq++;		  /* Reset accession number	*/
	walk = ptptr->pthead; /* First item on msg list	*/

	if (walk != NULL)
	{ /* If message list nonempty	*/

		/* Walk message list and dispose of each message */

		for (; walk != NULL; walk = walk->ptnext)
		{
			(*dispose)(walk->ptmsg);
		}

		/* Link entire message list into the free list */

		(ptptr->pttail)->ptnext = ptfree;
		ptfree = ptptr->pthead;
	}

	if (newstate == PT_ALLOC)
	{
		ptptr->pttail = ptptr->pthead = NULL;
		semreset(ptptr->ptssem, ptptr->ptmaxcnt);
		semreset(ptptr->ptrsem, 0);
	}
	else
	{
		semdelete(ptptr->ptssem);
		semdelete(ptptr->ptrsem);
	}
	ptptr->ptstate = newstate;
	return;
}
