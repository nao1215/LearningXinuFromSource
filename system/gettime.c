/**
 * @file gettime.c
 * @brief 1970年1月1日からの経過時間（秒単位）にロケーション（時差）を反映した時間を返す。
 */
#include <xinu.h>

/**
 * @brief 1970年1月1日からの経過時間（秒単位）にロケーション（時差）を反映した時間を返す。
 * @details UCT（協定世界時）からの経過時刻に対してロケーション（時差）を反映する。
 * @param[in,out] timvar XINU時刻の取得結果の保存先
 * @return XINU時間を取得できた場合はOK、UCTからの経過時間が取得できなかった場合はSYSERRを返す。
 */
status gettime(uint32 *timvar)
{
	uint32 now;	  /* Current time (UCT)		*/
	int32 retval; /* Return value from call	*/

	/* Get current time in UCT representation (GMT) */

	retval = getutime(&now);
	if (retval == SYSERR)
	{
		return SYSERR;
	}

	/* Adjust to xinu time and store result */

	*timvar = utim2ltim(now);
	return OK;
}
