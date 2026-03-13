/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-27     flybreak     the first version
 * 2026-03-09     wdfk-prog    add 8/16-bit atomic operations support
 */

#include <rtthread.h>

#if defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
#include <intrinsics.h>
#include <iccarm_builtin.h>
#endif

/**
 \brief   LDR Exclusive (8 bit)
 \details Executes a exclusive LDR instruction for 8 bit values.
 \param [in]    ptr  Pointer to data
 \return        value of type uint8_t at (*ptr)
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __LDREXB
#define __LDREXB        (uint8_t)__builtin_arm_ldrex
#endif
#define __LDREXB_PRIV(ptr)                                                     ((rt_atomic8_t)__LDREXB((volatile uint8_t *)(ptr)))
#elif defined(__ARMCC_VERSION)          /* ARM Compiler V5 */
#if __ARMCC_VERSION < 5060020
#define __LDREXB_PRIV(ptr)                                                     ((rt_atomic8_t ) __ldrex(ptr))
#else
#define __LDREXB_PRIV(ptr)       _Pragma("push") _Pragma("diag_suppress 3731") ((rt_atomic8_t ) __ldrex(ptr))  _Pragma("pop")
#endif
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
_Pragma("inline=forced") __intrinsic rt_atomic8_t __LDREXB_PRIV(volatile rt_atomic8_t *ptr)
{
    return __iar_builtin_LDREXB((volatile unsigned char *)ptr);
}
#elif defined (__GNUC__)                /* GNU GCC Compiler */
__attribute__((always_inline)) static inline rt_atomic8_t __LDREXB_PRIV(volatile rt_atomic8_t *addr)
{
    uint32_t result;

#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
    __asm volatile ("ldrexb %0, %1" : "=r" (result) : "Q" (*addr) );
#else
    __asm volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );
#endif
    return (rt_atomic8_t)result;
}
#endif

/**
 \brief   STR Exclusive (8 bit)
 \details Executes a exclusive STR instruction for 8 bit values.
 \param [in]  value  Value to store
 \param [in]    ptr  Pointer to location
 \return          0  Function succeeded
 \return          1  Function failed
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __STREXB
#define __STREXB        (uint32_t)__builtin_arm_strex
#endif
#define __STREXB_PRIV(value, ptr)                                              ((rt_atomic_t)__STREXB((uint8_t)(value), (volatile uint8_t *)(ptr)))
#elif defined(__ARMCC_VERSION)          /* ARM Compiler V5 */
#if __ARMCC_VERSION < 5060020
#define __STREXB_PRIV(value, ptr)                                              __strex(value, ptr)
#else
#define __STREXB_PRIV(value, ptr) _Pragma("push") _Pragma("diag_suppress 3731") __strex(value, ptr) _Pragma("pop")
#endif
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
_Pragma("inline=forced") __intrinsic rt_atomic_t __STREXB_PRIV(rt_atomic8_t value, volatile rt_atomic8_t *ptr)
{
    return __iar_builtin_STREXB(value, (volatile unsigned char *)ptr);
}
#elif defined (__GNUC__)                /* GNU GCC Compiler */
__attribute__((always_inline)) static inline rt_atomic_t __STREXB_PRIV(rt_atomic8_t value, volatile rt_atomic8_t *addr)
{
    rt_atomic_t result;

    __asm volatile ("strexb %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
    return result;
}
#endif

/**
 \brief   LDR Exclusive (16 bit)
 \details Executes a exclusive LDR instruction for 16 bit values.
 \param [in]    ptr  Pointer to data
 \return        value of type uint16_t at (*ptr)
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __LDREXH
#define __LDREXH        (uint16_t)__builtin_arm_ldrex
#endif
#define __LDREXH_PRIV(ptr)                                                     ((rt_atomic16_t)__LDREXH((volatile uint16_t *)(ptr)))
#elif defined(__ARMCC_VERSION)          /* ARM Compiler V5 */
#if __ARMCC_VERSION < 5060020
#define __LDREXH_PRIV(ptr)                                                     ((rt_atomic16_t ) __ldrex(ptr))
#else
#define __LDREXH_PRIV(ptr)       _Pragma("push") _Pragma("diag_suppress 3731") ((rt_atomic16_t ) __ldrex(ptr))  _Pragma("pop")
#endif
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
_Pragma("inline=forced") __intrinsic rt_atomic16_t __LDREXH_PRIV(volatile rt_atomic16_t *ptr)
{
    return __iar_builtin_LDREXH((volatile unsigned short *)ptr);
}
#elif defined (__GNUC__)                /* GNU GCC Compiler */
__attribute__((always_inline)) static inline rt_atomic16_t __LDREXH_PRIV(volatile rt_atomic16_t *addr)
{
    uint32_t result;

#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
    __asm volatile ("ldrexh %0, %1" : "=r" (result) : "Q" (*addr) );
#else
    __asm volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );
#endif
    return (rt_atomic16_t)result;
}
#endif

