/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#include "nfc_le_oob_rec_parser.h"
#include "sdk_errors.h"

/**
 * @brief Function for parsing LE OOB record payload.
 *
 * This function parses LE OOB record payload and extracts BLE OOB Advertising data structure.
 *
 * @param[in]     p_buff                       Pointer to the record payload.
 * @param[in]     p_len                        Pointer to the record payload length.
 * @param[in,out] p_nfc_ble_oob_pairing_data   Pointer to the structure that will be used to hold
 *                                             parsed data.
 *
 * @retval NRF_SUCCESS              If the function completed successfully.
 * @retval Other                    An error code that might have been returned by
 *                                  @ref nfc_ble_oob_advdata_parse function.
 */
static ret_code_t nfc_le_oob_payload_parse(uint8_t                    * p_buff,
                                           uint32_t                   * const p_len,
                                           nfc_ble_oob_pairing_data_t * const p_nfc_ble_oob_pairing_data)
{
    ret_code_t err_code = nfc_ble_oob_advdata_parse(p_buff,
                                                    *p_len,
                                                    p_nfc_ble_oob_pairing_data);
    return err_code;
}

ret_code_t nfc_le_oob_rec_parse(nfc_ndef_record_desc_t     const * const p_rec_desc,
                                nfc_ble_oob_pairing_data_t       * const p_nfc_ble_oob_pairing_data)
{
    ret_code_t err_code;

    if (p_rec_desc->tnf != TNF_MEDIA_TYPE)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    if (p_rec_desc->type_length != sizeof(le_oob_rec_type_field))
    {
        return NRF_ERROR_INVALID_DATA;
    }

    if (memcmp(p_rec_desc->p_type, le_oob_rec_type_field, sizeof(le_oob_rec_type_field)) != 0)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    if (p_rec_desc->payload_constructor != (p_payload_constructor_t) nfc_ndef_bin_payload_memcopy)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    uint8_t const * p_payload = ((nfc_ndef_bin_payload_desc_t*)(p_rec_desc->p_payload_descriptor))->p_payload;
    uint32_t payload_lenght   = ((nfc_ndef_bin_payload_desc_t*)(p_rec_desc->p_payload_descriptor))->payload_length;

    err_code = nfc_le_oob_payload_parse((uint8_t *) p_payload,
                                        &payload_lenght,
                                        p_nfc_ble_oob_pairing_data);

    return err_code;
}
