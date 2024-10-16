/*
** ###################################################################
**     Processor:           S32K344
**     Reference manual:    S32K3xx RM Rev.3
**     Version:             rev. 1.9, 2021-10-27
**     Build:               b211026
**
**     Abstract:
**         Peripheral Access Layer for S32K344
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K344_LCU.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_LCU
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/

/* Prevention from multiple including the same memory map */
#if !defined(S32K344_LCU_H_)  /* Check if memory map has not been already included */
#define S32K344_LCU_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- LCU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCU_Peripheral_Access_Layer LCU Peripheral Access Layer
 * @{
 */

/** LCU - Size of Registers Arrays */
#define LCU_LC_LUTCTRL_COUNT                      4u
#define LCU_LC_FILT_COUNT                         4u
#define LCU_LC_COUNT                              3u
#define LCU_SEL_COUNT                             12u

/** LCU - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x40 */
    __IO uint32_t LUTCTRL[LCU_LC_LUTCTRL_COUNT];     /**< LC 0 Output 0 LUT Control..LC 2 Output 3 LUT Control, array offset: 0x0, array step: index*0x40, index2*0x4 */
    __IO uint32_t FILT[LCU_LC_FILT_COUNT];           /**< LC 0 Output 0 Filter..LC 2 Output 3 Filter, array offset: 0x10, array step: index*0x40, index2*0x4 */
    __IO uint32_t INTDMAEN;                          /**< LC 0 Interrupt and DMA Enable..LC 2 Interrupt and DMA Enable, array offset: 0x20, array step: 0x40 */
    __IO uint32_t STS;                               /**< LC 0 Status..LC 2 Status, array offset: 0x24, array step: 0x40 */
    __IO uint32_t OUTPOL;                            /**< LC 0 Output Polarity Control..LC 2 Output Polarity Control, array offset: 0x28, array step: 0x40 */
    __IO uint32_t FFILT;                             /**< LC 0 Force Filter..LC 2 Force Filter, array offset: 0x2C, array step: 0x40 */
    __IO uint32_t FCTRL;                             /**< LC 0 Force Control..LC 2 Force Control, array offset: 0x30, array step: 0x40 */
    __IO uint32_t SCTRL;                             /**< LC 0 Sync Control..LC 2 Sync Control, array offset: 0x34, array step: 0x40 */
    uint8_t RESERVED_0[8];
  } LC[LCU_LC_COUNT];
  uint8_t RESERVED_0[320];
  __IO uint32_t MUXSEL[LCU_SEL_COUNT];             /**< Mux Select, array offset: 0x200, array step: 0x4 */
  uint8_t RESERVED_1[80];
  __IO uint32_t CFG;                               /**< Configuration, offset: 0x280 */
  __IO uint32_t SWEN;                              /**< Software Override Enable, offset: 0x284 */
  __IO uint32_t SWVALUE;                           /**< Software Override Value, offset: 0x288 */
  __IO uint32_t OUTEN;                             /**< Output Enable, offset: 0x28C */
  __I  uint32_t LCIN;                              /**< Logic Inputs, offset: 0x290 */
  __I  uint32_t SWOUT;                             /**< Overridden Inputs, offset: 0x294 */
  __I  uint32_t LCOUT;                             /**< Logic Outputs, offset: 0x298 */
  __I  uint32_t FORCEOUT;                          /**< Forced Outputs, offset: 0x29C */
  __IO uint32_t FORCESTS;                          /**< Force Status, offset: 0x2A0 */
  uint8_t RESERVED_2[4];
  __IO uint32_t DBGEN;                             /**< Debug Mode Enable, offset: 0x2A8 */
} LCU_Type, *LCU_MemMapPtr;

/** Number of instances of the LCU module. */
#define LCU_INSTANCE_COUNT                       (2u)

/* LCU - Peripheral instance base addresses */
/** Peripheral LCU_0 base address */
#define IP_LCU_0_BASE                            (0x40098000u)
/** Peripheral LCU_0 base pointer */
#define IP_LCU_0                                 ((LCU_Type *)IP_LCU_0_BASE)
/** Peripheral LCU_1 base address */
#define IP_LCU_1_BASE                            (0x4009C000u)
/** Peripheral LCU_1 base pointer */
#define IP_LCU_1                                 ((LCU_Type *)IP_LCU_1_BASE)
/** Array initializer of LCU peripheral base addresses */
#define IP_LCU_BASE_ADDRS                        { IP_LCU_0_BASE, IP_LCU_1_BASE }
/** Array initializer of LCU peripheral base pointers */
#define IP_LCU_BASE_PTRS                         { IP_LCU_0, IP_LCU_1 }

