/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk-pll.h"
#include "clk-rk-mux.h"

#define PLL_MODE_MASK           0x3
#define PLL_MODE_SLOW           0x0
#define PLL_MODE_NORM           0x1
#define PLL_MODE_DEEP           0x2
#define PLL_RK3328_MODE_MASK    0x1

#define MHZ                     (1000UL * 1000UL)
#define KHZ                     (1000UL)

/* CLK_PLL_TYPE_RK3066_AUTO type ops */
#define PLL_FREF_MIN            (269 * KHZ)
#define PLL_FREF_MAX            (2200 * MHZ)

#define PLL_FVCO_MIN            (440 * MHZ)
#define PLL_FVCO_MAX            (2200 * MHZ)

#define PLL_FOUT_MIN            (27500 * KHZ)
#define PLL_FOUT_MAX            (2200 * MHZ)

#define PLL_NF_MAX              (4096)
#define PLL_NR_MAX              (64)
#define PLL_NO_MAX              (16)

/* CLK_PLL_TYPE_RK3036/3366/3399_AUTO type ops */
#define MIN_FOUTVCO_FREQ        (800 * MHZ)
#define MAX_FOUTVCO_FREQ        (2000 * MHZ)

static struct rockchip_pll_rate_table auto_table;

static void rockchip_pll_clk_set_postdiv(rt_ubase_t fout_hz,
        rt_uint32_t *postdiv1, rt_uint32_t *postdiv2, rt_uint32_t *foutvco)
{
    rt_ubase_t freq;

    if (fout_hz < MIN_FOUTVCO_FREQ)
    {
        for (*postdiv1 = 1; *postdiv1 <= 7; (*postdiv1)++)
        {
            for (*postdiv2 = 1; *postdiv2 <= 7; (*postdiv2)++)
            {
                freq = fout_hz * (*postdiv1) * (*postdiv2);

                if (freq >= MIN_FOUTVCO_FREQ && freq <= MAX_FOUTVCO_FREQ)
                {
                    *foutvco = freq;
                    return;
                }
            }
        }
    }
    else
    {
        *postdiv1 = 1;
        *postdiv2 = 1;
    }
}

static struct rockchip_pll_rate_table *rockchip_pll_clk_set_by_auto(
        rt_ubase_t fin_hz, rt_ubase_t fout_hz)
{
    rt_ubase_t clk_gcd = 0;
    rt_uint64_t fin_64, frac_64;
    rt_uint32_t foutvco = fout_hz, f_frac, postdiv1, postdiv2;
    struct rockchip_pll_rate_table *rate_table = &auto_table;

    if (fin_hz == 0 || fout_hz == 0 || fout_hz == fin_hz)
    {
        return RT_NULL;
    }

    rockchip_pll_clk_set_postdiv(fout_hz, &postdiv1, &postdiv2, &foutvco);
    rate_table->postdiv1 = postdiv1;
    rate_table->postdiv2 = postdiv2;
    rate_table->dsmpd = 1;

    if (fin_hz / MHZ * MHZ == fin_hz && fout_hz / MHZ * MHZ == fout_hz)
    {
        fin_hz /= MHZ;
        foutvco /= MHZ;
        clk_gcd = rockchip_gcd(fin_hz, foutvco);
        rate_table->refdiv = fin_hz / clk_gcd;
        rate_table->fbdiv = foutvco / clk_gcd;

        rate_table->frac = 0;
    }
    else
    {
        clk_gcd = rockchip_gcd(fin_hz / MHZ, foutvco / MHZ);
        rate_table->refdiv = fin_hz / MHZ / clk_gcd;
        rate_table->fbdiv = foutvco / MHZ / clk_gcd;

        rate_table->frac = 0;

        f_frac = (foutvco % MHZ);
        fin_64 = fin_hz;
        rt_do_div(fin_64, (rt_uint64_t)rate_table->refdiv);
        frac_64 = (rt_uint64_t)f_frac << 24;
        rt_do_div(frac_64, fin_64);
        rate_table->frac = (rt_uint32_t)frac_64;
        if (rate_table->frac > 0)
        {
            rate_table->dsmpd = 0;
        }
    }

    return rate_table;
}

static void *rockchip_pll_base(struct rockchip_pll_clk_cell *pll_clk_cell)
{
    return pll_clk_cell->rk_cell.provider->reg_base + pll_clk_cell->con_offset;
}

static struct rockchip_pll_rate_table * rockchip_rk3066_pll_clk_set_by_auto(
        rt_ubase_t fin_hz, rt_ubase_t fout_hz)
{
    rt_ubase_t clk_gcd = 0;
    rt_uint64_t fref, fvco, fout;
    rt_uint32_t nr, nf, no, nonr, nr_out, nf_out, no_out, n, numerator, denominator;
    struct rockchip_pll_rate_table *rate_table = &auto_table;

    nr_out = PLL_NR_MAX + 1;
    no_out = 0;
    nf_out = 0;

    if (fin_hz == 0 || fout_hz == 0 || fout_hz == fin_hz)
    {
        return RT_NULL;
    }

    clk_gcd = rockchip_gcd(fin_hz, fout_hz);

    numerator = fout_hz / clk_gcd;
    denominator = fin_hz / clk_gcd;

    for (n = 1;; ++n)
    {
        nf = numerator * n;
        nonr = denominator * n;

        if (nf > PLL_NF_MAX || nonr > (PLL_NO_MAX * PLL_NR_MAX))
        {
            break;
        }

        for (no = 1; no <= PLL_NO_MAX; ++no)
        {
            if (!(no == 1 || !(no % 2)))
            {
                continue;
            }

            if (nonr % no)
            {
                continue;
            }
            nr = nonr / no;

            if (nr > PLL_NR_MAX)
            {
                continue;
            }

            fref = fin_hz / nr;
            if (fref < PLL_FREF_MIN || fref > PLL_FREF_MAX)
            {
                continue;
            }

            fvco = fref * nf;
            if (fvco < PLL_FVCO_MIN || fvco > PLL_FVCO_MAX)
            {
                continue;
            }

            fout = fvco / no;
            if (fout < PLL_FOUT_MIN || fout > PLL_FOUT_MAX)
            {
                continue;
            }

            /* select the best from all available PLL settings */
            if ((no > no_out) || ((no == no_out) && (nr < nr_out)))
            {
                nr_out = nr;
                nf_out = nf;
                no_out = no;
            }
        }
    }

    /* output the best PLL setting */
    if ((nr_out <= PLL_NR_MAX) && (no_out > 0))
    {
        rate_table->nr = nr_out;
        rate_table->nf = nf_out;
        rate_table->no = no_out;
    }
    else
    {
        return RT_NULL;
    }

    return rate_table;
}

