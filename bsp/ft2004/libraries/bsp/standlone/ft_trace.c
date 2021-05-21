/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-15 11:27:24
 * @LastEditTime: 2021-05-25 10:52:32
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#include "ft_trace.h"
#include "ft_printf.h"


void Sdmmc_TraceHeapAlloc(const char *tag)
{

}

void dump_hex(const u8 *ptr, u32 buflen, const char *tag)
{
    unsigned char *buf = (unsigned char *)ptr;
    u32 i, j;

    Ft_printf("dump hex for %s\r\n", tag);
    for (i = 0; i < buflen; i += 16)
    {
        Ft_printf("%08X: ", ptr + i);

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                Ft_printf("%02X ", buf[i + j]);
            }
            else
            {
                Ft_printf("   ");
            }
        }
        Ft_printf(" ");

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                Ft_printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        Ft_printf("\r\n");
    }
}
