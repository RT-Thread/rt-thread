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

#define DBG_TAG "nvmem.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct spacemit_efuse
{
    struct rt_nvmem_device parent;

    void *base;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    rt_uint8_t *efuse_data;
    rt_uint32_t size;
};

#define raw_to_spacemit_efuse(raw) rt_container_of(raw, struct spacemit_efuse, parent)

static rt_err_t spacemit_k1_efuse_read(struct spacemit_efuse *efuse)
{
    rt_err_t err;

    if ((err = rt_clk_prepare_enable(efuse->clk)))
    {
        LOG_E("Failed to prepare/enable efuse clk");
        return err;
    }

    if ((err = rt_reset_control_deassert(efuse->rstc)))
    {
        LOG_E("Failed to deassert efuse");
        rt_clk_disable_unprepare(efuse->clk);
        return err;
    }

    /*
     * efuse data has been load into register by uboot already,
     * just get efuse data from register
    */
    for (int i = 0; i < efuse->size; i += 4)
    {
        *(rt_uint32_t *)(efuse->efuse_data + i) = *(rt_uint32_t *)(efuse->base + i);
    }

    /* RESET_AES is shared with the crypto and RNG blocks. */
    rt_clk_disable_unprepare(efuse->clk);

    return err;
}

static rt_ssize_t spacemit_efuse_read(struct rt_nvmem_device *ndev, int offset,
        void *val, rt_size_t bytes)
{
    struct spacemit_efuse *efuse = raw_to_spacemit_efuse(ndev);

    rt_memcpy(val, &efuse->efuse_data[offset], bytes);

    return bytes;
}

static rt_err_t spacemit_efuse_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t address, size;
    struct spacemit_efuse *efuse;
    struct rt_nvmem_device *nvmem;
    struct rt_device *dev = &pdev->parent;
    rt_err_t (*efuse_read)(struct spacemit_efuse *efuse);

    if (!(efuse_read = pdev->id->data))
    {
        return -RT_EINVAL;
    }

    if (!(efuse = rt_calloc(1, sizeof(*efuse))))
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_dm_dev_get_address(dev, 0, &address, &size)))
    {
        goto _fail;
    }

    efuse->base = rt_ioremap((void *)address, size);
    if (!efuse->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    efuse->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(efuse->clk))
    {
        err = rt_ptr_err(efuse->clk);
        goto _fail;
    }

    efuse->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(efuse->rstc))
    {
        err = rt_ptr_err(efuse->rstc);
        goto _fail;
    }

    efuse->size = rt_roundup(size, sizeof(rt_uint32_t));
    efuse->efuse_data = rt_calloc(1, efuse->size);
    if (!efuse->efuse_data)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if ((err = efuse_read(efuse)))
    {
        goto _fail;
    }

    nvmem = &efuse->parent;
    nvmem->parent.ofw_node = dev->ofw_node;
    nvmem->reg_read = spacemit_efuse_read,
    nvmem->size = size;
    nvmem->read_only = RT_TRUE;
    nvmem->stride = 1;
    nvmem->word_size = 1;

    if ((err = rt_nvmem_device_register(nvmem)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (efuse->base)
    {
        rt_iounmap(efuse->base);
    }

    if (!rt_is_err_or_null(efuse->clk))
    {
        rt_clk_put(efuse->clk);
    }

    if (!rt_is_err_or_null(efuse->rstc))
    {
        rt_reset_control_put(efuse->rstc);
    }

    if (efuse->efuse_data)
    {
        rt_free(efuse->efuse_data);
    }

    rt_free(efuse);

    return err;
}

static const struct rt_ofw_node_id spacemit_efuse_ofw_ids[] =
{
    { .compatible = "spacemit,k1-efuse", .data = &spacemit_k1_efuse_read },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_efuse_driver =
{
    .name = "nvmem-spacemit-efuse",
    .ids = spacemit_efuse_ofw_ids,

    .probe = spacemit_efuse_probe,
};

RT_PLATFORM_DRIVER_EXPORT(spacemit_efuse_driver);
