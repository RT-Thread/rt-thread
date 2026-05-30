/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-13     wdfk-prog    Add STM32 DMA common helpers
 */

/**
 * @file drv_dma.c
 * @brief STM32 DMA common helper layer for peripheral drivers.
 */

#include "drv_dma.h"

// #define DRV_DEBUG
#define LOG_TAG             "drv.dma"
#include <drv_log.h>
/*
 * DMA-capable BSPs are expected to enable HAL_DMA_MODULE_ENABLED in the
 * STM32 HAL configuration, so keep the common DMA helper in the build.
 */
#ifdef HAL_DMA_MODULE_ENABLED

#if defined(STM32_DMA_USES_REQUEST)
/**
 * @brief Enable the DMAMUX clock when the current STM32 DMA path needs it.
 */
static void stm32_dma_enable_dmamux_clock(void)
{
#if defined(DMAMUX1) && defined(__HAL_RCC_DMAMUX1_CLK_ENABLE)
    __HAL_RCC_DMAMUX1_CLK_ENABLE();
#elif defined(DMAMUX) && defined(__HAL_RCC_DMAMUX_CLK_ENABLE)
    __HAL_RCC_DMAMUX_CLK_ENABLE();
#endif /* defined(DMAMUX1) && defined(__HAL_RCC_DMAMUX1_CLK_ENABLE) */
}
#endif /* defined(STM32_DMA_USES_REQUEST) */

/**
 * @brief Enable the clock of one DMA controller and wait for the write to complete.
 * @param dma_rcc RCC enable bit of the DMA controller.
 */
static void stm32_dma_enable_clock(rt_uint32_t dma_rcc)
{
    rt_uint32_t tmpreg = 0x00U;

#if defined(STM32_DMA_USES_RCC_AHBENR)
    SET_BIT(RCC->AHBENR, dma_rcc);
    tmpreg = READ_BIT(RCC->AHBENR, dma_rcc);
#elif defined(STM32_DMA_USES_RCC_MP_AHB2ENSETR)
    SET_BIT(RCC->MP_AHB2ENSETR, dma_rcc);
    tmpreg = READ_BIT(RCC->MP_AHB2ENSETR, dma_rcc);
#elif defined(STM32_DMA_USES_RCC_AHB1ENR)
    SET_BIT(RCC->AHB1ENR, dma_rcc);
    tmpreg = READ_BIT(RCC->AHB1ENR, dma_rcc);
#endif /* defined(STM32_DMA_USES_RCC_AHBENR) || defined(STM32_DMA_USES_RCC_MP_AHB2ENSETR) || defined(STM32_DMA_USES_RCC_AHB1ENR) */

#if defined(STM32_DMA_USES_REQUEST)
    stm32_dma_enable_dmamux_clock();
#endif /* defined(STM32_DMA_USES_REQUEST) */

    UNUSED(tmpreg);
}

/* Only a few STM32 families expose DMA requests on shared NVIC lines.
 * Use reference counting only for those known shared IRQ numbers so one
 * DMA client does not disable a line still used by another active client.
 * All other DMA IRQs keep the direct enable/disable behavior.
 */
#if (defined(SOC_SERIES_STM32F1) && defined(DMA2_Channel4_5_IRQn)) \
 || (defined(SOC_SERIES_STM32L0) && defined(DMA1_Channel4_5_6_7_IRQn)) \
 || (defined(SOC_SERIES_STM32G0) && defined(DMA1_Channel2_3_IRQn)) \
 || (defined(SOC_SERIES_STM32F0) && (defined(DMA1_Channel2_3_IRQn) || defined(DMA1_Channel4_5_IRQn) || defined(DMA1_Channel4_5_6_7_IRQn)))
#define STM32_DMA_HAS_SHARED_IRQ_REFCNT
#define STM32_DMA_IRQ_SLOT_COUNT    ((rt_uint32_t)(sizeof(NVIC->ISER) / sizeof(NVIC->ISER[0]) * 32U))

/**
 * @brief Reference count for each shared DMA IRQ line.
 */
static rt_uint16_t stm32_dma_irq_ref_count[STM32_DMA_IRQ_SLOT_COUNT];

