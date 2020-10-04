/**
 * @file queue.h
 * @brief キュー構造体に関する宣言／定数／インライン関数を定義する。
 */

/**
 * キューテーブルのエントリ数（=NQENT）は、条件付きコンパイルによって、動的に<br>
 * そのサイズを変更できる（queue.hの修正が不要となる）。
 */
#ifndef NQENT
/**
 * キューテーブル配列に対するデフォルトキューエントリ数。
 * NPROC個のプロセスに加えて、READYリスト／休眠リスト／セマフォリストの先頭と<br>
 * 末尾のポインタを保持するためのエントリ数を定義している。<br>
 * キューエントリは、プロセスごとに1個、レディリストに2個、休眠リストに2個、<br>
 * セマフォに2個を割り当てている。
 */
#define NQENT (NPROC + 4 + NSEM + NSEM)
#endif

//! 次のキューインデックスもしくは前のキューインデックスがNULL値
#define EMPTY (-1)
//! キューの中に格納できるキーの最大値
#define MAXKEY 0x7FFFFFFF
//! キューの中に格納できるキーの最小値
#define MINKEY 0x80000000

/**
 * @struct qentry
 * @brief プロセスキューの一つであり、本構造体の配列がプロセスキューテーブルとなる。
 * @details プロセスごとに1個、リストごとに2個必要。
 */
struct qentry
{
	//! キュー順序を決定するキー。
	int32 qkey;
	//! 次のプロセスか末尾のプロセスのインデックス。
	qid16 qnext;
	//! 前のプロセスか先頭のプロセスのインデックス。
	qid16 qprev;
};

/** プロセスキューテーブル（全てのプロセスがアクセス可能な変数）。*/
extern struct qentry queuetab[];

/* Inline queue manipulation functions */

#define queuehead(q) (q)
#define queuetail(q) ((q) + 1)
#define firstid(q) (queuetab[queuehead(q)].qnext)
#define lastid(q) (queuetab[queuetail(q)].qprev)
#define isempty(q) (firstid(q) >= NPROC)
#define nonempty(q) (firstid(q) < NPROC)
#define firstkey(q) (queuetab[firstid(q)].qkey)
#define lastkey(q) (queuetab[lastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */

#define isbadqid(x) (((int32)(x) < NPROC) || (int32)(x) >= NQENT - 1)
