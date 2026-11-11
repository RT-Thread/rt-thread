/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include "dev_sdio_dw.h"

#include <mmu.h>

#define SYNOPSYS_DW_MCI_VENDOR_ID 0x0700
#define SYNOPSYS_DW_MCI_DEVICE_ID 0x1107

#define MCI_REG_NO 2

static const struct sdio_dw_drv_data sdio_dw_pci_drv_data =
{
};

static rt_err_t sdio_dw_pci_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct sdio_dw *sd = rt_calloc(1, sizeof(*sd));

    if (!sd)
    {
        return -RT_ENOMEM;
    }

    sd->bus_dev = &pdev->parent;
    sd->base = rt_pci_iomap(pdev, MCI_REG_NO);

    if (!sd->base)
    {
        goto _fail;
    }

    sd->irq = pdev->irq;
    rt_pci_irq_unmask(pdev);

    sd->base_phy = (rt_ubase_t)rt_kmem_v2p(sd->base);
    sd->drv_data = &sdio_dw_pci_drv_data;

    /* board data */
    sd->bus_hz = 33 * 1000 * 1000;
    sd->detect_delay_ms = 200;
    sd->fifo_depth = 32;

    pdev->parent.user_data = sd;

    if ((err = sdio_dw_probe(sd)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (sd->base)
    {
        rt_iounmap(sd->base);
    }

    rt_free(sd);

    return err;
}

static rt_err_t sdio_dw_pci_remove(struct rt_pci_device *pdev)
{
    struct sdio_dw *sd = pdev->parent.user_data;

    sdio_dw_remove(sd);

    rt_iounmap(sd->base);

    rt_free(sd);

    return RT_EOK;
}

static const struct rt_pci_device_id sdio_dw_pci_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(SYNOPSYS_DW_MCI_VENDOR_ID, SYNOPSYS_DW_MCI_DEVICE_ID) },
    { /* sentinel */ }
};

static struct rt_pci_driver sdio_dw_pci_driver =
{
    .name = "dw-mmc-pci",

    .ids = sdio_dw_pci_pci_ids,
    .probe = sdio_dw_pci_probe,
    .remove = sdio_dw_pci_remove,
};
RT_PCI_DRIVER_EXPORT(sdio_dw_pci_driver);
