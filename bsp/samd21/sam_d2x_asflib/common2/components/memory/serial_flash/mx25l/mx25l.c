/**
 * \file
 *
 * \brief Management of the Serial Flash MX25L driver through SPI.
 * This file manages the access to the Serial Flash MX25L components.
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
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

#include "mx25l.h"

#if SAM_PART_IS_DEFINED(SAMR21E18A) || defined(__DOXYGEN__)
/** \name MX25L2006E Pin Connection in ATSAMR21B18-MZ210PA
 * @{
 */
#  define MX25L_SPI                SERCOM3
#  define MX25L_SPI_PIN_SI         PIN_PA25
#  define MX25L_SPI_PIN_SO         PIN_PA24
#  define MX25L_SPI_PIN_SCLK       PIN_PA28
#  define MX25L_SPI_PIN_CS         PIN_PA27
#  define MX25L_SPI_PINMUX_SI      PINMUX_PA25C_SERCOM3_PAD3
#  define MX25L_SPI_PINMUX_SO      PINMUX_PA24C_SERCOM3_PAD2
#  define MX25L_SPI_PINMUX_SCLK    PINMUX_PA28F_SERCOM3_PAD1
#  define MX25L_SPI_PINMUX_CS      PINMUX_UNUSED
#  define MX25L_SPI_MUX_SETTING    SPI_SIGNAL_MUX_SETTING_K

/* @} */
#else
#  error This Serial Flash is not supported by the driver.
#endif

/** \name MX25L Command HEX Code Definition
 * @{
 */
 /** RDID (Read Identification) */
#define MX25L_CMD_RDID         0x9F
/** RES (Read Electronic ID) */
#define MX25L_CMD_RES          0xAB
/** REMS (Read Electronic & Device ID) */
#define MX25L_CMD_REMS         0x90

/** WRSR (Write Status Register) */
#define MX25L_CMD_WRSR         0x01
/** RDSR (Read Status Register) */
#define MX25L_CMD_RDSR         0x05

/** READ (1 x I/O) */
#define MX25L_CMD_READ         0x03
/** FAST READ (Fast read data) */
#define MX25L_CMD_FASTREAD     0x0B
/** DREAD (1In/2 Out fast read) */
#define MX25L_CMD_DREAD        0x3B

/** WREN (Write Enable) */
#define MX25L_CMD_WREN         0x06
/** WRDI (Write Disable) */
#define MX25L_CMD_WRDI         0x04
/** PP (page program) */
#define MX25L_CMD_PP           0x02

/** SE (Sector Erase) */
#define MX25L_CMD_SE           0x20
/** BE (Block Erase) */
#define MX25L_CMD_BE           0xD8
/** CE (Chip Erase) hex code: 60 or C7 */
#define MX25L_CMD_CE           0x60

/** DP (Deep Power Down) */
#define MX25L_CMD_DP           0xB9
/** RDP (Release form Deep Power Down) */
#define MX25L_CMD_RDP          0xAB
/* @} */

/** Timeout value for waiting write operation done. */
#define MX25L_WAIT_TIMEOUT    50000000

/** SPI instance. */
struct spi_module _mx25l_spi;

/** \name Internal Functions
 * @{
 */

/**
 * \brief Select the chip.
 *
 * This function selects the specified chip by driving its CS line low.
 */
static inline void _mx25l_chip_select(void)
{
	port_pin_set_output_level(MX25L_SPI_PIN_CS, false);
}

/**
 * \brief Deselect the chip.
 *
 * This function deselects the specified chip by driving its CS line high.
 */
static inline void _mx25l_chip_deselect(void)
{
	port_pin_set_output_level(MX25L_SPI_PIN_CS, true);
}

/**
 * \brief Send command to set or reset WEL bit.
 *
 * The WREN instruction is for setting Write Enable Latch (WEL) bit.
 * The WRDI instruction is to reset Write Enable Latch (WEL) bit.
 *
 * \param[in] cmd WREN or WRDI command
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 */
static enum status_code _mx25l_send_cmd_write_latch(uint8_t cmd)
{
	enum status_code status;
	uint8_t tx_buf[1] = {cmd};

	_mx25l_chip_select();
	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 1);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}
	_mx25l_chip_deselect();

	return STATUS_OK;
}

