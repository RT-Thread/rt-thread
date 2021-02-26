/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtdevice.h>
#include <rthw.h>
#include "drivers/spi.h"

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, uint32_t portindex, uint32_t  cs_gpiobase, uint32_t cs_gpio_pin);

struct tm4c123_hw_spi_cs
{
    uint32_t portbase;
    uint32_t GPIO_Pin;
};

struct tm4c123_spi_config
{
    uint32_t   base;
    char      *bus_name;
};

/* tm4c123 spi dirver class */
struct tm4c123_spi
{
    struct tm4c123_spi_config *config;
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus spi_bus;
};

struct tm4c123_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};

#endif /*__DRV_SPI_H__ */

/************************** end of file ******************/