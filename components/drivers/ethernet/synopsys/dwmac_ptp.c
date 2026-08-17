/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "dwmac_ptp.h"

#define DBG_TAG "eth.dwmac.ptp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define NSEC_PER_SEC        1000000000LL

static rt_err_t dwmac_ptp_poll_tcr(struct dwmac_eth *eth, rt_uint32_t mask,
        rt_bool_t wait_clear)
{
    rt_uint32_t val;
    rt_tick_t start = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond(100);

    while (rt_tick_get() - start < timeout)
    {
        val = dwmac_ptp_readl(eth, PTP_TCR);
        if (wait_clear ? !(val & mask) : (val & mask))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(10);
    }

    return -RT_ETIMEOUT;
}

static void dwmac_ptp_config_hw_tstamping(struct dwmac_eth *eth, rt_uint32_t flags)
{
    rt_uint32_t val = dwmac_ptp_readl(eth, PTP_TCR);

    val &= ~(PTP_TCR_TSENA | PTP_TCR_TSCFUPDT | PTP_TCR_TSCTRLSSR);
    val |= flags;
    dwmac_ptp_writel(eth, PTP_TCR, val);
}

static rt_err_t dwmac_ptp_config_sub_second_inc(struct dwmac_eth *eth,
        rt_uint32_t ptp_rate, rt_uint32_t *out_inc)
{
    rt_uint64_t inc;
    rt_uint32_t reg;

    inc = (2000000000ULL / ptp_rate);
    if (inc > PTP_SSIR_SSINC_MAX)
    {
        inc = PTP_SSIR_SSINC_MAX;
    }

    reg = (rt_uint32_t)inc << GMAC4_PTP_SSIR_SSINC_SHIFT;
    dwmac_ptp_writel(eth, PTP_SSIR, reg);

    if (out_inc)
    {
        *out_inc = (rt_uint32_t)inc;
    }

    return RT_EOK;
}

static rt_err_t dwmac_ptp_config_addend(struct dwmac_eth *eth, rt_uint32_t addend)
{
    rt_uint32_t val;

    dwmac_ptp_writel(eth, PTP_TAR, addend);

    val = dwmac_ptp_readl(eth, PTP_TCR);
    val |= PTP_TCR_TSADDREG;
    dwmac_ptp_writel(eth, PTP_TCR, val);

    return dwmac_ptp_poll_tcr(eth, PTP_TCR_TSADDREG, RT_TRUE);
}

static rt_err_t dwmac_ptp_init_systime(struct dwmac_eth *eth,
        rt_uint32_t sec, rt_uint32_t nsec)
{
    rt_uint32_t val;

    dwmac_ptp_writel(eth, PTP_STSUR, sec);
    dwmac_ptp_writel(eth, PTP_STNSUR, nsec);

    val = dwmac_ptp_readl(eth, PTP_TCR);
    val |= PTP_TCR_TSINIT;
    dwmac_ptp_writel(eth, PTP_TCR, val);

    return dwmac_ptp_poll_tcr(eth, PTP_TCR_TSINIT, RT_TRUE);
}

static rt_err_t dwmac_ptp_adjust_systime(struct dwmac_eth *eth,
        rt_uint32_t sec, rt_uint32_t nsec, rt_bool_t sub)
{
    rt_uint32_t val;

    if (sub)
    {
        sec = (rt_uint32_t)(-(rt_int32_t)sec);
        if (dwmac_ptp_readl(eth, PTP_TCR) & PTP_TCR_TSCTRLSSR)
        {
            nsec = PTP_DIGITAL_ROLLOVER_MODE - nsec;
        }
    }

    dwmac_ptp_writel(eth, PTP_STSUR, sec);
    val = (sub ? RT_BIT(PTP_STNSUR_ADDSUB_SHIFT) : 0) | nsec;
    dwmac_ptp_writel(eth, PTP_STNSUR, val);

    val = dwmac_ptp_readl(eth, PTP_TCR);
    val |= PTP_TCR_TSUPDT;
    dwmac_ptp_writel(eth, PTP_TCR, val);

    return dwmac_ptp_poll_tcr(eth, PTP_TCR_TSUPDT, RT_TRUE);
}

