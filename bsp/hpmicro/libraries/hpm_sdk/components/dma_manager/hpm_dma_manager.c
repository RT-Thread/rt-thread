/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <string.h>
#include "hpm_dma_manager.h"
#include "hpm_soc.h"

/*****************************************************************************************************************
 *
 *  Definitions
 *
 *****************************************************************************************************************/

typedef struct _dma_instance_info {
    DMA_Type *base;
    int32_t irq_num;
} dma_channel_info_t;

/**
 * @brief DMA Manager Context Structure
 *
 */
typedef struct _dma_manager_context {
    dma_channel_info_t dma_instance[DMA_SOC_MAX_COUNT];                                  /**< DMA instances */
    hpm_dma_channel_context_t channels[DMA_SOC_MAX_COUNT][DMA_SOC_CHANNEL_NUM]; /**< Array of DMA channels */
} hpm_dma_manager_context_t;

#define DMA_DISABLE_ALL_CHN_INT (DMA_INTERRUPT_MASK_ERROR | DMA_INTERRUPT_MASK_ABORT | DMA_INTERRUPT_MASK_TERMINAL_COUNT)


/*****************************************************************************************************************
 *
 *  Prototypes
 *
 *****************************************************************************************************************/

/**
 * @brief Search DMA channel context for specified DMA channel resource
 *
 * @param [in] resource DMA Channel resource
 * @return The request DMA channel context if resource is valid or NULL if resource in invalid
 */
static hpm_dma_channel_context_t *dma_manager_search_channel_context(const hpm_dma_resource_t *resource);

static uint32_t dma_manager_enter_critical(void);
static void dma_manager_exit_critical(uint32_t level);

static void dma0_isr(void);
SDK_DECLARE_EXT_ISR_M(IRQn_HDMA, dma0_isr);

#if defined(DMA_SOC_MAX_COUNT) && (DMA_SOC_MAX_COUNT > 1)
static void dma1_isr(void);
SDK_DECLARE_EXT_ISR_M(IRQn_XDMA, dma1_isr);
#endif

/*****************************************************************************************************************
 *
 *  Variables
 *
 *****************************************************************************************************************/
static hpm_dma_manager_context_t s_dma_mngr_ctx;
#define HPM_DMA_MGR (&s_dma_mngr_ctx)



/*****************************************************************************************************************
 *
 *  Codes
 *
 *****************************************************************************************************************/
static inline void handle_dma_isr(DMA_Type *ptr, uint32_t instance)
{
    for (uint8_t channel = 0; channel < DMA_SOC_CHANNEL_NUM; channel++) {
        uint32_t int_disable_mask = dma_check_channel_interrupt_mask(ptr, channel);
        /* If Channel interrupt is enabled */
        if (int_disable_mask != DMA_DISABLE_ALL_CHN_INT) {
            uint32_t chn_int_stat = dma_check_transfer_status(ptr, channel);
            if (chn_int_stat != DMA_CHANNEL_STATUS_ONGOING) {
                hpm_dma_channel_context_t *chn_ctx = &HPM_DMA_MGR->channels[instance][channel];
                if (chn_ctx->callback != NULL) {
                    chn_ctx->callback(ptr, channel, chn_ctx->user_data, chn_int_stat);
                }
            } /* end if (chn_int_stat != DMA_CHANNEL_STATUS_ONGOING) */
        } /* end if (int_disable_mask != DMA_DISABLE_ALL_CHN_INT) */
    } /* end for (uint8_t channel = 0; channel < DMA_SOC_MAX_COUNT; channel++) */
}

void dma0_isr(void)
{
    handle_dma_isr(HPM_HDMA, 0);
}

#if defined(DMA_SOC_MAX_COUNT) && (DMA_SOC_MAX_COUNT > 1)
void dma1_isr(void)
{
    handle_dma_isr(HPM_XDMA, 1);
}
#endif

static uint32_t dma_manager_enter_critical(void)
{
    uint32_t level = read_csr(CSR_MSTATUS);
    disable_global_irq(CSR_MSTATUS_MIE_MASK);
    return level;
}

static void dma_manager_exit_critical(uint32_t level)
{
    write_csr(CSR_MSTATUS, level);
}

/* See hpm_dma_manager.h for more details */
void dma_manager_init(void)
{
    (void) memset(HPM_DMA_MGR, 0, sizeof(*HPM_DMA_MGR));
    HPM_DMA_MGR->dma_instance[0].base = HPM_HDMA,
    HPM_DMA_MGR->dma_instance[0].irq_num = IRQn_HDMA;
 #if defined(DMA_SOC_MAX_COUNT) && (DMA_SOC_MAX_COUNT > 1)
    HPM_DMA_MGR->dma_instance[1].base = HPM_XDMA;
    HPM_DMA_MGR->dma_instance[1].irq_num = IRQn_XDMA;
 #endif
}

