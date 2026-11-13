/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "crypto.sunxi.ce"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_CE_CTL                  0x000
#define SUNXI_CE_KEY(index)           (0x004 + (index) * 4)
#define SUNXI_CE_IV(index)            (0x024 + (index) * 4)
#define SUNXI_CE_CNT(index)           (0x034 + (index) * 4)
#define SUNXI_CE_FCSR                 0x044
#define SUNXI_CE_ICSR                 0x048
#define SUNXI_CE_MD(index)            (0x04c + (index) * 4)
#define SUNXI_CE_RXFIFO               0x200
#define SUNXI_CE_TXFIFO               0x204

#define SUNXI_CE_CTL_START            RT_BIT(0)
#define SUNXI_CE_CTL_PRNG_START       RT_BIT(1)
#define SUNXI_CE_CTL_DIRECTION        RT_BIT(7)
#define SUNXI_CE_CTL_KEY_SIZE_SHIFT   8
#define SUNXI_CE_CTL_METHOD_SHIFT     4
#define SUNXI_CE_CTL_MODE_SHIFT       12

#define SUNXI_CE_FCSR_TX_READY        RT_BIT(22)
#define SUNXI_CE_FCSR_RX_READY        RT_BIT(30)
#define SUNXI_CE_ICSR_RX_EMPTY        RT_BIT(10)
#define SUNXI_CE_ICSR_TX_AVAILABLE    RT_BIT(8)

#define SUNXI_CE_METHOD_AES           0
#define SUNXI_CE_METHOD_PRNG          5

#define SUNXI_CE_AES_ECB              0
#define SUNXI_CE_AES_CBC              1
#define SUNXI_CE_AES_CTR              2

#define SUNXI_CE_AES_BLOCK_SIZE       16
#define SUNXI_CE_PRNG_SEED_WORDS      6
#define SUNXI_CE_TIMEOUT_US           500000

struct sunxi_ce
{
    struct rt_hwcrypto_device parent;

    void *base;
    struct rt_clk_array *clks;
    struct rt_reset_control *reset;
    struct rt_mutex lock;
    rt_bool_t clks_enabled;
};

#define to_sunxi_ce(raw) rt_container_of(raw, struct sunxi_ce, parent)

static rt_uint32_t sunxi_ce_readl(struct sunxi_ce *ce, rt_uint32_t offset)
{
    return HWREG32(ce->base + offset);
}

static void sunxi_ce_writel(struct sunxi_ce *ce, rt_uint32_t value,
        rt_uint32_t offset)
{
    HWREG32(ce->base + offset) = value;
}

static rt_uint32_t sunxi_ce_get_le32(const rt_uint8_t *data)
{
    rt_uint32_t value;

    rt_memcpy(&value, data, sizeof(value));
    return value;
}

static void sunxi_ce_put_le32(rt_uint8_t *data, rt_uint32_t value)
{
    rt_memcpy(data, &value, sizeof(value));
}

