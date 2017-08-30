/**
 * \file
 *
 * \brief SD/MMC card unit tests
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
 * \mainpage SD/MMC Card Unit tests
 *
 * \section intro Introduction
 * This is the unit test application for the SD/MMC stack.
 * It consists of test cases for the following functionalities:
 * - SD/MMC card initialization.
 * - SD/MMC card read and write test.
 * The SD/MMC stack supports all MCI/SPI interfaces from AVR and SAM devices.
 *
 * \note Please connect a SD/MMC card on the board before running the test.
 * While using Xplained Pro evaluation kits, the IO1 Xplained Pro
 * extension board should be attached to EXT1.
 *
 * \section Description
 *
 * The unit tests executes the following sequences:
 * - Wait a card insertion on the first slot of the board
 * - Inilialize an SD, MMC card.
 * - If the inserted card is an SD or MMC card, test read/write access.
 * Three modes are tested: SINGLE, MULTIPLE block, and fragmented MULTIPLE block.
 *     - Read data from the card, save it
 *     - Write data into the card
 *     - Read data from the card
 *     - Verify the written data.
 *     - Write the data saved
 *     - Read the data saved
 *     - Verify the written data.
 *
 * The example outputs the information through the standard utput (stdio).
 * To know the output used by the board, look in  the conf_test.h file
 * and connect a terminal on the correct port.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.atmel.com/">Atmel</a>.\n
 * Support and FAQ: http://www.atmel.com/design-support/
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <conf_test.h>
#include "sd_mmc_protocol.h"

//! \name Test configurations
//! @{
//! Number of blocks for multiple read or write
#define NB_MULTI_BLOCKS     (2)

//! The value used to generate test data
#define TEST_FILL_VALUE_U32     (0x5500AAFFU)

//! Buffer used to save the sector area used by read/write tests
COMPILER_WORD_ALIGNED
static uint8_t buf_save[SD_MMC_BLOCK_SIZE * NB_MULTI_BLOCKS];

//! Buffer used by read/write tests
COMPILER_WORD_ALIGNED
static uint8_t buf_test[SD_MMC_BLOCK_SIZE * NB_MULTI_BLOCKS];

//! Read and write test length of CIA in bytes
#define TEST_CIA_SIZE           (0x16)

//! Structure for UART module connected to EDBG (used for unit test output)
struct usart_module cdc_uart_module;
//! @}


/**
 * \brief SD/MMC card read and write test.
 *
 * \param test Current test case.
 * \param nb_block Test blocks.
 * \param split_tansfer Split transfer setting.
 */
