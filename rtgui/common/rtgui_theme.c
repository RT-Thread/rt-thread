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

#define WINTITLE_CB_WIDTH		14
#define WINTITLE_CB_HEIGHT		14
#define SELECTED_HEIGHT			25

static const rt_uint8_t *close_unpressed_xpm[] = {
	"14 14 55 1",
	" 	c None",
	".	c #DCDFEA",
	"+	c #A4ADD3",
	"@	c #8F9ACA",
	"#	c #98A2CD",
	"$	c #D2D6E6",
	"%	c #F7F7F7",
	"&	c #F6F6F6",
	"*	c #B9C1D0",
	"=	c #7A8AAA",
	"-	c #D6DAE2",
	";	c #D8DCE3",
	">	c #7485A5",
	",	c #455C89",
	"'	c #516690",
	")	c #D3D8E0",
	"!	c #536891",
	"~	c #6D7FA1",
	"{	c #F5F5F5",
	"]	c #D1D6DF",
	"^	c #D2D7DF",
	"/	c #D5D9E1",
	"(	c #4E648E",
	"_	c #CFD4DE",
	":	c #F4F4F4",
	"<	c #D0D5DE",
	"[	c #CED3DD",
	"}	c #F3F3F3",
	"|	c #CFD4DD",
	"1	c #CDD2DC",
	"2	c #F2F2F2",
	"3	c #D3D7DF",
	"4	c #526790",
	"5	c #D0D5DD",
	"6	c #F1F1F1",
	"7	c #D2D6DE",
	"8	c #CFD4DC",
	"9	c #F0F0F0",
	"0	c #D1D5DD",
	"a	c #C9CED8",
	"b	c #CDD2DB",
	"c	c #50658F",
	"d	c #CED3DB",
	"e	c #7283A3",
	"f	c #6E80A2",
	"g	c #EFEFEF",
	"h	c #B2BACA",
	"i	c #7081A2",
	"j	c #C8CDD7",
	"k	c #CCD1DA",
	"l	c #ACB5C7",
	"m	c #D0D4E2",
	"n	c #EEEEEE",
	"o	c #D2D5E3",
	"p	c #97A1CC",
	".+@@@@@@@@@@+.",
	"#$%%%%%%%%%%$#",
	"@&*=-&&&&;=*&@",
	"@&>,')&&-!,~&@",
	"@{]','^/!,(_{@",
	"@::<','!,([::@",
	"@}}}|',,(1}}}@",
	"@22234,,'5222@",
	"@6674,(','866@",
	"@904,(abc,cd9@",
	"@9e,(a99bc,f9@",
	"@ghijggggkelg@",
	"#mnnnnnnnnnnm#",
	"op@@@@@@@@@@po"};

