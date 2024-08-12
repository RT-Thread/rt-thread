/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_DMA_MGR_H
#define HPM_DMA_MGR_H

#include "hpm_common.h"
#include "hpm_dmamux_drv.h"
#include "hpm_dmamux_src.h"
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
#include "hpm_dmav2_drv.h"
#else
#include "hpm_dma_drv.h"
#endif
#include "hpm_soc_feature.h"

#ifdef HPMSOC_HAS_HPMSDK_DMAV2
#define DMA_MGR_HAS_INFINITE_LOOP        (1U)
#define DMA_MGR_HAS_HALF_TC_INT          (1U)
#define DMA_MGR_HAS_HANDSHAKE_OPT        (1U)
#define DMA_MGR_HAS_BURST_OPT            (1U)
#if defined(HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS) && (HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS == 1)
#define DMA_MGR_HAS_BURST_IN_FIXED_TRANS HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS
#else
#define DMA_MGR_HAS_BURST_IN_FIXED_TRANS 0
#endif
#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
#define DMA_MGR_HAS_BYTE_ORDER_SWAP HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP
#else
#define DMA_MGR_HAS_BYTE_ORDER_SWAP 0
#endif
#endif

#define DMA_MGR_CHANNEL_PRIORITY_LOW  DMA_CHANNEL_PRIORITY_LOW
#define DMA_MGR_CHANNEL_PRIORITY_HIGH DMA_CHANNEL_PRIORITY_HIGH

#define DMA_MGR_NUM_TRANSFER_PER_BURST_1T    DMA_NUM_TRANSFER_PER_BURST_1T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_2T    DMA_NUM_TRANSFER_PER_BURST_2T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_4T    DMA_NUM_TRANSFER_PER_BURST_4T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_8T    DMA_NUM_TRANSFER_PER_BURST_8T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_16T   DMA_NUM_TRANSFER_PER_BURST_16T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_32T   DMA_NUM_TRANSFER_PER_BURST_32T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_64T   DMA_NUM_TRANSFER_PER_BURST_64T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_128T  DMA_NUM_TRANSFER_PER_BURST_128T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_256T  DMA_NUM_TRANSFER_PER_BURST_256T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_512T  DMA_NUM_TRANSFER_PER_BURST_512T
#define DMA_MGR_NUM_TRANSFER_PER_BURST_1024T DMA_NUM_TRANSFER_PER_BURST_1024T

#define DMA_MGR_TRANSFER_WIDTH_BYTE        DMA_TRANSFER_WIDTH_BYTE
#define DMA_MGR_TRANSFER_WIDTH_HALF_WORD   DMA_TRANSFER_WIDTH_HALF_WORD
#define DMA_MGR_TRANSFER_WIDTH_WORD        DMA_TRANSFER_WIDTH_WORD
#define DMA_MGR_TRANSFER_WIDTH_DOUBLE_WORD DMA_TRANSFER_WIDTH_DOUBLE_WORD

#define DMA_MGR_HANDSHAKE_MODE_NORMAL    DMA_HANDSHAKE_MODE_NORMAL
#define DMA_MGR_HANDSHAKE_MODE_HANDSHAKE DMA_HANDSHAKE_MODE_HANDSHAKE

#define DMA_MGR_ADDRESS_CONTROL_INCREMENT DMA_ADDRESS_CONTROL_INCREMENT
#define DMA_MGR_ADDRESS_CONTROL_DECREMENT DMA_ADDRESS_CONTROL_DECREMENT
#define DMA_MGR_ADDRESS_CONTROL_FIXED     DMA_ADDRESS_CONTROL_FIXED

#if defined(DMA_MGR_HAS_BURST_OPT) && DMA_MGR_HAS_BURST_OPT
#define DMA_MGR_SRC_BURST_OPT_STANDAND_SIZE DMA_SRC_BURST_OPT_STANDAND_SIZE
#define DMA_MGR_SRC_BURST_OPT_CUSTOM_SIZE   DMA_SRC_BURST_OPT_CUSTOM_SIZE
#else
#define DMA_MGR_SRC_BURST_OPT_STANDAND_SIZE 0
#define DMA_MGR_SRC_BURST_OPT_CUSTOM_SIZE   0
#endif

