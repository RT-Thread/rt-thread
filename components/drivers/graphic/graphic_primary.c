/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "graphic.primary"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_graphic_device *primary_gdev = RT_NULL;

#define framebuffer_drift(plane, x, y, bpp) \
    ((plane)->framebuffer + (x) * ((bpp) / 8) + (y) * (plane)->line_length)

#define fixup_dir(a1, a2) \
    if ((a1) > (a2)) { (a1) ^= (a2); (a2) ^= (a1); (a1) ^= (a2); }

static void graphic_primary_set_pixel_8bit(const char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint8_t *)framebuffer_drift(plane, x, y, 8) = *(rt_uint8_t *)pixel;
}

static void graphic_primary_get_pixel_8bit(char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint8_t *)pixel = *(rt_uint8_t *)framebuffer_drift(plane, x, y, 8);
}

static void graphic_primary_draw_hline_8bit(const char *pixel, int x1, int x2, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(x1, x2);
    rt_memset(framebuffer_drift(plane, x1, y, 8), *(rt_uint8_t *)pixel, x2 - x1);
}

static void graphic_primary_draw_vline_8bit(const char *pixel, int x, int y1, int y2)
{
    rt_uint8_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(y1, y2);
    fb = framebuffer_drift(plane, x, y1, 8);

    for (; y1 < y2; ++y1)
    {
        *fb = *(rt_uint8_t *)pixel;
        fb += plane->line_length;
    }
}

static void graphic_primary_blit_line_8bit(const char *pixel, int x, int y, rt_size_t size)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    rt_memcpy(framebuffer_drift(plane, x, y, 8), pixel, size);
}

static struct rt_device_graphic_ops graphic_primary_8bit_ops =
{
    .set_pixel = graphic_primary_set_pixel_8bit,
    .get_pixel = graphic_primary_get_pixel_8bit,
    .draw_hline = graphic_primary_draw_hline_8bit,
    .draw_vline = graphic_primary_draw_vline_8bit,
    .blit_line = graphic_primary_blit_line_8bit,
};

static void graphic_primary_set_pixel_16bit(const char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint16_t *)framebuffer_drift(plane, x, y, 16) = *(rt_uint16_t *)pixel;
}

static void graphic_primary_get_pixel_16bit(char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint16_t *)pixel = *(rt_uint16_t *)framebuffer_drift(plane, x, y, 16);
}

static void graphic_primary_draw_hline_16bit(const char *pixel, int x1, int x2, int y)
{
    rt_uint16_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(x1, x2);

    fb = framebuffer_drift(plane, x1, y, 16);

    for (; x1 < x2; ++x1)
    {
        *fb++ = *(rt_uint16_t *)pixel;
    }
}

static void graphic_primary_draw_vline_16bit(const char *pixel, int x, int y1, int y2)
{
    rt_uint16_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(y1, y2);

    fb = framebuffer_drift(plane, x, y1, 16);

    for (; y1 < y2; ++y1)
    {
        *fb = *(rt_uint16_t *)pixel;
        fb = (void *)fb + plane->line_length;
    }
}

static void graphic_primary_blit_line_16bit(const char *pixel, int x, int y, rt_size_t size)
{
    rt_uint16_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fb = framebuffer_drift(plane, x, y, 16);

    while (size --> 0)
    {
        *fb++ = *(rt_uint16_t *)pixel;
        pixel += 2;
    }
}

static struct rt_device_graphic_ops graphic_primary_16bit_ops =
{
    .set_pixel = graphic_primary_set_pixel_16bit,
    .get_pixel = graphic_primary_get_pixel_16bit,
    .draw_hline = graphic_primary_draw_hline_16bit,
    .draw_vline = graphic_primary_draw_vline_16bit,
    .blit_line = graphic_primary_blit_line_16bit,
};

static void graphic_primary_set_pixel_24bit(const char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    rt_memcpy(framebuffer_drift(plane, x, y, 24), pixel, 3);
}

static void graphic_primary_get_pixel_24bit(char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    rt_memcpy(pixel, framebuffer_drift(plane, x, y, 24), 3);
}

static void graphic_primary_draw_hline_24bit(const char *pixel, int x1, int x2, int y)
{
    rt_uint8_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(x1, x2);

    fb = framebuffer_drift(plane, x1, y, 24);

    for (; x1 < x2; ++x1)
    {
        *fb++ = ((rt_uint8_t *)pixel)[0];
        *fb++ = ((rt_uint8_t *)pixel)[1];
        *fb++ = ((rt_uint8_t *)pixel)[2];
    }
}

static void graphic_primary_draw_vline_24bit(const char *pixel, int x, int y1, int y2)
{
    rt_uint8_t *fb;
    rt_size_t xlate;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(y1, y2);

    fb = framebuffer_drift(plane, x, y1, 24);
    xlate = plane->line_length - 3;

    for (; y1 < y2; ++y1)
    {
        *fb++ = ((rt_uint8_t *)pixel)[0];
        *fb++ = ((rt_uint8_t *)pixel)[1];
        *fb++ = ((rt_uint8_t *)pixel)[2];

        fb = (void *)fb + xlate;
    }
}

