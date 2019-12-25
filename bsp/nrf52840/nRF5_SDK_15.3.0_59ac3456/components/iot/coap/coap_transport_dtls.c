/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#include "nrf_error.h"
#include "nrf_drv_rng.h"
#include "sdk_config.h"
#include "iot_common.h"
#include "iot_pbuffer.h"
#include "coap_transport.h"
#include "coap.h"
#include "udp_api.h"
#include "nrf_tls.h"
#include "mem_manager.h"
#include "iot_errors.h"


#if IOT_COAP_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME coap_dtls

#define NRF_LOG_LEVEL       IOT_COAP_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IOT_COAP_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IOT_COAP_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define COAPT_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define COAPT_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define COAPT_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define COAPT_ENTRY()                       COAPT_TRC(">> %s", __func__)
#define COAPT_EXIT()                        COAPT_TRC("<< %s", __func__)
#define COAPT_ENTRY_WITH_READLEN(read_len)  COAPT_TRC(">> %s, readlen %d", __func__, read_len)
#define COAPT_EXIT_WITH_RESULT(result)      COAPT_TRC("<< %s, result 0x%08lX", __func__, result)

#else // IOT_COAP_CONFIG_LOG_ENABLED

#define COAPT_TRC(...)                                                                           /**< Disables traces. */
#define COAPT_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define COAPT_ERR(...)                                                                           /**< Disables error logs. */

#define COAPT_ENTRY(...)
#define COAPT_EXIT(...)
#define COAPT_ENTRY_WITH_READLEN(...)
#define COAPT_EXIT_WITH_RESULT(...)

#endif // IOT_COAP_CONFIG_LOG_ENABLED

/**@brief Max size to be requested from the DTLS library when polling for decoded CoAP data. */
#define MAX_BUFFER_SIZE          1024


/**@brief UDP port information. */
typedef struct
{
    uint32_t                 socket_id;                                        /**<  Socket information provided by UDP. */
    uint16_t                 port_number;                                      /**<  Associated port number. */
    nrf_tls_key_settings_t * p_settings;                                       /**<  Key preferences. */
} udp_port_t;

/**@brief CoAP remote session. Encapsulates information needed for DTLS. */
typedef struct
{
    nrf_tls_instance_t   dtls_instance;                                        /**< DTLS instance identifier. */
    coap_remote_t        remote_endpoint;                                      /**< Remote endoint indentification. */
    uint16_t             local_port_index;                                     /**< Identifies local endpoint assoicated with the session. */
} coap_remote_session_t;

/**@brief Possible CoAP transport types. Needed for internal handling of events and data. */
typedef enum
{
    COAP_TRANSPORT_NON_SECURE_DATAGRAM = 0,                                    /**< Non-secure transport, no DTLS procedures apply. */
    COAP_TRANSPORT_SECURE_DATAGRAM     = 1,                                    /**< Secure transport, DTLS procedures apply. */
    COAP_TRANSPORT_MAX_TYPES           = 2                                     /**< Maximum transport types. Not a valid transport identifer used as max count. */
} coap_transport_type_t;

/**
 * @brief Transport write handler signature.
 *
 * @param[in] p_remote          Remote endpoint on which data is to be written.
 * @param[in] local_port_index  Local endpoint identifier writing the data.
 * @param[in] p_data            Data to be written.
 * @param[in] datalen           Length of data to be written.
 *
 * @retval NRF_SUCCESS if the procedure was successful, else an error code indicating reason for
 *         failure.
 */
typedef uint32_t (* port_write_t) (const coap_remote_t  * const p_remote,
                                   uint32_t               local_port_index,
                                   const uint8_t        * p_data,
                                   uint16_t               datalen);

/**
 * @brief Transport read handler signature.
 *
 * @param[in] p_remote          Remote endpoint which sent data.
 * @param[in] local_port_index  Local endpoint identifier to which the data was sent.
 * @param[in] p_data            Data read on the transport.
 * @param[in] datalen           Length of data read on the transport.
 *
 * @retval NRF_SUCCESS if the procedure was successful, else an error code indicating reason for
 *         failure.
 */
typedef uint32_t (* port_read_t) (const coap_remote_t  * const p_remote,
                                  uint32_t               local_port_index,
                                  uint32_t               read_result,
                                  const uint8_t        * p_data,
                                  uint16_t               datalen);

