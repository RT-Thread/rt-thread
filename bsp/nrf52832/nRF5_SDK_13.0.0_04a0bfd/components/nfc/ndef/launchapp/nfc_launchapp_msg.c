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
#include <stdint.h>
#include <string.h>
#include "nfc_launchapp_rec.h"
#include "nfc_launchapp_msg.h"
#include "nrf_error.h"

/** @brief Function for generating a description of an NFC NDEF launch application message.
 *
 * This function declares and initializes a static instance of an NFC NDEF message description
 * and the NFC NDEF record descriptions that are referenced by this message description.
 *
 * @param[in]  p_android_package_name       Pointer to the Android package name string.
 *                                          If NULL, the Android Application Record will be skipped.
 * @param[in]  android_package_name_length  Length of the Android package name.
 * @param[in]  p_win_app_id                 Pointer to the Windows application ID string (GUID).
 *                                          If NULL, the Windows LaunchApp Record will be skipped.
 * @param[in]  win_app_id_length            Length of the Windows application ID.
 * @param[out] pp_launchapp_msg_desc        Pointer to pointer to the NDEF message description.
 *
 * @retval NRF_SUCCESS              If the description was successfully created.
 * @retval NRF_ERROR_INVALID_PARAM  If both p_android_package_name and windows_application_id were
 *                                  invalid (equal to NULL).
 */
__STATIC_INLINE ret_code_t nfc_launchapp_msg_declare(uint8_t const        * p_android_package_name,
                                     uint8_t                android_package_name_length,
                                     uint8_t const        * p_win_app_id,
                                     uint8_t                win_app_id_length,
                                     nfc_ndef_msg_desc_t ** pp_launchapp_msg_desc)
{

    uint32_t err_code;

    nfc_ndef_record_desc_t * p_win_rec, * p_android_rec;

    /* Create NFC NDEF message description, capacity - 2 records */
    NFC_NDEF_MSG_DEF(nfc_launchapp_msg, 2);

    /* The message description is static, therefore you must */
    /* clear the message (needed for supporting multiple calls).  */
    nfc_ndef_msg_clear(&NFC_NDEF_MSG(nfc_launchapp_msg));

    if (p_win_app_id != NULL)
    {
        /* Create NFC NDEF Windows Phone LaunchApp Record description */
        p_win_rec = nfc_windows_launchapp_rec_declare(p_win_app_id,
                                                      win_app_id_length);

        /* Add Windows LaunchApp record as first record to message */
        err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_launchapp_msg), p_win_rec);

        if (err_code != NRF_SUCCESS)
            return err_code;
    }

    if (p_android_package_name != NULL)
    {
        /* Create NFC NDEF Android Application Record description */
        p_android_rec = nfc_android_application_rec_declare(p_android_package_name,
                                                            android_package_name_length);

        /* Add Android App Record as second record to message */
        err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_launchapp_msg), p_android_rec);

        if (err_code != NRF_SUCCESS)
            return err_code;
    }

    if (NFC_NDEF_MSG(nfc_launchapp_msg).record_count == 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    *pp_launchapp_msg_desc = &NFC_NDEF_MSG(nfc_launchapp_msg);

    return NRF_SUCCESS;
}


ret_code_t nfc_launchapp_msg_encode(uint8_t const * p_android_package_name,
                                    uint8_t         android_package_name_length,
                                    uint8_t const * p_win_app_id,
                                    uint8_t         win_app_id_length,
                                    uint8_t       * p_buf,
                                    uint32_t      * p_len)
{
    nfc_ndef_msg_desc_t * p_launchapp_msg_desc;
    ret_code_t            err_code;

    err_code = nfc_launchapp_msg_declare(p_android_package_name,
                                         android_package_name_length,
                                         p_win_app_id,
                                         win_app_id_length,
                                         &p_launchapp_msg_desc);

    if (err_code != NRF_SUCCESS)
        return err_code;

    /* Encode whole message into buffer */
    err_code = nfc_ndef_msg_encode(p_launchapp_msg_desc,
                                   p_buf,
                                   p_len);

    return err_code;
}


