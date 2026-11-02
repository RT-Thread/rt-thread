/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-01-21     charlown           first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_CLOCK_TIMER

#define LOG_TAG "drv.clock_timer"
#include <drv_log.h>

struct clock_timer_device
{
    struct rt_clock_timer_device parent;
    TIM_TypeDef *periph;
    IRQn_Type irqn;
    char *name;
};

#ifdef BSP_USING_TIM1_CLOCK_TIMER
struct clock_timer_device clock_timer_device1 =
    {
        .periph = TIM1,
        .irqn = TIM1_UP_IRQn,
        .name = "timer1"};
#endif

#ifdef BSP_USING_TIM2_CLOCK_TIMER
struct clock_timer_device clock_timer_device2 =
    {
        .periph = TIM2,
        .irqn = TIM2_IRQn,
        .name = "timer2"};
#endif

#ifdef BSP_USING_TIM3_CLOCK_TIMER
struct clock_timer_device clock_timer_device3 =
    {
        .periph = TIM3,
        .irqn = TIM3_IRQn,
        .name = "timer3"};
#endif

#ifdef BSP_USING_TIM4_CLOCK_TIMER
struct clock_timer_device clock_timer_device4 =
    {
        .periph = TIM4,
        .irqn = TIM4_IRQn,
        .name = "timer4"};
#endif

#ifdef BSP_USING_TIM5_CLOCK_TIMER
struct clock_timer_device clock_timer_device5 =
    {
        .periph = TIM5,
        .irqn = TIM5_IRQn,
        .name = "timer5"};
#endif

#ifdef BSP_USING_TIM6_CLOCK_TIMER
struct clock_timer_device clock_timer_device6 =
    {
        .periph = TIM6,
        .irqn = TIM6_IRQn,
        .name = "timer6"};
#endif

#ifdef BSP_USING_TIM7_CLOCK_TIMER
struct clock_timer_device clock_timer_device7 =
    {
        .periph = TIM7,
        .irqn = TIM7_IRQn,
        .name = "timer7"};
#endif

#ifdef BSP_USING_TIM8_CLOCK_TIMER
struct clock_timer_device clock_timer_device8 =
    {
        .periph = TIM8,
        .irqn = TIM8_UP_IRQn,
        .name = "timer8"};
#endif

#ifdef BSP_USING_TIM9_CLOCK_TIMER
struct clock_timer_device clock_timer_device9 =
    {
        .periph = TIM9,
        .irqn = TIM9_UP_IRQn,
        .name = "timer9"};
#endif

#ifdef BSP_USING_TIM10_CLOCK_TIMER
struct clock_timer_device clock_timer_device10 =
    {
        .periph = TIM10,
        .irqn = TIM10_UP_IRQn,
        .name = "timer10"};
#endif

static void ch32f2_clock_timer_init(struct rt_clock_timer_device *device, rt_uint32_t state)
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
        ch32f2_tim_clock_init(clock_timer_dev->periph);

        clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_dev->periph);

        clk = ch32f2_tim_clock_get(clock_timer_dev->periph);

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

static rt_err_t ch32f2_clock_timer_start(struct rt_clock_timer_device *device, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
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

static void ch32f2_clock_timer_stop(struct rt_clock_timer_device *device)
{
    struct clock_timer_device *clock_timer_dev;

    RT_ASSERT(device != RT_NULL);

    clock_timer_dev = (struct clock_timer_device *)device;

    TIM_Cmd(clock_timer_dev->periph, DISABLE);

    TIM_SetCounter(clock_timer_dev->periph, 0);
}

static rt_uint32_t ch32f2_clock_timer_counter_get(struct rt_clock_timer_device *device)
{
    struct clock_timer_device *clock_timer_dev;

    RT_ASSERT(device != RT_NULL);

    clock_timer_dev = (struct clock_timer_device *)device;

    return clock_timer_dev->periph->CNT;
}

static rt_err_t ch32f2_clock_timer_control(struct rt_clock_timer_device *device, rt_uint32_t cmd, void *arg)
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

            clk = ch32f2_tim_clock_get(clock_timer_dev->periph);

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
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static const struct rt_clock_timer_ops clock_timer_ops =
    {
        .init = ch32f2_clock_timer_init,
        .start = ch32f2_clock_timer_start,
        .stop = ch32f2_clock_timer_stop,
        .count_get = ch32f2_clock_timer_counter_get,
        .control = ch32f2_clock_timer_control,
};

static int rt_hw_clock_timer_init(void)
{
    rt_err_t ret;
    struct rt_clock_timer_info *clock_timer_info;

#ifdef BSP_USING_TIM1_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device1.periph);
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

#ifdef BSP_USING_TIM2_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device2.periph);
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

#ifdef BSP_USING_TIM3_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device3.periph);
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

#ifdef BSP_USING_TIM4_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device4.periph);
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

#ifdef BSP_USING_TIM5_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device5.periph);
    clock_timer_device5.parent.info = clock_timer_info;
    clock_timer_device5.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device5.parent, clock_timer_device5.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device5.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device5.name);
    }
#endif

#ifdef BSP_USING_TIM6_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device6.periph);
    clock_timer_device6.parent.info = clock_timer_info;
    clock_timer_device6.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device6.parent, clock_timer_device6.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device6.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device6.name);
    }
#endif

#ifdef BSP_USING_TIM7_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device7.periph);
    clock_timer_device7.parent.info = clock_timer_info;
    clock_timer_device7.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device7.parent, clock_timer_device7.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device7.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device7.name);
    }
#endif

#ifdef BSP_USING_TIM8_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device8.periph);
    clock_timer_device8.parent.info = clock_timer_info;
    clock_timer_device8.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device8.parent, clock_timer_device8.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device8.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device8.name);
    }
#endif

#ifdef BSP_USING_TIM9_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device9.periph);
    clock_timer_device9.parent.info = clock_timer_info;
    clock_timer_device9.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device9.parent, clock_timer_device9.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device9.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device9.name);
    }
#endif

#ifdef BSP_USING_TIM10_CLOCK_TIMER
    clock_timer_info = ch32f2_clock_timer_info_config_get(clock_timer_device10.periph);
    clock_timer_device10.parent.info = clock_timer_info;
    clock_timer_device10.parent.ops = &clock_timer_ops;
    ret = rt_clock_timer_register(&clock_timer_device10.parent, clock_timer_device10.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("clock_timer: %s register success.", clock_timer_device10.name);
    }
    else
    {
        LOG_D("clock_timer: %s register failed.", clock_timer_device10.name);
    }
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

#ifdef BSP_USING_TIM1_CLOCK_TIMER
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

#ifdef BSP_USING_TIM2_CLOCK_TIMER
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

#ifdef BSP_USING_TIM3_CLOCK_TIMER
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

#ifdef BSP_USING_TIM4_CLOCK_TIMER
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

#ifdef BSP_USING_TIM5_CLOCK_TIMER
void TIM5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device5.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device5.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device5.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM6_CLOCK_TIMER
void TIM6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device6.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device6.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device6.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM7_CLOCK_TIMER
void TIM7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device7.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device7.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device7.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM8_CLOCK_TIMER
void TIM8_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device8.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device8.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device8.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM9_CLOCK_TIMER
void TIM9_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device9.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device9.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device9.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM10_CLOCK_TIMER
void TIM10_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(clock_timer_device10.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(clock_timer_device10.periph, TIM_IT_Update);
        rt_clock_timer_isr(&clock_timer_device10.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#endif /* BSP_USING_CLOCK_TIMER */
