/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "clk.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dt-bindings/clock/bcm2835.h>
#include <firmware-raspberrypi.h>

#define CM_PASSWORD                 0x5a000000

#define CM_GNRICCTL                 0x000
#define CM_GNRICDIV                 0x004
#define CM_DIV_FRAC_BITS            12
#define CM_DIV_FRAC_MASK            RT_GENMASK(CM_DIV_FRAC_BITS - 1, 0)

#define CM_VPUCTL                   0x008
#define CM_VPUDIV                   0x00c
#define CM_SYSCTL                   0x010
#define CM_SYSDIV                   0x014
#define CM_PERIACTL                 0x018
#define CM_PERIADIV                 0x01c
#define CM_PERIICTL                 0x020
#define CM_PERIIDIV                 0x024
#define CM_H264CTL                  0x028
#define CM_H264DIV                  0x02c
#define CM_ISPCTL                   0x030
#define CM_ISPDIV                   0x034
#define CM_V3DCTL                   0x038
#define CM_V3DDIV                   0x03c
#define CM_CAM0CTL                  0x040
#define CM_CAM0DIV                  0x044
#define CM_CAM1CTL                  0x048
#define CM_CAM1DIV                  0x04c
#define CM_CCP2CTL                  0x050
#define CM_CCP2DIV                  0x054
#define CM_DSI0ECTL                 0x058
#define CM_DSI0EDIV                 0x05c
#define CM_DSI0PCTL                 0x060
#define CM_DSI0PDIV                 0x064
#define CM_DPICTL                   0x068
#define CM_DPIDIV                   0x06c
#define CM_GP0CTL                   0x070
#define CM_GP0DIV                   0x074
#define CM_GP1CTL                   0x078
#define CM_GP1DIV                   0x07c
#define CM_GP2CTL                   0x080
#define CM_GP2DIV                   0x084
#define CM_HSMCTL                   0x088
#define CM_HSMDIV                   0x08c
#define CM_OTPCTL                   0x090
#define CM_OTPDIV                   0x094
#define CM_PCMCTL                   0x098
#define CM_PCMDIV                   0x09c
#define CM_PWMCTL                   0x0a0
#define CM_PWMDIV                   0x0a4
#define CM_SLIMCTL                  0x0a8
#define CM_SLIMDIV                  0x0ac
#define CM_SMICTL                   0x0b0
#define CM_SMIDIV                   0x0b4
/* No definition for 0x0b8 and 0x0bc */
#define CM_TCNTCTL                  0x0c0
#define   CM_TCNT_SRC1_SHIFT        12
#define CM_TCNTCNT                  0x0c4
#define CM_TECCTL                   0x0c8
#define CM_TECDIV                   0x0cc
#define CM_TD0CTL                   0x0d0
#define CM_TD0DIV                   0x0d4
#define CM_TD1CTL                   0x0d8
#define CM_TD1DIV                   0x0dc
#define CM_TSENSCTL                 0x0e0
#define CM_TSENSDIV                 0x0e4
#define CM_TIMERCTL                 0x0e8
#define CM_TIMERDIV                 0x0ec
#define CM_UARTCTL                  0x0f0
#define CM_UARTDIV                  0x0f4
#define CM_VECCTL                   0x0f8
#define CM_VECDIV                   0x0fc
#define CM_DSI0HSCK                 0x120
#define CM_PULSECTL                 0x190
#define CM_PULSEDIV                 0x194
#define CM_SDCCTL                   0x1a8
#define CM_SDCDIV                   0x1ac
#define CM_ARMCTL                   0x1b0
#define CM_AVEOCTL                  0x1b8
#define CM_AVEODIV                  0x1bc
#define CM_EMMCCTL                  0x1c0
#define CM_EMMCDIV                  0x1c4
#define CM_EMMC2CTL                 0x1d0
#define CM_EMMC2DIV                 0x1d4

/* General bits for the CM_*CTL regs */
#define CM_ENABLE                   RT_BIT(4)
#define CM_KILL                     RT_BIT(5)
#define CM_GATE_BIT                 6
#define CM_GATE                     RT_BIT(CM_GATE_BIT)
#define CM_BUSY                     RT_BIT(7)
#define CM_BUSYD                    RT_BIT(8)
#define CM_FRAC                     RT_BIT(9)
#define CM_SRC_SHIFT                0
#define CM_SRC_BITS                 4
#define CM_SRC_MASK                 0xf
#define CM_SRC_GND                  0
#define CM_SRC_OSC                  1
#define CM_SRC_TESTDEBUG0           2
#define CM_SRC_TESTDEBUG1           3
#define CM_SRC_PLLA_CORE            4
#define CM_SRC_PLLA_PER             4
#define CM_SRC_PLLC_CORE0           5
#define CM_SRC_PLLC_PER             5
#define CM_SRC_PLLC_CORE1           8
#define CM_SRC_PLLD_CORE            6
#define CM_SRC_PLLD_PER             6
#define CM_SRC_PLLH_AUX             7
#define CM_SRC_PLLC_CORE1           8
#define CM_SRC_PLLC_CORE2           9

#define CM_OSCCOUNT                 0x100

#define CM_PLLA                     0x104
#define CM_PLL_ANARST               RT_BIT(8)
#define CM_PLLA_HOLDPER             RT_BIT(7)
#define CM_PLLA_LOADPER             RT_BIT(6)
#define CM_PLLA_HOLDCORE            RT_BIT(5)
#define CM_PLLA_LOADCORE            RT_BIT(4)
#define CM_PLLA_HOLDCCP2            RT_BIT(3)
#define CM_PLLA_LOADCCP2            RT_BIT(2)
#define CM_PLLA_HOLDDSI0            RT_BIT(1)
#define CM_PLLA_LOADDSI0            RT_BIT(0)

#define CM_PLLC                     0x108
#define CM_PLLC_HOLDPER             RT_BIT(7)
#define CM_PLLC_LOADPER             RT_BIT(6)
#define CM_PLLC_HOLDCORE2           RT_BIT(5)
#define CM_PLLC_LOADCORE2           RT_BIT(4)
#define CM_PLLC_HOLDCORE1           RT_BIT(3)
#define CM_PLLC_LOADCORE1           RT_BIT(2)
#define CM_PLLC_HOLDCORE0           RT_BIT(1)
#define CM_PLLC_LOADCORE0           RT_BIT(0)

#define CM_PLLD                     0x10c
#define CM_PLLD_HOLDPER             RT_BIT(7)
#define CM_PLLD_LOADPER             RT_BIT(6)
#define CM_PLLD_HOLDCORE            RT_BIT(5)
#define CM_PLLD_LOADCORE            RT_BIT(4)
#define CM_PLLD_HOLDDSI1            RT_BIT(3)
#define CM_PLLD_LOADDSI1            RT_BIT(2)
#define CM_PLLD_HOLDDSI0            RT_BIT(1)
#define CM_PLLD_LOADDSI0            RT_BIT(0)

#define CM_PLLH                     0x110
#define CM_PLLH_LOADRCAL            RT_BIT(2)
#define CM_PLLH_LOADAUX             RT_BIT(1)
#define CM_PLLH_LOADPIX             RT_BIT(0)

#define CM_LOCK                     0x114
#define CM_LOCK_FLOCKH              RT_BIT(12)
#define CM_LOCK_FLOCKD              RT_BIT(11)
#define CM_LOCK_FLOCKC              RT_BIT(10)
#define CM_LOCK_FLOCKB              RT_BIT(9)
#define CM_LOCK_FLOCKA              RT_BIT(8)

#define CM_EVENT                    0x118
#define CM_DSI1ECTL                 0x158
#define CM_DSI1EDIV                 0x15c
#define CM_DSI1PCTL                 0x160
#define CM_DSI1PDIV                 0x164
#define CM_DFTCTL                   0x168
#define CM_DFTDIV                   0x16c

#define CM_PLLB                     0x170
#define CM_PLLB_HOLDARM             RT_BIT(1)
#define CM_PLLB_LOADARM             RT_BIT(0)

#define A2W_PLLA_CTRL               0x1100
#define A2W_PLLC_CTRL               0x1120
#define A2W_PLLD_CTRL               0x1140
#define A2W_PLLH_CTRL               0x1160
#define A2W_PLLB_CTRL               0x11e0
#define A2W_PLL_CTRL_PRST_DISABLE   RT_BIT(17)
#define A2W_PLL_CTRL_PWRDN          RT_BIT(16)
#define A2W_PLL_CTRL_PDIV_MASK      0x000007000
#define A2W_PLL_CTRL_PDIV_SHIFT     12
#define A2W_PLL_CTRL_NDIV_MASK      0x0000003ff
#define A2W_PLL_CTRL_NDIV_SHIFT     0

#define A2W_PLLA_ANA0               0x1010
#define A2W_PLLC_ANA0               0x1030
#define A2W_PLLD_ANA0               0x1050
#define A2W_PLLH_ANA0               0x1070
#define A2W_PLLB_ANA0               0x10f0

#define A2W_PLL_KA_SHIFT            7
#define A2W_PLL_KA_MASK             RT_GENMASK(9, 7)
#define A2W_PLL_KI_SHIFT            19
#define A2W_PLL_KI_MASK             RT_GENMASK(21, 19)
#define A2W_PLL_KP_SHIFT            15
#define A2W_PLL_KP_MASK             RT_GENMASK(18, 15)

