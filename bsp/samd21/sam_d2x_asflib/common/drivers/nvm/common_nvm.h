/**
 * \file
 *
 * \brief Non volatile memories management
 *
 * Copyright (c) 2012-2015 Atmel Corporation. All rights reserved.
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

#ifndef COMMON_NVM_H_INCLUDED
#define COMMON_NVM_H_INCLUDED

#include "compiler.h"
#include "conf_board.h"
#include "parts.h"
#include "status_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
#include "at45dbx.h"
#endif

/* ! \name Non volatile memory types */
/* ! @{ */
typedef enum {
	INT_FLASH     /* !< Internal Flash */

#if (XMEGA || UC3 || SAM4S)
	, INT_USERPAGE  /* !< Userpage/User signature */
#endif

#if XMEGA
	, INT_EEPROM    /* !< Internal EEPROM */
#endif

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	, AT45DBX        /* !< External AT45DBX dataflash */
#endif
} mem_type_t;
/* ! @} */

#if SAM
#       ifndef IFLASH_PAGE_SIZE
#               define IFLASH_PAGE_SIZE IFLASH0_PAGE_SIZE
#       endif

#       ifndef IFLASH_ADDR
#               define IFLASH_ADDR IFLASH0_ADDR
#       endif
#endif

/**
 * \defgroup nvm_group NVM service
 *
 * See \ref common_nvm_quickstart.
 *
 * This is the common API for non volatile memories. Additional features are
 * available
 * in the documentation of the specific modules.
 *
 */

/**
 * \brief Initialize the non volatile memory specified.
 *
 * \param mem Type of non volatile memory to initialize
 */
status_code_t nvm_init(mem_type_t mem);

/**
 * \brief Read single byte of data.
 *
 * \param mem Type of non volatile memory to read
 * \param address Address to read
 * \param data Pointer to where to store the read data
 */
status_code_t nvm_read_char(mem_type_t mem, uint32_t address, uint8_t *data);

/**
 * \brief Write single byte of data.
 *
 * \note For SAM4S internal flash, the page existed in the address must be erased first
 *  before written, and the minimum write unit is a page,thus when writing a single
 *  byte, a whole page that contains the data is writen.
 *
 * \param mem Type of non volatile memory to write
 * \param address Address to write
 * \param data Data to be written
 */
status_code_t nvm_write_char(mem_type_t mem, uint32_t address, uint8_t data);

/**
 * \brief Read \a len number of bytes from address \a address in non volatile
 * memory \a mem and store it in the buffer \a buffer
 *
 * \param mem Type of non volatile memory to read
 * \param address Address to read
 * \param buffer Pointer to destination buffer
 * \param len Number of bytes to read
 */
status_code_t nvm_read(mem_type_t mem, uint32_t address, void *buffer,
		uint32_t len);

/**
 * \brief Write \a len number of bytes at address \a address in non volatile
 * memory \a mem from the buffer \a buffer
 *
 * \note For SAM4S internal flash, the page existed in the address must be erased
 *  first before written.
 *
 * \param mem Type of non volatile memory to write
 * \param address Address to write
 * \param buffer Pointer to source buffer
 * \param len Number of bytes to write
 */
status_code_t nvm_write(mem_type_t mem, uint32_t address, void *buffer,
		uint32_t len);

/**
 * \brief Erase a page in the non volatile memory.
 *
 * The function is only available for internal flash and/or userpage signature.
 *
 * \note For SAM4S internal flash erase, the minimum erase unit is 8 pages.
 *
 * \param mem Type of non volatile memory to erase
 * \param page_number Page number to erase
 */
status_code_t nvm_page_erase(mem_type_t mem, uint32_t page_number);

/**
 * \brief Get the size of whole non volatile memory specified.
 *
 * \param mem Type of non volatile memory
 * \param size Pointer to where to store the size
 */
status_code_t nvm_get_size(mem_type_t mem, uint32_t *size);

/**
 * \brief Get the size of a page in the non volatile memory specified.
 *
 * \param mem Type of non volatile memory
 * \param size Pointer to where to store the size
 */
status_code_t nvm_get_page_size(mem_type_t mem, uint32_t *size);

/**
 * \brief Get the page number from the byte address \a address.
 *
 * \param mem Type of non volatile memory
 * \param address Byte address of the non volatile memory
 * \param num Pointer to where to store the page number
 */
status_code_t nvm_get_pagenumber(mem_type_t mem, uint32_t address,
		uint32_t *num);

/**
 * \brief Enable security bit which blocks external read and write access
 * to the device.
 *
 */
status_code_t nvm_set_security_bit(void);

/**
 * \page common_nvm_quickstart Quick Start quide for common NVM driver
 *
 * This is the quick start quide for the \ref nvm_group "Common NVM driver",
 * with step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section nvm_basic_use_case Basic use case
 * In this basic use case, NVM driver is configured for Internal Flash
 *
 * \section nvm_basic_use_case_setup Setup steps
 *
 * \subsection nvm_basic_use_case_setup_code Example code
 * Add to you application C-file:
 * \code
	if(nvm_init(INT_FLASH) == STATUS_OK)
	  do_something();
\endcode
 *
 * \subsection nvm_basic_use_case_setup_flow Workflow
 * -# Ensure that board_init() has configured selected I/Os for TWI function
 * when using external AT45DBX dataflash
 * -# Ensure that \ref conf_nvm.h is present for the driver.
 *   - \note This file is only for the driver and should not be included by the
 * user.
 * -# Call nvm_init \code nvm_init(INT_FLASH); \endcode
 * and optionally check its return code
 *
 * \section nvm_basic_use_case_usage Usage steps
 * \subsection nvm_basic_use_case_usage_code_writing Example code: Writing to
 * non volatile memory
 * Use in the application C-file:
 * \code
	   uint8_t buffer[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};

	   if(nvm_write(INT_FLASH, test_address, (void *)buffer, sizeof(buffer)) ==
	 STATUS_OK)
	     do_something();
\endcode
 *
 * \subsection nvm_basic_use_case_usage_flow Workflow
 * -# Prepare the data you want to send to the non volatile memory
 *   \code uint8_t buffer[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE}; \endcode
 * -# Call nvm_write \code nvm_write(INT_FLASH, test_address, (void *)buffer,
	 sizeof(buffer)) \endcode
 * and optionally check its return value for STATUS_OK.
 *
 * \subsection nvm_basic_use_case_usage_code_reading Example code: Reading from
 * non volatile memory
 * Use in application C-file:
 * \code
	   uint8_t data_read[8];

	   if(nvm_read(INT_FLASH, test_address, (void *)data_read, sizeof(data_read))
	 == STATUS_OK) {
	     //Check read content
	     if(data_read[0] == 0xAA)
	       do_something();
	   }
\endcode
 *
 * \subsection nvm_basic_use_case_usage_flow Workflow
 * -# Prepare a data buffer that will read data from non volatile memory
 *   \code uint8_t data_read[8]; \endcode
 * -# Call nvm_read \code nvm_read(INT_FLASH, test_address, (void *)data_read,
	 sizeof(data_read)); \endcode
 * and optionally check its return value for STATUS_OK.
 * The data read from the non volatile memory are in data_read.
 *
 * \subsection nvm_basic_use_case_usage_code_erasing Example code: Erasing a
 * page of non volatile memory
 * Use in the application C-file:
 * \code
	if(nvm_page_erase(INT_FLASH, test_page) == STATUS_OK)
	  do_something();
\endcode
 *
 * \subsection nvm_basic_use_case_usage_flow Workflow
 * -# Call nvm_page_erase \code nvm_page_erase(INT_FLASH, test_page) \endcode
 * and optionally check its return value for STATUS_OK.
 *
 * \subsection nvm_basic_use_case_usage_code_config Example code: Reading
 *configuration of non volatile memory
 * Use in application C-file:
 * \code
	   uint8_t mem_size, page_size, page_num;

	   nvm_get_size(INT_FLASH, &mem_size);
	   nvm_get_page_size(INT_FLASH, &page_size);
	   nvm_get_pagenumber(INT_FLASH, test_address, &page_num);
\endcode
 *
 * \subsection nvm_basic_use_case_usage_flow Workflow
 * -# Prepare a buffer to store configuration of non volatile memory
 *   \code uint8_t mem_size, page_size, page_num; \endcode
 * -# Call nvm_get_size \code nvm_get_size(INT_FLASH, &mem_size); \endcode
 * and optionally check its return value for STATUS_OK.
 * The memory size of the non volatile memory is in mem_size.
 * -# Call nvm_get_page_size \code nvm_get_page_size(INT_FLASH, &page_size);
\endcode
 * and optionally check its return value for STATUS_OK.
 * The page size of the non volatile memory is in page_size.
 * -# Call nvm_get_pagenumber \code nvm_get_page_number(INT_FLASH, test_address,
	 &page_num); \endcode
 * and optionally check its return value for STATUS_OK.
 * The page number of given address in the non volatile memory is in page_num.
 *
 * \subsection nvm_basic_use_case_usage_code_locking Example code: Enabling
 * security bit
 * Use in the application C-file:
 * \code
	if(nvm_set_security_bit() == STATUS_OK)
	  do_something();
\endcode
 *
 * \subsection nvm_basic_use_case_usage_flow Workflow
 * -# Call nvm_set_security_bit \code nvm_set_security_bit() \endcode
 * and optionally check its return value for STATUS_OK.
 */

#ifdef __cplusplus
}
#endif

#endif /* COMMON_NVM_H_INCLUDED */
