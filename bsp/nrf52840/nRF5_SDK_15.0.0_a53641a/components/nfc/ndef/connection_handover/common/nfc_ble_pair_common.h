/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#ifndef NFC_BLE_PAIR_COMMON_H__
#define NFC_BLE_PAIR_COMMON_H__

#include <stdint.h>
#include "ble_advdata.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @defgroup nfc_ble_pair_common Common data for Connection Handover and Connection Handover Parser modules
 * @{
 * @ingroup nfc_ble_pair_msg
 */

#define AD_TYPE_LE_ROLE_DATA_SIZE       1UL                                     /**< Data size (in octets) of the LE Role AD type. */
#define AD_TYPE_LE_ROLE_SIZE            (AD_DATA_OFFSET + \
                                            AD_TYPE_LE_ROLE_DATA_SIZE)          /**< Size (in octets) of the LE Role AD type. */
#define AD_TYPE_TK_VALUE_DATA_SIZE      (sizeof(ble_advdata_tk_value_t))        /**< Data size (in octets) of the Security Manager TK value AD type. */
#define AD_TYPE_TK_VALUE_SIZE           (AD_DATA_OFFSET + \
                                            AD_TYPE_TK_VALUE_DATA_SIZE)         /**< Size (in octets) of the Security Manager TK value AD type. */
#define AD_TYPE_OOB_FLAGS_DATA_SIZE     1UL                                     /**< Data size (in octets) of the Security Manager OOB Flags AD type. */
#define AD_TYPE_OOB_FLAGS_SIZE          (AD_DATA_OFFSET + \
                                            AD_TYPE_OOB_FLAGS_DATA_SIZE)        /**< Size (in octets) of the Security Manager OOB Flags AD type. */

#define AD_TYPE_CONFIRM_VALUE_DATA_SIZE 16UL                                    /**< Data size (in octets) of the LESC Confirmation value. */
#define AD_TYPE_CONFIRM_VALUE_SIZE      (AD_DATA_OFFSET + \
                                            AD_TYPE_CONFIRM_VALUE_DATA_SIZE)    /**< Size (in octets) of the LESC Confirmation value AD type. */
#define AD_TYPE_RANDOM_VALUE_DATA_SIZE  16UL                                    /**< Data size (in octets) of the LESC Random value. */
#define AD_TYPE_RANDOM_VALUE_SIZE       (AD_DATA_OFFSET + \
                                            AD_TYPE_RANDOM_VALUE_DATA_SIZE)     /**< Size (in octets) of the LESC Random value AD type. */
#define AD_TYPE_LESC_SIZE               (AD_TYPE_RANDOM_VALUE_SIZE + \
                                            AD_TYPE_CONFIRM_VALUE_SIZE)         /**< Total size (in octets) of the LESC OOB AD data fields in NDEF message. */

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

/**
 * @brief External reference to the type field of the Bluetooth LE Carrier Configuration NDEF record, defined
 * in the file @c nfc_ble_pair_common.c
 */
extern const uint8_t le_oob_rec_type_field[32];

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_BLE_PAIR_COMMON_H__
