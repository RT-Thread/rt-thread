/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMAV2_DRV_H
#define HPM_DMAV2_DRV_H
#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_dmav2_regs.h"

/**
 *
 * @brief DMA driver APIs
 * @defgroup dma_interface DMA driver APIs
 * @ingroup io_interfaces
 * @{
 */

#define DMA_Type DMAV2_Type

#define DMA_CHANNEL_PRIORITY_LOW                (0U)
#define DMA_CHANNEL_PRIORITY_HIGH               (1U)

#define DMA_NUM_TRANSFER_PER_BURST_1T           (0U)
#define DMA_NUM_TRANSFER_PER_BURST_2T           (1U)
#define DMA_NUM_TRANSFER_PER_BURST_4T           (2U)
#define DMA_NUM_TRANSFER_PER_BURST_8T           (3U)
#define DMA_NUM_TRANSFER_PER_BURST_16T          (4U)
#define DMA_NUM_TRANSFER_PER_BURST_32T          (5U)
#define DMA_NUM_TRANSFER_PER_BURST_64T          (6U)
#define DMA_NUM_TRANSFER_PER_BURST_128T         (7U)
#define DMA_NUM_TRANSFER_PER_BURST_256T         (8U)
#define DMA_NUM_TRANSFER_PER_BURST_512T         (9U)
#define DMA_NUM_TRANSFER_PER_BURST_1024T        (10U)

#define DMA_TRANSFER_WIDTH_BYTE                 (0U)
#define DMA_TRANSFER_WIDTH_HALF_WORD            (1U)
#define DMA_TRANSFER_WIDTH_WORD                 (2U)
#define DMA_TRANSFER_WIDTH_DOUBLE_WORD          (3U)

#define DMA_ALIGN_HALF_WORD(x)                  (x & ~(1u))
#define DMA_ALIGN_WORD(x)                       (x & ~(3u))
#define DMA_ALIGN_DOUBLE_WORD(x)                (x & ~(7u))

#define DMA_CHANNEL_STATUS_ONGOING              (1U)
#define DMA_CHANNEL_STATUS_ERROR                (2U)
#define DMA_CHANNEL_STATUS_ABORT                (4U)
#define DMA_CHANNEL_STATUS_TC                   (8U)
#define DMA_CHANNEL_STATUS_HALF_TC              (16U)

#define DMA_CHANNEL_IRQ_STATUS_ERROR(x)         (uint32_t)(1 << x)
#define DMA_CHANNEL_IRQ_STATUS_ABORT(x)         (uint32_t)(1 << x)
#define DMA_CHANNEL_IRQ_STATUS_TC(x)            (uint32_t)(1 << x)
#define DMA_CHANNEL_IRQ_STATUS_HALF_TC(x)       (uint32_t)(1 << x)

#define DMA_HANDSHAKE_MODE_NORMAL               (0U)
#define DMA_HANDSHAKE_MODE_HANDSHAKE            (1U)

#define DMA_ADDRESS_CONTROL_INCREMENT           (0U)
#define DMA_ADDRESS_CONTROL_DECREMENT           (1U)
#define DMA_ADDRESS_CONTROL_FIXED               (2U)

#define DMA_SRC_BURST_OPT_STANDAND_SIZE         (0U)
#define DMA_SRC_BURST_OPT_CUSTOM_SIZE           (1U)

#define DMA_HANDSHAKE_OPT_ONE_BURST             (0U)
#define DMA_HANDSHAKE_OPT_ALL_TRANSIZE          (1U)

#define DMA_SWAP_MODE_TABLE                     (0U)
#define DMA_SWAP_MODE_BYTE                      (1U)
#define DMA_SWAP_MODE_HALF_WORD                 (2U)
#define DMA_SWAP_MODE_WORD                      (3U)

