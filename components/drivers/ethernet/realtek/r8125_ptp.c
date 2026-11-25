/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "r8125.h"

#define DBG_TAG "eth.r8125.ptp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define NSEC_PER_SEC                    1000000000LL
#define R8125_PTP_MAC_MAX_FREQ          119304647
#define R8125_PTP_PHY_MAX_FREQ          488281

#define R8125_PTP_SEC_MASK              0x0000ffffffffffffULL
#define R8125_PTP_NSEC_MASK             0x3fffffffU

#define R8125_PHY_PTP_CTL               0xE400
#define R8125_PHY_PTP_INER              0xE402
#define R8125_PHY_PTP_INSR              0xE404
#define R8125_PHY_PTP_SYNCE_CTL         0xE406
#define R8125_PHY_PTP_GEN_CFG           0xE408
#define R8125_PHY_PTP_CLK_CFG           0xE410
#define R8125_PHY_PTP_NS_LO             0xE412
#define R8125_PHY_PTP_NS_HI             0xE414
#define R8125_PHY_PTP_SEC_LO            0xE416
#define R8125_PHY_PTP_SEC_MI            0xE418
#define R8125_PHY_PTP_SEC_HI            0xE41A
#define R8125_PHY_PTP_TAI_CFG           0xE420
#define R8125_PHY_PTP_TAI_SEC_LO        0xE42A
#define R8125_PHY_PTP_TAI_SEC_HI        0xE42C

#define R8125_PHY_PTP_CLK_MODE_SET      RT_BIT(0)
#define R8125_PHY_PTP_DIRECT_READ       4
#define R8125_PHY_PTP_DIRECT_WRITE      6
#define R8125_PHY_PTP_INCREMENT_STEP    8
#define R8125_PHY_PTP_DECREMENT_STEP    10
#define R8125_PHY_PTP_RATE_WRITE        14

