/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rng.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rockchip.h"

#define ROCKCHIP_AUTOSUSPEND_DELAY      100
#define ROCKCHIP_POLL_PERIOD_US         100
#define ROCKCHIP_POLL_TIMEOUT_US        50000
#define RK_MAX_RNG_BYTE                 (32)

/* start of CRYPTO V1 register define */
#define CRYPTO_V1_CTRL                  0x0008
#define CRYPTO_V1_RNG_START             RT_BIT(8)
#define CRYPTO_V1_RNG_FLUSH             RT_BIT(9)

#define CRYPTO_V1_TRNG_CTRL             0x0200
#define CRYPTO_V1_OSC_ENABLE            RT_BIT(16)
#define CRYPTO_V1_TRNG_SAMPLE_PERIOD(x) (x)

#define CRYPTO_V1_TRNG_DOUT_0           0x0204
/* end of CRYPTO V1 register define */

/* start of CRYPTO V2 register define */
#define CRYPTO_V2_RNG_DEFAULT_OFFSET    0x0400
#define CRYPTO_V2_RNG_CTL               0x0
#define CRYPTO_V2_RNG_64_BIT_LEN        ((0x00) << (4))
#define CRYPTO_V2_RNG_128_BIT_LEN       ((0x01) << (4))
#define CRYPTO_V2_RNG_192_BIT_LEN       ((0x02) << (4))
#define CRYPTO_V2_RNG_256_BIT_LEN       ((0x03) << (4))
#define CRYPTO_V2_RNG_FATESY_SOC_RING   ((0x00) << (2))
#define CRYPTO_V2_RNG_SLOWER_SOC_RING_0 ((0x01) << (2))
#define CRYPTO_V2_RNG_SLOWER_SOC_RING_1 ((0x02) << (2))
#define CRYPTO_V2_RNG_SLOWEST_SOC_RING  ((0x03) << (2))
#define CRYPTO_V2_RNG_ENABLE            RT_BIT(1)
#define CRYPTO_V2_RNG_START             RT_BIT(0)
#define CRYPTO_V2_RNG_SAMPLE_CNT        0x0004
#define CRYPTO_V2_RNG_DOUT_0            0x0010
/* end of CRYPTO V2 register define */

/* start of TRNG_V1 register define */
/* TRNG is no longer subordinate to the Crypto module */
#define TRNG_V1_CTRL                    0x0000
#define TRNG_V1_CTRL_NOP                ((0x00) << (0))
#define TRNG_V1_CTRL_RAND               ((0x01) << (0))
#define TRNG_V1_CTRL_SEED               ((0x02) << (0))

#define TRNG_V1_STAT                    0x0004
#define TRNG_V1_STAT_SEEDED             RT_BIT(9)
#define TRNG_V1_STAT_GENERATING         RT_BIT(30)
#define TRNG_V1_STAT_RESEEDING          RT_BIT(31)

#define TRNG_V1_MODE                    0x0008
#define TRNG_V1_MODE_128_BIT            ((0x00) << (3))
#define TRNG_V1_MODE_256_BIT            ((0x01) << (3))

#define TRNG_V1_IE                      0x0010
#define TRNG_V1_IE_GLBL_EN              RT_BIT(31)
#define TRNG_V1_IE_SEED_DONE_EN         RT_BIT(1)
#define TRNG_V1_IE_RAND_RDY_EN          RT_BIT(0)

#define TRNG_V1_ISTAT                   0x0014
#define TRNG_V1_ISTAT_RAND_RDY          RT_BIT(0)

/* RAND0 ~ RAND7 */
#define TRNG_V1_RAND0                   0x0020
#define TRNG_V1_RAND7                   0x003C

#define TRNG_V1_AUTO_RQSTS              0x0060

#define TRNG_V1_VERSION                 0x00F0
#define TRNG_v1_VERSION_CODE            0x46bc
/* end of TRNG_V1 register define */

struct rockchip_rng;

struct rockchip_rng_soc_data
{
    rt_uint32_t default_offset;

    rt_err_t (*init)(struct rockchip_rng *rk_rng);
    rt_uint32_t (*read)(struct rockchip_rng *rk_rng, void *buf, rt_size_t max, rt_bool_t wait);
};

struct rockchip_rng
{
    struct rt_hwcrypto_device parent;

    void *regs;

    struct rt_clk_array *clk_arr;
    struct rt_reset_control *rstc;

    const struct rockchip_rng_soc_data *soc_data;
};

#define raw_to_rockchip_rng(raw) rt_container_of(raw, struct rockchip_rng, parent)

static void rockchip_rng_writel(struct rockchip_rng *rk_rng, rt_uint32_t val, int offset)
{
    HWREG32(rk_rng->regs + offset) = val;
}

