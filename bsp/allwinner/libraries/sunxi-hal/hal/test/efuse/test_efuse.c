#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hal_cmd.h>

#undef  HEXDUMP_LINE_CHR_CNT
#define HEXDUMP_LINE_CHR_CNT 16
static int sunxi_hexdump(const unsigned char *buf, int bytes)
{
    unsigned char line[HEXDUMP_LINE_CHR_CNT] = {0};
    int addr;

    for (addr = 0; addr < bytes; addr += HEXDUMP_LINE_CHR_CNT)
    {
        int len = ((bytes-addr)<HEXDUMP_LINE_CHR_CNT ? (bytes-addr) : HEXDUMP_LINE_CHR_CNT);
    int i;

        memcpy(line, buf + addr, len);
        memset(line + len, 0, HEXDUMP_LINE_CHR_CNT - len);

        /* print addr */
        printf("0x%.8X: ", addr);
        /* print hex */
        for (i = 0; i < HEXDUMP_LINE_CHR_CNT; i++)
        {
            if (i < len)
            {
                printf("%.2X ", line[i]);
            }
            else { printf("   "); }
        }
        /* print char */
        printf("|");
        for (i = 0; i < HEXDUMP_LINE_CHR_CNT; i++)
        {
            if (i < len)
            {
                if (line[i] >= 0x20 && line[i] <= 0x7E)
                {
                    printf("%c", line[i]);
                }
                else
                {
                    printf(".");
                }
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    return 0;
}


int hal_efuse_get_chipid(unsigned char *buffer);

int cmd_test_efuse(int argc, char **argv)
{
    char buffer[32] = {0};

    hal_efuse_get_chipid(buffer);
    sunxi_hexdump(buffer, sizeof(buffer));

    /* TODO: add more APIs to test */
    printf("===================================\n");
    printf("Test Finished.\n");

    return 0;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_test_efuse, hal_efuse, efuse hal APIs tests)

