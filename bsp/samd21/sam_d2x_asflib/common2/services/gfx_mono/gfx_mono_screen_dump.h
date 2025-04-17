/**
 * \file
 *
 * \brief Service for performing a screen dump to XPM image file
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef GFX_MONO_SCREEN_DUMP_H_INCLUDED
#define GFX_MONO_SCREEN_DUMP_H_INCLUDED

#include <drivers/dev_serial.h>
#include <gfx_mono.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_screen_dump XPM USART Screendump functions
 *
 * This service will add the possibility to dump the LCD screen to the USART
 * using the XPM file format.
 *
 * Before using the screen dump function one should make sure that one has
 * performed initialization of this service by calling
 * \ref gfx_mono_screen_dump_init() to set up which USART to use. One should
 * also make sure that one has initialized the gfx mono driver
 * \ref gfx_mono_init() which will produce the screen buffer that is dumped
 * trough the USART.
 *
 * \section asfdoc_common2_screen_dump_dependencies Dependencies
 * This driver depends on the following modules:
 * - asfdoc_samd20_sercom_spi_group
 * @{
 */

/** TODO: This define should be fetched from the GFX display header file. */
#define LCD_PAGE_HEIGHT 8
#define GFX_MONO_LCD_PAGE_COUNT GFX_MONO_LCD_HEIGHT / LCD_PAGE_HEIGHT

/* Define used for stringifying number defines */
#define str(s) # s

#define _XPM_HEADER(w, h) "/* XPM */\r\n" \
	"static char * asf_screen_dump[] = {\r\n" \
	"\"" str(w) " " str(h) " 2 1\",\r\n" \
	"\"   c #FFFFFF\",\r\n"	\
	"\".  c #000000\",\r\n"

#define XPM_HEADER _XPM_HEADER(GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT)

#if UC3
typedef avr32_usart_t dump_usart_t;
#elif XMEGA
typedef USART_t dump_usart_t;
#endif

/** storage for the usart to use when dumping data */
dump_usart_t *dump_usart;

static const uint8_t xpm_header[] = XPM_HEADER;

/**
 * \brief Init the framebuffer dump function
 *
 * \param[in] usart   pointer to the USART to use for dumping the image
 * \param[in] options pointer to the USART options, see documentation
 *
 */
static inline void gfx_mono_screen_dump_init(dump_usart_t *usart,
		const usart_serial_options_t *options)
{
	dump_usart = usart;
	usart_serial_init(usart, options);
}

/**
 * \brief Function for dumping a LCD framebuffer
 *
 * This function will dump a framebuffer to a UART in XPM file format.
 */
static inline void gfx_mono_screen_dump(void)
{
	uint8_t page_buffer[GFX_MONO_LCD_WIDTH];
	/* wait to receive a character on UART before sending */
	uint8_t dummy;
	usart_serial_getchar(dump_usart, &dummy);

	/* write the XPM header */
	usart_serial_write_packet(dump_usart, xpm_header,
			(sizeof(xpm_header) - 1));

	for (uint8_t page = 0; page < GFX_MONO_LCD_PAGE_COUNT; ++page) {
		gfx_mono_get_page(page_buffer, page, 0, GFX_MONO_LCD_WIDTH);
		for (uint8_t row = 0; row < LCD_PAGE_HEIGHT; ++row) {
			usart_putchar(dump_usart, '"');
			for (uint16_t column = 0; column < GFX_MONO_LCD_WIDTH;
					++column) {
				if ((page_buffer[column] & (0x01 << row)) !=
						0x00) {
					usart_putchar(dump_usart, '.');
				} else {
					usart_putchar(dump_usart, ' ');
				}
			}
			usart_serial_write_packet(dump_usart,
					(uint8_t *)"\",\r\n", 4);
		}
	}
	usart_serial_write_packet(dump_usart, (uint8_t *)"};\r\n", 4);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_SCREEN_DUMP_H_INCLUDED */
