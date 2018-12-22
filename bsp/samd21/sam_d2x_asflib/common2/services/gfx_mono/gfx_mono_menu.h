/**
 * \file
 *
 * \brief Simple menu system
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
#ifndef GFX_MONO_MENU_H
#define GFX_MONO_MENU_H

#include "compiler.h"
#include "conf_menu.h"
#include "gfx_mono.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_menu Menu system for monochrome graphical displays
 *
 * This module provides a simple menu system for monochrome graphical
 * displays.
 *
 * Typical flow of an application using the menu system:
 *
 * 1) Define menu structure.\n
 * 2) Call asfdoc_common2_gfx_mono_menu_init.\n
 * 3) Get user input.\n
 * 4) Update menu with user input using function \ref
 *    gfx_mono_menu_process_key.\n
 * 5) Interpret \ref gfx_mono_menu_process_key return value.\n
 * 6) Go to 3.\n
 *
 * The menu is declared using the \ref gfx_mono_menu struct.
 *
 * To start the menu system, call the \ref gfx_mono_menu_init function.
 * This function will clear the display and draw the menu.
 *
 * Before the menu can be updated, you need input from the user. Methods for
 * getting input is not part of the menu module.
 *
 * As soon as input is received, inform the menu system using the
 * \ref gfx_mono_menu_process_key function.
 * This function will then return a status code and act depending on the given
 * keycode:
 *
 * MENU_KEYCODE_DOWN : Change selection to next menu item (or first if at
 * bottom).
 * Returns MENU_EVENT_IDLE.
 *
 * MENU_KEYCODE_UP : Change selection to previous menu item (or last if at top).
 * Returns MENU_EVENT_IDLE.
 *
 * MENU_KEYCODE_ENTER : Nothing changes in menu. Returns the line selected.
 *
 * MENU_KEYCODE_BACK : Nothing changes in menu. Returns MENU_EVENT_EXIT.
 *
 * The value of the keycodes used are defined in conf_menu.h. These value can
 * be changed if needed.
 *
 * The graphical indicator used to indicate menu selection is defined in
 * conf_menu.h. This indicator can be changed if needed.
 * @{
 */

/** \name Menu events definitions */
/** @{ */
/** Idle. Nothing to report. */
#define GFX_MONO_MENU_EVENT_IDLE    0xFF
/** Exit. User has pressed the back button. */
#define GFX_MONO_MENU_EVENT_EXIT    0xFE
/** @} */

/** Maximum number of menu elements on display */
#define GFX_MONO_MENU_ELEMENTS_PER_SCREEN ((GFX_MONO_LCD_HEIGHT / \
	SYSFONT_LINESPACING) - 1)

/** Menu struct */
struct gfx_mono_menu {
	PROGMEM_STRING_T title;
	PROGMEM_STRING_T *strings;
	uint8_t num_elements;
	uint8_t current_selection;
	uint8_t current_page;
};

void gfx_mono_menu_init(struct gfx_mono_menu *menu);
uint8_t gfx_mono_menu_process_key(struct gfx_mono_menu *menu, uint8_t keycode);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_MENU_H */
