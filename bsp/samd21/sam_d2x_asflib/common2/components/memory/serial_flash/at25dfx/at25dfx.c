/**
 * \file
 *
 * \brief AT25DFx SerialFlash driver implementation.
 *
 * Copyright (C) 2013-2015 Atmel Corporation. All rights reserved.
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

#include "at25dfx.h"

/** SerialFlash command opcodes */
enum at25dfx_command_opcode {
	AT25DFX_COMMAND_PROGRAM_PAGE         = 0x02,
	AT25DFX_COMMAND_READ_STATUS          = 0x05,
	AT25DFX_COMMAND_READ_ARRAY           = 0x0b,
	AT25DFX_COMMAND_READ_DEVICE_ID       = 0x9f,
	AT25DFX_COMMAND_WRITE_ENABLE         = 0x06,
	AT25DFX_COMMAND_WRITE_DISABLE        = 0x04,
	AT25DFX_COMMAND_ERASE_CHIP           = 0xc7,
	AT25DFX_COMMAND_ERASE_BLOCK_4KB      = 0x20,
	AT25DFX_COMMAND_ERASE_BLOCK_32KB     = 0x52,
	AT25DFX_COMMAND_ERASE_BLOCK_64KB     = 0xd8,
	AT25DFX_COMMAND_WRITE_STATUS         = 0x01,
	AT25DFX_COMMAND_PROTECT_SECTOR       = 0x36,
	AT25DFX_COMMAND_UNPROTECT_SECTOR     = 0x39,
	AT25DFX_COMMAND_READ_PROTECT_SECTOR  = 0x3c,
	AT25DFX_COMMAND_SLEEP                = 0xb9,
	AT25DFX_COMMAND_WAKE                 = 0xab,
};

/** AT25DFx page size in bytes */
#define AT25DFX_PAGE_SIZE         256
/** Maximum length of a SerialFlash command */
#define AT25DFX_COMMAND_MAX_SIZE  (1 + 3 + 2)

/** SerialFlash status bits */
enum at25dfx_status_field {
	// These two are read-fields
	AT25DFX_STATUS_BUSY            = (1 << 0),
	AT25DFX_STATUS_ERROR           = (1 << 5),
	// This is a write-field
	AT25DFX_STATUS_GLOBAL_PROTECT  = (0x0f << 2),
};

/** SerialFlash command container */
struct at25dfx_command {
	/** Opcode to send */
	enum at25dfx_command_opcode opcode;
	/** Size: opcode byte (1) [+ address bytes (3)] [+ dummy bytes (N)] */
	uint8_t command_size;
	/** SerialFlash address to operate on */
	at25dfx_address_t address;
	/** Buffer to read from/write to */
	union {
		const uint8_t *tx;
		uint8_t *rx;
	} data;
	/** Number of bytes to read/write */
	at25dfx_datalen_t length;
};

//! \name SerialFlash chip info helpers
//@{

/**
 * \brief Get the device ID of a specific SerialFlash type.
 *
 * \param[in] type Type of SerialFlash.
 *
 * \return SerialFlash device ID.
 */
static inline uint32_t _at25dfx_get_device_id(enum at25dfx_type type)
{
	switch (type) {
	case AT25DFX_512B:
		return 0x00651f;

	case AT25DFX_021:
		return 0x00431f;

	case AT25DFX_041A:
		return 0x01441f;

	case AT25DFX_081:
		return 0x02451f;

	case AT25DFX_081A:
		return 0x01451f;

	case AT25DFX_161:
		return 0x02461f;

	case AT25DFX_L161:
		return 0x03461f;

	case AT25DFX_Q161:
		return 0x00861f;

	case AT25DFX_321A:
		return 0x01471f;

	case AT25DFX_641:
		return 0x00481f;

	default:
		Assert(false);
		return 0;
	}
}

/**
 * \brief Get the storage size of a specific SerialFlash type.
 *
 * \param[in] type Type of SerialFlash.
 *
 * \return SerialFlash storage size.
 */
