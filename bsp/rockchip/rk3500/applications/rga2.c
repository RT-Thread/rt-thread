/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_FINSH) && defined(RT_USING_GRAPHIC) && defined(RT_ROCKCHIP_RGA2)
#include <finsh.h>
#include <rga2.h>
#include <stdlib.h>

#define RGA2_TEST_WIDTH                320
#define RGA2_TEST_HEIGHT               180
#define RGA2_TEST_MARGIN               12
#define RGA2_ANIM_DEFAULT_FRAMES       600U
#define RGA2_ANIM_MAX_FRAMES           3600U

static void rga2_make_pattern(rt_uint32_t *pixels, int width, int height)
{
    int x, y;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            rt_uint32_t color;

            if (x < width / 4 && y < height / 4)
            {
                color = 0xffff0000;
            }
            else if (x >= width * 3 / 4 && y < height / 4)
            {
                color = 0xff00ff00;
            }
            else if (x < width / 4 && y >= height * 3 / 4)
            {
                color = 0xff0000ff;
            }
            else if (x >= width * 3 / 4 && y >= height * 3 / 4)
            {
                color = 0xffffffff;
            }
            else
            {
                rt_uint32_t red = x * 255 / width;
                rt_uint32_t green = y * 255 / height;
                rt_uint32_t blue = (x + y) * 127 / (width + height);

                color = 0xff000000 | (red << 16) | (green << 8) | blue;
            }

            /* An off-centre cross makes every rotation and mirror obvious. */
            if ((x >= width / 3 && x < width / 3 + 5) ||
                (y >= height / 3 && y < height / 3 + 5))
            {
                color = 0xffffff00;
            }
            pixels[y * width + x] = color;
        }
    }
}

static void rga2_set_image(struct rga2_image *image,
        const struct rga2_buffer *buffer, rt_uint16_t width,
        rt_uint16_t height, rt_uint16_t stride)
{
    image->address = buffer->phys_addr;
    image->width = width;
    image->height = height;
    image->stride = stride;
    image->format = RGA2_FORMAT_BGRA8888;
}

static rt_err_t rga2_fill(rt_device_t rga, struct rga2_req *req,
        rt_uint16_t x, rt_uint16_t y, rt_uint16_t width,
        rt_uint16_t height, rt_uint32_t color)
{
    req->render_mode = RGA2_MODE_COLOR_FILL;
    req->rotate = RGA2_ROTATE_0;
    req->mirror = 0;
    req->color = color;
    req->dst.rect.x = x;
    req->dst.rect.y = y;
    req->dst.rect.width = width;
    req->dst.rect.height = height;

    return rt_device_control(rga, RGA2_SUBMIT, req);
}

static rt_err_t rga2_blit(rt_device_t rga, struct rga2_req *req,
        rt_uint16_t x, rt_uint16_t y, rt_uint16_t width,
        rt_uint16_t height, rt_uint8_t rotate, rt_uint8_t mirror)
{
    req->render_mode = RGA2_MODE_BITBLT;
    req->rotate = rotate;
    req->mirror = mirror;
    req->src.rect.x = 0;
    req->src.rect.y = 0;
    req->src.rect.width = RGA2_TEST_WIDTH;
    req->src.rect.height = RGA2_TEST_HEIGHT;
    req->dst.rect.x = x;
    req->dst.rect.y = y;
    req->dst.rect.width = width;
    req->dst.rect.height = height;

    return rt_device_control(rga, RGA2_SUBMIT, req);
}

static rt_uint32_t rga2_triangle(rt_uint32_t frame, rt_uint32_t period,
        rt_uint32_t amplitude)
{
    rt_uint32_t half = period / 2;
    rt_uint32_t phase = frame % period;

    if (phase > half)
    {
        phase = period - phase;
    }

    return half ? (rt_uint64_t)amplitude * phase / half : 0;
}

static rt_uint32_t rga2_color(rt_uint8_t red, rt_uint8_t green,
        rt_uint8_t blue)
{
    return 0xff000000U | (rt_uint32_t)red << 16 |
            (rt_uint32_t)green << 8 | blue;
}

static rt_err_t rga2_parse_frames(const char *text, rt_uint32_t *frames)
{
    char *end;
    unsigned long value = strtoul(text, &end, 0);

    if (!text[0] || *end || !value || value > RGA2_ANIM_MAX_FRAMES)
    {
        return -RT_EINVAL;
    }

    *frames = value;
    return RT_EOK;
}

