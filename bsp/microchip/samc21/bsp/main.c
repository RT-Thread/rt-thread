/**
 * \file
 *
 * \brief RWWEE Flash Array Read-Write Example
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <atmel_start.h>
#include "driver_init.h"

static uint8_t src_buff[128];
static uint8_t chk_buff[128];

/**
 * Example of using FLASH to read and write Flash RWWEE array.
 */
void rww_flash(void)
{
	uint32_t page_size;
	uint16_t i;
	bool     is_corrupted = false;

	/* Init source data */
	page_size = _rww_flash_get_page_size(&FLASH_0.dev);

	for (i = 0; i < page_size; i++) {
		src_buff[i] = i;
	}

	/* Write data to RWWEE flash */
	if (_rww_flash_write(&FLASH_0.dev, NVMCTRL_RWW_EEPROM_ADDR, src_buff, page_size) != ERR_NONE) {
		printf("RWW flash write failed.");
	}

	/* Read data from RWWEE flash */
	if (_rww_flash_read(&FLASH_0.dev, NVMCTRL_RWW_EEPROM_ADDR, chk_buff, page_size) != ERR_NONE) {
		printf("RWW flash read failed.");
	}

	/* Check data */
	for (i = 0; i < page_size; i++) {
		if (src_buff[i] != chk_buff[i]) {
			is_corrupted = true;
			printf("RWW Flash data verification failed.");
			break;
		}
	}

	if (!is_corrupted) {
		printf("One page Write - Read is successful in RWW Flash memory");
	}
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Read and write Flash RWWEE array */
	rww_flash();

	while (1) {
	}
}
