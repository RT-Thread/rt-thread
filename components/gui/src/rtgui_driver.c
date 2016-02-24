/*
 * File      : driver.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#include <rtthread.h>
#include <rtgui/driver.h>
#include <rtgui/region.h>
#include <rtgui/rtgui_system.h>
#include <string.h>

extern const struct rtgui_graphic_driver_ops *rtgui_pixel_device_get_ops(int pixel_format);
extern const struct rtgui_graphic_driver_ops *rtgui_framebuffer_get_ops(int pixel_format);

static struct rtgui_graphic_driver _driver;
static struct rtgui_graphic_driver *_current_driver = &_driver;

#ifdef RTGUI_USING_VFRAMEBUFFER
#ifndef RTGUI_VFB_PIXEL_FMT
#define RTGUI_VFB_PIXEL_FMT     RTGRAPHIC_PIXEL_FORMAT_RGB565
#endif

#include <rtgui/dc.h>
static struct rtgui_graphic_driver _vfb_driver = {0};
static void _graphic_driver_vmode_init(void)
{
    if (_vfb_driver.width != _driver.width || _vfb_driver.height != _driver.height)
    {
        if (_vfb_driver.framebuffer != RT_NULL) rtgui_free((void*)_vfb_driver.framebuffer);

        _vfb_driver.device = RT_NULL;
        _vfb_driver.pixel_format = RTGUI_VFB_PIXEL_FMT;
        _vfb_driver.bits_per_pixel = rtgui_color_get_bits(RTGUI_VFB_PIXEL_FMT);
        _vfb_driver.width  = _driver.width;
        _vfb_driver.height = _driver.height;
        _vfb_driver.pitch  = _driver.width * _UI_BITBYTES(_vfb_driver.bits_per_pixel);
        _vfb_driver.framebuffer = rtgui_malloc(_vfb_driver.height * _vfb_driver.pitch);
        rt_memset(_vfb_driver.framebuffer, 0, _vfb_driver.height * _vfb_driver.pitch);
        _vfb_driver.ext_ops = RT_NULL;
        _vfb_driver.ops = rtgui_framebuffer_get_ops(_vfb_driver.pixel_format);
    }
}

void rtgui_graphic_driver_vmode_enter(void)
{
    rtgui_screen_lock(RT_WAITING_FOREVER);
    _current_driver = &_vfb_driver;
}
RTM_EXPORT(rtgui_graphic_driver_vmode_enter);

void rtgui_graphic_driver_vmode_exit(void)
{
    _current_driver = &_driver;
    rtgui_screen_unlock();
}
RTM_EXPORT(rtgui_graphic_driver_vmode_exit);

rt_bool_t rtgui_graphic_driver_is_vmode(void)
{
    if (_current_driver == &_vfb_driver)
        return RT_TRUE;

    return RT_FALSE;
}
RTM_EXPORT(rtgui_graphic_driver_is_vmode);

struct rtgui_dc*
rtgui_graphic_driver_get_rect_buffer(const struct rtgui_graphic_driver *driver,
                                     struct rtgui_rect *r)
{
    int w, h;
    struct rtgui_dc_buffer *buffer;
    rt_uint8_t *pixel, *dst;
    struct rtgui_rect src, rect;

    /* use virtual framebuffer in default */
    if (driver == RT_NULL) driver = _current_driver;

    if (r == RT_NULL)
    {
        rtgui_graphic_driver_get_rect(driver, &rect);
    }
    else
    {
        rtgui_graphic_driver_get_rect(driver, &src);
        rect = *r;
        rtgui_rect_intersect(&src, &rect);
    }

    w = rtgui_rect_width (rect);
    h = rtgui_rect_height(rect);
    if (!(w && h) || driver->framebuffer == RT_NULL)
        return RT_NULL;

    /* create buffer DC */
    buffer = (struct rtgui_dc_buffer*)rtgui_dc_buffer_create_pixformat(driver->pixel_format, w, h);
    if (buffer == RT_NULL)
        return (struct rtgui_dc*)buffer;

    /* get source pixel */
    pixel = (rt_uint8_t*)driver->framebuffer
        + rect.y1 * driver->pitch
        + rect.x1 * rtgui_color_get_bpp(driver->pixel_format);

    dst = buffer->pixel;

    while (h--)
    {
        rt_memcpy(dst, pixel, buffer->pitch);

        dst += buffer->pitch;
        pixel += driver->pitch;
    }

    return (struct rtgui_dc*)buffer;
}
RTM_EXPORT(rtgui_graphic_driver_get_rect_buffer);
#else
rt_bool_t rtgui_graphic_driver_is_vmode(void)
{
    return RT_FALSE;
}
RTM_EXPORT(rtgui_graphic_driver_is_vmode);
#endif