/* ----------------------------------------------------------------------------
   -- LCU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCU_Register_Masks LCU Register Masks
 * @{
 */

/*! @name LUTCTRL - LC 0 Output 0 LUT Control..LC 2 Output 3 LUT Control */
/*! @{ */

#define LCU_LUTCTRL_LUTCTRL_MASK                 (0xFFFFU)
#define LCU_LUTCTRL_LUTCTRL_SHIFT                (0U)
#define LCU_LUTCTRL_LUTCTRL_WIDTH                (16U)
#define LCU_LUTCTRL_LUTCTRL(x)                   (((uint32_t)(((uint32_t)(x)) << LCU_LUTCTRL_LUTCTRL_SHIFT)) & LCU_LUTCTRL_LUTCTRL_MASK)
/*! @} */

/*! @name FILT - LC 0 Output 0 Filter..LC 2 Output 3 Filter */
/*! @{ */

#define LCU_FILT_LUT_FALL_FILT_MASK              (0xFFFFU)
#define LCU_FILT_LUT_FALL_FILT_SHIFT             (0U)
#define LCU_FILT_LUT_FALL_FILT_WIDTH             (16U)
#define LCU_FILT_LUT_FALL_FILT(x)                (((uint32_t)(((uint32_t)(x)) << LCU_FILT_LUT_FALL_FILT_SHIFT)) & LCU_FILT_LUT_FALL_FILT_MASK)

#define LCU_FILT_LUT_RISE_FILT_MASK              (0xFFFF0000U)
#define LCU_FILT_LUT_RISE_FILT_SHIFT             (16U)
#define LCU_FILT_LUT_RISE_FILT_WIDTH             (16U)
#define LCU_FILT_LUT_RISE_FILT(x)                (((uint32_t)(((uint32_t)(x)) << LCU_FILT_LUT_RISE_FILT_SHIFT)) & LCU_FILT_LUT_RISE_FILT_MASK)
/*! @} */

/*! @name INTDMAEN - LC 0 Interrupt and DMA Enable..LC 2 Interrupt and DMA Enable */
/*! @{ */

#define LCU_INTDMAEN_LUT_INT_EN_MASK             (0xFU)
#define LCU_INTDMAEN_LUT_INT_EN_SHIFT            (0U)
#define LCU_INTDMAEN_LUT_INT_EN_WIDTH            (4U)
#define LCU_INTDMAEN_LUT_INT_EN(x)               (((uint32_t)(((uint32_t)(x)) << LCU_INTDMAEN_LUT_INT_EN_SHIFT)) & LCU_INTDMAEN_LUT_INT_EN_MASK)

#define LCU_INTDMAEN_LUT_DMA_EN_MASK             (0xF00U)
#define LCU_INTDMAEN_LUT_DMA_EN_SHIFT            (8U)
#define LCU_INTDMAEN_LUT_DMA_EN_WIDTH            (4U)
#define LCU_INTDMAEN_LUT_DMA_EN(x)               (((uint32_t)(((uint32_t)(x)) << LCU_INTDMAEN_LUT_DMA_EN_SHIFT)) & LCU_INTDMAEN_LUT_DMA_EN_MASK)

#define LCU_INTDMAEN_FORCE_INT_EN_MASK           (0xF0000U)
#define LCU_INTDMAEN_FORCE_INT_EN_SHIFT          (16U)
#define LCU_INTDMAEN_FORCE_INT_EN_WIDTH          (4U)
#define LCU_INTDMAEN_FORCE_INT_EN(x)             (((uint32_t)(((uint32_t)(x)) << LCU_INTDMAEN_FORCE_INT_EN_SHIFT)) & LCU_INTDMAEN_FORCE_INT_EN_MASK)

#define LCU_INTDMAEN_FORCE_DMA_EN_MASK           (0xF000000U)
#define LCU_INTDMAEN_FORCE_DMA_EN_SHIFT          (24U)
#define LCU_INTDMAEN_FORCE_DMA_EN_WIDTH          (4U)
#define LCU_INTDMAEN_FORCE_DMA_EN(x)             (((uint32_t)(((uint32_t)(x)) << LCU_INTDMAEN_FORCE_DMA_EN_SHIFT)) & LCU_INTDMAEN_FORCE_DMA_EN_MASK)
/*! @} */

