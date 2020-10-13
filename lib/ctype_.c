/**
 * @file ctype_.c
 * @brief 「文字種類の判定」や「文字変換」の際に使用するビットマスク配列を定義する。
 * @details ASCII文字コード表<br>
 *        [16進数]                      [10進数] <br>
 *         2 3 4 5 6 7       30 40 50 60 70 80 90 100 110 120<br>
 *       -------------      ---------------------------------<br>
 *      0:   0 @ P ` p     0:    (  2  <  F  P  Z  d   n   x<br>
 *      1: ! 1 A Q a q     1:    )  3  =  G  Q  [  e   o   y<br>
 *      2: " 2 B R b r     2:    *  4  >  H  R  \  f   p   z<br>
 *      3: # 3 C S c s     3: !  +  5  ?  I  S  ]  g   q   {<br>
 *      4: $ 4 D T d t     4: "  ,  6  @  J  T  ^  h   r   |<br>
 *      5: % 5 E U e u     5: #  -  7  A  K  U  _  i   s   }<br>
 *      6: & 6 F V f v     6: $  .  8  B  L  V  `  j   t   ~<br>
 *      7: ' 7 G W g w     7: %  /  9  C  M  W  a  k   u  DEL<br>
 *      8: ( 8 H X h x     8: &  0  :  D  N  X  b  l   v<br>
 *      9: ) 9 I Y i y     9: '  1  ;  E  O  Y  c  m   w<br>
 *      A: * : J Z j z<br>
 *      B: + ; K [ k {<br>
 *      C: , < L \ l |<br>
 *      D: - = M ] m }<br>
 *      E: . > N ^ n ~<br>
 *      F: / ? O _ o DEL<br>
 *    ※ 16進数は列の値に、行の値を連結して読む（列=7、行=Aの場合、7A='z'）<br>
 *    ※ 10進数は列の値に、行の値を加算して読み（列=50、行=6の場合、56='8'）<br>
 * @note Doxygenドキュメント上ではASCII表がズレるため、ASCII表のスクショを併記する。
 * @image html "ascii.png"
 */
#include <ctype.h>

/**
 * 「文字種類の判定」や「文字変換」の際に使用するビットマスク配列<br>
 * ASCII文字は7bit（0〜127の数値）で表される。そのため、_ctype_配列に<br>
 * 英字、数値、制御文字などを判定するためのビットマスクを予め仕込んでおき、<br>
 * Step1. チェック対象文字を配列の添字として、_ctype_配列からビットマスクを取得<br>
 * Step2. 前手順Step2.で取得したビットマスクが期待値通りかチェック<br>
 * という手順を実施する事によって、文字の種類を判定できる。
 */
const char _ctype_[] = {
    0,
    _C, _C, _C, _C, _C, _C, _C, _C,
    _C, _S, _S, _S, _S, _S, _C, _C,
    _C, _C, _C, _C, _C, _C, _C, _C,
    _C, _C, _C, _C, _C, _C, _C, _C,
    _S, _P, _P, _P, _P, _P, _P, _P,
    _P, _P, _P, _P, _P, _P, _P, _P,
    _N, _N, _N, _N, _N, _N, _N, _N,
    _N, _N, _P, _P, _P, _P, _P, _P,
    _P, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X,
    _U,
    _U, _U, _U, _U, _U, _U, _U, _U,
    _U, _U, _U, _U, _U, _U, _U, _U,
    _U, _U, _U, _P, _P, _P, _P, _P,
    _P, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X,
    _L,
    _L, _L, _L, _L, _L, _L, _L, _L,
    _L, _L, _L, _L, _L, _L, _L, _L,
    _L, _L, _L, _P, _P, _P, _P, _C};
