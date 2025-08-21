/**************************************************************************//**
 * @file     gic_v3.h
 * @brief    CMSIS Cortex-A53 Generic Interrupt Controller API header file
 * @version  V1.0.1
 * @date     05. october 2021
 ******************************************************************************/
/*
 * Copyright (c) 2021 Arm Limited. All rights reserved.
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if   defined ( __ICCARM__ )
  #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __GIC_V3_H
#define __GIC_V3_H

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************
 *                 GIC Data Types
 ******************************************************************************/

/** \brief  AArch64 System registers to access the Generic Interrupt Controller CPU interface
*/
#if defined(__GNUC__)
  #define ICC_BPR0_EL1           S3_0_C12_C8_3
  #define ICC_BPR1_EL1           S3_0_C12_C12_3
  #define ICC_CTLR_EL1           S3_0_C12_C12_4
  #define ICC_CTLR_EL3           S3_6_C12_C12_4
  #define ICC_EOIR0_EL1          S3_0_C12_C8_1
  #define ICC_EOIR1_EL1          S3_0_C12_C12_1
  #define ICC_HPPIR0_EL1         S3_0_C12_C8_2
  #define ICC_HPPIR1_EL1         S3_0_C12_C12_2
  #define ICC_IAR0_EL1           S3_0_C12_C8_0
  #define ICC_IAR1_EL1           S3_0_C12_C12_0
  #define ICC_IGRPEN0_EL1        S3_0_C12_C12_6
  #define ICC_IGRPEN1_EL1        S3_0_C12_C12_7
  #define ICC_IGRPEN1_EL3        S3_6_C12_C12_7
  #define ICC_PMR_EL1            S3_0_C4_C6_0
  #define ICC_RPR_EL1            S3_0_C12_C11_3
  #define ICC_SGI0R_EL1          S3_0_C12_C11_7
  #define ICC_SGI1R_EL1          S3_0_C12_C11_5
  #define ICC_SRE_EL1            S3_0_C12_C12_5
  #define ICC_SRE_EL2            S3_4_C12_C9_5
  #define ICC_SRE_EL3            S3_6_C12_C12_5
#endif /* __GNUC__ */

/* ICC_SGIR */
#define ICC_SGIR_TARGETLIST_SHIFT	(0)
#define ICC_SGIR_TARGETLIST_MASK	(0xffff)
#define ICC_SGIR_AFF_MASK		(0xff)
#define ICC_SGIR_AFF1_SHIFT		(16)
#define ICC_SGIR_INTID_SHIFT		(24)
#define ICC_SGIR_INTID_MASK		(0xf)
#define ICC_SGIR_AFF2_SHIFT		(32)
#define ICC_SGIR_IRM_SHIFT		(40)
#define ICC_SGIR_IRM_MASK		(0x1)
#define ICC_SGIR_RS_SHIFT		(44)
#define ICC_SGIR_RS_MASK		(0xf)
#define ICC_SGIR_AFF3_SHIFT		(48)

#define MPIDR_TO_RS(mpidr)		(MPIDR_TO_AFF_LEVEL(mpidr, 0) >> 4)

#define COMPOSE_ICC_SGIR_VALUE(aff3, aff2, aff1, intid, irm, rs, tlist)	\
	((((uint64_t)(aff3) & ICC_SGIR_AFF_MASK) << ICC_SGIR_AFF3_SHIFT) |	\
	 (((uint64_t)(rs) & ICC_SGIR_RS_MASK) << ICC_SGIR_RS_SHIFT) |		\
	 (((uint64_t)(irm) & ICC_SGIR_IRM_MASK) << ICC_SGIR_IRM_SHIFT) |	\
	 (((uint64_t)(aff2) & ICC_SGIR_AFF_MASK) << ICC_SGIR_AFF2_SHIFT) |	\
	 (((intid) & ICC_SGIR_INTID_MASK) << ICC_SGIR_INTID_SHIFT) |		\
	 (((aff1) & ICC_SGIR_AFF_MASK) << ICC_SGIR_AFF1_SHIFT) |		\
	 (((tlist) & ICC_SGIR_TARGETLIST_MASK) << ICC_SGIR_TARGETLIST_SHIFT))

#define GIC_REDISTRIBUTOR_STRIDE	(0x20000)
#define GICR_SGI_BASE_OFF		(0x10000)

#define GICR_TYPER_LAST_SHIFT		(4)
#define GICR_TYPER_LAST_MASK		(1 << GICR_TYPER_LAST_SHIFT)
#define GICR_TYPER_AFF_SHIFT		(32)

#define GICR_WAKER_PS_SHIFT		(1)
#define GICR_WAKER_CA_SHIFT		(2)


