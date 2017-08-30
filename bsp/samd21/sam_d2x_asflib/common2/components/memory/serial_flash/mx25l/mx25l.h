/**
 * \file
 *
 * \brief API driver for Serial Flash MX25L (Known Good Die) in SAM device.
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

#ifndef MX25L_H_INCLUDED
#define MX25L_H_INCLUDED

/**
 * \defgroup asfdoc_common2_mx25l_group MX25L Serial Flash Driver
 *
 * This driver provides an interface for basic usage of MX25L Serial Flash
 * devices, i.e., initialization, data read/write, block protection, 
 * device ID read, enter or exit deep power mode etc.
 *
 * SPI polling mode is used in this driver.
 *
 * Boards can use this module:
 * - ATSAMR21B18-MZ210PA
 *
 * The following peripherals are used by this module:
 * - SERCOM SPI (data transfer)
 * - PORT (chip selection)
 *
 * For quick start guide related to this driver, see
 * \ref asfdoc_common2_mx25l_exqsg.
 *
 * \section asfdoc_common2_mx25l_api_overview API Overview
 *
 * @{
 */

#include "compiler.h"
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif

#if SAM_PART_IS_DEFINED(SAMR21E18A) || defined(__DOXYGEN__)
/**
 * \name MX25L2006E Related Parameter Definition
 * @{
 */
#  define MX25L_FLASH_SIZE   0x40000  /**< Flash size 256 KB */
#  define MX25L_BLOCK_SIZE   0x10000  /**< 64K block size */
#  define MX25L_SECTOR_SIZE  0x1000   /**< 4K sector size */
#  define MX25L_PAGE_SIZE    0x0100   /**< 256 byte page size */

#  define MX25L_BLOCK_NUM    (MX25L_FLASH_SIZE / MX25L_BLOCK_SIZE)
#  define MX25L_SECTOR_NUM   (MX25L_FLASH_SIZE / MX25L_SECTOR_SIZE)
#  define MX25L_PAGE_NUM     (MX25L_FLASH_SIZE / MX25L_PAGE_SIZE)
/* @} */
#else
#  error This Serial Flash is not supported by the driver.
#endif

/**
 * \name Bit Mask Definition for Status Register
 * @{
 */
/** The Write in Progress (WIP) bit */
#define MX25L_STATUS_WIP    (0x01 << 0)
/** The Write Enable Latch (WEL) bit */
#define MX25L_STATUS_WEL    (0x01 << 1)
/** The Block Protect BP0 bit */
#define MX25L_STATUS_BP0    (0x01 << 2)
/** The Block Protect BP1 bit */
#define MX25L_STATUS_BP1    (0x01 << 3)
/** The Status Register Write Disable (SRWD) bit */
#define MX25L_STATUS_SRWD   (0x01 << 7)
/* @} */

 /**
 * \name Protect Level for Status register
 * @{
 */
/** The protect level 0 */
#define MX25L_STATUS_PROTECT_LEVEL_0    (0x00 << 2)
/** The protect level 1 */
#define MX25L_STATUS_PROTECT_LEVEL_1    (0x01 << 2)
/** The protect level 2 */
#define MX25L_STATUS_PROTECT_LEVEL_2    (0x02 << 2)
/** The protect level 3 */
#define MX25L_STATUS_PROTECT_LEVEL_3    (0x03 << 2)
/** The protect level mask */
#define MX25L_STATUS_PROTECT_LEVEL_MASK (0x03 << 2)
/* @} */

/** SPI interface configuration for Serial Flash. */
struct mx25l_spi_config {
	/** SPI transfer mode: Mode 0 and Mode 3 are supported */
	enum spi_transfer_mode spi_transfer_mode;
	/** SPI baudrate of serial clock */
	uint32_t spi_baudrate;
};

/** Serial Flash identification. */
struct mx25l_id {
	/** Manufacturer ID */
	uint8_t manufacturer_id;
	/** Memory type */
	uint8_t memory_type;
	/** Density ID */
	uint8_t memroy_density;
	/** Electronic ID */
	uint8_t electronic_id;
	/** Device ID */
	uint8_t device_id;
};

/**
 * \name Initialization
 * @{
 */
/**
 * \brief Get default SPI interface configuration.
 *
 * This function initializes the SPI configuration struct with default settings
 * that should work with Serial Flash devices.
 *
 * The default configuration is as follows:
 *  \li Transfer mode 0
 *  \li Baudrate 100000
 *
 * \param[out] config Address of config struct to initialize
 */
