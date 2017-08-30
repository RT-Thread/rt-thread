/**
* \file
*
* \brief AT25DFx SerialFlash driver quick start
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
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
* Atmel microcontroller product.
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

#ifndef QS_AT25DFX_BASIC_H
#define QS_AT25DFX_BASIC_H

/**
* \page asfdoc_common2_at25dfx_basic_use Quick Start Guide for AT25DFx SerialFlash Driver
*
* This quick start will read, unprotect, erase and write bytes to an AT25DF081A
* that is connected to the SPI interface on EXT1 header of SAM D20 Xplained Pro or EXT3 of SAM D21 Xplained Pro.
*
* The SERCOM SPI will be configured with the following settings:
*
* For SAM D20 Xplained Pro
* - 500 kHz baud rate
* - SCK, MISO and MOSI on EXT1 header's SPI pins
*
* For SAM D21 Xplained Pro 
* - 120 kHz baud rate
* - SCK, MISO and MOSI on EXT3
*
* The AT25DFx driver instance will be configured with the following settings:
*
* For SAM D20 Xplained Pro 
* - CS on EXT1 header's SS0 pin
*
* For SAM D21 Xplained Pro 
* - CS on EXT3 PA13
*
*
* \section asfdoc_common2_at25dfx_basic_setup Setup
*
* \subsection asfdoc_common2_at25dfx_basic_prereq Prerequisites
*
* There are no special setup requirements for this use-case.
*
*
* \subsection asfdoc_common2_at25dfx_basic_setup_code Code
*
* Add to the main application source file, outside of any functions:
* \snippet qs_at25dfx_basic.c buffers
* \snippet qs_at25dfx_basic.c driver_instances
*
* Create a new function for initializing the AT25DFx:
* \snippet qs_at25dfx_basic.c init_function
*
* If not already present, add to the initialization code:
* \snippet qs_at25dfx_basic.c init_calls
*
*
* \subsection asfdoc_common2_at25dfx_basic_setup_flow Workflow
*
* -# Create read and write buffers.
*    \snippet qs_at25dfx_basic.c buffers
* -# Create global instances of SPI and AT25DFx chip.
*    \snippet qs_at25dfx_basic.c driver_instances
* -# Create a function to contain the AT25DFx initialization code.
* -# Create local instances of SPI and AT25DFx configurations.
*    \snippet qs_at25dfx_basic.c config_instances
* -# Initialize the SPI for AT25DFx connected to EXT1 header.
*    \snippet qs_at25dfx_basic.c spi_setup
* -# Initialize the AT25DFx instance for AT25DF081A, with Slave Select on the
* SS_0 pin on EXT1.
*    \snippet qs_at25dfx_basic.c chip_setup
*
*
* \section asfdoc_common2_at25dfx_basic_use_case Use Case
*
* \subsection asfdoc_common2_at25dfx_basic_use_case_code Code
*
* Copy into main application:
* \snippet qs_at25dfx_basic.c use_code
*
*
* \subsection asfdoc_common2_at25dfx_basic_use_case_flow Workflow
*
* -# Wakeup serialFlash.
*    \snippet qs_at25dfx_basic.c wake_chip
* -# Check that the SerialFlash is present.
*    \snippet qs_at25dfx_basic.c check_presence
* -# Read out the first \ref AT25DFX_BUFFER_SIZE bytes, starting at the very
* first flash address.
*    \snippet qs_at25dfx_basic.c read_buffer
* -# Disable protection of the second sector.
*    \note This device has sectors with a uniform size of 64 kB, so the address
* \c 0x10000 marks the start of the second sector. This can differ between
* devices.
*
*    \snippet qs_at25dfx_basic.c unprotect_sector
* -# Erase the first 4 kB of the second 64 kB block (64-68 kB range).
*    \snippet qs_at25dfx_basic.c erase_block
* -# Write \ref AT25DFX_BUFFER_SIZE bytes, starting at the beginning of the
* sector and the newly erased memory locations.
*    \snippet qs_at25dfx_basic.c write_buffer
* -# Enable protection of all sectors, to prevent accidental erases of content.
*    \snippet qs_at25dfx_basic.c global_protect
* -# Put SerialFlash device to sleep, to conserve power.
*    \snippet qs_at25dfx_basic.c sleep
*
*/

#endif // QS_AT25DFX_BASIC_H