/**
 * \brief Check if Serial Flash in busy.
 *
 * \return true or false.
 * \retval true   Busy (WIP bit = 1)
 * \retval false  Ready (WIP bit = 0)
 */
static bool _mx25l_is_flash_busy(void)
{
	uint8_t mx25_status;

	mx25l_read_status(&mx25_status);
	if (mx25_status & MX25L_STATUS_WIP) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Wait Serial Flash ready with timeout.
 *
 * \param[in] timeout Time to wait
 *
 * \return true or false.
 * \retval true   Flash is ready
 * \retval false  flash is time-out
 */
static bool _mx25l_wait_flash_ready(uint32_t timeout)
{
	while (1) {
		if (_mx25l_is_flash_busy()) {
			if (timeout) {
				timeout--;
			}
			if (timeout == 0) {
				return false;
			}
		} else {
			break;
		}
	}

	return true;
}

/* @} */

/**
 * \brief Initialize chip driver instance.
 *
 * This function initializes a chip instance and associates it with a specified
 * SPI instance.
 *
 * \param[in] config Pointer to the configuration for the SPI interface.
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 */
enum status_code mx25l_init(struct mx25l_spi_config *const config)
{
	enum status_code status;

	/* Initialize SPI interface */
	struct spi_config spi_conf;

	spi_get_config_defaults(&spi_conf);
	spi_conf.transfer_mode = config->spi_transfer_mode;
	spi_conf.mode_specific.master.baudrate = config->spi_baudrate;
	spi_conf.mux_setting = MX25L_SPI_MUX_SETTING;
	spi_conf.pinmux_pad0 = MX25L_SPI_PINMUX_SI;
	spi_conf.pinmux_pad1 = MX25L_SPI_PINMUX_CS;
	spi_conf.pinmux_pad2 = MX25L_SPI_PINMUX_SO;
	spi_conf.pinmux_pad3 = MX25L_SPI_PINMUX_SCLK;

	status = spi_init(&_mx25l_spi, MX25L_SPI, &spi_conf);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}
	spi_enable(&_mx25l_spi);

	/* Initialize CS pin */
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(MX25L_SPI_PIN_CS, &pin_conf);
	port_pin_set_output_level(MX25L_SPI_PIN_CS, true);

	return STATUS_OK;
};

/**
 * \brief Read Serial Flash identification.
 * Read ID information with command RDID, RES and REMS.
 *
 * \param[out] id Pointer to Serial Flash id struct
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 */
enum status_code mx25l_read_id(struct mx25l_id *id)
{
	enum status_code status;
	uint8_t tx_buf[4] = {0, 0, 0, 0};
	uint8_t rx_buf[3];

	/* Read RDID */
	_mx25l_chip_select();
	tx_buf[0] = MX25L_CMD_RDID;
	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 1);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}
	status = spi_read_buffer_wait(&_mx25l_spi, rx_buf, 3, 0);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}
	id->manufacturer_id = rx_buf[0];
	id->memory_type = rx_buf[1];
	id->memroy_density = rx_buf[2];
	_mx25l_chip_deselect();

	/* Read RES */
	_mx25l_chip_select();
	tx_buf[0] = MX25L_CMD_RES; /* 1 byte cmd + 3 bytes dummy data */
	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 4);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}
	status = spi_read_buffer_wait(&_mx25l_spi, rx_buf, 1, 0);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}
	id->electronic_id = rx_buf[0];
	_mx25l_chip_deselect();

	/* Read REMS */
	_mx25l_chip_select();
	tx_buf[0] = MX25L_CMD_REMS;
	tx_buf[3] = 0; /* ADD = 0 */
	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 4);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}
	status = spi_read_buffer_wait(&_mx25l_spi, rx_buf, 2, 0);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	} 
	id->device_id = rx_buf[1];
	_mx25l_chip_deselect();

	return STATUS_OK;
};

/**
 * \brief Read Status Register.
 *
 * The RDSR instruction is for reading Status Register Bits.
 *
 * \param[out] value Pointer to status buffer
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 */
enum status_code mx25l_read_status(uint8_t *value)
{
	enum status_code status;
	uint8_t tx_buf[1] = {MX25L_CMD_RDSR};

	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 1);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	status = spi_read_buffer_wait(&_mx25l_spi, value, 1, 0);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	return STATUS_OK;
}

