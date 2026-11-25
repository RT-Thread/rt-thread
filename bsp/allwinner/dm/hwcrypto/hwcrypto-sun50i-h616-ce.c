/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "crypto.h616"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define H616_CE_TDQ 0x000
#define H616_CE_ICR 0x008
#define H616_CE_ISR 0x00c
#define H616_CE_TLR 0x010
#define H616_CE_ESR 0x018

#define H616_CE_FLOW_AES       0
#define H616_CE_FLOW_TRNG      3
#define H616_CE_COMM_DECRYPT   RT_BIT(8)
#define H616_CE_COMM_INTERRUPT RT_BIT(31)
#define H616_CE_AES            0
#define H616_CE_TRNG_V2        0x1c
#define H616_CE_AES_128        0
#define H616_CE_AES_192        1
#define H616_CE_AES_256        2
#define H616_CE_AES_ECB        0
#define H616_CE_AES_CBC        RT_BIT(8)
#define H616_CE_BLOCK_SIZE     16
#define H616_CE_TRNG_SIZE      32
#define H616_CE_TIMEOUT_US     3000000

struct h616_ce_sg
{
    rt_uint32_t address;
    rt_uint32_t length;
} __attribute__((packed));

struct h616_ce_task
{
    rt_uint32_t id;
    rt_uint32_t common_ctl;
    rt_uint32_t symmetric_ctl;
    rt_uint32_t asymmetric_ctl;
    rt_uint32_t key;
    rt_uint32_t iv;
    rt_uint32_t counter;
    rt_uint32_t data_length;
    struct h616_ce_sg source[8];
    struct h616_ce_sg destination[8];
    rt_uint32_t next;
    rt_uint32_t reserved[3];
} __attribute__((packed, aligned(8)));

struct h616_ce
{
    struct rt_hwcrypto_device parent;
    struct rt_device *dev;
    void *base;
    struct rt_clk_array *clks;
    struct rt_reset_control *reset;
    struct rt_mutex lock;
    struct h616_ce_task *task;
    rt_ubase_t task_dma;
    void *trng;
    rt_ubase_t trng_dma;
    rt_bool_t clks_enabled;
};

#define to_h616_ce(raw) rt_container_of(raw, struct h616_ce, parent)

static rt_uint32_t h616_ce_readl(struct h616_ce *ce, rt_uint32_t offset)
{
    return HWREG32(ce->base + offset);
}

static void h616_ce_writel(struct h616_ce *ce, rt_uint32_t value,
                           rt_uint32_t offset)
{
    HWREG32(ce->base + offset) = value;
}

static rt_err_t h616_ce_word_address(rt_ubase_t address, rt_uint32_t *word)
{
    if ((address & 3) || address > RT_UINT32_MAX)
    {
        return -RT_EINVAL;
    }
    *word = address >> 2;
    return RT_EOK;
}

static rt_err_t h616_ce_run_task(struct h616_ce *ce, rt_uint32_t flow)
{
    rt_uint32_t task_address;
    rt_uint32_t status;
    rt_uint32_t elapsed;
    rt_err_t err;

    if ((err = h616_ce_word_address(ce->task_dma, &task_address)))
    {
        return err;
    }
    h616_ce_writel(ce, RT_BIT(flow), H616_CE_ISR);
    h616_ce_writel(ce, h616_ce_readl(ce, H616_CE_ICR) | RT_BIT(flow), H616_CE_ICR);
    h616_ce_writel(ce, task_address, H616_CE_TDQ);
    rt_hw_dmb();
    h616_ce_writel(ce, 1 | ((ce->task->common_ctl & 0x7f) << 8), H616_CE_TLR);
    for (elapsed = 0; elapsed < H616_CE_TIMEOUT_US; elapsed++)
    {
        status = h616_ce_readl(ce, H616_CE_ISR);
        if (status & RT_BIT(flow))
        {
            h616_ce_writel(ce, RT_BIT(flow), H616_CE_ISR);
            status = (h616_ce_readl(ce, H616_CE_ESR) >> (flow * 8)) & 0xff;
            return status ? -RT_EIO : RT_EOK;
        }
        rt_hw_us_delay(1);
    }
    return -RT_ETIMEOUT;
}

static rt_err_t h616_ce_aes_mode(hwcrypto_type type, rt_uint32_t *mode)
{
    switch (type)
    {
    case HWCRYPTO_TYPE_AES_ECB:
        *mode = H616_CE_AES_ECB;
        return RT_EOK;
    case HWCRYPTO_TYPE_AES_CBC:
        *mode = H616_CE_AES_CBC;
        return RT_EOK;
    default:
        return -RT_ENOSYS;
    }
}

