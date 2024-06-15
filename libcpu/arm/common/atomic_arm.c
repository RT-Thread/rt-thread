/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-27     flybreak       the first version
 */

#include <rtthread.h>

#if defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
#include <intrinsics.h>
#include <iccarm_builtin.h>
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
