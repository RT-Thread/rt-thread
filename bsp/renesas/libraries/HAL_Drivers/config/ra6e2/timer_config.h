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
#include <drv_config.h>
#include "hal_data.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define PLCKD_PRESCALER_MAX_SELECT     7

/* RA6M3: Frequency ratio: PCLKA:PCLKD = 1:N (N = 1/2/4/8/16/32/64) */
#define PLCKD_PRESCALER_120M           (BSP_FEATURE_GPT_ODC_FREQ_MAX)
#define PLCKD_PRESCALER_60M            (BSP_FEATURE_GPT_ODC_FREQ_MAX / 2)
#define PLCKD_PRESCALER_30M            (BSP_FEATURE_GPT_ODC_FREQ_MAX / 4)
#define PLCKD_PRESCALER_15M            (BSP_FEATURE_GPT_ODC_FREQ_MAX / 8)
#define PLCKD_PRESCALER_7_5M           (BSP_FEATURE_GPT_ODC_FREQ_MAX / 16)
#define PLCKD_PRESCALER_3_75M          (BSP_FEATURE_GPT_ODC_FREQ_MAX / 32)
#define PLCKD_PRESCALER_1_875M         (BSP_FEATURE_GPT_ODC_FREQ_MAX / 64)

#ifndef TMR_DEV_INFO_CONFIG
#define TMR_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 120000000,                   \
        .minfreq = 1875000,                     \
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
