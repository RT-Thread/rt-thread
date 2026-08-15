/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "clk.rp1"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <cpuport.h>
#include <dt-bindings/clock/rp1.h>

#define PLL_SYS_CS                      0x08000
#define PLL_SYS_PWR                     0x08004
#define PLL_SYS_FBDIV_INT               0x08008
#define PLL_SYS_FBDIV_FRAC              0x0800c
#define PLL_SYS_PRIM                    0x08010
#define PLL_SYS_SEC                     0x08014

#define PLL_AUDIO_CS                    0x0c000
#define PLL_AUDIO_PWR                   0x0c004
#define PLL_AUDIO_FBDIV_INT             0x0c008
#define PLL_AUDIO_FBDIV_FRAC            0x0c00c
#define PLL_AUDIO_PRIM                  0x0c010
#define PLL_AUDIO_SEC                   0x0c014
#define PLL_AUDIO_TERN                  0x0c018

#define PLL_VIDEO_CS                    0x10000
#define PLL_VIDEO_PWR                   0x10004
#define PLL_VIDEO_FBDIV_INT             0x10008
#define PLL_VIDEO_FBDIV_FRAC            0x1000c
#define PLL_VIDEO_PRIM                  0x10010
#define PLL_VIDEO_SEC                   0x10014

#define GPCLK_OE_CTRL                   0x00000

#define CLK_SYS_CTRL                    0x00014
#define CLK_SYS_DIV_INT                 0x00018
#define CLK_SYS_SEL                     0x00020

#define CLK_SLOW_SYS_CTRL               0x00024
#define CLK_SLOW_SYS_DIV_INT            0x00028
#define CLK_SLOW_SYS_SEL                0x00030

#define CLK_DMA_CTRL                    0x00044
#define CLK_DMA_DIV_INT                 0x00048
#define CLK_DMA_SEL                     0x00050

#define CLK_UART_CTRL                   0x00054
#define CLK_UART_DIV_INT                0x00058
#define CLK_UART_SEL                    0x00060

#define CLK_ETH_CTRL                    0x00064
#define CLK_ETH_DIV_INT                 0x00068
#define CLK_ETH_SEL                     0x00070

#define CLK_PWM0_CTRL                   0x00074
#define CLK_PWM0_DIV_INT                0x00078
#define CLK_PWM0_DIV_FRAC               0x0007c
#define CLK_PWM0_SEL                    0x00080

#define CLK_PWM1_CTRL                   0x00084
#define CLK_PWM1_DIV_INT                0x00088
#define CLK_PWM1_DIV_FRAC               0x0008c
#define CLK_PWM1_SEL                    0x00090

#define CLK_AUDIO_IN_CTRL               0x00094
#define CLK_AUDIO_IN_DIV_INT            0x00098
#define CLK_AUDIO_IN_SEL                0x000a0

#define CLK_AUDIO_OUT_CTRL              0x000a4
#define CLK_AUDIO_OUT_DIV_INT           0x000a8
#define CLK_AUDIO_OUT_SEL               0x000b0

#define CLK_I2S_CTRL                    0x000b4
#define CLK_I2S_DIV_INT                 0x000b8
#define CLK_I2S_SEL                     0x000c0

#define CLK_MIPI0_CFG_CTRL              0x000c4
#define CLK_MIPI0_CFG_DIV_INT           0x000c8
#define CLK_MIPI0_CFG_SEL               0x000d0

#define CLK_MIPI1_CFG_CTRL              0x000d4
#define CLK_MIPI1_CFG_DIV_INT           0x000d8
#define CLK_MIPI1_CFG_SEL               0x000e0

#define CLK_PCIE_AUX_CTRL               0x000e4
#define CLK_PCIE_AUX_DIV_INT            0x000e8
#define CLK_PCIE_AUX_SEL                0x000f0

#define CLK_USBH0_MICROFRAME_CTRL       0x000f4
#define CLK_USBH0_MICROFRAME_DIV_INT    0x000f8
#define CLK_USBH0_MICROFRAME_SEL        0x00100

#define CLK_USBH1_MICROFRAME_CTRL       0x00104
#define CLK_USBH1_MICROFRAME_DIV_INT    0x00108
#define CLK_USBH1_MICROFRAME_SEL        0x00110

#define CLK_USBH0_SUSPEND_CTRL          0x00114
#define CLK_USBH0_SUSPEND_DIV_INT       0x00118
#define CLK_USBH0_SUSPEND_SEL           0x00120

#define CLK_USBH1_SUSPEND_CTRL          0x00124
#define CLK_USBH1_SUSPEND_DIV_INT       0x00128
#define CLK_USBH1_SUSPEND_SEL           0x00130

#define CLK_ETH_TSU_CTRL                0x00134
#define CLK_ETH_TSU_DIV_INT             0x00138
#define CLK_ETH_TSU_SEL                 0x00140

#define CLK_ADC_CTRL                    0x00144
#define CLK_ADC_DIV_INT                 0x00148
#define CLK_ADC_SEL                     0x00150

#define CLK_SDIO_TIMER_CTRL             0x00154
#define CLK_SDIO_TIMER_DIV_INT          0x00158
#define CLK_SDIO_TIMER_SEL              0x00160

#define CLK_SDIO_ALT_SRC_CTRL           0x00164
#define CLK_SDIO_ALT_SRC_DIV_INT        0x00168
#define CLK_SDIO_ALT_SRC_SEL            0x00170

#define CLK_GP0_CTRL                    0x00174
#define CLK_GP0_DIV_INT                 0x00178
#define CLK_GP0_DIV_FRAC                0x0017c
#define CLK_GP0_SEL                     0x00180

#define CLK_GP1_CTRL                    0x00184
#define CLK_GP1_DIV_INT                 0x00188
#define CLK_GP1_DIV_FRAC                0x0018c
#define CLK_GP1_SEL                     0x00190

#define CLK_GP2_CTRL                    0x00194
#define CLK_GP2_DIV_INT                 0x00198
#define CLK_GP2_DIV_FRAC                0x0019c
#define CLK_GP2_SEL                     0x001a0

#define CLK_GP3_CTRL                    0x001a4
#define CLK_GP3_DIV_INT                 0x001a8
#define CLK_GP3_DIV_FRAC                0x001ac
#define CLK_GP3_SEL                     0x001b0

#define CLK_GP4_CTRL                    0x001b4
#define CLK_GP4_DIV_INT                 0x001b8
#define CLK_GP4_DIV_FRAC                0x001bc
#define CLK_GP4_SEL                     0x001c0

#define CLK_GP5_CTRL                    0x001c4
#define CLK_GP5_DIV_INT                 0x001c8
#define CLK_GP5_DIV_FRAC                0x001cc
#define CLK_GP5_SEL                     0x001d0

#define CLK_SYS_RESUS_CTRL              0x0020c

#define CLK_SLOW_SYS_RESUS_CTRL         0x00214

#define FC0_REF_KHZ                     0x0021c
#define FC0_MIN_KHZ                     0x00220
#define FC0_MAX_KHZ                     0x00224
#define FC0_DELAY                       0x00228
#define FC0_INTERVAL                    0x0022c
#define FC0_SRC                         0x00230
#define FC0_STATUS                      0x00234
#define FC0_RESULT                      0x00238
#define FC_SIZE                         0x20
#define FC_COUNT                        8
#define FC_NUM(idx, off)                ((idx) * 32 + (off))

#define AUX_SEL                         1

#define VIDEO_CLOCKS_OFFSET             0x4000
#define VIDEO_CLK_VEC_CTRL              (VIDEO_CLOCKS_OFFSET + 0x0000)
#define VIDEO_CLK_VEC_DIV_INT           (VIDEO_CLOCKS_OFFSET + 0x0004)
#define VIDEO_CLK_VEC_SEL               (VIDEO_CLOCKS_OFFSET + 0x000c)
#define VIDEO_CLK_DPI_CTRL              (VIDEO_CLOCKS_OFFSET + 0x0010)
#define VIDEO_CLK_DPI_DIV_INT           (VIDEO_CLOCKS_OFFSET + 0x0014)
#define VIDEO_CLK_DPI_SEL               (VIDEO_CLOCKS_OFFSET + 0x001c)
#define VIDEO_CLK_MIPI0_DPI_CTRL        (VIDEO_CLOCKS_OFFSET + 0x0020)
#define VIDEO_CLK_MIPI0_DPI_DIV_INT     (VIDEO_CLOCKS_OFFSET + 0x0024)
#define VIDEO_CLK_MIPI0_DPI_DIV_FRAC    (VIDEO_CLOCKS_OFFSET + 0x0028)
#define VIDEO_CLK_MIPI0_DPI_SEL         (VIDEO_CLOCKS_OFFSET + 0x002c)
#define VIDEO_CLK_MIPI1_DPI_CTRL        (VIDEO_CLOCKS_OFFSET + 0x0030)
#define VIDEO_CLK_MIPI1_DPI_DIV_INT     (VIDEO_CLOCKS_OFFSET + 0x0034)
#define VIDEO_CLK_MIPI1_DPI_DIV_FRAC    (VIDEO_CLOCKS_OFFSET + 0x0038)
#define VIDEO_CLK_MIPI1_DPI_SEL         (VIDEO_CLOCKS_OFFSET + 0x003c)