#define A2W_PLLH_KA_SHIFT           19
#define A2W_PLLH_KA_MASK            RT_GENMASK(21, 19)
#define A2W_PLLH_KI_LOW_SHIFT       22
#define A2W_PLLH_KI_LOW_MASK        RT_GENMASK(23, 22)
#define A2W_PLLH_KI_HIGH_SHIFT      0
#define A2W_PLLH_KI_HIGH_MASK       RT_GENMASK(0, 0)
#define A2W_PLLH_KP_SHIFT           1
#define A2W_PLLH_KP_MASK            RT_GENMASK(4, 1)

#define A2W_XOSC_CTRL               0x1190
#define A2W_XOSC_CTRL_PLLB_ENABLE   RT_BIT(7)
#define A2W_XOSC_CTRL_PLLA_ENABLE   RT_BIT(6)
#define A2W_XOSC_CTRL_PLLD_ENABLE   RT_BIT(5)
#define A2W_XOSC_CTRL_DDR_ENABLE    RT_BIT(4)
#define A2W_XOSC_CTRL_CPR1_ENABLE   RT_BIT(3)
#define A2W_XOSC_CTRL_USB_ENABLE    RT_BIT(2)
#define A2W_XOSC_CTRL_HDMI_ENABLE   RT_BIT(1)
#define A2W_XOSC_CTRL_PLLC_ENABLE   RT_BIT(0)

#define A2W_PLLA_FRAC               0x1200
#define A2W_PLLC_FRAC               0x1220
#define A2W_PLLD_FRAC               0x1240
#define A2W_PLLH_FRAC               0x1260
#define A2W_PLLB_FRAC               0x12e0
#define A2W_PLL_FRAC_MASK           ((1 << A2W_PLL_FRAC_BITS) - 1)
#define A2W_PLL_FRAC_BITS           20

#define A2W_PLL_CHANNEL_DISABLE     RT_BIT(8)
#define A2W_PLL_DIV_BITS            8
#define A2W_PLL_DIV_SHIFT           0

#define A2W_PLLA_DSI0               0x1300
#define A2W_PLLA_CORE               0x1400
#define A2W_PLLA_PER                0x1500
#define A2W_PLLA_CCP2               0x1600

#define A2W_PLLC_CORE2              0x1320
#define A2W_PLLC_CORE1              0x1420
#define A2W_PLLC_PER                0x1520
#define A2W_PLLC_CORE0              0x1620

#define A2W_PLLD_DSI0               0x1340
#define A2W_PLLD_CORE               0x1440
#define A2W_PLLD_PER                0x1540
#define A2W_PLLD_DSI1               0x1640

#define A2W_PLLH_AUX                0x1360
#define A2W_PLLH_RCAL               0x1460
#define A2W_PLLH_PIX                0x1560
#define A2W_PLLH_STS                0x1660

#define A2W_PLLH_CTRLR              0x1960
#define A2W_PLLH_FRACR              0x1a60
#define A2W_PLLH_AUXR               0x1b60
#define A2W_PLLH_RCALR              0x1c60
#define A2W_PLLH_PIXR               0x1d60
#define A2W_PLLH_STSR               0x1e60

#define A2W_PLLB_ARM                0x13e0
#define A2W_PLLB_SP0                0x14e0
#define A2W_PLLB_SP1                0x15e0
#define A2W_PLLB_SP2                0x16e0

#define LOCK_TIMEOUT_NS             100000000
#define LOCK_TIMEOUT_US             (LOCK_TIMEOUT_NS / 1000)
#define BCM2835_MAX_FB_RATE         1750000000U

#define CLK_TYPE_PLL                0
#define CLK_TYPE_DIV                1
#define CLK_TYPE_CLK                2
#define CLK_TYPE_VPU                3

#define SOC_TYPE_BCM2835            RT_BIT(0)
#define SOC_TYPE_BCM2711            RT_BIT(1)
#define SOC_ALL                     (SOC_TYPE_BCM2835 | SOC_TYPE_BCM2711)

#define VCMSG_ID_CORE_CLOCK         4

struct bcm2835_cprman;

struct cprman_soc_data
{
    rt_uint32_t soc;
};

struct bcm2835_clock_data
{
    struct rt_clk_cell cell;

    struct bcm2835_cprman *cprman;
    void (*init)(struct bcm2835_cprman *cprman, struct bcm2835_clock_data *cdata);

    rt_uint32_t supported;

    /* Bitmap encoding which parents accept rate change propagation. */
    rt_uint32_t set_rate_parent;

    rt_uint32_t ctl_reg;
    rt_uint32_t div_reg;

    /* Number of integer bits in the divider */
    rt_uint32_t int_bits;
    /* Number of fractional bits in the divider */
    rt_uint32_t frac_bits;

    rt_uint32_t flags;

    rt_bool_t is_vpu_clock;
    rt_bool_t is_mash_clock;
    rt_bool_t low_jitter;

    rt_uint32_t tcnt_mux;

    rt_bool_t round_up;
};

#define cell_to_bcm2835_clock_data(cell) rt_container_of(cell, struct bcm2835_clock_data, cell);

static const char *const cprman_parent_names[] =
{
    "osc", "dsi0_byte", "dsi0_ddr2", "dsi0_ddr", "dsi1_byte", "dsi1_ddr2", "dsi1_ddr",
};

struct bcm2835_cprman
{
    struct rt_clk_node parent;

    void *regs;
    struct rt_clk *osc_clk;
    struct rpi_firmware *fw;

    rt_uint32_t soc;
    const char *real_parent_names[RT_ARRAY_SIZE(cprman_parent_names)];
};

#define raw_to_bcm2835_cprman(raw) rt_container_of(raw, struct bcm2835_cprman, parent)

rt_inline void cprman_write(struct bcm2835_cprman *cprman,
        rt_uint32_t reg, rt_uint32_t val)
{
    HWREG32(cprman->regs + reg) = CM_PASSWORD | val;
}

rt_inline rt_uint32_t cprman_read(struct bcm2835_cprman *cprman, rt_uint32_t reg)
{
    return HWREG32(cprman->regs + reg);
}

static rt_bool_t bcm2835_clk_is_claimed(const char *name);

/* ---------------------------------- PLL ----------------------------------- */
struct bcm2835_pll_ana_bits
{
    rt_uint32_t mask0;
    rt_uint32_t set0;
    rt_uint32_t mask1;
    rt_uint32_t set1;
    rt_uint32_t mask3;
    rt_uint32_t set3;
    rt_uint32_t fb_prediv_mask;
};

struct bcm2835_pll_data
{
    struct bcm2835_clock_data cdata;

    rt_uint32_t cm_ctrl_reg;
    rt_uint32_t a2w_ctrl_reg;
    rt_uint32_t frac_reg;
    rt_uint32_t ana_reg_base;
    rt_uint32_t reference_enable_mask;
    /* Bit in CM_LOCK to indicate when the PLL has locked. */
    rt_uint32_t lock_mask;

    const struct bcm2835_pll_ana_bits *ana;

    rt_ubase_t min_rate;
    rt_ubase_t max_rate;
    /*
     * Highest rate for the VCO before we have to use the
     * pre-divide-by-2.
     */
    rt_ubase_t max_fb_rate;
};

rt_inline struct bcm2835_pll_data *cell_to_bcm2835_pll_data(struct rt_clk_cell *cell)
{
    struct bcm2835_clock_data *cdata = cell_to_bcm2835_clock_data(cell);

    return rt_container_of(cdata, struct bcm2835_pll_data, cdata);
}

static const struct bcm2835_pll_ana_bits bcm2835_ana_default =
{
    .mask0 = 0,
    .set0 = 0,
    .mask1 = A2W_PLL_KI_MASK | A2W_PLL_KP_MASK,
    .set1 = (2 << A2W_PLL_KI_SHIFT) | (8 << A2W_PLL_KP_SHIFT),
    .mask3 = A2W_PLL_KA_MASK,
    .set3 = (2 << A2W_PLL_KA_SHIFT),
    .fb_prediv_mask = RT_BIT(14),
};

static const struct bcm2835_pll_ana_bits bcm2835_ana_pllh =
{
    .mask0 = A2W_PLLH_KA_MASK | A2W_PLLH_KI_LOW_MASK,
    .set0 = (2 << A2W_PLLH_KA_SHIFT) | (2 << A2W_PLLH_KI_LOW_SHIFT),
    .mask1 = A2W_PLLH_KI_HIGH_MASK | A2W_PLLH_KP_MASK,
    .set1 = (6 << A2W_PLLH_KP_SHIFT),
    .mask3 = 0,
    .set3 = 0,
    .fb_prediv_mask = RT_BIT(11),
};

static void bcm2835_pll_choose_ndiv_and_fdiv(rt_base_t rate,
        rt_base_t parent_rate, rt_uint32_t *ndiv, rt_uint32_t *fdiv)
{
    rt_uint64_t div;

    div = (rt_uint64_t)rate << A2W_PLL_FRAC_BITS;
    rt_do_div(div, parent_rate);

    *ndiv = div >> A2W_PLL_FRAC_BITS;
    *fdiv = div & ((1 << A2W_PLL_FRAC_BITS) - 1);
}

static rt_uint32_t bcm2835_pll_get_prediv_mask(struct bcm2835_cprman *cprman,
        struct bcm2835_pll_data *data)
{
    /*
     * On BCM2711 there isn't a pre-divisor available in the PLL feedback
     * loop. Bits 13:14 of ANA1 (PLLA,PLLB,PLLC,PLLD) have been re-purposed
     * for to for VCO RANGE bits.
     */
    if (cprman->soc & SOC_TYPE_BCM2711)
    {
        return 0;
    }

