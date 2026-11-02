/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <rtdevice.h>
#include <rtthread.h>

#include <drivers/clk.h>
#include <drivers/syscon.h>

#define DBG_TAG "phye.rockchip.inno-usb2"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define U2PHY_BIT_WRITEABLE_SHIFT   16
#define U2PHY_CLK480M_RATE          480000000UL

enum rockchip_u2phy_port_id
{
    ROCKCHIP_U2PHY_PORT_OTG = 0,
    ROCKCHIP_U2PHY_PORT_HOST = 1,
    ROCKCHIP_U2PHY_PORT_NUM = 2,
};

struct rockchip_u2phy_reg
{
    rt_uint32_t offset;
    rt_uint16_t bitend;
    rt_uint16_t bitstart;
    rt_uint16_t disable;
    rt_uint16_t enable;
};

struct rockchip_u2phy_port_cfg
{
    struct rockchip_u2phy_reg phy_sus;
    struct rockchip_u2phy_reg bvalid_det_en;
    struct rockchip_u2phy_reg bvalid_det_st;
    struct rockchip_u2phy_reg bvalid_det_clr;
    struct rockchip_u2phy_reg ls_det_en;
    struct rockchip_u2phy_reg ls_det_st;
    struct rockchip_u2phy_reg ls_det_clr;
    struct rockchip_u2phy_reg iddig_output;
    struct rockchip_u2phy_reg iddig_en;
    struct rockchip_u2phy_reg idfall_det_en;
    struct rockchip_u2phy_reg idfall_det_st;
    struct rockchip_u2phy_reg idfall_det_clr;
    struct rockchip_u2phy_reg idrise_det_en;
    struct rockchip_u2phy_reg idrise_det_st;
    struct rockchip_u2phy_reg idrise_det_clr;
    struct rockchip_u2phy_reg utmi_avalid;
    struct rockchip_u2phy_reg utmi_bvalid;
    struct rockchip_u2phy_reg utmi_iddig;
    struct rockchip_u2phy_reg utmi_ls;
    struct rockchip_u2phy_reg utmi_hstdet;
    struct rockchip_u2phy_reg vbus_det_en;
};

struct rockchip_u2phy_cfg
{
    rt_uint32_t reg;
    rt_uint32_t num_ports;
    struct rockchip_u2phy_reg clkout_ctl;
    const struct rockchip_u2phy_port_cfg port_cfgs[ROCKCHIP_U2PHY_PORT_NUM];
};

struct rockchip_u2phy_port
{
    struct rt_phye phye;
    struct rt_device port_dev;
    enum rockchip_u2phy_port_id id;
    rt_bool_t registered;
    struct rt_regulator *supply;
    struct rockchip_inno_usb2phy *parent;
};

struct rockchip_inno_usb2phy
{
    struct rt_device *dev;
    struct rt_syscon *usbgrf;
    struct rt_clk *phyclk;
    struct rt_reset_control *phy_rst;
    const struct rockchip_u2phy_cfg *cfg;
    struct rt_clk_node clk_np;
    struct rt_clk_cell clk480m;
    struct rt_clk_cell *clk_cells[1];
    struct rockchip_u2phy_port ports[ROCKCHIP_U2PHY_PORT_NUM];
};

#define phye_to_u2phy_port(phye)    rt_container_of(phye, struct rockchip_u2phy_port, phye)

static rt_uint32_t rockchip_u2phy_genmask(rt_uint32_t hi, rt_uint32_t lo)
{
    return ((1u << (hi - lo + 1)) - 1) << lo;
}

static struct rt_syscon *rockchip_u2phy_get_syscon(struct rockchip_inno_usb2phy *rphy)
{
    return rphy->usbgrf;
}

