#ifndef __INIT_H__
#define __INIT_H__

#include "mss_gpio.h"
#include "mss_uart.h"

#include <rthw.h>
#include <rtthread.h>

void boardInit(void);
void MSS_UART_polled_tx_byte(mss_uart_instance_t *this_uart, const uint8_t byte);
void rt_hw_console_output(const char *str);
char rt_hw_console_getchar(void);
void sayHello(void);

#endif
