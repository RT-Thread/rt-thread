/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#ifndef COND_FIELD_SERIALIZATION_H__
#define COND_FIELD_SERIALIZATION_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t (*field_encoder_handler_t)(void const * const p_field,
                                            uint8_t * const    p_buf,
                                            uint32_t           buf_len,
                                            uint32_t * const   p_index);

typedef uint32_t (*field_decoder_handler_t)(uint8_t const * const p_buf,
                                            uint32_t              buf_len,
                                            uint32_t * const      p_index,
                                            void *                p_field);

/**@brief Function for safe encoding of a conditional field.
 *
 * Function sets a presence flag and checks if conditional field is provided. If the field is not NULL,
 * it calls the provided parser function which attempts to encode the field content to the buffer stream.
 *
 * @param[in]      p_field          Pointer to the input struct.
 * @param[in]      p_buf            Pointer to the beginning of the output buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the encoded data.
 * @param[in]      fp_field_encoder Pointer to the function which implements fields encoding.
 *
 * @return NRF_SUCCESS              Fields encoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t cond_field_enc(void const * const      p_field,
                        uint8_t * const         p_buf,
                        uint32_t                buf_len,
                        uint32_t * const        p_index,
                        field_encoder_handler_t fp_field_encoder);

/**@brief Function for safe decoding of a conditional field.
 *
 * Function checks if conditional field is present in the input buffer. If it is set, it calls
 * the provided parser function which attempts to parse the buffer content to the known field.
 *
 * @param[in]      p_buf            Pointer to the beginning of the input buffer.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the uint8 value in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded data.
 * @param[in]      pp_field         Pointer to output location.
 * @param[in]      fp_field_decoder Pointer to the function which implements field decoding.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t cond_field_dec(uint8_t const * const   p_buf,
                        uint32_t                buf_len,
                        uint32_t * const        p_index,
                        void * * const          pp_field,
                        field_decoder_handler_t fp_field_decoder);

#ifdef __cplusplus
}
#endif

#endif // COND_FIELD_SERIALIZATION_H__
