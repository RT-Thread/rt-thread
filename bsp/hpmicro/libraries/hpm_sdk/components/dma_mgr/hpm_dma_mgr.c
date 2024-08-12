/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <string.h>
#include "hpm_dma_mgr.h"
#include "hpm_soc.h"

/*****************************************************************************************************************
 *
 *  Definitions
 *
 *****************************************************************************************************************/

typedef struct _dma_instance_info {
    DMA_Type *base;
    int32_t irq_num;
} dma_chn_info_t;

/**
 * @brief DMA Channel Context Structure
 */
typedef struct _dma_channel_context {
    bool is_allocated;                               /**< Whether DMA channel was allocated */
    void *tc_cb_data_ptr;                            /**< User data required by transfer complete callback */
    void *half_tc_cb_data_ptr;                       /**< User data required by half transfer complete callback */
    void *error_cb_data_ptr;                         /**< User data required by error callback */
    void *abort_cb_data_ptr;                         /**< User data required by abort callback */
    dma_mgr_chn_cb_t tc_cb;                          /**< DMA channel transfer complete callback */
    dma_mgr_chn_cb_t half_tc_cb;                     /**< DMA channel half transfer complete callback */
    dma_mgr_chn_cb_t error_cb;                       /**< DMA channel error callback */
    dma_mgr_chn_cb_t abort_cb;                       /**< DMA channel abort callback */
} dma_chn_context_t;

/**
 * @brief DMA Manager Context Structure
 *
 */
typedef struct _dma_mgr_context {
    dma_chn_info_t dma_instance[DMA_SOC_MAX_COUNT];                                  /**< DMA instances */
    dma_chn_context_t channels[DMA_SOC_MAX_COUNT][DMA_SOC_CHANNEL_NUM];              /**< Array of DMA channels */
} dma_mgr_context_t;


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
static dma_chn_context_t *dma_mgr_search_chn_context(const dma_resource_t *resource);

static uint32_t dma_mgr_enter_critical(void);
static void dma_mgr_exit_critical(uint32_t level);

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
static dma_mgr_context_t s_dma_mngr_ctx;
#define HPM_DMA_MGR (&s_dma_mngr_ctx)

/*****************************************************************************************************************
 *
 *  Codes
 *
 *****************************************************************************************************************/
void dma_mgr_isr_handler(DMA_Type *ptr, uint32_t instance)
{
    uint32_t int_disable_mask;
    uint32_t chn_int_stat;
    dma_chn_context_t *chn_ctx;

    for (uint8_t channel = 0; channel < DMA_SOC_CHANNEL_NUM; channel++) {
        int_disable_mask = dma_check_channel_interrupt_mask(ptr, channel);
        chn_int_stat = dma_check_transfer_status(ptr, channel);
        chn_ctx = &HPM_DMA_MGR->channels[instance][channel];

        if (((int_disable_mask & DMA_MGR_INTERRUPT_MASK_TC) == 0) && ((chn_int_stat & DMA_MGR_CHANNEL_STATUS_TC) != 0)) {
            if (chn_ctx->tc_cb != NULL) {
                chn_ctx->tc_cb(ptr, channel, chn_ctx->tc_cb_data_ptr);
            }
        }
        if (((int_disable_mask & DMA_MGR_INTERRUPT_MASK_HALF_TC) == 0) && ((chn_int_stat & DMA_MGR_CHANNEL_STATUS_HALF_TC) != 0)) {
            if (chn_ctx->half_tc_cb != NULL) {
                chn_ctx->half_tc_cb(ptr, channel, chn_ctx->half_tc_cb_data_ptr);
            }
        }
        if (((int_disable_mask & DMA_MGR_INTERRUPT_MASK_ERROR) == 0) && ((chn_int_stat & DMA_MGR_CHANNEL_STATUS_ERROR) != 0)) {
            if (chn_ctx->error_cb != NULL) {
                chn_ctx->error_cb(ptr, channel, chn_ctx->error_cb_data_ptr);
            }
        }
        if (((int_disable_mask & DMA_MGR_INTERRUPT_MASK_ABORT) == 0) && ((chn_int_stat & DMA_MGR_CHANNEL_STATUS_ABORT) != 0)) {
            if (chn_ctx->abort_cb != NULL) {
                chn_ctx->abort_cb(ptr, channel, chn_ctx->abort_cb_data_ptr);
            }
        }
    }
}

