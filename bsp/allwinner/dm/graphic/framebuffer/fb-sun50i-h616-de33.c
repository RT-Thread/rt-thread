/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "fb.h616"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mm_aspace.h>

#include "sunxi-display-output.h"
#include "sunxi-h616-hdmi.h"
#include "sunxi_tcon_top.h"

/* DE33 mixer register windows described by sun50i-h616.dtsi. */
#define DE33_TOP_GLB_CTL     0x0000
#define DE33_TOP_GLB_SIZE    0x0008
#define DE33_TOP_GLB_CLK     0x000c
#define DE33_BLD_BASE        0x1000
#define DE33_UI0_BASE        0xc1000
#define DE33_UI_ATTR         0x0000
#define DE33_UI_SIZE         0x0004
#define DE33_UI_COORD        0x0008
#define DE33_UI_PITCH        0x000c
#define DE33_UI_LADDR        0x0010
#define DE33_UI_HADDR        0x0080
#define DE33_UI_OVL_SIZE     0x0088
#define DE33_BLD_PIPE_CTL    0x0000
#define DE33_BLD_FCOLOR0     0x0004
#define DE33_BLD_INSIZE0     0x0008
#define DE33_BLD_COORD0      0x000c
#define DE33_BLD_ROUTE       0x0080
#define DE33_BLD_PREMULTIPLY 0x0084
#define DE33_BLD_BKCOLOR     0x0088
#define DE33_BLD_OUTSIZE     0x008c
#define DE33_BLD_MODE0       0x0090

#define TCON_GCTL    0x0000
#define TCON1_CTL    0x0090
#define TCON1_BASIC0 0x0094
#define TCON1_BASIC1 0x0098
#define TCON1_BASIC2 0x009c
#define TCON1_BASIC3 0x00a0
#define TCON1_BASIC4 0x00a4
#define TCON1_BASIC5 0x00a8
#define TCON1_IO_POL 0x00f0
#define TCON1_IO_TRI 0x00f4

/* Synopsys DW-HDMI registers; H616 uses byte-wide register addressing. */
#define HDMI_IH_PHY_STAT0            0x0104
#define HDMI_IH_I2CM_STAT0           0x0105
#define HDMI_IH_I2CMPHY_STAT0        0x0108
#define HDMI_IH_MUTE_PHY_STAT0       0x0184
#define HDMI_IH_MUTE_I2CM_STAT0      0x0185
#define HDMI_TX_INVID0               0x0200
#define HDMI_TX_INSTUFFING           0x0201
#define HDMI_VP_PR_CD                0x0801
#define HDMI_VP_STUFF                0x0802
#define HDMI_VP_REMAP                0x0803
#define HDMI_VP_CONF                 0x0804
#define HDMI_FC_INVIDCONF            0x1000
#define HDMI_FC_INHACTV0             0x1001
#define HDMI_FC_INHACTV1             0x1002
#define HDMI_FC_INHBLANK0            0x1003
#define HDMI_FC_INHBLANK1            0x1004
#define HDMI_FC_INVACTV0             0x1005
#define HDMI_FC_INVACTV1             0x1006
#define HDMI_FC_INVBLANK             0x1007
#define HDMI_FC_HSYNCINDELAY0        0x1008
#define HDMI_FC_HSYNCINDELAY1        0x1009
#define HDMI_FC_HSYNCINWIDTH0        0x100a
#define HDMI_FC_HSYNCINWIDTH1        0x100b
#define HDMI_FC_VSYNCINDELAY         0x100c
#define HDMI_FC_VSYNCINWIDTH         0x100d
#define HDMI_FC_CTRLDUR              0x1011
#define HDMI_FC_EXCTRLDUR            0x1012
#define HDMI_FC_EXCTRLSPAC           0x1013
#define HDMI_FC_CH0PREAM             0x1014
#define HDMI_FC_CH1PREAM             0x1015
#define HDMI_FC_CH2PREAM             0x1016
#define HDMI_FC_AUDICONF0            0x1025
#define HDMI_FC_AUDICONF1            0x1026
#define HDMI_FC_AUDICONF2            0x1027
#define HDMI_FC_AUDICONF3            0x1028
#define HDMI_FC_AUDSCONF             0x1063
#define HDMI_FC_AUDSCHNLS0           0x1067
#define HDMI_FC_AUDSCHNLS2           0x1069
#define HDMI_FC_AUDSCHNLS3           0x106a
#define HDMI_FC_AUDSCHNLS4           0x106b
#define HDMI_FC_AUDSCHNLS5           0x106c
#define HDMI_FC_AUDSCHNLS6           0x106d
#define HDMI_FC_AUDSCHNLS7           0x106e
#define HDMI_FC_AUDSCHNLS8           0x106f
#define HDMI_FC_DATAUTO3             0x10b7
#define HDMI_PHY_CONF0               0x3000
#define HDMI_PHY_TST0                0x3001
#define HDMI_PHY_STAT0               0x3004
#define HDMI_PHY_POL0                0x3007
#define HDMI_PHY_I2CM_SLAVE_ADDR     0x3020
#define HDMI_PHY_I2CM_ADDRESS_ADDR   0x3021
#define HDMI_PHY_I2CM_DATAO_1_ADDR   0x3022
#define HDMI_PHY_I2CM_DATAO_0_ADDR   0x3023
#define HDMI_PHY_I2CM_OPERATION_ADDR 0x3026
#define HDMI_I2CM_SLAVE              0x7e00
#define HDMI_I2CM_ADDRESS            0x7e01
#define HDMI_I2CM_DATAI              0x7e03
#define HDMI_I2CM_OPERATION          0x7e04
#define HDMI_I2CM_INT                0x7e05
#define HDMI_I2CM_CTLINT             0x7e06
#define HDMI_I2CM_DIV                0x7e07
#define HDMI_I2CM_SOFTRSTZ           0x7e09
#define HDMI_MC_CLKDIS               0x4001
#define HDMI_MC_SWRSTZ               0x4002
#define HDMI_MC_FLOWCTRL             0x4004
#define HDMI_MC_PHYRSTZ              0x4005
#define HDMI_MC_HEACPHY_RST          0x4007
#define HDMI_CSC_CFG                 0x4100
#define HDMI_AUD_CONF0               0x3100
#define HDMI_AUD_CONF1               0x3101
#define HDMI_AUD_N1                  0x3200
#define HDMI_AUD_N2                  0x3201
#define HDMI_AUD_N3                  0x3202
#define HDMI_AUD_CTS1                0x3203
#define HDMI_AUD_CTS2                0x3204
#define HDMI_AUD_CTS3                0x3205
#define HDMI_AUD_INPUTCLKFS          0x3206

