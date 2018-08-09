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
/** @file coap_block.h
 *
 * @defgroup iot_sdk_coap_block CoAP Block transfer
 * @ingroup iot_sdk_coap
 * @{
 * @brief CoAP block transfer options encoding and decoding interface and definitions.
 *
 */

#ifndef COAP_BLOCK_H__
#define COAP_BLOCK_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define COAP_BLOCK_OPT_BLOCK_MORE_BIT_UNSET  0      /**< Value when more flag is set. */
#define COAP_BLOCK_OPT_BLOCK_MORE_BIT_SET    1      /**< Value when more flag is not set. */

typedef struct
{
    uint8_t  more;                                  /**< More bit value. */
    uint16_t size;                                  /**< Size of the block in bytes. */
    uint32_t number;                                /**< Block number. */
} coap_block_opt_block1_t;

typedef coap_block_opt_block1_t coap_block_opt_block2_t;

/**@brief Encode block1 option into its uint binary counter part.
 *
 * @param[out] p_encoded Encoded version of the coap block1 option value. Must not be NULL.
 * @param[in]  p_opt     Pointer to block1 option structure to be decoded into uint format. Must
 *                       not be NULL.
 *
 * @retval NRF_SUCCESS             If encoding of option was successful.
 * @retval NRF_ERROR_NULL          If one of the parameters supplied is a null pointer.
 * @retval NRF_ERROR_INVALID_PARAM If one of the fields in the option structure has an illegal
 *                                 value.
 */
uint32_t coap_block_opt_block1_encode(uint32_t * p_encoded, coap_block_opt_block1_t * p_opt);

/**@brief Decode block1 option from a uint to its structure counter part.
 *
 * @param[out] p_opt     Pointer to block1 option structure to be filled by the function. Must not
 *                       be NULL.
 * @param[in]  encoded   Encoded version of the coap block1 option value.
 *
 * @retval NRF_SUCCESS             If decoding of the option was successful.
 * @retval NRF_ERROR_NULL          If p_opt parameter is NULL.
 * @retval NRF_ERROR_INVALID_PARAM If the block number is higher then allowed by spec (more than
                                   20 bits).
 * @retval NRF_ERROR_INVALID_DATA  If the size has the value of the reserved 2048 value (7).
 */
uint32_t coap_block_opt_block1_decode(coap_block_opt_block1_t * p_opt, uint32_t encoded);

/**@brief Encode block2 option into its uint binary counter part.
 *
 * @param[out] p_encoded Encoded version of the coap block2 option value. Must not be NULL.
 * @param[in]  p_opt     Pointer to block2 option structure to be decoded into uint format. Must
 *                       not be NULL.
 *
 * @retval NRF_SUCCESS             If encoding of option was successful.
 * @retval NRF_ERROR_NULL          If one of the parameters supplied is a null pointer.
 * @retval NRF_ERROR_INVALID_PARAM If one of the fields in the option structure has an illegal
 *                                 value.
 */
uint32_t coap_block_opt_block2_encode(uint32_t * p_encoded, coap_block_opt_block2_t * p_opt);

/**@brief Decode block2 option from a uint to its structure counter part.
 *
 * @param[out] p_opt     Pointer to block2 option structure to be filled by the function. Must not
 *                       be NULL.
 * @param[in]  encoded   Encoded version of the coap block2 option value.
 *
 * @retval NRF_SUCCESS             If decoding of the option was successful.
 * @retval NRF_ERROR_NULL          If p_opt parameter is NULL.
 * @retval NRF_ERROR_INVALID_PARAM If the block number is higher then allowed by spec (more than
                                   20 bits).
 * @retval NRF_ERROR_INVALID_DATA  If the size has the value of the reserved 2048 value (7).
 */
uint32_t coap_block_opt_block2_decode(coap_block_opt_block2_t * p_opt, uint32_t encoded);

#endif // COAP_BLOCK_H__

/** @} */
