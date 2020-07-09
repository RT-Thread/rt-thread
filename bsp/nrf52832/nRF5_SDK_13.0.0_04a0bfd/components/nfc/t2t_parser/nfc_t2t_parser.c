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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NFC_T2T_PARSER)

#include <string.h>
#include <stdbool.h>
#include "nrf_delay.h"
#include "nfc_t2t_parser.h"

#define NRF_LOG_MODULE_NAME "NFC_T2T_PARSER"
#if NFC_T2T_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_T2T_PARSER_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_T2T_PARSER_INFO_COLOR
#else // NFC_T2T_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // NFC_T2T_PARSER_LOG_ENABLED
#include "nrf_log.h"

/// Gets least significant nibble (a 4-bit value) from a byte.
#define LSN_GET(val) (val & 0x0F)

/// Gets most significant nibble (a 4-bit value) from a byte.
#define MSN_GET(val) ((val >> 4) & 0x0F)

/**
 * @brief Function for inserting the TLV block into a @ref type_2_tag_t structure.
 *
 * The content of a TLV block structure pointed by the p_tlv_block is copied into a TLV block
 * array within the structure pointed by the p_type_2_tag.
 *
 * @param[in,out] p_type_2_tag Pointer to the structure that contains the TLV blocks array.
 * @param[in]     p_tlv_block  Pointer to the TLV block to insert.
 *
 * @retval        NRF_SUCCESS       If the block was inserted successfully.
 * @retval        NRF_ERROR_NO_MEM  If there is already maximum number of blocks stored in the array.
 *
 */
static ret_code_t type_2_tag_tlv_block_insert(type_2_tag_t * p_type_2_tag,
                                              tlv_block_t  * p_tlv_block)
{
    if (p_type_2_tag->tlv_count == p_type_2_tag->max_tlv_blocks)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Copy contents of the source block.
    p_type_2_tag->p_tlv_block_array[p_type_2_tag->tlv_count] = *p_tlv_block;
    p_type_2_tag->tlv_count++;

    return NRF_SUCCESS;
}


/**
 * @brief Function for checking if the TLV block length is correct.
 *
 * Some TLV block has predefined length:
 * TLV_NULL and TLV_TERMINATOR always have a length of 1 byte.
 * TLV_LOCK_CONTROL and TLV_MEMORY_CONTROL always have a length of 3 bytes.
 *
 * @param[in]     p_block_to_check Pointer to the structure that contains the TLV block length.
 *
 * @retval        TRUE   If the length is correct.
 * @retval        FALSE  Otherwise.
 *
 */
static bool tlv_block_is_data_length_correct(tlv_block_t * p_block_to_check)
{
    switch (p_block_to_check->tag)
    {
        case TLV_NULL:
        case TLV_TERMINATOR:
            if (p_block_to_check->length != TLV_NULL_TERMINATOR_LEN)
            {
                return false;
            }
            break;

        case TLV_LOCK_CONTROL:
        case TLV_MEMORY_CONTROL:
            if (p_block_to_check->length != TLV_LOCK_MEMORY_CTRL_LEN)
            {
                return false;
            }
            break;

        case TLV_NDEF_MESSAGE:
        case TLV_PROPRIETARY:
        default:
            // Any length will do.
            break;
    }

    return true;
}

/**
 * @brief Function for checking if the end of the tag data area was reached.
 *
 * @param[in]     p_type_2_tag  Pointer to the structure that contains the data area size.
 * @param[in]     offset        Current byte offset.
 *
 * @retval        TRUE          If the offset indicates the end of the data area.
 * @retval        FALSE         Otherwise.
 *
 */
static bool type_2_tag_is_end_reached(type_2_tag_t * p_type_2_tag, uint16_t offset)
{
    return offset == (p_type_2_tag->cc.data_area_size + T2T_FIRST_DATA_BLOCK_OFFSET);
}


/**
 * @brief Function for checking if version of Type 2 Tag specification read from a tag is supported.
 *
 * @param[in]     p_type_2_tag  Pointer to the structure that contains the tag version.
 *
 * @retval        TRUE          If the version is supported and tag data can be parsed.
 * @retval        FALSE         Otherwise.
 *
 */
