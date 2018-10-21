/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-27     Liuguang     the first version.
 */
 
#ifndef __DRV_SPI_BUS_H__ 
#define __DRV_SPI_BUS_H__ 

#include <rtthread.h> 
#include <rtdevice.h> 

int rt_hw_spi_bus_init(void);
rt_err_t rt1050_spi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin); 

#endif