#define HDMI_PHY_STAT0_LOCK       RT_BIT(0)
#define HDMI_PHY_STAT0_HPD        RT_BIT(1)
#define HDMI_PHY_SVSRET           RT_BIT(5)
#define HDMI_PHY_PDDQ             RT_BIT(4)
#define HDMI_PHY_TXPWRON          RT_BIT(3)
#define HDMI_PHY_DATA_EN_POL      RT_BIT(1)
#define HDMI_PHY_I2C_DONE         RT_BIT(1)
#define HDMI_PHY_I2C_ERROR        RT_BIT(0)
#define HDMI_PHY_I2C_WRITE        0x10
#define HDMI_PHY_I2C_ADDR         0x69
#define HDMI_PHY_HPD              0x02
#define HDMI_PHY_RX_SENSE0        0x10
#define HDMI_IH_PHY_HPD           0x01
#define HDMI_IH_PHY_RX_SENSE0     0x04
#define HDMI_IH_I2CM_DONE         0x02
#define HDMI_IH_I2CM_ERROR        0x01
#define HDMI_I2CM_READ            0x01
#define HDMI_I2CM_INT_DONE_POL    0x08
#define HDMI_I2CM_CTLINT_NAC_POL  0x80
#define HDMI_I2CM_CTLINT_ARB_POL  0x08
#define HDMI_MC_CLKDIS_AUDCLK     RT_BIT(3)
#define HDMI_AUD_CONF0_I2S        RT_BIT(5)
#define HDMI_AUD_CONF1_WIDTH_16   0x10
#define HDMI_AUD_CONF1_WIDTH_24   0x18
#define HDMI_AUD_INPUTCLKFS_512FS 2

#define H616_HDMI_PHY_REXT_CTRL 0x0004
#define H616_HDMI_PHY_REXT_EN   RT_BIT(31)

struct h616_fb_block
{
    struct rt_ofw_node *node;
    struct rt_clk_array *clks;
    struct rt_reset_control *resets;
    void *base;
    rt_bool_t enabled;
};

struct h616_fb
{
    struct rt_graphic_device parent;
    struct rt_device *dev;
    struct rt_clk_array *mixer_clks;
    struct rt_reset_control *mixer_resets;
    struct rt_ofw_node *top_np;
    void *layer;
    void *top;
    void *display;
    void *phy;
    struct h616_fb_block tcon;
    struct h616_fb_block hdmi;
    struct h616_fb_block hdmi_phy;
    struct sunxi_fb_timing timing;
    rt_ubase_t framebuffer_dma;
    int hpd_irq;
    rt_bool_t mixer_enabled;
    rt_bool_t timing_from_dt;
    rt_bool_t hpd;
    rt_bool_t edid_valid;
    rt_uint8_t edid[sizeof(struct edid)];
};

struct h616_hdmi_phy_cfg
{
    rt_uint32_t max_pixelclock;
    rt_uint16_t cpce, gmp, curr;
    rt_uint16_t sym, term, vlev;
};

static struct h616_fb *h616_hdmi_active;

/* Values are the H616 variant from Linux's sun8i_hdmi_phy.c. */
static const struct h616_hdmi_phy_cfg h616_hdmi_phy_cfgs[] = {
    { 27000000, 0x00b3, 0x2153, 0x0012, 0x8009, 0x0007, 0x02b0 },
    { 74250000, 0x0072, 0x2145, 0x0013, 0x8019, 0x0004, 0x0290 },
    { 148500000, 0x0051, 0x214c, 0x0019, 0x8019, 0x0004, 0x0290 },
    { 297000000, 0x0040, 0x3b4c, 0x0019, 0x8039, 0x0004, 0x022b },
    { 594000000, 0x1a40, 0x3b4c, 0x0010, 0x8029, 0x0000, 0x008a },
};

static void h616_program_de(struct h616_fb *fb);
static void h616_program_tcon(struct h616_fb *fb);
static rt_err_t h616_block_set_rate(struct h616_fb_block *block,
                                    const char *name, rt_ubase_t rate);

static const rt_uint32_t h616_fb_modes[] = {
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
};

static rt_err_t h616_timing_read(struct rt_ofw_node *np, const char *name,
                                 rt_uint32_t *value)
{
    int count = rt_ofw_prop_count_of_u32(np, name);

    if (count <= 0)
    {
        return count ? (rt_err_t)count : -RT_ENOENT;
    }
    return rt_ofw_prop_read_u32_index(np, name, count >= 3 ? 1 : 0, value);
}

static rt_err_t h616_timing_parse_node(struct rt_ofw_node *np,
                                       struct sunxi_fb_timing *timing)
{
    rt_uint32_t value;
    rt_uint64_t htotal, vtotal;

    rt_memset(timing, 0, sizeof(*timing));
    if (h616_timing_read(np, "clock-frequency", &timing->pixelclock) ||
        h616_timing_read(np, "hactive", &timing->hactive) ||
        h616_timing_read(np, "hfront-porch", &timing->hfront_porch) ||
        h616_timing_read(np, "hback-porch", &timing->hback_porch) ||
        h616_timing_read(np, "hsync-len", &timing->hsync_len) ||
        h616_timing_read(np, "vactive", &timing->vactive) ||
        h616_timing_read(np, "vfront-porch", &timing->vfront_porch) ||
        h616_timing_read(np, "vback-porch", &timing->vback_porch) ||
        h616_timing_read(np, "vsync-len", &timing->vsync_len))
    {
        return -RT_EINVAL;
    }
    timing->hsync_active = RT_TRUE;
    timing->vsync_active = RT_TRUE;
    if (!rt_ofw_prop_read_u32(np, "hsync-active", &value))
    {
        timing->hsync_active = !!value;
    }
    if (!rt_ofw_prop_read_u32(np, "vsync-active", &value))
    {
        timing->vsync_active = !!value;
    }
    htotal = (rt_uint64_t)timing->hactive + timing->hfront_porch +
             timing->hback_porch + timing->hsync_len;
    vtotal = (rt_uint64_t)timing->vactive + timing->vfront_porch +
             timing->vback_porch + timing->vsync_len;
    if (!timing->pixelclock || !timing->hactive || !timing->vactive ||
        !timing->hsync_len || !timing->vsync_len || timing->hactive > 4096 ||
        timing->vactive > 4096 || htotal > 8192 || vtotal > 4095)
    {
        return -RT_EINVAL;
    }
    timing->htotal = (rt_uint32_t)htotal;
    timing->vtotal = (rt_uint32_t)vtotal;
    return RT_EOK;
}