    return data->ana->fb_prediv_mask;
}

static rt_ubase_t bcm2835_pll_rate_from_divisors(rt_base_t parent_rate,
        rt_uint32_t ndiv, rt_uint32_t fdiv, rt_uint32_t pdiv)
{
    rt_uint64_t rate;

    if (pdiv == 0)
    {
        return 0;
    }

    rate = (rt_uint64_t)parent_rate * ((ndiv << A2W_PLL_FRAC_BITS) + fdiv);
    rt_do_div(rate, pdiv);

    return rate >> A2W_PLL_FRAC_BITS;
}

static void bcm2835_pll_write_ana(struct bcm2835_cprman *cprman,
        rt_uint32_t ana_reg_base, rt_uint32_t *ana)
{
    /*
     * ANA register setup is done as a series of writes to ANA3-ANA0,
     * in that order.  This lets us write all 4 registers as a single cycle of
     * the serdes interface (taking 100 xosc clocks),
     * whereas if we were to update ana0, 1, and 3 individually through
     * their partial-write registers, each would be their own serdes cycle.
     */
    for (int i = 3; i >= 0; --i)
    {
        cprman_write(cprman, ana_reg_base + i * 4, ana[i]);
    }
}

static rt_err_t bcm2835_pll_on(struct rt_clk_cell *cell)
{
    rt_tick_t timeout;
    struct bcm2835_pll_data *data = cell_to_bcm2835_pll_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    cprman_write(cprman, data->a2w_ctrl_reg,
                 cprman_read(cprman, data->a2w_ctrl_reg) & ~A2W_PLL_CTRL_PWRDN);

    /* Take the PLL out of reset. */
    cprman_write(cprman, data->cm_ctrl_reg,
                 cprman_read(cprman, data->cm_ctrl_reg) & ~CM_PLL_ANARST);

    /* Wait for the PLL to lock. */
    if (rt_strcmp(cell->name, "pllh"))
    {
        timeout = rt_tick_from_millisecond(LOCK_TIMEOUT_US / 1000);
        timeout += rt_tick_get();

        while (!(cprman_read(cprman, CM_LOCK) & data->lock_mask))
        {
            if (rt_tick_get() > timeout)
            {
                return -RT_ETIMEOUT;
            }

            rt_hw_cpu_relax();
        }
    }

    cprman_write(cprman, data->a2w_ctrl_reg,
                 cprman_read(cprman, data->a2w_ctrl_reg) | A2W_PLL_CTRL_PRST_DISABLE);

    return RT_EOK;
}

static void bcm2835_pll_off(struct rt_clk_cell *cell)
{
    struct bcm2835_pll_data *data = cell_to_bcm2835_pll_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    cprman_write(cprman, data->cm_ctrl_reg, CM_PLL_ANARST);
    cprman_write(cprman, data->a2w_ctrl_reg,
                 cprman_read(cprman, data->a2w_ctrl_reg) | A2W_PLL_CTRL_PWRDN);
}

static rt_bool_t bcm2835_pll_is_on(struct rt_clk_cell *cell)
{
    struct bcm2835_pll_data *data = cell_to_bcm2835_pll_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    return !!(cprman_read(cprman, data->a2w_ctrl_reg) & A2W_PLL_CTRL_PRST_DISABLE);
}

static rt_ubase_t bcm2835_pll_get_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_bool_t using_prediv;
    rt_uint32_t ndiv, pdiv, fdiv, a2wctrl;
    struct bcm2835_pll_data *data = cell_to_bcm2835_pll_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    if (parent_rate == 0)
    {
        return 0;
    }

    a2wctrl = cprman_read(cprman, data->a2w_ctrl_reg);

    fdiv = cprman_read(cprman, data->frac_reg) & A2W_PLL_FRAC_MASK;
    ndiv = (a2wctrl & A2W_PLL_CTRL_NDIV_MASK) >> A2W_PLL_CTRL_NDIV_SHIFT;
    pdiv = (a2wctrl & A2W_PLL_CTRL_PDIV_MASK) >> A2W_PLL_CTRL_PDIV_SHIFT;
    using_prediv = cprman_read(cprman, data->ana_reg_base + 4) &
                   bcm2835_pll_get_prediv_mask(cprman, data);

    if (using_prediv)
    {
        ndiv *= 2;
        fdiv *= 2;
    }

    return bcm2835_pll_rate_from_divisors(parent_rate, ndiv, fdiv, pdiv);
}

static rt_base_t bcm2835_pll_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    rt_uint32_t ndiv, fdiv;
    struct bcm2835_pll_data *data = cell_to_bcm2835_pll_data(cell);

    rate = rt_clamp(rate, data->min_rate, data->max_rate);

    bcm2835_pll_choose_ndiv_and_fdiv(rate, *parent_rate, &ndiv, &fdiv);

    return bcm2835_pll_rate_from_divisors(*parent_rate, ndiv, fdiv, 1);
}

static rt_err_t bcm2835_pll_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t prediv_mask, ndiv, fdiv, a2w_ctl, ana[4];
    rt_bool_t was_using_prediv, use_fb_prediv, do_ana_setup_first;
    struct bcm2835_pll_data *data = cell_to_bcm2835_pll_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    prediv_mask = bcm2835_pll_get_prediv_mask(cprman, data);

    if (rate > data->max_fb_rate)
    {
        use_fb_prediv = RT_TRUE;
        rate /= 2;
    }
    else
    {
        use_fb_prediv = RT_FALSE;
    }

    bcm2835_pll_choose_ndiv_and_fdiv(rate, parent_rate, &ndiv, &fdiv);

    for (int i = 3; i >= 0; --i)
    {
        ana[i] = cprman_read(cprman, data->ana_reg_base + i * 4);
    }

    was_using_prediv = ana[1] & prediv_mask;

    ana[0] &= ~data->ana->mask0;
    ana[0] |= data->ana->set0;
    ana[1] &= ~data->ana->mask1;
    ana[1] |= data->ana->set1;
    ana[3] &= ~data->ana->mask3;
    ana[3] |= data->ana->set3;

    if (was_using_prediv && !use_fb_prediv)
    {
        ana[1] &= ~prediv_mask;
        do_ana_setup_first = RT_TRUE;
    }
    else if (!was_using_prediv && use_fb_prediv)
    {
        ana[1] |= prediv_mask;
        do_ana_setup_first = RT_FALSE;
    }
    else
    {
        do_ana_setup_first = RT_TRUE;
    }

    /* Unmask the reference clock from the oscillator. */
    cprman_write(cprman, A2W_XOSC_CTRL,
                 cprman_read(cprman, A2W_XOSC_CTRL) | data->reference_enable_mask);

    if (do_ana_setup_first)
    {
        bcm2835_pll_write_ana(cprman, data->ana_reg_base, ana);
    }

    /* Set the PLL multiplier from the oscillator. */
    cprman_write(cprman, data->frac_reg, fdiv);

    a2w_ctl = cprman_read(cprman, data->a2w_ctrl_reg);
    a2w_ctl &= ~A2W_PLL_CTRL_NDIV_MASK;
    a2w_ctl |= ndiv << A2W_PLL_CTRL_NDIV_SHIFT;
    a2w_ctl &= ~A2W_PLL_CTRL_PDIV_MASK;
    a2w_ctl |= 1 << A2W_PLL_CTRL_PDIV_SHIFT;
    cprman_write(cprman, data->a2w_ctrl_reg, a2w_ctl);

    if (!do_ana_setup_first)
    {
        bcm2835_pll_write_ana(cprman, data->ana_reg_base, ana);
    }

    return RT_EOK;
}

static const struct rt_clk_ops bcm2835_pll_clk_ops =
{
    .prepare = bcm2835_pll_on,
    .unprepare = bcm2835_pll_off,
    .is_prepared = bcm2835_pll_is_on,
    .recalc_rate = bcm2835_pll_get_rate,
    .round_rate = bcm2835_pll_round_rate,
    .set_rate = bcm2835_pll_set_rate,
};

static void bcm2835_pll_init(struct bcm2835_cprman *cprman, struct bcm2835_clock_data *cdata)
{
    struct rt_clk_cell *cell = &cdata->cell;

    /* All of the PLLs derive from the external oscillator. */
    cell->parents_nr = 1;
    cell->parent_name = cprman->real_parent_names[0];

    if (!bcm2835_clk_is_claimed(cell->name))
    {
        cell->flags |= RT_CLK_F_IS_CRITICAL;
    }
}

#define REGISTER_PLL(_struct, _name, _supported, _flags, ...) \
static struct bcm2835_pll_data _struct =                \
{                                                       \
    .cdata =                                            \
    {                                                   \
        .cell.name = _name,                             \
        .cell.ops = &bcm2835_pll_clk_ops,               \
        .cell.flags = RT_CLK_F_IGNORE_UNUSED | _flags,  \
        .init = bcm2835_pll_init,                       \
        .supported = _supported,                        \
    },                                                  \
    __VA_ARGS__                                         \
};
/* ---------------------------------- PLL ----------------------------------- */

/* ------------------------------ PLL Divider ------------------------------- */
struct bcm2835_pll_divider_data
{
    struct bcm2835_clock_data cdata;

    rt_uint32_t cm_reg;
    rt_uint32_t a2w_reg;

    rt_uint32_t load_mask;
    rt_uint32_t hold_mask;
    rt_uint32_t fixed_divider;
};

