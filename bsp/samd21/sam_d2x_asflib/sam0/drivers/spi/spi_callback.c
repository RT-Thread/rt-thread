/**
 * \file
 *
 * \brief Serial Peripheral Interface Driver for SAMB11
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
#include "spi_callback.h"

struct spi_module *_spi_instances[SPI_INST_NUM];

/**
 * \internal
 *
 * Dummy byte to send when reading in master mode.
 */
static uint16_t dummy_write;
static bool flag_direction_both[SPI_INST_NUM];

/**
 * \internal
 * Writes a character from the TX buffer to the Data register.
 *
 * \param[in,out]  module  Pointer to SPI software instance struct
 */
static void _spi_write(
		struct spi_module *const module)
{
	/* Pointer to the hardware module instance */
	Spi *const spi_hw = module->hw;

	/* Write value will be at least 8-bits long */
	uint16_t data_to_send = *(module->tx_buffer_ptr);
	/* Increment 8-bit pointer */
	(module->tx_buffer_ptr)++;

	/* Write the data to send*/
	spi_hw->TRANSMIT_DATA.reg = data_to_send & SPI_TRANSMIT_DATA_MASK;

	/* Decrement remaining buffer length */
	(module->remaining_tx_buffer_length)--;
}

/**
 * \internal
 * Reads a character from the Data register to the RX buffer.
 *
 * \param[in,out]  module  Pointer to SPI software instance struct
 */
static void _spi_read(
		struct spi_module *const module)
{
	/* Pointer to the hardware module instance */
	Spi *const spi_hw = module->hw;

	uint16_t received_data = (spi_hw->RECEIVE_DATA.reg & SPI_RECEIVE_DATA_MASK);

	/* Read value will be at least 8-bits long */
	*(module->rx_buffer_ptr) = received_data;
	/* Increment 8-bit pointer */
	module->rx_buffer_ptr += 1;

	/* Decrement length of the remaining buffer */
	module->remaining_rx_buffer_length--;
}

#if CONF_SPI_MASTER_ENABLE == true
/**
 * \internal
 * Writes a dummy character to the Data register.
 *
 * \param[in,out]  module  Pointer to SPI software instance struct
 */
static void _spi_write_dummy(
		struct spi_module *const module)
{
	/* Pointer to the hardware module instance */
	Spi *const spi_hw = module->hw;

	/* Write dummy byte */
	spi_hw->TRANSMIT_DATA.reg = dummy_write;

	/* Decrement remaining dummy buffer length */
	module->remaining_dummy_buffer_length--;
}
#endif

/**
 * \internal
 * Writes a dummy character from the to the Data register.
 *
 * \param[in,out]  module  Pointer to SPI software instance struct
 */
static void _spi_read_dummy(
		struct spi_module *const module)
{
	/* Pointer to the hardware module instance */
	Spi *const spi_hw = module->hw;
	uint16_t flush = 0;

	/* Read dummy byte */
	flush = spi_hw->RECEIVE_DATA.reg;
	UNUSED(flush);

	/* Decrement remaining dummy buffer length */
	module->remaining_dummy_buffer_length--;
}