static int rga2_test(int argc, char **argv)
{
    const char *rga_name = argc > 1 ? argv[1] : "rga0";
    const char *fb_name = argc > 2 ? argv[2] : "fb0";
    rt_device_t rga = rt_device_find(rga_name);
    rt_device_t fb = rt_device_find(fb_name);
    struct rt_device_graphic_info info;
    struct rt_device_rect_info rect;
    struct rga2_buffer source = { 0 };
    struct rga2_buffer destination = { 0 };
    struct rga2_req req = { 0 };
    static const rt_uint8_t rotations[] =
    {
        RGA2_ROTATE_0, RGA2_ROTATE_90, RGA2_ROTATE_180,
        RGA2_ROTATE_270, RGA2_ROTATE_0, RGA2_ROTATE_0,
    };
    static const rt_uint8_t mirrors[] =
    {
        0, 0, 0, 0, RGA2_MIRROR_X, RGA2_MIRROR_Y,
    };
    static const char *names[] =
    {
        "scale", "rotate 90", "rotate 180", "rotate 270",
        "mirror X", "mirror Y",
    };
    rt_uint32_t version;
    rt_uint16_t panel_width, panel_height;
    int i;
    rt_err_t err = -RT_ERROR;

    if (!rga || !fb)
    {
        rt_kprintf("device not found: %s or %s\n", rga_name, fb_name);
        return -RT_EINVAL;
    }
    if ((err = rt_device_open(fb, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        return err;
    }
    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_GET_INFO, &info)) != RT_EOK)
    {
        goto _out;
    }
    if (info.bits_per_pixel != 32 || !info.framebuffer)
    {
        rt_kprintf("rga2_test requires a 32-bit framebuffer\n");
        err = -RT_ENOSYS;
        goto _out;
    }
    if (info.width <= RGA2_TEST_MARGIN * 4 ||
        info.height <= RGA2_TEST_MARGIN * 3 || info.pitch > UINT16_MAX)
    {
        rt_kprintf("framebuffer geometry is not supported\n");
        err = -RT_EINVAL;
        goto _out;
    }

    source.size = RGA2_TEST_WIDTH * RGA2_TEST_HEIGHT * 4;
    destination.size = info.pitch * info.height;
    if ((err = rt_device_control(rga, RGA2_ALLOC_BUFFER, &source)) != RT_EOK ||
        (err = rt_device_control(rga, RGA2_ALLOC_BUFFER, &destination)) != RT_EOK)
    {
        rt_kprintf("RGA2 buffer allocation failed: %d\n", err);
        goto _out;
    }
    rga2_make_pattern(source.virt_addr, RGA2_TEST_WIDTH, RGA2_TEST_HEIGHT);

    rga2_set_image(&req.src, &source, RGA2_TEST_WIDTH,
            RGA2_TEST_HEIGHT, RGA2_TEST_WIDTH * 4);
    rga2_set_image(&req.dst, &destination, info.width,
            info.height, info.pitch);

    /* Clear the complete output through the color-fill render mode. */
    if ((err = rga2_fill(rga, &req, 0, 0, info.width, info.height,
            0xff202020)) != RT_EOK)
    {
        rt_kprintf("RGA2 color fill failed: %d, irq=0x%08x\n",
                   err, req.irq_status);
        goto _out;
    }

    panel_width = (info.width - RGA2_TEST_MARGIN * 4) / 3;
    panel_height = (info.height - RGA2_TEST_MARGIN * 3) / 2;
    if (!panel_width || !panel_height)
    {
        err = -RT_EINVAL;
        goto _out;
    }

    for (i = 0; i < 6; ++i)
    {
        rt_uint16_t x = RGA2_TEST_MARGIN +
                (i % 3) * (panel_width + RGA2_TEST_MARGIN);
        rt_uint16_t y = RGA2_TEST_MARGIN +
                (i / 3) * (panel_height + RGA2_TEST_MARGIN);

        err = rga2_blit(rga, &req, x, y, panel_width, panel_height,
                rotations[i], mirrors[i]);
        if (err != RT_EOK)
        {
            rt_kprintf("RGA2 %s failed: %d, irq=0x%08x\n",
                       names[i], err, req.irq_status);
            goto _out;
        }
        rt_kprintf("RGA2 %-10s: (%u,%u) %ux%u\n",
                   names[i], x, y, panel_width, panel_height);
    }

    rt_memcpy(info.framebuffer, destination.virt_addr, destination.size);
    rect.x = 0;
    rect.y = 0;
    rect.width = info.width;
    rect.height = info.height;
    rt_device_control(fb, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
    rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);
    rt_device_control(rga, RGA2_GET_VERSION, &version);
    rt_kprintf("RGA2 %08x completed fill/scale/rotate/mirror tests on %s\n",
               version, fb_name);
    err = RT_EOK;

