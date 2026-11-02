/*
 * This is a generated file
 * 
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

#ifndef __HAL_APB_I2CS_H__
#define __HAL_APB_I2CS_H__

#include "stdint.h"

#define MY_I2C_SLAVE_ADDRESS 		0x62
#define MY_I2C_SLAVE_ADDRESS_7BIT 	(0x62 << 1)

#define I2C_MASTER_REG_DEV_ADDRESS								0x00
#define I2C_MASTER_REG_ENABLE									0x01
#define I2C_MASTER_REG_DEBOUNCE_LENGTH							0x02
#define I2C_MASTER_REG_SCL_DELAY_LENGTH							0x03
#define I2C_MASTER_REG_SDA_DELAY_LENGTH							0x04
#define I2C_MASTER_REG_MSG_I2C_APB								0x10
#define I2C_MASTER_REG_MSG_I2C_APB_STATUS						0x11
#define I2C_MASTER_REG_MSG_APB_I2C								0x12
#define I2C_MASTER_REG_MSG_APB_I2C_STATUS						0x13
#define I2C_MASTER_REG_FIFO_I2C_APB_WRITE_DATA_PORT				0x20
#define I2C_MASTER_REG_FIFO_I2C_APB_READ_DATA_PORT				0x21
#define I2C_MASTER_REG_FIFO_I2C_APB_FLUSH						0x22
#define I2C_MASTER_REG_FIFO_I2C_APB_WRITE_FLAGS					0x23
#define I2C_MASTER_REG_FIFO_I2C_APB_READ_FLAGS					0x24
#define I2C_MASTER_REG_FIFO_APB_I2C_WRITE_DATA_PORT				0x30
#define I2C_MASTER_REG_FIFO_APB_I2C_READ_DATA_PORT				0x31
#define I2C_MASTER_REG_FIFO_APB_I2C_FLUSH						0x32
#define I2C_MASTER_REG_FIFO_APB_I2C_WRITE_FLAGS					0x33
#define I2C_MASTER_REG_FIFO_APB_I2C_READ_FLAGS					0x34
#define I2C_MASTER_REG_INTERRUPT_STATUS							0x40
#define I2C_MASTER_REG_INTERRUPT_ENABLE							0x41
#define I2C_MASTER_REG_INTERRUPT_I2C_APB_WRITE_FLAGS_SELECT		0x42
#define I2C_MASTER_REG_INTERRUPT_APB_I2C_READ_FLAGS_SELECT		0x43
#define I2C_MASTER_REG_INTERRUPT_TO_APB_STATUS					0x50
#define I2C_MASTER_REG_INTERRUPT_TO_APB_ENABLE					0x51
#define I2C_MASTER_REG_INTERRUPT_APB_I2C_WRITE_FLAGS_SELECT 	0x52
#define I2C_MASTER_REG_INTERRUPT_I2C_APB_READ_FLAGS_SELECT		0x53

uint8_t hal_get_apb_i2cs_slave_address(void);
void hal_set_apb_i2cs_slave_address(uint8_t aSlaveAddress);
uint8_t hal_set_apb_i2cs_slave_on_off(uint8_t aStatus);
uint8_t hal_get_i2cs_fifo_i2c_apb_read_data_port(void);
void hal_set_i2cs_fifo_apb_i2c_write_data_port(uint8_t aData);
uint8_t hal_get_i2cs_fifo_i2c_apb_write_flags(void);
uint8_t hal_get_i2cs_fifo_i2c_apb_read_flags(void);
uint8_t hal_get_i2cs_fifo_apb_i2c_read_flags(void);
uint8_t hal_get_i2cs_fifo_apb_i2c_write_flags(void);
uint8_t hal_get_i2cs_msg_i2c_apb(void);
uint8_t hal_get_i2cs_msg_i2c_apb_status(void);
void hal_set_i2cs_msg_apb_i2c(uint8_t aData);
uint8_t hal_get_i2cs_msg_apb_i2c_status(void);
void hal_i2cs_fifo_i2c_apb_FIFO_flush(void);
void hal_i2cs_fifo_apb_i2c_FIFO_flush(void);


#endif // __HAL_APB_I2CS_H__
