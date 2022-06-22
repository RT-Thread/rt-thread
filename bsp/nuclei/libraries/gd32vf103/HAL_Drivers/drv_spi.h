/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2029-04-29     hqfang       first implementation.
 */

#ifndef __DRV_SPI__
#define __DRV_SPI__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_config.h>

/* gd32 config class */
struct gd32_spi_config
{
    const char *name;
    rt_uint32_t spi_periph;
};

struct gd32_spi_cs
{
    rt_uint32_t pin;
};

struct gd32_spi
{
    struct rt_spi_bus bus;
    struct gd32_spi_config *config;
};

int rt_hw_spi_init(void);
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin);

#endif