static bool type_2_tag_is_version_supported(type_2_tag_t * p_type_2_tag)
{
    // Simple check atm, as only 1 major version has been issued so far, so no backward compatibility
    // is needed, tags with newer version implemented shall be rejected according to the doc.
    return p_type_2_tag->cc.major_version == T2T_SUPPORTED_MAJOR_VERSION;
}


/**
 * @brief Function for checking if the field fits into the data area specified in
 *        the Capability Container.
 *
 * @param[in]     p_type_2_tag  Pointer to the structure that contains the data area size.
 * @param[in]     offset As     Offset of the field to check.
 * @param[in]     field_length  Length of the field to check.
 *
 * @retval        TRUE          If the field fits into the data area.
 * @retval        FALSE         If the field exceeds the data area.
 *
 */
static bool type_2_tag_is_field_within_data_range(type_2_tag_t * p_type_2_tag,
                                                  uint16_t       offset,
                                                  uint16_t       field_length)
{
    // Invalid argument, return false.
    if (field_length == 0)
    {
        return false;
    }
    return     ( (offset + field_length - 1) <
                 (p_type_2_tag->cc.data_area_size + T2T_FIRST_DATA_BLOCK_OFFSET) )
            && ( offset >= T2T_FIRST_DATA_BLOCK_OFFSET );
}


/**
 * @brief Function for reading the tag field of a TLV block from the p_raw_data buffer.
 *
 * This function reads the tag field containing a TLV block type and inserts its value into
 * a structure pointed by the p_tlv_buf pointer.
 *
 * @param[in]     p_type_2_tag Pointer to the structure that contains Type 2 Tag data parsed so far.
 * @param[in]     p_raw_data   Pointer to the buffer with a raw data from the tag.
 * @param[in,out] p_t_offset As input: offset of the tag field to read. As output: offset of
 *                             the first byte after the tag field.
 * @param[out]    p_tlv_buf    Pointer to a @ref tlv_block_t structure where the tag type will be
 *                             inserted.
 *
 * @retval        NRF_SUCCESS             If the tag field at specified offset is correct.
 * @retval        NRF_ERROR_INVALID_DATA  If the tag field at specified offset exceeds the data
 *                                        area specified in the Capability Container.
 *
 */
static ret_code_t type_2_tag_type_extract(type_2_tag_t * p_type_2_tag,
                                          uint8_t      * p_raw_data,
                                          uint16_t     * p_t_offset,
                                          tlv_block_t  * p_tlv_buf)
{
    if (!type_2_tag_is_field_within_data_range(p_type_2_tag, *p_t_offset, TLV_T_LENGTH))
    {
        return NRF_ERROR_INVALID_DATA;
    }

    p_tlv_buf->tag = p_raw_data[*p_t_offset];
    *p_t_offset   += TLV_T_LENGTH;

    return NRF_SUCCESS;
}


/**
 * @brief Function for reading the length field of a TLV block from the p_raw_data buffer.
 *
 * This function reads the length field of a TLV block and inserts its value into a structure
 * pointed by the p_tlv_buf pointer.
 *
 * @param[in]     p_type_2_tag Pointer to the structure that contains Type 2 Tag data parsed so far.
 * @param[in]     p_raw_data   Pointer to the buffer with a raw data from the tag.
 * @param[in,out] p_l_offset As input: offset of the length field to read. As output: offset of
 *                             the first byte after the length field.
 * @param[out]    p_tlv_buf    Pointer to a @ref tlv_block_t structure where the length will be
 *                             inserted.
 *
 * @retval        NRF_SUCCESS             If the length field at specified offset is correct.
 * @retval        NRF_ERROR_INVALID_DATA  If the length field at specified offset exceeds the data
 *                                        area specified in the Capability Container or has
 *                                        incorrect format.
 *
 */
