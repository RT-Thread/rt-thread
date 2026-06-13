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
 * @file pci_endpoint.h
 * @brief PCI Endpoint (EP) framework public API
 *
 * The PCI Endpoint framework allows an RT-Thread device to operate as
 * a PCIe endpoint (rather than a root complex). This is essential for
 * embedded systems that need to appear as PCIe devices to a host CPU.
 *
 * Provides APIs for:
 * - Writing the PCI configuration space header (vendor/device IDs, BARs)
 * - Setting up BARs for exposing local memory to the host
 * - Address mapping (CPU → PCI bus address space)
 * - MSI/MSI-X configuration and interrupt raising to the host
 * - Starting and stopping endpoint operation
 * - Managing endpoint functions (EPFs)
 * - Memory allocation from the endpoint's local pool
 */

#ifndef __PCI_ENDPOINT_H__
#define __PCI_ENDPOINT_H__

#include <drivers/pci.h>

/**
 * @brief PCI endpoint INTx pin selection
 *
 * Selects which legacy INTx line (INTA through INTD) the endpoint
 * function drives when raising a legacy interrupt.
 */
enum rt_pci_ep_pin
{
    RT_PCI_EP_PIN_UNKNOWN,  /**< Unknown / not configured */
    RT_PCI_EP_PIN_INTA,     /**< INTA# (pin 1) */
    RT_PCI_EP_PIN_INTB,     /**< INTB# (pin 2) */
    RT_PCI_EP_PIN_INTC,     /**< INTC# (pin 3) */
    RT_PCI_EP_PIN_INTD,     /**< INTD# (pin 4) */
};

/**
 * @brief PCI endpoint interrupt type
 *
 * Specifies which interrupt mechanism to use when raising an
 * interrupt from the endpoint to the PCIe host.
 */
enum rt_pci_ep_irq
{
    RT_PCI_EP_IRQ_UNKNOWN,  /**< Unknown type */
    RT_PCI_EP_IRQ_LEGACY,   /**< Legacy INTx (level-triggered, shared) */
    RT_PCI_EP_IRQ_MSI,      /**< MSI (Message Signaled Interrupt) */
    RT_PCI_EP_IRQ_MSIX,     /**< MSI-X (extended message signaled interrupt) */
};

/**
 * @brief PCI endpoint configuration header
 *
 * Contains the standard PCI configuration space header fields that
 * identify the endpoint to the host system. Written via
 * rt_pci_ep_write_header() before starting the endpoint.
 */
struct rt_pci_ep_header
{
    rt_uint16_t vendor;              /**< PCI vendor ID */
    rt_uint16_t device;              /**< PCI device ID */
    rt_uint8_t revision;             /**< Revision ID */
    rt_uint8_t progif;               /**< Programming interface */
    rt_uint8_t subclass;             /**< Subclass code */
    rt_uint8_t class_code;           /**< Base class code */
    rt_uint8_t cache_line_size;      /**< Cache line size in DWORDs */
    rt_uint16_t subsystem_vendor;    /**< Subsystem vendor ID */
    rt_uint16_t subsystem_device;    /**< Subsystem device ID */

    enum rt_pci_ep_pin intx;         /**< INTx pin to assert for legacy interrupts */
};

/**
 * @brief PCI endpoint BAR descriptor
 *
 * Describes a Base Address Register on the endpoint. bus contains
 * the PCI-side resource (flags, base, size); cpu_addr is the
 * local CPU physical address that backs the BAR.
 */
struct rt_pci_ep_bar
{
    /* To PCI Bus */
    struct rt_pci_bus_resource bus;  /**< PCI-side resource (flags, base, size) */
    /* To CPU */
    rt_ubase_t cpu_addr;             /**< Local CPU physical address backing the BAR */
};

/**
 * @brief MSI-X table entry for endpoints
 *
 * Each MSI-X table entry contains a 64-bit message address,
 * 32-bit message data, and a 32-bit vector control field.
 * For more format detail, see pci_msi.h.
 */
