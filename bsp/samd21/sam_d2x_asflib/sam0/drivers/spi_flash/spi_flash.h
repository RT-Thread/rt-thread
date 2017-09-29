/**
 * \file
 *
 * \brief SAM SPI Flash Driver for SAMB11
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
#ifndef SPI_FLASH_H_INCLUDED
#define SPI_FLASH_H_INCLUDED

/**
 * \defgroup asfdoc_samb_spi_flash_group SAM SPI Flash Driver (SPI Flash)
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the
 * configuration and management of the device's SPI Flash functionality. The
 * following driver API modes are covered by this manual:
 *
 * The following peripherals are used by this module:
 *  - SPI Flash (SPI Flash Management)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_samb_spi_flash_prerequisites
 *  - \ref asfdoc_samb_spi_flash_module_overview
 *  - \ref asfdoc_samb_spi_flash_special_considerations
 *  - \ref asfdoc_samb_spi_flash_extra_info
 *  - \ref asfdoc_samb_spi_flash_examples
 *  - \ref asfdoc_samb_spi_flash_api_overview
 *
 *
 * \section asfdoc_samb_spi_flash_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_samb_spi_flash_module_overview Module Overview
 * The AHB SPI-Flash Controller is used to access the internal stacked FLASH
 * memory to access various instruction/data code needed for storing
 * application code, code patches, and OTA images.
 *
 * The table above describes the stacked SPI Flash memory organization and layout.
 * Boot up, the ROM boot loader starts loading different sections of from the
 * flash by first reading the flash header to figure out the locations and sizes
 * for different sections, then copying the sections one by one into their
 * respective memory regions. The header and all sections have CRC calculated
 * for integrity check. If CRC fails, section will not be loaded into RAM.
 *
 * <table>
 *  <tr>
 *    <th>SPI flash memory address</th>
 *    <th>Function description</th>
 *  </tr>
 *  <tr>
 *    <td>0x0000 ~ 0x0FFF</td>
 *    <td>Flash Header</td>
 *  </tr>
 *  <tr>
 *    <td>0x1000 ~ End of patch section (according to patch size)</td>
 *    <td>Patch image section</td>
 *  </tr>
 *  <tr>
 *    <td>User App Start Section ~ User App End Section <=254KB</td>
 *    <td>USER APP</td>
 *  </tr>
 *  <tr>
 *    <td>NVDS 4KB</td>
 *    <td>NVDS</td>
 *  </tr>
 * </table>
 *
 * \section asfdoc_samb_spi_flash_special_considerations Special Considerations
 * There are no special considerations for this module.
 *
 * \section asfdoc_samb_spi_flash_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_samb_spi_flash_extra. This includes:
 *  - \ref asfdoc_samb_spi_flash_extra_acronyms
 *  - \ref asfdoc_samb_spi_flash_extra_dependencies
 *  - \ref asfdoc_samb_spi_flash_extra_errata
 *  - \ref asfdoc_samb_spi_flash_extra_history
 *
 *
 * \section asfdoc_samb_spi_flash_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_spi_flash_exqsg.
 *
 *
 * \section asfdoc_samb_spi_flash_api_overview API Overview
 * @{
 */

#include <stdint.h>
#include <string.h>
#include <compiler.h>
#include <gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Flash memory size: 256 KBytes */
#define FLASH_MEMORY_SIZE       0x40000

/** Accessible NVDS area start spi flash address */
#define FLASH_NVDS_START_ADDRESS  0x3F000

/** Accessible NVDS area spi flash size */
#define FLASH_NVDS_SIZE         0x1000

/** Flash memory sector size 4 KBytes */
#define FLASH_SECTOR_SIZE       0x1000

/** Flash memory page size: 256 Bytes */
#define FLASH_PAGE_SIZE         0x100

/** Flash sector Mask */
#define FLASH_SECT_MASK         0xFFF000

/** Flash page mask */
#define FLASH_PAGE_MASK         0xFFFF00

/** SPI flash write enable */
#define SPI_FLASH_CMD_WRITE_ENABLE      0x06
/** SPI flash write disable */
#define SPI_FLASH_CMD_WRITE_DISABLE     0x04
/** SPI flash read identification */
#define SPI_FLASH_CMD_READ_ID           0x9F
/** SPI flash read status register */
#define SPI_FLASH_CMD_READ_STATUS       0x05
/** SPI flash write status register */
#define SPI_FLASH_CMD_WRITE_STATUS      0x01
/** SPI flash read data bytes */
#define SPI_FLASH_CMD_READ_DATA         0x03
/** SPI flash read data bytes at higher speed */
#define SPI_FLASH_CMD_READ_HIGH_SPEED   0x0B
/** SPI flash page program */
#define SPI_FLASH_CMD_PAGE_PROGRAM      0x02
/** SPI flash sector erase */
#define SPI_FLASH_CMD_SECTOR_ERASE      0x20
/** SPI flash bulk erase */
#define SPI_FLASH_CMD_BULK_ERASE        0xC7
/** SPI flash deep power-down */
#define SPI_FLASH_CMD_ENTER_LOW_POWER   0xB9
/** SPI flash release from deep power down */
#define SPI_FLASH_CMD_LEAVE_LOW_POWER   0xAB

/** SPI flash direction: send command */
#define SPI_FLASH_DIRECTION_CMD         0x01
/** SPI flash direction: program or erase */
#define SPI_FLASH_DIRECTION_PRO         0x0F
/** SPI flash direction: read data */
#define SPI_FLASH_DIRECTION_READ        0x1F

/** \name SPI flash callback config
 * @{
 */
void spi_flash_init(void) ;
/** @}*/

/** \name SPI flash read/write/erase operation
 * @{
 */
uint32_t spi_flash_rdid(void);
void spi_flash_read(uint8_t *read_buf, uint32_t flash_addr, uint32_t size);
int8_t spi_flash_write(void *write_buf, uint32_t flash_addr, uint32_t size);
void spi_flash_sector_erase(uint32_t flash_addr);
uint8_t spi_flash_erase(uint32_t start_offset, uint32_t size);
void spi_flash_enter_low_power_mode(void);
void spi_flash_leave_low_power_mode(void);
void spi_flash_clock_init(void);
void spi_flash_turn_off(void);
void spi_flash_turn_on(void);
/** @}*/

/** @}*/

#ifdef __cplusplus
}
#endif


/**
 * \page asfdoc_samb_spi_flash_extra Extra Information for SPI Flash Driver
 *
 * \section asfdoc_samb_spi_flash_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>SPI Flash</td>
 *		<td>Serial Peripheral Interface Flash</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_samb_spi_flash_extra_dependencies Dependencies
 * There are no dependencies related to this driver.
 *
 *
 * \section asfdoc_samb_spi_flash_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_samb_spi_flash_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_samb_spi_flash_exqsg Examples for SPI Flash Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_samb_spi_flash_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_samb_spi_flash_basic_use_case
 *
 * \page asfdoc_samb_spi_flash_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>A</td>
 *		<td>09/2015</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

#endif
