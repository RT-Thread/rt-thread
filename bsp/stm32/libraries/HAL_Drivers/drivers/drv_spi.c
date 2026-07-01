/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 * 2018-12-11     greedyhao    Porting for stm32f7xx
 * 2019-01-03     zylx         modify DMA initialization and spixfer function
 * 2020-01-15     whj4674672   Porting for stm32h7xx
 * 2020-06-18     thread-liu   Porting for stm32mp1xx
 * 2020-10-14     PeakRacing   Porting for stm32wbxx
 * 2025-09-22     wdfk_prog    Refactor spixfer to fix DMA reception bug, correct timeout calculation.
 * 2026-04-14     wdfk_prog    Refine SPI DMA config hierarchy
 * 2026-04-16     wdfk_prog    Add SPI interrupt transfer mode scaffolding
 */

/**
 * @file drv_spi.c
 * @brief STM32 SPI bus driver implementation.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef BSP_USING_SPI

#include "drv_spi.h"
#include "drv_config.h"
#include <string.h>

#ifdef BSP_HARDWARE_SPI
/**
 * @brief SPI transfer route policy.
 *
 * @details
 *
 * For a universal and most conservative strategy across all STM32 series
 * under full-duplex operation at the highest supported SPI clock rates,
 * there is no generally safe transfer-length threshold for interrupt mode.
 * The interrupt servicing latency depends on MCU performance, bus clock,
 * HAL/LL implementation cost, system interrupt load, and runtime context,
 * so a single INT threshold cannot be guaranteed to work reliably on all targets.
 *
 * Therefore, use the following unified rule:
 *   - transfer length < 32 bytes  : use polling mode
 *   - transfer length >= 32 bytes : use DMA mode
 *   - interrupt mode              : disabled by default
 *
 * This policy prioritizes robustness and portability over theoretical peak efficiency.
 */
#ifndef BSP_SPI_DMA_TRANS_MIN_LEN
/* Minimum transfer length that may use DMA mode. */
#define BSP_SPI_DMA_TRANS_MIN_LEN 32U
#endif /* BSP_SPI_DMA_TRANS_MIN_LEN */
#ifndef BSP_SPI_INT_TRANS_MIN_LEN
/* Minimum transfer length that may use interrupt mode. */
#define BSP_SPI_INT_TRANS_MIN_LEN 32U
#endif /* BSP_SPI_INT_TRANS_MIN_LEN */

/*#define DRV_DEBUG*/
#define LOG_TAG              "drv.spi"
#include <drv_log.h>

/**
 * @brief Runtime array indexes for enabled STM32 SPI instances.
 *
 * @note The index order must match @ref spi_config and @ref spi_bus_obj.
 */
enum
{
#ifdef BSP_USING_SPI1
    SPI1_INDEX, /**< Runtime array index for SPI1. */
#endif
#ifdef BSP_USING_SPI2
    SPI2_INDEX, /**< Runtime array index for SPI2. */
#endif
#ifdef BSP_USING_SPI3
    SPI3_INDEX, /**< Runtime array index for SPI3. */
#endif
#ifdef BSP_USING_SPI4
    SPI4_INDEX, /**< Runtime array index for SPI4. */
#endif
#ifdef BSP_USING_SPI5
    SPI5_INDEX, /**< Runtime array index for SPI5. */
#endif
#ifdef BSP_USING_SPI6
    SPI6_INDEX, /**< Runtime array index for SPI6. */
#endif
};

/**
 * @var spi_config
 * @brief Static STM32 SPI bus configuration table.
 *
 * @details The table contains one conditional SPIx_BUS_CONFIG entry for
 * each enabled BSP_USING_SPIx instance. The table order must match the
 * SPIx_INDEX values and @ref spi_bus_obj.
 */
static struct stm32_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG, /**< Static bus configuration entry for SPI1. */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG, /**< Static bus configuration entry for SPI2. */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    SPI3_BUS_CONFIG, /**< Static bus configuration entry for SPI3. */
#endif /* BSP_USING_SPI3 */

#ifdef BSP_USING_SPI4
    SPI4_BUS_CONFIG, /**< Static bus configuration entry for SPI4. */
#endif /* BSP_USING_SPI4 */

#ifdef BSP_USING_SPI5
    SPI5_BUS_CONFIG, /**< Static bus configuration entry for SPI5. */
#endif /* BSP_USING_SPI5 */

#ifdef BSP_USING_SPI6
    SPI6_BUS_CONFIG, /**< Static bus configuration entry for SPI6. */
#endif /* BSP_USING_SPI6 */
};

/**
 * @brief Runtime STM32 SPI bus object table paired with @ref spi_config.
 */
static struct stm32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

#ifdef BSP_SPI_USING_DMA
/**
 * @brief Roll back SPI DMA setup that was partially initialized.
 *
 * @param spi_drv STM32 SPI driver context.
 * @param dma_flags RT_DEVICE_FLAG_DMA_* bits indicating DMA channels to release.
 */