static rt_err_t h616_timing_parse(struct h616_fb *fb)
{
    struct rt_ofw_node *timings, *child;
    rt_err_t err;

    if (!(err = h616_timing_parse_node(fb->dev->ofw_node, &fb->timing)))
    {
        fb->timing_from_dt = RT_TRUE;
        return RT_EOK;
    }
    timings = rt_ofw_get_child_by_tag(fb->dev->ofw_node, "display-timings");
    if (timings)
    {
        child = rt_ofw_parse_phandle(timings, "native-mode", 0);
        if (child)
        {
            err = h616_timing_parse_node(child, &fb->timing);
            rt_ofw_node_put(child);
        }
        if (err)
        {
            rt_ofw_foreach_available_child_node(timings, child)
            {
                err = h616_timing_parse_node(child, &fb->timing);
                rt_ofw_node_put(child);
                if (!err)
                {
                    break;
                }
            }
        }
        rt_ofw_node_put(timings);
        if (!err)
        {
            fb->timing_from_dt = RT_TRUE;
            return RT_EOK;
        }
    }

    /* Start with a CEA mode, then replace it from a connected sink's EDID. */
    fb->timing.pixelclock = 74250000;
    fb->timing.hactive = 1280;
    fb->timing.hfront_porch = 110;
    fb->timing.hsync_len = 40;
    fb->timing.hback_porch = 220;
    fb->timing.vactive = 720;
    fb->timing.vfront_porch = 5;
    fb->timing.vsync_len = 5;
    fb->timing.vback_porch = 20;
    fb->timing.htotal = 1650;
    fb->timing.vtotal = 750;
    fb->timing.hsync_active = RT_TRUE;
    fb->timing.vsync_active = RT_TRUE;
    return RT_EOK;
}

static rt_uint32_t h616_de_format(rt_uint32_t mode)
{
    switch (mode)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        return 0;
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        return 1;
    default:
        return RT_UINT32_MAX;
    }
}

static void h616_hdmi_write(struct h616_fb *fb, rt_uint32_t reg, rt_uint8_t value)
{
    HWREG8((rt_uint8_t *)fb->hdmi.base + reg) = value;
}

static rt_uint8_t h616_hdmi_read(struct h616_fb *fb, rt_uint32_t reg)
{
    return HWREG8((rt_uint8_t *)fb->hdmi.base + reg);
}

static void h616_hdmi_update(struct h616_fb *fb, rt_uint32_t reg,
                             rt_uint8_t mask, rt_uint8_t value)
{
    h616_hdmi_write(fb, reg, (h616_hdmi_read(fb, reg) & ~mask) | (value & mask));
}

static rt_uint32_t h616_hdmi_audio_n(rt_uint32_t samplerate,
                                     rt_uint32_t pixelclock)
{
    rt_uint32_t rate = samplerate;
    rt_uint32_t multiplier = 1;
    rt_uint32_t n;

    while (rate > 48000)
    {
        rate /= 2;
        multiplier *= 2;
    }
    switch (rate)
    {
    case 32000:
        n = pixelclock == 27027000 ? 4096 : pixelclock == 74176000 || pixelclock == 148352000 ? 11648
                                                                                              : 4096;
        break;
    case 44100:
        n = pixelclock == 25175000 ? 7007 : pixelclock == 74176000 ? 17836
                                        : pixelclock == 148352000  ? 8918
                                                                   : 6272;
        break;
    case 48000:
        n = pixelclock == 27027000 ? 6144 : pixelclock == 74176000 ? 11648
                                        : pixelclock == 148352000  ? 5824
                                                                   : 6144;
        break;
    default:
        n = 128 * rate / 1000;
        break;
    }
    return n * multiplier;
}

static rt_uint8_t h616_hdmi_audio_frequency(rt_uint32_t samplerate)
{
    switch (samplerate)
    {
    case 32000:
        return 0x03;
    case 44100:
        return 0x00;
    case 48000:
        return 0x02;
    case 88200:
        return 0x08;
    case 96000:
        return 0x0a;
    case 176400:
        return 0x0c;
    case 192000:
        return 0x0e;
    default:
        return 0x01;
    }
}

static rt_uint8_t h616_hdmi_audio_original_frequency(rt_uint32_t samplerate)
{
    switch (samplerate)
    {
    case 32000:
        return 0x0c;
    case 44100:
        return 0x0f;
    case 48000:
        return 0x0d;
    case 88200:
        return 0x07;
    case 96000:
        return 0x05;
    case 176400:
        return 0x03;
    case 192000:
        return 0x01;
    default:
        return 0;
    }
}

static rt_uint8_t h616_hdmi_channel_allocation(rt_uint32_t channels)
{
    static const rt_uint8_t allocations[] = { 0x00, 0x00, 0x01, 0x03,
                                              0x07, 0x0b, 0x13, 0x1f };

    return allocations[channels - 1];
}

rt_err_t sunxi_h616_hdmi_audio_configure(rt_uint32_t samplerate,
                                         rt_uint32_t channels, rt_uint32_t samplebits)
{
    struct h616_fb *fb = h616_hdmi_active;
    rt_uint32_t n;
    rt_uint8_t lanes;

    if (!fb)
    {
        return -RT_EIO;
    }
    if (!channels || channels > 8 || (samplebits != 16 && samplebits != 24 && samplebits != 32))
    {
        return -RT_EINVAL;
    }
    n = h616_hdmi_audio_n(samplerate, fb->timing.pixelclock);
    lanes = RT_BIT((channels - 1) / 2 + 1) - 1;
    h616_hdmi_write(fb, HDMI_AUD_CONF0, 0x80);
    h616_hdmi_write(fb, HDMI_AUD_CONF1, samplebits == 16 ? HDMI_AUD_CONF1_WIDTH_16 : HDMI_AUD_CONF1_WIDTH_24);
    h616_hdmi_write(fb, HDMI_AUD_INPUTCLKFS, HDMI_AUD_INPUTCLKFS_512FS);
    h616_hdmi_write(fb, HDMI_AUD_N1, n);
    h616_hdmi_write(fb, HDMI_AUD_N2, n >> 8);
    h616_hdmi_write(fb, HDMI_AUD_N3, n >> 16);
    h616_hdmi_write(fb, HDMI_AUD_CTS1, 0);
    h616_hdmi_write(fb, HDMI_AUD_CTS2, 0);
    h616_hdmi_write(fb, HDMI_AUD_CTS3, 0);
    h616_hdmi_write(fb, HDMI_FC_AUDICONF0, (channels - 1) << 4);
    h616_hdmi_write(fb, HDMI_FC_AUDICONF1, h616_hdmi_audio_frequency(samplerate));
    h616_hdmi_write(fb, HDMI_FC_AUDICONF2, h616_hdmi_channel_allocation(channels));
    h616_hdmi_write(fb, HDMI_FC_AUDICONF3, 0);
    h616_hdmi_write(fb, HDMI_FC_AUDSCONF, channels > 2 ? 1 : 0);
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS0, 1);
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS2, channels);
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS3, 0x22);
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS4, 0x22);
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS5, 0x11);
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS6, 0x11);
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS7,
                    0x30 | h616_hdmi_audio_frequency(samplerate));
    h616_hdmi_write(fb, HDMI_FC_AUDSCHNLS8,
                    (h616_hdmi_audio_original_frequency(samplerate) << 4) | 0x0b);
    h616_hdmi_write(fb, HDMI_AUD_CONF0, HDMI_AUD_CONF0_I2S | lanes);
    return RT_EOK;
}