/*! @name STS - LC 0 Status..LC 2 Status */
/*! @{ */

#define LCU_STS_LUT_STS_MASK                     (0xFU)
#define LCU_STS_LUT_STS_SHIFT                    (0U)
#define LCU_STS_LUT_STS_WIDTH                    (4U)
#define LCU_STS_LUT_STS(x)                       (((uint32_t)(((uint32_t)(x)) << LCU_STS_LUT_STS_SHIFT)) & LCU_STS_LUT_STS_MASK)

#define LCU_STS_FORCESTS_MASK                    (0xF00U)
#define LCU_STS_FORCESTS_SHIFT                   (8U)
#define LCU_STS_FORCESTS_WIDTH                   (4U)
#define LCU_STS_FORCESTS(x)                      (((uint32_t)(((uint32_t)(x)) << LCU_STS_FORCESTS_SHIFT)) & LCU_STS_FORCESTS_MASK)
/*! @} */

/*! @name OUTPOL - LC 0 Output Polarity Control..LC 2 Output Polarity Control */
/*! @{ */

#define LCU_OUTPOL_OUTPOL_MASK                   (0xFU)
#define LCU_OUTPOL_OUTPOL_SHIFT                  (0U)
#define LCU_OUTPOL_OUTPOL_WIDTH                  (4U)
#define LCU_OUTPOL_OUTPOL(x)                     (((uint32_t)(((uint32_t)(x)) << LCU_OUTPOL_OUTPOL_SHIFT)) & LCU_OUTPOL_OUTPOL_MASK)
/*! @} */

/*! @name FFILT - LC 0 Force Filter..LC 2 Force Filter */
/*! @{ */

#define LCU_FFILT_FORCE_FILT_MASK                (0xFFU)
#define LCU_FFILT_FORCE_FILT_SHIFT               (0U)
#define LCU_FFILT_FORCE_FILT_WIDTH               (8U)
#define LCU_FFILT_FORCE_FILT(x)                  (((uint32_t)(((uint32_t)(x)) << LCU_FFILT_FORCE_FILT_SHIFT)) & LCU_FFILT_FORCE_FILT_MASK)

#define LCU_FFILT_FORCE_POL_MASK                 (0x70000U)
#define LCU_FFILT_FORCE_POL_SHIFT                (16U)
#define LCU_FFILT_FORCE_POL_WIDTH                (3U)
#define LCU_FFILT_FORCE_POL(x)                   (((uint32_t)(((uint32_t)(x)) << LCU_FFILT_FORCE_POL_SHIFT)) & LCU_FFILT_FORCE_POL_MASK)

#define LCU_FFILT_COMB_EN_MASK                   (0x7000000U)
#define LCU_FFILT_COMB_EN_SHIFT                  (24U)
#define LCU_FFILT_COMB_EN_WIDTH                  (3U)
#define LCU_FFILT_COMB_EN(x)                     (((uint32_t)(((uint32_t)(x)) << LCU_FFILT_COMB_EN_SHIFT)) & LCU_FFILT_COMB_EN_MASK)

#define LCU_FFILT_COMB_FORCE_MASK                (0xF0000000U)
#define LCU_FFILT_COMB_FORCE_SHIFT               (28U)
#define LCU_FFILT_COMB_FORCE_WIDTH               (4U)
#define LCU_FFILT_COMB_FORCE(x)                  (((uint32_t)(((uint32_t)(x)) << LCU_FFILT_COMB_FORCE_SHIFT)) & LCU_FFILT_COMB_FORCE_MASK)
/*! @} */

/*! @name FCTRL - LC 0 Force Control..LC 2 Force Control */
/*! @{ */

#define LCU_FCTRL_FORCE_SENSE0_MASK              (0xFU)
#define LCU_FCTRL_FORCE_SENSE0_SHIFT             (0U)
#define LCU_FCTRL_FORCE_SENSE0_WIDTH             (4U)
#define LCU_FCTRL_FORCE_SENSE0(x)                (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_SENSE0_SHIFT)) & LCU_FCTRL_FORCE_SENSE0_MASK)

#define LCU_FCTRL_FORCE_MODE0_MASK               (0x30U)
#define LCU_FCTRL_FORCE_MODE0_SHIFT              (4U)
#define LCU_FCTRL_FORCE_MODE0_WIDTH              (2U)
#define LCU_FCTRL_FORCE_MODE0(x)                 (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_MODE0_SHIFT)) & LCU_FCTRL_FORCE_MODE0_MASK)

