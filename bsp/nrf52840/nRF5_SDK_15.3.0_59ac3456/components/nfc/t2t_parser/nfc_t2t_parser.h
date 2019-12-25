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
#ifndef NFC_TYPE_2_TAG_PARSER_H__
#define NFC_TYPE_2_TAG_PARSER_H__

#include <stdint.h>
#include "nfc_tlv_block.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nfc_type_2_tag Type 2 Tag
 * @{
 * @ingroup  nfc_type_2_tag_parser
 *
 * @brief Descriptor for a Type 2 Tag.
 *
 */

/**
 * @brief Descriptor for the internal bytes of a Type 2 Tag.
 */
typedef struct
{
    uint8_t     manufacturer_id;        ///< Manufacturer ID (the most significant byte of the UID/serial number).
    uint16_t    serial_number_part_1;   ///< Bytes 5-4 of the tag UID.
    uint8_t     check_byte_0;           ///< First block check character byte (XOR of the cascade tag byte, manufacturer ID byte, and the serial_number_part_1 bytes).
    uint32_t    serial_number_part_2;   ///< Bytes 3-0 of the tag UID.
    uint8_t     check_byte_1;           ///< Second block check character byte (XOR of the serial_number_part_2 bytes).
    uint8_t     internal;               ///< Tag internal bytes.
} type_2_tag_serial_number_t;

/**
 * @brief Descriptor for the Capability Container (CC) bytes of a Type 2 Tag.
 */
typedef struct
{
    uint8_t     major_version;      ///< Major version of the supported Type 2 Tag specification.
    uint8_t     minor_version;      ///< Minor version of the supported Type 2 Tag specification.
    uint16_t    data_area_size;     ///< Size of the data area in bytes.
    uint8_t     read_access;        ///< Read access for the data area.
    uint8_t     write_access;       ///< Write access for the data area.
} type_2_tag_capability_container_t;

/**
 * @brief Type 2 Tag descriptor.
 */
typedef struct
{
    type_2_tag_serial_number_t          sn;                 ///< Values within the serial number area of the tag.
    uint16_t                            lock_bytes;         ///< Value of the lock bytes.
    type_2_tag_capability_container_t   cc;                 ///< Values within the Capability Container area of the tag.

    uint16_t                      const max_tlv_blocks;     ///< Maximum number of TLV blocks that can be stored.
    tlv_block_t                       * p_tlv_block_array;  ///< Pointer to the array for TLV blocks.
    uint16_t                            tlv_count;          ///< Number of TLV blocks stored in the Type 2 Tag.

} type_2_tag_t;

/**
 * @brief Macro for creating and initializing a Type 2 Tag descriptor.
 *
 * This macro creates and initializes a static instance of a @ref type_2_tag_t structure and
 * an array of @ref tlv_block_t descriptors.
 *
 * Use the macro @ref NFC_TYPE_2_TAG_DESC to access the Type 2 Tag descriptor instance.
 *
 * @param[in] NAME          Name of the created descriptor instance.
 * @param[in] MAX_BLOCKS    Maximum number of @ref tlv_block_t descriptors that can be stored in the array.
 *
 */
#define NFC_TYPE_2_TAG_DESC_DEF(NAME, MAX_BLOCKS)           \
    static tlv_block_t  NAME##_tlv_block_array[MAX_BLOCKS]; \
    static type_2_tag_t NAME##_type_2_tag =                 \
    {                                                       \
        .max_tlv_blocks = MAX_BLOCKS,                       \
        .p_tlv_block_array = NAME##_tlv_block_array,        \
        .tlv_count = 0                                      \
    }

/**
 * @brief Macro for accessing the @ref type_2_tag_t instance that was created
 *        with @ref NFC_TYPE_2_TAG_DESC_DEF.
 */
#define NFC_TYPE_2_TAG_DESC(NAME) (NAME##_type_2_tag)


#define T2T_NFC_FORUM_DEFINED_DATA      0xE1 ///< Value indicating that the Type 2 Tag contains NFC Forum defined data.
#define T2T_UID_BCC_CASCADE_BYTE        0x88 ///< Value used for calculating the first BCC byte of a Type 2 Tag serial number.

#define T2T_SUPPORTED_MAJOR_VERSION     1    ///< Supported major version of the Type 2 Tag specification.
#define T2T_SUPPORTED_MINOR_VERSION     2    ///< Supported minor version of the Type 2 Tag specification.

#define T2T_BLOCK_SIZE                  4   ///< Type 2 Tag block size in bytes.

#define T2T_CC_BLOCK_OFFSET             12  ///< Offset of the Capability Container area in the Type 2 Tag.
#define T2T_FIRST_DATA_BLOCK_OFFSET     16  ///< Offset of the data area in the Type 2 Tag.

/**
 * @}
 */


/**
 * @defgroup nfc_type_2_tag_parser NFC Type 2 Tag parser
 * @{
 * @ingroup  nfc_t2t
 *
 * @brief Parser for Type 2 Tag data.
 *
 */

/**
 * @brief Function for clearing the @ref type_2_tag_t structure.
 *
 * @param[in,out] p_type_2_tag Pointer to the structure that should be cleared.
 *
 */
void type_2_tag_clear(type_2_tag_t * p_type_2_tag);

/**
 * @brief Function for parsing raw data read from a Type 2 Tag.
 *
 * This function parses the header and the following TLV blocks of a Type 2 Tag. The data is read
 * from a buffer and stored in a @ref type_2_tag_t structure.
 *
 * @param[out] p_type_2_tag     Pointer to the structure that will be filled with parsed data.
 * @param[in]  p_raw_data       Pointer to the buffer with raw data from the tag (should
 *                              point at the first byte of the first block of the tag).
 *
 * @retval     NRF_SUCCESS      If the data was parsed successfully.
 * @retval     NRF_ERROR_NO_MEM If there is not enough memory to store all of the TLV blocks.
 * @retval     Other            If an error occurred during the parsing operation.
 *
 */
ret_code_t type_2_tag_parse(type_2_tag_t * p_type_2_tag, uint8_t * p_raw_data);

/**
 * @brief Function for printing parsed contents of the Type 2 Tag.
 *
 * @param[in] p_type_2_tag Pointer to the structure that should be printed.
 *
 */
void type_2_tag_printout(type_2_tag_t * p_type_2_tag);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* NFC_TYPE_2_TAG_PARSER_H__ */
