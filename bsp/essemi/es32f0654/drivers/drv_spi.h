/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-24     wangyq        the first version
 */

#ifndef DRV_SPI_H__
#define DRV_SPI_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

struct es32f0_hw_spi_cs
{
    rt_uint32_t pin;
};

/* cannot be used before completion init */
rt_err_t es32f0_spi_device_attach(rt_uint32_t pin, const char *bus_name, const char *device_name);
int rt_hw_spi_init(void);

#endif
