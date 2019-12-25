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
/** @file
 *
 * @brief MQTT Client Implementation over LwIP Stack port on nRF.
 *
 * This file contains the source code for MQTT Protocol over LwIP Stack for a nRF device.
 * The implementation is limited to MQTT Client role only.
 */


#include "mqtt_transport.h"
#include "mqtt_internal.h"
#include "mqtt_rx.h"

#include "lwip/opt.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "lwip/pbuf.h"
/*lint -save -e607 */
#include "lwip/tcp.h"
/*lint -restore -e607 */

#if MQTT_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME mqtt_lwip

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
    tcp_arg((struct tcp_pcb *)p_client->tcp_id, NULL);
    UNUSED_VARIABLE(tcp_output((struct tcp_pcb *)p_client->tcp_id));
    tcp_recv((struct tcp_pcb *)p_client->tcp_id, NULL);

    UNUSED_VARIABLE(tcp_close((struct tcp_pcb *)p_client->tcp_id));
}


err_t tcp_write_complete_cb(void *p_arg, struct tcp_pcb *ttcp_id, u16_t len)
{
    MQTT_MUTEX_LOCK();

    mqtt_client_t   *p_client = (mqtt_client_t *)(p_arg);

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_DISCONNECTING))
    {
        MQTT_TRC("[%p]: Closing TCP connection.", p_client);
        tcp_close_connection(p_client);
        disconnect_event_notify(p_client, NRF_SUCCESS);
    }
    else
    {
        MQTT_RESET_STATE(p_client, MQTT_STATE_PENDING_WRITE);
        MQTT_TRC("[%p]: TCP Write Complete.", p_client);
    }

    MQTT_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t mqtt_client_tcp_write(mqtt_client_t * p_client, uint8_t const * data, uint32_t datalen)
{
    uint32_t retval = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_PENDING_WRITE))
    {
        retval = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_TCP_CONNECTED))
    {
        tcp_sent((struct tcp_pcb *)p_client->tcp_id, tcp_write_complete_cb);

        MQTT_MUTEX_UNLOCK ();

        uint32_t err = tcp_write((struct tcp_pcb *)p_client->tcp_id,
                                 data,
                                 datalen,
                                 TCP_WRITE_FLAG_COPY);

        MQTT_MUTEX_LOCK ();

        if (err == ERR_OK)
        {
            MQTT_SET_STATE(p_client, MQTT_STATE_PENDING_WRITE);
            UNUSED_VARIABLE(iot_timer_wall_clock_get(&p_client->last_activity));
            MQTT_TRC("[%p]: TCP Write in Progress, length 0x%08x.", p_client, datalen);
            retval = NRF_SUCCESS;
        }
        else
        {
            MQTT_TRC("[%p]: TCP write failed, err = %d", err);
            retval = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
        }
    }

    return retval;
}


uint32_t mqtt_client_tcp_read(mqtt_client_t * p_id, uint8_t * p_data, uint32_t datalen)
{
    return mqtt_handle_rx_data( p_id, p_data, datalen);
}


/**@brief Callback registered with TCP to handle incoming data on the connection. */
err_t recv_callback(void * p_arg, struct tcp_pcb * p_tcp_id, struct pbuf * p_buffer, err_t err)
{
    MQTT_MUTEX_LOCK();

    mqtt_client_t * p_client = (mqtt_client_t *)(p_arg);

    MQTT_TRC(">> %s, result 0x%08x, buffer %p", __func__, err, p_buffer);

    if (err == ERR_OK && p_buffer != NULL)
    {
        MQTT_TRC(">> Packet buffer length 0x%08x ", p_buffer->tot_len);
        tcp_recved(p_tcp_id, p_buffer->tot_len);
        UNUSED_VARIABLE(mqtt_transport_read(p_client, p_buffer->payload, p_buffer->tot_len));
    }
    else
    {
        MQTT_TRC("Error receiving data, closing connection");
        tcp_close_connection(p_client);
        disconnect_event_notify(p_client, MQTT_ERR_TRANSPORT_CLOSED);
    }

    UNUSED_VARIABLE(pbuf_free(p_buffer));

    MQTT_MUTEX_UNLOCK();

    return ERR_OK;
}