rt_inline struct bcm2835_pll_divider_data *cell_to_bcm2835_divider_data(struct rt_clk_cell *cell)
{
    struct bcm2835_clock_data *cdata = cell_to_bcm2835_clock_data(cell);

    return rt_container_of(cdata, struct bcm2835_pll_divider_data, cdata);
}

static rt_err_t bcm2835_pll_divider_on(struct rt_clk_cell *cell)
{
    struct bcm2835_pll_divider_data *data = cell_to_bcm2835_divider_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    cprman_write(cprman, data->a2w_reg,
                 cprman_read(cprman, data->a2w_reg) & ~A2W_PLL_CHANNEL_DISABLE);

    cprman_write(cprman, data->cm_reg,
                 cprman_read(cprman, data->cm_reg) & ~data->hold_mask);

    return RT_EOK;
}

static void bcm2835_pll_divider_off(struct rt_clk_cell *cell)
{
    struct bcm2835_pll_divider_data *data = cell_to_bcm2835_divider_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    cprman_write(cprman, data->cm_reg,
                 (cprman_read(cprman, data->cm_reg) & ~data->load_mask) | data->hold_mask);
    cprman_write(cprman, data->a2w_reg,
                 cprman_read(cprman, data->a2w_reg) | A2W_PLL_CHANNEL_DISABLE);
}

static rt_bool_t bcm2835_pll_divider_is_on(struct rt_clk_cell *cell)
{
    struct bcm2835_pll_divider_data *data = cell_to_bcm2835_divider_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    return !(cprman_read(cprman, data->a2w_reg) & A2W_PLL_CHANNEL_DISABLE);
}

static rt_ubase_t bcm2835_pll_divider_get_rate(struct rt_clk_cell *cell,
        rt_ubase_t parent_rate)
{
    rt_uint32_t val, div;
    struct bcm2835_pll_divider_data *data = cell_to_bcm2835_divider_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    val = cprman_read(cprman, data->a2w_reg) >> A2W_PLL_DIV_SHIFT;
    val &= (1 << A2W_PLL_DIV_BITS) - 1;

    div = val ? val : (1 << A2W_PLL_DIV_BITS);

    return div ? RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, div) : parent_rate;
}

static rt_err_t bcm2835_pll_divider_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t cm, div, max_div = 1 << A2W_PLL_DIV_BITS;
    struct bcm2835_pll_divider_data *data = cell_to_bcm2835_divider_data(cell);
    struct bcm2835_cprman *cprman = data->cdata.cprman;

    div = RT_DIV_ROUND_UP_ULL(parent_rate, rate);

    div = rt_min(div, max_div);
    if (div == max_div)
    {
        div = 0;
    }

    cprman_write(cprman, data->a2w_reg, div);
    cm = cprman_read(cprman, data->cm_reg);
    cprman_write(cprman, data->cm_reg, cm | data->load_mask);
    cprman_write(cprman, data->cm_reg, cm & ~data->load_mask);

    return RT_EOK;
}

static const struct rt_clk_ops bcm2835_pll_divider_clk_ops =
{
    .prepare = bcm2835_pll_divider_on,
    .unprepare = bcm2835_pll_divider_off,
    .is_prepared = bcm2835_pll_divider_is_on,
    .recalc_rate = bcm2835_pll_divider_get_rate,
    .set_rate = bcm2835_pll_divider_set_rate,
};

static void bcm2835_pll_divider_init(struct bcm2835_cprman *cprman, struct bcm2835_clock_data *cdata)
{
    struct rt_clk_cell *cell = &cdata->cell;
    struct bcm2835_pll_divider_data *divider_data = cell_to_bcm2835_divider_data(cell);;

    if (!(cprman_read(cprman, divider_data->cm_reg) & divider_data->hold_mask))
    {
        if (!bcm2835_clk_is_claimed(cell->parent_name) ||
            !bcm2835_clk_is_claimed(cell->name))
        {
            cell->flags |= RT_CLK_F_IS_CRITICAL;
        }
    }
}

#define REGISTER_PLL_DIV(_struct, _name, _parent, _supported, _flags, ...) \
static struct bcm2835_pll_divider_data _struct =        \
{                                                       \
    .cdata =                                            \
    {                                                   \
        .cell.name = _name,                             \
        .cell.ops = &bcm2835_pll_divider_clk_ops,       \
        .cell.parents_nr = 1,                           \
        .cell.parent_name = _parent,                    \
        .cell.flags = RT_CLK_F_IGNORE_UNUSED | _flags,  \
        .init = bcm2835_pll_divider_init,               \
        .supported = _supported,                        \
    },                                                  \
    __VA_ARGS__                                         \
};
/* ------------------------------ PLL Divider ------------------------------- */

/* ---------------------------------- CLK ----------------------------------- */
/*
 * The CM dividers do fixed-point division, so we can't use the
 * generic integer divider code like the PLL dividers do (and we can't
 * fake it by having some fixed shifts preceding it in the clock tree,
 * because we'd run out of bits in a 32-bit rt_ubase_t).
 */
struct bcm2835_clock
{
    struct bcm2835_clock_data cdata;
};

rt_inline struct bcm2835_clock *cell_to_bcm2835_clock(struct rt_clk_cell *cell)
{
    struct bcm2835_clock_data *cdata = cell_to_bcm2835_clock_data(cell);

    return rt_container_of(cdata, struct bcm2835_clock, cdata);
}

static rt_uint32_t bcm2835_clock_choose_div(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint64_t temp;
    rt_uint32_t unused_frac_mask, div, mindiv, maxdiv;
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;

    unused_frac_mask = RT_GENMASK(CM_DIV_FRAC_BITS - cdata->frac_bits, 0) >> 1;
    temp = (rt_uint64_t)parent_rate << CM_DIV_FRAC_BITS;

    rt_do_div(temp, rate);
    div = temp;
    div &= ~unused_frac_mask;

    /* Different clamping limits apply for a mash clock */
    if (cdata->is_mash_clock)
    {
        /* Clamp to min divider of 2 */
        mindiv = 2 << CM_DIV_FRAC_BITS;
        /* Clamp to the highest possible integer divider */
        maxdiv = (RT_BIT(cdata->int_bits) - 1) << CM_DIV_FRAC_BITS;
    }
    else
    {
        /* Clamp to min divider of 1 */
        mindiv = 1 << CM_DIV_FRAC_BITS;
        /* Clamp to the highest possible fractional divider */
        maxdiv = RT_GENMASK(cdata->int_bits + CM_DIV_FRAC_BITS - 1,
                            CM_DIV_FRAC_BITS - cdata->frac_bits);
    }

    /* Apply the clamping  limits */
    div = rt_max_t(rt_uint32_t, div, mindiv);
    div = rt_min_t(rt_uint32_t, div, maxdiv);

    return div;
}

static rt_ubase_t bcm2835_clock_rate_from_divisor(struct bcm2835_clock *clock,
        rt_ubase_t parent_rate, rt_uint32_t div)
{
    rt_uint64_t temp;
    struct bcm2835_clock_data *data = &clock->cdata;

    if (data->int_bits == 0 && data->frac_bits == 0)
    {
        return parent_rate;
    }

    /*
     * The divisor is a 12.12 fixed point field, but only some of
     * the bits are populated in any given clock.
     */
    div >>= CM_DIV_FRAC_BITS - data->frac_bits;
    div &= (1 << (data->int_bits + data->frac_bits)) - 1;

    if (div == 0)
    {
        return 0;
    }

    temp = (rt_uint64_t)parent_rate << data->frac_bits;

    rt_do_div(temp, div);

    return temp;
}

static rt_ubase_t bcm2835_round_rate(rt_ubase_t rate)
{
    rt_ubase_t scaler = 1, limit;

    limit = rate / 100000;

    while (scaler < limit)
    {
        scaler *= 10;
    }

    /*
     * If increasing a clock by less than 0.1% changes it
     * from ..999.. to ..000.., round up.
     */
    if ((rate + scaler - 1) / scaler % 1000 == 0)
    {
        rate = rt_roundup(rate, scaler);
    }

    return rate;
}

static void bcm2835_clock_wait_busy(struct bcm2835_clock *clock)
{
    rt_tick_t timeout;
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    timeout = rt_tick_from_millisecond(LOCK_TIMEOUT_US / 1000);
    timeout += rt_tick_get();

    while (cprman_read(cprman, cdata->ctl_reg) & CM_BUSY)
    {
        if (rt_tick_get() > timeout)
        {
            LOG_E("%s: couldn't lock PLL", cdata->cell.name);
            return;
        }

        rt_hw_cpu_relax();
    }
}

static void bcm2835_clock_off(struct rt_clk_cell *cell)
{
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    cprman_write(cprman, cdata->ctl_reg,
                 cprman_read(cprman, cdata->ctl_reg) & ~CM_ENABLE);

    /* BUSY will remain high until the divider completes its cycle. */
    bcm2835_clock_wait_busy(clock);
}

static rt_err_t bcm2835_clock_on(struct rt_clk_cell *cell)
{
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    cprman_write(cprman, cdata->ctl_reg,
                 cprman_read(cprman, cdata->ctl_reg) | CM_ENABLE | CM_GATE);

    return RT_EOK;
}

static rt_bool_t bcm2835_clock_is_on(struct rt_clk_cell *cell)
{
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    return (cprman_read(cprman, cdata->ctl_reg) & CM_ENABLE) != 0;
}

