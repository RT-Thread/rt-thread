/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#ifndef NFC_T4T_TLV_BLOCK_H__
#define NFC_T4T_TLV_BLOCK_H__

/**@file
 *
 * @defgroup nfc_t4t_tlv_block File Control TLV block parser for Type 4 Tag.
 * @{
 * @ingroup  nfc_t4t_cc_file
 *
 * @brief    File Control TLV block parser for Type 4 Tag (T4T).
 *
 */

#include <stdint.h>
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CONTROL_FILE_READ_ACCESS_GRANTED   0x00 ///< Read access granted without any security.

/**
 * @name Possible values of file write access condition field.
 * @{
 */
#define CONTROL_FILE_WRITE_ACCESS_GRANTED  0x00 ///< Write access granted without any security.
#define CONTROL_FILE_WRITE_ACCESS_DISABLED 0xFF ///< No write access granted without any security (read-only).
/** @} */

/**
 * @brief Possible types of File Control TLV for Type 4 Tag.
 */
typedef enum
{
    NDEF_FILE_CONTROL_TLV          = 0x04, ///< Control information concerning the EF file with short NDEF message.
    PROPRIETARY_FILE_CONTROL_TLV   = 0x05, ///< Control information concerning the Proprietary file with proprietary data.
    EXTENDED_NDEF_FILE_CONTROL_TLV = 0x06  ///< Control information concerning the EF file with long NDEF message.
} nfc_t4t_tlv_block_types_t;

/**
 * @brief File content descriptor.
 */
typedef struct
{
    uint8_t * p_content; ///< Pointer to the file content.
    uint16_t  len;       ///< Length of file content.
} nfc_t4t_file_t;

/**
 * @brief Extended NDEF/NDEF/Proprietary File Control Value descriptor.
 */
typedef struct
{
    nfc_t4t_file_t file;          ///< Pointer to the described file content.
    uint32_t       max_file_size; ///< Maximum size (in bytes) of the file.
    uint16_t       file_id;       ///< File identifier.
    uint8_t        read_access;   ///< File read access condition.
    uint8_t        write_access;  ///< File write access condition.
} nfc_t4t_file_control_val_t;

/**
 * @brief File Control TLV block descriptor.
 */
typedef struct
{
    nfc_t4t_file_control_val_t value;  ///< Value field descriptor.
    uint16_t                   length; ///< Length of the value field.
    uint8_t                    type;   ///< Type of the TLV block.
} nfc_t4t_tlv_block_t;

/**
 * @brief Function for parsing raw data of File Control TLV, read from a Type 4 Tag.
 *
 * This function parses raw data of File Control TLV and stores the results in its
 * descriptor.
 *
 * @param[in,out]  p_file_control_tlv Pointer to the File Control TLV that will be filled with
 *                                    parsed data.
 * @param[in]      p_raw_data         Pointer to the buffer with raw TLV data.
 * @param[in,out]  p_len              In:  Buffer length with TLV blocks.
 *                                    Out: Total length of first identified TLV within the buffer.
 *
 * @retval NRF_SUCCESS                If operation was successful.
 * @retval NRF_ERROR_INVALID_LENGTH   If provided buffer length is too small for TLV block.
 * @retval NRF_ERROR_INVALID_DATA     If any TLV block field contains invalid data.
 */
ret_code_t nfc_t4t_file_control_tlv_parse(nfc_t4t_tlv_block_t * p_file_control_tlv,
                                          uint8_t             * p_raw_data,
                                          uint16_t            * p_len);

/**
 * @brief Function for printing TLV block descriptor.
 *
 * This function prints TLV block descriptor.
 *
 * @param[in]  num             TLV block number.
 * @param[in]  p_t4t_tlv_block Pointer to the TLV block descriptor.
 */
void nfc_t4t_file_control_tlv_printout(uint8_t num, nfc_t4t_tlv_block_t * p_t4t_tlv_block);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NFC_T4T_TLV_BLOCK_H__ */
