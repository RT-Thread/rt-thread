/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pcie.brcmstb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <ecam.h>
#include <mmu.h>
#include <mm_aspace.h>
#include <dt-bindings/size.h>

/* BRCM_PCIE_CAP_REGS - Offset for the mandatory capability config regs */
#define BRCM_PCIE_CAP_REGS                                              0x00ac

/* Broadcom STB PCIe Register Offsets */
#define PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1                         0x0188
#define  PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1_ENDIAN_MODE_BAR2_MASK  0xc
#define  PCIE_RC_CFG_VENDOR_SPECIFIC_REG1_LITTLE_ENDIAN                 0x0

#define PCIE_RC_CFG_PRIV1_ID_VAL3                                       0x043c
#define  PCIE_RC_CFG_PRIV1_ID_VAL3_CLASS_CODE_MASK                      0xffffff

#define PCIE_RC_CFG_PRIV1_LINK_CAPABILITY                               0x04dc
#define  PCIE_RC_CFG_PRIV1_LINK_CAPABILITY_MAX_LINK_WIDTH_MASK          0x1f0

#define PCIE_RC_CFG_PRIV1_ROOT_CAP                                      0x4f8
#define  PCIE_RC_CFG_PRIV1_ROOT_CAP_L1SS_MODE_MASK                      0xf8

#define PCIE_RC_TL_VDM_CTL0                                             0x0a20
#define  PCIE_RC_TL_VDM_CTL0_VDM_ENABLED_MASK                           0x10000
#define  PCIE_RC_TL_VDM_CTL0_VDM_IGNORETAG_MASK                         0x20000
#define  PCIE_RC_TL_VDM_CTL0_VDM_IGNOREVNDRID_MASK                      0x40000

#define PCIE_RC_TL_VDM_CTL1                                             0x0a0c
#define  PCIE_RC_TL_VDM_CTL1_VDM_VNDRID0_MASK                           0x0000ffff
#define  PCIE_RC_TL_VDM_CTL1_VDM_VNDRID1_MASK                           0xffff0000

#define PCIE_RC_DL_MDIO_ADDR                                            0x1100
#define PCIE_RC_DL_MDIO_WR_DATA                                         0x1104
#define PCIE_RC_DL_MDIO_RD_DATA                                         0x1108

#define PCIE_RC_PL_REG_PHY_CTL_1                                        0x1804
#define  PCIE_RC_PL_REG_PHY_CTL_1_REG_P2_POWERDOWN_ENA_NOSYNC_MASK      0x8

#define PCIE_RC_PL_PHY_CTL_15                                           0x184c
#define  PCIE_RC_PL_PHY_CTL_15_DIS_PLL_PD_MASK                          0x400000
#define  PCIE_RC_PL_PHY_CTL_15_PM_CLK_PERIOD_MASK                       0xff

#define PCIE_RC_PL_STATS_CTRL                                           0x1940
#define  PCIE_RC_PL_STATS_CTRL_EN_MASK                                  0x1
#define  PCIE_RC_PL_STATS_CTRL_LEN_MASK                                 0xfffffff0

#define PCIE_RC_PL_STATS_TXTLP_LO                                       0x1944
#define PCIE_RC_PL_STATS_TXTLP_HI                                       0x1948
#define PCIE_RC_PL_STATS_TXDLLP_LO                                      0x194c
#define PCIE_RC_PL_STATS_TXDLLP_HI                                      0x1950
#define PCIE_RC_PL_STATS_RXTLP_LO                                       0x195c
#define PCIE_RC_PL_STATS_RXTLP_HI                                       0x1960
#define PCIE_RC_PL_STATS_RXDLLP_LO                                      0x1964
#define PCIE_RC_PL_STATS_RXDLLP_HI                                      0x1968
#define PCIE_RC_PL_STATS_RXPL_ERR                                       0x1974
#define PCIE_RC_PL_STATS_RXDL_ERR                                       0x1978
#define PCIE_RC_PL_STATS_RXTL_ERR                                       0x197c

#define PCIE_RC_PL_LTSSM_STATS_3                                        0x19b0
#define  PCIE_RC_PL_LTSSM_STATS_3_TIME_L0S_MASK                         0xffff0000
#define  PCIE_RC_PL_LTSSM_STATS_3_TIME_RECOV_MASK                       0x0000ffff

#define PCIE_RC_PL_LTSSM_STATS_CNT                                      0x19b4
#define  PCIE_RC_PL_LTSSM_STATS_CNT_L0S_FAIL_MASK                       0xffff0000
#define  PCIE_RC_PL_LTSSM_STATS_CNT_RECOV_MASK                          0x0000ffff

#define PCIE_RC_PL_LTSSM_HIST_0                                         0x1cec
#define PCIE_RC_PL_LTSSM_HIST(n) (PCIE_RC_PL_LTSSM_HIST_0 + ((n) * 4))

#define PCIE_MISC_MISC_CTRL                                             0x4008
#define  PCIE_MISC_MISC_CTRL_PCIE_RCB_64B_MODE_MASK                     0x80
#define  PCIE_MISC_MISC_CTRL_PCIE_RCB_MPS_MODE_MASK                     0x400
#define  PCIE_MISC_MISC_CTRL_SCB_ACCESS_EN_MASK                         0x1000
#define  PCIE_MISC_MISC_CTRL_CFG_READ_UR_MODE_MASK                      0x2000
#define  PCIE_MISC_MISC_CTRL_MAX_BURST_SIZE_MASK                        0x300000

#define  PCIE_MISC_MISC_CTRL_SCB0_SIZE_MASK                             0xf8000000
#define  PCIE_MISC_MISC_CTRL_SCB1_SIZE_MASK                             0x07c00000
#define  PCIE_MISC_MISC_CTRL_SCB2_SIZE_MASK                             0x0000001f
#define  SCB_SIZE_MASK(x) PCIE_MISC_MISC_CTRL_SCB ## x ## _SIZE_MASK

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LO                                0x400c
#define PCIE_MEM_WIN0_LO(win) PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LO + ((win) * 8)

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI                                0x4010
#define PCIE_MEM_WIN0_HI(win) PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI + ((win) * 8)

#define PCIE_BRCM_MAX_INBOUND_WINS                                      16
#define PCIE_MISC_RC_BAR1_CONFIG_LO                                     0x402c
#define  PCIE_MISC_RC_BAR1_CONFIG_LO_SIZE_MASK                          0x1f

#define PCIE_MISC_RC_BAR4_CONFIG_LO                                     0x40d4

#define PCIE_MISC_MSI_BAR_CONFIG_LO                                     0x4044
#define PCIE_MISC_MSI_BAR_CONFIG_HI                                     0x4048

#define PCIE_MISC_MSI_DATA_CONFIG                                       0x404c
#define  PCIE_MISC_MSI_DATA_CONFIG_VAL_32                               0xffe06540
#define  PCIE_MISC_MSI_DATA_CONFIG_VAL_8                                0xfff86540

#define PCIE_MISC_RC_CONFIG_RETRY_TIMEOUT                               0x405c

#define PCIE_MISC_PCIE_CTRL                                             0x4064
#define  PCIE_MISC_PCIE_CTRL_PCIE_L23_REQUEST_MASK                      0x1
#define PCIE_MISC_PCIE_CTRL_PCIE_PERSTB_MASK                            0x4

#define PCIE_MISC_PCIE_STATUS                                           0x4068
#define  PCIE_MISC_PCIE_STATUS_PCIE_PORT_MASK                           0x80
#define  PCIE_MISC_PCIE_STATUS_PCIE_DL_ACTIVE_MASK                      0x20
#define  PCIE_MISC_PCIE_STATUS_PCIE_PHYLINKUP_MASK                      0x10
#define  PCIE_MISC_PCIE_STATUS_PCIE_LINK_IN_L23_MASK                    0x40

#define PCIE_MISC_REVISION                                              0x406c
#define  BRCM_PCIE_HW_REV_33                                            0x0303
#define  BRCM_PCIE_HW_REV_3_20                                          0x0320

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT                        0x4070
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_LIMIT_MASK            0xfff00000
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_BASE_MASK             0xfff0
#define PCIE_MEM_WIN0_BASE_LIMIT(win) PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT + ((win) * 4)

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI                           0x4080
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI_BASE_MASK                0xff
#define PCIE_MEM_WIN0_BASE_HI(win) PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI + ((win) * 8)

#define PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI                          0x4084
#define  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI_LIMIT_MASK              0xff
#define PCIE_MEM_WIN0_LIMIT_HI(win) PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI + ((win) * 8)

#define PCIE_MISC_HARD_PCIE_HARD_DEBUG                                  pcie->soc_data->reg_offsets[PCIE_HARD_DEBUG]
#define  PCIE_MISC_HARD_PCIE_HARD_DEBUG_CLKREQ_DEBUG_ENABLE_MASK        0x2
#define  PCIE_MISC_HARD_PCIE_HARD_DEBUG_PERST_ASSERT_MASK               0x8
#define  PCIE_MISC_HARD_PCIE_HARD_DEBUG_REFCLK_OVRD_ENABLE_MASK         0x10000
#define  PCIE_MISC_HARD_PCIE_HARD_DEBUG_REFCLK_OVRD_OUT_MASK            0x100000
#define  PCIE_MISC_HARD_PCIE_HARD_DEBUG_L1SS_ENABLE_MASK                0x200000
#define  PCIE_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK                0x08000000
#define  PCIE_BMIPS_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK          0x00800000
#define  PCIE_CLKREQ_MASK \
      (PCIE_MISC_HARD_PCIE_HARD_DEBUG_CLKREQ_DEBUG_ENABLE_MASK | \
       PCIE_MISC_HARD_PCIE_HARD_DEBUG_L1SS_ENABLE_MASK)

/* PCIe Link Capabilities: L0s Entry Supported (PCI Express Base Spec) */
#ifndef PCI_EXP_LNKCAP_ASPM_L0S
#define PCI_EXP_LNKCAP_ASPM_L0S                                         0x00000400
#endif

#define PCIE_MISC_CTRL_1                                                0x40A0
#define  PCIE_MISC_CTRL_1_OUTBOUND_TC_MASK                              0xf
#define  PCIE_MISC_CTRL_1_OUTBOUND_NO_SNOOP_MASK                        RT_BIT(3)
#define  PCIE_MISC_CTRL_1_OUTBOUND_RO_MASK                              RT_BIT(4)
#define  PCIE_MISC_CTRL_1_EN_VDM_QOS_CONTROL_MASK                       RT_BIT(5)

#define PCIE_MISC_UBUS_CTRL                                             0x40a4
#define  PCIE_MISC_UBUS_CTRL_UBUS_PCIE_REPLY_ERR_DIS_MASK               RT_BIT(13)
#define  PCIE_MISC_UBUS_CTRL_UBUS_PCIE_REPLY_DECERR_DIS_MASK            RT_BIT(19)

#define PCIE_MISC_UBUS_TIMEOUT                                          0x40a8

#define PCIE_MISC_UBUS_BAR1_CONFIG_REMAP                                0x40ac
#define  PCIE_MISC_UBUS_BAR1_CONFIG_REMAP_ACCESS_ENABLE_MASK            RT_BIT(0)
#define PCIE_MISC_UBUS_BAR1_CONFIG_REMAP_HI                             0x40b0
#define PCIE_MISC_UBUS_BAR4_CONFIG_REMAP                                0x410c

#define PCIE_MISC_UBUS_BAR2_CONFIG_REMAP                                0x40b4
#define  PCIE_MISC_UBUS_BAR2_CONFIG_REMAP_ACCESS_ENABLE_MASK            RT_BIT(0)
#define PCIE_MISC_UBUS_BAR3_CONFIG_REMAP                                0x40bc

/* Additional RC BARs */
#define  PCIE_MISC_RC_BAR_CONFIG_LO_SIZE_MASK       0x1f
#define PCIE_MISC_RC_BAR4_CONFIG_LO                 0x40d4
#define PCIE_MISC_RC_BAR4_CONFIG_HI                 0x40d8

#define PCIE_MISC_RC_BAR10_CONFIG_LO                0x4104
#define PCIE_MISC_RC_BAR10_CONFIG_HI                0x4108

#define PCIE_MISC_UBUS_BAR_CONFIG_REMAP_ENABLE      0x1
#define PCIE_MISC_UBUS_BAR_CONFIG_REMAP_LO_MASK     0xfffff000
#define PCIE_MISC_UBUS_BAR_CONFIG_REMAP_HI_MASK     0xff
#define PCIE_MISC_UBUS_BAR4_CONFIG_REMAP_LO         0x410c
#define PCIE_MISC_UBUS_BAR4_CONFIG_REMAP_HI         0x4110

#define PCIE_MISC_UBUS_BAR10_CONFIG_REMAP_LO        0x413c
#define PCIE_MISC_UBUS_BAR10_CONFIG_REMAP_HI        0x4140

