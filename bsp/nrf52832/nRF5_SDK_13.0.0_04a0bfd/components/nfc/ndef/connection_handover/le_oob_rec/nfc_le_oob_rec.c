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
#include "nfc_le_oob_rec.h"
#include "sdk_errors.h"
#include "ble_gap.h"
#include "nfc_ble_pair_common.h"

/**
 * @brief Function for validating AD structure content for a Bluetooth Carrier Configuration LE record.
 *
 * This function validates AD structure content. LE Bluetooth Device Address and LE Role
 * fields are required. Security Manager Out Of Band Flags structure must not be included.
 *
 * @param[in]       p_ble_advdata   Pointer to the description of the payload.
 *
 * @retval NRF_SUCCESS                     If the validation was successful.
 * @retval NRF_ERROR_INVALID_PARAM         Otherwise.
 */
static ret_code_t nfc_le_oob_adv_data_check(ble_advdata_t const *  const p_ble_advdata)
{
    if ((false == p_ble_advdata->include_ble_device_addr)        ||
       (BLE_ADVDATA_ROLE_NOT_PRESENT == p_ble_advdata->le_role) ||
       (NULL != p_ble_advdata->p_sec_mgr_oob_flags))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    /* If Flags field in AD structure is present, the BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED flag
       must be set. */
    if ((0 != p_ble_advdata->flags) &&
            ((p_ble_advdata->flags & BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED) == 0))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    return NRF_SUCCESS;
}

/**
 * @brief Function for constructing the payload for a Bluetooth Carrier Configuration LE record.
 *
 * This function encodes the record payload according to the BLE AD structure. It implements
 * an API compatible with @ref p_payload_constructor_t
 *
 * @param[in]       p_ble_advdata   Pointer to the description of the payload.
 * @param[out]      p_buff          Pointer to payload destination. If NULL, function will
 *                                  calculate the expected size of the record payload.
 *
 * @param[in,out]   p_len           Size of available memory to write as input. Size of generated
 *                                  payload as output.
 *
 * @retval NRF_SUCCESS   If the record payload was encoded successfully.
 * @retval Other         If the record payload encoding failed.
 */
static ret_code_t nfc_le_oob_payload_constructor(ble_advdata_t * p_ble_advdata,
                                                 uint8_t       * p_buff,
                                                 uint32_t      * p_len)
{
    ret_code_t err_code = NRF_SUCCESS;

    /* Check correctness of the configuration structure */
    err_code = nfc_le_oob_adv_data_check(p_ble_advdata);
    if (NRF_SUCCESS != err_code)
    {
        return err_code;
    }

    /* Encode AD structures into NFC record payload */
    uint16_t buff_len = *p_len;
    if (*p_len > UINT16_MAX)
    {
        buff_len = UINT16_MAX;
    }
    err_code = nfc_ble_oob_adv_data_encode(p_ble_advdata, p_buff, &buff_len);

    /* Update total payload length */
    *p_len = (uint32_t) buff_len;

    return err_code;
}

nfc_ndef_record_desc_t * nfc_le_oob_rec_declare(uint8_t                        rec_payload_id,
                                                ble_advdata_t    const * const p_ble_advdata)
{
    static uint8_t payload_id = 0;

    NFC_NDEF_GENERIC_RECORD_DESC_DEF( nfc_le_oob_rec,
                                      TNF_MEDIA_TYPE,
                                      &payload_id,   // memory for possible ID value
                                      0,             // no ID by default
                                      (le_oob_rec_type_field),
                                      sizeof(le_oob_rec_type_field),
                                      nfc_le_oob_payload_constructor,
                                      NULL);

    nfc_ndef_record_desc_t * nfc_le_oob_rec = &NFC_NDEF_GENERIC_RECORD_DESC( nfc_le_oob_rec);

    /* Update record descriptor */
    nfc_le_oob_rec->p_payload_descriptor = (void *) p_ble_advdata;

    /* Handle record ID configuration */
    payload_id                = rec_payload_id;
    nfc_le_oob_rec->id_length = (rec_payload_id != 0) ? 1 : 0;

    return nfc_le_oob_rec;
}
