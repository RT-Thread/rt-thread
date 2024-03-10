/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "LPC177x_8x.h"
#include "lpc177x_8x_pinsel.h"

#include "drv_glcd.h"

#define RT_HW_LCD_WIDTH     480
#define RT_HW_LCD_HEIGHT    272

static struct rt_device_graphic_info _lcd_info;
static struct rt_device  lcd;

/* RT-Thread Device Interface */
static rt_err_t rt_lcd_init (rt_device_t dev)
{
    PINSEL_ConfigPin(5, 4, 0);
    LPC_GPIO5->DIR |= 1<<4;
    LPC_GPIO5->CLR  = 1<<4;
    LPC_GPIO5->SET  = 1<<4;

    /*Disable LCD controller*/
    GLCD_Ctrl (FALSE);
    /*Init LCD and copy picture in video RAM*/
    GLCD_Init (_lcd_info.framebuffer);
    /*Enable LCD*/
    GLCD_Ctrl (TRUE);

    return RT_EOK;
}

static rt_err_t rt_lcd_control (rt_device_t dev, int cmd, void *args)
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


/* LCD BL P5_4 */
void rt_hw_lcd_init(void)
{
    rt_uint16_t * _rt_framebuffer = RT_NULL;

    // _rt_framebuffer = rt_malloc_align(sizeof(rt_uint16_t)*RT_HW_LCD_HEIGHT*RT_HW_LCD_WIDTH, 8);
    // if (_rt_framebuffer == RT_NULL) return; /* no memory yet */

    _rt_framebuffer = (rt_uint16_t *)0xA0000000;

    _lcd_info.bits_per_pixel = 16;
    _lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    _lcd_info.framebuffer = (void*)_rt_framebuffer;
    _lcd_info.width = RT_HW_LCD_WIDTH;
    _lcd_info.height = RT_HW_LCD_HEIGHT;

    /* init device structure */
    lcd.type = RT_Device_Class_Graphic;
    lcd.init = rt_lcd_init;
    lcd.open = RT_NULL;
    lcd.close = RT_NULL;
    lcd.control = rt_lcd_control;
    lcd.user_data = (void*)&_lcd_info;

    /* register lcd device to RT-Thread */
    rt_device_register(&lcd, "lcd", RT_DEVICE_FLAG_RDWR);
}

void lcd_fill(uint8_t * start, uint8_t * end, uint8_t pixel)
{
    while(start<end)
    {
        *start++ = pixel;
    }
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(lcd_fill, lcd_fill  );
#endif
