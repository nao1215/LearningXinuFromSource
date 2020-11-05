/**
 * @file clock.h
 * @brief クロックに関する定義
 */

//! 起動してからの現在の時間[s]
extern uint32 clktime;
//! 最後のクロックチックからのミリ秒
extern uint32 count1000;
//! スリープ中のプロセスキュー
extern qid16 sleepq;
//! スリープキューが空ではない場合、ゼロ以外
extern int32 slnonempty;
//! スリープキューの最初のアイテムのキーへのポインタ
extern int32 *sltop;
//! プリエンプションカウンタ
extern uint32 preempt;

/**
 * @struct am335x_timer1ms
 * @brief AM335X SOCのタイマー（1[ms]）
 */
struct am335x_timer1ms
{
	//! 識別レジスタ
	uint32 tidr;
	//! 予約領域その1
	uint32 res1[3];
	//! OCPインターフェースレジスタ
	uint32 tiocp_cfg;
	//! ステータスレジスタ
	uint32 tistat;
	//! 割り込みステータスレジスタ
	uint32 tisr;
	//! 割り込み許可レジスタ
	uint32 tier;
	//! Wakeup許可レジスタ
	uint32 twer;
	//! オプション機能
	uint32 tclr;
	//! 内部カウント値
	uint32 tcrr;
	//! タイマー読み込み値
	uint32 tldr;
	//! トリガレジスタ
	uint32 ttgr;
	//! 書き込みポスティングレジスタ
	uint32 twps;
	//! マッチレジスタ
	uint32 tmar;
	//! キャプチャレジスタその1
	uint32 tcar1;
	//! 同期インターフェース制御
	uint32 tsicr;
	//! キャプチャレジスタその2
	uint32 tcar2;
	//! ポジティブインクリメントレジスタ
	uint32 tpir;
	//! ネガティブインクリメントレジスタ
	uint32 tnir;
	//! 1[ms]制御レジスタ
	uint32 tcvr;
	//! オーバーフローマスクレジスタ
	uint32 tocr;
	//! オーバーフローのNo.
	uint32 towr;
};

//! 1[ms]タイマーのアドレス
#define AM335X_TIMER1MS_ADDR 0x44E31000
//! 1[ms]タイマーの割り込み番号
#define AM335X_TIMER1MS_IRQ 67
//! 1[ms]タイマーのソフトリセットコンフィグ
#define AM335X_TIMER1MS_TIOCP_CFG_SOFTRESET 0x00000002
//! 1[ms]タイマーのリセット完了状態
#define AM335X_TIMER1MS_TISTAT_RESETDONE 0x00000001
//! TCRRとTMARの比較を行うフラグ
#define AM335X_TIMER1MS_TISR_MAT_IT_FLAG 0x00000001
//! TCRRオーバーフロー発生時の設定
#define AM335X_TIMER1MS_TISR_OVF_IT_FLAG 0x00000002
//! 外部ピンPIEVENTCAPTから検出された正しい極性の外部パルス遷移を示す
#define AM335X_TIMER1MS_TISR_TCAR_IT_FLAG 0x00000004
//! マッチ割り込みの許可
#define AM335X_TIMER1MS_TIER_MAT_IT_ENA 0x00000001
//! オーバーフロー割り込みの許可
#define AM335X_TIMER1MS_TIER_OVF_IT_ENA 0x00000002
//! キャプチャ割り込みの許可
#define AM335X_TIMER1MS_TIER_TCAR_IT_ENA 0x00000004
//! Start/Stopタイマ制御
#define AM335X_TIMER1MS_TCLR_ST 0x00000001
//! 自動リロードモード
#define AM335X_TIMER1MS_TCLR_AR 0x00000002
//! 1[ms]タイマーのクロック制御アドレス
#define AM335X_TIMER1MS_CLKCTRL_ADDR 0x44E004C4
//! 1[ms]タイマーのクロック制御の許可
#define AM335X_TIMER1MS_CLKCTRL_EN 0x00000002