static ret_code_t type_2_tag_length_extract(type_2_tag_t * p_type_2_tag,
                                            uint8_t      * p_raw_data,
                                            uint16_t     * p_l_offset,
                                            tlv_block_t  * p_tlv_buf)
{
    uint16_t length;

    if (!type_2_tag_is_field_within_data_range(p_type_2_tag, *p_l_offset, TLV_L_SHORT_LENGTH))
    {
        return NRF_ERROR_INVALID_DATA;
    }

    length = p_raw_data[*p_l_offset];

    if (length == TLV_L_FORMAT_FLAG)
    {
        // Check another two bytes.
        if (!type_2_tag_is_field_within_data_range(p_type_2_tag, *p_l_offset, TLV_L_LONG_LENGTH))
        {
            return NRF_ERROR_INVALID_DATA;
        }

        length = uint16_big_decode(&p_raw_data[*p_l_offset + 1]);

        // Long length value cannot be lower than 0xFF.
        if (length < 0xFF)
        {
            return NRF_ERROR_INVALID_DATA;
        }

        p_tlv_buf->length = length;
        *p_l_offset += TLV_L_LONG_LENGTH;

    }
    else
    {
        p_tlv_buf->length = length;
        *p_l_offset += TLV_L_SHORT_LENGTH;
    }

    return NRF_SUCCESS;
}


/**
 * @brief Function for reading a pointer to the value field of a TLV block from the p_raw_data buffer.
 *
 * This function reads a pointer to the value field of a TLV block and inserts it into
 * a structure pointed by the p_tlv_buf pointer. If there is no value field present in the
 * TLV block, NULL is inserted.
 *
 * @param[in]     p_type_2_tag Pointer to the structure that contains Type 2 Tag data parsed so far.
 * @param[in]     p_raw_data   Pointer to the buffer with a raw data from the tag.
 * @param[in,out] p_v_offset As input: offset of the value field to read. As output: offset of
 *                             the first byte after the value field.
 * @param[in,out] p_tlv_buf    Pointer to a @ref tlv_block_t structure where the value field
 *                             pointer will be inserted.
 *
 * @retval        NRF_SUCCESS               If the value field at specified offset is correct.
 * @retval        NRF_ERROR_INVALID_DATA    If the value field at specified offset exceeds the data
 *                                          area specified in the Capability Container.
 *
 */
static ret_code_t type_2_tag_value_ptr_extract(type_2_tag_t * p_type_2_tag,
                                               uint8_t      * p_raw_data,
                                               uint16_t     * p_v_offset,
                                               tlv_block_t  * p_tlv_buf)
{
    if (p_tlv_buf->length == 0)
    {
        // Clear the value pointer, don't touch the offset.
        p_tlv_buf->p_value = NULL;
    }
    else
    {
        if (!type_2_tag_is_field_within_data_range(p_type_2_tag, *p_v_offset, p_tlv_buf->length))
        {
            return NRF_ERROR_INVALID_DATA;
        }

        p_tlv_buf->p_value = p_raw_data + *p_v_offset;
        *p_v_offset += p_tlv_buf->length;
    }

    return NRF_SUCCESS;
}


/**
 * @brief Function for reading a single TLV block from the p_raw_data buffer.
 *
 * This function reads a single TLV block from the p_raw_data buffer and stores its contents in a
 * structure pointed by the p_tlv_buf.
 *
 * @param[in]     p_type_2_tag Pointer to the structure that contains Type 2 Tag data parsed so far.
 * @param[in]     p_raw_data   Pointer to the buffer with a raw data from the tag.
 * @param[in,out] p_tlv_offset As input: offset of the TLV block to read. As output: offset of the
 *                             next TLV block, 0 if it was the last block.
 * @param[out]    p_tlv_buf    Pointer to a @ref tlv_block_t structure that will be filled with
 *                             the data read.
 *
 * @retval        NRF_SUCCESS  If the parsing operation of the block succeeded. Otherwise, an error
 *                             code is returned.
 *
 */
