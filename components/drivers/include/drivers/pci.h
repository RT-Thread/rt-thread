/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

/**
 * @file pci.h
 * @brief PCI (Peripheral Component Interconnect) bus framework public API
 *
 * Defines the core PCI subsystem: device, bus, host bridge, driver
 * structures, configuration space access, capability discovery,
 * INTx/MSI/MSI-X interrupt management, resource allocation,
 * device tree integration, and bus enumeration.
 */

#ifndef __PCI_H__
#define __PCI_H__

#include <rtdef.h>
#include <bitmap.h>
#include <ioremap.h>
#include <drivers/ofw.h>
#include <drivers/pic.h>
#include <drivers/core/dm.h>
#include <drivers/core/driver.h>

#include "../../pci/pci_ids.h"
#include "../../pci/pci_regs.h"

/** @brief Maximum INTx pin number (INTA=1, INTB=2, INTC=3, INTD=4) */
#define RT_PCI_INTX_PIN_MAX         4
/** @brief Maximum number of BARs per PCI device */
#define RT_PCI_BAR_NR_MAX           6
/** @brief Maximum number of devices per PCI bus */
#define RT_PCI_DEVICE_MAX           32
/** @brief Maximum number of functions per PCI device (without ARI) */
#define RT_PCI_FUNCTION_MAX         8

/** @brief Maximum steps when searching the PCI capability linked list */
#define RT_PCI_FIND_CAP_TTL         48

/*
 * The PCI interface treats multi-function devices as independent
 * devices.  The slot/function address of each device is encoded
 * in a single byte as follows:
 *
 *  7:3 = slot
 *  2:0 = function
 */

/** @brief Build a 16-bit device ID from bus and devfn */
#define RT_PCI_DEVID(bus, devfn)    ((((rt_uint16_t)(bus)) << 8) | (devfn))
/** @brief Encode slot and function into a devfn byte */
#define RT_PCI_DEVFN(slot, func)    ((((slot) & 0x1f) << 3) | ((func) & 0x07))
/** @brief Extract slot number from a devfn byte */
#define RT_PCI_SLOT(devfn)          (((devfn) >> 3) & 0x1f)
/** @brief Extract function number from a devfn byte */
#define RT_PCI_FUNC(devfn)          ((devfn) & 0x07)

/** @brief PCIe L0s link state */
#define PCIE_LINK_STATE_L0S         RT_BIT(0)
/** @brief PCIe L1 link state */
#define PCIE_LINK_STATE_L1          RT_BIT(1)
/** @brief PCIe clock PM link state */
#define PCIE_LINK_STATE_CLKPM       RT_BIT(2)
/** @brief PCIe L1.1 substate */
#define PCIE_LINK_STATE_L1_1        RT_BIT(3)
/** @brief PCIe L1.2 substate */
#define PCIE_LINK_STATE_L1_2        RT_BIT(4)
/** @brief PCIe L1.1 with PCI-PM substate */
#define PCIE_LINK_STATE_L1_1_PCIPM  RT_BIT(5)
/** @brief PCIe L1.2 with PCI-PM substate */
#define PCIE_LINK_STATE_L1_2_PCIPM  RT_BIT(6)
/** @brief All PCIe ASPM link states combined */
#define PCIE_LINK_STATE_ALL         \
( \
    PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 | \
    PCIE_LINK_STATE_CLKPM | \
    PCIE_LINK_STATE_L1_1 | PCIE_LINK_STATE_L1_2 | \
    PCIE_LINK_STATE_L1_1_PCIPM | PCIE_LINK_STATE_L1_2_PCIPM \
)

/**
 * @brief PCI bus address region descriptor
 *
 * Describes a contiguous range of PCI bus address space and its
 * mapping to CPU physical memory. Used for BAR allocation.
 */
struct rt_pci_bus_region
{
    rt_uint64_t phy_addr;    /**< PCI bus physical address (start of region) */
    rt_uint64_t cpu_addr;    /**< CPU physical address mapped to this region */
    rt_uint64_t size;        /**< Region size in bytes */

    rt_uint64_t bus_start;   /**< Current allocation cursor within the region */

#define PCI_BUS_REGION_F_NONE       0xffffffff    /**< Region type: no memory (unused) */
#define PCI_BUS_REGION_F_MEM        0x00000000    /**< Region type: PCI memory space */
#define PCI_BUS_REGION_F_IO         0x00000001    /**< Region type: PCI I/O space */
#define PCI_BUS_REGION_F_PREFETCH   0x00000008    /**< Region type: prefetchable PCI memory */
    rt_ubase_t flags;        /**< Region flags (PCI_BUS_REGION_F_*) */
};

/**
 * @brief PCI BAR resource descriptor
 *
 * Describes a single BAR (Base Address Register) or Expansion ROM:
 * its CPU-side base address, size, and type flags.
 */
struct rt_pci_bus_resource
{
    rt_ubase_t base;         /**< CPU-side base address of the BAR */
    rt_size_t size;          /**< BAR size in bytes */

