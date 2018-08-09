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
/**
 * @addtogroup ser_app Application side code
 * @ingroup ble_sdk_lib_serialization
 * @brief SoftDevice handler and transport on the application side.
 */

/** @file
 *
 * @defgroup ser_sd_transport Serialization SoftDevice Transport
 * @{
 * @ingroup ser_app
 *
 * @brief   Serialization SoftDevice Transport on application side.
 *
 * @details This file contains declarations of functions and definitions of data structures and
 *          identifiers (typedef enum) used as API of the serialization of SoftDevice. This layer
 *          ensures atomic nature of SoftDevice calls (command and waiting for response). Packet
 *          type field of incoming packets is handled in this layer - responses are handled by
 *          ser_sd_transport (using response decoder handler provided for each SoftDevice call), but
 *          events are forwarded to the user so it is up to the user to free the RX buffer.
 *
 */
#ifndef SER_SD_TRANSPORT_H_
#define SER_SD_TRANSPORT_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ser_sd_transport_evt_handler_t)(uint8_t * p_buffer, uint16_t length);
typedef void (*ser_sd_transport_rsp_wait_handler_t)(void);
typedef void (*ser_sd_transport_rsp_set_handler_t)(void);
typedef void (*ser_sd_transport_rx_notification_handler_t)(void);

typedef uint32_t (*ser_sd_transport_rsp_handler_t)(const uint8_t * p_buffer, uint16_t length);

/**@brief Function for opening the module.
 *
 * @note 'Wait for response' and 'Response set' callbacks can be set in RTOS environment.
 *       It enables rescheduling while waiting for the Connectivity Chip response. In a nonOS environment,
 *       usually 'Wait for response' will only be used for handling incoming events or forcing the
 *       application to low power mode.
 *
 * @param[in] ble_evt_handler           Handler to be called when ble event packet is received.
 * @param[in] ant_evt_handler           Handler to be called when ant event packet is received.
 * @param[in] os_rsp_wait_handler       Handler to be called after the request is send. It should
 *                                      implement a 'Wait for signal' functionality in an OS environment.
 * @param[in] os_rsp_set_handler        Handler to be called after response reception. It should
 *                                      implement a 'Signal Set' functionality in an OS environment.
 * @param[in] rx_not_handler            Handler to be called after the transport layer notifies that
 *                                      an incoming RX packet is detected.
 *
 * @retval NRF_SUCCESS              Operation success.
 * @retval NRF_ERROR_NULL           Operation failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_PARAM  Operation failure. Parameter propagated from ser_hal_transport
 *                                  opening or timer creation.
 * @retval NRF_ERROR_INVALID_STATE  Operation failure. Parameter propagated from ser_hal_transport
 *                                  opening or timer creation.
 * @retval NRF_ERROR_INTERNAL       Operation failure.  Parameter propagated from ser_hal_transport
 *                                  opening or timer creation.
 * @retval NRF_ERROR_NO_MEM         Operation failure.  Parameter propagated from timer creation.
 */
uint32_t ser_sd_transport_open(ser_sd_transport_evt_handler_t             ble_evt_handler,
                               ser_sd_transport_evt_handler_t             ant_evt_handler,
                               ser_sd_transport_rsp_wait_handler_t        os_rsp_wait_handler,
                               ser_sd_transport_rsp_set_handler_t         os_rsp_set_handler,
                               ser_sd_transport_rx_notification_handler_t rx_not_handler);


/**@brief Function setting a 'One Time' handler to be called between sending the next request packet and
 *        receiving the response packet.
 * @note It is intended to be used in a nonOS environment to implement concurrency.
 * @note It is a 'One Time' handler meaning that it is valid only for the next SoftDevice call processing.
 *
 *
 * @param[in] wait_handler       Handler to be called after the request packet is sent.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t ser_sd_transport_ot_rsp_wait_handler_set(ser_sd_transport_rsp_wait_handler_t wait_handler);


/**@brief Function for closing the module.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t ser_sd_transport_close(void);

/**@brief Function for allocating a TX packet to be used for request command.
 *
 * @param[out] pp_data       Pointer to the data pointer to be set to point to allocated buffer.
 * @param[out] p_len         Pointer to allocated buffer length.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t ser_sd_transport_tx_alloc(uint8_t * * pp_data, uint16_t * p_len);


/**@brief Function for freeing a TX packet.
 *
 * @note Function should be called once the command is processed.
 *
 * @param[out] p_data       Pointer to the allocated TX buffer.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t ser_sd_transport_tx_free(uint8_t * p_data);


/**@brief Function for freeing an RX event packet.
 *
 * @note Function should be called once the SoftDevice event buffer is processed.
 *
 * @param[out] p_data       Pointer to the allocated RX buffer.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t ser_sd_transport_rx_free(uint8_t * p_data);


/**@brief Function for checking if module is busy waiting for response from connectivity side.
 *
 * @retval true      Module busy. Cannot accept the next command.
 * @retval false     Module not busy. Can accept next the command.
 */
bool ser_sd_transport_is_busy(void);

/**@brief Function for handling a SoftDevice command.
 *
 * @note Function blocks task context until response is received and processed.
 * @note Non-blocking functionality can be achieved using OS handlers or a 'One Time' handler
 * @warning Function should not be called from interrupt context, which would block switching to
 *          serial port interrupt.
 *
 * @param[in] p_buffer                 Pointer to command.
 * @param[in] length                   Pointer to allocated buffer length.
 * @param[in] cmd_resp_decode_callback Pointer to a function for decoding the response packet.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t ser_sd_transport_cmd_write(const uint8_t *                p_buffer,
                                    uint16_t                       length,
                                    ser_sd_transport_rsp_handler_t cmd_resp_decode_callback);


#ifdef __cplusplus
}
#endif

#endif /* SER_SD_TRANSPORT_H_ */
/** @} */