static void dwmac_ptp_get_systime(struct dwmac_eth *eth, rt_uint64_t *systime)
{
    rt_uint64_t ns, sec0, sec1;

    sec1 = dwmac_ptp_readl(eth, PTP_STSR);
    do
    {
        sec0 = sec1;
        ns = dwmac_ptp_readl(eth, PTP_STNSR);
        sec1 = dwmac_ptp_readl(eth, PTP_STSR);
    } while (sec0 != sec1);

    if (systime)
    {
        *systime = ns + sec1 * NSEC_PER_SEC;
    }
}

static rt_uint32_t dwmac_ptp_get_clk_rate(struct dwmac_eth *eth)
{
    rt_uint32_t rate = 0;

    if (!rt_is_err_or_null(eth->ptp_clk))
    {
        rate = (rt_uint32_t)rt_clk_get_rate(eth->ptp_clk);
    }

    if (!rate && !rt_is_err_or_null(eth->stmmac_clk))
    {
        rate = (rt_uint32_t)rt_clk_get_rate(eth->stmmac_clk);
    }

    return rate;
}

static rt_err_t dwmac_ptp_poll_acr(struct dwmac_eth *eth, rt_uint32_t mask)
{
    rt_uint32_t val;
    rt_tick_t start = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond(10);

    while (rt_tick_get() - start < timeout)
    {
        val = dwmac_ptp_readl(eth, PTP_ACR);
        if (!(val & mask))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(10);
    }

    return -RT_ETIMEOUT;
}

static void dwmac_ptp_discover_caps(struct dwmac_eth *eth)
{
    rt_uint32_t feat1, feat2;

    eth->pps_out_num = 1;
    eth->aux_snapshot_num = 1;

    feat1 = dwmac_reg_readl(eth, GMAC_HW_FEATURE1);
    feat2 = dwmac_reg_readl(eth, GMAC_HW_FEATURE2);

    if (feat1)
    {
        eth->pps_out_num = (feat1 & GMAC_HW_FEAT_PPSOUTNUM_MASK) >> 24;
        if (!eth->pps_out_num)
        {
            eth->pps_out_num = 1;
        }
    }

    if (feat2)
    {
        eth->aux_snapshot_num = (feat2 & GMAC_HW_FEAT_AUXSNAPNUM_MASK) >> 28;
        if (!eth->aux_snapshot_num)
        {
            eth->aux_snapshot_num = 1;
        }
    }
}

static rt_err_t dwmac_ptp_fixed_pps(struct dwmac_eth *eth, rt_bool_t on)
{
    rt_uint32_t val = dwmac_reg_readl(eth, MAC_PPS_CONTROL);

    if (on)
    {
        val |= PPSEN0;
    }
    else
    {
        val &= ~PPSEN0;
        val = (val & ~PPSx_MASK(0)) | PPSCMDx(0, 0x5);
    }

    dwmac_reg_writel(eth, MAC_PPS_CONTROL, val);

    return RT_EOK;
}

