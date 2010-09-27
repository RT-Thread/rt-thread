/*
 * File      : rtgui_theme.h
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
#ifndef __RTGUI_THEME_H__
#define __RTGUI_THEME_H__

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>

#define CHECK_BOX_W		13
#define CHECK_BOX_H		13

#define RADIO_BOX_W		12
#define RADIO_BOX_H		12

#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/iconbox.h>
#include <rtgui/widgets/checkbox.h>
#include <rtgui/widgets/radiobox.h>
#include <rtgui/widgets/slider.h>
#include <rtgui/widgets/scrollbar.h>
#include <rtgui/widgets/progressbar.h>
#include <rtgui/widgets/staticline.h>

#ifdef __cplusplus
extern "C" {
#endif

void rtgui_system_theme_init(void);

void rtgui_theme_draw_win(struct rtgui_topwin* win);
void rtgui_theme_draw_button(rtgui_button_t* btn);
void rtgui_theme_draw_label(rtgui_label_t* label);
void rtgui_theme_draw_textbox(rtgui_textbox_t* box);
void rtgui_theme_draw_iconbox(rtgui_iconbox_t* iconbox);
void rtgui_theme_draw_checkbox(rtgui_checkbox_t* checkbox);
void rtgui_theme_draw_radiobutton(struct rtgui_radiobox* radiobox, rt_uint16_t item);

void rtgui_theme_draw_radiobox(struct rtgui_radiobox* radiobox);
void rtgui_theme_draw_slider(struct rtgui_slider* slider);
void rtgui_theme_draw_scrollbar(struct rtgui_scrollbar* bar);
void rtgui_theme_draw_progressbar(struct rtgui_progressbar* bar);
void rtgui_theme_draw_staticline(struct rtgui_staticline* staticline);

rt_uint16_t rtgui_theme_get_selected_height(void);
void rtgui_theme_draw_selected(struct rtgui_dc* dc, rtgui_rect_t *rect);

rtgui_color_t rtgui_theme_default_bc(void);
rtgui_color_t rtgui_theme_default_fc(void);

#ifdef __cplusplus
}
#endif

#endif