void sunxi_h616_hdmi_audio_enable(rt_bool_t enable)
{
    struct h616_fb *fb = h616_hdmi_active;

    if (!fb)
    {
        return;
    }
    h616_hdmi_update(fb, HDMI_MC_CLKDIS, HDMI_MC_CLKDIS_AUDCLK,
                     enable ? 0 : HDMI_MC_CLKDIS_AUDCLK);
}

static rt_err_t h616_hdmi_ddc_read_byte(struct h616_fb *fb, rt_uint8_t offset,
                                        rt_uint8_t *value)
{
    rt_uint32_t waited;

    h616_hdmi_write(fb, HDMI_IH_I2CM_STAT0,
                    HDMI_IH_I2CM_DONE | HDMI_IH_I2CM_ERROR);
    h616_hdmi_write(fb, HDMI_I2CM_ADDRESS, offset);
    h616_hdmi_write(fb, HDMI_I2CM_OPERATION, HDMI_I2CM_READ);
    for (waited = 0; waited < 20000; waited += 100)
    {
        rt_uint8_t status = h616_hdmi_read(fb, HDMI_IH_I2CM_STAT0);

        if (status & (HDMI_IH_I2CM_DONE | HDMI_IH_I2CM_ERROR))
        {
            h616_hdmi_write(fb, HDMI_IH_I2CM_STAT0, status);
            if (status & HDMI_IH_I2CM_ERROR)
            {
                return -RT_EIO;
            }
            *value = h616_hdmi_read(fb, HDMI_I2CM_DATAI);
            return RT_EOK;
        }
        rt_hw_us_delay(100);
    }
    return -RT_ETIMEOUT;
}

static rt_err_t h616_hdmi_read_edid(struct h616_fb *fb)
{
    rt_uint32_t sum = 0;
    rt_size_t i;
    rt_err_t err;

    if (!(h616_hdmi_read(fb, HDMI_PHY_STAT0) & HDMI_PHY_STAT0_HPD))
    {
        return -RT_EIO;
    }
    h616_hdmi_write(fb, HDMI_I2CM_SOFTRSTZ, 0);
    h616_hdmi_write(fb, HDMI_I2CM_DIV, 0);
    h616_hdmi_write(fb, HDMI_I2CM_INT, HDMI_I2CM_INT_DONE_POL);
    h616_hdmi_write(fb, HDMI_I2CM_CTLINT,
                    HDMI_I2CM_CTLINT_NAC_POL | HDMI_I2CM_CTLINT_ARB_POL);
    h616_hdmi_write(fb, HDMI_IH_MUTE_I2CM_STAT0,
                    HDMI_IH_I2CM_DONE | HDMI_IH_I2CM_ERROR);
    h616_hdmi_write(fb, HDMI_I2CM_SLAVE, 0x50);

    for (i = 0; i < sizeof(fb->edid); i++)
    {
        if ((err = h616_hdmi_ddc_read_byte(fb, i, &fb->edid[i])))
        {
            return err;
        }
        sum += fb->edid[i];
    }
    if (rt_memcmp(fb->edid, "\x00\xff\xff\xff\xff\xff\xff\x00", 8) ||
        (sum & 0xff))
    {
        return -RT_EINVAL;
    }
    fb->edid_valid = RT_TRUE;
    return RT_EOK;
}

static rt_err_t h616_timing_from_edid(struct h616_fb *fb)
{
    const rt_uint8_t *dtd = &fb->edid[54];
    struct sunxi_fb_timing timing = { 0 };
    rt_uint32_t hblank, vblank;
    rt_uint64_t htotal, vtotal;

    if (!fb->edid_valid || (!dtd[0] && !dtd[1]))
    {
        return -RT_ENOENT;
    }
    timing.pixelclock = ((rt_uint32_t)dtd[0] | ((rt_uint32_t)dtd[1] << 8)) * 10000;
    timing.hactive = dtd[2] | ((rt_uint32_t)(dtd[4] & 0xf0) << 4);
    hblank = dtd[3] | ((rt_uint32_t)(dtd[4] & 0x0f) << 8);
    timing.vactive = dtd[5] | ((rt_uint32_t)(dtd[7] & 0xf0) << 4);
    vblank = dtd[6] | ((rt_uint32_t)(dtd[7] & 0x0f) << 8);
    timing.hfront_porch = dtd[8] | ((rt_uint32_t)(dtd[11] & 0xc0) << 2);
    timing.hsync_len = dtd[9] | ((rt_uint32_t)(dtd[11] & 0x30) << 4);
    timing.vfront_porch = (dtd[10] >> 4) | ((rt_uint32_t)(dtd[11] & 0x0c) << 2);
    timing.vsync_len = (dtd[10] & 0x0f) | ((rt_uint32_t)(dtd[11] & 0x03) << 4);
    if (hblank <= timing.hfront_porch + timing.hsync_len ||
        vblank <= timing.vfront_porch + timing.vsync_len)
    {
        return -RT_EINVAL;
    }
    timing.hback_porch = hblank - timing.hfront_porch - timing.hsync_len;
    timing.vback_porch = vblank - timing.vfront_porch - timing.vsync_len;
    timing.hsync_active = !!(dtd[17] & RT_BIT(1));
    timing.vsync_active = !!(dtd[17] & RT_BIT(2));
    htotal = (rt_uint64_t)timing.hactive + hblank;
    vtotal = (rt_uint64_t)timing.vactive + vblank;
    if (!timing.pixelclock || !timing.hactive || !timing.vactive ||
        !timing.hsync_len || !timing.vsync_len || timing.hactive > 4096 ||
        timing.vactive > 4096 || htotal > 8192 || vtotal > 4095)
    {
        return -RT_EINVAL;
    }
    timing.htotal = htotal;
    timing.vtotal = vtotal;
    fb->timing = timing;
    return RT_EOK;
}