void dma0_isr(void)
{
    dma_mgr_isr_handler(HPM_HDMA, 0);
}

#if defined(DMA_SOC_MAX_COUNT) && (DMA_SOC_MAX_COUNT > 1)
void dma1_isr(void)
{
    dma_mgr_isr_handler(HPM_XDMA, 1);
}
#endif

static uint32_t dma_mgr_enter_critical(void)
{
    return disable_global_irq(CSR_MSTATUS_MIE_MASK);
}

static void dma_mgr_exit_critical(uint32_t level)
{
    restore_global_irq(level);
}

void dma_mgr_init(void)
{
    (void) memset(HPM_DMA_MGR, 0, sizeof(*HPM_DMA_MGR));
    HPM_DMA_MGR->dma_instance[0].base = HPM_HDMA,
    HPM_DMA_MGR->dma_instance[0].irq_num = IRQn_HDMA;
 #if defined(DMA_SOC_MAX_COUNT) && (DMA_SOC_MAX_COUNT > 1)
    HPM_DMA_MGR->dma_instance[1].base = HPM_XDMA;
    HPM_DMA_MGR->dma_instance[1].irq_num = IRQn_XDMA;
 #endif
}

hpm_stat_t dma_mgr_request_resource(dma_resource_t *resource)
{
    hpm_stat_t status;

    if (resource == NULL) {
        status = status_invalid_argument;
    } else {
        uint32_t instance;
        uint32_t channel;
        bool has_found = false;
        uint32_t level = dma_mgr_enter_critical();
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
            status = status_dma_mgr_no_resource;
        }

        dma_mgr_exit_critical(level);
    }

    return status;
}

static dma_chn_context_t *dma_mgr_search_chn_context(const dma_resource_t *resource)
{
    dma_chn_context_t *chn_ctx = NULL;

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
            if (HPM_DMA_MGR->channels[instance][channel].is_allocated) {
                chn_ctx = &HPM_DMA_MGR->channels[instance][channel];
            }
        }
    }

    return chn_ctx;
}

hpm_stat_t dma_mgr_release_resource(const dma_resource_t *resource)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        uint32_t level = dma_mgr_enter_critical();
        chn_ctx->is_allocated = false;
        chn_ctx->tc_cb_data_ptr = NULL;
        chn_ctx->half_tc_cb_data_ptr = NULL;
        chn_ctx->error_cb_data_ptr = NULL;
        chn_ctx->abort_cb_data_ptr = NULL;
        chn_ctx->tc_cb = NULL;
        chn_ctx->half_tc_cb = NULL;
        chn_ctx->error_cb = NULL;
        chn_ctx->abort_cb = NULL;
        status = status_success;
        dma_mgr_exit_critical(level);
    }
    return status;
}

hpm_stat_t dma_mgr_enable_dma_irq_with_priority(const dma_resource_t *resource, uint32_t priority)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        intc_m_enable_irq_with_priority(resource->irq_num, priority);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_disable_dma_irq(const dma_resource_t *resource)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        intc_m_disable_irq(resource->irq_num);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_install_chn_tc_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        chn_ctx->tc_cb_data_ptr = user_data;
        chn_ctx->tc_cb = callback;
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_install_chn_half_tc_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        chn_ctx->half_tc_cb_data_ptr = user_data;
        chn_ctx->half_tc_cb = callback;
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_install_chn_error_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        chn_ctx->error_cb_data_ptr = user_data;
        chn_ctx->error_cb = callback;
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_install_chn_abort_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        chn_ctx->abort_cb_data_ptr = user_data;
        chn_ctx->abort_cb = callback;
        status = status_success;
    }
    return status;
}

