/*
 * File      : rtgui_theme.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */

#include <rtgui/rtgui.h>
#include <rtgui/dc.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/iconbox.h>
#include <rtgui/widgets/title.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

#define SELECTED_HEIGHT			25

const rtgui_color_t default_foreground = RTGUI_RGB(0x00, 0x00, 0x00);
const rtgui_color_t default_background = RTGUI_RGB(212, 208, 200);
const rtgui_color_t selected_color = RTGUI_RGB(0xc0, 0xc0, 0xc0);
const rtgui_color_t disable_foreground = RTGUI_RGB(0x80, 0x80, 0x80);

extern struct rtgui_font rtgui_font_asc16;
extern struct rtgui_font rtgui_font_arial16;
extern struct rtgui_font rtgui_font_asc12;
extern struct rtgui_font rtgui_font_arial12;

/* init theme */
void rtgui_system_theme_init()
{
#if RTGUI_DEFAULT_FONT_SIZE == 16
	rtgui_font_set_defaut(&rtgui_font_asc16);
#elif RTGUI_DEFAULT_FONT_SIZE == 12
	rtgui_font_set_defaut(&rtgui_font_asc12);
#else
	rtgui_font_set_defaut(&rtgui_font_asc12);
#endif
}

static const rt_uint8_t close_byte[14] = {0x06, 0x18, 0x03, 0x30, 0x01, 0xE0, 0x00,
	0xC0, 0x01, 0xE0, 0x03, 0x30, 0x06, 0x18
};

/* window drawing */
void rtgui_theme_draw_win(struct rtgui_topwin* win)
{
	struct rtgui_dc* dc;
	rtgui_rect_t rect;

	if (win->title == RT_NULL) return; /* no title and no board */

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(win->title));
	if (dc == RT_NULL) return;

	/* get rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(win->title), &rect);

	/* draw border */
	if (win->flag & WINTITLE_BORDER)
	{
		rect.x2 -= 1; rect.y2 -= 1;
		RTGUI_WIDGET_FOREGROUND(win->title) = RTGUI_RGB(212, 208, 200);
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y1);
		rtgui_dc_draw_vline(dc, rect.x1, rect.y1, rect.y2);

		RTGUI_WIDGET_FOREGROUND(win->title) = white;
		rtgui_dc_draw_hline(dc, rect.x1 + 1, rect.x2 - 1, rect.y1 + 1);
		rtgui_dc_draw_vline(dc, rect.x1 + 1, rect.y1 + 1, rect.y2 - 1);

		RTGUI_WIDGET_FOREGROUND(win->title) = RTGUI_RGB(128, 128, 128);
		rtgui_dc_draw_hline(dc, rect.x1 + 1, rect.x2 - 1, rect.y2 - 1);
		rtgui_dc_draw_vline(dc, rect.x2 - 1, rect.y1 + 1, rect.y2);

		RTGUI_WIDGET_FOREGROUND(win->title) = RTGUI_RGB(64, 64, 64);
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y2);
		rtgui_dc_draw_vline(dc, rect.x2, rect.y1, rect.y2 + 1);

		/* shrink border */
		rtgui_rect_inflate(&rect, -WINTITLE_BORDER_SIZE);
	}

	/* draw title */
	if (!(win->flag & WINTITLE_NO))
	{
		rt_uint32_t index;
		float r, g, b, delta;

		if (win->flag & WINTITLE_ACTIVATE)
		{
			r = 10; g = 36; b = 106;
			delta = 150 / (float)(rect.x2 - rect.x1);
		}
		else
		{
			r = 128; g = 128; b = 128;
			delta = 64 / (float)(rect.x2 - rect.x1);
		}

		RTGUI_WIDGET_FOREGROUND(win->title) = RTGUI_RGB(r, g, b);
		for (index = rect.x1; index < rect.x2 + 1; index ++)
		{
			rtgui_dc_draw_vline(dc, index, rect.y1, rect.y2);
			r += delta; g += delta; b += delta;
		}

		if (win->flag & WINTITLE_ACTIVATE)
		{
			RTGUI_WIDGET_FOREGROUND(win->title) = white;
		}
		else
		{
			RTGUI_WIDGET_FOREGROUND(win->title) = RTGUI_RGB(212, 208, 200);
		}

		rect.x1 += 4;
		rect.y1 += 2; rect.y2 = rect.y1 + WINTITLE_CB_HEIGHT;
		rtgui_dc_draw_text(dc, rtgui_wintitle_get_title(win->title), &rect);

		if (win->flag & WINTITLE_CLOSEBOX)
		{
			/* get close button rect */
			rtgui_rect_t box_rect = {0, 0, WINTITLE_CB_WIDTH, WINTITLE_CB_HEIGHT};
			rtgui_rect_moveto_align(&rect, &box_rect, RTGUI_ALIGN_CENTER_VERTICAL | RTGUI_ALIGN_RIGHT);
			box_rect.x1 -= 3; box_rect.x2 -= 3;
			rtgui_dc_fill_rect(dc, &box_rect);

			/* draw close box */
			if (win->flag & WINTITLE_CB_PRESSED)
			{
				rtgui_dc_draw_border(dc, &box_rect, RTGUI_BORDER_SUNKEN);
				RTGUI_WIDGET_FOREGROUND(win->title) = red;
				rtgui_dc_draw_word(dc, box_rect.x1, box_rect.y1 + 6, 7, close_byte);
			}
			else
			{
				rtgui_dc_draw_border(dc, &box_rect, RTGUI_BORDER_RAISE);
				RTGUI_WIDGET_FOREGROUND(win->title) = black;
				rtgui_dc_draw_word(dc, box_rect.x1 - 1, box_rect.y1 + 5, 7, close_byte);
			}
		}
	}

	rtgui_dc_end_drawing(dc);
}

