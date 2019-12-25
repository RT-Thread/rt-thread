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
#if NRF_MODULE_ENABLED(NFC_NDEF_LAUNCHAPP_MSG)

#include <stdint.h>
#include <string.h>
#include "nfc_launchapp_rec.h"
#include "nfc_launchapp_msg.h"
#include "nrf_error.h"
#include "sdk_macros.h"

ret_code_t nfc_launchapp_msg_encode(uint8_t const * p_android_package_name,
                                    uint8_t         android_package_name_length,
                                    uint8_t const * p_win_app_id,
                                    uint8_t         win_app_id_length,
                                    uint8_t       * p_buf,
                                    uint32_t      * p_len)
{
    ret_code_t err_code;

    /* Create NFC NDEF message description, capacity - 2 records */
    NFC_NDEF_MSG_DEF(nfc_launchapp_msg, 2);

    /* Create NFC NDEF Windows Phone LaunchApp Record description */
    NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC_DEF(nfc_win_launchapp_rec,
                                               p_win_app_id,
                                               win_app_id_length);

    /* Create NFC NDEF Android Application Record description */
    NFC_NDEF_ANDROID_LAUNCHAPP_RECORD_DESC_DEF(nfc_and_launchapp_rec,
                                               p_android_package_name,
                                               android_package_name_length);

    if (p_win_app_id != NULL)
    {
        /* Add Windows Phone LaunchApp Record as first record to message */
        err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_launchapp_msg),
                                           &NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC(nfc_win_launchapp_rec));
        VERIFY_SUCCESS(err_code);
    }
    if (p_android_package_name != NULL)
    {
        /* Add Android Application Record as second record to message */
        err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_launchapp_msg),
                                           &NFC_NDEF_ANDROID_LAUNCHAPP_RECORD_DESC(nfc_and_launchapp_rec));
        VERIFY_SUCCESS(err_code);
    }
    VERIFY_FALSE(NFC_NDEF_MSG(nfc_launchapp_msg).record_count == 0,
                              NRF_ERROR_INVALID_PARAM);

    /* Encode whole message into buffer */
    err_code = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_launchapp_msg),
                                   p_buf,
                                   p_len);

    return err_code;
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_LAUNCHAPP_MSG)
