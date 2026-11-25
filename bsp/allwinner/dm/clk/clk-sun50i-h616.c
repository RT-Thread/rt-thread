/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

/* IDs follow the Linux sun50i-h616-ccu binding, including its reserved IDs. */
#define H616_CLK_PLL_PERIPH0     4
#define H616_CLK_CPUX            21
#define H616_CLK_PSI_AHB         24
#define H616_CLK_AHB3            25
#define H616_CLK_APB1            26
#define H616_CLK_APB2            27
#define H616_CLK_UART0           66
#define H616_CLK_TWI0            72
#define H616_CLK_AUDIO_CODEC_1X  91
#define H616_CLK_AUDIO_CODEC_4X  92
#define H616_CLK_BUS_AUDIO_CODEC 93
#define H616_CLK_AUDIO_HUB       94
#define H616_CLK_BUS_AUDIO_HUB   95
#define H616_CLK_COUNT           134
#define H616_RST_UART0           17
#define H616_RST_TWI0            23
#define H616_RST_G2D             64
#define H616_UART_BGR            0x90c
#define H616_TWI_BGR             0x91c

struct h616_ccu
{
    struct rt_clk_node clocks;
    /* Keep OFW clock/reset provider headers adjacent for composite lookup. */
    struct rt_reset_controller resets;
    struct rt_clk_cell *cells[H616_CLK_COUNT];
    struct rt_clk_cell bus_clocks[H616_CLK_COUNT];
    struct rt_spinlock lock;
    void *base;
    struct rt_clk *osc[4];
    rt_ubase_t osc_rate[4];
    rt_bool_t is_r;
};

struct h616_ccu_soc_data
{
    rt_bool_t is_r;
};

static const struct h616_ccu_soc_data h616_ccu_data = { 0 };
static const struct h616_ccu_soc_data h616_r_ccu_data =
{
    .is_r = RT_TRUE,
};

struct h616_clock_desc
{
    const char *name;
    unsigned int id;
};

static const struct h616_clock_desc h616_clock_descs[] = {
    { "h616-pll-periph0", H616_CLK_PLL_PERIPH0 },
    { "h616-cpux", H616_CLK_CPUX },
    { "h616-pll-video0", 9 },
    { "h616-pll-video0-4x", 10 },
    { "h616-pll-video1", 11 },
    { "h616-pll-video1-4x", 12 },
    { "h616-pll-video2", 13 },
    { "h616-pll-video2-4x", 14 },
    { "h616-pll-ve", 15 },
    { "h616-pll-de", 16 },
    { "h616-psi-ahb", H616_CLK_PSI_AHB },
    { "h616-ahb3", H616_CLK_AHB3 },
    { "h616-apb1", H616_CLK_APB1 },
    { "h616-apb2", H616_CLK_APB2 },
    { "h616-de", 29 },
    { "h616-de-bus", 30 },
    { "h616-g2d", 33 },
    { "h616-g2d-bus", 34 },
    { "h616-ce", 38 },
    { "h616-ce-bus", 39 },
    { "h616-ve", 40 },
    { "h616-ve-bus", 41 },
    { "h616-ve-mbus", 51 },
    { "h616-ce-mbus", 52 },
    { "h616-g2d-mbus", 55 },
    { "h616-uart0", H616_CLK_UART0 },
    { "h616-uart1", H616_CLK_UART0 + 1 },
    { "h616-uart2", H616_CLK_UART0 + 2 },
    { "h616-uart3", H616_CLK_UART0 + 3 },
    { "h616-uart4", H616_CLK_UART0 + 4 },
    { "h616-uart5", H616_CLK_UART0 + 5 },
    { "h616-twi0", H616_CLK_TWI0 },
    { "h616-twi1", H616_CLK_TWI0 + 1 },
    { "h616-twi2", H616_CLK_TWI0 + 2 },
    { "h616-twi3", H616_CLK_TWI0 + 3 },
    { "h616-twi4", H616_CLK_TWI0 + 4 },
    { "h616-pwm-bus", 47 },
    { "h616-spi0", 77 },
    { "h616-spi1", 78 },
    { "h616-spi0-bus", 79 },
    { "h616-spi1-bus", 80 },
    { "h616-dma-bus", 42 },
    { "h616-dma-mbus", 50 },
    { "h616-mmc0", 60 },
    { "h616-mmc1", 61 },
    { "h616-mmc2", 62 },
    { "h616-mmc0-bus", 63 },
    { "h616-mmc1-bus", 64 },
    { "h616-mmc2-bus", 65 },
    { "h616-audio-codec-1x", H616_CLK_AUDIO_CODEC_1X },
    { "h616-audio-codec-4x", H616_CLK_AUDIO_CODEC_4X },
    { "h616-audio-codec-bus", H616_CLK_BUS_AUDIO_CODEC },
    { "h616-audio-hub", H616_CLK_AUDIO_HUB },
    { "h616-audio-hub-bus", H616_CLK_BUS_AUDIO_HUB },
    { "h616-emac0-bus", 82 },
    { "h616-emac1-bus", 83 },
    { "h616-ths-bus", 86 },
    { "h616-gpadc-bus", 129 },
    { "h616-keyadc-bus", 113 },
    { "h616-hdmi", 114 },
    { "h616-hdmi-slow", 115 },
    { "h616-hdmi-cec", 116 },
    { "h616-hdmi-bus", 117 },
    { "h616-tcon-top-bus", 118 },
    { "h616-tcon-tv0", 119 },
    { "h616-tcon-tv1", 120 },
    { "h616-tcon-tv0-bus", 121 },
    { "h616-tcon-tv1-bus", 122 },
    { "h616-hdcp", 126 },
    { "h616-hdcp-bus", 127 },
    { "h616-pll-32k", 128 },
};

