/*
 * Copyright 2021 QuickLogic
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DRIVERS_INCLUDE_UDMA_I2CM_DRIVER_H_
#define DRIVERS_INCLUDE_UDMA_I2CM_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

#include "hal_udma_ctrl_reg_defs.h"

#define SEMAPHORE_WAIT_TIME_IN_MS	10

typedef enum {
		kI2cmReset
} udma_i2cm_control_type_t;

typedef enum {
	kI2cmCmdStart 	= 0x00,
	kI2cmCmdStop	= 0x20,
	kI2cmCmdRdAck	= 0x40,
	kI2cmCmdRdNack	= 0x60,
	kI2cmCmdWr		= 0x80,
	kI2cmCmdWait	= 0xA0,
	kI2cmCmdRpt		= 0xC0,
	kI2cmCmdCfg		= 0xE0,
	kI2cmCmdWaitEvt	= 0x10,
} i2cm_cmd_t;

uint16_t udma_i2cm_open (uint8_t i2c_id, uint32_t i2c_clk_freq);
uint16_t udma_i2cm_close (uint8_t i2c_id);
uint16_t udma_i2cm_control(uint8_t i2c_id, udma_i2cm_control_type_t control_type, void* pparam);
uint8_t udma_i2cm_write(uint8_t i2c_id, uint8_t i2c_addr, uint8_t reg_addr, uint16_t write_len, uint8_t* write_data, bool more_follows);
uint8_t udma_i2cm_read(uint8_t i2c_id, uint8_t i2c_addr, uint8_t reg_addr, uint16_t read_len, uint8_t* read_buffer, bool more_follows);
uint8_t udma_i2cm_16read8(uint8_t i2c_id, uint8_t i2c_addr, uint16_t reg_addr, uint16_t read_len, uint8_t* read_buffer, bool more_follows);



// helper functions
uint8_t _udma_i2cm_write_addr_plus_regaddr (uint8_t i2c_id, uint8_t i2c_addr, uint8_t reg_addr);
uint8_t _udma_i2cm_write_addr_plus_reg16addr (uint8_t i2c_id, uint8_t i2c_addr, uint16_t reg_addr);
uint8_t _udma_i2cm_read(uint8_t i2c_id, uint8_t i2c_addr, uint16_t read_len, uint8_t* read_buffer, bool more_follows);
uint8_t _udma_i2cm_send_stop(uint8_t i2c_id);

#endif /* DRIVERS_INCLUDE_UDMA_I2CM_DRIVER_H_ */

