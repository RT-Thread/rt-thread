/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-20     BruceOu      first implementation
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

struct gd32_spi_cs
{
    uint32_t GPIOx;
    uint32_t GPIO_Pin;
};

/* gd32 spi dirver class */
struct gd32_spi
{
    uint32_t spi_periph;
    char *bus_name;
    rcu_periph_enum spi_clk;
    struct rt_spi_bus *spi_bus;
    const char *sck_pin_name;
    const char *miso_pin_name;
    const char *mosi_pin_name;
    const char *sck_alternate;
    const char *miso_alternate;
    const char *mosi_alternate;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */

