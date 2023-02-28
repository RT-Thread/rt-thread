/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-10     MXH          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_HWTIMER
#define DBG_TAG               "TIM"
#define DBG_LVL               DBG_LOG
#include <rtdbg.h>

#include "drv_hwtimer.h"
#include "board.h"

#ifdef RT_USING_HWTIMER

enum
{
#ifdef BSP_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_TIM2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_TIM3
    TIM3_INDEX,
#endif
#ifdef BSP_USING_TIM4
    TIM4_INDEX,
#endif
#ifdef BSP_USING_TIM5
    TIM5_INDEX,
#endif
#ifdef BSP_USING_TIM6
    TIM6_INDEX,
#endif
#ifdef BSP_USING_TIM7
    TIM7_INDEX,
#endif
#ifdef BSP_USING_TIM8
    TIM8_INDEX,
#endif
#ifdef BSP_USING_TIM9
    TIM9_INDEX,
#endif
#ifdef BSP_USING_TIM10
    TIM10_INDEX,
#endif
};

static struct ch32_hwtimer ch32_hwtimer_obj[] =
{
#ifdef BSP_USING_TIM1
    TIM1_CONFIG,
#endif

#ifdef BSP_USING_TIM2
    TIM2_CONFIG,
#endif

#ifdef BSP_USING_TIM3
    TIM3_CONFIG,
#endif

#ifdef BSP_USING_TIM4
    TIM4_CONFIG,
#endif

#ifdef BSP_USING_TIM5
    TIM5_CONFIG,
#endif

#ifdef BSP_USING_TIM6
    TIM6_CONFIG,
#endif

#ifdef BSP_USING_TIM7
    TIM7_CONFIG,
#endif

#ifdef BSP_USING_TIM8
    TIM8_CONFIG,
#endif

#ifdef BSP_USING_TIM9
    TIM9_CONFIG,
#endif

#ifdef BSP_USING_TIM10
    TIM10_CONFIG,
#endif
};

/* APBx timer clocks frequency doubler state related to APB1CLKDivider value */
void ch32_get_pclk_doubler(rt_uint32_t *pclk1_doubler, rt_uint32_t *pclk2_doubler)
{
    RT_ASSERT(pclk1_doubler != RT_NULL);
    RT_ASSERT(pclk2_doubler != RT_NULL);

    *pclk1_doubler = 1;
    *pclk2_doubler = 1;

    if((RCC->CFGR0 & RCC_PPRE1) == RCC_PPRE1_DIV1)
    {
        *pclk1_doubler = 1;
    }
    else
    {
        *pclk1_doubler = 2;
    }

    if((RCC->CFGR0 & RCC_PPRE2) == RCC_PPRE2_DIV1)
    {
        *pclk2_doubler = 1;
    }
    else
    {
        *pclk2_doubler = 2;
    }
}

