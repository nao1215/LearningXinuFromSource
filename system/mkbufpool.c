/**
 * @file mkbufpool.c
 * @brief バッファプール用のメモリを割り当て、バッファ同士をリンクする。
 */
#include <xinu.h>

/**
 * @brief バッファプール用のメモリを割り当て、バッファ同士をリンクする。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 以下のいずれかの場合は、割り込み状態を復元し、処理を終了する。<br>
 * 　・バッファサイズがバッファ最小値を下回る場合<br>
 * 　・バッファサイズがバッファ最大値を超えた場合<br>
 * 　・バッファ数が0以下の場合<br>
 * 　・バッファ数がバッファ最大数を超えた場合<br>
 * 　・割り当て済みのバッファプール数が最大数を超えた場合<br>
 * Step3. 要求されたバッファサイズを4の倍数で丸める。<br>
 * Step4. 要求されたバッファサイズ + バッファプールID分のメモリをバッファ数分、割り当てる。<br>
 * メモリ確保に失敗した場合は割り込み状態を復元し、処理を終了する。
 * Step5. 新しいバッファプールIDを割り当て、バッファプールの総数を1増加させる。<br>
 * Step6. 割り当てたバッファとバッファプールをリンクする。<br>
 * Step7. 割り当てたバッファにセマフォを割り当てる。<br>
 * セマフォ割り当てに失敗した場合は割り当てたバッファを解放し、バッファプール総数を元に戻し、<br>
 * 割り込み状態を復元し、処理を終了する。<br>
 * Step8. 割り当てたバッファ同士をリンクする。<br>
 * Step9. 割り込み状態を復元する。
 * @param[in] bufsiz バッファプール中のバッファサイズ
 * @param[in] numbufs バッファプール中のバッファ数
 * @return バッファプールを割り当てた場合はバッファプールIDを返し、以下の場合はSYSERRを返す。<br>
 * 　・バッファサイズがバッファ最小値を下回る場合<br>
 * 　・バッファサイズがバッファ最大値を超えた場合<br>
 * 　・バッファ数が0以下の場合<br>
 * 　・バッファ数がバッファ最大数を超えた場合<br>
 * 　・割り当て済みのバッファプール数が最大数を超えた場合<br>
 * 　・バッファを確保できなかった場合<br>
 * 　・セマフォを作成できなかった場合
 */
bpid32 mkbufpool(int32 bufsiz, int32 numbufs)
{
	intmask mask;		   /* Saved interrupt mask		*/
	bpid32 poolid;		   /* ID of pool that is created	*/
	struct bpentry *bpptr; /* Pointer to entry in buftab	*/
	char *buf;			   /* Pointer to memory for buffer	*/

	mask = disable();
	if (bufsiz < BP_MINB || bufsiz > BP_MAXB || numbufs < 1 || numbufs > BP_MAXN || nbpools >= NBPOOLS)
	{
		restore(mask);
		return (bpid32)SYSERR;
	}
	/* Round request to a multiple of 4 bytes */

	bufsiz = ((bufsiz + 3) & (~3));

	buf = (char *)getmem(numbufs * (bufsiz + sizeof(bpid32)));
	if ((int32)buf == SYSERR)
	{
		restore(mask);
		return (bpid32)SYSERR;
	}
	poolid = nbpools++;
	bpptr = &buftab[poolid];
	bpptr->bpnext = (struct bpentry *)buf;
	bpptr->bpsize = bufsiz;
	if ((bpptr->bpsem = semcreate(numbufs)) == SYSERR)
	{
		freemem(buf, numbufs * (bufsiz + sizeof(bpid32)));
		nbpools--;
		restore(mask);
		return (bpid32)SYSERR;
	}
	bufsiz += sizeof(bpid32);
	for (numbufs--; numbufs > 0; numbufs--)
	{
		bpptr = (struct bpentry *)buf;
		buf += bufsiz;
		bpptr->bpnext = (struct bpentry *)buf;
	}
	bpptr = (struct bpentry *)buf;
	bpptr->bpnext = (struct bpentry *)NULL;
	restore(mask);
	return poolid;
}
