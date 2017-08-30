/**
 * \file
 *
 * \brief AT25DFx SerialFlash driver interface.
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

#ifndef AT25DFX_H
#define AT25DFX_H

/**
 * \defgroup asfdoc_common2_at25dfx_group AT25DFx SerialFlash Driver
 *
 * This driver provides an interface for basic usage of SerialFlash devices,
 * i.e., read/write, global and local protect/unprotect of sectors, and
 * sleep/wake.
 *
 * It supports multiple instances, and the instances can be connected to either
 * common or individual SPI interfaces. For a list of the supported SerialFlash
 * types, see \ref at25dfx_type.
 *
 * The following peripherals are used by this module:
 * - \ref SERCOM SPI (data transfer)
 * - \ref PORT (chip selection)
 *
 * The outline of this documentation is as follows:
 * - \ref asfdoc_common2_at25dfx_prerequisites
 * - \ref asfdoc_common2_at25dfx_module_overview
 * - \ref asfdoc_common2_at25dfx_special_considerations
 * - \ref asfdoc_common2_at25dfx_extra_info
 * - \ref asfdoc_common2_at25dfx_examples
 * - \ref asfdoc_common2_at25dfx_api_overview
 *
 *
 * \section asfdoc_common2_at25dfx_prerequisites Prerequisites
 *
 * This driver requires that the SPI drivers are instantiated, initialized and
 * enabled by the user, and that the SPI instances are persistent for as long as
 * the associated instances of this driver exist or are used. To ensure
 * persistence of the SPI instances, the convention is to define them in the
 * same scope as the instances of this driver, which is usually a global one.
 *
 * The hardware abstraction layer (HAL) of this driver supports several SPI
 * driver implementations, but not at the same time. So for a given project, one
 * must select which implementation to support, and use it for all instances.
 * The reader is assumed to be familiar with how to configure and initialize the
 * SPI drivers, but the basic configuration to use is supplied by this driver's
 * HAL:
 * - \ref at25dfx_spi_get_config_defaults() for polled SERCOM SPI
 * - \ref at25dfx_spi_master_vec_get_config_defaults() for SERCOM SPI Master
 *    with Vectored I/O
 *
 * To ensure correct operation, the user should not change anything in the base
 * configuration except the baud rate, the SERCOM MUX and the pin MUX settings.
 *
 *
 * \section asfdoc_common2_at25dfx_module_overview Module Overview
 *
 * This driver enables the user to do basic operations on SerialFlash devices in
 * the AT25DFx series, such as checking their presence, reading from and writing
 * to them, putting them to sleep and waking them back up when needed. Basic
 * security is implemented, i.e., sector protection to prevent accidental erase
 * and write. Functionality for permanently locking and securing AT25DFx devices
 * is not implemented in this driver.
 *
 * Each instance of this driver corresponds to a single AT25DFx device, and must
 * be associated with an instance of the SPI driver supported by the selected
 * HAL implementation, as well as a PORT pin for chip select (CS).
 *
 * All functions of this driver are blocking, which means that they do not
 * return until the initiated operation completes. Further, since the selected
 * HAL might use an interrupt-driven driver, this driver should not be used
 * within interrupts.
 *
 *
 * \subsection asfdoc_common2_at25dfx_module_spi_share SPI Bus Sharing
 *
 * SerialFlash devices can share a SPI bus, due to the use of CS lines. SPI bus
 * sharing is supported by this driver without any special configuration. To
 * share a SPI bus, simply associate the same SPI driver instance to multiple
 * instances of this driver.
 *
 * The \ref asfdoc_sam0_at25dfx_example "figure below" illustrates an example
 * where two out of three instances of this driver are associated with the same
 * SPI driver instance.
 *
 * \anchor asfdoc_sam0_at25dfx_example
 * \image html at25dfx.png "AT25DFx and SPI instance sharing."
 *
 *
 * \subsection asfdoc_common2_at25dfx_module_threads Use in Threaded Environments
 *
 * The functions of this driver rely on the locking mechanism in the SPI drivers
 * to ensure exclusive access to a SPI driver instance for the entire duration
 * of an operation, such as writing data to the AT25DFx device. They will not
 * wait for an already locked instance to be unlocked. Instead, they will simply
 * return a status code indicating that it was busy.
 *
 * This behavior means that the functions are thread safe in the sense that no
 * two operations may interfere with each other. It also means that there is no
 * queueing of operations. Assuming the illustration above was a multi-threaded
 * application, it would have to wait for an operation on AT25DFx instance #2 to
 * end before one could be initiated on instance #3, and vice versa. If queueing
 * of operations is needed, it must be implemented as a layer on top of this
 * driver.
 *
 * Be aware that the protocol implementation in this driver is not interrupt-
 * driven, and the HAL may use a polled driver. Hence, an on-going operation may
 * be temporarily paused if the MCU switches threads.
 *
 *
 * \section asfdoc_common2_at25dfx_special_considerations Special Considerations
 *
 * \subsection asfdoc_common2_at25dfx_special_dev Device Specifics
 *
 * The available erase block sizes, and the availability and granularity of
 * protection sectors may differ between devices.
 *
 * For example, with AT25F512B (\ref AT25DFX_512B), issuing a 64 kB block erase
 * command will cause a 32 kB erase, and it does not support setting protection
 * on individual sectors, only globally.
 *
 * Refer to the SerialFlash device's datasheet for details about which
 * operations are supported and what limitations apply to them.
 *
 *
 * \subsection asfdoc_common2_at25dfx_special_flash Flash Memory Behavior
 *
 * The reader should be aware of some details of how flash memory generally
 * functions:
 * -# Erasing a flash memory block means that all bits in the block are reset to
 *    a high level (logical "1"), i.e., all bytes will read as \c 0xFF.
 * -# Writing to a flash memory location will only set relevant bits to a low
 *    level (logical "0"), never to a high level.
 * -# It is possible to write several times to a flash memory block without
 *    erasing, but there may be limitations on the number of times it can be
 *    done.
 *
 *
 * \section asfdoc_common2_at25dfx_extra_info Extra Information
 *
 * For extra information, see
 * \subpage asfdoc_common2_at25dfx_extra. This includes:
 * - \ref asfdoc_common2_at25dfx_extra_acronyms
 * - \ref asfdoc_common2_at25dfx_extra_dependencies
 * - \ref asfdoc_common2_at25dfx_extra_errata
 * - \ref asfdoc_common2_at25dfx_extra_history
 *
 * \section asfdoc_common2_at25dfx_examples Examples
 *
 * For a list of examples related to this driver, see
 * \subpage asfdoc_common2_at25dfx_exqsg.
 *
 * \section asfdoc_common2_at25dfx_api_overview API Overview
 *
 * @{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/** SerialFlash type. */