static rt_err_t rockchip_u2phy_property_enable(struct rt_syscon *syscon,
        const struct rockchip_u2phy_reg *reg, rt_bool_t en)
{
    rt_uint32_t mask, val, tmp;

    if (!syscon || !reg)
    {
        return -RT_EINVAL;
    }

    tmp = en ? reg->enable : reg->disable;
    mask = rockchip_u2phy_genmask(reg->bitend, reg->bitstart);
    val = (tmp << reg->bitstart) | (mask << U2PHY_BIT_WRITEABLE_SHIFT);

    return rt_syscon_write(syscon, reg->offset, val);
}

static rt_bool_t rockchip_u2phy_property_enabled(struct rt_syscon *syscon,
        const struct rockchip_u2phy_reg *reg)
{
    rt_uint32_t val, mask;

    if (!syscon || !reg)
    {
        return RT_FALSE;
    }

    if (rt_syscon_read(syscon, reg->offset, &val))
    {
        return RT_FALSE;
    }

    mask = rockchip_u2phy_genmask(reg->bitend, reg->bitstart);
    val = (val & mask) >> reg->bitstart;

    return val != reg->disable;
}

static rt_err_t rockchip_u2phy_reset(struct rockchip_inno_usb2phy *rphy)
{
    rt_err_t err;

    if (!rphy->phy_rst)
    {
        return RT_EOK;
    }

    if ((err = rt_reset_control_assert(rphy->phy_rst)))
    {
        return err;
    }

    rt_hw_us_delay(20);

    if ((err = rt_reset_control_deassert(rphy->phy_rst)))
    {
        return err;
    }

    rt_hw_us_delay(100);

    return RT_EOK;
}

static const struct rockchip_u2phy_port_cfg *rockchip_u2phy_port_cfg(
        struct rockchip_u2phy_port *port)
{
    return &port->parent->cfg->port_cfgs[port->id];
}

static rt_err_t rockchip_u2phy_port_power_on(struct rt_phye *phye)
{
    struct rockchip_u2phy_port *port = phye_to_u2phy_port(phye);

    if (port->supply)
    {
        return rt_regulator_enable(port->supply);
    }

    return RT_EOK;
}

static rt_err_t rockchip_u2phy_port_power_off(struct rt_phye *phye)
{
    struct rockchip_u2phy_port *port = phye_to_u2phy_port(phye);

    if (port->supply)
    {
        return rt_regulator_disable(port->supply);
    }

    return RT_EOK;
}

static rt_err_t rockchip_u2phy_port_init(struct rt_phye *phye)
{
    struct rockchip_u2phy_port *port = phye_to_u2phy_port(phye);
    struct rockchip_inno_usb2phy *rphy = port->parent;
    struct rt_syscon *syscon = rockchip_u2phy_get_syscon(rphy);
    const struct rockchip_u2phy_port_cfg *port_cfg = rockchip_u2phy_port_cfg(port);

    rockchip_u2phy_property_enable(syscon, &port_cfg->phy_sus, RT_FALSE);
    rt_hw_us_delay(2000);

    return RT_EOK;
}

static rt_err_t rockchip_u2phy_port_exit(struct rt_phye *phye)
{
    struct rockchip_u2phy_port *port = phye_to_u2phy_port(phye);
    struct rockchip_inno_usb2phy *rphy = port->parent;
    struct rt_syscon *syscon = rockchip_u2phy_get_syscon(rphy);
    const struct rockchip_u2phy_port_cfg *port_cfg = rockchip_u2phy_port_cfg(port);

    return rockchip_u2phy_property_enable(syscon, &port_cfg->phy_sus, RT_TRUE);
}

static rt_err_t rockchip_u2phy_clk480m_prepare(struct rt_clk_cell *cell)
{
    rt_err_t err;
    struct rockchip_inno_usb2phy *rphy = rt_container_of(cell->clk_np,
            struct rockchip_inno_usb2phy, clk_np);

    if (rockchip_u2phy_property_enabled(rphy->usbgrf, &rphy->cfg->clkout_ctl))
    {
        return RT_EOK;
    }

    if ((err = rockchip_u2phy_property_enable(rphy->usbgrf, &rphy->cfg->clkout_ctl, RT_TRUE)))
    {
        return err;
    }

    rt_hw_us_delay(1300);

    return RT_EOK;
}