void spi_rx0_isr_handler(void)
{
	struct spi_module *module = _spi_instances[0];

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->RECEIVE_STATUS.reg;
	flags &= module->hw->RX_INTERRUPT_MASK.reg;

	if (flags & SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY) {
		if (module->hw->RECEIVE_STATUS.reg & SPI_RECEIVE_STATUS_FIFO_OVERRUN) {
			if (module->dir != SPI_DIRECTION_WRITE) {
				/* Store the error code */
				module->status = STATUS_ERR_OVERFLOW;

				/* End transaction */
				module->dir = SPI_DIRECTION_IDLE;

				module->hw->RX_INTERRUPT_MASK.reg &=
					~(SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK |
					SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
				/* Run callback if registered and enabled */
				if ((module->enabled_callback & (1 << SPI_CALLBACK_ERROR)) &&
					(module->registered_callback & (1 << SPI_CALLBACK_ERROR))) {
					module->status = STATUS_ERR_OVERFLOW;
					module->hw->RX_INTERRUPT_MASK.reg &=
							~(SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK);
					(module->callback[SPI_CALLBACK_ERROR])(module);
				}
			}
			/* Flush */
			uint16_t flush = module->hw->RECEIVE_DATA.reg;
			UNUSED(flush);
		} else {
			if (module->dir == SPI_DIRECTION_WRITE) {
				/* Flush receive buffer when writing */
				_spi_read_dummy(module);
				if (module->remaining_dummy_buffer_length == 0) {
					module->hw->RX_INTERRUPT_MASK.reg &=
						~SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK;
					module->status = STATUS_OK;
					module->dir = SPI_DIRECTION_IDLE;
					///* Run callback if registered and enabled */
					//if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_TRANSMITTED)) &&
						//(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_TRANSMITTED))) {
						//(module->callback[SPI_CALLBACK_BUFFER_TRANSMITTED])(module);
					//}
				}
			} else {
				_spi_read(module);
				if (module->remaining_rx_buffer_length == 0) {
					if(module->dir == SPI_DIRECTION_READ) {
						if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_RECEIVED)) &&
							(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_RECEIVED))) {
							module->status = STATUS_OK;
							module->hw->RX_INTERRUPT_MASK.reg &=
									~(SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
							(module->callback[SPI_CALLBACK_BUFFER_RECEIVED])(module);
						}
					} else if (module->dir == SPI_DIRECTION_BOTH) {
						if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED)) &&
							(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED))) {
								module->hw->RX_INTERRUPT_MASK.reg &=
										~(SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
								if (flag_direction_both[0]) {
									module->status = STATUS_OK;
									flag_direction_both[0] = false;
									(module->callback[SPI_CALLBACK_BUFFER_TRANSCEIVED])(module);
								} else {
									flag_direction_both[0] = true;
								}
						}
					}
				}
			}
		}
	}
}

void spi_tx0_isr_handler(void)
{
	struct spi_module *module = _spi_instances[0];

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->TRANSMIT_STATUS.reg;
	flags &= module->hw->TX_INTERRUPT_MASK.reg;

	if (flags & SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1) {
#  if CONF_SPI_MASTER_ENABLE == true
		if ((module->mode == SPI_MODE_MASTER) &&
			(module->dir == SPI_DIRECTION_READ)) {
			/* Send dummy byte when reading in master mode */
			_spi_write_dummy(module);
			if (module->remaining_dummy_buffer_length == 0) {
				/* Disable the Data Register Empty Interrupt */
				module->hw->TX_INTERRUPT_MASK.reg &=
					~SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
			}
		}
#  endif
		if (0
#  if CONF_SPI_MASTER_ENABLE == true
		|| ((module->mode == SPI_MODE_MASTER) &&
		(module->dir != SPI_DIRECTION_READ))
#  endif
#  if CONF_SPI_SLAVE_ENABLE == true
		|| ((module->mode == SPI_MODE_SLAVE) &&
		(module->dir != SPI_DIRECTION_READ))
#  endif
		) {
			_spi_write(module);
			if (module->remaining_tx_buffer_length == 0) {
				module->hw->TX_INTERRUPT_MASK.reg &=
						~SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
				module->hw->TX_INTERRUPT_MASK.reg |=
						SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
			}
		}
	}
	if (flags & SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY) {
		if (module->dir == SPI_DIRECTION_WRITE) {
			if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_TRANSMITTED)) &&
				(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_TRANSMITTED))) {
					module->status = STATUS_OK;
					/* Disable interrupt */
					module->hw->TX_INTERRUPT_MASK.reg &=
							~SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
					(module->callback[SPI_CALLBACK_BUFFER_TRANSMITTED])(module);
				}
		} else if (module->dir == SPI_DIRECTION_BOTH) {
			if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED)) &&
				(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED))) {
					/* Disable interrupt */
					module->hw->TX_INTERRUPT_MASK.reg &=
							~SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
					if (flag_direction_both[0]) {
						module->status = STATUS_OK;
						flag_direction_both[0] = false;
						(module->callback[SPI_CALLBACK_BUFFER_TRANSCEIVED])(module);
					} else {
						flag_direction_both[0] = true;
					}
			}
		}
	}
}