    rt_ubase_t flags;        /**< Resource flags (PCI_BUS_REGION_F_*) */
};

/*
 * PCI topology:
 *
 *   +-----+-----+         +-------------+   PCI Bus 0  +------------+ PCI Bus 1
 *   | RAM | CPU |---------| Host Bridge |--------+-----| PCI Bridge |-----+
 *   +-----+-----+         +-------------+        |     +------------+     |    +-------------+
 *                                                |                        +----| End Point 2 |
 *  +-------------+         +-------------+       |     +-------------+    |    +-------------+
 *  | End Point 5 |----+    | End Point 0 |-------+     | End Point 3 |----+
 *  +-------------+    |    +-------------+       |     +-------------+    |
 *                     |                          |                        |
 *  +-------------+    |    +-------------+       |     +-------------+    |    +-------------+
 *  | End Point 6 |----+----|  ISA Bridge |-------+-----| End Point 1 |    +----| End Point 4 |
 *  +-------------+         +-------------+       |     +-------------+         +-------------+
 *                                                |
 *         +------+         +----------------+    |
 *         | Port |---------| CardBus Bridge |----+
 *         +------+         +----------------+
 */

struct rt_pci_bus;

/**
 * @brief PCI device ID entry for driver matching
 *
 * Used in a driver's ID table. Supports matching by vendor/device,
 * subsystem vendor/device, and class code. PCI_ANY_ID acts as a
 * wildcard that matches any value.
 */
struct rt_pci_device_id
{
#define PCI_ANY_ID   (~0)
/** @brief Helper: initialize a device ID by vendor and device (subsystem = any) */
#define RT_PCI_DEVICE_ID(vend, dev) \
    .vendor = (vend),               \
    .device = (dev),                \
    .subsystem_vendor = PCI_ANY_ID, \
    .subsystem_device = PCI_ANY_ID

/** @brief Helper: initialize a device ID by class code with mask */
#define RT_PCI_DEVICE_CLASS(dev_class, dev_class_mask)  \
    .vendor = PCI_ANY_ID, .device = PCI_ANY_ID,         \
    .subsystem_vendor = PCI_ANY_ID,                     \
    .subsystem_device = PCI_ANY_ID,                     \
    .class = (dev_class), .class_mask = (dev_class_mask),

    rt_uint32_t vendor, device;           /**< Vendor and device ID (or PCI_ANY_ID for wildcard) */
    rt_uint32_t subsystem_vendor;         /**< Subsystem vendor ID (or PCI_ANY_ID) */
    rt_uint32_t subsystem_device;         /**< Subsystem device ID (or PCI_ANY_ID) */
    rt_uint32_t class, class_mask;        /**< (class, subclass, prog-if) triplet and mask */

    const void *data;                      /**< Driver-private data associated with this ID */
};

/**
 * @brief PCI device descriptor
 *
 * Represents a single PCI/PCIe device (endpoint or bridge) on a PCI bus.
 * Contains all configuration space information, resource assignments,
 * capability offsets, interrupt configuration, and MSI state.
 */
struct rt_pci_device
{
    struct rt_device parent;                               /**< Inherited RT-Thread device */
    const char *name;                                       /**< Device name (e.g., "0000:00:01.0") */

    rt_list_t list;                                         /**< Node in bus->devices_nodes */
    struct rt_pci_bus *bus;                                 /**< Parent PCI bus */
    struct rt_pci_bus *subbus;                              /**< Subordinate bus for PCI-to-PCI bridges (NULL for endpoints) */

    const struct rt_pci_device_id *id;                      /**< Matched device ID from driver table */

    rt_uint32_t devfn;                                      /**< Encoded device & function index */
    rt_uint16_t vendor;                                     /**< PCI vendor ID */
    rt_uint16_t device;                                     /**< PCI device ID */
    rt_uint16_t subsystem_vendor;                           /**< Subsystem vendor ID */
    rt_uint16_t subsystem_device;                           /**< Subsystem device ID */
    rt_uint32_t class;                                      /**< 3 bytes: (base class, subclass, prog-if) */
    rt_uint8_t revision;                                    /**< Revision ID */
    rt_uint8_t hdr_type;                                    /**< Header type (PCIM_HDRTYPE_*) */
    rt_uint8_t max_latency;                                 /**< Max latency timer value */
    rt_uint8_t min_grantl;                                  /**< Min grant value for burst transfers */
    rt_uint8_t int_pin;                                     /**< Interrupt pin (0=none, 1=INTA..4=INTD) */
    rt_uint8_t int_line;                                    /**< Interrupt line (IRQ number assigned by BIOS/fw) */
    rt_uint16_t exp_flags;                                  /**< PCI Express flags from PCIER_FLAGS register */
    rt_uint32_t cfg_size;                                   /**< Configuration space size (256 or 4096 bytes) */

    void *sysdata;                                           /**< System-private data */

    int irq;                                                /**< Assigned IRQ number */
    rt_uint8_t pin;                                         /**< INTx pin used for routing */
    struct rt_pic *intx_pic;                                /**< Interrupt controller for INTx */

