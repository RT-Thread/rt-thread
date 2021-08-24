/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#include <board.h>
#include "drv_hwtimer.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.hwtimer"
#include <drv_log.h>

#ifdef BSP_USING_HWTIMER
enum
{
#ifdef BSP_USING_HWTIM1
    TIM1_INDEX,
#endif

#ifdef BSP_USING_HWTIM2
    TIM2_INDEX,
#endif

#ifdef BSP_USING_HWTIM3
    TIM3_INDEX,
#endif

#ifdef BSP_USING_HWTIM4
    TIM4_INDEX,
#endif

#ifdef BSP_USING_HWTIM5
    TIM5_INDEX,
#endif

#ifdef BSP_USING_HWTIM6
    TIM6_INDEX,
#endif

#ifdef BSP_USING_HWTIM7
    TIM7_INDEX,
#endif

#ifdef BSP_USING_HW_TIM8
    TIM8_INDEX,
#endif

#ifdef BSP_USING_HWTIM9
    TIM9_INDEX,
#endif

#ifdef BSP_USING_HWTIM10
    TIM10_INDEX,
#endif

#ifdef BSP_USING_HWTIM11
    TIM11_INDEX,
#endif

#ifdef BSP_USING_HWTIM12
    TIM12_INDEX,
#endif

#ifdef BSP_USING_HWTIM13
    TIM13_INDEX,
#endif

#ifdef BSP_USING_HWTIM14
    TIM14_INDEX,
#endif

#ifdef BSP_USING_HWTIM15
    TIM15_INDEX,
#endif
};

struct n32_hwtimer
{
    rt_hwtimer_t    time_device;
    TIM_Module*     tim_handle;
    IRQn_Type       tim_irqn;
    char            *name;
};

static struct n32_hwtimer n32_hwtimer_obj[] =
{
#ifdef BSP_USING_HWTIM1
    TIM1_CONFIG,
#endif

#ifdef BSP_USING_HWTIM2
    TIM2_CONFIG,
#endif

#ifdef BSP_USING_HWTIM3
    TIM3_CONFIG,
#endif

#ifdef BSP_USING_HWTIM4
    TIM4_CONFIG,
#endif

#ifdef BSP_USING_HWTIM5
    TIM5_CONFIG,
#endif

#ifdef BSP_USING_HWTIM6
    TIM6_CONFIG,
#endif

#ifdef BSP_USING_HWTIM7
    TIM7_CONFIG,
#endif

#ifdef BSP_USING_HWTIM8
    TIM8_CONFIG,
#endif

#ifdef BSP_USING_HWTIM9
    TIM9_CONFIG,
#endif

#ifdef BSP_USING_HWTIM10
    TIM10_CONFIG,
#endif

#ifdef BSP_USING_HWTIM11
    TIM11_CONFIG,
#endif

#ifdef BSP_USING_HWTIM12
    TIM12_CONFIG,
#endif

#ifdef BSP_USING_HWTIM13
    TIM13_CONFIG,
#endif

#ifdef BSP_USING_HWTIM14
    TIM14_CONFIG,
#endif

#ifdef BSP_USING_HWTIM15
    TIM15_CONFIG,
#endif
};

static void n32_timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    RCC_ClocksType RCC_ClockStruct;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    NVIC_InitType NVIC_InitStructure;
    uint32_t prescaler_value = 0;
    TIM_Module *tim = RT_NULL;
    struct n32_hwtimer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        tim = (TIM_Module *)timer->parent.user_data;
        tim_device = (struct n32_hwtimer *)timer;

        /* timer clock enable */
        n32_msp_hwtim_init(tim);

        /* timer init */
        RCC_GetClocksFreqValue(&RCC_ClockStruct);
        /* Set timer clock is 1Mhz */
        prescaler_value = (uint32_t)(RCC_ClockStruct.SysclkFreq / 10000) - 1;

        TIM_TimeBaseStructure.Period = 10000 - 1;
        rt_kprintf("Period=[%d]", TIM_TimeBaseStructure.Period);
        TIM_TimeBaseStructure.Prescaler = prescaler_value;
        rt_kprintf("Prescaler=[%d]", TIM_TimeBaseStructure.Prescaler);
        TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;
        TIM_TimeBaseStructure.RepetCnt = 0;

        if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;
        }
        else
        {
            TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_DOWN;
        }

        TIM_InitTimeBase(tim, &TIM_TimeBaseStructure);

        /* Enable the TIMx global Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = tim_device->tim_irqn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        TIM_ConfigInt(tim, TIM_INT_UPDATE ,ENABLE);
        TIM_ClrIntPendingBit(tim, TIM_INT_UPDATE);

        LOG_D("%s init success", tim_device->name);
    }
}

static rt_err_t n32_timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    TIM_Module *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_Module *)timer->parent.user_data;

    /* set tim cnt */
    TIM_SetCnt(tim, 0);
    /* set tim arr */
    TIM_SetAutoReload(tim, t - 1);
    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        TIM_SelectOnePulseMode(tim, TIM_OPMODE_SINGLE);
    }
    else
    {
        TIM_SelectOnePulseMode(tim, TIM_OPMODE_REPET);
    }

    /* start timer */
    TIM_Enable(tim, ENABLE);

    return result;
}

