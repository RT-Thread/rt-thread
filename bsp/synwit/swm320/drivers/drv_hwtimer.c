/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10    Zohar_Lee    first version
 * 2020-07-10    lik          format file
 */

#include "drv_hwtimer.h"

#ifdef RT_USING_HWTIMER
#ifdef BSP_USING_TIM

//#define DRV_DEBUG
#define LOG_TAG "drv.hwtimer"
#include <drv_log.h>

#if !defined(BSP_USING_TIM0) && !defined(BSP_USING_TIM1) && !defined(BSP_USING_TIM2) && !defined(BSP_USING_TIM3)     \
&& !defined(BSP_USING_TIM4) && !defined(BSP_USING_TIM5)
#error "Please define at least one BSP_USING_TIMx"
/* this driver can be disabled at menuconfig ? RT-Thread Components ? Device Drivers */
#endif

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

struct swm_hwtimer_cfg
{
    char *name;
    TIMR_TypeDef *TIMRx;
};

struct swm_hwtimer_device
{
    struct swm_hwtimer_cfg *hwtimer_cfg;
    rt_hwtimer_t time_device;
};

enum
{
#ifdef BSP_USING_TIM0
    TIM0_INDEX,
#endif
#ifdef BSP_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_TIM2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_TIM3
    TIM3_INDEX,
#endif
#ifdef BSP_USING_TIM4
    TIM4_INDEX,
#endif
#ifdef BSP_USING_TIM5
    TIM5_INDEX,
#endif
};

static struct swm_hwtimer_cfg swm_hwtimer_cfg[] =
    {
#ifdef BSP_USING_TIM0
        TIM0_CFG,
#endif
#ifdef BSP_USING_TIM1
        TIM1_CFG,
#endif
#ifdef BSP_USING_TIM2
        TIM2_CFG,
#endif
#ifdef BSP_USING_TIM3
        TIM3_CFG,
#endif
#ifdef BSP_USING_TIM4
        TIM4_CFG,
#endif
#ifdef BSP_USING_TIM5
        TIM5_CFG,
#endif
};

static struct swm_hwtimer_device hwtimer_obj[sizeof(swm_hwtimer_cfg) / sizeof(swm_hwtimer_cfg[0])] = {0};

static void swm_timer_configure(struct rt_hwtimer_device *timer_device, rt_uint32_t state)
{
    struct swm_hwtimer_cfg *hwtimer_cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);

    if (state)
    {
        hwtimer_cfg = timer_device->parent.user_data;
        TIMR_Init(hwtimer_cfg->TIMRx, TIMR_MODE_TIMER, SystemCoreClock, 1);
        timer_device->freq = SystemCoreClock;
    }
}

static rt_err_t swm_timer_start(rt_hwtimer_t *timer_device, rt_uint32_t cnt, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    struct swm_hwtimer_cfg *hwtimer_cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    hwtimer_cfg = timer_device->parent.user_data;

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        timer_device->mode = HWTIMER_MODE_ONESHOT;
    }
    else
    {
        timer_device->mode = HWTIMER_MODE_PERIOD;
    }
    TIMR_SetPeriod(hwtimer_cfg->TIMRx, cnt);
    TIMR_Stop(hwtimer_cfg->TIMRx);
    TIMR_Start(hwtimer_cfg->TIMRx);

    return result;
}

static void swm_timer_stop(rt_hwtimer_t *timer_device)
{
    struct swm_hwtimer_cfg *hwtimer_cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    hwtimer_cfg = timer_device->parent.user_data;

    /* stop timer */
    TIMR_Stop(hwtimer_cfg->TIMRx);
}

static rt_uint32_t swm_timer_count_get(rt_hwtimer_t *timer_device)
{
    struct swm_hwtimer_cfg *hwtimer_cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    hwtimer_cfg = timer_device->parent.user_data;

    return TIMR_GetCurValue(hwtimer_cfg->TIMRx);
}

static rt_err_t swm_timer_control(rt_hwtimer_t *timer_device, rt_uint32_t cmd, void *args)
{
    struct swm_hwtimer_cfg *hwtimer_cfg = RT_NULL;
    rt_err_t result = RT_EOK;
    RT_ASSERT(timer_device != RT_NULL);
    RT_ASSERT(args != RT_NULL);
    hwtimer_cfg = timer_device->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;
        freq = *(rt_uint32_t *)args;

        TIMR_Init(hwtimer_cfg->TIMRx, TIMR_MODE_TIMER, SystemCoreClock / freq, 1);
    }
    break;
    default:
    {
        result = -RT_ENOSYS;
    }
    break;
    }

    return result;
}

static const struct rt_hwtimer_info _info = TIM_DEV_INFO_CONFIG;

static const struct rt_hwtimer_ops swm_timer_ops =
    {
        .init = swm_timer_configure,
        .start = swm_timer_start,
        .stop = swm_timer_stop,
        .count_get = swm_timer_count_get,
        .control = swm_timer_control};

void swm_timer_isr(rt_hwtimer_t *timer_device)
{
    struct swm_hwtimer_cfg *hwtimer_cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    hwtimer_cfg = timer_device->parent.user_data;

    TIMR_INTClr(hwtimer_cfg->TIMRx);
    rt_device_hwtimer_isr(timer_device);
}

#ifdef BSP_USING_TIM0
void TIMR0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM0_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM0

#ifdef BSP_USING_TIM1
void TIMR1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM1_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM1

#ifdef BSP_USING_TIM2
void TIMR2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM2_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM2

#ifdef BSP_USING_TIM3
void TIMR3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM3_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM3

#ifdef BSP_USING_TIM4
void TIMR4_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM4_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM4

#ifdef BSP_USING_TIM5
void TIMR5_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM5_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM5

static int swm_timer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(swm_hwtimer_cfg) / sizeof(swm_hwtimer_cfg[0]); i++)
    {
        hwtimer_obj[i].hwtimer_cfg = &swm_hwtimer_cfg[i];
        hwtimer_obj[i].time_device.info = &_info;
        hwtimer_obj[i].time_device.ops = &swm_timer_ops;
        result = rt_device_hwtimer_register(&hwtimer_obj[i].time_device, hwtimer_obj[i].hwtimer_cfg->name, hwtimer_obj[i].hwtimer_cfg);
        if (result != RT_EOK)
        {
            LOG_E("%s register fail.", hwtimer_obj[i].hwtimer_cfg->name);
        }
        else
        {
            LOG_D("%s register success.", hwtimer_obj[i].hwtimer_cfg->name);
        }
    }

    return result;
}
INIT_BOARD_EXPORT(swm_timer_init);

#endif /* BSP_USING_TIM */
#endif /* RT_USING_HWTIMER */
