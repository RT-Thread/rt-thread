/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __PCIE_ROCKCHIP_H__
#define __PCIE_ROCKCHIP_H__

#include <rtthread.h>
#include <rtdevice.h>

#include "ecam.h"
#include "rockchip.h"

/*
 * The upper 16 bits of PCIE_CLIENT_CONFIG are a write mask for the lower 16
 * bits. This allows atomic updates of the register without locking.
 */
#define PCI_HIWORD_UPDATE(mask, val)                        (((mask) << 16) | (val))
#define PCI_HIWORD_UPDATE_BIT(val)                          PCI_HIWORD_UPDATE(val, val)
#define PCI_HIWORD_DISABLE_BIT(val)                         PCI_HIWORD_UPDATE(val, ~val)

#define ENCODE_LANES(x)                                     ((((x) >> 1) & 3) << 4)
#define MAX_LANE_NUM                                        4
#define MAX_REGION_LIMIT                                    32
#define MIN_EP_APERTURE                                     28

#define PCIE_CLIENT_BASE                                    0x0
#define PCIE_CLIENT_CONFIG                                  (PCIE_CLIENT_BASE + 0x00)
#define   PCIE_CLIENT_CONF_ENABLE                           PCI_HIWORD_UPDATE_BIT(0x0001)
#define   PCIE_CLIENT_CONF_DISABLE                          PCI_HIWORD_UPDATE(0x0001, 0)
#define   PCIE_CLIENT_LINK_TRAIN_ENABLE                     PCI_HIWORD_UPDATE_BIT(0x0002)
#define   PCIE_CLIENT_LINK_TRAIN_DISABLE                    PCI_HIWORD_UPDATE(0x0002, 0x0000)
#define   PCIE_CLIENT_ARI_ENABLE                            PCI_HIWORD_UPDATE_BIT(0x0008)
#define   PCIE_CLIENT_CONF_LANE_NUM(x)                      PCI_HIWORD_UPDATE(0x0030, ENCODE_LANES(x))
#define   PCIE_CLIENT_MODE_RC                               PCI_HIWORD_UPDATE_BIT(0x0040)
#define   PCIE_CLIENT_MODE_EP                               PCI_HIWORD_UPDATE(0x0040, 0)
#define   PCIE_CLIENT_GEN_SEL_1                             PCI_HIWORD_UPDATE(0x0080, 0)
#define   PCIE_CLIENT_GEN_SEL_2                             PCI_HIWORD_UPDATE_BIT(0x0080)
#define PCIE_CLIENT_LEGACY_INT_CTRL                         (PCIE_CLIENT_BASE + 0x0c)
#define   PCIE_CLIENT_INT_IN_ASSERT                         PCI_HIWORD_UPDATE_BIT(0x0002)
#define   PCIE_CLIENT_INT_IN_DEASSERT                       PCI_HIWORD_UPDATE(0x0002, 0)
#define   PCIE_CLIENT_INT_PEND_ST_PEND                      PCI_HIWORD_UPDATE_BIT(0x0001)
#define   PCIE_CLIENT_INT_PEND_ST_NORMAL                    PCI_HIWORD_UPDATE(0x0001, 0)
#define PCIE_CLIENT_SIDE_BAND_STATUS                        (PCIE_CLIENT_BASE + 0x20)
#define   PCIE_CLIENT_PHY_ST                                RT_BIT(12)
#define PCIE_CLIENT_DEBUG_OUT_0                             (PCIE_CLIENT_BASE + 0x3c)
#define   PCIE_CLIENT_DEBUG_LTSSM_MASK                      RT_GENMASK(5, 0)
#define   PCIE_CLIENT_DEBUG_LTSSM_L0                        0x10
#define   PCIE_CLIENT_DEBUG_LTSSM_L1                        0x18
#define   PCIE_CLIENT_DEBUG_LTSSM_L2                        0x19
#define PCIE_CLIENT_BASIC_STATUS1                           (PCIE_CLIENT_BASE + 0x48)
#define   PCIE_CLIENT_LINK_STATUS_UP                        0x00300000
#define   PCIE_CLIENT_LINK_STATUS_MASK                      0x00300000
#define PCIE_CLIENT_INT_MASK                                (PCIE_CLIENT_BASE + 0x4c)
#define PCIE_CLIENT_INT_STATUS                              (PCIE_CLIENT_BASE + 0x50)
#define   PCIE_CLIENT_INTR_MASK                             RT_GENMASK(8, 5)
#define   PCIE_CLIENT_INTR_SHIFT                            5
#define   PCIE_CLIENT_INT_LEGACY_DONE                       RT_BIT(15)
#define   PCIE_CLIENT_INT_MSG                               RT_BIT(14)
#define   PCIE_CLIENT_INT_HOT_RST                           RT_BIT(13)
#define   PCIE_CLIENT_INT_DPA                               RT_BIT(12)
#define   PCIE_CLIENT_INT_FATAL_ERR                         RT_BIT(11)
#define   PCIE_CLIENT_INT_NFATAL_ERR                        RT_BIT(10)
#define   PCIE_CLIENT_INT_CORR_ERR                          RT_BIT(9)
#define   PCIE_CLIENT_INT_INTD                              RT_BIT(8)
#define   PCIE_CLIENT_INT_INTC                              RT_BIT(7)
#define   PCIE_CLIENT_INT_INTB                              RT_BIT(6)
#define   PCIE_CLIENT_INT_INTA                              RT_BIT(5)
#define   PCIE_CLIENT_INT_LOCAL                             RT_BIT(4)
#define   PCIE_CLIENT_INT_UDMA                              RT_BIT(3)
#define   PCIE_CLIENT_INT_PHY                               RT_BIT(2)
#define   PCIE_CLIENT_INT_HOT_PLUG                          RT_BIT(1)
#define   PCIE_CLIENT_INT_PWR_STCG                          RT_BIT(0)

