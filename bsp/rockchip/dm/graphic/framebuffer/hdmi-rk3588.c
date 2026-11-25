/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#include "rockchip-display.h"
#include "rockchip-hdmi.h"

#define DBG_TAG "hdmi.rk3588"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RK3588_GRF_SOC_CON2             0x0308
#define RK3588_GRF_SOC_CON7             0x031c
#define RK3588_GRF_SOC_STATUS1          0x0384
#define RK3588_HDMI0_HPD_INT_MSK        RT_BIT(13)
#define RK3588_HDMI1_HPD_INT_MSK        RT_BIT(15)
#define RK3588_HDMI0_LEVEL_INT          RT_BIT(16)
#define RK3588_HDMI1_LEVEL_INT          RT_BIT(24)
#define RK3588_SET_HPD_PATH_MASK        (0x3U << 12)

#define RK3588_GRF_VO1_CON3             0x000c
#define RK3588_GRF_VO1_CON4             0x0010
#define RK3588_GRF_VO1_CON6             0x0018
#define RK3588_GRF_VO1_CON7             0x001c
#define RK3588_GRF_VO1_CON9             0x0024
#define RK3588_HDMI21_MASK              RT_BIT(0)
#define RK3588_COMPRESS_MODE_MASK       RT_BIT(12)
#define RK3588_COLOR_FORMAT_MASK        0xfU
#define RK3588_COLOR_DEPTH_MASK         (0xfU << 4)
#define RK3588_8BPC                     0U
#define RK3588_RGB                      0U
#define RK3588_YUV444                   2U
#define RK3588_SCLIN                    RT_BIT(9)
#define RK3588_SDAIN                    RT_BIT(10)
#define RK3588_MODE                     RT_BIT(11)
#define RK3588_I2S_SEL                  RT_BIT(13)
#define RK3588_HDMI0_GRANT_SEL          RT_BIT(10)
#define RK3588_HDMI1_GRANT_SEL          RT_BIT(12)

#define TIMER_BASE_CONFIG0              0x0080
#define I2CM_FM_SCL_CONFIG0             0x00e4
#define I2CM_CONTROL0                   0x00ec
#define I2CM_INTERFACE_CONTROL0         0x00f4
#define I2CM_FM_EN                      RT_BIT(0)
#define HDCP2LOGIC_CONFIG0              0x08e0
#define HDCP2_BYPASS                    RT_BIT(0)
#define FRAME_COMPOSER_CONFIG9          0x0864
#define VIDEO_INTERFACE_CONTROL0        0x080c
#define VIDEO_INTERFACE_CONFIG0         0x0800
#define VIDEO_INTERFACE_FIFO_CLEAR      RT_BIT(0)
#define VIDEO_INTERFACE_ENABLE          RT_BIT(21)
#define LINK_CONFIG0                    0x0968
#define OPMODE_DVI                      RT_BIT(4)
#define OPMODE_FRL                      RT_BIT(0)
#define MAINUNIT_0_INT_MASK_N           0x3014
#define MAINUNIT_1_INT_MASK_N           0x3024
#define MAINUNIT_1_INT_CLEAR            0x3028
#define AVP_1_INT_MASK_N                0x3824
#define AVP_3_INT_MASK_N                0x3844
#define I2CM_NACK_RCVD_CLEAR            RT_BIT(2)
#define I2CM_OP_DONE_CLEAR              RT_BIT(0)

#define RK3588_HDMI_TMDS_MAX_RATE       594000000ULL

/* VOP owns dclk_vp*, while HDMI owns these controller clocks. */
#define RK3588_HDMI_CONTROLLER_CLK_COUNT 6

