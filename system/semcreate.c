/**
 * @file semcreate.c
 * @brief 新しいセマフォを作成する。
 */
#include <xinu.h>

//! 未使用のセマフォIDを返す。
local sid32 newsem(void);

/**
 * @brief 未使用セマフォを割り当て、そのセマフォへのインデックス（セマフォID）を返す。
 * @details
 * Step1. 割り込みを禁止する<br>
 * Step2. セマフォカウント初期値が負の値、もしくは未使用のセマフォがない場合は、割り込みを許可状態に復元し、処理を終了する。<br>
 * Step3. newsem()で取得したセマフォIDを用いて、セマフォテーブルからセマフォを取り出し、セマフォカウントの初期値を設定する。<br>
 * Step4. 割り込みを許可状態に復元する。
 * @param[in] count セマフォカウントの初期値
 * @return セマフォが生成できた場合は生成したセマフォのID、<br>
 * 「セマフォカウント初期値が負の値」もしくは「未使用のセマフォがない」場合はSYSERRを返す。
 * @note セマフォの状態は、newsem()内で未使用→使用に変更されている。
 */
sid32 semcreate(int32 count)
{
	intmask mask; /* Saved interrupt mask		*/
	sid32 sem;	  /* Semaphore ID to return	*/

	mask = disable();

	if (count < 0 || ((sem = newsem()) == SYSERR))
	{
		restore(mask);
		return SYSERR;
	}
	semtab[sem].scount = count; /* Initialize table entry	*/

	restore(mask);
	return sem;
}

/**
 * @brief 未使用セマフォを探索し、そのセマフォへのインデックス（セマフォID）を返す。
 * @details newsem()内で、次に確認すべきセマフォ（未使用セマフォ）へのインデックスを保持している。<br>
 * 未使用セマフォが見つかるまで、以下の処理を最大NSEM（セマフォ上限数）回ループして、セマフォテーブルの全探索を行う。<br>
 * Step1. 前回調査したセマフォIDをインクリメントする。<br>
 * Step2. 調査対象のセマフォIDがNSEMを超えていた場合、調査対象のセマフォIDを0とする。<br>
 * Step3. 調査対象のセマフォIDが未使用状態であった場合、使用中に変更し、そのセマフォIDを返して処理を終了する。<br>
 * @return 未使用セマフォが見つかった場合はそのセマフォID、未使用セマフォが無かった場合はSYSERRを返す。
 */
local sid32 newsem(void)
{
	static sid32 nextsem = 0; /* Next semaphore index to try	*/
	sid32 sem;				  /* Semaphore ID to return	*/
	int32 i;				  /* Iterate through # entries	*/

	for (i = 0; i < NSEM; i++)
	{
		sem = nextsem++;
		if (nextsem >= NSEM)
			nextsem = 0;
		if (semtab[sem].sstate == S_FREE)
		{
			semtab[sem].sstate = S_USED;
			return sem;
		}
	}
	return SYSERR;
}
