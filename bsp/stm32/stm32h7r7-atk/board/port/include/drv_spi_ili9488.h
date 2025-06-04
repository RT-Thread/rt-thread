/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-08-14     flybreak          the first version
 * 2018-09-18     balanceTWK        add sleep mode function
 * 2022-02-01     Rudy Lo           add lcd_fill_array function
 */

#ifndef __DRV_LCD_SPI_H__
#define __DRV_LCD_SPI_H__

#include <rtthread.h>

#define LCD_W 480
#define LCD_H 320

//POINT_COLOR
#define WHITE            0xFFFFFF
#define BLACK            0x000000
#define BLUE             0x0000FF
//#define BRED             0XF81F
//#define GRED             0XFFE0
//#define GBLUE            0X07FF
#define RED              0xFF0000
//#define MAGENTA          0xF81F
#define GREEN            0x00FF00
//#define CYAN             0x7FFF
//#define YELLOW           0xFFE0
//#define BROWN            0XBC40
//#define BRRED            0XFC07
//#define GRAY             0X8430
//#define GRAY175          0XAD75
//#define GRAY151          0X94B2
//#define GRAY187          0XBDD7
//#define GRAY240          0XF79E

int rt_hw_spi_lcd_init(void);

void lcd_clear(rt_uint32_t color);
void lcd_address_set(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);
void lcd_set_color(rt_uint32_t back, rt_uint32_t fore);

void lcd_draw_point(rt_uint16_t x, rt_uint16_t y);
void lcd_draw_point_color(rt_uint16_t x, rt_uint16_t y, rt_uint32_t color);
void lcd_draw_circle(rt_uint16_t x0, rt_uint16_t y0, rt_uint8_t r);
void lcd_draw_line(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);
void lcd_draw_rectangle(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);
void lcd_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint32_t color);
void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor);

void lcd_show_num(rt_uint16_t x, rt_uint16_t y, rt_uint32_t num, rt_uint8_t len, rt_uint32_t size);
rt_err_t lcd_show_string(rt_uint16_t x, rt_uint16_t y, rt_uint32_t size, const char *fmt, ...);
rt_err_t lcd_show_image(rt_uint16_t x, rt_uint16_t y, rt_uint16_t length, rt_uint16_t wide, const rt_uint8_t *p);

void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
void lcd_display_on(void);
void lcd_display_off(void);

#endif /* __DRV_LCD_SPI_H__ */
