/**
 * @file xsh_argecho.c
 * @brief 引数を順に表示する。
 */
#include <xinu.h>
#include <stdio.h>

/**
 * @brief 引数を順に表示する。
 * @details 「引数番号」と「引数番号に対応する引数（文字列として扱う）」が1行単位で出力される。
 * @param[in] nargs 引数の数
 * @param[in] args 引数（引数を持つ配列）
 * @return 0を返す。
 */
shellcmd xsh_argecho(int nargs, char *args[])
{
	int32 i;

	printf("\n\nThe %d arguments are:\n", nargs);
	for (i = 0; i < nargs; i++)
	{
		printf("    %2d: %s\n", i, args[i]);
	}
	printf("\n");

	return 0;
}
