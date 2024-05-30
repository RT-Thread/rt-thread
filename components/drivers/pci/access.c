/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <drivers/pci.h>

struct rt_spinlock rt_pci_lock = { 0 };

#ifdef RT_PCI_LOCKLESS
#define pci_lock_config(l)      do { (void)(l); } while (0)
#define pci_unlock_config(l)    do { (void)(l); } while (0)
#else
#define pci_lock_config(l)      l = rt_spin_lock_irqsave(&rt_pci_lock)
#define pci_unlock_config(l)    rt_spin_unlock_irqrestore(&rt_pci_lock, l)
#endif

#define PCI_OPS_READ(name, type) \
rt_err_t rt_pci_bus_read_config_##name(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg, type *value) \
{                                                               \
    rt_err_t err;                                               \
    rt_ubase_t level;                                           \
    rt_uint32_t data = 0;                                       \
    pci_lock_config(level);                                     \
    err = bus->ops->read(bus, devfn, reg, sizeof(type), &data); \
    *value = err ? (type)(~0) : (type)data;                     \
    pci_unlock_config(level);                                   \
    return err;                                                 \
}

#define PCI_OPS_WRITE(name, type) \
rt_err_t rt_pci_bus_write_config_##name(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg, type value) \
{                                                                \
    rt_err_t err;                                                \
    rt_ubase_t level;                                            \
    pci_lock_config(level);                                      \
    err = bus->ops->write(bus, devfn, reg, sizeof(type), value); \
    pci_unlock_config(level);                                    \
    return err;                                                  \
}

#define PCI_OPS(name, type)  \
    PCI_OPS_READ(name, type) \
    PCI_OPS_WRITE(name, type)

PCI_OPS(u8, rt_uint8_t)
PCI_OPS(u16, rt_uint16_t)
PCI_OPS(u32, rt_uint32_t)

#undef PCI_OP_WRITE
#undef PCI_OP_READ
#undef PCI_OPS

rt_err_t rt_pci_bus_read_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t *val)
{
    void *base;

    if ((base = bus->ops->map(bus, devfn, reg)))
    {
        if (width == 1)
        {
            *val = HWREG8(base);
        }
        else if (width == 2)
        {
            *val = HWREG16(base);
        }
        else
        {
            *val = HWREG32(base);
        }

        return RT_EOK;
    }

    return -RT_ERROR;
}

rt_err_t rt_pci_bus_write_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t val)
{
    void *base;

    if ((base = bus->ops->map(bus, devfn, reg)))
    {
        if (width == 1)
        {
            HWREG8(base) = val;
        }
        else if (width == 2)
        {
            HWREG16(base) = val;
        }
        else
        {
            HWREG32(base) = val;
        }

        return RT_EOK;
    }

    return -RT_ERROR;
}
