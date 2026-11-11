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

#define DBG_TAG "fb.bcm2708"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <firmware-raspberrypi.h>

#define MAX_FRAMEBUFFERS       3
#define FRAMEBUFFER_ALIGNMENT  4096

struct fb_alloc_tags
{
    struct rpi_firmware_property_tag_header tag1;
    rt_uint32_t xres, yres;

    struct rpi_firmware_property_tag_header tag2;
    rt_uint32_t xres_virtual, yres_virtual;

    struct rpi_firmware_property_tag_header tag3;
    rt_uint32_t bpp;

    struct rpi_firmware_property_tag_header tag4;
    rt_uint32_t xoffset, yoffset;

    struct rpi_firmware_property_tag_header tag5;
    rt_uint32_t base, screen_size;

    struct rpi_firmware_property_tag_header tag6;
    rt_uint32_t pitch;
};

struct vc4_display_settings
{
    rt_uint32_t display_num;
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t depth;
    rt_uint32_t pitch;
    rt_uint32_t virtual_width;
    rt_uint32_t virtual_height;
    rt_uint32_t virtual_width_offset;
    rt_uint32_t virtual_height_offset;
    rt_ubase_t fb_bus_address;
};

struct bcm2708fb;

struct bcm2708fb_display
{
    struct rt_graphic_device parent;

    struct bcm2708fb *fb;

    void *framebuffer;
    rt_ubase_t framebuffer_dma;
    rt_size_t framebuffer_size;
    rt_size_t stride;

    struct vc4_display_settings display_settings;
    struct { rt_uint32_t base, length; } gpu_mem;
};

struct bcm2708fb
{
    struct rpi_firmware *rpi_fw;

    struct bcm2708fb_display displays[MAX_FRAMEBUFFERS];
};

static rt_err_t bcm2708fb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    struct bcm2708fb_display *display;

    display = rt_container_of(plane->graphic, struct bcm2708fb_display, parent);

    plane->line_length = display->stride;
    plane->bits_per_pixel = rt_graphic_mode_bpp(mode);

    plane->framebuffer = display->framebuffer;
    plane->screen_len = display->framebuffer_size;
    plane->framebuffer_len = display->framebuffer_size;

    return RT_EOK;
}

static const struct rt_graphic_plane_ops bcm2708fb_plane_ops =
{
    .fb_remap = bcm2708fb_plane_fb_remap,
};

static rt_err_t bcm2708fb_dpms_switch(struct rt_graphic_device *gdev, rt_uint32_t dpms)
{
    rt_err_t err;
    rt_uint32_t value;
    struct bcm2708fb_display *display;

    display = rt_container_of(gdev, struct bcm2708fb_display, parent);
    value = display->display_settings.display_num;

    if ((err = rpi_firmware_property(display->fb->rpi_fw,
            RPI_FIRMWARE_FRAMEBUFFER_SET_DISPLAY_NUM, &value, sizeof(value))))
    {
        return err;
    }

    switch (dpms)
    {
    case RT_GRAPHIC_DPMS_ON:
        value = 0;
        break;

    case RT_GRAPHIC_DPMS_STANDBY:
    case RT_GRAPHIC_DPMS_SUSPEND:
    case RT_GRAPHIC_DPMS_OFF:
        value = 1;
        break;
    }

    return rpi_firmware_property(display->fb->rpi_fw,
            RPI_FIRMWARE_FRAMEBUFFER_BLANK, &value, sizeof(value));
}

static rt_err_t bcm2708fb_wait_vsync(struct rt_graphic_device *gdev)
{
    rt_err_t err;
    rt_uint32_t value;
    struct bcm2708fb_display *display;

    display = rt_container_of(gdev, struct bcm2708fb_display, parent);
    value = display->display_settings.display_num;

    if ((err = rpi_firmware_property(display->fb->rpi_fw,
            RPI_FIRMWARE_FRAMEBUFFER_SET_DISPLAY_NUM, &value, sizeof(value))))
    {
        return err;
    }

    return rpi_firmware_property(display->fb->rpi_fw,
            RPI_FIRMWARE_FRAMEBUFFER_SET_VSYNC, &value, sizeof(value));
}

static struct rt_graphic_device_ops bcm2708fb_ops =
{
    .dpms_switch = bcm2708fb_dpms_switch,
    .wait_vsync = bcm2708fb_wait_vsync,
};

static rt_uint32_t bcm2708fb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
    RTGRAPHIC_PIXEL_FORMAT_BGR888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
};

static rt_err_t bcm2708fb_firmware_alloc(struct rpi_firmware *rpi_fw,
        struct bcm2708fb_display *display, rt_uint32_t depth,
        struct fb_alloc_tags *fbinfo)
{
    rt_err_t err;

    rt_memset(fbinfo, 0, sizeof(*fbinfo));