static void ch32_hwtimer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    RT_ASSERT(timer != RT_NULL);
    TIM_HandleTypeDef *tim = RT_NULL;
    RCC_ClocksTypeDef RCC_ClockStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    struct ch32_hwtimer *tim_device = RT_NULL;
    rt_uint32_t prescaler_value = 0;
    rt_uint32_t pclk1_doubler, pclk2_doubler;

    RCC_GetClocksFreq(&RCC_ClockStruct);
    ch32_get_pclk_doubler(&pclk1_doubler, &pclk2_doubler);

    if(state)
    {
        tim = (TIM_HandleTypeDef *)timer->parent.user_data;
        tim_device = (struct ch32_hwtimer *)timer;

#if defined (SOC_RISCV_SERIES_CH32V2)
        if(tim->instance == TIM1)
#elif defined(SOC_RISCV_SERIES_CH32V3)
        if(tim->instance == TIM1 || tim->instance == TIM8 ||
                tim->instance == TIM9 || tim->instance == TIM10)
#else
#error " unsupported CH32 series! "
        if(RT_NULL)
#endif
        {
            RCC_APB2PeriphClockCmd(tim->rcc, ENABLE);
            prescaler_value = (RCC_ClockStruct.PCLK2_Frequency * pclk2_doubler / 10000) - 1;
        }
        else
        {
            RCC_APB1PeriphClockCmd(tim->rcc, ENABLE);
            prescaler_value = (RCC_ClockStruct.PCLK1_Frequency * pclk1_doubler / 10000) - 1;
        }
        tim->init.TIM_Prescaler = prescaler_value;
        tim->init.TIM_ClockDivision = TIM_CKD_DIV1;
        tim->init.TIM_Period = 10000 - 1;
        tim->init.TIM_RepetitionCounter = 0;

        if(timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            tim->init.TIM_CounterMode = TIM_CounterMode_Up;
        }
        else
        {
            tim->init.TIM_CounterMode   = TIM_CounterMode_Down;
        }
#if defined (SOC_RISCV_SERIES_CH32V3)
        /* TIM6 and TIM7 only support counter up mode */
        if(tim->instance == TIM6 || tim->instance == TIM7)
        {
            tim->init.TIM_CounterMode = TIM_CounterMode_Up;
        }
#endif
        TIM_TimeBaseInit(tim->instance, &tim->init);

        NVIC_InitStruct.NVIC_IRQChannel = tim_device->irqn;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);

        TIM_ClearITPendingBit(tim->instance, TIM_IT_Update);
        TIM_ITConfig(tim->instance, TIM_IT_Update, ENABLE);
    }
}

static rt_err_t ch32_hwtimer_start(struct rt_hwtimer_device *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    RT_ASSERT(timer != RT_NULL);
    TIM_HandleTypeDef *tim = RT_NULL;
    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* set tim cnt */
    tim->instance->CNT = 0;
    /* set tim arr */
    tim->instance->ATRLR = cnt - 1;
    tim->init.TIM_Period = cnt - 1;

    if (mode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        tim->instance->CTLR1 &= (rt_uint16_t) ~((rt_uint16_t)TIM_OPM);
        tim->instance->CTLR1 |= TIM_OPMode_Single;
    }
    else
    {
        tim->instance->CTLR1 &= (rt_uint16_t) ~((rt_uint16_t)TIM_OPM);
        tim->instance->CTLR1 |= TIM_OPMode_Repetitive;
    }

    /* start timer */
    TIM_Cmd(tim->instance, ENABLE);

    return RT_EOK;
}

static void ch32_hwtimer_stop(struct rt_hwtimer_device *timer)
{
    RT_ASSERT(timer != RT_NULL);
    TIM_HandleTypeDef *tim = RT_NULL;

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* stop timer */
    TIM_Cmd(tim->instance, DISABLE);

    /* set tim cnt */
    tim->instance->CNT = 0;
}

static rt_uint32_t ch32_hwtimer_count_get(struct rt_hwtimer_device *timer)
{
    RT_ASSERT(timer != RT_NULL);
    TIM_HandleTypeDef *tim = RT_NULL;
    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    return tim->instance->CNT;
}