static const struct h616_clock_desc h616_r_clock_descs[] = {
    { "h616-r-ahb", 1 },
    { "h616-r-apb1", 2 },
    { "h616-r-apb2", 3 },
    { "h616-r-twd", 5 },
    { "h616-r-i2c", 8 },
    { "h616-r-ir-bus", 9 },
    { "h616-r-ir", 11 },
    { "h616-r-rsb", 13 },
    { "h616-r-rtc", 14 },
};

static rt_ubase_t h616_nmp_rate(struct h616_ccu *ccu, unsigned int reg)
{
    rt_uint32_t v = HWREG32(ccu->base + reg);

    if (!(v & RT_BIT(31)))
    {
        return 0;
    }
    return ccu->osc_rate[0] * (((v >> 8) & 255) + 1) /
           ((((v >> 1) & 1) + 1) * ((v & 1) + 1));
}

static rt_ubase_t h616_mmc_parent(struct h616_ccu *ccu, unsigned int mux)
{
    return mux == 0 ? ccu->osc_rate[0] : (mux < 3 ? h616_nmp_rate(ccu, mux == 1 ? 0x20 : 0x28) : 0);
}

static rt_ubase_t h616_r_bus_rate(struct h616_ccu *ccu, unsigned int reg)
{
    rt_uint32_t v = HWREG32(ccu->base + reg);
    rt_uint32_t mux = (v >> 24) & 3;
    rt_ubase_t rate = ccu->osc_rate[mux];

    if (mux == 3)
    {
        rate /= (v & 31) + 1;
    }
    return rate / RT_BIT((v >> 8) & 3);
}

static rt_ubase_t h616_pll_rate(struct h616_ccu *ccu)
{
    rt_uint32_t value = HWREG32(ccu->base + 0x20);

    if (!(value & RT_BIT(31)))
    {
        return 0;
    }

    /* N is encoded as N-1; M and P are one-bit linear dividers. */
    return ccu->osc_rate[0] * (((value >> 8) & 0xff) + 1) /
           (2 * (((value >> 1) & 1) + 1) * ((value & 1) + 1));
}

static rt_ubase_t h616_cpux_rate(struct h616_ccu *ccu)
{
    rt_uint32_t value = HWREG32(ccu->base + 0x500);

    switch ((value >> 24) & 7)
    {
    case 0:
        return ccu->osc_rate[0];
    case 1:
        return ccu->osc_rate[1];
    case 2:
        return ccu->osc_rate[2];
    case 3:
        value = HWREG32(ccu->base);
        return (value & RT_BIT(31)) ? ccu->osc_rate[0] * (((value >> 8) & 0xff) + 1) : 0;
    case 4:
        return h616_pll_rate(ccu);
    default:
        return 0;
    }
}

static rt_ubase_t h616_bus_rate(struct h616_ccu *ccu, unsigned int reg)
{
    rt_uint32_t value = HWREG32(ccu->base + reg);
    rt_uint32_t mux = (value >> 24) & 3;
    rt_ubase_t rate;

    if (mux == 3)
    {
        rate = h616_pll_rate(ccu);
    }
    else if (mux == 2 && reg != 0x510)
    {
        rate = h616_bus_rate(ccu, 0x510);
    }
    else
    {
        rate = ccu->osc_rate[mux];
    }

    return rate / ((value & 3) + 1) / RT_BIT((value >> 8) & 3);
}

static rt_ubase_t h616_audio_pll_rate(struct h616_ccu *ccu)
{
    rt_uint32_t pattern = HWREG32(ccu->base + 0x178);

    if (!(HWREG32(ccu->base + 0x78) & RT_BIT(31)))
    {
        return 0;
    }
    if (pattern == 0xc001288d)
    {
        return 90316800;
    }
    if (pattern == 0xc001eb85)
    {
        return 98304000;
    }

    return 0;
}

static rt_ubase_t h616_audio_module_rate(struct h616_ccu *ccu,
                                         unsigned int reg)
{
    rt_uint32_t value = HWREG32(ccu->base + reg);
    rt_ubase_t parent = h616_audio_pll_rate(ccu);

    switch ((value >> 24) & 3)
    {
    case 0:
        parent /= 4;
        break;
    case 1:
        parent /= 2;
        break;
    default:
        break;
    }

    return parent / ((value & 15) + 1);
}

static rt_ubase_t h616_periph_parent_rate(struct h616_ccu *ccu,
                                          unsigned int mux)
{
    switch (mux)
    {
    case 0:
        return ccu->osc_rate[0];
    case 1:
        return h616_pll_rate(ccu);
    case 3:
        return h616_pll_rate(ccu) * 2;
    default:
        /* PLL_PERIPH1 is not modelled because firmware owns it. */
        return 0;
    }
}

static rt_ubase_t h616_mp_rate(struct h616_ccu *ccu, unsigned int reg)
{
    rt_uint32_t value = HWREG32(ccu->base + reg);
    rt_ubase_t parent = h616_periph_parent_rate(ccu, (value >> 24) & 7);

    return parent / ((value & 15) + 1) / RT_BIT((value >> 8) & 3);
}

static rt_ubase_t h616_mp_find_rate(struct h616_ccu *ccu,
                                    rt_ubase_t requested, rt_uint32_t *value)
{
    rt_ubase_t best = 0;
    unsigned int mux;
    unsigned int m;
    unsigned int n;

    for (mux = 0; mux < 4; ++mux)
    {
        rt_ubase_t parent = h616_periph_parent_rate(ccu, mux);

        if (!parent)
        {
            continue;
        }
        for (m = 0; m < 16; ++m)
        {
            for (n = 0; n < 4; ++n)
            {
                rt_ubase_t rate = parent / (m + 1) / RT_BIT(n);

                if (rate <= requested && rate > best)
                {
                    best = rate;
                    *value = (mux << 24) | (n << 8) | m;
                }
            }
        }
    }

    return best;
}

