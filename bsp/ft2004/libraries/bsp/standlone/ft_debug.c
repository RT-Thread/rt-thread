/*
 * @[H]: Copyright (C) 2014-2021 Phytium Technology.  All rights reserved.
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  Use of the Software is limited solely to applications:
 *  (a) running on a Phytium device, or
 *  (b) that interact with a Phytium device through a bus or interconnect.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  PHYTIUM  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 *  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 * 
 *  Except as contained in this notice, the name of the Phytium shall not be used
 *  in advertising or otherwise to promote the sale, use or other dealings in
 *  this Software without prior written authorization from Phytium. 
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