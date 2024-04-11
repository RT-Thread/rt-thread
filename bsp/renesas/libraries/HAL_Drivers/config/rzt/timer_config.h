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

#ifdef __cplusplus
extern "C"
{
#endif

#define PLCKD_PRESCALER_MAX_SELECT     8

/* RSK-RZN2L: Frequency ratio: PCLKA:PCLKD = 1:N (N = 1/2/4/8/16/32/64) */
#define PLCKD_PRESCALER_400M           (BSP_PRV_PCLKGPTL_FREQ_400_MHZ)
#define PLCKD_PRESCALER_200M           (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 2)
#define PLCKD_PRESCALER_100M           (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 4)
#define PLCKD_PRESCALER_50M            (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 8)
#define PLCKD_PRESCALER_25M            (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 16)
#define PLCKD_PRESCALER_12_5M          (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 32)
#define PLCKD_PRESCALER_6_25M          (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 64)
#define PLCKD_PRESCALER_3_125M         (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 128)
#define PLCKD_PRESCALER_1_5625M        (BSP_PRV_PCLKGPTL_FREQ_400_MHZ / 256)

#ifndef TMR_DEV_INFO_CONFIG
#define TMR_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 400000000,                   \
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

#endif /* __TIMER_CONFIG_H__ */
