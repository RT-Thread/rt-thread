/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-25 16:44:23
 * @LastEditTime: 2021-04-25 16:44:23
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */
#include "ft_debug.h"

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
void Ft_DumpHexByte(const u8 *ptr, ft_base_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        Ft_printf("0x%08X: ", ptr + i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                Ft_printf("%02X ", buf[i + j]);
            else
                Ft_printf("   ");
        Ft_printf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                Ft_printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        Ft_printf("\r\n");
    }
}

void Ft_DumpHexWord(const u32 *ptr, ft_base_t buflen)
{
    u32 *buf = (u32 *)ptr;
    int i, j;
    buflen = buflen / 4;
    for (i = 0; i < buflen; i += 4)
    {
        Ft_printf("0x%08X: ", ptr + i);

        for (j = 0; j < 4; j++)
        {
            if (i + j < buflen)
            {
                Ft_printf("%08X ", buf[i + j]);
            }
            else
            {
                Ft_printf("   ");
            }
        }

        Ft_printf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                Ft_printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        Ft_printf("\r\n");
    }
}
