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
/** @file mqtt_rx.c
 *
 * @brief Handles packet receive on transport TCP or TLS.
 */
#include "mqtt_internal.h"

void event_notify(mqtt_client_t * const p_client, const mqtt_evt_t * p_evt, uint32_t flags);
void disconnect_event_notify(mqtt_client_t * p_client, uint32_t result);

#if MQTT_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME mqtt_rx

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

static uint32_t mqtt_handle_packet(mqtt_client_t * p_client,
                                   uint8_t       * p_data,
                                   uint32_t        datalen,
                                   uint32_t        offset)
{
    mqtt_evt_t    evt;
    uint32_t      err_code = NRF_SUCCESS;
    bool          notify_event = true;

    // Success by default, overwritten in special cases.
    evt.result = NRF_SUCCESS;

    switch (p_data[0] & 0xF0)
    {
        case MQTT_PKT_TYPE_CONNACK:
        {
            MQTT_TRC("[%p]: Received MQTT_PKT_TYPE_CONNACK!", p_client);

            if (p_client->protocol_version == MQTT_VERSION_3_1_1)
            {
                evt.param.connack.session_present_flag = p_data[2] & MQTT_HEADER_CONNACK_MASK;

                MQTT_TRC("[%p]: session_present_flag: %d",
                              p_client,
                              evt.param.connack.session_present_flag);
            }

            evt.param.connack.return_code =
                                   (mqtt_conn_return_code_t)(p_data[3] & MQTT_HEADER_CONNACK_MASK);

            MQTT_TRC("[%p]: return_code: %d",
                          p_client,
                          evt.param.connack.return_code);

            if (evt.param.connack.return_code == MQTT_CONNECTION_ACCEPTED)
            {
                // Set state.
                MQTT_SET_STATE(p_client, MQTT_STATE_CONNECTED);
            }

            evt.result = evt.param.connack.return_code;
            evt.id = MQTT_EVT_CONNACK;

            break;
        }
        case MQTT_PKT_TYPE_PUBLISH:
        {
            evt.param.publish.dup_flag          = p_data[0] & MQTT_HEADER_DUP_MASK;
            evt.param.publish.retain_flag       = p_data[0] & MQTT_HEADER_RETAIN_MASK;
            evt.param.publish.message.topic.qos = ((p_data[0] & MQTT_HEADER_QOS_MASK) >> 1);

            MQTT_TRC("[CID %p]: Received MQTT_PKT_TYPE_PUBLISH, QoS:%02x",
                          p_client, evt.param.publish.message.topic.qos);

            err_code = unpack_utf8_str(&evt.param.publish.message.topic.topic,
                                       datalen,
                                       p_data,
                                       &offset);

            if (err_code == NRF_SUCCESS)
            {
                if (evt.param.publish.message.topic.qos)
                {
                    err_code = unpack_uint16(&evt.param.publish.message_id,
                                             datalen,
                                             p_data,
                                             &offset);
                }
            }

            if (err_code == NRF_SUCCESS)
            {
                err_code = unpack_bin_str(&evt.param.publish.message.payload,
                                          datalen,
                                          p_data,
                                          &offset);

                // Zero length publish messages are permitted.
                if (err_code != NRF_SUCCESS)
                {
                     evt.param.publish.message.payload.p_bin_str = NULL;
                     evt.param.publish.message.payload.bin_strlen = 0;
                }
            }

            MQTT_TRC("PUB message len %08x, topic len %08x",
                          evt.param.publish.message.payload.bin_strlen,
                          evt.param.publish.message.topic.topic.utf_strlen);

            evt.id     = MQTT_EVT_PUBLISH;
            evt.result = err_code;

            UNUSED_VARIABLE(iot_timer_wall_clock_get(&p_client->last_activity));

            break;
        }

        case MQTT_PKT_TYPE_PUBACK:
        {
            MQTT_TRC("Received MQTT_PKT_TYPE_PUBACK!");

            evt.id     = MQTT_EVT_PUBACK;
            err_code   = unpack_uint16(&evt.param.puback.message_id,
                                       datalen,
                                       p_data,
                                       &offset);
            evt.result = err_code;
            break;
        }

        case MQTT_PKT_TYPE_PUBREC:
        {
            MQTT_TRC("Received MQTT_PKT_TYPE_PUBREC!");

            evt.id     = MQTT_EVT_PUBREC;
            err_code   = unpack_uint16(&evt.param.pubrec.message_id,
                                       datalen,
                                       p_data,
                                       &offset);
            evt.result = err_code;
            break;
        }
        case MQTT_PKT_TYPE_PUBREL:
        {
            MQTT_TRC("Received MQTT_PKT_TYPE_PUBREL!");

            evt.id     = MQTT_EVT_PUBREL;
            err_code   = unpack_uint16(&evt.param.pubrel.message_id,
                                       datalen,
                                       p_data,
                                       &offset);
            evt.result = err_code;
            break;
        }
        case MQTT_PKT_TYPE_PUBCOMP:
        {
            MQTT_TRC("Received MQTT_PKT_TYPE_PUBCOMP!");

            evt.id     = MQTT_EVT_PUBCOMP;
            err_code   = unpack_uint16(&evt.param.pubcomp.message_id,
                                       datalen,
                                       p_data,
                                       &offset);
            evt.result = err_code;
            break;
        }
        case MQTT_PKT_TYPE_SUBACK:
        {
            MQTT_TRC("Received MQTT_PKT_TYPE_SUBACK!");

            evt.id     = MQTT_EVT_SUBACK;
            err_code   = unpack_uint16(&evt.param.pubrec.message_id,
                                       datalen,
                                       p_data,
                                       &offset);
            evt.result = err_code;
            break;
        }
        case MQTT_PKT_TYPE_UNSUBACK:
        {
            MQTT_TRC("Received MQTT_PKT_TYPE_UNSUBACK!");

            evt.id     = MQTT_EVT_UNSUBACK;
            err_code   = unpack_uint16(&evt.param.pubrec.message_id,
                                       datalen,
                                       p_data,
                                       &offset);
            evt.result = err_code;
            break;
        }
        case MQTT_PKT_TYPE_PINGRSP:
        {
            MQTT_TRC("Received MQTT_PKT_TYPE_PINGRSP!");

            // No notification of Ping response to application.
            notify_event = false;
            break;
        }
        default:
        {
            // Nothing to notify.
            notify_event = false;
            break;
        }
    }

    if (notify_event == true)
    {
        event_notify(p_client, &evt, MQTT_EVT_FLAG_NONE);
    }

    return err_code;
}


uint32_t mqtt_handle_rx_data(mqtt_client_t * p_client, uint8_t * p_data, uint32_t datalen)
{
    uint32_t      err_code = NRF_SUCCESS;
    uint32_t      offset = 0;

    while (offset < datalen)
    {
        uint32_t start = offset;
        uint32_t remaining_length = 0;

        offset = 1; // Skip first byte to offset MQTT packet length.
        err_code = packet_length_decode(p_data + start,
                                        datalen - start,
                                        &remaining_length,
                                        &offset);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        uint32_t packet_length = offset + remaining_length;

        if (start + packet_length > datalen)
        {
            return NRF_ERROR_INVALID_LENGTH;
        }

        err_code = mqtt_handle_packet(p_client,
                                      p_data + start,
                                      packet_length,
                                      offset);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        offset = start + packet_length;
    }

    return err_code;
}
