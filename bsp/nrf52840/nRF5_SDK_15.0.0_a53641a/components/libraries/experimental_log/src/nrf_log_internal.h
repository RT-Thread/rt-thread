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
#ifndef NRF_LOG_INTERNAL_H__
#define NRF_LOG_INTERNAL_H__
#include "sdk_common.h"
#include "nrf.h"
#include "nrf_error.h"
#include "app_util.h"
#include <stdint.h>
#include <stdbool.h>
#include "nrf_log_instance.h"
#include "nrf_log_types.h"

#ifndef NRF_LOG_ERROR_COLOR
    #define NRF_LOG_ERROR_COLOR NRF_LOG_COLOR_DEFAULT
#endif

#ifndef NRF_LOG_WARNING_COLOR
    #define NRF_LOG_WARNING_COLOR NRF_LOG_COLOR_DEFAULT
#endif

#ifndef NRF_LOG_INFO_COLOR
    #define NRF_LOG_INFO_COLOR NRF_LOG_COLOR_DEFAULT
#endif

#ifndef NRF_LOG_DEBUG_COLOR
    #define NRF_LOG_DEBUG_COLOR NRF_LOG_COLOR_DEFAULT
#endif


#ifndef NRF_LOG_COLOR_DEFAULT
#define NRF_LOG_COLOR_DEFAULT 0
#endif

#ifndef NRF_LOG_DEFAULT_LEVEL
#define NRF_LOG_DEFAULT_LEVEL 0
#endif

#ifndef NRF_LOG_USES_COLORS
#define NRF_LOG_USES_COLORS       0
#endif

#ifndef NRF_LOG_USES_TIMESTAMP
#define NRF_LOG_USES_TIMESTAMP    0
#endif

#ifndef NRF_LOG_FILTERS_ENABLED
#define NRF_LOG_FILTERS_ENABLED   0
#endif

#ifndef NRF_LOG_MODULE_NAME
    #define NRF_LOG_MODULE_NAME app
#endif

#define NRF_LOG_LEVEL_BITS         3
#define NRF_LOG_LEVEL_MASK         ((1UL << NRF_LOG_LEVEL_BITS) - 1)
#define NRF_LOG_MODULE_ID_BITS     16
#define NRF_LOG_MODULE_ID_POS      16


#define NRF_LOG_MAX_NUM_OF_ARGS         6


#if NRF_LOG_FILTERS_ENABLED && NRF_LOG_ENABLED
    #define NRF_LOG_FILTER              NRF_LOG_ITEM_DATA_DYNAMIC(NRF_LOG_MODULE_NAME).filter
    #define NRF_LOG_INST_FILTER(p_inst) (p_inst)->filter
#else
    #undef NRF_LOG_FILTER
    #define NRF_LOG_FILTER              NRF_LOG_SEVERITY_DEBUG
    #define NRF_LOG_INST_FILTER(p_inst) NRF_LOG_SEVERITY_DEBUG
#endif

#if NRF_LOG_ENABLED
#define NRF_LOG_MODULE_ID        NRF_LOG_ITEM_DATA_DYNAMIC(NRF_LOG_MODULE_NAME).module_id
#define NRF_LOG_INST_ID(p_inst)  (p_inst)->module_id
#else
#define NRF_LOG_MODULE_ID       0
#define NRF_LOG_INST_ID(p_inst) 0
#endif


#define LOG_INTERNAL_X(N, ...)          CONCAT_2(LOG_INTERNAL_, N) (__VA_ARGS__)
#define LOG_INTERNAL(type, ...) LOG_INTERNAL_X(NUM_VA_ARGS_LESS_1( \
                                                           __VA_ARGS__), type, __VA_ARGS__)
#if NRF_LOG_ENABLED
#define NRF_LOG_INTERNAL_LOG_PUSH(_str) nrf_log_push(_str)
#define LOG_INTERNAL_0(type, str) \
    nrf_log_frontend_std_0(type, str)
#define LOG_INTERNAL_1(type, str, arg0) \
    /*lint -save -e571*/nrf_log_frontend_std_1(type, str, (uint32_t)(arg0))/*lint -restore*/
#define LOG_INTERNAL_2(type, str, arg0, arg1) \
    /*lint -save -e571*/nrf_log_frontend_std_2(type, str, (uint32_t)(arg0), \
            (uint32_t)(arg1))/*lint -restore*/
#define LOG_INTERNAL_3(type, str, arg0, arg1, arg2) \
    /*lint -save -e571*/nrf_log_frontend_std_3(type, str, (uint32_t)(arg0), \
            (uint32_t)(arg1), (uint32_t)(arg2))/*lint -restore*/
