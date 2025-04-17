/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 * 2014-04-03     Grissiom     many enhancements
 * 2018-11-22     Jesven       add rt_hw_ipi_send()
 *                             add rt_hw_ipi_handler_install()
 * 2023-02-01     GuEe-GUI     move macros to header
 */

#ifndef __PIC_GICV3_H__
#define __PIC_GICV3_H__

#include <rtdef.h>

#include <cpuport.h>

#include <drivers/pic.h>
#include <drivers/core/dm.h>
#include <dt-bindings/size.h>

/* Distributor registers */
#define GICD_CTLR               0x0000
#define GICD_TYPER              0x0004
#define GICD_IIDR               0x0008
#define GICD_TYPER2             0x000C
#define GICD_STATUSR            0x0010
#define GICD_SETSPI_NSR         0x0040
#define GICD_CLRSPI_NSR         0x0048
#define GICD_SETSPI_SR          0x0050
#define GICD_CLRSPI_SR          0x0058
#define GICD_IGROUPR            0x0080
#define GICD_ISENABLER          0x0100
#define GICD_ICENABLER          0x0180
#define GICD_ISPENDR            0x0200
#define GICD_ICPENDR            0x0280
#define GICD_ISACTIVER          0x0300
#define GICD_ICACTIVER          0x0380
#define GICD_IPRIORITYR         0x0400
#define GICD_ICFGR              0x0C00
#define GICD_IGRPMODR           0x0D00
#define GICD_NSACR              0x0E00
#define GICD_IGROUPRnE          0x1000
#define GICD_ISENABLERnE        0x1200
#define GICD_ICENABLERnE        0x1400
#define GICD_ISPENDRnE          0x1600
#define GICD_ICPENDRnE          0x1800
#define GICD_ISACTIVERnE        0x1A00
#define GICD_ICACTIVERnE        0x1C00
#define GICD_IPRIORITYRnE       0x2000
#define GICD_ICFGRnE            0x3000
#define GICD_IROUTER            0x6000
#define GICD_IROUTERnE          0x8000
#define GICD_IDREGS             0xFFD0
#define GICD_PIDR2              0xFFE8

#define GICD_ITARGETSR          0x0800
#define GICD_SGIR               0x0F00
#define GICD_CPENDSGIR          0x0F10
#define GICD_SPENDSGIR          0x0F20

#define GICD_CTLR_RWP           (1U << 31)
#define GICD_CTLR_nASSGIreq     (1U << 8)
#define GICD_CTLR_DS            (1U << 6)
#define GICD_CTLR_ARE_NS        (1U << 4)
#define GICD_CTLR_ENABLE_G1A    (1U << 1)
#define GICD_CTLR_ENABLE_G1     (1U << 0)

#define GICD_TYPER_RSS          (1U << 26)
#define GICD_TYPER_LPIS         (1U << 17)
#define GICD_TYPER_MBIS         (1U << 16)
#define GICD_TYPER_ESPI         (1U << 8)
#define GICD_TYPER_ID_BITS(t)   ((((t) >> 19) & 0x1f) + 1)
#define GICD_TYPER_NUM_LPIS(t)  ((((t) >> 11) & 0x1f) + 1)
#define GICD_TYPER_SPIS(t)      ((((t) & 0x1f) + 1) * 32)
#define GICD_TYPER_ESPIS(t)     (((t) & GICD_TYPER_ESPI) ? GICD_TYPER_SPIS((t) >> 27) : 0)

/* Redistributor registers */
#define GICR_CTLR               0x0000
#define GICR_IIDR               0x0004
#define GICR_TYPER              0x0008
#define GICR_STATUSR            0x0010
#define GICR_WAKER              0x0014
#define GICR_MPAMIDR            0x0018
#define GICR_PARTIDR            0x001C
#define GICR_SETLPIR            0x0040
#define GICR_CLRLPIR            0x0048
#define GICR_PROPBASER          0x0070
#define GICR_PENDBASER          0x0078
#define GICR_INVLPIR            0x00A0
#define GICR_INVALLR            0x00B0
#define GICR_SYNCR              0x00C0
#define GICR_PIDR2              GICD_PIDR2

#define GICR_CTLR_ENABLE_LPIS   (1UL << 0)
#define GICR_CTLR_CES           (1UL << 1)
#define GICR_CTLR_IR            (1UL << 2)
#define GICR_CTLR_RWP           (1UL << 3)

#define GICR_TYPER_CPU_NO(r)    (((r) >> 8) & 0xffff)