static void stm32_spi_dma_rollback(struct stm32_spi *spi_drv, rt_uint16_t dma_flags)
{
#if defined(BSP_SPI_RX_USING_DMA)
    if ((dma_flags & RT_DEVICE_FLAG_DMA_RX) && (spi_drv->config->dma_rx != RT_NULL))
    {
        (void)stm32_dma_deinit(&spi_drv->dma.handle_rx, spi_drv->config->dma_rx, RT_FALSE);
        spi_drv->dma.handle_rx.Parent = RT_NULL;
        spi_drv->handle.hdmarx = RT_NULL;
    }
#endif /* BSP_SPI_RX_USING_DMA */

#if defined(BSP_SPI_TX_USING_DMA)
    if ((dma_flags & RT_DEVICE_FLAG_DMA_TX) && (spi_drv->config->dma_tx != RT_NULL))
    {
        (void)stm32_dma_deinit(&spi_drv->dma.handle_tx, spi_drv->config->dma_tx, RT_FALSE);
        spi_drv->dma.handle_tx.Parent = RT_NULL;
        spi_drv->handle.hdmatx = RT_NULL;
    }
#endif /* BSP_SPI_TX_USING_DMA */
}
#endif /* BSP_SPI_USING_DMA */

/**
 * @brief Initialize an STM32 SPI instance according to an RT-Thread SPI configuration.
 *
 * @param spi_drv STM32 SPI driver context.
 * @param cfg RT-Thread SPI bus configuration.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
static rt_err_t stm32_spi_init(struct stm32_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;

    if (cfg->mode & RT_SPI_SLAVE)
    {
        spi_handle->Init.Mode = SPI_MODE_SLAVE;
    }
    else
    {
        spi_handle->Init.Mode = SPI_MODE_MASTER;
    }

    if (cfg->mode & RT_SPI_3WIRE)
    {
        spi_handle->Init.Direction = SPI_DIRECTION_1LINE;
    }
    else
    {
        spi_handle->Init.Direction = SPI_DIRECTION_2LINES;
    }

    if (cfg->data_width == 8)
    {
        spi_handle->Init.DataSize = SPI_DATASIZE_8BIT;
    }
    else if (cfg->data_width == 16)
    {
        spi_handle->Init.DataSize = SPI_DATASIZE_16BIT;
    }
    else
    {
        return -RT_EIO;
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        spi_handle->Init.CLKPhase = SPI_PHASE_2EDGE;
    }
    else
    {
        spi_handle->Init.CLKPhase = SPI_PHASE_1EDGE;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        spi_handle->Init.CLKPolarity = SPI_POLARITY_HIGH;
    }
    else
    {
        spi_handle->Init.CLKPolarity = SPI_POLARITY_LOW;
    }

    spi_handle->Init.NSS = SPI_NSS_SOFT;

    uint32_t spi_clock = 0UL;
    /* Some series may only have APBPERIPH_BASE, but don't have HAL_RCC_GetPCLK2Freq */
#if defined(APBPERIPH_BASE)
    spi_clock = HAL_RCC_GetPCLK1Freq();
#elif defined(APB1PERIPH_BASE) || defined(APB2PERIPH_BASE)
    /* The SPI clock for H7 cannot be configured with a peripheral bus clock, so it needs to be written separately */
#if defined(SOC_SERIES_STM32H7)
    /* When the configuration is generated using CUBEMX, the configuration for the SPI clock is placed in the HAL_SPI_Init function.
    Therefore, it is necessary to initialize and configure the SPI clock to automatically configure the frequency division */
    HAL_SPI_Init(spi_handle);
    spi_clock = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI123);
#else
    if ((rt_uint32_t)spi_drv->config->Instance >= APB2PERIPH_BASE)
    {
        spi_clock = HAL_RCC_GetPCLK2Freq();
    }
    else
    {
        spi_clock = HAL_RCC_GetPCLK1Freq();
    }
#endif /* SOC_SERIES_STM32H7) */
#endif /* APBPERIPH_BASE */

    if (cfg->max_hz >= spi_clock / 2)
    {
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    }
    else if (cfg->max_hz >= spi_clock / 4)
    {
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    }
    else if (cfg->max_hz >= spi_clock / 8)
    {
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    }
    else if (cfg->max_hz >= spi_clock / 16)
    {
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    }
    else if (cfg->max_hz >= spi_clock / 32)
    {
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    }
    else if (cfg->max_hz >= spi_clock / 64)
    {
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    }
    else if (cfg->max_hz >= spi_clock / 128)
    {
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    }
    else
    {
        /*  min prescaler 256 */
        spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    }

#if defined(SOC_SERIES_STM32H7)
    cfg->usage_freq = spi_clock / (rt_size_t)(1 << ((spi_handle->Init.BaudRatePrescaler >> SPI_CFG1_MBR_Pos) + 1));
#else
    cfg->usage_freq = spi_clock / (rt_size_t)(1 << ((spi_handle->Init.BaudRatePrescaler >> SPI_CR1_BR_Pos) + 1));
#endif /* SOC_SERIES_STM32H7 */

    LOG_D("sys freq: %d, pclk freq: %d, SPI limiting freq: %d, SPI usage freq: %d",
#if defined(SOC_SERIES_STM32MP1)
          HAL_RCC_GetSystemCoreClockFreq(),
#else
          HAL_RCC_GetSysClockFreq(),
#endif
          spi_clock,
          cfg->max_hz,
          cfg->usage_freq);

    if (cfg->mode & RT_SPI_MSB)
    {
        spi_handle->Init.FirstBit = SPI_FIRSTBIT_MSB;
    }
    else
    {
        spi_handle->Init.FirstBit = SPI_FIRSTBIT_LSB;
    }

    spi_handle->Init.TIMode = SPI_TIMODE_DISABLE;
    spi_handle->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi_handle->State = HAL_SPI_STATE_RESET;
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32WB)
    spi_handle->Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