#define GLOBAL_SWRESET_REQUEST          0x0040
#define AVP_VIDEO_SWINIT                RT_BIT(6)
#define AVP_AUDIO_SWINIT                RT_BIT(10)
#define GLOBAL_SWDISABLE                0x0044
#define AVP_VIDEO_SWDISABLE             RT_BIT(6)
#define AVP_AUDIO_SWDISABLE             RT_BIT(10)
#define CMU_STATUS                      0x00b0
#define MAINUNIT_STATUS0                0x0180
#define VIDEO_INTERFACE_STATUS0         0x0814
#define FRAME_COMPOSER_CONTROL0         0x086c
#define AVP_0_INT_STATUS                0x3810
#define AVP_0_INT_CLEAR                 0x3818
#define AUDIO_INTERFACE_CONFIG0         0x0820
#define AUD_IF_I2S                      0x1
#define AUD_IF_SEL_MASK                 0x3
#define AUD_FIFO_INIT_ON_OVF            RT_BIT(2)
#define I2S_LINE0_EN                    RT_BIT(4)
#define I2S_LINES_EN_MASK               (0xfU << 4)
#define I2S_BPCUV_RCV_MASK              RT_BIT(12)
#define AUD_FORMAT_MASK                 (0x7U << 24)
#define AUD_FORMAT_ASP                  0
#define AUDIO_INTERFACE_CONTROL0        0x082c
#define AUDIO_FIFO_CLEAR                RT_BIT(0)
#define PKTSCHED_PKT_EN                 0x0aa8
#define PKTSCHED_AVI_TX_EN              RT_BIT(13)
#define PKTSCHED_GCP_TX_EN              RT_BIT(3)
#define PKTSCHED_PKT_CONTROL0           0x0aac
#define PKTSCHED_CLEAR_AVMUTE           2U
#define PKT_AVI_CONTENTS0               0x0be0
#define PKT_AVI_CONTENTS1               0x0be4
#define PKT_AVI_CONTENTS2               0x0be8
#define PKT_AVI_CONTENTS3               0x0bec
#define PKT_AVI_CONTENTS4               0x0bf0
#define PKTSCHED_PKT_CONFIG1            0x0a9c
#define PKTSCHED_AVI_FIELDRATE          RT_BIT(12)
#define FLT_CONFIG0                     0x0160
#define SCRAMB_CONFIG0                  0x0960
#define PKTSCHED_AUDI_TX_EN             RT_BIT(15)
#define PKTSCHED_AMD_TX_EN              RT_BIT(8)
#define PKTSCHED_AUDS_TX_EN             RT_BIT(2)
#define PKTSCHED_ACR_TX_EN              RT_BIT(1)
#define PKT_AUDI_CONTENTS0              0x0c20
#define PKT_AUDI_CONTENTS1              0x0c24
#define PKT_AUDI_CONTENTS2              0x0c28
#define AUDPKT_CONTROL0                 0x0e20
#define AUDPKT_PBIT_FORCE_EN            RT_BIT(12)
#define AUDPKT_CHSTATUS_OVR_EN          RT_BIT(0)
#define AUDPKT_ACR_CONTROL0             0x0e40
#define AUDPKT_ACR_N_MASK               0xfffffU
#define AUDPKT_ACR_CONTROL1             0x0e44
#define AUDPKT_ACR_CTS_OVR_EN           RT_BIT(1)
#define AUDPKT_CHSTATUS_OVR0            0x0e60
#define AUDPKT_CHSTATUS_OVR1            0x0e64

struct rk3588_hdmi
{
    void *regs;
    struct rt_syscon *grf;
    struct rt_syscon *vo1_grf;
    struct rt_phye *phy;
    struct rt_device *dev;
    struct rt_clk *clks[RK3588_HDMI_CONTROLLER_CLK_COUNT];
    struct rt_clk *link_clk;
    struct rt_clk *dclk;
    struct rt_reset_control *ref_rst;
    struct rt_reset_control *hdp_rst;
    struct display_timing mode;
    rt_uint8_t id;
    rt_bool_t clks_enabled;
    rt_bool_t link_clk_enabled;
    rt_bool_t dclk_enabled;
    rt_bool_t prepared;
    rt_bool_t enabled;
    rt_uint32_t audio_rate;
    rt_uint32_t audio_n;
    rt_bool_t audio_configured;
    rt_bool_t audio_enabled;
};

rt_inline rt_uint32_t rk3588_hdmi_read(struct rk3588_hdmi *hdmi, rt_uint32_t reg)
{
    return HWREG32((rt_uint8_t *)hdmi->regs + reg);
}

rt_inline void rk3588_hdmi_write(struct rk3588_hdmi *hdmi, rt_uint32_t reg,
        rt_uint32_t val)
{
    HWREG32((rt_uint8_t *)hdmi->regs + reg) = val;
    rt_hw_dsb();
}

static void rk3588_hdmi_mod(struct rk3588_hdmi *hdmi, rt_uint32_t reg,
        rt_uint32_t mask, rt_uint32_t val)
{
    rt_uint32_t tmp;

    tmp = rk3588_hdmi_read(hdmi, reg);

    tmp &= ~mask;
    rk3588_hdmi_write(hdmi, reg, tmp | (val & mask));
}

static rt_uint32_t rk3588_hdmi_audio_n(rt_uint64_t tmds, rt_uint32_t rate)
{
    rt_uint32_t min_n;
    rt_uint32_t max_n;
    rt_uint32_t ideal_n;
    rt_uint32_t best_n = 0;
    rt_uint64_t best_rem = ~(rt_uint64_t)0;
    rt_uint32_t n;

    if (!rate || !tmds)
    {
        return 0;
    }

    min_n = (128U * rate + 1499U) / 1500U;
    max_n = (128U * rate) / 300U;
    ideal_n = (128U * rate) / 1000U;

    for (n = min_n; n <= max_n; ++n)
    {
        rt_uint64_t rem = (tmds * n) % (128ULL * rate);

        if (rem < best_rem || (rem == best_rem &&
                (n > ideal_n ? n - ideal_n : ideal_n - n) <
                (best_n > ideal_n ? best_n - ideal_n : ideal_n - best_n)))
        {
            best_n = n;
            best_rem = rem;
        }

        if (!best_rem && n > ideal_n && n - ideal_n >
                (best_n > ideal_n ? best_n - ideal_n : ideal_n - best_n))
        {
            break;
        }
    }

    return best_n;
}

static rt_uint32_t rk3588_hdmi_audio_cs_rate(rt_uint32_t rate)
{
    switch (rate)
    {
    case 32000:
        return 0x3;
    case 44100:
        return 0x0;
    case 48000:
        return 0x2;
    case 88200:
        return 0x8;
    case 96000:
        return 0xa;
    case 176400:
        return 0xc;
    case 192000:
        return 0xe;
    default:
        return 0x1;
    }
}

