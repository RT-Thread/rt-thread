/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#include <rtdevice.h>
#include <rtthread.h>

#define DBG_TAG "phye.hdptx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define HDPTX_TMDS_MAX_RATE            594000000ULL

#define GRF_HDPTX_CON0                 0x0000
#define GRF_HDPTX_STATUS               0x0080
#define HDPTX_I_PLL_EN                 RT_BIT(7)
#define HDPTX_I_BIAS_EN                RT_BIT(6)
#define HDPTX_I_BGR_EN                 RT_BIT(5)
#define HDPTX_O_PLL_LOCK_DONE          RT_BIT(3)
#define HDPTX_O_PHY_CLK_RDY            RT_BIT(2)
#define HDPTX_O_PHY_RDY                RT_BIT(1)

#define LNTOP_REG0200                  0x0800
#define LNTOP_REG0207                  0x081c
#define LANE0_BASE                     0x0c00

struct hdptx_regval
{
    rt_uint16_t reg;
    rt_uint8_t val;
};

struct rk_hdptx
{
    struct rt_phye parent;
    void *regs;
    struct rt_syscon *grf;
    struct rt_clk *ref_clk;
    struct rt_clk *apb_clk;
    struct rt_reset_control *phy_rst;
    struct rt_reset_control *apb_rst;
    struct rt_reset_control *init_rst;
    struct rt_reset_control *cmn_rst;
    struct rt_reset_control *lane_rst;
    struct rt_reset_control *ropll_rst;
    rt_uint64_t tmds_clock;
    struct rt_clk_node clk_np;
    struct rt_clk_cell pixel_clk;
    struct rt_clk_cell *clk_cells[1];
    struct rt_device clk_port_dev;
    rt_uint32_t pixel_users;
    rt_bool_t pll_configured;
    rt_uint8_t id;
};

struct hdptx_ropll_cfg
{
    rt_uint8_t pms_mdiv;
    rt_uint8_t pms_mdiv_afc;
    rt_uint8_t pms_pdiv;
    rt_uint8_t pms_refdiv;
    rt_uint8_t pms_sdiv;
    rt_uint8_t sdm_en;
    rt_uint8_t sdm_deno;
    rt_uint8_t sdm_num_sign;
    rt_uint8_t sdm_num;
    rt_uint8_t sdc_n;
    rt_uint8_t sdc_num;
    rt_uint8_t sdc_deno;
};

struct hdptx_ropll_rate_cfg
{
    rt_uint64_t rate;
    struct hdptx_ropll_cfg cfg;
};

/*
 * The HDPTX fractional loop has rate-specific settings.  A PLL lock alone
 * does not validate the resulting TMDS bit clock, so keep the Linux-verified
 * 74.25 MHz entry used by the default 720p mode instead of deriving it.
 */
static const struct hdptx_ropll_rate_cfg hdptx_ropll_rate_cfgs[] =
{
    {
        74250000ULL,
        { 124, 124, 1, 1, 7, 1, 62, 1, 16, 5, 0, 1 },
    },
};

#define phye_to_hdptx(phye) rt_container_of(phye, struct rk_hdptx, parent)

