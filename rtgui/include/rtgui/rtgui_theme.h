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

#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/iconbox.h>

#ifdef __cplusplus
extern "C" {
#endif

void rtgui_system_theme_init(void);

void rtgui_theme_draw_win(struct rtgui_topwin* win);
void rtgui_theme_draw_button(rtgui_button_t* btn);
void rtgui_theme_draw_label(rtgui_label_t* label);
void rtgui_theme_draw_textbox(rtgui_textbox_t* box);
void rtgui_theme_draw_iconbox(rtgui_iconbox_t* iconbox);

rt_uint16_t rtgui_theme_get_selected_height(void);
void rtgui_theme_draw_selected(struct rtgui_dc* dc, rtgui_rect_t *rect);

rtgui_color_t rtgui_theme_default_bc(void);
rtgui_color_t rtgui_theme_default_fc(void);

#ifdef __cplusplus
}
#endif

#endif
