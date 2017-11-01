/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef ANCS_TX_BUFFER_H__
#define ANCS_TX_BUFFER_H__

#include "nrf_ble_ancs_c.h"

/** @file
 *
 * @addtogroup ble_ancs_c
 * @{
 */

#define TX_BUFFER_MASK                   0x07                     //!< TX buffer mask. Must be a mask of contiguous zeroes followed by a contiguous sequence of ones: 000...111.
#define TX_BUFFER_SIZE                   (TX_BUFFER_MASK + 1)     //!< Size of the send buffer, which is 1 bigger than the mask.
#define WRITE_MESSAGE_LENGTH             20                       //!< Length of the write message for the CCCD/control point.

/**@brief ANCS request types.
 */
typedef enum
{
    READ_REQ = 1,  /**< Type identifying that this TX message is a read request. */
    WRITE_REQ      /**< Type identifying that this TX message is a write request. */
} tx_request_t;


/**@brief Structure for writing a message to the central, thus the Control Point or CCCD.
 */
typedef struct
{
  uint8_t                  gattc_value[WRITE_MESSAGE_LENGTH]; //!< The message to write.
  ble_gattc_write_params_t gattc_params;                      //!< GATTC parameters for this message.
} write_params_t;


/**@brief Data to be transmitted to the connected master.
 */
typedef struct
{
  uint16_t          conn_handle;  //!< Connection handle to be used when transmitting this message.
  tx_request_t type;         //!< Type of this message (read or write message).
    union
    {
      uint16_t       read_handle;    //!< Read request message.
      write_params_t write_req; //!< Write request message.
    } req;
} tx_message_t;

/**@brief Function for clearing the TX buffer.
 *
 * @details Always call this function before using the TX buffer.
*/
void tx_buffer_init(void);

/**@brief Function for moving the pointer of the ring buffer to the next element.
*/
void tx_buffer_insert(tx_message_t * p_msg);

/**@brief Function for passing any pending request from the buffer to the stack.
*/
void tx_buffer_process(void);

/** @} */

#endif // ANCS_TX_BUFFER_H__

