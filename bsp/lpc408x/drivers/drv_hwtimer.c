/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2015-09-02     heyuanjie87      the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "lpc_timer.h"
#include "lpc_clkpwr.h"
#include "drv_hwtimer.h"

#ifdef RT_USING_HWTIMER

static void NVIC_Configuration(void)
{
    NVIC_EnableIRQ(TIMER0_IRQn);
}

static void timer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    LPC_TIM_TypeDef *tim;
    TIM_TIMERCFG_Type cfg;

    tim = (LPC_TIM_TypeDef *)timer->parent.user_data;

    TIM_DeInit(tim);

    if (state == 1)
    {
        NVIC_Configuration();

        cfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
        cfg.PrescaleValue = 0xFFFF;
        TIM_Init(tim, TIM_TIMER_MODE, &cfg);
    }
}

static rt_err_t timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    LPC_TIM_TypeDef *tim;
    TIM_MATCHCFG_Type match;

    tim = (LPC_TIM_TypeDef *)timer->parent.user_data;

    match.MatchChannel = 0;
    match.IntOnMatch = ENABLE;
    match.ResetOnMatch = ENABLE;
    match.StopOnMatch = (opmode == HWTIMER_MODE_ONESHOT) ? ENABLE : DISABLE;
    match.ExtMatchOutputType = 0;
    match.MatchValue = t;

    TIM_ConfigMatch(tim, &match);
    TIM_Cmd(tim, ENABLE);

    return RT_EOK;
}

static void timer_stop(rt_hwtimer_t *timer)
{
    LPC_TIM_TypeDef *tim;

    tim = (LPC_TIM_TypeDef *)timer->parent.user_data;

    TIM_Cmd(tim, DISABLE);
}

static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    LPC_TIM_TypeDef *tim;
    rt_err_t err = RT_EOK;

    tim = (LPC_TIM_TypeDef *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;

        clk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);
        pre = clk / *((uint32_t *)arg) - 1;
        tim->PR = pre;
    }
    break;
    default:
    {
        err = -RT_ENOSYS;
    }
    break;
    }

    return err;
}

static rt_uint32_t timer_counter_get(rt_hwtimer_t *timer)
{
    LPC_TIM_TypeDef *tim;

    tim = (LPC_TIM_TypeDef *)timer->parent.user_data;

    return tim->TC;
}

static const struct rt_hwtimer_info _info =
{
    1000000,           /* the maximum count frequency can be set */
    2000,              /* the minimum count frequency can be set */
    0xFFFFFF,          /* the maximum counter value */
    HWTIMER_CNTMODE_UP,/* Increment or Decreasing count mode */
};

static const struct rt_hwtimer_ops _ops =
{
    timer_init,
    timer_start,
    timer_stop,
    timer_counter_get,
    timer_ctrl,
};

static rt_hwtimer_t _timer0;

int rt_hw_hwtimer_init(void)
{
    _timer0.info = &_info;
    _timer0.ops  = &_ops;

    rt_device_hwtimer_register(&_timer0, "timer0", LPC_TIM0);

    return 0;
}

void TIMER0_IRQHandler(void)
{
    if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT) != RESET)
    {
        TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
        rt_device_hwtimer_isr(&_timer0);
    }
}

INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif  /* RT_USING_HWTIMER */
