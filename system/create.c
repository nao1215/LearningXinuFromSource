/**
 * @file create.c
 * @brief 新しいプロセスを作成する。
 */
#include <xinu.h>

//! 新しいプロセスIDを取得するnewpid()の宣言
local int newpid();

/**
 * @def roundew()
 * @brief 4の倍数でスタックサイズを丸める。
 * @param[in] x スタックサイズ
 * @return 下位2Bitを切り落とし、4の倍数で丸めたスタックサイズを返す。
 */
#define roundew(x) ((x + 3) & ~0x3)

/**
 * @brief 関数の実行を開始するプロセスを作成する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. スタックサイズがMINSTKを下回っていた場合、サイズをMINSTKまで引き上げ、丸めを行う。<br>
 * Step3.  以下のいずれかを満たした場合は、割り込み許可状態に復元し、SYSERRを返す。<br>
 * 　・スタックが確保できなかった場合<br>
 * 　・全てのプロセスがFREE状態ではなかった場合（使用中だった場合）<br>
 * 　・引数のプロセス優先度が1より小さかった場合<br>
 * Step4. アクティブプロセス数を１増やす。
 * Step5. プロセステーブルエントリを以下の状態で初期化する。<br>
 * 　・プロセス状態 = サスペンド<br>
 * 　・プロセス優先度 = 引数で指定した優先度<br>
 * 　・スタックアドレス = getstk()で取得したスタックアドレス（ プロセススタックの最上位にオーバフロー検知マーカを付与）<br>
 * 　・スタックサイズ = 引数で指定されたスタックサイズ（MINSTK以上のサイズ）<br>
 * 　・プロセス名 = 引数で指定した名前（15文字 + NULL終端）<br>
 * 　・セマフォとメッセージ = 未使用状態<br>
 * 　・デバイスディスクリプタ = XINU Shell用に0:STDIN(標準入力)、1:STDOUT(標準出力)、2:STDERR(標準エラー)を設定<br>
 * Step6. 可変長引数と関数ポインタをスタックに積む。前提として、ARMはr0〜r3レジスタが引数渡しに使用される。<br>
 * 可変長引数の5個目〜N個目をスタックに積んだ後、関数ポインタをスタックに積む。<br>
 * 引数をレジスタ渡しするためにスタックにr4〜r11用の情報（=0）を積み、r3〜r0用の情報（引数次第で変化）を積む。<br>
 * Step7. 関数のリターンアドレス（INITRET = userret()であり、kill()を呼び出す）をスタックに積む。<br>
 * Step8. CPSR F bitを有効化し、スーパバイザモードに移行するためのビットマスクをスタックに積む。<br>
 * スーパーバイザモードに移行する理由は、userret()内でシステムをDeadループさせるhalt()を実行するため（誤っている可能性高い）。<br>
 * Step9. 新しいスタックアドレスをプロセステーブルにセットする。<br>
 * Step10. 割り込み許可状態に復元する。
 * @param[in] procaddr 関数ポインタ（プロセスのエントリポイント）
 * @param[in] ssize スタックサイズ（Byte）
 * @param[in] priority プロセスの優先度（> 0）
 * @param[in] name プロセス名（デバッグ用）
 * @param[in] nargs 本引数より後にある引数の総数
 * @param[in] ... 可変長引数
 * @return 成功時は作成したプロセスのID、以下の場合はSYSERRを返す。<br>
 * 　・スタックが確保できなかった場合<br>
 * 　・全てのプロセスがFREE状態ではなかった場合（使用中だった場合）<br>
 * 　・引数のプロセス優先度が1より小さかった場合
 */
pid32 create(void *procaddr, uint32 ssize, pri16 priority, char *name, uint32 nargs, ...)
{
	intmask mask;		   /* interrupt mask		*/
	pid32 pid;			   /* stores new process id	*/
	struct procent *prptr; /* pointer to proc. table entry */
	int32 i;
	uint32 *a;	   /* points to list of args	*/
	uint32 *saddr; /* stack address		*/

	mask = disable();
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (uint32)roundew(ssize);
	if (((saddr = (uint32 *)getstk(ssize)) ==
		 (uint32 *)SYSERR) ||
		(pid = newpid()) == SYSERR || priority < 1)
	{
		restore(mask);
		return SYSERR;
	}

	prcount++;
	prptr = &proctab[pid];

	/* initialize process table entry for new process */
	prptr->prstate = PR_SUSP; /* initial state is suspended	*/
	prptr->prprio = priority;
	prptr->prstkbase = (char *)saddr;
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN - 1] = NULLCH;
	for (i = 0; i < PNMLEN - 1 && (prptr->prname[i] = name[i]) != NULLCH; i++)
		;
	prptr->prsem = -1;
	prptr->prparent = (pid32)getpid();
	prptr->prhasmsg = FALSE;

	/* set up initial device descriptors for the shell		*/
	prptr->prdesc[0] = CONSOLE; /* stdin  is CONSOLE device	*/
	prptr->prdesc[1] = CONSOLE; /* stdout is CONSOLE device	*/
	prptr->prdesc[2] = CONSOLE; /* stderr is CONSOLE device	*/

	/* Initialize stack as if the process was called		*/

	*saddr = STACKMAGIC;

	/* push arguments */
	a = (uint32 *)(&nargs + 1); /* start of args		*/
	a += nargs - 1;				/* last argument		*/
	for (; nargs > 4; nargs--)	/* machine dependent; copy args	*/
		*--saddr = *a--;		/* onto created process's stack	*/
	*--saddr = (long)procaddr;
	for (i = 11; i >= 4; i--)
		*--saddr = 0;
	for (i = 4; i > 0; i--)
	{
		if (i <= nargs)
			*--saddr = *a--;
		else
			*--saddr = 0;
	}
	*--saddr = (long)INITRET;	 /* push on return address	*/
	*--saddr = (long)0x00000053; /* CPSR F bit set,		*/
	/* Supervisor mode		*/
	prptr->prstkptr = (char *)saddr;
	restore(mask);
	return pid;
}

/**
 * @brief 新しいPID（FREEなPID）を取o得する。
 * @details newpid()内で、前回のnewpid()実行結果に１を加算したPIDを保持している。<br>
 * このPIDから順番に、状態がFREEなプロセスをプロセステーブルから探す。<br>
 * 検索は全てのプロセスに対して行われ、探索対象のPIDがNPROC（プロセス総数）と一致した場合、<br>
 * 検索対象のPIDが0番に戻る（nextpid %= NPROC;部分）
 * @return 成功時は新しいPID、全てのプロセスがFREE状態ではなかった場合SYSERRを返す。
 */
local pid32 newpid(void)
{
	uint32 i;				  /* iterate through all processes*/
	static pid32 nextpid = 1; /* position in table to try or	*/
	/*  one beyond end of table	*/

	/* check all NPROC slots */

	for (i = 0; i < NPROC; i++)
	{
		nextpid %= NPROC; /* wrap around to beginning */
		if (proctab[nextpid].prstate == PR_FREE)
		{
			return nextpid++;
		}
		else
		{
			nextpid++;
		}
	}
	return (pid32)SYSERR;
}
