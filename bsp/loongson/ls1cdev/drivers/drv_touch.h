/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     Zhangyihong  the first version
 * 2018-10-29     XY
 */

#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include "rtthread.h"
#include "rtdevice.h"

#define TOUCH_EVENT_UP      (0x01)
#define TOUCH_EVENT_DOWN    (0x02)
#define TOUCH_EVENT_MOVE    (0x03)
#define TOUCH_EVENT_NONE    (0x80)

struct touch_message
{
    rt_uint16_t x;
    rt_uint16_t y;
    rt_uint8_t event;
};
typedef struct touch_message *touch_message_t;

struct touch_ops
{
    void (*init)(struct rt_i2c_bus_device *);
    void (*deinit)(void);
    rt_err_t (*read_point)(touch_message_t);
};
typedef struct touch_ops *touch_ops_t;

struct touch_driver
{
    rt_slist_t      list;
    rt_bool_t (*probe)(struct rt_i2c_bus_device *i2c_bus);
    rt_sem_t        isr_sem;
    touch_ops_t     ops;
    void            *user_data;
};
typedef struct touch_driver *touch_driver_t;

rt_err_t rt_touch_drivers_register(touch_driver_t drv);

int rt_touch_read(rt_uint16_t addr, void *cmd_buf, size_t cmd_len, void *data_buf, size_t data_len);
int rt_touch_write(rt_uint16_t addr, void *data_buf, size_t data_len);

#endif
