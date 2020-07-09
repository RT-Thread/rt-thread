/**
 * \file
 *
 * \brief TWIHS Master Mode management
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
#ifndef TWIHS_MASTER_H_INCLUDED
#define TWIHS_MASTER_H_INCLUDED

#include <parts.h>
#include <compiler.h>

#if (SAMG || SAMV70 || SAMV71 || SAME70 || SAMS70)
# include "sam_twihs/twihs_master.h"
#else
# error Unsupported chip type
#endif

/**
 *
 * \defgroup twihs_group Two Wire-interface High Speed(TWIHS)
 *
 * This is the common API for TWIHS. Additional features are available
 * in the documentation of the specific modules.
 *
 * See \ref twihs_quickstart.
 *
 * \section twihs_group_platform Platform Dependencies
 *
 * The TWIHS API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behaviour. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - Master TWIHS Module initialization
 *   \code status_code_t twihs_master_setup(*twihs_module_pointer, twihs_master_options_t *opt) \endcode
 *   - Enables TWIHS Module
 *   \code void twihs_master_enable(*twihs_module_pointer) \endcode
 *   - Disables TWIHS Module
 *   \code void twihs_master_disable(*twihs_module_pointer) \endcode
 *   - Read data from a slave device
 *   \code status_code_t twihs_master_read(*twihs_module_pointer, twihs_package_t *package) \endcode
 *   - Write data from to a slave device
 *   \code status_code_t twihs_master_write(*twihs_module_pointer, twihs_package_t *package) \endcode
 *
 * @{
 */

/**
 * \typedef twihs_master_t
 * This type can be used independently to refer to TWIHS master module for the
 * architecture used. It refers to the correct type definition for the
 * architecture.
 */

//! @}

/**
 * \page twihs_quickstart Quickstart guide for Common service TWIHS
 *
 * This is the quickstart guide for the \ref twihs_group "Common service TWIHS",
 * with step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section twihs_basic_use_case Basic use case
 * In the most basic use case, the TWIHS module is configured for
 * - Master operation
 * - addressing one slave device of the bus at address 0x50
 * - TWIHS clock of 400kHz
 * - polled read/write handling
 *
 * \section twihs_basic_use_case_setup Setup steps
 * \subsection twihs_basic_use_case_setup_code Example code
 * Add to your application C-file, for example in SAM series chip:
 * \code
	  void twihs_init(void)
	  {
	    twihs_master_options_t opt = {
	        .speed = 400000,
	        .chip  = 0x50
	    };

	    twihs_master_setup(&TWIM0, &opt);
	  }
\endcode
 *
 * \subsection twihs_basic_use_case_setup_flow Workflow
 * -# Ensure that board_init() has configured selected I/Os for TWIHS function.
 * -# Ensure that \ref conf_twim.h is present for the driver.
 *   - \note This file is only for the driver and should not be included by the
 * user.
 * -# Define and initialize config structs for TWIHS module in your TWIHS initialization
 * function, for example in SAM series chip:
 *   - \code
	twihs_master_options_t opt = {
	  .speed = 400000,
	  .chip  = 0x50
	}; \endcode
 *   - field \ref speed sets the baudrate of the TWIHS bus
 *   - field \ref chip sets the address of the slave device you want to communicate with
 * -# Call twihs_master_setup and optionally check its return code
 *   - \note The config structs can be reused for other TWIHS modules
 * after this step. Simply reconfigure and write to others modules.
 *
 * \section twihs_basic_use_case_usage Usage steps
 * \subsection twihs_basic_use_case_usage_code_writing Example code : Writing to a slave device
 * Use in application C-file, for example in SAM series chip:
 * \code
	  const uint8_t test_pattern[] = {0x55,0xA5,0x5A,0x77,0x99};

	  twihs_package_t packet_write = {
	    .addr         = EEPROM_MEM_ADDR,      // TWIHS slave memory address data
	    .addr_length  = sizeof (uint16_t),    // TWIHS slave memory address data size
	    .chip         = EEPROM_BUS_ADDR,      // TWIHS slave bus address
	    .buffer       = (void *)test_pattern, // transfer data source buffer
	    .length       = sizeof(test_pattern)  // transfer data size (bytes)
	  };

	  while (twihs_master_write(&TWIM0, &packet_write) != TWI_SUCCESS);
\endcode
 *
 * \subsection twihs_basic_use_case_usage_flow Workflow
 * -# Prepare the data you want to send to the slave device:
 *   - \code const uint8_t test_pattern[] = {0x55,0xA5,0x5A,0x77,0x99}; \endcode
 * -# Prepare a twihs_package_t structure
 *   \code twihs_package_t packet_write; \endcode
 * Fill all the fields of the structure :
 *  - addr is the address in the slave device
 *  - addr_length is the size of the address in the slave (support for large TWI memory devices)
 *  - chip sets the 7 bit address of the slave device you want to communicate with
 *  - buffer is a pointer on the data to write to slave
 *  - length is the number of data to write
 *
 * -# Finally, call twihs_master_write \code twihs_master_write(&TWIM0, &packet_write); \endcode
 * and optionally check its return value for TWI_SUCCESS.
 * \subsection twihs_basic_use_case_usage_code_reading Example code : Reading from a slave device
 * Use in application C-file, for example in SAM series chip:
 * \code
	   uint8_t data_received[10];

	   twihs_package_t packet_read = {
	     .addr         = EEPROM_MEM_ADDR,      // TWIHS slave memory address data
	     .addr_length  = sizeof (uint16_t),    // TWIHS slave memory address data size
	     .chip         = EEPROM_BUS_ADDR,      // TWIHS slave bus address
	     .buffer       = data_received,        // transfer data destination buffer
	     .length       = 10                    // transfer data size (bytes)
	   };
	   // Perform a multi-byte read access then check the result.
	   if(twihs_master_read(&TWIM0, &packet_read) == TWI_SUCCESS){
	     //Check read content
	     if(data_received[0]==0x55)
	       do_something();
	   }
\endcode
 *
 * \subsection twihs_basic_use_case_usage_flow Workflow
 * -# Prepare a data buffer that will receive the data from the slave device:
 *   \code uint8_t data_received[10]; \endcode
 * -# Prepare a twihs_package_t structure
 *   \code twihs_package_t packet_read; \endcode
 * Fill all the fields of the structure :
 *  - addr is the address in the slave device
 *  - addr_length is the size of the address in the slave (support for large TWI memory devices)
 *  - chip sets the 7 bit address of the slave device you want to communicate with
 *  - buffer is a pointer on the data buffer that will receive the data from the slave device
 *  - length is the number of data to read
 *
 * -# Finally, call twihs_master_read \code twihs_master_read(&TWIM0, &packet_read); \endcode
 * and optionally check its return value for TWI_SUCCESS.
 * the data read from the device are now in data_received.
 */

#endif /* TWI_MASTER_H_INCLUDED */
