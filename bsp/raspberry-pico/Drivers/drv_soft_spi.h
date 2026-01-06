/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-02     Chushicheng  the first version
 */
#ifndef DRV_SOFT_SPI_H_
#define DRV_SOFT_SPI_H_

#ifdef BSP_USING_SOFT_SPI
#include <rtdevice.h>
#include <dev_spi_bit_ops.h>

/* pico soft spi config */
struct pico_soft_spi_config
{
    rt_uint8_t sck;
    rt_uint8_t mosi;
    rt_uint8_t miso;
    const char *bus_name;
};

/* pico soft spi dirver */
struct pico_soft_spi
{
    struct rt_spi_bit_obj spi;
    struct pico_soft_spi_config *cfg;
};

#ifdef BSP_USING_SOFT_SPI0
#define SOFT_SPI0_BUS_CONFIG                                \
    {                                                       \
        .sck = BSP_S_SPI0_SCK_PIN,                          \
        .mosi = BSP_S_SPI0_MOSI_PIN,                        \
        .miso = BSP_S_SPI0_MISO_PIN,                        \
        .bus_name = "sspi0",                                \
    }
#endif /* BSP_USING_SOFT_SPI0 */
#ifdef BSP_USING_SOFT_SPI1
#define SOFT_SPI1_BUS_CONFIG                                \
    {                                                       \
        .sck = BSP_S_SPI1_SCK_PIN,                          \
        .mosi = BSP_S_SPI_MOSI_PIN,                        \
        .miso = BSP_S_SPI1_MISO_PIN,                        \
        .bus_name = "sspi1",                                \
    }
#endif /* BSP_USING_SOFT_SPI1 */

rt_err_t rt_hw_softspi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);
int rt_soft_spi_init(void);

#endif /* BSP_USING_SOFT_SPI */
#endif /* __DRV_SOFT_SPI__ */