    rt_bool_t pm_enabled;                                   /**< PME# is currently enabled */

    struct rt_pci_bus_resource resource[RT_PCI_BAR_NR_MAX]; /**< BAR resources (6 standard BARs) */
    struct rt_pci_bus_resource rom;                         /**< Expansion ROM resource */

    rt_uint8_t pme_cap;                                     /**< PM capability offset */
    rt_uint8_t msi_cap;                                     /**< MSI capability offset */
    rt_uint8_t msix_cap;                                    /**< MSI-X capability offset */
    rt_uint8_t pcie_cap;                                    /**< PCI Express capability offset */

    rt_uint8_t busmaster:1;             /**< Bus master (DMA capable) is enabled */
    rt_uint8_t multi_function:1;        /**< Multi-function device (bit 7 of header type) */
    rt_uint8_t ari_enabled:1;           /**< Alternative Routing-ID Interpretation enabled */
    rt_uint8_t no_msi:1;                /**< MSI is not available for this device */
    rt_uint8_t no_64bit_msi:1;          /**< Device only supports 32-bit MSI addresses */
    rt_uint8_t msi_enabled:1;           /**< MSI is currently enabled */
    rt_uint8_t msix_enabled:1;          /**< MSI-X is currently enabled */
    rt_uint8_t broken_intx_masking:1;   /**< INTx masking does not work on this device */
    rt_uint8_t pme_support:5;           /**< Bitmask of power states from which PME# can be generated */

#ifdef RT_PCI_MSI
    void *msix_base;                     /**< Virtual address of the MSI-X table */
    struct rt_pic *msi_pic;             /**< MSI interrupt controller for this device */
    rt_list_t msi_desc_nodes;            /**< List of MSI/MSI-X descriptors */
    struct rt_spinlock msi_lock;         /**< Spinlock for MSI descriptor operations */
#endif
};

/**
 * @brief PCI host bridge descriptor
 *
 * Represents the PCI host bridge (root complex). Manages bus address
 * regions, DMA regions, IRQ routing, and the root PCI bus.
 */
struct rt_pci_host_bridge
{
    struct rt_device parent;                               /**< Inherited RT-Thread device */

    rt_uint32_t domain;                                     /**< PCI domain number */

    struct rt_pci_bus *root_bus;                            /**< Root PCI bus */
    const struct rt_pci_ops *ops;                           /**< Root bus operations */
    const struct rt_pci_ops *child_ops;                     /**< Child bus operations */

    rt_uint32_t bus_range[2];                               /**< [start_bus, end_bus] range from device tree */
    rt_size_t bus_regions_nr;                               /**< Number of bus address regions */
    struct rt_pci_bus_region *bus_regions;                  /**< Bus address regions (CPU → PCI) */
    rt_size_t dma_regions_nr;                               /**< Number of DMA address regions */
    struct rt_pci_bus_region *dma_regions;                  /**< DMA address regions (PCI → CPU) */

    rt_uint8_t (*irq_slot)(struct rt_pci_device *pdev, rt_uint8_t *pinp);  /**< INTx swizzling callback */
    int (*irq_map)(struct rt_pci_device *pdev, rt_uint8_t slot, rt_uint8_t pin);  /**< IRQ mapping callback */

    void *sysdata;                                           /**< System-private data */
    rt_uint8_t priv[0];                                     /**< Variable-length private data */
};
/** @brief Cast a rt_device to its containing rt_pci_host_bridge */
#define rt_device_to_pci_host_bridge(dev) rt_container_of(dev, struct rt_pci_host_bridge, parent)

/**
 * @brief PCI bus operations vtable
 *
 * Each PCI bus (root bus or child bus) has its own set of operations
 * for configuration space access and bus lifecycle management.
 */
struct rt_pci_ops
{
    rt_err_t (*add)(struct rt_pci_bus *bus);     /**< Called when a new bus is added */
    rt_err_t (*remove)(struct rt_pci_bus *bus);  /**< Called when a bus is being removed */

    void *(*map)(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg);  /**< Map config space register to virtual addr */

    rt_err_t (*read)(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t *value);   /**< Read from config space */
    rt_err_t (*write)(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t value);    /**< Write to config space */
};

/**
 * @brief PCI bus descriptor
 *
 * Each PCI bus in the topology is represented by this structure.
 * Buses form a tree: root bus → bridge bus → child bus.
 * The union self/host_bridge disambiguates root buses from
 * PCI-to-PCI bridge buses.
 */
struct rt_pci_bus
{
    rt_list_t list;                      /**< Node in parent's children_nodes */
    rt_list_t children_nodes;            /**< List of child buses */
    rt_list_t devices_nodes;             /**< List of devices on this bus */
    struct rt_pci_bus *parent;           /**< Parent bus (NULL for root bus) */

    union
    {
        /* In PCI-to-PCI bridge, parent is not NULL */
        struct rt_pci_device *self;      /**< Bridge device that created this bus */
        /* In Host bridge, this is Root bus ('PCI Bus 0') */
        struct rt_pci_host_bridge *host_bridge;  /**< Host bridge for root bus */
    };

