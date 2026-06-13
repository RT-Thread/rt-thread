/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

/**
 * @file access.c
 * @brief PCI Configuration Space Access Layer
 *
 * Provides standardized read/write access to PCI configuration space
 * through bus ops (ECAM, DW PCIe, etc.). Includes lock-protected
 * config access, memory-mapped access helpers, and generic 32-bit
 * access with sub-word extraction/merging.
 *
 * Configuration space locking can be disabled at compile time with
 * RT_PCI_LOCKLESS for single-CPU or carefully managed systems.
 */

#include <rthw.h>
#include <rtthread.h>

#include <drivers/pci.h>

/** @brief Global PCI configuration space spinlock */
struct rt_spinlock rt_pci_lock = { 0 };

#ifdef RT_PCI_LOCKLESS
#define pci_lock_config(l)      do { (void)(l); } while (0)
#define pci_unlock_config(l)    do { (void)(l); } while (0)
#else
/** @brief Acquire the PCI config space lock with IRQ save */
#define pci_lock_config(l)      l = rt_spin_lock_irqsave(&rt_pci_lock)
/** @brief Release the PCI config space lock with IRQ restore */
#define pci_unlock_config(l)    rt_spin_unlock_irqrestore(&rt_pci_lock, l)
#endif

/**
 * @def PCI_OPS_READ(name, type)
 * @brief Generate a locked config-space read function
 *
 * Reads a value of the specified width from PCI config space
 * through the bus operations, protected by the PCI config lock.
 *
 * @param[in]  bus   PCI bus
 * @param[in]  devfn Device/function number
 * @param[in]  reg   Configuration register offset
 * @param[out] value Read value (all-ones on error)
 * @return RT_EOK on success, error code otherwise
 */
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

/**
 * @def PCI_OPS_WRITE(name, type)
 * @brief Generate a locked config-space write function
 *
 * Writes a value of the specified width to PCI config space
 * through the bus operations, protected by the PCI config lock.
 *
 * @param[in] bus   PCI bus
 * @param[in] devfn Device/function number
 * @param[in] reg   Configuration register offset
 * @param[in] value Value to write
 * @return RT_EOK on success, error code otherwise
 */
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

/**
 * @brief Read from PCI config space using memory-mapped access (any width)
 *
 * Uses bus->ops->map() to get a direct MMIO pointer to the config
 * register, then reads the appropriate width (1/2/4 bytes).
 *
 * @param[in]  bus   PCI bus
 * @param[in]  devfn Device/function number
 * @param[in]  reg   Configuration register offset
 * @param[in]  width Access width (1, 2, or 4 bytes)
 * @param[out] value Read value
 * @return RT_EOK on success, -RT_ERROR if mapping failed
 */
rt_err_t rt_pci_bus_read_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t *value)
{
    void *base;

    if ((base = bus->ops->map(bus, devfn, reg)))
    {
        if (width == 1)
        {
            *value = HWREG8(base);
        }
        else if (width == 2)
        {
            *value = HWREG16(base);
        }
        else
        {
            *value = HWREG32(base);
        }

        return RT_EOK;
    }

    return -RT_ERROR;
}

/**
 * @brief Write to PCI config space using memory-mapped access (any width)
 *
 * @param[in] bus   PCI bus
 * @param[in] devfn Device/function number
 * @param[in] reg   Configuration register offset
 * @param[in] width Access width (1, 2, or 4 bytes)
 * @param[in] value Value to write
 * @return RT_EOK on success, -RT_ERROR if mapping failed
 */
rt_err_t rt_pci_bus_write_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t value)
{
    void *base;

    if ((base = bus->ops->map(bus, devfn, reg)))
    {
        if (width == 1)
        {
            HWREG8(base) = value;
        }
        else if (width == 2)
        {
            HWREG16(base) = value;
        }
        else
        {
            HWREG32(base) = value;
        }

        return RT_EOK;
    }

    return -RT_ERROR;
}

/**
 * @brief Read from PCI config space using generic 32-bit access with sub-word extraction
 *
 * Always reads a full 32-bit word and extracts the requested bytes.
 * Required for platforms where the bus ops only support 32-bit access.
 *
 * @param[in]  bus   PCI bus
 * @param[in]  devfn Device/function number
 * @param[in]  reg   Configuration register offset
 * @param[in]  width Access width (1 or 2 bytes; 4 also works)
 * @param[out] value Read value (correctly shifted and masked)
 * @return RT_EOK on success, -RT_ERROR if mapping failed
 */
rt_err_t rt_pci_bus_read_config_generic_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t *value)
{
    void *base;

    if ((base = bus->ops->map(bus, devfn, reg)))
    {
        *value = HWREG32(base);

        if (width <= 2)
        {
            *value = (*value >> (8 * (reg & 3))) & ((1 << (width * 8)) - 1);
        }

        return RT_EOK;
    }

    return -RT_ERROR;
}

/**
 * @brief Write to PCI config space using generic 32-bit access with sub-word merging
 *
 * Uses a read-modify-write cycle for sub-32-bit writes to preserve
 * surrounding bytes. Required for platforms that only support 32-bit
 * config space access.
 *
 * @param[in] bus   PCI bus
 * @param[in] devfn Device/function number
 * @param[in] reg   Configuration register offset
 * @param[in] width Access width (1, 2, or 4 bytes)
 * @param[in] value Value to write
 * @return RT_EOK on success, -RT_ERROR if mapping failed
 */
rt_err_t rt_pci_bus_write_config_generic_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t value)
{
    void *base;

    if ((base = bus->ops->map(bus, devfn, reg & ~0x3)))
    {
        if (width == 4)
        {
            HWREG32(base) = value;
        }
        else
        {
            rt_uint32_t mask, tmp;

            mask = ~(((1 << (width * 8)) - 1) << ((reg & 0x3) * 8));
            tmp = HWREG32(base) & mask;
            tmp |= value << ((reg & 0x3) * 8);
            HWREG32(base) = tmp;
        }

        return RT_EOK;
    }

    return -RT_ERROR;
}