static rt_err_t rk3588_hdmi_qp_audio_get(struct rt_ofw_node *np,
        struct rk3588_hdmi **hdmi)
{
    if (!np || !hdmi || !rt_ofw_node_is_compatible(np, "rockchip,rk3588-dw-hdmi"))
    {
        return -RT_ENOSYS;
    }

    *hdmi = rt_ofw_data(np);
    return *hdmi ? RT_EOK : -RT_ENOSYS;
}

rt_err_t rk3588_hdmi_qp_audio_enable(struct rt_ofw_node *np, rt_bool_t enable)
{
    struct rk3588_hdmi *hdmi;
    rt_err_t err;

    if ((err = rk3588_hdmi_qp_audio_get(np, &hdmi)))
    {
        return err;
    }

    if (enable && !hdmi->enabled)
    {
        return -RT_EBUSY;
    }

    if (enable)
    {
        if (hdmi->audio_enabled)
        {
            return RT_EOK;
        }

        rk3588_hdmi_mod(hdmi, GLOBAL_SWDISABLE, AVP_AUDIO_SWDISABLE, 0);
    }
    else
    {
        rk3588_hdmi_mod(hdmi, GLOBAL_SWDISABLE, AVP_AUDIO_SWDISABLE,
                AVP_AUDIO_SWDISABLE);
    }

    hdmi->audio_enabled = enable;
    return RT_EOK;
}

static void rk3588_hdmi_qp_audio_init(struct rk3588_hdmi *hdmi)
{
    rt_uint32_t n;

    n = rk3588_hdmi_audio_n(hdmi->mode.pixelclock, 48000);

    /* Match the QP core's display-enable audio startup sequence. */
    rk3588_hdmi_write(hdmi, AUDIO_INTERFACE_CONTROL0, AUDIO_FIFO_CLEAR);
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0, AUD_IF_SEL_MASK, AUD_IF_I2S);
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0, I2S_LINES_EN_MASK, I2S_LINE0_EN);
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0,
            I2S_BPCUV_RCV_MASK | AUD_FORMAT_MASK, AUD_FORMAT_ASP);
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0,
            AUD_FIFO_INIT_ON_OVF, AUD_FIFO_INIT_ON_OVF);
    rk3588_hdmi_mod(hdmi, AUDPKT_ACR_CONTROL0, AUDPKT_ACR_N_MASK, n);
    rk3588_hdmi_mod(hdmi, AUDPKT_ACR_CONTROL1,
            AUDPKT_ACR_CTS_OVR_EN, 0);
    rk3588_hdmi_write(hdmi, AUDPKT_CHSTATUS_OVR0, 0);
    rk3588_hdmi_write(hdmi, AUDPKT_CHSTATUS_OVR1,
            rk3588_hdmi_audio_cs_rate(48000) | (2U << 8));
    rk3588_hdmi_write(hdmi, AUDPKT_CONTROL0,
            AUDPKT_PBIT_FORCE_EN | AUDPKT_CHSTATUS_OVR_EN);
    rk3588_hdmi_write(hdmi, PKT_AUDI_CONTENTS1, 0x70U | (1U << 8));
    rk3588_hdmi_write(hdmi, PKT_AUDI_CONTENTS2, 0);
    rk3588_hdmi_write(hdmi, PKTSCHED_PKT_EN,
            PKTSCHED_AVI_TX_EN | PKTSCHED_GCP_TX_EN |
            PKTSCHED_ACR_TX_EN | PKTSCHED_AUDS_TX_EN | PKTSCHED_AUDI_TX_EN |
            PKTSCHED_AMD_TX_EN);
    rk3588_hdmi_mod(hdmi, GLOBAL_SWDISABLE, AVP_AUDIO_SWDISABLE, 0);

    hdmi->audio_rate = 48000;
    hdmi->audio_n = n;
    hdmi->audio_enabled = RT_TRUE;
    hdmi->audio_configured = RT_TRUE;
}

