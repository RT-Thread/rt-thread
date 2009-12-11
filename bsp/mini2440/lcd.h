/*
 * File      : lcd.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-03-29     Yi.Qiu
 */
#ifndef __LCD_H__
#define __LCD_H__

#include <rtthread.h>

void rt_hw_lcd_init();
void rt_hw_lcd_draw_pixel(int x, int y, rt_uint32_t p);
void rt_hw_lcd_draw_hline(int x1, int x2, int y, rt_uint32_t p);
void rt_hw_lcd_draw_vline(int x, int y1, int y2, rt_uint32_t p);
void rt_hw_lcd_update();

#endif
