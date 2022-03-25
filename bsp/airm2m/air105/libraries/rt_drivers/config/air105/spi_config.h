/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */


#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HSPI0                      0
#define SPI0                       1
#define SPI1                       2
#define SPI2                       3
#define SPI0S                      4

#ifdef BSP_USING_HSPI0
#ifndef HSPI0_BUS_CONFIG
#define HSPI0_BUS_CONFIG                            \
    {                                               \
        .bus_name = "hspi0",                        \
        .id = HSPI0,                                \
    }
#endif /* HSPI0_BUS_CONFIG */
#endif /* BSP_USING_HSPI0 */

#ifdef BSP_USING_SPI0
#ifndef SPI0_BUS_CONFIG
#define SPI0_BUS_CONFIG                             \
    {                                               \
        .bus_name = "spi0",                         \
        .id = SPI0,                                 \
    }
#endif /* SPI0_BUS_CONFIG */
#endif /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                             \
    {                                               \
        .bus_name = "spi1",                         \
        .id = SPI1,                                 \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG                             \
    {                                               \
        .bus_name = "spi2",                         \
        .id = SPI2,                                 \
    }
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI0S
#ifndef SPI0S_BUS_CONFIG
#define SPI0S_BUS_CONFIG                            \
    {                                               \
        .bus_name = "spi0s",                        \
        .id = SPI0S,                                \
    }
#endif /* SPI0S_BUS_CONFIG */
#endif /* BSP_USING_SPI0S */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */
