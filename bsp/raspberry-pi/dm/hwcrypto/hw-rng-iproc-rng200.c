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

#define RNG_CTRL_OFFSET                                 0x00
#define RNG_CTRL_RNG_RBGEN_MASK                         0x00001fff
#define RNG_CTRL_RNG_RBGEN_ENABLE                       0x00000001

#define RNG_SOFT_RESET_OFFSET                           0x04
#define RNG_SOFT_RESET                                  0x00000001

#define RBG_SOFT_RESET_OFFSET                           0x08
#define RBG_SOFT_RESET                                  0x00000001

#define RNG_INT_STATUS_OFFSET                           0x18
#define RNG_INT_STATUS_MASTER_FAIL_LOCKOUT_IRQ_MASK     0x80000000
#define RNG_INT_STATUS_STARTUP_TRANSITIONS_MET_IRQ_MASK 0x00020000
#define RNG_INT_STATUS_NIST_FAIL_IRQ_MASK               0x00000020
#define RNG_INT_STATUS_TOTAL_BITS_COUNT_IRQ_MASK        0x00000001

#define RNG_FIFO_DATA_OFFSET                            0x20

#define RNG_FIFO_COUNT_OFFSET                           0x24
#define RNG_FIFO_COUNT_RNG_FIFO_COUNT_MASK              0x000000ff

#define MAX_RESETS_PER_READ     1
#define MAX_IDLE_TIME           (1 * 100)

struct iproc_rng200
{
    struct rt_hwcrypto_device parent;

    void *regs;
};

#define raw_to_iproc_rng200(raw) rt_container_of(raw, struct iproc_rng200, parent)

static void iproc_rng200_enable_set(struct iproc_rng200 *rng200, rt_bool_t enable)
{
    rt_uint32_t val;

    val = HWREG32(rng200->regs + RNG_CTRL_OFFSET);
    val &= ~RNG_CTRL_RNG_RBGEN_MASK;

    if (enable)
    {
        val |= RNG_CTRL_RNG_RBGEN_ENABLE;
    }

    HWREG32(rng200->regs + RNG_CTRL_OFFSET) = val;
}

static void iproc_rng200_restart(struct iproc_rng200 *rng200)
{
    rt_uint32_t val;
    void *regs = rng200->regs;

    iproc_rng200_enable_set(rng200, RT_FALSE);

    /* Clear all interrupt status */
    HWREG32(regs + RNG_INT_STATUS_OFFSET) = 0xffffffffUL;

    /* Reset RNG and RBG */
    val = HWREG32(regs + RBG_SOFT_RESET_OFFSET);
    val |= RBG_SOFT_RESET;
    HWREG32(regs + RBG_SOFT_RESET_OFFSET) = val;

    val = HWREG32(regs + RNG_SOFT_RESET_OFFSET);
    val |= RNG_SOFT_RESET;
    HWREG32(regs + RNG_SOFT_RESET_OFFSET) = val;

    val = HWREG32(regs + RNG_SOFT_RESET_OFFSET);
    val &= ~RNG_SOFT_RESET;
    HWREG32(regs + RNG_SOFT_RESET_OFFSET) = val;

    val = HWREG32(regs + RBG_SOFT_RESET_OFFSET);
    val &= ~RBG_SOFT_RESET;
    HWREG32(regs + RBG_SOFT_RESET_OFFSET) = val;

    iproc_rng200_enable_set(rng200, RT_TRUE);
}

static rt_uint32_t iproc_rng200_read(struct iproc_rng200 *rng200, void *buf,
        rt_size_t max, rt_bool_t wait)
{
    rt_uint32_t num_remaining = max, status, num_resets = 0;

    while (num_remaining > 0)
    {
        rt_thread_mdelay(MAX_IDLE_TIME >> 1);

        /* Is RNG sane? If not, reset it. */
        status = HWREG32(rng200->regs + RNG_INT_STATUS_OFFSET);
        if ((status & (RNG_INT_STATUS_MASTER_FAIL_LOCKOUT_IRQ_MASK |
                RNG_INT_STATUS_NIST_FAIL_IRQ_MASK)) != 0)
        {
            if (num_resets >= MAX_RESETS_PER_READ)
            {
                return max - num_remaining;
            }

            iproc_rng200_restart(rng200);
            ++num_resets;
        }

        /* Are there any random numbers available? */
        if ((HWREG32(rng200->regs + RNG_FIFO_COUNT_OFFSET) &
                RNG_FIFO_COUNT_RNG_FIFO_COUNT_MASK) > 0)
        {
            if (num_remaining >= sizeof(rt_uint32_t))
            {
                /* Buffer has room to store entire word */
                *(rt_uint32_t *)buf = HWREG32(rng200->regs + RNG_FIFO_DATA_OFFSET);
                buf += sizeof(rt_uint32_t);
                num_remaining -= sizeof(rt_uint32_t);
            }
            else
            {
                /* Buffer can only store partial word */
                rt_uint32_t rnd_number = HWREG32(rng200->regs + RNG_FIFO_DATA_OFFSET);

                rt_memcpy(buf, &rnd_number, num_remaining);
                buf += num_remaining;
                num_remaining = 0;
            }
        }
        else
        {
            if (!wait)
            {
                /* Cannot wait, return immediately */
                return max - num_remaining;
            }

            /* Can wait, give others chance to run */
            rt_hw_us_delay((rt_min(num_remaining * 10, 500U)) >> 1);
        }
    }

    return max - num_remaining;
}