static rt_err_t ch32_hwtimer_control(struct rt_hwtimer_device *timer, rt_uint32_t cmd, void *args)
{
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(args != RT_NULL);

    TIM_HandleTypeDef *tim = RT_NULL;
    rt_err_t result = RT_EOK;
    rt_uint32_t pclk1_doubler, pclk2_doubler;

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;
        rt_uint16_t val;
        RCC_ClocksTypeDef RCC_ClockStruct;

        /* set timer frequence */
        freq = *((rt_uint32_t *)args);

        ch32_get_pclk_doubler(&pclk1_doubler, &pclk2_doubler);
        RCC_GetClocksFreq(&RCC_ClockStruct);

#if defined (SOC_RISCV_SERIES_CH32V2)
        if(tim->instance == TIM1)
#elif defined(SOC_RISCV_SERIES_CH32V3)
        if(tim->instance == TIM1 || tim->instance == TIM8 ||
                tim->instance == TIM9 || tim->instance == TIM10)
#else
#error " unsupported CH32 series! "
        if(RT_NULL)
#endif
        {
            val = RCC_ClockStruct.PCLK2_Frequency * pclk2_doubler / freq;
        }
        else
        {
            val = RCC_ClockStruct.PCLK1_Frequency * pclk1_doubler / freq;
        }

        /* Update frequency value */
        TIM_PrescalerConfig(tim->instance, val - 1, TIM_PSCReloadMode_Immediate);

        result = RT_EOK;
        break;
    }

    case HWTIMER_CTRL_MODE_SET:
    {
        if (*(rt_hwtimer_mode_t *)args == HWTIMER_MODE_ONESHOT)
        {
            /* set timer to single mode */
            tim->instance->CTLR1 &= (rt_uint16_t) ~((rt_uint16_t)TIM_OPM);
            tim->instance->CTLR1 |= TIM_OPMode_Single;
        }
        else
        {
            tim->instance->CTLR1 &= (rt_uint16_t) ~((rt_uint16_t)TIM_OPM);
            tim->instance->CTLR1 |= TIM_OPMode_Repetitive;
        }
        break;
    }

    case HWTIMER_CTRL_INFO_GET:
    {
        *(rt_hwtimer_mode_t *)args = tim->instance->CNT;
        break;
    }

    case HWTIMER_CTRL_STOP:
    {
        ch32_hwtimer_stop(timer);
        break;
    }

    default:
    {
        result = -RT_EINVAL;
        break;
    }
    }

    return result;
}

static const struct rt_hwtimer_info ch32_hwtimer_info = TIM_DEV_INFO_CONFIG;
static const struct rt_hwtimer_ops ch32_hwtimer_ops =
{
    ch32_hwtimer_init,
    ch32_hwtimer_start,
    ch32_hwtimer_stop,
    ch32_hwtimer_count_get,
    ch32_hwtimer_control
};

static void ch32_hwtimer_isr(struct rt_hwtimer_device *device)
{
    RT_ASSERT(device != RT_NULL);
    struct ch32_hwtimer *hwtimer = RT_NULL;
    hwtimer = rt_container_of(device, struct ch32_hwtimer, device);

    if(TIM_GetITStatus(hwtimer->handle.instance, TIM_IT_Update) != RESET)
    {
        rt_device_hwtimer_isr(device);
        TIM_ClearITPendingBit(hwtimer->handle.instance, TIM_IT_Update);
    }
}

#ifdef BSP_USING_TIM1
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM1_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM1 */

#ifdef BSP_USING_TIM2
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM2_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM2 */

#ifdef BSP_USING_TIM3
void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM3_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM3_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM3 */

#ifdef BSP_USING_TIM4
void TIM4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM4_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM4_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM4 */

#ifdef BSP_USING_TIM5
void TIM5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM5_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM5_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM5 */

#ifdef BSP_USING_TIM6
void TIM6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM6_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM6_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM6 */

#ifdef BSP_USING_TIM7
void TIM7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM7_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM7_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM7 */

#ifdef BSP_USING_TIM8
void TIM8_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM8_UP_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM8_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM8 */

#ifdef BSP_USING_TIM9
void TIM9_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM9_UP_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM9_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM9 */

#ifdef BSP_USING_TIM10
void TIM10_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM10_UP_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    ch32_hwtimer_isr(&(ch32_hwtimer_obj[TIM10_INDEX].device));
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* BSP_USING_TIM10 */

static int rt_hw_timer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(ch32_hwtimer_obj) / sizeof(ch32_hwtimer_obj[0]); i++)
    {
        ch32_hwtimer_obj[i].device.info = &ch32_hwtimer_info;
        ch32_hwtimer_obj[i].device.ops  = &ch32_hwtimer_ops;
        result = rt_device_hwtimer_register(&ch32_hwtimer_obj[i].device,
                    ch32_hwtimer_obj[i].name, (void *)&ch32_hwtimer_obj[i].handle);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

#endif /* RT_USING_HWTIMER */
#endif /* BSP_USING_HWTIMER */
