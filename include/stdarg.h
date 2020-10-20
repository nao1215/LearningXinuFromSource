/**
 * @file stdarg.h
 * @brief 可変長引数を実現するための宣言およびマクロ
 */

//! 可変個の実引数を扱うための情報を保持するための型（__builtin_va_listはGCCに定義された型）
typedef __builtin_va_list va_list;

/**
 * @def va_copy()
 * @brief va_list型のコピーを作成する。
 * @details GCCに定義された__builtin_va_copy()のラッパーマクロ。
 * @param[out] dst コピー先（va_list型）
 * @param[in] src コピー元（va_list型）
 */
#define va_copy(dst, src) __builtin_va_copy(dst, src)
/**
 * @def va_start()
 * @brief va_list型を初期化し、可変長引数の使用を開始する。
 * @details GCCに定義された__builtin_va_start()のラッパーマクロ。<br>
 * va_start()とva_end<>は対応関係があり、どちらかが欠けていると未定義動作となる。
 * @param[in] last va_list型
 * @param[in] va 可変長引数でない最後の引数（例：フォーマット）
 */
#define va_start(last, va) __builtin_va_start(last, va)
/**
 * @def va_arg()
 * @brief 可変長引数の値を返し、次の引数へ進む。<br>
 * 「va_start()とva_end()の間」もしくは「va_copy()とva_end()の間」で使用する。
 * @details GCCに定義された__builtin_va_arg()のラッパーマクロ。
 * @param[in] va va_list型
 * @param[in] type 可変長引数から取り出したい引数の型
 */
#define va_arg(va, type) __builtin_va_arg(va, type)
/**
 * @def va_end()
 * @brief 可変長引数の処理を終了する。
 * @details GCCに定義された__builtin_va_end(()のラッパーマクロ。<br>
 * va_start()とva_end<>は対応関係があり、どちらかが欠けていると未定義動作となる。
 * @param[in] va va_list型
 */
#define va_end(va) __builtin_va_end(va)
