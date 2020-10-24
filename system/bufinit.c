/**
 * @file bufinit.c
 * @brief バッファプールデータ構造を初期化する。
 */
#include <xinu.h>

//! バッファプールテーブルエントリ
struct bpentry buftab[NBPOOLS];
//! 割り当てられたバッファプールの現在の数
bpid32 nbpools;

/**
 * @brief バッファプールデータ構造を初期化する。
 * @details 現在のバッファプール数を0にする。
 * @return OKを返す。
 */
status bufinit(void)
{
	nbpools = 0;
	return OK;
}
