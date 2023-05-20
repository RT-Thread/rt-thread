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

#if defined(__ARMCC_VERSION)
extern void $Super$$__cpp_initialize__aeabi_(void);
/* we need to change the cpp_initialize order */
rt_weak void $Sub$$__cpp_initialize__aeabi_(void)
{
    /* empty */
}
#elif defined(__GNUC__) && !defined(__CS_SOURCERYGXX_MAJ__)
/* The _init()/_fini() routines has been defined in codesourcery g++ lite */
rt_weak void _init()
{
}

rt_weak void _fini()
{
}

rt_weak void *__dso_handle = 0;

#endif

/**
 * @brief   This function initializes the C++ runtime environment for ARM and GCC compilers.
 *
 * @note    If there is no SHT$$INIT_ARRAY section, calling $Super$$__cpp_initialize__aeabi_() will cause an error
 *          in ARMCC compiler. Therefore, this function manually iterates through the base addresses of the
 *          SHT$$INIT_ARRAY section to call the constructor functions of each object. In GCC compiler, this function
 *          uses the __ctors_start__ and __ctors_end__ global variables to determine the range of constructor function
 *          pointers and calls each constructor function of every object in that range.
 *
 * @return  Returns 0 if the initialization of the C++ runtime environment is successful. Otherwise, it returns
 *          an error code indicating the failure of the operation.
 */
rt_weak int cplusplus_system_init(void)
{
#if defined(__ARMCC_VERSION)
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
