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
#include "iot_defines.h"
#include "iot_errors.h"
#include "sdk_config.h"
#include "socket_trace.h"
#include "socket_common.h"
#include "socket_config.h"
#include "config_medium.h"
#include "transport_if.h"
#include "udp_api.h"
#include "portdb.h"
#include "nrf_soc.h"
#include "nrf_fifo.h"

/**@brief Verify that IPv6 address length is correct. */
#define VERIFY_ADDRESS_LEN(len)                          \
    do {                                                 \
        if ((len) != sizeof(sockaddr_in6_t)) {           \
            return NRF_ERROR_NULL | IOT_SOCKET_ERR_BASE; \
        }                                                \
    } while (0)

#define SOCKET_MAX_PENDING_PACKETS          32  /**< Maximum number of pending received packets. */

/**@brief Nordic IPv6 handle structure. */
typedef struct
{
    udp6_socket_t socket;       /**< UDP socket. */
    nrf_fifo_t    recv_queue;   /**< Received packets queue. */
    uint16_t      local_port;   /**< Local port number. */
} ipv6_handle_t;

static const char  * unused = "UNUSED";                     /**< A pointer indicating an unused socket. */
static ipv6_handle_t ipv6_handles[SOCKET_MAX_SOCKET_COUNT]; /**< IPv6 handle array. */

void free_pbuffer(void * p_data)
{
    (void) iot_pbuffer_free((iot_pbuffer_t *)p_data, true);
}

static ipv6_handle_t * ipv6_handle_allocate(socket_t * p_socket)
{
    ipv6_handle_t * p_handle = NULL;
    for (uint32_t i = 0; i < SOCKET_MAX_SOCKET_COUNT; i++)
    {
        if (ipv6_handles[i].socket.p_app_data == unused)
        {
            p_handle = &ipv6_handles[i];
            p_handle->socket.p_app_data = p_socket;
            (void) nrf_fifo_init(&p_handle->recv_queue, SOCKET_MAX_PENDING_PACKETS, socket_wait, free_pbuffer);
            uint32_t err_code = udp6_socket_app_data_set(&p_handle->socket);
            if (err_code != NRF_SUCCESS)
            {
                p_handle = NULL;
            }
            break;
        }
    }
    return p_handle;
}

static uint32_t ipv6_handle_free(ipv6_handle_t * p_handle)
{
    p_handle->local_port        = 0;
    p_handle->socket.p_app_data = (void *)unused;
    return udp6_socket_app_data_set(&p_handle->socket);
}

void transport_event_handler(iot_interface_t * p_interface, ipv6_event_t * p_event)
{
    (void) p_interface;

    switch (p_event->event_id)
    {
        case IPV6_EVT_INTERFACE_ADD:
            transport_interface_up();
            break;
        case IPV6_EVT_INTERFACE_DELETE:
            transport_interface_down();
            break;
        case IPV6_EVT_INTERFACE_RX_DATA:
            break;
        default:
            break;
    }
}

void transport_handler_init(void)
{
    ipv6_init_t init_param;
    init_param.p_eui64       = config_medium_local_iid();
    init_param.event_handler = transport_event_handler;

    uint32_t err_code = ipv6_init(&init_param);
    (void) err_code;
    // APP_ERROR_CHECK(err_code);
    for (uint32_t i = 0; i< SOCKET_MAX_SOCKET_COUNT; i++)
    {
        ipv6_handles[i].local_port = 0;
        ipv6_handles[i].socket.socket_id = 0;
        ipv6_handles[i].socket.p_app_data = (void *)unused;
    }
}

static uint32_t ipv6_transport_open(socket_t * p_socket)
{
    uint32_t err_code = NRF_SUCCESS;
    if (p_socket->so_params.so_type != SOCK_DGRAM)
    {
        err_code = SOCKET_UNSUPPORTED_PROTOCOL;
    }
    if (err_code == NRF_SUCCESS)
    {
        ipv6_handle_t * p_ipv6_handle = ipv6_handle_allocate(p_socket);
        if (p_ipv6_handle == NULL)
        {
            err_code = NRF_ERROR_NULL;
        }
        else
        {
            err_code = udp6_socket_allocate(&p_ipv6_handle->socket);
            if (err_code == NRF_SUCCESS)
            {
                p_socket->so_ctx = p_ipv6_handle;
            }
            else
            {
                (void) ipv6_handle_free(p_ipv6_handle);
            }
        }
    }
    return err_code;
}

