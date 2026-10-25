/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-07     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "input.ts.cst3530"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define CST3530_MAX_CONTACTS       5
#define CST3530_MAX_WIDTH          4096
#define CST3530_MAX_HEIGHT         4096
#define CST3530_REPORT_SIZE        64
#define CST3530_POLL_INTERVAL_MS   20

#define CST3530_DATA_START_REG     0xd0070000U
#define CST3530_DATA_CLEAR_REG     0xd00002abU

struct cst3530_ts
{
    struct rt_input_device parent;
    struct rt_i2c_client *client;

    rt_ssize_t irq_pin;
    rt_ssize_t reset_pin;
    rt_uint8_t irq_mode;
    rt_uint8_t reset_active;
    rt_bool_t active_slots[CST3530_MAX_CONTACTS];
    rt_bool_t use_irq;
    rt_bool_t irq_sem_inited;

    struct rt_thread *worker;
    struct rt_semaphore irq_sem;
};

static rt_err_t cst3530_i2c_read(struct cst3530_ts *ts, rt_uint32_t reg,
                                 rt_uint8_t *buf, rt_size_t len)
{
    rt_uint8_t address[] = {
        (rt_uint8_t)(reg >> 24),
        (rt_uint8_t)(reg >> 16),
        (rt_uint8_t)(reg >> 8),
        (rt_uint8_t)reg,
    };
    struct rt_i2c_msg msgs[] = {
        {
            .addr = ts->client->client_addr,
            .flags = RT_I2C_WR,
            .buf = address,
            .len = sizeof(address),
        },
        {
            .addr = ts->client->client_addr,
            .flags = RT_I2C_RD,
            .buf = buf,
            .len = len,
        },
    };
    rt_ssize_t res;

    res = rt_i2c_transfer(ts->client->bus, msgs, RT_ARRAY_SIZE(msgs));

    if (res < 0)
    {
        return res;
    }

    return res == RT_ARRAY_SIZE(msgs) ? RT_EOK : -RT_EIO;
}

static rt_err_t cst3530_i2c_write_address(struct cst3530_ts *ts, rt_uint32_t reg)
{
    rt_uint8_t address[] = {
        (rt_uint8_t)(reg >> 24),
        (rt_uint8_t)(reg >> 16),
        (rt_uint8_t)(reg >> 8),
        (rt_uint8_t)reg,
    };
    struct rt_i2c_msg msg = {
        .addr = ts->client->client_addr,
        .flags = RT_I2C_WR,
        .buf = address,
        .len = sizeof(address),
    };
    rt_ssize_t res;

    res = rt_i2c_transfer(ts->client->bus, &msg, 1);

    if (res < 0)
    {
        return res;
    }

    return res == 1 ? RT_EOK : -RT_EIO;
}

static void cst3530_release_unused_slots(struct cst3530_ts *ts,
                                          const rt_bool_t *seen_slots)
{
    int slot;

    for (slot = 0; slot < CST3530_MAX_CONTACTS; ++slot)
    {
        if (ts->active_slots[slot] && !seen_slots[slot])
        {
            rt_input_report_touch_slot(&ts->parent, slot);
            rt_input_event(&ts->parent, EV_ABS, ABS_MT_TRACKING_ID, -1);
            ts->active_slots[slot] = RT_FALSE;
        }
    }
}

static rt_err_t cst3530_process_events(struct cst3530_ts *ts)
{
    rt_uint8_t report[CST3530_REPORT_SIZE];
    rt_bool_t seen_slots[CST3530_MAX_CONTACTS] = { RT_FALSE };
    rt_uint8_t report_type;
    rt_uint8_t contacts;
    rt_uint8_t key_count;
    int point;
    rt_err_t err;

    err = cst3530_i2c_read(ts, CST3530_DATA_START_REG, report, sizeof(report));
    if (err)
    {
        return err;
    }

    /* The controller requires an address-only write after each report read. */
    err = cst3530_i2c_write_address(ts, CST3530_DATA_CLEAR_REG);
    if (err)
    {
        LOG_D("failed to acknowledge touch report: %s", rt_strerror(err));
    }

    report_type = report[2];
    contacts = report[3] & 0x0f;
    key_count = report[3] >> 4;

    if (report_type != 0xff || contacts > CST3530_MAX_CONTACTS)
    {
        contacts = 0;
    }

    for (point = 0; point < contacts; ++point)
    {
        rt_uint32_t x;
        rt_uint32_t y;
        rt_uint32_t strength;
        rt_size_t offset = (key_count + point) * 5;

        if (offset + 7 >= sizeof(report))
        {
            break;
        }

        x = report[offset + 4] | ((report[offset + 7] & 0x0f) << 8);
        y = report[offset + 5] | ((report[offset + 7] & 0xf0) << 4);
        strength = report[offset + 6];

        if (!strength || x >= CST3530_MAX_WIDTH || y >= CST3530_MAX_HEIGHT)
        {
            continue;
        }

        rt_input_parse_touch_position(&ts->parent, &x, &y);
        rt_input_report_touch_slot(&ts->parent, point);
        rt_input_event(&ts->parent, EV_ABS, ABS_MT_TRACKING_ID, point);
        rt_input_report_touch_position(&ts->parent, x, y, RT_TRUE);
        rt_input_report_abs(&ts->parent, ABS_MT_TOUCH_MAJOR, strength);
        rt_input_report_abs(&ts->parent, ABS_MT_WIDTH_MAJOR, strength);
        ts->active_slots[point] = RT_TRUE;
        seen_slots[point] = RT_TRUE;
    }

    cst3530_release_unused_slots(ts, seen_slots);
    rt_input_sync(&ts->parent);

    return RT_EOK;
}