#define LOG_INTERNAL_4(type, str, arg0, arg1, arg2, arg3) \
    /*lint -save -e571*/nrf_log_frontend_std_4(type, str, (uint32_t)(arg0), \
            (uint32_t)(arg1), (uint32_t)(arg2), (uint32_t)(arg3))/*lint -restore*/
#define LOG_INTERNAL_5(type, str, arg0, arg1, arg2, arg3, arg4) \
    /*lint -save -e571*/nrf_log_frontend_std_5(type, str, (uint32_t)(arg0), \
            (uint32_t)(arg1), (uint32_t)(arg2), (uint32_t)(arg3), (uint32_t)(arg4))/*lint -restore*/
#define LOG_INTERNAL_6(type, str, arg0, arg1, arg2, arg3, arg4, arg5) \
    /*lint -save -e571*/nrf_log_frontend_std_6(type, str, (uint32_t)(arg0), \
            (uint32_t)(arg1), (uint32_t)(arg2), (uint32_t)(arg3), (uint32_t)(arg4), (uint32_t)(arg5))/*lint -restore*/


#else //NRF_LOG_ENABLED
#define NRF_LOG_INTERNAL_LOG_PUSH(_str) (void)(_str)
#define LOG_INTERNAL_0(_type, _str) \
               (void)(_type); (void)(_str)
#define LOG_INTERNAL_1(_type, _str, _arg0) \
               (void)(_type); (void)(_str); (void)(_arg0)
#define LOG_INTERNAL_2(_type, _str, _arg0, _arg1) \
               (void)(_type); (void)(_str); (void)(_arg0); (void)(_arg1)
#define LOG_INTERNAL_3(_type, _str, _arg0, _arg1, _arg2) \
               (void)(_type); (void)(_str); (void)(_arg0); (void)(_arg1); (void)(_arg2)
#define LOG_INTERNAL_4(_type, _str, _arg0, _arg1, _arg2, _arg3) \
               (void)(_type); (void)(_str); (void)(_arg0); (void)(_arg1); (void)(_arg2); (void)(_arg3)
#define LOG_INTERNAL_5(_type, _str, _arg0, _arg1, _arg2, _arg3, _arg4) \
               (void)(_type); (void)(_str); (void)(_arg0); (void)(_arg1); (void)(_arg2); (void)(_arg3); (void)(_arg4)
#define LOG_INTERNAL_6(_type, _str, _arg0, _arg1, _arg2, _arg3, _arg4, _arg5) \
               (void)(_type); (void)(_str); (void)(_arg0); (void)(_arg1); (void)(_arg2); (void)(_arg3); (void)(_arg4); (void)(_arg5)
#endif //NRF_LOG_ENABLED

#define LOG_SEVERITY_MOD_ID(severity) ((severity) | NRF_LOG_MODULE_ID << NRF_LOG_MODULE_ID_POS)
#define LOG_SEVERITY_INST_ID(severity,p_inst) ((severity) | NRF_LOG_INST_ID(p_inst) << NRF_LOG_MODULE_ID_POS)

#if NRF_LOG_ENABLED
#define LOG_HEXDUMP(_severity, _p_data, _length) \
            nrf_log_frontend_hexdump((_severity), (_p_data), (_length))
#else
#define LOG_HEXDUMP(_severity, _p_data, _length) \
             (void)(_severity); (void)(_p_data); (void)_length
#endif

#define NRF_LOG_INTERNAL_INST(level, level_id, p_inst, ...)                              \
    if (NRF_LOG_ENABLED && (NRF_LOG_LEVEL >= level) &&                                   \
        (level <= NRF_LOG_DEFAULT_LEVEL))                                                \
    {                                                                                    \
        if (NRF_LOG_INST_FILTER(p_inst) >= level)                                        \
        {                                                                                \
            LOG_INTERNAL(LOG_SEVERITY_INST_ID(level_id, p_inst), __VA_ARGS__);           \
        }                                                                                \
    }

#define NRF_LOG_INTERNAL_MODULE(level, level_id, ...)                                    \
    if (NRF_LOG_ENABLED && (NRF_LOG_LEVEL >= level) &&                                   \
        (level <= NRF_LOG_DEFAULT_LEVEL))                                                \
    {                                                                                    \
        if (NRF_LOG_FILTER >= level)                                                     \
        {                                                                                \
            LOG_INTERNAL(LOG_SEVERITY_MOD_ID(level_id), __VA_ARGS__);                    \
        }                                                                                \
    }

