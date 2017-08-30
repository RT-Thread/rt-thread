/**
 * \file
 *
 * \brief Common SPI interface for SD/MMC stack
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
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

#ifndef SD_MMC_SPI_H_INCLUDED
#define SD_MMC_SPI_H_INCLUDED

#include "compiler.h"
#include "sd_mmc_protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup sd_mmc_stack_group
 * \defgroup sd_mmc_stack_spi Common SPI interface for SD/MMC stack
 * @{
 */

//! Type of return error code
typedef uint8_t sd_mmc_spi_errno_t;

//! \name Return error codes
//! @{
#define SD_MMC_SPI_NO_ERR                 0 //! No error
#define SD_MMC_SPI_ERR                    1 //! General or an unknown error
#define SD_MMC_SPI_ERR_RESP_TIMEOUT       2 //! Timeout during command
#define SD_MMC_SPI_ERR_RESP_BUSY_TIMEOUT  3 //! Timeout on busy signal of R1B response
#define SD_MMC_SPI_ERR_READ_TIMEOUT       4 //! Timeout during read operation
#define SD_MMC_SPI_ERR_WRITE_TIMEOUT      5 //! Timeout during write operation
#define SD_MMC_SPI_ERR_RESP_CRC           6 //! Command CRC error
#define SD_MMC_SPI_ERR_READ_CRC           7 //! CRC error during read operation
#define SD_MMC_SPI_ERR_WRITE_CRC          8 //! CRC error during write operation
#define SD_MMC_SPI_ERR_ILLEGAL_COMMAND    9 //! Command not supported
#define SD_MMC_SPI_ERR_WRITE             10 //! Error during write operation
#define SD_MMC_SPI_ERR_OUT_OF_RANGE      11 //! Data access out of range
//! @}


/** \brief Return the error code of last function
 *
 * \return error code
 */
sd_mmc_spi_errno_t sd_mmc_spi_get_errno(void);

/** \brief Initializes the low level driver
 *
 * This enable the clock required and the hardware interface.
 */
void sd_mmc_spi_init(void);

/** \brief Return the maximum bus width of a slot
 *
 * \param slot     Selected slot
 *
 * \return 1, 4 or 8 lines.
 */
static __inline__ uint8_t sd_mmc_spi_get_bus_width(uint8_t slot) {
	UNUSED(slot);
	return 1;
}

/** \brief Return the high speed capability of the driver
 *
 * \return true, if the high speed is supported
 */
static __inline__ bool sd_mmc_spi_is_high_speed_capable(void) {
	return false;
}

/**
 * \brief Select a slot and initialize it
 *
 * \param slot       Selected slot
 * \param clock      Maximum clock to use (Hz)
 * \param bus_width  Bus width to use (1, 4 or 8)
 * \param high_speed true, to enable high speed mode
 */
void sd_mmc_spi_select_device(uint8_t slot, uint32_t clock, uint8_t bus_width,
		bool high_speed);

/**
 * \brief Deselect a slot
 *
 * \param slot       Selected slot
 */
void sd_mmc_spi_deselect_device(uint8_t slot);

/** \brief Send 74 clock cycles on the line of selected slot
 * Note: It is required after card plug and before card install.
 */
void sd_mmc_spi_send_clock(void);

/** \brief Send a command on the selected slot
 *
 * \param cmd        Command definition
 * \param arg        Argument of the command
 *
 * \return true if success, otherwise false
 */
bool sd_mmc_spi_send_cmd(sdmmc_cmd_def_t cmd, uint32_t arg);

/** \brief Return the 32 bits response of the last command
 *
 * \return 32 bits response
 */
uint32_t sd_mmc_spi_get_response(void);
static __inline__ void sd_mmc_spi_get_response_128(uint8_t *resp) {
	UNUSED(resp);
	return;
}


/** \brief Send a adtc command on the selected slot
 * A adtc command is used for read/write access.
 *
 * \param cmd          Command definition
 * \param arg          Argument of the command
 * \param block_size   Block size used for the transfer
 * \param nb_block     Total number of block for this transfer
 * \param access_block if true, the x_read_blocks() and x_write_blocks()
 * functions must be used after this function.
 * If false, the mci_read_word() and mci_write_word()
 * functions must be used after this function.
 *
 * \return true if success, otherwise false
 */
bool sd_mmc_spi_adtc_start(sdmmc_cmd_def_t cmd, uint32_t arg,
		uint16_t block_size, uint16_t nb_block, bool access_block);

/** \brief Send a command to stop a adtc command on the selected slot
 *
 * \param cmd        Command definition
 * \param arg        Argument of the command
 *
 * \return true if success, otherwise false
 */
bool sd_mmc_spi_adtc_stop(sdmmc_cmd_def_t cmd, uint32_t arg);

/** \brief Read a word on the line
 *
 * \param value  Pointer on a word to fill
 *
 * \return true if success, otherwise false
 */
bool sd_mmc_spi_read_word(uint32_t* value);

/** \brief Write a word on the line
 *
 * \param value  Word to send
 *
 * \return true if success, otherwise false
 */
bool sd_mmc_spi_write_word(uint32_t value);

/** \brief Start a read blocks transfer on the line
 * Note: The driver will use the DMA available to speed up the transfer.
 *
 * \param dest       Pointer on the buffer to fill
 * \param nb_block   Number of block to transfer
 *
 * \return true if started, otherwise false
 */
bool sd_mmc_spi_start_read_blocks(void *dest, uint16_t nb_block);

/** \brief Wait the end of transfer initiated by mci_start_read_blocks()
 *
 * \return true if success, otherwise false
 */
bool sd_mmc_spi_wait_end_of_read_blocks(void);

/** \brief Start a write blocks transfer on the line
 * Note: The driver will use the DMA available to speed up the transfer.
 *
 * \param src        Pointer on the buffer to send
 * \param nb_block   Number of block to transfer
 *
 * \return true if started, otherwise false
 */
bool sd_mmc_spi_start_write_blocks(const void *src, uint16_t nb_block);

/** \brief Wait the end of transfer initiated by mci_start_write_blocks()
 *
 * \return true if success, otherwise false
 */
bool sd_mmc_spi_wait_end_of_write_blocks(void);

//! @}

#ifdef __cplusplus
}
#endif

#endif /* SD_MMC_SPI_H_INCLUDED */
