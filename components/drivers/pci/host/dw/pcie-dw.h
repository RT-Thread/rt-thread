/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __PCIE_DESIGNWARE_H__
#define __PCIE_DESIGNWARE_H__

#include <rtthread.h>
#include <rtdevice.h>

/* Parameters for the waiting for link up routine */
#define LINK_WAIT_MAX_RETRIES                       10
#define LINK_WAIT_USLEEP_MIN                        90000
#define LINK_WAIT_USLEEP_MAX                        100000

/* Parameters for the waiting for iATU enabled routine */
#define LINK_WAIT_MAX_IATU_RETRIES                  5
#define LINK_WAIT_IATU                              9

/* Synopsys-specific PCIe configuration registers */
#define PCIE_PORT_AFR                               0x70c
#define PORT_AFR_N_FTS_MASK                         RT_GENMASK(15, 8)
#define PORT_AFR_N_FTS(n)                           RT_FIELD_PREP(PORT_AFR_N_FTS_MASK, n)
#define PORT_AFR_CC_N_FTS_MASK                      RT_GENMASK(23, 16)
#define PORT_AFR_CC_N_FTS(n)                        RT_FIELD_PREP(PORT_AFR_CC_N_FTS_MASK, n)
#define PORT_AFR_ENTER_ASPM                         RT_BIT(30)
#define PORT_AFR_L0S_ENTRANCE_LAT_SHIFT             24
#define PORT_AFR_L0S_ENTRANCE_LAT_MASK              RT_GENMASK(26, 24)
#define PORT_AFR_L1_ENTRANCE_LAT_SHIFT              27
#define PORT_AFR_L1_ENTRANCE_LAT_MASK               RT_GENMASK(29, 27)

#define PCIE_PORT_LINK_CONTROL                      0x710
#define PORT_LINK_LPBK_ENABLE                       RT_BIT(2)
#define PORT_LINK_DLL_LINK_EN                       RT_BIT(5)
#define PORT_LINK_FAST_LINK_MODE                    RT_BIT(7)
#define PORT_LINK_MODE_MASK                         RT_GENMASK(21, 16)
#define PORT_LINK_MODE(n)                           RT_FIELD_PREP(PORT_LINK_MODE_MASK, n)
#define PORT_LINK_MODE_1_LANES                      PORT_LINK_MODE(0x1)
#define PORT_LINK_MODE_2_LANES                      PORT_LINK_MODE(0x3)
#define PORT_LINK_MODE_4_LANES                      PORT_LINK_MODE(0x7)
#define PORT_LINK_MODE_8_LANES                      PORT_LINK_MODE(0xf)

#define PCIE_PORT_DEBUG0                            0x728
#define PORT_LOGIC_LTSSM_STATE_MASK                 0x1f
#define PORT_LOGIC_LTSSM_STATE_L0                   0x11
#define PCIE_PORT_DEBUG1                            0x72c
#define PCIE_PORT_DEBUG1_LINK_UP                    RT_BIT(4)
#define PCIE_PORT_DEBUG1_LINK_IN_TRAINING           RT_BIT(29)

#define PCIE_LINK_WIDTH_SPEED_CONTROL               0x80c
#define PORT_LOGIC_N_FTS_MASK                       RT_GENMASK(7, 0)
#define PORT_LOGIC_SPEED_CHANGE                     RT_BIT(17)
#define PORT_LOGIC_LINK_WIDTH_MASK                  RT_GENMASK(12, 8)
#define PORT_LOGIC_LINK_WIDTH(n)                    RT_FIELD_PREP(PORT_LOGIC_LINK_WIDTH_MASK, n)
#define PORT_LOGIC_LINK_WIDTH_1_LANES               PORT_LOGIC_LINK_WIDTH(0x1)
#define PORT_LOGIC_LINK_WIDTH_2_LANES               PORT_LOGIC_LINK_WIDTH(0x2)
#define PORT_LOGIC_LINK_WIDTH_4_LANES               PORT_LOGIC_LINK_WIDTH(0x4)
#define PORT_LOGIC_LINK_WIDTH_8_LANES               PORT_LOGIC_LINK_WIDTH(0x8)