static rt_ubase_t bcm2835_clock_get_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint32_t div;
    rt_ubase_t rate;
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    if (cdata->int_bits == 0 && cdata->frac_bits == 0)
    {
        return parent_rate;
    }

    div = cprman_read(cprman, cdata->div_reg);

    rate = bcm2835_clock_rate_from_divisor(clock, parent_rate, div);

    if (cdata->round_up)
    {
        rate = bcm2835_round_rate(rate);
    }

    return rate;
}

static rt_ubase_t bcm2835_clock_get_rate_vpu(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    if (cprman->fw)
    {
        struct
        {
            rt_uint32_t id;
            rt_uint32_t val;
        } packet;

        packet.id = VCMSG_ID_CORE_CLOCK;
        packet.val = 0;

        if (!rpi_firmware_property(cprman->fw, RPI_FIRMWARE_GET_MAX_CLOCK_RATE,
            &packet, sizeof(packet)))
        {
            return packet.val;
        }
    }

    return bcm2835_clock_get_rate(cell, parent_rate);
}

static rt_err_t bcm2835_clock_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t div, ctl;
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    div = bcm2835_clock_choose_div(cell, rate, parent_rate);
    ctl = cprman_read(cprman, cdata->ctl_reg);

    /*
     * If the clock is running, we have to pause clock generation while
     * updating the control and div regs.  This is glitchless (no clock
     * signals generated faster than the rate) but each reg access is two
     * OSC cycles so the clock will slow down for a moment.
     */
    if (ctl & CM_ENABLE)
    {
        cprman_write(cprman, cdata->ctl_reg, ctl & ~CM_ENABLE);
        bcm2835_clock_wait_busy(clock);
    }

    ctl &= ~CM_FRAC;
    ctl |= (div & CM_DIV_FRAC_MASK) ? CM_FRAC : 0;
    cprman_write(cprman, cdata->ctl_reg, ctl);

    cprman_write(cprman, cdata->div_reg, div);

    return RT_EOK;
}

static rt_err_t bcm2835_clock_set_parent(struct rt_clk_cell *cell, rt_uint8_t idx)
{
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    cprman_write(cprman, cdata->ctl_reg, (idx << CM_SRC_SHIFT) & CM_SRC_MASK);

    return RT_EOK;
}

static rt_uint8_t bcm2835_clock_get_parent(struct rt_clk_cell *cell)
{
    struct bcm2835_clock *clock = cell_to_bcm2835_clock(cell);
    struct bcm2835_clock_data *cdata = &clock->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    return (cprman_read(cprman, cdata->ctl_reg) & CM_SRC_MASK) >> CM_SRC_SHIFT;
}

static const struct rt_clk_ops bcm2835_clock_clk_ops =
{
    .prepare = bcm2835_clock_on,
    .unprepare = bcm2835_clock_off,
    .is_prepared = bcm2835_clock_is_on,
    .recalc_rate = bcm2835_clock_get_rate,
    .set_rate = bcm2835_clock_set_rate,
    .set_parent = bcm2835_clock_set_parent,
    .get_parent = bcm2835_clock_get_parent,
};

static rt_bool_t bcm2835_vpu_clock_is_on(struct rt_clk_cell *cell)
{
    return RT_TRUE;
}

/*
 * The VPU clock can never be disabled (it doesn't have an ENABLE bit),
 * so it gets its own set of clock ops.
 */
static const struct rt_clk_ops bcm2835_vpu_clock_clk_ops =
{
    .is_prepared = bcm2835_vpu_clock_is_on,
    .recalc_rate = bcm2835_clock_get_rate_vpu,
    .set_rate = bcm2835_clock_set_rate,
    .set_parent = bcm2835_clock_set_parent,
    .get_parent = bcm2835_clock_get_parent,
};

static void bcm2835_clock_init(struct bcm2835_cprman *cprman, struct bcm2835_clock_data *cdata)
{
    struct rt_clk_cell *cell = &cdata->cell;

    /*
     * Some GPIO clocks for ethernet/wifi PLLs are marked as
     * critical (since some platforms use them), but if the
     * firmware didn't have them turned on then they clearly
     * aren't actually critical.
     */
    if ((cprman_read(cprman, cdata->ctl_reg) & CM_ENABLE) == 0)
    {
        cell->flags &= ~RT_CLK_F_IS_CRITICAL;
    }

    /*
     * Pass the CLK_SET_RATE_PARENT flag if we are allowed to propagate
     * rate changes on at least of the parents.
     */
    if (cdata->set_rate_parent)
    {
        cell->flags |= RT_CLK_F_SET_RATE_PARENT;
    }

    if (cdata->is_vpu_clock)
    {
        cell->ops = &bcm2835_vpu_clock_clk_ops;
    }
    else
    {
        /* If the clock wasn't actually enabled at boot, it's not critical. */
        if (!(cprman_read(cprman, cdata->ctl_reg) & CM_ENABLE))
        {
            cell->flags &= ~RT_CLK_F_IS_CRITICAL;
        }
    }
}

#define REGISTER_CLK(_struct, _name, _parents, _supported, _flags, ...) \
static struct bcm2835_clock _struct =                   \
{                                                       \
    .cdata =                                            \
    {                                                   \
        .cell.name = _name,                             \
        .cell.parents_nr = RT_ARRAY_SIZE(_parents),     \
        .cell.parent_names = _parents,                  \
        .cell.ops = &bcm2835_clock_clk_ops,             \
        .cell.flags = RT_CLK_F_IGNORE_UNUSED | _flags,  \
        .init = bcm2835_clock_init,                     \
        .supported = _supported,                        \
    },                                                  \
    __VA_ARGS__                                         \
};
/* ---------------------------------- CLK ----------------------------------- */

/* -------------------------------- PLL Gate -------------------------------- */
struct bcm2835_gate_data
{
    struct bcm2835_clock_data cdata;
};

rt_inline struct bcm2835_gate_data *cell_to_bcm2835_gate_data(struct rt_clk_cell *cell)
{
    struct bcm2835_clock_data *cdata = cell_to_bcm2835_clock_data(cell);

    return rt_container_of(cdata, struct bcm2835_gate_data, cdata);
}

static void bcm2835_clock_gate_endisable(struct rt_clk_cell *cell, int enable)
{
    rt_uint32_t value;
    int set = 0 ^ enable;
    struct bcm2835_gate_data *gate = cell_to_bcm2835_gate_data(cell);
    struct bcm2835_clock_data *cdata = &gate->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    value = cprman_read(cprman, cdata->ctl_reg);
    if (set)
    {
        value |= RT_BIT(CM_GATE_BIT);
    }
    else
    {
        value &= ~RT_BIT(CM_GATE_BIT);
    }
    cprman_write(cprman, cdata->ctl_reg, value);
}

static rt_err_t bcm2835_clock_gate_enable(struct rt_clk_cell *cell)
{
    bcm2835_clock_gate_endisable(cell, 1);

    return RT_EOK;
}

static void bcm2835_clock_gate_disable(struct rt_clk_cell *cell)
{
    bcm2835_clock_gate_endisable(cell, 0);
}

static rt_bool_t bcm2835_clock_gate_is_enabled(struct rt_clk_cell *cell)
{
    rt_uint32_t value;
    struct bcm2835_gate_data *gate = cell_to_bcm2835_gate_data(cell);
    struct bcm2835_clock_data *cdata = &gate->cdata;
    struct bcm2835_cprman *cprman = cdata->cprman;

    value = cprman_read(cprman, cdata->ctl_reg);
    value &= RT_BIT(CM_GATE_BIT);

    return !!value;
}

const struct rt_clk_ops bcm2835_clock_gate_ops =
{
    .enable = bcm2835_clock_gate_enable,
    .disable = bcm2835_clock_gate_disable,
    .is_enabled = bcm2835_clock_gate_is_enabled,
};

#define REGISTER_GATE(_struct, _name, _parent, _supported, _flags, ...) \
static struct bcm2835_gate_data _struct =               \
{                                                       \
    .cdata =                                            \
    {                                                   \
        .cell.name = _name,                             \
        .cell.ops = &bcm2835_clock_gate_ops,            \
        .cell.parents_nr = 1,                           \
        .cell.parent_name = _parent,                    \
        .cell.flags = RT_CLK_F_SET_RATE_GATE |          \
                      RT_CLK_F_IGNORE_UNUSED | _flags,  \
        .supported = _supported,                        \
    },                                                  \
    __VA_ARGS__                                         \
};
/* -------------------------------- PLL Gate -------------------------------- */

/*
 * PLLA is the auxiliary PLL, used to drive the CCP2
 * (Compact Camera Port 2) transmitter clock.
 *
 * It is in the PX LDO power domain, which is on when the
 * AUDIO domain is on.
 */
REGISTER_PLL(plla, "plla", SOC_ALL, 0,
    .cm_ctrl_reg = CM_PLLA,
    .a2w_ctrl_reg = A2W_PLLA_CTRL,
    .frac_reg = A2W_PLLA_FRAC,
    .ana_reg_base = A2W_PLLA_ANA0,
    .reference_enable_mask = A2W_XOSC_CTRL_PLLA_ENABLE,
    .lock_mask = CM_LOCK_FLOCKA,
    .ana = &bcm2835_ana_default,
    .min_rate = 600000000U,
    .max_rate = 2400000000U,
    .max_fb_rate = BCM2835_MAX_FB_RATE);
