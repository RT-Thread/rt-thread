/**
 * \file
 *
 * \brief TWI Slave driver for SAM.
 *
 * Copyright (c) 2011-2016 Atmel Corporation. All rights reserved.
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

#ifndef _TWI_SLAVE_H_
#define _TWI_SLAVE_H_

#include "twi.h"
#include "sysclk.h"

typedef Twi *twi_slave_t;

static inline void twi_slave_setup(twi_slave_t p_twi, uint32_t dw_device_addr)
{
#if SAMG55
	if (p_twi == TWI0) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM0);
	} else if (p_twi == TWI1) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM1);
	} else if (p_twi == TWI2) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM2);
	} else if (p_twi == TWI3) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM3);
	} else if (p_twi == TWI4) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM4);
	} else if (p_twi == TWI5) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM5);
	} else if (p_twi == TWI6) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM6);
#ifdef _SAMG55_FLEXCOM7_INSTANCE_
	} else if (p_twi == TWI7) {
		sysclk_enable_peripheral_clock(ID_FLEXCOM7);
#endif /* _SAMG55_FLEXCOM7_INSTANCE_*/
	} else {
		// Do Nothing
	}
#else
#if (!(SAMG51 || SAMG53 || SAMG54))
	if (p_twi == TWI0) {
		sysclk_enable_peripheral_clock(ID_TWI0);
	} else
#endif
	if (p_twi == TWI1) {
		sysclk_enable_peripheral_clock(ID_TWI1);
#if (SAM4N || SAMG)
	} else if (p_twi == TWI2) {
		sysclk_enable_peripheral_clock(ID_TWI2);
#endif
	} else {
		// Do Nothing
	}
#endif

	twi_slave_init(p_twi, dw_device_addr);
}

#define twi_slave_enable(p_twi)  twi_enable_slave_mode(p_twi)

#define twi_slave_disable(p_twi)  twi_disable_slave_mode(p_twi)

#endif // _TWI_SLAVE_H_