#define PCIE_MSI_ADDR_LO                            0x820
#define PCIE_MSI_ADDR_HI                            0x824
#define PCIE_MSI_INTR0_ENABLE                       0x828
#define PCIE_MSI_INTR0_MASK                         0x82c
#define PCIE_MSI_INTR0_STATUS                       0x830

#define PCIE_PORT_MULTI_LANE_CTRL                   0x8c0
#define PORT_MLTI_UPCFG_SUPPORT                     RT_BIT(7)

#define PCIE_ATU_VIEWPORT                           0x900
#define PCIE_ATU_REGION_INBOUND                     RT_BIT(31)
#define PCIE_ATU_REGION_OUTBOUND                    0
#define PCIE_ATU_CR1                                0x904
#define PCIE_ATU_TYPE_MEM                           0x0
#define PCIE_ATU_TYPE_IO                            0x2
#define PCIE_ATU_TYPE_CFG0                          0x4
#define PCIE_ATU_TYPE_CFG1                          0x5
#define PCIE_ATU_FUNC_NUM(pf)                       ((pf) << 20)
#define PCIE_ATU_CR2                                0x908
#define PCIE_ATU_ENABLE                             RT_BIT(31)
#define PCIE_ATU_BAR_MODE_ENABLE                    RT_BIT(30)
#define PCIE_ATU_FUNC_NUM_MATCH_EN                  RT_BIT(19)
#define PCIE_ATU_LOWER_BASE                         0x90c
#define PCIE_ATU_UPPER_BASE                         0x910
#define PCIE_ATU_LIMIT                              0x914
#define PCIE_ATU_LOWER_TARGET                       0x918
#define PCIE_ATU_BUS(x)                             RT_FIELD_PREP(RT_GENMASK(31, 24), x)
#define PCIE_ATU_DEV(x)                             RT_FIELD_PREP(RT_GENMASK(23, 19), x)
#define PCIE_ATU_FUNC(x)                            RT_FIELD_PREP(RT_GENMASK(18, 16), x)
#define PCIE_ATU_UPPER_TARGET                       0x91c

#define PCIE_MISC_CONTROL_1_OFF                     0x8bc
#define PCIE_DBI_RO_WR_EN                           RT_BIT(0)

#define PCIE_MSIX_DOORBELL                          0x948
#define PCIE_MSIX_DOORBELL_PF_SHIFT                 24

#define PCIE_PL_CHK_REG_CONTROL_STATUS              0xb20
#define PCIE_PL_CHK_REG_CHK_REG_START               RT_BIT(0)
#define PCIE_PL_CHK_REG_CHK_REG_CONTINUOUS          RT_BIT(1)
#define PCIE_PL_CHK_REG_CHK_REG_COMPARISON_ERROR    RT_BIT(16)
#define PCIE_PL_CHK_REG_CHK_REG_LOGIC_ERROR         RT_BIT(17)
#define PCIE_PL_CHK_REG_CHK_REG_COMPLETE            RT_BIT(18)

#define PCIE_PL_CHK_REG_ERR_ADDR                    0xb28

/*
 * iATU Unroll-specific register definitions
 * From 4.80 core version the address translation will be made by unroll
 */
#define PCIE_ATU_UNR_REGION_CTRL1                   0x00
#define PCIE_ATU_UNR_REGION_CTRL2                   0x04
#define PCIE_ATU_UNR_LOWER_BASE                     0x08
#define PCIE_ATU_UNR_UPPER_BASE                     0x0C
#define PCIE_ATU_UNR_LOWER_LIMIT                    0x10
#define PCIE_ATU_UNR_LOWER_TARGET                   0x14
#define PCIE_ATU_UNR_UPPER_TARGET                   0x18
#define PCIE_ATU_UNR_UPPER_LIMIT                    0x20

/*
 * The default address offset between dbi_base and atu_base. Root controller
 * drivers are not required to initialize atu_base if the offset matches this
 * default; the driver core automatically derives atu_base from dbi_base using
 * this offset, if atu_base not set.
 */
#define DEFAULT_DBI_ATU_OFFSET                      (0x3 << 20)

/* Register address builder */
#define PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(region)    ((region) << 9)
#define PCIE_GET_ATU_INB_UNR_REG_OFFSET(region)     (((region) << 9) | RT_BIT(8))

