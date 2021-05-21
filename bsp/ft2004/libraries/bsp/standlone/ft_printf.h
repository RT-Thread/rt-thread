/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:30:52
 * @Description:  This files is for printf functions
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef Ft_printf_H
#define Ft_printf_H

#include <stdarg.h>
#include "ft_types.h"

// #define NEED_CLOSE_ISR
#define PRINTF_BUFFER_LENGTH 4096

typedef s32 (*vsprintf_p)(char *buf, const char *format, va_list arg_ptr);

void Ft_vsprintfRegister(vsprintf_p f);
void Ft_printf(const char *fmt, ...);
char *Ft_itoa(int num, char *str, int radix);

#endif // !