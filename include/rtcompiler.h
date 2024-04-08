/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-18     Shell        Separate the compiler porting from rtdef.h
 */
#ifndef __RT_COMPILER_H__
#define __RT_COMPILER_H__

#include <rtconfig.h>

#if defined(__ARMCC_VERSION)        /* ARM Compiler */
#define rt_section(x)               __attribute__((section(x)))
#define rt_used                     __attribute__((used))
#define rt_align(n)                 __attribute__((aligned(n)))
#define rt_weak                     __attribute__((weak))
#define rt_typeof                   typeof
#define rt_noreturn
#define rt_inline                   static __inline
#define rt_always_inline            rt_inline
#elif defined (__IAR_SYSTEMS_ICC__) /* for IAR Compiler */
#define rt_section(x)               @ x
#define rt_used                     __root
#define PRAGMA(x)                   _Pragma(#x)
#define rt_align(n)                 PRAGMA(data_alignment=n)
#define rt_weak                     __weak
#define rt_typeof                   __typeof
#define rt_noreturn
#define rt_inline                   static inline
#define rt_always_inline            rt_inline
#elif defined (__GNUC__)            /* GNU GCC Compiler */
#define __RT_STRINGIFY(x...)        #x
#define RT_STRINGIFY(x...)          __RT_STRINGIFY(x)
#define rt_section(x)               __attribute__((section(x)))
#define rt_used                     __attribute__((used))
#define rt_align(n)                 __attribute__((aligned(n)))
#define rt_weak                     __attribute__((weak))
#define rt_typeof                   __typeof__
#define rt_noreturn                 __attribute__ ((noreturn))
#define rt_inline                   static __inline
#define rt_always_inline            static inline __attribute__((always_inline))
#elif defined (__ADSPBLACKFIN__)    /* for VisualDSP++ Compiler */
#define rt_section(x)               __attribute__((section(x)))
#define rt_used                     __attribute__((used))
#define rt_align(n)                 __attribute__((aligned(n)))
#define rt_weak                     __attribute__((weak))
#define rt_typeof                   typeof
#define rt_noreturn
#define rt_inline                   static inline
#define rt_always_inline            rt_inline
#elif defined (_MSC_VER)            /* for Visual Studio Compiler */
#define rt_section(x)
#define rt_used
#define rt_align(n)                 __declspec(align(n))
#define rt_weak
#define rt_typeof                   typeof
#define rt_noreturn
#define rt_inline                   static __inline
#define rt_always_inline            rt_inline
#elif defined (__TI_COMPILER_VERSION__) /* for TI CCS Compiler */
/**
 * The way that TI compiler set section is different from other(at least
 * GCC and MDK) compilers. See ARM Optimizing C/C++ Compiler 5.9.3 for more
 * details.
 */
#define rt_section(x)               __attribute__((section(x)))
#ifdef __TI_EABI__
#define rt_used                     __attribute__((retain)) __attribute__((used))
#else
#define rt_used                     __attribute__((used))
#endif
#define PRAGMA(x)                   _Pragma(#x)
#define rt_align(n)                 __attribute__((aligned(n)))
#ifdef __TI_EABI__
#define rt_weak                     __attribute__((weak))
#else
#define rt_weak
#endif
#define rt_typeof                   typeof
#define rt_noreturn
#define rt_inline                   static inline
#define rt_always_inline            rt_inline
#elif defined (__TASKING__)         /* for TASKING Compiler */
#define rt_section(x)               __attribute__((section(x)))
#define rt_used                     __attribute__((used, protect))
#define PRAGMA(x)                   _Pragma(#x)
#define rt_align(n)                 __attribute__((__align(n)))
#define rt_weak                     __attribute__((weak))
#define rt_typeof                   typeof
#define rt_noreturn
#define rt_inline                   static inline
#define rt_always_inline            rt_inline
#else                              /* Unkown Compiler */
    #error not supported tool chain
#endif /* __ARMCC_VERSION */

#endif /* __RT_COMPILER_H__ */
