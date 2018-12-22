/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 20012-01-01    aozima       first implementation.
 */

#ifndef STM32F20X_40X_SPI_H_INCLUDED
#define STM32F20X_40X_SPI_H_INCLUDED

#include <rtthread.h>
#include <drivers/spi.h>

#include "stm32f4xx_hal.h"

//#define SPI_USE_DMA

struct stm32f4_spi
{
    SPI_HandleTypeDef spi_handle;
#ifdef SPI_USE_DMA
    DMA_HandleTypeDef hdma_rx;
    IRQn_Type hdma_rx_irq;

    DMA_HandleTypeDef hdma_tx;
    IRQn_Type hdma_tx_irq;
#endif /* #ifdef SPI_USE_DMA */
};

struct stm32_spi_cs
{
    GPIO_TypeDef * GPIOx;
    uint16_t GPIO_Pin;
};

/* public function */
rt_err_t stm32_spi_bus_register(SPI_TypeDef * SPI, const char * spi_bus_name);

#endif // STM32F20X_40X_SPI_H_INCLUDED
