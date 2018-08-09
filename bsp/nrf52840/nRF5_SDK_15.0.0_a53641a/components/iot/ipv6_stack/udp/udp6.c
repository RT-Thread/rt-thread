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
#include "nordic_common.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "iot_common.h"
#include "iot_pbuffer.h"
#include "udp_api.h"
#include "udp.h"
#include "ipv6_utils.h"

#if UDP6_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME udp6

#define NRF_LOG_LEVEL       UDP6_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  UDP6_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR UDP6_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define UDP6_TRC     NRF_LOG_DEBUG                                                                  /**< Used for getting trace of execution in the module. */
#define UDP6_ERR     NRF_LOG_ERROR                                                                  /**< Used for logging errors in the module. */
#define UDP6_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                          /**< Used for dumping octet information to get details of bond information etc. */

#define UDP6_ENTRY() UDP6_TRC(">> %s", __func__)
#define UDP6_EXIT()  UDP6_TRC("<< %s", __func__)

#else // UDP6_CONFIG_LOG_ENABLED

#define UDP6_TRC(...)                                                                               /**< Disables traces. */
#define UDP6_DUMP(...)                                                                              /**< Disables dumping of octet streams. */
#define UDP6_ERR(...)                                                                               /**< Disables error logs. */

#define UDP6_ENTRY(...)
#define UDP6_EXIT(...)

#endif // UDP6_CONFIG_LOG_ENABLED

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          UDP_DISABLE_API_PARAM_CHECK should be set to 1 to disable these checks.
 *
 * @{
 */
#if (UDP6_DISABLE_API_PARAM_CHECK == 0)

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                                                             \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return (SDK_ERR_MODULE_NOT_INITIALIZED | IOT_UDP6_ERR_BASE);                           \
        }

/**@brief Macro to check is module is initialized before requesting one of the module
         procedures but does not use any return code. */
#define VERIFY_MODULE_IS_INITIALIZED_VOID()                                                        \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return;                                                                                \
        }

/**
 * @brief Verify NULL parameters are not passed to API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_UDP6_ERR_BASE);                                           \
        }

/**
 * @brief Verify socket id passed on the API by application is valid.
 */
#define VERIFY_SOCKET_ID(ID)                                                                       \
        if (((ID) >=  UDP6_MAX_SOCKET_COUNT))                                                      \
        {                                                                                          \
            return (NRF_ERROR_INVALID_ADDR | IOT_UDP6_ERR_BASE);                                   \
        }

/**
 * @brief Verify socket id passed on the API by application is valid.
 */
#define VERIFY_PORT_NUMBER(PORT)                                                                   \
        if ((PORT) ==  0)                                                                          \
        {                                                                                          \
            return (NRF_ERROR_INVALID_PARAM | IOT_UDP6_ERR_BASE);                                  \
        }

/**
 * @brief Verify socket id passed on the API by application is valid.
 */
#define VERIFY_NON_ZERO_LENGTH(LEN)                                                                \
        if ((LEN) ==  0)                                                                           \
        {                                                                                          \
            return (NRF_ERROR_INVALID_LENGTH | IOT_UDP6_ERR_BASE);                                 \
        }

#else // UDP6_DISABLE_API_PARAM_CHECK

#define VERIFY_MODULE_IS_INITIALIZED()
#define VERIFY_MODULE_IS_INITIALIZED_VOID()
#define NULL_PARAM_CHECK(PARAM)
#define VERIFY_SOCKET_ID(ID)
#endif //UDP6_DISABLE_API_PARAM_CHECK

/**
 * @defgroup ble_ipsp_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define UDP_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_udp_mutex)                                   /**< Lock module using mutex */
#define UDP_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_udp_mutex)                                 /**< Unlock module using mutex */
/** @} */

#define UDP_PORT_FREE  0                                                                 /**< Reserved port of the socket, indicates that port is free. */