#define MAX_MSI_IRQS                                256
#define MAX_MSI_IRQS_PER_CTRL                       32
#define MAX_MSI_CTRLS                               (MAX_MSI_IRQS / MAX_MSI_IRQS_PER_CTRL)
#define MSI_REG_CTRL_BLOCK_SIZE                     12
#define MSI_DEF_NUM_VECTORS                         32

/* Maximum number of inbound/outbound iATUs */
#define MAX_IATU_IN                                 256
#define MAX_IATU_OUT                                256

#define DWC_IATU_UNROLL_EN                          RT_BIT(0)
#define DWC_IATU_IOCFG_SHARED                       RT_BIT(1)

struct dw_pcie_host_ops;
struct dw_pcie_ep_ops;
struct dw_pcie_ops;

/**
 * @brief iATU region direction type
 */
enum dw_pcie_region_type
{
    DW_PCIE_REGION_UNKNOWN,  /**< Unknown / not specified */
    DW_PCIE_REGION_INBOUND,  /**< Inbound: PCI bus address → CPU address (EP BAR backing) */
    DW_PCIE_REGION_OUTBOUND, /**< Outbound: CPU address → PCI bus address (RC memory access) */
};

/**
 * @brief DesignWare PCIe controller device mode
 *
 * The controller can operate as a Root Complex (RC) or
 * Endpoint (EP). The mode is determined by the device tree
 * compatible string:
 * - "snps,dw-pcie" → RC mode
 * - "snps,dw-pcie-ep" → EP mode
 */
enum dw_pcie_device_mode
{
    DW_PCIE_UNKNOWN_TYPE,  /**< Unknown / not configured */
    DW_PCIE_EP_TYPE,       /**< Endpoint mode */
    DW_PCIE_LEG_EP_TYPE,   /**< Legacy endpoint mode */
    DW_PCIE_RC_TYPE,       /**< Root Complex mode */
};

/**
 * @brief iATU address space type for inbound/outbound translation
 */
enum dw_pcie_aspace_type
{
    DW_PCIE_ASPACE_UNKNOWN, /**< Unknown type */
    DW_PCIE_ASPACE_MEM,     /**< Memory space */
    DW_PCIE_ASPACE_IO,      /**< I/O space */
};

/**
 * @brief DesignWare PCIe port descriptor (RC mode)
 *
 * Holds the configuration space window, I/O space, MSI controller
 * state, and host bridge reference for the root complex port.
 */
struct dw_pcie_port
{
    void *cfg0_base;                             /**< Virtual address of config space window */
    rt_uint64_t cfg0_addr;                       /**< CPU physical address of config space */
    rt_uint64_t cfg0_size;                       /**< Config space window size */

    rt_ubase_t io_addr;                          /**< CPU physical address of I/O space */
    rt_ubase_t io_bus_addr;                      /**< PCI bus address of I/O space */
    rt_size_t io_size;                           /**< I/O space size */

    const struct dw_pcie_host_ops *ops;           /**< Platform-specific host operations */

    int sys_irq;                                 /**< System IRQ number */
    int msi_irq;                                 /**< MSI IRQ number */
    struct rt_pic *irq_pic;                      /**< System interrupt controller */
    struct rt_pic *msi_pic;                      /**< MSI interrupt controller */

    void *msi_data;                              /**< DMA-coherent MSI data buffer (virtual) */
    rt_ubase_t msi_data_phy;                     /**< DMA-coherent MSI data buffer (physical) */

    rt_uint32_t irq_count;                       /**< Number of MSI IRQs supported */
    rt_uint32_t irq_mask[MAX_MSI_CTRLS];         /**< Per-controller MSI mask values */

    struct rt_pci_host_bridge *bridge;           /**< Associated PCI host bridge */
    const struct rt_pci_ops *bridge_child_ops;   /**< Child bus PCI ops (NULL = use dw_child_pcie_ops) */

    struct rt_spinlock lock;                     /**< Spinlock for MSI bitmap operations */
    RT_BITMAP_DECLARE(msi_map, MAX_MSI_IRQS);   /**< MSI IRQ allocation bitmap */
};

/**
 * @brief DesignWare PCIe host operations (platform-specific callbacks)
 */