static rt_uint32_t rockchip_rk3588_pll_frac_get(
        rt_uint32_t m, rt_uint32_t p, rt_uint32_t s, rt_uint64_t fin_hz, rt_uint64_t fvco)
{
    rt_uint32_t k = 0;
    rt_uint64_t fref, fout, ffrac;

    fref = fin_hz / p;
    ffrac = fvco - (m * fref);
    fout = ffrac * 65536;
    k = fout / fref;

    if (k > 32767)
    {
        fref = fin_hz / p;
        ffrac = ((m + 1) * fref) - fvco;
        fout = ffrac * 65536;
        k = ((fout * 10 / fref) + 7) / 10;

        if (k > 32767)
        {
            k = 0;
        }
        else
        {
            k = ~k + 1;
        }
    }
    return k;
}

static struct rockchip_pll_rate_table *rockchip_rk3588_pll_frac_by_auto(
        rt_ubase_t fin_hz, rt_ubase_t fout_hz)
{
    rt_uint32_t p, m, s, k;
    rt_uint64_t fvco, fvco_min = 2250 * MHZ, fvco_max = 4500 * MHZ;
    struct rockchip_pll_rate_table *rate_table = &auto_table;

    for (s = 0; s <= 6; ++s)
    {
        fvco = (rt_uint64_t)fout_hz << s;

        if (fvco < fvco_min || fvco > fvco_max)
        {
            continue;
        }
        for (p = 1; p <= 4; ++p)
        {
            for (m = 64; m <= 1023; ++m)
            {
                if ((fvco >= m * fin_hz / p) && (fvco < (m + 1) * fin_hz / p))
                {
                    k = rockchip_rk3588_pll_frac_get(m, p, s, (rt_uint64_t)fin_hz, fvco);

                    if (!k)
                    {
                        continue;
                    }

                    rate_table->p = p;
                    rate_table->s = s;
                    rate_table->k = k;

                    if (k > 32767)
                    {
                        rate_table->m = m + 1;
                    }
                    else
                    {
                        rate_table->m = m;
                    }

                    return rate_table;
                }
            }
        }
    }

    return RT_NULL;
}

static struct rockchip_pll_rate_table *rockchip_rk3588_pll_clk_set_by_auto(
        rt_ubase_t fin_hz, rt_ubase_t fout_hz)
{
    rt_uint32_t p, m, s;
    rt_uint64_t fvco, fout_min = 37 * MHZ, fout_max = 4500 * MHZ;
    rt_uint64_t fvco_min = 2250 * MHZ, fvco_max = 4500 * MHZ;
    struct rockchip_pll_rate_table *rate_table = &auto_table;

    if (fin_hz == 0 || fout_hz == 0 || fout_hz == fin_hz)
    {
        return RT_NULL;
    }

    if (fout_hz > fout_max || fout_hz < fout_min)
    {
        return RT_NULL;
    }

    if (fin_hz / MHZ * MHZ == fin_hz && fout_hz / MHZ * MHZ == fout_hz)
    {
        for (s = 0; s <= 6; ++s)
        {
            fvco = (rt_uint64_t)fout_hz << s;

            if (fvco < fvco_min || fvco > fvco_max)
            {
                continue;
            }

            for (p = 2; p <= 4; ++p)
            {
                for (m = 64; m <= 1023; ++m)
                {
                    if (fvco == m * fin_hz / p)
                    {
                        rate_table->p = p;
                        rate_table->m = m;
                        rate_table->s = s;
                        rate_table->k = 0;

                        return rate_table;
                    }
                }
            }
        }
    }
    else
    {
        if ((rate_table = rockchip_rk3588_pll_frac_by_auto(fin_hz, fout_hz)))
        {
            return rate_table;
        }
    }

    return RT_NULL;
}

static const struct rockchip_pll_rate_table *rockchip_get_pll_settings(
        struct rockchip_pll_clk_cell *pll_clk_cell, rt_ubase_t rate)
{
    const struct rockchip_pll_rate_table *rate_table = pll_clk_cell->rate_table;

    for (int i = 0; i < rate_table[i].rate; ++i)
    {
        if (rate == rate_table[i].rate)
        {
            if (i < pll_clk_cell->sel)
            {
                pll_clk_cell->scaling = rate;

                return &rate_table[pll_clk_cell->sel];
            }
            pll_clk_cell->scaling = 0;

            return &rate_table[i];
        }
    }
    pll_clk_cell->scaling = 0;

    if (pll_clk_cell->type == pll_type_rk3066)
    {
        return rockchip_rk3066_pll_clk_set_by_auto(24 * MHZ, rate);
    }
    else if (pll_clk_cell->type == pll_type_rk3588 || pll_clk_cell->type == pll_type_rk3588_core)
    {
        return rockchip_rk3588_pll_clk_set_by_auto(24 * MHZ, rate);
    }
    else
    {
        return rockchip_pll_clk_set_by_auto(24 * MHZ, rate);
    }
}

static rt_base_t rockchip_pll_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t drate, rt_ubase_t *prate)
{
    return drate;
}

#define LINK_GRF(grf, off)   grf, off

static rt_uint32_t grf_read(struct rt_syscon *grf, int offset)
{
    rt_uint32_t val;

    rt_syscon_read(grf, offset, &val);

    return val;
}

/*
 * Wait for the pll to reach the locked state.
 * The calling set_rate function is responsible for making sure the
 * grf regmap is available.
 */
static rt_err_t rockchip_pll_wait_lock(struct rockchip_pll_clk_cell *pll_clk_cell)
{
    rt_uint32_t val;
    struct rt_syscon *grf = pll_clk_cell->rk_cell.provider->grf;

    return readx_poll_timeout(grf_read,
                              LINK_GRF(grf, pll_clk_cell->grf_lock_offset),
                              val,
                              val & RT_BIT(pll_clk_cell->lock_shift),
                              0, 1000);
}

static rt_err_t rockchip_pll_set_parent(struct rt_clk_cell *cell, rt_uint8_t index)
{
    return rockchip_mux_clk_ops.set_parent(cell, index);
}

static rt_uint8_t rockchip_pll_get_parent(struct rt_clk_cell *cell)
{
    return rockchip_mux_clk_ops.get_parent(cell);
}

/*
 * PLL used in RK3036
 */

