/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <finsh.h>

static int fb_rotate(int argc, char **argv)
{
    static const char *angles[] = { "0", "90", "180", "270" };
    const char *name;
    rt_device_t dev;
    struct rt_graphic_device *graphic;
    struct rt_graphic_plane *plane;
    rt_ubase_t rotation;
    rt_err_t err;

    if (argc < 2 || argc > 3)
    {
        goto usage;
    }
    for (rotation = 0; rotation < RT_ARRAY_SIZE(angles); ++rotation)
    {
        if (!rt_strcmp(argv[1], angles[rotation]))
        {
            break;
        }
    }
    if (rotation == RT_ARRAY_SIZE(angles))
    {
        goto usage;
    }

    name = argc == 3 ? argv[2] : "fb0";
    dev = rt_device_find(name);
    if (!dev || dev->type != RT_Device_Class_Graphic)
    {
        rt_kprintf("fb_rotate: graphic device %s not found\n", name);
        return -RT_ENOENT;
    }
    err = rt_device_open(dev, RT_DEVICE_OFLAG_RDWR);
    if (err)
    {
        return err;
    }

    graphic = rt_container_of(dev, struct rt_graphic_device, parent);
    plane = graphic->primary_plane;
    if (!plane || !plane->ops || !plane->ops->prop_set)
    {
        err = -RT_ENOSYS;
    }
    else
    {
        err = plane->ops->prop_set(plane, RT_GRAPHIC_PLANE_PROP_ROTATE,
                (void *)rotation);
    }
    rt_device_close(dev);
    if (err)
    {
        rt_kprintf("fb_rotate: %s\n", rt_strerror(err));
    }
    else
    {
        rt_kprintf("fb_rotate: %s %s degrees\n", name, angles[rotation]);
    }
    return err;

usage:
    rt_kprintf("usage: fb_rotate <0|90|180|270> [fb0]\n");
    return -RT_EINVAL;
}
MSH_CMD_EXPORT(fb_rotate, rotate the primary plane of a framebuffer);
