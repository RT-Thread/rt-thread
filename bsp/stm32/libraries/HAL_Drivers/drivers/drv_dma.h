/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-10     SummerGift   first version
 * 2020-10-14     PeakRacing   Porting for stm32wbxx
 * 2026-04-13     wdfk-prog    Add STM32 DMA common helpers
 * 2026-08-28     moment-NEW   Unify DMA/BDMA/GPDMA descriptors
 */

/**
 * @file drv_dma.h
 * @brief STM32 DMA common descriptors and helper interfaces.
 */

#ifndef __DRV_DMA_H_
#define __DRV_DMA_H_

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SPI6 BDMA on STM32H7 must also enable the BDMA clock helper. Close the
 * Kconfig/C macro gap so AHB4 RCC code is compiled whenever SPI BDMA is
 * selected, even if BSP_USING_BDMA was not selected explicitly.
 */
#if defined(SOC_SERIES_STM32H7) && \
    (defined(BSP_SPI6_TX_USING_BDMA) || defined(BSP_SPI6_RX_USING_BDMA))
#ifndef BSP_USING_BDMA
#define BSP_USING_BDMA
#endif
#endif /* defined(SOC_SERIES_STM32H7) && SPI6 BDMA */

/*
 * DMA-capable BSPs are expected to enable HAL_DMA_MODULE_ENABLED in the
 * STM32 HAL configuration, so keep the common DMA helper in the build.
 */
#ifdef HAL_DMA_MODULE_ENABLED

/**
 * @brief DMA capability classification for STM32 series supported by this BSP.
 */
#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32L5) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS) || defined(SOC_SERIES_STM32L1)
#define DMA_INSTANCE_TYPE DMA_Channel_TypeDef
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
#define DMA_INSTANCE_TYPE DMA_Stream_TypeDef
#endif /* defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32L5)
|| defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G0)
|| defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32F3)
|| defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS) || defined(SOC_SERIES_STM32L1)*/

#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
#define STM32_DMA_USES_CHANNEL
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */

#if defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS)
#define STM32_DMA_USES_GPDMA
#endif /* defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS) */

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32L5) || defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS)
#define STM32_DMA_USES_REQUEST
#endif /* defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G0)
|| defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
|| defined(SOC_SERIES_STM32L5) || defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS) */

#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
#define STM32_DMA_SUPPORTS_FIFO
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1) */

#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32L1)
#define STM32_DMA_USES_RCC_AHBENR
#endif /* defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32L0) || defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32L1) */

#if defined(SOC_SERIES_STM32MP1)
#define STM32_DMA_USES_RCC_MP_AHB2ENSETR
#endif /* defined(SOC_SERIES_STM32MP1) */

#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32L5) || defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS)
#define STM32_DMA_USES_RCC_AHB1ENR
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
|| defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WL) || defined(SOC_SERIES_STM32G4)
|| defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32L5)
|| defined(SOC_SERIES_STM32U5) || defined(SOC_SERIES_STM32H5) || defined(SOC_SERIES_STM32H7RS) */

#ifndef STM32_DMA_DEFAULT_PRIORITY
#define STM32_DMA_DEFAULT_PRIORITY DMA_PRIORITY_LOW
#endif /* STM32_DMA_DEFAULT_PRIORITY */

#ifndef STM32_DMA_DEFAULT_PREEMPT_PRIORITY
#define STM32_DMA_DEFAULT_PREEMPT_PRIORITY 0
#endif /* STM32_DMA_DEFAULT_PREEMPT_PRIORITY */

#ifndef STM32_DMA_DEFAULT_SUB_PRIORITY
#define STM32_DMA_DEFAULT_SUB_PRIORITY 0
#endif /* STM32_DMA_DEFAULT_SUB_PRIORITY */

#if defined(STM32_DMA_USES_GPDMA)
#ifndef STM32_GPDMA_DEFAULT_BLOCK_HW_REQUEST
#define STM32_GPDMA_DEFAULT_BLOCK_HW_REQUEST DMA_BREQ_SINGLE_BURST
#endif /* STM32_GPDMA_DEFAULT_BLOCK_HW_REQUEST */