#define RK3036_PLLCON(i)                (i * 0x4)
#define RK3036_PLLCON0_FBDIV_MASK       0xfff
#define RK3036_PLLCON0_FBDIV_SHIFT      0
#define RK3036_PLLCON0_POSTDIV1_MASK    0x7
#define RK3036_PLLCON0_POSTDIV1_SHIFT   12
#define RK3036_PLLCON1_REFDIV_MASK      0x3f
#define RK3036_PLLCON1_REFDIV_SHIFT     0
#define RK3036_PLLCON1_POSTDIV2_MASK    0x7
#define RK3036_PLLCON1_POSTDIV2_SHIFT   6
#define RK3036_PLLCON1_LOCK_STATUS      RT_BIT(10)
#define RK3036_PLLCON1_DSMPD_MASK       0x1
#define RK3036_PLLCON1_DSMPD_SHIFT      12
#define RK3036_PLLCON1_PWRDOWN          RT_BIT(13)
#define RK3036_PLLCON1_PLLPDSEL         RT_BIT(15)
#define RK3036_PLLCON2_FRAC_MASK        0xffffff
#define RK3036_PLLCON2_FRAC_SHIFT       0

static rt_err_t rockchip_rk3036_pll_wait_lock(struct rockchip_pll_clk_cell *pll_clk_cell)
{
    void *base;
    rt_uint32_t pllcon;

    base = rockchip_pll_base(pll_clk_cell);

    /*
     * Lock time typical 250, max 500 input clock cycles @24MHz
     * So define a very safe maximum of 1000us, meaning 24000 cycles.
     */
    return readl_poll_timeout(base + RK3036_PLLCON(1),
                              pllcon,
                              pllcon & RK3036_PLLCON1_LOCK_STATUS,
                              0, 1000);
}


static rt_err_t rockchip_rk3036_pll_enable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);

    HWREG32(base + RK3036_PLLCON(1)) = HIWORD_UPDATE(0, RK3036_PLLCON1_PWRDOWN, 0);
    rockchip_rk3036_pll_wait_lock(pll_clk_cell);

    rockchip_mux_clk_ops.set_parent(cell, PLL_MODE_NORM);

    return RT_EOK;
}

static void rockchip_rk3036_pll_disable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    rockchip_mux_clk_ops.set_parent(cell, PLL_MODE_SLOW);

    base = rockchip_pll_base(pll_clk_cell);

    HWREG32(base + RK3036_PLLCON(1)) = HIWORD_UPDATE(
            RK3036_PLLCON1_PWRDOWN, RK3036_PLLCON1_PWRDOWN, 0);
}

static rt_bool_t rockchip_rk3036_pll_is_enabled(struct rt_clk_cell *cell)
{
    void *base;
    rt_uint32_t pllcon;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);
    pllcon = HWREG32(base + RK3036_PLLCON(1));

    return !(pllcon & RK3036_PLLCON1_PWRDOWN);
}

static void rockchip_rk3036_pll_get_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        struct rockchip_pll_rate_table *rate)
{
    rt_uint32_t pllcon;
    void *base = rockchip_pll_base(pll_clk_cell);

    pllcon = HWREG32(base + RK3036_PLLCON(0));
    rate->fbdiv = ((pllcon >> RK3036_PLLCON0_FBDIV_SHIFT) & RK3036_PLLCON0_FBDIV_MASK);
    rate->postdiv1 = ((pllcon >> RK3036_PLLCON0_POSTDIV1_SHIFT) & RK3036_PLLCON0_POSTDIV1_MASK);

    pllcon = HWREG32(base + RK3036_PLLCON(1));
    rate->refdiv = ((pllcon >> RK3036_PLLCON1_REFDIV_SHIFT) & RK3036_PLLCON1_REFDIV_MASK);
    rate->postdiv2 = ((pllcon >> RK3036_PLLCON1_POSTDIV2_SHIFT) & RK3036_PLLCON1_POSTDIV2_MASK);
    rate->dsmpd = ((pllcon >> RK3036_PLLCON1_DSMPD_SHIFT) & RK3036_PLLCON1_DSMPD_MASK);

    pllcon = HWREG32(base + RK3036_PLLCON(2));
    rate->frac = ((pllcon >> RK3036_PLLCON2_FRAC_SHIFT) & RK3036_PLLCON2_FRAC_MASK);
}

static rt_ubase_t rockchip_rk3036_pll_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t prate)
{
    rt_uint64_t rate64 = prate, frac_rate64 = prate;
    struct rockchip_pll_rate_table cur;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    if (pll_clk_cell->sel && pll_clk_cell->scaling)
    {
        return pll_clk_cell->scaling;
    }

    rockchip_rk3036_pll_get_params(pll_clk_cell, &cur);

    rate64 *= cur.fbdiv;
    rt_do_div(rate64, cur.refdiv);

    if (cur.dsmpd == 0)
    {
        /* Fractional mode */
        frac_rate64 *= cur.frac;

        rt_do_div(frac_rate64, cur.refdiv);
        rate64 += frac_rate64 >> 24;
    }

    rt_do_div(rate64, cur.postdiv1);
    rt_do_div(rate64, cur.postdiv2);

    return (rt_ubase_t)rate64;
}

static rt_err_t rockchip_rk3036_pll_set_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        const struct rockchip_pll_rate_table *rate)
{
    void *base;
    rt_err_t err;
    rt_uint32_t pllcon;
    int rate_change_remuxed = 0, cur_parent;
    struct rockchip_pll_rate_table cur;

    rockchip_rk3036_pll_get_params(pll_clk_cell, &cur);
    cur.rate = 0;

    if (!(pll_clk_cell->flags & ROCKCHIP_PLL_FIXED_MODE))
    {
        cur_parent = rockchip_mux_clk_ops.get_parent(&pll_clk_cell->rk_cell.cell);

        if (cur_parent == PLL_MODE_NORM)
        {
            rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_SLOW);
            rate_change_remuxed = 1;
        }
    }

    base = rockchip_pll_base(pll_clk_cell);

    /* Update pll values */
    HWREG32(base + RK3036_PLLCON(0)) =
            HIWORD_UPDATE(rate->fbdiv, RK3036_PLLCON0_FBDIV_MASK, RK3036_PLLCON0_FBDIV_SHIFT) |
            HIWORD_UPDATE(rate->postdiv1, RK3036_PLLCON0_POSTDIV1_MASK, RK3036_PLLCON0_POSTDIV1_SHIFT);

    HWREG32(base + RK3036_PLLCON(1)) =
            HIWORD_UPDATE(rate->refdiv, RK3036_PLLCON1_REFDIV_MASK, RK3036_PLLCON1_REFDIV_SHIFT) |
            HIWORD_UPDATE(rate->postdiv2, RK3036_PLLCON1_POSTDIV2_MASK, RK3036_PLLCON1_POSTDIV2_SHIFT) |
            HIWORD_UPDATE(rate->dsmpd, RK3036_PLLCON1_DSMPD_MASK, RK3036_PLLCON1_DSMPD_SHIFT);

    /* GPLL CON2 is not HIWORD_MASK */
    pllcon = HWREG32(base + RK3036_PLLCON(2));
    pllcon &= ~(RK3036_PLLCON2_FRAC_MASK << RK3036_PLLCON2_FRAC_SHIFT);
    pllcon |= rate->frac << RK3036_PLLCON2_FRAC_SHIFT;
    HWREG32(base + RK3036_PLLCON(2)) = pllcon;

    /* Wait for the pll to lock */
    if ((err = rockchip_rk3036_pll_wait_lock(pll_clk_cell)))
    {
        rockchip_rk3036_pll_set_params(pll_clk_cell, &cur);
    }

    if (rate_change_remuxed)
    {
        rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_NORM);
    }

    return err;
}

