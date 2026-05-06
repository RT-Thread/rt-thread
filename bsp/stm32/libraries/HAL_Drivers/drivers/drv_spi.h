/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 * 2026-04-16     wdfk-prog    Add SPI interrupt transfer mode scaffolding
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"
#include <ipc/completion.h>

/* hardware bus */
#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || defined(BSP_USING_SPI4) || defined(BSP_USING_SPI5) || defined(BSP_USING_SPI6)
#define BSP_HARDWARE_SPI
#endif

/* POLL configuration visibility */
#if defined(BSP_SPI1_TX_USING_POLL) || defined(BSP_SPI2_TX_USING_POLL) || defined(BSP_SPI3_TX_USING_POLL) || defined(BSP_SPI4_TX_USING_POLL) || defined(BSP_SPI5_TX_USING_POLL) || defined(BSP_SPI6_TX_USING_POLL)
#define BSP_SPI_TX_USING_POLL
#endif

#if defined(BSP_SPI1_RX_USING_POLL) || defined(BSP_SPI2_RX_USING_POLL) || defined(BSP_SPI3_RX_USING_POLL) || defined(BSP_SPI4_RX_USING_POLL) || defined(BSP_SPI5_RX_USING_POLL) || defined(BSP_SPI6_RX_USING_POLL)
#define BSP_SPI_RX_USING_POLL
#endif

#if defined(BSP_SPI1_TX_USING_POLL) || defined(BSP_SPI1_RX_USING_POLL)
#define BSP_SPI1_USING_POLL
#endif

#if defined(BSP_SPI2_TX_USING_POLL) || defined(BSP_SPI2_RX_USING_POLL)
#define BSP_SPI2_USING_POLL
#endif

#if defined(BSP_SPI3_TX_USING_POLL) || defined(BSP_SPI3_RX_USING_POLL)
#define BSP_SPI3_USING_POLL
#endif

#if defined(BSP_SPI4_TX_USING_POLL) || defined(BSP_SPI4_RX_USING_POLL)
#define BSP_SPI4_USING_POLL
#endif

#if defined(BSP_SPI5_TX_USING_POLL) || defined(BSP_SPI5_RX_USING_POLL)
#define BSP_SPI5_USING_POLL
#endif

#if defined(BSP_SPI6_TX_USING_POLL) || defined(BSP_SPI6_RX_USING_POLL)
#define BSP_SPI6_USING_POLL
#endif

#if defined(BSP_SPI_TX_USING_POLL) || defined(BSP_SPI_RX_USING_POLL)
#define BSP_SPI_USING_POLL
#endif

/* DMA */
#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI3_TX_USING_DMA) || defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI6_TX_USING_DMA)
#define BSP_SPI_TX_USING_DMA
#endif

#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA) || defined(BSP_SPI3_RX_USING_DMA) || defined(BSP_SPI4_RX_USING_DMA) || defined(BSP_SPI5_RX_USING_DMA) || defined(BSP_SPI6_RX_USING_DMA)
#define BSP_SPI_RX_USING_DMA
#endif

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA)
#define BSP_SPI1_USING_DMA
#endif

#if defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
#define BSP_SPI2_USING_DMA
#endif

#if defined(BSP_SPI3_TX_USING_DMA) || defined(BSP_SPI3_RX_USING_DMA)
#define BSP_SPI3_USING_DMA
#endif

#if defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI4_RX_USING_DMA)
#define BSP_SPI4_USING_DMA
#endif

#if defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI5_RX_USING_DMA)
#define BSP_SPI5_USING_DMA
#endif

#if defined(BSP_SPI6_TX_USING_DMA) || defined(BSP_SPI6_RX_USING_DMA)
#define BSP_SPI6_USING_DMA
#endif

#if defined(BSP_SPI_TX_USING_DMA) || defined(BSP_SPI_RX_USING_DMA)
#define BSP_SPI_USING_DMA
#endif

/* INT */
#if defined(BSP_SPI1_TX_USING_INT) || defined(BSP_SPI2_TX_USING_INT) || defined(BSP_SPI3_TX_USING_INT) || defined(BSP_SPI4_TX_USING_INT) || defined(BSP_SPI5_TX_USING_INT) || defined(BSP_SPI6_TX_USING_INT)
#define BSP_SPI_TX_USING_INT
#endif

