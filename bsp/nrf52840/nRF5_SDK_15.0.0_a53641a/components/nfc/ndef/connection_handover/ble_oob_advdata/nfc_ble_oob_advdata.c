/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NFC_BLE_OOB_ADVDATA)

#include "nfc_ble_oob_advdata.h"
#include "sdk_common.h"
#include "nfc_ble_pair_msg.h"
#include "nfc_ble_pair_common.h"


/**
 * @brief Macro for verifying basic parameters used for encoding single BLE AD Type.
 *
 * It verifies if provided buffer is NULL and if there is enough space for the encoded data.
 * In case of NULL pointer buffer, necessary space for current AD Type is calculated.
 *
 * @param[in] P_ENCODED_DATA   Buffer for the encoded data.
 * @param[in] P_OFFSET         Pointer to index of the first free cell in the buffer.
 * @param[in] AD_TYPE_SIZE     Size of the single AD Type.
 * @param[in] MAX_SIZE         Maximal size of the provided buffer.
 */
#define NFC_BLE_OOB_ADVDATA_INPUT_VERIFY( P_ENCODED_DATA, P_OFFSET, AD_TYPE_SIZE, MAX_SIZE) \
    if ( (P_ENCODED_DATA) == NULL )                                                         \
    {                                                                                       \
        *(P_OFFSET) += (AD_TYPE_SIZE);                                                      \
        return NRF_SUCCESS;                                                                 \
    }                                                                                       \
    if ( *(P_OFFSET) + (AD_TYPE_SIZE) > (MAX_SIZE) )                                        \
    {                                                                                       \
        return NRF_ERROR_DATA_SIZE;                                                         \
    }

/**@brief Function for encoding data of Security Manager OOB Flags AD Type.
 *
 * @param[in]      oob_flags       Security Manager OOB Flags AD Type payload.
 * @param[out]     p_encoded_data  Pointer to the buffer where encoded data will be returned.
 * @param[in,out]  p_offset        \c in: Offset of \p p_encoded_data buffer before this AD type encoding.
 *                                 \c out: Offset of \p p_encoded_data buffer after this AD type encoding.
 * @param[in]      max_size        Size of \p p_encoded_data buffer.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_DATA_SIZE     If the provided buffer size is too small.
 */
static ret_code_t sec_mgr_oob_flags_encode(uint8_t    oob_flags,
                                           uint8_t  * p_encoded_data,
                                           uint16_t * p_offset,
                                           uint16_t   max_size)
{
    NFC_BLE_OOB_ADVDATA_INPUT_VERIFY(p_encoded_data, p_offset, AD_TYPE_OOB_FLAGS_SIZE, max_size);

    // Encode flags.
    p_encoded_data[*p_offset]  = (uint8_t)(AD_TYPE_FIELD_SIZE + AD_TYPE_OOB_FLAGS_DATA_SIZE);
    *p_offset                 += AD_LENGTH_FIELD_SIZE;
    p_encoded_data[*p_offset]  = BLE_GAP_AD_TYPE_SECURITY_MANAGER_OOB_FLAGS;
    *p_offset                 += AD_TYPE_FIELD_SIZE;
    p_encoded_data[*p_offset]  = oob_flags;
    *p_offset                 += AD_TYPE_OOB_FLAGS_DATA_SIZE;

    return NRF_SUCCESS;
}

/**@brief Function for encoding data of Security Manager TK Value AD Type.
 *
 * @param[in]      p_tk_value      Security Manager TK Value AD Type payload.
 * @param[out]     p_encoded_data  Pointer to the buffer where encoded data will be returned.
 * @param[in,out]  p_offset        \c in: Offset of \p p_encoded_data buffer before this AD type encoding.
 *                                 \c out: Offset of \p p_encoded_data buffer after this AD type encoding.
 * @param[in]      max_size        Size of \p p_encoded_data buffer.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_DATA_SIZE     If the provided buffer size is too small.
 */
