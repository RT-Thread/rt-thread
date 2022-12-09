/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
=======
 * 2022-12-08     WangShun        the first version
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
<<<<<<< HEAD

=======
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
#include "udma_uart_driver.h"
#include "hal_udma_ctrl_reg_defs.h"
#include "hal_udma_uart_reg_defs.h"
#include "core-v-mcu-config.h"
#include "drv_usart.h"
#include "string.h"
<<<<<<< HEAD
extern rt_uint8_t uart_rxbuffer[16];
extern struct rt_ringbuffer uart_rxTCB;
extern struct rt_semaphore  shell_rx_semaphore;
extern void vPortSetupTimerInterrupt(void);
=======

extern void rt_systick_config(void);
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE (64*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];
void *rt_heap_begin_get(void)
{
	return rt_heap;
}
void *rt_heap_end_get(void)
{
	return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_hw_board_init()
{
    /* System Clock Update */
	extern void system_init(void);
	system_init();
	/* System Tick Configuration */
<<<<<<< HEAD
	vPortSetupTimerInterrupt();
=======
	rt_systick_config();
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd

	volatile uint32_t mtvec = 0;
	__asm volatile( "csrr %0, mtvec" : "=r"( mtvec ) );
	__asm volatile( "csrs mie, %0" :: "r"(0x880) );

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
<<<<<<< HEAD
	//rt_ringbuffer_init(&uart_rxTCB,uart_rxbuffer,16);
	//rt_sem_init(&(shell_rx_semaphore),"shell_rx",0,0);
}



/*not use device*/
#if 0
char rt_hw_console_getchar(void)
{
	char ch=0;
	while(rt_ringbuffer_getchar(&uart_rxTCB,(rt_uint8_t*)&ch)!=0)
	{
		rt_sem_take(&shell_rx_semaphore,RT_WAITING_FOREVER);
	}
	return ch;
}
#endif

#if 0
uint16_t writeraw(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer) {
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	while (puart->status_b.tx_busy) {  // ToDo: Why is this necessary?  Thought the semaphore should have protected
	}

	puart->tx_saddr = (uint32_t)write_buffer;
	puart->tx_size = write_len;
	puart->tx_cfg_b.en = 1; //enable the transfer

	return 0;
}
void rt_hw_console_output(const char *str)
{
	writeraw(0, strlen(str), (uint8_t*)str);
}
#endif

=======
}
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