/**
 \brief   STR Exclusive (16 bit)
 \details Executes a exclusive STR instruction for 16 bit values.
 \param [in]  value  Value to store
 \param [in]    ptr  Pointer to location
 \return          0  Function succeeded
 \return          1  Function failed
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __STREXH
#define __STREXH        (uint32_t)__builtin_arm_strex
#endif
#define __STREXH_PRIV(value, ptr)                                              ((rt_atomic_t)__STREXH((uint16_t)(value), (volatile uint16_t *)(ptr)))
#elif defined(__ARMCC_VERSION)          /* ARM Compiler V5 */
#if __ARMCC_VERSION < 5060020
#define __STREXH_PRIV(value, ptr)                                              __strex(value, ptr)
#else
#define __STREXH_PRIV(value, ptr) _Pragma("push") _Pragma("diag_suppress 3731") __strex(value, ptr) _Pragma("pop")
#endif
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
_Pragma("inline=forced") __intrinsic rt_atomic_t __STREXH_PRIV(rt_atomic16_t value, volatile rt_atomic16_t *ptr)
{
    return __iar_builtin_STREXH(value, (volatile unsigned short *)ptr);
}
#elif defined (__GNUC__)                /* GNU GCC Compiler */
__attribute__((always_inline)) static inline rt_atomic_t __STREXH_PRIV(rt_atomic16_t value, volatile rt_atomic16_t *addr)
{
    rt_atomic_t result;

    __asm volatile ("strexh %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
    return result;
}
#endif

/**
 \brief   LDR Exclusive (32 bit)
 \details Executes a exclusive LDR instruction for 32 bit values.
 \param [in]    ptr  Pointer to data
 \return        value of type uint32_t at (*ptr)
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#define __LDREXW        (rt_atomic_t)__builtin_arm_ldrex
#elif defined(__ARMCC_VERSION)          /* ARM Compiler V5 */
#if __ARMCC_VERSION < 5060020
#define __LDREXW(ptr)                                                        ((rt_atomic_t ) __ldrex(ptr))
#else
#define __LDREXW(ptr)          _Pragma("push") _Pragma("diag_suppress 3731") ((rt_atomic_t ) __ldrex(ptr))  _Pragma("pop")
#endif
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
_Pragma("inline=forced") __intrinsic rt_atomic_t __LDREXW(volatile rt_atomic_t *ptr)
{
    return __iar_builtin_LDREX((volatile unsigned int *)ptr);
}
#elif defined (__GNUC__)                /* GNU GCC Compiler */
__attribute__((always_inline))     static inline rt_atomic_t __LDREXW(volatile rt_atomic_t *addr)
{
    rt_atomic_t result;

    __asm volatile ("ldrex %0, %1" : "=r" (result) : "Q" (*addr) );
    return result;
}
#endif

/**
 \brief   STR Exclusive (32 bit)
 \details Executes a exclusive STR instruction for 32 bit values.
 \param [in]  value  Value to store
 \param [in]    ptr  Pointer to location
 \return          0  Function succeeded
 \return          1  Function failed
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#define __STREXW        (rt_atomic_t)__builtin_arm_strex
#elif defined(__ARMCC_VERSION)          /* ARM Compiler V5 */
#if __ARMCC_VERSION < 5060020
#define __STREXW(value, ptr)                                                 __strex(value, ptr)
#else
#define __STREXW(value, ptr)   _Pragma("push") _Pragma("diag_suppress 3731") __strex(value, ptr)        _Pragma("pop")
#endif
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
_Pragma("inline=forced") __intrinsic rt_atomic_t __STREXW(rt_atomic_t value, volatile rt_atomic_t *ptr)
{
    return __STREX(value, (unsigned int *)ptr);
}
#elif defined (__GNUC__)                /* GNU GCC Compiler */
__attribute__((always_inline))     static inline rt_atomic_t __STREXW(volatile rt_atomic_t value, volatile rt_atomic_t *addr)
{
    rt_atomic_t result;

    __asm volatile ("strex %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" (value) );
    return result;
}
#endif

rt_atomic_t rt_hw_atomic_load(volatile rt_atomic_t *ptr)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(oldval, ptr)) != 0U);
    return oldval;
}

