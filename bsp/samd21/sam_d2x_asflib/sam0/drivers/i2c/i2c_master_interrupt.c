/**
 * \file
 *
 * \brief I2C Master Interrupt Driver for SAMB
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

#include "i2c_master_interrupt.h"

void *_i2c_instances;

/**
 * \internal
 * Read next data. Used by interrupt handler to get next data byte from slave.
 *
 * \param[in,out] module  Pointer to software module structure
 */
static void _i2c_master_read(
		struct i2c_master_module *const module)
{
	/* Sanity check arguments. */
	Assert(module);
	Assert(module->hw);

	I2c *const i2c_module = module->hw;

	/* Find index to save next value in buffer */
	uint16_t buffer_index = module->buffer_length - module->buffer_remaining;

	module->buffer_remaining--;

	module->buffer[buffer_index] = i2c_module->RECEIVE_DATA.reg;
}

/**
 * \internal
 *
 * Write next data. Used by interrupt handler to send next data byte to slave.
 *
 * \param[in,out] module  Pointer to software module structure
 */
static void _i2c_master_write(struct i2c_master_module *const module)
{
	/* Sanity check arguments. */
	Assert(module);
	Assert(module->hw);

	I2c *const i2c_module = module->hw;

	/* Find index to get next byte in buffer */
	volatile uint16_t buffer_index = module->buffer_length - module->buffer_remaining;

	module->buffer_remaining--;

	/* Write byte from buffer to slave */
	i2c_module->TRANSMIT_DATA.reg = module->buffer[buffer_index];
	
	if (module->buffer_remaining <= 0) {
		i2c_module->TX_INTERRUPT_MASK.reg = I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;
	}
}


/**
 * \brief Registers callback for the specified callback type
 *
 * Associates the given callback function with the
 * specified callback type.
 *
 * To enable the callback, the \ref i2c_master_enable_callback function
 * must be used.
 *
 * \param[in,out]  module         Pointer to the software module struct
 * \param[in]      callback       Pointer to the function desired for the
 *                                specified callback
 * \param[in]      callback_type  Callback type to register
 */
void i2c_master_register_callback(
		struct i2c_master_module *const module,
		const i2c_master_callback_t callback,
		enum i2c_master_callback callback_type)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(callback);

	/* Register callback */
	module->callbacks[callback_type] = callback;

	/* Set corresponding bit to set callback as registered */
	module->registered_callback |= (1 << callback_type);
}

/**
 * \brief Unregisters callback for the specified callback type
 *
 * When called, the currently registered callback for the given callback type
 * will be removed.
 *
 * \param[in,out] module         Pointer to the software module struct
 * \param[in]     callback_type  Specifies the callback type to unregister
 */
void i2c_master_unregister_callback(
		struct i2c_master_module *const module,
		enum i2c_master_callback callback_type)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	
	/* Register callback */
	module->callbacks[callback_type] = NULL;

	/* Clear corresponding bit to set callback as unregistered */
	module->registered_callback &= ~(1 << callback_type);
}

/**
 * \internal
 * Starts a read packet operation.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of starting reading I<SUP>2</SUP>C packet.
 * \retval STATUS_OK    If reading was started successfully
 * \retval STATUS_BUSY  If module is currently busy with another transfer
 */
static enum status_code _i2c_master_read_packet(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	I2c *const i2c_module = module->hw;

	/* Save packet to software module */
	module->buffer             = packet->data;
	module->buffer_remaining   = packet->data_length;
	module->transfer_direction = I2C_TRANSFER_READ;
	module->status             = STATUS_BUSY;
	
	i2c_wait_for_idle(i2c_module);
	/* Flush the FIFO */
	i2c_module->I2C_FLUSH.reg = 1;
	/* Enable I2C on bus (start condition) */
	i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_1;
	/* Set address and direction bit. Will send start command on bus */
	i2c_module->TRANSMIT_DATA.reg = I2C_TRANSMIT_DATA_ADDRESS_FLAG_1 |
			(packet->address << 1) | module->transfer_direction;
	/* Enable interrupts */
	i2c_module->RX_INTERRUPT_MASK.reg = I2C_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK;
	
	return STATUS_OK;
}

/**
 * \brief Initiates a read packet operation
 *
 * Reads a data packet from the specified slave address on the I<SUP>2</SUP>C
 * bus. This is the non-blocking equivalent of \ref i2c_master_read_packet_wait.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of starting reading I<SUP>2</SUP>C packet.
 * \retval STATUS_OK    If reading was started successfully
 * \retval STATUS_BUSY  If module is currently busy with another transfer
 */
enum status_code i2c_master_read_packet_job(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	/* Check if the I2C module is busy with a job */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}

	/* Make sure we send STOP */
	module->no_stop = false;
	/* Start reading */
	return _i2c_master_read_packet(module, packet);
}

/**
 * \brief Initiates a read packet operation without sending a STOP condition when done
 *
 * Reads a data packet from the specified slave address on the I<SUP>2</SUP>C bus without
 * sending a stop condition, thus retaining ownership of the bus when done.
 * To end the transaction, a \ref i2c_master_read_packet_wait "read" or
 * \ref i2c_master_write_packet_wait "write" with stop condition must be
 * performed.
 *
 * This is the non-blocking equivalent of \ref i2c_master_read_packet_wait_no_stop.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of starting reading I<SUP>2</SUP>C packet.
 * \retval STATUS_OK   If reading was started successfully
 * \retval STATUS_BUSY If module is currently busy with another operation
 */
enum status_code i2c_master_read_packet_job_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	/* Check if the I2C module is busy with a job */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}

	/* Make sure we don't send STOP */
	module->no_stop = true;
	/* Start reading */
	return _i2c_master_read_packet(module, packet);
}