static rt_err_t sunxi_ce_wait_fifo(struct sunxi_ce *ce, rt_uint32_t mask)
{
    rt_uint32_t timeout;

    for (timeout = 0; timeout < SUNXI_CE_TIMEOUT_US; ++timeout)
    {
        if (sunxi_ce_readl(ce, SUNXI_CE_FCSR) & mask)
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    return -RT_ETIMEOUT;
}

static void sunxi_ce_reset_engine(struct sunxi_ce *ce)
{
    rt_uint32_t value;

    sunxi_ce_writel(ce, 0, SUNXI_CE_CTL);
    sunxi_ce_writel(ce, 0, SUNXI_CE_FCSR);
    value = sunxi_ce_readl(ce, SUNXI_CE_ICSR);
    sunxi_ce_writel(ce, value | SUNXI_CE_ICSR_RX_EMPTY |
            SUNXI_CE_ICSR_TX_AVAILABLE, SUNXI_CE_ICSR);
}

static rt_err_t sunxi_ce_aes_mode(hwcrypto_type type, rt_uint32_t *mode)
{
    switch (type)
    {
    case HWCRYPTO_TYPE_AES_ECB:
        *mode = SUNXI_CE_AES_ECB;
        return RT_EOK;
    case HWCRYPTO_TYPE_AES_CBC:
        *mode = SUNXI_CE_AES_CBC;
        return RT_EOK;
    case HWCRYPTO_TYPE_AES_CTR:
        *mode = SUNXI_CE_AES_CTR;
        return RT_EOK;
    default:
        return -RT_ENOSYS;
    }
}

static rt_err_t sunxi_ce_aes_crypt(struct hwcrypto_symmetric *symmetric,
        struct hwcrypto_symmetric_info *info)
{
    rt_err_t err;
    rt_uint32_t control;
    rt_uint32_t aes_mode;
    rt_size_t offset;
    rt_size_t word;
    struct sunxi_ce *ce;

    if (!symmetric->key_bitlen ||
            (symmetric->key_bitlen != 128 && symmetric->key_bitlen != 192 &&
             symmetric->key_bitlen != 256) ||
            (info->length % SUNXI_CE_AES_BLOCK_SIZE) ||
            (!info->in && info->length) || (!info->out && info->length))
    {
        return -RT_EINVAL;
    }

    if ((err = sunxi_ce_aes_mode(symmetric->parent.type, &aes_mode)))
    {
        return err;
    }

    if (aes_mode != SUNXI_CE_AES_ECB &&
            symmetric->iv_len != SUNXI_CE_AES_BLOCK_SIZE)
    {
        return -RT_EINVAL;
    }

    ce = to_sunxi_ce(symmetric->parent.device);
    rt_mutex_take(&ce->lock, RT_WAITING_FOREVER);

    sunxi_ce_reset_engine(ce);
    control = SUNXI_CE_METHOD_AES << SUNXI_CE_CTL_METHOD_SHIFT;
    control |= aes_mode << SUNXI_CE_CTL_MODE_SHIFT;
    control |= ((symmetric->key_bitlen - 128) / 64) << SUNXI_CE_CTL_KEY_SIZE_SHIFT;
    if (info->mode == HWCRYPTO_MODE_DECRYPT)
    {
        control |= SUNXI_CE_CTL_DIRECTION;
    }
    sunxi_ce_writel(ce, control, SUNXI_CE_CTL);

    for (offset = 0; offset < symmetric->key_bitlen / 8; offset += 4)
    {
        sunxi_ce_writel(ce, sunxi_ce_get_le32(&symmetric->key[offset]),
                SUNXI_CE_KEY(offset / 4));
    }

    if (aes_mode == SUNXI_CE_AES_CBC)
    {
        for (offset = 0; offset < SUNXI_CE_AES_BLOCK_SIZE; offset += 4)
        {
            sunxi_ce_writel(ce, sunxi_ce_get_le32(&symmetric->iv[offset]),
                    SUNXI_CE_IV(offset / 4));
        }
    }
    else if (aes_mode == SUNXI_CE_AES_CTR)
    {
        for (offset = 0; offset < SUNXI_CE_AES_BLOCK_SIZE; offset += 4)
        {
            sunxi_ce_writel(ce, sunxi_ce_get_le32(&symmetric->iv[offset]),
                    SUNXI_CE_CNT(offset / 4));
        }
    }

    sunxi_ce_writel(ce, control | SUNXI_CE_CTL_START, SUNXI_CE_CTL);

    for (offset = 0; offset < info->length; offset += SUNXI_CE_AES_BLOCK_SIZE)
    {
        for (word = 0; word < SUNXI_CE_AES_BLOCK_SIZE; word += 4)
        {
            if ((err = sunxi_ce_wait_fifo(ce, SUNXI_CE_FCSR_RX_READY)))
            {
                goto _out;
            }

            sunxi_ce_writel(ce, sunxi_ce_get_le32(&info->in[offset + word]),
                    SUNXI_CE_RXFIFO);
        }

        for (word = 0; word < SUNXI_CE_AES_BLOCK_SIZE; word += 4)
        {
            if ((err = sunxi_ce_wait_fifo(ce, SUNXI_CE_FCSR_TX_READY)))
            {
                goto _out;
            }

            sunxi_ce_put_le32(&info->out[offset + word],
                    sunxi_ce_readl(ce, SUNXI_CE_TXFIFO));
        }
    }

    err = RT_EOK;

_out:
    sunxi_ce_reset_engine(ce);
    rt_mutex_release(&ce->lock);

    return err;
}

static rt_uint32_t sunxi_ce_seed_word(rt_uint32_t salt)
{
    rt_uint32_t i;
    rt_uint64_t counter;
    rt_uint32_t value;

    counter = rt_clock_time_get_counter();
    value = (rt_uint32_t)counter ^ (rt_uint32_t)(counter >> 32) ^ salt;

    for (i = 0; i < 32; ++i)
    {
        counter = rt_clock_time_get_counter();
        value ^= value << 13;
        value ^= value >> 17;
        value ^= value << 5;
        value ^= (rt_uint32_t)counter ^ (rt_uint32_t)(counter >> 32);
    }

    return value;
}

static rt_uint32_t sunxi_ce_rng_update(struct hwcrypto_rng *rng)
{
    rt_uint32_t control;
    rt_uint32_t i;
    rt_uint32_t timeout;
    rt_uint32_t value;
    struct sunxi_ce *ce;

    value = 0;
    ce = to_sunxi_ce(rng->parent.device);

    rt_mutex_take(&ce->lock, RT_WAITING_FOREVER);
    sunxi_ce_reset_engine(ce);

    control = SUNXI_CE_METHOD_PRNG << SUNXI_CE_CTL_METHOD_SHIFT;
    sunxi_ce_writel(ce, control, SUNXI_CE_CTL);

    for (i = 0; i < SUNXI_CE_PRNG_SEED_WORDS; ++i)
    {
        sunxi_ce_writel(ce, sunxi_ce_seed_word((i + 1) * 0x9e3779b9U),
                SUNXI_CE_KEY(i));
    }

    /* The PRNG trigger is sampled only after the CE engine has started. */
    sunxi_ce_writel(ce, control | SUNXI_CE_CTL_START, SUNXI_CE_CTL);
    sunxi_ce_writel(ce, control | SUNXI_CE_CTL_START |
            SUNXI_CE_CTL_PRNG_START, SUNXI_CE_CTL);
    for (timeout = 0; timeout < SUNXI_CE_TIMEOUT_US; ++timeout)
    {
        if (!(sunxi_ce_readl(ce, SUNXI_CE_CTL) & SUNXI_CE_CTL_PRNG_START))
        {
            value = sunxi_ce_readl(ce, SUNXI_CE_MD(0));
            break;
        }

        rt_hw_us_delay(1);
    }

    if (timeout == SUNXI_CE_TIMEOUT_US)
    {
        LOG_E("PRNG operation timed out");
    }

    sunxi_ce_reset_engine(ce);
    rt_mutex_release(&ce->lock);

    return value;
}

static const struct hwcrypto_symmetric_ops sunxi_ce_aes_ops =
{
    .crypt = sunxi_ce_aes_crypt,
};

static const struct hwcrypto_rng_ops sunxi_ce_rng_ops =
{
    .update = sunxi_ce_rng_update,
};

static rt_err_t sunxi_ce_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_uint32_t aes_mode;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
        if (sunxi_ce_aes_mode(ctx->type, &aes_mode))
        {
            return -RT_ENOSYS;
        }
        ((struct hwcrypto_symmetric *)ctx)->ops = &sunxi_ce_aes_ops;
        return RT_EOK;
    case HWCRYPTO_TYPE_RNG:
        ((struct hwcrypto_rng *)ctx)->ops = &sunxi_ce_rng_ops;
        return RT_EOK;
    default:
        return -RT_ENOSYS;
    }
}

