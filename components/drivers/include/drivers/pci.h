/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
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

#define RT_PCI_INTX_PIN_MAX         4
#define RT_PCI_BAR_NR_MAX           6
#define RT_PCI_DEVICE_MAX           32
#define RT_PCI_FUNCTION_MAX         8

#define RT_PCI_FIND_CAP_TTL         48

/*
 * The PCI interface treats multi-function devices as independent
 * devices.  The slot/function address of each device is encoded
 * in a single byte as follows:
 *
 *  7:3 = slot
 *  2:0 = function
 */
#define RT_PCI_DEVID(bus, devfn)    ((((rt_uint16_t)(bus)) << 8) | (devfn))
#define RT_PCI_DEVFN(slot, func)    ((((slot) & 0x1f) << 3) | ((func) & 0x07))
#define RT_PCI_SLOT(devfn)          (((devfn) >> 3) & 0x1f)
#define RT_PCI_FUNC(devfn)          ((devfn) & 0x07)

#define PCIE_LINK_STATE_L0S         RT_BIT(0)
#define PCIE_LINK_STATE_L1          RT_BIT(1)
#define PCIE_LINK_STATE_CLKPM       RT_BIT(2)
#define PCIE_LINK_STATE_L1_1        RT_BIT(3)
#define PCIE_LINK_STATE_L1_2        RT_BIT(4)
#define PCIE_LINK_STATE_L1_1_PCIPM  RT_BIT(5)
#define PCIE_LINK_STATE_L1_2_PCIPM  RT_BIT(6)
#define PCIE_LINK_STATE_ALL         \
( \
    PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 | \
    PCIE_LINK_STATE_CLKPM | \
    PCIE_LINK_STATE_L1_1 | PCIE_LINK_STATE_L1_2 | \
    PCIE_LINK_STATE_L1_1_PCIPM | PCIE_LINK_STATE_L1_2_PCIPM \
)

struct rt_pci_bus_region
{
    rt_uint64_t phy_addr;
    rt_uint64_t cpu_addr;
    rt_uint64_t size;

    rt_uint64_t bus_start;

#define PCI_BUS_REGION_F_NONE       0xffffffff    /* PCI no memory */
#define PCI_BUS_REGION_F_MEM        0x00000000    /* PCI memory space */
#define PCI_BUS_REGION_F_IO         0x00000001    /* PCI IO space */
#define PCI_BUS_REGION_F_PREFETCH   0x00000008    /* Prefetchable PCI memory */
    rt_ubase_t flags;
};

struct rt_pci_bus_resource
{
    rt_ubase_t base;
    rt_size_t size;

    rt_ubase_t flags;
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

struct rt_pci_device_id
{
#define PCI_ANY_ID   (~0)
#define RT_PCI_DEVICE_ID(vend, dev) \
    .vendor = (vend),               \
    .device = (dev),                \
    .subsystem_vendor = PCI_ANY_ID, \
    .subsystem_device = PCI_ANY_ID

#define RT_PCI_DEVICE_CLASS(dev_class, dev_class_mask)  \
    .vendor = PCI_ANY_ID, .device = PCI_ANY_ID,         \
    .subsystem_vendor = PCI_ANY_ID,                     \
    .subsystem_device = PCI_ANY_ID,                     \
    .class = (dev_class), .class_mask = (dev_class_mask),

    rt_uint32_t vendor, device;     /* Vendor and device ID or PCI_ANY_ID */
    rt_uint32_t subsystem_vendor;   /* Subsystem ID's or PCI_ANY_ID */
    rt_uint32_t subsystem_device;   /* Subsystem ID's or PCI_ANY_ID */
    rt_uint32_t class, class_mask;  /* (class, subclass, prog-if) triplet */

    const void *data;
};

struct rt_pci_device
{
    struct rt_device parent;
    const char *name;

    rt_list_t list;
    struct rt_pci_bus *bus;
    struct rt_pci_bus *subbus;      /* In PCI-to-PCI bridge, 'End Point' or 'Port' is NULL */

    const struct rt_pci_device_id *id;

