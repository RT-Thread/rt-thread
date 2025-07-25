/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-03     zmshahaha    the first version
 */

#define PLL_MODE_MASK               0x3
#define PLL_RK3328_MODE_MASK            0x1

/* Define pll mode */
#define RKCLK_PLL_MODE_SLOW     0
#define RKCLK_PLL_MODE_NORMAL   1
#define RKCLK_PLL_MODE_DEEP     2

/* Only support RK3036 type CLK */
#define RK3036_PLLCON0_FBDIV_MASK      0xfff
#define RK3036_PLLCON0_FBDIV_SHIFT     0
#define RK3036_PLLCON0_POSTDIV1_MASK   (0x7 << 12)
#define RK3036_PLLCON0_POSTDIV1_SHIFT  12
#define RK3036_PLLCON1_LOCK_STATUS     (1 << 10)
#define RK3036_PLLCON1_REFDIV_MASK     0x3f
#define RK3036_PLLCON1_REFDIV_SHIFT    0
#define RK3036_PLLCON1_POSTDIV2_MASK   (0x7 << 6)
#define RK3036_PLLCON1_POSTDIV2_SHIFT  6
#define RK3036_PLLCON1_DSMPD_MASK      (0x1 << 12)
#define RK3036_PLLCON1_DSMPD_SHIFT     12
#define RK3036_PLLCON2_FRAC_MASK       0xffffff
#define RK3036_PLLCON2_FRAC_SHIFT      0
#define RK3036_PLLCON1_PWRDOWN_SHIT    13
#define RK3036_PLLCON1_PWRDOWN         (1 << RK3036_PLLCON1_PWRDOWN_SHIT)

#define VCO_MAX_HZ      (3200UL * MHZ)
#define VCO_MIN_HZ      (800UL * MHZ)
#define OUTPUT_MAX_HZ       (3200UL * MHZ)
#define OUTPUT_MIN_HZ       (24UL * MHZ)
#define MIN_FOUTVCO_FREQ    (800UL * MHZ)
#define MAX_FOUTVCO_FREQ    (2000UL * MHZ)

#define RK3588_VCO_MIN_HZ   (2250UL * MHZ)
#define RK3588_VCO_MAX_HZ   (4500UL * MHZ)
#define RK3588_FOUT_MIN_HZ  (37UL * MHZ)
#define RK3588_FOUT_MAX_HZ  (4500UL * MHZ)

#define RK3588_PLLCON(i)        ((i) * 0x4)
#define RK3588_PLLCON0_M_MASK       (0x3ff << 0)
#define RK3588_PLLCON0_M_SHIFT      0
#define RK3588_PLLCON1_P_MASK       (0x3f << 0)
#define RK3588_PLLCON1_P_SHIFT      0
#define RK3588_PLLCON1_S_MASK       (0x7 << 6)
#define RK3588_PLLCON1_S_SHIFT      6
#define RK3588_PLLCON2_K_MASK       0xffff
#define RK3588_PLLCON2_K_SHIFT      0
#define RK3588_PLLCON1_PWRDOWN      (1 << 13)
#define RK3588_PLLCON6_LOCK_STATUS  (1 << 15)
#define RK3588_B0PLL_CLKSEL_CON(i)  ((i) * 0x4 + 0x50000 + 0x300)
#define RK3588_B1PLL_CLKSEL_CON(i)  ((i) * 0x4 + 0x52000 + 0x300)
#define RK3588_LPLL_CLKSEL_CON(i)   ((i) * 0x4 + 0x58000 + 0x300)
#define RK3588_CORE_DIV_MASK        0x1f
#define RK3588_CORE_L02_DIV_SHIFT   0
#define RK3588_CORE_L13_DIV_SHIFT   7
#define RK3588_CORE_B02_DIV_SHIFT   8
#define RK3588_CORE_B13_DIV_SHIFT   0

static struct rk_pll_rate_table auto_table;

static int gcd(int m, int n)
{
    while (m > 0)
    {
        if (n > m)
        {
            int t = m;
            m = n;
            n = t;
        }
        m -= n;
    }

    return n;
}

