/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <cpuport.h>
#include <drivers/misc.h>

#if defined(RT_USING_GRAPHIC) && defined(RT_USING_INPUT)

#define CURSOR_WIDTH    64
#define CURSOR_HEIGHT   64

struct hmi_info
{
    struct rt_device *gdev;
    struct rt_device *idev;

    struct rt_device_graphic_info info;
    struct rt_device_notify event_notify;
    struct rt_input_handler handler;

    rt_bool_t event;
    rt_bool_t vsync;
    rt_bool_t keydown;

    rt_uint32_t x, y;
    rt_uint32_t dx, dy;
    rt_uint32_t bytes_per_pixel;
    rt_ubase_t line[2];
    rt_ubase_t colors[4];

    void *backend_framebuffer;
};

static rt_bool_t hmi_working;

static struct rt_input_device *to_input_device(struct rt_device *idev)
{
    return rt_container_of(idev, struct rt_input_device, parent);
}

static rt_ubase_t to_color(rt_uint8_t color255, rt_ubase_t color_max)
{
    return (rt_ubase_t)color255 * color_max / 255;
}

static void hmi_reset(struct hmi_info *hmi)
{
    void *cursor;
    rt_ubase_t none_alpha;
    rt_ubase_t red_off, green_off, blue_off, alpha_off;
    rt_ubase_t red_mask, green_mask, blue_mask, alpha_mask;
    struct fb_var_screeninfo var;

    if (hmi->backend_framebuffer)
    {
        rt_free(hmi->backend_framebuffer);
    }

    rt_device_control(hmi->gdev, FBIOGET_VSCREENINFO, &var);
    rt_device_control(hmi->gdev, RTGRAPHIC_CTRL_GET_INFO, &hmi->info);

    hmi->backend_framebuffer = rt_malloc(hmi->info.smem_len);

    hmi->bytes_per_pixel = hmi->info.bits_per_pixel / 8;
    red_off = var.red.offset;
    red_mask = RT_GENMASK(var.red.length - 1, 0);
    green_off = var.green.offset;
    green_mask = RT_GENMASK(var.green.length - 1, 0);
    blue_off = var.blue.offset;
    blue_mask = RT_GENMASK(var.blue.length - 1, 0);

    if (var.transp.length)
    {
        alpha_off = var.transp.offset;
        alpha_mask = RT_GENMASK(var.transp.length - 1, 0);
    }
    else
    {
        alpha_off = 0;
        alpha_mask = 0;
    }

    if ((cursor = rt_malloc(CURSOR_WIDTH * CURSOR_HEIGHT * hmi->bytes_per_pixel)))
    {
        rt_uint8_t *stream = cursor;
        rt_ubase_t color = ((to_color(0x82, red_mask)) << red_off) |
                            (to_color(0x50, green_mask) << green_off) |
                            (to_color(0xdf, blue_mask) << blue_off) |
                            (to_color(0xcc, alpha_mask) << alpha_off);

        for (int y = 0; y < CURSOR_HEIGHT; ++y)
        {
            for (int x = 0; x < CURSOR_WIDTH; ++x)
            {
                rt_memcpy(stream, &color, hmi->bytes_per_pixel);
                stream += hmi->bytes_per_pixel;
            }
        }

        rt_device_control(hmi->gdev, RT_DEVICE_CTRL_CURSOR_SET_TYPE, cursor);
        rt_free(cursor);
    }

    none_alpha = alpha_mask << alpha_off;

    hmi->line[0] = ~0UL;
    hmi->line[1] = none_alpha;

    hmi->colors[0] = ((to_color(0xff, red_mask)) << red_off) |
                      (to_color(0x4b, green_mask) << green_off) |
                      (to_color(0x00, blue_mask) << blue_off) | none_alpha;
    hmi->colors[1] = ((to_color(0x7f, red_mask)) << red_off) |
                      (to_color(0xdb, green_mask) << green_off) |
                      (to_color(0x3b, blue_mask) << blue_off) | none_alpha;
    hmi->colors[2] = ((to_color(0x00, red_mask)) << red_off) |
                      (to_color(0xa4, green_mask) << green_off) |
                      (to_color(0xef, blue_mask) << blue_off) | none_alpha;
    hmi->colors[3] = ((to_color(0xff, red_mask)) << red_off) |
                      (to_color(0xb8, green_mask) << green_off) |
                      (to_color(0x1c, blue_mask) << blue_off) | none_alpha;

    hmi->event = RT_FALSE;
}

