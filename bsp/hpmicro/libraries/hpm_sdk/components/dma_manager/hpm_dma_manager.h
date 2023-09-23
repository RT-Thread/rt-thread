/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_DMA_MANAGER_H
#define HPM_DMA_MANAGER_H

#include "hpm_common.h"
#ifdef CONFIG_HAS_HPMSDK_DMAV2
#include "hpm_dmav2_drv.h"
#else
#include "hpm_dma_drv.h"
#endif
#include "hpm_soc_feature.h"


#ifdef __cplusplus

extern "C" {
#endif


/**
 * @brief DMA Manager status codes
 */
enum {
    status_dma_manager_no_resource = MAKE_STATUS(status_group_dma_manager, 0), /**< No DMA resource available */
};

/**
 * @brief DMA Channel Interrupt callback
 *
 * @param [in] DMA base address
 * @param [in] channel DMA channel index
 * @param [in/out] user_data User Data context
 * @param [in] int_stat DMA interrupt status
 *             bit0 - DMA_CHANNEL_STATUS_ONGOING
 *             bit1 - DMA_CHANNEL_STATUS_ERROR
 *             bit2 - DMA_CHANNEL_STATUS_ABORT
 *             bit3 - DMA_CHANNEL_STATUS_TC
 */
typedef void (*hpm_dma_channel_callback_t)(DMA_Type *base, uint32_t channel, void *user_data,  uint32_t int_stat);

/**
 * @brief DMA Resource Structure
 */
typedef struct _dma_resource {
    DMA_Type *base;             /**< The DMA intance that the allocated channel belongs to */
    uint32_t channel;           /**< Channel index */
    int32_t irq_num;            /**< DMA IRQ number */
} hpm_dma_resource_t;

/**
 * @brief DMA Channel Context Structure
 */
typedef struct _dma_channel_context {
    bool is_allocated;                  /**< Whether DMA channel was allocated */
    void *user_data;                    /**< User data required by DMA channel callback */
    hpm_dma_channel_callback_t callback;/**< DMA channel callback */
} hpm_dma_channel_context_t;


/**
 * @brief Initialize DMA Manager Context
 */
void dma_manager_init(void);

/**
 * @brief Request DMA resource from DMA Manager
 *
 * @param [out] resource DMA resource
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if the parameter is invalid
 * @retval status_dma_manager_no_resource if all DMA channels are occupied;
 */
hpm_stat_t dma_manager_request_resource(hpm_dma_resource_t *resource);

/**
 * @brief Release DMA resource
 *
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if the parameter is invalid
 */
hpm_stat_t dma_manager_release_resource(const hpm_dma_resource_t *resource);


/**
 * @brief Enable Resource interrupt
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_manager_enable_channel_interrupt(const hpm_dma_resource_t *resource, uint32_t irq_mask);


/**
 * @brief Disable Resource interrupt
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_manager_disable_channel_interrupt(const hpm_dma_resource_t *resource, uint32_t irq_mask);


/**
 * @brief Enable DMa interrupt
 * @param [in] resource DMA resource
 * @param [in] priority Interrupt Priority
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_manager_enable_dma_interrupt(const hpm_dma_resource_t *resource, uint32_t priority);

/**
 * @brief Disable DMA interrupt
 *        NOTE: Each DMA instance consists of several DMA channels, disabling the DMA interrupt
 *              will disable the global DMA interrupt for all DMA channels. Please be aware of the
 *              impact
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_manager_disable_dma_interrupt(const hpm_dma_resource_t *resource);


/**
 * @brief Install Interrupt Callback for the DMA resource
 *
 * @param [in] resource DMA resource
 * @param [in] callback Interrupt callback for DMA resource
 * @param [in] user_data User data used in the callback
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_manager_install_interrupt_callback(const hpm_dma_resource_t *resource, hpm_dma_channel_callback_t callback, void *user_data);



#ifdef __cplusplus
}
#endif

#endif /* HPM_DMA_MANAGER_H */
