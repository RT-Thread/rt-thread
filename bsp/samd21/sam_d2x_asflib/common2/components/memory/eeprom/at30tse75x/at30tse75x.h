/**
 * \file
 *
 * \brief AT30TSE75X driver
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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef AT30TSE75X_H_INCLUDED
#define AT30TSE75X_H_INCLUDED

#include <compiler.h>
#include <i2c_master.h>

/* Temperature sensor configuration file */
#include "conf_at30tse75x.h"

/**
 * \defgroup asfdoc_samb_at30tse75x_group AT30TSE75X Digital Temperature Sensor and Serial EEPROM.
 * This driver provides API for AT30TSE75X temperature sensor and EEPROM
 * through I2C interface.
 *
 * See \ref asfdoc_samb_at30tse75x_qs.
 *
 *
 * \section asfdoc_samb_at30tse75x_dependencies Dependencies
 * This driver depends on the following module:
 * - \ref asfdoc_samb_i2c_group "SAM B11 I2C master"
 *
 * \section asfdoc_samb_at30tse75x_api_overview API Overview
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define AT30TSE_TEMPERATURE_TWI_ADDR	0x48 //0b1001000
#define AT30TSE758_EEPROM_TWI_ADDR		0x50 //0b1010000
#define AT30TSE754_EEPROM_TWI_ADDR		0x50 //0b1010000
#define AT30TSE752_EEPROM_TWI_ADDR		0x50 //0b1010000

#define AT30TSE_TEMPERATURE_REG			0x00
#define AT30TSE_TEMPERATURE_REG_SIZE	2
#define AT30TSE_NON_VOLATILE_REG		0x00
#define AT30TSE_VOLATILE_REG			0x10

#define AT30TSE_CONFIG_REG				0x01
#define AT30TSE_CONFIG_REG_SIZE			2
#define AT30TSE_TLOW_REG				0x02
#define AT30TSE_TLOW_REG_SIZE			2
#define AT30TSE_THIGH_REG				0x03
#define AT30TSE_THIGH_REG_SIZE			2

#define AT30TSE_CONFIG_RES_Pos 			13
#define AT30TSE_CONFIG_RES_Msk 			(0x03 << AT30TSE_CONFIG_RES_Pos)
#define AT30TSE_CONFIG_RES(value) 		((AT30TSE_CONFIG_RES_Msk & ((value) << AT30TSE_CONFIG_RES_Pos)))

#define AT30TSE_CONFIG_RES_9_bit		0
#define AT30TSE_CONFIG_RES_10_bit		1
#define AT30TSE_CONFIG_RES_11_bit		2
#define AT30TSE_CONFIG_RES_12_bit		3

#define AT30TSE_CONFIG_FTQ_Pos 			13
#define AT30TSE_CONFIG_FTQ_Msk 			(0x03 << AT30TSE_CONFIG_FTQ_Pos)
#define AT30TSE_CONFIG_FTQ(value) 		((AT30TSE_CONFIG_FTQ_Msk & ((value) << AT30TSE_CONFIG_FTQ_Pos)))

#define AT30TSE_CONFIG_FTQ_1_fault		0
#define AT30TSE_CONFIG_RES_2_fault		1
#define AT30TSE_CONFIG_RES_4_fault		2
#define AT30TSE_CONFIG_RES_6_fault		3

// R/W bits
#define AT30TSE_CONFIG_OS				(1 << 15)
#define AT30TSE_CONFIG_R1				(1 << 14)
#define AT30TSE_CONFIG_R0				(1 << 13)
#define AT30TSE_CONFIG_FT1				(1 << 12)
#define AT30TSE_CONFIG_FT0				(1 << 11)
#define AT30TSE_CONFIG_POL				(1 << 10)
#define AT30TSE_CONFIG_CMP_INT			(1 << 9)
#define AT30TSE_CONFIG_SD				(1 << 8)

/* Read only bits */
#define AT30TSE_CONFIG_NVRBSY			(1 << 0)

void at30tse_init(void);
void at30tse_eeprom_write(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page);
void at30tse_eeprom_read(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page);
double at30tse_read_temperature(void);
void at30tse_write_config_register(uint16_t value);
uint16_t at30tse_read_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size);
void at30tse_write_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size, uint16_t reg_value);
void at30tse_set_register_pointer(uint8_t reg, uint8_t reg_type);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* AT30TSE75X_H_ */
