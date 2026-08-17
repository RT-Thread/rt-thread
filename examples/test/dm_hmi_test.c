/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 * 2026-07-23     GuEe-GUI     support touch input and page flipping
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <cpuport.h>
#include <drivers/lcd.h>
#include <drivers/misc.h>

#if defined(RT_USING_GRAPHIC) && defined(RT_USING_INPUT)

#define HMI_CURSOR_WIDTH        64
#define HMI_CURSOR_HEIGHT       64
#define HMI_MAX_MT_SLOTS        16
#define HMI_MAX_INPUT_DEVICES   32
#define HMI_MAX_GRAPHIC_DEVICES 8

struct hmi_info
{
    struct rt_device *gdev;
    struct rt_device *idev;

    struct rt_device_graphic_info info;
    struct fb_var_screeninfo      var;
    struct rt_device_notify event_notify;
    struct rt_input_handler handler;
    struct rt_semaphore           wakeup;

    volatile rt_bool_t running;
    volatile rt_bool_t dirty;
    volatile rt_bool_t reconfigure;
    rt_bool_t          powered;
    rt_bool_t          notify_installed;
    rt_bool_t          handler_installed;
    rt_bool_t keydown;
    rt_bool_t          multitouch;

    rt_uint32_t dx;
    rt_uint32_t dy;
    rt_uint32_t bytes_per_pixel;
    rt_uint32_t mt_x[HMI_MAX_MT_SLOTS];
    rt_uint32_t mt_y[HMI_MAX_MT_SLOTS];
    rt_int32_t  mt_slot;
    rt_ubase_t  mt_active;
    rt_ubase_t line[2];
    rt_ubase_t colors[4];

    rt_size_t frame_len;
    rt_size_t page_count;
    rt_size_t front_page;
    void     *framebuffer;
};

static struct hmi_info *hmi_active;

static struct rt_input_device *to_input_device(struct rt_device *idev)
{
    return rt_container_of(idev, struct rt_input_device, parent);
}

static rt_ubase_t hmi_color_mask(rt_uint8_t length)
{
    if (!length)
    {
        return 0;
    }

    if (length >= RT_BITS_PER_TYPE(rt_ubase_t))
    {
        return ~0UL;
    }

    return (1UL << length) - 1;
}

static rt_ubase_t hmi_color_component(rt_uint8_t value, rt_ubase_t mask)
{
    return (rt_ubase_t)value * mask / 255;
}

static rt_bool_t hmi_color_field_valid(const struct fb_bitfield *field,
                                       rt_uint32_t               bits_per_pixel)
{
    if (!field->length)
    {
        return RT_TRUE;
    }

    return field->offset < bits_per_pixel &&
           field->length <= bits_per_pixel - field->offset &&
           field->length <= RT_BITS_PER_TYPE(rt_ubase_t);
}

static rt_ubase_t hmi_make_color(struct hmi_info *hmi,
                                 rt_uint8_t red, rt_uint8_t green, rt_uint8_t blue,
                                 rt_uint8_t alpha)
{
    rt_ubase_t red_mask   = hmi_color_mask(hmi->var.red.length);
    rt_ubase_t green_mask = hmi_color_mask(hmi->var.green.length);
    rt_ubase_t blue_mask  = hmi_color_mask(hmi->var.blue.length);
    rt_ubase_t alpha_mask = hmi_color_mask(hmi->var.transp.length);

    return (hmi_color_component(red, red_mask) << hmi->var.red.offset) |
           (hmi_color_component(green, green_mask) << hmi->var.green.offset) |
           (hmi_color_component(blue, blue_mask) << hmi->var.blue.offset) |
           (hmi_color_component(alpha, alpha_mask) << hmi->var.transp.offset);
}

static void hmi_swap_lines(struct hmi_info *hmi)
{
    rt_ubase_t color = hmi->line[0];

    hmi->line[0] = hmi->line[1];
    hmi->line[1] = color;
}

