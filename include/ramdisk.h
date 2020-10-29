/**
 * @file ramdisk.h
 * @brief RAMディスクに関する定義（testing）
 */

//! RAMディスクのブロックサイズ
#define RM_BLKSIZ 512
//! RAMディスクのブロック数
#define RM_BLKS 200

/**
 * @struct ramdisk
 * @brief RAMディスク操作用の構造体
 */
struct ramdisk
{
	//! RAMディスク操作用の配列
	char disk[RM_BLKSIZ * RM_BLKS];
};

//! RAMディスク操作用の構造体のextern宣言
extern struct ramdisk Ram;
