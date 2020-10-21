/**
 * @file semcount.c
 * @brief セマフォのカウント値を返す。
 */
#include <xinu.h>

/**
 * @brief セマフォのカウント値を返す。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 「セマフォIDが不正値」か「セマフォがFREE状態」の場合、割り込み許可状態に復元して、処理を終了する。<br>
 * Step3. 引数で渡されたセマフォIDを基に、セマフォテーブルからセマフォのカウント値を取得する。<br>
 * Step4. 割り込み許可状態に復元する。
 * @param[in] semid セマフォカウンタを確認したいセマフォのID
 * @return 成功時はセマフォのカウント値、「不正なセマフォID」や「セマフォがFREE状態の場合はSYSERR」を返す。
 * @note セマフォカウンタ値が整数値（正負問わず）のため、SYSERR（-1）と同じ値になる可能性がある。
 */
syscall semcount(sid32 semid)
{
	intmask mask; /* Saved interrupt mask		*/
	int32 count;  /* Current sempahore count	*/

	mask = disable();

	if (isbadsem(semid) || semtab[semid].sstate == S_FREE)
	{
		restore(mask);
		return SYSERR;
	}
	count = semtab[semid].scount;
	restore(mask);
	return count;
}
