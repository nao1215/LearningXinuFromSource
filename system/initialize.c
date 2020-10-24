/**
 * @file initialize.c
 * @brief システムの初期化を処理し、nullプロセスとなる。
 */
#include <xinu.h>
#include <string.h>

//! XINUコードの開始であるstart()のextern宣言
extern void start(void);
//! XINUコードの終わり
extern void *_end;

//! 最初に生成されるmainプロセスのextern宣言
extern void main(void);
//! 内部システムの初期化を行うsysinit()のextern宣言
static void sysinit();
//! フリーメモリリストを初期化するmeminit()のextern宣言
extern void meminit(void);
//! スタートアップタスクを完了するプロセス
local process startup(void);

//! プロセステーブルエントリ
struct procent proctab[NPROC];
//! セマフォテーブルエントリ
struct sentry semtab[NSEM];
//! フリーメモリブロックのリスト
struct memblk memlist;

//! 生存しているプロセスの総数
int prcount;
//! 現在実行中のプロセスのID
pid32 currpid;
//! コンソール（コンソールカラー、文字、ポジション）をリセットするためのエスケープシーケンス
#define CONSOLE_RESET " \033[0m\033[2J\033[;H"

/**
 * @brief システムの初期化を処理し、nullプロセスとなる。
 * @details
 * Step1. XINUデータ構造とデバイスを初期化する。<br>
 * Step2. XINUシステムのメモリレイアウトを出力する。<br>
 * Step3. 割り込みを許可状態にする。<br>
 * Step4. ネットワークデータ構造およびネットワーク関連プロセスを初期化する。<br>
 * Step5. スタートアップ（初期化）終了プロセスを呼び出し、その中でmainプロセスを呼び出す。<br>
 * Step6. 本関数はnullプロセスとなる。つまり、他のプロセスを実行する準備ができていない時、<br>
 * CPUを実行するプロセス（nullプロセス）がある事を保証する。
 * @note Cランタイム環境が確立された後に、プログラムの実行は本関数から開始される。<br>
 * 割り込みは最初は無効であり、最終的には明示的に有効にする必要がある。<br>
 * 本関数は、初期化完了後にnullプロセスとなる。nullプロセスは常に実行可能な状態を<br>
 * 維持する必要がある。そのため、中断、セマフォの待機、スリープ状態、または終了を<br>
 * 引き起こす可能性のあるコードを実行できない。特に、コードはkprintfなどのポーリング版を<br>
 * 除いて、I/Oを実行してはならない。
 */
void nulluser()
{
	struct memblk *memptr; /* Ptr to memory block		*/
	uint32 free_mem;	   /* Total amount of free memory	*/

	/* Initialize the system */

	sysinit();

	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
		 memptr = memptr->mnext)
	{
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext)
	{
		kprintf("           [0x%08X to 0x%08X]\n",
				(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
			(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
			(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
			(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
			(uint32)&data, (uint32)&ebss - 1);

	/* Enable interrupts */

	enable();

	/* Initialize the network stack and start processes */

	net_init();

	/* Create a process to finish startup and start main */

	resume(create((void *)startup, INITSTK, INITPRIO,
				  "Startup process", 0, NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE)
	{
		; /* Do nothing */
	}
}

/**
 * @brief nullプロセスから実行できないスタートアップ処理（初期化処理）を行い、mainプロセスを作成／実行する。
 * @details
 * Step1. DHCPを使用してIPアドレスを取得／表示する。<br>
 * Step2. mainプロセスを作成し、実行する。
 * @return OKを返す。
 */
local process startup(void)
{
	uint32 ipaddr; /* Computer's IP address	*/
	char str[128]; /* String used to format output	*/

	/* Use DHCP to obtain an IP address and format it */

	ipaddr = getlocalip();
	if ((int32)ipaddr == SYSERR)
	{
		kprintf("Cannot obtain an IP address\n");
	}
	else
	{
		/* Print the IP in dotted decimal and hex */
		ipaddr = NetData.ipucast;
		sprintf(str, "%d.%d.%d.%d",
				(ipaddr >> 24) & 0xff, (ipaddr >> 16) & 0xff,
				(ipaddr >> 8) & 0xff, ipaddr & 0xff);

		kprintf("Obtained IP address  %s   (0x%08x)\n", str,
				ipaddr);
	}
	/* Create a process to execute function main() */

	resume(create((void *)main, INITSTK, INITPRIO,
				  "Main process", 0, NULL));

	/* Startup process exits at this point */

	return OK;
}

/**
 * @brief XINUデータ構造とデバイスを初期化する。
 * @details
 * Step1. コンソールリセットを行う。<br>
 * Step2. プラットフォーム固有の初期化を行う。<br>
 * Step3. 割り込みベクタを初期化する。<br>
 * Step4. フリーメモリリストを初期化する。<br>
 * Step5. プロセス総数を記録する（nullプロセス分のみ記録するため、1となる）。<br>
 * Step6. スケジューリングの延期（Defer）状態をリセットする。<br>
 * Step7. プロセステーブルエントリ（nullプロセス分も含む）を初期化する。<br>
 * Step8. セマフォテーブルを初期化する。<br>
 * Step9. バッファプールを初期化する。<br>
 * Step10. プロセスのREADYリストを作成する。<br>
 * Step11. リアルタイムクロックを初期化する。<br>
 * Step12. デバイスとデバイスドライバを初期化する。<br>
 */
static void sysinit()
{
	int32 i;
	struct procent *prptr; /* Ptr to process table entry	*/
	struct sentry *semptr; /* Ptr to semaphore table entry	*/

	kprintf(CONSOLE_RESET);
	kprintf("\n%s\n\n", VERSION);

	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();

	/* Initialize free memory list */

	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++)
	{
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;

	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++)
	{
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++)
	{
		init(i);
	}
	return;
}

/**
 * @brief 処理を停止させる。無限ループによる停止のため、復帰にはリセットが必要である。
 * @param[in] s 停止時に表示するメッセージ
 */
int32 stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while (1)
		/* Empty */;
}

/**
 * @brief マイクロ秒単位で処理を遅らせる。
 * @param[in] n 遅延時間（マイクロ秒）
 * @return OKを返す。
 */
int32 delay(int n)
{
	DELAY(n);
	return OK;
}