/*
 * rational_best_approximation(31415, 10000,
 *          (1 << 8) - 1, (1 << 5) - 1, &n, &d);
 *
 * you may look at given_numerator as a fixed point number,
 * with the fractional part size described in given_denominator.
 *
 * for theoretical background, see:
 * http://en.wikipedia.org/wiki/Continued_fraction
 */
void rational_best_approximation(rt_ubase_t given_numerator,
                    rt_ubase_t given_denominator,
                    rt_ubase_t max_numerator,
                    rt_ubase_t max_denominator,
                    rt_ubase_t *best_numerator,
                    rt_ubase_t *best_denominator)
{
    rt_ubase_t n, d, n0, d0, n1, d1;

    n = given_numerator;
    d = given_denominator;
    n0 = 0;
    d1 = 0;
    n1 = 1;
    d0 = 1;

    for (;;)
    {
        rt_ubase_t t, a;

        if (n1 > max_numerator || d1 > max_denominator)
        {
            n1 = n0;
            d1 = d0;
            break;
        }
        if (d == 0)
        {
            break;
        }
        t = d;
        a = n / d;
        d = n % d;
        n = t;
        t = n0 + a * n1;
        n0 = n1;
        n1 = t;
        t = d0 + a * d1;
        d0 = d1;
        d1 = t;
    }
    *best_numerator = n1;
    *best_denominator = d1;
}

/*
 * How to calculate the PLL(from TRM V0.3 Part 1 Page 63):
 * Formulas also embedded within the Fractional PLL Verilog model:
 * If DSMPD = 1 (DSM is disabled, "integer mode")
 * FOUTVCO = FREF / REFDIV * FBDIV
 * FOUTPOSTDIV = FOUTVCO / POSTDIV1 / POSTDIV2
 * Where:
 * FOUTVCO = Fractional PLL non-divided output frequency
 * FOUTPOSTDIV = Fractional PLL divided output frequency
 *               (output of second post divider)
 * FREF = Fractional PLL input reference frequency, (the OSC_HZ 24MHz input)
 * REFDIV = Fractional PLL input reference clock divider
 * FBDIV = Integer value programmed into feedback divide
 */

static int rk_pll_clk_set_postdiv(rt_ubase_t fout_hz, rt_uint32_t *postdiv1,
        rt_uint32_t *postdiv2, rt_uint32_t *foutvco)
{
    rt_ubase_t freq;

    if (fout_hz < MIN_FOUTVCO_FREQ)
    {
        for (*postdiv1 = 1; *postdiv1 <= 7; ++(*postdiv1))
        {
            for (*postdiv2 = 1; *postdiv2 <= 7; ++(*postdiv2))
            {
                freq = fout_hz * (*postdiv1) * (*postdiv2);
                if (freq >= MIN_FOUTVCO_FREQ && freq <= MAX_FOUTVCO_FREQ)
                {
                    *foutvco = freq;
                    return 0;
                }
            }
        }
    }
    else
    {
        *postdiv1 = 1;
        *postdiv2 = 1;
    }
    return 0;
}

static struct rk_pll_rate_table *rk_pll_clk_set_by_auto(rt_ubase_t fin_hz, rt_ubase_t fout_hz)
{
    struct rk_pll_rate_table *rate_table = &auto_table;
    rt_uint32_t foutvco = fout_hz;
    rt_ubase_t fin_64, frac_64;
    rt_uint32_t f_frac, postdiv1, postdiv2;
    rt_ubase_t clk_gcd = 0;

    if (fin_hz == 0 || fout_hz == 0 || fout_hz == fin_hz)
    {
        return RT_NULL;
    }

    rk_pll_clk_set_postdiv(fout_hz, &postdiv1, &postdiv2, &foutvco);
    rate_table->postdiv1 = postdiv1;
    rate_table->postdiv2 = postdiv2;
    rate_table->dsmpd = 1;

