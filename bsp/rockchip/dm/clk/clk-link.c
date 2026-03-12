/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "clk.link"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct rockchip_link_data
{
    rt_size_t cells_nr;
    struct rt_clk_cell **cells;
};

struct rockchip_link_cell
{
    struct rt_clk_cell cell;
    rt_uint32_t bit_idx;
};

#define cell_to_rockchip_link_cell(cell) rt_container_of(cell, struct rockchip_link_cell, cell)

struct rockchip_link_clk
{
    struct rt_clk_node parent;

    void *base;
};

#define raw_to_rockchip_link_clk(raw) rt_container_of(raw, struct rockchip_link_clk, parent)

static void clk_gate_endisable(struct rt_clk_cell *cell, int enable)
{
    rt_uint32_t reg;
    int set = 1 ^ enable;
    struct rockchip_link_cell *link_cell = cell_to_rockchip_link_cell(cell);
    struct rockchip_link_clk *link_clk = raw_to_rockchip_link_clk(cell->clk_np);

    reg = RT_BIT(link_cell->bit_idx + 16);

    if (set)
    {
        reg |= RT_BIT(link_cell->bit_idx);
    }

    HWREG32(link_clk->base) = reg;
}

static rt_err_t rockchip_link_clk_enable(struct rt_clk_cell *cell)
{
    clk_gate_endisable(cell, 1);

    return RT_EOK;
}

static void rockchip_link_clk_disable(struct rt_clk_cell *cell)
{
    clk_gate_endisable(cell, 0);
}

static rt_bool_t rockchip_link_clk_is_enabled(struct rt_clk_cell *cell)
{
    rt_uint32_t reg;
    struct rockchip_link_cell *link_cell = cell_to_rockchip_link_cell(cell);
    struct rockchip_link_clk *link_clk = raw_to_rockchip_link_clk(cell->clk_np);

    reg = HWREG32(link_clk->base);
    reg ^= RT_BIT(link_cell->bit_idx);
    reg &= RT_BIT(link_cell->bit_idx);

    return !!reg;
}

const struct rt_clk_ops clk_gate_ops =
{
    .enable = rockchip_link_clk_enable,
    .disable = rockchip_link_clk_disable,
    .is_enabled = rockchip_link_clk_is_enabled,
};

#define GATE_LINK(_name, _pname, _bit_idx)  \
(void *)&(struct rockchip_link_cell)        \
{                                           \
    .cell.name = _name,                     \
    .cell.parents_nr = 1,                   \
    .cell.parent_name = _pname,             \
    .cell.ops = &clk_gate_ops,              \
    .cell.flags = RT_CLK_F_SET_RATE_PARENT, \
    .bit_idx = _bit_idx,                    \
}

static struct rt_clk_cell *rk3562_clk_cells[] =
{
    GATE_LINK("aclk_rga_jdec", "aclk_rga_pre", 3),
    GATE_LINK("aclk_vdpu", "aclk_vdpu_pre", 5),
    GATE_LINK("aclk_vepu", "aclk_vepu_pre", 3),
    GATE_LINK("aclk_vi_isp", "aclk_vi", 3),
    GATE_LINK("aclk_vo", "aclk_vo_pre", 3),
    GATE_LINK("hclk_vepu", "hclk_vepu_pre", 4),
};

static const struct rockchip_link_data rk3562_clk_data =
{
    .cells = rk3562_clk_cells,
    .cells_nr = RT_ARRAY_SIZE(rk3562_clk_cells),
};

static struct rt_clk_cell *rk3588_clk_cells[] =
{
    GATE_LINK("aclk_isp1_pre", "aclk_isp1_root", 6),
    GATE_LINK("hclk_isp1_pre", "hclk_isp1_root", 8),
    GATE_LINK("hclk_nvm", "hclk_nvm_root", 2),
    GATE_LINK("aclk_usb", "aclk_usb_root", 2),
    GATE_LINK("hclk_usb", "hclk_usb_root", 3),
    GATE_LINK("aclk_jpeg_decoder_pre", "aclk_jpeg_decoder_root", 7),
    GATE_LINK("aclk_vdpu_low_pre", "aclk_vdpu_low_root", 5),
    GATE_LINK("aclk_rkvenc1_pre", "aclk_rkvenc1_root", 3),
    GATE_LINK("hclk_rkvenc1_pre", "hclk_rkvenc1_root", 2),
    GATE_LINK("hclk_rkvdec0_pre", "hclk_rkvdec0_root", 5),
    GATE_LINK("aclk_rkvdec0_pre", "aclk_rkvdec0_root", 6),
    GATE_LINK("hclk_rkvdec1_pre", "hclk_rkvdec1_root", 4),
    GATE_LINK("aclk_rkvdec1_pre", "aclk_rkvdec1_root", 5),
    GATE_LINK("aclk_hdcp0_pre", "aclk_vo0_root", 9),
    GATE_LINK("hclk_vo0", "hclk_vo0_root", 5),
    GATE_LINK("aclk_hdcp1_pre", "aclk_hdcp1_root", 6),
    GATE_LINK("hclk_vo1", "hclk_vo1_root", 9),
    GATE_LINK("aclk_av1_pre", "aclk_av1_root", 1),
    GATE_LINK("pclk_av1_pre", "pclk_av1_root", 4),
    GATE_LINK("hclk_sdio_pre", "hclk_sdio_root", 1),
    GATE_LINK("pclk_vo0_grf", "pclk_vo0_root", 10),
    GATE_LINK("pclk_vo1_grf", "pclk_vo1_root", 12),
};

static const struct rockchip_link_data rk3588_clk_data =
{
    .cells = rk3588_clk_cells,
    .cells_nr = RT_ARRAY_SIZE(rk3588_clk_cells),
};

static rt_err_t rockchip_clk_link_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    const struct rockchip_link_data *clk_data = pdev->id->data;
    struct rockchip_link_clk *link_clk = rt_calloc(1, sizeof(*link_clk));

    if (!link_clk)
    {
        return -RT_ENOMEM;
    }

    if (!(link_clk->base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    link_clk->parent.dev = dev;
    link_clk->parent.cells = clk_data->cells;
    link_clk->parent.cells_nr = clk_data->cells_nr;

    if ((err = rt_clk_register(&link_clk->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (link_clk->base)
    {
        rt_iounmap(link_clk->base);
    }

    rt_free(link_clk);

    return err;
}

static const struct rt_ofw_node_id rockchip_clk_link_ofw_ids[] =
{
    { .compatible = "rockchip,rk3562-clock-gate-link", .data = &rk3562_clk_data },
    { .compatible = "rockchip,rk3588-clock-gate-link", .data = &rk3588_clk_data },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_clk_link_driver =
{
    .name = "clk-link",
    .ids = rockchip_clk_link_ofw_ids,

    .probe = rockchip_clk_link_probe,
};

static int rockchip_clk_link_register(void)
{
    rt_platform_driver_register(&rockchip_clk_link_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rockchip_clk_link_register);
