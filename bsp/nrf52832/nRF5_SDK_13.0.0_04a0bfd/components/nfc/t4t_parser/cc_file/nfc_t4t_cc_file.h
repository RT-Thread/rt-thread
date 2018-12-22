/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef NFC_T4T_CC_FILE_H__
#define NFC_T4T_CC_FILE_H__

/**@file
 *
 * @defgroup nfc_t4t_cc_file CC file parser
 * @{
 * @ingroup  nfc_t4t_parser
 *
 * @brief    Capability Container file parser for Type 4 Tag.
 *
 */

#include <stdint.h>
#include "sdk_errors.h"
#include "nfc_t4t_tlv_block.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Descriptor for the Capability Container (CC) file of  Type 4 Tag.
 */
typedef struct
{
    nfc_t4t_tlv_block_t * p_tlv_block_array; ///< Pointer to the array for TLV blocks.
    uint16_t              tlv_count;         ///< Number of TLV blocks stored in the Type 4 Tag.
    uint16_t        const max_tlv_blocks;    ///< Maximum number of TLV blocks.
    uint16_t              len;               ///< Size (bytes) of a Capability Container including this field.
    uint16_t              max_rapdu_size;    ///< MLe field - maximum R-APDU data size (bytes).
    uint16_t              max_capdu_size;    ///< MLc field - maximum C-APDU data size (bytes).
    uint8_t               major_version;     ///< Major version of the supported Type 4 Tag specification.
    uint8_t               minor_version;     ///< Minor version of the supported Type 4 Tag specification.
} nfc_t4t_capability_container_t;

/**
 * @brief Macro for creating and initializing a Type 4 Tag Capability Container descriptor.
 *
 * This macro creates and initializes a static instance of a @ref nfc_t4t_capability_container_t
 * structure and an array of @ref nfc_t4t_tlv_block_t descriptors.
 *
 * Use the macro @ref NFC_T4T_CC_DESC to access the Type 4 Tag descriptor instance.
 *
 * @param[in] NAME        Name of the created descriptor instance.
 * @param[in] MAX_BLOCKS  Maximum number of @ref nfc_t4t_tlv_block_t descriptors that can be
 *                        stored in the array.
 *
 */
#define NFC_T4T_CC_DESC_DEF(NAME, MAX_BLOCKS)                                 \
    static nfc_t4t_tlv_block_t            NAME##_tlv_block_array[MAX_BLOCKS]; \
    static nfc_t4t_capability_container_t NAME##_type_4_tag =                 \
    {                                                                         \
        .max_tlv_blocks    = MAX_BLOCKS,                                      \
        .p_tlv_block_array = NAME##_tlv_block_array,                          \
        .tlv_count         = 0                                                \
    }

/**
 * @brief Macro for accessing the @ref nfc_t4t_capability_container_t instance that was created
 *        with @ref NFC_T4T_CC_DESC_DEF.
 *
 * @param[in] NAME  Name of the created descriptor instance.
 */
#define NFC_T4T_CC_DESC(NAME) (NAME##_type_4_tag)

/**
 * @brief Function for parsing raw data of a CC file, read from a Type 4 Tag.
 *
 * This function parses raw data of a Capability Container file and stores the results in its
 * descriptor.
 *
 * @param[in,out]  p_t4t_cc_file    Pointer to the CC file descriptor that will be filled with
 *                                  parsed data.
 * @param[in]      p_raw_data       Pointer to the buffer with raw data.
 * @param[in]      len              Buffer length.
 *
 * @retval NRF_SUCCESS              If operation was successful.
 * @retval NRF_ERROR_NULL           If any of the provided pointer arguments is NULL.
 * @retval NRF_ERROR_INVALID_LENGTH If provided buffer exceeds a valid CC file length range.
 * @retval NRF_ERROR_INVALID_DATA   If mapping version of Type 4 Tag specification is not a
 *                                  compatible CC file structure.
 * @retval Other                    Other error codes might be returned depending on
 *                                  @ref nfc_t4t_file_control_tlv_parse function.
 */
ret_code_t nfc_t4t_cc_file_parse(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                 uint8_t                        * p_raw_data,
                                 uint16_t                         len);

/**
 * @brief Function for finding File Control TLV block within the CC file descriptor.
 *
 * This function finds File Control TLV block that matches
 * the specified file ID within the CC file descriptor.
 *
 * @param[in] p_t4t_cc_file Pointer to the CC file descriptor.
 * @param[in] file_id       File identifier.
 *
 * @retval TLV  Pointer to the File Control TLV.
 * @retval NULL If TLV with the specified File ID was not found.
 */
nfc_t4t_tlv_block_t * nfc_t4t_file_content_get(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                               uint16_t                         file_id);

/**
 * @brief Function for binding a file with its File Control TLV block.
 *
 * This function binds file content with its File Control TLV block, in which
 * maximal file size and access conditions are stored.
 *
 * @param[in,out]  p_t4t_cc_file Pointer to the CC file descriptor.
 * @param[in]      file          File descriptor.
 * @param[in]      file_id       File identifier.
 *
 * @retval NRF_SUCCESS           If operation was successful.
 * @retval NRF_ERROR_NOT_FOUND   If the provided file ID does not match any ID stored in TLV blocks
 *                               of the CC file.
 */
ret_code_t nfc_t4t_file_content_set(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                    nfc_t4t_file_t                   file,
                                    uint16_t                         file_id);

/**
 * @brief Function for printing the CC file descriptor.
 *
 * This function prints the CC file descriptor.
 *
 * @param[in]  p_t4t_cc_file  Pointer to the CC file.
 */
void nfc_t4t_cc_file_printout(nfc_t4t_capability_container_t * p_t4t_cc_file);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NFC_T4T_CC_FILE_H__ */
