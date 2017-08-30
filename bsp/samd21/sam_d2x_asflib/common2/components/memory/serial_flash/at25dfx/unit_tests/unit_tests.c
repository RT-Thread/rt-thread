/**
 * \file
 *
 * \brief Unit tests for AT25DFx driver.
 *
 * Copyright (C) 2013-2015 Atmel Corporation. All rights reserved.
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
 * \mainpage AT25DFx SerialFlash Driver Unit Test
 *
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 *
 * This application runs a suite of tests for the AT25DFx SerialFlash driver
 * with any SPI HAL that is supported by the driver and for which setup code
 * has been added to this application.
 */

/**
 * \page appdoc_main AT25DFx SerialFlash Driver Unit Test
 *
 * Overview:
 * - \ref appdoc_common2_at25dfx_unit_test_intro
 * - \ref appdoc_common2_at25dfx_unit_test_setup
 * - \ref appdoc_common2_at25dfx_unit_test_compinfo
 * - \ref appdoc_common2_at25dfx_unit_test_contactinfo
 *
 *
 * \section appdoc_common2_at25dfx_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The test suite consists of test cases for the following functionality:
 * - chip presence checking
 * - reading and writing of buffers
 * - chip erase
 * - block erase
 * - global protection
 * - sector protection
 * - sleeping and waking
 *
 * The test suite has been written to test with an AT25DF081A on the EXT1 header
 * of an Xplained Pro board.
 *
 * Test reporting is done via UART configured on \ref CONF_STDIO_USART_MODULE,
 * with baud rate \ref CONF_STDIO_BAUDRATE. The convention is to use EDBG CDC.
 *
 *
 * \section appdoc_common2_at25dfx_unit_test_setup Setup
 *
 * Connect a SerialFlash () wing board to EXT1 of the Xplained Pro.
 * The SPI pin mapping is according to the convention, meaning the regular MISO,
 * MOSI, SCK and SS_0 as defined in the board definition header file.
 *
 * \note SS_1 is used as a dummy pin in verification of presence checking.
 *
 *
 * \section appdoc_common2_at25dfx_unit_test_compinfo Compilation Info
 *
 * This software was written for the GNU GCC for ARM.
 * Other compilers may or may not work.
 *
 *
 * \section appdoc_common2_at25dfx_unit_test_contactinfo Contact Information
 *
 * For further information, visit
 * <a href="http://www.atmel.com">http://www.atmel.com</a>.
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <conf_test.h>
#include <conf_at25dfx.h>

#define TEST_BUFFER_SIZE  16
#define TEST_ERASE_VALUE  0xff
#define TEST_FLASH_SIZE   (1024 * 1024UL)
#define TEST_PAGE_SIZE    256


static at25dfx_spi_module_t at25dfx_spi;

static struct at25dfx_chip_module at25dfx_chip;
static struct at25dfx_chip_module at25dfx_dummy;
static struct usart_module cdc_uart_module;

static uint8_t test_rx_buffer[TEST_BUFFER_SIZE];
static uint8_t test_tx_buffer[TEST_BUFFER_SIZE] = {
		0x12, 0x34, 0x56, 0x78,
		0x9a, 0xbc, 0xde, 0xf0,
		0x21, 0x43, 0x65, 0x87,
		0xa9, 0xcb, 0xed, 0x0f,
	};


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

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

static void test_at25dfx_init(void)
{
	struct at25dfx_chip_config at25dfx_chip_config;

#ifdef CONF_TEST_VECTORED_MASTER
	struct spi_master_vec_config at25dfx_spi_config;
	at25dfx_spi_master_vec_get_config_defaults(&at25dfx_spi_config);
	at25dfx_spi_config.baudrate = AT25DFX_CLOCK_SPEED;
#else
	struct spi_config at25dfx_spi_config;
	at25dfx_spi_get_config_defaults(&at25dfx_spi_config);
	at25dfx_spi_config.mode_specific.master.baudrate = AT25DFX_CLOCK_SPEED;
#endif

	at25dfx_spi_config.mux_setting = AT25DFX_SPI_PINMUX_SETTING;
	at25dfx_spi_config.pinmux_pad0 = AT25DFX_SPI_PINMUX_PAD0;
	at25dfx_spi_config.pinmux_pad1 = AT25DFX_SPI_PINMUX_PAD1; 
	at25dfx_spi_config.pinmux_pad2 = AT25DFX_SPI_PINMUX_PAD2;
	at25dfx_spi_config.pinmux_pad3 = AT25DFX_SPI_PINMUX_PAD3;

#ifdef CONF_TEST_VECTORED_MASTER
	spi_master_vec_init(&at25dfx_spi, AT25DFX_SPI, &at25dfx_spi_config);
	spi_master_vec_enable(&at25dfx_spi);
#else
	spi_init(&at25dfx_spi, AT25DFX_SPI, &at25dfx_spi_config);
	spi_enable(&at25dfx_spi);
#endif

	// Initialize real and dummy chip
	at25dfx_chip_config.type = AT25DFX_MEM_TYPE;
	at25dfx_chip_config.cs_pin = AT25DFX_CS;

	at25dfx_chip_init(&at25dfx_chip, &at25dfx_spi, &at25dfx_chip_config);

	at25dfx_chip_config.cs_pin = EXT1_PIN_SPI_SS_1;

	at25dfx_chip_init(&at25dfx_dummy, &at25dfx_spi, &at25dfx_chip_config);
}


//! \name Tests
//@{

static void run_check_presence_test(const struct test_case *test)
{
	enum status_code status;

	status = at25dfx_chip_check_presence(&at25dfx_chip);
	test_assert_true(test, status == STATUS_OK,
			"Failed to detect presence of chip");

	status = at25dfx_chip_check_presence(&at25dfx_dummy);
	test_assert_true(test, status == STATUS_ERR_NOT_FOUND,
			"Failed to detect absence of chip");
}


static void run_read_write_buffer_test(const struct test_case *test)
{
	enum status_code status;

// Globally disable sector protect
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);

// Read out of bounds, verify ARG ERROR status
	status = at25dfx_chip_read_buffer(&at25dfx_chip,
			TEST_FLASH_SIZE, test_rx_buffer, 1);
	test_assert_true(test, status == STATUS_ERR_INVALID_ARG,
			"Failed to detect out of bounds read");

// Write out of bounds, verify ARG ERROR status
	status = at25dfx_chip_write_buffer(&at25dfx_chip,
			TEST_FLASH_SIZE, test_tx_buffer, 1);
	test_assert_true(test, status == STATUS_ERR_INVALID_ARG,
			"Failed to detect out of bounds write");

// Erase device
	at25dfx_chip_erase(&at25dfx_chip);

// Write first byte
	status = at25dfx_chip_write_buffer(&at25dfx_chip,
			0, &test_tx_buffer[0], 1);
	test_assert_true(test, status == STATUS_OK,
			"Failed to write first byte");

// Write last byte
	status = at25dfx_chip_write_buffer(&at25dfx_chip,
			TEST_FLASH_SIZE - 1, &test_tx_buffer[1], 1);
	test_assert_true(test, status == STATUS_OK,
			"Failed to write last byte");

// Read two first bytes back, verify values
	status = at25dfx_chip_read_buffer(&at25dfx_chip,
			0, &test_rx_buffer[0], 2);
	test_assert_true(test, status == STATUS_OK,
			"Failed to read two first bytes");

	test_assert_true(test,
			(test_rx_buffer[0] == test_tx_buffer[0])
			&& (test_rx_buffer[1] == TEST_ERASE_VALUE),
			"Verification of two first bytes failed");

// Read last byte back, verify value
	status = at25dfx_chip_read_buffer(&at25dfx_chip,
			TEST_FLASH_SIZE - 1, &test_rx_buffer[1], 1);
	test_assert_true(test, status == STATUS_OK,
			"Failed to read last byte");

	test_assert_true(test, test_rx_buffer[1] == test_tx_buffer[1],
			"Verification of last byte failed");

// Do write of multiple bytes across page boundary
	status = at25dfx_chip_write_buffer(&at25dfx_chip,
			TEST_PAGE_SIZE - TEST_BUFFER_SIZE/2,
			&test_tx_buffer[0], TEST_BUFFER_SIZE);
	test_assert_true(test, status == STATUS_OK,
			"Failed to write across page boundary");

// Read bytes back, verify
	status = at25dfx_chip_read_buffer(&at25dfx_chip,
			TEST_PAGE_SIZE - TEST_BUFFER_SIZE/2,
			&test_rx_buffer[0], TEST_BUFFER_SIZE);
	test_assert_true(test, status == STATUS_OK,
			"Failed to read multiple bytes");

	test_assert_true(test,
			test_rx_buffer[0] == test_tx_buffer[0],
			"Verification of cross page boundary write failed at first byte");
	test_assert_true(test,
			test_rx_buffer[TEST_BUFFER_SIZE/2 - 1] == test_tx_buffer[TEST_BUFFER_SIZE/2 - 1],
			"Verification of cross page boundary write failed at last byte in first page");
	test_assert_true(test,
			test_rx_buffer[TEST_BUFFER_SIZE/2] == test_tx_buffer[TEST_BUFFER_SIZE/2],
			"Verification of cross page boundary write failed at first byte in new page");
	test_assert_true(test,
			test_rx_buffer[TEST_BUFFER_SIZE - 1] == test_tx_buffer[TEST_BUFFER_SIZE - 1],
			"Verification of cross page boundary write failed at last byte in new page");
}

static void run_erase_test(const struct test_case *test)
{
	enum status_code status;

// Globally disable sector protect
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);

// Write first and last byte
	at25dfx_chip_write_buffer(&at25dfx_chip, 0, &test_tx_buffer[0], 1);
	at25dfx_chip_write_buffer(&at25dfx_chip, TEST_FLASH_SIZE - 1, &test_tx_buffer[1], 1);

// Do chip erase
	status = at25dfx_chip_erase(&at25dfx_chip);
	test_assert_true(test, status == STATUS_OK,
			"Failed to erase chip");

// Read back first and last byte
	at25dfx_chip_read_buffer(&at25dfx_chip,	0, &test_rx_buffer[0], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip,	TEST_FLASH_SIZE - 1, &test_rx_buffer[1], 1);

// Verify both bytes erased
	test_assert_true(test,
			(test_rx_buffer[0] == TEST_ERASE_VALUE)
			&& (test_rx_buffer[1] == TEST_ERASE_VALUE),
			"Verification of chip erase failed");
}

static void run_erase_block_test(const struct test_case *test)
{
	enum status_code status;

// Globally disable sector protect
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);

// Erase out of bounds block, verify ARG ERR status
	status = at25dfx_chip_erase_block(&at25dfx_chip,
		TEST_FLASH_SIZE, AT25DFX_BLOCK_SIZE_4KB);
	test_assert_true(test, status == STATUS_ERR_INVALID_ARG,
			"Failed to detect out of bounds erase");

// Write to first byte, 4k boundary, 32k boundary and 64k boundary
	at25dfx_chip_write_buffer(&at25dfx_chip, 0, &test_tx_buffer[0], 1);
	at25dfx_chip_write_buffer(&at25dfx_chip, 1UL << 12, &test_tx_buffer[1], 1);
	at25dfx_chip_write_buffer(&at25dfx_chip, 1UL << 15, &test_tx_buffer[2], 1);
	at25dfx_chip_write_buffer(&at25dfx_chip, 1UL << 16, &test_tx_buffer[3], 1);

// Erase first 4 k block
	at25dfx_chip_erase_block(&at25dfx_chip, 0, AT25DFX_BLOCK_SIZE_4KB);
	
// Verify byte 0 erased, others intact
	at25dfx_chip_read_buffer(&at25dfx_chip, 0, &test_rx_buffer[0], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 12, &test_rx_buffer[1], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 15, &test_rx_buffer[2], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 16, &test_rx_buffer[3], 1);
	test_assert_true(test,
			(test_rx_buffer[0] == TEST_ERASE_VALUE)
			&& (test_rx_buffer[1] == test_tx_buffer[1])
			&& (test_rx_buffer[2] == test_tx_buffer[2])
			&& (test_rx_buffer[3] == test_tx_buffer[3]),
			"Verification of 4 kB block erase failed");

// Erase first 32 k block
	at25dfx_chip_erase_block(&at25dfx_chip, 0, AT25DFX_BLOCK_SIZE_32KB);

// Verify byte 2^14 erased, 2^15 intact
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 12, &test_rx_buffer[1], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 15, &test_rx_buffer[2], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 16, &test_rx_buffer[3], 1);
	test_assert_true(test,
			(test_rx_buffer[1] == TEST_ERASE_VALUE)
			&& (test_rx_buffer[2] == test_tx_buffer[2])
			&& (test_rx_buffer[3] == test_tx_buffer[3]),
			"Verification of 32 kB block erase failed");

// Erase first 64 k block
	at25dfx_chip_erase_block(&at25dfx_chip, 0, AT25DFX_BLOCK_SIZE_64KB);

// Verify byte 2^15 erased, 2^16 intact
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 15, &test_rx_buffer[2], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, 1UL << 16, &test_rx_buffer[3], 1);
	test_assert_true(test,
			(test_rx_buffer[2] == TEST_ERASE_VALUE)
			&& (test_rx_buffer[3] == test_tx_buffer[3]),
			"Verification of 64 kB block erase failed");
}

static void run_global_sector_protect_test(const struct test_case *test)
{
	enum status_code status;

// Globally disable sector protect
	status = at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);
	test_assert_true(test, status == STATUS_OK,
			"Failed to globally disable sector protection");

// Write to first and last byte
	at25dfx_chip_write_buffer(&at25dfx_chip, 0, &test_tx_buffer[0], 1);
	at25dfx_chip_write_buffer(&at25dfx_chip, TEST_FLASH_SIZE - 1, &test_tx_buffer[1], 1);

// Globally enable protect
	status = at25dfx_chip_set_global_sector_protect(&at25dfx_chip, true);
	test_assert_true(test, status == STATUS_OK,
			"Failed to globally enable sector protection");

// Attempt chip erase
	at25dfx_chip_erase(&at25dfx_chip);

// Verify bytes intact
	at25dfx_chip_read_buffer(&at25dfx_chip, 0, &test_rx_buffer[0], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, TEST_FLASH_SIZE - 1, &test_rx_buffer[1], 1);
	test_assert_true(test,
			(test_rx_buffer[0] == test_tx_buffer[0])
			&& (test_rx_buffer[1] == test_tx_buffer[1]),
			"Verification of intact bytes failed");

// Globally disable protect
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);

// Attempt chip erase
	at25dfx_chip_erase(&at25dfx_chip);

// Verify bytes erased
	at25dfx_chip_read_buffer(&at25dfx_chip, 0, &test_rx_buffer[0], 1);
	at25dfx_chip_read_buffer(&at25dfx_chip, TEST_FLASH_SIZE - 1, &test_rx_buffer[1], 1);
	test_assert_true(test,
			(test_rx_buffer[0] == TEST_ERASE_VALUE)
			&& (test_rx_buffer[1] == TEST_ERASE_VALUE),
			"Verification of erased bytes failed");
}

static void run_set_get_sector_protect_test(const struct test_case *test)
{
	bool protect_1, protect_2;
	enum status_code status;

// Globally disable sector protect
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);

// Get out of bounds sector protect
	status = at25dfx_chip_get_sector_protect(&at25dfx_chip, TEST_FLASH_SIZE, &protect_1);
	test_assert_true(test, status == STATUS_ERR_INVALID_ARG,
			"Failed to detect getting out of bounds sector protect");

// Set out of bounds sector protect
	status = at25dfx_chip_set_sector_protect(&at25dfx_chip, TEST_FLASH_SIZE, true);
	test_assert_true(test, status == STATUS_ERR_INVALID_ARG,
			"Failed to detect setting out of bounds sector protect");

// Get sector protect of first and last sector
	status = at25dfx_chip_get_sector_protect(&at25dfx_chip, 0, &protect_1);
	test_assert_true(test, status == STATUS_OK,
			"Failed to get first sector protect");

	status = at25dfx_chip_get_sector_protect(&at25dfx_chip, TEST_FLASH_SIZE - 1, &protect_2);
	test_assert_true(test, status == STATUS_OK,
			"Failed to get last sector protect");

	test_assert_true(test,
			(protect_1 == false)
			&& (protect_2 == false),
			"Verification of sector protect getting failed");

// Set and clear sector protect of first sector
	status = at25dfx_chip_set_sector_protect(&at25dfx_chip, 0, true);
	test_assert_true(test, status == STATUS_OK,
			"Failed to set first sector protect");

	status = at25dfx_chip_set_sector_protect(&at25dfx_chip, 0, false);
	test_assert_true(test, status == STATUS_OK,
			"Failed to clear first sector protect");

// Set sector protect of last sector
	status = at25dfx_chip_set_sector_protect(&at25dfx_chip, TEST_FLASH_SIZE - 1, true);
	test_assert_true(test, status == STATUS_OK,
			"Failed to set last sector protect");

// Get sector protects and verify 
	at25dfx_chip_get_sector_protect(&at25dfx_chip, 0, &protect_1);
	at25dfx_chip_get_sector_protect(&at25dfx_chip, TEST_FLASH_SIZE - 1, &protect_2);

	test_assert_true(test, protect_1 == false,
			"Verification of sector protect clear failed");
	test_assert_true(test, protect_2 == true,
			"Verification of sector protect set failed");
}

static void run_sleep_wake_test(const struct test_case *test)
{
	// Globally disable sector protect
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);

	// Erase first block
	at25dfx_chip_erase_block(&at25dfx_chip, 0, AT25DFX_BLOCK_SIZE_4KB);
	at25dfx_chip_write_buffer(&at25dfx_chip, 0, &test_tx_buffer[0], 1);

	// Put device to sleep
	at25dfx_chip_sleep(&at25dfx_chip);

	// Read out first byte, verify device did not respond
	at25dfx_chip_read_buffer(&at25dfx_chip, 0, &test_rx_buffer[0], 1);
	test_assert_true(test, test_rx_buffer[0] == 0,
			"Verification of read during sleep failed");

	// Wake device up
	at25dfx_chip_wake(&at25dfx_chip);

	// Redo test, verify device response
	at25dfx_chip_read_buffer(&at25dfx_chip, 0, &test_rx_buffer[0], 1);
	test_assert_true(test, test_rx_buffer[0] == test_tx_buffer[0],
			"Verification of read during wake failed");
}

//@}

int main(void)
{
	system_init();
	cdc_uart_init();
	test_at25dfx_init();

	DEFINE_TEST_CASE(check_presence_test, NULL,
			run_check_presence_test, NULL,
			"Testing presence checking");

	DEFINE_TEST_CASE(read_write_buffer_test, NULL,
			run_read_write_buffer_test, NULL,
			"Testing read and write");

	DEFINE_TEST_CASE(erase_test, NULL,
			run_erase_test, NULL,
			"Testing chip erase");

	DEFINE_TEST_CASE(erase_block_test, NULL,
			run_erase_block_test, NULL,
			"Testing block erase");

	DEFINE_TEST_CASE(global_sector_protect_test, NULL,
			run_global_sector_protect_test, NULL,
			"Testing global sector protect setting");

	DEFINE_TEST_CASE(set_get_sector_protect_test, NULL,
			run_set_get_sector_protect_test, NULL,
			"Testing sector protect setting and getting");

	DEFINE_TEST_CASE(sleep_wake_test, NULL,
			run_sleep_wake_test, NULL,
			"Testing sleep and wake");

	DEFINE_TEST_ARRAY(at25dfx_tests) = {
		&check_presence_test,
		&read_write_buffer_test,
		&erase_test,
		&erase_block_test,
		&global_sector_protect_test,
		&set_get_sector_protect_test,
		&sleep_wake_test,
	};

	DEFINE_TEST_SUITE(at25dfx_test_suite, at25dfx_tests,
			"AT25DFx driver test suite");

	test_suite_run(&at25dfx_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
