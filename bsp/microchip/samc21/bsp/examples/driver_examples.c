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

static uint8_t src_data[128];
static uint8_t chk_data[128];
/**
 * Example of using FLASH_0 to read and write Flash main array.
 */
void FLASH_0_example(void)
{
	uint32_t page_size;
	uint16_t i;

	/* Init source data */
	page_size = flash_get_page_size(&FLASH_0);

	for (i = 0; i < page_size; i++) {
		src_data[i] = i;
	}

	/* Write data to flash */
	flash_write(&FLASH_0, 0x3200, src_data, page_size);

	/* Read data from flash */
	flash_read(&FLASH_0, 0x3200, chk_data, page_size);
}

/**
 * Example of using FLASH_0 to read and write Flash RWWEE array.
 */
void RWW_FLASH_0_example(void)
{
	uint32_t page_size;
	uint16_t i;

	/* Init source data */
	page_size = _rww_flash_get_page_size(&FLASH_0.dev);

	for (i = 0; i < page_size; i++) {
		src_data[i] = i;
	}

	/* Write data to RWWEE flash */
	if (_rww_flash_write(&FLASH_0.dev, NVMCTRL_RWW_EEPROM_ADDR, src_data, page_size) != ERR_NONE) {
		while (1)
			; /* Trap here when flash write error happen */
	}

	/* Read data from RWWEE flash */
	if (_rww_flash_read(&FLASH_0.dev, NVMCTRL_RWW_EEPROM_ADDR, chk_data, page_size) != ERR_NONE) {
		while (1)
			; /* Trap here when flash read error happen */
	}

	/* Check data */
	for (i = 0; i < page_size; i++) {
		if (src_data[i] != chk_data[i]) {
			while (1)
				; /* Trap here when check error happen */
		}
	}
}

/**
 * Example of using TARGET_IO to write "Hello World" using the IO abstraction.
 */
void TARGET_IO_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&TARGET_IO, &io);
	usart_sync_enable(&TARGET_IO);

	io_write(io, (uint8_t *)"Hello World!", 12);
}
