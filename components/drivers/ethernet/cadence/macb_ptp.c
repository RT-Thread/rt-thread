/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include "macb.h"

#define DBG_TAG "eth.macb.ptp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define NSEC_PER_SEC        1000000000L
#define GEM_PTP_MAX_FREQ    500000000
#define TSU_NSEC_MAX_VAL    ((1 << 30) - 1)

rt_inline rt_uint32_t gem_readl(struct macb_eth *eth, rt_uint32_t off)
{
    return *(volatile rt_uint32_t *)((rt_uint8_t *)eth->regs + off);
}

rt_inline void gem_writel(struct macb_eth *eth, rt_uint32_t off, rt_uint32_t val)
{
    *(volatile rt_uint32_t *)((rt_uint8_t *)eth->regs + off) = val;
}

static rt_bool_t gem_tsu_present(struct macb_eth *eth)
{
    rt_uint32_t dcfg5 = gem_readl(eth, GEM_DCFG5);

    return (dcfg5 & (1u << GEM_DCFG5_TSU_SHIFT)) ? RT_TRUE : RT_FALSE;
}

static rt_err_t macb_ptp_adjfreq(struct rt_ptp_clock *ptp, rt_base_t freq)
{
    rt_int64_t adj;
    rt_uint32_t inc;
    struct macb_eth *eth = raw_to_macb_ptp(ptp);

    /* Base increment in GEM_TI (NSINCR field) */
    inc = gem_readl(eth, GEM_TI) & 0xff;
    if (inc == 0)
    {
        inc = 1;
    }

    adj = (rt_int64_t)inc * (rt_int64_t)freq / 1000000000LL;
    if (adj > 0x7fffffff || adj < -0x80000000LL)
    {
        return -RT_EINVAL;
    }

    gem_writel(eth, GEM_TI, (inc + (rt_uint32_t)adj) & 0xff);

    return RT_EOK;
}

static rt_err_t macb_ptp_adjtime(struct rt_ptp_clock *ptp, rt_int64_t delta)
{
    rt_uint32_t adj;
    struct macb_eth *eth = raw_to_macb_ptp(ptp);

    if (delta < 0)
    {
        delta = -delta;
        adj = RT_BIT(31) | (rt_uint32_t)(delta > TSU_NSEC_MAX_VAL ? TSU_NSEC_MAX_VAL : delta);
    }
    else
    {
        adj = (rt_uint32_t)(delta > TSU_NSEC_MAX_VAL ? TSU_NSEC_MAX_VAL : delta);
    }

    gem_writel(eth, GEM_TA, adj);

    return RT_EOK;
}

static rt_err_t macb_ptp_gettime(struct rt_ptp_clock *ptp, struct rt_ptp_clock_time *ts)
{
    rt_uint32_t tsh, tsl, tn;
    struct macb_eth *eth = raw_to_macb_ptp(ptp);

    tn = gem_readl(eth, GEM_TN);
    tsl = gem_readl(eth, GEM_TSL);
    tsh = gem_readl(eth, GEM_TSH) & 0xffffU;

    ts->sec = ((rt_int64_t)tsh << 32) | tsl;
    ts->nsec = (rt_int32_t)(tn & 0x3fffffffU);

    return RT_EOK;
}

static rt_err_t macb_ptp_settime(struct rt_ptp_clock *ptp, const struct rt_ptp_clock_time *ts)
{
    struct macb_eth *eth = raw_to_macb_ptp(ptp);

    if (!ts || ts->nsec < 0 || ts->nsec >= NSEC_PER_SEC)
    {
        return -RT_EINVAL;
    }

    /* TN clear, TSH, TSL, then TN */
    gem_writel(eth, GEM_TN, 0);
    gem_writel(eth, GEM_TSH, (rt_uint32_t)((rt_uint64_t)ts->sec >> 32) & 0xffffU);
    gem_writel(eth, GEM_TSL, (rt_uint32_t)ts->sec);
    gem_writel(eth, GEM_TN, (rt_uint32_t)ts->nsec);

    return RT_EOK;
}

static rt_err_t macb_ptp_enable(struct rt_ptp_clock *ptp, struct rt_ptp_clock_request *req, rt_bool_t on)
{
    return RT_EOK;
}

static const struct rt_ptp_ops macb_gem_ptp_ops =
{
    .adjfreq = macb_ptp_adjfreq,
    .adjtime = macb_ptp_adjtime,
    .gettime = macb_ptp_gettime,
    .settime = macb_ptp_settime,
    .enable = macb_ptp_enable,
};

rt_err_t macb_ptp_register(struct macb_eth *eth)
{
    rt_err_t err;
    struct rt_ptp_clock *ptp = &eth->ptp_parent;

    if (!gem_tsu_present(eth))
    {
        return -RT_ENOSYS;
    }

    ptp->ops = &macb_gem_ptp_ops;
    ptp->max_freq = GEM_PTP_MAX_FREQ;

    if ((err = rt_ptp_clock_register(ptp)))
    {
        ptp->ops = RT_NULL;
        return err;
    }

    return RT_EOK;
}

void macb_ptp_unregister(struct macb_eth *eth)
{
    struct rt_ptp_clock *ptp = &eth->ptp_parent;

    if (!ptp->ops)
    {
        return;
    }

    rt_ptp_clock_unregister(ptp);
    ptp->ops = RT_NULL;
}
