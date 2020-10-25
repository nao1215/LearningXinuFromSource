/**
 * @file am335x_eth.h
 * @brief AM335X SoCのEthernetデバイスに関する定義。
 */

/**
 * @struct eth_a_ale
 * @brief Address Lookup Engine(ALE)レジスタ用の構造体
 */
struct eth_a_ale
{
	//! ALE ID/Versionレジスタ
	uint32 idver;
	//! 予約1
	uint32 res1;
	//! ALE制御レジスタ
	uint32 ctrl;
	//! 予約2
	uint32 res2;
	//! ALEプレスケールレジスタ
	uint32 prescale;
	//! 予約3
	uint32 res3;
	//! ALE不明なVLANレジスタ
	uint32 unknown_vlan;
	//! 予約4
	uint32 res4;
	//! ALEテーブル制御
	uint32 tblctl;
	//! 予約5
	uint32 res5[4];
	//! ALEテーブルワード2レジスタ
	uint32 tblw2;
	//! ALEテーブルワード1レジスタ
	uint32 tblw1;
	//! ALEテーブルワード0レジスタ
	uint32 tblw0;
	//! ALEポート0〜5制御レジスタ
	uint32 portctl[6];
};

//! Address Lookup Engine(ALE)を有効化する
#define ETH_AM335X_ALECTL_EN 0x80000000
//! Address Lookup Engine(ALE)制御をBypassモードとする
#define ETH_AM335X_ALECTL_BY 0x00000010
//! Address Lookup Engine(ALE)制御をポートフォワード状態とする
#define ETH_AM335X_ALEPCTL_FWD 0x00000003

/**
 * @struct eth_a_cpdma
 * @brief Cryptographic Processor RAM DMA(CPDMA、暗号化DMA)レジスタ用の構造体
 */
struct eth_a_cpdma
{
	//! TX(送信) ID/Versionレジスタ
	uint32 tx_idver;
	//! TX(送信) 制御レジスタ
	uint32 tx_ctrl;
	//! TX(送信) 終了レジスタ
	uint32 tx_teardown;
	//! 予約0
	uint32 res0;
	//! RX(受信) ID/Versionレジスタ
	uint32 rx_idver;
	//! RX(受信) 制御レジスタ
	uint32 rx_ctrl;
	//! RX(受信) 終了レジスタ
	uint32 rx_teardown;
	//! CPDMAソフトリセットレジスタ
	uint32 reset;
	//! CPDMA制御レジスタ
	uint32 dmactrl;
	//! CPDMAステータスレジスタ
	uint32 dmastat;
	//! RX(受信) バッファオフセット
	uint32 rx_buf_off;
	//! CPDMAエミュレージョン制御
	uint32 emctrl;
	//! TX(送信)優先度0〜7レジスタ
	uint32 tx_pri_rate[8];
	//! 予約1
	byte res1[48];
	//! TX(送信)割り込みステータスレジスタ（RAW値）
	uint32 tx_intstat_raw;
	//! TX(送信)割り込みステータスレジスタ（マスク値）
	uint32 tx_intstat_masked;
	//! TX(送信)割り込みマスクセットレジスタ
	uint32 tx_intmask_set;
	//! TX(送信)割り込みマスククリアレジスタ
	uint32 tx_intmask_clear;
	//! CPDMA入力ベクタ（Read Only）
	uint32 in_vector;
	//! CPDMA割り込み終了ベクタ
	uint32 eoi_vector;
	//! 予約2
	byte res2[8];
	//! RX(受信)割り込みステータスレジスタ（RAW値）
	uint32 rx_intstat_raw;
	//! RX(受信)割り込みステータスレジスタ（マスク値）
	uint32 rx_intstat_masked;
	//! RX(受信)割り込みマスクセットレジスタ
	uint32 rx_intmask_set;
	//! RX(受信)割り込みマスククリアレジスタ
	uint32 rx_intmask_clear;
	//! CPDMA割り込みステータスレジスタ（RAW値）
	uint32 dma_intstat_raw;
	//! CPDMA割り込みステータスレジスタ（マスク値）
	uint32 dma_intstat_masket;
	//! CPDMA割り込みマスクセットレジスタ
	uint32 dma_intmask_set;
	//! CPDMA割り込みマスククリアレジスタ
	uint32 dma_intmask_clear;
	//! RX(受信)ペンディング閾値レジスタ チャネル0〜7
	uint32 rx_pendthresh[8];
	//! RX(受信)フリーバッファレジスタ チャネル0〜7
	uint32 rx_freebuffer[8];
};

/**
 * @struct eth_a_stateram
 * @brief CPDMA_STATERAMレジスタ用の構造体
 */
struct eth_a_stateram
{
	//! TX(送信) チャネル0〜7 先頭ディスクリプタへのポインタ
	uint32 tx_hdp[8];
	//! RX(受信) チャネル0〜7 先頭ディスクリプタへのポインタ
	uint32 rx_hdp[8];
	//! TX(送信) チャネル0〜7 完了ポインタレジスタ
	uint32 tx_cp[8];
	//! RX(受信) チャネル0〜7 完了ポインタレジスタ
	uint32 rx_cp[8];
};

