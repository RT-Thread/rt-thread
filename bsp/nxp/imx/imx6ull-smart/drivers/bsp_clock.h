/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-20     Lyons        first version
 */

#ifndef __BSP_CLOCK_H__
#define __BSP_CLOCK_H__

extern uint32_t *g_iomuxc_vbase;
extern uint32_t *g_iomuxc_snvs_vbase;
extern uint32_t *g_src_vbase;
extern uint32_t *g_wdog1_vbase;
extern uint32_t *g_snvs_vbase;

void SystemAddressMapping(void);
void SystemClockInit(void);

void rt_hw_us_delay(uint32_t us);
void rt_hw_ms_delay(uint32_t ms);

#endif //#ifndef __BSP_CLOCK_H__
