/**
 * \file
 *
 * \brief Haven Display UG 2832HSWEG04 display glue code for display controller
 *
 * Copyright (c) 2013-2015 Atmel Corporation. All rights reserved.
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
#include "gfx_mono_ug_2832hsweg04.h"

/* If we are using a serial interface without readback, use framebuffer */

#ifdef CONFIG_SSD1306_FRAMEBUFFER
static uint8_t framebuffer[GFX_MONO_LCD_FRAMEBUFFER_SIZE];
#endif

/**
 * \brief Initialize SSD1306 controller and LCD display.
 * It will also write the graphic controller RAM to all zeroes.
 *
 * \note This function will clear the contents of the display.
 */
void gfx_mono_ssd1306_init(void)
{
	uint8_t page;
	uint8_t column;

#ifdef CONFIG_SSD1306_FRAMEBUFFER
	gfx_mono_set_framebuffer(framebuffer);
#endif

	/* Initialize the low-level display controller. */
	ssd1306_init();

	/* Set display to output data from line 0 */
	ssd1306_set_display_start_line_address(0);

	/* Clear the contents of the display.
	 * If using a framebuffer (SPI interface) it will both clear the
	 * controller memory and the framebuffer.
	 */
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		for (column = 0; column < GFX_MONO_LCD_WIDTH; column++) {
			gfx_mono_ssd1306_put_byte(page, column, 0x00, true);
		}
	}
}

#ifdef CONFIG_SSD1306_FRAMEBUFFER
/**
 * \brief Put framebuffer to LCD controller
 *
 * This function will output the complete framebuffer from RAM to the
 * LCD controller.
 *
 * \note This is done automatically if using the graphic primitives. Only
 * needed if you are manipulating the framebuffer directly in your code.
 */
void gfx_mono_ssd1306_put_framebuffer(void)
{
	uint8_t page;

	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		ssd1306_set_page_address(page);
		ssd1306_set_column_address(0);
		gfx_mono_ssd1306_put_page(framebuffer
				+ (page * GFX_MONO_LCD_WIDTH), page, 0,
				GFX_MONO_LCD_WIDTH);
	}
}
#endif

/**
 * \brief Draw pixel to screen
 *
 * \param[in] x         X coordinate of the pixel
 * \param[in] y         Y coordinate of the pixel
 * \param[in] color     Pixel operation
 *
 * The following will set the pixel at x=10,y=10:
 * \code
	gfx_mono_ssd1306_draw_pixel(10, 10, GFX_PIXEL_SET);
\endcode
 * The following example will clear the pixel at x=10,y=10:
 * \code
	gfx_mono_ssd1306_draw_pixel(10, 10, GFX_PIXEL_CLR);
\endcode
 * And the following will toggle the pixel at x=10,y=10:
 * \code
	gfx_mono_ssd1306_draw_pixel(10, 10, GFX_PIXEL_XOR);
\endcode
 */
void gfx_mono_ssd1306_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t color)
{
	uint8_t page;
	uint8_t pixel_mask;
	uint8_t pixel_value;

	/* Discard pixels drawn outside the screen */
	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	/*
	 * Read the page containing the pixel in interest, then perform the
	 * requested action on this pixel before writing the page back to the
	 * display.
	 */
	pixel_value = gfx_mono_get_byte(page, x);

	switch (color) {
	case GFX_PIXEL_SET:
		pixel_value |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		pixel_value &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		pixel_value ^= pixel_mask;
		break;

	default:
		break;
	}

	gfx_mono_put_byte(page, x, pixel_value);
}

/**
 * \brief Get the pixel value at x,y
 *
 * \param[in] x      X coordinate of pixel
 * \param[in] y      Y coordinate of pixel
 * \return Non zero value if pixel is set.
 *
 * The following example will read the pixel value from x=10,y=10:
 * \code
	pixelval = gfx_mono_ssd1306_get_pixel(10,10);
\endcode
 */
uint8_t gfx_mono_ssd1306_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
	uint8_t page;
	uint8_t pixel_mask;

	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return 0;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	return gfx_mono_get_byte(page, x) & pixel_mask;
}

