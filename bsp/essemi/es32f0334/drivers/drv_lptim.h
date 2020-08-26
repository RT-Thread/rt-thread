/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2019-11-01     wangyq          first version
 */

#ifndef  __DRV_PMTIMER_H__
#define  __DRV_PMTIMER_H__

#include <rtthread.h>

rt_uint32_t es32f0_lptim_get_countfreq(void);
rt_uint32_t es32f0_lptim_get_tick_max(void);
rt_uint32_t es32f0_lptim_get_current_tick(void);

rt_err_t es32f0_lptim_start(rt_uint32_t load);
void es32f0_lptim_stop(void);

#endif /* __DRV_PMTIMER_H__ */
