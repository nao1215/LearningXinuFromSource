/**
 * @file putc.c
 * @brief デバイスへ文字１Byteを送信する。
 */
#include <xinu.h>

/**
 * @brief デバイスへ文字１Byteを送信する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. デバイスディスクリプタが不正値の場合は、割り込み状態を復元し、処理を終了する。<br>
 * Step3. デバイスに応じたputc()処理を行う。<br>
 * Step4. 割り込み状態を復元する。
 * @param[in] descrp デバイスディスクリプタ
 * @param[in] ch 送信したい文字
 * @return 成功時はデバイスに応じた返り値、デバイスディスクリプタが不正値の場合はSYSERRを返す。
 */
syscall putc(did32 descrp, char ch)
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
	retval = (*devptr->dvputc)(devptr, ch);
	restore(mask);
	return retval;
}