struct h616_display_clock
{
    unsigned int id;
    unsigned int reg;
    unsigned int mux_width;
    unsigned int p_width;
    unsigned int parents;
};

static const struct h616_display_clock h616_display_clocks[] = {
    { 29, 0x600, 1, 0, 2 },
    { 114, 0xb00, 2, 0, 4 },
    { 119, 0xb80, 3, 2, 4 },
    { 120, 0xb84, 3, 2, 4 },
    { 126, 0xc40, 2, 0, 2 },
};

static const struct h616_display_clock *h616_display_clock(unsigned int id)
{
    rt_size_t i;

    for (i = 0; i < RT_ARRAY_SIZE(h616_display_clocks); ++i)
    {
        if (h616_display_clocks[i].id == id)
        {
            return &h616_display_clocks[i];
        }
    }
    return RT_NULL;
}

static rt_ubase_t h616_video_rate(struct h616_ccu *ccu, unsigned int index,
                                  rt_bool_t four_x)
{
    /* Include the test output divider when inheriting firmware settings. */
    return h616_nmp_rate(ccu, 0x40 + index * 8) / (four_x ? 1 : 4);
}

static rt_ubase_t h616_display_parent(struct h616_ccu *ccu,
                                      const struct h616_display_clock *clock, unsigned int mux)
{
    if (mux >= clock->parents)
    {
        return 0;
    }
    if (clock->id == 29)
    {
        return h616_nmp_rate(ccu, mux ? 0x20 : 0x60);
    }
    if (clock->id == 126)
    {
        return h616_nmp_rate(ccu, mux ? 0x28 : 0x20) / 2;
    }
    return h616_video_rate(ccu, mux < 2 ? 0 : (clock->id == 114 ? 2 : 1), mux & 1);
}

static rt_ubase_t h616_display_rate(struct h616_ccu *ccu,
                                    const struct h616_display_clock *clock)
{
    rt_uint32_t value = HWREG32(ccu->base + clock->reg);
    unsigned int mux = (value >> 24) & (RT_BIT(clock->mux_width) - 1);
    unsigned int p = (value >> 8) & (RT_BIT(clock->p_width) - 1);

    return h616_display_parent(ccu, clock, mux) / ((value & 15) + 1) / RT_BIT(p);
}

static rt_ubase_t h616_display_find_rate(struct h616_ccu *ccu,
                                         const struct h616_display_clock *clock, rt_ubase_t requested,
                                         rt_uint32_t *value)
{
    rt_ubase_t best = 0;
    unsigned int mux, m, p;

    /* Only use live firmware PLLs; do not retune a shared parent implicitly. */
    for (mux = 0; mux < clock->parents; ++mux)
    {
        for (m = 0; m < 16; ++m)
        {
            for (p = 0; p < RT_BIT(clock->p_width); ++p)
            {
                rt_ubase_t rate = h616_display_parent(ccu, clock, mux) / (m + 1) / RT_BIT(p);

                if (rate <= requested && rate > best)
                {
                    best = rate;
                    *value = (mux << 24) | (p << 8) | m;
                }
            }
        }
    }
    return best;
}

static rt_ubase_t h616_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct h616_ccu *ccu = cell->clk_np->priv;
    const struct h616_clock_desc *desc = cell->priv;
    const struct h616_display_clock *display;

    if (ccu->is_r)
    {
        if (desc->id == 3 || desc->id == 8 || desc->id == 13)
        {
            return h616_r_bus_rate(ccu, 0x10);
        }
        if (desc->id == 11)
        {
            rt_uint32_t v = HWREG32(ccu->base + 0x1c0);
            rt_ubase_t rate = ccu->osc_rate[((v >> 24) & 1) ? 0 : 1];
            return rate / ((v & 31) + 1) / RT_BIT((v >> 8) & 3);
        }
        return h616_r_bus_rate(ccu, 0) /
               (desc->id == 1 ? 1 : ((HWREG32(ccu->base + 0xc) & 3) + 1));
    }
    display = h616_display_clock(desc->id);
    if (display)
    {
        return h616_display_rate(ccu, display);
    }
    if (desc->id >= 9 && desc->id <= 14)
    {
        return h616_video_rate(ccu, (desc->id - 9) / 2, !(desc->id & 1));
    }
    if (desc->id == 15 || desc->id == 16)
    {
        return h616_nmp_rate(ccu, desc->id == 15 ? 0x58 : 0x60);
    }
    if (desc->id == H616_CLK_CPUX)
    {
        return h616_cpux_rate(ccu);
    }
    if (desc->id == 115)
    {
        return ccu->osc_rate[0];
    }
    if (desc->id == 116)
    {
        unsigned int mux = (HWREG32(ccu->base + 0xb10) >> 24) & 3;

        return mux == 0 ? ccu->osc_rate[1] : (mux == 1 ? h616_nmp_rate(ccu, 0x20) / 36621 : 0);
    }
    if (desc->id == H616_CLK_AUDIO_CODEC_1X)
    {
        return h616_audio_module_rate(ccu, 0xa50);
    }
    if (desc->id == H616_CLK_AUDIO_CODEC_4X)
    {
        return h616_audio_module_rate(ccu, 0xa54);
    }
    if (desc->id == H616_CLK_AUDIO_HUB)
    {
        return h616_audio_module_rate(ccu, 0xa60);
    }
    if (desc->id == 30)
    {
        return h616_bus_rate(ccu, 0x510);
    }
    if (desc->id == 117 || desc->id == 118 || desc->id == 121 ||
        desc->id == 122 || desc->id == 127)
    {
        return h616_bus_rate(ccu, 0x51c);
    }
    if (desc->id >= 60 && desc->id <= 62)
    {
        rt_uint32_t v = HWREG32(ccu->base + 0x830 + (desc->id - 60) * 4);
        return h616_mmc_parent(ccu, (v >> 24) & 3) /
               (2 * ((v & 15) + 1) * RT_BIT((v >> 8) & 3));
    }
    if (desc->id == 128)
    {
        return h616_pll_rate(ccu) * 2 / 36621;
    }
    if ((desc->id >= 63 && desc->id <= 65) || desc->id == 82 || desc->id == 83)
    {
        return h616_bus_rate(ccu, 0x51c);
    }
    if (desc->id == 42)
    {
        return h616_bus_rate(ccu, 0x510);
    }
    if (desc->id == 86)
    {
        return h616_bus_rate(ccu, 0x520);
    }
    if (desc->id == 50)
    {
        rt_uint32_t v = HWREG32(ccu->base + 0x540);
        unsigned int mux = (v >> 24) & 3;
        rt_ubase_t rate = mux == 0 ? ccu->osc_rate[0] : h616_nmp_rate(ccu, mux == 1 ? 0x20 : (mux == 2 ? 0x10 : 0x18));
        return rate / ((v & 7) + 1);
    }
    if (desc->id == 77 || desc->id == 78 || desc->id == 38)
    {
        return h616_mp_rate(ccu, desc->id == 77 ? 0x940 : desc->id == 78 ? 0x944
                                                                         : 0x680);
    }
    if (desc->id == 33)
    {
        return h616_periph_parent_rate(ccu,
                                       (HWREG32(ccu->base + 0x630) >> 24) & 1) /
               ((HWREG32(ccu->base + 0x630) & 15) + 1);
    }
    if (desc->id == 40)
    {
        return h616_nmp_rate(ccu, 0x58) /
               ((HWREG32(ccu->base + 0x690) & 7) + 1);
    }

    switch (desc->id)
    {
    case H616_CLK_PLL_PERIPH0:
        return h616_pll_rate(ccu);
    case H616_CLK_PSI_AHB:
        return h616_bus_rate(ccu, 0x510);
    case H616_CLK_AHB3:
        return h616_bus_rate(ccu, 0x51c);
    case H616_CLK_APB1:
        return h616_bus_rate(ccu, 0x520);
    default:
        return h616_bus_rate(ccu, 0x524);
    }
}