static void graphic_primary_blit_line_24bit(const char *pixel, int x, int y, rt_size_t size)
{
    rt_uint8_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fb = framebuffer_drift(plane, x, y, 24);

    while (size --> 0)
    {
        *fb++ = *(rt_uint8_t *)pixel++;
        *fb++ = *(rt_uint8_t *)pixel++;
        *fb++ = *(rt_uint8_t *)pixel++;
    }
}

static struct rt_device_graphic_ops graphic_primary_24bit_ops =
{
    .set_pixel = graphic_primary_set_pixel_24bit,
    .get_pixel = graphic_primary_get_pixel_24bit,
    .draw_hline = graphic_primary_draw_hline_24bit,
    .draw_vline = graphic_primary_draw_vline_24bit,
    .blit_line = graphic_primary_blit_line_24bit,
};

static void graphic_primary_set_pixel_32bit(const char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint32_t *)framebuffer_drift(plane, x, y, 32) = *(rt_uint32_t *)pixel;
}

static void graphic_primary_get_pixel_32bit(char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint32_t *)pixel = *(rt_uint32_t *)framebuffer_drift(plane, x, y, 32);
}

static void graphic_primary_draw_hline_32bit(const char *pixel, int x1, int x2, int y)
{
    rt_uint32_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(x1, x2);

    fb = framebuffer_drift(plane, x1, y, 32);

    for (; x1 < x2; ++x1)
    {
        *fb++ = *(rt_uint32_t *)pixel;
    }
}

static void graphic_primary_draw_vline_32bit(const char *pixel, int x, int y1, int y2)
{
    rt_uint32_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(y1, y2);

    fb = framebuffer_drift(plane, x, y1, 32);

    for (; y1 < y2; ++y1)
    {
        *fb = *(rt_uint32_t *)pixel;
        fb = (void *)fb + plane->line_length;
    }
}

static void graphic_primary_blit_line_32bit(const char *pixel, int x, int y, rt_size_t size)
{
    rt_uint32_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fb = framebuffer_drift(plane, x, y, 32);

    while (size --> 0)
    {
        *fb++ = *(rt_uint32_t *)pixel;
        pixel += 4;
    }
}

static struct rt_device_graphic_ops graphic_primary_32bit_ops =
{
    .set_pixel = graphic_primary_set_pixel_32bit,
    .get_pixel = graphic_primary_get_pixel_32bit,
    .draw_hline = graphic_primary_draw_hline_32bit,
    .draw_vline = graphic_primary_draw_vline_32bit,
    .blit_line = graphic_primary_blit_line_32bit,
};

static void graphic_primary_set_pixel_64bit(const char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint64_t *)framebuffer_drift(plane, x, y, 64) = *(rt_uint64_t *)pixel;
}

static void graphic_primary_get_pixel_64bit(char *pixel, int x, int y)
{
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    *(rt_uint64_t *)pixel = *(rt_uint64_t *)framebuffer_drift(plane, x, y, 64);
}

static void graphic_primary_draw_hline_64bit(const char *pixel, int x1, int x2, int y)
{
    rt_uint64_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(x1, x2);

    fb = framebuffer_drift(plane, x1, y, 64);

    for (; x1 < x2; ++x1)
    {
        *fb++ = *(rt_uint64_t *)pixel;
    }
}

static void graphic_primary_draw_vline_64bit(const char *pixel, int x, int y1, int y2)
{
    rt_uint64_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fixup_dir(y1, y2);

    fb = framebuffer_drift(plane, x, y1, 64);

    for (; y1 < y2; ++y1)
    {
        *fb = *(rt_uint64_t *)pixel;
        fb = (void *)fb + plane->line_length;
    }
}

static void graphic_primary_blit_line_64bit(const char *pixel, int x, int y, rt_size_t size)
{
    rt_uint64_t *fb;
    struct rt_graphic_plane *plane = primary_gdev->primary_plane;

    fb = framebuffer_drift(plane, x, y, 64);

    while (size --> 0)
    {
        *fb++ = *(rt_uint64_t *)pixel;
        pixel += 8;
    }
}

static struct rt_device_graphic_ops graphic_primary_64bit_ops =
{
    .set_pixel = graphic_primary_set_pixel_64bit,
    .get_pixel = graphic_primary_get_pixel_64bit,
    .draw_hline = graphic_primary_draw_hline_64bit,
    .draw_vline = graphic_primary_draw_vline_64bit,
    .blit_line = graphic_primary_blit_line_64bit,
};

struct rt_device_graphic_ops *rt_graphic_device_switch_primary(struct rt_graphic_device *gdev)
{
    primary_gdev = gdev;

    RT_ASSERT(primary_gdev != RT_NULL);
    RT_ASSERT(primary_gdev->primary_plane != RT_NULL);

    switch (rt_graphic_mode_bpp(primary_gdev->primary_plane->mode))
    {
    case 32: return &graphic_primary_32bit_ops;
    case 24: return &graphic_primary_24bit_ops;
    case 16: return &graphic_primary_16bit_ops;
    case 64: return &graphic_primary_64bit_ops;
    case 8:  return &graphic_primary_8bit_ops;
    default:
        LOG_E("What the fuck format(%u)", primary_gdev->primary_plane->mode);
        RT_ASSERT(0);
        break;
    }

    return RT_NULL;
}
