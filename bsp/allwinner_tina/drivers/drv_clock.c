/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#include <rtthread.h>
#include <rthw.h>

#include "drv_clock.h"

int cpu_get_pll_clk(void)
{
    rt_uint32_t reg;
    int n, k, m, p;

    reg = CCU->pll_cpu_ctrl;
    if (!(reg & (0x01 << 31)))
        return 0;

    p = PLL_CPU_DIV_P(reg) + 1;
    n = PLL_CPU_FACTOR_N(reg) + 1;
    k = PLL_CPU_FACTOR_K(reg) + 1;
    m = PLL_CPU_FACTOR_M(reg) + 1;
    //(24MHz*n*k)/(m*p)
    return (_24MHZ_ * n * k) / (m * p);
}

int audio_get_pll_clk(void)
{
    rt_uint32_t reg;
    unsigned char n, m;

    reg = CCU->pll_audio_ctrl;
    if (!(reg & (0x01 << 31)))
        return 0;

    n = PLL_AUDIO_FACTOR_N(reg) + 1;
    m = PLL_AUDIO_PREDIV_M(reg) + 1;

    //24MHz*n*2/m
    return _24MHZ_ * 2 * n / m;
}

int video_get_pll_clk(void)
{
    rt_uint32_t reg;
    int n, m;

    reg = CCU->pll_video_ctrl;
    if (!(reg & (0x01 << 31)))
        return 0;

    if (reg & PLL_VIDEO_MODE_SEL)
    {
        //(24MHz*n)/m
        n = PLL_VIDEO_FACTOR_N(reg) + 1;
        m = PLL_VIDEO_PREDIV_M(reg) + 1;
        return (_24MHZ_ * n) / m;
    }

    if (reg & PLL_VIDEO_FRAC_CLK_OUT)
        return 270000000;
    else
        return 297000000;

    return 0;
}

int ve_get_pll_clk(void)
{
    rt_uint32_t reg;
    int n, m;

    reg = CCU->pll_ve_ctrl;
    if (!(reg & (0x01 << 31)))
        return 0;

    if (reg & PLL_VE_MODE_SEL)
    {
        //(24MHz*n)/m
        n = PLL_VE_FACTOR_N(reg) + 1;
        m = PLL_VE_PREDIV_M(reg) + 1;

        return (_24MHZ_ * n) / m;
    }

    if (reg & PLL_VE_FRAC_CLK_OUT)
        return 297000000;
    else
        return 270000000;

    return 0;
}

int ddr_get_pll_clk(void)
{
    rt_uint32_t reg;
    int n, k, m;

    reg = CCU->pll_ddr_ctrl;
    if (!(reg & (0x01 << 31)))
        return 0;

    n = PLL_DDR_FACTOR_N(reg) + 1;
    k = PLL_DDR_FACTOR_K(reg) + 1;
    m = PLL_DDR_FACTOR_M(reg) + 1;

    //(24MHz*n*k)/m
    return (_24MHZ_ * n * k) / m;
}

int periph_get_pll_clk(void)
{
    rt_uint32_t reg;
    int n, k;

    reg = CCU->pll_periph_ctrl;
    if (!(reg & (0x01 << 31)))
        return 0;

    n = PLL_PERIPH_FACTOR_N(reg) + 1;
    k = PLL_PERIPH_FACTOR_K(reg) + 1;

    return _24MHZ_ * n * k;
}

static int cpu_get_clk_src(void)
{
    return (CCU->cpu_clk_src >> 16) & 0x3;
}

int cpu_get_clk(void)
{
    rt_uint32_t reg;
    int cpusrc;

    reg = CCU->ahb_apb_hclkc_cfg;
    cpusrc = cpu_get_clk_src();

    if (cpusrc == CLK_PLL_SRC)
        return (cpu_get_pll_clk() / (HCLKC_DIV(reg) + 1));
    else if (cpusrc == CLK_OSC24M_SRC)
        return _24MHZ_ / (HCLKC_DIV(reg) + 1);
    else
        return _32KHZ_ / (HCLKC_DIV(reg) + 1);  //猜测 内部32KHz时钟

    return 0;
}

