/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-01     Meco Man     First version
 */

#ifndef __DRV_TIM_H__
#define __DRV_TIM_H__

#include <rtdef.h>

void stm32_tim_pclkx_doubler_get(rt_uint32_t *pclk1_doubler, rt_uint32_t *pclk2_doubler);

#endif /* __DRV_TIM_H__ */
