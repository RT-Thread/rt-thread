/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <mmu.h>
#include <rpi-sense.h>

struct rpisense_framebuffer
{
    struct rt_graphic_device parent;

    struct rpisense *rpisense;

    rt_uint8_t *gamma;

    rt_uint8_t vram[128];
    rt_uint8_t vram_work[193];
    rt_uint8_t gamma_user[32];
};

#define raw_to_rpisense_framebuffer(raw) rt_container_of(raw, struct rpisense_framebuffer, parent)

static rt_uint8_t gamma_default[32] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x02, 0x02, 0x03, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0e, 0x0f, 0x11,
    0x12, 0x14, 0x15, 0x17, 0x19, 0x1b, 0x1d, 0x1f,
};

static rt_uint8_t gamma_low[32] =
{
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
    0x03, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06,
    0x06, 0x07, 0x07, 0x08, 0x08, 0x09, 0x0a, 0x0a,
};

static void rpisense_fb_deferred_io(struct rpisense_framebuffer *rpisense_fb)
{
    rt_uint8_t *gamma = rpisense_fb->gamma;
    rt_uint8_t *vram_work = rpisense_fb->vram_work;
    rt_uint16_t *vram = (rt_uint16_t *)rpisense_fb->vram;
    struct rt_graphic_plane *primary_plane = rpisense_fb->parent.primary_plane;

    vram_work[0] = 0;

    for (int y = 0; y < primary_plane->height; ++y)
    {
        for (int x = 0; x < primary_plane->width; ++x)
        {
            vram_work[(y * 24) + x + 1] = gamma[(vram[(y * 8) + x] >> 11) & 0x1f];
            vram_work[(y * 24) + (x + 8) + 1] = gamma[(vram[(y * 8) + x] >> 6) & 0x1f];
            vram_work[(y * 24) + (x + 16) + 1] = gamma[(vram[(y * 8) + x]) & 0x1f];
        }
    }

    rpisense_block_write(rpisense_fb->rpisense,
            (const void *)vram_work, sizeof(rpisense_fb->vram_work));
}

static rt_err_t rpisense_fb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct rpisense_framebuffer *rpisense_fb = raw_to_rpisense_framebuffer(plane->graphic);

    rpisense_fb_deferred_io(rpisense_fb);

    return RT_EOK;
}

static rt_err_t rpisense_fb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    struct rpisense_framebuffer *rpisense_fb = raw_to_rpisense_framebuffer(plane->graphic);

    plane->line_length = 16;
    plane->bits_per_pixel = 16;

    plane->framebuffer = rpisense_fb->vram;
    plane->screen_len = sizeof(rpisense_fb->vram);
    plane->framebuffer_len = sizeof(rpisense_fb->vram);

    return RT_EOK;
}

static const struct rt_graphic_plane_ops rpisense_fb_plane_ops =
{
    .update = rpisense_fb_plane_update,
    .fb_remap = rpisense_fb_plane_fb_remap,
};

static rt_err_t rpisense_fb_wait_vsync(struct rt_graphic_device *gdev)
{
    struct rpisense_framebuffer *rpisense_fb = raw_to_rpisense_framebuffer(gdev);

    rpisense_fb_deferred_io(rpisense_fb);

    return RT_EOK;
}

static rt_err_t rpisense_fb_control(struct rt_graphic_device *gdev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rpisense_framebuffer *rpisense_fb = raw_to_rpisense_framebuffer(gdev);

    switch (cmd)
    {
    case SENSEFB_FBIOGET_GAMMA:
        rt_memcpy(args, rpisense_fb->gamma, sizeof(rpisense_fb->gamma_user));
        break;

    case SENSEFB_FBIOSET_GAMMA:
        rt_memcpy(rpisense_fb->gamma_user, args, sizeof(rpisense_fb->gamma_user));
        rpisense_fb->gamma = rpisense_fb->gamma_user;
        break;

    case SENSEFB_FBIORESET_GAMMA:
        switch ((rt_ubase_t)args)
        {
        case 0:
            rpisense_fb->gamma = gamma_default;
            break;

        case 1:
            rpisense_fb->gamma = gamma_low;
            break;

        case 2:
            rpisense_fb->gamma = rpisense_fb->gamma_user;
            break;

        default:
            err = -RT_EINVAL;
            break;
        }
        break;

    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

static const struct rt_graphic_device_ops rpisense_fb_ops =
{
    .wait_vsync = rpisense_fb_wait_vsync,
    .control = rpisense_fb_control,
};

static rt_uint32_t rpisense_fb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
};

static rt_err_t rpisense_fb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rpisense *rpisense = pdev->priv;
    struct rpisense_framebuffer *rpisense_fb = rt_calloc(1, sizeof(*rpisense_fb));

    if (!rpisense_fb)
    {
        return -RT_ENOMEM;
    }

    rpisense_fb->rpisense = rpisense;
    rpisense_fb->gamma = gamma_default;
    rpisense_fb->parent.ops = &rpisense_fb_ops;

    if ((err = rt_graphic_device_simple_register(&rpisense_fb->parent,
            8, 8, 0, &rpisense_fb_plane_ops,
            rpisense_fb_modes, RT_ARRAY_SIZE(rpisense_fb_modes))))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(rpisense_fb);

    return err;
}

static rt_err_t rpisense_fb_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;

    rt_device_unregister(&pdev->parent);

    rt_free(rt_container_of(dev->user_data, struct rpisense_framebuffer, parent));

    return RT_EOK;
}

static struct rt_platform_driver rpisense_fb_driver =
{
    .name = "rpi-sense-fb",

    .probe = rpisense_fb_probe,
    .remove = rpisense_fb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rpisense_fb_driver);