void dma_mgr_get_default_chn_config(dma_mgr_chn_conf_t *config)
{
    config->en_dmamux = false;
    config->dmamux_src = 0;
    config->priority = DMA_MGR_CHANNEL_PRIORITY_LOW;
    config->src_burst_size = DMA_MGR_NUM_TRANSFER_PER_BURST_1T;
    config->src_mode = DMA_MGR_HANDSHAKE_MODE_NORMAL;
    config->dst_mode = DMA_MGR_HANDSHAKE_MODE_NORMAL;
    config->src_width = DMA_MGR_TRANSFER_WIDTH_BYTE;
    config->dst_width = DMA_MGR_TRANSFER_WIDTH_BYTE;
    config->src_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_INCREMENT;
    config->dst_addr_ctrl = DMA_MGR_ADDRESS_CONTROL_INCREMENT;
    config->src_addr = 0;
    config->dst_addr = 0;
    config->size_in_byte = 0;
    config->linked_ptr = 0;
    config->interrupt_mask = DMA_MGR_INTERRUPT_MASK_ALL;
    config->en_infiniteloop = false;
    config->handshake_opt = DMA_MGR_HANDSHAKE_OPT_ONE_BURST;
    config->burst_opt = DMA_MGR_SRC_BURST_OPT_STANDAND_SIZE;
    config->en_src_burst_in_fixed_trans = false;
    config->en_dst_burst_in_fixed_trans = false;
    config->swap_mode = DMA_MGR_SWAP_MODE_TABLE;
    config->swap_table = 0;
}

hpm_stat_t dma_mgr_setup_channel(const dma_resource_t *resource, dma_mgr_chn_conf_t *config)
{
    hpm_stat_t status;
    uint32_t dmamux_ch;
    dma_channel_config_t dma_config;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dmamux_ch = DMA_SOC_CHN_TO_DMAMUX_CHN(resource->base, resource->channel);
        dmamux_config(HPM_DMAMUX, dmamux_ch, config->dmamux_src, config->en_dmamux);
        dma_config.priority = config->priority;
        dma_config.src_burst_size = config->src_burst_size;
        dma_config.src_mode = config->src_mode;
        dma_config.dst_mode = config->dst_mode;
        dma_config.src_width = config->src_width;
        dma_config.dst_width = config->dst_width;
        dma_config.src_addr_ctrl = config->src_addr_ctrl;
        dma_config.dst_addr_ctrl = config->dst_addr_ctrl;
        dma_config.src_addr = config->src_addr;
        dma_config.dst_addr = config->dst_addr;
        dma_config.size_in_byte = config->size_in_byte;
        dma_config.linked_ptr = config->linked_ptr;
        dma_config.interrupt_mask = config->interrupt_mask;
#if defined(DMA_MGR_HAS_INFINITE_LOOP) && DMA_MGR_HAS_INFINITE_LOOP
        dma_config.en_infiniteloop = config->en_infiniteloop;
#endif
#if defined(DMA_MGR_HAS_HANDSHAKE_OPT) && DMA_MGR_HAS_HANDSHAKE_OPT
        dma_config.handshake_opt = config->handshake_opt;
#endif
#if defined(DMA_MGR_HAS_BURST_OPT) && DMA_MGR_HAS_BURST_OPT
        dma_config.burst_opt = config->burst_opt;
#endif
#if defined(DMA_MGR_HAS_BURST_IN_FIXED_TRANS) && DMA_MGR_HAS_BURST_IN_FIXED_TRANS
        dma_config.en_src_burst_in_fixed_trans = config->en_src_burst_in_fixed_trans;
        dma_config.en_dst_burst_in_fixed_trans = config->en_dst_burst_in_fixed_trans;
#endif
#if defined(DMA_MGR_HAS_BYTE_ORDER_SWAP) && DMA_MGR_HAS_BYTE_ORDER_SWAP
        dma_config.swap_mode = config->swap_mode;
        dma_config.swap_table = config->swap_table;
#endif
        status = dma_setup_channel(resource->base, resource->channel, &dma_config, false);
    }
    return status;
}