    const struct rt_pci_ops *ops;        /**< Bus-level PCI operations */

    char name[48];                       /**< Bus name (e.g., "0000:00") */
    char number;                         /**< Bus number (0-255) */
    struct rt_spinlock lock;             /**< Spinlock for bus-level operations */

    void *sysdata;                       /**< System-private data (e.g., ECAM config window) */
};

/**
 * @brief PCI driver descriptor
 *
 * Each PCI device driver provides this structure, including a device ID
 * table for matching and probe/remove/shutdown callbacks.
 */
struct rt_pci_driver
{
    struct rt_driver parent;                               /**< Inherited RT-Thread driver */

    const char *name;                                       /**< Driver name */
    const struct rt_pci_device_id *ids;                    /**< Device ID table (terminated by sentinel) */

    rt_err_t (*probe)(struct rt_pci_device *pdev);         /**< Probe callback: initialize a matched device */
    rt_err_t (*remove)(struct rt_pci_device *pdev);        /**< Remove callback: deinitialize a device */
    rt_err_t (*shutdown)(struct rt_pci_device *pdev);      /**< Shutdown callback: prepare for power-off */
};

/**
 * @brief MSI-X entry specification for vector allocation
 *
 * Used when allocating MSI-X vectors to specify which table entries
 * to use. On return, irq is filled with the assigned IRQ number.
 */
struct rt_pci_msix_entry
{
    int irq;         /**< Assigned IRQ number (filled on return) */
    int index;       /**< Requested MSI-X table entry index */
};

/**
 * @brief PCI device power states (D0-D3)
 *
 * Standard PCI power management states. D0 is fully operational;
 * D3cold is the deepest sleep with no auxiliary power.
 */
enum rt_pci_power
{
    RT_PCI_D0,       /**< Fully operational */
    RT_PCI_D1,       /**< Light sleep */
    RT_PCI_D2,       /**< Medium sleep */
    RT_PCI_D3HOT,    /**< Deep sleep, auxiliary power available */
    RT_PCI_D3COLD,   /**< Deep sleep, no auxiliary power (Vcc removed) */

    RT_PCI_PME_MAX,  /**< Sentinel: number of power states */
};

/* === PME (Power Management Event) API === */

/** @brief Initialize PME capability for a device */
void rt_pci_pme_init(struct rt_pci_device *pdev);

/** @brief Activate or deactivate PME# signal and manage power domain */
void rt_pci_pme_active(struct rt_pci_device *pdev, rt_bool_t enable);

/** @brief Enable or disable device wake-up from a given power state */
rt_err_t rt_pci_enable_wake(struct rt_pci_device *pci_dev,
        enum rt_pci_power state, rt_bool_t enable);

/**
 * @brief Check if a device can generate PME# from a given power state
 *
 * @param[in] pdev   PCI device
 * @param[in] state  Power state to check
 *
 * @return RT_TRUE if PME# can be generated from this state
 */
rt_inline rt_bool_t rt_pci_pme_capable(struct rt_pci_device *pdev,
        enum rt_pci_power state)
{
    if (!pdev->pme_cap)
    {
        return RT_FALSE;
    }

    return !!(pdev->pme_support & (1 << state));
}

/* === MSI Initialization === */

/** @brief Initialize MSI capability (disables MSI if enabled) */
void rt_pci_msi_init(struct rt_pci_device *pdev);

/** @brief Initialize MSI-X capability (disables MSI-X if enabled) */
void rt_pci_msix_init(struct rt_pci_device *pdev);

/* === Bus Master Control === */

/** @brief Enable bus mastering (DMA capability) */
void rt_pci_set_master(struct rt_pci_device *pdev);

/** @brief Disable bus mastering */
void rt_pci_clear_master(struct rt_pci_device *pdev);

/* === Host Bridge Lifecycle === */

/** @brief Allocate a PCI host bridge structure with private data space */
struct rt_pci_host_bridge *rt_pci_host_bridge_alloc(rt_size_t priv_size);

/** @brief Free a host bridge and its associated bus/DMA regions */
rt_err_t rt_pci_host_bridge_free(struct rt_pci_host_bridge *);

/** @brief Initialize a host bridge from device tree data */
rt_err_t rt_pci_host_bridge_init(struct rt_pci_host_bridge *host_bridge);

/** @brief Probe a host bridge: register root bus and scan for devices */
rt_err_t rt_pci_host_bridge_probe(struct rt_pci_host_bridge *host_bridge);

/* === Device Probing === */

/** @brief Allocate and initialize a new PCI device on a bus */
struct rt_pci_device *rt_pci_alloc_device(struct rt_pci_bus *bus);

/** @brief Scan and probe a single PCI device at a given devfn */
struct rt_pci_device *rt_pci_scan_single_device(struct rt_pci_bus *bus, rt_uint32_t devfn);

/** @brief Complete PCI device setup: read config, allocate BARs, init capabilities */
rt_err_t rt_pci_setup_device(struct rt_pci_device *pdev);

