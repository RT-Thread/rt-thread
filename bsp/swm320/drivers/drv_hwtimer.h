/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#include "board.h"

struct swm_hwtimer_cfg
{
    char *name;
    TIMR_TypeDef *TIMRx;
};

struct swm_hwtimer
{
    struct swm_hwtimer_cfg *cfg;
    rt_hwtimer_t time_device;
};

#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG            \
    {                                  \
        .maxfreq = 120000000,          \
        .minfreq = 120000000,          \
        .maxcnt = 0xFFFFFFFF,          \
        .cntmode = HWTIMER_CNTMODE_DW, \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_TIM0
#ifndef TIM0_CFG
#define TIM0_CFG          \
    {                     \
        .name = "timer0", \
        .TIMRx = TIMR0,   \
    }
#endif /* TIM0_CFG */
#endif /* BSP_USING_TIM0 */

#ifdef BSP_USING_TIM1
#ifndef TIM1_CFG
#define TIM1_CFG          \
    {                     \
        .name = "timer1", \
        .TIMRx = TIMR1,   \
    }
#endif /* TIM1_CFG */
#endif /* BSP_USING_TIM1 */

#ifdef BSP_USING_TIM2
#ifndef TIM2_CFG
#define TIM2_CFG          \
    {                     \
        .name = "timer2", \
        .TIMRx = TIMR2,   \
    }
#endif /* TIM2_CFG */
#endif /* BSP_USING_TIM2 */

#ifdef BSP_USING_TIM3
#ifndef TIM3_CFG
#define TIM3_CFG          \
    {                     \
        .name = "timer3", \
        .TIMRx = TIMR3,   \
    }
#endif /* TIM3_CFG */
#endif /* BSP_USING_TIM3 */

#ifdef BSP_USING_TIM4
#ifndef TIM4_CFG
#define TIM4_CFG          \
    {                     \
        .name = "timer4", \
        .TIMRx = TIMR4,   \
    }
#endif /* TIM4_CFG */
#endif /* BSP_USING_TIM4 */

#ifdef BSP_USING_TIM5
#ifndef TIM5_CFG
#define TIM5_CFG          \
    {                     \
        .name = "timer5", \
        .TIMRx = TIMR5,   \
    }
#endif /* TIM5_CFG */
#endif /* BSP_USING_TIM5 */

int rt_hw_hwtimer_init(void);

#endif /* __DRV_HWTIMER_H__ */