#define PCIE_CLIENT_INT_LEGACY \
        (PCIE_CLIENT_INT_INTA | PCIE_CLIENT_INT_INTB | \
        PCIE_CLIENT_INT_INTC | PCIE_CLIENT_INT_INTD)

#define PCIE_CLIENT_INT_CLI \
        (PCIE_CLIENT_INT_CORR_ERR | PCIE_CLIENT_INT_NFATAL_ERR | \
        PCIE_CLIENT_INT_FATAL_ERR | PCIE_CLIENT_INT_DPA | \
        PCIE_CLIENT_INT_HOT_RST | PCIE_CLIENT_INT_MSG | \
        PCIE_CLIENT_INT_LEGACY_DONE | PCIE_CLIENT_INT_LEGACY | \
        PCIE_CLIENT_INT_PHY | PCIE_CLIENT_INT_UDMA)

#define PCIE_APB_CORE_UDMA_BASE                             (RT_BIT(23) | RT_BIT(22) | RT_BIT(21))
#define PCIE_CH0_DONE_ENABLE                                RT_BIT(0)
#define PCIE_CH1_DONE_ENABLE                                RT_BIT(1)
#define PCIE_CH0_ERR_ENABLE                                 RT_BIT(8)
#define PCIE_CH1_ERR_ENABLE                                 RT_BIT(9)

#define PCIE_UDMA_INT_REG                                   0xa0
#define PCIE_UDMA_INT_ENABLE_REG                            0xa4

#define PCIE_UDMA_INT_ENABLE_MASK \
        (PCIE_CH0_DONE_ENABLE | PCIE_CH1_DONE_ENABLE | \
        PCIE_CH0_ERR_ENABLE | PCIE_CH1_ERR_ENABLE)

