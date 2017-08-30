/**
 * \file
 *
 * \brief Management of the AT45DBX DataFlash component.
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
#ifndef _AT45DBX_H_
#define _AT45DBX_H_

#include "conf_at45dbx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup at45dbx_group AT45dbx DataFlash component driver.
 *
 * This is a driver for the AT45dbX series DataFlash memories.
 * It provides functions for initialization, read and write operations at
 * byte or sector level.
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref asfdoc_samd20_sercom_spi_group for SPI interface.
 *
 * @{
 */
//_____ D E F I N I T I O N S ______________________________________________

/*! \name Available AT45DBX Sizes
 *
 * Number of address bits of available AT45DBX data flash memories.
 *
 * \note All memories from page sizes of 256 bytes to 1024 bytes are
 *       supported.
 */
//! @{
#define AT45DBX_500KB           19
#define AT45DBX_1MB             20
#define AT45DBX_2MB             21
#define AT45DBX_4MB             22
#define AT45DBX_8MB             23
//! @}

//! Number of bits for addresses within sectors.
#define AT45DBX_SECTOR_BITS     9

//! Sector size in bytes.
#define AT45DBX_SECTOR_SIZE     (1 << AT45DBX_SECTOR_BITS)


//_____ D E C L A R A T I O N S ____________________________________________

/*! \name Control Functions
 */
//! @{

/*! \brief Initializes the data flash controller and the SPI channel by which
 *         the DF is controlled.
 *
 * \retval true Success.
 * \retval false Failure.
 */
extern bool at45dbx_init(void);

/*! \brief Performs a memory check on all DataFlash memories.
 *
 * \retval true Success.
 * \retval false Failure.
 */
extern bool at45dbx_mem_check(void);

/*! \brief Opens a DataFlash memory in read mode at a given sector.
 *
 * \param sector  Start sector.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note Sector may be page-unaligned (depending on the DataFlash page size).
 */
extern bool at45dbx_read_sector_open(uint32_t sector);

/*! \brief Opens a DataFlash memory in read mode at a given byte address.
 *
 * \param ad  Start address.
 *
 * \retval true Success.
 * \retval false Failure.
 */
extern bool at45dbx_read_byte_open(uint32_t ad);


/*! \brief Unselects the current DataFlash memory.
 */
extern void at45dbx_read_close(void);

/*! \brief This function opens a DataFlash memory in write mode at a given sector.
 *
 * \param sector  Start sector.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note Sector may be page-unaligned (depending on the DF page size).
 *
 * \note If \ref AT45DBX_PAGE_SIZE > \ref AT45DBX_SECTOR_SIZE, page content is
 *       first loaded in buffer to then be partially updated by write byte or
 *       write sector functions.
 */
extern bool at45dbx_write_sector_open(uint32_t sector);

/*! \brief This function opens a DataFlash memory in write mode at a given address.
 *
 * \param ad  Start address.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 */
extern bool at45dbx_write_byte_open(uint32_t ad);

/*! \brief Fills the end of the current logical sector and launches page programming.
 */
extern void at45dbx_write_close(void);

//! @}


/*! \name Single-Byte Access Functions
 */
//! @{

/*! \brief Performs a single byte read from DataFlash memory.
 *
 * \return The read byte.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_read_byte_open
 *       function.
 */
extern uint8_t at45dbx_read_byte(void);

/*! \brief Performs a single byte write to DataFlash memory.
 *
 * \param b The byte to write.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_write_byte_open
 *       function.
 */
extern bool at45dbx_write_byte(uint8_t b);

//! @}




/*! \name Single-Sector Access Functions
 */
//! @{

/*! \brief Reads one DataFlash sector to a RAM buffer.
 *
 * Data flow is: DataFlash -> RAM.
 *
 * \param ram Pointer to RAM buffer.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_read_sector_open
 *       function.
 */
extern bool at45dbx_read_sector_to_ram(void *ram);

/*! \brief Writes one DataFlash sector from a RAM buffer.
 *
 * Data flow is: RAM -> DataFlash.
 *
 * \param ram Pointer to RAM buffer.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_write_sector_open
 *       function.
 */
extern bool at45dbx_write_sector_from_ram(const void *ram);

//! @}

/*! \name Functions to connect the DataFlash driver with the SPI Multiple-Sector Access Functions
 */
//! @{
extern void at45dbx_spi_init(void);
extern void at45dbx_spi_select_device(uint8_t mem_id);
extern void at45dbx_spi_deselect_device(uint8_t mem_id);
extern void at45dbx_spi_write_byte(uint8_t data);
extern void at45dbx_spi_read_byte(uint8_t *data);
extern void at45dbx_spi_read_packet(void const *data, size_t len);
extern void at45dbx_spi_write_packet(void const *data, size_t len);
//! @}

//! @}

/**
 * \internal
 * \brief Check the address passed is valid.
 *
 * Driver-internal function for checking the DataFlash address is in memory
 * range configuration.
 *
 * \param  address  The address to be checked
 *
 * \return true when the address is valid, false when out of memory range.
 */
static inline bool at45dbx_check_address(uint32_t address)
{
	if (address > (((uint32_t)1<<AT45DBX_MEM_SIZE)*AT45DBX_MEM_CNT)) {
		return false;
	} else {
		return true;
	}
}

#ifdef __cplusplus
}
#endif

#endif  // _AT45DBX_H_
