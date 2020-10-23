/**
 * @file xsh_echo.c
 * @brief STDOUT（標準出力）に引数に指定した文字列を出力する。
 */
#include <xinu.h>
#include <stdio.h>

/**
 * @brief STDOUT（標準出力）に引数に指定した文字列を出力する。
 * @details 複数の引数がある場合は、改行せずにスペース区切りで引数が続けて出力される。
 * @param[in] nargs 引数の数
 * @param[in] args 引数（引数を持つ配列）
 * @return 0を返す。
 */
shellcmd xsh_echo(int nargs, char *args[])
{
	int32 i; /* walks through args array	*/

	if (nargs > 1)
	{
		printf("%s", args[1]);

		for (i = 2; i < nargs; i++)
		{
			printf(" %s", args[i]);
		}
	}
	printf("\n");

	return 0;
}
