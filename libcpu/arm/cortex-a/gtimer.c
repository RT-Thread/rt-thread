/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-30     huijie.feng  first version
 */

#include "cp15.h"
#include <rtdef.h>

/** Set CNTFRQ
 *  This function assigns the given value to PL1 Physical Timer Counter Frequency Register (CNTFRQ).
 *  @param value: CNTFRQ Register value to set
 */
static inline void __set_cntfrq(rt_uint32_t value)
{
    __set_cp(15, 0, value, 14, 0, 0);
}

/** Get CNTFRQ
 *  This function returns the value of the PL1 Physical Timer Counter Frequency Register (CNTFRQ).
 *  return CNTFRQ Register value
 */
static inline rt_uint32_t __get_cntfrq(void)
{
    rt_uint32_t result;
    __get_cp(15, 0, result, 14, 0 , 0);
    return result;
}

/** Set CNTP_TVAL
 *  This function assigns the given value to PL1 Physical Timer Value Register (CNTP_TVAL).
 *  param value: CNTP_TVAL Register value to set
 */
static inline void __set_cntp_tval(rt_uint32_t value)
{
    __set_cp(15, 0, value, 14, 2, 0);
}

/** Get CNTP_TVAL
 *  This function returns the value of the PL1 Physical Timer Value Register (CNTP_TVAL).
 *  return CNTP_TVAL Register value
 */
static inline rt_uint32_t __get_cntp_tval(void)
{
    rt_uint32_t result;
    __get_cp(15, 0, result, 14, 2, 0);
    return result;
}

/** Get CNTPCT
 *  This function returns the value of the 64 bits PL1 Physical Count Register (CNTPCT).
 *  return CNTPCT Register value
 */
static inline rt_uint64_t __get_cntpct(void)
{
    rt_uint64_t result;
    __get_cp64(15, 0, result, 14);
    return result;
}

/** Set CNTP_CVAL
 *  This function assigns the given value to 64bits PL1 Physical Timer CompareValue Register (CNTP_CVAL).
 *  param value: CNTP_CVAL Register value to set
*/
static inline void __set_cntp_cval(rt_uint64_t value)
{
    __set_cp64(15, 2, value, 14);
}

/** Get CNTP_CVAL
 *  This function returns the value of the 64 bits PL1 Physical Timer CompareValue Register (CNTP_CVAL).
 *  return CNTP_CVAL Register value
 */
static inline rt_uint64_t __get_cntp_cval(void)
{
    rt_uint64_t result;
    __get_cp64(15, 2, result, 14);
    return result;
}

/** Set CNTP_CTL
 *  This function assigns the given value to PL1 Physical Timer Control Register (CNTP_CTL).
 *  param value: CNTP_CTL Register value to set
 */
static inline void __set_cntp_ctl(rt_uint32_t value)
{
    __set_cp(15, 0, value, 14, 2, 1);
}

/** Get CNTP_CTL register
 *  return CNTP_CTL Register value
 */
static inline rt_uint32_t __get_cntp_ctl(void)
{
    rt_uint32_t result;
    __get_cp(15, 0, result, 14, 2, 1);
    return result;
}

/** Configures the frequency the timer shall run at.
 *  param value The timer frequency in Hz.
 */
void gtimer_set_counter_frequency(rt_uint32_t value)
{
    __set_cntfrq(value);
    __asm__ volatile ("isb 0xF":::"memory");
}

/** Get the frequency the timer shall run at.
 *  return timer frequency in Hz.
 */
rt_uint32_t gtimer_get_counter_frequency(void)
{
    return(__get_cntfrq());
}

/** Sets the reset value of the timer.
 *  param value: The value the timer is loaded with.
 */
void gtimer_set_load_value(rt_uint32_t value)
{
    __set_cntp_tval(value);
    __asm__ volatile ("isb 0xF":::"memory");
}

/** Get the current counter value.
 *  return Current counter value.
 */
rt_uint32_t gtimer_get_current_value(void)
{
    return(__get_cntp_tval());
}

/** Get the current physical counter value.
 *  return Current physical counter value.
 */
rt_uint64_t gtimer_get_current_physical_value(void)
{
    return(__get_cntpct());
}

/** Set the physical compare value.
 *  param value: New physical timer compare value.
 */
void gtimer_set_physical_compare_value(rt_uint64_t value)
{
    __set_cntp_cval(value);
    __asm__ volatile ("isb 0xF":::"memory");
}

/** Get the physical compare value.
 *  return Physical compare value.
 */
rt_uint64_t gtimer_get_physical_compare_value(void)
{
    return(__get_cntp_cval());
}

/** Configure the timer by setting the control value.
 *  param value: New timer control value.
 */
void gtimer_set_control(rt_uint32_t value)
{
    __set_cntp_ctl(value);
    __asm__ volatile ("isb 0xF":::"memory");
}

/** Get the control value.
 *  return Control value.
 */
rt_uint32_t gtimer_get_control(void)
{
    return(__get_cntp_ctl());
}