#define PCIE_CORE_CTRL_MGMT_BASE                            0x900000
#define PCIE_CORE_CTRL                                      (PCIE_CORE_CTRL_MGMT_BASE + 0x000)
#define   PCIE_CORE_PL_CONF_SPEED_5G                        0x00000008
#define   PCIE_CORE_PL_CONF_SPEED_MASK                      0x00000018
#define   PCIE_CORE_PL_CONF_LANE_MASK                       0x00000006
#define   PCIE_CORE_PL_CONF_LANE_SHIFT                      1
#define PCIE_CORE_CTRL_PLC1                                 (PCIE_CORE_CTRL_MGMT_BASE + 0x004)
#define   PCIE_CORE_CTRL_PLC1_FTS_MASK                      RT_GENMASK(23, 8)
#define   PCIE_CORE_CTRL_PLC1_FTS_SHIFT                     8
#define   PCIE_CORE_CTRL_PLC1_FTS_CNT                       0xffff
#define PCIE_CORE_TXCREDIT_CFG1                             (PCIE_CORE_CTRL_MGMT_BASE + 0x020)
#define   PCIE_CORE_TXCREDIT_CFG1_MUI_MASK                  0xFFFF0000
#define   PCIE_CORE_TXCREDIT_CFG1_MUI_SHIFT                 16
#define   PCIE_CORE_TXCREDIT_CFG1_MUI_ENCODE(x)             (((x) >> 3) << PCIE_CORE_TXCREDIT_CFG1_MUI_SHIFT)
#define PCIE_CORE_LANE_MAP                                  (PCIE_CORE_CTRL_MGMT_BASE + 0x200)
#define   PCIE_CORE_LANE_MAP_MASK                           0x0000000f
#define   PCIE_CORE_LANE_MAP_REVERSE                        RT_BIT(16)
#define PCIE_CORE_INT_STATUS                                (PCIE_CORE_CTRL_MGMT_BASE + 0x20c)
#define   PCIE_CORE_INT_PRFPE                               RT_BIT(0)
#define   PCIE_CORE_INT_CRFPE                               RT_BIT(1)
#define   PCIE_CORE_INT_RRPE                                RT_BIT(2)
#define   PCIE_CORE_INT_PRFO                                RT_BIT(3)
#define   PCIE_CORE_INT_CRFO                                RT_BIT(4)
#define   PCIE_CORE_INT_RT                                  RT_BIT(5)
#define   PCIE_CORE_INT_RTR                                 RT_BIT(6)
#define   PCIE_CORE_INT_PE                                  RT_BIT(7)
#define   PCIE_CORE_INT_MTR                                 RT_BIT(8)
#define   PCIE_CORE_INT_UCR                                 RT_BIT(9)
#define   PCIE_CORE_INT_FCE                                 RT_BIT(10)
#define   PCIE_CORE_INT_CT                                  RT_BIT(11)
#define   PCIE_CORE_INT_UTC                                 RT_BIT(18)
#define   PCIE_CORE_INT_MMVC                                RT_BIT(19)
#define PCIE_CORE_CONFIG_VENDOR                             (PCIE_CORE_CTRL_MGMT_BASE + 0x44)
#define PCIE_CORE_INT_MASK                                  (PCIE_CORE_CTRL_MGMT_BASE + 0x210)
#define PCIE_CORE_PHY_FUNC_CFG                              (PCIE_CORE_CTRL_MGMT_BASE + 0x2c0)
#define PCIE_RC_BAR_CONF                                    (PCIE_CORE_CTRL_MGMT_BASE + 0x300)
#define RK_PCIE_CORE_BAR_CFG_CTRL_DISABLED                  0x0
#define RK_PCIE_CORE_BAR_CFG_CTRL_IO_32BITS                 0x1
#define RK_PCIE_CORE_BAR_CFG_CTRL_MEM_32BITS                0x4
#define RK_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_32BITS       0x5
#define RK_PCIE_CORE_BAR_CFG_CTRL_MEM_64BITS                0x6
#define RK_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_64BITS       0x7

