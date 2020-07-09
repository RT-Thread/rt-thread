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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_LOG)
#include "app_util.h"
#include "app_util_platform.h"
#include "nrf_log.h"
#include "nrf_log_internal.h"
#include "nrf_log_backend.h"
#include "nrf_log_ctrl.h"
#include <string.h>

#if NRF_LOG_DEFERRED
STATIC_ASSERT((NRF_LOG_DEFERRED_BUFSIZE == 0) || IS_POWER_OF_TWO(NRF_LOG_DEFERRED_BUFSIZE));
#else
#define NRF_LOG_DEFERRED_BUFSIZE 1
#endif

/**
 * brief An internal control block of the logger
 *
 * @note Circular buffer is using never cleared indexes and a mask. It means
 * that logger may break when indexes overflows. However, it is quite unlikely.
 * With rate of 1000 log entries with 2 parameters per second such situation
 * would happen after 12 days.
 */
typedef struct
{
    uint32_t                  wr_idx;          // Current write index (never reset)
    uint32_t                  rd_idx;          // Current read index  (never_reset)
    uint32_t                  mask;            // Size of buffer (must be power of 2) presented as mask
    uint32_t                  buffer[NRF_LOG_DEFERRED_BUFSIZE];
    nrf_log_timestamp_func_t  timestamp_func;  // A pointer to function that returns timestamp
    nrf_log_std_handler_t     std_handler;     // A handler used for processing standard log calls
    nrf_log_hexdump_handler_t hexdump_handler; // A handler for processing hex dumps
} log_data_t;

static log_data_t   m_log_data;
#if (NRF_LOG_DEFERRED == 1)
static const char * m_overflow_info = NRF_LOG_ERROR_COLOR_CODE "Overflow\r\n";
#endif //(NRF_LOG_DEFERRED == 1)

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
#define HEADER_SIZE         ((NRF_LOG_USES_TIMESTAMP) ? 2 : 1)

#define STD_ADDR_MASK       ((uint32_t)(1U << 22) - 1U)
#define HEADER_TYPE_STD     1U
#define HEADER_TYPE_HEXDUMP 2U
#define HEADER_TYPE_PUSHED  0U

typedef struct
{
    uint32_t type       : 2;
    uint32_t raw        : 1;
    uint32_t data       : 29;
} nrf_log_generic_header_t;

typedef struct
{
    uint32_t type       : 2;
    uint32_t raw        : 1;
    uint32_t severity   : 3;
    uint32_t nargs      : 4;
    uint32_t addr       : 22;
} nrf_log_std_header_t;

typedef struct
{
    uint32_t type       : 2;
    uint32_t raw        : 1;
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
} nrf_log_header_t;

/* IAR does not support initialization with non-constant variables */
#if defined ( __ICCARM__ )
#define STD_HEADER_DEF(NAME, P_STR, SEVERITY, NARGS)        \
    nrf_log_header_t NAME = {                               \
        .std = {                                            \
            .type     = HEADER_TYPE_STD,                    \
        }                                                   \
    };                                                      \
    NAME.std.type     = HEADER_TYPE_STD;                    \
    NAME.std.raw      = ((SEVERITY) & NRF_LOG_RAW);         \
    NAME.std.severity = (SEVERITY) & NRF_LOG_LEVEL_MASK;    \
    NAME.std.nargs    = (NARGS);                            \
    NAME.std.addr     = ((uint32_t)(P_STR) & STD_ADDR_MASK)
#else
#define STD_HEADER_DEF(NAME, P_STR, SEVERITY, NARGS)       \
    nrf_log_header_t NAME = {                              \
        .std = {                                           \
            .type     = HEADER_TYPE_STD,                   \
            .raw      = ((SEVERITY) & NRF_LOG_RAW),        \
            .severity = (SEVERITY) & NRF_LOG_LEVEL_MASK,   \
            .nargs    = (NARGS),                           \
            .addr     = ((uint32_t)(P_STR) & STD_ADDR_MASK)\
        }                                                  \
    }
