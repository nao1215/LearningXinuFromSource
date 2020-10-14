/**
 * @file memset.c
 * @brief 指定のByteブロックに対して、同じ値をNバイト分書き込む。
 */

/**
 * @brief 指定のByteブロックに対して、同じ値をNバイト分書き込む。
 * @param[in,out] s Byteブロックへのポインタ（例：文字列）
 * @param[in] c 書き込む値（1Byte）
 * @param[in] n 書き込むサイズ（Byte）
 * @return 書き込み完了後のByteブロックへのポインタ
 */
void *memset(
    void *s, /* Address of memory block	*/
    int c,   /* Byte value to use		*/
    int n    /* Size of block in bytes 	*/
)
{
    register int i;
    char *cp = (char *)s;

    for (i = 0; i < n; i++)
    {
        *cp = (unsigned char)c;
        cp++;
    }
    return s;
}
