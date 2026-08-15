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

#define DBG_TAG "dsi.rk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define DSI_VERSION                     0x00
#define DSI_PWR_UP                      0x04
#define DSI_CLKMGR_CFG                  0x08
#define DSI_DPI_VCID                    0x0c
#define DSI_DPI_COLOR_CODING            0x10
#define DSI_DPI_CFG_POL                 0x14
#define DSI_DPI_LP_CMD_TIM              0x18
#define DSI_PCKHDL_CFG                  0x2c
#define DSI_MODE_CFG                    0x34
#define DSI_VID_MODE_CFG                0x38
#define DSI_VID_PKT_SIZE                0x3c
#define DSI_VID_NUM_CHUNKS              0x40
#define DSI_VID_NULL_SIZE               0x44
#define DSI_VID_HSA_TIME                0x48
#define DSI_VID_HBP_TIME                0x4c
#define DSI_VID_HLINE_TIME              0x50
#define DSI_VID_VSA_LINES               0x54
#define DSI_VID_VBP_LINES               0x58
#define DSI_VID_VFP_LINES               0x5c
#define DSI_VID_VACTIVE_LINES           0x60
#define DSI_EDPI_CMD_SIZE               0x64
#define DSI_CMD_MODE_CFG                0x68
#define DSI_GEN_HDR                     0x6c
#define DSI_GEN_PLD_DATA                0x70
#define DSI_CMD_PKT_STATUS              0x74
#define DSI_TO_CNT_CFG                  0x78
#define DSI_BTA_TO_CNT                  0x8c
#define DSI_LPCLK_CTRL                  0x94
#define DSI_PHY_TMR_LPCLK_CFG           0x98
#define DSI_PHY_TMR_CFG                 0x9c
#define DSI_PHY_RSTZ                    0xa0
#define DSI_PHY_IF_CFG                  0xa4
#define DSI_PHY_STATUS                  0xb0
#define DSI_PHY_TST_CTRL0               0xb4
#define DSI_INT_ST0                     0xbc
#define DSI_INT_ST1                     0xc0
#define DSI_INT_MSK0                    0xc4
#define DSI_INT_MSK1                    0xc8
#define DSI_PHY_TMR_RD_CFG              0xf4

#define DSI_POWERUP                     RT_BIT(0)
#define DSI_CMD_MODE                    RT_BIT(0)
#define DSI_VIDEO_MODE                  0

#define DSI_TO_CLK_DIV(x)               (((x) & 0xff) << 8)
#define DSI_TX_ESC_CLK_DIV(x)           ((x) & 0xff)

#define DSI_DPI_COLOR_16BIT             0x0
#define DSI_DPI_COLOR_18BIT_PACKED      0x3
#define DSI_DPI_COLOR_18BIT_LOOSE       (0x4 | RT_BIT(8))
#define DSI_DPI_COLOR_24BIT             0x5
#define DSI_HSYNC_ACTIVE_LOW            RT_BIT(2)
#define DSI_VSYNC_ACTIVE_LOW            RT_BIT(1)

#define DSI_CRC_RX_EN                   RT_BIT(4)
#define DSI_ECC_RX_EN                   RT_BIT(3)
#define DSI_BTA_EN                      RT_BIT(2)
#define DSI_EOTP_RX_EN                  RT_BIT(1)
#define DSI_EOTP_TX_EN                  RT_BIT(0)

#define DSI_LP_HFP_EN                   RT_BIT(13)
#define DSI_LP_HBP_EN                   RT_BIT(12)
#define DSI_LP_VACT_EN                  RT_BIT(11)
#define DSI_LP_VFP_EN                   RT_BIT(10)
#define DSI_LP_VBP_EN                   RT_BIT(9)
#define DSI_LP_VSA_EN                   RT_BIT(8)
#define DSI_ENABLE_LP_CMD               RT_BIT(15)
#define DSI_VID_MODE_BURST              0x2
#define DSI_VID_MODE_SYNC_PULSE         0x0
#define DSI_VID_MODE_SYNC_EVENT         0x1
#define DSI_VID_MODE_VPG_ENABLE         RT_BIT(16)
#define DSI_VID_MODE_VPG_BER            RT_BIT(20)
#define DSI_VID_MODE_VPG_HORIZONTAL     RT_BIT(24)

#define DSI_CMD_MODE_ALL_LP             (RT_BIT(24) | RT_BIT(19) | RT_BIT(18) | \
                                         RT_BIT(17) | RT_BIT(16) | RT_BIT(14) | \
                                         RT_BIT(13) | RT_BIT(12) | RT_BIT(11) | \
                                         RT_BIT(10) | RT_BIT(9) | RT_BIT(8))

#define DSI_GEN_PLD_W_FULL              RT_BIT(3)
#define DSI_GEN_PLD_W_EMPTY             RT_BIT(2)
#define DSI_GEN_CMD_FULL                RT_BIT(1)
#define DSI_GEN_CMD_EMPTY               RT_BIT(0)
#define DSI_GEN_RD_CMD_BUSY             RT_BIT(6)
#define DSI_GEN_PLD_R_EMPTY             RT_BIT(4)

