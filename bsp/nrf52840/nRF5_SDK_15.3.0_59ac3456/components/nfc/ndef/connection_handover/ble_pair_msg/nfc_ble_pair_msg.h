/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef NFC_BLE_PAIR_MSG_H__
#define NFC_BLE_PAIR_MSG_H__

/**@file
 *
 * @defgroup nfc_modules NDEF message modules
 * @ingroup nfc_api
 * @brief Implementation of NDEF messages.
 *
 * @defgroup nfc_ndef_messages Predefined NDEF messages
 * @ingroup nfc_modules
 * @brief Predefined NDEF messages for standard use.
 *
 * @defgroup nfc_ble_pair_msg BLE pairing messages
 * @{
 * @ingroup  nfc_ndef_messages
 *
 * @brief    Generation of NFC NDEF messages used for BLE pairing.
 *
 */

#include <stdint.h>
#include "ble_advdata.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Types of BLE pairing message.
 *
 * Use one of these values to choose the type of NDEF BLE pairing message.
 */
typedef enum
{
    NFC_BLE_PAIR_MSG_BLUETOOTH_LE_SHORT, ///< Simplified LE OOB message.
    NFC_BLE_PAIR_MSG_BLUETOOTH_EP_SHORT, ///< Simplified EP OOB message.
    NFC_BLE_PAIR_MSG_FULL                ///< BLE Handover Select Message.
} nfc_ble_pair_type_t;

/** @brief Function for encoding simplified LE OOB messages.
 *
 * This function encodes a simplified LE OOB message into a buffer. The payload of the LE OOB record
 * inside the message can be configured via the advertising data structure.
 *
 * This function was implemented partially according to "Bluetooth Secure Simple Pairing Using NFC"
 * (denotation "NFCForum-AD-BTSSP_1_1" published on 2014-01-09) chapters 3.1, 3.2, 4.3.2,
 * and according to "Supplement to the Bluetooth Core Specification" (Version 5, adoption date:
 * Dec 02 2014).
 *
 * @note To be able to encode the message, a SoftDevice must be enabled and configured.
 *
 * @param[in]       p_le_advdata        Pointer to the BLE advertising data structure for the LE OOB record.
 * @param[out]      p_buf               Pointer to the buffer for the message.
 * @param[in,out]   p_len               Size of the available memory for the message as input.
 *                                      Size of the generated message as output.
 *
 * @retval NRF_SUCCESS                  If the function completed successfully.
 * @retval NRF_ERROR_xxx                If an error occurred.
 */
ret_code_t nfc_ble_simplified_le_oob_msg_encode(ble_advdata_t const * const p_le_advdata,
                                                uint8_t             *       p_buf,
                                                uint32_t            *       p_len);

/** @brief Function for encoding simplified EP OOB messages.
 *
 * This function encodes a simplified EP OOB message into a buffer. The payload of the EP OOB record
 * inside the message can be configured via the advertising data structure.
 *
 * This function was implemented partially according to "Bluetooth Secure Simple Pairing Using NFC"
 * (denotation "NFCForum-AD-BTSSP_1_1" published on 2014-01-09) chapters 3.1, 3.2, 4.3.1,
 * and according to "Supplement to the Bluetooth Core Specification" (Version 5, adoption date:
 * Dec 02 2014).
 *
 * @note To be able to encode the message, a SoftDevice must be enabled and configured.
 *
 * @param[in]       p_ep_advdata        Pointer to the BLE advertising data structure for the EP OOB record.
 * @param[out]      p_buf               Pointer to the buffer for the message.
 * @param[in,out]   p_len               Size of the available memory for the message as input.
 *                                      Size of the generated message as output.
 *
 * @retval NRF_SUCCESS                  If the function completed successfully.
 * @retval NRF_ERROR_xxx                If an error occurred.
 */
ret_code_t nfc_ble_simplified_ep_oob_msg_encode(ble_advdata_t const * const p_ep_advdata,
                                                uint8_t             *       p_buf,
                                                uint32_t            *       p_len);

