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

#define DBG_TAG "fb.simple"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct simplefb_format
{
    const char *name;
    rt_uint32_t mode;
    rt_uint32_t bits_per_pixel;
};

struct simplefb_params
{
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t stride;
    struct simplefb_format *format;
};

struct simplefb
{
    struct rt_graphic_device parent;

    void *screen_base;
    rt_size_t screen_size;
    rt_size_t stride;

#ifdef RT_USING_CLK
    rt_bool_t clk_arr_enabled;
    struct rt_clk_array *clk_arr;
#endif
#ifdef RT_USING_REGULATOR
    rt_bool_t supplys_enabled;
    rt_size_t supplys_nr;
    struct rt_regulator **supplys;
#endif
};

#ifdef RT_USING_CLK
static rt_err_t simplefb_clk_probe(struct simplefb *sfb,
        struct rt_platform_device *pdev)
{
    sfb->clk_arr = rt_clk_get_array(&pdev->parent);

    if (rt_is_err(sfb->clk_arr))
    {
        return rt_ptr_err(sfb->clk_arr);
    }

    return RT_EOK;
}

static void simplefb_clk_enable(struct simplefb *sfb)
{
    rt_clk_array_prepare_enable(sfb->clk_arr);
    sfb->clk_arr_enabled = RT_TRUE;
}

static void simplefb_clk_remove(struct simplefb *sfb)
{
    if (!rt_is_err_or_null(sfb->clk_arr))
    {
        if (sfb->clk_arr_enabled)
        {
            rt_clk_array_disable_unprepare(sfb->clk_arr);
        }

        rt_clk_array_put(sfb->clk_arr);
    }
}
#else
static rt_err_t simplefb_clk_probe(struct simplefb *sfb,
        struct rt_platform_device *pdev) { return RT_EOK; }
static void simplefb_clk_enable(struct simplefb *sfb) { }
static void simplefb_clk_remove(struct simplefb *sfb) { }
#endif /* RT_USING_CLK */

#ifdef RT_USING_REGULATOR
#define SUPPLY_SUFFIX "-supply"

static rt_err_t simplefb_regulator_probe(struct simplefb *sfb,
        struct rt_platform_device *pdev)
{
    int i = 0;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *np = dev->ofw_node;

    rt_ofw_foreach_prop(np, prop)
    {
        name = rt_strstr(prop->name, SUPPLY_SUFFIX);

        if (name && name != prop->name)
        {
            ++sfb->supplys_nr;
        }
    }

    sfb->supplys = rt_calloc(sfb->supplys_nr, sizeof(sfb->supplys[0]));

    if (!sfb->supplys)
    {
        return -RT_ENOMEM;
    }

    rt_ofw_foreach_prop(np, prop)
    {
        name = rt_strstr(prop->name, SUPPLY_SUFFIX);

        if (name && name != prop->name)
        {
            char name[32];
            int len = name - prop->name;

            rt_strncpy(name, prop->name, len);
            name[len] = '\0';

            sfb->supplys[i] = rt_regulator_get(dev, (const char *)name);

            if (rt_is_err(sfb->supplys[i]))
            {
                return rt_ptr_err(sfb->supplys[i]);
            }

            ++i;
        }
    }

    return RT_EOK;
}

static void simplefb_regulator_enable(struct simplefb *sfb)
{
    if (sfb->supplys)
    {
        for (int i = 0; i < sfb->supplys_nr; ++i)
        {
            rt_regulator_enable(sfb->supplys[i]);
        }

        sfb->supplys_enabled = RT_TRUE;
    }
}

static void simplefb_regulator_remove(struct simplefb *sfb)
{
    if (sfb->supplys && sfb->supplys_enabled)
    {
        for (int i = 0; i < sfb->supplys_nr; ++i)
        {
            struct rt_regulator *supply = sfb->supplys[i];

            if (!rt_is_err(supply))
            {
                rt_regulator_disable(supply);
                rt_regulator_put(supply);
            }
        }

        rt_free(sfb->supplys);
    }
}
#else
static rt_err_t simplefb_regulator_probe(struct simplefb *sfb,
        struct rt_platform_device *pdev)
{
    return RT_EOK;
}

static void simplefb_regulator_enable(struct simplefb *sfb)
{
}

static void simplefb_regulator_remove(struct simplefb *sfb)
{
}
#endif /* RT_USING_REGULATOR */

