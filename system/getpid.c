/**
 * @file getpid.c
 * @brief 現在実行中のプロセスIDを返す。
 */
#include <xinu.h>

/**
 * @brief 現在実行中のプロセスIDを返す。
 * @return 現在実行中のプロセスIDを返す（グローバル変数currpidをそのまま返す）
 */
pid32 getpid(void)
{
	return (currpid);
}
