/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author          Notes
 * 2021-02-14       supperthomas    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include "spi.h"

#ifndef __DRV_SPI_H_
#define __DRV_SPI_H_

/**
 * @brief Attach the spi device to SPI bus, this function must be used after initialization.
 * @param bus_name     spi bus name  "spi0"/"spi1"/"spi2"
 * @param device_name  spi device name "spi0x"/"spi1x"/"spi2x"
 * @param ss_pin       spi ss pin number
 * @retval  -RT_ERROR / RT_EOK
*/
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t ss_pin);

//SPI bus config
#ifdef BSP_USING_SPI0
#define MCU_SPI0_CONFIG          \
{                                \
    .bus_name = "spi0",          \
    .spi_instance = SPI0A,       \
}
#endif
#ifdef BSP_USING_SPI1
#ifdef BSP_USING_SPI1A  //The SPI1A is conflit with UART1 TX RX P0.10 P0.11
#define MCU_SPI1_CONFIG          \
{                                \
    .bus_name = "spi1",          \
    .spi_instance = SPI1A        \
}
#else
#define MCU_SPI1_CONFIG          \
{                                \
    .bus_name = "spi1",          \
    .spi_instance = SPI1B        \
}
#endif
#endif

struct mcu_drv_spi_config
{
    char *bus_name;
    spi_type spi_instance;
};

struct mcu_drv_spi
{
    spi_type spi_instance;
    spi_req_t spixfer_req;
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus spi_bus;
};

#endif  /*__DRV_SPI_H_*/
