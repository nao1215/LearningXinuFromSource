/**
 * @file xsh_clear.c
 * @brief ディスプレイウィンドウをクリアする（xtermやVT100を想定している）
 */
#include <xinu.h>
#include <stdio.h>

/**
 * @brief  ディスプレイウィンドウをクリアする（xtermやVT100を想定している）
 * @param[in] nargs 引数の数
 * @param[in] args 引数（引数を持つ配列）
 * @return 成功時は0、コマンド名以外の引数が存在する場合は1を返す。
 * @note printf()で使用されているエスケープシーケンスは、以下の意味を持つ。<br>
 * ・\033[0m ：エスケープシーケンス指定をリセットして、未指定状態に戻す。
 * ・\033[2J\：画面クリアを行う。
 * ・\033[H  ：カーソルを画面の左上隅（最初の行、最初の列）に移動させる。
 */
shellcmd xsh_clear(int nargs, char *args[])
{

    /* Insure no arguments were passed */

    if (nargs > 1)
    {
        fprintf(stderr, "use is: %s\n", args[0]);
        return 1;
    }

    printf("\033[0m\033[2J\033[H\n");
    return 0;
}
