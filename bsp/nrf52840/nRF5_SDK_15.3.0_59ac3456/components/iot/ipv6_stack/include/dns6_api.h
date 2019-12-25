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
/** @file dns6_api.h
 *
 * @defgroup iot_dns6 DNS Application Interface for Nordic's IPv6 stack
 * @ingroup iot_sdk_stack
 * @{
 * @brief Domain Name System module provides implementation of DNS6 service.
 *
 */

#ifndef DNS6_H__
#define DNS6_H__

#include "sdk_config.h"
#include "sdk_common.h"
#include "ipv6_api.h"
#include "iot_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief DNS Server parameter. */
typedef struct
{
    ipv6_addr_t addr;                          /**< The IPv6 address of the DNS Server. */
    uint16_t    port;                          /**< The default UDP port of the DNS Server. */
} dns6_server_param_t;


/**@brief Initialization parameters type. */
typedef struct
{
    uint16_t            local_src_port;        /**< The local UDP port for reception the DNS responses. */
    dns6_server_param_t dns_server;            /**< Parameters of the DNS Server. */
} dns6_init_t;


/**
 * @brief   DNS event receive callback.
 *
 * @details API used to notify the application of DNS Response on specific hostname or of an error
 *          during resolving process. The process_result parameter indicates whether the DNS module
 *          was successfully processed. If the received DNS Response is malformed in a way that
 *          allow to assign response with specific callback (e.g. timeout occurs or hostname is not
 *          found), information about error is still notified to the application. The application
 *          should check process_result and number of IPv6 address before reading them.
 *
 * @param[in]  process_result Notifies the application if the DNS module was processed successfully
 *                            or if an error occurred, for example DNS server is unreachable.
 * @param[in]  p_hostname     Identifies hostname (URL string) that was requested to bee resolved,
 *                            e.g. "example.com".
 * @param[in]  p_addr         Pointer to the IPv6 addresses being resolved for given hostname. In
 *                            case addr_count variable is 0, p_addr gets NULL value and should not
 *                            be used.
 * @param[in]  addr_count     Number of IPv6 addresses being successfully resolved.
 *
 * @retval  None.
 */
typedef void (* dns6_evt_handler_t) (uint32_t      process_result,
                                     const char  * p_hostname,
                                     ipv6_addr_t * p_addr,
                                     uint16_t      addr_count);

/**
 * @brief Function for initializing DNS6 module.
 *
 * @param[in] p_dns_init Initialization structure for DNS client. Should not be NULL.
 *
 * @note DNS protocol module uses UDP transport layer, therefore one UDP socket is allocated
 *       inside function and uses for further communication.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t dns6_init(const dns6_init_t * p_dns_init);


/**
 * @brief Function for uninitializing DNS6 module.
 *
 * @note Apart of DNS specific functionality, function frees previously allocated UDP socket.
 *       Function removes any pending queries from the sending queue, so registered user
 *       callbacks will not be executed.
 *
 * @retval NRF_SUCCESS on successful execution of procedure, else an error code indicating reason
 *                     for failure.
 */
uint32_t dns6_uninit(void);


/**
 * @brief  Function for querying given URL string to DNS server, in order to get IPv6 address of
 *         given hostname.
 *
 * @param[in] p_hostname  Identifies hostname (URL string) to be find, e.g. "example.com". Should
 *                        not be NULL.
 * @param[in] evt_handler Callback that is called once response is received, timeout occurred or
 *                        internal error was detected. Should not be NULL.
 *
 * @note Function sends DNS Query to DNS Server to obtain all AAAA records (with IPv6 address)
 *       assigned to given hostname. In case DNS Server replies with more that one AAAA records
 *       DNS module call user defined evt_handler with addr_count indicates number of addresses.
 *
 * @retval NRF_SUCCESS on successful execution of procedure.
 * @retval IOT_DNS6_ERR_BASE | NRF_ERROR_NO_MEM if there is no place in pending queries' queue.
 * @retval IOT_PBUFFER_ERR_BASE | NRF_ERROR_NO_MEM if there is no memory for hostname allocation.
 * @retval NRF_ERROR_MEMORY_MANAGER_ERR_BASE | NRF_ERROR_NO_MEM if there is no memory for packet allocation.
 * @retval UDP_INTERFACE_NOT_READY if interface is not ready for sending packets e.g. interface is
 *                                 down.
 * @retval Other errors indicates reason of failure.
 */
uint32_t dns6_query(const char * p_hostname, dns6_evt_handler_t evt_handler);


/**@brief Function for performing retransmissions of DNS queries.
 *
 * @note DNS module implements the retransmission mechanism by invoking this function periodically.
 *       So that method has to be added to IoT Timer client list and has to be called with minimum of
 *       DNS6_RETRANSMISSION_INTERVAL resolution.
 *
 * @param[in] wall_clock_value  The value of the wall clock that triggered the callback.
 *
 * @retval None.
 */
void dns6_timeout_process(iot_timer_time_in_ms_t wall_clock_value);


#ifdef __cplusplus
}
#endif

#endif //DNS6_H__

/**@} */