rt_err_t rk3588_hdmi_qp_audio_configure(struct rt_ofw_node *np,
        rt_uint32_t samplerate, rt_uint8_t channels, rt_uint8_t samplebits)
{
    struct rk3588_hdmi *hdmi;
    rt_uint32_t n;
    rt_uint32_t cs3;
    rt_err_t err;

    if ((err = rk3588_hdmi_qp_audio_get(np, &hdmi)))
    {
        return err;
    }

    if (!hdmi->enabled)
    {
        return -RT_EBUSY;
    }
    if (channels != 2 ||
            (samplebits != 16 && samplebits != 24 && samplebits != 32))
    {
        return -RT_EINVAL;
    }

    n = rk3588_hdmi_audio_n(hdmi->mode.pixelclock, samplerate);
    if (!n)
    {
        return -RT_EINVAL;
    }

    if (hdmi->audio_configured && hdmi->audio_rate == samplerate &&
            channels == 2 && samplebits == 16)
    {
        return RT_EOK;
    }

    /*
     * The QP audio register block is clocked by the AVP audio path.  Linux
     * enables that path from audio_startup before hw_params touches 0x820.
     */
    /*
     * The AVP audio datapath was initialized while enabling the link.  A
     * second software reset here makes the QP audio register window stop
     * responding on RK3588 before the FIFO clear can complete.
     */
    rk3588_hdmi_mod(hdmi, PKTSCHED_PKT_EN,
            PKTSCHED_ACR_TX_EN | PKTSCHED_AUDS_TX_EN |
            PKTSCHED_AUDI_TX_EN, 0);

    /* The FIFO was cleared during link enable while this QP window was live. */
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0, AUD_IF_SEL_MASK, AUD_IF_I2S);
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0, I2S_LINES_EN_MASK, I2S_LINE0_EN);
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0,
            I2S_BPCUV_RCV_MASK | AUD_FORMAT_MASK, AUD_FORMAT_ASP);
    rk3588_hdmi_mod(hdmi, AUDIO_INTERFACE_CONFIG0,
            AUD_FIFO_INIT_ON_OVF, AUD_FIFO_INIT_ON_OVF);

    /* Use the hardware CTS generator; only N is programmed by the driver. */
    rk3588_hdmi_mod(hdmi, AUDPKT_ACR_CONTROL0, AUDPKT_ACR_N_MASK, n);
    rk3588_hdmi_mod(hdmi, AUDPKT_ACR_CONTROL1,
            AUDPKT_ACR_CTS_OVR_EN, 0);

    /* IEC60958 consumer PCM, stereo layout 0 and matching source rate. */
    rk3588_hdmi_write(hdmi, AUDPKT_CHSTATUS_OVR0, 0);
    cs3 = rk3588_hdmi_audio_cs_rate(samplerate);
    rk3588_hdmi_write(hdmi, AUDPKT_CHSTATUS_OVR1, cs3 | (2U << 8));
    rk3588_hdmi_write(hdmi, AUDPKT_CONTROL0,
            AUDPKT_PBIT_FORCE_EN | AUDPKT_CHSTATUS_OVR_EN);

    /* HDMI Audio InfoFrame: LPCM, two channels, no channel allocation. */
    rk3588_hdmi_write(hdmi, PKT_AUDI_CONTENTS1, 0x70U | (1U << 8));
    rk3588_hdmi_write(hdmi, PKT_AUDI_CONTENTS2, 0);
    rk3588_hdmi_write(hdmi, PKTSCHED_PKT_EN,
            PKTSCHED_AVI_TX_EN | PKTSCHED_GCP_TX_EN |
            PKTSCHED_ACR_TX_EN | PKTSCHED_AUDS_TX_EN | PKTSCHED_AUDI_TX_EN |
            PKTSCHED_AMD_TX_EN);

    hdmi->audio_rate = samplerate;
    hdmi->audio_n = n;
    hdmi->audio_configured = RT_TRUE;
    LOG_D("HDMI%u audio %u Hz, %u ch, %u bit, N=%u", hdmi->id,
            samplerate, channels, samplebits, n);

    return RT_EOK;
}

static rt_err_t rk3588_hdmi_clks_enable(struct rk3588_hdmi *hdmi)
{
    rt_err_t err;
    rt_size_t i;

    if (hdmi->clks_enabled)
    {
        return RT_EOK;
    }

    for (i = 0; i < RK3588_HDMI_CONTROLLER_CLK_COUNT; ++i)
    {
        err = rt_clk_prepare_enable(hdmi->clks[i]);
        if (err)
        {
            while (i)
            {
                rt_clk_disable_unprepare(hdmi->clks[--i]);
            }
            return err;
        }
    }

    hdmi->clks_enabled = RT_TRUE;
    return RT_EOK;
}

static void rk3588_hdmi_clks_disable(struct rk3588_hdmi *hdmi)
{
    rt_size_t i;

    if (!hdmi->clks_enabled)
    {
        return;
    }

    for (i = RK3588_HDMI_CONTROLLER_CLK_COUNT; i; --i)
    {
        rt_clk_disable_unprepare(hdmi->clks[i - 1]);
    }

    hdmi->clks_enabled = RT_FALSE;
}

static rt_err_t rk3588_hdmi_reset_controller(struct rk3588_hdmi *hdmi)
{
    rt_err_t err;

    err = rt_reset_control_assert(hdmi->ref_rst);
    if (err)
    {
        return err;
    }
    err = rt_reset_control_assert(hdmi->hdp_rst);
    if (err)
    {
        return err;
    }

    rt_hw_us_delay(10);

    err = rt_reset_control_deassert(hdmi->ref_rst);
    if (err)
    {
        return err;
    }
    err = rt_reset_control_deassert(hdmi->hdp_rst);
    if (err)
    {
        return err;
    }

    return RT_EOK;
}

static rt_err_t rk3588_hdmi_link_clk_enable(struct rk3588_hdmi *hdmi)
{
    rt_err_t err;

    if (hdmi->link_clk_enabled)
    {
        return RT_EOK;
    }

    err = rt_clk_set_rate(hdmi->link_clk, hdmi->mode.pixelclock);
    if (err)
    {
        return err;
    }

    err = rt_clk_prepare_enable(hdmi->link_clk);
    if (!err)
    {
        hdmi->link_clk_enabled = RT_TRUE;
    }

    return err;
}

static void rk3588_hdmi_link_clk_disable(struct rk3588_hdmi *hdmi)
{
    if (!hdmi->link_clk_enabled)
    {
        return;
    }

    rt_clk_disable_unprepare(hdmi->link_clk);
    hdmi->link_clk_enabled = RT_FALSE;
}

static rt_err_t rk3588_hdmi_dclk_enable(struct rk3588_hdmi *hdmi)
{
    rt_err_t err;

    if (hdmi->dclk_enabled)
    {
        return RT_EOK;
    }

    err = rt_clk_prepare_enable(hdmi->dclk);
    if (!err)
    {
        hdmi->dclk_enabled = RT_TRUE;
    }

    return err;
}

static void rk3588_hdmi_dclk_disable(struct rk3588_hdmi *hdmi)
{
    if (!hdmi->dclk_enabled)
    {
        return;
    }

    rt_clk_disable_unprepare(hdmi->dclk);
    hdmi->dclk_enabled = RT_FALSE;
}

static void rk3588_hdmi_io_path_init(struct rk3588_hdmi *hdmi)
{
    rt_uint32_t io_cfg;
    rt_uint32_t hpd_mask;
    rt_uint32_t grant;
    rt_uint32_t vo1_con;

    io_cfg = RK3588_SCLIN | RK3588_SDAIN | RK3588_MODE | RK3588_I2S_SEL;
    hpd_mask = hdmi->id ? RK3588_HDMI1_HPD_INT_MSK :
            RK3588_HDMI0_HPD_INT_MSK;
    grant = hdmi->id ? RK3588_HDMI1_GRANT_SEL : RK3588_HDMI0_GRANT_SEL;
    vo1_con = hdmi->id ? RK3588_GRF_VO1_CON6 : RK3588_GRF_VO1_CON3;

    /* VOP2 presents the RT framebuffer to the QP as 8-bit RGB. */
    rt_syscon_write(hdmi->vo1_grf, hdmi->id ? RK3588_GRF_VO1_CON7 : RK3588_GRF_VO1_CON4,
            RK3588_HDMI21_MASK << 16);
    rt_syscon_write(hdmi->vo1_grf, vo1_con,
            RK3588_RGB |
            ((RK3588_COMPRESS_MODE_MASK | RK3588_COLOR_FORMAT_MASK |
              RK3588_COLOR_DEPTH_MASK) << 16));

    /* Match dw_hdmi_qp_rk3588_io_init(): do not disturb other VO1 fields. */
    rt_syscon_write(hdmi->vo1_grf, vo1_con, io_cfg | (io_cfg << 16));
    rt_syscon_write(hdmi->grf, RK3588_GRF_SOC_CON7,
            RK3588_SET_HPD_PATH_MASK | (RK3588_SET_HPD_PATH_MASK << 16));
    rt_syscon_write(hdmi->vo1_grf, RK3588_GRF_VO1_CON9, grant | (grant << 16));
    rt_syscon_write(hdmi->grf, RK3588_GRF_SOC_CON2, hpd_mask | (hpd_mask << 16));
}

static void rk3588_hdmi_qp_configure_avi(struct rk3588_hdmi *hdmi)
{
    /* AVI Y=0 declares the RGB transport selected in VO1 GRF. */
    rt_uint8_t pb1;
    rt_uint8_t pb2;
    rt_uint8_t pb3;
    rt_uint8_t pb4 = 0;        /* no CTA VIC for 2560x1440p60 */
    rt_uint8_t pb5 = 0;        /* default RGB quantization range */
    rt_uint8_t checksum;
    rt_uint32_t sum;

    pb1 = RK3588_RGB << 5;
    pb2 = 0;
    pb3 = 0;

    if (hdmi->mode.hactive == 1280 && hdmi->mode.vactive == 720 &&
            hdmi->mode.pixelclock == 74250000)
    {
        pb4 = 4; /* CEA-861 720p60 */
    }

    sum = 0x82 + 2 + 13 + pb1 + pb2 + pb3 + pb4 + pb5;
    checksum = (rt_uint8_t)(0U - sum);

    /* HDMI AVI v2: header lives in CONTENTS0, then checksum and PB1..PB13. */
    rk3588_hdmi_write(hdmi, PKT_AVI_CONTENTS0, (2U << 8) | (13U << 16));
    rk3588_hdmi_write(hdmi, PKT_AVI_CONTENTS1,
            checksum | ((rt_uint32_t)pb1 << 8) |
            ((rt_uint32_t)pb2 << 16) | ((rt_uint32_t)pb3 << 24));
    rk3588_hdmi_write(hdmi, PKT_AVI_CONTENTS2,
            pb4 | ((rt_uint32_t)pb5 << 8));
    rk3588_hdmi_write(hdmi, PKT_AVI_CONTENTS3, 0);
    rk3588_hdmi_write(hdmi, PKT_AVI_CONTENTS4, 0);
    rk3588_hdmi_write(hdmi, PKTSCHED_PKT_CONFIG1, 0);
}

static void rk3588_hdmi_qp_init(struct rk3588_hdmi *hdmi)
{
    /* The controller reset leaves the AVP datapath software-disabled. */
    rk3588_hdmi_write(hdmi, GLOBAL_SWRESET_REQUEST, AVP_VIDEO_SWINIT);
    rt_hw_us_delay(1);
    rk3588_hdmi_mod(hdmi, GLOBAL_SWDISABLE, AVP_VIDEO_SWDISABLE, 0);

    rk3588_hdmi_write(hdmi, MAINUNIT_0_INT_MASK_N, 0);
    rk3588_hdmi_write(hdmi, MAINUNIT_1_INT_MASK_N, 0);
    rk3588_hdmi_write(hdmi, AVP_1_INT_MASK_N, 0);
    rk3588_hdmi_write(hdmi, AVP_3_INT_MASK_N, 0);
    rk3588_hdmi_write(hdmi, TIMER_BASE_CONFIG0, 428571429U);

    /* Match dw_hdmi_qp_init_hw() after every controller reset. */
    rk3588_hdmi_write(hdmi, I2CM_CONTROL0, 1);
    rk3588_hdmi_write(hdmi, I2CM_FM_SCL_CONFIG0, 0x085c085cU);
    rk3588_hdmi_write(hdmi, I2CM_INTERFACE_CONTROL0, 0);
    rk3588_hdmi_write(hdmi, MAINUNIT_1_INT_CLEAR,
            I2CM_OP_DONE_CLEAR | I2CM_NACK_RCVD_CLEAR);
    rk3588_hdmi_write(hdmi, AVP_0_INT_CLEAR, 0xffffffffU);

    rk3588_hdmi_write(hdmi, LINK_CONFIG0, 0);
    rk3588_hdmi_write(hdmi, HDCP2LOGIC_CONFIG0, HDCP2_BYPASS);

    rk3588_hdmi_write(hdmi, FRAME_COMPOSER_CONFIG9, 2U << 8);
    rk3588_hdmi_write(hdmi, FLT_CONFIG0, 0);
    rk3588_hdmi_write(hdmi, SCRAMB_CONFIG0, 0);
    rk3588_hdmi_qp_configure_avi(hdmi);
    rk3588_hdmi_write(hdmi, PKTSCHED_PKT_EN,
            PKTSCHED_AVI_TX_EN | PKTSCHED_GCP_TX_EN);

    /* Let the QP accept the RGB stream presented by VOP2. */
    rk3588_hdmi_write(hdmi, VIDEO_INTERFACE_CONFIG0,
            VIDEO_INTERFACE_ENABLE);

    LOG_D("HDMI%u QP TMDS video path configured", hdmi->id);
}

static void rk3588_hdmi_qp_log_state(struct rk3588_hdmi *hdmi)
{
    LOG_D("HDMI%u QP state: cfg0=%08x swdis=%08x cmu=%08x main=%08x "
            "vif=%08x fc=%08x pkt=%08x avp0=%08x",
            hdmi->id,
            rk3588_hdmi_read(hdmi, VIDEO_INTERFACE_CONFIG0),
            rk3588_hdmi_read(hdmi, GLOBAL_SWDISABLE),
            rk3588_hdmi_read(hdmi, CMU_STATUS),
            rk3588_hdmi_read(hdmi, MAINUNIT_STATUS0),
            rk3588_hdmi_read(hdmi, VIDEO_INTERFACE_STATUS0),
            rk3588_hdmi_read(hdmi, FRAME_COMPOSER_CONTROL0),
            rk3588_hdmi_read(hdmi, PKTSCHED_PKT_EN),
            rk3588_hdmi_read(hdmi, AVP_0_INT_STATUS));
}

static rt_err_t rk3588_hdmi_prepare(void *priv, rt_uint32_t vp_id,
        const struct display_timing *tim)
{
    struct rk3588_hdmi *hdmi = priv;
    rt_err_t err;

    if (!hdmi || !tim)
    {
        return -RT_EINVAL;
    }

    /* The display framework calls connector prepare before mode_set. */
    hdmi->mode = *tim;
    if (!hdmi->mode.htotal || !hdmi->mode.vtotal)
    {
        display_timing_derive(&hdmi->mode);
    }
    if (!hdmi->mode.pixelclock ||
            hdmi->mode.pixelclock > RK3588_HDMI_TMDS_MAX_RATE)
    {
        return -RT_EINVAL;
    }

    if (hdmi->prepared)
    {
        return RT_EOK;
    }

    {
        char name[16];

        rt_snprintf(name, sizeof(name), "dclk_vp%u", vp_id);
        hdmi->dclk = rt_clk_get_by_name(hdmi->dev, name);
        if (rt_is_err_or_null(hdmi->dclk))
        {
            LOG_E("HDMI%u %s unavailable", hdmi->id, name);
            return -RT_ENOENT;
        }
    }

    /* The first probe can defer on the HDMI PHY before PM domains exist. */
    if (!hdmi->dev->power_domain_unit)
    {
        err = rt_dm_power_domain_attach(hdmi->dev, RT_TRUE);
        if (err)
        {
            LOG_E("HDMI%u VO1 power domain unavailable: %s", hdmi->id,
                    rt_strerror(err));
            rt_clk_put(hdmi->dclk);
            hdmi->dclk = RT_NULL;
            return err;
        }
    }

    err = rk3588_hdmi_clks_enable(hdmi);
    if (err)
    {
        rt_clk_put(hdmi->dclk);
        hdmi->dclk = RT_NULL;
        return err;
    }

    err = rk3588_hdmi_reset_controller(hdmi);
    if (err)
    {
        rk3588_hdmi_clks_disable(hdmi);
        rt_clk_put(hdmi->dclk);
        hdmi->dclk = RT_NULL;
        return err;
    }

    err = rk3588_hdmi_link_clk_enable(hdmi);
    if (err)
    {
        LOG_E("HDMI%u link clock failed: %d", hdmi->id, err);
        rk3588_hdmi_clks_disable(hdmi);
        rt_clk_put(hdmi->dclk);
        hdmi->dclk = RT_NULL;
        return err;
    }

    rk3588_hdmi_io_path_init(hdmi);
    hdmi->prepared = RT_TRUE;

    return RT_EOK;
}

static rt_err_t rk3588_hdmi_mode_set(void *priv, const struct display_timing *tim)
{
    struct rk3588_hdmi *hdmi = priv;

    if (!hdmi || !tim)
    {
        return -RT_EINVAL;
    }

    hdmi->mode = *tim;
    if (!hdmi->mode.htotal || !hdmi->mode.vtotal)
    {
        display_timing_derive(&hdmi->mode);
    }

    if (!hdmi->mode.pixelclock ||
            hdmi->mode.pixelclock > RK3588_HDMI_TMDS_MAX_RATE)
    {
        LOG_E("unsupported TMDS rate %u Hz", (rt_uint32_t)hdmi->mode.pixelclock);
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t rk3588_hdmi_detect(void *priv, rt_bool_t *connected)
{
    struct rk3588_hdmi *hdmi = priv;
    rt_uint32_t status;
    rt_err_t err;

    if (!hdmi || !connected)
    {
        return -RT_EINVAL;
    }

    err = rt_syscon_read(hdmi->grf, RK3588_GRF_SOC_STATUS1, &status);
    if (err)
    {
        return err;
    }

    *connected = !!(status & (hdmi->id ? RK3588_HDMI1_LEVEL_INT :
            RK3588_HDMI0_LEVEL_INT));

    return RT_EOK;
}

static rt_err_t rk3588_hdmi_enable(void *priv, rt_bool_t enable)
{
    struct rk3588_hdmi *hdmi = priv;
    union rt_phye_configure_opts opts = { 0 };
    rt_err_t err;
    rt_bool_t phy_inited = RT_FALSE;

    if (!hdmi)
    {
        return -RT_EINVAL;
    }
    if (!enable)
    {
        if (hdmi->enabled)
        {
            rt_phye_power_off(hdmi->phy);
            rt_phye_exit(hdmi->phy);
            hdmi->enabled = RT_FALSE;
        }
        rk3588_hdmi_dclk_disable(hdmi);
        if (!rt_is_err_or_null(hdmi->dclk))
        {
            rt_clk_put(hdmi->dclk);
            hdmi->dclk = RT_NULL;
        }
        rk3588_hdmi_link_clk_disable(hdmi);
        return RT_EOK;
    }
    if (hdmi->enabled)
    {
        return RT_EOK;
    }

    if (!hdmi->prepared)
    {
        err = rk3588_hdmi_prepare(hdmi, 0, &hdmi->mode);
        if (err)
        {
            return err;
        }
    }

    /* Mirror dw_hdmi_dclk_set(): the QP owns one dclk reference as well. */
    err = rk3588_hdmi_dclk_enable(hdmi);
    if (err)
    {
        LOG_E("HDMI%u dclk enable failed: %d", hdmi->id, err);
        return err;
    }

    /* VOP has enabled dclk_vp* before connector enable. */
    opts.hdmi.pixel_clock = hdmi->mode.pixelclock;
    opts.hdmi.tmds_clock = hdmi->mode.pixelclock;
    err = rt_phye_set_mode_simple(hdmi->phy, RT_PHYE_MODE_HDMI);
    if (!err)
    {
        err = rt_phye_configure(hdmi->phy, &opts);
    }
    if (!err)
    {
        err = rt_phye_init(hdmi->phy);
        phy_inited = !err;
    }
    if (!err)
    {
        err = rt_phye_power_on(hdmi->phy);
    }
    if (err)
    {
        if (phy_inited)
        {
            rt_phye_exit(hdmi->phy);
        }
        rk3588_hdmi_dclk_disable(hdmi);
        LOG_E("HDPTX setup failed: %d", err);
        return err;
    }

    /*
     * The QP register file is clocked by the HDPTX PLL.  EDK2 configures
     * that PLL before accessing the QP, then switches it into TMDS mode.
     * Keep the same ordering so a cold boot never programs an unclocked QP.
     */
    rk3588_hdmi_qp_init(hdmi);
    rk3588_hdmi_qp_audio_init(hdmi);
    /*
     * The sink sees AVMUTE until the PHY has had time to train.  U-Boot
     * waits 50 ms here; 50 us is not sufficient on a cold boot.
     */
    rt_hw_us_delay(50000);
    rk3588_hdmi_write(hdmi, PKTSCHED_PKT_CONTROL0, PKTSCHED_CLEAR_AVMUTE);
    rk3588_hdmi_mod(hdmi, PKTSCHED_PKT_EN,
            PKTSCHED_AVI_TX_EN | PKTSCHED_GCP_TX_EN,
            PKTSCHED_AVI_TX_EN | PKTSCHED_GCP_TX_EN);
    rk3588_hdmi_qp_log_state(hdmi);

    hdmi->enabled = RT_TRUE;
    LOG_D("HDMI%u TMDS enabled: %ux%u@%uHz", hdmi->id,
            hdmi->mode.hactive, hdmi->mode.vactive,
            (rt_uint32_t)hdmi->mode.pixelclock);

    return RT_EOK;
}

static rt_err_t rk3588_hdmi_disable(void *priv)
{
    struct rk3588_hdmi *hdmi = priv;

    if (!hdmi)
    {
        return -RT_EINVAL;
    }

    rk3588_hdmi_enable(hdmi, RT_FALSE);
    rk3588_hdmi_clks_disable(hdmi);
    hdmi->prepared = RT_FALSE;

    return RT_EOK;
}

static const struct rockchip_connector_ops rk3588_hdmi_ops =
{
    .detect = rk3588_hdmi_detect,
    .prepare = rk3588_hdmi_prepare,
    .mode_set = rk3588_hdmi_mode_set,
    .enable = rk3588_hdmi_enable,
    .disable = rk3588_hdmi_disable,
};

static rt_err_t rk3588_hdmi_probe(struct rt_platform_device *pdev)
{
    static const char * const clock_names[] =
    {
        "pclk", "hpd", "earc", "hdmitx_ref", "aud", "hclk_vo1",
    };
    struct rt_device *dev = &pdev->parent;
    struct rk3588_hdmi *hdmi;
    rt_size_t i;
    rt_err_t err;

    hdmi = rt_calloc(1, sizeof(*hdmi));
    if (!hdmi)
    {
        return -RT_ENOMEM;
    }

    hdmi->dev = dev;
    hdmi->regs = rt_ofw_iomap(dev->ofw_node, 0);
    hdmi->grf = rt_syscon_find_by_ofw_phandle(dev->ofw_node, "rockchip,grf");
    hdmi->vo1_grf = rt_syscon_find_by_ofw_phandle(dev->ofw_node,
            "rockchip,vo1_grf");
    if (!hdmi->regs || !hdmi->grf || !hdmi->vo1_grf)
    {
        LOG_E("%s: MMIO/GRF resource unavailable",
                rt_ofw_node_full_name(dev->ofw_node));
        err = -RT_EIO;
        goto _fail;
    }
    hdmi->id = rt_ofw_get_alias_id(dev->ofw_node, "hdmi");
    if (hdmi->id < 0 || hdmi->id > 1)
    {
        LOG_E("%s: invalid HDMI alias ID %d", rt_ofw_node_full_name(dev->ofw_node),
                hdmi->id);
        err = -RT_EINVAL;
        goto _fail;
    }

    for (i = 0; i < RT_ARRAY_SIZE(hdmi->clks); ++i)
    {
        hdmi->clks[i] = rt_clk_get_by_name(dev, clock_names[i]);
        if (rt_is_err_or_null(hdmi->clks[i]))
        {
            LOG_E("%s: clock '%s' unavailable", rt_ofw_node_full_name(dev->ofw_node),
                    clock_names[i]);
            err = -RT_EIO;
            goto _fail;
        }
    }

    hdmi->ref_rst = rt_reset_control_get_by_name(dev, "ref");
    hdmi->hdp_rst = rt_reset_control_get_by_name(dev, "hdp");
    if (rt_is_err_or_null(hdmi->ref_rst) || rt_is_err_or_null(hdmi->hdp_rst))
    {
        LOG_E("%s: HDMI reset controls unavailable",
                rt_ofw_node_full_name(dev->ofw_node));
        err = -RT_EIO;
        goto _fail;
    }

    hdmi->link_clk = rt_clk_get_by_name(dev, "link_clk");
    if (rt_is_err_or_null(hdmi->link_clk))
    {
        LOG_E("%s: link clock unavailable",
                rt_ofw_node_full_name(dev->ofw_node));
        err = -RT_EIO;
        goto _fail;
    }

    hdmi->phy = rt_phye_get_by_name(dev, "hdmi");
    if (rt_is_err_or_null(hdmi->phy))
    {
        LOG_E("%s: HDMI PHY unavailable",
                rt_ofw_node_full_name(dev->ofw_node));
        err = -RT_EIO;
        goto _fail;
    }

    err = rockchip_display_register_connector(dev->ofw_node, &rk3588_hdmi_ops, hdmi);
    if (err)
    {
        LOG_E("%s: connector registration failed: %d",
                rt_ofw_node_full_name(dev->ofw_node), err);
        goto _fail;
    }

    dev->user_data = hdmi;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, hdmi);

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(hdmi->phy))
    {
        rt_phye_put(hdmi->phy);
    }
    if (!rt_is_err_or_null(hdmi->hdp_rst))
    {
        rt_reset_control_put(hdmi->hdp_rst);
    }
    if (!rt_is_err_or_null(hdmi->ref_rst))
    {
        rt_reset_control_put(hdmi->ref_rst);
    }
    if (!rt_is_err_or_null(hdmi->link_clk))
    {
        rt_clk_put(hdmi->link_clk);
    }
    for (i = 0; i < RT_ARRAY_SIZE(hdmi->clks); ++i)
    {
        if (!rt_is_err_or_null(hdmi->clks[i]))
        {
            rt_clk_put(hdmi->clks[i]);
        }
    }
    if (hdmi->regs)
    {
        rt_iounmap(hdmi->regs);
    }
    rt_free(hdmi);

    return err;
}

static const struct rt_ofw_node_id rk3588_hdmi_ids[] =
{
    { .compatible = "rockchip,rk3588-dw-hdmi" },
    { /* sentinel */ }
};

static struct rt_platform_driver rk3588_hdmi_driver =
{
    .name = "dw-hdmi-qp-rk3588",
    .ids = rk3588_hdmi_ids,
    .probe = rk3588_hdmi_probe,
};
RT_PLATFORM_DRIVER_EXPORT(rk3588_hdmi_driver);