hpm_stat_t dma_mgr_config_linked_descriptor(const dma_resource_t *resource, dma_mgr_chn_conf_t *config, dma_mgr_linked_descriptor_t *descriptor)
{
    hpm_stat_t status;
    dma_channel_config_t dma_config;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_config.priority = config->priority;
        dma_config.src_burst_size = config->src_burst_size;
        dma_config.src_mode = config->src_mode;
        dma_config.dst_mode = config->dst_mode;
        dma_config.src_width = config->src_width;
        dma_config.dst_width = config->dst_width;
        dma_config.src_addr_ctrl = config->src_addr_ctrl;
        dma_config.dst_addr_ctrl = config->dst_addr_ctrl;
        dma_config.src_addr = config->src_addr;
        dma_config.dst_addr = config->dst_addr;
        dma_config.size_in_byte = config->size_in_byte;
        dma_config.linked_ptr = config->linked_ptr;
        dma_config.interrupt_mask = config->interrupt_mask;
#if defined(DMA_MGR_HAS_INFINITE_LOOP) && DMA_MGR_HAS_INFINITE_LOOP
        dma_config.en_infiniteloop = config->en_infiniteloop;
#endif
#if defined(DMA_MGR_HAS_HANDSHAKE_OPT) && DMA_MGR_HAS_HANDSHAKE_OPT
        dma_config.handshake_opt = config->handshake_opt;
#endif
#if defined(DMA_MGR_HAS_BURST_OPT) && DMA_MGR_HAS_BURST_OPT
        dma_config.burst_opt = config->burst_opt;
#endif
#if defined(DMA_MGR_HAS_BURST_IN_FIXED_TRANS) && DMA_MGR_HAS_BURST_IN_FIXED_TRANS
        dma_config.en_src_burst_in_fixed_trans = config->en_src_burst_in_fixed_trans;
        dma_config.en_dst_burst_in_fixed_trans = config->en_dst_burst_in_fixed_trans;
#endif
#if defined(DMA_MGR_HAS_BYTE_ORDER_SWAP) && DMA_MGR_HAS_BYTE_ORDER_SWAP
        dma_config.swap_mode = config->swap_mode;
        dma_config.swap_table = config->swap_table;
#endif
        status = dma_config_linked_descriptor(resource->base, (dma_linked_descriptor_t *)descriptor, resource->channel, &dma_config);
    }
    return status;
}

hpm_stat_t dma_mgr_enable_channel(const dma_resource_t *resource)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        status = dma_enable_channel(resource->base, resource->channel);
    }
    return status;
}

hpm_stat_t dma_mgr_disable_channel(const dma_resource_t *resource)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_disable_channel(resource->base, resource->channel);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_check_chn_enable(const dma_resource_t *resource, bool *enable)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        *enable = dma_channel_is_enable(resource->base, resource->channel);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_enable_chn_irq(const dma_resource_t *resource, uint32_t irq_mask)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_enable_channel_interrupt(resource->base, resource->channel, irq_mask);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_disable_chn_irq(const dma_resource_t *resource, uint32_t irq_mask)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_disable_channel_interrupt(resource->base, resource->channel, irq_mask);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_priority(const dma_resource_t *resource, uint8_t priority)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_priority(resource->base, resource->channel, priority);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_src_work_mode(const dma_resource_t *resource, uint8_t mode)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_source_work_mode(resource->base, resource->channel, mode);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_dst_work_mode(const dma_resource_t *resource, uint8_t mode)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_destination_work_mode(resource->base, resource->channel, mode);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_src_burst_size(const dma_resource_t *resource, uint8_t burstsize)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_source_burst_size(resource->base, resource->channel, burstsize);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_get_chn_remaining_transize(const dma_resource_t *resource, uint32_t *size)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        *size = dma_get_remaining_transfer_size(resource->base, resource->channel);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_transize(const dma_resource_t *resource, uint32_t size)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_transfer_size(resource->base, resource->channel, size);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_src_width(const dma_resource_t *resource, uint8_t width)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_source_width(resource->base, resource->channel, width);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_dst_width(const dma_resource_t *resource, uint8_t width)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_destination_width(resource->base, resource->channel, width);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_src_addr(const dma_resource_t *resource, uint32_t addr)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_source_address(resource->base, resource->channel, addr);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_dst_addr(const dma_resource_t *resource, uint32_t addr)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_destination_address(resource->base, resource->channel, addr);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_src_addr_ctrl(const dma_resource_t *resource, uint8_t addr_ctrl)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_source_address_ctrl(resource->base, resource->channel, addr_ctrl);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_dst_addr_ctrl(const dma_resource_t *resource, uint8_t addr_ctrl)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_set_destination_address_ctrl(resource->base, resource->channel, addr_ctrl);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_infinite_loop_mode(const dma_resource_t *resource, bool infinite_loop)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
#if defined(DMA_MGR_HAS_INFINITE_LOOP) && DMA_MGR_HAS_INFINITE_LOOP
        dma_set_infinite_loop_mode(resource->base, resource->channel, infinite_loop);
        status = status_success;
