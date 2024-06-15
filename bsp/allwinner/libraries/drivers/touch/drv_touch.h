/*
 * COPYRIGHT (C) 2012-2024, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread  the first version
 */

#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include <stddef.h>
#include "rtthread.h"
#include "rtdevice.h"

#define TOUCH_POLL_MODE (1 << 0)
#define TOUCH_INT_MODE (1 << 1)

struct touch_ops
{
    void (*init)(struct rt_i2c_bus_device *);
    void (*deinit)(void);
    rt_err_t (*read_point)(struct rt_touch_data *touch_data, rt_size_t touch_num);
};
typedef struct touch_ops *touch_ops_t;

struct touch_driver
{
    rt_slist_t list;
    rt_bool_t (*probe)(struct rt_i2c_bus_device *i2c_bus);
    rt_tick_t read_interval;
    rt_uint32_t check_mode;
    touch_ops_t ops;
    void *user_data;
};
typedef struct touch_driver *touch_driver_t;

rt_err_t rt_touch_drivers_register(touch_driver_t drv);

int rt_touch_read(rt_uint16_t addr, void *cmd_buf, size_t cmd_len, void *data_buf, size_t data_len);
int rt_touch_write(rt_uint16_t addr, void *data_buf, size_t data_len);
void touch_coord_convert(int *x, int *y, int range_x, int range_y, int flag);
#endif
