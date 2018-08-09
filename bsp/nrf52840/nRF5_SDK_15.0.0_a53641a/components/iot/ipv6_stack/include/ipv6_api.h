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
/** @file ipv6_api.h
 *
 * @defgroup iot_ipv6 IPv6 Core Application Interface for Nordic's IPv6 stack
 * @ingroup iot_sdk_stack
 * @{
 * @brief Nordic's IPv6 stack. Currently, only a Host role is supported.
 *
 * @details Nordic's IPv6 stack provides minimal implementations of ICMP, UDP for a Host, and
 *          IPv6 Neighbor Discovery for Host.
 *          Router, neighbor, and prefix cache are not maintained across BLE link disconnections or
 *          power cycles.
 */

#ifndef IPV6_API_H_
#define IPV6_API_H_

#include <stdint.h>
#include "sdk_config.h"
#include "iot_common.h"
#include "iot_pbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Asynchronous event identifiers type. */
typedef enum
{
    IPV6_EVT_INTERFACE_ADD,                                                                         /**< Notification of a new IPv6 interface added. */
    IPV6_EVT_INTERFACE_DELETE,                                                                      /**< Notification of IPv6 interface deleted. */
    IPV6_EVT_INTERFACE_RX_DATA                                                                     /**< Notification of IPv6 data, depending on configuration. For example, IPV6_ENABLE_USNUPORTED_PROTOCOLS_TO_APPLICATION. */
} ipv6_event_id_t;

/**@brief IPv6 address configuration. */
typedef struct
{
    ipv6_addr_t       addr;
    ipv6_addr_state_t state;
} ipv6_addr_conf_t;

/**@brief Event parameters associated with the IPV6_EVT_INTERFACE_RX_DATA event. */
typedef struct
{
    ipv6_header_t * p_ip_header;                                                                    /**< IPv6 header of the packet. */
    iot_pbuffer_t * p_rx_packet;                                                                    /**< Packet buffer contains received data. */
} ipv6_data_rx_t;

/**@brief Asynchronous event parameter type. */
typedef union
{
    ipv6_data_rx_t  rx_event_param;                                                                 /**< Parameters notified with the received IPv6 packet. */
} ipv6_event_param_t;

/**@brief Asynchronous event type. */
typedef struct
{
    ipv6_event_id_t    event_id;                                                                    /**< Event identifier. */
    ipv6_event_param_t event_param;                                                                 /**< Event parameters. */
} ipv6_event_t;

/**@brief Asynchronous event notification callback type. */
typedef void (* ipv6_evt_handler_t)(iot_interface_t  * p_interface,
                                    ipv6_event_t     * p_event);

/**@brief Initialization parameters type. */
typedef struct
{
    eui64_t            * p_eui64;                                                                   /**< Global identifiers EUI-64 address of device. */
    ipv6_evt_handler_t   event_handler;                                                             /**< Asynchronous event notification callback registered to receive IPv6 events. */
} ipv6_init_t;


/**@brief Initializes the IPv6 stack module.
 *
 * @param[in]  p_init Initialization parameters.
 *
 * @retval    NRF_SUCCESS If initialization was successful. Otherwise, an error code is returned.
 */
uint32_t ipv6_init(const ipv6_init_t * p_init);

/**@brief Sets address to specific interface.
 *
 * @details API used to add or update an IPv6 address on an interface. The address can have three specific
 *          states that determine transmitting capabilities.
 *
 * @param[in]   p_interface The interface on which the address must be assigned.
 * @param[in]   p_addr      IPv6 address and state to be assigned/updated.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NO_MEM         If no memory was available.
 */
uint32_t ipv6_address_set(const iot_interface_t   * p_interface,
                          const ipv6_addr_conf_t  * p_addr);


/**@brief Removes address from specific interface.
 *
 * @details API used to remove an IPv6 address from an interface.
 *
 * @param[in]   p_interface The interface from which the address must be removed.
 * @param[in]   p_addr      IPv6 address to remove.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NOT_FOUND      If no address was found.
 */
uint32_t ipv6_address_remove(const iot_interface_t * p_interface,
                             const ipv6_addr_t     * p_addr);


/**@brief Checks if given unicast address has been registered.
 *
 * @param[in]   p_interface The interface on which IPv6 address wil be checked.
 * @param[in]   p_addr      IPv6 address to be checked.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NOT_FOUND      If no address was found.
 */
uint32_t ipv6_address_check(const iot_interface_t * p_interface,
                            const ipv6_addr_t     * p_addr);


/**@brief Finds the best matched address and interface.
 *
 * @details API used to find the most suitable interface and address to a given destination address.
 *
 * To look only for the interface, set p_addr_r to NULL.
 *
 * To find the best matched address, IPV6_ADDR_STATE_PREFERRED state of address is required.
 *
 * @param[out]     pp_interface Interface to be found.
 * @param[out]     p_addr_r     Best matching address if procedure succeeded and this value was not NULL.
 * @param[inout]   p_addr_f     IPv6 address for which best matching interface and/or address are requested.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NOT_FOUND      If no interface was found.
 * @retval NRF_ERROR_NOT_SUPPORTED  If the operation was not supported.
 */
uint32_t ipv6_address_find_best_match(iot_interface_t     ** pp_interface,
                                      ipv6_addr_t          * p_addr_r,
                                      const ipv6_addr_t    * p_addr_f);


/**@brief Sends IPv6 packet.
 *
 * @details API used to send an IPv6 packet. Which interface that packet must be sent to is determined
 *          by analyzing the destination address.
 *
 * @param[in]   p_interface The interface to which the packet is to be sent.
 * @param[in]   p_packet    IPv6 packet to send. The packet should be allocated using
 *                          @ref iot_pbuffer_allocate, to give stack control and to release
 *                          the memory buffer.
 *
 * @retval NRF_SUCCESS              If the send request was successful.
 * @retval NRF_ERROR_NOT_FOUND      If there was a failure while looking for the interface.
 * @retval NRF_ERROR_INVALID_PARAM  If there was an error in processing the IPv6 packet.
 * @retval NRF_ERROR_NO_MEM         If no memory was available in the transport
 *                                  interface.
 */
uint32_t ipv6_send(const iot_interface_t * p_interface, iot_pbuffer_t * p_packet);

#ifdef __cplusplus
}
#endif

#endif //IPV6_API_H_

/** @} */

