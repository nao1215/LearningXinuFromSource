/**
 * @file panic.c
 * @brief Panic状態に陥った旨のメッセージを表示し、全てのプロセスを停止させる。
 */
#include <xinu.h>

/**
 * @brief Panic状態に陥った旨のメッセージを表示し、全てのプロセスを停止させる。
 * @details 割り込み禁止後にPanicメッセージを表示し、無限ループを行う。
 * @param[in] msg 表示するメッセージ
 */
void panic(char *msg)
{
	disable(); /* Disable interrupts		*/
	kprintf("\n\n\rpanic: %s\n\n", msg);
	while (TRUE)
	{
		;
	} /* Busy loop forever		*/
}
