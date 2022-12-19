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
#include "hal_udma_qspi_reg_defs.h"
#include <udma_qspi_driver.h>

SemaphoreHandle_t  qspim_semaphores_rx[N_QSPIM];
SemaphoreHandle_t  qspim_semaphores_tx[N_QSPIM];
SemaphoreHandle_t  qspim_semaphores_cmd[N_QSPIM];
SemaphoreHandle_t  qspim_semaphores_eot[N_QSPIM];

uint8_t aucclkdiv;
static unsigned int isr_count;
void spi_tx_isr() {
	isr_count += 0x1;
}
void spi_rx_isr() {
	isr_count += 0x100;
}
void spi_cmd_isr() {
	isr_count += 0x10000;
}
void spi_eot_isr() {
	isr_count += 0x1000000;
}

uint16_t udma_qspim_open (uint8_t qspim_id, uint32_t clk_freq) {
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;
	UdmaQspi_t*					pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t					clk_divisor;

	/* See if already initialized */
	if (qspim_semaphores_rx[qspim_id] != NULL || qspim_semaphores_tx[qspim_id] != NULL) {
		return 1;
	}
	/* Enable reset and enable uart clock */
	if( qspim_id == 0 )
	{
		pudma_ctrl->reg_rst |= ( UDMA_CTRL_QSPIM0_CLKEN ) ;
		pudma_ctrl->reg_rst &= ~(UDMA_CTRL_QSPIM0_CLKEN);
		pudma_ctrl->reg_cg |= (UDMA_CTRL_QSPIM0_CLKEN );
	}
	else if( qspim_id == 1 )
	{
#if(NEW_BIT_FILE == 1 )
		pudma_ctrl->reg_rst |= ( UDMA_CTRL_QSPIM1_CLKEN ) ;
		pudma_ctrl->reg_rst &= ~(UDMA_CTRL_QSPIM1_CLKEN);
		pudma_ctrl->reg_cg |= (UDMA_CTRL_QSPIM1_CLKEN );
#endif
	}


	/* Set semaphore */
	SemaphoreHandle_t shSemaphoreHandle;		// FreeRTOS.h has a define for xSemaphoreHandle, so can't use that
	shSemaphoreHandle = xSemaphoreCreateBinary();
	configASSERT(shSemaphoreHandle);
	xSemaphoreGive(shSemaphoreHandle);
	qspim_semaphores_rx[qspim_id] = shSemaphoreHandle;

	shSemaphoreHandle = xSemaphoreCreateBinary();
	configASSERT(shSemaphoreHandle);
	xSemaphoreGive(shSemaphoreHandle);
	qspim_semaphores_tx[qspim_id] = shSemaphoreHandle;

	shSemaphoreHandle = xSemaphoreCreateBinary();
	configASSERT(shSemaphoreHandle);
	xSemaphoreGive(shSemaphoreHandle);
	qspim_semaphores_cmd[qspim_id] = shSemaphoreHandle;

	shSemaphoreHandle = xSemaphoreCreateBinary();
	configASSERT(shSemaphoreHandle);
	xSemaphoreGive(shSemaphoreHandle);
	qspim_semaphores_eot[qspim_id] = shSemaphoreHandle;

	/* Set handlers. */
	isr_count = 0;
	pi_fc_event_handler_set(SOC_EVENT_UDMA_SPIM_RX(qspim_id), spi_rx_isr, qspim_semaphores_rx[qspim_id]);
	pi_fc_event_handler_set(SOC_EVENT_UDMA_SPIM_TX(qspim_id), spi_tx_isr, qspim_semaphores_tx[qspim_id]);
	pi_fc_event_handler_set(SOC_EVENT_UDMA_SPIM_CMD(qspim_id), spi_cmd_isr, qspim_semaphores_cmd[qspim_id]);
	pi_fc_event_handler_set(SOC_EVENT_UDMA_SPIM_EOT(qspim_id), spi_eot_isr, qspim_semaphores_eot[qspim_id]);

	/* Enable SOC events propagation to FC. */
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_SPIM_RX(qspim_id));
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_SPIM_TX(qspim_id));
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_SPIM_CMD(qspim_id));
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_SPIM_EOT(qspim_id));

	/* configure */
	aucclkdiv = 5000000/clk_freq;

	return 0;
}

