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
/** @file mqtt.c
 *
 * @brief MQTT Client API Implementation.
 */


#include "mqtt.h"
#include "mem_manager.h"
#include "mqtt_transport.h"
#include "mqtt_internal.h"
#include "iot_timer.h"

#if MQTT_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME mqtt

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

/**< Never changing ping request, needed for Keep Alive. */
static const uint8_t        m_ping_packet[MQTT_PKT_HEADER_SIZE] = \
                                         {MQTT_PKT_TYPE_PINGREQ,  \
                                         0x00};

/**< Never changing disconnect request. */
static const uint8_t        m_disc_packet[MQTT_PKT_HEADER_SIZE] = \
                                         {MQTT_PKT_TYPE_DISCONNECT, \
                                         0x00};

static mqtt_client_t      * m_mqtt_client[MQTT_MAX_CLIENTS];                             /**< MQTT Client table. */
SDK_MUTEX_DEFINE(m_mqtt_mutex)                                                           /**< Mutex variable for the module, currently unused. */


static uint32_t get_client_index(mqtt_client_t * const p_client)
{
    for (uint32_t index = 0; index < MQTT_MAX_CLIENTS; index++)
    {
        if (m_mqtt_client[index] == p_client)
        {
            return index;
        }
    }

    return MQTT_MAX_CLIENTS;
}


void client_free(mqtt_client_t * const p_client)
{
    MQTT_STATE_INIT(p_client);

    // Free memory used for TX packets and reset the pointer.
    nrf_free(p_client->p_packet);
    p_client->p_packet = NULL;

    // Free TLS instance and reset the instance.
    UNUSED_VARIABLE(nrf_tls_free(&p_client->tls_instance));
    NRF_TLS_INTSANCE_INIT(&p_client->tls_instance);
}


void client_init(mqtt_client_t * const p_client)
{
    memset(p_client, 0, sizeof(*p_client));

    MQTT_STATE_INIT(p_client);

    p_client->protocol_version = MQTT_VERSION_3_1_0;
    p_client->clean_session = 1;

    NRF_TLS_INTSANCE_INIT(&p_client->tls_instance);
}


/**@brief Notifies event to the application.
 *
 * @param[in]  p_client  Identifies the client for which the procedure is requested.
 * @param[in]  p_evt     Reason for disconnection.
 */
void event_notify(mqtt_client_t * const p_client, const mqtt_evt_t * p_evt, uint32_t flags)
{
    const mqtt_evt_cb_t     evt_cb = p_client->evt_cb;

    if (evt_cb != NULL)
    {
        MQTT_MUTEX_UNLOCK();

        evt_cb(p_client, p_evt);

        MQTT_MUTEX_LOCK();

        if (IS_SET(flags,MQTT_EVT_FLAG_INSTANCE_RESET))
        {
            client_init(p_client);
        }
    }
}


/**@brief Notifies disconnection event to the application.
 *
 * @param[in]  p_client  Identifies the client for which the procedure is requested.
 * @param[in]  result    Reason for disconnection.
 */
void disconnect_event_notify(mqtt_client_t * p_client, uint32_t result)
{
    mqtt_evt_t        evt;
    const uint32_t    client_index = get_client_index(p_client);

    // Remove the client from internal table.
    if (client_index != MQTT_MAX_CLIENTS)
    {
        m_mqtt_client[client_index] = NULL;
    }

    // Determine appropriate event to generate.
    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED) ||
        MQTT_VERIFY_STATE(p_client, MQTT_STATE_DISCONNECTING))
    {
        evt.id     = MQTT_EVT_DISCONNECT;
        evt.result = result;
    }
    else
    {
        evt.id     = MQTT_EVT_CONNACK;
        evt.result = MQTT_CONNECTION_FAILED;
    }

    // Free the instance.
    client_free(p_client);

    // Notify application.
    event_notify(p_client, &evt, MQTT_EVT_FLAG_INSTANCE_RESET);
}


uint32_t mqtt_init(void)
{
    SDK_MUTEX_INIT(m_mqtt_mutex);

    MQTT_MUTEX_LOCK();

    memset(m_mqtt_client, 0, sizeof(m_mqtt_client));

    MQTT_MUTEX_UNLOCK();

    return nrf_tls_init();
}