struct rt_pci_ep_msix_tbl
{
    union
    {
        rt_uint64_t msg_addr;        /**< Full 64-bit message address */
        struct
        {
            rt_uint32_t msg_addr_upper;  /**< Upper 32 bits of message address */
            rt_uint32_t msg_addr_lower;  /**< Lower 32 bits of message address */
        };
    };
    rt_uint32_t msg_data;            /**< Message data (identifies the interrupt) */
    rt_uint32_t vector_ctrl;         /**< Vector control (bit 0 = mask) */
};

struct rt_pci_ep_ops;
struct rt_pci_ep_mem;

/**
 * @brief PCI endpoint controller descriptor
 *
 * Represents a single PCIe endpoint controller instance. Each controller
 * can support multiple functions, each with its own configuration space.
 * Reference counting (ref) ensures safe concurrent access.
 */
struct rt_pci_ep
{
    rt_list_t list;                                   /**< Node in the global endpoint list */
    const char *name;                                  /**< Controller name (matches platform device) */

    struct rt_ref ref;                                 /**< Reference count for safe lifecycle management */

    const struct rt_device *rc_dev;                    /**< Parent root complex device */
    const struct rt_pci_ep_ops *ops;                   /**< Controller operations vtable */

    rt_size_t mems_nr;                                 /**< Number of memory regions */
    struct rt_pci_ep_mem *mems;                        /**< Array of memory region descriptors */

    rt_uint8_t max_functions;                          /**< Maximum number of functions supported */
    RT_BITMAP_DECLARE(functions_map, 8);               /**< Bitmap of allocated function numbers */
    rt_list_t epf_nodes;                               /**< List of registered endpoint functions */
    struct rt_mutex lock;                              /**< Mutex for thread-safe operations */

    void *priv;                                        /**< Controller driver private data */
};

/**
 * @brief PCI endpoint memory region descriptor
 *
 * Describes a contiguous physical memory region that the endpoint
 * controller can use for BAR backing, MSI/MSI-X memory, and DMA buffers.
 * A bitmap tracks free/used pages within the region.
 */
struct rt_pci_ep_mem
{
    rt_ubase_t cpu_addr;         /**< CPU physical base address of the region */
    rt_size_t size;              /**< Total size of the region in bytes */
    rt_size_t page_size;         /**< Allocation granularity (page size) in bytes */

    rt_bitmap_t *map;            /**< Page allocation bitmap (1 bit per page) */
    rt_size_t bits;              /**< Total number of pages in this region */
};

/**
 * @brief PCI endpoint function descriptor
 *
 * An endpoint function represents one logical PCI function on the
 * endpoint controller. Each function has its own configuration header,
 * BARs, and MSI/MSI-X settings.
 */
struct rt_pci_epf
{
    rt_list_t list;                              /**< Node in the endpoint's epf_nodes list */
    const char *name;                            /**< Function name (from device tree) */

    struct rt_pci_ep_header *header;             /**< Configuration header to present to the host */
    struct rt_pci_ep_bar bar[PCI_STD_NUM_BARS];  /**< BAR descriptors (6 standard BARs) */

    rt_uint8_t  msi_interrupts;                  /**< Number of MSI vectors requested */
    rt_uint16_t msix_interrupts;                 /**< Number of MSI-X vectors requested */
    rt_uint8_t func_no;                          /**< Function number (0 to max_functions-1) */

    struct rt_pci_ep *ep;                        /**< Parent endpoint controller */
};

/**
 * @brief PCI endpoint controller operations vtable
 *
 * Each endpoint controller driver provides implementations of these
 * operations. The framework calls them under the endpoint's mutex lock.
 */