static const struct hdptx_regval hdptx_ropll_common[] =
{
    { 0x0020, 0x00 }, { 0x0024, 0x0c }, { 0x0028, 0x83 },
    { 0x002c, 0x06 }, { 0x0030, 0x20 }, { 0x0034, 0xb8 },
    { 0x0038, 0x0f }, { 0x003c, 0x0f }, { 0x0040, 0x04 },
    { 0x0044, 0x01 }, { 0x0048, 0x26 }, { 0x004c, 0x22 },
    { 0x0050, 0x24 }, { 0x0054, 0x77 }, { 0x0058, 0x08 },
    { 0x005c, 0x20 }, { 0x0060, 0x04 }, { 0x0064, 0x48 },
    { 0x0068, 0x01 }, { 0x006c, 0x00 }, { 0x0070, 0x01 },
    { 0x0074, 0x64 }, { 0x0078, 0x14 }, { 0x007c, 0x00 },
    { 0x0080, 0x00 }, { 0x0084, 0x00 }, { 0x0088, 0x11 },
    { 0x008c, 0x00 }, { 0x0090, 0x00 }, { 0x0094, 0x53 },
    { 0x0098, 0x00 }, { 0x009c, 0x00 }, { 0x00a0, 0x01 },
    { 0x00a4, 0x01 }, { 0x00a8, 0x00 }, { 0x00ac, 0x00 },
    { 0x00b0, 0x00 }, { 0x00b4, 0x00 }, { 0x00b8, 0x04 },
    { 0x00bc, 0x00 }, { 0x00c0, 0x20 }, { 0x00c4, 0x30 },
    { 0x00c8, 0x0b }, { 0x00cc, 0x23 }, { 0x00d0, 0x00 },
    { 0x00d4, 0x00 }, { 0x00e0, 0x00 }, { 0x00e4, 0x00 },
    { 0x00e8, 0x00 }, { 0x00ec, 0x00 }, { 0x00f0, 0x80 },
    { 0x00f4, 0x40 }, { 0x00f8, 0x0c }, { 0x00fc, 0x83 },
    { 0x0100, 0x06 }, { 0x0104, 0x20 }, { 0x0108, 0x78 },
    { 0x010c, 0x00 }, { 0x0110, 0x46 }, { 0x0114, 0x24 },
    { 0x0118, 0xdd }, { 0x011c, 0x00 }, { 0x0120, 0x11 },
    { 0x0124, 0xfa }, { 0x0128, 0x08 }, { 0x012c, 0x00 },
    { 0x0130, 0x01 }, { 0x0134, 0x64 }, { 0x0138, 0x34 },
    { 0x013c, 0x00 }, { 0x0140, 0x00 },
    { 0x0170, 0x25 }, { 0x0174, 0x0c }, { 0x0178, 0x4f },
    { 0x017c, 0x01 }, { 0x01ac, 0x04 }, { 0x01cc, 0x30 },
    { 0x01d0, 0x04 }, { 0x01d4, 0x20 }, { 0x01d8, 0x30 },
    { 0x01dc, 0x08 }, { 0x01e0, 0x0c }, { 0x01e4, 0x00 },
    { 0x01ec, 0x00 }, { 0x01f0, 0x00 }, { 0x01f4, 0x00 },
    { 0x01f8, 0x00 }, { 0x01fc, 0x00 }, { 0x0200, 0x00 },
    { 0x0204, 0x01 }, { 0x0208, 0x04 }, { 0x020c, 0x24 },
    { 0x0210, 0x20 }, { 0x0214, 0x03 }, { 0x021c, 0x04 },
    { 0x0224, 0x00 }, { 0x0228, 0x55 }, { 0x022c, 0x25 },
    { 0x0230, 0x2c }, { 0x0234, 0x22 }, { 0x0238, 0x14 },
    { 0x023c, 0x20 }, { 0x0240, 0x00 }, { 0x0244, 0x00 },
    { 0x0248, 0x00 }, { 0x024c, 0x00 }, { 0x0254, 0x00 },
    { 0x025c, 0x02 }, { 0x0264, 0x04 }, { 0x0268, 0x11 },
    { 0x026c, 0x00 },
};

rt_inline void hdptx_write(struct rk_hdptx *hdptx, rt_uint16_t reg, rt_uint8_t val)
{
    HWREG32((rt_uint8_t *)hdptx->regs + reg) = val;
}

static void hdptx_update_bits(struct rk_hdptx *hdptx, rt_uint16_t reg,
        rt_uint8_t mask, rt_uint8_t val)
{
    rt_uint8_t old;

    old = HWREG32((rt_uint8_t *)hdptx->regs + reg);

    hdptx_write(hdptx, reg, (old & ~mask) | (val & mask));
}

static void hdptx_grf_write(struct rk_hdptx *hdptx, rt_uint32_t reg, rt_uint32_t val)
{
    rt_syscon_write(hdptx->grf, reg, val);
}

static rt_uint32_t hdptx_grf_read(struct rk_hdptx *hdptx, rt_uint32_t reg)
{
    rt_uint32_t val;

    val = 0;
    rt_syscon_read(hdptx->grf, reg, &val);

    return val;
}

