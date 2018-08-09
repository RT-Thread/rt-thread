/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#include <stdbool.h>
#include <stddef.h>

#include "coap_block.h"
#include "nrf_error.h"
#include "iot_errors.h"
#include "sdk_config.h"


/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          COAP_DISABLE_API_PARAM_CHECK should be defined to disable these checks.
 *
 * @{
 */
#if (COAP_DISABLE_API_PARAM_CHECK == 0)

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);                                               \
    }
#else // COAP_DISABLE_API_PARAM_CHECK

#define NULL_PARAM_CHECK(PARAM)

#endif // COAP_DISABLE_API_PARAM_CHECK
/** @} */


#define BLOCK_SIZE_BASE_CONSTANT  4                                        /**< Block size base exponent. 4 means a base block size of 2^4 = 16 bytes. */

#define BLOCK_SIZE_16             0                                        /**< Block size of 2^(4+0) = 16 bytes. */
#define BLOCK_SIZE_32             1                                        /**< Block size of 2^(4+1) = 32 bytes. */
#define BLOCK_SIZE_64             2                                        /**< Block size of 2^(4+2) = 64 bytes. */
#define BLOCK_SIZE_128            3                                        /**< Block size of 2^(4+3) = 128 bytes. */
#define BLOCK_SIZE_256            4                                        /**< Block size of 2^(4+4) = 256 bytes. */
#define BLOCK_SIZE_512            5                                        /**< Block size of 2^(4+5) = 512 bytes. */
#define BLOCK_SIZE_1024           6                                        /**< Block size of 2^(4+6) = 1024 bytes. */
#define BLOCK_SIZE_2048_RESERVED  7                                        /**< Reserved. */

#define BLOCK_MORE_BIT_UNSET      0                                        /**< Value when more flag is set. */
#define BLOCK_MORE_BIT_SET        1                                        /**< Value when more flag is not set. */

#define BLOCK_SIZE_POS            0                                        /**< Bit offset to the size. */
#define BLOCK_MORE_BIT_POS        3                                        /**< Bit offset to the more bit. */
#define BLOCK_NUMBER_POS          4                                        /**< Bit offset to the block number. */

#define BLOCK_SIZE_MASK           0x7                                      /**< Block size mask. */
#define BLOCK_MORE_BIT_MASK       (1 << BLOCK_MORE_BIT_POS)                /**< More bit mask. */
#define BLOCK_NUMBER_MASK         (0xFFFFF << 4)                           /**< Block number mask. */

#define BLOCK_SIZE_MAX            0x7                                      /**< Maximum block size number. */
#define BLOCK_MORE_BIT_MAX        BLOCK_MORE_BIT_SET                       /**< Maximum more bit value. */
#define BLOCK_NUMBER_MAX          0xFFFFF                                  /**< Maximum block number. 20 bits max value is (1 << 20) - 1. */

static uint32_t block_opt_encode(uint8_t    more,
		                         uint16_t   size,
		                         uint32_t   number,
		                         uint32_t * p_encoded)
{
    if ((number > BLOCK_NUMBER_MAX) || (more > BLOCK_MORE_BIT_MAX))
    {
        return (NRF_ERROR_INVALID_PARAM | IOT_COAP_ERR_BASE);
    }

    uint32_t val = 0;

    switch (size)
    {
        case 16:
            val = BLOCK_SIZE_16;
            break;

        case 32:
            val = BLOCK_SIZE_32;
            break;

        case 64:
            val = BLOCK_SIZE_64;
            break;

        case 128:
            val = BLOCK_SIZE_128;
            break;

        case 256:
            val = BLOCK_SIZE_256;
            break;

        case 512:
            val = BLOCK_SIZE_512;
            break;

        case 1024:
            val = BLOCK_SIZE_1024;
            break;

        case 2048:
            // Falltrough.
        default:
            // Break omitted.
            return (NRF_ERROR_INVALID_PARAM | IOT_COAP_ERR_BASE);
    }

    // Value has been initialized.
    val |= (more) << BLOCK_MORE_BIT_POS;
    val |= (number) << BLOCK_NUMBER_POS;

    *p_encoded = val;
    return NRF_SUCCESS;
}

static uint32_t block_opt_decode(uint32_t encoded,
		                         uint8_t  * p_more,
                                 uint16_t * p_size,
                                 uint32_t * p_number)
{
    if ((encoded & BLOCK_SIZE_MASK) == BLOCK_SIZE_2048_RESERVED)
    {
        return (NRF_ERROR_INVALID_DATA | IOT_COAP_ERR_BASE);
    }

    if ((encoded >> BLOCK_NUMBER_POS) > BLOCK_NUMBER_MAX)
    {
        return (NRF_ERROR_INVALID_PARAM | IOT_COAP_ERR_BASE);
    }

    *p_size   = (1 << ((BLOCK_SIZE_BASE_CONSTANT + (encoded & BLOCK_SIZE_MASK))));
    *p_more   = (encoded & BLOCK_MORE_BIT_MASK) >> BLOCK_MORE_BIT_POS;
    *p_number = (encoded & BLOCK_NUMBER_MASK) >> BLOCK_NUMBER_POS;

    return NRF_SUCCESS;
}

uint32_t coap_block_opt_block1_encode(uint32_t * p_encoded, coap_block_opt_block1_t * p_opt)
{
    NULL_PARAM_CHECK(p_encoded);
    NULL_PARAM_CHECK(p_opt);
    return block_opt_encode(p_opt->more, p_opt->size, p_opt->number, p_encoded);
}

uint32_t coap_block_opt_block1_decode(coap_block_opt_block1_t * p_opt, uint32_t encoded)
{
    NULL_PARAM_CHECK(p_opt);
    return block_opt_decode(encoded, &p_opt->more, &p_opt->size, &p_opt->number);
}

uint32_t coap_block_opt_block2_encode(uint32_t * p_encoded, coap_block_opt_block2_t * p_opt)
{
    NULL_PARAM_CHECK(p_encoded);
    NULL_PARAM_CHECK(p_opt);
    return block_opt_encode(p_opt->more, p_opt->size, p_opt->number, p_encoded);
}

uint32_t coap_block_opt_block2_decode(coap_block_opt_block2_t * p_opt, uint32_t encoded)
{
    NULL_PARAM_CHECK(p_opt);
    return block_opt_decode(encoded, &p_opt->more, &p_opt->size, &p_opt->number);
}
