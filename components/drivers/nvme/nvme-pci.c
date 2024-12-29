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

#define NVME_REG_BAR 0

struct pci_nvme_quirk
{
    const struct rt_nvme_ops *ops;
};

struct pci_nvme_controller
{
    struct rt_nvme_controller parent;
    const struct pci_nvme_quirk *quirk;

    rt_bool_t is_msi;
    struct rt_pci_msix_entry msix_entries[RT_USING_NVME_QUEUE];
};

static const struct rt_nvme_ops pci_nvme_std_ops =
{
    .name = "PCI",
};

static rt_err_t pci_nvme_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    rt_ssize_t msi_nr;
    struct rt_nvme_controller *nvme;
    struct pci_nvme_controller *pci_nvme = rt_calloc(1, sizeof(*pci_nvme));
    const struct pci_nvme_quirk *quirk = pdev->id->data;

    if (!pci_nvme)
    {
        return -RT_ENOMEM;
    }

    pci_nvme->quirk = quirk;
    nvme = &pci_nvme->parent;
    nvme->dev = &pdev->parent;
    nvme->regs = rt_pci_iomap(pdev, NVME_REG_BAR);

    if (!nvme->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    nvme->ops = quirk && quirk->ops ? quirk->ops : &pci_nvme_std_ops;

    if ((msi_nr = rt_pci_msix_vector_count(pdev)) <= 0)
    {
        msi_nr = rt_pci_msi_vector_count(pdev);
    }
    if (msi_nr > 0)
    {
        nvme->irqs_nr = RT_ARRAY_SIZE(pci_nvme->msix_entries);
        nvme->irqs_nr = rt_min_t(rt_size_t, msi_nr, nvme->irqs_nr);
    }

    if (nvme->irqs_nr > 0)
    {
        rt_pci_msix_entry_index_linear(pci_nvme->msix_entries, nvme->irqs_nr);

        if (rt_pci_msix_enable(pdev, pci_nvme->msix_entries, nvme->irqs_nr) > 0)
        {
            pci_nvme->is_msi = RT_TRUE;

            for (int i = 0; i < nvme->irqs_nr; ++i)
            {
                nvme->irqs[i] = pci_nvme->msix_entries[i].irq;
            }
        }
    }

    if (!pci_nvme->is_msi)
    {
        nvme->irqs_nr = 1;
        nvme->irqs[0] = pdev->irq;
        rt_pci_irq_unmask(pdev);
    }

    rt_pci_set_master(pdev);

    if ((err = rt_nvme_controller_register(nvme)))
    {
        goto _disable;
    }

    pdev->parent.user_data = pci_nvme;

    return RT_EOK;

_disable:
    if (pci_nvme->is_msi)
    {
        rt_pci_msix_disable(pdev);
    }
    else
    {
        rt_pci_irq_mask(pdev);
    }
    rt_pci_clear_master(pdev);
    rt_iounmap(nvme->regs);

_fail:
    rt_free(pci_nvme);

    return err;
}

static rt_err_t pci_nvme_remove(struct rt_pci_device *pdev)
{
    struct rt_nvme_controller *nvme;
    struct pci_nvme_controller *pci_nvme = pdev->parent.user_data;

    nvme = &pci_nvme->parent;

    rt_nvme_controller_unregister(nvme);

    if (pci_nvme->is_msi)
    {
        rt_pci_msix_disable(pdev);
    }
    else
    {
        /* INTx is shared, don't mask all */
        rt_hw_interrupt_umask(pdev->irq);
        rt_pci_irq_mask(pdev);
    }

    rt_pci_clear_master(pdev);

    rt_iounmap(nvme->regs);
    rt_free(pci_nvme);

    return RT_EOK;
}

static rt_err_t pci_nvme_shutdown(struct rt_pci_device *pdev)
{
    return pci_nvme_remove(pdev);
}

static const struct rt_pci_device_id pci_nvme_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0010) },
    { RT_PCI_DEVICE_CLASS(PCIS_STORAGE_EXPRESS, ~0) },
    { /* sentinel */ }
};

static struct rt_pci_driver pci_nvme_driver =
{
    .name = "nvme-pci",

    .ids = pci_nvme_ids,
    .probe = pci_nvme_probe,
    .remove = pci_nvme_remove,
    .shutdown = pci_nvme_shutdown,
};
RT_PCI_DRIVER_EXPORT(pci_nvme_driver);