int ahb_get_clk(void)
{
    rt_uint32_t reg;
    int sel, spd;

    reg = CCU->ahb_apb_hclkc_cfg;
    sel = AHB_SRC_SEL(reg);

    if (sel == CLK_PLL_SRC)
    {
        spd = cpu_get_clk();
        return spd / (1 << AHB_CLK_DIV(reg));
    }
    else if (sel == PRE_DIV_SRC)
    {
        spd = periph_get_pll_clk();
        return spd / (AHB_PRE_DIV(reg) + 1) / (1 << AHB_CLK_DIV(reg));
    }
    else if (sel == CLK_OSC24M_SRC)
        return _24MHZ_ / (1 << AHB_CLK_DIV(reg));
    else
        return _32KHZ_ / (1 << AHB_CLK_DIV(reg));
}

int apb_get_clk(void)
{
    rt_uint32_t reg;
    int spd;

    reg = CCU->ahb_apb_hclkc_cfg;
    spd = ahb_get_clk();
    // 0x:/2 10:/4 11:/8
    if (!(APH_CLK_PATIO(reg) & 0x1))
        return spd / 2;
    else
        return spd / (1 << APH_CLK_PATIO(reg));
}


static rt_err_t wait_pll_stable(rt_uint32_t base)
{
    rt_uint32_t rval = 0;
    volatile int time = 0xfff;

    do
    {
        rval = *((volatile rt_uint32_t *)base);
        time--;
    }
    while (time && !(rval & (1 << 28)));

    return !time;
}

rt_err_t cpu_set_pll_clk(int clk)
{
    rt_uint32_t cpu_src;
    int p = 0, k = 1, m = 1, n = 0;

    if (clk == 0)
        return RT_EINVAL;

    if (clk > 1152000000)
    {
        k = 2;
    }
    else if (clk > 768000000)
    {
        k = 3;
        m = 2;
    }

    n = clk / (_24MHZ_ * k / m) - 1;
    cpu_src = (CCU->cpu_clk_src >> 16) & 0x3;
    CCU->cpu_clk_src = CLK_OSC24M_SRC << 16;
    CCU->pll_cpu_ctrl &= ~(0x1 << 31);
    //PLL1 rate = ((24000000 * n * k) >> 0) / m   (p is ignored)
    CCU->pll_cpu_ctrl = (0x1 << 31) | (m << 0) | (k << 4) | (n << 8) | (p << 16);
    if (wait_pll_stable((rt_uint32_t)(&CCU->pll_cpu_ctrl)))
        return RT_ERROR;

    CCU->cpu_clk_src = cpu_src << 16;

    return RT_EOK;
}

rt_err_t audio_set_pll_clk(int clk)
{
    int n = 0, m = 0;
    int n_temp = clk;
    int m_temp = _24MHZ_ * 2;

    if ((clk > 200000000) || (clk < 20000000))
        return RT_EINVAL;

    if (clk == 0)
    {
        CCU->pll_audio_ctrl &= ~(0x1 << 31);
        return RT_EOK;
    }

    while (n_temp != m_temp)
    {
        if (n_temp > m_temp)
        {
            n_temp = n_temp - m_temp;
        }
        else if (m_temp > n_temp)
        {
            m_temp = m_temp - n_temp;
        }
    }

    n = clk / n_temp;
    m = _24MHZ_ * 2 / m_temp;
    if ((n > 128) || (m > 32) || (clk != (_24MHZ_ * n * 2) / m))
        return RT_ERROR;

    CCU->pll_audio_ctrl &= ~(0x1 << 31);
    n = (n - 1) & 0x7f;
    m = (m - 1) & 0x1f;
    //clk = (24 * n * 2) / m
    CCU->pll_audio_ctrl = (0x1 << 31) | (0x0 << 24) | (n << 8) | m;

    if (wait_pll_stable((rt_uint32_t)(&CCU->pll_audio_ctrl)))
        return RT_ERROR;
    else
        return RT_EOK;
}

rt_err_t video_set_pll_clk(int clk)
{
    int n = 0, m = 0;
    int n_temp = clk;
    int m_temp = _24MHZ_;

    if ((clk > 600000000) || (clk < 30000000))
        return RT_EINVAL;

    if (clk == 0)
    {
        CCU->pll_video_ctrl &= ~(0x1 << 31);
        return RT_EOK;
    }

    while (n_temp != m_temp)
    {
        if (n_temp > m_temp)
        {
            n_temp = n_temp - m_temp;
        }
        else if (m_temp > n_temp)
        {
            m_temp = m_temp - n_temp;
        }
    }

    n = clk / n_temp;
    m = _24MHZ_ / m_temp;

    if ((n > 128) || (m > 16) || (clk != (_24MHZ_ * n) / m))
        return RT_ERROR;

    CCU->pll_video_ctrl &= ~(0x1 << 31);
    n = (n - 1) & 0x7f;
    m = (m - 1) & 0xf;
    //speed = (24*n)/m
    CCU->pll_video_ctrl = (0x1 << 31) | (0x0 << 30) | (0x1 << 24) | (n << 8) | m;

    if (wait_pll_stable((rt_uint32_t)(&CCU->pll_video_ctrl)))
        return RT_ERROR;
    else
        return RT_EOK;
}