static void n32_timer_stop(rt_hwtimer_t *timer)
{
    TIM_Module *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_Module *)timer->parent.user_data;

    /* stop timer */
    TIM_Enable(tim, DISABLE);
    /* set tim cnt */
    TIM_SetCnt(tim, 0);
}

static rt_uint32_t n32_timer_counter_get(rt_hwtimer_t *timer)
{
    TIM_Module *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_Module *)timer->parent.user_data;

    return tim->CNT;
}

static rt_err_t n32_timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    RCC_ClocksType RCC_ClockStruct;
    TIM_Module *tim = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    tim = (TIM_Module *)timer->parent.user_data;

    switch(cmd)
    {
        case HWTIMER_CTRL_FREQ_SET:
        {
            rt_uint32_t freq;
            rt_uint16_t val;

            /* set timer frequence */
            freq = *((rt_uint32_t *)arg);

            /* time init */
            RCC_GetClocksFreqValue(&RCC_ClockStruct);

            val = RCC_ClockStruct.SysclkFreq / freq;

            TIM_ConfigPrescaler(tim, val - 1, TIM_PSC_RELOAD_MODE_IMMEDIATE);
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
static const struct rt_hwtimer_ops _ops =
{
    .init      = n32_timer_init,
    .start     = n32_timer_start,
    .stop      = n32_timer_stop,
    .count_get = n32_timer_counter_get,
    .control   = n32_timer_ctrl,
};

#ifdef BSP_USING_HWTIM2
void TIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TIM_GetIntStatus(TIM2, TIM_INT_UPDATE) == SET)
    {

        rt_device_hwtimer_isr(&n32_hwtimer_obj[TIM2_INDEX].time_device);
        TIM_ClrIntPendingBit(TIM2, TIM_INT_UPDATE);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIM3
void TIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TIM_GetIntStatus(TIM3, TIM_INT_UPDATE) == SET)
    {

        rt_device_hwtimer_isr(&n32_hwtimer_obj[TIM3_INDEX].time_device);
        TIM_ClrIntPendingBit(TIM3, TIM_INT_UPDATE);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIM4
void TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TIM_GetIntStatus(TIM4, TIM_INT_UPDATE) == SET)
    {

        rt_device_hwtimer_isr(&n32_hwtimer_obj[TIM4_INDEX].time_device);
        TIM_ClrIntPendingBit(TIM4, TIM_INT_UPDATE);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIM5
void TIM5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TIM_GetIntStatus(TIM5, TIM_INT_UPDATE) == SET)
    {

        rt_device_hwtimer_isr(&n32_hwtimer_obj[TIM5_INDEX].time_device);
        TIM_ClrIntPendingBit(TIM5, TIM_INT_UPDATE);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIM6
void TIM6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TIM_GetIntStatus(TIM6, TIM_INT_UPDATE) == SET)
    {

        rt_device_hwtimer_isr(&n32_hwtimer_obj[TIM6_INDEX].time_device);
        TIM_ClrIntPendingBit(TIM6, TIM_INT_UPDATE);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIM7
void TIM7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TIM_GetIntStatus(TIM7, TIM_INT_UPDATE) == SET)
    {

        rt_device_hwtimer_isr(&n32_hwtimer_obj[TIM7_INDEX].time_device);
        TIM_ClrIntPendingBit(TIM7, TIM_INT_UPDATE);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static int rt_hw_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(n32_hwtimer_obj) / sizeof(n32_hwtimer_obj[0]); i++)
    {
        n32_hwtimer_obj[i].time_device.info = &_info;
        n32_hwtimer_obj[i].time_device.ops  = &_ops;
        if (rt_device_hwtimer_register(&n32_hwtimer_obj[i].time_device, n32_hwtimer_obj[i].name, n32_hwtimer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", n32_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", n32_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* BSP_USING_HWTIMER */







