/**
 * @file ctype.h
 * @brief 「文字種類の判定」や「文字変換」を行う関数マクロを提供する。
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
 *    ※ 10進数は列の値に、行の値を加算して読む（列=50、行=6の場合、56='8'）<br>
 * @note Doxygenドキュメント上ではASCII表がズレるため、ASCII表のスクショを併記する。
 * @image html "ascii.png"
 */

//! アルファベット大文字を判定するためのビットマスク
#define _U 0x01
//! アルファベット小文字を判定するためのビットマスク
#define _L 0x02
//! 10進数の文字を判定するためのビットマスク
#define _N 0x04
//! 空白文字を判定するためのビットマスク
#define _S 0x08
//! 区切り文字を判定するためのビットマスク
#define _P 0x10
//! 制御文字 (control character)を判定するためのビットマスク
#define _C 0x20
//! 16進数の文字を判定するためのビットマスク
#define _X 0x40

//! 「文字種類の判定」や「文字変換」の際に使用するビットマスク配列
extern const char _ctype_[];

/**
 * @def isalpha()
 * @brief 文字がアルファベットかどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字がアルファベットの場合はtrue、それ以外の場合はfalseを返す。
 */
#define isalpha(c) ((_ctype_ + 1)[(int)c] & (_U | _L))

/**
 * @def isupper()
 * @brief 文字がアルファベットの大文字かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字がアルファベットの大文字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define isupper(c) ((_ctype_ + 1)[(int)c] & _U)

/**
 * @def islower()
 * @brief 文字がアルファベットの小文字かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字がアルファベットの小文字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define islower(c) ((_ctype_ + 1)[(int)c] & _L)

/**
 * @def isdigit()
 * @brief 文字が10進数の数字かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字が10進数の数字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define isdigit(c) ((_ctype_ + 1)[(int)c] & _N)

/**
 * @def isxdigit()
 * @brief 文字が16進数の数字かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字が16進数の数字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define isxdigit(c) ((_ctype_ + 1)[(int)c] & (_N | _X))

/**
 * @def isspace()
 * @brief 文字が空白かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字が空白の場合はtrue、それ以外の場合はfalseを返す。
 */
#define isspace(c) ((_ctype_ + 1)[(int)c] & _S)

/**
 * @def ispunct()
 * @brief 文字が区切り文字 (punctuation character) かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字が区切り文字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define ispunct(c) ((_ctype_ + 1)[(int)c] & _P)

/**
 * @def isalnum()
 * @brief 文字がアルファベットもしくは数字かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字がアルファベットもしくは数字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define isalnum(c) ((_ctype_ + 1)[(int)c] & (_U | _L | _N))

/**
 * @def isprint()
 * @brief 文字が表示文字かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字が表示文字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define isprint(c) ((_ctype_ + 1)[(int)c] & (_P | _U | _L | _N | _S))

/**
 * @def iscntrl()
 * @brief 文字が制御文字 (control character) かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字が制御文字の場合はtrue、それ以外の場合はfalseを返す。
 */
#define iscntrl(c) ((_ctype_ + 1)[(int)c] & _C)

/**
 * @def isascii()
 * @brief 文字がASCII文字かどうかをチェックするマクロ
 * @param[in] c チェック対象の文字
 * @return 文字がASCII文字の場合はtrue、それ以外の場合はfalseを返す。
 * @note ASCII文字は、0x7F=127が終端となる。
 */
#define isascii(c) ((unsigned)((int)(c)) <= 0x7F)

/**
 * @def toupper()
 * @brief アルファベットの小文字を大文字に変換するマクロ
 * @param[in] c アルファベットの小文字
 * @return アルファベットの大文字
 */
#define toupper(c) (((int)(c)) - 'a' + 'A')

/**
 * @def tolower()
 * @brief アルファベットの大文字を小文字に変換するマクロ
 * @param[in] c アルファベットの大文字
 * @return アルファベットの小文字
 */
#define tolower(c) (((int)(c)) - 'A' + 'a')

/**
 * @def tolower()
 * @brief 文字をASCII文字に変換するマクロ
 * @param[in] c 任意の文字
 * @return ASCIIに変換された文字
 * @note 最上位ビットをクリアし、ASCII文字コードに適合するように文字cを<br>
 * 7bitの unsigned char に変換する。0x7F=0b0111_1111。
 */
#define toascii(c) (((int)(c)) & 0x7F)

/**
 * @def iseof()
 * @brief 文字がEnd Of File（制御文字）かどうかをチェックするマクロ
 * @param[in] c 任意の文字
 * @return 文字がEnd Of File（制御文字）の場合はtrue、それ以外はfalseを返す。
 */
#define iseof(c) (0x04 == (int)c)
