/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-11-15       BetMul      first version
 */

#include "drv_hwtimer.h"

#include <rtthread.h>
#include <rtdevice.h>
#include "driver/gptimer.h"
#include "sdkconfig.h"

#ifdef RT_USING_HWTIMER

/**
 * handle interrupt for hwtimer.
 */
static bool mcu_hwtimer_intr_handler(gptimer_handle_t gptimer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    rt_interrupt_enter();

    rt_hwtimer_t *hwtimer = (rt_hwtimer_t *)user_ctx;
    rt_device_hwtimer_isr(hwtimer);

    rt_interrupt_leave();

    return 0;
}

/**
 * init the hwtimer
*/
static void mcu_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;

    // let the gptimer into enable status
    ESP_ERROR_CHECK(gptimer_enable(gptimer));
}

/**
 * start the hwtimer, change status into running
*/
static rt_err_t mcu_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;
    gptimer_alarm_config_t alarm_config = {
        .alarm_count = cnt,
    };
    if (mode == HWTIMER_MODE_ONESHOT)
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
 * stop the hwtimer, change the status from running into enable
*/
static void mcu_hwtimer_stop(rt_hwtimer_t *timer)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;

    ESP_ERROR_CHECK(gptimer_stop(gptimer));
}

/**
 * get count
*/
static rt_uint32_t mcu_hwtimer_count_get(rt_hwtimer_t *timer)
{
    gptimer_handle_t gptimer = (gptimer_handle_t)timer->parent.user_data;
    // get count number
    uint64_t value;
    ESP_ERROR_CHECK(gptimer_get_raw_count(gptimer, &value));
    return (rt_uint32_t)value;
}

/**
 * control the hwtimer
*/
static rt_err_t mcu_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{

    rt_err_t err = RT_EOK;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        err = -RT_ERROR;
        break;

    case HWTIMER_CTRL_INFO_GET:
        err = -RT_ERROR;
        break;

    case HWTIMER_CTRL_MODE_SET:
        timer->mode = *(rt_uint32_t *)args;
        break;

    case HWTIMER_CTRL_STOP:
        mcu_hwtimer_stop(timer);
        break;
    }

    return err;
}

static struct rt_hwtimer_device _hwtimer;
static const struct rt_hwtimer_ops _hwtimer_ops =
    {
        .init = mcu_hwtimer_init,
        .start = mcu_hwtimer_start,
        .stop = mcu_hwtimer_stop,
        .count_get = mcu_hwtimer_count_get,
        .control = mcu_hwtimer_control};

static const struct rt_hwtimer_info _hwtimer_info =
    {
        // TODO:what is the true max and  min?
        .maxfreq = 1000000UL,
        .minfreq = 1000000UL,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_MODE_ONESHOT};

int rt_hw_hwtimer_init(void)
{

    char *name = "timer0";

    gptimer_handle_t gptimer = NULL;
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1 * 1000 * 1000,
    };

    gptimer_event_callbacks_t cbs = {
        .on_alarm = mcu_hwtimer_intr_handler,
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, &_hwtimer));

    _hwtimer.info = &_hwtimer_info;
    _hwtimer.ops = &_hwtimer_ops;

    return rt_device_hwtimer_register(&_hwtimer, name, (void *)gptimer);

}

INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);
#endif /* RT_USING_HWTIMER */