#define NRF_LOG_INTERNAL_HEXDUMP_INST(level, level_id, p_inst, p_data, len)        \
    if (NRF_LOG_ENABLED && (NRF_LOG_LEVEL >= level) &&                             \
        (level <= NRF_LOG_DEFAULT_LEVEL))                                          \
    {                                                                              \
        if (NRF_LOG_INST_FILTER(p_inst) >= level)                                  \
        {                                                                          \
            LOG_HEXDUMP(LOG_SEVERITY_INST_ID(level_id, p_inst),                    \
                                     (p_data), (len));                             \
        }                                                                          \
    }

#define NRF_LOG_INTERNAL_HEXDUMP_MODULE(level, level_id, p_data, len)              \
    if (NRF_LOG_ENABLED && (NRF_LOG_LEVEL >= level) &&                             \
        (level <= NRF_LOG_DEFAULT_LEVEL))                                          \
    {                                                                              \
        if (NRF_LOG_FILTER >= level)                                               \
        {                                                                          \
            LOG_HEXDUMP(LOG_SEVERITY_MOD_ID(level_id),                             \
                                     (p_data), (len));                             \
        }                                                                          \
    }

#define NRF_LOG_INTERNAL_INST_ERROR(p_inst, ...) \
                NRF_LOG_INTERNAL_INST(NRF_LOG_SEVERITY_ERROR, NRF_LOG_SEVERITY_ERROR, p_inst, __VA_ARGS__)

#define NRF_LOG_INTERNAL_ERROR(...) \
                NRF_LOG_INTERNAL_MODULE(NRF_LOG_SEVERITY_ERROR, NRF_LOG_SEVERITY_ERROR,__VA_ARGS__)

#define NRF_LOG_INTERNAL_HEXDUMP_INST_ERROR(p_inst, p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_INST(NRF_LOG_SEVERITY_ERROR, NRF_LOG_SEVERITY_ERROR, p_inst, p_data, len)

#define NRF_LOG_INTERNAL_HEXDUMP_ERROR(p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_MODULE(NRF_LOG_SEVERITY_ERROR, NRF_LOG_SEVERITY_ERROR, p_data, len)

#define NRF_LOG_INTERNAL_INST_WARNING(p_inst, ...) \
            NRF_LOG_INTERNAL_INST(NRF_LOG_SEVERITY_WARNING, NRF_LOG_SEVERITY_WARNING, p_inst, __VA_ARGS__)

#define NRF_LOG_INTERNAL_WARNING(...) \
            NRF_LOG_INTERNAL_MODULE(NRF_LOG_SEVERITY_WARNING, NRF_LOG_SEVERITY_WARNING,__VA_ARGS__)

#define NRF_LOG_INTERNAL_HEXDUMP_INST_WARNING(p_inst, p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_INST(NRF_LOG_SEVERITY_WARNING, NRF_LOG_SEVERITY_WARNING, p_inst, p_data, len)

#define NRF_LOG_INTERNAL_HEXDUMP_WARNING(p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_(NRF_LOG_SEVERITY_WARNING, NRF_LOG_SEVERITY_WARNING, p_data, len)

#define NRF_LOG_INTERNAL_INST_INFO(p_inst, ...) \
        NRF_LOG_INTERNAL_INST(NRF_LOG_SEVERITY_INFO, NRF_LOG_SEVERITY_INFO, p_inst, __VA_ARGS__)

#define NRF_LOG_INTERNAL_INFO(...) \
        NRF_LOG_INTERNAL_MODULE(NRF_LOG_SEVERITY_INFO, NRF_LOG_SEVERITY_INFO, __VA_ARGS__)

#define NRF_LOG_INTERNAL_HEXDUMP_INST_INFO(p_inst, p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_INST(NRF_LOG_SEVERITY_INFO, NRF_LOG_SEVERITY_INFO, p_inst, p_data, len)

#define NRF_LOG_INTERNAL_HEXDUMP_INFO(p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_MODULE(NRF_LOG_SEVERITY_INFO, NRF_LOG_SEVERITY_INFO, p_data, len)

#define NRF_LOG_INTERNAL_RAW_INFO(...) \
        NRF_LOG_INTERNAL_MODULE(NRF_LOG_SEVERITY_INFO, NRF_LOG_SEVERITY_INFO_RAW, __VA_ARGS__)

#define NRF_LOG_INTERNAL_RAW_HEXDUMP_INFO(p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_MODULE(NRF_LOG_SEVERITY_INFO, NRF_LOG_SEVERITY_INFO_RAW, p_data, len)

