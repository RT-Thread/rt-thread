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

struct ifx_spi_handle
{
    const char *bus_name;
    cyhal_spi_t *spi_obj;

    uint16_t sck_pin;
    uint16_t miso_pin;
    uint16_t mosi_pin;
    uint32_t freq;
};

/* ifx spi dirver class */
struct ifx_spi
{
    rt_uint32_t cs_pin;

    struct ifx_spi_handle       *spi_handle_t;
    struct rt_spi_configuration *rt_spi_cfg_t;
    struct rt_spi_bus spi_bus;

    struct rt_completion cpt;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#endif
