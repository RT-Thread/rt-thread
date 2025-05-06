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

#define AHCI_REG_BAR 5

struct pci_ahci_quirk
{
    int bar_idx;
    rt_bool_t bar_offset;

    const struct rt_ahci_ops *ops;
};

struct pci_ahci_host
{
    struct rt_ahci_host parent;
    const struct pci_ahci_quirk *quirk;

    rt_bool_t is_msi;
};

#define raw_to_pci_ahci_host(raw) rt_container_of(raw, struct pci_ahci_host, parent)

static rt_err_t pci_ahci_init(struct rt_ahci_host *host)
{
    struct rt_pci_device *pdev;

    pdev = rt_container_of(host->parent.dev, struct rt_pci_device, parent);

    if (pdev->vendor == PCI_VENDOR_ID_JMICRON)
    {
        rt_pci_write_config_u8(pdev, 0x41, 0xa1);
    }

    return RT_EOK;
}

static const struct rt_ahci_ops pci_ahci_ops =
{
    .host_init = pci_ahci_init,
};

static rt_err_t pci_ahci_intel_init(struct rt_ahci_host *host)
{
    rt_uint16_t val;
    struct rt_pci_device *pdev;

    pdev = rt_container_of(host->parent.dev, struct rt_pci_device, parent);

    rt_pci_read_config_u16(pdev, 0x92, &val);
    rt_pci_write_config_u16(pdev, 0x92, val & ~0xf);

    rt_thread_mdelay(10);
    rt_pci_write_config_u16(pdev, 0x92, val | 0xf);

    return RT_EOK;
}

static const struct rt_ahci_ops pci_ahci_intel_ops =
{
    .host_init = pci_ahci_intel_init,
};

static rt_err_t pci_ahci_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    int bar_idx;
    struct rt_ahci_host *ahci;
    struct pci_ahci_host *pci_ahci = rt_calloc(1, sizeof(*pci_ahci));
    const struct pci_ahci_quirk *quirk = pdev->id->data;

    if (!pci_ahci)
    {
        return -RT_ENOMEM;
    }

    pci_ahci->quirk = quirk;
    ahci = &pci_ahci->parent;
    ahci->parent.dev = &pdev->parent;

    bar_idx = quirk && quirk->bar_offset ? quirk->bar_idx : AHCI_REG_BAR;

    ahci->regs = rt_pci_iomap(pdev, bar_idx);

    if (!ahci->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ahci->ops = quirk && quirk->ops ? quirk->ops : &pci_ahci_ops;

    if (rt_pci_msi_enable(pdev) > 0)
    {
        pci_ahci->is_msi = RT_TRUE;
    }
    else
    {
        rt_pci_irq_unmask(pdev);
    }
    ahci->irq = pdev->irq;

    rt_pci_set_master(pdev);

    if ((err = rt_ahci_host_register(ahci)))
    {
        goto _disable;
    }

    pdev->parent.user_data = pci_ahci;

    return RT_EOK;

_disable:
    if (pci_ahci->is_msi)
    {
        rt_pci_msix_disable(pdev);
    }
    else
    {
        rt_pci_irq_mask(pdev);
    }
    rt_pci_clear_master(pdev);
    rt_iounmap(ahci->regs);

_fail:
    rt_free(pci_ahci);

    return err;
}

static rt_err_t pci_ahci_remove(struct rt_pci_device *pdev)
{
    struct rt_ahci_host *ahci;
    struct pci_ahci_host *pci_ahci = pdev->parent.user_data;

    ahci = &pci_ahci->parent;

    rt_ahci_host_unregister(ahci);

    if (pci_ahci->is_msi)
    {
        rt_pci_msi_disable(pdev);
    }
    else
    {
        /* INTx is shared, don't mask all */
        rt_hw_interrupt_umask(pdev->irq);
        rt_pci_irq_mask(pdev);
    }

    rt_pci_clear_master(pdev);

    rt_iounmap(ahci->regs);
    rt_free(pci_ahci);

    return RT_EOK;
}

static rt_err_t pci_ahci_shutdown(struct rt_pci_device *pdev)
{
    return pci_ahci_remove(pdev);
}

static struct pci_ahci_quirk intel_quirk =
{
    .ops = &pci_ahci_intel_ops,
};

static struct pci_ahci_quirk cavium_sata_quirk =
{
    .bar_idx = 0,
    .bar_offset = RT_TRUE,
};

static const struct rt_pci_device_id pci_ahci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_INTEL, 0x2922), .data = &intel_quirk },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_ASMEDIA, 0x0611) },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_MARVELL, 0x6121) },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_MARVELL, 0x6145) },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_CAVIUM, 0xa01c), .data = &cavium_sata_quirk },
    { RT_PCI_DEVICE_CLASS(PCIS_STORAGE_SATA_AHCI, ~0) },
    { /* sentinel */ }
};

static struct rt_pci_driver pci_ahci_driver =
{
    .name = "ahci-pci",

    .ids = pci_ahci_ids,
    .probe = pci_ahci_probe,
    .remove = pci_ahci_remove,
    .shutdown = pci_ahci_shutdown,
};
RT_PCI_DRIVER_EXPORT(pci_ahci_driver);
