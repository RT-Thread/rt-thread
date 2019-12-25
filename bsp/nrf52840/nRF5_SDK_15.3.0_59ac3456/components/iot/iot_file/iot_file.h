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
 * @file iot_file.h
 * @brief IoT File abstraction API.
 */

#ifndef IOT_FILE_H__
#define IOT_FILE_H__

#include "iot_common.h"
#include "iot_file_port.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup iot_sdk_common
 * @addtogroup iot_file IoT File
 * @brief IoT File abstraction definition.
 * @{
 * @defgroup iot_file_abstraction IoT file abstraction
 * @{
 * @brief Structures and public API definition.
 */

/**
 * @enum iot_file_evt_t
 * @brief List of events returned in callback for file ports with asynchronous operation
 *        like open, read, write and close.
 */
typedef enum {
    IOT_FILE_OPENED,                /**< Event indicates that file has been opened.*/
    IOT_FILE_WRITE_COMPLETE,        /**< Event indicates that single write operation has been completed.*/
    IOT_FILE_READ_COMPLETE,         /**< Event indicates that single read operation has been completed.*/
    IOT_FILE_CLOSED,                /**< Event indicates that file has been closed.*/
    IOT_FILE_ERROR                  /**< Event indicates that file encountered a problem.*/
} iot_file_evt_t;

/**
 * @brief IoT File user callback type definition.
 *
 * @param[in] p_file Reference to an IoT file instance.
 * @param[in] event  Event structure describing what has happened.
 * @param[in] result Result code (should be NRF_SUCCESS for all events except errors).
 * @param[in] p_data Pointer to memory buffer.
 * @param[in] size   Size of data stored in memory buffer.
 *
 * @retval None.
 */
typedef void (*iot_file_callback_t) (iot_file_t * p_file, iot_file_evt_t event, uint32_t result, void * p_data, uint32_t size);

/**
 * @brief Function to open IoT file. Depending on port, it should allocate required buffer.
 *
 * @param[in] p_file          Pointer to an IoT file instance.
 * @param[in] requested_size  Maximum number of bytes to be read/written.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t iot_file_fopen(iot_file_t * p_file, uint32_t requested_size);

/**
 * @brief Function to write data buffer into a file.
 *
 * @param[in] p_file  Pointer to an IoT file instance.
 * @param[in] p_data  Pointer to data block which will be written into the file.
 * @param[in] size    Number of bytes to be written.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t iot_file_fwrite(iot_file_t * p_file, const void * p_data, uint32_t size);

/**
 * @brief Function to read data buffer from file.
 *
 * @param[in] p_file  Pointer to an IoT file instance.
 * @param[in] p_data  Pointer to data block to be filled with read data.
 * @param[in] size    Number of bytes to be read.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t iot_file_fread(iot_file_t * p_file, void * p_data, uint32_t size);

/**
 * @brief Function to read current cursor position.
 *
 * @param[in]  p_file    Pointer to an IoT file instance.
 * @param[out] p_cursor  Current value of a cursor.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t iot_file_ftell(iot_file_t * p_file, uint32_t * p_cursor);

/**
 * @brief Function to set current cursor position.
 *
 * @param[in] p_file  Pointer to an IoT file instance.
 * @param[in] cursor  New cursor value.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t iot_file_fseek(iot_file_t * p_file, uint32_t cursor);

/**
 * @brief Function to rewind file cursor.
 *
 * @param[in]  p_file  Pointer to an IoT file instance.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t iot_file_frewind(iot_file_t * p_file);

/**
 * @brief Function to close IoT file. Depending on port, it should free used buffer.
 *
 * @param[in]  p_file  Pointer to an IoT file instance.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t iot_file_fclose(iot_file_t * p_file);

#ifdef __cplusplus
}
#endif

#endif // IOT_FILE_H__

/** @} */
/** @} */