static ret_code_t tk_value_encode(ble_advdata_tk_value_t * p_tk_value,
                                  uint8_t                * p_encoded_data,
                                  uint16_t               * p_offset,
                                  uint16_t                 max_size)
{
    ret_code_t err_code;

    NFC_BLE_OOB_ADVDATA_INPUT_VERIFY(p_encoded_data, p_offset, AD_TYPE_TK_VALUE_SIZE, max_size);

    // Encode TK Value.
    p_encoded_data[*p_offset]  = (uint8_t)(AD_TYPE_FIELD_SIZE + AD_TYPE_TK_VALUE_DATA_SIZE);
    *p_offset                 += AD_LENGTH_FIELD_SIZE;
    p_encoded_data[*p_offset]  = BLE_GAP_AD_TYPE_SECURITY_MANAGER_TK_VALUE;
    *p_offset                 += AD_TYPE_FIELD_SIZE;

    // Remember location of TK in the buffer if this feature was enabled.
    err_code = nfc_tk_to_group_add(&p_encoded_data[*p_offset]);
    VERIFY_SUCCESS(err_code);

    nfc_tk_value_payload_encode(p_tk_value, &p_encoded_data[*p_offset]);
    (*p_offset) += AD_TYPE_TK_VALUE_DATA_SIZE;

    return NRF_SUCCESS;
}

/**@brief Function for encoding LESC OOB data in the CH NDEF message.
 *
 * @param[in]      p_lesc_value    Pointer to the LESC OOB values to be encoded.
 * @param[out]     p_encoded_data  Pointer to the buffer where encoded data will be returned.
 * @param[in,out]  p_offset        \c in: Offset of \p p_encoded_data buffer before this AD type encoding.
 *                                 \c out: Offset of \p p_encoded_data buffer after this AD type encoding.
 * @param[in]      max_size        Size of \p p_encoded_data buffer.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_DATA_SIZE     If the provided buffer size is too small.
 */
static ret_code_t lesc_value_encode(ble_gap_lesc_oob_data_t * p_lesc_value,
                                    uint8_t                 * p_encoded_data,
                                    uint16_t                * p_offset,
                                    uint16_t                  max_size)
{
    ret_code_t err_code;

    NFC_BLE_OOB_ADVDATA_INPUT_VERIFY(p_encoded_data, p_offset, AD_TYPE_LESC_SIZE, max_size);

    // Encode LESC Confirm Value.
    p_encoded_data[*p_offset]  = (uint8_t)(AD_TYPE_FIELD_SIZE + AD_TYPE_CONFIRM_VALUE_DATA_SIZE);
    *p_offset                 += AD_LENGTH_FIELD_SIZE;
    p_encoded_data[*p_offset]  = BLE_GAP_AD_TYPE_LESC_CONFIRMATION_VALUE;
    *p_offset                 += AD_TYPE_FIELD_SIZE;

    memcpy(&p_encoded_data[*p_offset], p_lesc_value->c, sizeof(p_lesc_value->c));

    uint8_t *p_confirm = &p_encoded_data[*p_offset];

    (*p_offset) += AD_TYPE_CONFIRM_VALUE_DATA_SIZE;

    // Encode LESC Random Value.
    p_encoded_data[*p_offset]  = (uint8_t)(AD_TYPE_FIELD_SIZE + AD_TYPE_RANDOM_VALUE_DATA_SIZE);
    *p_offset                 += AD_LENGTH_FIELD_SIZE;
    p_encoded_data[*p_offset]  = BLE_GAP_AD_TYPE_LESC_RANDOM_VALUE;
    *p_offset                 += AD_TYPE_FIELD_SIZE;

    memcpy(&p_encoded_data[*p_offset], p_lesc_value->r, sizeof(p_lesc_value->r));

    uint8_t *p_random = &p_encoded_data[*p_offset];

    (*p_offset) += AD_TYPE_RANDOM_VALUE_DATA_SIZE;

    // Remember location of LESC OOB data in the buffer in case of key changes.
    err_code = nfc_lesc_pos_set(p_confirm, p_random);

    return err_code;
}

/**@brief Function for encoding data of LE Role AD Type.
 *
 * @param[in]      le_role         LE Role AD Type payload.
 * @param[out]     p_encoded_data  Pointer to the buffer where encoded data will be returned.
 * @param[in,out]  p_offset        \c in: Offset of \p p_encoded_data buffer before this AD type encoding.
 *                                 \c out: Offset of \p p_encoded_data buffer after this AD type encoding.
 * @param[in]      max_size        Size of \p p_encoded_data buffer.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_DATA_SIZE     If the provided buffer size is too small.
 * @retval NRF_ERROR_INVALID_PARAM If \p le_role parameter has invalid value.
 */
