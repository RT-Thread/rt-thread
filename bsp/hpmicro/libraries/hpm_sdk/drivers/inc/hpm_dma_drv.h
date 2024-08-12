/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMAV1_DRV_H
#define HPM_DMAV1_DRV_H
#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_dma_regs.h"

/**
 *
 * @brief DMA driver APIs
 * @defgroup dma_interface DMA driver APIs
 * @ingroup io_interfaces
 * @{
 */

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

#define DMA_STATUS_ERROR_SHIFT                  (0U)
#define DMA_STATUS_ABORT_SHIFT                  (8U)
#define DMA_STATUS_TC_SHIFT                     (16U)

#define DMA_CHANNEL_STATUS_ONGOING              (1U)
#define DMA_CHANNEL_STATUS_ERROR                (2U)
#define DMA_CHANNEL_STATUS_ABORT                (4U)
#define DMA_CHANNEL_STATUS_TC                   (8U)

#define DMA_CHANNEL_IRQ_STATUS_ERROR(x)         (uint32_t)(1 << (DMA_STATUS_ERROR_SHIFT + x))
#define DMA_CHANNEL_IRQ_STATUS_ABORT(x)         (uint32_t)(1 << (DMA_STATUS_ABORT_SHIFT + x))
#define DMA_CHANNEL_IRQ_STATUS_TC(x)            (uint32_t)(1 << (DMA_STATUS_TC_SHIFT + x))
#define DMA_CHANNEL_IRQ_STATUS(x)               (uint32_t)(DMA_CHANNEL_IRQ_STATUS_TC(x) | \
                                                           DMA_CHANNEL_IRQ_STATUS_ABORT(x) | \
                                                           DMA_CHANNEL_IRQ_STATUS_ERROR(x))

#define DMA_CHANNEL_IRQ_STATUS_GET_ALL_TC(x) ((x) & (((0x01UL << DMA_SOC_CHANNEL_NUM) - 1) << DMA_STATUS_TC_SHIFT))
#define DMA_CHANNEL_IRQ_STATUS_GET_ALL_ABORT(x) ((x) & (((0x01UL << DMA_SOC_CHANNEL_NUM) - 1) << DMA_STATUS_ABORT_SHIFT))
#define DMA_CHANNEL_IRQ_STATUS_GET_ALL_ERROR(x) ((x) & (((0x01UL << DMA_SOC_CHANNEL_NUM) - 1) << DMA_STATUS_ERROR_SHIFT))

#define DMA_HANDSHAKE_MODE_NORMAL (0U)
#define DMA_HANDSHAKE_MODE_HANDSHAKE (1U)

#define DMA_ADDRESS_CONTROL_INCREMENT (0U)
#define DMA_ADDRESS_CONTROL_DECREMENT (1U)
#define DMA_ADDRESS_CONTROL_FIXED (2U)

#define DMA_INTERRUPT_MASK_NONE (0U)
#define DMA_INTERRUPT_MASK_ERROR  DMA_CHCTRL_CTRL_INTERRMASK_MASK
#define DMA_INTERRUPT_MASK_ABORT  DMA_CHCTRL_CTRL_INTABTMASK_MASK
#define DMA_INTERRUPT_MASK_TERMINAL_COUNT DMA_CHCTRL_CTRL_INTTCMASK_MASK
#define DMA_INTERRUPT_MASK_ALL \
    (uint8_t)(DMA_INTERRUPT_MASK_TERMINAL_COUNT \
            | DMA_INTERRUPT_MASK_ABORT \
            | DMA_INTERRUPT_MASK_ERROR)

#ifndef DMA_SUPPORT_64BIT_ADDR
#define DMA_SUPPORT_64BIT_ADDR (0)
#endif

/**
 * @brief Linked descriptor
 *
 * It is consumed by DMA controlled directly
 */
typedef struct dma_linked_descriptor {
    uint32_t ctrl;              /**< Control */
    uint32_t trans_size;        /**< Transfer size in source width */
    uint32_t src_addr;          /**< Source address */
    uint32_t src_addr_high;     /**< Source address high 32-bit, only valid when bus width > 32bits */
    uint32_t dst_addr;          /**< Destination address */
    uint32_t dst_addr_high;     /**< Destination address high 32-bit, only valid when bus width > 32bits */
    uint32_t linked_ptr;        /**< Linked descriptor address */
    uint32_t linked_ptr_high;   /**< Linked descriptor address high 32-bit, , only valid when bus width > 32bits */
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
#if DMA_SUPPORT_64BIT_ADDR
    uint32_t src_addr_high;         /**< Source address high 32bits */
    uint32_t dst_addr_high;         /**< Destination address high 32bits */
    uint32_t linked_ptr_high;       /**< Linked descriptor high 32bits */
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
} dma_handshake_config_t;


