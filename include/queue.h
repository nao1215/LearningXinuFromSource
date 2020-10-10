/**
 * @file queue.h
 * @brief キュー構造体に関する宣言／定数／インライン関数を定義する。
 * @note プロセスキューテーブルは、リストとも呼ばれる。
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
 * @details プロセスごとに1個、リストごとに2個（先頭／末尾分）必要。
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

/**
 * @def  queuehead()
 * @brief キューの先頭を返す。
 * @param[in] q  キューID
 * @return キュー先頭のキューID（引数のキューIDそのまま）を返す。
 */
#define queuehead(q) (q)

/**
 * @def  queuetail()
 * @brief キューの末尾を返す。
 * @param[in] q  キューID
 * @return キュー末尾のキューID（引数のキューIDに1を加算した値）を返す。
 */
#define queuetail(q) ((q) + 1)

/**
 * @def  firstid()
 * @brief リストの最初のプロセスのIDを返す。
 * @param[in] q  キューID
 * @return リストの最初のプロセスのID
 * @note リストは必ず先頭と末尾を持っている。先頭のqnextには、最初のプロセスIDが入っている。
 */
#define firstid(q) (queuetab[queuehead(q)].qnext)

/**
 * @def  lastid()
 * @brief リストの最後のプロセスのIDを返す。
 * @param[in] q  キューID
 * @return リストの最後のプロセスのID
 * @note リストは必ず先頭と末尾を持っている。末尾のqprevには、最後のプロセスIDが入っている。
 */
#define lastid(q) (queuetab[queuetail(q)].qprev)

/**
 * @def  isempty()
 * @brief リストが空かどうかを返す。
 * @param[in] q  キューID
 * @return リストが空の場合はtrue、それ以外はfalseを返す。
 * @note リストは必ず先頭と末尾を持っていて、それらのインデックスはNPROC以上である。<br>
 * リストの最初のノード（先頭のqnext）がNPROC以上の場合は、先頭と末尾しか無い（リストが空）とみなせる<br>
 */
#define isempty(q) (firstid(q) >= NPROC)

/**
 * @def  nonempty()
 * @brief リストに中身（プロセス）があるかどうかを返す。
 * @param[in] q  キューID
 * @return リストが空の場合はtrue、それ以外はfalseを返す。
 * @note リストは必ず先頭と末尾を持っていて、それらのインデックスはNPROC以上である。<br>
 * リストの最初のノード（先頭のqnext）がNPROCより小さい場合は、プロセスが挿入されている。<br>
 */
#define nonempty(q) (firstid(q) < NPROC)

/**
 * @def  firstkey()
 * @brief リスト中の最初のプロセスのキーを返す。
 * @param[in] q  キューID
 * @return リスト中の最初のプロセスのキー（最初のプロセスのqueuetabインデックス）
 */
#define firstkey(q) (queuetab[firstid(q)].qkey)

/**
 * @def  firstkey()
 * @brief リスト中の最後のプロセスのキーを返す。
 * @param[in] q  キューID
 * @return リスト中の最後のプロセスのキー（最後のプロセスのqueuetabインデックス）
 */
#define lastkey(q) (queuetab[lastid(q)].qkey)

/**
 * @def isbadqid()
 * @brief キューIDが不正値かどうかをチェックする。
 * @param[in] x キューID
 * @details 割り込みが禁止された状態である事を想定している。<br>
 * キューIDの不正とは、<br>
 * ① キューIDがユーザプロセス総数(NPROC)より小さい
 * ② キューIDがデフォルトキューエントリ総数以上
 * のいずれかである。
 * @return 不正なキューIDの場合はtrue、それ以外の場合はfalseを返す。
 * @note 上記①に関しては、XINUオペレーティングシステムデザイン改訂2版では、<br>
 * 「キューIDが負の値か」という条件であった。この考え方は、配列操作の観点から正しい。<br>
 * XINUとしての仕様では、0 < x <NPROCの範囲はプロセスが使用し、それ以上の範囲をキューが使用するため、<br>
 * isbadqid()の仕様を変えたと思われる。
 */
#define isbadqid(x) (((int32)(x) < NPROC) || (int32)(x) >= NQENT - 1)
