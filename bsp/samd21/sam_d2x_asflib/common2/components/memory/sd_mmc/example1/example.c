/**
 * \file
 *
 * \brief SD/MMC card example
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 * \mainpage SD/MMC Card Example
 *
 * \section Purpose
 *
 * This example demonstrates basic functions of SD/MMC stack.
 * It will read and write an SD/MMC card over MCI or SPI interface.
 * It is a development base for a specific SD/MMC
 * application which does not require a file system.
 *
 * \section Description
 *
 * The example executes the following sequences:
 * - For each card slot available on board:
 *   - Wait for a card insertion
 *   - Initialize an SD/MMC card.
 *   - If the inserted card is an SD or MMC card, test read/write access.
 *       - Write data into the card
 *       - Read data from the card
 *       - Verify the written data.
 *
 * The example outputs the information through the standard output (stdio).
 * To know the output used on the board, look in the conf_example.h file
 * and connect a terminal to the correct stdio port.
 * 
 * While using Xplained Pro evaluation kits, please attach I/O1 Xplained Pro
 * extension board to EXT1.
 *
 * \section Usage
 *
 * -# Build the program and download it into the  board.
 * -# On the computer, open and configure a terminal application.
 * Refer to conf_example.h file.
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- SD/MMC Card Example --
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     Please plug an SD/MMC card in slot 1.
 *     !!Warning, the data contained will be lost!!
 *    \endcode
 * -# If the inserted card is a SD or MMC card, the following text should appear:
 *     A card has been connected.
 *     Card information:
 *         xxxx
 *         xxxx MB
 *         Write pattern... XXXXKBps [OK]
 *         Read... XXXXKBps [OK]
 *         Read and check pattern... [OK]
 *     Test finished, please unplugged card.
 *    \endcode
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include "conf_example.h"
#include <string.h>
#include "time_tick.h"

//! Structure for UART module connected to EDBG (used for unit test output)
struct usart_module cdc_uart_module;

//! \name Read/write access configurations
//! @{

//! Offset before the end of memory card to start the test
#define TEST_MEM_START_OFFSET  (1024lu * 1024lu * 4lu) // 4MB

//! Memory area size dedicated for the read/write test
#define TEST_MEM_AREA_SIZE (1024lu * 128lu) // 128KB
/**
 * Size of each read or write access.
 * Increasing this number can get higher R/W performance.
 */
#define TEST_MEM_ACCESS_SIZE  (8lu * SD_MMC_BLOCK_SIZE)

#if TEST_MEM_START_OFFSET < TEST_MEM_AREA_SIZE
#  error TEST_MEM_START_OFFSET must be higher than TEST_MEM_AREA_SIZE
#endif
#if TEST_MEM_ACCESS_SIZE > TEST_MEM_AREA_SIZE
#  error TEST_MEM_AREA_SIZE must be higher than TEST_MEM_ACCESS_SIZE
#endif

//! The value used to generate test data
#define TEST_FILL_VALUE_U32     (0x5500AAFFU)

//! Buffer used by read/write tests
COMPILER_WORD_ALIGNED
static uint8_t buf_test[TEST_MEM_ACCESS_SIZE];

//! @}

static void main_display_info_card(uint8_t slot);
static void main_test_memory(uint8_t slot);

/**
 * \brief Initialize the USART for output
 *
 * Initializes the SERCOM USART used for sending the output to the
 * computer via the EDBG CDC gateway.
 */
static void cdc_uart_init(void)
{
	struct usart_config usart_conf;

	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t slot = 0;
	sd_mmc_err_t err;

	system_init();
	delay_init();
	cdc_uart_init();

	irq_initialize_vectors();
	cpu_irq_enable();

	time_tick_init();

	// Initialize SD MMC stack
	sd_mmc_init();

	printf("\x0C\n\r-- SD/MMC Card Example --\n\r");
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	while (1) {
		if (slot == sd_mmc_nb_slot()) {
			slot = 0;
		}
		printf("Please plug an SD/MMC card in slot %d.\n\r", slot+1);

		// Wait for a card and ready
		do {
			err = sd_mmc_check(slot);
			if ((SD_MMC_ERR_NO_CARD != err)
					&& (SD_MMC_INIT_ONGOING != err)
					&& (SD_MMC_OK != err)) {
				printf("Card install FAILED\n\r");
				printf("Please unplug and re-plug the card.\n\r");
				while (SD_MMC_ERR_NO_CARD != sd_mmc_check(slot)) {
				}
			}
		} while (SD_MMC_OK != err);
	
		// Display basic card information
		main_display_info_card(slot);
	
		/* Test the card */
		if (sd_mmc_get_type(slot) & (CARD_TYPE_SD | CARD_TYPE_MMC)) {
			// SD/MMC Card R/W
			main_test_memory(slot);
		}	

		printf("Test finished, please unplugged the card.\n\r");
		while (SD_MMC_OK == sd_mmc_check(slot)) {
		}
		slot++;
	}
}

/**
 * \brief Display basic information of the card.
 * \note This function should be called only after the card has been
 *       initialized successfully.
 *
 * \param slot   SD/MMC slot to test
 */
static void main_display_info_card(uint8_t slot)
{
	printf("Card information:\n\r");

	printf("    ");
	switch (sd_mmc_get_type(slot)) {
	case CARD_TYPE_SD | CARD_TYPE_HC:
		printf("SDHC");
		break;
	case CARD_TYPE_SD:
		printf("SD");
		break;
	case CARD_TYPE_MMC | CARD_TYPE_HC:
		printf("MMC High Density");
		break;
	case CARD_TYPE_MMC:
		printf("MMC");
		break;
	case CARD_TYPE_SD_COMBO:
		printf("SD COMBO");
		break;
	case CARD_TYPE_UNKNOWN:
	default:
		printf("Unknow\n\r");
		return;
	}
	printf("\n\r    %d MB\n\r", (uint16_t)(sd_mmc_get_capacity(slot)/1024));
}

