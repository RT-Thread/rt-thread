/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-12     hqfang       first version
 */

#include "drv_hwtimer.h"

#ifdef BSP_USING_HWTIMER

#if !defined(BSP_USING_HWTIMER0) && !defined(BSP_USING_HWTIMER1) && !defined(BSP_USING_HWTIMER2) \
    && !defined(BSP_USING_HWTIMER3) && !defined(BSP_USING_HWTIMER4)
    #error "Please define at least one BSP_USING_HWTIMERx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable HWTIMER */
#endif

static struct gd32_hwtimer_config hwtimer_config[] =
{
#ifdef BSP_USING_HWTIMER0
    {
        "timer0",
        TIMER0,
        TIMER0_UP_IRQn,
    },
#endif
#ifdef BSP_USING_HWTIMER1
    {
        "timer1",
        TIMER1,
        TIMER1_IRQn,
    },
#endif
#ifdef BSP_USING_HWTIMER2
    {
        "timer2",
        TIMER2,
        TIMER2_IRQn,
    },
#endif
#ifdef BSP_USING_HWTIMER3
    {
        "timer3",
        TIMER3,
        TIMER3_IRQn,
    },
#endif
#ifdef BSP_USING_HWTIMER4
    {
        "timer4",
        TIMER4,
        TIMER4_IRQn,
    },
#endif
#ifdef BSP_USING_HWTIMER5
    {
        "timer5",
        TIMER5,
        TIMER5_IRQn,
    },
#endif
#ifdef BSP_USING_HWTIMER6
    {
        "timer6",
        TIMER6,
        TIMER6_IRQn,
    },
#endif
};

static struct gd32_hwtimer hwtimer_obj[sizeof(hwtimer_config) / sizeof(hwtimer_config[0])] = {0};

static rt_err_t gd32_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct gd32_hwtimer_config *config;
    RT_ASSERT(timer != RT_NULL);

    config = (struct gd32_hwtimer_config *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint8_t clkpre;
        uint32_t pre;
        if (config->timer_periph != TIMER0)
        {
            clk = rcu_clock_freq_get(CK_APB1);
            clkpre = GET_BITS(RCU_CFG0, 8, 10);
        }
        else
        {
            clk = rcu_clock_freq_get(CK_APB2);
            clkpre = GET_BITS(RCU_CFG0, 11, 13);
        }
        if (clkpre >= 4)
        {
            clk = clk * 2;
        }
        pre = (clk / * ((uint32_t *)args)) - 1;
        TIMER_PSC(config->timer_periph) = (uint32_t)pre;
    }
    break;
    case HWTIMER_CTRL_STOP:
        timer_disable(config->timer_periph);
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t gd32_hwtimer_count_get(rt_hwtimer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    struct gd32_hwtimer_config *config;
    RT_ASSERT(timer != RT_NULL);

    config = (struct gd32_hwtimer_config *)timer->parent.user_data;

    CurrentTimer_Count = timer_counter_read(config->timer_periph);

    return CurrentTimer_Count;
}

static void gd32_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    struct gd32_hwtimer_config *config;
    timer_parameter_struct initpara;
    RT_ASSERT(timer != RT_NULL);
    config = (struct gd32_hwtimer_config *)timer->parent.user_data;

    if (state == 1)
    {
        timer_deinit(config->timer_periph);
        timer_struct_para_init(&initpara);
        timer_init(config->timer_periph, &initpara);
    }
    else
    {
        timer_disable(config->timer_periph);
        timer_interrupt_enable(config->timer_periph, TIMER_INT_FLAG_UP);
        ECLIC_DisableIRQ(config->irqn);
    }
}

static rt_err_t gd32_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    struct gd32_hwtimer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct gd32_hwtimer_config *)timer->parent.user_data;

    if (mode == HWTIMER_MODE_ONESHOT)
    {
        timer_single_pulse_mode_config(config->timer_periph, TIMER_SP_MODE_SINGLE);
    }
    else
    {
        timer_single_pulse_mode_config(config->timer_periph, TIMER_SP_MODE_REPETITIVE);
    }
    timer_counter_value_config(config->timer_periph, 0);
    timer_autoreload_value_config(config->timer_periph, cnt);
    timer_interrupt_enable(config->timer_periph, TIMER_INT_FLAG_UP);
    timer_enable(config->timer_periph);
    ECLIC_EnableIRQ(config->irqn);

    return RT_EOK;
}

