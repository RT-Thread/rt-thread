/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add apm32F4 serie MCU support
 */

#include <board.h>

#define LOG_TAG               "drv.hwtimer"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_HWTIMER

static const struct rt_hwtimer_info _info =
{
    .maxfreq = 1000000,
    .minfreq = 2000,
    .maxcnt  = 0xFFFF,
    .cntmode = HWTIMER_CNTMODE_UP,
};

/* apm32 config class */
struct apm32_timer
{
    char         *name;
    TMR_T        *tmr;
    IRQn_Type    irqn;
    rt_hwtimer_t device;
};

enum
{
#ifdef BSP_USING_TMR1
    TMR1_INDEX,
#endif
#ifdef BSP_USING_TMR2
    TMR2_INDEX,
#endif
#ifdef BSP_USING_TMR3
    TMR3_INDEX,
#endif
#ifdef BSP_USING_TMR4
    TMR4_INDEX,
#endif
#ifdef BSP_USING_TMR5
    TMR5_INDEX,
#endif
#ifdef BSP_USING_TMR6
    TMR6_INDEX,
#endif
#ifdef BSP_USING_TMR7
    TMR7_INDEX,
#endif
#ifdef BSP_USING_TMR8
    TMR8_INDEX,
#endif
#ifdef BSP_USING_TMR9
    TMR9_INDEX,
#endif
#ifdef BSP_USING_TMR10
    TMR10_INDEX,
#endif
#ifdef BSP_USING_TMR11
    TMR11_INDEX,
#endif
#ifdef BSP_USING_TMR12
    TMR12_INDEX,
#endif
#ifdef BSP_USING_TMR13
    TMR13_INDEX,
#endif
#ifdef BSP_USING_TMR14
    TMR14_INDEX,
#endif
};

static struct apm32_timer tmr_config[] =
{
#ifdef BSP_USING_TMR1
    {
        "timer1",
        TMR1,
#ifdef APM32F10X_HD
        TMR1_UP_IRQn,
#elif APM32F40X
        TMR1_UP_TMR10_IRQn,
#endif
    },
#endif
#ifdef BSP_USING_TMR2
    {
        "timer2",
        TMR2,
        TMR2_IRQn,
    },
#endif
#ifdef BSP_USING_TMR3
    {
        "timer3",
        TMR3,
        TMR3_IRQn,
    },
#endif
#ifdef BSP_USING_TMR4
    {
        "timer4",
        TMR4,
        TMR4_IRQn,
    },
#endif
#ifdef BSP_USING_TMR5
    {
        "timer5",
        TMR5,
        TMR5_IRQn,
    },
#endif
#ifdef BSP_USING_TMR6
    {
        "timer6",
        TMR6,
#ifdef APM32F10X_HD
        TMR6_IRQn,
#elif APM32F40X
        TMR6_DAC_IRQn
#endif
    },
#endif
#ifdef BSP_USING_TMR7
    {
        "timer7",
        TMR7,
        TMR7_IRQn,
    },
#endif
#ifdef BSP_USING_TMR8
    {
        "timer8",
        TMR8,
#ifdef APM32F10X_HD
        TMR8_UP_IRQn,
#elif APM32F40X
        TMR8_UP_TMR13_IRQn,
#endif
    },
#endif
#ifdef BSP_USING_TMR9
    {
        "timer9",
        TMR9,
        TMR1_BRK_TMR9_IRQn,
    },
#endif
#ifdef BSP_USING_TMR10
    {
        "timer10",
        TMR10,
        TMR1_UP_TMR10_IRQn,
    },
#endif
#ifdef BSP_USING_TMR11
    {
        "timer11",
        TMR11,
        TMR1_TRG_COM_TMR11_IRQn,
    },
#endif
#ifdef BSP_USING_TMR12
    {
        "timer12",
        TMR12,
        TMR8_BRK_TMR12_IRQn,
    },
#endif
#ifdef BSP_USING_TMR13
    {
        "timer13",
        TMR13,
        TMR8_UP_TMR13_IRQn,
    },
#endif
#ifdef BSP_USING_TMR14
    {
        "timer14",
        TMR14,
        TMR8_TRG_COM_TMR14_IRQn,
    },
#endif
};

static rt_uint32_t _hwtimer_clock_get(TMR_T *tmr)
{
    uint32_t pclk1, pclk2;

    RCM_ReadPCLKFreq(&pclk1, &pclk2);

    if (tmr == TMR1 || tmr == TMR8 || tmr == TMR9 || tmr == TMR10 || tmr == TMR11)
    {
        return (rt_uint32_t)(pclk2 * ((RCM->CFG_B.APB2PSC != RCM_APB_DIV_1) ? 2 : 1));
    }
    else
    {
        return (rt_uint32_t)(pclk1 * ((RCM->CFG_B.APB1PSC != RCM_APB_DIV_1) ? 2 : 1));
    }
}