void mqtt_client_init(mqtt_client_t * const p_client)
{
    NULL_PARAM_CHECK_VOID(p_client);

    MQTT_MUTEX_LOCK();

    client_init(p_client);

    MQTT_MUTEX_UNLOCK();
}


uint32_t mqtt_connect(mqtt_client_t * const p_client)
{
    // Look for a free instance if available.
    uint32_t err_code     = NRF_SUCCESS;
    uint32_t client_index = 0;

    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_client->client_id.p_utf_str);

    MQTT_MUTEX_LOCK();

    for (client_index = 0; client_index < MQTT_MAX_CLIENTS; client_index++)
    {
         if (m_mqtt_client[client_index] == NULL)
         {
             // Found a free instance.
             m_mqtt_client[client_index] = p_client;

             // Allocate buffer packets in TX path.
             p_client->p_packet = nrf_malloc(MQTT_MAX_PACKET_LENGTH);
             break;
         }
    }

    if ((client_index == MQTT_MAX_CLIENTS) || (p_client->p_packet == NULL))
    {
        err_code = (NRF_ERROR_NO_MEM | IOT_MQTT_ERR_BASE);
    }
    else
    {
        err_code = tcp_request_connection(p_client);

        if (err_code != NRF_SUCCESS)
        {
            // Free the instance.
            m_mqtt_client[client_index] = NULL;
            nrf_free(p_client->p_packet);
            err_code = MQTT_ERR_TCP_PROC_FAILED;
        }
    }

    UNUSED_VARIABLE(p_client);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_publish(mqtt_client_t               * const p_client,
                      mqtt_publish_param_t  const * const p_param)
{
    uint32_t   err_code = MQTT_ERR_NOT_CONNECTED;
    uint32_t   offset   = 0;
    uint32_t   mqtt_packetlen = 0;
    uint8_t  * p_payload;

    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_param);

    MQTT_TRC("[CID %p]:[State 0x%02x]: >> %s Topic size 0x%08x, Data size 0x%08x",
                  p_client,
                  p_client->state,
                  __func__,
                  p_param->message.topic.topic.utf_strlen,
                  p_param->message.payload.bin_strlen);

    MQTT_MUTEX_LOCK();

    p_payload = &p_client->p_packet[MQTT_FIXED_HEADER_EXTENDED_SIZE];

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_PENDING_WRITE))
    {
        err_code = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED))
    {
        memset(p_payload, 0, MQTT_MAX_PACKET_LENGTH);

        // Pack topic.
        err_code = pack_utf8_str(&p_param->message.topic.topic,
                                 MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                                 p_payload,
                                 &offset);

        if (err_code == NRF_SUCCESS)
        {
            if (p_param->message.topic.qos)
            {
                err_code = pack_uint16(p_param->message_id,
                                       MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                                       p_payload,
                                       &offset);
            }
        }
        if (err_code == NRF_SUCCESS)
        {
            // Pack message on the topic.
            err_code = pack_bin_str(&p_param->message.payload,
                                    MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                                    p_payload,
                                    &offset);
        }


        if (err_code == NRF_SUCCESS)
        {
            const uint8_t message_type = MQTT_MESSAGES_OPTIONS(MQTT_PKT_TYPE_PUBLISH,
                                                               0,  // Duplicate flag not set.
                                                               p_param->message.topic.qos,
                                                               0); // Retain flag not set.

            mqtt_packetlen = mqtt_encode_fixed_header(message_type, // Message type
                                                      offset,       // Payload size without the fixed header
                                                      &p_payload);  // Address where the p_payload is contained.


            // Publish message.
            err_code = mqtt_transport_write(p_client, p_payload, mqtt_packetlen);
        }
    }

    MQTT_TRC("<< %s", (uint32_t)__func__);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


/**@brief Encodes and sends messages that contain only message id in the variable header.
 *
 * @param[in]  p_client    Identifies the client for which the procedure is requested.
 * @param[in]  op_code     Opcode for the message.
 * @param[in]  message_id  Message id to be encoded in the variable header.
 *
 * @retval NRF_SUCCESS or an error code indicating a reason for failure.
 */