/* get default driver */
struct rtgui_graphic_driver *rtgui_graphic_driver_get_default(void)
{
    return _current_driver;
}
RTM_EXPORT(rtgui_graphic_driver_get_default);

void rtgui_graphic_driver_get_rect(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect)
{
    RT_ASSERT(rect != RT_NULL);

    /* use default driver */
    if (driver == RT_NULL)
        driver = _current_driver;

    rect->x1 = rect->y1 = 0;
    rect->x2 = driver->width;
    rect->y2 = driver->height;
}
RTM_EXPORT(rtgui_graphic_driver_get_rect);

rt_err_t rtgui_graphic_set_device(rt_device_t device)
{
    rt_err_t result;
    struct rt_device_graphic_info info;
    struct rtgui_graphic_ext_ops *ext_ops;

    /* get framebuffer address */
    result = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        /* get device information failed */
        return -RT_ERROR;
    }

    /* if the first set graphic device */
    if (_driver.width == 0 || _driver.height == 0)
    {
        rtgui_rect_t rect;

        rtgui_get_mainwin_rect(&rect);
        if (rect.x2 == 0 || rect.y2 == 0)
        {
            rtgui_rect_init(&rect, 0, 0, info.width, info.height);
            /* re-set main-window */
            rtgui_set_mainwin_rect(&rect);
        }
    }

    /* initialize framebuffer driver */
    _driver.device = device;
    _driver.pixel_format = info.pixel_format;
    _driver.bits_per_pixel = info.bits_per_pixel;
    _driver.width = info.width;
    _driver.height = info.height;
    _driver.pitch = _driver.width * _UI_BITBYTES(_driver.bits_per_pixel);
    _driver.framebuffer = info.framebuffer;

    /* get graphic extension operations */
    result = rt_device_control(device, RTGRAPHIC_CTRL_GET_EXT, &ext_ops);
    if (result == RT_EOK)
    {
        _driver.ext_ops = ext_ops;
    }

    if (info.framebuffer != RT_NULL)
    {
        /* is a frame buffer device */
        _driver.ops = rtgui_framebuffer_get_ops(_driver.pixel_format);
    }
    else
    {
        /* is a pixel device */
        _driver.ops = rtgui_pixel_device_get_ops(_driver.pixel_format);
    }

#ifdef RTGUI_USING_HW_CURSOR
    /* set default cursor image */
    rtgui_cursor_set_image(RTGUI_CURSOR_ARROW);
#endif

#ifdef RTGUI_USING_VFRAMEBUFFER
    _graphic_driver_vmode_init();
#endif

    return RT_EOK;
}
RTM_EXPORT(rtgui_graphic_set_device);

/* screen update */
void rtgui_graphic_driver_screen_update(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect)
{
    if (driver->device != RT_NULL)
    {
        struct rt_device_rect_info rect_info;

        rect_info.x = rect->x1;
        rect_info.y = rect->y1;
        rect_info.width = rect->x2 - rect->x1;
        rect_info.height = rect->y2 - rect->y1;
        rt_device_control(driver->device, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
    }
}
RTM_EXPORT(rtgui_graphic_driver_screen_update);

void rtgui_graphic_driver_set_framebuffer(void *fb)
{
    if (_current_driver)
        _current_driver->framebuffer = fb;
    else
        _driver.framebuffer = fb;
}

/* get video frame buffer */
rt_uint8_t *rtgui_graphic_driver_get_framebuffer(const struct rtgui_graphic_driver *driver)
{
    if (driver == RT_NULL) driver = _current_driver;

    return (rt_uint8_t *)driver->framebuffer;
}
RTM_EXPORT(rtgui_graphic_driver_get_framebuffer);

/*
 * FrameBuffer type driver
 */
#define GET_PIXEL(dst, x, y, type)  \
    (type *)((rt_uint8_t*)((dst)->framebuffer) + (y) * (dst)->pitch + (x) * _UI_BITBYTES((dst)->bits_per_pixel))

static void _rgb565_set_pixel(rtgui_color_t *c, int x, int y)
{
    *GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t) = rtgui_color_to_565(*c);
}

