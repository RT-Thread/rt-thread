/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#include "drv_timer.h"

#ifdef RT_USING_CLOCK_TIME

#if defined(BSP_USING_CLOCK_TIMER1) || defined(BSP_USING_CLOCK_TIMER2) || defined(BSP_USING_CLOCK_TIMER3) || \
    defined(BSP_USING_CLOCK_TIMER4) || defined(BSP_USING_CLOCK_TIMER5) || defined(BSP_USING_CLOCK_TIMER6) || \
    defined(BSP_USING_CLOCK_TIMER7) || defined(BSP_USING_CLOCK_TIMER8) || defined(BSP_USING_CLOCK_TIMER9)

static struct n32_clock_timer_config clock_timer_config[] =
{
#ifdef BSP_USING_CLOCK_TIMER1
    {
        "timer1",
        TIM1,
        TIM1_UP_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER2
    {
        "timer2",
        TIM2,
        TIM2_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER3
    {
        "timer3",
        TIM3,
        TIM3_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER4
    {
        "timer4",
        TIM4,
        TIM4_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER5
    {
        "timer5",
        TIM5,
        TIM5_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER6
    {
        "timer6",
        TIM6,
        TIM6_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER7
    {
        "timer7",
        TIM7,
        TIM7_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER8
    {
        "timer8",
        TIM8,
        TIM8_UP_IRQn,
    },
#endif

#ifdef BSP_USING_CLOCK_TIMER9
    {
        "timer9",
        TIM9,
        TIM9_IRQn,
    },
#endif
};

uint8_t tim1_count = 0, tim2_count = 0, tim3_count = 0, tim4_count = 0,tim5_count = 0, tim6_count = 0, tim7_count = 0, tim8_count = 0;
#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
uint8_t tim9_count = 0;
#endif

static void caculate_tim_count()
{
    uint8_t count = 0;

#ifdef BSP_USING_CLOCK_TIMER1
    tim1_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER2
    tim2_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER3
    tim3_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER4
    tim4_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER5
    tim5_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER6
    tim6_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER7
    tim7_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER8
    tim8_count = count;
    count++;
#endif

#ifdef BSP_USING_CLOCK_TIMER9
    tim9_count = count;
    count++;
#endif
}

#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

static struct n32_clock_timer clock_timer_obj[sizeof(clock_timer_config) / sizeof(clock_timer_config[0])] = {0};

static rt_err_t n32_clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct n32_clock_timer_config *config;
    RCC_ClocksType RCC_ClockFreq;
    RT_ASSERT(timer != RT_NULL);

    config = (struct n32_clock_timer_config *)timer->parent.user_data;

    RCC_GetClocksFreqValue(&RCC_ClockFreq);

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint8_t clkpre;
        uint32_t pre;
        if (config->timer_periph != TIM1 && config->timer_periph != TIM8)
        {
            clk = RCC_ClockFreq.Pclk1Freq;
            clkpre = GET_BITS(RCC->CFG, 8, 10);
        }
        else
        {
            clk = RCC_ClockFreq.Pclk2Freq;
            clkpre = GET_BITS(RCC->CFG, 11, 13);
        }
        if (clkpre >= 4)
        {
            clk = clk * 2;
        }
        pre = (clk / * ((uint32_t *)args)) - 1;
        TIM_ConfigPrescaler(config->timer_periph, pre, TIM_PSC_RELOAD_MODE_IMMEDIATE);
        config->timer_periph->EVTGEN |= TIM_EVTGEN_UDGN;
    }
    break;
    case CLOCK_TIMER_CTRL_STOP:
        TIM_Enable(config->timer_periph, DISABLE);
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t n32_clock_timer_count_get(rt_clock_timer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    struct n32_clock_timer_config *config;
    RT_ASSERT(timer != RT_NULL);

    config = (struct n32_clock_timer_config *)timer->parent.user_data;

    CurrentTimer_Count = TIM_GetCnt(config->timer_periph);

    return CurrentTimer_Count;
}

/**
 * @brief  Configures the NVIC for TIM.
 */
void TIM_NVIC_Config(IRQn_Type IRQn, uint8_t PreemptionPriority, uint8_t SubPriority,FunctionalState cmd)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel    = IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = cmd;

    if (cmd)
    {
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority        = SubPriority;
    }
    NVIC_Init(&NVIC_InitStructure);
}


static void n32_clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    struct n32_clock_timer_config *config;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    RCC_ClocksType RCC_ClockFreq;
    RT_ASSERT(timer != RT_NULL);
    config = (struct n32_clock_timer_config *)timer->parent.user_data;

    if (state == 1)
    {
        uint32_t clk;
        uint8_t clkpre;
        uint32_t pre;

        RCC_GetClocksFreqValue(&RCC_ClockFreq);
        TIM_DeInit(config->timer_periph);

        if (config->timer_periph != TIM1 && config->timer_periph != TIM8)
        {
            clk = RCC_ClockFreq.Pclk1Freq;
            clkpre = GET_BITS(RCC->CFG, 8, 10);
        }
        else
        {
            clk = RCC_ClockFreq.Pclk2Freq;
            clkpre = GET_BITS(RCC->CFG, 11, 13);
        }
        if (clkpre >= 4)
        {
            clk = clk * 2;
        }
        pre = (clk / 10000) - 1;

        /* Time Base configuration */
        TIM_TimeBaseStructure.Prescaler = pre;
        TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
        TIM_TimeBaseStructure.Period    = 10000 - 1;
        TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
        TIM_TimeBaseStructure.RepetCnt  = 0;

        if (timer->info->cntmode == CLOCK_TIMER_CNTMODE_UP)
        {
            TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
        }
        else
        {
            TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_DOWN;
        }
        TIM_InitTimeBase(config->timer_periph, &TIM_TimeBaseStructure);
        /* set the TIMx priority */
        TIM_NVIC_Config(config->irqn, 3, 0, ENABLE);
        /* clear update flag */
        TIM_ClearFlag(config->timer_periph, TIM_FLAG_UPDATE);
    }
    else
    {
        TIM_Enable(config->timer_periph, DISABLE);
        TIM_ConfigInt(config->timer_periph, TIM_INT_UPDATE, ENABLE);
        TIM_NVIC_Config(config->irqn, 3, 0, DISABLE);
    }
}

static rt_err_t n32_clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    struct n32_clock_timer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct n32_clock_timer_config *)timer->parent.user_data;

    /* set tim cnt */
    TIM_SetCnt(config->timer_periph, 0);
    /* set tim arr */
    TIM_SetAutoReload(config->timer_periph, cnt - 1);

    if (mode == CLOCK_TIMER_MODE_ONESHOT)
    {
        TIM_SelectOnePulseMode(config->timer_periph, TIM_OPMODE_SINGLE);
    }
    else
    {
        TIM_SelectOnePulseMode(config->timer_periph, TIM_OPMODE_REPET);
    }

    /* start timer */
    TIM_ConfigInt(config->timer_periph, TIM_INT_UPDATE, ENABLE);
    /* TIM counter enable */
    TIM_Enable(config->timer_periph, ENABLE);

    TIM_NVIC_Config(config->irqn, 3, 0, ENABLE);

    return RT_EOK;
}

static void n32_clock_timer_stop(rt_clock_timer_t *timer)
{
    struct n32_clock_timer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct n32_clock_timer_config *)timer->parent.user_data;

    TIM_Enable(config->timer_periph, DISABLE);

    TIM_NVIC_Config(config->irqn, 3, 0, DISABLE);
}

static const struct rt_clock_timer_ops n32_clock_timer_ops =
{
    .init = n32_clock_timer_init,
    .start = n32_clock_timer_start,
    .stop = n32_clock_timer_stop,
    .count_get = n32_clock_timer_count_get,
    .control = n32_clock_timer_control,
};

static const struct rt_clock_timer_info n32_clock_timer_info =
{
    1000000,            /* the maximum count frequency can be set */
    2000,               /* the minimum count frequency can be set */
    0xFFFF,
    CLOCK_TIMER_CNTMODE_UP,
};

/**
  * @brief  This function handles TIM interrupts requests.
  * @param  htim TIM  handle
  * @retval None
  */
void TIM_IRQHandler(TIM_Module* timer_periph)
{
    /* Capture compare 1 event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC1) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_CC1) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC1);
        }
    }
    /* Capture compare 2 event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC2) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_CC2) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC2);
        }
    }
    /* Capture compare 3 event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC3) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_CC3) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC3);
        }
    }
    /* Capture compare 4 event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC4) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_CC4) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC4);
        }
    }
    /* TIM Update event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_UPDATE) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_UPDATE) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_UPDATE);
        }
    }
    /* TIM Break input event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_BREAK) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_BREAK) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_BREAK);
        }
    }
    /* TIM Trigger detection event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_TRIG) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_TRIG) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_TRIG);
        }
    }
    /* TIM commutation event */
    if (TIM_GetFlagStatus(timer_periph, TIM_FLAG_COM) != RESET)
    {
        if (TIM_GetIntStatus(timer_periph, TIM_INT_COM) !=RESET)
        {
            TIM_ClrIntPendingBit(timer_periph, TIM_INT_COM);
        }
    }
}

#ifdef BSP_USING_CLOCK_TIMER1
void TIM1_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim1_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim1_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER2
void TIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim2_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim2_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER3
void TIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim3_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim3_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER4
void TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim4_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim4_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER5
void TIM5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim5_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim5_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER6
void TIM6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim6_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim6_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER7
void TIM7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim7_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim7_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER8
void TIM8_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim8_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim8_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CLOCK_TIMER9
void TIM9_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(clock_timer_obj[tim9_count].config->timer_periph, TIM_INT_UPDATE);
    rt_clock_timer_isr(&clock_timer_obj[tim9_count].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

int rt_clock_timer_init(void)
{
    int i = 0;
    int result = RT_EOK;

#ifdef BSP_USING_CLOCK_TIMER1
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER2
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER3
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER4
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER5
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER6
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER7
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM7, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER8
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
#endif

#ifdef BSP_USING_CLOCK_TIMER9
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM9, ENABLE);
#endif

    caculate_tim_count();
    for (i = 0; i < sizeof(clock_timer_obj) / sizeof(clock_timer_obj[0]); i++)
    {
        clock_timer_obj[i].time_device.info = &n32_clock_timer_info;
        clock_timer_obj[i].time_device.ops  = &n32_clock_timer_ops;
        clock_timer_obj[i].config = &clock_timer_config[i];
        rt_clock_timer_register(&clock_timer_obj[i].time_device, \
                                   clock_timer_obj[i].config->name, clock_timer_obj[i].config);
    }

    return result;

}
INIT_DEVICE_EXPORT(rt_clock_timer_init);

#endif /* defined(BSP_USING_CLOCK_TIMERx) */
#endif /* RT_USING_CLOCK_TIME */
