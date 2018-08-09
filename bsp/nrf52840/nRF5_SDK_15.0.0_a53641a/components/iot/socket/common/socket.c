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
#include "nordic_common.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "nrf_sdm.h"
#include "app_scheduler.h"
#include "app_timer.h"
#include "iot_common.h"
#include "app_error.h"
#include "socket_api.h"
#include "socket_common.h"
#include "socket_trace.h"
#include "sdk_os.h"
#include "transport_if.h"
#include "portdb.h"
#include "errno.h"
#include "mem_manager.h"
#include "ipv6_parse.h"
#include "netinet/in.h"
#include "unistd.h"
#include "sdk_os.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#ifndef SOCKET_ENABLE_API_PARAM_CHECK
#define SOCKET_ENABLE_API_PARAM_CHECK 0
#endif

#include "socket_config.h"

#if SOCKET_CONFIG_LOG_ENABLED == 1
    NRF_LOG_MODULE_REGISTER();
#endif

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          SOCKET_ENABLE_API_PARAM_CHECK should be set to 0 to disable these checks.
 *
 * @{
 */
#if SOCKET_ENABLE_API_PARAM_CHECK == 1

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                                    \
    do {                                                                  \
        if (m_initialization_state == false)                              \
        {                                                                 \
            return (SDK_ERR_MODULE_NOT_INITIALIZED | IOT_SOCKET_ERR_BASE);\
        }                                                                 \
    } while (0)


/**
 * @brief Verify NULL parameters are not passed to API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                            \
    do {                                                   \
        if ((PARAM) == NULL)                               \
        {                                                  \
            set_errno(EFAULT);                             \
            return -1;                                     \
        }                                                  \
    } while (0)

/**
 * @brief Verify socket id passed on the API by application is valid.
 */
#define VERIFY_SOCKET_ID(ID)                                       \
    do {                                                           \
        if (((ID) < 0) || ((ID) >= NUM_SOCKETS))       \
        {                                                          \
            set_errno(EBADF);                                      \
            return -1;                                             \
        }                                                          \
    } while (0)


#else

#define VERIFY_MODULE_IS_INITIALIZED()
#define NULL_PARAM_CHECK(PARAM)
#define VERIFY_SOCKET_ID(ID)
#endif

/** @} */
#define SOCKET_MUTEX_INIT()   SDK_MUTEX_INIT(m_socket_mtx);
#define SOCKET_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_socket_mtx)
#define SOCKET_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_socket_mtx)
// note: one extra for configuration socket
#define NUM_SOCKETS SOCKET_MAX_SOCKET_COUNT + 1

SDK_MUTEX_DEFINE(m_socket_mtx)                                                                      /**< Mutex for protecting m_socket_table (not individual entries). */

#define SCHED_QUEUE_SIZE                    16                                                      /**< Maximum number of events in the scheduler queue. */
#define SCHED_MAX_EVENT_DATA_SIZE           192                                                     /**< Maximum size of scheduler events. */

static bool             m_initialization_state = false;                                             /**< Variable to maintain module initialization state. */
static volatile bool    m_interface_up         = false;                                             /**< Interface state. */
static socket_t         m_socket_table[NUM_SOCKETS];                                                /**< Socket table. */

const struct in6_addr in6addr_any = { {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,                              /**< IPv6 anycast address. */
                                       0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u} };

#if defined (NRF_LOG_ENABLED) && (NRF_LOG_ENABLED == 1)

void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

#else // defined (NRF_LOG_ENABLED) && (NRF_LOG_ENABLED == 1)

void log_init(void)
{
    ;
}

#endif // defined (NRF_LOG_ENABLED) && (NRF_LOG_ENABLED == 1)

uint32_t socket_init(void)
{
    memset(m_socket_table, 0, sizeof(m_socket_table));

    SOCKET_MUTEX_INIT();

    log_init();

    uint32_t err_code = nrf_mem_init();
    APP_ERROR_CHECK(err_code);

    APP_SCHED_INIT(SCHED_MAX_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);

    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    err_code = config_socket_init();
    APP_ERROR_CHECK(err_code);

#if SOCKET_TRANSPORT_ENABLE == 1
    err_code = portdb_init(SOCKET_MAX_SOCKET_COUNT);
    APP_ERROR_CHECK(err_code);

    transport_handler_init();
#endif
    config_socket_start();
    m_initialization_state = true;

    SOCKET_TRACE("Socket init complete");

    return NRF_SUCCESS;
}

/**
 * Finds a free entry in the socket table, marks it as used and returns it. Returns -1 if no entry
 * was found.
 */
static int socket_allocate(socket_t ** pp_socket)
{
    int ret_sock = -1;
    SOCKET_MUTEX_LOCK();
    for (int sock = 0; sock < NUM_SOCKETS; sock++)
    {
        SOCKET_TRACE("Looking at socket %d with state %d", (int)sock, m_socket_table[sock].so_state);
        if (m_socket_table[sock].so_state == STATE_CLOSED)
        {
            m_socket_table[sock].so_state = STATE_OPEN;
            ret_sock                      = sock;
            *pp_socket                    = &m_socket_table[sock];
            break;
        }
    }
    if (ret_sock < 0)
    {
        set_errno(EMFILE);
    }
    SOCKET_MUTEX_UNLOCK();
    return ret_sock;
}

static socket_t * socket_find(int sock)
{
    SOCKET_MUTEX_LOCK();
    socket_t * p_socket = &m_socket_table[sock];
    SOCKET_MUTEX_UNLOCK();
    return p_socket;
}

static void socket_free(int sock)
{
    SOCKET_TRACE("Freeing socket %d", (int)sock);
    SOCKET_MUTEX_LOCK();
    memset(&m_socket_table[sock], 0, sizeof(m_socket_table[sock]));
    m_socket_table[sock].so_state = STATE_CLOSED;
    SOCKET_MUTEX_UNLOCK();
}

#if SOCKET_TRANSPORT_ENABLE == 1
void transport_interface_up(void)
{
    m_interface_up = true;
}

void transport_interface_down(void)
{
    m_interface_up = false;
    for (int sock = 0; sock < NUM_SOCKETS; sock++)
    {
        (void) close(sock);
    }
}
#endif

int fcntl(int fd, int cmd, int flags)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(fd);

    if (!((cmd == F_SETFL) || (cmd == F_GETFL)))
    {
        set_errno(EINVAL);
        return -1;
    }
    socket_t * p_socket = socket_find(fd);

    if (cmd == F_SETFL)
    {
        p_socket->so_flags = flags;
    }
    else if (cmd == F_GETFL)
    {
        return p_socket->so_flags;
    }

    return 0;
}