/** \brief  Structure type to access the Generic Interrupt Controller Distributor (GICD)
*/
typedef struct
{
  __IOM uint32_t CTLR;                 /*!< \brief  Offset: 0x000 (R/W) Distributor Control Register */
  __IM  uint32_t TYPER;                /*!< \brief  Offset: 0x004 (R/ ) Interrupt Controller Type Register */
  __IM  uint32_t IIDR;                 /*!< \brief  Offset: 0x008 (R/ ) Distributor Implementer Identification Register */
        RESERVED(0, uint32_t)
  __IOM uint32_t STATUSR;              /*!< \brief  Offset: 0x010 (R/W) Error Reporting Status Register, optional */
        RESERVED(1[11], uint32_t)
  __OM  uint32_t SETSPI_NSR;           /*!< \brief  Offset: 0x040 ( /W) Set SPI Register */
        RESERVED(2, uint32_t)
  __OM  uint32_t CLRSPI_NSR;           /*!< \brief  Offset: 0x048 ( /W) Clear SPI Register */
        RESERVED(3, uint32_t)
  __OM  uint32_t SETSPI_SR;            /*!< \brief  Offset: 0x050 ( /W) Set SPI, Secure Register */
        RESERVED(4, uint32_t)
  __OM  uint32_t CLRSPI_SR;            /*!< \brief  Offset: 0x058 ( /W) Clear SPI, Secure Register */
        RESERVED(5[9], uint32_t)
  __IOM uint32_t IGROUPR[32];          /*!< \brief  Offset: 0x080 (R/W) Interrupt Group Registers */
  __IOM uint32_t ISENABLER[32];        /*!< \brief  Offset: 0x100 (R/W) Interrupt Set-Enable Registers */
  __IOM uint32_t ICENABLER[32];        /*!< \brief  Offset: 0x180 (R/W) Interrupt Clear-Enable Registers */
  __IOM uint32_t ISPENDR[32];          /*!< \brief  Offset: 0x200 (R/W) Interrupt Set-Pending Registers */
  __IOM uint32_t ICPENDR[32];          /*!< \brief  Offset: 0x280 (R/W) Interrupt Clear-Pending Registers */
  __IOM uint32_t ISACTIVER[32];        /*!< \brief  Offset: 0x300 (R/W) Interrupt Set-Active Registers */
  __IOM uint32_t ICACTIVER[32];        /*!< \brief  Offset: 0x380 (R/W) Interrupt Clear-Active Registers */
  __IOM uint32_t IPRIORITYR[255];      /*!< \brief  Offset: 0x400 (R/W) Interrupt Priority Registers */
        RESERVED(6, uint32_t)
  __IOM uint32_t  ITARGETSR[255];      /*!< \brief  Offset: 0x800 (R/W) Interrupt Targets Registers */
        RESERVED(7, uint32_t)
  __IOM uint32_t ICFGR[64];            /*!< \brief  Offset: 0xC00 (R/W) Interrupt Configuration Registers */
  __IOM uint32_t IGRPMODR[32];         /*!< \brief  Offset: 0xD00 (R/W) Interrupt Group Modifier Registers */
        RESERVED(8[32], uint32_t)
  __IOM uint32_t NSACR[64];            /*!< \brief  Offset: 0xE00 (R/W) Non-secure Access Control Registers */
  __OM  uint32_t SGIR;                 /*!< \brief  Offset: 0xF00 ( /W) Software Generated Interrupt Register */
        RESERVED(9[3], uint32_t)
  __IOM uint32_t CPENDSGIR[4];         /*!< \brief  Offset: 0xF10 (R/W) SGI Clear-Pending Registers */
  __IOM uint32_t SPENDSGIR[4];         /*!< \brief  Offset: 0xF20 (R/W) SGI Set-Pending Registers */
        RESERVED(10[5172], uint32_t)
  __IOM uint64_t IROUTER[988];         /*!< \brief  Offset: 0x6000(R/W) Interrupt Routing Registers */
}  GICDistributor_Type;

#define GICDistributor      ((GICDistributor_Type      *)     GIC_DISTRIBUTOR_BASE ) /*!< \brief GIC Distributor register set access pointer */

/** \brief  Structure type to access the Generic Interrupt Controller Redistributor (GICR)
*/
typedef struct
{
  __IOM uint32_t CTLR;                 /*!< \brief  Offset: 0x000 (R/W) Redistributor Control Register */
  __IM  uint32_t IIDR;                 /*!< \brief  Offset: 0x004 (R/ ) Implementer Identification Register */
  __IM  uint64_t TYPER;                /*!< \brief  Offset: 0x008 (R/ ) Redistributor Type Register */
  __IOM uint32_t STATUSR;              /*!< \brief  Offset: 0x010 (R/W) Error Reporting Status Register, optional */
  __IOM uint32_t WAKER;                /*!< \brief  Offset: 0x014 (R/W) Redistributor Wake Register */
  __IM  uint32_t MPAMIDR;              /*!< \brief  Offset: 0x018 (R/ ) Report maximum PARTID and PMG Register */
  __IOM uint32_t PARTIDR;              /*!< \brief  Offset: 0x01C (R/W) Set PARTID and PMG Register */
        RESERVED(1[8], uint32_t)
  __OM  uint32_t SETLPIR;              /*!< \brief  Offset: 0x040 ( /W) Set LPI Pending Register */
        RESERVED(2, uint32_t)
  __OM  uint32_t CLRLPIR;              /*!< \brief  Offset: 0x048 ( /W) Clear LPI Pending Register */
        RESERVED(3[9], uint32_t)
  __IOM uint32_t PROPBASER;            /*!< \brief  Offset: 0x070 (R/W) Redistributor Properties Base Address Register */
        RESERVED(4, uint32_t)
  __IOM uint32_t PENDBASER;            /*!< \brief  Offset: 0x078 (R/W) Redistributor LPI Pending Table Base Address Register */
        RESERVED(5[9], uint32_t)
  __OM  uint32_t INVLPIR;              /*!< \brief  Offset: 0x0A0 ( /W) Redistributor Invalidate LPI Register */
        RESERVED(6[3], uint32_t)
  __OM  uint32_t INVALLR;              /*!< \brief  Offset: 0x0B0 ( /W) Redistributor Invalidate All Register */
        RESERVED(7[3], uint32_t)
  __IM  uint32_t SYNCR;                /*!< \brief  Offset: 0x0C0 (R/ ) Redistributor Synchronize Register */
}  GICRedistributor_Type;