static rt_err_t dwmac_ptp_flex_pps(struct dwmac_eth *eth, int index,
        const struct rt_ptp_request_perout *perout, rt_bool_t on)
{
    rt_uint32_t tnsec, val;
    rt_uint64_t period;

    if (index >= eth->pps_out_num)
    {
        return -RT_EINVAL;
    }

    tnsec = dwmac_reg_readl(eth, MAC_PPSx_TARGET_TIME_NSEC(index));
    if (tnsec & TRGTBUSY0)
    {
        return -RT_EBUSY;
    }

    val = dwmac_reg_readl(eth, MAC_PPS_CONTROL);
    val &= ~PPSx_MASK(index);

    if (!on)
    {
        val |= PPSCMDx(index, 0x5);
        val |= PPSEN0;
        dwmac_reg_writel(eth, MAC_PPS_CONTROL, val);
        return RT_EOK;
    }

    val |= TRGTMODSELx(index, 0x2);
    val |= PPSEN0;
    dwmac_reg_writel(eth, MAC_PPS_CONTROL, val);

    dwmac_reg_writel(eth, MAC_PPSx_TARGET_TIME_SEC(index),
            (rt_uint32_t)perout->start_phase.sec);
    dwmac_reg_writel(eth, MAC_PPSx_TARGET_TIME_NSEC(index),
            (rt_uint32_t)perout->start_phase.nsec);

    period = (rt_uint64_t)perout->period.sec * NSEC_PER_SEC + perout->period.nsec;
    period /= eth->sub_second_inc;
    if (period <= 1)
    {
        return -RT_EINVAL;
    }

    dwmac_reg_writel(eth, MAC_PPSx_INTERVAL(index), (rt_uint32_t)(period - 1));

    period >>= 1;
    if (period <= 1)
    {
        return -RT_EINVAL;
    }

    dwmac_reg_writel(eth, MAC_PPSx_WIDTH(index), (rt_uint32_t)(period - 1));

    val = dwmac_reg_readl(eth, MAC_PPS_CONTROL);
    val |= PPSCMDx(index, 0x2);
    dwmac_reg_writel(eth, MAC_PPS_CONTROL, val);

    return RT_EOK;
}

static rt_err_t dwmac_ptp_extts(struct dwmac_eth *eth,
        const struct rt_ptp_request_extts *extts, rt_bool_t on)
{
    rt_uint32_t acr;

    if (extts->chan >= eth->aux_snapshot_num)
    {
        return -RT_EINVAL;
    }

    acr = dwmac_ptp_readl(eth, PTP_ACR);

    if (on)
    {
        acr |= PTP_ACR_ATSEN(extts->chan);
        acr |= PTP_ACR_ATSFC;
    }
    else
    {
        acr &= ~PTP_ACR_ATSEN(extts->chan);
    }

    dwmac_ptp_writel(eth, PTP_ACR, acr);

    if (on)
    {
        return dwmac_ptp_poll_acr(eth, PTP_ACR_ATSFC);
    }

    return RT_EOK;
}

rt_err_t dwmac_ptp_hw_init(struct dwmac_eth *eth)
{
    rt_uint64_t temp;
    rt_uint32_t sec_inc = 0;

    eth->ptp_clk_rate = dwmac_ptp_get_clk_rate(eth);
    if (!eth->ptp_clk_rate)
    {
        LOG_W("PTP clock rate unknown");
        return -RT_EINVAL;
    }

    dwmac_ptp_discover_caps(eth);

    eth->systime_flags = DWMAC_PTP_HWTS_ACTIVE;
    dwmac_ptp_config_hw_tstamping(eth, eth->systime_flags);

    dwmac_ptp_config_sub_second_inc(eth, eth->ptp_clk_rate, &sec_inc);
    eth->sub_second_inc = sec_inc;

    temp = NSEC_PER_SEC / sec_inc;
    temp <<= 32;
    eth->default_addend = (rt_uint32_t)(temp / eth->ptp_clk_rate);

    if (dwmac_ptp_config_addend(eth, eth->default_addend))
    {
        return -RT_ETIMEOUT;
    }

    return dwmac_ptp_init_systime(eth, 0, 0);
}

static rt_err_t dwmac_ptp_adjfreq(struct rt_ptp_clock *ptp, rt_base_t freq)
{
    rt_int64_t adj;
    rt_uint32_t addend;
    struct dwmac_eth *eth = raw_to_dwmac_ptp(ptp);

    adj = (rt_int64_t)eth->default_addend * (rt_int64_t)freq / NSEC_PER_SEC;
    addend = eth->default_addend + (rt_uint32_t)adj;

    return dwmac_ptp_config_addend(eth, addend);
}

