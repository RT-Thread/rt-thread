/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-07     GuEe-GUI     first version
 */

#include <rtthread.h>

#define DBG_TAG "pci.irq"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pci.h>

void rt_pci_assign_irq(struct rt_pci_device *pdev)
{
    int irq = 0;
    rt_uint8_t pin, slot = -1;
    struct rt_pci_host_bridge *host_bridge = rt_pci_find_host_bridge(pdev->bus);

    if (!host_bridge->irq_map)
    {
        LOG_D("PCI-Device<%s> runtime IRQ mapping not provided by platform",
                rt_dm_dev_get_name(&pdev->parent));

        return;
    }

    /* Must try the swizzle when interrupt line passes through a P2P bridge */
    rt_pci_read_config_u8(pdev, PCIR_INTPIN, &pin);

    if (pin > RT_PCI_INTX_PIN_MAX)
    {
        pin = 1;
    }

    if (pin)
    {
        if (host_bridge->irq_slot)
        {
            slot = host_bridge->irq_slot(pdev, &pin);
        }

        /* Map IRQ */
        if ((irq = host_bridge->irq_map(pdev, slot, pin)) == -1)
        {
            irq = 0;
        }
    }
    pdev->irq = irq;

    LOG_D("PCI-Device<%s> assign IRQ: got %d", rt_dm_dev_get_name(&pdev->parent), pdev->irq);

    /* Save IRQ */
    rt_pci_write_config_u8(pdev, PCIR_INTLINE, irq);
}
