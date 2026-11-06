/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SPI0
#ifndef BSP_SPI0_SCK_PIN
#define BSP_SPI0_SCK_PIN       "PA5"
#endif
#ifndef BSP_SPI0_MISO_PIN
#define BSP_SPI0_MISO_PIN      "PA6"
#endif
#ifndef BSP_SPI0_MOSI_PIN
#define BSP_SPI0_MOSI_PIN      "PA7"
#endif
#ifndef BSP_SPI0_SCK_AFIO
#ifdef SOC_SERIES_GD32E23x
#define BSP_SPI0_SCK_AFIO      "AF0"
#else
#define BSP_SPI0_SCK_AFIO      "AF5"
#endif
#endif
#ifndef BSP_SPI0_MISO_AFIO
#ifdef SOC_SERIES_GD32E23x
#define BSP_SPI0_MISO_AFIO     "AF0"
#else
#define BSP_SPI0_MISO_AFIO     "AF5"
#endif
#endif
#ifndef BSP_SPI0_MOSI_AFIO
#ifdef SOC_SERIES_GD32E23x
#define BSP_SPI0_MOSI_AFIO     "AF0"
#else
#define BSP_SPI0_MOSI_AFIO     "AF5"
#endif
#endif
#ifndef SPI0_BUS_CONFIG
#define SPI0_BUS_CONFIG                                      \
    {                                                        \
        .spi_periph = SPI0,                                  \
        .bus_name = "spi0",                                  \
        .spi_clk = RCU_SPI0,                                 \
        .spi_bus = &spi_bus0,                                \
        .sck_pin_name = BSP_SPI0_SCK_PIN,                    \
        .miso_pin_name = BSP_SPI0_MISO_PIN,                  \
        .mosi_pin_name = BSP_SPI0_MOSI_PIN,                  \
        .sck_alternate = BSP_SPI0_SCK_AFIO,                  \
        .miso_alternate = BSP_SPI0_MISO_AFIO,                \
        .mosi_alternate = BSP_SPI0_MOSI_AFIO,                \
    }
#endif
#endif

#ifdef BSP_USING_SPI1
#ifndef BSP_SPI1_SCK_PIN
#define BSP_SPI1_SCK_PIN       "PB13"
#endif
#ifndef BSP_SPI1_MISO_PIN
#define BSP_SPI1_MISO_PIN      "PB14"
#endif
#ifndef BSP_SPI1_MOSI_PIN
#define BSP_SPI1_MOSI_PIN      "PB15"
#endif
#ifndef BSP_SPI1_SCK_AFIO
#ifdef SOC_SERIES_GD32E23x
#define BSP_SPI1_SCK_AFIO      "AF0"
#else
#define BSP_SPI1_SCK_AFIO      "AF5"
#endif
#endif
#ifndef BSP_SPI1_MISO_AFIO
#ifdef SOC_SERIES_GD32E23x
#define BSP_SPI1_MISO_AFIO     "AF0"
#else
#define BSP_SPI1_MISO_AFIO     "AF5"
#endif
#endif
#ifndef BSP_SPI1_MOSI_AFIO
#ifdef SOC_SERIES_GD32E23x
#define BSP_SPI1_MOSI_AFIO     "AF0"
#else
#define BSP_SPI1_MOSI_AFIO     "AF5"
#endif
#endif
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                                      \
    {                                                        \
        .spi_periph = SPI1,                                  \
        .bus_name = "spi1",                                  \
        .spi_clk = RCU_SPI1,                                 \
        .spi_bus = &spi_bus1,                                \
        .sck_pin_name = BSP_SPI1_SCK_PIN,                    \
        .miso_pin_name = BSP_SPI1_MISO_PIN,                  \
        .mosi_pin_name = BSP_SPI1_MOSI_PIN,                  \
        .sck_alternate = BSP_SPI1_SCK_AFIO,                  \
        .miso_alternate = BSP_SPI1_MISO_AFIO,                \
        .mosi_alternate = BSP_SPI1_MOSI_AFIO,                \
    }
#endif
#endif

#ifdef BSP_USING_SPI2
#ifndef BSP_SPI2_SCK_PIN
#define BSP_SPI2_SCK_PIN       "PB3"
#endif
#ifndef BSP_SPI2_MISO_PIN
#define BSP_SPI2_MISO_PIN      "PB4"
#endif
#ifndef BSP_SPI2_MOSI_PIN
#define BSP_SPI2_MOSI_PIN      "PB5"
#endif
#ifndef BSP_SPI2_SCK_AFIO
#define BSP_SPI2_SCK_AFIO      "AF6"
#endif
#ifndef BSP_SPI2_MISO_AFIO
#define BSP_SPI2_MISO_AFIO     "AF6"
#endif
#ifndef BSP_SPI2_MOSI_AFIO
#define BSP_SPI2_MOSI_AFIO     "AF6"
#endif
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG                                      \
    {                                                        \
        .spi_periph = SPI2,                                  \
        .bus_name = "spi2",                                  \
        .spi_clk = RCU_SPI2,                                 \
        .spi_bus = &spi_bus2,                                \
        .sck_pin_name = BSP_SPI2_SCK_PIN,                    \
        .miso_pin_name = BSP_SPI2_MISO_PIN,                  \
        .mosi_pin_name = BSP_SPI2_MOSI_PIN,                  \
        .sck_alternate = BSP_SPI2_SCK_AFIO,                  \
        .miso_alternate = BSP_SPI2_MISO_AFIO,                \
        .mosi_alternate = BSP_SPI2_MOSI_AFIO,                \
    }
#endif
#endif

#ifdef BSP_USING_SPI3
#ifndef BSP_SPI3_SCK_PIN
#define BSP_SPI3_SCK_PIN       "PE2"
#endif
#ifndef BSP_SPI3_MISO_PIN
#define BSP_SPI3_MISO_PIN      "PE5"
#endif
#ifndef BSP_SPI3_MOSI_PIN
#define BSP_SPI3_MOSI_PIN      "PE6"
#endif
#ifndef BSP_SPI3_SCK_AFIO
#define BSP_SPI3_SCK_AFIO      "AF5"
#endif
#ifndef BSP_SPI3_MISO_AFIO
#define BSP_SPI3_MISO_AFIO     "AF5"
#endif
#ifndef BSP_SPI3_MOSI_AFIO
#define BSP_SPI3_MOSI_AFIO     "AF5"
#endif
#ifndef SPI3_BUS_CONFIG
#define SPI3_BUS_CONFIG                                      \
    {                                                        \
        .spi_periph = SPI3,                                  \
        .bus_name = "spi3",                                  \
        .spi_clk = RCU_SPI3,                                 \
        .spi_bus = &spi_bus3,                                \
        .sck_pin_name = BSP_SPI3_SCK_PIN,                    \
        .miso_pin_name = BSP_SPI3_MISO_PIN,                  \
        .mosi_pin_name = BSP_SPI3_MOSI_PIN,                  \
        .sck_alternate = BSP_SPI3_SCK_AFIO,                  \
        .miso_alternate = BSP_SPI3_MISO_AFIO,                \
        .mosi_alternate = BSP_SPI3_MOSI_AFIO,                \
    }
#endif
#endif

#ifdef BSP_USING_SPI4
#ifndef BSP_SPI4_SCK_PIN
#define BSP_SPI4_SCK_PIN       "PF7"
#endif
#ifndef BSP_SPI4_MISO_PIN
#define BSP_SPI4_MISO_PIN      "PF8"
#endif
#ifndef BSP_SPI4_MOSI_PIN
#define BSP_SPI4_MOSI_PIN      "PF9"
#endif
#ifndef BSP_SPI4_SCK_AFIO
#define BSP_SPI4_SCK_AFIO      "AF5"
#endif
#ifndef BSP_SPI4_MISO_AFIO
#define BSP_SPI4_MISO_AFIO     "AF5"
#endif
#ifndef BSP_SPI4_MOSI_AFIO
#define BSP_SPI4_MOSI_AFIO     "AF5"
#endif
#ifndef SPI4_BUS_CONFIG
#define SPI4_BUS_CONFIG                                      \
    {                                                        \
        .spi_periph = SPI4,                                  \
        .bus_name = "spi4",                                  \
        .spi_clk = RCU_SPI4,                                 \
        .spi_bus = &spi_bus4,                                \
        .sck_pin_name = BSP_SPI4_SCK_PIN,                    \
        .miso_pin_name = BSP_SPI4_MISO_PIN,                  \
        .mosi_pin_name = BSP_SPI4_MOSI_PIN,                  \
        .sck_alternate = BSP_SPI4_SCK_AFIO,                  \
        .miso_alternate = BSP_SPI4_MISO_AFIO,                \
        .mosi_alternate = BSP_SPI4_MOSI_AFIO,                \
    }
#endif
#endif

#ifdef BSP_USING_SPI5
#ifndef BSP_SPI5_SCK_PIN
#define BSP_SPI5_SCK_PIN       "PG13"
#endif
#ifndef BSP_SPI5_MISO_PIN
#define BSP_SPI5_MISO_PIN      "PG12"
#endif
#ifndef BSP_SPI5_MOSI_PIN
#define BSP_SPI5_MOSI_PIN      "PG14"
#endif
#ifndef BSP_SPI5_SCK_AFIO
#define BSP_SPI5_SCK_AFIO      "AF5"
#endif
#ifndef BSP_SPI5_MISO_AFIO
#define BSP_SPI5_MISO_AFIO     "AF5"
#endif
#ifndef BSP_SPI5_MOSI_AFIO
#define BSP_SPI5_MOSI_AFIO     "AF5"
#endif
#ifndef SPI5_BUS_CONFIG
#define SPI5_BUS_CONFIG                                      \
    {                                                        \
        .spi_periph = SPI5,                                  \
        .bus_name = "spi5",                                  \
        .spi_clk = RCU_SPI5,                                 \
        .spi_bus = &spi_bus5,                                \
        .sck_pin_name = BSP_SPI5_SCK_PIN,                    \
        .miso_pin_name = BSP_SPI5_MISO_PIN,                  \
        .mosi_pin_name = BSP_SPI5_MOSI_PIN,                  \
        .sck_alternate = BSP_SPI5_SCK_AFIO,                  \
        .miso_alternate = BSP_SPI5_MISO_AFIO,                \
        .mosi_alternate = BSP_SPI5_MOSI_AFIO,                \
    }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SPI_CONFIG_H__ */
