/**
 * @file ptreset.c
 * @brief ポートをリセットを行う。
 * @details 待機中のプロセスとメッセージを解放した後、ポートを再利用できるようにする。
 */
/* ptreset.c - ptreset */

#include <xinu.h>

/**
 * @brief ポートをリセットを行う。
 * @details 待機中のプロセスとメッセージを解放した後、ポートを再利用できるようにする。<br>
 * Step1. 割り込みを禁止する。<br>
 * Step2. ポートIDが不正、もしくはポートがALLOC状態でなければ割り込み状態を復元し、処理を終了する。<br>
 * Step3. ポートを用いたメッセージと待機中プロセスを解放し、セマフォはリセットする。<br>
 * Step4. 割り込み状態を復元する。
 * @param[in] portid 削除対象のポート
 * @param[in] disp 待機メッセージ処分用の関数ポインタ
 * @return 成功時はOK、ポートIDが不正もしくはポートがALLOC状態以外の場合はSYSERRを返す。
 */
syscall ptreset(int32 portid, int32 (*disp)(int32))
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
	_ptclear(ptptr, PT_ALLOC, disp);
	restore(mask);
	return OK;
}