/* Memory mapped GIC interface may be disabled when ICC_SRE_ELx.SRE set 1 by hypervisor.
   In this case we will be using MSR/MRS system registers.  */
#ifdef GIC_INTERFACE_BASE

/** \brief  Structure type to access the Generic Interrupt Controller Interface (GICC)
*/
typedef struct
{
  __IOM uint32_t CTLR;                 /*!< \brief  Offset: 0x000 (R/W) CPU Interface Control Register */
  __IOM uint32_t PMR;                  /*!< \brief  Offset: 0x004 (R/W) Interrupt Priority Mask Register */
  __IOM uint32_t BPR;                  /*!< \brief  Offset: 0x008 (R/W) Binary Point Register */
  __IM  uint32_t IAR;                  /*!< \brief  Offset: 0x00C (R/ ) Interrupt Acknowledge Register */
  __OM  uint32_t EOIR;                 /*!< \brief  Offset: 0x010 ( /W) End Of Interrupt Register */
  __IM  uint32_t RPR;                  /*!< \brief  Offset: 0x014 (R/ ) Running Priority Register */
  __IM  uint32_t HPPIR;                /*!< \brief  Offset: 0x018 (R/ ) Highest Priority Pending Interrupt Register */
  __IOM uint32_t ABPR;                 /*!< \brief  Offset: 0x01C (R/W) Aliased Binary Point Register */
  __IM  uint32_t AIAR;                 /*!< \brief  Offset: 0x020 (R/ ) Aliased Interrupt Acknowledge Register */
  __OM  uint32_t AEOIR;                /*!< \brief  Offset: 0x024 ( /W) Aliased End Of Interrupt Register */
  __IM  uint32_t AHPPIR;               /*!< \brief  Offset: 0x028 (R/ ) Aliased Highest Priority Pending Interrupt Register */
  __IOM uint32_t STATUSR;              /*!< \brief  Offset: 0x02C (R/W) Error Reporting Status Register, optional */
        RESERVED(1[40], uint32_t)
  __IOM uint32_t APR[4];               /*!< \brief  Offset: 0x0D0 (R/W) Active Priority Register */
  __IOM uint32_t NSAPR[4];             /*!< \brief  Offset: 0x0E0 (R/W) Non-secure Active Priority Register */
        RESERVED(2[3], uint32_t)
  __IM  uint32_t IIDR;                 /*!< \brief  Offset: 0x0FC (R/ ) CPU Interface Identification Register */
        RESERVED(3[960], uint32_t)
  __OM  uint32_t DIR;                  /*!< \brief  Offset: 0x1000( /W) Deactivate Interrupt Register */
}  GICInterface_Type;

#define GICInterface        ((GICInterface_Type        *)     GIC_INTERFACE_BASE )   /*!< \brief GIC Interface register set access pointer */
#endif /* GIC_INTERFACE_BASE */

/* ctrl register access in non-secure */
#define GICD_CTLR_RWP		31
#define GICD_CTLR_ARE_NS	4
#define GICD_CTLR_ENGRP1A	1
#define GICD_CTLR_ENGRP1	0

#define GICR_CTLR_RWP		3

enum gic_rwp {
  GICD_RWP,
  GICR_RWP,
};

/*******************************************************************************
 *                 GIC Functions
 ******************************************************************************/

/* ##########################  GIC functions  ###################################### */

/** \brief Get the recomposed MPIDR_EL1 Affinity fields.
* the recomposed Affinity value format is (aff3:aff2:aff1:aff0)
*/
__STATIC_INLINE uint32_t GIC_MPIDRtoAffinity(void)
{
  uint32_t aff3, aff2, aff1, aff0, aff;
  uint64_t mpidr = __get_MPIDR_EL1();

  aff0 = MPIDR_TO_AFF_LEVEL(mpidr, 0);
  aff1 = MPIDR_TO_AFF_LEVEL(mpidr, 1);
  aff2 = MPIDR_TO_AFF_LEVEL(mpidr, 2);
  aff3 = MPIDR_TO_AFF_LEVEL(mpidr, 3);

  aff = (aff0 & MPIDR_AFFLVL_MASK) << 0  |
        (aff1 & MPIDR_AFFLVL_MASK) << 8  |
        (aff2 & MPIDR_AFFLVL_MASK) << 16 |
        (aff3 & MPIDR_AFFLVL_MASK) << 24;

  return aff;
}

