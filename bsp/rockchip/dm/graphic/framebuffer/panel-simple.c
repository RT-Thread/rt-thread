/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "rockchip-display.h"

#define DBG_TAG "panel.simple"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

rt_packed(struct panel_cmd_header
{
    rt_uint8_t data_type;
    rt_uint8_t delay;
    rt_uint8_t payload_length;
});

struct panel_cmd_desc
{
    struct panel_cmd_header header;
    rt_uint8_t *payload;
};

struct panel_cmd_seq
{
    struct panel_cmd_desc *cmds;
    rt_uint8_t *blob;
    rt_uint32_t cmd_cnt;
};

struct panel_simple
{
    struct rt_device parent;
    struct display_timing timing;
    rt_base_t reset_pin;
    rt_uint8_t reset_active;
    rt_base_t enable_pin;
    rt_uint8_t enable_active;
    rt_uint32_t reset_delay_ms;
    rt_uint32_t prepare_delay_ms;
    rt_uint32_t enable_delay_ms;
    rt_uint32_t init_delay_ms;
    struct panel_cmd_seq init_seq;
    struct rt_regulator *supply;
    rt_bool_t prepared;
    rt_bool_t enabled;
#ifdef RT_GRAPHIC_BACKLIGHT
    struct rt_backlight_device *backlight;
    rt_uint32_t brightness;
#endif
};

static rt_err_t panel_simple_get_timing(void *priv, struct display_timing *tim)
{
    struct panel_simple *panel = priv;

    if (!panel || !tim)
    {
        return -RT_EINVAL;
    }

    *tim = panel->timing;

    return RT_EOK;
}

static void panel_simple_pulse_reset(struct panel_simple *panel)
{
    if (panel->reset_pin < 0)
    {
        return;
    }

    rt_pin_mode(panel->reset_pin, PIN_MODE_OUTPUT);
    rt_pin_write(panel->reset_pin, panel->reset_active);
    rt_thread_mdelay(panel->reset_delay_ms);
    rt_pin_write(panel->reset_pin, !panel->reset_active);
    rt_thread_mdelay(panel->reset_delay_ms);
}

static rt_err_t panel_simple_parse_cmd_seq(struct rt_ofw_node *np, const char *prop,
        struct panel_cmd_seq *seq)
{
    const rt_uint8_t *data;
    rt_ssize_t len;
    const rt_uint8_t *d;
    rt_size_t remain, i, cnt;
    struct panel_cmd_header *header;

    if (!np || !prop || !seq)
    {
        return -RT_EINVAL;
    }

    data = rt_ofw_prop_read_raw(np, prop, &len);

    if (!data || len <= 0)
    {
        return -RT_ENOENT;
    }

    seq->blob = rt_malloc(len);

    if (!seq->blob)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(seq->blob, data, len);
    d = seq->blob;
    remain = len;
    cnt = 0;

    while (remain)
    {
        if (remain < sizeof(*header))
        {
            rt_free(seq->blob);
            seq->blob = RT_NULL;
            return -RT_EINVAL;
        }

        header = (struct panel_cmd_header *)d;
        d += sizeof(*header);
        remain -= sizeof(*header);

        if (header->payload_length > remain)
        {
            rt_free(seq->blob);
            seq->blob = RT_NULL;
            return -RT_EINVAL;
        }

        d += header->payload_length;
        remain -= header->payload_length;
        ++cnt;
    }

    seq->cmds = rt_calloc(cnt, sizeof(*seq->cmds));

    if (!seq->cmds)
    {
        rt_free(seq->blob);
        seq->blob = RT_NULL;
        return -RT_ENOMEM;
    }

    seq->cmd_cnt = cnt;
    d = seq->blob;
    remain = len;

    for (i = 0; i < cnt; ++i)
    {
        header = (struct panel_cmd_header *)d;
        d += sizeof(*header);
        remain -= sizeof(*header);
        seq->cmds[i].header = *header;
        seq->cmds[i].payload = (rt_uint8_t *)d;
        d += header->payload_length;
        remain -= header->payload_length;
    }