rt_err_t ve_set_pll_clk(int clk)
{
    int n = 0, m = 0;
    int n_temp = clk;
    int m_temp = _24MHZ_;

    if ((clk > 600000000) || (clk < 30000000))
        return RT_EINVAL;

    if (clk == 0)
    {
        CCU->pll_ve_ctrl &= ~(0x1 << 31);
        return RT_EOK;
    }

    while (n_temp != m_temp)
    {
        if (n_temp > m_temp)
        {
            n_temp = n_temp - m_temp;
        }
        else if (m_temp > n_temp)
        {
            m_temp = m_temp - n_temp;
        }
    }

    n = clk / n_temp;
    m = _24MHZ_ / m_temp;

    if ((n > 128) || (m > 16) || (clk != (_24MHZ_ * n) / m))
        return RT_ERROR;

    CCU->pll_ve_ctrl &= ~(0x1 << 31);
    n = (n - 1) & 0x7f;
    m = (m - 1) & 0xf;
    //clk = (24 * n) / m
    CCU->pll_ve_ctrl = (0x1 << 31) | (0x1 << 24) | (n << 8) | m;
    if (wait_pll_stable((rt_uint32_t)(&CCU->pll_ve_ctrl)))
        return RT_ERROR;
    else
        return RT_EOK;
}

rt_err_t periph_set_pll_clk(int clk)
{
    rt_uint32_t clk_src;
    rt_uint32_t temp_data;
    int n = 0, k = 0;

    if ((clk > 1800000000) || (clk < 200000000) || (clk == 0) || (clk % _24MHZ_ != 0))
        return RT_EINVAL;

    n = clk / _24MHZ_;

    for (k = 2; ((n > 32) || (k < 5)); k++)
    {
        if ((n % k) != 0)
            n /= k;
    }

    if ((n > 32) || (k > 4) || (clk != (_24MHZ_ * n * k)))
        return RT_ERROR;
    temp_data = CCU->ahb_apb_hclkc_cfg;
    clk_src = (temp_data >> 12) & 0x3;
    temp_data &= ~(0x3 << 12);
    temp_data |= (CLK_PLL_SRC << 12);
    CCU->ahb_apb_hclkc_cfg = temp_data;
    CCU->pll_periph_ctrl &= ~(0x1 << 31);
    n = (n - 1) & 0x1f;
    k = (k - 1) & 0x3;
    //clk = 24 * n *k
    CCU->pll_periph_ctrl = (0x1 << 31) | (0x1 << 18) | (n << 8) | (k << 4) || (0x1);
    if (wait_pll_stable((rt_uint32_t)(&CCU->pll_periph_ctrl)))
        return RT_ERROR;

    temp_data = CCU->ahb_apb_hclkc_cfg;
    temp_data &= ~(0x3 << 12);
    temp_data |= (clk_src << 12);
    CCU->ahb_apb_hclkc_cfg = temp_data;

    return RT_EOK;
}

rt_err_t cpu_set_clk(int clk)
{
    if (clk < _24MHZ_)
        return RT_EINVAL;

    if (clk == cpu_get_clk())
        return RT_EOK;

    CCU->cpu_clk_src = CLK_OSC24M_SRC << 16;
    if (clk == _24MHZ_)
        return RT_EOK;

    if (cpu_set_pll_clk(clk))
        return RT_ERROR;

    CCU->ahb_apb_hclkc_cfg &= ~(0x3 << 16);
    CCU->cpu_clk_src = CLK_PLL_SRC << 16;

    return RT_EOK;
}

