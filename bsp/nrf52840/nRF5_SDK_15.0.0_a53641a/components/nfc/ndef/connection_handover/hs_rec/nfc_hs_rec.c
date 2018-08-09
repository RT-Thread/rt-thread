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
#if NRF_MODULE_ENABLED(NFC_HS_REC)

#include "nfc_hs_rec.h"
#include "nfc_ac_rec.h"
#include "nrf_error.h"

#define HS_REC_VERSION_SIZE     1

const uint8_t nfc_hs_rec_type_field[] = {'H', 's'}; ///< Handover Select record type.


ret_code_t nfc_hs_rec_payload_constructor(nfc_hs_rec_payload_desc_t * p_nfc_hs_rec_payload_desc,
                                          uint8_t                   * p_buff,
                                          uint32_t                  * p_len)
{
    ret_code_t err_code = NRF_SUCCESS;

    if (p_buff != NULL)
    {
        // There must be at least 1 free byte in buffer for version byte.
        if (*p_len < HS_REC_VERSION_SIZE)
        {
            return NRF_ERROR_NO_MEM;
        }

        // Major/minor version byte.
        *p_buff = ( (p_nfc_hs_rec_payload_desc->major_version << 4) & 0xF0) |
                  (  p_nfc_hs_rec_payload_desc->minor_version       & 0x0F);
        p_buff += HS_REC_VERSION_SIZE;

        // Decrement remaining buffer size.
        *p_len -= HS_REC_VERSION_SIZE;
    }

    // Encode local records encapsulated in a message.
    err_code = nfc_ndef_msg_encode(p_nfc_hs_rec_payload_desc->p_local_records, p_buff, p_len);
    if (err_code!= NRF_SUCCESS)
    {
        return err_code;
    }

    // Add version byte to the total record size.
    *p_len += HS_REC_VERSION_SIZE;

    return NRF_SUCCESS;
}


void nfc_hs_rec_local_record_clear(nfc_ndef_record_desc_t * p_hs_rec)
{
    nfc_hs_rec_payload_desc_t* p_hs_payload =
            (nfc_hs_rec_payload_desc_t*)p_hs_rec->p_payload_descriptor;

    nfc_ndef_msg_clear(p_hs_payload->p_local_records);
}


ret_code_t nfc_hs_rec_local_record_add(nfc_ndef_record_desc_t * p_hs_rec,
                                       nfc_ndef_record_desc_t * p_local_rec)
{
    nfc_hs_rec_payload_desc_t* p_hs_payload =
            (nfc_hs_rec_payload_desc_t*)p_hs_rec->p_payload_descriptor;

    return nfc_ndef_msg_record_add(p_hs_payload->p_local_records, p_local_rec);
}

#endif // NRF_MODULE_ENABLED(NFC_HS_REC)
