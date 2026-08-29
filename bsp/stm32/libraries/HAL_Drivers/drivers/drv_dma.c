/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-13     wdfk-prog    Add STM32 DMA common helpers
 * 2026-08-28     moment-NEW   Dispatch DMA/BDMA/GPDMA by descriptor type
 */

/**
 * @file drv_dma.c
 * @brief STM32 DMA common helper layer for peripheral drivers.
 */

#include "drv_dma.h"

// #define DRV_DEBUG
#define LOG_TAG "drv.dma"
#include <drv_log.h>
/*
 * DMA-capable BSPs are expected to enable HAL_DMA_MODULE_ENABLED in the
 * STM32 HAL configuration, so keep the common DMA helper in the build.
 */
#ifdef HAL_DMA_MODULE_ENABLED

/**
 * @brief Get the controller type name for logging.
 *
 * The name follows the descriptor type so DMA, BDMA and GPDMA share one
 * helper path while still producing a distinct log tag.
 */
#define STM32_DMA_TYPE_NAME(dma_config)                                              \
    (((dma_config)->common.type == STM32_DMA_TYPE_GPDMA) ? "gpdma" :                 \
     ((dma_config)->common.type == STM32_DMA_TYPE_BDMA)  ? "bdma"  : "dma")

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
 * @brief Enable the clock of one DMA/BDMA controller and wait for the write to complete.
 * @param dma_rcc RCC enable bit of the DMA/BDMA controller.
 * @param type Type of the DMA/BDMA controller.
 */
