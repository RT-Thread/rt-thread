/**
 * \file
 *
 * \brief SPI Master Mode management
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
#ifndef SPI_MASTER_H_INCLUDED
#define SPI_MASTER_H_INCLUDED

#include <parts.h>

#if XMEGA
# include "xmega_spi/spi_master.h"
#elif MEGA_RF
# include "megarf_spi/spi_master.h"
#elif UC3
# include "uc3_spi/spi_master.h"
#elif SAM
# include "sam_spi/spi_master.h"
#else
# error Unsupported chip type
#endif

/**
 *
 * \defgroup spi_group Serial Peripheral Interface (SPI)
 *
 * This is the common API for SPI interface. Additional features are available
 * in the documentation of the specific modules.
 *
 * \section spi_group_platform Platform Dependencies
 *
 * The SPI API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behavior. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - spi_master_init()
 *   - spi_master_setup_device()
 *   - spi_select_device()
 *   - spi_deselect_device()
 *   - spi_write_single()
 *   - spi_write_packet()
 *   - spi_read_single()
 *   - spi_read_packet()
 *   - spi_is_tx_empty()
 *   - spi_is_tx_ready()
 *   - spi_is_rx_full()
 *   - spi_is_rx_ready()
 *   - spi_enable()
 *   - spi_disable()
 *   - spi_is_enabled()
 *
 * \section spi_master_quickstart_section Quick Start Guide
 * See \ref common_spi_master_quickstart
 * @{
 */

//! @}

/**
 * \page common_spi_master_quickstart Quick Start Guide for the SPI Master Driver
 *
 * This is the quick start guide for the \ref spi_group "SPI Driver", with
 * step-by-step instructions on how to configure and use the driver for a
 * specific use case.
 *
 * The use case contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * The steps for setting up the SPI master for XMEGA and UC3 use exactly the
 * same approach, but note that there are different names on the peripherals. So
 * to use this Quick Start for UC3 please make sure that all the peripheral
 * names are updated according to the UC3 datasheet.
 * - \subpage spi_master_xmega
 *
 */