/** \brief Get the Redistributor base.
*/
__STATIC_INLINE GICRedistributor_Type *GIC_GetRdist(void)
{
  uintptr_t rd_addr = GIC_REDISTRIBUTOR_BASE;
  uint32_t rd_aff, aff = GIC_MPIDRtoAffinity();
  uint64_t rd_typer;

  do {
    rd_typer = ((GICRedistributor_Type *)rd_addr)->TYPER;
    rd_aff = rd_typer >> GICR_TYPER_AFF_SHIFT;

    if (rd_aff == aff)
      return (GICRedistributor_Type *)rd_addr;

    rd_addr += GIC_REDISTRIBUTOR_STRIDE;
  } while (!(rd_typer & GICR_TYPER_LAST_MASK));

  return NULL;
}

/** \brief Get the Redistributor SGI_base.
*/
__STATIC_INLINE void *GIC_GetRdistSGIBase(void *rd_base)
{
  return (void *)((uintptr_t)rd_base + GICR_SGI_BASE_OFF);
}

/** \brief Wait for register write pending.
*/
__STATIC_INLINE void GIC_WaitRWP(enum gic_rwp rwp)
{
  uint32_t rwp_mask;
  uint32_t __IM *base;

  if (rwp == GICR_RWP) {
    base = &GIC_GetRdist()->CTLR;
    if (!base)
      return;
    rwp_mask = BIT(GICR_CTLR_RWP);
  } else if (rwp == GICD_RWP) {
    base = &GICDistributor->CTLR;
    rwp_mask = BIT(GICD_CTLR_RWP);
  } else {
    return;
  }

  while (*base & rwp_mask)
    ;
}

/** \brief Get the Affinity Routing status.
*/
__STATIC_INLINE bool GIC_GetARE(void)
{
  return !!(GICDistributor->CTLR & 0x30);
}

/** \brief Disable the interrupt distributor using the GIC's CTLR register.
*/
__STATIC_INLINE void GIC_DisableDistributor(void)
{
  GICDistributor->CTLR &=~1U;
  GIC_WaitRWP(GICD_RWP);
}

/** \brief Read the GIC's TYPER register.
* \return GICDistributor_Type::TYPER
*/
__STATIC_INLINE uint32_t GIC_DistributorInfo(void)
{
  return (GICDistributor->TYPER);
}

/** \brief Reads the GIC's IIDR register.
* \return GICDistributor_Type::IIDR
*/
__STATIC_INLINE uint32_t GIC_DistributorImplementer(void)
{
  return (GICDistributor->IIDR);
}

/** \brief Sets the GIC's ITARGETSR register for the given interrupt.
* \param [in] IRQn Interrupt to be configured.
* \param [in] cpu_target CPU interfaces to assign this interrupt to.
*/
__STATIC_INLINE void GIC_SetTarget(IRQn_Type IRQn, uint64_t cpu_target)
{
  if (IRQn >= 32)
  {
    if (GIC_GetARE())
    {
      /* affinity routing */
      GICDistributor->IROUTER[IRQn] = cpu_target;
    }
    else
    {
      /* legacy */
      uint32_t mask = GICDistributor->ITARGETSR[IRQn / 4U] & ~(0xFFUL << ((IRQn % 4U) * 8U));
      GICDistributor->ITARGETSR[IRQn / 4U] = mask | ((cpu_target & 0xFFUL) << ((IRQn % 4U) * 8U));
    }
  }
}

/** \brief Get the target core of the interrupt.
* \param [in] IRQn Interrupt to acquire the configuration for.
*
* \return:
* For SPI: GICDistributor_Type::ITARGETSR when Affinity Routing isn't enabled,
* or GICDistributor_Type::IROUTER when Affinity Routing is enabled
* For SGI/PPI: The Affinity fields of the MPIDR_EL1.
*/
__STATIC_INLINE uint64_t GIC_GetTarget(IRQn_Type IRQn)
{
  uint64_t cpu_target = 0;

  if (IRQn >= 32)
  {
    if (GIC_GetARE())
    {
      /* affinity routing */
      cpu_target = GICDistributor->IROUTER[IRQn];
    }
    else
    {
      /* legacy */
      cpu_target = (GICDistributor->ITARGETSR[IRQn / 4U] >> ((IRQn % 4U) * 8U)) & 0xFFUL;
    }
  }
  else
  {
      /* local */
      cpu_target = __get_MPIDR_EL1() & MPIDR_AFFINITY_MASK;
  }

  return cpu_target;
}

/** \brief Enables the given interrupt using GIC's ISENABLER register.
* \param [in] IRQn The interrupt to be enabled.
*/
__STATIC_INLINE void GIC_EnableIRQ(IRQn_Type IRQn)
{
  uint64_t mpidr = __get_MPIDR_EL1();
  GICDistributor_Type *s_RedistPPIBaseAddrs;

  GIC_SetTarget(IRQn, mpidr & MPIDR_AFFINITY_MASK);

  if (IRQn < 32) {
    s_RedistPPIBaseAddrs = GIC_GetRdistSGIBase(GIC_GetRdist());
    s_RedistPPIBaseAddrs->ISENABLER[0] = 1U << IRQn;
  } else {
    GICDistributor->ISENABLER[IRQn / 32U] = 1U << (IRQn % 32U);
  }
}

