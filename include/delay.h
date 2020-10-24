/**
 * @file delay.h
 * @brief ミリ秒もしくはマイクロ秒単位で処理を遅らせる。
 */

/**
 * @def DELAY(n)
 * @param[in] n 遅延時間（マイクロ秒）
 * @brief マイクロ秒単位で処理を遅らせる。
 */
#define DELAY(n)                 \
	{                            \
		volatile long N = 2 * n; \
                                 \
		while (N > 0)            \
		{                        \
			N--;                 \
		}                        \
	}

/**
 * @def MDELAY(n)
 * @param[in] n 遅延時間（ミリ秒）
 * @brief ミリ秒単位で処理を遅らせる。
 */
#define MDELAY(n)               \
	{                           \
		register long i;        \
                                \
		for (i = n; i > 0; i--) \
		{                       \
			DELAY(1000);        \
		}                       \
	}
