/**
 * \file
 *
 * \brief I2C Master Driver for SAMB
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

#include "i2c_master.h"
#if I2C_MASTER_CALLBACK_MODE == true
#  include "i2c_master_interrupt.h"
#endif

/**
 * \brief Gets the I<SUP>2</SUP>C master default configurations
 *
 * Use to initialize the configuration structure to known default values.
 *
 * The default configuration is as follows:
 * - Baudrate 100KHz
 * - Clock sourc I2C_CLK_INPUT_3
 * - Clock divider = 0x10
 * - Pinmux pad0 PINMUX_LP_GPIO_8_MUX2_I2C0_SDA
 * - Pinmux pad1 PINMUX_LP_GPIO_9_MUX2_I2C0_SCK
 *
 * \param[out] config  Pointer to configuration structure to be initiated
 */
void i2c_master_get_config_defaults(
		struct i2c_master_config *const config)
{
	/* Sanity check */
	Assert(config);
	
	config->clock_source    = I2C_CLK_INPUT_3;
	config->clock_divider   = 0x10;
	config->pin_number_pad0 = PIN_LP_GPIO_8;
	config->pin_number_pad1 = PIN_LP_GPIO_9;
	config->pinmux_sel_pad0 = MUX_LP_GPIO_8_I2C0_SDA;
	config->pinmux_sel_pad1 = MUX_LP_GPIO_9_I2C0_SCL;
}

#if !defined(__DOXYGEN__)
/**
 * \internal Sets configurations to module
 *
 * \param[out] module  Pointer to software module structure
 * \param[in]  config  Configuration structure with configurations to set
 *
 */
static void _i2c_master_set_config(
		struct i2c_master_module *const module,
		const struct i2c_master_config *const config)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(config);

	I2c *const i2c_module = (module->hw);

	/* Set the pinmux for this i2c module. */
	gpio_pinmux_cofiguration(config->pin_number_pad0, (uint16_t)(config->pinmux_sel_pad0));
	gpio_pinmux_cofiguration(config->pin_number_pad1, (uint16_t)(config->pinmux_sel_pad1));
	/* Set clock. */
	i2c_module->CLOCK_SOURCE_SELECT.reg = config->clock_source;
	i2c_module->I2C_CLK_DIVIDER.reg = I2C_CLK_DIVIDER_I2C_DIVIDE_RATIO(config->clock_divider);
	/* Enable master mode. */
	i2c_module->I2C_MASTER_MODE.reg = I2C_MASTER_MODE_MASTER_ENABLE_1;
}
#endif /* __DOXYGEN__ */

/**
 * \brief Initializes the requested I<SUP>2</SUP>C hardware module
 *
 * Initializes the I<SUP>2</SUP>C master device requested and sets the provided
 * software module struct. Run this function before any further use of
 * the driver.
 *
 * \param[out] module  Pointer to software module struct
 * \param[in]  config  Pointer to the configuration struct
 *
 * \return Status of initialization.
 * \retval STATUS_OK                        Module initiated correctly
 * \retval STATUS_ERR_INVALID_ARG           Invalid argument in module or config structure.
 * \retval STATUS_ERR_ALREADY_INITIALIZED   If the Pinmux is not a valid one for I2C signals.
 *
 */
enum status_code i2c_master_init(
		struct i2c_master_module *const module,
		I2c *const hw,
		const struct i2c_master_config *const config)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(config);
	
	module->hw = hw;

	/* Sanity check arguments. */
	if ((module == NULL) || (config == NULL))
		return STATUS_ERR_INVALID_ARG;

	i2c_disable(module->hw);
	if (module->hw == I2C0) {
		system_peripheral_reset(PERIPHERAL_I2C0_CORE);
	} else if (module->hw == I2C1) {
		system_peripheral_reset(PERIPHERAL_I2C1_CORE);
	} else {
		return STATUS_ERR_INVALID_ARG;
	}