static void hmi_graphic_notify(rt_device_t dev)
{
    struct hmi_info *hmi = (void *)dev;

    hmi->event = RT_TRUE;
}

static rt_bool_t hmi_input_callback(struct rt_input_handler *handler,
        struct rt_input_event *ev)
{
    struct hmi_info *hmi = handler->priv;

    if (ev->type == EV_ABS)
    {
        if (ev->code == 0)
        {
            hmi->dx = (ev->value * hmi->info.width) /
                (handler->idev->absinfo->maximum - handler->idev->absinfo->minimum);
        }
        else if (ev->code == 1)
        {
            hmi->dy = (ev->value * hmi->info.height) /
                (handler->idev->absinfo->maximum - handler->idev->absinfo->minimum);
        }
    }
    else if (ev->type == EV_KEY)
    {
        if (ev->code == BTN_LEFT)
        {
            if (hmi->keydown && ev->value == 0)
            {
                /* Swap lines color */
                hmi->line[0] ^= hmi->line[1];
                hmi->line[1] ^= hmi->line[0];
                hmi->line[0] ^= hmi->line[1];

                hmi->keydown = RT_FALSE;
                hmi->vsync = RT_FALSE;
            }
            else
            {
                hmi->keydown = RT_TRUE;
            }
        }
    }
    else if (ev->type == EV_SYN)
    {
        hmi->vsync = RT_FALSE;
    }

    return RT_TRUE;
}