#elif defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32MP1)
    spi_handle->Init.NSS                        = SPI_NSS_SOFT;
    spi_handle->Init.NSSPMode                   = SPI_NSS_PULSE_DISABLE;
    spi_handle->Init.NSSPolarity                = SPI_NSS_POLARITY_LOW;
    spi_handle->Init.CRCPolynomial              = 7;
    spi_handle->Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    spi_handle->Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    spi_handle->Init.MasterSSIdleness           = SPI_MASTER_SS_IDLENESS_00CYCLE;
    spi_handle->Init.MasterInterDataIdleness    = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    spi_handle->Init.MasterReceiverAutoSusp     = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    spi_handle->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;
    spi_handle->Init.IOSwap                     = SPI_IO_SWAP_DISABLE;
    spi_handle->Init.FifoThreshold              = SPI_FIFO_THRESHOLD_01DATA;
#endif

    if (HAL_SPI_Init(spi_handle) != HAL_OK)
    {
        return -RT_EIO;
    }

#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) \
        || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32WB)
    SET_BIT(spi_handle->Instance->CR2, SPI_RXFIFO_THRESHOLD_HF);
#endif

#ifdef BSP_SPI_USING_DMA
    /* DMA configuration */
#if defined(BSP_SPI_RX_USING_DMA)
    if (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_DMA_RX)
    {
        if (stm32_dma_setup(&spi_drv->dma.handle_rx,
                            &spi_drv->handle,
                            &spi_drv->handle.hdmarx,
                            spi_drv->config->dma_rx) != RT_EOK)
        {
            stm32_spi_dma_rollback(spi_drv, RT_DEVICE_FLAG_DMA_RX);
            return -RT_EIO;
        }
    }
#endif /* BSP_SPI_RX_USING_DMA */

#if defined(BSP_SPI_TX_USING_DMA)
    if (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_DMA_TX)
    {
        if (stm32_dma_setup(&spi_drv->dma.handle_tx,
                            &spi_drv->handle,
                            &spi_drv->handle.hdmatx,
                            spi_drv->config->dma_tx) != RT_EOK)
        {
            stm32_spi_dma_rollback(spi_drv, RT_DEVICE_FLAG_DMA_TX | (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_DMA_RX));
            return -RT_EIO;
        }
    }
#endif /* BSP_SPI_TX_USING_DMA */
#endif /* BSP_SPI_USING_DMA */

#ifdef BSP_SPI_USING_IRQ
    if ((spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_DMA_TX) || (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_DMA_RX)
     || (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_INT_TX) || (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_INT_RX))
    {
        HAL_NVIC_SetPriority(spi_drv->config->irq_type, 2, 0);
        HAL_NVIC_EnableIRQ(spi_drv->config->irq_type);
    }
#endif /* BSP_SPI_USING_IRQ */

    LOG_D("%s init done", spi_drv->config->bus_name);
    return RT_EOK;
}

/**
 * @brief Transfer one RT-Thread SPI message over an STM32 SPI bus.
 *
 * @param device RT-Thread SPI device.
 * @param message SPI message containing TX/RX buffers and transfer length.
 * @return Transferred byte count on success, otherwise a negative RT-Thread error code.
 */
static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    HAL_StatusTypeDef state = HAL_OK;
    rt_size_t message_length, already_send_length;
    rt_uint16_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct stm32_spi *spi_drv =  rt_container_of(device->bus, struct stm32_spi, spi_bus);
    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;

    rt_bool_t need_abort = RT_FALSE;
    rt_uint64_t total_byte_ms = (rt_uint64_t)message->length * 1000;
    rt_uint32_t speed_bytes_per_sec = spi_drv->cfg->usage_freq / 8;
    if (speed_bytes_per_sec == 0)
    {
        speed_bytes_per_sec = 1;
    }

    rt_uint32_t timeout_ms = total_byte_ms / speed_bytes_per_sec + 100;
#ifdef BSP_SPI_USING_IRQ
    rt_tick_t timeout_tick = rt_tick_from_millisecond(timeout_ms);
#endif /* BSP_SPI_USING_IRQ */

#if defined(BSP_SPI_USING_DMA) || defined(BSP_SPI_USING_INT)
    /*
     * Snapshot the call context once for the whole SPI message.
     *
     * The async route decision must stay stable across all chunks split from
     * one message. Re-evaluating scheduler/IRQ state per chunk could route
     * one logical SPI transfer through different async/polling policies.
     *
     * A thread switch or interrupt can happen while waiting for async transfer
     * completion, but execution still resumes in the same spixfer() call
     * context. Therefore, the route policy should follow this message-level
     * context instead of re-sampling a transient runtime state.
     */
    const rt_bool_t scheduler_available = rt_scheduler_is_available();
    const rt_bool_t irq_disabled = rt_hw_interrupt_is_disabled();
    const rt_bool_t async_allowed = (scheduler_available && !irq_disabled);
