/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#ifndef __SPI_H_
#define __SPI_H_

#include <rtthread.h>

/* 片选信号结构声明 */
struct am_spi_cs
{
    rt_uint32_t chip_select;
};

/**
 * @brief External function definitions
 *
 */
int yr_hw_spi_init(void);

#endif // __SPI_H_
