/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-02-25     iysheng           first version
 */

#include <board.h>
#include <rtdevice.h>
#include <drivers/clock_time.h>

#ifdef BSP_USING_CLOCK_TIMER

typedef struct {
    uint32_t reg_base;
    IRQn_Type irqn;
    rcu_periph_enum rcu;
} gd32_clock_timer_data;

typedef struct {
    char dev_name[RT_NAME_MAX];
    const gd32_clock_timer_data hw_data;
    rt_clock_timer_t clock_timer_dev;
    const struct rt_clock_timer_info clock_timer_info;
} gd32_clock_timer_device;

enum timer_index_E {
#ifdef BSP_USING_CLOCK_TIMER0
    TIM0_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER3
    TIM3_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER4
    TIM4_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER5
    TIM5_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER6
    TIM6_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER7
    TIM7_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER8
    TIM8_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER9
    TIM9_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER10
    TIM10_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER11
    TIM11_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER12
    TIM12_INDEX,
#endif
#ifdef BSP_USING_CLOCK_TIMER13
    TIM13_INDEX,
#endif
};

/*
 * static void __set_timerx_freq
 * Set freq with timerx
 *
 * @param timerx the pointer of TIMER_TypeDef
 * @param freq of the timer clock
 * @retval None
 */
static void __set_timerx_freq(uint32_t timerx, uint32_t freq)
{
    uint32_t ap1freq, ap2freq;
    uint16_t prescaler;
    uint32_t temp;

    if (timerx == TIMER0 || timerx == TIMER7 || timerx == TIMER8 \
        || timerx == TIMER9 || timerx == TIMER10)
    {
        ap2freq = rcu_clock_freq_get(CK_APB2);
        temp = RCU_CFG0 & RCU_CFG0_APB2PSC;
        temp >>= 11;
        /* whether should frequency doubling */
        temp = (temp < 4) ? 0 : 1;

        prescaler = (ap2freq << temp) / freq - 1;
    }
    else
    {
        ap1freq = rcu_clock_freq_get(CK_APB1);
        temp = RCU_CFG0 & RCU_CFG0_APB1PSC;
        temp >>= 8;
        /* whether should frequency doubling */
        temp = (temp < 4) ? 0 : 1;

        prescaler = (ap1freq << temp) / freq - 1;
    }

    timer_prescaler_config(timerx, prescaler, TIMER_PSC_RELOAD_NOW);
}

static void gd32_clock_timer_init(struct rt_clock_timer_device *timer, rt_uint32_t state)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;
    timer_parameter_struct initpara;

    if (state)
    {
        timer_internal_clock_config(timer_base);
        timer_struct_para_init(&initpara);
        initpara.period =  timer->info->maxcnt;
        timer_init(timer_base, &initpara);
        __set_timerx_freq(timer_base, timer->info->maxfreq);
    }
}

static rt_err_t gd32_clock_timer_start(struct rt_clock_timer_device *timer, \
    rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;

    if (mode == CLOCK_TIMER_MODE_ONESHOT)
    {
        timer_single_pulse_mode_config(timer_base, TIMER_SP_MODE_SINGLE);
    }
    else if (mode == CLOCK_TIMER_MODE_PERIOD)
    {
        timer_single_pulse_mode_config(timer_base, TIMER_SP_MODE_REPETITIVE);
    }

    timer_counter_value_config(timer_base, 0);
    timer_autoreload_value_config(timer_base, cnt - 1);
    timer_enable(timer_base);

    return 0;
}

static void gd32_clock_timer_stop(struct rt_clock_timer_device *timer)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;

    timer_disable(timer_base);
}

static rt_uint32_t gd32_clock_timer_count_get(struct rt_clock_timer_device *timer)
{
    uint32_t timer_base = (uint32_t)timer->parent.user_data;
    rt_uint32_t count;

    count = timer_counter_read(timer_base);

    return count;
}

static rt_err_t gd32_clock_timer_control(struct rt_clock_timer_device *timer, rt_uint32_t cmd, \
    void *args)
{
    int ret = RT_EOK;
    rt_int32_t freq;
    rt_clock_timer_mode_t mode;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
        freq = *(rt_uint32_t *)args;
        __set_timerx_freq((uint32_t)timer->parent.user_data, freq);
        break;
    default:
        rt_kprintf("invalid cmd:%x\n", cmd);
        ret = -RT_EINVAL;
        break;
    }

    return ret;
}