static const rt_uint8_t *close_pressed_xpm[] = {
	"14 14 66 1",
	" 	c None",
	".	c #CED4EE",
	"+	c #7E90DD",
	"@	c #6076D7",
	"#	c #6C80D9",
	"$	c #BFC8EA",
	"%	c #F2F3F5",
	"&	c #F0F2F3",
	"*	c #A5B6D7",
	"=	c #587ABB",
	"-	c #C9D3E4",
	";	c #CBD5E4",
	">	c #EEF0F2",
	",	c #5073B7",
	"'	c #1746A3",
	")	c #2551A8",
	"!	c #C5CFE2",
	"~	c #C8D1E3",
	"{	c #2853A8",
	"]	c #496DB4",
	"^	c #ECEEF1",
	"/	c #C0CCE0",
	"(	c #C3CEE1",
	"_	c #C6D0E2",
	":	c #224FA7",
	"<	c #BEC9DF",
	"[	c #EAECF0",
	"}	c #BFCAE0",
	"|	c #2551A7",
	"1	c #224EA7",
	"2	c #BCC8DF",
	"3	c #E8EBEE",
	"4	c #BDCADE",
	"5	c #BAC7DD",
	"6	c #E6E9ED",
	"7	c #C1CBDF",
	"8	c #2753A8",
	"9	c #BECADE",
	"0	c #E4E7EB",
	"a	c #BFCADD",
	"b	c #224EA6",
	"c	c #BDC8DC",
	"d	c #E1E5EA",
	"e	c #2752A8",
	"f	c #B3C0D9",
	"g	c #B8C5DB",
	"h	c #2451A7",
	"i	c #BAC6DB",
	"j	c #DFE2E8",
	"k	c #4C70B4",
	"l	c #B2BED8",
	"m	c #B6C2D9",
	"n	c #2450A7",
	"o	c #486BB3",
	"p	c #DCE0E7",
	"q	c #96A8CE",
	"r	c #496CB3",
	"s	c #AFBCD7",
	"t	c #B4C1D8",
	"u	c #4B6FB4",
	"v	c #8EA4CC",
	"w	c #6C80D8",
	"x	c #B4BEDF",
	"y	c #DADEE5",
	"z	c #B5BEDE",
	"A	c #6A7ED7",
	".+@@@@@@@@@@+.",
	"#$%%%%%%%%%%$#",
	"@&*=-&&&&;=*&@",
	"@>,')!>>~{']>@",
	"@^/)')(_{':<^@",
	"@[[}|'|{'12[[@",
	"@3334|''15333@",
	"@66678''|9666@",
	"@00a8'b|'|c00@",
	"@dce'bfgh'hid@",
	"@jk'bljjmn'oj@",
	"@pqrspppptuvp@",
	"wxyyyyyyyyyyxw",
	"zA@@@@@@@@@@Az"};

static rtgui_image_t* close_pressed = RT_NULL;
static rtgui_image_t* close_unpressed = RT_NULL;

const rtgui_color_t default_foreground = RTGUI_RGB(0x00, 0x00, 0x00);
const rtgui_color_t default_background = RTGUI_RGB(212, 208, 200);

extern struct rtgui_font rtgui_font_asc16;
extern struct rtgui_font rtgui_font_arial16;
extern struct rtgui_font rtgui_font_asc12;
extern struct rtgui_font rtgui_font_arial12;

/* init theme */
void rtgui_system_theme_init()
{
	close_pressed = rtgui_image_create_from_mem("xpm", 
		(const rt_uint8_t*)close_pressed_xpm, sizeof(close_pressed_xpm), RT_TRUE);
	close_unpressed = rtgui_image_create_from_mem("xpm", 
		(const rt_uint8_t*)close_unpressed_xpm, sizeof(close_unpressed_xpm), RT_TRUE);

	rtgui_font_set_defaut(&rtgui_font_arial16);
}

