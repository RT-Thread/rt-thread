/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-20     ZYH            the first version
 */

#ifndef __STM32_SPI_H_
#define __STM32_SPI_H_

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>


//cannot be used before completion init
extern rt_err_t stm32_spi_bus_attach_device(rt_uint32_t pin,const char * bus_name,const char * device_name);
extern int stm32_hw_spi_init(void);



#endif