static void hmi_signal(struct hmi_info *hmi)
{
    rt_bool_t wakeup = !hmi->dirty;

    hmi->dirty = RT_TRUE;
    rt_hw_wmb();

    if (wakeup)
    {
        rt_sem_release(&hmi->wakeup);
    }
}

static rt_bool_t hmi_input_supported(struct rt_device *dev,
                                     rt_bool_t        *multitouch)
{
    const char             *name;
    rt_bool_t               mt;
    struct rt_input_device *idev;

    if (!dev)
    {
        return RT_FALSE;
    }

    name = rt_dm_dev_get_name(dev);

    if (!name || rt_strncmp(name, "input", sizeof("input") - 1))
    {
        return RT_FALSE;
    }

    idev = to_input_device(dev);

    if (!rt_bitmap_test_bit(idev->cap, EV_ABS))
    {
        return RT_FALSE;
    }

    mt = rt_bitmap_test_bit(idev->abs_map, ABS_MT_SLOT) &&
         rt_bitmap_test_bit(idev->abs_map, ABS_MT_TRACKING_ID) &&
         rt_bitmap_test_bit(idev->abs_map, ABS_MT_POSITION_X) &&
         rt_bitmap_test_bit(idev->abs_map, ABS_MT_POSITION_Y);

    if (!mt && !(rt_bitmap_test_bit(idev->abs_map, ABS_X) &&
                 rt_bitmap_test_bit(idev->abs_map, ABS_Y)))
    {
        return RT_FALSE;
    }

    if (multitouch)
    {
        *multitouch = mt;
    }

    return RT_TRUE;
}

static struct rt_device *hmi_find_graphic(const char *name)
{
    char              device_name[16];
    struct rt_device *dev;
    int               i;

    if (name && rt_strcmp(name, "auto"))
    {
        return rt_device_find(name);
    }

    for (i = 0; i < HMI_MAX_GRAPHIC_DEVICES; ++i)
    {
        rt_snprintf(device_name, sizeof(device_name), "fb%d", i);

        if ((dev = rt_device_find(device_name)))
        {
            return dev;
        }
    }

    return RT_NULL;
}

static struct rt_device *hmi_find_input(const char *name,
                                        rt_bool_t  *multitouch)
{
    char              device_name[16];
    struct rt_device *dev;
    int               i;

    if (name && rt_strcmp(name, "auto"))
    {
        dev = rt_device_find(name);

        return hmi_input_supported(dev, multitouch) ? dev : RT_NULL;
    }

    for (i = 0; i < HMI_MAX_INPUT_DEVICES; ++i)
    {
        rt_snprintf(device_name, sizeof(device_name), "input%d", i);
        dev = rt_device_find(device_name);

        if (hmi_input_supported(dev, multitouch))
        {
            return dev;
        }
    }

    return RT_NULL;
}

static rt_uint32_t hmi_scale_axis(struct rt_input_device *idev,
                                  rt_uint16_t axis, rt_int32_t value, rt_uint32_t size)
{
    rt_int32_t               min, max;
    struct rt_input_absinfo *absinfo;

    if (!idev->absinfo || axis >= ABS_CNT || size <= 1)
    {
        return 0;
    }

    absinfo = &idev->absinfo[axis];
    min     = absinfo->minimum;
    max     = absinfo->maximum;

    if (max <= min)
    {
        return 0;
    }

    value = rt_clamp(value, min, max);

    return (rt_uint64_t)(value - min) * (size - 1) / (max - min);
}

static void hmi_select_mt_position(struct hmi_info *hmi)
{
    int slot;

    for (slot = 0; slot < HMI_MAX_MT_SLOTS; ++slot)
    {
        if (hmi->mt_active & RT_BIT(slot))
        {
            hmi->dx = hmi->mt_x[slot];
            hmi->dy = hmi->mt_y[slot];
            break;
        }
    }
}

static rt_bool_t hmi_input_callback(struct rt_input_handler *handler,
        struct rt_input_event *ev)
{
    rt_bool_t        down;
    rt_ubase_t       slot_mask;
    struct hmi_info *hmi = handler->priv;

