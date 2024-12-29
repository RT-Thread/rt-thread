/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __DEV_SPI_DM_H__
#define __DEV_SPI_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_OFW
rt_err_t spi_device_ofw_parse(struct rt_spi_device *spi_dev);
#else
rt_inline rt_err_t spi_device_ofw_parse(struct rt_spi_device *spi_dev)
{
    return RT_EOK;
}
#endif /* RT_USING_OFW */

void spi_bus_scan_devices(struct rt_spi_bus *bus);

#endif /* __DEV_SPI_DM_H__ */
