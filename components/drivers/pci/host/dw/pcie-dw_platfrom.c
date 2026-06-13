/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

/**
 * @file pcie-dw_platfrom.c
 * @brief Synopsys DesignWare PCIe platform driver
 *
 * This is the generic DesignWare PCIe platform driver that binds to
 * "snps,dw-pcie" and "snps,dw-pcie-ep" compatible nodes in the device tree.
 * It supports both Root Complex (RC) and Endpoint (EP) modes, selected
 * by the compatible string.
 *
 * RC mode (@ref DW_PCIE_RC_TYPE):
 * - Maps DBI registers
 * - Configures MSI interrupt controller
 * - Sets up ATU for memory and I/O space translation
 * - Initiates link training
 *
 * EP mode (@ref DW_PCIE_EP_TYPE):
 * - Maps DBI and DBI2 (endpoint config space) registers
 * - Resets BARs to default state
 * - Supports legacy INTx, MSI, and MSI-X IRQ raising
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pcie.dw.platfrom"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-dw.h"

/**
 * @brief Platform-specific SoC data
 *
 * Determines whether the controller operates as RC or EP.
 */
struct dw_dw_platform_pcie_soc_data
{
    enum dw_pcie_device_mode mode; /**< Device mode: RC or EP */
};

/**
 * @brief Platform PCIe instance
 */
struct dw_platform_pcie
{
    struct dw_pcie *pci;                              /**< Core DW PCIe structure */
    struct rt_syscon *regmap;                          /**< Optional syscon regmap */
    const struct dw_dw_platform_pcie_soc_data *soc_data; /**< SoC-specific data */
};

/**
 * @brief RC host init: setup RC, wait for link, init MSI
 *
 * @param[in] port DW PCIe port
 * @return RT_EOK
 */
static rt_err_t dw_platform_pcie_host_init(struct dw_pcie_port *port)
{
    struct dw_pcie *pci = to_dw_pcie_from_port(port);

    dw_pcie_setup_rc(port);
    dw_pcie_wait_for_link(pci);
    dw_pcie_msi_init(port);

    return RT_EOK;
}

/**
 * @brief Set maximum MSI IRQ count for the platform
 *
 * @param[in] pp DW PCIe port (irq_count updated)
 */
static void dw_platform_set_irq_count(struct dw_pcie_port *pp)
{
    pp->irq_count = MAX_MSI_IRQS;
}

/** @brief Platform host ops */
static const struct dw_pcie_host_ops dw_platform_pcie_host_ops =
{
    .host_init = dw_platform_pcie_host_init,
    .set_irq_count = dw_platform_set_irq_count,
};

/**
 * @brief Platform-specific link establishment (no-op, handled by dw_pcie_setup)
 *
 * @param[in] pci DW PCIe controller
 * @return RT_EOK
 */
static rt_err_t dw_platform_pcie_establish_link(struct dw_pcie *pci)
{
    return RT_EOK;
}

/** @brief Platform PCIe ops */
static const struct dw_pcie_ops dw_platform_pcie_ops =
{
    .start_link = dw_platform_pcie_establish_link,
};

/**
 * @brief EP initialization: reset all BARs to default
 *
 * @param[in] ep DW PCIe EP
 * @return RT_EOK
 */
static rt_err_t dw_platform_pcie_ep_init(struct dw_pcie_ep *ep)
{
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    for (int bar = 0; bar < PCI_STD_NUM_BARS; ++bar)
    {
        dw_pcie_ep_reset_bar(pci, bar);
    }

    return RT_EOK;
}

/**
 * @brief EP IRQ raise: dispatch to legacy, MSI, or MSI-X handler
 *
 * @param[in] ep      DW PCIe EP
 * @param[in] func_no Function number
 * @param[in] type    IRQ type
 * @param[in] irq     Vector number (for MSI/MSI-X)
 * @return RT_EOK on success
 */
static rt_err_t dw_platform_pcie_ep_raise_irq(struct dw_pcie_ep *ep,
        rt_uint8_t func_no, enum rt_pci_ep_irq type, unsigned irq)
{
    switch (type)
    {
    case RT_PCI_EP_IRQ_LEGACY:
        return dw_pcie_ep_raise_legacy_irq(ep, func_no);

    case RT_PCI_EP_IRQ_MSI:
        return dw_pcie_ep_raise_msi_irq(ep, func_no, irq);

    case RT_PCI_EP_IRQ_MSIX:
        return dw_pcie_ep_raise_msix_irq(ep, func_no, irq);

    default:
        LOG_E("Unknown IRQ type = %d", type);
    }

    return RT_EOK;
}

/** @brief Platform EP ops */
static const struct dw_pcie_ep_ops dw_platform_pcie_ep_ops =
{
    .ep_init = dw_platform_pcie_ep_init,
    .raise_irq = dw_platform_pcie_ep_raise_irq,
};

/**
 * @brief Add a PCIe port in RC mode
 *
 * Gets system IRQ and MSI IRQ from device tree, assigns
 * host ops, and calls dw_pcie_host_init().
 *
 * @param[in] plat_pcie Platform PCIe instance
 * @param[in] dev       Platform device
 * @return RT_EOK on success
 */
static rt_err_t dw_platform_add_pcie_port(struct dw_platform_pcie *plat_pcie,
        struct rt_device *dev)
{
    rt_err_t err;
    struct dw_pcie *pci = plat_pcie->pci;
    struct dw_pcie_port *port = &pci->port;

    port->sys_irq = rt_dm_dev_get_irq(dev, 1);

