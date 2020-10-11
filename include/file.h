/**
 * @file file.h
 * @brief リモートもしくはローカルのファイルシステムに関する共通の定義。
 * @details ファイルモードのbits、ファイルコントロール機能を定義している。
 */

//! 読み込み権限を付与するbit。
#define F_MODE_R 0x01
//! 書き込み権限を付与するbit。
#define F_MODE_W 0x02
//! Read/Write bits用のマスク。
#define F_MODE_RW 0x03
//! "New"モードのbit（New/Oldモードbitは互いに排他である）。
#define F_MODE_N 0x04
//! "New"モードのbit（New/Oldモードbitは互いに排他である）。
#define F_MODE_O 0x08
//! "New"／"Old"モード用のマスク。
#define F_MODE_NO 0x0C /* Mask for "n" and "o" bits	*/

//! ファイルを削除する。
#define F_CTL_DEL 1
//! ファイルを切り捨てる。
#define F_CTL_TRUNC 2
//! ディレクトリを作成する。
#define F_CTL_MKDIR 3
//! ディレクトリを削除する。
#define F_CTL_RMDIR 4
//! ファイルサイズを取得する。
#define F_CTL_SIZE 5
