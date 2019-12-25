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
#include "udp_api.h"
#include "ipv6_api.h"
#include "app_error.h"
#include "sdk_common.h"
#include "sntp_client.h"

#if SNTP_CLIENT_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME sntp

#define NRF_LOG_LEVEL       SNTP_CLIENT_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  SNTP_CLIENT_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR SNTP_CLIENT_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define SNTP_TRC     NRF_LOG_DEBUG                                                                  /**< Used for getting trace of execution in the module. */
#define SNTP_ERR     NRF_LOG_ERROR                                                                  /**< Used for logging errors in the module. */
#define SNTP_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                          /**< Used for dumping octet information to get details of bond information etc. */

#define SNTP_ENTRY() SNTP_TRC(">> %s", __func__)
#define SNTP_EXIT()  SNTP_TRC("<< %s", __func__)

#else // SNTP_CLIENT_CONFIG_LOG_ENABLED

#define SNTP_TRC(...)                                                                               /**< Disables traces. */
#define SNTP_DUMP(...)                                                                              /**< Disables dumping of octet streams. */
#define SNTP_ERR(...)                                                                               /**< Disables error logs. */

#define SNTP_ENTRY(...)
#define SNTP_EXIT(...)

#endif // SNTP_CLIENT_CONFIG_LOG_ENABLED

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          SNTP_CLIENT_DISABLE_API_PARAM_CHECK should be defined to disable these checks.
 *
 * @{
 */
#if (SNTP_CLIENT_DISABLE_API_PARAM_CHECK == 0)

/**
 * @brief Verify NULL parameters are not passed to an API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_NTP_ERR_BASE);                                            \
        }

/**
 * @brief Verify that not zero is passed to an API by application.
 */
#define ZERO_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == 0x00)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_NTP_ERR_BASE);                                            \
        }

/**
 * @brief Macro to check if module is initialized.
 */
#define VERIFY_MODULE_IS_INITIALIZED()                                                             \
        if (m_sntp_client_state == SNTP_CLIENT_STATE_UNINITIALIZED)                                \
        {                                                                                          \
            return (SDK_ERR_MODULE_NOT_INITIALIZED | IOT_NTP_ERR_BASE);                            \
        }

#else // SNTP_CLIENT_DISABLE_API_PARAM_CHECK

#define NULL_PARAM_CHECK(PARAM)
#define ZERO_PARAM_CHECK(PARAM)
#define VERIFY_MODULE_IS_INITIALIZED()

#endif //SNTP_CLIENT_DISABLE_API_PARAM_CHECK
/** @} */

/**
 * @defgroup ble_sntp_c_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define SNTP_C_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_sntp_c_mutex)              /**< Lock module using mutex */
#define SNTP_C_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_sntp_c_mutex)            /**< Unlock module using mutex */
/** @} */

#define TIME_AT_1970          2208988800UL  // Number of seconds between 1st Jan 1900 and 1st Jan 1970, for NTP<->Unix time conversion.
#define PROTOCOL_MODE_SERVER             4

/**@brief NTP Header Format. */
typedef struct
{
    uint8_t  flags;                     /**< Please see RFC 4330. */
    uint8_t  stratum;                   /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint8_t  poll_interval;             /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint8_t  precision;                 /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint32_t root_delay;                /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint32_t root_dispersion;           /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint32_t reference_id;              /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint32_t reference_timestamp[2];    /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint32_t originate_timestamp[2];    /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint32_t receive_timestamp[2];      /**< Please see RFC 4330. This field is significant only in SNTP server messages. */
    uint32_t transmit_timestamp[2];     /**< Please see RFC 4330. */
} ntp_header_t;

typedef enum
{
    SNTP_CLIENT_STATE_UNINITIALIZED = 1,
    SNTP_CLIENT_STATE_IDLE,
    SNTP_CLIENT_STATE_BUSY
} sntp_client_state_t;

typedef struct
{
    time_t                   unix_time;
    iot_timer_time_in_ms_t   wall_clock_value;
} local_timestamp_t;

SDK_MUTEX_DEFINE(m_sntp_c_mutex)                                                                  /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */
static sntp_client_state_t      m_sntp_client_state = SNTP_CLIENT_STATE_UNINITIALIZED;
static ipv6_addr_t            * m_p_ntp_server_address;
static uint16_t                 m_ntp_server_port;
static bool                     m_do_sync_local_time;
static iot_timer_time_in_ms_t   m_time_of_last_transmission;
static uint8_t                  m_retransmission_count;
static sntp_evt_handler_t       m_app_evt_handler;
static udp6_socket_t            m_udp_socket;
static local_timestamp_t        m_local_time;

