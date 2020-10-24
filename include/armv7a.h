/**
 * @file armv7a.h
 * @brief ARMv7-A命令セット（Cortex-A8）に関する宣言。
 * @note CPSR Bits、Coprocessor c1、例外ベクタ、ヒープメモリに関する宣言がある。
 */

//! CPSR：Impreciseデータアボート禁止
#define ARMV7A_CPSR_A 0x00000100
//! CPSR：IRQ割り込み禁止
#define ARMV7A_CPSR_I 0x00000080
//! CPSR：FIQ割り込み禁止
#define ARMV7A_CPSR_F 0x00000040
//! CPSR：プロセッサモードマスク
#define ARMV7A_CPSR_MM 0x0000001F
//! CPSR：プロセッサモード = User
#define ARMV7A_CPSR_USR 0x00000010
//! CPSR：プロセッサモード = FIQ
#define ARMV7A_CPSR_FIQ 0x00000011
//! CPSR：プロセッサモード = IRQ
#define ARMV7A_CPSR_IRQ 0x00000012
//! CPSR：プロセッサモード =  Supervisor
#define ARMV7A_CPSR_SPR 0x00000013
//! CPSR：プロセッサモード =  Abort
#define ARMV7A_CPSR_ABT 0x00000017
//! CPSR：プロセッサモード = 未定義
#define ARMV7A_CPSR_UND 0x0000001B
//! CPSR：プロセッサモード = System
#define ARMV7A_CPSR_SYS 0x0000001F
//! CPSR：プロセッサモード = セキュアモニタ
#define ARMv7A_CPSR_SCM 0x00000016

//! Coprocessor c1 - 制御レジスタBits：例外ベースアドレス制御
#define ARMV7A_C1CTL_V 0x00002000
//! Coprocessor c1 - 制御レジスタBits：命令キャッシュの有効化
#define ARMV7A_C1CTL_I 0x00001000
//! Coprocessor c1 - 制御レジスタBits：データキャッシュの有効化
#define ARMV7A_C1CTL_C 0x00000004
//! Coprocessor c1 - 制御レジスタBits：Strict alignment（厳密なアライメント）の有効化
#define ARMV7A_C1CTL_A 0x00000002
//! Coprocessor c1 - 制御レジスタBits：MMUの有効化
#define ARMV7A_C1CTL_M 0x00000001

//! 例外ベクタの開始アドレス
#define ARMV7A_EV_START 0x4030CE00
//! 例外ベクタの終了アドレス
#define ARMV7A_EV_END 0x4030CE20
//! 例外ハンドラの開始アドレス
#define ARMV7A_EH_START 0x4030CE24
//! 例外ハンドラの終了アドレス
#define ARMV7A_EH_END 0x4030CE40
//! IRQハンドラアドレス
#define ARMV7A_IRQH_ADDR 0x4030CE38

//! 0x80000000から始まる512MB RAMの最終アドレス
#define MAXADDR 0xA0000000
