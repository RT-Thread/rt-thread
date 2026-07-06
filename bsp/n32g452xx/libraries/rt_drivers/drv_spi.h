/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-06     BalanceTWK        first version
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <n32g45x.h>

#ifdef __cplusplus
extern "C" {
#endif

struct n32_hw_spi_cs
{
    GPIO_Module* module;
    uint32_t pin;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_Module *cs_gpiox, uint32_t cs_gpio_pin);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_CONFIG_H__ */
