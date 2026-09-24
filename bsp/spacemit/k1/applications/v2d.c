/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <v2d.h>

#if defined(RT_USING_FINSH) && defined(RT_USING_GRAPHIC) && defined(RT_SOC_SPACEMIT_V2D)
#include <finsh.h>
#include <stdlib.h>

#define V2D_TEST_WIDTH              320U
#define V2D_TEST_HEIGHT             240U
#define V2D_TEST_STRIDE             (V2D_TEST_WIDTH * 4U)
#define V2D_TEST_DEFAULT_FRAMES     240U
#define V2D_TEST_MAX_FRAMES         3600U
#define V2D_TEST_MAX_DEVICES        32U

static rt_device_t v2d_test_find_device(char *name, rt_size_t name_size)
{
    rt_uint32_t id;

    for (id = 0; id < V2D_TEST_MAX_DEVICES; ++id)
    {
        rt_device_t device;

        rt_snprintf(name, name_size, "v2d%u", id);
        device = rt_device_find(name);
        if (device)
        {
            return device;
        }
    }

    name[0] = '\0';
    return RT_NULL;
}

static void v2d_test_set_address(V2D_SURFACE_S *surface,
        const V2D_BUFFER_S *buffer)
{
    surface->phyaddr_y_l = (rt_uint32_t)buffer->phys_addr;
    surface->phyaddr_y_h = (rt_uint32_t)(buffer->phys_addr >> 32);
}

static void v2d_test_fill_pattern(rt_uint32_t *pixels)
{
    static const rt_uint32_t colors[] =
    {
        0xffff3030U,
        0xffffa020U,
        0xffffff30U,
        0xff30d060U,
        0xff30d8ffU,
        0xff4070ffU,
        0xffb050e0U,
        0xffffffffU,
    };
    rt_uint32_t x, y;

    for (y = 0; y < V2D_TEST_HEIGHT; ++y)
    {
        for (x = 0; x < V2D_TEST_WIDTH; ++x)
        {
            rt_uint32_t color = colors[x * RT_ARRAY_SIZE(colors) /
                    V2D_TEST_WIDTH];

            if (x < 3 || y < 3 || x >= V2D_TEST_WIDTH - 3 ||
                y >= V2D_TEST_HEIGHT - 3 || x % 40 < 2 || y % 40 < 2)
            {
                color = 0xff101010U;
            }
            if (x + y >= V2D_TEST_WIDTH - 2 &&
                x + y <= V2D_TEST_WIDTH + 2)
            {
                color = 0xffffffffU;
            }

            pixels[y * V2D_TEST_WIDTH + x] = color;
        }
    }
}