/* window drawing */
void rtgui_theme_draw_win(struct rtgui_topwin* win)
{
	struct rtgui_dc* dc;
	rtgui_rect_t rect;

	/* init close box image */
	if (close_pressed == RT_NULL)
		close_pressed = rtgui_image_create_from_mem("xpm", 
			(const rt_uint8_t*)close_pressed_xpm, sizeof(close_pressed_xpm), RT_TRUE);
	if (close_unpressed == RT_NULL)
		close_unpressed = rtgui_image_create_from_mem("xpm", 
			(const rt_uint8_t*)close_unpressed_xpm, sizeof(close_unpressed_xpm), RT_TRUE);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(win->title));

	/* get rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(win->title), &rect);

	/* draw border */
	if (win->flag & WINTITLE_BORDER)
	{
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(win->title)) = RTGUI_RGB(212, 208, 200);
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y1);
		rtgui_dc_draw_vline(dc, rect.x1, rect.y1, rect.y2);

		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(win->title)) = white;
		rtgui_dc_draw_hline(dc, rect.x1 + 1, rect.x2 - 1, rect.y1 + 1);
		rtgui_dc_draw_vline(dc, rect.x1 + 1, rect.y1 + 1, rect.y2 - 1);

		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(win->title)) = RTGUI_RGB(128, 128, 128);
		rtgui_dc_draw_hline(dc, rect.x1 + 1, rect.x2 - 1, rect.y2 - 1);
		rtgui_dc_draw_vline(dc, rect.x2 - 1, rect.y1 + 1, rect.y2 - 1);

		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(win->title)) = RTGUI_RGB(64, 64, 64);
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2 + 1, rect.y2);
		rtgui_dc_draw_vline(dc, rect.x2, rect.y1, rect.y2);

		/* shrink border */
		rect.x1 += WINTITLE_BORDER_SIZE;
		rect.y1 += WINTITLE_BORDER_SIZE;
		rect.x2 -= WINTITLE_BORDER_SIZE;
		rect.y2 -= WINTITLE_BORDER_SIZE;
	}

	/* draw title */
	if (!(win->flag & WINTITLE_NO))
	{
		rt_uint32_t index;
		float r, g, b, delta;

		if (win->flag & WINTITLE_ACTIVATE)
		{
			r = 10; g = 36; b = 106;
			delta = (float)(rect.x2 - rect.x1) / 160;
		}
		else
		{
			r = 128; g = 128; b = 128;
			delta = (float)(rect.x2 - rect.x1) / 64;
		}

		for (index = rect.x1; index < rect.x2; index ++)
		{
			RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(win->title)) = RTGUI_RGB(r, g, b);
			rtgui_dc_draw_vline(dc, index, rect.y1, rect.y2);
			r += delta; g += delta; b += delta;
		}

		if (win->flag & WINTITLE_ACTIVATE)
		{
			RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(win->title)) = white;
		}
		else
		{
			RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(win->title)) = RTGUI_RGB(212, 208, 200);
		}
		// rtgui_dc_fill_rect(dc, &rect);

		rect.x1 += 4;
		rect.y1 += 2;
		rtgui_dc_draw_text(dc, rtgui_wintitle_get_title(win->title), &rect);

		if (win->flag & WINTITLE_CLOSEBOX)
		{
			/* get close button rect */
			rect.x1 = rtgui_rect_width(RTGUI_WIDGET(win->title)->extent) -
				WINTITLE_BORDER_SIZE - WINTITLE_CB_WIDTH - 3;
			rect.y1 = 3;
			rect.x2 = rect.x1 + WINTITLE_CB_WIDTH;
			rect.y2 = rect.y1 + WINTITLE_CB_HEIGHT;

			/* draw close box */
			if(win->flag & WINTITLE_CB_PRESSED) rtgui_image_blit(close_pressed, dc, &rect);
			else rtgui_image_blit(close_unpressed, dc, &rect);
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
	rtgui_color_t fc;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(btn));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(btn), &rect);

	/* get forecolor */
	fc = RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(btn));

	/* fill button rect with background color */
	rtgui_dc_fill_rect(dc, &rect);

	if (btn->flag & RTGUI_BUTTON_TYPE_PUSH && btn->flag & RTGUI_BUTTON_FLAG_PRESS)
	{
		/* draw border */
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(btn)) = RTGUI_RGB(64, 64, 64);
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y1);
		rtgui_dc_draw_vline(dc, rect.x1, rect.y1, rect.y2);

		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(btn)) = RTGUI_RGB(128, 128, 128);
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2 - 1, rect.y1 + 1);
		rtgui_dc_draw_vline(dc, rect.x1 + 1, rect.y1 + 1, rect.y2 - 2);

		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(btn)) = RTGUI_RGB(255, 255, 255);
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2 + 1, rect.y2 - 1);
		rtgui_dc_draw_vline(dc, rect.x2 - 1, rect.y1, rect.y2);

		if (btn->pressed_image != RT_NULL)
		{
			rtgui_rect_t image_rect;
			image_rect.x1 = 0; image_rect.y1 = 0;
			image_rect.x2 = btn->unpressed_image->w;
			image_rect.y2 = btn->unpressed_image->h;
			rtgui_rect_moveto_align(&rect, &image_rect, RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);

			rtgui_image_blit(btn->pressed_image, dc, &image_rect);
		}
	}
	else if (btn->flag & RTGUI_BUTTON_FLAG_PRESS)
	{
		if (btn->pressed_image != RT_NULL)
		{
			rtgui_rect_t image_rect;
			image_rect.x1 = 0; image_rect.y1 = 0;
			image_rect.x2 = btn->unpressed_image->w;
			image_rect.y2 = btn->unpressed_image->h;
			rtgui_rect_moveto_align(&rect, &image_rect, RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);

			rtgui_image_blit(btn->pressed_image, dc, &image_rect);
		}
		else
		{
			/* draw border */
			RTGUI_WIDGET(btn)->gc.foreground = RTGUI_RGB(0, 0, 0);
			rtgui_dc_draw_rect(dc, &rect);

			RTGUI_WIDGET(btn)->gc.foreground = RTGUI_RGB(128, 128, 128);
			rect.x1 += 1; rect.y1 += 1; rect.x2 -= 1; rect.y2 -= 1;
			rtgui_dc_draw_rect(dc, &rect);
		}
	}
	else
	{
		if (btn->unpressed_image != RT_NULL)
		{
			rtgui_rect_t image_rect;
			image_rect.x1 = 0; image_rect.y1 = 0;
			image_rect.x2 = btn->unpressed_image->w;
			image_rect.y2 = btn->unpressed_image->h;
			rtgui_rect_moveto_align(&rect, &image_rect, RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);

			rtgui_image_blit(btn->unpressed_image, dc, &image_rect);
		}
		else
		{
			/* draw border */
			RTGUI_WIDGET(btn)->gc.foreground = RTGUI_RGB(255, 255, 255);
			rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y1);
			rtgui_dc_draw_vline(dc, rect.x1, rect.y1, rect.y2);

			RTGUI_WIDGET(btn)->gc.foreground = RTGUI_RGB(0, 0, 0);
			rtgui_dc_draw_hline(dc, rect.x1, rect.x2 + 1, rect.y2);
			rtgui_dc_draw_vline(dc, rect.x2, rect.y1, rect.y2);

			RTGUI_WIDGET(btn)->gc.foreground = RTGUI_RGB(128, 128, 128);
			rtgui_dc_draw_hline(dc, rect.x1 + 1, rect.x2, rect.y2 - 1);
			rtgui_dc_draw_vline(dc, rect.x2 - 1, rect.y1 + 1, rect.y2 - 1);
		}
	}

	/* set forecolor */
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(btn)) = fc;

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

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(box));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);

	/* fill widget rect with background color */
	rtgui_dc_fill_rect(dc, &rect);

	/* draw border */
	rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_STATIC);

	/* draw text */
	if (box->text != RT_NULL)
	{
		rect.x1 += RTGUI_TEXTBOX_MARGIN;

		rtgui_dc_draw_text(dc, box->text, &rect);

		/* draw caret */
		if (box->flag & RTGUI_TEXTBOX_CARET_SHOW)
		{
			rect.x1 += box->position * box->font_width;
			rect.x2 = rect.x1 + box->font_width;

			rect.y1 = rect.y2 - 3;

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
		rtgui_dc_draw_text(dc, iconbox->text, &rect);
	}
	else if (iconbox->text_position == RTGUI_ICONBOX_TEXT_RIGHT && iconbox->text != RT_NULL)
	{
		rect.x1 = iconbox->image->w + RTGUI_WIDGET_DEFAULT_MARGIN;
		rtgui_dc_draw_text(dc, iconbox->text, &rect);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
}

void rtgui_theme_draw_checkbox(struct rtgui_checkbox* checkbox)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect, box_rect;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(checkbox));
	if (dc == RT_NULL) return;

	/* get rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(checkbox), &rect);

    /* fill rect */
	rtgui_dc_fill_rect(dc, &rect);

	if (RTGUI_WIDGET_IS_FOCUSED(RTGUI_WIDGET(checkbox)) == RT_TRUE)
	{
		/* draw focused border */
		rtgui_rect_inflate(&rect, -1);
		rtgui_dc_draw_focus_rect(dc, &rect);

		rtgui_rect_inflate(&rect, 1);
	}

	/* draw check box */
	box_rect = rect;
	box_rect.x1 += 2;
	box_rect.y1 += 2;
	box_rect.x2 = rtgui_rect_height(rect) - 4;
	box_rect.y2 = rtgui_rect_height(rect) - 4;

	rtgui_dc_draw_rect(dc, &box_rect);
	if (checkbox->status_down == RTGUI_CHECKBOX_STATUS_CHECKED)
	{
		rtgui_color_t save;

		save = RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(checkbox));

		/* swap fore/back color */
		RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(checkbox)) = RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(checkbox));

		rtgui_rect_inflate(&box_rect, -4);
		rtgui_dc_fill_rect(dc, &box_rect);

		/* restore saved color */
		RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(checkbox)) = save;
	}

	/* draw text */
	rect.x1 += rtgui_rect_height(rect) - 4 + 5;
	rtgui_dc_draw_text(dc, rtgui_label_get_text(RTGUI_LABEL(checkbox)), &rect);

	/* end drawing */
	rtgui_dc_end_drawing(dc);

	return;
}

