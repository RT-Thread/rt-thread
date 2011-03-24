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

#define CHECK_BOX_W		13
#define CHECK_BOX_H		13

#define RADIO_BOX_W		12
#define RADIO_BOX_H		12

#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/iconbox.h>
#include <rtgui/widgets/checkbox.h>
#include <rtgui/widgets/radiobox.h>
#include <rtgui/widgets/listbox.h>
#include <rtgui/widgets/scrollbar.h>
#include <rtgui/widgets/slider.h>
#include <rtgui/widgets/progressbar.h>
#include <rtgui/widgets/staticline.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/menu.h>
#include <rtgui/widgets/combobox.h>

#ifdef __cplusplus
extern "C" {
#endif

void rtgui_system_theme_init(void);

void rtgui_theme_draw_win_closebox(rtgui_win_t *win);
void rtgui_theme_draw_win_maxbox(rtgui_win_t *win);
void rtgui_theme_draw_win_minbox(rtgui_win_t *win);
void rtgui_theme_draw_win_title(rtgui_win_t *win);
void rtgui_theme_draw_win(rtgui_win_t* win);
void rtgui_theme_draw_button(rtgui_button_t* btn);
void rtgui_theme_draw_label(rtgui_label_t* label);
void rtgui_theme_draw_textbox(rtgui_textbox_t* box);
void rtgui_theme_draw_iconbox(rtgui_iconbox_t* iconbox);
void rtgui_theme_draw_checkbox(rtgui_checkbox_t* checkbox);
void rtgui_theme_draw_radiobutton(rtgui_radiobox_t* rbox, rt_uint32_t index);
void rtgui_theme_draw_radiobox(rtgui_radiobox_t* rbox);
void rtgui_theme_draw_menu(rtgui_menu_t* menu);
void rtgui_theme_draw_menu_item(rtgui_menu_t* menu, rtgui_menu_item_t *item);
void rtgui_theme_draw_slider(rtgui_slider_t* slider);
void rtgui_theme_draw_scrollbar(rtgui_scrollbar_t* bar);
void rtgui_theme_draw_progressbar(rtgui_progressbar_t* bar);
void rtgui_theme_draw_staticline(rtgui_staticline_t* sline);

void rtgui_theme_draw_selected(rtgui_dc_t *dc, rtgui_color_t *color, rtgui_rect_t *rect);

rtgui_color_t rtgui_theme_default_bc(void);//default black ground color
rtgui_color_t rtgui_theme_default_fc(void);
void rtgui_theme_draw_panel(rtgui_panel_t *panel);
void rtgui_theme_draw_combo(rtgui_combo_t *cbo);
void rtgui_theme_draw_combo_downarrow(rtgui_combo_t *cbo);

#ifdef __cplusplus
}
#endif

#endif
