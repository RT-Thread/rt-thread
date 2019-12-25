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
#include "sdk_config.h"
#if NFC_T4T_CC_FILE_PARSER_ENABLED

#include <string.h>
#include "nfc_t4t_cc_file.h"
#include "sdk_macros.h"
#include "nordic_common.h"
#include "app_util.h"

#define NRF_LOG_MODULE_NAME nfc_t4t_cc_file_parser
#if NFC_T4T_CC_FILE_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_T4T_CC_FILE_PARSER_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_T4T_CC_FILE_PARSER_INFO_COLOR
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#else // NFC_T4T_CC_FILE_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#include "nrf_log.h"
#endif // NFC_T4T_CC_FILE_PARSER_LOG_ENABLED

/**
 * @brief Valid value range for CCLEN field.
 */
#define CC_LEN_MIN_VALUE           0x000F
#define CC_LEN_MAX_VALUE           0xFFFE

/**
 * @brief Valid major versions of Type 4 Tag specification.
 */
#define NFC_T4T_EXTENDED_MAJOR_VER 0x03  ///< Major version number allowing first TLV block to be Extended NDEF File Control TLV
#define NFC_T4T_REGULAR_MAJOR_VER  0x02  ///< Major version number allowing first TLV block to be NDEF File Control TLV

/**
 * @brief Valid value range for MLe field.
 */
#define MLE_LEN_MIN_VALUE          0x000F
#define MLE_LEN_MAX_VALUE          0xFFFF

/**
 * @brief Valid value range for MLc field.
 */
#define MLC_LEN_MIN_VALUE          0x0001
#define MLC_LEN_MAX_VALUE          0xFFFF

/**
 * @brief Field sizes that are present in CC file.
 */
#define CC_LEN_FIELD_SIZE          2U
#define MAP_VER_FIELD_SIZE         1U
#define MLE_FIELD_SIZE             2U
#define MLC_FIELD_SIZE             2U

/// Gets least significant nibble (a 4-bit value) from a byte.
#define LSN_GET(val) (val & 0x0F)

/// Gets most significant nibble (a 4-bit value) from a byte.
#define MSN_GET(val) ((val >> 4) & 0x0F)

/**
 * @brief Function for validating arguments used by CC file parsing procedure.
 */
__STATIC_INLINE ret_code_t nfc_t4t_cc_args_validate(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                                    uint8_t                        * p_raw_data,
                                                    uint16_t                         len)
{
    if ( (p_t4t_cc_file == NULL)
         || (p_t4t_cc_file->p_tlv_block_array == NULL)
         || (p_raw_data == NULL) )
    {
        return NRF_ERROR_NULL;
    }

    if ( (len < CC_LEN_MIN_VALUE) || (len > CC_LEN_MAX_VALUE) )
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    if (p_t4t_cc_file->max_tlv_blocks == 0)
    {
        return NRF_ERROR_NO_MEM;
    }

    return NRF_SUCCESS;
}


/**
 * @brief Function for validating CC file descriptor content.
 */
__STATIC_INLINE ret_code_t nfc_t4t_cc_file_validate(nfc_t4t_capability_container_t * p_t4t_cc_file)
{
    uint16_t type = p_t4t_cc_file->p_tlv_block_array[0].type;

    if ( (p_t4t_cc_file->major_version == NFC_T4T_EXTENDED_MAJOR_VER
          && type == EXTENDED_NDEF_FILE_CONTROL_TLV) ||
         (p_t4t_cc_file->major_version == NFC_T4T_REGULAR_MAJOR_VER
          && type == NDEF_FILE_CONTROL_TLV) )
    {
        return NRF_SUCCESS;
    }

    return NRF_ERROR_INVALID_DATA;
}


/**
 * @brief Function for clearing all TLV blocks from CC file descriptor.
 */
__STATIC_INLINE void nfc_t4t_cc_file_clear(nfc_t4t_capability_container_t * p_t4t_cc_file)
{
    p_t4t_cc_file->tlv_count = 0;
}


/**
 * @brief Function for adding a TLV block to the CC file descriptor.
 */