uint32_t mqtt_message_id_only_enc_n_send(mqtt_client_t    * const p_client,
                                         uint8_t                  opcode,
                                         uint16_t                 message_id)
{
    uint32_t      err_code       = MQTT_ERR_NOT_CONNECTED;
    uint32_t      offset         = 0;
    uint32_t      mqtt_packetlen = 0;
    uint8_t     * p_payload;

    p_payload = &p_client->p_packet[MQTT_FIXED_HEADER_EXTENDED_SIZE];

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_PENDING_WRITE))
    {
        err_code = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED))
    {
        memset(p_payload, 0, MQTT_MAX_PACKET_LENGTH);

        err_code = pack_uint16(message_id,
                               MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                               p_payload,
                               &offset);

        if (err_code == NRF_SUCCESS)
        {
            const uint8_t message_type = MQTT_MESSAGES_OPTIONS(opcode,
                                                               0,  // Duplicate flag not set.
                                                               0,  // QoS unused.
                                                               0); // Retain flag not set.

            mqtt_packetlen = mqtt_encode_fixed_header(message_type, // Message type
                                                      offset,       // Payload size without the fixed header
                                                      &p_payload);  // Address where the p_payload is contained.

            // Publish message.
            err_code = mqtt_transport_write(p_client, p_payload, mqtt_packetlen);
        }
    }

    return err_code;
}


/**@brief Sends raw message to the peer.
 *
 * @param[in]  p_client    Identifies the client for which the procedure is requested.
 * @param[in]  p_message   Raw message to be sent to the peer.
 * @param[in]  message_id  Message id to be encoded in the variable header.
 *
 * @retval NRF_SUCCESS or an error code indicating a reason for failure.
 */
uint32_t mqtt_raw_message_send(mqtt_client_t        * const p_client,
                               const uint8_t        * p_message,
                               uint16_t               message_len)
{
    uint32_t err_code;

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_PENDING_WRITE))
    {
        err_code = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED))
    {
        err_code = mqtt_transport_write(p_client, p_message, message_len);
    }
    else
    {
        err_code = MQTT_ERR_NOT_CONNECTED;
    }

    return err_code;
}


