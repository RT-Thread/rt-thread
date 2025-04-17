/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-14      solar        first version
 */

#ifndef __DRV_SOFT_SPI__
#define __DRV_SOFT_SPI__

#include <rthw.h>
#include <rtdevice.h>
#include <dev_spi_bit_ops.h>

/* stm32 soft spi config */
struct stm32_soft_spi_config
{
    rt_uint8_t sck;
    rt_uint8_t mosi;
    rt_uint8_t miso;
    const char *bus_name;
};

/* stm32 soft spi dirver */
struct stm32_soft_spi
{
    struct rt_spi_bit_obj spi;
    struct rt_spi_bit_ops ops;
    struct stm32_soft_spi_config *cfg;
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

rt_err_t rt_hw_softspi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);
int rt_soft_spi_init(void);

#endif /* __DRV_SOFT_SPI__ */
