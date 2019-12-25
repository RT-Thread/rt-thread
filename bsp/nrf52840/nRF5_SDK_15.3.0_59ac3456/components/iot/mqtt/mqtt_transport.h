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
/** @file mqtt_transport.h
 *
 * @brief Internal functions to handle transport in MQTT module.
 */

#ifndef MQTT_TRANSPORT_H_
#define MQTT_TRANSPORT_H_

#include "mqtt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Transport for handling transport connect procedure. */
typedef uint32_t (*transport_connect_handler_t)(mqtt_client_t * p_client);

/**@brief Transport write handler. */
typedef uint32_t (*transport_write_handler_t)(mqtt_client_t * p_client, uint8_t const * data, uint32_t datalen);

/**@brief Transport read handler. */
typedef uint32_t (*transport_read_handler_t)(mqtt_client_t * p_client, uint8_t * data, uint32_t datalen);

/**@brief Transport disconnect handler. */
typedef uint32_t (*transport_disconnect_handler_t)(mqtt_client_t * p_client);

/**@brief Transport procedure handlers. */
typedef struct
{
    transport_connect_handler_t    connect;                                                         /**< Transport connect handler. Handles TCP connection callback based on type of transport.*/
    transport_write_handler_t      write;                                                           /**< Transport write handler. Handles transport write based on type of transport. */
    transport_read_handler_t       read;                                                            /**< Transport read handler. Handles transport read based on type of transport. */
    transport_disconnect_handler_t disconnect;                                                      /**< Transport disconnect handler. Handles transport disconnection based on type of transport. */
} transport_procedure_t;


/**@brief Handles TCP Connection Complete for configured transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_transport_connect(mqtt_client_t * p_client);


/**@brief Handles write requests on configured transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 * @param[in] p_data   Data to be written on the transport.
 * @param[in] datalen  Length of data to be written on the transport.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_transport_write(mqtt_client_t * p_client, uint8_t const * p_data, uint32_t datalen);


/**@brief Handles read requests on configured transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 * @param[in] p_data   Pointer where read data is to be fetched.
 * @param[in] datalen  Size of memory provided for the operation.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_transport_read(mqtt_client_t * p_client, uint8_t * p_data, uint32_t datalen);


/**@brief Handles transport disconnection requests on configured transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_transport_disconnect(mqtt_client_t * p_client);


/**@brief Initiates TCP Connection.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t tcp_request_connection(mqtt_client_t * p_client);


/**
 * @brief Wait for an incoming MQTT packet.
 *        The registered callback will be called with the packet payload.
 *
 * @param[in]  p_client  Client instance for which the procedure is requested.
 *                       Shall not be NULL.
 * @param[in]  timeout   Maximum interval (in milliseconds) to wait for a packet.
 *                       If timeout is 0, the interval is indefinitely.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t tcp_receive_packet(mqtt_client_t * p_client, uint32_t timeout);


/**@brief Handles TCP Connection Complete for TCP(non-secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tcp_connect(mqtt_client_t * p_client);


/**@brief Handles write requests on TCP(non-secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 * @param[in] p_data   Data to be written on the transport.
 * @param[in] datalen  Length of data to be written on the transport.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tcp_write(mqtt_client_t * p_client, uint8_t const * p_data, uint32_t datalen);


/**@brief Handles read requests on TCP(non-secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 * @param[in] p_data   Pointer where read data is to be fetched.
 * @param[in] datalen  Size of memory provided for the operation.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tcp_read(mqtt_client_t * p_client, uint8_t * p_data, uint32_t datalen);


/**@brief Handles transport disconnection requests on TCP(non-secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tcp_disconnect(mqtt_client_t * p_client);


/**@brief Handles read requests on TLS(secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 * @param[in] p_data   Pointer where read data is to be fetched.
 * @param[in] datalen  Size of memory provided for the operation.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tls_connect(mqtt_client_t * p_client);


/**@brief Handles write requests on TLS(secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 * @param[in] p_data   Data to be written on the transport.
 * @param[in] datalen  Length of data to be written on the transport.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tls_write(mqtt_client_t * p_client, uint8_t const * p_data, uint32_t datalen);


/**@brief Handles read requests on TLS(secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 * @param[in] p_data   Pointer where read data is to be fetched.
 * @param[in] datalen  Size of memory provided for the operation.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tls_read(mqtt_client_t * p_client, uint8_t * p_data, uint32_t datalen);


/**@brief Handles transport disconnection requests on TLS(secure) transport.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
uint32_t mqtt_client_tls_disconnect(mqtt_client_t * p_client);


/**@brief Aborts TCP connection.
 *
 * @param[in] p_client Identifies the client on which the procedure is requested.
 *
 * @retval NRF_SUCCESS or an error code indicating reason for failure.
 */
void mqtt_client_tcp_abort(mqtt_client_t * p_client);

#ifdef __cplusplus
}
#endif

#endif // MQTT_TRANSPORT_H_