#define DSI_PHY_TXREQUESTCLKHS          RT_BIT(0)
#define DSI_AUTO_CLKLANE_CTRL           RT_BIT(1)
#define DSI_PHY_LOCK                    RT_BIT(0)
#define DSI_PHY_STOP_CLK                RT_BIT(2)
#define DSI_PHY_ENABLE                  0x0f

#define MIPI_DSI_MODE_VIDEO             RT_BIT(0)
#define MIPI_DSI_MODE_VIDEO_BURST       RT_BIT(1)
#define MIPI_DSI_MODE_VIDEO_SYNC_PULSE  RT_BIT(2)
#define MIPI_DSI_MODE_VIDEO_NO_HFP      RT_BIT(5)
#define MIPI_DSI_MODE_VIDEO_NO_HBP      RT_BIT(6)
#define MIPI_DSI_MODE_NO_EOT_PACKET     RT_BIT(9)
#define MIPI_DSI_CLOCK_NON_CONTINUOUS   RT_BIT(10)
#define MIPI_DSI_MODE_LPM               RT_BIT(11)

#define MIPI_DSI_FMT_RGB888             0
#define MIPI_DSI_FMT_RGB666             1
#define MIPI_DSI_FMT_RGB666_PACKED      2
#define MIPI_DSI_FMT_RGB565             3

#define RK3568_GRF_VO_CON2              0x0368
#define RK3568_GRF_VO_CON3              0x036c
#define RK3568_DSI_LANE_CFG_MASK        ((0x1f << 11) | (0xf << 4) | RT_BIT(2) | RT_BIT(0))
#define HIWORD_UPDATE(v, m)             (((v) & (m)) | ((m) << 16))

#define DSI_FIFO_TIMEOUT_US             20000
#define DSI_PHY_TIMEOUT_US              20000

struct rk_dsi
{
    struct rt_device *dev;
    void *regs;
    struct rt_clk_array *clks;
    struct rt_reset_control *apb_rst;
    struct rt_syscon *grf;
    struct rt_phye *dphy;
    struct rt_ofw_node *panel_np;
    rt_uint32_t grf_lane_reg;
    rt_uint32_t lanes;
    rt_uint32_t channel;
    rt_uint32_t format;
    rt_uint32_t mode_flags;
    rt_uint32_t lane_mbps;
    rt_uint32_t id;
    struct display_timing mode;
    rt_bool_t prepared;
    rt_bool_t phy_on;
};

static struct rk_dsi *rk_dsi_instances[2];

rt_inline rt_uint32_t dsi_read(struct rk_dsi *dsi, rt_uint32_t reg)
{
    return HWREG32((rt_uint8_t *)dsi->regs + reg);
}

rt_inline void dsi_write(struct rk_dsi *dsi, rt_uint32_t reg, rt_uint32_t val)
{
    HWREG32((rt_uint8_t *)dsi->regs + reg) = val;
}

static rt_err_t rk_dsi_wait(struct rk_dsi *dsi, rt_uint32_t reg,
        rt_uint32_t mask, rt_uint32_t expected, rt_uint32_t timeout_us)
{
    while (timeout_us)
    {
        if ((dsi_read(dsi, reg) & mask) == expected)
        {
            return RT_EOK;
        }

        rt_hw_us_delay(10);
        timeout_us = timeout_us > 10 ? timeout_us - 10 : 0;
    }

    return -RT_ETIMEOUT;
}

static rt_bool_t rk_dsi_packet_is_long(rt_uint8_t type)
{
    return type == 0x19 || type == 0x29 || type == 0x39;
}

static rt_err_t rk_dsi_write_packet(struct rk_dsi *dsi, rt_uint8_t type,
        const rt_uint8_t *payload, rt_size_t len)
{
    rt_uint32_t header, word, status;
    rt_size_t i;

    if (rk_dsi_packet_is_long(type))
    {
        for (i = 0; i < len; i += sizeof(word))
        {
            rt_size_t chunk = len - i;

            if (rk_dsi_wait(dsi, DSI_CMD_PKT_STATUS, DSI_GEN_PLD_W_FULL, 0,
                    DSI_FIFO_TIMEOUT_US))
            {
                return -RT_ETIMEOUT;
            }

            if (chunk > sizeof(word))
            {
                chunk = sizeof(word);
            }

            word = 0;
            rt_memcpy(&word, &payload[i], chunk);
            dsi_write(dsi, DSI_GEN_PLD_DATA, word);
        }

        header = (type & 0x3f) | ((dsi->channel & 0x3) << 6) |
                ((len & 0xff) << 8) | (((len >> 8) & 0xff) << 16);
    }
    else
    {
        header = (type & 0x3f) | ((dsi->channel & 0x3) << 6);

        if (len)
        {
            header |= payload[0] << 8;
        }
        if (len > 1)
        {
            header |= payload[1] << 16;
        }
    }

    if (rk_dsi_wait(dsi, DSI_CMD_PKT_STATUS, DSI_GEN_CMD_FULL, 0,
            DSI_FIFO_TIMEOUT_US))
    {
        return -RT_ETIMEOUT;
    }

    dsi_write(dsi, DSI_GEN_HDR, header);
    status = DSI_GEN_CMD_EMPTY | DSI_GEN_PLD_W_EMPTY;

    return rk_dsi_wait(dsi, DSI_CMD_PKT_STATUS, status, status,
            DSI_FIFO_TIMEOUT_US);
}