/** @brief Scan all functions in a PCI slot */
rt_size_t rt_pci_scan_slot(struct rt_pci_bus *bus, rt_uint32_t devfn);

/** @brief Recursively scan child buses with a bus count limit */
rt_uint32_t rt_pci_scan_child_buses(struct rt_pci_bus *bus, rt_size_t buses);

/** @brief Scan all child buses of a PCI bus (unlimited buses) */
rt_uint32_t rt_pci_scan_child_bus(struct rt_pci_bus *bus);

/* === Bus Management === */

/** @brief Register a host bridge's root bus */
rt_err_t rt_pci_host_bridge_register(struct rt_pci_host_bridge *host_bridge);

/** @brief Register a host bridge and scan its root bus */
rt_err_t rt_pci_scan_root_bus_bridge(struct rt_pci_host_bridge *host_bridge);

/* === Teardown === */

/** @brief Remove a host bridge and all its devices */
rt_err_t rt_pci_host_bridge_remove(struct rt_pci_host_bridge *host_bridge);

/** @brief Remove a PCI bus (only if it has no children or devices) */
rt_err_t rt_pci_bus_remove(struct rt_pci_bus *bus);

/** @brief Remove a PCI device from its bus */
rt_err_t rt_pci_device_remove(struct rt_pci_device *pdev);

/* === Domain and Bus Access === */

/** @brief Get the PCI domain number for a device */
rt_uint32_t rt_pci_domain(struct rt_pci_device *pdev);

/* === Capability Discovery === */

/** @brief Find a standard PCI capability by ID on a bus/devfn */
rt_uint8_t rt_pci_bus_find_capability(struct rt_pci_bus *bus, rt_uint32_t devfn, int cap);

/** @brief Find a standard PCI capability on a device */
rt_uint8_t rt_pci_find_capability(struct rt_pci_device *pdev, int cap);

/** @brief Find the next instance of a capability (continue from a previous find) */
rt_uint8_t rt_pci_find_next_capability(struct rt_pci_device *pdev, rt_uint8_t pos, int cap);

/** @brief Find a PCIe extended capability on a device */
rt_uint16_t rt_pci_find_ext_capability(struct rt_pci_device *pdev, int cap);

/** @brief Find the next PCIe extended capability starting from a given position */
rt_uint16_t rt_pci_find_ext_next_capability(struct rt_pci_device *pdev, rt_uint16_t pos, int cap);

/* === Bus Hierarchy === */

/** @brief Find the root PCI bus by walking up the parent chain */
struct rt_pci_bus *rt_pci_find_root_bus(struct rt_pci_bus *bus);

/** @brief Find the host bridge for a given PCI bus */
struct rt_pci_host_bridge *rt_pci_find_host_bridge(struct rt_pci_bus *bus);

/**
 * @brief Get the 16-bit Requester ID for a PCI device
 *
 * RID = (bus << 8) | devfn, used for MSI mapping and DMA routing.
 *
 * @param[in] pdev  PCI device
 *
 * @return Requester ID
 */
rt_inline rt_uint16_t rt_pci_dev_id(struct rt_pci_device *pdev)
{
    return RT_PCI_DEVID(pdev->bus->number, pdev->devfn);
}

/**
 * @brief Check if a PCI bus is the root bus
 *
 * @param[in] bus  PCI bus
 *
 * @return RT_TRUE if this is the root bus (no parent)
 */
rt_inline rt_bool_t rt_pci_is_root_bus(struct rt_pci_bus *bus)
{
    return bus->parent ? RT_FALSE : RT_TRUE;
}

/**
 * @brief Check if a PCI device is a bridge (PCI-to-PCI or CardBus)
 *
 * @param[in] pdev  PCI device
 *
 * @return RT_TRUE if the device is a bridge
 */
rt_inline rt_bool_t rt_pci_is_bridge(struct rt_pci_device *pdev)
{
    return pdev->hdr_type == PCIM_HDRTYPE_BRIDGE ||
            pdev->hdr_type == PCIM_HDRTYPE_CARDBUS;
}

/**
 * @brief Check if a PCI device supports PCI Express
 *
 * @param[in] pdev  PCI device
 *
 * @return RT_TRUE if the PCIe capability was found
 */
rt_inline rt_bool_t rt_pci_is_pcie(struct rt_pci_device *pdev)
{
    return !!pdev->pcie_cap;
}

/** @brief Iterate over all bridge devices on a PCI bus */
#define rt_pci_foreach_bridge(pdev, bus) \
    rt_list_for_each_entry(pdev, &bus->devices_nodes, list) \
        if (rt_pci_is_bridge(pdev))

/* === Configuration Space Access === */

/** @brief Read a byte from PCI config space via bus operations */
rt_err_t rt_pci_bus_read_config_u8(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int pos, rt_uint8_t *value);

/** @brief Read a halfword from PCI config space via bus operations */
rt_err_t rt_pci_bus_read_config_u16(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int pos, rt_uint16_t *value);

