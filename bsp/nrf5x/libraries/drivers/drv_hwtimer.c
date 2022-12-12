/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-21     chenyingchun first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <nrfx_timer.h>

#ifdef SOFTDEVICE_PRESENT
#ifdef BSP_USING_TIM0
#error "TIMER0 cannot be used when SOFTDEVICE has been used."
#endif
#endif

#ifdef BSP_USING_TIM

#define LOG_TAG             "drv.hwtimer"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_HWTIMER

#ifndef TIM_DEV_INFO_CONFIG
// maxfreq and minfreq unit is HZ
#define TIM_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 16000000,                    \
        .minfreq = 31250,                       \
        .maxcnt  = 0xFFFFFFFF,                  \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif

typedef struct
{
    nrfx_timer_t            timer_inst;
    nrfx_timer_config_t     timer_cfg;
    nrf_timer_cc_channel_t  cc_channel;
}nrf5x_timer_info_t;

struct nrf5x_hwtimer
{
    rt_hwtimer_t            timer_device;
    nrf5x_timer_info_t      timer_info;
    char                    *name;
};

static struct nrf5x_hwtimer nrf5x_hwtimer_obj[] =
{
#ifdef BSP_USING_TIM0
    {
       .timer_info.timer_inst = NRFX_TIMER_INSTANCE(0),
       .timer_info.timer_cfg  = NRFX_TIMER_DEFAULT_CONFIG,
       .timer_info.cc_channel = NRF_TIMER_CC_CHANNEL0,
       .name                  = "timer0",
    },
#endif

#ifdef BSP_USING_TIM1
    {
       .timer_info.timer_inst = NRFX_TIMER_INSTANCE(1),
       .timer_info.timer_cfg  = NRFX_TIMER_DEFAULT_CONFIG,
       .timer_info.cc_channel = NRF_TIMER_CC_CHANNEL1,
       .name                  = "timer1",
    },
#endif

#ifdef BSP_USING_TIM2
     {
        .timer_info.timer_inst = NRFX_TIMER_INSTANCE(2),
        .timer_info.timer_cfg  = NRFX_TIMER_DEFAULT_CONFIG,
        .timer_info.cc_channel = NRF_TIMER_CC_CHANNEL2,
        .name                  = "timer2",
     },
#endif

#ifdef BSP_USING_TIM3
     {
        .timer_info.timer_inst = NRFX_TIMER_INSTANCE(3),
        .timer_info.timer_cfg  = NRFX_TIMER_DEFAULT_CONFIG,
        .timer_info.cc_channel = NRF_TIMER_CC_CHANNEL3,
        .name                  = "timer3",
     },
#endif

#ifdef BSP_USING_TIM4
     {
        .timer_info.timer_inst = NRFX_TIMER_INSTANCE(4),
        .timer_info.timer_cfg  = NRFX_TIMER_DEFAULT_CONFIG,
        .timer_info.cc_channel = NRF_TIMER_CC_CHANNEL4,
        .name                  = "timer4",
     }
#endif
};

static void timer_callback(nrf_timer_event_t event_type, void* p_context)
{
    rt_hwtimer_t       *timer_device = (struct rt_hwtimer_device *)p_context;

    // no matter what event_type is(NRF_TIMER_EVENT_COMPARE0 or others), call same function "rt_device_hwtimer_isr"
    LOG_D("timer_callback event_type = %d, inst_id = %d, cc conunt = %d\r\n",
           event_type, timer_info->timer_inst.instance_id, timer_info->timer_inst.cc_channel_count);
    rt_device_hwtimer_isr(timer_device);
}

static void timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    nrf5x_timer_info_t *timer_info   = RT_NULL;
    nrfx_timer_config_t *timer_cfg   = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        timer_info = (nrf5x_timer_info_t *)timer->parent.user_data;
        timer_cfg  = &(timer_info->timer_cfg);
        timer_cfg->bit_width = NRF_TIMER_BIT_WIDTH_32;
        timer_cfg->p_context = timer;

        nrfx_timer_init(&(timer_info->timer_inst), timer_cfg, timer_callback);
    }
}

