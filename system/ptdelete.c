/**
 * @file ptdelete.c
 * @brief ポートを削除し、待機中のプロセスとメッセージを解放する。
 */
#include <xinu.h>

/**
 * @brief ポートを削除し、待機中のプロセスとメッセージを解放する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. ポートIDが不正、もしくはポートがALLOC状態でなければ割り込み状態を復元し、処理を終了する。<br>
 * Step3. ポートを用いたメッセージと待機中プロセスを解放する。<br>
 * Step4. 次回のポート作成時には、今回削除したポートIDを使用するように設定する。<br>
 * Step5. 割り込み状態を復元する。
 * @param[in] portid 削除対象のポート
 * @param[in] disp 待機メッセージ処分用の関数ポインタ
 * @return 成功時はOK、ポートIDが不正もしくはポートがALLOC状態以外の場合はSYSERRを返す。
 */
syscall ptdelete(int32 portid, int32 (*disp)(int32))
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct ptentry *ptptr; /* Pointer to port table entry	*/

	mask = disable();
	if (isbadport(portid) ||
		(ptptr = &porttab[portid])->ptstate != PT_ALLOC)
	{
		restore(mask);
		return SYSERR;
	}
	_ptclear(ptptr, PT_FREE, disp);
	ptnextid = portid;
	restore(mask);
	return OK;
}
