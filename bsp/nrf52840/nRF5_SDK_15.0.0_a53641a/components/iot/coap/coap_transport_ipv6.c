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
#include "sdk_errors.h"
#include "sdk_config.h"
#include "iot_common.h"
#include "iot_pbuffer.h"
#include "coap_transport.h"
#include "coap.h"
#include "udp_api.h"


/**@brief UDP port information. */
typedef struct
{
    uint32_t    socket_id;                                 /**< Socket information provided by UDP. */
    uint16_t    port_number;                               /**< Associated port number. */
} udp_port_t;

static udp_port_t m_port_table[COAP_PORT_COUNT];           /**< Table maintaining association between CoAP ports and corresponding UDP socket identifiers. */


/**@brief Callback handler to receive data on the UDP port.
 *
 * @details Callback handler to receive data on the UDP port.
 *
 * @param[in]   p_socket         Socket identifier.
 * @param[in]   p_ip_header      IPv6 header containing source and destination addresses.
 * @param[in]   p_udp_header     UDP header identifying local and remote endpoints.
 * @param[in]   process_result   Result of data reception, there could be possible errors like
 *                               invalid checksum etc.
 * @param[in]   iot_pbuffer_t    Packet buffer containing the received data packet.
 *
 * @retval NRF_SUCCESS          Indicates received data was handled successfully, else an an
 *                              error code indicating reason for failure..
 */
static uint32_t port_data_callback(const udp6_socket_t * p_socket,
                                   const ipv6_header_t * p_ip_header,
                                   const udp6_header_t * p_udp_header,
                                   uint32_t              process_result,
                                   iot_pbuffer_t       * p_rx_packet)
{
    uint32_t                index;
    uint32_t                retval = NRF_ERROR_NOT_FOUND;

    //Search for the port.
    for (index = 0; index < COAP_PORT_COUNT; index++)
    {
        //Matching port found.
        if (m_port_table[index].socket_id == p_socket->socket_id)
        {
            coap_remote_t           remote_endpoint;
            coap_remote_t           local_endpoint;
            const coap_port_t       port       = {p_udp_header->destport};

            memcpy (remote_endpoint.addr, p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE);
            remote_endpoint.port_number = p_udp_header->srcport;

            memcpy (local_endpoint.addr, p_ip_header->destaddr.u8, IPV6_ADDR_SIZE);
            local_endpoint.port_number = p_udp_header->destport;

            COAP_MUTEX_LOCK();

            //Notify the module of received data.
            retval = coap_transport_read(&port,
                                         &remote_endpoint,
                                         &local_endpoint,
                                         process_result,
                                         p_rx_packet->p_payload,
                                         p_rx_packet->length);

            COAP_MUTEX_UNLOCK();
        }
    }

    return retval;
}


/**@brief Creates port as requested in p_port.
 *
 * @details Creates port as requested in p_port.
 *
 * @param[in]   index    Index to the m_port_table where entry of the port created is to be made.
 * @param[in]   p_port   Port information to be created.
 *
 * @retval NRF_SUCCESS   Indicates if port was created successfully, else an an  error code
 *                       indicating reason for failure.
 */
static uint32_t port_create(uint32_t index, coap_port_t  * p_port)
{
    uint32_t        err_code;
    udp6_socket_t   socket;

    //Request new socket creation.
    err_code = udp6_socket_allocate(&socket);

    if (err_code == NRF_SUCCESS)
    {
        // Bind the socket to the local port.
        err_code = udp6_socket_bind(&socket, IPV6_ADDR_ANY, p_port->port_number);
        if (err_code == NRF_SUCCESS)
        {
            //Register data receive callback.
            err_code = udp6_socket_recv(&socket, port_data_callback);
            if (err_code == NRF_SUCCESS)
            {
                //All procedure with respect to port creation succeeded, make entry in the table.
                m_port_table[index].socket_id   = socket.socket_id;
                m_port_table[index].port_number = p_port->port_number;
                socket.p_app_data = &m_port_table[index];
                UNUSED_VARIABLE(udp6_socket_app_data_set(&socket));
            }
        }

        if (err_code != NRF_SUCCESS)
        {
            //Not all procedures succeeded with allocated socket, hence free it.
            UNUSED_VARIABLE(udp6_socket_free(&socket));
        }
    }
    return err_code;
}


uint32_t coap_transport_init(const coap_transport_init_t   * p_param)
{
    uint32_t    err_code = NRF_ERROR_NO_MEM;
    uint32_t    index;

    NULL_PARAM_CHECK(p_param);
    NULL_PARAM_CHECK(p_param->p_port_table);

    for (index = 0; index < COAP_PORT_COUNT; index++)
    {
        // Create end point for each of the CoAP ports.
        err_code = port_create(index, &p_param->p_port_table[index]);
        if (err_code != NRF_SUCCESS)
        {
            break;
        }
    }

    return err_code;
}


uint32_t coap_transport_write(const coap_port_t    * p_port,
                              const coap_remote_t  * p_remote,
                              const uint8_t        * p_data,
                              uint16_t               datalen)
{
    uint32_t                       err_code = NRF_ERROR_NOT_FOUND;
    uint32_t                       index;
    udp6_socket_t                  socket;
    ipv6_addr_t                    remote_addr;
    iot_pbuffer_t                * p_buffer;
    iot_pbuffer_alloc_param_t      buffer_param;

    NULL_PARAM_CHECK(p_port);
    NULL_PARAM_CHECK(p_remote);
    NULL_PARAM_CHECK(p_data);

    memcpy(remote_addr.u8, p_remote->addr, 16);


    buffer_param.type   = UDP6_PACKET_TYPE;
    buffer_param.flags  = PBUFFER_FLAG_DEFAULT;
    buffer_param.length = datalen;

    //Search for the corresponding port.
    for (index = 0; index < COAP_PORT_COUNT; index ++)
    {
        if (m_port_table[index].port_number == p_port->port_number)
        {
            //Allocate buffer to send the data on port.
            err_code = iot_pbuffer_allocate(&buffer_param, &p_buffer);

            if (err_code == NRF_SUCCESS)
            {
                socket.socket_id = m_port_table[index].socket_id;

                //Make a copy of the data onto the buffer.
                memcpy (p_buffer->p_payload, p_data, datalen);

                COAP_MUTEX_UNLOCK();

                //Send on UDP port.
                err_code = udp6_socket_sendto(&socket,
                                              &remote_addr,
                                              p_remote->port_number,
                                              p_buffer);

                COAP_MUTEX_LOCK();

                if (err_code != NRF_SUCCESS)
                {
                    //Free the allocated buffer as send procedure has failed.
                    UNUSED_VARIABLE(iot_pbuffer_free(p_buffer, true));
                }
            }
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
    return NRF_ERROR_API_NOT_IMPLEMENTED;
}


uint32_t coap_security_destroy(uint16_t              local_port,
                               coap_remote_t * const p_remote)
{
    return NRF_ERROR_API_NOT_IMPLEMENTED;
}