struct rt_pci_ep_ops
{
    /**
     * @brief Write the PCI configuration header for an endpoint function
     *
     * @param[in] ep      Endpoint controller
     * @param[in] func_no Function number
     * @param[in] hdr     Header data to program
     *
     * @return RT_EOK on success
     */
    rt_err_t (*write_header)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            struct rt_pci_ep_header *hdr);

    /**
     * @brief Set a BAR on an endpoint function
     *
     * @param[in] ep      Endpoint controller
     * @param[in] func_no Function number
     * @param[in] bar     BAR configuration (flags, base, size)
     * @param[in] bar_idx BAR index (0-5)
     *
     * @return RT_EOK on success
     */
    rt_err_t (*set_bar)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            struct rt_pci_ep_bar *bar, int bar_idx);

    /**
     * @brief Clear a BAR on an endpoint function
     *
     * @param[in] ep      Endpoint controller
     * @param[in] func_no Function number
     * @param[in] bar     BAR to clear
     * @param[in] bar_idx BAR index
     *
     * @return RT_EOK on success
     */
    rt_err_t (*clear_bar)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            struct rt_pci_ep_bar *bar, int bar_idx);

    /**
     * @brief Map a CPU address to PCI bus address space
     *
     * @param[in] ep       Endpoint controller
     * @param[in] func_no  Function number
     * @param[in] addr     CPU physical address
     * @param[in] pci_addr Target PCI bus address
     * @param[in] size     Mapping size in bytes
     *
     * @return RT_EOK on success
     */
    rt_err_t (*map_addr)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size);

    /**
     * @brief Unmap a previously mapped address
     *
     * @param[in] ep      Endpoint controller
     * @param[in] func_no Function number
     * @param[in] addr    CPU physical address to unmap
     *
     * @return RT_EOK on success
     */
    rt_err_t (*unmap_addr)(struct rt_pci_ep *ep, rt_uint8_t func_no, rt_ubase_t addr);

    /**
     * @brief Configure MSI Multi-Message Enable for an endpoint function
     *
     * @param[in] ep      Endpoint controller
     * @param[in] func_no Function number
     * @param[in] irq_nr  Log2 of number of MSI vectors
     *
     * @return RT_EOK on success
     */
    rt_err_t (*set_msi)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned irq_nr);

    /**
     * @brief Get the current MSI configuration
     *
     * @param[in]  ep         Endpoint controller
     * @param[in]  func_no    Function number
     * @param[out] out_irq_nr Number of MSI vectors enabled
     *
     * @return RT_EOK on success
     */
    rt_err_t (*get_msi)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned *out_irq_nr);

    /**
     * @brief Configure MSI-X for an endpoint function
     *
     * @param[in] ep      Endpoint controller
     * @param[in] func_no Function number
     * @param[in] irq_nr  Number of MSI-X vectors
     * @param[in] bar_idx BAR index for the MSI-X table
     * @param[in] offset  Offset within the BAR for the table
     *
     * @return RT_EOK on success
     */
    rt_err_t (*set_msix)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned irq_nr, int bar_idx, rt_off_t offset);

    /**
     * @brief Get the current MSI-X configuration
     *
     * @param[in]  ep         Endpoint controller
     * @param[in]  func_no    Function number
     * @param[out] out_irq_nr Number of MSI-X vectors enabled
     *
     * @return RT_EOK on success
     */
    rt_err_t (*get_msix)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            unsigned *out_irq_nr);

    /**
     * @brief Raise an interrupt from the endpoint to the host
     *
     * @param[in] ep      Endpoint controller
     * @param[in] func_no Function number
     * @param[in] type    Interrupt type (LEGACY, MSI, or MSIX)
     * @param[in] irq     Vector number (1-based for MSI/MSI-X)
     *
     * @return RT_EOK on success
     */
    rt_err_t (*raise_irq)(struct rt_pci_ep *ep, rt_uint8_t func_no,
            enum rt_pci_ep_irq type, unsigned irq);

    /**
     * @brief Start the endpoint — make it visible on the PCIe bus
     *
     * @param[in] ep  Endpoint controller
     *
     * @return RT_EOK on success
     */
    rt_err_t (*start)(struct rt_pci_ep *ep);

    /**
     * @brief Stop the endpoint — remove it from the PCIe bus
     *
     * @param[in] ep  Endpoint controller
     *
     * @return RT_EOK on success
     */
    rt_err_t (*stop)(struct rt_pci_ep *ep);
};

