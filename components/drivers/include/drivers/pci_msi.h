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
 * @file pci_msi.h
 * @brief PCI MSI (Message Signaled Interrupts) and MSI-X data structures
 *
 * Defines the configuration descriptors and message format for MSI
 * and MSI-X interrupt mechanisms. MSI uses config-space registers;
 * MSI-X uses a memory-mapped table in a device BAR.
 */

#ifndef __PCI_MSI_H__
#define __PCI_MSI_H__

#include <drivers/pci.h>

/*
 * MSI Format:
 *  T0: 32-bit Address
 *  T1: 64-bit Address
 *  T2: 32-bit Address with Per-Vector Masking
 *  T3: 64-bit Address with Per-Vector Masking
 *
 *   31                      16  15              8 7             0
 *  +---------------------------+-----------------+---------------+
 *  |      Message Control      | Next Capability | Capability ID | DW0
 *  |                           |     Pointer     |     (05h)     |
 *  +---------------------------+-----------------+---------------+
 *  |                    Message Address [31:0]                   | DW1
 *  +-------------------------------------------------------------+
 *  |                    Message Address [63:32]                  | DW2 (T1: only 64-bit)
 *  +---------------------------+---------------------------------+
 *  |         Reserved          |           Message Data          | DW3
 *  +---------------------------+---------------------------------+
 *  |                       Mask Bits                             | DW4 (T2/T3: only with Per-Vector Masking)
 *  +-------------------------------------------------------------+
 *  |                      Pending Bits                           | DW5 (T2/T3: only with Per-Vector Masking)
 *  +-------------------------------------------------------------+
 *
 * MSI Message Control:
 *
 *   15                   9  8   7  6             4 3        1  0
 *  +----------------------+---+---+---------------+----------+---+
 *  |       Reserved       |   |   |               |          |   |
 *  +----------------------+---+---+---------------+----------+---+
 *                           ^   ^         ^             ^      ^
 *                           |   |         |             |      |
 *                           |   |         |             |      +---- MSI Enable (RW)
 *                           |   |         |             +----------- Multiple Message Capable (RO, log2n, [n <= 5])
 *                           |   |         +------------------------- Multiple Message Enable (RW, log2n, [n <= 5])
 *                           |   +----------------------------------- 64-bit Address Capable
 *                           +--------------------------------------- Per-Vector Masking Capable
 */

/**
 * @brief MSI capability configuration
 *
 * Holds the per-vector mask state, the mask register offset, the
 * default INTx IRQ (for fallback when MSI is disabled), and the
 * capability flags parsed from the MSI Message Control register.
 */
struct rt_pci_msi_conf
{
    rt_uint32_t mask;            /**< Current vector mask bits */
    rt_uint8_t mask_pos;         /**< Mask register offset in config space */
    int default_irq;             /**< Default INTx IRQ for fallback on MSI shutdown */

    struct
    {
        rt_uint8_t is_masking:1;     /**< Per-Vector Masking Capable (bit 8) */
        rt_uint8_t is_64bit:1;       /**< 64-bit Address Capable (bit 7) */
        rt_uint8_t multi_msg_max:3;  /**< Multiple Message Capable — log2 of max vectors (bits 3:1) */
        rt_uint8_t multi_msg_use:3;  /**< Multiple Message Enable — log2 of vectors in use (bits 6:4) */
    } cap; /**< Capability flags parsed from Message Control register */
};

/*
 * MSI-X Format:
 *
 *   31                      16  15              8 7             0
 *  +---------------------------+-----------------+---------------+
 *  |      Message Control      | Next Capability | Capability ID | DW0
 *  |                           |     Pointer     |     (11h)     |
 *  +---------------------------+-----------------+---+-----------+
 *  |                    MSI-X Table Offset           | Table BIR | DW1 (BIR: BAR Index Register)
 *  +-------------------------------------------------+-----------+               |
 *  |             Pending Bit Array (PBA) Offset      |  PBA BIR  | DW2 --------+ |
 *  +-------------------------------------------------+-----------+             | |
 *                                                                              | |
 * MSI-X Message Control:                                                       | |
 *                                                                              | |
 *   15 14 13      11 10                                         0              | |
 *  +---+---+----------+------------------------------------------+             | |
 *  |   |   | Reserved |         Table Size in N-1 (RO)           |             | |
 *  +---+---+----------+------------------------------------------+             | |
 *    ^   ^                                                                     | |
 *    |   |                                                                     | |
 *    |   +---- Function Mask (RW)                                              | |
 *    +-------- MSI-X Enable (RW)                                               | |
 *                                                                              | |
 * MSI-X Table (BAR[Table BIR] + MSI-X Table Offset):                           | |
 *                                                                              | |
 *          DW3            DW2             DW1             DW0                  | |
 *  +----------------+--------------+---------------+---------------+ <---------|-+
 *  | Vector Control | Message Data | Upper Address | Lower Address | Entry 0   |
 *  +----------------+--------------+---------------+---------------+           |
 *  | Vector Control | Message Data | Upper Address | Lower Address | Entry 1   |
 *  +----------------+--------------+---------------+---------------+           |
 *  |     ......     |    ......    |    ......     |    ......     |           |
 *  +----------------+--------------+---------------+---------------+           |
 *  | Vector Control | Message Data | Upper Address | Lower Address | Entry N-1 |
 *  +----------------+--------------+---------------+---------------+           |
 *                  ^                                                           |
 *                  |                                                           |
 *                  +---- Bit 0 is vector Mask Bit (R/W)                        |
 *                                                                              |
 * MSI-X Pending Bit Array (BAR[PBA BIR] + Pending Bit Array Offset):           |
 *                                                                              |
 *          DW1            DW0                                                  |
 *  +-------------------------------+ <-----------------------------------------+
 *  |     Pending Bits 0 - 63       | QW 0
 *  +-------------------------------+
 *  |    Pending Bits 64 - 127      | QW 1
 *  +-------------------------------+
 *  |            ......             |
 *  +-------------------------------+
 *  |         Pending Bits          | QW (N-1)/64
 *  +-------------------------------+
 */