static void hdptx_rational_best(rt_uint64_t num, rt_uint64_t den,
        rt_uint32_t max_num, rt_uint32_t max_den, rt_uint8_t *best_num,
        rt_uint8_t *best_den)
{
    rt_uint64_t best_err = ~(rt_uint64_t)0;
    rt_uint32_t n;
    rt_uint32_t d;

    *best_num = 0;
    *best_den = 1;

    for (d = 1; d <= max_den; ++d)
    {
        rt_uint64_t err;

        n = (rt_uint32_t)((num * d + den / 2) / den);
        if (n > max_num)
        {
            continue;
        }

        err = num * d > den * n ? num * d - den * n : den * n - num * d;
        if (err * *best_den < best_err * d)
        {
            best_err = err;
            *best_num = n;
            *best_den = d;
        }
    }
}

static rt_bool_t hdptx_ropll_calc(rt_uint64_t rate, struct hdptx_ropll_cfg *cfg)
{
    const rt_uint64_t fout = rate / 200;
    const rt_uint32_t fref = 24000;
    rt_uint32_t sdiv;
    rt_uint32_t mdiv = 0;
    rt_uint32_t sdc = 0;
    rt_uint64_t fvco = 0;
    rt_uint8_t k = 0;
    rt_uint8_t lc = 1;
    rt_uint8_t k_sub = 0;
    rt_uint8_t lc_sub = 1;

    if (!fout)
    {
        return RT_FALSE;
    }

    for (sdiv = 16; sdiv; --sdiv)
    {
        if ((sdiv & 1) && sdiv != 1)
        {
            continue;
        }

        fvco = fout * sdiv;
        if (fvco < 2000000 || fvco > 4000000)
        {
            continue;
        }

        mdiv = (rt_uint32_t)((fvco + fref - 1) / fref);
        if (mdiv < 20 || mdiv > 255)
        {
            continue;
        }

        if (fref * mdiv != fvco)
        {
            for (sdc = 264000; sdc <= 750000; sdc += fref)
            {
                if ((rt_uint64_t)sdc * 8 > (rt_uint64_t)fref * mdiv)
                {
                    break;
                }
            }
            if (sdc > 750000)
            {
                continue;
            }

            hdptx_rational_best((rt_uint64_t)fref * mdiv - fvco, sdc / 16,
                    0x7f, 0xff, &k, &lc);
            hdptx_rational_best((rt_uint64_t)sdc * 8 - (rt_uint64_t)fref * mdiv,
                    sdc, 0x7f, 0xff, &k_sub, &lc_sub);
        }
        break;
    }

    if (!sdiv)
    {
        return RT_FALSE;
    }

    cfg->pms_mdiv = mdiv;
    cfg->pms_mdiv_afc = mdiv;
    cfg->pms_pdiv = 1;
    cfg->pms_refdiv = 1;
    cfg->pms_sdiv = sdiv - 1;
    cfg->sdm_en = k ? 1 : 0;
    cfg->sdm_deno = lc;
    cfg->sdm_num_sign = cfg->sdm_en;
    cfg->sdm_num = k;
    cfg->sdc_n = 5;
    cfg->sdc_num = k_sub;
    cfg->sdc_deno = lc_sub;

    return RT_TRUE;
}

static rt_bool_t hdptx_ropll_get_cfg(rt_uint64_t rate, struct hdptx_ropll_cfg *cfg)
{
    rt_size_t i;

    for (i = 0; i < RT_ARRAY_SIZE(hdptx_ropll_rate_cfgs); ++i)
    {
        if (hdptx_ropll_rate_cfgs[i].rate == rate)
        {
            *cfg = hdptx_ropll_rate_cfgs[i].cfg;
            return RT_TRUE;
        }
    }

    return hdptx_ropll_calc(rate, cfg);
}

static void hdptx_reset_assert(struct rt_reset_control *rst)
{
    if (!rt_is_err_or_null(rst))
    {
        rt_reset_control_assert(rst);
    }
}

static void hdptx_reset_deassert(struct rt_reset_control *rst)
{
    if (!rt_is_err_or_null(rst))
    {
        rt_reset_control_deassert(rst);
    }
}

