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
/** @file coap_transport.h
 *
 * @defgroup iot_sdk_coap_transport CoAP transport abstraction
 * @ingroup iot_sdk_coap
 * @{
 * @brief The transport interface that the CoAP depends on for sending and receiving CoAP messages.
 *
 * @details  While the interface is well defined and should not be altered, the implementation of the
 *        interface depends on the choice of IP stack. The only exception to this is the
 *        \ref coap_transport_read API. This API is implemented in the CoAP, and the transport layer is
 *        expected to call this function when data is received on one of the CoAP ports.
 */

#ifndef COAP_TRANSPORT_H__
#define COAP_TRANSPORT_H__

#include <stdint.h>
#include <nrf_tls.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Port identification information. */
typedef struct
{
    uint16_t      port_number;                       /**< Port number. */
} coap_port_t;


/**@brief Remote endpoint. */
typedef struct
{
    uint8_t        addr[16];                        /**< Address of the remote device. */
    uint16_t       port_number;                     /**< Remote port number. */
} coap_remote_t;


/**@brief Transport initialization information. */
typedef struct
{
    coap_port_t     * p_port_table;                 /**< Information about the ports being registered. Count is assumed to be COAP_PORT_COUNT. */
    void            * p_arg;                        /**< Public. Miscellaneous pointer to application provided data that should be passed to the transport. */
} coap_transport_init_t;



/**@brief Initializes the transport layer to have the data ports set up for CoAP.
 *
 * @param[in] p_param  Port count and port numbers.
 *
 * @retval NRF_SUCCESS If initialization was successful. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t coap_transport_init (const coap_transport_init_t   * p_param);


/**@brief Sends data on a CoAP endpoint or port.
 *
 * @param[in] p_port    Port on which the data is to be sent.
 * @param[in] p_remote  Remote endpoint to which the data is targeted.
 * @param[in] p_data    Pointer to the data to be sent.
 * @param[in] datalen   Length of the data to be sent.
 *
 * @retval NRF_SUCCESS If the data was sent successfully. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t coap_transport_write(const coap_port_t    * p_port,
                              const coap_remote_t  * p_remote,
                              const uint8_t        * p_data,
                              uint16_t               datalen);



/**@brief Handles data received on a CoAP endpoint or port.
 *
 * This API is not implemented by the transport layer, but assumed to exist. This approach
 * avoids unnecessary registering of callback and remembering it in the transport layer.
 *
 * @param[in] p_port    Port on which the data is received.
 * @param[in] p_remote  Remote endpoint from which the data is received.
 * @param[in] p_local   Local endpoint on which the data is received.
 * @param[in] result    Indicates if the data was processed successfully by lower layers.
 *                      Possible failures could be NRF_SUCCESS,
 *                                                 UDP_BAD_CHECKSUM,
 *                                                 UDP_TRUNCATED_PACKET, or
 *                                                 UDP_MALFORMED_PACKET.
 * @param[in] p_data    Pointer to the data received.
 * @param[in] datalen   Length of the data received.
 *
 * @retval NRF_SUCCESS If the data was handled successfully. Otherwise, an error code that indicates the reason for the failure is returned.
 *
 */
uint32_t coap_transport_read(const coap_port_t    * p_port,
                             const coap_remote_t  * p_remote,
                             const coap_remote_t  * p_local,
                             uint32_t               result,
                             const uint8_t        * p_data,
                             uint16_t               datalen);


/**@brief Process loop to handle DTLS processing.
 *
 * @details The function handles any processing of encrypted packets.
 *          Some encryption libraries requires to be run in a processing
 *          loop. This function is called by the CoAP library everytime
 *          \ref coap_time_tick is issued from the library user. Any other process
 *          specific routines that should be done regularly could be added in
 *          this function.
 */
void coap_transport_process(void);

/**@brief Process loop when using coap BSD socket transport implementation.
 *
 * @details This is blocking call. The function unblock is only
 *          triggered upon an socket event registered to select() by coap transport.
 *          This function must be called as often as possible in order to dispatch incomming
 *          socket events. Preferred to be put in the application's main loop or similar.
 */
void coap_transport_input(void);

#ifdef __cplusplus
}
#endif

#endif //COAP_TRANSPORT_H__

/** @} */
