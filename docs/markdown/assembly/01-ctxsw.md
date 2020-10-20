@brief ARM (32bit)用のコンテキストスイッチを行う。

## コンテキストスイッチ ctxsw.S

@details C 言語からは、ctxsw(&old_sp, &new_sp)という形式で使用する。<br>
@param[in] old_sp：プロセステーブル中のカレントプロセススタックポインタ<br>
@param[in] new_sp：新しいプロセスのスタックポインタ<br>
<br>

## ソースコード

```
	.text
	.globl	ctxsw

ctxsw:
	push	{r0-r11, lr}    /* r0〜r11およびlrをメモリに保存する */
	push	{lr}            /* リターンアドレスを保存する        */
	mrs	r2, cpsr            /* cpsrコプロセッサからステータスを取得する */
	push	{r2}            /* ステータスをメモリに保存する */
	str	sp, [r0]            /* カレントプロセスのスタックポインタをメモリに保存する。*/
	ldr	sp, [r1]            /* 新しいプロセスのスタックポインタをメモリから読み込む	*/
	pop	{r0}                /* 引数としてステータスをメモリから取得する	*/
	bl	restore             /* restore命令を呼び出し、リストアを行う */
	pop	{lr}                /* リターンアドレスを取得する */
	pop	{r0-r12}            /* 汎用レジスタをリストアする */
	mov	pc, r12	            /* 新しいプロセスに戻る	*/
```