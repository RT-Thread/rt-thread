/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "nvmem.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_SID_PRCTL               0x00
#define SUNXI_SID_PR_ADDR             0x04
#define SUNXI_SID_RDKEY               0x0c

#define SUNXI_SID_READ_START          RT_BIT(1)
#define SUNXI_SID_READ_LOCK           0xadbf0000
#define SUNXI_SID_READ_TIMEOUT        1000

struct sunxi_sid
{
    struct rt_nvmem_device parent;

    void *base;
    struct rt_spinlock lock;
};

#define to_sunxi_sid(raw) rt_container_of(raw, struct sunxi_sid, parent)

static rt_err_t sunxi_sid_read_word(struct sunxi_sid *sid, rt_uint32_t offset,
        rt_uint32_t *value)
{
    rt_ubase_t level;
    int retry;

    level = rt_spin_lock_irqsave(&sid->lock);
    HWREG32(sid->base + SUNXI_SID_PR_ADDR) = offset / sizeof(*value);
    HWREG32(sid->base + SUNXI_SID_PRCTL) = SUNXI_SID_READ_LOCK |
            SUNXI_SID_READ_START;

    for (retry = 0; retry < SUNXI_SID_READ_TIMEOUT; ++retry)
    {
        if (!(HWREG32(sid->base + SUNXI_SID_PRCTL) & SUNXI_SID_READ_START))
        {
            *value = HWREG32(sid->base + SUNXI_SID_RDKEY);
            rt_spin_unlock_irqrestore(&sid->lock, level);
            return RT_EOK;
        }
        rt_hw_us_delay(1);
    }

    HWREG32(sid->base + SUNXI_SID_PRCTL) = 0;
    rt_spin_unlock_irqrestore(&sid->lock, level);
    return -RT_ETIMEOUT;
}

static rt_ssize_t sunxi_sid_read(struct rt_nvmem_device *ndev, int offset,
        void *buffer, rt_size_t bytes)
{
    rt_size_t copy;
    rt_uint8_t *out = buffer;
    struct sunxi_sid *sid = to_sunxi_sid(ndev);

    if (offset < 0 || (rt_size_t)offset > ndev->size ||
            bytes > ndev->size - offset)
    {
        return -RT_EINVAL;
    }

    while (bytes)
    {
        rt_uint32_t value;
        rt_size_t in_word = offset & (sizeof(value) - 1);
        rt_err_t err = sunxi_sid_read_word(sid, offset - in_word, &value);

        if (err)
        {
            return err;
        }

        copy = sizeof(value) - in_word;
        if (copy > bytes)
        {
            copy = bytes;
        }
        rt_memcpy(out, (rt_uint8_t *)&value + in_word, copy);
        out += copy;
        offset += copy;
        bytes -= copy;
    }

    return out - (rt_uint8_t *)buffer;
}

static void sunxi_sid_release(struct sunxi_sid *sid)
{
    if (sid->base)
    {
        rt_iounmap(sid->base);
    }
    rt_free(sid);
}

static rt_err_t sunxi_sid_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_sid *sid = rt_calloc(1, sizeof(*sid));

    if (!sid)
    {
        return -RT_ENOMEM;
    }

    sid->base = rt_dm_dev_iomap(dev, 0);
    if (!sid->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rt_spin_lock_init(&sid->lock);
    sid->parent.parent.ofw_node = dev->ofw_node;
    sid->parent.reg_read = sunxi_sid_read;
    sid->parent.size = 64;
    sid->parent.stride = sizeof(rt_uint32_t);
    sid->parent.word_size = sizeof(rt_uint32_t);
    sid->parent.read_only = RT_TRUE;

    if ((err = rt_nvmem_device_register(&sid->parent)))
    {
        goto _fail;
    }

    dev->user_data = sid;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, sid);
    return RT_EOK;

_fail:
    sunxi_sid_release(sid);
    return err;
}

static rt_err_t sunxi_sid_remove(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_sid *sid = dev->user_data;

    err = rt_nvmem_device_unregister(&sid->parent);
    if (err)
    {
        return err;
    }

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);
    sunxi_sid_release(sid);
    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_sid_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-sid" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_sid_driver =
{
    .name = "nvmem-sunxi-sid",
    .ids = sunxi_sid_ofw_ids,
    .probe = sunxi_sid_probe,
    .remove = sunxi_sid_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_sid_driver);
