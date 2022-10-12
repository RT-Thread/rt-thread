/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMA_DRV_H
#define HPM_DMA_DRV_H
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
#define DMA_TRANSFER_WIDTH_QUAD_WORD            (4U)
#define DMA_TRANSFER_WIDTH_EIGHT_WORD           (5U)

#define DMA_STATUS_ERROR_SHIFT                  (0U)
#define DMA_STATUS_ABORT_SHIFT                  (8U)
#define DMA_STATUS_TC_SHIFT                     (16U)

#define DMA_CHANNEL_STATUS_ONGOING (1U)
#define DMA_CHANNEL_STATUS_ERROR (2U)
#define DMA_CHANNEL_STATUS_ABORT (4U)
#define DMA_CHANNEL_STATUS_TC (8U)

#define DMA_CHANNEL_IRQ_STATUS_ERROR(x) (uint32_t)(1 << (DMA_STATUS_ERROR_SHIFT + x))
#define DMA_CHANNEL_IRQ_STATUS_ABORT(x) (uint32_t)(1 << (DMA_STATUS_ABORT_SHIFT + x))
#define DMA_CHANNEL_IRQ_STATUS_TC(x) (uint32_t)(1 << (DMA_STATUS_TC_SHIFT + x))
#define DMA_CHANNEL_IRQ_STATUS(x) (uint32_t)(DMA_CHANNEL_IRQ_STATUS_TC(x) | \
                                         DMA_CHANNEL_IRQ_STATUS_ABORT(x) | \
                                         DMA_CHANNEL_IRQ_STATUS_ERROR(x))

#define DMA_CHANNEL_IRQ_STATUS_GET_ALL_TC(x) ((x) & (((0x01UL << DMA_SOC_CHANNEL_NUM) - 1) << DMA_STATUS_TC_SHIFT))
#define DMA_CHANNEL_IRQ_STATUS_GET_ALL_ABORT(x) ((x) & (((0x01UL << DMA_SOC_CHANNEL_NUM) - 1) << DMA_STATUS_ABORT_SHIFT))
#define DMA_CHANNEL_IRQ_STATUS_GET_ALL_ERROR(x) ((x) & (((0x01UL << DMA_SOC_CHANNEL_NUM) - 1) << DMA_STATUS_ERROR_SHIFT))

#define DMA_HANDSHAKE_MODE_HANDSHAKE (1U)
#define DMA_HANDSHAKE_MODE_NORMAL (0U)

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
 * @retval 1 if transfer is still ongoing
 * @retval 2 if any error occurred during transferring
 * @retval 4 if transfer is aborted
 * @retval 8 if transfer is finished without error
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
 * @brief Enable DMA Channel interrupt
 *
 * @param [in] ptr DMA base address
 * @param [in] ch_index Target channel index
 * @param [in] interrupt_mask Interrupt mask
 */
static inline void dma_enable_channel_interrupt(DMA_Type *ptr, uint8_t ch_index, int32_t interrupt_mask)
{
    ptr->CHCTRL[ch_index].CTRL &= ~(interrupt_mask & (DMA_INTERRUPT_MASK_ERROR | DMA_INTERRUPT_MASK_ABORT | DMA_INTERRUPT_MASK_TERMINAL_COUNT));
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
    ptr->CHCTRL[ch_index].CTRL |= (interrupt_mask & (DMA_INTERRUPT_MASK_ERROR | DMA_INTERRUPT_MASK_ABORT | DMA_INTERRUPT_MASK_TERMINAL_COUNT));
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
    return ptr->CHCTRL[ch_index].CTRL & (DMA_INTERRUPT_MASK_ERROR | DMA_INTERRUPT_MASK_ABORT | DMA_INTERRUPT_MASK_TERMINAL_COUNT);
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
 * @param[in] ch_index Target channel index to be configured
 * @param[in] ch Channel config
 *
 * @return  status_success if everything is okay
 */
hpm_stat_t dma_setup_channel(DMA_Type *ptr, uint32_t ch_index,
                            dma_channel_config_t *ch);
/**
 * @brief   Start DMA copy
 *
 * @param[in] ptr DMA base address
 * @param[in] ch_index Target channel index
 * @param[in] dst Destination address
 * @param[in] src Source Address
 * @param[in] size_in_byte Size in byte
 * @param[in] burst_len_in_byte Burst length in byte
 *
 * @return status_success if everthing is okay
 * @note: dst, src, size should be aligned with burst_len_in_byte
 */
hpm_stat_t dma_start_memcpy(DMA_Type *ptr, uint8_t ch_index,
                               uint32_t dst, uint32_t src,
                               uint32_t size_in_byte, uint32_t burst_len_in_byte);

/**
 * @brief   config dma handshake function
 *
 * @param[in] ptr DMA base address
 * @param[in] pconfig dma handshake config pointer
 *
 * @return status_success if everthing is okay
 */
hpm_stat_t dma_setup_handshake(DMA_Type *ptr,  dma_handshake_config_t *pconfig);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_DMA_DRV_H */
