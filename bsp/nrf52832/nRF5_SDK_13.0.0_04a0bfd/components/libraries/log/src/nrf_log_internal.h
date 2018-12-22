/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef NRF_LOG_INTERNAL_H__
#define NRF_LOG_INTERNAL_H__
#include "sdk_common.h"
#include "nrf.h"
#include "nrf_error.h"
#include "app_util.h"
#include <stdint.h>
#include <stdbool.h>

#ifndef NRF_LOG_DEFAULT_LEVEL
#define NRF_LOG_DEFAULT_LEVEL 0
#endif

#ifndef NRF_LOG_USES_COLORS
#define NRF_LOG_USES_COLORS        0
#endif

#define NRF_LOG_LEVEL_ERROR        1U
#define NRF_LOG_LEVEL_WARNING      2U
#define NRF_LOG_LEVEL_INFO         3U
#define NRF_LOG_LEVEL_DEBUG        4U
#define NRF_LOG_LEVEL_INTERNAL     5U
#define NRF_LOG_LEVEL_MASK         0x07
#define NRF_LOG_RAW_POS            4U
#define NRF_LOG_RAW                (1U << NRF_LOG_RAW_POS)
#define NRF_LOG_LEVEL_INFO_RAW     (NRF_LOG_RAW | NRF_LOG_LEVEL_INFO)


#define NRF_LOG_COLOR_CODE_DEFAULT "\x1B[0m"
#define NRF_LOG_COLOR_CODE_BLACK   "\x1B[1;30m"
#define NRF_LOG_COLOR_CODE_RED     "\x1B[1;31m"
#define NRF_LOG_COLOR_CODE_GREEN   "\x1B[1;32m"
#define NRF_LOG_COLOR_CODE_YELLOW  "\x1B[1;33m"
#define NRF_LOG_COLOR_CODE_BLUE    "\x1B[1;34m"
#define NRF_LOG_COLOR_CODE_MAGENTA "\x1B[1;35m"
#define NRF_LOG_COLOR_CODE_CYAN    "\x1B[1;36m"
#define NRF_LOG_COLOR_CODE_WHITE   "\x1B[1;37m"

#define NRF_LOG_COLOR_0            NRF_LOG_COLOR_CODE_DEFAULT
#define NRF_LOG_COLOR_1            NRF_LOG_COLOR_CODE_BLACK
#define NRF_LOG_COLOR_2            NRF_LOG_COLOR_CODE_RED
#define NRF_LOG_COLOR_3            NRF_LOG_COLOR_CODE_GREEN
#define NRF_LOG_COLOR_4            NRF_LOG_COLOR_CODE_YELLOW
#define NRF_LOG_COLOR_5            NRF_LOG_COLOR_CODE_BLUE
#define NRF_LOG_COLOR_6            NRF_LOG_COLOR_CODE_MAGENTA
#define NRF_LOG_COLOR_7            NRF_LOG_COLOR_CODE_CYAN
#define NRF_LOG_COLOR_8            NRF_LOG_COLOR_CODE_WHITE

#define NRF_LOG_COLOR_DECODE(N) CONCAT_2(NRF_LOG_COLOR_, N)
#if NRF_LOG_USES_COLORS
#define NRF_LOG_ERROR_COLOR_CODE   NRF_LOG_COLOR_DECODE(NRF_LOG_ERROR_COLOR)
#define NRF_LOG_WARNING_COLOR_CODE NRF_LOG_COLOR_DECODE(NRF_LOG_WARNING_COLOR)
#define NRF_LOG_INFO_COLOR_CODE    NRF_LOG_COLOR_DECODE(NRF_LOG_INFO_COLOR)
#define NRF_LOG_DEBUG_COLOR_CODE   NRF_LOG_COLOR_DECODE(NRF_LOG_DEBUG_COLOR)
#else // NRF_LOG_USES_COLORS
#define NRF_LOG_ERROR_COLOR_CODE
#define NRF_LOG_WARNING_COLOR_CODE
#define NRF_LOG_INFO_COLOR_CODE
#define NRF_LOG_DEBUG_COLOR_CODE
#endif // NRF_LOG_USES_COLORS

#define LOG_INTERNAL_0(type, prefix, str) \
    nrf_log_frontend_std_0(type, prefix str)
#define LOG_INTERNAL_1(type, prefix, str, arg0) \
    nrf_log_frontend_std_1(type, prefix str, arg0)
#define LOG_INTERNAL_2(type, prefix, str, arg0, arg1) \
    nrf_log_frontend_std_2(type, prefix str, arg0, arg1)