/* widget drawing */
void rtgui_theme_draw_button(rtgui_button_t* btn)
{
	/* draw button */
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	rtgui_color_t bc, fc;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(btn));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(btn), &rect);

	/* get foreground color */
	bc = RTGUI_WIDGET_BACKGROUND(btn);
	fc = RTGUI_WIDGET_FOREGROUND(btn);

	if (btn->flag & RTGUI_BUTTON_FLAG_PRESS)
	{
		/* fill button rect with background color */
		rtgui_dc_fill_rect(dc, &rect);

		if (btn->pressed_image != RT_NULL)
		{
			rtgui_rect_t image_rect;
			image_rect.x1 = 0; image_rect.y1 = 0;
			image_rect.x2 = btn->unpressed_image->w;
			image_rect.y2 = btn->unpressed_image->h;
			rtgui_rect_moveto_align(&rect, &image_rect, RTGUI_ALIGN_CENTER);

			rtgui_image_blit(btn->pressed_image, dc, &image_rect);
		}
		else
		{
			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
		}
	}
	else
	{
		/* fill button rect with background color */
		rtgui_dc_fill_rect(dc, &rect);

		if (btn->unpressed_image != RT_NULL)
		{
			rtgui_rect_t image_rect;
			image_rect.x1 = 0; image_rect.y1 = 0;
			image_rect.x2 = btn->unpressed_image->w;
			image_rect.y2 = btn->unpressed_image->h;
			rtgui_rect_moveto_align(&rect, &image_rect, RTGUI_ALIGN_CENTER);

			rtgui_image_blit(btn->unpressed_image, dc, &image_rect);
		}
		else
		{
			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_RAISE);
		}
	}

	if (RTGUI_WIDGET_IS_FOCUSED(btn))
	{
		/* re-set foreground and get default rect */
		rtgui_widget_get_rect(RTGUI_WIDGET(btn), &rect);
		rtgui_rect_inflate(&rect, -2);

		RTGUI_WIDGET_FOREGROUND(btn) = black;
		rtgui_dc_draw_focus_rect(dc, &rect);
	}

	/* set forecolor */
	RTGUI_WIDGET_BACKGROUND(btn) = bc;
	RTGUI_WIDGET_FOREGROUND(btn) = fc;

	if (btn->pressed_image == RT_NULL)
	{
		/* re-set foreground and get default rect */
		rtgui_widget_get_rect(RTGUI_WIDGET(btn), &rect);

		/* remove border */
		rtgui_rect_inflate(&rect, -2);

		/* draw text */
		rtgui_dc_draw_text(dc, rtgui_label_get_text(RTGUI_LABEL(btn)), &rect);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
}