#ifndef STM32_GPDMA_DEFAULT_SRC_BURST_LENGTH
#define STM32_GPDMA_DEFAULT_SRC_BURST_LENGTH 1U
#endif /* STM32_GPDMA_DEFAULT_SRC_BURST_LENGTH */

#ifndef STM32_GPDMA_DEFAULT_DEST_BURST_LENGTH
#define STM32_GPDMA_DEFAULT_DEST_BURST_LENGTH 1U
#endif /* STM32_GPDMA_DEFAULT_DEST_BURST_LENGTH */

#ifndef STM32_GPDMA_DEFAULT_TRANSFER_ALLOCATED_PORT
#define STM32_GPDMA_DEFAULT_TRANSFER_ALLOCATED_PORT 0U
#endif /* STM32_GPDMA_DEFAULT_TRANSFER_ALLOCATED_PORT */

#ifndef STM32_GPDMA_DEFAULT_TRANSFER_EVENT_MODE
#define STM32_GPDMA_DEFAULT_TRANSFER_EVENT_MODE DMA_TCEM_BLOCK_TRANSFER
#endif /* STM32_GPDMA_DEFAULT_TRANSFER_EVENT_MODE */
#endif /* defined(STM32_DMA_USES_GPDMA) */

/**
 * @brief DMA controller type stored in each endpoint descriptor.
 */
typedef enum stm32_dma_type
{
    STM32_DMA_TYPE_DMA = 0,
    STM32_DMA_TYPE_BDMA,
    STM32_DMA_TYPE_GPDMA,
} stm32_dma_type;

/**
 * @brief Fields shared by classic DMA, BDMA and GPDMA descriptors.
 */
struct stm32_dma_config_common
{
    void *Instance;              /**< DMA/BDMA/GPDMA controller instance pointer. */
    stm32_dma_type type;         /**< Controller type used to dispatch apply/clock. */
    rt_uint32_t dma_rcc;         /**< RCC enable bit for the controller. */
    IRQn_Type dma_irq;           /**< Controller global IRQ number. */
    rt_uint32_t priority;        /**< Transfer priority. */
    rt_uint8_t preempt_priority; /**< NVIC preempt priority. */
    rt_uint8_t sub_priority;     /**< NVIC sub priority. */

#if defined(STM32_DMA_USES_REQUEST)
    rt_uint32_t request; /**< DMA request selector. */
#endif
    rt_uint32_t direction; /**< Transfer direction. */
    rt_uint32_t mode;      /**< Transfer mode. */
};

/**
 * @brief Classic DMA / BDMA HAL configuration fields.
 *
 * Channel and FIFO members are always present in the software descriptor.
 * Initializers only fill them when the current series exposes those HAL
 * fields; apply() copies them only for STM32_DMA_TYPE_DMA.
 */
struct stm32_dma_classic_config
{
    rt_uint32_t periph_inc;            /**< Peripheral address increment mode. */
    rt_uint32_t mem_inc;               /**< Memory address increment mode. */
    rt_uint32_t periph_data_alignment; /**< Peripheral data alignment. */
    rt_uint32_t mem_data_alignment;    /**< Memory data alignment. */
    rt_uint32_t channel;               /**< DMA channel selector for stream-based DMA. */
    rt_uint32_t fifo_mode;             /**< FIFO enable state. */
    rt_uint32_t fifo_threshold;        /**< FIFO threshold selection. */
    rt_uint32_t mem_burst;             /**< Memory burst transfer mode. */
    rt_uint32_t periph_burst;          /**< Peripheral burst transfer mode. */
};

/**
 * @brief GPDMA HAL configuration fields.
 */
