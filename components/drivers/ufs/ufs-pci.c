/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define UFS_REG_BAR 0

struct pci_ufs_quirk
{
    const struct rt_ufs_ops *ops;
};

struct pci_ufs_host
{
    struct rt_ufs_host parent;
    const struct pci_ufs_quirk *quirk;
};

static const struct rt_ufs_ops pci_ufs_std_ops =
{
};

static rt_err_t pci_ufs_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct rt_ufs_host *ufs;
    struct pci_ufs_host *pci_ufs = rt_calloc(1, sizeof(*pci_ufs));
    const struct pci_ufs_quirk *quirk = pdev->id->data;

    if (!pci_ufs)
    {
        return -RT_ENOMEM;
    }

    pci_ufs->quirk = quirk;
    ufs = &pci_ufs->parent;
    ufs->parent.dev = &pdev->parent;
    ufs->regs = rt_pci_iomap(pdev, UFS_REG_BAR);
    ufs->irq = pdev->irq;

    if (!ufs->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ufs->ops = quirk ? quirk->ops : &pci_ufs_std_ops;

    rt_pci_irq_unmask(pdev);
    rt_pci_set_master(pdev);

    if ((err = rt_ufs_host_register(ufs)))
    {
        goto _fail;
    }

    pdev->parent.user_data = pci_ufs;

    return RT_EOK;

_fail:
    rt_free(pci_ufs);

    return err;
}

static rt_err_t pci_ufs_remove(struct rt_pci_device *pdev)
{
    struct rt_ufs_host *ufs;
    struct pci_ufs_host *pci_ufs = pdev->parent.user_data;

    ufs = &pci_ufs->parent;

    rt_ufs_host_unregister(ufs);

    /* INTx is shared, don't mask all */
    rt_hw_interrupt_umask(pdev->irq);
    rt_pci_irq_mask(pdev);
    rt_pci_clear_master(pdev);

    rt_iounmap(ufs->regs);
    rt_free(pci_ufs);

    return RT_EOK;
}

static rt_err_t pci_ufs_shutdown(struct rt_pci_device *pdev)
{
    return pci_ufs_remove(pdev);
}

static const struct rt_pci_device_id pci_ufs_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0013), },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_SAMSUNG, 0xc00c), },
    { /* sentinel */ }
};

static struct rt_pci_driver pci_ufs_driver =
{
    .name = "ufs-pci",

    .ids = pci_ufs_ids,
    .probe = pci_ufs_probe,
    .remove = pci_ufs_remove,
    .shutdown = pci_ufs_shutdown,
};
RT_PCI_DRIVER_EXPORT(pci_ufs_driver);