static void rockchip_u2phy_clk480m_unprepare(struct rt_clk_cell *cell)
{
    struct rockchip_inno_usb2phy *rphy = rt_container_of(cell->clk_np,
            struct rockchip_inno_usb2phy, clk_np);

    rockchip_u2phy_property_enable(rphy->usbgrf, &rphy->cfg->clkout_ctl, RT_FALSE);
}

static rt_bool_t rockchip_u2phy_clk480m_is_prepared(struct rt_clk_cell *cell)
{
    struct rockchip_inno_usb2phy *rphy = rt_container_of(cell->clk_np,
            struct rockchip_inno_usb2phy, clk_np);

    return rockchip_u2phy_property_enabled(rphy->usbgrf, &rphy->cfg->clkout_ctl);
}

static rt_ubase_t rockchip_u2phy_clk480m_recalc_rate(struct rt_clk_cell *cell,
        rt_ubase_t parent_rate)
{
    RT_UNUSED(cell);
    RT_UNUSED(parent_rate);

    return U2PHY_CLK480M_RATE;
}

static const struct rt_clk_ops rockchip_u2phy_clk480m_ops =
{
    .prepare = rockchip_u2phy_clk480m_prepare,
    .unprepare = rockchip_u2phy_clk480m_unprepare,
    .is_prepared = rockchip_u2phy_clk480m_is_prepared,
    .recalc_rate = rockchip_u2phy_clk480m_recalc_rate,
};

static const struct rt_phye_ops rockchip_u2phy_port_ops =
{
    .init = rockchip_u2phy_port_init,
    .exit = rockchip_u2phy_port_exit,
    .power_on = rockchip_u2phy_port_power_on,
    .power_off = rockchip_u2phy_port_power_off,
};

static rt_err_t rockchip_u2phy_register_clk480m(struct rockchip_inno_usb2phy *rphy)
{
    rt_err_t err;
    const char *clk_name = rt_dm_dev_get_name(rphy->dev);

    rphy->clk_cells[0] = &rphy->clk480m;

    rphy->clk480m.name = clk_name;
    rphy->clk480m.ops = &rockchip_u2phy_clk480m_ops;
    rphy->clk480m.parents_nr = 1;
    rphy->clk480m.parent = rphy->phyclk;

    if (rphy->phyclk && rphy->phyclk->cell)
    {
        rphy->clk480m.parent_name = rphy->phyclk->cell->name;
    }

    rt_dm_dev_prop_read_string(rphy->dev, "clock-output-names", &rphy->clk480m.name);

    rphy->clk_np.dev = rphy->dev;
    rphy->clk_np.cells_nr = RT_ARRAY_SIZE(rphy->clk_cells);
    rphy->clk_np.cells = rphy->clk_cells;
    rt_list_init(&rphy->clk_np.parent.list);

    if ((err = rt_clk_register(&rphy->clk_np)))
    {
        return err;
    }

    return RT_EOK;
}

static rt_err_t rockchip_u2phy_register_port(struct rockchip_inno_usb2phy *rphy,
        struct rt_ofw_node *port_np, enum rockchip_u2phy_port_id id)
{
    rt_err_t err;
    const char *log_name = rt_ofw_node_full_name(port_np);
    struct rockchip_u2phy_port *port = &rphy->ports[id];

    port->parent = rphy;
    port->id = id;
    port->port_dev.ofw_node = port_np;
    port->phye.dev = &port->port_dev;
    port->phye.ops = &rockchip_u2phy_port_ops;
    port->registered = RT_FALSE;
    port->supply = rt_regulator_get(&port->port_dev, "phy");

    if (rt_is_err(port->supply))
    {
        if (id == ROCKCHIP_U2PHY_PORT_OTG)
        {
            port->supply = rt_regulator_get(&port->port_dev, "vbus");
        }

        if (rt_is_err(port->supply))
        {
            port->supply = RT_NULL;
        }
    }