/* AXI priority forwarding - automatic level-based */
#define PCIE_MISC_TC_QUEUE_TO_QOS_MAP(x)            (0x4160 - (x) * 4)
/* Defined in quarter-fullness */
#define  QUEUE_THRESHOLD_34_TO_QOS_MAP_SHIFT        12
#define  QUEUE_THRESHOLD_23_TO_QOS_MAP_SHIFT        8
#define  QUEUE_THRESHOLD_12_TO_QOS_MAP_SHIFT        4
#define  QUEUE_THRESHOLD_01_TO_QOS_MAP_SHIFT        0
#define  QUEUE_THRESHOLD_MASK                       0xf

/* VDM messages indexing TCs to AXI priorities */
/* Indexes 8-15 */
#define PCIE_MISC_VDM_PRIORITY_TO_QOS_MAP_HI        0x4164
/* Indexes 0-7 */
#define PCIE_MISC_VDM_PRIORITY_TO_QOS_MAP_LO        0x4168
#define  VDM_PRIORITY_TO_QOS_MAP_SHIFT(x)           (4 * (x))
#define  VDM_PRIORITY_TO_QOS_MAP_MASK               0xf

#define PCIE_MISC_AXI_INTF_CTRL                     0x416c
#define  AXI_EN_RCLK_QOS_ARRAY_FIX                  RT_BIT(13)
#define  AXI_EN_QOS_UPDATE_TIMING_FIX               RT_BIT(12)
#define  AXI_DIS_QOS_GATING_IN_MASTER               RT_BIT(11)
#define  AXI_REQFIFO_EN_QOS_PROPAGATION             RT_BIT(7)
#define  AXI_BRIDGE_LOW_LATENCY_MODE                RT_BIT(6)
#define  AXI_MASTER_MAX_OUTSTANDING_REQUESTS_MASK   0x3f

#define PCIE_MISC_AXI_READ_ERROR_DATA               0x4170

#define PCIE_MSI_INTR2_BASE                         0x4500
/* Offsets from PCIE_INTR2_CPU_BASE and PCIE_MSI_INTR2_BASE */
#define  MSI_INT_STATUS                             0x0
#define  MSI_INT_CLR                                0x8
#define  MSI_INT_MASK_SET                           0x10
#define  MSI_INT_MASK_CLR                           0x14

#define PCIE_EXT_CFG_DATA                           0x8000
#define PCIE_EXT_CFG_INDEX                          0x9000

#define  PCIE_RGR1_SW_INIT_1_PERST_MASK             0x1
#define  PCIE_RGR1_SW_INIT_1_PERST_SHIFT            0x0

#define RGR1_SW_INIT_1_INIT_GENERIC_MASK            0x2
#define RGR1_SW_INIT_1_INIT_GENERIC_SHIFT           0x1
#define RGR1_SW_INIT_1_INIT_7278_MASK               0x1
#define RGR1_SW_INIT_1_INIT_7278_SHIFT              0x0

/* PCIe parameters */
#define BRCM_NUM_PCIE_OUT_WINS                      0x4
#define BRCM_INT_PCI_MSI_NR                         32
#define BRCM_INT_PCI_MSI_LEGACY_NR                  8
#define BRCM_INT_PCI_MSI_SHIFT                      0
#define BRCM_INT_PCI_MSI_MASK                       RT_GENMASK(BRCM_INT_PCI_MSI_NR - 1, 0)
#define BRCM_INT_PCI_MSI_LEGACY_MASK                RT_GENMASK(31, 32 - BRCM_INT_PCI_MSI_LEGACY_NR)

/* MSI target addresses */
#define BRCM_MSI_TARGET_ADDR_LT_4GB                 0x0fffffffcULL
#define BRCM_MSI_TARGET_ADDR_GT_4GB                 0xffffffffcULL

/* PCIe CEM 2.2 / PCIe r5.0 6.6.1: wait after PERST# deassertion */
#define PCIE_RESET_CONFIG_WAIT_MS                   100

/* MDIO registers */
#define MDIO_PORT0                                  0x0
#define MDIO_DATA_MASK                              0x7fffffff
#define MDIO_PORT_MASK                              0xf0000
#define MDIO_PORT_EXT_MASK                          0x200000
#define MDIO_REGAD_MASK                             0xffff
#define MDIO_CMD_MASK                               0x00100000
#define MDIO_CMD_READ                               0x1
#define MDIO_CMD_WRITE                              0x0
#define MDIO_DATA_DONE_MASK                         0x80000000
#define MDIO_RD_DONE(x)                             (((x) & MDIO_DATA_DONE_MASK) ? 1 : 0)
#define MDIO_WT_DONE(x)                             (((x) & MDIO_DATA_DONE_MASK) ? 0 : 1)
#define SSC_REGS_ADDR                               0x1100
#define SET_ADDR_OFFSET                             0x1f
#define SSC_CNTL_OFFSET                             0x2
#define SSC_CNTL_OVRD_EN_MASK                       0x8000
#define SSC_CNTL_OVRD_VAL_MASK                      0x4000
#define SSC_STATUS_OFFSET                           0x1
#define SSC_STATUS_SSC_MASK                         0x400
#define SSC_STATUS_PLL_LOCK_MASK                    0x800
#define PCIE_BRCM_MAX_MEMC                          3

#define IDX_ADDR(pcie)                              (pcie->soc_data->reg_offsets[EXT_CFG_INDEX])
#define DATA_ADDR(pcie)                             (pcie->soc_data->reg_offsets[EXT_CFG_DATA])
#define HARD_DEBUG(pcie)                            (pcie->soc_data->reg_offsets[PCIE_HARD_DEBUG])
#define INTR2_CPU_BASE(pcie)                        (pcie->soc_data->reg_offsets[PCIE_INTR2_CPU_BASE])
#define PCIE_RGR1_SW_INIT_1(pcie)                   (pcie->soc_data->reg_offsets[RGR1_SW_INIT_1])

/* Rescal registers */
#define PCIE_DVT_PMU_PHY_CTRL                       0xc700
#define  PCIE_DVT_PMU_PHY_CTRL_DAST_NFLDS           0x3
#define  PCIE_DVT_PMU_PHY_CTRL_DAST_DIG_RESET_MASK  0x4
#define  PCIE_DVT_PMU_PHY_CTRL_DAST_DIG_RESET_SHIFT 0x2
#define  PCIE_DVT_PMU_PHY_CTRL_DAST_RESET_MASK      0x2
#define  PCIE_DVT_PMU_PHY_CTRL_DAST_RESET_SHIFT     0x1
#define  PCIE_DVT_PMU_PHY_CTRL_DAST_PWRDN_MASK      0x1
#define  PCIE_DVT_PMU_PHY_CTRL_DAST_PWRDN_SHIFT     0x0

enum
{
    RGR1_SW_INIT_1,
    EXT_CFG_INDEX,
    EXT_CFG_DATA,
    PCIE_HARD_DEBUG,
    PCIE_INTR2_CPU_BASE,
};

enum
{
    RGR1_SW_INIT_1_INIT_MASK,
    RGR1_SW_INIT_1_INIT_SHIFT,
};

enum brcm_pcie_type
{
    GENERIC,
    BCM2711,
    BCM4908,
    BCM7278,
    BCM7425,
    BCM7435,
    BCM7712,
};

static const char * const supplies_prefix[] =
{
    "vpcie3v3",
    "vpcie3v3aux",
    "vpcie12v",
};

struct brcm_pcie;

struct inbound_win
{
    rt_uint64_t size;
    rt_uint64_t pci_offset;
    rt_uint64_t cpu_addr;
};

struct pcie_cfg_soc_data
{
    const int *reg_offsets;
    const enum brcm_pcie_type type;
    const rt_bool_t has_phy;

#define CFG_QUIRK_AVOID_BRIDGE_SHUTDOWN     RT_BIT(0)
#define CFG_QUIRK_NO_SSC                    RT_BIT(1)
    const rt_uint32_t quirks;
    rt_uint8_t num_inbound_wins;

    rt_err_t (*perst_set)(struct brcm_pcie *pcie, rt_uint32_t val);
    rt_err_t (*bridge_sw_init_set)(struct brcm_pcie *pcie, rt_uint32_t val);
    rt_err_t (*post_setup)(struct brcm_pcie *pcie);
};

struct brcm_msi
{
    int irq;
    void *pcie_base;
    void *intr_base;

    struct rt_pic inner_pic;
    rt_uint64_t data_address;

    rt_bool_t legacy;
    /* Some chips have MSIs in bits [31..24] of a shared register. */
    int legacy_shift;

    int msi_max_nr;
    RT_BITMAP_DECLARE(msi_map, 64);
    struct rt_spinlock lock;
};

/* Internal PCIe Host Controller Information. */
struct brcm_pcie
{
    const struct pcie_cfg_soc_data *soc_data;
    struct rt_device *dev;

    void *base;

    rt_bool_t ssc;                  /* Spread Spectrum Clocking */
    rt_bool_t l1ss;                 /* L1 PM Substates */
    rt_bool_t ep_wakeup_capable;
    rt_uint32_t qos_map;
    rt_uint32_t generation;
    rt_uint32_t misc_revision;
    rt_uint32_t tperst_clk_ms;

    rt_size_t memc_nr;
    rt_uint64_t memc_size[PCIE_BRCM_MAX_MEMC];

    struct rt_clk *clk;
    struct rt_reset_control *rescal_rstc;
    struct rt_reset_control *perst_rstc;
    struct rt_reset_control *bridge_rstc;
    struct rt_reset_control *swinit_rstc;
    struct rt_regulator *supplies[RT_ARRAY_SIZE(supplies_prefix)];

    struct brcm_msi *msi;
    rt_uint64_t msi_data_address;

    struct rt_pci_host_bridge *bridge;

    struct inbound_win inbound_wins[PCIE_BRCM_MAX_INBOUND_WINS];
    rt_uint8_t num_inbound_wins;
};

static void brcm_pcie_reapply_7712_maps(struct brcm_pcie *pcie);

rt_inline void replace_u32_bitfield(rt_uint32_t *p, rt_uint32_t val, rt_uint32_t field)
{
    *p = (*p & ~field) | ((val & (field / (field & -field))) * (field & -field));
}

rt_inline void replace_u16_bitfield(rt_uint16_t *p, rt_uint16_t val, rt_uint16_t field)
{
    *p = (*p & ~field) | ((val & (field / (field & -field))) * (field & -field));
}

rt_inline int __fls64(rt_uint64_t x)
{
    const rt_uint64_t bits_per_u64 = (sizeof(x) * 8);
    int num = bits_per_u64 - 1;

    if (x == 0)
    {
        return 0;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 32))))
    {
        num -= 32;
        x <<= 32;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 16))))
    {
        num -= 16;
        x <<= 16;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 8))))
    {
        num -= 8;
        x <<= 8;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 4))))
    {
        num -= 4;
        x <<= 4;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 2))))
    {
        num -= 2;
        x <<= 2;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 1))))
    {
        num -= 1;
    }

    return num + 1;
}

rt_uint32_t __hweight32(rt_uint32_t w)
{
    rt_uint32_t res = w - ((w >> 1) & 0x55555555);
    res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
    res = (res + (res >> 4)) & 0x0f0f0f0f;
    res = res + (res >> 8);
    return (res + (res >> 16)) & 0x000000ff;
}

rt_inline rt_bool_t is_bmips(const struct brcm_pcie *pcie)
{
    const struct pcie_cfg_soc_data *soc_data = pcie->soc_data;

    return soc_data->type == BCM7435 || soc_data->type == BCM7425;
}

/*
 * This is to convert the size of the inbound "BAR" region to the
 * non-linear values of PCIE_X_MISC_RC_BAR[123]_CONFIG_LO.SIZE
 */
static int brcm_pcie_encode_ibar_size(rt_uint64_t size)
{
    int log2_in = rt_ilog2(size);

    if (log2_in >= 12 && log2_in <= 15)
    {
        /* Covers 4KB to 32KB (inclusive) */
        return (log2_in - 12) + 0x1c;
    }
    else if (log2_in >= 16 && log2_in <= 36)
    {
        /* Covers 64KB to 64GB, (inclusive) */
        return log2_in - 15;
    }

    /* Something is awry so disable */
    return 0;
}

static rt_uint32_t brcm_pcie_mdio_form_pkt(int port, int regad, int cmd)
{
    rt_uint32_t pkt = 0;

    pkt |= RT_FIELD_PREP(MDIO_PORT_EXT_MASK, port >> 4);
    pkt |= RT_FIELD_PREP(MDIO_PORT_MASK, port);
    pkt |= RT_FIELD_PREP(MDIO_REGAD_MASK, regad);
    pkt |= RT_FIELD_PREP(MDIO_CMD_MASK, cmd);

    return pkt;
}

