/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#ifndef __PCI_ENDPOINT_H__
#define __PCI_ENDPOINT_H__

#include <drivers/pci.h>

enum rt_pci_ep_pin
{
    RT_PCI_EP_PIN_UNKNOWN,
    RT_PCI_EP_PIN_INTA,
    RT_PCI_EP_PIN_INTB,
    RT_PCI_EP_PIN_INTC,
    RT_PCI_EP_PIN_INTD,
};

enum rt_pci_ep_irq
{
    RT_PCI_EP_IRQ_UNKNOWN,
    RT_PCI_EP_IRQ_LEGACY,
    RT_PCI_EP_IRQ_MSI,
    RT_PCI_EP_IRQ_MSIX,
};

struct rt_pci_ep_header
{
    rt_uint16_t vendor;
    rt_uint16_t device;
    rt_uint8_t revision;
    rt_uint8_t progif;
    rt_uint8_t subclass;
    rt_uint8_t class_code;
    rt_uint8_t cache_line_size;
    rt_uint16_t subsystem_vendor;
    rt_uint16_t subsystem_device;

    enum rt_pci_ep_pin intx;
};

struct rt_pci_ep_bar
{
    /* To PCI Bus */
    struct rt_pci_bus_resource bus;
    /* To CPU */
    rt_ubase_t cpu_addr;
};

/*
 * Type of MSI-X table, For more format detail,
 * please read `components/drivers/include/drivers/pci_msi.h`
 */
struct rt_pci_ep_msix_tbl
{
    union
    {
        rt_uint64_t msg_addr;
        struct
        {
            rt_uint32_t msg_addr_upper;
            rt_uint32_t msg_addr_lower;
        };
    };
    rt_uint32_t msg_data;
    rt_uint32_t vector_ctrl;
};

struct rt_pci_ep_ops;
struct rt_pci_ep_mem;

struct rt_pci_ep
{
    rt_list_t list;
    const char *name;

    struct rt_ref ref;

    const struct rt_device *rc_dev;
    const struct rt_pci_ep_ops *ops;

    rt_size_t mems_nr;
    struct rt_pci_ep_mem *mems;

    rt_uint8_t max_functions;
    RT_BITMAP_DECLARE(functions_map, 8);
    rt_list_t epf_nodes;
    struct rt_mutex lock;

    void *priv;
};

struct rt_pci_ep_mem
{
    rt_ubase_t cpu_addr;
    rt_size_t size;
    rt_size_t page_size;

    rt_bitmap_t *map;
    rt_size_t bits;
};

struct rt_pci_epf
{
    rt_list_t list;
    const char *name;

    struct rt_pci_ep_header *header;
    struct rt_pci_ep_bar bar[PCI_STD_NUM_BARS];

    rt_uint8_t  msi_interrupts;
    rt_uint16_t msix_interrupts;
    rt_uint8_t func_no;

    struct rt_pci_ep *ep;
};

struct rt_pci_ep_ops
{
    rt_err_t (*write_header)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            struct rt_pci_ep_header *hdr);

    rt_err_t (*set_bar)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            struct rt_pci_ep_bar *bar, int bar_idx);
    rt_err_t (*clear_bar)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            struct rt_pci_ep_bar *bar, int bar_idx);

    rt_err_t (*map_addr)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size);
    rt_err_t (*unmap_addr)(struct rt_pci_ep *ep, rt_uint8_t func_no, rt_ubase_t addr);

    rt_err_t (*set_msi)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned irq_nr);
    rt_err_t (*get_msi)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned *out_irq_nr);

    rt_err_t (*set_msix)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned irq_nr, int bar_idx, rt_off_t offset);
    rt_err_t (*get_msix)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned *out_irq_nr);

    rt_err_t (*raise_irq)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            enum rt_pci_ep_irq type, unsigned irq);

    rt_err_t (*start)(struct rt_pci_ep *ep);
    rt_err_t (*stop)(struct rt_pci_ep *ep);
};

rt_err_t rt_pci_ep_write_header(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_header *hdr);

rt_err_t rt_pci_ep_set_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx);
rt_err_t rt_pci_ep_clear_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx);

rt_err_t rt_pci_ep_map_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size);
rt_err_t rt_pci_ep_unmap_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr);

rt_err_t rt_pci_ep_set_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr);
rt_err_t rt_pci_ep_get_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr);

rt_err_t rt_pci_ep_set_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr, int bar_idx, rt_off_t offset);
rt_err_t rt_pci_ep_get_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr);

rt_err_t rt_pci_ep_raise_irq(struct rt_pci_ep *ep, rt_uint8_t func_no,
        enum rt_pci_ep_irq type, unsigned irq);

rt_err_t rt_pci_ep_start(struct rt_pci_ep *ep);
rt_err_t rt_pci_ep_stop(struct rt_pci_ep *ep);

rt_err_t rt_pci_ep_register(struct rt_pci_ep *ep);
rt_err_t rt_pci_ep_unregister(struct rt_pci_ep *ep);

rt_err_t rt_pci_ep_mem_array_init(struct rt_pci_ep *ep,
        struct rt_pci_ep_mem *mems, rt_size_t mems_nr);
rt_err_t rt_pci_ep_mem_init(struct rt_pci_ep *ep,
        rt_ubase_t cpu_addr, rt_size_t size, rt_size_t page_size);

void *rt_pci_ep_mem_alloc(struct rt_pci_ep *ep,
        rt_ubase_t *out_cpu_addr, rt_size_t size);
void rt_pci_ep_mem_free(struct rt_pci_ep *ep,
        void *vaddr, rt_ubase_t cpu_addr, rt_size_t size);

rt_err_t rt_pci_ep_add_epf(struct rt_pci_ep *ep, struct rt_pci_epf *epf);
rt_err_t rt_pci_ep_remove_epf(struct rt_pci_ep *ep, struct rt_pci_epf *epf);

struct rt_pci_ep *rt_pci_ep_get(const char *name);
void rt_pci_ep_put(struct rt_pci_ep *ep);

#endif /* __PCI_ENDPOINT_H__ */