static void socket_set_errno(uint32_t err_code)
{
    switch (err_code) {
        case UDP_INTERFACE_NOT_READY: // fallthrough
        case SOCKET_INTERFACE_NOT_READY:
            set_errno(ENETDOWN);
            break;
        case SOCKET_WOULD_BLOCK:
            set_errno(EAGAIN);
            break;
        case SOCKET_NO_ROUTE:
            set_errno(ENETUNREACH);
            break;
        case NRF_ERROR_NO_MEM: // fallthrough
        case SOCKET_NO_MEM:
            set_errno(ENOMEM);
            break;
        case SOCKET_TIMEOUT:
            set_errno(ETIMEDOUT);
            break;
        case SOCKET_NO_AVAILABLE_PORTS:
            set_errno(EMFILE);
            break;
        case SOCKET_PORT_IN_USE: // fallthrough
        case SOCKET_ADDRESS_IN_USE:
            set_errno(EADDRINUSE);
            break;
        case SOCKET_INVALID_PARAM:
            set_errno(EINVAL);
            break;
        case SOCKET_UNSUPPORTED_PROTOCOL:
            set_errno(EPROTONOSUPPORT);
            break;
        case SOCKET_NOT_CONNECTED:
            set_errno(ENOTCONN);
            break;
    }
}