static void h616_hdmi_hpd_isr(int irq, void *param)
{
    struct h616_fb *fb = param;
    rt_uint8_t status = h616_hdmi_read(fb, HDMI_IH_PHY_STAT0);
    rt_uint8_t events = status & (HDMI_IH_PHY_HPD | HDMI_IH_PHY_RX_SENSE0);

    RT_UNUSED(irq);
    if (!events)
    {
        return;
    }
    if (events & HDMI_IH_PHY_HPD)
    {
        h616_hdmi_update(fb, HDMI_PHY_POL0, HDMI_PHY_HPD,
                         ~h616_hdmi_read(fb, HDMI_PHY_POL0));
    }
    if (events & HDMI_IH_PHY_RX_SENSE0)
    {
        h616_hdmi_update(fb, HDMI_PHY_POL0, HDMI_PHY_RX_SENSE0,
                         ~h616_hdmi_read(fb, HDMI_PHY_POL0));
    }
    fb->hpd = !!(h616_hdmi_read(fb, HDMI_PHY_STAT0) & HDMI_PHY_STAT0_HPD);
    h616_hdmi_write(fb, HDMI_IH_PHY_STAT0, status);
    h616_hdmi_write(fb, HDMI_IH_MUTE_PHY_STAT0,
                    (rt_uint8_t) ~(HDMI_IH_PHY_HPD | HDMI_IH_PHY_RX_SENSE0));
}

static void h616_hdmi_setup_hpd(struct h616_fb *fb)
{
    h616_hdmi_write(fb, HDMI_PHY_POL0, HDMI_PHY_HPD | HDMI_PHY_RX_SENSE0);
    h616_hdmi_write(fb, HDMI_IH_PHY_STAT0,
                    HDMI_IH_PHY_HPD | HDMI_IH_PHY_RX_SENSE0);
    h616_hdmi_write(fb, HDMI_IH_MUTE_PHY_STAT0,
                    (rt_uint8_t) ~(HDMI_IH_PHY_HPD | HDMI_IH_PHY_RX_SENSE0));
    fb->hpd = !!(h616_hdmi_read(fb, HDMI_PHY_STAT0) & HDMI_PHY_STAT0_HPD);
}

static rt_err_t h616_hdmi_phy_write(struct h616_fb *fb, rt_uint16_t value,
                                    rt_uint8_t address)
{
    rt_uint32_t waited;

    h616_hdmi_write(fb, HDMI_IH_I2CMPHY_STAT0, 0xff);
    h616_hdmi_write(fb, HDMI_PHY_I2CM_ADDRESS_ADDR, address);
    h616_hdmi_write(fb, HDMI_PHY_I2CM_DATAO_1_ADDR, value >> 8);
    h616_hdmi_write(fb, HDMI_PHY_I2CM_DATAO_0_ADDR, value);
    h616_hdmi_write(fb, HDMI_PHY_I2CM_OPERATION_ADDR, HDMI_PHY_I2C_WRITE);
    for (waited = 0; waited < 20000; waited += 100)
    {
        rt_uint8_t status = h616_hdmi_read(fb, HDMI_IH_I2CMPHY_STAT0);
        if (status & (HDMI_PHY_I2C_DONE | HDMI_PHY_I2C_ERROR))
        {
            h616_hdmi_write(fb, HDMI_IH_I2CMPHY_STAT0, status);
            return status & HDMI_PHY_I2C_ERROR ? -RT_EIO : RT_EOK;
        }
        rt_hw_us_delay(100);
    }
    return -RT_ETIMEOUT;
}

static rt_err_t h616_hdmi_configure_phy(struct h616_fb *fb)
{
    const struct h616_hdmi_phy_cfg *cfg = RT_NULL;
    const struct sunxi_fb_timing *timing = &fb->timing;
    rt_size_t i;
    struct
    {
        rt_uint16_t value;
        rt_uint8_t reg;
    } writes[8];

    for (i = 0; i < RT_ARRAY_SIZE(h616_hdmi_phy_cfgs); i++)
    {
        if (timing->pixelclock <= h616_hdmi_phy_cfgs[i].max_pixelclock)
        {
            cfg = &h616_hdmi_phy_cfgs[i];
            break;
        }
    }
    if (!cfg)
    {
        return -RT_EINVAL;
    }

    /* H6/H616's external PHY requires its bandgap/reference resistor setup. */
    HWREG32(fb->phy + H616_HDMI_PHY_REXT_CTRL) =
        (HWREG32(fb->phy + H616_HDMI_PHY_REXT_CTRL) & 0x0000ffff) |
        0x80c00000 | H616_HDMI_PHY_REXT_EN;

    h616_hdmi_update(fb, HDMI_PHY_CONF0, HDMI_PHY_TXPWRON | HDMI_PHY_PDDQ,
                     HDMI_PHY_PDDQ);
    h616_hdmi_update(fb, HDMI_PHY_CONF0, HDMI_PHY_SVSRET, HDMI_PHY_SVSRET);
    h616_hdmi_write(fb, HDMI_MC_PHYRSTZ, 1);
    h616_hdmi_write(fb, HDMI_MC_PHYRSTZ, 0);
    h616_hdmi_write(fb, HDMI_MC_HEACPHY_RST, 1);
    h616_hdmi_update(fb, HDMI_PHY_TST0, RT_BIT(5), RT_BIT(5));
    h616_hdmi_write(fb, HDMI_PHY_I2CM_SLAVE_ADDR, HDMI_PHY_I2C_ADDR);
    h616_hdmi_update(fb, HDMI_PHY_TST0, RT_BIT(5), 0);

    writes[0].value = cfg->cpce;
    writes[0].reg = 0x06;
    writes[1].value = cfg->gmp;
    writes[1].reg = 0x15;
    writes[2].value = cfg->curr;
    writes[2].reg = 0x10;
    writes[3].value = 0;
    writes[3].reg = 0x13;
    writes[4].value = 6;
    writes[4].reg = 0x17;
    writes[5].value = cfg->term;
    writes[5].reg = 0x19;
    writes[6].value = cfg->sym;
    writes[6].reg = 0x09;
    writes[7].value = cfg->vlev;
    writes[7].reg = 0x0e;
    for (i = 0; i < RT_ARRAY_SIZE(writes); i++)
    {
        rt_err_t err = h616_hdmi_phy_write(fb, writes[i].value, writes[i].reg);
        if (err)
        {
            return err;
        }
    }
    h616_hdmi_update(fb, HDMI_PHY_CONF0, HDMI_PHY_TXPWRON | HDMI_PHY_PDDQ,
                     HDMI_PHY_TXPWRON);
    for (i = 0; i < 50; i++)
    {
        if (h616_hdmi_read(fb, HDMI_PHY_STAT0) & HDMI_PHY_STAT0_LOCK)
        {
            return RT_EOK;
        }
        rt_hw_us_delay(100);
    }
    return -RT_ETIMEOUT;
}