#define PCIE_CORE_INT \
        (PCIE_CORE_INT_PRFPE | PCIE_CORE_INT_CRFPE | \
         PCIE_CORE_INT_RRPE | PCIE_CORE_INT_CRFO | \
         PCIE_CORE_INT_RT | PCIE_CORE_INT_RTR | \
         PCIE_CORE_INT_PE | PCIE_CORE_INT_MTR | \
         PCIE_CORE_INT_UCR | PCIE_CORE_INT_FCE | \
         PCIE_CORE_INT_CT | PCIE_CORE_INT_UTC | \
         PCIE_CORE_INT_MMVC)

#define PCIE_RC_RP_ATS_BASE                                 0x400000
#define PCIE_RC_CONFIG_NORMAL_BASE                          0x800000
#define PCIE_RC_CONFIG_BASE                                 0xa00000
#define PCIE_EP_CONFIG_BASE                                 0xa00000
#define PCIE_EP_CONFIG_DID_VID                              (PCIE_EP_CONFIG_BASE + 0x00)
#define PCIE_RC_CONFIG_RID_CCR                              (PCIE_RC_CONFIG_BASE + 0x08)
#define   PCIE_RC_CONFIG_SCC_SHIFT                          16
#define PCIE_RC_CONFIG_DCR                                  (PCIE_RC_CONFIG_BASE + 0xc4)
#define   PCIE_RC_CONFIG_DCR_CSPL_SHIFT                     18
#define   PCIE_RC_CONFIG_DCR_CSPL_LIMIT                     0xff
#define   PCIE_RC_CONFIG_DCR_CPLS_SHIFT                     26
#define PCIE_RC_CONFIG_DCSR                                 (PCIE_RC_CONFIG_BASE + 0xc8)
#define   PCIE_RC_CONFIG_DCSR_MPS_MASK                      RT_GENMASK(7, 5)
#define   PCIE_RC_CONFIG_DCSR_MPS_256                       (0x1 << 5)
#define PCIE_RC_CONFIG_LINK_CAP                             (PCIE_RC_CONFIG_BASE + 0xcc)
#define   PCIE_RC_CONFIG_LINK_CAP_L0S                       RT_BIT(10)
#define PCIE_RC_CONFIG_LCS                                  (PCIE_RC_CONFIG_BASE + 0xd0)
#define PCIE_RC_CONFIG_L1_SUBSTATE_CTRL2                    (PCIE_RC_CONFIG_BASE + 0x90c)
#define PCIE_RC_CONFIG_THP_CAP                              (PCIE_RC_CONFIG_BASE + 0x274)
#define   PCIE_RC_CONFIG_THP_CAP_NEXT_MASK                  RT_GENMASK(31, 20)

#define PCIE_CORE_AXI_CONF_BASE                             0xc00000
#define PCIE_CORE_OB_REGION_ADDR0                           (PCIE_CORE_AXI_CONF_BASE + 0x0)
#define   PCIE_CORE_OB_REGION_ADDR0_NUM_BITS                0x3f
#define   PCIE_CORE_OB_REGION_ADDR0_LO_ADDR                 0xffffff00
#define PCIE_CORE_OB_REGION_ADDR1                           (PCIE_CORE_AXI_CONF_BASE + 0x4)
#define PCIE_CORE_OB_REGION_DESC0                           (PCIE_CORE_AXI_CONF_BASE + 0x8)
#define PCIE_CORE_OB_REGION_DESC1                           (PCIE_CORE_AXI_CONF_BASE + 0xc)

#define PCIE_CORE_AXI_INBOUND_BASE                          0xc00800
#define PCIE_RP_IB_ADDR0                                    (PCIE_CORE_AXI_INBOUND_BASE + 0x0)
#define   PCIE_CORE_IB_REGION_ADDR0_NUM_BITS                0x3f
#define   PCIE_CORE_IB_REGION_ADDR0_LO_ADDR                 0xffffff00
#define PCIE_RP_IB_ADDR1                                    (PCIE_CORE_AXI_INBOUND_BASE + 0x4)

