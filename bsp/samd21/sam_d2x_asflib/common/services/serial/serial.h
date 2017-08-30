/**
 * \file
 *
 * \brief Serial Mode management
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
#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include <parts.h>
#include "status_codes.h"

/**
 * \typedef usart_if
 *
 * This type can be used independently to refer to USART module for the
 * architecture used. It refers to the correct type definition for the
 * architecture, ie. USART_t* for XMEGA or avr32_usart_t* for UC3.
 */

#if XMEGA
# include "xmega_usart/usart_serial.h"
#elif MEGA_RF
# include "megarf_usart/usart_serial.h"
#elif UC3
# include "uc3_usart/usart_serial.h"
#elif (SAMB)
#include "samb_uart/uart_serial.h"
#elif (SAM0)
#include "sam0_usart/usart_serial.h"
#elif SAM
# include "sam_uart/uart_serial.h"
#else
# error Unsupported chip type
#endif

/**
 *
 * \defgroup serial_group Serial Interface (Serial)
 *
 * See \ref serial_quickstart.
 *
 * This is the common API for serial interface. Additional features are available
 * in the documentation of the specific modules.
 *
 * \section serial_group_platform Platform Dependencies
 *
 * The serial API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behaviour. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - usart_serial_init()
 *   - usart_serial_putchar()
 *   - usart_serial_getchar()
 *   - usart_serial_write_packet()
 *   - usart_serial_read_packet()
 *
 *
 * @{
 */
 
//! @}

/**
 * \page serial_quickstart Quick start guide for Serial Interface service
 *
 * This is the quick start guide for the \ref serial_group "Serial Interface module", with
 * step-by-step instructions on how to configure and use the serial in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section serial_use_cases Serial use cases
 * - \ref serial_basic_use_case
 * - \subpage serial_use_case_1
 *
 * \section serial_basic_use_case Basic use case - transmit a character
 * In this use case, the serial module is configured for:
 * - Using USARTD0
 * - Baudrate: 9600
 * - Character length: 8 bit
 * - Parity mode: Disabled
 * - Stop bit: None
 * - RS232 mode
 *
 * The use case waits for a received character on the configured USART and
 * echoes the character back to the same USART.
 *
 * \section serial_basic_use_case_setup Setup steps
 *
 * \subsection serial_basic_use_case_setup_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (sysclk)"
 *
 * \subsection serial_basic_use_case_setup_code Example code
 * The following configuration must be added to the project (typically to a 
 * conf_uart_serial.h file, but it can also be added to your main application file.)
 *
 * \note The following takes SAM3X configuration for example, other devices have similar
 * configuration, but their parameters may be different, refer to corresponding header files.
 *
 * \code
	#define USART_SERIAL                     &USARTD0
	#define USART_SERIAL_BAUDRATE            9600
	#define USART_SERIAL_CHAR_LENGTH         US_MR_CHRL_8_BIT
	#define USART_SERIAL_PARITY              US_MR_PAR_NO
	#define USART_SERIAL_STOP_BIT            false
\endcode
 *
 * A variable for the received byte must be added:
 * \code uint8_t received_byte; \endcode
 *
 * Add to application initialization:
 * \code
	    sysclk_init();

	    static usart_serial_options_t usart_options = {
	       .baudrate = USART_SERIAL_BAUDRATE,
	       .charlength = USART_SERIAL_CHAR_LENGTH,
	       .paritytype = USART_SERIAL_PARITY,
	       .stopbits = USART_SERIAL_STOP_BIT
	    };

	    usart_serial_init(USART_SERIAL, &usart_options);
\endcode
 *
 * \subsection serial_basic_use_case_setup_flow Workflow
 * -# Initialize system clock:
 *   - \code sysclk_init(); \endcode
 * -# Create serial USART options struct:
 *   - \code
	static usart_serial_options_t usart_options = {
	   .baudrate = USART_SERIAL_BAUDRATE,
	   .charlength = USART_SERIAL_CHAR_LENGTH,
	   .paritytype = USART_SERIAL_PARITY,
	   .stopbits = USART_SERIAL_STOP_BIT
	};
\endcode
 * -# Initialize the serial service:
 *   - \code usart_serial_init(USART_SERIAL, &usart_options);\endcode
 *
 * \section serial_basic_use_case_usage Usage steps
 *
 * \subsection serial_basic_use_case_usage_code Example code
 * Add to application C-file:
 * \code
	usart_serial_getchar(USART_SERIAL, &received_byte);
	usart_serial_putchar(USART_SERIAL, received_byte);
\endcode
 *
 * \subsection serial_basic_use_case_usage_flow Workflow
 * -# Wait for reception of a character:
 *   - \code usart_serial_getchar(USART_SERIAL, &received_byte); \endcode
 * -# Echo the character back:
 *   - \code usart_serial_putchar(USART_SERIAL, received_byte); \endcode
 */

/**
 * \page serial_use_case_1 Advanced use case - Send a packet of serial data
 *
 * In this use case, the USART module is configured for:
 * - Using USARTD0
 * - Baudrate: 9600
 * - Character length: 8 bit
 * - Parity mode: Disabled
 * - Stop bit: None
 * - RS232 mode
 *
 * The use case sends a string of text through the USART.
 *
 * \section serial_use_case_1_setup Setup steps
 *
 * \subsection serial_use_case_1_setup_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (sysclk)"
 *
 * \subsection serial_use_case_1_setup_code Example code
 * The following configuration must be added to the project (typically to a 
 * conf_uart_serial.h file, but it can also be added to your main application file.):
 *
 * \note The following takes SAM3X configuration for example, other devices have similar
 * configuration, but their parameters may be different, refer to corresponding header files.
 *
 * \code
	#define USART_SERIAL                     &USARTD0
	#define USART_SERIAL_BAUDRATE            9600
	#define USART_SERIAL_CHAR_LENGTH         US_MR_CHRL_8_BIT
	#define USART_SERIAL_PARITY              US_MR_PAR_NO
	#define USART_SERIAL_STOP_BIT            false
\endcode
 *
 * Add to application initialization:
 * \code
	    sysclk_init();

	    static usart_serial_options_t usart_options = {
	       .baudrate = USART_SERIAL_BAUDRATE,
	       .charlength = USART_SERIAL_CHAR_LENGTH,
	       .paritytype = USART_SERIAL_PARITY,
	       .stopbits = USART_SERIAL_STOP_BIT
	    };

	    usart_serial_init(USART_SERIAL, &usart_options);
\endcode
 *
 * \subsection serial_use_case_1_setup_flow Workflow
 * -# Initialize system clock:
 *   - \code sysclk_init(); \endcode
 * -# Create USART options struct:
 *   - \code
	static usart_serial_options_t usart_options = {
	   .baudrate = USART_SERIAL_BAUDRATE,
	   .charlength = USART_SERIAL_CHAR_LENGTH,
	   .paritytype = USART_SERIAL_PARITY,
	   .stopbits = USART_SERIAL_STOP_BIT
	};
\endcode
 * -# Initialize in RS232 mode:
 *   - \code usart_serial_init(USART_SERIAL_EXAMPLE, &usart_options); \endcode
 *
 * \section serial_use_case_1_usage Usage steps
 *
 * \subsection serial_use_case_1_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
	usart_serial_write_packet(USART_SERIAL, "Test String", strlen("Test String"));
\endcode
 *
 * \subsection serial_use_case_1_usage_flow Workflow
 * -# Write a string of text to the USART:
 *   - \code usart_serial_write_packet(USART_SERIAL, "Test String", strlen("Test String")); \endcode
 */

#endif /* SERIAL_H_INCLUDED */