/** Forward declaration. */
uint32_t non_secure_datagram_write (const coap_remote_t  * const p_remote,
                                    uint32_t               local_port_index,
                                    const uint8_t        * p_data,
                                    uint16_t               datalen);

/** Forward declaration. */
uint32_t secure_datagram_write (const coap_remote_t  * const p_remote,
                                uint32_t               local_port_index,
                                const uint8_t        * p_data,
                                uint16_t               datalen);

/** Forward declaration. */
uint32_t non_secure_datagram_read (const coap_remote_t  * const p_remote,
                                   uint32_t               local_port_index,
                                   uint32_t               read_result,
                                   const uint8_t        * p_data,
                                   uint16_t               datalen);

/** Forward declaration. */
uint32_t secure_datagram_read(const coap_remote_t  * const p_remote,
                              uint32_t               local_port_index,
                              uint32_t               read_result,
                              const uint8_t        * p_data,
                              uint16_t               datalen);

/** Forward declaration. */
uint32_t dtls_output_handler(nrf_tls_instance_t const * p_instance,
                             uint8_t            const * p_data,
                             uint32_t                   datalen);

static udp_port_t            m_port_table[COAP_PORT_COUNT];                    /**< Table maintaining association between CoAP ports and corresponding UDP socket identifiers. */
static coap_remote_session_t m_remote_session[COAP_DTLS_MAX_REMOTE_SESSION];        /**< Table for managing security sessions with remote endpoints. */

/**@brief Table of transport write handlers. */
const port_write_t port_write_fn[COAP_TRANSPORT_MAX_TYPES] =
{
    non_secure_datagram_write,
    secure_datagram_write
};

/**@brief Table of transport read handlers. */
const port_read_t port_read_fn[COAP_TRANSPORT_MAX_TYPES] =
{
    non_secure_datagram_read,
    secure_datagram_read
};


/**
 * @brief Searches the local port reference based on the port number.
 *
 * @param[out] p_index    Pointer where local port refernce should be provided (if found).
 * @param[in]  port_query Port number for which local port reference is requested.
 *
 * @retval NRF_SUCCESS if procedure succeeded else NRF_ERROR_NOT_FOUND.
 */
static uint32_t local_port_index_get(uint32_t * p_index, uint16_t port_query)
{
    uint32_t local_port_index;

    // Find local port index.
    for (local_port_index = 0; local_port_index < COAP_PORT_COUNT; local_port_index++)
    {
        if (m_port_table[local_port_index].port_number == port_query)
        {
            break;
        }
    }

    // If we could not find the local port requested in the port table.
    if (local_port_index >= COAP_PORT_COUNT)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    *p_index = local_port_index;

    return NRF_SUCCESS;
}


/**
 * @brief Session to be initialized/freed.
 *
 * @param[in] p_session Session
 */
static void remote_session_init(coap_remote_session_t * p_session)
{
    memset(p_session, 0, sizeof(coap_remote_session_t));
    NRF_TLS_INTSANCE_INIT(&p_session->dtls_instance);
}


/**
 * @brief Creates DTLS session between remote and local endpoint.
 *
 * @param[in]  local_port_index    Identifies local endpoint.
 * @param[in]  role                Identifies DTLS role to be played (server or client).
 * @param[in]  p_remote            Identifies remote endpoint.
 * @param[in]  p_settings          Security settings to be used for the session.
 * @param[out] pp_session          Pointer to the session created (if any).
 *
 * @retval NRF_SUCCESS is procedure succeeded else an error code indicating reason for failure.
 */
