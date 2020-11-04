/**
 * @file am335x_control.h
 * @brief AM335X SoCのThe PAD制御レジスタに関する定義
 * @details PAD制御レジスタ（32bit）は、各I/Oの信号多重化およびその他の側面を制御する。
 */
//! プルアップダウンが有効
#define AM335X_PADCTL_PEN 0x00000008
//! プルアップが選択された
#define AM335X_PADCTL_PUP 0x00000010
//! プルダウンが選択された
#define AM335X_PADCTL_PDN 0x00000000
//! 入力モードもしくは出力モード
#define AM335X_PADCTL_RXTX 0x00000020
//! 出力限定モード
#define AM335X_PADCTL_TX 0x00000000
//! スルーコントロールが遅い状態
#define AM335X_PADCTL_SS 0x00000040
//! スルーコントロールが速い状態
#define AM335X_PADCTL_SF 0x00000000
/**
 * @def am335x_padctl()
 * @brief 引数で指定されたアドレスに値を代入する。
 * @param[in,out] addr 代入先のアドレス
 * @param[in] val 代入する値（OR条件で指定されたBit値）
 */
#define am335x_padctl(addr, val) (*((uint32 *)(addr))) = (val)