/* Negative return value indicates error */
static rt_err_t brcm_pcie_mdio_read(void *base,
        rt_uint8_t port, rt_uint8_t regad, rt_uint32_t *val)
{
    rt_uint32_t data;

    HWREG32(base + PCIE_RC_DL_MDIO_ADDR) =
            brcm_pcie_mdio_form_pkt(port, regad, MDIO_CMD_READ);
    data = HWREG32(base + PCIE_RC_DL_MDIO_ADDR);

    data = HWREG32(base + PCIE_RC_DL_MDIO_RD_DATA);

    for (int tries = 0; !MDIO_RD_DONE(data) && tries < 10; ++tries)
    {
        rt_hw_us_delay(10);
        data = HWREG32(base + PCIE_RC_DL_MDIO_RD_DATA);
    }

    *val = RT_FIELD_GET(MDIO_DATA_MASK, data);

    return MDIO_RD_DONE(data) ? 0 : -RT_EIO;
}

/* Negative return value indicates error */
static rt_err_t brcm_pcie_mdio_write(void *base,
        rt_uint8_t port, rt_uint8_t regad, rt_uint16_t wrdata)
{
    rt_uint32_t data;

    HWREG32(base + PCIE_RC_DL_MDIO_ADDR) =
            brcm_pcie_mdio_form_pkt(port, regad, MDIO_CMD_WRITE);
    data = HWREG32(base + PCIE_RC_DL_MDIO_ADDR);
    HWREG32(base + PCIE_RC_DL_MDIO_WR_DATA) = MDIO_DATA_DONE_MASK | wrdata;

    data = HWREG32(base + PCIE_RC_DL_MDIO_WR_DATA);

    for (int tries = 0; !MDIO_WT_DONE(data) && tries < 10; ++tries)
    {
        rt_hw_us_delay(10);
        data = HWREG32(base + PCIE_RC_DL_MDIO_WR_DATA);
    }

    return MDIO_WT_DONE(data) ? 0 : -RT_EIO;
}

/*
 * Configures device for Spread Spectrum Clocking (SSC) mode;
 * a negative return value indicates error.
 */
static rt_err_t brcm_pcie_set_ssc(struct brcm_pcie *pcie)
{
    int pll, ssc;
    rt_err_t err;
    rt_uint32_t tmp;

    if ((err = brcm_pcie_mdio_write(pcie->base,
            MDIO_PORT0, SET_ADDR_OFFSET, SSC_REGS_ADDR)) < 0)
    {
        return err;
    }

    if ((err = brcm_pcie_mdio_read(pcie->base,
            MDIO_PORT0, SSC_CNTL_OFFSET, &tmp)) < 0)
    {
        return err;
    }

    replace_u32_bitfield(&tmp, 1, SSC_CNTL_OVRD_EN_MASK);
    replace_u32_bitfield(&tmp, 1, SSC_CNTL_OVRD_VAL_MASK);

    if ((err = brcm_pcie_mdio_write(pcie->base,
            MDIO_PORT0, SSC_CNTL_OFFSET, tmp)) < 0)
    {
        return err;
    }

    rt_hw_us_delay(1500);

    if ((err = brcm_pcie_mdio_read(pcie->base,
            MDIO_PORT0, SSC_STATUS_OFFSET, &tmp)) < 0)
    {
        return err;
    }

    ssc = RT_FIELD_GET(SSC_STATUS_SSC_MASK, tmp);
    pll = RT_FIELD_GET(SSC_STATUS_PLL_LOCK_MASK, tmp);

    return ssc && pll ? 0 : -RT_EIO;
}

/*
 * SerDes MDIO refclk programming for BCM7712/2712 (54MHz xosc).
 * Must run after SERDES_IDDQ is cleared.
 */
static void brcm_pcie_delay_ms(rt_uint32_t ms);

static rt_err_t brcm_pcie_serdes_munge_pll(struct brcm_pcie *pcie)
{
    void *base = pcie->base;
    const rt_uint16_t data[] =
    {
        0x50b9, 0xbda1, 0x0094, 0x97b4, 0x5030, 0x5030, 0x0007
    };
    const rt_uint8_t regs[] =
    {
        0x16, 0x17, 0x18, 0x19, 0x1b, 0x1c, 0x1e
    };
    rt_err_t err;

    if ((err = brcm_pcie_mdio_write(base, MDIO_PORT0, SET_ADDR_OFFSET, 0x1600)))
    {
        return err;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(regs); ++i)
    {
        if ((err = brcm_pcie_mdio_write(base, MDIO_PORT0, regs[i], data[i])))
        {
            return err;
        }
    }

    rt_hw_us_delay(200);

    return RT_EOK;
}

static void brcm_pcie_serdes_pm_clk_period(struct brcm_pcie *pcie)
{
    rt_uint32_t tmp;
    void *base = pcie->base;

    /*
     * L1SS sub-state timers: PM clock period 18.52ns (1/54MHz, round down).
     */
    tmp = HWREG32(base + PCIE_RC_PL_PHY_CTL_15);
    tmp &= ~PCIE_RC_PL_PHY_CTL_15_PM_CLK_PERIOD_MASK;
    tmp |= 0x12;
    HWREG32(base + PCIE_RC_PL_PHY_CTL_15) = tmp;
}

/* Limits operation to a specific generation (1, 2, or 3) */
static void brcm_pcie_set_generation(struct brcm_pcie *pcie, int generation)
{
    rt_uint16_t lnkctl2;
    rt_uint32_t lnkcap;

    lnkctl2 = HWREG16(pcie->base + BRCM_PCIE_CAP_REGS + PCIER_LINK_CTL2);
    lnkcap = HWREG32(pcie->base + BRCM_PCIE_CAP_REGS + PCIER_LINK_CAP);

    replace_u32_bitfield(&lnkcap, generation, PCIEM_LINK_CAP_MAX_SPEED);
    HWREG32(pcie->base + BRCM_PCIE_CAP_REGS + PCIER_LINK_CAP) = lnkcap;

    replace_u16_bitfield(&lnkctl2, generation, PCIEM_LNKCTL2_TLS);
    HWREG16(pcie->base + BRCM_PCIE_CAP_REGS + PCIER_LINK_CTL2) = lnkctl2;
}

static void brcm_pcie_set_outbound_win(struct brcm_pcie *pcie, rt_uint32_t win,
        rt_uint64_t cpu_addr, rt_uint64_t pcie_addr, rt_uint64_t size)
{
    int high_addr_shift;
    rt_ubase_t cpu_addr_mb, limit_addr_mb;
    rt_uint32_t cpu_addr_mb_high, limit_addr_mb_high, tmp;

    /* Set the base of the pcie_addr window */
    HWREG32(pcie->base + PCIE_MEM_WIN0_LO(win)) = rt_lower_32_bits(pcie_addr);
    HWREG32(pcie->base + PCIE_MEM_WIN0_HI(win)) = rt_upper_32_bits(pcie_addr);

    /* Write the addr base & limit lower bits (in MBs) */
    cpu_addr_mb = cpu_addr / SIZE_MB;
    limit_addr_mb = (cpu_addr + size - 1) / SIZE_MB;

    tmp = HWREG32(pcie->base + PCIE_MEM_WIN0_BASE_LIMIT(win));
    replace_u32_bitfield(&tmp, cpu_addr_mb,
            PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_BASE_MASK);
    replace_u32_bitfield(&tmp, limit_addr_mb,
            PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_LIMIT_MASK);
    HWREG32(pcie->base + PCIE_MEM_WIN0_BASE_LIMIT(win)) = tmp;

    if (is_bmips(pcie))
    {
        return;
    }

    /* Write the cpu & limit addr upper bits */
    high_addr_shift = __hweight32(PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_BASE_MASK);

    cpu_addr_mb_high = cpu_addr_mb >> high_addr_shift;
    tmp = HWREG32(pcie->base + PCIE_MEM_WIN0_BASE_HI(win));
    replace_u32_bitfield(&tmp, cpu_addr_mb_high,
            PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI_BASE_MASK);
    HWREG32(pcie->base + PCIE_MEM_WIN0_BASE_HI(win)) = tmp;

    limit_addr_mb_high = limit_addr_mb >> high_addr_shift;
    tmp = HWREG32(pcie->base + PCIE_MEM_WIN0_LIMIT_HI(win));
    replace_u32_bitfield(&tmp, limit_addr_mb_high,
            PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI_LIMIT_MASK);
    HWREG32(pcie->base + PCIE_MEM_WIN0_LIMIT_HI(win)) = tmp;
}

static void brcm_pcie_misc_ctrl_enable_access(struct brcm_pcie *pcie)
{
    void *base = pcie->base;
    rt_uint32_t tmp = HWREG32(base + PCIE_MISC_MISC_CTRL);
    rt_uint32_t burst;

    if (is_bmips(pcie))
    {
        burst = 0x1;
    }
    else if (pcie->soc_data->type == BCM2711)
    {
        burst = 0x0;
    }
    else if (pcie->soc_data->type == BCM7278)
    {
        burst = 0x3;
    }
    else
    {
        burst = 0x2;
    }

    replace_u32_bitfield(&tmp, 1, PCIE_MISC_MISC_CTRL_SCB_ACCESS_EN_MASK);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_MISC_CTRL_CFG_READ_UR_MODE_MASK);
    replace_u32_bitfield(&tmp, burst, PCIE_MISC_MISC_CTRL_MAX_BURST_SIZE_MASK);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_MISC_CTRL_PCIE_RCB_MPS_MODE_MASK);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_MISC_CTRL_PCIE_RCB_64B_MODE_MASK);
    HWREG32(base + PCIE_MISC_MISC_CTRL) = tmp;
}

static void brcm_pcie_apply_outbound_wins(struct brcm_pcie *pcie)
{
    struct rt_pci_host_bridge *bridge = pcie->bridge;
    int num_out_wins = 0;

    for (int i = 0; i < bridge->bus_regions_nr; ++i)
    {
        struct rt_pci_bus_region *region = &bridge->bus_regions[i];

        if (region->flags != PCI_BUS_REGION_F_MEM &&
            region->flags != PCI_BUS_REGION_F_PREFETCH)
        {
            continue;
        }

        if (num_out_wins >= BRCM_NUM_PCIE_OUT_WINS)
        {
            LOG_E("Too many outbound wins");
            return;
        }

        if (is_bmips(pcie))
        {
            rt_uint64_t start = region->cpu_addr;
            rt_off_t offset = region->cpu_addr - region->phy_addr;
            rt_uint32_t nwins = region->size / 128 * SIZE_MB;

            if (nwins > BRCM_NUM_PCIE_OUT_WINS)
            {
                nwins = BRCM_NUM_PCIE_OUT_WINS;
            }

            for (int j = 0; j < nwins; ++j, start += 128 * SIZE_MB)
            {
                brcm_pcie_set_outbound_win(pcie, j, start, start - offset, 128 * SIZE_MB);
            }
            return;
        }

        brcm_pcie_set_outbound_win(pcie, num_out_wins,
                region->cpu_addr, region->phy_addr, region->size);
        ++num_out_wins;
    }
}

/* The controller is capable of serving in both RC and EP roles */
static rt_bool_t brcm_pcie_rc_mode(struct brcm_pcie *pcie)
{
    void *base = pcie->base;
    rt_uint32_t val = HWREG32(base + PCIE_MISC_PCIE_STATUS);

    return !!RT_FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_PORT_MASK, val);
}

static rt_bool_t brcm_pcie_link_up(struct brcm_pcie *pcie)
{
    rt_uint32_t val = HWREG32(pcie->base + PCIE_MISC_PCIE_STATUS);
    rt_uint32_t dla = RT_FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_DL_ACTIVE_MASK, val);
    rt_uint32_t plu = RT_FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_PHYLINKUP_MASK, val);

    return dla && plu;
}

static void brcm_pcie_prep_train_clk(struct brcm_pcie *pcie)
{
    rt_uint32_t tmp;
    void *base = pcie->base;

    tmp = HWREG32(base + HARD_DEBUG(pcie));
    tmp &= ~PCIE_CLKREQ_MASK;
    HWREG32(base + HARD_DEBUG(pcie)) = tmp;
}

static void brcm_pcie_delay_ms(rt_uint32_t ms)
{
    if (ms == 0)
    {
        return;
    }

    /*
     * Always busy-wait: link training runs during init (often before the
     * scheduler is fully ready). mdelay can yield or mis-time here.
     */
    rt_hw_us_delay(ms * 1000UL);
}

static void *brcm_pcie_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg)
{
    void *base;
    struct brcm_pcie *pcie = bus->sysdata;

    base = pcie->base;

    /* Accesses to the RC go right to the RC registers if !devfn */
    if (rt_pci_is_root_bus(bus))
    {
        return devfn ? RT_NULL : base + PCIE_ECAM_REG(reg);
    }

    /* An access to our HW w/o link-up will cause a CPU Abort */
    if (!brcm_pcie_link_up(pcie))
    {
        return RT_NULL;
    }

    /* For devices, write to the config space index register */
    HWREG32(pcie->base + IDX_ADDR(pcie)) = PCIE_ECAM_OFFSET(bus->number, devfn, 0);
    return base + DATA_ADDR(pcie) + PCIE_ECAM_REG(reg);
}