static rt_bool_t h616_gate(unsigned int id, unsigned int *reg, unsigned int *bit)
{
    const struct h616_display_clock *display = h616_display_clock(id);

    if (display)
    {
        *reg = display->reg;
        *bit = 31;
        return RT_TRUE;
    }
    switch (id)
    {
    case 15:
        *reg = 0x58;
        *bit = 31;
        return RT_TRUE;
    case 30:
        *reg = 0x60c;
        *bit = 0;
        return RT_TRUE;
    case 33:
        *reg = 0x630;
        *bit = 31;
        return RT_TRUE;
    case 34:
        *reg = 0x63c;
        *bit = 0;
        return RT_TRUE;
    case 38:
        *reg = 0x680;
        *bit = 31;
        return RT_TRUE;
    case 39:
        *reg = 0x68c;
        *bit = 0;
        return RT_TRUE;
    case 40:
        *reg = 0x690;
        *bit = 31;
        return RT_TRUE;
    case 41:
        *reg = 0x69c;
        *bit = 0;
        return RT_TRUE;
    case 47:
        *reg = 0x7ac;
        *bit = 0;
        return RT_TRUE;
    case 51:
        *reg = 0x804;
        *bit = 1;
        return RT_TRUE;
    case 52:
        *reg = 0x804;
        *bit = 2;
        return RT_TRUE;
    case 55:
        *reg = 0x804;
        *bit = 10;
        return RT_TRUE;
    case 77:
        *reg = 0x940;
        *bit = 31;
        return RT_TRUE;
    case 78:
        *reg = 0x944;
        *bit = 31;
        return RT_TRUE;
    case 79:
        *reg = 0x96c;
        *bit = 0;
        return RT_TRUE;
    case 80:
        *reg = 0x96c;
        *bit = 1;
        return RT_TRUE;
    case 129:
        *reg = 0x9ec;
        *bit = 0;
        return RT_TRUE;
    case 113:
        *reg = 0xa9c;
        *bit = 0;
        return RT_TRUE;
    case H616_CLK_AUDIO_CODEC_1X:
        *reg = 0xa50;
        *bit = 31;
        return RT_TRUE;
    case H616_CLK_AUDIO_CODEC_4X:
        *reg = 0xa54;
        *bit = 31;
        return RT_TRUE;
    case H616_CLK_BUS_AUDIO_CODEC:
        *reg = 0xa5c;
        *bit = 0;
        return RT_TRUE;
    case H616_CLK_AUDIO_HUB:
        *reg = 0xa60;
        *bit = 31;
        return RT_TRUE;
    case H616_CLK_BUS_AUDIO_HUB:
        *reg = 0xa6c;
        *bit = 0;
        return RT_TRUE;
    case 115:
        *reg = 0xb04;
        *bit = 31;
        return RT_TRUE;
    case 116:
        *reg = 0xb10;
        *bit = 31;
        return RT_TRUE;
    case 117:
        *reg = 0xb1c;
        *bit = 0;
        return RT_TRUE;
    case 118:
        *reg = 0xb5c;
        *bit = 0;
        return RT_TRUE;
    case 121:
        *reg = 0xb9c;
        *bit = 0;
        return RT_TRUE;
    case 122:
        *reg = 0xb9c;
        *bit = 1;
        return RT_TRUE;
    case 127:
        *reg = 0xc4c;
        *bit = 0;
        return RT_TRUE;
    }
    if (id == 42 || id == 50 || id == 86 || id == 82 || id == 83)
    {
        *reg = id == 42 ? 0x70c : id == 50 ? 0x804
                              : id == 86   ? 0x9fc
                                           : 0x97c;
        *bit = id == 83 ? 1 : 0;
        return RT_TRUE;
    }
    if (id >= 60 && id <= 65)
    {
        *reg = id < 63 ? 0x830 + (id - 60) * 4 : 0x84c;
        *bit = id < 63 ? 31 : id - 63;
        return RT_TRUE;
    }
    if (id >= H616_CLK_UART0 && id < H616_CLK_UART0 + 6)
    {
        *reg = H616_UART_BGR;
        *bit = id - H616_CLK_UART0;
        return RT_TRUE;
    }
    if (id >= H616_CLK_TWI0 && id < H616_CLK_TWI0 + 5)
    {
        *reg = H616_TWI_BGR;
        *bit = id - H616_CLK_TWI0;
        return RT_TRUE;
    }
    return RT_FALSE;
}

