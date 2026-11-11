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

#define DBG_TAG "dsi2.rk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define UPDATE(v, h, l)                 (((v) << (l)) & (((2U << (h)) - 1U) & ~((1U << (l)) - 1U)))
#define GRF_REG_FIELD(reg, lsb, msb)    (((reg) << 16) | ((lsb) << 8) | (msb))

#define DSI2_PWR_UP                     0x000c
#define DSI2_SOFT_RESET                 0x0010
#define DSI2_MODE_CTRL                  0x0018
#define DSI2_MODE_STATUS                0x001c
#define DSI2_CORE_STATUS                0x0020
#define MANUAL_MODE_CFG                 0x0024
#define DSI2_PHY_MODE_CFG               0x0100
#define DSI2_PHY_CLK_CFG                0x0104
#define DSI2_PHY_IPI_RATIO_MAN_CFG      0x0134
#define DSI2_DSI_GENERAL_CFG            0x0200
#define DSI2_DSI_VCID_CFG               0x0204
#define DSI2_DSI_VID_TX_CFG             0x020c
#define DSI2_IPI_COLOR_MAN_CFG          0x0300
#define DSI2_IPI_VID_HSA_MAN_CFG        0x0304
#define DSI2_IPI_VID_HBP_MAN_CFG        0x030c
#define DSI2_IPI_VID_HACT_MAN_CFG       0x0314
#define DSI2_IPI_VID_HLINE_MAN_CFG      0x031c
#define DSI2_IPI_VID_VSA_MAN_CFG        0x0324
#define DSI2_IPI_VID_VBP_MAN_CFG        0x032c
#define DSI2_IPI_VID_VACT_MAN_CFG       0x0334
#define DSI2_IPI_VID_VFP_MAN_CFG        0x033c
#define DSI2_IPI_PIX_PKT_CFG            0x0344
#define DSI2_CRI_TX_HDR                 0x02c0
#define DSI2_CRI_TX_PLD                 0x02c4

#define POWER_UP                        RT_BIT(0)
#define SYS_RSTN                        RT_BIT(2)
#define PHY_RSTN                        RT_BIT(1)
#define IPI_RSTN                        RT_BIT(0)
#define MANUAL_MODE_EN                  RT_BIT(0)
#define COMMAND_MODE                    3
#define VIDEO_MODE                      4
#define BTA_EN                          RT_BIT(1)
#define EOTP_TX_EN                      RT_BIT(0)
#define CRI_BUSY                        RT_BIT(16)
#define CRT_FIFOS_NOT_EMPTY             RT_BIT(17)
#define PPI_WIDTH_16_BITS               1
#define DPHY                            0
#define IPI_DEPTH_8_BITS                0x05
#define IPI_FORMAT_RGB                  0x0
#define VID_MODE_TYPE_BURST             2
#define CMD_TX_MODE(x)                  UPDATE(x, 24, 24)
#define NON_CONTINUOUS_CLK              RT_BIT(0)

#define MIPI_DSI_MODE_VIDEO             RT_BIT(0)
#define MIPI_DSI_MODE_VIDEO_BURST       RT_BIT(3)
#define MIPI_DSI_MODE_LPM               RT_BIT(4)
#define MIPI_DSI_MODE_NO_EOT_PACKET     RT_BIT(5)

#define IPI_COLOR_DEPTH                 GRF_REG_FIELD(0x0028, 8, 11)
#define IPI_FORMAT                      GRF_REG_FIELD(0x0028, 4, 7)

enum dsi2_grf_field
{
    GRF_IPI_COLOR_DEPTH,
    GRF_IPI_FORMAT,
};

struct rk_dsi2
{
    struct rt_device *dev;
    void *regs;
    struct rt_clk_array *clks;
    struct rt_syscon *grf;
    struct rt_phye *dcphy;
    rt_uint32_t lanes;
    rt_uint32_t channel;
    rt_uint32_t mode_flags;
    rt_uint64_t lane_hs_rate;
    struct display_timing mode;
    rt_bool_t prepared;
    rt_bool_t phy_on;
    rt_bool_t video_on;
};

