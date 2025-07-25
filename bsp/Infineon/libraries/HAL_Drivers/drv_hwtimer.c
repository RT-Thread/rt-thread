/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                   Notes
 * 2022-07-29     rtthread qiu       first version
 */
#include "drv_common.h"
#include "drv_hwtimer.h"

#include <board.h>
#ifdef BSP_USING_TIM

/*#define DRV_DEBUG*/
#define LOG_TAG "drv.hwtimer"
#include <drv_log.h>

static void isr_timer(void *callback_arg, cyhal_timer_event_t event);

#ifdef RT_USING_HWTIMER
enum
{
#ifdef BSP_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_TIM2
    TIM2_INDEX,
#endif
};

struct cyp_hwtimer
{
    rt_hwtimer_t time_device;
    cyhal_timer_t tim_handle;
    IRQn_Type tim_irqn;
    char *name;
};

static struct cyp_hwtimer cyp_hwtimer_obj[] =
{
#ifdef BSP_USING_TIM1
    TIM1_CONFIG,
#endif
#ifdef BSP_USING_TIM2
    TIM2_CONFIG,
#endif
};

static void timer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    RT_ASSERT(timer != RT_NULL);

    cy_rslt_t result = RT_EOK;

    cyhal_timer_t *tim = RT_NULL;

    tim = (cyhal_timer_t *)timer->parent.user_data;

    const cyhal_timer_cfg_t init_timer_cfg =
    {
        .compare_value = 0,              /* Timer compare value, not used */
        .period = 9999,                  /* Defines the timer period */
        .direction = CYHAL_TIMER_DIR_UP, /* Timer counts up */
        .is_compare = false,             /* Don't use compare mode */
        .is_continuous = true,           /* Run timer indefinitely */
        .value = 0                       /* Initial value of counter */
    };

    if (state)
    {
        /* Initialize the timer object. Does not use input pin ('pin' is NC) and
         * does not use a pre-configured clock source ('clk' is NULL). */
        result = cyhal_timer_init(tim, NC, NULL);

        if (result != CY_RSLT_SUCCESS)
        {
            LOG_E("timer init error \r\n");
            return;
        }
        else
        {
            /* Configure timer period and operation mode such as count direction,
                duration */
            cyhal_timer_configure(tim, &init_timer_cfg);

            /* Set the frequency of timer's clock source */
            cyhal_timer_set_frequency(tim, 10000);

            cyhal_timer_start(tim);
        }
    }
    else
    {
        cyhal_timer_free(tim);
        LOG_E("free time \r\n");
    }
}

static rt_err_t timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(opmode != RT_NULL);

    cy_rslt_t result = RT_EOK;

    cyhal_timer_t *tim = RT_NULL;

    tim = (cyhal_timer_t *)timer->parent.user_data;

    const cyhal_timer_cfg_t init_timer_cfg =
    {
        .compare_value = 0,              /* Timer compare value, not used */
        .period = t - 1,                 /* Defines the timer period */
        .direction = CYHAL_TIMER_DIR_UP, /* Timer counts up */
        .is_compare = false,             /* Don't use compare mode */
        .is_continuous = true,           /* Run timer indefinitely */
        .value = 0                       /* Initial value of counter */
    };
    /* Configure timer period and operation mode such as count direction,
    duration */
    cyhal_timer_configure(tim, &init_timer_cfg);

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        cyhal_timer_stop(tim);
    }
    else
    {
        cyhal_timer_reset(tim);
    }

    result = cyhal_timer_start(tim);
    if (result != CY_RSLT_SUCCESS)
    {
        LOG_E("time start error\r\n");
        cyhal_timer_free(tim);
    }

    /* Assign the ISR to execute on timer interrupt */
    cyhal_timer_register_callback(tim, isr_timer, NULL);

    /* Set the event on which timer interrupt occurs and enable it */
    cyhal_timer_enable_event(tim, CYHAL_TIMER_IRQ_TERMINAL_COUNT, 1, true);

    return result;
}

static void timer_stop(rt_hwtimer_t *timer)
{

    RT_ASSERT(timer != RT_NULL);

    cyhal_timer_t *tim = RT_NULL;

    tim = (cyhal_timer_t *)timer->parent.user_data;

    cyhal_timer_stop(tim);
}

static rt_uint32_t timer_counter_get(rt_hwtimer_t *timer)
{
    cyhal_timer_t *tim = RT_NULL;

    rt_uint32_t count;

    RT_ASSERT(timer != RT_NULL);

    tim = (cyhal_timer_t *)timer->parent.user_data;

    count = cyhal_timer_read(tim);

    return count;
}

static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    cyhal_timer_t *tim = RT_NULL;

    rt_err_t result = -RT_ERROR;

    tim = (cyhal_timer_t *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;
        rt_uint16_t val;

        freq = *((rt_uint32_t *)arg);

        result = cyhal_timer_set_frequency(tim, freq);

        if (result != CY_RSLT_SUCCESS)
        {
            LOG_E("cyhal_timer_set_frequency error\r\n");
            return -RT_ERROR;
        }
    }
    break;
    default:
    {
        result = -RT_EINVAL;
    }
    break;
    }
    return result;
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

static void isr_timer(void *callback_arg, cyhal_timer_event_t event)
{
    /* enter interrupt */
    rt_interrupt_enter();

    (void)callback_arg;
    (void)event;
#ifdef BSP_USING_TIM1
    rt_device_hwtimer_isr(&cyp_hwtimer_obj[TIM1_INDEX].time_device);
#endif
#ifdef BSP_USING_TIM2
    rt_device_hwtimer_isr(&cyp_hwtimer_obj[TIM2_INDEX].time_device);
#endif
    /* leave interrupt */
    rt_interrupt_leave();
}

int cyp_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(cyp_hwtimer_obj) / sizeof(cyp_hwtimer_obj[0]); i++)
    {
        cyp_hwtimer_obj[i].time_device.info = &_info;
        cyp_hwtimer_obj[i].time_device.ops = &_ops;
        if (rt_device_hwtimer_register(&cyp_hwtimer_obj[i].time_device, cyp_hwtimer_obj[i].name, &cyp_hwtimer_obj[i].tim_handle) != RT_EOK)
        {
            LOG_E("%s register failed", cyp_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }
    return result;
}
INIT_BOARD_EXPORT(cyp_hwtimer_init);

#endif /*RT_USING_HWTIMER*/
#endif /*BSP_USING_TIM*/

/* this is a hwtimer test demo*/
#include <rtthread.h>
#include <rtdevice.h>

#define HWTIMER_DEV_NAME "time2" /* device name */

static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

int hwtimer_sample()
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;
    rt_uint32_t freq = 10000;

    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return -RT_ERROR;
    }

    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);

    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* Example Set the timeout period of the timer */
    timeout_s.sec = 3;  /* secend */
    timeout_s.usec = 0; /* microsecend */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }

    while (1)
    {
        rt_thread_mdelay(1500);

        rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
        rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);
    }
    return ret;
}
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