#define NRF_LOG_INTERNAL_INST_DEBUG(p_inst, ...) \
        NRF_LOG_INTERNAL_INST(NRF_LOG_SEVERITY_DEBUG, NRF_LOG_SEVERITY_DEBUG, p_inst, __VA_ARGS__)

#define NRF_LOG_INTERNAL_DEBUG(...) \
        NRF_LOG_INTERNAL_MODULE(NRF_LOG_SEVERITY_DEBUG, NRF_LOG_SEVERITY_DEBUG, __VA_ARGS__)

#define NRF_LOG_INTERNAL_HEXDUMP_INST_DEBUG(p_inst, p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_INST(NRF_LOG_SEVERITY_DEBUG, NRF_LOG_SEVERITY_DEBUG, p_inst, p_data, len)

#define NRF_LOG_INTERNAL_HEXDUMP_DEBUG(p_data, len) \
        NRF_LOG_INTERNAL_HEXDUMP_MODULE(NRF_LOG_SEVERITY_DEBUG, NRF_LOG_SEVERITY_DEBUG, p_data, len)


#if NRF_LOG_ENABLED

#ifdef UNIT_TEST
#define COMPILED_LOG_LEVEL 4
#else
#define COMPILED_LOG_LEVEL NRF_LOG_LEVEL
#endif


#define NRF_LOG_INTERNAL_MODULE_REGISTER() \
                   NRF_LOG_INTERNAL_ITEM_REGISTER(NRF_LOG_MODULE_NAME,                 \
                                                  STRINGIFY(NRF_LOG_MODULE_NAME),      \
                                                  NRF_LOG_INFO_COLOR,                  \
                                                  NRF_LOG_DEBUG_COLOR,                 \
                                                  NRF_LOG_INITIAL_LEVEL,               \
                                                  COMPILED_LOG_LEVEL)

#else
#define NRF_LOG_INTERNAL_MODULE_REGISTER() /*lint -save -e19*/ /*lint -restore*/
#endif

extern NRF_LOG_DYNAMIC_STRUCT_NAME NRF_LOG_ITEM_DATA_DYNAMIC(NRF_LOG_MODULE_NAME);

/**
 * Set of macros for encoding and decoding header for log entries.
 * There are 3 types of entries:
 * 1. Standard entry (STD)
 *    An entry consists of header, pointer to string and values. Header contains
 *    severity leveland determines number of arguments and thus size of the entry.
 *    Since flash address space starts from 0x00000000 and is limited to kB rather
 *    than MB 22 bits are used to store the address (4MB). It is used that way to
 *    save one RAM memory.
 *
 *    --------------------------------
 *    |TYPE|SEVERITY|NARGS|    P_STR |
 *    |------------------------------|
 *    |    Module_ID (optional)      |
 *    |------------------------------|
 *    |    TIMESTAMP (optional)      |
 *    |------------------------------|
 *    |             ARG0             |
 *    |------------------------------|
 *    |             ....             |
 *    |------------------------------|
 *    |             ARG(nargs-1)     |
 *    --------------------------------
 *
 * 2. Hexdump entry (HEXDUMP) is used for dumping raw data. An entry consists of
 *    header, optional timestamp, pointer to string and data. A header contains
 *    length (10bit) and offset which is updated after backend processes part of
 *    data.
 *
 *    --------------------------------
 *    |TYPE|SEVERITY|NARGS|OFFSET|LEN|
 *    |------------------------------|
 *    |    Module_ID (optional)      |
 *    |------------------------------|
 *    |    TIMESTAMP (optional)      |
 *    |------------------------------|
 *    |           P_STR              |
 *    |------------------------------|
 *    |             data             |
 *    |------------------------------|
 *    |  data |       dummy          |
 *    --------------------------------
 *
 * 3. Pushed string. If string is pushed into the logger internal buffer it is
 *    stored as PUSHED entry. It consists of header, unused data (optional) and
 *    string. Unused data is present if string does not not fit into a buffer
 *    without wrapping (and string cannot be wrapped). In that case header
 *    contains information about offset.
 *
 *    --------------------------------
 *    |TYPE| OFFSET   |      LEN     |
 *    |------------------------------|
 *    |           OFFSET             |
 *    |------------------------------|
 * end|           OFFSET             |
 *   0|------------------------------|
 *    |           STRING             |
 *    |------------------------------|
 *    |  STRING |     dummy          |
 *    --------------------------------
 */

#define STD_ADDR_MASK       ((uint32_t)(1U << 22) - 1U)
#define HEADER_TYPE_STD     1U
#define HEADER_TYPE_HEXDUMP 2U
#define HEADER_TYPE_PUSHED  0U
#define HEADER_TYPE_INVALID 3U

