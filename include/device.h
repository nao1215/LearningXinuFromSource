/**
 * @file device.h
 * @brief 「デバイス名の最大長」と「デバイスID検証マクロ」を提供する。
 */

//!  デバイス名の最大サイズ
#define DEVNAMLEN 16

/**
 * @def isbaddev()
 * @brief デバイスIDを検証するマクロ。
 * @param[in] f デバイスディスクリプタ
 * @return デバイスIDが不正の場合はtrue、正常の場合はfalseを返す。
 */
#define isbaddev(f) (((f) < 0) | ((f) >= NDEVS))