static rt_err_t rk_dsi_transfer(void *priv, rt_uint8_t data_type, rt_uint8_t delay_ms,
        const rt_uint8_t *payload, rt_size_t len)
{
    struct rk_dsi *dsi = priv;
    rt_uint32_t val;
    rt_err_t err;

    if (!dsi || (!payload && len))
    {
        return -RT_EINVAL;
    }

    dsi_write(dsi, DSI_DPI_LP_CMD_TIM, (16 << 16) | 4);
    dsi_write(dsi, DSI_CMD_MODE_CFG,
            (dsi->mode_flags & MIPI_DSI_MODE_LPM) ? DSI_CMD_MODE_ALL_LP : 0);

    val = dsi_read(dsi, DSI_VID_MODE_CFG);
    if (dsi->mode_flags & MIPI_DSI_MODE_LPM)
    {
        val |= DSI_ENABLE_LP_CMD;
        dsi_write(dsi, DSI_LPCLK_CTRL,
                dsi_read(dsi, DSI_LPCLK_CTRL) & ~DSI_PHY_TXREQUESTCLKHS);
    }
    else
    {
        val &= ~DSI_ENABLE_LP_CMD;
        dsi_write(dsi, DSI_LPCLK_CTRL,
                dsi_read(dsi, DSI_LPCLK_CTRL) | DSI_PHY_TXREQUESTCLKHS);
    }
    dsi_write(dsi, DSI_VID_MODE_CFG, val);

    err = rk_dsi_write_packet(dsi, data_type, payload, len);

    if (delay_ms)
    {
        rt_thread_mdelay(delay_ms);
    }

    return err;
}

static rt_err_t rk_dsi_read_packet(struct rk_dsi *dsi, rt_uint8_t command,
        rt_uint8_t *payload, rt_size_t len)
{
    rt_uint8_t max_return[2];
    rt_uint32_t saved_power, saved_mode, saved_cmd, saved_lpclk, saved_video;
    rt_uint32_t status, val, word;
    rt_size_t i, j;
    rt_err_t err;

    if (!dsi || !payload || !len || len > 0xffff)
    {
        return -RT_EINVAL;
    }

    max_return[0] = len & 0xff;
    max_return[1] = (len >> 8) & 0xff;

    saved_power = dsi_read(dsi, DSI_PWR_UP);
    saved_mode = dsi_read(dsi, DSI_MODE_CFG);
    saved_cmd = dsi_read(dsi, DSI_CMD_MODE_CFG);
    saved_lpclk = dsi_read(dsi, DSI_LPCLK_CTRL);
    saved_video = dsi_read(dsi, DSI_VID_MODE_CFG);

    /* Stop the video stream before requesting bus turn-around. */
    dsi_write(dsi, DSI_PWR_UP, 0);
    dsi_write(dsi, DSI_MODE_CFG, DSI_CMD_MODE);
    dsi_write(dsi, DSI_DPI_LP_CMD_TIM, (16 << 16) | 4);
    dsi_write(dsi, DSI_CMD_MODE_CFG, DSI_CMD_MODE_ALL_LP);

    val = dsi_read(dsi, DSI_VID_MODE_CFG) | DSI_ENABLE_LP_CMD;
    dsi_write(dsi, DSI_VID_MODE_CFG, val);
    dsi_write(dsi, DSI_LPCLK_CTRL,
            dsi_read(dsi, DSI_LPCLK_CTRL) & ~DSI_PHY_TXREQUESTCLKHS);
    dsi_write(dsi, DSI_PWR_UP, DSI_POWERUP);

    err = rk_dsi_wait(dsi, DSI_PHY_STATUS, DSI_PHY_STOP_CLK,
            DSI_PHY_STOP_CLK, DSI_PHY_TIMEOUT_US);
    if (err)
    {
        goto _restore;
    }

    err = rk_dsi_write_packet(dsi, 0x37, max_return, sizeof(max_return));
    if (err)
    {
        goto _restore;
    }

    dsi_write(dsi, DSI_CMD_MODE_CFG, DSI_CMD_MODE_ALL_LP);
    err = rk_dsi_write_packet(dsi, 0x06, &command, 1);
    if (err)
    {
        goto _restore;
    }

    err = rk_dsi_wait(dsi, DSI_CMD_PKT_STATUS, DSI_GEN_RD_CMD_BUSY, 0,
            DSI_FIFO_TIMEOUT_US);
    if (err)
    {
        goto _restore;
    }

    for (i = 0; i < len; i += sizeof(word))
    {
        err = rk_dsi_wait(dsi, DSI_CMD_PKT_STATUS, DSI_GEN_PLD_R_EMPTY, 0,
                DSI_FIFO_TIMEOUT_US);
        if (err)
        {
            goto _restore;
        }

        word = dsi_read(dsi, DSI_GEN_PLD_DATA);
        for (j = 0; j < sizeof(word) && i + j < len; ++j)
        {
            payload[i + j] = (word >> (j * 8)) & 0xff;
        }
    }

    status = dsi_read(dsi, DSI_CMD_PKT_STATUS);
    if (!(status & DSI_GEN_PLD_R_EMPTY))
    {
        LOG_W("DCS read left data in RX FIFO, status=0x%08x", status);
    }

_restore:
    dsi_write(dsi, DSI_PWR_UP, 0);
    dsi_write(dsi, DSI_CMD_MODE_CFG, saved_cmd);
    dsi_write(dsi, DSI_VID_MODE_CFG, saved_video);
    dsi_write(dsi, DSI_LPCLK_CTRL, saved_lpclk);
    dsi_write(dsi, DSI_MODE_CFG, saved_mode);
    dsi_write(dsi, DSI_PWR_UP, saved_power);

    return err;
}

