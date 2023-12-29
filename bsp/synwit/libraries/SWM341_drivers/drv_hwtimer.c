/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_hwtimer.h"

#ifdef RT_USING_HWTIMER
#ifdef BSP_USING_TIM

//#define DRV_DEBUG
#define LOG_TAG "drv.hwtimer"
#include <drv_log.h>

#if !defined(BSP_USING_TIM0) && !defined(BSP_USING_TIM1) && !defined(BSP_USING_TIM2) && !defined(BSP_USING_TIM3)     \
&& !defined(BSP_USING_TIM4) && !defined(BSP_USING_BTIM0) && !defined(BSP_USING_BTIM1) && !defined(BSP_USING_BTIM2)   \
&& !defined(BSP_USING_BTIM3) && !defined(BSP_USING_BTIM4) && !defined(BSP_USING_BTIM5) && !defined(BSP_USING_BTIM6)  \
&& !defined(BSP_USING_BTIM7) && !defined(BSP_USING_BTIM8) && !defined(BSP_USING_BTIM9) && !defined(BSP_USING_BTIM10) \
&& !defined(BSP_USING_BTIM11)
#error "Please define at least one BSP_USING_TIMx or BSP_USING_BTIMx"
/* this driver can be disabled at menuconfig ? RT-Thread Components ? Device Drivers */
#endif