/* PLLB is used for the ARM's clock. */
REGISTER_PLL(pllb, "pllb", SOC_ALL, RT_CLK_F_GET_RATE_NOCACHE,
    .cm_ctrl_reg = CM_PLLB,
    .a2w_ctrl_reg = A2W_PLLB_CTRL,
    .frac_reg = A2W_PLLB_FRAC,
    .ana_reg_base = A2W_PLLB_ANA0,
    .reference_enable_mask = A2W_XOSC_CTRL_PLLB_ENABLE,
    .lock_mask = CM_LOCK_FLOCKB,
    .ana = &bcm2835_ana_default,
    .min_rate = 600000000U,
    .max_rate = 3000000000U,
    .max_fb_rate = BCM2835_MAX_FB_RATE);
/*
 * PLLC is the core PLL, used to drive the core VPU clock.
 *
 * It is in the PX LDO power domain, which is on when the
 * AUDIO domain is on.
 */
REGISTER_PLL(pllc, "pllc", SOC_ALL, 0,
    .cm_ctrl_reg = CM_PLLC,
    .a2w_ctrl_reg = A2W_PLLC_CTRL,
    .frac_reg = A2W_PLLC_FRAC,
    .ana_reg_base = A2W_PLLC_ANA0,
    .reference_enable_mask = A2W_XOSC_CTRL_PLLC_ENABLE,
    .lock_mask = CM_LOCK_FLOCKC,
    .ana = &bcm2835_ana_default,
    .min_rate = 600000000U,
    .max_rate = 3000000000U,
    .max_fb_rate = BCM2835_MAX_FB_RATE);
/*
 * PLLD is the display PLL, used to drive DSI display panels.
 *
 * It is in the PX LDO power domain, which is on when the
 * AUDIO domain is on.
 */
REGISTER_PLL(plld, "plld", SOC_ALL, 0,
    .cm_ctrl_reg = CM_PLLD,
    .a2w_ctrl_reg = A2W_PLLD_CTRL,
    .frac_reg = A2W_PLLD_FRAC,
    .ana_reg_base = A2W_PLLD_ANA0,
    .reference_enable_mask = A2W_XOSC_CTRL_DDR_ENABLE,
    .lock_mask = CM_LOCK_FLOCKD,
    .ana = &bcm2835_ana_default,
    .min_rate = 600000000U,
    .max_rate = 2400000000U,
    .max_fb_rate = BCM2835_MAX_FB_RATE);

/*
 * PLLH is used to supply the pixel clock or the AUX clock for the
 * TV encoder.
 *
 * It is in the HDMI power domain.
 */
REGISTER_PLL(pllh, "pllh", SOC_TYPE_BCM2835, 0,
    .cm_ctrl_reg = CM_PLLH,
    .a2w_ctrl_reg = A2W_PLLH_CTRL,
    .frac_reg = A2W_PLLH_FRAC,
    .ana_reg_base = A2W_PLLH_ANA0,
    .reference_enable_mask = A2W_XOSC_CTRL_PLLC_ENABLE,
    .lock_mask = CM_LOCK_FLOCKH,
    .ana = &bcm2835_ana_pllh,
    .min_rate = 600000000U,
    .max_rate = 3000000000U,
    .max_fb_rate = BCM2835_MAX_FB_RATE);

REGISTER_PLL_DIV(plla_core, "plla_core", "plla", SOC_ALL, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLA,
    .a2w_reg = A2W_PLLA_CORE,
    .load_mask = CM_PLLA_LOADCORE,
    .hold_mask = CM_PLLA_HOLDCORE,
    .fixed_divider = 1);

/*
 * PLLA_PER is used for gpu clocks. Controlled by firmware, see
 * clk-raspberrypi.c.
 */
REGISTER_PLL_DIV(plla_dsi0, "plla_dsi0", "plla", SOC_ALL, 0,
    .cm_reg = CM_PLLA,
    .a2w_reg = A2W_PLLA_DSI0,
    .load_mask = CM_PLLA_LOADDSI0,
    .hold_mask = CM_PLLA_HOLDDSI0,
    .fixed_divider = 1);

REGISTER_PLL_DIV(plla_ccp2, "plla_ccp2", "plla", SOC_ALL, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLA,
    .a2w_reg = A2W_PLLA_CCP2,
    .load_mask = CM_PLLA_LOADCCP2,
    .hold_mask = CM_PLLA_HOLDCCP2,
    .fixed_divider = 1);

REGISTER_PLL_DIV(pllb_arm, "pllb_arm", "pllb", SOC_ALL, RT_CLK_F_SET_RATE_PARENT | RT_CLK_F_GET_RATE_NOCACHE,
    .cm_reg = CM_PLLB,
    .a2w_reg = A2W_PLLB_ARM,
    .load_mask = CM_PLLB_LOADARM,
    .hold_mask = CM_PLLB_HOLDARM,
    .fixed_divider = 1);

REGISTER_PLL_DIV(pllc_core0, "pllc_core0", "pllc", SOC_ALL, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLC,
    .a2w_reg = A2W_PLLC_CORE0,
    .load_mask = CM_PLLC_LOADCORE0,
    .hold_mask = CM_PLLC_HOLDCORE0,
    .fixed_divider = 1);
REGISTER_PLL_DIV(pllc_core1, "pllc_core1", "pllc", SOC_ALL, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLC,
    .a2w_reg = A2W_PLLC_CORE1,
    .load_mask = CM_PLLC_LOADCORE1,
    .hold_mask = CM_PLLC_HOLDCORE1,
    .fixed_divider = 1);
REGISTER_PLL_DIV(pllc_core2, "pllc_core2", "pllc", SOC_ALL, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLC,
    .a2w_reg = A2W_PLLC_CORE2,
    .load_mask = CM_PLLC_LOADCORE2,
    .hold_mask = CM_PLLC_HOLDCORE2,
    .fixed_divider = 1);
REGISTER_PLL_DIV(pllc_per, "pllc_per", "pllc", SOC_ALL, RT_CLK_F_IS_CRITICAL | RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLC,
    .a2w_reg = A2W_PLLC_PER,
    .load_mask = CM_PLLC_LOADPER,
    .hold_mask = CM_PLLC_HOLDPER,
    .fixed_divider = 1);

REGISTER_PLL_DIV(plld_core, "plld_core", "plld", SOC_ALL, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLD,
    .a2w_reg = A2W_PLLD_CORE,
    .load_mask = CM_PLLD_LOADCORE,
    .hold_mask = CM_PLLD_HOLDCORE,
    .fixed_divider = 1);
/*
 * VPU firmware assumes that PLLD_PER isn't disabled by the ARM core.
 * Otherwise this could cause firmware lookups. That's why we mark
 * it as critical.
 */
REGISTER_PLL_DIV(plld_per, "plld_per", "plld", SOC_ALL, RT_CLK_F_IS_CRITICAL | RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLD,
    .a2w_reg = A2W_PLLD_PER,
    .load_mask = CM_PLLD_LOADPER,
    .hold_mask = CM_PLLD_HOLDPER,
    .fixed_divider = 1);
REGISTER_PLL_DIV(plld_dsi0, "plld_dsi0", "plld", SOC_ALL, 0,
    .cm_reg = CM_PLLD,
    .a2w_reg = A2W_PLLD_DSI0,
    .load_mask = CM_PLLD_LOADDSI0,
    .hold_mask = CM_PLLD_HOLDDSI0,
    .fixed_divider = 1);
REGISTER_PLL_DIV(plld_dsi1, "plld_dsi1", "plld", SOC_ALL, 0,
    .cm_reg = CM_PLLD,
    .a2w_reg = A2W_PLLD_DSI1,
    .load_mask = CM_PLLD_LOADDSI1,
    .hold_mask = CM_PLLD_HOLDDSI1,
    .fixed_divider = 1);
REGISTER_PLL_DIV(pllh_rcal, "pllh_rcal", "pllh", SOC_TYPE_BCM2835, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLH,
    .a2w_reg = A2W_PLLH_RCAL,
    .load_mask = CM_PLLH_LOADRCAL,
    .hold_mask = 0,
    .fixed_divider = 10);
REGISTER_PLL_DIV(pllh_aux, "pllh_aux", "pllh", SOC_TYPE_BCM2835, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLH,
    .a2w_reg = A2W_PLLH_AUX,
    .load_mask = CM_PLLH_LOADAUX,
    .hold_mask = 0,
    .fixed_divider = 1);
REGISTER_PLL_DIV(pllh_pix, "pllh_pix", "pllh", SOC_TYPE_BCM2835, RT_CLK_F_SET_RATE_PARENT,
    .cm_reg = CM_PLLH,
    .a2w_reg = A2W_PLLH_PIX,
    .load_mask = CM_PLLH_LOADPIX,
    .hold_mask = 0,
    .fixed_divider = 10);

/* Main oscillator parent mux */
static const char *const bcm2835_clock_osc_parents[] =
{
    "gnd", "osc", "testdebug0", "testdebug1"
};

/* One Time Programmable Memory clock.  Maximum 10Mhz. */
REGISTER_CLK(clock_otp, "otp", bcm2835_clock_osc_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_OTPCTL,
    .cdata.div_reg = CM_OTPDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 0,
    .cdata.tcnt_mux = 6);
/*
 * Used for a 1Mhz clock for the system clocksource, and also used
 * bythe watchdog timer and the camera pulse generator.
 */
REGISTER_CLK(clock_timer, "timer", bcm2835_clock_osc_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_TIMERCTL,
    .cdata.div_reg = CM_TIMERDIV,
    .cdata.int_bits = 6,
    .cdata.frac_bits = 12);