#define DMA_INTERRUPT_MASK_NONE                 (0U)
#define DMA_INTERRUPT_MASK_ERROR  DMAV2_CHCTRL_CTRL_INTERRMASK_MASK
#define DMA_INTERRUPT_MASK_ABORT  DMAV2_CHCTRL_CTRL_INTABTMASK_MASK
#define DMA_INTERRUPT_MASK_TERMINAL_COUNT DMAV2_CHCTRL_CTRL_INTTCMASK_MASK
#define DMA_INTERRUPT_MASK_HALF_TC DMAV2_CHCTRL_CTRL_INTHALFCNTMASK_MASK
#define DMA_INTERRUPT_MASK_ALL \
    (uint8_t)(DMA_INTERRUPT_MASK_TERMINAL_COUNT \
            | DMA_INTERRUPT_MASK_ABORT \
            | DMA_INTERRUPT_MASK_ERROR \
            | DMA_INTERRUPT_MASK_HALF_TC)

#define DMA_SUPPORT_64BIT_ADDR (0)


enum {
    dmav2_state_idle = 0,
    dmav2_state_read,
    dmav2_state_read_ack,
    dmav2_state_write,
    dmav2_state_write_ack,
    dmav2_state_ll,
    dmav2_state_end,
    dmav2_state_end_wait,
};

/**
 * @brief Linked descriptor
 *
 * It is consumed by DMA controlled directly
 */
typedef struct dma_linked_descriptor {
    uint32_t ctrl;              /**< Control */
    uint32_t trans_size;        /**< Transfer size in source width */
    uint32_t src_addr;          /**< Source address */
    uint32_t req_ctrl;          /**< Request select */
    uint32_t dst_addr;          /**< Destination address */
    uint32_t swap_table;        /**< Swap table */
    uint32_t linked_ptr;        /**< Linked descriptor address */
    uint32_t reserved0;         /**< not used on dmav2 */
} dma_linked_descriptor_t;

/* @brief Channel config */
typedef struct dma_channel_config {
    uint8_t priority;               /**< Channel priority */
    uint8_t src_burst_size;         /**< Source burst size */
    uint8_t src_mode;               /**< Source work mode */
    uint8_t dst_mode;               /**< Destination work mode */
    uint8_t src_width;              /**< Source width */
    uint8_t dst_width;              /**< Destination width */
    uint8_t src_addr_ctrl;          /**< Source address control */
    uint8_t dst_addr_ctrl;          /**< Destination address control */
    uint16_t interrupt_mask;        /**< Interrupt mask */
    uint32_t src_addr;              /**< Source address */
    uint32_t dst_addr;              /**< Destination address */
    uint32_t linked_ptr;            /**< Next linked descriptor */
    uint32_t size_in_byte;          /**< Total size to be transferred in byte */
    bool en_infiniteloop;           /**< Infinite loop transfer enable. Attention: only DMAV2 support */
    uint8_t handshake_opt;          /**< Handshake transfer option. Attention: only DMAV2 support */
    uint8_t burst_opt;              /**< Burst size option. Attention: only DMAV2 support */
#if defined(HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS) && (HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS == 1)
    bool en_src_burst_in_fixed_trans;          /**< Source burst in fix transfer size enable, discard src_addr_ctrl setting. Attention: only DMAV2 support */
    bool en_dst_burst_in_fixed_trans;          /**< Destination burst in fix transfer size enable, discard dst_addr_ctrl setting. Attention: only DMAV2 support */
#endif
#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
    uint8_t swap_mode;              /**< Swap Mode. Attention: only DMAV2 support */
    uint32_t swap_table;            /**< Swap Table. Attention: only DMAV2 support */
#endif
} dma_channel_config_t;

/* @brief Channel config */
typedef struct dma_handshake_config {
    uint32_t dst;
    uint32_t src;
    uint32_t size_in_byte;
    uint8_t data_width;            /* data width, value defined by DMA_TRANSFER_WIDTH_xxx */
    uint8_t ch_index;
    bool dst_fixed;
    bool src_fixed;
    bool en_infiniteloop;
    uint16_t interrupt_mask;
} dma_handshake_config_t;


