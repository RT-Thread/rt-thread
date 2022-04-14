/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */

#include "atmel_start.h"
#include "stdio_start.h"

void STDIO_REDIRECT_0_example(void)
{
	/* Print welcome message */
	printf("\r\nHello ATMEL World!\r\n");
}

void stdio_redirect_init(void)
{

	usart_sync_enable(&TARGET_IO);
	stdio_io_init(&TARGET_IO.io);
}
