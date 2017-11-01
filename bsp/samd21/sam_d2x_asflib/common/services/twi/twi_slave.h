/**
 * \file
 *
 * \brief TWI Slave Mode management
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
#ifndef TWI_SLAVE_H_INCLUDED
#define TWI_SLAVE_H_INCLUDED

#include <parts.h>
#include <compiler.h>

#if (SAM3S || SAM3U || SAM3N || SAM3XA || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP)
# include "sam_twi/twi_slave.h"
#elif XMEGA
# include "xmega_twi/twi_slave.h"
#elif MEGA_RF
# include "megarf_twi/twi_slave.h"
#elif (defined(__GNUC__) && defined(__AVR32__)) || (defined(__ICCAVR32__) || defined(__AAVR32__))
#if (defined AVR32_TWI)
#error Not supported.
#endif
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
 * \section twi_group_platform Platform Dependencies
 *
 * The twi API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behaviour. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - twi_slave_setup()
 *   - twi_slave_enable()
 *   - twi_slave_disable()
 *   - twi_slave_read()
 *   - twi_slave_write()
 *
 * @{
 */

/**
 * \typedef twi_slave_t
 * This type can be used independently to refer to TWI slave module for the
 * architecture used. It refers to the correct type definition for the
 * architecture, ie. TWI_t* for XMEGA or avr32_twi_t* for UC3
 */

//! @}

#endif /* TWI_SLAVE_H_INCLUDED */