static void h616_hdmi_program(struct h616_fb *fb)
{
    const struct sunxi_fb_timing *t = &fb->timing;
    rt_uint32_t hblank = t->hfront_porch + t->hsync_len + t->hback_porch;
    rt_uint32_t vblank = t->vfront_porch + t->vsync_len + t->vback_porch;
    rt_uint8_t pol = 0x90 | 0x08;

    if (t->hsync_active)
    {
        pol |= RT_BIT(5);
    }
    if (t->vsync_active)
    {
        pol |= RT_BIT(6);
    }
    h616_hdmi_write(fb, HDMI_TX_INVID0, 1);
    h616_hdmi_write(fb, HDMI_TX_INSTUFFING, 7);
    h616_hdmi_write(fb, HDMI_FC_INVIDCONF, pol);
    h616_hdmi_write(fb, HDMI_FC_INHACTV0, t->hactive);
    h616_hdmi_write(fb, HDMI_FC_INHACTV1, t->hactive >> 8);
    h616_hdmi_write(fb, HDMI_FC_INVACTV0, t->vactive);
    h616_hdmi_write(fb, HDMI_FC_INVACTV1, t->vactive >> 8);
    h616_hdmi_write(fb, HDMI_FC_INHBLANK0, hblank);
    h616_hdmi_write(fb, HDMI_FC_INHBLANK1, hblank >> 8);
    h616_hdmi_write(fb, HDMI_FC_INVBLANK, vblank);
    h616_hdmi_write(fb, HDMI_FC_HSYNCINDELAY0, t->hfront_porch);
    h616_hdmi_write(fb, HDMI_FC_HSYNCINDELAY1, t->hfront_porch >> 8);
    h616_hdmi_write(fb, HDMI_FC_VSYNCINDELAY, t->vfront_porch);
    h616_hdmi_write(fb, HDMI_FC_HSYNCINWIDTH0, t->hsync_len);
    h616_hdmi_write(fb, HDMI_FC_HSYNCINWIDTH1, t->hsync_len >> 8);
    h616_hdmi_write(fb, HDMI_FC_VSYNCINWIDTH, t->vsync_len);
    h616_hdmi_write(fb, HDMI_VP_PR_CD, 0);
    h616_hdmi_write(fb, HDMI_VP_STUFF, 7);
    h616_hdmi_write(fb, HDMI_VP_REMAP, 0);
    h616_hdmi_write(fb, HDMI_VP_CONF, 0x47);
    h616_hdmi_write(fb, HDMI_CSC_CFG, 0);
    h616_hdmi_write(fb, HDMI_FC_CTRLDUR, 12);
    h616_hdmi_write(fb, HDMI_FC_EXCTRLDUR, 32);
    h616_hdmi_write(fb, HDMI_FC_EXCTRLSPAC, 1);
    h616_hdmi_write(fb, HDMI_FC_CH0PREAM, 0x0b);
    h616_hdmi_write(fb, HDMI_FC_CH1PREAM, 0x16);
    h616_hdmi_write(fb, HDMI_FC_CH2PREAM, 0x21);
    h616_hdmi_write(fb, HDMI_MC_FLOWCTRL, 0);
    h616_hdmi_write(fb, HDMI_MC_CLKDIS, 0x7c);
    h616_hdmi_write(fb, HDMI_MC_SWRSTZ, 0xfd);
}

static rt_err_t h616_hdmi_apply_mode(struct h616_fb *fb)
{
    rt_err_t err;

    if ((err = h616_block_set_rate(&fb->tcon, "tcon-ch1",
                                   fb->timing.pixelclock)) ||
        (err = h616_block_set_rate(&fb->hdmi, "tmds",
                                   fb->timing.pixelclock)))
    {
        return err;
    }
    h616_program_de(fb);
    h616_program_tcon(fb);
    if ((err = h616_hdmi_configure_phy(fb)))
    {
        return err;
    }
    h616_hdmi_program(fb);
    return RT_EOK;
}

static void h616_program_de(struct h616_fb *fb)
{
    rt_uint32_t size = (fb->timing.hactive - 1) | ((fb->timing.vactive - 1) << 16);
    rt_size_t i;

    HWREG32(fb->top + DE33_TOP_GLB_CTL) = RT_BIT(0);
    HWREG32(fb->top + DE33_TOP_GLB_CLK) = 1;
    HWREG32(fb->top + DE33_TOP_GLB_SIZE) = size;
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_BKCOLOR) = 0xff000000;
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_FCOLOR0) = 0xff000000;
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_INSIZE0) = size;
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_COORD0) = 0;
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_ROUTE) = 1;
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_PREMULTIPLY) = 0;
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_OUTSIZE) = size;
    for (i = 0; i < 4; i++)
    {
        HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_MODE0 + i * 4) = 0x03010301;
    }
    HWREG32(fb->display + DE33_BLD_BASE + DE33_BLD_PIPE_CTL) = RT_BIT(8);
}

static void h616_program_tcon(struct h616_fb *fb)
{
    const struct sunxi_fb_timing *t = &fb->timing;
    rt_uint32_t hbp = t->hback_porch + t->hsync_len;
    rt_uint32_t vbp = t->vback_porch + t->vsync_len;
    rt_uint32_t pol = RT_BIT(26);
    rt_uint32_t delay;

    if (t->hsync_active)
    {
        pol |= RT_BIT(25);
    }
    if (t->vsync_active)
    {
        pol |= RT_BIT(24);
    }
    HWREG32(fb->tcon.base + TCON1_CTL) = 0;
    HWREG32(fb->tcon.base + TCON1_BASIC0) = (t->hactive - 1) << 16 | (t->vactive - 1);
    HWREG32(fb->tcon.base + TCON1_BASIC1) = (t->hactive - 1) << 16 | (t->vactive - 1);
    HWREG32(fb->tcon.base + TCON1_BASIC2) = (t->hactive - 1) << 16 | (t->vactive - 1);
    HWREG32(fb->tcon.base + TCON1_BASIC3) = (t->htotal - 1) << 16 | (hbp - 1);
    HWREG32(fb->tcon.base + TCON1_BASIC4) = (t->vtotal * 2) << 16 | (vbp - 1);
    HWREG32(fb->tcon.base + TCON1_BASIC5) = (t->hsync_len - 1) << 16 | (t->vsync_len - 1);
    HWREG32(fb->tcon.base + TCON1_IO_POL) = pol;
    HWREG32(fb->tcon.base + TCON1_IO_TRI) = 0;
    HWREG32(fb->tcon.base + TCON_GCTL) = RT_BIT(31) | RT_BIT(0);
    delay = t->vtotal > t->vactive + 2 ? t->vtotal - t->vactive - 2 : 0;
    if (delay > 30)
    {
        delay = 30;
    }
    HWREG32(fb->tcon.base + TCON1_CTL) = RT_BIT(31) | (delay << 4);
}