    if (port->sys_irq < 0)
    {
        return port->sys_irq;
    }

#ifdef RT_PCI_MSI
    port->msi_irq = rt_dm_dev_get_irq(dev, 0);

    if (port->msi_irq < 0)
    {
        return port->msi_irq;
    }
#endif

    port->ops = &dw_platform_pcie_host_ops;

    if ((err = dw_pcie_host_init(port)))
    {
        LOG_E("Failed to initialize host");
        return err;
    }

    return RT_EOK;
}

/**
 * @brief Add a PCIe port in EP mode
 *
 * Maps DBI2, gets the address space for outbound translation,
 * and initializes the endpoint.
 *
 * @param[in] plat_pcie Platform PCIe instance
 * @param[in] dev       Platform device
 * @return RT_EOK on success
 */
static rt_err_t dw_platform_add_pcie_ep(struct dw_platform_pcie *plat_pcie,
        struct rt_device *dev)
{
    rt_err_t err;
    struct dw_pcie *pci = plat_pcie->pci;
    struct dw_pcie_ep *ep = &pci->endpoint;

    pci->dbi_base2 = rt_dm_dev_iomap_by_name(dev, "dbi2");

    if (!pci->dbi_base2)
    {
        return -RT_EIO;
    }

    err = rt_dm_dev_get_address_by_name(dev, "addr_space", &ep->aspace, &ep->aspace_size);

    if (err)
    {
        rt_iounmap(pci->dbi_base2);
        return err;
    }

    ep->ops = &dw_platform_pcie_ep_ops;

    if ((err = dw_pcie_ep_init(ep)))
    {
        LOG_E("Failed to initialize endpoint");
        return err;
    }

    return RT_EOK;
}

/**
 * @brief Probe a DW PCIe platform device
 *
 * Binds to "snps,dw-pcie" (RC mode) or "snps,dw-pcie-ep" (EP mode).
 * Maps DBI base, determines mode from soc_data, and initializes
 * the appropriate port type.
 *
 * @param[in] pdev Platform device
 * @return RT_EOK on success
 */
static rt_err_t dw_platform_pcie_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct dw_pcie *pci = RT_NULL;
    struct dw_platform_pcie *plat_pcie;
    struct rt_device *dev = &pdev->parent;

    if (!(plat_pcie = rt_calloc(1, sizeof(*plat_pcie))))
    {
        return -RT_ENOMEM;
    }

    if (!(pci = rt_calloc(1, sizeof(*pci))))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    plat_pcie->pci = pci;
    plat_pcie->soc_data = pdev->id->data;

    pci->dev = dev;
    pci->ops = &dw_platform_pcie_ops;
    pci->dbi_base = rt_dm_dev_iomap_by_name(dev, "dbi");

    if (!pci->dbi_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    dev->user_data = plat_pcie;

    switch (plat_pcie->soc_data->mode)
    {
    case DW_PCIE_RC_TYPE:
        if (!RT_KEY_ENABLED(RT_PCI_DW_HOST))
        {
            err = -RT_ENOSYS;
            goto _fail;
        }

        if ((err = dw_platform_add_pcie_port(plat_pcie, dev)))
        {
            goto _fail;
        }
        break;

    case DW_PCIE_EP_TYPE:
        if (!RT_KEY_ENABLED(RT_PCI_DW_EP))
        {
            err = -RT_ENOSYS;
            goto _fail;
        }

        if ((err = dw_platform_add_pcie_ep(plat_pcie, dev)))
        {
            goto _fail;
        }
        break;

    default:
        LOG_E("Invalid device type %d", plat_pcie->soc_data->mode);
        err = -RT_EINVAL;
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (pci)
    {
        if (pci->dbi_base)
        {
            rt_iounmap(pci->dbi_base);
        }

        rt_free(pci);
    }

    rt_free(plat_pcie);

    return err;
}

/**
 * @brief Remove a DW PCIe platform device
 *
 * @param[in] pdev Platform device
 * @return RT_EOK
 */
static rt_err_t dw_platform_pcie_remove(struct rt_platform_device *pdev)
{
    struct dw_platform_pcie *plat_pcie = pdev->parent.user_data;

    rt_pci_host_bridge_remove(plat_pcie->pci->port.bridge);
    dw_pcie_host_free(&plat_pcie->pci->port);

    rt_iounmap(plat_pcie->pci->dbi_base);
    rt_free(plat_pcie->pci);

    rt_free(plat_pcie);

    return RT_EOK;
}

/** @brief RC mode SoC data */
static const struct dw_dw_platform_pcie_soc_data dw_platform_pcie_rc_soc_data =
{
    .mode = DW_PCIE_RC_TYPE,
};

/** @brief EP mode SoC data */
static const struct dw_dw_platform_pcie_soc_data dw_platform_pcie_ep_soc_data =
{
    .mode = DW_PCIE_EP_TYPE,
};

/** @brief Device tree compatible IDs */
static const struct rt_ofw_node_id dw_platform_pcie_ofw_ids[] =
{
    { .compatible = "snps,dw-pcie", .data = &dw_platform_pcie_rc_soc_data },
    { .compatible = "snps,dw-pcie-ep", .data = &dw_platform_pcie_ep_soc_data },
    { /* sentinel */ }
};

/** @brief DW PCIe platform driver */
static struct rt_platform_driver dw_platform_pcie_driver =
{
    .name = "dw-pcie",
    .ids = dw_platform_pcie_ofw_ids,

    .probe = dw_platform_pcie_probe,
    .remove = dw_platform_pcie_remove,
};
RT_PLATFORM_DRIVER_EXPORT(dw_platform_pcie_driver);