/**@brief Function for checking if a received NTP packet is valid.
 *
 * @param[in] p_ntp_response Pointer to the NTP packet header.
 *
 */
static bool is_response_valid(ntp_header_t * p_ntp_response)
{
    if (((p_ntp_response->transmit_timestamp[0] == 0x00) &&          \
             (p_ntp_response->transmit_timestamp[1] == 0x00))     || \
        ((p_ntp_response->flags & 0x38) == 0x00)                  || \
        ((p_ntp_response->flags & 0x07) != PROTOCOL_MODE_SERVER))
    {
        return false;
    }

    return true;
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
static uint32_t port_data_callback(const udp6_socket_t * p_socket,
                                   const ipv6_header_t * p_ip_header,
                                   const udp6_header_t * p_udp_header,
                                   uint32_t              process_result,
                                   iot_pbuffer_t       * p_rx_packet)
{
    SNTP_C_MUTEX_LOCK();

    SNTP_ENTRY();

    uint32_t err_code = NRF_SUCCESS;
    ntp_header_t * p_ntp_header = (ntp_header_t *)p_rx_packet->p_payload;

    if (m_sntp_client_state != SNTP_CLIENT_STATE_BUSY)
    {
        SNTP_ERR("Unexpected NTP response received.");

        SNTP_C_MUTEX_UNLOCK();

        SNTP_EXIT();
        return (NRF_ERROR_INVALID_STATE | IOT_NTP_ERR_BASE);
    }
    else
    {
        // Check UDP process result and data length.
        if ((process_result != NRF_SUCCESS) || p_rx_packet->length < sizeof(ntp_header_t))
        {
            SNTP_ERR("Received erroneous NTP response.");

            m_sntp_client_state    = SNTP_CLIENT_STATE_IDLE;
            m_retransmission_count = 0;
            m_do_sync_local_time   = false;
            err_code               = (NRF_ERROR_INVALID_DATA | IOT_NTP_ERR_BASE);

            SNTP_C_MUTEX_UNLOCK();

            if (m_app_evt_handler != NULL)
            {
                m_app_evt_handler(&(p_ip_header->srcaddr), p_udp_header->srcport, err_code, \
                                  (sntp_client_cb_param_t){ .callback_data = 0x00 });
            }

            SNTP_EXIT();
            return err_code;
        }
        else
        {
            if (!is_response_valid(p_ntp_header))
            {
                SNTP_ERR("Received bad NTP response.");

                m_sntp_client_state    = SNTP_CLIENT_STATE_IDLE;
                m_retransmission_count = 0;
                m_do_sync_local_time   = false;
                err_code               = NTP_SERVER_BAD_RESPONSE;

                SNTP_C_MUTEX_UNLOCK();

                if (m_app_evt_handler != NULL)
                {
                    m_app_evt_handler(&(p_ip_header->srcaddr), \
                                      p_udp_header->srcport,   \
                                      err_code,                \
                                      (sntp_client_cb_param_t){ .callback_data = 0x00 });
                }

                SNTP_EXIT();
                return err_code;
            }
            else
            {
                // Check if Kiss-o'-Death packet.
                if (p_ntp_header->stratum == 0x00)
                {
                    SNTP_TRC("Received Kiss-o'-Death packet.");

                    m_sntp_client_state    = SNTP_CLIENT_STATE_IDLE;
                    m_retransmission_count = 0;
                    m_do_sync_local_time   = false;

                    SNTP_C_MUTEX_UNLOCK();

                    if (m_app_evt_handler != NULL)
                    {
                        m_app_evt_handler(&(p_ip_header->srcaddr), p_udp_header->srcport, \
                                          NTP_SERVER_KOD_PACKET_RECEIVED,                 \
                                          (sntp_client_cb_param_t){ .callback_data        \
                                                                    = p_ntp_header->reference_id });
                    }

                    SNTP_EXIT();
                    return NRF_SUCCESS;
                }
                else
                {
                    // Process decent NTP response.
                    time_t time_from_response = (HTONL(p_ntp_header->transmit_timestamp[0])) - \
                                                                                     TIME_AT_1970;

                    if (m_do_sync_local_time)
                    {
                        iot_timer_time_in_ms_t wall_clock_value;
                        UNUSED_VARIABLE(iot_timer_wall_clock_get(&wall_clock_value));
                        m_local_time.unix_time        = time_from_response;
                        m_local_time.wall_clock_value = wall_clock_value;
                        m_do_sync_local_time = false;
                    }

                    m_sntp_client_state    = SNTP_CLIENT_STATE_IDLE;
                    m_retransmission_count = 0;

                    SNTP_C_MUTEX_UNLOCK();

                    if (m_app_evt_handler != NULL)
                    {
                        m_app_evt_handler(&(p_ip_header->srcaddr),                      \
                                          p_udp_header->srcport,                        \
                                          NRF_SUCCESS,                                  \
                                          (sntp_client_cb_param_t){ .time_from_server = \
                                                                        time_from_response });
                    }

                    SNTP_EXIT();
                    return NRF_SUCCESS;
                }
            }
        }
    }
}


uint32_t sntp_client_init(const sntp_client_init_param_t * p_sntp_client_init_param)
{
    NULL_PARAM_CHECK(p_sntp_client_init_param);
    ZERO_PARAM_CHECK(p_sntp_client_init_param->local_udp_port);

    SNTP_ENTRY();

    SDK_MUTEX_INIT(m_sntp_c_mutex);
    SNTP_C_MUTEX_LOCK();

    uint32_t err_code;

    memset(&m_local_time, 0x00, sizeof(m_local_time));
    m_app_evt_handler = p_sntp_client_init_param->app_evt_handler;

    //Request new socket creation.
    err_code = udp6_socket_allocate(&m_udp_socket);

    if (err_code == NRF_SUCCESS)
    {
        // Bind the socket to the local port.
        err_code = udp6_socket_bind(&m_udp_socket,  \
                                    IPV6_ADDR_ANY,  \
                                    p_sntp_client_init_param->local_udp_port);
        if (err_code == NRF_SUCCESS)
        {
            //Register data receive callback.
            err_code = udp6_socket_recv(&m_udp_socket, port_data_callback);
        }
        if (err_code != NRF_SUCCESS)
        {
            //Not all procedures succeeded with allocated socket, hence free it.
            UNUSED_VARIABLE(udp6_socket_free(&m_udp_socket));
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        m_sntp_client_state = SNTP_CLIENT_STATE_IDLE;
    }

    SNTP_EXIT();

    SNTP_C_MUTEX_UNLOCK();

    return err_code;
}


static uint32_t local_time_get(time_t * p_local_time)
{
    uint32_t err_code = NRF_SUCCESS;
    iot_timer_time_in_ms_t delta_ms;
    err_code = iot_timer_wall_clock_delta_get(&m_local_time.wall_clock_value, &delta_ms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    *p_local_time = m_local_time.unix_time + (delta_ms / 1000);

    return err_code;
}


uint32_t sntp_client_local_time_get(time_t * p_current_time)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_current_time);

    uint32_t err_code = NRF_SUCCESS;

    SNTP_ENTRY();

    SNTP_C_MUTEX_LOCK();

    err_code = local_time_get(p_current_time);

    SNTP_EXIT();

    SNTP_C_MUTEX_UNLOCK();

    return err_code;
}


/**@brief Function for sending SNTP query.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, otherwise an error code indicating reason
 *                     for failure.
 */
static uint32_t sntp_query_send()
{
    uint32_t                    err_code;
    iot_pbuffer_t             * p_buffer;
    iot_pbuffer_alloc_param_t   buffer_param;
    time_t                      current_local_time;

    err_code = local_time_get(&current_local_time);
    if (err_code != NRF_SUCCESS)
    {
        SNTP_ERR("An error occurred while getting local time value!");
        return err_code;
    }

    buffer_param.type   = UDP6_PACKET_TYPE;
    buffer_param.flags  = PBUFFER_FLAG_DEFAULT;
    buffer_param.length = sizeof(ntp_header_t);

    UNUSED_VARIABLE(iot_timer_wall_clock_get(&m_time_of_last_transmission));

    // Allocate packet buffer.
    err_code = iot_pbuffer_allocate(&buffer_param, &p_buffer);

    if (err_code == NRF_SUCCESS)
    {
        ntp_header_t * p_ntp_header = (ntp_header_t *)p_buffer->p_payload;
        memset(p_ntp_header, 0x00, sizeof(ntp_header_t));

        // Fill NTP header fields.
        p_ntp_header->flags                 = 0x1B; // LI = 0; VN = 3; Mode = 3
        p_ntp_header->transmit_timestamp[0] = HTONL((uint32_t)(current_local_time  + TIME_AT_1970));

        // Send NTP query using UDP socket.
        err_code = udp6_socket_sendto(&m_udp_socket,          \
                                      m_p_ntp_server_address, \
                                      m_ntp_server_port,      \
                                      p_buffer);
        if (err_code != NRF_SUCCESS)
        {
            SNTP_ERR("Unable to send query on UDP socket. Reason %08lx.", err_code);

            // Free the allocated buffer as send procedure has failed.
            UNUSED_VARIABLE(iot_pbuffer_free(p_buffer, true));
        }
    }
    else
    {
        SNTP_ERR("No memory to allocate packet buffer.");
    }

    return err_code;
}


uint32_t sntp_client_server_query(ipv6_addr_t * p_ntp_server_address, \
                                  uint16_t      ntp_server_udp_port,  \
                                  bool          sync_local_time)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_ntp_server_address);
    ZERO_PARAM_CHECK(ntp_server_udp_port);

    uint32_t err_code = NRF_SUCCESS;
    SNTP_ENTRY();

    SNTP_C_MUTEX_LOCK();

    if (m_sntp_client_state != SNTP_CLIENT_STATE_IDLE)
    {
        SNTP_EXIT();
        return (NRF_ERROR_BUSY | IOT_NTP_ERR_BASE);
    }

    m_p_ntp_server_address = p_ntp_server_address;
    m_ntp_server_port      = ntp_server_udp_port;
    m_do_sync_local_time   = sync_local_time;

    err_code = sntp_query_send();
    if (err_code == NRF_SUCCESS)
    {
        m_sntp_client_state = SNTP_CLIENT_STATE_BUSY;
    }

    SNTP_EXIT();

    SNTP_C_MUTEX_UNLOCK();

    return err_code;
}