static void h616_program_plane(struct h616_fb *fb, struct rt_graphic_plane *plane,
                               rt_ubase_t dma)
{
    rt_uint32_t format = h616_de_format(plane->mode);
    rt_uint32_t size = (plane->width - 1) | ((plane->height - 1) << 16);

    HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_SIZE) = size;
    HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_OVL_SIZE) = size;
    HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_COORD) = 0;
    HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_PITCH) = plane->line_length;
    HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_LADDR) = dma;
    HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_HADDR) = 0;
    HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_ATTR) = RT_BIT(0) | (format << 8) | (0xff << 24);
}

static rt_err_t h616_plane_update(struct rt_graphic_plane *plane,
                                  struct rt_device_rect_info *rect)
{
    struct h616_fb *fb = rt_container_of(plane->graphic, struct h616_fb, parent);
    RT_UNUSED(rect);
    if (!plane->framebuffer || !fb->framebuffer_dma)
    {
        return -RT_EINVAL;
    }
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, plane->framebuffer, plane->screen_len);
    h616_program_plane(fb, plane, fb->framebuffer_dma);
    return RT_EOK;
}

static rt_err_t h616_plane_remap(struct rt_graphic_plane *plane, rt_uint32_t mode,
                                 struct rt_device_rect_info *rect)
{
    struct h616_fb *fb = rt_container_of(plane->graphic, struct h616_fb, parent);
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);
    rt_size_t length;
    rt_ubase_t dma;
    void *buffer;

    if (!bpp || rect->width != fb->timing.hactive || rect->height != fb->timing.vactive ||
        h616_de_format(mode) == RT_UINT32_MAX)
    {
        return -RT_EINVAL;
    }
    plane->line_length = RT_ALIGN(rect->width * bpp, 64) / 8;
    length = plane->line_length * rect->height;
    buffer = rt_malloc_align(length, 64);
    if (!buffer)
    {
        return -RT_ENOMEM;
    }
    dma = (rt_ubase_t)rt_kmem_v2p(buffer);
    if ((rt_uint64_t)dma > RT_UINT32_MAX)
    {
        rt_free_align(buffer);
        return -RT_EINVAL;
    }
    rt_memset(buffer, 0, length);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, buffer, length);
    plane->bits_per_pixel = bpp;
    plane->framebuffer = buffer;
    plane->screen_len = length;
    plane->framebuffer_len = length;
    plane->width = rect->width;
    plane->height = rect->height;
    fb->framebuffer_dma = dma;
    h616_program_plane(fb, plane, dma);
    return RT_EOK;
}

static rt_err_t h616_plane_cleanup(struct rt_graphic_plane *plane)
{
    struct h616_fb *fb = rt_container_of(plane->graphic, struct h616_fb, parent);
    if (fb->layer)
    {
        HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_ATTR) = 0;
    }
    if (plane->framebuffer)
    {
        rt_free_align(plane->framebuffer);
    }
    plane->framebuffer = RT_NULL;
    fb->framebuffer_dma = 0;
    return RT_EOK;
}

static const struct rt_graphic_plane_ops h616_plane_ops = {
    .update = h616_plane_update,
    .fb_remap = h616_plane_remap,
    .fb_cleanup = h616_plane_cleanup,
};

static void h616_block_put(struct h616_fb_block *block)
{
    if (block->enabled)
    {
        rt_clk_array_disable_unprepare(block->clks);
    }
    if (!rt_is_err_or_null(block->resets))
    {
        rt_reset_control_put(block->resets);
    }
    if (!rt_is_err_or_null(block->clks))
    {
        rt_clk_array_put(block->clks);
    }
    if (block->base)
    {
        rt_iounmap(block->base);
    }
    if (block->node)
    {
        rt_ofw_node_put(block->node);
    }
    rt_memset(block, 0, sizeof(*block));
}

static rt_err_t h616_block_get(struct h616_fb_block *block, const char *compatible)
{
    rt_err_t err;

    block->node = rt_ofw_find_node_by_compatible(RT_NULL, compatible);
    if (!block->node)
    {
        return -RT_ENOENT;
    }
    if ((err = rt_platform_ofw_request(block->node)))
    {
        goto fail;
    }
    if (!block->node->dev)
    {
        err = -RT_EIO;
        goto fail;
    }
    block->base = rt_ofw_iomap(block->node, 0);
    block->clks = rt_clk_get_array(block->node->dev);
    block->resets = rt_reset_control_get_array(block->node->dev);
    if (!block->base || rt_is_err_or_null(block->clks) || rt_is_err_or_null(block->resets))
    {
        err = -RT_EIO;
        goto fail;
    }
    if ((err = rt_clk_array_prepare_enable(block->clks)))
    {
        goto fail;
    }
    block->enabled = RT_TRUE;
    if ((err = rt_reset_control_deassert(block->resets)))
    {
        goto fail;
    }
    return RT_EOK;
fail:
    h616_block_put(block);
    return err;
}

static rt_err_t h616_block_set_rate(struct h616_fb_block *block,
                                    const char *name, rt_ubase_t rate)
{
    struct rt_clk *clk;
    rt_err_t err;

    clk = rt_clk_get_by_name(block->node->dev, name);
    if (rt_is_err_or_null(clk))
    {
        return clk ? rt_ptr_err(clk) : -RT_ENOENT;
    }
    err = rt_clk_set_rate(clk, rate);
    rt_clk_put(clk);
    return err;
}

static void h616_hw_disable(struct h616_fb *fb)
{
    if (fb->layer)
    {
        HWREG32(fb->layer + DE33_UI0_BASE + DE33_UI_ATTR) = 0;
    }
    if (fb->top)
    {
        HWREG32(fb->top + DE33_TOP_GLB_CTL) = 0;
    }
    if (fb->tcon.base)
    {
        HWREG32(fb->tcon.base + TCON1_CTL) = 0;
        HWREG32(fb->tcon.base + TCON_GCTL) = 0;
    }
    if (fb->hdmi.base)
    {
        h616_hdmi_update(fb, HDMI_PHY_CONF0, HDMI_PHY_TXPWRON | HDMI_PHY_PDDQ, HDMI_PHY_PDDQ);
    }
}