void spi_rx1_isr_handler(void)
{
	struct spi_module *module = _spi_instances[1];

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->RECEIVE_STATUS.reg;
	flags &= module->hw->RX_INTERRUPT_MASK.reg;

	if (flags & SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY) {
		if (module->hw->RECEIVE_STATUS.reg & SPI_RECEIVE_STATUS_FIFO_OVERRUN) {
			if (module->dir != SPI_DIRECTION_WRITE) {
				/* Store the error code */
				module->status = STATUS_ERR_OVERFLOW;

				/* End transaction */
				module->dir = SPI_DIRECTION_IDLE;

				module->hw->RX_INTERRUPT_MASK.reg &=
						~(SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK |
						SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
				/* Run callback if registered and enabled */
				if ((module->enabled_callback & (1 << SPI_CALLBACK_ERROR)) &&
					(module->registered_callback & (1 << SPI_CALLBACK_ERROR))) {
					module->status = STATUS_ERR_OVERFLOW;
					module->hw->RX_INTERRUPT_MASK.reg &=
							~(SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK);
					(module->callback[SPI_CALLBACK_ERROR])(module);
				}
			}
			/* Flush */
			uint16_t flush = module->hw->RECEIVE_DATA.reg;
			UNUSED(flush);
		} else {
			if (module->dir == SPI_DIRECTION_WRITE) {
				/* Flush receive buffer when writing */
				_spi_read_dummy(module);
				if (module->remaining_dummy_buffer_length == 0) {
					module->hw->RX_INTERRUPT_MASK.reg &=
							~SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK;
					module->status = STATUS_OK;
					module->dir = SPI_DIRECTION_IDLE;
				}
			} else {
				_spi_read(module);
				if (module->remaining_rx_buffer_length == 0) {
					if(module->dir == SPI_DIRECTION_READ) {
						if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_RECEIVED)) &&
							(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_RECEIVED))) {
							module->status = STATUS_OK;
							module->hw->RX_INTERRUPT_MASK.reg &=
									~(SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
							(module->callback[SPI_CALLBACK_BUFFER_RECEIVED])(module);
						}
					} else if (module->dir == SPI_DIRECTION_BOTH) {
						if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED)) &&
							(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED))) {
							module->hw->RX_INTERRUPT_MASK.reg &=
									~(SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK);
							if (flag_direction_both[1]) {
								module->status = STATUS_OK;
								flag_direction_both[1] = false;
								(module->callback[SPI_CALLBACK_BUFFER_TRANSCEIVED])(module);
							} else {
								flag_direction_both[1] = true;
							}
						}
					}
				}
			}
		}
	}
}

void spi_tx1_isr_handler(void)
{
	struct spi_module *module = _spi_instances[1];

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->TRANSMIT_STATUS.reg;
	flags &= module->hw->TX_INTERRUPT_MASK.reg;

	if (flags & SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1) {
#  if CONF_SPI_MASTER_ENABLE == true
		if ((module->mode == SPI_MODE_MASTER) &&
		(module->dir == SPI_DIRECTION_READ)) {
			/* Send dummy byte when reading in master mode */
			_spi_write_dummy(module);
			if (module->remaining_dummy_buffer_length == 0) {
				/* Disable the Data Register Empty Interrupt */
				module->hw->TX_INTERRUPT_MASK.reg &=
				~SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
			}
		}
#  endif
		if (0
#  if CONF_SPI_MASTER_ENABLE == true
		|| ((module->mode == SPI_MODE_MASTER) &&
		(module->dir != SPI_DIRECTION_READ))
#  endif
#  if CONF_SPI_SLAVE_ENABLE == true
		|| ((module->mode == SPI_MODE_SLAVE) &&
		(module->dir != SPI_DIRECTION_READ))
#  endif
		) {
			_spi_write(module);
			if (module->remaining_tx_buffer_length == 0) {
				module->hw->TX_INTERRUPT_MASK.reg &=
						~SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
				module->hw->TX_INTERRUPT_MASK.reg |=
				SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
			}
		}
	}
	if (flags & SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY) {
		if (module->dir == SPI_DIRECTION_WRITE) {
			if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_TRANSMITTED)) &&
			(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_TRANSMITTED))) {
				module->status = STATUS_OK;
				/* Disable interrupt */
				module->hw->TX_INTERRUPT_MASK.reg &=
						~SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
				(module->callback[SPI_CALLBACK_BUFFER_TRANSMITTED])(module);
			}
		} else if (module->dir == SPI_DIRECTION_BOTH) {
			if ((module->enabled_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED)) &&
				(module->registered_callback & (1 << SPI_CALLBACK_BUFFER_TRANSCEIVED))) {
				/* Disable interrupt */
				module->hw->TX_INTERRUPT_MASK.reg &=
						~SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
				if (flag_direction_both[1]) {
					module->status = STATUS_OK;
					flag_direction_both[1] = false;
					(module->callback[SPI_CALLBACK_BUFFER_TRANSCEIVED])(module);
				} else {
					flag_direction_both[1] = true;
				}
			}
		}
	}
}