static void _rgb565_get_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint16_t pixel;

    pixel = *GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t);

    /* get pixel from color */
    *c = rtgui_color_from_565(pixel);
}

static void _rgb565_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_ubase_t index;
    rt_uint16_t pixel;
    rt_uint16_t *pixel_ptr;

    /* get pixel from color */
    pixel = rtgui_color_to_565(*c);

    /* get pixel pointer in framebuffer */
    pixel_ptr = GET_PIXEL(rtgui_graphic_get_device(), x1, y, rt_uint16_t);

    for (index = x1; index < x2; index ++)
    {
        *pixel_ptr = pixel;
        pixel_ptr ++;
    }
}

static void _rgb565_draw_vline(rtgui_color_t *c, int x , int y1, int y2)
{
    struct rtgui_graphic_driver *drv;
    rt_uint8_t *dst;
    rt_uint16_t pixel;
    rt_ubase_t index;

    drv = rtgui_graphic_get_device();
    pixel = rtgui_color_to_565(*c);
    dst = GET_PIXEL(drv, x, y1, rt_uint8_t);
    for (index = y1; index < y2; index ++)
    {
        *(rt_uint16_t *)dst = pixel;
        dst += drv->pitch;
    }
}

static void _rgb565p_set_pixel(rtgui_color_t *c, int x, int y)
{
    *GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t) = rtgui_color_to_565p(*c);
}

static void _rgb565p_get_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint16_t pixel;

    pixel = *GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t);

    /* get pixel from color */
    *c = rtgui_color_from_565p(pixel);
}

static void _rgb565p_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_ubase_t index;
    rt_uint16_t pixel;
    rt_uint16_t *pixel_ptr;

    /* get pixel from color */
    pixel = rtgui_color_to_565p(*c);

    /* get pixel pointer in framebuffer */
    pixel_ptr = GET_PIXEL(rtgui_graphic_get_device(), x1, y, rt_uint16_t);

    for (index = x1; index < x2; index ++)
    {
        *pixel_ptr = pixel;
        pixel_ptr ++;
    }
}

static void _rgb565p_draw_vline(rtgui_color_t *c, int x , int y1, int y2)
{
    struct rtgui_graphic_driver *drv;
    rt_uint8_t *dst;
    rt_uint16_t pixel;
    rt_ubase_t index;

    drv = rtgui_graphic_get_device();
    pixel = rtgui_color_to_565p(*c);
    dst = GET_PIXEL(drv, x, y1, rt_uint8_t);
    for (index = y1; index < y2; index ++)
    {
        *(rt_uint16_t *)dst = pixel;
        dst += drv->pitch;
    }
}

/* draw raw hline */
static void framebuffer_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
    struct rtgui_graphic_driver *drv;
    rt_uint8_t *dst;

    drv = rtgui_graphic_get_device();
    dst = GET_PIXEL(drv, x1, y, rt_uint8_t);
    rt_memcpy(dst, pixels,
              (x2 - x1) * _UI_BITBYTES(drv->bits_per_pixel));
}

