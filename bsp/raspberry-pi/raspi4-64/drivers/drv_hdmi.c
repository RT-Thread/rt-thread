/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-10-26     bigmagic       first version
 */

#include <stdint.h>
#include <rtthread.h>
#include <ioremap.h>

#if defined(BSP_USING_HDMI) && defined(RT_USING_SMART)
#include <lwp.h>
#include <lwp_user_mm.h>

#include <hypercall.h>

#include "mbox.h"
#include "drv_hdmi.h"

#define LCD_WIDTH     (800)
#define LCD_HEIGHT    (480)
#define LCD_DEPTH     (32)
#define LCD_BPP       (32)

#define TAG_ALLOCATE_BUFFER         0x00040001
#define TAG_SET_PHYS_WIDTH_HEIGHT   0x00048003
#define TAG_SET_VIRT_WIDTH_HEIGHT   0x00048004
#define TAG_SET_DEPTH               0x00048005
#define TAG_SET_PIXEL_ORDER         0x00048006
#define TAG_GET_PITCH               0x00040008
#define TAG_SET_VIRT_OFFSET         0x00048009
#define TAG_END                     0x00000000


enum {
    MBOX_TAG_FB_GET_GPIOVIRT        = 0x00040010,
    MBOX_TAG_FB_ALLOCATE_BUFFER     = 0x00040001,
    MBOX_TAG_FB_RELEASE_BUFFER      = 0x00048001,
    MBOX_TAG_FB_BLANK_SCREEN        = 0x00040002,
    MBOX_TAG_FB_GET_PHYS_WH         = 0x00040003,
    MBOX_TAG_FB_TEST_PHYS_WH        = 0x00044003,
    MBOX_TAG_FB_SET_PHYS_WH         = 0x00048003,
    MBOX_TAG_FB_GET_VIRT_WH         = 0x00040004,
    MBOX_TAG_FB_TEST_VIRT_WH        = 0x00044004,
    MBOX_TAG_FB_SET_VIRT_WH         = 0x00048004,
    MBOX_TAG_FB_GET_DEPTH           = 0x00040005,
    MBOX_TAG_FB_TEST_DEPTH          = 0x00044005,
    MBOX_TAG_FB_SET_DEPTH           = 0x00048005,
    MBOX_TAG_FB_GET_PIXEL_ORDER     = 0x00040006,
    MBOX_TAG_FB_TEST_PIXEL_ORDER    = 0x00044006,
    MBOX_TAG_FB_SET_PIXEL_ORDER     = 0x00048006,
    MBOX_TAG_FB_GET_ALPHA_MODE      = 0x00040007,
    MBOX_TAG_FB_TEST_ALPHA_MODE     = 0x00044007,
    MBOX_TAG_FB_SET_ALPHA_MODE      = 0x00048007,
    MBOX_TAG_FB_GET_PITCH           = 0x00040008,
    MBOX_TAG_FB_GET_VIRT_OFFSET     = 0x00040009,
    MBOX_TAG_FB_TEST_VIRT_OFFSET    = 0x00044009,
    MBOX_TAG_FB_SET_VIRT_OFFSET     = 0x00048009,
    MBOX_TAG_FB_GET_OVERSCAN        = 0x0004000a,
    MBOX_TAG_FB_TEST_OVERSCAN       = 0x0004400a,
    MBOX_TAG_FB_SET_OVERSCAN        = 0x0004800a,
    MBOX_TAG_FB_GET_PALETTE         = 0x0004000b,
    MBOX_TAG_FB_TEST_PALETTE        = 0x0004400b,
    MBOX_TAG_FB_SET_PALETTE         = 0x0004800b,
};

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

rt_ssize_t hdmi_fb_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
    return 0;
}

rt_ssize_t hdmi_fb_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return size;
}

rt_err_t hdmi_fb_control(rt_device_t dev, int cmd, void *args)
{
    static unsigned long smem_start = 0;
    static unsigned long smem_len = 0;
    struct rt_hdmi_fb_device *lcd = LCD_DEVICE(dev);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        {
            if (smem_start != 0)
            {
                rt_hw_cpu_dcache_clean_and_invalidate((void *)smem_start, smem_len);
            }
        }
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        {
            struct rt_device_graphic_info *lcd_info = (struct rt_device_graphic_info *)args;
            lcd_info->bits_per_pixel = 32;
            lcd_info->pixel_format = RTGRAPHIC_PIXEL_FORMAT_ARGB888; /* should be coherent to adding layers */
            lcd_info->width = lcd->width;
            lcd_info->height = lcd->height;
            lcd_info->framebuffer = (void *)lwp_map_user_phy(lwp_self(), RT_NULL, lcd->fb, lcd->width * lcd->height * sizeof(rt_uint32_t), 1);
        }
        break;
#define FBIOGET_FSCREENINFO 0x4602
    case FBIOGET_FSCREENINFO:
        {
            struct fb_fix_screeninfo
            {
                char id[16];
                unsigned long smem_start;
                uint32_t smem_len;

                uint32_t line_length;
            } *info = (struct fb_fix_screeninfo *)args;
            rt_strncpy(info->id, "lcd", sizeof(info->id));
            info->smem_len = lcd->width * lcd->height * sizeof(rt_uint32_t);
            info->smem_start = (size_t)lwp_map_user_phy(lwp_self(), RT_NULL, lcd->fb, info->smem_len, 1);
            info->line_length = lcd->width * sizeof(rt_uint32_t);
            rt_memset((void *)info->smem_start, 0, info->smem_len);
            smem_start = info->smem_start;
            smem_len = info->smem_len;
        }
        break;
    }
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops hdmi_fb_ops =
{
    RT_NULL,
    hdmi_fb_open,
    hdmi_fb_close,
    hdmi_fb_read,
    hdmi_fb_write,
    hdmi_fb_control,
};
#endif

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