struct stm32_gpdma_config
{
    rt_uint32_t blk_hw_request;          /**< GPDMA block hardware request mode. */
    rt_uint32_t src_inc;                 /**< GPDMA source increment mode. */
    rt_uint32_t dest_inc;                /**< GPDMA destination increment mode. */
    rt_uint32_t src_data_width;          /**< GPDMA source data width. */
    rt_uint32_t dest_data_width;         /**< GPDMA destination data width. */
    rt_uint32_t src_burst_length;        /**< GPDMA source burst length. */
    rt_uint32_t dest_burst_length;       /**< GPDMA destination burst length. */
    rt_uint32_t transfer_allocated_port; /**< GPDMA allocated port selection. */
    rt_uint32_t transfer_event_mode;     /**< GPDMA transfer event mode. */
};

/**
 * @brief Static DMA endpoint description used by board-level config headers.
 *
 * Controller differences are expressed by @ref stm32_dma_config_common.type
 * and the corresponding union arm. Peripheral drivers always use this type.
 */
struct stm32_dma_config
{
    struct stm32_dma_config_common common; /**< Fields shared by all controller types. */
    union
    {
        struct stm32_dma_classic_config classic; /**< Classic DMA / BDMA fields. */
        struct stm32_gpdma_config gpdma;         /**< GPDMA fields. */
    } config;
};

/**
 * @brief Optional selector fields kept in the descriptor for board-level readability.
 */
#if defined(STM32_DMA_USES_CHANNEL)
#define STM32_DMA_CHANNEL_FIELD(_channel) .channel = (_channel),
#else
#define STM32_DMA_CHANNEL_FIELD(_channel)
#endif /* defined(STM32_DMA_USES_CHANNEL) */

#if defined(STM32_DMA_USES_REQUEST)
#define STM32_DMA_REQUEST_FIELD(_request) .request = (_request),
#else
#define STM32_DMA_REQUEST_FIELD(_request)
#endif /* defined(STM32_DMA_USES_REQUEST) */

#if defined(STM32_DMA_SUPPORTS_FIFO)
#define STM32_DMA_FIFO_FIELD_DEFAULTS          \
    .fifo_mode = DMA_FIFOMODE_DISABLE,         \
    .fifo_threshold = DMA_FIFO_THRESHOLD_FULL, \
    .mem_burst = DMA_MBURST_SINGLE,            \
    .periph_burst = DMA_PBURST_SINGLE,

#define STM32_DMA_FIFO_FIELD_VALUES(_fifo_mode, _fifo_threshold, _mem_burst, _periph_burst) \
    .fifo_mode = (_fifo_mode),                                                              \
    .fifo_threshold = (_fifo_threshold),                                                    \
    .mem_burst = (_mem_burst),                                                              \
    .periph_burst = (_periph_burst),
#else
#define STM32_DMA_FIFO_FIELD_DEFAULTS
#define STM32_DMA_FIFO_FIELD_VALUES(_fifo_mode, _fifo_threshold, _mem_burst, _periph_burst)
#endif /* defined(STM32_DMA_SUPPORTS_FIFO) */

/**
 * @brief Generic descriptor initializer with explicit DMA direction and data layout.
 */
#define STM32_DMA_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority, _direction, _periph_inc, _mem_inc, _periph_data_alignment, _mem_data_alignment, _mode) \
    {                                                                                                                                                                                                                   \
        .common = {                                                                                                                                                                                                     \
            .Instance = (_instance),                                                                                                                                                                                    \
            .type = STM32_DMA_TYPE_DMA,                                                                                                                                                                                 \
            .dma_rcc = (_dma_rcc),                                                                                                                                                                                      \
            .dma_irq = (_dma_irq),                                                                                                                                                                                      \
            .priority = (_priority),                                                                                                                                                                                    \
            .preempt_priority = (_preempt_priority),                                                                                                                                                                    \
            .sub_priority = (_sub_priority),                                                                                                                                                                            \
            STM32_DMA_REQUEST_FIELD(_request)                                                                                                                                                                           \
                .direction = (_direction),                                                                                                                                                                              \
            .mode = (_mode),                                                                                                                                                                                            \
        },                                                                                                                                                                                                              \
        .config.classic = {                                                                                                                                                                                             \
            .periph_inc = (_periph_inc),                                                                                                                                                                                \
            .mem_inc = (_mem_inc),                                                                                                                                                                                      \
            .periph_data_alignment = (_periph_data_alignment),                                                                                                                                                          \
            .mem_data_alignment = (_mem_data_alignment),                                                                                                                                                                \
            STM32_DMA_CHANNEL_FIELD(_channel) STM32_DMA_FIFO_FIELD_DEFAULTS                                                                                                                                             \
        },                                                                                                                                                                                                              \
    }

