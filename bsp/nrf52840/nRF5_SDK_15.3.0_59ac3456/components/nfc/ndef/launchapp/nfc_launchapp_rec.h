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
#ifndef NFC_LAUNCHAPP_REC_H__
#define NFC_LAUNCHAPP_REC_H__

/**@file
 *
 * @defgroup nfc_launchapp_rec Launch app records
 * @{
 * @ingroup  nfc_launchapp_msg
 *
 * @brief    Generation of NFC NDEF record descriptions that launch apps.
 *
 */

#include <stdint.h>
#include "nfc_ndef_record.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Size of the type field of the Android Application Record, defined in the file
 * @c nfc_launchapp_rec.c. It is used in the @ref NFC_NDEF_ANDROID_LAUNCHAPP_RECORD_DESC macro.
 */
#define NFC_ANDROID_REC_TYPE_LENGTH 15

/**
 * @brief Size of the type field of the Windows LaunchApp Record, defined in the file
 * @c nfc_launchapp_rec.c. It is used in the @ref NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC_DEF macro.
 */
#define NFC_WINDOWS_REC_TYPE_LENGTH 21

/**
 * @brief Size of the platform type, which is used to encode payload field of the Windows LaunchApp
 * Record, defined in the file @c nfc_launchapp_rec.c. It is used in the
 * @ref NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC_DEF macro.
 */
#define NFC_WINDOWS_PLAT_TYPE_LENGTH 12

/**
 * @brief Type of description of payload of Windows LaunchApp record.
 */
typedef struct
{
    const uint8_t * platform;
    uint8_t         platform_length;
    const uint8_t * app_id;
    uint8_t         app_id_length;
} win_launchapp_payload_desc_t;

/**
 * @brief External reference to the type field of the NFC NDEF Android Application Record, defined in the
 * file @c nfc_launchapp_rec.c. It is used in the @ref NFC_NDEF_ANDROID_LAUNCHAPP_RECORD_DESC_DEF macro.
 */
extern const uint8_t ndef_android_launchapp_rec_type[NFC_ANDROID_REC_TYPE_LENGTH];

/**
 * @brief External reference to the type field of the NFC NDEF Windows LaunchApp record, defined in the
 * file @c nfc_launchapp_rec.c. It is used in the @ref NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC_DEF macro.
 */
extern const uint8_t ndef_windows_launchapp_rec_type[NFC_WINDOWS_REC_TYPE_LENGTH];

/**
 * @brief External reference to the platform type, which is used to encode payload field of the NFC NDEF
 * Windows LaunchApp record. This constant is defined in the file @c nfc_launchapp_rec.c and is used in
 * the macro @ref NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC_DEF.
 */
extern const uint8_t ndef_windows_launchapp_plat_type[NFC_WINDOWS_PLAT_TYPE_LENGTH];

/**
 * @brief Function for constructing the payload for a Windows LaunchApp record.
 *
 * This function encodes the payload according to the LaunchApp record definition. It implements an API
 * compatible with p_payload_constructor_t.
 *
 * @param[in] p_input    Pointer to the description of the payload.
 * @param[out] p_buff    Pointer to payload destination. If NULL, function will
 *                       calculate the expected size of the LaunchApp record payload.
 *
 * @param[in,out] p_len  Size of available memory to write as input. Size of generated
 *                       payload as output.
 *
 * @retval NRF_SUCCESS   Always success.
 */
ret_code_t nfc_win_launchapp_payload_constructor(win_launchapp_payload_desc_t * p_input,
                                                 uint8_t                      * p_buff,
                                                 uint32_t                     * p_len);

/** @brief Macro for generating a description of an NFC NDEF Android Application Record (AAR).
 *
 * This macro declares and initializes an instance of an NFC NDEF record description
 * of an Android Application Record (AAR).
 *
 * @note The record descriptor is declared as automatic variable, which implies that
 *       the NDEF message encoding (see @ref nfc_launchapp_msg_encode) must be done
 *       in the same variable scope.
 *
 * @param[in]  NAME                 Name for accessing record descriptor.
 * @param[in]  P_PACKAGE_NAME       Pointer to the Android package name string.
 * @param[in]  PACKAGE_NAME_LENGTH  Length of the Android package name.
 */
#define NFC_NDEF_ANDROID_LAUNCHAPP_RECORD_DESC_DEF(NAME,                  \
                                                   P_PACKAGE_NAME,        \
                                                   PACKAGE_NAME_LENGTH)   \
    NFC_NDEF_RECORD_BIN_DATA_DEF(NAME,                                    \
                                 TNF_EXTERNAL_TYPE,                       \
                                 NULL,                                    \
                                 0,                                       \
                                 ndef_android_launchapp_rec_type,         \
                                 sizeof(ndef_android_launchapp_rec_type), \
                                 (P_PACKAGE_NAME),                        \
                                 (PACKAGE_NAME_LENGTH))

/**
 * @brief Macro for accessing the NFC NDEF Android Application Record descriptor
 * instance that was created with @ref NFC_NDEF_ANDROID_LAUNCHAPP_RECORD_DESC_DEF.
 */
#define NFC_NDEF_ANDROID_LAUNCHAPP_RECORD_DESC(NAME) NFC_NDEF_RECORD_BIN_DATA(NAME)

/** @brief Macro for generating a description of an NFC NDEF Windows LaunchApp record.
 *
 * This macro declares and initializes an instance of an NFC NDEF record description
 * of a Windows LaunchApp record.
 *
 * @note The record descriptor is declared as automatic variable, which implies that
 *       the NDEF message encoding (see @ref nfc_launchapp_msg_encode) must be done
 *       in the same variable scope.
 *
 * @param[in]  NAME                 Name for accessing record descriptor.
 * @param[in]  P_WIN_APP_ID         Pointer to the Windows application ID string (GUID).
 * @param[in]  WIN_APP_ID_LENGTH    Length of the Windows application ID.
 *
 * @return Pointer to the description of the record.
 */
#define NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC_DEF(NAME,                          \
                                                   P_WIN_APP_ID,                  \
                                                   WIN_APP_ID_LENGTH)             \
    win_launchapp_payload_desc_t NAME##_ndef_win_launchapp_rec_payload_desc =     \
    {                                                                             \
        .platform        = ndef_windows_launchapp_plat_type,                      \
        .platform_length = sizeof(ndef_windows_launchapp_plat_type),              \
        .app_id          = (P_WIN_APP_ID),                                        \
        .app_id_length   = WIN_APP_ID_LENGTH                                      \
    };                                                                            \
    NFC_NDEF_GENERIC_RECORD_DESC_DEF(NAME,                                        \
                                     TNF_ABSOLUTE_URI,                            \
                                     NULL,                                        \
                                     0,                                           \
                                     ndef_windows_launchapp_rec_type,             \
                                     sizeof(ndef_windows_launchapp_rec_type),     \
                                     nfc_win_launchapp_payload_constructor,       \
                                     &NAME##_ndef_win_launchapp_rec_payload_desc) \

/**
 * @brief Macro for accessing the NFC NDEF Windows LaunchApp Record descriptor
 * instance that was created with @ref NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC_DEF.
 */
#define NFC_NDEF_WINDOWS_LAUNCHAPP_RECORD_DESC(NAME) NFC_NDEF_GENERIC_RECORD_DESC(NAME)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_LAUNCHAPP_REC
