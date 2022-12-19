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
#include "rtconfig.h"
#ifdef PKG_USING_FREERTOS_WRAPPER
#include "FreeRTOS.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "semphr.h"
#include "core-v-mcu-config.h"
#include "hal_fc_event.h"
#include "hal_udma_ctrl_reg_defs.h"
#include "hal_udma_sdio_reg_defs.h"
#include <udma_sdio_driver.h>

#define BLOCK_SIZE 512

uint16_t udma_sdio_open (uint8_t sdio_id)
{
	int i = 0;
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;
	UdmaSdio_t*					psdio_regs = (UdmaSdio_t*)(UDMA_CH_ADDR_SDIO + sdio_id * UDMA_CH_SIZE);

	/* Enable reset and enable uart clock */
	pudma_ctrl->reg_rst |= (UDMA_CTRL_SDIO0_CLKEN << sdio_id);
	pudma_ctrl->reg_rst &= ~(UDMA_CTRL_SDIO0_CLKEN << sdio_id);
	pudma_ctrl->reg_cg |= (UDMA_CTRL_SDIO0_CLKEN << sdio_id);

	psdio_regs->clk_div_b.clk_div = 7;//5;
	psdio_regs->clk_div_b.valid = 1;
	//Restore pin muxes
	for(i=0; i<6; i++ )
	{
		//set pin muxes to sdio functionality
		 hal_setpinmux(37+i, 0);
	}
	return 0;
}

uint16_t udma_sdio_control(uint8_t sdio_id, udma_sdio_control_type_t control_type, void* pparam) {
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;
	UdmaSdio_t*					psdio_regs = (UdmaSdio_t*)(UDMA_CH_ADDR_SDIO + sdio_id * UDMA_CH_SIZE);

	switch(control_type) {
	case kSDIOmReset:
		pudma_ctrl->reg_rst |= (UDMA_CTRL_SDIO0_CLKEN << sdio_id);
		pudma_ctrl->reg_rst &= ~(UDMA_CTRL_SDIO0_CLKEN << sdio_id);
		break;
	default:
		configASSERT(0);
	}
	return 0;
}

void udma_sdio_clearDataSetup(uint8_t sdio_id)
{
	UdmaSdio_t *psdio_regs = (UdmaSdio_t*)(UDMA_CH_ADDR_SDIO + sdio_id * UDMA_CH_SIZE);
	psdio_regs->data_setup = 0x00000000;
}
uint8_t udma_sdio_writeBlockData(uint8_t sdio_id, uint32_t aNumOfBlocks, uint32_t *aBuf, uint32_t aBufLen)
{
	uint8_t lSts = 0;
	uint32_t lData = 0;
	UdmaSdio_t *psdio_regs = (UdmaSdio_t*)(UDMA_CH_ADDR_SDIO + sdio_id * UDMA_CH_SIZE);

	psdio_regs->tx_cfg_b.clr = 1;
	psdio_regs->tx_cfg_b.en = 0;
	psdio_regs->tx_cfg_b.datasize = 2;

	psdio_regs->tx_saddr = aBuf;
	psdio_regs->tx_size = aBufLen;

	lData = 0;
	psdio_regs->data_setup = 0x00000000;
	lData |= 1 << 0;	//Data Enable - Enable data transfer for current command
	lData |= 0 << 1;	//RWN: Set transfer direction 1 read; 0 write
	lData |= 1 << 2;	//QUAD mode: Use quad mode.
	lData |= ( aNumOfBlocks - 1 ) << 8; //Number of blocks
	lData |= ( BLOCK_SIZE - 1 ) << 16; //Block size

	psdio_regs->data_setup = lData;

	psdio_regs->tx_cfg_b.en = 1;
}

uint8_t udma_sdio_readBlockData(uint8_t sdio_id, uint32_t aNumOfBlocks, uint32_t *aBuf, uint32_t aBufLen)
{
	uint8_t lSts = 0;
	uint32_t lData = 0;
	UdmaSdio_t *psdio_regs = (UdmaSdio_t*)(UDMA_CH_ADDR_SDIO + sdio_id * UDMA_CH_SIZE);

	psdio_regs->rx_cfg_b.clr = 1;
	psdio_regs->rx_cfg_b.en = 0;
	psdio_regs->rx_cfg_b.datasize = 2;

	psdio_regs->rx_saddr = aBuf;
	psdio_regs->rx_size = aBufLen;

	lData = 0;
	psdio_regs->data_setup = 0x00000000;
	lData |= 1 << 0;	//Data Enable - Enable data transfer for current command
	lData |= 1 << 1;	//RWN: Set transfer direction 1 read; 0 write
	lData |= 1 << 2;	//QUAD mode: Use quad mode.
	lData |= ( aNumOfBlocks - 1 ) << 8; //Number of blocks
	lData |= ( BLOCK_SIZE - 1 ) << 16; //Block size

	psdio_regs->data_setup = lData;

	psdio_regs->rx_cfg_b.en = 1;

}

