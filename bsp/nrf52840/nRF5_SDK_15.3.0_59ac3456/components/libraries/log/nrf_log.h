/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
 * @defgroup nrf_log Logger module
 * @{
 * @ingroup app_common
 *
 * @brief The nrf_log module interface.
 */

#ifndef NRF_LOG_H_
#define NRF_LOG_H_

#include "sdk_common.h"
#include "nrf_section.h"
#if NRF_MODULE_ENABLED(NRF_LOG)
#include "nrf_strerror.h"
#define NRF_LOG_ERROR_STRING_GET(code) nrf_strerror_get(code)
#else
#define NRF_LOG_ERROR_STRING_GET(code) ""
#endif


#ifdef __cplusplus
extern "C" {
#endif

/** @brief Severity level for the module.
 *
 * The severity level can be defined in a module to override the default.
 */
#ifndef NRF_LOG_LEVEL
    #define NRF_LOG_LEVEL NRF_LOG_DEFAULT_LEVEL
#endif

/** @brief Initial severity if filtering is enabled.
 */
#ifndef NRF_LOG_INITIAL_LEVEL
    #define NRF_LOG_INITIAL_LEVEL NRF_LOG_LEVEL
#endif


#include "nrf_log_internal.h"

/** @def NRF_LOG_ERROR
 *  @brief Macro for logging error messages. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 */

/** @def NRF_LOG_WARNING
 *  @brief Macro for logging error messages. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes warning logs.
 */

/** @def NRF_LOG_INFO
 *  @brief Macro for logging error messages. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes info logs.
 */

/** @def NRF_LOG_DEBUG
 *  @brief Macro for logging error messages. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes debug logs.
 */

#define NRF_LOG_ERROR(...)                     NRF_LOG_INTERNAL_ERROR(__VA_ARGS__)
#define NRF_LOG_WARNING(...)                   NRF_LOG_INTERNAL_WARNING( __VA_ARGS__)
#define NRF_LOG_INFO(...)                      NRF_LOG_INTERNAL_INFO( __VA_ARGS__)
#define NRF_LOG_DEBUG(...)                     NRF_LOG_INTERNAL_DEBUG( __VA_ARGS__)

/** @def NRF_LOG_INST_ERROR
 *  @brief Macro for logging error messages for a given module instance. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @param p_inst Pointer to the instance with logging support.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 */

/** @def NRF_LOG_INST_WARNING
 *  @brief Macro for logging error messages for a given module instance. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @param p_inst Pointer to the instance with logging support.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 */

/** @def NRF_LOG_INST_INFO
 *  @brief Macro for logging error messages for a given module instance. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @param p_inst Pointer to the instance with logging support.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 */

/** @def NRF_LOG_INST_DEBUG
 *  @brief Macro for logging error messages for given module instance. It takes a printf-like, formatted
 *  string with up to seven arguments.
 *
 *  @param p_inst Pointer to the instance with logging support.
 *
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 */
#define NRF_LOG_INST_ERROR(p_inst,...)         NRF_LOG_INTERNAL_INST_ERROR(p_inst,__VA_ARGS__)
#define NRF_LOG_INST_WARNING(p_inst,...)       NRF_LOG_INTERNAL_INST_WARNING(p_inst,__VA_ARGS__)
#define NRF_LOG_INST_INFO(p_inst,...)          NRF_LOG_INTERNAL_INST_INFO(p_inst, __VA_ARGS__)
#define NRF_LOG_INST_DEBUG(p_inst,...)         NRF_LOG_INTERNAL_INST_DEBUG(p_inst, __VA_ARGS__)

/**
 * @brief Macro for logging a formatted string without any prefix or timestamp.
 */
#define NRF_LOG_RAW_INFO(...)                  NRF_LOG_INTERNAL_RAW_INFO( __VA_ARGS__)

/** @def NRF_LOG_HEXDUMP_ERROR
 *  @brief Macro for logging raw bytes.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 *
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
/** @def NRF_LOG_HEXDUMP_WARNING
 *  @brief Macro for logging raw bytes.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes warning logs.
 *
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
/** @def NRF_LOG_HEXDUMP_INFO
 *  @brief Macro for logging raw bytes.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes info logs.
 *
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
/** @def NRF_LOG_HEXDUMP_DEBUG
 *  @brief Macro for logging raw bytes.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes debug logs.
 *
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
#define NRF_LOG_HEXDUMP_ERROR(p_data, len)   NRF_LOG_INTERNAL_HEXDUMP_ERROR(p_data, len)
#define NRF_LOG_HEXDUMP_WARNING(p_data, len) NRF_LOG_INTERNAL_HEXDUMP_WARNING(p_data, len)
#define NRF_LOG_HEXDUMP_INFO(p_data, len)    NRF_LOG_INTERNAL_HEXDUMP_INFO(p_data, len)
#define NRF_LOG_HEXDUMP_DEBUG(p_data, len)   NRF_LOG_INTERNAL_HEXDUMP_DEBUG(p_data, len)

/** @def NRF_LOG_HEXDUMP_INST_ERROR
 *  @brief Macro for logging raw bytes for a specific module instance.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 *
 * @param p_inst     Pointer to the instance with logging support.
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
/** @def NRF_LOG_HEXDUMP_INST_WARNING
 *  @brief Macro for logging raw bytes for a specific module instance.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 *
 * @param p_inst     Pointer to the instance with logging support.
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
/** @def NRF_LOG_HEXDUMP_INST_INFO
 *  @brief Macro for logging raw bytes for a specific module instance.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 *
 * @param p_inst     Pointer to the instance with logging support.
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
/** @def NRF_LOG_HEXDUMP_INST_DEBUG
 *  @brief Macro for logging raw bytes for a specific module instance.
 *  @details This macro is compiled only if @ref NRF_LOG_LEVEL includes error logs.
 *
 * @param p_inst     Pointer to the instance with logging support.
 * @param p_data     Pointer to data.
 * @param len        Data length in bytes.
 */
#define NRF_LOG_HEXDUMP_INST_ERROR(p_inst, p_data, len)   NRF_LOG_INTERNAL_HEXDUMP_INST_ERROR(p_inst, p_data, len)
#define NRF_LOG_HEXDUMP_INST_WARNING(p_inst, p_data, len) NRF_LOG_INTERNAL_HEXDUMP_INST_WARNING(p_inst, p_data, len)
#define NRF_LOG_HEXDUMP_INST_INFO(p_inst, p_data, len)    NRF_LOG_INTERNAL_HEXDUMP_INST_INFO(p_inst, p_data, len)
#define NRF_LOG_HEXDUMP_INST_DEBUG(p_inst, p_data, len)   NRF_LOG_INTERNAL_HEXDUMP_INST_DEBUG(p_inst, p_data, len)

/**
 * @brief Macro for logging hexdump without any prefix or timestamp.
 */
#define NRF_LOG_RAW_HEXDUMP_INFO(p_data, len) NRF_LOG_INTERNAL_RAW_HEXDUMP_INFO(p_data, len)


/**
 * @brief Macro for copying a string to internal logger buffer if logs are deferred.
 *
 * @param _str  String.
 */
#define NRF_LOG_PUSH(_str)                   NRF_LOG_INTERNAL_LOG_PUSH(_str)

/**
 * @brief Function for copying a string to the internal logger buffer if logs are deferred.
 *
 * Use this function to store a string that is volatile (for example allocated
 * on stack) or that may change before the deferred logs are processed. Such string is copied
 * into the internal logger buffer (see @ref NRF_LOG_STR_PUSH_BUFFER_SIZE).
 *
 * @note String storing is not reliable. It means that string is copied to the buffer but there is
 *       no indication when it was used and could be freed. String may be overwritten by another
 *       @ref nrf_log_push call before being processed. For reliable data dumping use
 *       hexdump macros (e.g. @ref NRF_LOG_HEXDUMP_INFO).
 *
 * @note If the logs are not deferred, then this function returns the input parameter.
 *
 * @param p_str Pointer to the user string.
 *
 * @return Address to the location where the string is stored in the internal logger buffer.
 */
char const * nrf_log_push(char * const p_str);

/**
 * @brief Macro to be used in a formatted string to a pass float number to the log.
 *
 * Use this macro in a formatted string instead of the %f specifier together with
 * @ref NRF_LOG_FLOAT macro.
 * Example: NRF_LOG_INFO("My float number" NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT(f)))
 */
#define NRF_LOG_FLOAT_MARKER "%s%d.%02d"

/**
 * @brief Macro for dissecting a float number into two numbers (integer and residuum).
 */
#define NRF_LOG_FLOAT(val) (uint32_t)(((val) < 0 && (val) > -1.0) ? "-" : ""),   \
                           (int32_t)(val),                                       \
                           (int32_t)((((val) > 0) ? (val) - (int32_t)(val)       \
                                                : (int32_t)(val) - (val))*100)


/**
 * @brief Macro for registering an independent module.
 *
 * Registration creates set of dynamic (RAM) and constant variables associated with the module.
 */
#define NRF_LOG_MODULE_REGISTER() NRF_LOG_INTERNAL_MODULE_REGISTER()


#ifdef __cplusplus
}
#endif

#endif // NRF_LOG_H_

/** @} */
