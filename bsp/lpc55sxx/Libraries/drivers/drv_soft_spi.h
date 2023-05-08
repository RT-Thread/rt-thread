/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-14     Wangyuqiang  the first version
 */

#ifndef DRV_SOFT_SPI_H_
#define DRV_SOFT_SPI_H_

#include <rthw.h>
#include <rtdevice.h>
#include <spi-bit-ops.h>
#include <drv_pin.h>

/* Notice: PIO1_11(sck) --> 93; PIO0_15(miso) --> 22; PIO1_8(mosi) --> 24 */

#define BSP_S_SPI1_SCK_PIN  GET_PINS(1,11)
#define BSP_S_SPI1_MISO_PIN GET_PINS(0,15)
#define BSP_S_SPI1_MOSI_PIN GET_PINS(1,8)

/* Notice: PIO1_9(sck) --> 10; PIO0_18(miso) --> 56; PIO1_10(mosi) --> 40 */

#define BSP_S_SPI2_SCK_PIN  GET_PINS(1,9)
#define BSP_S_SPI2_MISO_PIN GET_PINS(0,18)
#define BSP_S_SPI2_MOSI_PIN GET_PINS(1,10)

/* lpc soft spi config */
struct lpc_soft_spi_config
{
    rt_uint8_t sck;
    rt_uint8_t mosi;
    rt_uint8_t miso;
    const char *bus_name;
};

/* lpc soft spi dirver */
struct lpc_soft_spi
{
    struct rt_spi_bit_obj spi;
    struct lpc_soft_spi_config *cfg;
};

#ifdef BSP_USING_SOFT_SPI1
#define SOFT_SPI1_BUS_CONFIG                                \
    {                                                       \
        .sck = BSP_S_SPI1_SCK_PIN,                          \
        .mosi = BSP_S_SPI1_MOSI_PIN,                        \
        .miso = BSP_S_SPI1_MISO_PIN,                        \
        .bus_name = "sspi1",                                \
    }
#endif /* BSP_USING_SOFT_SPI1 */
#ifdef BSP_USING_SOFT_SPI2
#define SOFT_SPI2_BUS_CONFIG                                \
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