static rt_err_t h616_ce_aes_crypt(struct hwcrypto_symmetric *symmetric,
                                  struct hwcrypto_symmetric_info *info)
{
    struct h616_ce *ce = to_h616_ce(symmetric->parent.device);
    struct h616_ce_task *task = ce->task;
    rt_ubase_t input_dma;
    rt_ubase_t output_dma;
    rt_ubase_t key_dma;
    rt_ubase_t iv_dma;
    rt_uint32_t mode;
    rt_uint32_t key_size;
    rt_uint32_t input_address;
    rt_uint32_t output_address;
    rt_uint32_t key_address;
    rt_uint32_t iv_address = 0;
    rt_err_t err;

    if (!info->length || info->length % H616_CE_BLOCK_SIZE ||
        !info->in || !info->out || (symmetric->key_bitlen != 128 && symmetric->key_bitlen != 192 && symmetric->key_bitlen != 256))
    {
        return -RT_EINVAL;
    }
    if ((err = h616_ce_aes_mode(symmetric->parent.type, &mode)))
    {
        return err;
    }
    if (mode == H616_CE_AES_CBC && symmetric->iv_len != H616_CE_BLOCK_SIZE)
    {
        return -RT_EINVAL;
    }
    input_dma = (rt_ubase_t)rt_kmem_v2p((void *)info->in);
    output_dma = (rt_ubase_t)rt_kmem_v2p(info->out);
    key_dma = (rt_ubase_t)rt_kmem_v2p(symmetric->key);
    iv_dma = (rt_ubase_t)rt_kmem_v2p(symmetric->iv);
    if ((err = h616_ce_word_address(input_dma, &input_address)) ||
        (err = h616_ce_word_address(output_dma, &output_address)) ||
        (err = h616_ce_word_address(key_dma, &key_address)))
    {
        return err;
    }
    if (mode == H616_CE_AES_CBC &&
        (err = h616_ce_word_address(iv_dma, &iv_address)))
    {
        return err;
    }

    key_size = symmetric->key_bitlen == 128 ? H616_CE_AES_128 : symmetric->key_bitlen == 192 ? H616_CE_AES_192
                                                                                             : H616_CE_AES_256;
    rt_mutex_take(&ce->lock, RT_WAITING_FOREVER);
    rt_memset(task, 0, sizeof(*task));
    task->id = H616_CE_FLOW_AES;
    task->common_ctl = H616_CE_AES | H616_CE_COMM_INTERRUPT |
                       (info->mode == HWCRYPTO_MODE_DECRYPT ? H616_CE_COMM_DECRYPT : 0);
    task->symmetric_ctl = mode | key_size;
    task->data_length = info->length;
    task->source[0].address = input_address;
    task->source[0].length = info->length / 4;
    task->destination[0].address = output_address;
    task->destination[0].length = info->length / 4;
    task->key = key_address;
    if (mode == H616_CE_AES_CBC)
    {
        task->iv = iv_address;
    }
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)info->in, info->length);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, symmetric->key,
                         symmetric->key_bitlen / 8);
    if (mode == H616_CE_AES_CBC)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, symmetric->iv, H616_CE_BLOCK_SIZE);
    }
    err = h616_ce_run_task(ce, H616_CE_FLOW_AES);
    if (!err)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, info->out, info->length);
    }
    rt_mutex_release(&ce->lock);
    return err;
}

static rt_uint32_t h616_ce_rng_update(struct hwcrypto_rng *rng)
{
    struct h616_ce *ce = to_h616_ce(rng->parent.device);
    struct h616_ce_task *task = ce->task;
    rt_uint32_t result = 0;
    rt_uint32_t address;

    if (h616_ce_word_address(ce->trng_dma, &address))
    {
        return 0;
    }
    rt_mutex_take(&ce->lock, RT_WAITING_FOREVER);
    rt_memset(task, 0, sizeof(*task));
    task->id = H616_CE_FLOW_TRNG;
    task->common_ctl = H616_CE_TRNG_V2 | H616_CE_COMM_INTERRUPT;
    task->data_length = H616_CE_TRNG_SIZE;
    task->destination[0].address = address;
    task->destination[0].length = H616_CE_TRNG_SIZE / 4;
    if (!h616_ce_run_task(ce, H616_CE_FLOW_TRNG))
    {
        rt_memcpy(&result, ce->trng, sizeof(result));
    }
    rt_mutex_release(&ce->lock);
    return result;
}

