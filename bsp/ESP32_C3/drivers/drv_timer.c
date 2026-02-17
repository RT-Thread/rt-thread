/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-11-15       BetMul      first version
 */

#include "drv_timer.h"

#include <rtthread.h>
#include <rtdevice.h>
#include "driver/gptimer.h"
#include "sdkconfig.h"

#ifdef RT_USING_CLOCK_TIME

/**
 * handle interrupt for clock_timer.
 */
static bool mcu_clock_timer_intr_handler(gptimer_handle_t gptimer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    rt_interrupt_enter();

    rt_clock_timer_t *clock_timer = (rt_clock_timer_t *)user_ctx;
    rt_clock_timer_isr(clock_timer);

    rt_interrupt_leave();

    return 0;
}

/**
 * init the clock_timer
*/
static void mcu_clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;

    // let the gptimer into enable status
    ESP_ERROR_CHECK(gptimer_enable(gptimer));
}

/**
 * start the clock_timer, change status into running
*/
static rt_err_t mcu_clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;
    gptimer_alarm_config_t alarm_config = {
        .alarm_count = cnt,
    };
    if (mode == CLOCK_TIMER_MODE_ONESHOT)
    {

    }
    else
    {
        alarm_config.reload_count = 0;
        alarm_config.flags.auto_reload_on_alarm = true;
    }
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));
    ESP_ERROR_CHECK(gptimer_start(gptimer));

    return RT_EOK;
}

/**
 * stop the clock_timer, change the status from running into enable
*/
static void mcu_clock_timer_stop(rt_clock_timer_t *timer)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;

    ESP_ERROR_CHECK(gptimer_stop(gptimer));
}

/**
 * get count
*/
static rt_uint32_t mcu_clock_timer_count_get(rt_clock_timer_t *timer)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;
    // get count number
    uint64_t value;
    ESP_ERROR_CHECK(gptimer_get_raw_count(gptimer, &value));
    return (rt_uint32_t)value;
}

/**
 * control the clock_timer
*/
static rt_err_t mcu_clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{

    rt_err_t err = RT_EOK;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
        err = -RT_ERROR;
        break;

    case CLOCK_TIMER_CTRL_INFO_GET:
        err = -RT_ERROR;
        break;

    case CLOCK_TIMER_CTRL_MODE_SET:
        timer->mode = *(rt_uint32_t *)args;
        break;

    case CLOCK_TIMER_CTRL_STOP:
        mcu_clock_timer_stop(timer);
        break;
    }

    return err;
}

static struct rt_clock_timer_device _clock_timer;
static const struct rt_clock_timer_ops _clock_timer_ops =
    {
        .init = mcu_clock_timer_init,
        .start = mcu_clock_timer_start,
        .stop = mcu_clock_timer_stop,
        .count_get = mcu_clock_timer_count_get,
        .control = mcu_clock_timer_control};

static const struct rt_clock_timer_info _clock_timer_info =
    {
        // TODO:what is the true max and  min?
        .maxfreq = 1000000UL,
        .minfreq = 1000000UL,
        .maxcnt = 0xFFFF,
        .cntmode = CLOCK_TIMER_MODE_ONESHOT};

int rt_hw_clock_timer_init(void)
{

    char *name = "timer0";

    gptimer_handle_t gptimer = NULL;
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1 * 1000 * 1000,
    };

    gptimer_event_callbacks_t cbs = {
        .on_alarm = mcu_clock_timer_intr_handler,
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, &_clock_timer));

    _clock_timer.info = &_clock_timer_info;
    _clock_timer.ops = &_clock_timer_ops;

    return rt_clock_timer_register(&_clock_timer, name, (void *)gptimer);

}

INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);
#endif /* RT_USING_CLOCK_TIME */