#define DIV_INT_8BIT_MAX                0x000000ffU /* max divide for most clocks */
#define DIV_INT_16BIT_MAX               0x0000ffffU /* max divide for GPx, PWM */
#define DIV_INT_24BIT_MAX               0x00ffffffU /* max divide for CLK_SYS */

#define FC0_STATUS_DONE                 RT_BIT(4)
#define FC0_STATUS_RUNNING              RT_BIT(8)
#define FC0_RESULT_FRAC_SHIFT           5

#define PLL_PRIM_DIV1_SHIFT             16
#define PLL_PRIM_DIV1_MASK              0x00070000
#define PLL_PRIM_DIV2_SHIFT             12
#define PLL_PRIM_DIV2_MASK              0x00007000

#define PLL_SEC_DIV_SHIFT               8
#define PLL_SEC_DIV_WIDTH               5
#define PLL_SEC_DIV_MASK                0x00001f00

#define PLL_CS_LOCK                     RT_BIT(31)
#define PLL_CS_REFDIV_SHIFT             0

#define PLL_PWR_PD                      RT_BIT(0)
#define PLL_PWR_DACPD                   RT_BIT(1)
#define PLL_PWR_DSMPD                   RT_BIT(2)
#define PLL_PWR_POSTDIVPD               RT_BIT(3)
#define PLL_PWR_4PHASEPD                RT_BIT(4)
#define PLL_PWR_VCOPD                   RT_BIT(5)
#define PLL_PWR_MASK                    0x0000003f

#define PLL_SEC_RST                     RT_BIT(16)
#define PLL_SEC_IMPL                    RT_BIT(31)

/* PLL phase output for both PRI and SEC */
#define PLL_PH_EN                       RT_BIT(4)
#define PLL_PH_PHASE_SHIFT              0

#define RP1_PLL_PHASE_0                 0
#define RP1_PLL_PHASE_90                1
#define RP1_PLL_PHASE_180               2
#define RP1_PLL_PHASE_270               3

/* Clock fields for all clocks */
#define CLK_CTRL_ENABLE                 RT_BIT(11)
#define CLK_CTRL_AUXSRC_MASK            0x000003e0
#define CLK_CTRL_AUXSRC_SHIFT           5
#define CLK_CTRL_SRC_SHIFT              0
#define CLK_DIV_FRAC_BITS               16

#define KHz                             1000
#define MHz                             (KHz * KHz)
#define RP1_XOSC_RATE                   19200000
#define LOCK_TIMEOUT_NS                 100000000
#define FC_TIMEOUT_NS                   100000000

#define MAX_CLK_PARENTS                 16

#define ABS_DIFF(a, b)                  ((a) > (b) ? (a) - (b) : (b) - (a))
#define DIV_NEAREST(a, b)               (((a) + ((b) >> 1)) / (b))
#define DIV_U64_NEAREST(a, b)           rt_div_u64(((a) + ((b) >> 1)), (b))

struct clk_div_table
{
    rt_uint32_t val;
    rt_uint32_t div;
};

struct rp1_clockman
{
    struct rt_clk_node parent;

    void *regs;

    struct rt_clk_cell *clk_cell_xosc;
    struct rt_clk_cell *clk_cell_audio;
    struct rt_clk_cell *clk_cell_i2s;
    struct rt_clk_cell *clk_cell_slow_sys;
};

#define raw_to_rp1_clockman(raw) rt_container_of(raw, struct rp1_clockman, parent)

#define RP1_CLK_BASE \
    struct rt_clk_cell cell; \
    void (*init)(struct rp1_clockman *clockman, struct rt_clk_cell *cell);

struct rp1_clk_common
{
    RP1_CLK_BASE;
};

rt_inline rt_uint32_t set_register_field(rt_uint32_t reg, rt_uint32_t val,
        rt_uint32_t mask, rt_uint32_t shift)
{
    reg &= ~mask;
    reg |= (val << shift) & mask;

    return reg;
}

rt_inline void clockman_write(struct rp1_clockman *clockman,
        rt_uint32_t reg, rt_uint32_t val)
{
    HWREG32(clockman->regs + reg) = val;
}

rt_inline rt_uint32_t clockman_read(struct rp1_clockman *clockman, rt_uint32_t reg)
{
    return HWREG32(clockman->regs + reg);
}

struct rp1_pll_core_data
{
    RP1_CLK_BASE;

    rt_ubase_t cached_rate;

    rt_uint32_t cs_reg;
    rt_uint32_t pwr_reg;
    rt_uint32_t fbdiv_int_reg;
    rt_uint32_t fbdiv_frac_reg;
    rt_uint32_t fc0_src;
};

#define cell_to_rp1_pll_core_data(cell) rt_container_of(cell, struct rp1_pll_core_data, cell)

static rt_err_t rp1_pll_core_on(struct rt_clk_cell *cell)
{
    rt_tick_t timeout;
    rt_uint32_t fbdiv_frac;
    struct rp1_pll_core_data *pll_core = cell_to_rp1_pll_core_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    if (!(clockman_read(clockman, pll_core->cs_reg) & PLL_CS_LOCK))
    {
        /* Reset to a known state. */
        clockman_write(clockman, pll_core->pwr_reg, PLL_PWR_MASK);
        clockman_write(clockman, pll_core->fbdiv_int_reg, 20);
        clockman_write(clockman, pll_core->fbdiv_frac_reg, 0);
        clockman_write(clockman, pll_core->cs_reg, 1 << PLL_CS_REFDIV_SHIFT);
    }

    /* Come out of reset. */
    fbdiv_frac = clockman_read(clockman, pll_core->fbdiv_frac_reg);
    clockman_write(clockman, pll_core->pwr_reg, fbdiv_frac ? 0 : PLL_PWR_DSMPD);

    /* Wait for the PLL to lock. */
    timeout = rt_tick_from_millisecond(LOCK_TIMEOUT_NS / 1000000);
    timeout += rt_tick_get();

    while (!(clockman_read(clockman, pll_core->cs_reg) & PLL_CS_LOCK))
    {
        if (rt_tick_get() > timeout)
        {
            LOG_E("%s: can't lock PLL", cell->name);
            return -RT_ETIMEOUT;
        }

        rt_hw_cpu_relax();
    }

    return RT_EOK;
}

static void rp1_pll_core_off(struct rt_clk_cell *cell)
{
    struct rp1_pll_core_data *pll_core = cell_to_rp1_pll_core_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    clockman_write(clockman, pll_core->pwr_reg, 0);
}

static rt_bool_t rp1_pll_core_is_on(struct rt_clk_cell *cell)
{
    rt_uint32_t pwr;
    struct rp1_pll_core_data *pll_core = cell_to_rp1_pll_core_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    pwr = clockman_read(clockman, pll_core->pwr_reg);

    return (pwr & PLL_PWR_PD) || (pwr & PLL_PWR_POSTDIVPD);
}

static rt_ubase_t rp1_pll_core_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_ubase_t calc_rate;
    rt_uint32_t fbdiv_int, fbdiv_frac;
    struct rp1_pll_core_data *pll_core = cell_to_rp1_pll_core_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    fbdiv_int = clockman_read(clockman, pll_core->fbdiv_int_reg);
    fbdiv_frac = clockman_read(clockman, pll_core->fbdiv_frac_reg);
    calc_rate = ((rt_uint64_t)parent_rate * (((rt_uint64_t)fbdiv_int << 24) + fbdiv_frac) + (1 << 23)) >> 24;

    return calc_rate;
}