static rt_uint32_t rockchip_rng_readl(struct rockchip_rng *rk_rng, int offset)
{
    return HWREG32(rk_rng->regs + offset);
}

static void rockchip_rng_read_regs(struct rockchip_rng *rk_rng, rt_uint32_t offset,
        void *buf, rt_size_t size)
{
    rt_uint32_t *data = buf;

    for (int i = 0; i < size; i += 4, ++offset)
    {
        data[i] = rt_be32_to_cpu(rockchip_rng_readl(rk_rng, offset));
    }
}

static rt_uint32_t rockchip_crypto_v1_read(struct rockchip_rng *rk_rng, void *buf,
        rt_size_t max, rt_bool_t wait)
{
    rt_tick_t start;
    rt_uint32_t res = 0, reg_ctrl = 0;
    int timeout = rt_tick_from_millisecond(ROCKCHIP_POLL_TIMEOUT_US / 1000);

    /* enable osc_ring to get entropy, sample period is set as 100 */
    reg_ctrl = CRYPTO_V1_OSC_ENABLE | CRYPTO_V1_TRNG_SAMPLE_PERIOD(100);
    rockchip_rng_writel(rk_rng, reg_ctrl, CRYPTO_V1_TRNG_CTRL);

    reg_ctrl = HIWORD_UPDATE(CRYPTO_V1_RNG_START, CRYPTO_V1_RNG_START, 0);

    rockchip_rng_writel(rk_rng, reg_ctrl, CRYPTO_V1_CTRL);

    start = rt_tick_get();

    while (rockchip_rng_readl(rk_rng, CRYPTO_V1_CTRL) & CRYPTO_V1_RNG_START)
    {
        rt_hw_us_delay(ROCKCHIP_POLL_PERIOD_US);

        if ((rt_tick_get() - start) > timeout)
        {
            goto _time_out;
        }

        rt_hw_cpu_relax();
    }

    res = rt_min_t(rt_size_t, max, RK_MAX_RNG_BYTE);

    rockchip_rng_read_regs(rk_rng, CRYPTO_V1_TRNG_DOUT_0, buf, res);

_time_out:
    /* close TRNG */
    rockchip_rng_writel(rk_rng, HIWORD_UPDATE(0, CRYPTO_V1_RNG_START, 0), CRYPTO_V1_CTRL);

    return res;
}

static rt_uint32_t rockchip_crypto_v2_read(struct rockchip_rng *rk_rng, void *buf,
        rt_size_t max, rt_bool_t wait)
{
    rt_tick_t start;
    rt_uint32_t res = 0, reg_ctrl = 0;
    int timeout = rt_tick_from_millisecond(ROCKCHIP_POLL_TIMEOUT_US / 1000);

    /* enable osc_ring to get entropy, sample period is set as 100 */
    rockchip_rng_writel(rk_rng, 100, CRYPTO_V2_RNG_SAMPLE_CNT);

    reg_ctrl |= CRYPTO_V2_RNG_256_BIT_LEN;
    reg_ctrl |= CRYPTO_V2_RNG_SLOWER_SOC_RING_0;
    reg_ctrl |= CRYPTO_V2_RNG_ENABLE;
    reg_ctrl |= CRYPTO_V2_RNG_START;

    rockchip_rng_writel(rk_rng, HIWORD_UPDATE(reg_ctrl, 0xffff, 0), CRYPTO_V2_RNG_CTL);

    start = rt_tick_get();

    while (rockchip_rng_readl(rk_rng, CRYPTO_V2_RNG_CTL) & CRYPTO_V2_RNG_START)
    {
        rt_hw_us_delay(ROCKCHIP_POLL_PERIOD_US);

        if ((rt_tick_get() - start) > timeout)
        {
            goto _time_out;
        }

        rt_hw_cpu_relax();
    }

    res = rt_min_t(rt_size_t, max, RK_MAX_RNG_BYTE);

    rockchip_rng_read_regs(rk_rng, CRYPTO_V2_RNG_DOUT_0, buf, res);

_time_out:
    /* close TRNG */
    rockchip_rng_writel(rk_rng, HIWORD_UPDATE(0, 0xffff, 0), CRYPTO_V2_RNG_CTL);

    return res;
}

