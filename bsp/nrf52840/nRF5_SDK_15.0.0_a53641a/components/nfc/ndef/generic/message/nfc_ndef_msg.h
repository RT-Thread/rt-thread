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
#ifndef NFC_NDEF_MSG_H__
#define NFC_NDEF_MSG_H__

#include "nfc_ndef_record.h"

#ifdef __cplusplus
extern "C" {
#endif
/**@file
 *
 * @defgroup nfc_ndef_msg Custom NDEF messages
 * @{
 * @ingroup  nfc_modules
 *
 * @brief    Generation of NFC NDEF messages for the NFC tag.
 *
 */

#define TYPE_4_TAG      4U                       ///< Type 4 Tag identifier.
#define NLEN_FIELD_SIZE 2U                       ///< Size of NLEN field, used to encode NDEF message for Type 4 Tag.

 /**
  * @brief NDEF message descriptor.
  */
 typedef struct {
     nfc_ndef_record_desc_t ** pp_record;        ///< Pointer to an array of pointers to NDEF record descriptors.
     uint32_t                  max_record_count; ///< Number of elements in the allocated pp_record array, which defines the maximum number of records within the NDEF message.
     uint32_t                  record_count;     ///< Number of records in the NDEF message.
 } nfc_ndef_msg_desc_t;

 /**
  * @brief  Function for encoding an NDEF message.
  *
  * This function encodes an NDEF message according to the provided message descriptor.
  *
  * @note The way of encoding an NDEF message may vary depending on tag's platform, which
  *       can be chosen with @ref NFC_NDEF_MSG_TAG_TYPE in @c sdk_config.h.
  *
  * @param[in]     p_ndef_msg_desc  Pointer to the message descriptor.
  * @param[out]    p_msg_buffer     Pointer to the message destination. If NULL, function will
 *                                  calculate the expected size of the message.
  * @param[in,out] p_msg_len        Size of the available memory for the message as input. Size of
  *                                 the generated message as output.
  *
  * @return  Return value from @ref nfc_ndef_record_encode.
  */
ret_code_t nfc_ndef_msg_encode(nfc_ndef_msg_desc_t const * p_ndef_msg_desc,
                               uint8_t                   * p_msg_buffer,
                               uint32_t                  * const  p_msg_len);

/**
 * @brief Function for clearing an NDEF message.
 *
 * This function clears an NDEF message descriptor, thus empties the NDEF message.
 *
 * @param[in,out] p_msg Pointer to the message descriptor.
 */
void nfc_ndef_msg_clear( nfc_ndef_msg_desc_t * p_msg);

/**
 * @brief Function for adding a record to an NDEF message.
 *
 * @param[in] p_record  Pointer to the record descriptor.
 * @param[in,out] p_msg Pointer to the message descriptor.
 *
 * @retval NRF_SUCCESS      If the record was added successfully.
 * @retval NRF_ERROR_NO_MEM If the message already contains the maximum number of records and the operation is not allowed.
 */
ret_code_t nfc_ndef_msg_record_add(nfc_ndef_msg_desc_t    * const p_msg,
                                   nfc_ndef_record_desc_t * const p_record);


/**@brief Macro for creating and initializing an NFC NDEF message descriptor.
 *
 * This macro creates and initializes an instance of type @ref nfc_ndef_msg_desc_t
 * and an array of pointers to record descriptors (@ref nfc_ndef_record_desc_t) used
 * by the message.
 *
 * Use the macro @ref NFC_NDEF_MSG to access the NDEF message descriptor instance.
 *
 * @note The message descriptor is declared as automatic variable, which implies that
 *       the NDEF message encoding must be done in the same variable scope.
 *
 * @param[in]  NAME                 Name of the related instance.
 * @param[in]  MAX_RECORD_CNT       Maximal count of records in the message.
 */
#define NFC_NDEF_MSG_DEF(NAME, MAX_RECORD_CNT)                                             \
    nfc_ndef_record_desc_t   * NAME##_nfc_ndef_p_record_desc_array[MAX_RECORD_CNT];        \
    nfc_ndef_msg_desc_t  NAME##_nfc_ndef_msg_desc =                                        \
        {                                                                                  \
            .pp_record = NAME##_nfc_ndef_p_record_desc_array,                              \
            .max_record_count = MAX_RECORD_CNT,                                            \
            .record_count = 0                                                              \
        }

/** @brief Macro for accessing the NFC NDEF message descriptor instance
 *  that you created with @ref NFC_NDEF_MSG_DEF.
 */
#define NFC_NDEF_MSG(NAME) (NAME##_nfc_ndef_msg_desc)

/**
 * @brief Macro for creating and initializing an NFC NDEF record descriptor with an encapsulated NDEF message.

 * This macro creates and initializes a static instance of type
 * @ref nfc_ndef_record_desc_t that contains an encapsulated NDEF message as
 * payload. @ref nfc_ndef_msg_encode is used as payload constructor to encode
 * the message. The encoded message is then used as payload for the record.
 *
 * Use the macro @ref NFC_NDEF_NESTED_NDEF_MSG_RECORD to access the NDEF record descriptor instance.
 *
 * @note The message descriptor is declared as automatic variable, which implies that
 *       the NDEF message encoding must be done in the same variable scope.
 *
 * @param[in] NAME             Name of the created record descriptor instance.
 * @param[in] TNF              Type Name Format (TNF) value for the record.
 * @param[in] P_ID             Pointer to the ID string.
 * @param[in] ID_LEN           Length of the ID string.
 * @param[in] P_TYPE           Pointer to the type string.
 * @param[in] TYPE_LEN         Length of the type string.
 * @param[in] P_NESTED_MESSAGE Pointer to the message descriptor to encapsulate
 *                             as the record's payload.
 */
#define NFC_NDEF_NESTED_NDEF_MSG_RECORD_DEF( NAME,                             \
                                             TNF,                              \
                                             P_ID,                             \
                                             ID_LEN,                           \
                                             P_TYPE,                           \
                                             TYPE_LEN,                         \
                                             P_NESTED_MESSAGE )                \
    nfc_ndef_record_desc_t NAME##_ndef_record_nested_desc =                    \
    {                                                                          \
        .tnf = TNF,                                                            \
                                                                               \
        .id_length = ID_LEN,                                                   \
        .p_id =  P_ID,                                                         \
                                                                               \
        .type_length = TYPE_LEN,                                               \
        .p_type = P_TYPE,                                                      \
                                                                               \
        .payload_constructor = (p_payload_constructor_t)(nfc_ndef_msg_encode), \
        .p_payload_descriptor = (void*) (P_NESTED_MESSAGE)                     \
    }

/** @brief Macro for accessing the NFC NDEF record descriptor instance
 *  that you created with @ref NFC_NDEF_NESTED_NDEF_MSG_RECORD_DEF.
 */
#define NFC_NDEF_NESTED_NDEF_MSG_RECORD(NAME) (NAME##_ndef_record_nested_desc)

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

