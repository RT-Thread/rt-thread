/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#ifndef __DRV_SPI_H__ 
#define __DRV_SPI_H__ 

#include <rtthread.h> 
#include <rtdevice.h> 

int rt_hw_spi_init(void);
rt_err_t lpc_spi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin); 

#endif