/* @brief DMA specific status */
enum {
    status_dma_transfer_done = MAKE_STATUS(status_group_dma, 0),
    status_dma_transfer_error = MAKE_STATUS(status_group_dma, 1),
    status_dma_transfer_abort = MAKE_STATUS(status_group_dma, 2),
    status_dma_transfer_ongoing = MAKE_STATUS(status_group_dma, 3),
    status_dma_alignment_error = MAKE_STATUS(status_group_dma, 4),
    status_dma_transfer_half_done = MAKE_STATUS(status_group_dma, 5),
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset DMA
 *
 * @param[in] ptr DMA base address
 */
static inline void dma_reset(DMAV2_Type *ptr)
{
    ptr->DMACTRL |= DMAV2_DMACTRL_RESET_MASK;
}

/**
 * @brief   Enable DMA channel
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel to be enabled
 *
 * @return status_success if everything's okay
 */
static inline hpm_stat_t dma_enable_channel(DMAV2_Type *ptr, uint32_t ch_index)
{
    ptr->CHCTRL[ch_index].CTRL |= DMAV2_CHCTRL_CTRL_ENABLE_MASK;

    if ((ptr->CHEN == 0) || !(ptr->CHEN & 1 << ch_index)) {
        return status_fail;
    }
    return status_success;
}

/**
 * @brief   Disable DMA channel
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel to be disabled
 *
 */
static inline void dma_disable_channel(DMAV2_Type *ptr, uint32_t ch_index)
{
    ptr->CHCTRL[ch_index].CTRL &= ~DMAV2_CHCTRL_CTRL_ENABLE_MASK;
}

/**
 * @brief   Check whether DMA channel is enable
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 *
 * @return   true if DMA channel is enable
 *
 */
static inline bool dma_channel_is_enable(DMAV2_Type *ptr, uint32_t ch_index)
{
    return (ptr->CHCTRL[ch_index].CTRL & DMAV2_CHCTRL_CTRL_ENABLE_MASK) ? true : false;
}

/**
 * @brief   Set DMA channel priority
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] priority dma priority
 *  @arg @ref DMA_CHANNEL_PRIORITY_LOW
 *  @arg @ref DMA_CHANNEL_PRIORITY_HIGH
 *
 */
static inline void dma_set_priority(DMAV2_Type *ptr, uint32_t ch_index, uint8_t priority)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_PRIORITY_MASK) | DMAV2_CHCTRL_CTRL_PRIORITY_SET(priority);
}

/**
 * @brief   Set DMA channel source work mode
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] mode source work mode
 *  @arg @ref DMA_HANDSHAKE_MODE_NORMAL
 *  @arg @ref DMA_HANDSHAKE_MODE_HANDSHAKE
 *
 */
static inline void dma_set_source_work_mode(DMAV2_Type *ptr, uint32_t ch_index, uint8_t mode)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_SRCMODE_MASK) | DMAV2_CHCTRL_CTRL_SRCMODE_SET(mode);
}

/**
 * @brief   Set DMA channel destination work mode
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] mode destination work mode
 *  @arg @ref DMA_HANDSHAKE_MODE_NORMAL
 *  @arg @ref DMA_HANDSHAKE_MODE_HANDSHAKE
 *
 */
static inline void dma_set_destination_work_mode(DMAV2_Type *ptr, uint32_t ch_index, uint8_t mode)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_DSTMODE_MASK) | DMAV2_CHCTRL_CTRL_DSTMODE_SET(mode);
}

/**
 * @brief   Set DMA channel source burst size
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] burstsize source burst size
 *  when BURSTOPT is 0, please reference follows:
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_1T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_2T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_4T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_8T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_16T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_32T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_64T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_128T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_256T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_512T
 *      @arg @ref DMA_NUM_TRANSFER_PER_BURST_1024T
 *  when BURSTOPT is 1, burst size is (burstsize + 1).
 *
 */
static inline void dma_set_source_burst_size(DMAV2_Type *ptr, uint32_t ch_index, uint8_t burstsize)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_MASK) | DMAV2_CHCTRL_CTRL_SRCBURSTSIZE_SET(burstsize);
}