/**
 * \page spi_master_xmega Basic setup for SPI master on XMEGA devices
 *
 * \section spi_master_xmega_basic Basic setup for XMEGA devices
 * The SPI module will be set up as master:
 *  - SPI on PORTD
 *  - 1MHz SPI clock speed
 *  - Slave Chip Select connected on PORTD pin 1
 *  - SPI mode 0 (data on rising clock edge)
 *
 * \section   spi_master_xmega_basic_setup Setup steps
 * \subsection spi_master_xmega_basic_setup_code Example code
 * Add to application C-file (e.g. main.c):
 * \code
	   void spi_init_pins(void)
	   {
	       ioport_configure_port_pin(&PORTD, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);

	       ioport_configure_port_pin(&PORTD, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	       ioport_configure_port_pin(&PORTD, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	       ioport_configure_port_pin(&PORTD, PIN6_bm, IOPORT_DIR_INPUT);
	       ioport_configure_port_pin(&PORTD, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	   }

	   void spi_init_module(void)
	   {
	      struct spi_device spi_device_conf = {
	          .id = IOPORT_CREATE_PIN(PORTD, 1)
	      };

	      spi_master_init(&SPID);
	      spi_master_setup_device(&SPID, &spi_device_conf, SPI_MODE_0, 1000000, 0);
	      spi_enable(&SPID);
	   }
\endcode
 *
 * \subsection spi_master_xmega_basic_setup Workflow
 * -# Ensure that \ref conf_spi_master.h is present for the driver.
 *  - \note This file is only for the driver and should not be included by the
 * user. In this example the file can be left empty.
 * -# Initialize the pins used by the SPI interface (this initialization is for
 * the ATxmega32A4U device).
 *  -# Set the pin used for slave select as output high:
 *    \code
	ioport_configure_port_pin(&PORTD, PIN1_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
\endcode
 *  -# Enable pull-up on own chip select (SS):
 *    \code
	ioport_configure_port_pin(&PORTD, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
\endcode
 *    \attention If this pin is pulled low the SPI module will go into slave mode.
 *  -# Set MOSI and SCL as output high, and set MISO as input:
 *    \code
	ioport_configure_port_pin(&PORTD, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTD, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTD, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
\endcode
 * -# Define the SPI device configuration struct to describe which pin the
 * slave select (slave chip select) is connected to, in this case the slave
 * select pin has been connected to PORTD pin 1 (PD1):
 *  - \code
	struct spi_device spi_device_conf = {
	    .id = IOPORT_CREATE_PIN(PORTD, 1)
	};
\endcode
 * -# Initialize the SPI module, in this case SPI on PORTD has been chosen:
 *  - \code
	spi_master_init(&SPID);
\endcode
 * -# Setup the SPI master module for a specific device:
 *  - \code
	spi_master_setup_device(&SPID, &spi_device_conf, SPI_MODE_0, 1000000, 0);
\endcode
 *  - \note The last argument, which is zero in this case, can be ignored and is
 *  only included for compatibility purposes.
 * -# Then enable the SPI:
 *  - \code
	spi_enable(&SPID);
\endcode
 *
 * \section spi_master_xmega_basic_usage Usage steps
 * \subsection spi_master_xmega_basic_usage_code Example code
 * Add to, e.g., the main loop in the application C-file:
 * \code
	   uint8_t data_buffer[1] = {0xAA};

	   struct spi_device spi_device_conf = {
	       .id = IOPORT_CREATE_PIN(PORTD, 1)
	   };

	   spi_select_device(&SPID, &spi_device_conf);

	   spi_write_packet(&SPID, data_buffer, 1);
	   spi_read_packet(&SPID, data_buffer, 1);

	   spi_deselect_device(&SPID, &spi_device_conf);
\endcode
 *
 * \subsection spi_master_xmega_basic_usage_flow Workflow
 * -# Create a buffer for data to be sent/received on the SPI bus, in this case
 * a single byte buffer is used. The buffer can be of arbitrary size as long as
 * there is space left in SRAM:
 *  - \code
	uint8_t data_buffer[1] = {0xAA};
\endcode
 * -# Define the SPI device configuration struct to describe which pin the
 * slave select (slave chip select) is connected to, in this case the slave
 * select pin has been connected to PORTD pin 1 (PD1):
 *  - \code
	struct spi_device spi_device_conf = {
	    .id = IOPORT_CREATE_PIN(PORTD, 1)
	};
\endcode
 *  - \note As this struct is the same for both the initializing part and the usage
 * part it could be a good idea to make the struct global, and hence accessible
 * for both the initializing part and usage part. Another solution could be to
 * create the struct in the main function and pass the address of the struct to
 * the spi_init_module() function, e.g.:
 *  \code
	   void spi_init_module(struct spi_device *spi_device_conf)
	   {
	       ...

	       spi_master_setup_device(&SPID, spi_device_conf, SPI_MODE_0, 1000000, 0);

	       ...
	   }
\endcode
 * -# Write data to the SPI slave device, in this case write one byte from the
 * data_buffer:
 *  - \code
	spi_write_packet(&SPID, data_buffer, 1);
\endcode
 * -# Read data from the SPI slave device, in this case read one byte and put it
 * into the data_buffer:
 *  - \code
	spi_read_packet(&SPID, data_buffer, 1);
\endcode
 *  - \attention As the SPI works as a shift register so that data is shifted in at
 * the same time as data is shifted out a read operation will mean that a dummy
 * byte \ref CONFIG_SPI_MASTER_DUMMY is written to the SPI bus. \ref CONFIG_SPI_MASTER_DUMMY
 * defaults to 0xFF, but can be changed by defining it inside the \ref conf_spi_master.h
 * file.
 * -# When read and write operations is done de-select the slave:
 *  - \code
	spi_deselect_device(&SPID, &spi_device_conf);
\endcode
 *
 */

#endif /* SPI_MASTER_H_INCLUDED */
