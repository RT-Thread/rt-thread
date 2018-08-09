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
/** @file
 *
 * @brief MQTT Client Implementation over BSD Socket API on nRF.
 *
 * This file contains the source code for MQTT Protocol over BSD Socket API for a nRF device.
 * The implementation is limited to MQTT Client role only.
 */


#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "mem_manager.h"
#include "mqtt_transport.h"
#include "mqtt_internal.h"
#include "mqtt_rx.h"

#if MQTT_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME mqtt_soc

#define NRF_LOG_LEVEL       MQTT_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  MQTT_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR MQTT_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define MQTT_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define MQTT_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define MQTT_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define MQTT_ENTRY()                       MQTT_TRC(">> %s", __func__)
#define MQTT_EXIT()                        MQTT_TRC("<< %s", __func__)

#else // MQTT_CONFIG_LOG_ENABLED

#define MQTT_TRC(...)                                                                           /**< Disables traces. */
#define MQTT_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define MQTT_ERR(...)                                                                           /**< Disables error logs. */

#define MQTT_ENTRY(...)
#define MQTT_EXIT(...)

#endif // MQTT_CONFIG_LOG_ENABLED

void disconnect_event_notify(mqtt_client_t * p_client, uint32_t result);


/**@brief Close TCP connection and clean up client instance.
 *
 * @param[in]  p_client  Identifies the client for which the procedure is requested.
 */
static void tcp_close_connection(const mqtt_client_t * p_client)
{
    MQTT_TRC("Closing socket %d", p_client->socket_fd);
    UNUSED_VARIABLE(close(p_client->socket_fd));
}


uint32_t mqtt_client_tcp_write(mqtt_client_t * p_client, uint8_t const * data, uint32_t datalen)
{
    uint32_t err_code = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_PENDING_WRITE))
    {
        err_code = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_TCP_CONNECTED))
    {
        MQTT_TRC("[%p]: TCP writing %d bytes.", p_client, datalen);
        MQTT_SET_STATE(p_client, MQTT_STATE_PENDING_WRITE);

        MQTT_MUTEX_UNLOCK();

        ssize_t nbytes = send(p_client->socket_fd, data, datalen, 0);

        MQTT_MUTEX_LOCK();

        MQTT_RESET_STATE(p_client, MQTT_STATE_PENDING_WRITE);

        if (nbytes == datalen)
        {
            MQTT_TRC("[%p]: TCP write complete.", p_client);
            UNUSED_VARIABLE(iot_timer_wall_clock_get(&p_client->last_activity));
            err_code = NRF_SUCCESS;
        }
        else
        {
            MQTT_TRC("TCP write failed, errno = %d, closing connection", errno);
            tcp_close_connection(p_client);
            disconnect_event_notify(p_client, MQTT_ERR_TRANSPORT_CLOSED);
            err_code = (NRF_ERROR_INTERNAL | IOT_MQTT_ERR_BASE);
        }
    }
    else
    {
       err_code = MQTT_ERR_NOT_CONNECTED;
    }

    return err_code;
}


uint32_t mqtt_client_tcp_read(mqtt_client_t * p_client, uint8_t * p_data, uint32_t datalen)
{
    return mqtt_handle_rx_data(p_client, p_data, datalen);
}


uint32_t mqtt_client_tcp_connect(mqtt_client_t * p_client)
{
    uint32_t err_code;

    connect_request_encode(p_client, &p_client->p_pending_packet, &p_client->pending_packetlen);

    // Send MQTT identification message to broker.
    MQTT_SET_STATE(p_client, MQTT_STATE_PENDING_WRITE);

    MQTT_MUTEX_UNLOCK();

    ssize_t nbytes = send(p_client->socket_fd,
                          p_client->p_pending_packet,
                          p_client->pending_packetlen,
                          0);

    MQTT_MUTEX_LOCK();

    MQTT_RESET_STATE(p_client, MQTT_STATE_PENDING_WRITE);

    if (nbytes == p_client->pending_packetlen)
    {
        UNUSED_VARIABLE(iot_timer_wall_clock_get(&p_client->last_activity));
        p_client->p_pending_packet  = NULL;
        p_client->pending_packetlen = 0;
        err_code = NRF_SUCCESS;
    }
    else
    {
        mqtt_client_tcp_abort(p_client);
        err_code = (NRF_ERROR_INTERNAL | IOT_MQTT_ERR_BASE);
    }

    return err_code;
}


