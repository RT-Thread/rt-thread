/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: ft_debug.c
 * Date: 2021-04-25 16:44:23
 * LastEditTime: 2022-02-17 18:04:50
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "fdebug.h"
#include "fprintf.h"
#include "stdio.h"

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
void FtDumpHexByte(const u8 *ptr, u32 buflen)
{
    u8 *buf = (u8 *)ptr;
    fsize_t i, j;

    for (i = 0; i < buflen; i += 16)
    {
        printf("%p: ", ptr + i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                printf("%02X ", buf[i + j]);
            else
                printf("   ");
        printf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                printf("%c", (char)(__is_print(buf[i + j]) ? buf[i + j] : '.'));
        printf("\r\n");
    }
}

void FtDumpHexByteDebug(const u8 *ptr, u32 buflen)
{
    u8 *buf = (u8 *)ptr;
    fsize_t i, j;

    for (i = 0; i < buflen; i += 16)
    {
        f_printf("%x: ", ptr + i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                f_printf("%x ", buf[i + j]);
            else
                f_printf("   ");
        f_printf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                f_printf("%c", (char)(__is_print(buf[i + j]) ? buf[i + j] : '.'));
        f_printf("\r\n");
    }
}


void FtDumpHexWord(const u32 *ptr, u32 buflen)
{
    u32 *buf = (u32 *)ptr;
    u8 *char_data = (u8 *)ptr;
    fsize_t i, j;
    buflen = buflen / 4;
    for (i = 0; i < buflen; i += 4)
    {
        printf("%p: ", ptr + i);

        for (j = 0; j < 4; j++)
        {
            if (i + j < buflen)
            {
                printf("%lx ", buf[i + j]);
            }
            else
            {
                printf("   ");
            }
        }

        printf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                printf("%c", (char)(__is_print(char_data[i + j]) ? char_data[i + j] : '.'));

        printf("\r\n");
    }
}
