/*
 * File      : drv_i2c.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-24     LaiYiKeTang  the first version
 */

#ifndef __DRVI2C_H__
#define __DRVI2C_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
struct rt1052_i2c_bus
{
    struct rt_i2c_bus_device parent;
    LPI2C_Type *I2C;
    struct rt_i2c_msg *msg;
    rt_uint32_t msg_cnt;
    volatile rt_uint32_t msg_ptr;
    volatile rt_uint32_t dptr;
    char *device_name;
};

#endif

