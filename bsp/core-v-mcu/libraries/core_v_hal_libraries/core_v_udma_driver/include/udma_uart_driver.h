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
 
#ifndef __UDMA_UART_DRIVER_H_
#define __UDMA_UART_DRIVER_H_

#include "stdint.h"

#include "hal_udma_ctrl_reg_defs.h"

typedef enum {
		kUartDataValid
} udma_uart_control_type_t;

uint16_t udma_uart_open (uint8_t uart_id, uint32_t xbaudrate);
uint16_t udma_uart_close (uint8_t uart_id);
uint16_t udma_uart_write(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer);
uint16_t udma_uart_writeraw(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer);
uint16_t udma_uart_read(uint8_t uart_id, uint16_t read_len, uint8_t* read_buffer);
uint16_t udma_uart_readraw(uint8_t uart_id, uint16_t read_len, uint8_t* read_buffer);
uint8_t udma_uart_getchar(uint8_t uart_id);
uint16_t udma_uart_control(uint8_t uart_id, udma_uart_control_type_t control_type, void* pparam);

uint8_t uart_getchar (uint8_t id);
#endif //__UDMA_UART_DRIVER_H_
