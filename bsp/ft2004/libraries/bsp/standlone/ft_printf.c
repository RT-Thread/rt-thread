/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-26 15:20:14
 * @Description:  This files is for printf function
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_printf.h"
#include "stdio.h"
#include "ft_aarch32_asm.h"

static char print_buffer[PRINTF_BUFFER_LENGTH];

extern void outbyte(char byte);

vsprintf_p Vsprintf_pFun = (vsprintf_p)vsprintf;

void Ft_vsprintfRegister(vsprintf_p f)
{
    Vsprintf_pFun = f;
}

void Ft_printf(const char *fmt, ...)
{
    va_list args;
    size_t i;
    size_t length;
#ifdef NEED_CLOSE_ISR
    IRQ_DISABLE();
#endif
    va_start(args, fmt);

    length = Vsprintf_pFun(print_buffer, fmt, args);
    va_end(args);
    for (i = 0; i < length; i++)
    {
        outbyte(print_buffer[i]);
    }

#ifdef NEED_CLOSE_ISR
    IRQ_ENABLE();
#endif
}

char *Ft_itoa(int num, char *str, int radix)
{
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum;
    int i = 0;
    int j;
    int k;
    char temp;

    if (radix == 10 && num < 0)
    {
        unum = (unsigned)-num;
        str[i++] = '-';
    }
    else
    {
        unum = (unsigned)num;
    }

    do
    {
        str[i++] = index[unum % (unsigned)radix];
        unum /= radix;
    } while (unum);

    str[i] = '\0';

    if (str[0] == '-')
    {
        k = 1;
    }
    else
    {
        k = 0;
    }

    for (j = k; j <= (i - 1) / 2; j++)
    {
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }

    return str;
}
