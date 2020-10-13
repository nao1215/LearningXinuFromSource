/**
 * @file strcmp.c
 * @brief 二つの文字列を比較し、その結果を返す。
 */

/**
 * @brief 二つの文字列を比較し、その結果を返す。
 * @param[in] str1 比較対象の文字列その1
 * @param[in] str2 比較対象の文字列その2
 * @return str1 > str2の場合は1、s1 = s2の場合は0、str1 < str2の場合は-1を返す。
 */
int strcmp(
	char *str1,
	char *str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
		{
			return 0;
		}
		str1++;
		str2++;
	}
	if (*str1 < *str2)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
