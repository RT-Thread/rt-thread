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
#include "iot_defines.h"
#include "iot_errors.h"
#include "sdk_config.h"
#include "socket_common.h"
#include "socket_trace.h"
#include "transport_if.h"
#include "portdb.h"
#include "app_timer.h"
#include "mem_manager.h"
#include "nrf_fifo.h"
#include "mbuf.h"
#include "app_util.h"
#include "nrf_platform_port.h"
#include "app_util_platform.h"

#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/tcp.h"
#include "lwip/timers.h"

/**@brief Verify that IPv6 address length is correct. */
#define VERIFY_ADDRESS_LEN(len)                          \
    do {                                                 \
        if ((len) != sizeof(sockaddr_in6_t)) {           \
            return NRF_ERROR_NULL | IOT_SOCKET_ERR_BASE; \
        }                                                \
    } while (0)

#define LWIP_SYS_TIMER_INTERVAL             APP_TIMER_TICKS(100)    /**< Interval for timer used as trigger to send. */

#define SOCKET_MAX_PENDING_PACKETS          32                      /**< Maximum number of pending received packets. */
#define SOCKET_MAX_PENDING_CONNECTIONS      10                      /**< Maximum number of simultaneous connections. */

/**@brief TCP state */
typedef enum
{
    TCP_STATE_IDLE,
    TCP_STATE_REQUEST_CONNECTION,
    TCP_STATE_CONNECTED,
    TCP_STATE_DATA_TX_IN_PROGRESS,
    TCP_STATE_TCP_SEND_PENDING,
    TCP_STATE_DISCONNECTED
} tcp_state_t;

/**@brief LwIP handle structure. */
typedef struct {
    struct tcp_pcb        * p_pcb;      /**< A pointer to LwIP TCP protocol control block. */
    socket_t              * p_socket;   /**< A pointer to corresponding socket. */
    nrf_fifo_t              conn_queue; /**< Connections queue. */
    mbuf_t                  mbuf;       /**< Memory management queue. */
    volatile tcp_state_t    tcp_state;  /**< TCP state. */
} lwip_handle_t;

static lwip_handle_t lwip_handles[SOCKET_MAX_SOCKET_COUNT]; /**< LwIP handle array. */

/**@brief Timer for LwIP. */
APP_TIMER_DEF(m_lwip_timer_id);

static err_t lwip_recv_callback(void           * p_arg,
                                struct tcp_pcb * p_pcb,
                                struct pbuf    * p_pbuf,
                                err_t            err);

static uint32_t lwip_buf_read(void    * p_ctx,
                              uint32_t  read_offset,
                              uint8_t * p_destbuf,
                              uint32_t  destbuf_len)
{
    struct pbuf * p_pbuf   = (struct pbuf *)p_ctx;
    uint32_t      copy_len = MIN(destbuf_len, (p_pbuf->len - read_offset));
    memcpy(p_destbuf, (void *)(((uint8_t *)p_pbuf->payload) + read_offset), copy_len);
    return copy_len;
}

static uint32_t lwip_buf_len(void * p_ctx)
{
    struct pbuf * p_pbuf = (struct pbuf *)p_ctx;
    return p_pbuf->len;
}

static void lwip_buf_free(void * p_ctx)
{
    nrf_free(((struct pbuf *)p_ctx)->payload);
    (void) pbuf_free((struct pbuf *)p_ctx);
}

static void lwip_timer_callback(void * p_ctx)
{
    (void) p_ctx;
    sys_check_timeouts();
}

void nrf_driver_interface_up(iot_interface_t const * p_interface)
{
    UNUSED_PARAMETER(p_interface);
    transport_interface_up();
}

void nrf_driver_interface_down(iot_interface_t const * p_interface)
{
    UNUSED_PARAMETER(p_interface);
    transport_interface_down();
}