struct dw_pcie_host_ops
{
    rt_err_t (*host_init)(struct dw_pcie_port *port);     /**< RC initialization callback */
    rt_err_t (*msi_host_init)(struct dw_pcie_port *port); /**< Custom MSI initialization (optional) */
    void (*set_irq_count)(struct dw_pcie_port *port);     /**< Override default MSI IRQ count */
};

/**
 * @brief DesignWare PCIe endpoint function descriptor
 *
 * A per-function descriptor tracking the MSI and MSI-X capability
 * offsets for each function on a multi-function endpoint.
 */
struct dw_pcie_ep_func
{
    rt_list_t list;              /**< Node in ep->func_nodes */

    rt_uint8_t func_no;          /**< Function number (0 to max_functions-1) */
    rt_uint8_t msi_cap;          /**< MSI capability offset in DBI space */
    rt_uint8_t msix_cap;         /**< MSI-X capability offset in DBI space */
};

/**
 * @brief DesignWare PCIe endpoint descriptor
 *
 * Manages the EP mode state: BAR-to-ATU mapping, inbound/outbound
 * ATU window bitmaps, function list, and MSI memory.
 */
struct dw_pcie_ep
{
    struct rt_pci_ep *epc;                                /**< EP framework controller reference */
    struct rt_pci_ep_bar *epc_bar[PCI_STD_NUM_BARS];     /**< EP BAR backing descriptors */

    rt_list_t func_nodes;                                  /**< List of dw_pcie_ep_func nodes */

    const struct dw_pcie_ep_ops *ops;                      /**< Platform-specific EP operations */

    rt_uint64_t aspace;                                    /**< Address space base (from DT addr_space) */
    rt_uint64_t aspace_size;                               /**< Address space size */
    rt_size_t page_size;                                   /**< Allocation page size */

    rt_uint8_t bar_to_atu[PCI_STD_NUM_BARS];               /**< BAR index → ATU region index mapping */
    rt_ubase_t *outbound_addr;                             /**< Per-window outbound CPU address array */

    rt_bitmap_t *ib_window_map;                            /**< Inbound ATU window allocation bitmap */
    rt_bitmap_t *ob_window_map;                            /**< Outbound ATU window allocation bitmap */
    rt_uint32_t num_ib_windows;                            /**< Total inbound ATU windows */
    rt_uint32_t num_ob_windows;                            /**< Total outbound ATU windows */

    void *msi_mem;                                         /**< MSI/MSI-X posted-write memory (virtual) */
    rt_ubase_t msi_mem_phy;                                /**< MSI/MSI-X posted-write memory (physical) */
};

/**
 * @brief DesignWare PCIe endpoint operations (platform-specific)
 */
struct dw_pcie_ep_ops
{
    rt_err_t (*ep_init)(struct dw_pcie_ep *ep);           /**< EP initialization callback */
    rt_err_t (*raise_irq)(struct dw_pcie_ep *ep, rt_uint8_t func_no,
            enum rt_pci_ep_irq type, unsigned irq);       /**< Raise an interrupt to the host */
    rt_off_t (*func_select)(struct dw_pcie_ep *ep, rt_uint8_t func_no); /**< Select function register offset */
};

/**
 * @brief DesignWare PCIe controller descriptor
 *
 * Top-level structure shared between RC and EP modes.
 * Contains DBI register pointers, ATU base, version info,
 * lane/link configuration, and the dual-mode port/endpoint union.
 */
struct dw_pcie
{
    struct rt_device *dev;           /**< Parent platform device */

    void *dbi_base;                  /**< DBI (Data Bus Interface) virtual base for own config */
    void *dbi_base2;                 /**< DBI2 base for EP-mode config space */
    void *atu_base;                  /**< iATU registers virtual base */

    rt_uint32_t version;             /**< Controller version (e.g., 0x480a for 4.80a) */
    rt_uint32_t num_viewport;        /**< Number of ATU viewport registers */
    rt_uint32_t num_lanes;           /**< Number of PCIe lanes (1/2/4/8) */
    rt_uint32_t link_gen;            /**< Target link generation (1-4) */
    rt_uint32_t user_speed;          /**< User-specified speed override */
    rt_uint8_t iatu_unroll_enabled;  /**< iATU unroll mode flags (DWC_IATU_*) */
    rt_uint8_t fts_number[2];        /**< Fast Training Sequence values (gen1, gen2+) */

