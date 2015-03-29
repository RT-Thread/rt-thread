/*
* File      : crt_init.c
* This file is part of Device File System in RT-Thread RTOS
* COPYRIGHT (C) 2008-2011, RT-Thread Development Team
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
* Change Logs:
* Date           Author       Notes
* 2014-12-03     Bernard      Add copyright header.
* 2014-12-29     Bernard      Add cplusplus initialization for ARMCC.
*/

#include <rtthread.h>

#ifdef __CC_ARM
extern void $Super$$__cpp_initialize__aeabi_(void);
/* we need to change the cpp_initialize order */
void $Sub$$__cpp_initialize__aeabi_(void)
{
	/* empty */
}
#endif

int cplusplus_system_init(void)
{
#if defined(__GNUC__) && !defined(__CC_ARM)
    extern unsigned char __ctors_start__;
    extern unsigned char __ctors_end__;
    typedef void (*func)(void);

    /* .ctors initalization */
    func *ctors_func;

    for (ctors_func = (func *)&__ctors_start__;
         ctors_func < (func *)&__ctors_end__;
         ctors_func ++)
    {
        (*ctors_func)();
    }
#elif defined(__CC_ARM)
    /* If there is no SHT$$INIT_ARRAY, calling
     * $Super$$__cpp_initialize__aeabi_() will cause fault. At least until Keil5.12
     * the problem still exists. So we have to initialize the C++ runtime by ourself.
     */
    typedef void PROC();
    extern const unsigned long SHT$$INIT_ARRAY$$Base[];
    extern const unsigned long SHT$$INIT_ARRAY$$Limit[];
    
    const unsigned long *base = SHT$$INIT_ARRAY$$Base;
    const unsigned long *lim  = SHT$$INIT_ARRAY$$Limit;

    for (; base != lim; base++)
    {
        PROC *proc = (PROC*)((const char*)base + *base);
        (*proc)();
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(cplusplus_system_init);
