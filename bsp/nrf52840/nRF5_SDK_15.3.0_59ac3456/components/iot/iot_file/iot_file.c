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
#include "sdk_config.h"
#include "iot_file.h"
#include "iot_common.h"

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          IOT_FILE_DISABLE_API_PARAM_CHECK should be set to 0 to enable these checks.
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


/**
 * @brief Function to open IoT file. Depending on port, it should allocate required buffer.
 */
uint32_t iot_file_fopen(iot_file_t * p_file, uint32_t requested_size)
{
    NULL_PARAM_CHECK(p_file);

    if (p_file->open != NULL)
    {
        return p_file->open(p_file, requested_size);
    }
    else
    {
        p_file->buffer_size = requested_size;
        return NRF_ERROR_API_NOT_IMPLEMENTED;
    }
}


/**
 * @brief Function to write data buffer into a file.
 */
uint32_t iot_file_fwrite(iot_file_t * p_file, const void * p_data, uint32_t size)
{
    NULL_PARAM_CHECK(p_file);

    if (p_file->write != NULL)
    {
        return p_file->write(p_file, p_data, size);
    }
    else
    {
        return NRF_ERROR_API_NOT_IMPLEMENTED;
    }
}


/**
 * @brief Function to read data buffer from file.
 */
uint32_t iot_file_fread(iot_file_t * p_file, void * p_data, uint32_t size)
{
    NULL_PARAM_CHECK(p_file);

    if (p_file->read != NULL)
    {
        return p_file->read(p_file, p_data, size);
    }
    else
    {
        return NRF_ERROR_API_NOT_IMPLEMENTED;
    }
}


/**
 * @brief Function to read current cursor position.
 */
uint32_t iot_file_ftell(iot_file_t * p_file, uint32_t * p_cursor)
{
    NULL_PARAM_CHECK(p_file);

    if (p_file->tell != NULL)
    {
        return p_file->tell(p_file, p_cursor);
    }
    else
    {
        return NRF_ERROR_API_NOT_IMPLEMENTED;
    }
}


/**
 * @brief Function to set current cursor position.
 */
uint32_t iot_file_fseek(iot_file_t * p_file, uint32_t cursor)
{
    NULL_PARAM_CHECK(p_file);

    if (p_file->seek != NULL)
    {
        return p_file->seek(p_file, cursor);
    }
    else
    {
        return NRF_ERROR_API_NOT_IMPLEMENTED;
    }
}


/**
 * @brief Function to rewind file cursor.
 */
uint32_t iot_file_frewind(iot_file_t * p_file)
{
    NULL_PARAM_CHECK(p_file);

    if (p_file->rewind != NULL)
    {
        return p_file->rewind(p_file);
    }
    else
    {
        return NRF_ERROR_API_NOT_IMPLEMENTED;
    }
}


/**
 * @brief Function to close IoT file. Depending on port, it should free used buffer.
 */
uint32_t iot_file_fclose(iot_file_t * p_file)
{
    NULL_PARAM_CHECK(p_file);

    if (p_file->close != NULL)
    {
        return p_file->close(p_file);
    }
    else
    {
        return NRF_ERROR_API_NOT_IMPLEMENTED;
    }
}

