@brief 割り込み（IRQ）を許可／禁止する。

## 割り込み許可 enable：ソースコード（intr.S）

```
enable:
	cpsie	i		/* 割り込みを許可する */
	mov	pc, lr		/* enableを呼び出す前のアドレスに戻る */
```

## 割り込み禁止 disable：ソースコード（intr.S）

C 言語上は、割り込みマスクビット(cpsr)が disable()の返り値(r0)として渡される。<br>
この返り値は、resume()や suspend()の復帰時に cpsr の状態を元に戻すために使用する。

```
disable:
	mrs	r0, cpsr    /* CPSRレジスタの内容をr0にコピー */
	cpsid	i       /* 割り込み禁止状態に遷移         */
	mov	pc, lr		/* diableを呼び出す前のアドレスに戻る */
```
