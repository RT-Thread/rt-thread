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
#ifndef GFX_MONO_H
#define GFX_MONO_H

#include <stdint.h>

#include "compiler.h"

#ifndef PROGMEM_DECLARE
#  define PROGMEM_DECLARE(type, name) const type name
#  define PROGMEM_T const
#  define PROGMEM_PTR_T const *
#  define PROGMEM_READ_BYTE(x) *(x)
#  define PROGMEM_STRING_T const char*
#endif

/**
 * \defgroup asfdoc_common2_gfx_mono Monochrome graphical display system
 *
 * See \ref asfdoc_common2_gfx_mono_quickstart.
 *
 * This library provides an interface to drawing graphics on monochrome
 * graphical displays
 *
 * The graphics drivers consists of the following:
 * - Display driver interface (gfx_mono.h)
 * - General graphics drawing primitives (gfx_mono_generic.h)
 * - Display specific implementation (ex. gfx_mono_ug_2832hsweg04.h)
 *
 * The generic drawing primitives is a library of functions for drawing
 * graphics primitives such as lines, rectangles and circles. It uses other
 * functions implemented by the display driver for drawing the primitives. The
 * implementation of these functions can optionally be used by a display
 * driver, but if the hardware of the display allows faster handling of any of
 * the primitives, the display driver can implement it directly.
 *
 * The display specific drivers provides an interface to the graphical display.
 * It implements the low level communication with the display hardware, putting
 * pixels on the display and drawing primitives such as lines, circles and
 * rectangles. Depending on the display driver implementation, drawing the
 * graphics primitives might be handled by the generic graphics drawing
 * primitives rather than the display driver itself.
 *
 * \section asfdoc_common2_gfx_mono_examples Examples
 * The following examples are available for the driver:
 * - \ref asfdoc_common2_gfx_mono_quickstart
 * - \ref asfdoc_common2_gfx_mono_sysfont_example
 * - \ref asfdoc_common2_gfx_mono_spinner_example
 *
 * \section asfdoc_common2_gfx_mono_api_overview API Overview
 *
 * \note The functions in the library are not interrupt safe.
 * @{
 */

typedef uint8_t gfx_mono_color_t;
typedef uint8_t gfx_coord_t;

/** Pixel operations */
enum gfx_mono_color {
	/** Pixel is cleared */
	GFX_PIXEL_CLR = 0,
	/** Pixel is set on screen (OR) */
	GFX_PIXEL_SET = 1,
	/** Pixel is XORed */
	GFX_PIXEL_XOR = 2,
};

/** Bitmap types */
enum gfx_mono_bitmap_type {
	/** Bitmap stored in SRAM */
	GFX_MONO_BITMAP_RAM,
	/** Bitmap stored in progmem */
	GFX_MONO_BITMAP_PROGMEM
};

/* Cannot be moved to top, as they use the bitmap and color enums. */
#ifdef USE_SDL
# include "gfx_mono_sdl.h"
#elif defined(GFX_MONO_C12832_A1Z)
# include "gfx_mono_c12832_a1z.h"
#elif defined(GFX_MONO_UG_2832HSWEG04)
# include "gfx_mono_ug_2832hsweg04.h"
#else
/* NULL driver by default */
# include "gfx_mono_null.h"
#endif
#include "gfx_mono_generic.h"

/** \name Circle Sector Definitions */
/** @{ */

/** Bitmask for drawing circle octant 0. */
#define GFX_OCTANT0     (1 << 0)
/** Bitmask for drawing circle octant 1. */
#define GFX_OCTANT1     (1 << 1)
/** Bitmask for drawing circle octant 2. */
#define GFX_OCTANT2     (1 << 2)
/** Bitmask for drawing circle octant 3. */
#define GFX_OCTANT3     (1 << 3)
/** Bitmask for drawing circle octant 4. */
#define GFX_OCTANT4     (1 << 4)
/** Bitmask for drawing circle octant 5. */
#define GFX_OCTANT5     (1 << 5)
/** Bitmask for drawing circle octant 6. */
#define GFX_OCTANT6     (1 << 6)
/** Bitmask for drawing circle octant 7. */
#define GFX_OCTANT7     (1 << 7)

/** Bitmask for drawing circle quadrant 0. */
#define GFX_QUADRANT0   (GFX_OCTANT0 | GFX_OCTANT1)
/** Bitmask for drawing circle quadrant 1. */
#define GFX_QUADRANT1   (GFX_OCTANT2 | GFX_OCTANT3)
/** Bitmask for drawing circle quadrant 2. */
#define GFX_QUADRANT2   (GFX_OCTANT4 | GFX_OCTANT5)
/** Bitmask for drawing circle quadrant 3. */
#define GFX_QUADRANT3   (GFX_OCTANT6 | GFX_OCTANT7)

/** Bitmask for drawing left half of circle. */
#define GFX_LEFTHALF    (GFX_QUADRANT3 | GFX_QUADRANT0)
/** Bitmask for drawing top half of circle. */
#define GFX_TOPHALF     (GFX_QUADRANT0 | GFX_QUADRANT1)
/** Bitmask for drawing right half of circle. */
#define GFX_RIGHTHALF   (GFX_QUADRANT1 | GFX_QUADRANT2)
/** Bitmask for drawing bottom half of circle. */
#define GFX_BOTTOMHALF  (GFX_QUADRANT2 | GFX_QUADRANT3)

/** Bitmask for drawing whole circle. */
#define GFX_WHOLE       0xFF

/** @} */

/** \name Graphic Drawing Primitives */
/** @{ */