/** \brief Get interrupt enable status using GIC's ISENABLER register.
* \param [in] IRQn The interrupt to be queried.
* \return 0 - interrupt is not enabled, 1 - interrupt is enabled.
*/
__STATIC_INLINE uint32_t GIC_GetEnableIRQ(IRQn_Type IRQn)
{
  return (GICDistributor->ISENABLER[IRQn / 32U] >> (IRQn % 32U)) & 1UL;
}

/** \brief Disables the given interrupt using GIC's ICENABLER register.
* \param [in] IRQn The interrupt to be disabled.
*/
__STATIC_INLINE void GIC_DisableIRQ(IRQn_Type IRQn)
{
  GICDistributor_Type *s_RedistPPIBaseAddrs;

  if (IRQn < 32) {
    s_RedistPPIBaseAddrs = GIC_GetRdistSGIBase(GIC_GetRdist());
    s_RedistPPIBaseAddrs->ICENABLER[0] = 1U << IRQn;
    GIC_WaitRWP(GICR_RWP);
  } else {
    GICDistributor->ICENABLER[IRQn / 32U] = 1U << (IRQn % 32U);
    GIC_WaitRWP(GICD_RWP);
  }
}

/** \brief Get interrupt pending status from GIC's ISPENDR register.
* \param [in] IRQn The interrupt to be queried.
* \return 0 - interrupt is not pending, 1 - interrupt is pendig.
*/
__STATIC_INLINE uint32_t GIC_GetPendingIRQ(IRQn_Type IRQn)
{
  uint32_t pend;

  if (IRQn >= 16) {
    pend = (GICDistributor->ISPENDR[IRQn / 32U] >> (IRQn % 32U)) & 1UL;
  } else {
    // INTID 0-15 Software Generated Interrupt
    pend = (GICDistributor->SPENDSGIR[IRQn / 4U] >> ((IRQn % 4U) * 8U)) & 0xFFUL;
    // No CPU identification offered
    if (pend != 0U) {
      pend = 1U;
    } else {
      pend = 0U;
    }
  }

  return (pend);
}

/** \brief Sets the given interrupt as pending using GIC's ISPENDR register.
* \param [in] IRQn The interrupt to be enabled.
*/
__STATIC_INLINE void GIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if (IRQn >= 16) {
    GICDistributor->ISPENDR[IRQn / 32U] = 1U << (IRQn % 32U);
  } else {
    // INTID 0-15 Software Generated Interrupt
    GICDistributor->SPENDSGIR[IRQn / 4U] = 1U << ((IRQn % 4U) * 8U);
    // Forward the interrupt to the CPU interface that requested it
    GICDistributor->SGIR = (IRQn | 0x02000000U);
  }
}

/** \brief Clears the given interrupt from being pending using GIC's ICPENDR register.
* \param [in] IRQn The interrupt to be enabled.
*/
__STATIC_INLINE void GIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if (IRQn >= 16) {
    GICDistributor->ICPENDR[IRQn / 32U] = 1U << (IRQn % 32U);
  } else {
    // INTID 0-15 Software Generated Interrupt
    GICDistributor->CPENDSGIR[IRQn / 4U] = 1U << ((IRQn % 4U) * 8U);
  }
}

/** \brief Sets the interrupt configuration using GIC's ICFGR register.
* \param [in] IRQn The interrupt to be configured.
* \param [in] int_config Int_config field value. Bit 0: Reserved (0 - N-N model, 1 - 1-N model for some GIC before v1)
*                                           Bit 1: 0 - level sensitive, 1 - edge triggered
*/
__STATIC_INLINE void GIC_SetConfiguration(IRQn_Type IRQn, uint32_t int_config)
{
  uint32_t icfgr = GICDistributor->ICFGR[IRQn / 16U];
  uint32_t shift = (IRQn % 16U) << 1U;

  icfgr &= (~(3U         << shift));
  icfgr |= (  int_config << shift);

  GICDistributor->ICFGR[IRQn / 16U] = icfgr;
}

/** \brief Get the interrupt configuration from the GIC's ICFGR register.
* \param [in] IRQn Interrupt to acquire the configuration for.
* \return Int_config field value. Bit 0: Reserved (0 - N-N model, 1 - 1-N model for some GIC before v1)
*                                 Bit 1: 0 - level sensitive, 1 - edge triggered
*/
__STATIC_INLINE uint32_t GIC_GetConfiguration(IRQn_Type IRQn)
{
  return (GICDistributor->ICFGR[IRQn / 16U] >> ((IRQn % 16U) >> 1U));
}

__STATIC_INLINE void GIC_SetRedistPriority(IRQn_Type IRQn, uint32_t priority)
{
  GICDistributor_Type *s_RedistPPIBaseAddrs = GIC_GetRdistSGIBase(GIC_GetRdist());
  uint32_t mask = s_RedistPPIBaseAddrs->IPRIORITYR[IRQn / 4U] & ~(0xFFUL << ((IRQn % 4U) * 8U));

  s_RedistPPIBaseAddrs->IPRIORITYR[IRQn / 4U] = mask | ((priority & 0xFFUL) << ((IRQn % 4U) * 8U));
}