static rt_err_t iproc_rng200_init(struct iproc_rng200 *rng200)
{
    iproc_rng200_enable_set(rng200, RT_TRUE);

    return RT_EOK;
}

static void iproc_rng200_cleanup(struct iproc_rng200 *rng200)
{
    iproc_rng200_enable_set(rng200, RT_FALSE);
}

static rt_uint32_t iproc_rng200_rand(struct hwcrypto_rng *ctx)
{
    rt_size_t size;
    rt_uint32_t rand;
    struct iproc_rng200 *rng200 = raw_to_iproc_rng200(ctx->parent.device);

    size = iproc_rng200_read(rng200, &rand, sizeof(rand), RT_TRUE);

    if (size != sizeof(rand))
    {
        return 0;
    }

    return rand;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = iproc_rng200_rand,
};

static rt_err_t iproc_rng200_create(struct rt_hwcrypto_ctx *ctx)
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

static void iproc_rng200_destroy(struct rt_hwcrypto_ctx *ctx)
{
    struct iproc_rng200 *rng200 = raw_to_iproc_rng200(ctx->device);

    iproc_rng200_cleanup(rng200);

    rt_free(ctx->contex);
}

static rt_err_t iproc_rng200_copy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
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

static void iproc_rng200_reset(struct rt_hwcrypto_ctx *ctx)
{
    struct iproc_rng200 *rng200 = raw_to_iproc_rng200(ctx->device);

    iproc_rng200_init(rng200);
}

static const struct rt_hwcrypto_ops iproc_rng200_ops =
{
    .create = iproc_rng200_create,
    .destroy = iproc_rng200_destroy,
    .copy = iproc_rng200_copy,
    .reset = iproc_rng200_reset,
};

static rt_err_t iproc_rng200_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct iproc_rng200 *rng200 = rt_calloc(1, sizeof(*rng200));

    if (!rng200)
    {
        return -RT_ENOMEM;
    }

    rng200->regs = rt_dm_dev_iomap(dev, 0);

    if (!rng200->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    dev->user_data = rng200;

    rng200->parent.ops = &iproc_rng200_ops;

    if ((err = rt_hwcrypto_register(&rng200->parent, "hwrng")))
    {
        goto _fail;
    }

    iproc_rng200_init(rng200);

    return RT_EOK;

_fail:
    if (rng200->regs)
    {
        rt_iounmap(rng200->regs);
    }

    rt_free(rng200);

    return err;
}

static rt_err_t iproc_rng200_remove(struct rt_platform_device *pdev)
{
    struct iproc_rng200 *rng200 = pdev->parent.user_data;

    iproc_rng200_cleanup(rng200);

    rt_device_unregister(&rng200->parent.parent);

    rt_iounmap(rng200->regs);
    rt_free(rng200);

    return RT_EOK;
}

static const struct rt_ofw_node_id iproc_rng200_ofw_ids[] =
{
    { .compatible = "brcm,bcm2711-rng200", },
    { .compatible = "brcm,bcm7211-rng200", },
    { .compatible = "brcm,bcm7278-rng200", },
    { .compatible = "brcm,iproc-rng200", },
    { /* sentinel */ }
};

static struct rt_platform_driver iproc_rng200_driver =
{
    .name = "iproc-rng200",
    .ids = iproc_rng200_ofw_ids,

    .probe = iproc_rng200_probe,
    .remove = iproc_rng200_remove,
};
RT_PLATFORM_DRIVER_EXPORT(iproc_rng200_driver);
