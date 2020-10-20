/**
 * @file exit.c
 * @brief 現在実行中のプロセスを終了させる。
 */

#include <xinu.h>

/**
 * @brief 現在実行中のプロセスを終了させる。
 */
void exit(void)
{
	kill(getpid()); /* Kill the current process */
}
