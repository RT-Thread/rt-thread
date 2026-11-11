/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "phy.mdio.bcm-unimac"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MDIO_CMD            0x00
#define  MDIO_START_BUSY    (1 << 29)
#define  MDIO_READ_FAIL     (1 << 28)
#define  MDIO_RD            (2 << 26)
#define  MDIO_WR            (1 << 26)
#define  MDIO_PMD_SHIFT     21
#define  MDIO_PMD_MASK      0x1f
#define  MDIO_REG_SHIFT     16
#define  MDIO_REG_MASK      0x1f

#define MDIO_CFG            0x04
#define  MDIO_C22           (1 << 0)
#define  MDIO_C45           0
#define  MDIO_CLK_DIV_SHIFT 4
#define  MDIO_CLK_DIV_MASK  0x3f
#define  MDIO_SUPP_PREAMBLE (1 << 12)

struct unimac_mdio
{
    struct rt_device *dev;
    struct mii_bus *mdio;

    void *base;

    rt_uint32_t clk_freq;
    struct rt_clk *clk;
};

rt_inline void unimac_mdio_start(struct unimac_mdio *umdio)
{
    rt_uint32_t reg;

    reg = HWREG32(umdio->base + MDIO_CMD);
    reg |= MDIO_START_BUSY;
    HWREG32(umdio->base + MDIO_CMD) = reg;
}

static rt_err_t unimac_mdio_poll(struct unimac_mdio *umdio)
{
    rt_uint32_t timeout = 1000;

    do {
        if (!(HWREG32(umdio->base + MDIO_CMD) & MDIO_START_BUSY))
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1500);
    } while (--timeout);

    return -RT_ETIMEOUT;
}

static int unimac_mdio_read(struct mii_bus *bus, int addr, int devad, int reg)
{
    int err;
    rt_uint32_t cmd;
    struct unimac_mdio *umdio = bus->priv;

    cmd = MDIO_RD | (addr << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT);
    HWREG32(umdio->base + MDIO_CMD) = cmd;

    unimac_mdio_start(umdio);

    if ((err = (int)unimac_mdio_poll(umdio)))
    {
        return err;
    }

    cmd = HWREG32(umdio->base + MDIO_CMD);

    return cmd & 0xffff;
}

static int unimac_mdio_write(struct mii_bus *bus, int addr, int devad, int reg, rt_uint16_t val)
{
    rt_uint32_t cmd;
    struct unimac_mdio *umdio = bus->priv;

    cmd = MDIO_WR | (addr << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT) | (0xffff & val);
    HWREG32(umdio->base + MDIO_CMD) = cmd;

    unimac_mdio_start(umdio);

    return (int)unimac_mdio_poll(umdio);
}

static int unimac_mdio_reset(struct mii_bus *bus)
{
    rt_uint32_t read_mask = 0, addr;
    struct unimac_mdio *umdio = bus->priv;
    struct rt_ofw_node *np = umdio->dev->ofw_node, *child;

    if (!np)
    {
        read_mask = ~bus->phy_mask;
    }
    else
    {
        rt_ofw_foreach_available_child_node(np, child)
        {
            if (!rt_ofw_prop_read_u32(child, "reg", &addr) && addr < RT_PHY_MAX)
            {
                read_mask |= 1 << addr;
            }
        }
    }

    for (addr = 0; addr < RT_PHY_MAX; ++addr)
    {
        if (read_mask & (1 << addr))
        {
            unimac_mdio_read(bus, addr, 0, RT_MII_BMSR);
        }
    }

    return 0;
}

#ifdef RT_USING_PM
static rt_err_t unimac_mdio_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    struct unimac_mdio *umdio = device->user_data;

    rt_clk_disable_unprepare(umdio->clk);

    return RT_EOK;
}

static void unimac_mdio_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    struct unimac_mdio *umdio = device->user_data;

    rt_clk_prepare_enable(umdio->clk);
}

static const struct rt_device_pm_ops unimac_mdio_pm_ops =
{
    .suspend = unimac_mdio_pm_suspend,
    .resume = unimac_mdio_pm_resume,
};
#endif /* RT_USING_PM */

