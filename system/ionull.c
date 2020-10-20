/**
 * @file ionull.c
 * @brief 何もしない（デバイステーブルの"don't care"エントリに使用する）
 */
#include <xinu.h>

/**
 * @brief 何もしない（デバイステーブルの"don't care"エントリに使用する）
 * @return 必ずOKを返す。
 */
devcall ionull(void)
{
	return OK;
}
