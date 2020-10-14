/**
 * @file strchr.c
 * @brief 指定された文字を文字列から探し、最初にに見つかった位置をポインタで返す。
 */

/**
 * @brief 指定された文字を文字列から探し、最初にに見つかった位置をポインタで返す。
 * @param[in] s 探索対象の文字列
 * @param[in] c 検索文字
 * @return 文字cが見つかった場合は文字cが最初に登場した位置を示すポインタ、<br>
 * 文字cが見つからなかった場合はNULLを返す。
 */
char *strchr(const char *s, int c)
{
    for (; *s != '\0'; s++)
    {
        if (*s == (const char)c)
        {
            return (char *)s;
        }
    }

    if ((const char)c == *s)
    {
        return (char *)s;
    }

    return 0;
}
