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
#include "sdk_config.h"
#if NFC_T4T_TLV_BLOCK_PARSER_ENABLED

#include <string.h>
#include "nfc_t4t_tlv_block.h"
#include "app_util.h"
#include "sdk_macros.h"
#include "nordic_common.h"

#define NRF_LOG_MODULE_NAME "NFC_T4T_TLV_BLOCK_PARSER"
#if NFC_T4T_TLV_BLOCK_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_T4T_TLV_BLOCK_PARSER_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_T4T_TLV_BLOCK_PARSER_INFO_COLOR
#else // NFC_T4T_TLV_BLOCK_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // NFC_T4T_TLV_BLOCK_PARSER_LOG_ENABLED
#include "nrf_log.h"

#define TLV_TYPE_FIELD_LEN                  1U    ///< Length of a type field.

/**
 * @brief TLV length field related defines.
 */
#define TLV_LEN_SHORT_FIELD_LEN                1U    ///< Length of a short length field.
#define TLV_LEN_LONG_FIELD_LEN                 3U    ///< Length of an extended length field.
#define TLV_LEN_LONG_FORMAT_TOKEN              0xFF  ///< Value indicating the use of an extended length field.
#define TLV_LEN_LONG_FORMAT_TOKEN_SIZE         1U    ///< Size of long format token.
#define TLV_LEN_LONG_FORMAT_MIN_VALUE          0xFF  ///< The minimal value of length field that can be used in long format.

/**
 * @brief Possible sizes of TLV block.
 */
#define TLV_MIN_TL_FIELD_LEN                   (TLV_TYPE_FIELD_LEN + TLV_LEN_SHORT_FIELD_LEN)
#define TLV_MIN_LONG_FORMAT_TL_FIELD_LEN       (TLV_TYPE_FIELD_LEN + TLV_LEN_LONG_FIELD_LEN)
#define TLV_MIN_VALUE_FIELD_SIZE               6U

/**
 * @brief Field sizes that are present in TLV block.
 */
#define FILE_CONTROL_FILE_ID_FIELD_SIZE        2U
#define FILE_CONTROL_READ_ACCESS_FIELD_SIZE    1U
#define FILE_CONTROL_WRITE_ACCESS_FIELD_SIZE   1U
#define FILE_CONTROL_COMMON_FIELDS_SIZE        (FILE_CONTROL_FILE_ID_FIELD_SIZE       \
                                               + FILE_CONTROL_READ_ACCESS_FIELD_SIZE  \
                                               + FILE_CONTROL_WRITE_ACCESS_FIELD_SIZE)

/**
 * @brief Invalid values for File Identifier field.
 */
#define FILE_ID_INVALID_VALUE_0                0x0000
#define FILE_ID_INVALID_VALUE_1                0xE102
#define FILE_ID_INVALID_VALUE_2                0xE103
#define FILE_ID_INVALID_VALUE_3                0x3F00
#define FILE_ID_INVALID_VALUE_4                0x3FFF
#define FILE_ID_INVALID_VALUE_5                0xFFFF

/**
 * @brief NDEF file related defines.
 */
#define NDEF_FILE_MAX_SIZE_FIELD_SIZE          2U
#define NDEF_FILE_MAX_SIZE_MIN_VAL             0x0005
#define NDEF_FILE_MAX_SIZE_MAX_VAL             0xFFFE
#define NDEF_FILE_CONTROL_TLV_LEN              (FILE_CONTROL_COMMON_FIELDS_SIZE \
                                               + NDEF_FILE_MAX_SIZE_FIELD_SIZE)

/**
 * @brief Proprietary file related defines.
 */
#define PROPRIETARY_FILE_MAX_SIZE_FIELD_SIZE   2U
#define PROPRIETARY_FILE_MAX_SIZE_MIN_VAL      0x0003
#define PROPRIETARY_FILE_MAX_SIZE_MAX_VAL      0xFFFE
#define PROPRIETARY_FILE_CONTROL_TLV_LEN       (FILE_CONTROL_COMMON_FIELDS_SIZE        \
                                                + PROPRIETARY_FILE_MAX_SIZE_FIELD_SIZE)

/**
 * @brief Extended NDEF file related defines.
 */
#define EXTENDED_NDEF_FILE_MAX_SIZE_FIELD_SIZE 4U
#define EXTENDED_NDEF_FILE_MAX_SIZE_MIN_VAL    0x0000FFFF
#define EXTENDED_NDEF_FILE_MAX_SIZE_MAX_VAL    0xFFFFFFFE
#define EXTENDED_NDEF_FILE_CONTROL_TLV_LEN     (FILE_CONTROL_COMMON_FIELDS_SIZE          \
                                                + EXTENDED_NDEF_FILE_MAX_SIZE_FIELD_SIZE)

