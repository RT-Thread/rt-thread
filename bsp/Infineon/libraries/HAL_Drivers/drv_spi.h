/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-18     Rbb666       first version
 */

#ifndef __DRV_SPI__
#define __DRV_SPI__

#include <rtthread.h>
#include <drivers/spi.h>

#include "drv_gpio.h"

#define SPI_FREQ_HZ         (10000000UL)

/* gd32 spi dirver class */
struct ifx_spi
{
    char *bus_name;
    struct rt_spi_bus *spi_bus;
    cyhal_spi_t *spi_obj;

    uint16_t sck_pin;
    uint16_t miso_pin;
    uint16_t mosi_pin;
    uint32_t freq;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, uint16_t cs_gpio_pin);

#endif
