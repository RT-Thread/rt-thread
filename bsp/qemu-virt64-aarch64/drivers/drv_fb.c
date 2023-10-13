/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2023-10-12     fangjianzhou     support sdl2
 */

#include <ioremap.h>
#include <lwp_user_mm.h>
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include <string.h>
#include <virtio_gpu.h>
#include "drivers/lcd.h"
#include <dfs_file.h>

#ifdef RT_USING_VIRTIO_GPU

static struct rt_device_graphic_info _graphic_info;
static struct rt_device_rect_info    _rect_info;
static struct rt_device              _fb      = {};

static rt_device_t                   _gpu_dev = RT_NULL;

static rt_err_t fb_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t fb_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t fb_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
        case FBIOPAN_DISPLAY:
        {
            rt_hw_cpu_dcache_clean(_graphic_info.framebuffer, _graphic_info.smem_len);
            rt_device_control(_gpu_dev, RTGRAPHIC_CTRL_RECT_UPDATE, &_rect_info);
            break;
        }
        case FBIOGET_FSCREENINFO:
        {
            struct fb_fix_screeninfo *info = (struct fb_fix_screeninfo *)args;
            strncpy(info->id, "lcd", sizeof(info->id));
            info->smem_len = _graphic_info.smem_len;
            break;
        }
        case FBIOGET_VSCREENINFO:
        {
            struct fb_var_screeninfo *info = (struct fb_var_screeninfo *)args;
            info->bits_per_pixel           = _graphic_info.bits_per_pixel;
            info->xres                     = _graphic_info.width;
            info->yres                     = _graphic_info.height;
            break;
        }
        case RT_FIOMMAP2:
        {
            struct dfs_mmap2_args *mmap2 = (struct dfs_mmap2_args *)args;

            if(mmap2)
            {
                mmap2->ret = lwp_map_user_phy(lwp_self(), RT_NULL, rt_kmem_v2p(_graphic_info.framebuffer), mmap2->length, 1);
            }
            else
            {
                return -EIO;
            }

            break;
        }
        default:
            break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops fb_ops =
{
    RT_NULL,
    fb_open,
    fb_close,
    RT_NULL,
    RT_NULL,
    fb_control
};
#endif
static int fb_init()
{
    _gpu_dev = rt_device_find("virtio-gpu0");
    RT_ASSERT(_gpu_dev);

    if(_gpu_dev != RT_NULL && rt_device_open(_gpu_dev, 0) == RT_EOK)
    {
        rt_memset(&_graphic_info, 0, sizeof(_graphic_info));
        rt_memset(&_rect_info, 0, sizeof(_rect_info));
        rt_device_control(_gpu_dev, VIRTIO_DEVICE_CTRL_GPU_SET_PRIMARY, RT_NULL);
        rt_device_control(_gpu_dev, VIRTIO_DEVICE_CTRL_GPU_CREATE_2D, (void *)RTGRAPHIC_PIXEL_FORMAT_RGB888);
        rt_device_control(_gpu_dev, RTGRAPHIC_CTRL_GET_INFO, &_graphic_info);
        _rect_info.x      = 0;
        _rect_info.y      = 0;
        _rect_info.width  = _graphic_info.width;
        _rect_info.height = _graphic_info.height;
        memset(_graphic_info.framebuffer, 0xff, _graphic_info.smem_len);
        rt_device_control(_gpu_dev, RTGRAPHIC_CTRL_RECT_UPDATE, &_rect_info);
    }

    RT_ASSERT(!rt_device_find("fb0"));
    _fb.type = RT_Device_Class_Miscellaneous;

#ifdef RT_USING_DEVICE_OPS
    _fb.ops  = &fb_ops;
#else
    _fb.init      = RT_NULL;
    _fb.open      = fb_open;
    _fb.close     = fb_close;
    _fb.read      = RT_NULL;
    _fb.write     = RT_NULL;
    _fb.control   = fb_control;
    _fb.user_data = RT_NULL;
#endif

    rt_device_register(&_fb, "fb0", RT_DEVICE_FLAG_RDWR);
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(fb_init);

#endif