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
#if NRF_MODULE_ENABLED(NFC_NDEF_URI_MSG)

#include <string.h>
#include "nfc_uri_msg.h"
#include "sdk_macros.h"

ret_code_t nfc_uri_msg_encode( nfc_uri_id_t          uri_id_code,
                               uint8_t const * const p_uri_data,
                               uint8_t               uri_data_len,
                               uint8_t       *       p_buf,
                               uint32_t      *       p_len)
{
    ret_code_t err_code;

    /* Create NFC NDEF message description with URI record */
    NFC_NDEF_MSG_DEF(nfc_uri_msg, 1);
    NFC_NDEF_URI_RECORD_DESC_DEF(nfc_uri_rec, uri_id_code, p_uri_data, uri_data_len);

    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_uri_msg),
                                       &NFC_NDEF_URI_RECORD_DESC(nfc_uri_rec));
    VERIFY_SUCCESS(err_code);
    VERIFY_PARAM_NOT_NULL(p_uri_data);

    /* Encode whole message into buffer */
    err_code = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_uri_msg),
                                   p_buf,
                                   p_len);

    return err_code;
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_URI_MSG)
