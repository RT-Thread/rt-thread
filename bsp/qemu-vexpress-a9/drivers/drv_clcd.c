/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <rtthread.h>
#include "drv_clcd.h"

#define CLCD_WIDTH  (BSP_LCD_WIDTH)
#define CLCD_HEIGHT (BSP_LCD_HEIGHT)

#define CLCD_DEVICE(dev)    (struct drv_clcd_device*)(dev)

#define PL111_CR_EN         0x001
#define PL111_CR_PWR        0x800
#define PL111_IOBASE        0x10020000
#define PL111_PALBASE       (PL111_IOBASE + 0x200)

typedef struct _PL111MMIO
{
    uint32_t      volatile tim0;      //0
    uint32_t      volatile tim1;      //4
    uint32_t      volatile tim2;      //8
    uint32_t      volatile tim3;      //c
    uint32_t      volatile upbase;    //10
    uint32_t      volatile f;         //14
    uint32_t      volatile control;   //18
    uint32_t      volatile g;         //1c
} PL111MMIO;

struct drv_clcd_device
{
    struct rt_device parent;

    int width;
    int height;

    uint8_t *fb;
};
struct drv_clcd_device _lcd;

static rt_err_t drv_clcd_init(struct rt_device *device)
{
    struct drv_clcd_device *lcd = CLCD_DEVICE(device);

    lcd = lcd; /* nothing, right now */
    return RT_EOK;
}

static rt_err_t drv_clcd_control(struct rt_device *device, int cmd, void *args)
{
    struct drv_clcd_device *lcd = CLCD_DEVICE(device);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        {
            struct rt_device_rect_info *info = (struct rt_device_rect_info*)args;

            info = info; /* nothing, right now */
        }
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        {
            struct rt_device_graphic_info* info = (struct rt_device_graphic_info*)args;

            RT_ASSERT(info != RT_NULL);
            info->pixel_format  = RTGRAPHIC_PIXEL_FORMAT_RGB565;
            // info->pixel_format  = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
            info->bits_per_pixel= 16;
            info->width         = lcd->width;
            info->height        = lcd->height;
            info->framebuffer   = lcd->fb;
        }
        break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops clcd_ops = 
{
    drv_clcd_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    drv_clcd_control
};
#endif

int drv_clcd_hw_init(void)
{
    PL111MMIO   *plio;
    struct rt_device *device = &_lcd.parent;

    /* memset _lcd to zero */
    memset(&_lcd, 0x0, sizeof(_lcd));

    _lcd.width  = CLCD_WIDTH;
    _lcd.height = CLCD_HEIGHT;
    _lcd.fb     = rt_malloc (_lcd.width * _lcd.height * 2);
    if (_lcd.fb == NULL)
    {
        rt_kprintf("initialize frame buffer failed!\n");
        return -1;
    }

    memset(_lcd.fb, 0xff, _lcd.width * _lcd.height * 2);

    plio = (PL111MMIO*)PL111_IOBASE;

    plio->tim0 = 0x3F1F3C00 | ((CLCD_WIDTH/16 - 1) << 2);
    plio->tim1 = 0x080B6000 | (CLCD_HEIGHT - 1);

    plio->upbase = (uint32_t)_lcd.fb;
    /* 16-bit 565 color */
    plio->control = 0x1921 | (0x6 << 1);

    device->type    = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &clcd_ops;
#else
    device->init    = drv_clcd_init;
    device->control = drv_clcd_control;
#endif

    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    return 0;
}
INIT_DEVICE_EXPORT(drv_clcd_hw_init);
