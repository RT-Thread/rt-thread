/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#ifdef UNIX
#include <fcntl.h>
#endif
#include <errno.h>
#include <stdint.h>
#include "mem_manager.h"
#include "sdk_errors.h"
#include "sdk_config.h"
#include "iot_common.h"
#include "nordic_common.h"
#include "coap_transport.h"
#include "coap.h"

/**@brief UDP port information. */
typedef struct
{
    int               socket_fd;                           /**< Socket information provided by UDP. */
    uint16_t          port_number;                         /**< Associated port number. */
} udp_port_t;

static udp_port_t m_port_table[COAP_PORT_COUNT];           /**< Table maintaining association between CoAP ports and corresponding UDP socket identifiers. */

static fd_set m_readfds;
static int    m_max_sd = 0;

/**@brief Creates port as requested in p_port.
 *
 * @details Creates port as requested in p_port.
 *
 * @param[in]   index    Index to the m_port_table where entry of the port created is to be made.
 * @param[in]   p_port   Port information to be created.
 *
 * @retval NRF_SUCCESS   Indicates if port was created successfully, else an an error code
 *                       indicating reason for failure.
 */
static uint32_t port_create(uint32_t index, coap_port_t  * p_port)
{
    // Request new socket creation.
    int socket_fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_fd != -1)
    {
        // Bind the socket to the local port.
        struct sockaddr_in6 sin6;

        memset(&sin6, 0, sizeof(struct sockaddr_in6));
        sin6.sin6_family = AF_INET6;
        sin6.sin6_port = htons(p_port->port_number);
        sin6.sin6_addr = in6addr_any;

        int retval = bind(socket_fd, (struct sockaddr *)&sin6, sizeof(sin6));
        if (retval != -1)
        {
              m_port_table[index].port_number = p_port->port_number;
              m_port_table[index].socket_fd   = socket_fd;
        }
        else
        {
            // Not all procedures succeeded with allocated socket, hence free it.
            UNUSED_VARIABLE(close(socket_fd));
            return NRF_ERROR_INVALID_PARAM;
        }
    }

    // Configure socket to be non-blocking.
    int flags = fcntl(socket_fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    UNUSED_VARIABLE(fcntl(m_port_table[index].socket_fd, F_SETFL, flags));

    // Add socket to file descriptor set.
    FD_SET(m_port_table[index].socket_fd, &m_readfds);

    // If enumeration is having a gap, increase the max fd count.
    if (socket_fd >= m_max_sd)
    {
        m_max_sd = (socket_fd + 1);
    }

    return NRF_SUCCESS;
}


uint32_t coap_transport_init(const coap_transport_init_t   * p_param)
{
    uint32_t err_code = NRF_SUCCESS;
    uint32_t index;

    NULL_PARAM_CHECK(p_param);
    NULL_PARAM_CHECK(p_param->p_port_table);

    FD_ZERO(&m_readfds);

    err_code = nrf_mem_init();

    if (err_code == NRF_SUCCESS) {
        for (index = 0; index < COAP_PORT_COUNT; index++)
        {
            // Create end point for each of the COAP ports.
            err_code = port_create(index, &p_param->p_port_table[index]);
            if (err_code != NRF_SUCCESS)
            {
                break;
            }
        }
    }

    return err_code;
}


uint32_t coap_transport_write(const coap_port_t    * p_port,
                              const coap_remote_t  * p_remote,
                              const uint8_t        * p_data,
                              uint16_t               datalen)
{

    uint32_t err_code = NRF_ERROR_NOT_FOUND;
    uint32_t index;

    NULL_PARAM_CHECK(p_port);
    NULL_PARAM_CHECK(p_remote);
    NULL_PARAM_CHECK(p_data);

    // Search for the corresponding port.
    for (index = 0; index < COAP_PORT_COUNT; index++)
    {
        if (m_port_table[index].port_number == p_port->port_number)
        {
            COAP_MUTEX_UNLOCK();

            static struct sockaddr_in6 dest_address_in6;

            memset(&dest_address_in6, 0, sizeof(struct sockaddr_in6));
            dest_address_in6.sin6_family = AF_INET6;
            dest_address_in6.sin6_port = htons(p_remote->port_number);

            memcpy(&dest_address_in6.sin6_addr, p_remote->addr, sizeof(struct in6_addr));

            // Send on UDP port.
            int retval = sendto(m_port_table[index].socket_fd,
                                p_data,
                                datalen,
                                0,
                                (struct sockaddr *)&dest_address_in6,
                                sizeof(dest_address_in6));
            if (retval == -1)
            {
                // Error in sendto.
                err_code = NRF_ERROR_INTERNAL;
            }
            else
            {
                err_code = NRF_SUCCESS;
            }

            COAP_MUTEX_LOCK();
            break;
        }
    }

    return err_code;
}


void coap_transport_process(void)
{
    return;
}


uint32_t coap_security_setup(uint16_t                       local_port,
                             nrf_tls_role_t                 role,
                             coap_remote_t          * const p_remote,
                             nrf_tls_key_settings_t * const p_settings)
{
    return SDK_ERR_API_NOT_IMPLEMENTED;
}


uint32_t coap_security_destroy(uint16_t              local_port,
                               coap_remote_t * const p_remote)
{
    return SDK_ERR_API_NOT_IMPLEMENTED;
}


void coap_transport_input(void)
{
    int retval = select(m_max_sd, &m_readfds, NULL, NULL, NULL);

    if (retval == -1)
    {
        // Error in select().
        // Placeholder for debugging.
    }
    else if (retval >= 1) // Number of file descriptiors with activity.
    {
        uint32_t index = 0;
        int socket_fd = m_port_table[index].socket_fd;

        // The descriptor has data.
        if (FD_ISSET(socket_fd, &m_readfds)) // If socket_fd is set to read.
        {
            static uint8_t read_mem[COAP_MESSAGE_DATA_MAX_SIZE];
            static struct  sockaddr_in6 client_address_in6;
            socklen_t address_length = sizeof(struct  sockaddr_in6);

            int bytes_read = recvfrom(socket_fd,
                                      read_mem,
                                      sizeof(read_mem),
                                      0,
                                      (struct sockaddr *)&client_address_in6,
                                      (socklen_t *)&address_length); // Blocking call, waiting for incoming transaction.
            if (bytes_read >= 0)
            {
                coap_port_t port;
                port.port_number = m_port_table[index].port_number;

                coap_remote_t remote_endpoint;
                memcpy(remote_endpoint.addr, &client_address_in6.sin6_addr, sizeof(struct in6_addr));
                remote_endpoint.port_number = ntohs(client_address_in6.sin6_port);

                uint32_t result = NRF_SUCCESS;

                // Notify the CoAP module of received data.
                retval = coap_transport_read(&port,
                                             &remote_endpoint,
                                             NULL,
                                             result,
                                             read_mem,
                                             (uint16_t)bytes_read);

                // Nothing much to do if CoAP could not interpret the datagram.
                UNUSED_VARIABLE(retval);
            }
            else
            {
                // Error in readfrom().
                // Placeholder for debugging.
                // If select() indicated this socket file descriptor to have pending
                // data, this case should not occur.
            }
        }
    }
    else
    {
        // In case of socket() returning 0, timeout.
        // Not implemented.
    }
}
