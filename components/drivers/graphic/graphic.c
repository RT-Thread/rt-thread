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

#define DBG_TAG "rtdm.graphic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define raw_to_graphic(dev) rt_container_of(dev, struct rt_graphic_device, parent)

struct fb_format
{
    rt_uint32_t mode;
    rt_uint32_t bits_per_pixel;
    struct fb_bitfield red;
    struct fb_bitfield green;
    struct fb_bitfield blue;
    struct fb_bitfield transp;
};

static const struct fb_format graphic_formats[] =
{
    { RTGRAPHIC_PIXEL_FORMAT_GRAY4,         4,  },
    { RTGRAPHIC_PIXEL_FORMAT_GRAY16,        16, },
    { RTGRAPHIC_PIXEL_FORMAT_RGB332,        8,  {  5, 3 }, { 2, 3 }, {  0, 2 }, },
    { RTGRAPHIC_PIXEL_FORMAT_RGB444,        12, {  8, 4 }, { 4, 4 }, {  0, 4 }, },
    { RTGRAPHIC_PIXEL_FORMAT_RGB565,        16, { 11, 5 }, { 5, 6 }, {  0, 5 }, },
    { RTGRAPHIC_PIXEL_FORMAT_RGB565P,       16, {  0, 5 }, { 5, 6 }, { 11, 5 }, },
    { RTGRAPHIC_PIXEL_FORMAT_BGR565,        16, {  0, 5 }, { 5, 6 }, { 11, 5 }, },
    { RTGRAPHIC_PIXEL_FORMAT_RGB666,        18, { 12, 6 }, { 6, 6 }, {  0, 6 }, },
    { RTGRAPHIC_PIXEL_FORMAT_RGB888,        24, { 16, 8 }, { 8, 8 }, {  0, 8 }, },
    { RTGRAPHIC_PIXEL_FORMAT_BGR888,        24, {  0, 8 }, { 8, 8 }, { 16, 8 }, },
    { RTGRAPHIC_PIXEL_FORMAT_ARGB888,       32, { 16, 8 }, { 8, 8 }, {  0, 8 }, { 24, 8 }, },
    { RTGRAPHIC_PIXEL_FORMAT_ABGR888,       32, {  0, 8 }, { 8, 8 }, { 16, 8 }, { 24, 8 }, },
};

/* RT-Thread device max id is 255 */
static rt_uint8_t fbcon_map[256] = {};

static struct rt_dm_ida graphic_ida = RT_DM_IDA_INIT(GRAPHIC_FRAMEBUFFER);

rt_inline void spin_lock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_lock(&spinlock->lock);
}

rt_inline void spin_unlock(struct rt_spinlock *spinlock)
{
    rt_hw_spin_unlock(&spinlock->lock);
}

static rt_bool_t plane_need_update(struct rt_graphic_plane *plane)
{
    if (plane->ops->update)
    {
        if (!plane->graphic->update_timer)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static struct rt_graphic_plane *plane_get_current(struct rt_graphic_device *gdev)
{
    if (gdev->ops->current_plane)
    {
        return gdev->ops->current_plane(gdev);
    }

    return gdev->primary_plane;
}

static rt_err_t plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    rt_err_t err;

    if (plane->ops->fb_cleanup && (err = plane->ops->fb_cleanup(plane)))
    {
        return err;
    }

    if (!(err = plane->ops->fb_remap(plane, mode, rect)))
    {
        plane->mode = mode;
        plane->x = rect->x;
        plane->y = rect->y;
        plane->width = rect->width;
        plane->height = rect->height;
    }

    return err;
}

static rt_err_t plane_fb_pan_display(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    void *framebuffer_end = plane->framebuffer;
    rt_size_t byte_per_pixel = plane->bits_per_pixel / 8;

    framebuffer_end += rect->x * byte_per_pixel;
    framebuffer_end += rect->y * plane->line_length;
    framebuffer_end += rect->width * rect->height * byte_per_pixel;

    if (framebuffer_end < plane->framebuffer + plane->framebuffer_len)
    {
        return plane->ops->fb_pan_display(plane, rect);
    }

    return -RT_EINVAL;
}

static rt_err_t graphic_dpms_switch(struct rt_graphic_device *gdev, rt_uint32_t dpms)
{
    rt_err_t err;

    if (!(err = gdev->ops->dpms_switch(gdev, dpms)))
    {
        gdev->dpms = dpms;
    }

    return err;
}

static rt_err_t _graphic_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_graphic_device *gdev = raw_to_graphic(dev);
    struct rt_graphic_plane *plane = gdev->primary_plane;

    if (dev->ref_count > 0 && (oflag & RT_DEVICE_OFLAG_WRONLY))
    {
        return -RT_EBUSY;
    }

    if (plane->ops->fb_pan_display)
    {
        struct rt_device_rect_info rect;

        rect.x = 0;
        rect.y = 0;
        rect.width = plane->width;
        rect.height = plane->height;

        return plane->ops->fb_pan_display(plane, &rect);
    }

    return RT_EOK;
}