static rt_bool_t h616_r_gate(unsigned int id, unsigned int *reg, unsigned int *bit)
{
    *bit = 0;
    switch (id)
    {
    case 5:
        *reg = 0x12c;
        return RT_TRUE;
    case 8:
        *reg = 0x19c;
        return RT_TRUE;
    case 9:
        *reg = 0x1cc;
        return RT_TRUE;
    case 11:
        *reg = 0x1c0;
        *bit = 31;
        return RT_TRUE;
    case 13:
        *reg = 0x1bc;
        return RT_TRUE;
    case 14:
        *reg = 0x20c;
        return RT_TRUE;
    default:
        return RT_FALSE;
    }
}

static void h616_update(struct h616_ccu *ccu, unsigned int reg,
                        unsigned int bit, rt_bool_t set)
{
    rt_base_t level = rt_spin_lock_irqsave(&ccu->lock);
    rt_uint32_t value = HWREG32(ccu->base + reg);

    HWREG32(ccu->base + reg) = set ? value | RT_BIT(bit) : value & ~RT_BIT(bit);
    rt_spin_unlock_irqrestore(&ccu->lock, level);
}

static rt_err_t h616_display_parent_enable(struct h616_ccu *ccu,
                                           const struct h616_display_clock *display)
{
    unsigned int mux, reg, n, waited;
    rt_uint32_t before, value;
    rt_base_t level;

    mux = (HWREG32(ccu->base + display->reg) >> 24) &
          (RT_BIT(display->mux_width) - 1);
    if (mux >= display->parents)
    {
        return -RT_EINVAL;
    }
    if (display->id == 126 || (display->id == 29 && mux == 1))
    {
        /* Peripheral PLLs are shared with storage and other running devices. */
        return h616_display_parent(ccu, display, mux) ? RT_EOK : -RT_EIO;
    }
    if (ccu->osc_rate[0] != 24000000)
    {
        return -RT_EINVAL;
    }
    if (display->id == 29)
    {
        reg = 0x60;
        n = 24; /* 600 MHz DE clock. */
    }
    else
    {
        reg = 0x40 + (mux / 2) * (display->id == 114 ? 16 : 8);
        n = 98; /* 2376 MHz VCO, 594 MHz after the fixed /4. */
    }
    level = rt_spin_lock_irqsave(&ccu->lock);
    before = HWREG32(ccu->base + reg);
    value = before;
    if (!(value & RT_BIT(31)))
    {
        value = (value & ~((255U << 8) | 3U)) | (n << 8);
    }
    /* Enable lock detection and the output gate, as required by H616 CCU. */
    HWREG32(ccu->base + reg) = value | RT_BIT(31) | RT_BIT(29) | RT_BIT(27);
    rt_spin_unlock_irqrestore(&ccu->lock, level);
    for (waited = 0; waited < 10000; ++waited)
    {
        if (HWREG32(ccu->base + reg) & RT_BIT(28))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(1);
    }
    level = rt_spin_lock_irqsave(&ccu->lock);
    HWREG32(ccu->base + reg) = before;
    rt_spin_unlock_irqrestore(&ccu->lock, level);
    return -RT_ETIMEOUT;
}

static rt_err_t h616_enable(struct rt_clk_cell *cell)
{
    struct h616_ccu *ccu = cell->clk_np->priv;
    const struct h616_clock_desc *desc = cell->priv;
    unsigned int reg, bit;

    if (!ccu->is_r)
    {
        const struct h616_display_clock *display = h616_display_clock(desc->id);
        rt_err_t err;

        if (display && (err = h616_display_parent_enable(ccu, display)))
        {
            return err;
        }
    }

    if (!ccu->is_r && desc->id == 116)
    {
        rt_base_t level;

        /* OSC32K is not usable by CEC on H616; use PERIPH0-2X / 36621. */
        if (!h616_nmp_rate(ccu, 0x20))
        {
            return -RT_EIO;
        }
        level = rt_spin_lock_irqsave(&ccu->lock);
        HWREG32(ccu->base + 0xb10) = (HWREG32(ccu->base + 0xb10) & ~(3U << 24)) |
                                     RT_BIT(24) | RT_BIT(30) | RT_BIT(31);
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return RT_EOK;
    }

    if (!ccu->is_r && desc->id == 15)
    {
        h616_update(ccu, 0x58, 31, RT_TRUE);
        return h616_nmp_rate(ccu, 0x58) ? RT_EOK : -RT_EIO;
    }

    /* VE is clocked solely from PLL-VE, which firmware commonly leaves off. */
    if (!ccu->is_r && desc->id == 40)
    {
        h616_update(ccu, 0x58, 31, RT_TRUE);
    }

    if (!h616_recalc_rate(cell, 0))
    {
        return -RT_EIO;
    }
    if (ccu->is_r ? h616_r_gate(desc->id, &reg, &bit) : h616_gate(desc->id, &reg, &bit))
    {
        h616_update(cell->clk_np->priv, reg, bit, RT_TRUE);
    }
    return RT_EOK;
}