static void hdptx_pre_power_up(struct rk_hdptx *hdptx)
{
    hdptx_reset_assert(hdptx->apb_rst);
    rt_hw_us_delay(20);
    hdptx_reset_deassert(hdptx->apb_rst);

    hdptx_reset_assert(hdptx->lane_rst);
    hdptx_reset_assert(hdptx->cmn_rst);
    hdptx_reset_assert(hdptx->init_rst);
    hdptx_grf_write(hdptx, GRF_HDPTX_CON0,
            (HDPTX_I_PLL_EN | HDPTX_I_BIAS_EN | HDPTX_I_BGR_EN) << 16);
}

static rt_err_t hdptx_enable_pll(struct rk_hdptx *hdptx)
{
    rt_uint32_t val;
    int i;

    hdptx_grf_write(hdptx, GRF_HDPTX_CON0,
            ((HDPTX_I_BIAS_EN | HDPTX_I_BGR_EN) << 16) |
            HDPTX_I_BIAS_EN | HDPTX_I_BGR_EN);
    rt_hw_us_delay(10);
    hdptx_reset_deassert(hdptx->init_rst);
    rt_hw_us_delay(10);
    hdptx_grf_write(hdptx, GRF_HDPTX_CON0, (HDPTX_I_PLL_EN << 16) | HDPTX_I_PLL_EN);
    rt_hw_us_delay(10);
    hdptx_reset_deassert(hdptx->cmn_rst);

    for (i = 0; i < 20; ++i)
    {
        val = hdptx_grf_read(hdptx, GRF_HDPTX_STATUS);
        if (val & HDPTX_O_PHY_CLK_RDY)
        {
            return RT_EOK;
        }
        rt_hw_us_delay(20);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t hdptx_program_ropll(struct rk_hdptx *hdptx, rt_uint64_t rate)
{
    struct hdptx_ropll_cfg cfg;
    rt_size_t i;
    rt_err_t err;

    if (rate > HDPTX_TMDS_MAX_RATE || !hdptx_ropll_get_cfg(rate, &cfg))
    {
        return -RT_EINVAL;
    }

    hdptx_pre_power_up(hdptx);

    /* The TMDS ROPLL has its own reset line in the RK3588 binding. */
    hdptx_reset_assert(hdptx->ropll_rst);
    rt_hw_us_delay(20);
    hdptx_reset_deassert(hdptx->ropll_rst);
    hdptx_grf_write(hdptx, GRF_HDPTX_CON0, RT_BIT(11) << 16);

    for (i = 0; i < RT_ARRAY_SIZE(hdptx_ropll_common); ++i)
    {
        hdptx_write(hdptx, hdptx_ropll_common[i].reg, hdptx_ropll_common[i].val);
    }

    hdptx_write(hdptx, 0x0144, cfg.pms_mdiv);
    hdptx_write(hdptx, 0x0154, cfg.pms_mdiv_afc);
    hdptx_write(hdptx, 0x0164, (cfg.pms_pdiv << 4) | cfg.pms_refdiv);
    hdptx_write(hdptx, 0x0168, cfg.pms_sdiv << 4);
    hdptx_write(hdptx, 0x0178, cfg.sdm_en ? 0x4f : 0x40);
    hdptx_write(hdptx, 0x0180, cfg.sdm_deno);
    /* Linux only updates ROPLL_SDM_NUM_SIGN_RBR (bit 3).  The reset
     * defaults in bits [2:0] are required by the TMDS serial datapath. */
    hdptx_update_bits(hdptx, 0x0190, RT_BIT(3),
            cfg.sdm_num_sign ? RT_BIT(3) : 0);
    hdptx_write(hdptx, 0x0194, cfg.sdm_num);
    hdptx_write(hdptx, 0x01a4, cfg.sdc_n);
    hdptx_write(hdptx, 0x01b0, cfg.sdc_num);
    hdptx_write(hdptx, 0x01c0, cfg.sdc_deno);
    hdptx_write(hdptx, 0x0218, (cfg.pms_sdiv << 4) | RT_BIT(0));

    err = hdptx_enable_pll(hdptx);
    if (!err)
    {
        hdptx->tmds_clock = rate;
        hdptx->pll_configured = RT_TRUE;
    }

    return err;
}

static rt_err_t hdptx_enable_lanes(struct rk_hdptx *hdptx)
{
    rt_uint32_t val;
    int i;

    hdptx_reset_deassert(hdptx->lane_rst);
    hdptx_grf_write(hdptx, GRF_HDPTX_CON0,
            ((HDPTX_I_BIAS_EN | HDPTX_I_BGR_EN) << 16) |
            HDPTX_I_BIAS_EN | HDPTX_I_BGR_EN);
    hdptx_write(hdptx, LNTOP_REG0207, 0x0f);

    for (i = 0; i < 50; ++i)
    {
        val = hdptx_grf_read(hdptx, GRF_HDPTX_STATUS);
        if ((val & (HDPTX_O_PHY_RDY | HDPTX_O_PLL_LOCK_DONE)) ==
                (HDPTX_O_PHY_RDY | HDPTX_O_PLL_LOCK_DONE))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(100);
    }

    return -RT_ETIMEOUT;
}

static void hdptx_program_lanes(struct rk_hdptx *hdptx)
{
    static const struct hdptx_regval lane_cfg[] =
    {
        { 0x000c, 0x0c }, { 0x001c, 0x20 }, { 0x0028, 0x17 },
        { 0x002c, 0x77 }, { 0x0030, 0x77 }, { 0x0034, 0x77 },
        { 0x0038, 0x38 }, { 0x0040, 0x03 }, { 0x0044, 0x0f },
        { 0x0048, 0x00 }, { 0x0058, 0x02 }, { 0x006c, 0x01 },
        { 0x007c, 0x15 }, { 0x0080, 0xa0 },
    };
    rt_size_t i;
    rt_uint32_t lane;

    hdptx_write(hdptx, 0x0450, 0x00);
    hdptx_write(hdptx, 0x0454, 0x00);
    hdptx_write(hdptx, 0x0458, 0x00);
    hdptx_write(hdptx, 0x045c, 0x00);
    hdptx_write(hdptx, LNTOP_REG0200, 0x06);
    hdptx_write(hdptx, 0x0804, 0x07);
    hdptx_write(hdptx, 0x0808, 0xc1);
    hdptx_write(hdptx, 0x080c, 0xf0);
    hdptx_write(hdptx, 0x0810, 0x7c);
    hdptx_write(hdptx, 0x0814, 0x1f);
    hdptx_write(hdptx, 0x0818, 0x07);

    for (lane = 0; lane < 4; ++lane)
    {
        for (i = 0; i < RT_ARRAY_SIZE(lane_cfg); ++i)
        {
            hdptx_write(hdptx, LANE0_BASE + lane * 0x400 + lane_cfg[i].reg,
                    lane_cfg[i].val);
        }
        hdptx_write(hdptx, LANE0_BASE + lane * 0x400 + 0x0078,
                lane == 3 ? 0x08 : 0x00);
        hdptx_write(hdptx, LANE0_BASE + lane * 0x400 + 0x000c, 0x2f);
        hdptx_write(hdptx, LANE0_BASE + lane * 0x400 + 0x0014, 0x03);
        hdptx_write(hdptx, LANE0_BASE + lane * 0x400 + 0x0018, 0x1c);
    }

    /*
     * Keep the TMDS lane deskew sequence identical to the RK3588 Linux
     * HDPTX driver.  A PLL/lane-ready indication alone is not sufficient:
     * without these final inter-pair values the link can lock while pixel
     * symbols are sampled on the wrong lane boundary.
     */
    hdptx_write(hdptx, LANE0_BASE + 0x0078, 0x02);
    hdptx_write(hdptx, LANE0_BASE + 0x0400 + 0x0078, 0x02);
    hdptx_write(hdptx, LANE0_BASE + 0x0800 + 0x0078, 0x02);
    hdptx_write(hdptx, LANE0_BASE + 0x0c00 + 0x0078, 0x0a);
}

static rt_err_t hdptx_configure(struct rt_phye *phye,
        union rt_phye_configure_opts *opts)
{
    struct rk_hdptx *hdptx = phye_to_hdptx(phye);

    if (phye->mode != RT_PHYE_MODE_HDMI || !opts ||
            !opts->hdmi.pixel_clock ||
            opts->hdmi.pixel_clock != opts->hdmi.tmds_clock ||
            opts->hdmi.tmds_clock > HDPTX_TMDS_MAX_RATE)
    {
        return -RT_EINVAL;
    }

    hdptx->tmds_clock = opts->hdmi.tmds_clock;

    return RT_EOK;
}

static rt_err_t hdptx_init(struct rt_phye *phye)
{
    struct rk_hdptx *hdptx = phye_to_hdptx(phye);
    rt_err_t err;

    err = rt_clk_prepare_enable(hdptx->apb_clk);
    if (err)
    {
        return err;
    }

    err = rt_clk_prepare_enable(hdptx->ref_clk);
    if (err)
    {
        rt_clk_disable_unprepare(hdptx->apb_clk);
    }

    return err;
}

static rt_err_t hdptx_exit(struct rt_phye *phye)
{
    struct rk_hdptx *hdptx = phye_to_hdptx(phye);

    rt_clk_disable_unprepare(hdptx->ref_clk);
    rt_clk_disable_unprepare(hdptx->apb_clk);

    return RT_EOK;
}

static rt_err_t hdptx_power_on(struct rt_phye *phye)
{
    struct rk_hdptx *hdptx = phye_to_hdptx(phye);
    rt_err_t err;

    if (phye->mode != RT_PHYE_MODE_HDMI || !hdptx->tmds_clock)
    {
        return -RT_EINVAL;
    }

    /*
     * Match the Linux split: clk_hdmiphy_pixel* programs the ROPLL before
     * the HDMI PHY is powered, while power_on only configures TMDS lanes.
     * Keep a fallback for consumers which did not enable that clock.
     */
    if (!hdptx->pll_configured)
    {
        err = hdptx_program_ropll(hdptx, hdptx->tmds_clock);
        if (err)
        {
            LOG_E("ROPLL lock timeout");
            return err;
        }
    }

    hdptx_program_lanes(hdptx);
    err = hdptx_enable_lanes(hdptx);
    if (err)
    {
        LOG_E("TMDS lane lock timeout");
        return err;
    }

    LOG_D("TMDS locked at %u Hz", (rt_uint32_t)hdptx->tmds_clock);

    return RT_EOK;
}

static rt_err_t hdptx_power_off(struct rt_phye *phye)
{
    struct rk_hdptx *hdptx = phye_to_hdptx(phye);

    hdptx_write(hdptx, LNTOP_REG0207, 0);
    hdptx_reset_assert(hdptx->lane_rst);
    if (!hdptx->pixel_users)
    {
        hdptx_reset_assert(hdptx->cmn_rst);
        hdptx_reset_assert(hdptx->init_rst);
        hdptx_grf_write(hdptx, GRF_HDPTX_CON0,
                (HDPTX_I_PLL_EN | HDPTX_I_BIAS_EN | HDPTX_I_BGR_EN) << 16);
        hdptx->pll_configured = RT_FALSE;
    }

    return RT_EOK;
}

static rt_ubase_t hdptx_pixel_recalc_rate(struct rt_clk_cell *cell,
        rt_ubase_t parent_rate)
{
    struct rk_hdptx *hdptx = rt_container_of(cell->clk_np,
            struct rk_hdptx, clk_np);

    RT_UNUSED(parent_rate);

    return (rt_ubase_t)hdptx->tmds_clock;
}

static rt_base_t hdptx_pixel_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    struct hdptx_ropll_cfg cfg;

    RT_UNUSED(cell);
    RT_UNUSED(parent_rate);

    return rate <= HDPTX_TMDS_MAX_RATE && hdptx_ropll_get_cfg(rate, &cfg) ?
            (rt_base_t)rate : -RT_EINVAL;
}

static rt_err_t hdptx_pixel_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    struct rk_hdptx *hdptx = rt_container_of(cell->clk_np,
            struct rk_hdptx, clk_np);

    RT_UNUSED(parent_rate);

    if (rate > HDPTX_TMDS_MAX_RATE || !rate)
    {
        return -RT_EINVAL;
    }

    hdptx->tmds_clock = rate;
    if (hdptx->pixel_users)
    {
        return hdptx_program_ropll(hdptx, rate);
    }

    return RT_EOK;
}

