/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-02-26     ox-horse         first version
 */

#ifndef __DRV_TIM_H__
#define __DRV_TIM_H__

#include <rtdef.h>
#include <board.h>

void n32_tim_ahbx_div_get(TIM_Module *timer, rt_uint32_t *div);
void n32_tim_enable_clock(TIM_Module *timer);

#endif /* __DRV_TIM_H__ */
