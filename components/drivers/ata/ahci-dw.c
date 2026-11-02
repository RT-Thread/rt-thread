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

#define DBG_TAG "ahci.dwc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct dwc_ahci_host
{
    struct rt_ahci_host parent;

    struct rt_clk_array *clk_arr;
    struct rt_phye      *sata_phy;
};

static const struct rt_ahci_ops dwc_ahci_ops = {};

static void dwc_ahci_free(struct dwc_ahci_host *dwc_ahci)
{
    if (!rt_is_err_or_null(dwc_ahci->sata_phy))
    {
        rt_phye_put(dwc_ahci->sata_phy);
    }

    if (dwc_ahci->parent.regs)
    {
        rt_iounmap(dwc_ahci->parent.regs);
    }

    rt_free(dwc_ahci);
}

static rt_err_t dwc_ahci_probe(struct rt_platform_device *pdev)
{
    rt_err_t              err;
    struct rt_ahci_host  *ahci;
    struct rt_device     *dev      = &pdev->parent;
    struct dwc_ahci_host *dwc_ahci = rt_calloc(1, sizeof(*dwc_ahci));

    if (!dwc_ahci)
    {
        return -RT_ENOMEM;
    }

    ahci             = &dwc_ahci->parent;
    ahci->parent.dev = dev;

    ahci->regs = rt_dm_dev_iomap(dev, 0);

    if (!ahci->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ahci->irq = rt_dm_dev_get_irq(dev, 0);

    if (ahci->irq < 0)
    {
        err = ahci->irq;
        goto _fail;
    }

    dwc_ahci->clk_arr = rt_clk_get_array(dev);

    if (rt_is_err(dwc_ahci->clk_arr))
    {
        LOG_E("Missing CLK");
        err = rt_ptr_err(dwc_ahci->clk_arr);

        goto _fail;
    }

    dwc_ahci->sata_phy = rt_phye_get_by_name(dev, "sata-phy");

    if (rt_is_err(dwc_ahci->sata_phy))
    {
        LOG_E("Missing PHY");
        err = rt_ptr_err(dwc_ahci->sata_phy);

        goto _fail;
    }

    if ((err = rt_clk_array_prepare_enable(dwc_ahci->clk_arr)))
    {
        goto _fail;
    }

    if ((err = rt_phye_init(dwc_ahci->sata_phy)))
    {
        goto _disable_clk;
    }

    if ((err = rt_phye_power_on(dwc_ahci->sata_phy)))
    {
        goto _phy_exit;
    }

    ahci->ops = &dwc_ahci_ops;

    if ((err = rt_ahci_host_register(ahci)))
    {
        goto _phy_power_off;
    }

    dev->user_data = dwc_ahci;

    return RT_EOK;

_phy_power_off:
    rt_phye_power_off(dwc_ahci->sata_phy);

_phy_exit:
    rt_phye_exit(dwc_ahci->sata_phy);

_disable_clk:
    rt_clk_array_disable_unprepare(dwc_ahci->clk_arr);

_fail:
    dwc_ahci_free(dwc_ahci);

    return err;
}

static rt_err_t dwc_ahci_remove(struct rt_platform_device *pdev)
{
    struct dwc_ahci_host *dwc_ahci = pdev->parent.user_data;

    rt_phye_exit(dwc_ahci->sata_phy);
    rt_phye_power_off(dwc_ahci->sata_phy);

    rt_clk_array_disable_unprepare(dwc_ahci->clk_arr);

    dwc_ahci_free(dwc_ahci);

    return RT_EOK;
}

static rt_err_t dwc_ahci_shutdown(struct rt_platform_device *pdev)
{
    return dwc_ahci_remove(pdev);
}

static const struct rt_ofw_node_id dwc_ahci_ofw_ids[] = {
    { .compatible = "snps,dwc-ahci" },
    { /* sentinel */ }
};

static struct rt_platform_driver ahci_dwc_driver = {
    .name = "ahci-dwc",
    .ids  = dwc_ahci_ofw_ids,

    .probe    = dwc_ahci_probe,
    .remove   = dwc_ahci_remove,
    .shutdown = dwc_ahci_shutdown,
};
RT_PLATFORM_DRIVER_EXPORT(ahci_dwc_driver);