static rt_err_t rockchip_trng_v1_init(struct rockchip_rng *rk_rng)
{
    rt_uint32_t auto_reseed_cnt = 1000;
    rt_uint32_t reg_ctrl, status, version;

    version = rockchip_rng_readl(rk_rng, TRNG_V1_VERSION);

    if (version != TRNG_v1_VERSION_CODE)
    {
        LOG_E("Wrong trng version, expected = %08x, actual = %08x",
                TRNG_V1_VERSION, version);

        return -RT_EIO;
    }

    status = rockchip_rng_readl(rk_rng, TRNG_V1_STAT);

    /* TRNG should wait RAND_RDY triggered if it is busy or not seeded */
    if (!(status & TRNG_V1_STAT_SEEDED) || (status & TRNG_V1_STAT_GENERATING) ||
        (status & TRNG_V1_STAT_RESEEDING))
    {
        rt_tick_t start;
        rt_uint32_t mask = TRNG_V1_STAT_SEEDED | TRNG_V1_STAT_GENERATING |
                TRNG_V1_STAT_RESEEDING;
        int timeout = rt_tick_from_millisecond(ROCKCHIP_POLL_TIMEOUT_US / 1000);

        rt_hw_us_delay(10);

        /* wait for GENERATING and RESEEDING flag to clear */
        start = rt_tick_get();

        while ((rockchip_rng_readl(rk_rng, TRNG_V1_STAT) & mask) != TRNG_V1_STAT_SEEDED)
        {
            rt_hw_us_delay(ROCKCHIP_POLL_PERIOD_US);

            if ((rt_tick_get() - start) > timeout)
            {
                break;
            }

            rt_hw_cpu_relax();
        }
    }

    /* clear ISTAT flag because trng may auto reseeding when power on */
    reg_ctrl = rockchip_rng_readl(rk_rng, TRNG_V1_ISTAT);
    rockchip_rng_writel(rk_rng, reg_ctrl, TRNG_V1_ISTAT);

    /* auto reseed after (auto_reseed_cnt * 16) byte rand generate */
    rockchip_rng_writel(rk_rng, auto_reseed_cnt, TRNG_V1_AUTO_RQSTS);

    return RT_EOK;
}

static rt_uint32_t rockchip_trng_v1_read(struct rockchip_rng *rk_rng, void *buf,
        rt_size_t max, rt_bool_t wait)
{
    rt_uint32_t res = 0, reg_ctrl = 0;

    /* clear ISTAT anyway */
    reg_ctrl = rockchip_rng_readl(rk_rng, TRNG_V1_ISTAT);
    rockchip_rng_writel(rk_rng, reg_ctrl, TRNG_V1_ISTAT);

    /* generate 256bit random */
    rockchip_rng_writel(rk_rng, TRNG_V1_MODE_256_BIT, TRNG_V1_MODE);
    rockchip_rng_writel(rk_rng, TRNG_V1_CTRL_RAND, TRNG_V1_CTRL);

    /*
     * Generate2 56 bit random data will cost 1024 clock cycles.
     * Estimated at 150M RNG module frequency, it takes 6.7 microseconds.
     */
    rt_hw_us_delay(10);
    reg_ctrl = rockchip_rng_readl(rk_rng, TRNG_V1_ISTAT);

    if (!(reg_ctrl & TRNG_V1_ISTAT_RAND_RDY))
    {
        rt_tick_t start = rt_tick_get();
        int timeout = rt_tick_from_millisecond(ROCKCHIP_POLL_TIMEOUT_US / 1000);

        /* wait RAND_RDY triggered */
        while (!(rockchip_rng_readl(rk_rng, TRNG_V1_ISTAT) & TRNG_V1_ISTAT_RAND_RDY))
        {
            rt_hw_us_delay(ROCKCHIP_POLL_PERIOD_US);

            if ((rt_tick_get() - start) > timeout)
            {
                goto _time_out;
            }

            rt_hw_cpu_relax();
        }
    }

    res = rt_min_t(rt_size_t, max, RK_MAX_RNG_BYTE);

    rockchip_rng_read_regs(rk_rng, TRNG_V1_RAND0, buf, res);

    /* clear all status flag */
    rockchip_rng_writel(rk_rng, reg_ctrl, TRNG_V1_ISTAT);
_time_out:
    /* close TRNG */
    rockchip_rng_writel(rk_rng, TRNG_V1_CTRL_NOP, TRNG_V1_CTRL);

    return res;
}

static rt_uint32_t rockchip_rng_read(struct rockchip_rng *rk_rng, void *buf,
        rt_size_t max, rt_bool_t wait)
{
    rt_uint32_t res;
    int read_len = 0;

    if (!rk_rng->soc_data->read)
    {
        return 0;
    }

    res = 0;

    while (max > res)
    {
        read_len = rk_rng->soc_data->read(rk_rng, buf + res, max - res, wait);

        if (read_len < 0)
        {
            res = read_len;

            break;
        }
        res += read_len;
    }

    return res;
}