enum at25dfx_type {
	/** AT25F512B, compatible with AT25BCM512B */
	AT25DFX_512B,
	/** AT25DF021 */
	AT25DFX_021,
	/** AT25DF041A */
	AT25DFX_041A,
	/** AT25DF081, compatible with AT25DL081 */
	AT25DFX_081,
	/** AT25DF081A, compatible with AT26DF081A */
	AT25DFX_081A,
	/** AT25DF161 */
	AT25DFX_161,
	/** AT25DL161 */
	AT25DFX_L161,
	/** AT25DQ161 */
	AT25DFX_Q161,
	/** AT25DF321A */
	AT25DFX_321A,
	/** AT25DF641, compatible with AT25DF641A */
	AT25DFX_641,
};

#include <at25dfx_hal.h>

/** Size of block to erase. */
enum at25dfx_block_size {
	/** 4 kiloByte block size. */
	AT25DFX_BLOCK_SIZE_4KB,
	/** 32 kiloByte block size. */
	AT25DFX_BLOCK_SIZE_32KB,
	/** 64 kiloByte block size. */
	AT25DFX_BLOCK_SIZE_64KB,
};

/** SerialFlash internal address. */
typedef uint32_t at25dfx_address_t;

/** Length of data package to read/write. */
typedef uint16_t at25dfx_datalen_t;

/** SerialFlash chip driver instance. */
struct at25dfx_chip_module {
#if !defined(__DOXYGEN__)
	/** SPI module to use. */
	at25dfx_spi_module_t *spi;
	/** Type of SerialFlash */
	enum at25dfx_type type;
	/** Chip Select (CS) pin. */
	uint8_t cs_pin;
#endif
};

/** SerialFlash chip configuration. */
struct at25dfx_chip_config {
	/** Type of SerialFlash */
	enum at25dfx_type type;
	/** Chip Select (CS) pin. */
	uint8_t cs_pin;
};

//! \name Initialization
//@{

/**
 * \brief Initialize chip driver instance.
 *
 * This function initializes a chip instance and associates it with a specified
 * SPI instance.
 *
 * \param[out] module Pointer to the chip instance to initialize.
 * \param[in] spi_module Pointer to the SPI instance to associate with.
 * \param[in] config Pointer to the configuration for the chip.
 */