/**
 * \brief Card R/W tests
 *
 * \param slot   SD/MMC slot to test
 */
static void main_test_memory(uint8_t slot)
{
	uint32_t last_blocks_addr, i, nb_trans;
	uint32_t tick_start, time_ms;

	// Compute the last address
	last_blocks_addr = sd_mmc_get_capacity(slot) *
			(1024 / SD_MMC_BLOCK_SIZE);
	if (last_blocks_addr < (TEST_MEM_START_OFFSET / 512lu)) {
		printf("[Memory is too small.]\n\r");
		return;
	}
	last_blocks_addr -= (TEST_MEM_START_OFFSET / SD_MMC_BLOCK_SIZE);

	printf("Card R/W test:\n\r");

	// Read the last block
	printf("    Read... ");
	tick_start = time_tick_get();
	if (SD_MMC_OK != sd_mmc_init_read_blocks(slot,
			last_blocks_addr,
			TEST_MEM_AREA_SIZE / SD_MMC_BLOCK_SIZE)) {
		printf("[FAIL]\n\r");
		return;
	}
	for (nb_trans = 0; nb_trans < (TEST_MEM_AREA_SIZE / TEST_MEM_ACCESS_SIZE);
			nb_trans++) {
		if (SD_MMC_OK != sd_mmc_start_read_blocks(buf_test,
					TEST_MEM_ACCESS_SIZE / SD_MMC_BLOCK_SIZE)) {
			printf("[FAIL]\n\r");
			return;
		}
		if (SD_MMC_OK != sd_mmc_wait_end_of_read_blocks(false)) {
			printf("[FAIL]\n\r");
			return;
		}		
	}
	time_ms = time_tick_calc_delay(tick_start, time_tick_get());
	if (time_ms) { // Valid time_ms
		printf(" %d KBps ", (int)(((TEST_MEM_AREA_SIZE
				* 1000lu) / 1024lu) / time_ms));
	}
	printf("[OK]\n\r");

	if (sd_mmc_is_write_protected(slot)) {
		printf("Card is write protected [WRITE TEST SKIPPED]\n\r");
		return;
	}
	
	// Fill buffer with a pattern
	for (i = 0; i < (TEST_MEM_ACCESS_SIZE / sizeof(uint32_t)); i++) {
		((uint32_t*)buf_test)[i] = TEST_FILL_VALUE_U32;
	}

	printf("    Write pattern... ");
	if (SD_MMC_OK != sd_mmc_init_write_blocks(slot,
			last_blocks_addr,
			TEST_MEM_AREA_SIZE / SD_MMC_BLOCK_SIZE)) {
		printf("[FAIL]\n\r");
		return;
	}
	tick_start = time_tick_get();
	for (nb_trans = 0; nb_trans < (TEST_MEM_AREA_SIZE / TEST_MEM_ACCESS_SIZE);
			nb_trans++) {
		((uint32_t*)buf_test)[0] = nb_trans; // Unique value for each area
		if (SD_MMC_OK != sd_mmc_start_write_blocks(buf_test,
				TEST_MEM_ACCESS_SIZE / SD_MMC_BLOCK_SIZE)) {
			printf("[FAIL]\n\r");
			return;
		}
		if (SD_MMC_OK != sd_mmc_wait_end_of_write_blocks(false)) {
			printf("[FAIL]\n\r");
			return;
		}
	}
	time_ms = time_tick_calc_delay(tick_start, time_tick_get());
	if (time_ms) { // Valid time_ms
		printf(" %d KBps ", (int)(((TEST_MEM_AREA_SIZE
				* 1000lu) / 1024lu) / time_ms));
	}
	printf("[OK]\n\r");

	printf("    Read and check pattern... ");
	if (SD_MMC_OK != sd_mmc_init_read_blocks(slot,
			last_blocks_addr,
			TEST_MEM_AREA_SIZE / SD_MMC_BLOCK_SIZE)) {
		printf("Read [FAIL]\n\r");
		return;
	}
	for (nb_trans = 0; nb_trans < (TEST_MEM_AREA_SIZE / TEST_MEM_ACCESS_SIZE);
			nb_trans++) {
		// Clear buffer
		for (i = 0; i < (TEST_MEM_ACCESS_SIZE / sizeof(uint32_t)); i++) {
			((uint32_t*)buf_test)[i] = 0xFFFFFFFF;
		}
		// Fill buffer
		if (SD_MMC_OK != sd_mmc_start_read_blocks(buf_test,
					TEST_MEM_ACCESS_SIZE / SD_MMC_BLOCK_SIZE)) {
			printf("Read [FAIL]\n\r");
			return;
		}
		if (SD_MMC_OK != sd_mmc_wait_end_of_read_blocks(false)) {
			printf("Read [FAIL]\n\r");
			return;
		}
		// Check the unique value of the area
		if (((uint32_t*)buf_test)[0] != nb_trans) {
			printf("Check [FAIL]\n\r");
			return;
		}
		// Check buffer
		for (i = 1; i < (TEST_MEM_ACCESS_SIZE / sizeof(uint32_t)); i++) {
			if (((uint32_t*)buf_test)[i] != TEST_FILL_VALUE_U32) {
				printf("Check [FAIL]\n\r");
				return;
			}
		}
	}
	printf("[OK]\n\r");
}

