/**
 * \file
 *
 * \brief I2C Slave Driver for SAMB
 *
 * Copyright (c) 2015-2016 Atmel Corporation. All rights reserved.
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

#ifndef I2C_SLAVE_H_INCLUDED
#define I2C_SLAVE_H_INCLUDED

#include "i2c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_samb_i2c_group
 *
 * @{
 *
 */

/**
 * \brief I<SUP>2</SUP>C slave packet for read/write
 *
 * Structure to be used when transferring I<SUP>2</SUP>C slave packets.
 */
struct i2c_slave_packet {
	/** Length of data array */
	uint16_t data_length;
	/** Data array containing all data to be transferred */
	uint8_t *data;
};

#if I2C_SLAVE_CALLBACK_MODE == true
 /**
 * \brief Callback types
 *
 * The available callback types for the I<SUP>2</SUP>C slave.
 */
enum i2c_slave_callback {
	/** Callback for packet write complete */
	I2C_SLAVE_CALLBACK_WRITE_COMPLETE,
	/** Callback for packet read complete */
	I2C_SLAVE_CALLBACK_READ_COMPLETE,
	/**
	 * Callback for read request from master - can be used to
	 * issue a write
	 */
	I2C_SLAVE_CALLBACK_READ_REQUEST,
	/**
	 * Callback for write request from master - can be used to issue a read
	 */
	I2C_SLAVE_CALLBACK_WRITE_REQUEST,
	/** Callback for error */
	I2C_SLAVE_CALLBACK_ERROR,
#  if !defined(__DOXYGEN__)
	/** Total number of callbacks */
	_I2C_SLAVE_CALLBACK_N,
#  endif
};

#  if !defined(__DOXYGEN__)
/** Software module prototype. */
struct i2c_slave_module;

/** Callback type. */
typedef void (*i2c_slave_callback_t)(
		struct i2c_slave_module *const module);
#  endif
#endif

/**
 * \brief Enum for the direction of a request
 *
 * Enum for the direction of a request.
 */
enum i2c_slave_direction {
	/** Read */
	I2C_SLAVE_DIRECTION_READ,
	/** Write */
	I2C_SLAVE_DIRECTION_WRITE,
	/** No direction */
	I2C_SLAVE_DIRECTION_NONE,
};

/**
 * \brief I<SUP>2</SUP>C Slave driver software device instance structure.
 *
 * I<SUP>2</SUP>C Slave driver software instance structure, used to
 * retain software state information of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct i2c_slave_module {
#if !defined(__DOXYGEN__)
	/** Hardware instance initialized for the struct */
	I2c *hw;
	/** Module lock */
	volatile bool locked;
	/** Timeout value for polled functions */
	uint16_t buffer_timeout;
#  if I2C_SLAVE_CALLBACK_MODE == true
	/** Pointers to callback functions */
	volatile i2c_slave_callback_t callbacks[_I2C_SLAVE_CALLBACK_N];
	/** Mask for registered callbacks */
	volatile uint8_t registered_callback;
	/** Mask for enabled callbacks */
	volatile uint8_t enabled_callback;
	/** The total number of bytes to transfer */
	volatile uint16_t buffer_length;
	/**
	 * Counter used for bytes left to send in write and to count number of
	 * obtained bytes in read
	 */
	uint16_t buffer_remaining;
	/** Data buffer for packet write and read */
	volatile uint8_t *buffer;
	/** Save direction of request from master. 1 = read, 0 = write. */
	volatile enum i2c_transfer_direction transfer_direction;
	/** Status for status read back in error callback */
	volatile enum status_code status;
#  endif
#endif
};

/**
 * \brief Configuration structure for the I<SUP>2</SUP>C Slave device
 *
 * This is the configuration structure for the I<SUP>2</SUP>C Slave device. It is used
 * as an argument for \ref i2c_slave_init to provide the desired
 * configurations for the module. The structure should be initialized using the
 * \ref i2c_slave_get_config_defaults.
 */
struct i2c_slave_config {
	/** Timeout to wait for master in polled functions */
	uint16_t buffer_timeout;
	/** Address or upper limit of address range */
	uint16_t address;
	/** CLOCK INPUT to use as clock source */
	enum i2c_clock_input clock_source;
	/** Divide ratio used to generate the sck clock */
	uint16_t clock_divider;
	/** PAD0 (SDA) pin number */
	uint32_t pin_number_pad0;
	/** PAD0 (SDA) pinmux selection */
	uint32_t pinmux_sel_pad0;
	/** PAD1 (SCL) pin numer */
	uint32_t pin_number_pad1;
	/** PAD1 (SCL) pinmux selection */
	uint32_t pinmux_sel_pad1;
};

/**
 * \name Configuration and Initialization
 * @{
 */

void i2c_slave_get_config_defaults(
		struct i2c_slave_config *const config);
enum status_code i2c_slave_init(struct i2c_slave_module *const module,
		I2c *const hw,
		const struct i2c_slave_config *const config);
enum status_code i2c_slave_write_packet_wait(
		struct i2c_slave_module *const module,
		struct i2c_slave_packet *const packet);
enum status_code i2c_slave_read_packet_wait(
		struct i2c_slave_module *const module,
		struct i2c_slave_packet *const packet);

/** @} */

/**
 * \name Status Management
 * @{
 */
uint32_t i2c_slave_get_status(
		struct i2c_slave_module *const module);
void i2c_slave_clear_status(
		struct i2c_slave_module *const module,
		uint32_t status_flags);
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* I2C_SLAVE_H_INCLUDED */