static rt_ubase_t get_pll_core_divider(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate,
        rt_uint32_t *div_int, rt_uint32_t *div_frac)
{
    rt_ubase_t calc_rate;
    rt_uint32_t fbdiv_int, fbdiv_frac;
    rt_uint64_t div_fp64; /* 32.32 fixed point fraction. */

    /* Factor of reference clock to VCO frequency. */
    div_fp64 = (rt_uint64_t)rate << 32;
    div_fp64 = DIV_U64_NEAREST(div_fp64, parent_rate);

    /* Round the fractional component at 24 bits. */
    div_fp64 += 1 << (32 - 24 - 1);

    fbdiv_int = div_fp64 >> 32;
    fbdiv_frac = (div_fp64 >> (32 - 24)) & 0xffffff;

    calc_rate = ((rt_uint64_t)parent_rate * (((rt_uint64_t)fbdiv_int << 24) + fbdiv_frac) + (1 << 23)) >> 24;

    *div_int = fbdiv_int;
    *div_frac = fbdiv_frac;

    return calc_rate;
}

static rt_base_t rp1_pll_core_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    rt_base_t calc_rate;
    rt_uint32_t fbdiv_int, fbdiv_frac;

    calc_rate = get_pll_core_divider(cell, rate, *parent_rate, &fbdiv_int, &fbdiv_frac);

    return calc_rate;
}

static rt_err_t rp1_pll_core_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_ubase_t calc_rate;
    rt_uint32_t fbdiv_int, fbdiv_frac;
    struct rp1_pll_core_data *pll_core = cell_to_rp1_pll_core_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    /* Disable dividers to start with. */
    clockman_write(clockman, pll_core->fbdiv_int_reg, 0);
    clockman_write(clockman, pll_core->fbdiv_frac_reg, 0);

    calc_rate = get_pll_core_divider(cell, rate, parent_rate, &fbdiv_int, &fbdiv_frac);

    clockman_write(clockman, pll_core->pwr_reg, fbdiv_frac ? 0 : PLL_PWR_DSMPD);
    clockman_write(clockman, pll_core->fbdiv_int_reg, fbdiv_int);
    clockman_write(clockman, pll_core->fbdiv_frac_reg, fbdiv_frac);

    pll_core->cached_rate = calc_rate;

    /* Don't need to divide ref unless parent_rate > (output freq / 16) */
    clockman_write(clockman, pll_core->cs_reg,
                   clockman_read(clockman, pll_core->cs_reg) | (1 << PLL_CS_REFDIV_SHIFT));

    return RT_EOK;
}

static const struct rt_clk_ops rp1_pll_core_ops =
{
    .prepare = rp1_pll_core_on,
    .unprepare = rp1_pll_core_off,
    .is_prepared = rp1_pll_core_is_on,
    .recalc_rate = rp1_pll_core_recalc_rate,
    .round_rate = rp1_pll_core_round_rate,
    .set_rate = rp1_pll_core_set_rate,
};

static void rp1_init_pll_core(struct rp1_clockman *clockman, struct rt_clk_cell *cell)
{
    cell->parents_nr = 1;
    cell->parent_name = "xosc";
    cell->ops = &rp1_pll_core_ops;
    cell->flags |= RT_CLK_F_IS_CRITICAL;
}

#define REGISTER_PLL_CORE(...) (void *)&(struct rp1_pll_core_data){ .init = rp1_init_pll_core, __VA_ARGS__ }

struct rp1_pll_data
{
    RP1_CLK_BASE;

    rt_ubase_t cached_rate;

    rt_uint32_t ctrl_reg;
    rt_uint32_t fc0_src;
};

#define cell_to_rp1_pll_data(cell) rt_container_of(cell, struct rp1_pll_data, cell)

static rt_ubase_t rp1_pll_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint32_t prim, prim_div1, prim_div2;
    struct rp1_pll_data *pll = cell_to_rp1_pll_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    prim = clockman_read(clockman, pll->ctrl_reg);
    prim_div1 = (prim & PLL_PRIM_DIV1_MASK) >> PLL_PRIM_DIV1_SHIFT;
    prim_div2 = (prim & PLL_PRIM_DIV2_MASK) >> PLL_PRIM_DIV2_SHIFT;

    if (!prim_div1 || !prim_div2)
    {
        LOG_E("%s: zero divider value", cell->name);
        return 0;
    }

    return RT_DIV_ROUND_CLOSEST(parent_rate, prim_div1 * prim_div2);
}

static void get_pll_prim_dividers(rt_ubase_t rate, rt_ubase_t parent_rate,
        rt_uint32_t *divider1, rt_uint32_t *divider2)
{
    rt_base_t rate_diff, calc_rate;
    rt_uint32_t div1, div2, best_div1 = 7, best_div2 = 7;
    rt_ubase_t best_rate_diff = ABS_DIFF(RT_DIV_ROUND_CLOSEST(parent_rate, best_div1 * best_div2), rate);

    for (div1 = 1; div1 <= 7; ++div1)
    {
        for (div2 = 1; div2 <= div1; ++div2)
        {
            calc_rate = RT_DIV_ROUND_CLOSEST(parent_rate, div1 * div2);
            rate_diff = ABS_DIFF(calc_rate, rate);

            if (calc_rate == rate)
            {
                best_div1 = div1;
                best_div2 = div2;
                goto _done;
            }
            else if (rate_diff < best_rate_diff)
            {
                best_div1 = div1;
                best_div2 = div2;
                best_rate_diff = rate_diff;
            }
        }
    }

_done:
    *divider1 = best_div1;
    *divider2 = best_div2;
}

static rt_ubase_t rp1_get_xosc_rate(struct rp1_clockman *clockman)
{
    if (clockman->clk_cell_xosc)
    {
        return rt_clk_cell_get_rate(clockman->clk_cell_xosc);
    }

    return RP1_XOSC_RATE;
}

static rt_ubase_t calc_core_pll_rate(struct rp1_clockman *clockman,
        rt_ubase_t target_rate, int *pdiv_prim, int *pdiv_clk)
{
    const rt_ubase_t xosc_rate = rp1_get_xosc_rate(clockman);
    const rt_ubase_t core_max = 2400000000;
    const rt_ubase_t core_min = xosc_rate * 16;
    static const int prim_divs[] =
    {
        2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 16,
        18, 20, 21, 24, 25, 28, 30, 35, 36, 42, 49,
    };
    rt_ubase_t core_rate = 0, best_rate = core_max + 1;
    int div_int, div_frac, best_div_prim = 1, best_div_clk = 1;
    rt_uint64_t div;

    /* Given the target rate, choose a set of divisors/multipliers */
    for (int i = 0; i < RT_ARRAY_SIZE(prim_divs); ++i)
    {
        int div_clk, div_prim = prim_divs[i];

        for (div_clk = 1; div_clk <= 256; ++div_clk)
        {
            core_rate = target_rate * div_clk * div_prim;
            if (core_rate >= core_min)
            {
                if (core_rate < best_rate)
                {
                    best_rate = core_rate;
                    best_div_prim = div_prim;
                    best_div_clk = div_clk;
                }
                break;
            }
        }
    }

    if (best_rate < core_max)
    {
        div = ((best_rate << 24) + xosc_rate / 2) / xosc_rate;
        div_int = div >> 24;
        div_frac = div % (1 << 24);
        core_rate = (xosc_rate * ((div_int << 24) + div_frac) + (1 << 23)) >> 24;
    }
    else
    {
        core_rate = 0;
    }

    if (pdiv_prim)
    {
        *pdiv_prim = best_div_prim;
    }
    if (pdiv_clk)
    {
        *pdiv_clk = best_div_clk;
    }

    return core_rate;
}

static rt_base_t rp1_pll_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    int div_prim, div_clk;
    rt_uint32_t div1, div2;
    rt_ubase_t audio_rate, core_rate;
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    core_rate = calc_core_pll_rate(clockman, rate, &div_prim, &div_clk);
    audio_rate = DIV_NEAREST(core_rate, div_prim);

    if (cell == clockman->clk_cell_audio && audio_rate == rate)
    {
        *parent_rate = audio_rate;
    }

    get_pll_prim_dividers(rate, *parent_rate, &div1, &div2);

    return RT_DIV_ROUND_CLOSEST(*parent_rate, div1 * div2);
}

static rt_err_t rp1_pll_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t prim, prim_div1, prim_div2;
    struct rp1_pll_data *pll = cell_to_rp1_pll_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    get_pll_prim_dividers(rate, parent_rate, &prim_div1, &prim_div2);

    prim = clockman_read(clockman, pll->ctrl_reg);
    prim = set_register_field(prim, prim_div1, PLL_PRIM_DIV1_MASK, PLL_PRIM_DIV1_SHIFT);
    prim = set_register_field(prim, prim_div2, PLL_PRIM_DIV2_MASK, PLL_PRIM_DIV2_SHIFT);
    clockman_write(clockman, pll->ctrl_reg, prim);

    return RT_EOK;
}

