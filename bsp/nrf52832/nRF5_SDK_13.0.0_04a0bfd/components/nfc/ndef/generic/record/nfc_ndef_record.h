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
#ifndef NFC_NDEF_RECORD_H__
#define NFC_NDEF_RECORD_H__

#include <stdint.h>
#include <string.h>
#include "compiler_abstraction.h"
#include "sdk_errors.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@file
 *
 * @defgroup nfc_ndef_record Custom NDEF records
 * @{
 * @ingroup  nfc_ndef_msg
 *
 * @brief    Generation of NFC NDEF records for NFC messages.
 *
 */


#define NDEF_RECORD_IL_MASK                0x08 ///< Mask of the ID field presence bit in the flags byte of an NDEF record.
#define NDEF_RECORD_TNF_MASK               0x07 ///< Mask of the TNF value field in the first byte of an NDEF record.
#define NDEF_RECORD_SR_MASK                0x10 ///< Mask of the SR flag. If set, this flag indicates that the PAYLOAD_LENGTH field has a size of 1 byte. Otherwise, PAYLOAD_LENGTH has 4 bytes.
#define NDEF_RECORD_PAYLOAD_LEN_LONG_SIZE  4    ///< Size of the Payload Length field in a long NDEF record.
#define NDEF_RECORD_PAYLOAD_LEN_SHORT_SIZE 1    ///< Size of the Payload Length field in a short NDEF record.
#define NDEF_RECORD_ID_LEN_SIZE            1    ///< Size of the ID Length field in an NDEF record.


/**
 * @brief Payload constructor type.

 * A payload constructor is a function for constructing the payload of an NDEF
 * record.
 *
 * @param[in] p_payload_descriptor  Pointer to the input data for the constructor.
 * @param[out] p_buffer             Pointer to the payload destination. If NULL, function will
 *                                  calculate the expected size of the record payload.
 *
 * @param[in,out] p_len             Size of the available memory to write as input. Size of the generated
 *                                  record payload as output. The implementation must check if the payload
 *                                  will fit in the provided buffer. This must be checked by the caller function.
 *
 * @retval NRF_SUCCESS     If the function completed successfully.
 * @retval NRF_ERROR_xxx   If an error occurred.
 */
typedef ret_code_t (* p_payload_constructor_t)(void     * p_payload_descriptor,
                                               uint8_t  * p_buffer,
                                               uint32_t * p_len);


/**
 * @brief Type Name Format (TNF) Field Values.
 *
 * Values to specify the TNF of a record.
 */
typedef enum
{
    TNF_EMPTY         = 0x00, ///< The value indicates that there is no type or payload associated with this record.
    TNF_WELL_KNOWN    = 0x01, ///< NFC Forum well-known type [NFC RTD].
    TNF_MEDIA_TYPE    = 0x02, ///< Media-type as defined in RFC 2046 [RFC 2046].
    TNF_ABSOLUTE_URI  = 0x03, ///< Absolute URI as defined in RFC 3986 [RFC 3986].
    TNF_EXTERNAL_TYPE = 0x04, ///< NFC Forum external type [NFC RTD].
    TNF_UNKNOWN_TYPE  = 0x05, ///< The value indicates that there is no type associated with this record.
    TNF_UNCHANGED     = 0x06, ///< The value is used for the record chunks used in chunked payload.
    TNF_RESERVED      = 0x07, ///< The value is reserved for future use.
} nfc_ndef_record_tnf_t;


/**
 * @brief NDEF record descriptor.
 */
typedef struct
{
    nfc_ndef_record_tnf_t tnf;                    ///< Value of the Type Name Format (TNF) field.

    uint8_t         id_length;                    ///< Length of the ID field. If 0, a record format without ID field is assumed.
    uint8_t const * p_id;                         ///< Pointer to the ID field data. Not relevant if id_length is 0.

    uint8_t         type_length;                  ///< Length of the type field.
    uint8_t const * p_type;                       ///< Pointer to the type field data. Not relevant if type_length is 0.

    p_payload_constructor_t payload_constructor;  ///< Pointer to the payload constructor function.
    void                  * p_payload_descriptor; ///< Pointer to the data for the payload constructor function.

} nfc_ndef_record_desc_t;

/**
 * @brief Record position within the NDEF message.
 *
 * Values to specify the location of a record within the NDEF message.
 */
typedef enum
{
    NDEF_FIRST_RECORD  = 0x80, ///< First record.
    NDEF_MIDDLE_RECORD = 0x00, ///< Middle record.
    NDEF_LAST_RECORD   = 0x40, ///< Last record.
    NDEF_LONE_RECORD   = 0xC0  ///< Only one record in the message.
} nfc_ndef_record_location_t;

#define NDEF_RECORD_LOCATION_MASK (NDEF_LONE_RECORD) ///< Mask of the Record Location bits in the NDEF record's flags byte.

/**
 * @brief Binary data descriptor containing the payload for the record.
 */
typedef struct
{
    uint8_t const * p_payload;      ///< Pointer to the buffer with the data.
    uint32_t        payload_length; ///< Length of data in bytes.
} nfc_ndef_bin_payload_desc_t;

/**
 * @brief Macro for creating and initializing an NFC NDEF record descriptor for a generic record.
 *
 * This macro creates and initializes a static instance of type @ref nfc_ndef_record_desc_t.
 *
 * Use the macro @ref NFC_NDEF_GENERIC_RECORD_DESC to access the NDEF record descriptor instance.
 *
 * @param[in] NAME                  Name of the created descriptor instance.
 * @param[in] TNF                   Type Name Format (TNF) value for the record.
 * @param[in] P_ID                  Pointer to the ID string.
 * @param[in] ID_LEN                Length of the ID string.
 * @param[in] P_TYPE                Pointer to the type string.
 * @param[in] TYPE_LEN              Length of the type string.
 * @param[in] P_PAYLOAD_CONSTRUCTOR Pointer to the payload constructor function.
 *                                  The constructor must be of type @ref p_payload_constructor_t.
 * @param[in] P_PAYLOAD_DESCRIPTOR  Pointer to the data for the payload constructor.
 */
#define NFC_NDEF_GENERIC_RECORD_DESC_DEF(NAME,                                  \
                                         TNF,                                   \
                                         P_ID,                                  \
                                         ID_LEN,                                \
                                         P_TYPE,                                \
                                         TYPE_LEN,                              \
                                         P_PAYLOAD_CONSTRUCTOR,                 \
                                         P_PAYLOAD_DESCRIPTOR)                  \
    static nfc_ndef_record_desc_t NAME##_ndef_generic_record_desc =             \
    {                                                                           \
        .tnf = TNF,                                                             \
                                                                                \
        .id_length = ID_LEN,                                                    \
        .p_id      = P_ID,                                                      \
                                                                                \
        .type_length = TYPE_LEN,                                                \
        .p_type      = P_TYPE,                                                  \
                                                                                \
        .payload_constructor  = (p_payload_constructor_t)P_PAYLOAD_CONSTRUCTOR, \
        .p_payload_descriptor = (void *) P_PAYLOAD_DESCRIPTOR                   \
    }