    struct dw_pcie_port port;        /**< RC mode port descriptor */
    struct dw_pcie_ep endpoint;      /**< EP mode endpoint descriptor */
    const struct dw_pcie_ops *ops;   /**< Platform-specific operations */

    void *priv;                      /**< Private data for the platform driver */
};

/**
 * @brief DesignWare PCIe platform operations vtable
 *
 * Optional hooks for platform-specific controller behavior:
 * address fixup, custom DBI access, link status, and power control.
 */
struct dw_pcie_ops
{
    rt_uint64_t (*cpu_addr_fixup)(struct dw_pcie *pcie, rt_uint64_t cpu_addr); /**< Fix up CPU address before ATU programming */
    rt_uint32_t (*read_dbi)(struct dw_pcie *pcie, void *base, rt_uint32_t reg, rt_size_t size);  /**< Custom DBI read */
    void        (*write_dbi)(struct dw_pcie *pcie, void *base, rt_uint32_t reg, rt_size_t size, rt_uint32_t val);  /**< Custom DBI write */
    void        (*write_dbi2)(struct dw_pcie *pcie, void *base, rt_uint32_t reg, rt_size_t size, rt_uint32_t val); /**< Custom DBI2 write */
    rt_bool_t   (*link_up)(struct dw_pcie *pcie);       /**< Platform-specific link status check */
    rt_err_t    (*start_link)(struct dw_pcie *pcie);    /**< Start link training */
    void        (*stop_link)(struct dw_pcie *pcie);     /**< Stop link / disable PHY */
};

#define to_dw_pcie_from_port(ptr)       rt_container_of((ptr), struct dw_pcie, port)
#define to_dw_pcie_from_endpoint(ptr)   rt_container_of((ptr), struct dw_pcie, endpoint)

#ifdef RT_PCI_DW_HOST
#undef RT_PCI_DW_HOST
#define RT_PCI_DW_HOST                  1
#define HOST_API
#define HOST_RET(...)                   ;
#else
#define HOST_API                        rt_inline
#define HOST_RET(...)                   { return __VA_ARGS__; }
#endif

#ifdef RT_PCI_DW_EP
#undef RT_PCI_DW_EP
#define RT_PCI_DW_EP                    1
#define EP_API
#define EP_RET(...)                     ;
#else
#define EP_API                          rt_inline
#define EP_RET(...)                     { return __VA_ARGS__; }
#endif

rt_uint8_t dw_pcie_find_capability(struct dw_pcie *pci, rt_uint8_t cap);
rt_uint16_t dw_pcie_find_ext_capability(struct dw_pcie *pci, rt_uint8_t cap);

rt_err_t dw_pcie_read(void *addr, rt_size_t size, rt_uint32_t *out_val);
rt_err_t dw_pcie_write(void *addr, rt_size_t size, rt_uint32_t val);

rt_uint32_t dw_pcie_read_dbi(struct dw_pcie *pci, rt_uint32_t reg, rt_size_t size);
void dw_pcie_write_dbi(struct dw_pcie *pci, rt_uint32_t reg, rt_size_t size, rt_uint32_t val);
void dw_pcie_write_dbi2(struct dw_pcie *pci, rt_uint32_t reg, rt_size_t size, rt_uint32_t val);
rt_uint32_t dw_pcie_readl_atu(struct dw_pcie *pci, rt_uint32_t reg);
void dw_pcie_writel_atu(struct dw_pcie *pci, rt_uint32_t reg, rt_uint32_t val);
rt_bool_t dw_pcie_link_up(struct dw_pcie *pci);
void dw_pcie_upconfig_setup(struct dw_pcie *pci);
rt_err_t dw_pcie_wait_for_link(struct dw_pcie *pci);
void dw_pcie_prog_outbound_atu(struct dw_pcie *pci, int index, int type, rt_uint64_t cpu_addr, rt_uint64_t pci_addr, rt_size_t size);
void dw_pcie_prog_ep_outbound_atu(struct dw_pcie *pci, rt_uint8_t func_no, int index, int type, rt_uint64_t cpu_addr, rt_uint64_t pci_addr, rt_size_t size);
rt_err_t dw_pcie_prog_inbound_atu(struct dw_pcie *pci, rt_uint8_t func_no, int index, int bar, rt_uint64_t cpu_addr, enum dw_pcie_aspace_type aspace_type);
void dw_pcie_disable_atu(struct dw_pcie *pci, int index, enum dw_pcie_region_type type);
void dw_pcie_setup(struct dw_pcie *pci);

