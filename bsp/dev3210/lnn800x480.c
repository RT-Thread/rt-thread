/*
 * File      : lnn800x480.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2010 - 2012, RT-Thread Development Team
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
#include <soc3210.h>

/* LCD driver for 800x480 16bit */
#define RT_HW_LCD_WIDTH		800
#define RT_HW_LCD_HEIGHT	480

#define K1BASE				0xA0000000
#define KSEG1(addr)			((void *)(K1BASE | (rt_uint32_t)(addr)))
#define HW_FB_ADDR			KSEG1(_rt_framebuffer)
#define HW_FB_PIXEL(x, y)	*(volatile rt_uint16_t*)((rt_uint8_t*)HW_FB_ADDR + (y * RT_HW_LCD_WIDTH * 2) + x * 2)

ALIGN(4)
volatile rt_uint16_t _rt_framebuffer[RT_HW_LCD_HEIGHT][RT_HW_LCD_WIDTH];
static struct rt_device_graphic_info _lcd_info;

static rt_err_t rt_lcd_init (rt_device_t dev)
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

	return RT_EOK;
}

static rt_err_t rt_lcd_control (rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch (cmd)
	{
	case RTGRAPHIC_CTRL_RECT_UPDATE:
		break;
	case RTGRAPHIC_CTRL_POWERON:
		break;
	case RTGRAPHIC_CTRL_POWEROFF:
		break;
	case RTGRAPHIC_CTRL_GET_INFO:		
		rt_memcpy(args, &_lcd_info, sizeof(_lcd_info));
		break;
	case RTGRAPHIC_CTRL_SET_MODE:
		break;
	}

	return RT_EOK;
}

void rt_hw_lcd_init(void)
{
	rt_device_t lcd = rt_malloc(sizeof(struct rt_device));
	if (lcd == RT_NULL)
		return; /* no memory yet */

	_lcd_info.bits_per_pixel = 16;
	_lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
	_lcd_info.framebuffer = (rt_uint8_t*)HW_FB_ADDR;
	_lcd_info.width = RT_HW_LCD_WIDTH;
	_lcd_info.height = RT_HW_LCD_HEIGHT;

	/* init device structure */
	lcd->type = RT_Device_Class_Graphic;
	lcd->init = rt_lcd_init;
	lcd->open = RT_NULL;
	lcd->close = RT_NULL;
	lcd->control = rt_lcd_control;
	lcd->user_data = (void*)&_lcd_info;
	
	/* register lcd device to RT-Thread */
	rt_device_register(lcd, "lcd", RT_DEVICE_FLAG_RDWR);
}