static rt_err_t r8125_ptp_validate_time(const struct rt_ptp_clock_time *ts)
{
    if (!ts || ts->sec < 0 || ts->sec > (rt_int64_t)R8125_PTP_SEC_MASK ||
        ts->nsec < 0 || ts->nsec >= NSEC_PER_SEC)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static void r8125_ptp_delta_to_time(rt_int64_t delta, rt_bool_t *neg,
        struct rt_ptp_clock_time *ts)
{
    rt_uint64_t ns;

    if (delta < 0)
    {
        *neg = RT_TRUE;
        ns = (rt_uint64_t)(-(delta + 1)) + 1;
    }
    else
    {
        *neg = RT_FALSE;
        ns = (rt_uint64_t)delta;
    }

    ts->sec = (rt_int64_t)(ns / (rt_uint64_t)NSEC_PER_SEC);
    ts->nsec = (rt_int32_t)(ns % (rt_uint64_t)NSEC_PER_SEC);
}

static rt_err_t r8125_ptp_phy_wait_clk(struct r8125_eth *eth)
{
    for (int i = 0; i < 1000; ++i)
    {
        if (!(r8125_phy_ocp_read(eth, R8125_PHY_PTP_CLK_CFG) &
              R8125_PHY_PTP_CLK_MODE_SET))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(10);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t r8125_ptp_phy_clk_mode(struct r8125_eth *eth, rt_uint16_t mode)
{
    r8125_phy_ocp_update_bits(eth, R8125_PHY_PTP_CLK_CFG,
                              RT_BIT(3) | RT_BIT(2) | RT_BIT(1),
                              R8125_PHY_PTP_CLK_MODE_SET | mode);

    return r8125_ptp_phy_wait_clk(eth);
}

static void r8125_ptp_mac_enable(struct r8125_eth *eth, rt_bool_t enable)
{
    RTL_W16(eth, R8125_PTP_CTRL, 0);
    if (enable)
    {
        rt_uint16_t ctrl;

        RTL_W8(eth, R8125_PTP_ISR, 0xff);
        r8125_mac_ocp_write(eth, 0xDC00, r8125_mac_ocp_read(eth, 0xDC00) | RT_BIT(6));

        ctrl = RT_BIT(0) | RT_BIT(3) | RT_BIT(4) | RT_BIT(6) |
               RT_BIT(10) | RT_BIT(12);
        RTL_W16(eth, R8125_PTP_CTRL, ctrl);
    }
}

static void r8125_ptp_phy_enable(struct r8125_eth *eth, rt_bool_t enable)
{
    if (enable)
    {
        r8125_phy_ocp_set_bits(eth, R8125_PHY_PTP_INER, RT_BIT(2) | RT_BIT(3));
        r8125_phy_ocp_set_bits(eth, R8125_PHY_PTP_GEN_CFG, RT_BIT(0));
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_INSR, 0xffff);
        r8125_phy_ocp_clear_bits(eth, R8125_PHY_PTP_SYNCE_CTL, RT_BIT(0));
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_CTL,
                            RT_BIT(0) | RT_BIT(1) | RT_BIT(2) | RT_BIT(3) |
                            RT_BIT(4) | RT_BIT(5) | RT_BIT(6) | RT_BIT(7) |
                            RT_BIT(12));
        r8125_phy_ocp_set_bits(eth, 0xA640, RT_BIT(15));
    }
    else
    {
        r8125_phy_ocp_clear_bits(eth, R8125_PHY_PTP_INER, RT_BIT(2) | RT_BIT(3));
        r8125_phy_ocp_clear_bits(eth, R8125_PHY_PTP_SYNCE_CTL, RT_BIT(0));
        r8125_phy_ocp_clear_bits(eth, R8125_PHY_PTP_CTL, RT_BIT(0));
        r8125_phy_ocp_set_bits(eth, 0xA640, RT_BIT(15));
    }
}

static rt_err_t r8125_ptp_mac_gettime_locked(struct r8125_eth *eth,
        struct rt_ptp_clock_time *ts)
{
    RTL_W16(eth, R8125_PTP_TIME_CMD,
            R8125_PTP_CMD_LATCH_TIME | R8125_PTP_EXEC_CMD);

    ts->nsec = (rt_int32_t)(RTL_R32(eth, R8125_PTP_SOFT_NS) &
                            R8125_PTP_NSEC_MASK);
    ts->sec = RTL_R16(eth, R8125_PTP_SOFT_SEC + 4);
    ts->sec <<= 32;
    ts->sec |= RTL_R32(eth, R8125_PTP_SOFT_SEC);

    return RT_EOK;
}

static rt_err_t r8125_ptp_mac_settime_locked(struct r8125_eth *eth,
        const struct rt_ptp_clock_time *ts)
{
    RTL_W32(eth, R8125_PTP_SOFT_NS, (rt_uint32_t)ts->nsec & R8125_PTP_NSEC_MASK);
    RTL_W32(eth, R8125_PTP_SOFT_SEC, (rt_uint32_t)ts->sec);
    RTL_W16(eth, R8125_PTP_SOFT_SEC + 4, (rt_uint16_t)((rt_uint64_t)ts->sec >> 32));
    RTL_W16(eth, R8125_PTP_TIME_CMD,
            R8125_PTP_CMD_SET_TIME | R8125_PTP_EXEC_CMD);

    return RT_EOK;
}

static rt_err_t r8125_ptp_mac_adjtime_locked(struct r8125_eth *eth,
        rt_int64_t delta)
{
    rt_uint64_t sec;
    rt_uint32_t nsec;
    rt_bool_t neg = RT_FALSE;
    struct rt_ptp_clock_time ts;

    r8125_ptp_delta_to_time(delta, &neg, &ts);
    sec = (rt_uint64_t)ts.sec;
    nsec = (rt_uint32_t)ts.nsec;

    if (neg)
    {
        sec = (rt_uint64_t)(-(rt_int64_t)sec);
        nsec = (rt_uint32_t)(-(rt_int32_t)nsec);
        nsec |= R8125_PTP_NS_NEGATIVE;
    }

    sec &= R8125_PTP_SEC_MASK;
    nsec &= (R8125_PTP_NSEC_MASK | R8125_PTP_NS_NEGATIVE);

    RTL_W32(eth, R8125_PTP_SOFT_NS, nsec);
    RTL_W32(eth, R8125_PTP_SOFT_SEC, (rt_uint32_t)sec);
    RTL_W16(eth, R8125_PTP_SOFT_SEC + 4, (rt_uint16_t)(sec >> 32));
    RTL_W16(eth, R8125_PTP_TIME_CMD,
            R8125_PTP_CMD_SET_TIME | R8125_PTP_EXEC_CMD);

    return RT_EOK;
}

static rt_err_t r8125_ptp_phy_gettime_locked(struct r8125_eth *eth,
        struct rt_ptp_clock_time *ts)
{
    rt_err_t err;
    rt_uint64_t sec;
    rt_uint32_t nsec;

    err = r8125_ptp_phy_clk_mode(eth, R8125_PHY_PTP_DIRECT_READ);
    if (err)
    {
        return err;
    }

    nsec = r8125_phy_ocp_read(eth, R8125_PHY_PTP_NS_HI) & 0x3fff;
    nsec <<= 16;
    nsec |= r8125_phy_ocp_read(eth, R8125_PHY_PTP_NS_LO);

    sec = r8125_phy_ocp_read(eth, R8125_PHY_PTP_SEC_HI);
    sec <<= 16;
    sec |= r8125_phy_ocp_read(eth, R8125_PHY_PTP_SEC_MI);
    sec <<= 16;
    sec |= r8125_phy_ocp_read(eth, R8125_PHY_PTP_SEC_LO);

    ts->sec = (rt_int64_t)sec;
    ts->nsec = (rt_int32_t)nsec;

    return RT_EOK;
}

static rt_err_t r8125_ptp_phy_settime_locked(struct r8125_eth *eth,
        const struct rt_ptp_clock_time *ts)
{
    r8125_phy_ocp_write(eth, R8125_PHY_PTP_NS_LO, (rt_uint16_t)ts->nsec);
    r8125_phy_ocp_write(eth, R8125_PHY_PTP_NS_HI,
                        (rt_uint16_t)(((rt_uint32_t)ts->nsec >> 16) & 0x3fff));

    r8125_phy_ocp_write(eth, R8125_PHY_PTP_SEC_LO, (rt_uint16_t)ts->sec);
    r8125_phy_ocp_write(eth, R8125_PHY_PTP_SEC_MI, (rt_uint16_t)((rt_uint64_t)ts->sec >> 16));
    r8125_phy_ocp_write(eth, R8125_PHY_PTP_SEC_HI, (rt_uint16_t)((rt_uint64_t)ts->sec >> 32));

    return r8125_ptp_phy_clk_mode(eth, R8125_PHY_PTP_DIRECT_WRITE);
}

static rt_err_t r8125_ptp_gettime(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_time *ts)
{
    rt_err_t err;
    struct r8125_eth *eth = raw_to_r8125_ptp(ptp);

    if (!ts)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&eth->ptp_lock, RT_WAITING_FOREVER);
    if (eth->ptp_ver == R8125_PTP_PHY)
    {
        err = r8125_ptp_phy_gettime_locked(eth, ts);
    }
    else
    {
        err = r8125_ptp_mac_gettime_locked(eth, ts);
    }
    rt_mutex_release(&eth->ptp_lock);

    return err;
}

