/**
 * @file strstr.c
 * @brief 検索対象の文字列Aから文字列Bを探す。
 */

/**
 * @brief 検索対象の文字列Aから文字列Bを探す。
 * @param[in] cs 検索対象の文字列
 * @param[in] ct 検索語句（検索キーワード）となる文字列
 * @return 検索語句が見つかった場合はその位置をポインタで返し、見つからなかった場合はNULLを返す。
 */
char *strstr(const char *cs, const char *ct)
{
    char *cq;
    char *cr;

    for (; *cs != '\0'; cs++)
    {
        if (*cs == *ct)
        {
            cq = (char *)cs;
            cr = (char *)ct;
            while ((*cq != '\0') && (*cr != '\0'))
            {
                if (*cq != *cr)
                {
                    break;
                }
                cq++;
                cr++;
            }
            if ('\0' == *cr)
            {
                return (char *)cs;
            }
        }
    }
    return 0;
}
