/**
 * @file name.h
 * @brief 名前空間（ネームスペースマッピング）に関する宣言
 */

//! プレフィックス文字列の最大サイズ
#define NM_PRELEN 64
//! 置換（1個）の最大サイズ
#define NM_REPLLEN 96
//! ファイル名の最大サイズ
#define NM_MAXLEN 256
//! プレフィックス定義の数
#define NNAMES 40

/**
 * @struct nmentry
 * @brief  全ての名前マッピングを定義する名前プレフィックステーブルの定義（ネームテーブルエントリ）
 */
struct nmentry
{
	//! NULL終端のプレフィックス
	char nprefix[NM_PRELEN];
	//! NULL終端置換
	char nreplace[NM_REPLLEN];
	//! プレフィックス用のデバイスディスクリプタ
	did32 ndevice;
};

//! 名前マッピングのテーブル
extern struct nmentry nametab[];
//! 割り当てられたネームテーブルエントリの数
extern int32 nnames;