    if (ev->type == EV_ABS)
    {
        if (hmi->multitouch && ev->code == ABS_MT_SLOT)
        {
            hmi->mt_slot = ev->value >= 0 &&
                                   ev->value < HMI_MAX_MT_SLOTS
                               ? ev->value
                               : -1;
        }
        else if (hmi->multitouch && ev->code == ABS_MT_TRACKING_ID &&
                 hmi->mt_slot >= 0)
        {
            slot_mask = RT_BIT(hmi->mt_slot);

            if (ev->value < 0)
            {
                hmi->mt_active &= ~slot_mask;
            }
            else
            {
                hmi->mt_active |= slot_mask;
            }
        }
        else if (ev->code == ABS_X)
        {
            hmi->dx = hmi_scale_axis(handler->idev, ABS_X,
                                     ev->value, hmi->info.width);
        }
        else if (ev->code == ABS_Y)
        {
            hmi->dy = hmi_scale_axis(handler->idev, ABS_Y,
                                     ev->value, hmi->info.height);
        }
        else if (hmi->multitouch && hmi->mt_slot >= 0 &&
                 ev->code == ABS_MT_POSITION_X)
        {
            hmi->mt_x[hmi->mt_slot] = hmi_scale_axis(handler->idev,
                                                     ABS_MT_POSITION_X, ev->value, hmi->info.width);
        }
        else if (hmi->multitouch && hmi->mt_slot >= 0 &&
                 ev->code == ABS_MT_POSITION_Y)
        {
            hmi->mt_y[hmi->mt_slot] = hmi_scale_axis(handler->idev,
                                                     ABS_MT_POSITION_Y, ev->value, hmi->info.height);
        }
    }
    else if (ev->type == EV_KEY && !hmi->multitouch &&
             (ev->code == BTN_LEFT || ev->code == BTN_TOUCH))
    {
        if (hmi->keydown && ev->value == 0)
        {
            hmi_swap_lines(hmi);
        }

        hmi->keydown = ev->value != 0;
    }
    else if (ev->type == EV_SYN && ev->code == SYN_REPORT)
    {
        if (hmi->multitouch)
        {
            down = hmi->mt_active != 0;

            if (hmi->keydown && !down)
            {
                hmi_swap_lines(hmi);
            }

            hmi->keydown = down;

            if (down)
            {
                hmi_select_mt_position(hmi);
            }
        }

        hmi_signal(hmi);
    }

    return RT_FALSE;
}

static void hmi_graphic_notify(rt_device_t dev)
{
    struct hmi_info *hmi = (void *)dev;

    hmi->reconfigure = RT_TRUE;
    hmi_signal(hmi);
}

static void hmi_write_pixel(rt_uint8_t *pixel, rt_ubase_t color,
                            rt_uint32_t bytes_per_pixel)
{
    rt_memcpy(pixel, &color, bytes_per_pixel);
}

static void hmi_fill_span(rt_uint8_t *pixel, rt_uint32_t width,
                          rt_ubase_t color, rt_uint32_t bytes_per_pixel)
{
    rt_uint32_t x;

    switch (bytes_per_pixel)
    {
    case 1:
        rt_memset(pixel, (rt_uint8_t)color, width);
        break;

    case 2:
        for (x = 0; x < width; ++x)
        {
            ((rt_uint16_t *)pixel)[x] = (rt_uint16_t)color;
        }
        break;

    case 4:
        for (x = 0; x < width; ++x)
        {
            ((rt_uint32_t *)pixel)[x] = (rt_uint32_t)color;
        }
        break;

    default:
        for (x = 0; x < width; ++x)
        {
            hmi_write_pixel(pixel, color, bytes_per_pixel);
            pixel += bytes_per_pixel;
        }
        break;
    }
}

