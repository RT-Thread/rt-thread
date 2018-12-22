/**
 * \file
 *
 * \brief TWIHS Slave driver for SAM.
 *
 * Copyright (c) 2013-2015 Atmel Corporation. All rights reserved.
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

#ifndef TWIHS_SLAVE_H_INCLUDED
#define TWIHS_SLAVE_H_INCLUDED

#include "twihs.h"
#include "sysclk.h"

typedef Twihs *twihs_slave_t;

static inline void twihs_slave_setup(twihs_slave_t p_twihs, uint32_t dw_device_addr)
{
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	if (p_twihs == TWIHS0) {
		sysclk_enable_peripheral_clock(ID_TWIHS0);
	} else if (p_twihs == TWIHS1) {
		sysclk_enable_peripheral_clock(ID_TWIHS1);
	} else if (p_twihs == TWIHS2) {
		sysclk_enable_peripheral_clock(ID_TWIHS2);
	} else {
		// Do Nothing
	}
#else
	if (p_twihs == TWI0) {
		sysclk_enable_peripheral_clock(ID_TWI0);
#if SAMG55		
	} else if (p_twihs == TWI1) {
		sysclk_enable_peripheral_clock(ID_TWI1);
	} else if (p_twihs == TWI2) {
		sysclk_enable_peripheral_clock(ID_TWI2);
	} else if (p_twihs == TWI3) {
		sysclk_enable_peripheral_clock(ID_TWI3);
	} else if (p_twihs == TWI4) {
		sysclk_enable_peripheral_clock(ID_TWI4);
	} else if (p_twihs == TWI5) {
		sysclk_enable_peripheral_clock(ID_TWI5);
	} else if (p_twihs == TWI6) {
		sysclk_enable_peripheral_clock(ID_TWI6);
	} else if (p_twihs == TWI7) {
		sysclk_enable_peripheral_clock(ID_TWI7);
#endif		
	} else {
		// Do Nothing
	}
#endif
	twihs_slave_init(p_twihs, dw_device_addr);
}

#define twihs_slave_enable(p_twihs)  twihs_enable_slave_mode(p_twihs)

#define twihs_slave_disable(p_twihs)  twihs_disable_slave_mode(p_twihs)

#endif /* TWIHS_SLAVE_H_INCLUDED */