static rt_err_t rk_dsi2_parse_panel_props(struct rk_dsi2 *dsi2, struct rt_ofw_node *panel_np);
static void rk_dsi2_bind_panel(struct rk_dsi2 *dsi2);

rt_inline void dsi2_write(struct rk_dsi2 *dsi2, rt_uint32_t reg, rt_uint32_t val)
{
    HWREG32((rt_uint8_t *)dsi2->regs + reg) = val;
}

rt_inline rt_uint32_t dsi2_read(struct rk_dsi2 *dsi2, rt_uint32_t reg)
{
    return HWREG32((rt_uint8_t *)dsi2->regs + reg);
}

static void rk_dsi2_grf_field_write(struct rk_dsi2 *dsi2, rt_uint32_t field, rt_uint32_t val)
{
    rt_uint32_t reg = (field >> 16) & 0xffff;
    rt_uint8_t lsb = (field >> 8) & 0xff;
    rt_uint8_t msb = field & 0xff;
    rt_uint32_t mask = RT_GENMASK(msb, lsb);

    if (!dsi2->grf || !field)
    {
        return;
    }

    rt_syscon_write(dsi2->grf, reg, ((val << lsb) & mask) | (mask << 16));
}

static rt_err_t rk_dsi2_wait_mode(struct rk_dsi2 *dsi2, rt_uint32_t mode, rt_int32_t timeout_us)
{
    rt_int32_t i;

    for (i = 0; i < timeout_us; ++i)
    {
        if ((dsi2_read(dsi2, DSI2_MODE_STATUS) & mode) == mode)
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t rk_dsi2_cri_wait(struct rk_dsi2 *dsi2)
{
    rt_uint32_t sts;
    rt_int32_t i;

    for (i = 0; i < 20000; ++i)
    {
        sts = dsi2_read(dsi2, DSI2_CORE_STATUS);

        if (!(sts & (CRI_BUSY | CRT_FIFOS_NOT_EMPTY)))
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    return -RT_ETIMEOUT;
}

static void rk_dsi2_set_cmd_mode(struct rk_dsi2 *dsi2)
{
    dsi2_write(dsi2, DSI2_MODE_CTRL, COMMAND_MODE);
    rk_dsi2_wait_mode(dsi2, COMMAND_MODE, 10000);
}

static void rk_dsi2_set_video_mode(struct rk_dsi2 *dsi2)
{
    dsi2_write(dsi2, DSI2_MODE_CTRL, VIDEO_MODE);
    rk_dsi2_wait_mode(dsi2, VIDEO_MODE, 10000);
}

static void dsi2_host_reset(struct rk_dsi2 *dsi2)
{
    dsi2_write(dsi2, DSI2_SOFT_RESET, 0);
    rt_thread_mdelay(1);
    dsi2_write(dsi2, DSI2_SOFT_RESET, SYS_RSTN | PHY_RSTN | IPI_RSTN);
}

static void dsi2_phy_basic_cfg(struct rk_dsi2 *dsi2)
{
    rt_uint32_t val;

    val = UPDATE(PPI_WIDTH_16_BITS, 9, 8) |
          UPDATE((dsi2->lanes - 1) & 0x3, 5, 4) |
          UPDATE(DPHY, 0, 0);
    dsi2_write(dsi2, DSI2_PHY_MODE_CFG, val);
    dsi2_write(dsi2, DSI2_PHY_CLK_CFG, NON_CONTINUOUS_CLK);
}

static void rk_dsi2_grf_ipi_cfg(struct rk_dsi2 *dsi2)
{
    rk_dsi2_grf_field_write(dsi2, IPI_COLOR_DEPTH, IPI_DEPTH_8_BITS);
    rk_dsi2_grf_field_write(dsi2, IPI_FORMAT, IPI_FORMAT_RGB);
}

static rt_uint64_t rk_dsi2_calc_lane_rate(struct rk_dsi2 *dsi2, const struct display_timing *tim)
{
    rt_uint64_t pixelclock = tim->pixelclock;
    rt_uint32_t value;
    rt_uint64_t tmp;

    if (!pixelclock)
    {
        pixelclock = (rt_uint64_t)tim->htotal * tim->vtotal * 60;
    }

    if (dsi2->dev && !rt_dm_dev_prop_read_u32(dsi2->dev, "rockchip,lane-rate", &value))
    {
        if (value >= 80 && value <= 4500)
        {
            return value;
        }
    }

    tmp = pixelclock * 24 / dsi2->lanes / 1000000;

    if (dsi2->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
    {
        tmp = tmp * 10 / 9;
    }

    if (tmp < 200)
    {
        tmp = 500;
    }

    return tmp;
}

static void dsi2_ipi_timing(struct rk_dsi2 *dsi2, const struct display_timing *tim)
{
    rt_uint64_t pixel_clk, phy_hs_clk, tmp;
    rt_uint32_t hsa_time, hbp_time, hact_time, hline_time;

    if (!tim->pixelclock)
    {
        return;
    }

    pixel_clk = tim->pixelclock;
    phy_hs_clk = dsi2->lane_hs_rate * 1000000ULL / 16ULL;

    tmp = (rt_uint64_t)tim->hsync_len * phy_hs_clk;
    hsa_time = (rt_uint32_t)((tmp << 16) / pixel_clk);
    dsi2_write(dsi2, DSI2_IPI_VID_HSA_MAN_CFG, hsa_time);

    tmp = (rt_uint64_t)tim->hback_porch * phy_hs_clk;
    hbp_time = (rt_uint32_t)((tmp << 16) / pixel_clk);
    dsi2_write(dsi2, DSI2_IPI_VID_HBP_MAN_CFG, hbp_time);

    tmp = (rt_uint64_t)tim->hactive * phy_hs_clk;
    hact_time = (rt_uint32_t)((tmp << 16) / pixel_clk);
    dsi2_write(dsi2, DSI2_IPI_VID_HACT_MAN_CFG, hact_time);

    tmp = (rt_uint64_t)tim->htotal * phy_hs_clk;
    hline_time = (rt_uint32_t)((tmp << 16) / pixel_clk);
    dsi2_write(dsi2, DSI2_IPI_VID_HLINE_MAN_CFG, hline_time);

    dsi2_write(dsi2, DSI2_IPI_VID_VSA_MAN_CFG, tim->vsync_len);
    dsi2_write(dsi2, DSI2_IPI_VID_VBP_MAN_CFG, tim->vback_porch);
    dsi2_write(dsi2, DSI2_IPI_VID_VACT_MAN_CFG, tim->vactive);
    dsi2_write(dsi2, DSI2_IPI_VID_VFP_MAN_CFG, tim->vfront_porch);
    dsi2_write(dsi2, DSI2_IPI_PIX_PKT_CFG, tim->hactive);

    tmp = ((phy_hs_clk << 16) / pixel_clk);
    dsi2_write(dsi2, DSI2_PHY_IPI_RATIO_MAN_CFG, (rt_uint32_t)tmp);
}

static rt_err_t rk_dsi2_build_packet(rt_uint8_t data_type, const rt_uint8_t *payload,
        rt_size_t len, rt_uint8_t header[4], rt_uint32_t *pld)
{
    rt_size_t i;

    rt_memset(header, 0, 4);
    header[0] = data_type;

    switch (data_type)
    {
    case 0x05:
    case 0x15:
        if (len >= 1)
        {
            header[1] = payload[0];
        }
        if (len >= 2 && data_type == 0x15)
        {
            header[2] = payload[1];
        }
        break;
    case 0x23:
    case 0x13:
    case 0x03:
        if (len >= 1)
        {
            header[1] = payload[0];
        }
        if (len >= 2)
        {
            header[2] = payload[1];
        }
        break;
    case 0x39:
    case 0x29:
        header[1] = len & 0xff;
        header[2] = (len >> 8) & 0xff;
        *pld = 0;
        for (i = 0; i < len && i < 4; ++i)
        {
            ((rt_uint8_t *)pld)[i] = payload[i];
        }
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t rk_dsi2_transfer(void *priv, rt_uint8_t data_type, rt_uint8_t delay_ms,
        const rt_uint8_t *payload, rt_size_t len)
{
    struct rk_dsi2 *dsi2 = priv;
    rt_uint8_t header[4];
    rt_uint32_t pld = 0;
    rt_uint32_t hdr;
    rt_err_t err;
    rt_bool_t lpm = !!(dsi2->mode_flags & MIPI_DSI_MODE_LPM);

    if (!dsi2 || !dsi2->prepared)
    {
        return -RT_EINVAL;
    }

    rk_dsi2_set_cmd_mode(dsi2);

    if ((err = rk_dsi2_build_packet(data_type, payload, len, header, &pld)))
    {
        return err;
    }

    if ((err = rk_dsi2_cri_wait(dsi2)))
    {
        return err;
    }

    if (data_type == 0x39 || data_type == 0x29)
    {
        rt_size_t off = 0;
        rt_uint32_t val;

        while (off < len)
        {
            rt_size_t chunk = len - off;

            if (chunk >= 4)
            {
                val = payload[off] | (payload[off + 1] << 8) |
                      (payload[off + 2] << 16) | (payload[off + 3] << 24);
                off += 4;
            }
            else
            {
                val = 0;
                rt_memcpy(&val, &payload[off], chunk);
                off = len;
            }

            dsi2_write(dsi2, DSI2_CRI_TX_PLD, val);
        }
    }

    hdr = header[0] | (header[1] << 8) | (header[2] << 16) | (header[3] << 24);
    dsi2_write(dsi2, DSI2_CRI_TX_HDR, CMD_TX_MODE(lpm ? 1 : 0) | hdr);

    if ((err = rk_dsi2_cri_wait(dsi2)))
    {
        return err;
    }

    if (delay_ms)
    {
        rt_thread_mdelay(delay_ms);
    }

    return RT_EOK;
}

static rt_err_t rk_dsi2_phy_up(struct rk_dsi2 *dsi2)
{
    rt_err_t err;
    union rt_phye_configure_opts phy_opts;

    if (!dsi2->dcphy || dsi2->phy_on)
    {
        return RT_EOK;
    }

    if ((err = rt_phye_set_mode_simple(dsi2->dcphy, RT_PHYE_MODE_MIPI_DPHY)))
    {
        return err;
    }

    if ((err = rt_phye_mipi_dphy_get_default_config_for_hsclk(
            dsi2->lane_hs_rate * 1000000ULL, dsi2->lanes, &phy_opts.mipi_dphy)))
    {
        return err;
    }

    if ((err = rt_phye_configure(dsi2->dcphy, &phy_opts)))
    {
        return err;
    }

    dsi2->lane_hs_rate = phy_opts.mipi_dphy.hs_clk_rate / 1000000ULL;

    if ((err = rt_phye_init(dsi2->dcphy)))
    {
        return err;
    }

    if ((err = rt_phye_power_on(dsi2->dcphy)))
    {
        rt_phye_exit(dsi2->dcphy);
        return err;
    }

    dsi2->phy_on = RT_TRUE;

    return RT_EOK;
}

static void rk_dsi2_phy_down(struct rk_dsi2 *dsi2)
{
    if (!dsi2->dcphy || !dsi2->phy_on)
    {
        return;
    }

    rt_phye_power_off(dsi2->dcphy);
    rt_phye_exit(dsi2->dcphy);
    dsi2->phy_on = RT_FALSE;
}

static rt_err_t rk_dsi2_prepare(void *priv, rt_uint32_t vp_id, const struct display_timing *tim)
{
    struct rk_dsi2 *dsi2 = priv;
    rt_err_t err;

    RT_UNUSED(vp_id);

    if (!dsi2 || !tim)
    {
        return -RT_EINVAL;
    }

    dsi2->mode = *tim;
    dsi2->lane_hs_rate = rk_dsi2_calc_lane_rate(dsi2, tim);

    rt_clk_array_prepare_enable(dsi2->clks);

    if ((err = rk_dsi2_phy_up(dsi2)))
    {
        rt_clk_array_disable_unprepare(dsi2->clks);
        return err;
    }

    dsi2_write(dsi2, DSI2_PWR_UP, 0);
    dsi2_host_reset(dsi2);
    dsi2_phy_basic_cfg(dsi2);
    dsi2_write(dsi2, MANUAL_MODE_CFG, MANUAL_MODE_EN);
    rk_dsi2_grf_ipi_cfg(dsi2);
    rk_dsi2_set_cmd_mode(dsi2);

    dsi2->prepared = RT_TRUE;
    dsi2->video_on = RT_FALSE;

    return RT_EOK;
}

static rt_err_t rk_dsi2_mode_set(void *priv, const struct display_timing *tim)
{
    struct rk_dsi2 *dsi2 = priv;
    rt_uint32_t val;
    rt_uint32_t vid_mode = (dsi2->mode_flags & MIPI_DSI_MODE_VIDEO_BURST) ?
            VID_MODE_TYPE_BURST : 1;
    rt_uint32_t general = BTA_EN;

    if (!dsi2 || !tim)
    {
        return -RT_EINVAL;
    }

    dsi2->mode = *tim;

    if (!dsi2->mode.pixelclock)
    {
        dsi2->mode.pixelclock = (rt_uint64_t)tim->htotal * tim->vtotal * 60;
    }

    val = UPDATE(IPI_DEPTH_8_BITS, 7, 4) | UPDATE(IPI_FORMAT_RGB, 3, 0);
    dsi2_write(dsi2, DSI2_IPI_COLOR_MAN_CFG, val);

    if (!(dsi2->mode_flags & MIPI_DSI_MODE_NO_EOT_PACKET))
    {
        general |= EOTP_TX_EN;
    }

    dsi2_write(dsi2, DSI2_DSI_GENERAL_CFG, general);
    dsi2_write(dsi2, DSI2_DSI_VCID_CFG, dsi2->channel & 0x3);
    dsi2_write(dsi2, DSI2_DSI_VID_TX_CFG, UPDATE(vid_mode, 1, 0));

    dsi2_ipi_timing(dsi2, &dsi2->mode);
    rk_dsi2_set_video_mode(dsi2);
    dsi2_write(dsi2, DSI2_PWR_UP, POWER_UP);

    dsi2->video_on = RT_TRUE;

    return RT_EOK;
}

static rt_err_t rk_dsi2_enable(void *priv, rt_bool_t enable)
{
    struct rk_dsi2 *dsi2 = priv;

    if (!dsi2)
    {
        return -RT_EINVAL;
    }

    if (enable)
    {
        if (!dsi2->prepared || !dsi2->video_on)
        {
            return -RT_EINVAL;
        }

        dsi2_write(dsi2, DSI2_PWR_UP, POWER_UP);
    }
    else
    {
        dsi2_write(dsi2, DSI2_PWR_UP, 0);
    }

    return RT_EOK;
}

static rt_err_t rk_dsi2_disable(void *priv)
{
    struct rk_dsi2 *dsi2 = priv;

    if (!dsi2)
    {
        return -RT_EINVAL;
    }

    rk_dsi2_enable(priv, RT_FALSE);
    rk_dsi2_phy_down(dsi2);
    rt_clk_array_disable_unprepare(dsi2->clks);
    dsi2->prepared = RT_FALSE;
    dsi2->video_on = RT_FALSE;

    return RT_EOK;
}

static const struct rockchip_connector_ops rk_dsi2_connector_ops =
{
    .prepare = rk_dsi2_prepare,
    .mode_set = rk_dsi2_mode_set,
    .transfer = rk_dsi2_transfer,
    .enable = rk_dsi2_enable,
    .disable = rk_dsi2_disable,
};

static rt_err_t rk_dsi2_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct rk_dsi2 *dsi2 = rt_calloc(1, sizeof(*dsi2));

    if (!dsi2)
    {
        return -RT_ENOMEM;
    }

    dsi2->regs = rt_ofw_iomap(np, 0);

    if (!dsi2->regs)
    {
        rt_free(dsi2);
        return -RT_EIO;
    }

    dsi2->clks = rt_clk_get_array(dev);

    if (rt_is_err(dsi2->clks))
    {
        rt_iounmap(dsi2->regs);
        rt_free(dsi2);
        return rt_ptr_err(dsi2->clks);
    }

    dsi2->dev = dev;
    dsi2->grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf");

    dsi2->lanes = 4;
    dsi2->channel = 0;
    rt_dm_dev_prop_read_u32(dev, "rockchip,dsi,lanes", &dsi2->lanes);
    rt_dm_dev_prop_read_u32(dev, "rockchip,dsi,channel", &dsi2->channel);

    dsi2->dcphy = rt_phye_get_by_name(dev, "dcphy");
    if (rt_is_err(dsi2->dcphy))
    {
        dsi2->dcphy = RT_NULL;
    }

    rockchip_display_register_connector(np, &rk_dsi2_connector_ops, dsi2);
    rk_dsi2_bind_panel(dsi2);

    pdev->parent.user_data = dsi2;

    LOG_D("DSI2 %s: %u lanes", np->name, dsi2->lanes);

    return RT_EOK;
}

static rt_err_t rk_dsi2_parse_panel_props(struct rk_dsi2 *dsi2, struct rt_ofw_node *panel_np)
{
    rt_uint32_t flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
            MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_NO_EOT_PACKET;

    if (!panel_np)
    {
        dsi2->mode_flags = flags;
        return RT_EOK;
    }

    rt_ofw_prop_read_u32(panel_np, "dsi,flags", &flags);
    rt_ofw_prop_read_u32(panel_np, "dsi,lanes", &dsi2->lanes);

    dsi2->mode_flags = flags;

    return RT_EOK;
}

static void rk_dsi2_bind_panel(struct rk_dsi2 *dsi2)
{
    struct rt_ofw_node *np = dsi2->dev->ofw_node;
    struct rt_ofw_node *child, *ports_np = RT_NULL, *port_np, *ep_np, *remote;

    rt_ofw_foreach_child_node(np, child)
    {
        if (!rt_strcmp(child->name, "ports"))
        {
            ports_np = child;
            break;
        }
    }

    if (!ports_np)
    {
        dsi2->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
                MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_NO_EOT_PACKET;
        return;
    }

    rt_ofw_foreach_child_node(ports_np, port_np)
    {
        rt_ofw_foreach_child_node(port_np, ep_np)
        {
            remote = rt_ofw_parse_phandle(ep_np, "remote-endpoint", 0);

            if (!remote)
            {
                continue;
            }

            port_np = rt_ofw_get_parent(remote);

            if (port_np)
            {
                rk_dsi2_parse_panel_props(dsi2, rt_ofw_get_parent(port_np));
            }

            rt_ofw_node_put(remote);
            return;
        }
    }
}

static const struct rt_ofw_node_id rk_dsi2_ids[] =
{
    { .compatible = "rockchip,rk3576-mipi-dsi2" },
    { /* sentinel */ }
};

static struct rt_platform_driver rk_dsi2_driver =
{
    .name = "dw-mipi-dsi2-rockchip",
    .ids = rk_dsi2_ids,
    .probe = rk_dsi2_probe,
    .remove = RT_NULL,
};
RT_PLATFORM_DRIVER_EXPORT(rk_dsi2_driver);
