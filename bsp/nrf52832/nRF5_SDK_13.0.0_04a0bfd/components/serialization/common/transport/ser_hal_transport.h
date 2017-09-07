/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
 * @defgroup ser_hal_transport Serialization HAL Transport
 * @{
 * @ingroup ble_sdk_lib_serialization
 *
 * @brief HAL Transport layer for serialization.
 *
 * @details The @ref ser_hal_transport declares functions and typedefs used as API of the HAL
 *          transport layer for serialization. This layer is fully hardware-independent.
 *          Currently, the HAL transport layer is responsible for controlling the PHY layer and
 *          memory management. In the future, more features might be added to it, such as CRC
 *          or retransmission.
 *
 * \n \n
 * \image html ser_hal_transport_rx_state_machine.svg "RX state machine"
 * \n \n
 * \image html ser_hal_transport_tx_state_machine.svg "TX state machine"
 * \n
 */

#ifndef SER_HAL_TRANSPORT_H__
#define SER_HAL_TRANSPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Serialization HAL Transport layer event types. */
typedef enum
{
    SER_HAL_TRANSP_EVT_TX_PKT_SENT = 0,     /**< An event indicating that TX packet has been
                                                 transmitted. */
    SER_HAL_TRANSP_EVT_RX_PKT_RECEIVING,    /**< An event indicating that RX packet is being
                                                 scheduled to receive or to drop. */
    SER_HAL_TRANSP_EVT_RX_PKT_RECEIVED,     /**< An event indicating that RX packet is ready for
                                                 read. */
    SER_HAL_TRANSP_EVT_RX_PKT_DROPPED,      /**< An event indicating that RX packet was dropped
                                                 because it was longer than available buffer. */
    SER_HAL_TRANSP_EVT_PHY_ERROR,           /**< An event indicating error on PHY layer. */
    SER_HAL_TRANSP_EVT_TYPE_MAX             /**< Enumeration upper bound. */
} ser_hal_transport_evt_type_t;


/**@brief Serialization PHY layer error types. */
typedef enum
{
    SER_HAL_TRANSP_PHY_ERROR_RX_OVERFLOW = 0, /**< An error indicating that more information has
                                                   been transmitted than the PHY module could handle. */
    SER_HAL_TRANSP_PHY_ERROR_TX_OVERREAD,     /**< An error indicating that the PHY module was forced to
                                                   transmit more information than possessed. */
    SER_HAL_TRANSP_PHY_ERROR_HW_ERROR,        /**< An error indicating a hardware error in the PHY
                                                   module. */
    SER_HAL_TRANSP_PHY_ERROR_TYPE_MAX         /**< Enumeration upper bound. */
} ser_hal_transport_phy_error_type_t;


/**@brief Struct containing parameters of event of type
 *        @ref SER_HAL_TRANSP_EVT_RX_PKT_RECEIVED.
 */
typedef struct
{
    uint8_t * p_buffer;     /**< Pointer to a buffer containing a packet to read. */
    uint16_t  num_of_bytes; /**< Length of a received packet in octets. */
} ser_hal_transport_evt_rx_pkt_received_params_t;


/**@brief Struct containing parameters of event of type @ref SER_HAL_TRANSP_EVT_PHY_ERROR. */
typedef struct
{
    ser_hal_transport_phy_error_type_t error_type; /**< Type of the PHY error. */
    uint32_t hw_error_code; /**< Hardware error code - specific for a microcontroller. Parameter
                                 is valid only for the PHY error of type
                                 @ref SER_HAL_TRANSP_PHY_ERROR_HW_ERROR. */
} ser_hal_transport_evt_phy_error_params_t;


/**@brief Struct containing events from the Serialization HAL Transport layer.
 *
 * @note  Some events do not have parameters, then the whole information is contained in the evt_type.
 */
typedef struct
{
    ser_hal_transport_evt_type_t evt_type;  /**< Type of event. */
    union  /**< Union alternative identified by evt_type in the enclosing struct. */
    {
        ser_hal_transport_evt_rx_pkt_received_params_t  rx_pkt_received; /**< Parameters of event of type @ref SER_HAL_TRANSP_EVT_RX_PKT_RECEIVED. */
        ser_hal_transport_evt_phy_error_params_t        phy_error;       /**< Parameters of event of type @ref SER_HAL_TRANSP_EVT_PHY_ERROR. */
    } evt_params;
} ser_hal_transport_evt_t;


/**@brief Generic callback function type to be used by all Serialization HAL Transport layer
 *        events.
 *
 * @param[in] event    Serialization HAL Transport layer event.
 */
typedef void (*ser_hal_transport_events_handler_t)(ser_hal_transport_evt_t event);


/**@brief Function for opening and initializing the Serialization HAL Transport layer.
 *
 * @note The function opens the transport channel, initializes a PHY layer, and registers the callback
 *       function to be used by all Serialization HAL Transport layer events.
 *
 * @warning If the function has been already called, the function @ref ser_hal_transport_close has
 *          to be called before ser_hal_transport_open can be called again.
 *
 * @param[in] events_handler    Generic callback function to be used by all Serialization HAL
 *                              Transport layer events.
 *
 * @retval NRF_SUCCESS              Operation success.
 * @retval NRF_ERROR_NULL           Operation failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_PARAM  Operation failure. Hardware initialization parameters taken from
 *                                  the configuration file are wrong.
 * @retval NRF_ERROR_INVALID_STATE  Operation failure. The function has been already called. To call
 *                                  it again the function @ref ser_hal_transport_close has to be
 *                                  called first.
 * @retval NRF_ERROR_INTERNAL       Operation failure. Internal error ocurred.
 */
uint32_t ser_hal_transport_open(ser_hal_transport_events_handler_t events_handler);


/**@brief Function for closing a transport channel.
 *
 * @note The function disables the hardware, resets internal module states, and unregisters the events
 *       callback function. Can be called multiple times, also for a channel that is not opened.
 */
void ser_hal_transport_close(void);


/**@brief Function for freeing memory allocated for an RX packet.
 *
 * @note The function should be called as a response to an event of type
 *       @ref SER_HAL_TRANSP_EVT_RX_PKT_RECEIVED when the received data has beed processed. The function
 *       frees the RX memory pointed by p_buffer. The memory, immediately or at a later time, is
 *       reused by the underlying transport layer.
 *
 * @param[in] p_buffer    A pointer to the beginning of the buffer that has been processed (has to be
 *                        the same address as provided in the event of type
 *                        @ref SER_HAL_TRANSP_EVT_RX_PKT_RECEIVED).
 *
 * @retval NRF_SUCCESS              Operation success.
 * @retval NRF_ERROR_NULL           Operation failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_ADDR   Operation failure. Not a valid pointer (provided address is not
 *                                  the starting address of a buffer managed by HAL Transport layer).
 * @retval NRF_ERROR_INVALID_STATE  Operation failure. The function should be called as a response
 *                                  to an event of type @ref SER_HAL_TRANSP_EVT_RX_PKT_RECEIVED.
 * @retval NRF_ERROR_INTERNAL       Operation failure. Internal error ocurred.
 */
uint32_t ser_hal_transport_rx_pkt_free(uint8_t * p_buffer);


/**@brief Function for allocating memory for a TX packet.
 *
 * @param[out] pp_memory       A pointer to pointer to which an address of the beginning of the
 *                             allocated buffer is written.
 * @param[out] p_num_of_bytes  A pointer to a variable to which size in octets of the allocated
 *                             buffer is written.
 *
 * @retval NRF_SUCCESS              Operation success. Memory was allocated.
 * @retval NRF_ERROR_NULL           Operation failure. NULL pointer supplied.
 * @retval NRF_ERROR_NO_MEM         Operation failure. No memory available.
 * @retval NRF_ERROR_INVALID_STATE  Operation failure. The function was called before calling
 *                                  @ref ser_hal_transport_open function.
 */
uint32_t ser_hal_transport_tx_pkt_alloc(uint8_t ** pp_memory, uint16_t * p_num_of_bytes);

/**@brief Function for transmitting a packet.
 *
 * @note The function adds a packet pointed by the p_buffer parameter to a transmission queue. A buffer
 *       provided to this function must be allocated by the @ref ser_hal_transport_tx_pkt_alloc function.
 *
 * @warning Completion of this method does not guarantee that actual peripheral transmission will be completed.
 *
 * @param[in] p_buffer        Pointer to the buffer to transmit.
 * @param[in] num_of_bytes    Number of octets to transmit. Must be more than 0.
 *
 * @retval NRF_SUCCESS              Operation success. Packet was added to the transmission queue.
 * @retval NRF_ERROR_NULL           Operation failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_PARAM  Operation failure. num_of_bytes is equal to 0.
 * @retval NRF_ERROR_INVALID_ADDR   Operation failure. Not a valid pointer (provided address is not
 *                                  the starting address of a buffer managed by HAL Transport layer).
 * @retval NRF_ERROR_DATA_SIZE      Operation failure. Packet size exceeds limit.
 * @retval NRF_ERROR_BUSY           Operation failure. Transmission queue is full so packet was not
 *                                  added to the transmission queue.
 * @retval NRF_ERROR_INVALID_STATE  Operation failure. Transmittion channel was not opened by
 *                                  @ref ser_hal_transport_open function or provided buffer was not
 *                                  allocated by @ref ser_hal_transport_tx_pkt_alloc function.
 * @retval NRF_ERROR_INTERNAL       Operation failure. Internal error ocurred.
 */
uint32_t ser_hal_transport_tx_pkt_send(const uint8_t * p_buffer, uint16_t num_of_bytes);


/**@brief Function for freeing memory allocated for a TX packet.
 *
 * @note The function frees the TX memory pointed by p_buffer. Freeing a TX buffer is possible only if
 *       the buffer was allocated by @ref ser_hal_transport_tx_pkt_alloc function and transmittion
 *       is not in progress. When transmittion has finished, this function is automatically called by
 *       the Serialization HAL Transport layer, so the only case when this function should be used
 *       from outside is when a TX buffer was allocated but a transmittion has not been started
 *       (@ref ser_hal_transport_tx_pkt_send function has not been called).
 *
 * @param[in] p_buffer    Pointer to the beginning of a buffer that has been allocated by
 *                        @ref ser_hal_transport_tx_pkt_alloc function.
 *
 * @retval NRF_SUCCESS              Operation success. Memory was freed.
 * @retval NRF_ERROR_NULL           Operation failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_ADDR   Operation failure. Not a valid pointer (provided address is not
 *                                  the starting address of a buffer managed by HAL Transport layer).
 * @retval NRF_ERROR_INVALID_STATE  Operation failure. Freeing a TX buffer is possible only if the
 *                                  buffer was allocated by @ref ser_hal_transport_tx_pkt_alloc
 *                                  function and transmittion is not in progress.
 */
uint32_t ser_hal_transport_tx_pkt_free(uint8_t * p_buffer);



#ifdef __cplusplus
}
#endif

#endif /* SER_HAL_TRANSPORT_H__ */
/** @} */