/**
 * @brief   Get DMA channel remaining transfer size
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 *
 * @return remaining transfer size
 *
 */
static inline uint32_t dma_get_remaining_transfer_size(DMAV2_Type *ptr, uint32_t ch_index)
{
    return ptr->CHCTRL[ch_index].TRANSIZE;
}

/**
 * @brief   Set DMA channel transfer size
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] size_in_width transfer size of the channel. The width is current dma channel configured source width.
 *            Transfer total bytes are (size_in_width * source width).
 *
 */
static inline void dma_set_transfer_size(DMAV2_Type *ptr, uint32_t ch_index, uint32_t size_in_width)
{
    ptr->CHCTRL[ch_index].TRANSIZE = DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SET(size_in_width);
}

/**
 * @brief   Set DMA channel source width
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] width transfer source width of the channel
 *  @arg @ref DMA_TRANSFER_WIDTH_BYTE
 *  @arg @ref DMA_TRANSFER_WIDTH_HALF_WORD
 *  @arg @ref DMA_TRANSFER_WIDTH_WORD
 *  @arg @ref DMA_TRANSFER_WIDTH_DOUBLE_WORD
 */
static inline void dma_set_source_width(DMAV2_Type *ptr, uint32_t ch_index, uint8_t width)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_SRCWIDTH_MASK) | DMAV2_CHCTRL_CTRL_SRCWIDTH_SET(width);
}

/**
 * @brief   Set DMA channel destination width
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] width transfer destination width of the channel
 *  @arg @ref DMA_TRANSFER_WIDTH_BYTE
 *  @arg @ref DMA_TRANSFER_WIDTH_HALF_WORD
 *  @arg @ref DMA_TRANSFER_WIDTH_WORD
 *  @arg @ref DMA_TRANSFER_WIDTH_DOUBLE_WORD
 */
static inline void dma_set_destination_width(DMAV2_Type *ptr, uint32_t ch_index, uint8_t width)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_DSTWIDTH_MASK) | DMAV2_CHCTRL_CTRL_DSTWIDTH_SET(width);
}

/**
 * @brief   Set DMA channel transfer width and size in byte
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] src_width transfer source width of the channel
 *  @arg @ref DMA_TRANSFER_WIDTH_BYTE
 *  @arg @ref DMA_TRANSFER_WIDTH_HALF_WORD
 *  @arg @ref DMA_TRANSFER_WIDTH_WORD
 *  @arg @ref DMA_TRANSFER_WIDTH_DOUBLE_WORD
 * @param[in] size_in_byte transfer size in byte of the channel. The dma transfer size is (size_in_byte >> src_width).
 *
 */
static inline void dma_set_transfer_src_width_byte_size(DMAV2_Type *ptr, uint32_t ch_index, uint8_t src_width, uint32_t size_in_byte)
{
    assert((src_width == DMA_TRANSFER_WIDTH_BYTE) || (src_width == DMA_TRANSFER_WIDTH_HALF_WORD)
        || (src_width == DMA_TRANSFER_WIDTH_WORD) || (src_width == DMA_TRANSFER_WIDTH_DOUBLE_WORD));

    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_SRCWIDTH_MASK) | DMAV2_CHCTRL_CTRL_SRCWIDTH_SET(src_width);
    ptr->CHCTRL[ch_index].TRANSIZE = DMAV2_CHCTRL_TRANSIZE_TRANSIZE_SET(size_in_byte >> src_width);
}

/**
 * @brief   Set DMA channel source address
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] addr source address
 *
 */
static inline void dma_set_source_address(DMAV2_Type *ptr, uint32_t ch_index, uint32_t addr)
{
    ptr->CHCTRL[ch_index].SRCADDR = addr;
}

/**
 * @brief   Set DMA channel destination address
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] addr destination address
 *
 */
static inline void dma_set_destination_address(DMAV2_Type *ptr, uint32_t ch_index, uint32_t addr)
{
    ptr->CHCTRL[ch_index].DSTADDR = addr;
}