static rt_uint32_t rockchip_rng_rand(struct hwcrypto_rng *ctx)
{
    rt_uint32_t rand;
    struct rockchip_rng *rk_rng = raw_to_rockchip_rng(ctx->parent.device);

    if (rockchip_rng_read(rk_rng, &rand, sizeof(rand), RT_TRUE) != sizeof(rand))
    {
        return 0;
    }

    return rand;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = rockchip_rng_rand,
};

static rt_err_t rockchip_rng_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;
    struct hwcrypto_rng *rng;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_RNG:
        ctx->contex = RT_NULL;

        rng = rt_container_of(ctx, struct hwcrypto_rng, parent);
        rng->ops = &rng_ops;
        break;

    default:
        res = -RT_ENOSYS;
        break;
    }

    return res;
}

static void rockchip_rng_destroy(struct rt_hwcrypto_ctx *ctx)
{
    rt_free(ctx->contex);
}

static rt_err_t rockchip_rng_copy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t err = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_RNG:
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

static void rockchip_rng_reset(struct rt_hwcrypto_ctx *ctx)
{
}

static const struct rt_hwcrypto_ops rockchip_rng_ops =
{
    .create = rockchip_rng_create,
    .destroy = rockchip_rng_destroy,
    .copy = rockchip_rng_copy,
    .reset = rockchip_rng_reset,
};

static void rockchip_rng_free(struct rockchip_rng *rk_rng)
{
    if (!rk_rng->regs)
    {
        rt_iounmap(rk_rng->regs);
    }

    if (!rt_is_err_or_null(rk_rng->rstc))
    {
        rt_reset_control_assert(rk_rng->rstc);
        rt_reset_control_put(rk_rng->rstc);
    }

    if (!rt_is_err_or_null(rk_rng->clk_arr))
    {
        rt_clk_array_disable_unprepare(rk_rng->clk_arr);
        rt_clk_array_put(rk_rng->clk_arr);
    }

    rt_free(rk_rng);
}

static rt_err_t rockchip_rng_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_rng *rk_rng = rt_calloc(1, sizeof(*rk_rng));

    if (!rk_rng)
    {
        return -RT_ENOMEM;
    }

    rk_rng->soc_data = pdev->id->data;

    rk_rng->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_rng->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_rng->rstc = rt_reset_control_get_by_name(dev, "reset");

    if (rt_is_err(rk_rng->rstc))
    {
        err = rt_ptr_err(rk_rng->rstc);
        goto _fail;
    }

    if (rk_rng->rstc)
    {
        rt_reset_control_assert(rk_rng->rstc);
        rt_hw_us_delay(10);
        rt_reset_control_deassert(rk_rng->rstc);
    }

    rk_rng->clk_arr = rt_clk_get_array(dev);

    if (rt_is_err(rk_rng->clk_arr))
    {
        err = rt_ptr_err(rk_rng->clk_arr);
        goto _fail;
    }

    rt_clk_array_prepare_enable(rk_rng->clk_arr);

    if (rk_rng->soc_data->init)
    {
        err = rk_rng->soc_data->init(rk_rng);
    }

    if (err)
    {
        goto _fail;
    }

    dev->user_data = rk_rng;

    rk_rng->parent.ops = &rockchip_rng_ops;

    if ((err = rt_hwcrypto_register(&rk_rng->parent, "hwrng")))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rockchip_rng_free(rk_rng);

    return err;
}

static rt_err_t rockchip_rng_remove(struct rt_platform_device *pdev)
{
    struct rockchip_rng *rk_rng = pdev->parent.user_data;

    rt_device_unregister(&rk_rng->parent.parent);

    rockchip_rng_free(rk_rng);

    return RT_EOK;
}

static const struct rockchip_rng_soc_data rk_crypto_v1_soc_data =
{
    .default_offset = 0,
    .read = rockchip_crypto_v1_read,
};

static const struct rockchip_rng_soc_data rk_crypto_v2_soc_data =
{
    .default_offset = CRYPTO_V2_RNG_DEFAULT_OFFSET,
    .read = rockchip_crypto_v2_read,
};

static const struct rockchip_rng_soc_data rk_trng_v1_soc_data =
{
    .default_offset = 0,
    .init = rockchip_trng_v1_init,
    .read = rockchip_trng_v1_read,
};

static const struct rt_ofw_node_id rockchip_rng_ofw_ids[] =
{
    { .compatible = "rockchip,cryptov1-rng", .data = &rk_crypto_v1_soc_data, },
    { .compatible = "rockchip,cryptov2-rng", .data = &rk_crypto_v2_soc_data, },
    { .compatible = "rockchip,trngv1", .data = &rk_trng_v1_soc_data, },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_rng_driver =
{
    .name = "rockchip-rng",
    .ids = rockchip_rng_ofw_ids,

    .probe = rockchip_rng_probe,
    .remove = rockchip_rng_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_rng_driver);
