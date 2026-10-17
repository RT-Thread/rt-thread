/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_FINSH) && defined(RT_USING_GRAPHIC) && \
        defined(RT_SOC_SUNXI_G2D)

#include <finsh.h>
#include <stdlib.h>

#include <sunxi-g2d.h>

#define F101_G2D_PATTERN_WIDTH       96U
#define F101_G2D_PATTERN_HEIGHT      64U
#define F101_G2D_TEST_MARGIN          12U
#define F101_G2D_SCALE_NUMERATOR      3U
#define F101_G2D_SCALE_DENOMINATOR    2U
#define F101_G2D_ANIM_DEFAULT_FRAMES 180U
#define F101_G2D_ANIM_MAX_FRAMES     3600U

struct f101_g2d_format
{
    enum sunxi_g2d_format format;
    rt_uint8_t bytes_per_pixel;
    const char *name;
};

static rt_err_t f101_g2d_format_from_info(
        const struct rt_device_graphic_info *info,
        struct f101_g2d_format *format)
{
    switch (info->pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        format->format = SUNXI_G2D_FORMAT_RGB565;
        format->bytes_per_pixel = 2;
        format->name = "RGB565";
        return RT_EOK;

    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        format->format = SUNXI_G2D_FORMAT_ARGB8888;
        format->bytes_per_pixel = 4;
        format->name = "ARGB8888";
        return RT_EOK;

    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        format->format = SUNXI_G2D_FORMAT_ABGR8888;
        format->bytes_per_pixel = 4;
        format->name = "ABGR8888";
        return RT_EOK;

    default:
        return -RT_ENOSYS;
    }
}

static rt_uint32_t f101_g2d_pixel(const struct f101_g2d_format *format,
        rt_uint8_t red, rt_uint8_t green, rt_uint8_t blue)
{
    if (format->format == SUNXI_G2D_FORMAT_RGB565)
    {
        return ((rt_uint16_t)(red & 0xf8) << 8) |
                ((rt_uint16_t)(green & 0xfc) << 3) | (blue >> 3);
    }
    if (format->format == SUNXI_G2D_FORMAT_ABGR8888)
    {
        return 0xff000000U | ((rt_uint32_t)blue << 16) |
                ((rt_uint32_t)green << 8) | red;
    }

    return 0xff000000U | ((rt_uint32_t)red << 16) |
            ((rt_uint32_t)green << 8) | blue;
}

static void f101_g2d_make_pattern(void *buffer,
        const struct f101_g2d_format *format, rt_uint16_t width,
        rt_uint16_t height)
{
    rt_uint16_t x;
    rt_uint16_t y;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            rt_uint8_t red = x * 255U / width;
            rt_uint8_t green = y * 255U / height;
            rt_uint8_t blue = (x + y) * 127U / (width + height);

            if (x < width / 5U && y < height / 4U)
            {
                red = 255;
                green = 32;
                blue = 32;
            }
            else if (x >= width * 4U / 5U && y < height / 4U)
            {
                red = 32;
                green = 255;
                blue = 32;
            }
            else if (x < width / 5U && y >= height * 3U / 4U)
            {
                red = 32;
                green = 64;
                blue = 255;
            }
            else if (x >= width * 4U / 5U && y >= height * 3U / 4U)
            {
                red = 255;
                green = 255;
                blue = 255;
            }

            if (x > width / 3U && x < width / 3U + 4U)
            {
                red = 255;
                green = 255;
                blue = 0;
            }
            if (format->bytes_per_pixel == 2)
            {
                ((rt_uint16_t *)buffer)[(rt_size_t)y * width + x] =
                        f101_g2d_pixel(format, red, green, blue);
            }
            else
            {
                ((rt_uint32_t *)buffer)[(rt_size_t)y * width + x] =
                        f101_g2d_pixel(format, red, green, blue);
            }
        }
    }
}