/* Size of one AXI Region (not Region 0) */
#define AXI_REGION_SIZE                                     RT_BIT(20)
/* Size of Region 0, equal to sum of sizes of other regions */
#define AXI_REGION_0_SIZE                                   (32 * (0x1 << 20))
#define OB_REG_SIZE_SHIFT                                   5
#define IB_ROOT_PORT_REG_SIZE_SHIFT                         3
#define AXI_WRAPPER_IO_WRITE                                0x6
#define AXI_WRAPPER_MEM_WRITE                               0x2
#define AXI_WRAPPER_TYPE0_CFG                               0xa
#define AXI_WRAPPER_TYPE1_CFG                               0xb
#define AXI_WRAPPER_NOR_MSG                                 0xc

#define MAX_AXI_IB_ROOTPORT_REGION_NUM                      3
#define MIN_AXI_ADDR_BITS_PASSED                            8
#define PCIE_RC_SEND_PME_OFF                                0x11960
#define RK_VENDOR_ID                                        0x1d87
#undef  PCIE_ECAM_BUS
#undef  PCIE_ECAM_REG
#define PCIE_ECAM_BUS(x)                                    (((x) & 0xff) << 20)
#define PCIE_ECAM_DEV(x)                                    (((x) & 0x1f) << 15)
#define PCIE_ECAM_FUNC(x)                                   (((x) & 0x7) << 12)
#define PCIE_ECAM_REG(x)                                    (((x) & 0xfff) << 0)
#define PCIE_ECAM_ADDR(bus, dev, func, reg) \
        (PCIE_ECAM_BUS(bus) | PCIE_ECAM_DEV(dev) | PCIE_ECAM_FUNC(func) | PCIE_ECAM_REG(reg))
#define PCIE_LINK_IS_L0(x) \
        (((x) & PCIE_CLIENT_DEBUG_LTSSM_MASK) == PCIE_CLIENT_DEBUG_LTSSM_L0)
#define PCIE_LINK_IS_L2(x) \
        (((x) & PCIE_CLIENT_DEBUG_LTSSM_MASK) == PCIE_CLIENT_DEBUG_LTSSM_L2)
#define PCIE_LINK_UP(x) \
        (((x) & PCIE_CLIENT_LINK_STATUS_MASK) == PCIE_CLIENT_LINK_STATUS_UP)
#define PCIE_LINK_IS_GEN2(x) \
        (((x) & PCIE_CORE_PL_CONF_SPEED_MASK) == PCIE_CORE_PL_CONF_SPEED_5G)

#define RC_REGION_0_ADDR_TRANS_H                            0x00000000
#define RC_REGION_0_ADDR_TRANS_L                            0x00000000
#define RC_REGION_0_PASS_BITS                               (25 - 1)
#define RC_REGION_0_TYPE_MASK                               RT_GENMASK(3, 0)
#define MAX_AXI_WRAPPER_REGION_NUM                          33

#define RK_PCIE_MSG_ROUTING_TO_RC                           0x0
#define RK_PCIE_MSG_ROUTING_VIA_ADDR                        0x1
#define RK_PCIE_MSG_ROUTING_VIA_ID                          0x2
#define RK_PCIE_MSG_ROUTING_BROADCAST                       0x3
#define RK_PCIE_MSG_ROUTING_LOCAL_INTX                      0x4
#define RK_PCIE_MSG_ROUTING_PME_ACK                         0x5
#define RK_PCIE_MSG_CODE_ASSERT_INTA                        0x20
#define RK_PCIE_MSG_CODE_ASSERT_INTB                        0x21
#define RK_PCIE_MSG_CODE_ASSERT_INTC                        0x22
#define RK_PCIE_MSG_CODE_ASSERT_INTD                        0x23
#define RK_PCIE_MSG_CODE_DEASSERT_INTA                      0x24
#define RK_PCIE_MSG_CODE_DEASSERT_INTB                      0x25
#define RK_PCIE_MSG_CODE_DEASSERT_INTC                      0x26
#define RK_PCIE_MSG_CODE_DEASSERT_INTD                      0x27
#define RK_PCIE_MSG_ROUTING_MASK                            RT_GENMASK(7, 5)
#define RK_PCIE_MSG_ROUTING(route)                          (((route) << 5) & RK_PCIE_MSG_ROUTING_MASK)
#define RK_PCIE_MSG_CODE_MASK                               RT_GENMASK(15, 8)
#define RK_PCIE_MSG_CODE(code)                              (((code) << 8) & RK_PCIE_MSG_CODE_MASK)
#define RK_PCIE_MSG_NO_DATA                                 RT_BIT(16)