/**
 * \internal Initiates a write packet operation
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of starting writing I<SUP>2</SUP>C packet job.
 * \retval STATUS_OK   If writing was started successfully
 * \retval STATUS_BUSY If module is currently busy with another transfer
 */
static enum status_code _i2c_master_write_packet(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	I2c *const i2c_module = module->hw;

	/* Save packet to software module */
	module->buffer             = packet->data;
	module->buffer_remaining   = packet->data_length;
	module->transfer_direction = I2C_TRANSFER_WRITE;
	module->status             = STATUS_BUSY;

	/* Enable I2C on bus (start condition) */
	i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_1;
	/* Set address and direction bit, will send start command on bus */
	i2c_module->TRANSMIT_DATA.reg = I2C_TRANSMIT_DATA_ADDRESS_FLAG_1 |
			(packet->address << 1) | module->transfer_direction;
	/* Enable interrupts */
	i2c_module->TX_INTERRUPT_MASK.reg = I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK;

	return STATUS_OK;
}

/**
 * \brief Initiates a write packet operation
 *
 * Writes a data packet to the specified slave address on the I<SUP>2</SUP>C
 * bus. This is the non-blocking equivalent of \ref i2c_master_write_packet_wait.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of starting writing I<SUP>2</SUP>C packet job.
 * \retval STATUS_OK    If writing was started successfully
 * \retval STATUS_BUSY  If module is currently busy with another transfer
 */
enum status_code i2c_master_write_packet_job(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	/* Check if the I2C module is busy with another job. */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}

	/* Make sure we send STOP at end*/
	module->no_stop = false;
	/* Start write operation */
	return _i2c_master_write_packet(module, packet);
}

/**
 * \brief Initiates a write packet operation without sending a STOP condition when done
 *
 * Writes a data packet to the specified slave address on the I<SUP>2</SUP>C bus
 * without sending a stop condition, thus retaining ownership of the bus when
 * done. To end the transaction, a \ref i2c_master_read_packet_wait "read" or
 * \ref i2c_master_write_packet_wait "write" with stop condition or sending
 * a stop with the \ref i2c_master_send_stop function must be performed.
 *
 * This is the non-blocking equivalent of \ref i2c_master_write_packet_wait_no_stop.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of starting writing I<SUP>2</SUP>C packet job.
 * \retval STATUS_OK    If writing was started successfully
 * \retval STATUS_BUSY  If module is currently busy with another
 */
enum status_code i2c_master_write_packet_job_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	/* Check if the I2C module is busy with another job. */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}

	/* Do not send stop condition when done */
	module->no_stop = true;
	/* Start write operation */
	return _i2c_master_write_packet(module, packet);
}

/**
 * Interrupt handler for I<SUP>2</SUP>C master.
 */
void _i2c_master_isr_handler(void)
{
	/* Get software module for callback handling */
	struct i2c_master_module *module =
			(struct i2c_master_module*)_i2c_instances;

	Assert(module);

	I2c *const i2c_module = module->hw;

	/* Combine callback registered and enabled masks */
	uint8_t callback_mask = module->enabled_callback &
			module->registered_callback;

	if ((module->buffer_length <= 0) && (module->buffer_remaining > 0)) {
		module->buffer_length = module->buffer_remaining;
	/* Check if buffer write is done */
	} else if ((module->buffer_length > 0) && (module->buffer_remaining <= 0) &&
			(module->status == STATUS_BUSY) &&
			(module->transfer_direction == I2C_TRANSFER_WRITE)) {
		/* Disable write interrupt flag */
		i2c_module->TX_INTERRUPT_MASK.reg = 0;

		module->buffer_length = 0;
		module->status        = STATUS_OK;

		if (!module->no_stop) {
			/* Send stop condition */
			i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_0;
		} 

		if (callback_mask & (1 << I2C_MASTER_CALLBACK_WRITE_COMPLETE)) {
			module->callbacks[I2C_MASTER_CALLBACK_WRITE_COMPLETE](module);
		}

	/* Continue buffer write/read */
	} else if ((module->buffer_length > 0) && (module->buffer_remaining > 0)){
		if (module->transfer_direction == I2C_TRANSFER_WRITE) {
			_i2c_master_write(module);
		} else {
			_i2c_master_read(module);
		}
	}

	/* Check if read buffer transfer is complete */
	if ((module->buffer_length > 0) && (module->buffer_remaining <= 0) &&
			(module->status == STATUS_BUSY) &&
			(module->transfer_direction == I2C_TRANSFER_READ)) {
		/* Disable read interrupt flag */
		i2c_module->RX_INTERRUPT_MASK.reg = 0;

		module->buffer_length = 0;
		module->status        = STATUS_OK;

		if (!module->no_stop) {
			/* Send stop condition */
			i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_0;
		}
		
		if ((callback_mask & (1 << I2C_MASTER_CALLBACK_READ_COMPLETE))
				&& (module->transfer_direction == I2C_TRANSFER_READ)) {
			module->callbacks[I2C_MASTER_CALLBACK_READ_COMPLETE](module);
		}
	}
	if (module->transfer_direction == I2C_TRANSFER_READ) {
		if (module->hw == I2C0) {
			NVIC_ClearPendingIRQ(I2C0_RX_IRQn);
		} else if (module->hw == I2C1) {
			NVIC_ClearPendingIRQ(I2C1_RX_IRQn);
		} 
	} else {
		if (module->hw == I2C0) {
			NVIC_ClearPendingIRQ(I2C0_TX_IRQn);
		} else if (module->hw == I2C1) {
			NVIC_ClearPendingIRQ(I2C1_TX_IRQn);
		}
	}
}