typedef struct
{
    uint32_t type       : 2;
    uint32_t in_progress: 1;
    uint32_t data       : 29;
} nrf_log_generic_header_t;

typedef struct
{
    uint32_t type       : 2;
    uint32_t in_progress: 1;
    uint32_t severity   : 3;
    uint32_t nargs      : 4;
    uint32_t addr       : 22;
} nrf_log_std_header_t;

typedef struct
{
    uint32_t type       : 2;
    uint32_t in_progress: 1;
    uint32_t severity   : 3;
    uint32_t offset     : 10;
    uint32_t reserved   : 6;
    uint32_t len        : 10;
} nrf_log_hexdump_header_t;

typedef struct
{
    uint32_t type       : 2;
    uint32_t reserved0  : 4;
    uint32_t offset     : 10;
    uint32_t reserved1  : 6;
    uint32_t len        : 10;
} nrf_log_pushed_header_t;

typedef union
{
    nrf_log_generic_header_t generic;
    nrf_log_std_header_t     std;
    nrf_log_hexdump_header_t hexdump;
    nrf_log_pushed_header_t  pushed;
    uint32_t                 raw;
} nrf_log_main_header_t;

typedef struct
{
    nrf_log_main_header_t base;
    uint16_t module_id;
    uint16_t dropped;
    uint32_t timestamp;
} nrf_log_header_t;

#define HEADER_SIZE         (sizeof(nrf_log_header_t)/sizeof(uint32_t) - \
                (NRF_LOG_USES_TIMESTAMP ? 0 : 1))

#define PUSHED_HEADER_SIZE (sizeof(nrf_log_pushed_header_t)/sizeof(uint32_t))

//Implementation assumes that pushed header has one word.
STATIC_ASSERT(PUSHED_HEADER_SIZE == 1);
/**
 * @brief A function for logging raw string.
 *
 * @param severity_mid Severity.
 * @param p_str        A pointer to a string.
 */
void nrf_log_frontend_std_0(uint32_t severity_mid, char const * const p_str);

/**
 * @brief A function for logging a formatted string with one argument.
 *
 * @param severity_mid  Severity.
 * @param p_str         A pointer to a formatted string.
 * @param val0          An argument.
 */
void nrf_log_frontend_std_1(uint32_t           severity_mid,
                            char const * const p_str,
                            uint32_t           val0);

/**
 * @brief A function for logging a formatted string with 2 arguments.
 *
 * @param severity_mid   Severity.
 * @param p_str          A pointer to a formatted string.
 * @param val0, val1     Arguments for formatting string.
 */
void nrf_log_frontend_std_2(uint32_t           severity_mid,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1);

/**
 * @brief A function for logging a formatted string with 3 arguments.
 *
 * @param severity_mid     Severity.
 * @param p_str            A pointer to a formatted string.
 * @param val0, val1, val2 Arguments for formatting string.
 */
void nrf_log_frontend_std_3(uint32_t           severity_mid,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2);

/**
 * @brief A function for logging a formatted string with 4 arguments.
 *
 * @param severity_mid           Severity.
 * @param p_str                  A pointer to a formatted string.
 * @param val0, val1, val2, val3 Arguments for formatting string.
 */
void nrf_log_frontend_std_4(uint32_t           severity_mid,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3);

/**
 * @brief A function for logging a formatted string with 5 arguments.
 *
 * @param severity_mid                 Severity.
 * @param p_str                        A pointer to a formatted string.
 * @param val0, val1, val2, val3, val4 Arguments for formatting string.
 */
void nrf_log_frontend_std_5(uint32_t           severity_mid,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3,
                            uint32_t           val4);

/**
 * @brief A function for logging a formatted string with 6 arguments.
 *
 * @param severity_mid                       Severity.
 * @param p_str                              A pointer to a formatted string.
 * @param val0, val1, val2, val3, val4, val5 Arguments for formatting string.
 */
void nrf_log_frontend_std_6(uint32_t           severity_mid,
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
 * @param severity_mid Severity.
 * @param p_str        A pointer to a string which is prefixing the data.
 * @param p_data       A pointer to data to be dumped.
 * @param length       Length of data (in bytes).
 *
 */
void nrf_log_frontend_hexdump(uint32_t           severity_mid,
                              const void * const p_data,
                              uint16_t           length);

/**
 * @brief A function for reading a byte from log backend.
 *
 * @return Byte.
 */
uint8_t nrf_log_getchar(void);
#endif // NRF_LOG_INTERNAL_H__