static rt_err_t dwmac_ptp_adjtime(struct rt_ptp_clock *ptp, rt_int64_t delta)
{
    rt_uint32_t sec, nsec;
    rt_bool_t sub = RT_FALSE;
    struct dwmac_eth *eth = raw_to_dwmac_ptp(ptp);

    if (delta < 0)
    {
        sub = RT_TRUE;
        delta = -delta;
    }

    sec = (rt_uint32_t)(delta / NSEC_PER_SEC);
    nsec = (rt_uint32_t)(delta % NSEC_PER_SEC);

    return dwmac_ptp_adjust_systime(eth, sec, nsec, sub);
}

static rt_err_t dwmac_ptp_gettime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts)
{
    rt_uint64_t ns = 0;
    struct dwmac_eth *eth = raw_to_dwmac_ptp(ptp);

    dwmac_ptp_get_systime(eth, &ns);
    ts->sec = (rt_int64_t)(ns / NSEC_PER_SEC);
    ts->nsec = (rt_int32_t)(ns % NSEC_PER_SEC);

    return RT_EOK;
}

static rt_err_t dwmac_ptp_settime(struct rt_ptp_clock *ptp, const struct rt_ptp_clock_time *ts)
{
    struct dwmac_eth *eth = raw_to_dwmac_ptp(ptp);

    if (!ts || ts->nsec < 0 || ts->nsec >= NSEC_PER_SEC)
    {
        return -RT_EINVAL;
    }

    return dwmac_ptp_init_systime(eth, (rt_uint32_t)ts->sec, (rt_uint32_t)ts->nsec);
}

static rt_err_t dwmac_ptp_enable(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_request *req, rt_bool_t on)
{
    struct dwmac_eth *eth = raw_to_dwmac_ptp(ptp);

    if (!req)
    {
        return -RT_EINVAL;
    }

    switch (req->type)
    {
    case PTP_CLK_REQ_PPS:
        return dwmac_ptp_fixed_pps(eth, on);

    case PTP_CLK_REQ_EXTTS:
        return dwmac_ptp_extts(eth, &req->extts, on);

    case PTP_CLK_REQ_PEROUT:
        return dwmac_ptp_flex_pps(eth, (int)req->perout.chan, &req->perout, on);

    default:
        return -RT_ENOSYS;
    }
}

static const struct rt_ptp_ops dwmac_ptp_ops =
{
    .adjfreq = dwmac_ptp_adjfreq,
    .adjtime = dwmac_ptp_adjtime,
    .gettime = dwmac_ptp_gettime,
    .settime = dwmac_ptp_settime,
    .enable = dwmac_ptp_enable,
};

rt_err_t dwmac_ptp_register(struct dwmac_eth *eth)
{
    rt_err_t err;
    struct rt_ptp_clock *ptp = &eth->ptp_parent;

    if ((err = dwmac_ptp_hw_init(eth)))
    {
        return err;
    }

    ptp->ops = &dwmac_ptp_ops;
    ptp->max_freq = (rt_int32_t)eth->ptp_clk_rate;
    ptp->pps = 1;
    ptp->extts_nr = eth->aux_snapshot_num;
    ptp->perout_nr = eth->pps_out_num;

    if ((err = rt_ptp_clock_register(ptp)))
    {
        ptp->ops = RT_NULL;
        return err;
    }

    LOG_D("PTP clock registered, rate=%u Hz addend=0x%08x ssinc=%u pps=%u extts=%u",
            eth->ptp_clk_rate, eth->default_addend, eth->sub_second_inc,
            eth->pps_out_num, eth->aux_snapshot_num);

    return RT_EOK;
}

void dwmac_ptp_unregister(struct dwmac_eth *eth)
{
    struct rt_ptp_clock *ptp = &eth->ptp_parent;

    if (!ptp->ops)
    {
        return;
    }

    rt_ptp_clock_unregister(ptp);
    ptp->ops = RT_NULL;
}