#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG            \
    {                                  \
        .maxfreq = 1000000,            \
        .minfreq = 1000000,            \
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

#ifdef BSP_USING_BTIM0
#ifndef BTIM0_CFG
#define BTIM0_CFG          \
    {                      \
        .name = "btimer0", \
        .TIMRx = BTIMR0,   \
    }
#endif /* BTIM0_CFG */
#endif /* BSP_USING_BTIM0 */

#ifdef BSP_USING_BTIM1
#ifndef BTIM1_CFG
#define BTIM1_CFG          \
    {                      \
        .name = "btimer1", \
        .TIMRx = BTIMR1,   \
    }
#endif /* BTIM1_CFG */
#endif /* BSP_USING_BTIM1 */

#ifdef BSP_USING_BTIM2
#ifndef BTIM2_CFG
#define BTIM2_CFG          \
    {                      \
        .name = "btimer2", \
        .TIMRx = BTIMR2,   \
    }
#endif /* BTIM2_CFG */
#endif /* BSP_USING_BTIM2 */

#ifdef BSP_USING_BTIM3
#ifndef BTIM3_CFG
#define BTIM3_CFG          \
    {                      \
        .name = "btimer3", \
        .TIMRx = BTIMR3,   \
    }
#endif /* BTIM3_CFG */
#endif /* BSP_USING_BTIM3 */

#ifdef BSP_USING_BTIM4
#ifndef BTIM4_CFG
#define BTIM4_CFG          \
    {                      \
        .name = "btimer4", \
        .TIMRx = BTIMR4,   \
    }
#endif /* BTIM4_CFG */
#endif /* BSP_USING_BTIM4 */

#ifdef BSP_USING_BTIM5
#ifndef BTIM5_CFG
#define BTIM5_CFG          \
    {                      \
        .name = "btimer5", \
        .TIMRx = BTIMR5,   \
    }
#endif /* BTIM5_CFG */
#endif /* BSP_USING_BTIM5 */

#ifdef BSP_USING_BTIM6
#ifndef BTIM6_CFG
#define BTIM6_CFG          \
    {                      \
        .name = "btimer6", \
        .TIMRx = BTIMR6,   \
    }
#endif /* BTIM6_CFG */
#endif /* BSP_USING_BTIM6 */

#ifdef BSP_USING_BTIM7
#ifndef BTIM7_CFG
#define BTIM7_CFG          \
    {                      \
        .name = "btimer7", \
        .TIMRx = BTIMR7,   \
    }
#endif /* BTIM7_CFG */
#endif /* BSP_USING_BTIM7 */

#ifdef BSP_USING_BTIM8
#ifndef BTIM8_CFG
#define BTIM8_CFG          \
    {                      \
        .name = "btimer8", \
        .TIMRx = BTIMR8,   \
    }
#endif /* BTIM8_CFG */
#endif /* BSP_USING_BTIM8 */

#ifdef BSP_USING_BTIM9
#ifndef BTIM9_CFG
#define BTIM9_CFG          \
    {                      \
        .name = "btimer9", \
        .TIMRx = BTIMR9,   \
    }
#endif /* BTIM9_CFG */
#endif /* BSP_USING_BTIM9 */

#ifdef BSP_USING_BTIM10
#ifndef BTIM10_CFG
#define BTIM10_CFG          \
    {                       \
        .name = "btimer10", \
        .TIMRx = BTIMR10,   \
    }
#endif /* BTIM10_CFG */
#endif /* BSP_USING_BTIM10 */

#ifdef BSP_USING_BTIM11
#ifndef BTIM11_CFG
#define BTIM11_CFG          \
    {                       \
        .name = "btimer11", \
        .TIMRx = BTIMR11,   \
    }
#endif /* BTIM11_CFG */
#endif /* BSP_USING_BTIM11 */

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
#ifdef BSP_USING_BTIM0
    BTIM0_INDEX,
#endif
#ifdef BSP_USING_BTIM1
    BTIM1_INDEX,
#endif
#ifdef BSP_USING_BTIM2
    BTIM2_INDEX,
#endif
#ifdef BSP_USING_BTIM3
    BTIM3_INDEX,
#endif
#ifdef BSP_USING_BTIM4
    BTIM4_INDEX,
#endif
#ifdef BSP_USING_BTIM5
    BTIM5_INDEX,
#endif
#ifdef BSP_USING_BTIM6
    BTIM6_INDEX,
#endif
#ifdef BSP_USING_BTIM7
    BTIM7_INDEX,
#endif
#ifdef BSP_USING_BTIM8
    BTIM8_INDEX,
#endif
#ifdef BSP_USING_BTIM9
    BTIM9_INDEX,
#endif
#ifdef BSP_USING_BTIM10
    BTIM10_INDEX,
#endif
#ifdef BSP_USING_BTIM11
    BTIM11_INDEX,
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
#ifdef BSP_USING_BTIM0
        BTIM0_CFG,
#endif
#ifdef BSP_USING_BTIM1
        BTIM1_CFG,
#endif
#ifdef BSP_USING_BTIM2
        BTIM2_CFG,
#endif
#ifdef BSP_USING_BTIM3
        BTIM3_CFG,
#endif
#ifdef BSP_USING_BTIM4
        BTIM4_CFG,
#endif
#ifdef BSP_USING_BTIM5
        BTIM5_CFG,
#endif
#ifdef BSP_USING_BTIM6
        BTIM6_CFG,
#endif
#ifdef BSP_USING_BTIM7
        BTIM7_CFG,
#endif
#ifdef BSP_USING_BTIM8
        BTIM8_CFG,
#endif
#ifdef BSP_USING_BTIM9
        BTIM9_CFG,
#endif
#ifdef BSP_USING_BTIM10
        BTIM10_CFG,
#endif
#ifdef BSP_USING_BTIM11
        BTIM11_CFG,
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
        TIMR_Init(hwtimer_cfg->TIMRx, TIMR_MODE_TIMER, CyclesPerUs, 1000000, 1);
        timer_device->freq = 1000000;
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
    hwtimer_cfg->TIMRx->LOAD = cnt - 1;
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

        TIMR_Init(hwtimer_cfg->TIMRx, TIMR_MODE_TIMER, CyclesPerUs, freq, 1);
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
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM0_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_TIM0

#ifdef BSP_USING_TIM1
void TIMR1_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM1_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_TIM1

#ifdef BSP_USING_TIM2
void TIMR2_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM2_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_TIM2

#ifdef BSP_USING_TIM3
void TIMR3_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM3_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_TIM3

#ifdef BSP_USING_TIM4
void TIMR4_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[TIM4_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_TIM4

#ifdef BSP_USING_BTIM0
void BTIMR0_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM0_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM0

#ifdef BSP_USING_BTIM1
void BTIMR1_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM1_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM1

#ifdef BSP_USING_BTIM2
void BTIMR2_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM2_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM2

#ifdef BSP_USING_BTIM3
void BTIMR3_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM3_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM3

#ifdef BSP_USING_BTIM4
void BTIMR4_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM4_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM4

#ifdef BSP_USING_BTIM5
void BTIMR5_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM5_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM5

#ifdef BSP_USING_BTIM6
void BTIMR6_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM6_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM6

#ifdef BSP_USING_BTIM7
void BTIMR7_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM7_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM7

#ifdef BSP_USING_BTIM8
void BTIMR8_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM8_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM8

#ifdef BSP_USING_BTIM9
void BTIMR9_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM9_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM9

#ifdef BSP_USING_BTIM10
void BTIMR10_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM10_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM10

#ifdef BSP_USING_BTIM11
void BTIMR11_Handler(void)
{
    rt_interrupt_enter();
    swm_timer_isr(&(hwtimer_obj[BTIM11_INDEX].time_device));
    rt_interrupt_leave();
}
#endif // BSP_USING_BTIM11

int swm_timer_init(void)
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
