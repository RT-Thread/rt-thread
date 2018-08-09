/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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

 /**@file
 *
 * @defgroup nrf_log_backend_flash Flash logger backend
 * @{
 * @ingroup  nrf_log
 * @brief Flash logger backend.
 */

#ifndef NRF_LOG_BACKEND_FLASH_H
#define NRF_LOG_BACKEND_FLASH_H

#include "nrf_log_backend_interface.h"
#include "nrf_fstorage.h"
#include "nrf_log_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Flashlog logger backend API. */
extern const nrf_log_backend_api_t nrf_log_backend_flashlog_api;

/** @brief Crashlog logger backend API. */
extern const nrf_log_backend_api_t nrf_log_backend_crashlog_api;

/** @brief Flashlog logger backend structure. */
typedef struct {
    nrf_log_backend_t      backend;
} nrf_log_backend_flashlog_t;

/** @brief Crashlog logger backend structure. */
typedef struct {
    nrf_log_backend_t      backend;
} nrf_log_backend_crashlog_t;

/** @brief Macro for creating an instance of the flashlog logger backend. */
#define NRF_LOG_BACKEND_FLASHLOG_DEF(name)                   \
    static nrf_log_backend_flashlog_t name = {               \
        .backend = {.p_api = &nrf_log_backend_flashlog_api}, \
    }

/** @brief Macro for creating an instance of the crashlog logger backend. */
#define NRF_LOG_BACKEND_CRASHLOG_DEF(name)                   \
    static nrf_log_backend_crashlog_t name = {               \
        .backend = {.p_api = &nrf_log_backend_crashlog_api}, \
    }

/**
 * @brief Function for initializing the flash logger backend.
 *
 * Flash logger backend consists of two logical backends: flashlog and crashlog. Since both
 * backends write to the same flash area, the initialization is common.
 *
 * @param p_fs_api fstorage API to be used.
 *
 * @return NRF_SUCCESS or error code returned by @ref nrf_fstorage_init.
 */
ret_code_t nrf_log_backend_flash_init(nrf_fstorage_api_t const * p_fs_api);

/**
 * @brief Function for getting a log entry stored in flash.
 *
 * Log messages stored in flash can be read one by one starting from the oldest one.
 *
 * @param[in, out] p_token   Token reused between consecutive readings of log entries.
 *                           Token must be set to 0 to read the first entry.
 * @param[out]     pp_header Pointer to the entry header.
 * @param[out]     pp_data   Pointer to the data part of the entry (arguments or data in case of hexdump).
 *
 * @retval NRF_SUCCESS             Entry was successfully read.
 * @retval NRF_ERROR_NOT_SUPPORTED fstorage API does not support direct reading.
 * @retval NRF_ERROR_NOT_FOUND     Entry not found. Last entry was already reached or area is empty.
 */
ret_code_t nrf_log_backend_flash_next_entry_get(uint32_t *          p_token,
                                               nrf_log_header_t * * pp_header,
                                               uint8_t * *          pp_data);

/**
 * @brief Function for erasing flash area dedicated for the flash logger backend.
 */
ret_code_t nrf_log_backend_flash_erase(void);

#ifdef __cplusplus
}
#endif

#endif //NRF_LOG_BACKEND_UART_H

/** @} */
