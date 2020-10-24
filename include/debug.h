/**
 * @file debug.h
 * @brief デバッグに用いる定数や関数の宣言
 */
//! メモリ内容の出力時にASCIIとして出力する指定
#define DEBUG_ASCII 0x01
//! メモリ内容の出力時に16進数として出力する指定
#define DEBUG_HEX 0x02

//! メモリ内容をダンプするhexdump()の宣言
void hexdump(void *buffer, uint32 length, bool8 text);
//! debugbreak()の宣言（実装がない）
void debugbreak(void);
//! debugret()の宣言（実装がない）
void debugret(void);
