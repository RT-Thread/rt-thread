/**
 * \file
 *
 * \brief Monochrome graphic library API header file
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
#ifndef GFX_MONO_TEXT_H_INCLUDED
#define GFX_MONO_TEXT_H_INCLUDED

#include <stdint.h>

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_font GFX Mono Font Library
 * This modules provides functionality for outputting a monochrome font
 * to a display.
 *
 * \section asfdoc_common2_gfx_mono_font_api_overview API Overview
 * @{
 */

/**
 * \brief Valid storage locations for font data
 *
 * Add support for fonts in regular ram
 */
enum font_data_type {
	/** Font data stored in program/flash memory. */
	FONT_LOC_PROGMEM,
};

/** Storage structure for font meta data. */
struct font {
	/** Type of storage used for binary font data. See \ref font_data_type. */
	enum font_data_type type;
	union {
		/**
		 * Pointer to where the binary font data is stored. This
		 * variable is accessed either through hugemem or progmem
		 * depending on the value of \a type.
		 */
#ifdef CONFIG_HAVE_HUGEMEM
		hugemem_ptr_t hugemem;
#endif
		uint8_t PROGMEM_PTR_T progmem;
	} data;
	/** Width of one font character, in pixels. */
	uint8_t width;
	/** Height of one font character, in pixels. */
	uint8_t height;
	/** ASCII value of first character in font set. */
	uint8_t first_char;
	/** ASCII value of last character in the set. */
	uint8_t last_char;
};

/** \name Strings and characters located in RAM */
/** @{ */
void gfx_mono_draw_char(const char c, const gfx_coord_t x, const gfx_coord_t y,
		const struct font *font);

void gfx_mono_draw_string(const char *str, const gfx_coord_t x,
		const gfx_coord_t y, const struct font *font);

void gfx_mono_get_string_bounding_box(char const *str, const struct font *font,
		gfx_coord_t *width, gfx_coord_t *height);

/** @} */

/** \name Strings located in flash */
/** @{ */
void gfx_mono_draw_progmem_string(char PROGMEM_PTR_T str, gfx_coord_t x,
		gfx_coord_t y, const struct font *font);

void gfx_mono_get_progmem_string_bounding_box(char PROGMEM_PTR_T str,
		const struct font *font, gfx_coord_t *width,
		gfx_coord_t *height);

/** @} */

/** @} */

/**
 * \page asfdoc_common2_gfx_mono_font_quickstart Quick Start Guide for the mono font service
 *
 * This is the quick start guide for the \ref asfdoc_common2_gfx_mono_font
 * with step-by-step instructions on how to configure and use it for a specific
 * use case.
 *
 * \section asfdoc_common2_gfx_mono_font_quickstart_basic Basic usage of the graphics service
 * This use case will demonstrate initializing the mono graphics service and
 * then draw a "Hello world!" sting on the display.
 *
 * \section asfdoc_common2_gfx_mono_font_quickstart_depend Dependencies
 * In order to use this quick start, the following dependencies are needed:
 * - \ref asfdoc_samd20_system_group
 * - \ref asfdoc_common2_gfx_mono_font
 * - \ref conf_sysfont.h Containing the actual font.
 *
 * \section asfdoc_common2_gfx_mono_font_basic_usage Usage steps
 * \subsection gfx_mono_font_basic_usage_code Example code
 * Add to, e.g., the main function in the application C-file:
 * \code
	     system_init();

	     gfx_mono_init();

	     gfx_mono_draw_string("Hello world!",0, 0, &sysfont);

	     while (1) {

	     }
\endcode
 *
 * \subsection asfdoc_common2_gfx_mono_font_basic_usage_workflow Workflow
 * -# Initialize system:
 *  - \code system_init(); \endcode
 * -# Initialize monochrome graphics service
 *  - \code gfx_mono_init(); \endcode
 *  - \note This will call the init function for the low level display
 *          controller driver and intialize the screen to a cleared background.
 * -# Draw a string on the screen starting at pixel (0,0)
 * -  \code gfx_mono_draw_string("Hello world!",0, 0, &sysfont); \endcode
 * -  \note This uses \ref conf_sysfont.h where sysfont is defines to give the font
 * to be used on the screen.
 */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_TEXT_H_INCLUDED */