/**
 * \brief Write Status Register.
 *
 * The WRSR instruction is for changing the values of Status Register Bits
 * (and configuration register).
 *
 * \param[out] value Value to be write
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 */
enum status_code mx25l_write_status(uint8_t value)
{
	enum status_code status;
	uint8_t tx_buf[2] = {MX25L_CMD_WRSR, value};

	if (_mx25l_is_flash_busy()) {
		return STATUS_BUSY;
	}

	_mx25l_send_cmd_write_latch(MX25L_CMD_WREN);

	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 2);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	if (!_mx25l_wait_flash_ready(MX25L_WAIT_TIMEOUT)) {
		return STATUS_ERR_IO;
	}

	return STATUS_OK;
}

/**
 * \brief Read data from Serial Flash device.
 *
 * This function reads data from the Serial Flash device, into a buffer.
 *
 * \param[in] address SerialFlash internal address to start reading from
 * \param[out] data  Buffer to write data into
 * \param[in] length Number of bytes to read
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 * \retval STATUS_ERR_INVALID_ARG if address and/or length is out of bounds
 * \retval STATUS_BUSY            if flash in busy
 */
enum status_code mx25l_read_buffer(uint32_t address, void *data, uint32_t length)
{
	enum status_code status;
	uint8_t tx_buf[4] = {
		MX25L_CMD_READ,
		(uint8_t)(address >> 16),
		(uint8_t)(address >> 8),
		(uint8_t)(address)
	};

	Assert(data);

	if ((address + length) > MX25L_FLASH_SIZE) {
		return STATUS_ERR_INVALID_ARG;
	}

	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 4);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	status = spi_read_buffer_wait(&_mx25l_spi, data, length, 0);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	return STATUS_OK;
}

/**
 * \brief Write data to Serial Flash device.
 *
 * This function writes data to the Serial Flash device, from a buffer.
 *
 * \note Please erase related memory area before write operation.
 *
 * \param[in] address SerialFlash internal address to start writing to
 * \param[in] data    Buffer to read data from
 * \param[in] length  Number of bytes to write
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 * \retval STATUS_ERR_INVALID_ARG if address and/or length is out of bounds
 * \retval STATUS_BUSY            if flash in busy
 */
enum status_code mx25l_write_buffer(uint32_t address, const void *data, uint32_t length)
{
	enum status_code status;
	uint32_t write_address;
	uint32_t write_length;
	uint8_t *data_wr = (uint8_t *)data;
	uint8_t tx_buf[4] = {MX25L_CMD_PP};

	Assert(data);

	if ((address + length) > MX25L_FLASH_SIZE) {
		return STATUS_ERR_INVALID_ARG;
	}

	if (_mx25l_is_flash_busy()) {
		return STATUS_BUSY;
	}

	write_address = address;
	write_length = MX25L_PAGE_SIZE - (address % MX25L_PAGE_SIZE);
	if (write_length) {
		_mx25l_send_cmd_write_latch(MX25L_CMD_WREN);
		_mx25l_chip_select();

		/* Write page program command */
		tx_buf[1] = (uint8_t)(write_address >> 16);
		tx_buf[2] = (uint8_t)(write_address >> 8);
		tx_buf[3] = (uint8_t)(write_address);
		status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 4);
		if (status != STATUS_OK) {
			return STATUS_ERR_IO;
		}

		/* Write page data into flash */
		status = spi_write_buffer_wait(&_mx25l_spi, data_wr, write_length);
		if (status != STATUS_OK) {
			return STATUS_ERR_IO;
		}

		_mx25l_chip_deselect();

		if (!_mx25l_wait_flash_ready(MX25L_WAIT_TIMEOUT)) {
			return STATUS_ERR_IO;
		}

		write_address += write_length;
		data_wr += write_length;
		length -= write_length;
	}

	while (length) {
		write_length = min(MX25L_PAGE_SIZE, length);
		_mx25l_send_cmd_write_latch(MX25L_CMD_WREN);
		_mx25l_chip_select();

		/* Write page program command */
		tx_buf[1] = (uint8_t)(write_address >> 16);
		tx_buf[2] = (uint8_t)(write_address >> 8);
		tx_buf[3] = (uint8_t)(write_address);
		status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 4);
		if (status != STATUS_OK) {
			return STATUS_ERR_IO;
		}

		/* Write page data into flash */
		status = spi_write_buffer_wait(&_mx25l_spi, data_wr, write_length);
		if (status != STATUS_OK) {
			return STATUS_ERR_IO;
		}

		_mx25l_chip_deselect();

		if (!_mx25l_wait_flash_ready(MX25L_WAIT_TIMEOUT)) {
			return STATUS_ERR_IO;
		}

		write_address += write_length;
		data_wr += write_length;
		length -= write_length;
	}

	return STATUS_OK;
}

