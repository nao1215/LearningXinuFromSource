/**
 * @file ptcreate.c
 * @brief 未処理のメッセージを「カウント」できるポートを作成する。
 */
#include <xinu.h>

/**
 * @brief 未処理のメッセージを「カウント」できるポートを作成する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. ポートサイズが0より小さい場合は割り込み状態を復元し、処理を終了する。<br>
 * Step3. 0〜NPORTS(30)の中で、空きポートIDを探す。<br>
 * Step4. 空きポートに以下の対応を行う。<br>
 * 　・状態をALLOCに変更<br>
 * 　・送受信セマフォを作成<br>
 * 　・メッセージリストを初期化（先頭と末尾をNULLとする）<br>
 * 　・シーケンス番号を1増加<br>
 * 　・最大待機メッセージ数を設定<br>
 * Step5. 割り込み状態を復元する。
 * @param[in] count ポートサイズ（未処理メッセージの最大数）
 * @return 成功時は割り当てたポートID、ポートサイズが不正な場合はSYSERRを返す。
 */
syscall ptcreate(int32 count)
{
	intmask mask;		   /* Saved interrupt mask		*/
	int32 i;			   /* Counts all possible ports	*/
	int32 ptnum;		   /* Candidate port number to try	*/
	struct ptentry *ptptr; /* Pointer to port table entry	*/

	mask = disable();
	if (count < 0)
	{
		restore(mask);
		return SYSERR;
	}

	for (i = 0; i < NPORTS; i++)
	{					  /* Count all table entries	*/
		ptnum = ptnextid; /* Get an entry to check	*/
		if (++ptnextid >= NPORTS)
		{
			ptnextid = 0; /* Reset for next iteration	*/
		}

		/* Check table entry that corresponds to ID ptnum */

		ptptr = &porttab[ptnum];
		if (ptptr->ptstate == PT_FREE)
		{
			ptptr->ptstate = PT_ALLOC;
			ptptr->ptssem = semcreate(count);
			ptptr->ptrsem = semcreate(0);
			ptptr->pthead = ptptr->pttail = NULL;
			ptptr->ptseq++;
			ptptr->ptmaxcnt = count;
			restore(mask);
			return ptnum;
		}
	}
	restore(mask);
	return SYSERR;
}