static rt_err_t rockchip_rk3036_pll_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t drate, rt_ubase_t prate)
{
    const struct rockchip_pll_rate_table *rate;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    /* Get required rate settings from table */
    if (!(rate = rockchip_get_pll_settings(pll_clk_cell, drate)))
    {
        return -RT_EINVAL;
    }

    return rockchip_rk3036_pll_set_params(pll_clk_cell, rate);
}

static const struct rt_clk_ops rockchip_rk3036_pll_clk_norate_ops =
{
    .enable = rockchip_rk3036_pll_enable,
    .disable = rockchip_rk3036_pll_disable,
    .is_enabled = rockchip_rk3036_pll_is_enabled,
    .recalc_rate = rockchip_rk3036_pll_recalc_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

static const struct rt_clk_ops rockchip_rk3036_pll_clk_ops =
{
    .enable = rockchip_rk3036_pll_enable,
    .disable = rockchip_rk3036_pll_disable,
    .is_enabled = rockchip_rk3036_pll_is_enabled,
    .recalc_rate = rockchip_rk3036_pll_recalc_rate,
    .round_rate = rockchip_pll_round_rate,
    .set_rate = rockchip_rk3036_pll_set_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

static void rockchip_rk3036_pll_init(struct rt_clk_cell *cell)
{
    rt_ubase_t drate;
    struct rockchip_pll_rate_table cur;
    const struct rockchip_pll_rate_table *rate;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    if (!(pll_clk_cell->flags & ROCKCHIP_PLL_SYNC_RATE))
    {
        return;
    }

    drate = rt_clk_cell_get_rate(cell);
    rate = rockchip_get_pll_settings(pll_clk_cell, drate);

    /* when no rate setting for the current rate, rely on clk_set_rate */
    if (!rate)
    {
        return;
    }

    rockchip_rk3036_pll_get_params(pll_clk_cell, &cur);

    if (rate->fbdiv != cur.fbdiv || rate->postdiv1 != cur.postdiv1 ||
        rate->refdiv != cur.refdiv || rate->postdiv2 != cur.postdiv2 ||
        rate->dsmpd != cur.dsmpd || (!cur.dsmpd && (rate->frac != cur.frac)))
    {
        if (!rt_clk_cell_get_parent(cell))
        {
            return;
        }

        rockchip_rk3036_pll_set_params(pll_clk_cell, rate);
    }
}

/*
 * PLL used in RK3066, RK3188 and RK3288
 */

#define RK3066_PLL_RESET_DELAY(nr)  ((nr * 500) / 24 + 1)

#define RK3066_PLLCON(i)            (i * 0x4)
#define RK3066_PLLCON0_OD_MASK      0xf
#define RK3066_PLLCON0_OD_SHIFT     0
#define RK3066_PLLCON0_NR_MASK      0x3f
#define RK3066_PLLCON0_NR_SHIFT     8
#define RK3066_PLLCON1_NF_MASK      0x1fff
#define RK3066_PLLCON1_NF_SHIFT     0
#define RK3066_PLLCON2_NB_MASK      0xfff
#define RK3066_PLLCON2_NB_SHIFT     0
#define RK3066_PLLCON3_RESET        (1 << 5)
#define RK3066_PLLCON3_PWRDOWN      (1 << 1)
#define RK3066_PLLCON3_BYPASS       (1 << 0)

static rt_err_t rockchip_rk3066_pll_enable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);

    HWREG32(base + RK3066_PLLCON(3)) = HIWORD_UPDATE(0, RK3066_PLLCON3_PWRDOWN, 0);
    rockchip_pll_wait_lock(pll_clk_cell);

    return RT_EOK;
}

static void rockchip_rk3066_pll_disable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);

    HWREG32(base + RK3066_PLLCON(3)) = HIWORD_UPDATE(
            RK3066_PLLCON3_PWRDOWN, RK3066_PLLCON3_PWRDOWN, 0);
}

static rt_bool_t rockchip_rk3066_pll_is_enabled(struct rt_clk_cell *cell)
{
    void *base;
    rt_uint32_t pllcon;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);
    pllcon = HWREG32(base + RK3066_PLLCON(3));

    return !(pllcon & RK3066_PLLCON3_PWRDOWN);
}

static void rockchip_rk3066_pll_get_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        struct rockchip_pll_rate_table *rate)
{
    rt_uint32_t pllcon;
    void *base = rockchip_pll_base(pll_clk_cell);

    pllcon = HWREG32(base + RK3066_PLLCON(0));
    rate->nr = ((pllcon >> RK3066_PLLCON0_NR_SHIFT) & RK3066_PLLCON0_NR_MASK) + 1;
    rate->no = ((pllcon >> RK3066_PLLCON0_OD_SHIFT) & RK3066_PLLCON0_OD_MASK) + 1;

    pllcon = HWREG32(base + RK3066_PLLCON(1));
    rate->nf = ((pllcon >> RK3066_PLLCON1_NF_SHIFT) & RK3066_PLLCON1_NF_MASK) + 1;

    pllcon = HWREG32(base + RK3066_PLLCON(2));
    rate->nb = ((pllcon >> RK3066_PLLCON2_NB_SHIFT) & RK3066_PLLCON2_NB_MASK) + 1;
}

static rt_ubase_t rockchip_rk3066_pll_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t prate)
{
    void *base;
    rt_uint32_t pllcon;
    rt_uint64_t rate64 = prate;
    struct rockchip_pll_rate_table cur;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);

    pllcon = HWREG32(base + RK3066_PLLCON(3));
    if (pllcon & RK3066_PLLCON3_BYPASS)
    {
        return prate;
    }

    if (pll_clk_cell->sel && pll_clk_cell->scaling)
    {
        return pll_clk_cell->scaling;
    }

    rockchip_rk3066_pll_get_params(pll_clk_cell, &cur);

    rate64 *= cur.nf;
    rt_do_div(rate64, cur.nr);
    rt_do_div(rate64, cur.no);

    return (rt_ubase_t)rate64;
}

static rt_err_t rockchip_rk3066_pll_set_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        const struct rockchip_pll_rate_table *rate)
{
    void *base;
    rt_err_t err;
    int rate_change_remuxed = 0, cur_parent;
    struct rockchip_pll_rate_table cur;

    rockchip_rk3066_pll_get_params(pll_clk_cell, &cur);
    cur.rate = 0;

    cur_parent = rockchip_mux_clk_ops.get_parent(&pll_clk_cell->rk_cell.cell);
    if (cur_parent == PLL_MODE_NORM)
    {
        rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_SLOW);
        rate_change_remuxed = 1;
    }

    base = rockchip_pll_base(pll_clk_cell);

    /* Enter reset mode */
    HWREG32(base + RK3066_PLLCON(3)) = HIWORD_UPDATE(
            RK3066_PLLCON3_RESET, RK3066_PLLCON3_RESET, 0);

    /* Update pll values */
    HWREG32(base + RK3066_PLLCON(0)) =
            HIWORD_UPDATE(rate->nr - 1, RK3066_PLLCON0_NR_MASK, RK3066_PLLCON0_NR_SHIFT) |
            HIWORD_UPDATE(rate->no - 1, RK3066_PLLCON0_OD_MASK, RK3066_PLLCON0_OD_SHIFT);

    HWREG32(base + RK3066_PLLCON(1)) = HIWORD_UPDATE(
            rate->nf - 1, RK3066_PLLCON1_NF_MASK, RK3066_PLLCON1_NF_SHIFT);
    HWREG32(base + RK3066_PLLCON(2)) = HIWORD_UPDATE(
            rate->nb - 1, RK3066_PLLCON2_NB_MASK, RK3066_PLLCON2_NB_SHIFT);

    /* Leave reset and wait the reset_delay */
    HWREG32(base + RK3066_PLLCON(3)) = HIWORD_UPDATE(0, RK3066_PLLCON3_RESET, 0);
    rt_hw_us_delay(RK3066_PLL_RESET_DELAY(rate->nr));

    /* Wait for the pll to lock */
    if ((err = rockchip_pll_wait_lock(pll_clk_cell)))
    {
        rockchip_rk3066_pll_set_params(pll_clk_cell, &cur);
    }

    if (rate_change_remuxed)
    {
        rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_NORM);
    }

    return err;
}

static rt_err_t rockchip_rk3066_pll_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t drate, rt_ubase_t prate)
{
    rt_err_t err;
    const struct rockchip_pll_rate_table *rate;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    rockchip_rk3066_pll_recalc_rate(cell, prate);

    /* Get required rate settings from table */
    if (!(rate = rockchip_get_pll_settings(pll_clk_cell, drate)))
    {
        return -RT_EINVAL;
    }

    if ((err = rockchip_rk3066_pll_set_params(pll_clk_cell, rate)))
    {
        pll_clk_cell->scaling = 0;
    }

    return err;
}

static const struct rt_clk_ops rockchip_rk3066_pll_clk_norate_ops =
{
    .enable = rockchip_rk3066_pll_enable,
    .disable = rockchip_rk3066_pll_disable,
    .is_enabled = rockchip_rk3066_pll_is_enabled,
    .recalc_rate = rockchip_rk3066_pll_recalc_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

static const struct rt_clk_ops rockchip_rk3066_pll_clk_ops =
{
    .enable = rockchip_rk3066_pll_enable,
    .disable = rockchip_rk3066_pll_disable,
    .is_enabled = rockchip_rk3066_pll_is_enabled,
    .recalc_rate = rockchip_rk3066_pll_recalc_rate,
    .round_rate = rockchip_pll_round_rate,
    .set_rate = rockchip_rk3066_pll_set_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

static void rockchip_rk3066_pll_init(struct rt_clk_cell *cell)
{
    rt_ubase_t drate;
    struct rockchip_pll_rate_table cur;
    const struct rockchip_pll_rate_table *rate;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    if (!(pll_clk_cell->flags & ROCKCHIP_PLL_SYNC_RATE))
    {
        return;
    }

    drate = rt_clk_cell_get_rate(cell);

    /* when no rate setting for the current rate, rely on clk_set_rate */
    if (!(rate = rockchip_get_pll_settings(pll_clk_cell, drate)))
    {
        return;
    }

    rockchip_rk3066_pll_get_params(pll_clk_cell, &cur);

    if (rate->nr != cur.nr || rate->no != cur.no ||
        rate->nf != cur.nf || rate->nb != cur.nb)
    {
        rockchip_rk3066_pll_set_params(pll_clk_cell, rate);
    }
}

/*
 * PLL used in RK3399
 */

#define RK3399_PLLCON(i)                (i * 0x4)
#define RK3399_PLLCON0_FBDIV_MASK       0xfff
#define RK3399_PLLCON0_FBDIV_SHIFT      0
#define RK3399_PLLCON1_REFDIV_MASK      0x3f
#define RK3399_PLLCON1_REFDIV_SHIFT     0
#define RK3399_PLLCON1_POSTDIV1_MASK    0x7
#define RK3399_PLLCON1_POSTDIV1_SHIFT   8
#define RK3399_PLLCON1_POSTDIV2_MASK    0x7
#define RK3399_PLLCON1_POSTDIV2_SHIFT   12
#define RK3399_PLLCON2_FRAC_MASK        0xffffff
#define RK3399_PLLCON2_FRAC_SHIFT       0
#define RK3399_PLLCON2_LOCK_STATUS      RT_BIT(31)
#define RK3399_PLLCON3_PWRDOWN          RT_BIT(0)
#define RK3399_PLLCON3_DSMPD_MASK       0x1
#define RK3399_PLLCON3_DSMPD_SHIFT      3

static rt_err_t rockchip_rk3399_pll_wait_lock(struct rockchip_pll_clk_cell *pll_clk_cell)
{
    void *base;
    rt_uint32_t pllcon;

    base = rockchip_pll_base(pll_clk_cell);

    /*
    * Lock time typical 250, max 500 input clock cycles @24MHz
    * So define a very safe maximum of 1000us, meaning 24000 cycles.
    */
    return readl_poll_timeout(base + RK3399_PLLCON(2),
                              pllcon,
                              pllcon & RK3399_PLLCON2_LOCK_STATUS,
                              0, 1000);
}

static rt_err_t rockchip_rk3399_pll_enable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);
    HWREG32(base + RK3399_PLLCON(3)) = HIWORD_UPDATE(0, RK3399_PLLCON3_PWRDOWN, 0);
    rockchip_rk3399_pll_wait_lock(pll_clk_cell);

    return RT_EOK;
}

static void rockchip_rk3399_pll_disable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);
    HWREG32(base + RK3399_PLLCON(3)) = HIWORD_UPDATE(
            RK3399_PLLCON3_PWRDOWN, RK3399_PLLCON3_PWRDOWN, 0);
}

static rt_bool_t rockchip_rk3399_pll_is_enabled(struct rt_clk_cell *cell)
{
    void *base;
    rt_uint32_t pllcon;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);
    pllcon = HWREG32(base + RK3399_PLLCON(3));

    return !(pllcon & RK3399_PLLCON3_PWRDOWN);
}

