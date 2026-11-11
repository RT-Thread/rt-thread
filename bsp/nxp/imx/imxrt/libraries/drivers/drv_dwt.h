/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-01     RTT          the first version, generic i.MX RT DWT driver
 */

#ifndef DRV_DWT_H__
#define DRV_DWT_H__

#include <rtthread.h>
#include <stdint.h>

#ifdef BSP_USING_DWT

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the DWT cycle counter.
 * Enables the CoreDebug trace and sets CYCCNTENA in DWT_CTRL.
 * Must be called before using any other dwt_* functions.
 *
 * @return RT_EOK on success, -RT_ERROR if DWT is not available.
 */
rt_err_t dwt_init(void);

/**
 * Read the current DWT cycle counter value.
 *
 * @return 32-bit free-running cycle count. Wraps around after 2^32 cycles.
 */
rt_uint32_t dwt_get_cycles(void);

/**
 * Convert a DWT cycle count difference to microseconds.
 * Uses the CMSIS SystemCoreClock variable for the conversion.
 *
 * @param cycles  number of cycles to convert
 * @return elapsed time in microseconds
 */
rt_uint32_t dwt_cycles_to_us(rt_uint32_t cycles);

/**
 * Busy-wait delay using the DWT cycle counter.
 * dwt_init() must have been called before using this function.
 *
 * @param us  delay duration in microseconds
 */
void dwt_delay_us(rt_uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* BSP_USING_DWT */

#endif /* DRV_DWT_H__ */