static rt_err_t r8125_ptp_settime(struct rt_ptp_clock *ptp,
        const struct rt_ptp_clock_time *ts)
{
    rt_err_t err;
    struct r8125_eth *eth = raw_to_r8125_ptp(ptp);

    if ((err = r8125_ptp_validate_time(ts)))
    {
        return err;
    }

    rt_mutex_take(&eth->ptp_lock, RT_WAITING_FOREVER);
    if (eth->ptp_ver == R8125_PTP_PHY)
    {
        err = r8125_ptp_phy_settime_locked(eth, ts);
    }
    else
    {
        err = r8125_ptp_mac_settime_locked(eth, ts);
    }
    rt_mutex_release(&eth->ptp_lock);

    return err;
}

static rt_err_t r8125_ptp_adjtime(struct rt_ptp_clock *ptp, rt_int64_t delta)
{
    rt_err_t err;
    struct rt_ptp_clock_time ts;
    struct r8125_eth *eth = raw_to_r8125_ptp(ptp);

    rt_mutex_take(&eth->ptp_lock, RT_WAITING_FOREVER);
    if (eth->ptp_ver == R8125_PTP_PHY)
    {
        rt_bool_t neg;
        rt_uint64_t sec;
        rt_uint32_t nsec;

        r8125_ptp_delta_to_time(delta, &neg, &ts);
        sec = (rt_uint64_t)ts.sec & R8125_PTP_SEC_MASK;
        nsec = (rt_uint32_t)ts.nsec & R8125_PTP_NSEC_MASK;
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_NS_LO, (rt_uint16_t)nsec);
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_NS_HI, (rt_uint16_t)(nsec >> 16));
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_SEC_LO, (rt_uint16_t)sec);
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_SEC_MI, (rt_uint16_t)(sec >> 16));
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_SEC_HI, (rt_uint16_t)(sec >> 32));
        err = r8125_ptp_phy_clk_mode(eth, neg ?
                                     R8125_PHY_PTP_DECREMENT_STEP :
                                     R8125_PHY_PTP_INCREMENT_STEP);
    }
    else
    {
        err = r8125_ptp_mac_adjtime_locked(eth, delta);
    }
    rt_mutex_release(&eth->ptp_lock);

    return err;
}