static uint32_t session_create(uint32_t                       local_port_index,
                               nrf_tls_role_t                 role,
                               const coap_remote_t    * const p_remote,
                               nrf_tls_key_settings_t * const p_settings,
                               coap_remote_session_t  **      pp_session)
{
    uint32_t err_code = NRF_ERROR_NO_MEM;

    for (uint32_t index = 0; index < COAP_DTLS_MAX_REMOTE_SESSION; index++)
    {
        if (m_remote_session[index].remote_endpoint.port_number == 0)
        {
            // Found free session.
            m_remote_session[index].remote_endpoint.port_number = p_remote->port_number;
            memcpy(m_remote_session[index].remote_endpoint.addr, p_remote->addr, IPV6_ADDR_SIZE);
            m_remote_session[index].local_port_index = local_port_index;

            // Attempt Allocate TLS session.
            const nrf_tls_options_t dtls_options =
            {
                .output_fn      = dtls_output_handler,
                .transport_type = NRF_TLS_TYPE_DATAGRAM,
                .role           = role,
                .p_key_settings = p_settings
            };

            m_remote_session[index].dtls_instance.transport_id = index;

            COAP_MUTEX_UNLOCK();

            err_code = nrf_tls_alloc(&m_remote_session[index].dtls_instance, &dtls_options);

            COAP_MUTEX_LOCK();

            COAPT_TRC("[%p]: nrf_tls_alloc result %08x",
                       &m_remote_session[index],
                       err_code);

            // TLS allocation succeeded, book keep information for endpoint.
            if (err_code == NRF_SUCCESS)
            {
                (*pp_session) = &m_remote_session[index];
                break;
            }
            else
            {
                // If free the session and notify failure.
                remote_session_init(&m_remote_session[index]);
            }
        }
    }

    return err_code;
}


/**
 * @brief API to free TLS session.
 *
 * @param[in] p_session Identifies the session to be freed.
 */
static __INLINE void session_free (coap_remote_session_t * p_session)
{
    // Free TLS session.
    UNUSED_VARIABLE(nrf_tls_free(&p_session->dtls_instance));

    // Free the session.
    remote_session_init(p_session);
}


/**
 * @brief Searches for DTLS session between remote and local endpoint.
 *
 * @param[in]  local_port_index    Identifies local endpoint.
 * @param[in]  p_remote            Identifies remote endpoint.
 * @param[out] pp_session          Pointer to the session found (if any).
 *
 * @retval NRF_SUCCESS is procedure succeeded else NRF_ERROR_NOT_FOUND.
 */
uint32_t remote_session_search(uint32_t                 local_port_index,
                               const coap_remote_t    * p_remote,
                               coap_remote_session_t ** pp_session)
{
    uint32_t err_code = NRF_ERROR_NOT_FOUND;
    uint32_t index    = 0;


    for (index = 0; index < COAP_DTLS_MAX_REMOTE_SESSION; index++)
    {
        const coap_remote_session_t * session = &m_remote_session[index];
        if ((session->local_port_index == local_port_index)                 &&
            (session->remote_endpoint.port_number == p_remote->port_number) &&
            ((memcmp(session->remote_endpoint.addr, p_remote->addr, IPV6_ADDR_SIZE) == 0)))
        {
            // Entry exists.
            (*pp_session) = (coap_remote_session_t *)session;
            err_code      = NRF_SUCCESS;
            break;
        }
    }

    return err_code;
}


/**
 * @brief Provides transport type to be used between remote and local endpoint.
 *
 * @param[in]  local_port_index    Identifies local endpoint.
 * @param[in]  p_remote            Identifies remote endpoint.
 *
 * @retval COAP_TRANSPORT_SECURE_DATAGRAM     if transport type to be used is secure.
 * @retval COAP_TRANSPORT_NON_SECURE_DATAGRAM if transport type to be used is non-secure.
 */
uint8_t get_transport_type(uint32_t local_port_index, const coap_remote_t * p_remote)
{
    coap_remote_session_t * p_session;
    uint8_t transport_type = COAP_TRANSPORT_NON_SECURE_DATAGRAM;

    uint32_t err_code = remote_session_search(local_port_index, p_remote, &p_session);
    if (err_code == NRF_SUCCESS)
    {
        COAPT_TRC("Transport type  = SECURE");
        transport_type = COAP_TRANSPORT_SECURE_DATAGRAM;
    }
    else if (m_port_table[local_port_index].p_settings != NULL)
    {
        COAPT_TRC("Transport type  = SECURE");
        transport_type = COAP_TRANSPORT_SECURE_DATAGRAM;
    }
    else
    {
        COAPT_TRC("Transport type  = NON-SECURE");
    }

    return transport_type;
}


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
 * @retval      NRF_SUCCESS      Indicates received data was handled successfully, else an an
 *                               error code indicating reason for failure..
 */