const struct rtgui_graphic_driver_ops _framebuffer_rgb565_ops =
{
    _rgb565_set_pixel,
    _rgb565_get_pixel,
    _rgb565_draw_hline,
    _rgb565_draw_vline,
    framebuffer_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops _framebuffer_rgb565p_ops =
{
    _rgb565p_set_pixel,
    _rgb565p_get_pixel,
    _rgb565p_draw_hline,
    _rgb565p_draw_vline,
    framebuffer_draw_raw_hline,
};

#define FRAMEBUFFER (drv->framebuffer)
#define MONO_PIXEL(framebuffer, x, y) \
    ((rt_uint8_t**)(framebuffer))[y/8][x]

static void _mono_set_pixel(rtgui_color_t *c, int x, int y)
{
    struct rtgui_graphic_driver *drv = rtgui_graphic_get_device();

    if (*c == white)
        MONO_PIXEL(FRAMEBUFFER, x, y) &= ~(1 << (y % 8));
    else
        MONO_PIXEL(FRAMEBUFFER, x, y) |= (1 << (y % 8));
}

static void _mono_get_pixel(rtgui_color_t *c, int x, int y)
{
    struct rtgui_graphic_driver *drv = rtgui_graphic_get_device();

    if (MONO_PIXEL(FRAMEBUFFER, x, y) & (1 << (y % 8)))
        *c = black;
    else
        *c = white;
}

static void _mono_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    struct rtgui_graphic_driver *drv = rtgui_graphic_get_device();
    rt_ubase_t index;

    if (*c == white)
        for (index = x1; index < x2; index ++)
        {
            MONO_PIXEL(FRAMEBUFFER, index, y) &= ~(1 << (y % 8));
        }
    else
        for (index = x1; index < x2; index ++)
        {
            MONO_PIXEL(FRAMEBUFFER, index, y) |= (1 << (y % 8));
        }
}

static void _mono_draw_vline(rtgui_color_t *c, int x , int y1, int y2)
{
    struct rtgui_graphic_driver *drv = rtgui_graphic_get_device();
    rt_ubase_t index;

    if (*c == white)
        for (index = y1; index < y2; index ++)
        {
            MONO_PIXEL(FRAMEBUFFER, x, index) &= ~(1 << (index % 8));
        }
    else
        for (index = y1; index < y2; index ++)
        {
            MONO_PIXEL(FRAMEBUFFER, x, index) |= (1 << (index % 8));
        }
}

/* draw raw hline */
static void _mono_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
    struct rtgui_graphic_driver *drv = rtgui_graphic_get_device();
    rt_ubase_t index;

    for (index = x1; index < x2; index ++)
    {
        if (pixels[index / 8] && (1 << (index % 8)))
            MONO_PIXEL(FRAMEBUFFER, index, y) |= (1 << (y % 8));
        else
            MONO_PIXEL(FRAMEBUFFER, index, y) &= ~(1 << (y % 8));
    }
}

const struct rtgui_graphic_driver_ops _framebuffer_mono_ops =
{
    _mono_set_pixel,
    _mono_get_pixel,
    _mono_draw_hline,
    _mono_draw_vline,
    _mono_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops *rtgui_framebuffer_get_ops(int pixel_format)
{
    switch (pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_MONO:
        return &_framebuffer_mono_ops;
    case RTGRAPHIC_PIXEL_FORMAT_GRAY4:
        break;
    case RTGRAPHIC_PIXEL_FORMAT_GRAY16:
        break;
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        return &_framebuffer_rgb565_ops;
    case RTGRAPHIC_PIXEL_FORMAT_RGB565P:
        return &_framebuffer_rgb565p_ops;
    default:
        RT_ASSERT(0);
        break;
    }

    return RT_NULL;
}

/*
 * Pixel type driver
 */
#define gfx_device      (rtgui_graphic_get_device()->device)
#define gfx_device_ops  rt_graphix_ops(gfx_device)

static void _pixel_mono_set_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint8_t pixel;

    pixel = rtgui_color_to_mono(*c);
    gfx_device_ops->set_pixel((char *)&pixel, x, y);
}

static void _pixel_rgb565p_set_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint16_t pixel;

    pixel = rtgui_color_to_565p(*c);
    gfx_device_ops->set_pixel((char *)&pixel, x, y);
}

static void _pixel_rgb565_set_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint16_t pixel;

    pixel = rtgui_color_to_565(*c);
    gfx_device_ops->set_pixel((char *)&pixel, x, y);
}

static void _pixel_rgb888_set_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint32_t pixel;

    pixel = rtgui_color_to_888(*c);
    gfx_device_ops->set_pixel((char *)&pixel, x, y);
}

static void _pixel_mono_get_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint8_t pixel;

    gfx_device_ops->get_pixel((char *)&pixel, x, y);
    *c = rtgui_color_from_mono(pixel);
}

static void _pixel_rgb565p_get_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint16_t pixel;

    gfx_device_ops->get_pixel((char *)&pixel, x, y);
    *c = rtgui_color_from_565p(pixel);
}

static void _pixel_rgb565_get_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint16_t pixel;

    gfx_device_ops->get_pixel((char *)&pixel, x, y);
    *c = rtgui_color_from_565(pixel);
}

