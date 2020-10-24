/**
 * @file memory.h
 * @brief メモリマネージャが使用する定数と構造体の宣言
 */

//! ページサイズ(メモリ領域を管理する一定のサイズ。Byte単位)
#define PAGE_SIZE 4096

/**
 * @def roundmb(x)
 * @brief メモリブロックサイズ（8の倍数）にアドレスを変換するために、8の倍数で丸める。
 * @details ~7 = 0xF8 = 0b11111000である。<br>
 * 0 -> 7  -> 0
 * 1 -> 8  -> 8
 * 2 -> 9  -> 8
 * : (省略)
 * 7 -> 14 -> 8
 * 8 -> 15 -> 8
 * 9 -> 16 -> 16
 * @param[in] x アドレス
 * @return アドレス末尾が0の場合は下位3Bitを切り捨てたアドレス値（8の倍数）、<br>
 * それ以外の場合は次の8の倍数に切り上げたアドレス値を返す。
 * @note フリーメモリリスト上の各ブロックは、memblk構造体（8Byte）の倍数として扱う。
 */
#define roundmb(x) (char *)((7 + (uint32)(x)) & (~7))

/**
 * @def truncmb(x)
 * @brief メモリブロックサイズ（8の倍数）にアドレスを変換するために、下位3bitを切り捨てる。
 * @param[in] x アドレス
 * @return 下位3Bitを切り捨てたアドレス値（8の倍数）を返す。
 * @note フリーメモリリスト上の各ブロックは、memblk構造体（8Byte）の倍数として扱う。<br>
 * 切り捨てはスタートアップ時にだけ使用される。
 */
#define truncmb(x) (char *)(((uint32)(x)) & (~7))

/**
 * @def freestk(x)
 * @brief getstk()で割り当てたスタックメモリを解放する。
 * @param[in] p 解放するメモリブロックの基点
 * @param[in] len  解放するメモリブロックのサイズ(Byte)
 * @return メモリ解放に成功した場合はOK、それ以外の場合はSYSERRを返す。
 * @note 返り値の詳細は、 freemem()を参照する事。<br>
 * スタックは下方向に成長するため、freemem()に渡すポインタアドレスの基点を上位側から下位側に変換して渡している。
 */
#define freestk(p, len) freemem((char *)((uint32)(p) - ((uint32)roundmb(len)) + (uint32)sizeof(uint32)), \
								(uint32)roundmb(len))

/**
 * @struct memblk
 * @brief メモリブロックを管理するための構造体。
 */
struct memblk
{
	//! 次のフリーメモリブロックへのポインタ
	struct memblk *mnext;
	//! memblk構造体のサイズを含むブロックサイズ
	uint32 mlength;
};

//! フリーメモリリストの先頭
extern struct memblk memlist;
//! ヒープの開始地点
extern void *minheap;
//! 最上位かつ正常なヒープアドレス
extern void *maxheap;

/* Added by linker */

//! テキストセグメントの開始アドレス（リンカが追加する）
extern int text;
//! テキストセグメントの終了アドレス（リンカが追加する）
extern int etext;
//! データセグメントの開始アドレス（リンカが追加する）
extern int data;
//! データセグメントの終了アドレス（リンカが追加する）
extern int edata;
//! BSSセグメントの開始アドレス（リンカが追加する）
extern int bss;
//! BSSセグメントの終了アドレス（リンカが追加する）
extern int ebss;
//! プログラムの終了アドレス（リンカが追加する）
extern int end;
