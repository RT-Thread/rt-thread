/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
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

struct rt_pci_msi_conf
{
    rt_uint32_t mask;
    rt_uint8_t mask_pos;
    int default_irq;

    struct
    {
        rt_uint8_t is_masking:1;
        rt_uint8_t is_64bit:1;
        rt_uint8_t multi_msg_max:3; /* log2 num of messages allocated */
        rt_uint8_t multi_msg_use:3; /* log2 num of messages supported */
    } cap;
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

struct rt_pci_msix_conf
{
    int index;

    rt_uint32_t msg_ctrl;
    void *table_base;
};

struct rt_pci_msi_msg
{
    rt_uint32_t address_lo;
    rt_uint32_t address_hi;
    rt_uint32_t data;
};

struct rt_pci_msi_desc
{
    rt_list_t list;

    int irq;
    rt_size_t vector_used;
    rt_size_t vector_count;

    union
    {
        /* For MSI-X */
        rt_bitmap_t *affinity;
        /* For MSI */
        rt_bitmap_t **affinities;
    };

    struct rt_pci_device *pdev;
    struct rt_pci_msi_msg msg;

    void *write_msi_msg_data;
    void (*write_msi_msg)(struct rt_pci_msi_desc *, void *);

    rt_bool_t is_msix;
    union
    {
        struct rt_pci_msi_conf msi;
        struct rt_pci_msix_conf msix;
    };

    void *priv;
};

#define rt_pci_msi_first_desc(pdev) \
    (rt_list_isempty(&(pdev)->msi_desc_nodes) ? RT_NULL : \
        rt_list_first_entry(&(pdev)->msi_desc_nodes, struct rt_pci_msi_desc, list))

#define rt_pci_msi_for_each_desc(pdev, desc) \
    rt_list_for_each_entry(desc, &(pdev)->msi_desc_nodes, list)

#define rt_pci_msix_table_size(flags) ((flags & PCIM_MSIXCTRL_TABLE_SIZE) + 1)

rt_err_t rt_pci_msi_setup_irqs(struct rt_pci_device *pdev, int nvec, int type);

void rt_pci_msi_shutdown(struct rt_pci_device *pdev);
void rt_pci_msix_shutdown(struct rt_pci_device *pdev);
void rt_pci_msi_free_irqs(struct rt_pci_device *pdev);
void rt_pci_msi_write_msg(struct rt_pci_msi_desc *desc, struct rt_pci_msi_msg *msg);

void rt_pci_msi_mask_irq(struct rt_pic_irq *pirq);
void rt_pci_msi_unmask_irq(struct rt_pic_irq *pirq);

#endif /* __PCI_MSI_H__ */
