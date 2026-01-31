/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-12     hqfang       first version
 */

#include "drv_timer.h"

#ifdef BSP_USING_CLOCK_TIMER

#if !defined(BSP_USING_CLOCK_TIMER0) && !defined(BSP_USING_CLOCK_TIMER1) && !defined(BSP_USING_CLOCK_TIMER2) \
    && !defined(BSP_USING_CLOCK_TIMER3) && !defined(BSP_USING_CLOCK_TIMER4)
    #error "Please define at least one BSP_USING_CLOCK_TIMERx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable CLOCK_TIMER */
#endif

static struct gd32_clock_timer_config clock_timer_config[] =
{
#ifdef BSP_USING_CLOCK_TIMER0
    {
        "timer0",
        TIMER0,
        TIMER0_UP_IRQn,
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER1
    {
        "timer1",
        TIMER1,
        TIMER1_IRQn,
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER2
    {
        "timer2",
        TIMER2,
        TIMER2_IRQn,
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER3
    {
        "timer3",
        TIMER3,
        TIMER3_IRQn,
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER4
    {
        "timer4",
        TIMER4,
        TIMER4_IRQn,
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER5
    {
        "timer5",
        TIMER5,
        TIMER5_IRQn,
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER6
    {
        "timer6",
        TIMER6,
        TIMER6_IRQn,
    },
#endif
};

static struct gd32_clock_timer clock_timer_obj[sizeof(clock_timer_config) / sizeof(clock_timer_config[0])] = {0};

static rt_err_t gd32_clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct gd32_clock_timer_config *config;
    RT_ASSERT(timer != RT_NULL);

    config = (struct gd32_clock_timer_config *)timer->parent.user_data;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
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
    case CLOCK_TIMER_CTRL_STOP:
        timer_disable(config->timer_periph);
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t gd32_clock_timer_count_get(rt_clock_timer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    struct gd32_clock_timer_config *config;
    RT_ASSERT(timer != RT_NULL);

    config = (struct gd32_clock_timer_config *)timer->parent.user_data;

    CurrentTimer_Count = timer_counter_read(config->timer_periph);

    return CurrentTimer_Count;
}

static void gd32_clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    struct gd32_clock_timer_config *config;
    timer_parameter_struct initpara;
    RT_ASSERT(timer != RT_NULL);
    config = (struct gd32_clock_timer_config *)timer->parent.user_data;

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

static rt_err_t gd32_clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    struct gd32_clock_timer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct gd32_clock_timer_config *)timer->parent.user_data;

    if (mode == CLOCK_TIMER_MODE_ONESHOT)
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

static void gd32_clock_timer_stop(rt_clock_timer_t *timer)
{
    struct gd32_clock_timer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct gd32_clock_timer_config *)timer->parent.user_data;

    timer_disable(config->timer_periph);

    ECLIC_DisableIRQ(config->irqn);
}

static const struct rt_clock_timer_ops gd32_clock_timer_ops =
{
    .init = gd32_clock_timer_init,
    .start = gd32_clock_timer_start,
    .stop = gd32_clock_timer_stop,
    .count_get = gd32_clock_timer_count_get,
    .control = gd32_clock_timer_control,
};

static const struct rt_clock_timer_info gd32_clock_timer_info =
{
    54000000,           /* the maximum count frequency can be set */
    1000,               /* the minimum count frequency can be set */
    0xFFFF,
    CLOCK_TIMER_CNTMODE_UP,
};

#ifdef BSP_USING_CLOCK_TIMER0

void TIMER0_UP_IRQHandler(void)
{
    timer_interrupt_flag_clear(clock_timer_obj[0].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_clock_timer_isr(&clock_timer_obj[0].time_device);
}

#endif

#ifdef BSP_USING_CLOCK_TIMER1

void TIMER1_IRQHandler(void)
{
    timer_interrupt_flag_clear(clock_timer_obj[1].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_clock_timer_isr(&clock_timer_obj[1].time_device);
}

#endif

#ifdef BSP_USING_CLOCK_TIMER2

void TIMER2_IRQHandler(void)
{
    timer_interrupt_flag_clear(clock_timer_obj[2].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_clock_timer_isr(&clock_timer_obj[2].time_device);
}

#endif

#ifdef BSP_USING_CLOCK_TIMER3

void TIMER3_IRQHandler(void)
{
    timer_interrupt_flag_clear(clock_timer_obj[3].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_clock_timer_isr(&clock_timer_obj[3].time_device);
}

#endif

#ifdef BSP_USING_CLOCK_TIMER4

void TIMER4_IRQHandler(void)
{
    timer_interrupt_flag_clear(clock_timer_obj[4].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_clock_timer_isr(&clock_timer_obj[4].time_device);
}

#endif

#ifdef BSP_USING_CLOCK_TIMER5

void TIMER5_IRQHandler(void)
{
    timer_interrupt_flag_clear(clock_timer_obj[5].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_clock_timer_isr(&clock_timer_obj[5].time_device);
}

#endif

#ifdef BSP_USING_CLOCK_TIMER6

void TIMER6_IRQHandler(void)
{
    timer_interrupt_flag_clear(clock_timer_obj[6].config->timer_periph, TIMER_INT_FLAG_UP);
    rt_clock_timer_isr(&clock_timer_obj[6].time_device);
}

#endif

static int rt_clock_timer_init(void)
{
    int i = 0;
    int result = RT_EOK;

#ifdef BSP_USING_CLOCK_TIMER0
    rcu_periph_clock_enable(RCU_TIMER0);
#endif
#ifdef BSP_USING_CLOCK_TIMER1
    rcu_periph_clock_enable(RCU_TIMER1);
#endif
#ifdef BSP_USING_CLOCK_TIMER2
    rcu_periph_clock_enable(RCU_TIMER2);
#endif
#ifdef BSP_USING_CLOCK_TIMER3
    rcu_periph_clock_enable(RCU_TIMER3);
#endif
#ifdef BSP_USING_CLOCK_TIMER4
    rcu_periph_clock_enable(RCU_TIMER4);
#endif
#ifdef BSP_USING_CLOCK_TIMER5
    rcu_periph_clock_enable(RCU_TIMER5);
#endif
#ifdef BSP_USING_CLOCK_TIMER6
    rcu_periph_clock_enable(RCU_TIMER6);
#endif

    for (i = 0; i < sizeof(clock_timer_obj) / sizeof(clock_timer_obj[0]); i++)
    {
        clock_timer_obj[i].time_device.info = &gd32_clock_timer_info;
        clock_timer_obj[i].time_device.ops  = &gd32_clock_timer_ops;
        clock_timer_obj[i].config = &clock_timer_config[i];
        rt_clock_timer_register(&clock_timer_obj[i].time_device, \
                                   clock_timer_obj[i].config->name, clock_timer_obj[i].config);
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_clock_timer_init);

#endif /* RT_USING_CLOCK_TIME */
