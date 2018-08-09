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
/**@file socket_trace.h
 *
 * @defgroup iot_socket_debug_log Module's log macros
 * @ingroup iot_sdk_socket
 * @{
 * @brief Socket trace macros.
 *
 * @details Macros for creating module logs which can be useful in understanding the handling
 *          of events or actions on API requests. These are intended for debugging purposes and
 *          can be disabled by defining the SOCKET_CONFIG_LOG_ENABLED.
 * @note If NRF_LOG_ENABLED is disabled, SOCKET_CONFIG_LOG_ENABLED has no effect.
 */
#ifndef SOCKET_TRACE_H__
#define SOCKET_TRACE_H__

#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if SOCKET_CONFIG_LOG_ENABLED == 1
#if defined (NRF_LOG_ENABLED) && (NRF_LOG_ENABLED == 1)

#define NRF_LOG_MODULE_NAME socket

#define NRF_LOG_LEVEL       SOCKET_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  SOCKET_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR SOCKET_CONFIG_DEBUG_COLOR

#include "nrf_log.h"

#define SOCKET_TRACE   NRF_LOG_DEBUG                 /**< Used for getting trace of execution in the module. */
#define SOCKET_ERR     NRF_LOG_ERROR                 /**< Used for logging errors in the module. */
#define SOCKET_DUMP    NRF_LOG_HEXDUMP_DEBUG         /**< Used for dumping octet information to get details of bond information etc. */

#else

#define SOCKET_TRACE(...)                       \
    do {                                        \
        (void) fprintf( stderr, "socket: " );   \
        (void) fprintf( stderr, __VA_ARGS__ );  \
        (void) fprintf( stderr, "\r\n" );       \
    } while (0)

#endif

#else // SOCKET_CONFIG_LOG_ENABLED

#define SOCKET_TRACE(...)                            /**< Disables traces. */
#define SOCKET_ERR(...)                              /**< Disables error logs. */
#define SOCKET_DUMP(...)                             /**< Disables dumping of octet streams. */

#endif // SOCKET_CONFIG_LOG_ENABLED


#ifdef __cplusplus
}
#endif

#endif // SOCKET_TRACE_H__

/**@} */
