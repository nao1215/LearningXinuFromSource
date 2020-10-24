/**
 * @file bufpool.h
 * @brief バッファプールに関する構造体や定数の宣言。
 */

#ifndef NBPOOLS
//!  バッファプール数の最大数
#define NBPOOLS 20
#endif

#ifndef BP_MAXB
//! 最大バッファサイズ（Byte）
#define BP_MAXB 8192
#endif

//! 最小バッファサイズ（Byte）
#define BP_MINB 8
#ifndef BP_MAXN
//! バッファプールに存在するバッファの最大数
#define BP_MAXN 2048
#endif

/**
 * @struct bpentry
 * @brief バッファプールテーブルエントリ
 */
struct bpentry
{
	//! 次のフリーバッファへのポインタ
	struct bpentry *bpnext;
	//! バッファプールで現在使用可能なバッファをカウントするセマフォ
	sid32 bpsem;
	//! 本バッファプール内のバッファサイズ
	uint32 bpsize;
};

//! バッファプールテーブルのextern宣言
extern struct bpentry buftab[];
//! 割り当てられたバッファプールの現在の数
extern bpid32 nbpools;