static void hmi_fill_rect(struct hmi_info *hmi, rt_uint32_t x,
                          rt_uint32_t y, rt_uint32_t width, rt_uint32_t height,
                          rt_ubase_t color)
{
    rt_uint8_t *row;
    rt_uint32_t line;

    if (!width || !height)
    {
        return;
    }

    row = (rt_uint8_t *)hmi->framebuffer +
          (rt_size_t)y * hmi->info.pitch +
          (rt_size_t)x * hmi->bytes_per_pixel;

    for (line = 0; line < height; ++line)
    {
        hmi_fill_span(row, width, color, hmi->bytes_per_pixel);
        row += hmi->info.pitch;
    }
}

static void hmi_draw_lines(struct hmi_info *hmi,
                           rt_uint32_t x, rt_uint32_t y)
{
    rt_uint8_t *pixel;
    rt_uint32_t line;

    pixel = (rt_uint8_t *)hmi->framebuffer +
            (rt_size_t)y * hmi->info.pitch;
    hmi_fill_span(pixel, hmi->info.width, hmi->line[0],
                  hmi->bytes_per_pixel);

    pixel = (rt_uint8_t *)hmi->framebuffer +
            (rt_size_t)x * hmi->bytes_per_pixel;

    for (line = 0; line < hmi->info.height; ++line)
    {
        hmi_write_pixel(pixel, hmi->line[1], hmi->bytes_per_pixel);
        pixel += hmi->info.pitch;
    }
}

static void hmi_setup_cursor(struct hmi_info *hmi)
{
    rt_ubase_t  color;
    rt_uint8_t *cursor;
    rt_uint8_t *pixel;
    rt_size_t   cursor_len;
    rt_uint32_t count;

    cursor_len = HMI_CURSOR_WIDTH * HMI_CURSOR_HEIGHT *
                 hmi->bytes_per_pixel;
    cursor     = rt_malloc(cursor_len);

    if (!cursor)
    {
        return;
    }

    color = hmi_make_color(hmi, 0x82, 0x50, 0xdf, 0xcc);
    pixel = cursor;

    for (count = 0; count < HMI_CURSOR_WIDTH * HMI_CURSOR_HEIGHT; ++count)
    {
        hmi_write_pixel(pixel, color, hmi->bytes_per_pixel);
        pixel += hmi->bytes_per_pixel;
    }

    rt_device_control(hmi->gdev, RT_DEVICE_CTRL_CURSOR_SET_TYPE, cursor);
    rt_free(cursor);
}