#endif

#if defined ( __ICCARM__ )
#define HEXDUMP_HEADER_DEF(NAME, SEVERITY, LENGTH)          \
    nrf_log_header_t NAME = {                               \
        .hexdump = {                                        \
            .type     = HEADER_TYPE_HEXDUMP,                \
            .offset   = 0,                                  \
        }                                                   \
    };                                                      \
    NAME.hexdump.raw      = ((SEVERITY) & NRF_LOG_RAW);     \
    NAME.hexdump.severity = (SEVERITY) & NRF_LOG_LEVEL_MASK;\
    NAME.hexdump.len      = (LENGTH)

#else
#define HEXDUMP_HEADER_DEF(NAME, SEVERITY, LENGTH)          \
    nrf_log_header_t NAME = {                               \
        .hexdump = {                                        \
            .type     = HEADER_TYPE_HEXDUMP,                \
            .raw      = ((SEVERITY) & NRF_LOG_RAW),         \
            .severity = (SEVERITY) & NRF_LOG_LEVEL_MASK,    \
            .offset   = 0,                                  \
            .len      = LENGTH,                             \
        }                                                   \
    }
#endif

#if defined ( __ICCARM__ )
#define PUSHED_HEADER_DEF(NAME, OFFSET, LENGTH)        \
    nrf_log_header_t NAME = {                          \
        .pushed = {                                    \
            .type   = HEADER_TYPE_PUSHED,              \
        }                                              \
    };                                                 \
    NAME.pushed.offset = (OFFSET);                     \
    NAME.pushed.len   = (LENGTH)

#else
#define PUSHED_HEADER_DEF(NAME, OFFSET, LENGTH)        \
    nrf_log_header_t NAME = {                          \
        .pushed = {                                    \
            .type   = HEADER_TYPE_PUSHED,              \
            .offset = (OFFSET),                        \
            .len    = (LENGTH),                        \
        }                                              \
    }

#endif

ret_code_t nrf_log_init(nrf_log_timestamp_func_t timestamp_func)
{
    if (NRF_LOG_USES_TIMESTAMP && (timestamp_func == NULL))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    ret_code_t err_code = nrf_log_backend_init(NRF_LOG_DEFERRED ? false : true);

    if (err_code == NRF_SUCCESS)
    {
        nrf_log_frontend_init(nrf_log_backend_std_handler_get(),
                              nrf_log_backend_hexdump_handler_get(),
                              timestamp_func);
    }
    return err_code;
}


ret_code_t nrf_log_blocking_backend_set(void)
{
    // Return value is ommited because
    return nrf_log_backend_init(true);
}


void nrf_log_frontend_init(nrf_log_std_handler_t     std_handler,
                           nrf_log_hexdump_handler_t hexdump_handler,
                           nrf_log_timestamp_func_t  timestamp_func)
{
#if NRF_LOG_DEFERRED
    m_log_data.mask   = NRF_LOG_DEFERRED_BUFSIZE - 1;
    m_log_data.wr_idx = 0;
    m_log_data.rd_idx = 0;
#endif //NRF_LOG_DEFERRED
#if NRF_LOG_USES_TIMESTAMP
    m_log_data.timestamp_func = timestamp_func;
#endif //NRF_LOG_USES_TIMESTAMP
    nrf_log_handlers_set(std_handler, hexdump_handler);
}


void nrf_log_handlers_set(nrf_log_std_handler_t     std_handler,
                          nrf_log_hexdump_handler_t hexdump_handler)
{
    m_log_data.std_handler     = std_handler;
    m_log_data.hexdump_handler = hexdump_handler;
}