static rt_uint32_t rk_dsi_lbcc(struct rk_dsi *dsi, rt_uint32_t pixels)
{
    rt_uint64_t cycles;

    if (!dsi->mode.pixelclock)
    {
        return 0;
    }

    cycles = (rt_uint64_t)pixels * dsi->lane_mbps * 1000000ULL;
    cycles = (cycles + dsi->mode.pixelclock * 4) / (dsi->mode.pixelclock * 8);

    return (rt_uint32_t)cycles;
}

static void rk_dsi_set_mode(struct rk_dsi *dsi, rt_bool_t video)
{
    rt_uint32_t val;

    dsi_write(dsi, DSI_PWR_UP, 0);

    if (video)
    {
        val = DSI_LP_VSA_EN | DSI_LP_VBP_EN | DSI_LP_VFP_EN |
                DSI_LP_VACT_EN | DSI_LP_HBP_EN | DSI_LP_HFP_EN;

        if (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_NO_HFP)
        {
            val &= ~DSI_LP_HFP_EN;
        }
        if (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_NO_HBP)
        {
            val &= ~DSI_LP_HBP_EN;
        }

        if (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
        {
            val |= DSI_VID_MODE_BURST;
        }
        else if (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
        {
            val |= DSI_VID_MODE_SYNC_PULSE;
        }
        else
        {
            val |= DSI_VID_MODE_SYNC_EVENT;
        }

        dsi_write(dsi, DSI_VID_MODE_CFG, val);
        dsi_write(dsi, DSI_MODE_CFG, DSI_VIDEO_MODE);
    }
    else
    {
        dsi_write(dsi, DSI_MODE_CFG, DSI_CMD_MODE);
    }

    dsi_write(dsi, DSI_PWR_UP, DSI_POWERUP);
}

static rt_err_t rk_dsi_configure_phy(struct rk_dsi *dsi)
{
    union rt_phye_configure_opts opts;
    rt_uint64_t target_rate;
    rt_uint32_t bpp;
    rt_err_t err;

    if (!dsi->dphy)
    {
        return -RT_ENOSYS;
    }

    switch (dsi->format)
    {
    case MIPI_DSI_FMT_RGB565:
        bpp = 16;
        break;
    case MIPI_DSI_FMT_RGB666:
    case MIPI_DSI_FMT_RGB666_PACKED:
        bpp = 18;
        break;
    case MIPI_DSI_FMT_RGB888:
    default:
        bpp = 24;
        break;
    }

    /* Match Rockchip Linux's MHz-rounded external-PHY bandwidth calculation. */
    target_rate = RT_DIV_ROUND_UP_ULL(dsi->mode.pixelclock, 1000000ULL);
    target_rate = target_rate * (bpp / dsi->lanes) * 10 / 9;
    target_rate = (target_rate * dsi->lanes + bpp / 2) / bpp;
    target_rate = target_rate * bpp * 1000000ULL / dsi->lanes;

    rt_memset(&opts, 0, sizeof(opts));
    rt_phye_mipi_dphy_get_default_config_for_hsclk(target_rate, dsi->lanes,
            &opts.mipi_dphy);

    if ((err = rt_phye_set_mode_simple(dsi->dphy, RT_PHYE_MODE_MIPI_DPHY)))
    {
        return err;
    }
    if ((err = rt_phye_configure(dsi->dphy, &opts)))
    {
        return err;
    }

    dsi->lane_mbps = (rt_uint32_t)((opts.mipi_dphy.hs_clk_rate + 999999) / 1000000);

    return RT_EOK;
}

static void rk_dsi_host_config(struct rk_dsi *dsi)
{
    rt_uint32_t color, pol = 0, pckhdl, esc_div, hwver;

    esc_div = ((dsi->lane_mbps / 8) + 19) / 20;
    if (!esc_div)
    {
        esc_div = 1;
    }

    dsi_write(dsi, DSI_PWR_UP, 0);
    dsi_write(dsi, DSI_CLKMGR_CFG, DSI_TO_CLK_DIV(10) | DSI_TX_ESC_CLK_DIV(esc_div));

    switch (dsi->format)
    {
    case MIPI_DSI_FMT_RGB565:
        color = DSI_DPI_COLOR_16BIT;
        break;
    case MIPI_DSI_FMT_RGB666:
        color = DSI_DPI_COLOR_18BIT_LOOSE;
        break;
    case MIPI_DSI_FMT_RGB666_PACKED:
        color = DSI_DPI_COLOR_18BIT_PACKED;
        break;
    case MIPI_DSI_FMT_RGB888:
    default:
        color = DSI_DPI_COLOR_24BIT;
        break;
    }

    if (!(dsi->mode.flags & DISPLAY_TIMING_F_PHSYNC))
    {
        pol |= DSI_HSYNC_ACTIVE_LOW;
    }
    if (!(dsi->mode.flags & DISPLAY_TIMING_F_PVSYNC))
    {
        pol |= DSI_VSYNC_ACTIVE_LOW;
    }

    dsi_write(dsi, DSI_DPI_VCID, dsi->channel & 0x3);
    dsi_write(dsi, DSI_DPI_COLOR_CODING, color);
    dsi_write(dsi, DSI_DPI_CFG_POL, pol);

    pckhdl = DSI_CRC_RX_EN | DSI_ECC_RX_EN | DSI_BTA_EN;
    if (!(dsi->mode_flags & MIPI_DSI_MODE_NO_EOT_PACKET))
    {
        pckhdl |= DSI_EOTP_RX_EN | DSI_EOTP_TX_EN;
    }
    dsi_write(dsi, DSI_PCKHDL_CFG, pckhdl);

    dsi_write(dsi, DSI_VID_PKT_SIZE, dsi->mode.hactive);
    dsi_write(dsi, DSI_VID_NUM_CHUNKS, 0);
    dsi_write(dsi, DSI_VID_NULL_SIZE, 0);
    dsi_write(dsi, DSI_VID_HSA_TIME, rk_dsi_lbcc(dsi, dsi->mode.hsync_len));
    dsi_write(dsi, DSI_VID_HBP_TIME, rk_dsi_lbcc(dsi, dsi->mode.hback_porch));
    dsi_write(dsi, DSI_VID_HLINE_TIME, rk_dsi_lbcc(dsi, dsi->mode.htotal));
    dsi_write(dsi, DSI_VID_VSA_LINES, dsi->mode.vsync_len);
    dsi_write(dsi, DSI_VID_VBP_LINES, dsi->mode.vback_porch);
    dsi_write(dsi, DSI_VID_VFP_LINES, dsi->mode.vfront_porch);
    dsi_write(dsi, DSI_VID_VACTIVE_LINES, dsi->mode.vactive);

    dsi_write(dsi, DSI_TO_CNT_CFG, (1000 << 16) | 1000);
    dsi_write(dsi, DSI_BTA_TO_CNT, 0xd00);
    dsi_write(dsi, DSI_MODE_CFG, DSI_CMD_MODE);

    dsi_write(dsi, DSI_PHY_RSTZ, 0);
    dsi_write(dsi, DSI_PHY_TST_CTRL0, 0);
    dsi_write(dsi, DSI_PHY_TST_CTRL0, 1);
    dsi_write(dsi, DSI_PHY_TST_CTRL0, 0);

    hwver = dsi_read(dsi, DSI_VERSION) & 0xffffff00;
    if (hwver >= 0x31333100)
    {
        dsi_write(dsi, DSI_PHY_TMR_CFG, (0x14 << 16) | 0x10);
        dsi_write(dsi, DSI_PHY_TMR_RD_CFG, 10000);
    }
    else
    {
        dsi_write(dsi, DSI_PHY_TMR_CFG, (0x14 << 24) | (0x10 << 16) | 10000);
    }
    dsi_write(dsi, DSI_PHY_TMR_LPCLK_CFG, (0x40 << 16) | 0x40);
    dsi_write(dsi, DSI_PHY_IF_CFG, (0x20 << 8) | ((dsi->lanes - 1) & 0x3));

    (void)dsi_read(dsi, DSI_INT_ST0);
    (void)dsi_read(dsi, DSI_INT_ST1);
    dsi_write(dsi, DSI_INT_MSK0, 0);
    dsi_write(dsi, DSI_INT_MSK1, 0);
}

static rt_err_t rk_dsi_prepare(void *priv, rt_uint32_t vp_id,
        const struct display_timing *tim)
{
    struct rk_dsi *dsi = priv;
    rt_err_t err;

    RT_UNUSED(vp_id);

    if (!dsi || !tim || !tim->hactive || !tim->vactive)
    {
        return -RT_EINVAL;
    }

    if (dsi->prepared)
    {
        return RT_EOK;
    }

    dsi->mode = *tim;

    if ((err = rt_clk_array_prepare_enable(dsi->clks)))
    {
        return err;
    }

    if (!rt_is_err_or_null(dsi->apb_rst))
    {
        rt_reset_control_assert(dsi->apb_rst);
        rt_hw_us_delay(10);
        rt_reset_control_deassert(dsi->apb_rst);
    }

    if ((err = rk_dsi_configure_phy(dsi)))
    {
        goto _fail_clk;
    }

    if (dsi->grf)
    {
        rt_syscon_write(dsi->grf, dsi->grf_lane_reg,
                HIWORD_UPDATE(0, RK3568_DSI_LANE_CFG_MASK));
    }

    rk_dsi_host_config(dsi);

    if ((err = rt_phye_init(dsi->dphy)))
    {
        goto _fail_clk;
    }
    if ((err = rt_phye_power_on(dsi->dphy)))
    {
        rt_phye_exit(dsi->dphy);
        goto _fail_clk;
    }
    dsi->phy_on = RT_TRUE;

    dsi_write(dsi, DSI_PHY_RSTZ, DSI_PHY_ENABLE);

    if ((err = rk_dsi_wait(dsi, DSI_PHY_STATUS, DSI_PHY_LOCK,
            DSI_PHY_LOCK, DSI_PHY_TIMEOUT_US)))
    {
        LOG_W("PHY lock timeout, status=0x%08x", dsi_read(dsi, DSI_PHY_STATUS));
        goto _fail_phy;
    }
    if ((err = rk_dsi_wait(dsi, DSI_PHY_STATUS, DSI_PHY_STOP_CLK,
            DSI_PHY_STOP_CLK, DSI_PHY_TIMEOUT_US)))
    {
        LOG_W("PHY clock lane stop timeout, status=0x%08x", dsi_read(dsi, DSI_PHY_STATUS));
        goto _fail_phy;
    }

    /* Synopsys requires two generated frame periods before panel prepare. */
    if (tim->pixelclock && tim->htotal && tim->vtotal)
    {
        rt_uint64_t frame_pixels = (rt_uint64_t)tim->htotal * tim->vtotal;
        rt_uint32_t refresh = (rt_uint32_t)(tim->pixelclock / frame_pixels);

        if (!refresh)
        {
            refresh = 60;
        }
        rt_thread_mdelay(RT_DIV_ROUND_UP(1000, refresh) * 2);
    }

    rk_dsi_set_mode(dsi, RT_FALSE);
    dsi->prepared = RT_TRUE;

    LOG_D("prepared %ux%u, %u lane(s) at %u Mbps",
            tim->hactive, tim->vactive, dsi->lanes, dsi->lane_mbps);

    return RT_EOK;

_fail_phy:
    rt_phye_power_off(dsi->dphy);
    rt_phye_exit(dsi->dphy);
    dsi->phy_on = RT_FALSE;
_fail_clk:
    rt_clk_array_disable_unprepare(dsi->clks);
    return err;
}

static rt_err_t rk_dsi_enable(void *priv, rt_bool_t enable)
{
    struct rk_dsi *dsi = priv;
    rt_uint32_t val;

    if (!dsi || (enable && !dsi->prepared))
    {
        return -RT_EINVAL;
    }

    if (enable)
    {
        val = DSI_PHY_TXREQUESTCLKHS;
        if (dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS)
        {
            val |= DSI_AUTO_CLKLANE_CTRL;
        }
        dsi_write(dsi, DSI_LPCLK_CTRL, val);
        dsi_write(dsi, DSI_EDPI_CMD_SIZE, dsi->mode.hactive);
        rk_dsi_set_mode(dsi, !!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO));

#if DBG_LVL >= DBG_LOG
        LOG_D("enabled video stream: phy=0x%08x cmd=0x%08x int0=0x%08x int1=0x%08x",
                dsi_read(dsi, DSI_PHY_STATUS),
                dsi_read(dsi, DSI_CMD_PKT_STATUS),
                dsi_read(dsi, DSI_INT_ST0),
                dsi_read(dsi, DSI_INT_ST1));
#endif
    }
    else
    {
        dsi_write(dsi, DSI_LPCLK_CTRL, 0);
        dsi_write(dsi, DSI_PWR_UP, 0);

        if (dsi->phy_on)
        {
            rt_phye_power_off(dsi->dphy);
            rt_phye_exit(dsi->dphy);
            dsi->phy_on = RT_FALSE;
        }

        rt_clk_array_disable_unprepare(dsi->clks);
        dsi->prepared = RT_FALSE;
    }

    return RT_EOK;
}

static rt_err_t rk_dsi_disable(void *priv)
{
    return rk_dsi_enable(priv, RT_FALSE);
}

static const struct rockchip_connector_ops rk_dsi_connector_ops =
{
    .prepare = rk_dsi_prepare,
    .transfer = rk_dsi_transfer,
    .enable = rk_dsi_enable,
    .disable = rk_dsi_disable,
};

static struct rt_ofw_node *rk_dsi_find_panel(struct rt_ofw_node *np)
{
    struct rt_ofw_node *child;

    rt_ofw_foreach_available_child_node(np, child)
    {
        if (rt_ofw_node_is_compatible(child, "simple-panel-dsi") ||
                rt_ofw_node_is_compatible(child, "rockchip,panel-simple"))
        {
            return child;
        }
    }

    return RT_NULL;
}

static rt_err_t rk_dsi_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct rk_dsi *dsi = rt_calloc(1, sizeof(*dsi));
    rt_uint64_t addr;
    rt_err_t err;

    if (!dsi)
    {
        return -RT_ENOMEM;
    }

    dsi->dev = dev;
    dsi->regs = rt_ofw_iomap(np, 0);

    if (!dsi->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    dsi->clks = rt_clk_get_array(dev);
    if (rt_is_err(dsi->clks))
    {
        err = rt_ptr_err(dsi->clks);
        goto _fail_unmap;
    }

    dsi->apb_rst = rt_reset_control_get_by_name(dev, "apb");
    dsi->grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf");
    dsi->dphy = rt_phye_get_by_name(dev, "dphy");

    if (rt_is_err_or_null(dsi->dphy))
    {
        LOG_D("%s: waiting for DPHY provider", rt_ofw_node_full_name(np));
        err = -RT_EBUSY;
        goto _fail_resources;
    }

    dsi->lanes = 4;
    dsi->channel = 0;
    dsi->format = MIPI_DSI_FMT_RGB888;
    dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
            MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_NO_EOT_PACKET;

    dsi->panel_np = rk_dsi_find_panel(np);
    if (dsi->panel_np)
    {
        rt_ofw_prop_read_u32(dsi->panel_np, "dsi,lanes", &dsi->lanes);
        rt_ofw_prop_read_u32(dsi->panel_np, "dsi,format", &dsi->format);
        rt_ofw_prop_read_u32(dsi->panel_np, "dsi,flags", &dsi->mode_flags);
        rt_ofw_prop_read_u32(dsi->panel_np, "reg", &dsi->channel);

        err = rt_platform_ofw_request(dsi->panel_np);
        if (err || !dsi->panel_np->dev || !dsi->panel_np->dev->drv)
        {
            LOG_E("%s: panel driver probe failed", rt_ofw_node_full_name(np));
            err = err ? err : -RT_ENOSYS;
            goto _fail_dphy;
        }
    }

    if (!dsi->lanes || dsi->lanes > 4)
    {
        err = -RT_EINVAL;
        goto _fail_dphy;
    }

    if (!rt_ofw_get_address(np, 0, &addr, RT_NULL) && addr == 0xfe070000ULL)
    {
        dsi->id = 1;
        dsi->grf_lane_reg = RK3568_GRF_VO_CON3;
    }
    else
    {
        dsi->id = 0;
        dsi->grf_lane_reg = RK3568_GRF_VO_CON2;
    }

    if ((err = rockchip_display_register_connector(np, &rk_dsi_connector_ops, dsi)))
    {
        goto _fail_dphy;
    }

    dev->user_data = dsi;
    rk_dsi_instances[dsi->id] = dsi;

    LOG_D("DSI %s: panel=%s lanes=%u format=%u flags=0x%x",
            rt_ofw_node_full_name(np),
            dsi->panel_np ? rt_ofw_node_full_name(dsi->panel_np) : "<none>",
            dsi->lanes, dsi->format, dsi->mode_flags);

    return RT_EOK;

_fail_dphy:
    if (dsi->panel_np)
    {
        rt_ofw_node_put(dsi->panel_np);
    }
    rt_phye_put(dsi->dphy);
_fail_resources:
    if (!rt_is_err_or_null(dsi->apb_rst))
    {
        rt_reset_control_put(dsi->apb_rst);
    }
    rt_clk_array_put(dsi->clks);
_fail_unmap:
    rt_iounmap(dsi->regs);
_fail:
    rt_free(dsi);
    return err;
}

static int rk_dsi_retry_deferred_probe(void)
{
    rt_err_t err;
    struct rt_ofw_node *np;

    rt_ofw_foreach_node_by_compatible(np, "rockchip,rk3568-mipi-dsi")
    {
        if (!rt_ofw_node_is_available(np) || (np->dev && np->dev->drv))
        {
            continue;
        }

        err = rt_platform_ofw_request(np);
        if (err || !np->dev || !np->dev->drv)
        {
            LOG_E("%s: deferred probe failed: %s",
                    rt_ofw_node_full_name(np), rt_strerror(err ? err : -RT_ENOSYS));
        }
    }

    return 0;
}
INIT_COMPONENT_EXPORT(rk_dsi_retry_deferred_probe);

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <stdlib.h>

static int rk_dsi_vpg(int argc, char **argv)
{
    struct rk_dsi *dsi;
    rt_uint32_t id, val;

    if (argc != 3 || argv[1][1] || (argv[1][0] != '0' && argv[1][0] != '1'))
    {
        rt_kprintf("Usage: dsi_vpg <0|1> <off|color|ber>\n");
        return -RT_EINVAL;
    }

    id = argv[1][0] - '0';
    dsi = rk_dsi_instances[id];
    if (!dsi || !dsi->prepared)
    {
        rt_kprintf("dsi%u is not prepared\n", id);
        return -RT_EBUSY;
    }

    val = dsi_read(dsi, DSI_VID_MODE_CFG);
    val &= ~(DSI_VID_MODE_VPG_ENABLE | DSI_VID_MODE_VPG_BER |
            DSI_VID_MODE_VPG_HORIZONTAL);

    if (!rt_strcmp(argv[2], "color"))
    {
        val |= DSI_VID_MODE_VPG_ENABLE;
    }
    else if (!rt_strcmp(argv[2], "ber"))
    {
        val |= DSI_VID_MODE_VPG_ENABLE | DSI_VID_MODE_VPG_BER;
    }
    else if (rt_strcmp(argv[2], "off"))
    {
        rt_kprintf("Usage: dsi_vpg <0|1> <off|color|ber>\n");
        return -RT_EINVAL;
    }

    dsi_write(dsi, DSI_VID_MODE_CFG, val);
    rt_kprintf("dsi%u: VID_MODE_CFG=0x%08x PHY=0x%08x INT0=0x%08x INT1=0x%08x\n",
            id, val, dsi_read(dsi, DSI_PHY_STATUS),
            dsi_read(dsi, DSI_INT_ST0), dsi_read(dsi, DSI_INT_ST1));

    return RT_EOK;
}
MSH_CMD_EXPORT_ALIAS(rk_dsi_vpg, dsi_vpg,
        DSI internal pattern: dsi_vpg <0|1> <off|color|ber>);

static int rk_dsi_dcs_read(int argc, char **argv)
{
    struct rk_dsi *dsi;
    rt_uint8_t data[16];
    unsigned long id, command, len = 1;
    char *end;
    rt_size_t i;
    rt_err_t err;

    if (argc < 3 || argc > 4)
    {
        goto _usage;
    }

    id = strtoul(argv[1], &end, 0);
    if (*end || id > 1)
    {
        goto _usage;
    }

    command = strtoul(argv[2], &end, 0);
    if (*end || command > 0xff)
    {
        goto _usage;
    }

    if (argc == 4)
    {
        len = strtoul(argv[3], &end, 0);
        if (*end || !len || len > sizeof(data))
        {
            goto _usage;
        }
    }

    dsi = rk_dsi_instances[id];
    if (!dsi || !dsi->prepared)
    {
        rt_kprintf("dsi%lu is not prepared\n", id);
        return -RT_EBUSY;
    }

    rt_memset(data, 0, sizeof(data));
    err = rk_dsi_read_packet(dsi, command, data, len);
    rt_kprintf("dsi%lu DCS[0x%02lx]:", id, command);
    if (err)
    {
        rt_kprintf(" read failed: %s, status=0x%08x int0=0x%08x int1=0x%08x\n",
                rt_strerror(err), dsi_read(dsi, DSI_CMD_PKT_STATUS),
                dsi_read(dsi, DSI_INT_ST0), dsi_read(dsi, DSI_INT_ST1));
        return err;
    }

    for (i = 0; i < len; ++i)
    {
        rt_kprintf(" %02x", data[i]);
    }
    rt_kprintf("\n");

    return RT_EOK;

_usage:
    rt_kprintf("Usage: dsi_dcs_read <0|1> <command> [1..16]\n");
    return -RT_EINVAL;
}
MSH_CMD_EXPORT_ALIAS(rk_dsi_dcs_read, dsi_dcs_read,
        Read panel DCS register: dsi_dcs_read <0|1> <command> [length]);
#endif

static const struct rt_ofw_node_id rk_dsi_ids[] =
{
    { .compatible = "rockchip,rk3568-mipi-dsi" },
    { /* sentinel */ }
};

static struct rt_platform_driver rk_dsi_driver =
{
    .name = "dw-mipi-dsi-rockchip",
    .ids = rk_dsi_ids,
    .probe = rk_dsi_probe,
};
RT_PLATFORM_DRIVER_EXPORT(rk_dsi_driver);