static rt_err_t hmi_configure(struct hmi_info *hmi)
{
    rt_err_t                 err;
    rt_uint32_t              slot;
    rt_size_t                frame_len, page_count, front_page;
    struct fb_fix_screeninfo fix;
    void                    *framebuffer;

    if ((err = rt_device_control(hmi->gdev,
                                 RTGRAPHIC_CTRL_GET_INFO, &hmi->info)))
    {
        return err;
    }

    if ((err = rt_device_control(hmi->gdev,
                                 FBIOGET_VSCREENINFO, &hmi->var)))
    {
        return err;
    }

    if (!hmi->info.framebuffer || !hmi->info.width || !hmi->info.height ||
        !hmi->info.pitch || !hmi->info.bits_per_pixel ||
        hmi->info.bits_per_pixel % 8)
    {
        return -RT_EINVAL;
    }

    hmi->bytes_per_pixel = hmi->info.bits_per_pixel / 8;

    if (!hmi->bytes_per_pixel ||
        hmi->bytes_per_pixel > sizeof(rt_ubase_t) ||
        hmi->info.width > hmi->info.pitch / hmi->bytes_per_pixel ||
        !hmi_color_field_valid(&hmi->var.red,
                               hmi->info.bits_per_pixel) ||
        !hmi_color_field_valid(&hmi->var.green,
                               hmi->info.bits_per_pixel) ||
        !hmi_color_field_valid(&hmi->var.blue,
                               hmi->info.bits_per_pixel) ||
        !hmi_color_field_valid(&hmi->var.transp,
                               hmi->info.bits_per_pixel) ||
        hmi->info.pitch > (rt_size_t)-1 / hmi->info.height)
    {
        return -RT_EINVAL;
    }

    frame_len  = (rt_size_t)hmi->info.pitch * hmi->info.height;
    page_count = hmi->info.smem_len / frame_len;

    if (!page_count)
    {
        return -RT_EINVAL;
    }

    if (page_count > 1)
    {
        rt_memset(&fix, 0, sizeof(fix));

        if (rt_device_control(hmi->gdev, FBIOGET_FSCREENINFO, &fix) ||
            !fix.ypanstep)
        {
            page_count = 1;
        }
    }

    framebuffer = rt_malloc(frame_len);

    if (!framebuffer)
    {
        return -RT_ENOMEM;
    }

    front_page = hmi->var.yoffset / hmi->info.height;

    if (front_page >= page_count)
    {
        front_page = 0;
    }

    if (page_count > 1)
    {
        hmi->var.pixclock = 0;
        hmi->var.activate = FB_ACTIVATE_NOW;

        if ((err = rt_device_control(hmi->gdev,
                                     FBIOPUT_VSCREENINFO, &hmi->var)))
        {
            rt_free(framebuffer);
            return err;
        }
    }

    if (hmi->framebuffer)
    {
        rt_free(hmi->framebuffer);
    }

    hmi->framebuffer = framebuffer;
    hmi->frame_len   = frame_len;
    hmi->page_count  = page_count;
    hmi->front_page  = front_page;

    hmi->line[0]   = hmi_make_color(hmi, 0xff, 0xff, 0xff, 0xff);
    hmi->line[1]   = hmi_make_color(hmi, 0x00, 0x00, 0x00, 0xff);
    hmi->colors[0] = hmi_make_color(hmi, 0xff, 0x4b, 0x00, 0xff);
    hmi->colors[1] = hmi_make_color(hmi, 0x7f, 0xdb, 0x3b, 0xff);
    hmi->colors[2] = hmi_make_color(hmi, 0x00, 0xa4, 0xef, 0xff);
    hmi->colors[3] = hmi_make_color(hmi, 0xff, 0xb8, 0x1c, 0xff);

    if (hmi->dx >= hmi->info.width || hmi->dy >= hmi->info.height)
    {
        hmi->dx = hmi->info.width / 2;
        hmi->dy = hmi->info.height / 2;
    }

    for (slot = 0; slot < HMI_MAX_MT_SLOTS; ++slot)
    {
        if (hmi->mt_x[slot] >= hmi->info.width)
        {
            hmi->mt_x[slot] = hmi->dx;
        }

        if (hmi->mt_y[slot] >= hmi->info.height)
        {
            hmi->mt_y[slot] = hmi->dy;
        }
    }

    rt_memset(hmi->framebuffer, 0, hmi->frame_len);
    hmi_setup_cursor(hmi);

    return RT_EOK;
}

static rt_err_t hmi_present(struct hmi_info *hmi)
{
    rt_err_t                   err;
    rt_ubase_t                 cursor_position;
    rt_uint32_t                x, y;
    struct rt_device_rect_info rect;
    struct fb_var_screeninfo   var;

    x = rt_min(hmi->dx, (rt_uint32_t)hmi->info.width - 1);
    y = rt_min(hmi->dy, (rt_uint32_t)hmi->info.height - 1);

    hmi_fill_rect(hmi, 0, 0, x, y, hmi->colors[0]);
    hmi_fill_rect(hmi, x, 0, hmi->info.width - x, y, hmi->colors[1]);
    hmi_fill_rect(hmi, 0, y, x, hmi->info.height - y, hmi->colors[2]);
    hmi_fill_rect(hmi, x, y, hmi->info.width - x,
                  hmi->info.height - y, hmi->colors[3]);
    hmi_draw_lines(hmi, x, y);

    if (hmi->page_count > 1)
    {
        rt_size_t   back_page   = (hmi->front_page + 1) % hmi->page_count;
        rt_uint8_t *framebuffer = hmi->info.framebuffer;

        rt_memcpy(framebuffer + back_page * hmi->frame_len,
                  hmi->framebuffer, hmi->frame_len);

        var          = hmi->var;
        var.xoffset  = 0;
        var.yoffset  = back_page * hmi->info.height;
        var.activate = FB_ACTIVATE_VBL;
        err          = rt_device_control(hmi->gdev, FBIOPAN_DISPLAY, &var);

        if (err)
        {
            return err;
        }

        hmi->var        = var;
        hmi->front_page = back_page;
    }
    else
    {
        rt_memcpy(hmi->info.framebuffer, hmi->framebuffer, hmi->frame_len);

        rect.x      = 0;
        rect.y      = 0;
        rect.width  = hmi->info.width;
        rect.height = hmi->info.height;

        if ((err = rt_device_control(hmi->gdev,
                                     RTGRAPHIC_CTRL_RECT_UPDATE, &rect)))
        {
            return err;
        }

        if ((err = rt_device_control(hmi->gdev,
                                     RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL)))
        {
            return err;
        }
    }

    cursor_position = RTGRAPHIC_PIXEL_POSITION(x, y);
    rt_device_control(hmi->gdev, RT_DEVICE_CTRL_CURSOR_SET_POSITION,
                      (void *)cursor_position);

    return RT_EOK;
}