/**
 * @brief Validates maximum file size field range. This field is present in every File Control TLV.
 */
#define NFC_T4T_FILE_CONTROL_MAX_SIZE_FIELD_RANGE_VERIFY(VALUE, MIN, MAX) \
    if ( ( (VALUE) < (MIN) ) || ( (VALUE) > (MAX) ) )                     \
    {                                                                     \
        return NRF_ERROR_INVALID_DATA;                                    \
    }


/**
 * @brief Function for validating all possible types of File Control TLV.
 */
__STATIC_INLINE ret_code_t nfc_t4t_file_control_tl_validate(nfc_t4t_tlv_block_t * p_file_control_tlv)
{
    switch (p_file_control_tlv->type)
    {
        case NDEF_FILE_CONTROL_TLV:
            VERIFY_TRUE(p_file_control_tlv->length == NDEF_FILE_CONTROL_TLV_LEN,
                        NRF_ERROR_INVALID_DATA);
            return NRF_SUCCESS;

        case PROPRIETARY_FILE_CONTROL_TLV:
            VERIFY_TRUE(p_file_control_tlv->length == PROPRIETARY_FILE_CONTROL_TLV_LEN,
                        NRF_ERROR_INVALID_DATA);
            return NRF_SUCCESS;

        case EXTENDED_NDEF_FILE_CONTROL_TLV:
            VERIFY_TRUE(p_file_control_tlv->length == EXTENDED_NDEF_FILE_CONTROL_TLV_LEN,
                        NRF_ERROR_INVALID_DATA);
            return NRF_SUCCESS;

        default:
            return NRF_ERROR_INVALID_DATA;
    }
}


/**
 * @brief Function for parsing value field of File Control TLV.
 */
static ret_code_t nfc_t4t_file_control_value_parse(nfc_t4t_tlv_block_t * p_file_control_tlv,
                                                   uint8_t             * p_value_buff)
{
    nfc_t4t_file_control_val_t * p_control_tlv_val;

    // Handle File Identifier field.
    p_control_tlv_val          = &p_file_control_tlv->value;
    p_control_tlv_val->file_id = uint16_big_decode(p_value_buff);
    p_value_buff              += FILE_CONTROL_FILE_ID_FIELD_SIZE;

    switch (p_control_tlv_val->file_id)
    {
        case FILE_ID_INVALID_VALUE_0:
        case FILE_ID_INVALID_VALUE_1:
        case FILE_ID_INVALID_VALUE_2:
        case FILE_ID_INVALID_VALUE_3:
        case FILE_ID_INVALID_VALUE_4:
        case FILE_ID_INVALID_VALUE_5:
            return NRF_ERROR_INVALID_DATA;

        default:
            break;
    }

    // Handle Max file size field.
    switch (p_file_control_tlv->type)
    {
        case NDEF_FILE_CONTROL_TLV:
            p_control_tlv_val->max_file_size = uint16_big_decode(p_value_buff);
            p_value_buff                    += NDEF_FILE_MAX_SIZE_FIELD_SIZE;
            NFC_T4T_FILE_CONTROL_MAX_SIZE_FIELD_RANGE_VERIFY(p_control_tlv_val->max_file_size,
                                                             NDEF_FILE_MAX_SIZE_MIN_VAL,
                                                             NDEF_FILE_MAX_SIZE_MAX_VAL);
            break;

        case PROPRIETARY_FILE_CONTROL_TLV:
            p_control_tlv_val->max_file_size = uint16_big_decode(p_value_buff);
            p_value_buff                    += PROPRIETARY_FILE_MAX_SIZE_FIELD_SIZE;
            NFC_T4T_FILE_CONTROL_MAX_SIZE_FIELD_RANGE_VERIFY(p_control_tlv_val->max_file_size,
                                                             PROPRIETARY_FILE_MAX_SIZE_MIN_VAL,
                                                             PROPRIETARY_FILE_MAX_SIZE_MAX_VAL);
            break;

        case EXTENDED_NDEF_FILE_CONTROL_TLV:
            p_control_tlv_val->max_file_size = uint32_big_decode(p_value_buff);
            p_value_buff                    += EXTENDED_NDEF_FILE_MAX_SIZE_FIELD_SIZE;
            NFC_T4T_FILE_CONTROL_MAX_SIZE_FIELD_RANGE_VERIFY(p_control_tlv_val->max_file_size,
                                                             EXTENDED_NDEF_FILE_MAX_SIZE_MIN_VAL,
                                                             EXTENDED_NDEF_FILE_MAX_SIZE_MAX_VAL);
            break;
    }

    // Handle read access condition field.
    p_control_tlv_val->read_access = *p_value_buff;
    p_value_buff                  += FILE_CONTROL_READ_ACCESS_FIELD_SIZE;

    // Handle write access condition field.
    p_control_tlv_val->write_access = *p_value_buff;

    return NRF_SUCCESS;
}


