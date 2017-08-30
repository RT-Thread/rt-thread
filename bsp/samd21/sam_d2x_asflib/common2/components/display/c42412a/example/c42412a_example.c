/**
 * \file
 *
 * \brief C42412A LCD Glass component example for SAM.
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
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
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the C42412A LCD Glass component example.
 * It also comes bundled with an application-example of usage.
 *
 * This example demonstrates how to use the C42412A LCD Glass driver.
 *
 * The supported board list:
 *    - SAM L22 Xplained Pro
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * The SEGMENT LCD1 Xplained Pro extension board must be connected to SAM devices.
 *
 * \section configinfo Configuration Information
 * - PC terminal settings:
 *   - 115200 bps,
 *   - 8 data bits,
 *   - no parity bit,
 *   - 1 stop bit,
 *   - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com">Atmel</A>.\n
 * Support and FAQ: http://www.atmel.com/design-support/
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <string.h>
#include "config_c42412a.h"
struct usart_module usart_instance;

/**
 *  Configure serial console.
 */
static void configure_console(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate = 38400;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
}

static void c42412a_icon_test(void)
{
	c42412a_show_icon(C42412A_ICON_COLON);
	delay_s(1);
	c42412a_show_battery(C42412A_BATTERY_THREE);
	delay_s(1);
	c42412a_show_battery(C42412A_BATTERY_ONE);
	delay_s(1);
	c42412a_show_wireless(C42412A_WIRELESS_THREE);
	delay_s(1);
	c42412a_show_wireless(C42412A_WIRELESS_TWO);
	delay_s(1);
	c42412a_show_icon(C42412A_ICON_AUDIO_PLAY);
	delay_s(1);
	c42412a_clear_icon(C42412A_ICON_COLON);
}
static void c42412a_blink_test(void)
{
	c42412a_blink_icon_start(C42412A_ICON_USB);
	c42412a_blink_icon_start(C42412A_ICON_ATMEL);
	delay_s(1);
	c42412a_blink_icon_stop(C42412A_ICON_USB);
}
static void c42412a_text_test(void)
{
	c42412a_clear_text();
	c42412a_show_text((const uint8_t *)"Hi");
	delay_s(1);
	c42412a_clear_text();
	c42412a_show_text((const uint8_t *)"Hello");
	delay_s(1);
	c42412a_clear_text();
	c42412a_show_text((const uint8_t *)"Atmel");
}

static void c42412a_num_dec_test(void)
{
	c42412a_clear_numeric_dec();
	c42412a_show_numeric_dec(12);
	delay_s(1);
	c42412a_clear_numeric_dec();
	c42412a_show_numeric_dec(345);
	delay_s(1);
	c42412a_clear_numeric_dec();
	c42412a_show_numeric_dec(6789);
	delay_s(1);
	c42412a_clear_numeric_dec();
	c42412a_show_numeric_dec(-98765);
	delay_s(1);
	c42412a_clear_numeric_dec();
	c42412a_show_numeric_dec(-198765);
}

static void c42412a_animation_test(void)
{
	c42412a_circular_animation_start(8,0x0f);
}

/**
 * \brief main function : do init and loop
 */
int main(void)
{
	system_init();
	configure_console();
	delay_init();

	/* Turn on the backlight. */
	port_pin_set_output_level(SLCD_BACLKLIGHT,true);

	printf("Start SLCD test\r\n");
	/* Initialize the C42412A LCD glass component. */
	c42412a_init();

	c42412a_show_all();
	c42412a_set_contrast(0x8);
	delay_s(1);
	c42412a_clear_all();

	c42412a_icon_test();
	delay_s(1);
	c42412a_blink_test();
	delay_s(1);
	c42412a_text_test();
	delay_s(1);
	c42412a_num_dec_test();
	delay_s(1);
	c42412a_animation_test();
	while (1) {
	}
}

