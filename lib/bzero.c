/**
 * @file bzero.c
 * @brief Byteブロック領域の先頭N bytesを数値ゼロで埋める。
 */

/**
 * @brief Byteブロック領域の先頭N bytesを数値ゼロで埋める。
 * @param[in,out] p Byteブロック（bzero()終了後にゼロで埋まった状態となる）
 * @param[in] len 数値ゼロ埋めするサイズ（Byte）
 * @note 引数lenが0以下の場合は、何もせずreturnする。
 */
void bzero(
    void *p,
    int len)
{
    int n;
    char *pch = (char *)p;

    if ((n = len) <= 0)
    {
        return;
    }
    do
    {
        *pch++ = 0;
    } while (--n);
}
