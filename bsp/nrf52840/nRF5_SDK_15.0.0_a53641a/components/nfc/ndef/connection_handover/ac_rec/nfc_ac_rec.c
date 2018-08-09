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
#if NRF_MODULE_ENABLED(NFC_AC_REC)

#include "nfc_ac_rec.h"
#include <string.h>
#include "nrf_error.h"
#include "nrf.h"

#define AC_REC_CPS_BYTE_SIZE            1 ///< Size of the field with CPS data.
#define AC_REC_DATA_REF_LEN_SIZE        1 ///< Size of the Data Reference Length field.
#define AC_REC_AUX_DATA_REF_COUNT_SIZE  1 ///< Size of the Data Reference Length field.

const uint8_t nfc_ac_rec_type_field[2] = {'a', 'c'}; ///< Alternative Carrier Record type.

/**
 * @brief Function for calculating the payload length of the NFC NDEF Alternative Carrier record.
 */
static uint32_t nfc_ac_rec_payload_size_get(nfc_ac_rec_payload_desc_t const * p_ac_rec_payload_desc)
{
    int32_t i = 0;
    // Initialize with size of byte with CPS.
    uint32_t payload_size = AC_REC_CPS_BYTE_SIZE;

    // Add Carrier Data Reference size.
    payload_size +=  p_ac_rec_payload_desc->carrier_data_ref.length + AC_REC_DATA_REF_LEN_SIZE;

    // Add Auxiliary Data Reference Count size.
    payload_size += AC_REC_AUX_DATA_REF_COUNT_SIZE;

    for (i = 0; i < p_ac_rec_payload_desc->aux_data_ref_count; i++)
    {
        // Add Auxiliary Data Reference size.
        payload_size += p_ac_rec_payload_desc->p_aux_data_ref[i].length + AC_REC_DATA_REF_LEN_SIZE;
    }

    return payload_size;
}


ret_code_t nfc_ac_rec_payload_constructor(nfc_ac_rec_payload_desc_t * p_nfc_rec_ac_payload_desc,
                                          uint8_t                   * p_buff,
                                          uint32_t                  * p_len)
{
    int32_t  i = 0;
    uint32_t payload_size = nfc_ac_rec_payload_size_get(p_nfc_rec_ac_payload_desc);

    if (p_buff != NULL)
    {
        // Not enough space in the buffer, return an error.
        if (payload_size > *p_len)
        {
            return NRF_ERROR_NO_MEM;
        }

        // Invalid CPS value.
        if ( p_nfc_rec_ac_payload_desc->cps & ~NFC_AC_CPS_MASK )
        {
            return NRF_ERROR_INVALID_PARAM;
        }

        // Copy CPS.
        *p_buff = p_nfc_rec_ac_payload_desc->cps;
        p_buff += AC_REC_CPS_BYTE_SIZE;

        // Copy Carrier Data Reference.
        *p_buff = p_nfc_rec_ac_payload_desc->carrier_data_ref.length;
        p_buff += AC_REC_DATA_REF_LEN_SIZE;

        memcpy( p_buff,
                p_nfc_rec_ac_payload_desc->carrier_data_ref.p_data,
                p_nfc_rec_ac_payload_desc->carrier_data_ref.length );
        p_buff += p_nfc_rec_ac_payload_desc->carrier_data_ref.length;

        // Copy Auxiliary Data Reference.
        *p_buff = p_nfc_rec_ac_payload_desc->aux_data_ref_count;
        p_buff += AC_REC_AUX_DATA_REF_COUNT_SIZE;

        for (i = 0; i < p_nfc_rec_ac_payload_desc->aux_data_ref_count; i++)
        {
            *p_buff = p_nfc_rec_ac_payload_desc->p_aux_data_ref[i].length;
            p_buff += AC_REC_DATA_REF_LEN_SIZE;

            memcpy( p_buff,
                    p_nfc_rec_ac_payload_desc->p_aux_data_ref[i].p_data,
                    p_nfc_rec_ac_payload_desc->p_aux_data_ref[i].length );
            p_buff += p_nfc_rec_ac_payload_desc->p_aux_data_ref[i].length;
        }
    }

    // Assign payload size to the return buffer.
    *p_len = payload_size;

    return NRF_SUCCESS;
}


void nfc_ac_rec_auxiliary_data_ref_clear(nfc_ndef_record_desc_t * p_ac_rec)
{
    nfc_ac_rec_payload_desc_t * p_ac_rec_payload =
            (nfc_ac_rec_payload_desc_t*)p_ac_rec->p_payload_descriptor;

    p_ac_rec_payload->aux_data_ref_count = 0;
}


ret_code_t nfc_ac_rec_auxiliary_data_ref_add(nfc_ndef_record_desc_t * p_ac_rec,
                                             uint8_t                * p_aux_data,
                                             uint8_t                  aux_length)
{
    nfc_ac_rec_payload_desc_t * p_ac_rec_payload =
            (nfc_ac_rec_payload_desc_t *)p_ac_rec->p_payload_descriptor;

    if (p_ac_rec_payload->aux_data_ref_count >= p_ac_rec_payload->max_aux_data_ref)
    {
        return NRF_ERROR_NO_MEM;
    }

    p_ac_rec_payload->p_aux_data_ref[p_ac_rec_payload->aux_data_ref_count].p_data = p_aux_data;
    p_ac_rec_payload->p_aux_data_ref[p_ac_rec_payload->aux_data_ref_count].length = aux_length;
    p_ac_rec_payload->aux_data_ref_count++;

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NFC_AC_REC)