static void h616_disable(struct rt_clk_cell *cell)
{
    struct h616_ccu *ccu = cell->clk_np->priv;
    const struct h616_clock_desc *desc = cell->priv;
    unsigned int reg, bit;

    if (ccu->is_r ? h616_r_gate(desc->id, &reg, &bit) : h616_gate(desc->id, &reg, &bit))
    {
        h616_update(cell->clk_np->priv, reg, bit, RT_FALSE);
        if (!ccu->is_r && desc->id == 116)
        {
            h616_update(ccu, reg, 30, RT_FALSE);
        }
    }
}

static rt_ubase_t h616_mmc_find_rate(struct h616_ccu *ccu, rt_ubase_t requested,
                                     rt_uint32_t *value)
{
    rt_ubase_t best = 0;
    unsigned int mux, m, p;

    for (mux = 0; mux < 3; ++mux)
    {
        for (m = 0; m < 16; ++m)
        {
            for (p = 0; p < 4; ++p)
            {
                rt_ubase_t rate = h616_mmc_parent(ccu, mux) / (2 * (m + 1) * RT_BIT(p));
                if (rate <= requested && rate > best)
                {
                    best = rate;
                    *value = (mux << 24) | (p << 8) | m;
                }
            }
        }
    }
    return best;
}

static rt_base_t h616_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate,
                                 rt_ubase_t *parent_rate)
{
    struct h616_ccu *ccu = cell->clk_np->priv;
    const struct h616_clock_desc *desc = cell->priv;
    rt_uint32_t value;
    const struct h616_display_clock *display = h616_display_clock(desc->id);

    if (ccu->is_r && desc->id == 11)
    {
        return rate == 8000000 && ccu->osc_rate[0] == 24000000 ? rate : h616_recalc_rate(cell, 0);
    }
    if (!ccu->is_r && desc->id == H616_CLK_CPUX)
    {
        /* PLL_CPUX is an integer multiple of the 24 MHz oscillator. */
        if (rate >= 216000000 && rate <= 1512000000 &&
            !(rate % ccu->osc_rate[0]))
        {
            return rate;
        }
        return -RT_EINVAL;
    }
    if (!ccu->is_r && display)
    {
        if (rate && h616_display_find_rate(ccu, display, rate, &value) == rate)
        {
            return rate;
        }
        return -RT_EINVAL;
    }

    if (!ccu->is_r && desc->id >= 60 && desc->id <= 62)
    {
        return h616_mmc_find_rate(ccu, rate, &value);
    }
    if (!ccu->is_r && (desc->id == 77 || desc->id == 78 || desc->id == 38))
    {
        return h616_mp_find_rate(ccu, rate, &value);
    }
    return h616_recalc_rate(cell, 0);
}

static rt_err_t h616_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate,
                              rt_ubase_t parent_rate)
{
    struct h616_ccu *ccu = cell->clk_np->priv;
    const struct h616_clock_desc *desc = cell->priv;
    rt_uint32_t value;
    rt_base_t level;
    void *reg;
    const struct h616_display_clock *display = h616_display_clock(desc->id);

    if (!ccu->is_r && desc->id == H616_CLK_CPUX)
    {
        rt_uint32_t old_pll;
        rt_uint32_t old_cpux;
        rt_uint32_t pll;
        rt_uint32_t cpux;
        rt_uint32_t n;
        unsigned int waited;

        if (!rate || rate % ccu->osc_rate[0])
        {
            return -RT_EINVAL;
        }
        n = rate / ccu->osc_rate[0];
        if (n < 9 || n > 63)
        {
            return -RT_EINVAL;
        }

        /*
         * The H616 CPU clock must leave PLL_CPUX while that PLL is
         * retuned.  Linux uses PLL_PERIPH0 (mux value 4) as this bypass
         * parent; it is already required by the running system and keeps
         * every CPU executing from a stable 600 MHz source.
         */
        reg = ccu->base + 0x500;
        level = rt_spin_lock_irqsave(&ccu->lock);
        old_cpux = HWREG32(reg);
        old_pll = HWREG32(ccu->base);
        cpux = (old_cpux & ~(7U << 24)) | (4U << 24);
        HWREG32(reg) = cpux;
        rt_hw_dsb();
        rt_hw_isb();

        /* M is a factory-test field and must remain zero on H616. */
        pll = (old_pll & ~((0xffU << 8) | RT_BIT(1))) |
              ((n - 1) << 8) | RT_BIT(31) | RT_BIT(29);
        HWREG32(ccu->base) = pll;
        rt_spin_unlock_irqrestore(&ccu->lock, level);

        for (waited = 0; waited < 10000; ++waited)
        {
            if (HWREG32(ccu->base) & RT_BIT(28))
            {
                break;
            }
            rt_hw_us_delay(1);
        }

        level = rt_spin_lock_irqsave(&ccu->lock);
        if (waited == 10000)
        {
            HWREG32(ccu->base) = old_pll;
            HWREG32(reg) = old_cpux;
            rt_spin_unlock_irqrestore(&ccu->lock, level);
            return -RT_ETIMEOUT;
        }
        HWREG32(reg) = (cpux & ~(7U << 24)) | (3U << 24);
        rt_hw_dsb();
        rt_hw_isb();
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return RT_EOK;
    }

    if (ccu->is_r && desc->id == 11 && rate == 8000000 &&
        ccu->osc_rate[0] == 24000000)
    {
        reg = ccu->base + 0x1c0;
        level = rt_spin_lock_irqsave(&ccu->lock);
        HWREG32(reg) = (HWREG32(reg) & ~((1U << 24) | (3U << 8) | 31U)) |
                       RT_BIT(24) | 2;
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return RT_EOK;
    }
    if (!ccu->is_r && display)
    {
        rt_uint32_t mask = ((RT_BIT(display->mux_width) - 1) << 24) |
                           ((RT_BIT(display->p_width) - 1) << 8) | 15;

        /* Pixel clocks must not silently become a lower refresh rate. */
        if (!rate || h616_display_find_rate(ccu, display, rate, &value) != rate)
        {
            return -RT_EINVAL;
        }
        reg = ccu->base + display->reg;
        level = rt_spin_lock_irqsave(&ccu->lock);
        HWREG32(reg) = (HWREG32(reg) & ~mask) | value;
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return RT_EOK;
    }

    if (!ccu->is_r && (desc->id == H616_CLK_AUDIO_CODEC_1X ||
                       desc->id == H616_CLK_AUDIO_CODEC_4X ||
                       desc->id == H616_CLK_AUDIO_HUB))
    {
        rt_uint32_t pll;
        rt_uint32_t pattern;
        rt_uint32_t divider;

        switch (rate)
        {
        case 22579200:
            pll = (22U << 8) | (3U << 16);
            pattern = 0xc001288d;
            divider = 3;
            break;
        case 24576000:
            pll = (40U << 8) | (5U << 16);
            pattern = 0xc001eb85;
            divider = 3;
            break;
        case 45158400:
            pll = (22U << 8) | (3U << 16);
            pattern = 0xc001288d;
            divider = 1;
            break;
        case 49152000:
            pll = (40U << 8) | (5U << 16);
            pattern = 0xc001eb85;
            divider = 1;
            break;
        default:
            return -RT_EINVAL;
        }

        /* PLL_AUDIO_4X feeds codec and AHUB clocks through their own dividers. */
        level = rt_spin_lock_irqsave(&ccu->lock);
        HWREG32(ccu->base + 0x178) = pattern;
        HWREG32(ccu->base + 0x78) = pll | RT_BIT(31) | RT_BIT(24) | RT_BIT(0);
        reg = ccu->base + (desc->id == H616_CLK_AUDIO_CODEC_1X ? 0xa50 :
                           desc->id == H616_CLK_AUDIO_CODEC_4X ? 0xa54 : 0xa60);
        HWREG32(reg) = divider | (2U << 24) | RT_BIT(31);
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return RT_EOK;
    }

    if (!ccu->is_r && (desc->id == 77 || desc->id == 78 || desc->id == 38))
    {
        unsigned int offset = desc->id == 77 ? 0x940 : desc->id == 78 ? 0x944
                                                                      : 0x680;

        if (!rate || !h616_mp_find_rate(ccu, rate, &value))
        {
            return -RT_EINVAL;
        }
        reg = ccu->base + offset;
        level = rt_spin_lock_irqsave(&ccu->lock);
        HWREG32(reg) = (HWREG32(reg) & ~((7U << 24) | (3U << 8) | 15U)) |
                       value;
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return RT_EOK;
    }

    if (ccu->is_r || desc->id < 60 || desc->id > 62)
    {
        return rate == h616_recalc_rate(cell, 0) ? RT_EOK : -RT_ENOSYS;
    }
    if (!h616_mmc_find_rate(ccu, rate, &value))
    {
        return -RT_EINVAL;
    }
    reg = ccu->base + 0x830 + (desc->id - 60) * 4;
    level = rt_spin_lock_irqsave(&ccu->lock);
    HWREG32(reg) = (HWREG32(reg) & ~((3U << 24) | (3U << 8) | 15U)) | value;
    rt_spin_unlock_irqrestore(&ccu->lock, level);
    return RT_EOK;
}

