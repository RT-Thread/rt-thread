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

#define DBG_TAG "rng.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RNG_CTRL            0x0
#define RNG_STATUS          0x4
#define RNG_DATA            0x8
#define RNG_INT_MASK        0x10

/* enable rng */
#define RNG_RBGEN           0x1

/* the initial numbers generated are "less random" so will be discarded */
#define RNG_WARMUP_COUNT    0x40000

#define RNG_INT_OFF         0x1

struct bcm2835_rng_soc_data
{
    rt_bool_t mask_interrupts;
};

struct bcm2835_rng
{
    struct rt_hwcrypto_device parent;

    void *regs;

    rt_bool_t mask_interrupts;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;
};

#define raw_to_bcm2835_rng(raw) rt_container_of(raw, struct bcm2835_rng, parent)

rt_inline rt_uint32_t rng_readl(struct bcm2835_rng *brng, int offset)
{
    return HWREG32(brng->regs + offset);
}

rt_inline void rng_writel(struct bcm2835_rng *brng, int offset, rt_uint32_t val)
{
    HWREG32(brng->regs + offset) = val;
}

static rt_uint32_t bcm2835_rng_read(struct bcm2835_rng *brng, void *buf,
        rt_size_t max, rt_bool_t wait)
{
    rt_uint32_t max_words = max / sizeof(rt_uint32_t), num_words;

    while ((rng_readl(brng, RNG_STATUS) >> 24) == 0)
    {
        if (!wait)
        {
            return 0;
        }

        rt_thread_mdelay(1000);
    }

    num_words = rng_readl(brng, RNG_STATUS) >> 24;

    if (num_words > max_words)
    {
        num_words = max_words;
    }

    for (int count = 0; count < num_words; ++count)
    {
        ((rt_uint32_t *)buf)[count] = rng_readl(brng, RNG_DATA);
    }

    return num_words * sizeof(rt_uint32_t);
}

static rt_err_t bcm2835_rng_init(struct bcm2835_rng *brng)
{
    rt_err_t err;
    rt_uint32_t val;

    if ((err = rt_clk_prepare_enable(brng->clk)))
    {
        LOG_E("CLK enable error = %s", rt_strerror(err));
        return err;
    }

    if ((err = rt_reset_control_reset(brng->rstc)))
    {
        LOG_E("Reset error = %s", rt_strerror(err));
        return err;
    }

    if (brng->mask_interrupts)
    {
        /* mask the interrupt */
        val = rng_readl(brng, RNG_INT_MASK);
        val |= RNG_INT_OFF;
        rng_writel(brng, RNG_INT_MASK, val);
    }

    /* set warm-up count & enable */
    rng_writel(brng, RNG_STATUS, RNG_WARMUP_COUNT);
    rng_writel(brng, RNG_CTRL, RNG_RBGEN);

    return RT_EOK;
}

static void bcm2835_rng_cleanup(struct bcm2835_rng *brng)
{
    /* Disable rng hardware */
    rng_writel(brng, RNG_CTRL, 0);

    rt_clk_disable_unprepare(brng->clk);
}

static rt_uint32_t bcm2835_rng_rand(struct hwcrypto_rng *ctx)
{
    rt_size_t size;
    rt_uint32_t rand;
    struct bcm2835_rng *brng = raw_to_bcm2835_rng(ctx->parent.device);

    size = bcm2835_rng_read(brng, &rand, sizeof(rand), RT_TRUE);

    if (size != sizeof(rand))
    {
        return 0;
    }

    return rand;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = bcm2835_rng_rand,
};

static rt_err_t bcm2835_rng_create(struct rt_hwcrypto_ctx *ctx)
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

static void bcm2835_rng_destroy(struct rt_hwcrypto_ctx *ctx)
{
    struct bcm2835_rng *brng = raw_to_bcm2835_rng(ctx->device);

    bcm2835_rng_cleanup(brng);

    rt_free(ctx->contex);
}

static rt_err_t bcm2835_rng_copy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
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

static void bcm2835_rng_reset(struct rt_hwcrypto_ctx *ctx)
{
    struct bcm2835_rng *brng = raw_to_bcm2835_rng(ctx->device);

    bcm2835_rng_init(brng);
}

static const struct rt_hwcrypto_ops bcm2835_rng_ops =
{
    .create = bcm2835_rng_create,
    .destroy = bcm2835_rng_destroy,
    .copy = bcm2835_rng_copy,
    .reset = bcm2835_rng_reset,
};

static void bcm2835_rng_free(struct bcm2835_rng *brng)
{
    if (!brng->regs)
    {
        rt_iounmap(brng->regs);
    }

    if (!rt_is_err_or_null(brng->rstc))
    {
        rt_reset_control_assert(brng->rstc);
        rt_reset_control_put(brng->rstc);
    }

    if (!rt_is_err_or_null(brng->clk))
    {
        rt_clk_disable_unprepare(brng->clk);
        rt_clk_put(brng->clk);
    }

    rt_free(brng);
}

static rt_err_t bcm2835_rng_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    struct rt_device *dev = &pdev->parent;
    const struct bcm2835_rng_soc_data *soc_data;
    struct bcm2835_rng *brng = rt_calloc(1, sizeof(*brng));

    if (!brng)
    {
        return -RT_ENOMEM;
    }

    brng->regs = rt_dm_dev_iomap(dev, 0);

    if (!brng->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    brng->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(brng->clk))
    {
        err = rt_ptr_err(brng->clk);
        goto _fail;
    }

    brng->rstc = rt_reset_control_get_by_index(dev, 0);

    if (rt_is_err(brng->rstc))
    {
        err = rt_ptr_err(brng->rstc);
        goto _fail;
    }

    if ((soc_data = pdev->id->data))
    {
        brng->mask_interrupts = soc_data->mask_interrupts;
    }

    dev->user_data = brng;

    brng->parent.ops = &bcm2835_rng_ops;

    if ((err = rt_hwcrypto_register(&brng->parent, "hwrng")))
    {
        goto _fail;
    }

    bcm2835_rng_init(brng);

    return RT_EOK;

_fail:
    bcm2835_rng_free(brng);

    return err;
}

static rt_err_t bcm2835_rng_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_rng *brng = pdev->parent.user_data;

    bcm2835_rng_cleanup(brng);

    rt_device_unregister(&brng->parent.parent);

    bcm2835_rng_free(brng);

    return RT_EOK;
}

static const struct bcm2835_rng_soc_data nsp_rng_data =
{
    .mask_interrupts = RT_TRUE,
};

static const struct rt_ofw_node_id bcm2835_rng_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-rng" },
    { .compatible = "brcm,bcm-nsp-rng", .data = &nsp_rng_data },
    { .compatible = "brcm,bcm5301x-rng", .data = &nsp_rng_data },
    { .compatible = "brcm,bcm6368-rng" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_rng_driver =
{
    .name = "bcm2835-rng",
    .ids = bcm2835_rng_ofw_ids,

    .probe = bcm2835_rng_probe,
    .remove = bcm2835_rng_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_rng_driver);
