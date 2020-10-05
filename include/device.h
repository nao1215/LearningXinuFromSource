/**
 * @file device.h
 * @brief 「デバイス名の最大長」と「デバイスID検証マクロ」を提供する。
 */

//!  デバイス名の最大サイズ
#define DEVNAMLEN 16

/* Macro used to verify device ID is valid  */
/**
 * @def isbaddev()
 * @brief デバイスIDを検証するマクロ。
 * @param デバイスディスクリプタ
 * @return デバイスIDが不正の場合は真（非0）、正常の場合は偽（0）を返す。
 */
#define isbaddev(f) (((f) < 0) | ((f) >= NDEVS))