#if (NRF_LOG_DEFERRED == 1)
/**
 * @brief Allocates chunk in a buffer for one entry and injects overflow if
 * there is no room for requested entry.
 *
 * @param nargs    Number of 32bit arguments. In case of allocating for hex dump it
 * is the size of the buffer in 32bit words (ceiled).
 * @param p_wr_idx Pointer to write index.
 *
 * @return True if successful allocation, false otherwise.
 *
 */
static inline bool buf_prealloc(uint32_t nargs, uint32_t * p_wr_idx)
{
    nargs += HEADER_SIZE;
    uint32_t ovflw_tag_size = HEADER_SIZE;
    bool     ret            = true;
    CRITICAL_REGION_ENTER();
    *p_wr_idx = m_log_data.wr_idx;
    uint32_t available_words = (m_log_data.mask + 1) - (m_log_data.wr_idx - m_log_data.rd_idx);
    uint32_t required_words  = nargs + ovflw_tag_size; // room for current entry and overflow
    if (required_words > available_words)
    {
        if (available_words >= HEADER_SIZE)
        {
            // Overflow entry is injected
            STD_HEADER_DEF(header, m_overflow_info, NRF_LOG_LEVEL_INTERNAL, 0);
            m_log_data.buffer[m_log_data.wr_idx++ & m_log_data.mask] =
                header.raw;
#if NRF_LOG_USES_TIMESTAMP
            m_log_data.buffer[m_log_data.wr_idx++ & m_log_data.mask] =
                m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        }
        // overflow case
        ret = false;
    }
    else
    {
        m_log_data.wr_idx += nargs;
    }
    CRITICAL_REGION_EXIT();
    return ret;
}


/**
 * @brief Function for preallocating a continuous chunk of memory from circular buffer.
 *
 * If buffer does not fit starting from current position it will be allocated at
 * the beginning of the circular buffer and offset will be returned indicating
 * how much memory has been ommited at the end of the buffer. Function is
 * using critical section.
 *
 * @param len32    Length of buffer to allocate. Given in words.
 * @param p_offset Offset of the buffer.
 * @param p_wr_idx Pointer to write index.
 *
 * @return A pointer to the allocated buffer. NULL if allocation failed.
 */
static inline uint32_t * cont_buf_prealloc(uint32_t len32,
                                           uint32_t * p_offset,
                                           uint32_t * p_wr_idx)
{
    uint32_t * p_buf = NULL;

    len32++; // Increment because 32bit header is needed to be stored.

    CRITICAL_REGION_ENTER();
    *p_wr_idx = m_log_data.wr_idx;
    uint32_t available_words = (m_log_data.mask + 1) -
                               (m_log_data.wr_idx & m_log_data.mask);
    if (len32 <= available_words)
    {
        // buffer will fit as is
        p_buf              = &m_log_data.buffer[(m_log_data.wr_idx + 1) & m_log_data.mask];
        m_log_data.wr_idx += len32;
        *p_offset          = 0;
    }
    else if (len32 < (m_log_data.rd_idx & m_log_data.mask))
    {
        // wraping to the begining of the buffer
        m_log_data.wr_idx += (len32 + available_words - 1);
        *p_offset          = available_words - 1;
        p_buf              = m_log_data.buffer;
    }
    available_words = (m_log_data.mask + 1) - (m_log_data.wr_idx - m_log_data.rd_idx);
    // If there is no more room for even overflow tag indicate failed allocation.
    if (available_words < HEADER_SIZE)
    {
        p_buf = NULL;
    }
    CRITICAL_REGION_EXIT();

    return p_buf;
}
#endif //(NRF_LOG_DEFERRED == 1)


#if (NRF_LOG_DEFERRED == 0)
static inline void nrf_log_direct_feed(uint8_t            type,
                                       char const * const p_str,
                                       uint32_t         * p_args,
                                       uint32_t           nargs)
{
    uint32_t   timestamp   = 0;
    uint32_t * p_timestamp = NRF_LOG_USES_TIMESTAMP ? &timestamp : NULL;

#if NRF_LOG_USES_TIMESTAMP
    timestamp = m_log_data.timestamp_func();
#else //NRF_LOG_USES_TIMESTAMP
    UNUSED_VARIABLE(timestamp);
#endif //NRF_LOG_USES_TIMESTAMP

    UNUSED_VARIABLE
      (m_log_data.std_handler(type, p_timestamp, (char *)p_str, p_args, nargs));

}
#endif //(NRF_LOG_DEFERRED == 0)