    fbinfo->tag1 = (struct rpi_firmware_property_tag_header)
    {
        RPI_FIRMWARE_FRAMEBUFFER_SET_PHYSICAL_WIDTH_HEIGHT, 8, 0,
    };
    fbinfo->xres = display->display_settings.width;
    fbinfo->yres = display->display_settings.height;
    fbinfo->tag2 = (struct rpi_firmware_property_tag_header)
    {
        RPI_FIRMWARE_FRAMEBUFFER_SET_VIRTUAL_WIDTH_HEIGHT, 8, 0,
    };
    fbinfo->xres_virtual = display->display_settings.virtual_width;
    fbinfo->yres_virtual = display->display_settings.virtual_height;
    fbinfo->tag3 = (struct rpi_firmware_property_tag_header)
    {
        RPI_FIRMWARE_FRAMEBUFFER_SET_DEPTH, 4, 0,
    };
    fbinfo->bpp = depth;
    fbinfo->tag4 = (struct rpi_firmware_property_tag_header)
    {
        RPI_FIRMWARE_FRAMEBUFFER_SET_VIRTUAL_OFFSET, 8, 0,
    };
    fbinfo->xoffset = display->display_settings.virtual_width_offset;
    fbinfo->yoffset = display->display_settings.virtual_height_offset;
    fbinfo->tag5 = (struct rpi_firmware_property_tag_header)
    {
        RPI_FIRMWARE_FRAMEBUFFER_ALLOCATE, 8, 0,
    };
    fbinfo->base = FRAMEBUFFER_ALIGNMENT;
    fbinfo->tag6 = (struct rpi_firmware_property_tag_header)
    {
        RPI_FIRMWARE_FRAMEBUFFER_GET_PITCH, 4, 0,
    };

    err = rpi_firmware_property_list(rpi_fw, fbinfo, sizeof(*fbinfo));

    if (!err && (!fbinfo->base || !fbinfo->screen_size || !fbinfo->pitch))
    {
        err = -RT_ENOMEM;
    }

    if (!err && (fbinfo->bpp != depth ||
            fbinfo->pitch < (fbinfo->xres_virtual * depth) / 8))
    {
        err = -RT_EINVAL;
    }

    return err;
}

