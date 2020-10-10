/**
 * @file xsh_exit.c
 * @brief XINUシェルにおけるexitコマンドを提供する。
 * @details exitコマンドは、シェル終了を引き起こす終了コードを返す。
 */

#include <xinu.h>

/**
 * @brief exitコマンドとして、シェル終了を引き起こす終了コードを返す。
 * @param[in] nargs 引数の数（使用しない）
 * @param[in] args 引数（使用しない）
 * @return SHELL_EXITを返す。
 */
shellcmd xsh_exit(int nargs, char *args[])
{
	return SHELL_EXIT;
}
