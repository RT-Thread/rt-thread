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
#ifndef NFC_TLV_BLOCK_H__
#define NFC_TLV_BLOCK_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@file
 *
 * @defgroup nfc_type_2_tag_tlv_block Type 2 Tag TLV blocks
 * @{
 * @ingroup  nfc_type_2_tag_parser
 *
 * @brief Descriptor for a Type 2 Tag TLV block.
 *
 */

/**
 * @brief Tag field values.
 *
 * Possible values for the tag field in a TLV block.
 */
typedef enum
{
    TLV_NULL            = 0x00, ///< Might be used for padding of memory areas.
    TLV_LOCK_CONTROL    = 0x01, ///< Defines details of the lock bits.
    TLV_MEMORY_CONTROL  = 0x02, ///< Identifies reserved memory areas.
    TLV_NDEF_MESSAGE    = 0x03, ///< Contains an NDEF message.
    TLV_PROPRIETARY     = 0xFD, ///< Tag proprietary information.
    TLV_TERMINATOR      = 0xFE  ///< Last TLV block in the data area.
} tlv_block_types_t;

/**
 * @brief TLV block descriptor.
 */
typedef struct
{
    uint8_t    tag;             ///< Type of the TLV block.
    uint16_t   length;          ///< Length of the value field.
    uint8_t  * p_value;         ///< Pointer to the value field (NULL if no value field is present in the block).
} tlv_block_t;

#define TLV_T_LENGTH        1           ///< Length of a tag field.

#define TLV_L_SHORT_LENGTH  1           ///< Length of a short length field.
#define TLV_L_LONG_LENGTH   3           ///< Length of an extended length field.
#define TLV_L_FORMAT_FLAG   0xFF        ///< Value indicating the use of an extended length field.

#define TLV_NULL_TERMINATOR_LEN     0   ///< Predefined length of the NULL and TERMINATOR TLV blocks.
#define TLV_LOCK_MEMORY_CTRL_LEN    3   ///< Predefined length of the LOCK CONTROL and MEMORY CONTROL blocks.

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* NFC_TLV_BLOCK_H__ */