/**@brief UDP Socket Data needed by the module to manage it. */
typedef struct
{
    uint16_t           local_port;                                                       /**< Local Port of the socket. */
    uint16_t           remote_port;                                                      /**< Remote port of the socket. */
    ipv6_addr_t        local_addr;                                                       /**< Local IPv6 Address of the socket. */
    ipv6_addr_t        remote_addr;                                                      /**< Remote IPv6 Address of the socket. */
    udp6_handler_t     rx_cb;                                                            /**< Callback registered by application to receive data on the socket. */
    void             * p_app_data;                                                       /**< Application data mapped to the socket using the udp6_app_data_set. */
} udp_socket_entry_t;


SDK_MUTEX_DEFINE(m_udp_mutex)                                                            /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */
static bool      m_initialization_state  = false;                                        /**< Variable to maintain module initialization state. */
static udp_socket_entry_t  m_socket[UDP6_MAX_SOCKET_COUNT];                              /**< Table of sockets managed by the module. */


/** @brief Initializes socket managed by the module. */
static void udp_socket_init(udp_socket_entry_t * p_socket)
{
    p_socket->local_port  = UDP_PORT_FREE;
    p_socket->remote_port = UDP_PORT_FREE;
    p_socket->rx_cb       = NULL;
    p_socket->p_app_data  = NULL;
    IPV6_ADDRESS_INITIALIZE(&p_socket->local_addr);
    IPV6_ADDRESS_INITIALIZE(&p_socket->remote_addr);
}

/**
 * @brief Find UDP socket based on local port. If found its index to m_socket table is returned.
 *        else  UDP6_MAX_SOCKET_COUNT is returned.
 */
static uint32_t socket_find(uint16_t port)
{
    uint32_t index;

    for (index = 0; index < UDP6_MAX_SOCKET_COUNT; index++)
    {
        if (m_socket[index].local_port == port)
        {
            break;
        }
    }

    return index;
}


uint32_t udp_init(void)
{
    uint32_t index;

    UDP6_ENTRY();

    SDK_MUTEX_INIT(m_udp_mutex);

    UDP_MUTEX_LOCK();

    for (index = 0; index < UDP6_MAX_SOCKET_COUNT; index++)
    {
        udp_socket_init(&m_socket[index]);
    }

    m_initialization_state = true;

    UDP6_EXIT();

    UDP_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t udp6_socket_allocate(udp6_socket_t  * p_socket)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    //Search for an unassigned socket.
    const uint32_t socket_id = socket_find(UDP_PORT_FREE);
    uint32_t       err_code  = NRF_SUCCESS;

    if (socket_id != UDP6_MAX_SOCKET_COUNT)
    {
        UDP6_TRC("Assigned socket 0x%08lX", socket_id);

        // Found a free socket. Assign.
        p_socket->socket_id = socket_id;
    }
    else
    {
        // No free socket found.
        UDP6_ERR("No room for new socket.");
        err_code = (NRF_ERROR_NO_MEM | IOT_UDP6_ERR_BASE);
    }

    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return err_code;
}


uint32_t udp6_socket_free(const udp6_socket_t * p_socket)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);
    VERIFY_SOCKET_ID(p_socket->socket_id);

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    udp_socket_init(&m_socket[p_socket->socket_id]);

    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return NRF_SUCCESS;
}


uint32_t udp6_socket_recv(const udp6_socket_t  * p_socket,
                          const udp6_handler_t   callback)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);
    NULL_PARAM_CHECK(callback);
    VERIFY_SOCKET_ID(p_socket->socket_id);
    VERIFY_PORT_NUMBER(m_socket[p_socket->socket_id].local_port);

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    m_socket[p_socket->socket_id].rx_cb = callback;

    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return NRF_SUCCESS;
}


uint32_t udp6_socket_bind(const udp6_socket_t * p_socket,
                          const ipv6_addr_t   * p_src_addr,
                          uint16_t              src_port)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);
    NULL_PARAM_CHECK(p_src_addr);
    VERIFY_SOCKET_ID(p_socket->socket_id);
    VERIFY_PORT_NUMBER(src_port);

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    uint32_t err_code = NRF_SUCCESS;

    // Change Host Byte Order to Network Byte Order.
    src_port = HTONS(src_port);

    //Check if port is already registered.
    for (uint32_t index = 0; index < UDP6_MAX_SOCKET_COUNT; index ++)
    {
        if (m_socket[index].local_port == src_port)
        {
            err_code = UDP_PORT_IN_USE;
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        m_socket[p_socket->socket_id].local_port = src_port;
        m_socket[p_socket->socket_id].local_addr = (*p_src_addr);

    }
    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return err_code;
}