/** @brief Function for encoding BLE Handover Select Messages.
 *
 * This function encodes a BLE Handover Select Message into a buffer. The payload of the LE OOB record
 * and the EP OOB record inside the message can be configured via the advertising data structures.
 *
 * This function was implemented partially according to "Bluetooth Secure Simple Pairing Using NFC"
 * (denotation "NFCForum-AD-BTSSP_1_1" published on 2014-01-09) chapters 3.1, 3.2, 4.1.1
 * and 4.1.2 (combined), and according to "Supplement to the Bluetooth Core Specification" (Version 5,
 * adoption date: Dec 02 2014).
 *
 * @note To be able to encode the message, a SoftDevice must be enabled and configured.
 *
 * @param[in]       p_le_advdata        Pointer to the BLE advertising data structure for the LE OOB record.
 * @param[in]       p_ep_advdata        Pointer to the BLE advertising data structure for the EP OOB record.
 * @param[out]      p_buf               Pointer to the buffer for the message.
 * @param[in,out]   p_len               Size of the available memory for the message as input.
 *                                      Size of the generated message as output.
 *
 * @retval NRF_SUCCESS                  If the function completed successfully.
 * @retval NRF_ERROR_xxx                If an error occurred.
 */
ret_code_t nfc_ble_full_handover_select_msg_encode(ble_advdata_t const * const p_le_advdata,
                                                   ble_advdata_t const * const p_ep_advdata,
                                                   uint8_t             *       p_buf,
                                                   uint32_t            *       p_len);

/** @brief Function for encoding any type of BLE pairing messages with default BLE
 *         advertising data structures.
 *
 * This function encodes a BLE pairing message into a buffer. The message can be encoded as
 * one of the three message types (using @ref nfc_ble_simplified_le_oob_msg_encode,
 * @ref nfc_ble_simplified_ep_oob_msg_encode, or @ref nfc_ble_full_handover_select_msg_encode),
 * according to the @p nfc_ble_pair_type parameter. LE and EP OOB records use the default
 * advertising data structure configuration. Only one field ('Security Manager TK') in the BLE
 * advertising data can be configured for both records by specifying the @p p_tk_value parameter.
 *
 * For LE OOB records, the default BLE advertising data structure configuration fills the required
 * fields 'LE Bluetooth Device Address' and 'LE Role' and the optional fields 'Appearance',
 * 'Local Name', and 'Flags'.
 *
 * For EP OOB records, the default BLE advertising data structure configuration fills the required
 * field 'Security Manager Out Of Band Flags' and the optional fields 'Appearance',
 * 'Local Name', and 'Flags'.
 *
 * @note To be able to encode the message, a SoftDevice must be enabled and configured.
 *
 * @param[in]       nfc_ble_pair_type   Type of BLE pairing message.
 * @param[in]       p_tk_value          Pointer to the authentication Temporary Key (TK). If NULL,
 *                                      TK value field is not encoded in the NDEF message.
 * @param[in]       p_lesc_data         Pointer to the LESC OOB data. If NULL, LESC OOB fields are
 *                                      not encoded in the NDEF message.
 * @param[out]      p_buf               Pointer to the buffer for the message.
 * @param[in,out]   p_len               Size of the available memory for the message as input.
 *                                      Size of the generated message as output.
 *
 * @retval NRF_SUCCESS                  If the function completed successfully.
 * @retval NRF_ERROR_xxx                If an error occurred.
 */
ret_code_t nfc_ble_pair_default_msg_encode(nfc_ble_pair_type_t             nfc_ble_pair_type,
                                           ble_advdata_tk_value_t  * const p_tk_value,
                                           ble_gap_lesc_oob_data_t * const p_lesc_data,
                                           uint8_t                 *       p_buf,
                                           uint32_t                *       p_len);

