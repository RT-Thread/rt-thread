/**
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
#include "uart.h"

/**
 * \internal
 * Internal driver device instance struct.
 */
struct uart_module *_uart_instances[UART_INST_NUM];

/**
 * \internal
 * Writes a character from the TX buffer to the Data register.
 *
 * \param[in,out]  module  Pointer to UART software instance struct
 */
static void _uart_write(struct uart_module *const module)
{
	/* Pointer to the hardware module instance */
	Uart *const uart_hw = module->hw;

	/* Write value will be at least 8-bits long */
	uint8_t data_to_send = *(module->tx_buffer_ptr);
	/* Increment 8-bit pointer */
	(module->tx_buffer_ptr)++;

	/* Write the data to send*/
	uart_hw->TRANSMIT_DATA.reg = data_to_send & UART_TRANSMIT_DATA_MASK;

	/* Decrement remaining buffer length */
	(module->remaining_tx_buffer_length)--;
}

/**
 * \internal
 * Reads a character from the Data register to the RX buffer.
 *
 * \param[in,out]  module  Pointer to UART software instance struct
 */
static void _uart_read(
		struct uart_module *const module)
{
	/* Pointer to the hardware module instance */
	Uart *const uart_hw = module->hw;

	uint16_t received_data = (uart_hw->RECEIVE_DATA.reg & UART_RECEIVE_DATA_MASK);

	/* Read value will be at least 8-bits long */
	*(module->rx_buffer_ptr) = received_data;
	/* Increment 8-bit pointer */
	module->rx_buffer_ptr += 1;

	/* Decrement length of the remaining buffer */
	module->remaining_rx_buffer_length--;
}

