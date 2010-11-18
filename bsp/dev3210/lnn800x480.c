/*
 * File      : lcd_800480.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-01     bernard      first version from QiuYi's driver
 */

#include <rtthread.h>
#ifdef RT_USING_RTGUI
#include <soc3210.h>
#include <rtgui/driver.h>
#include <rtgui/color.h>

/* LCD driver for 800x480 16bit */
#define RT_HW_LCD_WIDTH		800
#define RT_HW_LCD_HEIGHT	480

ALIGN(4)
volatile rt_uint16_t _rt_framebuffer[RT_HW_LCD_HEIGHT][RT_HW_LCD_WIDTH];

#define K1BASE				0xA0000000
#define KSEG1(addr)			((void *)(K1BASE | (rt_uint32_t)(addr)))
#define HW_FB_ADDR			KSEG1(_rt_framebuffer)
#define HW_FB_PIXEL(x, y)	*(volatile rt_uint16_t*)((rt_uint8_t*)HW_FB_ADDR + (y * RT_HW_LCD_WIDTH * 2) + x * 2)

void rt_hw_lcd_update(rtgui_rect_t *rect)
{
}

rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
	return (rt_uint8_t *)HW_FB_ADDR;
}

void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    if (x < RT_HW_LCD_WIDTH && y < RT_HW_LCD_HEIGHT)
	{
		HW_FB_PIXEL(x, y) = rtgui_color_to_565p(*c);
	}
}

void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    if (x < RT_HW_LCD_WIDTH && y < RT_HW_LCD_HEIGHT)
	{
		*c = rtgui_color_from_565p(HW_FB_PIXEL(x, y));
	}

    return ;
}

void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint32_t idx;
	rt_uint16_t color;

	/* get color pixel */
	color = rtgui_color_to_565p(*c);

	for (idx = x1; idx < x2; idx ++)
	{
		HW_FB_PIXEL(idx, y) = color;
	}
}

void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2)
{
    rt_uint32_t idy;
	rt_uint16_t color;

	/* get color pixel */
	color = rtgui_color_to_565p(*c);

	for (idy = y1; idy < y2; idy ++)
	{
		HW_FB_PIXEL(x, idy) = color;
	}
}

void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint8_t* ptr;

	ptr = (rt_uint8_t*)&HW_FB_PIXEL(x1, y);
	rt_memcpy(ptr, pixels, (x2 - x1) * 2);
}

struct rtgui_graphic_driver _rtgui_lcd_driver =
{
	"lcd",
	2,
	RT_HW_LCD_WIDTH,
	RT_HW_LCD_HEIGHT,
	rt_hw_lcd_update,
	rt_hw_lcd_get_framebuffer,
	rt_hw_lcd_set_pixel,
	rt_hw_lcd_get_pixel,
	rt_hw_lcd_draw_hline,
	rt_hw_lcd_draw_vline,
	rt_hw_lcd_draw_raw_hline
};

#include "finsh.h"
void hline(rt_uint32_t c, int x1, int x2, int y)
{
    rtgui_color_t color = (rtgui_color_t)c;
    rt_hw_lcd_draw_hline(&color, x1, x2, y);
}
FINSH_FUNCTION_EXPORT(hline, draw a hline);

void vline(rt_uint32_t c, int x, int y1, int y2)
{
    rtgui_color_t color = (rtgui_color_t)c;
    rt_hw_lcd_draw_vline(&color, x, y1, y2);
}
FINSH_FUNCTION_EXPORT(vline, draw a vline);

void clear()
{
    int y;

    for (y = 0; y < _rtgui_lcd_driver.height; y ++)
    {
        rt_hw_lcd_draw_hline((rtgui_color_t*)&white, 0, 240, y);
    }
}
FINSH_FUNCTION_EXPORT(clear, clear screen);

void fill(rt_uint32_t c)
{
    int y;
	rtgui_color_t color = (rtgui_color_t)c;

    for (y = 0; y < _rtgui_lcd_driver.height; y ++)
    {
        rt_hw_lcd_draw_hline(&color, 0, _rtgui_lcd_driver.width, y);
    }
}
FINSH_FUNCTION_EXPORT(fill, fill screen with color);

void lcd_init()
{
	/* disable LCD controller */
	LCD_CTRL = LCD_CTRL & 0xfffe;

	/* set LCD clock */
	HSB_MISC_REG = (HSB_MISC_REG & 0xFFFD01FF) | 
		(0x01 << 17) | /* enable LCD */
		(0x05 << 9);    /* clock */

	LCD_VBARA = (rt_uint32_t)_rt_framebuffer - 0x80000000;
	LCD_VBARB = (rt_uint32_t)_rt_framebuffer - 0x80000000;

	LCD_HTIM  = 0x12c031f;
	LCD_VTIM  = 0x11501df;
	LCD_HVLEN = 0x41e0279;

	LCD_CTRL = 0x8709;

	rt_kprintf("VBARA 0x%08x\n", LCD_VBARA);
	rt_kprintf("CTRL 0x%08x\n", LCD_CTRL);
	rt_kprintf("HTIM 0x%08x\n", LCD_HTIM);
	rt_kprintf("VTIM 0x%08x\n", LCD_VTIM);
	rt_kprintf("HVLEN 0x%08x\n", LCD_HVLEN);
	rt_kprintf("HSB_MISC 0x%08x\n", HSB_MISC_REG);

	/* add lcd driver into graphic driver */
	rtgui_graphic_driver_add(&_rtgui_lcd_driver);
}
FINSH_FUNCTION_EXPORT(lcd_init, init lcd);

void rt_hw_lcd_init()
{
	lcd_init();
}
#endif
