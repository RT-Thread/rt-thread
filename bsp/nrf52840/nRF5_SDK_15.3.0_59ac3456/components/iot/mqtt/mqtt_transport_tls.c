/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
 * @brief MQTT Client Implementation TLS layer.
 *
 * This file contains the source code for MQTT Protocol TLS layer for a nRF device.
 * The implementation is limited to MQTT Client role only.
 */


#include "mqtt_transport.h"
#include "mqtt_internal.h"
#include "mqtt_rx.h"
#include "mem_manager.h"

#if MQTT_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME mqtt_tls

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

uint32_t mqtt_client_tls_output_handler(nrf_tls_instance_t const * p_instance,
                                        uint8_t            const * p_data,
                                        uint32_t                   datalen)
{
    NULL_PARAM_CHECK(p_instance);

    uint32_t          err_code = NRF_ERROR_INTERNAL;
    mqtt_client_t   * p_client = (mqtt_client_t *)p_instance->transport_id;

    MQTT_MUTEX_LOCK();

    MQTT_TRC(">> %s, client %p", __func__, p_client);

    if (p_client != NULL)
    {
        err_code = mqtt_client_tcp_write(p_client, p_data, datalen);
    }

    MQTT_TRC("<< %s, client %p, result 0x%08x", __func__,
                  p_client, err_code);

    MQTT_MUTEX_UNLOCK();

    return err_code;
}


uint32_t mqtt_client_tls_connect(mqtt_client_t * p_client)
{
    const nrf_tls_options_t tls_option =
    {
        .output_fn      = mqtt_client_tls_output_handler,
        .transport_type = NRF_TLS_TYPE_STREAM,
        .role           = NRF_TLS_ROLE_CLIENT,
        .p_key_settings = p_client->p_security_settings
    };

    connect_request_encode(p_client,
                           &p_client->p_pending_packet,
                           &p_client->pending_packetlen);

    p_client->tls_instance.transport_id = (uint32_t)p_client;

    MQTT_MUTEX_UNLOCK ();

    uint32_t err_code = nrf_tls_alloc(&p_client->tls_instance, &tls_option);

    MQTT_MUTEX_LOCK ();

    return err_code;
}


uint32_t mqtt_client_tls_write(mqtt_client_t * p_client,
                               uint8_t const * p_data,
                               uint32_t        datalen)
{
    MQTT_MUTEX_UNLOCK ();

    uint32_t err_code = nrf_tls_write(&p_client->tls_instance, p_data, &datalen);

    MQTT_MUTEX_LOCK ();

    return err_code;
}


uint32_t mqtt_client_tls_read(mqtt_client_t * p_client, uint8_t * p_data, uint32_t datalen)
{
    uint32_t err = nrf_tls_input(&p_client->tls_instance, p_data, datalen);

    if ((err == NRF_SUCCESS) && (p_client->p_pending_packet == NULL))
    {
        uint32_t   rx_datalen  = 1024;
        uint8_t  * p_mqtt_data = nrf_malloc(1024);

        if (p_data != NULL)
        {
            MQTT_MUTEX_UNLOCK ();

            err = nrf_tls_read(&p_client->tls_instance,
                               p_mqtt_data,
                               &rx_datalen);

            MQTT_MUTEX_LOCK ();

            if ((err == NRF_SUCCESS) && (rx_datalen > 0))
            {
                 err = mqtt_handle_rx_data(p_client, p_mqtt_data, rx_datalen);
            }

            nrf_free(p_mqtt_data);
        }
    }

    return err;
}


uint32_t mqtt_client_tls_disconnect(mqtt_client_t * p_client)
{
    return mqtt_client_tcp_disconnect(p_client);
}