uint8_t udma_sdio_sendCmd(uint8_t sdio_id, uint8_t aCmdOpCode, uint8_t aRspType, uint32_t aCmdArgument, uint32_t *aResponseBuf)
{
	uint8_t lSts = 0;
	uint32_t lData = 0;
	uint32_t lLoopCounter = 0;
	UdmaSdio_t *psdio_regs = (UdmaSdio_t*)(UDMA_CH_ADDR_SDIO + sdio_id * UDMA_CH_SIZE);

	lData |= (aRspType & REG_CMD_OP_CMD_RSP_TYPE_MASK ) << REG_CMD_OP_CMD_RSP_TYPE_LSB;
	lData |= ( aCmdOpCode & REG_CMD_OP_CMD_OP_MASK ) << REG_CMD_OP_CMD_OP_LSB;
	psdio_regs->cmd_op = lData;

	//psdio_regs->cmd_op_b.cmd_op = ( aCmdOpCode & 0x3F );
	//psdio_regs->cmd_op_b.cmd_rsp_type = ( aRspType & 0x07 );
	psdio_regs->cmd_arg = aCmdArgument;

	psdio_regs->start = 1;

	while( ( ( psdio_regs->status & ( REG_STATUS_EOT_MASK << REG_STATUS_EOT_LSB ) ) >> REG_STATUS_EOT_LSB ) == 0 )
	{
		if( ( ( psdio_regs->status & ( REG_STATUS_ERROR_MASK << REG_STATUS_ERROR_LSB ) ) >> REG_STATUS_ERROR_LSB ) == 1 )
		{
			lSts = (psdio_regs->status & ( REG_STATUS_CMD_ERR_STATUS_MASK << REG_STATUS_CMD_ERR_STATUS_LSB ) ) >> REG_STATUS_CMD_ERR_STATUS_LSB;
			break;
		}
		else
		{
			if(++lLoopCounter >= 0x00010000 )
			{
				lSts = 5;
				break;
			}
		}
	}

	psdio_regs->status_b.eot = 1;	//Write 1 to EOT bit to clear it.


	if( aResponseBuf )
	{
		aResponseBuf[0] = psdio_regs->rsp0;
		aResponseBuf[1] = psdio_regs->rsp1;
		aResponseBuf[2] = psdio_regs->rsp2;
		aResponseBuf[3] = psdio_regs->rsp3;

	}
	return lSts;
}
#if 0
static uint32_t auccmd[16];

void udma_qspim_read(uint8_t qspim_id, uint8_t cs, uint16_t read_len, uint8_t* read_buffer) {
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;

		configASSERT(read_len < 256);

		SemaphoreHandle_t shSemaphoreHandle = qspim_semaphores_rx[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_cmd[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;

		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT | cs;  //cs 1
		*pcmd++ = kSPIm_RxData | (0x00470000 | (read_len-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->rx_saddr = read_buffer;
		pqspim_regs->rx_size = read_len;
		pqspim_regs->rx_cfg_b.en = 1;

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;

		// Block until UDMA operation is complete
		shSemaphoreHandle = qspim_semaphores_rx[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_cmd[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );
}


void udma_qspim_write (uint8_t qspim_id, uint8_t cs, uint16_t write_len, uint8_t *write_data) {
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;
	uint32_t tmp_size;
		configASSERT(write_len < 256);

		SemaphoreHandle_t shSemaphoreHandle = qspim_semaphores_tx[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_cmd[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

		pqspim_regs->rx_cfg_b.clr = 1;
		pqspim_regs->tx_cfg_b.clr = 1;
		pqspim_regs->cmd_cfg_b.clr = 1;

		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT | cs;
		*pcmd++ = kSPIm_TxData | 0x0470000 | write_len -1;
		*pcmd++ = kSPIm_EOT | 1; // generate event


		pqspim_regs->tx_saddr = write_data;
		pqspim_regs->tx_size = write_len-1;
		pqspim_regs->tx_cfg_b.datasize = 2;
		pqspim_regs->tx_cfg_b.en = 1;

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;





		// Block until UDMA operation is complete
		shSemaphoreHandle = qspim_semaphores_tx[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_cmd[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );
}

#endif
#endif