static ret_code_t le_role_encode(ble_advdata_le_role_t   le_role,
                                 uint8_t               * p_encoded_data,
                                 uint16_t              * p_offset,
                                 uint16_t                max_size)
{
    NFC_BLE_OOB_ADVDATA_INPUT_VERIFY(p_encoded_data, p_offset, AD_TYPE_LE_ROLE_SIZE, max_size);

    // Encode LE Role.
    p_encoded_data[*p_offset]  = (uint8_t)(AD_TYPE_FIELD_SIZE + AD_TYPE_LE_ROLE_DATA_SIZE);
    *p_offset                 += AD_LENGTH_FIELD_SIZE;
    p_encoded_data[*p_offset]  = BLE_GAP_AD_TYPE_LE_ROLE;
    *p_offset                 += AD_TYPE_FIELD_SIZE;
    switch (le_role)
    {
        case BLE_ADVDATA_ROLE_ONLY_PERIPH:
            p_encoded_data[*p_offset] = NFC_BLE_ADVDATA_ROLE_ENCODED_ONLY_PERIPH;
            break;
        case BLE_ADVDATA_ROLE_ONLY_CENTRAL:
            p_encoded_data[*p_offset] = NFC_BLE_ADVDATA_ROLE_ENCODED_ONLY_CENTRAL;
            break;
        case BLE_ADVDATA_ROLE_BOTH_PERIPH_PREFERRED:
            p_encoded_data[*p_offset] = NFC_BLE_ADVDATA_ROLE_ENCODED_BOTH_PERIPH_PREFERRED;
            break;
        case BLE_ADVDATA_ROLE_BOTH_CENTRAL_PREFERRED:
            p_encoded_data[*p_offset] = NFC_BLE_ADVDATA_ROLE_ENCODED_BOTH_CENTRAL_PREFERRED;
            break;
        default:
            return NRF_ERROR_INVALID_PARAM;
    }
    *p_offset += AD_TYPE_LE_ROLE_DATA_SIZE;

    return NRF_SUCCESS;
}

/**@brief Function for calculating the size of Local Name AD Type.
 *
 * @param[in]      p_advdata  Pointer to the structure for specifying the content of encoded data.
 * @param[out]     p_len      Size of the buffer that is necessary to encode Local Name AD Type.
 *
 * @retval NRF_SUCCESS    If the operation was successful.
 * @retval Other          Other error codes might be returned depending on
 *                        @ref sd_ble_gap_device_name_get function.
 */
__STATIC_INLINE ret_code_t nfc_ble_oob_name_size_calc(ble_advdata_t const * const p_advdata,
                                                      uint16_t            * const p_len)
{
    ret_code_t err_code = NRF_SUCCESS;
    uint16_t   device_len;

    if (p_advdata->name_type == BLE_ADVDATA_SHORT_NAME)
    {
        device_len = p_advdata->short_name_len;
    }
    else
    {
        err_code = sd_ble_gap_device_name_get(NULL, &device_len);
    }

    *p_len  += AD_LENGTH_FIELD_SIZE + AD_TYPE_FIELD_SIZE + device_len;
    return err_code;
}

/**@brief Function for calculating the size of AD Types which are encoded by @ref ble_advdata_encode function.
 *
 * @param[in]      p_advdata  Pointer to the structure for specifying the content of encoded data.
 * @param[out]     p_len      Size of the buffer that is necessary to encode AD Types.
 *
 * @retval NRF_SUCCESS        If the operation was successful.
 * @retval Other              Other error codes might be returned depending on
 *                            @ref nfc_ble_oob_name_size_calc function.
 */
static ret_code_t nfc_ble_oob_adv_data_size_calc(ble_advdata_t const * const p_advdata,
                                                 uint16_t            * const p_len)
{
    ret_code_t err_code = NRF_SUCCESS;

    if (p_advdata->include_ble_device_addr)
    {
        *p_len += AD_TYPE_BLE_DEVICE_ADDR_SIZE;
    }
    if (p_advdata->include_appearance)
    {
        *p_len += AD_TYPE_APPEARANCE_SIZE;
    }
    if (p_advdata->flags != 0)
    {
        *p_len += AD_TYPE_FLAGS_SIZE;
    }
    if (p_advdata->name_type != BLE_ADVDATA_NO_NAME)
    {
        err_code = nfc_ble_oob_name_size_calc(p_advdata, p_len);
    }
    return err_code;
}

