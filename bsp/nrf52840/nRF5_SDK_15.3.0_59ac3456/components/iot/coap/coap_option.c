/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#include <stdlib.h>
#include <string.h>

#include "coap_option.h"
#include "iot_common.h"

#if (COAP_DISABLE_API_PARAM_CHECK == 0)

#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);                                               \
    }

#else

#define NULL_PARAM_CHECK(PARAM)

#endif // COAP_DISABLE_API_PARAM_CHECK

uint32_t coap_opt_string_encode(uint8_t * p_encoded, uint16_t * p_length, uint8_t * p_string, uint16_t str_len)
{
    NULL_PARAM_CHECK(p_encoded);
    NULL_PARAM_CHECK(p_length);
    NULL_PARAM_CHECK(p_string);

    if (str_len > *p_length)
    {
        return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
    }

    memcpy(p_encoded, p_string, str_len);

    *p_length = str_len;

    return NRF_SUCCESS;
}

uint32_t coap_opt_string_decode(uint8_t * p_string, uint16_t * p_length, uint8_t * p_encoded)
{
    return NRF_SUCCESS;
}

uint32_t coap_opt_uint_encode(uint8_t * p_encoded, uint16_t * p_length, uint32_t data)
{
    NULL_PARAM_CHECK(p_encoded);
    NULL_PARAM_CHECK(p_length);

    uint16_t byte_index = 0;

    if (data <= UINT8_MAX)
    {
        if (*p_length < sizeof(uint8_t))
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }

        p_encoded[byte_index++] = (uint8_t)data;
    }
    else if (data <= UINT16_MAX)
    {
        if (*p_length < sizeof(uint16_t))
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }

        p_encoded[byte_index++] = (uint8_t)((data & 0xFF00) >> 8);
        p_encoded[byte_index++] = (uint8_t)(data & 0x00FF);
    }
    else
    {
        if (*p_length < sizeof(uint32_t))
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }

        p_encoded[byte_index++] = (uint8_t)((data & 0xFF000000) >> 24);
        p_encoded[byte_index++] = (uint8_t)((data & 0x00FF0000) >> 16);
        p_encoded[byte_index++] = (uint8_t)((data & 0x0000FF00) >> 8);
        p_encoded[byte_index++] = (uint8_t)(data & 0x000000FF);
    }



    *p_length = byte_index;

    return NRF_SUCCESS;
}

uint32_t coap_opt_uint_decode(uint32_t * p_data, uint16_t length, uint8_t * p_encoded)
{
    NULL_PARAM_CHECK(p_data);
    NULL_PARAM_CHECK(p_encoded);

    uint8_t byte_index = 0;
    switch (length)
    {
        case 0:
            {
                *p_data = 0;
            }
            break;

        case 1:
            {
                *p_data = 0;
                *p_data |= p_encoded[byte_index++];
            }
            break;

        case 2:
            {
                *p_data = 0;
                *p_data |= (p_encoded[byte_index++] << 8);
                *p_data |= (p_encoded[byte_index++]);
            }
            break;

        case 3:
            {
                *p_data = 0;
                *p_data |= (p_encoded[byte_index++] << 16);
                *p_data |= (p_encoded[byte_index++] << 8);
                *p_data |= (p_encoded[byte_index++]);
            }
            break;

        case 4:
            {
                *p_data = 0;
                *p_data |= (p_encoded[byte_index++] << 24);
                *p_data |= (p_encoded[byte_index++] << 16);
                *p_data |= (p_encoded[byte_index++] << 8);
                *p_data |= (p_encoded[byte_index++]);
            }
            break;

        default:
            return (NRF_ERROR_INVALID_LENGTH | IOT_COAP_ERR_BASE);
    }

    return NRF_SUCCESS;
}
