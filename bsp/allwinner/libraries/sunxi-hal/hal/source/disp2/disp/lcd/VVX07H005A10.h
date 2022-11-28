/*
 * =====================================================================================
 *
 *       Filename:  lcd_panel_cfg.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/27/2021 04:32:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef TFT7201280_H
#define TFT7201280_H

#include "panels.h"

extern struct __lcd_panel tft7201280_panel;

extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);

#endif  /*LCD_PANEL_CFG_H*/
