/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add APM32F4 series MCU support
 * 2022-12-26     luobeihai         add APM32F0 series MCU support
 * 2023-03-27     luobeihai         add APM32E1/S1 series MCU support
 */

#include <board.h>

#define DBG_TAG               "drv.hwtimer"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_HWTIMER

static const struct rt_hwtimer_info apm32_timer_info =
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
#ifdef BSP_USING_TMR15
    TMR15_INDEX,
#endif
#ifdef BSP_USING_TMR16
    TMR16_INDEX,
#endif
#ifdef BSP_USING_TMR17
    TMR17_INDEX,
#endif
};

static struct apm32_timer tmr_config[] =
{
#ifdef BSP_USING_TMR1
    {
        "timer1",
        TMR1,
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
        TMR1_UP_IRQn,
#elif defined(SOC_SERIES_APM32F4)
        TMR1_UP_TMR10_IRQn,
#elif defined(SOC_SERIES_APM32F0)
        TMR1_BRK_UP_TRG_COM_IRQn
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
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(APM32F030) || defined(APM32F070)
        TMR6_IRQn,
#elif defined(SOC_SERIES_APM32F4)
        TMR6_DAC_IRQn
#elif defined(SOC_SERIES_APM32F0) && !defined(APM32F030) && !defined(APM32F070)
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
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1)
        TMR8_UP_IRQn,
#elif defined(SOC_SERIES_APM32F4)
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
#if defined(SOC_SERIES_APM32F0)
        TMR14_IRQn,
#elif defined(SOC_SERIES_APM32F4)
        TMR8_TRG_COM_TMR14_IRQn,
#endif
    },
#endif
#ifdef BSP_USING_TMR15
    {
        "timer15",
        TMR15,
        TMR15_IRQn,
    },
#endif
#ifdef BSP_USING_TMR16
    {
        "timer16",
        TMR16,
        TMR16_IRQn,
    },
#endif
#ifdef BSP_USING_TMR17
    {
        "timer17",
        TMR17,
        TMR17_IRQn,
    },
#endif
};

static rt_uint32_t apm32_hwtimer_clock_get(TMR_T *tmr)
{
#if defined(SOC_SERIES_APM32F0)
    uint32_t pclk1;

    pclk1 = RCM_ReadPCLKFreq();

    return (rt_uint32_t)(pclk1 * ((RCM->CFG1_B.APB1PSC != 0) ? 2 : 1));
#endif /* SOC_SERIES_APM32F0 */

#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    uint32_t pclk1, pclk2;

    RCM_ReadPCLKFreq(&pclk1, &pclk2);

#if defined(SOC_SERIES_APM32S1)
    if (tmr == TMR1)
#else
    if (tmr == TMR1 || tmr == TMR8 || tmr == TMR9 || tmr == TMR10 || tmr == TMR11)
#endif /* SOC_SERIES_APM32S1 */
    {
        return (rt_uint32_t)(pclk2 * ((RCM->CFG_B.APB2PSC != 0) ? 2 : 1));
    }
    else
    {
        return (rt_uint32_t)(pclk1 * ((RCM->CFG_B.APB1PSC != 0) ? 2 : 1));
    }
#endif
}

static void apm32_hwtimer_enable_clock(void)
{
#ifdef BSP_USING_TMR1
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR1);
#endif
#ifdef BSP_USING_TMR2
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR2);
#endif
#ifdef BSP_USING_TMR3
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);
#endif
#ifdef BSP_USING_TMR4
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR4);
#endif
#ifdef BSP_USING_TMR5
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR5);
#endif
#ifdef BSP_USING_TMR6
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR6);
#endif
#ifdef BSP_USING_TMR7
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR7);
#endif
#ifdef BSP_USING_TMR8
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR8);
#endif
#ifdef BSP_USING_TMR9
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR9);
#endif
#ifdef BSP_USING_TMR10
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR10);
#endif
#ifdef BSP_USING_TMR11
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR11);
#endif
#ifdef BSP_USING_TMR12
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR12);
#endif
#ifdef BSP_USING_TMR13
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR13);
#endif
#ifdef BSP_USING_TMR14
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR14);
#endif
#ifdef BSP_USING_TMR15
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR15);
#endif
#ifdef BSP_USING_TMR16
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR16);
#endif
#ifdef BSP_USING_TMR17
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR17);
#endif
}

static void apm32_hwtimer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
#if defined(SOC_SERIES_APM32F0)
    TMR_TimeBase_T   base_config;
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    TMR_BaseConfig_T base_config;
#endif
    uint32_t prescaler = 0;
    struct apm32_timer *timer_config;

    RT_ASSERT(timer != RT_NULL);

    if (state)
    {
        timer_config = (struct apm32_timer *)timer->parent.user_data;

        apm32_hwtimer_enable_clock();

        prescaler = (uint32_t)(apm32_hwtimer_clock_get(timer_config->tmr) / 10000) - 1;

        base_config.period          = 10000 - 1;
#if defined(SOC_SERIES_APM32F0)
        base_config.div               = prescaler;
        base_config.clockDivision     = TMR_CKD_DIV1;
        if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            base_config.counterMode   = TMR_COUNTER_MODE_UP;
        }
        else
        {
            base_config.counterMode   = TMR_COUNTER_MODE_DOWN;
        }
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
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
#endif
        base_config.repetitionCounter = 0;
        TMR_ConfigTimeBase(timer_config->tmr, &base_config);

