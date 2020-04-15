/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _FSL_IO_H
#define _FSL_IO_H

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief define a notify callback for IO
* @param size , transfer data size.
* @param rx, indicate a rx transfer is success.
* @param tx, indicate a tx transfer is success.
*/
typedef void (*notify)(size_t *size, bool rx, bool tx);

/*! @brief State structure storing io. */
typedef struct io_State
{
    void *ioBase;   /*!< Base of the IP register. */
    uint8_t ioType; /*!< device type */
#ifdef DEBUG_CONSOLE_TRANSFER_NON_BLOCKING
    notify callBack; /*!< define the callback function for buffer */
#endif

} io_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief io init function.
 *
 * Call this function to init IO.
 *
 * @param io configuration pointer
 * @param baudRate baud rate
 * @param clkSrcFreq clock freq
 * @param ringbuffer used to receive character
 */
void IO_Init(io_state_t *io, uint32_t baudRate, uint32_t clkSrcFreq, uint8_t *ringBuffer);

/*!
 * @brief Deinit IO.
 *
 * Call this function to Deinit IO.
 *
 * @return deinit status
 */
status_t IO_Deinit(void);

/*!
 * @brief io transfer function.
 *
 * Call this function to transfer log.
 * Print log:
 * @code
 * IO_Transfer(ch, size, true);
 * @endcode
 * Scanf log:
 * @code
 * IO_Transfer(ch, size, false);
 * @endcode
 *
 * @param   ch  transfer buffer pointer
 * @param	size transfer size
 * @param   tx indicate the transfer is TX or RX
 */
status_t IO_Transfer(uint8_t *ch, size_t size, bool tx);

/*!
 * @brief io wait idle.
 *
 * Call this function to wait the io idle
 *
 * @return Indicates whether wait idle was successful or not.
 */
status_t IO_WaitIdle(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _FSL_IO_H */
