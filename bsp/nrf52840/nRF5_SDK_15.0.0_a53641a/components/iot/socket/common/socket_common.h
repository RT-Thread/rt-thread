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
/**@file socket_common.h
 *
 * @defgroup socket_common BSD Socket internal functions and structures
 * @ingroup iot_sdk_socket
 * @{
 * @brief Nordic socket interface internal functions and structures.
 */
#ifndef SOCKET_COMMON_H__
#define SOCKET_COMMON_H__

#include <stdint.h>
#include "socket_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct socket_transport;

#define AF_NRF_CFG_INTERNAL 41 /**< Socket family type, internal NRF configuration socket. */

/**
 * @brief Function for initializing the socket API module.
 *
 * @return NRF_SUCCESS on success, otherwise error code is returned.
 */
uint32_t socket_init(void);

/**
 * @brief Waiting function for sockets.
 *
 * @details Must be implemented by specific modules such as BLEs.
 *
 * @return NRF_SUCCESS on success, otherwise error code is returned.
 */
uint32_t socket_wait(void);

/**
 * @brief Create parameters for a socket.
 */
typedef struct {
    socket_family_t   so_family;    /**< Socket family. */
    socket_protocol_t so_protocol;  /**< Socket protocol. */
    socket_type_t     so_type;      /**< Socket type. */
} socket_params_t;

/**
 * @brief Different states a socket can be in.
 */
typedef enum {
    STATE_CLOSED = 0,   /**< Socket is closed. */
    STATE_OPEN,         /**< Socket is opened. */
    STATE_CONNECTED,    /**< Socket is connected. */
} socket_state_t;

/**
 * @brief The state associated with a socket handle.
 */
typedef struct {
    socket_params_t           so_params;     /**< Generic socket parameters.          */
    void                    * so_ctx;        /**< Transport specific context.        */
    int                       so_flags;      /**< Socket flags.                      */
    uint16_t                  so_read_evt;   /**< Notifying of read events.          */
    uint16_t                  so_write_evt;  /**< Notifying of write events.         */
    uint16_t                  so_except_evt; /**< Notifying of exceptional events.   */
    struct socket_transport * so_transport;  /**< Transport attached to this socket. */
    volatile socket_state_t   so_state;      /**< Socket state.                      */
} socket_t;

#ifdef __cplusplus
}
#endif

#endif // SOCKET_COMMON_H__

/**@} */
