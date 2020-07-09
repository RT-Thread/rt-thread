/**
 * \file
 *
 * \brief TWI Master Mode management
 *
 * Copyright (c) 2010-2015 Atmel Corporation. All rights reserved.
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
#ifndef TWI_MASTER_H_INCLUDED
#define TWI_MASTER_H_INCLUDED

#include <compiler.h>

#if (SAM4L)
# include "sam_twim/twi_master.h"
#elif (SAM3S || SAM3U || SAM3N || SAM3XA || SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM)
# include "sam_twi/twi_master.h"
#elif XMEGA
# include "xmega_twi/twi_master.h"
#elif MEGA_RF
# include "megarf_twi/twi_master.h"
#elif UC3
# if (defined AVR32_TWI)
# include "uc3_twi/twi_master.h"
# else
# include "uc3_twim/twi_master.h"
# endif
#else
# error Unsupported chip type
#endif

/**
 *
 * \defgroup twi_group Two Wire-interface(TWI)
 *
 * This is the common API for TWIs. Additional features are available
 * in the documentation of the specific modules.
 *
 * See \ref twi_quickstart.
 *
 * \section twi_group_platform Platform Dependencies
 *
 * The TWI API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behaviour. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - Master TWI Module initialization
 *   \code status_code_t twi_master_setup(*twi_module_pointer, twi_master_options_t *opt) \endcode
 *   - Enables TWI Module
 *   \code void twi_master_enable(*twi_module_pointer) \endcode
 *   - Disables TWI Module
 *   \code void twi_master_disable(*twi_module_pointer) \endcode
 *   - Read data from a slave device
 *   \code status_code_t twi_master_read(*twi_module_pointer, twi_package_t *package) \endcode
 *   - Write data from to a slave device
 *   \code status_code_t twi_master_write(*twi_module_pointer, twi_package_t *package) \endcode
 *
 * @{
 */

/**
 * \typedef twi_master_t
 * This type can be used independently to refer to TWI master module for the
 * architecture used. It refers to the correct type definition for the
 * architecture, ie. TWI_t* for XMEGA or avr32_twim_t* for UC3
 */

//! @}


/**
 * \page twi_quickstart Quickstart guide for Common service TWI
 *
 * This is the quickstart guide for the \ref twi_group "Common service TWI",
 * with step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section twi_basic_use_case Basic use case
 * In the most basic use case, the TWI module is configured for
 * - Master operation
 * - addressing one slave device of the bus at address 0x50
 * - TWI clock of 50kHz
 * - polled read/write handling
 *
 * \section twi_basic_use_case_setup Setup steps
 * \subsection twi_basic_use_case_setup_code Example code
 * Add to your application C-file:
 * \code
	  void twi_init(void)
	  {
	    twi_master_options_t opt = {
	        .speed = 50000,
	        .chip  = 0x50
	    };

	    twi_master_setup(&TWIM0, &opt);
	  }
\endcode
 *
 * \subsection twi_basic_use_case_setup_flow Workflow
 * -# Ensure that board_init() has configured selected I/Os for TWI function.
 * -# Ensure that \ref conf_twim.h is present for the driver.
 *   - \note This file is only for the driver and should not be included by the
 * user.
 * -# Define and initialize config structs for TWI module in your TWI initialization
 * function:
 *   - \code
	twi_master_options_t opt = {
	  .speed = 50000,
	  .chip  = 0x50
	}; \endcode
 *   - field \ref speed sets the baudrate of the TWI bus
 *   - field \ref chip sets the address of the slave device you want to communicate with
 * -# Call twi_master_setup and optionally check its return code
 *   - \note The config structs can be reused for other TWI modules
 * after this step. Simply reconfigure and write to others modules.
 *
 * \section twi_basic_use_case_usage Usage steps
 * \subsection twi_basic_use_case_usage_code_writing Example code : Writing to a slave device
 * Use in application C-file:
 * \code
	  const uint8_t test_pattern[] = {0x55,0xA5,0x5A,0x77,0x99};

	  twi_package_t packet_write = {
	    .addr         = EEPROM_MEM_ADDR,      // TWI slave memory address data
	    .addr_length  = sizeof (uint16_t),    // TWI slave memory address data size
	    .chip         = EEPROM_BUS_ADDR,      // TWI slave bus address
	    .buffer       = (void *)test_pattern, // transfer data source buffer
	    .length       = sizeof(test_pattern)  // transfer data size (bytes)
	  };

	  while (twi_master_write(&TWIM0, &packet_write) != TWI_SUCCESS);
\endcode
 *
 * \subsection twi_basic_use_case_usage_flow Workflow
 * -# Prepare the data you want to send to the slave device:
 *   - \code const uint8_t test_pattern[] = {0x55,0xA5,0x5A,0x77,0x99}; \endcode
 * -# Prepare a twi_package_t structure
 *   \code twi_package_t packet_write; \endcode
 * Fill all the fields of the structure :
 *  - addr is the address in the slave device
 *  - addr_length is the size of the address in the slave (support for large TWI memory devices)
 *  - chip sets the 7 bit address of the slave device you want to communicate with
 *  - buffer is a pointer on the data to write to slave
 *  - length is the number of data to write
 *
 * -# Finally, call twi_master_write \code twi_master_write(&TWIM0, &packet_write); \endcode
 * and optionally check its return value for TWI_SUCCESS.
 * \subsection twi_basic_use_case_usage_code_reading Example code : Reading from a slave device
 * Use in application C-file:
 * \code
	   uint8_t data_received[10];

	   twi_package_t packet_read = {
	     .addr         = EEPROM_MEM_ADDR,      // TWI slave memory address data
	     .addr_length  = sizeof (uint16_t),    // TWI slave memory address data size
	     .chip         = EEPROM_BUS_ADDR,      // TWI slave bus address
	     .buffer       = data_received,        // transfer data destination buffer
	     .length       = 10                    // transfer data size (bytes)
	   };
	   // Perform a multi-byte read access then check the result.
	   if(twi_master_read(&TWIM0, &packet_read) == TWI_SUCCESS){
	     //Check read content
	     if(data_received[0]==0x55)
	       do_something();
	   }
\endcode
 *
 * \subsection twi_basic_use_case_usage_flow Workflow
 * -# Prepare a data buffer that will receive the data from the slave device:
 *   \code uint8_t data_received[10]; \endcode
 * -# Prepare a twi_package_t structure
 *   \code twi_package_t packet_read; \endcode
 * Fill all the fields of the structure :
 *  - addr is the address in the slave device
 *  - addr_length is the size of the address in the slave (support for large TWI memory devices)
 *  - chip sets the 7 bit address of the slave device you want to communicate with
 *  - buffer is a pointer on the data buffer that will receive the data from the slave device
 *  - length is the number of data to read
 *
 * -# Finally, call twi_master_read \code twi_master_read(&TWIM0, &packet_read); \endcode
 * and optionally check its return value for TWI_SUCCESS.
 * the data read from the device are now in data_received.
 */


#endif /* TWI_MASTER_H_INCLUDED */