ret_code_t nfc_t4t_file_control_tlv_parse(nfc_t4t_tlv_block_t * p_file_control_tlv,
                                          uint8_t             * p_raw_data,
                                          uint16_t            * p_len)
{
    ret_code_t err_code;
    uint8_t  * p_offset = p_raw_data;

    if (*p_len < TLV_MIN_TL_FIELD_LEN)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    memset(p_file_control_tlv, 0, sizeof(nfc_t4t_tlv_block_t));

    // Handle type field of TLV block.
    p_file_control_tlv->type = *p_offset;
    p_offset                += TLV_TYPE_FIELD_LEN;

    // Handle length field of TLV block.
    if (*p_offset == TLV_LEN_LONG_FORMAT_TOKEN)
    {
        if (*p_len < TLV_MIN_LONG_FORMAT_TL_FIELD_LEN)
        {
            return NRF_ERROR_INVALID_LENGTH;
        }

        p_file_control_tlv->length = uint16_big_decode(p_offset + TLV_LEN_LONG_FORMAT_TOKEN_SIZE);
        p_offset                  += TLV_LEN_LONG_FIELD_LEN;

        if (p_file_control_tlv->length < TLV_LEN_LONG_FORMAT_MIN_VALUE)
        {
            return NRF_ERROR_INVALID_DATA;
        }
    }
    else
    {
        p_file_control_tlv->length = *p_offset;
        p_offset                  += TLV_LEN_SHORT_FIELD_LEN;
    }

    // Calculate the total TLV block size.
    uint16_t tlv_block_len = (p_offset - p_raw_data) + p_file_control_tlv->length;
    if (*p_len < tlv_block_len)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    *p_len = tlv_block_len;

    // Validate if type and length fields contain values supported by Type 4 Tag.
    err_code = nfc_t4t_file_control_tl_validate(p_file_control_tlv);
    VERIFY_SUCCESS(err_code);

    // Handle value field of TLV block.
    err_code = nfc_t4t_file_control_value_parse(p_file_control_tlv, p_offset);
    return err_code;
}


void nfc_t4t_file_control_tlv_printout(uint8_t num, nfc_t4t_tlv_block_t * p_t4t_tlv_block)
{
    NRF_LOG_INFO("%d file Control TLV\r\n", num);
    switch (p_t4t_tlv_block->type)
    {
        case NDEF_FILE_CONTROL_TLV:
            NRF_LOG_INFO("Type: NDEF File Control (0x%02x)\r\n", p_t4t_tlv_block->type);
            break;

        case PROPRIETARY_FILE_CONTROL_TLV:
            NRF_LOG_INFO("Type: Proprietary File Control (0x%02x)\r\n", p_t4t_tlv_block->type);
            break;

        case EXTENDED_NDEF_FILE_CONTROL_TLV:
            NRF_LOG_INFO("Type: Extended NDEF File Control (0x%02x)\r\n", p_t4t_tlv_block->type);
            break;

        default:
            NRF_LOG_INFO("Type: Unknown (0x%02x)\r\n", p_t4t_tlv_block->type);
    }
    NRF_LOG_INFO("Length (in bytes): %d\r\n", p_t4t_tlv_block->length);

    nfc_t4t_file_control_val_t * p_tlv_val = &p_t4t_tlv_block->value;
    NRF_LOG_INFO("File Identifier: 0x%04X \r\n", p_tlv_val->file_id);
    NRF_LOG_INFO("Maximum file size: %d \r\n", p_tlv_val->max_file_size);
    NRF_LOG_INFO("Read access condition: 0x%02X \r\n", p_tlv_val->read_access);
    NRF_LOG_INFO("Write access condition: 0x%02x \r\n\r\n", p_tlv_val->write_access);

    if (p_tlv_val->file.p_content != NULL)
    {
        NRF_LOG_INFO("NDEF file content present. Length: %d \r\n", p_tlv_val->file.len);
        NRF_LOG_HEXDUMP_INFO(p_tlv_val->file.p_content, p_tlv_val->file.len);
    }
    else
    {
        NRF_LOG_INFO("NDEF file content is not present \r\n");
    }
    NRF_LOG_RAW_INFO("\r\n");
}


#endif // NFC_T4T_TLV_BLOCK_PARSER_ENABLED

