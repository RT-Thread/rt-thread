/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 */

#ifndef DRV_SPI_H__
#define DRV_SPI_H__

#include <rtthread.h>

struct swm320_spi_cs
{
    rt_uint32_t pin;
};

//cannot be used before completion init
static rt_err_t swm320_spi_bus_attach_device(rt_uint32_t pin,
        const char *bus_name,
        const char *device_name);
int rt_hw_spi_init(void);

#endif