#define RK_PCIE_EP_CMD_STATUS                               0x4
#define   RK_PCIE_EP_CMD_STATUS_IS                          RT_BIT(19)
#define RK_PCIE_EP_MSI_CTRL_REG                             0x90
#define   RK_PCIE_EP_MSI_FLAGS_OFFSET                       16
#define   RK_PCIE_EP_MSI_CTRL_MMC_OFFSET                    17
#define   RK_PCIE_EP_MSI_CTRL_MMC_MASK                      RT_GENMASK(19, 17)
#define   RK_PCIE_EP_MSI_CTRL_MME_OFFSET                    20
#define   RK_PCIE_EP_MSI_CTRL_MME_MASK                      RT_GENMASK(22, 20)
#define   RK_PCIE_EP_MSI_CTRL_ME                            RT_BIT(16)
#define   RK_PCIE_EP_MSI_CTRL_MASK_MSI_CAP                  RT_BIT(24)
#define RK_PCIE_EP_DUMMY_IRQ_ADDR                           0x1
#define RK_PCIE_EP_FUNC_BASE(fn)                            (((fn) << 12) & RT_GENMASK(19, 12))
#define RK_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar)            (PCIE_RC_RP_ATS_BASE + 0x0840 + (fn) * 0x0040 + (bar) * 0x0008)
#define RK_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar)            (PCIE_RC_RP_ATS_BASE + 0x0844 + (fn) * 0x0040 + (bar) * 0x0008)
#define RK_PCIE_AT_OB_REGION_PCI_ADDR0(r)                   (PCIE_RC_RP_ATS_BASE + 0x0000 + ((r) & 0x1f) * 0x0020)
#define RK_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK           RT_GENMASK(19, 12)
#define RK_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN(devfn)         (((devfn) << 12) & RK_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK)
#define RK_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK             RT_GENMASK(27, 20)
#define RK_PCIE_AT_OB_REGION_PCI_ADDR0_BUS(bus)             (((bus) << 20) & RK_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK)
#define RK_PCIE_AT_OB_REGION_PCI_ADDR1(r)                   (PCIE_RC_RP_ATS_BASE + 0x0004 + ((r) & 0x1f) * 0x0020)
#define RK_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID            RT_BIT(23)
#define RK_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK               RT_GENMASK(31, 24)
#define RK_PCIE_AT_OB_REGION_DESC0_DEVFN(devfn)             (((devfn) << 24) & RK_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK)
#define RK_PCIE_AT_OB_REGION_DESC0(r)                       (PCIE_RC_RP_ATS_BASE + 0x0008 + ((r) & 0x1f) * 0x0020)
#define RK_PCIE_AT_OB_REGION_DESC1(r)                       (PCIE_RC_RP_ATS_BASE + 0x000c + ((r) & 0x1f) * 0x0020)
#define RK_PCIE_AT_OB_REGION_CPU_ADDR0(r)                   (PCIE_RC_RP_ATS_BASE + 0x0018 + ((r) & 0x1f) * 0x0020)
#define RK_PCIE_AT_OB_REGION_CPU_ADDR1(r)                   (PCIE_RC_RP_ATS_BASE + 0x001c + ((r) & 0x1f) * 0x0020)