/* @brief DMA specific status */
enum {
    status_dma_transfer_done = MAKE_STATUS(status_group_dma, 0),
    status_dma_transfer_error = MAKE_STATUS(status_group_dma, 1),
    status_dma_transfer_abort = MAKE_STATUS(status_group_dma, 2),
    status_dma_transfer_ongoing = MAKE_STATUS(status_group_dma, 3),
    status_dma_alignment_error = MAKE_STATUS(status_group_dma, 4),
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset DMA
 *
 * @param[in] ptr DMA base address
 */
static inline void dma_reset(DMA_Type *ptr)
{
    ptr->DMACTRL |= DMA_DMACTRL_RESET_MASK;
}

/**
 * @brief   Enable DMA channel
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel to be enabled
 *
 * @return status_success if everything's okay
 */
static inline hpm_stat_t dma_enable_channel(DMA_Type *ptr, uint32_t ch_index)
{
    ptr->CHCTRL[ch_index].CTRL |= DMA_CHCTRL_CTRL_ENABLE_MASK;

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
static inline void dma_disable_channel(DMA_Type *ptr, uint32_t ch_index)
{
    ptr->CHCTRL[ch_index].CTRL &= ~DMA_CHCTRL_CTRL_ENABLE_MASK;
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
static inline bool dma_channel_is_enable(DMA_Type *ptr, uint32_t ch_index)
{
    return (ptr->CHCTRL[ch_index].CTRL & DMA_CHCTRL_CTRL_ENABLE_MASK) ? true : false;
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
static inline void dma_set_priority(DMA_Type *ptr, uint32_t ch_index, uint8_t priority)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_PRIORITY_MASK) | DMA_CHCTRL_CTRL_PRIORITY_SET(priority);
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
static inline void dma_set_source_work_mode(DMA_Type *ptr, uint32_t ch_index, uint8_t mode)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_SRCMODE_MASK) | DMA_CHCTRL_CTRL_SRCMODE_SET(mode);
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
static inline void dma_set_destination_work_mode(DMA_Type *ptr, uint32_t ch_index, uint8_t mode)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_DSTMODE_MASK) | DMA_CHCTRL_CTRL_DSTMODE_SET(mode);
}

/**
 * @brief   Set DMA channel source burst size
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] burstsize source burst size
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_1T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_2T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_4T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_8T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_16T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_32T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_64T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_128T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_256T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_512T
 *  @arg @ref DMA_NUM_TRANSFER_PER_BURST_1024T
 *
 */
static inline void dma_set_source_burst_size(DMA_Type *ptr, uint32_t ch_index, uint8_t burstsize)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_SRCBURSTSIZE_MASK) | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(burstsize);
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
static inline uint32_t dma_get_remaining_transfer_size(DMA_Type *ptr, uint32_t ch_index)
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
static inline void dma_set_transfer_size(DMA_Type *ptr, uint32_t ch_index, uint32_t size_in_width)
{
    ptr->CHCTRL[ch_index].TRANSIZE = DMA_CHCTRL_TRANSIZE_TRANSIZE_SET(size_in_width);
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
static inline void dma_set_source_width(DMA_Type *ptr, uint32_t ch_index, uint8_t width)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_SRCWIDTH_MASK) | DMA_CHCTRL_CTRL_SRCWIDTH_SET(width);
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
static inline void dma_set_destination_width(DMA_Type *ptr, uint32_t ch_index, uint8_t width)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_DSTWIDTH_MASK) | DMA_CHCTRL_CTRL_DSTWIDTH_SET(width);
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
static inline void dma_set_transfer_src_width_byte_size(DMA_Type *ptr, uint32_t ch_index, uint8_t src_width, uint32_t size_in_byte)
{
    assert((src_width == DMA_TRANSFER_WIDTH_BYTE) || (src_width == DMA_TRANSFER_WIDTH_HALF_WORD)
        || (src_width == DMA_TRANSFER_WIDTH_WORD) || (src_width == DMA_TRANSFER_WIDTH_DOUBLE_WORD));

    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_SRCWIDTH_MASK) | DMA_CHCTRL_CTRL_SRCWIDTH_SET(src_width);
    ptr->CHCTRL[ch_index].TRANSIZE = DMA_CHCTRL_TRANSIZE_TRANSIZE_SET(size_in_byte >> src_width);
}

/**
 * @brief   Set DMA channel source address
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Index of the channel
 * @param[in] addr source address
 *
 */
static inline void dma_set_source_address(DMA_Type *ptr, uint32_t ch_index, uint32_t addr)
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
static inline void dma_set_destination_address(DMA_Type *ptr, uint32_t ch_index, uint32_t addr)
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
static inline void dma_set_source_address_ctrl(DMA_Type *ptr, uint32_t ch_index, uint8_t addr_ctrl)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_SRCADDRCTRL_MASK) | DMA_CHCTRL_CTRL_SRCADDRCTRL_SET(addr_ctrl);
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
static inline void dma_set_destination_address_ctrl(DMA_Type *ptr, uint32_t ch_index, uint8_t addr_ctrl)
{
    ptr->CHCTRL[ch_index].CTRL = (ptr->CHCTRL[ch_index].CTRL & ~DMA_CHCTRL_CTRL_DSTADDRCTRL_MASK) | DMA_CHCTRL_CTRL_DSTADDRCTRL_SET(addr_ctrl);
}

/**
 * @brief   Abort channel transfer with mask
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index_mask Mask of channels to be aborted
 */