/**
 * @brief Check whether one DMA IRQ number can index the local reference table.
 * @param dma_irq DMA IRQ number to validate.
 * @retval RT_TRUE The IRQ number maps to one valid table slot.
 * @retval RT_FALSE The IRQ number is negative or outside the table range.
 */
static rt_bool_t stm32_dma_irq_is_valid(IRQn_Type dma_irq)
{
    return ((int32_t)dma_irq >= 0) && ((rt_uint32_t)dma_irq < STM32_DMA_IRQ_SLOT_COUNT);
}

/**
 * @brief Check whether one DMA IRQ line is shared and needs reference counting.
 * @param dma_irq DMA IRQ number to inspect.
 * @retval RT_TRUE The IRQ line is shared by multiple DMA endpoints.
 * @retval RT_FALSE The IRQ line can use direct enable and disable handling.
 */
static rt_bool_t stm32_dma_irq_needs_refcount(IRQn_Type dma_irq)
{
#if defined(SOC_SERIES_STM32F1) && defined(DMA2_Channel4_5_IRQn)
    if (dma_irq == DMA2_Channel4_5_IRQn)
    {
        return RT_TRUE;
    }
#endif /* defined(SOC_SERIES_STM32F1) && defined(DMA2_Channel4_5_IRQn) */

#if defined(SOC_SERIES_STM32L0) && defined(DMA1_Channel4_5_6_7_IRQn)
    if (dma_irq == DMA1_Channel4_5_6_7_IRQn)
    {
        return RT_TRUE;
    }
#endif /* defined(SOC_SERIES_STM32L0) && defined(DMA1_Channel4_5_6_7_IRQn) */

#if defined(SOC_SERIES_STM32G0) && defined(DMA1_Channel2_3_IRQn)
    if (dma_irq == DMA1_Channel2_3_IRQn)
    {
        return RT_TRUE;
    }
#endif /* defined(SOC_SERIES_STM32G0) && defined(DMA1_Channel2_3_IRQn) */

#if defined(SOC_SERIES_STM32F0)
# if defined(DMA1_Channel2_3_IRQn)
    if (dma_irq == DMA1_Channel2_3_IRQn)
    {
        return RT_TRUE;
    }
# endif /* defined(DMA1_Channel2_3_IRQn) */
# if defined(DMA1_Channel4_5_IRQn)
    if (dma_irq == DMA1_Channel4_5_IRQn)
    {
        return RT_TRUE;
    }
# endif /* defined(DMA1_Channel4_5_IRQn) */
# if defined(DMA1_Channel4_5_6_7_IRQn)
    if (dma_irq == DMA1_Channel4_5_6_7_IRQn)
    {
        return RT_TRUE;
    }
# endif /* defined(DMA1_Channel4_5_6_7_IRQn) */
#endif /* defined(SOC_SERIES_STM32F0) */

    return RT_FALSE;
}
#endif /* shared DMA IRQ families */

/**
 * @brief Enable one DMA IRQ line and apply the requested NVIC priority.
 * @param dma_irq DMA IRQ number to enable.
 * @param preempt_priority NVIC preempt priority for the DMA IRQ.
 * @param sub_priority NVIC subpriority for the DMA IRQ.
 */
static void stm32_dma_irq_get(IRQn_Type dma_irq,
                              rt_uint8_t preempt_priority,
                              rt_uint8_t sub_priority)
{
#if defined(STM32_DMA_HAS_SHARED_IRQ_REFCNT)
    rt_base_t level;

    if (stm32_dma_irq_needs_refcount(dma_irq) && stm32_dma_irq_is_valid(dma_irq))
    {
        level = rt_hw_interrupt_disable();
        if (stm32_dma_irq_ref_count[(rt_uint32_t)dma_irq] == 0U)
        {
            HAL_NVIC_SetPriority(dma_irq, preempt_priority, sub_priority);
            HAL_NVIC_EnableIRQ(dma_irq);
        }
        stm32_dma_irq_ref_count[(rt_uint32_t)dma_irq]++;
        rt_hw_interrupt_enable(level);
        return;
    }
#endif /* defined(STM32_DMA_HAS_SHARED_IRQ_REFCNT) */

    HAL_NVIC_SetPriority(dma_irq, preempt_priority, sub_priority);
    HAL_NVIC_EnableIRQ(dma_irq);
}