    if ((err = rt_phye_register(&port->phye)))
    {
        LOG_E("%s: register phy for %s failed: %s",
              rt_dm_dev_get_name(rphy->dev), log_name, rt_strerror(err));
        return err;
    }

    port->registered = RT_TRUE;
    LOG_I("%s: registered %s as %s phy supply=%s",
          rt_dm_dev_get_name(rphy->dev),
          log_name,
          id == ROCKCHIP_U2PHY_PORT_HOST ? "host" : "otg",
          port->supply ? "yes" : "no");

    return RT_EOK;
}

static void rockchip_u2phy_unregister_ports(struct rockchip_inno_usb2phy *rphy)
{
    int i;

    for (i = 0; i < ROCKCHIP_U2PHY_PORT_NUM; ++i)
    {
        struct rockchip_u2phy_port *port = &rphy->ports[i];

        if (!port->registered)
        {
            continue;
        }

        rt_phye_unregister(&port->phye);

        if (port->port_dev.ofw_node)
        {
            rt_ofw_data(port->port_dev.ofw_node) = RT_NULL;
        }

        port->registered = RT_FALSE;
    }
}

static const struct rockchip_u2phy_cfg rk3568_phy_cfgs[] =
{
    {
        .reg = 0xfe8a0000,
        .num_ports = 2,
        .clkout_ctl = { 0x0008, 4, 4, 1, 0 },
        .port_cfgs =
        {
            [ROCKCHIP_U2PHY_PORT_OTG] =
            {
                .phy_sus = { 0x0000, 8, 0, 0x052, 0x1d1 },
                .bvalid_det_en = { 0x0080, 2, 2, 0, 1 },
                .bvalid_det_st = { 0x0084, 2, 2, 0, 1 },
                .bvalid_det_clr = { 0x0088, 2, 2, 0, 1 },
                .iddig_output = { 0x0000, 10, 10, 0, 1 },
                .iddig_en = { 0x0000, 9, 9, 0, 1 },
                .idfall_det_en = { 0x0080, 5, 5, 0, 1 },
                .idfall_det_st = { 0x0084, 5, 5, 0, 1 },
                .idfall_det_clr = { 0x0088, 5, 5, 0, 1 },
                .idrise_det_en = { 0x0080, 4, 4, 0, 1 },
                .idrise_det_st = { 0x0084, 4, 4, 0, 1 },
                .idrise_det_clr = { 0x0088, 4, 4, 0, 1 },
                .ls_det_en = { 0x0080, 0, 0, 0, 1 },
                .ls_det_st = { 0x0084, 0, 0, 0, 1 },
                .ls_det_clr = { 0x0088, 0, 0, 0, 1 },
                .utmi_avalid = { 0x00c0, 10, 10, 0, 1 },
                .utmi_bvalid = { 0x00c0, 9, 9, 0, 1 },
                .utmi_iddig = { 0x00c0, 6, 6, 0, 1 },
                .utmi_ls = { 0x00c0, 5, 4, 0, 1 },
            },
            [ROCKCHIP_U2PHY_PORT_HOST] =
            {
                .phy_sus = { 0x0004, 8, 0, 0x1d2, 0x1d1 },
                .ls_det_en = { 0x0080, 1, 1, 0, 1 },
                .ls_det_st = { 0x0084, 1, 1, 0, 1 },
                .ls_det_clr = { 0x0088, 1, 1, 0, 1 },
                .utmi_ls = { 0x00c0, 17, 16, 0, 1 },
                .utmi_hstdet = { 0x00c0, 19, 19, 0, 1 },
            },
        },
    },
    {
        .reg = 0xfe8b0000,
        .num_ports = 2,
        .clkout_ctl = { 0x0008, 4, 4, 1, 0 },
        .port_cfgs =
        {
            [ROCKCHIP_U2PHY_PORT_OTG] =
            {
                .phy_sus = { 0x0000, 8, 0, 0x1d2, 0x1d1 },
                .ls_det_en = { 0x0080, 0, 0, 0, 1 },
                .ls_det_st = { 0x0084, 0, 0, 0, 1 },
                .ls_det_clr = { 0x0088, 0, 0, 0, 1 },
                .utmi_ls = { 0x00c0, 5, 4, 0, 1 },
                .utmi_hstdet = { 0x00c0, 7, 7, 0, 1 },
            },
            [ROCKCHIP_U2PHY_PORT_HOST] =
            {
                .phy_sus = { 0x0004, 8, 0, 0x1d2, 0x1d1 },
                .ls_det_en = { 0x0080, 1, 1, 0, 1 },
                .ls_det_st = { 0x0084, 1, 1, 0, 1 },
                .ls_det_clr = { 0x0088, 1, 1, 0, 1 },
                .utmi_ls = { 0x00c0, 17, 16, 0, 1 },
                .utmi_hstdet = { 0x00c0, 19, 19, 0, 1 },
            },
        },
    },
    { /* sentinel */ },
};

