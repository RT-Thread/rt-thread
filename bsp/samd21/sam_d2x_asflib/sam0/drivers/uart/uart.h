/**
 *
 * \file
 *
 * \brief SAM UART Driver for SAMB11
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

/**
 * \defgroup asfdoc_samb_uart_group SAM UART Driver (UART)
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the
 * configuration and management of the device's Universal Asynchronous
 * Receiver/Transmitter (UART) interfaces functionality.
 *
 * The following peripherals are used by this module:
 *  - UART (Universal Asynchronous Receiver/Transmitter)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_samb_uart_prerequisites
 *  - \ref asfdoc_samb_uart_module_overview
 *  - \ref asfdoc_samb_uart_special_considerations
 *  - \ref asfdoc_samb_uart_extra_info
 *  - \ref asfdoc_samb_uart_examples
 *  - \ref asfdoc_samb_uart_api_overview
 *
 *
 * \section asfdoc_samb_uart_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_samb_uart_module_overview Module Overview
 *
 * The device UART module provides an interface between the user application
 * logic and hardware peripheral. This driver provides an easy-to-use interface
 * to transfer and receive data.
 *
 * \section asfdoc_samb_uart_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_samb_uart_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_samb_uart_extra. This includes:
 *  - \ref asfdoc_samb_uart_extra_acronyms
 *  - \ref asfdoc_samb_uart_extra_dependencies
 *  - \ref asfdoc_samb_uart_extra_errata
 *  - \ref asfdoc_samb_uart_extra_history
 *
 *
 * \section asfdoc_samb_uart_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_uart_exqsg.
 *
 *
 * \section asfdoc_samb_uart_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system_sam_b.h>
#include <gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \brief UART byte bit selection
 *
 * Number of bit per byte selection for UART communication.
 */
enum uart_number_of_bit_selection{
	/** 8 bit per byte*/
	UART_8_BITS = UART_CONFIGURATION_NUMBER_OF_BITS_0,
	/** 7 bit per byte*/
	UART_7_BITS = UART_CONFIGURATION_NUMBER_OF_BITS_1,
};

/** \brief UART stop bit selection
 *
 * Number of stop bit selection for UART communication.
 */
enum uart_stop_bit_selection{
	/** 1 stop bit per byte*/
	UART_1_STOP_BIT = UART_CONFIGURATION_STOP_BITS_0,
	/** 2 stop bit per byte*/
	UART_2_STOP_BITS = UART_CONFIGURATION_STOP_BITS_1,
};


/** \brief UART Parity selection
 *
 * Parity type selection for UART communication.
 */
enum uart_parity_selection{
	/** No parity bit */
	UART_NO_PARITY = 0,
	/** Even parity */
	UART_EVEN_PARITY,
	/** Odd parity */
	UART_ODD_PARITY,
	/** Space parity */
	UART_SPACE_PARITY,
	/** Mark parity */
	UART_MARK_PARITY
};

/**
 * \brief UART module instance
 *
 * Forward Declaration for the device instance.
 */
struct uart_module;

/**
 * \brief UART callback type
 *
 * Type of the callback functions.
 */
typedef void (*uart_callback_t)(struct uart_module *const module);

/**
 * \brief UART Callback enum
 *
 * Callbacks for the UART driver.
 */
enum uart_callback {
	/** Callback for TX FIFO not full. */
	UART_TX_COMPLETE,
	/** Callback for CTS active. */
	UART_CTS_ACTIVE,
	/** Callback for RX FIFO overrun. */
	UART_RX_COMPLETE,
	/** Callback for RX FIFO overrun. */
	UART_RX_FIFO_OVERRUN,
	/** Number of available callbacks. */
	UART_CALLBACK_N,
};


/**
 * \brief Configuration structure for the UART module
 *
 * This is the configuration structure for the UART Module in SAMB11. It
 * is used as an argument for \ref uart_init to provide the desired
 * configurations for the module. The structure should be initialized using the
 * \ref uart_get_config_defaults .
 */
