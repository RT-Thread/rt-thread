#ifndef _UART_H_
#define _UART_H_

#define RT_DEVICE_CTRL_CUSTOM   0x20
#define RT_DEVICE_CTRL_PIN      0x21
#define RT_DEVICE_POWERSAVE     0x22
#define RT_DEVICE_WAKEUP        0x23

#define UART_CONFIG_BAUD_RATE_9600      1
#define UART_CONFIG_BAUD_RATE_115200    2

#define UART0_RB_SIZE        1024

// #define USE_UART0_1         0

void rt_hw_uart_init(void);

#endif