static inline uint32_t _at25dfx_get_device_size(enum at25dfx_type type)
{
	switch (type) {
	case AT25DFX_512B:
		return 64 * 1024UL;

	case AT25DFX_021:
		return 256 * 1024UL;

	case AT25DFX_041A:
		return 512 * 1024UL;

	case AT25DFX_081:
	case AT25DFX_081A:
		return 1024 * 1024UL;

	case AT25DFX_161:
	case AT25DFX_L161:
	case AT25DFX_Q161:
		return 2048 * 1024UL;

	case AT25DFX_321A:
		return 4096 * 1024UL;

	case AT25DFX_641:
		return 8192 * 1024UL;

	default:
		Assert(false);
		return 0;
	}
}

//@}

//! \name Private chip helpers
//@{

/**
 * \brief Select the chip
 *
 * This function selects the specified chip by driving its CS line low.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 */
static inline void _at25dfx_chip_select(struct at25dfx_chip_module *chip)
{
	port_pin_set_output_level(chip->cs_pin, false);
}

/**
 * \brief Deselect the chip
 *
 * This function deselects the specified chip by driving its CS line high.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 */
static inline void _at25dfx_chip_deselect(struct at25dfx_chip_module *chip)
{
	port_pin_set_output_level(chip->cs_pin, true);
}

#include <at25dfx_priv_hal.h>

/**
 * \brief Issue command to enable writing
 *
 * This function issues the command that enables operations which change the
 * SerialFlash content or operation, i.e., programming, erasing and protecting
 * or unprotecting sectors.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 */
static inline void _at25dfx_chip_enable_write(struct at25dfx_chip_module *chip)
{
	struct at25dfx_command cmd;

	cmd.opcode = AT25DFX_COMMAND_WRITE_ENABLE;
	cmd.command_size = 1;
	cmd.length = 0;

	// Init to avoid warnings with -Os
	cmd.address = (at25dfx_address_t)NULL;
	cmd.data.tx = NULL;

	_at25dfx_chip_issue_write_command_wait(chip, cmd);
}

//@}

/**
 * \brief Check presence of chip
 *
 * This function checks whether or not the SerialFlash device is present by
 * attempting to read out its device ID, and comparing it with the one that
 * its type should have.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 *
 * \return Status of operation.
 * \retval STATUS_OK if chip responded with ID matching its type.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 * \retval STATUS_ERR_NOT_FOUND if chip did not respond, or with wrong ID.
 */
enum status_code at25dfx_chip_check_presence(struct at25dfx_chip_module *chip)
{
	enum status_code status;
	struct at25dfx_command cmd;
	uint32_t id = 0;

	Assert(chip);

	// Reserve the SPI for us
	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	cmd.opcode = AT25DFX_COMMAND_READ_DEVICE_ID;
	cmd.command_size = 1;
	cmd.data.rx = (uint8_t *)&id;
	cmd.length = 3;

	// Init to avoid warnings with -Os
	cmd.address = (at25dfx_address_t)NULL;

	_at25dfx_chip_issue_read_command_wait(chip, cmd);

	_at25dfx_spi_unlock(chip->spi);

	if (id == _at25dfx_get_device_id(chip->type)) {
		return STATUS_OK;
	} else {
		return STATUS_ERR_NOT_FOUND;
	}
}

/**
 * \brief Read data from chip
 *
 * This function reads data from the SerialFlash device, into a buffer.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 * \param[in] address SerialFlash internal address to start reading from.
 * \param[out] data Buffer to write data into.
 * \param[in] length Number of bytes to read.
 *
 * \return Status of operation.
 * \retval STATUS_OK if operation succeeded.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 * \retval STATUS_ERR_INVALID_ARG if address and/or length is out of bounds.
 */
