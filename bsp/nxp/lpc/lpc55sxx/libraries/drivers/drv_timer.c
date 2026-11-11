/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-17     WangBing     the first version.
 * 2019-04-22     tyustli      add imxrt series support
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 *
*/
#include <rtthread.h>

#ifdef BSP_USING_CLOCK_TIMER

#define LOG_TAG             "drv.clock_timer"
#include <drv_log.h>

#include <rtdevice.h>
#include "drv_timer.h"
#include "fsl_ctimer.h"

enum
{
#ifdef BSP_USING_CTIMER0
    TIM1_INDEX,
#endif
#ifdef BSP_USING_CTIMER3
    TIM2_INDEX,
#endif
#ifdef BSP_USING_CTIMER4
    TIM3_INDEX,
#endif
};

struct lpc_clock_timer
{
    rt_clock_timer_t     time_device;
    CTIMER_Type*     tim_handle;
    enum IRQn        tim_irqn;
    char*            name;
};

static struct lpc_clock_timer lpc_clock_timer_obj[] =
{
#ifdef BSP_USING_CTIMER0
    TIM1_CONFIG,
#endif

#ifdef BSP_USING_CTIMER3
    TIM3_CONFIG,
#endif

#ifdef BSP_USING_CTIMER4
    TIM4_CONFIG,
#endif
};

static void NVIC_Configuration(void)
{
#ifdef BSP_USING_CTIMER0
    EnableIRQ(CTIMER0_IRQn);
#endif

#ifdef BSP_USING_CTIMER3
    EnableIRQ(CTIMER3_IRQn);
#endif

#ifdef BSP_USING_CTIMER4
    EnableIRQ(CTIMER4_IRQn);
#endif
}

static rt_err_t lpc_ctimer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
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
        if(clock_timer_dev == CTIMER3) clk = CLOCK_GetCTimerClkFreq(3U);
        if(clock_timer_dev == CTIMER4) clk = CLOCK_GetCTimerClkFreq(4U);

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

static rt_uint32_t lpc_ctimer_count_get(rt_clock_timer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    CTIMER_Type *clock_timer_dev;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CurrentTimer_Count = clock_timer_dev->TC;

    return CurrentTimer_Count;
}

static void lpc_ctimer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    CTIMER_Type *clock_timer_dev;
    ctimer_config_t cfg;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    /* Use Main clock for some of the Ctimers */
    if(clock_timer_dev == CTIMER0) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER0);
    if(clock_timer_dev == CTIMER3) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER3);
    if(clock_timer_dev == CTIMER4) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER4);

    CTIMER_Deinit(clock_timer_dev);

    if (state == 1)
    {
        NVIC_Configuration();
        CTIMER_GetDefaultConfig(&cfg);
        CTIMER_Init(clock_timer_dev, &cfg);
    }
}

static rt_err_t lpc_ctimer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
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

static void lpc_ctimer_stop(rt_clock_timer_t *timer)
{
    CTIMER_Type *clock_timer_dev;
    clock_timer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CTIMER_StopTimer(clock_timer_dev);
}

static const struct rt_clock_timer_ops lpc_clock_timer_ops =
{
    .init  = lpc_ctimer_init,
    .start = lpc_ctimer_start,
    .stop  = lpc_ctimer_stop,
    .count_get = lpc_ctimer_count_get,
    .control = lpc_ctimer_control,
};

static const struct rt_clock_timer_info lpc_clock_timer_info =
{
    25000000,           /* the maximum count frequency can be set */
    6103,               /* the minimum count frequency can be set */
    0xFFFFFFFF,
    CLOCK_TIMER_CNTMODE_UP,
};

int rt_hw_clock_timer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(lpc_clock_timer_obj) / sizeof(lpc_clock_timer_obj[0]); i++)
    {
        lpc_clock_timer_obj[i].time_device.info = &lpc_clock_timer_info;
        lpc_clock_timer_obj[i].time_device.ops  = &lpc_clock_timer_ops;
        if (rt_clock_timer_register(&lpc_clock_timer_obj[i].time_device,
            lpc_clock_timer_obj[i].name, lpc_clock_timer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", lpc_clock_timer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", lpc_clock_timer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

#ifdef BSP_USING_CTIMER0
void CTIMER0_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER0);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER0, int_stat);
    rt_clock_timer_isr(&lpc_clock_timer_obj[TIM1_INDEX].time_device);

}
#endif /* BSP_USING_CLOCK_TIMER0 */

#ifdef BSP_USING_CTIMER3
void CTIMER3_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER3);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER3, int_stat);
    rt_clock_timer_isr(&lpc_clock_timer_obj[TIM2_INDEX].time_device);

}
#endif /* BSP_USING_CLOCK_TIMER3 */

#ifdef BSP_USING_CTIMER4
void CTIMER4_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER4);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER4, int_stat);
    rt_clock_timer_isr(&lpc_clock_timer_obj[TIM3_INDEX].time_device);

}
#endif /* BSP_USING_CLOCK_TIMER4 */


#endif /* BSP_USING_CLOCK_TIMER */
