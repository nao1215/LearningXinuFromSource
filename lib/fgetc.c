/**
 * @file fgetc.c
 * @brief デバイス（ファイル）から文字を読み込む。
 */
extern int getc(int);

#ifndef EOF
//! End Of Fileを示す値
#define EOF (-2)
#endif

/**
 * @brief デバイス（ファイル）から文字を読み込む。
 * @param[in] dev デバイスディスクリプタ
 * @return  成功時は読み込んだ文字、異常時はEOFを返す。
 */
int fgetc(
    int dev)
{
    int result = (int)getc(dev);

    if (0 > result)
    {
        return EOF;
    }
    else
    {
        return result;
    }
}
