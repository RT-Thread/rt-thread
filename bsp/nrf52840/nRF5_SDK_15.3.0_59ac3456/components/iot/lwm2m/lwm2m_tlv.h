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
/** @file lwm2m_tlv.h
 *
 * @defgroup iot_sdk_lwm2m_tlv_api LWM2M TLV interface
 * @ingroup iot_sdk_lwm2m
 * @{
 * @brief TLV encoding and decoding interface for the LWM2M protocol.
 */

#ifndef LWM2M_TLV_H__
#define LWM2M_TLV_H__

#include <stdint.h>
#include "lwm2m_objects.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* TLV type masks
*/
#define TLV_TYPE_BIT_POS           6
#define TLV_ID_LEN_BIT_POS         5
#define TLV_LEN_TYPE_BIT_POS       3
#define TLV_VAL_LEN_BIT_POS        0

#define TLV_TYPE_MASK              (0x3 << TLV_TYPE_BIT_POS)     /**< Type bitmask, bit 7-6                (0b11000000). */
#define TLV_ID_LEN_MASK            (0x1 << TLV_ID_LEN_BIT_POS)   /**< Length bitmask, bit 5                (0b00100000). */
#define TLV_LEN_TYPE_MASK          (0x3 << TLV_LEN_TYPE_BIT_POS) /**< Length type bitmask, bit 4-3         (0b00011000). */
#define TLV_LEN_VAL_MASK           (0x7 << TLV_VAL_LEN_BIT_POS)  /**< Length of the value bitmask, bit 2-0 (0b00000111). */

#define TLV_TYPE_OBJECT            0x00
#define TLV_TYPE_RESOURCE_INSTANCE 0x01
#define TLV_TYPE_MULTI_RESOURCE    0x02
#define TLV_TYPE_RESOURCE_VAL      0x03

#define TLV_ID_LEN_8BIT            0x00
#define TLV_ID_LEN_16BIT           0x01

#define TLV_LEN_TYPE_3BIT          0x00
#define TLV_LEN_TYPE_8BIT          0x01
#define TLV_LEN_TYPE_16BIT         0x02
#define TLV_LEN_TYPE_24BIT         0x03

typedef struct
{
    uint16_t  id_type;             /**< Identifier type. */
    uint16_t  id;                  /**< Identifier ID. */
    uint32_t  length;              /**< Length of the value in the TLV. */
    uint8_t * value;               /**< Value of the TLV. */
} lwm2m_tlv_t;

/**@brief Decode a LWM2M TLV byte buffer into a TLV structure.
 *
 * @param[out]   p_tlv        This struct will be filled with id, length, type and pointer to value.
 * @param[inout] p_index      Index to start decoding from.
 * @param[in]    p_buffer     The buffer to decode from.
 * @param[in]    buffer_len   The length of the buffer.
 *
 * @retval NRF_SUCCESS If decoding was successful.
 * @retval IOT_LWM2M_ERR_BASE | NRF_INVALID_DATA
 */
uint32_t lwm2m_tlv_decode(lwm2m_tlv_t * p_tlv, uint32_t * p_index, uint8_t * p_buffer, uint16_t buffer_len);

/**@brief Encode a TLV structure into a LWM2M TLV byte buffer.
 *
 * @details Encode using the provided tlv, if the buffer provided is to small an NRF_ERROR_DATA_SIZE will be returned.
 *
 * Maximum buffer size requirement: value_length + 6 (1 for type byte, 2 for id bytes, 3 for length bytes).
 *
 * @param[out]   p_buffer    Buffer to put the encoded tlv into.
 * @param[inout] buffer_len  Length of input buffer out: length of the encoded buffer.
 * @param[in]    p_tlv       The tlv to use.
 *
 * @retval NRF_SUCCESS If decoding was successful.
 * @retval IOT_LWM2M_ERR_BASE | NRF_ERROR_DATA_SIZE
 */
uint32_t lwm2m_tlv_encode(uint8_t * p_buffer, uint32_t * p_buffer_len, lwm2m_tlv_t * p_tlv);

