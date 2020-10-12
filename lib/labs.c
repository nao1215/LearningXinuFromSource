/**
 * @file labs.c
 * @brief 実数（long型）の絶対値を返す。
 */

/**
 * @brief 実数（long型）の絶対値を返す。
 * @param[in] arg 絶対値に変換したい実数（long型）
 * @return 引数argの絶対値（long型）
 */
long labs(long arg)
{
    if (arg < 0)
        arg = -arg;
    return (arg);
}