/**
 * @brief Generic descriptor initializer for controllers that expose FIFO and burst fields.
 */
#define STM32_DMA_CONFIG_INIT_FIFO_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority, _direction, _periph_inc, _mem_inc, _periph_data_alignment, _mem_data_alignment, _mode, _fifo_mode, _fifo_threshold, _mem_burst, _periph_burst) \
    {                                                                                                                                                                                                                                                                                \
        .common = {                                                                                                                                                                                                                                                                  \
            .Instance = (_instance),                                                                                                                                                                                                                                                 \
            .type = STM32_DMA_TYPE_DMA,                                                                                                                                                                                                                                              \
            .dma_rcc = (_dma_rcc),                                                                                                                                                                                                                                                   \
            .dma_irq = (_dma_irq),                                                                                                                                                                                                                                                   \
            .priority = (_priority),                                                                                                                                                                                                                                                 \
            .preempt_priority = (_preempt_priority),                                                                                                                                                                                                                                 \
            .sub_priority = (_sub_priority),                                                                                                                                                                                                                                         \
            STM32_DMA_REQUEST_FIELD(_request)                                                                                                                                                                                                                                        \
                .direction = (_direction),                                                                                                                                                                                                                                           \
            .mode = (_mode),                                                                                                                                                                                                                                                         \
        },                                                                                                                                                                                                                                                                           \
        .config.classic = {                                                                                                                                                                                                                                                          \
            .periph_inc = (_periph_inc),                                                                                                                                                                                                                                             \
            .mem_inc = (_mem_inc),                                                                                                                                                                                                                                                   \
            .periph_data_alignment = (_periph_data_alignment),                                                                                                                                                                                                                       \
            .mem_data_alignment = (_mem_data_alignment),                                                                                                                                                                                                                             \
            STM32_DMA_CHANNEL_FIELD(_channel) STM32_DMA_FIFO_FIELD_VALUES(_fifo_mode, _fifo_threshold, _mem_burst, _periph_burst)                                                                                                                                                    \
        },                                                                                                                                                                                                                                                                           \
    }

/**
 * @brief Common byte/word transfer descriptor helpers used by board-level config headers.
 */
#define STM32_DMA_RX_BYTE_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_DMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_channel), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE, DMA_NORMAL)

#define STM32_DMA_TX_BYTE_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_DMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_channel), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_MEMORY_TO_PERIPH, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE, DMA_NORMAL)

#define STM32_DMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_DMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_channel), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE, DMA_CIRCULAR)

#define STM32_DMA_RX_WORD_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_DMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_channel), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_WORD, DMA_MDATAALIGN_WORD, DMA_NORMAL)

#define STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_DMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_channel), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_WORD, DMA_MDATAALIGN_WORD, DMA_CIRCULAR)

#define STM32_DMA_TX_WORD_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _channel, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_DMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_channel), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_MEMORY_TO_PERIPH, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_WORD, DMA_MDATAALIGN_WORD, DMA_NORMAL)

#if defined(STM32_DMA_USES_GPDMA)
/**
 * @brief GPDMA descriptor initializer with explicit source and destination attributes.
 */