uint16_t udma_qspim_control(uint8_t qspim_id, udma_qspim_control_type_t control_type, void* pparam) {
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;
	UdmaQspi_t*					pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);

	switch(control_type) {
	case kQSPImReset:
		if( qspim_id == 0 )
		{
			pudma_ctrl->reg_rst |= (UDMA_CTRL_QSPIM0_CLKEN);
			pudma_ctrl->reg_rst &= ~(UDMA_CTRL_QSPIM0_CLKEN);
		}
		else if( qspim_id == 1 )
		{
#if(NEW_BIT_FILE == 1 )
			pudma_ctrl->reg_rst |= (UDMA_CTRL_QSPIM1_CLKEN);
			pudma_ctrl->reg_rst &= ~(UDMA_CTRL_QSPIM1_CLKEN);
#endif
		}
		break;
	default:
		configASSERT(0);
	}
	return 0;
}

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
		pqspim_regs->tx_size = write_len;
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

uint32_t udma_flash_reset_enable(uint8_t qspim_id, uint8_t cs)
{
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;
	uint32_t result = 0;

	udma_qspim_control(qspim_id, (udma_qspim_control_type_t) kQSPImReset , (void*) 0);

	pqspim_regs->cmd_cfg_b.en = 0;

	pqspim_regs->cmd_cfg_b.clr = 1;

	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x70066); // reset enable command
	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	return result;
}

uint32_t udma_flash_reset_memory(uint8_t qspim_id, uint8_t cs)
{
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;
	uint32_t result = 0;

	udma_qspim_control(qspim_id, (udma_qspim_control_type_t) kQSPImReset , (void*) 0);

	pqspim_regs->cmd_cfg_b.en = 0;

	pqspim_regs->cmd_cfg_b.clr = 1;

	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x70099); // reset memory command

	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	return result;
}

static uint8_t rx_data[16];
uint32_t udma_flash_readid(uint8_t qspim_id, uint8_t cs) {
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;
	uint32_t result = 0;

	pqspim_regs->rx_cfg_b.en = 0;
	pqspim_regs->tx_cfg_b.en = 0;
	pqspim_regs->cmd_cfg_b.en = 0;

	pqspim_regs->rx_cfg_b.clr = 1;
	pqspim_regs->tx_cfg_b.clr = 1;
	pqspim_regs->cmd_cfg_b.clr = 1;

	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x7009f); // readid command
	*pcmd++ = kSPIm_RxData | (0x00470000 | (4-1)) ; // 4 words recieved
	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->rx_saddr = &rx_data;
	pqspim_regs->rx_size = 4;
	pqspim_regs->rx_cfg_b.en = 1;

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	while (pqspim_regs->rx_size != 0) {}

	result = *(uint32_t *) rx_data;
	return result;
}

uint8_t udma_flash_erase(uint8_t qspim_id, uint8_t cs, uint32_t addr, uint8_t cmd) {
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;
	union { uint32_t w; uint8_t b[4]; } result;
	SemaphoreHandle_t shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
    switch (cmd) {
    case 0: cmd = 0x20;break;  // subsector (4k erase)
    case 1: cmd = 0xd8;break; // sector erase (64K)
    case 2: cmd == 0xc7;break; // bulk erase
    default: configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
    	return 0xff;

    }

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;

		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT | cs;
		*pcmd++ = kSPIm_SendCmd | (0x70006) ; // write enable command
//		*pcmd++ = kSPIm_RxData | (0x00470000 | (4-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_EOT  | 1; // generate event

//		pqspim_regs->rx_saddr = &result.w;
//		pqspim_regs->rx_size = 0;
//		pqspim_regs->rx_cfg_b.en = 1;

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;
		pcmd = auccmd;
		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT | cs;
		*pcmd++ = kSPIm_SendCmd | (0x70000) | cmd; // write enable command
		*pcmd++ = kSPIm_SendCmd | (0xf0000) | ((addr >> 8) & 0xffff);
		*pcmd++ = kSPIm_SendCmd | (0x70000) | (addr & 0xff);
//		*pcmd++ = kSPIm_RxData | (0x00470000 | (4-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;

		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

		result.b[0] = 0;
		while ((result.b[0] & 0x80) == 0x0) {

			pqspim_regs->rx_cfg_b.en = 0;
			pqspim_regs->tx_cfg_b.en = 0;
			pqspim_regs->cmd_cfg_b.en = 0;
			pcmd = auccmd;
			*pcmd++ = kSPIm_Cfg | aucclkdiv;
			*pcmd++ = kSPIm_SOT | cs;
			*pcmd++ = kSPIm_SendCmd | (0x70070); // read flag register
			*pcmd++ = kSPIm_RxData | (0x00470000 | (4-1)) ; // 4 words recieved
			*pcmd++ = kSPIm_EOT  | 1; // generate event

			pqspim_regs->rx_saddr = &result.w;
			pqspim_regs->rx_size = 4;
			pqspim_regs->rx_cfg_b.en = 1;

			pqspim_regs->cmd_saddr = auccmd;
			pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
			pqspim_regs->cmd_cfg_b.en = 1;
			configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		}
		configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;
		pcmd = auccmd;
		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT | cs;
		*pcmd++ = kSPIm_SendCmd | (0x70004); // write disable
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;
		return result.b[0];
}