/**
 * @brief Release one DMA IRQ line and disable it when no user remains.
 * @param dma_irq DMA IRQ number to release.
 */
static void stm32_dma_irq_put(IRQn_Type dma_irq)
{
#if defined(STM32_DMA_HAS_SHARED_IRQ_REFCNT)
    rt_base_t level;

    if (stm32_dma_irq_needs_refcount(dma_irq) && stm32_dma_irq_is_valid(dma_irq))
    {
        level = rt_hw_interrupt_disable();
        if (stm32_dma_irq_ref_count[(rt_uint32_t)dma_irq] > 0U)
        {
            stm32_dma_irq_ref_count[(rt_uint32_t)dma_irq]--;
            if (stm32_dma_irq_ref_count[(rt_uint32_t)dma_irq] == 0U)
            {
                HAL_NVIC_DisableIRQ(dma_irq);
            }
        }
        rt_hw_interrupt_enable(level);
        return;
    }
#endif /* defined(STM32_DMA_HAS_SHARED_IRQ_REFCNT) */

    HAL_NVIC_DisableIRQ(dma_irq);
}

/**
 * @brief Copy one static DMA descriptor into one HAL DMA handle.
 * @param dma_handle DMA handle to update.
 * @param dma_config Static DMA endpoint description.
 */
static void stm32_dma_apply_config(DMA_HandleTypeDef *dma_handle,
                                   const struct stm32_dma_config *dma_config)
{
    dma_handle->Instance = dma_config->Instance;
#if defined(STM32_DMA_USES_GPDMA)
    dma_handle->Init.Request = dma_config->request;
    dma_handle->Init.BlkHWRequest = dma_config->blk_hw_request;
    dma_handle->Init.Direction = dma_config->direction;
    dma_handle->Init.SrcInc = dma_config->src_inc;
    dma_handle->Init.DestInc = dma_config->dest_inc;
    dma_handle->Init.SrcDataWidth = dma_config->src_data_width;
    dma_handle->Init.DestDataWidth = dma_config->dest_data_width;
    dma_handle->Init.Priority = dma_config->priority;
    dma_handle->Init.SrcBurstLength = dma_config->src_burst_length;
    dma_handle->Init.DestBurstLength = dma_config->dest_burst_length;
    dma_handle->Init.TransferAllocatedPort = dma_config->transfer_allocated_port;
    dma_handle->Init.TransferEventMode = dma_config->transfer_event_mode;
    dma_handle->Init.Mode = dma_config->mode;
#else
#if defined(STM32_DMA_USES_CHANNEL)
    dma_handle->Init.Channel = dma_config->channel;
#endif /* defined(STM32_DMA_USES_CHANNEL) */
#if defined(STM32_DMA_USES_REQUEST)
    dma_handle->Init.Request = dma_config->request;
#endif /* defined(STM32_DMA_USES_REQUEST) */
    dma_handle->Init.Direction = dma_config->direction;
    dma_handle->Init.PeriphInc = dma_config->periph_inc;
    dma_handle->Init.MemInc = dma_config->mem_inc;
    dma_handle->Init.PeriphDataAlignment = dma_config->periph_data_alignment;
    dma_handle->Init.MemDataAlignment = dma_config->mem_data_alignment;
    dma_handle->Init.Mode = dma_config->mode;
    dma_handle->Init.Priority = dma_config->priority;
#if defined(STM32_DMA_SUPPORTS_FIFO)
    dma_handle->Init.FIFOMode = dma_config->fifo_mode;
    dma_handle->Init.FIFOThreshold = dma_config->fifo_threshold;
    dma_handle->Init.MemBurst = dma_config->mem_burst;
    dma_handle->Init.PeriphBurst = dma_config->periph_burst;
#endif /* defined(STM32_DMA_SUPPORTS_FIFO) */
#endif /* defined(STM32_DMA_USES_GPDMA) */
}

