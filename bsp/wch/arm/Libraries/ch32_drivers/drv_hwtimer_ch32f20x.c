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

#ifdef BSP_USING_HWTIMER

#define LOG_TAG "drv.hwtimer"
#include <drv_log.h>

struct hwtimer_device
{
    struct rt_hwtimer_device parent;
    TIM_TypeDef *periph;
    IRQn_Type irqn;
    char *name;
};

#ifdef BSP_USING_TIM1_HWTIMER
struct hwtimer_device hwtimer_device1 =
    {
        .periph = TIM1,
        .irqn = TIM1_UP_IRQn,
        .name = "timer1"};
#endif

#ifdef BSP_USING_TIM2_HWTIMER
struct hwtimer_device hwtimer_device2 =
    {
        .periph = TIM2,
        .irqn = TIM2_IRQn,
        .name = "timer2"};
#endif

#ifdef BSP_USING_TIM3_HWTIMER
struct hwtimer_device hwtimer_device3 =
    {
        .periph = TIM3,
        .irqn = TIM3_IRQn,
        .name = "timer3"};
#endif

#ifdef BSP_USING_TIM4_HWTIMER
struct hwtimer_device hwtimer_device4 =
    {
        .periph = TIM4,
        .irqn = TIM4_IRQn,
        .name = "timer4"};
#endif

#ifdef BSP_USING_TIM5_HWTIMER
struct hwtimer_device hwtimer_device5 =
    {
        .periph = TIM5,
        .irqn = TIM5_IRQn,
        .name = "timer5"};
#endif

#ifdef BSP_USING_TIM6_HWTIMER
struct hwtimer_device hwtimer_device6 =
    {
        .periph = TIM6,
        .irqn = TIM6_IRQn,
        .name = "timer6"};
#endif

#ifdef BSP_USING_TIM7_HWTIMER
struct hwtimer_device hwtimer_device7 =
    {
        .periph = TIM7,
        .irqn = TIM7_IRQn,
        .name = "timer7"};
#endif

#ifdef BSP_USING_TIM8_HWTIMER
struct hwtimer_device hwtimer_device8 =
    {
        .periph = TIM8,
        .irqn = TIM8_UP_IRQn,
        .name = "timer8"};
#endif

#ifdef BSP_USING_TIM9_HWTIMER
struct hwtimer_device hwtimer_device9 =
    {
        .periph = TIM9,
        .irqn = TIM9_UP_IRQn,
        .name = "timer9"};
#endif

#ifdef BSP_USING_TIM10_HWTIMER
struct hwtimer_device hwtimer_device10 =
    {
        .periph = TIM10,
        .irqn = TIM10_UP_IRQn,
        .name = "timer10"};
#endif

static void ch32f2_hwtimer_init(struct rt_hwtimer_device *device, rt_uint32_t state)
{
    struct hwtimer_device *hwtimer_dev;
    struct rt_hwtimer_info *hwtimer_info;
    rt_uint32_t clk = 0;
    rt_uint16_t prescaler_value = 0;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitType;
    NVIC_InitTypeDef NVIC_InitStructure;

    RT_ASSERT(device != RT_NULL);

    hwtimer_dev = (struct hwtimer_device *)device;

    if (state)
    {
        ch32f2_tim_clock_init(hwtimer_dev->periph);

        hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_dev->periph);

        clk = ch32f2_tim_clock_get(hwtimer_dev->periph);

        prescaler_value = (rt_uint16_t)(clk / hwtimer_info->minfreq) - 1;

        /*
        * (1 / freq) = (cnt + 1) * (1 / (clk/(prescaler_value + 1) ) )
        */

        TIM_TimeBaseInitType.TIM_Period = hwtimer_info->maxcnt - 1;
        TIM_TimeBaseInitType.TIM_Prescaler = prescaler_value;
        TIM_TimeBaseInitType.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitType.TIM_RepetitionCounter = 0;

        if (hwtimer_info == RT_NULL)
        {
            TIM_TimeBaseInitType.TIM_CounterMode = TIM_CounterMode_Up;
        }
        else
        {
            if (hwtimer_info->cntmode == HWTIMER_CNTMODE_UP)
            {
                TIM_TimeBaseInitType.TIM_CounterMode = TIM_CounterMode_Up;
            }
            else
            {
                TIM_TimeBaseInitType.TIM_CounterMode = TIM_CounterMode_Down;
            }
        }

        TIM_TimeBaseInit(hwtimer_dev->periph, &TIM_TimeBaseInitType);

        NVIC_InitStructure.NVIC_IRQChannel = hwtimer_dev->irqn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        TIM_ITConfig(hwtimer_dev->periph, TIM_IT_Update, ENABLE);
        TIM_ClearITPendingBit(hwtimer_dev->periph, TIM_IT_Update);

        LOG_D("%s init success", hwtimer_dev->name);
    }
}