#define GICR_RD_BASE_SIZE       (64 * SIZE_KB)
#define GICR_SGI_OFFSET         (64 * SIZE_KB)
#define GICR_SGI_BASE_SIZE      GICR_SGI_OFFSET

/* Re-Distributor registers, offsets from SGI_base */
#define GICR_IGROUPR0           GICD_IGROUPR
#define GICR_ISENABLER0         GICD_ISENABLER
#define GICR_ICENABLER0         GICD_ICENABLER
#define GICR_ISPENDR0           GICD_ISPENDR
#define GICR_ICPENDR0           GICD_ICPENDR
#define GICR_ISACTIVER0         GICD_ISACTIVER
#define GICR_ICACTIVER0         GICD_ICACTIVER
#define GICR_IPRIORITYR0        GICD_IPRIORITYR
#define GICR_ICFGR0             GICD_ICFGR
#define GICR_IGRPMODR0          GICD_IGRPMODR
#define GICR_NSACR              GICD_NSACR

#define GICR_TYPER_PLPIS        (1U << 0)
#define GICR_TYPER_VLPIS        (1U << 1)
#define GICR_TYPER_DIRTY        (1U << 2)
#define GICR_TYPER_DirectLPIS   (1U << 3)
#define GICR_TYPER_LAST         (1U << 4)
#define GICR_TYPER_RVPEID       (1U << 7)
#define GICR_TYPER_COM_LPI_AFF  RT_GENMASK_ULL(25, 24)
#define GICR_TYPER_AFFINITY     RT_GENMASK_ULL(63, 32)

#define GICR_INVLPIR_INTID      RT_GENMASK_ULL(31, 0)
#define GICR_INVLPIR_VPEID      RT_GENMASK_ULL(47, 32)
#define GICR_INVLPIR_V          RT_GENMASK_ULL(63, 63)

#define GICR_INVALLR_VPEID      GICR_INVLPIR_VPEID
#define GICR_INVALLR_V          GICR_INVLPIR_V

#define GICR_VLPI_BASE_SIZE     (64 * SIZE_KB)
#define GICR_RESERVED_SIZE      (64 * SIZE_KB)

#define GIC_V3_REDIST_SIZE      0x20000

#define GICR_TYPER_NR_PPIS(t)   (16 + ({ int __ppinum = (((t) >> 27) & 0x1f); __ppinum <= 2 ? __ppinum : 0; }) * 32)

#define GICR_WAKER_ProcessorSleep   (1U << 1)
#define GICR_WAKER_ChildrenAsleep   (1U << 2)

#define GICR_PROPBASER_IDBITS_MASK  (0x1f)
#define GICR_PROPBASER_ADDRESS(x)   ((x) & RT_GENMASK_ULL(51, 12))
#define GICR_PENDBASER_ADDRESS(x)   ((x) & RT_GENMASK_ULL(51, 16))

/* ITS registers */
#define GITS_CTLR               0x0000
#define GITS_IIDR               0x0004
#define GITS_TYPER              0x0008
#define GITS_MPIDR              0x0018
#define GITS_CBASER             0x0080
#define GITS_CWRITER            0x0088
#define GITS_CREADR             0x0090
#define GITS_BASER              0x0100
#define GITS_IDREGS_BASE        0xffd0
#define GITS_PIDR0              0xffe0
#define GITS_PIDR1              0xffe4
#define GITS_PIDR2              GICR_PIDR2
#define GITS_PIDR4              0xffd0
#define GITS_CIDR0              0xfff0
#define GITS_CIDR1              0xfff4
#define GITS_CIDR2              0xfff8
#define GITS_CIDR3              0xfffc

#define GITS_TRANSLATER         0x10040

#define GITS_SGIR               0x20020

#define GITS_SGIR_VPEID                         RT_GENMASK_ULL(47, 32)
#define GITS_SGIR_VINTID                        RT_GENMASK_ULL(3, 0)

#define GITS_CTLR_ENABLE                        (1U << 0)
#define GITS_CTLR_ImDe                          (1U << 1)
#define GITS_CTLR_ITS_NUMBER_SHIFT              4
#define GITS_CTLR_ITS_NUMBER                    (0xFU << GITS_CTLR_ITS_NUMBER_SHIFT)
#define GITS_CTLR_QUIESCENT                     (1U << 31)