#if ADVANCED_ADVDATA_SUPPORT == 0
/**@brief Function for verifying if BLE advertising data structure contains only supported AD Types
 *        by this encoding module.
 *
 * @param[in]   advdata                  Structure with BLE advertising data.
 *
 * @retval      NRF_SUCCESS              If the verification was successful.
 * @retval      NRF_ERROR_INVALID_PARAM  If there is any AD type which is not supported by this
 *                                       module.
 */
static ret_code_t nfc_ble_oob_adv_data_check(ble_advdata_t advdata)
{
    advdata.p_sec_mgr_oob_flags     = NULL;
    advdata.p_tk_value              = NULL;
    advdata.le_role                 = BLE_ADVDATA_ROLE_NOT_PRESENT;
    advdata.include_ble_device_addr = false;
    advdata.include_appearance      = false;
    advdata.flags                   = 0;
    advdata.name_type               = BLE_ADVDATA_NO_NAME;
    advdata.short_name_len          = 0;
    advdata.p_lesc_data             = NULL;

    ble_advdata_t pattern_advdata;
    memset(&pattern_advdata, 0, sizeof(ble_advdata_t));

    if ( memcmp( &pattern_advdata, &advdata, sizeof(ble_advdata_t)) == 0 )
    {
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }
}
#endif //ADVANCED_ADVDATA_SUPPORT

ret_code_t nfc_ble_oob_adv_data_encode(ble_advdata_t const * const p_advdata,
                                       uint8_t             * const p_encoded_data,
                                       uint16_t            * const p_len)
{
    ret_code_t err_code = NRF_SUCCESS;
    uint16_t   max_size = *p_len;
    uint16_t   offset   = 0;

#if ADVANCED_ADVDATA_SUPPORT
    // In this mode, you cannot count the NDEF message length.
    VERIFY_FALSE(p_encoded_data == NULL, NRF_ERROR_INVALID_PARAM);
#else
    // Verify ADV data structure.
    err_code = nfc_ble_oob_adv_data_check(*p_advdata);
    VERIFY_SUCCESS(err_code);
#endif //ADVANCED_ADVDATA_SUPPORT

    // Encode Security Manager OOB Flags.
    if (p_advdata->p_sec_mgr_oob_flags != NULL)
    {
        err_code = sec_mgr_oob_flags_encode(*p_advdata->p_sec_mgr_oob_flags,
                                             p_encoded_data,
                                             &offset,
                                             max_size);
        VERIFY_SUCCESS(err_code);
    }

    // Encode LESC keys
    if (p_advdata->p_lesc_data != NULL)
    {
        err_code = lesc_value_encode(p_advdata->p_lesc_data, p_encoded_data, &offset, max_size);
        VERIFY_SUCCESS(err_code);
    }

    // Encode Security Manager TK value.
    if (p_advdata->p_tk_value != NULL)
    {
        err_code = tk_value_encode(p_advdata->p_tk_value, p_encoded_data, &offset, max_size);
        VERIFY_SUCCESS(err_code);
    }

    // Encode LE Role.
    if (BLE_ADVDATA_ROLE_NOT_PRESENT != p_advdata->le_role)
    {
        err_code = le_role_encode(p_advdata->le_role, p_encoded_data, &offset, max_size);
        VERIFY_SUCCESS(err_code);
    }

    // Encode remaining AD Types or precalculate necessary buffer space.
    if (p_encoded_data != NULL)
    {
        uint16_t adv_data_size = max_size - offset;
        err_code = ble_advdata_encode(p_advdata, p_encoded_data + offset, &adv_data_size);
        *p_len   = offset + adv_data_size;
    }
    else
    {
        err_code = nfc_ble_oob_adv_data_size_calc(p_advdata, &offset);
        *p_len   = offset;
    }

    return err_code;
}

void nfc_tk_value_payload_encode(ble_advdata_tk_value_t * p_tk_value,
                                 uint8_t                * p_tk_payload_data)
{
    for (uint8_t i = 0; i < AD_TYPE_TK_VALUE_DATA_SIZE; i++)
    {
        *(p_tk_payload_data++) = p_tk_value->tk[i];
    }
}

#endif // NRF_MODULE_ENABLED(NFC_BLE_OOB_ADVDATA)
