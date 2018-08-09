/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#ifndef _ANT_STRUCT_SERIALIZATION_
#define _ANT_STRUCT_SERIALIZATION_

/**@brief Function for safe encoding of an ANT_ENABLE struct.
 *
 * Safe decoding of an ANT_ENABLE struct. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_void_enable_params   An ANT_ENABLE struct to be encoded.
 * @param[out]     p_buf                  Buffer containing the struct.
 * @param[in]      buf_len                Size of the buffer.
 * @param[in,out]  p_index                \c in: Index to the start of the ANT_ENABLE struct in the buffer.
 *                                        \c out: Index in the buffer to the first byte after the decoded struct.
 *
 * @return NRF_SUCCESS                    Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH       Decoding failure. Incorrect buffer length.
 */
uint32_t ANT_ENABLE_enc( void const * const p_void_enable_params,
                         uint8_t * const    p_buf,
                         uint32_t           buf_len,
                         uint32_t * const   p_index);

/**@brief Function for safe decoding of an ANT_ENABLE struct.
 *
 * Safe decoding of a ANT_ENABLE struct. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf                  Buffer containing the struct.
 * @param[in]      buf_len                Size of the buffer.
 * @param[in,out]  p_index                \c in: Index to the start of the ANT_ENABLE struct in the buffer.
 *                                        \c out: Index in the buffer to the first byte after the decoded struct.
 * @param[out]     p_void_enable_params   Decoded ANT_ENABLE struct.
 */
uint32_t ANT_ENABLE_dec( uint8_t const * const p_buf,
                         uint32_t              buf_len,
                         uint32_t * const      p_index,
                         void * const          p_void_enable_params);

/**@brief Function for safe encoding of an ant_evt_t struct.
 *
 * Safe decoding of an ant_evt_t struct. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_void_ant_evt   An ant_evt_t struct to be encoded.
 * @param[out]     p_buf            Buffer containing the struct.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the ant_evt_t struct in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded struct.
 *
 * @return NRF_SUCCESS              Fields decoded successfully.
 * @retval NRF_ERROR_INVALID_LENGTH Decoding failure. Incorrect buffer length.
 */
uint32_t ant_evt_t_enc( void const * const p_void_ant_evt,
                        uint8_t * const    p_buf,
                        uint32_t           buf_len,
                        uint32_t * const   p_index);

/**@brief Function for safe decoding of an ant_evt_t struct.
 *
 * Safe decoding of a ant_evt_t struct. Range checks will be done if @ref SER_ASSERTS_ENABLED is set.
 *
 * @param[in]      p_buf            Buffer containing the struct.
 * @param[in]      buf_len          Size of the buffer.
 * @param[in,out]  p_index          \c in: Index to the start of the ant_evt_t struct in the buffer.
 *                                  \c out: Index in the buffer to the first byte after the decoded struct.
 * @param[out]     p_void_ant_evt   Decoded ant_evt_t struct.
 */
uint32_t ant_evt_t_dec( uint8_t const * const p_buf,
                        uint32_t              buf_len,
                        uint32_t * const      p_index,
                        void * const          p_void_ant_evt);

#endif
