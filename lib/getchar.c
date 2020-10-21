/**
 * @file getchar.c
 * @brief STDIN（標準入力）から文字を読み込む。
 */
#include <xinu.h>
#include <stdio.h>

/**
 * @brief STDIN（標準入力）から文字を読み込む。
 * @return 成功時は読み込んだ文字、異常時はEOFを返す。
 */
int getchar(void)
{
	return fgetc(stdin);
}