rt_err_t bus_gate_clk_enalbe(enum bus_gate bus)
{
    rt_uint32_t offset;
    rt_uint32_t gate_reg;

    offset = bus & 0xfff;
    gate_reg = bus >> BUS_GATE_OFFSET_BIT;

    if (gate_reg == 0x00)
        CCU->bus_clk_gating0 |= (0x1 << offset);
    else if (gate_reg == 0x01)
        CCU->bus_clk_gating1 |= (0x1 << offset);
    else if (gate_reg == 0x02)
        CCU->bus_clk_gating2 |= (0x1 << offset);
    else
        return RT_EINVAL;

    return RT_EOK;
}

rt_err_t bus_gate_clk_disalbe(enum bus_gate bus)
{
    rt_uint32_t offset;
    rt_uint32_t gate_reg;

    offset = bus & 0xfff;
    gate_reg = bus >> BUS_GATE_OFFSET_BIT;

    if (gate_reg == 0x00)
        CCU->bus_clk_gating0 &= ~(0x1 << offset);
    else if (gate_reg == 0x01)
        CCU->bus_clk_gating1 &= ~(0x1 << offset);
    else if (gate_reg == 0x02)
        CCU->bus_clk_gating2 &= ~(0x1 << offset);
    else
        return RT_EINVAL;

    return RT_EOK;
}

rt_err_t bus_software_reset_disalbe(enum bus_gate bus)
{
    rt_uint32_t offset;
    rt_uint32_t gate_reg;

    offset = bus & 0xfff;
    gate_reg = bus >> BUS_GATE_OFFSET_BIT;

    if (gate_reg == 0x00)
        CCU->bus_soft_rst0 |= (0x1 << offset);
    else if (gate_reg == 0x01)
        CCU->bus_soft_rst1 |= (0x1 << offset);
    else if (gate_reg == 0x02)
        CCU->bus_soft_rst2 |= (0x1 << offset);
    else
        return RT_EINVAL;

    return RT_EOK;
}

rt_err_t bus_software_reset_enalbe(enum bus_gate bus)
{
    rt_uint32_t offset;
    rt_uint32_t gate_reg;

    offset = bus & 0xfff;
    gate_reg = bus >> BUS_GATE_OFFSET_BIT;

    if (gate_reg == 0x00)
        CCU->bus_soft_rst0 &= ~(0x1 << offset);
    else if (gate_reg == 0x01)
        CCU->bus_soft_rst1 &= ~(0x1 << offset);
    else if (gate_reg == 0x02)
        CCU->bus_soft_rst2 &= ~(0x1 << offset);
    else
        return RT_EINVAL;

    return RT_EOK;
}

rt_err_t mmc_set_clk(enum mmc_clk_id clk_id, int hz)
{
    unsigned int pll, pll_hz, div, n, oclk_dly, sclk_dly;
    volatile rt_uint32_t *mmc_clk = (clk_id == SDMMC0) ? \
        (&CCU->sdmmc0_clk) : (&CCU->sdmmc1_clk);

    if (hz < 0)
    {
        return RT_EINVAL;
    }

    if (hz == 0)
    {
        *mmc_clk &= ~(0x1 << 31);
        return RT_EOK;
    }

    if (hz <= 24000000)
    {
        pll = (0x0 << 24);
        pll_hz = 24000000;
    }
    else
    {
        pll = (0x1 << 24);
        pll_hz = periph_get_pll_clk();
    }

    div = pll_hz / hz;
    if (pll_hz % hz)
    {
        div++;
    }

    n = 0;
    while (div > 16)
    {
        n++;
        div = (div + 1) / 2;
    }

    if (n > 3)
    {
        return -1;
    }

    /* determine delays */
    if (hz <= 400000)
    {
        oclk_dly = 0;
        sclk_dly = 0;
    }
    else if (hz <= 25000000)
    {
        oclk_dly = 0;
        sclk_dly = 5;
    }
    else if (hz <= 50000000)
    {
        oclk_dly = 3;
        sclk_dly = 4;
    }
    else
    {
        /* hz > 50000000 */
        oclk_dly = 1;
        sclk_dly = 4;
    }

    *mmc_clk = (0x1 << 31) | pll | (sclk_dly << 20) | \
           (n << 16) | (oclk_dly << 8) | (div - 1);

    return RT_EOK;
}

rt_err_t dram_gate_clk_enable(enum dram_gate dram_gate)
{
    CCU->dram_gating |= (0x01 << dram_gate);
    return RT_EOK;
}

rt_err_t dram_gate_clk_disable(enum dram_gate dram_gate)
{
    CCU->dram_gating &= ~(0x01 << dram_gate);
    return RT_EOK;
}