#define STM32_GPDMA_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority, _direction, _src_inc, _dest_inc, _src_data_width, _dest_data_width, _mode) \
    {                                                                                                                                                                                               \
        .common = {                                                                                                                                                                                 \
            .Instance = (_instance),                                                                                                                                                                \
            .type = STM32_DMA_TYPE_GPDMA,                                                                                                                                                           \
            .dma_rcc = (_dma_rcc),                                                                                                                                                                  \
            .dma_irq = (_dma_irq),                                                                                                                                                                  \
            .priority = (_priority),                                                                                                                                                                \
            .preempt_priority = (_preempt_priority),                                                                                                                                                \
            .sub_priority = (_sub_priority),                                                                                                                                                        \
            .request = (_request),                                                                                                                                                                  \
            .direction = (_direction),                                                                                                                                                              \
            .mode = (_mode),                                                                                                                                                                        \
        },                                                                                                                                                                                          \
        .config.gpdma = {                                                                                                                                                                           \
            .blk_hw_request = STM32_GPDMA_DEFAULT_BLOCK_HW_REQUEST,                                                                                                                                 \
            .src_inc = (_src_inc),                                                                                                                                                                  \
            .dest_inc = (_dest_inc),                                                                                                                                                                \
            .src_data_width = (_src_data_width),                                                                                                                                                    \
            .dest_data_width = (_dest_data_width),                                                                                                                                                  \
            .src_burst_length = STM32_GPDMA_DEFAULT_SRC_BURST_LENGTH,                                                                                                                                \
            .dest_burst_length = STM32_GPDMA_DEFAULT_DEST_BURST_LENGTH,                                                                                                                              \
            .transfer_allocated_port = STM32_GPDMA_DEFAULT_TRANSFER_ALLOCATED_PORT,                                                                                                                 \
            .transfer_event_mode = STM32_GPDMA_DEFAULT_TRANSFER_EVENT_MODE,                                                                                                                         \
        },                                                                                                                                                                                          \
    }

#define STM32_GPDMA_RX_BYTE_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_GPDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_SINC_FIXED, DMA_DINC_INCREMENTED, DMA_SRC_DATAWIDTH_BYTE, DMA_DEST_DATAWIDTH_BYTE, DMA_NORMAL)

#define STM32_GPDMA_TX_BYTE_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_GPDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_MEMORY_TO_PERIPH, DMA_SINC_INCREMENTED, DMA_DINC_FIXED, DMA_SRC_DATAWIDTH_BYTE, DMA_DEST_DATAWIDTH_BYTE, DMA_NORMAL)

#define STM32_GPDMA_RX_BYTE_CIRCULAR_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_GPDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_SINC_FIXED, DMA_DINC_INCREMENTED, DMA_SRC_DATAWIDTH_BYTE, DMA_DEST_DATAWIDTH_BYTE, DMA_CIRCULAR)

#define STM32_GPDMA_RX_WORD_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_GPDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_SINC_FIXED, DMA_DINC_INCREMENTED, DMA_SRC_DATAWIDTH_WORD, DMA_DEST_DATAWIDTH_WORD, DMA_NORMAL)

#define STM32_GPDMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_GPDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_SINC_FIXED, DMA_DINC_INCREMENTED, DMA_SRC_DATAWIDTH_WORD, DMA_DEST_DATAWIDTH_WORD, DMA_CIRCULAR)

#define STM32_GPDMA_TX_WORD_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_GPDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_MEMORY_TO_PERIPH, DMA_SINC_INCREMENTED, DMA_DINC_FIXED, DMA_SRC_DATAWIDTH_WORD, DMA_DEST_DATAWIDTH_WORD, DMA_NORMAL)
#endif /* defined(STM32_DMA_USES_GPDMA) */

#if defined(SOC_SERIES_STM32H7)
#ifndef STM32_BDMA_DEFAULT_PRIORITY
#define STM32_BDMA_DEFAULT_PRIORITY DMA_PRIORITY_LOW
#endif

#ifndef STM32_BDMA_DEFAULT_PREEMPT_PRIORITY
#define STM32_BDMA_DEFAULT_PREEMPT_PRIORITY 0
#endif

#ifndef STM32_BDMA_DEFAULT_SUB_PRIORITY
#define STM32_BDMA_DEFAULT_SUB_PRIORITY 0
#endif

/**
 * @brief BDMA descriptor initializer. Produces struct stm32_dma_config.
 *
 * BDMA shares classic increment/alignment fields and has no FIFO. apply()
 * skips FIFO/channel copies when type is STM32_DMA_TYPE_BDMA.
 */