/**
 * @brief   Set DMA channel source address control mode
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] addr_ctrl source address control mode
 *  @arg @ref DMA_ADDRESS_CONTROL_INCREMENT
 *  @arg @ref DMA_ADDRESS_CONTROL_DECREMENT
 *  @arg @ref DMA_ADDRESS_CONTROL_FIXED
 *
 */
static inline void dma_set_source_address_ctrl(DMAV2_Type *ptr, uint32_t ch_index, uint8_t addr_ctrl)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_SRCADDRCTRL_MASK) | DMAV2_CHCTRL_CTRL_SRCADDRCTRL_SET(addr_ctrl);
}

/**
 * @brief   Set DMA channel destination address control mode
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] addr_ctrl destination address control mode
 *  @arg @ref DMA_ADDRESS_CONTROL_INCREMENT
 *  @arg @ref DMA_ADDRESS_CONTROL_DECREMENT
 *  @arg @ref DMA_ADDRESS_CONTROL_FIXED
 *
 */
static inline void dma_set_destination_address_ctrl(DMAV2_Type *ptr, uint32_t ch_index, uint8_t addr_ctrl)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_DSTADDRCTRL_MASK) | DMAV2_CHCTRL_CTRL_DSTADDRCTRL_SET(addr_ctrl);
}

/**
 * @brief   Set DMA channel infinite loop mode
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] infinite_loop false - normal mode(single times mode); true - infinite loop mode(cycle mode)
 *
 */
static inline void dma_set_infinite_loop_mode(DMAV2_Type *ptr, uint32_t ch_index, bool infinite_loop)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_INFINITELOOP_MASK) | DMAV2_CHCTRL_CTRL_INFINITELOOP_SET(infinite_loop);
}

/**
 * @brief   Set DMA channel source burst option
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] burst_opt burst option
 *  @arg @ref DMA_SRC_BURST_OPT_STANDAND_SIZE
 *  @arg @ref DMA_SRC_BURST_OPT_CUSTOM_SIZE
 *
 */
static inline void dma_set_src_busrt_option(DMAV2_Type *ptr, uint32_t ch_index, uint8_t burst_opt)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_BURSTOPT_MASK) | DMAV2_CHCTRL_CTRL_BURSTOPT_SET(burst_opt);
}

/**
 * @brief   Set DMA channel handshake option
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] handshake_opt handshake option
 *  @arg @ref DMA_HANDSHAKE_OPT_ONE_BURST
 *  @arg @ref DMA_HANDSHAKE_OPT_ALL_TRANSIZE
 *
 */
static inline void dma_set_handshake_option(DMAV2_Type *ptr, uint32_t ch_index, uint8_t handshake_opt)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_MASK) | DMAV2_CHCTRL_CTRL_HANDSHAKEOPT_SET(handshake_opt);
}

#if defined(HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS) && (HPM_IP_FEATURE_DMAV2_BURST_IN_FIXED_TRANS == 1)
/**
 * @brief   Set DMA channel source burst in fixed transfer size enable or disable
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] enable false - disable; true - enable
 *
 */
static inline void dma_set_source_burst_in_fixed_transize_enable(DMAV2_Type *ptr, uint32_t ch_index, bool enable)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_SRC_FIXBURST_MASK) | DMAV2_CHCTRL_CTRL_SRC_FIXBURST_SET(enable);
}

/**
 * @brief   Set DMA channel destination burst in fixed transfer size enable or disable
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] enable false - disable; true - enable
 *
 */
static inline void dma_set_destination_burst_in_fixed_transize_enable(DMAV2_Type *ptr, uint32_t ch_index, bool enable)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_DST_FIXBURST_MASK) | DMAV2_CHCTRL_CTRL_DST_FIXBURST_SET(enable);
}
#endif

#if defined(HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP) && (HPM_IP_FEATURE_DMAV2_BYTE_ORDER_SWAP == 1)
/**
 * @brief   Set DMA channel swap mode
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] swap_mode swap mode
 *  @arg @ref DMA_SWAP_MODE_TABLE
 *  @arg @ref DMA_SWAP_MODE_BYTE
 *  @arg @ref DMA_SWAP_MODE_HALF_WORD
 *  @arg @ref DMA_SWAP_MODE_WORD
 *
 */