uint32_t mqtt_publish_ack(mqtt_client_t             * const p_client,
                          mqtt_puback_param_t const * p_param)
{
    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_param);

    MQTT_TRC("[CID %p]:[State 0x%02x]: >> %s Message id 0x%04x",
                   p_client,
                   p_client->state,
                   __func__,
                   p_param->message_id);

    MQTT_MUTEX_LOCK();

    uint32_t  err_code = mqtt_message_id_only_enc_n_send(p_client,
                                                         MQTT_PKT_TYPE_PUBACK,
                                                         p_param->message_id);

    MQTT_TRC("[CID %p]:[State 0x%02x]: << %s result 0x%08x",
                  p_client,
                  p_client->state,
                  __func__,
                  err_code);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_publish_receive(mqtt_client_t             * const p_client,
                              mqtt_pubrec_param_t const * const p_param)
{
    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_param);

    MQTT_TRC("[CID %p]:[State 0x%02x]: >> %s Message id 0x%04x",
                  p_client,
                  p_client->state,
                  __func__,
                  p_param->message_id);

    MQTT_MUTEX_LOCK();

    uint32_t  err_code = mqtt_message_id_only_enc_n_send(p_client,
                                                         MQTT_PKT_TYPE_PUBREC,
                                                         p_param->message_id);

    MQTT_TRC("[CID %p]:[State 0x%02x]: << %s result 0x%08x",
                  p_client,
                  p_client->state,
                  __func__,
                  err_code);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_publish_release(mqtt_client_t             * const p_client,
                              mqtt_pubrel_param_t const * const p_param)
{
    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_param);

    MQTT_TRC("[CID %p]:[State 0x%02x]: >> %s Message id 0x%04x",
                  p_client,
                  p_client->state,
                  __func__,
                  p_param->message_id);

    MQTT_MUTEX_LOCK();

    uint32_t  err_code = mqtt_message_id_only_enc_n_send(p_client,
                                                         MQTT_PKT_TYPE_PUBREL,
                                                         p_param->message_id);

    MQTT_TRC("[CID %p]:[State 0x%02x]: << %s result 0x%08x",
                  p_client,
                  p_client->state,
                  __func__,
                  err_code);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_publish_complete(mqtt_client_t              * const p_client,
                               mqtt_pubcomp_param_t const * const p_param)
{
    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_param);

    MQTT_TRC("[CID %p]:[State 0x%02x]: >> %s Message id 0x%04x",
                  p_client,
                  p_client->state,
                  __func__,
                  p_param->message_id);

    MQTT_MUTEX_LOCK();

    uint32_t  err_code = mqtt_message_id_only_enc_n_send(p_client,
                                                         MQTT_PKT_TYPE_PUBCOMP,
                                                         p_param->message_id);

    MQTT_TRC("[CID %p]:[State 0x%02x]: << %s result 0x%08x",
                  p_client,
                  p_client->state,
                  __func__,
                  err_code);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_disconnect(mqtt_client_t * const p_client)
{
    uint32_t   err_code = MQTT_ERR_NOT_CONNECTED;

    NULL_PARAM_CHECK(p_client);

    MQTT_MUTEX_LOCK();

    err_code = mqtt_raw_message_send(p_client, m_disc_packet, MQTT_FIXED_HEADER_SIZE);

    if (err_code == NRF_SUCCESS)
    {
        MQTT_SET_STATE_EXCLUSIVE(p_client, MQTT_STATE_DISCONNECTING);
    }

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_subscribe(mqtt_client_t                  * const p_client,
                        mqtt_subscription_list_t const * const p_param)
{
    uint32_t      err_code       = MQTT_ERR_NOT_CONNECTED;
    uint32_t      offset         = 0;
    uint32_t      count          = 0;
    uint32_t      mqtt_packetlen = 0;
    uint8_t     * p_payload;

    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_param);

    MQTT_TRC("[CID %p]:[State 0x%02x]: >> %s message id 0x%04x topic count 0x%04x",
                  p_client,
                  p_client->state,
                  __func__,
                  p_param->message_id,
                  p_param->list_count);

    MQTT_MUTEX_LOCK();

    p_payload = &p_client->p_packet[MQTT_FIXED_HEADER_EXTENDED_SIZE];

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_PENDING_WRITE))
    {
        err_code = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED))
    {
        memset(p_payload, 0, MQTT_MAX_PACKET_LENGTH);

        err_code = pack_uint16(p_param->message_id,
                               MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                               p_payload,
                               &offset);

        if (err_code == NRF_SUCCESS)
        {
            do
            {
                err_code = pack_utf8_str(&p_param->p_list[count].topic,
                                         MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                                         p_payload,
                                         &offset);
                if (err_code == NRF_SUCCESS)
                {
                    err_code = pack_uint8(p_param->p_list[count].qos,
                                          MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                                          p_payload,
                                          &offset);
                }
                count++;
            } while ((err_code != NRF_SUCCESS) || (count < p_param->list_count));
        }

        if (err_code == NRF_SUCCESS)
        {
            const uint8_t message_type = MQTT_MESSAGES_OPTIONS(MQTT_PKT_TYPE_SUBSCRIBE, 0, 1, 0);

            // Rewind the packet to encode the packet correctly.
            mqtt_packetlen = mqtt_encode_fixed_header(message_type, // Message type, Duplicate Flag, QoS and retain flag setting.
                                                      offset,       // p_payload size without the fixed header
                                                      &p_payload);  // Address where the p_payload is contained. Header will encoded by rewinding the location.
            // Send message.
            err_code = mqtt_transport_write(p_client, p_payload, mqtt_packetlen);
        }
    }

    MQTT_TRC("[CID %p]:[State 0x%02x]: << %s result 0x%08x",
                  p_client,
                  p_client->state,
                  __func__,
                  err_code);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_unsubscribe(mqtt_client_t                  * const p_client,
                          mqtt_subscription_list_t const * const p_param)
{
    uint32_t     err_code       = MQTT_ERR_NOT_CONNECTED;
    uint32_t     count          = 0;
    uint32_t     offset         = 0;
    uint32_t     mqtt_packetlen = 0;
    uint8_t    * p_payload;

    NULL_PARAM_CHECK(p_client);
    NULL_PARAM_CHECK(p_param);

    MQTT_MUTEX_LOCK();

    p_payload = &p_client->p_packet[MQTT_FIXED_HEADER_EXTENDED_SIZE];

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_PENDING_WRITE))
    {
        err_code = (NRF_ERROR_BUSY | IOT_MQTT_ERR_BASE);
    }
    else if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_CONNECTED))
    {
        memset(p_payload, 0, MQTT_MAX_PACKET_LENGTH);

        err_code = pack_uint16(p_param->message_id,
                               MQTT_MAX_PACKET_LENGTH,
                               p_payload,
                               &offset);

        if (err_code == NRF_SUCCESS)
        {
            do
            {
                err_code = pack_utf8_str(&p_param->p_list[count].topic,
                                         MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD,
                                         p_payload,
                                         &offset);
                count++;
            } while ((err_code != NRF_SUCCESS) || (count < p_param->list_count));
        }

        if (err_code == NRF_SUCCESS)
        {
            const uint8_t message_type = MQTT_MESSAGES_OPTIONS(MQTT_PKT_TYPE_UNSUBSCRIBE,
                                                               0, // Duplicate flag.
                                                               MQTT_QoS_1_ATLEAST_ONCE,
                                                               0); // Retain flag.

            // Rewind the packet to encode the packet correctly.
            mqtt_packetlen = mqtt_encode_fixed_header(message_type, // Message type, Duplicate Flag, QoS and retain flag setting.
                                                      offset,       // Payload size without the fixed header
                                                      &p_payload);  // Address where the p_payload is contained. Header will encoded by rewinding the location.

            // Send message.
            err_code = mqtt_transport_write(p_client, p_payload, mqtt_packetlen);
        }
    }

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_ping(mqtt_client_t * const p_client)
{
    uint32_t err_code;

    NULL_PARAM_CHECK(p_client);

    MQTT_MUTEX_LOCK();

    err_code = mqtt_raw_message_send(p_client, m_ping_packet, MQTT_PKT_HEADER_SIZE);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_abort(mqtt_client_t * const p_client)
{
    MQTT_MUTEX_LOCK();

    NULL_PARAM_CHECK(p_client);

    if (p_client->state != MQTT_STATE_IDLE)
    {
        mqtt_client_tcp_abort(p_client);
    }

    MQTT_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t mqtt_live(void)
{
    iot_timer_time_in_ms_t elapsed_time;
    uint32_t index;

    // Note: The module should not be locked when calling this TLS API.
    nrf_tls_process();

    MQTT_MUTEX_LOCK();

    for (index = 0; index < MQTT_MAX_CLIENTS; index++)
    {
        mqtt_client_t * p_client = m_mqtt_client[index];
        if (p_client != NULL)
        {
            UNUSED_VARIABLE(iot_timer_wall_clock_delta_get(&p_client->last_activity,
                                                           &elapsed_time));

            if ((MQTT_KEEPALIVE > 0) && (elapsed_time > ((MQTT_KEEPALIVE - 2) * 1000)))
            {
                UNUSED_VARIABLE(mqtt_ping(p_client));
            }
            if (p_client->p_pending_packet != NULL)
            {
                uint32_t err;
                err = mqtt_transport_write(p_client, p_client->p_pending_packet,
                                           p_client->pending_packetlen);

                if (err == NRF_SUCCESS)
                {
                    p_client->p_pending_packet  = NULL;
                    p_client->pending_packetlen = 0;
                }
            }
        }
    }

    MQTT_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t mqtt_input(mqtt_client_t * p_client, uint32_t timeout)
{
    uint32_t err_code;

    NULL_PARAM_CHECK(p_client);

    MQTT_MUTEX_LOCK();

    MQTT_TRC("%s: 0x%08x", __func__, p_client->state);

    if (MQTT_VERIFY_STATE(p_client, MQTT_STATE_TCP_CONNECTED) ||
        MQTT_VERIFY_STATE(p_client, MQTT_STATE_DISCONNECTING))
    {
        err_code = tcp_receive_packet(p_client, timeout);
    }
    else
    {
        err_code = (NRF_ERROR_INVALID_STATE | IOT_MQTT_ERR_BASE);
    }

    MQTT_MUTEX_UNLOCK();

    return err_code;
}
