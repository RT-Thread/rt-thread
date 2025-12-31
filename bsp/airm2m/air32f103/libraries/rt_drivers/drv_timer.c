/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_timer.h"

#ifdef BSP_USING_TIM

#define LOG_TAG "drv.clock_timer"
#include <drv_log.h>

static void air32_clock_timer_init(struct rt_clock_timer_device *device, rt_uint32_t state)
{
    struct clock_timer_device *clock_timer_dev;
    struct rt_clock_timer_info *clock_timer_info;
    rt_uint32_t clk = 0;
    rt_uint16_t prescaler_value = 0;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitType;
    NVIC_InitTypeDef NVIC_InitStructure;

    RT_ASSERT(device != RT_NULL);

    clock_timer_dev = (struct clock_timer_device *)device;

    if (state)
    {
        air32_tim_clock_init(clock_timer_dev->periph);

        clock_timer_info = air32_clock_timer_info_config_get(clock_timer_dev->periph);

        clk = air32_tim_clock_get(clock_timer_dev->periph);

        prescaler_value = (rt_uint16_t)(clk / clock_timer_info->minfreq) - 1;

        /*
        * (1 / freq) = (cnt + 1) * (1 / (clk/(prescaler_value + 1) ) )
        */

        TIM_TimeBaseInitType.TIM_Period = clock_timer_info->maxcnt - 1;
        TIM_TimeBaseInitType.TIM_Prescaler = prescaler_value;
        TIM_TimeBaseInitType.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitType.TIM_RepetitionCounter = 0;

        if (clock_timer_info == RT_NULL)
        {
            TIM_TimeBaseInitType.TIM_CounterMode = TIM_CounterMode_Up;
        }
        else
        {
            if (clock_timer_info->cntmode == CLOCK_TIMER_CNTMODE_UP)
            {
                TIM_TimeBaseInitType.TIM_CounterMode = TIM_CounterMode_Up;
            }
            else
            {
                TIM_TimeBaseInitType.TIM_CounterMode = TIM_CounterMode_Down;
            }
        }

        TIM_TimeBaseInit(clock_timer_dev->periph, &TIM_TimeBaseInitType);

        NVIC_InitStructure.NVIC_IRQChannel = clock_timer_dev->irqn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        TIM_ITConfig(clock_timer_dev->periph, TIM_IT_Update, ENABLE);
        TIM_ClearITPendingBit(clock_timer_dev->periph, TIM_IT_Update);

        LOG_D("%s init success", clock_timer_dev->name);
    }
}

static rt_err_t air32_clock_timer_start(struct rt_clock_timer_device *device, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{

    struct clock_timer_device *clock_timer_dev;

    RT_ASSERT(device != RT_NULL);

    clock_timer_dev = (struct clock_timer_device *)device;

    /*
    * (1 / freq) = (cnt + 1) * (1 / (clk/(prescaler_value + 1) ) )
    */

    TIM_SetCounter(clock_timer_dev->periph, 0);
    TIM_SetAutoreload(clock_timer_dev->periph, cnt - 1);

    if (mode == CLOCK_TIMER_MODE_ONESHOT)
    {
        TIM_SelectOnePulseMode(clock_timer_dev->periph, TIM_OPMode_Single);
    }
    else
    {
        TIM_SelectOnePulseMode(clock_timer_dev->periph, TIM_OPMode_Repetitive);
    }

    TIM_Cmd(clock_timer_dev->periph, ENABLE);

    LOG_D("%s start, cnt = %d", clock_timer_dev->name, cnt);

    return RT_EOK;
}

static void air32_clock_timer_stop(struct rt_clock_timer_device *device)
{
    struct clock_timer_device *clock_timer_dev;

    RT_ASSERT(device != RT_NULL);

    clock_timer_dev = (struct clock_timer_device *)device;

    TIM_Cmd(clock_timer_dev->periph, DISABLE);

    TIM_SetCounter(clock_timer_dev->periph, 0);
}

static rt_uint32_t air32_clock_timer_counter_get(struct rt_clock_timer_device *device)
{
    struct clock_timer_device *clock_timer_dev;

    RT_ASSERT(device != RT_NULL);

    clock_timer_dev = (struct clock_timer_device *)device;

    return clock_timer_dev->periph->CNT;
}

static rt_err_t air32_clock_timer_control(struct rt_clock_timer_device *device, rt_uint32_t cmd, void *arg)
{
    struct clock_timer_device *clock_timer_dev;
    rt_err_t result = RT_EOK;

    RT_ASSERT(device != RT_NULL);

    clock_timer_dev = (struct clock_timer_device *)device;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq = 0;
        rt_uint32_t clk = 0;
        rt_uint16_t prescaler_value = 0;

        /*
        * (1 / freq) = (cnt + 1) * (1 / (clk/(prescaler_value + 1) ) )
        */
        if (arg != RT_NULL)
        {

            freq = *((rt_uint32_t *)arg);

            clk = air32_tim_clock_get(clock_timer_dev->periph);

            prescaler_value = (rt_uint16_t)(clk / freq) - 1;

            TIM_PrescalerConfig(clock_timer_dev->periph, prescaler_value, TIM_PSCReloadMode_Immediate);
        }
        else
        {
            result = -RT_EINVAL;
        }
    }
    break;

    default:
        result = -RT_EINVAL;
        break;
    }

    return result;
}

static const struct rt_clock_timer_ops clock_timer_ops =
    {
        .init = air32_clock_timer_init,
        .start = air32_clock_timer_start,
        .stop = air32_clock_timer_stop,
        .count_get = air32_clock_timer_counter_get,
        .control = air32_clock_timer_control,
};

static int rt_hw_clock_timer_init(void)
{
    rt_err_t ret;
    struct rt_clock_timer_info *clock_timer_info;

#ifdef BSP_USING_TIM1
    clock_timer_info = air32_clock_timer_info_config_get(clock_timer_device1.periph);
    clock_timer_device1.parent.info = clock_timer_info;
    clock_timer_device1.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device1.parent, clock_timer_device1.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device1.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device1.name);
    }
#endif

#ifdef BSP_USING_TIM2
    clock_timer_info = air32_clock_timer_info_config_get(clock_timer_device2.periph);
    clock_timer_device2.parent.info = clock_timer_info;
    clock_timer_device2.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device2.parent, clock_timer_device2.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device2.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device2.name);
    }
#endif

#ifdef BSP_USING_TIM3
    clock_timer_info = air32_clock_timer_info_config_get(clock_timer_device3.periph);
    clock_timer_device3.parent.info = clock_timer_info;
    clock_timer_device3.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device3.parent, clock_timer_device3.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device3.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device3.name);
    }
#endif

#ifdef BSP_USING_TIM4
    clock_timer_info = air32_clock_timer_info_config_get(clock_timer_device4.periph);
    clock_timer_device4.parent.info = clock_timer_info;
    clock_timer_device4.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device4.parent, clock_timer_device4.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device4.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device4.name);
    }
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

#ifdef BSP_USING_TIM1
void TIM1_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device1.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device1.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device1.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM2
void TIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device2.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device2.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device2.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM3
void TIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device3.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device3.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device3.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM4
void TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device4.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device4.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device4.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#endif /* BSP_USING_CLOCK_TIMER */