static struct simplefb_format simplefb_formats[] =
{
    { "r5g6b5",   RTGRAPHIC_PIXEL_FORMAT_RGB565,  16 },
    { "r8g8b8",   RTGRAPHIC_PIXEL_FORMAT_RGB888,  24 },
    { "x8r8g8b8", RTGRAPHIC_PIXEL_FORMAT_ARGB888, 32 },
    { "a8r8g8b8", RTGRAPHIC_PIXEL_FORMAT_ARGB888, 32 },
    { "x8b8g8r8", RTGRAPHIC_PIXEL_FORMAT_ABGR888, 32 },
    { "a8b8g8r8", RTGRAPHIC_PIXEL_FORMAT_ABGR888, 32 },
};

static rt_err_t simplefb_params_parse(struct simplefb_params *params,
        struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *format;
    struct rt_device *dev = &pdev->parent;

    if ((err = rt_dm_dev_prop_read_u32(dev, "width", &params->width)))
    {
        LOG_E("Can't parse width property");

        return err;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "height", &params->height)))
    {
        LOG_E("Can't parse height property");

        return err;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "stride", &params->stride)))
    {
        LOG_E("Can't parse stride property");

        return err;
    }

    if ((err = rt_dm_dev_prop_read_string(dev, "format", &format)))
    {
        LOG_E("Can't parse format property");

        return err;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(simplefb_formats); ++i)
    {
        if (rt_strcmp(format, simplefb_formats[i].name))
        {
            continue;
        }

        params->format = &simplefb_formats[i];

        return RT_EOK;
    }

    LOG_E("Unsupport format value");

    return -RT_EINVAL;
}

static rt_err_t simplefb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    struct simplefb *sfb = rt_container_of(plane->graphic, struct simplefb, parent);

    plane->line_length = sfb->stride;
    plane->bits_per_pixel = rt_graphic_mode_bpp(mode);

    plane->framebuffer = sfb->screen_base;
    plane->screen_len = sfb->screen_size;
    plane->framebuffer_len = sfb->screen_size;

    return RT_EOK;
}

static const struct rt_graphic_plane_ops simplefb_plane_ops =
{
    .fb_remap = simplefb_plane_fb_remap,
};

static rt_err_t simplefb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t addr, size;
    struct simplefb_params params = {};
    struct simplefb *sfb = rt_calloc(1, sizeof(*sfb));

    if (!sfb)
    {
        return -RT_ENOMEM;
    }

    if ((err = simplefb_params_parse(&params, pdev)))
    {
        goto _fail;
    }

    sfb->stride = params.stride;

    if ((err = rt_dm_dev_get_address(&pdev->parent, 0, &addr, &size)))
    {
        goto _fail;
    }

    sfb->screen_size = (rt_size_t)size;
    sfb->screen_base = rt_ioremap_wt((void *)addr, sfb->screen_size);

    if (!sfb->screen_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((err = simplefb_clk_probe(sfb, pdev)))
    {
        LOG_E("Get %s error = %s", "clk", rt_strerror(err));

        goto _fail;
    }

    if ((err = simplefb_regulator_probe(sfb, pdev)))
    {
        LOG_E("Get %s error = %s", "regulator", rt_strerror(err));

        goto _fail;
    }

    simplefb_clk_enable(sfb);
    simplefb_regulator_enable(sfb);

    if ((err = rt_graphic_device_simple_register(&sfb->parent,
            params.width, params.height, 0, &simplefb_plane_ops,
            &params.format->mode, 1)))
    {
        goto _fail;
    }

    pdev->parent.user_data = sfb;

    return RT_EOK;

_fail:
    if (sfb->screen_base)
    {
        rt_iounmap(sfb->screen_base);
    }

    simplefb_clk_remove(sfb);
    simplefb_regulator_remove(sfb);

    rt_free(sfb);

    return err;
}

static rt_err_t simplefb_remove(struct rt_platform_device *pdev)
{
    struct simplefb *sfb = pdev->parent.user_data;

    rt_graphic_device_simple_unregister(&sfb->parent);

    simplefb_clk_remove(sfb);
    simplefb_regulator_remove(sfb);

    rt_iounmap(sfb->screen_base);

    rt_free(sfb);

    return RT_EOK;
}

static const struct rt_ofw_node_id simplefb_ofw_ids[] =
{
    { .compatible = "simple-framebuffer" },
    { /* sentinel */ }
};

static struct rt_platform_driver simplefb_driver =
{
    .name = "simple-framebuffer",
    .ids = simplefb_ofw_ids,

    .probe = simplefb_probe,
    .remove = simplefb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(simplefb_driver);
