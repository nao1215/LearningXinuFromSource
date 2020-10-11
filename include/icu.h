/**
 *  @file icu.h
 *  @brief Input Capture UnitのI/Oポートアドレス、レジスタ、割り込み終了を定義する。
 */

//! I/Oポートアドレス（8259A #1）
#define ICU1 0x20
//! I/Oポートアドレス（8258A #2）
#define ICU2 0xA0
//! オペレーションコマンドレジスタ（Operation Command Register）
#define OCR ICU1
//! 割り込みマスクレジスタ（Interrupt Mask Register）
#define IMR (ICU1 + 1)
//! 非特定の割り込み終了
#define EOI 0x20