static rt_ssize_t _graphic_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_ssize_t res;
    struct rt_graphic_device *gdev = raw_to_graphic(dev);
    struct rt_graphic_plane *plane = gdev->primary_plane;

    res = rt_min_t(rt_ssize_t, plane->framebuffer_len - pos, size);

    if (res > 0)
    {
        rt_memcpy(buffer, plane->framebuffer + pos, res);
    }
    else
    {
        res = 0;
    }

    return res;
}

static rt_ssize_t _graphic_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_ssize_t res;
    struct rt_graphic_device *gdev = raw_to_graphic(dev);
    struct rt_graphic_plane *plane = gdev->primary_plane;

    res = rt_min_t(rt_ssize_t, plane->framebuffer_len - pos, size);

    if (res > 0)
    {
        rt_memcpy(plane->framebuffer + pos, buffer, res);
    }
    else
    {
        res = 0;
    }

    return res;
}

static rt_err_t _graphic_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    rt_bool_t need_schedule = RT_FALSE;
    struct rt_graphic_device *gdev = raw_to_graphic(dev);

_retry:
    if (need_schedule)
    {
        rt_thread_yield();
    }

    spin_lock(&gdev->lock);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CURSOR_SET_POSITION:
        if (args)
        {
            struct rt_graphic_plane *plane = gdev->cursor_plane;

            if (plane)
            {
                rt_uint32_t position = (rt_uint32_t)(rt_ubase_t)args;

                plane->x = position >> 16;
                plane->y = position & 0xffff;

                if (plane_need_update(plane))
                {
                    struct rt_device_rect_info rect;

                    rect.x = plane->x;
                    rect.y = plane->y;
                    /* Ask driver to update position only */
                    rect.width = 0;
                    rect.height = 0;

                    err = plane->ops->update(plane, &rect);
                }
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RT_DEVICE_CTRL_CURSOR_SET_TYPE:
        if (args)
        {
            struct rt_graphic_plane *plane = gdev->cursor_plane;

            if (plane)
            {
                struct rt_device_rect_info rect =
                {
                    .x = 0,
                    .y = 0,
                    .width = plane->width,
                    .height = plane->height,
                };

                if (!plane->framebuffer)
                {
                    rt_uint32_t mode;

                    if (plane->mode == RTGRAPHIC_PIXEL_FORMAT_MONO)
                    {
                        mode = plane->modes[0];
                    }
                    else
                    {
                        mode = plane->mode;
                    }

                    if ((err = plane_fb_remap(plane, mode, &rect)))
                    {
                        break;
                    }
                }

                rt_memcpy(plane->framebuffer, args, plane->screen_len);

                /* Force to update */
                err = plane->ops->update(plane, &rect);
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
        if (args)
        {
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            if (plane_need_update(plane))
            {
                err = plane->ops->update(plane, args);
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_POWERON:
        if (gdev->ops->dpms_switch)
        {
            err = graphic_dpms_switch(gdev, RT_GRAPHIC_DPMS_ON);
        }
    #ifdef RT_GRAPHIC_BACKLIGHT
        if (!err && gdev->backlight)
        {
            spin_unlock(&gdev->lock);
            err = rt_backlight_set_power(gdev->backlight, RT_BACKLIGHT_POWER_NORMAL);
            spin_lock(&gdev->lock);
        }
    #endif /* RT_GRAPHIC_BACKLIGHT */
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        if (gdev->ops->dpms_switch)
        {
            err = graphic_dpms_switch(gdev, RT_GRAPHIC_DPMS_OFF);
        }
    #ifdef RT_GRAPHIC_BACKLIGHT
        if (!err && gdev->backlight)
        {
            spin_unlock(&gdev->lock);
            err = rt_backlight_set_power(gdev->backlight, RT_BACKLIGHT_POWER_POWERDOWN);
            spin_lock(&gdev->lock);
        }
    #endif /* RT_GRAPHIC_BACKLIGHT */
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        if (args)
        {
            struct rt_device_graphic_info *info = args;
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            info->pixel_format = plane->mode;
            info->bits_per_pixel = plane->bits_per_pixel;
            info->pitch = plane->line_length;
            info->width = plane->width;
            info->height = plane->height;
            info->framebuffer = plane->framebuffer;
            info->smem_len = plane->framebuffer_len;
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        if (args)
        {
            rt_uint32_t mode = (rt_uint32_t)(rt_ubase_t)args;
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            if (mode != plane->mode)
            {
                err = -RT_ENOSYS;

                if (plane->modes_nr > 1)
                {
                    for (int i = 0; i < plane->modes_nr; ++i)
                    {
                        if (mode == plane->modes[i])
                        {
                            struct rt_device_rect_info rect =
                            {
                                .x = plane->x,
                                .y = plane->y,
                                .width = plane->width,
                                .height = plane->height,
                            };

                            err = plane_fb_remap(plane, mode, &rect);
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_GET_EXT:
        if (args)
        {
            rt_memcpy(args, &gdev->edid, sizeof(gdev->edid));
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_SET_BRIGHTNESS:
        if (gdev->ops->set_brightness)
        {
            err = gdev->ops->set_brightness(gdev, (rt_uint32_t)(rt_ubase_t)args);
        }
    #ifdef RT_GRAPHIC_BACKLIGHT
        if (!err && gdev->backlight)
        {
            spin_unlock(&gdev->lock);

            return rt_backlight_set_brightness(gdev->backlight, (rt_uint32_t)(rt_ubase_t)args);
        }
    #endif /* RT_GRAPHIC_BACKLIGHT */
        break;

    case RTGRAPHIC_CTRL_GET_BRIGHTNESS:
        if (args)
        {
            if (gdev->ops->get_brightness)
            {
                err = gdev->ops->get_brightness(gdev, args);
            }
            else
            {
                *(rt_uint32_t *)args = RT_UINT32_MAX >> 1;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
    #ifdef RT_GRAPHIC_BACKLIGHT
        if (!err && gdev->backlight)
        {
            spin_unlock(&gdev->lock);

            return rt_backlight_get_brightness(gdev->backlight, args);
        }
    #endif /* RT_GRAPHIC_BACKLIGHT */
        break;

    case RTGRAPHIC_CTRL_GET_MODE:
        if (args)
        {
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            *(rt_uint32_t *)args = plane->mode;
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_GET_STATUS:
        if (args)
        {
            if (gdev->ops->get_status)
            {
                err = gdev->ops->get_status(gdev, args);
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_PAN_DISPLAY:
        if (args)
        {
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            if (plane->ops->fb_pan_display)
            {
                rt_size_t offset;
                struct rt_device_rect_info rect;

                offset = (rt_size_t)(args - plane->framebuffer);

                rect.x = (offset % plane->line_length) / (plane->bits_per_pixel / 8);
                rect.y = offset / plane->line_length;
                rect.width = plane->width;
                rect.height = plane->height;

                err = plane_fb_pan_display(plane, &rect);
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case RTGRAPHIC_CTRL_WAIT_VSYNC:
        if (gdev->ops->wait_vsync)
        {
            err = gdev->ops->wait_vsync(gdev);
        }
        break;

    case RT_DEVICE_CTRL_NOTIFY_SET:
        if (args)
        {
            if (rt_atomic_load(&gdev->event_notifying) == RT_TRUE)
            {
                need_schedule = RT_TRUE;

                spin_unlock(&gdev->lock);
                goto _retry;
            }

            rt_memcpy(&gdev->event_notify, args, sizeof(gdev->event_notify));
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIOGET_VSCREENINFO:
        if (args)
        {
            struct fb_var_screeninfo *var = args;
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            rt_memset(var, 0, sizeof(*var));

            var->xres = plane->width;
            var->yres = plane->height;
            var->xres_virtual = plane->width;
            var->yres_virtual = plane->height * (plane->framebuffer_len / plane->screen_len);
            var->bits_per_pixel = plane->bits_per_pixel;

            if (plane == gdev->primary_plane)
            {
                var->width = gdev->edid.width_cm ? gdev->edid.width_cm * 10 : -1;
                var->height = gdev->edid.height_cm ? gdev->edid.height_cm * 10 : -1;
            }
            else
            {
                var->width = -1;
                var->height = -1;
            }

            if (plane->mode == RTGRAPHIC_PIXEL_FORMAT_GRAY4 ||
                plane->mode == RTGRAPHIC_PIXEL_FORMAT_GRAY16)
            {
                var->grayscale = 1;
            }
            else
            {
                const struct fb_format *fmt = &graphic_formats[0];

                for (int i = 0; i < RT_ARRAY_SIZE(graphic_formats); ++i, ++fmt)
                {
                    if (fmt->mode == plane->mode)
                    {
                        rt_memcpy(&var->red, &fmt->red, sizeof(fmt->red));
                        rt_memcpy(&var->green, &fmt->green, sizeof(fmt->green));
                        rt_memcpy(&var->blue, &fmt->blue, sizeof(fmt->blue));
                        rt_memcpy(&var->transp, &fmt->transp, sizeof(fmt->transp));

                        break;
                    }
                }
            }

            if (gdev->update_timer)
            {
                rt_uint64_t update_ps;
                rt_tick_t update_tick;

                rt_timer_control(gdev->update_timer, RT_TIMER_CTRL_GET_TIME, &update_tick);
                /*
                 *           1s            update_ms * 1000
                 *  -------------------- = ----------------- (second/tick)
                 *   RT_TICK_PER_SECOND       update_tick
                 *
                 *  1000000ps = 1ms
                 */
                update_ps = (update_tick * 1000000) / (RT_TICK_PER_SECOND * 1000);

                var->pixclock = update_ps / (var->xres * var->yres);
            }
            else
            {
                var->pixclock = (RT_GRAPHIC_UPDATE_MS * 1000000) / (var->xres * var->yres);
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIOPUT_VSCREENINFO:
        if (args)
        {
            rt_uint32_t mode;
            struct fb_format fmt;
            struct rt_device_rect_info rect;
            struct fb_var_screeninfo *var = args;
            struct rt_graphic_plane *plane = plane_get_current(gdev);
            const rt_size_t cmp_offset = rt_offsetof(struct fb_format, bits_per_pixel);
            const rt_size_t cmp_size = sizeof(struct fb_format) - cmp_offset;

            if (!plane->ops->fb_pan_display)
            {
                if (var->xres != plane->width || var->yres != plane->height ||
                    var->xoffset != plane->x || var->yoffset != plane->y)
                {
                    err = -RT_ENOSYS;
                    break;
                }
            }

            mode = plane->mode;
            rect.x = plane->x;
            rect.y = plane->y;
            rect.width = plane->width;
            rect.height = plane->height;

            fmt.bits_per_pixel = var->bits_per_pixel;
            rt_memcpy(&fmt.red, &var->red, sizeof(fmt.red));
            rt_memcpy(&fmt.green, &var->green, sizeof(fmt.green));
            rt_memcpy(&fmt.blue, &var->blue, sizeof(fmt.blue));
            rt_memcpy(&fmt.transp, &var->transp, sizeof(fmt.transp));

            for (int i = 0; i < RT_ARRAY_SIZE(graphic_formats); ++i)
            {
                void *cmp_to = ((void *)&fmt) + cmp_offset;
                void *cmp_from = ((void *)&graphic_formats[i]) + cmp_offset;

                if (!rt_memcmp(cmp_to, cmp_from, cmp_size))
                {
                    mode = graphic_formats[i].mode;
                    break;
                }
            }

            err = -RT_ENOSYS;

            for (int i = 0; i < plane->modes_nr; ++i)
            {
                /* Check supported and commit */
                if (plane->modes[i] == mode && plane->mode != mode)
                {
                    err = plane_fb_remap(plane, mode, &rect);
                }
            }

            if (!err && plane->ops->fb_pan_display)
            {
                rect.x = var->xoffset;
                rect.y = var->yoffset;
                rect.width = var->xres;
                rect.height = var->yres;

                err = plane_fb_pan_display(plane, &rect);
            }

            if (!err && var->rotate && plane->ops->prop_set)
            {
                err = plane->ops->prop_set(plane, RT_GRAPHIC_PLANE_PROP_ROTATE,
                        (void *)(rt_ubase_t)((var->rotate % 360) / 90));
            }

            if (!err && plane == gdev->primary_plane && plane->ops->update)
            {
                rt_uint32_t update_ms = 0;

                if (var->pixclock)
                {
                    rt_uint64_t clock_cycles;

                    clock_cycles = var->pixclock;
                    clock_cycles *= rect.width;
                    clock_cycles *= rect.height;
                    /* Seconds in pico seconds */
                    clock_cycles /= 1000000000000ULL;

                    update_ms = (rt_uint32_t)clock_cycles * 1000;
                }

                err = rt_graphic_device_update_auto(gdev, update_ms);
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIOGET_FSCREENINFO:
        if (args)
        {
            struct fb_fix_screeninfo *fix = args;
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            rt_memset(fix, 0, sizeof(*fix));

            rt_snprintf(fix->id, rt_min_t(int, sizeof(fix->id), RT_NAME_MAX),
                    "%s", rt_dm_dev_get_name(&gdev->parent));

            fix->smem_start = (unsigned long)rt_kmem_v2p(plane->framebuffer);
            fix->smem_len = plane->framebuffer_len;
            fix->mmio_start = fix->smem_start;
            fix->mmio_len = plane->screen_len;
            fix->line_length = plane->line_length;
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIOGET_PIXELINFO:
        if (args)
        {
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            *(rt_uint32_t *)args = plane->mode;
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIOPAN_DISPLAY:
        if (args)
        {
            struct fb_var_screeninfo *var = args;
            struct rt_graphic_plane *plane = plane_get_current(gdev);

            if (plane->ops->fb_pan_display)
            {
                struct rt_device_rect_info rect;

                rect.x = var->xoffset;
                rect.y = var->yoffset;
                rect.width = var->xres;
                rect.height = var->yres;

                err = plane_fb_pan_display(plane, &rect);
            }
            else
            {
                err = -RT_ENOSYS;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIO_CURSOR:
        err = -RT_EINVAL;
        break;

    case FBIOGET_CON2FBMAP:
        if (args)
        {
            struct fb_con2fbmap *con2fbmap = args;

            if (con2fbmap->console < RT_ARRAY_SIZE(fbcon_map))
            {
                con2fbmap->framebuffer = fbcon_map[con2fbmap->console];
            }
            else
            {
                err = -RT_EFULL;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIOPUT_CON2FBMAP:
        if (args)
        {
            struct fb_con2fbmap *con2fbmap = args;

            if (con2fbmap->console < RT_ARRAY_SIZE(fbcon_map) &&
                con2fbmap->framebuffer < RT_ARRAY_SIZE(fbcon_map))
            {
                struct rt_device *vt;

                vt = rt_dm_device_find(MASTER_ID_TTY, con2fbmap->console);

            #ifdef RT_SERIAL_VIRTUAL
                if (!vt)
                {
                    vt = rt_device_find("vuart");
                }
            #endif

                if (vt)
                {
                    if (!(err = rt_device_open(vt, RT_DEVICE_OFLAG_RDWR)))
                    {
                        err = rt_device_control(vt, FBIOPUT_CON2FBMAP, con2fbmap);

                        if (!err)
                        {
                            fbcon_map[con2fbmap->console] = con2fbmap->framebuffer;
                        }

                        rt_device_close(vt);
                    }
                }
                else
                {
                    err = -RT_EEMPTY;
                }
            }
            else
            {
                err = -RT_EFULL;
            }
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    case FBIOBLANK:
        if (gdev->ops->dpms_switch)
        {
            rt_uint32_t dpms;

            switch ((rt_uint32_t)(rt_ubase_t)args)
            {
            case FB_BLANK_UNBLANK:
                /* Display: On, HSync: On, VSync: On */
                dpms = RT_GRAPHIC_DPMS_ON;
                break;

            case FB_BLANK_NORMAL:
                /* Display: Off, HSync: On, VSync: On */
                dpms = RT_GRAPHIC_DPMS_STANDBY;
                break;

            case FB_BLANK_HSYNC_SUSPEND:
                /* Display: Off, HSync: Off, VSync: On */
                dpms = RT_GRAPHIC_DPMS_STANDBY;
                break;

            case FB_BLANK_VSYNC_SUSPEND:
                /* Display: Off, HSync: On, VSync: Off */
                dpms = RT_GRAPHIC_DPMS_SUSPEND;
                break;

            case FB_BLANK_POWERDOWN:
                /* Display: Off, HSync: Off, VSync: Off */
                dpms = RT_GRAPHIC_DPMS_OFF;
                break;

            default:
                err = -RT_EINVAL;
                break;
            }

            if (!err)
            {
                graphic_dpms_switch(gdev, dpms);
            }
        }
        break;

    case FBIO_WAITFORVSYNC:
        if (gdev->ops->wait_vsync)
        {
            err = gdev->ops->wait_vsync(gdev);
        }
        break;

    case FBIO_ALLOC:
    case FBIO_FREE:
    case FBIOGET_GLYPH:
    case FBIOGET_HWCINFO:
    case FBIOPUT_MODEINFO:
    case FBIOGET_DISPINFO:
        LOG_D("FB IOCTL (%x) only used for SiS 300/630/730/540/315/550/650/740 frame buffer device", cmd);
        /* Fall through */
    case FBIOGET_VBLANK:
    case FBIOGETCMAP: /* fb_cmap */
    case FBIOPUTCMAP: /* fb_cmap */
        /* Fall through */
    default:
        if (gdev->ops->control)
        {
            err = gdev->ops->control(gdev, cmd, args);
        }
        else
        {
            err = -RT_ENOSYS;
        }
    }

    spin_unlock(&gdev->lock);

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _graphic_ops =
{
    .open = _graphic_open,
    .read = _graphic_read,
    .write = _graphic_write,
    .control = _graphic_control,
};
#endif

static void graphic_ofw_init(struct rt_graphic_device *gdev)
{
#ifdef RT_USING_OFW
    struct rt_ofw_node *np = gdev->parent.ofw_node;

#ifdef RT_GRAPHIC_BACKLIGHT
    if (!gdev->backlight)
    {
        struct rt_ofw_node *bl_np = rt_ofw_parse_phandle(np, "backlight", 0);

        if (bl_np && (gdev->backlight = rt_ofw_data(bl_np)))
        {
            rt_device_open(&gdev->backlight->parent, RT_DEVICE_OFLAG_RDWR);
        }
        rt_ofw_node_put(bl_np);
    }
#endif /* RT_GRAPHIC_BACKLIGHT */

    (void)np;
#endif /* RT_USING_OFW */
}

static void graphic_edid_res(struct rt_graphic_device *gdev,
        rt_uint32_t *out_width, rt_uint32_t *out_height)
{
    struct edid *edid = &gdev->edid;
    struct detailed_timing *dt = &edid->detailed_timings[0];
    struct detailed_pixel_timing *dpt = &dt->data.pixel_data;

    *out_width = dpt->hactive_lo + ((dpt->hactive_hblank_hi & 0xf0) << 4);
    *out_height = dpt->vactive_lo + ((dpt->vactive_vblank_hi & 0xf0) << 4);
}

#ifdef RT_USING_PM
static rt_err_t _graphic_pm_dpms_switch(struct rt_graphic_device *gdev, rt_uint8_t mode)
{
    rt_err_t err;

    spin_lock(&gdev->lock);

    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
    case PM_SLEEP_MODE_IDLE:
    case PM_SLEEP_MODE_LIGHT:
    case PM_SLEEP_MODE_DEEP:
        err = graphic_dpms_switch(gdev, RT_GRAPHIC_DPMS_ON);
        break;

    case PM_SLEEP_MODE_STANDBY:
        err = graphic_dpms_switch(gdev, RT_GRAPHIC_DPMS_STANDBY);
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        err = graphic_dpms_switch(gdev, RT_GRAPHIC_DPMS_OFF);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    spin_unlock(&gdev->lock);

    return err;
}

static rt_err_t _graphic_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    struct rt_graphic_device *gdev = raw_to_graphic(device);

    return _graphic_pm_dpms_switch(gdev, mode);
}

static void _graphic_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    struct rt_graphic_device *gdev = raw_to_graphic(device);

    _graphic_pm_dpms_switch(gdev, mode);
}

static const struct rt_device_pm_ops _graphic_pm_ops =
{
    .suspend = _graphic_pm_suspend,
    .resume = _graphic_pm_resume,
};
#endif /* RT_USING_PM */

rt_err_t rt_graphic_device_register(struct rt_graphic_device *gdev)
{
    rt_err_t err;
    int device_id;
    const char *dev_name;

    if (!gdev || !gdev->ops)
    {
        return -RT_EINVAL;
    }

    if (!gdev->primary_plane)
    {
        LOG_E("%s: Not %s found", rt_dm_dev_get_name(&gdev->parent), "primary plane");

        return -RT_EINVAL;
    }

    if ((device_id = rt_dm_ida_alloc(&graphic_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_dm_dev_set_name(&gdev->parent, "fb%u", device_id);
    dev_name = rt_dm_dev_get_name(&gdev->parent);

    rt_list_init(&gdev->overlay_nodes);
    rt_dm_ida_init(&gdev->plane_ida, CUSTOM);
    rt_spin_lock_init(&gdev->lock);

    graphic_ofw_init(gdev);

    if (!gdev->primary_plane->width || !gdev->primary_plane->height)
    {
        rt_uint32_t mode, width, height;
        struct rt_device_rect_info rect;

        graphic_edid_res(gdev, &width, &height);
        rect.x = 0;
        rect.y = 0;
        rect.width = width;
        rect.height = height;

        if (gdev->primary_plane->mode == RTGRAPHIC_PIXEL_FORMAT_MONO)
        {
            mode = gdev->primary_plane->modes[0];
        }
        else
        {
            mode = gdev->primary_plane->mode;
        }

        err = plane_fb_remap(gdev->primary_plane, mode, &rect);

        if (err)
        {
            LOG_E("%s: Set %s error = %s", rt_dm_dev_get_name(&gdev->parent),
                    "primary plane", rt_strerror(err));

            goto _fail;
        }
    }

    gdev->parent.type = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    gdev->parent.ops = &_graphic_ops;
#else
    gdev->parent.open = _graphic_open;
    gdev->parent.read = _graphic_read;
    gdev->parent.write = _graphic_write;
    gdev->parent.control = _graphic_control;
#endif
    gdev->parent.master_id = graphic_ida.master_id;
    gdev->parent.device_id = device_id;

    if ((err = rt_device_register(&gdev->parent, dev_name, RT_DEVICE_FLAG_RDWR)))
    {
        goto _fail;
    }

#ifdef RT_USING_PM
    rt_pm_device_register(&gdev->parent, &_graphic_pm_ops);
#endif

    if ((err = rt_graphic_logo_render(gdev)))
    {
        LOG_D("Logo render error = %s", rt_strerror(err));
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&graphic_ida, device_id);

    return err;
}

rt_err_t rt_graphic_device_unregister(struct rt_graphic_device *gdev)
{
    const char *dev_name;
    struct rt_graphic_plane *plane, *plane_next;

    if (!gdev)
    {
        return -RT_EINVAL;
    }

    dev_name = rt_dm_dev_get_name(&gdev->parent);

    if (gdev->parent.ref_count)
    {
        LOG_E("%s: there is %u user", dev_name, gdev->parent.ref_count);
        return -RT_EINVAL;
    }

#ifdef RT_USING_PM
    rt_pm_device_unregister(&gdev->parent);
#endif

    rt_graphic_device_update_auto(gdev, 0);

    if (gdev->ops->dpms_switch)
    {
        graphic_dpms_switch(gdev, RT_GRAPHIC_DPMS_OFF);
    }
#ifdef RT_GRAPHIC_BACKLIGHT
    if (gdev->backlight)
    {
        rt_backlight_set_power(gdev->backlight, RT_BACKLIGHT_POWER_POWERDOWN);
        rt_device_close(&gdev->backlight->parent);
    }
#endif

    rt_list_for_each_entry_safe(plane, plane_next, &gdev->overlay_nodes, list)
    {
        rt_graphic_device_del_plane(gdev, plane);
        rt_graphic_device_free_plane(plane);
    }

    rt_graphic_device_del_plane(gdev, gdev->primary_plane);
    rt_graphic_device_free_plane(gdev->primary_plane);

    if (gdev->cursor_plane)
    {
        rt_graphic_device_del_plane(gdev, gdev->cursor_plane);
        rt_graphic_device_free_plane(gdev->cursor_plane);
    }

    rt_dm_ida_free(&graphic_ida, gdev->parent.device_id);

    rt_device_unregister(&gdev->parent);

    return RT_EOK;
}

struct rt_graphic_plane *rt_graphic_device_alloc_plane(struct rt_graphic_device *gdev,
        rt_size_t priv_size, const struct rt_graphic_plane_ops *ops,
        const rt_uint32_t *modes, rt_uint32_t modes_nr, rt_uint8_t type)
{
    struct rt_graphic_plane *plane = RT_NULL;

    if (!gdev || !ops || !modes || !modes_nr || type > RT_GRAPHIC_PLANE_TYPE_CURSOR)
    {
        return RT_NULL;
    }

    plane = rt_calloc(1, sizeof(*plane) + priv_size);

    if (plane)
    {
        rt_list_init(&plane->list);
        plane->type = type;
        plane->modes_nr = modes_nr;
        plane->modes = modes;
        plane->mode = RTGRAPHIC_PIXEL_FORMAT_MONO;
        plane->graphic = gdev;
        plane->ops = ops;
    }

    return plane;
}

void rt_graphic_device_free_plane(struct rt_graphic_plane *plane)
{
    if (!plane)
    {
        return;
    }

    rt_free(plane);
}

rt_err_t rt_graphic_device_add_plane(struct rt_graphic_device *gdev,
        struct rt_graphic_plane *plane)
{
    rt_err_t err = RT_EOK;

    if (!gdev || !plane)
    {
        return -RT_EINVAL;
    }

    if (!plane->ops)
    {
        LOG_E("%s: %s have no plane ops",
                rt_dm_dev_get_name(&gdev->parent), plane->name);
        return -RT_EINVAL;
    }

    plane->id = rt_dm_ida_alloc(&gdev->plane_ida);

    if (plane->id == RT_DM_IDA_NUM)
    {
        LOG_E("%s: %s is out of plane max(%d)",
                rt_dm_dev_get_name(&gdev->parent), plane->name, RT_DM_IDA_NUM - 1);
        return -RT_EFULL;
    }

    if (plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        if (gdev->primary_plane)
        {
            err = -RT_EINVAL;
            goto _free_ida;
        }
        if (!plane->name[0])
        {
            rt_strncpy(plane->name, "primary", sizeof(plane->name));
        }
        gdev->primary_plane = plane;
    }
    else if (plane->type == RT_GRAPHIC_PLANE_TYPE_CURSOR)
    {
        if (gdev->cursor_plane)
        {
            err = -RT_EINVAL;
            goto _free_ida;
        }
        if (!plane->name[0])
        {
            rt_strncpy(plane->name, "cursor", sizeof(plane->name));
        }
        gdev->cursor_plane = plane;
    }
    else if (plane->type == RT_GRAPHIC_PLANE_TYPE_OVERLAY)
    {
        if (!plane->name[0])
        {
            rt_snprintf(plane->name, sizeof(plane->name), "overlay-%u", plane->id);
        }
        spin_lock(&gdev->lock);
        rt_list_insert_before(&gdev->overlay_nodes, &plane->list);
        rt_graphic_device_leave(gdev);
    }
    else
    {
        LOG_E("What the fuck plane type(%u)", plane->type);
        RT_ASSERT(0);
    }

_free_ida:
    if (err)
    {
        rt_dm_ida_free(&gdev->plane_ida, plane->id);
    }

    return err;
}

rt_err_t rt_graphic_device_del_plane(struct rt_graphic_device *gdev,
        struct rt_graphic_plane *plane)
{
    if (!gdev || !plane)
    {
        return -RT_EINVAL;
    }

    if (plane->ops->fb_cleanup)
    {
        /* Ignore error */
        plane->ops->fb_cleanup(plane);
    }

    if (plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        gdev->primary_plane = RT_NULL;
    }
    else if (plane->type == RT_GRAPHIC_PLANE_TYPE_CURSOR)
    {
        gdev->cursor_plane = RT_NULL;
    }
    else if (plane->type == RT_GRAPHIC_PLANE_TYPE_OVERLAY)
    {
        spin_lock(&gdev->lock);
        rt_list_remove(&plane->list);
        spin_unlock(&gdev->lock);
    }

    rt_dm_ida_free(&gdev->plane_ida, plane->id);

    return RT_EOK;
}

void rt_graphic_device_hotplug_event(struct rt_graphic_device *gdev)
{
    rt_err_t err;
    rt_uint32_t width, height;
    struct rt_device_rect_info rect;

    RT_ASSERT(gdev != RT_NULL);

    rt_graphic_device_enter(gdev);

    graphic_edid_res(gdev, &width, &height);
    rect.x = 0;
    rect.y = 0;
    rect.width = width;
    rect.height = height;

    err = plane_fb_remap(gdev->primary_plane, gdev->primary_plane->mode, &rect);

    if (err)
    {
        /* What the fuck? */
        LOG_E("%s: hotplug event process error = %s",
                rt_dm_dev_get_name(&gdev->parent), rt_strerror(err));
        goto _out_lock;
    }

_out_lock:
    rt_graphic_device_leave(gdev);

    rt_atomic_store(&gdev->event_notifying, RT_TRUE);

    if (gdev->event_notify.notify)
    {
        gdev->event_notify.notify(gdev->event_notify.dev);
    }

    rt_atomic_store(&gdev->event_notifying, RT_FALSE);
}

static void graphic_device_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    if (plane->ops->update)
    {
        plane->ops->update(plane, rect);
    }
}

static void graphic_device_update(void *param)
{
    struct rt_device_rect_info rect;
    struct rt_graphic_plane *plane;
    struct rt_graphic_device *gdev = param;

    rect.x = 0;
    rect.y = 0;

    spin_lock(&gdev->lock);

    rect.width = gdev->primary_plane->width;
    rect.height = gdev->primary_plane->height;
    graphic_device_plane_update(gdev->primary_plane, &rect);

    rt_list_for_each_entry(plane, &gdev->overlay_nodes, list)
    {
        rect.width = plane->width;
        rect.height = plane->height;

        graphic_device_plane_update(plane, &rect);
    }

    if ((plane = gdev->cursor_plane))
    {
        rect.x = plane->x;
        rect.y = plane->y;
        /* Ask driver to update position only */
        rect.width = 0;
        rect.height = 0;

        graphic_device_plane_update(plane, &rect);
    }

    spin_unlock(&gdev->lock);
}

rt_err_t rt_graphic_device_update_auto(struct rt_graphic_device *gdev, rt_uint32_t update_ms)
{
    if (!gdev)
    {
        return -RT_EINVAL;
    }

    if (update_ms)
    {
        if (!gdev->update_timer)
        {
            char name[RT_NAME_MAX];

            rt_snprintf(name, sizeof(name), "update-%s", rt_dm_dev_get_name(&gdev->parent));

            gdev->update_timer = rt_timer_create(name, &graphic_device_update, gdev,
                    rt_tick_from_millisecond(update_ms),
                    RT_TIMER_FLAG_PERIODIC);

            if (!gdev->update_timer)
            {
                return -RT_ENOMEM;
            }
        }

        rt_timer_start(gdev->update_timer);
    }
    else if (gdev->update_timer)
    {
        rt_timer_stop(gdev->update_timer);
        rt_timer_delete(gdev->update_timer);

        gdev->update_timer = RT_NULL;
    }

    return RT_EOK;
}

void rt_graphic_device_enter(struct rt_graphic_device *gdev)
{
    RT_ASSERT(gdev != RT_NULL);

    spin_lock(&gdev->lock);

    if (gdev->update_timer)
    {
        rt_timer_stop(gdev->update_timer);
    }
}

void rt_graphic_device_leave(struct rt_graphic_device *gdev)
{
    RT_ASSERT(gdev != RT_NULL);

    if (gdev->update_timer)
    {
        rt_timer_start(gdev->update_timer);
    }

    spin_unlock(&gdev->lock);
}

rt_uint32_t rt_graphic_mode_bpp(rt_uint32_t mode)
{
    for (int i = 0; i < RT_ARRAY_SIZE(graphic_formats); ++i)
    {
        if (graphic_formats[i].mode == mode)
        {
            return graphic_formats[i].bits_per_pixel;
        }
    }

    return 0;
}