#define LOG_INTERNAL_3(type, prefix, str, arg0, arg1, arg2) \
    nrf_log_frontend_std_3(type, prefix str, arg0, arg1, arg2)
#define LOG_INTERNAL_4(type, prefix, str, arg0, arg1, arg2, arg3) \
    nrf_log_frontend_std_4(type, prefix str, arg0, arg1, arg2, arg3)
#define LOG_INTERNAL_5(type, prefix, str, arg0, arg1, arg2, arg3, arg4) \
    nrf_log_frontend_std_5(type, prefix str, arg0, arg1, arg2, arg3, arg4)
#define LOG_INTERNAL_6(type, prefix, str, arg0, arg1, arg2, arg3, arg4, arg5) \
    nrf_log_frontend_std_6(type, prefix str, arg0, arg1, arg2, arg3, arg4, arg5)

#define LOG_INTERNAL_X(N, ...)          CONCAT_2(LOG_INTERNAL_, N) (__VA_ARGS__)
#define LOG_INTERNAL(type, prefix, ...) LOG_INTERNAL_X(NUM_VA_ARGS_LESS_1( \
                                                           __VA_ARGS__), type, prefix, __VA_ARGS__)

#define NRF_LOG_BREAK      ":"

#define LOG_ERROR_PREFIX   NRF_LOG_ERROR_COLOR_CODE NRF_LOG_MODULE_NAME NRF_LOG_BREAK "ERROR:"
#define LOG_WARNING_PREFIX NRF_LOG_WARNING_COLOR_CODE NRF_LOG_MODULE_NAME NRF_LOG_BREAK "WARNING:"
#define LOG_INFO_PREFIX    NRF_LOG_INFO_COLOR_CODE NRF_LOG_MODULE_NAME NRF_LOG_BREAK "INFO:"
#define LOG_DEBUG_PREFIX   NRF_LOG_DEBUG_COLOR_CODE NRF_LOG_MODULE_NAME NRF_LOG_BREAK "DEBUG:"

#define NRF_LOG_INTERNAL_ERROR(...)                                       \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_ERROR) &&                         \
        (NRF_LOG_LEVEL_ERROR <= NRF_LOG_DEFAULT_LEVEL))                   \
    {                                                                     \
        LOG_INTERNAL(NRF_LOG_LEVEL_ERROR, LOG_ERROR_PREFIX, __VA_ARGS__); \
    }
#define NRF_LOG_INTERNAL_HEXDUMP_ERROR(p_data, len)                                              \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_ERROR) &&                                                \
        (NRF_LOG_LEVEL_ERROR <= NRF_LOG_DEFAULT_LEVEL))                                          \
    {                                                                                            \
        nrf_log_frontend_hexdump(NRF_LOG_LEVEL_ERROR, LOG_ERROR_PREFIX "\r\n", (p_data), (len)); \
    }

#define NRF_LOG_INTERNAL_WARNING(...)                                         \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_WARNING) &&                           \
        (NRF_LOG_LEVEL_WARNING <= NRF_LOG_DEFAULT_LEVEL))                     \
    {                                                                         \
        LOG_INTERNAL(NRF_LOG_LEVEL_WARNING, LOG_WARNING_PREFIX, __VA_ARGS__); \
    }
#define NRF_LOG_INTERNAL_HEXDUMP_WARNING(p_data, len)                                                \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_WARNING) &&                                                  \
        (NRF_LOG_LEVEL_WARNING <= NRF_LOG_DEFAULT_LEVEL))                                            \
    {                                                                                                \
        nrf_log_frontend_hexdump(NRF_LOG_LEVEL_WARNING, LOG_WARNING_PREFIX "\r\n", (p_data), (len)); \
    }

#define NRF_LOG_INTERNAL_INFO(...)                                      \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_INFO) &&                        \
        (NRF_LOG_LEVEL_INFO <= NRF_LOG_DEFAULT_LEVEL))                  \
    {                                                                   \
        LOG_INTERNAL(NRF_LOG_LEVEL_INFO, LOG_INFO_PREFIX, __VA_ARGS__); \
    }

#define NRF_LOG_INTERNAL_RAW_INFO(...)                                  \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_INFO) &&                        \
        (NRF_LOG_LEVEL_INFO <= NRF_LOG_DEFAULT_LEVEL))                  \
    {                                                                   \
        LOG_INTERNAL(NRF_LOG_LEVEL_INFO | NRF_LOG_RAW, "", __VA_ARGS__);          \
    }

