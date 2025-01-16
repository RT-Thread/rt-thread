/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rtthread.h>

#define DBG_TAG "rtdm.led"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/led.h>
#include <drivers/core/dm.h>

struct blink_timer
{
    rt_bool_t toggle;
    rt_bool_t enabled;
    struct rt_timer timer;
};

static struct rt_dm_ida led_ida = RT_DM_IDA_INIT(LED);

static const char * const _led_states[] =
{
    [RT_LED_S_OFF] = "off",
    [RT_LED_S_ON] = "on",
    [RT_LED_S_TOGGLE] = "toggle",
    [RT_LED_S_BLINK] = "blink",
};

static rt_ssize_t _led_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_ssize_t res;
    rt_size_t state_len;
    enum rt_led_state state;
    struct rt_led_device *led = rt_container_of(dev, struct rt_led_device, parent);

    if ((res = rt_led_get_state(led, &state)))
    {
        return res;
    }

    state_len = rt_strlen(_led_states[state]);

    if (pos < state_len)
    {
        size = rt_min_t(rt_size_t, size, size - pos);
        ((char *)buffer)[size - 1] = '\0';
        rt_strncpy(buffer, &_led_states[state][pos], size);

        return size;
    }
    else
    {
        return 0;
    }
}

static rt_ssize_t _led_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_uint32_t brightness = 0;
    const char *value = buffer;
    struct rt_led_device *led = rt_container_of(dev, struct rt_led_device, parent);

    for (int i = 0; i < RT_ARRAY_SIZE(_led_states); ++i)
    {
        if (!rt_strncpy((char *)_led_states[i], buffer, size))
        {
            return rt_led_set_state(led, i) ? : size;
        }
    }

    while (*value)
    {
        if (*value < '0' || *value > '9')
        {
            return -RT_EINVAL;
        }

        brightness *= 10;
        brightness += *value - '0';

        ++value;
    }

    rt_led_set_brightness(led, brightness);

    return size;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _led_ops =
{
    .read = _led_read,
    .write = _led_write,
};
#endif

static void _led_blink_timerout(void *param)
{
    struct rt_led_device *led = param;
    struct blink_timer *btimer = led->sysdata;

    if (btimer->toggle)
    {
        led->ops->set_state(led, RT_LED_S_OFF);
    }
    else
    {
        led->ops->set_state(led, RT_LED_S_ON);
    }

    btimer->toggle = !btimer->toggle;
}

rt_err_t rt_hw_led_register(struct rt_led_device *led)
{
    rt_err_t err;
    int device_id;
    const char *dev_name;
    struct blink_timer *btimer = RT_NULL;

    if (!led || !led->ops)
    {
        return -RT_EINVAL;
    }

    if ((device_id = rt_dm_ida_alloc(&led_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_dm_dev_set_name(&led->parent, "led%u", device_id);
    dev_name = rt_dm_dev_get_name(&led->parent);

    led->sysdata = RT_NULL;
    rt_spin_lock_init(&led->spinlock);

    if (!led->ops->set_period && led->ops->set_state)
    {
        btimer = rt_malloc(sizeof(*btimer));

        if (!btimer)
        {
            LOG_E("%s create blink timer failed", dev_name);

            err = -RT_ENOMEM;
            goto _fail;
        }

        led->sysdata = btimer;

        btimer->toggle = RT_FALSE;
        btimer->enabled = RT_FALSE;
        rt_timer_init(&btimer->timer, dev_name, _led_blink_timerout, led,
                rt_tick_from_millisecond(500), RT_TIMER_FLAG_PERIODIC);
    }

    led->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    led->parent.ops = &_led_ops;
#else
    led->parent.read = _led_read;
    led->parent.write = _led_write;
#endif
    led->parent.master_id = led_ida.master_id;
    led->parent.device_id = device_id;

    if ((err = rt_device_register(&led->parent, dev_name, RT_DEVICE_FLAG_RDWR)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&led_ida, device_id);

    if (btimer)
    {
        rt_timer_detach(&btimer->timer);
        rt_free(btimer);

        led->sysdata = RT_NULL;
    }

    return err;
}

rt_err_t rt_hw_led_unregister(struct rt_led_device *led)
{
    if (!led)
    {
        return -RT_EINVAL;
    }

    rt_led_set_state(led, RT_LED_S_OFF);

    if (led->sysdata)
    {
        struct blink_timer *btimer = led->sysdata;

        rt_timer_detach(&btimer->timer);

        rt_free(btimer);
    }

    rt_dm_ida_free(&led_ida, led->parent.device_id);

    rt_device_unregister(&led->parent);

    return RT_EOK;
}

rt_err_t rt_led_set_state(struct rt_led_device *led, enum rt_led_state state)
{
    rt_err_t err;
    struct blink_timer *btimer;

    if (!led)
    {
        return -RT_EINVAL;
    }

    if (!led->ops->set_state)
    {
        return -RT_ENOSYS;
    }

    rt_spin_lock(&led->spinlock);

    btimer = led->sysdata;

    if (btimer && btimer->enabled)
    {
        rt_timer_stop(&btimer->timer);
    }

    err = led->ops->set_state(led, state);

    if (state == RT_LED_S_BLINK)
    {
        if (err == -RT_ENOSYS && btimer && !btimer->enabled)
        {
            btimer->enabled = RT_TRUE;
            rt_timer_start(&btimer->timer);
        }
    }
    else if (btimer && btimer->enabled)
    {
        if (err)
        {
            rt_timer_start(&btimer->timer);
        }
        else
        {
            btimer->enabled = RT_FALSE;
        }
    }

    rt_spin_unlock(&led->spinlock);

    return err;
}

rt_err_t rt_led_get_state(struct rt_led_device *led, enum rt_led_state *out_state)
{
    rt_err_t err;

    if (!led || !out_state)
    {
        return -RT_EINVAL;
    }

    if (!led->ops->get_state)
    {
        return -RT_ENOSYS;
    }

    rt_spin_lock(&led->spinlock);

    err = led->ops->get_state(led, out_state);

    rt_spin_unlock(&led->spinlock);

    return err;
}

rt_err_t rt_led_set_period(struct rt_led_device *led, rt_uint32_t period_ms)
{
    rt_err_t err;

    if (!led)
    {
        return -RT_EINVAL;
    }

    if (!led->ops->set_period && !led->sysdata)
    {
        return -RT_ENOSYS;
    }

    rt_spin_lock(&led->spinlock);

    if (led->ops->set_period)
    {
        err = led->ops->set_period(led, period_ms);
    }
    else
    {
        struct blink_timer *btimer = led->sysdata;
        rt_tick_t tick = rt_tick_from_millisecond(period_ms);

        err = rt_timer_control(&btimer->timer, RT_TIMER_CTRL_SET_TIME, &tick);
    }

    rt_spin_unlock(&led->spinlock);

    return err;
}

rt_err_t rt_led_set_brightness(struct rt_led_device *led, rt_uint32_t brightness)
{
    rt_err_t err;

    if (!led)
    {
        return -RT_EINVAL;
    }

    if (!led->ops->set_brightness)
    {
        return -RT_ENOSYS;
    }

    rt_spin_lock(&led->spinlock);

    err = led->ops->set_brightness(led, brightness);

    rt_spin_unlock(&led->spinlock);

    return err;
}
