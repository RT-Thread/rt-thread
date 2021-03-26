/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */


#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "rtdevice.h"
#include "drv_dma.h"
#include "board_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SPI1
#define SPI1_BUS_NAME			"spi1"
#define SPI1_BUS_MUTEX_NAME	    "spi1_bus_mutex"
#endif
#ifdef BSP_USING_SPI2
#define SPI2_BUS_NAME			"spi2"
#define SPI2_BUS_MUTEX_NAME	    "spi2_bus_mutex"
#endif
#ifdef BSP_USING_SPI3
#define SPI3_BUS_NAME			"spi3"
#define SPI3_BUS_MUTEX_NAME	    "spi3_bus_mutex"
#endif
#ifdef BSP_USING_SPI4
#define SPI4_BUS_NAME			"spi4"
#define SPI4_BUS_MUTEX_NAME	    "spi4_bus_mutex"
#endif
#ifdef BSP_USING_SPI5
#define SPI4_BUS_NAME			"spi5"
#define SPI4_BUS_MUTEX_NAME	    "spi5_bus_mutex"
#endif
#ifdef BSP_USING_SPI6
#define SPI4_BUS_NAME			"spi6"
#define SPI4_BUS_MUTEX_NAME	    "spi6_bus_mutex"
#endif

#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                             \
    {                                               \
        .Instance = M4_SPI1,                        \
        .bus_name = SPI1_BUS_NAME,                  \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_TX_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI1_TX_DMA_INSTANCE,           \
        .channel = SPI1_TX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI1_SPTI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI1_TX_DMA_IRQn,                \
            .irq_prio = SPI1_TX_DMA_INT_PRIO,       \
            .int_src = SPI1_TX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_SPI1_RX_USING_DMA
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI1_RX_DMA_INSTANCE,           \
        .channel = SPI1_RX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI1_SPRI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI1_RX_DMA_IRQn,                \
            .irq_prio = SPI1_RX_DMA_INT_PRIO,       \
            .int_src = SPI1_RX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG                             \
    {                                               \
        .Instance = M4_SPI2,                        \
        .bus_name = SPI2_BUS_NAME,                  \
    }
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_SPI2_TX_USING_DMA
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI2_TX_DMA_INSTANCE,           \
        .channel = SPI2_TX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI2_SPTI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI2_TX_DMA_IRQn,                \
            .irq_prio = SPI2_TX_DMA_INT_PRIO,       \
            .int_src = SPI2_TX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI2_TX_DMA_CONFIG */
#endif /* BSP_SPI2_TX_USING_DMA */

#ifdef BSP_SPI2_RX_USING_DMA
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI2_RX_DMA_INSTANCE,           \
        .channel = SPI2_RX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI2_SPRI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI2_RX_DMA_IRQn,                \
            .irq_prio = SPI2_RX_DMA_INT_PRIO,       \
            .int_src = SPI2_RX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef BSP_USING_SPI3
#ifndef SPI3_BUS_CONFIG
#define SPI3_BUS_CONFIG                             \
    {                                               \
        .Instance = M4_SPI3,                        \
        .bus_name = SPI3_BUS_NAME,                  \
    }
#endif /* SPI3_BUS_CONFIG */
#endif /* BSP_USING_SPI3 */

#ifdef BSP_SPI3_TX_USING_DMA
#ifndef SPI3_TX_DMA_CONFIG
#define SPI3_TX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI3_TX_DMA_INSTANCE,           \
        .channel = SPI3_TX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI3_SPTI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI3_TX_DMA_IRQn,                \
            .irq_prio = SPI3_TX_DMA_INT_PRIO,       \
            .int_src = SPI3_TX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI3_TX_DMA_CONFIG */
#endif /* BSP_SPI3_TX_USING_DMA */

#ifdef BSP_SPI3_RX_USING_DMA
#ifndef SPI3_RX_DMA_CONFIG
#define SPI3_RX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI3_RX_DMA_INSTANCE,           \
        .channel = SPI3_RX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI3_SPRI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI3_RX_DMA_IRQn,                \
            .irq_prio = SPI3_RX_DMA_INT_PRIO,       \
            .int_src = SPI3_RX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI3_RX_DMA_CONFIG */
#endif /* BSP_SPI3_RX_USING_DMA */

#ifdef BSP_USING_SPI4
#ifndef SPI4_BUS_CONFIG
#define SPI4_BUS_CONFIG                             \
    {                                               \
        .Instance = M4_SPI4,                        \
        .bus_name = SPI4_BUS_NAME,                  \
    }
#endif /* SPI4_BUS_CONFIG */
#endif /* BSP_USING_SPI4 */

#ifdef BSP_SPI4_TX_USING_DMA
#ifndef SPI4_TX_DMA_CONFIG
#define SPI4_TX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI4_TX_DMA_INSTANCE,           \
        .channel = SPI4_TX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI4_SPTI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI4_TX_DMA_IRQn,                \
            .irq_prio = SPI4_TX_DMA_INT_PRIO,       \
            .int_src = SPI4_TX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI4_TX_DMA_CONFIG */
#endif /* BSP_SPI4_TX_USING_DMA */

#ifdef BSP_SPI4_RX_USING_DMA
#ifndef SPI4_RX_DMA_CONFIG
#define SPI4_RX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI4_RX_DMA_INSTANCE,           \
        .channel = SPI4_RX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI4_SPRI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI4_RX_DMA_IRQn,                \
            .irq_prio = SPI4_RX_DMA_INT_PRIO,       \
            .int_src = SPI4_RX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI4_RX_DMA_CONFIG */
#endif /* BSP_SPI4_RX_USING_DMA */

#ifdef BSP_USING_SPI5
#ifndef SPI5_BUS_CONFIG
#define SPI5_BUS_CONFIG                             \
    {                                               \
        .Instance = M4_SPI5,                        \
        .bus_name = SPI5_BUS_NAME,                  \
    }
#endif /* SPI5_BUS_CONFIG */
#endif /* BSP_USING_SPI5 */

#ifdef BSP_SPI5_TX_USING_DMA
#ifndef SPI5_TX_DMA_CONFIG
#define SPI5_TX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI5_TX_DMA_INSTANCE,           \
        .channel = SPI5_TX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI5_SPTI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI5_TX_DMA_IRQn,                \
            .irq_prio = SPI5_TX_DMA_INT_PRIO,       \
            .int_src = SPI5_TX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI5_TX_DMA_CONFIG */
#endif /* BSP_SPI5_TX_USING_DMA */

#ifdef BSP_SPI5_RX_USING_DMA
#ifndef SPI5_RX_DMA_CONFIG
#define SPI5_RX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI5_RX_DMA_INSTANCE,           \
        .channel = SPI5_RX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI5_SPRI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI5_RX_DMA_IRQn,                \
            .irq_prio = SPI5_RX_DMA_INT_PRIO,       \
            .int_src = SPI5_RX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI5_RX_DMA_CONFIG */
#endif /* BSP_SPI5_RX_USING_DMA */

#ifdef BSP_USING_SPI6
#ifndef SPI6_BUS_CONFIG
#define SPI6_BUS_CONFIG                             \
    {                                               \
        .Instance = M4_SPI6,                        \
        .bus_name = SPI6_BUS_NAME,                  \
    }
#endif /* SPI6_BUS_CONFIG */
#endif /* BSP_USING_SPI6 */

#ifdef BSP_SPI6_TX_USING_DMA
#ifndef SPI6_TX_DMA_CONFIG
#define SPI6_TX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI6_TX_DMA_INSTANCE,           \
        .channel = SPI6_TX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI6_SPTI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI6_TX_DMA_IRQn,                \
            .irq_prio = SPI6_TX_DMA_INT_PRIO,       \
            .int_src = SPI6_TX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI6_TX_DMA_CONFIG */
#endif /* BSP_SPI6_TX_USING_DMA */

#ifdef BSP_SPI6_RX_USING_DMA
#ifndef SPI6_RX_DMA_CONFIG
#define SPI6_RX_DMA_CONFIG                          \
    {                                               \
        .Instance = SPI6_RX_DMA_INSTANCE,           \
        .channel = SPI6_RX_DMA_CHANNEL,             \
        .trigger_evt_src = EVT_SPI6_SPRI,           \
        .irq_config =                               \
        {                                           \
            .irq = SPI6_RX_DMA_IRQn,                \
            .irq_prio = SPI6_RX_DMA_INT_PRIO,       \
            .int_src = SPI6_RX_DMA_INT_SRC,         \
        }                                           \
    }
#endif /* SPI6_RX_DMA_CONFIG */
#endif /* BSP_SPI6_RX_USING_DMA */

typedef struct __SPI_HandleType
{
    M4_SPI_TypeDef *Instance;    /* SPI registers base address */
    stc_spi_init_t Init;         /* SPI communication parameters */
}SPI_HandleType;

struct hc32_hw_spi_cs
{
    rt_uint8_t  port;
    rt_uint16_t pin;
};

struct hc32_spi_config
{
    M4_SPI_TypeDef    *Instance;
    char              *bus_name;
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
};

struct stm32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};

/* HC32 SPI index */
struct spi_index
{
    rt_uint32_t      index;
    M4_SPI_TypeDef   *Instance;
};

struct hc32_spi
{
    struct rt_spi_bus           spi_bus;
    SPI_HandleType              handle;
    struct hc32_spi_config      *config;
    struct rt_spi_configuration *cfg;
    rt_uint16_t                 spi_dma_flag;
};

/* HC32 SPI irq handler */
struct spi_irq_handler
{
    void (*rx_dma_irq_handler)(void);
    void (*tx_dma_irq_handler)(void);
};

rt_err_t hc32_hw_spi_device_attach(const char *bus_name,
                                   const char *device_name,
                                   uint8_t    cs_gpio_port,
                                   uint16_t   cs_gpio_pin);


#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */

