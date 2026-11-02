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
#include "rockchip-hdmi.h"
#include "dw-hdmi-regs.h"

#define DBG_TAG "hdmi.rk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RK3568_GRF_VO_CON1              0x0364
#define RK3568_HDMI_SDAIN_MSK           ((1U << 15) | (1U << (15 + 16)))
#define RK3568_HDMI_SCLIN_MSK           ((1U << 14) | (1U << (14 + 16)))
#define RK_HDMI_PHY_I2C_TIMEOUT_US      20000

struct rk_hdmi_phy_config
{
    rt_uint32_t mpixelclock;
    rt_uint16_t sym_ctr;
    rt_uint16_t term;
    rt_uint16_t vlev_ctr;
};

struct rk_hdmi_mpll_config
{
    rt_uint32_t mpixelclock;
    rt_uint16_t cpce;
    rt_uint16_t gmp;
    rt_uint16_t curr;
};

struct rk_hdmi_phy_write
{
    rt_uint16_t data;
    rt_uint8_t addr;
};

struct rk_hdmi
{
    void *regs;
    struct rt_clk_array *clks;
    struct rt_syscon *grf;
    rt_uint32_t reg_io_width;
    struct display_timing mode;
    rt_bool_t clks_enabled;
    rt_bool_t prepared;
    rt_bool_t enabled;
    rt_bool_t sink_is_hdmi;
    rt_bool_t audio_configured;
    rt_bool_t audio_enabled;
    rt_uint32_t audio_n;
};

#if DBG_LVL >= DBG_LOG
static rt_ubase_t rk_hdmi_clk_rate(struct rk_hdmi *hdmi, const char *name)
{
    if (!hdmi || !hdmi->clks || !name)
    {
        return 0;
    }

    for (rt_size_t i = 0; i < hdmi->clks->count; i++)
    {
        struct rt_clk *clk = hdmi->clks->clks[i];

        if (!rt_is_err_or_null(clk) && clk->con_id && !rt_strcmp(clk->con_id, name))
        {
            return rt_clk_get_rate(clk);
        }
    }

    return 0;
}
#endif /* DBG_LVL >= DBG_LOG */

static const struct rk_hdmi_phy_config rockchip_phy_config[] =
{
    { 74250000,  0x8009, 0x0004, 0x0272 },
    { 165000000, 0x802b, 0x0004, 0x0209 },
    { 297000000, 0x8039, 0x0005, 0x028d },
    { 594000000, 0x8039, 0x0000, 0x019d },
    { ~0u,       0x0000, 0x0000, 0x0000 },
};

static const struct rk_hdmi_mpll_config rockchip_mpll_cfg[] =
{
    {  30666000, 0x00b3, 0x0000, 0x0000 },
    {  36800000, 0x00b3, 0x0000, 0x0000 },
    {  46000000, 0x00b3, 0x0000, 0x0000 },
    {  61333000, 0x0072, 0x0001, 0x0000 },
    {  73600000, 0x0072, 0x0001, 0x0000 },
    {  92000000, 0x0072, 0x0001, 0x0000 },
    { 122666000, 0x0051, 0x0002, 0x0000 },
    { 147200000, 0x0051, 0x0002, 0x0000 },
    { 184000000, 0x0051, 0x0002, 0x0000 },
    { 226666000, 0x0040, 0x0003, 0x0000 },
    { 272000000, 0x0040, 0x0003, 0x0000 },
    { 340000000, 0x0040, 0x0003, 0x0000 },
    { 600000000, 0x1a40, 0x0003, 0x0000 },
    { ~0u,       0x0051, 0x0003, 0x0000 },
};

static const rt_uint16_t rk_hdmi_csc_coeff_default[3][4] =
{
    { 0x2000, 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0x2000, 0x0000, 0x0000 },
    { 0x0000, 0x0000, 0x2000, 0x0000 },
};

rt_inline void rk_hdmi_write(struct rk_hdmi *hdmi, rt_uint32_t reg, rt_uint8_t val)
{
    if (hdmi->reg_io_width == 1)
    {
        HWREG8((rt_uint8_t *)hdmi->regs + reg) = val;
    }
    else
    {
        HWREG32((rt_uint8_t *)hdmi->regs + (reg << 2)) = val;
    }
}

rt_inline rt_uint8_t rk_hdmi_read(struct rk_hdmi *hdmi, rt_uint32_t reg)
{
    if (hdmi->reg_io_width == 1)
    {
        return HWREG8((rt_uint8_t *)hdmi->regs + reg);
    }

    return (rt_uint8_t)HWREG32((rt_uint8_t *)hdmi->regs + (reg << 2));
}

static void rk_hdmi_mod(struct rk_hdmi *hdmi, rt_uint32_t reg, rt_uint8_t mask, rt_uint8_t data)
{
    rt_uint8_t val = rk_hdmi_read(hdmi, reg) & ~mask;

    val |= data & mask;
    rk_hdmi_write(hdmi, reg, val);
}

static struct rk_hdmi *rk_hdmi_from_np(struct rt_ofw_node *np)
{
    if (!np)
    {
        return RT_NULL;
    }

    return rt_ofw_data(np);
}

static rt_uint32_t rk_hdmi_audio_n(rt_uint32_t samplerate)
{
    switch (samplerate)
    {
    case 32000:
        return 4096;
    case 44100:
        return 6272;
    case 48000:
        return 6144;
    case 88200:
        return 12544;
    case 96000:
        return 12288;
    case 176400:
        return 25088;
    case 192000:
        return 24576;
    default:
        return 0;
    }
}

static void rk_hdmi_audio_set_n(struct rk_hdmi *hdmi, rt_uint32_t n)
{
    /* I2S uses the controller's automatic CTS generator. */
    rk_hdmi_mod(hdmi, HDMI_AUD_CTS3,
            HDMI_AUD_CTS3_N_SHIFT_MASK | HDMI_AUD_CTS3_CTS_MANUAL, 0);
    rk_hdmi_write(hdmi, HDMI_AUD_CTS2, 0);
    rk_hdmi_write(hdmi, HDMI_AUD_CTS1, 0);
    rk_hdmi_write(hdmi, HDMI_AUD_N3, (n >> 16) & 0x0f);
    rk_hdmi_write(hdmi, HDMI_AUD_N2, n >> 8);
    rk_hdmi_write(hdmi, HDMI_AUD_N1, n);
}

rt_err_t rk_hdmi_audio_enable(struct rt_ofw_node *np, rt_bool_t enable)
{
    rt_uint8_t clkdis;
    struct rk_hdmi *hdmi = rk_hdmi_from_np(np);

    if (!hdmi)
    {
        return -RT_ENOSYS;
    }

    if (enable && (!hdmi->enabled || !hdmi->sink_is_hdmi ||
            !hdmi->audio_configured))
    {
        return -RT_EINVAL;
    }

    hdmi->audio_enabled = enable;
    clkdis = rk_hdmi_read(hdmi, HDMI_MC_CLKDIS);

    if (enable)
    {
        rk_hdmi_audio_set_n(hdmi, hdmi->audio_n);
        clkdis &= ~HDMI_MC_CLKDIS_AUDCLK_DISABLE;
    }
    else
    {
        rk_hdmi_audio_set_n(hdmi, 0);
        clkdis |= HDMI_MC_CLKDIS_AUDCLK_DISABLE;
    }

    rk_hdmi_write(hdmi, HDMI_MC_CLKDIS, clkdis);

    return RT_EOK;
}

rt_err_t rk_hdmi_audio_configure(struct rt_ofw_node *np,
        rt_uint32_t samplerate, rt_uint8_t channels, rt_uint8_t samplebits)
{
    rt_uint8_t conf0, conf1;
    struct rk_hdmi *hdmi = rk_hdmi_from_np(np);
    rt_uint32_t n = rk_hdmi_audio_n(samplerate);

    if (!hdmi)
    {
        return -RT_ENOSYS;
    }

    if (!hdmi->enabled || !hdmi->sink_is_hdmi)
    {
        return -RT_EBUSY;
    }

    if (!n || channels != 2 || (samplebits != 16 && samplebits != 24 && samplebits != 32))
    {
        return -RT_EINVAL;
    }

    rk_hdmi_audio_enable(np, RT_FALSE);

    /* Reset the I2S FIFO before changing its input format. */
    rk_hdmi_write(hdmi, HDMI_AUD_CONF0, HDMI_AUD_CONF0_SW_RESET);
    rk_hdmi_write(hdmi, HDMI_MC_SWRSTZ, (rt_uint8_t)~HDMI_MC_SWRSTZ_I2SSWRST_REQ);

    conf0 = HDMI_AUD_CONF0_I2S_SELECT | HDMI_AUD_CONF0_I2S_EN0;
    conf1 = HDMI_AUD_CONF1_MODE_I2S |
            (samplebits == 16 ? HDMI_AUD_CONF1_WIDTH_16 : HDMI_AUD_CONF1_WIDTH_24);

    rk_hdmi_write(hdmi, HDMI_AUD_INPUTCLKFS, HDMI_AUD_INPUTCLKFS_64FS);
    rk_hdmi_write(hdmi, HDMI_AUD_CONF0, conf0);
    rk_hdmi_write(hdmi, HDMI_AUD_CONF1, conf1);
    rk_hdmi_write(hdmi, HDMI_AUD_CONF2,
            rk_hdmi_read(hdmi, HDMI_DESIGN_ID) >= 0x21 ? HDMI_AUD_CONF2_INSERT_PCUV : 0);

    /* Stereo PCM uses layout 0 and channel allocation 0. */
    rk_hdmi_mod(hdmi, HDMI_FC_AUDSCONF,
            HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_MASK,
            HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT0);
    rk_hdmi_mod(hdmi, HDMI_FC_AUDICONF0,
            HDMI_FC_AUDICONF0_CC_MASK, (channels - 1) << HDMI_FC_AUDICONF0_CC_OFFSET);
    rk_hdmi_write(hdmi, HDMI_FC_AUDICONF1, 0);
    rk_hdmi_write(hdmi, HDMI_FC_AUDICONF2, 0);
    rk_hdmi_write(hdmi, HDMI_FC_AUDICONF3, 0);

    /* IEC60958 consumer PCM: sample frequency and 16-bit word length. */
    rk_hdmi_write(hdmi, HDMI_FC_AUDSCHNLS7,
            samplerate == 48000 ? 0x02 : samplerate == 44100 ? 0x00 : 0x03);
    rk_hdmi_write(hdmi, HDMI_FC_AUDSCHNLS8, samplebits == 16 ? 0x02 : 0x0b);

    hdmi->audio_n = n;
    hdmi->audio_configured = RT_TRUE;
    rk_hdmi_write(hdmi, HDMI_AUD_CONF0, conf0 | HDMI_AUD_CONF0_SW_RESET);
    rk_hdmi_write(hdmi, HDMI_MC_SWRSTZ, (rt_uint8_t)~HDMI_MC_SWRSTZ_I2SSWRST_REQ);

    LOG_D("audio %u Hz, %u ch, %u bit, N=%u",
            samplerate, channels, samplebits, n);

    return RT_EOK;
}

static void rk_hdmi_phy_test_clear(struct rk_hdmi *hdmi, rt_uint8_t enable)
{
    rk_hdmi_mod(hdmi, HDMI_PHY_TST0, HDMI_PHY_TST0_TSTCLR_MASK,
            enable << HDMI_PHY_TST0_TSTCLR_OFFSET);
}

static rt_err_t rk_hdmi_phy_wait_i2c_done(struct rk_hdmi *hdmi,
        rt_uint32_t timeout_us)
{
    rt_uint32_t step_us = 100;
    rt_uint32_t waited = 0;

    while (waited < timeout_us)
    {
        rt_uint8_t val = rk_hdmi_read(hdmi, HDMI_IH_I2CMPHY_STAT0);

        if (val & (HDMI_IH_I2CMPHY_STAT0_DONE |
                HDMI_IH_I2CMPHY_STAT0_ERROR))
        {
            rk_hdmi_write(hdmi, HDMI_IH_I2CMPHY_STAT0, val);

            return (val & HDMI_IH_I2CMPHY_STAT0_ERROR) ?
                    -RT_EIO : RT_EOK;
        }

        rt_hw_us_delay(step_us);
        waited += step_us;
    }

    return -RT_ETIMEOUT;
}

static rt_err_t rk_hdmi_phy_i2c_write(struct rk_hdmi *hdmi,
        rt_uint16_t data, rt_uint8_t addr)
{
    rk_hdmi_write(hdmi, HDMI_IH_I2CMPHY_STAT0, 0xff);
    rk_hdmi_write(hdmi, HDMI_PHY_I2CM_ADDRESS_ADDR, addr);
    rk_hdmi_write(hdmi, HDMI_PHY_I2CM_DATAO_1_ADDR, (rt_uint8_t)(data >> 8));
    rk_hdmi_write(hdmi, HDMI_PHY_I2CM_DATAO_0_ADDR, (rt_uint8_t)data);
    rk_hdmi_write(hdmi, HDMI_PHY_I2CM_OPERATION_ADDR, HDMI_PHY_I2CM_OPERATION_ADDR_WRITE);
    return rk_hdmi_phy_wait_i2c_done(hdmi, RK_HDMI_PHY_I2C_TIMEOUT_US);
}

static void rk_hdmi_phy_enable_svsret(struct rk_hdmi *hdmi, rt_uint8_t enable)
{
    rk_hdmi_mod(hdmi, HDMI_PHY_CONF0, HDMI_PHY_CONF0_SVSRET_MASK,
            enable << HDMI_PHY_CONF0_SVSRET_OFFSET);
}

static void rk_hdmi_phy_gen2_pddq(struct rk_hdmi *hdmi, rt_uint8_t enable)
{
    rk_hdmi_mod(hdmi, HDMI_PHY_CONF0, HDMI_PHY_CONF0_GEN2_PDDQ_MASK,
            enable << HDMI_PHY_CONF0_GEN2_PDDQ_OFFSET);
}

static void rk_hdmi_phy_gen2_txpwron(struct rk_hdmi *hdmi, rt_uint8_t enable)
{
    rk_hdmi_mod(hdmi, HDMI_PHY_CONF0, HDMI_PHY_CONF0_GEN2_TXPWRON_MASK,
            enable << HDMI_PHY_CONF0_GEN2_TXPWRON_OFFSET);
}

static void rk_hdmi_phy_power_off(struct rk_hdmi *hdmi)
{
    rt_uint32_t waited_us = 0;

    rk_hdmi_phy_gen2_txpwron(hdmi, 0);

    while (waited_us < 5000)
    {
        if (!(rk_hdmi_read(hdmi, HDMI_PHY_STAT0) & HDMI_PHY_TX_PHY_LOCK))
        {
            break;
        }

        rt_hw_us_delay(100);
        waited_us += 100;
    }

    rk_hdmi_phy_gen2_pddq(hdmi, 1);
}

static void rk_hdmi_phy_sel_data_en_pol(struct rk_hdmi *hdmi, rt_uint8_t enable)
{
    rk_hdmi_mod(hdmi, HDMI_PHY_CONF0, HDMI_PHY_CONF0_SELDATAENPOL_MASK,
            enable << HDMI_PHY_CONF0_SELDATAENPOL_OFFSET);
}

static void rk_hdmi_phy_sel_interface_control(struct rk_hdmi *hdmi, rt_uint8_t enable)
{
    rk_hdmi_mod(hdmi, HDMI_PHY_CONF0, HDMI_PHY_CONF0_SELDIPIF_MASK,
            enable << HDMI_PHY_CONF0_SELDIPIF_OFFSET);
}

static rt_err_t rk_hdmi_phy_configure(struct rk_hdmi *hdmi, rt_uint32_t mpixelclock)
{
    rt_err_t err;
    const struct rk_hdmi_mpll_config *mpll_cfg = rockchip_mpll_cfg;
    const struct rk_hdmi_phy_config *phy_cfg = rockchip_phy_config;
    struct rk_hdmi_phy_write writes[8];
    rt_size_t i;
    rt_uint32_t waited_us = 0;

    while (mpll_cfg->mpixelclock != ~0u && mpixelclock > mpll_cfg->mpixelclock)
    {
        mpll_cfg++;
    }

    while (phy_cfg->mpixelclock != ~0u && mpixelclock > phy_cfg->mpixelclock)
    {
        phy_cfg++;
    }

    if (mpll_cfg->mpixelclock == ~0u || phy_cfg->mpixelclock == ~0u)
    {
        return -RT_EINVAL;
    }

    LOG_D("phy cfg: mpixel=%u mpll(cpce=0x%04x gmp=0x%04x curr=0x%04x) phy(sym=0x%04x term=0x%04x vlev=0x%04x)",
            mpixelclock,
            mpll_cfg->cpce, mpll_cfg->gmp, mpll_cfg->curr,
            phy_cfg->sym_ctr, phy_cfg->term, phy_cfg->vlev_ctr);

    rk_hdmi_phy_power_off(hdmi);
    rk_hdmi_phy_enable_svsret(hdmi, 1);

    rk_hdmi_write(hdmi, HDMI_MC_PHYRSTZ, HDMI_MC_PHYRSTZ_PHYRSTZ);
    rk_hdmi_write(hdmi, HDMI_MC_PHYRSTZ, 0);
    rk_hdmi_write(hdmi, HDMI_MC_HEACPHY_RST, HDMI_MC_HEACPHY_RST_ASSERT);

    rk_hdmi_phy_test_clear(hdmi, 1);
    rk_hdmi_write(hdmi, HDMI_PHY_I2CM_SLAVE_ADDR, HDMI_PHY_I2CM_SLAVE_ADDR_PHY_GEN2);
    rk_hdmi_phy_test_clear(hdmi, 0);

    writes[0] = (struct rk_hdmi_phy_write)
            { mpll_cfg->cpce, HDMI_3D_TX_PHY_CPCE_CTRL };
    writes[1] = (struct rk_hdmi_phy_write)
            { mpll_cfg->gmp, HDMI_3D_TX_PHY_GMPCTRL };
    writes[2] = (struct rk_hdmi_phy_write)
            { mpll_cfg->curr, HDMI_3D_TX_PHY_CURRCTRL };
    writes[3] = (struct rk_hdmi_phy_write)
            { 0x0000, HDMI_3D_TX_PHY_PLLPHBYCTRL };
    writes[4] = (struct rk_hdmi_phy_write)
            { HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_FB_CLK, HDMI_3D_TX_PHY_MSM_CTRL };
    writes[5] = (struct rk_hdmi_phy_write)
            { phy_cfg->term, HDMI_3D_TX_PHY_TXTERM };
    writes[6] = (struct rk_hdmi_phy_write)
            { phy_cfg->sym_ctr, HDMI_3D_TX_PHY_CKSYMTXCTRL };
    writes[7] = (struct rk_hdmi_phy_write)
            { phy_cfg->vlev_ctr, HDMI_3D_TX_PHY_VLEVCTRL };

    for (i = 0; i < RT_ARRAY_SIZE(writes); ++i)
    {
        err = rk_hdmi_phy_i2c_write(hdmi, writes[i].data, writes[i].addr);
        if (err)
        {
            LOG_W("PHY I2C write reg=0x%02x failed: %s",
                    writes[i].addr, rt_strerror(err));
            rk_hdmi_phy_power_off(hdmi);
            return err;
        }
    }

    rk_hdmi_phy_gen2_txpwron(hdmi, 1);
    rk_hdmi_phy_gen2_pddq(hdmi, 0);

    while (waited_us < 5000)
    {
        rt_uint8_t stat0 = rk_hdmi_read(hdmi, HDMI_PHY_STAT0);

        if (stat0 & HDMI_PHY_TX_PHY_LOCK)
        {
            return RT_EOK;
        }

        rt_hw_us_delay(100);
        waited_us += 100;
    }

    LOG_W("PHY pll lock timeout, stat0=0x%02x", rk_hdmi_read(hdmi, HDMI_PHY_STAT0));
    rk_hdmi_phy_power_off(hdmi);

    return -RT_ETIMEOUT;
}

static rt_err_t rk_hdmi_phy_init(struct rk_hdmi *hdmi)
{
    if (!hdmi->mode.pixelclock)
    {
        return -RT_EINVAL;
    }

    rk_hdmi_phy_sel_data_en_pol(hdmi, 1);
    rk_hdmi_phy_sel_interface_control(hdmi, 0);

    return rk_hdmi_phy_configure(hdmi,
            (rt_uint32_t)hdmi->mode.pixelclock);
}

static void rk_hdmi_video_sample(struct rk_hdmi *hdmi)
{
    rt_uint8_t val = HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE |
            (1 << HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET);

    rk_hdmi_write(hdmi, HDMI_TX_INVID0, val);

    val = HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE |
          HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE |
          HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE;

    rk_hdmi_write(hdmi, HDMI_TX_INSTUFFING, val);
    rk_hdmi_write(hdmi, HDMI_TX_GYDATA0, 0x00);
    rk_hdmi_write(hdmi, HDMI_TX_GYDATA1, 0x00);
    rk_hdmi_write(hdmi, HDMI_TX_RCRDATA0, 0x00);
    rk_hdmi_write(hdmi, HDMI_TX_RCRDATA1, 0x00);
    rk_hdmi_write(hdmi, HDMI_TX_BCBDATA0, 0x00);
    rk_hdmi_write(hdmi, HDMI_TX_BCBDATA1, 0x00);
}

static void rk_hdmi_video_packetize(struct rk_hdmi *hdmi)
{
    rt_uint8_t val;

    /*
     * Keep the 8-bit RGB888 HDMI path aligned with the Synopsys/U-Boot
     * configuration: bypass the packetizer datapath, no YCC422 remap, and
     * leave the default phase cleared.
     */
    val = ((0 << HDMI_VP_PR_CD_COLOR_DEPTH_OFFSET) & HDMI_VP_PR_CD_COLOR_DEPTH_MASK) |
          ((0 << HDMI_VP_PR_CD_DESIRED_PR_FACTOR_OFFSET) & HDMI_VP_PR_CD_DESIRED_PR_FACTOR_MASK);
    rk_hdmi_write(hdmi, HDMI_VP_PR_CD, val);

    rk_hdmi_mod(hdmi, HDMI_VP_STUFF, HDMI_VP_STUFF_PR_STUFFING_MASK,
            HDMI_VP_STUFF_PR_STUFFING_STUFFING_MODE);

    val = HDMI_VP_CONF_PR_EN_DISABLE |
          HDMI_VP_CONF_BYPASS_SELECT_VID_PACKETIZER;
    rk_hdmi_mod(hdmi, HDMI_VP_CONF,
            HDMI_VP_CONF_PR_EN_MASK | HDMI_VP_CONF_BYPASS_SELECT_MASK, val);

    rk_hdmi_mod(hdmi, HDMI_VP_STUFF, HDMI_VP_STUFF_IDEFAULT_PHASE_MASK, 0);

    rk_hdmi_write(hdmi, HDMI_VP_REMAP, 0);

    val = HDMI_VP_CONF_BYPASS_EN_ENABLE |
          HDMI_VP_CONF_PP_EN_DISABLE |
          HDMI_VP_CONF_YCC422_EN_DISABLE;
    rk_hdmi_mod(hdmi, HDMI_VP_CONF,
            HDMI_VP_CONF_BYPASS_EN_MASK |
            HDMI_VP_CONF_PP_EN_ENMASK |
            HDMI_VP_CONF_YCC422_EN_MASK, val);

    rk_hdmi_mod(hdmi, HDMI_VP_STUFF,
            HDMI_VP_STUFF_PP_STUFFING_MASK | HDMI_VP_STUFF_YCC422_STUFFING_MASK,
            HDMI_VP_STUFF_PP_STUFFING_STUFFING_MODE |
            HDMI_VP_STUFF_YCC422_STUFFING_STUFFING_MODE);

    rk_hdmi_mod(hdmi, HDMI_VP_CONF, HDMI_VP_CONF_OUTPUT_SELECTOR_MASK,
            HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS);
}

static void rk_hdmi_video_csc(struct rk_hdmi *hdmi)
{
    rt_size_t i;

    if (!hdmi)
    {
        return;
    }

    rk_hdmi_write(hdmi, HDMI_CSC_CFG,
            HDMI_CSC_CFG_INTMODE_DISABLE | HDMI_CSC_CFG_DECMODE_DISABLE);
    rk_hdmi_mod(hdmi, HDMI_CSC_SCALE,
            HDMI_CSC_SCALE_CSC_COLORDE_PTH_MASK |
            HDMI_CSC_SCALE_CSCSCALE_MASK,
            HDMI_CSC_SCALE_CSC_COLORDE_PTH_24BPP | 0x01);

    for (i = 0; i < 4; i++)
    {
        rt_uint16_t coeff_a = rk_hdmi_csc_coeff_default[0][i];
        rt_uint16_t coeff_b = rk_hdmi_csc_coeff_default[1][i];
        rt_uint16_t coeff_c = rk_hdmi_csc_coeff_default[2][i];

        rk_hdmi_write(hdmi, HDMI_CSC_COEF_A1_LSB + i * 2, coeff_a & 0xff);
        rk_hdmi_write(hdmi, HDMI_CSC_COEF_A1_MSB + i * 2, coeff_a >> 8);
        rk_hdmi_write(hdmi, HDMI_CSC_COEF_B1_LSB + i * 2, coeff_b & 0xff);
        rk_hdmi_write(hdmi, HDMI_CSC_COEF_B1_MSB + i * 2, coeff_b >> 8);
        rk_hdmi_write(hdmi, HDMI_CSC_COEF_C1_LSB + i * 2, coeff_c & 0xff);
        rk_hdmi_write(hdmi, HDMI_CSC_COEF_C1_MSB + i * 2, coeff_c >> 8);
    }
}

static void rk_hdmi_config_input_polarity(struct rk_hdmi *hdmi,
        const struct display_timing *tim)
{
    rt_uint8_t pol = HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_HIGH;

    if (!hdmi || !tim)
    {
        return;
    }

    pol |= (tim->flags & DISPLAY_TIMING_F_PVSYNC) ?
            HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_HIGH :
            HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_LOW;
    pol |= (tim->flags & DISPLAY_TIMING_F_PHSYNC) ?
            HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_HIGH :
            HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_LOW;

    rk_hdmi_mod(hdmi, HDMI_A_VIDPOLCFG,
            HDMI_A_VIDPOLCFG_VSYNCPOL_MASK |
            HDMI_A_VIDPOLCFG_HSYNCPOL_MASK |
            HDMI_A_VIDPOLCFG_DATAENPOL_MASK,
            pol);
}

#if DBG_LVL >= DBG_LOG
static void rk_hdmi_dump_regs(struct rk_hdmi *hdmi, const char *tag)
{
    if (!hdmi)
    {
        return;
    }

    LOG_D("%s: PHY_STAT0=0x%02x PHY_CONF0=0x%02x MC_CLKDIS=0x%02x MC_FLOWCTRL=0x%02x",
            tag,
            rk_hdmi_read(hdmi, HDMI_PHY_STAT0),
            rk_hdmi_read(hdmi, HDMI_PHY_CONF0),
            rk_hdmi_read(hdmi, HDMI_MC_CLKDIS),
            rk_hdmi_read(hdmi, HDMI_MC_FLOWCTRL));
    LOG_D("%s: FC_INVIDCONF=0x%02x A_HDCPCFG0=0x%02x TX_INVID0=0x%02x",
            tag,
            rk_hdmi_read(hdmi, HDMI_FC_INVIDCONF),
            rk_hdmi_read(hdmi, HDMI_A_HDCPCFG0),
            rk_hdmi_read(hdmi, HDMI_TX_INVID0));
    LOG_D("%s: A_VIDPOLCFG=0x%02x CONFIG2_ID=0x%02x",
            tag,
            rk_hdmi_read(hdmi, HDMI_A_VIDPOLCFG),
            rk_hdmi_read(hdmi, HDMI_CONFIG2_ID));
    LOG_D("%s: CSC_CFG=0x%02x CSC_SCALE=0x%02x",
            tag,
            rk_hdmi_read(hdmi, HDMI_CSC_CFG),
            rk_hdmi_read(hdmi, HDMI_CSC_SCALE));
    LOG_D("%s: VP_CONF=0x%02x VP_PR_CD=0x%02x VP_STUFF=0x%02x VP_REMAP=0x%02x",
            tag,
            rk_hdmi_read(hdmi, HDMI_VP_CONF),
            rk_hdmi_read(hdmi, HDMI_VP_PR_CD),
            rk_hdmi_read(hdmi, HDMI_VP_STUFF),
            rk_hdmi_read(hdmi, HDMI_VP_REMAP));
}
#endif /* DBG_LVL >= DBG_LOG */

static void rk_hdmi_av_composer(struct rk_hdmi *hdmi, const struct display_timing *tim)
{
    rt_uint32_t hblank = tim->hsync_len + tim->hfront_porch + tim->hback_porch;
    rt_uint32_t vblank = tim->vsync_len + tim->vfront_porch + tim->vback_porch;
    rt_uint8_t inv = HDMI_FC_INVIDCONF_HDCP_KEEPOUT_ACTIVE |
            HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_HIGH |
            HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_LOW |
            HDMI_FC_INVIDCONF_IN_I_P_PROGRESSIVE;

    inv |= hdmi->sink_is_hdmi ?
            HDMI_FC_INVIDCONF_DVI_MODEZ_HDMI_MODE :
            HDMI_FC_INVIDCONF_DVI_MODEZ_DVI_MODE;

    if (tim->flags & DISPLAY_TIMING_F_PHSYNC)
    {
        inv |= HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_HIGH;
    }
    else
    {
        inv |= HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_LOW;
    }

    if (tim->flags & DISPLAY_TIMING_F_PVSYNC)
    {
        inv |= HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_HIGH;
    }
    else
    {
        inv |= HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_LOW;
    }

    rk_hdmi_write(hdmi, HDMI_FC_INVIDCONF, inv);
    rk_hdmi_write(hdmi, HDMI_FC_INHACTV1, tim->hactive >> 8);
    rk_hdmi_write(hdmi, HDMI_FC_INHACTV0, tim->hactive);
    rk_hdmi_write(hdmi, HDMI_FC_INVACTV1, tim->vactive >> 8);
    rk_hdmi_write(hdmi, HDMI_FC_INVACTV0, tim->vactive);
    rk_hdmi_write(hdmi, HDMI_FC_INHBLANK1, hblank >> 8);
    rk_hdmi_write(hdmi, HDMI_FC_INHBLANK0, hblank);
    rk_hdmi_write(hdmi, HDMI_FC_INVBLANK, vblank);
    rk_hdmi_write(hdmi, HDMI_FC_HSYNCINDELAY1, tim->hfront_porch >> 8);
    rk_hdmi_write(hdmi, HDMI_FC_HSYNCINDELAY0, tim->hfront_porch);
    rk_hdmi_write(hdmi, HDMI_FC_VSYNCINDELAY, tim->vfront_porch);
    rk_hdmi_write(hdmi, HDMI_FC_HSYNCINWIDTH1, tim->hsync_len >> 8);
    rk_hdmi_write(hdmi, HDMI_FC_HSYNCINWIDTH0, tim->hsync_len);
    rk_hdmi_write(hdmi, HDMI_FC_VSYNCINWIDTH, tim->vsync_len);
}

static void rk_hdmi_enable_video_path(struct rk_hdmi *hdmi)
{
    rt_uint8_t clkdis = 0x7f;

    rk_hdmi_write(hdmi, HDMI_FC_CTRLDUR, 12);
    rk_hdmi_write(hdmi, HDMI_FC_EXCTRLDUR, 32);
    rk_hdmi_write(hdmi, HDMI_FC_EXCTRLSPAC, 1);
    rk_hdmi_write(hdmi, HDMI_FC_CH0PREAM, 0x0b);
    rk_hdmi_write(hdmi, HDMI_FC_CH1PREAM, 0x16);
    rk_hdmi_write(hdmi, HDMI_FC_CH2PREAM, 0x21);
    rk_hdmi_write(hdmi, HDMI_MC_FLOWCTRL, HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS);

    clkdis &= ~HDMI_MC_CLKDIS_PIXELCLK_DISABLE;
    rk_hdmi_write(hdmi, HDMI_MC_CLKDIS, clkdis);

    clkdis &= ~HDMI_MC_CLKDIS_TMDSCLK_DISABLE;

    if (hdmi->audio_enabled)
    {
        clkdis &= ~HDMI_MC_CLKDIS_AUDCLK_DISABLE;
    }

    rk_hdmi_write(hdmi, HDMI_MC_CLKDIS, clkdis);
}

static void rk_hdmi_clear_overflow(struct rk_hdmi *hdmi)
{
    rt_uint8_t val;
    int count;

    rk_hdmi_write(hdmi, HDMI_MC_SWRSTZ, (rt_uint8_t)~HDMI_MC_SWRSTZ_TMDSSWRST_REQ);

    val = rk_hdmi_read(hdmi, HDMI_FC_INVIDCONF);

    for (count = 0; count < 4; count++)
    {
        rk_hdmi_write(hdmi, HDMI_FC_INVIDCONF, val);
    }
}

static void rk_hdmi_stabilize_link(struct rk_hdmi *hdmi)
{
    /*
     * Match the Rockchip Linux DW-HDMI setup sequence.  Holding the frame
     * composer test video briefly gives the sink a continuous TMDS stream
     * while it acquires the newly programmed mode.
     */
    rk_hdmi_write(hdmi, HDMI_FC_DBGTMDS0, 0);
    rk_hdmi_write(hdmi, HDMI_FC_DBGTMDS1, 0);
    rk_hdmi_write(hdmi, HDMI_FC_DBGTMDS2, 0);
    rk_hdmi_write(hdmi, HDMI_FC_DBGFORCE, HDMI_FC_DBGFORCE_FORCEVIDEO);
    rt_thread_mdelay(50);
    rk_hdmi_write(hdmi, HDMI_FC_DBGFORCE, 0);
}

static void rk_hdmi_core_init(struct rk_hdmi *hdmi)
{
    rt_uint8_t ih_mute = HDMI_IH_MUTE_MUTE_WAKEUP_INTERRUPT |
            HDMI_IH_MUTE_MUTE_ALL_INTERRUPT;

    rk_hdmi_write(hdmi, HDMI_IH_MUTE, ih_mute);
    rk_hdmi_write(hdmi, HDMI_I2CM_INT, (rt_uint8_t)~HDMI_I2CM_INT_DONE_MASK);
    rk_hdmi_write(hdmi, HDMI_I2CM_CTLINT,
            (rt_uint8_t)~(HDMI_I2CM_CTLINT_NAC_MASK | HDMI_I2CM_CTLINT_ARB_MASK));
    rk_hdmi_write(hdmi, HDMI_IH_MUTE_FC_STAT2,
            HDMI_IH_MUTE_FC_STAT2_OVERFLOW_MASK);
}

static void rk_hdmi_phy_irq_init(struct rk_hdmi *hdmi)
{
    rk_hdmi_write(hdmi, HDMI_PHY_I2CM_INT_ADDR, HDMI_PHY_I2CM_INT_ADDR_DONE_POL);
    rk_hdmi_write(hdmi, HDMI_PHY_I2CM_CTLINT_ADDR,
            HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL | HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL);
    rk_hdmi_write(hdmi, HDMI_PHY_MASK0, (rt_uint8_t)~HDMI_PHY_HPD);
    rk_hdmi_write(hdmi, HDMI_IH_PHY_STAT0, HDMI_IH_PHY_STAT0_HPD);
}

static rt_err_t rk_hdmi_clks_enable(struct rk_hdmi *hdmi)
{
    rt_err_t err;

    if (hdmi->clks_enabled)
    {
        return RT_EOK;
    }

    err = rt_clk_array_prepare_enable(hdmi->clks);
    if (!err)
    {
        hdmi->clks_enabled = RT_TRUE;
    }

    return err;
}

static void rk_hdmi_clks_disable(struct rk_hdmi *hdmi)
{
    if (!hdmi->clks_enabled)
    {
        return;
    }

    rt_clk_array_disable_unprepare(hdmi->clks);
    hdmi->clks_enabled = RT_FALSE;
}

static rt_err_t rk_hdmi_detect(void *priv, rt_bool_t *connected)
{
    struct rk_hdmi *hdmi = priv;
    rt_bool_t enabled_for_detect = RT_FALSE;
    rt_uint32_t sample;
    rt_err_t err;

    if (!hdmi || !connected)
    {
        return -RT_EINVAL;
    }

    if (!hdmi->clks_enabled)
    {
        err = rk_hdmi_clks_enable(hdmi);
        if (err)
        {
            return err;
        }
        enabled_for_detect = RT_TRUE;

        /* The HPD synchronizer is not reliable on the first bus-clock cycle. */
        rt_hw_us_delay(1000);
    }

    *connected = RT_FALSE;
    for (sample = 0; sample < 3; ++sample)
    {
        if (rk_hdmi_read(hdmi, HDMI_PHY_STAT0) & HDMI_PHY_HPD)
        {
            *connected = RT_TRUE;
            break;
        }

        rt_hw_us_delay(1000);
    }

    /*
     * Keep a connected HDMI clock chain alive until prepare() takes ownership.
     * Cycling the shared VO/HPLL clocks between HPD detection and mode setup can
     * leave the HDMI-only path gated, while a later MIPI setup happens to bring
     * that shared chain back.  A disconnected probe may release its clocks.
     */
    if (enabled_for_detect && !*connected)
    {
        rk_hdmi_clks_disable(hdmi);
    }

    return RT_EOK;
}

static rt_err_t rk_hdmi_prepare(void *priv, rt_uint32_t vp_id, const struct display_timing *tim)
{
    struct rk_hdmi *hdmi = priv;
    rt_err_t err;

    RT_UNUSED(vp_id);
    RT_UNUSED(tim);

    if (!hdmi)
    {
        return -RT_EINVAL;
    }

    if (hdmi->prepared)
    {
        return RT_EOK;
    }

    err = rk_hdmi_clks_enable(hdmi);
    if (err)
    {
        return err;
    }

    if (hdmi->grf)
    {
        rt_syscon_write(hdmi->grf, RK3568_GRF_VO_CON1,
                RK3568_HDMI_SDAIN_MSK | RK3568_HDMI_SCLIN_MSK);
    }

    rk_hdmi_core_init(hdmi);
    rk_hdmi_phy_irq_init(hdmi);
    hdmi->prepared = RT_TRUE;

    LOG_D("prepared, HPD=%d", !!(rk_hdmi_read(hdmi, HDMI_PHY_STAT0) & HDMI_PHY_HPD));

    return RT_EOK;
}

static rt_err_t rk_hdmi_mode_set(void *priv, const struct display_timing *tim)
{
    struct rk_hdmi *hdmi = priv;

    if (!hdmi || !tim)
    {
        return -RT_EINVAL;
    }

    hdmi->mode = *tim;

    if (!hdmi->mode.htotal || !hdmi->mode.vtotal)
    {
        display_timing_derive(&hdmi->mode);
    }

    if (!hdmi->mode.pixelclock && hdmi->mode.htotal && hdmi->mode.vtotal)
    {
        hdmi->mode.pixelclock = (rt_uint64_t)hdmi->mode.htotal * hdmi->mode.vtotal * 60;
    }

    LOG_D("mode %ux%u htotal=%u vtotal=%u pclk=%u",
            hdmi->mode.hactive, hdmi->mode.vactive,
            hdmi->mode.htotal, hdmi->mode.vtotal,
            (rt_uint32_t)hdmi->mode.pixelclock);

    return RT_EOK;
}

static rt_err_t rk_hdmi_enable(void *priv, rt_bool_t enable)
{
    struct rk_hdmi *hdmi = priv;
    rt_err_t err;

    if (!hdmi)
    {
        return -RT_EINVAL;
    }

    if (!enable)
    {
        if (!hdmi->clks_enabled)
        {
            hdmi->enabled = RT_FALSE;
            return RT_EOK;
        }

        rk_hdmi_write(hdmi, HDMI_MC_CLKDIS, 0x7f);
        rk_hdmi_phy_power_off(hdmi);
        hdmi->enabled = RT_FALSE;
        return RT_EOK;
    }

    if (hdmi->enabled)
    {
        return RT_EOK;
    }

    if (!hdmi->prepared)
    {
        err = rk_hdmi_prepare(priv, 0, &hdmi->mode);
        if (err)
        {
            return err;
        }
    }

    if (!hdmi->mode.hactive || !hdmi->mode.vactive || !hdmi->mode.pixelclock)
    {
        return -RT_EINVAL;
    }

#if DBG_LVL >= DBG_LOG
    LOG_D("enable clocks: pixel=%u ref=%lu",
            (rt_uint32_t)hdmi->mode.pixelclock, rk_hdmi_clk_rate(hdmi, "ref"));
#endif

    rk_hdmi_av_composer(hdmi, &hdmi->mode);
    rk_hdmi_config_input_polarity(hdmi, &hdmi->mode);
    rk_hdmi_mod(hdmi, HDMI_A_HDCPCFG0,
            HDMI_A_HDCPCFG0_HDMIDVI_MASK,
            hdmi->sink_is_hdmi ? HDMI_A_HDCPCFG0_HDMIDVI_HDMI :
                                 HDMI_A_HDCPCFG0_HDMIDVI_DVI);
    rk_hdmi_mod(hdmi, HDMI_A_HDCPCFG0,
            HDMI_A_HDCPCFG0_AVMUTE_MASK, HDMI_A_HDCPCFG0_AVMUTE_DISABLE);

    rk_hdmi_enable_video_path(hdmi);
    rk_hdmi_video_packetize(hdmi);
    rk_hdmi_video_csc(hdmi);
    rk_hdmi_video_sample(hdmi);

    err = rk_hdmi_phy_init(hdmi);
    if (err)
    {
        rk_hdmi_write(hdmi, HDMI_MC_CLKDIS, 0x7f);
        return err;
    }

    rk_hdmi_clear_overflow(hdmi);
    rk_hdmi_stabilize_link(hdmi);
    hdmi->enabled = RT_TRUE;

#if DBG_LVL >= DBG_LOG
    rk_hdmi_dump_regs(hdmi, "post-enable");
#endif

    LOG_D("enabled, mode=%s HPD=%d stat0=0x%02x",
            hdmi->sink_is_hdmi ? "hdmi" : "dvi",
            !!(rk_hdmi_read(hdmi, HDMI_PHY_STAT0) & HDMI_PHY_HPD),
            rk_hdmi_read(hdmi, HDMI_PHY_STAT0));

    return RT_EOK;
}

static rt_err_t rk_hdmi_disable(void *priv)
{
    struct rk_hdmi *hdmi = priv;

    if (!hdmi)
    {
        return -RT_EINVAL;
    }

    rk_hdmi_enable(priv, RT_FALSE);
    rk_hdmi_clks_disable(hdmi);
    hdmi->prepared = RT_FALSE;

    return RT_EOK;
}

static const struct rockchip_connector_ops rk_hdmi_connector_ops =
{
    .detect = rk_hdmi_detect,
    .prepare = rk_hdmi_prepare,
    .mode_set = rk_hdmi_mode_set,
    .enable = rk_hdmi_enable,
    .disable = rk_hdmi_disable,
};

static rt_err_t rk_hdmi_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct rk_hdmi *hdmi = rt_calloc(1, sizeof(*hdmi));

    if (!hdmi)
    {
        return -RT_ENOMEM;
    }

    hdmi->regs = rt_ofw_iomap(np, 0);
    if (!hdmi->regs)
    {
        rt_free(hdmi);
        return -RT_EIO;
    }

    hdmi->clks = rt_clk_get_array(dev);
    if (rt_is_err(hdmi->clks))
    {
        rt_iounmap(hdmi->regs);
        rt_free(hdmi);
        return rt_ptr_err(hdmi->clks);
    }

    hdmi->reg_io_width = 4;
    rt_dm_dev_prop_read_u32(dev, "reg-io-width", &hdmi->reg_io_width);
    hdmi->sink_is_hdmi = RT_TRUE;
    hdmi->grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf");

    err = rockchip_display_register_connector(np, &rk_hdmi_connector_ops, hdmi);
    if (err)
    {
        rt_clk_array_put(hdmi->clks);
        rt_iounmap(hdmi->regs);
        rt_free(hdmi);
        return err;
    }

    pdev->parent.user_data = hdmi;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, hdmi);

    LOG_D("HDMI %s: reg-io-width=%u", rt_ofw_node_full_name(np), hdmi->reg_io_width);

    return RT_EOK;
}

static const struct rt_ofw_node_id rk_hdmi_ids[] =
{
    { .compatible = "rockchip,rk3568-dw-hdmi" },
    { .compatible = "rockchip,rk3528-dw-hdmi" },
    { .compatible = "rockchip,rk3399-dw-hdmi" },
    { .compatible = "rockchip,rk3288-dw-hdmi" },
    { .compatible = "rockchip,rk3328-dw-hdmi" },
    { /* sentinel */ }
};

static struct rt_platform_driver rk_hdmi_driver =
{
    .name = "dw-hdmi-rockchip",
    .ids = rk_hdmi_ids,
    .probe = rk_hdmi_probe,
};
RT_PLATFORM_DRIVER_EXPORT(rk_hdmi_driver);