uint32_t udp6_socket_connect(const udp6_socket_t * p_socket,
                             const ipv6_addr_t   * p_dest_addr,
                             uint16_t              dest_port)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);
    NULL_PARAM_CHECK(p_dest_addr);
    VERIFY_SOCKET_ID(p_socket->socket_id);
    VERIFY_PORT_NUMBER(dest_port);
    VERIFY_PORT_NUMBER(m_socket[p_socket->socket_id].local_port);

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    m_socket[p_socket->socket_id].remote_port = HTONS(dest_port);
    m_socket[p_socket->socket_id].remote_addr = (*p_dest_addr);

    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return NRF_SUCCESS;
}


uint32_t udp6_socket_send(const udp6_socket_t * p_socket,
                          iot_pbuffer_t       * p_packet)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);
    NULL_PARAM_CHECK(p_packet);
    NULL_PARAM_CHECK(p_packet->p_payload);
    VERIFY_NON_ZERO_LENGTH(p_packet->length);
    VERIFY_SOCKET_ID(p_socket->socket_id);
    VERIFY_PORT_NUMBER(m_socket[p_socket->socket_id].local_port);
    VERIFY_PORT_NUMBER(m_socket[p_socket->socket_id].remote_port);

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    uint32_t err_code;
    const udp_socket_entry_t  * p_skt       = &m_socket[p_socket->socket_id];
    const uint32_t    header_size = UDP_HEADER_SIZE + IPV6_IP_HEADER_SIZE;
    udp6_header_t   * p_header    = (udp6_header_t *)(p_packet->p_payload - UDP_HEADER_SIZE);
    ipv6_header_t   * p_ip_header = (ipv6_header_t *)(p_packet->p_payload - header_size);
    iot_interface_t * p_interface = NULL;
    uint16_t          checksum;

    p_header->srcport  = p_skt->local_port;
    p_header->destport = p_skt->remote_port;
    p_header->checksum = 0;

    p_header->length = HTONS(p_packet->length  + UDP_HEADER_SIZE);

    // Pack destination address.
    p_ip_header->destaddr = p_skt->remote_addr;

    // Pack source address.
    if ((0 == IPV6_ADDRESS_CMP(&p_skt->local_addr, IPV6_ADDR_ANY)))
    {
        err_code = ipv6_address_find_best_match(&p_interface,
                                                &p_ip_header->srcaddr,
                                                &p_ip_header->destaddr);
    }
    else
    {
        err_code = ipv6_address_find_best_match(&p_interface,
                                                NULL,
                                                &p_ip_header->destaddr);

        p_ip_header->srcaddr = p_skt->local_addr;
    }

    if (err_code == NRF_SUCCESS)
    {
        // Pack next header.
        p_ip_header->next_header             = IPV6_NEXT_HEADER_UDP;

        //Pack HOP Limit.
        p_ip_header->hoplimit                = IPV6_DEFAULT_HOP_LIMIT;

        //Traffic class and flow label.
        p_ip_header->version_traffic_class   = 0x60;
        p_ip_header->traffic_class_flowlabel = 0x00;
        p_ip_header->flowlabel               = 0x0000;

        // Length.
        p_ip_header->length                  = HTONS(p_packet->length + UDP_HEADER_SIZE);

        checksum = p_packet->length + UDP_HEADER_SIZE + IPV6_NEXT_HEADER_UDP;

        ipv6_checksum_calculate(p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_packet->p_payload - UDP_HEADER_SIZE,
                                p_packet->length + UDP_HEADER_SIZE,
                                &checksum,
                                true);

        p_header->checksum = HTONS((~checksum));

        p_packet->p_payload -= header_size;
        p_packet->length    += header_size;

        err_code = ipv6_send(p_interface, p_packet);
    }
    else
    {
        err_code = UDP_INTERFACE_NOT_READY;
    }

    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return err_code;
}