static void _hwtimer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    TMR_BaseConfig_T base_config;
    uint32_t prescaler = 0;
    struct apm32_timer *timer_config;

    RT_ASSERT(timer != RT_NULL);

    if (state)
    {
        timer_config = (struct apm32_timer *)timer->parent.user_data;
        if (timer_config->tmr == TMR2)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR2);
        }
        else if (timer_config->tmr == TMR3)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);
        }
        else if (timer_config->tmr == TMR4)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR4);
        }
        else if (timer_config->tmr == TMR5)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR5);
        }
        else if (timer_config->tmr == TMR6)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR6);
        }
        else if (timer_config->tmr == TMR7)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR7);
        }
#ifdef APM32F10X_HD
        else if (timer_config->tmr == TMR1)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
        }
        else if (timer_config->tmr == TMR8)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR8);
        }
#endif
#ifdef APM32F40X
        else if (timer_config->tmr == TMR1)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
        }
        else if (timer_config->tmr == TMR8)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR8);
        }
        else if (timer_config->tmr == TMR9)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR9);
        }
        else if (timer_config->tmr == TMR10)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR10);
        }
        else if (timer_config->tmr == TMR11)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR11);
        }
        else if (timer_config->tmr == TMR12)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR12);
        }
        else if (timer_config->tmr == TMR13)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR13);
        }
        else if (timer_config->tmr == TMR14)
        {
            RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR14);
        }
#endif
        prescaler = (uint32_t)(_hwtimer_clock_get(timer_config->tmr) / 10000) - 1;

        base_config.period          = 10000 - 1;
        base_config.division        = prescaler;
        base_config.clockDivision   = TMR_CLOCK_DIV_1;
        if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            base_config.countMode   = TMR_COUNTER_MODE_UP;
        }
        else
        {
            base_config.countMode   = TMR_COUNTER_MODE_DOWN;
        }
        base_config.repetitionCounter = 0;
        TMR_ConfigTimeBase(timer_config->tmr, &base_config);

        /* set the TIMx priority */
        NVIC_EnableIRQRequest(timer_config->irqn, 3, 0);

        /* clear update flag */
        TMR_ClearStatusFlag(timer_config->tmr, TMR_FLAG_UPDATE);
        /* enable update request source */
        TMR_ConfigUpdateRequest(timer_config->tmr, TMR_UPDATE_SOURCE_REGULAR);
        LOG_D("%s init success", timer_config->name);
    }
}

static rt_err_t _hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    struct apm32_timer *timer_config = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    timer_config = (struct apm32_timer *)timer->parent.user_data;

    /* set timer_config counter */
    TMR_ConfigCounter(timer_config->tmr, 0);
    /* set timer_config autoReload */
    TMR_ConfigAutoreload(timer_config->tmr, t - 1);

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        TMR_ConfigSinglePulseMode(timer_config->tmr, TMR_SPM_SINGLE);
    }
    else
    {
        TMR_ConfigSinglePulseMode(timer_config->tmr, TMR_SPM_REPETITIVE);
    }

    TMR_EnableInterrupt(timer_config->tmr, TMR_INT_UPDATE);

    if (timer_config->tmr == TMR1 || timer_config->tmr == TMR8 || timer_config->tmr == TMR2 || \
            timer_config->tmr == TMR3 || timer_config->tmr == TMR4 || timer_config->tmr == TMR5 || \
            timer_config->tmr == TMR9 || timer_config->tmr == TMR12)
    {
        if (timer_config->tmr->SMCTRL_B.SMFSEL != TMR_SLAVE_MODE_TRIGGER)
        {
            TMR_Enable(timer_config->tmr);
            result = -RT_EOK;
        }
    }
    else
    {
        TMR_Enable(timer_config->tmr);
        result = -RT_EOK;
    }
    return result;
}

static void _hwtimer_stop(rt_hwtimer_t *timer)
{
    struct apm32_timer *timer_config = RT_NULL;
    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct apm32_timer *)timer->parent.user_data;

    TMR_DisableInterrupt(timer_config->tmr, TMR_INT_UPDATE);
    TMR_Enable(timer_config->tmr);
    TMR_ConfigCounter(timer_config->tmr, 0);
}

static rt_err_t _hwtimer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    struct apm32_timer *timer_config = RT_NULL;
    rt_err_t result = RT_EOK;
    rt_uint32_t freq;
    rt_uint16_t val;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    timer_config = (struct apm32_timer *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        /* set timer frequence */
        freq = *((rt_uint32_t *)arg);

        val = _hwtimer_clock_get(timer_config->tmr) / freq;

        TMR_ConfigPrescaler(timer_config->tmr, val - 1, TMR_PSC_RELOAD_IMMEDIATE);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }
    return result;
}