static const struct rt_clk_ops rp1_pll_ops =
{
    .recalc_rate = rp1_pll_recalc_rate,
    .round_rate = rp1_pll_round_rate,
    .set_rate = rp1_pll_set_rate,
};

static void rp1_init_pll(struct rp1_clockman *clockman, struct rt_clk_cell *cell)
{
    cell->ops = &rp1_pll_ops;
}

#define REGISTER_PLL(...) (void *)&(struct rp1_pll_data){ .init = rp1_init_pll, __VA_ARGS__ }

struct rp1_pll_div_data
{
    RP1_CLK_BASE;

    rt_ubase_t cached_rate;

    rt_uint32_t ctrl_reg;
    rt_uint32_t fc0_src;
};

#define cell_to_rp1_pll_div_data(cell) rt_container_of(cell, struct rp1_pll_div_data, cell)

static const struct clk_div_table pll_sec_div_table[] =
{
    { 0x00, 19 },
    { 0x01, 19 },
    { 0x02, 19 },
    { 0x03, 19 },
    { 0x04, 19 },
    { 0x05, 19 },
    { 0x06, 19 },
    { 0x07, 19 },
    { 0x08,  8 },
    { 0x09,  9 },
    { 0x0a, 10 },
    { 0x0b, 11 },
    { 0x0c, 12 },
    { 0x0d, 13 },
    { 0x0e, 14 },
    { 0x0f, 15 },
    { 0x10, 16 },
    { 0x11, 17 },
    { 0x12, 18 },
    { 0x13, 19 },
    { 0x14, 19 },
    { 0x15, 19 },
    { 0x16, 19 },
    { 0x17, 19 },
    { 0x18, 19 },
    { 0x19, 19 },
    { 0x1a, 19 },
    { 0x1b, 19 },
    { 0x1c, 19 },
    { 0x1d, 19 },
    { 0x1e, 19 },
    { 0x1f, 19 },
};

static rt_err_t rp1_pll_divider_on(struct rt_clk_cell *cell)
{
    struct rp1_pll_div_data *pll_div = cell_to_rp1_pll_div_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    clockman_write(clockman, pll_div->ctrl_reg,
                   clockman_read(clockman, pll_div->ctrl_reg) & ~PLL_SEC_RST);

    return RT_EOK;
}

static void rp1_pll_divider_off(struct rt_clk_cell *cell)
{
    struct rp1_pll_div_data *pll_div = cell_to_rp1_pll_div_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    clockman_write(clockman, pll_div->ctrl_reg,
                   clockman_read(clockman, pll_div->ctrl_reg) | PLL_SEC_RST);
}

static rt_bool_t rp1_pll_divider_is_on(struct rt_clk_cell *cell)
{
    struct rp1_pll_div_data *pll_div = cell_to_rp1_pll_div_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    return !(clockman_read(clockman, pll_div->ctrl_reg) & PLL_SEC_RST);
}

static rt_ubase_t rp1_pll_divider_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint32_t val, div;
    struct rp1_pll_div_data *pll_div = cell_to_rp1_pll_div_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    val = clockman_read(clockman, pll_div->ctrl_reg) >> PLL_SEC_DIV_SHIFT;
    val &= (1 << (PLL_SEC_DIV_WIDTH)) - 1;

    div = val + 1;

    for (int i = 0; i < RT_ARRAY_SIZE(pll_sec_div_table); ++i)
    {
        const struct clk_div_table *clkt = &pll_sec_div_table[i];

        if (clkt->val == val)
        {
            div = clkt->div;
            break;
        }
    }

    return div ? RT_DIV_ROUND_UP_ULL((rt_uint64_t)parent_rate, div) : parent_rate;
}

static rt_base_t rp1_pll_divider_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    int bestdiv = 0, div, up, down;
    rt_ubase_t up_rate, down_rate, maxdiv = 0;
    rt_uint32_t mask = (1 << (PLL_SEC_DIV_WIDTH)) - 1;

    if (!rate)
    {
        rate = 1;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(pll_sec_div_table); ++i)
    {
        const struct clk_div_table *clkt = &pll_sec_div_table[i];

        if (clkt->div > maxdiv && clkt->val <= mask)
        {
            maxdiv = clkt->div;
        }
    }

    up = RT_DIV_ROUND_UP_ULL((rt_uint64_t)*parent_rate, rate);
    down = *parent_rate / rate;

    /* Round up table */
    div = up;
    up = RT_UINT32_MAX >> 1;

    for (int i = 0; i < RT_ARRAY_SIZE(pll_sec_div_table); ++i)
    {
        const struct clk_div_table *clkt = &pll_sec_div_table[i];

        if (clkt->div == div)
        {
            up = clkt->div;
            break;
        }
        else if (clkt->div < div)
        {
            continue;
        }

        if (clkt->div - div < up - div)
        {
            up = clkt->div;
        }
    }

    /* Round down table */
    div = down;
    down = RT_UINT32_MAX;

    for (int i = 0; i < RT_ARRAY_SIZE(pll_sec_div_table); ++i)
    {
        const struct clk_div_table *clkt = &pll_sec_div_table[i];

        if (clkt->div < down)
        {
            down = clkt->div;
        }
    }

    for (int i = 0; i < RT_ARRAY_SIZE(pll_sec_div_table); ++i)
    {
        const struct clk_div_table *clkt = &pll_sec_div_table[i];

        if (clkt->div == div)
        {
            down = clkt->div;
            break;
        }
        else if (clkt->div > div)
        {
            continue;
        }

        if (div - clkt->div < div - down)
        {
            down = clkt->div;
        }
    }

    up_rate = RT_DIV_ROUND_UP_ULL((rt_uint64_t)*parent_rate, up);
    down_rate = RT_DIV_ROUND_UP_ULL((rt_uint64_t)*parent_rate, down);

    bestdiv = (rate - up_rate) <= (down_rate - rate) ? up : down;
    bestdiv = bestdiv == 0 ? 1 : bestdiv;
    bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;

    return RT_DIV_ROUND_UP_ULL((rt_uint64_t)*parent_rate, div);
}

static rt_err_t rp1_pll_divider_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t div, sec;
    struct rp1_pll_div_data *pll_div = cell_to_rp1_pll_div_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    div = RT_DIV_ROUND_UP_ULL(parent_rate, rate);
    div = rt_clamp(div, 8U, 19U);

    sec = clockman_read(clockman, pll_div->ctrl_reg);
    sec = set_register_field(sec, div, PLL_SEC_DIV_MASK, PLL_SEC_DIV_SHIFT);

    /* Must keep the divider in reset to change the value. */
    sec |= PLL_SEC_RST;
    clockman_write(clockman, pll_div->ctrl_reg, sec);

    sec &= ~PLL_SEC_RST;
    clockman_write(clockman, pll_div->ctrl_reg, sec);

    return RT_EOK;
}

static const struct rt_clk_ops rp1_pll_divider_ops =
{
    .prepare = rp1_pll_divider_on,
    .unprepare = rp1_pll_divider_off,
    .is_prepared = rp1_pll_divider_is_on,
    .recalc_rate = rp1_pll_divider_recalc_rate,
    .round_rate = rp1_pll_divider_round_rate,
    .set_rate = rp1_pll_divider_set_rate,
};

static void rp1_init_pll_divider(struct rp1_clockman *clockman, struct rt_clk_cell *cell)
{
    cell->ops = &rp1_pll_divider_ops;
}

#define REGISTER_PLL_DIV(...) (void *)&(struct rp1_pll_div_data){ .init = rp1_init_pll_divider, __VA_ARGS__ }

struct rp1_pll_ph_data
{
    RP1_CLK_BASE;

    rt_uint32_t phase;
    rt_uint32_t fixed_divider;
    rt_uint32_t ph_reg;
    rt_uint32_t fc0_src;
};

#define cell_to_rp1_pll_ph_data(cell) rt_container_of(cell, struct rp1_pll_ph_data, cell)

