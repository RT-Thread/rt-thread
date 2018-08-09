/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NFC_NDEF_RECORD_PARSER)

#include <stdint.h>
#include <stdbool.h>
#include "nfc_ndef_record_parser.h"
#include "app_util.h"
#include "nordic_common.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME nfc_ndef_parser
#if NFC_NDEF_RECORD_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_NDEF_RECORD_PARSER_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_NDEF_RECORD_PARSER_INFO_COLOR
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#else // NFC_NDEF_RECORD_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#include "nrf_log.h"
#endif // NFC_NDEF_RECORD_PARSER_LOG_ENABLED

/* Sum of sizes of fields: TNF-flags, Type Length, Payload Length in short NDEF record. */
#define NDEF_RECORD_BASE_LONG_SHORT (2 + NDEF_RECORD_PAYLOAD_LEN_SHORT_SIZE)


ret_code_t ndef_record_parser(nfc_ndef_bin_payload_desc_t * p_bin_pay_desc,
                              nfc_ndef_record_desc_t      * p_rec_desc,
                              nfc_ndef_record_location_t  * p_record_location,
                              uint8_t const               * p_nfc_data,
                              uint32_t                    * p_nfc_data_len)
{
    uint32_t expected_rec_size = NDEF_RECORD_BASE_LONG_SHORT;

    if (expected_rec_size > *p_nfc_data_len)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_rec_desc->tnf = (nfc_ndef_record_tnf_t) ((*p_nfc_data) & NDEF_RECORD_TNF_MASK);

    /* An NDEF parser that receives an NDEF record with an unknown or unsupported TNF field value
       SHOULD treat it as Unknown. See NFCForum-TS-NDEF_1.0 */
    if (p_rec_desc->tnf == TNF_RESERVED)
    {
        p_rec_desc->tnf = TNF_UNKNOWN_TYPE;
    }

    *p_record_location = (nfc_ndef_record_location_t) ((*p_nfc_data) & NDEF_RECORD_LOCATION_MASK);

    uint8_t flags = *(p_nfc_data++);

    p_rec_desc->type_length = *(p_nfc_data++);

    uint32_t payload_lenght;

    if (flags & NDEF_RECORD_SR_MASK)
    {
        payload_lenght = *(p_nfc_data++);
    }
    else
    {
        expected_rec_size +=
            NDEF_RECORD_PAYLOAD_LEN_LONG_SIZE - NDEF_RECORD_PAYLOAD_LEN_SHORT_SIZE;

        if (expected_rec_size > *p_nfc_data_len)
        {
            return NRF_ERROR_INVALID_LENGTH;
        }

        payload_lenght = uint32_big_decode(p_nfc_data);
        p_nfc_data    += NDEF_RECORD_PAYLOAD_LEN_LONG_SIZE;
    }

    if (flags & NDEF_RECORD_IL_MASK)
    {
        expected_rec_size += NDEF_RECORD_ID_LEN_SIZE;

        if (expected_rec_size > *p_nfc_data_len)
        {
            return NRF_ERROR_INVALID_LENGTH;
        }

        p_rec_desc->id_length = *(p_nfc_data++);
    }
    else
    {
        p_rec_desc->id_length = 0;
        p_rec_desc->p_id      = NULL;
    }

    expected_rec_size += p_rec_desc->type_length + p_rec_desc->id_length + payload_lenght;

    if (expected_rec_size > *p_nfc_data_len)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    if (p_rec_desc->type_length > 0)
    {
        p_rec_desc->p_type = p_nfc_data;

        p_nfc_data += p_rec_desc->type_length;
    }
    else
    {
        p_rec_desc->p_type = NULL;
    }

    if (p_rec_desc->id_length > 0)
    {
        p_rec_desc->p_id = p_nfc_data;

        p_nfc_data += p_rec_desc->id_length;
    }

    if (payload_lenght == 0)
    {
        p_bin_pay_desc->p_payload = NULL;
    }
    else
    {
        p_bin_pay_desc->p_payload = p_nfc_data;
    }

    p_bin_pay_desc->payload_length = payload_lenght;

    p_rec_desc->p_payload_descriptor = p_bin_pay_desc;
    p_rec_desc->payload_constructor  = (p_payload_constructor_t) nfc_ndef_bin_payload_memcopy;

    *p_nfc_data_len = expected_rec_size;

    return NRF_SUCCESS;
}

char const * const tnf_strings[] =
{
    "Empty",
    "NFC Forum well-known type",
    "Media-type (RFC 2046)",
    "Absolute URI (RFC 3986)",
    "NFC Forum external type (NFC RTD)",
    "Unknown",
    "Unchanged",
    "Reserved"
};

void ndef_record_printout(uint32_t num, nfc_ndef_record_desc_t * const p_rec_desc)
{
    NRF_LOG_INFO("NDEF record %d content:", num);
    NRF_LOG_INFO("TNF: %s",(uint32_t)tnf_strings[p_rec_desc->tnf]);

    if (p_rec_desc->p_id != NULL)
    {
        NRF_LOG_INFO("ID:");
        NRF_LOG_HEXDUMP_INFO((uint8_t *)p_rec_desc->p_id, p_rec_desc->id_length);
    }

    if (p_rec_desc->p_type != NULL)
    {
        NRF_LOG_INFO("type:");
        NRF_LOG_HEXDUMP_INFO((uint8_t *)p_rec_desc->p_type, p_rec_desc->type_length);
    }

    if (p_rec_desc->payload_constructor == (p_payload_constructor_t) nfc_ndef_bin_payload_memcopy)
    {
        nfc_ndef_bin_payload_desc_t * p_bin_pay_desc = p_rec_desc->p_payload_descriptor;

        if (p_bin_pay_desc->p_payload != NULL)
        {
            NRF_LOG_INFO("Payload length: %d bytes", p_bin_pay_desc->payload_length);
            NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_bin_pay_desc->p_payload, p_bin_pay_desc->payload_length);
        }
        else
        {
            NRF_LOG_INFO("No payload");
        }
    }
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_RECORD_PARSER)
