/**
 * @file main.c
 * @brief XINUシェルを起動する。
 */
#include <xinu.h>

/**
 * @brief XINUシェルを起動する。
 * @details
 * Step1. メッセージを全て受信する（ただし、メッセージ内容は確認しない）。<br>
 * Step2. XINUシェルを作成／起動する。<br>
 * Step3. XINUシェルが終了した場合は、以下の処理を行う（無限に繰り返す）。<br>
 * 　・メッセージ到着を待つ。メッセージが来なければ、待ち続ける。<br>
 * 　・200[ms]スリープする。<br>
 * 　・XINUシェルを再作成／起動する。
 * @return OKを返す。
 */
process main(void)
{

	/* Run the Xinu shell */

	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE)
	{
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