static rt_err_t hdptx_pixel_enable(struct rt_clk_cell *cell)
{
    struct rk_hdptx *hdptx = rt_container_of(cell->clk_np,
            struct rk_hdptx, clk_np);
    rt_err_t err;

    if (hdptx->pixel_users++)
    {
        return RT_EOK;
    }

    err = rt_clk_prepare_enable(hdptx->apb_clk);
    if (!err)
    {
        err = rt_clk_prepare_enable(hdptx->ref_clk);
    }
    if (!err)
    {
        err = hdptx_program_ropll(hdptx, hdptx->tmds_clock);
    }
    if (!err)
    {
        return RT_EOK;
    }

    hdptx->pixel_users = 0;
    rt_clk_disable_unprepare(hdptx->ref_clk);
    rt_clk_disable_unprepare(hdptx->apb_clk);

    return err;
}

static void hdptx_pixel_disable(struct rt_clk_cell *cell)
{
    struct rk_hdptx *hdptx = rt_container_of(cell->clk_np,
            struct rk_hdptx, clk_np);

    if (!hdptx->pixel_users || --hdptx->pixel_users)
    {
        return;
    }

    hdptx_reset_assert(hdptx->lane_rst);
    hdptx_reset_assert(hdptx->cmn_rst);
    hdptx_reset_assert(hdptx->init_rst);
    hdptx_grf_write(hdptx, GRF_HDPTX_CON0,
            (HDPTX_I_PLL_EN | HDPTX_I_BIAS_EN | HDPTX_I_BGR_EN) << 16);
    hdptx->pll_configured = RT_FALSE;
    rt_clk_disable_unprepare(hdptx->ref_clk);
    rt_clk_disable_unprepare(hdptx->apb_clk);
}