#if I2C_MASTER_CALLBACK_MODE == true
	/* Initialize values in module. */
	module->registered_callback = 0;
	module->enabled_callback    = 0;
	module->buffer_length       = 0;
	module->buffer_remaining    = 0;
	module->status              = STATUS_OK;
	module->buffer              = NULL;

	_i2c_instances = (void*)module;
	if (module->hw == I2C0) {
		system_register_isr(RAM_ISR_TABLE_I2CRX0_INDEX, (uint32_t)_i2c_master_isr_handler);
		system_register_isr(RAM_ISR_TABLE_I2CTX0_INDEX, (uint32_t)_i2c_master_isr_handler);
		NVIC_EnableIRQ(I2C0_RX_IRQn);
		NVIC_EnableIRQ(I2C0_TX_IRQn);
	} else if (module->hw == I2C1) {
		system_register_isr(RAM_ISR_TABLE_I2CRX1_INDEX, (uint32_t)_i2c_master_isr_handler);
		system_register_isr(RAM_ISR_TABLE_I2CTX1_INDEX, (uint32_t)_i2c_master_isr_handler);
		NVIC_EnableIRQ(I2C1_RX_IRQn);
		NVIC_EnableIRQ(I2C1_TX_IRQn);
	}
#endif

	/* Set config and return status. */
	_i2c_master_set_config(module, config);

	return STATUS_OK;
}

/**
 * \internal
 * Starts blocking read operation.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of reading packet.
 * \retval STATUS_OK                    The packet was read successfully
 * \retval STATUS_ERR_TIMEOUT           If no response was given within
 *                                      specified timeout period
 * \retval STATUS_ERR_DENIED            If error on bus
 * \retval STATUS_ERR_PACKET_COLLISION  If arbitration is lost
 * \retval STATUS_ERR_BAD_ADDRESS       If slave is busy, or no slave
 *                                      acknowledged the address
 */
static enum status_code _i2c_master_read_packet(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(config);
	
	uint16_t counter = 0;
	uint32_t status  = 0;
	I2c *const i2c_module    = (module->hw);
	uint16_t length = packet->data_length;

	if (length == 0) {
		return STATUS_ERR_INVALID_ARG;
	}

	i2c_wait_for_idle(i2c_module);

	/* Flush the FIFO */
	i2c_module->I2C_FLUSH.reg = 1;

	/* Enable I2C on bus (start condition). */
	i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_1;
	/* Address I2C slave in case of Master mode enabled. */
	i2c_module->TRANSMIT_DATA.reg = I2C_TRANSMIT_DATA_ADDRESS_FLAG_1 |
			(packet->address << 1) | I2C_TRANSFER_READ;

	/* Now check whether the core has sent the data out and free the bus. */
	while (!(status & I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY)) {
		status = i2c_module->TRANSMIT_STATUS.reg;
	}

	do {
		/* Send stop condition. */
		if ((!module->no_stop) && (counter == (length - 1))) {
			i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_0;
		}

		status = i2c_module->RECEIVE_STATUS.reg;
		if (status & I2C_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY)
			packet->data[counter++] = i2c_module->RECEIVE_DATA.reg;
	} while (counter < length);

	return STATUS_OK;
}

/**
 * \brief Reads data packet from slave
 *
 * Reads a data packet from the specified slave address on the I<SUP>2</SUP>C
 * bus and sends a stop condition when finished.
 *
 * \note This will stall the device from any other operation. For
 *       interrupt-driven operation, see \ref i2c_master_read_packet_job.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of reading packet.
 * \retval STATUS_OK                    The packet was read successfully
 * \retval STATUS_ERR_INVALID_ARG       Invalid argument in module or config strucuture
 *                                      specified timeout period
 * \retval STATUS_BUSY                  If module has a pending request.
 */
enum status_code i2c_master_read_packet_wait(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	if((module == NULL) || (packet == NULL))
		return STATUS_ERR_INVALID_ARG;

#if I2C_MASTER_CALLBACK_MODE == true
	/* Check if the I2C module is busy with a job. */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}
#endif

	module->no_stop = false;

	return _i2c_master_read_packet(module, packet);
}