/**
 * \brief Registers a SPI callback function
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref spi_enable_callback, in order
 *       for the interrupt handler to call it when the conditions for the
 *       callback type are met.
 *
 * \param[in]  module         Pointer to SPI software instance struct
 * \param[in]  callback_func  Pointer to callback function
 * \param[in]  callback_type  Callback type given by an enum
 *
 */
void spi_register_callback(
		struct spi_module *const module,
		spi_callback_t callback_func,
		enum spi_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	/* Register callback function */
	module->callback[callback_type] = callback_func;

	/* Set the bit corresponding to the callback_type */
	module->registered_callback |= (1 << callback_type);
}

/**
 * \brief Unregisters a SPI callback function
 *
 * Unregisters a callback function which is implemented by the user.
 *
 * \param[in] module         Pointer to SPI software instance struct
 * \param[in] callback_type  Callback type given by an enum
 *
 */
void spi_unregister_callback(
		struct spi_module *const module,
		enum spi_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Unregister callback function */
	module->callback[callback_type] = NULL;

	/* Clear the bit corresponding to the callback_type */
	module->registered_callback &= ~(1 << callback_type);
}

/**
 * \brief Enables callback
 *
 * Enables the callback function registered by the \ref spi_register_callback.
 * The callback function will be called from the interrupt handler when the
 * conditions for the callback type are met.
 *
 * \param[in]  module         Pointer to SPI software instance struct
 * \param[in]  callback_type  Callback type given by an enum
 */
void spi_enable_callback(struct spi_module *const module,
		enum spi_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Enable callback */
	module->enabled_callback |= (1 << callback_type);
}

/**
 * \brief Disables callback
 *
 * Disables the callback function registered by the \ref spi_register_callback.
 * The callback function will not be called from the interrupt handler.
 *
 * \param[in]  module         Pointer to SPI software instance struct
 * \param[in]  callback_type  Callback type given by an enum
 */
void spi_disable_callback(struct spi_module *const module,
		enum spi_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Enable callback */
	module->enabled_callback &= ~(1 << callback_type);
}

/**
 * \internal
 * Starts write of a buffer with a given length
 *
 * \param[in]  module   Pointer to SPI software instance struct
 * \param[in]  tx_data  Pointer to data to be transmitted
 * \param[in]  length   Length of data buffer
 *
 */
static void _spi_write_buffer(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint16_t length)
{
	Assert(module);
	Assert(tx_data);

	/* Write parameters to the device instance */
	module->remaining_tx_buffer_length = length;
	module->remaining_dummy_buffer_length = length;
	module->tx_buffer_ptr = tx_data;
	module->status = STATUS_BUSY;

	module->dir = SPI_DIRECTION_WRITE;

	/* Get a pointer to the hardware module instance */
	Spi *const hw = module->hw;

	hw->TX_INTERRUPT_MASK.reg = SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
}

/**
 * \internal
 * Setup SPI to read a buffer with a given length
 *
 * \param[in]  module   Pointer to SPI software instance struct
 * \param[in]  rx_data  Pointer to data to be received
 * \param[in]  length   Length of data buffer
 *
 */
static void _spi_read_buffer(
		struct spi_module *const module,
		uint8_t *rx_data,
		uint16_t length)
{
	Assert(module);
	Assert(rx_data);

	/* Set length for the buffer and the pointer, and let
	 * the interrupt handler do the rest */
	module->remaining_rx_buffer_length = length;
	module->remaining_dummy_buffer_length = length;
	module->rx_buffer_ptr = rx_data;
	module->status = STATUS_BUSY;

	module->dir = SPI_DIRECTION_READ;

	/* Get a pointer to the hardware module instance */
	Spi *const hw = module->hw;

	hw->RX_INTERRUPT_MASK.reg = SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK;

#if CONF_SPI_MASTER_ENABLE == true
	hw->TX_INTERRUPT_MASK.reg = SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
#endif
}

/**
 * \internal
 * Starts transceive of buffers with a given length
 *
 * \param[in]  module   Pointer to SPI software instance struct
 * \param[in]  rx_data  Pointer to data to be received
 * \param[in]  tx_data  Pointer to data to be transmitted
 * \param[in]  length   Length of data buffer
 *
 */