/** @brief Read a word from PCI config space via bus operations */
rt_err_t rt_pci_bus_read_config_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int pos, rt_uint32_t *value);

/** @brief Write a byte to PCI config space via bus operations */
rt_err_t rt_pci_bus_write_config_u8(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, rt_uint8_t value);

/** @brief Write a halfword to PCI config space via bus operations */
rt_err_t rt_pci_bus_write_config_u16(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, rt_uint16_t value);

/** @brief Write a word to PCI config space via bus operations */
rt_err_t rt_pci_bus_write_config_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, rt_uint32_t value);

/** @brief Read from config space with arbitrary width (memory-mapped access) */
rt_err_t rt_pci_bus_read_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t *value);

/** @brief Write to config space with arbitrary width (memory-mapped access) */
rt_err_t rt_pci_bus_write_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t value);

/** @brief Read with 32-bit access and sub-word extraction (for 32-bit-only controllers) */
rt_err_t rt_pci_bus_read_config_generic_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t *value);

/** @brief Write with read-modify-write for sub-32-bit access (for 32-bit-only controllers) */
rt_err_t rt_pci_bus_write_config_generic_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t value);

/* === Configuration Space Access (Device-Level Convenience) === */

/** @brief Read a byte from a PCI device's config space */
rt_inline rt_err_t rt_pci_read_config_u8(const struct rt_pci_device *pdev,
        int reg, rt_uint8_t *value)
{
    return rt_pci_bus_read_config_u8(pdev->bus, pdev->devfn, reg, value);
}

/** @brief Read a halfword from a PCI device's config space */
rt_inline rt_err_t rt_pci_read_config_u16(const struct rt_pci_device *pdev,
        int reg, rt_uint16_t *value)
{
    return rt_pci_bus_read_config_u16(pdev->bus, pdev->devfn, reg, value);
}

/** @brief Read a word from a PCI device's config space */
rt_inline rt_err_t rt_pci_read_config_u32(const struct rt_pci_device *pdev,
        int reg, rt_uint32_t *value)
{
    return rt_pci_bus_read_config_u32(pdev->bus, pdev->devfn, reg, value);
}

/** @brief Write a byte to a PCI device's config space */
rt_inline rt_err_t rt_pci_write_config_u8(const struct rt_pci_device *pdev,
        int reg, rt_uint8_t value)
{
    return rt_pci_bus_write_config_u8(pdev->bus, pdev->devfn, reg, value);
}

/** @brief Write a halfword to a PCI device's config space */
rt_inline rt_err_t rt_pci_write_config_u16(const struct rt_pci_device *pdev,
        int reg, rt_uint16_t value)
{
    return rt_pci_bus_write_config_u16(pdev->bus, pdev->devfn, reg, value);
}

/** @brief Write a word to a PCI device's config space */
rt_inline rt_err_t rt_pci_write_config_u32(const struct rt_pci_device *pdev,
        int reg, rt_uint32_t value)
{
    return rt_pci_bus_write_config_u32(pdev->bus, pdev->devfn, reg, value);
}

/* === Device Tree Integration === */

#ifdef RT_USING_OFW
/** @brief Parse and map an IRQ for a PCI device from device tree */
int rt_pci_ofw_irq_parse_and_map(struct rt_pci_device *pdev,
        rt_uint8_t slot, rt_uint8_t pin);

/** @brief Parse PCI bus address ranges from device tree */
rt_err_t rt_pci_ofw_parse_ranges(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge);

/** @brief Initialize a host bridge from device tree data */
rt_err_t rt_pci_ofw_host_bridge_init(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge);

/** @brief Initialize OFW data for a PCI bus */
rt_err_t rt_pci_ofw_bus_init(struct rt_pci_bus *bus);

/** @brief Free OFW data for a PCI bus */
rt_err_t rt_pci_ofw_bus_free(struct rt_pci_bus *bus);

/** @brief Associate a device tree node with an enumerated PCI device */
rt_err_t rt_pci_ofw_device_init(struct rt_pci_device *pdev);

/** @brief Release the device tree node reference for a PCI device */
rt_err_t rt_pci_ofw_device_free(struct rt_pci_device *pdev);
#else
rt_inline rt_err_t rt_pci_ofw_host_bridge_init(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge)
{
    return RT_EOK;
}
rt_inline rt_err_t rt_pci_ofw_bus_init(struct rt_pci_bus *bus)
{
    return RT_EOK;
}
rt_inline rt_err_t rt_pci_ofw_bus_free(struct rt_pci_bus *bus)
{
    return RT_EOK;
}
rt_inline rt_err_t rt_pci_ofw_device_init(struct rt_pci_device *pdev)
{
    return RT_EOK;
}
rt_inline rt_err_t rt_pci_ofw_device_free(struct rt_pci_device *pdev)
{
    return RT_EOK;
}
rt_inline int rt_pci_ofw_irq_parse_and_map(struct rt_pci_device *pdev,
        rt_uint8_t slot, rt_uint8_t pin)
{
    return -1;
}
rt_inline rt_err_t rt_pci_ofw_parse_ranges(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge)
{
    return -RT_ENOSYS;
}
#endif /* RT_USING_OFW */

