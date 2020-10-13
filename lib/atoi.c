/**
 * @file atoi.c
 * @brief ASCII文字列をint型の整数に変換する。
 */

/**
 * @brief ASCII文字列をint型に変換する。
 * @details 処理の流れは、<br>
 * Step1. 「不要な文字（空白、TAB）の削除」もしくは「正数／負数の判定」を行う<br>
 * Step2.  0〜9の範囲の値であれば、一桁ずつ記録する。それ以外の文字は呼び飛ばす<br>
 *         ASCIIコードとして、0=0x30、1=0x31、2=0x32、…、9=0x39であるため、<br>
 *         「0x30〜0x39の範囲のASCIIコード値(0〜9の値) - '0'(=0x30)」と計算すれば、<br>
 *         0〜9の整数値が得られる。<br>
 * Step3. Step.1で取得した符号情報（±）を反映した整数を返す。
 * @param[in] p ASCII文字列
 * @return ASCII文字列をint型に変換した整数値
 * @note ASCIIコード情報は、ターミナル上で"$ man ascii"で確認できる。
 */
int atoi(char *p)
{
    int n = 0, f = 0;

    for (;; p++)
    {
        switch (*p)
        {
        case ' ':
        case '\t':
            continue;
        case '-':
            f++;
        case '+':
            p++;
        }
        break;
    }

    while (*p >= '0' && *p <= '9')
    {
        n = n * 10 + *p++ - '0';
    }

    return (f ? -n : n);
}