static const struct hwcrypto_symmetric_ops h616_ce_aes_ops = {
    .crypt = h616_ce_aes_crypt,
};

static const struct hwcrypto_rng_ops h616_ce_rng_ops = {
    .update = h616_ce_rng_update,
};

static rt_err_t h616_ce_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_uint32_t mode;

    if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_AES)
    {
        if (h616_ce_aes_mode(ctx->type, &mode))
        {
            return -RT_ENOSYS;
        }
        ((struct hwcrypto_symmetric *)ctx)->ops = &h616_ce_aes_ops;
        return RT_EOK;
    }
    if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_RNG)
    {
        ((struct hwcrypto_rng *)ctx)->ops = &h616_ce_rng_ops;
        return RT_EOK;
    }
    return -RT_ENOSYS;
}

static void h616_ce_destroy(struct rt_hwcrypto_ctx *ctx)
{
    RT_UNUSED(ctx);
}

static rt_err_t h616_ce_copy(struct rt_hwcrypto_ctx *destination,
                             const struct rt_hwcrypto_ctx *source)
{
    RT_UNUSED(destination);
    RT_UNUSED(source);
    return RT_EOK;
}

static void h616_ce_reset(struct rt_hwcrypto_ctx *ctx)
{
    RT_UNUSED(ctx);
}

static const struct rt_hwcrypto_ops h616_ce_ops = {
    .create = h616_ce_create,
    .destroy = h616_ce_destroy,
    .copy = h616_ce_copy,
    .reset = h616_ce_reset,
};

static void h616_ce_release(struct h616_ce *ce)
{
    if (!ce)
    {
        return;
    }
    if (ce->trng)
    {
        rt_dma_free_coherent(ce->dev, H616_CE_TRNG_SIZE,
                             ce->trng, ce->trng_dma);
    }
    if (ce->task)
    {
        rt_dma_free_coherent(ce->dev, sizeof(*ce->task),
                             ce->task, ce->task_dma);
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

static rt_err_t h616_ce_probe(struct rt_platform_device *pdev)
{
    struct h616_ce *ce = rt_calloc(1, sizeof(*ce));
    struct rt_device *dev = &pdev->parent;
    rt_err_t err;

    if (!ce)
    {
        return -RT_ENOMEM;
    }
    ce->dev = dev;
    rt_mutex_init(&ce->lock, "h616-ce", RT_IPC_FLAG_PRIO);
    ce->base = rt_dm_dev_iomap(dev, 0);
    ce->clks = rt_clk_get_array(dev);
    ce->reset = rt_reset_control_get_by_index(dev, 0);
    if (!ce->base || rt_is_err_or_null(ce->clks) || rt_is_err_or_null(ce->reset))
    {
        err = -RT_EIO;
        goto fail;
    }
    if ((err = rt_clk_array_prepare_enable(ce->clks)) ||
        (err = rt_reset_control_deassert(ce->reset)))
    {
        goto fail;
    }
    ce->clks_enabled = RT_TRUE;
    ce->task = rt_dma_alloc_coherent(dev, sizeof(*ce->task), &ce->task_dma);
    ce->trng = rt_dma_alloc_coherent(dev, H616_CE_TRNG_SIZE, &ce->trng_dma);
    if (!ce->task || !ce->trng)
    {
        err = -RT_ENOMEM;
        goto fail;
    }
    ce->parent.ops = &h616_ce_ops;
    ce->parent.user_data = ce;
    if ((err = rt_hwcrypto_register(&ce->parent, "h616-ce")))
    {
        goto fail;
    }
    dev->user_data = ce;
    return RT_EOK;

fail:
    h616_ce_release(ce);
    return err;
}

static rt_err_t h616_ce_remove(struct rt_platform_device *pdev)
{
    struct h616_ce *ce = pdev->parent.user_data;

    if (ce)
    {
        h616_ce_release(ce);
    }
    return RT_EOK;
}

static const struct rt_ofw_node_id h616_ce_ofw_ids[] = {
    { .compatible = "allwinner,sun50i-h616-crypto" },
    {}
};

static struct rt_platform_driver h616_ce_driver = {
    .name = "sun50i-h616-ce",
    .ids = h616_ce_ofw_ids,
    .probe = h616_ce_probe,
    .remove = h616_ce_remove,
};
RT_PLATFORM_DRIVER_EXPORT(h616_ce_driver);