/** \brief Set the priority for the given interrupt.
* \param [in] IRQn The interrupt to be configured.
* \param [in] priority The priority for the interrupt, lower values denote higher priorities.
*/
__STATIC_INLINE void GIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  uint32_t mask;

  if ((IRQn < 32) && (GIC_GetARE())) {
    GIC_SetRedistPriority(IRQn, priority);
  } else {
    mask = GICDistributor->IPRIORITYR[IRQn / 4U] & ~(0xFFUL << ((IRQn % 4U) * 8U));
    GICDistributor->IPRIORITYR[IRQn / 4U] = mask | ((priority & 0xFFUL) << ((IRQn % 4U) * 8U));
  }
}

__STATIC_INLINE void GIC_RedistWakeUp(void)
{
  GICRedistributor_Type *const s_RedistBaseAddrs = GIC_GetRdist();

  if (!s_RedistBaseAddrs)
    return;

  if (!(s_RedistBaseAddrs->WAKER & (1 << GICR_WAKER_CA_SHIFT)))
    return;

  s_RedistBaseAddrs->WAKER &= ~ (1 << GICR_WAKER_PS_SHIFT);
  while (s_RedistBaseAddrs->WAKER & (1 << GICR_WAKER_CA_SHIFT))
    ;
}

__STATIC_INLINE uint32_t GIC_GetRedistPriority(IRQn_Type IRQn)
{
  GICDistributor_Type *s_RedistPPIBaseAddrs;

  s_RedistPPIBaseAddrs = GIC_GetRdistSGIBase(GIC_GetRdist());
  return (s_RedistPPIBaseAddrs->IPRIORITYR[IRQn / 4U] >> ((IRQn % 4U) * 8U)) & 0xFFUL;
}

/** \brief Read the current interrupt priority from GIC's IPRIORITYR register.
* \param [in] IRQn The interrupt to be queried.
*/
__STATIC_INLINE uint32_t GIC_GetPriority(IRQn_Type IRQn)
{
  if ((IRQn < 32) && (GIC_GetARE())) {
    return GIC_GetRedistPriority(IRQn);
  } else {
    return (GICDistributor->IPRIORITYR[IRQn / 4U] >> ((IRQn % 4U) * 8U)) & 0xFFUL;
  }
}

/** \brief Get the status for a given interrupt.
* \param [in] IRQn The interrupt to get status for.
* \return 0 - not pending/active, 1 - pending, 2 - active, 3 - pending and active
*/
__STATIC_INLINE uint32_t GIC_GetIRQStatus(IRQn_Type IRQn)
{
  uint32_t pending, active;

  active = ((GICDistributor->ISACTIVER[IRQn / 32U])  >> (IRQn % 32U)) & 1UL;
  pending = ((GICDistributor->ISPENDR[IRQn / 32U]) >> (IRQn % 32U)) & 1UL;

  return ((active<<1U) | pending);
}

/** \brief Generate a software interrupt (Affinity Routing version).
* \param [in] IRQn Software interrupt to be generated.
* \param [in] target_aff Target affinity in MPIDR form.
* \param [in] tlist List of CPUs the software interrupt should be forwarded to.
*/
__STATIC_INLINE void GIC_SendSGI_ARE(IRQn_Type IRQn, uint64_t target_aff, uint16_t tlist)
{
  uint32_t aff3, aff2, aff1, rs;
  uint64_t val;

  if (IRQn >= 16)
    return;

  aff1 = MPIDR_TO_AFF_LEVEL(target_aff, 1);
  aff2 = MPIDR_TO_AFF_LEVEL(target_aff, 2);
  aff3 = MPIDR_TO_AFF_LEVEL(target_aff, 3);
  rs = MPIDR_TO_RS(target_aff);
  val = COMPOSE_ICC_SGIR_VALUE(aff3, aff2, aff1, IRQn, 0, rs, tlist);

  __DSB();
  __MSR(ICC_SGI1R_EL1, val);
  __ISB();
}

/** \brief Generate a software interrupt.
* \param [in] IRQn Software interrupt to be generated.
* \param [in] target_aff Target affinity in MPIDR form.
* \param [in] target_list List of CPUs the software interrupt should be forwarded to.
*/
__STATIC_INLINE void GIC_SendSGI(IRQn_Type IRQn, uint64_t target_aff, uint16_t target_list)
{
  if (IRQn >= 16)
    return;

  if (GIC_GetARE()) {
    /* affinity routing */
    GIC_SendSGI_ARE(IRQn, target_aff, target_list);
  } else {
    GICDistributor->SGIR = ((target_list & 0xFFUL) << 16U) | (IRQn & 0x0FUL);
  }
}

/** \brief Set the interrupt group from the GIC's IGROUPR register.
* \param [in] IRQn The interrupt to be queried.
* \param [in] group Interrupt group number: 0 - Group 0, 1 - Group 1
*/
__STATIC_INLINE void GIC_SetGroup(IRQn_Type IRQn, uint32_t group)
{
  uint32_t igroupr = GICDistributor->IGROUPR[IRQn / 32U];
  uint32_t shift   = (IRQn % 32U);

  igroupr &= (~(1U          << shift));
  igroupr |= ( (group & 1U) << shift);

  GICDistributor->IGROUPR[IRQn / 32U] = igroupr;
}
#define GIC_SetSecurity         GIC_SetGroup