static uint32_t ipv6_transport_close(socket_t * p_socket)
{
    ipv6_handle_t * p_ipv6_handle = (ipv6_handle_t *) p_socket->so_ctx;
    if (p_ipv6_handle->local_port > 0)
    {
        portdb_free(p_ipv6_handle->local_port);
    }

    uint32_t err_code = udp6_socket_free(&p_ipv6_handle->socket);
    if (err_code == NRF_SUCCESS)
    {
        err_code = ipv6_handle_free(p_ipv6_handle);
    }
    return err_code;
}

static uint32_t ipv6_transport_recv_callback(const udp6_socket_t * p_udp_socket,
                                             const ipv6_header_t * p_ip_header,
                                             const udp6_header_t * p_udp_header,
                                             uint32_t              process_result,
                                             iot_pbuffer_t       * p_rx_packet)
{
    uint32_t        err_code      = process_result;
    socket_t      * p_socket      = (socket_t *)p_udp_socket->p_app_data;
    ipv6_handle_t * p_ipv6_handle = (ipv6_handle_t *)p_socket->so_ctx;
    if (err_code == NRF_SUCCESS)
    {
        err_code = nrf_fifo_enq(&p_ipv6_handle->recv_queue, p_rx_packet, false);
        if (err_code == NRF_SUCCESS)
        {
            p_socket->so_read_evt++;
            err_code = IOT_IPV6_ERR_PENDING;
        }
    }
    return err_code;
}

static uint32_t ipv6_transport_bind(socket_t * p_socket, const void * p_addr, socklen_t addr_len)
{
    VERIFY_ADDRESS_LEN(addr_len);
    const sockaddr_in6_t * p_addr_in6    = (const sockaddr_in6_t *)p_addr;
    ipv6_handle_t        * p_ipv6_handle = (ipv6_handle_t *)p_socket->so_ctx;
    udp6_socket_t        * p_udp_socket  = &p_ipv6_handle->socket;

    p_ipv6_handle->local_port = HTONS(p_addr_in6->sin6_port);
    uint32_t err_code = portdb_register(p_ipv6_handle->local_port);
    if (err_code == NRF_SUCCESS)
    {
        ipv6_addr_t * p_ipv6_addr = (ipv6_addr_t *)&p_addr_in6->sin6_addr;
        err_code = udp6_socket_bind(p_udp_socket, p_ipv6_addr, p_ipv6_handle->local_port);
    }
    if (err_code == NRF_SUCCESS)
    {
        err_code = udp6_socket_recv(p_udp_socket, ipv6_transport_recv_callback);
    }
    return err_code;
}

static uint32_t ipv6_transport_bind_any(ipv6_handle_t * p_ipv6_handle)
{
    udp6_socket_t * p_udp_socket = &p_ipv6_handle->socket;
    uint32_t        err_code     = portdb_alloc(&p_ipv6_handle->local_port);
    if (err_code == NRF_SUCCESS)
    {
        SOCKET_TRACE("Binding to port %hu\r\n", p_ipv6_handle->local_port);
        err_code = udp6_socket_bind(p_udp_socket, IPV6_ADDR_ANY, p_ipv6_handle->local_port);
    }

    if (err_code == NRF_SUCCESS)
    {
        err_code = udp6_socket_recv(p_udp_socket, ipv6_transport_recv_callback);
    }
    return err_code;
}

static uint32_t ipv6_transport_connect(socket_t * p_socket, const void * p_addr, socklen_t addr_len)
{
    VERIFY_ADDRESS_LEN(addr_len);

    ipv6_handle_t        * p_ipv6_handle = (ipv6_handle_t *)p_socket->so_ctx;
    udp6_socket_t        * p_udp_socket  = &p_ipv6_handle->socket;
    const sockaddr_in6_t * p_addr_in6    = (const sockaddr_in6_t *)p_addr;
    uint32_t               err_code      = NRF_SUCCESS;

    // Port might already have been bound with an explicit call to bind()
    if (p_ipv6_handle->local_port == 0)
    {
        err_code = ipv6_transport_bind_any(p_ipv6_handle);
    }

    if (err_code == NRF_SUCCESS)
    {
        // These data structures are compatible, and can therefore be cast
        err_code = udp6_socket_connect(p_udp_socket,
                                       (ipv6_addr_t *)&p_addr_in6->sin6_addr,
                                       HTONS(p_addr_in6->sin6_port));
    }

    return err_code;
}

