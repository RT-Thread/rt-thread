/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-16     Leo          first version
 */

#include <board.h>
#include "drv_hwtimer.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.hwtimer"
#include <drv_log.h>

#ifdef BSP_USING_HWTIMER
enum
{
#ifdef BSP_USING_HWTMR1
    TMR1_INDEX,
#endif

#ifdef BSP_USING_HWTMR2
    TMR2_INDEX,
#endif

#ifdef BSP_USING_HWTMR3
    TMR3_INDEX,
#endif

#ifdef BSP_USING_HWTMR4
    TMR4_INDEX,
#endif

#ifdef BSP_USING_HWTMR5
    TMR5_INDEX,
#endif

#ifdef BSP_USING_HWTMR6
    TMR6_INDEX,
#endif

#ifdef BSP_USING_HWTMR7
    TMR7_INDEX,
#endif

#ifdef BSP_USING_HW_TMR8
    TMR8_INDEX,
#endif

#ifdef BSP_USING_HWTMR9
    TMR9_INDEX,
#endif

#ifdef BSP_USING_HWTMR10
    TMR10_INDEX,
#endif

#ifdef BSP_USING_HWTMR11
    TMR11_INDEX,
#endif

#ifdef BSP_USING_HWTMR12
    TMR12_INDEX,
#endif

#ifdef BSP_USING_HWTMR13
    TMR13_INDEX,
#endif

#ifdef BSP_USING_HWTMR14
    TMR14_INDEX,
#endif

#ifdef BSP_USING_HWTMR15
    TMR15_INDEX,
#endif
};

struct at32_hwtimer
{
    rt_hwtimer_t  time_device;
    TMR_Type*     tim_handle;
    IRQn_Type     tim_irqn;
    char          *name;
};

static struct at32_hwtimer at32_hwtimer_obj[] =
{
#ifdef BSP_USING_HWTMR1
    TMR1_CONFIG,
#endif

#ifdef BSP_USING_HWTMR2
    TMR2_CONFIG,
#endif

#ifdef BSP_USING_HWTMR3
    TMR3_CONFIG,
#endif

#ifdef BSP_USING_HWTMR4
    TMR4_CONFIG,
#endif

#ifdef BSP_USING_HWTMR5
    TMR5_CONFIG,
#endif

#ifdef BSP_USING_HWTMR6
    TMR6_CONFIG,
#endif

#ifdef BSP_USING_HWTMR7
    TMR7_CONFIG,
#endif

#ifdef BSP_USING_HWTMR8
    TMR8_CONFIG,
#endif

#ifdef BSP_USING_HWTMR9
    TMR9_CONFIG,
#endif

#ifdef BSP_USING_HWTMR10
    TMR10_CONFIG,
#endif

#ifdef BSP_USING_HWTMR11
    TMR11_CONFIG,
#endif

#ifdef BSP_USING_HWTMR12
    TMR12_CONFIG,
#endif

#ifdef BSP_USING_HWTMR13
    TMR13_CONFIG,
#endif

#ifdef BSP_USING_HWTMR14
    TMR14_CONFIG,
#endif

#ifdef BSP_USING_HWTMR15
    TMR15_CONFIG,
#endif
};