rt_uint32_t bcm271x_mbox_fb_get_gpiovirt(void)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_FB_GET_GPIOVIRT;
    mbox[3] = 4;                        // buffer size
    mbox[4] = 0;                        // len

    mbox[5] = 0;                        // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);
    return (mbox[5] & 0x3fffffff);
}

rt_uint32_t bcm271x_mbox_fb_get_pitch(void)
{
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message

    mbox[2] = MBOX_TAG_FB_GET_PITCH;
    mbox[3] = 4;                    // buffer size
    mbox[4] = 0;                    // len

    mbox[5] = 0;                    // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);
    return mbox[5];
}

void bcm271x_mbox_fb_set_porder(int rgb)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_FB_SET_PIXEL_ORDER;
    mbox[3] = 4;                        // buffer size
    mbox[4] = 4;                        // len

    mbox[5] = rgb;                      // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);
}

void bcm271x_mbox_fb_setoffset(int xoffset, int yoffset)
{
    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_FB_SET_VIRT_OFFSET;
    mbox[3] = 8;                        // buffer size
    mbox[4] = 8;                        // len

    mbox[5] = xoffset;                  // id
    mbox[6] = yoffset;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);
}


void bcm271x_mbox_fb_setalpha(int alpha)
{

    mbox[0] = 8*4;                      // length of the message
    mbox[1] = MBOX_REQUEST;             // this is a request message

    mbox[2] = MBOX_TAG_FB_SET_ALPHA_MODE;
    mbox[3] = 4;                        // buffer size
    mbox[4] = 4;                        // len

    mbox[5] = alpha;                    // id
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    mbox_call(8, MMU_DISABLE);
}

void *bcm271x_mbox_fb_alloc(int width, int height, int bpp, int nrender)
{
    mbox[0] = 4 * 35;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = TAG_ALLOCATE_BUFFER;//get framebuffer, gets alignment on request
    mbox[3] = 8;                  //size
    mbox[4] = 4;                  //len
    mbox[5] = 4096;               //The design of MBOX driver forces us to give the virtual address 0x3C100000
    mbox[6] = 0;                  //FrameBufferInfo.size

    mbox[7] = TAG_SET_PHYS_WIDTH_HEIGHT;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = width;
    mbox[11] = height;

    mbox[12] = TAG_SET_VIRT_WIDTH_HEIGHT;
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = width;
    mbox[16] = height * nrender;

    mbox[17] = TAG_SET_DEPTH;
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = bpp;

    mbox[21] = TAG_SET_PIXEL_ORDER;
    mbox[22] = 4;
    mbox[23] = 0;
    mbox[24] = 0;                    //RGB, not BGR preferably

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

    mbox_call(8, MMU_DISABLE);
    return (void *)((size_t)(mbox[5] & 0x3fffffff));
}

int hdmi_fb_init(void)
{
    _hdmi.fb = (rt_uint8_t *)bcm271x_mbox_fb_alloc(LCD_WIDTH, LCD_HEIGHT, LCD_BPP, 1);

    if (_hdmi.fb == RT_NULL)
    {
        rt_kprintf("init hdmi fb err!\n");
        return -RT_ERROR;
    }

#ifdef BSP_USING_VM_MODE
    if (rt_hv_stage2_map((unsigned long)_hdmi.fb, 0x1400000))
    {
        rt_kprintf("alloc mmio from hyper fail!\n");
        return -RT_ERROR;
    }
#endif

    bcm271x_mbox_fb_setoffset(0, 0);
    bcm271x_mbox_fb_set_porder(0);
    _hdmi.width = LCD_WIDTH;
    _hdmi.height = LCD_HEIGHT;
    _hdmi.depth = LCD_DEPTH;
    _hdmi.pitch = 0;
    _hdmi.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB888;

    //rt_kprintf("_hdmi.fb is %p\n", _hdmi.fb);
    rt_hdmi_fb_device_init(&_hdmi, "lcd");

    return 0;
}

INIT_DEVICE_EXPORT(hdmi_fb_init);
#endif /*BSP_USING_HDMI */
