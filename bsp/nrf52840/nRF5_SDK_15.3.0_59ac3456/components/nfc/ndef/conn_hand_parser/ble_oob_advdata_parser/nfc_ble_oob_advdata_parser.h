/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
 * @defgroup nfc_ble_oob_advdata_parser Advertising and Scan Response Data Parser for NFC OOB pairing
 * @{
 * @ingroup nfc_ble_pair_msg
 * @brief Functions for parsing and decoding data in the Advertising and Scan Response
 *        Data format for NFC OOB pairing.
 */

#ifndef NFC_BLE_OOB_ADVDATA_PARSER_H_
#define NFC_BLE_OOB_ADVDATA_PARSER_H_

#include "sdk_errors.h"
#include "ble_advdata.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_ADVDATA_APPEARANCE_NOT_PRESENT    0    /**< Appearance AD structure not present. */

/**@brief Bluetooth Low Energy GAP device name. */
typedef struct
{
    ble_advdata_name_type_t   name_type;    /**< See @ref ble_advdata_name_type_t. */
    uint8_t                   len;          /**< Length of device name. */
    uint8_t                 * p_name;       /**< Pointer to the buffer with device name. */
} ble_gap_dev_name_t;

/**@brief BLE Advertising data that is relevant for OOB pairing. */
typedef struct
{
    ble_gap_dev_name_t        device_name;              /**< See @ref ble_gap_dev_name_t. */
    ble_gap_addr_t          * p_device_addr;            /**< See @ref ble_gap_addr_t. */
    ble_advdata_tk_value_t  * p_tk_value;               /**< See @ref ble_advdata_tk_value_t. */
    uint8_t                 * p_lesc_confirm_value;     /**< LESC OOB confirmation data. */
    uint8_t                 * p_lesc_random_value;      /**< LESC OOB random data. */
    ble_advdata_le_role_t     le_role;                  /**< See @ref ble_advdata_le_role_t. */
    uint16_t                  appearance;               /**< Advertising data Appearance field. */
    uint8_t                   flags;                    /**< Advertising data Flags field. */
    uint8_t                 * p_sec_mgr_oob_flags;      /**< Security Manager Out Of Band Flags data field. */
} nfc_ble_oob_pairing_data_t;

/**@brief Function for parsing BLE data encoded in AD Type format.
 *
 *        @details This function parses BLE data encoded in Advertising Data Type format which
 *        can be generated with @ref ble_advdata_encode function. The result of the parsing is
 *        stored within @ref nfc_ble_oob_pairing_data_t structure.
 *
 *        @note Currently, module can be used to parse BLE AD Type data, which contains
 *        AD Structures with following GAP AD Types: Flags, Shortened and Complete Device
 *        Name, Security Manager TK Value and OOB Flags, Appearance, LE Bluetooth Device
 *        Address and LE Role.
 *
 *        @warning Before passing \p p_nfc_ble_pairing_data structure to this function,
 *        it is necessary to provide buffers for AD Structures Data, which are expected to be
 *        found within parsed buffer. This applies to following GAP AD Types with corresponding
 *        structures: Shortened and Complete Device Name - @ref ble_gap_dev_name_t,
 *        LE Bluetooth Device Address - @ref ble_gap_addr_t, Security Manager TK Value -
 *        @ref ble_advdata_tk_value_t and Security Manager OOB Flags - uint8_t.
 *
 *        @param[in]    p_advdata               Pointer to the data to be parsed.
 *        @param[in]    len                     Size of the data to be parsed.
 *        @param[out]   p_nfc_ble_pairing_data  Pointer to the structure that will be used
 *                                              to hold parsed data.
 *
 *        @retval       NRF_SUCCESS              If the function completed successfully.
 *        @retval       NRF_ERROR_NO_MEM         If the provided buffer for device name is
 *                                               too small to hold parsed data.
 *        @retval       NRF_ERROR_INVALID_LENGTH If any AD Structure Length field contains
 *                                               different value than expected.
 *        @retval       NRF_ERROR_INVALID_PARAM  If any AD Structure Data field contains
 *                                               invalid parameters.
 *        @retval       NRF_ERROR_NULL           If any function pointer parameter is NULL or
 *                                               any expected buffer in \p p_nfc_ble_pairing_data
 *                                               was not provided.
 *        @retval       NRF_ERROR_NOT_SUPPORTED  If any AD Structure Type field contains
 *                                               type which is not supported or any AD
 *                                               Structure Type occurs more than once.
 */
ret_code_t nfc_ble_oob_advdata_parse(uint8_t              const * p_advdata,
                                     uint8_t                      len,
                                     nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data);


/**@brief Function for displaying values of basic BLE OOB Advertising data types.
 *
 *        @param[in]   p_pairing_data    Structure containing parsed data.
 */
void nfc_oob_data_printout(nfc_ble_oob_pairing_data_t const * const p_pairing_data);

#ifdef __cplusplus
}
#endif

#endif //NFC_BLE_OOB_ADVDATA_PARSER_H__

/** @} */
