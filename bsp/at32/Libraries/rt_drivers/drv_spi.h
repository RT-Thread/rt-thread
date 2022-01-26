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
#include "at32f4xx.h"

struct at32_spi_config
{
    SPI_Type *spix;
    const char *spi_name;
};

struct at32_spi
{
    struct at32_spi_config *config;
    struct rt_spi_bus spi_bus;
};

struct at32_spi_cs
{
    GPIO_Type *GPIOx;
    uint32_t GPIO_Pin;
};

/* public function */
int rt_hw_spi_init(void);
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_Type *cs_gpiox, uint16_t cs_gpio_pin);

#endif // __DRV_SPI__