static void _pixel_rgb888_get_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint32_t pixel;

    gfx_device_ops->get_pixel((char *)&pixel, x, y);
    *c = rtgui_color_from_888(pixel);
}

static void _pixel_mono_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_uint8_t pixel;

    pixel = rtgui_color_to_mono(*c);
    gfx_device_ops->draw_hline((char *)&pixel, x1, x2, y);
}

static void _pixel_rgb565p_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_uint16_t pixel;

    pixel = rtgui_color_to_565p(*c);
    gfx_device_ops->draw_hline((char *)&pixel, x1, x2, y);
}

static void _pixel_rgb565_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_uint16_t pixel;

    pixel = rtgui_color_to_565(*c);
    gfx_device_ops->draw_hline((char *)&pixel, x1, x2, y);
}

static void _pixel_rgb888_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_uint32_t pixel;

    pixel = rtgui_color_to_888(*c);
    gfx_device_ops->draw_hline((char *)&pixel, x1, x2, y);
}

static void _pixel_mono_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
    rt_uint8_t pixel;

    pixel = rtgui_color_to_mono(*c);
    gfx_device_ops->draw_vline((char *)&pixel, x, y1, y2);
}

static void _pixel_rgb565p_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
    rt_uint16_t pixel;

    pixel = rtgui_color_to_565p(*c);
    gfx_device_ops->draw_vline((char *)&pixel, x, y1, y2);
}

static void _pixel_rgb565_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
    rt_uint16_t pixel;

    pixel = rtgui_color_to_565(*c);
    gfx_device_ops->draw_vline((char *)&pixel, x, y1, y2);
}

static void _pixel_rgb888_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
    rt_uint32_t pixel;

    pixel = rtgui_color_to_888(*c);
    gfx_device_ops->draw_vline((char *)&pixel, x, y1, y2);
}

static void _pixel_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
    if (x2 > x1)
        gfx_device_ops->blit_line((char *)pixels, x1, y, (x2 - x1));
    else
        gfx_device_ops->blit_line((char *)pixels, x2, y, (x1 - x2));
}

const struct rtgui_graphic_driver_ops _pixel_mono_ops =
{
    _pixel_mono_set_pixel,
    _pixel_mono_get_pixel,
    _pixel_mono_draw_hline,
    _pixel_mono_draw_vline,
    _pixel_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops _pixel_rgb565p_ops =
{
    _pixel_rgb565p_set_pixel,
    _pixel_rgb565p_get_pixel,
    _pixel_rgb565p_draw_hline,
    _pixel_rgb565p_draw_vline,
    _pixel_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops _pixel_rgb565_ops =
{
    _pixel_rgb565_set_pixel,
    _pixel_rgb565_get_pixel,
    _pixel_rgb565_draw_hline,
    _pixel_rgb565_draw_vline,
    _pixel_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops _pixel_rgb888_ops =
{
    _pixel_rgb888_set_pixel,
    _pixel_rgb888_get_pixel,
    _pixel_rgb888_draw_hline,
    _pixel_rgb888_draw_vline,
    _pixel_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops *rtgui_pixel_device_get_ops(int pixel_format)
{
    switch (pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_MONO:
        return &_pixel_mono_ops;

    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        return &_pixel_rgb565_ops;

    case RTGRAPHIC_PIXEL_FORMAT_RGB565P:
        return &_pixel_rgb565p_ops;

    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
        return &_pixel_rgb888_ops;
    }

    return RT_NULL;
}

/*
 * Hardware cursor
 */

#ifdef RTGUI_USING_HW_CURSOR
void rtgui_cursor_set_position(rt_uint16_t x, rt_uint16_t y)
{
    rt_uint32_t value;

    if (_current_driver->device != RT_NULL)
    {
        value = (x << 16 | y);
        rt_device_control(_driver.device, RT_DEVICE_CTRL_CURSOR_SET_POSITION, &value);
    }
}

void rtgui_cursor_set_image(enum rtgui_cursor_type type)
{
    rt_uint32_t value;

    if (_current_driver->device != RT_NULL)
    {
        value = type;
        rt_device_control(_driver.device, RT_DEVICE_CTRL_CURSOR_SET_TYPE, &value);
    }
};
#endif