#define RK_PCIE_CORE_EP_FUNC_BAR_CFG0(fn)                   (PCIE_CORE_CTRL_MGMT_BASE + 0x0240 + (fn) * 0x0008)
#define RK_PCIE_CORE_EP_FUNC_BAR_CFG1(fn)                   (PCIE_CORE_CTRL_MGMT_BASE + 0x0244 + (fn) * 0x0008)
#define RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b)   (RT_GENMASK(4, 0) << ((b) * 8))
#define RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE(b, a)     (((a) << ((b) * 8)) & RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b))
#define RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b)       (RT_GENMASK(7, 5) << ((b) * 8))
#define RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL(b, c)         (((c) << ((b) * 8 + 5)) & RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b))

#define PCIE_USER_RELINK 0x1
#define PCIE_USER_UNLINK 0x2

struct rockchip_pcie
{
    void *axi_base;
    void *apb_base;

    rt_bool_t legacy_phy;
    struct rt_phye *phys[MAX_LANE_NUM];

    struct rt_reset_control *core_rstc;
    struct rt_reset_control *mgmt_rstc;
    struct rt_reset_control *mgmt_sticky_rstc;
    struct rt_reset_control *pipe_rstc;
    struct rt_reset_control *pm_rstc;
    struct rt_reset_control *aclk_rstc;
    struct rt_reset_control *pclk_rstc;

    struct rt_clk *aclk_pcie;
    struct rt_clk *aclk_perf_pcie;
    struct rt_clk *hclk_pcie;
    struct rt_clk *clk_pcie_pm;

    struct rt_regulator *vpcie12v;
    struct rt_regulator *vpcie3v3;
    struct rt_regulator *vpcie1v8;
    struct rt_regulator *vpcie0v9;

    rt_ubase_t ep_pin;
    rt_uint8_t active_val;

    rt_uint32_t num_lanes;
    rt_uint8_t lanes_map;
    rt_uint32_t link_gen;

    int sys_irq;
    int legacy_irq;
    int client_irq;
    struct rt_device *dev;
    struct rt_ofw_node *intx_np;
    struct rt_pic intx_pic;

    int offset;
    void *msg_region;
    rt_ubase_t msg_bus_addr;

    rt_uint64_t mem_base_addr;
    rt_uint64_t mem_base_size;

    rt_bool_t is_rc;
    rt_bool_t wait_ep;
    rt_bool_t in_remove;

    struct rt_pci_host_bridge *bridge;
};

rt_inline rt_uint32_t rockchip_pcie_read(struct rockchip_pcie *rk_pcie,
        rt_uint32_t reg)
{
    return HWREG32(rk_pcie->apb_base + reg);
}

rt_inline void rockchip_pcie_write(struct rockchip_pcie *rk_pcie,
        rt_uint32_t val, rt_uint32_t reg)
{
    HWREG32(rk_pcie->apb_base + reg) = val;
}

rt_err_t rockchip_pcie_ofw_parse(struct rockchip_pcie *rk_pcie);
rt_err_t rockchip_pcie_init_port(struct rockchip_pcie *rk_pcie);
rt_err_t rockchip_pcie_get_phys(struct rockchip_pcie *rk_pcie);
void rockchip_pcie_deinit_phys(struct rockchip_pcie *rk_pcie);
rt_err_t rockchip_pcie_enable_clocks(struct rockchip_pcie *rk_pcie);
void rockchip_pcie_disable_clocks(struct rockchip_pcie *rk_pcie);
void rockchip_pcie_common_free(struct rockchip_pcie *rk_pcie);
void rockchip_pcie_cfg_configuration_accesses(struct rockchip_pcie *rk_pcie, rt_uint32_t type);

#endif /* __PCIE_ROCKCHIP_H__ */
