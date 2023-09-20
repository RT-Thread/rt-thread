/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using TARGET_IO to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_TARGET_IO[12] = "Hello World!";

static void tx_cb_TARGET_IO(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void TARGET_IO_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&TARGET_IO, USART_ASYNC_TXC_CB, tx_cb_TARGET_IO);
	/*usart_async_register_callback(&TARGET_IO, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&TARGET_IO, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&TARGET_IO, &io);
	usart_async_enable(&TARGET_IO);

	io_write(io, example_TARGET_IO, 12);
}