enum status_code at25dfx_chip_read_buffer(struct at25dfx_chip_module *chip,
		at25dfx_address_t address, void *data, at25dfx_datalen_t length)
{
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);
	Assert(data);
	Assert(length);

	// Address out of range?
	if ((address + length) > _at25dfx_get_device_size(chip->type)) {
		return STATUS_ERR_INVALID_ARG;
	}

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	cmd.opcode = AT25DFX_COMMAND_READ_ARRAY;
	cmd.command_size = 5;
	cmd.address = address;
	cmd.data.rx = (uint8_t *)data;
	cmd.length = length;
	_at25dfx_chip_issue_read_command_wait(chip, cmd);

	_at25dfx_spi_unlock(chip->spi);

	return STATUS_OK;
}

/**
 * \brief Write data to chip
 *
 * This function writes data to the SerialFlash device, from a buffer.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 * \param[in] address SerialFlash internal address to start writing to.
 * \param[in] data Buffer to read data from.
 * \param[in] length Number of bytes to write.
 *
 * \return Status of operation.
 * \retval STATUS_OK if operation succeeded.
 * \retval STATUS_ERR_IO if operation failed.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 * \retval STATUS_ERR_INVALID_ARG if address and/or length is out of bounds.
 */
enum status_code at25dfx_chip_write_buffer(struct at25dfx_chip_module *chip,
		at25dfx_address_t address, const void *data, at25dfx_datalen_t length)
{
	at25dfx_datalen_t page_bytes;
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);
	Assert(data);
	Assert(length);

	if ((address + length) > _at25dfx_get_device_size(chip->type)) {
		return STATUS_ERR_INVALID_ARG;
	}

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	_at25dfx_chip_enable_write(chip);

	cmd.opcode = AT25DFX_COMMAND_PROGRAM_PAGE;
	cmd.command_size = 4;
	cmd.address = address;
	cmd.data.tx = (uint8_t *)data;
	page_bytes = AT25DFX_PAGE_SIZE - (address % AT25DFX_PAGE_SIZE);
	cmd.length = min(page_bytes, length);
	_at25dfx_chip_issue_write_command_wait(chip, cmd);

	status = _at25dfx_chip_get_nonbusy_status(chip);

	length -= cmd.length;

	while (length && (status == STATUS_OK)) {
		_at25dfx_chip_enable_write(chip);

		cmd.address += cmd.length;
		cmd.data.tx += cmd.length;
		cmd.length = min(AT25DFX_PAGE_SIZE, length);

		_at25dfx_chip_issue_write_command_wait(chip, cmd);

		status = _at25dfx_chip_get_nonbusy_status(chip);

		length -= cmd.length;
	}

	_at25dfx_spi_unlock(chip->spi);

	return status;
}

/**
 * \brief Erase chip
 *
 * This function erases all content of the SerialFlash device.
 *
 * \pre All sectors must be unprotected prior to a chip erase, or it will not be
 * performed.
 *
 * \sa at25dfx_chip_set_global_sector_protect()
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 *
 * \return Status of operation.
 * \retval STATUS_OK if operation succeeded.
 * \retval STATUS_ERR_IO if operation failed.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 */
enum status_code at25dfx_chip_erase(struct at25dfx_chip_module *chip)
{
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	_at25dfx_chip_enable_write(chip);

	cmd.opcode = AT25DFX_COMMAND_ERASE_CHIP;
	cmd.command_size = 1;
	cmd.length = 0;

	// Init to avoid warnings with -Os
	cmd.address = (at25dfx_address_t)NULL;
	cmd.data.tx = NULL;

	_at25dfx_chip_issue_write_command_wait(chip, cmd);

	status = _at25dfx_chip_get_nonbusy_status(chip);

	_at25dfx_spi_unlock(chip->spi);

	return status;
}