/**
 * \brief Reads data packet from slave without sending a stop condition when done
 *
 * Reads a data packet from the specified slave address on the I<SUP>2</SUP>C
 * bus without sending a stop condition when done, thus retaining ownership of
 * the bus when done. To end the transaction, a
 * \ref i2c_master_read_packet_wait "read" or
 * \ref i2c_master_write_packet_wait "write" with stop condition must be
 * performed.
 *
 * \note This will stall the device from any other operation. For
 *       interrupt-driven operation, see \ref i2c_master_read_packet_job.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of reading packet.
 * \retval STATUS_OK                    The packet was read successfully
 * \retval STATUS_ERR_INVALID_ARG       Invalid argument in module or config strucuture
 *                                      specified timeout period
 * \retval STATUS_BUSY                  If module has a pending request.
 */
enum status_code i2c_master_read_packet_wait_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	if((module == NULL) || (packet == NULL))
		return STATUS_ERR_INVALID_ARG;

#if I2C_MASTER_CALLBACK_MODE == true
	/* Check if the I2C module is busy with a job. */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}
#endif

	module->no_stop = true;

	return _i2c_master_read_packet(module, packet);
}

/**
 * \internal
 * Starts blocking write operation.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of write packet.
 * \retval STATUS_OK                    The packet was write successfully
 */
static enum status_code _i2c_master_write_packet(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);
	
	I2c *const i2c_module = (module->hw);
	uint16_t counter = 0;
	uint32_t status  = 0;

	uint16_t length = packet->data_length;

	i2c_wait_for_idle(i2c_module);

	/* Flush the FIFO */
	i2c_module->I2C_FLUSH.reg = 1;

	/* Enable I2C on bus (start condition) */
	i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_1;

	/* Address I2C slave in case of Master mode enabled */
	i2c_module->TRANSMIT_DATA.reg = I2C_TRANSMIT_DATA_ADDRESS_FLAG_1 | 
			((packet->address) << 1) | I2C_TRANSFER_WRITE;
	do {
		status = i2c_module->TRANSMIT_STATUS.reg;
		if (status & I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk) {
			i2c_module->TRANSMIT_DATA.reg = packet->data[counter++];
		}
	} while (counter < length); 

	/* Now check whether the core has sent the data out and free the bus */
	while (!(status & I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY)) {
			status = i2c_module->TRANSMIT_STATUS.reg;
	}

	/* Send stop condition */
	if (!module->no_stop) {
		i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_0;
	}

	return STATUS_OK;
}

/**
 * \brief Writes data packet to slave
 *
 * Writes a data packet to the specified slave address on the I<SUP>2</SUP>C bus
 * and sends a stop condition when finished.
 *
 * \note This will stall the device from any other operation. For
 *       interrupt-driven operation, see \ref i2c_master_read_packet_job.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of write packet.
 * \retval STATUS_OK                    The packet was written successfully
 * \retval STATUS_ERR_INVALID_ARG       Invalid argument in module or packet structure
 *                                      specified timeout period
 * \retval STATUS_BUSY                  If module has a pending request.
 */
enum status_code i2c_master_write_packet_wait(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check arguments. */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	if ((module == NULL) || (packet == NULL)) {
		return STATUS_ERR_INVALID_ARG;
	}
#if I2C_MASTER_CALLBACK_MODE == true
	/* Check if the I2C module is busy with a job. */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}
#endif

	module->no_stop = false;

	return _i2c_master_write_packet(module, packet);
}

/**
 * \brief Writes data packet to slave without sending a stop condition when done
 *
 * Writes a data packet to the specified slave address on the I<SUP>2</SUP>C bus
 * without sending a stop condition, thus retaining ownership of the bus when
 * done. To end the transaction, a \ref i2c_master_read_packet_wait "read" or
 * \ref i2c_master_write_packet_wait "write" with stop condition or sending a
 * stop with the \ref i2c_master_send_stop function must be performed.
 *
 * \note This will stall the device from any other operation. For
 *       interrupt-driven operation, see \ref i2c_master_read_packet_job.
 *
 * \param[in,out] module  Pointer to software module struct
 * \param[in,out] packet  Pointer to I<SUP>2</SUP>C packet to transfer
 *
 * \return Status of write packet.
 * \retval STATUS_OK                    The packet was written successfully
 * \retval STATUS_ERR_INVALID_ARG       Invalid argument in module or config structure
 *                                      specified timeout period
 * \retval STATUS_BUSY                  If module has a pending request.
 */