static void rockchip_rk3399_pll_get_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        struct rockchip_pll_rate_table *rate)
{
    rt_uint32_t pllcon;
    void *base = rockchip_pll_base(pll_clk_cell);

    pllcon = HWREG32(base + RK3399_PLLCON(0));
    rate->fbdiv = ((pllcon >> RK3399_PLLCON0_FBDIV_SHIFT) & RK3399_PLLCON0_FBDIV_MASK);

    pllcon = HWREG32(base + RK3399_PLLCON(1));
    rate->refdiv = ((pllcon >> RK3399_PLLCON1_REFDIV_SHIFT) & RK3399_PLLCON1_REFDIV_MASK);
    rate->postdiv1 = ((pllcon >> RK3399_PLLCON1_POSTDIV1_SHIFT) & RK3399_PLLCON1_POSTDIV1_MASK);
    rate->postdiv2 = ((pllcon >> RK3399_PLLCON1_POSTDIV2_SHIFT) & RK3399_PLLCON1_POSTDIV2_MASK);

    pllcon = HWREG32(base + RK3399_PLLCON(2));
    rate->frac = ((pllcon >> RK3399_PLLCON2_FRAC_SHIFT) & RK3399_PLLCON2_FRAC_MASK);

    pllcon = HWREG32(base + RK3399_PLLCON(3));
    rate->dsmpd = ((pllcon >> RK3399_PLLCON3_DSMPD_SHIFT) & RK3399_PLLCON3_DSMPD_MASK);
}

static rt_ubase_t rockchip_rk3399_pll_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t prate)
{
    rt_uint64_t rate64 = prate;
    struct rockchip_pll_rate_table cur;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    if (pll_clk_cell->sel && pll_clk_cell->scaling)
    {
        return pll_clk_cell->scaling;
    }

    rockchip_rk3399_pll_get_params(pll_clk_cell, &cur);

    rate64 *= cur.fbdiv;
    rt_do_div(rate64, cur.refdiv);

    if (cur.dsmpd == 0)
    {
        /* Fractional mode */
        rt_uint64_t frac_rate64 = prate * cur.frac;

        rt_do_div(frac_rate64, cur.refdiv);
        rate64 += frac_rate64 >> 24;
    }

    rt_do_div(rate64, cur.postdiv1);
    rt_do_div(rate64, cur.postdiv2);

    return (rt_ubase_t)rate64;
}

static rt_err_t rockchip_rk3399_pll_set_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        const struct rockchip_pll_rate_table *rate)
{
    rt_err_t err;
    rt_uint32_t pllcon;
    int rate_change_remuxed = 0, cur_parent;
    void *base = rockchip_pll_base(pll_clk_cell);
    struct rockchip_pll_rate_table cur;

    rockchip_rk3399_pll_get_params(pll_clk_cell, &cur);
    cur.rate = 0;

    cur_parent = rockchip_mux_clk_ops.get_parent(&pll_clk_cell->rk_cell.cell);

    if (cur_parent == PLL_MODE_NORM)
    {
        rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_SLOW);
        rate_change_remuxed = 1;
    }

    /* Set pll power down */
    HWREG32(base + RK3399_PLLCON(3)) = HIWORD_UPDATE(
            RK3399_PLLCON3_PWRDOWN, RK3399_PLLCON3_PWRDOWN, 0);

    /* Update pll values */
    HWREG32(base + RK3399_PLLCON(0)) = HIWORD_UPDATE(
            rate->fbdiv, RK3399_PLLCON0_FBDIV_MASK, RK3399_PLLCON0_FBDIV_SHIFT);

    HWREG32(base + RK3399_PLLCON(1)) =
            HIWORD_UPDATE(rate->refdiv, RK3399_PLLCON1_REFDIV_MASK, RK3399_PLLCON1_REFDIV_SHIFT) |
            HIWORD_UPDATE(rate->postdiv1, RK3399_PLLCON1_POSTDIV1_MASK, RK3399_PLLCON1_POSTDIV1_SHIFT) |
            HIWORD_UPDATE(rate->postdiv2, RK3399_PLLCON1_POSTDIV2_MASK, RK3399_PLLCON1_POSTDIV2_SHIFT);

    /* xPLL CON2 is not HIWORD_MASK */
    pllcon = HWREG32(base + RK3399_PLLCON(2));
    pllcon &= ~(RK3399_PLLCON2_FRAC_MASK << RK3399_PLLCON2_FRAC_SHIFT);
    pllcon |= rate->frac << RK3399_PLLCON2_FRAC_SHIFT;
    HWREG32(base + RK3399_PLLCON(2)) = pllcon;

    HWREG32(base + RK3399_PLLCON(3)) =
            HIWORD_UPDATE(rate->dsmpd, RK3399_PLLCON3_DSMPD_MASK, RK3399_PLLCON3_DSMPD_SHIFT);

    /* Set pll power up */
    HWREG32(base + RK3399_PLLCON(3)) = HIWORD_UPDATE(0, RK3399_PLLCON3_PWRDOWN, 0);

    /* Wait for the pll to lock */
    if ((err = rockchip_rk3399_pll_wait_lock(pll_clk_cell)))
    {
        rockchip_rk3399_pll_set_params(pll_clk_cell, &cur);
    }

    if (rate_change_remuxed)
    {
        rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_NORM);
    }

    return err;
}

static rt_err_t rockchip_rk3399_pll_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t drate, rt_ubase_t prate)
{
    rt_err_t err;
    const struct rockchip_pll_rate_table *rate;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    rockchip_rk3399_pll_recalc_rate(cell, prate);

    /* Get required rate settings from table */
    if (!(rate = rockchip_get_pll_settings(pll_clk_cell, drate)))
    {
        return -RT_EINVAL;
    }

    if ((err = rockchip_rk3399_pll_set_params(pll_clk_cell, rate)))
    {
        pll_clk_cell->scaling = 0;
    }

    return err;
}