/** @brief Function for encoding any type of BLE pairing messages with default BLE
 *         advertising data structures and with TK modifier feature.
 *
 * This function is very similar to the @ref nfc_ble_pair_default_msg_encode function, but
 * additionaly enables tracking of TK locations which were encoded in the Connection Handover
 * NDEF message. After using this function, you can update the TK value in NDEF by calling
 * @ref nfc_tk_group_modifier_update.
 *
 * @param[in]       nfc_ble_pair_type   Type of BLE pairing message.
 * @param[in]       p_tk_value          Pointer to the authentication Temporary Key (TK). If NULL,
 *                                      TK value field is not encoded in the NDEF message.
 * @param[in]       p_lesc_data         Pointer to the LESC OOB data. If NULL, LESC OOB values are
 *                                      not encoded in the NDEF message.
 * @param[out]      p_buf               Pointer to the buffer for the message.
 * @param[in,out]   p_len               Size of the available memory for the message as input.
 *                                      Size of the generated message as output.
 * @param[in]       pp_tk_group         Pointer to array of TK locations that should be modified with
 *                                      @ref nfc_tk_group_modifier_update function.
 * @param[in]       max_group_size      Maximal number of TK locations that can added to \p pp_tk_group.
 *
 * @retval NRF_SUCCESS                  If the function completed successfully.
 * @retval NRF_ERROR_xxx                If an error occurred.
 */
ret_code_t nfc_ble_pair_msg_updatable_tk_encode(nfc_ble_pair_type_t             nfc_ble_pair_type,
                                                ble_advdata_tk_value_t  * const p_tk_value,
                                                ble_gap_lesc_oob_data_t * const p_lesc_data,
                                                uint8_t                 *       p_buf,
                                                uint32_t                *       p_len,
                                                uint8_t                 **      pp_tk_group,
                                                uint8_t                         max_group_size);

/**@brief Function for updating the Connection Handover NDEF message with new TK value.
 *
 * @details This function updates NDEF message with new TK value. This update is applied to all of
 *          TK locations in the Connection Handover NDEF message. This function can only be used
 *          after calling @ref nfc_ble_pair_msg_updatable_tk_encode, which is used to encode
 *          Connection Handover NDEF message.
 *
 * @param[in]  p_tk_value      Pointer to the new TK value. The NDEF message will be updated with this
 *                             value.
 *
 * @retval     NRF_SUCCESS     If the operation was successful.
 * @retval     NRF_ERROR_NULL  If pointer to TK locations was NULL.
 */
ret_code_t nfc_tk_group_modifier_update(ble_advdata_tk_value_t * p_tk_value);

/**@brief Function for adding new location of TK value to the location description structure.
 *
 * @param[in] p_tk_location           New location of TK value in the Connection Handover NDEF message.
 *
 * @retval    NRF_SUCCESS             If the operation was successful or if buffer used for holding TK
 *                                    locations is NULL.
 * @retval    NRF_ERROR_NO_MEM        If there is no place in the buffer for the new TK value location.
 */
ret_code_t nfc_tk_to_group_add(uint8_t * p_tk_location);

/**@brief Function for updating the Connection Handover NDEF message with a new LESC OOB values.
 *
 * @details Updates LESC Confirmation and Random Values based on its locations set by the @ref nfc_lesc_pos_set function.
 *
 * @param[in]  p_ble_lesc_oob_data      Pointer to the new LESC OOB data. The NDEF message will be updated with this data.
 *
 * @retval     NRF_SUCCESS              If the operation was successful.
 * @retval     NRF_ERROR_NULL           If pointer to the new LESC OOB data is NULL.
 * @retval     NRF_ERROR_INVALID_STATE  If pointer to the LESC OOB data location in NDEF message is NULL.
 */
ret_code_t nfc_lesc_data_update(ble_gap_lesc_oob_data_t * p_ble_lesc_oob_data);

/**@brief Function for storing pointers to the LESC OOB data inside NDEF message.
 *
 * @details It allows LESC OOB data update without regenerating entire CH NDEF message.
 *
 * @param[in] p_confirm         Pointer to the LESC Confirmation Value position in the NDEF message.
 * @param[in] p_random          Pointer to the LESC Random Value position in the NDEF message.
 *
 * @retval    NRF_SUCCESS       If the operation was successful.
 * @retval    NRF_ERROR_NULL    If either of pointers is set to NULL.
 */
ret_code_t nfc_lesc_pos_set(uint8_t * p_confirm, uint8_t * p_random);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_BLE_PAIR_MSG_H__