static rt_err_t rp1_pll_ph_on(struct rt_clk_cell *cell)
{
    rt_uint32_t ph_reg;
    struct rp1_pll_ph_data *pll_ph = cell_to_rp1_pll_ph_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    ph_reg = clockman_read(clockman, pll_ph->ph_reg);
    ph_reg |= pll_ph->phase << PLL_PH_PHASE_SHIFT;
    ph_reg |= PLL_PH_EN;
    clockman_write(clockman, pll_ph->ph_reg, ph_reg);

    return RT_EOK;
}

static void rp1_pll_ph_off(struct rt_clk_cell *cell)
{
    struct rp1_pll_ph_data *pll_ph = cell_to_rp1_pll_ph_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    clockman_write(clockman, pll_ph->ph_reg,
                   clockman_read(clockman, pll_ph->ph_reg) & ~PLL_PH_EN);
}

static rt_bool_t rp1_pll_ph_is_on(struct rt_clk_cell *cell)
{
    struct rp1_pll_ph_data *pll_ph = cell_to_rp1_pll_ph_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    return !!(clockman_read(clockman, pll_ph->ph_reg) & PLL_PH_EN);
}

static rt_ubase_t rp1_pll_ph_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct rp1_pll_ph_data *pll_ph = cell_to_rp1_pll_ph_data(cell);

    return parent_rate / pll_ph->fixed_divider;
}

static rt_base_t rp1_pll_ph_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    struct rp1_pll_ph_data *pll_ph = cell_to_rp1_pll_ph_data(cell);

    return *parent_rate / pll_ph->fixed_divider;
}

static rt_err_t rp1_pll_ph_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    return RT_EOK;
}

static const struct rt_clk_ops rp1_pll_ph_ops =
{
    .prepare = rp1_pll_ph_on,
    .unprepare = rp1_pll_ph_off,
    .is_prepared = rp1_pll_ph_is_on,
    .recalc_rate = rp1_pll_ph_recalc_rate,
    .round_rate = rp1_pll_ph_round_rate,
    .set_rate = rp1_pll_ph_set_rate,
};

static void rp1_init_pll_ph(struct rp1_clockman *clockman, struct rt_clk_cell *cell)
{
    cell->ops = &rp1_pll_ph_ops;
}

#define REGISTER_PLL_PH(...) (void *)&(struct rp1_pll_ph_data){ .init = rp1_init_pll_ph, __VA_ARGS__ }

struct rp1_clock_data
{
    RP1_CLK_BASE;

    rt_ubase_t cached_rate;

    int num_std_parents;
    int num_aux_parents;

    rt_uint32_t oe_mask;
    rt_uint32_t clk_src_mask;
    rt_uint32_t ctrl_reg;
    rt_uint32_t div_int_reg;
    rt_uint32_t div_frac_reg;
    rt_uint32_t sel_reg;
    rt_uint32_t div_int_max;
    rt_ubase_t max_freq;
    rt_uint32_t fc0_src;
};

#define cell_to_rp1_clock_data(cell) rt_container_of(cell, struct rp1_clock_data, cell)

static rt_err_t rp1_clock_on(struct rt_clk_cell *cell)
{
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    clockman_write(clockman, clock->ctrl_reg,
                   clockman_read(clockman, clock->ctrl_reg) | CLK_CTRL_ENABLE);

    /* If this is a GPCLK, turn on the output-enable */
    if (clock->oe_mask)
    {
        clockman_write(clockman, GPCLK_OE_CTRL,
                       clockman_read(clockman, GPCLK_OE_CTRL) | clock->oe_mask);
    }

    return RT_EOK;
}

static void rp1_clock_off(struct rt_clk_cell *cell)
{
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    clockman_write(clockman, clock->ctrl_reg,
                   clockman_read(clockman, clock->ctrl_reg) & ~CLK_CTRL_ENABLE);
    /* If this is a GPCLK, turn off the output-enable */
    if (clock->oe_mask)
    {
        clockman_write(clockman, GPCLK_OE_CTRL,
                       clockman_read(clockman, GPCLK_OE_CTRL) & ~clock->oe_mask);
    }
}

static rt_bool_t rp1_clock_is_on(struct rt_clk_cell *cell)
{
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    return !!(clockman_read(clockman, clock->ctrl_reg) & CLK_CTRL_ENABLE);
}

static rt_ubase_t rp1_clock_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_uint32_t frac;
    rt_uint64_t calc_rate, div;
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    div = clockman_read(clockman, clock->div_int_reg);
    frac = (clock->div_frac_reg != 0) ? clockman_read(clockman, clock->div_frac_reg) : 0;

    /* If the integer portion of the divider is 0, treat it as 2^16 */
    if (!div)
    {
        div = 1 << 16;
    }

    div = (div << CLK_DIV_FRAC_BITS) | (frac >> (32 - CLK_DIV_FRAC_BITS));

    calc_rate = (rt_uint64_t)parent_rate << CLK_DIV_FRAC_BITS;
    calc_rate = calc_rate / div;

    return calc_rate;
}

static rt_uint32_t rp1_clock_choose_div(rt_ubase_t rate, rt_ubase_t parent_rate,
        const struct rp1_clock_data *clock)
{
    rt_uint64_t div;

    /*
     * Due to earlier rounding, calculated parent_rate may differ from
     * expected value. Don't fail on a small discrepancy near unity divide.
     */
    if (!rate || rate > parent_rate + (parent_rate >> CLK_DIV_FRAC_BITS))
    {
        return 0;
    }

    /*
     * Always express div in fixed-point format for fractional division;
     * If no fractional divider is present, the fraction part will be zero.
     */
    if (clock->div_frac_reg)
    {
        div = (rt_uint64_t)parent_rate << CLK_DIV_FRAC_BITS;
        div = DIV_U64_NEAREST(div, rate);
    }
    else
    {
        div = DIV_U64_NEAREST(parent_rate, rate);
        div <<= CLK_DIV_FRAC_BITS;
    }

    div = rt_clamp(div,
            (rt_uint64_t)(1ULL << CLK_DIV_FRAC_BITS),
            (rt_uint64_t)clock->div_int_max << CLK_DIV_FRAC_BITS);

    return div;
}

static rt_err_t rp1_clock_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t div;
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    div = rp1_clock_choose_div(rate, parent_rate, clock);

    if (!div)
    {
        div = 1 << CLK_DIV_FRAC_BITS;
    }

    clockman_write(clockman, clock->div_int_reg, div >> CLK_DIV_FRAC_BITS);

    if (clock->div_frac_reg)
    {
        clockman_write(clockman, clock->div_frac_reg, div << (32 - CLK_DIV_FRAC_BITS));
    }

    return RT_EOK;
}

static rt_err_t rp1_clock_set_parent(struct rt_clk_cell *cell, rt_uint8_t index)
{
    rt_uint32_t ctrl;
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    ctrl = clockman_read(clockman, clock->ctrl_reg);

    if (index >= clock->num_std_parents)
    {
        /* This is an aux source request */
        if (index >= clock->num_std_parents + clock->num_aux_parents)
        {
            return -RT_EINVAL;
        }

        /* Select parent from aux list */
        ctrl = set_register_field(ctrl, index - clock->num_std_parents,
                                  CLK_CTRL_AUXSRC_MASK, CLK_CTRL_AUXSRC_SHIFT);
        /* Set src to aux list */
        ctrl = set_register_field(ctrl, AUX_SEL, clock->clk_src_mask,
                                  CLK_CTRL_SRC_SHIFT);
    }
    else
    {
        ctrl = set_register_field(ctrl, index, clock->clk_src_mask,
                                  CLK_CTRL_SRC_SHIFT);
    }

    clockman_write(clockman, clock->ctrl_reg, ctrl);

    return RT_EOK;
}

static rt_uint8_t rp1_clock_get_parent(struct rt_clk_cell *cell)
{
    rt_uint8_t parent;
    rt_uint32_t sel, ctrl;
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);
    struct rp1_clockman *clockman = raw_to_rp1_clockman(cell->clk_np);

    sel = clockman_read(clockman, clock->sel_reg);
    parent = __rt_ffs(sel) - 1;

    /* sel == 0 implies the parent clock is not enabled yet. */
    if (!sel)
    {
        /* Read the clock src from the CTRL register instead */
        ctrl = clockman_read(clockman, clock->ctrl_reg);
        parent = (ctrl & clock->clk_src_mask) >> CLK_CTRL_SRC_SHIFT;
    }

    if (parent >= clock->num_std_parents)
    {
        parent = AUX_SEL;
    }

    if (parent == AUX_SEL)
    {
        /*
         * Clock parent is an auxiliary source, so get the parent from
         * the AUXSRC register field.
         */
        ctrl = clockman_read(clockman, clock->ctrl_reg);
        parent = (ctrl & CLK_CTRL_AUXSRC_MASK) >> CLK_CTRL_AUXSRC_SHIFT;
        parent += clock->num_std_parents;
    }

    if (parent >= cell->parents_nr)
    {
        parent = 0;
    }

    return parent;
}