static void *brcm7425_pcie_map(struct rt_pci_bus *bus, rt_uint32_t devfn, int reg)
{
    void *base;
    struct brcm_pcie *pcie = bus->sysdata;

    base = pcie->base;

    /* Accesses to the RC go right to the RC registers if !devfn */
    if (rt_pci_is_root_bus(bus))
    {
        return devfn ? RT_NULL : base + PCIE_ECAM_REG(reg);
    }

    /* An access to our HW w/o link-up will cause a CPU Abort */
    if (!brcm_pcie_link_up(pcie))
    {
        return RT_NULL;
    }

    /* For devices, write to the config space index register */
    HWREG32(base + IDX_ADDR(pcie)) = PCIE_ECAM_OFFSET(bus->number, devfn, reg);
    return base + DATA_ADDR(pcie);
}

static rt_err_t brcm_pcie_bridge_sw_init_set_generic(struct brcm_pcie *pcie, rt_uint32_t val)
{
    rt_err_t err;
    rt_uint32_t tmp, mask = RGR1_SW_INIT_1_INIT_GENERIC_MASK;
    rt_uint32_t shift = RGR1_SW_INIT_1_INIT_GENERIC_SHIFT;

    if (pcie->bridge_rstc)
    {
        if (val)
        {
            err = rt_reset_control_assert(pcie->bridge_rstc);
        }
        else
        {
            err = rt_reset_control_deassert(pcie->bridge_rstc);
        }

        return err;
    }

    tmp = HWREG32(pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
    tmp = (tmp & ~mask) | ((val << shift) & mask);
    HWREG32(pcie->base + PCIE_RGR1_SW_INIT_1(pcie)) = tmp;

    return RT_EOK;
}

static rt_err_t brcm_pcie_bridge_sw_init_set_7278(struct brcm_pcie *pcie, rt_uint32_t val)
{
    rt_uint32_t tmp, mask = RGR1_SW_INIT_1_INIT_7278_MASK;
    rt_uint32_t shift = RGR1_SW_INIT_1_INIT_7278_SHIFT;

    tmp = HWREG32(pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
    tmp = (tmp & ~mask) | ((val << shift) & mask);
    HWREG32(pcie->base + PCIE_RGR1_SW_INIT_1(pcie)) = tmp;

    return RT_EOK;
}

static rt_err_t brcm_pcie_perst_set_4908(struct brcm_pcie *pcie, rt_uint32_t val)
{
    rt_err_t err;

    if (!pcie->perst_rstc)
    {
        return -RT_EINVAL;
    }

    if (val)
    {
        err = rt_reset_control_assert(pcie->perst_rstc);
    }
    else
    {
        err = rt_reset_control_deassert(pcie->perst_rstc);
    }

    return err;
}

static rt_err_t brcm_pcie_perst_set_7278(struct brcm_pcie *pcie, rt_uint32_t val)
{
    rt_uint32_t tmp;

    /* Perst bit has moved and assert value is 0 */
    tmp = HWREG32(pcie->base + PCIE_MISC_PCIE_CTRL);
    replace_u32_bitfield(&tmp, !val, PCIE_MISC_PCIE_CTRL_PCIE_PERSTB_MASK);
    HWREG32(pcie->base +  PCIE_MISC_PCIE_CTRL) = tmp;

    return RT_EOK;
}

static rt_err_t brcm_pcie_perst_set_generic(struct brcm_pcie *pcie, rt_uint32_t val)
{
    rt_uint32_t tmp;

    tmp = HWREG32(pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
    replace_u32_bitfield(&tmp, val, PCIE_RGR1_SW_INIT_1_PERST_MASK);
    HWREG32(pcie->base + PCIE_RGR1_SW_INIT_1(pcie)) = tmp;

    return RT_EOK;
}

/*
 * access timeout may occur during L1SS sleep periods, even without the
 * presence of a PCIe access.
 */
static void brcm_extend_rbus_timeout(struct brcm_pcie *pcie)
{
    /* 4 seconds, our setting for L1SS */
    const rt_uint32_t timeout_us = 4000000;

    /* 7712 does not have this (RGR1) timer */
    if (pcie->soc_data->type == BCM7712)
    {
        return;
    }

    /* Each unit in timeout register is 1/216,000,000 seconds */
    HWREG32(pcie->base + PCIE_RGR1_SW_INIT_1(pcie) - 8) = 216 * timeout_us;
}

static void brcm_config_clkreq(struct brcm_pcie *pcie)
{
    rt_err_t err;
    void *base = pcie->base;
    rt_uint32_t clkreq_cntl, tmp;
    const char *mode = "default";

    err = rt_dm_dev_prop_read_string(pcie->dev, "brcm,clkreq-mode", &mode);

    if (err && err != -RT_EINVAL)
    {
        mode = "safe";
    }

    /*
     * brcm,enable-l1ss in DT documents capability; until ASPM is fully
     * handled in RT-Thread, force refclk on to avoid EP stuck in L1.x.
     */
    if (pcie->soc_data->type == BCM7712 &&
        rt_dm_dev_prop_read_bool(pcie->dev, "brcm,enable-l1ss"))
    {
        mode = "safe";
    }

    /* Start out assuming safe mode (both mode bits cleared) */
    clkreq_cntl = HWREG32(base + HARD_DEBUG(pcie));
    clkreq_cntl &= ~PCIE_CLKREQ_MASK;

    if (!rt_strcmp(mode, "no-l1ss"))
    {
        /*
         * "no-l1ss" -- Provides Clock Power Management, L0s, and
         * L1, but cannot provide L1 substate (L1SS) power
         * savings. If the downstream device connected to the RC is
         * L1SS capable AND the OS enables L1SS, all PCIe traffic
         * may abruptly halt, potentially hanging the system.
         */
        clkreq_cntl |= PCIE_MISC_HARD_PCIE_HARD_DEBUG_CLKREQ_DEBUG_ENABLE_MASK;
        /*
         * We want to un-advertise L1 substates because if the OS
         * tries to configure the controller into using L1 substate
         * power savings it may fail or hang when the RC HW is in
         * "no-l1ss" mode.
         */
        tmp = HWREG32(base + PCIE_RC_CFG_PRIV1_ROOT_CAP);
        replace_u32_bitfield(&tmp, 2, PCIE_RC_CFG_PRIV1_ROOT_CAP_L1SS_MODE_MASK);
        HWREG32(base + PCIE_RC_CFG_PRIV1_ROOT_CAP) = tmp;
    }
    else if (!rt_strcmp(mode, "default"))
    {
        /*
         * "default" -- Provides L0s, L1, and L1SS, but not
         * compliant to provide Clock Power Management;
         * specifically, may not be able to meet the Tclron max
         * timing of 400ns as specified in "Dynamic Clock Control",
         * section 3.2.5.2.2 of the PCIe spec.  This situation is
         * atypical and should happen only with older devices.
         */
        clkreq_cntl |= PCIE_MISC_HARD_PCIE_HARD_DEBUG_L1SS_ENABLE_MASK;
        brcm_extend_rbus_timeout(pcie);
    }
    else
    {
        /*
         * "safe" -- No power savings; refclk is driven by RC
         * unconditionally.
         */
        if (rt_strcmp(mode, "safe") != 0)
        {
            LOG_W("invalid 'brcm,clkreq-mode' DT string");
        }
        mode = "safe";
        clkreq_cntl |= PCIE_MISC_HARD_PCIE_HARD_DEBUG_REFCLK_OVRD_OUT_MASK;
        clkreq_cntl |= PCIE_MISC_HARD_PCIE_HARD_DEBUG_REFCLK_OVRD_ENABLE_MASK;
        tmp = HWREG32(base + PCIE_RC_CFG_PRIV1_ROOT_CAP);
        replace_u32_bitfield(&tmp, 2, PCIE_RC_CFG_PRIV1_ROOT_CAP_L1SS_MODE_MASK);
        HWREG32(base + PCIE_RC_CFG_PRIV1_ROOT_CAP) = tmp;
    }

    HWREG32(base + HARD_DEBUG(pcie)) = clkreq_cntl;
}


static rt_err_t brcm_pcie_start_link(struct brcm_pcie *pcie)
{
    rt_err_t err;
    rt_uint32_t tmp;
    rt_uint16_t tmp16;
    void *base = pcie->base;

    if (pcie->generation)
    {
        brcm_pcie_set_generation(pcie, pcie->generation);
    }

    brcm_pcie_prep_train_clk(pcie);

    if (pcie->tperst_clk_ms)
    {
        tmp = HWREG32(base + HARD_DEBUG(pcie));
        replace_u32_bitfield(&tmp, 1, PCIE_MISC_HARD_PCIE_HARD_DEBUG_PERST_ASSERT_MASK);
        HWREG32(base + HARD_DEBUG(pcie)) = tmp;

        if ((err = pcie->soc_data->perst_set(pcie, 0)))
        {
            return err;
        }
        brcm_pcie_delay_ms(pcie->tperst_clk_ms);

        tmp = HWREG32(base + HARD_DEBUG(pcie));
        replace_u32_bitfield(&tmp, 0, PCIE_MISC_HARD_PCIE_HARD_DEBUG_PERST_ASSERT_MASK);
        HWREG32(base + HARD_DEBUG(pcie)) = tmp;
    }
    else
    {
        if ((err = pcie->soc_data->perst_set(pcie, 0)))
        {
            return err;
        }
    }

    brcm_pcie_delay_ms(PCIE_RESET_CONFIG_WAIT_MS);

    for (int i = 0; i < 100 && !brcm_pcie_link_up(pcie); i += 5)
    {
        brcm_pcie_delay_ms(5);
    }

    if (!brcm_pcie_link_up(pcie))
    {
        LOG_E("%s: link down", rt_dm_dev_get_name(pcie->dev));
        return -RT_EINVAL;
    }

    brcm_config_clkreq(pcie);

    if (pcie->soc_data->post_setup)
    {
        /*
         * post_setup may run before the link is up; re-apply SerDes PLL
         * settings after training so downstream refclk is stable.
         */
        if ((err = brcm_pcie_serdes_munge_pll(pcie)))
        {
            LOG_W("post-train serdes munge failed: %s", rt_strerror(err));
        }
        else
        {
            brcm_pcie_serdes_pm_clk_period(pcie);
        }
    }

    if (pcie->ssc)
    {
        if (brcm_pcie_set_ssc(pcie))
        {
            LOG_E("Failed attempt to enter ssc mode");
        }
    }

    brcm_pcie_reapply_7712_maps(pcie);

    tmp16 = HWREG16(base + BRCM_PCIE_CAP_REGS + PCIER_ROOT_CAP);
    if (tmp16 & PCIEM_ROOT_CAP_CRS_VIS)
    {
        tmp16 = HWREG16(base + BRCM_PCIE_CAP_REGS + PCIER_ROOT_CTL);
        replace_u16_bitfield(&tmp16, 1, PCIEM_ROOT_CTL_CRS_VIS);
        HWREG16(base + BRCM_PCIE_CAP_REGS + PCIER_ROOT_CTL) = tmp16;
    }

    return RT_EOK;
}

static rt_err_t brcm_pcie_add_bus(struct rt_pci_bus *bus)
{
    rt_err_t err = RT_EOK;
    struct brcm_pcie *pcie = bus->sysdata;
    struct rt_device *dev = &bus->host_bridge->parent;

    if (!bus->parent)
    {
        return RT_EOK;
    }

    if (!rt_pci_is_root_bus(bus->parent))
    {
        return RT_EOK;
    }

    if (dev->ofw_node)
    {
        rt_size_t supplies = 0;

        for (int i = 0; i < RT_ARRAY_SIZE(pcie->supplies); ++i)
        {
            pcie->supplies[i] = rt_regulator_get(dev, supplies_prefix[i]);

            if (rt_is_err(pcie->supplies[i]))
            {
                err = rt_ptr_err(pcie->supplies[i]);

                while (i --> 0)
                {
                    rt_regulator_put(pcie->supplies[i]);
                    pcie->supplies[i] = RT_NULL;
                }

                return err;
            }
            else if (pcie->supplies[i])
            {
                ++supplies;
            }
        }

        if (!supplies)
        {
            goto _no_regulators;
        }

        for (int i = 0; i < RT_ARRAY_SIZE(pcie->supplies); ++i)
        {
            if (pcie->supplies[i])
            {
                if ((err = rt_regulator_enable(pcie->supplies[i])))
                {
                    LOG_E("Can't enable regulators for downstream device");

                    for (int i = 0; i < RT_ARRAY_SIZE(pcie->supplies); ++i)
                    {
                        rt_regulator_put(pcie->supplies[i]);
                        pcie->supplies[i] = RT_NULL;
                    }

                    return err;
                }
            }
        }
    }

_no_regulators:
    err = brcm_pcie_start_link(pcie);

    return err;
}

static rt_err_t brcm_pcie_remove_bus(struct rt_pci_bus *bus)
{
    struct brcm_pcie *pcie = bus->sysdata;

    for (int i = 0; i < RT_ARRAY_SIZE(pcie->supplies); ++i)
    {
        if (!rt_is_err_or_null(pcie->supplies[i]))
        {
            rt_regulator_disable(pcie->supplies[i]);
            rt_regulator_put(pcie->supplies[i]);
        }
    }

    return RT_EOK;
}

/* L23 is a low-power PCIe link state */
static void brcm_pcie_enter_l23(struct brcm_pcie *pcie)
{
    int l23;
    rt_uint32_t tmp;
    void *base = pcie->base;

    /* Assert request for L23 */
    tmp = HWREG32(base + PCIE_MISC_PCIE_CTRL);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_PCIE_CTRL_PCIE_L23_REQUEST_MASK);
    HWREG32(base + PCIE_MISC_PCIE_CTRL) = tmp;

    /* Wait up to 36 msec for L23 */
    tmp = HWREG32(base + PCIE_MISC_PCIE_STATUS);
    l23 = RT_FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_LINK_IN_L23_MASK, tmp);

    for (int i = 0; i < 15 && !l23; ++i)
    {
        rt_hw_us_delay(2200);

        tmp = HWREG32(base + PCIE_MISC_PCIE_STATUS);
        l23 = RT_FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_LINK_IN_L23_MASK, tmp);
    }

    if (!l23)
    {
        LOG_E("%s: failed to enter low-power link state", rt_dm_dev_get_name(pcie->dev));
    }
}