static void stm32_dma_enable_clock(rt_uint32_t dma_rcc,
                                   stm32_dma_type type)
{
    rt_uint32_t tmpreg = 0x00U;

    /*
     * STM32H7 BDMA lives on AHB4. Enable that clock and return so the
     * DMA1/DMA2 AHB1 path below is not used for a BDMA endpoint.
     */
#if defined(BSP_USING_BDMA) && defined(SOC_SERIES_STM32H7)
    if (type == STM32_DMA_TYPE_BDMA)
    {
        SET_BIT(RCC->AHB4ENR, dma_rcc);
        tmpreg = READ_BIT(RCC->AHB4ENR, dma_rcc);
        UNUSED(tmpreg);
        return;
    }
#endif /* defined(BSP_USING_BDMA) && defined(SOC_SERIES_STM32H7) */
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
#if (defined(SOC_SERIES_STM32F1) && defined(DMA2_Channel4_5_IRQn)) || (defined(SOC_SERIES_STM32L0) && defined(DMA1_Channel4_5_6_7_IRQn)) || (defined(SOC_SERIES_STM32G0) && defined(DMA1_Channel2_3_IRQn)) || (defined(SOC_SERIES_STM32F0) && (defined(DMA1_Channel2_3_IRQn) || defined(DMA1_Channel4_5_IRQn) || defined(DMA1_Channel4_5_6_7_IRQn)))
#define STM32_DMA_HAS_SHARED_IRQ_REFCNT
#define STM32_DMA_IRQ_SLOT_COUNT ((rt_uint32_t)(sizeof(NVIC->ISER) / sizeof(NVIC->ISER[0]) * 32U))

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
#if defined(DMA1_Channel2_3_IRQn)
    if (dma_irq == DMA1_Channel2_3_IRQn)
    {
        return RT_TRUE;
    }
#endif /* defined(DMA1_Channel2_3_IRQn) */
#if defined(DMA1_Channel4_5_IRQn)
    if (dma_irq == DMA1_Channel4_5_IRQn)
    {
        return RT_TRUE;
    }
#endif /* defined(DMA1_Channel4_5_IRQn) */
#if defined(DMA1_Channel4_5_6_7_IRQn)
    if (dma_irq == DMA1_Channel4_5_6_7_IRQn)
    {
        return RT_TRUE;
    }
#endif /* defined(DMA1_Channel4_5_6_7_IRQn) */
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
 * @brief Apply fields shared by classic DMA, BDMA and GPDMA to a HAL handle.
 * @param dma_handle DMA handle to update.
 * @param common Common configuration fields shared by all controller types.
 */
static void stm32_dma_apply_common_config(DMA_HandleTypeDef *dma_handle,
                                          const struct stm32_dma_config_common *common)
{
    dma_handle->Instance = common->Instance;
#if defined(STM32_DMA_USES_REQUEST)
    dma_handle->Init.Request = common->request;
#endif /* defined(STM32_DMA_USES_REQUEST) */
    dma_handle->Init.Direction = common->direction;
    dma_handle->Init.Mode = common->mode;
    dma_handle->Init.Priority = common->priority;
}

/**
 * @brief Apply one static descriptor to a HAL DMA handle.
 *
 * Software dispatch uses @ref stm32_dma_config_common.type. HAL member names
 * that exist only on classic DMA or only on GPDMA are still guarded by
 * @ref STM32_DMA_USES_GPDMA so unused cases compile as empty on that series.
 */
static void stm32_dma_apply_config(DMA_HandleTypeDef *dma_handle,
                                   const struct stm32_dma_config *dma_config)
{
    stm32_dma_apply_common_config(dma_handle, &dma_config->common);

    switch (dma_config->common.type)
    {
    case STM32_DMA_TYPE_DMA:
    case STM32_DMA_TYPE_BDMA:
#if !defined(STM32_DMA_USES_GPDMA)
        dma_handle->Init.PeriphInc = dma_config->config.classic.periph_inc;
        dma_handle->Init.MemInc = dma_config->config.classic.mem_inc;
        dma_handle->Init.PeriphDataAlignment = dma_config->config.classic.periph_data_alignment;
        dma_handle->Init.MemDataAlignment = dma_config->config.classic.mem_data_alignment;
        if (dma_config->common.type == STM32_DMA_TYPE_DMA)
        {
#if defined(STM32_DMA_USES_CHANNEL)
            dma_handle->Init.Channel = dma_config->config.classic.channel;
#endif /* defined(STM32_DMA_USES_CHANNEL) */
#if defined(STM32_DMA_SUPPORTS_FIFO)
            dma_handle->Init.FIFOMode = dma_config->config.classic.fifo_mode;
            dma_handle->Init.FIFOThreshold = dma_config->config.classic.fifo_threshold;
            dma_handle->Init.MemBurst = dma_config->config.classic.mem_burst;
            dma_handle->Init.PeriphBurst = dma_config->config.classic.periph_burst;
#endif /* defined(STM32_DMA_SUPPORTS_FIFO) */
        }
#endif /* !defined(STM32_DMA_USES_GPDMA) */
        break;
    case STM32_DMA_TYPE_GPDMA:
#if defined(STM32_DMA_USES_GPDMA)
        dma_handle->Init.BlkHWRequest = dma_config->config.gpdma.blk_hw_request;
        dma_handle->Init.SrcInc = dma_config->config.gpdma.src_inc;
        dma_handle->Init.DestInc = dma_config->config.gpdma.dest_inc;
        dma_handle->Init.SrcDataWidth = dma_config->config.gpdma.src_data_width;
        dma_handle->Init.DestDataWidth = dma_config->config.gpdma.dest_data_width;
        dma_handle->Init.SrcBurstLength = dma_config->config.gpdma.src_burst_length;
        dma_handle->Init.DestBurstLength = dma_config->config.gpdma.dest_burst_length;
        dma_handle->Init.TransferAllocatedPort = dma_config->config.gpdma.transfer_allocated_port;
        dma_handle->Init.TransferEventMode = dma_config->config.gpdma.transfer_event_mode;
#endif /* defined(STM32_DMA_USES_GPDMA) */
        break;
    default:
        break;
    }
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
    stm32_dma_enable_clock(dma_config->common.dma_rcc, dma_config->common.type);
    stm32_dma_apply_config(dma_handle, dma_config);

    LOG_D("%s init, dma=%p, irq=%d",
          STM32_DMA_TYPE_NAME(dma_config),
          dma_handle->Instance, dma_config->common.dma_irq);

    if (HAL_DMA_DeInit(dma_handle) != HAL_OK)
    {
        LOG_E("%s deinit failed, dma=%p, irq=%d",
              STM32_DMA_TYPE_NAME(dma_config),
              dma_handle->Instance, dma_config->common.dma_irq);
        return -RT_ERROR;
    }

    if (HAL_DMA_Init(dma_handle) != HAL_OK)
    {
        LOG_E("%s init failed, dma=%p, irq=%d",
              STM32_DMA_TYPE_NAME(dma_config),
              dma_handle->Instance, dma_config->common.dma_irq);
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

    stm32_dma_irq_get(dma_config->common.dma_irq, dma_config->common.preempt_priority, dma_config->common.sub_priority);

    LOG_D("%s setup, dma=%p, irq=%d",
          STM32_DMA_TYPE_NAME(dma_config),
          dma_handle->Instance, dma_config->common.dma_irq);

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

    stm32_dma_irq_put(dma_config->common.dma_irq);

    LOG_D("%s deinit, dma=%p, irq=%d",
          STM32_DMA_TYPE_NAME(dma_config),
          dma_handle->Instance, dma_config->common.dma_irq);

    if (abort_first)
    {
        if (HAL_DMA_Abort(dma_handle) != HAL_OK)
        {
            LOG_W("%s abort failed, continue deinit, dma=%p, irq=%d",
                  STM32_DMA_TYPE_NAME(dma_config),
                  dma_handle->Instance, dma_config->common.dma_irq);
        }
    }

    if (HAL_DMA_DeInit(dma_handle) != HAL_OK)
    {
        LOG_E("%s deinit failed, dma=%p, irq=%d",
              STM32_DMA_TYPE_NAME(dma_config),
              dma_handle->Instance, dma_config->common.dma_irq);
        return -RT_ERROR;
    }

    return RT_EOK;
}

#endif /* HAL_DMA_MODULE_ENABLED */
