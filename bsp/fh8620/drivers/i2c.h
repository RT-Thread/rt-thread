/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __FH81_I2C_H__
#define __FH81_I2C_H__


#include <rtthread.h>

struct i2c_driver
{
    int cmd_err;
    int msg_err;
    rt_uint32_t status;

    struct rt_i2c_msg *msgs;
    int msgs_num;
    int msg_write_idx;
    rt_uint32_t tx_buf_len;
    rt_uint8_t *tx_buf;
    int msg_read_idx;
    rt_uint32_t rx_buf_len;
    rt_uint8_t *rx_buf;

    struct rt_i2c_bus_device *i2c_bus_dev;
    struct rt_completion transfer_completion;
    rt_mutex_t lock;
    void*  priv;
};

void rt_hw_i2c_init(void);

#endif
