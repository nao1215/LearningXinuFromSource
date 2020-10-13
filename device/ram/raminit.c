/**
 * @dir device/ram
 * @brief Random Access Memoryデバイスドライバ
 * @file raminit.c
 * @brief RAMを初期化する。
 */

#include <xinu.h>
#include <ramdisk.h>

struct ramdisk Ram;

/*------------------------------------------------------------------------
 *  raminit  -  Initialize the remote disk system device
 *------------------------------------------------------------------------
 */
devcall raminit(
	struct dentry *devptr /* Entry in device switch table	*/
)
{
	memcpy(Ram.disk, "hopeless", 8);
	memcpy(&Ram.disk[8], Ram.disk, RM_BLKSIZ * RM_BLKS - 8);
	return OK;
}
