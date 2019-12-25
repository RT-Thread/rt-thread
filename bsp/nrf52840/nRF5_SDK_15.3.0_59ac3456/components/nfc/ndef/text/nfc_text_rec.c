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
#if NRF_MODULE_ENABLED(NFC_NDEF_TEXT_RECORD)

#include <string.h>
#include "nfc_text_rec.h"
#include "nrf_error.h"

#define TEXT_REC_STATUS_SIZE          1     ///< Size of the status.
#define TEXT_REC_STATUS_UTF_POS       7     ///< Position of a character encoding type.
#define TEXT_REC_RESERVED_POS         6     ///< Reserved position.

const uint8_t nfc_text_rec_type_field[] = {'T'};


/**
 * @brief Function for calculating payload size.
 */
__STATIC_INLINE uint32_t nfc_text_rec_payload_size_get(nfc_text_rec_payload_desc_t * p_nfc_rec_text_payload_desc)
{
    return (TEXT_REC_STATUS_SIZE
          + p_nfc_rec_text_payload_desc->lang_code_len
          + p_nfc_rec_text_payload_desc->data_len);
}

ret_code_t nfc_text_rec_payload_constructor(nfc_text_rec_payload_desc_t * p_nfc_rec_text_payload_desc,
                                            uint8_t                     * p_buff,
                                            uint32_t                    * p_len)
{
    if ((p_nfc_rec_text_payload_desc->lang_code_len == 0)
     || (p_nfc_rec_text_payload_desc->lang_code_len & (1 << TEXT_REC_RESERVED_POS))
     || (p_nfc_rec_text_payload_desc->lang_code_len & (1 << TEXT_REC_STATUS_UTF_POS))
     || (p_nfc_rec_text_payload_desc->p_lang_code   == NULL)
     || (p_nfc_rec_text_payload_desc->data_len      == 0)
     || (p_nfc_rec_text_payload_desc->p_data        == NULL)
     || (p_len                                      == NULL))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint32_t payload_size = nfc_text_rec_payload_size_get(p_nfc_rec_text_payload_desc);

    if (p_buff != NULL)
    {
        if (payload_size > *p_len)
        {
            return NRF_ERROR_NO_MEM;
        }

        *p_buff = (p_nfc_rec_text_payload_desc->lang_code_len
                + (p_nfc_rec_text_payload_desc->utf << TEXT_REC_STATUS_UTF_POS));
        p_buff += TEXT_REC_STATUS_SIZE;

        memcpy(p_buff,
            p_nfc_rec_text_payload_desc->p_lang_code,
            p_nfc_rec_text_payload_desc->lang_code_len);
        p_buff += p_nfc_rec_text_payload_desc->lang_code_len;

        memcpy(p_buff,
            p_nfc_rec_text_payload_desc->p_data,
            p_nfc_rec_text_payload_desc->data_len);
    }

    *p_len = payload_size;

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_TEXT_RECORD)
