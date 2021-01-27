/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 *
 * Copyright (c) 2020, duhuanpeng<548708880@qq.com>
 * legacy driver APIs from loongson 1C BSP.
 */

#include <rtthread.h>
#include "ls2k1000.h"

struct loongson_pll
{
    rt_uint64_t PLL_SYS_0;
    rt_uint64_t PLL_SYS_1;
    rt_uint64_t PLL_DDR_0;
    rt_uint64_t PLL_DDR_1;
    rt_uint64_t PLL_DC_0;
    rt_uint64_t PLL_DC_1;
    rt_uint64_t PLL_PIX0_0;
    rt_uint64_t PLL_PIX0_1;
    rt_uint64_t PLL_PIX1_0;
    rt_uint64_t PLL_PIX1_1;
    rt_uint64_t FREQSCALE;
};

/* See the Schematic */
#define SYS_CLKSEL1 1
#define SYS_CLKSEL0 0

/* bit field helpers. */
#define __M(n)               (~(~0<<(n)))
#define __RBF(number, n)     ((number)&__M(n))
#define __BF(number, n, m)   __RBF((number>>m), (n-m+1))
#define BF(number, n, m)     (m<n ? __BF(number, n, m) : __BF(number, m, n))

int refclk = 100;
int gmac_clock = 125;

volatile struct loongson_pll *pll = (void *)PLL_SYS_BASE;


unsigned long clk_get_pll_rate(void)
{
    return -RT_ENOSYS;

}

unsigned long clk_get_cpu_rate(void)
{
    unsigned long node_clock;
    int l1_div_ref;
    int l1_div_loopc;
    int l2_div_out_node;

    l1_div_ref      = BF(pll->PLL_SYS_0, 26, 31);
    l1_div_loopc    = BF(pll->PLL_SYS_0, 32, 41);
    l2_div_out_node = BF(pll->PLL_SYS_1,  5,  0);

    node_clock = refclk / l1_div_ref * l1_div_loopc / l2_div_out_node;
    return node_clock;
}

unsigned long clk_get_ddr_rate(void)
{
    unsigned long ddr_clock;
    int l1_div_ref;
    int l1_div_loopc;
    int l2_div_out_ddr;

    l1_div_ref     = BF(pll->PLL_DDR_0, 26, 31);
    l1_div_loopc   = BF(pll->PLL_DDR_0, 32, 41);
    l2_div_out_ddr = BF(pll->PLL_DDR_1, 0, 5);

    ddr_clock = refclk / l1_div_ref * l1_div_loopc / l2_div_out_ddr;
    return ddr_clock;
}

unsigned long clk_get_apb_rate(void)
{
    unsigned long apb_clock;
    int apb_freqscale;

    apb_freqscale = BF(pll->FREQSCALE, 22, 20);

    /* gmac clock is fixed 125MHz */
    apb_clock = gmac_clock * (apb_freqscale + 1) / 8;
    return apb_clock;

}

unsigned long clk_get_dc_rate(void)
{
    return -RT_ENOSYS;
}