static const struct rockchip_u2phy_cfg *rockchip_u2phy_match_cfg(
        const struct rockchip_u2phy_cfg *cfgs, rt_uint64_t addr)
{
    for (int i = 0; cfgs[i].reg; ++i)
    {
        if (cfgs[i].reg == (rt_uint32_t)addr)
        {
            return &cfgs[i];
        }
    }

    return RT_NULL;
}

static rt_err_t rockchip_inno_usb2phy_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t addr;
    int port_count = 0;
    struct rt_device *dev = &pdev->parent;
    const char *dev_name = rt_dm_dev_get_name(dev);
    struct rt_ofw_node *port_np;
    struct rockchip_inno_usb2phy *rphy = rt_calloc(1, sizeof(*rphy));
    const struct rockchip_u2phy_cfg *cfgs = pdev->id->data;

    if (!rphy)
    {
        LOG_E("%s: no memory for usb2phy", dev_name);
        return -RT_ENOMEM;
    }

    rphy->dev = dev;
    dev->user_data = rphy;
    LOG_I("%s: probe start", dev_name);

    if ((err = rt_dm_dev_get_address(dev, 0, &addr, RT_NULL)))
    {
        LOG_E("%s: get address failed: %s", dev_name, rt_strerror(err));
        goto _fail;
    }
    LOG_I("%s: addr=0x%08x", dev_name, (rt_uint32_t)addr);

    rphy->cfg = rockchip_u2phy_match_cfg(cfgs, addr);

    if (!rphy->cfg)
    {
        LOG_E("%s: no phy config for 0x%08x", dev_name, (rt_uint32_t)addr);
        err = -RT_EINVAL;
        goto _fail;
    }
    LOG_I("%s: matched phy cfg for 0x%08x", dev_name, (rt_uint32_t)addr);

    rphy->usbgrf = rt_syscon_find_by_ofw_phandle(dev->ofw_node, "rockchip,usbgrf");

    if (!rphy->usbgrf)
    {
        LOG_E("%s: failed to get usbgrf", dev_name);
        err = -RT_EIO;
        goto _fail;
    }
    LOG_I("%s: usbgrf acquired", dev_name);

    rphy->phyclk = rt_clk_get_by_name(dev, "phyclk");

    if (rt_is_err(rphy->phyclk))
    {
        err = rt_ptr_err(rphy->phyclk);
        LOG_E("%s: get phyclk failed: %s", dev_name, rt_strerror(err));
        goto _fail;
    }
    LOG_I("%s: phyclk acquired", dev_name);

    rphy->phy_rst = rt_reset_control_get_by_name(dev, "phy");

    if (rt_is_err(rphy->phy_rst))
    {
        rphy->phy_rst = RT_NULL;
        LOG_W("%s: reset 'phy' not found", dev_name);
    }
    else
    {
        LOG_I("%s: reset 'phy' acquired", dev_name);
    }

    if ((err = rt_clk_prepare_enable(rphy->phyclk)))
    {
        LOG_E("%s: enable phyclk failed: %s", dev_name, rt_strerror(err));
        goto _fail_clk;
    }
    LOG_I("%s: phyclk enabled", dev_name);

    if ((err = rockchip_u2phy_reset(rphy)))
    {
        LOG_E("%s: phy reset failed: %s", dev_name, rt_strerror(err));
        goto _fail_clk_en;
    }
    LOG_I("%s: phy reset done", dev_name);

    if ((err = rockchip_u2phy_register_clk480m(rphy)))
    {
        LOG_E("%s: register 480m clk failed: %s", dev_name, rt_strerror(err));
        goto _fail_clk_en;
    }
    LOG_I("%s: 480m output clock registered as %s", dev_name, rphy->clk480m.name);

    if (rphy->cfg->clkout_ctl.disable)
    {
        rockchip_u2phy_property_enable(rphy->usbgrf, &rphy->cfg->clkout_ctl, RT_TRUE);
        LOG_I("%s: clkout enabled", dev_name);
    }

    rt_ofw_foreach_available_child_node(dev->ofw_node, port_np)
    {
        const char *log_name = rt_ofw_node_full_name(port_np);

        LOG_I("%s: found child port %s", dev_name, log_name);

        if (rt_ofw_node_tag_equ(port_np, "host-port"))
        {
            err = rockchip_u2phy_register_port(rphy, port_np, ROCKCHIP_U2PHY_PORT_HOST);
        }
        else if (rt_ofw_node_tag_equ(port_np, "otg-port"))
        {
            err = rockchip_u2phy_register_port(rphy, port_np, ROCKCHIP_U2PHY_PORT_OTG);
        }
        else
        {
            LOG_W("%s: skip unknown child node %s", dev_name, log_name);
            continue;
        }

        if (err)
        {
            rt_ofw_node_put(port_np);
            LOG_E("%s: register port %s failed: %s", dev_name, log_name, rt_strerror(err));
            goto _fail_ports;
        }

        ++port_count;
    }

    if (!port_count)
    {
        LOG_W("%s: no available child ports registered", dev_name);
    }

    LOG_I("%s: probe success with %d port(s)", dev_name, port_count);

    return RT_EOK;