/**@brief Function for determining whether it is time to retransmit a query.
 *
 */
static bool is_it_time_to_retransmit()
{
    uint32_t err_code = NRF_SUCCESS;
    iot_timer_time_in_ms_t delta_ms = 0;

    err_code = iot_timer_wall_clock_delta_get(&m_time_of_last_transmission, &delta_ms);
    if (err_code != NRF_SUCCESS)
    {
        return true;
    }
    if (delta_ms >= (SNTP_RETRANSMISSION_INTERVAL * 1000))
    {
        return true;
    }
    else
    {
        return false;
    }
}


void sntp_client_timeout_process(iot_timer_time_in_ms_t wall_clock_value)
{
    SNTP_C_MUTEX_LOCK();

    UNUSED_PARAMETER(wall_clock_value);

    if (m_sntp_client_state == SNTP_CLIENT_STATE_BUSY)
    {
        if (is_it_time_to_retransmit())
        {
            m_retransmission_count++;
            if (m_retransmission_count > SNTP_MAX_RETRANSMISSION_COUNT)
            {
                m_sntp_client_state    = SNTP_CLIENT_STATE_IDLE;
                m_retransmission_count = 0;
                m_do_sync_local_time   = false;

                SNTP_C_MUTEX_UNLOCK();

                if (m_app_evt_handler != NULL)
                {
                    m_app_evt_handler(m_p_ntp_server_address,  \
                                      m_ntp_server_port,       \
                                      NTP_SERVER_UNREACHABLE,  \
                                      (sntp_client_cb_param_t){ .callback_data = 0x00 });
                }

                SNTP_TRC("NTP server did not respond to query.");
                return;
            }
            else
            {
                SNTP_TRC("Query retransmission [%d].", m_retransmission_count);
                UNUSED_VARIABLE(sntp_query_send());
            }
        }
    }

    SNTP_C_MUTEX_UNLOCK();
    return;
}


uint32_t sntp_client_uninitialize()
{
    VERIFY_MODULE_IS_INITIALIZED();

    SNTP_ENTRY();

    SNTP_C_MUTEX_LOCK();

    // Free UDP socket.
    UNUSED_VARIABLE(udp6_socket_free(&m_udp_socket));

    m_sntp_client_state    = SNTP_CLIENT_STATE_UNINITIALIZED;
    m_retransmission_count = 0;
    m_do_sync_local_time   = false;

    SNTP_EXIT();

    SNTP_C_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}