static ret_code_t nfc_t4t_tlv_block_insert(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                           nfc_t4t_tlv_block_t            * p_tlv_block)
{
    if (p_t4t_cc_file->tlv_count == p_t4t_cc_file->max_tlv_blocks)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Copy contents of the source block.
    p_t4t_cc_file->p_tlv_block_array[p_t4t_cc_file->tlv_count] = *p_tlv_block;
    p_t4t_cc_file->tlv_count++;

    return NRF_SUCCESS;
}


ret_code_t nfc_t4t_cc_file_parse(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                 uint8_t                        * p_raw_data,
                                 uint16_t                         len)
{
    ret_code_t err_code = nfc_t4t_cc_args_validate(p_t4t_cc_file, p_raw_data, len);
    VERIFY_SUCCESS(err_code);

    uint8_t * p_offset = p_raw_data;
    nfc_t4t_cc_file_clear(p_t4t_cc_file);

    p_t4t_cc_file->len = uint16_big_decode(p_offset);
    p_offset          += CC_LEN_FIELD_SIZE;

    p_t4t_cc_file->major_version = MSN_GET(*p_offset);
    p_t4t_cc_file->minor_version = LSN_GET(*p_offset);
    p_offset                    += MAP_VER_FIELD_SIZE;

    p_t4t_cc_file->max_rapdu_size = uint16_big_decode(p_offset);
    p_offset                     += MLE_FIELD_SIZE;

    p_t4t_cc_file->max_capdu_size = uint16_big_decode(p_offset);
    p_offset                     += MLC_FIELD_SIZE;

    nfc_t4t_tlv_block_t new_block;
    len -= (p_offset - p_raw_data);
    while (len > 0)
    {
        uint16_t tlv_len = len;
        err_code = nfc_t4t_file_control_tlv_parse(&new_block, p_offset, &tlv_len);
        VERIFY_SUCCESS(err_code);
        p_offset += tlv_len;
        len      -= tlv_len;

        err_code = nfc_t4t_tlv_block_insert(p_t4t_cc_file, &new_block);
        VERIFY_SUCCESS(err_code);
    }

    return nfc_t4t_cc_file_validate(p_t4t_cc_file);
}


nfc_t4t_tlv_block_t * nfc_t4t_file_content_get(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                               uint16_t                         file_id)
{
    nfc_t4t_tlv_block_t * p_tlv_array = p_t4t_cc_file->p_tlv_block_array;
    for (uint8_t i = 0; i < p_t4t_cc_file->tlv_count; i++)
    {
        nfc_t4t_file_control_val_t * p_tlv_value = &p_tlv_array[i].value;
        if (p_tlv_value->file_id == file_id)
        {
            return (p_tlv_array + i);
        }
    }
    return NULL;
}


ret_code_t nfc_t4t_file_content_set(nfc_t4t_capability_container_t * p_t4t_cc_file,
                                    nfc_t4t_file_t                   file,
                                    uint16_t                         file_id)
{
    nfc_t4t_tlv_block_t * p_tlv_block;

    p_tlv_block = nfc_t4t_file_content_get(p_t4t_cc_file, file_id);
    if (p_tlv_block != NULL)
    {
        p_tlv_block->value.file = file;
        return NRF_SUCCESS;
    }
    return NRF_ERROR_NOT_FOUND;
}


void nfc_t4t_cc_file_printout(nfc_t4t_capability_container_t * p_t4t_cc_file)
{
    NRF_LOG_INFO("Capability Container File content: ")
    NRF_LOG_INFO("CCLEN: %d ", p_t4t_cc_file->len);
    NRF_LOG_INFO("Mapping Version: %d.%d ",
                 p_t4t_cc_file->major_version,
                 p_t4t_cc_file->minor_version);
    NRF_LOG_INFO("MLe: %d ", p_t4t_cc_file->max_rapdu_size)
    NRF_LOG_INFO("MLc: %d ", p_t4t_cc_file->max_capdu_size)

    NRF_LOG_INFO("Capability Container File contains %d File Control TLV block(s).",
                 p_t4t_cc_file->tlv_count);
    for (uint8_t i = 0; i < p_t4t_cc_file->tlv_count; i++)
    {
        nfc_t4t_file_control_tlv_printout(i, &p_t4t_cc_file->p_tlv_block_array[i]);
    }
}


#endif // NFC_T4T_CC_FILE_PARSER_ENABLED

