/*
 * File      : stm32f1_i2c.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author                Notes
 * 2017-07-04     aubrcool@qq.com       1st version
 */
#include "stm32f10x.h"
#include <rtdevice.h>

#ifndef __STM32F10X_I2C_H__
#define __STM32F10X_I2C_H__

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"

#include "board.h"


struct stm32_i2c_bus
{
    struct rt_i2c_bus_device parent;
    struct rt_event ev;
    I2C_TypeDef *I2C;
    struct rt_i2c_msg *msg;
    rt_uint32_t msg_cnt;
    volatile rt_uint32_t msg_ptr;
    volatile rt_uint32_t dptr;
    rt_uint32_t wait_stop;
};

/* public function list */
rt_err_t stm32_i2c_register(I2C_TypeDef *I2C, rt_uint32_t bitrate,
                                        const char * i2c_bus_name);

#endif /*__STM32F10X_I2C_H__*/