void rtgui_theme_draw_label(rtgui_label_t* label)
{
	/* draw label */
	struct rtgui_dc* dc;
	struct rtgui_rect rect;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(label));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(label), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	/* default left and center draw */
	rtgui_dc_draw_text(dc, rtgui_label_get_text(label), &rect);

	/* end drawing */
	rtgui_dc_end_drawing(dc);
}

#define RTGUI_TEXTBOX_MARGIN	3
void rtgui_theme_draw_textbox(rtgui_textbox_t* box)
{
	/* draw button */
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	rtgui_color_t fc;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(box));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);
	fc = RTGUI_WIDGET_FOREGROUND(box);

	/* fill widget rect with white color */
	RTGUI_WIDGET_BACKGROUND(box) = white;
	rtgui_dc_fill_rect(dc, &rect);

	/* draw border */
	RTGUI_WIDGET_FOREGROUND(box) = RTGUI_RGB(123, 158, 189);
	rtgui_dc_draw_rect(dc, &rect);

	/* draw text */
	RTGUI_WIDGET_FOREGROUND(box) = fc;
	if (box->text != RT_NULL)
	{
		rect.x1 += RTGUI_TEXTBOX_MARGIN;

		if (box->flag & RTGUI_TEXTBOX_MASK)
		{
			/* draw '*' */
			rt_size_t len = rt_strlen(box->text);
			if (len > 0)
			{
				char *text_mask = rtgui_malloc(len + 1);
				rt_memset(text_mask, '*', len + 1);
				text_mask[len] = 0;
				rtgui_dc_draw_text(dc, text_mask, &rect);
				rtgui_free(text_mask);
			}
		}
		else
		{
			rtgui_dc_draw_text(dc, box->text, &rect);
		}

		/* draw caret */
		if (box->flag & RTGUI_TEXTBOX_CARET_SHOW)
		{
			rect.x1 += box->position * box->font_width;
			rect.x2 = rect.x1 + box->font_width;

			rect.y2 -= 2;
			rect.y1 = rect.y2 - 3;

			RTGUI_WIDGET_BACKGROUND(box) = black;
			rtgui_dc_fill_rect(dc, &rect);
		}
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
}

void rtgui_theme_draw_iconbox(rtgui_iconbox_t* iconbox)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	struct rtgui_rect text_rect;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(iconbox));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(iconbox), &rect);

	/* draw icon */
	rtgui_image_blit(iconbox->image, dc, &rect);

	/* draw text */
	if (iconbox->text_position == RTGUI_ICONBOX_TEXT_BELOW && iconbox->text != RT_NULL)
	{
		rect.y1 = iconbox->image->h + RTGUI_WIDGET_DEFAULT_MARGIN;
		rtgui_font_get_metrics(rtgui_dc_get_gc(dc)->font, iconbox->text, &text_rect);
		rtgui_rect_moveto_align(&rect, &text_rect, RTGUI_ALIGN_CENTER);
		rtgui_dc_draw_text(dc, iconbox->text, &text_rect);
	}
	else if (iconbox->text_position == RTGUI_ICONBOX_TEXT_RIGHT && iconbox->text != RT_NULL)
	{
		rect.x1 = iconbox->image->w + RTGUI_WIDGET_DEFAULT_MARGIN;
		rtgui_font_get_metrics(rtgui_dc_get_gc(dc)->font, iconbox->text, &text_rect);
		rtgui_rect_moveto_align(&rect, &text_rect, RTGUI_ALIGN_CENTER);
		rtgui_dc_draw_text(dc, iconbox->text, &text_rect);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
}

