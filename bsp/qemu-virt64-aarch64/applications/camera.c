/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-07     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <drv_camera.h>

/* Pixel format conversion - inlined for performance */
#define DO_CONV_RGB565(r, g, b, dst) \
    do { *((rt_uint16_t*)(dst)) = (((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3); } while(0)

#define DO_CONV_ARGB888(r, g, b, dst) \
    do { *((rt_uint32_t*)(dst)) = (0xFF << 24) | ((r) << 16) | ((g) << 8) | (b); } while(0)

#define DO_CONV_ABGR888(r, g, b, dst) \
    do { *((rt_uint32_t*)(dst)) = (0xFF << 24) | ((b) << 16) | ((g) << 8) | (r); } while(0)

/* Blend camera frame into framebuffer at specified position */
static void blend_camera_to_fb(rt_uint8_t *cam_fb, rt_uint8_t *fb,
                               int cam_w, int cam_h,
                               int fb_w, int fb_h, int fb_pitch,
                               int dst_x, int dst_y,
                               int pixel_format)
{
    int x, y;
    rt_uint8_t *dst, *src_row;
    /* Calculate actual draw region (clip to framebuffer bounds) */
    int draw_w = (dst_x + cam_w > fb_w) ? (fb_w - dst_x) : cam_w;
    int draw_h = (dst_y + cam_h > fb_h) ? (fb_h - dst_y) : cam_h;

    if (draw_w <= 0 || draw_h <= 0)
    {
        return;
    }

    /* Optimized conversion based on pixel format */
    switch (pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
    {
        rt_uint16_t *dst_pixel;
        for (y = 0; y < draw_h; ++y)
        {
            src_row = cam_fb + y * cam_w * 3;
            dst = fb + (dst_y + y) * fb_pitch + dst_x * 2;
            dst_pixel = (rt_uint16_t*)dst;

            for (x = 0; x < draw_w; ++x)
            {
                rt_uint8_t r = src_row[x * 3 + 0];
                rt_uint8_t g = src_row[x * 3 + 1];
                rt_uint8_t b = src_row[x * 3 + 2];
                DO_CONV_RGB565(r, g, b, dst_pixel + x);
            }
        }
        break;
    }

    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
    {
        rt_uint32_t *dst_pixel;
        for (y = 0; y < draw_h; ++y)
        {
            src_row = cam_fb + y * cam_w * 3;
            dst = fb + (dst_y + y) * fb_pitch + dst_x * 4;
            dst_pixel = (rt_uint32_t*)dst;

            for (x = 0; x < draw_w; ++x)
            {
                rt_uint8_t r = src_row[x * 3 + 0];
                rt_uint8_t g = src_row[x * 3 + 1];
                rt_uint8_t b = src_row[x * 3 + 2];
                DO_CONV_ARGB888(r, g, b, dst_pixel + x);
            }
        }
        break;
    }

    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
    {
        rt_uint32_t *dst_pixel;
        for (y = 0; y < draw_h; ++y)
        {
            src_row = cam_fb + y * cam_w * 3;
            dst = fb + (dst_y + y) * fb_pitch + dst_x * 4;
            dst_pixel = (rt_uint32_t*)dst;

            for (x = 0; x < draw_w; ++x)
            {
                rt_uint8_t r = src_row[x * 3 + 0];
                rt_uint8_t g = src_row[x * 3 + 1];
                rt_uint8_t b = src_row[x * 3 + 2];
                DO_CONV_ABGR888(r, g, b, dst_pixel + x);
            }
        }
        break;
    }

    default:
        /* Fallback: direct copy for RGB888 */
        for (y = 0; y < draw_h; ++y)
        {
            src_row = cam_fb + y * cam_w * 3;
            dst = fb + (dst_y + y) * fb_pitch + dst_x * 3;
            rt_memcpy(dst, src_row, draw_w * 3);
        }
        break;
    }
}

static int camera(int argc, char**argv)
{
    rt_err_t err;
    struct rt_device *cdev, *gdev;
    struct rt_device_graphic_info info;
    int cam_w, cam_h;
    void *cam_fb;
    int dst_x, dst_y;

    cdev = rt_device_find(argc > 1 ? argv[1] : "camera0");
    if (!cdev)
    {
        rt_kputs("Camera device not found\n");
        return -1;
    }

    gdev = rt_device_find(argc > 2 ? argv[2] : "fb0");
    if (!gdev)
    {
        rt_kputs("Framebuffer device not found\n");
        return -1;
    }

    if ((err = rt_device_open(cdev, 0)))
    {
        rt_kprintf("Open camera failed: %d\n", err);
        return (int)err;
    }

    if ((err = rt_device_open(gdev, 0)))
    {
        rt_kprintf("Open framebuffer failed: %d\n", err);
        goto _close_camera;
    }

    if ((err = rt_device_control(gdev, RTGRAPHIC_CTRL_GET_INFO, &info)))
    {
        rt_kprintf("Get framebuffer info failed: %d\n", err);
        goto _close_fb;
    }

    /* Get camera resolution */
    rt_device_control(cdev, RT_DEVICE_CTRL_CAMERA_GET_WIDTH, &cam_w);
    rt_device_control(cdev, RT_DEVICE_CTRL_CAMERA_GET_HEIGHT, &cam_h);

    /* Check pixel format support */
    if (info.pixel_format != RTGRAPHIC_PIXEL_FORMAT_RGB565 &&
        info.pixel_format != RTGRAPHIC_PIXEL_FORMAT_ARGB888 &&
        info.pixel_format != RTGRAPHIC_PIXEL_FORMAT_ABGR888 &&
        info.pixel_format != RTGRAPHIC_PIXEL_FORMAT_RGB888)
    {
        rt_kprintf("Unsupported pixel format: %d\n", info.pixel_format);
        goto _close_fb;
    }

    /* Get direct framebuffer access */
    rt_device_control(cdev, RT_DEVICE_CTRL_CAMERA_GET_FRAMEBUFFER, &cam_fb);

    /* Center camera on framebuffer */
    dst_x = (info.width - cam_w) / 2;
    dst_y = (info.height - cam_h) / 2;
    if (dst_x < 0) dst_x = 0;
    if (dst_y < 0) dst_y = 0;

    /* Main loop - read and display frames: ~10 seconds at 30 FPS */
    for (int frame_count = 0; frame_count < 300;)
    {
        /* Wait for new frame (short timeout for low latency) */
        if (rt_device_read(cdev, 0, RT_NULL, 0) > 0)
        {
            /* Blend camera into framebuffer */
            blend_camera_to_fb(cam_fb, info.framebuffer,
                               cam_w, cam_h,
                               info.width, info.height, info.pitch,
                               dst_x, dst_y,
                               info.pixel_format);
            ++frame_count;
        }
    }

_close_fb:
    rt_device_close(gdev);

_close_camera:
    rt_device_close(cdev);

    return err;
}
MSH_CMD_EXPORT(camera, camera show in framebuffer);
