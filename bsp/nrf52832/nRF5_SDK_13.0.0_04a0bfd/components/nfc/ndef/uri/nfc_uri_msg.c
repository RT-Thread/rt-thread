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
#include "nfc_uri_msg.h"

/** @brief Function for generating a description of an NFC NDEF URI message.
 *
 * This function declares and initializes a static instance of an NFC NDEF message description
 * and NFC NDEF records descriptions.
 *
 * @param[in]  uri_id_code          URI identifier code that defines the protocol field of the URI.
 * @param[in]  p_uri_data           Pointer to the URI string.
 *                                  This string should not contain the protocol field if the protocol
 *                                  was specified in @p uri_id_code
 * @param[in]  uri_data_len         Length of the URI string.
 * @param[out] pp_uri_msg_desc      Pointer to pointer to the NDEF message description.
 *
 * @retval NRF_SUCCESS              If the description was successfully created.
 * @retval NRF_ERROR_INVALID_PARAM  If the URI string was invalid (equal to NULL).
 */
static ret_code_t nfc_uri_msg_declare( nfc_uri_id_t           uri_id_code,
                                       uint8_t const *  const p_uri_data,
                                       uint8_t                uri_data_len,
                                       nfc_ndef_msg_desc_t ** pp_uri_msg_desc)
{
    ret_code_t               err_code;
    nfc_ndef_record_desc_t * p_uri_rec;

    /* Create NFC NDEF message description, capacity - 1 record */
    NFC_NDEF_MSG_DEF(nfc_uri_msg, 1);

    /* The message description is static, therefore */
    /* you must clear the message (needed for supporting multiple calls) */
    nfc_ndef_msg_clear(&NFC_NDEF_MSG(nfc_uri_msg));

    if (p_uri_data != NULL)
    {
        /* Create NFC NDEF URI Record description */
        p_uri_rec = nfc_uri_rec_declare(uri_id_code,
                                        p_uri_data,
                                        uri_data_len);

        /* Add URI record as lone record to message */
        err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_uri_msg), p_uri_rec);

        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    *pp_uri_msg_desc = &NFC_NDEF_MSG(nfc_uri_msg);

    return NRF_SUCCESS;
}

ret_code_t nfc_uri_msg_encode( nfc_uri_id_t           uri_id_code,
                               uint8_t const *  const p_uri_data,
                               uint8_t                uri_data_len,
                               uint8_t       *        p_buf,
                               uint32_t      *        p_len)
{
    ret_code_t err_code;
    nfc_ndef_msg_desc_t * p_uri_msg_desc;

    /* Create NFC NDEF message description with URI record */
    err_code = nfc_uri_msg_declare( uri_id_code,
                                    p_uri_data,
                                    uri_data_len,
                                    &p_uri_msg_desc);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    /* Encode whole message into buffer */
    err_code = nfc_ndef_msg_encode(p_uri_msg_desc,
                                   p_buf,
                                   p_len);

    return err_code;
}
