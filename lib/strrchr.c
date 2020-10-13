/**
 * @file strrchr.c
 * @brief 文字列から指定された文字を探し、最後に見つかった位置をポインタで返す。
 */

/**
 * @brief 文字列の後方から指定された文字を探し、最後に見つかった位置をポインタで返す。
 * @param[in] s 探索対象の文字列
 * @param[in] c 検索文字
 * @return 文字cが見つかった場合は文字cが最後に登場した位置を示すポインタ、<br>
 * 文字cが見つからなかった場合はNULLを返す。
 */
char *strrchr(const char *s, int c)
{
    char *r = 0;

    for (; *s != '\0'; s++)
    {
        if (*s == (const char)c)
        {
            r = (char *)s;
        }
    }

    if ((const char)c == *s)
    {
        return (char *)s;
    }

    return r;
}
