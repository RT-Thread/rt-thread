/**
 * \file
 *
 * \brief SSD1306 display controller driver example.
 *
 * Copyright (c) 2012-2015 Atmel Corporation. All rights reserved.
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
 * \mainpage
 *
 * \section intro Introduction
 * This simple example shows how to use the \ref ssd1306_oled_controller_group
 * for interfacing the SSD1306 controller
 *
 * \section files Main files:
 * - ssd1306_example.c: the SSD1306 low level driver example
 * - conf_ssd1306.h: configuration of the SSD1306 controller and interface
 * - conf_board.h: configuration for the board
 * - conf_clocks.h: configuration for the clocks used in the device
 * - interface configuration files.
 *
 * \section apiinfo SSD1306 low level driver API
 * The SSD1306 low level driver API can be found
 * \ref ssd1306_lcd_controller_group "here".
 *
 * \section deviceinfo Device Info
 * All devices with a SPI can be used.
 * \note Parallel interface is also possible, but not currently supported by the
 * driver.
 *
 * \section exampledescription Description of the example
 * The display is initialized and a pattern with alternating lines are drawn to
 * the entire screen. After this the screen is scrolled line by line using the
 * hardware scrolling function available in the LCD controller.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

int main(void)
{
	//! the page address to write to
	uint8_t page_address;
	//! the column address, or the X pixel.
	uint8_t column_address;
	//! store the LCD controller start draw line
	uint8_t start_line_address = 0;

	system_init();
	delay_init();

	// Initialize SPI and SSD1306 controller
	ssd1306_init();

	// set addresses at beginning of display
	ssd1306_set_page_address(0);
	ssd1306_set_column_address(0);

	// fill display with lines
	for (page_address = 0; page_address <= 8; page_address++) {
		ssd1306_set_page_address(page_address);
		for (column_address = 0; column_address < 128; column_address++) {
			ssd1306_set_column_address(column_address);
			/* fill every other pixel in the display. This will produce
			horizontal lines on the display. */
			ssd1306_write_data(0x0f);
		}
	}

	// scroll the display using hardware support in the LCD controller
	while (true) {
		ssd1306_set_display_start_line_address(start_line_address++);
		delay_ms(250);
	}
}