static uint32_t ipv6_transport_send(socket_t   * p_socket,
                                    const void * p_buf,
                                    uint32_t     len,
                                    int          flags,
                                    const void * p_destaddr,
                                    socklen_t    destaddr_len)
{
    ipv6_handle_t           * p_ipv6_handle = (ipv6_handle_t *)p_socket->so_ctx;
    udp6_socket_t           * p_udp_socket  = &p_ipv6_handle->socket;
    uint32_t                  err_code      = NRF_SUCCESS;
    iot_pbuffer_alloc_param_t pbuff_param;

    // Ensure that port is bound before sending packet
    if (p_ipv6_handle->local_port == 0)
    {
        err_code = ipv6_transport_bind_any(p_ipv6_handle);
    }

    if (err_code == NRF_SUCCESS)
    {
        pbuff_param.flags  = PBUFFER_FLAG_DEFAULT;
        pbuff_param.type   = UDP6_PACKET_TYPE;
        pbuff_param.length = len;

        iot_pbuffer_t * p_buffer = NULL;
        err_code = iot_pbuffer_allocate(&pbuff_param, &p_buffer);
        if (err_code == NRF_SUCCESS)
        {
            memcpy(p_buffer->p_payload, p_buf, len);
            if (p_destaddr != NULL && destaddr_len == sizeof(sockaddr_in6_t))
            {
                sockaddr_in6_t * p_addr_in6 = (sockaddr_in6_t *)p_destaddr;
                err_code = udp6_socket_sendto(p_udp_socket,
                                              (ipv6_addr_t *)&p_addr_in6->sin6_addr,
                                              HTONS(p_addr_in6->sin6_port),
                                              p_buffer);
            }
            else
            {
                err_code = udp6_socket_send(p_udp_socket, p_buffer);
            }
        }
    }
    return err_code;
}

static uint32_t ipv6_transport_recv(socket_t  * p_socket,
                                    void      * p_buf,
                                    uint32_t  * p_sz,
                                    int         flags,
                                    void      * p_srcaddr,
                                    socklen_t * p_srcaddr_len)
{
    if ((p_socket->so_flags & O_NONBLOCK) != 0 &&
        (flags & MSG_WAITALL) == 0)
    {
        flags |= MSG_DONTWAIT;
    }

    ipv6_handle_t * p_ipv6_handle = (ipv6_handle_t *)p_socket->so_ctx;
    iot_pbuffer_t * p_pbuffer     = NULL;
    uint32_t        err_code      = nrf_fifo_deq(&p_ipv6_handle->recv_queue,
                                                 (void **)&p_pbuffer,
                                                 (flags & MSG_DONTWAIT) == 0);
    if (err_code == NRF_SUCCESS)
    {
        uint32_t copy_len = MIN(*p_sz, p_pbuffer->length);
        memcpy(p_buf, p_pbuffer->p_payload, copy_len);
        *p_sz = copy_len;

        if (p_srcaddr != NULL && p_srcaddr_len != NULL)
        {
            const udp6_header_t * p_udp_header  =
                    (udp6_header_t *)(p_pbuffer->p_payload - UDP_HEADER_SIZE);
            const ipv6_header_t * p_ipv6_header =
                    (ipv6_header_t *)(p_pbuffer->p_payload - UDP_HEADER_SIZE - IPV6_IP_HEADER_SIZE);
            sockaddr_in6_t      * p_srcsockaddr = (sockaddr_in6_t *)p_srcaddr;

            *p_srcaddr_len               = sizeof(sockaddr_in6_t);
            p_srcsockaddr->sin6_addr     = *((in6_addr_t *)&p_ipv6_header->srcaddr);
            p_srcsockaddr->sin6_port     = HTONS(p_udp_header->srcport);
            p_srcsockaddr->sin6_len      = *p_srcaddr_len;
            p_srcsockaddr->sin6_family   = AF_INET6;
            p_srcsockaddr->sin6_flowinfo = 0;
            p_srcsockaddr->sin6_scope_id = 0;
        }

        (void) iot_pbuffer_free(p_pbuffer, true);
        p_socket->so_read_evt = 0;
    }
    return err_code;
}

static uint32_t ipv6_transport_listen(socket_t * p_socket, int backlog)
{
    // Ignore as this does not make sense for UDP
    (void) p_socket;
    (void) backlog;
    return NRF_SUCCESS;
}

/**
 * @brief Transport for Nordic IPv6 socket.
 */
socket_transport_t transport_impl =
{
    .open    = ipv6_transport_open,
    .bind    = ipv6_transport_bind,
    .connect = ipv6_transport_connect,
    .send    = ipv6_transport_send,
    .recv    = ipv6_transport_recv,
    .listen  = ipv6_transport_listen,
    .close   = ipv6_transport_close
};