static void cst3530_handle_events(struct cst3530_ts *ts)
{
    rt_err_t err;

    err = cst3530_process_events(ts);
    if (err)
    {
        LOG_D("failed to read touch report: %s", rt_strerror(err));
    }
}

static void cst3530_worker_entry(void *parameter)
{
    struct cst3530_ts *ts = parameter;

    while (RT_TRUE)
    {
        rt_sem_take(&ts->irq_sem, RT_WAITING_FOREVER);
        cst3530_handle_events(ts);
    }
}

static void cst3530_irq_callback(void *parameter)
{
    struct cst3530_ts *ts = parameter;

    rt_sem_release(&ts->irq_sem);
}

static void cst3530_poll(struct rt_input_device *idev)
{
    struct cst3530_ts *ts = rt_container_of(idev, struct cst3530_ts, parent);

    cst3530_handle_events(ts);
}

static rt_err_t cst3530_reset(struct cst3530_ts *ts)
{
    if (ts->reset_pin < 0)
    {
        return RT_EOK;
    }

    rt_pin_mode(ts->reset_pin, PIN_MODE_OUTPUT);
    rt_pin_write(ts->reset_pin, ts->reset_active);
    rt_thread_mdelay(20);
    rt_pin_write(ts->reset_pin, !ts->reset_active);
    rt_thread_mdelay(200);

    return RT_EOK;
}

static rt_err_t cst3530_setup_irq(struct cst3530_ts *ts)
{
    rt_err_t err;

    if (ts->irq_pin < 0)
    {
        return -RT_ENOSYS;
    }

    rt_pin_mode(ts->irq_pin, PIN_MODE_INPUT);

    err = rt_pin_attach_irq(ts->irq_pin, ts->irq_mode, cst3530_irq_callback, ts);
    if (err)
    {
        return err;
    }

    err = rt_pin_irq_enable(ts->irq_pin, RT_TRUE);
    if (err)
    {
        rt_pin_detach_irq(ts->irq_pin);
    }

    return err;
}

static rt_err_t cst3530_setup_polling(struct cst3530_ts *ts)
{
    rt_err_t err;

    err = rt_input_setup_polling(&ts->parent, cst3530_poll);
    if (err)
    {
        return err;
    }

    return rt_input_set_poll_interval(&ts->parent, CST3530_POLL_INTERVAL_MS);
}

static void cst3530_destroy(struct cst3530_ts *ts)
{
    if (ts->use_irq && ts->irq_pin >= 0)
    {
        rt_pin_irq_enable(ts->irq_pin, RT_FALSE);
        rt_pin_detach_irq(ts->irq_pin);
    }

    if (ts->worker)
    {
        rt_thread_delete(ts->worker);
    }

    if (ts->irq_sem_inited)
    {
        rt_sem_detach(&ts->irq_sem);
    }
}

