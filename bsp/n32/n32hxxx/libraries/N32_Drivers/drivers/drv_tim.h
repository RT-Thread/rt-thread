/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-02-26     ox-horse         first version
 * 2026-08-19     ox-horse         Add N32H47X_48X
 * 2026-08-19     ox-horse         Add N32H49X
 */

#ifndef __DRV_TIM_H__
#define __DRV_TIM_H__

#include <rtdef.h>
#include <board.h>

#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
rt_uint32_t n32_tim_clock_freq_get(TIM_Module *timer);
#endif /* SOC_SERIES_N32H47x_48x || SOC_SERIES_N32H49x */

void n32_tim_ahbx_div_get(TIM_Module *timer, rt_uint32_t *div);
void n32_tim_enable_clock(TIM_Module *timer);

#endif /* __DRV_TIM_H__ */
