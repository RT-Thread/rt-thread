/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */




#ifndef _IOTX_COMMON_MD5_H_
#define _IOTX_COMMON_MD5_H_

#include "iot_import.h"

typedef struct {
    uint32_t total[2];          /*!< number of bytes processed  */
    uint32_t state[4];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */
} iot_md5_context;

/**
 * \brief          Initialize MD5 context
 *
 * \param ctx      MD5 context to be initialized
 */
void utils_md5_init(iot_md5_context *ctx);

/**
 * \brief          Clear MD5 context
 *
 * \param ctx      MD5 context to be cleared
 */
void utils_md5_free(iot_md5_context *ctx);

/**
 * \brief          Clone (the state of) an MD5 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 */
void utils_md5_clone(iot_md5_context *dst,
                     const iot_md5_context *src);

/**
 * \brief          MD5 context setup
 *
 * \param ctx      context to be initialized
 */
void utils_md5_starts(iot_md5_context *ctx);

/**
 * \brief          MD5 process buffer
 *
 * \param ctx      MD5 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void utils_md5_update(iot_md5_context *ctx, const unsigned char *input, size_t ilen);

/**
 * \brief          MD5 final digest
 *
 * \param ctx      MD5 context
 * \param output   MD5 checksum result
 */
void utils_md5_finish(iot_md5_context *ctx, unsigned char output[16]);

/* Internal use */
void utils_md5_process(iot_md5_context *ctx, const unsigned char data[64]);

/**
 * \brief          Output = MD5( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   MD5 checksum result
 */
void utils_md5(const unsigned char *input, size_t ilen, unsigned char output[16]);

#endif