static rt_err_t timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    nrf5x_timer_info_t *timer_info   = RT_NULL;
    nrf_timer_short_mask_t mask = NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK;

    RT_ASSERT(timer != RT_NULL);

    timer_info = (nrf5x_timer_info_t *)timer->parent.user_data;

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        // means TIMER_SHORTS_COMPARE0_STOP_Msk or TIMER_SHORTS_COMPARE1_STOP_Msk ..., according to cc_channel.
        mask = (nrf_timer_short_mask_t)(1 << (timer_info->cc_channel + 8));
    }
    else
    {
        // means TIMER_SHORTS_COMPARE0_CLEAR_Msk or TIMER_SHORTS_COMPARE1_CLEAR_Msk ..., according to cc_channel.
        mask = (nrf_timer_short_mask_t)(1 << timer_info->cc_channel);
    }

    nrfx_timer_extended_compare(&(timer_info->timer_inst), timer_info->cc_channel, t, mask, true);
    nrfx_timer_enable(&(timer_info->timer_inst));
    return RT_EOK;
}

static void timer_stop(rt_hwtimer_t *timer)
{
    nrf5x_timer_info_t *timer_info = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    timer_info = (nrf5x_timer_info_t *)timer->parent.user_data;

    nrfx_timer_disable(&(timer_info->timer_inst));

    /* set time count register to zero*/
    nrfx_timer_clear(&(timer_info->timer_inst));
}

static nrf_timer_frequency_t frequency_convert(rt_uint32_t freq)
{
    nrf_timer_frequency_t frequency = NRF_TIMER_FREQ_1MHz;
    switch (freq)
    {
        case 16000000:
        {
            frequency = NRF_TIMER_FREQ_16MHz;
            break;
        }

        case 8000000:
        {
            frequency = NRF_TIMER_FREQ_8MHz;
            break;
        }

        case 2000000:
        {
            frequency = NRF_TIMER_FREQ_2MHz;
            break;
        }

        case 1000000:
        {
            frequency = NRF_TIMER_FREQ_1MHz;
            break;
        }

        case 500000:
        {
            frequency = NRF_TIMER_FREQ_500kHz;
            break;
        }

        case 250000:
        {
            frequency = NRF_TIMER_FREQ_250kHz;
            break;
        }

        case 125000:
        {
            frequency = NRF_TIMER_FREQ_125kHz;
            break;
        }

         case 62500:
        {
            frequency = NRF_TIMER_FREQ_62500Hz;
            break;
        }

        case 31250:
        {
            frequency = NRF_TIMER_FREQ_31250Hz;
            break;
        }

        default:
        {
            break;
        }
    }

    return frequency;
}

static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    rt_err_t result = RT_EOK;
    nrf5x_timer_info_t *timer_info = RT_NULL;
    nrfx_timer_t *timer_inst = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    timer_info = (nrf5x_timer_info_t *)timer->parent.user_data;
    timer_inst = &(timer_info->timer_inst);

    switch (cmd)
    {
        case HWTIMER_CTRL_FREQ_SET:
        {
            rt_uint32_t freq;
            /* set timer frequence */
            freq = *((rt_uint32_t *)arg);

            nrf_timer_frequency_set(timer_inst->p_reg, frequency_convert(freq));
            break;
        }
        default:
        {
            result = -RT_ENOSYS;
            break;
        }

    }

    return result;
}

static rt_uint32_t timer_counter_get(rt_hwtimer_t *timer)
{
    rt_uint32_t count = 0;
    nrf5x_timer_info_t *timer_info = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    timer_info = (nrf5x_timer_info_t *)timer->parent.user_data;

    // capture method will copy the current counter register to the specified cc channel (here is NRF_TIMER_CC_CHANNEL5).
    // the specified cc channel cannot be same with the already used cc channels
    count = nrfx_timer_capture(&(timer_info->timer_inst), NRF_TIMER_CC_CHANNEL5);
    return count;
}

static const struct rt_hwtimer_info _info = TIM_DEV_INFO_CONFIG;
static const struct rt_hwtimer_ops _ops =
{
    .init = timer_init,
    .start = timer_start,
    .stop = timer_stop,
    .count_get = timer_counter_get,
    .control = timer_ctrl,
};

static int nrf5x_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(nrf5x_hwtimer_obj) / sizeof(nrf5x_hwtimer_obj[0]); i++)
    {
        nrf5x_hwtimer_obj[i].timer_device.info = &_info;
        nrf5x_hwtimer_obj[i].timer_device.ops  = &_ops;
        if (rt_device_hwtimer_register(&nrf5x_hwtimer_obj[i].timer_device, nrf5x_hwtimer_obj[i].name, &nrf5x_hwtimer_obj[i].timer_info) == RT_EOK)
        {
            LOG_D("%s register success", nrf5x_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", nrf5x_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(nrf5x_hwtimer_init);

#endif /* RT_USING_HWTIMER */
#endif /* BSP_USING_TIM */

