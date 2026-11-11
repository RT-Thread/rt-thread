/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
* Change Logs:
* Date           Author       Notes
* 2024-02-21     Yilin Sun    Initial revision.
*/

#include "drv_timer.h"

#ifdef BSP_USING_CLOCK_TIMER

#include "fsl_mrt.h"

typedef struct
{
    rt_clock_timer_t timer_device;
    mrt_chnl_t channel;
    char *name;
} mcx_clock_timer_obj_t;

static inline rt_err_t mcx_clock_timer_mode_set(mcx_clock_timer_obj_t *handle, rt_clock_timer_mode_t mode)
{
    mrt_timer_mode_t mrt_mode;
    switch (mode)
    {
    case CLOCK_TIMER_MODE_ONESHOT:
        mrt_mode = kMRT_OneShotMode;
        break;

    case CLOCK_TIMER_MODE_PERIOD:
        mrt_mode = kMRT_RepeatMode;
        break;

    default:
        return -RT_EINVAL;
    }

    MRT_SetupChannelMode(MRT0, handle->channel, mrt_mode);

    return RT_EOK;
}

static void mcx_clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    mrt_config_t mrt_config;
    MRT_GetDefaultConfig(&mrt_config);

    MRT_Init(MRT0, &mrt_config);
}

static rt_err_t mcx_clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    rt_err_t ret = RT_EOK;

    mcx_clock_timer_obj_t *handle = timer->parent.user_data;

    MRT_StopTimer(MRT0, handle->channel);

    ret = mcx_clock_timer_mode_set(handle, mode);
    if (ret != RT_EOK)
    {
        return ret;
    }

    MRT_StartTimer(MRT0, handle->channel, cnt);
    MRT_EnableInterrupts(MRT0, handle->channel, kMRT_TimerInterruptEnable);

    return ret;
}

static void mcx_clock_timer_stop(rt_clock_timer_t *timer)
{
    mcx_clock_timer_obj_t *handle = timer->parent.user_data;
    MRT_StopTimer(MRT0, handle->channel);
    MRT_DisableInterrupts(MRT0, handle->channel, kMRT_TimerInterruptEnable);
}

static rt_uint32_t mcx_clock_timer_count_get(rt_clock_timer_t *timer)
{
    mcx_clock_timer_obj_t *handle = timer->parent.user_data;

    return MRT_GetCurrentTimerCount(MRT0, handle->channel);
}

static rt_err_t mcx_clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t ret = RT_EOK;

    mcx_clock_timer_obj_t *handle = timer->parent.user_data;
    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_STOP:
        mcx_clock_timer_stop(timer);
        break;

    case CLOCK_TIMER_CTRL_MODE_SET:
        ret = mcx_clock_timer_mode_set(handle, *(rt_clock_timer_mode_t *)args);
        if (ret != RT_EOK)
        {
            return ret;
        }
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static mcx_clock_timer_obj_t mcx_clock_timer_list[] =
{
    { .name = "timer0", .channel = kMRT_Channel_0, },
    { .name = "timer1", .channel = kMRT_Channel_1, },
    { .name = "timer2", .channel = kMRT_Channel_2, },
    { .name = "timer3", .channel = kMRT_Channel_3, },
};

static struct rt_clock_timer_info mcx_clock_timer_info =
{
    .cntmode = CLOCK_TIMER_CNTMODE_DW,
    .maxcnt = 0x00FFFFFF, /* 24bit counter */
    .minfreq = 150000000,
    .maxfreq = 150000000,
};

static const struct rt_clock_timer_ops mcx_clock_timer_ops =
{
    .init = mcx_clock_timer_init,
    .control = mcx_clock_timer_control,
    .start = mcx_clock_timer_start,
    .stop = mcx_clock_timer_stop,
    .count_get = mcx_clock_timer_count_get,
};

int rt_hw_clock_timer_init(void)
{
    /* MRT frequency is fixed to AHB clock */
    uint32_t mrt_freq = CLOCK_GetFreq(kCLOCK_BusClk);

    mcx_clock_timer_info.minfreq = mrt_freq;
    mcx_clock_timer_info.maxfreq = mrt_freq;

    for (uint8_t i = 0; i < ARRAY_SIZE(mcx_clock_timer_list); i++)
    {
        mcx_clock_timer_list[i].timer_device.info = &mcx_clock_timer_info;
        mcx_clock_timer_list[i].timer_device.ops = &mcx_clock_timer_ops;

        rt_err_t ret = rt_clock_timer_register(&mcx_clock_timer_list[i].timer_device, mcx_clock_timer_list[i].name, &mcx_clock_timer_list[i]);
        if (ret != RT_EOK)
        {
            return ret;
        }
    }

    EnableIRQ(MRT0_IRQn);

    return RT_EOK;
}

void MRT0_IRQHandler(void)
{
    /* Get channel interrupt flags */
    uint32_t mrt_flag = MRT0->IRQ_FLAG;

    /* Clear interrupt flags (W1C). */
    MRT0->IRQ_FLAG = mrt_flag;

    for (uint8_t i = 0; i < 4; i++)
    {
        if (mrt_flag & (1U << i))
        {
            rt_clock_timer_isr(&mcx_clock_timer_list[i].timer_device);
        }
    }
}

INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

#endif /* BSP_USING_CLOCK_TIMER */
