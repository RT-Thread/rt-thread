/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
#ifdef RT_USING_SMART
#include <lwp.h>
#include <lwp_user_mm.h>
#endif
#include <board.h>

#include "drv_clcd.h"
#include "rt_lcd.h"

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

    (void)lcd; /* nothing, right now */
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
            info->bits_per_pixel= 16;
            info->width         = lcd->width;
            info->height        = lcd->height;
            info->framebuffer   = lcd->fb;
        }
        break;

    case FBIOGET_FSCREENINFO:
    {
#ifdef RT_USING_SMART
        struct fb_fix_screeninfo *info = (struct fb_fix_screeninfo *)args;
        strncpy(info->id, "lcd", sizeof(info->id));
        info->smem_len    = lcd->width * lcd->height * 2;
        info->smem_start  = (uint32_t)lwp_map_user_phy(lwp_self(), RT_NULL, lcd->fb,
            info->smem_len, 1);
        info->line_length = lcd->width * 2;
#endif
    }
        break;

    case FBIOGET_VSCREENINFO:
    {
        struct fb_var_screeninfo *info = (struct fb_var_screeninfo *)args;
        info->bits_per_pixel = 16;
        info->xres = lcd->width;
        info->yres = lcd->height;
    }
        break;

    case FBIOGET_DISPINFO:
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
    rt_kprintf("try to allocate fb... | w - %d, h - %d | ", _lcd.width, _lcd.height);
#ifdef RT_USING_SMART
    _lcd.fb = rt_pages_alloc(rt_page_bits(_lcd.width * _lcd.height * 2));
#else
    _lcd.fb = rt_malloc(_lcd.width * _lcd.height * 2);
#endif
    rt_kprintf("done!\n");
    rt_kprintf("fb => 0x%08x\n", _lcd.fb);
    if (_lcd.fb == NULL)
    {
        rt_kprintf("initialize frame buffer failed!\n");
        return -1;
    }
    memset(_lcd.fb, 0xff, _lcd.width * _lcd.height * 2);

    plio = (PL111MMIO*)PL111_IOBASE;
#ifdef RT_USING_SMART
    plio = (PL111MMIO *)rt_ioremap((void*)PL111_IOBASE, 0x1000);
#endif
    plio->tim0 = 0x3F1F3C00 | ((CLCD_WIDTH / 16 - 1) << 2);
    plio->tim1 = 0x080B6000 | (CLCD_HEIGHT - 1);

    plio->upbase = (uint32_t)_lcd.fb;
#ifdef RT_USING_SMART
    plio->upbase += PV_OFFSET;
#endif
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
