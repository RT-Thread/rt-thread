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

#include "core-v-mcu-config.h"
#include <string.h>
#include "hal_fc_event.h"
#include "hal_udma_ctrl_reg_defs.h"
#include "hal_udma_uart_reg_defs.h"
#include <drv_usart.h>
#include <stdint.h>
//#include "FreeRTOS.h"
//#include "semphr.h"
#include "core-v-mcu-config.h"
#include "udma_uart_driver.h"
#include "rtthread.h"
//#include <ringbuffer.h>
//#include "ipc/ringbuffer.h" 
#include "rtdevice.h" 
#define  unuse_freertos_in_uart


//SemaphoreHandle_t  uart_semaphores_rx[N_UART];
//SemaphoreHandle_t  uart_semaphores_tx[N_UART];
char u1buffer[128], u0buffer[128];
int u1rdptr, u1wrptr, u0rdptr,u0wrptr;
UdmaUart_t *puart0 = (UdmaUart_t*)(UDMA_CH_ADDR_UART);
UdmaUart_t *puart1 = (UdmaUart_t*)(UDMA_CH_ADDR_UART + UDMA_CH_SIZE);

uint16_t outdata(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer) {
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	while (puart->status_b.tx_busy) {  // ToDo: Why is this necessary?  Thought the semaphore should have protected
	}

	puart->tx_saddr = (uint32_t)write_buffer;
	puart->tx_size = write_len;
	puart->tx_cfg_b.en = 1; //enable the transfer

	return 0;
}

// ringbuffer  
#define UART_RX_BUFFER_LEN 16
rt_uint8_t uart_rxbuffer[UART_RX_BUFFER_LEN]={0};
struct rt_ringbuffer uart_rxTCB;
struct rt_semaphore  shell_rx_semaphore;

// extern struct ch32_uart_config uart_config[];
// extern void uart_isr(struct rt_serial_device *serial);
// extern struct ch32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] ;
// extern UART1_INDEX;
char n_data[]="\r\n";
// void uart_rx_isr (void *id){
// 	rt_interrupt_enter();
// 	if (id == 6) {
// 		while (*(int*)0x1a102130) {
// 			u1buffer[u1wrptr++] = puart1->data_b.rx_data & 0xff;
// 			u1wrptr &= 0x7f;
// 		}
// 	}
// 	if (id == 2) {
// 		while (puart0->valid) {
// 			//u0buffer[u0wrptr++] = puart0->data_b.rx_data & 0xff;
// 			//u0wrptr &= 0x7f;
// 			//outdata(0,sizeof(u0buffer),u0buffer);
// 			//outdata(0,sizeof(n_data),n_data);
// 			//rt_ringbuffer_putchar(&uart_rxTCB,puart0->data_b.rx_data & 0xff);
// 			//u0wrptr=0;
// 			uart_isr(&(uart_obj[UART1_INDEX].serial));
// 		}
// 		//rt_sem_release(&shell_rx_semaphore);
// 	}
// 	rt_interrupt_leave();
// }
uint8_t uart_getchar (uint8_t id) {
	uint8_t retval;
	if (id == 1) {
		while (u1rdptr == u1wrptr) ;
		retval = u1buffer[u1rdptr++];
		u1rdptr &= 0x7f;
	}
	if (id == 0) {
		while (u0rdptr == u0wrptr) ;
		retval = u0buffer[u0rdptr++];
		u0rdptr &= 0x7f;
	}
	return retval;
}

void uart_rx_isr (void *id);
uint16_t udma_uart_open (uint8_t uart_id, uint32_t xbaudrate) {
	UdmaUart_t*				puart;
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;

	/* See if already initialized */
	pudma_ctrl->reg_rst |= (UDMA_CTRL_UART0_CLKEN << uart_id);
	pudma_ctrl->reg_rst &= ~(UDMA_CTRL_UART0_CLKEN << uart_id);
	pudma_ctrl->reg_cg |= (UDMA_CTRL_UART0_CLKEN << uart_id);


	user_pi_fc_event_handler_set(SOC_EVENT_UART_RX(uart_id), uart_rx_isr);


	/* Enable SOC events propagation to FC. */
	hal_soc_eu_set_fc_mask(SOC_EVENT_UART_RX(uart_id));
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_UART_TX(uart_id));

	/* configure */
	puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);
	puart->uart_setup_b.div = (uint16_t)(5000000/xbaudrate);
	puart->uart_setup_b.bits = 3; // 8-bits

	puart->irq_en_b.rx_irq_en = 1;
	puart->uart_setup_b.en_tx = 1;
	puart->uart_setup_b.en_rx = 1;
	puart->uart_setup_b.rx_clean_fifo = 1;
	
	if (uart_id == 1) {
		 u1rdptr = 0;
	 	 u1wrptr = 0;
	}
	if (uart_id == 0) {
		 u0rdptr = 0;
	 	 u0wrptr = 0;
	}

	return 0;
}

uint16_t udma_uart_writeraw(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer) {
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	// SemaphoreHandle_t shSemaphoreHandle = uart_semaphores_tx[uart_id];
	// if( xSemaphoreTake( shSemaphoreHandle, 1000000 ) != pdTRUE ) {
	// 	return 1;
	// }

	while (puart->status_b.tx_busy) {  // ToDo: Why is this necessary?  Thought the semaphore should have protected
	}

	puart->tx_saddr = (uint32_t)write_buffer;
	puart->tx_size = write_len;
	puart->tx_cfg_b.en = 1; //enable the transfer

	return 0;
}

uint16_t udma_uart_read(uint8_t uart_id, uint16_t read_len, uint8_t* read_buffer) {
	uint16_t ret = 0;
	uint8_t last_char = 0;
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);


	while ( (ret < (read_len - 2)) && (last_char != 0xd)) {
		if (puart->valid_b.rx_data_valid == 1) {
			last_char = (uint8_t)(puart->data_b.rx_data & 0xff);
			if (last_char == 0xd)  // if cr add
				read_buffer[ret++] = 0xa;  // linefeed
			read_buffer[ret++] = last_char;
		}
	}
	read_buffer[ret] = '\0';
	return ret--;
}

uint16_t udma_uart_readraw(uint8_t uart_id, uint16_t read_len, uint8_t* read_buffer) {
	uint16_t ret = 0;
	uint8_t last_char = 0;
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	while ( ret < read_len ) {
		if (puart->valid_b.rx_data_valid == 1) {
			last_char = (uint8_t)(puart->data_b.rx_data & 0xff);
			read_buffer[ret++] = last_char;
		}
	}
	return ret--;
}

uint8_t udma_uart_getchar(uint8_t uart_id) {
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	while (puart->valid_b.rx_data_valid == 0) {
	}
	return (puart->data_b.rx_data & 0xff);
}

uint16_t udma_uart_control(uint8_t uart_id, udma_uart_control_type_t control_type, void* pparam) {
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	switch(control_type) {
	case kUartDataValid:
		if (uart_id == 0)
			return !(u0rdptr == u0wrptr);
		if (uart_id == 1)
			return !(u1rdptr == u1wrptr);
		return puart->valid_b.rx_data_valid;
	default:
		return 0xFFFF;
	}
	return 0;
}
