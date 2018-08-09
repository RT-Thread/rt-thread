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
/**@file transport_if.h
 *
 * @defgroup iot_socket_transport_if Transport implementation interface
 * @ingroup iot_sdk_socket
 * @{
 * @brief Transport implementation interface.
 *
 * The transport interface defines the hook to be used for socket transport. The implementation of
 * this interface would be different across platforms and event IP stacks (i.e. Nordic IPv6 vs LwIP).
 */
#ifndef TRANSPORT_IF_H__
#define TRANSPORT_IF_H__

#include "iot_defines.h"
#include "socket_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Function for opening a socket.
 */
typedef uint32_t (*tr_open_t) (socket_t * p_socket);

/**
 * @brief Function for connecting a socket to an address.
 */
typedef uint32_t (*tr_connect_t)(socket_t * p_socket, const void * p_addr, socklen_t addrlen);

/**
 * @brief Function for sending data on a socket.
 */
typedef uint32_t (*tr_send_t)(socket_t   * p_socket,
                              const void * p_buf,
                              uint32_t     len,
                              int          flags,
                              const void * p_destaddr,
                              socklen_t    destaddr_len);

/**
 * @brief Function for receiving data from a socket.
 */
typedef uint32_t (*tr_recv_t)(socket_t  * p_socket,
                              void      * p_buf,
                              uint32_t  * sz,
                              int         flags,
                              void      * p_srcaddr,
                              socklen_t * p_srcaddr_len);

/**
 * @brief Function for binding a socket to an address and port.
 */
typedef uint32_t (*tr_bind_t)(socket_t * p_socket, const void * p_addr, socklen_t addrlen);

/**
 * @brief Function for listening on a socket.
 */
typedef uint32_t (*tr_listen_t)(socket_t * p_socket, int backlog);

/**
 * @brief Function for accepting a connection on a socket.
 */
typedef uint32_t (*tr_accept_t)(socket_t  * p_socket,
                                socket_t  * p_client,
                                void      * p_client_addr,
                                socklen_t * p_client_addr_len);

/**
 * @brief Function for closing a socket.
 */
typedef uint32_t (*tr_close_t)(socket_t * p_socket);

/**
 * @brief Function for setting options on a socket.
 */
typedef uint32_t (*tr_setsockopt_t)(socket_t   * p_socket,
                                    int          level,
                                    int          optname,
                                    const void * p_optval,
                                    socklen_t    optlen);

/**
 * @brief Function for getting options from a socket.
 */
typedef uint32_t (*tr_getsockopt_t)(socket_t  * p_socket,
                                    int         level,
                                    int         optname,
                                    void      * p_optval,
                                    socklen_t * p_optlen);

/**
 * @brief The transport interface.
 */
typedef struct socket_transport
{
    tr_open_t          open;        /**< Open a socket. */
    tr_connect_t       connect;     /**< Connect a socket to an address. */
    tr_send_t          send;        /**< Send data on a socket. */
    tr_recv_t          recv;        /**< Receive data from a socket. */
    tr_bind_t          bind;        /**< Bind a socket to an address and port. */
    tr_listen_t        listen;      /**< Listen on a socket. */
    tr_accept_t        accept;      /**< Accept connection on a socket. */
    tr_close_t         close;       /**< Close a socket. */
    tr_setsockopt_t    setsockopt;  /**< Set options on a socket. */
    tr_getsockopt_t    getsockopt;  /**< Get options from a socket. */
} socket_transport_t;

#if SOCKET_TRANSPORT_ENABLE == 1
extern socket_transport_t transport_impl;
void transport_handler_init(void);
void transport_interface_up(void);
void transport_interface_down(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // TRANSPORT_IF_H__

/**@} */
