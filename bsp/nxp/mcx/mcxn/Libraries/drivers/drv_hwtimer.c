/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
* Change Logs:
* Date           Author       Notes
* 2024-02-21     Yilin Sun    Initial revision.
*/

#include "drv_hwtimer.h"

#ifdef BSP_USING_HWTIMER

#include "fsl_mrt.h"

typedef struct
{
    rt_hwtimer_t timer_device;
    mrt_chnl_t channel;
    char *name;
} mcx_hwtimer_obj_t;

static inline rt_err_t mcx_hwtimer_mode_set(mcx_hwtimer_obj_t *handle, rt_hwtimer_mode_t mode)
{
    mrt_timer_mode_t mrt_mode;
    switch (mode)
    {
    case HWTIMER_MODE_ONESHOT:
        mrt_mode = kMRT_OneShotMode;
        break;

    case HWTIMER_MODE_PERIOD:
        mrt_mode = kMRT_RepeatMode;
        break;

    default:
        return -RT_EINVAL;
    }

    MRT_SetupChannelMode(MRT0, handle->channel, mrt_mode);

    return RT_EOK;
}

static void mcx_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    mrt_config_t mrt_config;
    MRT_GetDefaultConfig(&mrt_config);

    MRT_Init(MRT0, &mrt_config);
}

static rt_err_t mcx_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    rt_err_t ret = RT_EOK;

    mcx_hwtimer_obj_t *handle = timer->parent.user_data;

    MRT_StopTimer(MRT0, handle->channel);

    ret = mcx_hwtimer_mode_set(handle, mode);
    if (ret != RT_EOK)
    {
        return ret;
    }

    MRT_StartTimer(MRT0, handle->channel, cnt);
    MRT_EnableInterrupts(MRT0, handle->channel, kMRT_TimerInterruptEnable);

    return ret;
}

static void mcx_hwtimer_stop(rt_hwtimer_t *timer)
{
    mcx_hwtimer_obj_t *handle = timer->parent.user_data;
    MRT_StopTimer(MRT0, handle->channel);
    MRT_DisableInterrupts(MRT0, handle->channel, kMRT_TimerInterruptEnable);
}

static rt_uint32_t mcx_hwtimer_count_get(rt_hwtimer_t *timer)
{
    mcx_hwtimer_obj_t *handle = timer->parent.user_data;

    return MRT_GetCurrentTimerCount(MRT0, handle->channel);
}

static rt_err_t mcx_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t ret = RT_EOK;

    mcx_hwtimer_obj_t *handle = timer->parent.user_data;
    switch (cmd)
    {
    case HWTIMER_CTRL_STOP:
        mcx_hwtimer_stop(timer);
        break;

    case HWTIMER_CTRL_MODE_SET:
        ret = mcx_hwtimer_mode_set(handle, *(rt_hwtimer_mode_t *)args);
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

static mcx_hwtimer_obj_t mcx_hwtimer_list[] =
{
    { .name = "timer0", .channel = kMRT_Channel_0, },
    { .name = "timer1", .channel = kMRT_Channel_1, },
    { .name = "timer2", .channel = kMRT_Channel_2, },
    { .name = "timer3", .channel = kMRT_Channel_3, },
};

static struct rt_hwtimer_info mcx_hwtimer_info =
{
    .cntmode = HWTIMER_CNTMODE_DW,
    .maxcnt = 0x00FFFFFF, /* 24bit counter */
    .minfreq = 150000000,
    .maxfreq = 150000000,
};

static const struct rt_hwtimer_ops mcx_hwtimer_ops =
{
    .init = mcx_hwtimer_init,
    .control = mcx_hwtimer_control,
    .start = mcx_hwtimer_start,
    .stop = mcx_hwtimer_stop,
    .count_get = mcx_hwtimer_count_get,
};

int rt_hw_hwtimer_init(void)
{
    /* MRT frequency is fixed to AHB clock */
    uint32_t mrt_freq = CLOCK_GetFreq(kCLOCK_BusClk);

    mcx_hwtimer_info.minfreq = mrt_freq;
    mcx_hwtimer_info.maxfreq = mrt_freq;

    for (uint8_t i = 0; i < ARRAY_SIZE(mcx_hwtimer_list); i++)
    {
        mcx_hwtimer_list[i].timer_device.info = &mcx_hwtimer_info;
        mcx_hwtimer_list[i].timer_device.ops = &mcx_hwtimer_ops;

        rt_err_t ret = rt_device_hwtimer_register(&mcx_hwtimer_list[i].timer_device, mcx_hwtimer_list[i].name, &mcx_hwtimer_list[i]);
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
            rt_device_hwtimer_isr(&mcx_hwtimer_list[i].timer_device);
        }
    }
}

INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);

#endif /* BSP_USING_HWTIMER */