#define GITS_TYPER_PLPIS                        (1UL << 0)
#define GITS_TYPER_VLPIS                        (1UL << 1)
#define GITS_TYPER_ITT_ENTRY_SIZE_SHIFT         4
#define GITS_TYPER_ITT_ENTRY_SIZE               RT_GENMASK_ULL(7, 4)
#define GITS_TYPER_IDBITS_SHIFT                 8
#define GITS_TYPER_DEVBITS_SHIFT                13
#define GITS_TYPER_DEVBITS                      RT_GENMASK_ULL(17, 13)
#define GITS_TYPER_PTA                          (1UL << 19)
#define GITS_TYPER_HCC_SHIFT                    24
#define GITS_TYPER_HCC(r)                       (((r) >> GITS_TYPER_HCC_SHIFT) & 0xff)
#define GITS_TYPER_VMOVP                        (1ULL << 37)
#define GITS_TYPER_VMAPP                        (1ULL << 40)
#define GITS_TYPER_SVPET                        RT_GENMASK_ULL(42, 41)

/*
 * ITS commands
 */
#define GITS_CMD_MAPD                           0x08
#define GITS_CMD_MAPC                           0x09
#define GITS_CMD_MAPTI                          0x0a
#define GITS_CMD_MAPI                           0x0b
#define GITS_CMD_MOVI                           0x01
#define GITS_CMD_DISCARD                        0x0f
#define GITS_CMD_INV                            0x0c
#define GITS_CMD_MOVALL                         0x0e
#define GITS_CMD_INVALL                         0x0d
#define GITS_CMD_INT                            0x03
#define GITS_CMD_CLEAR                          0x04
#define GITS_CMD_SYNC                           0x05

/* ITS Config Area */
#define GITS_LPI_CFG_GROUP1                     (1 << 1)
#define GITS_LPI_CFG_ENABLED                    (1 << 0)

/* ITS Command Queue Descriptor */
#define GITS_BASER_SHAREABILITY_SHIFT           10
#define GITS_BASER_INNER_CACHEABILITY_SHIFT     59
#define GITS_BASER_OUTER_CACHEABILITY_SHIFT     53
#define GITS_CBASER_VALID                       (1UL << 63)
#define GITS_CBASER_SHAREABILITY_SHIFT          10
#define GITS_CBASER_INNER_CACHEABILITY_SHIFT    59
#define GITS_CBASER_OUTER_CACHEABILITY_SHIFT    53
#define GICR_PBASER_SHAREABILITY_SHIFT          10
#define GICR_PBASER_INNER_CACHEABILITY_SHIFT    7
#define GICR_PBASER_OUTER_CACHEABILITY_SHIFT    56

#define GITS_BASER_NR_REGS                      8
#define GITS_BASERn(idx)                        (GITS_BASER + sizeof(rt_uint64_t) * idx)

#define GITS_BASER_VALID                        (1ULL << 63)
#define GITS_BASER_INDIRECT                     (1ULL << 62)
#define GITS_BASER_TYPE_SHIFT                   56
#define GITS_BASER_TYPE(r)                      (((r) >> GITS_BASER_TYPE_SHIFT) & 7)
#define GITS_BASER_ENTRY_SIZE_SHIFT             48
#define GITS_BASER_ENTRY_SIZE(r)                ((((r) >> GITS_BASER_ENTRY_SIZE_SHIFT) & 0x1f) + 1)
#define GITS_BASER_PAGE_SIZE_SHIFT              8
#define GITS_BASER_PAGE_SIZE_4K                 (0ULL << GITS_BASER_PAGE_SIZE_SHIFT)
#define GITS_BASER_PAGE_SIZE_16K                (1ULL << GITS_BASER_PAGE_SIZE_SHIFT)
#define GITS_BASER_PAGE_SIZE_64K                (2ULL << GITS_BASER_PAGE_SIZE_SHIFT)
#define GITS_BASER_PAGE_SIZE_MASK               (3ULL << GITS_BASER_PAGE_SIZE_SHIFT)
#define GITS_BASER_PAGES_SHIFT                  0

#define GITS_LVL1_ENTRY_SIZE                    8UL

#define GITS_BASER_TYPE_NONE                    0
#define GITS_BASER_TYPE_DEVICE                  1
#define GITS_BASER_TYPE_VPE                     2
#define GITS_BASER_TYPE_RESERVED3               3
#define GITS_BASER_TYPE_COLLECTION              4
#define GITS_BASER_TYPE_RESERVED5               5
#define GITS_BASER_TYPE_RESERVED6               6
#define GITS_BASER_TYPE_RESERVED7               7