static const rt_uint8_t checked_byte[7] = {0x02, 0x06, 0x8E, 0xDC, 0xF8, 0x70, 0x20};
void rtgui_theme_draw_checkbox(struct rtgui_checkbox* checkbox)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect, box_rect;
	rtgui_color_t bc, fc;

	fc = RTGUI_WIDGET_FOREGROUND(checkbox);
	bc = RTGUI_WIDGET_BACKGROUND(checkbox);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(checkbox));
	if (dc == RT_NULL) return;

	/* get rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(checkbox), &rect);

    /* fill rect */
	rtgui_dc_fill_rect(dc, &rect);

	if (RTGUI_WIDGET_IS_FOCUSED(checkbox))
	{
		RTGUI_WIDGET_FOREGROUND(checkbox) = black;

		/* draw focused border */
		rtgui_rect_inflate(&rect, -1);
		rtgui_dc_draw_focus_rect(dc, &rect);

		rtgui_rect_inflate(&rect, 1);
	}

	/* draw check box */
	box_rect.x1 = 0;
	box_rect.y1 = 0;
	box_rect.x2 = CHECK_BOX_W;
	box_rect.y2 = CHECK_BOX_H;
	rtgui_rect_moveto_align(&rect, &box_rect, RTGUI_ALIGN_CENTER_VERTICAL);
	box_rect.x1 += 2; box_rect.x2 += 2;

	rtgui_dc_draw_border(dc, &box_rect, RTGUI_BORDER_BOX);
	rtgui_rect_inflate(&box_rect, -1);
	RTGUI_WIDGET_BACKGROUND(checkbox) = RTGUI_RGB(247, 247, 246);
	rtgui_dc_fill_rect(dc, &box_rect);
	if (checkbox->status_down == RTGUI_CHECKBOX_STATUS_CHECKED)
	{
		RTGUI_WIDGET_FOREGROUND(checkbox) = RTGUI_RGB(33, 161, 33);
		rtgui_dc_draw_byte(dc, box_rect.x1 + 2, box_rect.y1 + 2, 7, checked_byte);
	}

	/* restore saved color */
	RTGUI_WIDGET_BACKGROUND(checkbox) = bc;
	RTGUI_WIDGET_FOREGROUND(checkbox) = fc;

	/* draw text */
	rect.x1 += rtgui_rect_height(rect) - 4 + 5;
	rtgui_dc_draw_text(dc, rtgui_label_get_text(RTGUI_LABEL(checkbox)), &rect);

	/* end drawing */
	rtgui_dc_end_drawing(dc);

	return;
}

static const rt_uint8_t radio_unchecked_byte[] = 
{
	0x0f, 0x00, 0x30, 0xc0, 0x40, 0x20,
	0x40, 0x20,	0x80, 0x10,	0x80, 0x10,
	0x80, 0x10,	0x80, 0x10,	0x40, 0x20,
	0x40, 0x20,	0x30, 0xc0,	0x0f, 0x00,
};
static const rt_uint8_t radio_checked_byte[] = 
{
	0x0f, 0x00, 0x30, 0xc0, 0x40, 0x20, 
	0x40, 0x20, 0x86, 0x10, 0x8f, 0x10, 
	0x8f, 0x10, 0x86, 0x10, 0x40, 0x20, 
	0x40, 0x20, 0x30, 0xc0, 0x0f, 0x00,
};

void rtgui_theme_draw_radiobutton(struct rtgui_radiobox* radiobox, rt_uint16_t item)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect, item_rect;
	int item_size, bord_size;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(radiobox));
	if (dc == RT_NULL) return;
	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(radiobox), &rect);

	item_size = radiobox->item_size;
	/* get board size */
	if (radiobox->orient == RTGUI_VERTICAL)
		bord_size = item_size;
	else
	{
		rtgui_font_get_metrics(RTGUI_DC_FONT(dc), "H", &item_rect);
		bord_size = rtgui_rect_height(item_rect);
	}

	item_rect = rect;
	rtgui_rect_inflate(&item_rect, - bord_size);
	if (radiobox->orient == RTGUI_VERTICAL)
	{
		/* set the first text rect */
		item_rect.y1 += item * item_size;
		item_rect.y2 = item_rect.y1 + item_size;

		/* draw radio */
		if (radiobox->item_selection == item)
		{
			if (RTGUI_WIDGET_IS_FOCUSED(radiobox))
				rtgui_dc_draw_focus_rect(dc, &item_rect);

			rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1 + (item_size - RADIO_BOX_H) / 2, 
				RADIO_BOX_H, radio_checked_byte);
		}
		else
		{
			item_rect.x2 += 1; item_rect.y2 += 1;
			rtgui_dc_fill_rect(dc, &item_rect);
			item_rect.x2 -= 1; item_rect.y2 -= 1;
			rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1 + (item_size - RADIO_BOX_H) / 2, 
				RADIO_BOX_H, radio_unchecked_byte);
		}

		/* draw text */
		item_rect.x1 += item_size + 3;
		rtgui_dc_draw_text(dc, radiobox->items[item], &item_rect);
	}
	else
	{
		item_rect.x1 += item * item_size;

		/* set the first text rect */
		item_rect.x2 = item_rect.x1 + item_size - 1;
		item_rect.y2 = item_rect.y1 + bord_size;

		/* draw radio */
		if (radiobox->item_selection == item)
		{
			if (RTGUI_WIDGET_IS_FOCUSED(radiobox))
				rtgui_dc_draw_focus_rect(dc, &item_rect);
			rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1, RADIO_BOX_H, radio_checked_byte);
		}
		else
		{
			item_rect.x2 += 1; item_rect.y2 += 1;
			rtgui_dc_fill_rect(dc, &item_rect);
			item_rect.x2 -= 1; item_rect.y2 -= 1;
			rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1, RADIO_BOX_H, radio_unchecked_byte);
		}

		/* draw text */
		item_rect.x1 += bord_size + 3;
		rtgui_dc_draw_text(dc, radiobox->items[item], &item_rect);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
}

