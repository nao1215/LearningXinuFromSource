/**
 * @file am335x_watchdog.h
 * @brief AM335X SoCのWatchdogタイマの制御／状態レジスタに関する定義
 */

/**
 * @struct watchdog_csreg
 * @brief Watchdog CSREG（制御／状態）レジスタ操作用の構造体
 */
struct watchdog_csreg
{
	//! 識別レジスタ
	volatile uint32 widr;
	//! 予約領域その1
	volatile uint32 res1[3];
	//! システム制御レジスタ
	volatile uint32 wdsc;
	//! ステータスレジスタ
	volatile uint32 wdst;
	//! 割り込みステータスレジスタ
	volatile uint32 wisr;
	//! 割り込み許可レジスタ
	volatile uint32 wier;
	//! 予約領域その2
	volatile uint32 res2;
	//! 制御レジスタ
	volatile uint32 wclr;
	//! カウンタレジスタ
	volatile uint32 wcrr;
	//! ロードレジスタ
	volatile uint32 wldr;
	//! トリガーレジスタ
	volatile uint32 wtgr;
	//! ポストBitレジスタの書き込み
	volatile uint32 wwps;
	//! 予約領域その3
	volatile uint32 res3[3];
	//! 遅延制御レジスタ
	volatile uint32 wdly;
	//! 開始／終了レジスタ
	volatile uint32 wspr;
	//! 予約領域その4
	volatile uint32 res4[2];
	//! Raw割り込み開始レジスタ
	volatile uint32 wirqstatraw;
	//! 割り込みステータスレジスタ
	volatile uint32 wirqstat;
	//! 割り込み許可セットレジスタ
	volatile uint32 wirqenset;
	//! 割り込み許可コントロールレジスタ
	volatile uint32 wirqenclr;
};

//! Watchdogタイマに割り当てられたアドレス
#define WDTADDR 0x44E35000