static void h616_resource_put(struct h616_fb *fb)
{
    if (fb->hpd_irq >= 0)
    {
        rt_hw_interrupt_mask(fb->hpd_irq);
        rt_hw_interrupt_uninstall(fb->hpd_irq, h616_hdmi_hpd_isr, fb);
    }
    if (h616_hdmi_active == fb)
    {
        h616_hdmi_active = RT_NULL;
    }
    h616_block_put(&fb->hdmi_phy);
    h616_block_put(&fb->hdmi);
    h616_block_put(&fb->tcon);
    if (!rt_is_err_or_null(fb->mixer_resets))
    {
        rt_reset_control_put(fb->mixer_resets);
    }
    if (!rt_is_err_or_null(fb->mixer_clks))
    {
        rt_clk_array_put(fb->mixer_clks);
    }
    if (fb->display)
    {
        rt_iounmap(fb->display);
    }
    if (fb->top)
    {
        rt_iounmap(fb->top);
    }
    if (fb->layer)
    {
        rt_iounmap(fb->layer);
    }
    if (fb->top_np)
    {
        rt_ofw_node_put(fb->top_np);
    }
}

static rt_err_t h616_fb_probe(struct rt_platform_device *pdev)
{
    struct h616_fb *fb = rt_calloc(1, sizeof(*fb));
    rt_err_t err;
    rt_uint64_t clocks;
    rt_uint32_t refresh;

    if (!fb)
    {
        return -RT_ENOMEM;
    }
    fb->dev = &pdev->parent;
    fb->hpd_irq = -1;
    if ((err = h616_timing_parse(fb)))
    {
        goto fail;
    }
    fb->layer = rt_ofw_iomap(fb->dev->ofw_node, 0);
    fb->top = rt_ofw_iomap(fb->dev->ofw_node, 1);
    fb->display = rt_ofw_iomap(fb->dev->ofw_node, 2);
    fb->mixer_clks = rt_clk_get_array(fb->dev);
    fb->mixer_resets = rt_reset_control_get_array(fb->dev);
    if (!fb->layer || !fb->top || !fb->display || rt_is_err_or_null(fb->mixer_clks) ||
        rt_is_err_or_null(fb->mixer_resets))
    {
        err = -RT_EIO;
        goto fail;
    }
    if ((err = rt_clk_array_prepare_enable(fb->mixer_clks)))
    {
        goto fail;
    }
    fb->mixer_enabled = RT_TRUE;
    if ((err = rt_reset_control_deassert(fb->mixer_resets)))
    {
        goto fail;
    }

    fb->top_np = rt_ofw_find_node_by_compatible(RT_NULL, "allwinner,sun50i-h6-tcon-top");
    if (!fb->top_np)
    {
        err = -RT_ENOENT;
        goto fail;
    }
    if ((err = sunxi_tcon_top_route(fb->top_np, 0, 2, RT_TRUE)))
    {
        goto fail;
    }
    if ((err = h616_block_get(&fb->tcon, "allwinner,sun50i-h6-tcon-tv")))
    {
        goto fail;
    }
    if ((err = h616_block_get(&fb->hdmi, "allwinner,sun50i-h616-dw-hdmi")))
    {
        goto fail;
    }
    if ((err = h616_block_get(&fb->hdmi_phy, "allwinner,sun50i-h616-hdmi-phy")))
    {
        goto fail;
    }
    fb->phy = fb->hdmi_phy.base;
    if ((err = h616_hdmi_apply_mode(fb)))
    {
        LOG_E("HDMI PHY setup failed: %s", rt_strerror(err));
        goto fail;
    }
    h616_hdmi_setup_hpd(fb);
    if (!fb->timing_from_dt && !h616_hdmi_read_edid(fb) &&
        !h616_timing_from_edid(fb) && (err = h616_hdmi_apply_mode(fb)))
    {
        LOG_E("HDMI EDID mode setup failed: %s", rt_strerror(err));
        goto fail;
    }
    fb->hpd_irq = rt_dm_dev_get_irq(fb->hdmi.node->dev, 0);
    if (fb->hpd_irq >= 0)
    {
        rt_hw_interrupt_install(fb->hpd_irq, h616_hdmi_hpd_isr, fb, "hdmi-hpd");
        rt_hw_interrupt_umask(fb->hpd_irq);
    }
    clocks = (rt_uint64_t)fb->timing.htotal * fb->timing.vtotal;
    refresh = clocks ? fb->timing.pixelclock / clocks : 0;
    if ((err = rt_graphic_device_simple_register(&fb->parent, fb->timing.hactive,
                                                 fb->timing.vactive, refresh, &h616_plane_ops, h616_fb_modes,
                                                 RT_ARRAY_SIZE(h616_fb_modes))))
    {
        goto fail;
    }
    if (fb->edid_valid)
    {
        rt_memcpy(&fb->parent.edid, fb->edid, sizeof(fb->edid));
    }
    fb->dev->user_data = fb;
    h616_hdmi_active = fb;
    LOG_I("DE33 HDMI %ux%u@%u, HPD=%u, EDID=%s", fb->timing.hactive,
          fb->timing.vactive, refresh, fb->hpd, fb->edid_valid ? "valid" : "unavailable");
    return RT_EOK;
fail:
    h616_hw_disable(fb);
    if (!rt_is_err_or_null(fb->mixer_resets))
    {
        rt_reset_control_assert(fb->mixer_resets);
    }
    if (fb->mixer_enabled)
    {
        rt_clk_array_disable_unprepare(fb->mixer_clks);
    }
    h616_resource_put(fb);
    rt_free(fb);
    return err;
}

static rt_err_t h616_fb_remove(struct rt_platform_device *pdev)
{
    struct h616_fb *fb = pdev->parent.user_data;
    rt_err_t err;
    if (!fb)
    {
        return RT_EOK;
    }
    if ((err = rt_graphic_device_simple_unregister(&fb->parent)))
    {
        return err;
    }
    if (h616_hdmi_active == fb)
    {
        h616_hdmi_active = RT_NULL;
    }
    h616_hw_disable(fb);
    rt_reset_control_assert(fb->mixer_resets);
    if (fb->mixer_enabled)
    {
        rt_clk_array_disable_unprepare(fb->mixer_clks);
    }
    h616_resource_put(fb);
    rt_free(fb);
    return RT_EOK;
}

static const struct rt_ofw_node_id h616_fb_ids[] = {
    { .compatible = "allwinner,sun50i-h616-de33-mixer-0" },
    {}
};

static struct rt_platform_driver h616_fb_driver = {
    .name = "sun50i-h616-de33",
    .ids = h616_fb_ids,
    .probe = h616_fb_probe,
    .remove = h616_fb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(h616_fb_driver);
