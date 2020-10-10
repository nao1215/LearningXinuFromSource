/**
 * @file shell.h
 * @brief XINUシェルで使用される宣言と定数。
 */

//! インプットバッファの長さ
#define SHELL_BUFLEN TY_IBUFLEN + 1
//! 一行あたりの最大トークン数
#define SHELL_MAXTOK 32
//! コマンドを実行するプロセスに対するスタックサイズ
#define SHELL_CMDSTK 8192
//! 引数の領域（長さ）
#define SHELL_ARGLEN (SHELL_BUFLEN + SHELL_MAXTOK)
//! コマンドに対するプロセス優先度
#define SHELL_CMDPRIO 20

//! シェル起動時のバナー その0（文字色を赤くするANSIエスケープシーケンス）
#define SHELL_BAN0 "\033[31;1m"
//! シェル起動時のバナー その1
#define SHELL_BAN1 "------------------------------------------"
//! シェル起動時のバナー その2
#define SHELL_BAN2 "   __    __   _____    _   _    _    _    "
//! シェル起動時のバナー その3
#define SHELL_BAN3 "   \\ \\  / /  |__ __|  | \\ | |  | |  | |   "
//! シェル起動時のバナー その4
#define SHELL_BAN4 "    \\ \\/ /     | |    |  \\| |  | |  | |   "
//! シェル起動時のバナー その5
#define SHELL_BAN5 "    / /\\ \\    _| |_   | \\   |  | |  | |   "
//! シェル起動時のバナー その6
#define SHELL_BAN6 "   / /  \\ \\  |     |  | | \\ |  \\  --  /   "
//! シェル起動時のバナー その7
#define SHELL_BAN7 "   --    --   -----    -   -     ----     "
//! シェル起動時のバナー その8
#define SHELL_BAN8 "------------------------------------------"
//! シェル起動時のバナー その9（文字色をデフォルトに戻すANSIエスケープシーケンス）
#define SHELL_BAN9 "\033[0m\n"

//! コマンドプロンプト
#define SHELL_PROMPT "xsh $ "
//! Welcomeメッセージ
#define SHELL_STRTMSG "Welcome to Xinu!\n"
//! XINUシェル終了時のメッセージ
#define SHELL_EXITMSG "Shell closed\n"
//! シンタックスエラー時のメッセージ
#define SHELL_SYNERRMSG "Syntax error\n"
//! コマンド実行時にプロセスを生成できなかった場合のエラーメッセージ
#define SHELL_CREATMSG "Cannot create process\n"
//! インプットとして用いるファイルが開けなかった場合のエラーメッセージ
#define SHELL_INERRMSG "Cannot open file %s for input\n"
//! アウトプットとして用いるファイルが開けなかった場合のエラーメッセージ
#define SHELL_OUTERRMSG "Cannot open file %s for output\n"
//! I/Oリダイレクトできなかった場合もしくはバックグラウンドのXINUシェルビルトインコマンドエラー用のメッセージ
#define SHELL_BGERRMSG "Cannot redirect I/O or background a builtin\n"

//! LF改行コード'\n'（字句解析時に用いる）
#define SH_NEWLINE '\n'
//! End of File = Ctrl-D（字句解析時に用いる）
#define SH_EOF '\04'
//! アンパサンド文字'&'（字句解析時に用いる）
#define SH_AMPER '&'
//! ブランク（空白）文字（字句解析時に用いる）
#define SH_BLANK ' '
//! TAB文字（字句解析時に用いる）
#define SH_TAB '\t'
//! シングルクォート文字'''（字句解析時に用いる）
#define SH_SQUOTE '\''
//! ダブルクォート文字'"'（字句解析時に用いる）
#define SH_DQUOTE '"'
//! 小なり記号'<'
#define SH_LESS '<'
//! 大なり記号'>'
#define SH_GREATER '>'

//! アンパサンド'&'トークン
#define SH_TOK_AMPER 0
//! 小なり'<'トークン
#define SH_TOK_LESS 1
//! 大なり'>'トークン
#define SH_TOK_GREATER 2
//! その他（'&'、'<'、'>以外'）のトークン（例：英数字文字列）
#define SH_TOK_OTHER 3

//! XINUシェルの処理成功
#define SHELL_OK 0
//! XINUシェルの処理失敗
#define SHELL_ERROR 1
//! XINUシェルを終了させる返り値
#define SHELL_EXIT -3

/* Structure of an entry in the table of shell commands */

/**
 * @struct cmdent
 * @brief XINUシェルコマンドエントリテーブル用の構造体
 * @details 本構造体1個が1コマンド分であり、本構造体の配列でXINUシェルコマンドを全て管理する。
 */
struct cmdent
{
	//! コマンド名称
	char *cname;
	//! ビルトインコマンドかどうか
	bool8 cbuiltin;
	//! コマンドの機能を提供する関数（正確には関数ポインタ）
	int32 (*cfunc)(int32, char *[]);
};

//! XINUシェルが提供するコマンドの数
extern uint32 ncmd;
//! XINUシェルが提供するコマンドを管理する配列
extern const struct cmdent cmdtab[];