static void rw_test(const struct test_case *test, uint16_t nb_block,
		bool split_tansfer)
{
	uint32_t i;
	uint32_t last_blocks_addr;
	uint16_t nb_trans;

	/* Compute the last address */
	last_blocks_addr = sd_mmc_get_capacity(0) * (1024/SD_MMC_BLOCK_SIZE) - 50;
	test_assert_true(test, last_blocks_addr > NB_MULTI_BLOCKS,
			"Error: SD/MMC capacity.");

	last_blocks_addr -= NB_MULTI_BLOCKS;
	
	/* Read (save blocks) the last blocks */
	test_assert_true(test, SD_MMC_OK ==
			sd_mmc_init_read_blocks(0, last_blocks_addr, nb_block),
			"Error: SD/MMC initialize read sector(s).");

	for (nb_trans = 0; nb_trans < (split_tansfer? nb_block : 1); nb_trans++) {
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_start_read_blocks(
				&buf_save[nb_trans * SD_MMC_BLOCK_SIZE],
				split_tansfer? 1 : nb_block),
				"Error: SD/MMC start read sector(s).");
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_wait_end_of_read_blocks(false),
				"Error: SD/MMC wait end of read sector(s).");
	}

	test_assert_true(test, !sd_mmc_is_write_protected(0),
			"Error: SD/MMC is write protected.");

	/* Fill buffer */
	for (i = 0; i < (SD_MMC_BLOCK_SIZE * nb_block / sizeof(uint32_t)); i++) {
		((uint32_t*)buf_test)[i] = TEST_FILL_VALUE_U32;
	}
	
	/* Write the last blocks */
	test_assert_true(test, SD_MMC_OK ==
			sd_mmc_init_write_blocks(0, last_blocks_addr, nb_block),
			"Error: SD/MMC initialize write sector(s).");

	for (nb_trans = 0; nb_trans < (split_tansfer? nb_block : 1); nb_trans++) {
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_start_write_blocks(
				&buf_test[nb_trans * SD_MMC_BLOCK_SIZE],
				split_tansfer? 1 : nb_block),
				"Error: SD/MMC start write sector(s).");
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_wait_end_of_write_blocks(false),
				"Error: SD/MMC wait end of write sector(s).");
	}

	/* Clean buffer */
	for (i = 0; i < (SD_MMC_BLOCK_SIZE * nb_block / sizeof(uint32_t)); i++) {
		((uint32_t*)buf_test)[i] = 0xFFFFFFFF;
	}

	/* Read the last block */
	test_assert_true(test, SD_MMC_OK ==
			sd_mmc_init_read_blocks(0, last_blocks_addr, nb_block),
			"Error: SD/MMC initialize read sector(s).");

	for (nb_trans = 0; nb_trans < (split_tansfer? nb_block : 1); nb_trans++) {
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_start_read_blocks(
				&buf_test[nb_trans * SD_MMC_BLOCK_SIZE],
				split_tansfer? 1 : nb_block),
				"Error: SD/MMC start read sector(s).");
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_wait_end_of_read_blocks(false),
				"Error: SD/MMC wait end of read sector(s).");
	}

	/* Check buffer */
	for (i = 0; i < (SD_MMC_BLOCK_SIZE * nb_block / sizeof(uint32_t)); i++) {
		test_assert_true(test,
				((uint32_t*)buf_test)[i] == TEST_FILL_VALUE_U32,
				"Error: SD/MMC verify write operation.");
	}

	/* Write (restore) the last block */
	test_assert_true(test, SD_MMC_OK ==
			sd_mmc_init_write_blocks(0, last_blocks_addr, nb_block),
			"Error: SD/MMC initialize write restore sector(s).");

	for (nb_trans = 0; nb_trans < (split_tansfer? nb_block : 1); nb_trans++) {
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_start_write_blocks(
				&buf_save[nb_trans * SD_MMC_BLOCK_SIZE],
				split_tansfer? 1 : nb_block),
				"Error: SD/MMC start write restore sector(s).");
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_wait_end_of_write_blocks(false),
				"Error: SD/MMC wait end of write restore sector(s).");
	}

	/* Read (check restore) the last block */
	test_assert_true(test, SD_MMC_OK ==
			sd_mmc_init_read_blocks(0, last_blocks_addr, nb_block),
			"Error: SD/MMC initialize read sector(s).");

	for (nb_trans = 0; nb_trans < (split_tansfer? nb_block : 1); nb_trans++) {
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_start_read_blocks(
				&buf_test[nb_trans * SD_MMC_BLOCK_SIZE],
				split_tansfer? 1 : nb_block),
				"Error: SD/MMC start read sector(s).");
		test_assert_true(test, SD_MMC_OK ==
				sd_mmc_wait_end_of_read_blocks(false),
				"Error: SD/MMC wait end of read sector(s).");
	}

	/* Check buffer restored */
	for (i = 0; i < (SD_MMC_BLOCK_SIZE * nb_block / sizeof(uint32_t)); i++) {
		test_assert_true(test,
				((uint32_t*)buf_test)[i] == ((uint32_t*)buf_save)[i],
				"Error: SD/MMC verify restore operation.");
	}
}

/**
 * \brief SD/MMC stack initialization test.
 *
 * \param test Current test case.
 */
static void run_sd_mmc_init_test(const struct test_case *test)
{
	sd_mmc_err_t err;

	/* Initialize SD MMC stack */
	sd_mmc_init();

	/* Wait card connection */
	do {
		err = sd_mmc_check(0);
	} while (SD_MMC_ERR_NO_CARD == err);

	/* Check if the first state is an initialization */
	test_assert_true(test, err == SD_MMC_INIT_ONGOING,
			"No card initialization phase detected.");

	/* Check if the second step is an installation success */
	test_assert_true(test, sd_mmc_check(0) == SD_MMC_OK,
			"SD/MMC card initialization failed.");
}

/**
 * \brief SD/MMC card read and write test.
 *
 * \param test Current test case.
 */
static void run_sd_mmc_rw_test(const struct test_case *test)
{
	test_assert_true(test, SD_MMC_OK == sd_mmc_check(0),
			"SD/MMC card is not initialized OK.");

	if (sd_mmc_get_type(0) & (CARD_TYPE_SD | CARD_TYPE_MMC)) {
		rw_test(test, 1, false);
		rw_test(test, NB_MULTI_BLOCKS, false);
		rw_test(test, NB_MULTI_BLOCKS, true);
	}
}

/**
 * \brief Initialize the USART for unit test
 *
 * Initializes the SERCOM USART used for sending the unit test status to the
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
	system_init();
	delay_init();
	cdc_uart_init();

	/* Wait stdio stable */
	delay_ms(5);

	irq_initialize_vectors();
	cpu_irq_enable();

	/* Define all the test cases */
	DEFINE_TEST_CASE(sd_mmc_init_test, NULL, run_sd_mmc_init_test,
			NULL, "SD/MMC card initialization test.");

	DEFINE_TEST_CASE(sd_mmc_rw_test, NULL, run_sd_mmc_rw_test,
			NULL, "SD/MMC card read and write test.");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(sd_mmc_tests) = {
		&sd_mmc_init_test,
		&sd_mmc_rw_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(sd_mmc_suite, sd_mmc_tests,
			"SD/MMC stack test suite");

	/* Run all tests in the test suite */
	test_suite_run(&sd_mmc_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