static const struct rt_clock_timer_ops g_gd32_clock_timer_ops = {
    gd32_clock_timer_init,
    gd32_clock_timer_start,
    gd32_clock_timer_stop,
    gd32_clock_timer_count_get,
    gd32_clock_timer_control,
};

static gd32_clock_timer_device g_gd32_clock_timer[] = {
#ifdef BSP_USING_CLOCK_TIMER0
    {
        "timer0",
        {
             TIMER0,
             TIMER0_UP_IRQn,
             RCU_TIMER0,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER1
    {
        "timer1",
        {
             TIMER1,
             TIMER1_IRQn,
             RCU_TIMER1,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER2
    {
        "timer2",
        {
             TIMER2,
             TIMER2_IRQn,
             RCU_TIMER2,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER3
    {
        "timer3",
        {
             TIMER3,
             TIMER3_IRQn,
             RCU_TIMER3,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER4
    {
        "timer4",
        {
             TIMER4,
             TIMER4_IRQn,
             RCU_TIMER4,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER5
    {
        "timer5",
        {
             TIMER5,
             TIMER5_IRQn,
             RCU_TIMER5,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER6
    {
        "timer6",
        {
             TIMER6,
             TIMER6_IRQn,
             RCU_TIMER6,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER7
    {
        "timer7",
        {
             TIMER7,
             TIMER7_UP_IRQn,
             RCU_TIMER7,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER8
    {
        "timer8",
        {
             TIMER8,
             TIMER8_IRQn,
             RCU_TIMER8,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER9
    {
        "timer9",
        {
             TIMER9,
             TIMER9_IRQn,
             RCU_TIMER9,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER10
    {
        "timer10",
        {
             TIMER10,
             TIMER10_IRQn,
             RCU_TIMER10,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER11
    {
        "timer11",
        {
             TIMER11,
             TIMER11_IRQn,
             RCU_TIMER11,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER12
    {
        "timer12",
        {
             TIMER12,
             TIMER12_IRQn,
             RCU_TIMER12,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
#ifdef BSP_USING_CLOCK_TIMER13
    {
        "timer13",
        {
             TIMER13,
             TIMER13_IRQn,
             RCU_TIMER13,
        },
        {0},
        {
            1000000,
            1000,
            0xffff,
            0, /* count up mode  */
        }
    },
#endif
};

#ifdef BSP_USING_CLOCK_TIMER0
void TIMER0_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM0_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM0_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER1
void TIMER1_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM1_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM1_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER2
void TIMER2_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM2_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM2_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER3
void TIMER3_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM3_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM3_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER4
void TIMER4_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM4_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM4_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER5
void TIMER5_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM5_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM5_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER6
void TIMER6_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM6_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM6_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER7
void TIMER7_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_clock_timer_isr(&g_gd32_clock_timer[TIM7_INDEX].clock_timer_dev);
    timer_flag_clear((uint32_t)g_gd32_clock_timer[TIM7_INDEX].clock_timer_dev.parent.user_data, \
        TIMER_INT_UP);
    rt_interrupt_leave();
}
#endif

static int rt_clock_timer_init(void)
{
    int ret = 0, i = 0;

    for (; i < sizeof(g_gd32_clock_timer) / sizeof(g_gd32_clock_timer[0]); i++)
    {
        g_gd32_clock_timer[i].clock_timer_dev.ops = &g_gd32_clock_timer_ops;
        g_gd32_clock_timer[i].clock_timer_dev.info = &g_gd32_clock_timer[i].clock_timer_info;

        rcu_periph_clock_enable(g_gd32_clock_timer[i].hw_data.rcu);
        NVIC_SetPriority(g_gd32_clock_timer[i].hw_data.irqn, 0);
        NVIC_EnableIRQ(g_gd32_clock_timer[i].hw_data.irqn);
        timer_interrupt_enable(g_gd32_clock_timer[i].hw_data.reg_base, TIMER_INT_UP);
        ret = rt_clock_timer_register(&g_gd32_clock_timer[i].clock_timer_dev, \
            g_gd32_clock_timer[i].dev_name, (void *)g_gd32_clock_timer[i].hw_data.reg_base);
        if (RT_EOK != ret)
        {
            rt_kprintf("failed register %s, err=%d\n", g_gd32_clock_timer[i].dev_name, \
                ret);
            break;
        }
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_clock_timer_init);
#endif