/* See hpm_dma_manager.h for more details */
hpm_stat_t dma_manager_request_resource(hpm_dma_resource_t *resource)
{
    hpm_stat_t status;

    if (resource == NULL) {
        status = status_invalid_argument;
    } else {
        uint32_t instance;
        uint32_t channel;
        bool has_found = false;
        uint32_t level = dma_manager_enter_critical();
        for (instance = 0; instance < DMA_SOC_MAX_COUNT; instance++) {
            for (channel = 0; channel < DMA_SOC_CHANNEL_NUM; channel++) {
                if (!HPM_DMA_MGR->channels[instance][channel].is_allocated) {
                    has_found = true;
                    break;
                }
            }
            if (has_found) {
                break;
            }
        }

        if (has_found) {
            HPM_DMA_MGR->channels[instance][channel].is_allocated = true;
            resource->base = HPM_DMA_MGR->dma_instance[instance].base;
            resource->channel = channel;
            resource->irq_num = HPM_DMA_MGR->dma_instance[instance].irq_num;
            status = status_success;
        } else {
            status = status_dma_manager_no_resource;
        }

        dma_manager_exit_critical(level);
    }

    return status;
}

static hpm_dma_channel_context_t *dma_manager_search_channel_context(const hpm_dma_resource_t *resource)
{
    hpm_dma_channel_context_t *channel_ctx = NULL;

    if ((resource != NULL) && (resource->channel < DMA_SOC_CHANNEL_NUM)) {
        uint32_t instance;
        uint32_t channel;
        bool has_found = false;
        for (instance = 0; instance < DMA_SOC_MAX_COUNT; instance++) {
            if (resource->base == HPM_DMA_MGR->dma_instance[instance].base) {
                has_found = true;
                break;
            }
        }

        channel = resource->channel;
        if (has_found) {
            channel_ctx = &HPM_DMA_MGR->channels[instance][channel];
        }
    }

    return channel_ctx;
}

/* See hpm_dma_manager.h for more details */
hpm_stat_t dma_manager_release_resource(const hpm_dma_resource_t *resource)
{
    hpm_stat_t status;

    hpm_dma_channel_context_t *channel_ctx = dma_manager_search_channel_context(resource);

    if (channel_ctx == NULL) {
        status = status_invalid_argument;
    } else {

        uint32_t level = dma_manager_enter_critical();
        channel_ctx->is_allocated = false;
        channel_ctx->user_data = NULL;
        channel_ctx->callback = NULL;
        status = status_success;
        dma_manager_exit_critical(level);
    }
    return status;
}

/* See hpm_dma_manager.h for more details */
hpm_stat_t dma_manager_enable_channel_interrupt(const hpm_dma_resource_t *resource, uint32_t irq_mask)
{
    hpm_stat_t status;

    hpm_dma_channel_context_t *channel_ctx = dma_manager_search_channel_context(resource);

    if (channel_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_enable_channel_interrupt(resource->base, resource->channel, irq_mask);
        status = status_success;
    }
    return status;
}

/* See hpm_dma_manager.h for more details */
hpm_stat_t dma_manager_disable_channel_interrupt(const hpm_dma_resource_t *resource, uint32_t irq_mask)
{
    hpm_stat_t status;

    hpm_dma_channel_context_t *channel_ctx = dma_manager_search_channel_context(resource);

    if (channel_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_disable_channel_interrupt(resource->base, resource->channel, irq_mask);
        status = status_success;
    }
    return status;
}


/* See hpm_dma_manager.h for more details */
hpm_stat_t dma_manager_enable_dma_interrupt(const hpm_dma_resource_t *resource, uint32_t priority)
{
    hpm_stat_t status;

    hpm_dma_channel_context_t *channel_ctx = dma_manager_search_channel_context(resource);

    if (channel_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        intc_m_enable_irq_with_priority(resource->irq_num, priority);
        status = status_success;
    }
    return status;
}

/* See hpm_dma_manager.h for more details */
hpm_stat_t dma_manager_disable_dma_interrupt(const hpm_dma_resource_t *resource)
{
    hpm_stat_t status;

    hpm_dma_channel_context_t *channel_ctx = dma_manager_search_channel_context(resource);

    if (channel_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        intc_m_disable_irq(resource->irq_num);
        status = status_success;
    }
    return status;
}


/* See hpm_dma_manager.h for more details */
hpm_stat_t dma_manager_install_interrupt_callback(const hpm_dma_resource_t *resource, hpm_dma_channel_callback_t callback, void *user_data)
{
    hpm_stat_t status;

    hpm_dma_channel_context_t *channel_ctx = dma_manager_search_channel_context(resource);

    if (channel_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        channel_ctx->user_data = user_data;
        channel_ctx->callback = callback;
        status = status_success;
    }
    return status;
}
