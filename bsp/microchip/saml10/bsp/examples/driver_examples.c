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
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&ADC_0, 0);

	while (1) {
		adc_sync_read_channel(&ADC_0, 0, buffer, 2);
	}
}

void I2C_0_example(void)
{
	struct io_descriptor *I2C_0_io;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x12, I2C_M_SEVEN);
	io_write(I2C_0_io, (uint8_t *)"Hello World!", 12);
}

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