int socket(socket_family_t family, socket_type_t type, socket_protocol_t protocol)
{
    if (m_initialization_state == false)
    {
        (void) socket_init();
    }
    VERIFY_MODULE_IS_INITIALIZED();

    int        ret_sock = -1;
    socket_t * p_socket = NULL;
    int        sock     = socket_allocate(&p_socket);
    SOCKET_TRACE("Got value %d from allocate", (int)sock);
    if (sock >= 0)
    {
        p_socket->so_params.so_family   = family;
        p_socket->so_params.so_protocol = protocol;
        p_socket->so_params.so_type     = type;
        p_socket->so_transport          = NULL;

        if (family == AF_INET6)
        {
#if SOCKET_TRANSPORT_ENABLE == 1
            p_socket->so_transport = &transport_impl;
#else
            set_errno(EAFNOSUPPORT);
#endif
        }
        else if (family == AF_NRF_CFG || family == AF_NRF_CFG_INTERNAL)
        {
            p_socket->so_transport = &config_socket_transport;
        }
        else
        {
            set_errno(EAFNOSUPPORT);
        }

        if (p_socket->so_transport != NULL)
        {
            uint32_t err_code = p_socket->so_transport->open(p_socket);
            socket_set_errno(err_code);
            ret_sock = (err_code == NRF_SUCCESS) ? sock : ret_sock;
        }

        if (ret_sock < 0)
        {
            socket_free(sock);
        }
    }
    SOCKET_TRACE("Returning socket value %d", (int)ret_sock);
    return ret_sock;
}

static uint32_t wait_interface_up(void)
{
    SOCKET_TRACE("Waiting for interface to come up");
    uint32_t err_code = NRF_SUCCESS;
    while (err_code == NRF_SUCCESS && m_interface_up == false)
    {
        err_code = socket_wait();
    }
    if (m_interface_up == true)
    {
        SOCKET_TRACE("Interface is up!");
    }
    return err_code;
}

static uint32_t socket_interface_up(bool is_blocking)
{
    uint32_t err_code = NRF_SUCCESS;
    if (m_interface_up == false)
    {
        if (is_blocking)
        {
            (void) wait_interface_up();
        }
    }
    if (m_interface_up == false)
    {
        err_code = SOCKET_INTERFACE_NOT_READY;
    }
    return err_code;
}

int connect(int sock, const void * p_addr, socklen_t addrlen)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);
    NULL_PARAM_CHECK(p_addr);

    socket_t * p_socket    = socket_find(sock);
    bool       is_blocking = ((p_socket->so_flags & O_NONBLOCK) == 0);
    int        ret         = -1;

    uint32_t err_code = socket_interface_up(is_blocking);
    if (err_code != NRF_SUCCESS)
    {
        socket_set_errno(err_code);
    }
    else if (p_socket->so_state == STATE_OPEN)
    {
        err_code = p_socket->so_transport->connect(p_socket, p_addr, addrlen);
        if (err_code == NRF_SUCCESS)
        {
            p_socket->so_state = STATE_CONNECTED;
            ret = 0;
        }
        socket_set_errno(err_code);
    }
    else if (p_socket->so_state == STATE_CONNECTED)
    {
        set_errno(EISCONN);
    }
    else if (p_socket->so_state == STATE_CLOSED)
    {
        set_errno(EBADF);
    }
    return ret;
}


ssize_t sendto(int          sock,
               const void * p_buf,
               size_t       buflen,
               int          flags,
               const void * p_servaddr,
               socklen_t    addrlen)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);
    NULL_PARAM_CHECK(p_buf);

    socket_t * p_socket = socket_find(sock);

    if ((p_socket->so_flags & O_NONBLOCK) != 0 &&
        (flags & MSG_WAITALL) == 0)
    {
        flags |= MSG_DONTWAIT;
    }

    uint32_t err_code = socket_interface_up(((p_socket->so_flags & O_NONBLOCK) == 0) || ((flags & MSG_DONTWAIT) == 0));

    ssize_t ret = -1;
    if (err_code == NRF_SUCCESS)
    {
        err_code = p_socket->so_transport->send(p_socket, p_buf, buflen, flags, p_servaddr, addrlen);
        if (err_code == NRF_SUCCESS)
        {
            ret = (ssize_t) buflen;
        }
    }
    socket_set_errno(err_code);
    return ret;
}