static inline enum status_code at25dfx_chip_init(
		struct at25dfx_chip_module *const module,
		at25dfx_spi_module_t *const spi_module,
		const struct at25dfx_chip_config *const config)
{
	struct port_config port_config;

	module->type = config->type;
	module->cs_pin = config->cs_pin;
	module->spi = spi_module;

	// Configure CS pin as output, high
	port_get_config_defaults(&port_config);
	port_config.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(module->cs_pin, &port_config);
	port_pin_set_output_level(module->cs_pin, true);

	return STATUS_OK;
}

//@}

//! \name Presence
//@{
enum status_code at25dfx_chip_check_presence(struct at25dfx_chip_module *chip);
//@}

//! \name Read/Write
//@{
enum status_code at25dfx_chip_read_buffer(struct at25dfx_chip_module *chip,
		at25dfx_address_t address, void *data, at25dfx_datalen_t length);
enum status_code at25dfx_chip_write_buffer(struct at25dfx_chip_module *chip,
		at25dfx_address_t address, const void *data, at25dfx_datalen_t length);
//@}

//! \name Erase
//@{
enum status_code at25dfx_chip_erase(struct at25dfx_chip_module *chip);
enum status_code at25dfx_chip_erase_block(struct at25dfx_chip_module *chip,
		at25dfx_address_t address, enum at25dfx_block_size block_size);
//@}

//! \name Sector Protect
//@{
enum status_code at25dfx_chip_set_global_sector_protect(
		struct at25dfx_chip_module *chip, bool protect);
enum status_code at25dfx_chip_set_sector_protect(
		struct at25dfx_chip_module *chip, at25dfx_address_t address,
		bool protect);
enum status_code at25dfx_chip_get_sector_protect(
		struct at25dfx_chip_module *chip, at25dfx_address_t address,
		bool *protect);
//@}

//! \name Sleep/Wake
//@{
enum status_code at25dfx_chip_sleep(struct at25dfx_chip_module *chip);
enum status_code at25dfx_chip_wake(struct at25dfx_chip_module *chip);
//@}

/** @} */

/**
 * \page asfdoc_common2_at25dfx_extra Extra Information for AT25DFx SerialFlash Driver
 *
 *
 * \section asfdoc_common2_at25dfx_extra_acronyms Acronyms
 *
 * The table below presents the acronyms used in this module.
 *
 * <table>
 *   <tr>
 *     <th>Acronym</td>
 *     <th>Description</td>
 *   </tr>
 *   <tr>
 *     <td>CS</td>
 *     <td>Chip Select</td>
 *   </tr>
 *   <tr>
 *     <td>HAL</td>
 *     <td>Hardware Abstraction Layer</td>
 *   </tr>
 *   <tr>
 *     <td>SPI</td>
 *     <td>Serial Peripheral Interface</td>
 *   </tr>
 * </table>
 *
 *
 * \section asfdoc_common2_at25dfx_extra_dependencies Dependencies
 *
 * This driver has the following dependencies:
 * - \ref asfdoc_sam0_sercom_spi_group "SERCOM SPI driver" (depending on
 *    selected HAL)
 * - \ref asfdoc_sam0_sercom_spi_master_vec_group "SERCOM SPI master driver w/ vectored I/O"
 *    (depending on selected HAL)
 * - \ref asfdoc_sam0_port_group "PORT driver"
 * - \ref group_sam0_utils "Compiler driver"
 *
 *
 * \section asfdoc_common2_at25dfx_extra_errata Errata
 *
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_common2_at25dfx_extra_history Module History
 *
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in the
 * table.
 *
 * <table>
 *   <tr>
 *     <th>Changelog</th>
 *   </tr>
 *   <tr>
 *     <td>Initial Release</td>
 *   </tr>
 * </table>
 */

/**
 * \page asfdoc_common2_at25dfx_exqsg Examples for AT25DFx SerialFlash Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_common2_at25dfx_group. QSGs are
 * simple examples with step-by-step instructions to configure and use this
 * driver in a selection of use cases. Note that QSGs can be compiled as a
 * standalone application or be added to the user application.
 *
 * - \subpage asfdoc_common2_at25dfx_basic_use
 */

/**
 * \page asfdoc_common2_at25dfx_document_revision_history Document Revision History
 *
 * <table>
 * <tr>
 * <th>Doc. Rev.</td>
 * <th>Date</td>
 * <th>Comments</td>
 * </tr>
 * <tr>
 * <td>A</td>
 * <td>01/2014</td>
 * <td>Initial release</td>
 * </tr>
 * </table>
 */

#ifdef __cplusplus
}
#endif

#endif // AT25DFX_H