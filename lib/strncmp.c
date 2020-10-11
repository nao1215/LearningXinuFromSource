/**
 * @file strncmp.c
 * @brief 二つの文字列を最大N byteまで比較し、その結果を返す。
 */

/**
 * @brief 二つの文字列を最大N byteまで比較し、その結果を返す。
 * @param[in] s1 比較対象の文字列その1
 * @param[in] s2 比較対象の文字列その2
 * @param[in] n  比較するByte数（最大Byte）
 * @return s1 > s2の場合は0より大きい値、s1 = s2の場合は0、s1 < s2の場合は0より小さい値を返す。
 */
int strncmp(char *s1, char *s2, int n)
{

    while (--n >= 0 && *s1 == *s2++)
    {
        if (*s1++ == '\0')
        {
            return 0;
        }
    }
    return (n < 0 ? 0 : *s1 - *--s2);
}
