/**
 * \file
 *
 * \brief Simple menu system
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

#include "sysfont.h"
#include <conf_menu.h>

#include "gfx_mono_menu.h"

/**
 * \ingroup asfdoc_common2_gfx_mono_menu
 * @{
 */

PROGMEM_DECLARE(gfx_mono_color_t, arrow_right_data[]) = {
	GFX_MONO_MENU_INDICATOR_BITMAP
};

struct gfx_mono_bitmap menu_bitmap_indicator = {
	.height = GFX_MONO_MENU_INDICATOR_HEIGHT,
	.width = GFX_MONO_MENU_INDICATOR_WIDTH,
	.type = GFX_MONO_BITMAP_PROGMEM,
	.data.progmem = arrow_right_data
};

/**
 * \brief Draw menu strings and an icon by the current selection.
 *
 * \param[in] menu     a menu struct with menu settings
 * \param[in] redraw   clear screen before drawing menu
 */
static void menu_draw(struct gfx_mono_menu *menu, bool redraw)
{
	static bool redraw_state;
	uint8_t i;
	uint8_t line = 1;
	uint8_t menu_page = menu->current_selection /
			GFX_MONO_MENU_ELEMENTS_PER_SCREEN;

	if (menu->current_page != menu_page || redraw == true) {
		/* clear screen if we have changed the page or menu and prepare
		 * redraw */
		gfx_mono_draw_filled_rect(0, SYSFONT_LINESPACING,
				GFX_MONO_LCD_WIDTH,
				GFX_MONO_LCD_HEIGHT - SYSFONT_LINESPACING,
				GFX_PIXEL_CLR);
		redraw_state = true;
	}

	menu->current_page = menu_page;

	/* Clear old indicator icon */
	gfx_mono_draw_filled_rect(0, SYSFONT_LINESPACING,
			GFX_MONO_MENU_INDICATOR_WIDTH, GFX_MONO_LCD_HEIGHT -
			SYSFONT_LINESPACING, GFX_PIXEL_CLR);

	/* Put indicator icon on current selection */
	gfx_mono_put_bitmap(&menu_bitmap_indicator, 0,
			SYSFONT_LINESPACING * ((menu->current_selection %
			GFX_MONO_MENU_ELEMENTS_PER_SCREEN) + 1));

	/* Print visible options if page or menu has changed */
	if (redraw_state == true) {
		for (i = menu_page * GFX_MONO_MENU_ELEMENTS_PER_SCREEN;
				i < menu_page *
				GFX_MONO_MENU_ELEMENTS_PER_SCREEN +
				GFX_MONO_MENU_ELEMENTS_PER_SCREEN &&
				i < menu->num_elements; i++) {
			gfx_mono_draw_progmem_string(
					(char PROGMEM_PTR_T)menu->strings[i],
					GFX_MONO_MENU_INDICATOR_WIDTH + 1,
					line * SYSFONT_LINESPACING, &sysfont);
			line++;
		}
		redraw_state = false;
	}
}

/**
 * *\brief Initialize the menu handling. Clear screen and draw menu.
 *
 * \param[in] menu  menu struct with menu options
 *
 */
void gfx_mono_menu_init(struct gfx_mono_menu *menu)
{
	/* Clear screen */
	gfx_mono_draw_filled_rect(0, 0,
			GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT, GFX_PIXEL_CLR);

	/* Draw the menu title on the top of the screen */
	gfx_mono_draw_progmem_string((char PROGMEM_PTR_T)menu->title,
			0, 0, &sysfont);

	/* Draw menu options below */
	menu_draw(menu, true);
}

/**
 * \brief Update menu depending on input.
 *
 * \param[in] menu  menu struct with menu options
 * \param[in] keycode  keycode to process
 *
 * \retval selected menu option or status code
 */
uint8_t gfx_mono_menu_process_key(struct gfx_mono_menu *menu, uint8_t keycode)
{
	switch (keycode) {
	case GFX_MONO_MENU_KEYCODE_DOWN:
		if (menu->current_selection == menu->num_elements - 1) {
			menu->current_selection = 0;
		} else {
			menu->current_selection++;
		}

		/* Update menu on display */
		menu_draw(menu, false);
		/* Nothing selected yet */
		return GFX_MONO_MENU_EVENT_IDLE;

	case GFX_MONO_MENU_KEYCODE_UP:
		if (menu->current_selection) {
			menu->current_selection--;
		} else {
			menu->current_selection = menu->num_elements - 1;
		}

		/* Update menu on display */
		menu_draw(menu, false);
		/* Nothing selected yet */
		return GFX_MONO_MENU_EVENT_IDLE;

	case GFX_MONO_MENU_KEYCODE_ENTER:
		/* Got what we want. Return selection. */
		return menu->current_selection;

	case GFX_MONO_MENU_KEYCODE_BACK:
		/* User pressed "back" key, inform user */
		return GFX_MONO_MENU_EVENT_EXIT;

	default:
		/* Unknown key event */
		return GFX_MONO_MENU_EVENT_IDLE;
	}
}