static rt_err_t cst3530_probe(struct rt_i2c_client *client)
{
    struct rt_device *dev = &client->parent;
    struct rt_touch_info touch_info = {};
    struct cst3530_ts *ts;
    rt_uint8_t irq_active = 0;
    rt_uint8_t report[CST3530_REPORT_SIZE];
    rt_err_t err;

    ts = rt_calloc(1, sizeof(*ts));
    if (!ts)
    {
        return -RT_ENOMEM;
    }

    ts->client = client;
    ts->irq_pin = rt_pin_get_named_pin(dev, "interrupt", 0, RT_NULL, &irq_active);
    ts->reset_pin = rt_pin_get_named_pin(dev, "reset", 0, RT_NULL, &ts->reset_active);
    ts->irq_mode = irq_active ? PIN_IRQ_MODE_RISING : PIN_IRQ_MODE_FALLING;
    ts->parent.parent.ofw_node = dev->ofw_node;
    dev->user_data = ts;

    if ((ts->irq_pin < 0 && ts->irq_pin != PIN_NONE) ||
        (ts->reset_pin < 0 && ts->reset_pin != PIN_NONE))
    {
        err = -RT_EINVAL;
        goto _free;
    }

    if ((err = cst3530_reset(ts)))
    {
        goto _free;
    }

    /* CST3530 has no public chip-ID register; an idle report is its probe. */
    if ((err = cst3530_i2c_read(ts, CST3530_DATA_START_REG, report, sizeof(report))))
    {
        LOG_E("I2C communication failed at 0x%02x: %s",
              client->client_addr, rt_strerror(err));
        goto _free;
    }
    cst3530_i2c_write_address(ts, CST3530_DATA_CLEAR_REG);

    err = rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_SLOT);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_TRACKING_ID);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_POSITION_X);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_POSITION_Y);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_TOUCH_MAJOR);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_WIDTH_MAJOR);
    if (err)
    {
        goto _free;
    }

    rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_X, 0, CST3530_MAX_WIDTH - 1, 0, 0);
    rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_Y, 0, CST3530_MAX_HEIGHT - 1, 0, 0);
    rt_input_set_absinfo(&ts->parent, ABS_MT_TOUCH_MAJOR, 0, RT_UINT8_MAX, 0, 0);
    rt_input_set_absinfo(&ts->parent, ABS_MT_WIDTH_MAJOR, 0, RT_UINT8_MAX, 0, 0);

    touch_info.type = RT_TOUCH_TYPE_CAPACITANCE;
    touch_info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
    touch_info.point_num = CST3530_MAX_CONTACTS;

    err = rt_input_setup_touch(&ts->parent, CST3530_MAX_CONTACTS, &touch_info);
    if (err)
    {
        goto _free;
    }

    err = rt_sem_init(&ts->irq_sem, "cst3530", 0, RT_IPC_FLAG_FIFO);
    if (!err)
    {
        ts->irq_sem_inited = RT_TRUE;
        err = cst3530_setup_irq(ts);
    }

    if (err)
    {
        if (ts->irq_sem_inited)
        {
            rt_sem_detach(&ts->irq_sem);
            ts->irq_sem_inited = RT_FALSE;
        }

        err = cst3530_setup_polling(ts);
        if (err)
        {
            goto _remove_input;
        }
    }
    else
    {
        ts->use_irq = RT_TRUE;
        ts->worker = rt_thread_create(rt_dm_dev_get_name(dev), cst3530_worker_entry,
                                      ts, DM_THREAD_STACK_SIZE,
                                      RT_THREAD_PRIORITY_MAX / 2, 10);
        if (!ts->worker)
        {
            rt_pin_irq_enable(ts->irq_pin, RT_FALSE);
            rt_pin_detach_irq(ts->irq_pin);
            ts->use_irq = RT_FALSE;
            rt_sem_detach(&ts->irq_sem);
            ts->irq_sem_inited = RT_FALSE;

            if ((err = cst3530_setup_polling(ts)))
            {
                goto _remove_input;
            }
        }
    }

    err = rt_input_device_register(&ts->parent);
    if (err)
    {
        goto _remove_input;
    }

    if (ts->worker)
    {
        rt_thread_startup(ts->worker);
    }

    LOG_I("CST3530 touch ready at 0x%02x (%s)", client->client_addr,
          ts->use_irq ? "interrupt" : "polling");

    return RT_EOK;

_remove_input:
    cst3530_destroy(ts);
    rt_input_remove_config(&ts->parent);
_free:
    if (dev->user_data == ts)
    {
        dev->user_data = RT_NULL;
    }
    rt_free(ts);

    return err;
}

static rt_err_t cst3530_remove(struct rt_i2c_client *client)
{
    struct cst3530_ts *ts = client->parent.user_data;

    if (!ts)
    {
        return RT_EOK;
    }

    client->parent.user_data = RT_NULL;
    cst3530_destroy(ts);
    rt_input_device_unregister(&ts->parent);
    rt_free(ts);

    return RT_EOK;
}

static const struct rt_i2c_device_id cst3530_ids[] = {
    { .name = "cst3530" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id cst3530_ofw_ids[] = {
    { .compatible = "cst,cst3530" },
    { .compatible = "chipsea,cst3530" },
    { /* sentinel */ },
};

static struct rt_i2c_driver cst3530_driver = {
    .ids = cst3530_ids,
    .ofw_ids = cst3530_ofw_ids,

    .probe = cst3530_probe,
    .remove = cst3530_remove,
};
RT_I2C_DRIVER_EXPORT(cst3530_driver);