uint32_t udp6_socket_sendto(const udp6_socket_t    * p_socket,
                            const ipv6_addr_t      * p_dest_addr,
                            uint16_t                 dest_port,
                            iot_pbuffer_t          * p_packet)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);
    NULL_PARAM_CHECK(p_dest_addr);
    NULL_PARAM_CHECK(p_packet);
    NULL_PARAM_CHECK(p_packet->p_payload);
    VERIFY_NON_ZERO_LENGTH(p_packet->length);
    VERIFY_SOCKET_ID(p_socket->socket_id);
    VERIFY_PORT_NUMBER(dest_port);

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    uint32_t err_code;
    const udp_socket_entry_t  * p_skt       = &m_socket[p_socket->socket_id];
    const uint32_t    header_size = UDP_HEADER_SIZE + IPV6_IP_HEADER_SIZE;
    udp6_header_t   * p_header    = (udp6_header_t *)(p_packet->p_payload - UDP_HEADER_SIZE);
    ipv6_header_t   * p_ip_header = (ipv6_header_t *)(p_packet->p_payload - header_size);
    iot_interface_t * p_interface = NULL;
    uint16_t          checksum;

    p_header->srcport  = p_skt->local_port;
    p_header->destport = HTONS(dest_port);
    p_header->checksum = 0;

    checksum = p_packet->length + UDP_HEADER_SIZE + IPV6_NEXT_HEADER_UDP;

    p_header->length = HTONS(p_packet->length + UDP_HEADER_SIZE);

    //Pack destination address.
    p_ip_header->destaddr = *p_dest_addr;

    // Pack source address.
    if ((0 == IPV6_ADDRESS_CMP(&p_skt->local_addr, IPV6_ADDR_ANY)))
    {
        err_code = ipv6_address_find_best_match(&p_interface,
                                                &p_ip_header->srcaddr,
                                                &p_ip_header->destaddr);
    }
    else
    {
        err_code = ipv6_address_find_best_match(&p_interface,
                                                NULL,
                                                &p_ip_header->destaddr);

        p_ip_header->srcaddr = p_skt->local_addr;
    }

    if (err_code == NRF_SUCCESS)
    {
        //Pack next header.
        p_ip_header->next_header             = IPV6_NEXT_HEADER_UDP;

        //Pack HOP Limit.
        p_ip_header->hoplimit                = IPV6_DEFAULT_HOP_LIMIT;

        //Traffic class and flow label.
        p_ip_header->version_traffic_class   = 0x60;
        p_ip_header->traffic_class_flowlabel = 0x00;
        p_ip_header->flowlabel               = 0x0000;

        // Length.
        p_ip_header->length                  = HTONS(p_packet->length + UDP_HEADER_SIZE);

        ipv6_checksum_calculate(p_ip_header->srcaddr.u8,  IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
        ipv6_checksum_calculate(p_packet->p_payload - UDP_HEADER_SIZE,
                                p_packet->length + UDP_HEADER_SIZE,
                                &checksum,
                                true);

        p_header->checksum = HTONS((~checksum));

        p_packet->p_payload -= header_size;
        p_packet->length    += header_size;

        err_code = ipv6_send(p_interface, p_packet);
    }
    else
    {
        err_code = UDP_INTERFACE_NOT_READY;
    }

    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return err_code;
}


uint32_t udp6_socket_app_data_set(const udp6_socket_t * p_socket)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_socket);
    VERIFY_SOCKET_ID(p_socket->socket_id);

    //Note: no null check is performed on the p_app_data as it is permissible
    //to pass on a NULL value if need be.

    UDP6_ENTRY();

    UDP_MUTEX_LOCK();

    m_socket[p_socket->socket_id].p_app_data = p_socket->p_app_data;

    UDP_MUTEX_UNLOCK();

    UDP6_EXIT();

    return NRF_SUCCESS;
}


