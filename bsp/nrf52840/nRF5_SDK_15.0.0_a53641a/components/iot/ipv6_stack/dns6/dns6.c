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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "sdk_errors.h"
#include "sdk_os.h"
#include "sdk_config.h"
#include "iot_common.h"
#include "iot_pbuffer.h"
#include "mem_manager.h"
#include "ipv6_api.h"
#include "udp_api.h"
#include "dns6_api.h"

#if DNS6_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME dns6

#define NRF_LOG_LEVEL       DNS6_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  DNS6_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR DNS6_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define DNS6_TRC     NRF_LOG_DEBUG                                                                  /**< Used for getting trace of execution in the module. */
#define DNS6_ERR     NRF_LOG_ERROR                                                                  /**< Used for logging errors in the module. */
#define DNS6_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                          /**< Used for dumping octet information to get details of bond information etc. */

#define DNS6_ENTRY() DNS6_TRC(">> %s", __func__)
#define DNS6_EXIT()  DNS6_TRC("<< %s", __func__)

#else // DNS6_CONFIG_LOG_ENABLED

#define DNS6_TRC(...)                                                                               /**< Disables traces. */
#define DNS6_DUMP(...)                                                                              /**< Disables dumping of octet streams. */
#define DNS6_ERR(...)                                                                               /**< Disables error logs. */

#define DNS6_ENTRY(...)
#define DNS6_EXIT(...)

#endif // DNS6_CONFIG_LOG_ENABLED

/**
 * @defgroup dns6_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define DNS6_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_dns6_mutex)                                            /**< Lock module using mutex */
