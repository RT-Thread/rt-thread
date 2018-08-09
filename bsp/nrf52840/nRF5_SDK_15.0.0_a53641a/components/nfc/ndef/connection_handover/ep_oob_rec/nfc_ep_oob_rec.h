/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#ifndef NFC_EP_OOB_REC_H__
#define NFC_EP_OOB_REC_H__

/**@file
 *
 * @defgroup nfc_ep_oob_rec EP OOB records
 * @{
 * @ingroup  nfc_ble_pair_msg
 *
 * @brief    Generation of NFC NDEF EP OOB records for NDEF messages.
 *
 */

#include <stdint.h>
#include "nfc_ndef_record.h"
#include "nfc_ble_oob_advdata.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Size of the type field of the Bluetooth Carrier Configuration EP record, defined in the
 * file @c nfc_ep_oob_rec.c. It is used in the @ref NFC_NDEF_EP_OOB_RECORD_DESC_DEF macro.
 */
#define NFC_EP_OOB_REC_TYPE_LENGTH 32

/**
 * @brief External reference to the type field of the Bluetooth Carrier Configuration EP record, defined
 * in the file @c nfc_ep_oob_rec.c. It is used in the @ref NFC_NDEF_EP_OOB_RECORD_DESC_DEF macro.
 */
extern const uint8_t ndef_ep_oob_record_type[NFC_EP_OOB_REC_TYPE_LENGTH];

/**
 * @brief Function for constructing the payload for a Bluetooth Carrier Configuration EP record.
 *
 * This function encodes the record payload according to the BLE AD structure. It implements
 * an API compatible with @ref p_payload_constructor_t.
 *
 * @param[in]       p_ble_advdata   Pointer to the description of the payload.
 * @param[out]      p_buff          Pointer to payload destination. If NULL, function will
 *                                  calculate the expected size of the record payload.
 *
 * @param[in,out]   p_len           Size of available memory to write as input. Size of generated
 *                                  payload as output.
 *
 * @retval NRF_SUCCESS          If the record payload was encoded successfully.
 * @retval NRF_ERROR_NO_MEM     If available memory was not enough for record payload to be encoded.
 * @retval Other                If any other error occurred during record payload encoding.
 */
ret_code_t nfc_ep_oob_payload_constructor(ble_advdata_t * p_ble_advdata,
                                          uint8_t       * p_buff,
                                          uint32_t      * p_len);

/** @brief Macro for generating a description of an NFC NDEF Bluetooth Carrier Configuration EP record.
 *
 * This macro declares and initializes an instance of an NFC NDEF record description
 * for a Bluetooth Carrier Configuration EP record.
 *
 * @note The record descriptor is declared as automatic variable, which implies that
 *       the NDEF message encoding (see @ref nfc_ble_simplified_ep_oob_msg_encode)
 *       must be done in the same variable scope.
 *
 * @param[in]  NAME            Name for accessing record descriptor.
 * @param[in]  PAYLOAD_ID      NDEF record header Payload ID field (Limited to one byte).
 *                             If 0, no ID is present in the record description.
 * @param[in]  P_BLE_ADVDATA   Pointer to the encoded BLE advertising data structure. This
 *                             data is used to create the record payload.
 */
#define NFC_NDEF_EP_OOB_RECORD_DESC_DEF(NAME,                                  \
                                        PAYLOAD_ID,                            \
                                        P_BLE_ADVDATA)                         \
    uint8_t NAME##_ndef_ep_oob_record_id        = (PAYLOAD_ID);                \
    uint8_t NAME##_ndef_ep_oob_record_id_length = ((PAYLOAD_ID) != 0) ? 1 : 0; \
    NFC_NDEF_GENERIC_RECORD_DESC_DEF( NAME,                                    \
                                      TNF_MEDIA_TYPE,                          \
                                      &NAME##_ndef_ep_oob_record_id,           \
                                      NAME##_ndef_ep_oob_record_id_length,     \
                                      (ndef_ep_oob_record_type),               \
                                      sizeof(ndef_ep_oob_record_type),         \
                                      nfc_ep_oob_payload_constructor,          \
                                      (P_BLE_ADVDATA))                         \

/**
 * @brief Macro for accessing the NFC NDEF Bluetooth Carrier Configuration EP record descriptor
 * instance that was created with @ref NFC_NDEF_EP_OOB_RECORD_DESC_DEF.
 */
#define NFC_NDEF_EP_OOB_RECORD_DESC(NAME) NFC_NDEF_GENERIC_RECORD_DESC(NAME)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_EP_OOB_REC_H__
