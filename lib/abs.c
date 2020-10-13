/**
 * @dir lib
 * @brief C言語標準ライブラリ（Glibc）相当のXINUライブラリ
 * @file abs.c
 * @brief 整数（int型）の絶対値を返す。
 */

/**
 * @brief 整数の絶対値（int型）を返す。
 * @param[in] arg 絶対値に変換したい整数（int型）
 * @return 引数argの絶対値（int型）
 */
int abs(int arg)
{
    if (arg < 0)
        arg = -arg;
    return (arg);
}