/**
 * @brief I/O-map a PCI device's BAR for CPU access
 *
 * Maps the physical BAR address range into kernel virtual address space.
 *
 * @param[in] pdev     PCI device
 * @param[in] bar_idx  BAR index (0-5)
 *
 * @return Kernel virtual address of the mapped BAR
 */
rt_inline void *rt_pci_iomap(struct rt_pci_device *pdev, int bar_idx)
{
    struct rt_pci_bus_resource *res = &pdev->resource[bar_idx];

    RT_ASSERT(bar_idx < RT_ARRAY_SIZE(pdev->resource));

    return rt_ioremap((void *)res->base, res->size);
}

/* === INTx Interrupt Routing === */

/** @brief Perform INTx swizzling for a single bridge level */
rt_uint8_t rt_pci_irq_intx(struct rt_pci_device *pdev, rt_uint8_t pin);

/** @brief Perform INTx swizzling through all bridge levels */
rt_uint8_t rt_pci_irq_slot(struct rt_pci_device *pdev, rt_uint8_t *pinp);

/* === IRQ Management === */

/** @brief Assign an IRQ to a PCI device (reads pin, swizzles, maps, writes int_line) */
void rt_pci_assign_irq(struct rt_pci_device *pdev);

/** @brief Enable or disable legacy INTx interrupts */
void rt_pci_intx(struct rt_pci_device *pdev, rt_bool_t enable);

/** @brief Check if device generated an INTx and mask it (for interrupt handlers) */
rt_bool_t rt_pci_check_and_mask_intx(struct rt_pci_device *pdev);

/** @brief Check interrupt status and unmask INTx */
rt_bool_t rt_pci_check_and_unmask_intx(struct rt_pci_device *pdev);

/** @brief Mask a device's interrupt at the controller level */
void rt_pci_irq_mask(struct rt_pci_device *pdev);

/** @brief Unmask a device's interrupt at the controller level */
void rt_pci_irq_unmask(struct rt_pci_device *pdev);

/* === IRQ Allocation Flags === */

/** @brief Allow legacy INTx interrupts */
#define RT_PCI_IRQ_F_LEGACY     RT_BIT(0)
/** @brief Allow MSI interrupts */
#define RT_PCI_IRQ_F_MSI        RT_BIT(1)
/** @brief Allow MSI-X interrupts */
#define RT_PCI_IRQ_F_MSIX       RT_BIT(2)
/** @brief Auto-assign CPU affinity */
#define RT_PCI_IRQ_F_AFFINITY   RT_BIT(3)
/** @brief All interrupt types combined */
#define RT_PCI_IRQ_F_ALL_TYPES  (RT_PCI_IRQ_F_LEGACY | RT_PCI_IRQ_F_MSI | RT_PCI_IRQ_F_MSIX)

/* === MSI/MSI-X Vector Allocation === */

#ifdef RT_PCI_MSI
/** @brief Allocate interrupt vectors for a PCI device (MSI-X > MSI > INTx fallback) */
rt_ssize_t rt_pci_alloc_vector(struct rt_pci_device *pdev, int min, int max,
        rt_uint32_t flags, RT_IRQ_AFFINITY_DECLARE((*affinities)));

/** @brief Free all vectors allocated for a PCI device */
void rt_pci_free_vector(struct rt_pci_device *pdev);

/** @brief Get the number of MSI vectors the device supports */
rt_ssize_t rt_pci_msi_vector_count(struct rt_pci_device *pdev);

/** @brief Disable MSI on a device */
rt_err_t rt_pci_msi_disable(struct rt_pci_device *pdev);

/** @brief Enable MSI with a range of vectors and CPU affinity */
rt_ssize_t rt_pci_msi_enable_range_affinity(struct rt_pci_device *pdev,
        int min, int max, RT_IRQ_AFFINITY_DECLARE((*affinities)));

/** @brief Get the number of MSI-X table entries the device supports */
rt_ssize_t rt_pci_msix_vector_count(struct rt_pci_device *pdev);

/** @brief Disable MSI-X on a device */
rt_err_t rt_pci_msix_disable(struct rt_pci_device *pdev);

/** @brief Enable MSI-X with a range of vectors and CPU affinity */
rt_ssize_t rt_pci_msix_enable_range_affinity(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int min, int max,
        RT_IRQ_AFFINITY_DECLARE((*affinities)));
#else
rt_inline rt_ssize_t rt_pci_alloc_vector(struct rt_pci_device *pdev, int min, int max,
        rt_uint32_t flags, RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    return -RT_ENOSYS;
}

rt_inline void rt_pci_free_vector(struct rt_pci_device *pdev)
{
    return;
}

rt_inline rt_ssize_t rt_pci_msi_vector_count(struct rt_pci_device *pdev)
{
    return 0;
}

rt_inline rt_err_t rt_pci_msi_disable(struct rt_pci_device *pdev)
{
    return RT_EOK;
}