/**
 * @struct eth_a_sl
 * @brief CPSW_SLレジスタ用の構造体
 */
struct eth_a_sl
{
	//! SL ID／Versionレジスタ
	uint32 idver;
	//! DMAC制御レジスタ
	uint32 macctrl;
	//! DMAC状態レジスタ
	uint32 macstat;
	//! SLソフトリセットレジスタ
	uint32 reset;
	//! RX(受信)最大長レジスタ
	uint32 rx_maxlen;
	//! バックオフテストレジスタ
	uint32 bofftest;
	//! RX(受信)ポーズタイマーレジスタ
	uint32 rx_pause;
	//! TX(送信)ポーズタイマーレジスタ
	uint32 tx_pause;
	//! エミュレーション制御レジスタ
	uint32 emctrl;
	//! RX(受信)パケット優先度0〜7のマッピングレジスタ
	uint32 rx_pri_map;
	//! 内部パケットギャップTX(送信)レジスタ
	uint32 tx_gap;
};

//! 全二重通信
#define ETH_AM335X_SLCTL_FD 0x00000001
//! ループバック
#define ETH_AM335X_SLCTL_LB 0x00000002
//! 受信／送信の有効化
#define ETH_AM335X_SLCTL_EN 0x00000020
//! ギガビットモード
#define ETH_AM335X_SLCTL_GIG 0x00000080

/**
 * @struct eth_a_ss
 * @brief CPSW_SSレジスタ用の構造体
 */
struct eth_a_ss
{
	//! SS ID／Versionレジスタ
	uint32 idver;
	//! スイッチ制御レジスタ
	uint32 ctrl;
	//! SSソフトリセットレジスタ
	uint32 reset;
	//! 統計ポート有効化レジスタ
	uint32 stat_port_en;
	//! TX(送信)優先度タイプレジスタ
	uint32 ptype;
	//! ソフトアイドル
	uint32 soft_idle;
	//! スループット率
	uint32 thru_rate;
	//! CPGMAC_SL Short GAP閾値
	uint32 gap_thresh;
	//! TX(送信)開始ワード
	uint32 tx_start_wds;
	//! フロー制御
	uint32 flow_ctrl;
	//! LTYPE1とLTYPE2レジスタ
	uint32 vlan_type;
	//! VLAN LTYPE1とLTYPE2レジスタ
	uint32 ts_ltype;
	//! DLR LTYPEレジスタ
	uint32 dlr_ltype;
};

/**
 * @struct eth_a_wr
 * @brief CPSW_WRレジスタ用の構造体
 */
struct eth_a_wr
{
	//! WR ID／Versionレジスタ
	uint32 idver;
	//! WRソフトリセットレジスタ
	uint32 reset;
	//! WR制御レジスタ
	uint32 ctrl;
	//! サブシステム割り込み制御レジスタ
	uint32 int_ctrl;
	//! サブシステム コア0 RX(受信)閾値 割り込み許可レジスタ
	uint32 c0_rx_thresh_en;
	//! サブシステム コア0 RX(受信)割り込み許可レジスタ
	uint32 c0_rx_en;
	//! サブシステム コア0 TX(送信)割り込み許可レジスタ
	uint32 c0_tx_en;
	//!  サブシステム コア0 MISC割り込み許可レジスタ
	uint32 c0_misc_en;
	//! 予約1
	uint32 res1[8];
	//! サブシステム コア0 RX(受信)閾値 割り込みマスク状態レジスタ
	uint32 c0_rx_thresh_stat;
	//! サブシステム コア0 RX(受信)割り込みマスク状態レジスタ
	uint32 c0_rx_stat;
	//! サブシステム コア0 TX(送信)割り込みマスク状態レジスタ
	uint32 c0_tx_stat;
	//! サブシステム コア0 MISC割り込みマスク状態レジスタ
	uint32 c0_misc_stat;
};

/**
 * @struct eth_a_mdio
 * @brief Management Data Input/Output(MDIO)レジスタ用の構造体
 */
struct eth_a_mdio
{
	//! MDIO Versionレジスタ
	uint32 ver;
	//! MDIO制御レジスタ
	uint32 ctrl;
	//! PHY Alive状態レジスタ
	uint32 alive;
	//! PHYリンク状態レジスタ
	uint32 link;
	//! MDIOリンク状態変更割り込みレジスタ
	uint32 linkintraw;
	//! MDIOリンクステータス変更割り込みレジスタ（マスク値）
	uint32 linkintmasked;
	//! 予約1
	byte res1[8];
	//! MDIO ユーザコマンド完了割り込みレジスタ（RAW値）
	uint32 userintraw;
	//! MDIO ユーザコマンド完了割り込みレジスタ（マスク値）
	uint32 userintmasked;
	//! MDIO ユーザコマンド完了割り込みマスクセットレジスタ
	uint32 userintmaskset;
	//! MDIOユーザ割り込みマスククリアレジスタ
	uint32 userintmaskclr;
	//! 予約2
	byte res2[80];
	//! MDIO ユーザアクセスレジスタ0
	uint32 useraccess0;
	//! MDIO ユーザPHY選択レジスタ0
	uint32 userphysel0;
	//! MDIO ユーザアクセスレジスタ1
	uint32 useraccess1;
	//! MDIO ユーザPHY選択レジスタ1
	uint32 userphysel1;
};