/**
 * \brief Put a page from RAM to display controller.
 *
 * If the controller is accessed by the SPI interface, we can not read
 * back data from the LCD controller RAM. Because of this all data that is
 * written to the LCD controller in this mode is also written to a framebuffer
 * in MCU RAM.
 *
 * \param[in] data Pointer to data to be written
 * \param[in] page Page address
 * \param[in] column Offset into page (x coordinate)
 * \param[in] width Number of bytes to be written.
 *
 * The following example will write 32 bytes from data_buf to the page 0,
 * column 10. This will place data_buf in the rectangle x1=10,y1=0,x2=42,y2=8
 * (10 pixels from the upper left corner of the screen):
 * \code
	gfx_mono_ssd1306_put_page(data_buf, 0, 10, 32);
\endcode
 */
void gfx_mono_ssd1306_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t column, gfx_coord_t width)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	gfx_mono_framebuffer_put_page(data, page, column, width);
#endif
	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	do {
		ssd1306_write_data(*data++);
	} while (--width);
}

/**
 * \brief Read a page from the LCD controller
 *
 * If the LCD controller is accessed by the SPI interface we cannot read
 * data directly from the controller. In that case we will read the data from
 * the local framebuffer instead.
 *
 * \param[in] data   Pointer where to store the read data
 * \param[in] page   Page address
 * \param[in] column Offset into page (x coordinate)
 * \param[in] width  Number of bytes to be read
 *
 * The following example will read back the first 128 bytes (first page) from
 * the display memory:
 * \code
	gfx_mono_ssd1306_get_page(read_buffer, 0, 0, 128);
\endcode
 */
void gfx_mono_ssd1306_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t column, gfx_coord_t width)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	gfx_mono_framebuffer_get_page(data, page, column, width);
#else
	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	do {
		*data++ = ssd1306_read_data();
	} while (--width);
#endif
}

/**
 * \brief Put a byte to the display controller RAM
 *
 * If the LCD controller is accessed by the SPI interface we will also put the
 * data to the local framebuffer.
 *
 * \param[in] page Page address
 * \param[in] column Page offset (x coordinate)
 * \param[in] data Data to be written
 * \param[in] force Forces the write
 *
 * This example will put the value 0xFF to the first byte in the display memory
 * setting a 8 pixel high column of pixels in the upper left corner of the
 * display.
 * \code
	gfx_mono_ssd1306_put_byte(0, 0, 0xFF, false);
\endcode
  */
 void gfx_mono_ssd1306_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data, bool force)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	if (!force && data == gfx_mono_framebuffer_get_byte(page, column)) {
		return;
	}
	gfx_mono_framebuffer_put_byte(page, column, data);
#endif

	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	ssd1306_write_data(data);
}

/**
 * \brief Get a byte from the display controller RAM
 *
 * If the LCD controller is accessed by the SPI interface we cannot read the
 * data. In this case return the data from the local framebuffer instead.
 *
 * \param[in] page Page address
 * \param[in] column Page offset (x coordinate)
 * \return data from LCD controller or framebuffer.
 *
 * The following code will read the first byte from the display memory or the
 * local framebuffer if direct read is not possible. The data represents the
 * pixels from x = 0 and y = 0 to y = 7.
 * \code
	data = gfx_mono_ssd1306_get_byte(0, 0);
\endcode
 */
uint8_t gfx_mono_ssd1306_get_byte(gfx_coord_t page, gfx_coord_t column)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	return gfx_mono_framebuffer_get_byte(page, column);

#else
	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	return ssd1306_read_data();

#endif
}

/**
 * \brief Read/Modify/Write a byte on the display controller
 *
 * This function will read the byte from the display controller (or the
 * framebuffer if we cannot read directly from the controller) and
 * do a mask operation on the byte according to the pixel operation selected
 * by the color argument and the pixel mask provided.
 *
 * \param[in] page Page address
 * \param[in] column Page offset (x coordinate)
 * \param[in] pixel_mask Mask for pixel operation
 * \param[in] color Pixel operation
 *
 * A small example that will XOR the first byte of display memory with 0xAA
 * \code
	gfx_mono_ssd1306_mask_byte(0,0,0xAA,GFX_PIXEL_XOR);
\endcode
 */
void gfx_mono_ssd1306_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color)
{
	gfx_mono_color_t temp = gfx_mono_get_byte(page, column);

	switch (color) {
	case GFX_PIXEL_SET:
		temp |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		temp &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		temp ^= pixel_mask;
		break;

	default:
		break;
	}

	gfx_mono_put_byte(page, column, temp);
}