#if defined(DMA_MGR_HAS_HANDSHAKE_OPT) && DMA_MGR_HAS_HANDSHAKE_OPT
#define DMA_MGR_HANDSHAKE_OPT_ONE_BURST    DMA_HANDSHAKE_OPT_ONE_BURST
#define DMA_MGR_HANDSHAKE_OPT_ALL_TRANSIZE DMA_HANDSHAKE_OPT_ALL_TRANSIZE
#else
#define DMA_MGR_HANDSHAKE_OPT_ONE_BURST    0
#define DMA_MGR_HANDSHAKE_OPT_ALL_TRANSIZE 0
#endif

#define DMA_MGR_CHANNEL_STATUS_ONGOING DMA_CHANNEL_STATUS_ONGOING
#define DMA_MGR_CHANNEL_STATUS_ERROR   DMA_CHANNEL_STATUS_ERROR
#define DMA_MGR_CHANNEL_STATUS_ABORT   DMA_CHANNEL_STATUS_ABORT
#define DMA_MGR_CHANNEL_STATUS_TC      DMA_CHANNEL_STATUS_TC
#if defined(DMA_MGR_HAS_HALF_TC_INT) && DMA_MGR_HAS_HALF_TC_INT
#define DMA_MGR_CHANNEL_STATUS_HALF_TC DMA_CHANNEL_STATUS_HALF_TC
#else
#define DMA_MGR_CHANNEL_STATUS_HALF_TC 0
#endif
#define DMA_MGR_INTERRUPT_MASK_NONE  DMA_INTERRUPT_MASK_NONE
#define DMA_MGR_INTERRUPT_MASK_ERROR DMA_INTERRUPT_MASK_ERROR
#define DMA_MGR_INTERRUPT_MASK_ABORT DMA_INTERRUPT_MASK_ABORT
#define DMA_MGR_INTERRUPT_MASK_TC    DMA_INTERRUPT_MASK_TERMINAL_COUNT
#if defined(DMA_MGR_HAS_HALF_TC_INT) && DMA_MGR_HAS_HALF_TC_INT
#define DMA_MGR_INTERRUPT_MASK_HALF_TC DMA_INTERRUPT_MASK_HALF_TC
#else
#define DMA_MGR_INTERRUPT_MASK_HALF_TC 0
#endif
#define DMA_MGR_INTERRUPT_MASK_ALL DMA_INTERRUPT_MASK_ALL

#if defined(DMA_MGR_HAS_BYTE_ORDER_SWAP) && DMA_MGR_HAS_BYTE_ORDER_SWAP
#define DMA_MGR_SWAP_MODE_TABLE     DMA_SWAP_MODE_TABLE
#define DMA_MGR_SWAP_MODE_BYTE      DMA_SWAP_MODE_BYTE
#define DMA_MGR_SWAP_MODE_HALF_WORD DMA_SWAP_MODE_HALF_WORD
#define DMA_MGR_SWAP_MODE_WORD      DMA_SWAP_MODE_WORD
#else
#define DMA_MGR_SWAP_MODE_TABLE     0
#define DMA_MGR_SWAP_MODE_BYTE      0
#define DMA_MGR_SWAP_MODE_HALF_WORD 0
#define DMA_MGR_SWAP_MODE_WORD      0
#endif

#ifdef __cplusplus