static rt_err_t r8125_ptp_adjfreq(struct rt_ptp_clock *ptp, rt_base_t freq)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t val;
    rt_bool_t neg = RT_FALSE;
    struct r8125_eth *eth = raw_to_r8125_ptp(ptp);

    if (freq < -ptp->max_freq || freq > ptp->max_freq)
    {
        return -RT_EINVAL;
    }

    if (freq < 0)
    {
        neg = RT_TRUE;
        freq = -freq;
    }

    rt_mutex_take(&eth->ptp_lock, RT_WAITING_FOREVER);
    if (eth->ptp_ver == R8125_PTP_PHY)
    {
        val = (rt_uint32_t)(((rt_uint64_t)freq << 32) / NSEC_PER_SEC);
        if (neg)
        {
            val = ~val + 1;
        }

        r8125_phy_ocp_write(eth, R8125_PHY_PTP_NS_LO, (rt_uint16_t)val);
        r8125_phy_ocp_write(eth, R8125_PHY_PTP_NS_HI,
                            (rt_uint16_t)((val & 0x003f0000) >> 16));
        err = r8125_ptp_phy_clk_mode(eth, R8125_PHY_PTP_RATE_WRITE);
    }
    else
    {
        val = (rt_uint32_t)freq * 9U;
        if (neg)
        {
            val = (rt_uint32_t)(-((rt_int32_t)val));
            val &= R8125_PTP_NSEC_MASK;
            val |= R8125_PTP_NS_NEGATIVE;
        }
        else
        {
            val &= R8125_PTP_NSEC_MASK;
        }

        RTL_W32(eth, R8125_PTP_SOFT_NS, val);
        RTL_W16(eth, R8125_PTP_TIME_CMD,
                R8125_PTP_CMD_ADJ_TIME | R8125_PTP_EXEC_CMD);
    }
    rt_mutex_release(&eth->ptp_lock);

    return err;
}

static rt_err_t r8125_ptp_enable(struct rt_ptp_clock *ptp,
        struct rt_ptp_clock_request *request, rt_bool_t on)
{
    rt_uint16_t val;
    struct r8125_eth *eth = raw_to_r8125_ptp(ptp);

    if (!request || request->type != PTP_CLK_REQ_PPS)
    {
        return -RT_ENOSYS;
    }