#define GITS_BASER_CACHEABILITY(reg, inner_outer, type) \
    (GIC_BASER_CACHE_##type << reg##_##inner_outer##_CACHEABILITY_SHIFT)
#define GITS_BASER_SHAREABILITY(reg, type)              \
    (GIC_BASER_##type << reg##_SHAREABILITY_SHIFT)

#define GIC_BASER_CACHE_DnGnRnE     0x0UL /* Device-nGnRnE. */
#define GIC_BASER_CACHE_NIN         0x1UL /* Normal Inner Non-cacheable. */
#define GIC_BASER_CACHE_NIRAWT      0x2UL /* Normal Inner Cacheable Read-allocate, Write-through. */
#define GIC_BASER_CACHE_NIRAWB      0x3UL /* Normal Inner Cacheable Read-allocate, Write-back. */
#define GIC_BASER_CACHE_NIWAWT      0x4UL /* Normal Inner Cacheable Write-allocate, Write-through. */
#define GIC_BASER_CACHE_NIWAWB      0x5UL /* Normal Inner Cacheable Write-allocate, Write-back. */
#define GIC_BASER_CACHE_NIRAWAWT    0x6UL /* Normal Inner Cacheable Read-allocate, Write-allocate, Write-through. */
#define GIC_BASER_CACHE_NIRAWAWB    0x7UL /* Normal Inner Cacheable Read-allocate, Write-allocate, Write-back. */
#define GIC_BASER_CACHE_MASK        0x7UL
#define GIC_BASER_SHARE_NS          0x0UL /* Non-shareable. */
#define GIC_BASER_SHARE_IS          0x1UL /* Inner Shareable. */
#define GIC_BASER_SHARE_OS          0x2UL /* Outer Shareable. */
#define GIC_BASER_SHARE_RES         0x3UL /* Reserved. Treated as 0b00 */
#define GIC_BASER_SHARE_MASK        0x3UL

#define GITS_BASER_InnerShareable   GITS_BASER_SHAREABILITY(GITS_BASER, SHARE_IS)
#define GITS_BASER_SHARE_MASK_ALL   GITS_BASER_SHAREABILITY(GITS_BASER, SHARE_MASK)
#define GITS_BASER_INNER_MASK_ALL   GITS_BASER_CACHEABILITY(GITS_BASER, INNER, MASK)
#define GITS_BASER_nCnB             GITS_BASER_CACHEABILITY(GITS_BASER, INNER, DnGnRnE)
#define GITS_BASER_nC               GITS_BASER_CACHEABILITY(GITS_BASER, INNER, NIN)
#define GITS_BASER_RaWt             GITS_BASER_CACHEABILITY(GITS_BASER, INNER, NIRAWT)
#define GITS_BASER_RaWb             GITS_BASER_CACHEABILITY(GITS_BASER, INNER, NIRAWB)
#define GITS_BASER_WaWt             GITS_BASER_CACHEABILITY(GITS_BASER, INNER, NIWAWT)
#define GITS_BASER_WaWb             GITS_BASER_CACHEABILITY(GITS_BASER, INNER, NIWAWB)
#define GITS_BASER_RaWaWt           GITS_BASER_CACHEABILITY(GITS_BASER, INNER, NIRAWAWT)
#define GITS_BASER_RaWaWb           GITS_BASER_CACHEABILITY(GITS_BASER, INNER, NIRAWAWB)

#define GITS_CBASER_InnerShareable  GITS_BASER_SHAREABILITY(GITS_CBASER, SHARE_IS)
#define GITS_CBASER_SHARE_MASK_ALL  GITS_BASER_SHAREABILITY(GITS_CBASER, SHARE_MASK)
#define GITS_CBASER_INNER_MASK_ALL  GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, MASK)
#define GITS_CBASER_nCnB            GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, DnGnRnE)
#define GITS_CBASER_nC              GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, NIN)
#define GITS_CBASER_RaWt            GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, NIRAWT)
#define GITS_CBASER_RaWb            GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, NIRAWB)
#define GITS_CBASER_WaWt            GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, NIWAWT)
#define GITS_CBASER_WaWb            GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, NIWAWB)
#define GITS_CBASER_RaWaWt          GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, NIRAWAWT)
#define GITS_CBASER_RaWaWb          GITS_BASER_CACHEABILITY(GITS_CBASER, INNER, NIRAWAWB)

#define GICR_PBASER_InnerShareable  GITS_BASER_SHAREABILITY(GICR_PBASER, SHARE_IS)
#define GICR_PBASER_SHARE_MASK_ALL  GITS_BASER_SHAREABILITY(GICR_PBASER, SHARE_MASK)
#define GICR_PBASER_INNER_MASK_ALL  GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, MASK)
#define GICR_PBASER_nCnB            GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, DnGnRnE)
#define GICR_PBASER_nC              GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, NIN)
#define GICR_PBASER_RaWt            GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, NIRAWT)
#define GICR_PBASER_RaWb            GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, NIRAWB)
#define GICR_PBASER_WaWt            GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, NIWAWT)
#define GICR_PBASER_WaWb            GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, NIWAWB)
#define GICR_PBASER_RaWaWt          GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, NIRAWAWT)
#define GICR_PBASER_RaWaWb          GITS_BASER_CACHEABILITY(GICR_PBASER, INNER, NIRAWAWB)

#define GIC_EPPI_BASE_INTID         1056
#define GIC_ESPI_BASE_INTID         4096

#define GIC_IRQ_TYPE_LPI            0xa110c8ed
#define GIC_IRQ_TYPE_PARTITION      (GIC_IRQ_TYPE_LPI + 1)

#define read_gicreg(reg, out)           rt_hw_sysreg_read(reg, out)
#define write_gicreg(reg, in)           rt_hw_sysreg_write(reg, in)

#define ICC_CTLR_EOImode                0x2
#define ICC_PMR_MASK                    0xff
#define ICC_PMR_DEFAULT                 0xf0
#define ICC_IGRPEN1_EN                  0x1

#define ICC_SGIR_AFF3_SHIFT             48
#define ICC_SGIR_AFF2_SHIFT             32
#define ICC_SGIR_AFF1_SHIFT             16
#define ICC_SGIR_TARGET_MASK            0xffff
#define ICC_SGIR_IRQN_SHIFT             24
#define ICC_SGIR_ROUTING_BIT            (1ULL << 40)

#define ICC_SGI1R_TARGET_LIST_SHIFT     0
#define ICC_SGI1R_TARGET_LIST_MASK      (0xffff << ICC_SGI1R_TARGET_LIST_SHIFT)
#define ICC_SGI1R_TARGET_LIST_MAX       16
#define ICC_SGI1R_AFFINITY_1_SHIFT      16
#define ICC_SGI1R_AFFINITY_1_MASK       (0xff << ICC_SGI1R_AFFINITY_1_SHIFT)
#define ICC_SGI1R_SGI_ID_SHIFT          24
#define ICC_SGI1R_SGI_ID_MASK           (0xfULL << ICC_SGI1R_SGI_ID_SHIFT)
#define ICC_SGI1R_AFFINITY_2_SHIFT      32
#define ICC_SGI1R_AFFINITY_2_MASK       (0xffULL << ICC_SGI1R_AFFINITY_2_SHIFT)
#define ICC_SGI1R_IRQ_ROUTING_MODE_BIT  40
#define ICC_SGI1R_RS_SHIFT              44
#define ICC_SGI1R_RS_MASK               (0xfULL << ICC_SGI1R_RS_SHIFT)
#define ICC_SGI1R_AFFINITY_3_SHIFT      48
#define ICC_SGI1R_AFFINITY_3_MASK       (0xffULL << ICC_SGI1R_AFFINITY_3_SHIFT)

#define ICC_CTLR_EL1_CBPR_SHIFT         0
#define ICC_CTLR_EL1_CBPR_MASK          (1 << ICC_CTLR_EL1_CBPR_SHIFT)
#define ICC_CTLR_EL1_EOImode_SHIFT      (1)
#define ICC_CTLR_EL1_EOImode_drop       (1U << ICC_CTLR_EL1_EOImode_SHIFT)
#define ICC_CTLR_EL1_EOImode_drop_dir   (0U << ICC_CTLR_EL1_EOImode_SHIFT)
#define ICC_CTLR_EL1_PRI_BITS_SHIFT     (8)
#define ICC_CTLR_EL1_PRI_BITS_MASK      (0x7 << ICC_CTLR_EL1_PRI_BITS_SHIFT)
#define ICC_CTLR_EL1_RSS                (0x1 << 18)
#define ICC_CTLR_EL1_ExtRange           (0x1 << 19)

struct gicv3
{
    struct rt_pic parent;

    int version;
    int irq_nr;
    rt_uint32_t gicd_typer;
    rt_size_t line_nr;
    rt_size_t espi_nr;
    rt_size_t lpi_nr;
    rt_ubase_t flags;

    void *dist_base;
    rt_size_t dist_size;

    void *redist_percpu_base[RT_CPUS_NR];
    rt_uint64_t redist_percpu_flags[RT_CPUS_NR];
    rt_size_t percpu_ppi_nr[RT_CPUS_NR];

    struct
    {
        void *base;
        void *base_phy;
        rt_size_t size;
    } *redist_regions;
    rt_uint64_t redist_flags;
    rt_size_t redist_stride;
    rt_size_t redist_regions_nr;
};

#endif /* __PIC_GICV3_H__ */