/**
 * @brief Enable one DMA controller, apply the static descriptor and initialize HAL state.
 * @param dma_handle DMA handle owned by one peripheral driver.
 * @param dma_config Board-level DMA endpoint description.
 * @retval RT_EOK Initialization succeeded.
 * @retval -RT_ERROR HAL initialization failed.
 */
rt_err_t stm32_dma_init(DMA_HandleTypeDef *dma_handle,
                        const struct stm32_dma_config *dma_config)
{
    RT_ASSERT(dma_handle != RT_NULL);
    RT_ASSERT(dma_config != RT_NULL);

    stm32_dma_enable_clock(dma_config->dma_rcc);
    stm32_dma_apply_config(dma_handle, dma_config);

    LOG_D("dma init, dma=%p, irq=%d", dma_handle->Instance, dma_config->dma_irq);

    if (HAL_DMA_DeInit(dma_handle) != HAL_OK)
    {
        LOG_E("dma deinit failed, dma=%p, irq=%d", dma_handle->Instance, dma_config->dma_irq);
        return -RT_ERROR;
    }

    if (HAL_DMA_Init(dma_handle) != HAL_OK)
    {
        LOG_E("dma init failed, dma=%p, irq=%d", dma_handle->Instance, dma_config->dma_irq);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief Initialize one DMA handle, attach it to the parent HAL handle and enable the DMA IRQ.
 * @param dma_handle DMA handle owned by one peripheral driver.
 * @param parent_handle Parent HAL handle, such as UART_HandleTypeDef or SPI_HandleTypeDef.
 * @param dma_slot Address of the parent handle DMA slot, such as &huart->hdmarx.
 * @param dma_config Board-level DMA endpoint description.
 * @retval RT_EOK Initialization succeeded.
 * @retval -RT_ERROR HAL initialization failed.
 */
rt_err_t stm32_dma_setup(DMA_HandleTypeDef *dma_handle,
                         void *parent_handle,
                         DMA_HandleTypeDef **dma_slot,
                         const struct stm32_dma_config *dma_config)
{
    rt_err_t result;

    result = stm32_dma_init(dma_handle, dma_config);
    if (result != RT_EOK)
    {
        return result;
    }

    if ((parent_handle != RT_NULL) && (dma_slot != RT_NULL))
    {
        *dma_slot = dma_handle;
        dma_handle->Parent = parent_handle;
    }

    stm32_dma_irq_get(dma_config->dma_irq, dma_config->preempt_priority, dma_config->sub_priority);

    LOG_D("dma setup, dma=%p, irq=%d", dma_handle->Instance, dma_config->dma_irq);

    return RT_EOK;
}

/**
 * @brief Disable one DMA IRQ, optionally abort the current transfer and de-initialize HAL state.
 * @param dma_handle DMA handle owned by one peripheral driver.
 * @param dma_config Board-level DMA endpoint description.
 * @param abort_first RT_TRUE aborts the ongoing transfer before HAL_DMA_DeInit().
 * @retval RT_EOK De-initialization succeeded.
 * @retval -RT_ERROR HAL de-initialization failed.
 */
rt_err_t stm32_dma_deinit(DMA_HandleTypeDef *dma_handle,
                          const struct stm32_dma_config *dma_config,
                          rt_bool_t abort_first)
{
    RT_ASSERT(dma_handle != RT_NULL);
    RT_ASSERT(dma_config != RT_NULL);

    stm32_dma_irq_put(dma_config->dma_irq);

    LOG_D("dma deinit, dma=%p, irq=%d", dma_handle->Instance, dma_config->dma_irq);

    if (abort_first)
    {
        if (HAL_DMA_Abort(dma_handle) != HAL_OK)
        {
            LOG_W("dma abort failed, continue deinit, dma=%p, irq=%d", dma_handle->Instance, dma_config->dma_irq);
        }
    }

    if (HAL_DMA_DeInit(dma_handle) != HAL_OK)
    {
        LOG_E("dma deinit failed, dma=%p, irq=%d", dma_handle->Instance, dma_config->dma_irq);
        return -RT_ERROR;
    }

    return RT_EOK;
}
#endif /* HAL_DMA_MODULE_ENABLED */