    rt_uint32_t devfn;              /* Encoded device & function index */
    rt_uint16_t vendor;
    rt_uint16_t device;
    rt_uint16_t subsystem_vendor;
    rt_uint16_t subsystem_device;
    rt_uint32_t class;              /* 3 bytes: (base, sub, prog-if) */
    rt_uint8_t revision;
    rt_uint8_t hdr_type;
    rt_uint8_t max_latency;
    rt_uint8_t min_grantl;
    rt_uint8_t int_pin;
    rt_uint8_t int_line;
    rt_uint16_t exp_flags;
    rt_uint32_t cfg_size;

    void *sysdata;

    int irq;
    rt_uint8_t pin;
    struct rt_pic *intx_pic;

    struct rt_pci_bus_resource resource[RT_PCI_BAR_NR_MAX];

    rt_uint8_t pme_cap;
    rt_uint8_t msi_cap;
    rt_uint8_t msix_cap;
    rt_uint8_t pcie_cap;

    rt_uint8_t busmaster:1;             /* Is the bus master */
    rt_uint8_t multi_function:1;        /* Multi-function device */
    rt_uint8_t ari_enabled:1;           /* Alternative Routing-ID Interpretation */
    rt_uint8_t no_msi:1;                /* May not use MSI */
    rt_uint8_t no_64bit_msi:1;          /* May only use 32-bit MSIs */
    rt_uint8_t msi_enabled:1;           /* MSI enable */
    rt_uint8_t msix_enabled:1;          /* MSIx enable */
    rt_uint8_t broken_intx_masking:1;   /* INTx masking can't be used */
    rt_uint8_t pme_support:5;           /* Bitmask of states from which PME# can be generated */

#ifdef RT_PCI_MSI
    void *msix_base;
    struct rt_pic *msi_pic;
    rt_list_t msi_desc_nodes;
    struct rt_spinlock msi_lock;
#endif
};

struct rt_pci_host_bridge
{
    struct rt_device parent;

    rt_uint32_t domain;

    struct rt_pci_bus *root_bus;
    const struct rt_pci_ops *ops;
    const struct rt_pci_ops *child_ops;

    rt_uint32_t bus_range[2];
    rt_size_t bus_regions_nr;
    struct rt_pci_bus_region *bus_regions;
    rt_size_t dma_regions_nr;
    struct rt_pci_bus_region *dma_regions;

    rt_uint8_t (*irq_slot)(struct rt_pci_device *pdev, rt_uint8_t *pinp);
    int (*irq_map)(struct rt_pci_device *pdev, rt_uint8_t slot, rt_uint8_t pin);

    void *sysdata;
    rt_uint8_t priv[0];
};
#define rt_device_to_pci_host_bridge(dev) rt_container_of(dev, struct rt_pci_host_bridge, parent)

struct rt_pci_ops
{
    rt_err_t (*add)(struct rt_pci_bus *bus);
    rt_err_t (*remove)(struct rt_pci_bus *bus);

    void *(*map)(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg);

    rt_err_t (*read)(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t *value);
    rt_err_t (*write)(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t value);
};

struct rt_pci_bus
{
    rt_list_t list;
    rt_list_t children_nodes;
    rt_list_t devices_nodes;
    struct rt_pci_bus *parent;

    union
    {
        /* In PCI-to-PCI bridge, parent is not NULL */
        struct rt_pci_device *self;
        /* In Host bridge, this is Root bus ('PCI Bus 0') */
        struct rt_pci_host_bridge *host_bridge;
    };

    const struct rt_pci_ops *ops;

    char name[48];
    char number;
    struct rt_spinlock lock;

    void *sysdata;
};

struct rt_pci_driver
{
    struct rt_driver parent;

    const char *name;
    const struct rt_pci_device_id *ids;

    rt_err_t (*probe)(struct rt_pci_device *pdev);
    rt_err_t (*remove)(struct rt_pci_device *pdev);
    rt_err_t (*shutdown)(struct rt_pci_device *pdev);
};

struct rt_pci_msix_entry
{
    int irq;
    int index;
};

enum rt_pci_power
{
    RT_PCI_D0,
    RT_PCI_D1,
    RT_PCI_D2,
    RT_PCI_D3HOT,
    RT_PCI_D3COLD,