static ret_code_t type_2_tag_tlv_block_extract(type_2_tag_t * p_type_2_tag,
                                               uint8_t      * p_raw_data,
                                               uint16_t     * p_offset,
                                               tlv_block_t  * p_tlv_buf)
{
    ret_code_t err_code;
    memset(p_tlv_buf, 0, sizeof(tlv_block_t));

    // TLV Tag field.
    err_code = type_2_tag_type_extract(p_type_2_tag, p_raw_data, p_offset, p_tlv_buf);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Further processing depends on tag field value.
    switch (p_tlv_buf->tag)
    {
        case TLV_NULL:
            // Simply ignore NULL blocks, leave the incremented offset.
            break;

        case TLV_TERMINATOR:
            // Write 0 to the offset variable, indicating that last TLV block was found.
            *p_offset = 0;
            break;

        case TLV_LOCK_CONTROL:
        case TLV_MEMORY_CONTROL:
        case TLV_NDEF_MESSAGE:
        case TLV_PROPRIETARY:
        default:
            // Unknown blocks should also be extracted.
            err_code = type_2_tag_length_extract(p_type_2_tag, p_raw_data, p_offset, p_tlv_buf);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }

            if (p_tlv_buf->length > 0)
            {
                err_code = type_2_tag_value_ptr_extract(p_type_2_tag, p_raw_data, p_offset, p_tlv_buf);
                if (err_code != NRF_SUCCESS)
                {
                    return err_code;
                }
            }

            break;
    }

    return NRF_SUCCESS;
}


/**
 * @brief Function for checking the checksum bytes of the UID stored in internal area.
 *
 * This function calculates the block check character (BCC) bytes based on the parsed serial number
 * and compares them with bytes read from the Type 2 Tag.
 *
 * @param[in] p_sn Pointer to the @ref type_2_tag_serial_number_t structure to check.
 *
 * @retval  TRUE  If the calculated BCC matched the BCC from the tag.
 * @retval  FALSE Otherwise.
 *
 */
static bool type_2_tag_is_bcc_correct(type_2_tag_serial_number_t * p_sn)
{
    uint8_t bcc1 = (uint8_t)T2T_UID_BCC_CASCADE_BYTE                    ^
                   (uint8_t)p_sn->manufacturer_id                       ^
                   (uint8_t)((p_sn->serial_number_part_1 >> 8) & 0xFF)  ^
                   (uint8_t)(p_sn->serial_number_part_1 & 0xFF);

    uint8_t bcc2 = (uint8_t)((p_sn->serial_number_part_2 >> 24) & 0xFF) ^
                   (uint8_t)((p_sn->serial_number_part_2 >> 16) & 0xFF) ^
                   (uint8_t)((p_sn->serial_number_part_2 >>  8) & 0xFF) ^
                   (uint8_t)( p_sn->serial_number_part_2        & 0xFF);

    return (bcc1 == p_sn->check_byte_0) && (bcc2 == p_sn->check_byte_1);
}


/**
 * @brief Function for parsing an internal area of a Type 2 Tag.
 *
 * This function reads data from an internal area in the raw data buffer and fills the
 * @ref type_2_tag_serial_number_t structure within @ref type_2_tag_t.
 *
 * @param[in,out] p_type_2_tag Pointer to the structure that will be filled with parsed data.
 * @param[in]     p_raw_data   Pointer to the buffer with raw data from the tag.
 *
 * @retval        NRF_SUCCESS  If the parsing operation of the internal area succeeded.
 *                             Otherwise, an error code is returned.
 *
 */
static ret_code_t type_2_tag_internal_parse(type_2_tag_t * p_type_2_tag, uint8_t * p_raw_data)
{
    p_type_2_tag->sn.manufacturer_id      = p_raw_data[0];
    p_type_2_tag->sn.serial_number_part_1 = uint16_big_decode(&p_raw_data[1]);
    p_type_2_tag->sn.check_byte_0         = p_raw_data[3];
    p_type_2_tag->sn.serial_number_part_2 = uint32_big_decode(&p_raw_data[4]);
    p_type_2_tag->sn.check_byte_1         = p_raw_data[8];
    p_type_2_tag->sn.internal             = p_raw_data[9];

    p_type_2_tag->lock_bytes              = uint16_big_decode(&p_raw_data[10]);

    if (!type_2_tag_is_bcc_correct(&p_type_2_tag->sn))
    {
        NRF_LOG_WARNING("Warning! BCC of the serial number is not correct!\r\n");
    }

    return NRF_SUCCESS;
}