static inline void dma_abort_channel(DMA_Type *ptr, uint32_t ch_index_mask)
{
    ptr->CHABORT |= DMA_CHABORT_CHABORT_SET(ch_index_mask);
}

/**
 * @brief   Check if channels are enabled with mask
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index_mask Mask of channels to be checked
 *
 * @return Enabled channel mask
 */
static inline uint32_t dma_check_enabled_channel(DMA_Type *ptr,
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
static inline bool dma_has_linked_pointer_configured(DMA_Type *ptr, uint32_t ch_index)
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
 */
static inline uint32_t dma_check_transfer_status(DMA_Type *ptr, uint8_t ch_index)
{
    volatile uint32_t tmp = ptr->INTSTATUS;
    volatile uint32_t tmp_channel;
    uint32_t dma_status;

    dma_status = 0;
    tmp_channel = tmp & (1 << (DMA_STATUS_TC_SHIFT + ch_index));
    if (tmp_channel) {
        dma_status |= DMA_CHANNEL_STATUS_TC;
        ptr->INTSTATUS = tmp_channel;
    }
    tmp_channel = tmp & (1 << (DMA_STATUS_ERROR_SHIFT + ch_index));
    if (tmp_channel) {
        dma_status |= DMA_CHANNEL_STATUS_ERROR;
        ptr->INTSTATUS = tmp_channel;
    }
    tmp_channel = tmp & (1 << (DMA_STATUS_ABORT_SHIFT + ch_index));
    if (tmp_channel) {
        dma_status |= DMA_CHANNEL_STATUS_ABORT;
        ptr->INTSTATUS = tmp_channel;
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
static inline void dma_clear_transfer_status(DMA_Type *ptr, uint8_t ch_index)
{
    ptr->INTSTATUS = ((1 << (DMA_STATUS_TC_SHIFT + ch_index)) | (1 << (DMA_STATUS_ERROR_SHIFT + ch_index)) | (1 << (DMA_STATUS_ABORT_SHIFT + ch_index)));
}

/**
 * @brief Enable DMA Channel interrupt
 *
 * @param [in] ptr DMA base address
 * @param [in] ch_index Target channel index
 * @param [in] interrupt_mask Interrupt mask
 */
static inline void dma_enable_channel_interrupt(DMA_Type *ptr, uint8_t ch_index, int32_t interrupt_mask)
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
static inline void dma_disable_channel_interrupt(DMA_Type *ptr, uint8_t ch_index, int32_t interrupt_mask)
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
static inline uint32_t dma_check_channel_interrupt_mask(DMA_Type *ptr, uint8_t ch_index)
{
    return ptr->CHCTRL[ch_index].CTRL & DMA_INTERRUPT_MASK_ALL;
}

/**
 * @brief   Get clear IRQ status
 *
 * @param[in] ptr DMA base address
 * @param[in] mask irq mask to be cleared
 */
static inline void dma_clear_irq_status(DMA_Type *ptr, uint32_t mask)
{
    ptr->INTSTATUS = mask; /* Write-1-Clear */
}

/**
 * @brief   Get IRQ status
 *
 * @param[in] ptr DMA base address
 */
static inline uint32_t dma_get_irq_status(DMA_Type *ptr)
{
    return ptr->INTSTATUS;
}

/**
 * @brief   Get default channel config
 *
 * @param[in] ptr DMA base address
 * @param[in] ch Channel config
 */
void dma_default_channel_config(DMA_Type *ptr, dma_channel_config_t *ch);

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
hpm_stat_t dma_setup_channel(DMA_Type *ptr, uint8_t ch_num,
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
hpm_stat_t dma_config_linked_descriptor(DMA_Type *ptr, dma_linked_descriptor_t *descriptor, uint8_t ch_num, dma_channel_config_t *config);

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
hpm_stat_t dma_start_memcpy(DMA_Type *ptr, uint8_t ch_num,
                               uint32_t dst, uint32_t src,
                               uint32_t size_in_byte, uint32_t burst_len_in_byte);

/**
 * @brief   Get default handshake config
 *
 * @param[in] ptr DMA base address
 * @param[in] config default config
 */
void dma_default_handshake_config(DMA_Type *ptr, dma_handshake_config_t *config);

/**
 * @brief   config dma handshake function
 *
 * @param[in] ptr DMA base address
 * @param[in] pconfig dma handshake config pointer
 * @param[in] start_transfer Set true to start transfer
 *
 * @return status_success if everything is okay
 */
hpm_stat_t dma_setup_handshake(DMA_Type *ptr,  dma_handshake_config_t *pconfig, bool start_transfer);


#if defined(DMA_SOC_HAS_IDLE_FLAG) && (DMA_SOC_HAS_IDLE_FLAG == 1)
/**
 * @brief Check whether DMA is idle
 * @param [in] ptr DMA base address
 * @return true DMA is idle
 * @return false DMA is busy
 */
static inline bool dma_is_idle(DMA_Type *ptr)
{
    return ((ptr->IDMISC & DMA_IDMISC_IDLE_FLAG_MASK) != 0U);
}
#endif


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_DMAV1_DRV_H */