static void gd32_hwtimer_stop(rt_hwtimer_t *timer)
{
    struct gd32_hwtimer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct gd32_hwtimer_config *)timer->parent.user_data;

    timer_disable(config->timer_periph);

    ECLIC_DisableIRQ(config->irqn);
}

static const struct rt_hwtimer_ops gd32_hwtimer_ops =
{
    .init = gd32_hwtimer_init,
    .start = gd32_hwtimer_start,
    .stop = gd32_hwtimer_stop,
    .count_get = gd32_hwtimer_count_get,
    .control = gd32_hwtimer_control,
};

static const struct rt_hwtimer_info gd32_hwtimer_info =
{
    54000000,           /* the maximum count frequency can be set */
    1000,               /* the minimum count frequency can be set */
    0xFFFF,
    HWTIMER_CNTMODE_UP,
};

#ifdef BSP_USING_HWTIMER0

void TIMER0_UP_IRQHandler(void)
{
    timer_interrupt_flag_clear(hwtimer_obj[0].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_device_hwtimer_isr(&hwtimer_obj[0].time_device);
}

#endif

#ifdef BSP_USING_HWTIMER1

void TIMER1_IRQHandler(void)
{
    timer_interrupt_flag_clear(hwtimer_obj[1].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_device_hwtimer_isr(&hwtimer_obj[1].time_device);
}

#endif

#ifdef BSP_USING_HWTIMER2

void TIMER2_IRQHandler(void)
{
    timer_interrupt_flag_clear(hwtimer_obj[2].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_device_hwtimer_isr(&hwtimer_obj[2].time_device);
}

#endif

#ifdef BSP_USING_HWTIMER3

void TIMER3_IRQHandler(void)
{
    timer_interrupt_flag_clear(hwtimer_obj[3].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_device_hwtimer_isr(&hwtimer_obj[3].time_device);
}

#endif

#ifdef BSP_USING_HWTIMER4

void TIMER4_IRQHandler(void)
{
    timer_interrupt_flag_clear(hwtimer_obj[4].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_device_hwtimer_isr(&hwtimer_obj[4].time_device);
}

#endif

#ifdef BSP_USING_HWTIMER5

void TIMER5_IRQHandler(void)
{
    timer_interrupt_flag_clear(hwtimer_obj[5].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_device_hwtimer_isr(&hwtimer_obj[5].time_device);
}

#endif

#ifdef BSP_USING_HWTIMER6

void TIMER6_IRQHandler(void)
{
    timer_interrupt_flag_clear(hwtimer_obj[6].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_device_hwtimer_isr(&hwtimer_obj[6].time_device);
}

#endif

static int rt_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

#ifdef BSP_USING_HWTIMER0
    rcu_periph_clock_enable(RCU_TIMER0);
#endif
#ifdef BSP_USING_HWTIMER1
    rcu_periph_clock_enable(RCU_TIMER1);
#endif
#ifdef BSP_USING_HWTIMER2
    rcu_periph_clock_enable(RCU_TIMER2);
#endif
#ifdef BSP_USING_HWTIMER3
    rcu_periph_clock_enable(RCU_TIMER3);
#endif
#ifdef BSP_USING_HWTIMER4
    rcu_periph_clock_enable(RCU_TIMER4);
#endif
#ifdef BSP_USING_HWTIMER5
    rcu_periph_clock_enable(RCU_TIMER5);
#endif
#ifdef BSP_USING_HWTIMER6
    rcu_periph_clock_enable(RCU_TIMER6);
#endif

    for (i = 0; i < sizeof(hwtimer_obj) / sizeof(hwtimer_obj[0]); i++)
    {
        hwtimer_obj[i].time_device.info = &gd32_hwtimer_info;
        hwtimer_obj[i].time_device.ops  = &gd32_hwtimer_ops;
        hwtimer_obj[i].config = &hwtimer_config[i];
        rt_device_hwtimer_register(&hwtimer_obj[i].time_device, \
                                   hwtimer_obj[i].config->name, hwtimer_obj[i].config);
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hwtimer_init);

#endif /* RT_USING_HWTIMER */
