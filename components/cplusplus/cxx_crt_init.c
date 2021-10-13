/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-12-03     Bernard      Add copyright header.
 * 2014-12-29     Bernard      Add cplusplus initialization for ARMCC.
 * 2016-06-28     Bernard      Add _init/_fini routines for GCC.
 * 2016-10-02     Bernard      Add WEAK for cplusplus_system_init routine.
 */

#include <rtthread.h>

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern void $Super$$__cpp_initialize__aeabi_(void);
/* we need to change the cpp_initialize order */
RT_WEAK void $Sub$$__cpp_initialize__aeabi_(void)
{
    /* empty */
}
#elif defined(__GNUC__) && !defined(__CS_SOURCERYGXX_MAJ__)
/* The _init()/_fini() routines has been defined in codesourcery g++ lite */
RT_WEAK void _init()
{
}

RT_WEAK void _fini()
{
}

RT_WEAK void *__dso_handle = 0;

#endif

RT_WEAK int cplusplus_system_init(void)
{
#if defined(__CC_ARM) || defined(__CLANG_ARM)
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
        PROC *proc = (PROC *)((const char *)base + *base);
        (*proc)();
    }
#elif defined(__GNUC__)
    typedef void(*pfunc)();
    extern pfunc __ctors_start__[];
    extern pfunc __ctors_end__[];
    pfunc *p;

    for (p = __ctors_start__; p < __ctors_end__; p++)
        (*p)();
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(cplusplus_system_init);
