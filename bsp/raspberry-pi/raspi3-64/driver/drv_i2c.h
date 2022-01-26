/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include <rtdevice.h>
#include <rtthread.h>

#include "board.h"

struct raspi_master_config_t
{
    rt_uint8_t sdl_pin;
    rt_uint8_t scl_pin;
    rt_uint8_t sdl_pin_mode;
    rt_uint8_t scl_pin_mode;
    rt_uint8_t slave_address;
    rt_uint32_t bsc_base;
    rt_uint16_t clk_div;
};

struct raspi_i2c_bus
{
    struct rt_i2c_bus_device device;
    struct rt_i2c_msg *msg;
    rt_uint32_t msg_cnt;
    volatile rt_uint32_t msg_ptr;
    volatile rt_uint32_t dptr;
    char *device_name;
    struct raspi_master_config_t *cfg;
};

int rt_hw_i2c_init(void);

#endif