static uint32_t port_data_callback(const udp6_socket_t * p_socket,
                                   const ipv6_header_t * p_ip_header,
                                   const udp6_header_t * p_udp_header,
                                   uint32_t              process_result,
                                   iot_pbuffer_t       * p_rx_packet)
{
    uint32_t                index;
    uint32_t                retval = NRF_ERROR_NOT_FOUND;

    COAPT_TRC("port_data_callback: Src Port %d Dest Port %d. Len %08lx",
                       p_udp_header->srcport, p_udp_header->destport, p_rx_packet->length);

    COAP_MUTEX_LOCK();

    //Search for the port.
    for (index = 0; index < COAP_PORT_COUNT; index++)
    {
        if (m_port_table[index].socket_id == p_socket->socket_id)
        {
            COAPT_TRC("port_data_callback->coap_transport_read");

            //Matching port found.
            coap_remote_t   remote_endpoint;

            memcpy(remote_endpoint.addr, p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE);
            remote_endpoint.port_number = p_udp_header->srcport;

            uint8_t transport_type = get_transport_type(index, &remote_endpoint);

            // Handle read data on scoket based on nature of transport.
            retval = port_read_fn[transport_type](&remote_endpoint,
                                                  index,
                                                  process_result,
                                                  p_rx_packet->p_payload,
                                                  p_rx_packet->length);
            break;
        }
    }

    COAP_MUTEX_UNLOCK();

    return retval;
}


/**
 * @brief Transport read handler for non secure transport type.
 *
 * @param[in] p_remote          Remote endpoint which sent data.
 * @param[in] local_port_index  Local endpoint identifier to which the data was sent.
 * @param[in] read_result       Indicator result of data read on the transport.
 *                              Likely failures include UDP checksum failure, truncated packet etc.
 * @param[in] p_data            Data read on the transport.
 * @param[in] datalen           Length of data read on the transport.
 *
 * @retval NRF_SUCCESS if the procedure was successful, else an error code indicating reason for
 *         failure.
 */
uint32_t non_secure_datagram_read (const coap_remote_t  * const p_remote,
                                   uint32_t                     local_port_index,
                                   uint32_t                     read_result,
                                   const uint8_t        *       p_data,
                                   uint16_t                     datalen)
{
    const coap_port_t port =
    {
       .port_number = m_port_table[local_port_index].port_number
    };

    return coap_transport_read(&port,
                               p_remote,
                               NULL,
                               read_result,
                               p_data,
                               datalen);
}


/**
 * @brief Transport write handler for non secure transport type.
 *
 * @param[in] p_remote          Remote endpoint on which data is to be written.
 * @param[in] local_port_index  Local endpoint identifier writing the data.
 * @param[in] p_data            Data to be written.
 * @param[in] datalen           Length of data to be written.
 *
 * @retval NRF_SUCCESS if the procedure was successful, else an error code indicating reason for
 *         failure.
 */
uint32_t non_secure_datagram_write(const coap_remote_t * p_remote,
                                   uint32_t              index,
                                   const uint8_t       * p_data,
                                   uint16_t              datalen)
{
    uint32_t                       err_code;
    udp6_socket_t                  socket;
    ipv6_addr_t                    remote_addr;
    iot_pbuffer_t                * p_buffer;
    iot_pbuffer_alloc_param_t      buffer_param;

    buffer_param.type   = UDP6_PACKET_TYPE;
    buffer_param.flags  = PBUFFER_FLAG_DEFAULT;
    buffer_param.length = datalen;

    COAPT_TRC("[LP %04X]:[RP %04X]: port_write, datalen %d",
                        m_port_table[index].port_number,
                        p_remote->port_number,
                        datalen);

    memcpy(remote_addr.u8, p_remote->addr, IPV6_ADDR_SIZE);

    // Allocate buffer to send the data on port.
    err_code = iot_pbuffer_allocate(&buffer_param, &p_buffer);

    COAPT_TRC("port_write->iot_pbuffer_allocate result 0x%08X", err_code);

    if (err_code == NRF_SUCCESS)
    {
        socket.socket_id = m_port_table[index].socket_id;

        // Make a copy of the data onto the buffer.
        memcpy(p_buffer->p_payload, p_data, datalen);

        // Send on UDP port.
        err_code = udp6_socket_sendto(&socket,
                                      &remote_addr,
                                      p_remote->port_number,
                                      p_buffer);

        COAPT_TRC("port_write->udp6_socket_sendto result 0x%08X", err_code);
        if (err_code != NRF_SUCCESS)
        {
            // Free the allocated buffer as send procedure has failed.
            UNUSED_VARIABLE(iot_pbuffer_free(p_buffer, true));
        }
    }

    return err_code;
}