/*
 * Clock for the temperature sensor.
 * Generally run at 2Mhz, max 5Mhz.
 */
REGISTER_CLK(clock_tsens, "tsens", bcm2835_clock_osc_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_TSENSCTL,
    .cdata.div_reg = CM_TSENSDIV,
    .cdata.int_bits = 5,
    .cdata.frac_bits = 0);
REGISTER_CLK(clock_tec, "tec", bcm2835_clock_osc_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_TECCTL,
    .cdata.div_reg = CM_TECDIV,
    .cdata.int_bits = 6,
    .cdata.frac_bits = 0);

/* Main peripherial parent mux */
static const char *const bcm2835_clock_per_parents[] =
{
    "gnd", "osc", "testdebug0", "testdebug1", "plla_per", "pllc_per", "plld_per", "pllh_aux",
};

/* Clocks with per parent mux */
REGISTER_CLK(clock_aveo, "aveo", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_AVEOCTL,
    .cdata.div_reg = CM_AVEODIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 0,
    .cdata.tcnt_mux = 38);
REGISTER_CLK(clock_cam0, "cam0", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_CAM0CTL,
    .cdata.div_reg = CM_CAM0DIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 14);
REGISTER_CLK(clock_cam1, "cam1", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_CAM1CTL,
    .cdata.div_reg = CM_CAM1DIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 15);
REGISTER_CLK(clock_dft, "dft", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_DFTCTL,
    .cdata.div_reg = CM_DFTDIV,
    .cdata.int_bits = 5,
    .cdata.frac_bits = 0);
REGISTER_CLK(clock_dpi, "dpi", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_DPICTL,
    .cdata.div_reg = CM_DPIDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 17);

/* Arasan EMMC clock */
REGISTER_CLK(clock_emmc, "emmc", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_EMMCCTL,
    .cdata.div_reg = CM_EMMCDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 39);

/* EMMC2 clock (only available for BCM2711) */
REGISTER_CLK(clock_emmc2, "emmc2", bcm2835_clock_per_parents, SOC_TYPE_BCM2711, 0,
    .cdata.ctl_reg = CM_EMMC2CTL,
    .cdata.div_reg = CM_EMMC2DIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 42);

/* General purpose (GPIO) clocks */
REGISTER_CLK(clock_gp0, "gp0", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_GP0CTL,
    .cdata.div_reg = CM_GP0DIV,
    .cdata.int_bits = 12,
    .cdata.frac_bits = 12,
    .cdata.is_mash_clock = RT_TRUE,
    .cdata.tcnt_mux = 20);
REGISTER_CLK(clock_gp1, "gp1", bcm2835_clock_per_parents, SOC_ALL, RT_CLK_F_IS_CRITICAL,
    .cdata.ctl_reg = CM_GP1CTL,
    .cdata.div_reg = CM_GP1DIV,
    .cdata.int_bits = 12,
    .cdata.frac_bits = 12,
    .cdata.is_mash_clock = RT_TRUE,
    .cdata.tcnt_mux = 21);
REGISTER_CLK(clock_gp2, "gp2", bcm2835_clock_per_parents, SOC_ALL, RT_CLK_F_IS_CRITICAL,
    .cdata.ctl_reg = CM_GP2CTL,
    .cdata.div_reg = CM_GP2DIV,
    .cdata.int_bits = 12,
    .cdata.frac_bits = 12);

/* HDMI state machine */
REGISTER_CLK(clock_hsm, "hsm", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_HSMCTL,
    .cdata.div_reg = CM_HSMDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 22);
REGISTER_CLK(clock_pwm, "pwm", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_PWMCTL,
    .cdata.div_reg = CM_PWMDIV,
    .cdata.int_bits = 12,
    .cdata.frac_bits = 12,
    .cdata.is_mash_clock = RT_TRUE,
    .cdata.tcnt_mux = 24);
REGISTER_CLK(clock_slim, "slim", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_SLIMCTL,
    .cdata.div_reg = CM_SLIMDIV,
    .cdata.int_bits = 12,
    .cdata.frac_bits = 12,
    .cdata.is_mash_clock = RT_TRUE,
    .cdata.tcnt_mux = 25);
REGISTER_CLK(clock_smi, "smi", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_SMICTL,
    .cdata.div_reg = CM_SMIDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 27);
REGISTER_CLK(clock_uart, "uart", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_UARTCTL,
    .cdata.div_reg = CM_UARTDIV,
    .cdata.int_bits = 10,
    .cdata.frac_bits = 12,
    .cdata.tcnt_mux = 28,
    .cdata.round_up = RT_TRUE);

/* Dsi clocks */
REGISTER_CLK(clock_dsi0e, "dsi0e", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_DSI0ECTL,
    .cdata.div_reg = CM_DSI0EDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 18);
REGISTER_CLK(clock_dsi1e, "dsi1e", bcm2835_clock_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_DSI1ECTL,
    .cdata.div_reg = CM_DSI1EDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 19);

/*
 * Restrict clock sources for the PCM peripheral to the oscillator and
 * PLLD_PER because other source may have varying rates or be switched
 * off.
 *
 * Prevent other sources from being selected by replacing their names in
 * the list of potential parents with dummy entries (entry index is
 * significant).
 */
static const char *const bcm2835_pcm_per_parents[] =
{
    "-", "osc", "-", "-", "-", "-", "plld_per", "-",
};

REGISTER_CLK(clock_pcm, "pcm", bcm2835_pcm_per_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_PCMCTL,
    .cdata.div_reg = CM_PCMDIV,
    .cdata.int_bits = 12,
    .cdata.frac_bits = 12,
    .cdata.is_mash_clock = RT_TRUE,
    .cdata.low_jitter = RT_TRUE,
    .cdata.tcnt_mux = 23);

/* Main vpu parent mux */
static const char *const bcm2835_clock_vpu_parents[] =
{
    "gnd", "osc", "testdebug0", "testdebug1", "plla_core", "pllc_core0",
    "plld_core", "pllh_aux", "pllc_core1", "pllc_core2",
};

/* Clocks with vpu parent mux */
REGISTER_CLK(clock_h264, "h264", bcm2835_clock_vpu_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_H264CTL,
    .cdata.div_reg = CM_H264DIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 1);
REGISTER_CLK(clock_isp, "isp", bcm2835_clock_vpu_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_ISPCTL,
    .cdata.div_reg = CM_ISPDIV,
    .cdata.int_bits = 4,
    .cdata.frac_bits = 8,
    .cdata.tcnt_mux = 2);

/*
 * Secondary SDRAM clock.  Used for low-voltage modes when the PLL
 * in the SDRAM controller can't be used.
 */
REGISTER_CLK(clock_sdram, "sdram", bcm2835_clock_vpu_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_SDCCTL,
    .cdata.div_reg = CM_SDCDIV,
    .cdata.int_bits = 6,
    .cdata.frac_bits = 0,
    .cdata.tcnt_mux = 3);
/*
 * CLOCK_V3D is used for v3d clock. Controlled by firmware, see
 * clk-raspberrypi.c.
 */

/*
 * VPU clock.  This doesn't have an enable bit, since it drives
 * the bus for everything else, and is special so it doesn't need
 * to be gated for rate changes.  It is also known as "clk_audio"
 * in various hardware documentation.
 */
REGISTER_CLK(clock_vpu, "vpu", bcm2835_clock_vpu_parents, SOC_ALL, RT_CLK_F_IS_CRITICAL,
    .cdata.ctl_reg = CM_VPUCTL,
    .cdata.div_reg = CM_VPUDIV,
    .cdata.int_bits = 12,
    .cdata.frac_bits = 8,
    .cdata.is_vpu_clock = RT_TRUE,
    .cdata.tcnt_mux = 5);

/*
 * DSI parent clocks.  The DSI byte/DDR/DDR2 clocks come from the DSI
 * analog PHY.  The _inv variants are generated internally to cprman,
 * but we don't use them so they aren't hooked up.
 */
static const char *const bcm2835_clock_dsi0_parents[] =
{
    "gnd", "osc", "testdebug0", "testdebug1", "dsi0_ddr", "dsi0_ddr_inv", "dsi0_ddr2",
    "dsi0_ddr2_inv", "dsi0_byte", "dsi0_byte_inv",
};

REGISTER_CLK(clock_dsi0p, "dsi0p", bcm2835_clock_dsi0_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_DSI0PCTL,
    .cdata.div_reg = CM_DSI0PDIV,
    .cdata.int_bits = 0,
    .cdata.frac_bits = 0,
    .cdata.tcnt_mux = 12);

static const char *const bcm2835_clock_dsi1_parents[] =
{
    "gnd", "osc", "testdebug0", "testdebug1", "dsi1_ddr", "dsi1_ddr_inv", "dsi1_ddr2",
    "dsi1_ddr2_inv", "dsi1_byte", "dsi1_byte_inv",
};

REGISTER_CLK(clock_dsi1p, "dsi1p", bcm2835_clock_dsi1_parents, SOC_ALL, 0,
    .cdata.ctl_reg = CM_DSI1PCTL,
    .cdata.div_reg = CM_DSI1PDIV,
    .cdata.int_bits = 0,
    .cdata.frac_bits = 0,
    .cdata.tcnt_mux = 13);
/*
 * CM_PERIICTL (and CM_PERIACTL, CM_SYSCTL and CM_VPUCTL if
 * you have the debug bit set in the power manager, which we
 * don't bother exposing) are individual gates off of the
 * non-stop vpu clock.
 */
