/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-26     hywing       the first version.
 *
*/
#include <rtthread.h>

#ifdef BSP_USING_CLOCK_TIMER

#define LOG_TAG             "drv.clock_timer"
#include <drv_log.h>
#include <rtdevice.h>
#include "fsl_ctimer.h"

enum
{
#ifdef BSP_USING_CTIMER0
    TIM0_INDEX,
#endif
#ifdef BSP_USING_CTIMER1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_CTIMER2
    TIM2_INDEX,
#endif
};

#ifdef BSP_USING_CTIMER0
#define TIM0_CONFIG                                         \
    {                                                       \
       .tim_handle              = CTIMER0,                     \
       .tim_irqn                = CTIMER0_IRQn,                \
       .name                    = "timer0",                 \
    }
#endif /* TIM0_CONFIG */

#ifdef BSP_USING_CTIMER1
#define TIM1_CONFIG                                         \
    {                                                       \
       .tim_handle              = CTIMER1,                     \
       .tim_irqn                = CTIMER1_IRQn,                \
       .name                    = "timer1",                 \
    }
#endif /* TIM1_CONFIG */

#ifdef BSP_USING_CTIMER2
#define TIM2_CONFIG                                         \
    {                                                       \
       .tim_handle              = CTIMER2,                     \
       .tim_irqn                = CTIMER2_IRQn,                \
       .name                    = "timer2",                 \
    }
#endif /* TIM2_CONFIG */

struct mcxa_clock_timer
{
    rt_clock_timer_t     time_device;
    CTIMER_Type*     tim_handle;
    enum IRQn        tim_irqn;
    char*            name;
};

static struct mcxa_clock_timer mcxa_clock_timer_obj[] =
{
#ifdef BSP_USING_CTIMER0
    TIM0_CONFIG,
#endif

#ifdef BSP_USING_CTIMER1
    TIM1_CONFIG,
#endif

#ifdef BSP_USING_CTIMER2
    TIM2_CONFIG,
#endif
};

static void NVIC_Configuration(void)
{
#ifdef BSP_USING_CTIMER0
    EnableIRQ(CTIMER0_IRQn);
#endif

#ifdef BSP_USING_CTIMER1
    EnableIRQ(CTIMER1_IRQn);
#endif

#ifdef BSP_USING_CTIMER2
    EnableIRQ(CTIMER2_IRQn);
#endif
}

static rt_err_t mcxa_ctimer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    CTIMER_Type *clock_timer_dev;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;
        if(clock_timer_dev == CTIMER0) clk = CLOCK_GetCTimerClkFreq(0U);
        if(clock_timer_dev == CTIMER1) clk = CLOCK_GetCTimerClkFreq(1U);
        if(clock_timer_dev == CTIMER2) clk = CLOCK_GetCTimerClkFreq(2U);

        pre = clk / *((uint32_t *)args) - 1;

        clock_timer_dev->PR = pre;
    }
    break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t mcxa_ctimer_count_get(rt_clock_timer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    CTIMER_Type *clock_timer_dev;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CurrentTimer_Count = clock_timer_dev->TC;

    return CurrentTimer_Count;
}

static void mcxa_ctimer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    CTIMER_Type *clock_timer_dev;
    ctimer_config_t cfg;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    /* Use Main clock for some of the Ctimers */
    if(clock_timer_dev == CTIMER0)  CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
    if(clock_timer_dev == CTIMER1)  CLOCK_AttachClk(kFRO_HF_to_CTIMER1);
    if(clock_timer_dev == CTIMER2)  CLOCK_AttachClk(kFRO_HF_to_CTIMER2);

    CTIMER_Init(clock_timer_dev, &cfg);

    if (state == 1)
    {
        NVIC_Configuration();
        CTIMER_GetDefaultConfig(&cfg);
        CTIMER_Init(clock_timer_dev, &cfg);
    }
}

static rt_err_t mcxa_ctimer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    CTIMER_Type *clock_timer_dev;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;
    /* Match Configuration for Channel 0 */
    ctimer_match_config_t matchCfg;

    RT_ASSERT(timer != RT_NULL);

    /* Configuration*/
    matchCfg.enableCounterReset = true;
    matchCfg.enableCounterStop  = (mode == CLOCK_TIMER_MODE_ONESHOT) ? true : false;;
    matchCfg.matchValue         = cnt;
    matchCfg.outControl         = kCTIMER_Output_NoAction;
    matchCfg.outPinInitState    = false;
    matchCfg.enableInterrupt    = true;

    CTIMER_SetupMatch(clock_timer_dev, kCTIMER_Match_1, &matchCfg);

    NVIC_Configuration();

    CTIMER_StartTimer(clock_timer_dev);

    return RT_EOK;
}

static void mcxa_ctimer_stop(rt_clock_timer_t *timer)
{
    CTIMER_Type *clock_timer_dev;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CTIMER_StopTimer(clock_timer_dev);
}

static const struct rt_clock_timer_ops mcxa_clock_timer_ops =
{
    .init  = mcxa_ctimer_init,
    .start = mcxa_ctimer_start,
    .stop  = mcxa_ctimer_stop,
    .count_get = mcxa_ctimer_count_get,
    .control = mcxa_ctimer_control,
};

static const struct rt_clock_timer_info mcxa_clock_timer_info =
{
    96000000,           /* the maximum count frequency can be set */
    6103,               /* the minimum count frequency can be set */
    0xFFFFFFFF,
    CLOCK_TIMER_CNTMODE_UP,
};

int rt_hw_clock_timer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(mcxa_clock_timer_obj) / sizeof(mcxa_clock_timer_obj[0]); i++)
    {
        mcxa_clock_timer_obj[i].time_device.info = &mcxa_clock_timer_info;
        mcxa_clock_timer_obj[i].time_device.ops  = &mcxa_clock_timer_ops;
        if (rt_clock_timer_register(&mcxa_clock_timer_obj[i].time_device,
            mcxa_clock_timer_obj[i].name, mcxa_clock_timer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", mcxa_clock_timer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", mcxa_clock_timer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

#ifdef BSP_USING_CTIMER0
void CTIMER0_IRQHandler(void)
{
    rt_interrupt_enter();
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER0);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER0, int_stat);
    rt_clock_timer_isr(&mcxa_clock_timer_obj[TIM0_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CLOCK_TIMER0 */

#ifdef BSP_USING_CTIMER1
void CTIMER1_IRQHandler(void)
{
    rt_interrupt_enter();
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER1);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER1, int_stat);
    rt_clock_timer_isr(&mcxa_clock_timer_obj[TIM1_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CLOCK_TIMER1 */

#ifdef BSP_USING_CTIMER2
void CTIMER2_IRQHandler(void)
{
    rt_interrupt_enter();
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER2);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER2, int_stat);
    rt_clock_timer_isr(&mcxa_clock_timer_obj[TIM2_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CLOCK_TIMER2 */


#endif /* BSP_USING_CLOCK_TIMER */
