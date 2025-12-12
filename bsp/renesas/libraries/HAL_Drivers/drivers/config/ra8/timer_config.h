/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-04     Rbb666       first version
 */

#ifndef __TIMER_CONFIG_H__
#define __TIMER_CONFIG_H__

#include <rtthread.h>
#include "hal_data.h"

#ifdef SOC_SERIES_R7KA8P1

#ifdef __cplusplus
extern "C"
{
#endif

#define PLCKD_PRESCALER_MAX_SELECT	9
#define PLCKD_PRESCALER_250M    	(250000000U)
#define PLCKD_PRESCALER_200M    	(200000000U)
#define PLCKD_PRESCALER_100M    	(100000000U)
#define PLCKD_PRESCALER_50M     	(50000000U)
#define PLCKD_PRESCALER_25M     	(25000000U)
#define PLCKD_PRESCALER_12_5M   	(12500000U)
#define PLCKD_PRESCALER_6_25M   	(6250000U)
#define PLCKD_PRESCALER_3_125M  	(3125000U)
#define PLCKD_PRESCALER_1_5625M 	(1562500U)

#ifndef TMR_DEV_INFO_CONFIG
#define TMR_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 250000000,                   \
        .minfreq = 1562500,                     \
        .maxcnt  = 0XFFFFFFFF,                  \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */

enum
{
#ifdef BSP_USING_TIM0
    BSP_TIMER0_INDEX,
#endif
#ifdef BSP_USING_TIM1
    BSP_TIMER1_INDEX,
#endif
    BSP_TIMERS_NUM
};

#define TIMER_DRV_INITIALIZER(num)      \
    {                                   \
        .name = "timer" #num,           \
        .g_cfg = &g_timer##num##_cfg,   \
        .g_ctrl = &g_timer##num##_ctrl, \
        .g_timer = &g_timer##num,       \
    }

#ifdef __cplusplus
}
#endif

#endif /* SOC_SERIES_R7KA8P1 */

#endif /* __TIMER_CONFIG_H__ */