static const struct rt_clk_ops hdptx_pixel_clk_ops =
{
    .enable = hdptx_pixel_enable,
    .disable = hdptx_pixel_disable,
    .recalc_rate = hdptx_pixel_recalc_rate,
    .round_rate = hdptx_pixel_round_rate,
    .set_rate = hdptx_pixel_set_rate,
};

static rt_err_t hdptx_register_pixel_clk(struct rk_hdptx *hdptx,
        struct rt_ofw_node *port_np)
{
    const char *name;

    name = hdptx->id ? "clk_hdmiphy_pixel1" : "clk_hdmiphy_pixel0";

    hdptx->clk_cells[0] = &hdptx->pixel_clk;
    hdptx->pixel_clk.name = name;
    hdptx->pixel_clk.ops = &hdptx_pixel_clk_ops;
    hdptx->pixel_clk.parents_nr = 1;
    hdptx->pixel_clk.parent = hdptx->ref_clk;
    hdptx->pixel_clk.parent_name = hdptx->ref_clk->cell->name;
    hdptx->pixel_clk.flags = RT_CLK_F_GET_RATE_NOCACHE;

    hdptx->clk_port_dev.ofw_node = port_np;
    hdptx->clk_np.dev = &hdptx->clk_port_dev;
    hdptx->clk_np.cells_nr = RT_ARRAY_SIZE(hdptx->clk_cells);
    hdptx->clk_np.cells = hdptx->clk_cells;
    rt_list_init(&hdptx->clk_np.parent.list);

