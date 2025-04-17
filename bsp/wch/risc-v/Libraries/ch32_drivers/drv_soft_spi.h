/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-01     zhs          the first version which add from wch
 */
#ifndef LIBRARIES_HAL_DRIVERS_DRV_SOFT_SPI_H_
#define LIBRARIES_HAL_DRIVERS_DRV_SOFT_SPI_H_

#include <rthw.h>
#include <rtdevice.h>
#include <dev_spi_bit_ops.h>

/* ch32 soft spi config */
struct ch32_soft_spi_config
{
    rt_uint8_t sck;
    rt_uint8_t mosi;
    rt_uint8_t miso;
    const char *bus_name;
};

/* ch32 soft spi dirver */
struct ch32_soft_spi
{
    struct rt_spi_bit_obj spi;
    struct ch32_soft_spi_config *cfg;
};

#ifdef BSP_USING_SOFT_SPI1
#define SOFT_SPI1_BUS_CONFIG                            \
{                                                       \
    .sck = BSP_S_SPI1_SCK_PIN,                          \
    .mosi = BSP_S_SPI1_MOSI_PIN,                        \
    .miso = BSP_S_SPI1_MISO_PIN,                        \
    .bus_name = "sspi1",                                \
}
#endif /* BSP_USING_SOFT_SPI1 */
#ifdef BSP_USING_SOFT_SPI2
#define SOFT_SPI2_BUS_CONFIG                            \
{                                                       \
    .sck = BSP_S_SPI2_SCK_PIN,                          \
    .mosi = BSP_S_SPI2_MOSI_PIN,                        \
    .miso = BSP_S_SPI2_MISO_PIN,                        \
    .bus_name = "sspi2",                                \
}
#endif /* BSP_USING_SOFT_SPI2 */

rt_err_t rt_hw_soft_spi_device_attach(const char *bus_name, const char *device_name, const char *pin_name);
int rt_soft_spi_init(void);

#endif /* __DRV_SOFT_SPI__ */

