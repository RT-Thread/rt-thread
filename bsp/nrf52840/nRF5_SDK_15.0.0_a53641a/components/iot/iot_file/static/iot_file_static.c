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
#include "sdk_config.h"
#include "iot_file_static.h"
#include "iot_common.h"
#include <string.h>

#if IOT_FILE_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME iot_file_static

#define NRF_LOG_LEVEL       IOT_FILE_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IOT_FILE_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IOT_FILE_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define FSTATIC_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define FSTATIC_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define FSTATIC_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#else // IOT_FILE_CONFIG_LOG_ENABLED

#define FSTATIC_TRC(...)                                                                           /**< Disables traces. */
#define FSTATIC_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define FSTATIC_ERR(...)                                                                           /**< Disables error logs. */

#endif // IOT_FILE_CONFIG_LOG_ENABLED

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          IOT_FILE_STATIC_DISABLE_API_PARAM_CHECK should be set to 0 to enable these checks.
 *
 * @{
 */

#if (IOT_FILE_DISABLE_API_PARAM_CHECK == 0)

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                     \
    if ((PARAM) == NULL)                                            \
    {                                                               \
        return (NRF_ERROR_NULL | IOT_FILE_ERR_BASE);                \
    }

#else // IOT_FILE_DISABLE_API_PARAM_CHECK

#define NULL_PARAM_CHECK(PARAM)

#endif // IOT_FILE_DISABLE_API_PARAM_CHECK
/** @} */

#define CHECK_CURSOR(PARAM)                                         \
    if ((PARAM) == IOT_FILE_INVALID_CURSOR)                         \
    {                                                               \
        return  (NRF_ERROR_INVALID_STATE | IOT_FILE_ERR_BASE);      \
    }

/**@brief Static buffer fwrite port function definition. */
static uint32_t internal_fwrite(iot_file_t * p_file, const void * p_data, uint32_t size)
{
    NULL_PARAM_CHECK(p_data);
    CHECK_CURSOR(p_file->cursor);

    if ((size + p_file->cursor) > p_file->buffer_size)
    {
        return (NRF_ERROR_DATA_SIZE | IOT_FILE_ERR_BASE);
    }

    memcpy(((uint8_t *)p_file->p_buffer + p_file->cursor), p_data, size);
    p_file->cursor += size;

    if (p_file->cursor > p_file->file_size)
    {
        p_file->file_size = p_file->cursor;
    }

    return NRF_SUCCESS;
}


/**@brief Static buffer fread port function definition. */
static uint32_t internal_fread(iot_file_t * p_file, void * p_data, uint32_t size)
{
    NULL_PARAM_CHECK(p_data);
    CHECK_CURSOR(p_file->cursor);

    if (size + p_file->cursor > p_file->file_size)
    {
        return (NRF_ERROR_DATA_SIZE | IOT_FILE_ERR_BASE);
    }

    memcpy(p_data, (uint8_t *)p_file->p_buffer + p_file->cursor, size);
    p_file->cursor += size;

    return NRF_SUCCESS;
}


/**@brief Static ftell port function definition. */
static uint32_t internal_ftell(iot_file_t * p_file, uint32_t * p_cursor)
{
    NULL_PARAM_CHECK(p_cursor);
    CHECK_CURSOR(p_file->cursor);

    *p_cursor = p_file->cursor;

    return NRF_SUCCESS;
}


/**@brief Static fseek port function definition. */
static uint32_t internal_fseek(iot_file_t * p_file, uint32_t cursor)
{
    CHECK_CURSOR(p_file->cursor);

    if (cursor > p_file->buffer_size)
    {
        FSTATIC_ERR("Cursor outside file!");
        return (NRF_ERROR_INVALID_PARAM | IOT_FILE_ERR_BASE);
    }

    p_file->cursor = cursor;

    return NRF_SUCCESS;
}


/**@brief Static frewind port function definition. */
static uint32_t internal_frewind(iot_file_t * p_file)
{
    CHECK_CURSOR(p_file->cursor);

    p_file->cursor = 0;

    return NRF_SUCCESS;
}


/**@brief Static fopen port function definition. */
static uint32_t internal_fopen(iot_file_t * p_file, uint32_t requested_size)
{
    p_file->cursor = 0;

    if (requested_size != 0)
    {
        p_file->file_size = requested_size;
    }

    return NRF_SUCCESS;
}


/**@brief Static fclose port function definition. */
static uint32_t internal_fclose(iot_file_t * p_file)
{
    p_file->cursor = IOT_FILE_INVALID_CURSOR;

    return NRF_SUCCESS;
}


/**@brief This function is used to assign correct callbacks and file type to passed IoT File instance. */
void iot_file_static_assign(iot_file_t * p_file)
{
    if (p_file == NULL)
    {
        return;
    }

    p_file->type   = IOT_FILE_TYPE_STATIC;
    p_file->write  = internal_fwrite;
    p_file->read   = internal_fread;
    p_file->tell   = internal_ftell;
    p_file->seek   = internal_fseek;
    p_file->rewind = internal_frewind;
    p_file->open   = internal_fopen;
    p_file->close  = internal_fclose;
}
