
/**
 * @file resched.h
 * @brief 遅延スケジューリングに使用する宣言と定数。
 */

//! 遅延リスケジューリングの開始
#define DEFER_START 1
//! 遅延リスケジューリングの停止
#define DEFER_STOP 2

/**
 * @struct defer
 * @brief 遅延リスケジューリングに関連する項目を集約した構造体
 */
struct defer
{
	//! 未処理の延期プロセスの数
	int32 ndefers;
	//! 延期中に再スケジューリングが実行されたかどうか
	bool8 attempt;
};

//! defer構造体のextern宣言
extern struct defer Defer;