/**
 * @brief Function for parsing a Capabiliy Container area of a Type 2 Tag.
 *
 * This function reads data from a Capability Container area in the raw data buffer and fills the
 * @ref type_2_tag_capability_container_t structure within @ref type_2_tag_t.
 *
 * @param[in,out] p_type_2_tag Pointer to the structure that will be filled with parsed data.
 * @param[in]     p_raw_data   Pointer to the buffer with raw data from the tag.
 *
 * @retval        NRF_SUCCESS  If the parsing operation of the Capability Container succeeded.
 *                             Otherwise, an error code is returned.
 *
 */
static ret_code_t type_2_tag_cc_parse(type_2_tag_t * p_type_2_tag, uint8_t * p_raw_data)
{
    uint8_t * p_cc_block = p_raw_data + T2T_CC_BLOCK_OFFSET;

    if (p_cc_block[0] != T2T_NFC_FORUM_DEFINED_DATA)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    p_type_2_tag->cc.major_version  = MSN_GET(p_cc_block[1]);
    p_type_2_tag->cc.minor_version  = LSN_GET(p_cc_block[1]);
    p_type_2_tag->cc.data_area_size = p_cc_block[2] * 8;
    p_type_2_tag->cc.read_access    = MSN_GET(p_cc_block[3]);
    p_type_2_tag->cc.write_access   = LSN_GET(p_cc_block[3]);

    return NRF_SUCCESS;
}


/**
 * @brief Function for parsing a single TLV block.
 *
 * This function reads a single TLV block from the raw data buffer, from the position indicated by
 * the p_tlv_offset, and adds it to the @ref type_2_tag_t structure.
 *
 * @param[in,out] p_type_2_tag Pointer to the structure that will be filled with parsed data.
 * @param[in]     p_raw_data   Pointer to the buffer with raw data from the tag.
 * @param[in,out] p_tlv_offset As input: offset of the TLV block to parse. As output: offset of the
 *                             next TLV block, 0 if it was the last block.
 *
 * @retval        NRF_SUCCESS  If the parsing operation of the block succeeded. Otherwise, an error
 *                             code is returned.
 *
 */
static ret_code_t type_2_tag_tlv_parse(type_2_tag_t * p_type_2_tag,
                                       uint8_t      * p_raw_data,
                                       uint16_t     * p_tlv_offset)
{
    ret_code_t err_code;
    tlv_block_t new_block;

    // Get tag field.
    err_code = type_2_tag_tlv_block_extract(p_type_2_tag, p_raw_data, p_tlv_offset, &new_block);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (!tlv_block_is_data_length_correct(&new_block))
    {
        return NRF_ERROR_INVALID_DATA;
    }

    // Further action depends on tag type.
    switch (new_block.tag)
    {
        case TLV_NULL:
        case TLV_TERMINATOR:
            // Ignore them.
            break;

        case TLV_LOCK_CONTROL:
        case TLV_MEMORY_CONTROL:
        case TLV_NDEF_MESSAGE:
        case TLV_PROPRIETARY:
        default:
            // Unknown tag types are also added.
            err_code = type_2_tag_tlv_block_insert(p_type_2_tag, &new_block);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_WARNING("Warning! Not enough memory  to insert all of the blocks!\r\n");
                return err_code;
            }
            break;
    }

    return NRF_SUCCESS;
}


void type_2_tag_clear(type_2_tag_t * p_type_2_tag)
{
    p_type_2_tag->tlv_count = 0;
    memset(&p_type_2_tag->cc, 0, sizeof(p_type_2_tag->cc));
    memset(&p_type_2_tag->sn, 0, sizeof(p_type_2_tag->sn));
}


