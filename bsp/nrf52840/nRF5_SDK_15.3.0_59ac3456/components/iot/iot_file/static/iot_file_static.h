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
/**
 * @file iot_file_static.h
 * @brief FILE port for static buffers.
 */

#ifndef IOT_FILE_STATIC_H__
#define IOT_FILE_STATIC_H__

#include "iot_file_port.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup iot_file_static IoT file port for static buffers
 * @ingroup iot_file
 * @{
 * @brief Macro function which simplifies file setup process and file type assigning function.
 */

/**
 * @brief This macro function configures passed file as a static buffer file.
 */
#define IOT_FILE_STATIC_INIT(p_iot_file, p_file_name, p_mem, size)        \
    do {                                                                  \
        (p_iot_file)->p_filename  = p_file_name;                          \
        (p_iot_file)->cursor      = IOT_FILE_INVALID_CURSOR;              \
        (p_iot_file)->p_buffer    = p_mem;                                \
        (p_iot_file)->buffer_size = size;                                 \
        (p_iot_file)->file_size   = 0;                                    \
        (p_iot_file)->p_callback  = NULL;                                 \
        iot_file_static_assign(p_iot_file);                               \
    } while (0)

/**
 * @brief This function is used to assign correct callbacks and file type to passed IoT File instance.
 */
void iot_file_static_assign(iot_file_t * p_file);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // IOT_FILE_STATIC_H__