/**
 * \brief Erase sector of Serial Flash device.
 *
 * The SE instruction is for erasing the data of the chosen
 * sector (4KB) to be "1".
 *
 * \param[in] address Serial flash internal address in the sector
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 * \retval STATUS_BUSY            if flash in busy
 */
enum status_code mx25l_erase_sector(uint32_t address) //do we have to dispose the address?
{
	enum status_code status;
	uint8_t tx_buf[4] = {
		MX25L_CMD_SE,
		(uint8_t)(address >> 16),
		(uint8_t)(address >> 8),
		(uint8_t)(address)
	};

	if ((address) >= MX25L_FLASH_SIZE) {
		return STATUS_ERR_INVALID_ARG;
	}

	if (_mx25l_is_flash_busy()) {
		return STATUS_BUSY;
	}

	_mx25l_send_cmd_write_latch(MX25L_CMD_WREN);
	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 4);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	if (!_mx25l_wait_flash_ready(MX25L_WAIT_TIMEOUT)) {
		return STATUS_ERR_IO;
	}

	return STATUS_OK;
}

/**
 * \brief Erase block of Serial Flash device.
 *
 * The BE instruction is for erasing the data of the chosen
 * sector (64KB) to be "1".
 *
 * \param[in] address Serial flash internal address in the block
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 * \retval STATUS_BUSY            if flash in busy
 */
enum status_code mx25l_erase_block(uint32_t address)
{
	enum status_code status;
	uint8_t tx_buf[4] = {
		MX25L_CMD_BE,
		(uint8_t)(address >> 16),
		(uint8_t)(address >> 8),
		(uint8_t)(address)
	};

	if ((address) >= MX25L_FLASH_SIZE) {
		return STATUS_ERR_INVALID_ARG;
	}

	if (_mx25l_is_flash_busy()) {
		return STATUS_BUSY;
	}

	_mx25l_send_cmd_write_latch(MX25L_CMD_WREN);
	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 4);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	if (!_mx25l_wait_flash_ready(MX25L_WAIT_TIMEOUT)) {
		return STATUS_ERR_IO;
	}

	return STATUS_OK;
}

/**
 * \brief Erase all chip of Serial Flash device.
 *
 * The CE instruction is for erasing the data of the whole chip to be "1".
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 * \retval STATUS_BUSY            if flash in busy
 */
enum status_code mx25l_erase_chip(void)
{
	enum status_code status;
	uint8_t tx_buf[1] = {MX25L_CMD_CE};

	if (_mx25l_is_flash_busy()) {
		return STATUS_BUSY;
	}

	_mx25l_send_cmd_write_latch(MX25L_CMD_WREN);
	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 1);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	if (!_mx25l_wait_flash_ready(MX25L_WAIT_TIMEOUT)) {
		return STATUS_ERR_IO;
	}

	return STATUS_OK;
}

/**
 * \brief Enter deep power down mode.
 *
 * The DP instruction is for setting the device on the minimizing
 * the power consumption.
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 */
enum status_code mx25l_enter_deep_powerdown(void)
{
	enum status_code status;
	uint8_t tx_buf[1] = {MX25L_CMD_DP};

	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 1);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	return STATUS_OK;
}

/**
 * \brief Exit deep power down mode.
 *
 * The Release from RDP instruction is putting the device in the
 * Stand-by Power mode.
 *
 * \return Status of operation.
 * \retval STATUS_OK              if operation succeeded
 * \retval STATUS_ERR_IO          if operation failed
 */
enum status_code mx25l_exit_deep_powerdown(void)
{
	enum status_code status;
	uint8_t tx_buf[1] = {MX25L_CMD_RDP};

	_mx25l_chip_select();

	status = spi_write_buffer_wait(&_mx25l_spi, tx_buf, 1);
	if (status != STATUS_OK) {
		return STATUS_ERR_IO;
	}

	_mx25l_chip_deselect();

	return STATUS_OK;
}
