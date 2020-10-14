/**
 * @file memcmp.c
 * @brief Byteブロック2個に対して、先頭からN Byte分比較する。
 */

/*------------------------------------------------------------------------
 *  memcmp  -  Compare two equal-size blocks of memory.  If there are no
 *			differences, return 0.  Otherwise return >0 or <0
 *			if the first differing byte is greater or less
 *------------------------------------------------------------------------
 */
/**
 * @brief Byteブロック2個に対して、先頭からN Byte分比較する。
 * @param[in] s1 Byteブロックその1
 * @param[in] s2 Byteブロックその2
 * @param[in] n 比較するサイズ（Byte）
 * @return Byteブロックs1とs2に差がなければ0、s1>s2の場合は正の値、s1<s2の場合は負の値を返す。
 */
int memcmp(const void *s1, const void *s2, int n)
{
    const unsigned char *c1;
    const unsigned char *c2;

    for (c1 = s1, c2 = s2; n > 0; n--, c1++, c2++)
    {
        if (*c1 != *c2)
        {
            return ((int)*c1) - ((int)*c2);
        }
    }
    return 0;
}
