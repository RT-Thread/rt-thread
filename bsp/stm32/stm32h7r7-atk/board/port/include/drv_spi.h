/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 */

#ifndef __DRV_SPI_H_
#define __DRV_SPI_H_

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef* cs_gpiox, uint16_t cs_gpio_pin);

struct stm32_hw_spi_cs
{
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
};

struct stm32_spi_config
{
    SPI_TypeDef *Instance;
    char *bus_name;
    struct dma_config *dma_rx, *dma_tx;
};

struct stm32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};

#define SPI_USING_RX_DMA_FLAG   (1<<0)
#define SPI_USING_TX_DMA_FLAG   (1<<1)

/* stm32 spi dirver class */
struct stm32_spi
{
    SPI_HandleTypeDef handle;
    struct stm32_spi_config *config;
    struct rt_spi_configuration *cfg;

    struct
    {
        DMA_HandleTypeDef handle_rx;
        DMA_HandleTypeDef handle_tx;
    } dma;

    rt_uint8_t spi_dma_flag;
    struct rt_spi_bus spi_bus;
};

#endif /*__DRV_SPI_H_ */
