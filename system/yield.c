/**
 * @file yield.c
 * @brief CPU実行権を自発的に放棄する（タイムスライスを終了する）
 */
#include <xinu.h>

/**
 * @brief CPU実行権を自発的に放棄する（タイムスライスを終了する）。
 * @details 割り込みを禁止して再スケジューリングを行う。復帰後、割り込み状態を復元する。
 * @return OKを返す。
 */
syscall yield(void)
{
	intmask mask; /* Saved interrupt mask		*/

	mask = disable();
	resched();
	restore(mask);
	return OK;
}