enum status_code i2c_master_write_packet_wait_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	Assert(packet);

	if((module == NULL) || (packet == NULL)) {
		return STATUS_ERR_INVALID_ARG;
	}
#if I2C_MASTER_CALLBACK_MODE == true
	/* Check if the I2C module is busy with a job */
	if (module->buffer_remaining > 0) {
		return STATUS_BUSY;
	}
#endif

	module->no_stop = true;

	return _i2c_master_write_packet(module, packet);
}

/**
 * \brief Sends stop condition on bus
 *
 * Sends a stop condition on bus.
 *
 * \note This function can only be used after the
 *       \ref i2c_master_write_packet_wait_no_stop function. If a stop condition
 *       is to be sent after a read, the \ref i2c_master_read_packet_wait
 *       function must be used.
 *
 * \param[in,out] module  Pointer to the software instance struct
 */
void i2c_master_send_stop(struct i2c_master_module *const module)
{
	/* Sanity check */
	Assert(module);
	Assert(module->hw);
	
	I2c *const i2c_module = (module->hw);

	/* Send stop command */
	i2c_wait_for_idle(i2c_module);

	i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_0;
}

/**
 * \brief Sends start condition on bus
 *
 * Sends a start condition on bus.
 *
 * \note This function can only be used after the
 * \ref i2c_master_write_packet_wait_no_stop function. If a stop condition
 * is to be sent after a read, the \ref i2c_master_read_packet_wait
 * function must be used.
 *
 * \param[in,out] module  Pointer to the software instance struct
 */
void i2c_master_send_start(struct i2c_master_module *const module)
{
	I2c *const i2c_module = (module->hw);

	i2c_wait_for_idle(i2c_module);

	/* Send start command */
	i2c_module->I2C_ONBUS.reg = I2C_ONBUS_ONBUS_ENABLE_1;
}

/**
 * \brief Reads one byte data from slave
 *
 * \param[in,out]  module  Pointer to software module struct
 * \param[out]     byte    Read one byte data to slave
 *
 * \return Status of reading byte.
 * \retval STATUS_OK                    The packet was read successfully
 */
enum status_code i2c_master_read_byte(
		struct i2c_master_module *const module,
		uint8_t *byte)
{
	I2c *const i2c_module = (module->hw);

	/* Read a byte from slave. */
	i2c_wait_for_idle(i2c_module);

	*byte = i2c_module->RECEIVE_DATA.bit.RX_BYTE;

	return STATUS_OK;
}

/**
 * \brief Write Address & command to slave
 *
 * \param[in,out]  module  Pointer to software module struct
 * \param[in]      byte    Address of slave
 * \param[in]      byte    command 0 - Write, 1 - Read
 *
 * \return Status of writing byte.
 * \retval STATUS_OK   The Address and command was written successfully
 */
enum status_code i2c_master_write_address(
		struct i2c_master_module *const module,
		uint8_t address,
		uint8_t command)
{
	I2c *const i2c_module = (module->hw);

	/* Write byte to slave. */
	i2c_wait_for_idle(i2c_module);

	i2c_module->TRANSMIT_DATA.reg = I2C_TRANSMIT_DATA_ADDRESS_FLAG_1 | 
			(address << 1) | command;

	return STATUS_OK;
}


/**
 * \brief Write one byte data to slave
 *
 * \param[in,out]  module  Pointer to software module struct
 * \param[in]      byte    Send one byte data to slave
 *
 * \return Status of writing byte.
 * \retval STATUS_OK   One byte was written successfully
 */
enum status_code i2c_master_write_byte(
		struct i2c_master_module *const module,
		uint8_t byte)
{
	I2c *const i2c_module = (module->hw);

	/* Write byte to slave. */
	i2c_wait_for_idle(i2c_module);

	i2c_module->TRANSMIT_DATA.reg = (uint16_t)I2C_TRANSMIT_DATA_TX_DATA(byte);

	return STATUS_OK;
}
