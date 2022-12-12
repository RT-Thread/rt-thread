/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-04     BruceOu      first implementation
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rthw.h>
#include <rtthread.h>
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
    rcu_periph_enum gpio_clk;
    struct rt_spi_bus *spi_bus;
    uint32_t spi_port;
    uint16_t sck_pin;
    uint16_t miso_pin;
    uint16_t mosi_pin;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */
