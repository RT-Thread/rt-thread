/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-02     勤为本       first version
 */

#ifndef LS1C_DRV_SPI_H
#define LS1C_DRV_SPI_H


#include "../libraries/ls1c_spi.h"


struct ls1c_spi
{
    unsigned char SPIx;     // LS1C_SPI_0 or LS1C_SPI_1
};


struct ls1c_spi_cs
{
    unsigned char cs;       // LS1C_SPI_CS_0, LS1C_SPI_CS_1, LS1C_SPI_CS_2 or LS1C_SPI_CS_3
};



/*
 * 初始化并注册龙芯1c的spi总线
 * @SPI SPI总线，比如LS1C_SPI_0， LS1C_SPI_1
 * @spi_bus_name 总线名字
 * @ret
 */
rt_err_t ls1c_spi_bus_register(rt_uint8_t SPI, const char *spi_bus_name);


#endif

