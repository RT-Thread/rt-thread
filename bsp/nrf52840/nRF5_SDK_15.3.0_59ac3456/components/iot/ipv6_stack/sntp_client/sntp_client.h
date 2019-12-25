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
 * @defgroup sntp_client SNTP Client
 * @{
 * @ingroup iot_sdk_stack
 * @brief Simple Network Time Protocol (SNTP) client for obtaining and storing local unix time.
 *
 * @details Concurrent queries are not supported. Exponential-backoff algorithm for
 *          retransmissions is not implemented, retransmissions are triggered at regular intervals.
 *
 */

#ifndef SNTP_CLIENT_H__
#define SNTP_CLIENT_H__

#include <stdint.h>
/*lint -save -e43 -e1504 */
#include <time.h>
/*lint -restore */
#include "sdk_config.h"
#include "nrf_error.h"
#include "ipv6_api.h"
#include "iot_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KISS_CODE_LEN 4    /**< Kiss-o'-Death packets convey kiss codes as 4 character long @c ASCII messages. */

/**@brief SNTP client callback parameter.
 */
typedef union
{
    time_t   time_from_server;    /**< Unix time if a proper proper response is received from an NTP server. */
    uint32_t callback_data;       /**< Data pertaining to the event triggering the callback. The kiss code from any Kiss-o'-Death packets. */
} sntp_client_cb_param_t;

/**@brief SNTP client callback type.
 *
 * @details Execution of the callback function marks the completion of an SNTP query.
 *          The callback will be executed if a response is received from the NTP server,
 *          or if the server remains unresponsive even after @ref SNTP_MAX_RETRANSMISSION_COUNT
 *          is reached.
 *
 * @param[in] p_ntp_srv_addr      Pointer to the source IPv6 address of the NTP response, or to
 *                                the IPv6 address of the NTP server targeted by the unsuccessful
 *                                query.
 * @param[in] ntp_srv_udp_port    The source UDP port of the NTP response, or the UDP port of
 *                                the NTP server targeted by the unsuccessful query.
 * @param[in] process_result      The value of this parameter reveals whether a response from the
 *                                NTP server or a timeout triggered the callback.
 * @param[in] callback_parameter  This parameter holds the unix time from the server after a
 *                                successful query, or the kiss code if a Kiss-o'-Death packet
 *                                was received. Otherwise NULL.
 *
 * @retval None.
 *
 */
typedef void (*sntp_evt_handler_t)(const ipv6_addr_t      * p_ntp_srv_addr,      \
                                   uint16_t                 ntp_srv_udp_port,    \
                                   uint32_t                 process_result,      \
                                   sntp_client_cb_param_t   callback_parameter);

/**@brief SNTP client initialization structure.
 *
 * @note  @ref app_evt_handler can be set to zero to disable callbacks.
 */
typedef struct
{
    sntp_evt_handler_t   app_evt_handler;    /**< Pointer to the event handler callback function. Triggered by a response from an NTP server to an SNTP query, or a retransmission timeout after @ref SNTP_MAX_RETRANSMISSION_COUNT is reached. */
    uint16_t             local_udp_port;     /**< Local port used by the UDP socket allocated for the SNTP client module. Cannot be NULL. */
} sntp_client_init_param_t;

/**
 * @brief Function for initializing the SNTP client module.
 *
 * @details The SNTP client uses UDP as transport layer, therefore, one UDP socket is allocated
 *          for the module and is used to transmit any future queries.
 *
 * @param[in] p_sntp_client_init_param Pointer to the initialization structure for the SNTP client.
 *                       Should not be NULL.
 *
 * @note The event handler in the initialization structure can be set to NULL to disable callbacks
 *       from the module.
 *
 * @retval NRF_SUCCESS      Module successfully initialized.
 * @retval NRF_ERROR_NULL   If @b p_sntp_client_init_param is NULL, or if it points to a local UDP
 *                          port that is NULL.
 *
 */
uint32_t sntp_client_init(const sntp_client_init_param_t * p_sntp_client_init_param);

/**
 * @brief Function for uninitializing the SNTP client module.
 *
 * @details This procedure frees up the UDP socket previously allocated to the module.
 *          Any pending retransmissions are cleared and no more callbacks will be executed.
 *
 * @retval NRF_SUCCESS                      Module successfully uninitialized.
 * @retval SDK_ERR_MODULE_NOT_INITIALIZED   The module was not initialized.
 *
 */
uint32_t sntp_client_uninitialize(void);

/**@brief Function for sending an SNTP query to the specified NTP server.
 *
 * @details The local unix time is set to zero (1-Jan-70) when the module is initialized. It can
 *          be updated by using the @ref sntp_client_server_query procedure. The accuracy of the
 *          output is depending on the wall clock of the IoT Timer module.
 *
 * @param[in] p_ntp_server_address  Pointer to the IPv6 address of the NTP server. This memory must
 *                                  be resident until the query is completed.
 * @param[in] ntp_server_udp_port   Destination port of the NTP server. The UDP port number
 *                                  assigned by the IANA to NTP is 123.
 * @param[in] sync_local_time       A boolean value telling the module whether to synchronize its
 *                                  local clock with any response received from the NTP server.
 *
 * @retval NRF_SUCCESS                      SNTP query successfully sent.
 * @retval SDK_ERR_MODULE_NOT_INITIALIZED   The module was not initialized.
 * @retval NRF_ERROR_NULL                   If @b p_ntp_server_address or @b ntp_server_udp_port
 *                                          is a NULL pointer.
 *
 */
uint32_t sntp_client_server_query(ipv6_addr_t * p_ntp_server_address, \
                                  uint16_t      ntp_server_udp_port,  \
                                  bool          sync_local_time);

/**@brief Function for getting the local unix time from the module.
 *
 * @details The local unix time is set to zero (1-Jan-70) when the module is initialized. It can
 *          be updated by using @ref sntp_client_server_query procedure. The accuracy of the
 *          output is depending on the wall clock of the IoT Timer module.
 *
 * @param[out] p_current_time  Local unix time.
 *
 * @retval NRF_SUCCESS                    Getting locally stored unix time successful.
 * @retval SDK_ERR_MODULE_NOT_INITIALIZED  The module was not initialized.
 * @retval NRF_ERROR_NULL                 If @b p_current_time is a NULL pointer.
 *
 */
uint32_t sntp_client_local_time_get(time_t * p_current_time);

/**@brief Function for performing retransmissions of SNTP queries.
 *
 * @details The SNTP client module implements the retransmission mechanism by invoking this
 *          function periodically. This procedure is to be added to the IoT Timer client list
 *          and has to be called repeatedly with a minimum period of SNTP_RETRANSMISSION_INTERVAL.
 *
 * @param[in] wall_clock_value  The value of the wall clock that triggered the callback.
 *
 * @retval None.
 *
 */
void sntp_client_timeout_process(iot_timer_time_in_ms_t wall_clock_value);

#ifdef __cplusplus
}
#endif

#endif // SNTP_CLIENT_H__

/**@} */
