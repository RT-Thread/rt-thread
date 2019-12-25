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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NFC_LE_OOB_REC)

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

ret_code_t nfc_le_oob_payload_constructor(ble_advdata_t * p_ble_advdata,
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

#endif // NRF_MODULE_ENABLED(NFC_LE_OOB_REC)