uint32_t mqtt_client_tcp_connect(mqtt_client_t * p_client)
{
    connect_request_encode(p_client, &p_client->p_pending_packet, &p_client->pending_packetlen);

    // Send MQTT identification message to broker.
    uint32_t err = mqtt_client_tcp_write(p_client, p_client->p_pending_packet,
                                         p_client->pending_packetlen);
    if (err != ERR_OK)
    {
        mqtt_client_tcp_abort(p_client);
    }
    else
    {
        p_client->p_pending_packet  = NULL;
        p_client->pending_packetlen = 0;
    }

    return err;
}


/**@brief TCP Connection Callback. MQTT Connection  */
err_t tcp_connection_callback(void * p_arg, struct tcp_pcb * p_tcp_id, err_t err)
{
    MQTT_MUTEX_LOCK();

    mqtt_client_t * p_client = (mqtt_client_t *)p_arg;

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_TCP_CONNECTING) &&
       (err == ERR_OK))
    {
        MQTT_SET_STATE(p_client, MQTT_STATE_TCP_CONNECTED);

        // Register callback.
        tcp_recv(p_tcp_id, recv_callback);
        uint32_t err_code = mqtt_transport_connect(p_client);

        if (err_code != NRF_SUCCESS)
        {
            MQTT_TRC("Transport connect handler returned %08x", err_code);
            disconnect_event_notify(p_client, MQTT_CONNECTION_FAILED);
        }
    }

    MQTT_MUTEX_UNLOCK();

    return err;
}


void mqtt_client_tcp_abort(mqtt_client_t * p_client)
{
    tcp_abort((struct tcp_pcb *)p_client->tcp_id);
    disconnect_event_notify(p_client, MQTT_ERR_TCP_PROC_FAILED);
    MQTT_STATE_INIT(p_client);
}


void tcp_error_handler(void * p_arg, err_t err)
{
    MQTT_MUTEX_LOCK();

    mqtt_client_t * p_client = (mqtt_client_t *)(p_arg);

    disconnect_event_notify(p_client, err);

    MQTT_STATE_INIT(p_client);

    MQTT_MUTEX_UNLOCK();
}


err_t tcp_connection_poll(void * p_arg, struct tcp_pcb * p_tcp_id)
{
    MQTT_MUTEX_LOCK();

    mqtt_client_t * p_client = (mqtt_client_t *)(p_arg);

    p_client->poll_abort_counter++;

    MQTT_MUTEX_UNLOCK();

    return ERR_OK;
}


uint32_t tcp_request_connection(mqtt_client_t * p_client)
{
    p_client->poll_abort_counter = 0;
    p_client->tcp_id = (uint32_t)tcp_new_ip6();

    err_t err = tcp_connect((struct tcp_pcb *)p_client->tcp_id,
                            (ip_addr_t *)&p_client->broker_addr,
                             p_client->broker_port,
                             tcp_connection_callback);

    if (err != ERR_OK)
    {
        UNUSED_VARIABLE(mqtt_abort(p_client));
    }
    else
    {
        tcp_arg((struct tcp_pcb *)p_client->tcp_id, p_client);
        tcp_err((struct tcp_pcb *)p_client->tcp_id, tcp_error_handler);
        tcp_poll((struct tcp_pcb *)p_client->tcp_id, tcp_connection_poll, 10);
        tcp_accept((struct tcp_pcb *)p_client->tcp_id, tcp_connection_callback);

        MQTT_SET_STATE(p_client, MQTT_STATE_TCP_CONNECTING);
    }

    return err;
}


uint32_t mqtt_client_tcp_disconnect(mqtt_client_t * p_client)
{
    uint32_t err_code = NRF_ERROR_INVALID_STATE;

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED))
    {
        const uint8_t packet[] = {MQTT_PKT_TYPE_DISCONNECT, 0x00};
        UNUSED_VARIABLE(tcp_write((struct tcp_pcb *)p_client->tcp_id,
                       (void *)packet,
                        sizeof(packet),
                        1));

        tcp_close_connection(p_client);
        err_code = NRF_SUCCESS;
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_TCP_CONNECTED))
    {
        tcp_close_connection(p_client);
        err_code = NRF_SUCCESS;
    }

    return err_code;
}


uint32_t tcp_receive_packet(mqtt_client_t * p_client, uint32_t timeout)
{
    // This is not used in the lwip transport implementation.
    return NRF_ERROR_NOT_SUPPORTED | IOT_MQTT_ERR_BASE;
}
