/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MBX_DRV_H
#define HPM_MBX_DRV_H
#include "hpm_common.h"
#include "hpm_mbx_regs.h"

/**
 * @brief MBX driver APIs
 * @defgroup mbx_interface MBX driver APIs
 * @ingroup io_interfaces
 * @{
 */

/*
 * @brief Bus access responses
 */
typedef enum {
    no_bus_error_no_wait = 0,
    generate_bus_error = 1,
} mbx_bus_access_resp_t;

/*
 * @brief MBX specific status
 */
enum {
    status_mbx_not_available = MAKE_STATUS(status_group_mbx, 2),
};

#define MBX_CR_ALL_INTERRUPTS_MASK (MBX_CR_TFMAIE_MASK | MBX_CR_RFMAIE_MASK \
        | MBX_CR_RFMFIE_MASK | MBX_CR_TWMEIE_MASK)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Set bus access response
 *
 * @param[in] ptr MBX base address
 * @param[in] resp response value type
 */
static inline void mbx_set_bus_access_response(MBX_Type *ptr, mbx_bus_access_resp_t resp)
{
    ptr->CR = (ptr->CR & ~(MBX_CR_BARCTL_MASK)) | MBX_CR_BARCTL_SET(resp);
}

/**
 * @brief   Enable interrupt with mask
 *
 * @param[in] ptr MBX base address
 * @param[in] mask Mask of interrupts to be enabled
 */
static inline void mbx_enable_intr(MBX_Type *ptr, uint8_t mask)
{
    ptr->CR |= mask;
}

/**
 * @brief   Disable interrupt with mask
 *
 * @param[in] ptr MBX base address
 * @param[in] mask Mask of interrupts to be disabled
 */
static inline void mbx_disable_intr(MBX_Type *ptr, uint8_t mask)
{
    ptr->CR &= ~mask;
}

/**
 * @brief   Empty fifo
 *
 * @param[in] ptr MBX base address
 */
static inline void mbx_empty_txfifo(MBX_Type *ptr)
{
    ptr->CR |= MBX_CR_TXRESET_MASK;
}

/**
 * @brief   Initialization
 *
 * @param[in] ptr MBX base address
 */
static inline void mbx_init(MBX_Type *ptr)
{
    mbx_empty_txfifo(ptr);
    mbx_disable_intr(ptr, MBX_CR_ALL_INTERRUPTS_MASK);
}

/**
 * @brief   Send message
 *
 * @param[in] ptr MBX base address
 * @param[in] msg Message data in 32 bits
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t mbx_send_message(MBX_Type *ptr, uint32_t msg)
{
    if (ptr->SR & MBX_SR_TWME_MASK) {
        ptr->TXREG = msg;
        return status_success;
    }
    return status_mbx_not_available;
}


/**
 * @brief   Retrieve message
 *
 * @param[in] ptr MBX base address
 * @param[out] msg Pointer to buffer to save message data
 *
 * @return status_success if everything is okay
 */
static inline hpm_stat_t mbx_retrieve_message(MBX_Type *ptr, uint32_t *msg)
{
    if (ptr->SR & MBX_SR_RWMV_MASK) {
        *msg = ptr->RXREG;
        return status_success;
    }
    return status_mbx_not_available;
}

/**
 * @brief   Send message to fifo
 *
 * @param[in] ptr MBX base address
 * @param[in] msg Pointer to message array to be sent
 * @param[in] count Number of 32-bit data to be sent
 *
 * @return status_success if everything is okay
 * @return status_not_available if fifo is full
 */
static inline hpm_stat_t mbx_send_fifo(MBX_Type *ptr, uint32_t *msg, uint32_t count)
{
    uint32_t i;
    hpm_stat_t status = status_success;
    for (i = 0; i < 4; i++) {
        if (ptr->SR & MBX_SR_TFMA_MASK) {
            ptr->TXWRD[0] = MBX_TXWRD_TXFIFO_SET(*(msg + i));
            count--;
            if (!count) {
                break;
            }
        } else {
            status = status_mbx_not_available;
            break;
        }
    }
    return status;
}



/**
 * @brief   Retrieve data from fifo
 *
 * @param[in] ptr MBX base address
 * @param[out] msg Pointer of buffer to receive data
 * @param[in] count Number of 32-bit data to be retrieved
 *
 * @return status_success if everything is okay
 * @return status_mbx_not_available if fifo is empty
 */
static inline hpm_stat_t mbx_retrieve_fifo(MBX_Type *ptr, uint32_t *msg, uint32_t count)
{
    uint32_t i;
    hpm_stat_t status = status_success;
    for (i = 0; i < 4; i++) {
        if (ptr->SR & MBX_SR_RFMA_MASK) {
            *(msg + i) = (ptr->RXWRD[0] & MBX_RXWRD_RXFIFO_MASK) >> MBX_RXWRD_RXFIFO_SHIFT;
            count--;
            if (!count) {
                break;
            }
        } else {
            status = status_mbx_not_available;
            break;
        }
    }
    return status;
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_MBX_DRV_H */