static rt_uint32_t _hwtimer_counter_get(rt_hwtimer_t *timer)
{
    struct apm32_timer *timer_config = RT_NULL;
    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct apm32_timer *)timer->parent.user_data;

    return timer_config->tmr->CNT;
}

static const struct rt_hwtimer_ops _hwtimer_ops =
{
    .init  = _hwtimer_init,
    .start = _hwtimer_start,
    .stop  = _hwtimer_stop,
    .count_get = _hwtimer_counter_get,
    .control = _hwtimer_ctrl,
};

#ifdef APM32F10X_HD
#ifdef BSP_USING_TMR1
void TMR1_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR1_INDEX].device);
    TMR_ClearIntFlag(TMR1, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif
#elif APM32F40X
#if (defined(BSP_USING_TMR1) || defined(BSP_USING_TMR10))
void TMR1_UP_TMR10_IRQHandler(void)
{
    rt_interrupt_enter();
    if (TMR_ReadIntFlag(TMR1, TMR_INT_UPDATE))
    {
        rt_device_hwtimer_isr(&tmr_config[TMR1_INDEX].device);
        TMR_ClearIntFlag(TMR1, TMR_INT_UPDATE);
    }
    if (TMR_ReadIntFlag(TMR10, TMR_INT_UPDATE))
    {
        rt_device_hwtimer_isr(&tmr_config[TMR10_INDEX].device);
        TMR_ClearIntFlag(TMR10, TMR_INT_UPDATE);
    }
    rt_interrupt_leave();
}
#endif
#endif

#ifdef BSP_USING_TMR2
void TMR2_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR2_INDEX].device);
    TMR_ClearIntFlag(TMR2, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR3
void TMR3_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR3_INDEX].device);
    TMR_ClearIntFlag(TMR3, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR4
void TMR4_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR4_INDEX].device);
    TMR_ClearIntFlag(TMR4, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR5
void TMR5_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR5_INDEX].device);
    TMR_ClearIntFlag(TMR5, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR6
#ifdef APM32F10X_HD
    void TMR6_IRQHandler(void)
#elif APM32F40X
    void TMR6_DAC_IRQHandler(void)
#endif
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR6_INDEX].device);
    TMR_ClearIntFlag(TMR6, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR7
void TMR7_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR7_INDEX].device);
    TMR_ClearIntFlag(TMR7, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef APM32F10X_HD
#ifdef BSP_USING_TMR8
void TMR8_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR8_INDEX].device);
    TMR_ClearIntFlag(TMR8, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif
#elif APM32F40X
#if (defined(BSP_USING_TMR8) || defined(BSP_USING_TMR13))
void TMR8_UP_TMR13_IRQHandler(void)
{
    rt_interrupt_enter();
    if (TMR_ReadIntFlag(TMR8, TMR_INT_UPDATE))
    {
        rt_device_hwtimer_isr(&tmr_config[TMR8_INDEX].device);
        TMR_ClearIntFlag(TMR8, TMR_INT_UPDATE);
    }
    if (TMR_ReadIntFlag(TMR13, TMR_INT_UPDATE))
    {
        rt_device_hwtimer_isr(&tmr_config[TMR13_INDEX].device);
        TMR_ClearIntFlag(TMR13, TMR_INT_UPDATE);
    }
    rt_interrupt_leave();
}
#endif
#endif

#ifdef BSP_USING_TMR9
void TMR1_BRK_TMR9_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR9_INDEX].device);
    TMR_ClearIntFlag(TMR9, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR11
void TMR1_TRG_COM_TMR11_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR11_INDEX].device);
    TMR_ClearIntFlag(TMR11, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR12
void TMR8_BRK_TMR12_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR12_INDEX].device);
    TMR_ClearIntFlag(TMR12, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR14
void TMR8_TRG_COM_TMR14_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR14_INDEX].device);
    TMR_ClearIntFlag(TMR14, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

static int rt_hw_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(tmr_config) / sizeof(tmr_config[0]); i++)
    {
        tmr_config[i].device.info = &_info;
        tmr_config[i].device.ops  = &_hwtimer_ops;
        if (rt_device_hwtimer_register(&tmr_config[i].device, tmr_config[i].name, &tmr_config[i]) == RT_EOK)
        {
            LOG_D("%s register success", tmr_config[i].name);
        }
        else
        {
            LOG_E("%s register failed", tmr_config[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* RT_USING_HWTIMER */