_fail_ports:
    rockchip_u2phy_unregister_ports(rphy);

_fail_clk_en:
    rt_clk_disable_unprepare(rphy->phyclk);
    rt_clk_unregister(&rphy->clk_np);

_fail_clk:
    if (!rt_is_err_or_null(rphy->phyclk))
    {
        rt_clk_put(rphy->phyclk);
    }

_fail:
    rt_free(rphy);

    return err;
}

static rt_err_t rockchip_inno_usb2phy_remove(struct rt_platform_device *pdev)
{
    struct rockchip_inno_usb2phy *rphy = pdev->parent.user_data;
    const char *dev_name = rt_dm_dev_get_name(&pdev->parent);

    if (!rphy)
    {
        LOG_W("%s: remove with empty context", dev_name);
        return RT_EOK;
    }

    LOG_I("%s: remove", dev_name);
    pdev->parent.user_data = RT_NULL;

    rockchip_u2phy_unregister_ports(rphy);

    if (rt_clk_unregister(&rphy->clk_np))
    {
        LOG_W("%s: unregister 480m clk failed", dev_name);
    }

    rt_clk_disable_unprepare(rphy->phyclk);
    rt_clk_put(rphy->phyclk);

    if (!rt_is_err_or_null(rphy->phy_rst))
    {
        rt_reset_control_put(rphy->phy_rst);
    }

    rt_free(rphy);

    LOG_I("%s: remove done", dev_name);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_inno_usb2phy_ids[] =
{
    { .compatible = "rockchip,rk3568-usb2phy", .data = (void *)&rk3568_phy_cfgs },
    { /* sentinel */ },
};

static struct rt_platform_driver rockchip_inno_usb2phy_driver =
{
    .name = "phye-rockchip-inno-usb2",
    .ids = rockchip_inno_usb2phy_ids,

    .probe = rockchip_inno_usb2phy_probe,
    .remove = rockchip_inno_usb2phy_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_inno_usb2phy_driver);