static inline void dma_set_swap_mode(DMAV2_Type *ptr, uint32_t ch_index, uint8_t swap_mode)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMAV2_CHCTRL_CTRL_SWAP_CTL_MASK) | DMAV2_CHCTRL_CTRL_SWAP_CTL_SET(swap_mode);
}

/**
 * @brief   Set DMA channel swap table
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] swap_table swap table
 *
 */
static inline void dma_set_swap_table(DMAV2_Type *ptr, uint32_t ch_index, uint32_t swap_table)
{
    ptr->CHCTRL[ch_index].SWAPTABLE = swap_table;
}
#endif

/**
 * @brief   Abort channel transfer with mask
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index_mask Mask of channels to be aborted
 */
static inline void dma_abort_channel(DMAV2_Type *ptr, uint32_t ch_index_mask)
{
    ptr->CHABORT |= DMAV2_CHABORT_CHABORT_SET(ch_index_mask);
}

/**
 * @brief   Check if channels are enabled with mask
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index_mask Mask of channels to be checked
 *
 * @return Enabled channel mask
 */
static inline uint32_t dma_check_enabled_channel(DMAV2_Type *ptr,
                                                  uint32_t ch_index_mask)
{
    return (ch_index_mask & ptr->CHEN);
}

/**
 * @brief   Check if linked pointer has been configured
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Target channel index to be checked
 *
 * @return true if linked pointer has been configured
 */
static inline bool dma_has_linked_pointer_configured(DMAV2_Type *ptr, uint32_t ch_index)
{
    return ptr->CHCTRL[ch_index].LLPOINTER != 0;
}

/**
 * @brief   Check transfer status
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Target channel index to be checked
 *
 * @retval DMA_CHANNEL_STATUS_ONGOING if transfer is still ongoing
 * @retval DMA_CHANNEL_STATUS_ERROR if any error occurred during transferring
 * @retval DMA_CHANNEL_STATUS_ABORT if transfer is aborted
 * @retval DMA_CHANNEL_STATUS_TC if transfer is finished without error
 * @retval DMA_CHANNEL_STATUS_HALF_TC if half transfer complete without error
 */
static inline uint32_t dma_check_transfer_status(DMAV2_Type *ptr, uint8_t ch_index)
{
    uint32_t dma_status = 0;

    if (ptr->INTTCSTS & (1 << ch_index)) {
        dma_status |= DMA_CHANNEL_STATUS_TC;
        ptr->INTTCSTS = (1 << ch_index); /* W1C clear status*/
    }
    if (ptr->INTHALFSTS & (1 << ch_index)) {
        dma_status |= DMA_CHANNEL_STATUS_HALF_TC;
        ptr->INTHALFSTS = (1 << ch_index); /* W1C clear status*/
    }
    if (ptr->INTERRSTS & (1 << ch_index)) {
        dma_status |= DMA_CHANNEL_STATUS_ERROR;
        ptr->INTERRSTS = (1 << ch_index); /* W1C clear status*/
    }
    if (ptr->INTABORTSTS & (1 << ch_index)) {
        dma_status |= DMA_CHANNEL_STATUS_ABORT;
        ptr->INTABORTSTS = (1 << ch_index); /* W1C clear status*/
    }
    if (dma_status == 0) {
        dma_status = DMA_CHANNEL_STATUS_ONGOING;
    }
    return dma_status;
}

/**
 * @brief   Clear transfer status
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Target channel index
 *
 */
static inline void dma_clear_transfer_status(DMAV2_Type *ptr, uint8_t ch_index)
{
    /* W1C */
    ptr->INTHALFSTS  = (1 << ch_index);
    ptr->INTTCSTS    = (1 << ch_index);
    ptr->INTABORTSTS = (1 << ch_index);
    ptr->INTERRSTS   = (1 << ch_index);
}