static const struct rt_clk_ops rockchip_rk3399_pll_clk_norate_ops =
{
    .enable = rockchip_rk3399_pll_enable,
    .disable = rockchip_rk3399_pll_disable,
    .is_enabled = rockchip_rk3399_pll_is_enabled,
    .recalc_rate = rockchip_rk3399_pll_recalc_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

static const struct rt_clk_ops rockchip_rk3399_pll_clk_ops =
{
    .enable = rockchip_rk3399_pll_enable,
    .disable = rockchip_rk3399_pll_disable,
    .is_enabled = rockchip_rk3399_pll_is_enabled,
    .recalc_rate = rockchip_rk3399_pll_recalc_rate,
    .round_rate = rockchip_pll_round_rate,
    .set_rate = rockchip_rk3399_pll_set_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

static void rockchip_rk3399_pll_init(struct rt_clk_cell *cell)
{
    rt_ubase_t drate;
    struct rockchip_pll_rate_table cur;
    const struct rockchip_pll_rate_table *rate;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    if (!(pll_clk_cell->flags & ROCKCHIP_PLL_SYNC_RATE))
    {
        return;
    }

    drate = rt_clk_cell_get_rate(cell);
    rate = rockchip_get_pll_settings(pll_clk_cell, drate);

    /* When no rate setting for the current rate, rely on clk_set_rate */
    if (!rate)
    {
        return;
    }

    rockchip_rk3399_pll_get_params(pll_clk_cell, &cur);

    if (rate->fbdiv != cur.fbdiv || rate->postdiv1 != cur.postdiv1 ||
        rate->refdiv != cur.refdiv || rate->postdiv2 != cur.postdiv2 ||
        rate->dsmpd != cur.dsmpd ||
        (!cur.dsmpd && (rate->frac != cur.frac)))
    {
        if (!rt_clk_cell_get_parent(cell))
        {
            return;
        }

        rockchip_rk3399_pll_set_params(pll_clk_cell, rate);
    }
}

/*
 * PLL used in RK3588
 */
#define RK3588_PLLCON(i)            (i * 0x4)
#define RK3588_PLLCON0_M_MASK       0x3ff
#define RK3588_PLLCON0_M_SHIFT      0
#define RK3588_PLLCON1_P_MASK       0x3f
#define RK3588_PLLCON1_P_SHIFT      0
#define RK3588_PLLCON1_S_MASK       0x7
#define RK3588_PLLCON1_S_SHIFT      6
#define RK3588_PLLCON2_K_MASK       0xffff
#define RK3588_PLLCON2_K_SHIFT      0
#define RK3588_PLLCON1_PWRDOWN      RT_BIT(13)
#define RK3588_PLLCON6_LOCK_STATUS  RT_BIT(15)

static rt_err_t rockchip_rk3588_pll_wait_lock(struct rockchip_pll_clk_cell *pll_clk_cell)
{
    void *base;
    rt_uint32_t pllcon;

    base = rockchip_pll_base(pll_clk_cell);

    /*
     * Lock time typical 250, max 500 input clock cycles @24MHz
     * So define a very safe maximum of 1000us, meaning 24000 cycles.
     */
    return readl_poll_timeout(base + RK3588_PLLCON(6),
                             pllcon,
                             pllcon & RK3588_PLLCON6_LOCK_STATUS,
                             0, 1000);
}

static rt_err_t rockchip_rk3588_pll_enable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);

    HWREG32(base + RK3588_PLLCON(1)) = HIWORD_UPDATE(0, RK3588_PLLCON1_PWRDOWN, 0);

    rockchip_rk3588_pll_wait_lock(pll_clk_cell);

    rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_NORM);

    return RT_EOK;
}

static void rockchip_rk3588_pll_disable(struct rt_clk_cell *cell)
{
    void *base;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);

    rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_SLOW);

    HWREG32(base + RK3588_PLLCON(1)) = HIWORD_UPDATE(
            RK3588_PLLCON1_PWRDOWN, RK3588_PLLCON1_PWRDOWN, 0);
}

static rt_bool_t rockchip_rk3588_pll_is_enabled(struct rt_clk_cell *cell)
{
    void *base;
    rt_uint32_t pllcon;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    base = rockchip_pll_base(pll_clk_cell);
    pllcon = HWREG32(base + RK3588_PLLCON(1));

    return !(pllcon & RK3588_PLLCON1_PWRDOWN);
}

static void rockchip_rk3588_pll_get_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        struct rockchip_pll_rate_table *rate)
{
    rt_uint32_t pllcon;
    void *base = rockchip_pll_base(pll_clk_cell);

    pllcon = HWREG32(base + RK3588_PLLCON(0));
    rate->m = ((pllcon >> RK3588_PLLCON0_M_SHIFT) & RK3588_PLLCON0_M_MASK);

    pllcon = HWREG32(base + RK3588_PLLCON(1));
    rate->p = ((pllcon >> RK3588_PLLCON1_P_SHIFT) & RK3588_PLLCON1_P_MASK);
    rate->s = ((pllcon >> RK3588_PLLCON1_S_SHIFT) & RK3588_PLLCON1_S_MASK);

    pllcon = HWREG32(base + RK3588_PLLCON(2));
    rate->k = ((pllcon >> RK3588_PLLCON2_K_SHIFT) & RK3588_PLLCON2_K_MASK);
}

static rt_ubase_t rockchip_rk3588_pll_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t prate)
{
    rt_uint64_t rate64 = prate, postdiv;
    struct rockchip_pll_rate_table cur;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    if (pll_clk_cell->sel && pll_clk_cell->scaling)
    {
        return pll_clk_cell->scaling;
    }

    rockchip_rk3588_pll_get_params(pll_clk_cell, &cur);

    if (cur.p == 0)
    {
        return prate;
    }

    rate64 *= cur.m;
    rt_do_div(rate64, cur.p);

    if (cur.k & RT_BIT(15))
    {
        /* Fractional mode */
        rt_uint64_t frac_rate64;

        cur.k = (~(cur.k - 1)) & RK3588_PLLCON2_K_MASK;
        frac_rate64 = prate * cur.k;
        postdiv = cur.p;
        postdiv *= 65536;
        rt_do_div(frac_rate64, postdiv);
        rate64 -= frac_rate64;
    }
    else
    {
        /* Fractional mode */
        rt_uint64_t frac_rate64 = prate * cur.k;

        postdiv = cur.p;
        postdiv *= 65536;
        rt_do_div(frac_rate64, postdiv);
        rate64 += frac_rate64;
    }
    rate64 = rate64 >> cur.s;

    if (pll_clk_cell->type == pll_type_rk3588_ddr)
    {
        return (rt_ubase_t)rate64 * 2;
    }

    return (rt_ubase_t)rate64;
}

static rt_base_t rockchip_rk3588_pll_round_rate(struct rt_clk_cell *cell,
        rt_ubase_t drate, rt_ubase_t *prate)
{
    if ((drate < 37 * MHZ) || (drate > 4500 * MHZ))
    {
        return -RT_EINVAL;
    }

    return drate;
}