struct uart_config{
	/** Baud rate */
	uint32_t baud_rate;
	/** Number of data bits */
	enum uart_number_of_bit_selection data_bits;
	/** Number of stop bits */
	enum uart_stop_bit_selection stop_bits;
	/** Parity type */
	enum uart_parity_selection parity;
	/** flow control type */
	bool flow_control;
	/** UART PAD pin number */
	uint32_t pin_number_pad[4];
	/** UART PAD pinmux selection */
	uint32_t pinmux_sel_pad[4];
};

/**
 * \brief UART driver software device instance structure.
 *
 * UART driver software instance structure, used to retain software
 * state information of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct uart_module {
	/** Pointer to the hardware instance. */
	Uart *hw;
	/** Array to store callback function pointers in. */
	uart_callback_t callback[UART_CALLBACK_N];
	/** Buffer pointer to where the next received character will be put */
	volatile uint8_t *rx_buffer_ptr;
	/** Buffer pointer to where the next character will be transmitted from
	**/
	volatile uint8_t *tx_buffer_ptr;
	/** Remaining characters to receive */
	volatile uint16_t remaining_rx_buffer_length;
	/** Remaining characters to transmit */
	volatile uint16_t remaining_tx_buffer_length;
	/** Bit mask for callbacks registered. */
	uint8_t callback_reg_mask;
	/** Bit mask for callbacks enabled. */
	uint8_t callback_enable_mask;
	/** Holds the status of the ongoing or last operation */
	volatile enum status_code status;
};

/** \name UART Configuration and initialization
 * @{
 */
void uart_get_config_defaults(struct uart_config *const config);
enum status_code uart_init(struct uart_module *const module, Uart * const hw,
		const struct uart_config *const config);
/** @} */

/** \name UART read and write functions
 * @{
 */
enum status_code uart_write_wait(struct uart_module *const module,
		const uint8_t tx_data);
enum status_code uart_read_wait(struct uart_module *const module,
		uint8_t *const rx_data);
enum status_code uart_write_buffer_wait(struct uart_module *const module,
		const uint8_t *tx_data, uint32_t length);
enum status_code uart_read_buffer_wait(struct uart_module *const module,
		uint8_t *rx_data, uint16_t length);
enum status_code uart_write_buffer_job(struct uart_module *const module,
		uint8_t *tx_data, uint32_t length);
enum status_code uart_read_buffer_job(struct uart_module *const module,
		uint8_t *rx_data, uint16_t length);
/** @} */

/** \name UART callback config
 * @{
 */
void uart_register_callback(struct uart_module *const module,
		uart_callback_t callback_func,
		enum uart_callback callback_type);
void uart_unregister_callback(struct uart_module *module,
		enum uart_callback callback_type);
void uart_enable_callback(struct uart_module *const module,
		enum uart_callback callback_type);
void uart_disable_callback(struct uart_module *const module,
		enum uart_callback callback_type);
/** @}*/

/** \name UART DAM enable/disable functions
 * @{
 */
void uart_enable_transmit_dma(struct uart_module *const module);
void uart_disable_transmit_dma(struct uart_module *const module);
void uart_enable_receive_dma(struct uart_module *const module);
void uart_disable_receive_dma(struct uart_module *const module);
/** @}*/

/** @}*/

#ifdef __cplusplus
}
#endif


/**
 * \page asfdoc_samb_uart_extra Extra Information for UART Driver
 *
 * \section asfdoc_samb_uart_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>UART</td>
 *		<td>Universal Asynchronous Receiver/Transmitter</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_samb_uart_extra_dependencies Dependencies
 * There are no dependencies related to this driver.
 *
 *
 * \section asfdoc_samb_uart_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_samb_uart_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_samb_uart_exqsg Examples for UART Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_samb_uart_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_samb_uart_basic_use_case
 *  - \subpage asfdoc_samb_uart_dma_use_case
 *
 * \page asfdoc_samb_uart_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>A</td>
 *		<td>09/2015</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

#endif