static const struct rt_clk_ops rp1_clk_ops =
{
    .prepare = rp1_clock_on,
    .unprepare = rp1_clock_off,
    .is_prepared = rp1_clock_is_on,
    .recalc_rate = rp1_clock_recalc_rate,
    .set_rate = rp1_clock_set_rate,
    .set_parent = rp1_clock_set_parent,
    .get_parent = rp1_clock_get_parent,
};

static void rp1_init_clock(struct rp1_clockman *clockman, struct rt_clk_cell *cell)
{
    struct rp1_clock_data *clock = cell_to_rp1_clock_data(cell);

    cell->parents_nr = clock->num_std_parents + clock->num_aux_parents;
    cell->ops = &rp1_clk_ops;
}

#define REGISTER_CLK(...) (void *)&(struct rp1_clock_data){ .init = rp1_init_clock, __VA_ARGS__ }

struct rp1_varsrc_data
{
    RP1_CLK_BASE;
    rt_ubase_t rate;
};

#define cell_to_rp1_varsrc(cell) rt_container_of(cell, struct rp1_varsrc_data, cell)

static rt_ubase_t rp1_varsrc_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct rp1_varsrc_data *varsrc = cell_to_rp1_varsrc(cell);

    return varsrc->rate;
}

static rt_base_t rp1_varsrc_round_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    return rate;
}

static rt_err_t rp1_varsrc_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    struct rp1_varsrc_data *varsrc = cell_to_rp1_varsrc(cell);

    /*
     * "varsrc" exists purely to let clock dividers know the frequency
     * of an externally-managed clock source (such as MIPI DSI byte-clock)
     * which may change at run-time as a side-effect of some other driver.
     */
    varsrc->rate = rate;

    return RT_EOK;
}

static const struct rt_clk_ops rp1_varsrc_ops =
{
    .recalc_rate = rp1_varsrc_recalc_rate,
    .round_rate = rp1_varsrc_round_rate,
    .set_rate = rp1_varsrc_set_rate,
};

static void rp1_init_varsrc(struct rp1_clockman *clockman, struct rt_clk_cell *cell)
{
    cell->parents_nr = 1;
    cell->parent_name = "xosc";
    cell->ops = &rp1_varsrc_ops;
}

#define REGISTER_VARSRC(...) (void *)&(struct rp1_varsrc_data){ .init = rp1_init_varsrc, __VA_ARGS__ }

static struct rt_clk_cell *rp1_clk_cell[] =
{
    [RP1_PLL_SYS_CORE] = REGISTER_PLL_CORE(
        .cell.name = "pll_sys_core",
        .cs_reg = PLL_SYS_CS,
        .pwr_reg = PLL_SYS_PWR,
        .fbdiv_int_reg = PLL_SYS_FBDIV_INT,
        .fbdiv_frac_reg = PLL_SYS_FBDIV_FRAC),

    [RP1_PLL_AUDIO_CORE] = REGISTER_PLL_CORE(
        .cell.name = "pll_audio_core",
        .cs_reg = PLL_AUDIO_CS,
        .pwr_reg = PLL_AUDIO_PWR,
        .fbdiv_int_reg = PLL_AUDIO_FBDIV_INT,
        .fbdiv_frac_reg = PLL_AUDIO_FBDIV_FRAC),

    [RP1_PLL_VIDEO_CORE] = REGISTER_PLL_CORE(
        .cell.name = "pll_video_core",
        .cs_reg = PLL_VIDEO_CS,
        .pwr_reg = PLL_VIDEO_PWR,
        .fbdiv_int_reg = PLL_VIDEO_FBDIV_INT,
        .fbdiv_frac_reg = PLL_VIDEO_FBDIV_FRAC),

    [RP1_PLL_SYS] = REGISTER_PLL(
        .cell.name = "pll_sys",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_sys_core",
        .ctrl_reg = PLL_SYS_PRIM,
        .fc0_src = FC_NUM(0, 2)),

    [RP1_PLL_AUDIO] = REGISTER_PLL(
        .cell.name = "pll_audio",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_audio_core",
        .cell.flags = RT_CLK_F_SET_RATE_PARENT,
        .ctrl_reg = PLL_AUDIO_PRIM,
        .fc0_src = FC_NUM(4, 2)),

    [RP1_PLL_VIDEO] = REGISTER_PLL(
        .cell.name = "pll_video",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_video_core",
        .ctrl_reg = PLL_VIDEO_PRIM,
        .fc0_src = FC_NUM(3, 2)),

    [RP1_PLL_SYS_PRI_PH] = REGISTER_PLL_PH(
        .cell.name = "pll_sys_pri_ph",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_sys",
        .ph_reg = PLL_SYS_PRIM,
        .fixed_divider = 2,
        .phase = RP1_PLL_PHASE_0,
        .fc0_src = FC_NUM(1, 2)),

    [RP1_PLL_AUDIO_PRI_PH] = REGISTER_PLL_PH(
        .cell.name = "pll_audio_pri_ph",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_audio",
        .ph_reg = PLL_AUDIO_PRIM,
        .fixed_divider = 2,
        .phase = RP1_PLL_PHASE_0,
        .fc0_src = FC_NUM(5, 1)),

    [RP1_PLL_VIDEO_PRI_PH] = REGISTER_PLL_PH(
        .cell.name = "pll_video_pri_ph",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_video",
        .ph_reg = PLL_VIDEO_PRIM,
        .fixed_divider = 2,
        .phase = RP1_PLL_PHASE_0,
        .fc0_src = FC_NUM(4, 3)),

    [RP1_PLL_SYS_SEC] = REGISTER_PLL_DIV(
        .cell.name = "pll_sys_sec",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_sys_core",
        .ctrl_reg = PLL_SYS_SEC,
        .fc0_src = FC_NUM(2, 2)),

    [RP1_PLL_AUDIO_SEC] = REGISTER_PLL_DIV(
        .cell.name = "pll_audio_sec",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_audio_core",
        .ctrl_reg = PLL_AUDIO_SEC,
        .fc0_src = FC_NUM(6, 2)),

    [RP1_PLL_VIDEO_SEC] = REGISTER_PLL_DIV(
        .cell.name = "pll_video_sec",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_video_core",
        .ctrl_reg = PLL_VIDEO_SEC,
        .fc0_src = FC_NUM(5, 3)),

    [RP1_PLL_AUDIO_TERN] = REGISTER_PLL_DIV(
        .cell.name = "pll_audio_tern",
        .cell.parents_nr = 1,
        .cell.parent_name = "pll_audio_core",
        .ctrl_reg = PLL_AUDIO_TERN,
        .fc0_src = FC_NUM(6, 2)),

    [RP1_CLK_SYS] = REGISTER_CLK(
        .cell.name = "clk_sys",
        .cell.parent_names = (const char *[]){ "xosc", "", "pll_sys" },
        .cell.flags = RT_CLK_F_IS_CRITICAL,
        .num_std_parents = 3,
        .num_aux_parents = 0,
        .ctrl_reg = CLK_SYS_CTRL,
        .div_int_reg = CLK_SYS_DIV_INT,
        .sel_reg = CLK_SYS_SEL,
        .div_int_max = DIV_INT_24BIT_MAX,
        .max_freq = 200 * MHz,
        .fc0_src = FC_NUM(0, 4),
        .clk_src_mask = 0x3),

    [RP1_CLK_SLOW_SYS] = REGISTER_CLK(
        .cell.name = "clk_slow_sys",
        .cell.parent_name = "xosc",
        .cell.flags = RT_CLK_F_IS_CRITICAL,
        .num_std_parents = 1,
        .num_aux_parents = 0,
        .ctrl_reg = CLK_SLOW_SYS_CTRL,
        .div_int_reg = CLK_SLOW_SYS_DIV_INT,
        .sel_reg = CLK_SLOW_SYS_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 50 * MHz,
        .fc0_src = FC_NUM(1, 4),
        .clk_src_mask = 0x1),

