/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-12     Bluebear233  first implementation
 */


#ifndef __BOARD_H__
#define __BOARD_H__

// <o> Internal SRAM memory size[Kbytes] <8-64>
#define SRAM_SIZE         (160)
#define SRAM_END          (0x20000000 + SRAM_SIZE * 1024)

#define RT_UART_485_MODE      1
#define RT_UART_FLOW_CTS_CTRL 2
#define RT_UART_FLOW_RTS_CTRL 3
#define RT_UART_CLEAR_BUF     4

void rt_hw_pdma_init(void);
void rt_hw_uart_handle(void);
void rt_hw_sc_init(void);
void rt_hw_usart_init(void);
void rt_hw_uusart_init(void);
void rt_hw_io_init(void);
void phy_error_led(void);

unsigned char *eth_get_default_mac(void);
void eth_set_mac(const unsigned char * mac);
void wdt_reload(void);
unsigned int get_uid(void);

#endif /* BOARD_H_ */
