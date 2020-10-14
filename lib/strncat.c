/**
 * @file strncat.c
 * @brief 文字列s1の末尾に文字列s2をN文字（Byte）分、結合する。
 */

/**
 * @brief 文字列s1の末尾に文字列s2をN文字（Byte）分、結合する。
 * @details 処理の流れは、以下の通り。<br>
 * Step1. 文字列s1のNULL終端'\0'までポインタを進める。<br>
 * Step2. 文字列s1のNULL終端の位置から文字列s2を一文字ずつ連結する。<br>
 * Step3. N+1回目にNULL終端を付与する。<br>
 * @param[in,out] s1 結合先の文字列
 * @param[in] s2 結合する文字列
 * @param[in] n 結合する文字数（Byte）
 * @return  結合後の文字列s1を返す（NULL終端済み）。
 */
char *strncat(char *s1, const char *s2, int n)
{
    char *os1;

    os1 = s1;
    while (*s1++)
        ;
    --s1;
    while ((*s1++ = *s2++))
        if (--n < 0)
        {
            *--s1 = '\0';
            break;
        }
    return (os1);
}