void rtgui_theme_draw_radiobox(struct rtgui_radiobox* radiobox)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect, item_rect;
	int item_size, bord_size, index;
	rtgui_color_t fc;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(radiobox));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(radiobox), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	item_size = radiobox->item_size;
	/* get board size */
	if (radiobox->orient == RTGUI_VERTICAL)
		bord_size = item_size;
	else
	{
		rtgui_font_get_metrics(RTGUI_DC_FONT(dc), "H", &item_rect);
		bord_size = rtgui_rect_height(item_rect);
	}

	/* draw box */
	rtgui_rect_inflate(&rect, -bord_size/2);
	fc = RTGUI_WIDGET_FOREGROUND(radiobox);

	RTGUI_WIDGET_FOREGROUND(radiobox) = white;
	rect.x1 ++; rect.y1 ++; rect.x2 ++; rect.y2 ++;
	rtgui_dc_draw_rect(dc, &rect);

	RTGUI_WIDGET_FOREGROUND(radiobox) = RTGUI_RGB(128, 128, 128);
	rect.x1 --; rect.y1 --; rect.x2 --; rect.y2 --;
	rtgui_dc_draw_rect(dc, &rect);

	RTGUI_WIDGET_FOREGROUND(radiobox) = fc;

	rtgui_rect_inflate(&rect, bord_size/2);
	if (radiobox->text != RT_NULL)
	{
		struct rtgui_rect text_rect;

		/* draw group text */
		rtgui_font_get_metrics(RTGUI_DC_FONT(dc), radiobox->text, &text_rect);
		rtgui_rect_moveto(&text_rect, rect.x1 + bord_size + 5, rect.y1);
		rect.x1 -= 5; rect.x2 += 5;
		rtgui_dc_fill_rect(dc, &text_rect);
		rect.x1 += 5; rect.x2 -= 5;
		rtgui_dc_draw_text(dc, radiobox->text, &text_rect);
	}

	/* set init item rect */
	item_rect = rect;
	rtgui_rect_inflate(&item_rect, - bord_size);

	if (radiobox->orient == RTGUI_VERTICAL)
	{
		rt_uint16_t offset;
		
		/* set the first text rect */
		item_rect.y2 = item_rect.y1 + item_size;

		offset = (item_size - RADIO_BOX_H) / 2;
		/* draw each radio button */
		for (index = 0; index < radiobox->item_count; index ++)
		{
			if (item_rect.y2 > rect.y2 - item_size) break;

			/* draw radio */
			if (radiobox->item_selection == index)
			{
				if (RTGUI_WIDGET_IS_FOCUSED(radiobox))
					rtgui_dc_draw_focus_rect(dc, &item_rect);

				rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1 + offset, RADIO_BOX_H, radio_checked_byte);
			}
			else
			{
				rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1 + offset, RADIO_BOX_H, radio_unchecked_byte);
			}

			/* draw text */
			item_rect.x1 += item_size + 3;
			rtgui_dc_draw_text(dc, radiobox->items[index], &item_rect);
			item_rect.x1 -= item_size + 3;

			item_rect.y1 += item_size;
			item_rect.y2 += item_size;
		}
	}
	else
	{
		/* set the first text rect */
		item_rect.x2 = item_rect.x1 + item_size;
		item_rect.y2 = item_rect.y1 + bord_size;

		/* draw each radio button */
		for (index = 0; index < radiobox->item_count; index ++)
		{
			if (item_rect.x2 > rect.x2 - item_size) break;

			/* draw radio */
			if (radiobox->item_selection == index)
			{
				if (RTGUI_WIDGET_IS_FOCUSED(radiobox))
					rtgui_dc_draw_focus_rect(dc, &item_rect);
				rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1, RADIO_BOX_H, radio_checked_byte);
			}
			else
			{
				rtgui_dc_draw_word(dc, item_rect.x1, item_rect.y1, RADIO_BOX_H, radio_unchecked_byte);
			}

			/* draw text */
			item_rect.x1 += bord_size + 3;
			rtgui_dc_draw_text(dc, radiobox->items[index], &item_rect);
			item_rect.x1 -= bord_size + 3;

			item_rect.x1 += item_size;
			item_rect.x2 += (item_size - 1);
		}
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
}

