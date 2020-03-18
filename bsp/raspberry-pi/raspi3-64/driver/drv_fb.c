/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-08-29     zdzn           first version
 */

#include <rthw.h>
#include <stdint.h>
#include <rtthread.h>
#include "mbox.h"
#include "drv_fb.h"
#include "mmu.h"

#define LCD_WIDTH     (640)
#define LCD_HEIGHT    (480)
#define LCD_DEPTH     (32)

#define TAG_ALLOCATE_BUFFER         0x00040001
#define TAG_SET_PHYS_WIDTH_HEIGHT   0x00048003
#define TAG_SET_VIRT_WIDTH_HEIGHT   0x00048004
#define TAG_SET_DEPTH               0x00048005
#define TAG_SET_PIXEL_ORDER         0x00048006
#define TAG_GET_PITCH               0x00040008
#define TAG_SET_VIRT_OFFSET         0x00048009
#define TAG_END                     0x00000000

#define LCD_DEVICE(dev)    (struct rt_hdmi_fb_device*)(dev)

static struct rt_hdmi_fb_device _hdmi;

typedef rt_uint16_t color_t;

rt_err_t hdmi_fb_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

rt_err_t hdmi_fb_close(rt_device_t dev)
{
    return RT_EOK;
}

rt_size_t hdmi_fb_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
    return 0;
}

rt_size_t hdmi_fb_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return size;
}

rt_err_t hdmi_fb_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_hdmi_fb_device *lcd = LCD_DEVICE(dev);
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        {
            struct rt_device_rect_info *info = (struct rt_device_rect_info*)args;
            info = info;
        }
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        {
           struct rt_device_graphic_info* info = (struct rt_device_graphic_info*)args;

            RT_ASSERT(info != RT_NULL);
            info->pixel_format  = RTGRAPHIC_PIXEL_FORMAT_RGB888;
            info->bits_per_pixel= LCD_DEPTH;
            info->width         = lcd->width;
            info->height        = lcd->height;
            info->framebuffer   = lcd->fb;//(rt_uint8_t *)lcd->fb;
        }
        break;
    }
    return RT_EOK;
}

const static struct rt_device_ops hdmi_fb_ops = 
{
    RT_NULL,
    hdmi_fb_open,
    hdmi_fb_close,
    hdmi_fb_read,
    hdmi_fb_write,
    hdmi_fb_control
};

rt_err_t rt_hdmi_fb_device_init(struct rt_hdmi_fb_device *hdmi_fb, const char *name)
{
    struct rt_device *device;
    RT_ASSERT(hdmi_fb != RT_NULL);

    device = &hdmi_fb->parent;

    /* set device type */
    device->type = RT_Device_Class_Graphic;
    /* initialize device interface */
#ifdef RT_USING_DEVICE_OPS
    device->ops = &hdmi_fb_ops;
#else
    device->init = RT_NULL;
    device->open = hdmi_fb_open;
    device->close = hdmi_fb_close;
    device->read = hdmi_fb_read;
    device->write = hdmi_fb_write;
    device->control = hdmi_fb_control;
#endif

    /* register to device manager */
    rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}

int hdmi_fb_init(void)
{
    mbox[0] = 4 * 35;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = TAG_ALLOCATE_BUFFER;//get framebuffer, gets alignment on request
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 4096;   //FrameBufferInfo.pointer
    mbox[6] = 0;      //FrameBufferInfo.size

    mbox[7] = TAG_SET_PHYS_WIDTH_HEIGHT;
    mbox[8] = 8;
    mbox[9] = 0;
    mbox[10] = LCD_WIDTH;
    mbox[11] = LCD_HEIGHT;

    mbox[12] = TAG_SET_VIRT_WIDTH_HEIGHT;
    mbox[13] = 8;
    mbox[14] = 0;
    mbox[15] = LCD_WIDTH;
    mbox[16] = LCD_HEIGHT;

    mbox[17] = TAG_SET_DEPTH;
    mbox[18] = 4;
    mbox[19] = 0;
    mbox[20] = 16;    //FrameBufferInfo.depth RGB 565

    mbox[21] = TAG_SET_PIXEL_ORDER;
    mbox[22] = 4;
    mbox[23] = 0;
    mbox[24] = 1;     //RGB, not BGR preferably

    mbox[25] = TAG_GET_PITCH;
    mbox[26] = 4;
    mbox[27] = 0;
    mbox[28] = 0;

    mbox[29] = TAG_SET_VIRT_OFFSET;
    mbox[30] = 8;
    mbox[31] = 8;
    mbox[32] = 0;
    mbox[33] = 0;

    mbox[34] = TAG_END;

    mbox_call(MBOX_CH_PROP, MMU_DISABLE);

    _hdmi.fb = (rt_uint8_t *)(uintptr_t)(mbox[5] & 0x3FFFFFFF);

    _hdmi.width = LCD_WIDTH;
    _hdmi.height = LCD_HEIGHT;
    _hdmi.depth = LCD_DEPTH;
    _hdmi.pitch = 0;
    _hdmi.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB888;

    armv8_map((unsigned long)_hdmi.fb, (unsigned long)_hdmi.fb, 0x200000, MEM_ATTR_MEMORY);

    rt_kprintf("_hdmi.fb is %p\n", _hdmi.fb);
    rt_hdmi_fb_device_init(&_hdmi, "lcd");

    return 0;
}

INIT_DEVICE_EXPORT(hdmi_fb_init);
