/**
 * @file strnlen.c
 * @brief NULL終端された文字列の長さを返す。
 * @details 文字列を読み取る長さは、ユーザが指定したN Byteを最大長とする。<br>
 * 文字列の長さにNULL終端を含まない。
 */

/**
 * @brief NULL終端された文字列の長さを返す。NULL終端は長さに含まない。
 * @param[in] s 長さを調べる対象の文字列
 * @param[in] len 読み取る長さの最大長（Byte）
 * @return  文字列の長さを返す。NULL終端は長さに含まず、ユーザが指定したN Byteを最大長とする。
 */
int strnlen(const char *s, unsigned int len)
{
    int n;

    n = 0;
    while (*s++ && n < len)
        n++;

    return (n);
}