void transport_handler_init(void)
{
    lwip_init();
    uint32_t err_code = nrf_driver_init();
    APP_ERROR_CHECK(err_code);
    for (uint32_t i = 0; i < SOCKET_MAX_SOCKET_COUNT; i++)
    {
        lwip_handles[i].p_pcb     = NULL;
        lwip_handles[i].p_socket  = NULL;
        lwip_handles[i].tcp_state = TCP_STATE_IDLE;
    }
    err_code = app_timer_create(&m_lwip_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                lwip_timer_callback);
    APP_ERROR_CHECK(err_code);
    err_code = app_timer_start(m_lwip_timer_id, LWIP_SYS_TIMER_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
    SOCKET_TRACE("Initialized LWIP transport handler\r\n");
}

static void lwip_error_handler(void * p_arg, err_t err)
{
    (void) p_arg;
    SOCKET_TRACE("Error occured: %d\r\n", (int)err);
    if(err == ERR_ABRT)
    {
        portdb_reset();
    }
}

static err_t lwip_poll_handler(void * p_arg, struct tcp_pcb * p_pcb)
{
    (void) p_arg;
    (void) p_pcb;

    return ERR_OK;
}

static void lwip_drop_connection(void * p_ctx)
{
    struct tcp_pcb * p_pcb = (struct tcp_pcb *)p_ctx;
    tcp_abort(p_pcb);
}

static lwip_handle_t * lwip_handle_allocate(socket_t * p_socket, struct tcp_pcb * p_pcb)
{
    lwip_handle_t * p_handle = NULL;
    for (uint32_t i = 0; i < SOCKET_MAX_SOCKET_COUNT; i++)
    {
        if (lwip_handles[i].p_pcb == NULL)
        {
            p_handle = &lwip_handles[i];
            (void)mbuf_init(&p_handle->mbuf,
                            lwip_buf_read,
                            lwip_buf_len,
                            lwip_buf_free,
                            SOCKET_MAX_PENDING_PACKETS);
            (void) nrf_fifo_init(&p_handle->conn_queue,
                                 SOCKET_MAX_PENDING_CONNECTIONS,
                                 socket_wait,
                                 lwip_drop_connection);
            p_handle->p_socket  = p_socket;
            p_handle->tcp_state = TCP_STATE_IDLE;
            if (p_pcb == NULL)
            {
                p_handle->p_pcb = tcp_new();
            }
            else
            {
                p_handle->p_pcb = p_pcb;
            }
            tcp_arg(p_handle->p_pcb, p_handle);
            tcp_setprio(p_handle->p_pcb, TCP_PRIO_MIN);
            tcp_recv(p_handle->p_pcb, lwip_recv_callback);
            tcp_err(p_handle->p_pcb, lwip_error_handler);
            tcp_poll(p_handle->p_pcb, lwip_poll_handler, 0);
            break;
        }
    }
    SOCKET_TRACE("Allocated LWIP socket handle\r\n");
    return p_handle;
}

static void lwip_handle_free(lwip_handle_t * p_handle)
{
    nrf_fifo_deinit(&p_handle->conn_queue);
    mbuf_deinit(&p_handle->mbuf);
    p_handle->p_pcb = NULL;
    p_handle->p_socket = NULL;
    p_handle->tcp_state = TCP_STATE_IDLE;
    SOCKET_TRACE("Released LWIP socket handle\r\n");
}

static uint32_t lwip_transport_open(socket_t * p_socket)
{
    lwip_handle_t * p_handle = NULL;
    uint32_t        err_code = NRF_SUCCESS;
    switch (p_socket->so_params.so_type)
    {
        case SOCK_STREAM:
            p_handle = lwip_handle_allocate(p_socket, NULL);
            if (p_handle == NULL)
            {
                err_code = NRF_ERROR_NULL;
            }
            else
            {
                p_socket->so_ctx = p_handle;
            }
            break;
        default:
            err_code = NRF_ERROR_NULL;
            break;
    }
    return err_code;
}

uint32_t lwip_error_convert(err_t lwip_err)
{
    uint32_t err_code = NRF_ERROR_NULL;
    switch (lwip_err)
    {
        case ERR_OK:
            err_code = NRF_SUCCESS;
            break;
        case ERR_MEM:
            err_code = SOCKET_NO_MEM;
            break;
        case ERR_TIMEOUT:
            err_code = SOCKET_TIMEOUT;
            break;
        case ERR_RTE:
            err_code = SOCKET_NO_ROUTE;
            break;
        default:
            err_code = NRF_ERROR_NULL;
            break;
    }
    return err_code;
}

static uint32_t lwip_transport_close(socket_t * p_socket)
{
    lwip_handle_t * p_handle = (lwip_handle_t *)p_socket->so_ctx;
    portdb_free((uint16_t)p_handle->p_pcb->local_port);
    err_t err_code = tcp_close(p_handle->p_pcb);
    if (err_code == ERR_OK)
    {
        lwip_handle_free(p_handle);
    }
    return lwip_error_convert(err_code);
}

static err_t lwip_connect_callback(void * p_arg, struct tcp_pcb * p_pcb, err_t err)
{
    lwip_handle_t * p_handle = (lwip_handle_t *)p_arg;
    // TODO: Error check
    SOCKET_TRACE("New connection\r\n");
    p_handle->tcp_state = TCP_STATE_CONNECTED;
    return ERR_OK;
}

static err_t lwip_recv_callback(void           * p_arg,
                                struct tcp_pcb * p_pcb,
                                struct pbuf    * p_pbuf,
                                err_t            err)
{
    lwip_handle_t * p_handle = (lwip_handle_t *)p_arg;
    socket_t      * p_socket = p_handle->p_socket;
    if (err == ERR_OK)
    {
        uint8_t     * p_payload_cp = nrf_malloc(p_pbuf->len);
        struct pbuf * p_pbuf_cp    = pbuf_alloc(PBUF_RAW, p_pbuf->len, PBUF_REF);

        memcpy(p_payload_cp, p_pbuf->payload, p_pbuf->len);
        p_pbuf_cp->payload = p_payload_cp;
        p_pbuf_cp->len     = p_pbuf->len;
        p_pbuf_cp->tot_len = p_pbuf->tot_len;

        uint32_t err_code = mbuf_write(&p_handle->mbuf, p_pbuf_cp);
        if (err_code == NRF_SUCCESS)
        {
            p_socket->so_read_evt++;
        }
        else
        {
            err = ERR_MEM;
        }
    }
    return err;
}

static uint32_t lwip_wait_for_state(lwip_handle_t * p_handle, tcp_state_t state)
{
    uint32_t err_code = NRF_SUCCESS;
    while (err_code == NRF_SUCCESS &&
           p_handle->tcp_state != state &&
           p_handle->tcp_state != TCP_STATE_DISCONNECTED)
    {
         err_code = socket_wait();
    }
    if (err_code == NRF_SUCCESS && p_handle->tcp_state != state)
    {
        err_code = NRF_ERROR_NULL;
    }
    return err_code;
}

static void lwipaddr_to_sockaddr(const ip6_addr_t * p_lwip_addr, sockaddr_in6_t * p_addr_in6)
{
    struct in6_addr * addr = &p_addr_in6->sin6_addr;
    addr->s6_addr[0] = p_lwip_addr->addr[0] & 0xFF;
    addr->s6_addr[1] = (p_lwip_addr->addr[0] >> 8) & 0xFF;
    addr->s6_addr[2] = (p_lwip_addr->addr[0] >> 16) & 0xFF;
    addr->s6_addr[3] = (p_lwip_addr->addr[0] >> 24) & 0xFF;

    addr->s6_addr[4] = p_lwip_addr->addr[1] & 0xFF;
    addr->s6_addr[5] = (p_lwip_addr->addr[1] >> 8) & 0xFF;
    addr->s6_addr[6] = (p_lwip_addr->addr[1] >> 16) & 0xFF;
    addr->s6_addr[7] = (p_lwip_addr->addr[1] >> 24) & 0xFF;

    addr->s6_addr[8]  = p_lwip_addr->addr[2] & 0xFF;
    addr->s6_addr[9]  = (p_lwip_addr->addr[2] >> 8) & 0xFF;
    addr->s6_addr[10] = (p_lwip_addr->addr[2] >> 16) & 0xFF;
    addr->s6_addr[11] = (p_lwip_addr->addr[2] >> 24) & 0xFF;

    addr->s6_addr[12] = p_lwip_addr->addr[3] & 0xFF;
    addr->s6_addr[13] = (p_lwip_addr->addr[3] >> 8) & 0xFF;
    addr->s6_addr[14] = (p_lwip_addr->addr[3] >> 16) & 0xFF;
    addr->s6_addr[15] = (p_lwip_addr->addr[3] >> 24) & 0xFF;
}

static void sockaddr_to_lwipaddr(const sockaddr_in6_t * p_addr_in6, ip6_addr_t * p_lwip_addr)
{
    const struct in6_addr * addr = &p_addr_in6->sin6_addr;
    IP6_ADDR_PART(p_lwip_addr, 0, addr->s6_addr[0], addr->s6_addr[1], addr->s6_addr[2], addr->s6_addr[3]);
    IP6_ADDR_PART(p_lwip_addr, 1, addr->s6_addr[4], addr->s6_addr[5], addr->s6_addr[6], addr->s6_addr[7]);
    IP6_ADDR_PART(p_lwip_addr, 2, addr->s6_addr[8], addr->s6_addr[9], addr->s6_addr[10], addr->s6_addr[11]);
    IP6_ADDR_PART(p_lwip_addr, 3, addr->s6_addr[12], addr->s6_addr[13], addr->s6_addr[14], addr->s6_addr[15]);
}

static uint32_t lwip_transport_bind(socket_t * p_socket, const void * p_addr, socklen_t addr_len)
{
    VERIFY_ADDRESS_LEN(addr_len);
    const sockaddr_in6_t * p_addr_in6 = (const sockaddr_in6_t *)p_addr;
    lwip_handle_t * p_handle = (lwip_handle_t *)p_socket->so_ctx;

    uint16_t port = HTONS(p_addr_in6->sin6_port);
    uint32_t err_code = portdb_register(port);
    if (err_code == NRF_SUCCESS)
    {
        ip6_addr_t lwip_addr;
        sockaddr_to_lwipaddr(p_addr_in6, &lwip_addr);
        err_t err = tcp_bind(p_handle->p_pcb, &lwip_addr, port);
        err_code = lwip_error_convert(err);
    }
    return err_code;
}

static uint32_t lwip_transport_connect(socket_t   * p_socket,
                                       const void * p_addr,
                                       socklen_t    addr_len)
{
    VERIFY_ADDRESS_LEN(addr_len);

    bool                   is_blocking = ((p_socket->so_flags & O_NONBLOCK) == 0);
    lwip_handle_t        * p_handle    = (lwip_handle_t *)p_socket->so_ctx;
    const sockaddr_in6_t * p_addr_in6  = (const sockaddr_in6_t *)p_addr;
    uint16_t               port        = 0;
    uint32_t               err_code    = portdb_alloc(&port);

    SOCKET_TRACE("Binding to port %d\r\n", (int)port);
    if (err_code == NRF_SUCCESS)
    {
        ip6_addr_t any_addr;
        ip6_addr_set_any(&any_addr);
        err_t err = tcp_bind      (p_handle->p_pcb, &any_addr, port);
        SOCKET_TRACE("Err %d from bind\r\n", (int)err);
        err_code = lwip_error_convert(err);
    }

    if (err_code == NRF_SUCCESS)
    {
        ip6_addr_t remote_addr;
        sockaddr_to_lwipaddr(p_addr_in6, &remote_addr);

        p_handle->tcp_state = TCP_STATE_REQUEST_CONNECTION;
        err_t err = tcp_connect(p_handle->p_pcb, &remote_addr, HTONS(p_addr_in6->sin6_port), lwip_connect_callback);
        SOCKET_TRACE("Err %d from connect\r\n", (int)err);
        err_code = lwip_error_convert(err);

        if (err_code == NRF_SUCCESS && is_blocking)
        {
            err_code = lwip_wait_for_state(p_handle, TCP_STATE_CONNECTED);
        }
    }
    if (err_code != NRF_SUCCESS)
    {
        SOCKET_TRACE("Error %d when connecting to socket\r\n", (int)err_code);
        portdb_free(port);
    }
    else
    {
        SOCKET_TRACE("Successfully connected to remote host!\r\n");
    }

    return err_code;
}

static err_t lwip_send_complete(void * p_arg, struct tcp_pcb * p_pcb, u16_t len)
{
    lwip_handle_t * p_handle = (lwip_handle_t *)p_arg;
    if (p_handle->tcp_state == TCP_STATE_TCP_SEND_PENDING)
    {
        p_handle->tcp_state = TCP_STATE_DATA_TX_IN_PROGRESS;
    }
    return ERR_OK;
}

static inline uint32_t lwip_check_connected(socket_t * p_socket)
{
    return (p_socket->so_state == STATE_CONNECTED || p_socket->so_params.so_type == SOCK_DGRAM) ?
            NRF_SUCCESS : SOCKET_NOT_CONNECTED;
}


static uint32_t lwip_transport_send(socket_t   * p_socket,
                                    const void * p_buf,
                                    uint32_t     buf_len,
                                    int          flags,
                                    const void * p_destaddr,
                                    socklen_t    destaddr_len)
{
    (void) p_destaddr;
    (void) destaddr_len;

    lwip_handle_t * p_handle = (lwip_handle_t *)p_socket->so_ctx;
    if ((p_socket->so_flags & O_NONBLOCK) != 0 &&
        (flags & MSG_WAITALL) == 0)
    {
        flags |= MSG_DONTWAIT;
    }

    uint32_t err_code = lwip_check_connected(p_socket);
    if (err_code == NRF_SUCCESS)
    {
        uint32_t len = tcp_sndbuf(p_handle->p_pcb);
        if (len >= buf_len)
        {
            tcp_sent(p_handle->p_pcb, lwip_send_complete);
            p_handle->tcp_state = TCP_STATE_TCP_SEND_PENDING;
            err_t err = tcp_write(p_handle->p_pcb, p_buf, buf_len, 1);
            err_code = lwip_error_convert(err);
            if (err_code == NRF_SUCCESS &&
               (flags & MSG_DONTWAIT) == 0)
            {
                err_code = lwip_wait_for_state(p_handle, TCP_STATE_DATA_TX_IN_PROGRESS);
            }
        }
        else
        {
            err_code = SOCKET_NO_MEM;
        }
    }
    return err_code;
}


static uint32_t lwip_transport_recv(socket_t  * p_socket,
                                    void      * p_buf,
                                    uint32_t  * p_buf_size,
                                    int         flags,
                                    void      * p_srcaddr,
                                    socklen_t * p_srcaddr_len)
{
    lwip_handle_t * p_handle = (lwip_handle_t *)p_socket->so_ctx;
    if ((p_socket->so_flags & O_NONBLOCK) != 0 &&
        (flags & MSG_WAITALL) == 0)
    {
        flags |= MSG_DONTWAIT;
    }
    uint32_t err_code = lwip_check_connected(p_socket);
    if (err_code == NRF_SUCCESS)
    {
        if (mbuf_empty(&p_handle->mbuf) == true)
        {
            if ((flags & MSG_DONTWAIT) != 0)
            {
                err_code = SOCKET_WOULD_BLOCK;
            }
            else
            {
                while ((mbuf_empty(&p_handle->mbuf) == true) && (err_code == NRF_SUCCESS))
                {
                    err_code = socket_wait();
                }
            }
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        *p_buf_size = mbuf_read(&p_handle->mbuf, p_buf, *p_buf_size);
        tcp_recved(p_handle->p_pcb, *p_buf_size);
        p_socket->so_read_evt = 0;
    }
    return err_code;
}

static err_t lwip_accept_callback(void * p_arg, struct tcp_pcb * p_pcb, err_t err)
{
    lwip_handle_t * p_handle = (lwip_handle_t *)p_arg;
    socket_t      * p_socket = p_handle->p_socket;
    if (err == ERR_OK)
    {
        (void) nrf_fifo_enq(&p_handle->conn_queue, p_pcb, true);
        // TODO: Error check
        p_socket->so_read_evt++;
    }
    return err;
}

static uint32_t lwip_transport_listen(socket_t * p_socket, int backlog)
{
    lwip_handle_t  * p_handle = (lwip_handle_t *)p_socket->so_ctx;
    uint32_t         err_code = NRF_SUCCESS;
    struct tcp_pcb * p_pcb    = tcp_listen_with_backlog(p_handle->p_pcb, backlog);
    if (p_pcb == NULL)
    {
        err_code = SOCKET_ADDRESS_IN_USE;
    }
    else
    {
        p_handle->p_pcb = p_pcb;
        tcp_accept(p_handle->p_pcb, lwip_accept_callback);
    }
    return err_code;
}

static uint32_t lwip_transport_accept(socket_t  * p_socket,
                                      socket_t  * p_client,
                                      void      * p_cliaddr,
                                      socklen_t * p_cliaddr_len)
{
    VERIFY_ADDRESS_LEN(*p_cliaddr_len);
    struct tcp_pcb * p_client_pcb  = NULL;
    lwip_handle_t  * p_lwip_handle = (lwip_handle_t *)p_socket->so_ctx;
    uint32_t err_code = nrf_fifo_deq(&p_lwip_handle->conn_queue,
                                     (void **)&p_client_pcb,
                                     (p_socket->so_flags & O_NONBLOCK) == 0);

    if (err_code == NRF_SUCCESS)
    {
        lwip_handle_t  * p_lwip_client = lwip_handle_allocate(p_client, p_client_pcb);
        sockaddr_in6_t * p_sockaddr    = (sockaddr_in6_t *)p_cliaddr;

        p_client->so_ctx = p_lwip_client;

        lwipaddr_to_sockaddr(&p_client_pcb->remote_ip, p_sockaddr);
        p_sockaddr->sin6_port     = p_client_pcb->remote_port;
        p_sockaddr->sin6_len      = *p_cliaddr_len;
        p_sockaddr->sin6_family   = AF_INET6;
        p_sockaddr->sin6_flowinfo = 0;
        p_sockaddr->sin6_scope_id = 0;

        /*lint -save -e548 */
        tcp_accepted(p_lwip_handle->p_pcb);
        /*lint -restore */
    }

    return err_code;
}

/**
 * @brief Transport for LwIP socket.
 */
socket_transport_t transport_impl =
{
    .open    = lwip_transport_open,
    .bind    = lwip_transport_bind,
    .connect = lwip_transport_connect,
    .send    = lwip_transport_send,
    .recv    = lwip_transport_recv,
    .listen  = lwip_transport_listen,
    .accept  = lwip_transport_accept,
    .close   = lwip_transport_close
};
