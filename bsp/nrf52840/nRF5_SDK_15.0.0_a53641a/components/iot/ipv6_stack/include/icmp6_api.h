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
/** @file icmp6_api.h
 *
 * @defgroup iot_icmp6 ICMP6 Application Interface for Nordic's IPv6 stack
 * @ingroup iot_sdk_stack
 * @{
 * @brief Nordic Internet Control Message Protocol Application Interface for Nordic's IPv6 stack.
 *
 * @details This module provides basic features related to ICMPv6 support.
 */

#ifndef ICMP6_API_H__
#define ICMP6_API_H__

#include "sdk_config.h"
#include "sdk_common.h"
#include "iot_defines.h"
#include "ipv6_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ICMP6_ECHO_REQUEST_PAYLOAD_OFFSET           8                          /**< Offset of echo request payload from ICMPv6 header. */


/**@defgroup icmp6_code ICMPv6 codes per message type as defined in RFC 4443.
 * @ingroup iot_icmp6
 * @{
 */
#define ICMP6_DU_CODE_NO_ROUTE_TO_DESTINATION       0                          /**< Code for Destination Unreachable Message when there is no route to destination. */
#define ICMP6_DU_CODE_ADMINISTRATIVELY_PROHIBITED   1                          /**< Code for Destination Unreachable Message when the communication to destination administratively prohibited. */
#define ICMP6_DU_CODE_BEYOND_SCOPE_OF_SOURCE        2                          /**< Code for Destination Unreachable Message when the destination is beyond the scope of source address. */
#define ICMP6_DU_CODE_ADDRESS_UNREACHABLE           3                          /**< Code for Destination Unreachable Message when the destination address is unreachable. */
#define ICMP6_DU_CODE_PORT_UNREACHABLE              4                          /**< Code for Destination Unreachable Message when the destination port is unreachable. */
#define ICMP6_DU_CODE_FAILED_INGRESS_EGRESS_POLICY  5                          /**< Code for Destination Unreachable Message when the source address failed on ingress/egress policy. */
#define ICMP6_DU_CODE_REJECT_ROUTE_TO_DESTINATION   6                          /**< Code for Destination Unreachable Message when the route to destination is rejected. */

#define ICMP6_TE_CODE_EXCEEDED_HOP_LIMIT_TRANSIT    0                          /**< Code for Time Exceeded Message when the packet received had hop limit of zero. */
#define ICMP6_TE_CODE_FAR_TIME_EXCEEDED             1                          /**< Code for Time Exceeded Message to report fragmentation and reassembly timeout. */

#define ICMP6_PP_CODE_INVALID_HEADER                0                          /**< Code for Parameter Problem Message when the header of the incoming packet was erroneous. */
#define ICMP6_PP_CODE_UNKNOWN_NEXT_HEADER           1                          /**< Code for Parameter Problem Message when the next header of the incoming packet was unrecognized. */
#define ICMP6_PP_CODE_UNKNOWN_IPV6_OPTION           2                          /**< Code for Parameter Problem Message when the option of the incoming packet was unrecognized. */

#define ICMP6_ERROR_MESSAGE_INVOKING_PKT_OFFSET     8                          /**< Offset in the received ICMPv6 payload where the packet (partial or complete) that invoked the error message is found. */
/* @} */

/** Neighbor solicitation parameters. */
typedef struct
{
    ipv6_addr_t    target_addr;          /**< The IPv6 address of the target of the solicitation. MUST NOT be a multi-cast address. */
    bool           add_aro;              /**< Indicates if ARO option should be added. */
    uint16_t       aro_lifetime;         /**< The amount of time in units of 60 seconds that the router should retain the NCE for the sender of the NS. */
} icmp6_ns_param_t;

