/**
 * \file
 *
 * \brief Generic monochrome LCD graphic primitives
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
#ifndef GFX_MONO_GENERIC
#define GFX_MONO_GENERIC
#include "gfx_mono.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_generic_group Generic monochrome graphic primitives
 *
 * This is a service providing generic implementations of graphic primitives
 * - Horizontal line
 * - Vertical line
 * - Line
 * - Circle (filled/not filled)
 * - Rectangle (filled/not filled)
 *
 * it also provides functionality to draw a bitmap to the graphic memory.
 *
 * These functions are made available if the graphic hardware being used do
 * not implement the functionality in hardware. This is true in most cases.
 *
 * This service is included as a requirement for a
 * hardware specific component that uses these functions, and provides a
 * asfdoc_common2_draw_pixel function.
 *
 * @{
 */

/**
 * \brief Storage structure for bitmap pixel data and metadata
 */
struct gfx_mono_bitmap {
	/** Width of bitmap */
	gfx_coord_t width;
	/** Height of bitmap */
	gfx_coord_t height;
	/** Bitmap type */
	enum gfx_mono_bitmap_type type;
	union {
		/** Pointer to pixels for bitmap stored in RAM */
		gfx_mono_color_t *pixmap;
		/** Pointer to pixels for bitmap stored in progmem */
		gfx_mono_color_t PROGMEM_T *progmem;
	}
	data;
};

void gfx_mono_generic_draw_horizontal_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color);

void gfx_mono_generic_draw_vertical_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color);

void gfx_mono_generic_draw_line(gfx_coord_t x1, gfx_coord_t y1,
		gfx_coord_t x2, gfx_coord_t y2,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_filled_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t octant_mask);

void gfx_mono_generic_draw_filled_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t quadrant_mask);

void gfx_mono_generic_put_bitmap(struct gfx_mono_bitmap *bitmap, gfx_coord_t x,
		gfx_coord_t y);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_GENERIC */
