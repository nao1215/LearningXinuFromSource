/**
 * @file fputc.c
 * @brief 文字をデバイス（ファイル）に書き込む。
 */

//! 文字を書き込むputc()のextern宣言
extern int putc(int, char);

#ifndef SYSERR
//! システムエラーを示す値
#define SYSERR (-1)
#endif
#ifndef EOF
//! End Of Fileを示す値
#define EOF (-2)
#endif

/**
 * @brief 文字をデバイス（ファイル）に書き込む。
 * @param[in] c 書き込む文字
 * @param[in] dev デバイスディスクリプタ
 * @return 成功時は書き込んだ文字、異常時はEOFを返す。
 */
int fputc(int c, int dev)
{
    if (SYSERR == (int)putc(dev, c))
    {
        return EOF;
    }
    else
    {
        return c;
    }
}