/**
 * @brief Transport read handler for secure transport type.
 *
 * @param[in] p_remote          Remote endpoint which sent data.
 * @param[in] local_port_index  Local endpoint identifier to which the data was sent.
 * @param[in] read_result       Indicator result of data read on the transport.
 *                              Likely failures include UDP checksum failure, truncated packet etc.
 * @param[in] p_data            Data read on the transport.
 * @param[in] datalen           Length of data read on the transport.
 *
 * @retval NRF_SUCCESS if the procedure was successful, else an error code indicating reason for
 *         failure.
 */
uint32_t secure_datagram_read(const coap_remote_t  * const p_remote,
                              uint32_t               local_port_index,
                              uint32_t               read_result,
                              const uint8_t        * p_data,
                              uint16_t               datalen)
{
    const uint32_t          read_len  = datalen;
    uint32_t                err_code;
    coap_remote_session_t * p_session = NULL;

    COAPT_ENTRY_WITH_READLEN(read_len);

    // Search is a session exists.
    err_code = remote_session_search(local_port_index, p_remote, &p_session);

    if (err_code == NRF_SUCCESS)
    {
        COAPT_TRC("Remote session found, processing.");

        COAP_MUTEX_UNLOCK();

        // Session exists, send data to DTLS for decryption.
        err_code = nrf_tls_input(&p_session->dtls_instance, p_data, read_len);

        COAP_MUTEX_LOCK();
    }
    else
    {
        COAPT_TRC("Remote session not found, look for server security settings.");
        if (m_port_table[local_port_index].p_settings != NULL)
        {
            // Allocate a session for incoming client.
            err_code = session_create(local_port_index,
                                      NRF_TLS_ROLE_SERVER,
                                      p_remote,
                                      m_port_table[local_port_index].p_settings,
                                      &p_session);

            if (err_code == NRF_SUCCESS)
            {
                COAP_MUTEX_UNLOCK();

                COAPT_TRC("[%p]: New session created as DTLS server.", p_session);

                err_code = nrf_tls_input(&p_session->dtls_instance, p_data, read_len);

                COAP_MUTEX_LOCK();
            }
            else
            {
                COAPT_TRC("New session creation failed, reason 0x%08x.", err_code);
            }
        }
        else
        {
            COAPT_TRC("No remote session, no server settings, processing as raw");
            err_code = non_secure_datagram_read(p_remote,
                                                local_port_index,
                                                read_result,
                                                p_data,
                                                datalen);
        }
    }

    COAPT_EXIT_WITH_RESULT(err_code);

    return err_code;
}


/**
 * @brief Transport write handler for secure transport type.
 *
 * @param[in] p_remote          Remote endpoint on which data is to be written.
 * @param[in] local_port_index  Local endpoint identifier writing the data.
 * @param[in] p_data            Data to be written.
 * @param[in] datalen           Length of data to be written.
 *
 * @retval NRF_SUCCESS if the procedure was successful, else an error code indicating reason for
 *         failure.
 */
uint32_t secure_datagram_write(const coap_remote_t  * const  p_remote,
                               uint32_t                      local_port_index,
                               const uint8_t        *        p_data,
                               uint16_t                      datalen)
{

    uint32_t                err_code;
    coap_remote_session_t * p_session;

    // Search is a session exists.
    err_code = remote_session_search(local_port_index, p_remote, &p_session);

    if (err_code == NRF_ERROR_NOT_FOUND)
    {
        // No session found, return error.
        err_code = COAP_TRANSPORT_SECURITY_MISSING;
    }
    else
    {
        // Session exists, attempt a secure write.
        uint32_t actual_len = datalen;
        err_code = nrf_tls_write(&p_session->dtls_instance, p_data, &actual_len);
    }

    return err_code;
}