static void uart_rx0_isr_handler(void)
{
	struct uart_module *module = _uart_instances[0];
	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->RECEIVE_STATUS.reg;
	if (flags & UART_RECEIVE_STATUS_FIFO_OVERRUN) {
		/* Store the error code */
		module->status = STATUS_ERR_OVERFLOW;
		/* Disable interrupt */
		module->hw->RX_INTERRUPT_MASK.reg &=
			~(UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK |
			SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
		if ((module->callback_enable_mask & (1 << UART_RX_FIFO_OVERRUN)) &&
			(module->callback_reg_mask & (1 << UART_RX_FIFO_OVERRUN))) {
			(module->callback[UART_RX_FIFO_OVERRUN])(module);
		}
		/* Flush */
		uint8_t flush = module->hw->RECEIVE_DATA.reg;
		UNUSED(flush);
	}
	if (flags & UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY) {
		_uart_read(module);
		if (module->remaining_rx_buffer_length == 0) {
			if ((module->callback_enable_mask & (1 << UART_RX_COMPLETE)) &&
				(module->callback_reg_mask & (1 << UART_RX_COMPLETE))) {
				module->status = STATUS_OK;
				module->hw->RX_INTERRUPT_MASK.reg &=
					~(UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
				(module->callback[UART_RX_COMPLETE])(module);
			}
		}
	}
}

static void uart_tx0_isr_handler(void)
{
	struct uart_module *module = _uart_instances[0];
	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->TRANSMIT_STATUS.reg;
	if (flags & UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL) {
		_uart_write(module);
		if (module->remaining_tx_buffer_length == 0) {
			module->hw->TX_INTERRUPT_MASK.reg &=
					~UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
			module->hw->TX_INTERRUPT_MASK.reg |=
					UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
		}
	}
	if (flags & UART_TRANSMIT_STATUS_TX_FIFO_EMPTY) {
		if ((module->callback_enable_mask & (1 << UART_TX_COMPLETE)) &&
			(module->callback_reg_mask & (1 << UART_TX_COMPLETE))) {
			module->status = STATUS_OK;
			/* Disable interrupt */
			module->hw->TX_INTERRUPT_MASK.reg &=
				~UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
			(module->callback[UART_TX_COMPLETE])(module);
		}

	}
	if (flags & UART_TRANSMIT_STATUS_CTS_ACTIVE) {
		if ((module->callback_enable_mask & (1 << UART_CTS_ACTIVE)) &&
			(module->callback_reg_mask & (1 << UART_CTS_ACTIVE))) {
			(module->callback[UART_CTS_ACTIVE])(module);
		}

	}
}

static void uart_rx1_isr_handler(void)
{
	struct uart_module *module = _uart_instances[1];
	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->RECEIVE_STATUS.reg;
	if (flags & UART_RECEIVE_STATUS_FIFO_OVERRUN) {
		/* Store the error code */
		module->status = STATUS_ERR_OVERFLOW;
		/* Disable interrupt */
		module->hw->RX_INTERRUPT_MASK.reg &=
			~(UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK |
			SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
		if ((module->callback_enable_mask & (1 << UART_RX_FIFO_OVERRUN)) &&
			(module->callback_reg_mask & (1 << UART_RX_FIFO_OVERRUN))) {
			(module->callback[UART_RX_FIFO_OVERRUN])(module);
		}
		/* Flush */
		uint8_t flush = module->hw->RECEIVE_DATA.reg;
		UNUSED(flush);
	}
	if (flags & UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY) {
		_uart_read(module);
		if (module->remaining_rx_buffer_length == 0) {
			if ((module->callback_enable_mask & (1 << UART_RX_COMPLETE)) &&
				(module->callback_reg_mask & (1 << UART_RX_COMPLETE))) {
				module->status = STATUS_OK;
				module->hw->RX_INTERRUPT_MASK.reg &=
					~(UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
				(module->callback[UART_RX_COMPLETE])(module);
			}
		}
	}
}

static void uart_tx1_isr_handler(void)
{
	struct uart_module *module = _uart_instances[1];
	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->TRANSMIT_STATUS.reg;
	if (flags & UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL) {
		_uart_write(module);
		if (module->remaining_tx_buffer_length == 0) {
			module->hw->TX_INTERRUPT_MASK.reg &=
					~UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
			module->hw->TX_INTERRUPT_MASK.reg |=
					UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
		}
	}
	if (flags & UART_TRANSMIT_STATUS_TX_FIFO_EMPTY) {
		if ((module->callback_enable_mask & (1 << UART_TX_COMPLETE)) &&
			(module->callback_reg_mask & (1 << UART_TX_COMPLETE))) {
			module->status = STATUS_OK;
			/* Disable interrupt */
			module->hw->TX_INTERRUPT_MASK.reg &=
				~UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
			(module->callback[UART_TX_COMPLETE])(module);
		}

	}
	if (flags & UART_TRANSMIT_STATUS_CTS_ACTIVE) {
		if ((module->callback_enable_mask & (1 << UART_CTS_ACTIVE)) &&
			(module->callback_reg_mask & (1 << UART_CTS_ACTIVE))) {
			(module->callback[UART_CTS_ACTIVE])(module);
		}

	}
}

static void uart_set_baudrate(struct uart_module *const module,
		const uint32_t baud_rate)
{
	uint32_t clock;
	uint16_t integerpart = 0;
	uint8_t fractionalpart = 0;
	uint32_t diff;
	uint8_t i = 0;

	clock = system_clock_get_value();
	integerpart = clock / baud_rate;
	diff = clock - (baud_rate * integerpart);
	i = 0;
	while(diff > (baud_rate / 16)) {
		i++;
		diff -= (baud_rate / 16);
	}
	fractionalpart = (i + 1) / 2;

	module->hw->UART_CLOCK_SOURCE.reg = UART_CLOCK_SOURCE_CLOCK_SELECT_0;
	module->hw->UART_BAUD_RATE.reg =
		UART_BAUD_RATE_INTEGER_DIVISION(integerpart) |
		UART_BAUD_RATE_FRACTIONAL_DIVISION(fractionalpart);
}

/**
 * \brief Gets the UART default configurations
 *
 * Use to initialize the configuration structure to known default values.
 *
 * The default configuration is as follows:
 * - Baudrate 115200
 * - parity   UART_NO_PARITY
 * - flow_control 0 - No Flow control
 * - stop_bits 1 - 1 stop bit
 * - pinmux_pad[] - Pinmux default are UART0.
 *
 * \param[out] config  Pointer to configuration structure to be initiated
 */
void uart_get_config_defaults(
		struct uart_config *const config)
{
	config->baud_rate = 115200;
	config->data_bits = UART_8_BITS;
	config->stop_bits = UART_1_STOP_BIT;
	config->parity = UART_NO_PARITY;
	config->flow_control = false;

	config->pin_number_pad[0] = PIN_LP_GPIO_2;
	config->pin_number_pad[1] = PIN_LP_GPIO_3;
	config->pin_number_pad[2] = PIN_LP_GPIO_4;
	config->pin_number_pad[3] = PIN_LP_GPIO_5;

	config->pinmux_sel_pad[0] = MUX_LP_GPIO_2_UART0_RXD;
	config->pinmux_sel_pad[1] = MUX_LP_GPIO_3_UART0_TXD;
	config->pinmux_sel_pad[2] = MUX_LP_GPIO_4_UART0_CTS;
	config->pinmux_sel_pad[3] = MUX_LP_GPIO_5_UART0_RTS;
}

/**
 * \brief Initializes the device
 *
 * Initializes the UART device based on the setting specified in the
 * configuration struct.
 *
 * \param[in]  module  enumeration UART hw module
 * \param[in]  hw      Pointer to USART hardware instance
 * \param[in]  config  Pointer to configuration struct
 *
 * \return Status of the initialization.
 *
 * \retval STATUS_OK                       The initialization was successful
 */
enum status_code uart_init(struct uart_module *const module, Uart * const hw,
		const struct uart_config *const config)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(hw);
	Assert(config);

	uint8_t config_temp = 0;
	uint8_t i,index;

	/* Assign module pointer to software instance struct */
	module->hw = hw;

	for (i = 0; i < UART_CALLBACK_N; i++) {
		module->callback[i] = NULL;
	}
	module->rx_buffer_ptr = NULL;
	module->tx_buffer_ptr = NULL;
	module->remaining_rx_buffer_length = 0;
	module->remaining_tx_buffer_length = 0;
	module->callback_reg_mask = 0;
	module->callback_enable_mask = 0;
	module->status = STATUS_OK;

	if (hw == UART0) {
		system_peripheral_reset(PERIPHERAL_UART0_CORE);
		system_peripheral_reset(PERIPHERAL_UART0_IF);
		system_clock_peripheral_enable(PERIPHERAL_UART0_CORE);
		system_clock_peripheral_enable(PERIPHERAL_UART0_IF);
		_uart_instances[0] = module;
		system_register_isr(RAM_ISR_TABLE_UARTRX0_INDEX, (uint32_t)uart_rx0_isr_handler);
		system_register_isr(RAM_ISR_TABLE_UARTTX0_INDEX, (uint32_t)uart_tx0_isr_handler);
		NVIC_EnableIRQ(UART0_RX_IRQn);
		NVIC_EnableIRQ(UART0_TX_IRQn);
	} else if (hw == UART1) {
		system_peripheral_reset(PERIPHERAL_UART1_CORE);
		system_peripheral_reset(PERIPHERAL_UART1_IF);
		system_clock_peripheral_enable(PERIPHERAL_UART1_CORE);
		system_clock_peripheral_enable(PERIPHERAL_UART1_IF);
		_uart_instances[1] = module;
		system_register_isr(RAM_ISR_TABLE_UARTRX1_INDEX, (uint32_t)uart_rx1_isr_handler);
		system_register_isr(RAM_ISR_TABLE_UARTTX1_INDEX, (uint32_t)uart_tx1_isr_handler);
		NVIC_EnableIRQ(UART1_RX_IRQn);
		NVIC_EnableIRQ(UART1_TX_IRQn);
	}

	/* Set the pinmux for this UART module. */
	if(config->flow_control) {
		index = 4;
	} else {
		index = 2;
	}

#if (BTLC1000)
    index = 2;  /* BTLC1000 has no flow control function. */
#endif

	for(i = 0; i < index; i++) {
		gpio_pinmux_cofiguration(config->pin_number_pad[i], \
								(uint16_t)(config->pinmux_sel_pad[i]));
	}

	/* empty UART FIFO */
	while (module->hw->RECEIVE_STATUS.reg & UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY) {
		i = module->hw->RECEIVE_DATA.reg;
	}
	
	/* reset configuration register */
	module->hw->UART_CONFIGURATION.reg = 0;

	/* program the uart configuration. */
	if(config->flow_control) {
		config_temp |= UART_CONFIGURATION_CTS_ENABLE_1;
	}
	config_temp |= config->data_bits;
	config_temp |= config->stop_bits;
	switch(config->parity) {
		case UART_NO_PARITY:
			config_temp |= UART_CONFIGURATION_PARITY_ENABLE_0;
			break;

		case UART_EVEN_PARITY:
			config_temp |= UART_CONFIGURATION_PARITY_ENABLE_1;
			config_temp |= UART_CONFIGURATION_PARITY_MODE_0;
			break;

		case UART_ODD_PARITY:
			config_temp |= UART_CONFIGURATION_PARITY_ENABLE_1;
			config_temp |= UART_CONFIGURATION_PARITY_MODE_1;
			break;

		case UART_SPACE_PARITY:
			config_temp |= UART_CONFIGURATION_PARITY_ENABLE_1;
			config_temp |= UART_CONFIGURATION_PARITY_MODE_2;
			break;

		case UART_MARK_PARITY:
			config_temp |= UART_CONFIGURATION_PARITY_ENABLE_1;
			config_temp |= UART_CONFIGURATION_PARITY_MODE_3;
			break;

		default:
			break;
	}	
	module->hw->UART_CONFIGURATION.reg = config_temp;

	/* Calculate the baud rate. */
	uart_set_baudrate(module, config->baud_rate);

	module->hw->RX_INTERRUPT_MASK.reg = 0;	// disable int at initialization, enable it at read time
	module->hw->TX_INTERRUPT_MASK.reg = 0;	// disable int at initialization, enable it at write time
	
	return STATUS_OK;
}

/**
* \brief Transmit a character via the UART
*
* This blocking function will transmit a single character via the
* UART.
*
* \param[in]  module  enumeration UART hw module
* \param[in]  tx_data  Data to transfer
*
* \return Status of the operation.
* \retval STATUS_OK         If the operation was completed
*/
enum status_code uart_write_wait(struct uart_module *const module,
		const uint8_t tx_data)
{
	while (!(module->hw->TRANSMIT_STATUS.reg & UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL));

	module->hw->TRANSMIT_DATA.reg = tx_data;
	
	return STATUS_OK;
}

/**
* \brief Receive a character via the UART
*
* This blocking function will receive a character via the UART.
*
* \param[in]   module  enumeration UART hw module
* \param[out]  rx_data  Pointer to received data
*
* \return Status of the operation.
* \retval STATUS_OK                If the operation was completed
*/
enum status_code uart_read_wait(struct uart_module *const module,
		uint8_t *const rx_data)
{
	while (!(module->hw->RECEIVE_STATUS.reg & UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY));

	*rx_data = module->hw->RECEIVE_DATA.reg;
	
	return STATUS_OK;
}

/**
* \brief Transmit a buffer of characters via the UART
*
* This blocking function will transmit a block of \c length characters
* via the UART.
*
* \note Using this function in combination with the interrupt (\c _job) functions is
*       not recommended as it has no functionality to check if there is an
*       ongoing interrupt driven operation running or not.
*
* \param[in]  module  enumeration UART hw module
* \param[in]  tx_data  Pointer to data to transmit
* \param[in]  length   Number of characters to transmit
* 
* \return Status of the operation.
* \retval STATUS_OK              If operation was completed
*/
enum status_code uart_write_buffer_wait(struct uart_module *const module, 
		const uint8_t *tx_data, uint32_t length)
{
	while(length--)
		uart_write_wait(module, *tx_data++);
	
	return STATUS_OK;
}

/**
 * \brief Receive a buffer of \c length characters via the UART
 *
 * This blocking function will receive a block of \c length characters
 * via the UART.
 *
 * \note Using this function in combination with the interrupt (\c *_job)
 *       functions is not recommended as it has no functionality to check if
 *       there is an ongoing interrupt driven operation running or not.
 *
 * \param[in]  module  enumeration UART hw module
 * \param[out] rx_data  Pointer to receive buffer
 * \param[in]  length   Number of characters to receive
 *
 * \return Status of the operation.
 * \retval STATUS_OK                If operation was completed
 */
enum status_code uart_read_buffer_wait(struct uart_module *const module,
		uint8_t *rx_data, uint16_t length)
{
	while(length--)
		uart_read_wait(module, rx_data++);
	
	return STATUS_OK;
}

/**
 * \internal
 * Starts write of a buffer with a given length
 *
 * \param[in]  module   Pointer to UART software instance struct
 * \param[in]  tx_data  Pointer to data to be transmitted
 * \param[in]  length   Length of data buffer
 *
 */
static void _uart_write_buffer(
		struct uart_module *const module,
		uint8_t *tx_data,
		uint16_t length)
{
	Assert(module);
	Assert(tx_data);

	/* Write parameters to the device instance */
	module->remaining_tx_buffer_length = length;
	module->tx_buffer_ptr = tx_data;
	module->status = STATUS_BUSY;

	module->hw->TX_INTERRUPT_MASK.reg = UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
}

/**
 * \internal
 * Setup UART to read a buffer with a given length
 *
 * \param[in]  module   Pointer to UART software instance struct
 * \param[in]  rx_data  Pointer to data to be received
 * \param[in]  length   Length of data buffer
 *
 */
static void _uart_read_buffer(
		struct uart_module *const module,
		uint8_t *rx_data,
		uint16_t length)
{
	Assert(module);
	Assert(rx_data);

	/* Set length for the buffer and the pointer, and let
	 * the interrupt handler do the rest */
	module->remaining_rx_buffer_length = length;
	module->rx_buffer_ptr = rx_data;
	module->status = STATUS_BUSY;

	module->hw->RX_INTERRUPT_MASK.reg = UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK;
}

/**
 * \brief Asynchronous buffer write
 *
 * Sets up the driver to write to the UART from a given buffer. If registered
 * and enabled, a callback function will be called when the write is finished.
 *
 * \param[in]  module   Pointer to UART software instance struct
 * \param[out] tx_data  Pointer to data buffer to receive
 * \param[in]  length   Data buffer length
 *
 * \returns Status of the write request operation.
 * \retval STATUS_OK               If the operation completed successfully
 * \retval STATUS_ERR_BUSY         If the UART was already busy with a write
 *                                 operation
 * \retval STATUS_ERR_INVALID_ARG  If requested write length was zero
 */
enum status_code uart_write_buffer_job(struct uart_module *const module,
		uint8_t *tx_data, uint32_t length)
{
	Assert(module);
	Assert(tx_data);

	if (length == 0) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Check if the UART is busy transmitting or slave waiting for TXC*/
	if (module->status == STATUS_BUSY) {
		return STATUS_BUSY;
	}

	/* Issue internal write */
	_uart_write_buffer(module, tx_data, length);

	return STATUS_OK;
}

/**
 * \brief Asynchronous buffer read
 *
 * Sets up the driver to read from the UART to a given buffer. If registered
 * and enabled, a callback function will be called when the read is finished.
 *
 * \note If address matching is enabled for the slave, the first character
 *       received and placed in the RX buffer will be the address.
 *
 * \param[in]  module   Pointer to UART software instance struct
 * \param[out] rx_data  Pointer to data buffer to receive
 * \param[in]  length   Data buffer length
 * \param[in]  dummy    Dummy character to send when reading in master mode
 *
 * \returns Status of the operation.
 * \retval  STATUS_OK               If the operation completed successfully
 * \retval  STATUS_ERR_BUSY         If the UART was already busy with a read
 *                                  operation
 * \retval  STATUS_ERR_DENIED       If the receiver is not enabled
 * \retval  STATUS_ERR_INVALID_ARG  If requested read length was zero
 */
enum status_code uart_read_buffer_job(struct uart_module *const module,
		uint8_t *rx_data, uint16_t length)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(rx_data);

	if (length == 0) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Check if the UART is busy transmitting or slave waiting for TXC*/
	if (module->status == STATUS_BUSY) {
		return STATUS_BUSY;
	}

	/* Issue internal read */
	_uart_read_buffer(module, rx_data, length);
	return STATUS_OK;
}

/**
 * \brief Registers a callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref uart_enable_callback,
 *       in order for the interrupt handler to call it when the conditions for
 *       the callback type are met.
 *
 * \param[in]  module         Pointer to UART software instance struct
 * \param[in]  callback_func  Pointer to callback function
 * \param[in]  callback_type  Callback type given by an enum
 *
 */
void uart_register_callback(struct uart_module *const module,
		uart_callback_t callback_func,
		enum uart_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	/* Register callback function */
	module->callback[callback_type] = callback_func;
	/* Set the bit corresponding to the callback_type */
	module->callback_reg_mask |= (1 << callback_type);
}

/**
 * \brief Unregisters a callback
 *
 * Unregisters a callback function which is implemented by the user.
 *
 * \param[in,out]  module         Pointer to UART software instance struct
 * \param[in]      callback_type  Callback type given by an enum
 *
 */
void uart_unregister_callback(struct uart_module *module,
		enum uart_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Unregister callback function */
	module->callback[callback_type] = NULL;
	/* Clear the bit corresponding to the callback_type */
	module->callback_reg_mask &= ~(1 << callback_type);
}

/**
 * \brief Enables callback
 *
 * Enables the callback function registered by the \ref usart_register_callback.
 * The callback function will be called from the interrupt handler when the
 * conditions for the callback type are met.
 *
 * \param[in]  module         Pointer to UART software instance struct
 * \param[in]  callback_type  Callback type given by an enum
 */
void uart_enable_callback(struct uart_module *const module,
		enum uart_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Enable callback */
	module->callback_enable_mask |= (1 << callback_type);

	if (callback_type == UART_CTS_ACTIVE) {
		module->hw->TX_INTERRUPT_MASK.reg |= UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK;
	}
}

/**
 * \brief Disable callback
 *
 * Disables the callback function registered by the \ref usart_register_callback,
 * and the callback will not be called from the interrupt routine.
 *
 * \param[in]  module         Pointer to UART software instance struct
 * \param[in]  callback_type  Callback type given by an enum
 */
void uart_disable_callback(struct uart_module *const module,
		enum uart_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Disable callback */
	module->callback_enable_mask &= ~(1 << callback_type);

	if (callback_type == UART_CTS_ACTIVE) {
		module->hw->TX_INTERRUPT_MASK.reg &= ~UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK;
	}

}

/**
 * \brief Enables UART transmit DMA
 *
 * \param[in]  module         Pointer to UART software instance struct
 */
void uart_enable_transmit_dma(struct uart_module *const module)
{
	/* Sanity check arguments */
	Assert(module);

	/* DMA need the interrupt signal to trigger */
	module->hw->TX_INTERRUPT_MASK.reg |= UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;

	/* Disable NVIC to avoid trigger the CPU interrupt */
	if (module->hw == UART0) {
		NVIC_DisableIRQ(UART0_TX_IRQn);
	} else if (module->hw == UART1) {
		NVIC_DisableIRQ(UART1_TX_IRQn);
	}
}

/**
 * \brief Disables UART transmit DMA
 *
 * \param[in]  module         Pointer to UART software instance struct
 */
void uart_disable_transmit_dma(struct uart_module *const module)
{
	/* Sanity check arguments */
	Assert(module);

	module->hw->TX_INTERRUPT_MASK.reg &= ~UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;

	/* Enable NVIC to restore the callback functions */
	if (module->hw == UART0) {
		NVIC_EnableIRQ(UART0_TX_IRQn);
	} else if (module->hw == UART1) {
		NVIC_EnableIRQ(UART1_TX_IRQn);
	}
}

/**
 * \brief Enables UART receive DMA
 *
 * \param[in]  module         Pointer to UART software instance struct
 */
void uart_enable_receive_dma(struct uart_module *const module)
{
	/* Sanity check arguments */
	Assert(module);

	/* DMA need the interrupt signal to trigger */
	module->hw->RX_INTERRUPT_MASK.reg |= UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK;

	/* Disable NVIC to avoid trigger the CPU interrupt */
	if (module->hw == UART0) {
		NVIC_DisableIRQ(UART0_TX_IRQn);
	} else if (module->hw == UART1) {
		NVIC_DisableIRQ(UART1_TX_IRQn);
	}
}

/**
 * \brief Disables UART receive DMA
 *
 * \param[in]  module         Pointer to UART software instance struct
 */
void uart_disable_receive_dma(struct uart_module *const module)
{
	/* Sanity check arguments */
	Assert(module);

	module->hw->RX_INTERRUPT_MASK.reg &= ~UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK;

	/* Enable NVIC to restore the callback functions */
	if (module->hw == UART0) {
		NVIC_EnableIRQ(UART0_TX_IRQn);
	} else if (module->hw == UART1) {
		NVIC_EnableIRQ(UART1_TX_IRQn);
	}
}

