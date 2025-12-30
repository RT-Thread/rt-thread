/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#define SDHCI_REG_BAR 0

#include "../dev_sdio_dm.h"

struct pci_sdhci_host
{
    struct rt_sdhci_host parent;
};

static const struct rt_sdhci_ops pci_sdhci_ops =
{
    .set_clock = rt_sdhci_set_clock,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = rt_sdhci_reset,
};

static rt_err_t pci_sdhci_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct rt_sdhci_host *host;
    struct pci_sdhci_host *pci_host;

    host = rt_sdhci_alloc_host(&pdev->parent, sizeof(struct pci_sdhci_host));

    if (!host)
    {
        return -RT_ENOMEM;
    }
    pci_host = rt_container_of(host, struct pci_sdhci_host, parent);

    host->ioaddr = rt_pci_iomap(pdev, SDHCI_REG_BAR);

    if (!host->ioaddr)
    {
        err = -RT_EIO;
        goto _fail;
    }

    host->irq = pdev->irq;
    host->ops = &pci_sdhci_ops;

    rt_pci_irq_unmask(pdev);
    rt_pci_set_master(pdev);

    if ((err = rt_sdhci_set_and_add_host(host)))
    {
        goto _fail;
    }

    pdev->parent.user_data = pci_host;

    return RT_EOK;

_fail:
    if (host->ioaddr)
    {
        rt_iounmap(host->ioaddr);
    }

    rt_sdhci_free_host(host);

    return err;
}

static rt_err_t pci_sdhci_remove(struct rt_pci_device *pdev)
{
    rt_bool_t dead;
    struct rt_sdhci_host *host;
    struct pci_sdhci_host *pci_host = pdev->parent.user_data;

    host = &pci_host->parent;

    /* INTx is shared, don't mask all */
    rt_hw_interrupt_umask(pdev->irq);
    rt_pci_irq_mask(pdev);
    rt_pci_clear_master(pdev);

    dead = (HWREG32(host->ioaddr + RT_SDHCI_INT_STATUS) == 0xffffffff);

    rt_sdhci_uninit_host(host, dead);

    rt_iounmap(host->ioaddr);
    rt_sdhci_free_host(host);

    return RT_EOK;
}

static const struct rt_pci_device_id pci_sdhci_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0007), },
    { RT_PCI_DEVICE_CLASS(PCIS_SYSTEM_SDHCI, ~0) },
    { /* sentinel */ }
};

static struct rt_pci_driver pci_sdhci_driver =
{
    .name = "sdhci-pci",

    .ids = pci_sdhci_pci_ids,
    .probe = pci_sdhci_probe,
    .remove = pci_sdhci_remove,
};
RT_PCI_DRIVER_EXPORT(pci_sdhci_driver);