static rt_err_t v2d_test_get_format(const struct rt_device_graphic_info *info,
        V2D_COLOR_FORMAT_E *format)
{
    switch (info->pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        *format = V2D_COLOR_FORMAT_BGRA8888;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        *format = V2D_COLOR_FORMAT_RGBA8888;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        *format = V2D_COLOR_FORMAT_BGR565;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        *format = V2D_COLOR_FORMAT_RGB565;
        break;
    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_uint32_t v2d_test_triangle(rt_uint32_t frame, rt_uint32_t period,
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

static rt_uint32_t v2d_test_rgba(rt_uint8_t r, rt_uint8_t g,
        rt_uint8_t b, rt_uint8_t a)
{
    return (rt_uint32_t)a << 24 | (rt_uint32_t)b << 16 |
            (rt_uint32_t)g << 8 | r;
}

static void v2d_test_fill_task(V2D_SUBMIT_TASK_S *task,
        const V2D_BUFFER_S *source, const V2D_BUFFER_S *destination,
        const struct rt_device_graphic_info *info,
        V2D_COLOR_FORMAT_E destination_format)
{
    V2D_BLEND_LAYER_CONF_S *blend;

    rt_memset(task, 0, sizeof(*task));

    v2d_test_set_address(&task->param.layer0, source);
    task->param.layer0.w = V2D_TEST_WIDTH;
    task->param.layer0.h = V2D_TEST_HEIGHT;
    task->param.layer0.stride = V2D_TEST_STRIDE;
    task->param.layer0.format = V2D_COLOR_FORMAT_BGRA8888;
    task->param.l0_rect.w = V2D_TEST_WIDTH;
    task->param.l0_rect.h = V2D_TEST_HEIGHT;

    v2d_test_set_address(&task->param.dst, destination);
    task->param.dst.w = info->width;
    task->param.dst.h = info->height;
    task->param.dst.stride = info->pitch;
    task->param.dst.format = destination_format;
    task->param.dst_rect.w = info->width;
    task->param.dst_rect.h = info->height;

    task->param.blendconf.blend_cmd = V2D_BLENDCMD_ALPHA;
    task->param.blendconf.bgcolor.enable = true;
    task->param.blendconf.bgcolor.fillcolor.format =
            V2D_COLOR_FORMAT_RGBA8888;
    task->param.blendconf.bgcolor.fillcolor.colorvalue = 0xff202020U;

    blend = &task->param.blendconf.blendlayer[0];
    blend->blend_alpha_source = V2D_BLENDALPHA_SOURCE_GOLBAL;
    blend->blend_pre_alpha_func = V2D_BLEND_PRE_ALPHA_FUNC_DISABLE;
    blend->global_alpha = 0xff;
    blend->stBlendFactor.srcColorFactor = V2D_BLEND_ONE;
    blend->stBlendFactor.dstColorFactor = V2D_BLEND_ZERO;
    blend->stBlendFactor.srcAlphaFactor = V2D_BLEND_ONE;
    blend->stBlendFactor.dstAlphaFactor = V2D_BLEND_ZERO;
    blend->blend_area.w = info->width;
    blend->blend_area.h = info->height;

    task->param.layer1.solidcolor.enable = true;
    task->param.layer1.solidcolor.fillcolor.format =
            V2D_COLOR_FORMAT_RGBA8888;
    task->param.layer1.solidcolor.fillcolor.colorvalue =
            v2d_test_rgba(255, 255, 255, 255);

    blend = &task->param.blendconf.blendlayer[1];
    blend->blend_alpha_source = V2D_BLENDALPHA_SOURCE_GOLBAL;
    blend->blend_pre_alpha_func = V2D_BLEND_PRE_ALPHA_FUNC_DISABLE;
    blend->global_alpha = 0xa0;
    blend->stBlendFactor.srcColorFactor = V2D_BLEND_SRC_ALPHA;
    blend->stBlendFactor.dstColorFactor = V2D_BLEND_ONE_MINUS_SRC_ALPHA;
    blend->stBlendFactor.srcAlphaFactor = V2D_BLEND_ONE;
    blend->stBlendFactor.dstAlphaFactor = V2D_BLEND_ONE_MINUS_SRC_ALPHA;
    blend->blend_area.w = info->width / 5;
    blend->blend_area.h = info->height / 5;

    task->param.l0_rt = V2D_ROT_0;
    task->param.l1_rt = V2D_ROT_0;
    task->param.l0_csc = V2D_CSC_MODE_BUTT;
    task->param.l1_csc = V2D_CSC_MODE_BUTT;
    task->param.dither = V2D_NO_DITHER;
    task->acquireFencefd = -1;
    task->completeFencefd = -1;
}

static void v2d_test_animate_task(V2D_SUBMIT_TASK_S *task,
        const struct rt_device_graphic_info *info, rt_uint32_t frame)
{
    static const V2D_ROTATE_ANGLE_E rotations[] =
    {
        V2D_ROT_0,
        V2D_ROT_90,
        V2D_ROT_180,
        V2D_ROT_270,
        V2D_ROT_MIRROR,
        V2D_ROT_FLIP,
    };
    V2D_BLEND_LAYER_CONF_S *layer0 =
            &task->param.blendconf.blendlayer[0];
    V2D_BLEND_LAYER_CONF_S *layer1 =
            &task->param.blendconf.blendlayer[1];
    rt_uint32_t min_width, max_width, min_height, max_height;
    rt_uint32_t width, height;
    rt_uint32_t red, green, blue;

    min_width = rt_min((rt_uint32_t)info->width,
            rt_max((rt_uint32_t)96, (rt_uint32_t)info->width / 8));
    max_width = rt_max(min_width, (rt_uint32_t)info->width * 3 / 4);
    min_height = rt_min((rt_uint32_t)info->height,
            rt_max((rt_uint32_t)72, (rt_uint32_t)info->height / 8));
    max_height = rt_max(min_height, (rt_uint32_t)info->height * 3 / 4);

    width = min_width + v2d_test_triangle(frame, 151,
            max_width - min_width);
    height = min_height + v2d_test_triangle(frame + 37, 127,
            max_height - min_height);
    layer0->blend_area.w = width;
    layer0->blend_area.h = height;
    layer0->blend_area.x = v2d_test_triangle(frame, 137,
            info->width - width);
    layer0->blend_area.y = v2d_test_triangle(frame + 29, 103,
            info->height - height);
    task->param.l0_rt = rotations[(frame / 40) % RT_ARRAY_SIZE(rotations)];

    width = rt_max((rt_uint32_t)32, (rt_uint32_t)info->width / 5);
    height = rt_max((rt_uint32_t)32, (rt_uint32_t)info->height / 5);
    width = rt_min(width, (rt_uint32_t)info->width);
    height = rt_min(height, (rt_uint32_t)info->height);
    layer1->blend_area.w = width;
    layer1->blend_area.h = height;
    layer1->blend_area.x = v2d_test_triangle(frame + 61, 113,
            info->width - width);
    layer1->blend_area.y = v2d_test_triangle(frame + 17, 89,
            info->height - height);
    layer1->global_alpha = 80 + v2d_test_triangle(frame + 23, 97, 144);

    red = 20 + v2d_test_triangle(frame, 181, 52);
    green = 24 + v2d_test_triangle(frame + 53, 157, 48);
    blue = 32 + v2d_test_triangle(frame + 101, 193, 64);
    task->param.blendconf.bgcolor.fillcolor.colorvalue =
            v2d_test_rgba(red, green, blue, 255);

    red = 96 + v2d_test_triangle(frame + 73, 109, 159);
    green = 64 + v2d_test_triangle(frame + 7, 131, 191);
    blue = 80 + v2d_test_triangle(frame + 41, 149, 175);
    task->param.layer1.solidcolor.fillcolor.colorvalue =
            v2d_test_rgba(red, green, blue, 255);
}

static rt_err_t v2d_test_parse_frames(const char *text,
        rt_uint32_t *frames)
{
    char *end;
    unsigned long value = strtoul(text, &end, 0);

    if (!text[0] || *end || !value || value > V2D_TEST_MAX_FRAMES)
    {
        return -RT_EINVAL;
    }

    *frames = value;
    return RT_EOK;
}

static int v2d_test(int argc, char **argv)
{
    const char *fb_name = argc > 1 ? argv[1] : "fb0";
    struct rt_device_graphic_info info;
    struct rt_graphic_device *graphic;
    V2D_BUFFER_S source = { 0 };
    V2D_BUFFER_S destination = { 0 };
    V2D_SUBMIT_TASK_S task;
    V2D_COLOR_FORMAT_E destination_format;
    rt_device_t v2d, fb;
    rt_uint8_t *front_buffer, *back_buffer, *swap_buffer;
    char v2d_name[RT_NAME_MAX];
    rt_size_t screen_size;
    rt_uint32_t frame_count = V2D_TEST_DEFAULT_FRAMES;
    rt_uint32_t frame;
    rt_tick_t start_ms, elapsed_ms;
    rt_bool_t v2d_opened = RT_FALSE;
    rt_bool_t fb_opened = RT_FALSE;
    rt_bool_t restore_auto_update = RT_FALSE;
    rt_err_t err;

    if (argc > 3 || (argc > 2 &&
        v2d_test_parse_frames(argv[2], &frame_count) != RT_EOK))
    {
        rt_kprintf("Usage: v2d_test [framebuffer] [frames: 1-%u]\n",
                V2D_TEST_MAX_FRAMES);
        return -RT_EINVAL;
    }

    v2d = v2d_test_find_device(v2d_name, sizeof(v2d_name));
    fb = rt_device_find(fb_name);
    if (!v2d || !fb)
    {
        rt_kprintf("V2D device or framebuffer %s not found\n", fb_name);
        return -RT_ENOSYS;
    }

    if ((err = rt_device_open(v2d, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        rt_kprintf("open %s failed: %d\n", v2d_name, err);
        return err;
    }
    v2d_opened = RT_TRUE;

    if ((err = rt_device_open(fb, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        rt_kprintf("open %s failed: %d\n", fb_name, err);
        goto _out;
    }
    fb_opened = RT_TRUE;

    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_GET_INFO, &info)) !=
            RT_EOK)
    {
        goto _out;
    }
    screen_size = (rt_size_t)info.pitch * info.height;
    if (!info.framebuffer || !info.width || !info.height || !info.pitch ||
        screen_size > info.smem_len || screen_size > V2D_BUFFER_MAX_SIZE ||
        (err = v2d_test_get_format(&info, &destination_format)) != RT_EOK)
    {
        err = -RT_EINVAL;
        rt_kprintf("unsupported framebuffer layout: %ux%u pitch=%u fmt=%u\n",
                info.width, info.height, info.pitch, info.pixel_format);
        goto _out;
    }
    if (screen_size > info.smem_len / 2U)
    {
        err = -RT_ENOMEM;
        rt_kprintf("%s needs a double framebuffer for tear-free animation "
                "(have %u, need %u bytes)\n", fb_name,
                (unsigned int)info.smem_len,
                (unsigned int)(screen_size * 2U));
        goto _out;
    }
    front_buffer = info.framebuffer;
    back_buffer = front_buffer + screen_size;

    source.size = V2D_TEST_STRIDE * V2D_TEST_HEIGHT;
    if ((err = rt_device_control(v2d, V2D_ALLOC_BUFFER, &source)) != RT_EOK)
    {
        rt_kprintf("allocate V2D source failed: %d\n", err);
        goto _out;
    }
    destination.size = screen_size;
    if ((err = rt_device_control(v2d, V2D_ALLOC_BUFFER, &destination)) !=
            RT_EOK)
    {
        rt_kprintf("allocate V2D destination failed: %d\n", err);
        goto _out;
    }

    v2d_test_fill_pattern(source.virt_addr);
    rt_memset(destination.virt_addr, 0, destination.size);
    v2d_test_fill_task(&task, &source, &destination, &info,
            destination_format);

    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_POWERON, RT_NULL)) !=
            RT_EOK)
    {
        goto _out;
    }
    graphic = rt_container_of(fb, struct rt_graphic_device, parent);
    restore_auto_update = graphic->update_timer != RT_NULL;
    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, 0);
    }

    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_PAN_DISPLAY,
            front_buffer)) != RT_EOK ||
        (err = rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC,
            RT_NULL)) != RT_EOK)
    {
        rt_kprintf("framebuffer page-flip setup failed: %d\n", err);
        goto _out;
    }

    rt_kprintf("V2D animation: %ux%u BGRA8888 -> %ux%u format %u, %u frames\n",
            V2D_TEST_WIDTH, V2D_TEST_HEIGHT, info.width, info.height,
            info.pixel_format, frame_count);
    start_ms = rt_tick_get_millisecond();

    for (frame = 0; frame < frame_count; ++frame)
    {
        v2d_test_animate_task(&task, &info, frame * 2U);
        if ((err = rt_device_control(v2d, V2D_SUBMIT, &task)) != RT_EOK)
        {
            rt_kprintf("V2D submit failed at frame %u: %d\n", frame, err);
            goto _out;
        }

        rt_memcpy(back_buffer, destination.virt_addr, screen_size);
        if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_PAN_DISPLAY,
                back_buffer)) != RT_EOK ||
            (err = rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC,
                RT_NULL)) != RT_EOK)
        {
            rt_kprintf("framebuffer update failed at frame %u: %d\n",
                    frame, err);
            goto _out;
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
    rt_kprintf("V2D animation done on %s: %u frames in %u ms, %u.%u fps\n",
            fb_name, frame_count, (unsigned int)elapsed_ms,
            (unsigned int)((rt_uint64_t)frame_count * 1000 / elapsed_ms),
            (unsigned int)(((rt_uint64_t)frame_count * 10000 / elapsed_ms) % 10));
    err = RT_EOK;

_out:
    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, RT_GRAPHIC_UPDATE_MS);
    }
    if (destination.virt_addr)
    {
        rt_device_control(v2d, V2D_FREE_BUFFER, &destination);
    }
    if (source.virt_addr)
    {
        rt_device_control(v2d, V2D_FREE_BUFFER, &source);
    }
    if (fb_opened)
    {
        rt_device_close(fb);
    }
    if (v2d_opened)
    {
        rt_device_close(v2d);
    }

    return err;
}
MSH_CMD_EXPORT(v2d_test, run the K1 V2D animation and framebuffer test);
#endif /* RT_USING_FINSH && RT_USING_GRAPHIC && RT_SOC_SPACEMIT_V2D */