static rt_err_t bcm2708fb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t num_displays;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *fw_np;
    struct { rt_uint32_t base, length; } gpu_mem;
    struct bcm2708fb *bfb = rt_calloc(1, sizeof(*bfb));

    if (!bfb)
    {
        LOG_E("No memory for framebuffer state");
        return -RT_ENOMEM;
    }

    fw_np = rt_ofw_parse_phandle(np, "firmware", 0);

    if (!fw_np)
    {
        LOG_E("Missing firmware phandle");
        err = -RT_EINVAL;
        goto _fail;
    }

    bfb->rpi_fw = rpi_firmware_get(fw_np);
    rt_ofw_node_put(fw_np);

    if (!bfb->rpi_fw)
    {
        LOG_E("Raspberry Pi firmware is unavailable");
        err = -RT_EINVAL;
        goto _fail;
    }

    err = rpi_firmware_property(bfb->rpi_fw, RPI_FIRMWARE_FRAMEBUFFER_GET_NUM_DISPLAYS,
            &num_displays, sizeof(num_displays));

    if (err)
    {
        LOG_E("GET_NUM_DISPLAYS failed: %s", rt_strerror(err));
        goto _fail;
    }

    if (num_displays == 0)
    {
        LOG_E("Firmware reported no displays");
        err = -RT_EINVAL;
        goto _fail;
    }

    num_displays = rt_min_t(rt_uint32_t, num_displays, MAX_FRAMEBUFFERS);
    LOG_I("Firmware reported %u display(s)", num_displays);

    rpi_firmware_property(bfb->rpi_fw, RPI_FIRMWARE_GET_VC_MEMORY,
            &gpu_mem, sizeof(gpu_mem));

    rt_uint32_t num_registered = 0;

    for (int i = 0; i < num_displays; ++i)
    {
        rt_uint32_t midx, value, requested_depth, effective_depth, stride_width;
        struct fb_alloc_tags fbinfo;
        struct bcm2708fb_display *display = &bfb->displays[i];

        display->display_settings.display_num = i;

        err = rpi_firmware_property(bfb->rpi_fw,
                RPI_FIRMWARE_FRAMEBUFFER_GET_DISPLAY_SETTINGS,
                &display->display_settings, GET_DISPLAY_SETTINGS_PAYLOAD_SIZE);

        if (err)
        {
            goto _display_fail;
        }

        if (!display->display_settings.width)
        {
            display->display_settings.width = 800;
            display->display_settings.height = 480;
            display->display_settings.depth = 32;
        }

        if (!display->display_settings.virtual_width)
        {
            display->display_settings.virtual_width = display->display_settings.width;
        }

        if (!display->display_settings.virtual_height)
        {
            display->display_settings.virtual_height = display->display_settings.height;
        }

        requested_depth = display->display_settings.depth;
        value = i;

        if ((err = rpi_firmware_property(bfb->rpi_fw,
                RPI_FIRMWARE_FRAMEBUFFER_SET_DISPLAY_NUM, &value, sizeof(value))))
        {
            goto _display_fail;
        }

        err = bcm2708fb_firmware_alloc(bfb->rpi_fw, display,
                requested_depth, &fbinfo);

        if (err && requested_depth != 16)
        {
            LOG_W("Display(%d) preferred %ubpp unavailable, trying 16bpp",
                    i, requested_depth);
            requested_depth = 16;
            err = bcm2708fb_firmware_alloc(bfb->rpi_fw, display,
                    requested_depth, &fbinfo);
        }

        if (err)
        {
            LOG_E("Display(%d) firmware allocation failed: base=0x%08x size=%u pitch=%u",
                    i, fbinfo.base, fbinfo.screen_size, fbinfo.pitch);
            goto _display_fail;
        }

        fbinfo.base &= ~0xc0000000;
        display->framebuffer_dma = fbinfo.base;
        display->framebuffer_size = fbinfo.screen_size;
        display->stride = fbinfo.pitch;
        display->framebuffer = rt_ioremap_wt(
                (void *)display->framebuffer_dma, display->framebuffer_size);

        if (!display->framebuffer)
        {
            err = -RT_ENOMEM;
            goto _display_fail;
        }

        LOG_I("Display(%d) firmware framebuffer: bpp=%u pitch=%u size=%u",
                i, fbinfo.bpp, fbinfo.pitch, fbinfo.screen_size);

        if (!fbinfo.bpp || !fbinfo.pitch)
        {
            err = -RT_EINVAL;
            goto _display_fail;
        }

        effective_depth = fbinfo.bpp;
        stride_width = fbinfo.xres_virtual ? fbinfo.xres_virtual :
                display->display_settings.virtual_width;

        /* Pi 5 firmware can report stale bpp while returning the active pitch. */
        if (stride_width && fbinfo.pitch != (stride_width * fbinfo.bpp) / 8)
        {
            if (fbinfo.pitch == stride_width * 2)
            {
                effective_depth = 16;
            }
            else if (fbinfo.pitch == stride_width * 3)
            {
                effective_depth = 24;
            }
            else if (fbinfo.pitch == stride_width * 4)
            {
                effective_depth = 32;
            }

            if (effective_depth != fbinfo.bpp)
            {
                LOG_W("Display(%d) inconsistent format: bpp=%u pitch=%u width=%u; using %ubpp",
                        i, fbinfo.bpp, fbinfo.pitch, stride_width, effective_depth);
            }
        }

        display->display_settings.depth = effective_depth;
        display->stride = fbinfo.pitch;

        if (requested_depth != effective_depth)
        {
            LOG_W("Display(%d) depth adjusted by firmware: %u -> %u",
                    i, requested_depth, effective_depth);
        }

        switch (display->display_settings.depth)
        {
        case 16: midx = 0; break;
        case 24: midx = 1; break;
        case 32: midx = 2; break;
        default:
            err = -RT_EINVAL;
            goto _display_fail;
        }

        display->fb = bfb;
        display->gpu_mem.base = gpu_mem.base;
        display->gpu_mem.length = gpu_mem.length;

        display->parent.ops = &bcm2708fb_ops;

        rt_memset(display->framebuffer, 0, display->framebuffer_size);

        if ((err = rt_graphic_device_simple_register(&display->parent,
                display->display_settings.width, display->display_settings.height, 0,
                &bcm2708fb_plane_ops, &bcm2708fb_modes[midx], 1)))
        {
            goto _display_fail;
        }

        LOG_I("Display(%d) registered: %ux%u@%u, pitch=%u, fb=%p",
                i, display->display_settings.width, display->display_settings.height,
                display->display_settings.depth, (rt_uint32_t)display->stride,
                display->framebuffer);

        num_registered++;
        continue;

    _display_fail:
        if (display->framebuffer)
        {
            rt_iounmap(display->framebuffer);
        }

        display->display_settings.display_num = MAX_FRAMEBUFFERS;
        LOG_W("Display(%d) init error = %s", i, rt_strerror(err));
    }

    if (!num_registered)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pdev->parent.user_data = bfb;

    return RT_EOK;

_fail:
    if (bfb->rpi_fw)
    {
        rpi_firmware_put(bfb->rpi_fw);
    }

    rt_free(bfb);

    return err;
}

static rt_err_t bcm2708fb_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct bcm2708fb *bfb = dev->user_data;

    for (int i = 0; i < RT_ARRAY_SIZE(bfb->displays); ++i)
    {
        struct bcm2708fb_display *display = &bfb->displays[i];

        if (display->display_settings.display_num == MAX_FRAMEBUFFERS)
        {
            continue;
        }

        rt_graphic_device_simple_unregister(&display->parent);

        rt_iounmap(display->framebuffer);
    }

    rpi_firmware_put(bfb->rpi_fw);

    rt_free(bfb);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2708fb_ofw_ids[] =
{
    { .compatible = "brcm,bcm2708-fb" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2708fb_driver =
{
    .name = "bcm2708-framebuffer",
    .ids = bcm2708fb_ofw_ids,

    .probe = bcm2708fb_probe,
    .remove = bcm2708fb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2708fb_driver);