void rtgui_theme_draw_slider(struct rtgui_slider* slider)
{
	/* draw button */
	struct rtgui_dc* dc;
	int i, xsize, x0;
	rtgui_rect_t r, focus_rect, slider_rect, slot_rect;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(slider));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(slider), &focus_rect);
	/* fill widget rect with background color */
	rtgui_dc_fill_rect(dc, &focus_rect);
	r = focus_rect;

	if (slider->orient == RTGUI_VERTICAL)
	{
		rtgui_rect_inflate(&r, -1);
		xsize = r.y2 - r.y1  + 1 - slider->thumb_width;
		x0 = r.y1 + slider->thumb_width / 2;

		/* calculate thumb position */
		slider_rect = r;
		slider_rect.x1 = 5;
		slider_rect.y1 = x0 + xsize * (slider->value - slider->min) / (slider->max - slider->min) - slider->thumb_width/2;
		slider_rect.y2  = slider_rect.y1 + slider->thumb_width;

		/* calculate slot position */
		slot_rect.y1 = x0;
		slot_rect.y2 = x0 + xsize;
		slot_rect.x1 = (slider_rect.x1 + slider_rect.x2) /2 -1;
		slot_rect.x2 = slot_rect.x1 +3;
		/* draw slot */
		rtgui_dc_draw_border(dc, &slot_rect, RTGUI_BORDER_RAISE);

		/* draw the ticks */
		for (i = 0; i <= slider->ticks; i++)
		{
			int x = x0 + xsize * i / slider->ticks;
			rtgui_dc_draw_hline(dc, 1, 3, x);
		}

		/* draw the thumb */
		rtgui_dc_fill_rect(dc, &slider_rect);
		rtgui_dc_draw_border(dc, &slider_rect, RTGUI_BORDER_RAISE);
	}
	else
	{
		rtgui_rect_inflate(&r, -1);
		xsize = r.x2 - r.x1  + 1 - slider->thumb_width;
		x0 = r.x1 + slider->thumb_width / 2;

		/* calculate thumb position */
		slider_rect = r;
		slider_rect.y1 = 5;
		slider_rect.x1 = x0 + xsize * (slider->value - slider->min) / (slider->max - slider->min) - slider->thumb_width/2;
		slider_rect.x2  = slider_rect.x1 + slider->thumb_width;

		/* calculate slot position */
		slot_rect.x1 = x0;
		slot_rect.x2 = x0 + xsize;
		slot_rect.y1 = (slider_rect.y1 + slider_rect.y2) /2 -1;
		slot_rect.y2 = slot_rect.y1 +3;
		/* draw slot */
		rtgui_dc_draw_border(dc, &slot_rect, RTGUI_BORDER_RAISE);

		/* draw the ticks */
		for (i = 0; i <= slider->ticks; i++)
		{
			int x = x0 + xsize * i / slider->ticks;
			rtgui_dc_draw_vline(dc, x, 1, 3);
		}

		/* draw the thumb */
		rtgui_dc_fill_rect(dc, &slider_rect);
		rtgui_dc_draw_border(dc, &slider_rect, RTGUI_BORDER_RAISE);
	}

	/* draw focus */
	if (RTGUI_WIDGET_IS_FOCUSED(slider))
	{
		rtgui_dc_draw_focus_rect(dc, &focus_rect);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
	return;
}