void udma_flash_read(uint8_t qspim_id, uint8_t cs, uint32_t flash_addr,uint8_t *l2addr,uint16_t read_len ) {
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;

	SemaphoreHandle_t shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
	shSemaphoreHandle = qspim_semaphores_rx[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;

		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT;
		*pcmd++ = kSPIm_SendCmd | (0x70003);  // read command
		*pcmd++ = kSPIm_SendCmd | (0xf0000) | ((flash_addr >> 8) & 0xffff);
		*pcmd++ = kSPIm_SendCmd | (0x70000) | (flash_addr & 0xff);
		*pcmd++ = kSPIm_RxData | (0x00470000 | (read_len-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->rx_saddr = l2addr;
		pqspim_regs->rx_size = read_len;
		pqspim_regs->rx_cfg_b.en = 1;

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;

		shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_rx[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle) == pdTRUE );

}
void udma_flash_read_quad(uint8_t qspim_id, uint8_t cs, uint32_t flash_addr,uint8_t *l2addr,uint16_t read_len ) {
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;

	SemaphoreHandle_t shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
	shSemaphoreHandle = qspim_semaphores_rx[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;

		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT;
		//*pcmd++ = kSPIm_SendCmd | (0x7000B);  // read command
		*pcmd++ = kSPIm_SendCmd | (0x7006B);
		*pcmd++ = kSPIm_SendCmd | (0xf0000) | ((flash_addr >> 8) & 0xffff);
		*pcmd++ = kSPIm_SendCmd | (0x70000) | (flash_addr & 0xff);
		//*pcmd++ = kSPIm_Dummy | 0x001F0000;
		*pcmd++ = kSPIm_Dummy | 0x00070000;
		//*pcmd++ = kSPIm_RxData | (0x00470000 | (read_len-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_RxData | (0x08470000 | (read_len-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->rx_saddr = l2addr;
		pqspim_regs->rx_size = read_len;
		pqspim_regs->rx_cfg_b.en = 1;

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;

		shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_rx[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle) == pdTRUE );

}
void udma_flash_write(uint8_t qspim_id, uint8_t cs, uint32_t flash_addr,
		uint8_t *l2addr, uint16_t write_len ) {
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;

	SemaphoreHandle_t shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	shSemaphoreHandle = qspim_semaphores_tx[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
	shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

	pqspim_regs->rx_cfg_b.en = 0;
	pqspim_regs->tx_cfg_b.en = 0;
	pqspim_regs->cmd_cfg_b.en = 0;

	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x70006) ; // write enable command
	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;

		pcmd = auccmd;
		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT;
		*pcmd++ = kSPIm_SendCmd | (0x70002);  // program command
		*pcmd++ = kSPIm_SendCmd | (0xf0000) | ((flash_addr >> 8) & 0xffff);
		*pcmd++ = kSPIm_SendCmd | (0x70000) | (flash_addr & 0xff);
		*pcmd++ = kSPIm_TxData | (0x00470000 | (write_len-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->tx_saddr = l2addr;
		pqspim_regs->tx_size = write_len;
		pqspim_regs->tx_cfg_b.en = 1;

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;


		shSemaphoreHandle = qspim_semaphores_tx[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle) == pdTRUE );
		shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
uint8_t test;
		test = 1;
				while ((test & 0x3) == 0x1) {

					pqspim_regs->rx_cfg_b.en = 0;
					pqspim_regs->tx_cfg_b.en = 0;
					pqspim_regs->cmd_cfg_b.en = 0;
					pcmd = auccmd;
					*pcmd++ = kSPIm_Cfg | aucclkdiv;
					*pcmd++ = kSPIm_SOT | cs;
					*pcmd++ = kSPIm_SendCmd | (0x70005); // read status register
					*pcmd++ = kSPIm_RxData | (0x00470000 | (4-1)) ; // 4 words recieved
					*pcmd++ = kSPIm_EOT  | 1; // generate event

					pqspim_regs->rx_saddr = l2addr;
					pqspim_regs->rx_size = 4;
					pqspim_regs->rx_cfg_b.en = 1;

					pqspim_regs->cmd_saddr = auccmd;
					pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
					pqspim_regs->cmd_cfg_b.en = 1;
					configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
					test = l2addr[0] & 0xff;
				}

		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;

		pcmd = auccmd;
		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT | cs;
		*pcmd++ = kSPIm_SendCmd | (0x70004) ; // write disable command
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;

		shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		configASSERT( xSemaphoreGive( shSemaphoreHandle) == pdTRUE );
}

/*
 * https://forums.xilinx.com/t5/Processor-System-Design-and-AXI/QSPI-flash-programming-how-to-activate-qspi-in-quad-mode/td-p/871253
 * to enable the quad mode
1. send ENTER QUAD INPUT/OUTPUT MODE command 0x35h
2. send write enable cmd 0x06
3. to write into enhanced volatile configuration register - send  0x61 command.
4. 0x7F is written in the above register to activate in quad mode
5. poll the configuration register i.e read the enhanced volatile config register command is 0x65 and wait untill it
becomes 0X7F
6. then configure the controller in quad mode and send the multiple read id code 0XAF to read the ID code on all the four lines.
 */
void udma_flash_enterQuadIOMode(uint8_t qspim_id, uint8_t cs )
{
	UdmaQspi_t*	pqspim_regs = (UdmaQspi_t*)(UDMA_CH_ADDR_QSPIM + qspim_id * UDMA_CH_SIZE);
	uint32_t*	pcmd = auccmd;
	uint8_t test = 0;
	uint8_t l2addr[4] = {0};

	SemaphoreHandle_t shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	//shSemaphoreHandle = qspim_semaphores_tx[qspim_id];
	//configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
	shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

	pqspim_regs->rx_cfg_b.en = 0;
	pqspim_regs->tx_cfg_b.en = 0;
	pqspim_regs->cmd_cfg_b.en = 0;

	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x70035) ; // Enter QUAD command
	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x70006) ; // write enable command
	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x70061) ; // write Enhanced volatile register 0x61
	*pcmd++ = kSPIm_SendCmd | (0x7007F) ;
	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );

	while ((test & 0xFF) != 0x7F) {
		pqspim_regs->rx_cfg_b.en = 0;
		pqspim_regs->tx_cfg_b.en = 0;
		pqspim_regs->cmd_cfg_b.en = 0;
		pcmd = auccmd;
		*pcmd++ = kSPIm_Cfg | aucclkdiv;
		*pcmd++ = kSPIm_SOT | cs;
		*pcmd++ = kSPIm_SendCmd | (0x70065); // read status register
		*pcmd++ = kSPIm_RxData | (0x00470000 | (4-1)) ; // 4 words recieved
		*pcmd++ = kSPIm_EOT  | 1; // generate event

		pqspim_regs->rx_saddr = l2addr;
		pqspim_regs->rx_size = 4;
		pqspim_regs->rx_cfg_b.en = 1;

		pqspim_regs->cmd_saddr = auccmd;
		pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
		pqspim_regs->cmd_cfg_b.en = 1;
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		test = l2addr[0] & 0xff;
	}
	pqspim_regs->rx_cfg_b.en = 0;
	pqspim_regs->tx_cfg_b.en = 0;
	pqspim_regs->cmd_cfg_b.en = 0;

	pcmd = auccmd;
	*pcmd++ = kSPIm_Cfg | aucclkdiv;
	*pcmd++ = kSPIm_SOT | cs;
	*pcmd++ = kSPIm_SendCmd | (0x70004) ; // write disable command
	*pcmd++ = kSPIm_EOT  | 1; // generate event

	pqspim_regs->cmd_saddr = auccmd;
	pqspim_regs->cmd_size = (uint32_t)(pcmd - auccmd)*4;
	pqspim_regs->cmd_cfg_b.en = 1;

	shSemaphoreHandle = qspim_semaphores_eot[qspim_id];
	configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
	configASSERT( xSemaphoreGive( shSemaphoreHandle) == pdTRUE );
}
#endif