/**
 * \def gfx_mono_draw_horizontal_line(x, y, length, color)
 * \brief Draw a horizontal line, one pixel wide.
 *
 * \param[in]  x          X coordinate of leftmost pixel.
 * \param[in]  y          Y coordinate of the line.
 * \param[in]  length     Length of the line in pixels.
 * \param[in]  color      Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_vertical_line(x, y, length, color)
 * \brief Draw a vertical line, one pixel wide.
 *
 * \param[in]  x          X coordinate of the line.
 * \param[in]  y          Y coordinate of the topmost pixel.
 * \param[in]  length     Length of the line in pixels.
 * \param[in]  color      Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_line(x1, y1, x2, y2, color)
 * \brief Draw a line between two arbitrary points.
 *
 * \param[in]  x1          Start X coordinate.
 * \param[in]  y1          Start Y coordinate.
 * \param[in]  x2          End X coordinate.
 * \param[in]  y2          End Y coordinate.
 * \param[in]  color       Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_rect(x, y, width, height, color)
 * \brief Draw an outline of a rectangle.
 *
 * \param[in]  x           X coordinate of the left side.
 * \param[in]  y           Y coordinate of the top side.
 * \param[in]  width       Width of the rectangle.
 * \param[in]  height      Height of the rectangle.
 * \param[in]  color       Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_filled_rect(x, y, width, height, color)
 * \brief Draw a filled rectangle.
 *
 * \param[in]  x           X coordinate of the left side.
 * \param[in]  y           Y coordinate of the top side.
 * \param[in]  width       Width of the rectangle.
 * \param[in]  height      Height of the rectangle.
 * \param[in]  color       Pixel operation of the line
 */

/**
 * \def gfx_mono_draw_circle(x, y, radius, color, octant_mask)
 * \brief Draw an outline of a circle or arc.
 *
 * The radius is the distance from the center to the circumference,
 * which means that the total width or height of a circle will be
 * (radius*2+1).
 *
 * The octant_mask parameter is a bitmask that decides which octants of
 * the circle to draw. Use the GFX_OCTANTn, GFX_QUADRANTn, GFX_xHALF and
 * GFX_WHOLE constants and OR them together if required. Radius equal to
 * zero gives a single pixel.
 *
 * \param[in]  x           X coordinate of center.
 * \param[in]  y           Y coordinate of center.
 * \param[in]  radius      Circle radius in pixels.
 * \param[in]  color       Pixel operation.
 * \param[in]  octant_mask Bitmask indicating which octants to draw.
 */

/**
 * \def gfx_mono_draw_filled_circle(x, y, radius, color, quadrant_mask)
 * \brief Draw a filled circle or sector.
 *
 * The radius is the distance from the center to the circumference,
 * which means that the total width or height of a circle will be
 * (radius*2+1).
 *
 * The quadrant_mask parameter is a bitmask that decides which quadrants
 * of the circle to draw. Use the GFX_QUADRANTn, GFX_xHALF and
 * GFX_WHOLE constants and OR them together if required. Radius equal to
 * zero gives a single pixel.
 *
 * \note This function only supports quadrants while gfx_draw_circle()
 *       supports octants. This is to improve performance on drawing
 *       filled circles.
 *
 * \param[in]  x           X coordinate of center.
 * \param[in]  y           Y coordinate of center.
 * \param[in]  radius      Circle radius in pixels.
 * \param[in]  color       Pixel operation.
 * \param[in]  quadrant_mask Bitmask indicating which quadrants to draw.
 */

/** @} */

/** @} */

/**
 * \page asfdoc_common2_gfx_mono_quickstart Quick Start Guide for the mono graphics service
 *
 * This is the quick start guide for the \ref asfdoc_common2_gfx_mono "Monochrome Graphics service",
 * with step-by-step instructions on how to configure and use it for a specific
 * use case.
 *
 * \section asfdoc_common2_gfx_mono_quickstart_basic Basic usage of the graphics service
 * This use case will demonstrate initializing the mono graphics service and
 * then draw a black line on the screen from coordinates X=10, Y=10 to X=20,
 * Y=20.
 *
 * \section asfdoc_common2_gfx_mono_basic_usage Usage steps
 * \subsection asfdoc_common2_gfx_mono_basic_usage_code Example code
 * Add to, e.g., the main function in the application C-file:
 * \code
	system_init();
	gfx_mono_init();
	gfx_mono_draw_line(10, 10, 20, 20, GFX_PIXEL_SET);
\endcode
 *
 * \subsection gfx_mono_basic_usage_workflow Workflow
 * -# Initialize system:
 *  - \code system_init(); \endcode
 * -# Initialize monochrome graphics service
 *  - \code gfx_mono_init(); \endcode
 *  - \note This will call the init function for the low level display
 *          controller driver and intialize the screen to a cleared background.
 * -# Draw a line from 10,10 to 20,20:
 * -  \code gfx_mono_draw_line(10, 10, 20, 20, GFX_PIXEL_SET); \endcode
 * -  \note This uses GFX_PIXEL_SET to set the display pixels on the line;
 *          other options can be found in \ref gfx_mono_color.
 */

/**
 * \page asfdoc_common2_gfx_mono_exqsg Examples for GFX Mono Library
 *
 * This is a list of the available Quick Start guides (QSGs) and example applications
 * for \ref asfdoc_common2_gfx_mono. QSGs are simple examples with step-by-step instructions
 * to configure and use this driver in a selection of use cases. Note that QSGs can be compiled as
 * a standalone application or be added to the user application.
 *  - \subpage asfdoc_common2_gfx_mono_quickstart
 *  - \subpage asfdoc_common2_gfx_mono_font_quickstart
 *  - \subpage asfdoc_common2_gfx_mono_sysfont_example
 *  - \subpage asfdoc_common2_gfx_mono_spinner_example
 *
 */


#endif /* GFX_MONO_H */
