/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author           Notes
 * 2015-09-02     heyuanjie87      the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_hwtimer.h"

#ifdef RT_USING_HWTIMER

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the TIM5 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void timer_init(rt_hwtimer_t *timer)
{
    TIM_TypeDef *tim;

    tim = (TIM_TypeDef *)timer->parent.user_data;

    TIM_DeInit(tim);
    NVIC_Configuration();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_CounterModeConfig(tim, TIM_CounterMode_Up);
}

static void timer_deinit(rt_hwtimer_t *timer)
{
    TIM_TypeDef *tim;

    tim = (TIM_TypeDef *)timer->parent.user_data;
    TIM_DeInit(tim);
}

static void timer_start(rt_hwtimer_t *timer, rt_hwtimer_mode_t opmode)
{
    TIM_TypeDef *tim;
    uint16_t m;

    tim = (TIM_TypeDef *)timer->parent.user_data;
    m = (opmode == HWTIMER_MODE_ONESHOT)? TIM_OPMode_Single : TIM_OPMode_Repetitive;
    TIM_SelectOnePulseMode(tim, m);
    TIM_Cmd(tim, ENABLE);
}

static void timer_stop(rt_hwtimer_t *timer)
{
    TIM_TypeDef *tim;

    tim = (TIM_TypeDef *)timer->parent.user_data;
    TIM_Cmd(tim, DISABLE);
}

static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    TIM_TypeDef *tim;
    rt_err_t err = RT_EOK;

    tim = (TIM_TypeDef *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        RCC_ClocksTypeDef clk;
        uint16_t val;
        rt_uint32_t freq;

        RCC_GetClocksFreq(&clk);

        freq = *((rt_uint32_t*)arg);
        clk.PCLK1_Frequency *= 2;
        val = clk.PCLK1_Frequency/freq;
        
		TIM_ITConfig(tim, TIM_IT_Update, DISABLE);
        TIM_PrescalerConfig(tim, val - 1, TIM_PSCReloadMode_Immediate);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM_ITConfig(tim, TIM_IT_Update, ENABLE);
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
    TIM_TypeDef *tim;

    tim = (TIM_TypeDef *)timer->parent.user_data;

    return TIM_GetCounter(tim);
}

static rt_err_t timer_timeout_set(rt_hwtimer_t *timer, rt_uint32_t t)
{
    TIM_TypeDef *tim;

    tim = (TIM_TypeDef *)timer->parent.user_data;
    TIM_SetAutoreload(tim, t);

    return RT_EOK;
}

static const struct rt_hwtimer_info _info =
{
    1000000,           /* 可设置的最大计数时钟 */
    2000,              /* 可设置的最小计数时钟 */
    0xFFFF,            /* 最大超时值 */
    HWTIMER_CNTMODE_UP,/* 递增计数方式 */
};

static const struct rt_hwtimer_ops _ops =
{
    timer_init,
    timer_deinit,
    timer_start,
    timer_stop,
    timer_timeout_set,
    timer_counter_get,
    timer_ctrl,
};

static rt_hwtimer_t _timer0;

int stm32_hwtimer_init(void)
{
    _timer0.info = &_info;
    _timer0.ops  = &_ops;

    rt_device_hwtimer_register(&_timer0, "timer0", TIM2);

    return 0;
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        rt_device_hwtimer_isr(&_timer0);
    }
}

INIT_BOARD_EXPORT(stm32_hwtimer_init);
#endif
