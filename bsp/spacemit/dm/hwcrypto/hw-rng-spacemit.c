/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "spacemit.h"

#define RNG_BYTE_CNT        0x04
#define RNG_SRC_ADDR        0x14
#define RNG_DEST_ADDR       0x24
#define RNG_NEXT_DESC_PTR   0x34
#define RNG_SQU_CTRL        0x44
#define RNG_CURR_DESC_PTR   0x74
#define RNG_INT_MASK        0x84
#define RNG_REST_SEL        0x94
#define RNG_INT_STATUS      0xa4
#define RNG_CTRL            0xc0
#define RNG_DATA            0xc4
#define RNG_SEED_VAL        0xc8
#define RNG_CTRL_EXT        0xd0

#define SQU_CTRL_FIFO_CLR   RT_BIT(30)
#define SQU_CTRL_ENABLE_DMA 0x03c60383
#define RNG_INT_DONE_MASK   RT_BIT(0)
#define RESET_SEL_MASK      RT_BIT(0)
#define CTRL_RNG_EN         RT_BIT(0)
#define CTRL_RNG_VALID      RT_BIT(31)
#define CTRL_RNG_SEED_VALID RT_BIT(30)
#define CTRL_RNG_SEED_EN    RT_BIT(1)
#define RNG_REG_SEL         RT_BIT(4)
#define RNG_REG_LDO_PU      RT_BIT(6)
#define RNG_SUCCESS         0x55
#define RNG_FAIL            0xaa

#define DMA_MAX_SIZE        0xfff0

struct spacemit_rng
{
    struct rt_hwcrypto_device parent;

    void *base;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    struct rt_spinlock lock;
};

static void spacemit_rng_clr_fifo(struct spacemit_rng *rng)
{
    rt_uint32_t val;

    val = HWREG32(rng->base + RNG_SQU_CTRL);
    val |= SQU_CTRL_FIFO_CLR;
    HWREG32(rng->base + RNG_SQU_CTRL) = val;
}

static void spacemit_rng_reset_status(struct spacemit_rng *rng)
{
    rt_uint32_t val;

    /* Clear squ fifo */
    spacemit_rng_clr_fifo(rng);

    /* Clear rng and seed ctrl bit */
    val = HWREG32(rng->base + RNG_CTRL);
    val &= ~(CTRL_RNG_EN | CTRL_RNG_VALID);
    val &= ~(CTRL_RNG_SEED_EN | CTRL_RNG_SEED_VALID);
    HWREG32(rng->base + RNG_CTRL) = val;
}

static rt_err_t spacemit_rng_reset_seed(struct spacemit_rng *rng)
{
    rt_uint32_t val;
    rt_tick_t timeout = rt_tick_from_millisecond(100);

    for (int i = 0; i < 2; ++i)
    {
        /* Generate software seed */
        HWREG32(rng->base + RNG_SEED_VAL) = rt_tick_get();

        val = HWREG32(rng->base + RNG_CTRL);
        val |= CTRL_RNG_SEED_EN;
        HWREG32(rng->base + RNG_CTRL) = val;

        timeout += rt_tick_get();

        do {
            val = HWREG32(rng->base + RNG_CTRL);

            if (val & CTRL_RNG_SEED_VALID)
            {
                return RT_EOK;
            }

            if (rt_tick_get() >= timeout)
            {
                break;
            }
        } while (RT_TRUE);
    }

    spacemit_rng_reset_status(rng);

    return -RT_EIO;
}