/** @brief Write a 32-bit DBI register (convenience wrapper) */
rt_inline void dw_pcie_writel_dbi(struct dw_pcie *pci, rt_uint32_t reg, rt_uint32_t val)
{
    dw_pcie_write_dbi(pci, reg, 0x4, val);
}

/** @brief Read a 32-bit DBI register (convenience wrapper) */
rt_inline rt_uint32_t dw_pcie_readl_dbi(struct dw_pcie *pci, rt_uint32_t reg)
{
    return dw_pcie_read_dbi(pci, reg, 0x4);
}

/** @brief Write a 16-bit DBI register (convenience wrapper) */
rt_inline void dw_pcie_writew_dbi(struct dw_pcie *pci, rt_uint32_t reg, rt_uint16_t val)
{
    dw_pcie_write_dbi(pci, reg, 0x2, val);
}

/** @brief Read a 16-bit DBI register (convenience wrapper) */
rt_inline rt_uint16_t dw_pcie_readw_dbi(struct dw_pcie *pci, rt_uint32_t reg)
{
    return dw_pcie_read_dbi(pci, reg, 0x2);
}

/** @brief Write an 8-bit DBI register (convenience wrapper) */
rt_inline void dw_pcie_writeb_dbi(struct dw_pcie *pci, rt_uint32_t reg, rt_uint8_t val)
{
    dw_pcie_write_dbi(pci, reg, 0x1, val);
}

/** @brief Read an 8-bit DBI register (convenience wrapper) */
rt_inline rt_uint8_t dw_pcie_readb_dbi(struct dw_pcie *pci, rt_uint32_t reg)
{
    return dw_pcie_read_dbi(pci, reg, 0x1);
}

/** @brief Write a 32-bit DBI2 register (convenience wrapper) */
rt_inline void dw_pcie_writel_dbi2(struct dw_pcie *pci, rt_uint32_t reg, rt_uint32_t val)
{
    dw_pcie_write_dbi2(pci, reg, 0x4, val);
}

/**
 * @brief Enable or disable DBI read-only register write access
 *
 * @param[in] pci    DW PCIe controller
 * @param[in] enable RT_TRUE to allow writes to RO registers
 */
rt_inline void dw_pcie_dbi_ro_writable_enable(struct dw_pcie *pci, rt_bool_t enable)
{
    const rt_uint32_t reg = PCIE_MISC_CONTROL_1_OFF;

    if (enable)
    {
        dw_pcie_writel_dbi(pci, reg, dw_pcie_readl_dbi(pci, reg) | PCIE_DBI_RO_WR_EN);
    }
    else
    {
        dw_pcie_writel_dbi(pci, reg, dw_pcie_readl_dbi(pci, reg) & ~PCIE_DBI_RO_WR_EN);
    }
}

/** @brief Detect if iATU supports unroll mode (version >= 4.80a, VIEWPORT reads all-ones) */
rt_inline rt_uint8_t dw_pcie_iatu_unroll_enabled(struct dw_pcie *pci)
{
    return dw_pcie_readl_dbi(pci, PCIE_ATU_VIEWPORT) == 0xffffffff ? 1 : 0;
}

rt_inline rt_uint32_t dw_pcie_readl_ob_unroll(struct dw_pcie *pci,
        rt_uint32_t index, rt_uint32_t reg)
{
    return dw_pcie_readl_atu(pci, PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index) + reg);
}

rt_inline void dw_pcie_writel_ob_unroll(struct dw_pcie *pci,
        rt_uint32_t index, rt_uint32_t reg, rt_uint32_t val)
{
    dw_pcie_writel_atu(pci, PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index) + reg, val);
}

rt_inline rt_uint32_t dw_pcie_readl_ib_unroll(struct dw_pcie *pci,
        rt_uint32_t index, rt_uint32_t reg)
{
    return dw_pcie_readl_atu(pci, PCIE_GET_ATU_INB_UNR_REG_OFFSET(index) + reg);
}

