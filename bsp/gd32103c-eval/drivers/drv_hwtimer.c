/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-28     iysheng           first version
 */

#include <board.h>
#include <drivers/drv_comm.h>
#include <drivers/drv_hwtimer.h>

#ifdef BSP_USING_HWTIMER

enum timer_index_E {
#ifdef BSP_USING_HWTIMER0
    TIM0_INDEX,
#endif
#ifdef BSP_USING_HWTIMER1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_HWTIMER2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_HWTIMER3
    TIM3_INDEX,
#endif
#ifdef BSP_USING_HWTIMER4
    TIM4_INDEX,
#endif
#ifdef BSP_USING_HWTIMER5
    TIM5_INDEX,
#endif
#ifdef BSP_USING_HWTIMER6
    TIM6_INDEX,
#endif
#ifdef BSP_USING_HWTIMER7
    TIM7_INDEX,
#endif
#ifdef BSP_USING_HWTIMER8
    TIM8_INDEX,
#endif
#ifdef BSP_USING_HWTIMER9
    TIM9_INDEX,
#endif
#ifdef BSP_USING_HWTIMER10
    TIM10_INDEX,
#endif
#ifdef BSP_USING_HWTIMER11
    TIM11_INDEX,
#endif
#ifdef BSP_USING_HWTIMER12
    TIM12_INDEX,
#endif
#ifdef BSP_USING_HWTIMER13
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
static void __set_timerx_freq(TIMER_TypeDef *timerx, uint32_t freq)
{
    RCC_ClocksPara RCC_Clocks = {0};
    uint16_t prescaler;
    uint32_t temp;

    RCC_GetClocksFreq(&RCC_Clocks);
    if (timerx == TIMER0 || timerx == TIMER7 || timerx == TIMER8 \
        || timerx == TIMER9 || timerx == TIMER10)
    {
        temp = RCC->GCFGR & RCC_GCFGR_APB2PS;
        temp >>= 11;
        /* whether should frequency doubling */
        temp = (temp < 4) ? 0 : 1;

        prescaler = (RCC_Clocks.APB2_Frequency << temp) / freq - 1;
    }
    else
    {
        temp = RCC->GCFGR & RCC_GCFGR_APB1PS;
        temp >>= 8;
        /* whether should frequency doubling */
        temp = (temp < 4) ? 0 : 1;

        prescaler = (RCC_Clocks.APB1_Frequency << temp) / freq - 1;
    }

    TIMER_PrescalerConfig(timerx, prescaler, TIMER_PSC_RELOAD_NOW);
}

static void gd32_hwtimer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    TIMER_TypeDef * timer_base = timer->parent.user_data;
    TIMER_BaseInitPara TIMER_Init;

    RT_ASSERT(timer_base);

    if (state)
    {
        TIMER_InternalClockConfig(timer_base);
        TIMER_BaseStructInit(&TIMER_Init);
        TIMER_Init.TIMER_Period =  timer->info->maxcnt;
        TIMER_BaseInit(timer_base, &TIMER_Init);
        __set_timerx_freq(timer_base, timer->info->maxfreq);
    }
}

static rt_err_t gd32_hwtimer_start(struct rt_hwtimer_device *timer, \
    rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    TIMER_TypeDef * timer_base = timer->parent.user_data;

    if (mode == HWTIMER_MODE_ONESHOT)
    {
        TIMER_SinglePulseMode(timer_base, TIMER_SP_MODE_SINGLE);
    }
    else if (mode == HWTIMER_MODE_PERIOD)
    {
        TIMER_SinglePulseMode(timer_base, TIMER_SP_MODE_REPETITIVE);
    }

    TIMER_SetCounter(timer_base, 0);
    TIMER_SetAutoreload(timer_base, cnt - 1);
    TIMER_Enable(timer_base, ENABLE);

    return 0;
}

static void gd32_hwtimer_stop(struct rt_hwtimer_device *timer)
{
    TIMER_TypeDef * timer_base = timer->parent.user_data;

    TIMER_Enable(timer_base, DISABLE);
}

