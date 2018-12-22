/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#ifndef NFC_URI_MSG_H__
#define NFC_URI_MSG_H__

/**@file
 *
 * @defgroup nfc_uri_msg URI messages
 * @{
 * @ingroup  nfc_ndef_messages
 *
 * @brief    Generation of NFC NDEF messages with a URI record.
 *
 */

#include "nfc_ndef_msg.h"
#include "nfc_uri_rec.h"
#include "nrf_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Function for encoding an NFC NDEF URI message.
 *
 * This function encodes an NFC NDEF message into a buffer.
 *
 * @param[in]       uri_id_code         URI identifier code that defines the protocol field of the URI.
 * @param[in]       p_uri_data          Pointer to the URI string.
 *                                      The string should not contain the protocol field if the protocol
 *                                      was specified in @p uri_id_code.
 * @param[in]       uri_data_len        Length of the URI string.
 * @param[out]      p_buf               Pointer to the buffer for the message.
 * @param[in,out]   p_len               Size of the available memory for the message as input.
 *                                      Size of the generated message as output.
 *
 * @retval NRF_SUCCESS                  If the description was successfully created.
 * @retval NRF_ERROR_INVALID_PARAM      If the URI string was invalid (equal to NULL).
 * @retval NRF_ERROR_NO_MEM             If the predicted message size is bigger than the provided
 *                                      buffer space.
 * @retval Other                        Other codes might be returned depending on
 *                                      the function @ref nfc_ndef_msg_encode.
 */
ret_code_t nfc_uri_msg_encode( nfc_uri_id_t           uri_id_code,
                               uint8_t const *  const p_uri_data,
                               uint8_t                uri_data_len,
                               uint8_t       *        p_buf,
                               uint32_t      *        p_len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // NFC_URI_MSG_H__