static void sunxi_ce_destroy(struct rt_hwcrypto_ctx *ctx)
{
    RT_UNUSED(ctx);
}

static rt_err_t sunxi_ce_copy(struct rt_hwcrypto_ctx *destination,
        const struct rt_hwcrypto_ctx *source)
{
    RT_UNUSED(destination);
    RT_UNUSED(source);
    return RT_EOK;
}

static void sunxi_ce_reset(struct rt_hwcrypto_ctx *ctx)
{
    RT_UNUSED(ctx);
}

static const struct rt_hwcrypto_ops sunxi_ce_ops =
{
    .create = sunxi_ce_create,
    .destroy = sunxi_ce_destroy,
    .copy = sunxi_ce_copy,
    .reset = sunxi_ce_reset,
};

static void sunxi_ce_release(struct sunxi_ce *ce)
{
    if (ce->base && ce->clks_enabled)
    {
        sunxi_ce_reset_engine(ce);
    }
    if (!rt_is_err_or_null(ce->reset))
    {
        rt_reset_control_assert(ce->reset);
        rt_reset_control_put(ce->reset);
    }
    if (!rt_is_err_or_null(ce->clks))
    {
        if (ce->clks_enabled)
        {
            rt_clk_array_disable_unprepare(ce->clks);
        }
        rt_clk_array_put(ce->clks);
    }
    if (ce->base)
    {
        rt_iounmap(ce->base);
    }
    rt_mutex_detach(&ce->lock);
    rt_free(ce);
}

static rt_err_t sunxi_ce_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_ce *ce = rt_calloc(1, sizeof(*ce));

    if (!ce)
    {
        return -RT_ENOMEM;
    }

    rt_mutex_init(&ce->lock, "sunxi-ce", RT_IPC_FLAG_PRIO);
    ce->base = rt_dm_dev_iomap(dev, 0);
    if (!ce->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ce->reset = rt_reset_control_get_by_name(dev, "bus");
    if (rt_is_err(ce->reset))
    {
        err = rt_ptr_err(ce->reset);
        goto _fail;
    }

    ce->clks = rt_clk_get_array(dev);
    if (rt_is_err(ce->clks))
    {
        err = rt_ptr_err(ce->clks);
        goto _fail;
    }

    if ((err = rt_clk_array_prepare_enable(ce->clks)))
    {
        goto _fail;
    }
    ce->clks_enabled = RT_TRUE;

    rt_reset_control_assert(ce->reset);
    rt_hw_us_delay(10);
    rt_reset_control_deassert(ce->reset);

    ce->parent.ops = &sunxi_ce_ops;
    ce->parent.user_data = ce;
    if ((err = rt_hwcrypto_register(&ce->parent, RT_HWCRYPTO_DEFAULT_NAME)))
    {
        goto _fail;
    }

    dev->user_data = ce;
    return RT_EOK;

_fail:
    sunxi_ce_release(ce);
    return err;
}

static const struct rt_ofw_node_id sunxi_ce_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-ce" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_ce_driver =
{
    .name = "sunxi-ce",
    .ids = sunxi_ce_ofw_ids,
    .probe = sunxi_ce_probe,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_ce_driver);