#define NRF_LOG_INTERNAL_HEXDUMP_INFO(p_data, len)                                             \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_INFO) &&                                               \
        (NRF_LOG_LEVEL_INFO <= NRF_LOG_DEFAULT_LEVEL))                                         \
    {                                                                                          \
        nrf_log_frontend_hexdump(NRF_LOG_LEVEL_INFO, LOG_INFO_PREFIX "\r\n", (p_data), (len)); \
    }

#define NRF_LOG_INTERNAL_RAW_HEXDUMP_INFO(p_data, len)                                             \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_INFO) &&                                               \
        (NRF_LOG_LEVEL_INFO <= NRF_LOG_DEFAULT_LEVEL))                                         \
    {                                                                                          \
        nrf_log_frontend_hexdump(NRF_LOG_LEVEL_INFO | NRF_LOG_RAW, "", (p_data), (len)); \
    }

#define NRF_LOG_INTERNAL_DEBUG(...)                                       \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_DEBUG) &&                         \
        (NRF_LOG_LEVEL_DEBUG <= NRF_LOG_DEFAULT_LEVEL))                   \
    {                                                                     \
        LOG_INTERNAL(NRF_LOG_LEVEL_DEBUG, LOG_DEBUG_PREFIX, __VA_ARGS__); \
    }
#define NRF_LOG_INTERNAL_HEXDUMP_DEBUG(p_data, len)                                              \
    if ((NRF_LOG_LEVEL >= NRF_LOG_LEVEL_DEBUG) &&                                                \
        (NRF_LOG_LEVEL_DEBUG <= NRF_LOG_DEFAULT_LEVEL))                                          \
    {                                                                                            \
        nrf_log_frontend_hexdump(NRF_LOG_LEVEL_DEBUG, LOG_DEBUG_PREFIX "\r\n", (p_data), (len)); \
    }

#if NRF_MODULE_ENABLED(NRF_LOG)
#define NRF_LOG_INTERNAL_GETCHAR()  nrf_log_getchar()
#else
#define NRF_LOG_INTERNAL_GETCHAR()  (void)
#endif

/**
 * @brief A function for logging raw string.
 *
 * @param severity Severity.
 * @param p_str    A pointer to a string.
 */
void nrf_log_frontend_std_0(uint8_t severity, char const * const p_str);

/**
 * @brief A function for logging a formatted string with one argument.
 *
 * @param severity Severity.
 * @param p_str    A pointer to a formatted string.
 * @param val0     An argument.
 */
void nrf_log_frontend_std_1(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0);

/**
 * @brief A function for logging a formatted string with 2 arguments.
 *
 * @param severity   Severity.
 * @param p_str      A pointer to a formatted string.
 * @param val0, val1 Arguments for formatting string.
 */
void nrf_log_frontend_std_2(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1);

/**
 * @brief A function for logging a formatted string with 3 arguments.
 *
 * @param severity         Severity.
 * @param p_str            A pointer to a formatted string.
 * @param val0, val1, val2 Arguments for formatting string.
 */
void nrf_log_frontend_std_3(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2);

/**
 * @brief A function for logging a formatted string with 4 arguments.
 *
 * @param severity               Severity.
 * @param p_str                  A pointer to a formatted string.
 * @param val0, val1, val2, val3 Arguments for formatting string.
 */
void nrf_log_frontend_std_4(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3);

/**
 * @brief A function for logging a formatted string with 5 arguments.
 *
 * @param severity                     Severity.
 * @param p_str                        A pointer to a formatted string.
 * @param val0, val1, val2, val3, val4 Arguments for formatting string.
 */
void nrf_log_frontend_std_5(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3,
                            uint32_t           val4);

/**
 * @brief A function for logging a formatted string with 6 arguments.
 *
 * @param severity                           Severity.
 * @param p_str                              A pointer to a formatted string.
 * @param val0, val1, val2, val3, val4, val5 Arguments for formatting string.
 */
void nrf_log_frontend_std_6(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3,
                            uint32_t           val4,
                            uint32_t           val5);

/**
 * @brief A function for logging raw data.
 *
 * @param severity Severity.
 * @param p_str    A pointer to a string which is prefixing the data.
 * @param p_data   A pointer to data to be dumped.
 * @param length   Length of data (in bytes).
 *
 */
void nrf_log_frontend_hexdump(uint8_t            severity,
                              char const * const p_str,
                              const void * const p_data,
                              uint16_t           length);

/**
 * @brief A function for reading a byte from log backend.
 *
 * @return Byte.
 */
uint8_t nrf_log_getchar(void);
#endif // NRF_LOG_INTERNAL_H__
