/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */


#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct air_spi
{
    const char bus_name[RT_NAME_MAX];
    rt_uint8_t          id;
    struct rt_spi_bus   bus;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint8_t cs_pin);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_SPI_H__ */
