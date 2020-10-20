/**
 * @file xdone.c
 * @brief 最終プロセスの終了時、システム終了メッセージを表示する。
 */
#include <xinu.h>

/**
 * @brief 最終プロセスの終了時、システム終了メッセージを表示する。
 */
void xdone(void)
{
	kprintf("\n\nAll user processes have completed.\n\n");
	halt(); /* Halt the processor		*/
}