#if defined(SOC_SERIES_APM32F0)
        /* set the TIMx priority */
        NVIC_EnableIRQRequest(timer_config->irqn, 3);
        /* enable update request source */
        TMR_ConfigUPdateRequest(timer_config->tmr, TMR_UPDATE_SOURCE_REGULAR);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
        /* set the TIMx priority */
        NVIC_EnableIRQRequest(timer_config->irqn, 3, 0);
        /* enable update request source */
    #if defined(SOC_SERIES_APM32E1)
        TMR_ConfigUPdateRequest(timer_config->tmr, TMR_UPDATE_SOURCE_REGULAR);
    #else
        TMR_ConfigUpdateRequest(timer_config->tmr, TMR_UPDATE_SOURCE_REGULAR);
    #endif
#endif
        /* clear update flag */
        TMR_ClearStatusFlag(timer_config->tmr, TMR_FLAG_UPDATE);
        LOG_D("%s init success", timer_config->name);
    }
}

static rt_err_t apm32_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    struct apm32_timer *timer_config = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    timer_config = (struct apm32_timer *)timer->parent.user_data;

    /* set timer_config counter */
    timer_config->tmr->CNT = 0;
    /* set timer_config autoReload */
    timer_config->tmr->AUTORLD = t - 1;

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        timer_config->tmr->CTRL1_B.SPMEN = 1;
    }
    else
    {
        timer_config->tmr->CTRL1_B.SPMEN = 0;
    }

    TMR_EnableInterrupt(timer_config->tmr, TMR_INT_UPDATE);

#if defined(SOC_SERIES_APM32F0)
    if (timer_config->tmr == TMR1 || timer_config->tmr == TMR2 || timer_config->tmr == TMR3 || \
        timer_config->tmr == TMR15)
#elif defined(SOC_SERIES_APM32S1)
    if (timer_config->tmr == TMR1)
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32F4)
    if (timer_config->tmr == TMR1 || timer_config->tmr == TMR2 || timer_config->tmr == TMR3 || \
        timer_config->tmr == TMR4 || timer_config->tmr == TMR5 || timer_config->tmr == TMR8 || \
        timer_config->tmr == TMR9 || timer_config->tmr == TMR12)
#endif
    {
        if (timer_config->tmr->SMCTRL_B.SMFSEL != 0x06)
        {
            TMR_Enable(timer_config->tmr);
            result = RT_EOK;
        }
    }
    else
    {
        TMR_Enable(timer_config->tmr);
        result = RT_EOK;
    }
    return result;
}

static void apm32_hwtimer_stop(rt_hwtimer_t *timer)
{
    struct apm32_timer *timer_config = RT_NULL;
    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct apm32_timer *)timer->parent.user_data;

    TMR_DisableInterrupt(timer_config->tmr, TMR_INT_UPDATE);
    TMR_Enable(timer_config->tmr);
    timer_config->tmr->CNT = 0;
}

static rt_err_t apm32_hwtimer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
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

        val = apm32_hwtimer_clock_get(timer_config->tmr) / freq;

        /* Configures the timer prescaler */
        timer_config->tmr->PSC_B.PSC = val - 1;
        timer_config->tmr->CEG_B.UEG = 1;
        break;
    default:
        LOG_E("invalid cmd: 0x%x\n", cmd);
        result = -RT_ENOSYS;
        break;
    }
    return result;
}

static rt_uint32_t apm32_hwtimer_counter_get(rt_hwtimer_t *timer)
{
    struct apm32_timer *timer_config = RT_NULL;
    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct apm32_timer *)timer->parent.user_data;

    return timer_config->tmr->CNT;
}

static const struct rt_hwtimer_ops apm32_hwtimer_ops =
{
    .init  = apm32_hwtimer_init,
    .start = apm32_hwtimer_start,
    .stop  = apm32_hwtimer_stop,
    .count_get = apm32_hwtimer_counter_get,
    .control = apm32_hwtimer_ctrl,
};


#if defined(SOC_SERIES_APM32F0)
#ifdef BSP_USING_TMR1
void TMR1_BRK_UP_TRG_COM_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR1_INDEX].device);
    TMR_ClearIntFlag(TMR1, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
#ifdef BSP_USING_TMR1
void TMR1_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR1_INDEX].device);
    TMR_ClearIntFlag(TMR1, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif
#elif defined(SOC_SERIES_APM32F4)
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
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(APM32F030) || defined(APM32F070)
    void TMR6_IRQHandler(void)
#elif defined(SOC_SERIES_APM32F4)
    void TMR6_DAC_IRQHandler(void)
#elif defined(SOC_SERIES_APM32F0) && !defined(APM32F030) && !defined(APM32F070)
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

#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1)
#ifdef BSP_USING_TMR8
void TMR8_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR8_INDEX].device);
    TMR_ClearIntFlag(TMR8, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif
#elif defined(SOC_SERIES_APM32F4)
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
#if defined(SOC_SERIES_APM32F0)
    void TMR14_IRQHandler(void)
#elif defined(SOC_SERIES_APM32F4)
    void TMR8_TRG_COM_TMR14_IRQHandler(void)
#endif
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR14_INDEX].device);
    TMR_ClearIntFlag(TMR14, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR15
void TMR15_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR15_INDEX].device);
    TMR_ClearIntFlag(TMR15, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR16
void TMR16_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR16_INDEX].device);
    TMR_ClearIntFlag(TMR16, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR17
void TMR17_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_device_hwtimer_isr(&tmr_config[TMR17_INDEX].device);
    TMR_ClearIntFlag(TMR17, TMR_INT_UPDATE);
    rt_interrupt_leave();
}
#endif

static int rt_hw_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(tmr_config) / sizeof(tmr_config[0]); i++)
    {
        tmr_config[i].device.info = &apm32_timer_info;
        tmr_config[i].device.ops  = &apm32_hwtimer_ops;
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
