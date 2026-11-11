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

#ifndef DRIVERS_INCLUDE_UDMA_SDIO_DRIVER_H_
#define DRIVERS_INCLUDE_UDMA_SDIO_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

#include "hal_udma_ctrl_reg_defs.h"

typedef enum {
		kSDIOmReset
} udma_sdio_control_type_t;
/*
typedef enum {
	kSPIm_Cfg 	    = (0x0 << 28),
	kSPIm_SOT	    = (0x1 << 28),
	kSPIm_SendCmd	= (0x2 << 28),
	kSPIm_Dummy	    = (0x4 << 28),
	kSPIm_Wait		= (0x5 << 28),
	kSPIm_TxData	= (0x6 << 28),
	kSPIm_RxData  	= (0x7 << 28),
	kSPIm_Repeat	= (0x8 << 28),
	kSPIm_EOT		= (0x9 << 28),
	kSPIm_RepeatEnd = (0xa << 28),
	kSPIm_RxCheck	= (0xb << 28),
	kSPIm_FDX 		= (0xc << 28),
	kSPIm_UCA 		= (0xd << 28),
	kSPIm_UCS 		= (0xe << 28)

} spim_cmd_t;
*/
uint16_t udma_sdio_open (uint8_t sdio_id);
uint16_t udma_sdio_close (uint8_t sdio_id);
uint16_t udma_sdio_control(uint8_t sdio_id, udma_sdio_control_type_t control_type, void* pparam);
uint8_t udma_sdio_sendCmd(uint8_t sdio_id, uint8_t aCmdOpCode, uint8_t aRspType, uint32_t aCmdArgument, uint32_t *aResponseBuf);
void udma_sdio_write(uint8_t sdio_id, uint8_t cs, uint16_t write_len, uint8_t* write_data);
void udma_sdio_read(uint8_t sdio_id,  uint8_t cs, uint16_t read_len, uint8_t* read_buffer);
uint8_t udma_flash_erase(uint8_t sdio_id, uint8_t cs, uint32_t addr, uint8_t cmd);
uint32_t udma_flash_readid(uint8_t sdio_id, uint8_t cs);
void udma_flash_read(uint8_t sdio_id, uint8_t cs, uint32_t flash_addr,uint8_t *l2addr,uint16_t read_len ) ;
void udma_flash_write(uint8_t sdio_id, uint8_t cs, uint32_t flash_addr,uint8_t *l2addr,uint16_t write_len ) ;
uint32_t udma_flash_reset_enable(uint8_t sdio_id, uint8_t cs);
uint32_t udma_flash_reset_memory(uint8_t sdio_id, uint8_t cs);

uint8_t udma_sdio_readBlockData(uint8_t sdio_id, uint32_t aNumOfBlocks, uint32_t *aBuf, uint32_t aBufLen);
uint8_t udma_sdio_writeBlockData(uint8_t sdio_id, uint32_t aNumOfBlocks, uint32_t *aBuf, uint32_t aBufLen);
void udma_sdio_clearDataSetup(uint8_t sdio_id);

// helper functions


#endif /* DRIVERS_INCLUDE_UDMA_QSPIM_DRIVER_H_ */