void rt_hw_atomic_store(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    do
    {
        __LDREXW(ptr);
    } while ((__STREXW(val, ptr)) != 0U);
}

rt_atomic8_t rt_hw_atomic_load8(volatile rt_atomic8_t *ptr)
{
    rt_atomic8_t oldval;
    do
    {
        oldval = __LDREXB_PRIV(ptr);
    } while ((__STREXB_PRIV(oldval, ptr)) != 0U);
    return oldval;
}

void rt_hw_atomic_store8(volatile rt_atomic8_t *ptr, rt_atomic8_t val)
{
    do
    {
        __LDREXB_PRIV(ptr);
    } while ((__STREXB_PRIV(val, ptr)) != 0U);
}

rt_atomic16_t rt_hw_atomic_load16(volatile rt_atomic16_t *ptr)
{
    rt_atomic16_t oldval;
    do
    {
        oldval = __LDREXH_PRIV(ptr);
    } while ((__STREXH_PRIV(oldval, ptr)) != 0U);
    return oldval;
}

void rt_hw_atomic_store16(volatile rt_atomic16_t *ptr, rt_atomic16_t val)
{
    do
    {
        __LDREXH_PRIV(ptr);
    } while ((__STREXH_PRIV(val, ptr)) != 0U);
}

rt_atomic_t rt_hw_atomic_add(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(oldval + val, ptr)) != 0U);
    return oldval;
}

rt_atomic_t rt_hw_atomic_sub(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(oldval - val, ptr)) != 0U);
    return oldval;
}

rt_atomic8_t rt_hw_atomic_and8(volatile rt_atomic8_t *ptr, rt_atomic8_t val)
{
    rt_atomic8_t oldval;
    do
    {
        oldval = __LDREXB_PRIV(ptr);
    } while ((__STREXB_PRIV((rt_atomic8_t)(oldval & val), ptr)) != 0U);
    return oldval;
}

rt_atomic8_t rt_hw_atomic_or8(volatile rt_atomic8_t *ptr, rt_atomic8_t val)
{
    rt_atomic8_t oldval;
    do
    {
        oldval = __LDREXB_PRIV(ptr);
    } while ((__STREXB_PRIV((rt_atomic8_t)(oldval | val), ptr)) != 0U);
    return oldval;
}

rt_atomic16_t rt_hw_atomic_and16(volatile rt_atomic16_t *ptr, rt_atomic16_t val)
{
    rt_atomic16_t oldval;
    do
    {
        oldval = __LDREXH_PRIV(ptr);
    } while ((__STREXH_PRIV((rt_atomic16_t)(oldval & val), ptr)) != 0U);
    return oldval;
}

rt_atomic16_t rt_hw_atomic_or16(volatile rt_atomic16_t *ptr, rt_atomic16_t val)
{
    rt_atomic16_t oldval;
    do
    {
        oldval = __LDREXH_PRIV(ptr);
    } while ((__STREXH_PRIV((rt_atomic16_t)(oldval | val), ptr)) != 0U);
    return oldval;
}

rt_atomic_t rt_hw_atomic_and(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(oldval & val, ptr)) != 0U);
    return oldval;
}

rt_atomic_t rt_hw_atomic_or(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(oldval | val, ptr)) != 0U);
    return oldval;
}

rt_atomic_t rt_hw_atomic_xor(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(oldval ^ val, ptr)) != 0U);
    return oldval;
}

rt_atomic_t rt_hw_atomic_exchange(volatile rt_atomic_t *ptr, rt_atomic_t val)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(val, ptr)) != 0U);
    return oldval;
}

void rt_hw_atomic_flag_clear(volatile rt_atomic_t *ptr)
{
    do
    {
        __LDREXW(ptr);
    } while ((__STREXW(0, ptr)) != 0U);
}

rt_atomic_t rt_hw_atomic_flag_test_and_set(volatile rt_atomic_t *ptr)
{
    rt_atomic_t oldval;
    do
    {
        oldval = __LDREXW(ptr);
    } while ((__STREXW(1, ptr)) != 0U);
    return oldval;
}

rt_atomic_t rt_hw_atomic_compare_exchange_strong(volatile rt_atomic_t *ptr, rt_atomic_t *old, rt_atomic_t new)
{
    rt_atomic_t result;
    rt_atomic_t temp = *old;
    do
    {
        result = __LDREXW(ptr);
        if (result != temp)
        {
            *old = result;
            __STREXW(result, ptr);
            break;
        }
    } while ((__STREXW(new, ptr)) != 0U);
    return (result == temp);
}
