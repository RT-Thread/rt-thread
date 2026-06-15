/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-07     GuEe-GUI     first version
 */

/**
 * @file irq.c
 * @brief PCI interrupt routing and assignment
 *
 * Handles INTx interrupt assignment for PCI devices, including:
 * - Reading the Interrupt Pin register from config space
 * - Route mapping via the host bridge's irq_map callback
 * - Swizzling through PCI-to-PCI bridges (if the host bridge provides irq_slot)
 * - Writing the assigned IRQ number back to the Interrupt Line register
 */

#include <rtthread.h>

#define DBG_TAG "pci.irq"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pci.h>

/**
 * @brief Assign an IRQ to a PCI device
 *
 * The assignment flow:
 * 1. Read the Interrupt Pin register (INTA=1, INTB=2, INTC=3, INTD=4)
 * 2. Optionally perform swizzling through bridges via irq_slot callback
 * 3. Map the (slot, pin) pair to an IRQ number via irq_map callback
 * 4. Write the assigned IRQ to the Interrupt Line register
 *
 * The host bridge must provide the irq_map callback. Without it,
 * INTx interrupts are not available and the device must use MSI/MSI-X.
 *
 * @param[in] pdev PCI device to assign an IRQ to
 */
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