    RT_PCI_PME_MAX,
};

void rt_pci_pme_init(struct rt_pci_device *pdev);
void rt_pci_pme_active(struct rt_pci_device *pdev, rt_bool_t enable);
rt_err_t rt_pci_enable_wake(struct rt_pci_device *pci_dev,
        enum rt_pci_power state, rt_bool_t enable);
rt_inline rt_bool_t rt_pci_pme_capable(struct rt_pci_device *pdev,
        enum rt_pci_power state)
{
    if (!pdev->pme_cap)
    {
        return RT_FALSE;
    }

    return !!(pdev->pme_support & (1 << state));
}

void rt_pci_msi_init(struct rt_pci_device *pdev);
void rt_pci_msix_init(struct rt_pci_device *pdev);

void rt_pci_set_master(struct rt_pci_device *pdev);
void rt_pci_clear_master(struct rt_pci_device *pdev);

struct rt_pci_host_bridge *rt_pci_host_bridge_alloc(rt_size_t priv_size);
rt_err_t rt_pci_host_bridge_free(struct rt_pci_host_bridge *);
rt_err_t rt_pci_host_bridge_init(struct rt_pci_host_bridge *host_bridge);
rt_err_t rt_pci_host_bridge_probe(struct rt_pci_host_bridge *host_bridge);

struct rt_pci_device *rt_pci_alloc_device(struct rt_pci_bus *bus);
struct rt_pci_device *rt_pci_scan_single_device(struct rt_pci_bus *bus, rt_uint32_t devfn);
rt_err_t rt_pci_setup_device(struct rt_pci_device *pdev);
rt_size_t rt_pci_scan_slot(struct rt_pci_bus *bus, rt_uint32_t devfn);
rt_uint32_t rt_pci_scan_child_buses(struct rt_pci_bus *bus, rt_size_t buses);
rt_uint32_t rt_pci_scan_child_bus(struct rt_pci_bus *bus);

rt_err_t rt_pci_host_bridge_register(struct rt_pci_host_bridge *host_bridge);
rt_err_t rt_pci_scan_root_bus_bridge(struct rt_pci_host_bridge *host_bridge);

rt_err_t rt_pci_host_bridge_remove(struct rt_pci_host_bridge *host_bridge);
rt_err_t rt_pci_bus_remove(struct rt_pci_bus *bus);
rt_err_t rt_pci_device_remove(struct rt_pci_device *pdev);

rt_uint32_t rt_pci_domain(struct rt_pci_device *pdev);

rt_uint8_t rt_pci_bus_find_capability(struct rt_pci_bus *bus, rt_uint32_t devfn, int cap);
rt_uint8_t rt_pci_find_capability(struct rt_pci_device *pdev, int cap);
rt_uint8_t rt_pci_find_next_capability(struct rt_pci_device *pdev, rt_uint8_t pos, int cap);

rt_uint16_t rt_pci_find_ext_capability(struct rt_pci_device *pdev, int cap);
rt_uint16_t rt_pci_find_ext_next_capability(struct rt_pci_device *pdev, rt_uint16_t pos, int cap);

struct rt_pci_bus *rt_pci_find_root_bus(struct rt_pci_bus *bus);
struct rt_pci_host_bridge *rt_pci_find_host_bridge(struct rt_pci_bus *bus);

rt_inline rt_uint16_t rt_pci_dev_id(struct rt_pci_device *pdev)
{
    return RT_PCI_DEVID(pdev->bus->number, pdev->devfn);
}

rt_inline rt_bool_t rt_pci_is_root_bus(struct rt_pci_bus *bus)
{
    return bus->parent ? RT_FALSE : RT_TRUE;
}

rt_inline rt_bool_t rt_pci_is_bridge(struct rt_pci_device *pdev)
{
    return pdev->hdr_type == PCIM_HDRTYPE_BRIDGE ||
            pdev->hdr_type == PCIM_HDRTYPE_CARDBUS;
}

rt_inline rt_bool_t rt_pci_is_pcie(struct rt_pci_device *pdev)
{
    return !!pdev->pcie_cap;
}

#define rt_pci_foreach_bridge(pdev, bus) \
    rt_list_for_each_entry(pdev, &bus->devices_nodes, list) \
        if (rt_pci_is_bridge(pdev))

rt_err_t rt_pci_bus_read_config_u8(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int pos, rt_uint8_t *value);
rt_err_t rt_pci_bus_read_config_u16(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int pos, rt_uint16_t *value);
rt_err_t rt_pci_bus_read_config_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int pos, rt_uint32_t *value);

