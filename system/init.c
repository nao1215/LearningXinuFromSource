/**
 * @file init.c
 * @brief デバイスとデバイスドライバを初期化する。
 */
#include <xinu.h>

/**
 * @brief デバイスとデバイスドライバを初期化する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. デバイスディスクリプタが不正値の場合は、割り込み状態を復元し、処理を終了する。<br>
 * Step3. デバイス固有の初期化処理を実施する。<br>
 * Step4. 割り込み許可状態に復元する。
 * @param[in] descrp デバイスディスクリプタ
 * @return  成功時はデバイスに応じた返り値、デバイスディスクリプタが不正値の場合はSYSERRを返す。
 */
syscall init(did32 descrp)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct dentry *devptr; /* Entry in device switch table	*/
	int32 retval;		   /* Value to return to caller	*/

	mask = disable();
	if (isbaddev(descrp))
	{
		restore(mask);
		return SYSERR;
	}
	devptr = (struct dentry *)&devtab[descrp];
	retval = (*devptr->dvinit)(devptr);
	restore(mask);
	return retval;
}
