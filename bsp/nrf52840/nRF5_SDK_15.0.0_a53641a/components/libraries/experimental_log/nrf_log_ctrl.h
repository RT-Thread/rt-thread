/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#ifndef NRF_LOG_CTRL_H
#define NRF_LOG_CTRL_H

/**@file
 * @addtogroup nrf_log Logger module
 * @ingroup    app_common
 *
 * @defgroup nrf_log_ctrl Functions for controlling nrf_log
 * @{
 * @ingroup  nrf_log
 * @brief    The nrf_log control interface.
 */

#include "sdk_config.h"
#include "sdk_errors.h"
#include <stdint.h>
#include <stdbool.h>
#include "nrf_log_types.h"
#include "nrf_log_ctrl_internal.h"
#include "nrf_log_backend_interface.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Timestamp function prototype.
 *
 * @return Timestamp value.
 */
typedef uint32_t (*nrf_log_timestamp_func_t)(void);

/**@brief Macro for initializing the logs.
 *
 * Macro has one or two parameters. First parameter (obligatory) is the timestamp function (@ref nrf_log_timestamp_func_t).
 * Additionally, as the second parameter timestamp frequency in Hz can be provided. If not provided then default
 * frequency is used (@ref  NRF_LOG_TIMESTAMP_DEFAULT_FREQUENCY). Frequency is used to format timestamp prefix if
 * @ref NRF_LOG_STR_FORMATTER_TIMESTAMP_FORMAT_ENABLED is set.
 *
 * @return  NRF_SUCCESS after successful initialization, otherwise an error code.
 */
#define NRF_LOG_INIT(...) NRF_LOG_INTERNAL_INIT(__VA_ARGS__)


/**@brief Macro for processing a single log entry from a queue of deferred logs.
 *
 * You can call this macro from the main context or from the error handler to process
 * log entries one by one.
 *
 * @note If logs are not deferred, this call has no use and is defined as 'false'.
 *
 * @retval true    There are more logs to process in the buffer.
 * @retval false   No more logs in the buffer.
 */
#define NRF_LOG_PROCESS()    NRF_LOG_INTERNAL_PROCESS()

/** @brief Macro for processing all log entries from the buffer.
 * It blocks until all buffered entries are processed by the backend.
 *
 * @note If logs are not deferred, this call has no use and is empty.
 */
#define NRF_LOG_FLUSH()      NRF_LOG_INTERNAL_FLUSH()

/** @brief Macro for flushing log data before reset.
 *
 * @note If logs are not deferred, this call has no use and is empty.
 *
 * @note If RTT is used, then a breakpoint is hit once flushed.
 */
#define NRF_LOG_FINAL_FLUSH() NRF_LOG_INTERNAL_FINAL_FLUSH()

/**
 * @brief Function for initializing the frontend and the default backend.
 *
 * @ref NRF_LOG_INIT calls this function to initialize the frontend and the backend.
 * If custom backend is used, then @ref NRF_LOG_INIT should not be called.
 * Instead, frontend and user backend should be verbosely initialized.
 *
 * @param timestamp_func Function for getting a 32-bit timestamp.
 * @param timestamp_freq Frequency of the timestamp.
 *
 * @return Error status.
 *
 */
ret_code_t nrf_log_init(nrf_log_timestamp_func_t timestamp_func, uint32_t timestamp_freq);

/**
 * @brief Function for adding new backend interface to the logger.
 *
 * @param p_backend Pointer to the backend interface.
 * @param severity  Initial value of severity level for each module forwarded to the backend. This
 *                  option is only applicable if @ref NRF_LOG_FILTERS_ENABLED is set.
 * @return -1 if backend cannot be added or positive number (backend ID).
 */
int32_t nrf_log_backend_add(nrf_log_backend_t * p_backend, nrf_log_severity_t severity);

/**
 * @brief Function for removing backend from the logger.
 *
 * @param p_backend Pointer to the backend interface.
 *
 */
void nrf_log_backend_remove(nrf_log_backend_t * p_backend);

/**
 * @brief Function for setting logger backends into panic mode.
 *
 * When this function is called all attached backends are informed about panic state of the system.
 * It is up to the backend to react properly (hold or process logs in blocking mode, etc.)
 */
void nrf_log_panic(void);

/**
 * @brief Function for handling a single log entry.
 *
 * Use this function only if the logs are buffered. It takes a single entry from the
 * buffer and attempts to process it.
 *
 * @retval true  If there are more entries to process.
 * @retval false If there are no more entries to process.
 */
bool nrf_log_frontend_dequeue(void);

/**
 * @brief Function for getting number of independent log modules registered into the logger.
 *
 * @return Number of registered modules.
 */
uint32_t nrf_log_module_cnt_get(void);

/**
 * @brief Function for getting module name.
 *
 * @param module_id      Module ID.
 * @param is_ordered_idx Module ID is given is index in alphabetically sorted list of modules.
 * @return Pointer to string with module name.
 */
const char * nrf_log_module_name_get(uint32_t module_id, bool is_ordered_idx);

/**
 * @brief Function for getting coloring of specific logs.
 *
 * @param module_id Module ID.
 * @param severity  Log severity.
 *
 * @return ID of the color.
 */
uint8_t nrf_log_color_id_get(uint32_t module_id, nrf_log_severity_t severity);

/**
 * @brief Function for configuring filtering ofs logs in the module.
 *
 * Filtering of logs in modules is independent for each backend.
 *
 * @param backend_id Backend ID which want to chenge its configuration.
 * @param module_id  Module ID which logs will be reconfigured.
 * @param severity   New severity filter.
 */
void nrf_log_module_filter_set(uint32_t backend_id,
                               uint32_t module_id,
                               nrf_log_severity_t severity);

/**
 * @brief Function for getting module severity level.
 *
 * @param backend_id     Backend ID.
 * @param module_id      Module ID.
 * @param is_ordered_idx Module ID is given is index in alphabetically sorted list of modules.
 * @param dynamic        It true current filter for given backend is returned. If false then
 *                       compiled-in level is returned (maximum available). If this parameter is
 *                       false then backend_id parameter is not used.
 *
 * @return Severity.
 */
nrf_log_severity_t nrf_log_module_filter_get(uint32_t backend_id,
                                             uint32_t module_id,
                                             bool     is_ordered_idx,
                                             bool     dynamic);

#ifdef __cplusplus
}
#endif

#endif // NRF_LOG_CTRL_H

/**
 *@}
 **/
