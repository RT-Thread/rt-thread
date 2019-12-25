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
#include <stdint.h>
#include <string.h>
#include "lwm2m_tlv.h"
#include "lwm2m_objects.h"
#include "iot_errors.h"
#include "iot_defines.h"

// Used for encoding
// TODO: Remove this temp_buffer in order to allow to users to use the API at the same time.
//       Current implementation might fail if two different interrupt levels are executing
//       encode at the same time. The temp_buffer will be overwritten by the last user.
static uint8_t temp_buffer[4];


uint32_t lwm2m_tlv_bytebuffer_to_uint32(uint8_t * p_buffer, uint8_t val_len, uint32_t * p_result)
{
    uint32_t res;
    switch (val_len)
    {
        case 0:
        {
            res = 0;
            break;
        }

        case 1:
        {
            res = p_buffer[0];
            break;
        }

        case 2:
        {
            res = ((uint32_t)p_buffer[0] << 8)  |
                  p_buffer[1];
            break;
        }

        case 3:
        {
            res = ((uint32_t)p_buffer[0] << 16) |
                  ((uint32_t)p_buffer[1] << 8)  |
                  p_buffer[2];
            break;
        }

        case 4:
        {
            res = ((uint32_t)p_buffer[0] << 24) |
                  ((uint32_t)p_buffer[1] << 16) |
                  ((uint32_t)p_buffer[2] << 8)  |
                  p_buffer[3];
            break;
        }

        default:
            return NRF_ERROR_DATA_SIZE;
    }

    *p_result = res;
    return NRF_SUCCESS;
}


uint32_t lwm2m_tlv_bytebuffer_to_uint16(uint8_t * p_buffer, uint8_t val_len, uint16_t * p_result)
{
    uint16_t res;
    switch (val_len)
    {
        case 0:
        {
            res = 0;
            break;
        }

        case 1:
        {
            res = p_buffer[0];
            break;
        }

        case 2:
        {
            res = ((uint16_t)p_buffer[0] << 8) | p_buffer[1];
            break;
        }

        default:
            return NRF_ERROR_DATA_SIZE;
    }

    *p_result = res;
    return NRF_SUCCESS;
}


void lwm2m_tlv_uint16_to_bytebuffer(uint8_t * p_buffer, uint8_t * p_len, uint16_t value)
{
    if (value == 0)
    {
        *p_len = 0;
    }
    else if (value <= UINT8_MAX)
    {
        p_buffer[0] = value;
        *p_len  = 1;
    }
    else
    {

        p_buffer[1] = value;
        p_buffer[0] = value >> 8;
        *p_len  = 2;
    }
}


void lwm2m_tlv_uint32_to_bytebuffer(uint8_t * p_buffer, uint8_t * p_len, uint32_t value)
{
    if (value == 0)
    {
        *p_len = 0;
    }
    else if (value <= UINT8_MAX)
    {
        p_buffer[0] = value;
        *p_len  = 1;
    }
    else if (value <= UINT16_MAX)
    {

        p_buffer[1] = value;
        p_buffer[0] = value >> 8;
        *p_len  = 2;
    }
    else if (value <= 0xFFFFFF)   // 24 bit
    {
        p_buffer[2] = value;
        p_buffer[1] = value >> 8;
        p_buffer[0] = value >> 16;
        *p_len  = 3;
    }
    else
    {
        p_buffer[3] = value;
        p_buffer[2] = value >> 8;
        p_buffer[1] = value >> 16;
        p_buffer[0] = value >> 24;
        *p_len  = 4;
    }
}


void lwm2m_tlv_uint16_set(lwm2m_tlv_t * p_tlv, uint16_t value, uint16_t id)
{
    uint8_t val_len;
    lwm2m_tlv_uint16_to_bytebuffer(temp_buffer, &val_len, value);

    p_tlv->length = val_len;
    p_tlv->value  = temp_buffer;
    p_tlv->id     = id;
}


void lwm2m_tlv_uint32_set(lwm2m_tlv_t * p_tlv, uint32_t value, uint16_t id)
{
    uint8_t val_len;
    lwm2m_tlv_uint32_to_bytebuffer(temp_buffer, &val_len, value);

    p_tlv->length = val_len;
    p_tlv->value  = temp_buffer;
    p_tlv->id     = id;
}


void lwm2m_tlv_bool_set(lwm2m_tlv_t * p_tlv, bool value, uint16_t id)
{

    if (value == true)
    {
        temp_buffer[0] = 1;
    }
    else
    {
        temp_buffer[0] = 0;
    }

    p_tlv->length = 1;
    p_tlv->value  = temp_buffer;
    p_tlv->id     = id;
}


void lwm2m_tlv_string_set(lwm2m_tlv_t * p_tlv, lwm2m_string_t string, uint16_t id)
{
    p_tlv->length = string.len;
    p_tlv->value  = (uint8_t *)string.p_val;
    p_tlv->id     = id;
}


void lwm2m_tlv_opaque_set(lwm2m_tlv_t * p_tlv, lwm2m_opaque_t opaque, uint16_t id)
{
    p_tlv->length = opaque.len;
    p_tlv->value  = opaque.p_val;
    p_tlv->id     = id;
}


uint32_t lwm2m_tlv_decode(lwm2m_tlv_t * p_tlv,
                          uint32_t *    p_index,
                          uint8_t *     p_buffer,
                          uint16_t      buffer_len)
{
    uint32_t err_code;
    uint16_t index = *p_index;

    uint8_t  type       = (p_buffer[index] & TLV_TYPE_MASK) >> TLV_TYPE_BIT_POS;
    uint8_t  id_len     = (p_buffer[index] & TLV_ID_LEN_MASK) >> TLV_ID_LEN_BIT_POS;
    uint8_t  length_len = (p_buffer[index] & TLV_LEN_TYPE_MASK) >> TLV_LEN_TYPE_BIT_POS;
    uint32_t length     = (p_buffer[index] & TLV_LEN_VAL_MASK) >> TLV_VAL_LEN_BIT_POS;

    p_tlv->id_type      = type;
    p_tlv->length       = 0;

    // Jump to the byte following the "Type" at index 0.
    ++index;

    // Extract the Identifier based on the number of bytes indicated in id_len (bit 5).
    // Adding one to the id_len will give the number of bytes used.
    uint8_t id_len_size = id_len + 1;

    err_code = lwm2m_tlv_bytebuffer_to_uint16(&p_buffer[index], id_len_size, &p_tlv->id);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    index     += id_len_size;


    // Extract the value length.
    // The length_len tells how many bytes are being used.
    if (length_len == TLV_LEN_TYPE_3BIT)
    {
        p_tlv->length = length;
    }
    else
    {
        err_code = lwm2m_tlv_bytebuffer_to_uint32(&p_buffer[index], length_len, &length);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        p_tlv->length = length;
        index += length_len;
    }

    if (p_tlv->length > buffer_len)
    {
        return (IOT_LWM2M_ERR_BASE | NRF_ERROR_INVALID_DATA);
    }

    p_tlv->value = &p_buffer[index];

    *p_index = index + p_tlv->length;

    return NRF_SUCCESS;
}


uint32_t lwm2m_tlv_encode(uint8_t * p_buffer, uint32_t * buffer_len, lwm2m_tlv_t * p_tlv)
{
    uint8_t length_len;
    uint8_t id_len;

    uint8_t  id[2]  = {0,};
    uint8_t  len[3] = {0,};
    uint16_t index  = 0;
    uint8_t  type   = 0;

    // Set Identifier type by copying the lwm2m_tlv_t->id_type into bit 7-6.
    type = (p_tlv->id_type << TLV_TYPE_BIT_POS);

    // Set length of Identifier in bit 5 in the TLV type byte.
    if (p_tlv->id > UINT8_MAX)
    {
        type   |= (TLV_ID_LEN_16BIT << TLV_ID_LEN_BIT_POS);
        id[0]   = p_tlv->id >> 8;
        id[1]   = p_tlv->id;
        id_len  = 2;
    }
    else
    {
        type   |= (TLV_ID_LEN_8BIT << TLV_ID_LEN_BIT_POS);
        id[0]   = p_tlv->id;
        id_len  = 1;
    }

    // Set type of Length bit 4-3 in the TLV type byte.

    // If the Length can fit into 3 bits.
    if ((p_tlv->length & TLV_LEN_VAL_MASK) == p_tlv->length)
    {
        type       |= (TLV_LEN_TYPE_3BIT << TLV_LEN_TYPE_BIT_POS);
        length_len  = 0;

        // As Length type field is set to "No Length", set bit 2-0.
        type |= (p_tlv->length & TLV_LEN_VAL_MASK);
    }
    else
    {
        lwm2m_tlv_uint32_to_bytebuffer(&len[0], &length_len, p_tlv->length);

        // Length can not be larger than 24-bit.
        if (length_len > TLV_LEN_TYPE_24BIT)
        {
            return (IOT_LWM2M_ERR_BASE | NRF_ERROR_INVALID_PARAM);
        }

        type |= (length_len << TLV_LEN_TYPE_BIT_POS);
    }

    // Check if the buffer is large enough.
    if (*buffer_len < (p_tlv->length + id_len + length_len + 1)) // + 1 for the type byte
    {
        return (IOT_LWM2M_ERR_BASE | NRF_ERROR_DATA_SIZE);
    }

    // Copy the type to the buffer.
    memcpy(p_buffer + index, &type, 1);
    ++index;

    // Copy the Identifier to the buffer.
    memcpy(p_buffer + index, id, id_len);
    index += id_len;

    // Copy length to the buffer.
    if (length_len != 0)
    {
        memcpy(p_buffer + index, len, length_len);
        index += length_len;
    }

    // Copy the value to buffer, memcpy of 0 length is undefined behavior so lets avoid it.
    if (p_tlv->length > 0)
    {
        memcpy(p_buffer + index, p_tlv->value, p_tlv->length);
    }

    // Set length of the output buffer.
    *buffer_len = p_tlv->length + index;

    return NRF_SUCCESS;
}




