/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-03     Alex Yang    Add MCXC162 CTIMER0/1 support
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "fsl_clock.h"
#include "fsl_ctimer.h"

#if defined(BSP_USING_CLOCK_TIMER) && \
    (defined(BSP_USING_CTIMER0) || defined(BSP_USING_CTIMER1))

#define MCXC162_CTIMER_SOURCE_FREQ 72000000U

struct mcxc162_hwtimer
{
    rt_clock_timer_t timer;
    CTIMER_Type *base;
    rt_uint8_t instance;
    const char *name;
};

enum
{
#ifdef BSP_USING_CTIMER0
    MCXC162_CTIMER0_INDEX,
#endif
#ifdef BSP_USING_CTIMER1
    MCXC162_CTIMER1_INDEX,
#endif
};

static struct mcxc162_hwtimer mcxc162_hwtimers[] = {
#ifdef BSP_USING_CTIMER0
    {
        .base = CTIMER0,
        .instance = 0U,
        .name = "timer0",
    },
#endif
#ifdef BSP_USING_CTIMER1
    {
        .base = CTIMER1,
        .instance = 1U,
        .name = "timer1",
    },
#endif
};

static struct mcxc162_hwtimer *mcxc162_hwtimer_from_device(rt_clock_timer_t *timer)
{
    return rt_container_of(timer, struct mcxc162_hwtimer, timer);
}

static void mcxc162_hwtimer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    struct mcxc162_hwtimer *device = mcxc162_hwtimer_from_device(timer);
    ctimer_config_t config;

    if (!state)
    {
        DisableIRQ(device->instance == 0U ? CTIMER0_IRQn : CTIMER1_IRQn);
        CTIMER_Deinit(device->base);
        return;
    }

    if (device->instance == 0U)
    {
        CLOCK_SetClockDiv(kCLOCK_DivCTIMER0, 1U);
        CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
    }
    else
    {
        CLOCK_SetClockDiv(kCLOCK_DivCTIMER1, 1U);
        CLOCK_AttachClk(kFRO_HF_to_CTIMER1);
    }

    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(device->base, &config);
}

static rt_err_t mcxc162_hwtimer_start(rt_clock_timer_t *timer, rt_uint32_t count,
                                      rt_clock_timer_mode_t mode)
{
    struct mcxc162_hwtimer *device = mcxc162_hwtimer_from_device(timer);
    ctimer_match_config_t match = {
        .matchValue = count,
        .enableCounterReset = true,
        .enableCounterStop = mode == CLOCK_TIMER_MODE_ONESHOT,
        .outControl = kCTIMER_Output_NoAction,
        .outPinInitState = false,
        .enableInterrupt = true,
    };
    IRQn_Type irq = device->instance == 0U ? CTIMER0_IRQn : CTIMER1_IRQn;

    DisableIRQ(irq);
    CTIMER_StopTimer(device->base);
    CTIMER_Reset(device->base);
    CTIMER_ClearStatusFlags(device->base, kCTIMER_Match0Flag);
    CTIMER_SetupMatch(device->base, kCTIMER_Match_0, &match);
    NVIC_ClearPendingIRQ(irq);
    EnableIRQ(irq);
    CTIMER_StartTimer(device->base);

    return RT_EOK;
}

static void mcxc162_hwtimer_stop(rt_clock_timer_t *timer)
{
    struct mcxc162_hwtimer *device = mcxc162_hwtimer_from_device(timer);
    IRQn_Type irq = device->instance == 0U ? CTIMER0_IRQn : CTIMER1_IRQn;

    DisableIRQ(irq);
    CTIMER_StopTimer(device->base);
    CTIMER_ClearStatusFlags(device->base, kCTIMER_Match0Flag);
    NVIC_ClearPendingIRQ(irq);
}

static rt_uint32_t mcxc162_hwtimer_count_get(rt_clock_timer_t *timer)
{
    return mcxc162_hwtimer_from_device(timer)->base->TC;
}

static rt_err_t mcxc162_hwtimer_control(rt_clock_timer_t *timer, rt_uint32_t command,
                                        void *argument)
{
    struct mcxc162_hwtimer *device = mcxc162_hwtimer_from_device(timer);
    rt_uint32_t *frequency = (rt_uint32_t *)argument;
    uint32_t source;
    uint64_t divider;

    if (command != CLOCK_TIMER_CTRL_FREQ_SET)
    {
        return -RT_ENOSYS;
    }

    source = CLOCK_GetCTimerClkFreq(device->instance);
    divider = ((uint64_t)source + (*frequency / 2U)) / *frequency;
    if ((divider == 0U) || (divider > 0x100000000ULL))
    {
        return -RT_EINVAL;
    }

    CTIMER_SetPrescale(device->base, (uint32_t)(divider - 1U));
    *frequency = source / (uint32_t)divider;

    return RT_EOK;
}

static const struct rt_clock_timer_ops mcxc162_hwtimer_ops = {
    .init = mcxc162_hwtimer_init,
    .start = mcxc162_hwtimer_start,
    .stop = mcxc162_hwtimer_stop,
    .count_get = mcxc162_hwtimer_count_get,
    .control = mcxc162_hwtimer_control,
};

static const struct rt_clock_timer_info mcxc162_hwtimer_info = {
    .maxfreq = MCXC162_CTIMER_SOURCE_FREQ,
    .minfreq = 1,
    .maxcnt = 0xFFFFFFFFU,
    .cntmode = CLOCK_TIMER_CNTMODE_UP,
};

int rt_hw_hwtimer_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t index;

    for (index = 0; index < sizeof(mcxc162_hwtimers) / sizeof(mcxc162_hwtimers[0]); index++)
    {
        mcxc162_hwtimers[index].timer.info = &mcxc162_hwtimer_info;
        mcxc162_hwtimers[index].timer.ops = &mcxc162_hwtimer_ops;
        if (rt_clock_timer_register(&mcxc162_hwtimers[index].timer,
                                    mcxc162_hwtimers[index].name,
                                    mcxc162_hwtimers[index].base) != RT_EOK)
        {
            result = -RT_ERROR;
        }
    }

    if (result == RT_EOK)
    {
        result = rt_device_open(&mcxc162_hwtimers[0].timer.parent,
                                RT_DEVICE_OFLAG_RDWR);
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);

#ifdef BSP_USING_CTIMER0
void CTIMER0_IRQHandler(void)
{
    rt_interrupt_enter();

    if ((CTIMER_GetStatusFlags(CTIMER0) & kCTIMER_Match0Flag) != 0U)
    {
        CTIMER_ClearStatusFlags(CTIMER0, kCTIMER_Match0Flag);
        rt_clock_timer_isr(&mcxc162_hwtimers[MCXC162_CTIMER0_INDEX].timer);
    }

    rt_interrupt_leave();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#ifdef BSP_USING_CTIMER1
void CTIMER1_IRQHandler(void)
{
    rt_interrupt_enter();

    if ((CTIMER_GetStatusFlags(CTIMER1) & kCTIMER_Match0Flag) != 0U)
    {
        CTIMER_ClearStatusFlags(CTIMER1, kCTIMER_Match0Flag);
        rt_clock_timer_isr(&mcxc162_hwtimers[MCXC162_CTIMER1_INDEX].timer);
    }

    rt_interrupt_leave();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#endif /* BSP_USING_CLOCK_TIMER */