static rt_err_t ch32f2_hwtimer_start(struct rt_hwtimer_device *device, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{

    struct hwtimer_device *hwtimer_dev;

    RT_ASSERT(device != RT_NULL);

    hwtimer_dev = (struct hwtimer_device *)device;

    /*
    * (1 / freq) = (cnt + 1) * (1 / (clk/(prescaler_value + 1) ) )
    */

    TIM_SetCounter(hwtimer_dev->periph, 0);
    TIM_SetAutoreload(hwtimer_dev->periph, cnt - 1);

    if (mode == HWTIMER_MODE_ONESHOT)
    {
        TIM_SelectOnePulseMode(hwtimer_dev->periph, TIM_OPMode_Single);
    }
    else
    {
        TIM_SelectOnePulseMode(hwtimer_dev->periph, TIM_OPMode_Repetitive);
    }

    TIM_Cmd(hwtimer_dev->periph, ENABLE);

    LOG_D("%s start, cnt = %d", hwtimer_dev->name, cnt);

    return RT_EOK;
}

static void ch32f2_hwtimer_stop(struct rt_hwtimer_device *device)
{
    struct hwtimer_device *hwtimer_dev;

    RT_ASSERT(device != RT_NULL);

    hwtimer_dev = (struct hwtimer_device *)device;

    TIM_Cmd(hwtimer_dev->periph, DISABLE);

    TIM_SetCounter(hwtimer_dev->periph, 0);
}

static rt_uint32_t ch32f2_hwtimer_counter_get(struct rt_hwtimer_device *device)
{
    struct hwtimer_device *hwtimer_dev;

    RT_ASSERT(device != RT_NULL);

    hwtimer_dev = (struct hwtimer_device *)device;

    return hwtimer_dev->periph->CNT;
}

static rt_err_t ch32f2_hwtimer_control(struct rt_hwtimer_device *device, rt_uint32_t cmd, void *arg)
{
    struct hwtimer_device *hwtimer_dev;
    rt_err_t result = RT_EOK;

    RT_ASSERT(device != RT_NULL);

    hwtimer_dev = (struct hwtimer_device *)device;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
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

            clk = ch32f2_tim_clock_get(hwtimer_dev->periph);

            prescaler_value = (rt_uint16_t)(clk / freq) - 1;

            TIM_PrescalerConfig(hwtimer_dev->periph, prescaler_value, TIM_PSCReloadMode_Immediate);
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

static const struct rt_hwtimer_ops hwtimer_ops =
    {
        .init = ch32f2_hwtimer_init,
        .start = ch32f2_hwtimer_start,
        .stop = ch32f2_hwtimer_stop,
        .count_get = ch32f2_hwtimer_counter_get,
        .control = ch32f2_hwtimer_control,
};

static int rt_hw_hwtimer_init(void)
{
    rt_err_t ret;
    struct rt_hwtimer_info *hwtimer_info;

#ifdef BSP_USING_TIM1_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device1.periph);
    hwtimer_device1.parent.info = hwtimer_info;
    hwtimer_device1.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device1.parent, hwtimer_device1.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device1.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device1.name);
    }
#endif

#ifdef BSP_USING_TIM2_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device2.periph);
    hwtimer_device2.parent.info = hwtimer_info;
    hwtimer_device2.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device2.parent, hwtimer_device2.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device2.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device2.name);
    }
#endif

#ifdef BSP_USING_TIM3_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device3.periph);
    hwtimer_device3.parent.info = hwtimer_info;
    hwtimer_device3.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device3.parent, hwtimer_device3.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device3.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device3.name);
    }
#endif

#ifdef BSP_USING_TIM4_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device4.periph);
    hwtimer_device4.parent.info = hwtimer_info;
    hwtimer_device4.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device4.parent, hwtimer_device4.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device4.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device4.name);
    }
#endif

#ifdef BSP_USING_TIM5_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device5.periph);
    hwtimer_device5.parent.info = hwtimer_info;
    hwtimer_device5.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device5.parent, hwtimer_device5.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device5.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device5.name);
    }
#endif

#ifdef BSP_USING_TIM6_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device6.periph);
    hwtimer_device6.parent.info = hwtimer_info;
    hwtimer_device6.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device6.parent, hwtimer_device6.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device6.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device6.name);
    }
#endif

#ifdef BSP_USING_TIM7_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device7.periph);
    hwtimer_device7.parent.info = hwtimer_info;
    hwtimer_device7.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device7.parent, hwtimer_device7.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device7.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device7.name);
    }
#endif

#ifdef BSP_USING_TIM8_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device8.periph);
    hwtimer_device8.parent.info = hwtimer_info;
    hwtimer_device8.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device8.parent, hwtimer_device8.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device8.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device8.name);
    }
#endif

#ifdef BSP_USING_TIM9_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device9.periph);
    hwtimer_device9.parent.info = hwtimer_info;
    hwtimer_device9.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device9.parent, hwtimer_device9.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device9.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device9.name);
    }
#endif

#ifdef BSP_USING_TIM10_HWTIMER
    hwtimer_info = ch32f2_hwtimer_info_config_get(hwtimer_device10.periph);
    hwtimer_device10.parent.info = hwtimer_info;
    hwtimer_device10.parent.ops = &hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer_device10.parent, hwtimer_device10.name, RT_NULL);
    if (ret == RT_EOK)
    {
        LOG_D("hwtimer: %s register success.", hwtimer_device10.name);
    }
    else
    {
        LOG_D("hwtimer: %s register failed.", hwtimer_device10.name);
    }
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);

#ifdef BSP_USING_TIM1_HWTIMER
void TIM1_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device1.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device1.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device1.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM2_HWTIMER
void TIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device2.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device2.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device2.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM3_HWTIMER
void TIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device3.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device3.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device3.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM4_HWTIMER
void TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device4.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device4.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device4.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM5_HWTIMER
void TIM5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device5.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device5.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device5.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM6_HWTIMER
void TIM6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device6.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device6.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device6.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM7_HWTIMER
void TIM7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device7.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device7.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device7.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM8_HWTIMER
void TIM8_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device8.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device8.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device8.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM9_HWTIMER
void TIM9_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device9.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device9.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device9.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM10_HWTIMER
void TIM10_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIM_GetITStatus(hwtimer_device10.periph, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(hwtimer_device10.periph, TIM_IT_Update);
        rt_device_hwtimer_isr(&hwtimer_device10.parent);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#endif /* BSP_USING_HWTIMER */