/**
 * @brief Handles DTLS output to be sent on the underlying UDP transport.
 *
 * @param[in] p_instance        Identifies the TLS instance associated with the output.
 * @param[in] p_data            DTLS library output data to be written on the transport.
 * @param[in] datalen           Length of data.
 *
 * @retval NRF_SUCCESS if the procedure was successful, else an error code indicating reason for
 *         failure.
 */
uint32_t dtls_output_handler(nrf_tls_instance_t const * p_instance,
                             uint8_t            const * p_data,
                             uint32_t                   datalen)
{
    const uint16_t transport_write_len = datalen;

    if (p_instance->transport_id >= COAP_DTLS_MAX_REMOTE_SESSION)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    COAP_MUTEX_LOCK();

    coap_remote_session_t * p_session = &m_remote_session[p_instance->transport_id];
    uint32_t                err_code  = NRF_ERROR_NOT_FOUND;

    if (p_session->remote_endpoint.port_number != 0)
    {
        // Search for instance in remote sessions.
        err_code = non_secure_datagram_write(&p_session->remote_endpoint,
                                             p_session->local_port_index,
                                             p_data,
                                             transport_write_len);
    }

    COAP_MUTEX_UNLOCK();

    return err_code;
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

    // Request new socket creation.
    err_code = udp6_socket_allocate(&socket);

    if (err_code == NRF_SUCCESS)
    {
        // Bind the socket to the local port.
        err_code = udp6_socket_bind(&socket, IPV6_ADDR_ANY, p_port->port_number);

        if (err_code == NRF_SUCCESS)
        {
            // Register data receive callback.
            err_code = udp6_socket_recv(&socket, port_data_callback);

            if (err_code == NRF_SUCCESS)
            {
                // All procedure with respect to port creation succeeded, make entry in the table.
                m_port_table[index].socket_id      = socket.socket_id;
                m_port_table[index].port_number    = p_port->port_number;
                m_port_table[index].p_settings     = NULL;

                socket.p_app_data = &m_port_table[index];
                UNUSED_VARIABLE(udp6_socket_app_data_set(&socket));
            }
        }

        if (err_code != NRF_SUCCESS)
        {
            // Not all procedures succeeded with allocated socket, hence free it.
            UNUSED_VARIABLE(udp6_socket_free(&socket));
        }
    }
    return err_code;
}


uint32_t coap_transport_init(const coap_transport_init_t * p_param)
{
    uint32_t    err_code = NRF_ERROR_NO_MEM;
    uint32_t    index;

    NULL_PARAM_CHECK(p_param);
    NULL_PARAM_CHECK(p_param->p_port_table);

    err_code = nrf_tls_init();

    if (err_code == NRF_SUCCESS)
    {
        for (index = 0; index < COAP_PORT_COUNT; index++)
        {
            // Create end point for each of the CoAP ports.
            err_code = port_create(index, &p_param->p_port_table[index]);
            if (err_code != NRF_SUCCESS)
            {
                break;
            }
        }

        for (index = 0; index < COAP_DTLS_MAX_REMOTE_SESSION; index++)
        {
            remote_session_init(&m_remote_session[index]);
        }
    }

    return err_code;
}


uint32_t coap_transport_write(const coap_port_t    * p_port,
                              const coap_remote_t  * p_remote,
                              const uint8_t        * p_data,
                              uint16_t               datalen)
{
    uint32_t                err_code = NRF_ERROR_NOT_FOUND;
    uint32_t                index;

    NULL_PARAM_CHECK(p_port);
    NULL_PARAM_CHECK(p_remote);
    NULL_PARAM_CHECK(p_data);

    COAP_MUTEX_LOCK();

    //Search for the corresponding port.
    for (index = 0; index < COAP_PORT_COUNT; index++)
    {
        if (m_port_table[index].port_number == p_port->port_number)
        {
            // Get transport type for remote and local.
            uint8_t transport_type = get_transport_type(index, p_remote);

            err_code = port_write_fn[transport_type](p_remote,
                                                     index,
                                                     p_data,
                                                     datalen);
            break;
        }
    }

    COAP_MUTEX_UNLOCK();

    return err_code;
}