rt_err_t rt_pci_bus_write_config_u8(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, rt_uint8_t value);
rt_err_t rt_pci_bus_write_config_u16(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, rt_uint16_t value);
rt_err_t rt_pci_bus_write_config_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, rt_uint32_t value);

rt_err_t rt_pci_bus_read_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t *value);
rt_err_t rt_pci_bus_write_config_uxx(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t value);

rt_err_t rt_pci_bus_read_config_generic_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t *value);
rt_err_t rt_pci_bus_write_config_generic_u32(struct rt_pci_bus *bus,
        rt_uint32_t devfn, int reg, int width, rt_uint32_t value);

rt_inline rt_err_t rt_pci_read_config_u8(const struct rt_pci_device *pdev,
        int reg, rt_uint8_t *value)
{
    return rt_pci_bus_read_config_u8(pdev->bus, pdev->devfn, reg, value);
}

rt_inline rt_err_t rt_pci_read_config_u16(const struct rt_pci_device *pdev,
        int reg, rt_uint16_t *value)
{
    return rt_pci_bus_read_config_u16(pdev->bus, pdev->devfn, reg, value);
}

rt_inline rt_err_t rt_pci_read_config_u32(const struct rt_pci_device *pdev,
        int reg, rt_uint32_t *value)
{
    return rt_pci_bus_read_config_u32(pdev->bus, pdev->devfn, reg, value);
}

rt_inline rt_err_t rt_pci_write_config_u8(const struct rt_pci_device *pdev,
        int reg, rt_uint8_t value)
{
    return rt_pci_bus_write_config_u8(pdev->bus, pdev->devfn, reg, value);
}

rt_inline rt_err_t rt_pci_write_config_u16(const struct rt_pci_device *pdev,
        int reg, rt_uint16_t value)
{
    return rt_pci_bus_write_config_u16(pdev->bus, pdev->devfn, reg, value);
}

rt_inline rt_err_t rt_pci_write_config_u32(const struct rt_pci_device *pdev,
        int reg, rt_uint32_t value)
{
    return rt_pci_bus_write_config_u32(pdev->bus, pdev->devfn, reg, value);
}

#ifdef RT_USING_OFW
int rt_pci_ofw_irq_parse_and_map(struct rt_pci_device *pdev,
        rt_uint8_t slot, rt_uint8_t pin);

rt_err_t rt_pci_ofw_parse_ranges(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge);

rt_err_t rt_pci_ofw_host_bridge_init(struct rt_ofw_node *dev_np,
        struct rt_pci_host_bridge *host_bridge);

rt_err_t rt_pci_ofw_bus_init(struct rt_pci_bus *bus);
rt_err_t rt_pci_ofw_bus_free(struct rt_pci_bus *bus);
rt_err_t rt_pci_ofw_device_init(struct rt_pci_device *pdev);
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

rt_inline void *rt_pci_iomap(struct rt_pci_device *pdev, int bar_idx)
{
    struct rt_pci_bus_resource *res = &pdev->resource[bar_idx];

    RT_ASSERT(bar_idx < RT_ARRAY_SIZE(pdev->resource));

    return rt_ioremap((void *)res->base, res->size);
}

rt_uint8_t rt_pci_irq_intx(struct rt_pci_device *pdev, rt_uint8_t pin);
rt_uint8_t rt_pci_irq_slot(struct rt_pci_device *pdev, rt_uint8_t *pinp);

void rt_pci_assign_irq(struct rt_pci_device *pdev);

void rt_pci_intx(struct rt_pci_device *pdev, rt_bool_t enable);
rt_bool_t rt_pci_check_and_mask_intx(struct rt_pci_device *pdev);
rt_bool_t rt_pci_check_and_unmask_intx(struct rt_pci_device *pdev);