/**
 * @brief Enable DMA Channel interrupt
 *
 * @param [in] ptr DMA base address
 * @param [in] ch_index Target channel index
 * @param [in] interrupt_mask Interrupt mask
 */
static inline void dma_enable_channel_interrupt(DMAV2_Type *ptr, uint8_t ch_index, int32_t interrupt_mask)
{
    ptr->CHCTRL[ch_index].CTRL &= ~(interrupt_mask & DMA_INTERRUPT_MASK_ALL);
}

/**
 * @brief Disable DMA Channel interrupt
 *
 * @param [in] ptr DMA base address
 * @param [in] ch_index Target channel index
 * @param [in] interrupt_mask Interrupt mask
 */
static inline void dma_disable_channel_interrupt(DMAV2_Type *ptr, uint8_t ch_index, int32_t interrupt_mask)
{
    ptr->CHCTRL[ch_index].CTRL |= (interrupt_mask & DMA_INTERRUPT_MASK_ALL);
}


/**
 * @brief Check Channel interrupt master
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Target channel index to be checked
 * @return uint32_t Interrupt mask
 */
static inline uint32_t dma_check_channel_interrupt_mask(DMAV2_Type *ptr, uint8_t ch_index)
{
    return ptr->CHCTRL[ch_index].CTRL & DMA_INTERRUPT_MASK_ALL;
}

/**
 * @brief   Get default channel config
 *
 * @param[in] ptr DMA base address
 * @param[in] ch Channel config
 */
void dma_default_channel_config(DMAV2_Type *ptr, dma_channel_config_t *ch);

/**
 * @brief   Setup DMA channel
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_num Target channel index to be configured
 * @param[in] ch Channel config
 * @param[in] start_transfer Set true to start transfer
 *
 * @return  status_success if everything is okay
 */
hpm_stat_t dma_setup_channel(DMAV2_Type *ptr, uint8_t ch_num,
                            dma_channel_config_t *ch, bool start_transfer);

/**
 * @brief   Config linked descriptor function
 *
 * @param[in] ptr DMA base address
 * @param[in] descriptor Linked descriptor pointer
 * @param[in] ch_num Target channel index to be configured
 * @param[in] config Descriptor config pointer
 *
 * @return status_success if everything is okay
 */
hpm_stat_t dma_config_linked_descriptor(DMAV2_Type *ptr, dma_linked_descriptor_t *descriptor, uint8_t ch_num, dma_channel_config_t *config);

/**
 * @brief   Start DMA copy
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_num Target channel index
 * @param[in] dst Destination address
 * @param[in] src Source Address
 * @param[in] size_in_byte Size in byte
 * @param[in] burst_len_in_byte Burst length in byte
 *
 * @return status_success if everthing is okay
 * @note: dst, src, size should be aligned with burst_len_in_byte
 */
hpm_stat_t dma_start_memcpy(DMAV2_Type *ptr, uint8_t ch_num,
                               uint32_t dst, uint32_t src,
                               uint32_t size_in_byte, uint32_t burst_len_in_byte);

/**
 * @brief   Get default handshake config
 *
 * @param[in] ptr DMA base address
 * @param[in] config default config
 */
void dma_default_handshake_config(DMAV2_Type *ptr, dma_handshake_config_t *config);

/**
 * @brief   config dma handshake function
 *
 * @param[in] ptr DMA base address
 * @param[in] pconfig dma handshake config pointer
 * @param[in] start_transfer Set true to start transfer
 *
 * @return status_success if everything is okay
 */
hpm_stat_t dma_setup_handshake(DMAV2_Type *ptr,  dma_handshake_config_t *pconfig, bool start_transfer);

/**
 * @brief Check whether DMA is idle
 * @param [in] ptr DMA base address
 * @return true DMA is idle
 * @return false DMA is busy
 */
static inline bool dma_is_idle(DMAV2_Type *ptr)
{
    return (DMAV2_IDMISC_DMASTATE_GET(ptr->IDMISC) == dmav2_state_idle) ? true : false;
}


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_DMAV2_DRV_H */