static rt_uint32_t spacemit_rng_rand(struct hwcrypto_rng *ctx)
{
    rt_uint32_t val;
    rt_tick_t timeout = rt_tick_from_millisecond(100);
    struct spacemit_rng *rng = rt_container_of(ctx->parent.device, struct spacemit_rng, parent);

    rt_hw_spin_lock(&rng->lock.lock);

    if (spacemit_rng_reset_seed(rng))
    {
        goto _unlock;
    }

    /* Generate random value */
    val = HWREG32(rng->base + RNG_CTRL);
    val |= CTRL_RNG_EN;
    HWREG32(rng->base + RNG_CTRL) = val;

    for (int i = 0; i < 2; ++i)
    {
        timeout += rt_tick_get();

        do {
            if (HWREG32(rng->base + RNG_CTRL) & CTRL_RNG_VALID)
            {
                /* Clear squ fifo */
                spacemit_rng_clr_fifo(rng);
                val = HWREG32(rng->base + RNG_DATA);

                goto _unlock;
            }

            rt_hw_us_delay(200);

            if (rt_tick_get() >= timeout)
            {
                break;
            }
        } while (RT_TRUE);
    }

    val = 0;
    spacemit_rng_reset_status(rng);

_unlock:
    rt_hw_spin_unlock(&rng->lock.lock);

    return val;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = spacemit_rng_rand,
};

static rt_err_t spacemit_rng_create(struct rt_hwcrypto_ctx *ctx)
{
    if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_RNG)
    {
        struct hwcrypto_rng *rng;

        ctx->contex = RT_NULL;

        rng = rt_container_of(ctx, struct hwcrypto_rng, parent);
        rng->ops = &rng_ops;

        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static void spacemit_rng_destroy(struct rt_hwcrypto_ctx *ctx)
{
}

static rt_err_t spacemit_rng_copy(struct rt_hwcrypto_ctx *des,
        const struct rt_hwcrypto_ctx *src)
{
    if ((src->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_RNG)
    {
        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static void spacemit_rng_reset(struct rt_hwcrypto_ctx *ctx)
{
}

static const struct rt_hwcrypto_ops spacemit_rng_ops =
{
    .create = spacemit_rng_create,
    .destroy = spacemit_rng_destroy,
    .copy = spacemit_rng_copy,
    .reset = spacemit_rng_reset,
};

static void spacemit_crypto_free(struct spacemit_rng *rng)
{
    if (rng->base)
    {
        rt_iounmap(rng->base);
    }

    if (!rt_is_err_or_null(rng->rstc))
    {
        rt_reset_control_assert(rng->rstc);
        rt_reset_control_put(rng->rstc);
    }

    if (!rt_is_err_or_null(rng->clk))
    {
        rt_clk_disable_unprepare(rng->clk);
        rt_clk_put(rng->clk);
    }

    rt_free(rng);
}

static rt_err_t spacemit_rng_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_rng *rng = rt_calloc(1, sizeof(*rng));

    if (!rng)
    {
        return -RT_ENOMEM;
    }

    rng->base = rt_dm_dev_iomap(dev, 0);
    if (!rng->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rng->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(rng->clk))
    {
        err = rt_ptr_err(rng->clk);
        goto _fail;
    }
    rt_clk_prepare_enable(rng->clk);

    rng->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(rng->rstc))
    {
        err = rt_ptr_err(rng->rstc);
        goto _fail;
    }
    rt_reset_control_deassert(rng->rstc);

    rt_spin_lock_init(&rng->lock);
    rng->parent.ops = &spacemit_rng_ops;
    rng->parent.id = __LINE__;

    if ((err = rt_hwcrypto_register(&rng->parent, "hwrng")))
    {
        goto _fail;
    }

    dev->user_data = rng;

    return RT_EOK;

_fail:
    spacemit_crypto_free(rng);

    return err;
}

static rt_err_t spacemit_rng_remove(struct rt_platform_device *pdev)
{
    struct spacemit_rng *rng = pdev->parent.user_data;

    rt_device_unregister(&rng->parent.parent);

    spacemit_crypto_free(rng);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_rng_ofw_ids[] =
{
    { .compatible = "spacemit,hw_crng" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_rng_driver =
{
    .name = "hwrng-spacemit",
    .ids = spacemit_rng_ofw_ids,

    .probe = spacemit_rng_probe,
    .remove = spacemit_rng_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_rng_driver);
