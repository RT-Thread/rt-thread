/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     GuEe-GUI     first version
 */

#include <rtthread.h>

#include "8250.h"

#define IO_PORT_BAR 0

enum
{
    PCI_SERIAL  = 0,
    PCI_SERIAL2 = 2,
    PCI_SERIAL4 = 4,
};

enum
{
    SERIAL_8250 = 0,
    SERIAL_16450,
    SERIAL_16550,
    SERIAL_16650,
    SERIAL_16750,
    SERIAL_16850,
    SERIAL_16950,
};

struct pci_serial
{
    struct serial8250 parent;
    struct rt_spinlock spinlock;

    struct rt_pci_device *pci_dev;

    rt_uint8_t type;
    rt_uint8_t compat;
};

#define to_pci_serial(raw) rt_container_of(raw, struct pci_serial, parent)

static rt_err_t pci_serial_isr(struct serial8250 *serial, int irq)
{
    rt_uint32_t iir;
    void *base = serial->base;

    iir = HWREG8(base + UART_IIR);

    if (!(iir & UART_IIR_NO_INT))
    {
        rt_hw_serial_isr(&serial->parent, RT_SERIAL_EVENT_RX_IND);
    }

    return RT_EOK;
}

static rt_ubase_t pci_serial_clock(struct pci_serial *pci_serial)
{
    rt_ubase_t clock = 1843200;

    return clock;
}

static void pci_serial_free_resource(struct pci_serial *pci_serial)
{
    struct serial8250 *serial = &pci_serial->parent;

    if (serial->base)
    {
        rt_iounmap(serial->base);
    }

    rt_free(pci_serial);
}

static void pci_8250serial_remove(struct serial8250 *serial)
{
    struct pci_serial *pci_serial = to_pci_serial(serial);

    rt_pci_irq_mask(pci_serial->pci_dev);

    pci_serial_free_resource(pci_serial);
}

static rt_err_t pci_serial_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct serial8250 *serial;
    struct pci_serial *pci_serial = serial8250_alloc(pci_serial);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (!pci_serial)
    {
        return -RT_ENOMEM;
    }

    serial = &pci_serial->parent;
    serial->size = pdev->resource[IO_PORT_BAR].size;
    serial->base = rt_pci_iomap(pdev, IO_PORT_BAR);

    if (!serial->base)
    {
        err = -RT_EIO;

        goto _free_res;
    }

    pdev->parent.user_data = serial;

    serial->irq = pdev->irq;

    serial->parent.ops = &serial8250_uart_ops;
    serial->parent.config = config;
    serial->freq = pci_serial_clock(pci_serial);
    serial->handle_irq = &pci_serial_isr;
    serial->iotype = PORT_MMIO;
    serial->remove = &pci_8250serial_remove;
    serial->data = pci_serial;

    pci_serial->pci_dev = pdev;
    pci_serial->type = (rt_ubase_t)pdev->id->data;
    rt_spin_lock_init(&pci_serial->spinlock);
    rt_pci_read_config_u8(pdev, PCIR_PROGIF, &pci_serial->compat);

    if ((err = serial8250_setup(serial)))
    {
        goto _free_res;
    }

    rt_pci_irq_unmask(pci_serial->pci_dev);

    return RT_EOK;

_free_res:
    pci_serial_free_resource(pci_serial);

    return err;
}

static rt_err_t pci_serial_remove(struct rt_pci_device *pdev)
{
    struct serial8250 *serial = pdev->parent.user_data;

    return serial8250_remove(serial);
}

static const struct rt_pci_device_id pci_serial_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0002), .data = (void *)PCI_SERIAL, },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0003), .data = (void *)PCI_SERIAL2, },
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT, 0x0004), .data = (void *)PCI_SERIAL4, },
    { /* sentinel */ }
};

static struct rt_pci_driver pci_serial_driver =
{
    .name = "serial-pci",

    .ids = pci_serial_pci_ids,
    .probe = pci_serial_probe,
    .remove = pci_serial_remove,
};
RT_PCI_DRIVER_EXPORT(pci_serial_driver);