static void at32_timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    RCC_ClockType RCC_ClockStruct;
    TMR_TimerBaseInitType TMR_TMReBaseStructure;
    NVIC_InitType NVIC_InitStructure;
    uint32_t prescaler_value = 0;
    TMR_Type *tim = RT_NULL;
    struct at32_hwtimer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        tim = (TMR_Type *)timer->parent.user_data;
        tim_device = (struct at32_hwtimer *)timer;

        /* timer clock enable */
        at32_msp_hwtmr_init(tim);

        /* timer init */
        RCC_GetClocksFreq(&RCC_ClockStruct);
        /* Set timer clock is 1Mhz */
        prescaler_value = (uint32_t)(RCC_ClockStruct.SYSCLK_Freq / 10000) - 1;

        TMR_TMReBaseStructure.TMR_Period = 10000 - 1;
        TMR_TMReBaseStructure.TMR_DIV = prescaler_value;
        TMR_TMReBaseStructure.TMR_ClockDivision = TMR_CKD_DIV1;
        TMR_TMReBaseStructure.TMR_RepetitionCounter = 0;

        if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;
        }
        else
        {
            TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Down;
        }

        TMR_TimeBaseInit(tim, &TMR_TMReBaseStructure);

        /* Enable the TMRx global Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = tim_device->tim_irqn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        TMR_INTConfig(tim, TMR_INT_Overflow ,ENABLE);
        TMR_ClearITPendingBit(tim, TMR_INT_Overflow);

        LOG_D("%s init success", tim_device->name);
    }
}

static rt_err_t at32_timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    TMR_Type *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TMR_Type *)timer->parent.user_data;

    /* set tim cnt */
    TMR_SetCounter(tim, 0);
    /* set tim arr */
    TMR_SetAutoreload(tim, t - 1);
    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        TMR_SelectOnePulseMode(tim, TMR_OPMode_Once);
    }
    else
    {
        TMR_SelectOnePulseMode(tim, TMR_OPMode_Repetitive);
    }

    /* start timer */
    TMR_Cmd(tim, ENABLE);

    return result;
}

static void at32_timer_stop(rt_hwtimer_t *timer)
{
    TMR_Type *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TMR_Type *)timer->parent.user_data;

    /* stop timer */
    TMR_Cmd(tim, ENABLE);
    /* set tim cnt */
    TMR_SetCounter(tim, 0);
}

static rt_uint32_t at32_timer_counter_get(rt_hwtimer_t *timer)
{
    TMR_Type *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TMR_Type *)timer->parent.user_data;

    return tim->CNT;
}

static rt_err_t at32_timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    RCC_ClockType RCC_ClockStruct;
    TMR_Type *tim = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    tim = (TMR_Type *)timer->parent.user_data;

    switch(cmd)
    {
        case HWTIMER_CTRL_FREQ_SET:
        {
            rt_uint32_t freq;
            rt_uint16_t val;

            /* set timer frequence */
            freq = *((rt_uint32_t *)arg);

            /* time init */
            RCC_GetClocksFreq(&RCC_ClockStruct);

            val = RCC_ClockStruct.SYSCLK_Freq / freq;

            TMR_DIVConfig(tim, val - 1, TMR_DIVReloadMode_Immediate);
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

static const struct rt_hwtimer_info _info = TMR_DEV_INFO_CONFIG;
static const struct rt_hwtimer_ops _ops =
{
    .init      = at32_timer_init,
    .start     = at32_timer_start,
    .stop      = at32_timer_stop,
    .count_get = at32_timer_counter_get,
    .control   = at32_timer_ctrl,
};

#ifdef BSP_USING_HWTMR2
void TMR2_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TMR_GetINTStatus(TMR2, TMR_INT_Overflow) == SET)
    {

        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR2_INDEX].time_device);
        TMR_ClearITPendingBit(TMR2, TMR_INT_Overflow);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTMR3
void TMR3_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TMR_GetINTStatus(TMR3, TMR_INT_Overflow) == SET)
    {

        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR3_INDEX].time_device);
        TMR_ClearITPendingBit(TMR3, TMR_INT_Overflow);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTMR4
void TMR4_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TMR_GetINTStatus(TMR4, TMR_INT_Overflow) == SET)
    {

        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR4_INDEX].time_device);
        TMR_ClearITPendingBit(TMR4, TMR_INT_Overflow);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTMR5
void TMR5_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(TMR_GetINTStatus(TMR5, TMR_INT_Overflow) == SET)
    {

        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR5_INDEX].time_device);
        TMR_ClearITPendingBit(TMR5, TMR_INT_Overflow);

    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static int rt_hw_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(at32_hwtimer_obj) / sizeof(at32_hwtimer_obj[0]); i++)
    {
        at32_hwtimer_obj[i].time_device.info = &_info;
        at32_hwtimer_obj[i].time_device.ops  = &_ops;
        if (rt_device_hwtimer_register(&at32_hwtimer_obj[i].time_device, at32_hwtimer_obj[i].name, at32_hwtimer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", at32_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", at32_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* BSP_USING_HWTIMER */