static rt_uint32_t f101_g2d_triangle(rt_uint32_t frame, rt_uint32_t period,
        rt_uint32_t amplitude)
{
    rt_uint32_t half = period / 2U;
    rt_uint32_t phase = frame % period;

    if (phase > half)
    {
        phase = period - phase;
    }

    return half ? (rt_uint64_t)amplitude * phase / half : 0;
}

static rt_err_t f101_g2d_parse_frames(const char *text, rt_uint32_t *frames)
{
    char *end;
    unsigned long value = strtoul(text, &end, 0);

    if (!text[0] || *end || !value || value > F101_G2D_ANIM_MAX_FRAMES)
    {
        return -RT_EINVAL;
    }

    *frames = value;
    return RT_EOK;
}

static rt_err_t f101_g2d_present(rt_device_t framebuffer,
        const struct rt_device_graphic_info *info,
        const struct sunxi_g2d_buffer *canvas)
{
    struct rt_device_rect_info rect =
    {
        .x = 0,
        .y = 0,
        .width = info->width,
        .height = info->height,
    };

    /*
     * Keep G2D rendering off-screen. The ST77916 framebuffer driver waits for
     * TE from its RECT_UPDATE path, immediately before sending this completed
     * buffer to panel GRAM. Calling WAIT_VSYNC here would consume one TE edge
     * and make the driver wait for the following frame instead.
     */
    rt_memcpy(info->framebuffer, canvas->virt_addr, canvas->size);
    return rt_device_control(framebuffer, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
}

static rt_err_t f101_g2d_prepare(rt_device_t *g2d, rt_device_t *framebuffer,
        struct rt_device_graphic_info *info, int argc, char **argv,
        int maximum_arguments, struct f101_g2d_format *format)
{
    const char *g2d_name = argc > 1 ? argv[1] : "g2d0";
    const char *fb_name = argc > 2 ? argv[2] : "fb0";
    rt_err_t err;

    if (argc > maximum_arguments)
    {
        return -RT_EINVAL;
    }

    *g2d = rt_device_find(g2d_name);
    *framebuffer = rt_device_find(fb_name);
    if (!*g2d || !*framebuffer)
    {
        rt_kprintf("device not found: %s or %s\n", g2d_name, fb_name);
        return -RT_ENOSYS;
    }

    err = rt_device_open(*framebuffer, RT_DEVICE_OFLAG_RDWR);
    if (err)
    {
        return err;
    }
    err = rt_device_control(*framebuffer, RTGRAPHIC_CTRL_GET_INFO, info);
    if (err)
    {
        rt_device_close(*framebuffer);
        return err;
    }
    err = f101_g2d_format_from_info(info, format);
    if (err || !info->framebuffer ||
        info->bits_per_pixel != format->bytes_per_pixel * 8U ||
        info->pitch < (rt_uint32_t)info->width * format->bytes_per_pixel)
    {
        rt_kprintf("G2D test requires an RGB565, ARGB8888, or ABGR8888 framebuffer\n");
        rt_device_close(*framebuffer);
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t f101_g2d_allocate_canvas(rt_device_t g2d,
        const struct rt_device_graphic_info *info,
        const struct f101_g2d_format *format, struct sunxi_g2d_buffer *canvas,
        struct sunxi_g2d_image *image)
{
    rt_err_t err;

    canvas->size = (rt_size_t)info->pitch * info->height;
    err = rt_device_control(g2d, SUNXI_G2D_CMD_ALLOC_BUFFER, canvas);
    if (err)
    {
        return err;
    }

    image->buffer = canvas;
    image->width = info->width;
    image->height = info->height;
    image->pitch = info->pitch;
    image->format = format->format;
    return RT_EOK;
}

static rt_err_t f101_g2d_fill(rt_device_t g2d,
        struct sunxi_g2d_image *image, rt_uint16_t x, rt_uint16_t y,
        rt_uint16_t width, rt_uint16_t height, rt_uint32_t color)
{
    struct sunxi_g2d_fill request =
    {
        .destination = image,
        .rect = { x, y, width, height },
        .color = color,
        .timeout = rt_tick_from_millisecond(100),
    };

    return rt_device_control(g2d, SUNXI_G2D_CMD_FILL, &request);
}

static rt_err_t f101_g2d_blit(rt_device_t g2d,
        struct sunxi_g2d_image *source, struct sunxi_g2d_image *destination,
        rt_uint16_t destination_x, rt_uint16_t destination_y)
{
    struct sunxi_g2d_blit request =
    {
        .source = source,
        .source_rect = { 0, 0, source->width, source->height },
        .destination = destination,
        .destination_rect =
            { destination_x, destination_y, source->width, source->height },
        .timeout = rt_tick_from_millisecond(100),
    };

    return rt_device_control(g2d, SUNXI_G2D_CMD_BLIT, &request);
}

static void f101_g2d_image_to_surface(const struct sunxi_g2d_image *image,
        struct sunxi_g2d_surface *surface)
{
    rt_memset(surface, 0, sizeof(*surface));
    surface->format = image->format;
    surface->width = image->width;
    surface->height = image->height;
    surface->plane[0].buffer = image->buffer;
    surface->plane[0].pitch = image->pitch;
}

static rt_err_t f101_g2d_compose_blit(rt_device_t g2d,
        const struct sunxi_g2d_image *source,
        const struct sunxi_g2d_rect *source_rect,
        const struct sunxi_g2d_image *destination,
        const struct sunxi_g2d_rect *destination_rect,
        enum sunxi_g2d_rotation rotation)
{
    struct sunxi_g2d_operation operation;

    rt_memset(&operation, 0, sizeof(operation));
    operation.type = SUNXI_G2D_OPERATION_BLIT;
    operation.source_rect = *source_rect;
    operation.destination_rect = *destination_rect;
    operation.rotation = rotation;
    operation.timeout = rt_tick_from_millisecond(100);
    f101_g2d_image_to_surface(source, &operation.source);
    f101_g2d_image_to_surface(destination, &operation.destination);

    return rt_device_control(g2d, SUNXI_G2D_CMD_COMPOSE, &operation);
}

static rt_err_t f101_g2d_compose_blend(rt_device_t g2d,
        const struct sunxi_g2d_image *foreground,
        const struct sunxi_g2d_rect *foreground_rect,
        const struct sunxi_g2d_image *background,
        const struct sunxi_g2d_rect *background_rect,
        const struct sunxi_g2d_image *destination,
        const struct sunxi_g2d_rect *destination_rect)
{
    struct sunxi_g2d_operation operation;

    rt_memset(&operation, 0, sizeof(operation));
    operation.type = SUNXI_G2D_OPERATION_BLEND;
    operation.source_rect = *foreground_rect;
    operation.background_rect = *background_rect;
    operation.destination_rect = *destination_rect;
    operation.blend.mode = SUNXI_G2D_BLEND_SRC_OVER;
    operation.blend.foreground_alpha_mode = SUNXI_G2D_ALPHA_GLOBAL;
    operation.blend.foreground_alpha = 160;
    operation.blend.background_alpha_mode = SUNXI_G2D_ALPHA_PIXEL;
    operation.blend.background_alpha = 255;
    operation.timeout = rt_tick_from_millisecond(100);
    f101_g2d_image_to_surface(foreground, &operation.source);
    f101_g2d_image_to_surface(background, &operation.background);
    f101_g2d_image_to_surface(destination, &operation.destination);

    return rt_device_control(g2d, SUNXI_G2D_CMD_COMPOSE, &operation);
}

static int g2d_test(int argc, char **argv)
{
    rt_device_t g2d;
    rt_device_t framebuffer;
    struct rt_device_graphic_info info;
    struct sunxi_g2d_buffer canvas = { 0 };
    struct sunxi_g2d_buffer pattern = { 0 };
    struct sunxi_g2d_buffer background = { 0 };
    struct sunxi_g2d_image canvas_image = { 0 };
    struct sunxi_g2d_image pattern_image = { 0 };
    struct sunxi_g2d_image background_image = { 0 };
    struct sunxi_g2d_rect pattern_rect;
    struct sunxi_g2d_rect scale_rect;
    struct sunxi_g2d_rect rotate_rect;
    struct sunxi_g2d_rect blend_rect;
    struct f101_g2d_format format;
    rt_uint32_t version;
    rt_err_t err;

    err = f101_g2d_prepare(&g2d, &framebuffer, &info, argc, argv, 3, &format);
    if (err)
    {
        rt_kprintf("usage: g2d_test [g2d] [fb]\n");
        return err;
    }
    if (info.width < 2U * F101_G2D_TEST_MARGIN +
            F101_G2D_PATTERN_WIDTH * F101_G2D_SCALE_NUMERATOR /
            F101_G2D_SCALE_DENOMINATOR ||
        info.height < F101_G2D_TEST_MARGIN * 2U +
            F101_G2D_PATTERN_HEIGHT * F101_G2D_SCALE_NUMERATOR /
            F101_G2D_SCALE_DENOMINATOR * 2U)
    {
        rt_kprintf("G2D test requires a framebuffer of at least 168x216\n");
        err = -RT_EINVAL;
        goto _out;
    }

    err = f101_g2d_allocate_canvas(g2d, &info, &format, &canvas, &canvas_image);
    if (err)
    {
        goto _out;
    }
    pattern.size = F101_G2D_PATTERN_WIDTH * F101_G2D_PATTERN_HEIGHT *
            format.bytes_per_pixel;
    err = rt_device_control(g2d, SUNXI_G2D_CMD_ALLOC_BUFFER, &pattern);
    if (err)
    {
        goto _out;
    }
    pattern_image.buffer = &pattern;
    pattern_image.width = F101_G2D_PATTERN_WIDTH;
    pattern_image.height = F101_G2D_PATTERN_HEIGHT;
    pattern_image.pitch = F101_G2D_PATTERN_WIDTH * format.bytes_per_pixel;
    pattern_image.format = format.format;
    f101_g2d_make_pattern(pattern.virt_addr, &format, pattern_image.width,
            pattern_image.height);

    err = f101_g2d_allocate_canvas(g2d, &info, &format, &background,
            &background_image);
    if (err)
    {
        goto _out;
    }

    pattern_rect = (struct sunxi_g2d_rect)
    {
        0, 0, pattern_image.width, pattern_image.height
    };
    scale_rect = (struct sunxi_g2d_rect)
    {
        info.width - F101_G2D_TEST_MARGIN -
                pattern_image.width * F101_G2D_SCALE_NUMERATOR /
                F101_G2D_SCALE_DENOMINATOR,
        F101_G2D_TEST_MARGIN,
        pattern_image.width * F101_G2D_SCALE_NUMERATOR /
                F101_G2D_SCALE_DENOMINATOR,
        pattern_image.height * F101_G2D_SCALE_NUMERATOR /
                F101_G2D_SCALE_DENOMINATOR,
    };
    rotate_rect = (struct sunxi_g2d_rect)
    {
        F101_G2D_TEST_MARGIN,
        F101_G2D_TEST_MARGIN + pattern_image.height + F101_G2D_TEST_MARGIN,
        pattern_image.height,
        pattern_image.width,
    };
    blend_rect = (struct sunxi_g2d_rect)
    {
        scale_rect.x,
        scale_rect.y + scale_rect.height + F101_G2D_TEST_MARGIN,
        scale_rect.width,
        scale_rect.height,
    };

    err = f101_g2d_fill(g2d, &canvas_image, 0, 0, info.width, info.height,
            0xff182028U);
    if (err)
    {
        goto _out;
    }
    err = f101_g2d_blit(g2d, &pattern_image, &canvas_image,
            F101_G2D_TEST_MARGIN, F101_G2D_TEST_MARGIN);
    if (err)
    {
        goto _out;
    }
    err = f101_g2d_compose_blit(g2d, &pattern_image, &pattern_rect,
            &canvas_image, &scale_rect, SUNXI_G2D_ROTATE_0);
    if (err)
    {
        goto _out;
    }
    err = f101_g2d_compose_blit(g2d, &pattern_image, &pattern_rect,
            &canvas_image, &rotate_rect, SUNXI_G2D_ROTATE_90);
    if (err)
    {
        goto _out;
    }
    err = f101_g2d_fill(g2d, &background_image, 0, 0, info.width,
            info.height, 0xff203060U);
    if (err)
    {
        goto _out;
    }
    err = f101_g2d_compose_blend(g2d, &pattern_image, &pattern_rect,
            &background_image, &blend_rect, &canvas_image, &blend_rect);
    if (err)
    {
        goto _out;
    }
    err = f101_g2d_present(framebuffer, &info, &canvas);
    if (err)
    {
        goto _out;
    }
    rt_device_control(g2d, SUNXI_G2D_CMD_GET_VERSION, &version);
    rt_kprintf("G2D %08x completed fill, BitBlt, scale, rotate and blend test\n",
            version);

_out:
    if (err)
    {
        rt_kprintf("G2D test failed: %d\n", err);
    }
    if (pattern.virt_addr)
    {
        rt_device_control(g2d, SUNXI_G2D_CMD_FREE_BUFFER, &pattern);
    }
    if (canvas.virt_addr)
    {
        rt_device_control(g2d, SUNXI_G2D_CMD_FREE_BUFFER, &canvas);
    }
    if (background.virt_addr)
    {
        rt_device_control(g2d, SUNXI_G2D_CMD_FREE_BUFFER, &background);
    }
    rt_device_close(framebuffer);
    return err;
}
MSH_CMD_EXPORT(g2d_test, run F101 G2D fill BitBlt scale rotate blend test);

static int g2d_anim(int argc, char **argv)
{
    rt_device_t g2d;
    rt_device_t framebuffer;
    struct rt_device_graphic_info info;
    struct sunxi_g2d_buffer canvas = { 0 };
    struct sunxi_g2d_buffer pattern = { 0 };
    struct sunxi_g2d_image canvas_image = { 0 };
    struct sunxi_g2d_image pattern_image = { 0 };
    struct f101_g2d_format format;
    rt_uint32_t frames = F101_G2D_ANIM_DEFAULT_FRAMES;
    rt_tick_t started;
    rt_tick_t elapsed;
    rt_uint32_t frame;
    rt_err_t err;

    if (argc > 4 || (argc == 4 &&
        f101_g2d_parse_frames(argv[3], &frames) != RT_EOK))
    {
        rt_kprintf("usage: g2d_anim [g2d] [fb] [frames: 1-%u]\n",
                F101_G2D_ANIM_MAX_FRAMES);
        return -RT_EINVAL;
    }
    err = f101_g2d_prepare(&g2d, &framebuffer, &info, argc, argv, 4, &format);
    if (err)
    {
        return err;
    }
    if (info.width < F101_G2D_PATTERN_WIDTH * 2U ||
        info.height < F101_G2D_PATTERN_HEIGHT * 2U)
    {
        err = -RT_EINVAL;
        goto _out;
    }

    err = f101_g2d_allocate_canvas(g2d, &info, &format, &canvas, &canvas_image);
    if (err)
    {
        goto _out;
    }
    pattern.size = F101_G2D_PATTERN_WIDTH * F101_G2D_PATTERN_HEIGHT *
            format.bytes_per_pixel;
    err = rt_device_control(g2d, SUNXI_G2D_CMD_ALLOC_BUFFER, &pattern);
    if (err)
    {
        goto _out;
    }
    pattern_image.buffer = &pattern;
    pattern_image.width = F101_G2D_PATTERN_WIDTH;
    pattern_image.height = F101_G2D_PATTERN_HEIGHT;
    pattern_image.pitch = F101_G2D_PATTERN_WIDTH * format.bytes_per_pixel;
    pattern_image.format = format.format;
    f101_g2d_make_pattern(pattern.virt_addr, &format, pattern_image.width,
            pattern_image.height);

    rt_kprintf("G2D animation: %s scale and rotate, %u frames\n", format.name,
            frames);
    started = rt_tick_get_millisecond();
    for (frame = 0; frame < frames; ++frame)
    {
        struct sunxi_g2d_rect source_rect =
        {
            0, 0, pattern_image.width, pattern_image.height
        };
        struct sunxi_g2d_rect scale_rect;
        struct sunxi_g2d_rect rotate_rect;
        enum sunxi_g2d_rotation rotation;
        rt_uint16_t scale_width = pattern_image.width +
                f101_g2d_triangle(frame, 127,
                pattern_image.width);
        rt_uint16_t scale_height = (rt_uint32_t)pattern_image.height *
                scale_width / pattern_image.width;
        rt_uint16_t rotate_width;
        rt_uint16_t rotate_height;
        rt_uint8_t red = 20U + f101_g2d_triangle(frame, 181, 48);
        rt_uint8_t green = 24U + f101_g2d_triangle(frame + 53U, 157, 48);
        rt_uint8_t blue = 32U + f101_g2d_triangle(frame + 101U, 193, 48);
        rt_uint32_t background = 0xff000000U | ((rt_uint32_t)red << 16) |
                ((rt_uint32_t)green << 8) | blue;

        err = f101_g2d_fill(g2d, &canvas_image, 0, 0, info.width,
                info.height, background);
        if (err)
        {
            break;
        }
        scale_rect = (struct sunxi_g2d_rect)
        {
            f101_g2d_triangle(frame, 137, info.width - scale_width),
            f101_g2d_triangle(frame + 41U, 109, info.height - scale_height),
            scale_width,
            scale_height,
        };
        err = f101_g2d_compose_blit(g2d, &pattern_image, &source_rect,
                &canvas_image, &scale_rect, SUNXI_G2D_ROTATE_0);
        if (err)
        {
            break;
        }
        rotation = (frame / 45U) % 3U + SUNXI_G2D_ROTATE_90;
        if (rotation == SUNXI_G2D_ROTATE_90 ||
            rotation == SUNXI_G2D_ROTATE_270)
        {
            rotate_width = pattern_image.height;
            rotate_height = pattern_image.width;
        }
        else
        {
            rotate_width = pattern_image.width;
            rotate_height = pattern_image.height;
        }
        rotate_rect = (struct sunxi_g2d_rect)
        {
            info.width - F101_G2D_TEST_MARGIN - rotate_width,
            info.height - F101_G2D_TEST_MARGIN - rotate_height,
            rotate_width,
            rotate_height,
        };
        err = f101_g2d_compose_blit(g2d, &pattern_image, &source_rect,
                &canvas_image, &rotate_rect, rotation);
        if (err)
        {
            break;
        }
        err = f101_g2d_present(framebuffer, &info, &canvas);
        if (err)
        {
            break;
        }
    }
    elapsed = rt_tick_get_millisecond() - started;
    if (!elapsed)
    {
        elapsed = 1;
    }
    if (!err)
    {
        rt_kprintf("G2D animation done: %u frames in %u ms, %u.%u fps\n",
                frames, (unsigned int)elapsed,
                (unsigned int)((rt_uint64_t)frames * 1000U / elapsed),
                (unsigned int)(((rt_uint64_t)frames * 10000U / elapsed) % 10U));
    }

_out:
    if (err)
    {
        rt_kprintf("G2D animation failed at frame %u: %d\n", frame, err);
    }
    if (pattern.virt_addr)
    {
        rt_device_control(g2d, SUNXI_G2D_CMD_FREE_BUFFER, &pattern);
    }
    if (canvas.virt_addr)
    {
        rt_device_control(g2d, SUNXI_G2D_CMD_FREE_BUFFER, &canvas);
    }
    rt_device_close(framebuffer);
    return err;
}
MSH_CMD_EXPORT(g2d_anim, animate an F101 G2D scale and rotate scene);

#endif /* RT_USING_FINSH && RT_USING_GRAPHIC && RT_SOC_SUNXI_G2D */
