/**
 * @file debug.c
 * @brief メモリの内容をASCIIか16進数で表示する。
 */
#include <xinu.h>
#include <stdio.h>
#include <debug.h>

// ByteをASCIIか16進数でSTDOUT（標準出力）に出力するhexdump_print()の宣言
static void hexdump_print(byte, byte);

/**
 * @brief ByteをASCIIか16進数でSTDOUT（標準出力）に出力する。
 * @param[in] data 出力するデータ（Byte）
 * @param[in] mode ASCII（DEBUG_ASCII）か16進数（DEBUG_HEX）かの指定
 * @note ASCIIの場合は、文字がスペース(0x20)から~(0x7E)までの範囲内の場合はそのまま出力し、<br>
 * 前述の範囲外の場合は"."に置換して出力する。<br>
 */
static void hexdump_print(
    byte data, /* Item to print		*/
    byte mode  /* ASCII or hex mode		*/
)
{
    switch (mode)
    {
    case DEBUG_ASCII:
        data = (' ' <= data && data <= '~') ? data : '.';
        fprintf(stdout, "%c", data);
        break;
    case DEBUG_HEX:
        fprintf(stdout, "%02x ", data);
        break;
    default:
        break;
    }
}

/**
 * @brief メモリ内容をダンプする。
 * @param[in] buffer ダンプしたいメモリ領域の開始アドレス
 * @param[in] length メモリ領域の長さ（byte）
 * @param[in] canon 16進数とASCIIを出力する場合はTRUE、16進数のみの場合はFALSEを指定する。
 * @note char test[128] = "abcdefghijklmnopqrstuvwxyz";をダンプした例を以下に示す。<br>
 * 076b08b0  61 62 63 64 65 66 67 68  69 6a 6b 6c 6d 6e 6f 70  |abcdefghijklmnop|<br>
 * 076b08c0  71 72 73 74 75 76 77 78  79 7a 00 00 00 00 00 00  |qrstuvwxyz......|<br>
 * 076b08d0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|<br>
 * 076b08e0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|<br>
 * 076b08f0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|<br>
 * 076b0900  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|<br>
 * 076b0910  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|<br>
 * 076b0920  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|<br>
 * ※ ASCIIを出力しない設定の場合は、右側の| |で囲まれた部分は出力されない。
 */
void hexdump(void *buffer, uint32 length, bool8 canon)
{
    uint32 m, n, remain;

    byte *b = (byte *)buffer;

    for (n = 0; n < length; n += 0x10)
    {
        fprintf(stdout, "%08x ", (uint32)buffer + n);

        remain = length - n;

        for (m = 0; m < remain && m < 0x10; m++)
        {
            if (m % 0x08 == 0)
            {
                fprintf(stdout, " ");
            }
            hexdump_print(b[n + m], DEBUG_HEX);
        }

        /* Pad the rest if needed */
        if (remain < 0x10)
        {
            for (m = 0; m < 0x10 - remain; m++)
            {
                if ((0 != m) && (0 == m % 0x08))
                {
                    fprintf(stdout, " ");
                }
                fprintf(stdout, "   ");
            }
        }

        if (canon == TRUE)
        {
            fprintf(stdout, " |");
            for (m = 0; m < remain && m < 0x10; m++)
            {
                hexdump_print(b[n + m], DEBUG_ASCII);
            }
            fprintf(stdout, "|");
        }
        fprintf(stdout, "\n");
    }
}
