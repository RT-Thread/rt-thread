/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "board.h"

struct swm_spi_cs
{
    GPIO_TypeDef *GPIOx;
    uint32_t gpio_pin;
};

struct swm_spi_cfg
{
    const char *name;
    SPI_TypeDef *SPIx;
    SPI_InitStructure spi_initstruct;
};

/* swm spi dirver class */
struct swm_spi
{
    struct swm_spi_cfg *cfg;
    struct rt_spi_configuration *configure;
    struct rt_spi_bus spi_bus;
};

#ifdef BSP_USING_SPI0
#ifndef SPI0_BUS_CONFIG
#define SPI0_BUS_CONFIG                               \
    {                                                 \
        .name = "spi0",                               \
        .SPIx = SPI0,                                 \
        .spi_initstruct.clkDiv = SPI_CLKDIV_32,       \
        .spi_initstruct.FrameFormat = SPI_FORMAT_SPI, \
        .spi_initstruct.SampleEdge = SPI_SECOND_EDGE, \
        .spi_initstruct.IdleLevel = SPI_HIGH_LEVEL,   \
        .spi_initstruct.WordSize = 8,                 \
        .spi_initstruct.Master = 1,                   \
        .spi_initstruct.RXHFullIEn = 0,               \
        .spi_initstruct.TXEmptyIEn = 0,               \
        .spi_initstruct.TXCompleteIEn = 0,            \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                               \
    {                                                 \
        .name = "spi1",                               \
        .SPIx = SPI1,                                 \
        .spi_initstruct.clkDiv = SPI_CLKDIV_32,       \
        .spi_initstruct.FrameFormat = SPI_FORMAT_SPI, \
        .spi_initstruct.SampleEdge = SPI_SECOND_EDGE, \
        .spi_initstruct.IdleLevel = SPI_HIGH_LEVEL,   \
        .spi_initstruct.WordSize = 8,                 \
        .spi_initstruct.Master = 1,                   \
        .spi_initstruct.RXHFullIEn = 0,               \
        .spi_initstruct.TXEmptyIEn = 0,               \
        .spi_initstruct.TXCompleteIEn = 0,            \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

//cannot be used before completion init
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef *GPIOx, uint32_t n);
int rt_hw_spi_init(void);

#endif /* __DRV_SPI_H__ */
