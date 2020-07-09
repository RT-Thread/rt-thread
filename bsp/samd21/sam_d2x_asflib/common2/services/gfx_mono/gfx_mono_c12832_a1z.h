/**
 * \file
 *
 * \brief Haven Display C12832 A1Z display glue code for display controller
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

#ifndef GFX_MONO_C12832_A1Z_H
#define GFX_MONO_C12832_A1Z_H
#include "compiler.h"
#include "st7565r.h"

#include "gfx_mono.h"
#include "gfx_mono_framebuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_C12832_A1Z_group C12832_A1Z graphic library abstraction
 *
 * This module is an abstraction layer between the graphic library and the
 * C12832_A1Z monochrome LCD display connected to a ST7565R LCD controller.
 *
 * As the controller does not provide any hardware accelerated graphic, all the
 * graphic primitives are provided by the \ref asfdoc_common2_gfx_mono_generic_group service.
 *
 * \note Do not call the gfx_mono_st7565r_ functions directly. use the gfx_mono
 * names that are defined in this header and documented in \ref asfdoc_common2_gfx_mono .
 * Ie. gfx_mono_draw_pixel() should be used, not gfx_mono_st7565r_draw_pixel()
 * @{
 */

#define GFX_MONO_LCD_WIDTH              128
#ifndef GFX_MONO_LCD_HEIGHT
#	define GFX_MONO_LCD_HEIGHT             32
#endif
#define GFX_MONO_LCD_PIXELS_PER_BYTE    8
#define GFX_MONO_LCD_PAGES              (GFX_MONO_LCD_HEIGHT / \
	GFX_MONO_LCD_PIXELS_PER_BYTE)
#define GFX_MONO_LCD_FRAMEBUFFER_SIZE   ((GFX_MONO_LCD_WIDTH * \
	GFX_MONO_LCD_HEIGHT) / GFX_MONO_LCD_PIXELS_PER_BYTE)

#define gfx_mono_draw_horizontal_line(x, y, length, color) \
	gfx_mono_generic_draw_horizontal_line(x, y, length, color)

#define gfx_mono_draw_vertical_line(x, y, length, color) \
	gfx_mono_generic_draw_vertical_line(x, y, length, color)

#define gfx_mono_draw_line(x1, y1, x2, y2, color) \
	gfx_mono_generic_draw_line(x1, y1, x2, y2, color)

#define gfx_mono_draw_rect(x, y, width, height, color) \
	gfx_mono_generic_draw_rect(x, y, width, height, color)

#define gfx_mono_draw_filled_rect(x, y, width, height, color) \
	gfx_mono_generic_draw_filled_rect(x, y, width, height, \
		color)

#define gfx_mono_draw_circle(x, y, radius, color, octant_mask) \
	gfx_mono_generic_draw_circle(x, y, radius, color, \
		octant_mask)

#define gfx_mono_draw_filled_circle(x, y, radius, color, quadrant_mask)	\
	gfx_mono_generic_draw_filled_circle(x, y, radius, \
		color, quadrant_mask)

#define gfx_mono_put_bitmap(bitmap, x, y) \
	gfx_mono_generic_put_bitmap(bitmap, x, y)

#define gfx_mono_draw_pixel(x, y, color) \
	gfx_mono_st7565r_draw_pixel(x, y, color)

#define gfx_mono_get_pixel(x, y) \
	gfx_mono_st7565r_get_pixel(x, y)

#define gfx_mono_init()	\
	gfx_mono_st7565r_init()

#define gfx_mono_put_page(data, page, column, width) \
	gfx_mono_st7565r_put_page(data, page, column, width)

#define gfx_mono_get_page(data, page, column, width) \
	gfx_mono_st7565r_get_page(data, page, column, width)

#define gfx_mono_put_byte(page, column, data) \
	gfx_mono_st7565r_put_byte(page, column, data)

#define gfx_mono_get_byte(page, column)	\
	gfx_mono_st7565r_get_byte(page, column)

#define gfx_mono_mask_byte(page, column, pixel_mask, color) \
	gfx_mono_st7565r_mask_byte(page, column, pixel_mask, color)

#define gfx_mono_put_framebuffer() \
	gfx_mono_st7565r_put_framebuffer()

void gfx_mono_st7565r_put_framebuffer(void);

void gfx_mono_st7565r_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_st7565r_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_st7565r_init(void);

void gfx_mono_st7565r_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color);

uint8_t gfx_mono_st7565r_get_pixel(gfx_coord_t x, gfx_coord_t y);

void gfx_mono_st7565r_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data);

uint8_t gfx_mono_st7565r_get_byte(gfx_coord_t page, gfx_coord_t column);

void gfx_mono_st7565r_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_C12832_A1Z_H */
