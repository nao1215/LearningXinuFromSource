/**
 * @file memcpy.c
 * @brief メモリAの領域（source）からメモリBの領域（Destination）にN Byteコピーする。
 */

/**
 * @brief メモリAの領域（source）からメモリBの領域（Destination）にN Byteコピーする。
 * @param[in,out] s コピー先のアドレス（Destination address）
 * @param[in] ct コピー元のアドレス（Source address）
 * @param[in] n コピーサイズ（Byte）
 * @return コピー完了後のコピー先アドレス
 */
void *memcpy(void *s, const void *ct, int n)
{
    register int i;
    char *dst = (char *)s;
    char *src = (char *)ct;

    for (i = 0; i < n; i++)
    {
        *dst++ = *src++;
    }
    return s;
}