static void hmi_cleanup(struct hmi_info *hmi)
{
    struct rt_device_notify notify = { 0 };

    if (hmi->handler_installed)
    {
        rt_input_del_handler(&hmi->handler);
    }

    if (hmi->notify_installed)
    {
        rt_device_control(hmi->gdev, RT_DEVICE_CTRL_NOTIFY_SET, &notify);
    }

    if (hmi->powered)
    {
        rt_device_control(hmi->gdev, RTGRAPHIC_CTRL_POWEROFF, RT_NULL);
    }

    rt_device_close(hmi->idev);
    rt_device_close(hmi->gdev);

    if (hmi->framebuffer)
    {
        rt_free(hmi->framebuffer);
    }

    rt_sem_detach(&hmi->wakeup);
    hmi_active = RT_NULL;
    rt_free(hmi);
}

static void hmi_loop(void *param)
{
    rt_err_t         err = RT_EOK;
    rt_uint32_t      slot;
    struct hmi_info *hmi = param;

    hmi->event_notify.notify = hmi_graphic_notify;
    hmi->event_notify.dev    = (void *)hmi;

    if ((err = rt_device_control(hmi->gdev,
                                 RT_DEVICE_CTRL_NOTIFY_SET, &hmi->event_notify)))
    {
        goto _exit;
    }
    hmi->notify_installed = RT_TRUE;

    if ((err = rt_device_control(hmi->gdev,
                                 RTGRAPHIC_CTRL_POWERON, RT_NULL)))
    {
        goto _exit;
    }
    hmi->powered = RT_TRUE;

    if ((err = hmi_configure(hmi)))
    {
        goto _exit;
    }

    hmi->dx = hmi->info.width / 2;
    hmi->dy = hmi->info.height / 2;

    for (slot = 0; slot < HMI_MAX_MT_SLOTS; ++slot)
    {
        hmi->mt_x[slot] = hmi->dx;
        hmi->mt_y[slot] = hmi->dy;
    }

    hmi->handler.idev     = to_input_device(hmi->idev);
    hmi->handler.callback = hmi_input_callback;
    hmi->handler.priv     = hmi;

    if ((err = rt_input_add_handler(&hmi->handler)))
    {
        goto _exit;
    }
    hmi->handler_installed = RT_TRUE;

    while (hmi->running)
    {
        if (hmi->reconfigure)
        {
            hmi->reconfigure = RT_FALSE;
            rt_hw_wmb();

            if ((err = hmi_configure(hmi)))
            {
                break;
            }

            hmi->dirty = RT_TRUE;
        }

        if (hmi->dirty)
        {
            hmi->dirty = RT_FALSE;
            rt_hw_wmb();

            if ((err = hmi_present(hmi)))
            {
                break;
            }
        }

        if (hmi->running)
        {
            rt_sem_take(&hmi->wakeup, RT_WAITING_FOREVER);
        }
    }

_exit:
    if (err)
    {
        rt_kprintf("HMI stopped: %s\n", rt_strerror(err));
    }

    hmi_cleanup(hmi);
    rt_thread_delete(rt_thread_self());
}

