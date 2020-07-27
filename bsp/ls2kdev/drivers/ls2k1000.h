#ifndef _LS2K1000_H__
#define _LS2K1000_H__

#include <mips.h>
#include "interrupt.h"

#define APB_BASE         CKSEG1ADDR(0xbfe00000)

#define UART0_BASE_ADDR 0xbfe00000
#define UART0_OFF   0x0
#define UART0_BASE CKSEG1ADDR(UART0_BASE_ADDR + UART0_OFF)

#define UARTx_BASE(x)   ((APB_BASE | (0x0 << 12) | (x << 8)))

#define LIOINTC0_BASE    CKSEG1ADDR(0x1fe11400)
#define CORE0_INTISR0    CKSEG1ADDR(0x1fe11040)

#define LIOINTC1_BASE    CKSEG1ADDR(0x1fe11440)
#define CORE0_INTISR1    CKSEG1ADDR(0x1fe11048)

#define GPIO_BASE    0xFFFFFFFFBFE10500
#define PLL_SYS_BASE 0xFFFFFFFFBFE10480
#define RTC_BASE 0xFFFFFFFFBFE07820

#define GEN_CONFIG0_REG 0xFFFFFFFFBfe10420

void rt_hw_timer_handler(void);
void rt_hw_uart_init(void);

#endif