void rtgui_theme_draw_radiobox(struct rtgui_radiobox* radiobox)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect, item_rect;
	rt_size_t item_size, bord_size, index;
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
		rtgui_font_get_metrics(rtgui_dc_get_font(dc), "H", &item_rect);
		bord_size = rtgui_rect_height(item_rect);
	}

	/* draw box */
	rtgui_rect_inflate(&rect, -bord_size/2);
	fc = RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(radiobox));

	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(radiobox)) = white;
	rect.x1 ++; rect.y1 ++; rect.x2 ++; rect.y2 ++;
	rtgui_dc_draw_rect(dc, &rect);

	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(radiobox)) = RTGUI_RGB(128, 128, 128);
	rect.x1 --; rect.y1 --; rect.x2 --; rect.y2 --;
	rtgui_dc_draw_rect(dc, &rect);

	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(radiobox)) = fc;

	rtgui_rect_inflate(&rect, bord_size/2);
	if (radiobox->text != RT_NULL)
	{
		struct rtgui_rect text_rect;

		/* draw group text */
		rtgui_font_get_metrics(rtgui_dc_get_font(dc), radiobox->text, &text_rect);
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
		/* set the first text rect */
		item_rect.y2 = item_rect.y1 + item_size;

		/* draw each radio button */
		for (index = 0; index < radiobox->item_count; index ++)
		{
			if (item_rect.y2 > rect.y2 - item_size) break;

			/* draw radio */
			if (radiobox->item_selection == index)
			{
				if (RTGUI_WIDGET_IS_FOCUSED(RTGUI_WIDGET(radiobox)))
					rtgui_dc_draw_focus_rect(dc, &item_rect);
				rtgui_dc_draw_circle(dc, item_rect.x1 + item_size/2 + 2, item_rect.y1 + item_size/2 + 2, item_size/2 - 2);
				rtgui_dc_fill_circle(dc, item_rect.x1 + item_size/2 + 2, item_rect.y1 + item_size/2 + 2, item_size/2 - 4);
			}
			else
			{
				rtgui_dc_draw_circle(dc, item_rect.x1 + item_size/2 + 2, item_rect.y1 + item_size/2 + 2, item_size/2 - 2);
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

		/* draw each radio button */
		for (index = 0; index < radiobox->item_count; index ++)
		{
			if (item_rect.x2 > rect.x2 - item_size) break;

			/* draw radio */
			if (radiobox->item_selection == index)
			{
				rtgui_dc_draw_focus_rect(dc, &item_rect);
				rtgui_dc_draw_circle(dc, item_rect.x1 + bord_size/2 + 2, item_rect.y1 + bord_size/2 + 2, bord_size/2 - 2);
				rtgui_dc_fill_circle(dc, item_rect.x1 + bord_size/2 + 2, item_rect.y1 + bord_size/2 + 2, bord_size/2 - 4);
			}
			else
			{
				rtgui_dc_draw_circle(dc, item_rect.x1 + bord_size/2 + 2, item_rect.y1 + bord_size/2 + 2, bord_size/2 - 2);
			}

			/* draw text */
			item_rect.x1 += bord_size + 3;
			rtgui_dc_draw_text(dc, radiobox->items[index], &item_rect);
			item_rect.x1 -= bord_size + 3;

			item_rect.x1 += item_size;
			item_rect.x2 += item_size;
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
	if (RTGUI_WIDGET_IS_FOCUSED(RTGUI_WIDGET(slider)))
	{
		rtgui_dc_draw_focus_rect(dc, &focus_rect);
	}

	/* end drawing */
	rtgui_dc_end_drawing(dc);
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

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(&(bar->parent));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(&(bar->parent), &rect);

	/* fill button rect with background color */
	bar->parent.gc.background = RTGUI_RGB(212, 208, 200);
	rtgui_dc_fill_rect(dc, &rect);

    /* draw border */
    bar->parent.gc.foreground = RTGUI_RGB(128, 128, 128);
    rtgui_dc_draw_hline(dc, rect.x1, rect.x2 - 1, rect.y1);
    rtgui_dc_draw_vline(dc, rect.x1, rect.y1, rect.y2 - 1);
    bar->parent.gc.foreground = RTGUI_RGB(64, 64, 64);
    rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y1 + 1);
    rtgui_dc_draw_vline(dc, rect.x1 + 1, rect.y1, rect.y2);

	bar->parent.gc.foreground = RTGUI_RGB(212, 208, 200);
	rtgui_dc_draw_hline(dc, rect.x1, rect.x2 + 1, rect.y2);
	rtgui_dc_draw_vline(dc, rect.x2, rect.y1, rect.y2);

	bar->parent.gc.foreground = RTGUI_RGB(255, 255, 255);
	rtgui_dc_draw_hline(dc, rect.x1 + 1, rect.x2, rect.y2 - 1);
	rtgui_dc_draw_vline(dc, rect.x2 - 1, rect.y1 + 1, rect.y2 - 1);

    /* Nothing to draw */
    if (max == 0)
    {
        rtgui_dc_end_drawing(dc);
        return;
    }

    left = max - pos;
	rtgui_rect_inflate(&rect, -2);
    bar->parent.gc.background = RTGUI_RGB(0, 0, 255);

    if (bar->orientation == RTGUI_VERTICAL)
    {
        /* Vertical bar grows from bottom to top */
        int dy = (rtgui_rect_height(rect) * left) / max;
        rect.y1 += dy;
        rtgui_dc_fill_rect(dc, &rect);
    }
    else
    {
        /* Horizontal bar grows from left to right */
        rect.x2 -= (rtgui_rect_width(rect) * left) / max;
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
	
	if (staticline->orientation == RTGUI_HORIZONTAL)
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
	rtgui_color_t saved;
	rtgui_rect_t  focus_rect;
	
	focus_rect = *rect;
	saved = rtgui_dc_get_color(dc);
	rtgui_dc_set_color(dc, blue);

	rtgui_rect_inflate(&focus_rect, -1);
	rtgui_dc_draw_focus_rect(dc, &focus_rect);
	rtgui_rect_inflate(&focus_rect, -1);
	rtgui_dc_draw_focus_rect(dc, &focus_rect);

	rtgui_dc_set_color(dc, saved);
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

