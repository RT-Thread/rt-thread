/*******************************************************************************
 * (c) Copyright 2013 Microsemi SoC Products Group.  All rights reserved.
 *
 * Redirection of the standard library I/O to one of the SmartFusion2
 * MMUART.
 *
 * SVN $Revision: 7375 $
 * SVN $Date: 2015-05-01 14:57:40 +0100 (Fri, 01 May 2015) $
 */

/*==============================================================================
 * The content of this source file will only be compiled if either one of the
 * following two defined symbols are defined in the project settings:
 *  - MICROSEMI_STDIO_THRU_MMUART0
 *  - MICROSEMI_STDIO_THRU_MMUART1
 *
 */
#ifdef MICROSEMI_STDIO_THRU_MMUART0
#ifndef MICROSEMI_STDIO_THRU_UART
#define MICROSEMI_STDIO_THRU_UART
#endif
#endif  /* MICROSEMI_STDIO_THRU_MMUART0 */

#ifdef MICROSEMI_STDIO_THRU_MMUART1
#ifndef MICROSEMI_STDIO_THRU_UART
#define MICROSEMI_STDIO_THRU_UART
#endif
#endif  /* MICROSEMI_STDIO_THRU_MMUART1 */

/*==============================================================================
 * Actual implementation.
 */
#ifdef MICROSEMI_STDIO_THRU_UART

#include <stdio.h>
#include <rt_misc.h>

#include "m2sxxx.h"
#include "mss_uart.h"
#include "core_uart_apb.h"


/*
 * The baud rate will default to 57600 baud if no baud rate is specified though the
 * MICROSEMI_STDIO_BAUD_RATE define.
 */
#ifndef MICROSEMI_STDIO_BAUD_RATE
#define MICROSEMI_STDIO_BAUD_RATE  MSS_UART_115200_BAUD
#endif

#ifdef MICROSEMI_STDIO_THRU_MMUART0
static mss_uart_instance_t * const gp_my_uart = &g_mss_uart0;
#else
static mss_uart_instance_t * const gp_my_uart = &g_mss_uart1;
#endif

/*==============================================================================
 * Flag used to indicate if the UART driver needs to be initialized.
 */
static int g_stdio_uart_init_done = 0;


#define LSR_THRE_MASK   0x20u

/*
 * Disable semihosting apis
 */
#pragma import(__use_no_semihosting_swi)

/*==============================================================================
 * sendchar()
 */
int sendchar(int ch)
{
    uint32_t tx_ready;
    //第一次调用时，初始化串口
    if(!g_stdio_uart_init_done)
    {
        MSS_UART_init(gp_my_uart,
                      MICROSEMI_STDIO_BAUD_RATE,
                      MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY);
        g_stdio_uart_init_done = 1;
    }
    do {
        tx_ready = gp_my_uart->hw_reg->LSR & LSR_THRE_MASK;
    } while(!tx_ready);
    gp_my_uart->hw_reg->THR = ch;
    return (ch);
}

/*==============================================================================
 *
 */
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


/*==============================================================================
 * fputc()
 */
int fputc(int ch, FILE *f)
{
  return (sendchar(ch));
}

/*==============================================================================
 * fgetc()
 */
int fgetc(FILE *f)
{
    uint8_t rx_size;
    uint8_t rx_byte;

    do {
        rx_size = MSS_UART_get_rx(gp_my_uart, &rx_byte, 1);
    } while(0u == rx_size);

    return rx_byte;
}

/*==============================================================================
 * ferror()
 */
int ferror(FILE *f)
{
  /* Your implementation of ferror */
  return EOF;
}

/*==============================================================================
 * _ttywrch()
 */
void _ttywrch(int ch)
{
  sendchar(ch);
}

/*==============================================================================
 * _sys_exit()
 */
void _sys_exit(int return_code)
{
    for(;;)
    {
        ;  /* endless loop */
    }
}

#endif  /* MICROSEMI_STDIO_THRU_UART */
