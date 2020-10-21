/**
 * @file fputs.c
 * @brief 文字列をデバイス（ファイル）に書き込む。
 */

//! 文字を書き込むputc()のextern宣言
extern int putc(int, char);

/**
 * @brief 文字列をデバイス（ファイル）に書き込む。
 * @param[in] s 書き込む文字列（NULL終端されている事）
 * @param[in] dev デバイスディスクリプタ
 * @return 最後にputc()で書き込んだ結果を返す（詳細は、 putc()を参照する事）
 */
int fputs(char *s, int dev)
{
    int r = 0, c;

    while ((c = (*s++)))
    {
        r = putc(dev, c);
    }
    return r;
}