#define DNS6_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_dns6_mutex)                                          /**< Unlock module using mutex */
/** @} */

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          DNS6_DISABLE_API_PARAM_CHECK should be set to 0 to enable these checks.
 *
 * @{
 */

#if (DNS6_DISABLE_API_PARAM_CHECK == 0)

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                              \
    if (m_initialization_state == false)                            \
    {                                                               \
        return (SDK_ERR_MODULE_NOT_INITIALIZED | IOT_DNS6_ERR_BASE);\
    }

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                     \
    if ((PARAM) == NULL)                                            \
    {                                                               \
        return (NRF_ERROR_NULL | IOT_DNS6_ERR_BASE);                \
    }

/**@brief Verify that empty parameters are not passed to API by application. */
#define EMPTY_PARAM_CHECK(PARAM)                                    \
    if (*PARAM == 0)                                                \
    {                                                               \
        return (NRF_ERROR_INVALID_DATA | IOT_DNS6_ERR_BASE);        \
    }

#else // DNS6_DISABLE_API_PARAM_CHECK

#define VERIFY_MODULE_IS_INITIALIZED()
#define NULL_PARAM_CHECK(PARAM)
#define EMPTY_PARAM_CHECK(PARAM)

#endif // DNS6_DISABLE_API_PARAM_CHECK
/** @} */

/**@brief RFC1035 - DNS Header Fields and Values. */
#define DNS_HEADER_FLAG1_QR_QUERY              0x00                                                 /**< Bit specifies that message is a query. */
#define DNS_HEADER_FLAG1_QR_RESPONSE           0x80                                                 /**< Bit specifies that message is a response. */
#define DNS_HEADER_FLAG1_OPCODE_STANDARD       0x00                                                 /**< A standard type of query. */
#define DNS_HEADER_FLAG1_OPCODE_INVERSE        0x08                                                 /**< An inverse type of query. */
#define DNS_HEADER_FLAG1_OPCODE_STATUS         0x10                                                 /**< A server status request. */
#define DNS_HEADER_FLAG1_AA                    0x04                                                 /**< Bit specifies that the responding name server is an authority for the domain name in question section. */
#define DNS_HEADER_FLAG1_TC                    0x02                                                 /**< Bit specifies that message is truncated. */
#define DNS_HEADER_FLAG1_RD                    0x01                                                 /**< Bit specifies that recursion is desired. */

#define DNS_HEADER_FLAG2_RA                    0x80                                                 /**< Bit specifies if recursive query support is available in the name server. */
#define DNS_HEADER_FLAG2_RCODE_NONE            0x00                                                 /**< No error condition. */
#define DNS_HEADER_FLAG2_RCODE_FORMAT_ERROR    0x01                                                 /**< Error indicates that dns server is unable o interpret the query. */
#define DNS_HEADER_FLAG2_RCODE_SERVER_FAILURE  0x02                                                 /**< Error indicates that dns server has internal problem. */
#define DNS_HEADER_FLAG2_RCODE_NAME_ERROR      0x03                                                 /**< Error indicates that domain name referenced in the query does not exist. */
#define DNS_HEADER_FLAG2_RCODE_NOT_IMPLEMENTED 0x04                                                 /**< Error indicates that dns server does not support previously sent query. */
#define DNS_HEADER_FLAG2_RCODE_REFUSED         0x05                                                 /**< Error indicates that dns server refuses to perform operation. */
#define DNS_HEADER_FLAG2_RCODE_MASK            0x0F                                                 /**< Bit mask of RCODE field. */

#define DNS_QTYPE_A                            0x0001                                               /**< QTYPE indicates IPv4 address. */
#define DNS_QTYPE_CNAME                        0x0005                                               /**< QTYPE indicates CNAME record. */
#define DNS_QTYPE_AAAA                         0x001C                                               /**< QTYPE indicates IPv6 address. */

#define DNS_QCLASS_IN                          0x0001                                               /**< QCLASS indicates Internet type. */

/**@brief DNS6 client module's defines. */
#define DNS_LABEL_SEPARATOR                    '.'                                                  /**< Separator of hostname string. */
#define DNS_LABEL_OFFSET                       0xc0                                                 /**< Byte indicates that offset is used to determine hostname. */

#define DNS_HEADER_SIZE                        12                                                   /**< Size of DNS Header. */
#define DNS_QUESTION_FOOTER_SIZE               4                                                    /**< Size of DNS Question footer. */
#define DNS_RR_BODY_SIZE                       10                                                   /**< Size of DNS Resource Record Body. */

#define MESSAGE_ID_UNUSED                      0                                                    /**< Value indicates that record is unused and no request was performed yet. */
#define MESSAGE_ID_INITIAL                     0x0001                                               /**< Initial value of message id counter. */


/**@brief DNS Header Format. */
typedef struct
{
    uint16_t msg_id;                                                                                /**< Query/Response message identifier. */
    uint8_t  flags_1;                                                                               /**< Flags ( QR | Opcode | AA | TC | RD ). */
    uint8_t  flags_2;                                                                               /**< Flags ( RA | Z | RCODE ). */
    uint16_t qdcount;                                                                               /**< The number of entries in the question section. */
    uint16_t ancount;                                                                               /**< The number of resource records in the answer section. */
    uint16_t nscount;                                                                               /**< The number of name server resource records in the authority records section. */
    uint16_t arcount;                                                                               /**< The number of resource records in the additional records section. */
} dns_header_t;

/**@brief DNS Question Footer Format. */
typedef struct
{
    uint16_t qtype;                                                                                 /**< Type of the query. */
    uint16_t qclass;                                                                                /**< Class of the query. */
} dns_question_footer_t;

/**@brief DNS Resource AAAA Record Body Format. */
typedef struct
{
    uint16_t rtype;                                                                                 /**< Type of the response. */
    uint16_t rclass;                                                                                /**< Class of the response. */
    uint32_t rttl;                                                                                  /**< Time to Life field of the response. */
    uint16_t rdlength;                                                                              /**< Length of data in octets. */
} dns_rr_body_t;

/**@brief Structure holds pending query. */
typedef struct
{
    uint16_t                 message_id;                                                            /**< Message id for DNS Query. */
    uint8_t                  retries;                                                               /**< Number of already performed retries. */
    uint8_t                * p_hostname;                                                            /**< Pointer to hostname string in memory menager.*/
    iot_timer_time_in_ms_t   next_retransmission;                                                   /**< Time when next retransmission should be invoked. */
    dns6_evt_handler_t       evt_handler;                                                           /**< User registered callback. */
} pending_query_t;

SDK_MUTEX_DEFINE(m_dns6_mutex)                                                                      /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */
static bool            m_initialization_state = false;                                              /**< Variable to maintain module initialization state. */
static pending_query_t m_pending_queries[DNS6_MAX_PENDING_QUERIES];                                 /**< Queue contains pending queries. */
static uint16_t        m_message_id_counter;                                                        /**< Message ID counter, used to generate unique message IDs. */
static udp6_socket_t   m_socket;                                                                    /**< Socket information provided by UDP. */


/**@brief Function for freeing query entry in pending queue.
 *
 * @param[in] index  Index of query.
 *
 * @retval None.
 */
static void query_init(uint32_t index)
{
    if (m_pending_queries[index].p_hostname)
    {
        UNUSED_VARIABLE(nrf_free(m_pending_queries[index].p_hostname));
    }

    m_pending_queries[index].message_id          = MESSAGE_ID_UNUSED;
    m_pending_queries[index].retries             = 0;
    m_pending_queries[index].p_hostname          = NULL;
    m_pending_queries[index].evt_handler         = NULL;
    m_pending_queries[index].next_retransmission = 0;
}


/**@brief Function for adding new query to pending queue.
 *
 * @param[in] p_hostname  Pointer to hostname string.
 * @param[in] evt_handler User defined event to handle given query.
 *
 * @retval Index of element in pending queries' table or DNS6_MAX_PENDING_QUERIES if no memory.
 */
static uint32_t query_add(uint8_t * p_hostname, dns6_evt_handler_t evt_handler)
{
    uint32_t index;

    for (index = 0; index < DNS6_MAX_PENDING_QUERIES; index++)
    {
        if (m_pending_queries[index].message_id == MESSAGE_ID_UNUSED)
        {
            m_pending_queries[index].message_id          = m_message_id_counter++;
            m_pending_queries[index].retries             = 0;
            m_pending_queries[index].p_hostname          = p_hostname;
            m_pending_queries[index].evt_handler         = evt_handler;
            m_pending_queries[index].next_retransmission = 0;

            break;
        }
    }

    return index;
}


/**@brief Function for finding element in pending queue with specific message_id.
 *
 * @param[in] message_id Message identifier to find.
 *
 * @retval Index of element in pending queue or DNS6_MAX_PENDING_QUERIES if nothing found.
 */
static uint32_t query_find(uint32_t message_id)
{
    uint32_t index;

    for (index = 0; index < DNS6_MAX_PENDING_QUERIES; index++)
    {
        if (m_pending_queries[index].message_id == message_id)
        {
            break;
        }
    }

    return index;
}


/**@brief Function for checking if retransmission time of DNS query has been expired.
 *
 * @param[in] index  Index of pending query.
 *
 * @retval True if timer has been expired, False otherwise.
 */
static bool query_timer_is_expired(uint32_t index)
{
    uint32_t               err_code;
    iot_timer_time_in_ms_t wall_clock_value;

    // Get wall clock time.
    err_code = iot_timer_wall_clock_get(&wall_clock_value);

    if (err_code == NRF_SUCCESS)
    {
        if (wall_clock_value >= m_pending_queries[index].next_retransmission)
        {
            return true;
        }
    }

    return false;
}


/**@brief Function for setting retransmissions time of DNS query has been expired.
 *
 * @param[in] index  Index of pending query.
 *
 * @retval None.
 */
static void query_timer_set(uint32_t index)
{
    uint32_t               err_code;
    iot_timer_time_in_ms_t wall_clock_value;

    // Get wall clock time.
    err_code = iot_timer_wall_clock_get(&wall_clock_value);

    if (err_code == NRF_SUCCESS)
    {
        m_pending_queries[index].next_retransmission =
                        wall_clock_value + (DNS6_RETRANSMISSION_INTERVAL * 1000);
    }
}


/**@brief Function for creating compressed hostname from string.
 *
 * @param[inout] p_dest      Pointer to place where hostname will be compressed.
 * @param[in]    p_hostname  Pointer to hostname string.
 *
 * @retval Number of used bytes to compress a hostname.
 */
static uint32_t compress_hostname(uint8_t * p_dest, const uint8_t * p_hostname)
{
    uint32_t  index      = 0;
    uint32_t  label_pos  = 0;
    uint8_t * p_original = p_dest;

    // Elide first byte in destination buffer to put label.
    p_dest++;

    // Parse until string termination is found.
    for (index = 0; p_hostname[index] != 0; index++)
    {
        // Look for string separator.
        if (p_hostname[index] == DNS_LABEL_SEPARATOR)
        {
            // Put number of subsequent string to last label.
            p_original[label_pos] = index - label_pos;

            // Protection to stop compressing after getting incorrect sequence.
            if (index == label_pos)
            {
                return index + 1;
            }

            label_pos = index + 1;
        }
        else
        {
            // Copy character of hostname to destination buffer.
            *p_dest = p_hostname[index];
        }

        p_dest++;
    }

    // Set last label.
    p_original[label_pos] = index - label_pos;

    // Terminate compressed hostname with 0.
    *p_dest = 0;

    // Return length of compressed string.
    return index + 2;
}


/**@brief Function for finding end of compressed hostname.
 *
 * @param[in] p_hostname Pointer to compressed hostname string.
 *
 * @retval Pointer to the end of compressed hostname.
 */
static uint8_t * skip_compressed_hostname(uint8_t * p_hostname)
{
    while (*p_hostname != 0)
    {
        if ((*p_hostname & DNS_LABEL_OFFSET) == DNS_LABEL_OFFSET)
        {
            return p_hostname + 2;
        }
        else
        {
            p_hostname += *p_hostname + 1;
        }
    }

    return p_hostname + 1;
}


/**@brief Function for sending DNS query.
 *
 * @param[in] index  Index of query.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
static uint32_t query_send(uint32_t index)
{
    uint32_t                  length;
    uint32_t                  err_code;
    iot_pbuffer_t           * p_buffer;
    iot_pbuffer_alloc_param_t buffer_param;

    buffer_param.type   = UDP6_PACKET_TYPE;
    buffer_param.flags  = PBUFFER_FLAG_DEFAULT;
    buffer_param.length = DNS_HEADER_SIZE + DNS_QUESTION_FOOTER_SIZE +
                          strlen((const char *)m_pending_queries[index].p_hostname) + 2;

    // Allocate packet buffer.
    err_code = iot_pbuffer_allocate(&buffer_param, &p_buffer);

    if (err_code == NRF_SUCCESS)
    {
        const dns_question_footer_t question_footer =
        {
            .qtype  = HTONS(DNS_QTYPE_AAAA),
            .qclass = HTONS(DNS_QCLASS_IN)
        };

        dns_header_t        * p_dns_header = (dns_header_t *)p_buffer->p_payload;

        // Fill DNS header fields.
        p_dns_header->msg_id  = HTONS(m_pending_queries[index].message_id);
        p_dns_header->flags_1 = DNS_HEADER_FLAG1_QR_QUERY | DNS_HEADER_FLAG1_RD;
        p_dns_header->flags_2 = DNS_HEADER_FLAG2_RCODE_NONE;

        // Send only one question.
        p_dns_header->qdcount = HTONS(1);
        p_dns_header->ancount = HTONS(0);
        p_dns_header->nscount = HTONS(0);
        p_dns_header->arcount = HTONS(0);

        // Start indexing from the end of the DNS header.
        length = DNS_HEADER_SIZE;

        // Compress and put hostname.
        length += compress_hostname(&p_buffer->p_payload[length],
                                    m_pending_queries[index].p_hostname);

        // Add question footer.
        memcpy(&p_buffer->p_payload[length], (uint8_t *)&question_footer, DNS_QUESTION_FOOTER_SIZE);

        length += DNS_QUESTION_FOOTER_SIZE;

        // Update packet buffer's data length.
        p_buffer->length = length;

        // Set retransmission timer.
        query_timer_set(index);

        // Send DNS query using UDP socket.
        err_code = udp6_socket_send(&m_socket, p_buffer);

        if (err_code != NRF_SUCCESS)
        {
            DNS6_ERR("Unable to send query on UDP socket. Reason %08lx.", err_code);

            // Free the allocated buffer as send procedure has failed.
            UNUSED_VARIABLE(iot_pbuffer_free(p_buffer, true));
        }
    }
    else
    {
        DNS6_ERR("No memory to allocate packet buffer.");
    }

    return err_code;
}


/**@brief Function for notifying application of the DNS6 query status.
 *
 * @param[in] index           Index of query.
 * @param[in] process_result  Variable indicates result of DNS query.
 * @param[in] p_addr          Pointer to memory that holds IPv6 addresses.
 * @param[in] addr_count      Number of found addresses.
 *
 * @retval None.
 */
static void app_notify(uint32_t      index,
                       uint32_t      process_result,
                       ipv6_addr_t * p_addr,
                       uint16_t      addr_count)
{
    if (m_pending_queries[index].evt_handler)
    {
        DNS6_MUTEX_UNLOCK();

        // Call handler of user request.
        m_pending_queries[index].evt_handler(process_result,
                                             (const char *)m_pending_queries[index].p_hostname,
                                             p_addr,
                                             addr_count);

        DNS6_MUTEX_LOCK();
    }
}


/**@brief Callback handler to receive data on the UDP port.
 *
 * @param[in]   p_socket         Socket identifier.
 * @param[in]   p_ip_header      IPv6 header containing source and destination addresses.
 * @param[in]   p_udp_header     UDP header identifying local and remote endpoints.
 * @param[in]   process_result   Result of data reception, there could be possible errors like
 *                               invalid checksum etc.
 * @param[in]   p_rx_packet      Packet buffer containing the received data packet.
 *
 * @retval NRF_SUCCESS          Indicates received data was handled successfully, else an an
 *                              error code indicating reason for failure..
 */
static uint32_t server_response(const udp6_socket_t * p_socket,
                                const ipv6_header_t * p_ip_header,
                                const udp6_header_t * p_udp_header,
                                uint32_t              process_result,
                                iot_pbuffer_t       * p_rx_packet)
{
    uint32_t      index;
    uint32_t      rr_index;
    uint32_t      err_code    = NRF_SUCCESS;
    ipv6_addr_t * p_addresses = NULL;
    uint16_t      addr_length = 0;

    DNS6_MUTEX_LOCK();

    DNS6_ENTRY();

    // Check UDP process result and data length.
    if ((process_result != NRF_SUCCESS) || p_rx_packet->length < DNS_HEADER_SIZE)
    {
        DNS6_ERR("Received erroneous response.");
        err_code = (NRF_ERROR_INVALID_DATA | IOT_DNS6_ERR_BASE);
    }
    else
    {
        dns_header_t * p_dns_header = (dns_header_t *)p_rx_packet->p_payload;
        uint8_t      * p_data       = &p_rx_packet->p_payload[DNS_HEADER_SIZE];
        uint16_t       qdcount      = NTOHS(p_dns_header->qdcount);
        uint16_t       ancount      = NTOHS(p_dns_header->ancount);

        // Try to find a proper query for this response, else discard.
        index = query_find(NTOHS(p_dns_header->msg_id));

        if (index != DNS6_MAX_PENDING_QUERIES)
        {
            DNS6_TRC("Received response for hostname %s with %d answers.",
                     m_pending_queries[index].p_hostname, ancount);

            // Check truncation error.
            if (p_dns_header->flags_1 & DNS_HEADER_FLAG1_TC)
            {
                err_code = DNS6_RESPONSE_TRUNCATED;
            }
            else if (!(p_dns_header->flags_1 & DNS_HEADER_FLAG1_QR_RESPONSE))
            {
                err_code = (NRF_ERROR_INVALID_DATA | IOT_DNS6_ERR_BASE);
            }
            // Check response code.
            else if (p_dns_header->flags_2 & DNS_HEADER_FLAG2_RCODE_MASK)
            {
                switch (p_dns_header->flags_2 & DNS_HEADER_FLAG2_RCODE_MASK)
                {
                    case DNS_HEADER_FLAG2_RCODE_FORMAT_ERROR:
                        err_code = DNS6_FORMAT_ERROR;
                        break;

                    case DNS_HEADER_FLAG2_RCODE_SERVER_FAILURE:
                        err_code = DNS6_SERVER_FAILURE;
                        break;

                    case DNS_HEADER_FLAG2_RCODE_NAME_ERROR:
                        err_code = DNS6_HOSTNAME_NOT_FOUND;
                        break;

                    case DNS_HEADER_FLAG2_RCODE_NOT_IMPLEMENTED:
                        err_code = DNS6_NOT_IMPLEMENTED;
                        break;

                    case DNS_HEADER_FLAG2_RCODE_REFUSED:
                        err_code = DNS6_REFUSED_ERROR;
                        break;

                    default:
                        err_code = (NRF_ERROR_INVALID_DATA | IOT_DNS6_ERR_BASE);
                        break;
                }
            }
            else if (ancount == 0)
            {
                // No answer found.
                err_code = DNS6_HOSTNAME_NOT_FOUND;
            }
            else
            {
                dns_rr_body_t rr;

                // Skip questions section.
                for (rr_index = 0; rr_index < qdcount; rr_index++)
                {
                    p_data = skip_compressed_hostname(p_data) + DNS_QUESTION_FOOTER_SIZE;
                }

                // Addresses are moved to beginning of the packet to ensure alignment is correct.
                p_addresses = (ipv6_addr_t *)p_rx_packet->p_payload;

                // Parse responses section.
                for (rr_index = 0; rr_index < ancount; rr_index++)
                {
                    p_data = skip_compressed_hostname(p_data);

                    // Fill resource record structure to fit alignment.
                    memcpy((uint8_t *)&rr, p_data, DNS_RR_BODY_SIZE);

                    if (NTOHS(rr.rtype) == DNS_QTYPE_AAAA && NTOHS(rr.rclass) == DNS_QCLASS_IN)
                    {
                        if (NTOHS(rr.rdlength) == IPV6_ADDR_SIZE)
                        {
                            DNS6_TRC("Found AAAA record with IPv6 address:");
                            DNS6_DUMP(p_data + DNS_RR_BODY_SIZE, IPV6_ADDR_SIZE);

                            // Move all addresses next to each other.
                            memmove(p_addresses[addr_length].u8,
                                    p_data + DNS_RR_BODY_SIZE,
                                    IPV6_ADDR_SIZE);

                            addr_length++;
                        }
                    }

                    p_data += DNS_RR_BODY_SIZE + NTOHS(rr.rdlength);
                }

                if (addr_length == 0)
                {
                    DNS6_ERR("No IPv6 addresses was found.");

                    err_code = DNS6_HOSTNAME_NOT_FOUND;
                }
            }

            // Notify application.
            app_notify(index, err_code, p_addresses, addr_length);

            // Initialize query entry.
            query_init(index);
        }
        else
        {
            DNS6_ERR("Response with unknown message id.");
            err_code = (NRF_ERROR_NOT_FOUND | IOT_DNS6_ERR_BASE);
        }
    }

    DNS6_EXIT();

    DNS6_MUTEX_UNLOCK();

    return err_code;
}


uint32_t dns6_init(const dns6_init_t * p_dns_init)
{
    NULL_PARAM_CHECK(p_dns_init);

    uint32_t index;
    uint32_t err_code;

    DNS6_ENTRY();

    SDK_MUTEX_INIT(m_dns6_mutex);

    DNS6_MUTEX_LOCK();

    for (index = 0; index < DNS6_MAX_PENDING_QUERIES; index++)
    {
        query_init(index);
    }

    // Request new socket creation.
    err_code = udp6_socket_allocate(&m_socket);

    if (err_code == NRF_SUCCESS)
    {
        // Bind the socket to the local port.
        err_code = udp6_socket_bind(&m_socket, IPV6_ADDR_ANY, p_dns_init->local_src_port);

        if (err_code == NRF_SUCCESS)
        {
            // Connect to DNS server.
            err_code = udp6_socket_connect(&m_socket,
                                           &p_dns_init->dns_server.addr,
                                           p_dns_init->dns_server.port);

            if (err_code == NRF_SUCCESS)
            {
                // Register data receive callback.
                err_code = udp6_socket_recv(&m_socket, server_response);
            }
        }

        if (err_code == NRF_SUCCESS)
        {
            DNS6_TRC("Module initialization is complete.");

            // Set initialization state flag if all procedures succeeded.
            m_initialization_state = true;
            m_message_id_counter   = 0x0001;
        }
        else
        {
            DNS6_ERR("UDP socket initialization failed. Reason %08lx.", err_code);

            // Not all procedures succeeded with allocated socket, hence free it.
            UNUSED_VARIABLE(udp6_socket_free(&m_socket));
        }
    }

    DNS6_EXIT();

    DNS6_MUTEX_UNLOCK();

    return err_code;
}


uint32_t dns6_uninit(void)
{
    VERIFY_MODULE_IS_INITIALIZED();

    uint32_t index;

    DNS6_ENTRY();

    DNS6_MUTEX_LOCK();

    for (index = 0; index < DNS6_MAX_PENDING_QUERIES; index++)
    {
        query_init(index);
    }

    // Free UDP socket.
    UNUSED_VARIABLE(udp6_socket_free(&m_socket));

    // Clear initialization state flag.
    m_initialization_state = false;

    DNS6_EXIT();

    DNS6_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t dns6_query(const char * p_hostname, dns6_evt_handler_t evt_handler)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(evt_handler);
    NULL_PARAM_CHECK(p_hostname);
    EMPTY_PARAM_CHECK(p_hostname);

    uint32_t  index;
    uint32_t  err_code;
    uint32_t  hostname_length;
    uint8_t * p_hostname_buff = NULL;

    DNS6_ENTRY();

    DNS6_MUTEX_LOCK();

    // Calculate hostname length.
    hostname_length = strlen(p_hostname) + 1;

    // Allocate memory to make copy of hostname string.
    err_code = nrf_mem_reserve(&p_hostname_buff, &hostname_length);

    if (err_code == NRF_SUCCESS)
    {
        // Copy hostname to cache buffer.
        strcpy((char *)p_hostname_buff, p_hostname);

        // Add query to pending queue.
        index = query_add(p_hostname_buff, evt_handler);

        if (index != DNS6_MAX_PENDING_QUERIES)
        {
            // Create and send DNS Query.
            err_code = query_send(index);

            if (err_code != NRF_SUCCESS)
            {
                // Remove query from pending queue immediately.
                query_init(index);
            }
        }
        else
        {
            DNS6_ERR("No place in pending queue.");

            // No place in pending queue.
            err_code = (NRF_ERROR_NO_MEM | IOT_DNS6_ERR_BASE);
        }

        // Not all procedures succeeded with sending query, hence free buffer for hostname.
        if (err_code != NRF_SUCCESS)
        {
            UNUSED_VARIABLE(nrf_free(p_hostname_buff));
        }
    }
    else
    {
        DNS6_ERR("No memory to allocate buffer for hostname.");
    }

    DNS6_EXIT();

    DNS6_MUTEX_UNLOCK();

    return err_code;
}


void dns6_timeout_process(iot_timer_time_in_ms_t wall_clock_value)
{
    uint32_t index;
    uint32_t err_code;

    UNUSED_PARAMETER(wall_clock_value);

    DNS6_ENTRY();

    DNS6_MUTEX_LOCK();

    for (index = 0; index < DNS6_MAX_PENDING_QUERIES; index++)
    {
        if (m_pending_queries[index].message_id != MESSAGE_ID_UNUSED)
        {
            if (query_timer_is_expired(index))
            {
                err_code = NRF_SUCCESS;

                if (m_pending_queries[index].retries < DNS6_MAX_RETRANSMISSION_COUNT)
                {
                    DNS6_TRC("Query retransmission [%d] for hostname %s.",
                             m_pending_queries[index].retries, m_pending_queries[index].p_hostname);

                    // Increase retransmission number.
                    m_pending_queries[index].retries++;

                    // Send query again.
                    err_code = query_send(index);
                }
                else
                {
                    DNS6_ERR("DNS server did not response on query for hostname %s.",
                             m_pending_queries[index].p_hostname);

                    // No response from server.
                    err_code = DNS6_SERVER_UNREACHABLE;
                }

                if (err_code != NRF_SUCCESS)
                {
                    // Inform application that timeout occurs.
                    app_notify(index, err_code, NULL, 0);

                    // Remove query from pending queue.
                    query_init(index);
                }
            }
            break;
        }
    }

    DNS6_EXIT();

    DNS6_MUTEX_UNLOCK();
}
