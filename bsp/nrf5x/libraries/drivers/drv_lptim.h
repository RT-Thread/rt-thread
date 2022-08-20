/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2022-08-09     forest-rain     first version
 */

#ifndef  __DRV_PMTIMER_H__
#define  __DRV_PMTIMER_H__

#include <board.h>
#include <rtdevice.h>
#include <nrfx_rtc.h>
#include <nrfx_clock.h>

#define RTC_COUNTER_BITS        24u
#define RTC_FREQ                32768u

rt_uint32_t nrfx_lptim_get_countfreq(void);
rt_uint32_t nrfx_lptim_get_tick_max(void);
rt_uint32_t nrfx_lptim_get_current_tick(void);

rt_err_t nrfx_lptim_start(rt_uint32_t load);
void nrfx_lptim_stop(void);

#endif /* __DRV_PMTIMER_H__ */