static void hmi_loop(void *param)
{
    struct hmi_info *hmi = param;
    struct rt_device_rect_info rect;
    struct rt_device_graphic_ops *gops;

    /* Graphic device event */
    hmi->event_notify.notify = &hmi_graphic_notify;
    hmi->event_notify.dev = (void *)hmi;
    rt_device_control(hmi->gdev, RT_DEVICE_CTRL_NOTIFY_SET, &hmi->event_notify);

    /* Input device event */
    hmi->handler.idev = to_input_device(hmi->idev);
    hmi->handler.identify = RT_NULL;
    hmi->handler.callback = &hmi_input_callback;
    hmi->handler.priv = hmi;
    rt_input_add_handler(&hmi->handler);

    hmi->backend_framebuffer = RT_NULL;
    hmi_reset(hmi);

    hmi->dx = hmi->info.width >> 1;
    hmi->dy = hmi->info.height >> 1;

    rect.x = 0;
    rect.y = 0;

    gops = rt_graphix_ops(hmi->gdev);
    rt_device_control(hmi->gdev, RTGRAPHIC_CTRL_POWERON, RT_NULL);

    while (hmi_working)
    {
        rt_ubase_t pos;

        /* Wait graphic change */
        if (hmi->event)
        {
            hmi_reset(hmi);
        }

        hmi->x = hmi->dx;
        hmi->y = hmi->dy;

        rect.width = hmi->info.width;
        rect.height = hmi->info.height;
        pos = RTGRAPHIC_PIXEL_POSITION(hmi->x, hmi->y);

        for (int i = 0; i < RT_ARRAY_SIZE(hmi->colors); ++i)
        {
            rt_uint32_t x1, y1, x2, y2;
            void *fb = hmi->backend_framebuffer ? : hmi->info.framebuffer;

            switch (i)
            {
            case 0:
                x1 = 0;
                y1 = 0;
                x2 = hmi->x;
                y2 = hmi->y;
                break;

            case 1:
                x1 = hmi->x;
                y1 = 0;
                x2 = hmi->info.width;
                y2 = hmi->y;
                break;

            case 2:
                x1 = 0;
                y1 = hmi->y;
                x2 = hmi->x;
                y2 = hmi->info.height;
                break;

            case 3:
                x1 = hmi->x;
                y1 = hmi->y;
                x2 = hmi->info.width;
                y2 = hmi->info.height;
                break;
            }

            fb += x1 * hmi->bytes_per_pixel + y1 * hmi->info.pitch;

            for (int y = y1; y < y2; ++y)
            {
                void *fb_entry = fb;

                for (int x = x1; x < x2; ++x)
                {
                    rt_memcpy(fb, &hmi->colors[i], hmi->bytes_per_pixel);
                    fb += hmi->bytes_per_pixel;
                }

                fb = fb_entry + hmi->info.pitch;
            }
        }

        if (hmi->backend_framebuffer)
        {
            rt_memcpy(hmi->info.framebuffer, hmi->backend_framebuffer, hmi->info.smem_len);
        }

        gops->draw_hline((void *)&hmi->line[0], 0, rect.width, hmi->y);
        gops->draw_vline((void *)&hmi->line[1], hmi->x, 0, rect.height);

        rt_device_control(hmi->gdev, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
        rt_device_control(hmi->gdev, RT_DEVICE_CTRL_CURSOR_SET_POSITION, (void *)pos);

        /* Next position */
        hmi->vsync = RT_TRUE;
        rt_hw_wmb();

        while (hmi_working && hmi->vsync)
        {
            rt_thread_mdelay(1);
        }
    }

    rt_device_control(hmi->gdev, RTGRAPHIC_CTRL_POWEROFF, RT_NULL);

    rt_memset(&hmi->event_notify, 0, sizeof(hmi->event_notify));
    rt_device_control(hmi->gdev, RT_DEVICE_CTRL_NOTIFY_SET, &hmi->event_notify);

    rt_input_del_handler(&hmi->handler);

    rt_device_close(hmi->gdev);
    rt_device_close(hmi->idev);

    if (hmi->backend_framebuffer)
    {
        rt_free(hmi->backend_framebuffer);
    }
    rt_free(hmi);

    rt_thread_delete(rt_thread_self());
}

rt_err_t hmi_start(const char *gdev, const char *idev)
{
    rt_err_t err;
    struct hmi_info *hmi;
    struct rt_thread *loop;

    if (hmi_working)
    {
        rt_kprintf("HMI is running\n");
        return -RT_EBUSY;
    }

    hmi = rt_malloc(sizeof(*hmi));

    if (!hmi)
    {
        return -RT_ENOMEM;
    }

    hmi->gdev = rt_device_find(gdev);
    hmi->idev = rt_device_find(idev);

    if (!hmi->gdev || !hmi->idev)
    {
        rt_free(hmi);
        return -RT_EINVAL;
    }

    if (!rt_bitmap_test_bit(to_input_device(hmi->idev)->cap, EV_ABS))
    {
        rt_kprintf("%s is not a ABS input\n", idev);
        rt_free(hmi);
        return -RT_EINVAL;
    }

    if ((err = rt_device_open(hmi->gdev, 0)))
    {
        rt_free(hmi);
        return err;
    }

    if ((err = rt_device_open(hmi->idev, 0)))
    {
        rt_device_close(hmi->gdev);
        rt_free(hmi);
        return err;
    }

    loop = rt_thread_create("HMI", hmi_loop, hmi,
            DM_THREAD_STACK_SIZE,
            RT_THREAD_PRIORITY_MAX / 3,
            rt_tick_from_millisecond(RT_GRAPHIC_UPDATE_MS));

    if (!loop)
    {
        rt_device_close(hmi->gdev);
        rt_device_close(hmi->idev);
        rt_free(hmi);
        return -RT_ENOMEM;
    }

    hmi_working = RT_TRUE;
    rt_thread_startup(loop);

    return RT_EOK;
}

rt_err_t hmi_stop(void)
{
    hmi_working = RT_FALSE;
    return RT_EOK;
}

#ifdef RT_USING_FINSH
static int _hmi_start(int argc, char**argv)
{
    const char *gdev = "fb0", *idev = "input0";

    if (argc == 3)
    {
        gdev = argv[1];
        idev = argv[2];
    }

    return (int)hmi_start(gdev, idev);
}
MSH_CMD_EXPORT_ALIAS(_hmi_start, hmi_start, e.g: hmi_start("fb0", "input0"));

static int _hmi_stop(void)
{
    return (int)hmi_stop();
}
MSH_CMD_EXPORT_ALIAS(_hmi_stop, hmi_stop, e.g: hmi_exit());
#endif /* RT_USING_FINSH */
#endif /* RT_USING_GRAPHIC && RT_USING_INPUT */
