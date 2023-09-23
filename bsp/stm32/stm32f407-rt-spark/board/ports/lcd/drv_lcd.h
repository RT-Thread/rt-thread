/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-28     unknow       copy by STemwin
 */
#ifndef __DRV_LCD_H
#define __DRV_LCD_H
#include <rtthread.h>
#include "rtdevice.h"
#include <drv_common.h>
#ifdef PKG_USING_QRCODE
#include <qrcode.h>
#endif

#define LCD_BASE ((uint32_t)(0x68000000 | 0x0003FFFE)) // A18 link to DCX
#define LCD ((LCD_CONTROLLER_TypeDef *)LCD_BASE)
#define LCD_W 240
#define LCD_H 240

//LCD重要参数集
typedef struct
{
    uint16_t width;         //LCD 宽度
    uint16_t height;        //LCD 高度
    uint16_t id;            //LCD ID
    uint8_t  dir;           //横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t wramcmd;       //开始写gram指令
    uint16_t setxcmd;       //设置x坐标指令
    uint16_t setycmd;       //设置y坐标指令
}_lcd_dev;

//LCD参数
extern _lcd_dev lcddev; //管理LCD重要参数

typedef struct
{
  volatile uint8_t _u8_REG;
  volatile uint8_t RESERVED;
  volatile uint8_t _u8_RAM;
  volatile uint16_t _u16_RAM;
}LCD_CONTROLLER_TypeDef;


//POINT_COLOR
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN            0XBC40
#define BRRED            0XFC07
#define GRAY             0X8430
#define GRAY175          0XAD75
#define GRAY151          0X94B2
#define GRAY187          0XBDD7
#define GRAY240          0XF79E

//扫描方向定义
#define L2R_U2D  0      //从左到右,从上到下
#define L2R_D2U  1      //从左到右,从下到上
#define R2L_U2D  2      //从右到左,从上到下
#define R2L_D2U  3      //从右到左,从下到上

#define U2D_L2R  4      //从上到下,从左到右
#define U2D_R2L  5      //从上到下,从右到左
#define D2U_L2R  6      //从下到上,从左到右
#define D2U_R2L  7      //从下到上,从右到左

int drv_lcd_init(void);
void lcd_clear(rt_uint16_t color);
void lcd_address_set(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);
void lcd_set_color(rt_uint16_t back, rt_uint16_t fore);

rt_uint16_t change_byte_order(rt_uint16_t word);
void lcd_draw_point(rt_uint16_t x, rt_uint16_t y);
void lcd_draw_circle(rt_uint16_t x0, rt_uint16_t y0, rt_uint8_t r);
void lcd_draw_line(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);
void lcd_draw_rectangle(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);
void lcd_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint16_t color);

void lcd_address_set(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);
rt_err_t lcd_write_half_word(const rt_uint16_t da);
rt_err_t lcd_write_data_buffer(const void *send_buf, rt_size_t length);

void lcd_show_num(rt_uint16_t x, rt_uint16_t y, rt_uint32_t num, rt_uint8_t len, rt_uint32_t size);
rt_err_t lcd_show_string(rt_uint16_t x, rt_uint16_t y, rt_uint32_t size, const char *fmt, ...);
rt_err_t lcd_show_image(rt_uint16_t x, rt_uint16_t y, rt_uint16_t length, rt_uint16_t wide, const rt_uint8_t *p);
#ifdef PKG_USING_QRCODE
rt_err_t lcd_show_qrcode(rt_uint16_t x, rt_uint16_t y, rt_uint8_t version, rt_uint8_t ecc, const char *data, rt_uint8_t enlargement);
#endif

void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
void lcd_display_on(void);
void lcd_display_off(void);

void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor);

#endif
