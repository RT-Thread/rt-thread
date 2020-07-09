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
/** @file
 *
 * @defgroup nfc_ble_oob_advdata Advertising and Scan Response Data Encoder for NFC OOB pairing
 * @{
 * @ingroup nfc_ble_pair_msg
 * @brief Function for encoding data in the Advertising and Scan Response Data format, which
 *        can be used to create payload of NFC message intended for initiating the Out-of-Band
 *        pairing.
 */

#ifndef NFC_BLE_OOB_ADVDATA_H__
#define NFC_BLE_OOB_ADVDATA_H__

#include <stdint.h>
#include "ble_advdata.h"
#include "app_util.h"
#include "sdk_errors.h"


#define AD_TYPE_LE_ROLE_DATA_SIZE       1UL                                     /**< Data size (in octets) of the LE Bluetooth Device Address AD type. */
#define AD_TYPE_LE_ROLE_SIZE            (ADV_AD_DATA_OFFSET + \
                                            AD_TYPE_LE_ROLE_DATA_SIZE)          /**< Size (in octets) of the LE Bluetooth Device Address AD type. */
#define AD_TYPE_TK_VALUE_DATA_SIZE      (sizeof(ble_advdata_tk_value_t))        /**< Data size (in octets) of the Security Manager TK value AD type. */
#define AD_TYPE_TK_VALUE_SIZE           (ADV_AD_DATA_OFFSET + \
                                            AD_TYPE_TK_VALUE_DATA_SIZE)         /**< Size (in octets) of the Security Manager TK value AD type. */
#define AD_TYPE_OOB_FLAGS_DATA_SIZE     1UL                                     /**< Data size (in octets) of the Security Manager OOB Flags AD type. */
#define AD_TYPE_OOB_FLAGS_SIZE          (ADV_AD_DATA_OFFSET + \
                                            AD_TYPE_OOB_FLAGS_DATA_SIZE)        /**< Size (in octets) of the Security Manager OOB Flags AD type. */

#define AD_TYPE_CONFIRM_VALUE_DATA_SIZE 16UL                                    /**< Data size (in octets) of the LESC Confirmation value. */
#define AD_TYPE_CONFIRM_VALUE_SIZE      (ADV_AD_DATA_OFFSET + \
                                            AD_TYPE_CONFIRM_VALUE_DATA_SIZE)    /**< Size (in octets) of the LESC Confirmation value AD type. */
#define AD_TYPE_RANDOM_VALUE_DATA_SIZE  16UL                                    /**< Data size (in octets) of the LESC Random value. */
#define AD_TYPE_RANDOM_VALUE_SIZE       (ADV_AD_DATA_OFFSET + \
                                            AD_TYPE_RANDOM_VALUE_DATA_SIZE)     /**< Size (in octets) of the LESC Random value AD type. */
#define AD_TYPE_LESC_SIZE               (AD_TYPE_RANDOM_VALUE_SIZE + \
                                            AD_TYPE_CONFIRM_VALUE_SIZE)         /**< Size (in octets) of the LESC OOB AD data field in NDEF message. */

#define AD_TYPE_SEC_MGR_OOB_FLAG_SET                   1U                       /**< Security Manager OOB Flag set. Flag selection is done using _POS defines */
#define AD_TYPE_SEC_MGR_OOB_FLAG_CLEAR                 0U                       /**< Security Manager OOB Flag clear. Flag selection is done using _POS defines */
#define AD_TYPE_SEC_MGR_OOB_FLAG_OOB_DATA_PRESENT_POS  0UL                      /**< Security Manager OOB Data Present Flag position. */
#define AD_TYPE_SEC_MGR_OOB_FLAG_OOB_LE_SUPPORTED_POS  1UL                      /**< Security Manager OOB Low Energy Supported Flag position. */
#define AD_TYPE_SEC_MGR_OOB_FLAG_SIM_LE_AND_EP_POS     2UL                      /**< Security Manager OOB Simultaneous LE and BR/EDR to Same Device Capable Flag position. */
#define AD_TYPE_SEC_MGR_OOB_ADDRESS_TYPE_PUBLIC        0UL                      /**< Security Manager OOB Public Address type. */
#define AD_TYPE_SEC_MGR_OOB_ADDRESS_TYPE_RANDOM        1UL                      /**< Security Manager OOB Random Address type. */
#define AD_TYPE_SEC_MGR_OOB_FLAG_ADDRESS_TYPE_POS      3UL                      /**< Security Manager OOB Address type Flag (0 = Public Address, 1 = Random Address) position. */

/**@brief Payload field values of LE Role BLE GAP AD Type. Corresponds with @ref ble_advdata_le_role_t enum. */
typedef enum
{
    NFC_BLE_ADVDATA_ROLE_ENCODED_ONLY_PERIPH = 0,                      /**< Only Peripheral Role supported. */
    NFC_BLE_ADVDATA_ROLE_ENCODED_ONLY_CENTRAL,                         /**< Only Central Role supported. */
    NFC_BLE_ADVDATA_ROLE_ENCODED_BOTH_PERIPH_PREFERRED,                /**< Peripheral and Central Role supported. Peripheral Role preferred for connection establishment. */
    NFC_BLE_ADVDATA_ROLE_ENCODED_BOTH_CENTRAL_PREFERRED                /**< Peripheral and Central Role supported. Central Role preferred for connection establishment */
} nfc_ble_advdata_le_role_encoded_t;

/**@brief Function for encoding data in the Advertising and Scan Response data format, which
 *        is used for NFC OOB pairing.
 *
 *
 * @details This function encodes data into the Advertising and Scan Response data format (AD structures).
 *          Encoding is based on the selections in the supplied structures. This function uses
 *          @ref adv_data_encode to encode regular data and adds additional AD Structures which are specific
 *          for NFC OOB pairing: Security Manager TK Value, LESC OOB values, OOB Flags, and LE Role.
 *
 * @param[in]      p_advdata       Pointer to the structure for specifying the content of encoded data.
 * @param[out]     p_encoded_data  Pointer to the buffer where encoded data will be returned.
 * @param[in,out]  p_len           \c in: Size of \p p_encoded_data buffer.
 *                                 \c out: Length of encoded data.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_INVALID_PARAM If the operation failed because a wrong parameter was provided in \p p_advdata.
 * @retval NRF_ERROR_DATA_SIZE     If the operation failed because not all the requested data could fit into the
 *                                 provided buffer or some encoded AD structure is too long and its
 *                                 length cannot be encoded with one octet.
 */
ret_code_t nfc_ble_oob_adv_data_encode(ble_advdata_t const * const p_advdata,
                                       uint8_t             * const p_encoded_data,
                                       uint16_t            * const p_len);

/**@brief Function for encoding payload field of Security Manager TK Value AD Type.
 *
 * @param[in]     p_tk_value         Security Manager TK Value AD Type payload.
 * @param[out]    p_tk_payload_data  Pointer to the buffer where TK payload data will be stored.
 *
 */
void nfc_tk_value_payload_encode(ble_advdata_tk_value_t * p_tk_value,
                                 uint8_t                * p_tk_payload_data);

#endif // NFC_BLE_OOB_ADVDATA_H__

/** @} */