rt_err_t hmi_start(const char *gdev_name, const char *idev_name)
{
    rt_err_t err;
    struct hmi_info *hmi;
    struct rt_thread *loop;

    if (hmi_active)
    {
        rt_kprintf("HMI is running\n");
        return -RT_EBUSY;
    }

    hmi = rt_calloc(1, sizeof(*hmi));

    if (!hmi)
    {
        return -RT_ENOMEM;
    }

    hmi->gdev = hmi_find_graphic(gdev_name);
    hmi->idev = hmi_find_input(idev_name, &hmi->multitouch);

    if (!hmi->gdev || !hmi->idev)
    {
        rt_kprintf("No compatible graphic/input device found\n");
        rt_free(hmi);
        return -RT_ENOENT;
    }

    hmi->mt_slot = -1;
    hmi->running = RT_TRUE;
    hmi->dirty   = RT_TRUE;

    if ((err = rt_sem_init(&hmi->wakeup, "hmi", 0, RT_IPC_FLAG_FIFO)))
    {
        rt_free(hmi);
        return err;
    }

    if ((err = rt_device_open(hmi->gdev, 0)))
    {
        rt_sem_detach(&hmi->wakeup);
        rt_free(hmi);
        return err;
    }

    if ((err = rt_device_open(hmi->idev, 0)))
    {
        rt_device_close(hmi->gdev);
        rt_sem_detach(&hmi->wakeup);
        rt_free(hmi);
        return err;
    }

    loop = rt_thread_create("HMI", hmi_loop, hmi,
                            DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 3, 10);

    if (!loop)
    {
        rt_device_close(hmi->idev);
        rt_device_close(hmi->gdev);
        rt_sem_detach(&hmi->wakeup);
        rt_free(hmi);
        return -RT_ENOMEM;
    }

    hmi_active = hmi;

    if ((err = rt_thread_startup(loop)))
    {
        hmi_active = RT_NULL;
        rt_thread_delete(loop);
        rt_device_close(hmi->idev);
        rt_device_close(hmi->gdev);
        rt_sem_detach(&hmi->wakeup);
        rt_free(hmi);
        return err;
    }

    rt_kprintf("HMI: %s + %s (%s input)\n",
               rt_dm_dev_get_name(hmi->gdev),
               rt_dm_dev_get_name(hmi->idev),
               hmi->multitouch ? "multitouch" : "pointer");

    return RT_EOK;
}

rt_err_t hmi_stop(void)
{
    struct hmi_info *hmi = hmi_active;

    if (!hmi)
    {
        return -RT_ENOSYS;
    }

    hmi->running = RT_FALSE;
    rt_hw_wmb();
    rt_sem_release(&hmi->wakeup);

    return RT_EOK;
}

#ifdef RT_USING_FINSH
static int _hmi_start(int argc, char **argv)
{
    const char *gdev = RT_NULL;
    const char *idev = RT_NULL;

    if (argc > 3)
    {
        rt_kprintf("Usage: hmi_start [fbN|auto] [inputN|auto]\n");
        return -RT_EINVAL;
    }

    if (argc > 1)
    {
        gdev = argv[1];
    }

    if (argc > 2)
    {
        idev = argv[2];
    }

    return (int)hmi_start(gdev, idev);
}
MSH_CMD_EXPORT_ALIAS(_hmi_start, hmi_start,
                     auto select devices e.g.hmi_start or hmi_start fb0 input1);

static int _hmi_stop(void)
{
    return (int)hmi_stop();
}
MSH_CMD_EXPORT_ALIAS(_hmi_stop, hmi_stop, stop HMI test);
#endif /* RT_USING_FINSH */
#endif /* RT_USING_GRAPHIC && RT_USING_INPUT */