static rt_err_t brcm_phy_cntl(struct brcm_pcie *pcie, const int start)
{
    rt_err_t err = RT_EOK;
    void *base = pcie->base;
    rt_uint32_t val, tmp, combined_mask = 0;
    const int beg = start ? 0 : PCIE_DVT_PMU_PHY_CTRL_DAST_NFLDS - 1;
    const int end = start ? PCIE_DVT_PMU_PHY_CTRL_DAST_NFLDS : -1;
    static const rt_uint32_t shifts[PCIE_DVT_PMU_PHY_CTRL_DAST_NFLDS] =
    {
        PCIE_DVT_PMU_PHY_CTRL_DAST_PWRDN_SHIFT,
        PCIE_DVT_PMU_PHY_CTRL_DAST_RESET_SHIFT,
        PCIE_DVT_PMU_PHY_CTRL_DAST_DIG_RESET_SHIFT,
    };
    static const rt_uint32_t masks[PCIE_DVT_PMU_PHY_CTRL_DAST_NFLDS] =
    {
        PCIE_DVT_PMU_PHY_CTRL_DAST_PWRDN_MASK,
        PCIE_DVT_PMU_PHY_CTRL_DAST_RESET_MASK,
        PCIE_DVT_PMU_PHY_CTRL_DAST_DIG_RESET_MASK,
    };

    for (int i = beg; i != end; start ? ++i : --i)
    {
        val = start ? RT_BIT_MASK(shifts[i]) : 0;

        tmp = HWREG32(base + PCIE_DVT_PMU_PHY_CTRL);
        tmp = (tmp & ~masks[i]) | (val & masks[i]);
        HWREG32(base + PCIE_DVT_PMU_PHY_CTRL) = tmp;

        rt_hw_us_delay(125);
        combined_mask |= masks[i];
    }

    tmp = HWREG32(base + PCIE_DVT_PMU_PHY_CTRL);
    val = start ? combined_mask : 0;

    if ((tmp & combined_mask) != val)
    {
        err = -RT_EIO;
        LOG_E("%s: failed to %s phy", rt_dm_dev_get_name(pcie->dev), start ? "start" : "stop");
    }

    return err;
}


static rt_err_t brcm_pcie_post_setup_bcm2712(struct brcm_pcie *pcie)
{
    rt_err_t err;
    rt_uint32_t tmp;
    rt_uint8_t qos_map[8];
    void *base = pcie->base;

    if ((err = brcm_pcie_serdes_munge_pll(pcie)))
    {
        return err;
    }

    rt_hw_us_delay(200);
    brcm_pcie_serdes_pm_clk_period(pcie);

    /*
     * BCM7712/2712 uses a UBUS-AXI bridge.
     * Suppress AXI error responses and return 1s for read failures.
     */
    tmp = HWREG32(base + PCIE_MISC_UBUS_CTRL);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_UBUS_CTRL_UBUS_PCIE_REPLY_ERR_DIS_MASK);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_UBUS_CTRL_UBUS_PCIE_REPLY_DECERR_DIS_MASK);
    HWREG32(base + PCIE_MISC_UBUS_CTRL) = tmp;
    HWREG32(base + PCIE_MISC_AXI_READ_ERROR_DATA) = 0xffffffff;

    /*
     * Adjust timeouts. The UBUS timeout also affects Configuration Request
     * Retry responses, as the request will get terminated if
     * either timeout expires, so both have to be a large value
     * (in clocks of 750MHz).
     * Set UBUS timeout to 250ms, then set RC config retry timeout
     * to be ~240ms.
     *
     * If CRSSVE=1 this will stop the core from blocking on a Retry
     * response, but does require the device to be well-behaved...
     */
    HWREG32(base + PCIE_MISC_UBUS_TIMEOUT) = 0xb2d0000;
    HWREG32(base + PCIE_MISC_RC_CONFIG_RETRY_TIMEOUT) = 0xaba0000;

    /*
     * BCM2712 has a configurable QoS mechanism that assigns TLP Traffic Classes
     * to separate AXI IDs with a configurable priority scheme.
     * Dynamic priority elevation is supported through reception of Type 1
     * Vendor Defined Messages, but several bugs make this largely ineffective.
     */

    /* Disable broken forwarding search. Set chicken bits for 2712D0 */
    tmp = HWREG32(base + PCIE_MISC_AXI_INTF_CTRL);
    tmp &= ~AXI_REQFIFO_EN_QOS_PROPAGATION;
    tmp |= AXI_EN_RCLK_QOS_ARRAY_FIX | AXI_EN_QOS_UPDATE_TIMING_FIX | AXI_DIS_QOS_GATING_IN_MASTER;
    HWREG32(base + PCIE_MISC_AXI_INTF_CTRL) = tmp;

    /*
     * Work around spurious QoS=0 assignments to inbound traffic.
     * If the QOS_UPDATE_TIMING_FIX bit is Reserved-0, then this is a
     * 2712C1 chip, or a single-lane RC. Use the best-effort alternative
     * which is to partially throttle AXI requests in-flight to SDRAM.
     */
    tmp = HWREG32(base + PCIE_MISC_AXI_INTF_CTRL);
    if (!(tmp & AXI_EN_QOS_UPDATE_TIMING_FIX))
    {
        tmp &= ~AXI_MASTER_MAX_OUTSTANDING_REQUESTS_MASK;
        tmp |= 15;
        HWREG32(base + PCIE_MISC_AXI_INTF_CTRL) = tmp;
    }

    /* Disable VDM reception by default */
    tmp = HWREG32(base + PCIE_MISC_CTRL_1);
    tmp &= ~PCIE_MISC_CTRL_1_EN_VDM_QOS_CONTROL_MASK;
    HWREG32(base + PCIE_MISC_CTRL_1) = tmp;

    /*
     * U-Boot enables BAR2 UBUS remap access for inbound EP MemWr (DMA).
     * MIP MSIX doorbell (PCI 0xff_ffff_f000) uses inbound BAR3 on 2712.
     */
    tmp = HWREG32(base + PCIE_MISC_UBUS_BAR2_CONFIG_REMAP);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_UBUS_BAR2_CONFIG_REMAP_ACCESS_ENABLE_MASK);
    HWREG32(base + PCIE_MISC_UBUS_BAR2_CONFIG_REMAP) = tmp;

    tmp = HWREG32(base + PCIE_MISC_UBUS_BAR3_CONFIG_REMAP);
    replace_u32_bitfield(&tmp, 1, PCIE_MISC_UBUS_BAR2_CONFIG_REMAP_ACCESS_ENABLE_MASK);
    HWREG32(base + PCIE_MISC_UBUS_BAR3_CONFIG_REMAP) = tmp;

    if (!rt_dm_dev_prop_read_u8_array_index(pcie->dev, "brcm,fifo-qos-map", 0, 4, qos_map))
    {
        /*
         * Backpressure mode - each element is QoS for each
         * quartile of FIFO level. Each TC gets the same map, because
         * this mode is intended for nonrealtime EPs.
         */
        tmp = 0;
        for (int i = 0; i < 4; i++)
        {
            /* Priorities range from 0-15 */
            qos_map[i] &= 0x0f;
            tmp |= qos_map[i] << (i * 4);
        }

        for (int i = 0; i < 8; i++)
        {
            HWREG32(base + PCIE_MISC_TC_QUEUE_TO_QOS_MAP(i)) = tmp;
        }
    }
    else if (!rt_dm_dev_prop_read_u8_array_index(pcie->dev, "brcm,vdm-qos-map", 0, 8, qos_map))
    {
        /* Enable VDM reception */
        tmp = HWREG32(base + PCIE_MISC_CTRL_1);
        tmp |= PCIE_MISC_CTRL_1_EN_VDM_QOS_CONTROL_MASK;
        HWREG32(base + PCIE_MISC_CTRL_1) = tmp;

        tmp = 0;
        for (int i = 0; i < 8; i++)
        {
            /* Priorities range from 0-15 */
            qos_map[i] &= 0x0f;
            tmp |= qos_map[i] << (i * 4);
        }
        /* Broken forwarding means no point separating panic priorities from normal */
        HWREG32(base + PCIE_MISC_VDM_PRIORITY_TO_QOS_MAP_LO) = tmp;
        HWREG32(base + PCIE_MISC_VDM_PRIORITY_TO_QOS_MAP_HI) = tmp;

        /* Match Vendor ID of 0 */
        HWREG32(base + PCIE_RC_TL_VDM_CTL1) = 0;

        /*
         * Forward VDMs to priority interface anyway -
         * useful for debugging starvation through the received VDM count fields.
         */
        tmp = HWREG32(base + PCIE_RC_TL_VDM_CTL0);
        tmp |= PCIE_RC_TL_VDM_CTL0_VDM_ENABLED_MASK |
            PCIE_RC_TL_VDM_CTL0_VDM_IGNORETAG_MASK |
            PCIE_RC_TL_VDM_CTL0_VDM_IGNOREVNDRID_MASK;
        HWREG32(base + PCIE_RC_TL_VDM_CTL0) = tmp;
    }

    return RT_EOK;
}

static const int pcie_offsets[] =
{
    [RGR1_SW_INIT_1]        = 0x9210,
    [EXT_CFG_INDEX]         = 0x9000,
    [EXT_CFG_DATA]          = 0x8000,
    [PCIE_HARD_DEBUG]       = 0x4204,
    [PCIE_INTR2_CPU_BASE]   = 0x4300,
};

static const int pcie_offsets_bcm7278[] =
{
    [RGR1_SW_INIT_1]        = 0xc010,
    [EXT_CFG_INDEX]         = 0x9000,
    [EXT_CFG_DATA]          = 0x8000,
    [PCIE_HARD_DEBUG]       = 0x4204,
    [PCIE_INTR2_CPU_BASE]   = 0x4300,
};

static const int pcie_offsets_bcm7425[] =
{
    [RGR1_SW_INIT_1]        = 0x8010,
    [EXT_CFG_INDEX]         = 0x8300,
    [EXT_CFG_DATA]          = 0x8304,
    [PCIE_HARD_DEBUG]       = 0x4204,
    [PCIE_INTR2_CPU_BASE]   = 0x4300,
};

static const int pcie_offsets_bcm7712[] =
{
    [RGR1_SW_INIT_1]        = 0x9210,
    [EXT_CFG_INDEX]         = 0x9000,
    [EXT_CFG_DATA]          = 0x8000,
    [PCIE_HARD_DEBUG]       = 0x4304,
    [PCIE_INTR2_CPU_BASE]   = 0x4400,
};

static const struct pcie_cfg_soc_data generic_cfg =
{
    .reg_offsets = pcie_offsets,
    .type = GENERIC,
    .perst_set = brcm_pcie_perst_set_generic,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
    .num_inbound_wins = 3,
};

static const struct pcie_cfg_soc_data bcm7425_cfg =
{
    .reg_offsets = pcie_offsets_bcm7425,
    .type = BCM7425,
    .perst_set = brcm_pcie_perst_set_generic,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
    .num_inbound_wins = 3,
};

static const struct pcie_cfg_soc_data bcm7435_cfg =
{
    .reg_offsets = pcie_offsets,
    .type = BCM7435,
    .perst_set = brcm_pcie_perst_set_generic,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
    .num_inbound_wins = 3,
};

