/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 * Author: oxlm
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_config.h"

#ifdef BSP_USING_TIM

#define DRV_DEBUG
#define LOG_TAG             "drv.timer"
#include <drv_log.h>

struct ns800_clock_timer
{
    rt_clock_timer_t        timer;
    void                   *instance;
    IRQn_Type               irqno;
    void (*irq_handler)(void);
    char                   *name;
    rt_clock_timer_mode_t   mode;
};


enum
{
#ifdef BSP_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_TIM2
    TIM2_INDEX,
#endif
};


#ifdef BSP_USING_TIM1
void TIM1_IRQHandler(void);
#endif
#ifdef BSP_USING_TIM2
void TIM2_IRQHandler(void);
#endif

static struct ns800_clock_timer ns800_timers[] =
{
#ifdef BSP_USING_TIM1
    {.instance = TIM1,    .irqno = TIM1_IRQn,   .irq_handler = TIM1_IRQHandler, .name = "timer1"},
#endif
#ifdef BSP_USING_TIM2
    {.instance = TIM2,    .irqno = TIM2_IRQn,   .irq_handler = TIM2_IRQHandler, .name = "timer2"},
#endif
};

#define NS800_TIMER_NUM    (sizeof(ns800_timers) / sizeof(ns800_timers[0]))

static void ns800_clock_timer_isr(void *param)
{
    rt_interrupt_enter();

    struct ns800_clock_timer *tim = (struct ns800_clock_timer *)param;

    TIM_TypeDef *htim = (TIM_TypeDef *)tim->instance;
    if (TIM_getFlags(htim, TIM_FLAG_UPDATE))
    {
        TIM_clearFlags(htim, TIM_FLAG_UPDATE);
        rt_clock_timer_isr(&tim->timer);

        if (tim->mode == CLOCK_TIMER_MODE_ONESHOT)
            TIM_disableCounter(htim);
    }

    rt_interrupt_leave();
    __DSB();
}


#ifdef BSP_USING_TIM1
void TIM1_IRQHandler(void) { ns800_clock_timer_isr(&ns800_timers[TIM1_INDEX]); }
#endif
#ifdef BSP_USING_TIM2
void TIM2_IRQHandler(void) { ns800_clock_timer_isr(&ns800_timers[TIM2_INDEX]); }
#endif

static void ns800_clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    struct ns800_clock_timer *tim = (struct ns800_clock_timer *)timer->parent.user_data;
    TIM_TypeDef *htim = (TIM_TypeDef *)tim->instance;

    if(state)
    {
        __IO uint32_t cfg =
            TIM_PWMMODE_ONEPOINT |
            TIM_CLOCKDIVISION_DIV1 |
            TIM_AUTORELOADPRELOAD_ENABLE |
            TIM_COUNTERMODE_UP |
            TIM_ONEPULSEMODE_REPETITIVE;

        TIM_configTimeBase(htim, 200-1, 100-1, cfg);
        TIM_clearFlags(htim, TIM_FLAG_UPDATE);
        TIM_enableInterruptSource(htim, TIM_IT_UPDATE);
    }
    else
    {
        TIM_disableInterruptSource(htim, TIM_IT_UPDATE);
        TIM_disableCounter(htim);
    }
}

static rt_err_t ns800_clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    struct ns800_clock_timer *tim = (struct ns800_clock_timer *)timer->parent.user_data;
    tim->mode = mode;

    TIM_TypeDef *htim = (TIM_TypeDef *)tim->instance;

    if (cnt > 0xFFFF) cnt = 0xFFFF;
    TIM_setAutoReload(htim, cnt-1);
    TIM_setCounter(htim, 0);
    TIM_enableCounter(htim);
    return RT_EOK;
}

static void ns800_clock_timer_stop(rt_clock_timer_t *timer)
{
    struct ns800_clock_timer *tim = (struct ns800_clock_timer *)timer->parent.user_data;

    TIM_disableCounter((TIM_TypeDef *)tim->instance);
}

static rt_uint32_t ns800_clock_timer_count_get(rt_clock_timer_t *timer)
{
    struct ns800_clock_timer *tim = (struct ns800_clock_timer *)timer->parent.user_data;

    return TIM_getCounter((TIM_TypeDef *)tim->instance);
}

static rt_err_t __set_timerx_freq(rt_clock_timer_t *timer, uint32_t freq)
{
    #define TIM_SRC_CLK    200000000UL
    struct ns800_clock_timer *tim = timer->parent.user_data;

    rt_uint32_t psc = (TIM_SRC_CLK / freq ) - 1;
    TIM_setPrescaler(tim->instance, psc);

    return RT_EOK;
}

static rt_err_t ns800_clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    rt_int32_t freq;

    switch (cmd)
    {
        case CLOCK_TIMER_CTRL_FREQ_SET:
            freq = *(rt_uint32_t *)args;
            __set_timerx_freq(timer, freq);
            break;
        case CLOCK_TIMER_CTRL_INFO_GET:
            *(struct rt_clock_timer_info*)args = *timer->info;
            err = RT_EOK;
            break;

        case CLOCK_TIMER_CTRL_MODE_SET:
            timer->mode = *(rt_uint32_t *)args;
            break;

        case CLOCK_TIMER_CTRL_STOP:
            ns800_clock_timer_stop(timer);
            break;
    }
    return err;
}


static const struct rt_clock_timer_info ns800_clock_timer_info[] =
{
#ifdef BSP_USING_TIM1
    {
        .maxfreq = 200000000UL,
        .minfreq = 1UL,
        .maxcnt  = 0xFFFF,
        .cntmode = CLOCK_TIMER_CNTMODE_UP,
    },
#endif
#ifdef BSP_USING_TIM2
    {
        .maxfreq = 200000000UL,
        .minfreq = 1UL,
        .maxcnt  = 0xFFFF,
        .cntmode = CLOCK_TIMER_CNTMODE_UP,
    },
#endif
};


static const struct rt_clock_timer_ops ns800_clock_timer_ops =
{
    .init       = ns800_clock_timer_init,
    .start      = ns800_clock_timer_start,
    .stop       = ns800_clock_timer_stop,
    .count_get  = ns800_clock_timer_count_get,
    .control    = ns800_clock_timer_control,
};

int rt_hw_clock_timer_init(void)
{
    rt_err_t ret = RT_EOK;

    if (NS800_TIMER_NUM == 0)
        return RT_EOK;

    uint8_t i;
    IRQn_Type last_irq = (IRQn_Type)0;

    for (i = 0; i < NS800_TIMER_NUM; i++)
    {
        ns800_timers[i].timer.info = &ns800_clock_timer_info[i];
        ns800_timers[i].timer.ops  = &ns800_clock_timer_ops;

        ret = rt_clock_timer_register(&ns800_timers[i].timer,
                               ns800_timers[i].name,
                               &ns800_timers[i]);

        if ((ret == RT_EOK) && (ns800_timers[i].irqno != last_irq))
        {
            Interrupt_register(ns800_timers[i].irqno, ns800_timers[i].irq_handler);
            Interrupt_enable(ns800_timers[i].irqno);
            last_irq = ns800_timers[i].irqno;
        }
    }

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

#endif /* BSP_USING_TIM */