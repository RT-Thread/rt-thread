/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     Mr.Tiger   first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "hal_data.h"
#include "board.h"
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef R_SPI_H
struct ra_spi_handle
{
    const char bus_name[RT_NAME_MAX];
    const spi_cfg_t           *spi_cfg_t;
    const spi_instance_ctrl_t *spi_ctrl_t;
};

struct ra_spi
{
    rt_uint32_t                  cs_pin;
    struct ra_spi_handle        *ra_spi_handle_t;
    struct rt_spi_configuration *rt_spi_cfg_t;
    struct rt_spi_bus            bus;
};
#endif

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#ifdef __cplusplus
}
#endif

/* stm32 spi dirver class */

#endif /*__DRV_SPI_H__ */
