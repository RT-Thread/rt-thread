/**
 * \file
 *
 * \brief AT30TS(E)75x EEPROM and Temperature Sensor Example.
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
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

/**
 * \page asfdoc_samb_at30tse75x_qs AT30TS(E)75x EEPROM and Temperature Sensor Example
 *
 * \section Purpose
 *
 * The application demonstrates how to access AT30TS(E)75x temperature sensor.
 *
 * \section Requirements
 *
 * This package can be used with:
 * - SAMB11 Xplained Pro board.
 *
 * \section Description
 * There are 2 stages in the example.
 * - In 1st stage, some patterns are written to the specified memory address of
 * the EEPROM in AT30TSE75x. Then the memory is read and checked (note this
 * stage is only for the device which has EEPROM).
 * - In 2nd stage, the temperature sampled by AT30TS(E)75x is read every second.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR EWARM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 * Support and FAQ: http://www.atmel.com/design-support/
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <string.h>
#include "at30tse75x.h"

#define NB_PAGE 16
#define NB_BYTE 16

static uint8_t rx_buffer[NB_BYTE], tx_buffer[NB_BYTE];

static void delay(uint32_t count)
{
	for (uint32_t i = 0; i < count; i++) {
		for (uint32_t j = 0; j < 1000; j++)
			asm volatile ("nop");
	}
}

int main(void)
{
	volatile double temper_value;
	volatile bool data_check_status1 = true,
	              data_check_status2 = true;
	uint32_t i;

	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	/* Initialize AT30TS(E)75x */
	at30tse_init();

	/* First round data check */
	for (i = 0; i < NB_BYTE; i++) {
		tx_buffer[i] = i;
	}

	/* Write pages in EEPROM */
	for (i = 0; i < NB_PAGE; i++) {
		at30tse_eeprom_write(tx_buffer, NB_BYTE, 0, i);
		delay(200);
	}
	
	/* Read each page in EEPROM and compare them */
	for (i = 0; i < NB_PAGE; i++) {
		memset(rx_buffer, 0, NB_BYTE);
		at30tse_eeprom_read(rx_buffer, NB_BYTE, 0, i);
		if (memcmp(tx_buffer, rx_buffer, NB_BYTE)) {
			data_check_status1 = false;
			break;
		}
	}

	/* Second round data check */
	for (i = 0; i < NB_BYTE; i++) {
		tx_buffer[i] = NB_BYTE - i;
	}

	/* Write pages in EEPROM */
	for (i = 0; i < NB_PAGE; i++) {
		at30tse_eeprom_write(tx_buffer, NB_BYTE, 0, i);
		delay(200);
	}
	
	/* Read each page in EEPROM and compare them */
	for (i = 0; i < NB_PAGE; i++) {
		memset(rx_buffer, 0, NB_BYTE);
		at30tse_eeprom_read(rx_buffer, NB_BYTE, 0, i);
		if (memcmp(tx_buffer, rx_buffer, NB_BYTE)) {
			data_check_status2 = false;
			break;
		}
	}

	/* Read thigh and tlow */
	volatile uint16_t thigh = 0;
	thigh = at30tse_read_register(AT30TSE_THIGH_REG,
			AT30TSE_NON_VOLATILE_REG, AT30TSE_THIGH_REG_SIZE);

	volatile uint16_t tlow = 0;
	tlow = at30tse_read_register(AT30TSE_TLOW_REG,
			AT30TSE_NON_VOLATILE_REG, AT30TSE_TLOW_REG_SIZE);
			
	/* Set 12-bit resolution mode. */
	at30tse_write_config_register(
			AT30TSE_CONFIG_RES(AT30TSE_CONFIG_RES_12_bit));

	while (1) {
		/* Read current temperature. */
		temper_value = at30tse_read_temperature();
	}

	UNUSED(data_check_status1);
	UNUSED(data_check_status2);
	UNUSED(temper_value);
	UNUSED(tlow);
	UNUSED(thigh);
}