ssize_t send(int sock, const void * p_buf, size_t buflen, int flags)
{
    return sendto(sock, p_buf, buflen, flags, NULL, 0);
}

ssize_t write(int sock, const void * p_buf, size_t buflen)
{
    return send(sock, p_buf, buflen, 0);
}

ssize_t recvfrom(int         sock,
                 void      * p_buf,
                 size_t      buf_size,
                 int         flags,
                 void      * p_cliaddr,
                 socklen_t * p_addrlen)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);
    NULL_PARAM_CHECK(p_buf);

    socket_t * p_socket  = socket_find(sock);
    ssize_t    ret       = -1;
    uint32_t   recv_size = buf_size;

    uint32_t err_code  = p_socket->so_transport->recv(p_socket,
                                                      p_buf,
                                                      &recv_size,
                                                      flags,
                                                      p_cliaddr,
                                                      p_addrlen);
    if (err_code == NRF_SUCCESS)
    {
            ret = (ssize_t) recv_size;
    }
    socket_set_errno(err_code);
    return ret;
}

ssize_t recv(int sock, void * p_buf, size_t buf_size, int flags)
{
    return recvfrom(sock, p_buf, buf_size, flags, NULL, NULL);
}

ssize_t read(int sock, void * p_buf, size_t buf_size)
{
    return recv(sock, p_buf,  buf_size, 0);
}

int setsockopt(int              sock,
               socket_opt_lvl_t level,
               int              optname,
               const void *     p_optval,
               socklen_t        optlen)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);

    socket_t * p_socket = socket_find(sock);

    uint32_t err_code = p_socket->so_transport->setsockopt(p_socket,
                                                           level,
                                                           optname,
                                                           p_optval,
                                                           optlen);
    socket_set_errno(err_code);
    return (err_code == NRF_SUCCESS ? 0 : -1);
}

int getsockopt(int sock, socket_opt_lvl_t level, int optname, void * p_optval, socklen_t * p_optlen)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);

    socket_t * p_socket = socket_find(sock);

    uint32_t err_code = p_socket->so_transport->getsockopt(p_socket,
                                                           level,
                                                           optname,
                                                           p_optval,
                                                           p_optlen);
    socket_set_errno(err_code);
    return (err_code == NRF_SUCCESS ? 0 : -1);
}

int bind(int sock, const void * p_addr, socklen_t addrlen)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);
    NULL_PARAM_CHECK(p_addr);

    socket_t * p_socket    = socket_find(sock);
    bool       is_blocking = ((p_socket->so_flags & O_NONBLOCK) == 0);
    int        ret         = -1;

    uint32_t err_code = socket_interface_up(is_blocking);
    if (err_code == NRF_SUCCESS)
    {
        err_code = p_socket->so_transport->bind(p_socket, p_addr, addrlen);
    }
    if (err_code == NRF_SUCCESS)
    {
        ret = 0;
    }
    socket_set_errno(err_code);
    return ret;
}

int listen(int sock, int backlog)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);

    socket_t * p_socket = socket_find(sock);

    uint32_t err_code = p_socket->so_transport->listen(p_socket, backlog);
    return (err_code == NRF_SUCCESS ? 0 :  -1);
}

