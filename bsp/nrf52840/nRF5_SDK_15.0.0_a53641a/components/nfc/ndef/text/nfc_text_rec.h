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
#ifndef NFC_TEXT_REC_H__
#define NFC_TEXT_REC_H__

/**@file
 *
 * @defgroup nfc_text_rec Text records
 * @{
 * @ingroup  nfc_ndef_messages
 *
 * @brief    Generation of NFC NDEF Text record descriptions.
 *
 */

#include "nfc_ndef_record.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Type of the Unicode Transformation Format.
 *
 * Values to specify the type of UTF for an NFC NDEF Text record.
 */
typedef enum
{
    UTF_8   = 0, ///< Unicode Transformation Format 8.
    UTF_16  = 1, ///< Unicode Transformation Format 16.
} nfc_text_rec_utf_type_t;

/**
 * @brief Text record payload descriptor.
 */
typedef struct
{
    nfc_text_rec_utf_type_t utf;    ///< Type of the Unicode Transformation Format.

    uint8_t const * p_lang_code;    ///< Pointer to the IANA language code.
    uint8_t         lang_code_len;  ///< Length of the IANA language code.

    uint8_t const * p_data;         ///< Pointer to the user text.
    uint32_t        data_len;       ///< Length of the user text.
} nfc_text_rec_payload_desc_t;

/**
 * @brief Constructor for an NFC NDEF Text record payload.
 *
 * @param[in]       p_nfc_rec_text_payload_desc Pointer to the Text record description.
 * @param[out]      p_buff                      Pointer to the payload destination. If NULL, function will
 *                                              calculate the expected size of the Text record payload.
 *
 * @param[in,out]   p_len                       Size of the available memory to write as input.
 *                                              Size of the generated record payload as output.
 */
ret_code_t nfc_text_rec_payload_constructor(nfc_text_rec_payload_desc_t * p_nfc_rec_text_payload_desc,
                                            uint8_t                     * p_buff,
                                            uint32_t                    * p_len);

/**
 * @brief External reference to the type field of the Text record, defined in the
 * file @c nfc_text_rec.c. It is used in the @ref NFC_NDEF_TEXT_RECORD_DESC_DEF macro.
 */
extern const uint8_t nfc_text_rec_type_field[];

/**
 * @brief Size of the type field of the Text record, defined in the
 * file @c nfc_text_rec.c. It is used in the @ref NFC_NDEF_TEXT_RECORD_DESC_DEF macro.
 */
#define NFC_TEXT_REC_TYPE_LENGTH 1

/**
 *@brief Macro for creating and initializing an NFC NDEF record descriptor for a Text record.
 *
 * This macro creates and initializes an instance of type @ref nfc_ndef_record_desc_t and
 * an instance of type @ref nfc_text_rec_payload_desc_t, which together constitute
 * an instance of a Text record.
 *
 * Use the macro @ref NFC_NDEF_TEXT_RECORD_DESC to access the NDEF Text record descriptor instance.
 *
 * @param[in] NAME              Name of the created record descriptor instance.
 * @param[in] UTF               Unicode Transformation Format.
 * @param[in] P_LANG_CODE       Pointer to the IANA language code.
 * @param[in] LANG_CODE_LEN     Length of the IANA language code.
 * @param[in] P_DATA            Pointer to the user text.
 * @param[in] DATA_LEN          Length of the user text.
 */
#define NFC_NDEF_TEXT_RECORD_DESC_DEF(NAME,                                 \
                                      UTF,                                  \
                                      P_LANG_CODE,                          \
                                      LANG_CODE_LEN,                        \
                                      P_DATA,                               \
                                      DATA_LEN)                             \
    nfc_text_rec_payload_desc_t NAME##_nfc_text_rec_payload_desc =          \
    {                                                                       \
        .utf            = UTF,                                              \
        .p_lang_code    = P_LANG_CODE,                                      \
        .lang_code_len  = LANG_CODE_LEN,                                    \
        .p_data         = P_DATA,                                           \
        .data_len       = DATA_LEN,                                         \
    };                                                                      \
    NFC_NDEF_GENERIC_RECORD_DESC_DEF(NAME,                                  \
                                     TNF_WELL_KNOWN,                        \
                                     0,                                     \
                                     0,                                     \
                                     nfc_text_rec_type_field,               \
                                     NFC_TEXT_REC_TYPE_LENGTH,              \
                                     nfc_text_rec_payload_constructor,      \
                                     &(NAME##_nfc_text_rec_payload_desc))

/**
 * @brief Macro for accessing the NFC NDEF Text record descriptor
 * instance that was created with @ref NFC_NDEF_TEXT_RECORD_DESC_DEF.
 */
#define NFC_NDEF_TEXT_RECORD_DESC(NAME) NFC_NDEF_GENERIC_RECORD_DESC(NAME)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_TEXT_REC_H__
