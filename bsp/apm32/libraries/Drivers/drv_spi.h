/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "board.h"
#include <rtthread.h>
#include "drivers/dev_spi.h"

struct apm32_spi_config
{
    SPI_T *spi_x;
    char *spi_bus_name;
};

struct apm32_spi
{
    struct apm32_spi_config *config;
    struct rt_spi_bus spi_bus;
};

struct apm32_spi_cs
{
    GPIO_T *GPIOx;
    uint16_t GPIO_Pin;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_T *cs_gpiox, uint16_t cs_gpio_pin);

#endif /*__DRV_SPI_H__ */
