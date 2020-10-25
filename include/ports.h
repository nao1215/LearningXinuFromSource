/**
 * @file ports.h
 * @brief ポートを用いたメッセージ送受信に用いる構造体や定数の宣言
 */

//! ポートの最大数
#define NPORTS 30
//! システム内の最大メッセージ数
#define PT_MSGS 100
//! ポートがFREE状態
#define PT_FREE 1
//! ポートが削除された、もしくはリセットされる
#define PT_LIMBO 2
//! ポートが割り当てられた
#define PT_ALLOC 3

/**
 * @struct ptnode
 * @brief メッセージリストのノード
 */
struct ptnode
{
	//! ワンワードのメッセージ
	uint32 ptmsg;
	//! メッセージリストの次のノードへのポインタ
	struct ptnode *ptnext;
};

/**
 * @struct ptentry
 * @brief ポートテーブルエントリ
 */
struct ptentry
{
	//! 送信側セマフォ
	sid32 ptssem;
	//! 受信側セマフォ
	sid32 ptrsem;
	//! ポート状態（FREE／LIMBO／ALLOC）
	uint16 ptstate;
	//! ポートに挿入できる最大メッセージ数
	uint16 ptmaxcnt;
	//! 生成時に変更されたシーケンス
	int32 ptseq;
	//! メッセージリストの先頭ポインタ
	struct ptnode *pthead;
	//! メッセージリストの末尾ポインタ
	struct ptnode *pttail;
};

//! フリーノードリストのextern宣言
extern struct ptnode *ptfree;
//! ポートテーブルエントリのextern宣言
extern struct ptentry porttab[];
//! 空きスロットを探す際に試みる次のポートID
extern int32 ptnextid;

/**
 * @def isbadport(portid)
 * @brief ポートIDが不正値かどうかを確認する。
 * @param[in] portid ポートID
 * @return ポートIDが負の値もしくはポートの最大数を超えている場合はtrue、それ以外はfalseを返す。
 */
#define isbadport(portid) ((portid) < 0 || (portid) >= NPORTS)