#endif /* defined(BSP_SPI_USING_DMA) || defined(BSP_SPI_USING_INT) */

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            rt_pin_write(device->cs_pin, PIN_HIGH);
        }
        else
        {
            rt_pin_write(device->cs_pin, PIN_LOW);
        }
    }

    LOG_D("%s transfer prepare and start", spi_drv->config->bus_name);
    LOG_D("%s sendbuf: 0x%08x, recvbuf: 0x%08x, length: %d",
          spi_drv->config->bus_name,
          (uint32_t)message->send_buf,
          (uint32_t)message->recv_buf, message->length);

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;
    while (message_length)
    {
        /* the HAL library use uint16 to save the data length */
        if (message_length > 65535)
        {
            send_length = 65535;
            message_length = message_length - 65535;
        }
        else
        {
            send_length = message_length;
            message_length = 0;
        }

        /* calculate the start address */
        already_send_length = message->length - send_length - message_length;
        /* avoid null pointer problems */
        if (message->send_buf)
        {
            send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        }
        if (message->recv_buf)
        {
            recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        }

#ifdef BSP_SPI_USING_DMA
        const rt_uint8_t *dma_send_buf = send_buf;
        rt_uint8_t *dma_recv_buf = recv_buf;

        rt_uint8_t *aligned_send_buf = RT_NULL;
        rt_uint8_t *aligned_recv_buf = RT_NULL;

        rt_bool_t dma_eligible = (send_length >= BSP_SPI_DMA_TRANS_MIN_LEN);
#if defined(BSP_SPI_TX_USING_DMA)
        rt_bool_t use_tx_dma = dma_eligible && (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_DMA_TX);
#else
        rt_bool_t use_tx_dma = RT_FALSE;
#endif /* BSP_SPI_TX_USING_DMA */
#if defined(BSP_SPI_RX_USING_DMA)
        rt_bool_t use_rx_dma = dma_eligible && (spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_DMA_RX);
#else
        rt_bool_t use_rx_dma = RT_FALSE;
#endif /* BSP_SPI_RX_USING_DMA */

        if (!async_allowed)
        {
            use_rx_dma = use_tx_dma = dma_eligible = RT_FALSE;
        }

        if (dma_eligible)
        {
#if defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
            const rt_uint8_t align_size = 32;
#else
            const rt_uint8_t align_size = 4;
#endif
            /* Prepare DMA buffers only if the corresponding DMA will be used */
            if (send_buf && use_tx_dma && !RT_IS_ALIGN((rt_uint32_t)send_buf, align_size))
            {
                aligned_send_buf = rt_malloc_align(send_length, align_size);
                if (aligned_send_buf == RT_NULL)
                {
                    state = HAL_ERROR;
                    LOG_E("malloc aligned_send_buf failed!");
                    goto transfer_cleanup;
                }
                rt_memcpy(aligned_send_buf, send_buf, send_length);
                dma_send_buf = aligned_send_buf;
            }

            if (recv_buf && use_rx_dma && !RT_IS_ALIGN((rt_uint32_t)recv_buf, align_size))
            {
                aligned_recv_buf = rt_malloc_align(send_length, align_size);
                if (aligned_recv_buf == RT_NULL)
                {
                    state = HAL_ERROR;
                    LOG_E("malloc aligned_recv_buf failed!");
                    goto transfer_cleanup;
                }
                dma_recv_buf = aligned_recv_buf;
            }

#if defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
            // D-Cache maintenance for buffers that will be used by DMA
            if (dma_send_buf) rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)dma_send_buf, send_length);
            if (dma_recv_buf) rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, dma_recv_buf, send_length);
#endif
        }
#endif /* BSP_SPI_USING_DMA */

#ifdef BSP_SPI_USING_INT
        rt_bool_t int_eligible = (send_length >= BSP_SPI_INT_TRANS_MIN_LEN);
#if defined(BSP_SPI_TX_USING_INT)
        rt_bool_t use_tx_int = int_eligible && spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_INT_TX;
#else
        rt_bool_t use_tx_int = RT_FALSE;
#endif /* BSP_SPI_TX_USING_INT */
#if defined(BSP_SPI_RX_USING_INT)
        rt_bool_t use_rx_int = int_eligible && spi_drv->spi_xfer_flags & RT_DEVICE_FLAG_INT_RX;
#else
        rt_bool_t use_rx_int = RT_FALSE;
#endif /* BSP_SPI_RX_USING_INT */
        if (!async_allowed)
        {
            use_rx_int = use_tx_int = int_eligible = RT_FALSE;
        }
#endif /* BSP_SPI_USING_INT */

        rt_bool_t async_started = RT_TRUE;
#ifdef BSP_SPI_USING_IRQ
        /* Reinitialize the completion object for the current transfer. */
        rt_completion_init(&spi_drv->cpt);