    [RP1_CLK_DMA] = REGISTER_CLK(
        .cell.name = "clk_dma",
        .cell.parent_names = (const char *[]){ "pll_sys_pri_ph", "pll_video", "xosc" },
        .num_std_parents = 0,
        .num_aux_parents = 3,
        .ctrl_reg = CLK_DMA_CTRL,
        .div_int_reg = CLK_DMA_DIV_INT,
        .sel_reg = CLK_DMA_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(2, 2)),

    [RP1_CLK_UART] = REGISTER_CLK(
        .cell.name = "clk_uart",
        .cell.parent_names = (const char *[]){ "pll_sys_pri_ph", "pll_video", "xosc" },
        .num_std_parents = 0,
        .num_aux_parents = 3,
        .ctrl_reg = CLK_UART_CTRL,
        .div_int_reg = CLK_UART_DIV_INT,
        .sel_reg = CLK_UART_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(6, 7)),

    [RP1_CLK_ETH] = REGISTER_CLK(
        .cell.name = "clk_eth",
        .cell.parent_names = (const char *[]){ "pll_sys_sec", "pll_sys", "pll_video_sec" },
        .num_std_parents = 0,
        .num_aux_parents = 3,
        .ctrl_reg = CLK_ETH_CTRL,
        .div_int_reg = CLK_ETH_DIV_INT,
        .sel_reg = CLK_ETH_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 125 * MHz,
        .fc0_src = FC_NUM(4, 6)),

    [RP1_CLK_PWM0] = REGISTER_CLK(
        .cell.name = "clk_pwm0",
        .cell.parent_names = (const char *[]){ "", "pll_video_sec", "xosc" },
        .num_std_parents = 0,
        .num_aux_parents = 3,
        .ctrl_reg = CLK_PWM0_CTRL,
        .div_int_reg = CLK_PWM0_DIV_INT,
        .div_frac_reg = CLK_PWM0_DIV_FRAC,
        .sel_reg = CLK_PWM0_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 76800 * KHz,
        .fc0_src = FC_NUM(0, 5)),

    [RP1_CLK_PWM1] = REGISTER_CLK(
        .cell.name = "clk_pwm1",
        .cell.parent_names = (const char *[]){ "", "pll_video_sec", "xosc" },
        .num_std_parents = 0,
        .num_aux_parents = 3,
        .ctrl_reg = CLK_PWM1_CTRL,
        .div_int_reg = CLK_PWM1_DIV_INT,
        .div_frac_reg = CLK_PWM1_DIV_FRAC,
        .sel_reg = CLK_PWM1_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 76800 * KHz,
        .fc0_src = FC_NUM(1, 5)),

    [RP1_CLK_AUDIO_IN] = REGISTER_CLK(
        .cell.name = "clk_audio_in",
        .cell.parent_names = (const char *[]){ "", "", "", "pll_video_sec", "xosc" },
        .num_std_parents = 0,
        .num_aux_parents = 5,
        .ctrl_reg = CLK_AUDIO_IN_CTRL,
        .div_int_reg = CLK_AUDIO_IN_DIV_INT,
        .sel_reg = CLK_AUDIO_IN_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 76800 * KHz,
        .fc0_src = FC_NUM(2, 5)),

    [RP1_CLK_AUDIO_OUT] = REGISTER_CLK(
        .cell.name = "clk_audio_out",
        .cell.parent_names = (const char *[]){ "", "pll_audio_sec", "pll_video_sec", "xosc" },
        .num_std_parents = 0,
        .num_aux_parents = 4,
        .ctrl_reg = CLK_AUDIO_OUT_CTRL,
        .div_int_reg = CLK_AUDIO_OUT_DIV_INT,
        .sel_reg = CLK_AUDIO_OUT_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 153600 * KHz,
        .fc0_src = FC_NUM(3, 5)),

    [RP1_CLK_I2S] = REGISTER_CLK(
        .cell.name = "clk_i2s",
        .cell.parent_names = (const char *[]){ "xosc", "pll_audio", "pll_audio_sec" },
        .cell.flags = RT_CLK_F_SET_RATE_PARENT,
        .num_std_parents = 0,
        .num_aux_parents = 3,
        .ctrl_reg = CLK_I2S_CTRL,
        .div_int_reg = CLK_I2S_DIV_INT,
        .sel_reg = CLK_I2S_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 50 * MHz,
        .fc0_src = FC_NUM(4, 4)),

    [RP1_CLK_MIPI0_CFG] = REGISTER_CLK(
        .cell.name = "clk_mipi0_cfg",
        .cell.parent_name = "xosc",
        .num_std_parents = 0,
        .num_aux_parents = 1,
        .ctrl_reg = CLK_MIPI0_CFG_CTRL,
        .div_int_reg = CLK_MIPI0_CFG_DIV_INT,
        .sel_reg = CLK_MIPI0_CFG_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 50 * MHz,
        .fc0_src = FC_NUM(4, 5)),

    [RP1_CLK_MIPI1_CFG] = REGISTER_CLK(
        .cell.name = "clk_mipi1_cfg",
        .cell.parent_name = "xosc",
        .num_std_parents = 0,
        .num_aux_parents = 1,
        .ctrl_reg = CLK_MIPI1_CFG_CTRL,
        .div_int_reg = CLK_MIPI1_CFG_DIV_INT,
        .sel_reg = CLK_MIPI1_CFG_SEL,
        .clk_src_mask = 1,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 50 * MHz,
        .fc0_src = FC_NUM(5, 6)),