/**@brief Parameters associated with error message in receive and transmit paths. */
typedef struct
{
    uint8_t       type;                  /**< Identifies error message type, valid values as described in RFC 4443. See @ref icmp6_error_type for possible values. */
    uint8_t       code;                  /**< Identifies code, if any associated with the error. See \ref icmp6_code and RFC 4443 for details. */
    union                                /**< Additional field like MTU, pointer or unused based on message type. See RFC 4443 for more details. If unused, application may ignore this field. */
    {
        uint32_t  mtu;                   /**< MTU of next hop limit, used only with ICMP6_TYPE_PACKET_TOO_LONG type. */
        uint32_t  offset;                /**< Offset pointing to the parameter that resulted in the ICMP6_TYPE_PARAMETER_PROBLEM error. Used only with ICMP6_TYPE_PARAMETER_PROBLEM. */
        uint32_t  unused;                /**< Any other error message. Is always zero. */
    } error_field;
    uint8_t     * p_packet;              /**< Points to the start of IPv6 packet that has resulted in the error message. */
    uint16_t      packet_len;            /**< Length of the packet that resulted in error. The module may truncate the packet and pack only partially the packet based on configuration of ICMP6_ERROR_MESSAGE_MAX_SIZE. */
} icmp6_error_message_param_t;


/**@brief   ICMPv6 data RX callback.
 *
 * @details Asynchronous callback used to notify the application of ICMP packets received.
 *          By default, the application is not notified through ICMP of messages related to ECHO
 *          requests or any errors. However, these notifications can easily be enabled by defining
 *          either the ICMP6_ENABLE_ND6_MESSAGES_TO_APPLICATION or the
*           ICMP6_ENABLE_ALL_MESSAGES_TO_APPLICATION if the application should handle them.
 *
 * @param[in]  p_interface    Pointer to the IPv6 interface from where the ICMP packet was received.
 * @param[in]  p_ip_header    Pointer to the IP header of the ICMP packet received.
 * @param[in]  p_icmp_header  Pointer to the ICMP header of the received packet.
 * @param[in]  process_result Notifies the application if the ICMP packet was processed successfully or if
 *                            an error occurred, for example, if the packet was malformed.
 * @param[in]  p_rx_packet    Packet buffer containing the packet received. p_rx_packet->p_payload
 *                            contains the ICMP payload.
 *
 * @retval A provision for the application to notify the module of whether the received packet was
 *          processed successfully by application. The application may take ownership of the received
 *          packet by returning IOT_IPV6_ERR_PENDING, in which case the application must take care to
 *          free it using @ref iot_pbuffer_free.
 */
typedef uint32_t (*icmp6_receive_callback_t)(iot_interface_t  * p_interface,
                                             ipv6_header_t    * p_ip_header,
                                             icmp6_header_t   * p_icmp_header,
                                             uint32_t           process_result,
                                             iot_pbuffer_t    * p_rx_packet);


/**@brief   Sends ICMPv6 Error Message as defined in RFC 4443.
 *
 * @details API to send messages categorized under error messages. See @ref icmp6_error_type and
 *          RFC 4443 for valid types.
 *
 * @param[in]  p_interface    Identifies the interface on which the procedure was requested.
 *                            Shall not be NULL.
 * @param[in]  p_src_addr     Source IPv6 address to be used for the request. Shall not be NULL.
 * @param[in]  p_dest_addr    Destination IPv6 address to which the message send is requested.
 *                            Shall not be NULL.
 * @param[in]  p_param        Parameters describing Type, code, invoking packet information any
 *                            additional details associated with the error message.
 *
 * @retval NRF_SUCCESS If the send request was successful, else, an error code indicating reason for
 *                     failure.
 */
uint32_t icmp6_error_message(const iot_interface_t             * p_interface,
                             const ipv6_addr_t                 * p_src_addr,
                             const ipv6_addr_t                 * p_dest_addr,
                             const icmp6_error_message_param_t * p_param);