uint32_t udp_input(const iot_interface_t  * p_interface,
                   const ipv6_header_t    * p_ip_header,
                   iot_pbuffer_t          * p_packet)
{
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_ip_header);
    NULL_PARAM_CHECK(p_packet);

    UNUSED_VARIABLE(p_interface);

    uint32_t err_code = (NRF_ERROR_NOT_FOUND | IOT_UDP6_ERR_BASE);

    if ((p_packet->length > UDP_HEADER_SIZE) && (p_ip_header->length > UDP_HEADER_SIZE))
    {
        UDP_MUTEX_LOCK();

        UDP6_ENTRY();

        uint32_t index;
        udp6_header_t * p_udp_header = (udp6_header_t *)(p_packet->p_payload);

        // Check to which UDP socket, port and address was bind.
        for (index = 0; index < UDP6_MAX_SOCKET_COUNT; index ++)
        {
            if (m_socket[index].local_port == p_udp_header->destport)
            {
                if ((0 == IPV6_ADDRESS_CMP(&m_socket[index].local_addr, IPV6_ADDR_ANY)) ||
                   (0 == IPV6_ADDRESS_CMP(&m_socket[index].local_addr, &p_ip_header->destaddr)))
                {
                    // Check if connection was established.
                    if (m_socket[index].remote_port == 0 || m_socket[index].remote_port == p_udp_header->srcport)
                    {
                        if ((0 == IPV6_ADDRESS_CMP(&m_socket[index].remote_addr, IPV6_ADDR_ANY)) ||
                           (0 == IPV6_ADDRESS_CMP(&m_socket[index].remote_addr, &p_ip_header->srcaddr)))
                           {
                                err_code = NRF_SUCCESS;
                                break;
                           }
                    }
                }
            }
        }

        if (index < UDP6_MAX_SOCKET_COUNT)
        {
            uint16_t checksum = p_packet->length +  IPV6_NEXT_HEADER_UDP;
            uint32_t process_result = NRF_SUCCESS;
            uint16_t udp_hdr_length = NTOHS(p_udp_header->length);

            if (udp_hdr_length > p_packet->length)
            {
                UDP6_ERR("Received truncated packet, "
                         "payload length 0x%08lX, length in header 0x%08X.",
                         p_packet->length, NTOHS(p_udp_header->length));
                process_result = UDP_TRUNCATED_PACKET;
            }
            else if (udp_hdr_length < p_packet->length)
            {
                UDP6_ERR("Received malformed packet, "
                         "payload length 0x%08lX, length in header 0x%08X.",
                         p_packet->length, NTOHS(p_udp_header->length));

                process_result = UDP_MALFORMED_PACKET;
            }
            else
            {
                ipv6_checksum_calculate(p_ip_header->srcaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
                ipv6_checksum_calculate(p_ip_header->destaddr.u8, IPV6_ADDR_SIZE, &checksum, false);
                ipv6_checksum_calculate(p_packet->p_payload, p_packet->length, &checksum, false);

                if (checksum != 0 && checksum != 0xFFFF)
                {
                    UDP6_ERR("Bad checksum detected.");
                    process_result = UDP_BAD_CHECKSUM;
                }
            }

            p_packet->p_payload  = p_packet->p_payload + UDP_HEADER_SIZE;
            p_packet->length    -= UDP_HEADER_SIZE;

            //Found port for which data is intended.
            const  udp6_socket_t sock  = {index, m_socket[index].p_app_data};

            //Give application a callback if callback is registered.
            if (m_socket[index].rx_cb != NULL)
            {
                UDP_MUTEX_UNLOCK();

                // Change byte ordering given to application.
                p_udp_header->destport = NTOHS(p_udp_header->destport);
                p_udp_header->srcport  = NTOHS(p_udp_header->srcport);
                p_udp_header->length   = NTOHS(p_udp_header->length);
                p_udp_header->checksum = NTOHS(p_udp_header->checksum);

                err_code = m_socket[index].rx_cb(&sock, p_ip_header, p_udp_header, process_result, p_packet);

                UDP_MUTEX_LOCK();
            }
        }
        else
        {
            UDP6_ERR("Packet received on unknown port, dropping!");
        }

        UDP_MUTEX_UNLOCK();

        UDP6_EXIT();
    }
    else
    {
        UDP6_ERR("Packet of length less than UDP header size received!");
        err_code = (IOT_UDP6_ERR_BASE | NRF_ERROR_INVALID_LENGTH);
    }

    return err_code;
}