__STATIC_INLINE void GIC_SetRedistGroup(IRQn_Type IRQn, uint32_t group)
{
  GICDistributor_Type *s_RedistPPIBaseAddrs;
  uint32_t shift   = (IRQn % 32U);
  uint32_t igroupr;

  s_RedistPPIBaseAddrs = GIC_GetRdistSGIBase(GIC_GetRdist());
  igroupr = s_RedistPPIBaseAddrs->IGROUPR[IRQn / 32U];

  igroupr &= (~(1U          << shift));
  igroupr |= ( (group & 1U) << shift);

  s_RedistPPIBaseAddrs->IGROUPR[IRQn / 32U] = igroupr;
}
#define GIC_SetSecurity         GIC_SetGroup

/** \brief Get the interrupt group from the GIC's IGROUPR register.
* \param [in] IRQn The interrupt to be queried.
* \return 0 - Group 0, 1 - Group 1
*/
__STATIC_INLINE uint32_t GIC_GetGroup(IRQn_Type IRQn)
{
  return (GICDistributor->IGROUPR[IRQn / 32U] >> (IRQn % 32U)) & 1UL;
}
#define GIC_GetSecurity         GIC_GetGroup

/** \brief Initialize the interrupt distributor.
*/
__STATIC_INLINE void GIC_DistInit(void)
{
  uint32_t i;
  uint32_t num_irq = 0U;
  uint32_t priority_field;
  uint32_t ppi_priority;

  //A reset sets all bits in the IGROUPRs corresponding to the SPIs to 0,
  //configuring all of the interrupts as Secure.

  //Disable interrupt forwarding
  GIC_DisableDistributor();
  //Get the maximum number of interrupts that the GIC supports
  num_irq = 32U * ((GIC_DistributorInfo() & 0x1FU) + 1U);

  /* Priority level is implementation defined.
   To determine the number of priority bits implemented write 0xFF to an IPRIORITYR
   priority field and read back the value stored.
   Use PPI, as it is always accessible, even for a Guest OS using a hypervisor.
   Then restore the initial state.*/
  ppi_priority = GIC_GetPriority((IRQn_Type)31U);
  GIC_SetPriority((IRQn_Type)31U, 0xFFU);
  priority_field = GIC_GetPriority((IRQn_Type)31U);
  GIC_SetPriority((IRQn_Type)31U, ppi_priority);

  for (i = 32U; i < num_irq; i++)
  {
      /* Use non secure group1 for all SPI */
      GIC_SetGroup(i, 1);
      //Disable the SPI interrupt
      GIC_DisableIRQ((IRQn_Type)i);
      //Set level-sensitive (and N-N model)
      GIC_SetConfiguration((IRQn_Type)i, 0U);
      //Set priority
      GIC_SetPriority((IRQn_Type)i, priority_field*2U/3U);
  }

  /* Enable distributor with ARE_NS and NS_Group1 */
  GICDistributor->CTLR = ((1U << GICD_CTLR_ARE_NS) | (1U <<  GICD_CTLR_ENGRP1A));
  GIC_WaitRWP(GICD_RWP);
}

/** \brief Initialize the interrupt redistributor.
*/
__STATIC_INLINE void GIC_RedistInit(void)
{
  uint32_t i;
  uint32_t priority_field;

  /* Priority level is implementation defined.
   To determine the number of priority bits implemented write 0xFF to an IPRIORITYR
   priority field and read back the value stored.*/
  GIC_SetRedistPriority((IRQn_Type)31U, 0xFFU);
  priority_field = GIC_GetRedistPriority((IRQn_Type)31U);

  /* Wakeup the GIC */
  GIC_RedistWakeUp();

  for (i = 0; i < 32; i++)
  {
      //Disable the SPI interrupt
      GIC_DisableIRQ((IRQn_Type)i);
      //Set priority
      GIC_SetRedistPriority((IRQn_Type)i, priority_field*2U/3U);
  }
}

#ifdef GICInterface

/** \brief Enable the CPU's interrupt interface.
*/
__STATIC_INLINE void GIC_EnableInterface(void)
{
  GICInterface->CTLR |= 1U; //enable interface
}

/** \brief Disable the CPU's interrupt interface.
*/
__STATIC_INLINE void GIC_DisableInterface(void)
{
  GICInterface->CTLR &=~1U; //disable distributor
}

/** \brief Read the CPU's IAR register.
* \return GICInterface_Type::IAR
*/
__STATIC_INLINE IRQn_Type GIC_AcknowledgePending(void)
{
  return (IRQn_Type)(GICInterface->IAR);
}

/** \brief Writes the given interrupt number to the CPU's EOIR register.
* \param [in] IRQn The interrupt to be signaled as finished.
*/
__STATIC_INLINE void GIC_EndInterrupt(IRQn_Type IRQn)
{
  GICInterface->EOIR = IRQn;
}


/** \brief Set the interrupt priority mask using CPU's PMR register.
* \param [in] priority Priority mask to be set.
*/
__STATIC_INLINE void GIC_SetInterfacePriorityMask(uint32_t priority)
{
  GICInterface->PMR = priority & 0xFFUL; //set priority mask
}

/** \brief Read the current interrupt priority mask from CPU's PMR register.
* \result GICInterface_Type::PMR
*/
__STATIC_INLINE uint32_t GIC_GetInterfacePriorityMask(void)
{
  return GICInterface->PMR;
}

