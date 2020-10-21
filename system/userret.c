/**
 * @file userret.c
 * @brief プロセスが最上位の関数に戻る時に呼ばれる。現在のプロセスを終了させる。
 */
#include <xinu.h>

/**
 * @brief プロセスが最上位の関数に戻る時に呼ばれる。現在のプロセスを終了させる。
 * @note プロセス作成時に、戻りアドレスとしてuserret()がスタックに積まれる。
 */
void userret(void)
{
	kill(getpid()); /* Force process to exit */
}