#define LCU_FCTRL_SYNC_SEL0_MASK                 (0xC0U)
#define LCU_FCTRL_SYNC_SEL0_SHIFT                (6U)
#define LCU_FCTRL_SYNC_SEL0_WIDTH                (2U)
#define LCU_FCTRL_SYNC_SEL0(x)                   (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_SYNC_SEL0_SHIFT)) & LCU_FCTRL_SYNC_SEL0_MASK)

#define LCU_FCTRL_FORCE_SENSE1_MASK              (0xF00U)
#define LCU_FCTRL_FORCE_SENSE1_SHIFT             (8U)
#define LCU_FCTRL_FORCE_SENSE1_WIDTH             (4U)
#define LCU_FCTRL_FORCE_SENSE1(x)                (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_SENSE1_SHIFT)) & LCU_FCTRL_FORCE_SENSE1_MASK)

#define LCU_FCTRL_FORCE_MODE1_MASK               (0x3000U)
#define LCU_FCTRL_FORCE_MODE1_SHIFT              (12U)
#define LCU_FCTRL_FORCE_MODE1_WIDTH              (2U)
#define LCU_FCTRL_FORCE_MODE1(x)                 (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_MODE1_SHIFT)) & LCU_FCTRL_FORCE_MODE1_MASK)

#define LCU_FCTRL_SYNC_SEL1_MASK                 (0xC000U)
#define LCU_FCTRL_SYNC_SEL1_SHIFT                (14U)
#define LCU_FCTRL_SYNC_SEL1_WIDTH                (2U)
#define LCU_FCTRL_SYNC_SEL1(x)                   (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_SYNC_SEL1_SHIFT)) & LCU_FCTRL_SYNC_SEL1_MASK)

#define LCU_FCTRL_FORCE_SENSE2_MASK              (0xF0000U)
#define LCU_FCTRL_FORCE_SENSE2_SHIFT             (16U)
#define LCU_FCTRL_FORCE_SENSE2_WIDTH             (4U)
#define LCU_FCTRL_FORCE_SENSE2(x)                (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_SENSE2_SHIFT)) & LCU_FCTRL_FORCE_SENSE2_MASK)

#define LCU_FCTRL_FORCE_MODE2_MASK               (0x300000U)
#define LCU_FCTRL_FORCE_MODE2_SHIFT              (20U)
#define LCU_FCTRL_FORCE_MODE2_WIDTH              (2U)
#define LCU_FCTRL_FORCE_MODE2(x)                 (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_MODE2_SHIFT)) & LCU_FCTRL_FORCE_MODE2_MASK)

#define LCU_FCTRL_SYNC_SEL2_MASK                 (0xC00000U)
#define LCU_FCTRL_SYNC_SEL2_SHIFT                (22U)
#define LCU_FCTRL_SYNC_SEL2_WIDTH                (2U)
#define LCU_FCTRL_SYNC_SEL2(x)                   (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_SYNC_SEL2_SHIFT)) & LCU_FCTRL_SYNC_SEL2_MASK)

#define LCU_FCTRL_FORCE_SENSE3_MASK              (0xF000000U)
#define LCU_FCTRL_FORCE_SENSE3_SHIFT             (24U)
#define LCU_FCTRL_FORCE_SENSE3_WIDTH             (4U)
#define LCU_FCTRL_FORCE_SENSE3(x)                (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_SENSE3_SHIFT)) & LCU_FCTRL_FORCE_SENSE3_MASK)

#define LCU_FCTRL_FORCE_MODE3_MASK               (0x30000000U)
#define LCU_FCTRL_FORCE_MODE3_SHIFT              (28U)
#define LCU_FCTRL_FORCE_MODE3_WIDTH              (2U)
#define LCU_FCTRL_FORCE_MODE3(x)                 (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_FORCE_MODE3_SHIFT)) & LCU_FCTRL_FORCE_MODE3_MASK)

#define LCU_FCTRL_SYNC_SEL3_MASK                 (0xC0000000U)
#define LCU_FCTRL_SYNC_SEL3_SHIFT                (30U)
#define LCU_FCTRL_SYNC_SEL3_WIDTH                (2U)
#define LCU_FCTRL_SYNC_SEL3(x)                   (((uint32_t)(((uint32_t)(x)) << LCU_FCTRL_SYNC_SEL3_SHIFT)) & LCU_FCTRL_SYNC_SEL3_MASK)
/*! @} */

/*! @name SCTRL - LC 0 Sync Control..LC 2 Sync Control */
/*! @{ */

