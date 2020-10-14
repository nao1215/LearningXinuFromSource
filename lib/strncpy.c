/**
 * @file strncpy.c
 * @brief 文字列s1に文字列s2をN文字（Byte）分コピーする。
 */

/**
 * @brief 文字列s1に文字列s2をN文字（Byte）分コピーする。
 * @details 自動でNULL終端（'\0'）は付与しない。<br>
 * また、N Byteコピーする前にNULL終端に達した場合、残りのByte数分をNULL終端で埋める。
 * @param[in,out] s1 コピー先の文字列
 * @param[in] s2 コピー元の文字列
 * @param[in] n コピーする文字数（Byte）
 * @return  コピー後の文字列s1を返す。
 */
char *strncpy(char *s1, const char *s2, int n)
{
    register int i;
    register char *os1;

    os1 = s1;
    for (i = 0; i < n; i++)
    {
        if (((*s1++) = (*s2++)) == '\0')
        {
            while (++i < n)
            {
                *s1++ = '\0';
            }
            return os1;
        }
    }
    return os1;
}