extern "C" {
#endif

/**
 * @brief DMA Manager status codes
 */
enum {
    status_dma_mgr_no_resource = MAKE_STATUS(status_group_dma_manager, 0), /**< No DMA resource available */
};

/**
 * @brief DMA Channel Interrupt callback
 *
 * @param [in] DMA base address
 * @param [in] channel DMA channel index
 * @param [in/out] cb_data_ptr callback Data pointer
 */
typedef void (*dma_mgr_chn_cb_t)(DMA_Type *base, uint32_t channel, void *cb_data_ptr);

/**
 * @brief DMA Resource Structure
 */
typedef struct _dma_resource {
    DMA_Type *base;   /**< The DMA intance that the allocated channel belongs to */
    uint32_t channel; /**< Channel index */
    int32_t irq_num;  /**< DMA IRQ number */
} dma_resource_t;

typedef struct hpm_dma_mgr_chn_conf {
    bool en_dmamux;                   /**< DMAMUX enable */
    uint8_t dmamux_src;               /**< DMAMUX source */
    uint8_t priority;                 /**< Channel priority */
    uint8_t src_burst_size;           /**< Source burst size */
    uint8_t src_mode;                 /**< Source work mode: 0-Normal, 1-Handshake */
    uint8_t dst_mode;                 /**< Destination work mode: 0-Normal, 1-Handshake  */
    uint8_t src_width;                /**< Source width */
    uint8_t dst_width;                /**< Destination width */
    uint8_t src_addr_ctrl;            /**< Source address control: 0-inc, 1-dec, 2-fix */
    uint8_t dst_addr_ctrl;            /**< Destination address control: 0-inc, 1-dec, 2-fix */
    uint16_t interrupt_mask;          /**< Interrupt mask */
    uint32_t src_addr;                /**< Source address */
    uint32_t dst_addr;                /**< Destination address */
    uint32_t linked_ptr;              /**< Next linked descriptor */
    uint32_t size_in_byte;            /**< Total size to be transferred in byte */
    bool en_infiniteloop;             /**< Infinite loop transfer enable. Attention: only DMAV2 support */
    uint8_t handshake_opt;            /**< Handshake transfer option. Attention: only DMAV2 support */
    uint8_t burst_opt;                /**< Burst size option. Attention: only DMAV2 support  */
    bool en_src_burst_in_fixed_trans; /**< Source address burst in fix transfer size enable, discard src_addr_ctrl setting. Attention: only DMAV2 support */
    bool en_dst_burst_in_fixed_trans; /**< Destination address burst in fix transfer size enable, discard dst_addr_ctrl setting. Attention: only DMAV2 support */
    uint8_t swap_mode;                /**< Swap Mode. Attention: only DMAV2 support */
    uint32_t swap_table;              /**< Swap Table. Attention: only DMAV2 support */
} dma_mgr_chn_conf_t;

typedef struct hpm_dma_mgr_linked_descriptor {
    uint32_t descriptor[8];
} dma_mgr_linked_descriptor_t;

/**
 * @brief DMA Manager ISR handler
 */
void dma_mgr_isr_handler(DMA_Type *ptr, uint32_t instance);

/**
 * @brief Initialize DMA Manager Context
 */
void dma_mgr_init(void);

/**
 * @brief Request DMA resource from DMA Manager
 *
 * @param [out] resource DMA resource
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if the parameter is invalid
 * @retval status_dma_mgr_no_resource if all DMA channels are occupied;
 */
hpm_stat_t dma_mgr_request_resource(dma_resource_t *resource);

/**
 * @brief Release DMA resource
 *
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if the parameter is invalid
 */
hpm_stat_t dma_mgr_release_resource(const dma_resource_t *resource);

/**
 * @brief Enable DMA interrupt with priority
 * @param [in] resource DMA resource
 * @param [in] priority Interrupt Priority
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_enable_dma_irq_with_priority(const dma_resource_t *resource, uint32_t priority);

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
hpm_stat_t dma_mgr_disable_dma_irq(const dma_resource_t *resource);

/**
 * @brief Install Interrupt Callback for DMA channel transfer complete
 *
 * @param [in] resource DMA resource
 * @param [in] callback Interrupt callback for DMA resource
 * @param [in] user_data User data used in the callback
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_install_chn_tc_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data);

/**
 * @brief Install Interrupt Callback for DMA channel half transfer complete
 *
 * @param [in] resource DMA resource
 * @param [in] callback Interrupt callback for DMA resource
 * @param [in] user_data User data used in the callback
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_install_chn_half_tc_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data);

/**
 * @brief Install Interrupt Callback for DMA channel transfer error
 *
 * @param [in] resource DMA resource
 * @param [in] callback Interrupt callback for DMA resource
 * @param [in] user_data User data used in the callback
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_install_chn_error_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data);

/**
 * @brief Install Interrupt Callback for DMA channel transfer abort
 *
 * @param [in] resource DMA resource
 * @param [in] callback Interrupt callback for DMA resource
 * @param [in] user_data User data used in the callback
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_install_chn_abort_callback(const dma_resource_t *resource, dma_mgr_chn_cb_t callback, void *user_data);

/**
 * @brief Get DMA channel default config
 *
 * @param [out] config config data pointer
 */
void dma_mgr_get_default_chn_config(dma_mgr_chn_conf_t *config);

/**
 * @brief Setup channel config
 *
 * @param [in] resource DMA resource
 * @param [in] config DMA channel config
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_setup_channel(const dma_resource_t *resource, dma_mgr_chn_conf_t *config);

/**
 * @brief Setup chain linked descriptor config
 *
 * @param [in] resource DMA resource
 * @param [in] config DMA channel config
 * @param [out] descriptor linked descriptor config data pointer
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_config_linked_descriptor(const dma_resource_t *resource, dma_mgr_chn_conf_t *config, dma_mgr_linked_descriptor_t *descriptor);

/**
 * @brief Enable DMA channel, start transfer
 *
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_enable_channel(const dma_resource_t *resource);

/**
 * @brief Disable DMA channel
 *
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_disable_channel(const dma_resource_t *resource);

/**
 * @brief Check DMA channel enable status
 *
 * @param [in] resource DMA resource
 * @param [out] enable enable status
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_check_chn_enable(const dma_resource_t *resource, bool *enable);

/**
 * @brief Enable DMA channel interrupt
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_enable_chn_irq(const dma_resource_t *resource, uint32_t irq_mask);

/**
 * @brief Disable DMA channel interrupt
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_disable_chn_irq(const dma_resource_t *resource, uint32_t irq_mask);

/**
 * @brief Set DMA channel priority
 *
 * @param [in] resource DMA resource
 * @param [in] priority DMA channel priority
 *  @arg @ref DMA_MGR_PRIORITY_LOW
 *  @arg @ref DMA_MGR_PRIORITY_HIGH
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_priority(const dma_resource_t *resource, uint8_t priority);

/**
 * @brief Set DMA channel source work mode
 *
 * @param [in] resource DMA resource
 * @param [in] mode DMA source work mode
 *  @arg @ref DMA_MGR_HANDSHAKE_MODE_NORMAL
 *  @arg @ref DMA_MGR_HANDSHAKE_MODE_HANDSHAKE
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_src_work_mode(const dma_resource_t *resource, uint8_t mode);

/**
 * @brief Set DMA channel destination work mode
 *
 * @param [in] resource DMA resource
 * @param [in] mode DMA destination work mode
 *  @arg @ref DMA_MGR_HANDSHAKE_MODE_NORMAL
 *  @arg @ref DMA_MGR_HANDSHAKE_MODE_HANDSHAKE
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_dst_work_mode(const dma_resource_t *resource, uint8_t mode);

/**
 * @brief Set DMA channel source burst size
 *
 * @param [in] resource DMA resource
 * @param [in] burstsize DMA source burst size
 *  when BURSTOPT is 0, please reference follows:
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_1T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_2T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_4T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_8T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_16T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_32T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_64T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_128T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_256T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_512T
 *      @arg @ref DMA_MGR_NUM_TRANSFER_PER_BURST_1024T
 *  when BURSTOPT is 1, burst size is (burstsize + 1). Attention: only DMAV2 support
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_src_burst_size(const dma_resource_t *resource, uint8_t burstsize);

/**
 * @brief Get DMA channel remaining transfer size
 *
 * @param [in] resource DMA resource
 * @param [out] size remaining transfer size of the channel.
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_get_chn_remaining_transize(const dma_resource_t *resource, uint32_t *size);

/**
 * @brief Set DMA channel transfer size
 *
 * @param [in] resource DMA resource
 * @param [in] size transfer size of the channel.
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_transize(const dma_resource_t *resource, uint32_t size);

/**
 * @brief Set DMA channel source width
 *
 * @param [in] resource DMA resource
 * @param [in] width transfer source width of the channel
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_BYTE
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_HALF_WORD
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_WORD
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_DOUBLE_WORD
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_src_width(const dma_resource_t *resource, uint8_t width);

/**
 * @brief Set DMA channel destination width
 *
 * @param [in] resource DMA resource
 * @param [in] width transfer destination width of the channel
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_BYTE
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_HALF_WORD
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_WORD
 *  @arg @ref DMA_MGR_TRANSFER_WIDTH_DOUBLE_WORD
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_dst_width(const dma_resource_t *resource, uint8_t width);

/**
 * @brief Set DMA channel source address
 *
 * @param [in] resource DMA resource
 * @param [in] addr source address
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_src_addr(const dma_resource_t *resource, uint32_t addr);

/**
 * @brief Set DMA channel destination address
 *
 * @param [in] resource DMA resource
 * @param [in] addr destination address
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_dst_addr(const dma_resource_t *resource, uint32_t addr);

/**
 * @brief Set DMA channel source address control mode
 *
 * @param [in] resource DMA resource
 * @param [in] addr_ctrl source address control mode
 *  @arg @ref DMA_MGR_ADDRESS_CONTROL_INCREMENT
 *  @arg @ref DMA_MGR_ADDRESS_CONTROL_DECREMENT
 *  @arg @ref DMA_MGR_ADDRESS_CONTROL_FIXED
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_src_addr_ctrl(const dma_resource_t *resource, uint8_t addr_ctrl);

/**
 * @brief Set DMA channel destination address control mode
 *
 * @param [in] resource DMA resource
 * @param [in] addr_ctrl destination address control mode
 *  @arg @ref DMA_MGR_ADDRESS_CONTROL_INCREMENT
 *  @arg @ref DMA_MGR_ADDRESS_CONTROL_DECREMENT
 *  @arg @ref DMA_MGR_ADDRESS_CONTROL_FIXED
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_dst_addr_ctrl(const dma_resource_t *resource, uint8_t addr_ctrl);

/**
 * @brief Set DMA channel infinite loop mode. Attention: only DMAV2 support
 *
 * @param [in] resource DMA resource
 * @param [in] infinite_loop false - normal mode(single times mode); true - infinite loop mode(cycle mode)
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_infinite_loop_mode(const dma_resource_t *resource, bool infinite_loop);

/**
 * @brief Set DMA channel source burst option. Attention: only DMAV2 support
 *
 * @param [in] resource DMA resource
 * @param [in] burst_opt burst option
 *  @arg @ref DMA_MGR_SRC_BURST_OPT_STANDAND_SIZE
 *  @arg @ref DMA_MGR_SRC_BURST_OPT_CUSTOM_SIZE
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_src_busrt_option(const dma_resource_t *resource, uint8_t burst_opt);

/**
 * @brief Set DMA channel handshake option. Attention: only DMAV2 support
 *
 * @param [in] resource DMA resource
 * @param [in] handshake_opt handshake option
 *  @arg @ref DMA_HANDSHAKE_OPT_ONE_BURST
 *  @arg @ref DMA_HANDSHAKE_OPT_ALL_TRANSIZE
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_set_chn_handshake_option(const dma_resource_t *resource, uint8_t handshake_opt);

/**
 * @brief Abort DMA channel transfer
 *
 * @param [in] resource DMA resource
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_abort_chn_transfer(const dma_resource_t *resource);

/**
 * @brief Check DMA channel transfer status
 *
 * @param [in] resource DMA resource
 * @param [out] sts transfer status
 *    DMA_MGR_CHANNEL_STATUS_ONGOING if transfer is still ongoing
 *    DMA_MGR_CHANNEL_STATUS_ERROR if any error occurred during transferring
 *    DMA_MGR_CHANNEL_STATUS_ABORT if transfer is aborted
 *    DMA_MGR_CHANNEL_STATUS_TC if transfer is finished without error
 *    DMA_MGR_CHANNEL_STATUS_HALF_TC if half transfer complete without error. Attention: only DMAV2 support
 *
 * @retval status_success if no error occurred
 * @retval status_invalid_argument if any parameters are invalid
 */
hpm_stat_t dma_mgr_check_chn_transfer_status(const dma_resource_t *resource, uint32_t *status);

/**
 * @brief   Set DMA channel source burst in fixed transfer size enable or disable
 *
 * @param [in] resource DMA resource
 * @param[in] enable false - disable; true - enable
 *
 */
hpm_stat_t dma_mgr_set_source_burst_in_fixed_transize_enable(const dma_resource_t *resource, bool enable);

/**
 * @brief   Set DMA channel destination burst in fixed transfer size enable or disable
 *
 * @param [in] resource DMA resource
 * @param[in] enable false - disable; true - enable
 *
 */
hpm_stat_t dma_mgr_set_destination_burst_in_fix_transize_enable(const dma_resource_t *resource, bool enable);

/**
 * @brief   Set DMA channel swap mode
 *
 * @param [in] resource DMA resource
 * @param[in] swap_mode swap mode
 *  @arg @ref DMA_MGR_SWAP_MODE_TABLE
 *  @arg @ref DMA_MGR_SWAP_MODE_BYTE
 *  @arg @ref DMA_MGR_SWAP_MODE_HALF_WORD
 *  @arg @ref DMA_MGR_SWAP_MODE_WORD
 *
 */
hpm_stat_t dma_mgr_set_swap_mode(const dma_resource_t *resource, uint8_t swap_mode);

/**
 * @brief   Set DMA channel swap table
 *
 * @param [in] resource DMA resource
 * @param[in] swap_table swap table
 *
 */
hpm_stat_t dma_mgr_set_swap_table(const dma_resource_t *resource, uint32_t swap_table);

#ifdef __cplusplus
}
#endif

#endif /* HPM_DMA_MGR_H */