#define LCU_SCTRL_SW_MODE_MASK                   (0xFU)
#define LCU_SCTRL_SW_MODE_SHIFT                  (0U)
#define LCU_SCTRL_SW_MODE_WIDTH                  (4U)
#define LCU_SCTRL_SW_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << LCU_SCTRL_SW_MODE_SHIFT)) & LCU_SCTRL_SW_MODE_MASK)

#define LCU_SCTRL_SW_SYNC_SEL_MASK               (0x300U)
#define LCU_SCTRL_SW_SYNC_SEL_SHIFT              (8U)
#define LCU_SCTRL_SW_SYNC_SEL_WIDTH              (2U)
#define LCU_SCTRL_SW_SYNC_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << LCU_SCTRL_SW_SYNC_SEL_SHIFT)) & LCU_SCTRL_SW_SYNC_SEL_MASK)
/*! @} */

/*! @name MUXSEL - Mux Select */
/*! @{ */

#define LCU_MUXSEL_MUXSEL_MASK                   (0xFFU)
#define LCU_MUXSEL_MUXSEL_SHIFT                  (0U)
#define LCU_MUXSEL_MUXSEL_WIDTH                  (8U)
#define LCU_MUXSEL_MUXSEL(x)                     (((uint32_t)(((uint32_t)(x)) << LCU_MUXSEL_MUXSEL_SHIFT)) & LCU_MUXSEL_MUXSEL_MASK)
/*! @} */

/*! @name CFG - Configuration */
/*! @{ */

#define LCU_CFG_WP_MASK                          (0x1U)
#define LCU_CFG_WP_SHIFT                         (0U)
#define LCU_CFG_WP_WIDTH                         (1U)
#define LCU_CFG_WP(x)                            (((uint32_t)(((uint32_t)(x)) << LCU_CFG_WP_SHIFT)) & LCU_CFG_WP_MASK)

#define LCU_CFG_INCL_MUXES_MASK                  (0x80U)
#define LCU_CFG_INCL_MUXES_SHIFT                 (7U)
#define LCU_CFG_INCL_MUXES_WIDTH                 (1U)
#define LCU_CFG_INCL_MUXES(x)                    (((uint32_t)(((uint32_t)(x)) << LCU_CFG_INCL_MUXES_SHIFT)) & LCU_CFG_INCL_MUXES_MASK)

#define LCU_CFG_NUM_SYNCS_MASK                   (0xFF00U)
#define LCU_CFG_NUM_SYNCS_SHIFT                  (8U)
#define LCU_CFG_NUM_SYNCS_WIDTH                  (8U)
#define LCU_CFG_NUM_SYNCS(x)                     (((uint32_t)(((uint32_t)(x)) << LCU_CFG_NUM_SYNCS_SHIFT)) & LCU_CFG_NUM_SYNCS_MASK)

#define LCU_CFG_NUM_FORCES_MASK                  (0xFF0000U)
#define LCU_CFG_NUM_FORCES_SHIFT                 (16U)
#define LCU_CFG_NUM_FORCES_WIDTH                 (8U)
#define LCU_CFG_NUM_FORCES(x)                    (((uint32_t)(((uint32_t)(x)) << LCU_CFG_NUM_FORCES_SHIFT)) & LCU_CFG_NUM_FORCES_MASK)

#define LCU_CFG_NUM_LOGIC_CELLS_MASK             (0xFF000000U)
#define LCU_CFG_NUM_LOGIC_CELLS_SHIFT            (24U)
#define LCU_CFG_NUM_LOGIC_CELLS_WIDTH            (8U)
#define LCU_CFG_NUM_LOGIC_CELLS(x)               (((uint32_t)(((uint32_t)(x)) << LCU_CFG_NUM_LOGIC_CELLS_SHIFT)) & LCU_CFG_NUM_LOGIC_CELLS_MASK)
/*! @} */

/*! @name SWEN - Software Override Enable */
/*! @{ */

#define LCU_SWEN_SWEN_MASK                       (0xFFFU)
#define LCU_SWEN_SWEN_SHIFT                      (0U)
#define LCU_SWEN_SWEN_WIDTH                      (12U)
#define LCU_SWEN_SWEN(x)                         (((uint32_t)(((uint32_t)(x)) << LCU_SWEN_SWEN_SHIFT)) & LCU_SWEN_SWEN_MASK)
/*! @} */

/*! @name SWVALUE - Software Override Value */
/*! @{ */

