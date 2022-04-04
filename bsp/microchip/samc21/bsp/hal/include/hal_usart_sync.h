/**
 * \file
 *
 * \brief USART related functionality declaration.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef _HAL_SYNC_USART_H_INCLUDED
#define _HAL_SYNC_USART_H_INCLUDED

#include "hal_io.h"
#include <hpl_usart_sync.h>

/**
 * \addtogroup doc_driver_hal_usart_sync
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Synchronous USART descriptor
 */
struct usart_sync_descriptor {
	struct io_descriptor      io;
	struct _usart_sync_device device;
};

/**
 * \brief Initialize USART interface
 *
 * This function initializes the given I/O descriptor to be used
 * as USART interface descriptor.
 * It checks if the given hardware is not initialized and
 * if the given hardware is permitted to be initialized.
 *
 * \param[out] descr A USART descriptor which is used to communicate via USART
 * \param[in] hw The pointer to hardware instance
 * \param[in] func The pointer to as set of functions pointers
 *
 * \return Initialization status.
 */
int32_t usart_sync_init(struct usart_sync_descriptor *const descr, void *const hw, void *const func);

/**
 * \brief Deinitialize USART interface
 *
 * This function deinitializes the given I/O descriptor.
 * It checks if the given hardware is initialized and
 * if the given hardware is permitted to be deinitialized.
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 *
 * \return De-initialization status.
 */
int32_t usart_sync_deinit(struct usart_sync_descriptor *const descr);

/**
 * \brief Enable USART interface
 *
 * Enables the USART interface
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 *
 * \return Enabling status.
 */
int32_t usart_sync_enable(struct usart_sync_descriptor *const descr);

/**
 * \brief Disable USART interface
 *
 * Disables the USART interface
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 *
 * \return Disabling status.
 */
int32_t usart_sync_disable(struct usart_sync_descriptor *const descr);

/**
 * \brief Retrieve I/O descriptor
 *
 * This function retrieves the I/O descriptor of the given USART descriptor.
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[out] io An I/O descriptor to retrieve
 *
 * \return The status of the I/O descriptor retrieving.
 */
int32_t usart_sync_get_io_descriptor(struct usart_sync_descriptor *const descr, struct io_descriptor **io);

/**
 * \brief Specify action for flow control pins
 *
 * This function sets the action (or state) for the flow control pins
 * if the flow control is enabled.
 * It sets the state of flow control pins only if the automatic support of
 * the flow control is not supported by the hardware.
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[in] state A state to set the flow control pins
 *
 * \return The status of flow control action setup.
 */
int32_t usart_sync_set_flow_control(struct usart_sync_descriptor *const  descr,
                                    const union usart_flow_control_state state);

/**
 * \brief Set USART baud rate
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[in] baud_rate A baud rate to set
 *
 * \return The status of baud rate setting.
 */
int32_t usart_sync_set_baud_rate(struct usart_sync_descriptor *const descr, const uint32_t baud_rate);

/**
 * \brief Set USART data order
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[in] data_order A data order to set
 *
 * \return The status of data order setting.
 */
int32_t usart_sync_set_data_order(struct usart_sync_descriptor *const descr, const enum usart_data_order data_order);

/**
 * \brief Set USART mode
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[in] mode A mode to set
 *
 * \return The status of mode setting.
 */
int32_t usart_sync_set_mode(struct usart_sync_descriptor *const descr, const enum usart_mode mode);

/**
 * \brief Set USART parity
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[in] parity A parity to set
 *
 * \return The status of parity setting.
 */
int32_t usart_sync_set_parity(struct usart_sync_descriptor *const descr, const enum usart_parity parity);

/**
 * \brief Set USART stop bits
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[in] stop_bits Stop bits to set
 *
 * \return The status of stop bits setting.
 */
int32_t usart_sync_set_stopbits(struct usart_sync_descriptor *const descr, const enum usart_stop_bits stop_bits);

/**
 * \brief Set USART character size
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[in] size A character size to set
 *
 * \return The status of character size setting.
 */
int32_t usart_sync_set_character_size(struct usart_sync_descriptor *const descr, const enum usart_character_size size);

/**
 * \brief Retrieve the state of flow control pins
 *
 * This function retrieves the of flow control pins
 * if the flow control is enabled.
 * Function can return USART_FLOW_CONTROL_STATE_UNAVAILABLE in case
 * if the flow control is done by the hardware
 * and the pins state cannot be read out.
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 * \param[out] state The state of flow control pins
 *
 * \return The status of flow control state reading.
 */
int32_t usart_sync_flow_control_status(const struct usart_sync_descriptor *const descr,
                                       union usart_flow_control_state *const     state);

/**
 * \brief Check if the USART transmitter is empty
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 *
 * \return The status of USART TX empty checking.
 * \retval 0 The USART transmitter is not empty
 * \retval 1 The USART transmitter is empty
 */
int32_t usart_sync_is_tx_empty(const struct usart_sync_descriptor *const descr);

/**
 * \brief Check if the USART receiver is not empty
 *
 * \param[in] descr A USART descriptor which is used to communicate via USART
 *
 * \return The status of USART RX empty checking.
 * \retval 1 The USART receiver is not empty
 * \retval 0 The USART receiver is empty
 */
int32_t usart_sync_is_rx_not_empty(const struct usart_sync_descriptor *const descr);

/**
 * \brief Retrieve the current driver version
 *
 * \return Current driver version.
 */
uint32_t usart_sync_get_version(void);

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HAL_SYNC_USART_H_INCLUDED */