static rt_err_t unimac_mdio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t base, size, mac_base;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *pnp;
    struct unimac_mdio *umdio = rt_calloc(1, sizeof(*umdio));

    if (!umdio)
    {
        return -RT_ENOMEM;
    }
    umdio->dev = dev;

    pnp = rt_ofw_get_parent(np);
    rt_ofw_get_address(pnp, 0, &mac_base, RT_NULL);
    rt_ofw_node_put(pnp);
    rt_ofw_get_address(np, 0, &base, &size);

    umdio->base = rt_ioremap((void *)(mac_base + base), size);

    if (!umdio->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    umdio->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(umdio->clk))
    {
        err = rt_ptr_err(umdio->clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(umdio->clk)))
    {
        goto _fail;
    }

    rt_dm_dev_prop_read_u32(dev, "clock-frequency", &umdio->clk_freq);

    if (umdio->clk_freq)
    {
        rt_uint32_t reg, div;
        rt_ubase_t rate = 250000000;

        if (umdio->clk)
        {
            rate = rt_clk_get_rate(umdio->clk);
        }

        div = (rate / (2 * umdio->clk_freq)) - 1;

        /*
         * The MDIO clock is the reference clock (typically 250Mhz) divided by
         * 2 x (MDIO_CLK_DIV + 1)
         */
        reg = HWREG32(umdio->base + MDIO_CFG);
        reg &= ~(MDIO_CLK_DIV_MASK << MDIO_CLK_DIV_SHIFT);
        reg |= div << MDIO_CLK_DIV_SHIFT;
        HWREG32(umdio->base + MDIO_CFG) = reg;
    }

    umdio->mdio = rt_mdio_alloc();

    if (!umdio->mdio)
    {
        err = -RT_ENOMEM;
        goto _free_clk;
    }

    rt_sprintf(umdio->mdio->name, "unimac MII bus");
    umdio->mdio->priv = umdio;
    umdio->mdio->read = unimac_mdio_read;
    umdio->mdio->write = unimac_mdio_write;
    umdio->mdio->reset = unimac_mdio_reset;

    dev->user_data = umdio;

    if ((err = rt_mdio_register(umdio->mdio)))
    {
        goto _free_clk;
    }

#ifdef RT_USING_PM
    rt_pm_device_register(dev, &unimac_mdio_pm_ops);
#endif

    return RT_EOK;

_free_clk:
    if (!rt_is_err_or_null(umdio->clk))
    {
        rt_clk_disable_unprepare(umdio->clk);
    }

_fail:
    if (umdio->base)
    {
        rt_iounmap(umdio->base);
    }

    if (umdio->mdio)
    {
        rt_free(umdio->mdio);
    }

    rt_free(umdio);

    return err;
}

static rt_err_t unimac_mdio_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct unimac_mdio *umdio = dev->user_data;

#ifdef RT_USING_PM
    rt_pm_device_unregister(dev);
#endif

    rt_mdio_unregister(umdio->mdio);

    rt_clk_disable_unprepare(umdio->clk);
    rt_clk_put(umdio->clk);

    rt_free(umdio->mdio);
    rt_free(umdio);

    return RT_EOK;
}

static const struct rt_ofw_node_id unimac_mdio_ofw_ids[] =
{
    { .compatible = "brcm,asp-v2.1-mdio", },
    { .compatible = "brcm,asp-v2.0-mdio", },
    { .compatible = "brcm,bcm6846-mdio", },
    { .compatible = "brcm,genet-mdio-v5", },
    { .compatible = "brcm,genet-mdio-v4", },
    { .compatible = "brcm,genet-mdio-v3", },
    { .compatible = "brcm,genet-mdio-v2", },
    { .compatible = "brcm,genet-mdio-v1", },
    { .compatible = "brcm,unimac-mdio", },
    { /* sentinel */ }
};

static struct rt_platform_driver unimac_mdio_driver =
{
    .name = "unimac-mdio",
    .ids = unimac_mdio_ofw_ids,

    .probe = unimac_mdio_probe,
    .remove = unimac_mdio_remove,
};

static int unimac_mdio_drv_register(void)
{
    rt_platform_driver_register(&unimac_mdio_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(unimac_mdio_drv_register);