void rt_pci_irq_mask(struct rt_pci_device *pdev);
void rt_pci_irq_unmask(struct rt_pci_device *pdev);

#define RT_PCI_IRQ_F_LEGACY     RT_BIT(0)   /* Allow legacy interrupts */
#define RT_PCI_IRQ_F_MSI        RT_BIT(1)   /* Allow MSI interrupts */
#define RT_PCI_IRQ_F_MSIX       RT_BIT(2)   /* Allow MSI-X interrupts */
#define RT_PCI_IRQ_F_AFFINITY   RT_BIT(3)   /* Auto-assign affinity */
#define RT_PCI_IRQ_F_ALL_TYPES  (RT_PCI_IRQ_F_LEGACY | RT_PCI_IRQ_F_MSI | RT_PCI_IRQ_F_MSIX)

#ifdef RT_PCI_MSI
rt_ssize_t rt_pci_alloc_vector(struct rt_pci_device *pdev, int min, int max,
        rt_uint32_t flags, RT_IRQ_AFFINITY_DECLARE((*affinities)));
void rt_pci_free_vector(struct rt_pci_device *pdev);

rt_ssize_t rt_pci_msi_vector_count(struct rt_pci_device *pdev);
rt_err_t rt_pci_msi_disable(struct rt_pci_device *pdev);
rt_ssize_t rt_pci_msi_enable_range_affinity(struct rt_pci_device *pdev,
        int min, int max, RT_IRQ_AFFINITY_DECLARE((*affinities)));

rt_ssize_t rt_pci_msix_vector_count(struct rt_pci_device *pdev);
rt_err_t rt_pci_msix_disable(struct rt_pci_device *pdev);
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

rt_inline void rt_pci_msix_entry_index_linear(struct rt_pci_msix_entry *entries,
        rt_size_t nvectors)
{
    for (int i = 0; i < nvectors; ++i)
    {
        entries[i].index = i;
    }
}

rt_inline rt_ssize_t rt_pci_msi_enable_range(struct rt_pci_device *pdev,
        int min, int max)
{
    return rt_pci_msi_enable_range_affinity(pdev, min, max, RT_NULL);
}

rt_inline rt_err_t rt_pci_msi_enable(struct rt_pci_device *pdev)
{
    rt_ssize_t res = rt_pci_msi_enable_range(pdev, 1, 1);
    return res == 1 ? res : RT_EOK;
}

rt_inline rt_ssize_t rt_pci_msix_enable_range(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int min, int max)
{
    return rt_pci_msix_enable_range_affinity(pdev, entries, min, max, RT_NULL);
}

rt_inline rt_ssize_t rt_pci_msix_enable(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int count)
{
    return rt_pci_msix_enable_range(pdev, entries, count, count);
}

rt_err_t rt_pci_region_setup(struct rt_pci_host_bridge *host_bridge);
struct rt_pci_bus_region *rt_pci_region_alloc(struct rt_pci_host_bridge *host_bridge,
        void **out_addr, rt_size_t size, rt_ubase_t flags, rt_bool_t mem64);

rt_err_t rt_pci_device_alloc_resource(struct rt_pci_host_bridge *host_bridge,
        struct rt_pci_device *pdev);

void rt_pci_enum_device(struct rt_pci_bus *bus,
        rt_bool_t (callback(struct rt_pci_device *, void *)), void *data);

const struct rt_pci_device_id *rt_pci_match_id(struct rt_pci_device *pdev,
        const struct rt_pci_device_id *id);

const struct rt_pci_device_id *rt_pci_match_ids(struct rt_pci_device *pdev,
        const struct rt_pci_device_id *ids);

rt_err_t rt_pci_driver_register(struct rt_pci_driver *pdrv);
rt_err_t rt_pci_device_register(struct rt_pci_device *pdev);
struct rt_pci_bus_resource *rt_pci_find_bar(struct rt_pci_device* pdev,rt_ubase_t flags,int index);
#define RT_PCI_DRIVER_EXPORT(driver)    RT_DRIVER_EXPORT(driver, pci, BUILIN)

extern struct rt_spinlock rt_pci_lock;

#endif /* __PCI_H__ */