    [RP1_CLK_ETH_TSU] = REGISTER_CLK(
        .cell.name = "clk_eth_tsu",
        .cell.parent_names = (const char *[]){ "xosc", "pll_video_sec", "", "", "", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 8,
        .ctrl_reg = CLK_ETH_TSU_CTRL,
        .div_int_reg = CLK_ETH_TSU_DIV_INT,
        .sel_reg = CLK_ETH_TSU_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 50 * MHz,
        .fc0_src = FC_NUM(5, 7)),

    [RP1_CLK_ADC] = REGISTER_CLK(
        .cell.name = "clk_adc",
        .cell.parent_name = "xosc",
        .num_std_parents = 0,
        .num_aux_parents = 1,
        .ctrl_reg = CLK_ADC_CTRL,
        .div_int_reg = CLK_ADC_DIV_INT,
        .sel_reg = CLK_ADC_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 50 * MHz,
        .fc0_src = FC_NUM(5, 5)),

    [RP1_CLK_SDIO_TIMER] = REGISTER_CLK(
        .cell.name = "clk_sdio_timer",
        .cell.parent_name = "xosc",
        .num_std_parents = 0,
        .num_aux_parents = 1,
        .ctrl_reg = CLK_SDIO_TIMER_CTRL,
        .div_int_reg = CLK_SDIO_TIMER_DIV_INT,
        .sel_reg = CLK_SDIO_TIMER_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 50 * MHz,
        .fc0_src = FC_NUM(3, 4)),

    [RP1_CLK_SDIO_ALT_SRC] = REGISTER_CLK(
        .cell.name = "clk_sdio_alt_src",
        .cell.parent_name = "pll_sys",
        .num_std_parents = 0,
        .num_aux_parents = 1,
        .ctrl_reg = CLK_SDIO_ALT_SRC_CTRL,
        .div_int_reg = CLK_SDIO_ALT_SRC_DIV_INT,
        .sel_reg = CLK_SDIO_ALT_SRC_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 200 * MHz,
        .fc0_src = FC_NUM(5, 4)),

    [RP1_CLK_GP0] = REGISTER_CLK(
        .cell.name = "clk_gp0",
        .cell.parent_names = (const char *[]){ "xosc", "", "", "", "", "", "pll_sys", "", "", "", "clk_i2s", "clk_adc", "", "", "", "clk_sys" },
        .num_std_parents = 0,
        .num_aux_parents = 16,
        .oe_mask = RT_BIT(0),
        .ctrl_reg = CLK_GP0_CTRL,
        .div_int_reg = CLK_GP0_DIV_INT,
        .div_frac_reg = CLK_GP0_DIV_FRAC,
        .sel_reg = CLK_GP0_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(0, 1)),

    [RP1_CLK_GP1] = REGISTER_CLK(
        .cell.name = "clk_gp1",
        .cell.parent_names = (const char *[]){ "clk_sdio_timer", "", "", "", "", "", "pll_sys_pri_ph", "", "", "", "clk_adc", "clk_dpi", "clk_pwm0", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 16,
        .oe_mask = RT_BIT(1),
        .ctrl_reg = CLK_GP1_CTRL,
        .div_int_reg = CLK_GP1_DIV_INT,
        .div_frac_reg = CLK_GP1_DIV_FRAC,
        .sel_reg = CLK_GP1_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(1, 1)),

    [RP1_CLK_GP2] = REGISTER_CLK(
        .cell.name = "clk_gp2",
        .cell.parent_names = (const char *[]){ "clk_sdio_alt_src", "", "", "", "", "", "pll_sys_sec", "", "pll_video", "clk_audio_in", "clk_dpi", "clk_pwm0", "clk_pwm1", "clk_mipi0_dpi", "clk_mipi1_cfg", "clk_sys" },
        .num_std_parents = 0,
        .num_aux_parents = 16,
        .oe_mask = RT_BIT(2),
        .ctrl_reg = CLK_GP2_CTRL,
        .div_int_reg = CLK_GP2_DIV_INT,
        .div_frac_reg = CLK_GP2_DIV_FRAC,
        .sel_reg = CLK_GP2_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(2, 1)),

    [RP1_CLK_GP3] = REGISTER_CLK(
        .cell.name = "clk_gp3",
        .cell.parent_names = (const char *[]){ "xosc", "", "", "", "", "", "", "", "pll_video_pri_ph", "clk_audio_out", "", "", "clk_mipi1_dpi", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 16,
        .oe_mask = RT_BIT(3),
        .ctrl_reg = CLK_GP3_CTRL,
        .div_int_reg = CLK_GP3_DIV_INT,
        .div_frac_reg = CLK_GP3_DIV_FRAC,
        .sel_reg = CLK_GP3_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(3, 1)),

    [RP1_CLK_GP4] = REGISTER_CLK(
        .cell.name = "clk_gp4",
        .cell.parent_names = (const char *[]){ "xosc", "", "", "", "", "", "", "pll_video_sec", "", "", "", "clk_mipi0_cfg", "clk_uart", "", "", "clk_sys" },
        .num_std_parents = 0,
        .num_aux_parents = 16,
        .oe_mask = RT_BIT(4),
        .ctrl_reg = CLK_GP4_CTRL,
        .div_int_reg = CLK_GP4_DIV_INT,
        .div_frac_reg = CLK_GP4_DIV_FRAC,
        .sel_reg = CLK_GP4_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(4, 1)),

    [RP1_CLK_GP5] = REGISTER_CLK(
        .cell.name = "clk_gp5",
        .cell.parent_names = (const char *[]){ "xosc", "", "", "", "", "", "", "pll_video_sec", "clk_eth_tsu", "", "clk_vec", "", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 16,
        .oe_mask = RT_BIT(5),
        .ctrl_reg = CLK_GP5_CTRL,
        .div_int_reg = CLK_GP5_DIV_INT,
        .div_frac_reg = CLK_GP5_DIV_FRAC,
        .sel_reg = CLK_GP5_SEL,
        .div_int_max = DIV_INT_16BIT_MAX,
        .max_freq = 100 * MHz,
        .fc0_src = FC_NUM(5, 1)),

    [RP1_CLK_VEC] = REGISTER_CLK(
        .cell.name = "clk_vec",
        .cell.parent_names = (const char *[]){ "pll_sys_pri_ph", "pll_video_sec", "pll_video", "", "", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 8,
        .ctrl_reg = VIDEO_CLK_VEC_CTRL,
        .div_int_reg = VIDEO_CLK_VEC_DIV_INT,
        .sel_reg = VIDEO_CLK_VEC_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 108 * MHz,
        .fc0_src = FC_NUM(0, 6)),

    [RP1_CLK_DPI] = REGISTER_CLK(
        .cell.name = "clk_dpi",
        .cell.parent_names = (const char *[]){ "pll_sys", "pll_video_sec", "pll_video", "", "", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 8,
        .ctrl_reg = VIDEO_CLK_DPI_CTRL,
        .div_int_reg = VIDEO_CLK_DPI_DIV_INT,
        .sel_reg = VIDEO_CLK_DPI_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 200 * MHz,
        .fc0_src = FC_NUM(1, 6)),

    [RP1_CLK_MIPI0_DPI] = REGISTER_CLK(
        .cell.name = "clk_mipi0_dpi",
        .cell.parent_names = (const char *[]){ "pll_sys", "pll_video_sec", "pll_video", "clksrc_mipi0_dsi_byteclk", "", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 8,
        .ctrl_reg = VIDEO_CLK_MIPI0_DPI_CTRL,
        .div_int_reg = VIDEO_CLK_MIPI0_DPI_DIV_INT,
        .div_frac_reg = VIDEO_CLK_MIPI0_DPI_DIV_FRAC,
        .sel_reg = VIDEO_CLK_MIPI0_DPI_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 200 * MHz,
        .fc0_src = FC_NUM(2, 6)),

    [RP1_CLK_MIPI1_DPI] = REGISTER_CLK(
        .cell.name = "clk_mipi1_dpi",
        .cell.parent_names = (const char *[]){ "pll_sys", "pll_video_sec", "pll_video", "clksrc_mipi1_dsi_byteclk", "", "", "", "" },
        .num_std_parents = 0,
        .num_aux_parents = 8,
        .ctrl_reg = VIDEO_CLK_MIPI1_DPI_CTRL,
        .div_int_reg = VIDEO_CLK_MIPI1_DPI_DIV_INT,
        .div_frac_reg = VIDEO_CLK_MIPI1_DPI_DIV_FRAC,
        .sel_reg = VIDEO_CLK_MIPI1_DPI_SEL,
        .div_int_max = DIV_INT_8BIT_MAX,
        .max_freq = 200 * MHz,
        .fc0_src = FC_NUM(3, 6)),

    [RP1_CLK_MIPI0_DSI_BYTECLOCK] = REGISTER_VARSRC(
        .cell.name = "clksrc_mipi0_dsi_byteclk"),
    [RP1_CLK_MIPI1_DSI_BYTECLOCK] = REGISTER_VARSRC(
        .cell.name = "clksrc_mipi1_dsi_byteclk"),
};

static rt_err_t rp1_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rp1_clockman *clockman = rt_calloc(1, sizeof(*clockman));

    if (!clockman)
    {
        return -RT_ENOMEM;
    }

    clockman->regs = rt_dm_dev_iomap(dev, 0);

    if (!clockman->regs)
    {
        LOG_E("%s: ioremap failed", rt_ofw_node_full_name(dev->ofw_node));
        err = -RT_EIO;
        goto _free;
    }

    clockman->clk_cell_i2s = rp1_clk_cell[RP1_CLK_I2S];
    clockman->clk_cell_slow_sys = rp1_clk_cell[RP1_CLK_SLOW_SYS];

    for (int i = 0; i < RT_ARRAY_SIZE(rp1_clk_cell); ++i)
    {
        struct rp1_clk_common *common;
        struct rt_clk_cell *cell = rp1_clk_cell[i];

        if (!cell)
        {
            continue;
        }

        common = rt_container_of(cell, struct rp1_clk_common, cell);

        if (common->init)
        {
            common->init(clockman, cell);
        }
    }

    clockman->parent.dev = dev;
    clockman->parent.cells = rp1_clk_cell;
    clockman->parent.cells_nr = RT_ARRAY_SIZE(rp1_clk_cell);

    for (int i = 0; i < RT_ARRAY_SIZE(rp1_clk_cell); ++i)
    {
        struct rt_clk_cell *cell = rp1_clk_cell[i];

        if (cell)
        {
            cell->clk_np = &clockman->parent;
        }
    }

    clockman->clk_cell_xosc = rt_clk_cell_get_parent_by_index(clockman->clk_cell_i2s, 0);
    clockman->clk_cell_audio = rt_clk_cell_get_parent_by_index(clockman->clk_cell_i2s, 1);

    if ((err = rt_clk_register(&clockman->parent)))
    {
        LOG_E("%s: rt_clk_register failed err=%s",
                rt_ofw_node_full_name(dev->ofw_node), rt_strerror(err));
        goto _free;
    }

    return RT_EOK;

_free:
    if (clockman->regs)
    {
        rt_iounmap(clockman->regs);
    }

    rt_free(clockman);

    return err;
}

static const struct rt_ofw_node_id rp1_clk_ofw_ids[] =
{
    { .compatible = "raspberrypi,rp1-clocks" },
    { /* sentinel */ }
};

static struct rt_platform_driver rp1_clk_driver =
{
    .name = "clk-rp1",
    .ids = rp1_clk_ofw_ids,

    .probe = rp1_clk_probe,
};

static int rp1_clk_register(void)
{
    rt_platform_driver_register(&rp1_clk_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rp1_clk_register);
