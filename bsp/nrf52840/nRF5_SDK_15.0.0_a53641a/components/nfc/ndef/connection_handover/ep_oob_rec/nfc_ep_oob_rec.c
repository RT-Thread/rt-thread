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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NFC_EP_OOB_REC)

#include "nfc_ep_oob_rec.h"
#include "sdk_errors.h"
#include "ble_gap.h"
#include "app_util.h"

/* NFC OOB EP definitions */
#define NFC_EP_OOB_REC_GAP_ADDR_LEN          BLE_GAP_ADDR_LEN
#define NFC_EP_OOB_REC_OOB_DATA_LEN_SIZE     2UL
#define NFC_EP_OOB_REC_PAYLOAD_PREFIX_LEN    (NFC_EP_OOB_REC_GAP_ADDR_LEN + \
                                             NFC_EP_OOB_REC_OOB_DATA_LEN_SIZE)

/* Record Payload Type for Bluetooth Carrier Configuration EP record */
const uint8_t ndef_ep_oob_record_type[] =
{
    'a', 'p', 'p', 'l', 'i', 'c', 'a', 't', 'i', 'o', 'n', '/', 'v', 'n', 'd', '.',
    'b', 'l', 'u', 'e', 't', 'o', 'o', 't', 'h', '.', 'e', 'p', '.', 'o', 'o', 'b'
};

/**
 * @brief Function for validating AD structure content for a Bluetooth Carrier Configuration EP record.
 *
 * This function validates AD structure content. LE Bluetooth Device Address and LE Role
 * fields must not be included. Security Manager OOB Flags structure is required.
 *
 * @param[in]       p_ble_advdata   Pointer to the description of the payload.
 *
 * @retval NRF_SUCCESS                     If the validation was successful.
 * @retval NRF_ERROR_INVALID_PARAM         Otherwise.
 */
static ret_code_t nfc_ep_oob_adv_data_check(ble_advdata_t const *  const p_ble_advdata)
{
    if ((true == p_ble_advdata->include_ble_device_addr)         ||
       (BLE_ADVDATA_ROLE_NOT_PRESENT != p_ble_advdata->le_role) ||
       (NULL == p_ble_advdata->p_sec_mgr_oob_flags))
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
 * @brief Function for encoding device address to Bluetooth Carrier Configuration EP record.
 *
 * This fuction is used to encode device address to Bluetooth Carrier Configuration EP record.
 *
 * @param[in]       p_encoded_data      Pointer to the buffer where encoded data will be returned.
 * @param[in]       max_len             Available memory in the buffer.
 *
 * @retval NRF_SUCCESS                  If the encoding was successful.
 * @retval NRF_ERROR_NO_MEM             If available memory was not enough.
 * @retval NRF_ERROR_xxx                If any other error occured.
 */
static ret_code_t nfc_ep_oob_bluetooth_device_address_encode(uint8_t  * const p_encoded_data,
                                                             uint16_t         max_len)
{
    ret_code_t      err_code = NRF_SUCCESS;
    ble_gap_addr_t  device_address;

    memset(&device_address, 0x00, sizeof(device_address));

    if (NFC_EP_OOB_REC_GAP_ADDR_LEN > max_len)
    {
        return NRF_ERROR_NO_MEM;
    }

    /* Get BLE address */
    err_code = sd_ble_gap_addr_get(&device_address);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    /* Encode Bluetooth EP device address */
    memcpy(p_encoded_data, device_address.addr, NFC_EP_OOB_REC_GAP_ADDR_LEN);

    return NRF_SUCCESS;
}

ret_code_t nfc_ep_oob_payload_constructor(ble_advdata_t * p_ble_advdata,
                                          uint8_t       * p_buff,
                                          uint32_t      * p_len)
{
    ret_code_t  err_code  = NRF_SUCCESS;
    uint8_t   * p_ad_data = NULL;
    uint16_t    payload_len, ad_data_len;

    /* Check correctness of the configuration structure */
    err_code = nfc_ep_oob_adv_data_check(p_ble_advdata);
    if (NRF_SUCCESS != err_code)
    {
        return err_code;
    }

    if (p_buff != NULL)
    {
        /* Validate if there is enough memory for OOB payload length field and BLE device address */
        if (NFC_EP_OOB_REC_PAYLOAD_PREFIX_LEN > *p_len)
        {
            return NRF_ERROR_NO_MEM;
        }

        /* Set proper memory offset in payload buffer for AD structure and count available memory.
         * Bluetooth EP device address and OOB payload length field must be inserted before the AD payload */
        p_ad_data   = (uint8_t *) (p_buff + NFC_EP_OOB_REC_PAYLOAD_PREFIX_LEN);
        ad_data_len = *p_len - NFC_EP_OOB_REC_PAYLOAD_PREFIX_LEN;
        if ( *p_len - NFC_EP_OOB_REC_PAYLOAD_PREFIX_LEN > UINT16_MAX )
        {
            ad_data_len = UINT16_MAX;
        }
    }

    /* Encode AD structures into NFC record payload */
    err_code = nfc_ble_oob_adv_data_encode(p_ble_advdata, p_ad_data, &ad_data_len);
    if (NRF_SUCCESS != err_code)
    {
        return err_code;
    }

    /* Now as the final payload length is known OOB payload length field, and Bluetooth device
     * address can be encoded */
    payload_len  = ad_data_len + NFC_EP_OOB_REC_PAYLOAD_PREFIX_LEN;
    if (p_buff != NULL)
    {
        p_buff      += uint16_encode(payload_len, p_buff);
        err_code     = nfc_ep_oob_bluetooth_device_address_encode(p_buff, p_ad_data - p_buff);
        if (NRF_SUCCESS != err_code)
        {
            return err_code;
        }
    }

    /* Update total payload length */
    *p_len = payload_len;

    return err_code;
}

#endif // NRF_MODULE_ENABLED(NFC_EP_OOB_REC)