    return RT_EOK;
}

static rt_err_t panel_simple_run_init(void *priv,
        const struct rockchip_connector_ops *conn_ops, void *conn_priv)
{
    struct panel_simple *panel = priv;
    rt_uint32_t i;
    rt_err_t err = RT_EOK;

    if (!panel || !conn_ops || !conn_ops->transfer || !panel->init_seq.cmd_cnt)
    {
        return RT_EOK;
    }

    if (panel->init_delay_ms)
    {
        rt_thread_mdelay(panel->init_delay_ms);
    }

    for (i = 0; i < panel->init_seq.cmd_cnt; ++i)
    {
        struct panel_cmd_desc *cmd = &panel->init_seq.cmds[i];

        err = conn_ops->transfer(conn_priv, cmd->header.data_type, cmd->header.delay,
                cmd->payload, cmd->header.payload_length);

        if (err)
        {
            LOG_W("panel init cmd %u failed: %d", i, err);
            break;
        }
    }

    if (!err)
    {
        LOG_D("sent %u panel init command(s)", panel->init_seq.cmd_cnt);
    }

    return err;
}

static rt_err_t panel_simple_prepare(void *priv)
{
    struct panel_simple *panel = priv;
    rt_err_t err;

    if (!panel || panel->prepared)
    {
        return RT_EOK;
    }

    if (panel->supply)
    {
        err = rt_regulator_enable(panel->supply);

        if (err)
        {
            LOG_W("panel power enable failed: %d", err);
            return err;
        }
    }

    if (panel->prepare_delay_ms)
    {
        rt_thread_mdelay(panel->prepare_delay_ms);
    }

    panel_simple_pulse_reset(panel);
    panel->prepared = RT_TRUE;

    return RT_EOK;
}

static rt_err_t panel_simple_enable(void *priv)
{
    struct panel_simple *panel = priv;

    if (!panel)
    {
        return -RT_EINVAL;
    }

    if (panel->enable_pin >= 0)
    {
        rt_pin_mode(panel->enable_pin, PIN_MODE_OUTPUT);
        rt_pin_write(panel->enable_pin, panel->enable_active);
    }

    if (panel->enable_delay_ms)
    {
        rt_thread_mdelay(panel->enable_delay_ms);
    }

#ifdef RT_GRAPHIC_BACKLIGHT
    if (panel->backlight)
    {
        rt_backlight_set_power(panel->backlight, RT_BACKLIGHT_POWER_NORMAL);
        rt_backlight_set_brightness(panel->backlight, panel->brightness);
    }
#endif

    panel->enabled = RT_TRUE;

    return RT_EOK;
}

static rt_err_t panel_simple_disable(void *priv)
{
    struct panel_simple *panel = priv;

    if (!panel)
    {
        return -RT_EINVAL;
    }

#ifdef RT_GRAPHIC_BACKLIGHT
    if (panel->backlight)
    {
        rt_backlight_set_power(panel->backlight, RT_BACKLIGHT_POWER_POWERDOWN);
    }
#endif

    if (panel->enable_pin >= 0)
    {
        rt_pin_write(panel->enable_pin, !panel->enable_active);
    }

    if (panel->supply)
    {
        rt_regulator_disable(panel->supply);
    }

    panel->enabled = RT_FALSE;
    panel->prepared = RT_FALSE;

    return RT_EOK;
}

static const struct rockchip_panel_ops panel_simple_ops =
{
    .get_timing = panel_simple_get_timing,
    .prepare = panel_simple_prepare,
    .run_init = panel_simple_run_init,
    .enable = panel_simple_enable,
    .disable = panel_simple_disable,
};