int accept(int sock, void * p_cliaddr, socklen_t * p_addrlen)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);
    NULL_PARAM_CHECK(p_cliaddr);
    NULL_PARAM_CHECK(p_addrlen);

    socket_t * p_socket = socket_find(sock);
    int        ret      = -1;

    if (p_socket->so_params.so_type != SOCK_STREAM)
    {
        set_errno(EOPNOTSUPP);
    }
    else
    {
        uint32_t   err_code = NRF_SUCCESS;
        socket_t * p_client = NULL;
        int        sock_cli = socket_allocate(&p_client);
        if (sock_cli >= 0)
        {
            p_client->so_params    = p_socket->so_params;
            p_client->so_state     = STATE_CONNECTED;
            p_client->so_transport = p_socket->so_transport;
            err_code = p_socket->so_transport->accept(p_socket, p_client, p_cliaddr, p_addrlen);
        }

        if (err_code == NRF_SUCCESS)
        {
            ret = sock_cli;
        }
        else
        {
            socket_set_errno(err_code);
            socket_free(sock_cli);
        }
    }
    return ret;
}

int close(int sock)
{
    VERIFY_MODULE_IS_INITIALIZED();
    VERIFY_SOCKET_ID(sock);

    socket_t * p_socket = socket_find(sock);
    int        ret      = 0;

    if (p_socket->so_state != STATE_CLOSED)
    {
        uint32_t err_code = p_socket->so_transport->close(p_socket);
        ret = (err_code == NRF_SUCCESS) ? 0 : -1;
        SOCKET_TRACE("Close socket %d: ret: %d", (int)sock, ret);
        socket_free(sock);
    }
    return ret;
}

int fd_set_cmp(fd_set * set_a, fd_set * set_b)
{
    int ret = 0;
    if (set_a != NULL && set_b != NULL)
    {
        for (uint32_t i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, set_a) != FD_ISSET(i, set_b))
            {
                ret = 1;
                break;
            }
        }
    }
    return ret;
}

int select(int                    nfds,
           fd_set               * p_readset,
           fd_set               * p_writeset,
           fd_set               * p_exceptset,
           const struct timeval * p_timeout)
{
    VERIFY_SOCKET_ID(nfds - 1);

    // Approximately 10 ms sleep between each iteration
    uint32_t timestep = 10000;
    uint32_t endtime  = 0;
    if (p_timeout != NULL)
    {
        endtime = (p_timeout->tv_sec * 1000000) + p_timeout->tv_usec;
    }
    fd_set readset;
    FD_ZERO(&readset);
    fd_set writeset;
    FD_ZERO(&writeset);
    fd_set exceptset;
    FD_ZERO(&exceptset);

#define SELECT_CHECK_SET(in_set, out_set, evt_var)            \
    if ((in_set) != NULL)                                     \
    {                                                         \
        if (FD_ISSET(sock, (in_set)) && (evt_var) > 0)        \
        {                                                     \
            FD_SET(sock, (out_set));                          \
            num_ready++;                                      \
        }                                                     \
        else                                                  \
        {                                                     \
            FD_CLR(sock, (out_set));                          \
        }                                                     \
    }

    int      num_ready = 0;
    uint32_t err_code  = NRF_SUCCESS;
    while (err_code == NRF_SUCCESS)
    {
        for (int sock = 0; sock < nfds; sock++)
        {
            socket_t * p_socket = socket_find(sock);
            SELECT_CHECK_SET(p_readset, &readset, p_socket->so_read_evt);
            SELECT_CHECK_SET(p_writeset, &writeset, p_socket->so_write_evt);
            SELECT_CHECK_SET(p_exceptset, &exceptset, p_socket->so_except_evt);
        }
        // TODO: Check out how app events queue up while we checked the socket
        if (fd_set_cmp(p_readset, &readset) == 0 &&
            fd_set_cmp(p_writeset, &writeset) == 0 &&
            fd_set_cmp(p_exceptset, &exceptset) == 0)

        {
            break;
        }
        else
        {
            if (p_timeout == NULL)
            {
                err_code = socket_wait();
            }
            else if (endtime - timestep < endtime)
            {
                (void) usleep(timestep);
                endtime -= timestep;
            }
            else
            {
                break;
            }
        }

    }

    return num_ready;
}