rt_inline void dw_pcie_writel_ib_unroll(struct dw_pcie *pci,
        rt_uint32_t index, rt_uint32_t reg, rt_uint32_t val)
{
    dw_pcie_writel_atu(pci, reg + PCIE_GET_ATU_INB_UNR_REG_OFFSET(index), val);
}

/** @brief Handle all pending MSI interrupts (RC mode) */
HOST_API rt_err_t dw_handle_msi_irq(struct dw_pcie_port *port) HOST_RET(-RT_ENOSYS)
/** @brief Initialize MSI and program MSI address registers */
HOST_API void dw_pcie_msi_init(struct dw_pcie_port *port) HOST_RET()
/** @brief Free MSI resources */
HOST_API void dw_pcie_free_msi(struct dw_pcie_port *port) HOST_RET()

/** @brief Set up root complex configuration (RC mode) */
HOST_API void dw_pcie_setup_rc(struct dw_pcie_port *port) HOST_RET()

/** @brief Initialize DW PCIe host controller (full RC init) */
HOST_API rt_err_t dw_pcie_host_init(struct dw_pcie_port *port) HOST_RET(-RT_ENOSYS)
/** @brief Deinitialize host mode */
HOST_API void dw_pcie_host_deinit(struct dw_pcie_port *port) HOST_RET()
/** @brief Fully free host mode resources */
HOST_API void dw_pcie_host_free(struct dw_pcie_port *port) HOST_RET()

/** @brief Map config space for the root bus (DBI direct access) */
HOST_API void *dw_pcie_own_conf_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg) HOST_RET(RT_NULL)

/** @brief Initialize DW PCIe endpoint */
EP_API rt_err_t dw_pcie_ep_init(struct dw_pcie_ep *ep) EP_RET(-RT_ENOSYS)
/** @brief Complete EP initialization after dw_pcie_ep_init() */
EP_API rt_err_t dw_pcie_ep_init_complete(struct dw_pcie_ep *ep) EP_RET(-RT_ENOSYS)
/** @brief Clean up and free all EP resources */
EP_API void dw_pcie_ep_exit(struct dw_pcie_ep *ep) EP_RET()

/** @brief Raise legacy INTx from EP (not supported on DW) */
EP_API rt_err_t dw_pcie_ep_raise_legacy_irq(struct dw_pcie_ep *ep, rt_uint8_t func_no) EP_RET(-RT_ENOSYS)
/** @brief Raise MSI interrupt from EP via posted write */
EP_API rt_err_t dw_pcie_ep_raise_msi_irq(struct dw_pcie_ep *ep, rt_uint8_t func_no, unsigned irq) EP_RET(-RT_ENOSYS)
/** @brief Raise MSI-X interrupt via table entry write */
EP_API rt_err_t dw_pcie_ep_raise_msix_irq(struct dw_pcie_ep *ep, rt_uint8_t func_no, unsigned irq) EP_RET(-RT_ENOSYS)
/** @brief Raise MSI-X interrupt via doorbell register (faster) */
EP_API rt_err_t dw_pcie_ep_raise_msix_irq_doorbell(struct dw_pcie_ep *ep, rt_uint8_t func_no, unsigned irq) EP_RET(-RT_ENOSYS)

/** @brief Reset a BAR to default state for all EP functions */
EP_API void dw_pcie_ep_reset_bar(struct dw_pcie *pci, int bar_idx) EP_RET()

/** @brief Program an inbound iATU region for an EP BAR */
EP_API rt_err_t dw_pcie_ep_inbound_atu(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        int bar_idx, rt_ubase_t cpu_addr, enum dw_pcie_aspace_type aspace_type) EP_RET(-RT_ENOSYS)
/** @brief Program an outbound iATU region for EP→host access */
EP_API rt_err_t dw_pcie_ep_outbound_atu(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        rt_ubase_t phys_addr, rt_uint64_t pci_addr, rt_size_t size) EP_RET(-RT_ENOSYS)

/** @brief Get EP function descriptor by function number */
EP_API struct dw_pcie_ep_func *dw_pcie_ep_get_func_from_ep(struct dw_pcie_ep *ep, rt_uint8_t func_no) EP_RET(RT_NULL)

#endif /* __PCIE_DESIGNWARE_H__ */