_out:
    if (destination.virt_addr)
    {
        rt_device_control(rga, RGA2_FREE_BUFFER, &destination);
    }
    if (source.virt_addr)
    {
        rt_device_control(rga, RGA2_FREE_BUFFER, &source);
    }
    rt_device_close(fb);
    return err;
}
MSH_CMD_EXPORT(rga2_test, run RGA2 fill scale rotate and mirror tests);

static int rga2_anim(int argc, char **argv)
{
    const char *rga_name = argc > 1 ? argv[1] : "rga0";
    const char *fb_name = argc > 2 ? argv[2] : "fb0";
    rt_uint32_t frames = RGA2_ANIM_DEFAULT_FRAMES;
    rt_device_t rga = rt_device_find(rga_name);
    rt_device_t fb = rt_device_find(fb_name);
    struct rt_graphic_device *graphic;
    struct rt_device_graphic_info info;
    struct rga2_buffer source = { 0 };
    struct rga2_buffer destination = { 0 };
    struct rga2_req req = { 0 };
    static const rt_uint8_t rotations[] =
    {
        RGA2_ROTATE_0, RGA2_ROTATE_90, RGA2_ROTATE_180,
        RGA2_ROTATE_270, RGA2_ROTATE_0, RGA2_ROTATE_0,
    };
    static const rt_uint8_t mirrors[] =
    {
        0, 0, 0, 0, RGA2_MIRROR_X, RGA2_MIRROR_Y,
    };
    rt_uint8_t *front_buffer, *back_buffer, *swap_buffer;
    rt_size_t screen_size;
    unsigned long frame = 0;
    rt_tick_t start_ms, elapsed_ms;
    rt_bool_t restore_auto_update = RT_FALSE;
    rt_err_t err = -RT_ERROR;

    if (argc > 4 || (argc > 3 &&
        rga2_parse_frames(argv[3], &frames) != RT_EOK))
    {
        rt_kprintf("usage: rga2_anim [rga] [fb] [frames: 1-%u]\n",
                   RGA2_ANIM_MAX_FRAMES);
        return -RT_EINVAL;
    }
    if (!rga || !fb)
    {
        rt_kprintf("device not found: %s or %s\n", rga_name, fb_name);
        return -RT_ENOSYS;
    }
    if ((err = rt_device_open(fb, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        return err;
    }
    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_GET_INFO, &info)) != RT_EOK)
    {
        goto _out;
    }
    if (info.bits_per_pixel != 32 || !info.framebuffer ||
        info.width < 400 || info.height < 240 || info.pitch > UINT16_MAX)
    {
        rt_kprintf("rga2_anim requires a 32-bit framebuffer of at least 400x240\n");
        err = -RT_ENOSYS;
        goto _out;
    }

    screen_size = (rt_size_t)info.pitch * info.height;
    if (screen_size > info.smem_len / 2U)
    {
        rt_kprintf("%s needs a double framebuffer for tear-free animation\n",
                   fb_name);
        err = -RT_ENOMEM;
        goto _out;
    }
    front_buffer = info.framebuffer;
    back_buffer = front_buffer + screen_size;
    graphic = rt_container_of(fb, struct rt_graphic_device, parent);
    restore_auto_update = graphic->update_timer != RT_NULL;
    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, 0);
    }

    source.size = RGA2_TEST_WIDTH * RGA2_TEST_HEIGHT * 4;
    destination.size = screen_size;
    if ((err = rt_device_control(rga, RGA2_ALLOC_BUFFER, &source)) != RT_EOK ||
        (err = rt_device_control(rga, RGA2_ALLOC_BUFFER, &destination)) != RT_EOK)
    {
        rt_kprintf("RGA2 buffer allocation failed: %d\n", err);
        goto _out;
    }

    rga2_make_pattern(source.virt_addr, RGA2_TEST_WIDTH, RGA2_TEST_HEIGHT);
    rga2_set_image(&req.src, &source, RGA2_TEST_WIDTH,
            RGA2_TEST_HEIGHT, RGA2_TEST_WIDTH * 4);
    rga2_set_image(&req.dst, &destination, info.width,
            info.height, info.pitch);

    if ((err = rga2_fill(rga, &req, 0, 0, info.width, info.height,
            0xff182028)) != RT_EOK)
    {
        goto _failed;
    }
    rt_memcpy(front_buffer, destination.virt_addr, screen_size);
    rt_memcpy(back_buffer, destination.virt_addr, screen_size);
    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_PAN_DISPLAY,
            front_buffer)) != RT_EOK ||
        (err = rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC,
            RT_NULL)) != RT_EOK)
    {
        rt_kprintf("framebuffer page-flip setup failed: %d\n", err);
        goto _out;
    }

    rt_kprintf("RGA2 animation: fill, scale, rotate, mirror, %u frames\n",
               frames);
    start_ms = rt_tick_get_millisecond();

    for (frame = 0; frame < frames; ++frame)
    {
        rt_uint32_t min_width = rt_max(96U, info.width / 8U);
        rt_uint32_t min_height = rt_max(72U, info.height / 8U);
        rt_uint32_t max_width = info.width * 3U / 4U;
        rt_uint32_t max_height = info.height * 3U / 4U;
        rt_uint32_t width = min_width + rga2_triangle(frame, 151,
                max_width - min_width);
        rt_uint32_t height = min_height + rga2_triangle(frame + 37, 127,
                max_height - min_height);
        rt_uint32_t x = rga2_triangle(frame, 137, info.width - width);
        rt_uint32_t y = rga2_triangle(frame + 29, 103, info.height - height);
        rt_uint32_t transform = (frame / 40) % 6;
        rt_uint32_t small_width = rt_max(64U, info.width / 5U);
        rt_uint32_t small_height = rt_max(48U, info.height / 5U);
        rt_uint32_t small_x = rga2_triangle(frame + 61, 113,
                info.width - small_width);
        rt_uint32_t small_y = rga2_triangle(frame + 17, 89,
                info.height - small_height);
        rt_uint32_t box_width = rt_max(40U, info.width / 10U);
        rt_uint32_t box_height = rt_max(32U, info.height / 10U);
        rt_uint32_t box_x = rga2_triangle(frame + 83, 97,
                info.width - box_width);
        rt_uint32_t box_y = rga2_triangle(frame + 43, 79,
                info.height - box_height);
        rt_uint32_t background = rga2_color(
                20 + rga2_triangle(frame, 181, 52),
                24 + rga2_triangle(frame + 53, 157, 48),
                32 + rga2_triangle(frame + 101, 193, 64));
        rt_uint32_t box_color = rga2_color(
                96 + rga2_triangle(frame + 73, 109, 159),
                64 + rga2_triangle(frame + 7, 131, 191),
                80 + rga2_triangle(frame + 41, 149, 175));

        /* Each operation below is a separate RGA2 hardware job. */
        err = rga2_fill(rga, &req, 0, 0, info.width, info.height,
                background);
        if (err != RT_EOK)
        {
            goto _failed;
        }
        err = rga2_blit(rga, &req, x, y, width, height,
                rotations[transform], mirrors[transform]);
        if (err != RT_EOK)
        {
            goto _failed;
        }
        err = rga2_blit(rga, &req, small_x, small_y,
                small_width, small_height,
                rotations[(transform + 3) % 6],
                mirrors[(transform + 3) % 6]);
        if (err != RT_EOK)
        {
            goto _failed;
        }
        err = rga2_fill(rga, &req, box_x, box_y, box_width, box_height,
                box_color);
        if (err != RT_EOK)
        {
            goto _failed;
        }

        rt_memcpy(back_buffer, destination.virt_addr, screen_size);
        if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_PAN_DISPLAY,
                back_buffer)) != RT_EOK ||
            (err = rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC,
                RT_NULL)) != RT_EOK)
        {
            goto _failed;
        }
        swap_buffer = front_buffer;
        front_buffer = back_buffer;
        back_buffer = swap_buffer;
    }

    elapsed_ms = rt_tick_get_millisecond() - start_ms;
    if (!elapsed_ms)
    {
        elapsed_ms = 1;
    }
    rt_kprintf("RGA2 animation done on %s: %u frames in %u ms, %u.%u fps\n",
               fb_name, frames, (unsigned int)elapsed_ms,
               (unsigned int)((rt_uint64_t)frames * 1000 / elapsed_ms),
               (unsigned int)(((rt_uint64_t)frames * 10000 / elapsed_ms) % 10));
    err = RT_EOK;
    goto _out;

_failed:
    rt_kprintf("RGA2 animation failed at frame %lu: %d, irq=0x%08x\n",
               frame, err, req.irq_status);

_out:
    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, RT_GRAPHIC_UPDATE_MS);
    }
    if (destination.virt_addr)
    {
        rt_device_control(rga, RGA2_FREE_BUFFER, &destination);
    }
    if (source.virt_addr)
    {
        rt_device_control(rga, RGA2_FREE_BUFFER, &source);
    }
    rt_device_close(fb);
    return err;
}
MSH_CMD_EXPORT(rga2_anim, animate an RGA2 scaled and rotating image);
#endif /* RT_USING_FINSH && RT_USING_GRAPHIC && RT_ROCKCHIP_RGA2 */
