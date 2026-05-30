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

/**
 * @file drv_spi.h
 * @brief STM32 SPI bus driver private definitions.
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"
#include <ipc/completion.h>

/* Enable STM32 hardware SPI driver code when any SPI instance is selected. */
#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || defined(BSP_USING_SPI4) || defined(BSP_USING_SPI5) || defined(BSP_USING_SPI6)
#define BSP_HARDWARE_SPI
#endif

/* Aggregate polling transfer configuration from per-instance Kconfig macros. */
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

/* Aggregate DMA transfer configuration from per-instance Kconfig macros. */
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

/* Aggregate interrupt transfer configuration from per-instance Kconfig macros. */
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

/* Aggregate IRQ requirements from DMA and interrupt transfer modes. */
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

/**
 * @brief Attach an SPI device to a registered STM32 SPI bus.
 *
 * @param bus_name SPI bus name, such as "spi1".
 * @param device_name SPI device name to register.
 * @param cs_pin Chip-select pin used by the SPI device.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

/**
 * @brief Detach a previously attached STM32 SPI device.
 *
 * @param device_name SPI device name to detach.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
rt_err_t rt_hw_spi_device_detach(const char *device_name);

#ifdef __cplusplus
}
#endif

/**
 * @brief Static configuration for one STM32 SPI bus instance.
 */
struct stm32_spi_config
{
    SPI_TypeDef *Instance;     /**< SPI peripheral register base. */
    char *bus_name;            /**< RT-Thread SPI bus name. */
    IRQn_Type irq_type;        /**< SPI peripheral IRQ number. */
#ifdef BSP_SPI_RX_USING_DMA
    const struct stm32_dma_config *dma_rx; /**< RX DMA configuration. */
#endif /* BSP_SPI_RX_USING_DMA */
#ifdef BSP_SPI_TX_USING_DMA
    const struct stm32_dma_config *dma_tx; /**< TX DMA configuration. */
#endif /* BSP_SPI_TX_USING_DMA */
};

/**
 * @brief Board-level SPI device attachment information.
 */
struct stm32_spi_device
{
    rt_uint32_t pin;    /**< Chip-select pin number. */
    char *bus_name;     /**< SPI bus name used for attachment. */
    char *device_name;  /**< SPI device name registered on the bus. */
};

/**
 * @brief Runtime context for one STM32 SPI bus.
 */
struct stm32_spi
{
    SPI_HandleTypeDef handle;          /**< STM32 HAL SPI handle. */
    struct stm32_spi_config *config;   /**< Static bus configuration. */
    struct rt_spi_configuration *cfg;  /**< Active RT-Thread SPI configuration. */
    struct rt_spi_bus spi_bus;         /**< RT-Thread SPI bus object. */
    rt_uint16_t spi_xfer_flags;        /**< RT_DEVICE_FLAG_DMA_* and RT_DEVICE_FLAG_INT_* transfer flags. */
#ifdef BSP_SPI_USING_IRQ
    struct rt_completion cpt;          /**< Completion used by asynchronous SPI transfers. */
#endif /* BSP_SPI_USING_IRQ */
#ifdef BSP_SPI_USING_DMA
    struct
    {
#ifdef BSP_SPI_RX_USING_DMA
        DMA_HandleTypeDef handle_rx;   /**< STM32 HAL RX DMA handle. */
#endif /* BSP_SPI_RX_USING_DMA */
#ifdef BSP_SPI_TX_USING_DMA
        DMA_HandleTypeDef handle_tx;   /**< STM32 HAL TX DMA handle. */
#endif /* BSP_SPI_TX_USING_DMA */
    } dma;                             /**< DMA handles associated with this SPI bus. */
#endif /* BSP_SPI_USING_DMA */
};

#endif /*__DRV_SPI_H__ */
