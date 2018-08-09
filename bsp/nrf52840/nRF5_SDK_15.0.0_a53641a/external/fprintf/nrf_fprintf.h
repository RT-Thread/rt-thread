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
#ifndef NRF_FPRINTF_H__
#define NRF_FPRINTF_H__

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (* nrf_fprintf_fwrite)(void const * p_user_ctx, char const * p_str, size_t length);

/**
 * @brief fprintf context
 */
typedef struct nrf_fprintf_ctx
{
    char * const p_io_buffer;       ///< Pointer to IO buffer.
    size_t const io_buffer_size;    ///< IO buffer size.
    size_t io_buffer_cnt;           ///< IO buffer usage.
    bool auto_flush;                ///< Auto flush configurator.

    void const * const p_user_ctx;  ///< Pointer to user data to be passed to the fwrite funciton.

    nrf_fprintf_fwrite fwrite;      ///< Pointer to function sending data stream.
} nrf_fprintf_ctx_t;


/**
 * @brief Macro for defining nrf_fprintf instance.
 *
 * @param name              Instance name.
 * @param _p_user_ctx       Pointer to user data.
 * @param _p_io_buffer      Pointer to IO buffer
 * @param _io_buffer_size   Size of IO buffer.
 * @param _auto_flush       Indicator if IO buffer shall be automatically flush.
 * @param _fwrite           Pointer to function sending data stream.
 * */
#define NRF_FPRINTF_DEF(name, _p_user_ctx, _p_io_buffer, _io_buffer_size, _auto_flush, _fwrite) \
    static nrf_fprintf_ctx_t name =                                                             \
    {                                                                                           \
        .p_io_buffer = _p_io_buffer,                                                            \
        .io_buffer_size = _io_buffer_size,                                                      \
        .io_buffer_cnt = 0,                                                                     \
        .auto_flush = _auto_flush,                                                              \
        .p_user_ctx = _p_user_ctx,                                                              \
        .fwrite = _fwrite                                                                       \
    }

/**
 * @brief fprintf like function which send formated data stream to output specified by user
 * @ref nrf_fprintf_ctx_t
 *
 * @param p_ctx     fprintf context.
 * @param p_fmt     Format string.
 * @param ...       List of parameters to print.
 * */
void nrf_fprintf(nrf_fprintf_ctx_t * const p_ctx,
                 char const *              p_fmt,
                                           ...);

/**
 * @brief function flushing data stored in io_buffer @ref nrf_fprintf_ctx_t
 *
 * @param p_ctx fprintf context
 */
void nrf_fprintf_buffer_flush(nrf_fprintf_ctx_t * const p_ctx);


#ifdef __cplusplus
}
#endif

#endif /* NRF_FPRINTF_H__ */