const static rt_uint8_t _up_arrow[]    = {0x10, 0x38, 0x7C, 0xFE};
const static rt_uint8_t _down_arrow[]  = {0xFE,0x7C, 0x38, 0x10};
const static rt_uint8_t _left_arrow[]  = {0x10, 0x30, 0x70, 0xF0, 0x70, 0x30, 0x10};
const static rt_uint8_t _right_arrow[] = {0x80, 0xC0, 0xE0, 0xF0, 0xE0, 0xC0, 0x80};

void rtgui_theme_draw_scrollbar(struct rtgui_scrollbar* bar)
{
	/* draw scroll bar */
	struct rtgui_dc* dc;
	rtgui_rect_t rect, btn_rect, thum_rect, arrow_rect;
	rtgui_color_t bc, fc;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(&(bar->parent));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);

	/* draw background */
	fc = RTGUI_WIDGET_FOREGROUND(bar);
	if (!RTGUI_WIDGET_IS_ENABLE(bar))
		RTGUI_WIDGET_FOREGROUND(bar) = RTGUI_RGB(128, 128, 128);

	bc = RTGUI_WIDGET_BACKGROUND(bar);
	RTGUI_WIDGET_BACKGROUND(bar) = white;
	rtgui_dc_fill_rect(dc, &rect);

	RTGUI_WIDGET_BACKGROUND(bar) = bc;

	if (bar->orient == RTGUI_VERTICAL)
	{
		btn_rect = rect;
		btn_rect.y2 = btn_rect.y1 + (rect.x2 - rect.x1);

		/* draw up button */
		rtgui_dc_fill_rect(dc, &btn_rect);
		if (bar->status & SBS_UPARROW) rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);

		/* draw arrow */
		arrow_rect.x1 = 0; arrow_rect.y1 = 0;
		arrow_rect.x2 = 7; arrow_rect.y2 = 4;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, 
			RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, 
			rtgui_rect_height(arrow_rect), _up_arrow);

		/* draw thumb */
		if (RTGUI_WIDGET_IS_ENABLE(bar))
		{
			rtgui_scrollbar_get_thumb_rect(bar, &thum_rect);
			rtgui_dc_fill_rect(dc, &thum_rect);
			rtgui_dc_draw_border(dc, &thum_rect, RTGUI_BORDER_RAISE);
		}

		/* draw down button */
		btn_rect.y1 = rect.y2 - (rect.x2 - rect.x1);
		btn_rect.y2 = rect.y2;

		rtgui_dc_fill_rect(dc, &btn_rect);
		if (bar->status & SBS_DOWNARROW) rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);

		arrow_rect.x1 = 0; arrow_rect.y1 = 0;
		arrow_rect.x2 = 7; arrow_rect.y2 = 4;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, 
			RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, 
			rtgui_rect_height(arrow_rect), _down_arrow);
	}
	else
	{
		btn_rect.x1 = rect.x1;
		btn_rect.y1 = rect.y1;
		btn_rect.x2 = rect.y2;
		btn_rect.y2 = rect.y2;

		/* draw left button */
		rtgui_dc_fill_rect(dc, &btn_rect);
		if (bar->status & SBS_LEFTARROW) rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);

		arrow_rect.x1 = 0; arrow_rect.y1 = 0;
		arrow_rect.x2 = 4; arrow_rect.y2 = 7;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, 
			RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, 
			rtgui_rect_height(arrow_rect), _left_arrow);

		/* draw thumb */
		if (RTGUI_WIDGET_IS_ENABLE(bar))
		{
			rtgui_scrollbar_get_thumb_rect(bar, &thum_rect);
			rtgui_dc_fill_rect(dc, &thum_rect);
			rtgui_dc_draw_border(dc, &thum_rect, RTGUI_BORDER_RAISE);
		}

		btn_rect.x1 = rect.x2 - rect.y2;
		btn_rect.x2 = rect.x2;

		/* draw right button */
		rtgui_dc_fill_rect(dc, &btn_rect);
		if (bar->status & SBS_RIGHTARROW) rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);

		arrow_rect.x1 = 0; arrow_rect.y1 = 0;
		arrow_rect.x2 = 4; arrow_rect.y2 = 7;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, 
			RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, 
			rtgui_rect_height(arrow_rect), _right_arrow);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
	RTGUI_WIDGET_FOREGROUND(bar) = fc;

	return;
}