REGISTER_GATE(clock_peri_image, "peri_image", "vpu", SOC_ALL, 0,
    .cdata.ctl_reg = CM_PERIICTL);

static struct rt_clk_cell *bcm2835_clk_cell[] =
{
    [BCM2835_PLLA]              = &plla.cdata.cell,
    [BCM2835_PLLB]              = &pllb.cdata.cell,
    [BCM2835_PLLC]              = &pllc.cdata.cell,
    [BCM2835_PLLD]              = &plld.cdata.cell,
    [BCM2835_PLLH]              = &pllh.cdata.cell,

    [BCM2835_PLLA_CORE]         = &plla_core.cdata.cell,
    [BCM2835_PLLA_DSI0]         = &plla_dsi0.cdata.cell,
    [BCM2835_PLLA_CCP2]         = &plla_ccp2.cdata.cell,
    [BCM2835_PLLB_ARM]          = &pllb_arm.cdata.cell,
    [BCM2835_PLLC_CORE0]        = &pllc_core0.cdata.cell,
    [BCM2835_PLLC_CORE1]        = &pllc_core1.cdata.cell,
    [BCM2835_PLLC_CORE2]        = &pllc_core2.cdata.cell,
    [BCM2835_PLLC_PER]          = &pllc_per.cdata.cell,
    [BCM2835_PLLD_CORE]         = &plld_core.cdata.cell,
    [BCM2835_PLLD_PER]          = &plld_per.cdata.cell,
    [BCM2835_PLLD_DSI0]         = &plld_dsi0.cdata.cell,
    [BCM2835_PLLD_DSI1]         = &plld_dsi1.cdata.cell,
    [BCM2835_PLLH_RCAL]         = &pllh_rcal.cdata.cell,
    [BCM2835_PLLH_AUX]          = &pllh_aux.cdata.cell,
    [BCM2835_PLLH_PIX]          = &pllh_pix.cdata.cell,

    [BCM2835_CLOCK_OTP]         = &clock_otp.cdata.cell,
    [BCM2835_CLOCK_TIMER]       = &clock_timer.cdata.cell,
    [BCM2835_CLOCK_TSENS]       = &clock_tsens.cdata.cell,
    [BCM2835_CLOCK_TEC]         = &clock_tec.cdata.cell,
    [BCM2835_CLOCK_AVEO]        = &clock_aveo.cdata.cell,
    [BCM2835_CLOCK_CAM0]        = &clock_cam0.cdata.cell,
    [BCM2835_CLOCK_CAM1]        = &clock_cam1.cdata.cell,
    [BCM2835_CLOCK_DFT]         = &clock_dft.cdata.cell,
    [BCM2835_CLOCK_DPI]         = &clock_dpi.cdata.cell,
    [BCM2835_CLOCK_EMMC]        = &clock_emmc.cdata.cell,
    [BCM2711_CLOCK_EMMC2]       = &clock_emmc2.cdata.cell,
    [BCM2835_CLOCK_GP0]         = &clock_gp0.cdata.cell,
    [BCM2835_CLOCK_GP1]         = &clock_gp1.cdata.cell,
    [BCM2835_CLOCK_GP2]         = &clock_gp2.cdata.cell,
    [BCM2835_CLOCK_HSM]         = &clock_hsm.cdata.cell,
    [BCM2835_CLOCK_PWM]         = &clock_pwm.cdata.cell,
    [BCM2835_CLOCK_SLIM]        = &clock_slim.cdata.cell,
    [BCM2835_CLOCK_SMI]         = &clock_smi.cdata.cell,
    [BCM2835_CLOCK_UART]        = &clock_uart.cdata.cell,
    [BCM2835_CLOCK_DSI0E]       = &clock_dsi0e.cdata.cell,
    [BCM2835_CLOCK_DSI1E]       = &clock_dsi1e.cdata.cell,
    [BCM2835_CLOCK_PCM]         = &clock_pcm.cdata.cell,
    [BCM2835_CLOCK_H264]        = &clock_h264.cdata.cell,
    [BCM2835_CLOCK_ISP]         = &clock_isp.cdata.cell,
    [BCM2835_CLOCK_SDRAM]       = &clock_sdram.cdata.cell,
    [BCM2835_CLOCK_VPU]         = &clock_vpu.cdata.cell,
    [BCM2835_CLOCK_DSI0P]       = &clock_dsi0p.cdata.cell,
    [BCM2835_CLOCK_DSI1P]       = &clock_dsi1p.cdata.cell,

    [BCM2835_CLOCK_PERI_IMAGE]  = &clock_peri_image.cdata.cell,
};

static rt_bool_t bcm2835_clk_claimed[RT_ARRAY_SIZE(bcm2835_clk_cell)];

static rt_bool_t bcm2835_clk_is_claimed(const char *name)
{
    for (int i = 0; i < RT_ARRAY_SIZE(bcm2835_clk_cell); ++i)
    {
        if (bcm2835_clk_cell[i])
        {
            if (!rt_strcmp(name, bcm2835_clk_cell[i]->name))
            {
                return bcm2835_clk_claimed[i];
            }
        }
    }

    return RT_FALSE;
}

/*
 * Permanently take a reference on the parent of the SDRAM clock.
 *
 * While the SDRAM is being driven by its dedicated PLL most of the
 * time, there is a little loop running in the firmware that
 * periodically switches the SDRAM to using our CM clock to do PVT
 * recalibration, with the assumption that the previously configured
 * SDRAM parent is still enabled and running.
 */
static void bcm2835_mark_sdc_parent_critical(struct rt_clk_cell *cell)
{
    struct rt_clk_cell *parent = rt_clk_cell_get_parent(cell);

    if (parent)
    {
        rt_clk_prepare_enable(parent->clk);
    }
}

static rt_err_t bcm2835_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t value;
    struct rt_clk_cell *cell;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *fw_np;
    struct bcm2835_clock_data *cdata;
    const struct cprman_soc_data *pdata = pdev->id->data;
    struct bcm2835_cprman *cprman = rt_calloc(1, sizeof(*cprman));

    if (!cprman)
    {
        return -RT_ENOMEM;
    }

    pdata = pdev->id->data;
    cprman->soc = pdata->soc;

    cprman->regs = rt_dm_dev_iomap(dev, 0);

    if (!cprman->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((fw_np = rt_ofw_parse_phandle(np, "firmware", 0)))
    {
        if (!(cprman->fw = rpi_firmware_get(fw_np)))
        {
            err = -RT_ENOSYS;
            goto _fail;
        }

        rt_ofw_node_put(fw_np);
    }

    /* Mux DSI0 clock to PLLD */
    cprman_write(cprman, CM_DSI0HSCK, 1);

    rt_memset(bcm2835_clk_claimed, 0, sizeof(bcm2835_clk_claimed));

    for (int i = 0; !rt_dm_dev_prop_read_u32_index(dev, "claim-clocks", i, &value); ++i)
    {
        bcm2835_clk_claimed[value]= RT_TRUE;
    }

    rt_memcpy(cprman->real_parent_names, cprman_parent_names, sizeof(cprman_parent_names));

    for (int i = 0; i < RT_ARRAY_SIZE(cprman_parent_names); ++i)
    {
        if (!(cprman->real_parent_names[i] = rt_ofw_clk_get_parent_name(np, i)))
        {
            break;
        }
    }

    /*
     * Make sure the external oscillator has been registered.
     *
     * The other (DSI) clocks are not present on older device
     * trees, which we still need to support for backwards
     * compatibility.
     */
    if (!cprman->real_parent_names[0])
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(bcm2835_clk_cell); ++i)
    {
        cell = bcm2835_clk_cell[i];

        if (!cell)
        {
            continue;
        }

        cdata = cell_to_bcm2835_clock_data(cell);

        if (cdata->supported & cprman->soc)
        {
            cdata->cprman = cprman;

            if (cdata->init)
            {
                cdata->init(cprman, cdata);
            }
        }
        else
        {
            bcm2835_clk_cell[i] = RT_NULL;
        }
    }

    cprman->parent.dev = dev;
    cprman->parent.cells = bcm2835_clk_cell;
    cprman->parent.cells_nr = RT_ARRAY_SIZE(bcm2835_clk_cell);

    if ((err = rt_clk_register(&cprman->parent)))
    {
        goto _fail;
    }

    bcm2835_mark_sdc_parent_critical(bcm2835_clk_cell[BCM2835_CLOCK_SDRAM]);

    return RT_EOK;

_fail:
    if (cprman->fw)
    {
        rpi_firmware_put(cprman->fw);
    }

    if (cprman->regs)
    {
        rt_iounmap(cprman->regs);
    }

    rt_free(cprman);

    return err;
}

static const struct cprman_soc_data cprman_bcm2835_plat_data =
{
    .soc = SOC_TYPE_BCM2835,
};

static const struct cprman_soc_data cprman_bcm2711_plat_data =
{
    .soc = SOC_TYPE_BCM2711,
};

static const struct rt_ofw_node_id bcm2835_clk_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-cprman", .data = &cprman_bcm2835_plat_data },
    { .compatible = "brcm,bcm2711-cprman", .data = &cprman_bcm2711_plat_data },
    { /* Sentinel */ }
};

static struct rt_platform_driver clk_bcm2835_driver =
{
    .name = "clk-bcm2835",
    .ids = bcm2835_clk_ofw_ids,

    .probe = bcm2835_clk_probe,
};

static int clk_bcm2835_register(void)
{
    rt_platform_driver_register(&clk_bcm2835_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(clk_bcm2835_register);
