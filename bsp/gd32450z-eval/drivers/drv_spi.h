/*
 * File      : gd32f20x_40x_spi.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 20012-01-01    aozima       first implementation.
 */

#ifndef gd32F20X_40X_SPI_H_INCLUDED
#define gd32F20X_40X_SPI_H_INCLUDED

#include <rtthread.h>
#include <drivers/spi.h>

#include "gd32f4xx.h"

struct gd32f4_spi
{
    uint32_t spi_periph;
    rcu_periph_enum spi_clk;
    struct rt_spi_bus *spi_bus;
};


struct gd32_spi_cs
{
    uint32_t GPIOx;
    uint32_t GPIO_Pin;
};

/* public function */
rt_err_t gd32_spi_bus_register(uint32_t spi_periph,
								//struct gd32_spi_bus * gd32_spi,
								const char * spi_bus_name);

#endif // gd32F20X_40X_SPI_H_INCLUDED