void mqtt_client_tcp_abort(mqtt_client_t * p_client)
{
    tcp_close_connection(p_client);
    disconnect_event_notify(p_client, MQTT_ERR_TCP_PROC_FAILED);
}


uint32_t tcp_receive_packet(mqtt_client_t * p_client, uint32_t timeout)
{
    if (timeout != 0)
    {
        // TODO: Implement support for timeout.
        return NRF_ERROR_NOT_SUPPORTED | IOT_MQTT_ERR_BASE;
    }

    uint8_t * p_packet = nrf_malloc(MQTT_MAX_PACKET_LENGTH);
    if (p_packet == NULL)
    {
        return NRF_ERROR_NO_MEM | IOT_MQTT_ERR_BASE;
    }

    MQTT_MUTEX_UNLOCK();

    ssize_t p_len = recv(p_client->socket_fd, p_packet, MQTT_MAX_PACKET_LENGTH, 0);

    MQTT_MUTEX_LOCK();

    uint32_t err_code;

    if (p_len > 0)
    {
        err_code = mqtt_transport_read(p_client, p_packet, p_len);
        MQTT_TRC("Received %d bytes from %d: 0x%08x",
                      p_len, p_client->socket_fd, err_code);
    }
    else if (p_len == 0)
    {
        // Receiving 0 bytes indicates an orderly shutdown.
        MQTT_TRC("Received end of stream, closing connection");
        tcp_close_connection(p_client);
        disconnect_event_notify(p_client, MQTT_ERR_TRANSPORT_CLOSED);
        err_code = NRF_SUCCESS;
    }
    else
    {
        MQTT_TRC("Error receiving data, errno = %d, closing connection", errno);
        mqtt_client_tcp_abort(p_client);
        err_code = (NRF_ERROR_INVALID_DATA | IOT_MQTT_ERR_BASE);
    }

    nrf_free(p_packet);

    return err_code;
}


uint32_t tcp_request_connection(mqtt_client_t * p_client)
{
    uint32_t err_code = NRF_SUCCESS;

    p_client->socket_fd = socket(AF_INET6, SOCK_STREAM, 0);
    MQTT_TRC("Created socket %d", p_client->socket_fd);
    if (p_client->socket_fd < 0)
    {
        err_code = (NRF_ERROR_INTERNAL | IOT_MQTT_ERR_BASE);
    }

    if (err_code == NRF_SUCCESS)
    {
        struct sockaddr_in6 dest;
        memset(&dest, 0, sizeof(dest));
        dest.sin6_family = AF_INET6;
        dest.sin6_port = htons(p_client->broker_port);
        memcpy(&dest.sin6_addr, p_client->broker_addr.u8, sizeof(dest.sin6_addr));

        int ret = connect(p_client->socket_fd, (struct sockaddr *)&dest, sizeof(dest));
        if (ret == 0)
        {
            MQTT_SET_STATE(p_client, MQTT_STATE_TCP_CONNECTED);
            err_code = mqtt_transport_connect(p_client);
            MQTT_TRC("Sent connect %d: 0x%08x", p_client->socket_fd, err_code);
        }
        else
        {
            mqtt_client_tcp_abort(p_client);
            err_code = (NRF_ERROR_INTERNAL | IOT_MQTT_ERR_BASE);
        }
    }

    while (!MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED) && err_code == NRF_SUCCESS)
    {
        // Receive until connected.
        MQTT_TRC("Receive until connected");
        err_code = tcp_receive_packet(p_client, 0);
    }

    MQTT_TRC("Connect completed");
    return err_code;
}


uint32_t mqtt_client_tcp_disconnect(mqtt_client_t * p_client)
{
    uint32_t err_code;

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED))
    {
        const uint8_t packet[] = {MQTT_PKT_TYPE_DISCONNECT, 0x00};
        MQTT_SET_STATE(p_client, MQTT_STATE_PENDING_WRITE);

        MQTT_MUTEX_UNLOCK();

        UNUSED_VARIABLE(send(p_client->socket_fd, (void *)packet, sizeof(packet), 0));

        MQTT_MUTEX_LOCK();

        MQTT_RESET_STATE(p_client, MQTT_STATE_PENDING_WRITE);
        tcp_close_connection(p_client);
        err_code = NRF_SUCCESS;
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_TCP_CONNECTED))
    {
        tcp_close_connection(p_client);
        err_code = NRF_SUCCESS;
    }
    else
    {
        err_code = (NRF_ERROR_INVALID_STATE | IOT_MQTT_ERR_BASE);
    }

    return err_code;
}
