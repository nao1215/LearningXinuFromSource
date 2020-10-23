/**
 * @file getticks.c
 * @brief CPUリセット以降のclock tick数を取得する。
 */
#include <xinu.h>

/**
 * @brief CPUリセット以降のclock tick数を取得する。
 * @return CPUリセット以降のclock tick
 * @note インラインアセンブラ部分はPMCNT0〜PMCNT3レジスタを読み込んでいる。<br>
 * なお、CP15（コプロセッサ15、p15）は、システム制御機能を提供する。<br>
 * c9はパフォーマンスモニターカウントレジスタ、c13はサイクルカウントレジスタである。
 */
uint32 getticks()
{
	uint32 ret;
	asm volatile("MRC p15, 0, %0, c9, c13, 0\t\n"
				 : "=r"(ret));
	return ret;
}
