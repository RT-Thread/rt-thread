/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-24     spaceman          the first version
 */

#ifndef __DRV_LCD_SPI_H__
#define __DRV_LCD_SPI_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_DEVICE(dev)     (struct drv_lcd_device*)(dev)

struct drv_lcd_device
{
    struct rt_device parent;
    rt_device_t lcd_spi_dev;

    struct rt_device_graphic_info lcd_info;

    struct rt_semaphore lcd_lock;

    /* 0:front_buf is being used 1: back_buf is being used*/
    rt_uint8_t cur_buf;
    rt_uint8_t *front_buf;
    rt_uint8_t *back_buf;
};



void lcd_writebuff(uint16_t *databuff, uint16_t datasize);

void lcd_setaddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void lcd_clear(uint32_t color);
void lcd_clearrect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
void lcd_copybuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *databuff);

void lcd_drawpoint(uint16_t x, uint16_t y, uint32_t color);

void lcd_drawline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void lcd_drawline_v(uint16_t x, uint16_t y, uint16_t height, uint32_t color);
void lcd_drawline_h(uint16_t x, uint16_t y, uint16_t width, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_LCD_SPI_H__ */