/**@brief Encode a byte buffer into a uint32_t.
 *
 * @param[in] p_buffer Buffer which holds a serialized version of the uint32_t.
 * @param[in] val_len  Length of the value in the buffer.
 * @param[out] p_result By reference pointer to the result uint32_t.
 *
 * @retval NRF_SUCCESS If the conversion from byte buffer to uint32_t value was successful.
 */
uint32_t lwm2m_tlv_bytebuffer_to_uint32(uint8_t * p_buffer, uint8_t val_len, uint32_t * p_result);

/**@brief Encode a byte buffer into a uint16_t.
 *
 * @param[in]  p_buffer Buffer which holds a serialized version of the uint16_t.
 * @param[in]  val_len  Length of the value in the buffer.
 * @param[out] p_result By reference pointer to the result uint16_t.
 *
 * @retval NRF_SUCCESS If the conversion from byte buffer to uint32_t value was successful.
 */
uint32_t lwm2m_tlv_bytebuffer_to_uint16(uint8_t * p_buffer, uint8_t val_len, uint16_t * p_result);

/**@brief Decode a uint32_t into a byte buffer.
 *
 * @param[out]   p_buffer Buffer which holds a serialized version of the uint32_t.
 * @param[out]   p_len  By reference pointer to hold the length of the serialized value in the buffer.
 * @param[in]    value  Value to convert serialize into a byte buffer.
 *
 * @retval NRF_SUCCESS If the conversion from uint32_t value to byte buffer was successful.
 */
void lwm2m_tlv_uint32_to_bytebuffer(uint8_t * p_buffer, uint8_t * p_len, uint32_t value);

/**@brief Decode a uint16_t into a byte buffer.
 *
 * @param[out]   p_buffer Buffer which holds a serialized version of the uint16_t.
 * @param[out]   p_len  By reference pointer to hold the length of the serialized value in the buffer.
 * @param[in]    value  Value to convert serialize into a byte buffer.
 *
 * @retval NRF_SUCCESS If the conversion from uint16_t value to byte buffer was successful.
 */
void lwm2m_tlv_uint16_to_bytebuffer(uint8_t * p_buffer, uint8_t * p_len, uint16_t value);

/**@brief Set a uint32_t value to a lwm2m_tlv_t structure.
 *
 * @param[out] p_tlv TLV containing the uint32_t tlv.
 * @param[in]  value Value to set.
 * @param[in]  id    Resource Id associated with the value.
 */
void lwm2m_tlv_uint32_set(lwm2m_tlv_t * p_tlv, uint32_t value, uint16_t id);


/**@brief Set a uint16_t value to a lwm2m_tlv_t structure.
 *
 * @param[out] p_tlv TLV containing the uint16_t tlv.
 * @param[in]  value Value to set.
 * @param[in]  id    Resource Id associated with the value.
 */
void lwm2m_tlv_uint16_set(lwm2m_tlv_t * p_tlv, uint16_t value, uint16_t id);


/**@brief Set a boolean value to a lwm2m_tlv_t structure.
 *
 * @param[out] p_tlv TLV containing the boolean tlv.
 * @param[in]  value Value to set.
 * @param[in]  id    Resource Id associated with the value.
 */
void lwm2m_tlv_bool_set(lwm2m_tlv_t * p_tlv, bool value, uint16_t id);

/**@brief Set a string value to a lwm2m_tlv_t structure.
 *
 * @param[out] p_tlv TLV containing the string tlv.
 * @param[in]  value Value to set.
 * @param[in]  id    Resource Id associated with the value.
 */
void lwm2m_tlv_string_set(lwm2m_tlv_t * p_tlv, lwm2m_string_t string, uint16_t id);

/**@brief Set a opaque value to a lwm2m_tlv_t structure.
 *
 * @param[out] p_tlv TLV containing the opaque tlv.
 * @param[in]  value Value to set.
 * @param[in]  id    Resource Id associated with the value.
 */
void lwm2m_tlv_opaque_set(lwm2m_tlv_t * p_tlv, lwm2m_opaque_t opaque, uint16_t id);

#ifdef __cplusplus
}
#endif

#endif // LWM2M_TLV_H__

/** @} */