void coap_transport_process(void)
{
    nrf_tls_process();

    for (uint32_t index = 0; index < COAP_DTLS_MAX_REMOTE_SESSION; index++)
    {
        coap_remote_session_t * p_session = &m_remote_session[index];

        if (p_session->remote_endpoint.port_number != 0x0000)
        {
            uint32_t  datalen = MAX_BUFFER_SIZE;

            COAP_MUTEX_UNLOCK();

            // Check if there is data to be processed/read.
            uint32_t err_code = nrf_tls_read(&p_session->dtls_instance, NULL, &datalen);

            COAP_MUTEX_LOCK();

            COAPT_TRC("nrf_tls_read result %d", err_code);

            if ((err_code == NRF_SUCCESS) && (datalen > 0))
            {
                COAPT_TRC("nrf_tls_read datalen %d", datalen);

                // Allocate memory and fecth data from DTLS layer.
                uint8_t  * p_data      = NULL;
                uint32_t   buffer_size = datalen;

                err_code = nrf_mem_reserve(&p_data, &buffer_size);

                if (p_data != NULL)
                {
                    COAP_MUTEX_UNLOCK();

                    err_code = nrf_tls_read(&p_session->dtls_instance, p_data, &datalen);

                    COAP_MUTEX_LOCK();

                    if ((err_code == NRF_SUCCESS) && (datalen > 0))
                    {
                        UNUSED_VARIABLE(non_secure_datagram_read(&p_session->remote_endpoint,
                                                                 p_session->local_port_index,
                                                                 NRF_SUCCESS,
                                                                 p_data,
                                                                 datalen));
                    }

                    // Free the memory reserved for the incoming packet.
                    nrf_free(p_data);
                }
            }
        }
    }
}


uint32_t coap_security_setup(uint16_t                       local_port,
                             nrf_tls_role_t                 role,
                             coap_remote_t          * const p_remote,
                             nrf_tls_key_settings_t * const p_settings)
{
    uint32_t                err_code = NRF_ERROR_NO_MEM;
    uint32_t                local_port_index;
    coap_remote_session_t * p_session;

    COAP_MUTEX_LOCK();

    // Find local port index.
    err_code = local_port_index_get(&local_port_index, local_port);

    if (err_code == NRF_SUCCESS)
    {
        if (role == NRF_TLS_ROLE_CLIENT)
        {
            if (p_remote == NULL)
            {
                // Clients can never register session with wildcard remote.
                err_code = NRF_ERROR_NULL;
            }
            else
            {
                // Search is a session exists.
                err_code = remote_session_search(local_port_index, p_remote, &p_session);

                if (err_code != NRF_SUCCESS)
                {
                    // Session does not already exist, create one.
                    err_code = session_create(local_port_index,
                                              role, p_remote,
                                              p_settings,
                                              &p_session);
                }
            }
        }
        else
        {
            // For server role, disallow client specific settings.
            // This may not always be desired. But a constraint added in current design.
            if (p_remote != NULL)
            {
                err_code = NRF_ERROR_INVALID_PARAM;
            }
            else
            {
                // Cannot overwrite settings.
                if (m_port_table[local_port_index].p_settings != NULL)
                {
                    err_code = NRF_ERROR_FORBIDDEN;
                }
                else
                {
                    COAPT_TRC("[0x%08lx]: Server security setup successful",
                              local_port_index);

                    m_port_table[local_port_index].p_settings = p_settings;
                }
            }

        }
    }

    COAP_MUTEX_UNLOCK();

    return err_code;
}


uint32_t coap_security_destroy(uint16_t              local_port,
                               coap_remote_t * const p_remote)
{
    uint32_t                err_code;
    coap_remote_session_t * p_session;
    uint32_t                local_port_index;

    COAP_MUTEX_LOCK();

    // Find local port index.
    err_code = local_port_index_get(&local_port_index, local_port);

    if (err_code == NRF_SUCCESS)
    {
        if (p_remote != NULL)
        {
            // Search is a session exists.
            err_code = remote_session_search(local_port_index, p_remote, &p_session);

            if (err_code == NRF_SUCCESS)
            {
                session_free(p_session);
            }
        }
        else
        {
            // Remove all session associated with the local port if p_remote is NULL.
            for (uint32_t index = 0; index < COAP_DTLS_MAX_REMOTE_SESSION ; index++)
            {
                if (m_remote_session[index].local_port_index == local_port_index)
                {
                     session_free(&m_remote_session[index]);
                }
            }
        }
    }

    COAP_MUTEX_UNLOCK();

    return err_code;
}
