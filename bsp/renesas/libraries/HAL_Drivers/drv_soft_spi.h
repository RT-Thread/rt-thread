/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-14     Wangyuqiang  the first version
 */

#ifndef __DRV_SOFT_SPI__
#define __DRV_SOFT_SPI__

#include <rthw.h>
#include <rtdevice.h>
#include <spi-bit-ops.h>

/* ra soft spi config */
struct ra_soft_spi_config
{
    rt_base_t sck;
    rt_base_t mosi;
    rt_base_t miso;
    const char *bus_name;
};

/* ra soft spi dirver */
struct ra_soft_spi
{
    struct rt_spi_bit_obj spi;
    struct rt_spi_bit_ops ops;
    struct ra_soft_spi_config *cfg;
};

#ifdef BSP_USING_SOFT_SPI1
#define SOFT_SPI1_BUS_CONFIG                                    \
    {                                                       \
        .sck = BSP_S_SPI1_SCK_PIN,                          \
        .mosi = BSP_S_SPI1_MOSI_PIN,                        \
        .miso = BSP_S_SPI1_MISO_PIN,                        \
        .bus_name = "sspi1",                                \
    }
#endif /* BSP_USING_SOFT_SPI1 */
#ifdef BSP_USING_SOFT_SPI2
#define SOFT_SPI2_BUS_CONFIG                                    \
    {                                                       \
        .sck = BSP_S_SPI2_SCK_PIN,                          \
        .mosi = BSP_S_SPI2_MOSI_PIN,                        \
        .miso = BSP_S_SPI2_MISO_PIN,                        \
        .bus_name = "sspi2",                                \
    }
#endif /* BSP_USING_SOFT_SPI2 */

rt_err_t rt_soft_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);
int rt_soft_spi_init(void);

#endif /* __DRV_SOFT_SPI__ */
