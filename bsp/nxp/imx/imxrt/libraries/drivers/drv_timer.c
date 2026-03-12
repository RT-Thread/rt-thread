/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
* Change Logs:
* Date           Author       Notes
* 2018-04-17     WangBing     the first version.
* 2019-04-22     tyustli      add imxrt series support
*
*/
#include <rtthread.h>

#ifdef BSP_USING_CLOCK_TIMER

#define LOG_TAG             "drv.clock_timer"
#include <drv_log.h>

#include <rtdevice.h>
#include "drv_timer.h"
#include "fsl_gpt.h"

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

/* Select IPG Clock as PERCLK_CLK clock source */
#define EXAMPLE_GPT_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for PERCLK_CLK clock source */
#define EXAMPLE_GPT_CLOCK_DIVIDER_SELECT (5U)
/* Get source clock for GPT driver (GPT prescaler = 6) */
#ifdef SOC_IMXRT1170_SERIES
#undef EXAMPLE_GPT_CLOCK_DIVIDER_SELECT
#define EXAMPLE_GPT_CLOCK_DIVIDER_SELECT (2U)
// 1170 use this root directly, we have already divide this clk, can read it directly
#define EXAMPLE_GPT_CLK_FREQ (CLOCK_GetRootClockFreq(kCLOCK_Root_Gpt1))
#else
#define EXAMPLE_GPT_CLK_FREQ (CLOCK_GetFreq(kCLOCK_IpgClk) / (EXAMPLE_GPT_CLOCK_DIVIDER_SELECT + 1U))
#endif

static void NVIC_Configuration(void)
{
#ifdef BSP_USING_CLOCK_TIMER1
    EnableIRQ(GPT1_IRQn);
#endif

#ifdef BSP_USING_CLOCK_TIMER2
    EnableIRQ(GPT2_IRQn);
#endif
}

static rt_err_t imxrt_clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    GPT_Type *clock_timer_dev;
    clock_timer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;
        clk = EXAMPLE_GPT_CLK_FREQ;
        pre = clk / *((uint32_t *)args) - 1;
        GPT_SetClockDivider(clock_timer_dev, pre);
    }
    break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t imxrt_clock_timer_count_get(rt_clock_timer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    GPT_Type *clock_timer_dev;
    clock_timer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CurrentTimer_Count = GPT_GetCurrentTimerCount(clock_timer_dev);

    return CurrentTimer_Count;
}

static void imxrt_clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    GPT_Type *clock_timer_dev;
    gpt_config_t gptConfig;
    clock_timer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    if (state == 1)
    {
    #ifdef SOC_IMXRT1170_SERIES
    #ifdef BSP_USING_CLOCK_TIMER1
        /*Clock setting for GPT*/
        CLOCK_SetRootClockMux(kCLOCK_Root_Gpt1, EXAMPLE_GPT_CLOCK_SOURCE_SELECT);
        CLOCK_SetRootClockDiv(kCLOCK_Root_Gpt1, EXAMPLE_GPT_CLOCK_DIVIDER_SELECT);
    #endif
    #ifdef BSP_USING_CLOCK_TIMER2
        /*Clock setting for GPT*/
        CLOCK_SetRootClockMux(kCLOCK_Root_Gpt2, EXAMPLE_GPT_CLOCK_SOURCE_SELECT);
        CLOCK_SetRootClockDiv(kCLOCK_Root_Gpt2, EXAMPLE_GPT_CLOCK_DIVIDER_SELECT);
    #endif
    #else
        /*Clock setting for GPT*/
        CLOCK_SetMux(kCLOCK_PerclkMux, EXAMPLE_GPT_CLOCK_SOURCE_SELECT);
        CLOCK_SetDiv(kCLOCK_PerclkDiv, EXAMPLE_GPT_CLOCK_DIVIDER_SELECT);
    #endif

        /* Initialize GPT module by default config */
        GPT_GetDefaultConfig(&gptConfig);
        GPT_Init(clock_timer_dev, &gptConfig);
    }
}

static rt_err_t imxrt_clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    GPT_Type *clock_timer_dev;
    clock_timer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    clock_timer_dev->CR |= (mode != CLOCK_TIMER_MODE_PERIOD) ? GPT_CR_FRR_MASK : 0U;

    GPT_SetOutputCompareValue(clock_timer_dev, kGPT_OutputCompare_Channel1, cnt);

    GPT_EnableInterrupts(clock_timer_dev, kGPT_OutputCompare1InterruptEnable);

    NVIC_Configuration();

    GPT_StartTimer(clock_timer_dev);

    return RT_EOK;
}

static void imxrt_clock_timer_stop(rt_clock_timer_t *timer)
{
    GPT_Type *clock_timer_dev;
    clock_timer_dev = (GPT_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    GPT_StopTimer(clock_timer_dev);
}

static const struct rt_clock_timer_ops imxrt_clock_timer_ops =
{
    .init = imxrt_clock_timer_init,
    .start = imxrt_clock_timer_start,
    .stop = imxrt_clock_timer_stop,
    .count_get = imxrt_clock_timer_count_get,
    .control = imxrt_clock_timer_control,
};

static const struct rt_clock_timer_info imxrt_clock_timer_info =
{
    25000000,           /* the maximum count frequency can be set */
    6103,               /* the minimum count frequency can be set */
    0xFFFFFFFF,
    CLOCK_TIMER_CNTMODE_UP,
};

#ifdef BSP_USING_CLOCK_TIMER1
static rt_clock_timer_t GPT_timer1;
#endif /*BSP_USING_CLOCK_TIMER1*/

#ifdef BSP_USING_CLOCK_TIMER2
static rt_clock_timer_t GPT_timer2;
#endif

int rt_hw_clock_timer_init(void)
{
    int ret = RT_EOK;

#ifdef BSP_USING_CLOCK_TIMER1
    GPT_timer1.info = &imxrt_clock_timer_info;
    GPT_timer1.ops  = &imxrt_clock_timer_ops;
    ret = rt_clock_timer_register(&GPT_timer1, "gpt1", GPT1);

    if (ret != RT_EOK)
    {
        LOG_E("gpt1 register failed\n");
    }
#endif

#ifdef BSP_USING_CLOCK_TIMER2
    GPT_timer2.info = &imxrt_clock_timer_info;
    GPT_timer2.ops = &imxrt_clock_timer_ops;
    ret = rt_clock_timer_register(&GPT_timer2, "gpt2", GPT2);

    if (ret != RT_EOK)
    {
        LOG_E("gpt1 register failed\n");
    }
#endif

    return ret;
}

#ifdef BSP_USING_CLOCK_TIMER1

void GPT1_IRQHandler(void)
{
    if (GPT_GetStatusFlags(GPT1, kGPT_OutputCompare1Flag) != 0)
    {
        GPT_ClearStatusFlags(GPT1, kGPT_OutputCompare1Flag);
        rt_clock_timer_isr(&GPT_timer1);
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
    __DSB();
#endif
}

#endif /*BSP_USING_CLOCK_TIMER1*/

#ifdef BSP_USING_CLOCK_TIMER2

void GPT2_IRQHandler(void)
{
    if (GPT_GetStatusFlags(GPT2, kGPT_OutputCompare1Flag) != 0)
    {
        GPT_ClearStatusFlags(GPT2, kGPT_OutputCompare1Flag);
        rt_clock_timer_isr(&GPT_timer2);
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
    __DSB();
#endif
}
#endif /*BSP_USING_CLOCK_TIMER2*/

INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

#endif /* BSP_USING_CLOCK_TIMER */
