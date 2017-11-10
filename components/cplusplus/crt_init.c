/*
* File      : crt_init.c
* This file is part of Device File System in RT-Thread RTOS
* COPYRIGHT (C) 2008-2015, RT-Thread Development Team
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
* 2016-06-28     Bernard      Add _init/_fini routines for GCC.
* 2016-10-02     Bernard      Add WEAK for cplusplus_system_init routine.
*/

#include <rtthread.h>

#ifdef __CC_ARM
extern void $Super$$__cpp_initialize__aeabi_(void);
/* we need to change the cpp_initialize order */
void $Sub$$__cpp_initialize__aeabi_(void)
{
    /* empty */
}
#elif defined(__GNUC__) && !defined(__CS_SOURCERYGXX_MAJ__)
/* The _init()/_fini() routines has been defined in codesourcery g++ lite */
void _init()
{
}

void _fini()
{
}

RT_WEAK void *__dso_handle = 0;

#endif

RT_WEAK
int cplusplus_system_init(void)
{
#if defined(__GNUC__) && !defined(__CC_ARM)
    typedef void (*pfunc) ();
    extern pfunc __ctors_start__[];
    extern pfunc __ctors_end__[];
    pfunc *p;

    for (p = __ctors_start__; p < __ctors_end__; p++)
        (*p)();

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