/**
 * \brief Erase block
 *
 * This function erases all content within a block of the SerialFlash device.
 *
 * \pre The sector(s) which the block resides in must be unprotected prior to a
 * block erase, or it will not be performed.
 *
 * \sa at25dfx_chip_set_sector_protect()
 *
 * \note The alignment of the erase blocks is given by the erase block size. The
 * SerialFlash device will simply ignore address bits which index within the
 * block. For example, doing a 4 kB block erase with the start address set to
 * the 2 kB boundary will cause the first 4 kB to get erased, not 4 kB starting
 * at the 2 kB boundary.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 * \param[in] address Address within the block to erase.
 * \param[in] block_size Size of block to erase.
 *
 * \return Status of operation.
 * \retval STATUS_OK if operation succeeded.
 * \retval STATUS_ERR_IO if operation failed.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 * \retval STATUS_ERR_INVALID_ARG if address is out of bounds.
 */
enum status_code at25dfx_chip_erase_block(struct at25dfx_chip_module *chip,
		at25dfx_address_t address, enum at25dfx_block_size block_size)
{
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);

	if (address >= _at25dfx_get_device_size(chip->type)) {
		return STATUS_ERR_INVALID_ARG;
	}

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	_at25dfx_chip_enable_write(chip);

	switch (block_size) {
	case AT25DFX_BLOCK_SIZE_4KB:
		cmd.opcode = AT25DFX_COMMAND_ERASE_BLOCK_4KB;
		break;

	case AT25DFX_BLOCK_SIZE_32KB:
		cmd.opcode = AT25DFX_COMMAND_ERASE_BLOCK_32KB;
		break;

	case AT25DFX_BLOCK_SIZE_64KB:
		cmd.opcode = AT25DFX_COMMAND_ERASE_BLOCK_64KB;
		break;

	default:
		Assert(false);
		cmd.opcode = (enum at25dfx_command_opcode)0;
	}
	cmd.command_size = 4;
	cmd.address = address;
	cmd.length = 0;

	// Init to avoid warnings with -Os
	cmd.data.tx = NULL;

	_at25dfx_chip_issue_write_command_wait(chip, cmd);

	status = _at25dfx_chip_get_nonbusy_status(chip);

	_at25dfx_spi_unlock(chip->spi);

	return status;
}

/**
 * \brief Set sector protection globally
 *
 * This function applies a protect setting to all sectors.
 *
 * \note Global setting of sector protection is done by writing to the status
 * register of the device.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 * \param[in] bool Protection setting to apply.
 * \arg \c true if the sectors should be protected.
 * \arg \c false if the sectors should be unprotected.
 *
 * \return Status of operation.
 * \retval STATUS_OK if write operation succeeded.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 */
enum status_code at25dfx_chip_set_global_sector_protect(
		struct at25dfx_chip_module *chip, bool protect)
{
	enum status_code status;
	struct at25dfx_command cmd;
	uint8_t temp_data;

	Assert(chip);

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	_at25dfx_chip_enable_write(chip);

	temp_data = protect ? AT25DFX_STATUS_GLOBAL_PROTECT : 0;
	cmd.opcode = AT25DFX_COMMAND_WRITE_STATUS;
	cmd.command_size = 1;
	cmd.length = 1;
	cmd.data.tx = &temp_data;

	// Init to avoid warnings with -Os
	cmd.address = (at25dfx_address_t)NULL;

	_at25dfx_chip_issue_write_command_wait(chip, cmd);

	_at25dfx_spi_unlock(chip->spi);

	return STATUS_OK;
}

/**
 * \brief Set protection setting of a single sector
 *
 * This function applies a protect setting to a single sector.
 *
 * \note The granularity of the sectors for protection can vary between
 * SerialFlash devices and is not necessarily uniform. Please refer to the
 * datasheet for details.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 * \param[in] address Address within sector to protect.
 * \param[in] bool Protection setting to apply.
 * \arg \c true if the sector should be protected.
 * \arg \c false if the sector should be unprotected.
 *
 * \return Status of operation.
 * \retval STATUS_OK if write operation succeeded.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 * \retval STATUS_ERR_INVALID_ARG if address is out of bounds.
 */