/** @brief Macro for accessing the NFC NDEF record descriptor instance
 *  that you created with @ref NFC_NDEF_GENERIC_RECORD_DESC_DEF.
 */
#define NFC_NDEF_GENERIC_RECORD_DESC(NAME) (NAME##_ndef_generic_record_desc)

/**
 * @brief Macro for creating and initializing an NFC NDEF record descriptor for a record with
 * binary payload.
 *
 * This macro creates and initializes a static instance of type @ref nfc_ndef_record_desc_t and a binary data descriptor containing the payload data.
 *
 * Use the macro @ref NFC_NDEF_RECORD_BIN_DATA to access the NDEF record descriptor instance.
 *
 * @param[in] NAME        Name of the created descriptor instance.
 * @param[in] TNF         Type Name Format (TNF) value for the record.
 * @param[in] P_ID        Pointer to the ID string.
 * @param[in] ID_LEN      Length of the ID string.
 * @param[in] P_TYPE      Pointer to the type string.
 * @param[in] TYPE_LEN    Length of the type string.
 * @param[in] P_PAYLOAD   Pointer to the payload data that will be copied to the payload field.
 * @param[in] PAYLOAD_LEN Length of the payload.
 */
#define NFC_NDEF_RECORD_BIN_DATA_DEF(NAME,                                              \
                                     TNF,                                               \
                                     P_ID, ID_LEN,                                      \
                                     P_TYPE,                                            \
                                     TYPE_LEN,                                          \
                                     P_PAYLOAD,                                         \
                                     PAYLOAD_LEN)                                       \
    static nfc_ndef_bin_payload_desc_t NAME##_nfc_ndef_bin_payload_desc =               \
    {                                                                                   \
        .p_payload      = P_PAYLOAD,                                                    \
        .payload_length = PAYLOAD_LEN                                                   \
    };                                                                                  \
                                                                                        \
    static nfc_ndef_record_desc_t NAME##_nfc_ndef_bin_record_desc =                     \
    {                                                                                   \
        .tnf = TNF,                                                                     \
                                                                                        \
        .id_length = ID_LEN,                                                            \
        .p_id      = P_ID,                                                              \
                                                                                        \
        .type_length = TYPE_LEN,                                                        \
        .p_type      = P_TYPE,                                                          \
                                                                                        \
        .payload_constructor  = (p_payload_constructor_t) nfc_ndef_bin_payload_memcopy, \
        .p_payload_descriptor = (void *) &NAME##_nfc_ndef_bin_payload_desc              \
    }


