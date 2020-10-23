/**
 * @file addargs.c
 * @brief XINUシェルが作成したコマンドプロセスのスタックに引数argv（任意個）のローカルコピーを追加する。
 */
#include <xinu.h>
#include "shprototypes.h"

/**
 * @brief XINUシェルが作成したコマンドプロセスのスタックに引数argv（任意個）のローカルコピーを追加する。
 * @details
 * Step1. 割り込みを禁止する。<br>
 * Step2. 「引数の数が0以下」もしくは「トークンバッファの中にあるデータの長さが0以下」であれば、<br>
 * 割り込み状態を復元し、処理を修正する。<br>
 * Step3. args配列と引数文字列（トークンバッファ）を続けて格納するために、プロセススタックの最下位の場所を計算する。<br>
 * 4Byte単位での丸め計算も行うため、args配列はユーザスタック最下位かその次の4byteの倍数アドレスから始まる。<br>
 * 最下位アドレス：[トークン1へのポインタ][トークン2へのポインタ][NULL][トークン1][NULL][トークン2]...：最上位アドレス<br>
 * Step4. 文字列は可変長のため、args配列を超えた最初の位置を計算する。<br>
 * Step5. args配列に格納されたポインタ（各引数へのポインタ）に対して、文字列領域開始アドレスをオフセットとして加え、<br>
 * スタック最下位から順に格納する。
 * Step6. args配列に格納されたポインタの後に、区切りとしてNULLを付与する。<br>
 * Step7. 引数文字列をargs配列（+ NULL）を超えた位置にコピーする。<br>
 * Step8. プロセススタック中の第2引数（XINUシェルがプロセスをcreate()した際にスタックに追加した引数であり、<br>
 * 引数dummyと同じアドレスを持つ）を探し、第2引数の内容をプロセススタック中のargs配列アドレスに置換する。<br>
 * Step9. 割り込みを許可状態に復元する。
 * @param[in] pid 使用するプロセスID
 * @param[in] ntok 引数の数
 * @param[in] tok トークンバッファの中にあるトークンのインデックス
 * @param[in] tlen トークンバッファの中にあるデータの長さ
 * @param[in] tokbuf NULLで終わるトークン配列
 * @param[in,out] dummy 生成時に使用されるダミー引数。引数の配列へのポインタで置き換える必要がある。
 * @return
 */
status addargs(pid32 pid, int32 ntok, int32 tok[], int32 tlen, char *tokbuf, void *dummy)
{
	intmask mask;		   /* Saved interrupt mask		*/
	struct procent *prptr; /* Ptr to process' table entry	*/
	uint32 aloc;		   /* Argument location in process stack as an integer	*/
	uint32 *argloc;		   /* Location in process's stack to place args vector	*/
	char *argstr;		   /* Location in process's stack to place arg strings	*/
	uint32 *search;		   /* pointer that searches for dummy argument on stack	*/
	uint32 *aptr;		   /* Walks through args array	*/
	int32 i;			   /* Index into tok array		*/

	mask = disable();

	/* Check argument count and data length */

	if ((ntok <= 0) || (tlen < 0))
	{
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];

	/* Compute lowest location in the process stack where the	*/
	/*	args array will be stored followed by the argument	*/
	/*	strings							*/

	aloc = (uint32)(prptr->prstkbase - prptr->prstklen + sizeof(uint32));
	argloc = (uint32 *)((aloc + 3) & ~0x3); /* round multiple of 4	*/

	/* Compute the first location beyond args array for the strings	*/

	argstr = (char *)(argloc + (ntok + 1)); /* +1 for a null ptr	*/

	/* Set each location in the args vector to be the address of	*/
	/*	string area plus the offset of this argument		*/

	for (aptr = argloc, i = 0; i < ntok; i++)
	{
		*aptr++ = (uint32)(argstr + tok[i]);
	}

	/* Add a null pointer to the args array */

	*aptr++ = (uint32)NULL;

	/* Copy the argument strings from tokbuf into process's	stack	*/
	/*	just beyond the args vector				*/

	memcpy(aptr, tokbuf, tlen);

	/* Find the second argument in process's stack */

	for (search = (uint32 *)prptr->prstkptr;
		 search < (uint32 *)prptr->prstkbase; search++)
	{

		/* If found, replace with the address of the args vector*/

		if (*search == (uint32)dummy)
		{
			*search = (uint32)argloc;
			restore(mask);
			return OK;
		}
	}

	/* Argument value not found on the stack - report an error */

	restore(mask);
	return SYSERR;
}
