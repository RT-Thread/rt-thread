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
#ifndef NFC_LAUNCHAPP_REC_H__
#define NFC_LAUNCHAPP_REC_H__

/**@file
 *
 * @defgroup nfc_launch_app_rec Launch app records
 * @{
 * @ingroup  nfc_launch_app_msg
 *
 * @brief    Generation of NFC NDEF record descriptions that launch apps.
 *
 */

#include <stdint.h>
#include "nfc_ndef_record.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Function for generating a description of an NFC NDEF Android Application Record (AAR).
 *
 * This function declares and initializes a static instance of an NFC NDEF record description
 * of an Android Application Record (AAR).
 *
 * @note The record payload data (@p p_package_name) should be declared as
 *       static. If it is declared as automatic, the NDEF message encoding
 *       (see @ref nfc_ndef_msg_encode) must be done in the same variable
 *       scope.
 *
 * @param[in]  p_package_name       Pointer to the Android package name string.
 * @param[in]  package_name_length  Length of the Android package name.
 *
 * @return Pointer to the description of the record.
 */
nfc_ndef_record_desc_t * nfc_android_application_rec_declare(uint8_t const * p_package_name,
                                                             uint8_t         package_name_length);

/** @brief Function for generating a description of an NFC NDEF Windows LaunchApp record.
 *
 * This function declares and initializes a static instance of an NFC NDEF record description
 * of a Windows LaunchApp record.
 *
 * @note The record payload data (@p p_win_app_id) should be declared as
 *       static. If it is declared as automatic, the NDEF message encoding
 *       (see @ref nfc_ndef_msg_encode) must be done in the same variable
 *       scope.
 *
 * @param[in]  p_win_app_id         Pointer to the Windows application ID string (GUID).
 * @param[in]  win_app_id_length    Length of the Windows application ID.
 *
 * @return Pointer to the description of the record.
 */
nfc_ndef_record_desc_t * nfc_windows_launchapp_rec_declare(const uint8_t * p_win_app_id,
                                                           uint8_t         win_app_id_length);
/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_LAUNCHAPP_REC
