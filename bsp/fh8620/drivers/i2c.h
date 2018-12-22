/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
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
