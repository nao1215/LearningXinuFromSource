/**
 * @file rand.c
 * @brief 疑似乱数を返す。
 */
#include <stdlib.h>

//! 疑似乱数のシード値。
static unsigned int rand_seed = 1;
//! 任意のシード値を用いて、疑似乱数を返すrand_r()の宣言。
extern int rand_r(unsigned int *);

/**
 * @brief 予め設定済みのシード値を用いて、疑似乱数を返す。
 * @details シード値を変えない限り、疑似乱数に再現性がある。
 * @return 疑似乱数（int型の整数値。0〜RAND_MAXの範囲で表される値）
 */
int rand()
{
	return rand_r(&rand_seed);
}

/**
 * @brief 任意のシード値を用いて、疑似乱数を返す。
 * @param[in,out] seedp 疑似乱数のシード値（乱数を生成する際に用いる値）
 * @return 疑似乱数（int型の整数値。0〜RAND_MAXの範囲で表される値）
 */
int rand_r(unsigned int *seedp)
{
	*seedp = 16807 * (*seedp) % (RAND_MAX + 1);
	return (int)(*seedp);
}

/**
 * @brief 疑似乱数のシード値を設定する。
 * @param[in] seed 疑似乱数のシード（乱数を生成する際に用いる値）
 */
void srand(
	unsigned int seed)
{
	rand_seed = seed;
}