static const struct pcie_cfg_soc_data bcm4908_cfg =
{
    .reg_offsets = pcie_offsets,
    .type = BCM4908,
    .perst_set = brcm_pcie_perst_set_4908,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
    .num_inbound_wins = 3,
};

static const struct pcie_cfg_soc_data bcm7278_cfg =
{
    .reg_offsets = pcie_offsets_bcm7278,
    .type = BCM7278,
    .perst_set = brcm_pcie_perst_set_7278,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_7278,
    .num_inbound_wins = 3,
};

static const struct pcie_cfg_soc_data bcm2711_cfg =
{
    .reg_offsets = pcie_offsets,
    .type = BCM2711,
    .perst_set = brcm_pcie_perst_set_generic,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
    .num_inbound_wins = 3,
};

static const struct pcie_cfg_soc_data bcm7216_cfg =
{
    .reg_offsets = pcie_offsets_bcm7278,
    .type = BCM7278,
    .perst_set = brcm_pcie_perst_set_7278,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_7278,
    .has_phy = RT_TRUE,
    .num_inbound_wins = 3,
};

static const struct pcie_cfg_soc_data bcm7712_cfg =
{
    .reg_offsets = pcie_offsets_bcm7712,
    .type = BCM7712,
    .perst_set = brcm_pcie_perst_set_7278,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
    .num_inbound_wins = 10,
};

static const struct pcie_cfg_soc_data bcm2712_cfg =
{
    .reg_offsets = pcie_offsets_bcm7712,
    .type = BCM7712,
    .perst_set = brcm_pcie_perst_set_7278,
    .bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
    .post_setup = brcm_pcie_post_setup_bcm2712,
    .quirks = CFG_QUIRK_AVOID_BRIDGE_SHUTDOWN | CFG_QUIRK_NO_SSC,
    .num_inbound_wins = 10,
};

static const struct rt_pci_ops brcm_pcie_ops =
{
    .add = brcm_pcie_add_bus,
    .remove = brcm_pcie_remove_bus,
    .map = brcm_pcie_map,
    .read = rt_pci_bus_read_config_uxx,
    .write = rt_pci_bus_write_config_uxx,
};

static const struct rt_pci_ops brcm7425_pcie_ops =
{
    .add = brcm_pcie_add_bus,
    .remove = brcm_pcie_remove_bus,
    .map = brcm7425_pcie_map,
    .read = rt_pci_bus_read_config_generic_u32,
    .write = rt_pci_bus_write_config_generic_u32,
};

static void brcm_msi_ack_irq(struct rt_pic_irq *pirq)
{
    struct brcm_msi *msi = pirq->pic->priv_data;

    HWREG32(msi->intr_base + MSI_INT_CLR) = 1 << (pirq->hwirq + msi->legacy_shift);
}

static void brcm_msi_compose_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    struct brcm_msi *msi = pirq->pic->priv_data;

    msg->address_lo = rt_lower_32_bits(msi->data_address);
    msg->address_hi = rt_upper_32_bits(msi->data_address);
    msg->data = (0xffff & PCIE_MISC_MSI_DATA_CONFIG_VAL_32) | pirq->hwirq;
}

static int brcm_msi_irq_alloc(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc)
{
    int irq, hwirq;
    rt_ubase_t level;
    struct rt_pic_irq *pirq;
    struct brcm_msi *msi = pic->priv_data;

    level = rt_spin_lock_irqsave(&msi->lock);
    hwirq = rt_bitmap_next_clear_bit(msi->msi_map, 0, msi->msi_max_nr);

    if (hwirq >= msi->msi_max_nr)
    {
        irq = -RT_EEMPTY;
        goto _out_lock;
    }

    rt_bitmap_set_bit(msi->msi_map, hwirq);

    irq = rt_pic_config_irq(pic, hwirq, hwirq);
    pirq = rt_pic_find_irq(pic, hwirq);
    pirq->mode = RT_IRQ_MODE_EDGE_RISING;

_out_lock:
    rt_spin_unlock_irqrestore(&msi->lock, level);

    return irq;
}

static void brcm_msi_irq_free(struct rt_pic *pic, int irq)
{
    rt_ubase_t level;
    struct rt_pic_irq *pirq;
    struct brcm_msi *msi = pic->priv_data;

    pirq = rt_pic_find_pirq(pic, irq);

    if (!pirq)
    {
        return;
    }

    level = rt_spin_lock_irqsave(&msi->lock);
    rt_bitmap_clear_bit(msi->msi_map, pirq->hwirq);
    rt_spin_unlock_irqrestore(&msi->lock, level);
}

const static struct rt_pic_ops brcm_msi_ops =
{
    .name = "BRCMSTB-MSI",
    .irq_ack = brcm_msi_ack_irq,
    .irq_mask = rt_pci_msi_mask_irq,
    .irq_unmask = rt_pci_msi_unmask_irq,
    .irq_compose_msi_msg = brcm_msi_compose_msi_msg,
    .irq_alloc_msi = brcm_msi_irq_alloc,
    .irq_free_msi = brcm_msi_irq_free,
};

static void brcm_pcie_msi_isr(int irqno, void *param)
{
    rt_uint32_t status;
    rt_uint32_t raw_status;
    struct rt_pic_irq *pirq;
    struct brcm_msi *msi = param;

    RT_UNUSED(irqno);

    raw_status = HWREG32(msi->intr_base + MSI_INT_STATUS);
    status = raw_status >> msi->legacy_shift;

    for (int bit = 0; bit < BRCM_INT_PCI_MSI_NR && status; ++bit)
    {
        if (!(RT_BIT(bit) & status))
        {
            continue;
        }

        pirq = rt_pic_find_irq(&msi->inner_pic, bit);
        brcm_msi_ack_irq(pirq);
        rt_pic_handle_isr(pirq);

        pirq = rt_pic_find_irq(&msi->inner_pic, bit + 32);
        brcm_msi_ack_irq(pirq);
        rt_pic_handle_isr(pirq);

        status &= ~RT_BIT(bit);
    }

    rt_hw_interrupt_umask(msi->irq);
}

static rt_err_t brcm_pcie_enable_msi(struct brcm_pcie *pcie)
{
    int irq;
    rt_uint32_t val;
    struct brcm_msi *msi;
    struct rt_device *dev = pcie->dev;

    if ((irq = rt_dm_dev_get_irq(dev, 1)) < 0)
    {
        LOG_E("Read map MSI interrupt error = %s", rt_strerror(irq));
        return irq;
    }

    if (!(msi = rt_calloc(1, sizeof(*msi))))
    {
        return -RT_ENOMEM;
    }

    msi->pcie_base = pcie->base;
    msi->data_address = pcie->msi_data_address;
    msi->irq = irq;
    msi->legacy = pcie->misc_revision < BRCM_PCIE_HW_REV_33;
    rt_spin_lock_init(&msi->lock);

    if (msi->legacy)
    {
        msi->intr_base = msi->pcie_base + PCIE_INTR2_CPU_BASE;
        msi->msi_max_nr = BRCM_INT_PCI_MSI_LEGACY_NR;
        msi->legacy_shift = 24;
    }
    else
    {
        msi->intr_base = msi->pcie_base + PCIE_MSI_INTR2_BASE;
        msi->msi_max_nr = 64;
        msi->legacy_shift = 0;
    }

    msi->inner_pic.priv_data = msi;
    msi->inner_pic.ops = &brcm_msi_ops;
    rt_pic_linear_irq(&msi->inner_pic, msi->msi_max_nr);
    rt_pic_user_extends(&msi->inner_pic);

    rt_hw_interrupt_install(msi->irq, brcm_pcie_msi_isr, msi, "brcm-pcie-msi");
    rt_hw_interrupt_umask(msi->irq);

    val = msi->legacy ? BRCM_INT_PCI_MSI_LEGACY_MASK : BRCM_INT_PCI_MSI_MASK;

    HWREG32(msi->intr_base + MSI_INT_MASK_CLR) = val;
    HWREG32(msi->intr_base + MSI_INT_CLR) = val;

    /*
     * The 0 bit of PCIE_MISC_MSI_BAR_CONFIG_LO is repurposed to MSI enable,
     * which we set to 1.
     */
    HWREG32(msi->pcie_base + PCIE_MISC_MSI_BAR_CONFIG_LO) = rt_lower_32_bits(msi->data_address) | 0x1;
    HWREG32(msi->pcie_base + PCIE_MISC_MSI_BAR_CONFIG_HI) = rt_upper_32_bits(msi->data_address);

    val = msi->legacy ? PCIE_MISC_MSI_DATA_CONFIG_VAL_8 : PCIE_MISC_MSI_DATA_CONFIG_VAL_32;
    HWREG32(msi->pcie_base + PCIE_MISC_MSI_DATA_CONFIG) = val;

    pcie->msi = msi;

    rt_ofw_data(dev->ofw_node) = &msi->inner_pic;
    rt_ofw_node_set_flag(dev->ofw_node, RT_OFW_F_READLY);

    return RT_EOK;
}

rt_inline rt_err_t brcm_phy_start(struct brcm_pcie *pcie)
{
    return pcie->soc_data->has_phy ? brcm_phy_cntl(pcie, 1) : RT_EOK;
}

rt_inline rt_err_t brcm_phy_stop(struct brcm_pcie *pcie)
{
    return pcie->soc_data->has_phy ? brcm_phy_cntl(pcie, 0) : RT_EOK;
}

static void brcm_pcie_turn_off(struct brcm_pcie *pcie)
{
    rt_uint32_t tmp;
    void *base = pcie->base;

    if (brcm_pcie_link_up(pcie))
    {
        brcm_pcie_enter_l23(pcie);
    }
    /* Assert fundamental reset */
    pcie->soc_data->perst_set(pcie, 1);

    /* Deassert request for L23 in case it was asserted */
    tmp = HWREG32(base + PCIE_MISC_PCIE_CTRL);
    replace_u32_bitfield(&tmp, 0, PCIE_MISC_PCIE_CTRL_PCIE_L23_REQUEST_MASK);
    HWREG32(base + PCIE_MISC_PCIE_CTRL) = tmp;

    if (pcie->soc_data->type != BCM2711)
    {
        /* Turn off SerDes */
        tmp = HWREG32(base + HARD_DEBUG(pcie));
        replace_u32_bitfield(&tmp, 1, PCIE_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK);
        HWREG32(base + HARD_DEBUG(pcie)) = tmp;
    }

    if (!(pcie->soc_data->quirks & CFG_QUIRK_AVOID_BRIDGE_SHUTDOWN))
    {
        /* Shutdown PCIe bridge */
        pcie->soc_data->bridge_sw_init_set(pcie, 1);
    }
}

static void add_inbound_win(struct inbound_win *b, rt_uint8_t *count,
        rt_uint64_t size, rt_uint64_t cpu_addr, rt_uint64_t pci_offset)
{
    b->size = size;
    b->cpu_addr = cpu_addr;
    b->pci_offset = pci_offset;
    (*count)++;
}

/*
 * Debian DT omits the MIP doorbell dma-ranges entry present in bcm2712.dtsi.
 * EP MSIX MemWr to brcm,msi-pci-addr must inbound-map to the MIP MMIO block.
 */
static void brcm_pcie_add_mip_doorbell_win(struct brcm_pcie *pcie,
        struct inbound_win *b, rt_uint8_t *n, const struct inbound_win *begin)
{
    struct rt_ofw_node *np, *msi_np;
    rt_uint32_t addr_cells[2];
    rt_uint64_t pci_door, cpu_door, reg_size;
    int i;

    if (pcie->soc_data->type != BCM7712 || !pcie->dev)
    {
        return;
    }

    np = pcie->dev->ofw_node;
    msi_np = rt_ofw_parse_phandle(np, "msi-parent", 0);
    if (!msi_np || msi_np == np)
    {
        rt_ofw_node_put(msi_np);
        return;
    }

    if (!rt_ofw_node_is_compatible(msi_np, "brcm,bcm2712-mip-intc"))
    {
        rt_ofw_node_put(msi_np);
        return;
    }

    if (rt_ofw_prop_read_u32_array_index(msi_np, "brcm,msi-pci-addr", 0, 2, addr_cells) < 2 ||
            rt_ofw_get_address(msi_np, 0, &cpu_door, &reg_size))
    {
        rt_ofw_node_put(msi_np);
        return;
    }

    pci_door = ((rt_uint64_t)addr_cells[0] << 32) | addr_cells[1];

    for (i = 1; i <= *n; ++i)
    {
        if (begin[i].pci_offset == pci_door)
        {
            rt_ofw_node_put(msi_np);
            return;
        }
    }

    if (*n >= pcie->soc_data->num_inbound_wins)
    {
        LOG_W("No inbound slot for MIP doorbell pci=%#llx", (unsigned long long)pci_door);
        rt_ofw_node_put(msi_np);
        return;
    }

    add_inbound_win(b, n, 0x1000, cpu_door, pci_door);

    rt_ofw_node_put(msi_np);
}

