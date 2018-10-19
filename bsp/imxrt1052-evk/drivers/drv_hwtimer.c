/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
* Change Logs:
* Date           Author       Notes
* 2018-04-17     WangBing     the first version.
*/

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_hwtimer.h"

#include "fsl_common.h"
#include "fsl_gpt.h"

#ifdef RT_USING_HWTIMER

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

/* Select IPG Clock as PERCLK_CLK clock source */
#define EXAMPLE_GPT_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for PERCLK_CLK clock source */
#define EXAMPLE_GPT_CLOCK_DIVIDER_SELECT (5U)
/* Get source clock for GPT driver (GPT prescaler = 6) */
#define EXAMPLE_GPT_CLK_FREQ (CLOCK_GetFreq(kCLOCK_IpgClk) / (EXAMPLE_GPT_CLOCK_DIVIDER_SELECT + 1U))

static void NVIC_Configuration(void)
{
    EnableIRQ(GPT1_IRQn);
}

static rt_err_t rt1052_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    GPT_Type *hwtimer_dev;
    hwtimer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;
        clk = EXAMPLE_GPT_CLK_FREQ;
        pre = clk / *((uint32_t *)args) - 1;
        GPT_SetClockDivider(hwtimer_dev, pre);
    }
    break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t rt1052_hwtimer_count_get(rt_hwtimer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    GPT_Type *hwtimer_dev;
    hwtimer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CurrentTimer_Count = GPT_GetCurrentTimerCount(hwtimer_dev);

    return CurrentTimer_Count;
}

static void rt1052_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    GPT_Type *hwtimer_dev;
    gpt_config_t gptConfig;
    hwtimer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    GPT_Deinit(hwtimer_dev);

    if (state == 1)
    {
        /*Clock setting for GPT*/
        CLOCK_SetMux(kCLOCK_PerclkMux, EXAMPLE_GPT_CLOCK_SOURCE_SELECT);
        CLOCK_SetDiv(kCLOCK_PerclkDiv, EXAMPLE_GPT_CLOCK_DIVIDER_SELECT);

        /* Initialize GPT module by default config */
        GPT_GetDefaultConfig(&gptConfig);
        GPT_Init(hwtimer_dev, &gptConfig);
    }
}

static rt_err_t rt1052_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    GPT_Type *hwtimer_dev;
    hwtimer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    hwtimer_dev->CR |= (mode == HWTIMER_MODE_PERIOD) ? GPT_CR_FRR_MASK : 0U;

    GPT_SetOutputCompareValue(hwtimer_dev, kGPT_OutputCompare_Channel1, cnt);

    GPT_EnableInterrupts(hwtimer_dev, kGPT_OutputCompare1InterruptEnable);

    NVIC_Configuration();

    GPT_StartTimer(hwtimer_dev);

    return RT_EOK;
}

static void rt1052_hwtimer_stop(rt_hwtimer_t *timer)
{
    GPT_Type *hwtimer_dev;
    hwtimer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    GPT_StopTimer(hwtimer_dev);
}

static const struct rt_hwtimer_ops rt1052_hwtimer_ops =
{
    rt1052_hwtimer_init,
    rt1052_hwtimer_start,
    rt1052_hwtimer_stop,
    rt1052_hwtimer_count_get,
    rt1052_hwtimer_control,
};

static const struct rt_hwtimer_info rt1052_hwtimer_info =
{
    25000000,           /* the maximum count frequency can be set */
    6103,               /* the minimum count frequency can be set */
    0xFFFFFFFF,
    HWTIMER_CNTMODE_UP,
};

static rt_hwtimer_t GPT_timer1;

int rt1052_hw_hwtimer_init(void)
{
    int ret = RT_EOK;

    GPT_timer1.info = &rt1052_hwtimer_info;
    GPT_timer1.ops  = &rt1052_hwtimer_ops;

    rt_device_hwtimer_register(&GPT_timer1, "_timer", GPT1);

    return ret;
}

void GPT1_IRQHandler(void)
{
    if (GPT_GetStatusFlags(GPT1, kGPT_OutputCompare1Flag) != 0)
    {
        GPT_ClearStatusFlags(GPT1, kGPT_OutputCompare1Flag);
        rt_device_hwtimer_isr(&GPT_timer1);
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
    __DSB();
#endif
}

INIT_DEVICE_EXPORT(rt1052_hw_hwtimer_init);

#endif /*RT_USING_HWTIMER*/
