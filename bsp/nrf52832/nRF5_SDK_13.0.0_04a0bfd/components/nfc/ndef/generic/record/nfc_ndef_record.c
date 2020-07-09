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
#include <string.h>
#include "nfc_ndef_record.h"
#include "app_util.h"
#include "nrf.h"


/* Sum of sizes of fields: TNF-flags, Type Length, Payload Length in long NDEF record. */
#define NDEF_RECORD_BASE_LONG_SIZE          (2 + NDEF_RECORD_PAYLOAD_LEN_LONG_SIZE)

__STATIC_INLINE uint32_t record_header_size_calc(nfc_ndef_record_desc_t const * p_ndef_record_desc)
{
    uint32_t len = NDEF_RECORD_BASE_LONG_SIZE;

    len += p_ndef_record_desc->id_length + p_ndef_record_desc->type_length;

    if (p_ndef_record_desc->id_length > 0)
    {
        len++;
    }

    return len;
}


ret_code_t nfc_ndef_record_encode(nfc_ndef_record_desc_t const * p_ndef_record_desc,
                                  nfc_ndef_record_location_t     record_location,
                                  uint8_t                      * p_record_buffer,
                                  uint32_t                     * p_record_len)
{
    uint8_t * p_flags;              // use as pointer to TNF + flags field
    uint8_t * p_payload_len = NULL; // use as pointer to payload length field
    uint32_t  record_payload_len;

    if (p_ndef_record_desc == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // count record length without payload
    uint32_t record_header_len = record_header_size_calc(p_ndef_record_desc);
    uint32_t err_code          = NRF_SUCCESS;

    if (p_record_buffer != NULL)
    {
        /* verify location range */
        if ((record_location & (~NDEF_RECORD_LOCATION_MASK)) != 0x00)
        {
            return NRF_ERROR_INVALID_PARAM;
        }

        /* verify if there is enough available memory */
        if (record_header_len > *p_record_len)
        {
            return NRF_ERROR_NO_MEM;
        }

        p_flags = p_record_buffer;
        p_record_buffer++;

        // set location bits and clear other bits in 1st byte.
        *p_flags = record_location;

        *p_flags |= p_ndef_record_desc->tnf;

        /* TYPE LENGTH */
        *(p_record_buffer++) = p_ndef_record_desc->type_length;

        // use always long record and remember payload len field memory offset.
        p_payload_len    = p_record_buffer;
        p_record_buffer += NDEF_RECORD_PAYLOAD_LEN_LONG_SIZE;

        /* ID LENGTH - option */
        if (p_ndef_record_desc->id_length > 0)
        {
            *(p_record_buffer++) = p_ndef_record_desc->id_length;

            /* IL flag */
            *p_flags |= NDEF_RECORD_IL_MASK;
        }

        /* TYPE */
        memcpy(p_record_buffer, p_ndef_record_desc->p_type, p_ndef_record_desc->type_length);
        p_record_buffer += p_ndef_record_desc->type_length;

        /* ID */
        if (p_ndef_record_desc->id_length > 0)
        {
            memcpy(p_record_buffer, p_ndef_record_desc->p_id, p_ndef_record_desc->id_length);
            p_record_buffer += p_ndef_record_desc->id_length;
        }

        // count how much memory is left in record buffer for payload field.
        record_payload_len = (*p_record_len - record_header_len);
    }

    /* PAYLOAD */
    if (p_ndef_record_desc->payload_constructor != NULL)
    {
        err_code =
            p_ndef_record_desc->payload_constructor(p_ndef_record_desc->p_payload_descriptor,
                                                    p_record_buffer,
                                                    &record_payload_len);

        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    else
    {
        return NRF_ERROR_NULL;
    }

    if (p_record_buffer != NULL)
    {
        /* PAYLOAD LENGTH */
        (void) uint32_big_encode(record_payload_len, p_payload_len);
    }

    *p_record_len = record_header_len + record_payload_len;

    return NRF_SUCCESS;
}


ret_code_t nfc_ndef_bin_payload_memcopy(nfc_ndef_bin_payload_desc_t * p_payload_descriptor,
                                        uint8_t                     * p_buffer,
                                        uint32_t                    * p_len)
{

    if (p_buffer != NULL)
    {
        if ( *p_len < p_payload_descriptor->payload_length)
        {
            return NRF_ERROR_NO_MEM;
        }

        memcpy(p_buffer,
               p_payload_descriptor->p_payload,
               p_payload_descriptor->payload_length);
    }

    *p_len = p_payload_descriptor->payload_length;

    return NRF_SUCCESS;
}


