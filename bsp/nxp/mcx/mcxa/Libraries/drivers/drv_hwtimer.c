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

#ifdef BSP_USING_HWTIMER

#define LOG_TAG             "drv.hwtimer"
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

struct mcxa_hwtimer
{
    rt_hwtimer_t     time_device;
    CTIMER_Type*     tim_handle;
    enum IRQn        tim_irqn;
    char*            name;
};

static struct mcxa_hwtimer mcxa_hwtimer_obj[] =
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

static rt_err_t mcxa_ctimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;
        if(hwtimer_dev == CTIMER0) clk = CLOCK_GetCTimerClkFreq(0U);
        if(hwtimer_dev == CTIMER1) clk = CLOCK_GetCTimerClkFreq(1U);
        if(hwtimer_dev == CTIMER2) clk = CLOCK_GetCTimerClkFreq(2U);

        pre = clk / *((uint32_t *)args) - 1;

        hwtimer_dev->PR = pre;
    }
    break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t mcxa_ctimer_count_get(rt_hwtimer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CurrentTimer_Count = hwtimer_dev->TC;

    return CurrentTimer_Count;
}

static void mcxa_ctimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    CTIMER_Type *hwtimer_dev;
    ctimer_config_t cfg;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    /* Use Main clock for some of the Ctimers */
    if(hwtimer_dev == CTIMER0)  CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
    if(hwtimer_dev == CTIMER1)  CLOCK_AttachClk(kFRO_HF_to_CTIMER1);
    if(hwtimer_dev == CTIMER2)  CLOCK_AttachClk(kFRO_HF_to_CTIMER2);

    CTIMER_Init(hwtimer_dev, &cfg);

    if (state == 1)
    {
        NVIC_Configuration();
        CTIMER_GetDefaultConfig(&cfg);
        CTIMER_Init(hwtimer_dev, &cfg);
    }
}

static rt_err_t mcxa_ctimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;
    /* Match Configuration for Channel 0 */
    ctimer_match_config_t matchCfg;

    RT_ASSERT(timer != RT_NULL);

    /* Configuration*/
    matchCfg.enableCounterReset = true;
    matchCfg.enableCounterStop  = (mode == HWTIMER_MODE_ONESHOT) ? true : false;;
    matchCfg.matchValue         = cnt;
    matchCfg.outControl         = kCTIMER_Output_NoAction;
    matchCfg.outPinInitState    = false;
    matchCfg.enableInterrupt    = true;

    CTIMER_SetupMatch(hwtimer_dev, kCTIMER_Match_1, &matchCfg);

    NVIC_Configuration();

    CTIMER_StartTimer(hwtimer_dev);

    return RT_EOK;
}

static void mcxa_ctimer_stop(rt_hwtimer_t *timer)
{
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CTIMER_StopTimer(hwtimer_dev);
}

static const struct rt_hwtimer_ops mcxa_hwtimer_ops =
{
    .init  = mcxa_ctimer_init,
    .start = mcxa_ctimer_start,
    .stop  = mcxa_ctimer_stop,
    .count_get = mcxa_ctimer_count_get,
    .control = mcxa_ctimer_control,
};

static const struct rt_hwtimer_info mcxa_hwtimer_info =
{
    96000000,           /* the maximum count frequency can be set */
    6103,               /* the minimum count frequency can be set */
    0xFFFFFFFF,
    HWTIMER_CNTMODE_UP,
};

int rt_hw_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(mcxa_hwtimer_obj) / sizeof(mcxa_hwtimer_obj[0]); i++)
    {
        mcxa_hwtimer_obj[i].time_device.info = &mcxa_hwtimer_info;
        mcxa_hwtimer_obj[i].time_device.ops  = &mcxa_hwtimer_ops;
        if (rt_device_hwtimer_register(&mcxa_hwtimer_obj[i].time_device,
            mcxa_hwtimer_obj[i].name, mcxa_hwtimer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", mcxa_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", mcxa_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);

#ifdef BSP_USING_CTIMER0
void CTIMER0_IRQHandler(void)
{
    rt_interrupt_enter();
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER0);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER0, int_stat);
    rt_device_hwtimer_isr(&mcxa_hwtimer_obj[TIM0_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_HWTIMER0 */

#ifdef BSP_USING_CTIMER1
void CTIMER1_IRQHandler(void)
{
    rt_interrupt_enter();
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER1);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER1, int_stat);
    rt_device_hwtimer_isr(&mcxa_hwtimer_obj[TIM1_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_HWTIMER1 */

#ifdef BSP_USING_CTIMER2
void CTIMER2_IRQHandler(void)
{
    rt_interrupt_enter();
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER2);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER2, int_stat);
    rt_device_hwtimer_isr(&mcxa_hwtimer_obj[TIM2_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_HWTIMER2 */


#endif /* BSP_USING_HWTIMER */
