/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include "macb.h"

#define DBG_TAG "eth.macb.pci"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_ubase_t gem_clk_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    (void)cell;
    (void)parent_rate;
    return 50000000;
}

static struct rt_clk_ops gem_clk_ops =
{
    .recalc_rate = gem_clk_recalc_rate,
};

static struct rt_clk_cell *gem_cells[] =
{
    &(struct rt_clk_cell)
    {
        .cell.name = "macb_pci_pclk",
        .cell.ops = &gem_clk_ops,
    },
    &(struct rt_clk_cell)
    {
        .cell.name = "macb_pci_hclk",
        .cell.ops = &gem_clk_ops,
    },
};

static rt_err_t macb_pci_clk_init(void)
{
    rt_err_t err;
    static struct rt_clk_node *clk_np = RT_NULL;

    if (clk_np)
    {
        return RT_EOK;
    }

    if (!(clk_np = rt_calloc(1, sizeof(*clk_np))))
    {
        return -RT_ENOMEM;
    }

    clk_np->cells = gem_cells;
    clk_np->cells_nr = RT_ARRAY_SIZE(gem_cells);

    if ((err = rt_clk_register(clk_np)))
    {
        rt_free(clk_np);
    }

    return err;
}

static rt_err_t macb_pci_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct macb_eth *eth;

    if ((err = macb_pci_clk_init()))
    {
        return err;
    }

    if (!(eth = rt_calloc(1, sizeof(*eth))))
    {
        return -RT_ENOMEM;
    }

    rt_pci_set_master(pdev);

    eth->dev = &pdev->parent;

    eth->regs = rt_pci_iomap(pdev, 0);
    if (!eth->regs)
    {
        err = -RT_EIO;
        goto _free_eth;
    }

    eth->irq = pdev->irq;
    rt_pci_irq_unmask(pdev);

    eth->pclk = rt_clk_get_by_name(eth->dev, "macb_pci_pclk");

    if (rt_is_err_or_null(eth->pclk))
    {
        err = eth->pclk ? rt_ptr_err(eth->pclk) : -RT_EIO;
        goto _unmap;
    }

    eth->hclk = rt_clk_get_by_name(eth->dev, "macb_pci_hclk");

    if (rt_is_err_or_null(eth->hclk))
    {
        err = eth->hclk ? rt_ptr_err(eth->hclk) : -RT_EIO;
        goto _put_pclk;
    }

    ethernet_random_addr(&eth->parent, eth->mac);

    if ((err = macb_eth_hw_init(eth)))
    {
        goto _put_clks;
    }

    pdev->parent.user_data = eth;

    if ((err = macb_eth_common_probe(eth)))
    {
        macb_eth_common_remove(eth);
        pdev->parent.user_data = RT_NULL;
        goto _put_clks;
    }

    return RT_EOK;

_put_clks:
    rt_clk_put(eth->hclk);
_put_pclk:
    rt_clk_put(eth->pclk);
_unmap:
    rt_iounmap(eth->regs);
    rt_pci_irq_mask(pdev);
_free_eth:
    rt_free(eth);

    return err;
}

static rt_err_t macb_pci_remove(struct rt_pci_device *pdev)
{
    struct macb_eth *eth = pdev->parent.user_data;

    macb_eth_common_remove(eth);

    /* INTx is shared, don't mask all */
    rt_hw_interrupt_umask(pdev->irq);
    rt_pci_irq_mask(pdev);
    rt_pci_clear_master(pdev);

    rt_iounmap(eth->regs);
    rt_clk_put(eth->hclk);
    rt_clk_put(eth->pclk);

    rt_free(eth);

    return RT_EOK;
}

static const struct rt_pci_device_id macb_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_CDNS, 0xe007), },
    { /* sentinel */ }
};

static struct rt_pci_driver macb_pci_driver =
{
    .name = "macb-pci",

    .ids = macb_pci_ids,
    .probe = macb_pci_probe,
    .remove = macb_pci_remove,
};
RT_PCI_DRIVER_EXPORT(macb_pci_driver);
