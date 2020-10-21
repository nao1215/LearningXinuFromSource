/**
 * @file fgets.c
 * @brief デバイス（ファイル）から文字列を読み込む。
 */
#ifndef NULL
//! NULLを示す値
#define NULL 0
#endif

//! デバイスから1Byte読み込むgetc()のextern宣言
extern int getc(int);

/**
 * @brief デバイス（ファイル）から文字列を読み込む。
 * @details 以下のいずれかの場合に、文字列の読み込みを停止する<br>
 * 　・最大読み込みByteに達した<br>
 * 　・行の最後（改行コード）まで達した（Linux形式=LFか、Mac形式=CRのどちらか）<br>
 * 　・EOFまで達した<br>
 * 文字列（改行コード含む）の最後にはNULL終端を付与する。
 * @param[in,out] s 読み込んだ文字列
 * @param[in] n 最大読み込みByte
 * @param[in] dev デバイスディスクリプタ
 * @return  成功時は読み込んだ文字列（改行コードとNULL終端含む）、EOFや空文字の場合はNULLを返す。
 */
char *fgets(char *s, int n, int dev)
{
    int c = 0;
    char *cs;

    cs = s;

    /* Read characters until maximum read length, */
    /*  end of line, or end of file               */
    while ((--n > 0) && ((c = getc(dev)) >= 0))
    {
        *cs++ = c;
        if (('\n' == c) || ('\r' == c))
        {
            break;
        }
    }

    /* Check for EOF or empty string */
    if ((c < 0) && (cs == s))
    {
        return NULL;
    }

    /* Terminate string and return */
    *cs++ = '\0';
    return s;
}
