/**
 * \file
 *
 * \brief I/O I2C related functionality implementation.
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
#include <hal_i2c_m_sync.h>
#include <utils.h>
#include <utils_assert.h>

/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

/**
 * \brief Sync version of I2C I/O read
 */
static int32_t i2c_m_sync_read(struct io_descriptor *io, uint8_t *buf, const uint16_t n)
{
	struct i2c_m_sync_desc *i2c = CONTAINER_OF(io, struct i2c_m_sync_desc, io);
	struct _i2c_m_msg       msg;
	int32_t                 ret;

	msg.addr   = i2c->slave_addr;
	msg.len    = n;
	msg.flags  = I2C_M_STOP | I2C_M_RD;
	msg.buffer = buf;

	ret = _i2c_m_sync_transfer(&i2c->device, &msg);

	if (ret) {
		return ret;
	}

	return n;
}

/**
 * \brief Sync version of I2C I/O write
 */
static int32_t i2c_m_sync_write(struct io_descriptor *io, const uint8_t *buf, const uint16_t n)
{
	struct i2c_m_sync_desc *i2c = CONTAINER_OF(io, struct i2c_m_sync_desc, io);
	struct _i2c_m_msg       msg;
	int32_t                 ret;

	msg.addr   = i2c->slave_addr;
	msg.len    = n;
	msg.flags  = I2C_M_STOP;
	msg.buffer = (uint8_t *)buf;

	ret = _i2c_m_sync_transfer(&i2c->device, &msg);

	if (ret) {
		return ret;
	}

	return n;
}

/**
 * \brief Sync version of i2c initialize
 */
int32_t i2c_m_sync_init(struct i2c_m_sync_desc *i2c, void *hw)
{
	int32_t init_status;
	ASSERT(i2c);

	init_status = _i2c_m_sync_init(&i2c->device, hw);
	if (init_status) {
		return init_status;
	}

	/* Init I/O */
	i2c->io.read  = i2c_m_sync_read;
	i2c->io.write = i2c_m_sync_write;

	return ERR_NONE;
}

/**
 * \brief deinitialize
 */
int32_t i2c_m_sync_deinit(struct i2c_m_sync_desc *i2c)
{
	int32_t status;
	ASSERT(i2c);

	status = _i2c_m_sync_deinit(&i2c->device);
	if (status) {
		return status;
	}

	i2c->io.read  = NULL;
	i2c->io.write = NULL;

	return ERR_NONE;
}

/**
 * \brief Sync version of i2c enable
 */
int32_t i2c_m_sync_enable(struct i2c_m_sync_desc *i2c)
{
	return _i2c_m_sync_enable(&i2c->device);
}

/**
 * \brief Sync version of i2c disable
 */
int32_t i2c_m_sync_disable(struct i2c_m_sync_desc *i2c)
{
	return _i2c_m_sync_disable(&i2c->device);
}

/**
 * \brief Sync version of i2c set slave address
 */
int32_t i2c_m_sync_set_slaveaddr(struct i2c_m_sync_desc *i2c, int16_t addr, int32_t addr_len)
{
	return i2c->slave_addr = (addr & 0x3ff) | (addr_len & I2C_M_TEN);
}

/**
 * \brief Sync version of i2c set baudrate
 */
int32_t i2c_m_sync_set_baudrate(struct i2c_m_sync_desc *i2c, uint32_t clkrate, uint32_t baudrate)
{
	return _i2c_m_sync_set_baudrate(&i2c->device, clkrate, baudrate);
}

/**
 * \brief Sync version of i2c write command
 */
int32_t i2c_m_sync_cmd_write(struct i2c_m_sync_desc *i2c, uint8_t reg, uint8_t *buffer, uint8_t length)
{
	struct _i2c_m_msg msg;
	int32_t           ret;

	msg.addr   = i2c->slave_addr;
	msg.len    = 1;
	msg.flags  = 0;
	msg.buffer = &reg;

	ret = _i2c_m_sync_transfer(&i2c->device, &msg);

	if (ret != 0) {
		/* error occurred */
		return ret;
	}

	msg.flags  = I2C_M_STOP;
	msg.buffer = buffer;
	msg.len    = length;

	ret = _i2c_m_sync_transfer(&i2c->device, &msg);

	if (ret != 0) {
		/* error occurred */
		return ret;
	}

	return ERR_NONE;
}

/**
 * \brief Sync version of i2c read command
 */
int32_t i2c_m_sync_cmd_read(struct i2c_m_sync_desc *i2c, uint8_t reg, uint8_t *buffer, uint8_t length)
{
	struct _i2c_m_msg msg;
	int32_t           ret;

	msg.addr   = i2c->slave_addr;
	msg.len    = 1;
	msg.flags  = 0;
	msg.buffer = &reg;

	ret = _i2c_m_sync_transfer(&i2c->device, &msg);

	if (ret != 0) {
		/* error occurred */
		return ret;
	}

	msg.flags  = I2C_M_STOP | I2C_M_RD;
	msg.buffer = buffer;
	msg.len    = length;

	ret = _i2c_m_sync_transfer(&i2c->device, &msg);

	if (ret != 0) {
		/* error occurred */
		return ret;
	}

	return ERR_NONE;
}

/**
 * \brief Sync version of i2c transfer command
 */
int32_t i2c_m_sync_transfer(struct i2c_m_sync_desc *const i2c, struct _i2c_m_msg *msg)
{
	return _i2c_m_sync_transfer(&i2c->device, msg);
}

/**
 * \brief Sync version of i2c send stop condition command
 */
int32_t i2c_m_sync_send_stop(struct i2c_m_sync_desc *const i2c)
{
	return _i2c_m_sync_send_stop(&i2c->device);
}

/**
 * \brief Retrieve I/O descriptor
 */
int32_t i2c_m_sync_get_io_descriptor(struct i2c_m_sync_desc *const i2c, struct io_descriptor **io)
{
	*io = &i2c->io;
	return ERR_NONE;
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t i2c_m_sync_get_version(void)
{
	return DRIVER_VERSION;
}