/**
 * @brief MSI-X per-vector configuration
 *
 * Tracks a single MSI-X table entry's index, vector control value,
 * and the virtual address of the table in MMIO space.
 */
struct rt_pci_msix_conf
{
    int index;                   /**< Table entry index (0-based) */
    rt_uint32_t msg_ctrl;        /**< Saved vector control register value */
    void *table_base;            /**< Virtual address of the MSI-X table */
};

/**
 * @brief MSI/MSI-X message descriptor
 *
 * An MSI interrupt is essentially a posted memory write transaction.
 * The address (32 or 64 bits) and data values are programmed by the
 * interrupt controller (MSI PIC) and written to the device.
 */
struct rt_pci_msi_msg
{
    rt_uint32_t address_lo;      /**< Lower 32 bits of the message address */
    rt_uint32_t address_hi;      /**< Upper 32 bits of the message address (0 for 32-bit) */
    rt_uint32_t data;            /**< Message data (identifies the interrupt vector) */
};

/**
 * @brief MSI/MSI-X interrupt descriptor
 *
 * One descriptor per MSI group or per MSI-X table entry.
 * Stores the allocated IRQ number(s), CPU affinity information,
 * the composed MSI message, and capability-specific configuration.
 */
struct rt_pci_msi_desc
{
    rt_list_t list;              /**< Node in the device's msi_desc_nodes list */

    int irq;                     /**< Base IRQ number for MSI, or per-entry IRQ for MSI-X */
    rt_size_t vector_used;       /**< Number of vectors currently in use */
    rt_size_t vector_count;      /**< Total number of vectors this descriptor can handle */

    union
    {
        /* For MSI-X: single CPU affinity bitmap */
        rt_bitmap_t *affinity;
        /* For MSI: array of per-vector affinity bitmaps */
        rt_bitmap_t **affinities;
    };

    struct rt_pci_device *pdev;  /**< Owning PCI device */
    struct rt_pci_msi_msg msg;   /**< Current MSI message (address + data) */

    void *write_msi_msg_data;    /**< User data for write_msi_msg callback */
    void (*write_msi_msg)(struct rt_pci_msi_desc *, void *); /**< Custom MSI message write callback */

    rt_bool_t is_msix;           /**< RT_TRUE for MSI-X, RT_FALSE for MSI */
    union
    {
        struct rt_pci_msi_conf msi;    /**< MSI-specific config (when !is_msix) */
        struct rt_pci_msix_conf msix;  /**< MSI-X-specific config (when is_msix) */
    };

    void *priv;                  /**< PIC-private data */
};

/** @brief Get the first MSI descriptor for a device, or RT_NULL if none */
#define rt_pci_msi_first_desc(pdev) \
    (rt_list_isempty(&(pdev)->msi_desc_nodes) ? RT_NULL : \
        rt_list_first_entry(&(pdev)->msi_desc_nodes, struct rt_pci_msi_desc, list))

/** @brief Iterate over all MSI descriptors for a device */
#define rt_pci_msi_for_each_desc(pdev, desc) \
    rt_list_for_each_entry(desc, &(pdev)->msi_desc_nodes, list)

/** @brief Compute MSI-X table size from the Table Size field (N-1 encoding) */
#define rt_pci_msix_table_size(flags) ((flags & PCIM_MSIXCTRL_TABLE_SIZE) + 1)

/** @brief Set up MSI/MSI-X IRQs for a device */
rt_err_t rt_pci_msi_setup_irqs(struct rt_pci_device *pdev, int nvec, int type);

/** @brief Clean up (free) all MSI/MSI-X IRQs for a device */
rt_err_t rt_pci_msi_cleanup_irqs(struct rt_pci_device *pdev);

/** @brief Shutdown MSI: disable MSI, re-enable INTx */
void rt_pci_msi_shutdown(struct rt_pci_device *pdev);

/** @brief Shutdown MSI-X: mask all vectors, disable MSI-X, re-enable INTx */
void rt_pci_msix_shutdown(struct rt_pci_device *pdev);

/** @brief Free all IRQ resources for MSI/MSI-X on a device */
void rt_pci_msi_free_irqs(struct rt_pci_device *pdev);

/** @brief Write an MSI/MSI-X message to the device (address + data registers) */
void rt_pci_msi_write_msg(struct rt_pci_msi_desc *desc, struct rt_pci_msi_msg *msg);

/** @brief Mask an MSI/MSI-X IRQ at the device level */
void rt_pci_msi_mask_irq(struct rt_pic_irq *pirq);

/** @brief Unmask an MSI/MSI-X IRQ at the device level */
void rt_pci_msi_unmask_irq(struct rt_pic_irq *pirq);

#endif /* __PCI_MSI_H__ */