static void _spi_transceive_buffer(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint8_t *rx_data,
		uint16_t length)
{
	Assert(module);
	Assert(tx_data);

	/* Write parameters to the device instance */
	module->remaining_tx_buffer_length = length;
	module->remaining_rx_buffer_length = length;
	module->rx_buffer_ptr = rx_data;
	module->tx_buffer_ptr = tx_data;
	module->status = STATUS_BUSY;

	module->dir = SPI_DIRECTION_BOTH;

	if (module->hw == SPI0) {
		flag_direction_both[0] = false;
	} else if (module->hw == SPI1) {
		flag_direction_both[1] = false;
	}

	/* Get a pointer to the hardware module instance */
	Spi *const hw = module->hw;

	/* Enable the Data Register Empty and RX Complete Interrupt */
	hw->TX_INTERRUPT_MASK.reg = SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK;
	hw->RX_INTERRUPT_MASK.reg = SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK;
}

/**
 * \brief Asynchronous buffer write
 *
 * Sets up the driver to write to the SPI from a given buffer. If registered
 * and enabled, a callback function will be called when the write is finished.
 *
 * \param[in]  module   Pointer to SPI software instance struct
 * \param[out] tx_data  Pointer to data buffer to receive
 * \param[in]  length   Data buffer length
 *
 * \returns Status of the write request operation.
 * \retval STATUS_OK               If the operation completed successfully
 * \retval STATUS_ERR_BUSY         If the SPI was already busy with a write
 *                                 operation
 * \retval STATUS_ERR_INVALID_ARG  If requested write length was zero
 */
enum status_code spi_write_buffer_job(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint16_t length)
{
	Assert(module);
	Assert(tx_data);

	if (length == 0) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Check if the SPI is busy transmitting or slave waiting for TXC*/
	if (module->status == STATUS_BUSY) {
		return STATUS_BUSY;
	}

	/* Issue internal write */
	_spi_write_buffer(module, tx_data, length);

	return STATUS_OK;
}

/**
 * \brief Asynchronous buffer read
 *
 * Sets up the driver to read from the SPI to a given buffer. If registered
 * and enabled, a callback function will be called when the read is finished.
 *
 * \note If address matching is enabled for the slave, the first character
 *       received and placed in the RX buffer will be the address.
 *
 * \param[in]  module   Pointer to SPI software instance struct
 * \param[out] rx_data  Pointer to data buffer to receive
 * \param[in]  length   Data buffer length
 * \param[in]  dummy    Dummy character to send when reading in master mode
 *
 * \returns Status of the operation.
 * \retval  STATUS_OK               If the operation completed successfully
 * \retval  STATUS_ERR_BUSY         If the SPI was already busy with a read
 *                                  operation
 * \retval  STATUS_ERR_DENIED       If the receiver is not enabled
 * \retval  STATUS_ERR_INVALID_ARG  If requested read length was zero
 */
enum status_code spi_read_buffer_job(
		struct spi_module *const module,
		uint8_t *rx_data,
		uint16_t length,
		uint16_t dummy)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(rx_data);

	if (length == 0) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Check if the SPI is busy transmitting or slave waiting for TXC*/
	if (module->status == STATUS_BUSY) {
		return STATUS_BUSY;
	}

	dummy_write = dummy;
	/* Issue internal read */
	_spi_read_buffer(module, rx_data, length);
	return STATUS_OK;
}

/**
 * \brief Asynchronous buffer write and read
 *
 * Sets up the driver to write and read to and from given buffers. If registered
 * and enabled, a callback function will be called when the transfer is finished.
 *
 * \note If address matching is enabled for the slave, the first character
 *       received and placed in the RX buffer will be the address.
 *
 * \param[in]  module   Pointer to SPI software instance struct
 * \param[in] tx_data   Pointer to data buffer to send
 * \param[out] rx_data  Pointer to data buffer to receive
 * \param[in]  length   Data buffer length
 *
 * \returns Status of the operation.
 * \retval  STATUS_OK               If the operation completed successfully
 * \retval  STATUS_ERR_BUSY         If the SPI was already busy with a read
 *                                  operation
 * \retval  STATUS_ERR_DENIED       If the receiver is not enabled
 * \retval  STATUS_ERR_INVALID_ARG  If requested read length was zero
 */
enum status_code spi_transceive_buffer_job(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint8_t *rx_data,
		uint16_t length)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(rx_data);

	if (length == 0) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Check if the SPI is busy transmitting or slave waiting for TXC*/
	if (module->status == STATUS_BUSY) {
		return STATUS_BUSY;
	}

	/* Issue internal transceive */
	_spi_transceive_buffer(module, tx_data, rx_data, length);

	return STATUS_OK;
}
