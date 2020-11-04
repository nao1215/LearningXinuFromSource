/**
 * @file arp.h
 * @brief ARPのパケットフォーマットやキャッシュに関する定義
 * @details ARP(Address Resolution Protocolは、IPアドレスからEthernetのMACアドレスの情報を得られるプロトコル
 */

//! EthernetのMACアドレスサイズ
#define ARP_HALEN 6
//! IPアドレスサイズ
#define ARP_PALEN 4
//! Ethernetハードウェアタイプ
#define ARP_HTYPE 1
//! IPプロトコルタイプ
#define ARP_PTYPE 0x0800
//! リクエストオペコード
#define ARP_OP_REQ 1
//! リプライオペコード
#define ARP_OP_RPLY 2
//! キャシュ中のエントリ数
#define ARP_SIZ 16
//! ARPリクエストのリトライ回数
#define ARP_RETRY 3
//! [ms]毎のリトライタイマ
#define ARP_TIMEOUT 300 /* Retry timer in milliseconds	*/

//! ARPキャッシュエントリ状態：スロットが未使用
#define AR_FREE 0
//! ARPキャッシュエントリ状態：解決中
#define AR_PENDING 1
//! ARPキャッシュエントリ状態：エントリが正常
#define AR_RESOLVED 2

#pragma pack(2)
/**
 * @struct arppacket
 * @brief IP&Ethernet用のARPパケットフォーマット
 * @note 構造体メンバが2Byte境界を超えないよう、#pragma pack(2)で制御している
 */
struct arppacket
{
	//! Ethernet転送先のMACアドレス
	byte arp_ethdst[ETH_ADDR_LEN];
	//! Ethernet送信元のMACアドレス
	byte arp_ethsrc[ETH_ADDR_LEN];
	//! Ethernetタイプ領域
	uint16 arp_ethtype;
	//! ARPハードウェアタイプ
	uint16 arp_htype;
	//! ARPプロトコルタイプ
	uint16 arp_ptype;
	//! ARPハードウェアアドレス長さ
	byte arp_hlen;
	//! ARPプロトコルアドレス長さ
	byte arp_plen;
	//! ARPオペレーション
	uint16 arp_op;
	//! ARP送信者のEthernetアドレス
	byte arp_sndha[ARP_HALEN];
	//! ARP送信者のIPアドレス
	uint32 arp_sndpa;
	//! ARPターゲットのEthernetアドレス
	byte arp_tarha[ARP_HALEN];
	//! ARPターゲットのIPアドレス
	uint32 arp_tarpa;
};
#pragma pack()

/**
 * @struct arpentry
 * @brief ARPキャッシュエントリ
 */
struct arpentry
{
	//! エントリの状態
	int32 arstate;
	//! エントリのIPアドレス
	uint32 arpaddr;
	//! 待機中プロセスか-1
	pid32 arpid;
	//! エントリのEthernetアドレス
	byte arhaddr[ARP_HALEN];
};

//! ARPキャッシュエントリテーブル
extern struct arpentry arpcache[];
