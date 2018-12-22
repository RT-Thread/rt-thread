/**
 * \file
 *
 * \brief Monochrome graphic library framebuffer device
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
#ifndef GFX_MONO_FRAMEBUFFER
#define GFX_MONO_FRAMEBUFFER

#include "gfx_mono.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_framebuffer_group Framebuffer
 *
 * This module provides read/write from and to a framebuffer in RAM. This is
 * needed when using a controller that does not provide a way to read back data
 * from the LCD controller memory. In this case we need to buffer the data in
 * a local framebuffer to allow manipulation on pixel level. It is generally
 * not recommended to access the framebuffer directly; this is handled by the
 * graphic driver when needed.
 *
 * @{
 */

void gfx_mono_set_framebuffer(uint8_t *framebuffer);

void gfx_mono_framebuffer_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_framebuffer_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_framebuffer_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color);

uint8_t gfx_mono_framebuffer_get_pixel(gfx_coord_t x, gfx_coord_t y);

void gfx_mono_framebuffer_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data);

uint8_t gfx_mono_framebuffer_get_byte(gfx_coord_t page, gfx_coord_t column);

void gfx_mono_framebuffer_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_FRAMEBUFFER */