    if (fin_hz / MHZ * MHZ == fin_hz && fout_hz / MHZ * MHZ == fout_hz)
    {
        fin_hz /= MHZ;
        foutvco /= MHZ;
        clk_gcd = gcd(fin_hz, foutvco);
        rate_table->refdiv = fin_hz / clk_gcd;
        rate_table->fbdiv = foutvco / clk_gcd;

        rate_table->frac = 0;
    }
    else
    {
        clk_gcd = gcd(fin_hz / MHZ, foutvco / MHZ);
        rate_table->refdiv = fin_hz / MHZ / clk_gcd;
        rate_table->fbdiv = foutvco / MHZ / clk_gcd;

        rate_table->frac = 0;

        f_frac = (foutvco % MHZ);
        fin_64 = fin_hz;
        fin_64 = fin_64 / rate_table->refdiv;
        frac_64 = f_frac << 24;
        frac_64 = frac_64 / fin_64;
        rate_table->frac = frac_64;

        if (rate_table->frac > 0)
        {
            rate_table->dsmpd = 0;
        }
    }
    return rate_table;
}

static struct rk_pll_rate_table *
rk3588_pll_clk_set_by_auto(rt_ubase_t fin_hz,
               rt_ubase_t fout_hz)
{
    struct rk_pll_rate_table *rate_table = &auto_table;
    rt_uint32_t p, m, s;
    rt_ubase_t fvco, fref, fout, ffrac;

    if (fin_hz == 0 || fout_hz == 0 || fout_hz == fin_hz)
        return NULL;

    if (fout_hz > RK3588_FOUT_MAX_HZ || fout_hz < RK3588_FOUT_MIN_HZ)
        return NULL;

    if (fin_hz / MHZ * MHZ == fin_hz && fout_hz / MHZ * MHZ == fout_hz)
    {
        for (s = 0; s <= 6; s++)
        {
            fvco = fout_hz << s;
            if (fvco < RK3588_VCO_MIN_HZ ||
                fvco > RK3588_VCO_MAX_HZ)
                continue;
            for (p = 2; p <= 4; p++)
            {
                for (m = 64; m <= 1023; m++)
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
        LOG_E("CANNOT FIND Fout by auto,fout = %lu\n", fout_hz);
    } else {
        for (s = 0; s <= 6; s++)
        {
            fvco = fout_hz << s;
            if (fvco < RK3588_VCO_MIN_HZ ||
                fvco > RK3588_VCO_MAX_HZ)
                continue;
            for (p = 1; p <= 4; p++)
            {
                for (m = 64; m <= 1023; m++)
                {
                    if ((fvco >= m * fin_hz / p) && (fvco < (m + 1) * fin_hz / p))
                    {
                        rate_table->p = p;
                        rate_table->m = m;
                        rate_table->s = s;
                        fref = fin_hz / p;
                        ffrac = fvco - (m * fref);
                        fout = ffrac * 65536;
                        rate_table->k = fout / fref;
                        return rate_table;
                    }
                }
            }
        }
        LOG_E("CANNOT FIND Fout by auto,fout = %lu\n", fout_hz);
    }
    return NULL;
}

static const struct rk_pll_rate_table *rk_get_pll_settings(struct rk_pll_clock *pll, rt_ubase_t rate)
{
    struct rk_pll_rate_table *rate_table = pll->rate_table;

    while (rate_table->rate)
    {
        if (rate_table->rate == rate)
        {
            break;
        }
        ++rate_table;
    }

    if (rate_table->rate != rate)
    {
        if (pll->type == pll_rk3588)
            return rk3588_pll_clk_set_by_auto(24 * MHZ, rate);
        else
            return rk_pll_clk_set_by_auto(24 * MHZ, rate);
    }
    else
    {
        return rate_table;
    }
}

static int rk3036_pll_set_rate(struct rk_pll_clock *pll, void *base, rt_ubase_t pll_id, rt_ubase_t drate)
{
    const struct rk_pll_rate_table *rate;

    rate = rk_get_pll_settings(pll, drate);

    if (!rate)
    {
        return -RT_ERROR;
    }

    /*
     * When power on or changing PLL setting, we must force PLL into slow mode
     * to ensure output stable clock.
     */
    rk_clrsetreg(base + pll->mode_offset, pll->mode_mask << pll->mode_shift, RKCLK_PLL_MODE_SLOW << pll->mode_shift);

    /* Power down */
    rk_setreg(base + pll->con_offset + 0x4, 1 << RK3036_PLLCON1_PWRDOWN_SHIT);

    rk_clrsetreg(base + pll->con_offset, (RK3036_PLLCON0_POSTDIV1_MASK | RK3036_PLLCON0_FBDIV_MASK),
            (rate->postdiv1 << RK3036_PLLCON0_POSTDIV1_SHIFT) |rate->fbdiv);
    rk_clrsetreg(base + pll->con_offset + 0x4, (RK3036_PLLCON1_POSTDIV2_MASK | RK3036_PLLCON1_REFDIV_MASK),
            (rate->postdiv2 << RK3036_PLLCON1_POSTDIV2_SHIFT | rate->refdiv << RK3036_PLLCON1_REFDIV_SHIFT));

    if (!rate->dsmpd)
    {
        rt_uint32_t val;

        rk_clrsetreg(base + pll->con_offset + 0x4, RK3036_PLLCON1_DSMPD_MASK,
                rate->dsmpd << RK3036_PLLCON1_DSMPD_SHIFT);

        val = HWREG32(base + pll->con_offset + 0x8) & (~RK3036_PLLCON2_FRAC_MASK);
        HWREG32(base + pll->con_offset + 0x8) = val | (rate->frac << RK3036_PLLCON2_FRAC_SHIFT);
    }

    /* Power Up */
    rk_clrreg(base + pll->con_offset + 0x4, 1 << RK3036_PLLCON1_PWRDOWN_SHIT);

    /* Waiting for pll lock */
    while (!(HWREG32(base + pll->con_offset + 0x4) & (1 << pll->lock_shift)))
    {
    }

    rk_clrsetreg(base + pll->mode_offset, pll->mode_mask << pll->mode_shift, RKCLK_PLL_MODE_NORMAL << pll->mode_shift);

    return 0;
}

static rt_ubase_t rk3036_pll_get_rate(struct rk_pll_clock *pll, void *base, rt_ubase_t pll_id)
{
    rt_uint32_t refdiv, fbdiv, postdiv1, postdiv2, dsmpd, frac;
    rt_uint32_t con = 0, shift, mask;
    rt_ubase_t rate;

    pll->mode_mask = PLL_MODE_MASK;

    con = HWREG32(base + pll->mode_offset);
    shift = pll->mode_shift;
    mask = pll->mode_mask << shift;

    switch ((con & mask) >> shift)
    {
    case RKCLK_PLL_MODE_SLOW:
        return OSC_HZ;
    case RKCLK_PLL_MODE_NORMAL:
        /* normal mode */
        con = HWREG32(base + pll->con_offset);
        postdiv1 = (con & RK3036_PLLCON0_POSTDIV1_MASK) >> RK3036_PLLCON0_POSTDIV1_SHIFT;
        fbdiv = (con & RK3036_PLLCON0_FBDIV_MASK) >> RK3036_PLLCON0_FBDIV_SHIFT;
        con = HWREG32(base + pll->con_offset + 0x4);
        postdiv2 = (con & RK3036_PLLCON1_POSTDIV2_MASK) >> RK3036_PLLCON1_POSTDIV2_SHIFT;
        refdiv = (con & RK3036_PLLCON1_REFDIV_MASK) >> RK3036_PLLCON1_REFDIV_SHIFT;
        dsmpd = (con & RK3036_PLLCON1_DSMPD_MASK) >> RK3036_PLLCON1_DSMPD_SHIFT;
        con = HWREG32(base + pll->con_offset + 0x8);
        frac = (con & RK3036_PLLCON2_FRAC_MASK) >> RK3036_PLLCON2_FRAC_SHIFT;
        rate = (24 * fbdiv / (refdiv * postdiv1 * postdiv2)) * 1000000;

        if (dsmpd == 0)
        {
            rt_uint64_t frac_rate = OSC_HZ * (rt_uint64_t)frac;

            rt_do_div(frac_rate, refdiv);
            frac_rate >>= 24;
            rt_do_div(frac_rate, postdiv1);
            rt_do_div(frac_rate, postdiv1);
            rate += frac_rate;
        }
        return rate;
    case RKCLK_PLL_MODE_DEEP:
    default:
        return 32768;
    }
}

static int rk3588_pll_set_rate(struct rk_pll_clock *pll,
                   void *base, rt_ubase_t pll_id,
                   rt_ubase_t drate)
{
    const struct rk_pll_rate_table *rate;

    rate = rk_get_pll_settings(pll, drate);
    if (!rate)
    {
        LOG_D("%s unsupported rate\n", __func__);
        return -RT_EINVAL;
    }

    LOG_D("%s: rate settings for %lu p: %d, m: %d, s: %d, k: %d\n",
          __func__, rate->rate, rate->p, rate->m, rate->s, rate->k);

    /*
     * When power on or changing PLL setting,
     * we must force PLL into slow mode to ensure output stable clock.
     */
    if (pll_id == 3)
        rk_clrsetreg(base + 0x84c, 0x1 << 1, 0x1 << 1);

    rk_clrsetreg(base + pll->mode_offset,
             pll->mode_mask << pll->mode_shift,
             RKCLK_PLL_MODE_SLOW << pll->mode_shift);
    if (pll_id == 0)
        rk_clrsetreg(base + RK3588_B0PLL_CLKSEL_CON(0),
                 pll->mode_mask << 6,
                 RKCLK_PLL_MODE_SLOW << 6);
    else if (pll_id == 1)
        rk_clrsetreg(base + RK3588_B1PLL_CLKSEL_CON(0),
                 pll->mode_mask << 6,
                 RKCLK_PLL_MODE_SLOW << 6);
    else if (pll_id == 2)
        rk_clrsetreg(base + RK3588_LPLL_CLKSEL_CON(5),
                 pll->mode_mask << 14,
                 RKCLK_PLL_MODE_SLOW << 14);

    /* Power down */
    rk_setreg(base + pll->con_offset + RK3588_PLLCON(1),
          RK3588_PLLCON1_PWRDOWN);

    rk_clrsetreg(base + pll->con_offset,
             RK3588_PLLCON0_M_MASK,
             (rate->m << RK3588_PLLCON0_M_SHIFT));
    rk_clrsetreg(base + pll->con_offset + RK3588_PLLCON(1),
             (RK3588_PLLCON1_P_MASK |
             RK3588_PLLCON1_S_MASK),
             (rate->p << RK3588_PLLCON1_P_SHIFT |
             rate->s << RK3588_PLLCON1_S_SHIFT));
    if (rate->k)
    {
        rk_clrsetreg(base + pll->con_offset + RK3588_PLLCON(2),
                 RK3588_PLLCON2_K_MASK,
                 rate->k << RK3588_PLLCON2_K_SHIFT);
    }
    /* Power up */
    rk_clrreg(base + pll->con_offset + RK3588_PLLCON(1),
          RK3588_PLLCON1_PWRDOWN);

    /* waiting for pll lock */
    while (!(HWREG32(base + pll->con_offset + RK3588_PLLCON(6)) &
        RK3588_PLLCON6_LOCK_STATUS))
    {
    }

    rk_clrsetreg(base + pll->mode_offset, pll->mode_mask << pll->mode_shift,
             RKCLK_PLL_MODE_NORMAL << pll->mode_shift);
    if (pll_id == 0)
    {
        rk_clrsetreg(base + RK3588_B0PLL_CLKSEL_CON(0),
                 pll->mode_mask << 6,
                 2 << 6);
        rk_clrsetreg(base + RK3588_B0PLL_CLKSEL_CON(0),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_B02_DIV_SHIFT,
                 0 << RK3588_CORE_B02_DIV_SHIFT);
        rk_clrsetreg(base + RK3588_B0PLL_CLKSEL_CON(1),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_B13_DIV_SHIFT,
                 0 << RK3588_CORE_B13_DIV_SHIFT);
    } else if (pll_id == 1)
    {
        rk_clrsetreg(base + RK3588_B1PLL_CLKSEL_CON(0),
                 pll->mode_mask << 6,
                 2 << 6);
        rk_clrsetreg(base + RK3588_B1PLL_CLKSEL_CON(0),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_B02_DIV_SHIFT,
                 0 << RK3588_CORE_B02_DIV_SHIFT);
        rk_clrsetreg(base + RK3588_B1PLL_CLKSEL_CON(1),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_B13_DIV_SHIFT,
                 0 << RK3588_CORE_B13_DIV_SHIFT);
    } else if (pll_id == 2)
    {
        rk_clrsetreg(base + RK3588_LPLL_CLKSEL_CON(5),
                 pll->mode_mask << 14,
                 2 << 14);
        rk_clrsetreg(base + RK3588_LPLL_CLKSEL_CON(6),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_L13_DIV_SHIFT,
                 0 << RK3588_CORE_L13_DIV_SHIFT);
        rk_clrsetreg(base + RK3588_LPLL_CLKSEL_CON(6),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_L02_DIV_SHIFT,
                 0 << RK3588_CORE_L02_DIV_SHIFT);
        rk_clrsetreg(base + RK3588_LPLL_CLKSEL_CON(7),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_L13_DIV_SHIFT,
                 0 << RK3588_CORE_L13_DIV_SHIFT);
        rk_clrsetreg(base + RK3588_LPLL_CLKSEL_CON(7),
                 RK3588_CORE_DIV_MASK << RK3588_CORE_L02_DIV_SHIFT,
                 0 << RK3588_CORE_L02_DIV_SHIFT);
    }

    if (pll_id == 3)
        rk_clrsetreg(base + 0x84c, 0x1 << 1, 0);

    LOG_D("PLL at %p: con0=%x con1= %x con2= %x mode= %x\n",
          pll, HWREG32(base + pll->con_offset),
          HWREG32(base + pll->con_offset + 0x4),
          HWREG32(base + pll->con_offset + 0x8),
          HWREG32(base + pll->mode_offset));

    return 0;
}

static rt_ubase_t rk3588_pll_get_rate(struct rk_pll_clock *pll,
                 void *base, rt_ubase_t pll_id)
{
    rt_uint32_t m, p, s, k;
    rt_uint32_t con = 0, shift, mode;
    rt_uint64_t rate, postdiv;

    con = HWREG32(base + pll->mode_offset);
    shift = pll->mode_shift;
    if (pll_id == 8)
        mode = RKCLK_PLL_MODE_NORMAL;
    else
        mode = (con & (pll->mode_mask << shift)) >> shift;
    switch (mode)
    {
    case RKCLK_PLL_MODE_SLOW:
        return OSC_HZ;
    case RKCLK_PLL_MODE_NORMAL:
        /* normal mode */
        con = HWREG32(base + pll->con_offset);
        m = (con & RK3588_PLLCON0_M_MASK) >>
               RK3588_PLLCON0_M_SHIFT;
        con = HWREG32(base + pll->con_offset + RK3588_PLLCON(1));
        p = (con & RK3588_PLLCON1_P_MASK) >>
               RK3036_PLLCON0_FBDIV_SHIFT;
        s = (con & RK3588_PLLCON1_S_MASK) >>
             RK3588_PLLCON1_S_SHIFT;
        con = HWREG32(base + pll->con_offset + RK3588_PLLCON(2));
        k = (con & RK3588_PLLCON2_K_MASK) >>
            RK3588_PLLCON2_K_SHIFT;

        rate = OSC_HZ / p;
        rate *= m;
        if (k)
        {
            /* fractional mode */
            rt_uint64_t frac_rate64 = OSC_HZ * k;

            postdiv = p * 65536;
            rt_do_div(frac_rate64, postdiv);
            rate += frac_rate64;
        }
        rate = rate >> s;
        return rate;
    case RKCLK_PLL_MODE_DEEP:
    default:
        return 32768;
    }
}

rt_ubase_t rk_pll_get_rate(struct rk_pll_clock *pll,
                void *base,
                rt_ubase_t pll_id)
{
    rt_ubase_t rate = 0;

    switch (pll->type)
    {
    case pll_rk3036:
        pll->mode_mask = PLL_MODE_MASK;
        rate = rk3036_pll_get_rate(pll, base, pll_id);
        break;
    case pll_rk3328:
        pll->mode_mask = PLL_RK3328_MODE_MASK;
        rate = rk3036_pll_get_rate(pll, base, pll_id);
        break;
    case pll_rk3588:
        pll->mode_mask = PLL_MODE_MASK;
        rate = rk3588_pll_get_rate(pll, base, pll_id);
        break;
    default:
        LOG_D("%s: Unknown pll type for pll clk %ld\n",
               __func__, pll_id);
    }
    return rate;
}

int rk_pll_set_rate(struct rk_pll_clock *pll,
              void *base, rt_ubase_t pll_id,
              rt_ubase_t drate)
{
    int ret = 0;

    if (rk_pll_get_rate(pll, base, pll_id) == drate)
        return 0;

    switch (pll->type)
    {
    case pll_rk3036:
        pll->mode_mask = PLL_MODE_MASK;
        ret = rk3036_pll_set_rate(pll, base, pll_id, drate);
        break;
    case pll_rk3328:
        pll->mode_mask = PLL_RK3328_MODE_MASK;
        ret = rk3036_pll_set_rate(pll, base, pll_id, drate);
        break;
    case pll_rk3588:
        pll->mode_mask = PLL_MODE_MASK;
        ret = rk3588_pll_set_rate(pll, base, pll_id, drate);
        break;
    default:
        LOG_D("%s: Unknown pll type for pll clk %ld\n",
               __func__, pll_id);
    }
    return ret;
}

const struct rk_cpu_rate_table *rk_get_cpu_settings(struct rk_cpu_rate_table *cpu_table, rt_ubase_t rate)
{
    struct rk_cpu_rate_table *ps = cpu_table;

    while (ps->rate)
    {
        if (ps->rate == rate)
        {
            break;
        }
        ++ps;
    }
    if (ps->rate != rate)
    {
        return RT_NULL;
    }
    else
    {
        return ps;
    }
}

rt_base_t rk_clk_pll_round_rate(const struct rk_pll_rate_table *pll_rates,
        rt_size_t rate_count, rt_ubase_t drate, rt_ubase_t *prate)
{
    int i;

    /* Assumming rate_table is in descending order */
    for (i = 0; i < rate_count; i++)
    {
        if (drate >= pll_rates[i].rate)
        {
            return pll_rates[i].rate;
        }
    }

    /* return minimum supported value */
    return pll_rates[i - 1].rate;
}

void rk_clk_set_default_rates(struct rt_clk *clk,
        rt_err_t (*clk_set_rate)(struct rt_clk *, rt_ubase_t, rt_ubase_t), int id)
{
    rt_uint32_t rate;
    struct rt_ofw_cell_args clk_args;
    struct rt_ofw_node *np = clk->fw_node;
    const char *rate_propname = "assigned-clock-rates";

    if (!rt_ofw_prop_read_bool(np, rate_propname))
    {
        return;
    }

    for (int i = 0; ; ++i)
    {
        if (rt_ofw_parse_phandle_cells(np, "assigned-clocks", "#clock-cells", i, &clk_args))
        {
            break;
        }

        rt_ofw_node_put(clk_args.data);

        if (clk_args.args[0] != id)
        {
            continue;
        }

        if (!rt_ofw_prop_read_u32_index(np, rate_propname, i, &rate))
        {
            clk_set_rate(clk, rate, 0);
        }

        break;
    }
}
