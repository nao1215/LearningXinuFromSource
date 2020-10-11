/**
 * @file strcpy.c
 * @brief 文字列Aに文字列Bをコピーする。
 */

/**
 * @brief 文字列Aに文字列B（NULL終端を含めて）をコピーする。
 * @param[in,out] tar コピー先の文字列
 * @param[in] src コピーする文字列
 * @return 0を返す。
 */
int strcpy(char *tar, char *src)
{
	while ((*tar++ = *src++) != '\0')
	{
		;
	}
	return 0;
}