static int brcm_pcie_get_inbound_wins(struct brcm_pcie *pcie, struct inbound_win inbound_wins[])
{
    rt_uint8_t n = 0;
    rt_uint64_t lowest_pcie_addr = ~(rt_uint64_t)0;
    rt_uint64_t pci_offset, cpu_addr, size = 0, tot_size = 0;
    struct rt_pci_host_bridge *bridge = pcie->bridge;
    /*
     * The HW registers (and PCIe) use order-1 numbering for BARs.  As such,
     * we have inbound_wins[0] unused and BAR1 starts at inbound_wins[1].
     */
    struct inbound_win *b_begin = &inbound_wins[1], *b = b_begin;

    /*
     * STB chips beside 7712 disable the first inbound window default.
     * Rather being mapped to system memory it is mapped to the
     * internal registers of the SoC.  This feature is deprecated, has
     * security considerations, and is not implemented in our modern
     * SoCs.
     */
    if (pcie->soc_data->type != BCM7712)
    {
        add_inbound_win(b++, &n, 0, 0, 0);
    }

    for (int i = 0; i < bridge->dma_regions_nr; ++i)
    {
        rt_uint64_t pcie_start, cpu_start;
        struct rt_pci_bus_region *region = &bridge->dma_regions[i];

        pcie_start = region->phy_addr;
        cpu_start = region->cpu_addr;

        size = region->size;
        tot_size += size;

        if (pcie_start < lowest_pcie_addr)
        {
            lowest_pcie_addr = pcie_start;
        }

        /*
         * 7712 and newer chips may have many BARs, with each
         * offering a non-overlapping viewport to system memory.
         * That being said, each BARs size must still be a power of two.
         */
        if (pcie->soc_data->type == BCM7712)
        {
            add_inbound_win(b++, &n, size, cpu_start, pcie_start);
        }

        if (n > pcie->soc_data->num_inbound_wins)
        {
            break;
        }
    }

    if (lowest_pcie_addr == ~(rt_uint64_t)0)
    {
        return -RT_EINVAL;
    }

    /*
     * 7712 and newer chips do not have an internal memory mapping system
     * that enables multiple memory controllers.  As such, it can return
     * now w/o doing special configuration.
     */
    if (pcie->soc_data->type == BCM7712)
    {
        brcm_pcie_add_mip_doorbell_win(pcie, b, &n, inbound_wins);

        if (n > pcie->soc_data->num_inbound_wins)
        {
            LOG_E("Too many inbound windows (%u)", n);
            return -RT_EINVAL;
        }

        return n;
    }

    pcie->memc_nr = rt_dm_dev_prop_read_u64_array_index(pcie->dev,
            "brcm,scb-sizes", 0, PCIE_BRCM_MAX_MEMC, pcie->memc_size);

    if ((rt_ssize_t)pcie->memc_nr <= 0)
    {
        /* Make an educated guess */
        pcie->memc_nr = 1;
        pcie->memc_size[0] = 1ULL << __fls64(tot_size - 1);
    }

    /* Each memc is viewed through a "port" that is a power of 2 */
    for (int i = 0, size = 0; i < pcie->memc_nr; ++i)
    {
        size += pcie->memc_size[i];
    }

    /* Our HW mandates that the window size must be a power of 2 */
    size = 1ULL << __fls64(size - 1);

    /*
     * Pi4 firmware rewrites dma-ranges before boot.
     * Ignore bogus brcm,scb-sizes and derive the inbound aperture from the
     * parsed dma-ranges total instead.
     */
    if (pcie->soc_data->type == BCM2711)
    {
        if (tot_size >= SIZE_MB)
        {
            rt_uint64_t want = 1ULL << __fls64(tot_size - 1);

            if (size < want)
            {
                size = want;
            }
        }
        else if (lowest_pcie_addr == 0x400000000ULL)
        {
            size = 2ULL * SIZE_GB;
        }

    }

    /*
     * For STB chips, the BAR2 cpu_addr is hardwired to the start
     * of system memory, so we set it to 0.
     */
    cpu_addr = 0;
    pci_offset = lowest_pcie_addr;

    /*
     * We validate the inbound memory view even though we should trust
     * whatever the device-tree provides. This is because of an HW issue on
     * early Raspberry Pi 4's revisions (bcm2711). It turns out its
     * firmware has to dynamically edit dma-ranges due to a bug on the
     * PCIe controller integration, which prohibits any access above the
     * lower 3GB of memory. Given this, we decided to keep the dma-ranges
     * in check, avoiding hard to debug device-tree related issues in the
     * future:
     *
     * The PCIe host controller by design must set the inbound viewport to
     * be a contiguous arrangement of all of the system's memory.  In
     * addition, its size mut be a power of two.  To further complicate
     * matters, the viewport must start on a pcie-address that is aligned
     * on a multiple of its size.  If a portion of the viewport does not
     * represent system memory -- e.g. 3GB of memory requires a 4GB
     * viewport -- we can map the outbound memory in or after 3GB and even
     * though the viewport will overlap the outbound memory the controller
     * will know to send outbound memory downstream and everything else
     * upstream.
     *
     * For example:
     *
     * - The best-case scenario, memory up to 3GB, is to place the inbound
     *   region in the first 4GB of pcie-space, as some legacy devices can
     *   only address 32bits. We would also like to put the MSI under 4GB
     *   as well, since some devices require a 32bit MSI target address.
     *
     * - If the system memory is 4GB or larger we cannot start the inbound
     *   region at location 0 (since we have to allow some space for
     *   outbound memory @ 3GB). So instead it will  start at the 1x
     *   multiple of its size
     */
    if (!size || (pci_offset & (size - 1)) ||
        (pci_offset < 4UL * SIZE_GB && pci_offset > 2UL * SIZE_GB))
    {
        return -RT_EINVAL;
    }

    /* Enable inbound window 2, the main inbound window for STB chips */
    add_inbound_win(b++, &n, size, cpu_addr, pci_offset);

    /*
     * Disable inbound window 3.  On some chips presents the same
     * window as #2 but the data appears in a settable endianness.
     */
    add_inbound_win(b++, &n, 0, 0, 0);

    return n;
}

static rt_uint32_t brcm_bar_reg_offset(int bar)
{
    if (bar <= 3)
    {
        return PCIE_MISC_RC_BAR1_CONFIG_LO + 8 * (bar - 1);
    }
    else
    {
        return PCIE_MISC_RC_BAR4_CONFIG_LO + 8 * (bar - 4);
    }
}

static rt_uint32_t brcm_ubus_reg_offset(int bar)
{
    if (bar <= 3)
    {
        return PCIE_MISC_UBUS_BAR1_CONFIG_REMAP + 8 * (bar - 1);
    }
    else
    {
        return PCIE_MISC_UBUS_BAR4_CONFIG_REMAP + 8 * (bar - 4);
    }
}

static void set_inbound_win_registers(struct brcm_pcie *pcie,
        const struct inbound_win *inbound_wins, rt_uint8_t num_inbound_wins)
{
    void *base = pcie->base;

    for (int i = 1; i <= num_inbound_wins; ++i)
    {
        rt_uint64_t pci_offset = inbound_wins[i].pci_offset;
        rt_uint64_t cpu_addr = inbound_wins[i].cpu_addr;
        rt_uint64_t size = inbound_wins[i].size;
        rt_uint32_t reg_offset = brcm_bar_reg_offset(i);
        rt_uint32_t tmp = rt_lower_32_bits(pci_offset);

        replace_u32_bitfield(&tmp, brcm_pcie_encode_ibar_size(size),
                PCIE_MISC_RC_BAR1_CONFIG_LO_SIZE_MASK);

        /* Write low */
        HWREG32(base + reg_offset) = tmp;
        /* Write high */
        HWREG32(base + reg_offset + 4) = rt_upper_32_bits(pci_offset);

        /*
         * Most STB chips:
         *     Do nothing.
         * 7712:
         *     All of their BARs need to be set.
         */
        if (pcie->soc_data->type == BCM7712)
        {
            /* BUS remap register settings */
            reg_offset = brcm_ubus_reg_offset(i);
            tmp = rt_lower_32_bits(cpu_addr) & ~0xfffU;
            tmp |= PCIE_MISC_UBUS_BAR1_CONFIG_REMAP_ACCESS_ENABLE_MASK;
            HWREG32(base + reg_offset) = tmp;
            HWREG32(base + reg_offset + 4) = rt_upper_32_bits(cpu_addr);
        }
    }
}

static void brcm_pcie_reapply_inbound_access(struct brcm_pcie *pcie)
{
    void *base = pcie->base;

    if (!base || pcie->soc_data->type != BCM7712)
    {
        return;
    }

    brcm_pcie_misc_ctrl_enable_access(pcie);

    /*
     * MIP MSIX doorbell lands on inbound BAR3 (PCI ff_ffff_f000), not BAR2.
     * Re-enable ACCESS on every active inbound UBUS remap after link events.
     */
    for (int i = 1; i <= pcie->num_inbound_wins; ++i)
    {
        rt_uint32_t reg = brcm_ubus_reg_offset(i);
        rt_uint32_t tmp;

        if (pcie->inbound_wins[i].size == 0)
        {
            continue;
        }

        tmp = HWREG32(base + reg);
        replace_u32_bitfield(&tmp, 1,
                PCIE_MISC_UBUS_BAR2_CONFIG_REMAP_ACCESS_ENABLE_MASK);
        HWREG32(base + reg) = tmp;
    }
}

static void brcm_pcie_reapply_7712_maps(struct brcm_pcie *pcie)
{
    if (pcie->soc_data->type != BCM7712 || !pcie->num_inbound_wins)
    {
        return;
    }

    brcm_pcie_reapply_inbound_access(pcie);
    set_inbound_win_registers(pcie, pcie->inbound_wins, pcie->num_inbound_wins);
    brcm_pcie_apply_outbound_wins(pcie);
}

