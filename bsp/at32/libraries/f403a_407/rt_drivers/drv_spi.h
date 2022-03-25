/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-09     shelton      first version
 */

#ifndef __DRV_SPI__
#define __DRV_SPI__

#include <rtthread.h>
#include <drivers/spi.h>
#include "at32f403a_407.h"

struct at32_spi_config
{
    spi_type *spi_x;
    const char *spi_name;
};

struct at32_spi
{
    struct at32_spi_config *config;
    struct rt_spi_bus spi_bus;
};

struct at32_spi_cs
{
    gpio_type *gpio_x;
    uint32_t gpio_pin;
};

/* public function */
int rt_hw_spi_init(void);
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, gpio_type *cs_gpiox, uint16_t cs_gpio_pin);

#endif // __DRV_SPI__