#endif /* BSP_SPI_USING_IRQ */
        /* Start data exchange in full-duplex DMA mode. */
        if (message->send_buf && message->recv_buf)
        {
#ifdef BSP_SPI_USING_DMA
            if (use_tx_dma && use_rx_dma)
            {
                state = HAL_SPI_TransmitReceive_DMA(spi_handle, (uint8_t *)dma_send_buf, dma_recv_buf, send_length);
            }
            else
#endif /* BSP_SPI_USING_DMA */
#ifdef BSP_SPI_USING_INT
            if (use_tx_int && use_rx_int)
            {
                state = HAL_SPI_TransmitReceive_IT(spi_handle, (uint8_t *)send_buf, recv_buf, send_length);
            }
            else
#endif /* BSP_SPI_USING_INT */
            {
                state = HAL_SPI_TransmitReceive(spi_handle, (uint8_t *)send_buf, recv_buf, send_length, timeout_ms);
                async_started = RT_FALSE;
            }
        }
        else if (message->send_buf)
        {
#ifdef BSP_SPI_USING_DMA
            if (use_tx_dma)
            {
                state = HAL_SPI_Transmit_DMA(spi_handle, (uint8_t *)dma_send_buf, send_length);
            }
            else
#endif /* BSP_SPI_USING_DMA */
#ifdef BSP_SPI_USING_INT
            if (use_tx_int)
            {
                state = HAL_SPI_Transmit_IT(spi_handle, (uint8_t *)send_buf, send_length);
            }
            else
#endif /* BSP_SPI_USING_INT */
            {
                state = HAL_SPI_Transmit(spi_handle, (uint8_t *)send_buf, send_length, timeout_ms);
                async_started = RT_FALSE;
            }
        }
        else if (message->recv_buf)
        {
            rt_uint8_t *rx_dummy_buf = recv_buf;

            /* clear the old error flag */
            __HAL_SPI_CLEAR_OVRFLAG(spi_handle);
#ifdef BSP_SPI_USING_DMA
            if (use_rx_dma)
            {
                rx_dummy_buf = dma_recv_buf;
            }
#endif /* BSP_SPI_USING_DMA */
            /*
             * STM32 HAL uses the receive buffer as dummy TX data in master
             * receive-only mode, so preload the actual HAL buffer with 0xFF.
             */
            rt_memset(rx_dummy_buf, 0xFF, send_length);
#ifdef BSP_SPI_USING_DMA
            if (use_rx_dma)
            {
                state = HAL_SPI_Receive_DMA(spi_handle, dma_recv_buf, send_length);
            }
            else
#endif /* BSP_SPI_USING_DMA */
#ifdef BSP_SPI_USING_INT
            if (use_rx_int)
            {
                state = HAL_SPI_Receive_IT(spi_handle, recv_buf, send_length);
            }
            else
#endif /* BSP_SPI_USING_INT */
            {
                state = HAL_SPI_Receive(spi_handle, recv_buf, send_length, timeout_ms);
                async_started = RT_FALSE;
            }
        }
        else
        {
            state = HAL_ERROR;
            LOG_E("message->send_buf and message->recv_buf are both NULL!");
        }

        if (state != HAL_OK)
        {
            LOG_E("SPI transfer error: %d", state);
            message->length = 0;
            spi_handle->State = HAL_SPI_STATE_READY;
            goto transfer_cleanup;
        }

#ifdef BSP_SPI_USING_IRQ
        if (async_started)
        {
            /* blocking the thread,and the other tasks can run */
            if (rt_completion_wait(&spi_drv->cpt, timeout_tick) != RT_EOK)
            {
                state = HAL_TIMEOUT;
                need_abort = RT_TRUE;
                LOG_E("wait for SPI async transfer overtime!");
                goto transfer_cleanup;
            }

            if (spi_handle->ErrorCode != HAL_SPI_ERROR_NONE)
            {
                rt_uint32_t err = spi_handle->ErrorCode;
                rt_bool_t tx_only = (message->send_buf != RT_NULL) && (message->recv_buf == RT_NULL);
                rt_bool_t ovr_only = ((err & HAL_SPI_ERROR_OVR) != 0U) && ((err & ~(HAL_SPI_ERROR_OVR | HAL_SPI_ERROR_ABORT)) == 0U);

                /**
                 * Ignore the expected OVR from a completed Tx-only transfer.
                 *
                 * In 2-line SPI mode, Tx-only transfer still receives data from
                 * MISO. Since no RX buffer is provided, the received data is not
                 * read and HAL may latch OVR after async Tx completion.
                 */
                if (tx_only && ovr_only && (spi_handle->Init.Direction == SPI_DIRECTION_2LINES) && (spi_handle->TxXferCount == 0U))
                {
                    __HAL_SPI_CLEAR_OVRFLAG(spi_handle);
                    spi_handle->ErrorCode = HAL_SPI_ERROR_NONE;
                }
                else
                {
                    state = HAL_ERROR;
                    need_abort = RT_TRUE;
                    LOG_E("SPI async transfer failed, error code: 0x%08x", spi_handle->ErrorCode);
                    goto transfer_cleanup;
                }
            }
        }
#endif /* BSP_SPI_USING_IRQ */
        if (state == HAL_OK)
        {
            /* send-only */
            if (message->send_buf != RT_NULL && message->recv_buf == RT_NULL
            && message->cs_release && (device->config.mode & RT_SPI_3WIRE))
            {
                /* release the CS by disable SPI when using 3 wires SPI */
                __HAL_SPI_DISABLE(spi_handle);
            }
            LOG_D("%s transfer done", spi_drv->config->bus_name);
        }

transfer_cleanup:
        if (need_abort)
        {
            if (HAL_SPI_Abort(spi_handle) != HAL_OK)
            {
                LOG_W("abort SPI async transfer failed, state: %d, error: 0x%08x",
                      HAL_SPI_GetState(spi_handle),
                      spi_handle->ErrorCode);
            }
        }
