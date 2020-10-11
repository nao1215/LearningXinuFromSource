/**
 * @file strlen.c
 * @brief NULL終端された文字列の長さを返す。NULL終端は長さに含まない。
 */

/**
 * @brief NULL終端された文字列の長さを返す。NULL終端は長さに含まない。
 * @param[in] str 長さを調べる対象の文字列
 * @return  文字列の長さを返す。NULL終端は長さに含まない。
 */
int strlen(char *str)
{
	int len;

	len = 0;

	while (*str++ != '\0')
	{
		len++;
	}
	return len;
}
