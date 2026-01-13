/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "hwspinlock_dm.h"

#define HWSPINLOCK_NUMBER           64
#define HWSPINLOCK_STATUS_OFFSET(x) (0x4 * (x))
#define HWSPINLOCK_OWNER_ID         0x1

struct rockchip_hwspinlock
{
    struct rt_hwspinlock_bank parent;

    void *regs;
};

static rt_err_t rockchip_hwspinlock_trylock(struct rt_hwspinlock *hwlock)
{
    void *lock_regs = hwlock->priv;

    HWREG32(lock_regs) = HWSPINLOCK_OWNER_ID;

    /*
     * Get only first 4bits and compare to HWSPINLOCK_OWNER_ID:
     *  when 4bits is 0, 4bits can be written with new value.
     *  when 4bits is not 0, 4bits cannot be written.
     *  when write data is 0x0000, 4bits clean to 0.
     */

    return ((HWREG32(lock_regs) & 0xf) == HWSPINLOCK_OWNER_ID);
}

static void rockchip_hwspinlock_unlock(struct rt_hwspinlock *hwlock)
{
    void *lock_regs = hwlock->priv;

    HWREG32(lock_regs) = 0;
}

static const struct rt_hwspinlock_ops rk_hwspinlock_ops =
{
    .trylock = rockchip_hwspinlock_trylock,
    .unlock = rockchip_hwspinlock_unlock,
};

static rt_err_t rockchip_hwspinlock_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_hwspinlock *hwlock;
    struct rt_hwspinlock_bank *bank;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_hwspinlock *rk_hwspinlock;

    rk_hwspinlock = hwspinlock_bank_alloc(rk_hwspinlock, HWSPINLOCK_NUMBER);

    if (!rk_hwspinlock)
    {
        return -RT_ENOMEM;
    }

    rk_hwspinlock->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_hwspinlock->regs)
    {
        err = -RT_EIO;

        goto _fail;
    }

    bank = &rk_hwspinlock->parent;
    hwlock = &bank->locks[0];

    for (int i = 0; i < HWSPINLOCK_NUMBER; ++i, ++hwlock)
    {
        hwlock->priv = rk_hwspinlock->regs + HWSPINLOCK_STATUS_OFFSET(i);
    }

    bank->dev = dev;
    bank->ops = &rk_hwspinlock_ops;
    bank->locks_nr = HWSPINLOCK_NUMBER;

    if ((err = rt_hwspinlock_bank_register(bank)))
    {
        goto _fail;
    }

    dev->user_data = rk_hwspinlock;

    return RT_EOK;

_fail:
    if (rk_hwspinlock->regs)
    {
        rt_iounmap(rk_hwspinlock->regs);
    }
    rt_free(rk_hwspinlock);

    return err;
}

static rt_err_t rockchip_hwspinlock_remove(struct rt_platform_device *pdev)
{
    struct rockchip_hwspinlock *rk_hwspinlock = pdev->parent.user_data;

    rt_hwspinlock_bank_unregister(&rk_hwspinlock->parent);

    rt_iounmap(rk_hwspinlock->regs);

    rt_free(rk_hwspinlock);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_hwspinlock_ofw_ids[] =
{
    { .compatible = "rockchip,hwspinlock" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_hwspinlock_driver =
{
    .name = "hwspinlock-rockchip",
    .ids = rockchip_hwspinlock_ofw_ids,

    .probe = rockchip_hwspinlock_probe,
    .remove = rockchip_hwspinlock_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_hwspinlock_driver);