    return rt_clk_register(&hdptx->clk_np);
}

static rt_err_t hdptx_set_mode(struct rt_phye *phye,
        enum rt_phye_mode mode, int submode)
{
    RT_UNUSED(submode);

    if (mode != RT_PHYE_MODE_HDMI)
    {
        return -RT_ENOSYS;
    }

    phye->mode = mode;

    return RT_EOK;
}

static const struct rt_phye_ops hdptx_ops =
{
    .init = hdptx_init,
    .exit = hdptx_exit,
    .power_on = hdptx_power_on,
    .power_off = hdptx_power_off,
    .set_mode = hdptx_set_mode,
    .configure = hdptx_configure,
};

static rt_err_t hdptx_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rk_hdptx *hdptx;
    struct rt_ofw_node *port_np;
    rt_err_t err;

    hdptx = rt_calloc(1, sizeof(*hdptx));
    if (!hdptx)
    {
        return -RT_ENOMEM;
    }

    hdptx->regs = rt_ofw_iomap(dev->ofw_node, 0);
    hdptx->grf = rt_syscon_find_by_ofw_phandle(dev->ofw_node, "rockchip,grf");
    hdptx->ref_clk = rt_clk_get_by_name(dev, "ref");
    hdptx->apb_clk = rt_clk_get_by_name(dev, "apb");
    if (!hdptx->regs || !hdptx->grf || rt_is_err_or_null(hdptx->ref_clk) ||
            rt_is_err_or_null(hdptx->apb_clk))
    {
        err = -RT_EIO;
        goto _fail;
    }

    hdptx->phy_rst = rt_reset_control_get_by_name(dev, "phy");
    hdptx->apb_rst = rt_reset_control_get_by_name(dev, "apb");
    hdptx->init_rst = rt_reset_control_get_by_name(dev, "init");
    hdptx->cmn_rst = rt_reset_control_get_by_name(dev, "cmn");
    hdptx->lane_rst = rt_reset_control_get_by_name(dev, "lane");
    hdptx->ropll_rst = rt_reset_control_get_by_name(dev, "ropll");
    hdptx->id = rt_ofw_get_alias_id(dev->ofw_node, "hdptxhdmi");
    if (hdptx->id < 0 || hdptx->id > 1)
    {
        LOG_E("%s: invalid HDPTX HDMI alias ID %d",
                rt_ofw_node_full_name(dev->ofw_node), hdptx->id);
        err = -RT_EINVAL;
        goto _fail;
    }
    hdptx->parent.dev = dev;
    hdptx->parent.ops = &hdptx_ops;

    port_np = rt_ofw_get_child_by_tag(dev->ofw_node, "clk-port");
    if (!port_np)
    {
        err = -RT_EIO;
        goto _fail;
    }

    err = hdptx_register_pixel_clk(hdptx, port_np);
    if (err)
    {
        goto _fail;
    }

    err = rt_phye_register(&hdptx->parent);
    if (err)
    {
        goto _fail;
    }

    dev->user_data = hdptx;

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(hdptx->phy_rst))
    {
        rt_reset_control_put(hdptx->phy_rst);
    }
    if (!rt_is_err_or_null(hdptx->apb_rst))
    {
        rt_reset_control_put(hdptx->apb_rst);
    }
    if (!rt_is_err_or_null(hdptx->init_rst))
    {
        rt_reset_control_put(hdptx->init_rst);
    }
    if (!rt_is_err_or_null(hdptx->cmn_rst))
    {
        rt_reset_control_put(hdptx->cmn_rst);
    }
    if (!rt_is_err_or_null(hdptx->lane_rst))
    {
        rt_reset_control_put(hdptx->lane_rst);
    }
    if (!rt_is_err_or_null(hdptx->ropll_rst))
    {
        rt_reset_control_put(hdptx->ropll_rst);
    }
    if (!rt_is_err_or_null(hdptx->ref_clk))
    {
        rt_clk_put(hdptx->ref_clk);
    }
    if (!rt_is_err_or_null(hdptx->apb_clk))
    {
        rt_clk_put(hdptx->apb_clk);
    }
    if (hdptx->regs)
    {
        rt_iounmap(hdptx->regs);
    }
    rt_free(hdptx);

    return err;
}

static const struct rt_ofw_node_id hdptx_ids[] =
{
    { .compatible = "rockchip,rk3588-hdptx-phy-hdmi" },
    { /* sentinel */ }
};

static struct rt_platform_driver hdptx_driver =
{
    .name = "phy-rockchip-hdptx-hdmi",
    .ids = hdptx_ids,
    .probe = hdptx_probe,
};

static int hdptx_driver_register(void)
{
    return rt_platform_driver_register(&hdptx_driver);
}
INIT_SUBSYS_EXPORT(hdptx_driver_register);
