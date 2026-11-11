/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-12     lugl         first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

#ifdef RT_USING_SPI

struct ns800_spi_config
{
    const char *name;
    SPI_TypeDef *Instance;
    IRQn_Type rx_irq_type;
    IRQn_Type tx_irq_type;
    GPIO_TypeDef *sck_port;
    GPIO_PinNum sck_pin;
    GPIO_AltFunc sck_mux;
    GPIO_TypeDef *mosi_port;
    GPIO_PinNum mosi_pin;
    GPIO_AltFunc mosi_mux;
    GPIO_TypeDef *miso_port;
    GPIO_PinNum miso_pin;
    GPIO_AltFunc miso_mux;
};

struct ns800_spi
{
    SPI_TypeDef *Instance;
    struct rt_spi_bus spi_bus;
    struct ns800_spi_config *config;
};

int rt_hw_spi_init(void);

#endif

#endif /* __DRV_SPI_H__ */