/* === Endpoint Configuration API === */

/** @brief Write PCI configuration header for an endpoint function */
rt_err_t rt_pci_ep_write_header(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_header *hdr);

/** @brief Set a BAR on an endpoint function */
rt_err_t rt_pci_ep_set_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx);

/** @brief Clear a BAR on an endpoint function */
rt_err_t rt_pci_ep_clear_bar(struct rt_pci_ep *ep, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx);

/* === Address Mapping API === */

/** @brief Map CPU address to PCI bus address space for an endpoint */
rt_err_t rt_pci_ep_map_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size);

/** @brief Unmap a previously mapped address */
rt_err_t rt_pci_ep_unmap_addr(struct rt_pci_ep *ep, rt_uint8_t func_no,
        rt_ubase_t addr);

/* === MSI/MSI-X API === */

/** @brief Configure MSI for an endpoint function */
rt_err_t rt_pci_ep_set_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr);

/** @brief Get current MSI configuration */
rt_err_t rt_pci_ep_get_msi(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr);

/** @brief Configure MSI-X for an endpoint function */
rt_err_t rt_pci_ep_set_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned irq_nr, int bar_idx, rt_off_t offset);

/** @brief Get current MSI-X configuration */
rt_err_t rt_pci_ep_get_msix(struct rt_pci_ep *ep, rt_uint8_t func_no,
        unsigned *out_irq_nr);

/* === Interrupt and Control API === */

/** @brief Raise an interrupt from the endpoint to the host */
rt_err_t rt_pci_ep_raise_irq(struct rt_pci_ep *ep, rt_uint8_t func_no,
        enum rt_pci_ep_irq type, unsigned irq);

/** @brief Start the endpoint — enable link and respond to config requests */
rt_err_t rt_pci_ep_start(struct rt_pci_ep *ep);

/** @brief Stop the endpoint — disable link */
rt_err_t rt_pci_ep_stop(struct rt_pci_ep *ep);

/* === Lifecycle API === */

/** @brief Register an endpoint controller with the framework */
rt_err_t rt_pci_ep_register(struct rt_pci_ep *ep);

/** @brief Unregister an endpoint controller (fails if in use) */
rt_err_t rt_pci_ep_unregister(struct rt_pci_ep *ep);

/* === Memory API === */

/** @brief Initialize an array of memory regions for the endpoint */
rt_err_t rt_pci_ep_mem_array_init(struct rt_pci_ep *ep,
        struct rt_pci_ep_mem *mems, rt_size_t mems_nr);

/** @brief Initialize a single memory region (convenience wrapper) */
rt_err_t rt_pci_ep_mem_init(struct rt_pci_ep *ep,
        rt_ubase_t cpu_addr, rt_size_t size, rt_size_t page_size);

/** @brief Allocate memory from the endpoint's pool */
void *rt_pci_ep_mem_alloc(struct rt_pci_ep *ep,
        rt_ubase_t *out_cpu_addr, rt_size_t size);

/** @brief Free memory back to the endpoint's pool */
void rt_pci_ep_mem_free(struct rt_pci_ep *ep,
        void *vaddr, rt_ubase_t cpu_addr, rt_size_t size);

/* === Endpoint Function (EPF) API === */

/** @brief Add an endpoint function to a controller */
rt_err_t rt_pci_ep_add_epf(struct rt_pci_ep *ep, struct rt_pci_epf *epf);

/** @brief Remove an endpoint function from a controller */
rt_err_t rt_pci_ep_remove_epf(struct rt_pci_ep *ep, struct rt_pci_epf *epf);

/* === Lookup API === */

/** @brief Get a reference to an endpoint controller by name */
struct rt_pci_ep *rt_pci_ep_get(const char *name);

/** @brief Release a reference to an endpoint controller */
void rt_pci_ep_put(struct rt_pci_ep *ep);

#endif /* __PCI_ENDPOINT_H__ */