ret_code_t type_2_tag_parse(type_2_tag_t * p_type_2_tag, uint8_t * p_raw_data)
{
    ret_code_t err_code;

    type_2_tag_clear(p_type_2_tag);

    err_code = type_2_tag_internal_parse(p_type_2_tag, p_raw_data);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = type_2_tag_cc_parse(p_type_2_tag, p_raw_data);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (!type_2_tag_is_version_supported(p_type_2_tag))
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    uint16_t offset = T2T_FIRST_DATA_BLOCK_OFFSET;

    while (offset > 0)
    {
        // Check if end of tag is reached (no terminator block was present).
        if (type_2_tag_is_end_reached(p_type_2_tag, offset))
        {
            NRF_LOG_DEBUG("No terminator block was found in the tag!\r\n");
            break;
        }

        err_code = type_2_tag_tlv_parse(p_type_2_tag, p_raw_data, &offset);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    return NRF_SUCCESS;
}


void type_2_tag_printout(type_2_tag_t * p_type_2_tag)
{
    uint32_t i;
    NRF_LOG_INFO("Type 2 Tag contents:\r\n\r\n");
    NRF_LOG_INFO("Number of TLV blocks: %d\r\n\r\n", p_type_2_tag->tlv_count);

    NRF_LOG_INFO("Internal data:\r\n");
    NRF_LOG_INFO("    Manufacturer ID:      0x%02x\r\n",  p_type_2_tag->sn.manufacturer_id);
    NRF_LOG_INFO("    Serial number part 1: 0x%04x\r\n",  p_type_2_tag->sn.serial_number_part_1);
    NRF_LOG_INFO("    Check byte 0:         0x%02x\r\n",  p_type_2_tag->sn.check_byte_0);
    NRF_LOG_INFO("    Serial number part 2: 0x%08lx\r\n", p_type_2_tag->sn.serial_number_part_2);
    NRF_LOG_INFO("    Check byte 1:         0x%02x\r\n",  p_type_2_tag->sn.check_byte_1);
    NRF_LOG_INFO("    Internal byte:        0x%02x\r\n",  p_type_2_tag->sn.internal);
    NRF_LOG_INFO("    Lock bytes:           0x%04x\r\n\r\n",  p_type_2_tag->lock_bytes);

    NRF_LOG_INFO("Capability Container data:\r\n");
    NRF_LOG_INFO("    Major version number: %d\r\n", p_type_2_tag->cc.major_version);
    NRF_LOG_INFO("    Minor version number: %d\r\n", p_type_2_tag->cc.minor_version);
    NRF_LOG_INFO("    Data area size:       %d\r\n", p_type_2_tag->cc.data_area_size);
    NRF_LOG_INFO("    Read access:          0x%02X\r\n", p_type_2_tag->cc.read_access);
    NRF_LOG_INFO("    Write access:         0x%02X\r\n\r\n", p_type_2_tag->cc.write_access);

    for (i = 0; i < p_type_2_tag->tlv_count; i++)
    {
        NRF_LOG_INFO("TLV block 0x%02X: \r\n", p_type_2_tag->p_tlv_block_array[i].tag);
        switch (p_type_2_tag->p_tlv_block_array[i].tag)
        {
            case TLV_LOCK_CONTROL:
                NRF_LOG_INFO("Lock Control\r\n\r\n");
               break;
            case TLV_MEMORY_CONTROL:
                NRF_LOG_INFO("Memory Control\r\n\r\n");
               break;
            case TLV_NDEF_MESSAGE:
                NRF_LOG_INFO("NDEF Message\r\n\r\n");
               break;
            case TLV_PROPRIETARY:
                NRF_LOG_INFO("Proprietary\r\n\r\n");
               break;
            case TLV_NULL:
                NRF_LOG_INFO("Null\r\n\r\n");
               break;
            case TLV_TERMINATOR:
                NRF_LOG_INFO("Terminator\r\n\r\n");
               break;
            default:
                NRF_LOG_INFO("Unknown\r\n\r\n");
               break;
        }

        NRF_LOG_INFO("    Length: %d\r\n", p_type_2_tag->p_tlv_block_array[i].length);

        if (p_type_2_tag->p_tlv_block_array[i].length > 0)
        {
            NRF_LOG_INFO("    Data:\r\n");
            NRF_LOG_HEXDUMP_INFO(p_type_2_tag->p_tlv_block_array[i].p_value,
                                 p_type_2_tag->p_tlv_block_array[i].length);
        }
        NRF_LOG_INFO("\r\n\r\n");
    }
}

#endif // NRF_MODULE_ENABLED(NFC_T2T_PARSER)