#ifdef BSP_SPI_USING_DMA
        /* Post-transfer processing */
        if (state == HAL_OK)
        {
            if (aligned_recv_buf != RT_NULL)
            {
#if defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7)
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, aligned_recv_buf, send_length);
#endif
                rt_memcpy(recv_buf, aligned_recv_buf, send_length);
            }
        }

        // Free any temporary buffers that were allocated
        if (aligned_send_buf) rt_free_align(aligned_send_buf);
        if (aligned_recv_buf) rt_free_align(aligned_recv_buf);
#endif /* BSP_SPI_USING_DMA */
        if (state != HAL_OK)
        {
            break;
        }
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_LOW);
        else
            rt_pin_write(device->cs_pin, PIN_HIGH);
    }

    if(state != HAL_OK)
    {
        return -RT_ERROR;
    }
    return message->length;
}

/**
 * @brief Configure an RT-Thread SPI device backed by an STM32 SPI bus.
 *
 * @param device RT-Thread SPI device.
 * @param configuration SPI mode, data width and clock configuration.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct stm32_spi *spi_drv =  rt_container_of(device->bus, struct stm32_spi, spi_bus);
    spi_drv->cfg = configuration;

    return stm32_spi_init(spi_drv, configuration);
}

/**
 * @brief RT-Thread SPI operation callbacks implemented by the STM32 driver.
 */
static const struct rt_spi_ops stm_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

/**
 * @brief Register all enabled STM32 SPI buses with RT-Thread.
 *
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;

    for (rt_size_t i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];
        spi_bus_obj[i].handle.Instance = spi_config[i].Instance;

#ifdef BSP_SPI_USING_IRQ
        /* initialize completion object */
        rt_completion_init(&spi_bus_obj[i].cpt);
#endif /* BSP_SPI_USING_IRQ */

        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &stm_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}

/**
 * @brief Attach an SPI device to a registered STM32 SPI bus.
 *
 * @param bus_name SPI bus name, such as "spi1".
 * @param device_name SPI device name to register.
 * @param cs_pin Chip-select pin used by the SPI device.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

/**
 * @brief Detach a previously attached STM32 SPI device.
 *
 * @param device_name SPI device name to detach.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
rt_err_t rt_hw_spi_device_detach(const char *device_name)
{
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    rt_device_t device = rt_device_find(device_name);
    if (device == RT_NULL)
    {
        LOG_E("SPI device %s not found.", device_name);
        return -RT_ERROR;
    }

    if (device->type != RT_Device_Class_SPIDevice)
    {
        LOG_E("%s is not an SPI device.", device_name);
        return -RT_ERROR;
    }

    spi_device = (struct rt_spi_device *)device;

    result = rt_spi_bus_detach_device_cspin(spi_device);
    if (result != RT_EOK)
    {
        LOG_E("Failed to detach %s from its bus, error code: %d", device_name, result);
        return result;
    }

    rt_free(spi_device);

    LOG_D("SPI device %s has been detached.", device_name);

    return RT_EOK;
}

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_USING_IRQ)
/**
 * @brief Handle the SPI1 peripheral interrupt.
 */
void SPI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef BSP_SPI1_RX_USING_DMA
/**
 * @brief Handle the SPI1 RX DMA interrupt.
 */
void SPI1_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI1_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef BSP_SPI1_TX_USING_DMA
/**
 * @brief Handle the SPI1 TX DMA interrupt.
 */
void SPI1_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI1_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI1_TX_USING_DMA */
#endif /* defined(BSP_USING_SPI1) && defined(BSP_SPI1_USING_IRQ) */

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_USING_IRQ)
/**
 * @brief Handle the SPI2 peripheral interrupt.
 */
void SPI2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef BSP_SPI2_RX_USING_DMA
/**
 * @brief Handle the SPI2 RX DMA interrupt.
 */
void SPI2_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI2_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef BSP_SPI2_TX_USING_DMA
/**
 * @brief Handle the SPI2 TX DMA interrupt.
 */
void SPI2_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI2_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI2_TX_USING_DMA */
#endif /* defined(BSP_USING_SPI2) && defined(BSP_SPI2_USING_IRQ) */

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_USING_IRQ)
/**
 * @brief Handle the SPI3 peripheral interrupt.
 */
void SPI3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef BSP_SPI3_RX_USING_DMA
/**
 * @brief Handle the SPI3 RX DMA interrupt.
 */
void SPI3_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI3_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI3_RX_USING_DMA */

#ifdef BSP_SPI3_TX_USING_DMA
/**
 * @brief Handle the SPI3 TX DMA interrupt.
 */
void SPI3_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI3_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI3_TX_USING_DMA */
#endif /* defined(BSP_USING_SPI3) && defined(BSP_SPI3_USING_IRQ) */

#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_USING_IRQ)
/**
 * @brief Handle the SPI4 peripheral interrupt.
 */
void SPI4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI4_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef BSP_SPI4_RX_USING_DMA
/**
 * @brief Handle the SPI4 RX DMA interrupt.
 */
void SPI4_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI4_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI4_RX_USING_DMA */

#ifdef BSP_SPI4_TX_USING_DMA
/**
 * @brief Handle the SPI4 TX DMA interrupt.
 */
