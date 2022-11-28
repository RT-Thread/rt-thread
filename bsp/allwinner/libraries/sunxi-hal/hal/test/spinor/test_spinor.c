/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY'S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS'SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY'S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <hal_cmd.h>
#include <sunxi_hal_spinor.h>

static int init_flag = 0;

#ifndef MIN
#define MIN(a, b) (a > b ? b : a)
#endif

#define HEXDUMP_LINE_CHR_CNT 16
int spinor_hexdump(const unsigned char *buf, int bytes)
{
    unsigned char line[HEXDUMP_LINE_CHR_CNT] = {0};
    int addr;

    for (addr = 0; addr < bytes; addr += HEXDUMP_LINE_CHR_CNT)
    {
        int len = MIN(bytes - addr, HEXDUMP_LINE_CHR_CNT), i;

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
            else
            {
                printf("   ");
            }
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

static int cmd_test_spinor(int argc, const char **argv)
{
    int ret;
    uint32_t addr = 3 * 1024 *1024;
    uint32_t len = 4 * 1024;

    printf("Run spinor test");

    ret = hal_spinor_init(0);
    if (ret)
    {
        printf("init spinor failed\n");
        ret = -1;
        goto out;
    }

    char *buf = (char *)malloc(512);
    if (buf == NULL)
    {
        printf("allocate memnory failed\n");
        ret = -1;;
        goto out;
    }
    memset(buf, 0, 512);

    printf("read data:\n");
    ret = hal_spinor_read_data(addr, buf, 512);
    if (ret <= 0)
    {
        printf("spinor read data failed\n");
        ret = -1;
        goto error;
    }
    spinor_hexdump(buf, 512);
    printf("\n");

    printf("erase data:\n");
    ret = hal_spinor_erase_sector(addr, len);
    if (ret)
    {
        printf("spinor erase data failed\n");
        ret = -1;
        goto error;
    }

    printf("write data:\n");
    memset(buf, 0xa5, 512);
    ret = hal_spinor_program_data(addr, buf, 512);
    if (ret <= 0)
    {
        printf("spinor write data failed\n");
        ret = -1;
        goto error;
    }

    printf("after write data:\n");
    memset(buf, 0, 512);
    ret = hal_spinor_read_data(addr, buf, 512);
    if (ret <= 0)
    {
        printf("spinor read data failed\n");
        ret = -1;
        goto error;
    }
    spinor_hexdump(buf, 512);

error:
    free(buf);
out:
    return ret;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_test_spinor, hal_spinor, spinor hal APIs tests)