uint32_t nrf_log_push(char * const p_str)
{
#if (NRF_LOG_DEFERRED == 0)
    return (uint32_t)p_str;
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t mask      = m_log_data.mask;
    uint32_t slen      = strlen(p_str) + 1;
    uint32_t buflen    = CEIL_DIV(slen, 4);
    uint32_t offset    = 0;
    uint32_t wr_idx;
    char   * p_dst_str = (char *)cont_buf_prealloc(buflen, &offset, &wr_idx);
    if (p_dst_str)
    {
        PUSHED_HEADER_DEF(header, offset, buflen);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
        memcpy(p_dst_str, p_str, slen);
    }
    return (uint32_t)p_dst_str;
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_std_0(uint8_t severity, char const * const p_str)
{
#if (NRF_LOG_DEFERRED == 0)
    nrf_log_direct_feed(severity, p_str, NULL, 0);
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t nargs  = 0;
    uint32_t mask   = m_log_data.mask;
    uint32_t wr_idx;
    if (buf_prealloc(nargs, &wr_idx))
    {
        // Proceed only if buffer was successfully preallocated.
        STD_HEADER_DEF(header, p_str, severity, nargs);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_std_1(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0)
{
#if (NRF_LOG_DEFERRED == 0)
    uint32_t args[] = {val0};
    nrf_log_direct_feed(severity, p_str, args, ARRAY_SIZE(args));
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t nargs  = 1;
    uint32_t mask   = m_log_data.mask;
    uint32_t wr_idx;
    if (buf_prealloc(nargs, &wr_idx))
    {
        // Proceed only if buffer was successfully preallocated.
        STD_HEADER_DEF(header, p_str, severity, nargs);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx & mask] = val0;
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_std_2(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1)
{
#if (NRF_LOG_DEFERRED == 0)
    uint32_t args[] = {val0, val1};
    nrf_log_direct_feed(severity, p_str, args, ARRAY_SIZE(args));
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t nargs  = 2;
    uint32_t mask   = m_log_data.mask;
    uint32_t wr_idx;
    if (buf_prealloc(nargs, &wr_idx))
    {
        // Proceed only if buffer was successfully preallocated.
        STD_HEADER_DEF(header, p_str, severity, nargs);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = val0;
        m_log_data.buffer[wr_idx & mask]   = val1;
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_std_3(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2)
{
#if (NRF_LOG_DEFERRED == 0)
    uint32_t args[] = {val0, val1, val2};
    nrf_log_direct_feed(severity, p_str, args, ARRAY_SIZE(args));
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t nargs  = 3;
    uint32_t mask   = m_log_data.mask;
    uint32_t wr_idx;
    if (buf_prealloc(nargs, &wr_idx))
    {
        // Proceed only if buffer was successfully preallocated.
        STD_HEADER_DEF(header, p_str, severity, nargs);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = val0;
        m_log_data.buffer[wr_idx++ & mask] = val1;
        m_log_data.buffer[wr_idx & mask]   = val2;
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_std_4(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3)
{
#if (NRF_LOG_DEFERRED == 0)
    uint32_t args[] = {val0, val1, val2, val3};
    nrf_log_direct_feed(severity, p_str, args, ARRAY_SIZE(args));
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t nargs  = 4;
    uint32_t mask   = m_log_data.mask;
    uint32_t wr_idx;
    if (buf_prealloc(nargs, &wr_idx))
    {
        // Proceed only if buffer was successfully preallocated.
        STD_HEADER_DEF(header, p_str, severity, nargs);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = val0;
        m_log_data.buffer[wr_idx++ & mask] = val1;
        m_log_data.buffer[wr_idx++ & mask] = val2;
        m_log_data.buffer[wr_idx & mask]   = val3;
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_std_5(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3,
                            uint32_t           val4)
{
#if (NRF_LOG_DEFERRED == 0)
    uint32_t args[] = {val0, val1, val2, val3, val4};
    nrf_log_direct_feed(severity, p_str, args, ARRAY_SIZE(args));
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t nargs  = 5;
    uint32_t mask   = m_log_data.mask;
    uint32_t wr_idx;
    if (buf_prealloc(nargs, &wr_idx))
    {
        // Proceed only if buffer was successfully preallocated.
        STD_HEADER_DEF(header, p_str, severity, nargs);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = val0;
        m_log_data.buffer[wr_idx++ & mask] = val1;
        m_log_data.buffer[wr_idx++ & mask] = val2;
        m_log_data.buffer[wr_idx++ & mask] = val3;
        m_log_data.buffer[wr_idx & mask]   = val4;
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_std_6(uint8_t            severity,
                            char const * const p_str,
                            uint32_t           val0,
                            uint32_t           val1,
                            uint32_t           val2,
                            uint32_t           val3,
                            uint32_t           val4,
                            uint32_t           val5)
{
#if (NRF_LOG_DEFERRED == 0)
    uint32_t args[] = {val0, val1, val2, val3, val4, val5};
    nrf_log_direct_feed(severity, p_str, args, ARRAY_SIZE(args));
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t nargs  = 6;
    uint32_t mask   = m_log_data.mask;
    uint32_t wr_idx;
    if (buf_prealloc(nargs, &wr_idx))
    {
        // Proceed only if buffer was successfully preallocated.
        STD_HEADER_DEF(header, p_str, severity, nargs);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = val0;
        m_log_data.buffer[wr_idx++ & mask] = val1;
        m_log_data.buffer[wr_idx++ & mask] = val2;
        m_log_data.buffer[wr_idx++ & mask] = val3;
        m_log_data.buffer[wr_idx++ & mask] = val4;
        m_log_data.buffer[wr_idx & mask]   = val5;
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


void nrf_log_frontend_hexdump(uint8_t            severity,
                              char const * const p_str,
                              const void * const p_data,
                              uint16_t           length)
{
#if (NRF_LOG_DEFERRED == 0)
    uint32_t timestamp = 0;
#if NRF_LOG_USES_TIMESTAMP
    timestamp = m_log_data.timestamp_func();
#else //NRF_LOG_USES_TIMESTAMP
    (void) timestamp;
#endif //NRF_LOG_USES_TIMESTAMP

    uint32_t curr_offset = 0;

    do
    {
        curr_offset = m_log_data.hexdump_handler(severity,
                                                 NRF_LOG_USES_TIMESTAMP ? &timestamp : NULL,
                                                 p_str,
                                                 curr_offset,
                                                 p_data,
                                                 length,
                                                 NULL,
                                                 0);
    }
    while (curr_offset < length);
#else //(NRF_LOG_DEFERRED == 0)
    uint32_t mask   = m_log_data.mask;

    uint32_t wr_idx;
    if (buf_prealloc(CEIL_DIV(length, 4) + 1, &wr_idx))
    {
        HEXDUMP_HEADER_DEF(header, severity, length);
        m_log_data.buffer[wr_idx++ & mask] = header.raw;
#if NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = m_log_data.timestamp_func();
#endif //NRF_LOG_USES_TIMESTAMP
        m_log_data.buffer[wr_idx++ & mask] = (uint32_t)p_str;
        uint32_t space0 = sizeof(uint32_t) * (m_log_data.mask + 1 - (wr_idx & mask));
        if (length <= space0)
        {
            memcpy(&m_log_data.buffer[wr_idx & mask], p_data, length);
        }
        else
        {
            memcpy(&m_log_data.buffer[wr_idx & mask], p_data, space0);
            length -= space0;
            memcpy(&m_log_data.buffer[0], &((uint8_t *)p_data)[space0], length);
        }
    }
#endif //(NRF_LOG_DEFERRED == 0)
}


bool buffer_is_empty(void)
{
    return (m_log_data.rd_idx == m_log_data.wr_idx);
}


bool nrf_log_frontend_dequeue(void)
{
    if (buffer_is_empty())
    {
        return false;
    }

    uint32_t rd_idx        = m_log_data.rd_idx;
    uint32_t mask          = m_log_data.mask;
    uint32_t header_rd_idx = rd_idx;
    // uint32_t header = m_log_data.buffer[rd_idx++ & mask];
    nrf_log_header_t header;
    header.raw = m_log_data.buffer[rd_idx++ & mask];

    // Skip any string that is pushed to the circular buffer.
    while (header.generic.type == HEADER_TYPE_PUSHED)
    {
        rd_idx       += (header.pushed.len + header.pushed.offset);
        header_rd_idx = rd_idx;
        header.raw    = m_log_data.buffer[rd_idx++ & mask];
    }

    uint32_t * p_timestamp = NRF_LOG_USES_TIMESTAMP ?
                             &m_log_data.buffer[rd_idx++ & mask] : NULL;

    if (header.generic.raw)
    {
        p_timestamp = NULL;
    }

    bool ret = false;
    if (header.generic.type == HEADER_TYPE_HEXDUMP)
    {
        // buffer
        char   * p_str  = (char *)m_log_data.buffer[rd_idx++ & mask];
        uint32_t length = header.hexdump.len;
        uint32_t offset = header.hexdump.offset;
        uint32_t space0 = sizeof(uint32_t) * (mask + 1 - (rd_idx & mask));
        if (length > space0)
        {
            uint8_t * ptr0 = space0 ?
                             (uint8_t *)&m_log_data.buffer[rd_idx & mask] :
                             (uint8_t *)&m_log_data.buffer[0];
            uint8_t   len0 = space0 ? space0 : length;
            uint8_t * ptr1 = space0 ?
                             (uint8_t *)&m_log_data.buffer[0] : NULL;
            uint8_t len1 = space0 ? length - space0 : 0;

            offset = m_log_data.hexdump_handler(header.hexdump.severity,
                                                p_timestamp, p_str,
                                                offset,
                                                ptr0, len0,
                                                ptr1, len1);
        }
        else
        {
            offset = m_log_data.hexdump_handler(
                header.hexdump.severity,
                p_timestamp,
                p_str,
                offset,
                (uint8_t *)&m_log_data.buffer[rd_idx & mask],
                length,
                NULL, 0);
        }

        if (offset == length)
        {
            rd_idx += CEIL_DIV(length, 4);
            ret     = true;
        }
        else
        {
            // If there is more log to process just updated the offset but
            // do not move rd_idx.
            header.hexdump.offset                   = offset;
            m_log_data.buffer[header_rd_idx & mask] = header.raw;
        }
    }
    else // standard entry
    {
        uint32_t   args[6];
        uint32_t * p_arg = args;
        char     * p_str = (char *)((uint32_t)header.std.addr);
        uint32_t   nargs = header.std.nargs;

        uint32_t i;

        for (i = 0; i < nargs; i++)
        {
            *p_arg = m_log_data.buffer[rd_idx++ & mask];
            p_arg++;
        }

        ret = m_log_data.std_handler(header.std.severity,
                                     p_timestamp,
                                     p_str, args, nargs);
    }
    if (ret)
    {
        m_log_data.rd_idx = rd_idx;
    }
    return buffer_is_empty() ? false : true;

}

uint8_t nrf_log_getchar(void)
{
    return nrf_log_backend_getchar();
}

#endif // NRF_MODULE_ENABLED(NRF_LOG)