rt_inline rt_ssize_t rt_pci_msi_enable_range_affinity(struct rt_pci_device *pdev,
        int min, int max, RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    return -RT_ENOSYS;
}

rt_inline rt_ssize_t rt_pci_msix_vector_count(struct rt_pci_device *pdev)
{
    return 0;
}

rt_inline rt_err_t rt_pci_msix_disable(struct rt_pci_device *pdev)
{
    return RT_EOK;
}

rt_inline rt_ssize_t rt_pci_msix_enable_range_affinity(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int min, int max,
        RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    return -RT_ENOSYS;
}
#endif /* RT_PCI_MSI */

/**
 * @brief Initialize MSI-X entries with linear (sequential) indexing
 *
 * @param[in] entries    MSI-X entry array
 * @param[in] nvectors   Number of entries
 */
rt_inline void rt_pci_msix_entry_index_linear(struct rt_pci_msix_entry *entries,
        rt_size_t nvectors)
{
    for (int i = 0; i < nvectors; ++i)
    {
        entries[i].index = i;
    }
}

/**
 * @brief Enable MSI with a range of vectors (no affinity)
 *
 * @param[in] pdev  PCI device
 * @param[in] min   Minimum vectors
 * @param[in] max   Maximum vectors
 *
 * @return Number of vectors on success, negative error otherwise
 */
rt_inline rt_ssize_t rt_pci_msi_enable_range(struct rt_pci_device *pdev,
        int min, int max)
{
    return rt_pci_msi_enable_range_affinity(pdev, min, max, RT_NULL);
}

/**
 * @brief Enable a single MSI vector
 *
 * @param[in] pdev  PCI device
 *
 * @return RT_EOK on success
 */
rt_inline rt_err_t rt_pci_msi_enable(struct rt_pci_device *pdev)
{
    rt_ssize_t res = rt_pci_msi_enable_range(pdev, 1, 1);
    return res == 1 ? res : RT_EOK;
}

/**
 * @brief Enable MSI-X with a range of vectors (no affinity)
 *
 * @param[in] pdev     PCI device
 * @param[in] entries  MSI-X entry specifications
 * @param[in] min      Minimum vectors
 * @param[in] max      Maximum vectors
 *
 * @return Number of vectors on success, negative error otherwise
 */
rt_inline rt_ssize_t rt_pci_msix_enable_range(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int min, int max)
{
    return rt_pci_msix_enable_range_affinity(pdev, entries, min, max, RT_NULL);
}

/**
 * @brief Enable MSI-X with exactly count vectors (no affinity)
 *
 * @param[in] pdev     PCI device
 * @param[in] entries  MSI-X entry specifications
 * @param[in] count    Exact number of vectors
 *
 * @return Count on success, negative error otherwise
 */
rt_inline rt_ssize_t rt_pci_msix_enable(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int count)
{
    return rt_pci_msix_enable_range(pdev, entries, count, count);
}

/* === Resource Management === */

/** @brief Initialize bus resource regions with safe starting addresses */
rt_err_t rt_pci_region_setup(struct rt_pci_host_bridge *host_bridge);

/** @brief Allocate bus address space from the host bridge's regions */
struct rt_pci_bus_region *rt_pci_region_alloc(struct rt_pci_host_bridge *host_bridge,
        void **out_addr, rt_size_t size, rt_ubase_t flags, rt_bool_t mem64);

/** @brief Allocate BAR and ROM resources for a device */
rt_err_t rt_pci_device_alloc_resource(struct rt_pci_host_bridge *host_bridge,
        struct rt_pci_device *pdev);

/* === Bus Enumeration === */

/** @brief Enumerate all PCI devices in a bus hierarchy with a callback */
void rt_pci_enum_device(struct rt_pci_bus *bus,
        rt_bool_t (callback(struct rt_pci_device *, void *)), void *data);

/* === Driver Matching === */

/** @brief Match a PCI device against a single device ID entry */
const struct rt_pci_device_id *rt_pci_match_id(struct rt_pci_device *pdev,
        const struct rt_pci_device_id *id);

/** @brief Match a PCI device against an array of device IDs */
const struct rt_pci_device_id *rt_pci_match_ids(struct rt_pci_device *pdev,
        const struct rt_pci_device_id *ids);

/* === Registration === */

/** @brief Register a PCI driver */
rt_err_t rt_pci_driver_register(struct rt_pci_driver *pdrv);

/** @brief Register a PCI device on the PCI bus */
rt_err_t rt_pci_device_register(struct rt_pci_device *pdev);

/** @brief Find a BAR resource by type flags and index */
struct rt_pci_bus_resource *rt_pci_find_bar(struct rt_pci_device* pdev,rt_ubase_t flags,int index);

/** @brief Export a PCI driver (built-in only) */
#define RT_PCI_DRIVER_EXPORT(driver)    RT_DRIVER_EXPORT(driver, pci, BUILIN)

/** @brief Global PCI configuration space spinlock */
extern struct rt_spinlock rt_pci_lock;

#endif /* __PCI_H__ */