#if defined(BSP_SPI1_RX_USING_INT) || defined(BSP_SPI2_RX_USING_INT) || defined(BSP_SPI3_RX_USING_INT) || defined(BSP_SPI4_RX_USING_INT) || defined(BSP_SPI5_RX_USING_INT) || defined(BSP_SPI6_RX_USING_INT)
#define BSP_SPI_RX_USING_INT
#endif

#if defined(BSP_SPI1_TX_USING_INT) || defined(BSP_SPI1_RX_USING_INT)
#define BSP_SPI1_USING_INT
#endif

#if defined(BSP_SPI2_TX_USING_INT) || defined(BSP_SPI2_RX_USING_INT)
#define BSP_SPI2_USING_INT
#endif

#if defined(BSP_SPI3_TX_USING_INT) || defined(BSP_SPI3_RX_USING_INT)
#define BSP_SPI3_USING_INT
#endif

#if defined(BSP_SPI4_TX_USING_INT) || defined(BSP_SPI4_RX_USING_INT)
#define BSP_SPI4_USING_INT
#endif

#if defined(BSP_SPI5_TX_USING_INT) || defined(BSP_SPI5_RX_USING_INT)
#define BSP_SPI5_USING_INT
#endif

#if defined(BSP_SPI6_TX_USING_INT) || defined(BSP_SPI6_RX_USING_INT)
#define BSP_SPI6_USING_INT
#endif

#if defined(BSP_SPI_TX_USING_INT) || defined(BSP_SPI_RX_USING_INT)
#define BSP_SPI_USING_INT
#endif

#if defined(BSP_SPI1_USING_DMA) || defined(BSP_SPI1_USING_INT)
#define BSP_SPI1_USING_IRQ
#endif

#if defined(BSP_SPI2_USING_DMA) || defined(BSP_SPI2_USING_INT)
#define BSP_SPI2_USING_IRQ
#endif

#if defined(BSP_SPI3_USING_DMA) || defined(BSP_SPI3_USING_INT)
#define BSP_SPI3_USING_IRQ
#endif

#if defined(BSP_SPI4_USING_DMA) || defined(BSP_SPI4_USING_INT)
#define BSP_SPI4_USING_IRQ
#endif

#if defined(BSP_SPI5_USING_DMA) || defined(BSP_SPI5_USING_INT)
#define BSP_SPI5_USING_IRQ
#endif

#if defined(BSP_SPI6_USING_DMA) || defined(BSP_SPI6_USING_INT)
#define BSP_SPI6_USING_IRQ
#endif

#if defined(BSP_SPI_USING_DMA) || defined(BSP_SPI_USING_INT)
#define BSP_SPI_USING_IRQ
#endif


#ifdef __cplusplus
extern "C" {
#endif

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);
rt_err_t rt_hw_spi_device_detach(const char *device_name);

#ifdef __cplusplus
}
#endif

struct stm32_spi_config
{
    SPI_TypeDef *Instance;
    char *bus_name;
    IRQn_Type irq_type;
#ifdef BSP_SPI_RX_USING_DMA
    const struct stm32_dma_config *dma_rx;
#endif /* BSP_SPI_RX_USING_DMA */
#ifdef BSP_SPI_TX_USING_DMA
    const struct stm32_dma_config *dma_tx;
#endif /* BSP_SPI_TX_USING_DMA */
};

struct stm32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};

/* stm32 spi dirver class */
struct stm32_spi
{
    SPI_HandleTypeDef handle;
    struct stm32_spi_config *config;
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus spi_bus;
    rt_uint16_t spi_dma_flag;
#ifdef BSP_SPI_USING_IRQ
    struct rt_completion cpt;
#endif /* BSP_SPI_USING_IRQ */
#ifdef BSP_SPI_USING_DMA
    struct
    {
#ifdef BSP_SPI_RX_USING_DMA
        DMA_HandleTypeDef handle_rx;
#endif /* BSP_SPI_RX_USING_DMA */
#ifdef BSP_SPI_TX_USING_DMA
        DMA_HandleTypeDef handle_tx;
#endif /* BSP_SPI_TX_USING_DMA */
    } dma;
#endif /* BSP_SPI_USING_DMA */
};

#endif /*__DRV_SPI_H__ */
