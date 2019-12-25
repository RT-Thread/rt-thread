/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_CRYPTO)

#include "nrf_crypto_error.h"
#include "sdk_config.h"
#include "nrf_crypto_types.h"


ret_code_t padding_pkcs7_add(uint8_t * p_padding_buff,
                             uint8_t * p_message_buff,
                             uint8_t   msg_ending_len)
{
    uint8_t padding_count;

    if ((p_padding_buff == NULL) || (p_message_buff == NULL))
    {
        return NRF_ERROR_CRYPTO_INPUT_NULL;
    }

    if (msg_ending_len >= NRF_CRYPTO_AES_BLOCK_SIZE)
    {
        return NRF_ERROR_CRYPTO_INVALID_PARAM;
    }

    /* Creating padding buffer in two steps */
    /* step 1 add remaining message */
    memcpy(p_padding_buff, p_message_buff, msg_ending_len);

    /* step 2: add padding */
    padding_count   = NRF_CRYPTO_AES_BLOCK_SIZE - msg_ending_len;
    p_padding_buff += msg_ending_len;

    for (size_t i = 0; i < padding_count; i++)
    {
        p_padding_buff[i] = padding_count;
    }

    return NRF_SUCCESS;
}

ret_code_t padding_pkcs7_remove(uint8_t * p_padded_message,
                                size_t  * p_message_len)
{
    if (p_padded_message == NULL)
    {
        return NRF_ERROR_CRYPTO_INPUT_NULL;
    }
    if (p_message_len == NULL)
    {
        return NRF_ERROR_CRYPTO_OUTPUT_NULL;
    }

    /* padded_msg_len must be multiple of 16 */
    if ((*p_message_len == 0) || ((*p_message_len & 0x0F) != 0))
    {
        return NRF_ERROR_CRYPTO_INVALID_PARAM;
    }

    size_t padded_bytes = p_padded_message[*p_message_len - 1];

    if ((padded_bytes == 0) || (padded_bytes > NRF_CRYPTO_AES_BLOCK_SIZE))
    {
        return NRF_ERROR_CRYPTO_AES_INVALID_PADDING;
    }

    /* i = 2: 1 for valid string and 1 for already checked *p_message_len - 1 */
    for (size_t i = 2; i < padded_bytes; i++)
    {
        if (p_padded_message[*p_message_len - i] != padded_bytes)
        {
            return NRF_ERROR_CRYPTO_AES_INVALID_PADDING;
        }
    }

    *p_message_len -= padded_bytes;

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO)