/** \brief Configures the group priority and subpriority split point using CPU's BPR register.
* \param [in] binary_point Amount of bits used as subpriority.
*/
__STATIC_INLINE void GIC_SetBinaryPoint(uint32_t binary_point)
{
  GICInterface->BPR = binary_point & 7U; //set binary point
}

/** \brief Read the current group priority and subpriority split point from CPU's BPR register.
* \return GICInterface_Type::BPR
*/
__STATIC_INLINE uint32_t GIC_GetBinaryPoint(void)
{
  return GICInterface->BPR;
}

/** \brief Get the interrupt number of the highest interrupt pending from CPU's HPPIR register.
* \return GICInterface_Type::HPPIR
*/
__STATIC_INLINE uint32_t GIC_GetHighPendingIRQ(void)
{
  return GICInterface->HPPIR;
}

/** \brief Provides information about the implementer and revision of the CPU interface.
* \return GICInterface_Type::IIDR
*/
__STATIC_INLINE uint32_t GIC_GetInterfaceId(void)
{
  return GICInterface->IIDR;
}

#else /* GICInterface */

/** \brief Enable the CPU's interrupt interface.
*/
__STATIC_INLINE void GIC_EnableInterface(void)
{
  __MSR(ICC_IGRPEN1_EL1, 1);
}

/** \brief Disable the CPU's interrupt interface.
*/
__STATIC_INLINE void GIC_DisableInterface(void)
{
  __MSR(ICC_IGRPEN1_EL1, 0);
}

/** \brief Read the CPU's IAR register.
* \return GICInterface_Type::IAR
*/
__STATIC_INLINE IRQn_Type GIC_AcknowledgePending(void)
{
  uint32_t result;
  __MRS(ICC_IAR1_EL1, &result);
  return (IRQn_Type)(result);
}

/** \brief Writes the given interrupt number to the CPU's EOIR register.
* \param [in] IRQn The interrupt to be signaled as finished.
*/
__STATIC_INLINE void GIC_EndInterrupt(IRQn_Type IRQn)
{
  __MSR(ICC_EOIR1_EL1, (uint32_t)IRQn);
}

/** \brief Set the interrupt priority mask using CPU's PMR register.
* \param [in] priority Priority mask to be set.
*/
__STATIC_INLINE void GIC_SetInterfacePriorityMask(uint32_t priority)
{
  __MSR(ICC_PMR_EL1, priority & 0xFFUL);
}

/** \brief Read the current interrupt priority mask from CPU's PMR register.
* \result GICInterface_Type::PMR
*/
__STATIC_INLINE uint32_t GIC_GetInterfacePriorityMask(void)
{
  uint32_t result;
  __MRS(ICC_PMR_EL1, &result);
  return result;
}

/** \brief Configures the group priority and subpriority split point using CPU's BPR register.
* \param [in] binary_point Amount of bits used as subpriority.
*/
__STATIC_INLINE void GIC_SetBinaryPoint(uint32_t binary_point)
{
  __MSR(ICC_BPR1_EL1, binary_point & 7U);
}

/** \brief Read the current group priority and subpriority split point from CPU's BPR register.
* \return GICInterface_Type::BPR
*/
__STATIC_INLINE uint32_t GIC_GetBinaryPoint(void)
{
  uint32_t result;
  __MRS(ICC_BPR1_EL1, &result);
  return result;
}

/** \brief Get the interrupt number of the highest interrupt pending from CPU's HPPIR register.
* \return GICInterface_Type::HPPIR
*/
__STATIC_INLINE uint32_t GIC_GetHighPendingIRQ(void)
{
  uint32_t result;
  __MRS(ICC_HPPIR1_EL1, &result);
  return result;
}

#endif

__STATIC_INLINE void GIC_CPUInterfaceInit(void)
{
  uint32_t i;
  uint32_t priority_field;

  //A reset sets all bits in the IGROUPRs corresponding to the SPIs to 0,
  //configuring all of the interrupts as Secure.

  //Disable interrupt forwarding
  GIC_DisableInterface();

  /* Priority level is implementation defined.
   To determine the number of priority bits implemented write 0xFF to an IPRIORITYR
   priority field and read back the value stored.*/
  GIC_SetPriority((IRQn_Type)0U, 0xFFU);
  priority_field = GIC_GetPriority((IRQn_Type)0U);

  //SGI and PPI
  for (i = 0U; i < 32U; i++)
  {
    if (i > 15U) {
      //Set level-sensitive (and N-N model) for PPI
      GIC_SetConfiguration((IRQn_Type)i, 0U);
    }
    //Disable SGI and PPI interrupts
    GIC_DisableIRQ((IRQn_Type)i);
    //Set priority
    GIC_SetPriority((IRQn_Type)i, priority_field*2U/3U);
  }

  //Set binary point to 0
  GIC_SetBinaryPoint(0U);
  //Set priority mask
  GIC_SetInterfacePriorityMask(0xFFU);
  //Enable interface
  GIC_EnableInterface();
}

/** \brief Initialize and enable the GIC
*/
__STATIC_INLINE void GIC_Enable(int init_dist)
{
  /* Only one core should be responsible for the GIC distributor setup */
  if (init_dist)
    GIC_DistInit();

  GIC_RedistInit();
  GIC_CPUInterfaceInit(); //per CPU
}

#ifdef __cplusplus
}
#endif

#endif /* __GIC_V3_H */
