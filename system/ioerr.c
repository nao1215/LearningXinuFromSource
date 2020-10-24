/**
 * @file ioerr.c
 * @brief ステータスとしてエラーを返す（デバイステーブルの"error"エントリに対して使用する）
 */

#include <xinu.h>

/**
 * @brief ステータスとしてエラーを返す（デバイステーブルの"error"エントリに対して使用する）。
 * @return  SYSERRを返す。
 */
devcall ioerr(void)
{
	return SYSERR;
}