static rt_err_t rockchip_rk3588_pll_set_params(struct rockchip_pll_clk_cell *pll_clk_cell,
        const struct rockchip_pll_rate_table *rate)
{
    rt_err_t err;
    void *base = rockchip_pll_base(pll_clk_cell);
    int rate_change_remuxed = 0, cur_parent;
    struct rockchip_pll_rate_table cur;

    rockchip_rk3588_pll_get_params(pll_clk_cell, &cur);
    cur.rate = 0;

    if (pll_clk_cell->type == pll_type_rk3588)
    {
        cur_parent = rockchip_mux_clk_ops.get_parent(&pll_clk_cell->rk_cell.cell);

        if (cur_parent == PLL_MODE_NORM)
        {
            rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_SLOW);
            rate_change_remuxed = 1;
        }
    }

    /* Set pll power down */
    HWREG32(base + RK3588_PLLCON(1)) = HIWORD_UPDATE(
            RK3588_PLLCON1_PWRDOWN, RK3588_PLLCON1_PWRDOWN, 0);

    /* Update pll values */
    HWREG32(base + RK3588_PLLCON(0)) = HIWORD_UPDATE(
            rate->m, RK3588_PLLCON0_M_MASK, RK3588_PLLCON0_M_SHIFT);

    HWREG32(base + RK3588_PLLCON(1)) =
            HIWORD_UPDATE(rate->p, RK3588_PLLCON1_P_MASK, RK3588_PLLCON1_P_SHIFT) |
            HIWORD_UPDATE(rate->s, RK3588_PLLCON1_S_MASK, RK3588_PLLCON1_S_SHIFT);

    HWREG32(base + RK3588_PLLCON(2)) = HIWORD_UPDATE(
            rate->k, RK3588_PLLCON2_K_MASK, RK3588_PLLCON2_K_SHIFT);

    /* Set pll power up */
    HWREG32(base + RK3588_PLLCON(1)) = HIWORD_UPDATE(0, RK3588_PLLCON1_PWRDOWN, 0);

    /* Wait for the pll to lock */
    if ((err = rockchip_rk3588_pll_wait_lock(pll_clk_cell)))
    {
        rockchip_rk3588_pll_set_params(pll_clk_cell, &cur);
    }

    if ((pll_clk_cell->type == pll_type_rk3588) && rate_change_remuxed)
    {
        rockchip_mux_clk_ops.set_parent(&pll_clk_cell->rk_cell.cell, PLL_MODE_NORM);
    }

    return err;
}

static rt_err_t rockchip_rk3588_pll_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t drate, rt_ubase_t prate)
{
    rt_err_t err;
    const struct rockchip_pll_rate_table *rate;
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(cell);

    rockchip_rk3588_pll_recalc_rate(cell, prate);

    /* Get required rate settings from table */
    if (!(rate = rockchip_get_pll_settings(pll_clk_cell, drate)))
    {
        return -RT_EINVAL;
    }

    if ((err = rockchip_rk3588_pll_set_params(pll_clk_cell, rate)))
    {
        pll_clk_cell->scaling = 0;
    }

    return err;
}

static const struct rt_clk_ops rockchip_rk3588_pll_clk_norate_ops =
{
    .enable = rockchip_rk3588_pll_enable,
    .disable = rockchip_rk3588_pll_disable,
    .is_enabled = rockchip_rk3588_pll_is_enabled,
    .recalc_rate = rockchip_rk3588_pll_recalc_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

static const struct rt_clk_ops rockchip_rk3588_pll_clk_ops =
{
    .enable = rockchip_rk3588_pll_enable,
    .disable = rockchip_rk3588_pll_disable,
    .is_enabled = rockchip_rk3588_pll_is_enabled,
    .recalc_rate = rockchip_rk3588_pll_recalc_rate,
    .round_rate = rockchip_rk3588_pll_round_rate,
    .set_rate = rockchip_rk3588_pll_set_rate,
    .set_parent = rockchip_pll_set_parent,
    .get_parent = rockchip_pll_get_parent,
};

void rockchip_pll_clk_cell_init(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(&rk_cell->cell);

    rk_cell->muxdiv_offset = pll_clk_cell->mode_offset;
    rk_cell->mux_shift = pll_clk_cell->mode_shift;

    if (pll_clk_cell->type == pll_type_rk3328)
    {
        rk_cell->mux_mask = PLL_RK3328_MODE_MASK;
    }
    else
    {
        rk_cell->mux_mask = PLL_MODE_MASK;
    }

    rk_cell->mux_flags |= CLK_MUX_HIWORD_MASK;

    rk_cell->cell.ops = &rockchip_mux_clk_ops;

    switch (pll_clk_cell->type)
    {
    case pll_type_rk3036:
    case pll_type_rk3328:
        if (!pll_clk_cell->rate_table)
        {
            rk_cell->cell.ops = &rockchip_rk3036_pll_clk_norate_ops;
        }
        else
        {
            rk_cell->cell.ops = &rockchip_rk3036_pll_clk_ops;
        }
        break;
    case pll_type_rk3066:
        if (!pll_clk_cell->rate_table || !rk_cell->provider->grf)
        {
            rk_cell->cell.ops = &rockchip_rk3066_pll_clk_norate_ops;
        }
        else
        {
            rk_cell->cell.ops = &rockchip_rk3066_pll_clk_ops;
        }
        break;
    case pll_type_rk3399:
        if (!pll_clk_cell->rate_table)
        {
            rk_cell->cell.ops = &rockchip_rk3399_pll_clk_norate_ops;
        }
        else
        {
            rk_cell->cell.ops = &rockchip_rk3399_pll_clk_ops;
        }
        break;
    case pll_type_rk3588:
    case pll_type_rk3588_core:
    case pll_type_rk3588_ddr:
        if (!pll_clk_cell->rate_table)
        {
            rk_cell->cell.ops = &rockchip_rk3588_pll_clk_norate_ops;
        }
        else
        {
            rk_cell->cell.ops = &rockchip_rk3588_pll_clk_ops;
        }
        goto _set_falgs_done;
    default:
        break;
    }

    if (!(pll_clk_cell->flags & ROCKCHIP_PLL_ALLOW_POWER_DOWN))
    {
        /* Keep all plls untouched for now */
        rk_cell->cell.flags |= RT_CLK_F_IGNORE_UNUSED;
    }

_set_falgs_done:
    return;
}

void rockchip_pll_clk_cell_setup(struct rockchip_clk_cell *rk_cell)
{
    struct rockchip_pll_clk_cell *pll_clk_cell = cell_to_rockchip_pll_clk_cell(&rk_cell->cell);

    switch (pll_clk_cell->type)
    {
    case pll_type_rk3036:
    case pll_type_rk3328:
        if (pll_clk_cell->rate_table)
        {
            rockchip_rk3036_pll_init(&rk_cell->cell);
        }
        break;
    case pll_type_rk3066:
        if (pll_clk_cell->rate_table && rk_cell->provider->grf)
        {
            rockchip_rk3066_pll_init(&rk_cell->cell);
        }
        break;
    case pll_type_rk3399:
        if (pll_clk_cell->rate_table)
        {
            rockchip_rk3399_pll_init(&rk_cell->cell);
        }
        break;
    default:
        break;
    }
}