static const struct rt_clk_ops h616_clk_ops = {
    .enable = h616_enable,
    .disable = h616_disable,
    .recalc_rate = h616_recalc_rate,
    .round_rate = h616_round_rate,
    .set_rate = h616_set_rate,
};

static rt_bool_t h616_reset_line(int id, unsigned int *reg, unsigned int *bit)
{
    *bit = 16;
    switch (id)
    {
    case H616_RST_G2D:
        *reg = 0x63c;
        return RT_TRUE;
    case 1:
        *reg = 0x60c;
        return RT_TRUE;
    case 2:
        *reg = 0x62c;
        return RT_TRUE;
    case 4:
        *reg = 0x68c;
        return RT_TRUE;
    case 5:
        *reg = 0x69c;
        return RT_TRUE;
    case 10:
        *reg = 0x7ac;
        return RT_TRUE;
    case 51:
        *reg = 0xb1c;
        return RT_TRUE;
    case 52:
        *reg = 0xb1c;
        *bit = 17;
        return RT_TRUE;
    case 53:
        *reg = 0xb5c;
        return RT_TRUE;
    case 54:
        *reg = 0xb9c;
        return RT_TRUE;
    case 55:
        *reg = 0xb9c;
        *bit = 17;
        return RT_TRUE;
    case 58:
        *reg = 0xc4c;
        return RT_TRUE;
    }
    if (id == 6)
    {
        *reg = 0x70c;
        return RT_TRUE;
    }
    if (id == 36)
    {
        *reg = 0xa5c;
        return RT_TRUE;
    }
    if (id == 37)
    {
        *reg = 0xa6c;
        return RT_TRUE;
    }
    if (id == 33)
    {
        *reg = 0x9fc;
        return RT_TRUE;
    }
    if (id == 59)
    {
        *reg = 0xa9c;
        return RT_TRUE;
    }
    if (id == 60)
    {
        *reg = 0x9ec;
        return RT_TRUE;
    }
    if (id >= 14 && id <= 16)
    {
        *reg = 0x84c;
        *bit += id - 14;
        return RT_TRUE;
    }
    if (id == 28 || id == 29)
    {
        *reg = 0x96c;
        *bit += id - 28;
        return RT_TRUE;
    }
    if (id == 30 || id == 31)
    {
        *reg = 0x97c;
        *bit += id - 30;
        return RT_TRUE;
    }
    if (id < H616_RST_UART0 || id >= H616_RST_TWI0 + 5)
    {
        return RT_FALSE;
    }
    *reg = id < H616_RST_TWI0 ? H616_UART_BGR : H616_TWI_BGR;
    *bit = 16 + id - (id < H616_RST_TWI0 ? H616_RST_UART0 : H616_RST_TWI0);
    return RT_TRUE;
}

