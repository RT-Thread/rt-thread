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
 * @file iot_file_port.h
 * @brief Types and definitions used while writing port.
 */

#ifndef IOT_FILE_PORT_H__
#define IOT_FILE_PORT_H__

/**
 * @defgroup iot_file_port_defs IoT file definition for port libraries.
 * @{
 * @ingroup iot_file
 * @brief Type definitions for port modules.
 */
#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

//NOTE: Port functions don't need to check if p_file exists, because call can be done only on a correct file instance.

#define IOT_FILE_INVALID_CURSOR 0xFFFFFFFF

/**
 * @enum iot_file_type_t
 * @brief Supported file type values.
 */
typedef enum
{
    IOT_FILE_TYPE_UNKNOWN = 0,  /**< File type used for describing not initialized files. */
    IOT_FILE_TYPE_PSTORAGE_RAW, /**< File type used for accessing flash memory. */
    IOT_FILE_TYPE_STATIC        /**< File type used for representing static buffers. */
} iot_file_type_t;

/**
 * @brief iot_file_t structure forward definition.
 */
typedef struct iot_file_struct_t iot_file_t;

/**
 * @brief IoT File fopen() callback type definition.
 */
typedef uint32_t (*iot_fopen_t)(iot_file_t * p_file, uint32_t requested_size);

/**
 * @brief IoT File fwrite() callback type definition.
 */
typedef uint32_t (*iot_fwrite_t)(iot_file_t * p_file, const void * p_data, uint32_t size);

/**
 * @brief IoT File fread() callback type definition.
 */
typedef uint32_t (*iot_fread_t)(iot_file_t * p_file, void * p_data, uint32_t size);

/**
 * @brief IoT File ftell() callback type definition.
 */
typedef uint32_t (*iot_ftell_t)(iot_file_t * p_file, uint32_t * p_cursor);

/**
 * @brief IoT File fseek() callback type definition.
 */
typedef uint32_t (*iot_fseek_t)(iot_file_t * p_file, uint32_t cursor);

/**
 * @brief IoT File frewind() callback type definition.
 */
typedef uint32_t (*iot_frewind_t)(iot_file_t * p_file);

/**
 * @brief IoT File fclose() callback type definition.
 */
typedef uint32_t (*iot_fclose_t)(iot_file_t * p_file);

/**
 * @brief Generic IoT File instance structure.
 */
struct iot_file_struct_t
{
    const char          * p_filename;     /**< Public. String constant describing file name. */
    iot_file_type_t       type;           /**< Public. Type of file. Each type should be added into iot_file_type_t enum. */
    uint32_t              file_size;      /**< Public. Number of valid bytes inside file. */

    uint32_t              cursor;         /**< Internal. Cursor describing which byte will be read/written. */
    uint32_t              buffer_size;    /**< Internal. Size of data buffer. */
    void                * p_buffer;       /**< Internal. Pointer to a data buffer set by calling fopen. */
    void                * p_callback;     /**< Internal. User callback used in order to notify about finished file operations. */
    void                * p_arg;          /**< Internal. User defined argument, used inside the port. */
    iot_fopen_t           open;           /**< Internal. Callback for fopen operation assigned by particular port. */
    iot_fwrite_t          write;          /**< Internal. Callback for fwrite operation assigned by particular port. */
    iot_fread_t           read;           /**< Internal. Callback for fread operation assigned by particular port. */
    iot_ftell_t           tell;           /**< Internal. Callback for ftell operation assigned by particular port. */
    iot_fseek_t           seek;           /**< Internal. Callback for fseek operation assigned by particular port. */
    iot_frewind_t         rewind;         /**< Internal. Callback for frewind operation assigned by particular port. */
    iot_fclose_t          close;          /**< Internal. Callback for fclose operation assigned by particular port. */
};

#ifdef __cplusplus
}
#endif

#endif // IOT_FILE_PORT_H__

/** @} */
