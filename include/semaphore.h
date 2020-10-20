/**
 * @file semaphore.h
 * @brief セマフォ（セマフォ数、状態、セマフォテーブル）に関する宣言およびマクロ定義
 */
#ifndef NSEM
//! セマフォ数が未定義の場合は、セマフォ数を120個とする。
#define NSEM 120
#endif

//! セマフォテーブルエントリが利用可能
#define S_FREE 0
//! セマフォテーブルエントリが利用中
#define S_USED 1

/**
 * @struct sentry
 * @brief セマフォテーブルエントリであり、本構造体の配列（長さNSEM）が静的に確保される。
 */
struct sentry
{
	//! エントリ状態が利用可能（S_FREE）か、利用中（S_USED）かを表す。
	byte sstate;
	//! セマフォカウント（負の値(-N)の場合は、キューにN個の待機プロセスがある。それ以外はキューが空である）
	int32 scount;
	//! セマフォ待機中プロセスのキュー
	qid16 squeue;
};

//! セマフォテーブルエントリのextern宣言
extern struct sentry semtab[];

/**
 * @def isbadsem()
 * @brief セマフォIDが不適切かどうかを確認する。
 * @param[in] s チェック対象のセマフォID（セマフォテーブルエントリのインデックス）
 * @return セマフォIDが負の値もしくは作成可能なセマフォ総数（NSEM）を超えている場合はtrueを返し、<br>
 * それ以外の場合はfalseを返す。
 * @note セマフォテーブルエントリは静的に割り当てられた配列のため、その操作には配列のインデックスを用いる。
 */
#define isbadsem(s) ((int32)(s) < 0 || (s) >= NSEM)
