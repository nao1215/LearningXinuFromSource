/**
 * @file kernel.h
 * @brief XINU OSのkernel部分で使用する汎用的な宣言。
 */

//! 符号なし8ビット値（unsigned char）
typedef unsigned char byte;
//! 符号なし8ビット値（unsigned char）
typedef unsigned char uint8;
//! 符号あり32ビット整数（int）
typedef int int32;
//! 符号あり16ビット整数（short）
typedef short int16;
//! 符号なし32ビット整数（unsigned int）
typedef unsigned int uint32;
//! 符号なし16ビット整数（unsigned short）
typedef unsigned short uint16;
//! 符号なし64ビット整数（unsigned long long）
typedef unsigned long long uint64;

//! セマフォID
typedef int32 sid32;
//! キューID
typedef int16 qid16;
//! プロセスID
typedef int32 pid32;
//! デバイスID
typedef int32 did32;
//! プロセス優先度
typedef int16 pri16;
//! プロセス間で渡されるメッセージ
typedef uint32 umsg32;
//! バッファプールID
typedef int32 bpid32;
//! Boolean値
typedef byte bool8;
//! 保存された割り込みマスク
typedef uint32 intmask;
//! ブロックIDのインデックス（ファイルシステムで使用する）
typedef int32 ibid32;
//! データブロックID（ファイルシステムで使用する）
typedef int32 dbid32;
//! UDPテーブルディスクリプタのID
typedef int32 uid32;

//! システムコール関数 返り値の型
typedef int32 syscall;
//! デバイスコール関数 返り値の型
typedef int32 devcall;
//! シェルコール関数 返り値の型
typedef int32 shellcmd;
//! プロセスの最上位レベル関数 返り値の型
typedef int32 process;
//! 割り込みハンドラ 返り値の型
typedef void interrupt;
//! ステータスを意味する返り値の型（OK／SYSERR）
typedef int32 status;

//! ローカル関数かローカル変数の宣言
#define local static

//! Boolean False（0）
#define FALSE 0
//! Boolean True（1）
#define TRUE 1

//! 連結リスト用のNULLポインタ
#define NULL 0
//! NULL文字（NULL終端）
#define NULLCH '\0'
//! 空文字
#define NULLSTR ""

/* Universal return constants */

//! 処理が成功した場合
#define OK (1)
//! 処理が失敗した場合
#define SYSERR (-1)
//! ファイルの終端（End of File）に達した場合（読み込み処理に用いる）
#define EOF (-2)
//! システムコールがタイムアウトした場合
#define TIMEOUT (-3)

//! READY状態のプロセスリストに対するグローバルID
extern qid16 readylist;

//! 最小のスタックサイズ（Byte）
#define MINSTK 400
//! ランタイムスタックの関数呼び出しコンテキスト上のByte
#define CONTEXT 64
//! ミリ秒単位のタイムスライス
#define QUANTUM 2

//! NULLプロセスのスタックサイズ
#define NULLSTK 8192 /* stack size for null process		*/

//! ポーリングI/Oを使用して、フォーマットされた文字列をコンソールに出力する。
syscall kprintf(char *fmt, ...);
//! ポーリングI/Oを使用して、コンソールのシリアルラインに文字を書き込む。
syscall kputc(byte);
//! ポーリングI/Oを使用して、コンソールのシリアルラインから文字を読み取る。
syscall kgetc(void);