void SPI4_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI4_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI4_TX_USING_DMA */
#endif /* defined(BSP_USING_SPI4) && defined(BSP_SPI4_USING_IRQ) */

#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_USING_IRQ)
/**
 * @brief Handle the SPI5 peripheral interrupt.
 */
void SPI5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI5_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef BSP_SPI5_RX_USING_DMA
/**
 * @brief Handle the SPI5 RX DMA interrupt.
 */
void SPI5_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI5_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI5_RX_USING_DMA */

#ifdef BSP_SPI5_TX_USING_DMA
/**
 * @brief Handle the SPI5 TX DMA interrupt.
 */
void SPI5_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI5_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI5_TX_USING_DMA */
#endif /* defined(BSP_USING_SPI5) && defined(BSP_SPI5_USING_IRQ) */

#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_USING_IRQ)
/**
 * @brief Handle the SPI6 peripheral interrupt.
 */
void SPI6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI6_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef BSP_SPI6_RX_USING_DMA
/**
 * @brief Handle the SPI6 RX DMA interrupt.
 */
void SPI6_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI6_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI6_RX_USING_DMA */

#ifdef BSP_SPI6_TX_USING_DMA
/**
 * @brief Handle the SPI6 TX DMA interrupt.
 */
void SPI6_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI6_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_SPI6_TX_USING_DMA */
#endif /* defined(BSP_USING_SPI6) && defined(BSP_SPI6_USING_IRQ) */

#ifdef BSP_SPI_USING_IRQ
/**
 * @brief Populate per-instance SPI transfer flags and DMA configuration pointers.
 */