static rt_bool_t h616_r_reset_line(int id, unsigned int *reg, unsigned int *bit)
{
    *bit = 16;
    switch (id)
    {
    case 1:
        *reg = 0x12c;
        return RT_TRUE;
    case 4:
        *reg = 0x19c;
        return RT_TRUE;
    case 5:
        *reg = 0x1cc;
        return RT_TRUE;
    case 7:
        *reg = 0x1bc;
        return RT_TRUE;
    default:
        return RT_FALSE;
    }
}

static rt_err_t h616_reset_update(struct rt_reset_control *rstc, rt_bool_t release)
{
    struct h616_ccu *ccu = rstc->rstcer->priv;
    unsigned int reg, bit;

    if (!(ccu->is_r ? h616_r_reset_line(rstc->id, &reg, &bit) : h616_reset_line(rstc->id, &reg, &bit)))
    {
        return -RT_EINVAL;
    }
    h616_update(rstc->rstcer->priv, reg, bit, release);
    return RT_EOK;
}

static rt_err_t h616_assert(struct rt_reset_control *rstc)
{
    return h616_reset_update(rstc, RT_FALSE);
}

static rt_err_t h616_deassert(struct rt_reset_control *rstc)
{
    return h616_reset_update(rstc, RT_TRUE);
}

static int h616_status(struct rt_reset_control *rstc)
{
    struct h616_ccu *ccu = rstc->rstcer->priv;
    unsigned int reg, bit;

    if (!(ccu->is_r ? h616_r_reset_line(rstc->id, &reg, &bit) : h616_reset_line(rstc->id, &reg, &bit)))
    {
        return -RT_EINVAL;
    }
    return !(HWREG32(ccu->base + reg) & RT_BIT(bit));
}

static const struct rt_reset_control_ops h616_reset_ops = {
    .assert = h616_assert,
    .deassert = h616_deassert,
    .status = h616_status,
};

static rt_err_t h616_ccu_probe(struct rt_platform_device *pdev)
{
    static const char * const osc_names[] = { "hosc", "losc", "iosc", "pll-periph" };
    const struct h616_ccu_soc_data *soc_data = pdev->id->data;
    const struct h616_clock_desc *descs;
    rt_size_t count;
    struct h616_ccu *ccu;
    rt_err_t err = -RT_EIO;
    rt_size_t i;

    if (!soc_data)
    {
        return -RT_EINVAL;
    }
    ccu = rt_calloc(1, sizeof(*ccu));
    if (!ccu)
    {
        return -RT_ENOMEM;
    }
    ccu->is_r = soc_data->is_r;
    descs = ccu->is_r ? h616_r_clock_descs : h616_clock_descs;
    count = ccu->is_r ? RT_ARRAY_SIZE(h616_r_clock_descs) : RT_ARRAY_SIZE(h616_clock_descs);
    ccu->base = rt_dm_dev_iomap(&pdev->parent, 0);
    if (!ccu->base)
    {
        goto fail;
    }
    rt_spin_lock_init(&ccu->lock);
    for (i = 0; i < (ccu->is_r ? 4 : 3); ++i)
    {
        ccu->osc[i] = rt_clk_get_by_name(&pdev->parent, osc_names[i]);
        if (rt_is_err_or_null(ccu->osc[i]))
        {
            err = rt_is_err(ccu->osc[i]) ? rt_ptr_err(ccu->osc[i]) : -RT_EIO;
            goto fail;
        }
        ccu->osc_rate[i] = rt_clk_get_rate(ccu->osc[i]);
    }
    if (!ccu->osc_rate[0])
    {
        goto fail;
    }
    ccu->clocks.dev = &pdev->parent;
    /* Parent references are owned above; do not acquire the list twice. */
    ccu->clocks.parents_clk = rt_err_ptr(-RT_ENOSYS);
    ccu->clocks.priv = ccu;
    ccu->clocks.cells = ccu->cells;
    ccu->clocks.cells_nr = RT_ARRAY_SIZE(ccu->cells);
    for (i = 0; i < count; ++i)
    {
        struct rt_clk_cell *cell = &ccu->bus_clocks[i];

        cell->name = descs[i].name;
        cell->ops = &h616_clk_ops;
        cell->priv = (void *)&descs[i];
        cell->flags = RT_CLK_F_GET_RATE_NOCACHE;
        ccu->cells[descs[i].id] = cell;
    }
    if ((err = rt_clk_register(&ccu->clocks)))
    {
        goto fail;
    }
    ccu->resets.ofw_node = pdev->parent.ofw_node;
    ccu->resets.priv = ccu;
    ccu->resets.ops = &h616_reset_ops;
    if ((err = rt_reset_controller_register(&ccu->resets)))
    {
        if (rt_clk_unregister(&ccu->clocks))
        {
            return err;
        }
        goto fail;
    }
    pdev->parent.user_data = ccu;
    return RT_EOK;

fail:
    for (i = 0; i < RT_ARRAY_SIZE(ccu->osc); ++i)
    {
        if (!rt_is_err_or_null(ccu->osc[i]))
        {
            rt_clk_put(ccu->osc[i]);
        }
    }
    if (ccu->base)
    {
        rt_iounmap(ccu->base);
    }
    rt_free(ccu);
    return err;
}

static const struct rt_ofw_node_id h616_ccu_ids[] = {
    { .compatible = "allwinner,sun50i-h616-ccu", .data = &h616_ccu_data },
    { .compatible = "allwinner,sun50i-h616-r-ccu", .data = &h616_r_ccu_data },
    { /* sentinel */ }
};

static struct rt_platform_driver h616_ccu_driver = {
    .name = "h616-ccu",
    .ids = h616_ccu_ids,
    .probe = h616_ccu_probe,
};

static int h616_ccu_register(void)
{
    rt_platform_driver_register(&h616_ccu_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(h616_ccu_register);
