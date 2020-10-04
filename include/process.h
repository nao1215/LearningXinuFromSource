/**
 * @file process.h
 * @brief プロセスに関する情報（プロセスの数、プロセス状態、プロセステーブル等）を定義する。
 * @details XINUは組込みシステムで用いられる事を前提として、設計されている。<br>
 * 例えば、組み込み用途に耐えうるメモリ使用量とするために、XINUはリンクリストを用いた<br>
 * プロセス管理を採用していない。ここでのリンクリストとは、ノードを連結したデータ構造である。<br>
 * [ノード]<br>
 *  ・データオブジェクト（例：プロセス、キー値）<br>
 *  ・一つ前のノートへのポインタ<br>
 *  ・一つ後のノートへのポインタ<br>
 *<br>
 * [（双方向）リンクリスト]<br>
 *  ・最先頭ノード <-> ノード <-> ノード <-> … <-> 最後方ノード<br>
 *<br>
 * 上記のようなリンクリストは、Linux Kernel等で用いられている。<br>
 * しかし、XINUはプロセス数がデフォルト8個と少ないため、<br>
 *  ・ノードを連続したメモリ領域に配置<br>
 *  ・ノードからプロセスIDを省略（配列のインデックス = プロセスIDとみなす）<br>
 * という形で設計する事によって、使用するメモリを減らしている。<br>
 *  （ポインタサイズの4byteですら、削減している）
 */

/**
 * プロセス数（=NPROC）は、条件付きコンパイルによって、動的にそのサイズを変更できる<br>
 * （process.hの修正が不要となる）。
 */
#ifndef NPROC
//! デフォルトのプロセス数。
#define NPROC 8
#endif

//! プロセステーブルエントリが使用されていない状態。
#define PR_FREE 0
//! プロセスが現在動作中。
#define PR_CURR 1
//! プロセスがREADYキューにいる状態。
#define PR_READY 2
//! プロセスがメッセージを待っている状態。
#define PR_RECV 3
//! プロセスが休眠中の状態。
#define PR_SLEEP 4
//! プロセスがサスペンド（休止）させられた状態。
#define PR_SUSP 5
//! プロセスがセマフォキューにいる状態。
#define PR_WAIT 6
//! プロセスがタイムアウトありで受信中の状態。
#define PR_RECTIM 7

//! プロセス名の長さ
#define PNMLEN 16
//! NULLプロセスのID
#define NULLPROC 0

//! 初期プロセススタックサイズ
#define INITSTK 65536
//! 初期プロセス優先度
#define INITPRIO 20
//! プロセスが戻るアドレス。
#define INITRET userret

/**
 * @def isbadpid(x)
 * @brief プロセスIDを検証する。割り込みが無効になっている事を想定している。
 * @param[in] x プロセスID。
 * @details  プロセスIDがプロセスID範囲内に収まっていない、もしくはプロセステーブルで<br>
 * 当該プロセスIDが未使用状態であれば、そのプロセスIDは不正とみなす。
 * @return プロセスIDが不正の場合≠0、正常の場合は＝0を返す。
 */
#define isbadpid(x) (((pid32)(x) < 0) ||      \
					 ((pid32)(x) >= NPROC) || \
					 (proctab[(x)].prstate == PR_FREE))

/**
 * 一つのプロセスが開く事ができるデバイスディスクリプタの数。
 * procent構造体を4N Bytesにするため、奇数でなければいけない。
 */
#define NDESC 5 /* must be odd to make procent 4N bytes	*/

/**
 * @struct procent
 * @brief プロセステーブル（32bitsの倍数）。
 */
struct procent
{
	//! プロセス状態（PR_CURR, ..., etc）。
	uint16 prstate;
	//! プロセスの優先度。
	pri16 prprio;
	//! 保存されたスタックポインタ。
	char *prstkptr;
	//! ランタイムスタックの基点。
	char *prstkbase;
	//! Bytesで表されたスタックの長さ。
	uint32 prstklen;
	//! プロセス名。
	char prname[PNMLEN];
	//! プロセスが待機しているセマフォ。
	sid32 prsem;
	//! このプロセスを作成したプロセスID（親プロセスID）。
	pid32 prparent;
	//! このプロセスに送信されたメッセージ。
	umsg32 prmsg;
	//! 有効（Valid）メッセージの場合、非0となる。
	bool8 prhasmsg;
	//! プロセス用のデバイスディスクリプタ
	int16 prdesc[NDESC];
};

//! プロセススタックの最上位に配置するマーカ（オーバフロー検出に用いる）
#define STACKMAGIC 0x0A0AAAA9

//! プロセステーブル。
extern struct procent proctab[];
//! 現在アクティブのプロセス。
extern int32 prcount;
//! 現在実行中のプロセス。
extern pid32 currpid;