static rt_uint32_t gd32_hwtimer_count_get(struct rt_hwtimer_device *timer)
{
    TIMER_TypeDef * timer_base = timer->parent.user_data;
    rt_uint32_t count;

    count = TIMER_GetCounter(timer_base);

    return count;
}

static rt_err_t gd32_hwtimer_control(struct rt_hwtimer_device *timer, rt_uint32_t cmd, \
    void *args)
{
    int ret = RT_EOK;
    rt_int32_t freq;
    rt_hwtimer_mode_t mode;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        freq = *(rt_uint32_t *)args;
        __set_timerx_freq(timer->parent.user_data, freq);
        break;
    default:
        rt_kprintf("invalid cmd:%x\n", cmd);
        ret = -EINVAL;
        break;
    }

    return ret;
}

static const struct rt_hwtimer_ops g_gd32_hwtimer_ops = {
    gd32_hwtimer_init,
    gd32_hwtimer_start,
    gd32_hwtimer_stop,
    gd32_hwtimer_count_get,
    gd32_hwtimer_control,
};

static gd32_hwtimer_device g_gd32_hwtimer[] = {
#ifdef BSP_USING_HWTIMER0
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
#ifdef BSP_USING_HWTIMER1
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
#ifdef BSP_USING_HWTIMER2
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
#ifdef BSP_USING_HWTIMER3
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
#ifdef BSP_USING_HWTIMER4
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
#ifdef BSP_USING_HWTIMER5
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
#ifdef BSP_USING_HWTIMER6
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
#ifdef BSP_USING_HWTIMER7
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
#ifdef BSP_USING_HWTIMER8
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
#ifdef BSP_USING_HWTIMER9
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
#ifdef BSP_USING_HWTIMER10
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
#ifdef BSP_USING_HWTIMER11
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
#ifdef BSP_USING_HWTIMER12
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
#ifdef BSP_USING_HWTIMER13
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

#ifdef BSP_USING_HWTIMER0
void TIMER0_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM0_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM0_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER1
void TIMER1_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM1_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM1_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER2
void TIMER2_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM2_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM2_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER3
void TIMER3_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM3_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM3_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER4
void TIMER4_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM4_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM4_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER5
void TIMER5_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM5_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM5_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER6
void TIMER6_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM6_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM6_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTIMER7
void TIMER7_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&g_gd32_hwtimer[TIM7_INDEX].hwtimer_dev);
    TIMER_ClearIntBitState(g_gd32_hwtimer[TIM7_INDEX].hwtimer_dev.parent.user_data, \
        TIMER_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

static int rt_hwtimer_init(void)
{
    int ret = 0, i = 0;

    for (; i < ARRAY_SIZE(g_gd32_hwtimer); i++)
    {
        g_gd32_hwtimer[i].hwtimer_dev.ops = &g_gd32_hwtimer_ops;
        g_gd32_hwtimer[i].hwtimer_dev.info = &g_gd32_hwtimer[i].hwtimer_info;

        rcu_periph_clock_enable(g_gd32_hwtimer[i].hw_data.rcu);
        NVIC_SetPriority(g_gd32_hwtimer[i].hw_data.irqn, 0);
        NVIC_EnableIRQ(g_gd32_hwtimer[i].hw_data.irqn);
        TIMER_INTConfig(g_gd32_hwtimer[i].hw_data.reg_base, TIMER_INT_UPDATE, ENABLE);
        ret = rt_device_hwtimer_register(&g_gd32_hwtimer[i].hwtimer_dev, \
            g_gd32_hwtimer[i].dev_name, g_gd32_hwtimer[i].hw_data.reg_base);
        if (RT_EOK != ret)
        {
            rt_kprintf("failed register %s, err=%d\n", g_gd32_hwtimer[i].dev_name, \
                ret);
            break;
        }
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hwtimer_init);
#endif