/**@brief   Sends ICMPv6 echo request as defined in RFC4443.
 *
 * @details API used to send an ICMPv6 echo request packet to a specific destination address.
 *          The user can decide how much additional data must be sent.
 *
 * The application calling the function should allocate a packet before, with the type set to
 *  ICMP6_PACKET_TYPE in the allocation parameter.
 *
 * The application should pack the payload at ICMP6_ECHO_REQUEST_PAYLOAD_OFFSET. ID,
 * Sequence number, ICMP Code, type checksum, etc. are filled in by the module.
 *
 * The application shall not free the allocated packet buffer if the procedure was successful,
 * to ensure that no data copies are needed when transmitting a packet.
 *
 * @param[in]  p_interface      Pointer to the IPv6 interface to send the ICMP packet.
 * @param[in]  p_src_addr       IPv6 source address from where the echo request is sent.
 * @param[in]  p_dest_addr      IPv6 destination address to where the echo request is sent.
 * @param[in]  p_request        Packet buffer containing the echo request.
 *
 * @retval NRF_SUCCESS If the send request was successful.
 */
uint32_t icmp6_echo_request(const iot_interface_t  * p_interface,
                            const ipv6_addr_t      * p_src_addr,
                            const ipv6_addr_t      * p_dest_addr,
                            iot_pbuffer_t          * p_request);


/**@brief   Sends router solicitation message defined in RFC6775.
 *
 * @details API used to send a neighbor discovery message of type Router Solicitation to a specific
 *          destination address. If no address is known, the user should send the message to all
 *          routers' address (FF02::1).
 *
 * The function internally tries to allocate a packet buffer. EUI-64 used in the SLLAO option is
 * taken from the interface parameter defined in the @ref ipv6_init() function.
 *
 * @param[in]  p_interface      Pointer to the IPv6 interface to send the ICMP packet.
 * @param[in]  p_src_addr       IPv6 source address from where the router solicitation message is
 *                              sent.
 * @param[in]  p_dest_addr      IPv6 destination address to where the router solicitation message is
 *                              sent.
 *
 * @retval NRF_SUCCESS If the send request was successful.
 */
uint32_t icmp6_rs_send(const iot_interface_t  * p_interface,
                       const ipv6_addr_t      * p_src_addr,
                       const ipv6_addr_t      * p_dest_addr);


/**@brief   Sends neighbour solicitation message defined in RFC6775.
 *
 * @details API used to send a neighbor discovery message of type Neighbor Solicitation to a
 *         specific destination address.
 *
 * The function internally tries to allocate a packet buffer. EUI-64 used in the SLLAO and ARO
 * options is taken from the interface parameter defined in the @ref ipv6_init() function.
 *
 * @param[in]  p_interface      Pointer to the IPv6 interface to send the ICMP packet.
 * @param[in]  p_src_addr       IPv6 source address from where the neighbor solicitation message is
 *                              sent.
 * @param[in]  p_dest_addr      IPv6 destination address to where the neighbor solicitation message
 *                              is sent.
 * @param[in]  p_ns_param       Neighbor discovery parameters.
 *
 * @retval NRF_SUCCESS  If the send request was successful.
 */
uint32_t icmp6_ns_send(const iot_interface_t  * p_interface,
                       const ipv6_addr_t      * p_src_addr,
                       const ipv6_addr_t      * p_dest_addr,
                       const icmp6_ns_param_t * p_ns_param);


/**@brief   Registers the callback function for echo reply.
 *
 * @details API used to register callback to indicate the ICMP echo reply packet. Could be not used.
 *
 * Neighbor discovery related messages are not relayed to the application by default.
 *       However, this can be enabled by using the ICMP6_ENABLE_ND6_MESSAGES_TO_APPLICATION
 *       configuration parameter.
 *
 * @param[in]  cb  Handler called when an ICMP packet is received.
 *
 * @retval NRF_SUCCESS If the registration was successful.
 */
uint32_t icmp6_receive_register(icmp6_receive_callback_t cb);

#ifdef __cplusplus
}
#endif

#endif //ICMP6_API_H__

/**@} */
