/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include "reboot-mode.h"

#define MODE_SUFFIXE "mode-"

struct mode_info
{
    rt_slist_t list;

    const char *mode;
    rt_uint32_t magic;
};

static rt_err_t reboot_mode_work(struct rt_device *dev, char *cmd)
{
    struct mode_info *info;
    struct reboot_mode *reboot = (void *)dev;

    cmd = cmd ? : "normal";

    rt_slist_for_each_entry(info, &reboot->mode_nodes, list)
    {
        if (!rt_strcmp(info->mode, cmd))
        {
            reboot->write(reboot, info->magic);
            break;
        }
    }

    return RT_EOK;
}

rt_err_t reboot_mode_register(struct reboot_mode *reboot)
{
    rt_err_t err;
    struct mode_info *info;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *np = reboot->dev->ofw_node;
    const int mode_suffixe_len = sizeof(MODE_SUFFIXE) - 1;

    if (!reboot || !reboot->dev)
    {
        return -RT_EINVAL;
    }

    rt_slist_init(&reboot->mode_nodes);

    rt_ofw_foreach_prop(np, prop)
    {
        if (rt_strncmp(prop->name, MODE_SUFFIXE, mode_suffixe_len))
        {
            continue;
        }

        info = rt_malloc(sizeof(*info));

        if (!info)
        {
            err = -RT_ENOMEM;

            goto _end;
        }

        info->mode = prop->name + mode_suffixe_len;
        info->magic = fdt32_to_cpu(*(const fdt32_t *)prop->value);

        rt_slist_init(&info->list);

        rt_slist_insert(&reboot->mode_nodes, &info->list);
    }

    err = rt_dm_reboot_mode_register((void *)reboot, &reboot_mode_work);

_end:
    if (err)
    {
        struct mode_info *prev_info = RT_NULL;

        rt_slist_for_each_entry(info, &reboot->mode_nodes, list)
        {
            if (prev_info)
            {
                rt_free(prev_info);
            }

            prev_info = info;
        }

        if (prev_info)
        {
            rt_free(prev_info);
        }
    }

    return err;
}