#define STM32_BDMA_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority, _direction, _periph_inc, _mem_inc, _periph_data_alignment, _mem_data_alignment, _mode) \
    {                                                                                                                                                                                                          \
        .common = {                                                                                                                                                                                            \
            .Instance = (_instance),                                                                                                                                                                           \
            .type = STM32_DMA_TYPE_BDMA,                                                                                                                                                                       \
            .dma_rcc = (_dma_rcc),                                                                                                                                                                             \
            .dma_irq = (_dma_irq),                                                                                                                                                                             \
            .priority = (_priority),                                                                                                                                                                           \
            .preempt_priority = (_preempt_priority),                                                                                                                                                           \
            .sub_priority = (_sub_priority),                                                                                                                                                                   \
            STM32_DMA_REQUEST_FIELD(_request)                                                                                                                                                                  \
                .direction = (_direction),                                                                                                                                                                     \
            .mode = (_mode),                                                                                                                                                                                   \
        },                                                                                                                                                                                                     \
        .config.classic = {                                                                                                                                                                                    \
            .periph_inc = (_periph_inc),                                                                                                                                                                       \
            .mem_inc = (_mem_inc),                                                                                                                                                                             \
            .periph_data_alignment = (_periph_data_alignment),                                                                                                                                                 \
            .mem_data_alignment = (_mem_data_alignment),                                                                                                                                                       \
        },                                                                                                                                                                                                     \
    }

#define STM32_BDMA_RX_BYTE_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_BDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_PERIPH_TO_MEMORY, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE, DMA_NORMAL)

#define STM32_BDMA_TX_BYTE_CONFIG_INIT_EX(_instance, _dma_rcc, _dma_irq, _request, _priority, _preempt_priority, _sub_priority) \
    STM32_BDMA_CONFIG_INIT_EX((_instance), (_dma_rcc), (_dma_irq), (_request), (_priority), (_preempt_priority), (_sub_priority), DMA_MEMORY_TO_PERIPH, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE, DMA_NORMAL)
#endif /* defined(SOC_SERIES_STM32H7) */

/**
 * @brief Apply one static DMA descriptor and initialize the HAL DMA handle.
 * @param dma_handle DMA handle to initialize.
 * @param dma_config Static DMA endpoint description.
 * @retval RT_EOK Success.
 * @retval -RT_ERROR HAL initialization failed.
 */
rt_err_t stm32_dma_init(DMA_HandleTypeDef *dma_handle,
                        const struct stm32_dma_config *dma_config);

/**
 * @brief Initialize one DMA handle, link it to the parent peripheral and enable its IRQ.
 * @param dma_handle DMA handle to initialize.
 * @param parent_handle Parent peripheral HAL handle.
 * @param dma_slot Parent peripheral DMA slot address, such as &huart->hdmarx.
 * @param dma_config Static DMA endpoint description.
 * @retval RT_EOK Success.
 * @retval -RT_ERROR HAL initialization failed.
 */
rt_err_t stm32_dma_setup(DMA_HandleTypeDef *dma_handle,
                         void *parent_handle,
                         DMA_HandleTypeDef **dma_slot,
                         const struct stm32_dma_config *dma_config);

/**
 * @brief Abort and de-initialize one DMA handle.
 *
 * The helper uses IRQ reference counting only for known shared DMA IRQ lines:
 * STM32F1 DMA2_Channel4_5_IRQn, STM32L0 DMA1_Channel4_5_6_7_IRQn and
 * STM32G0 DMA1_Channel2_3_IRQn. Other series keep direct IRQ disable behavior.
 *
 * @param dma_handle DMA handle to de-initialize.
 * @param dma_config Static DMA endpoint description.
 * @param abort_first RT_TRUE aborts the DMA transfer before de-initialization.
 * @retval RT_EOK Success.
 * @retval -RT_ERROR HAL abort or de-initialization failed.
 */
rt_err_t stm32_dma_deinit(DMA_HandleTypeDef *dma_handle,
                          const struct stm32_dma_config *dma_config,
                          rt_bool_t abort_first);

#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_DMA_H_ */