#define LCU_SWVALUE_SWVALUE_MASK                 (0xFFFU)
#define LCU_SWVALUE_SWVALUE_SHIFT                (0U)
#define LCU_SWVALUE_SWVALUE_WIDTH                (12U)
#define LCU_SWVALUE_SWVALUE(x)                   (((uint32_t)(((uint32_t)(x)) << LCU_SWVALUE_SWVALUE_SHIFT)) & LCU_SWVALUE_SWVALUE_MASK)
/*! @} */

/*! @name OUTEN - Output Enable */
/*! @{ */

#define LCU_OUTEN_OUTEN_MASK                     (0xFFFU)
#define LCU_OUTEN_OUTEN_SHIFT                    (0U)
#define LCU_OUTEN_OUTEN_WIDTH                    (12U)
#define LCU_OUTEN_OUTEN(x)                       (((uint32_t)(((uint32_t)(x)) << LCU_OUTEN_OUTEN_SHIFT)) & LCU_OUTEN_OUTEN_MASK)
/*! @} */

/*! @name LCIN - Logic Inputs */
/*! @{ */

#define LCU_LCIN_LC_INPUTS_MASK                  (0xFFFU)
#define LCU_LCIN_LC_INPUTS_SHIFT                 (0U)
#define LCU_LCIN_LC_INPUTS_WIDTH                 (12U)
#define LCU_LCIN_LC_INPUTS(x)                    (((uint32_t)(((uint32_t)(x)) << LCU_LCIN_LC_INPUTS_SHIFT)) & LCU_LCIN_LC_INPUTS_MASK)
/*! @} */

/*! @name SWOUT - Overridden Inputs */
/*! @{ */

#define LCU_SWOUT_SWOUT_MASK                     (0xFFFU)
#define LCU_SWOUT_SWOUT_SHIFT                    (0U)
#define LCU_SWOUT_SWOUT_WIDTH                    (12U)
#define LCU_SWOUT_SWOUT(x)                       (((uint32_t)(((uint32_t)(x)) << LCU_SWOUT_SWOUT_SHIFT)) & LCU_SWOUT_SWOUT_MASK)
/*! @} */

/*! @name LCOUT - Logic Outputs */
/*! @{ */

#define LCU_LCOUT_LCOUT_MASK                     (0xFFFU)
#define LCU_LCOUT_LCOUT_SHIFT                    (0U)
#define LCU_LCOUT_LCOUT_WIDTH                    (12U)
#define LCU_LCOUT_LCOUT(x)                       (((uint32_t)(((uint32_t)(x)) << LCU_LCOUT_LCOUT_SHIFT)) & LCU_LCOUT_LCOUT_MASK)
/*! @} */

/*! @name FORCEOUT - Forced Outputs */
/*! @{ */

#define LCU_FORCEOUT_FORCEOUT_MASK               (0xFFFU)
#define LCU_FORCEOUT_FORCEOUT_SHIFT              (0U)
#define LCU_FORCEOUT_FORCEOUT_WIDTH              (12U)
#define LCU_FORCEOUT_FORCEOUT(x)                 (((uint32_t)(((uint32_t)(x)) << LCU_FORCEOUT_FORCEOUT_SHIFT)) & LCU_FORCEOUT_FORCEOUT_MASK)
/*! @} */

/*! @name FORCESTS - Force Status */
/*! @{ */

#define LCU_FORCESTS_FORCESTS_MASK               (0xFFFU)
#define LCU_FORCESTS_FORCESTS_SHIFT              (0U)
#define LCU_FORCESTS_FORCESTS_WIDTH              (12U)
#define LCU_FORCESTS_FORCESTS(x)                 (((uint32_t)(((uint32_t)(x)) << LCU_FORCESTS_FORCESTS_SHIFT)) & LCU_FORCESTS_FORCESTS_MASK)
/*! @} */

/*! @name DBGEN - Debug Mode Enable */
/*! @{ */

#define LCU_DBGEN_DBGEN_MASK                     (0xFFFU)
#define LCU_DBGEN_DBGEN_SHIFT                    (0U)
#define LCU_DBGEN_DBGEN_WIDTH                    (12U)
#define LCU_DBGEN_DBGEN(x)                       (((uint32_t)(((uint32_t)(x)) << LCU_DBGEN_DBGEN_SHIFT)) & LCU_DBGEN_DBGEN_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LCU_Register_Masks */

/*!
 * @}
 */ /* end of group LCU_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_LCU_H_) */
