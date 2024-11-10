/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     wumingzi      first implementation
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "driver/spi_common.h" /*bsp/ESP32_C3/packages/ESP-IDF-latest/components/driver/include/driver/spi_common.h*/
#ifdef __cplusplus
extern "C" {
#endif

/* esp32 spi dirver class */
struct esp32_spi
{
    char *bus_name;
    struct rt_spi_bus *spi_bus;
    spi_bus_config_t* esp32_spi_bus_cfg;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */
