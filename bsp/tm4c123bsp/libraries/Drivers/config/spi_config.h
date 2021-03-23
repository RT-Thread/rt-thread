/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SPI0
#ifndef SPI0_BUS_CONFIG
#define SPI0_BUS_CONFIG                             \
    {                                               \
        .base = SSI0_BASE,                          \
        .bus_name = "spi0",                         \
    }
#endif /* SPI0_BUS_CONFIG */
#endif /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                             \
    {                                               \
        .base = SSI1_BASE,                          \
        .bus_name = "spi1",                         \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG                             \
    {                                               \
        .base = SSI2_BASE,                          \
        .bus_name = "spi2",                         \
    }
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
#ifndef SPI3_BUS_CONFIG
#define SPI3_BUS_CONFIG                             \
    {                                               \
        .base = SSI3_BASE,                          \
        .bus_name = "spi3",                         \
    }
#endif /* SPI3_BUS_CONFIG */
#endif /* BSP_USING_SPI3 */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */

/************************** end of file ******************/
