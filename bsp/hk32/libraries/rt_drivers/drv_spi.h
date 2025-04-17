/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-15     Jonas        first version
 */

#ifndef __DRV_SPI__
#define __DRV_SPI__

#include <rtthread.h>
#include "drivers/dev_spi.h"
#include <hk32f0xx.h>

struct hk32_spi_config
{
    SPI_TypeDef *spix;
    const char *spi_name;
};

struct hk32_spi
{
    struct hk32_spi_config *config;
    struct rt_spi_bus spi_bus;
};

struct hk32_spi_cs
{
    GPIO_TypeDef *GPIOx;
    uint32_t GPIO_Pin;
};

/* public function */
int rt_hw_spi_init(void);
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef *cs_gpiox, uint16_t cs_gpio_pin);

#endif /* __DRV_SPI__ */