    rt_mutex_take(&eth->ptp_lock, RT_WAITING_FOREVER);
    if (eth->ptp_ver == R8125_PTP_MAC)
    {
        val = RTL_R16(eth, R8125_PTP_CTRL);
        val &= ~RT_BIT(15);
        if (on)
        {
            val |= RT_BIT(14);
        }
        else
        {
            val &= ~RT_BIT(14);
        }
        RTL_W16(eth, R8125_PTP_CTRL, val);
    }
    else if (eth->ptp_ver == R8125_PTP_PHY)
    {
        if (on)
        {
            struct rt_ptp_clock_time ts;
            rt_uint64_t next_sec;

            r8125_mac_ocp_write(eth, 0xDC00, r8125_mac_ocp_read(eth, 0xDC00) & ~RT_BIT(6));
            r8125_mac_ocp_write(eth, 0xDC60, r8125_mac_ocp_read(eth, 0xDC60) | RT_BIT(6));

            val = r8125_phy_ocp_read(eth, 0xE432);
            val &= 0xFE00;
            val |= 0x017d;
            r8125_phy_ocp_write(eth, 0xE432, val);
            r8125_phy_ocp_write(eth, 0xE434, 0x7840);

            val = r8125_phy_ocp_read(eth, 0xE436);
            val &= 0xFE00;
            val |= 0x00be;
            r8125_phy_ocp_write(eth, 0xE436, val);
            r8125_phy_ocp_write(eth, 0xE438, 0xbc20);

            if (!r8125_ptp_phy_gettime_locked(eth, &ts))
            {
                next_sec = (rt_uint64_t)ts.sec + 1;
                r8125_phy_ocp_write(eth, R8125_PHY_PTP_TAI_SEC_LO,
                                    (rt_uint16_t)next_sec);
                r8125_phy_ocp_write(eth, R8125_PHY_PTP_TAI_SEC_HI,
                                    (rt_uint16_t)(next_sec >> 16));
                r8125_phy_ocp_write(eth, R8125_PHY_PTP_TAI_CFG,
                                    RT_BIT(8) | RT_BIT(5) | RT_BIT(1) | RT_BIT(0));
            }
        }
        else
        {
            r8125_phy_ocp_write(eth, R8125_PHY_PTP_TAI_CFG, 0);
        }
    }
    rt_mutex_release(&eth->ptp_lock);

    return RT_EOK;
}

static const struct rt_ptp_ops r8125_ptp_ops =
{
    .adjfreq = r8125_ptp_adjfreq,
    .adjtime = r8125_ptp_adjtime,
    .gettime = r8125_ptp_gettime,
    .settime = r8125_ptp_settime,
    .enable = r8125_ptp_enable,
};

void rtl8125_ptp_reset(struct r8125_eth *eth)
{
    if (!eth || !eth->ptp_ver)
    {
        return;
    }

    rt_mutex_take(&eth->ptp_lock, RT_WAITING_FOREVER);
    if (eth->ptp_ver == R8125_PTP_PHY)
    {
        r8125_ptp_phy_enable(eth, RT_FALSE);
    }
    else
    {
        r8125_ptp_mac_enable(eth, RT_FALSE);
    }
    rt_mutex_release(&eth->ptp_lock);
}

void rtl8125_ptp_suspend(struct r8125_eth *eth)
{
    rtl8125_ptp_reset(eth);
}

rt_err_t rtl8125_ptp_register(struct r8125_eth *eth)
{
    rt_err_t err;
    struct rt_ptp_clock *ptp;

    if (!eth || eth->ptp_ver == R8125_PTP_NONE)
    {
        return -RT_ENOSYS;
    }

    ptp = &eth->ptp_parent;
    ptp->ops = &r8125_ptp_ops;
    ptp->max_freq = (eth->ptp_ver == R8125_PTP_PHY) ?
                    R8125_PTP_PHY_MAX_FREQ : R8125_PTP_MAC_MAX_FREQ;
    ptp->pps = 1;

    if (eth->ptp_ver == R8125_PTP_PHY)
    {
        r8125_ptp_phy_enable(eth, RT_TRUE);
    }
    else
    {
        r8125_ptp_mac_enable(eth, RT_TRUE);
    }

    err = rt_ptp_clock_register(ptp);
    if (err)
    {
        rtl8125_ptp_reset(eth);
        ptp->ops = RT_NULL;
        return err;
    }

    eth->ptp_registered = RT_TRUE;
    LOG_D("Registered %s PTP hardware clock", eth->ptp_ver == R8125_PTP_PHY ? "PHY" : "MAC");

    return RT_EOK;
}

void rtl8125_ptp_unregister(struct r8125_eth *eth)
{
    if (!eth || !eth->ptp_registered)
    {
        return;
    }

    rtl8125_ptp_reset(eth);
    rt_ptp_clock_unregister(&eth->ptp_parent);
    eth->ptp_parent.ops = RT_NULL;
    eth->ptp_registered = RT_FALSE;
}
