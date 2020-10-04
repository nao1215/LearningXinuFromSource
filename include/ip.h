/**
 *  @file ip.h
 *  @brief Internet Protocol version 4 (IPv4)に関する定数。
 */

//! IPローカルブロードキャストアドレス。
#define IP_BCAST 0xffffffff
//! 「このホスト」のソースIPアドレス。
#define IP_THIS 0xffffffff
//! 全てゼロのIPアドレス。
#define IP_ALLZEROS 0x00000000

//! IP向けのICMPプロトコルタイプ
#define IP_ICMP 1
//! IP向けのUDPプロトコルタイプ
#define IP_UDP 17

//! IPアドレスのバイト数
#define IP_ASIZE 4
//! IPヘッダのバイト数。
#define IP_HDR_LEN 20
//! 「IPバージョン」および「HDRの長さ」
#define IP_VH 0x45
//! IPアウトプットキューのサイズ
#define IP_OQSIZ 8

/* Queue of outgoing IP packets waiting for ipout process */

/**
 * @struct iqentry
 * @brief ipout（IP送信）プロセスを待機している送信用IPパケットのキュー
 */
struct iqentry
{
	//! 次に送信するパケットのインデックス
	int32 iqhead;
	//! 次の空きスロットのインデックス。
	int32 iqtail;
	//! パケット（pkts）をカウントするセマフォ
	sid32 iqsem;
	//! 循環パケットキュー
	struct netpacket *iqbuf[IP_OQSIZ];
};

//! ネットワーク送信キュー
extern struct iqentry ipoqueue;