static inline void mx25l_spi_get_config_defaults(
		struct mx25l_spi_config *const config)
{
	config->spi_transfer_mode = SPI_TRANSFER_MODE_0;
	config->spi_baudrate = 100000;
}

enum status_code mx25l_init(struct mx25l_spi_config *const config);
/* @} */

/**
 * \name Read Device ID
 * @{
 */
enum status_code mx25l_read_id(struct mx25l_id *id);
/* @} */

/**
 * \name Read/Write Status Register
 * @{
 */
enum status_code mx25l_read_status(uint8_t *value);
enum status_code mx25l_write_status(uint8_t value);
/* @} */

/**
 * \name Read/Write Data
 * @{
 */
enum status_code mx25l_read_buffer(uint32_t address,
		void *data, uint32_t length);
enum status_code mx25l_write_buffer(uint32_t address,
		const void *data, uint32_t length);
/* @} */

/**
 * \name Erase Sector/Block/Chip
 * @{
 */
enum status_code mx25l_erase_sector(uint32_t address);
enum status_code mx25l_erase_block(uint32_t address);
enum status_code mx25l_erase_chip(void);
/* @} */

/**
 * \name Enter/Exit Deep Power Down
 * @{
 */
enum status_code mx25l_enter_deep_powerdown(void);
enum status_code mx25l_exit_deep_powerdown(void);
/* @} */

#ifdef __cplusplus
}
#endif
/** @} */

/**
 * \page asfdoc_common2_mx25l_exqsg Quick Start Guide for MX25L Driver
 *
 * This is the quick start guide for the \ref asfdoc_common2_mx25l_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case. The code examples can be copied into the main
 * application loop or any other function that will need to control the
 * MX25L module.
 *
 * \section asfdoc_common2_mx25l_qsg_use_cases Use Cases
 * - \ref asfdoc_common2_mx25l_qsg_basic
 *
 * \section asfdoc_common2_mx25l_qsg_basic Basic Usage of MX25L Driver
 *
 * This use case will demonstrate:
 * * How to initialize the MX25L module with SPI interface
 * * Read device ID
 * * Basic erase, read, and write functions
 *
 * \section asfdoc_common2_mx25l_qsg_basic_setup Setup Steps
 *
 * \subsection asfdoc_common2_mx25l_qsg_basic_prereq Prerequisites
 *
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_common2_mx25l_qsg_basic_setup_code Setup Code
 *
 * Add this to the main application source file, outside of any functions:
 * \code
	#define TEST_ADDR    0

	struct mx25l_id mx25l_id;
	uint8_t mx25l_rd_buf[MX25L_PAGE_SIZE];
	uint8_t mx25l_wr_buf[MX25L_PAGE_SIZE];
 * \endcode
 *
 * Add setup code to your main application C-file (typically the start of \c main()):
 * \code
	struct mx25l_spi_config spi_config;
	enum status_code status;

	system_init();

	mx25l_spi_get_config_defaults(&spi_config);
	status = mx25l_init(&spi_config);
 * \endcode
 *
 * \subsection asfdoc_common2_mx25l_qsg_basic_capture_setup_workflow Workflow
 *
 * -# Exit from deep power down mode
 *  \code status = mx25l_exit_deep_powerdown(); \endcode
 * -# Read Device ID
 *  \code
	status = mx25l_read_id(&mx25l_id);
 *  \endcode
 * -# Read a number of data from a specific address
 *  \code
	status = mx25l_read_buffer(TEST_ADDR, mx25l_rd_buf, MX25L_PAGE_SIZE);
 *  \endcode
 * -# Erase sector
 *  \code
	status = mx25l_erase_sector(TEST_ADDR);
 *  \endcode
 *
 *  More erase functions:
 *  \code
	status = mx25l_erase_block(TEST_ADDR);
	status = mx25l_erase_chip();
 *  \endcode
 * -# Write a number of data to a specific address
 *  \code
	for (i = 0 ; i < MX25L_PAGE_SIZE; i++) {
		mx25l_wr_buf[i] = i;
	}

	status = mx25l_write_buffer(TEST_ADDR, mx25l_wr_buf, MX25L_PAGE_SIZE);
 *  \endcode
 * -# Enter deep power down mode
 *  \code status = mx25l_enter_deep_powerdown(); \endcode
 * -# Enter infinite loop
 *  \code
	while (1) {
	};
 *  \endcode
 */

#endif /* MX25L_H_INCLUDED */