static rt_err_t brcm_pcie_setup(struct brcm_pcie *pcie)
{
    rt_err_t err;
    void *base = pcie->base;
    int num_out_wins = 0, num_inbound_wins = 0;
    rt_uint32_t tmp, num_lanes = 0, num_lanes_cap = 0;
    struct rt_pci_host_bridge *bridge = pcie->bridge;
    struct inbound_win inbound_wins[PCIE_BRCM_MAX_INBOUND_WINS];

    /* Reset the bridge */
    pcie->soc_data->bridge_sw_init_set(pcie, 1);

    /* Ensure that PERST# is asserted; some bootloaders may deassert it. */
    if (pcie->soc_data->type == BCM2711)
    {
        if ((err = pcie->soc_data->perst_set(pcie, 1)))
        {
            pcie->soc_data->bridge_sw_init_set(pcie, 0);
            return err;
        }
    }

    rt_hw_us_delay(150);

    /* Take the bridge out of reset */
    if ((err = pcie->soc_data->bridge_sw_init_set(pcie, 0)))
    {
        return err;
    }

    /*
     * On some BCM2711 integrations this register window can raise SError
     * immediately after bridge reset deassert; skip this write there.
     */
    if (pcie->soc_data->type != BCM2711)
    {
        tmp = HWREG32(base + HARD_DEBUG(pcie));
        if (is_bmips(pcie))
        {
            tmp &= ~PCIE_BMIPS_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK;
        }
        else
        {
            tmp &= ~PCIE_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK;
        }
        HWREG32(base + HARD_DEBUG(pcie)) = tmp;
        /* Wait for SerDes to be stable */
        rt_hw_us_delay(150);
    }

    brcm_pcie_misc_ctrl_enable_access(pcie);

    num_inbound_wins = brcm_pcie_get_inbound_wins(pcie, inbound_wins);
    if (num_inbound_wins < 0)
    {
        return num_inbound_wins;
    }

    set_inbound_win_registers(pcie, inbound_wins, num_inbound_wins);
    pcie->num_inbound_wins = (rt_uint8_t)num_inbound_wins;
    rt_memcpy(pcie->inbound_wins, inbound_wins, sizeof(inbound_wins));

    if (!brcm_pcie_rc_mode(pcie))
    {
        LOG_E("PCIe RC controller misconfigured as Endpoint");
        return -RT_EINVAL;
    }

    tmp = HWREG32(base + PCIE_MISC_MISC_CTRL);

    for (int memc = 0; memc < pcie->memc_nr; memc++)
    {
        rt_uint32_t scb_size_val = rt_ilog2(pcie->memc_size[memc]) - 15;

        if (memc == 0)
        {
            replace_u32_bitfield(&tmp, scb_size_val, SCB_SIZE_MASK(0));
        }
        else if (memc == 1)
        {
            replace_u32_bitfield(&tmp, scb_size_val, SCB_SIZE_MASK(1));
        }
        else if (memc == 2)
        {
            replace_u32_bitfield(&tmp, scb_size_val, SCB_SIZE_MASK(2));
        }
    }

    HWREG32(base + PCIE_MISC_MISC_CTRL) = tmp;

    /*
     * We ideally want the MSI target address to be located in the 32bit
     * addressable memory area. Some devices might depend on it. This is
     * possible either when the inbound window is located above the lower
     * 4GB or when the inbound area is smaller than 4GB (taking into
     * account the rounding-up we're forced to perform).
     */
    if (inbound_wins[2].pci_offset >= (4UL * SIZE_GB) ||
        (inbound_wins[2].size + inbound_wins[2].pci_offset) < (4UL * SIZE_GB))
    {
        pcie->msi_data_address = BRCM_MSI_TARGET_ADDR_LT_4GB;
    }
    else
    {
        pcie->msi_data_address = BRCM_MSI_TARGET_ADDR_GT_4GB;
    }

    /* Don't advertise L0s capability if 'aspm-no-l0s' */
    tmp = HWREG32(base + PCIE_RC_CFG_PRIV1_LINK_CAPABILITY);
    if (rt_dm_dev_prop_read_bool(pcie->dev, "aspm-no-l0s"))
    {
        tmp &= ~PCI_EXP_LNKCAP_ASPM_L0S;
    }
    HWREG32(base + PCIE_RC_CFG_PRIV1_LINK_CAPABILITY) = tmp;

    num_lanes_cap = (tmp & PCIE_RC_CFG_PRIV1_LINK_CAPABILITY_MAX_LINK_WIDTH_MASK) >> 4;

    /*
     * Use hardware negotiated Max Link Width value by default. If the
     * "num-lanes" DT property is present, assume that the chip's default
     * link width capability information is incorrect/undesired and use the
     * specified value instead.
     */
    if (!rt_dm_dev_prop_read_u32(pcie->dev, "num-lanes", &num_lanes) &&
        num_lanes && num_lanes <= 4 && num_lanes_cap != num_lanes)
    {
        replace_u32_bitfield(&tmp, num_lanes,
                PCIE_RC_CFG_PRIV1_LINK_CAPABILITY_MAX_LINK_WIDTH_MASK);
        HWREG32(base + PCIE_RC_CFG_PRIV1_LINK_CAPABILITY) = tmp;
        tmp = HWREG32(base + PCIE_RC_PL_REG_PHY_CTL_1);
        replace_u32_bitfield(&tmp, 1,
                PCIE_RC_PL_REG_PHY_CTL_1_REG_P2_POWERDOWN_ENA_NOSYNC_MASK);
        HWREG32(base + PCIE_RC_PL_REG_PHY_CTL_1) = tmp;
    }

    /*
     * For config space accesses on the RC, show the right class for
     * a PCIe-PCIe bridge (the default setting is to be EP mode).
     */
    tmp = HWREG32(base + PCIE_RC_CFG_PRIV1_ID_VAL3);
    replace_u32_bitfield(&tmp, 0x060400,
            PCIE_RC_CFG_PRIV1_ID_VAL3_CLASS_CODE_MASK);
    HWREG32(base + PCIE_RC_CFG_PRIV1_ID_VAL3) = tmp;

    for (int i = 0; i < bridge->bus_regions_nr; ++i)
    {
        struct rt_pci_bus_region *region = &bridge->bus_regions[i];

        if (region->flags != PCI_BUS_REGION_F_MEM &&
            region->flags != PCI_BUS_REGION_F_PREFETCH)
        {
            continue;
        }

        if (num_out_wins >= BRCM_NUM_PCIE_OUT_WINS)
        {
            LOG_E("Too many outbound wins");
            return -RT_EINVAL;
        }

        if (is_bmips(pcie))
        {
            rt_uint64_t start = region->cpu_addr;
            rt_off_t offset = region->cpu_addr - region->phy_addr;
            rt_uint32_t nwins = region->size / 128 * SIZE_MB;

            /* BMIPS PCIe outbound windows have a 128MB max size */
            if (nwins > BRCM_NUM_PCIE_OUT_WINS)
            {
                nwins = BRCM_NUM_PCIE_OUT_WINS;
            }

            for (int j = 0; j < nwins; ++j, start += 128 * SIZE_MB)
            {
                brcm_pcie_set_outbound_win(pcie, j, start, start - offset, 128 * SIZE_MB);
            }
            break;
        }

        brcm_pcie_set_outbound_win(pcie, num_out_wins,
                region->cpu_addr, region->phy_addr, region->size);
        ++num_out_wins;
    }

    /* PCIe->SCB endian mode for BAR */
    tmp = HWREG32(base + PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1);
    replace_u32_bitfield(&tmp, PCIE_RC_CFG_VENDOR_SPECIFIC_REG1_LITTLE_ENDIAN,
            PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1_ENDIAN_MODE_BAR2_MASK);
    HWREG32(base + PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1) = tmp;

    if (pcie->soc_data->post_setup)
    {
        if ((err = pcie->soc_data->post_setup(pcie)))
        {
            return err;
        }
    }

    return RT_EOK;
}

static void brcm_pcie_free(struct brcm_pcie *pcie)
{
    if (pcie->bridge)
    {
        rt_pci_host_bridge_remove(pcie->bridge);
    }

    if (pcie->soc_data && pcie->soc_data->has_phy)
    {
        brcm_phy_stop(pcie);
    }

    brcm_pcie_turn_off(pcie);

    if (!rt_is_err_or_null(pcie->rescal_rstc))
    {
        rt_reset_control_assert(pcie->rescal_rstc);
        rt_reset_control_put(pcie->rescal_rstc);
    }

    if (!rt_is_err_or_null(pcie->perst_rstc))
    {
        rt_reset_control_put(pcie->perst_rstc);
    }

    if (!rt_is_err_or_null(pcie->bridge_rstc))
    {
        rt_reset_control_put(pcie->bridge_rstc);
    }

    if (!rt_is_err_or_null(pcie->swinit_rstc))
    {
        rt_reset_control_put(pcie->swinit_rstc);
    }

    if (!rt_is_err_or_null(pcie->clk))
    {
        rt_clk_disable_unprepare(pcie->clk);
    }

    if (pcie->base)
    {
        rt_iounmap(pcie->base);
    }

    rt_pci_host_bridge_free(pcie->bridge);
}

static rt_err_t brcm_pcie_get_optional_reset(struct rt_device *dev, const char *name,
        struct rt_reset_control **rstc)
{
    struct rt_reset_control *rc = rt_reset_control_get_by_name(dev, name);

    if (rt_is_err(rc))
    {
        if (rt_ptr_err(rc) == -RT_ENOENT)
        {
            *rstc = RT_NULL;
            return RT_EOK;
        }

        return rt_ptr_err(rc);
    }

    *rstc = rc;

    return RT_EOK;
}

static rt_err_t brcm_pcie_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct brcm_pcie *pcie;
    struct rt_device *dev = &pdev->parent;
    struct rt_pci_host_bridge *bridge;
    struct rt_ofw_node *np = dev->ofw_node, *msi_np;

    bridge = rt_pci_host_bridge_alloc(sizeof(*pcie));

    if (!bridge)
    {
        return -RT_ENOMEM;
    }

    pcie = (void *)bridge->priv;
    pcie->soc_data = pdev->id->data;
    pcie->dev = dev;
    pcie->bridge = bridge;

    pcie->base = rt_dm_dev_iomap(dev, 0);

    if (!pcie->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    pcie->clk = rt_clk_get_by_name(dev, "sw_pcie");

    if (rt_is_err(pcie->clk))
    {
        if (rt_ptr_err(pcie->clk) != -RT_ENOENT)
        {
            err = rt_ptr_err(pcie->clk);
            goto _fail;
        }

        pcie->clk = RT_NULL;
    }
    else if ((err = rt_clk_prepare_enable(pcie->clk)))
    {
        LOG_E("%s: could not enable clock", rt_dm_dev_get_name(dev));
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32(dev, "max-link-speed", &pcie->generation))
    {
        pcie->generation = 0;
    }

    pcie->ssc = rt_dm_dev_prop_read_bool(dev, "brcm,enable-ssc");
    rt_dm_dev_prop_read_u32(dev, "brcm,tperst-clk-ms", &pcie->tperst_clk_ms);

    if ((err = brcm_pcie_get_optional_reset(dev, "rescal", &pcie->rescal_rstc)))
    {
        goto _fail;
    }

    if ((err = brcm_pcie_get_optional_reset(dev, "perst", &pcie->perst_rstc)))
    {
        goto _fail;
    }

    if ((err = brcm_pcie_get_optional_reset(dev, "bridge", &pcie->bridge_rstc)))
    {
        goto _fail;
    }

    if ((err = brcm_pcie_get_optional_reset(dev, "swinit", &pcie->swinit_rstc)))
    {
        goto _fail;
    }

    pcie->soc_data->bridge_sw_init_set(pcie, 0);

    if (pcie->swinit_rstc)
    {
        if ((err = rt_reset_control_assert(pcie->swinit_rstc)))
        {
            goto _fail;
        }

        rt_hw_us_delay(1);

        if ((err = rt_reset_control_deassert(pcie->swinit_rstc)))
        {
            goto _fail;
        }
    }

    if (pcie->rescal_rstc &&
        (err = rt_reset_control_reset(pcie->rescal_rstc)))
    {
        goto _fail;
    }

    if ((err = brcm_phy_start(pcie)))
    {
        goto _fail;
    }

    bridge->parent.ofw_node = np;

    if ((err = rt_pci_host_bridge_init(bridge)))
    {
        goto _fail;
    }

    if ((err = brcm_pcie_setup(pcie)))
    {
        goto _fail;
    }

    pcie->misc_revision = HWREG32(pcie->base + PCIE_MISC_REVISION);

    if (pcie->soc_data->type == BCM4908 &&
        pcie->misc_revision >= BRCM_PCIE_HW_REV_3_20)
    {
        LOG_E("%s: hardware revision with unsupported PERST# setup",
                rt_dm_dev_get_name(dev));
        err = -RT_EINVAL;
        goto _fail;
    }

    msi_np = rt_ofw_parse_phandle(np, "msi-parent", 0);

    if (msi_np == np)
    {
        if ((err = brcm_pcie_enable_msi(pcie)))
        {
            LOG_E("%s: probe ofw internal MSI error = %s",
                    rt_dm_dev_get_name(dev), rt_strerror(err));

            goto _fail;
        }
    }

    rt_ofw_node_put(msi_np);

    bridge->ops = pcie->soc_data->type == BCM7425 ? &brcm7425_pcie_ops : &brcm_pcie_ops;
    bridge->sysdata = pcie;

    if ((err = rt_pci_host_bridge_probe(bridge)))
    {
        goto _fail;
    }

    if (!brcm_pcie_link_up(pcie))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    brcm_pcie_reapply_7712_maps(pcie);

    dev->user_data = pcie;

    return RT_EOK;

_fail:
    if (pcie->msi)
    {
        rt_pic_cancel_irq(&pcie->msi->inner_pic);
    }

    brcm_pcie_free(pcie);

    return err;
}

static rt_err_t brcm_pcie_remove(struct rt_platform_device *pdev)
{
    struct brcm_pcie *pcie = pdev->parent.user_data;

    brcm_pcie_free(pcie);

    return RT_EOK;
}

static const struct rt_ofw_node_id brcm_pcie_ofw_ids[] =
{
    { .compatible = "brcm,bcm2711-pcie", .data = &bcm2711_cfg },
    { .compatible = "brcm,bcm2712-pcie", .data = &bcm2712_cfg },
    { .compatible = "brcm,bcm4908-pcie", .data = &bcm4908_cfg },
    { .compatible = "brcm,bcm7211-pcie", .data = &generic_cfg },
    { .compatible = "brcm,bcm7278-pcie", .data = &bcm7278_cfg },
    { .compatible = "brcm,bcm7216-pcie", .data = &bcm7216_cfg },
    { .compatible = "brcm,bcm7445-pcie", .data = &generic_cfg },
    { .compatible = "brcm,bcm7435-pcie", .data = &bcm7435_cfg },
    { .compatible = "brcm,bcm7425-pcie", .data = &bcm7425_cfg },
    { .compatible = "brcm,bcm7712-pcie", .data = &bcm7712_cfg },
    { /* sentinel */ }
};

void brcm_pcie_reapply_maps(struct rt_pci_device *pdev)
{
    struct brcm_pcie *pcie;
    struct rt_pci_host_bridge *host_bridge;

    if (!pdev || !pdev->bus)
    {
        return;
    }

    if (!(host_bridge = rt_pci_find_host_bridge(pdev->bus)))
    {
        return;
    }

    if ((pcie = host_bridge->sysdata))
    {
        brcm_pcie_reapply_7712_maps(pcie);
    }
}

static struct rt_platform_driver brcm_pcie_driver =
{
    .name = "pcie-brcm",
    .ids = brcm_pcie_ofw_ids,

    .probe = brcm_pcie_probe,
    .remove = brcm_pcie_remove,
};
RT_PLATFORM_DRIVER_EXPORT(brcm_pcie_driver);