/** @brief Macro for accessing the NFC NDEF record descriptor instance
 *  that you created with @ref NFC_NDEF_RECORD_BIN_DATA_DEF.
 */
#define NFC_NDEF_RECORD_BIN_DATA(NAME) (NAME##_nfc_ndef_bin_record_desc)

/** @brief Macro for accessing the binary data descriptor that contains
 * the payload of the record that you created with @ref NFC_NDEF_RECORD_BIN_DATA_DEF.
 */
#define NFC_NDEF_BIN_PAYLOAD_DESC(NAME) (NAME##_nfc_ndef_bin_payload_desc)

/**
 * @brief Function for encoding an NDEF record.
 *
 * This function encodes an NDEF record according to the provided record descriptor.
 *
 * @param[in] p_ndef_record_desc  Pointer to the record descriptor.
 * @param[in] record_location     Location of the record within the NDEF message.
 * @param[out] p_record_buffer    Pointer to the record destination. If NULL, function will
 *                                calculate the expected size of the record.
 * @param[in,out] p_record_len    Size of the available memory for the record as input. Size of the generated
 *                                record as output.
 *
 * @retval NRF_SUCCESS              If the record was encoded successfully.
 * @retval NRF_ERROR_NO_MEM         If the predicted record size is bigger than the provided buffer space.
 * @retval NRF_ERROR_INVALID_PARAM  If the location of the record is erroneous.
 * @retval Other                    Other codes might be returned depending on the NDEF record payload constructor implementation.
 */
ret_code_t nfc_ndef_record_encode(nfc_ndef_record_desc_t const * p_ndef_record_desc,
                                  nfc_ndef_record_location_t     record_location,
                                  uint8_t                      * p_record_buffer,
                                  uint32_t                     * p_record_len);

/**
 * @brief Function for constructing the payload for an NFC NDEF record from binary data.
 *
 * This function copies data from a binary buffer to the payload field of the NFC NDEF record.
 *
 * @param[in] p_payload_descriptor   Pointer to the descriptor of the binary data location and size.
 *
 * @param[out] p_buffer              Pointer to the payload destination. If NULL, function will
 *                                   calculate the expected size of the record payload.
 * @param[in,out] p_len              Size of the available memory for the payload as input. Size of the copied payload
 *                                   as output.
 *
 * @retval NRF_SUCCESS      If the function completed successfully.
 * @retval NRF_ERROR_NO_MEM If the payload size is bigger than the provided buffer space.
 */
ret_code_t nfc_ndef_bin_payload_memcopy(nfc_ndef_bin_payload_desc_t * p_payload_descriptor,
                                        uint8_t                     * p_buffer,
                                        uint32_t                    * p_len);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif // NFC_NDEF_RECORD_H__