static rt_err_t panel_simple_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct panel_simple *panel = rt_calloc(1, sizeof(*panel));
    rt_err_t err;

    if (!panel)
    {
        return -RT_ENOMEM;
    }

    panel->reset_pin = -1;
    panel->enable_pin = -1;
    panel->reset_delay_ms = 20;
    panel->prepare_delay_ms = 0;
    panel->enable_delay_ms = 0;
#ifdef RT_GRAPHIC_BACKLIGHT
    panel->brightness = 255;
#endif

    if ((err = display_timing_parse(np, &panel->timing)))
    {
        LOG_W("%s: no timing, use 1920x1080", np->name);
        panel->timing.hactive = 1920;
        panel->timing.vactive = 1080;
        panel->timing.hfront_porch = 40;
        panel->timing.hback_porch = 40;
        panel->timing.hsync_len = 10;
        panel->timing.vfront_porch = 20;
        panel->timing.vback_porch = 20;
        panel->timing.vsync_len = 4;
        display_timing_derive(&panel->timing);
    }

    rt_dm_dev_prop_read_u32(dev, "reset-delay-ms", &panel->reset_delay_ms);
    rt_dm_dev_prop_read_u32(dev, "prepare-delay-ms", &panel->prepare_delay_ms);
    rt_dm_dev_prop_read_u32(dev, "enable-delay-ms", &panel->enable_delay_ms);
    rt_dm_dev_prop_read_u32(dev, "init-delay-ms", &panel->init_delay_ms);

    err = panel_simple_parse_cmd_seq(np, "panel-init-sequence", &panel->init_seq);
    if (err && err != -RT_ENOENT)
    {
        LOG_E("%s: invalid panel-init-sequence: %s",
                rt_ofw_node_full_name(np), rt_strerror(err));
        rt_free(panel);
        return err;
    }

    panel->reset_pin = rt_pin_get_named_pin(dev, "reset", 0, RT_NULL, &panel->reset_active);
    if (panel->reset_pin < 0 && panel->reset_pin != PIN_NONE)
    {
        panel->reset_pin = -1;
    }

    panel->enable_pin = rt_pin_get_named_pin(dev, "enable", 0, RT_NULL, &panel->enable_active);
    if (panel->enable_pin < 0 && panel->enable_pin != PIN_NONE)
    {
        panel->enable_pin = -1;
    }

    panel->supply = rt_regulator_get(dev, "power");
    if (rt_is_err(panel->supply))
    {
        panel->supply = RT_NULL;
    }

#ifdef RT_GRAPHIC_BACKLIGHT
    {
        struct rt_ofw_node *bl_np = rt_ofw_parse_phandle(np, "backlight", 0);

        if (bl_np)
        {
            panel->backlight = rt_ofw_data(bl_np);

            if (panel->backlight)
            {
                rt_device_open(&panel->backlight->parent, RT_DEVICE_OFLAG_RDWR);
                panel->brightness = panel->backlight->props.max_brightness ?
                        panel->backlight->props.max_brightness : 255;
            }

            rt_ofw_node_put(bl_np);
        }
    }
#endif /* RT_GRAPHIC_BACKLIGHT */

    rockchip_display_register_panel(np, &panel_simple_ops, panel);

    pdev->parent.user_data = panel;

    LOG_D("panel %s: %ux%u, init-cmds=%u", rt_ofw_node_full_name(np),
            panel->timing.hactive, panel->timing.vactive, panel->init_seq.cmd_cnt);

    return RT_EOK;
}

static const struct rt_ofw_node_id panel_simple_ids[] =
{
    { .compatible = "simple-panel" },
    { .compatible = "simple-panel-dsi" },
    { .compatible = "rockchip,panel-simple" },
    { /* sentinel */ }
};

static struct rt_platform_driver panel_simple_driver =
{
    .name = "panel-simple",
    .ids = panel_simple_ids,
    .probe = panel_simple_probe,
};
RT_PLATFORM_DRIVER_EXPORT(panel_simple_driver);