//! Management Data Input/Output(MDIO)制御を有効化
#define ETH_AM335X_MDIOCTL_EN 0x40000000
//! 実行するManagement Data Input/Output(MDIO)のアクセス
#define ETH_AM335X_MDIOUA_GO 0x80000000
//! Management Data Input/Output(MDIO) 書き込みアクセス
#define ETH_AM335X_MDIOUA_WR 0x40000000
//! Management Data Input/Output(MDIO) 読み込み確認応答(Ack)
#define ETH_AM335X_MDIOUA_ACK 0x20000000
//! Management Data Input/Output(MDIO)データマスク
#define ETH_AM335X_MDIOUA_DM 0x0000ffff

/**
 * @struct eth_a_csreg
 * @brief Ethernet subsystemレジスタ構造体
 */
struct eth_a_csreg
{
	//! CPSW_ALEレジスタ
	volatile struct eth_a_ale *ale;
	//! CPSW_CPDMAレジスタ
	volatile struct eth_a_cpdma *cpdma;
	//! CPSW_STATERANレジスタ
	volatile struct eth_a_stateram *stateram;
	//! CPSW_SLレジスタ
	volatile struct eth_a_sl *sl;
	//! CPSW_SSレジスタ
	volatile struct eth_a_ss *ss;
	//! CPSW_WRレジスタ
	volatile struct eth_a_wr *wr;
	//! MDIOレジスタ
	volatile struct eth_a_mdio *mdio;
};

/**
 * @struct eth_a_rx_desc
 * @brief DMA RX(受信)ディスクリプタ
 */
struct eth_a_rx_desc
{
	//! 次のDMA RX(受信)ディスクリプタ
	struct eth_a_rx_desc *next;
	//! DMAバッファ
	uint32 buffer;
	//! DMAバッファの長さ
	uint16 buflen;
	//! DMAバッファのオフセット
	uint16 bufoff;
	//! DMAパケットの長さ
	uint16 packlen;
	//! DMA状態
	uint16 stat;
};

//! RX(受信)パケットの開始
#define ETH_AM335X_RDS_SOP 0x8000
//! RX(受信)パケットの終了
#define ETH_AM335X_RDS_EOP 0x4000
//! DMAが所持するディスクリプタ
#define ETH_AM335X_RDS_OWN 0x2000
//! 不明
#define ETH_AM335X_RDS_EOQ 0x1000
//! RX(受信)リングバッファサイズ
#define ETH_AM335X_RX_RING_SIZE 32

/**
 * @struct eth_a_tx_desc
 * @brief DMA TX(送信)ディスクリプタ
 */
struct eth_a_tx_desc
{
	//! 次のDMA TX(受信)ディスクリプタ
	struct eth_a_tx_desc *next;
	//! DMAバッファ
	uint32 buffer;
	//! DMAバッファの長さ
	uint16 buflen;
	//! DMAバッファのオフセット
	uint16 bufoff;
	//! DMAパケットの長さ
	uint16 packlen;
	//! DMA状態
	uint16 stat;
};

//! TX(送信)パケットの開始
#define ETH_AM335X_TDS_SOP 0x8000
//! TX(送信)パケットの終了
#define ETH_AM335X_TDS_EOP 0x4000
//! DMAが所持するディスクリプタ
#define ETH_AM335X_TDS_OWN 0x2000
//! 不明
#define ETH_AM335X_TDS_EOQ 0x1000
//! 不明
#define ETH_AM335X_TDS_DIR 0x0010
//! 不明
#define ETH_AM335X_TDS_P1 0x0001
//! TX(送信)リングバッファサイズ
#define ETH_AM335X_TX_RING_SIZE 16

//! Address Lookup Engine(ALE)の開始アドレス
#define ETH_AM335X_ALE_ADDR 0x4A100D00
//! Cryptographic Processor RAM DMA(CPDMA、暗号化DMA)の開始アドレス
#define ETH_AM335X_CPDMA_ADDR 0x4A100800
//! STATERAMの開始アドレス
#define ETH_AM335X_STATERAM_ADDR 0x4A100A00
//! SL1の開始アドレス
#define ETH_AM335X_SL1_ADDR 0x4A100D80
//! Management Data Input/Output(MDIO)の開始アドレス
#define ETH_AM335X_MDIO_ADDR 0x4A101000
//! SSの開始アドレス
#define ETH_AM335X_SS_ADDR 0x4A100000
//! WRの開始アドレス
#define ETH_AM335X_WR_ADDR 0x4A101200
//! RX(受信)の割り込みベクタ
#define ETH_AM335X_RXINT 41
//! TX(送信)の割り込みベクタ
#define ETH_AM335X_TXINT 42
//! 初期化時のディレイ
#define ETH_AM335X_INIT_DELAY 1000000