static void stm32_get_xfer_info(void)
{
#ifdef BSP_USING_SPI1
    spi_bus_obj[SPI1_INDEX].spi_xfer_flags = 0;
#ifdef BSP_SPI1_RX_USING_INT
    spi_bus_obj[SPI1_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_RX;
#endif
#ifdef BSP_SPI1_TX_USING_INT
    spi_bus_obj[SPI1_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_TX;
#endif
#ifdef BSP_SPI1_RX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_RX;
    /** SPI1 RX DMA configuration descriptor. */
    static const struct stm32_dma_config spi1_dma_rx = SPI1_RX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_rx = &spi1_dma_rx;
#endif
#ifdef BSP_SPI1_TX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_TX;
    /** SPI1 TX DMA configuration descriptor. */
    static const struct stm32_dma_config spi1_dma_tx = SPI1_TX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_tx = &spi1_dma_tx;
#endif
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    spi_bus_obj[SPI2_INDEX].spi_xfer_flags = 0;
#ifdef BSP_SPI2_RX_USING_INT
    spi_bus_obj[SPI2_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_RX;
#endif
#ifdef BSP_SPI2_TX_USING_INT
    spi_bus_obj[SPI2_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_TX;
#endif
#ifdef BSP_SPI2_RX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_RX;
    /** SPI2 RX DMA configuration descriptor. */
    static const struct stm32_dma_config spi2_dma_rx = SPI2_RX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_rx = &spi2_dma_rx;
#endif
#ifdef BSP_SPI2_TX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_TX;
    /** SPI2 TX DMA configuration descriptor. */
    static const struct stm32_dma_config spi2_dma_tx = SPI2_TX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_tx = &spi2_dma_tx;
#endif
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    spi_bus_obj[SPI3_INDEX].spi_xfer_flags = 0;
#ifdef BSP_SPI3_RX_USING_INT
    spi_bus_obj[SPI3_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_RX;
#endif
#ifdef BSP_SPI3_TX_USING_INT
    spi_bus_obj[SPI3_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_TX;
#endif
#ifdef BSP_SPI3_RX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_RX;
    /** SPI3 RX DMA configuration descriptor. */
    static const struct stm32_dma_config spi3_dma_rx = SPI3_RX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_rx = &spi3_dma_rx;
#endif
#ifdef BSP_SPI3_TX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_TX;
    /** SPI3 TX DMA configuration descriptor. */
    static const struct stm32_dma_config spi3_dma_tx = SPI3_TX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_tx = &spi3_dma_tx;
#endif
#endif /* BSP_USING_SPI3 */

#ifdef BSP_USING_SPI4
    spi_bus_obj[SPI4_INDEX].spi_xfer_flags = 0;
#ifdef BSP_SPI4_RX_USING_INT
    spi_bus_obj[SPI4_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_RX;
#endif
#ifdef BSP_SPI4_TX_USING_INT
    spi_bus_obj[SPI4_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_TX;
#endif
#ifdef BSP_SPI4_RX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_RX;
    /** SPI4 RX DMA configuration descriptor. */
    static const struct stm32_dma_config spi4_dma_rx = SPI4_RX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_rx = &spi4_dma_rx;
#endif
#ifdef BSP_SPI4_TX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_TX;
    /** SPI4 TX DMA configuration descriptor. */
    static const struct stm32_dma_config spi4_dma_tx = SPI4_TX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_tx = &spi4_dma_tx;
#endif
#endif /* BSP_USING_SPI4 */

#ifdef BSP_USING_SPI5
    spi_bus_obj[SPI5_INDEX].spi_xfer_flags = 0;
#ifdef BSP_SPI5_RX_USING_INT
    spi_bus_obj[SPI5_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_RX;
#endif
#ifdef BSP_SPI5_TX_USING_INT
    spi_bus_obj[SPI5_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_TX;
#endif
#ifdef BSP_SPI5_RX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_RX;
    /** SPI5 RX DMA configuration descriptor. */
    static const struct stm32_dma_config spi5_dma_rx = SPI5_RX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_rx = &spi5_dma_rx;
#endif
#ifdef BSP_SPI5_TX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_TX;
    /** SPI5 TX DMA configuration descriptor. */
    static const struct stm32_dma_config spi5_dma_tx = SPI5_TX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_tx = &spi5_dma_tx;
#endif
#endif /* BSP_USING_SPI5 */

#ifdef BSP_USING_SPI6
    spi_bus_obj[SPI6_INDEX].spi_xfer_flags = 0;
#ifdef BSP_SPI6_RX_USING_INT
    spi_bus_obj[SPI6_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_RX;
#endif
#ifdef BSP_SPI6_TX_USING_INT
    spi_bus_obj[SPI6_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_INT_TX;
#endif
#ifdef BSP_SPI6_RX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_RX;
    /** SPI6 RX DMA configuration descriptor. */
    static const struct stm32_dma_config spi6_dma_rx = SPI6_RX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_rx = &spi6_dma_rx;
#endif
#ifdef BSP_SPI6_TX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_xfer_flags |= RT_DEVICE_FLAG_DMA_TX;
    /** SPI6 TX DMA configuration descriptor. */
    static const struct stm32_dma_config spi6_dma_tx = SPI6_TX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_tx = &spi6_dma_tx;
#endif
#endif /* BSP_USING_SPI6 */
}

/**
 * @brief Handle STM32 HAL full-duplex SPI transfer completion.
 *
 * @param hspi STM32 HAL SPI handle that completed the transfer.
 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    struct stm32_spi *spi_drv =  rt_container_of(hspi, struct stm32_spi, handle);
    rt_completion_done(&spi_drv->cpt);
}

/**
 * @brief Handle STM32 HAL SPI TX completion.
 *
 * @param hspi STM32 HAL SPI handle that completed the transfer.
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    struct stm32_spi *spi_drv =  rt_container_of(hspi, struct stm32_spi, handle);
    rt_completion_done(&spi_drv->cpt);
}

/**
 * @brief Handle STM32 HAL SPI RX completion.
 *
 * @param hspi STM32 HAL SPI handle that completed the transfer.
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    struct stm32_spi *spi_drv =  rt_container_of(hspi, struct stm32_spi, handle);
    rt_completion_done(&spi_drv->cpt);
}

/**
 * @brief Handle STM32 HAL SPI asynchronous transfer errors.
 *
 * @param hspi STM32 HAL SPI handle that reported the error.
 */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    struct stm32_spi *spi_drv =  rt_container_of(hspi, struct stm32_spi, handle);
    LOG_W("%s error code 0x%08x", spi_drv->config->bus_name, hspi->ErrorCode);
    rt_completion_done(&spi_drv->cpt);
}
#endif /* BSP_SPI_USING_IRQ */

#if defined(SOC_SERIES_STM32F0)
/**
 * @brief Dispatch the combined SPI1 DMA RX/TX interrupt.
 */
void SPI1_DMA_RX_TX_IRQHandler(void)
{
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
    SPI1_DMA_TX_IRQHandler();
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
    SPI1_DMA_RX_IRQHandler();
#endif
}

/**
 * @brief Dispatch the combined SPI2 DMA RX/TX interrupt.
 */
void SPI2_DMA_RX_TX_IRQHandler(void)
{
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
    SPI2_DMA_TX_IRQHandler();
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
    SPI2_DMA_RX_IRQHandler();
#endif
}
#elif defined(SOC_SERIES_STM32G0)
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_USING_DMA)
/**
 * @brief Dispatch the combined SPI1 DMA RX/TX interrupt.
 */
void SPI1_DMA_RX_TX_IRQHandler(void)
{
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
    SPI1_DMA_TX_IRQHandler();
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
    SPI1_DMA_RX_IRQHandler();
#endif
}
#endif /* defined(BSP_USING_SPI1) && defined(BSP_SPI1_USING_DMA) */
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_USING_DMA)
/**
 * @brief Dispatch the combined SPI2 DMA RX/TX interrupt.
 */
void SPI2_DMA_RX_TX_IRQHandler(void)
{
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
    SPI2_DMA_TX_IRQHandler();
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
    SPI2_DMA_RX_IRQHandler();
#endif
}
#endif /* defined(BSP_USING_SPI2) && defined(BSP_SPI2_USING_DMA) */
#if defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx)
#if defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3)
/**
 * @brief Dispatch the shared SPI2/SPI3 peripheral interrupt.
 */
void SPI2_3_IRQHandler(void)
{
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_USING_IRQ)
    SPI2_IRQHandler();
#endif
#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_USING_IRQ)
    SPI3_IRQHandler();
#endif
}
#endif /* defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) */
#endif /* defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx) */
#endif /* defined(SOC_SERIES_STM32F0) */

/**
 * @brief Initialize the STM32 SPI driver during board startup.
 *
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
int rt_hw_spi_init(void)
{
#ifdef BSP_SPI_USING_IRQ
    stm32_get_xfer_info();
#endif /* BSP_SPI_USING_IRQ */
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_HARDWARE_SPI */
#endif /* BSP_USING_SPI */