enum status_code at25dfx_chip_set_sector_protect(
		struct at25dfx_chip_module *chip, at25dfx_address_t address,
		bool protect)
{
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);

	if ((address) >= _at25dfx_get_device_size(chip->type)) {
		return STATUS_ERR_INVALID_ARG;
	}

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	_at25dfx_chip_enable_write(chip);

	cmd.opcode = protect ?
			AT25DFX_COMMAND_PROTECT_SECTOR : AT25DFX_COMMAND_UNPROTECT_SECTOR;
	cmd.command_size = 4;
	cmd.address = address;
	cmd.length = 0;

	// Init to avoid warnings with -Os
	cmd.data.tx = NULL;

	_at25dfx_chip_issue_write_command_wait(chip, cmd);

	_at25dfx_spi_unlock(chip->spi);

	return STATUS_OK;
}

/**
 * \brief Get protection setting of a single sector
 *
 * This function gets the protect setting of a single sector.
 *
 * \sa at25dfx_chip_set_sector_protect()
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 * \param[in] address Address within sector to get setting of.
 * \param[out] bool Address of variable to store the setting to.
 *
 * \return Status of operation.
 * \retval STATUS_OK if operation succeeded.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 * \retval STATUS_ERR_INVALID_ARG if address is out of bounds.
 */
enum status_code at25dfx_chip_get_sector_protect(
		struct at25dfx_chip_module *chip, at25dfx_address_t address,
		bool *protect)
{
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);

	if ((address) >= _at25dfx_get_device_size(chip->type)) {
		return STATUS_ERR_INVALID_ARG;
	}

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	cmd.opcode = AT25DFX_COMMAND_READ_PROTECT_SECTOR;
	cmd.command_size = 4;
	cmd.address = address;
	cmd.length = 1;
	cmd.data.rx = (uint8_t *)protect;
	_at25dfx_chip_issue_read_command_wait(chip, cmd);

	_at25dfx_spi_unlock(chip->spi);

	return STATUS_OK;
}

/**
 * \brief Put device to sleep
 *
 * This function puts the SerialFlash device to sleep for the purpose of
 * reducing power consumption while the device is not needed.
 *
 * \sa at25dfx_chip_wake()
 *
 * \note The device will not respond to any commands until it is woken up.
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 *
 * \return Status of operation.
 * \retval STATUS_OK if write operation succeeded.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 */
enum status_code at25dfx_chip_sleep(struct at25dfx_chip_module *chip)
{
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	cmd.opcode = AT25DFX_COMMAND_SLEEP;
	cmd.command_size = 1;
	cmd.length = 0;

	// Init to avoid warnings with -Os
	cmd.address = (at25dfx_address_t)NULL;
	cmd.data.tx = NULL;

	_at25dfx_chip_issue_write_command_wait(chip, cmd);

	_at25dfx_spi_unlock(chip->spi);

	return STATUS_OK;
}

/**
 * \brief Wake device from sleep
 *
 * This function wakes the SerialFlash device from sleep.
 *
 * \sa at25dfx_chip_sleep()
 *
 * \param[in] chip Address of SerialFlash chip instance to operate on.
 *
 * \return Status of operation.
 * \retval STATUS_OK if write operation succeeded.
 * \retval STATUS_BUSY if SPI is busy with some other operation.
 */
enum status_code at25dfx_chip_wake(struct at25dfx_chip_module *chip)
{
	enum status_code status;
	struct at25dfx_command cmd;

	Assert(chip);

	status = _at25dfx_spi_lock(chip->spi);
	if (status == STATUS_BUSY) {
		return status;
	}

	cmd.opcode = AT25DFX_COMMAND_WAKE;
	cmd.command_size = 1;
	cmd.length = 0;

	// Init to avoid warnings with -Os
	cmd.address = (at25dfx_address_t)NULL;
	cmd.data.tx = NULL;

	_at25dfx_chip_issue_write_command_wait(chip, cmd);

	_at25dfx_spi_unlock(chip->spi);

	return STATUS_OK;
}