/*
 * File      : lcd.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-03-29     Yi.Qiu
 */
#ifndef __LCD_H__
#define __LCD_H__

#include <rtthread.h>

void rt_hw_lcd_init();

#define RT_DEVICE_CTRL_LCD_GET_WIDTH				0
#define RT_DEVICE_CTRL_LCD_GET_HEIGHT			1
#define RT_DEVICE_CTRL_LCD_GET_BPP			 	2
#define RT_DEVICE_CTRL_LCD_GET_FRAMEBUFFER		3

#endif
