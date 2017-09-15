#ifndef __BOARD_H_
#define __BOARD_H_

#include <rtthread.h>

// <o> Internal SRAM memory size[Kbytes] <8-256>
//	<i>Default: 256
#define AM_SRAM_SIZE         256
#define AM_SRAM_END          (0x10000000 + AM_SRAM_SIZE * 1024)

/* USART driver select. */
#define RT_USING_UART0
#define RT_USING_UART1

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