void rtgui_theme_draw_progressbar(struct rtgui_progressbar* bar)
{
	/* draw progress bar */
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
    int max = bar->range;
    int pos = bar->position;
    int left;
	rtgui_color_t bc;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(&(bar->parent));
	if (dc == RT_NULL) return;

	bc = RTGUI_DC_BC(dc);
	rtgui_widget_get_rect(&(bar->parent), &rect);

	/* fill button rect with background color */
	RTGUI_WIDGET_BACKGROUND(bar) = RTGUI_RGB(212, 208, 200);

    /* draw border */
	rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);

	/* Nothing to draw */
    if (max == 0)
    {
        rtgui_dc_end_drawing(dc);
        return;
    }

	rect.x2 ++; rect.y2 ++;
    left = max - pos;
	rtgui_rect_inflate(&rect, -2);
    RTGUI_WIDGET_BACKGROUND(bar) = RTGUI_RGB(0, 0, 255);
	rect.y2 --; rect.x2 --;

    if (bar->orient == RTGUI_VERTICAL)
    {
        /* Vertical bar grows from bottom to top */
        int dy = (rtgui_rect_height(rect) * left) / max;
        rect.y1 += dy;
        rtgui_dc_fill_rect(dc, &rect);

		RTGUI_DC_BC(dc) = bc;
		rect.y1 -= dy; rect.y2 = dy;
		rtgui_dc_fill_rect(dc, &rect);
    }
    else
    {
        /* Horizontal bar grows from left to right */
		int dx = (rtgui_rect_width(rect) * left) / max;
        rect.x2 -= dx;
        rtgui_dc_fill_rect(dc, &rect);

		RTGUI_DC_BC(dc) = bc;
		rect.x1 = rect.x2; rect.x2 += dx;
		rtgui_dc_fill_rect(dc, &rect);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
	return;
}

void rtgui_theme_draw_staticline(struct rtgui_staticline* staticline)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	
	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(staticline));
	if (dc == RT_NULL) return ;

	rtgui_widget_get_rect(RTGUI_WIDGET(staticline), &rect);
	rtgui_dc_fill_rect(dc, &rect);
	
	if (staticline->orient == RTGUI_HORIZONTAL)
	{
		rtgui_dc_draw_horizontal_line(dc, rect.x1, rect.x2, rect.y1);
	}
	else
	{
		rtgui_dc_draw_vertical_line(dc, rect.x1, rect.y1, rect.y2);
	}
	
	rtgui_dc_end_drawing(dc);
}

rt_uint16_t rtgui_theme_get_selected_height()
{
	return SELECTED_HEIGHT;
}

void rtgui_theme_draw_selected(struct rtgui_dc* dc, rtgui_rect_t *rect)
{
	rtgui_color_t bc;
	rt_uint16_t index;
	
	bc = RTGUI_DC_FC(dc);
	RTGUI_DC_FC(dc) = selected_color;

	rtgui_dc_draw_hline(dc, rect->x1 + 3, rect->x2 - 2, rect->y1 + 1);
	rtgui_dc_draw_hline(dc, rect->x1 + 3, rect->x2 - 2, rect->y2 - 2);

	rtgui_dc_draw_vline(dc, rect->x1 + 2, rect->y1 + 2, rect->y2 - 2);
	rtgui_dc_draw_vline(dc, rect->x2 - 2, rect->y1 + 2, rect->y2 - 2);

	for (index = rect->y1 + 1; index < rect->y2 - 2; index ++)
		rtgui_dc_draw_hline(dc, rect->x1 + 3, rect->x2 - 2, index);

	RTGUI_DC_FC(dc) = bc;
}

/* get default background color */
rtgui_color_t rtgui_theme_default_bc()
{
	return default_background;
}

/* get default foreground color */
rtgui_color_t rtgui_theme_default_fc()
{
	return default_foreground;
}