#else
        (void)infinite_loop;
        status = status_fail;
#endif
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_src_busrt_option(const dma_resource_t *resource, uint8_t burst_opt)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
#if defined(DMA_MGR_HAS_HANDSHAKE_OPT) && DMA_MGR_HAS_HANDSHAKE_OPT
        dma_set_src_busrt_option(resource->base, resource->channel, burst_opt);
        status = status_success;
#else
        (void)burst_opt;
        status = status_fail;
#endif
    }
    return status;
}

hpm_stat_t dma_mgr_set_chn_handshake_option(const dma_resource_t *resource, uint8_t handshake_opt)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
#if defined(DMA_MGR_HAS_HANDSHAKE_OPT) && DMA_MGR_HAS_HANDSHAKE_OPT
        dma_set_handshake_option(resource->base, resource->channel, handshake_opt);
        status = status_success;
#else
        (void)handshake_opt;
        status = status_fail;
#endif
    }
    return status;
}

hpm_stat_t dma_mgr_abort_chn_transfer(const dma_resource_t *resource)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
        dma_abort_channel(resource->base, 1u << resource->channel);
        status = status_success;
    }
    return status;
}

hpm_stat_t dma_mgr_check_chn_transfer_status(const dma_resource_t *resource, uint32_t *status)
{
    hpm_stat_t stat;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        stat = status_invalid_argument;
    } else {
        *status = dma_check_transfer_status(resource->base, resource->channel);
        stat = status_success;
    }
    return stat;
}

hpm_stat_t dma_mgr_set_source_burst_in_fixed_transize_enable(const dma_resource_t *resource, bool enable)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
#if defined(DMA_MGR_HAS_BURST_IN_FIXED_TRANS) && DMA_MGR_HAS_BURST_IN_FIXED_TRANS
        dma_set_source_burst_in_fixed_transize_enable(resource->base, resource->channel, enable);
        status = status_success;
#else
        (void)enable;
        status = status_fail;
#endif
    }
    return status;
}

hpm_stat_t dma_mgr_set_destination_burst_in_fix_transize_enable(const dma_resource_t *resource, bool enable)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
#if defined(DMA_MGR_HAS_BURST_IN_FIXED_TRANS) && DMA_MGR_HAS_BURST_IN_FIXED_TRANS
        dma_set_destination_burst_in_fixed_transize_enable(resource->base, resource->channel, enable);
        status = status_success;
#else
        (void)enable;
        status = status_fail;
#endif
    }
    return status;
}

hpm_stat_t dma_mgr_set_swap_mode(const dma_resource_t *resource, uint8_t swap_mode)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
#if defined(DMA_MGR_HAS_BYTE_ORDER_SWAP) && DMA_MGR_HAS_BYTE_ORDER_SWAP
        dma_set_swap_mode(resource->base, resource->channel, swap_mode);
        status = status_success;
#else
        (void)swap_mode;
        status = status_fail;
#endif
    }
    return status;
}

hpm_stat_t dma_mgr_set_swap_table(const dma_resource_t *resource, uint32_t swap_table)
{
    hpm_stat_t status;

    dma_chn_context_t *chn_ctx = dma_mgr_search_chn_context(resource);

    if (chn_ctx == NULL) {
        status = status_invalid_argument;
    } else {
#if defined(DMA_MGR_HAS_BYTE_ORDER_SWAP) && DMA_MGR_HAS_BYTE_ORDER_SWAP
        dma_set_swap_table(resource->base, resource->channel, swap_table);
        status = status_success;
#else
        (void)swap_table;
        status = status_fail;
#endif
    }
    return status;
}
