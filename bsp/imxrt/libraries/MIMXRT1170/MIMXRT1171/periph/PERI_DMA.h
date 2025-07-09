/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for DMA
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_DMA.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for DMA
 *
 * CMSIS Peripheral Access Layer for DMA
 */

#if !defined(PERI_DMA_H_)
#define PERI_DMA_H_                              /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Size of Registers Arrays */
#define DMA_TCD_COUNT                             32u

/** DMA - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< Control, offset: 0x0 */
  __I  uint32_t ES;                                /**< Error Status, offset: 0x4 */
       uint8_t RESERVED_0[4];
  __IO uint32_t ERQ;                               /**< Enable Request, offset: 0xC */
       uint8_t RESERVED_1[4];
  __IO uint32_t EEI;                               /**< Enable Error Interrupt, offset: 0x14 */
  __IO uint8_t CEEI;                               /**< Clear Enable Error Interrupt, offset: 0x18 */
  __IO uint8_t SEEI;                               /**< Set Enable Error Interrupt, offset: 0x19 */
  __IO uint8_t CERQ;                               /**< Clear Enable Request, offset: 0x1A */
  __IO uint8_t SERQ;                               /**< Set Enable Request, offset: 0x1B */
  __IO uint8_t CDNE;                               /**< Clear DONE Status Bit, offset: 0x1C */
  __IO uint8_t SSRT;                               /**< Set START Bit, offset: 0x1D */
  __IO uint8_t CERR;                               /**< Clear Error, offset: 0x1E */
  __IO uint8_t CINT;                               /**< Clear Interrupt Request, offset: 0x1F */
       uint8_t RESERVED_2[4];
  __IO uint32_t INT;                               /**< Interrupt Request, offset: 0x24 */
       uint8_t RESERVED_3[4];
  __IO uint32_t ERR;                               /**< Error, offset: 0x2C */
       uint8_t RESERVED_4[4];
  __I  uint32_t HRS;                               /**< Hardware Request Status, offset: 0x34 */
       uint8_t RESERVED_5[12];
  __IO uint32_t EARS;                              /**< Enable Asynchronous Request in Stop, offset: 0x44 */
       uint8_t RESERVED_6[184];
  __IO uint8_t DCHPRI3;                            /**< Channel Priority, offset: 0x100 */
  __IO uint8_t DCHPRI2;                            /**< Channel Priority, offset: 0x101 */
  __IO uint8_t DCHPRI1;                            /**< Channel Priority, offset: 0x102 */
  __IO uint8_t DCHPRI0;                            /**< Channel Priority, offset: 0x103 */
  __IO uint8_t DCHPRI7;                            /**< Channel Priority, offset: 0x104 */
  __IO uint8_t DCHPRI6;                            /**< Channel Priority, offset: 0x105 */
  __IO uint8_t DCHPRI5;                            /**< Channel Priority, offset: 0x106 */
  __IO uint8_t DCHPRI4;                            /**< Channel Priority, offset: 0x107 */
  __IO uint8_t DCHPRI11;                           /**< Channel Priority, offset: 0x108 */
  __IO uint8_t DCHPRI10;                           /**< Channel Priority, offset: 0x109 */
  __IO uint8_t DCHPRI9;                            /**< Channel Priority, offset: 0x10A */
  __IO uint8_t DCHPRI8;                            /**< Channel Priority, offset: 0x10B */
  __IO uint8_t DCHPRI15;                           /**< Channel Priority, offset: 0x10C */
  __IO uint8_t DCHPRI14;                           /**< Channel Priority, offset: 0x10D */
  __IO uint8_t DCHPRI13;                           /**< Channel Priority, offset: 0x10E */
  __IO uint8_t DCHPRI12;                           /**< Channel Priority, offset: 0x10F */
  __IO uint8_t DCHPRI19;                           /**< Channel Priority, offset: 0x110 */
  __IO uint8_t DCHPRI18;                           /**< Channel Priority, offset: 0x111 */
  __IO uint8_t DCHPRI17;                           /**< Channel Priority, offset: 0x112 */
  __IO uint8_t DCHPRI16;                           /**< Channel Priority, offset: 0x113 */
  __IO uint8_t DCHPRI23;                           /**< Channel Priority, offset: 0x114 */
  __IO uint8_t DCHPRI22;                           /**< Channel Priority, offset: 0x115 */
  __IO uint8_t DCHPRI21;                           /**< Channel Priority, offset: 0x116 */
  __IO uint8_t DCHPRI20;                           /**< Channel Priority, offset: 0x117 */
  __IO uint8_t DCHPRI27;                           /**< Channel Priority, offset: 0x118 */
  __IO uint8_t DCHPRI26;                           /**< Channel Priority, offset: 0x119 */
  __IO uint8_t DCHPRI25;                           /**< Channel Priority, offset: 0x11A */
  __IO uint8_t DCHPRI24;                           /**< Channel Priority, offset: 0x11B */
  __IO uint8_t DCHPRI31;                           /**< Channel Priority, offset: 0x11C */
  __IO uint8_t DCHPRI30;                           /**< Channel Priority, offset: 0x11D */
  __IO uint8_t DCHPRI29;                           /**< Channel Priority, offset: 0x11E */
  __IO uint8_t DCHPRI28;                           /**< Channel Priority, offset: 0x11F */
       uint8_t RESERVED_7[3808];
  struct {                                         /* offset: 0x1000, array step: 0x20 */
    __IO uint32_t SADDR;                             /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
    __IO uint16_t SOFF;                              /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
    __IO uint16_t ATTR;                              /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
    union {                                          /* offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLNO;                       /**< TCD Minor Byte Count (Minor Loop Mapping Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLOFFNO;                    /**< TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled), array offset: 0x1008, array step: 0x20 */
      __IO uint32_t NBYTES_MLOFFYES;                   /**< TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled), array offset: 0x1008, array step: 0x20 */
    };
    __IO int32_t SLAST;                              /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
    __IO uint32_t DADDR;                             /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
    __IO uint16_t DOFF;                              /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
    union {                                          /* offset: 0x1016, array step: 0x20 */
      __IO uint16_t CITER_ELINKNO;                     /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1016, array step: 0x20 */
      __IO uint16_t CITER_ELINKYES;                    /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x1016, array step: 0x20 */
    };
    __IO int32_t DLAST_SGA;                          /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
    __IO uint16_t CSR;                               /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
    union {                                          /* offset: 0x101E, array step: 0x20 */
      __IO uint16_t BITER_ELINKNO;                     /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101E, array step: 0x20 */
      __IO uint16_t BITER_ELINKYES;                    /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x101E, array step: 0x20 */
    };
  } TCD[DMA_TCD_COUNT];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name CR - Control */
/*! @{ */

#define DMA_CR_EDBG_MASK                         (0x2U)
#define DMA_CR_EDBG_SHIFT                        (1U)
/*! EDBG - Enable Debug
 *  0b0..When the chip is in Debug mode, the eDMA continues to operate.
 *  0b1..When the chip is in debug mode, the DMA stalls the start of a new channel. Executing channels are allowed to complete.
 */
#define DMA_CR_EDBG(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_EDBG_SHIFT)) & DMA_CR_EDBG_MASK)

#define DMA_CR_ERCA_MASK                         (0x4U)
#define DMA_CR_ERCA_SHIFT                        (2U)
/*! ERCA - Enable Round Robin Channel Arbitration
 *  0b0..Fixed priority arbitration within each group
 *  0b1..Round robin arbitration within each group
 */
#define DMA_CR_ERCA(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_ERCA_SHIFT)) & DMA_CR_ERCA_MASK)

#define DMA_CR_ERGA_MASK                         (0x8U)
#define DMA_CR_ERGA_SHIFT                        (3U)
/*! ERGA - Enable Round Robin Group Arbitration
 *  0b0..Fixed priority arbitration
 *  0b1..Round robin arbitration
 */
#define DMA_CR_ERGA(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_ERGA_SHIFT)) & DMA_CR_ERGA_MASK)

#define DMA_CR_HOE_MASK                          (0x10U)
#define DMA_CR_HOE_SHIFT                         (4U)
/*! HOE - Halt On Error
 *  0b0..Normal operation
 *  0b1..Error causes HALT field to be automatically set to 1
 */
#define DMA_CR_HOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_HOE_SHIFT)) & DMA_CR_HOE_MASK)

#define DMA_CR_HALT_MASK                         (0x20U)
#define DMA_CR_HALT_SHIFT                        (5U)
/*! HALT - Halt eDMA Operations
 *  0b0..Normal operation
 *  0b1..eDMA operations halted
 */
#define DMA_CR_HALT(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_HALT_SHIFT)) & DMA_CR_HALT_MASK)

#define DMA_CR_CLM_MASK                          (0x40U)
#define DMA_CR_CLM_SHIFT                         (6U)
/*! CLM - Continuous Link Mode
 *  0b0..Continuous link mode is off
 *  0b1..Continuous link mode is on
 */
#define DMA_CR_CLM(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_CLM_SHIFT)) & DMA_CR_CLM_MASK)

#define DMA_CR_EMLM_MASK                         (0x80U)
#define DMA_CR_EMLM_SHIFT                        (7U)
/*! EMLM - Enable Minor Loop Mapping
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define DMA_CR_EMLM(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CR_EMLM_SHIFT)) & DMA_CR_EMLM_MASK)

#define DMA_CR_GRP0PRI_MASK                      (0x100U)
#define DMA_CR_GRP0PRI_SHIFT                     (8U)
/*! GRP0PRI - Channel Group 0 Priority */
#define DMA_CR_GRP0PRI(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CR_GRP0PRI_SHIFT)) & DMA_CR_GRP0PRI_MASK)

#define DMA_CR_GRP1PRI_MASK                      (0x400U)
#define DMA_CR_GRP1PRI_SHIFT                     (10U)
/*! GRP1PRI - Channel Group 1 Priority */
#define DMA_CR_GRP1PRI(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CR_GRP1PRI_SHIFT)) & DMA_CR_GRP1PRI_MASK)

#define DMA_CR_ECX_MASK                          (0x10000U)
#define DMA_CR_ECX_SHIFT                         (16U)
/*! ECX - Error Cancel Transfer
 *  0b0..Normal operation
 *  0b1..Cancel the remaining data transfer
 */
#define DMA_CR_ECX(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_CR_ECX_SHIFT)) & DMA_CR_ECX_MASK)

#define DMA_CR_CX_MASK                           (0x20000U)
#define DMA_CR_CX_SHIFT                          (17U)
/*! CX - Cancel Transfer
 *  0b0..Normal operation
 *  0b1..Cancel the remaining data transfer
 */
#define DMA_CR_CX(x)                             (((uint32_t)(((uint32_t)(x)) << DMA_CR_CX_SHIFT)) & DMA_CR_CX_MASK)

#define DMA_CR_VERSION_MASK                      (0x7F000000U)
#define DMA_CR_VERSION_SHIFT                     (24U)
/*! VERSION - eDMA version number */
#define DMA_CR_VERSION(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CR_VERSION_SHIFT)) & DMA_CR_VERSION_MASK)

#define DMA_CR_ACTIVE_MASK                       (0x80000000U)
#define DMA_CR_ACTIVE_SHIFT                      (31U)
/*! ACTIVE - eDMA Active Status
 *  0b0..eDMA is idle
 *  0b1..eDMA is executing a channel
 */
#define DMA_CR_ACTIVE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_CR_ACTIVE_SHIFT)) & DMA_CR_ACTIVE_MASK)
/*! @} */

/*! @name ES - Error Status */
/*! @{ */

#define DMA_ES_DBE_MASK                          (0x1U)
#define DMA_ES_DBE_SHIFT                         (0U)
/*! DBE - Destination Bus Error
 *  0b0..No destination bus error.
 *  0b1..The most-recently recorded error was a bus error on a destination write.
 */
#define DMA_ES_DBE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DBE_SHIFT)) & DMA_ES_DBE_MASK)

#define DMA_ES_SBE_MASK                          (0x2U)
#define DMA_ES_SBE_SHIFT                         (1U)
/*! SBE - Source Bus Error
 *  0b0..No source bus error.
 *  0b1..The most-recently recorded error was a bus error on a source read.
 */
#define DMA_ES_SBE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SBE_SHIFT)) & DMA_ES_SBE_MASK)

#define DMA_ES_SGE_MASK                          (0x4U)
#define DMA_ES_SGE_SHIFT                         (2U)
/*! SGE - Scatter/Gather Configuration Error
 *  0b0..No scatter/gather configuration error.
 *  0b1..The most-recently recorded error was a configuration error detected in the TCDn_DLASTSGA field.
 */
#define DMA_ES_SGE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SGE_SHIFT)) & DMA_ES_SGE_MASK)

#define DMA_ES_NCE_MASK                          (0x8U)
#define DMA_ES_NCE_SHIFT                         (3U)
/*! NCE - NBYTES/CITER Configuration Error
 *  0b0..No NBYTES/CITER configuration error.
 *  0b1..The most-recently recorded error was a configuration error detected in the TCDn_NBYTES or TCDn_CITER
 *       fields. TCDn_NBYTES is not a multiple of TCDn_ATTR[SSIZE] and TCDn_ATTR[DSIZE], or TCDn_CITER[CITER] = 0, or
 *       TCDn_CITER[ELINK] is not equal to TCDn_BITER[ELINK].
 */
#define DMA_ES_NCE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_NCE_SHIFT)) & DMA_ES_NCE_MASK)

#define DMA_ES_DOE_MASK                          (0x10U)
#define DMA_ES_DOE_SHIFT                         (4U)
/*! DOE - Destination Offset Error
 *  0b0..No destination offset configuration error.
 *  0b1..The most-recently recorded error was a configuration error detected in the TCDn_DOFF field. TCDn_DOFF is inconsistent with TCDn_ATTR[DSIZE].
 */
#define DMA_ES_DOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DOE_SHIFT)) & DMA_ES_DOE_MASK)

#define DMA_ES_DAE_MASK                          (0x20U)
#define DMA_ES_DAE_SHIFT                         (5U)
/*! DAE - Destination Address Error
 *  0b0..No destination address configuration error.
 *  0b1..The most-recently recorded error was a configuration error detected in the TCDn_DADDR field. TCDn_DADDR
 *       is inconsistent with TCDn_ATTR[DSIZE].
 */
#define DMA_ES_DAE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_DAE_SHIFT)) & DMA_ES_DAE_MASK)

#define DMA_ES_SOE_MASK                          (0x40U)
#define DMA_ES_SOE_SHIFT                         (6U)
/*! SOE - Source Offset Error
 *  0b0..No source offset configuration error.
 *  0b1..The most-recently recorded error was a configuration error detected in the TCDn_SOFF field. TCDn_SOFF is inconsistent with TCDn_ATTR[SSIZE].
 */
#define DMA_ES_SOE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SOE_SHIFT)) & DMA_ES_SOE_MASK)

#define DMA_ES_SAE_MASK                          (0x80U)
#define DMA_ES_SAE_SHIFT                         (7U)
/*! SAE - Source Address Error
 *  0b0..No source address configuration error.
 *  0b1..The most-recently recorded error was a configuration error detected in the TCDn_SADDR field. TCDn_SADDR
 *       is inconsistent with TCDn_ATTR[SSIZE].
 */
#define DMA_ES_SAE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_SAE_SHIFT)) & DMA_ES_SAE_MASK)

#define DMA_ES_ERRCHN_MASK                       (0x1F00U)
#define DMA_ES_ERRCHN_SHIFT                      (8U)
/*! ERRCHN - Error Channel Number or Canceled Channel Number */
#define DMA_ES_ERRCHN(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ES_ERRCHN_SHIFT)) & DMA_ES_ERRCHN_MASK)

#define DMA_ES_CPE_MASK                          (0x4000U)
#define DMA_ES_CPE_SHIFT                         (14U)
/*! CPE - Channel Priority Error
 *  0b0..No channel priority error.
 *  0b1..The most-recently recorded error was a configuration error in the channel priorities within a group.
 *       Channel priorities within a group are not unique.
 */
#define DMA_ES_CPE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_CPE_SHIFT)) & DMA_ES_CPE_MASK)

#define DMA_ES_GPE_MASK                          (0x8000U)
#define DMA_ES_GPE_SHIFT                         (15U)
/*! GPE - Group Priority Error
 *  0b0..No group priority error.
 *  0b1..The most-recently recorded error was a configuration error among the group priorities. All group priorities are not unique.
 */
#define DMA_ES_GPE(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_GPE_SHIFT)) & DMA_ES_GPE_MASK)

#define DMA_ES_ECX_MASK                          (0x10000U)
#define DMA_ES_ECX_SHIFT                         (16U)
/*! ECX - Transfer Canceled
 *  0b0..No canceled transfers
 *  0b1..The most-recently recorded entry was a canceled transfer initiated by the error cancel transfer field
 */
#define DMA_ES_ECX(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_ECX_SHIFT)) & DMA_ES_ECX_MASK)

#define DMA_ES_VLD_MASK                          (0x80000000U)
#define DMA_ES_VLD_SHIFT                         (31U)
/*! VLD - Logical OR of all ERR status fields
 *  0b0..No ERR fields are 1
 *  0b1..At least one ERR field has a value of 1, indicating a valid error exists that has not been cleared
 */
#define DMA_ES_VLD(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_ES_VLD_SHIFT)) & DMA_ES_VLD_MASK)
/*! @} */

/*! @name ERQ - Enable Request */
/*! @{ */

#define DMA_ERQ_ERQ0_MASK                        (0x1U)
#define DMA_ERQ_ERQ0_SHIFT                       (0U)
/*! ERQ0 - Enable DMA Request 0
 *  0b0..The DMA request signal for channel 0 is disabled
 *  0b1..The DMA request signal for channel 0 is enabled
 */
#define DMA_ERQ_ERQ0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ0_SHIFT)) & DMA_ERQ_ERQ0_MASK)

#define DMA_ERQ_ERQ1_MASK                        (0x2U)
#define DMA_ERQ_ERQ1_SHIFT                       (1U)
/*! ERQ1 - Enable DMA Request 1
 *  0b0..The DMA request signal for channel 1 is disabled
 *  0b1..The DMA request signal for channel 1 is enabled
 */
#define DMA_ERQ_ERQ1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ1_SHIFT)) & DMA_ERQ_ERQ1_MASK)

#define DMA_ERQ_ERQ2_MASK                        (0x4U)
#define DMA_ERQ_ERQ2_SHIFT                       (2U)
/*! ERQ2 - Enable DMA Request 2
 *  0b0..The DMA request signal for channel 2 is disabled
 *  0b1..The DMA request signal for channel 2 is enabled
 */
#define DMA_ERQ_ERQ2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ2_SHIFT)) & DMA_ERQ_ERQ2_MASK)

#define DMA_ERQ_ERQ3_MASK                        (0x8U)
#define DMA_ERQ_ERQ3_SHIFT                       (3U)
/*! ERQ3 - Enable DMA Request 3
 *  0b0..The DMA request signal for channel 3 is disabled
 *  0b1..The DMA request signal for channel 3 is enabled
 */
#define DMA_ERQ_ERQ3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ3_SHIFT)) & DMA_ERQ_ERQ3_MASK)

#define DMA_ERQ_ERQ4_MASK                        (0x10U)
#define DMA_ERQ_ERQ4_SHIFT                       (4U)
/*! ERQ4 - Enable DMA Request 4
 *  0b0..The DMA request signal for channel 4 is disabled
 *  0b1..The DMA request signal for channel 4 is enabled
 */
#define DMA_ERQ_ERQ4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ4_SHIFT)) & DMA_ERQ_ERQ4_MASK)

#define DMA_ERQ_ERQ5_MASK                        (0x20U)
#define DMA_ERQ_ERQ5_SHIFT                       (5U)
/*! ERQ5 - Enable DMA Request 5
 *  0b0..The DMA request signal for channel 5 is disabled
 *  0b1..The DMA request signal for channel 5 is enabled
 */
#define DMA_ERQ_ERQ5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ5_SHIFT)) & DMA_ERQ_ERQ5_MASK)

#define DMA_ERQ_ERQ6_MASK                        (0x40U)
#define DMA_ERQ_ERQ6_SHIFT                       (6U)
/*! ERQ6 - Enable DMA Request 6
 *  0b0..The DMA request signal for channel 6 is disabled
 *  0b1..The DMA request signal for channel 6 is enabled
 */
#define DMA_ERQ_ERQ6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ6_SHIFT)) & DMA_ERQ_ERQ6_MASK)

#define DMA_ERQ_ERQ7_MASK                        (0x80U)
#define DMA_ERQ_ERQ7_SHIFT                       (7U)
/*! ERQ7 - Enable DMA Request 7
 *  0b0..The DMA request signal for channel 7 is disabled
 *  0b1..The DMA request signal for channel 7 is enabled
 */
#define DMA_ERQ_ERQ7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ7_SHIFT)) & DMA_ERQ_ERQ7_MASK)

#define DMA_ERQ_ERQ8_MASK                        (0x100U)
#define DMA_ERQ_ERQ8_SHIFT                       (8U)
/*! ERQ8 - Enable DMA Request 8
 *  0b0..The DMA request signal for channel 8 is disabled
 *  0b1..The DMA request signal for channel 8 is enabled
 */
#define DMA_ERQ_ERQ8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ8_SHIFT)) & DMA_ERQ_ERQ8_MASK)

#define DMA_ERQ_ERQ9_MASK                        (0x200U)
#define DMA_ERQ_ERQ9_SHIFT                       (9U)
/*! ERQ9 - Enable DMA Request 9
 *  0b0..The DMA request signal for channel 9 is disabled
 *  0b1..The DMA request signal for channel 9 is enabled
 */
#define DMA_ERQ_ERQ9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ9_SHIFT)) & DMA_ERQ_ERQ9_MASK)

#define DMA_ERQ_ERQ10_MASK                       (0x400U)
#define DMA_ERQ_ERQ10_SHIFT                      (10U)
/*! ERQ10 - Enable DMA Request 10
 *  0b0..The DMA request signal for channel 10 is disabled
 *  0b1..The DMA request signal for channel 10 is enabled
 */
#define DMA_ERQ_ERQ10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ10_SHIFT)) & DMA_ERQ_ERQ10_MASK)

#define DMA_ERQ_ERQ11_MASK                       (0x800U)
#define DMA_ERQ_ERQ11_SHIFT                      (11U)
/*! ERQ11 - Enable DMA Request 11
 *  0b0..The DMA request signal for channel 11 is disabled
 *  0b1..The DMA request signal for channel 11 is enabled
 */
#define DMA_ERQ_ERQ11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ11_SHIFT)) & DMA_ERQ_ERQ11_MASK)

#define DMA_ERQ_ERQ12_MASK                       (0x1000U)
#define DMA_ERQ_ERQ12_SHIFT                      (12U)
/*! ERQ12 - Enable DMA Request 12
 *  0b0..The DMA request signal for channel 12 is disabled
 *  0b1..The DMA request signal for channel 12 is enabled
 */
#define DMA_ERQ_ERQ12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ12_SHIFT)) & DMA_ERQ_ERQ12_MASK)

#define DMA_ERQ_ERQ13_MASK                       (0x2000U)
#define DMA_ERQ_ERQ13_SHIFT                      (13U)
/*! ERQ13 - Enable DMA Request 13
 *  0b0..The DMA request signal for channel 13 is disabled
 *  0b1..The DMA request signal for channel 13 is enabled
 */
#define DMA_ERQ_ERQ13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ13_SHIFT)) & DMA_ERQ_ERQ13_MASK)

#define DMA_ERQ_ERQ14_MASK                       (0x4000U)
#define DMA_ERQ_ERQ14_SHIFT                      (14U)
/*! ERQ14 - Enable DMA Request 14
 *  0b0..The DMA request signal for channel 14 is disabled
 *  0b1..The DMA request signal for channel 14 is enabled
 */
#define DMA_ERQ_ERQ14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ14_SHIFT)) & DMA_ERQ_ERQ14_MASK)

#define DMA_ERQ_ERQ15_MASK                       (0x8000U)
#define DMA_ERQ_ERQ15_SHIFT                      (15U)
/*! ERQ15 - Enable DMA Request 15
 *  0b0..The DMA request signal for channel 15 is disabled
 *  0b1..The DMA request signal for channel 15 is enabled
 */
#define DMA_ERQ_ERQ15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ15_SHIFT)) & DMA_ERQ_ERQ15_MASK)

#define DMA_ERQ_ERQ16_MASK                       (0x10000U)
#define DMA_ERQ_ERQ16_SHIFT                      (16U)
/*! ERQ16 - Enable DMA Request 16
 *  0b0..The DMA request signal for channel 16 is disabled
 *  0b1..The DMA request signal for channel 16 is enabled
 */
#define DMA_ERQ_ERQ16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ16_SHIFT)) & DMA_ERQ_ERQ16_MASK)

#define DMA_ERQ_ERQ17_MASK                       (0x20000U)
#define DMA_ERQ_ERQ17_SHIFT                      (17U)
/*! ERQ17 - Enable DMA Request 17
 *  0b0..The DMA request signal for channel 17 is disabled
 *  0b1..The DMA request signal for channel 17 is enabled
 */
#define DMA_ERQ_ERQ17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ17_SHIFT)) & DMA_ERQ_ERQ17_MASK)

#define DMA_ERQ_ERQ18_MASK                       (0x40000U)
#define DMA_ERQ_ERQ18_SHIFT                      (18U)
/*! ERQ18 - Enable DMA Request 18
 *  0b0..The DMA request signal for channel 18 is disabled
 *  0b1..The DMA request signal for channel 18 is enabled
 */
#define DMA_ERQ_ERQ18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ18_SHIFT)) & DMA_ERQ_ERQ18_MASK)

#define DMA_ERQ_ERQ19_MASK                       (0x80000U)
#define DMA_ERQ_ERQ19_SHIFT                      (19U)
/*! ERQ19 - Enable DMA Request 19
 *  0b0..The DMA request signal for channel 19 is disabled
 *  0b1..The DMA request signal for channel 19 is enabled
 */
#define DMA_ERQ_ERQ19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ19_SHIFT)) & DMA_ERQ_ERQ19_MASK)

#define DMA_ERQ_ERQ20_MASK                       (0x100000U)
#define DMA_ERQ_ERQ20_SHIFT                      (20U)
/*! ERQ20 - Enable DMA Request 20
 *  0b0..The DMA request signal for channel 20 is disabled
 *  0b1..The DMA request signal for channel 20 is enabled
 */
#define DMA_ERQ_ERQ20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ20_SHIFT)) & DMA_ERQ_ERQ20_MASK)

#define DMA_ERQ_ERQ21_MASK                       (0x200000U)
#define DMA_ERQ_ERQ21_SHIFT                      (21U)
/*! ERQ21 - Enable DMA Request 21
 *  0b0..The DMA request signal for channel 21 is disabled
 *  0b1..The DMA request signal for channel 21 is enabled
 */
#define DMA_ERQ_ERQ21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ21_SHIFT)) & DMA_ERQ_ERQ21_MASK)

#define DMA_ERQ_ERQ22_MASK                       (0x400000U)
#define DMA_ERQ_ERQ22_SHIFT                      (22U)
/*! ERQ22 - Enable DMA Request 22
 *  0b0..The DMA request signal for channel 22 is disabled
 *  0b1..The DMA request signal for channel 22 is enabled
 */
#define DMA_ERQ_ERQ22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ22_SHIFT)) & DMA_ERQ_ERQ22_MASK)

#define DMA_ERQ_ERQ23_MASK                       (0x800000U)
#define DMA_ERQ_ERQ23_SHIFT                      (23U)
/*! ERQ23 - Enable DMA Request 23
 *  0b0..The DMA request signal for channel 23 is disabled
 *  0b1..The DMA request signal for channel 23 is enabled
 */
#define DMA_ERQ_ERQ23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ23_SHIFT)) & DMA_ERQ_ERQ23_MASK)

#define DMA_ERQ_ERQ24_MASK                       (0x1000000U)
#define DMA_ERQ_ERQ24_SHIFT                      (24U)
/*! ERQ24 - Enable DMA Request 24
 *  0b0..The DMA request signal for channel 24 is disabled
 *  0b1..The DMA request signal for channel 24 is enabled
 */
#define DMA_ERQ_ERQ24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ24_SHIFT)) & DMA_ERQ_ERQ24_MASK)

#define DMA_ERQ_ERQ25_MASK                       (0x2000000U)
#define DMA_ERQ_ERQ25_SHIFT                      (25U)
/*! ERQ25 - Enable DMA Request 25
 *  0b0..The DMA request signal for channel 25 is disabled
 *  0b1..The DMA request signal for channel 25 is enabled
 */
#define DMA_ERQ_ERQ25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ25_SHIFT)) & DMA_ERQ_ERQ25_MASK)

#define DMA_ERQ_ERQ26_MASK                       (0x4000000U)
#define DMA_ERQ_ERQ26_SHIFT                      (26U)
/*! ERQ26 - Enable DMA Request 26
 *  0b0..The DMA request signal for channel 26 is disabled
 *  0b1..The DMA request signal for channel 26 is enabled
 */
#define DMA_ERQ_ERQ26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ26_SHIFT)) & DMA_ERQ_ERQ26_MASK)

#define DMA_ERQ_ERQ27_MASK                       (0x8000000U)
#define DMA_ERQ_ERQ27_SHIFT                      (27U)
/*! ERQ27 - Enable DMA Request 27
 *  0b0..The DMA request signal for channel 27 is disabled
 *  0b1..The DMA request signal for channel 27 is enabled
 */
#define DMA_ERQ_ERQ27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ27_SHIFT)) & DMA_ERQ_ERQ27_MASK)

#define DMA_ERQ_ERQ28_MASK                       (0x10000000U)
#define DMA_ERQ_ERQ28_SHIFT                      (28U)
/*! ERQ28 - Enable DMA Request 28
 *  0b0..The DMA request signal for channel 28 is disabled
 *  0b1..The DMA request signal for channel 28 is enabled
 */
#define DMA_ERQ_ERQ28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ28_SHIFT)) & DMA_ERQ_ERQ28_MASK)

#define DMA_ERQ_ERQ29_MASK                       (0x20000000U)
#define DMA_ERQ_ERQ29_SHIFT                      (29U)
/*! ERQ29 - Enable DMA Request 29
 *  0b0..The DMA request signal for channel 29 is disabled
 *  0b1..The DMA request signal for channel 29 is enabled
 */
#define DMA_ERQ_ERQ29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ29_SHIFT)) & DMA_ERQ_ERQ29_MASK)

#define DMA_ERQ_ERQ30_MASK                       (0x40000000U)
#define DMA_ERQ_ERQ30_SHIFT                      (30U)
/*! ERQ30 - Enable DMA Request 30
 *  0b0..The DMA request signal for channel 30 is disabled
 *  0b1..The DMA request signal for channel 30 is enabled
 */
#define DMA_ERQ_ERQ30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ30_SHIFT)) & DMA_ERQ_ERQ30_MASK)

#define DMA_ERQ_ERQ31_MASK                       (0x80000000U)
#define DMA_ERQ_ERQ31_SHIFT                      (31U)
/*! ERQ31 - Enable DMA Request 31
 *  0b0..The DMA request signal for channel 31 is disabled
 *  0b1..The DMA request signal for channel 31 is enabled
 */
#define DMA_ERQ_ERQ31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERQ_ERQ31_SHIFT)) & DMA_ERQ_ERQ31_MASK)
/*! @} */

/*! @name EEI - Enable Error Interrupt */
/*! @{ */

#define DMA_EEI_EEI0_MASK                        (0x1U)
#define DMA_EEI_EEI0_SHIFT                       (0U)
/*! EEI0 - Enable Error Interrupt 0
 *  0b0..An error on channel 0 does not generate an error interrupt
 *  0b1..An error on channel 0 generates an error interrupt request
 */
#define DMA_EEI_EEI0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI0_SHIFT)) & DMA_EEI_EEI0_MASK)

#define DMA_EEI_EEI1_MASK                        (0x2U)
#define DMA_EEI_EEI1_SHIFT                       (1U)
/*! EEI1 - Enable Error Interrupt 1
 *  0b0..An error on channel 1 does not generate an error interrupt
 *  0b1..An error on channel 1 generates an error interrupt request
 */
#define DMA_EEI_EEI1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI1_SHIFT)) & DMA_EEI_EEI1_MASK)

#define DMA_EEI_EEI2_MASK                        (0x4U)
#define DMA_EEI_EEI2_SHIFT                       (2U)
/*! EEI2 - Enable Error Interrupt 2
 *  0b0..An error on channel 2 does not generate an error interrupt
 *  0b1..An error on channel 2 generates an error interrupt request
 */
#define DMA_EEI_EEI2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI2_SHIFT)) & DMA_EEI_EEI2_MASK)

#define DMA_EEI_EEI3_MASK                        (0x8U)
#define DMA_EEI_EEI3_SHIFT                       (3U)
/*! EEI3 - Enable Error Interrupt 3
 *  0b0..An error on channel 3 does not generate an error interrupt
 *  0b1..An error on channel 3 generates an error interrupt request
 */
#define DMA_EEI_EEI3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI3_SHIFT)) & DMA_EEI_EEI3_MASK)

#define DMA_EEI_EEI4_MASK                        (0x10U)
#define DMA_EEI_EEI4_SHIFT                       (4U)
/*! EEI4 - Enable Error Interrupt 4
 *  0b0..An error on channel 4 does not generate an error interrupt
 *  0b1..An error on channel 4 generates an error interrupt request
 */
#define DMA_EEI_EEI4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI4_SHIFT)) & DMA_EEI_EEI4_MASK)

#define DMA_EEI_EEI5_MASK                        (0x20U)
#define DMA_EEI_EEI5_SHIFT                       (5U)
/*! EEI5 - Enable Error Interrupt 5
 *  0b0..An error on channel 5 does not generate an error interrupt
 *  0b1..An error on channel 5 generates an error interrupt request
 */
#define DMA_EEI_EEI5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI5_SHIFT)) & DMA_EEI_EEI5_MASK)

#define DMA_EEI_EEI6_MASK                        (0x40U)
#define DMA_EEI_EEI6_SHIFT                       (6U)
/*! EEI6 - Enable Error Interrupt 6
 *  0b0..An error on channel 6 does not generate an error interrupt
 *  0b1..An error on channel 6 generates an error interrupt request
 */
#define DMA_EEI_EEI6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI6_SHIFT)) & DMA_EEI_EEI6_MASK)

#define DMA_EEI_EEI7_MASK                        (0x80U)
#define DMA_EEI_EEI7_SHIFT                       (7U)
/*! EEI7 - Enable Error Interrupt 7
 *  0b0..An error on channel 7 does not generate an error interrupt
 *  0b1..An error on channel 7 generates an error interrupt request
 */
#define DMA_EEI_EEI7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI7_SHIFT)) & DMA_EEI_EEI7_MASK)

#define DMA_EEI_EEI8_MASK                        (0x100U)
#define DMA_EEI_EEI8_SHIFT                       (8U)
/*! EEI8 - Enable Error Interrupt 8
 *  0b0..An error on channel 8 does not generate an error interrupt
 *  0b1..An error on channel 8 generates an error interrupt request
 */
#define DMA_EEI_EEI8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI8_SHIFT)) & DMA_EEI_EEI8_MASK)

#define DMA_EEI_EEI9_MASK                        (0x200U)
#define DMA_EEI_EEI9_SHIFT                       (9U)
/*! EEI9 - Enable Error Interrupt 9
 *  0b0..An error on channel 9 does not generate an error interrupt
 *  0b1..An error on channel 9 generates an error interrupt request
 */
#define DMA_EEI_EEI9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI9_SHIFT)) & DMA_EEI_EEI9_MASK)

#define DMA_EEI_EEI10_MASK                       (0x400U)
#define DMA_EEI_EEI10_SHIFT                      (10U)
/*! EEI10 - Enable Error Interrupt 10
 *  0b0..An error on channel 10 does not generate an error interrupt
 *  0b1..An error on channel 10 generates an error interrupt request
 */
#define DMA_EEI_EEI10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI10_SHIFT)) & DMA_EEI_EEI10_MASK)

#define DMA_EEI_EEI11_MASK                       (0x800U)
#define DMA_EEI_EEI11_SHIFT                      (11U)
/*! EEI11 - Enable Error Interrupt 11
 *  0b0..An error on channel 11 does not generate an error interrupt
 *  0b1..An error on channel 11 generates an error interrupt request
 */
#define DMA_EEI_EEI11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI11_SHIFT)) & DMA_EEI_EEI11_MASK)

#define DMA_EEI_EEI12_MASK                       (0x1000U)
#define DMA_EEI_EEI12_SHIFT                      (12U)
/*! EEI12 - Enable Error Interrupt 12
 *  0b0..An error on channel 12 does not generate an error interrupt
 *  0b1..An error on channel 12 generates an error interrupt request
 */
#define DMA_EEI_EEI12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI12_SHIFT)) & DMA_EEI_EEI12_MASK)

#define DMA_EEI_EEI13_MASK                       (0x2000U)
#define DMA_EEI_EEI13_SHIFT                      (13U)
/*! EEI13 - Enable Error Interrupt 13
 *  0b0..An error on channel 13 does not generate an error interrupt
 *  0b1..An error on channel 13 generates an error interrupt request
 */
#define DMA_EEI_EEI13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI13_SHIFT)) & DMA_EEI_EEI13_MASK)

#define DMA_EEI_EEI14_MASK                       (0x4000U)
#define DMA_EEI_EEI14_SHIFT                      (14U)
/*! EEI14 - Enable Error Interrupt 14
 *  0b0..An error on channel 14 does not generate an error interrupt
 *  0b1..An error on channel 14 generates an error interrupt request
 */
#define DMA_EEI_EEI14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI14_SHIFT)) & DMA_EEI_EEI14_MASK)

#define DMA_EEI_EEI15_MASK                       (0x8000U)
#define DMA_EEI_EEI15_SHIFT                      (15U)
/*! EEI15 - Enable Error Interrupt 15
 *  0b0..An error on channel 15 does not generate an error interrupt
 *  0b1..An error on channel 15 generates an error interrupt request
 */
#define DMA_EEI_EEI15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI15_SHIFT)) & DMA_EEI_EEI15_MASK)

#define DMA_EEI_EEI16_MASK                       (0x10000U)
#define DMA_EEI_EEI16_SHIFT                      (16U)
/*! EEI16 - Enable Error Interrupt 16
 *  0b0..An error on channel 16 does not generate an error interrupt
 *  0b1..An error on channel 16 generates an error interrupt request
 */
#define DMA_EEI_EEI16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI16_SHIFT)) & DMA_EEI_EEI16_MASK)

#define DMA_EEI_EEI17_MASK                       (0x20000U)
#define DMA_EEI_EEI17_SHIFT                      (17U)
/*! EEI17 - Enable Error Interrupt 17
 *  0b0..An error on channel 17 does not generate an error interrupt
 *  0b1..An error on channel 17 generates an error interrupt request
 */
#define DMA_EEI_EEI17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI17_SHIFT)) & DMA_EEI_EEI17_MASK)

#define DMA_EEI_EEI18_MASK                       (0x40000U)
#define DMA_EEI_EEI18_SHIFT                      (18U)
/*! EEI18 - Enable Error Interrupt 18
 *  0b0..An error on channel 18 does not generate an error interrupt
 *  0b1..An error on channel 18 generates an error interrupt request
 */
#define DMA_EEI_EEI18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI18_SHIFT)) & DMA_EEI_EEI18_MASK)

#define DMA_EEI_EEI19_MASK                       (0x80000U)
#define DMA_EEI_EEI19_SHIFT                      (19U)
/*! EEI19 - Enable Error Interrupt 19
 *  0b0..An error on channel 19 does not generate an error interrupt
 *  0b1..An error on channel 19 generates an error interrupt request
 */
#define DMA_EEI_EEI19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI19_SHIFT)) & DMA_EEI_EEI19_MASK)

#define DMA_EEI_EEI20_MASK                       (0x100000U)
#define DMA_EEI_EEI20_SHIFT                      (20U)
/*! EEI20 - Enable Error Interrupt 20
 *  0b0..An error on channel 20 does not generate an error interrupt
 *  0b1..An error on channel 20 generates an error interrupt request
 */
#define DMA_EEI_EEI20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI20_SHIFT)) & DMA_EEI_EEI20_MASK)

#define DMA_EEI_EEI21_MASK                       (0x200000U)
#define DMA_EEI_EEI21_SHIFT                      (21U)
/*! EEI21 - Enable Error Interrupt 21
 *  0b0..An error on channel 21 does not generate an error interrupt
 *  0b1..An error on channel 21 generates an error interrupt request
 */
#define DMA_EEI_EEI21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI21_SHIFT)) & DMA_EEI_EEI21_MASK)

#define DMA_EEI_EEI22_MASK                       (0x400000U)
#define DMA_EEI_EEI22_SHIFT                      (22U)
/*! EEI22 - Enable Error Interrupt 22
 *  0b0..An error on channel 22 does not generate an error interrupt
 *  0b1..An error on channel 22 generates an error interrupt request
 */
#define DMA_EEI_EEI22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI22_SHIFT)) & DMA_EEI_EEI22_MASK)

#define DMA_EEI_EEI23_MASK                       (0x800000U)
#define DMA_EEI_EEI23_SHIFT                      (23U)
/*! EEI23 - Enable Error Interrupt 23
 *  0b0..An error on channel 23 does not generate an error interrupt
 *  0b1..An error on channel 23 generates an error interrupt request
 */
#define DMA_EEI_EEI23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI23_SHIFT)) & DMA_EEI_EEI23_MASK)

#define DMA_EEI_EEI24_MASK                       (0x1000000U)
#define DMA_EEI_EEI24_SHIFT                      (24U)
/*! EEI24 - Enable Error Interrupt 24
 *  0b0..An error on channel 24 does not generate an error interrupt
 *  0b1..An error on channel 24 generates an error interrupt request
 */
#define DMA_EEI_EEI24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI24_SHIFT)) & DMA_EEI_EEI24_MASK)

#define DMA_EEI_EEI25_MASK                       (0x2000000U)
#define DMA_EEI_EEI25_SHIFT                      (25U)
/*! EEI25 - Enable Error Interrupt 25
 *  0b0..An error on channel 25 does not generate an error interrupt
 *  0b1..An error on channel 25 generates an error interrupt request
 */
#define DMA_EEI_EEI25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI25_SHIFT)) & DMA_EEI_EEI25_MASK)

#define DMA_EEI_EEI26_MASK                       (0x4000000U)
#define DMA_EEI_EEI26_SHIFT                      (26U)
/*! EEI26 - Enable Error Interrupt 26
 *  0b0..An error on channel 26 does not generate an error interrupt
 *  0b1..An error on channel 26 generates an error interrupt request
 */
#define DMA_EEI_EEI26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI26_SHIFT)) & DMA_EEI_EEI26_MASK)

#define DMA_EEI_EEI27_MASK                       (0x8000000U)
#define DMA_EEI_EEI27_SHIFT                      (27U)
/*! EEI27 - Enable Error Interrupt 27
 *  0b0..An error on channel 27 does not generate an error interrupt
 *  0b1..An error on channel 27 generates an error interrupt request
 */
#define DMA_EEI_EEI27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI27_SHIFT)) & DMA_EEI_EEI27_MASK)

#define DMA_EEI_EEI28_MASK                       (0x10000000U)
#define DMA_EEI_EEI28_SHIFT                      (28U)
/*! EEI28 - Enable Error Interrupt 28
 *  0b0..An error on channel 28 does not generate an error interrupt
 *  0b1..An error on channel 28 generates an error interrupt request
 */
#define DMA_EEI_EEI28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI28_SHIFT)) & DMA_EEI_EEI28_MASK)

#define DMA_EEI_EEI29_MASK                       (0x20000000U)
#define DMA_EEI_EEI29_SHIFT                      (29U)
/*! EEI29 - Enable Error Interrupt 29
 *  0b0..An error on channel 29 does not generate an error interrupt
 *  0b1..An error on channel 29 generates an error interrupt request
 */
#define DMA_EEI_EEI29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI29_SHIFT)) & DMA_EEI_EEI29_MASK)

#define DMA_EEI_EEI30_MASK                       (0x40000000U)
#define DMA_EEI_EEI30_SHIFT                      (30U)
/*! EEI30 - Enable Error Interrupt 30
 *  0b0..An error on channel 30 does not generate an error interrupt
 *  0b1..An error on channel 30 generates an error interrupt request
 */
#define DMA_EEI_EEI30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI30_SHIFT)) & DMA_EEI_EEI30_MASK)

#define DMA_EEI_EEI31_MASK                       (0x80000000U)
#define DMA_EEI_EEI31_SHIFT                      (31U)
/*! EEI31 - Enable Error Interrupt 31
 *  0b0..An error on channel 31 does not generate an error interrupt
 *  0b1..An error on channel 31 generates an error interrupt request
 */
#define DMA_EEI_EEI31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_EEI_EEI31_SHIFT)) & DMA_EEI_EEI31_MASK)
/*! @} */

/*! @name CEEI - Clear Enable Error Interrupt */
/*! @{ */

#define DMA_CEEI_CEEI_MASK                       (0x1FU)
#define DMA_CEEI_CEEI_SHIFT                      (0U)
/*! CEEI - Clear Enable Error Interrupt */
#define DMA_CEEI_CEEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CEEI_SHIFT)) & DMA_CEEI_CEEI_MASK)

#define DMA_CEEI_CAEE_MASK                       (0x40U)
#define DMA_CEEI_CAEE_SHIFT                      (6U)
/*! CAEE - Clear All Enable Error Interrupts
 *  0b0..Write 0 only to the EEI field specified in the CEEI field
 *  0b1..Write 0 to all fields in EEI
 */
#define DMA_CEEI_CAEE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_CAEE_SHIFT)) & DMA_CEEI_CAEE_MASK)

#define DMA_CEEI_NOP_MASK                        (0x80U)
#define DMA_CEEI_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other fields in this register
 */
#define DMA_CEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CEEI_NOP_SHIFT)) & DMA_CEEI_NOP_MASK)
/*! @} */

/*! @name SEEI - Set Enable Error Interrupt */
/*! @{ */

#define DMA_SEEI_SEEI_MASK                       (0x1FU)
#define DMA_SEEI_SEEI_SHIFT                      (0U)
/*! SEEI - Set Enable Error Interrupt */
#define DMA_SEEI_SEEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SEEI_SHIFT)) & DMA_SEEI_SEEI_MASK)

#define DMA_SEEI_SAEE_MASK                       (0x40U)
#define DMA_SEEI_SAEE_SHIFT                      (6U)
/*! SAEE - Set All Enable Error Interrupts
 *  0b0..Write 1 only to the EEI field specified in the SEEI field
 *  0b1..Writes 1 to all fields in EEI
 */
#define DMA_SEEI_SAEE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_SAEE_SHIFT)) & DMA_SEEI_SAEE_MASK)

#define DMA_SEEI_NOP_MASK                        (0x80U)
#define DMA_SEEI_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other fields in this register
 */
#define DMA_SEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SEEI_NOP_SHIFT)) & DMA_SEEI_NOP_MASK)
/*! @} */

/*! @name CERQ - Clear Enable Request */
/*! @{ */

#define DMA_CERQ_CERQ_MASK                       (0x1FU)
#define DMA_CERQ_CERQ_SHIFT                      (0U)
/*! CERQ - Clear Enable Request */
#define DMA_CERQ_CERQ(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CERQ_SHIFT)) & DMA_CERQ_CERQ_MASK)

#define DMA_CERQ_CAER_MASK                       (0x40U)
#define DMA_CERQ_CAER_SHIFT                      (6U)
/*! CAER - Clear All Enable Requests
 *  0b0..Write 0 to only the ERQ field specified in the CERQ field
 *  0b1..Write 0 to all fields in ERQ
 */
#define DMA_CERQ_CAER(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_CAER_SHIFT)) & DMA_CERQ_CAER_MASK)

#define DMA_CERQ_NOP_MASK                        (0x80U)
#define DMA_CERQ_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other fields in this register
 */
#define DMA_CERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CERQ_NOP_SHIFT)) & DMA_CERQ_NOP_MASK)
/*! @} */

/*! @name SERQ - Set Enable Request */
/*! @{ */

#define DMA_SERQ_SERQ_MASK                       (0x1FU)
#define DMA_SERQ_SERQ_SHIFT                      (0U)
/*! SERQ - Set Enable Request */
#define DMA_SERQ_SERQ(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SERQ_SHIFT)) & DMA_SERQ_SERQ_MASK)

#define DMA_SERQ_SAER_MASK                       (0x40U)
#define DMA_SERQ_SAER_SHIFT                      (6U)
/*! SAER - Set All Enable Requests
 *  0b0..Write 1 to only the ERQ field specified in the SERQ field
 *  0b1..Write 1 to all fields in ERQ
 */
#define DMA_SERQ_SAER(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_SAER_SHIFT)) & DMA_SERQ_SAER_MASK)

#define DMA_SERQ_NOP_MASK                        (0x80U)
#define DMA_SERQ_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation, ignore the other fields in this register
 */
#define DMA_SERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SERQ_NOP_SHIFT)) & DMA_SERQ_NOP_MASK)
/*! @} */

/*! @name CDNE - Clear DONE Status Bit */
/*! @{ */

#define DMA_CDNE_CDNE_MASK                       (0x1FU)
#define DMA_CDNE_CDNE_SHIFT                      (0U)
/*! CDNE - Clear DONE field */
#define DMA_CDNE_CDNE(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CDNE_SHIFT)) & DMA_CDNE_CDNE_MASK)

#define DMA_CDNE_CADN_MASK                       (0x40U)
#define DMA_CDNE_CADN_SHIFT                      (6U)
/*! CADN - Clears All DONE fields
 *  0b0..Writes 0 to only the TCDn_CSR[DONE] field specified in the CDNE field
 *  0b1..Writes 0 to all bits in TCDn_CSR[DONE]
 */
#define DMA_CDNE_CADN(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_CADN_SHIFT)) & DMA_CDNE_CADN_MASK)

#define DMA_CDNE_NOP_MASK                        (0x80U)
#define DMA_CDNE_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation; all other fields in this register are ignored.
 */
#define DMA_CDNE_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CDNE_NOP_SHIFT)) & DMA_CDNE_NOP_MASK)
/*! @} */

/*! @name SSRT - Set START Bit */
/*! @{ */

#define DMA_SSRT_SSRT_MASK                       (0x1FU)
#define DMA_SSRT_SSRT_SHIFT                      (0U)
/*! SSRT - Set START field */
#define DMA_SSRT_SSRT(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SSRT_SHIFT)) & DMA_SSRT_SSRT_MASK)

#define DMA_SSRT_SAST_MASK                       (0x40U)
#define DMA_SSRT_SAST_SHIFT                      (6U)
/*! SAST - Set All START fields (activates all channels)
 *  0b0..Write 1 to only the TCDn_CSR[START] field specified in the SSRT field
 *  0b1..Write 1 to all bits in TCDn_CSR[START]
 */
#define DMA_SSRT_SAST(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_SAST_SHIFT)) & DMA_SSRT_SAST_MASK)

#define DMA_SSRT_NOP_MASK                        (0x80U)
#define DMA_SSRT_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation; all other fields in this register are ignored.
 */
#define DMA_SSRT_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_SSRT_NOP_SHIFT)) & DMA_SSRT_NOP_MASK)
/*! @} */

/*! @name CERR - Clear Error */
/*! @{ */

#define DMA_CERR_CERR_MASK                       (0x1FU)
#define DMA_CERR_CERR_SHIFT                      (0U)
/*! CERR - Clear Error Indicator */
#define DMA_CERR_CERR(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CERR_SHIFT)) & DMA_CERR_CERR_MASK)

#define DMA_CERR_CAEI_MASK                       (0x40U)
#define DMA_CERR_CAEI_SHIFT                      (6U)
/*! CAEI - Clear All Error Indicators
 *  0b0..Write 0 to only the ERR field specified in the CERR field
 *  0b1..Write 0 to all fields in ERR
 */
#define DMA_CERR_CAEI(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CERR_CAEI_SHIFT)) & DMA_CERR_CAEI_MASK)

#define DMA_CERR_NOP_MASK                        (0x80U)
#define DMA_CERR_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation; all other fields in this register are ignored.
 */
#define DMA_CERR_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CERR_NOP_SHIFT)) & DMA_CERR_NOP_MASK)
/*! @} */

/*! @name CINT - Clear Interrupt Request */
/*! @{ */

#define DMA_CINT_CINT_MASK                       (0x1FU)
#define DMA_CINT_CINT_SHIFT                      (0U)
/*! CINT - Clear Interrupt Request */
#define DMA_CINT_CINT(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CINT_SHIFT)) & DMA_CINT_CINT_MASK)

#define DMA_CINT_CAIR_MASK                       (0x40U)
#define DMA_CINT_CAIR_SHIFT                      (6U)
/*! CAIR - Clear All Interrupt Requests
 *  0b0..Clear only the INT field specified in the CINT field
 *  0b1..Clear all bits in INT
 */
#define DMA_CINT_CAIR(x)                         (((uint8_t)(((uint8_t)(x)) << DMA_CINT_CAIR_SHIFT)) & DMA_CINT_CAIR_MASK)

#define DMA_CINT_NOP_MASK                        (0x80U)
#define DMA_CINT_NOP_SHIFT                       (7U)
/*! NOP - No Op Enable
 *  0b0..Normal operation
 *  0b1..No operation; all other fields in this register are ignored.
 */
#define DMA_CINT_NOP(x)                          (((uint8_t)(((uint8_t)(x)) << DMA_CINT_NOP_SHIFT)) & DMA_CINT_NOP_MASK)
/*! @} */

/*! @name INT - Interrupt Request */
/*! @{ */

#define DMA_INT_INT0_MASK                        (0x1U)
#define DMA_INT_INT0_SHIFT                       (0U)
/*! INT0 - Interrupt Request 0
 *  0b0..The interrupt request for channel 0 is cleared
 *  0b1..The interrupt request for channel 0 is active
 */
#define DMA_INT_INT0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT0_SHIFT)) & DMA_INT_INT0_MASK)

#define DMA_INT_INT1_MASK                        (0x2U)
#define DMA_INT_INT1_SHIFT                       (1U)
/*! INT1 - Interrupt Request 1
 *  0b0..The interrupt request for channel 1 is cleared
 *  0b1..The interrupt request for channel 1 is active
 */
#define DMA_INT_INT1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT1_SHIFT)) & DMA_INT_INT1_MASK)

#define DMA_INT_INT2_MASK                        (0x4U)
#define DMA_INT_INT2_SHIFT                       (2U)
/*! INT2 - Interrupt Request 2
 *  0b0..The interrupt request for channel 2 is cleared
 *  0b1..The interrupt request for channel 2 is active
 */
#define DMA_INT_INT2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT2_SHIFT)) & DMA_INT_INT2_MASK)

#define DMA_INT_INT3_MASK                        (0x8U)
#define DMA_INT_INT3_SHIFT                       (3U)
/*! INT3 - Interrupt Request 3
 *  0b0..The interrupt request for channel 3 is cleared
 *  0b1..The interrupt request for channel 3 is active
 */
#define DMA_INT_INT3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT3_SHIFT)) & DMA_INT_INT3_MASK)

#define DMA_INT_INT4_MASK                        (0x10U)
#define DMA_INT_INT4_SHIFT                       (4U)
/*! INT4 - Interrupt Request 4
 *  0b0..The interrupt request for channel 4 is cleared
 *  0b1..The interrupt request for channel 4 is active
 */
#define DMA_INT_INT4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT4_SHIFT)) & DMA_INT_INT4_MASK)

#define DMA_INT_INT5_MASK                        (0x20U)
#define DMA_INT_INT5_SHIFT                       (5U)
/*! INT5 - Interrupt Request 5
 *  0b0..The interrupt request for channel 5 is cleared
 *  0b1..The interrupt request for channel 5 is active
 */
#define DMA_INT_INT5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT5_SHIFT)) & DMA_INT_INT5_MASK)

#define DMA_INT_INT6_MASK                        (0x40U)
#define DMA_INT_INT6_SHIFT                       (6U)
/*! INT6 - Interrupt Request 6
 *  0b0..The interrupt request for channel 6 is cleared
 *  0b1..The interrupt request for channel 6 is active
 */
#define DMA_INT_INT6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT6_SHIFT)) & DMA_INT_INT6_MASK)

#define DMA_INT_INT7_MASK                        (0x80U)
#define DMA_INT_INT7_SHIFT                       (7U)
/*! INT7 - Interrupt Request 7
 *  0b0..The interrupt request for channel 7 is cleared
 *  0b1..The interrupt request for channel 7 is active
 */
#define DMA_INT_INT7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT7_SHIFT)) & DMA_INT_INT7_MASK)

#define DMA_INT_INT8_MASK                        (0x100U)
#define DMA_INT_INT8_SHIFT                       (8U)
/*! INT8 - Interrupt Request 8
 *  0b0..The interrupt request for channel 8 is cleared
 *  0b1..The interrupt request for channel 8 is active
 */
#define DMA_INT_INT8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT8_SHIFT)) & DMA_INT_INT8_MASK)

#define DMA_INT_INT9_MASK                        (0x200U)
#define DMA_INT_INT9_SHIFT                       (9U)
/*! INT9 - Interrupt Request 9
 *  0b0..The interrupt request for channel 9 is cleared
 *  0b1..The interrupt request for channel 9 is active
 */
#define DMA_INT_INT9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT9_SHIFT)) & DMA_INT_INT9_MASK)

#define DMA_INT_INT10_MASK                       (0x400U)
#define DMA_INT_INT10_SHIFT                      (10U)
/*! INT10 - Interrupt Request 10
 *  0b0..The interrupt request for channel 10 is cleared
 *  0b1..The interrupt request for channel 10 is active
 */
#define DMA_INT_INT10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT10_SHIFT)) & DMA_INT_INT10_MASK)

#define DMA_INT_INT11_MASK                       (0x800U)
#define DMA_INT_INT11_SHIFT                      (11U)
/*! INT11 - Interrupt Request 11
 *  0b0..The interrupt request for channel 11 is cleared
 *  0b1..The interrupt request for channel 11 is active
 */
#define DMA_INT_INT11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT11_SHIFT)) & DMA_INT_INT11_MASK)

#define DMA_INT_INT12_MASK                       (0x1000U)
#define DMA_INT_INT12_SHIFT                      (12U)
/*! INT12 - Interrupt Request 12
 *  0b0..The interrupt request for channel 12 is cleared
 *  0b1..The interrupt request for channel 12 is active
 */
#define DMA_INT_INT12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT12_SHIFT)) & DMA_INT_INT12_MASK)

#define DMA_INT_INT13_MASK                       (0x2000U)
#define DMA_INT_INT13_SHIFT                      (13U)
/*! INT13 - Interrupt Request 13
 *  0b0..The interrupt request for channel 13 is cleared
 *  0b1..The interrupt request for channel 13 is active
 */
#define DMA_INT_INT13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT13_SHIFT)) & DMA_INT_INT13_MASK)

#define DMA_INT_INT14_MASK                       (0x4000U)
#define DMA_INT_INT14_SHIFT                      (14U)
/*! INT14 - Interrupt Request 14
 *  0b0..The interrupt request for channel 14 is cleared
 *  0b1..The interrupt request for channel 14 is active
 */
#define DMA_INT_INT14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT14_SHIFT)) & DMA_INT_INT14_MASK)

#define DMA_INT_INT15_MASK                       (0x8000U)
#define DMA_INT_INT15_SHIFT                      (15U)
/*! INT15 - Interrupt Request 15
 *  0b0..The interrupt request for channel 15 is cleared
 *  0b1..The interrupt request for channel 15 is active
 */
#define DMA_INT_INT15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT15_SHIFT)) & DMA_INT_INT15_MASK)

#define DMA_INT_INT16_MASK                       (0x10000U)
#define DMA_INT_INT16_SHIFT                      (16U)
/*! INT16 - Interrupt Request 16
 *  0b0..The interrupt request for channel 16 is cleared
 *  0b1..The interrupt request for channel 16 is active
 */
#define DMA_INT_INT16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT16_SHIFT)) & DMA_INT_INT16_MASK)

#define DMA_INT_INT17_MASK                       (0x20000U)
#define DMA_INT_INT17_SHIFT                      (17U)
/*! INT17 - Interrupt Request 17
 *  0b0..The interrupt request for channel 17 is cleared
 *  0b1..The interrupt request for channel 17 is active
 */
#define DMA_INT_INT17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT17_SHIFT)) & DMA_INT_INT17_MASK)

#define DMA_INT_INT18_MASK                       (0x40000U)
#define DMA_INT_INT18_SHIFT                      (18U)
/*! INT18 - Interrupt Request 18
 *  0b0..The interrupt request for channel 18 is cleared
 *  0b1..The interrupt request for channel 18 is active
 */
#define DMA_INT_INT18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT18_SHIFT)) & DMA_INT_INT18_MASK)

#define DMA_INT_INT19_MASK                       (0x80000U)
#define DMA_INT_INT19_SHIFT                      (19U)
/*! INT19 - Interrupt Request 19
 *  0b0..The interrupt request for channel 19 is cleared
 *  0b1..The interrupt request for channel 19 is active
 */
#define DMA_INT_INT19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT19_SHIFT)) & DMA_INT_INT19_MASK)

#define DMA_INT_INT20_MASK                       (0x100000U)
#define DMA_INT_INT20_SHIFT                      (20U)
/*! INT20 - Interrupt Request 20
 *  0b0..The interrupt request for channel 20 is cleared
 *  0b1..The interrupt request for channel 20 is active
 */
#define DMA_INT_INT20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT20_SHIFT)) & DMA_INT_INT20_MASK)

#define DMA_INT_INT21_MASK                       (0x200000U)
#define DMA_INT_INT21_SHIFT                      (21U)
/*! INT21 - Interrupt Request 21
 *  0b0..The interrupt request for channel 21 is cleared
 *  0b1..The interrupt request for channel 21 is active
 */
#define DMA_INT_INT21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT21_SHIFT)) & DMA_INT_INT21_MASK)

#define DMA_INT_INT22_MASK                       (0x400000U)
#define DMA_INT_INT22_SHIFT                      (22U)
/*! INT22 - Interrupt Request 22
 *  0b0..The interrupt request for channel 22 is cleared
 *  0b1..The interrupt request for channel 22 is active
 */
#define DMA_INT_INT22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT22_SHIFT)) & DMA_INT_INT22_MASK)

#define DMA_INT_INT23_MASK                       (0x800000U)
#define DMA_INT_INT23_SHIFT                      (23U)
/*! INT23 - Interrupt Request 23
 *  0b0..The interrupt request for channel 23 is cleared
 *  0b1..The interrupt request for channel 23 is active
 */
#define DMA_INT_INT23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT23_SHIFT)) & DMA_INT_INT23_MASK)

#define DMA_INT_INT24_MASK                       (0x1000000U)
#define DMA_INT_INT24_SHIFT                      (24U)
/*! INT24 - Interrupt Request 24
 *  0b0..The interrupt request for channel 24 is cleared
 *  0b1..The interrupt request for channel 24 is active
 */
#define DMA_INT_INT24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT24_SHIFT)) & DMA_INT_INT24_MASK)

#define DMA_INT_INT25_MASK                       (0x2000000U)
#define DMA_INT_INT25_SHIFT                      (25U)
/*! INT25 - Interrupt Request 25
 *  0b0..The interrupt request for channel 25 is cleared
 *  0b1..The interrupt request for channel 25 is active
 */
#define DMA_INT_INT25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT25_SHIFT)) & DMA_INT_INT25_MASK)

#define DMA_INT_INT26_MASK                       (0x4000000U)
#define DMA_INT_INT26_SHIFT                      (26U)
/*! INT26 - Interrupt Request 26
 *  0b0..The interrupt request for channel 26 is cleared
 *  0b1..The interrupt request for channel 26 is active
 */
#define DMA_INT_INT26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT26_SHIFT)) & DMA_INT_INT26_MASK)

#define DMA_INT_INT27_MASK                       (0x8000000U)
#define DMA_INT_INT27_SHIFT                      (27U)
/*! INT27 - Interrupt Request 27
 *  0b0..The interrupt request for channel 27 is cleared
 *  0b1..The interrupt request for channel 27 is active
 */
#define DMA_INT_INT27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT27_SHIFT)) & DMA_INT_INT27_MASK)

#define DMA_INT_INT28_MASK                       (0x10000000U)
#define DMA_INT_INT28_SHIFT                      (28U)
/*! INT28 - Interrupt Request 28
 *  0b0..The interrupt request for channel 28 is cleared
 *  0b1..The interrupt request for channel 28 is active
 */
#define DMA_INT_INT28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT28_SHIFT)) & DMA_INT_INT28_MASK)

#define DMA_INT_INT29_MASK                       (0x20000000U)
#define DMA_INT_INT29_SHIFT                      (29U)
/*! INT29 - Interrupt Request 29
 *  0b0..The interrupt request for channel 29 is cleared
 *  0b1..The interrupt request for channel 29 is active
 */
#define DMA_INT_INT29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT29_SHIFT)) & DMA_INT_INT29_MASK)

#define DMA_INT_INT30_MASK                       (0x40000000U)
#define DMA_INT_INT30_SHIFT                      (30U)
/*! INT30 - Interrupt Request 30
 *  0b0..The interrupt request for channel 30 is cleared
 *  0b1..The interrupt request for channel 30 is active
 */
#define DMA_INT_INT30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT30_SHIFT)) & DMA_INT_INT30_MASK)

#define DMA_INT_INT31_MASK                       (0x80000000U)
#define DMA_INT_INT31_SHIFT                      (31U)
/*! INT31 - Interrupt Request 31
 *  0b0..The interrupt request for channel 31 is cleared
 *  0b1..The interrupt request for channel 31 is active
 */
#define DMA_INT_INT31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_INT_INT31_SHIFT)) & DMA_INT_INT31_MASK)
/*! @} */

/*! @name ERR - Error */
/*! @{ */

#define DMA_ERR_ERR0_MASK                        (0x1U)
#define DMA_ERR_ERR0_SHIFT                       (0U)
/*! ERR0 - Error In Channel 0
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR0_SHIFT)) & DMA_ERR_ERR0_MASK)

#define DMA_ERR_ERR1_MASK                        (0x2U)
#define DMA_ERR_ERR1_SHIFT                       (1U)
/*! ERR1 - Error In Channel 1
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR1_SHIFT)) & DMA_ERR_ERR1_MASK)

#define DMA_ERR_ERR2_MASK                        (0x4U)
#define DMA_ERR_ERR2_SHIFT                       (2U)
/*! ERR2 - Error In Channel 2
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR2_SHIFT)) & DMA_ERR_ERR2_MASK)

#define DMA_ERR_ERR3_MASK                        (0x8U)
#define DMA_ERR_ERR3_SHIFT                       (3U)
/*! ERR3 - Error In Channel 3
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR3_SHIFT)) & DMA_ERR_ERR3_MASK)

#define DMA_ERR_ERR4_MASK                        (0x10U)
#define DMA_ERR_ERR4_SHIFT                       (4U)
/*! ERR4 - Error In Channel 4
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR4_SHIFT)) & DMA_ERR_ERR4_MASK)

#define DMA_ERR_ERR5_MASK                        (0x20U)
#define DMA_ERR_ERR5_SHIFT                       (5U)
/*! ERR5 - Error In Channel 5
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR5_SHIFT)) & DMA_ERR_ERR5_MASK)

#define DMA_ERR_ERR6_MASK                        (0x40U)
#define DMA_ERR_ERR6_SHIFT                       (6U)
/*! ERR6 - Error In Channel 6
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR6_SHIFT)) & DMA_ERR_ERR6_MASK)

#define DMA_ERR_ERR7_MASK                        (0x80U)
#define DMA_ERR_ERR7_SHIFT                       (7U)
/*! ERR7 - Error In Channel 7
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR7_SHIFT)) & DMA_ERR_ERR7_MASK)

#define DMA_ERR_ERR8_MASK                        (0x100U)
#define DMA_ERR_ERR8_SHIFT                       (8U)
/*! ERR8 - Error In Channel 8
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR8_SHIFT)) & DMA_ERR_ERR8_MASK)

#define DMA_ERR_ERR9_MASK                        (0x200U)
#define DMA_ERR_ERR9_SHIFT                       (9U)
/*! ERR9 - Error In Channel 9
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR9_SHIFT)) & DMA_ERR_ERR9_MASK)

#define DMA_ERR_ERR10_MASK                       (0x400U)
#define DMA_ERR_ERR10_SHIFT                      (10U)
/*! ERR10 - Error In Channel 10
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR10_SHIFT)) & DMA_ERR_ERR10_MASK)

#define DMA_ERR_ERR11_MASK                       (0x800U)
#define DMA_ERR_ERR11_SHIFT                      (11U)
/*! ERR11 - Error In Channel 11
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR11_SHIFT)) & DMA_ERR_ERR11_MASK)

#define DMA_ERR_ERR12_MASK                       (0x1000U)
#define DMA_ERR_ERR12_SHIFT                      (12U)
/*! ERR12 - Error In Channel 12
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR12_SHIFT)) & DMA_ERR_ERR12_MASK)

#define DMA_ERR_ERR13_MASK                       (0x2000U)
#define DMA_ERR_ERR13_SHIFT                      (13U)
/*! ERR13 - Error In Channel 13
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR13_SHIFT)) & DMA_ERR_ERR13_MASK)

#define DMA_ERR_ERR14_MASK                       (0x4000U)
#define DMA_ERR_ERR14_SHIFT                      (14U)
/*! ERR14 - Error In Channel 14
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR14_SHIFT)) & DMA_ERR_ERR14_MASK)

#define DMA_ERR_ERR15_MASK                       (0x8000U)
#define DMA_ERR_ERR15_SHIFT                      (15U)
/*! ERR15 - Error In Channel 15
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR15_SHIFT)) & DMA_ERR_ERR15_MASK)

#define DMA_ERR_ERR16_MASK                       (0x10000U)
#define DMA_ERR_ERR16_SHIFT                      (16U)
/*! ERR16 - Error In Channel 16
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR16_SHIFT)) & DMA_ERR_ERR16_MASK)

#define DMA_ERR_ERR17_MASK                       (0x20000U)
#define DMA_ERR_ERR17_SHIFT                      (17U)
/*! ERR17 - Error In Channel 17
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR17_SHIFT)) & DMA_ERR_ERR17_MASK)

#define DMA_ERR_ERR18_MASK                       (0x40000U)
#define DMA_ERR_ERR18_SHIFT                      (18U)
/*! ERR18 - Error In Channel 18
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR18_SHIFT)) & DMA_ERR_ERR18_MASK)

#define DMA_ERR_ERR19_MASK                       (0x80000U)
#define DMA_ERR_ERR19_SHIFT                      (19U)
/*! ERR19 - Error In Channel 19
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR19_SHIFT)) & DMA_ERR_ERR19_MASK)

#define DMA_ERR_ERR20_MASK                       (0x100000U)
#define DMA_ERR_ERR20_SHIFT                      (20U)
/*! ERR20 - Error In Channel 20
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR20_SHIFT)) & DMA_ERR_ERR20_MASK)

#define DMA_ERR_ERR21_MASK                       (0x200000U)
#define DMA_ERR_ERR21_SHIFT                      (21U)
/*! ERR21 - Error In Channel 21
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR21_SHIFT)) & DMA_ERR_ERR21_MASK)

#define DMA_ERR_ERR22_MASK                       (0x400000U)
#define DMA_ERR_ERR22_SHIFT                      (22U)
/*! ERR22 - Error In Channel 22
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR22_SHIFT)) & DMA_ERR_ERR22_MASK)

#define DMA_ERR_ERR23_MASK                       (0x800000U)
#define DMA_ERR_ERR23_SHIFT                      (23U)
/*! ERR23 - Error In Channel 23
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR23_SHIFT)) & DMA_ERR_ERR23_MASK)

#define DMA_ERR_ERR24_MASK                       (0x1000000U)
#define DMA_ERR_ERR24_SHIFT                      (24U)
/*! ERR24 - Error In Channel 24
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR24_SHIFT)) & DMA_ERR_ERR24_MASK)

#define DMA_ERR_ERR25_MASK                       (0x2000000U)
#define DMA_ERR_ERR25_SHIFT                      (25U)
/*! ERR25 - Error In Channel 25
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR25_SHIFT)) & DMA_ERR_ERR25_MASK)

#define DMA_ERR_ERR26_MASK                       (0x4000000U)
#define DMA_ERR_ERR26_SHIFT                      (26U)
/*! ERR26 - Error In Channel 26
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR26_SHIFT)) & DMA_ERR_ERR26_MASK)

#define DMA_ERR_ERR27_MASK                       (0x8000000U)
#define DMA_ERR_ERR27_SHIFT                      (27U)
/*! ERR27 - Error In Channel 27
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR27_SHIFT)) & DMA_ERR_ERR27_MASK)

#define DMA_ERR_ERR28_MASK                       (0x10000000U)
#define DMA_ERR_ERR28_SHIFT                      (28U)
/*! ERR28 - Error In Channel 28
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR28_SHIFT)) & DMA_ERR_ERR28_MASK)

#define DMA_ERR_ERR29_MASK                       (0x20000000U)
#define DMA_ERR_ERR29_SHIFT                      (29U)
/*! ERR29 - Error In Channel 29
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR29_SHIFT)) & DMA_ERR_ERR29_MASK)

#define DMA_ERR_ERR30_MASK                       (0x40000000U)
#define DMA_ERR_ERR30_SHIFT                      (30U)
/*! ERR30 - Error In Channel 30
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR30_SHIFT)) & DMA_ERR_ERR30_MASK)

#define DMA_ERR_ERR31_MASK                       (0x80000000U)
#define DMA_ERR_ERR31_SHIFT                      (31U)
/*! ERR31 - Error In Channel 31
 *  0b0..No error in this channel has occurred
 *  0b1..An error in this channel has occurred
 */
#define DMA_ERR_ERR31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ERR_ERR31_SHIFT)) & DMA_ERR_ERR31_MASK)
/*! @} */

/*! @name HRS - Hardware Request Status */
/*! @{ */

#define DMA_HRS_HRS0_MASK                        (0x1U)
#define DMA_HRS_HRS0_SHIFT                       (0U)
/*! HRS0 - Hardware Request Status Channel 0
 *  0b0..A hardware service request for channel 0 is not present
 *  0b1..A hardware service request for channel 0 is present
 */
#define DMA_HRS_HRS0(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS0_SHIFT)) & DMA_HRS_HRS0_MASK)

#define DMA_HRS_HRS1_MASK                        (0x2U)
#define DMA_HRS_HRS1_SHIFT                       (1U)
/*! HRS1 - Hardware Request Status Channel 1
 *  0b0..A hardware service request for channel 1 is not present
 *  0b1..A hardware service request for channel 1 is present
 */
#define DMA_HRS_HRS1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS1_SHIFT)) & DMA_HRS_HRS1_MASK)

#define DMA_HRS_HRS2_MASK                        (0x4U)
#define DMA_HRS_HRS2_SHIFT                       (2U)
/*! HRS2 - Hardware Request Status Channel 2
 *  0b0..A hardware service request for channel 2 is not present
 *  0b1..A hardware service request for channel 2 is present
 */
#define DMA_HRS_HRS2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS2_SHIFT)) & DMA_HRS_HRS2_MASK)

#define DMA_HRS_HRS3_MASK                        (0x8U)
#define DMA_HRS_HRS3_SHIFT                       (3U)
/*! HRS3 - Hardware Request Status Channel 3
 *  0b0..A hardware service request for channel 3 is not present
 *  0b1..A hardware service request for channel 3 is present
 */
#define DMA_HRS_HRS3(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS3_SHIFT)) & DMA_HRS_HRS3_MASK)

#define DMA_HRS_HRS4_MASK                        (0x10U)
#define DMA_HRS_HRS4_SHIFT                       (4U)
/*! HRS4 - Hardware Request Status Channel 4
 *  0b0..A hardware service request for channel 4 is not present
 *  0b1..A hardware service request for channel 4 is present
 */
#define DMA_HRS_HRS4(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS4_SHIFT)) & DMA_HRS_HRS4_MASK)

#define DMA_HRS_HRS5_MASK                        (0x20U)
#define DMA_HRS_HRS5_SHIFT                       (5U)
/*! HRS5 - Hardware Request Status Channel 5
 *  0b0..A hardware service request for channel 5 is not present
 *  0b1..A hardware service request for channel 5 is present
 */
#define DMA_HRS_HRS5(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS5_SHIFT)) & DMA_HRS_HRS5_MASK)

#define DMA_HRS_HRS6_MASK                        (0x40U)
#define DMA_HRS_HRS6_SHIFT                       (6U)
/*! HRS6 - Hardware Request Status Channel 6
 *  0b0..A hardware service request for channel 6 is not present
 *  0b1..A hardware service request for channel 6 is present
 */
#define DMA_HRS_HRS6(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS6_SHIFT)) & DMA_HRS_HRS6_MASK)

#define DMA_HRS_HRS7_MASK                        (0x80U)
#define DMA_HRS_HRS7_SHIFT                       (7U)
/*! HRS7 - Hardware Request Status Channel 7
 *  0b0..A hardware service request for channel 7 is not present
 *  0b1..A hardware service request for channel 7 is present
 */
#define DMA_HRS_HRS7(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS7_SHIFT)) & DMA_HRS_HRS7_MASK)

#define DMA_HRS_HRS8_MASK                        (0x100U)
#define DMA_HRS_HRS8_SHIFT                       (8U)
/*! HRS8 - Hardware Request Status Channel 8
 *  0b0..A hardware service request for channel 8 is not present
 *  0b1..A hardware service request for channel 8 is present
 */
#define DMA_HRS_HRS8(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS8_SHIFT)) & DMA_HRS_HRS8_MASK)

#define DMA_HRS_HRS9_MASK                        (0x200U)
#define DMA_HRS_HRS9_SHIFT                       (9U)
/*! HRS9 - Hardware Request Status Channel 9
 *  0b0..A hardware service request for channel 9 is not present
 *  0b1..A hardware service request for channel 9 is present
 */
#define DMA_HRS_HRS9(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS9_SHIFT)) & DMA_HRS_HRS9_MASK)

#define DMA_HRS_HRS10_MASK                       (0x400U)
#define DMA_HRS_HRS10_SHIFT                      (10U)
/*! HRS10 - Hardware Request Status Channel 10
 *  0b0..A hardware service request for channel 10 is not present
 *  0b1..A hardware service request for channel 10 is present
 */
#define DMA_HRS_HRS10(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS10_SHIFT)) & DMA_HRS_HRS10_MASK)

#define DMA_HRS_HRS11_MASK                       (0x800U)
#define DMA_HRS_HRS11_SHIFT                      (11U)
/*! HRS11 - Hardware Request Status Channel 11
 *  0b0..A hardware service request for channel 11 is not present
 *  0b1..A hardware service request for channel 11 is present
 */
#define DMA_HRS_HRS11(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS11_SHIFT)) & DMA_HRS_HRS11_MASK)

#define DMA_HRS_HRS12_MASK                       (0x1000U)
#define DMA_HRS_HRS12_SHIFT                      (12U)
/*! HRS12 - Hardware Request Status Channel 12
 *  0b0..A hardware service request for channel 12 is not present
 *  0b1..A hardware service request for channel 12 is present
 */
#define DMA_HRS_HRS12(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS12_SHIFT)) & DMA_HRS_HRS12_MASK)

#define DMA_HRS_HRS13_MASK                       (0x2000U)
#define DMA_HRS_HRS13_SHIFT                      (13U)
/*! HRS13 - Hardware Request Status Channel 13
 *  0b0..A hardware service request for channel 13 is not present
 *  0b1..A hardware service request for channel 13 is present
 */
#define DMA_HRS_HRS13(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS13_SHIFT)) & DMA_HRS_HRS13_MASK)

#define DMA_HRS_HRS14_MASK                       (0x4000U)
#define DMA_HRS_HRS14_SHIFT                      (14U)
/*! HRS14 - Hardware Request Status Channel 14
 *  0b0..A hardware service request for channel 14 is not present
 *  0b1..A hardware service request for channel 14 is present
 */
#define DMA_HRS_HRS14(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS14_SHIFT)) & DMA_HRS_HRS14_MASK)

#define DMA_HRS_HRS15_MASK                       (0x8000U)
#define DMA_HRS_HRS15_SHIFT                      (15U)
/*! HRS15 - Hardware Request Status Channel 15
 *  0b0..A hardware service request for channel 15 is not present
 *  0b1..A hardware service request for channel 15 is present
 */
#define DMA_HRS_HRS15(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS15_SHIFT)) & DMA_HRS_HRS15_MASK)

#define DMA_HRS_HRS16_MASK                       (0x10000U)
#define DMA_HRS_HRS16_SHIFT                      (16U)
/*! HRS16 - Hardware Request Status Channel 16
 *  0b0..A hardware service request for channel 16 is not present
 *  0b1..A hardware service request for channel 16 is present
 */
#define DMA_HRS_HRS16(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS16_SHIFT)) & DMA_HRS_HRS16_MASK)

#define DMA_HRS_HRS17_MASK                       (0x20000U)
#define DMA_HRS_HRS17_SHIFT                      (17U)
/*! HRS17 - Hardware Request Status Channel 17
 *  0b0..A hardware service request for channel 17 is not present
 *  0b1..A hardware service request for channel 17 is present
 */
#define DMA_HRS_HRS17(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS17_SHIFT)) & DMA_HRS_HRS17_MASK)

#define DMA_HRS_HRS18_MASK                       (0x40000U)
#define DMA_HRS_HRS18_SHIFT                      (18U)
/*! HRS18 - Hardware Request Status Channel 18
 *  0b0..A hardware service request for channel 18 is not present
 *  0b1..A hardware service request for channel 18 is present
 */
#define DMA_HRS_HRS18(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS18_SHIFT)) & DMA_HRS_HRS18_MASK)

#define DMA_HRS_HRS19_MASK                       (0x80000U)
#define DMA_HRS_HRS19_SHIFT                      (19U)
/*! HRS19 - Hardware Request Status Channel 19
 *  0b0..A hardware service request for channel 19 is not present
 *  0b1..A hardware service request for channel 19 is present
 */
#define DMA_HRS_HRS19(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS19_SHIFT)) & DMA_HRS_HRS19_MASK)

#define DMA_HRS_HRS20_MASK                       (0x100000U)
#define DMA_HRS_HRS20_SHIFT                      (20U)
/*! HRS20 - Hardware Request Status Channel 20
 *  0b0..A hardware service request for channel 20 is not present
 *  0b1..A hardware service request for channel 20 is present
 */
#define DMA_HRS_HRS20(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS20_SHIFT)) & DMA_HRS_HRS20_MASK)

#define DMA_HRS_HRS21_MASK                       (0x200000U)
#define DMA_HRS_HRS21_SHIFT                      (21U)
/*! HRS21 - Hardware Request Status Channel 21
 *  0b0..A hardware service request for channel 21 is not present
 *  0b1..A hardware service request for channel 21 is present
 */
#define DMA_HRS_HRS21(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS21_SHIFT)) & DMA_HRS_HRS21_MASK)

#define DMA_HRS_HRS22_MASK                       (0x400000U)
#define DMA_HRS_HRS22_SHIFT                      (22U)
/*! HRS22 - Hardware Request Status Channel 22
 *  0b0..A hardware service request for channel 22 is not present
 *  0b1..A hardware service request for channel 22 is present
 */
#define DMA_HRS_HRS22(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS22_SHIFT)) & DMA_HRS_HRS22_MASK)

#define DMA_HRS_HRS23_MASK                       (0x800000U)
#define DMA_HRS_HRS23_SHIFT                      (23U)
/*! HRS23 - Hardware Request Status Channel 23
 *  0b0..A hardware service request for channel 23 is not present
 *  0b1..A hardware service request for channel 23 is present
 */
#define DMA_HRS_HRS23(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS23_SHIFT)) & DMA_HRS_HRS23_MASK)

#define DMA_HRS_HRS24_MASK                       (0x1000000U)
#define DMA_HRS_HRS24_SHIFT                      (24U)
/*! HRS24 - Hardware Request Status Channel 24
 *  0b0..A hardware service request for channel 24 is not present
 *  0b1..A hardware service request for channel 24 is present
 */
#define DMA_HRS_HRS24(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS24_SHIFT)) & DMA_HRS_HRS24_MASK)

#define DMA_HRS_HRS25_MASK                       (0x2000000U)
#define DMA_HRS_HRS25_SHIFT                      (25U)
/*! HRS25 - Hardware Request Status Channel 25
 *  0b0..A hardware service request for channel 25 is not present
 *  0b1..A hardware service request for channel 25 is present
 */
#define DMA_HRS_HRS25(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS25_SHIFT)) & DMA_HRS_HRS25_MASK)

#define DMA_HRS_HRS26_MASK                       (0x4000000U)
#define DMA_HRS_HRS26_SHIFT                      (26U)
/*! HRS26 - Hardware Request Status Channel 26
 *  0b0..A hardware service request for channel 26 is not present
 *  0b1..A hardware service request for channel 26 is present
 */
#define DMA_HRS_HRS26(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS26_SHIFT)) & DMA_HRS_HRS26_MASK)

#define DMA_HRS_HRS27_MASK                       (0x8000000U)
#define DMA_HRS_HRS27_SHIFT                      (27U)
/*! HRS27 - Hardware Request Status Channel 27
 *  0b0..A hardware service request for channel 27 is not present
 *  0b1..A hardware service request for channel 27 is present
 */
#define DMA_HRS_HRS27(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS27_SHIFT)) & DMA_HRS_HRS27_MASK)

#define DMA_HRS_HRS28_MASK                       (0x10000000U)
#define DMA_HRS_HRS28_SHIFT                      (28U)
/*! HRS28 - Hardware Request Status Channel 28
 *  0b0..A hardware service request for channel 28 is not present
 *  0b1..A hardware service request for channel 28 is present
 */
#define DMA_HRS_HRS28(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS28_SHIFT)) & DMA_HRS_HRS28_MASK)

#define DMA_HRS_HRS29_MASK                       (0x20000000U)
#define DMA_HRS_HRS29_SHIFT                      (29U)
/*! HRS29 - Hardware Request Status Channel 29
 *  0b0..A hardware service request for channel 29 is not preset
 *  0b1..A hardware service request for channel 29 is present
 */
#define DMA_HRS_HRS29(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS29_SHIFT)) & DMA_HRS_HRS29_MASK)

#define DMA_HRS_HRS30_MASK                       (0x40000000U)
#define DMA_HRS_HRS30_SHIFT                      (30U)
/*! HRS30 - Hardware Request Status Channel 30
 *  0b0..A hardware service request for channel 30 is not present
 *  0b1..A hardware service request for channel 30 is present
 */
#define DMA_HRS_HRS30(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS30_SHIFT)) & DMA_HRS_HRS30_MASK)

#define DMA_HRS_HRS31_MASK                       (0x80000000U)
#define DMA_HRS_HRS31_SHIFT                      (31U)
/*! HRS31 - Hardware Request Status Channel 31
 *  0b0..A hardware service request for channel 31 is not present
 *  0b1..A hardware service request for channel 31 is present
 */
#define DMA_HRS_HRS31(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_HRS_HRS31_SHIFT)) & DMA_HRS_HRS31_MASK)
/*! @} */

/*! @name EARS - Enable Asynchronous Request in Stop */
/*! @{ */

#define DMA_EARS_EDREQ_0_MASK                    (0x1U)
#define DMA_EARS_EDREQ_0_SHIFT                   (0U)
/*! EDREQ_0 - Enable asynchronous DMA request in stop mode for channel 0.
 *  0b0..Disable asynchronous DMA request for channel 0
 *  0b1..Enable asynchronous DMA request for channel 0
 */
#define DMA_EARS_EDREQ_0(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_0_SHIFT)) & DMA_EARS_EDREQ_0_MASK)

#define DMA_EARS_EDREQ_1_MASK                    (0x2U)
#define DMA_EARS_EDREQ_1_SHIFT                   (1U)
/*! EDREQ_1 - Enable asynchronous DMA request in stop mode for channel 1.
 *  0b0..Disable asynchronous DMA request for channel 1
 *  0b1..Enable asynchronous DMA request for channel 1
 */
#define DMA_EARS_EDREQ_1(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_1_SHIFT)) & DMA_EARS_EDREQ_1_MASK)

#define DMA_EARS_EDREQ_2_MASK                    (0x4U)
#define DMA_EARS_EDREQ_2_SHIFT                   (2U)
/*! EDREQ_2 - Enable asynchronous DMA request in stop mode for channel 2.
 *  0b0..Disable asynchronous DMA request for channel 2
 *  0b1..Enable asynchronous DMA request for channel 2
 */
#define DMA_EARS_EDREQ_2(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_2_SHIFT)) & DMA_EARS_EDREQ_2_MASK)

#define DMA_EARS_EDREQ_3_MASK                    (0x8U)
#define DMA_EARS_EDREQ_3_SHIFT                   (3U)
/*! EDREQ_3 - Enable asynchronous DMA request in stop mode for channel 3.
 *  0b0..Disable asynchronous DMA request for channel 3
 *  0b1..Enable asynchronous DMA request for channel 3
 */
#define DMA_EARS_EDREQ_3(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_3_SHIFT)) & DMA_EARS_EDREQ_3_MASK)

#define DMA_EARS_EDREQ_4_MASK                    (0x10U)
#define DMA_EARS_EDREQ_4_SHIFT                   (4U)
/*! EDREQ_4 - Enable asynchronous DMA request in stop mode for channel 4.
 *  0b0..Disable asynchronous DMA request for channel 4
 *  0b1..Enable asynchronous DMA request for channel 4
 */
#define DMA_EARS_EDREQ_4(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_4_SHIFT)) & DMA_EARS_EDREQ_4_MASK)

#define DMA_EARS_EDREQ_5_MASK                    (0x20U)
#define DMA_EARS_EDREQ_5_SHIFT                   (5U)
/*! EDREQ_5 - Enable asynchronous DMA request in stop mode for channel 5.
 *  0b0..Disable asynchronous DMA request for channel 5
 *  0b1..Enable asynchronous DMA request for channel 5
 */
#define DMA_EARS_EDREQ_5(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_5_SHIFT)) & DMA_EARS_EDREQ_5_MASK)

#define DMA_EARS_EDREQ_6_MASK                    (0x40U)
#define DMA_EARS_EDREQ_6_SHIFT                   (6U)
/*! EDREQ_6 - Enable asynchronous DMA request in stop mode for channel 6.
 *  0b0..Disable asynchronous DMA request for channel 6
 *  0b1..Enable asynchronous DMA request for channel 6
 */
#define DMA_EARS_EDREQ_6(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_6_SHIFT)) & DMA_EARS_EDREQ_6_MASK)

#define DMA_EARS_EDREQ_7_MASK                    (0x80U)
#define DMA_EARS_EDREQ_7_SHIFT                   (7U)
/*! EDREQ_7 - Enable asynchronous DMA request in stop mode for channel 7.
 *  0b0..Disable asynchronous DMA request for channel 7
 *  0b1..Enable asynchronous DMA request for channel 7
 */
#define DMA_EARS_EDREQ_7(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_7_SHIFT)) & DMA_EARS_EDREQ_7_MASK)

#define DMA_EARS_EDREQ_8_MASK                    (0x100U)
#define DMA_EARS_EDREQ_8_SHIFT                   (8U)
/*! EDREQ_8 - Enable asynchronous DMA request in stop mode for channel 8.
 *  0b0..Disable asynchronous DMA request for channel 8
 *  0b1..Enable asynchronous DMA request for channel 8
 */
#define DMA_EARS_EDREQ_8(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_8_SHIFT)) & DMA_EARS_EDREQ_8_MASK)

#define DMA_EARS_EDREQ_9_MASK                    (0x200U)
#define DMA_EARS_EDREQ_9_SHIFT                   (9U)
/*! EDREQ_9 - Enable asynchronous DMA request in stop mode for channel 9.
 *  0b0..Disable asynchronous DMA request for channel 9
 *  0b1..Enable asynchronous DMA request for channel 9
 */
#define DMA_EARS_EDREQ_9(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_9_SHIFT)) & DMA_EARS_EDREQ_9_MASK)

#define DMA_EARS_EDREQ_10_MASK                   (0x400U)
#define DMA_EARS_EDREQ_10_SHIFT                  (10U)
/*! EDREQ_10 - Enable asynchronous DMA request in stop mode for channel 10.
 *  0b0..Disable asynchronous DMA request for channel 10
 *  0b1..Enable asynchronous DMA request for channel 10
 */
#define DMA_EARS_EDREQ_10(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_10_SHIFT)) & DMA_EARS_EDREQ_10_MASK)

#define DMA_EARS_EDREQ_11_MASK                   (0x800U)
#define DMA_EARS_EDREQ_11_SHIFT                  (11U)
/*! EDREQ_11 - Enable asynchronous DMA request in stop mode for channel 11.
 *  0b0..Disable asynchronous DMA request for channel 11
 *  0b1..Enable asynchronous DMA request for channel 11
 */
#define DMA_EARS_EDREQ_11(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_11_SHIFT)) & DMA_EARS_EDREQ_11_MASK)

#define DMA_EARS_EDREQ_12_MASK                   (0x1000U)
#define DMA_EARS_EDREQ_12_SHIFT                  (12U)
/*! EDREQ_12 - Enable asynchronous DMA request in stop mode for channel 12.
 *  0b0..Disable asynchronous DMA request for channel 12
 *  0b1..Enable asynchronous DMA request for channel 12
 */
#define DMA_EARS_EDREQ_12(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_12_SHIFT)) & DMA_EARS_EDREQ_12_MASK)

#define DMA_EARS_EDREQ_13_MASK                   (0x2000U)
#define DMA_EARS_EDREQ_13_SHIFT                  (13U)
/*! EDREQ_13 - Enable asynchronous DMA request in stop mode for channel 13.
 *  0b0..Disable asynchronous DMA request for channel 13
 *  0b1..Enable asynchronous DMA request for channel 13
 */
#define DMA_EARS_EDREQ_13(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_13_SHIFT)) & DMA_EARS_EDREQ_13_MASK)

#define DMA_EARS_EDREQ_14_MASK                   (0x4000U)
#define DMA_EARS_EDREQ_14_SHIFT                  (14U)
/*! EDREQ_14 - Enable asynchronous DMA request in stop mode for channel 14.
 *  0b0..Disable asynchronous DMA request for channel 14
 *  0b1..Enable asynchronous DMA request for channel 14
 */
#define DMA_EARS_EDREQ_14(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_14_SHIFT)) & DMA_EARS_EDREQ_14_MASK)

#define DMA_EARS_EDREQ_15_MASK                   (0x8000U)
#define DMA_EARS_EDREQ_15_SHIFT                  (15U)
/*! EDREQ_15 - Enable asynchronous DMA request in stop mode for channel 15.
 *  0b0..Disable asynchronous DMA request for channel 15
 *  0b1..Enable asynchronous DMA request for channel 15
 */
#define DMA_EARS_EDREQ_15(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_15_SHIFT)) & DMA_EARS_EDREQ_15_MASK)

#define DMA_EARS_EDREQ_16_MASK                   (0x10000U)
#define DMA_EARS_EDREQ_16_SHIFT                  (16U)
/*! EDREQ_16 - Enable asynchronous DMA request in stop mode for channel 16.
 *  0b0..Disable asynchronous DMA request for channel 16
 *  0b1..Enable asynchronous DMA request for channel 16
 */
#define DMA_EARS_EDREQ_16(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_16_SHIFT)) & DMA_EARS_EDREQ_16_MASK)

#define DMA_EARS_EDREQ_17_MASK                   (0x20000U)
#define DMA_EARS_EDREQ_17_SHIFT                  (17U)
/*! EDREQ_17 - Enable asynchronous DMA request in stop mode for channel 17.
 *  0b0..Disable asynchronous DMA request for channel 17
 *  0b1..Enable asynchronous DMA request for channel 17
 */
#define DMA_EARS_EDREQ_17(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_17_SHIFT)) & DMA_EARS_EDREQ_17_MASK)

#define DMA_EARS_EDREQ_18_MASK                   (0x40000U)
#define DMA_EARS_EDREQ_18_SHIFT                  (18U)
/*! EDREQ_18 - Enable asynchronous DMA request in stop mode for channel 18.
 *  0b0..Disable asynchronous DMA request for channel 18
 *  0b1..Enable asynchronous DMA request for channel 18
 */
#define DMA_EARS_EDREQ_18(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_18_SHIFT)) & DMA_EARS_EDREQ_18_MASK)

#define DMA_EARS_EDREQ_19_MASK                   (0x80000U)
#define DMA_EARS_EDREQ_19_SHIFT                  (19U)
/*! EDREQ_19 - Enable asynchronous DMA request in stop mode for channel 19.
 *  0b0..Disable asynchronous DMA request for channel 19
 *  0b1..Enable asynchronous DMA request for channel 19
 */
#define DMA_EARS_EDREQ_19(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_19_SHIFT)) & DMA_EARS_EDREQ_19_MASK)

#define DMA_EARS_EDREQ_20_MASK                   (0x100000U)
#define DMA_EARS_EDREQ_20_SHIFT                  (20U)
/*! EDREQ_20 - Enable asynchronous DMA request in stop mode for channel 20.
 *  0b0..Disable asynchronous DMA request for channel 20
 *  0b1..Enable asynchronous DMA request for channel 20
 */
#define DMA_EARS_EDREQ_20(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_20_SHIFT)) & DMA_EARS_EDREQ_20_MASK)

#define DMA_EARS_EDREQ_21_MASK                   (0x200000U)
#define DMA_EARS_EDREQ_21_SHIFT                  (21U)
/*! EDREQ_21 - Enable asynchronous DMA request in stop mode for channel 21.
 *  0b0..Disable asynchronous DMA request for channel 21
 *  0b1..Enable asynchronous DMA request for channel 21
 */
#define DMA_EARS_EDREQ_21(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_21_SHIFT)) & DMA_EARS_EDREQ_21_MASK)

#define DMA_EARS_EDREQ_22_MASK                   (0x400000U)
#define DMA_EARS_EDREQ_22_SHIFT                  (22U)
/*! EDREQ_22 - Enable asynchronous DMA request in stop mode for channel 22.
 *  0b0..Disable asynchronous DMA request for channel 22
 *  0b1..Enable asynchronous DMA request for channel 22
 */
#define DMA_EARS_EDREQ_22(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_22_SHIFT)) & DMA_EARS_EDREQ_22_MASK)

#define DMA_EARS_EDREQ_23_MASK                   (0x800000U)
#define DMA_EARS_EDREQ_23_SHIFT                  (23U)
/*! EDREQ_23 - Enable asynchronous DMA request in stop mode for channel 23.
 *  0b0..Disable asynchronous DMA request for channel 23
 *  0b1..Enable asynchronous DMA request for channel 23
 */
#define DMA_EARS_EDREQ_23(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_23_SHIFT)) & DMA_EARS_EDREQ_23_MASK)

#define DMA_EARS_EDREQ_24_MASK                   (0x1000000U)
#define DMA_EARS_EDREQ_24_SHIFT                  (24U)
/*! EDREQ_24 - Enable asynchronous DMA request in stop mode for channel 24.
 *  0b0..Disable asynchronous DMA request for channel 24
 *  0b1..Enable asynchronous DMA request for channel 24
 */
#define DMA_EARS_EDREQ_24(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_24_SHIFT)) & DMA_EARS_EDREQ_24_MASK)

#define DMA_EARS_EDREQ_25_MASK                   (0x2000000U)
#define DMA_EARS_EDREQ_25_SHIFT                  (25U)
/*! EDREQ_25 - Enable asynchronous DMA request in stop mode for channel 25.
 *  0b0..Disable asynchronous DMA request for channel 25
 *  0b1..Enable asynchronous DMA request for channel 25
 */
#define DMA_EARS_EDREQ_25(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_25_SHIFT)) & DMA_EARS_EDREQ_25_MASK)

#define DMA_EARS_EDREQ_26_MASK                   (0x4000000U)
#define DMA_EARS_EDREQ_26_SHIFT                  (26U)
/*! EDREQ_26 - Enable asynchronous DMA request in stop mode for channel 26.
 *  0b0..Disable asynchronous DMA request for channel 26
 *  0b1..Enable asynchronous DMA request for channel 26
 */
#define DMA_EARS_EDREQ_26(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_26_SHIFT)) & DMA_EARS_EDREQ_26_MASK)

#define DMA_EARS_EDREQ_27_MASK                   (0x8000000U)
#define DMA_EARS_EDREQ_27_SHIFT                  (27U)
/*! EDREQ_27 - Enable asynchronous DMA request in stop mode for channel 27.
 *  0b0..Disable asynchronous DMA request for channel 27
 *  0b1..Enable asynchronous DMA request for channel 27
 */
#define DMA_EARS_EDREQ_27(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_27_SHIFT)) & DMA_EARS_EDREQ_27_MASK)

#define DMA_EARS_EDREQ_28_MASK                   (0x10000000U)
#define DMA_EARS_EDREQ_28_SHIFT                  (28U)
/*! EDREQ_28 - Enable asynchronous DMA request in stop mode for channel 28.
 *  0b0..Disable asynchronous DMA request for channel 28
 *  0b1..Enable asynchronous DMA request for channel 28
 */
#define DMA_EARS_EDREQ_28(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_28_SHIFT)) & DMA_EARS_EDREQ_28_MASK)

#define DMA_EARS_EDREQ_29_MASK                   (0x20000000U)
#define DMA_EARS_EDREQ_29_SHIFT                  (29U)
/*! EDREQ_29 - Enable asynchronous DMA request in stop mode for channel 29.
 *  0b0..Disable asynchronous DMA request for channel 29
 *  0b1..Enable asynchronous DMA request for channel 29
 */
#define DMA_EARS_EDREQ_29(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_29_SHIFT)) & DMA_EARS_EDREQ_29_MASK)

#define DMA_EARS_EDREQ_30_MASK                   (0x40000000U)
#define DMA_EARS_EDREQ_30_SHIFT                  (30U)
/*! EDREQ_30 - Enable asynchronous DMA request in stop mode for channel 30.
 *  0b0..Disable asynchronous DMA request for channel 30
 *  0b1..Enable asynchronous DMA request for channel 30
 */
#define DMA_EARS_EDREQ_30(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_30_SHIFT)) & DMA_EARS_EDREQ_30_MASK)

#define DMA_EARS_EDREQ_31_MASK                   (0x80000000U)
#define DMA_EARS_EDREQ_31_SHIFT                  (31U)
/*! EDREQ_31 - Enable asynchronous DMA request in stop mode for channel 31.
 *  0b0..Disable asynchronous DMA request for channel 31
 *  0b1..Enable asynchronous DMA request for channel 31
 */
#define DMA_EARS_EDREQ_31(x)                     (((uint32_t)(((uint32_t)(x)) << DMA_EARS_EDREQ_31_SHIFT)) & DMA_EARS_EDREQ_31_MASK)
/*! @} */

/*! @name DCHPRI3 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI3_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI3_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI3_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_CHPRI_SHIFT)) & DMA_DCHPRI3_CHPRI_MASK)

#define DMA_DCHPRI3_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI3_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI3_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_GRPPRI_SHIFT)) & DMA_DCHPRI3_GRPPRI_MASK)

#define DMA_DCHPRI3_DPA_MASK                     (0x40U)
#define DMA_DCHPRI3_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI3_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_DPA_SHIFT)) & DMA_DCHPRI3_DPA_MASK)

#define DMA_DCHPRI3_ECP_MASK                     (0x80U)
#define DMA_DCHPRI3_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI3_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI3_ECP_SHIFT)) & DMA_DCHPRI3_ECP_MASK)
/*! @} */

/*! @name DCHPRI2 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI2_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI2_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI2_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_CHPRI_SHIFT)) & DMA_DCHPRI2_CHPRI_MASK)

#define DMA_DCHPRI2_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI2_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI2_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_GRPPRI_SHIFT)) & DMA_DCHPRI2_GRPPRI_MASK)

#define DMA_DCHPRI2_DPA_MASK                     (0x40U)
#define DMA_DCHPRI2_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI2_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_DPA_SHIFT)) & DMA_DCHPRI2_DPA_MASK)

#define DMA_DCHPRI2_ECP_MASK                     (0x80U)
#define DMA_DCHPRI2_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI2_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI2_ECP_SHIFT)) & DMA_DCHPRI2_ECP_MASK)
/*! @} */

/*! @name DCHPRI1 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI1_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI1_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI1_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_CHPRI_SHIFT)) & DMA_DCHPRI1_CHPRI_MASK)

#define DMA_DCHPRI1_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI1_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI1_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_GRPPRI_SHIFT)) & DMA_DCHPRI1_GRPPRI_MASK)

#define DMA_DCHPRI1_DPA_MASK                     (0x40U)
#define DMA_DCHPRI1_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI1_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_DPA_SHIFT)) & DMA_DCHPRI1_DPA_MASK)

#define DMA_DCHPRI1_ECP_MASK                     (0x80U)
#define DMA_DCHPRI1_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI1_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI1_ECP_SHIFT)) & DMA_DCHPRI1_ECP_MASK)
/*! @} */

/*! @name DCHPRI0 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI0_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI0_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI0_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_CHPRI_SHIFT)) & DMA_DCHPRI0_CHPRI_MASK)

#define DMA_DCHPRI0_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI0_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI0_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_GRPPRI_SHIFT)) & DMA_DCHPRI0_GRPPRI_MASK)

#define DMA_DCHPRI0_DPA_MASK                     (0x40U)
#define DMA_DCHPRI0_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI0_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_DPA_SHIFT)) & DMA_DCHPRI0_DPA_MASK)

#define DMA_DCHPRI0_ECP_MASK                     (0x80U)
#define DMA_DCHPRI0_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI0_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI0_ECP_SHIFT)) & DMA_DCHPRI0_ECP_MASK)
/*! @} */

/*! @name DCHPRI7 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI7_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI7_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI7_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_CHPRI_SHIFT)) & DMA_DCHPRI7_CHPRI_MASK)

#define DMA_DCHPRI7_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI7_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI7_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_GRPPRI_SHIFT)) & DMA_DCHPRI7_GRPPRI_MASK)

#define DMA_DCHPRI7_DPA_MASK                     (0x40U)
#define DMA_DCHPRI7_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI7_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_DPA_SHIFT)) & DMA_DCHPRI7_DPA_MASK)

#define DMA_DCHPRI7_ECP_MASK                     (0x80U)
#define DMA_DCHPRI7_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI7_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI7_ECP_SHIFT)) & DMA_DCHPRI7_ECP_MASK)
/*! @} */

/*! @name DCHPRI6 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI6_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI6_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI6_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_CHPRI_SHIFT)) & DMA_DCHPRI6_CHPRI_MASK)

#define DMA_DCHPRI6_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI6_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI6_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_GRPPRI_SHIFT)) & DMA_DCHPRI6_GRPPRI_MASK)

#define DMA_DCHPRI6_DPA_MASK                     (0x40U)
#define DMA_DCHPRI6_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI6_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_DPA_SHIFT)) & DMA_DCHPRI6_DPA_MASK)

#define DMA_DCHPRI6_ECP_MASK                     (0x80U)
#define DMA_DCHPRI6_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI6_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI6_ECP_SHIFT)) & DMA_DCHPRI6_ECP_MASK)
/*! @} */

/*! @name DCHPRI5 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI5_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI5_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI5_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_CHPRI_SHIFT)) & DMA_DCHPRI5_CHPRI_MASK)

#define DMA_DCHPRI5_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI5_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI5_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_GRPPRI_SHIFT)) & DMA_DCHPRI5_GRPPRI_MASK)

#define DMA_DCHPRI5_DPA_MASK                     (0x40U)
#define DMA_DCHPRI5_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI5_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_DPA_SHIFT)) & DMA_DCHPRI5_DPA_MASK)

#define DMA_DCHPRI5_ECP_MASK                     (0x80U)
#define DMA_DCHPRI5_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI5_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI5_ECP_SHIFT)) & DMA_DCHPRI5_ECP_MASK)
/*! @} */

/*! @name DCHPRI4 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI4_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI4_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI4_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_CHPRI_SHIFT)) & DMA_DCHPRI4_CHPRI_MASK)

#define DMA_DCHPRI4_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI4_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI4_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_GRPPRI_SHIFT)) & DMA_DCHPRI4_GRPPRI_MASK)

#define DMA_DCHPRI4_DPA_MASK                     (0x40U)
#define DMA_DCHPRI4_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI4_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_DPA_SHIFT)) & DMA_DCHPRI4_DPA_MASK)

#define DMA_DCHPRI4_ECP_MASK                     (0x80U)
#define DMA_DCHPRI4_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI4_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI4_ECP_SHIFT)) & DMA_DCHPRI4_ECP_MASK)
/*! @} */

/*! @name DCHPRI11 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI11_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI11_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI11_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_CHPRI_SHIFT)) & DMA_DCHPRI11_CHPRI_MASK)

#define DMA_DCHPRI11_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI11_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI11_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_GRPPRI_SHIFT)) & DMA_DCHPRI11_GRPPRI_MASK)

#define DMA_DCHPRI11_DPA_MASK                    (0x40U)
#define DMA_DCHPRI11_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI11_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_DPA_SHIFT)) & DMA_DCHPRI11_DPA_MASK)

#define DMA_DCHPRI11_ECP_MASK                    (0x80U)
#define DMA_DCHPRI11_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI11_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI11_ECP_SHIFT)) & DMA_DCHPRI11_ECP_MASK)
/*! @} */

/*! @name DCHPRI10 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI10_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI10_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI10_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_CHPRI_SHIFT)) & DMA_DCHPRI10_CHPRI_MASK)

#define DMA_DCHPRI10_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI10_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI10_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_GRPPRI_SHIFT)) & DMA_DCHPRI10_GRPPRI_MASK)

#define DMA_DCHPRI10_DPA_MASK                    (0x40U)
#define DMA_DCHPRI10_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI10_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_DPA_SHIFT)) & DMA_DCHPRI10_DPA_MASK)

#define DMA_DCHPRI10_ECP_MASK                    (0x80U)
#define DMA_DCHPRI10_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI10_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI10_ECP_SHIFT)) & DMA_DCHPRI10_ECP_MASK)
/*! @} */

/*! @name DCHPRI9 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI9_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI9_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI9_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_CHPRI_SHIFT)) & DMA_DCHPRI9_CHPRI_MASK)

#define DMA_DCHPRI9_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI9_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI9_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_GRPPRI_SHIFT)) & DMA_DCHPRI9_GRPPRI_MASK)

#define DMA_DCHPRI9_DPA_MASK                     (0x40U)
#define DMA_DCHPRI9_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI9_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_DPA_SHIFT)) & DMA_DCHPRI9_DPA_MASK)

#define DMA_DCHPRI9_ECP_MASK                     (0x80U)
#define DMA_DCHPRI9_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI9_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI9_ECP_SHIFT)) & DMA_DCHPRI9_ECP_MASK)
/*! @} */

/*! @name DCHPRI8 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI8_CHPRI_MASK                   (0xFU)
#define DMA_DCHPRI8_CHPRI_SHIFT                  (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI8_CHPRI(x)                     (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_CHPRI_SHIFT)) & DMA_DCHPRI8_CHPRI_MASK)

#define DMA_DCHPRI8_GRPPRI_MASK                  (0x30U)
#define DMA_DCHPRI8_GRPPRI_SHIFT                 (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI8_GRPPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_GRPPRI_SHIFT)) & DMA_DCHPRI8_GRPPRI_MASK)

#define DMA_DCHPRI8_DPA_MASK                     (0x40U)
#define DMA_DCHPRI8_DPA_SHIFT                    (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI8_DPA(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_DPA_SHIFT)) & DMA_DCHPRI8_DPA_MASK)

#define DMA_DCHPRI8_ECP_MASK                     (0x80U)
#define DMA_DCHPRI8_ECP_SHIFT                    (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI8_ECP(x)                       (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI8_ECP_SHIFT)) & DMA_DCHPRI8_ECP_MASK)
/*! @} */

/*! @name DCHPRI15 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI15_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI15_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI15_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_CHPRI_SHIFT)) & DMA_DCHPRI15_CHPRI_MASK)

#define DMA_DCHPRI15_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI15_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI15_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_GRPPRI_SHIFT)) & DMA_DCHPRI15_GRPPRI_MASK)

#define DMA_DCHPRI15_DPA_MASK                    (0x40U)
#define DMA_DCHPRI15_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI15_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_DPA_SHIFT)) & DMA_DCHPRI15_DPA_MASK)

#define DMA_DCHPRI15_ECP_MASK                    (0x80U)
#define DMA_DCHPRI15_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI15_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI15_ECP_SHIFT)) & DMA_DCHPRI15_ECP_MASK)
/*! @} */

/*! @name DCHPRI14 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI14_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI14_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI14_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_CHPRI_SHIFT)) & DMA_DCHPRI14_CHPRI_MASK)

#define DMA_DCHPRI14_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI14_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI14_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_GRPPRI_SHIFT)) & DMA_DCHPRI14_GRPPRI_MASK)

#define DMA_DCHPRI14_DPA_MASK                    (0x40U)
#define DMA_DCHPRI14_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI14_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_DPA_SHIFT)) & DMA_DCHPRI14_DPA_MASK)

#define DMA_DCHPRI14_ECP_MASK                    (0x80U)
#define DMA_DCHPRI14_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI14_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI14_ECP_SHIFT)) & DMA_DCHPRI14_ECP_MASK)
/*! @} */

/*! @name DCHPRI13 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI13_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI13_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI13_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_CHPRI_SHIFT)) & DMA_DCHPRI13_CHPRI_MASK)

#define DMA_DCHPRI13_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI13_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI13_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_GRPPRI_SHIFT)) & DMA_DCHPRI13_GRPPRI_MASK)

#define DMA_DCHPRI13_DPA_MASK                    (0x40U)
#define DMA_DCHPRI13_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI13_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_DPA_SHIFT)) & DMA_DCHPRI13_DPA_MASK)

#define DMA_DCHPRI13_ECP_MASK                    (0x80U)
#define DMA_DCHPRI13_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI13_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI13_ECP_SHIFT)) & DMA_DCHPRI13_ECP_MASK)
/*! @} */

/*! @name DCHPRI12 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI12_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI12_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI12_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_CHPRI_SHIFT)) & DMA_DCHPRI12_CHPRI_MASK)

#define DMA_DCHPRI12_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI12_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI12_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_GRPPRI_SHIFT)) & DMA_DCHPRI12_GRPPRI_MASK)

#define DMA_DCHPRI12_DPA_MASK                    (0x40U)
#define DMA_DCHPRI12_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI12_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_DPA_SHIFT)) & DMA_DCHPRI12_DPA_MASK)

#define DMA_DCHPRI12_ECP_MASK                    (0x80U)
#define DMA_DCHPRI12_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI12_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI12_ECP_SHIFT)) & DMA_DCHPRI12_ECP_MASK)
/*! @} */

/*! @name DCHPRI19 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI19_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI19_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI19_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_CHPRI_SHIFT)) & DMA_DCHPRI19_CHPRI_MASK)

#define DMA_DCHPRI19_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI19_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI19_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_GRPPRI_SHIFT)) & DMA_DCHPRI19_GRPPRI_MASK)

#define DMA_DCHPRI19_DPA_MASK                    (0x40U)
#define DMA_DCHPRI19_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI19_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_DPA_SHIFT)) & DMA_DCHPRI19_DPA_MASK)

#define DMA_DCHPRI19_ECP_MASK                    (0x80U)
#define DMA_DCHPRI19_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI19_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI19_ECP_SHIFT)) & DMA_DCHPRI19_ECP_MASK)
/*! @} */

/*! @name DCHPRI18 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI18_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI18_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI18_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_CHPRI_SHIFT)) & DMA_DCHPRI18_CHPRI_MASK)

#define DMA_DCHPRI18_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI18_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI18_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_GRPPRI_SHIFT)) & DMA_DCHPRI18_GRPPRI_MASK)

#define DMA_DCHPRI18_DPA_MASK                    (0x40U)
#define DMA_DCHPRI18_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI18_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_DPA_SHIFT)) & DMA_DCHPRI18_DPA_MASK)

#define DMA_DCHPRI18_ECP_MASK                    (0x80U)
#define DMA_DCHPRI18_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI18_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI18_ECP_SHIFT)) & DMA_DCHPRI18_ECP_MASK)
/*! @} */

/*! @name DCHPRI17 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI17_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI17_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI17_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_CHPRI_SHIFT)) & DMA_DCHPRI17_CHPRI_MASK)

#define DMA_DCHPRI17_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI17_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI17_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_GRPPRI_SHIFT)) & DMA_DCHPRI17_GRPPRI_MASK)

#define DMA_DCHPRI17_DPA_MASK                    (0x40U)
#define DMA_DCHPRI17_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI17_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_DPA_SHIFT)) & DMA_DCHPRI17_DPA_MASK)

#define DMA_DCHPRI17_ECP_MASK                    (0x80U)
#define DMA_DCHPRI17_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI17_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI17_ECP_SHIFT)) & DMA_DCHPRI17_ECP_MASK)
/*! @} */

/*! @name DCHPRI16 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI16_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI16_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI16_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_CHPRI_SHIFT)) & DMA_DCHPRI16_CHPRI_MASK)

#define DMA_DCHPRI16_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI16_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI16_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_GRPPRI_SHIFT)) & DMA_DCHPRI16_GRPPRI_MASK)

#define DMA_DCHPRI16_DPA_MASK                    (0x40U)
#define DMA_DCHPRI16_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI16_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_DPA_SHIFT)) & DMA_DCHPRI16_DPA_MASK)

#define DMA_DCHPRI16_ECP_MASK                    (0x80U)
#define DMA_DCHPRI16_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI16_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI16_ECP_SHIFT)) & DMA_DCHPRI16_ECP_MASK)
/*! @} */

/*! @name DCHPRI23 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI23_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI23_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI23_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_CHPRI_SHIFT)) & DMA_DCHPRI23_CHPRI_MASK)

#define DMA_DCHPRI23_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI23_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI23_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_GRPPRI_SHIFT)) & DMA_DCHPRI23_GRPPRI_MASK)

#define DMA_DCHPRI23_DPA_MASK                    (0x40U)
#define DMA_DCHPRI23_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI23_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_DPA_SHIFT)) & DMA_DCHPRI23_DPA_MASK)

#define DMA_DCHPRI23_ECP_MASK                    (0x80U)
#define DMA_DCHPRI23_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI23_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI23_ECP_SHIFT)) & DMA_DCHPRI23_ECP_MASK)
/*! @} */

/*! @name DCHPRI22 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI22_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI22_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI22_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_CHPRI_SHIFT)) & DMA_DCHPRI22_CHPRI_MASK)

#define DMA_DCHPRI22_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI22_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI22_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_GRPPRI_SHIFT)) & DMA_DCHPRI22_GRPPRI_MASK)

#define DMA_DCHPRI22_DPA_MASK                    (0x40U)
#define DMA_DCHPRI22_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI22_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_DPA_SHIFT)) & DMA_DCHPRI22_DPA_MASK)

#define DMA_DCHPRI22_ECP_MASK                    (0x80U)
#define DMA_DCHPRI22_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI22_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI22_ECP_SHIFT)) & DMA_DCHPRI22_ECP_MASK)
/*! @} */

/*! @name DCHPRI21 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI21_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI21_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI21_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_CHPRI_SHIFT)) & DMA_DCHPRI21_CHPRI_MASK)

#define DMA_DCHPRI21_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI21_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI21_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_GRPPRI_SHIFT)) & DMA_DCHPRI21_GRPPRI_MASK)

#define DMA_DCHPRI21_DPA_MASK                    (0x40U)
#define DMA_DCHPRI21_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI21_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_DPA_SHIFT)) & DMA_DCHPRI21_DPA_MASK)

#define DMA_DCHPRI21_ECP_MASK                    (0x80U)
#define DMA_DCHPRI21_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI21_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI21_ECP_SHIFT)) & DMA_DCHPRI21_ECP_MASK)
/*! @} */

/*! @name DCHPRI20 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI20_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI20_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI20_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_CHPRI_SHIFT)) & DMA_DCHPRI20_CHPRI_MASK)

#define DMA_DCHPRI20_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI20_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI20_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_GRPPRI_SHIFT)) & DMA_DCHPRI20_GRPPRI_MASK)

#define DMA_DCHPRI20_DPA_MASK                    (0x40U)
#define DMA_DCHPRI20_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI20_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_DPA_SHIFT)) & DMA_DCHPRI20_DPA_MASK)

#define DMA_DCHPRI20_ECP_MASK                    (0x80U)
#define DMA_DCHPRI20_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI20_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI20_ECP_SHIFT)) & DMA_DCHPRI20_ECP_MASK)
/*! @} */

/*! @name DCHPRI27 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI27_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI27_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI27_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_CHPRI_SHIFT)) & DMA_DCHPRI27_CHPRI_MASK)

#define DMA_DCHPRI27_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI27_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI27_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_GRPPRI_SHIFT)) & DMA_DCHPRI27_GRPPRI_MASK)

#define DMA_DCHPRI27_DPA_MASK                    (0x40U)
#define DMA_DCHPRI27_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI27_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_DPA_SHIFT)) & DMA_DCHPRI27_DPA_MASK)

#define DMA_DCHPRI27_ECP_MASK                    (0x80U)
#define DMA_DCHPRI27_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI27_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI27_ECP_SHIFT)) & DMA_DCHPRI27_ECP_MASK)
/*! @} */

/*! @name DCHPRI26 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI26_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI26_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI26_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_CHPRI_SHIFT)) & DMA_DCHPRI26_CHPRI_MASK)

#define DMA_DCHPRI26_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI26_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI26_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_GRPPRI_SHIFT)) & DMA_DCHPRI26_GRPPRI_MASK)

#define DMA_DCHPRI26_DPA_MASK                    (0x40U)
#define DMA_DCHPRI26_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI26_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_DPA_SHIFT)) & DMA_DCHPRI26_DPA_MASK)

#define DMA_DCHPRI26_ECP_MASK                    (0x80U)
#define DMA_DCHPRI26_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI26_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI26_ECP_SHIFT)) & DMA_DCHPRI26_ECP_MASK)
/*! @} */

/*! @name DCHPRI25 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI25_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI25_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI25_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_CHPRI_SHIFT)) & DMA_DCHPRI25_CHPRI_MASK)

#define DMA_DCHPRI25_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI25_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI25_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_GRPPRI_SHIFT)) & DMA_DCHPRI25_GRPPRI_MASK)

#define DMA_DCHPRI25_DPA_MASK                    (0x40U)
#define DMA_DCHPRI25_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI25_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_DPA_SHIFT)) & DMA_DCHPRI25_DPA_MASK)

#define DMA_DCHPRI25_ECP_MASK                    (0x80U)
#define DMA_DCHPRI25_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI25_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI25_ECP_SHIFT)) & DMA_DCHPRI25_ECP_MASK)
/*! @} */

/*! @name DCHPRI24 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI24_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI24_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI24_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_CHPRI_SHIFT)) & DMA_DCHPRI24_CHPRI_MASK)

#define DMA_DCHPRI24_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI24_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI24_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_GRPPRI_SHIFT)) & DMA_DCHPRI24_GRPPRI_MASK)

#define DMA_DCHPRI24_DPA_MASK                    (0x40U)
#define DMA_DCHPRI24_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI24_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_DPA_SHIFT)) & DMA_DCHPRI24_DPA_MASK)

#define DMA_DCHPRI24_ECP_MASK                    (0x80U)
#define DMA_DCHPRI24_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI24_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI24_ECP_SHIFT)) & DMA_DCHPRI24_ECP_MASK)
/*! @} */

/*! @name DCHPRI31 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI31_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI31_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI31_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_CHPRI_SHIFT)) & DMA_DCHPRI31_CHPRI_MASK)

#define DMA_DCHPRI31_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI31_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI31_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_GRPPRI_SHIFT)) & DMA_DCHPRI31_GRPPRI_MASK)

#define DMA_DCHPRI31_DPA_MASK                    (0x40U)
#define DMA_DCHPRI31_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI31_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_DPA_SHIFT)) & DMA_DCHPRI31_DPA_MASK)

#define DMA_DCHPRI31_ECP_MASK                    (0x80U)
#define DMA_DCHPRI31_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI31_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI31_ECP_SHIFT)) & DMA_DCHPRI31_ECP_MASK)
/*! @} */

/*! @name DCHPRI30 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI30_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI30_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI30_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_CHPRI_SHIFT)) & DMA_DCHPRI30_CHPRI_MASK)

#define DMA_DCHPRI30_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI30_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI30_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_GRPPRI_SHIFT)) & DMA_DCHPRI30_GRPPRI_MASK)

#define DMA_DCHPRI30_DPA_MASK                    (0x40U)
#define DMA_DCHPRI30_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI30_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_DPA_SHIFT)) & DMA_DCHPRI30_DPA_MASK)

#define DMA_DCHPRI30_ECP_MASK                    (0x80U)
#define DMA_DCHPRI30_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI30_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI30_ECP_SHIFT)) & DMA_DCHPRI30_ECP_MASK)
/*! @} */

/*! @name DCHPRI29 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI29_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI29_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI29_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_CHPRI_SHIFT)) & DMA_DCHPRI29_CHPRI_MASK)

#define DMA_DCHPRI29_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI29_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI29_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_GRPPRI_SHIFT)) & DMA_DCHPRI29_GRPPRI_MASK)

#define DMA_DCHPRI29_DPA_MASK                    (0x40U)
#define DMA_DCHPRI29_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI29_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_DPA_SHIFT)) & DMA_DCHPRI29_DPA_MASK)

#define DMA_DCHPRI29_ECP_MASK                    (0x80U)
#define DMA_DCHPRI29_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI29_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI29_ECP_SHIFT)) & DMA_DCHPRI29_ECP_MASK)
/*! @} */

/*! @name DCHPRI28 - Channel Priority */
/*! @{ */

#define DMA_DCHPRI28_CHPRI_MASK                  (0xFU)
#define DMA_DCHPRI28_CHPRI_SHIFT                 (0U)
/*! CHPRI - Channel n Arbitration Priority */
#define DMA_DCHPRI28_CHPRI(x)                    (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_CHPRI_SHIFT)) & DMA_DCHPRI28_CHPRI_MASK)

#define DMA_DCHPRI28_GRPPRI_MASK                 (0x30U)
#define DMA_DCHPRI28_GRPPRI_SHIFT                (4U)
/*! GRPPRI - Channel n Current Group Priority */
#define DMA_DCHPRI28_GRPPRI(x)                   (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_GRPPRI_SHIFT)) & DMA_DCHPRI28_GRPPRI_MASK)

#define DMA_DCHPRI28_DPA_MASK                    (0x40U)
#define DMA_DCHPRI28_DPA_SHIFT                   (6U)
/*! DPA - Disable Preempt Ability. This field resets to 0.
 *  0b0..Channel n can suspend a lower priority channel
 *  0b1..Channel n cannot suspend any channel, regardless of channel priority
 */
#define DMA_DCHPRI28_DPA(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_DPA_SHIFT)) & DMA_DCHPRI28_DPA_MASK)

#define DMA_DCHPRI28_ECP_MASK                    (0x80U)
#define DMA_DCHPRI28_ECP_SHIFT                   (7U)
/*! ECP - Enable Channel Preemption. This field resets to 0.
 *  0b0..Channel n cannot be suspended by a higher priority channel's service request
 *  0b1..Channel n can be temporarily suspended by the service request of a higher priority channel
 */
#define DMA_DCHPRI28_ECP(x)                      (((uint8_t)(((uint8_t)(x)) << DMA_DCHPRI28_ECP_SHIFT)) & DMA_DCHPRI28_ECP_MASK)
/*! @} */

/*! @name SADDR - TCD Source Address */
/*! @{ */

#define DMA_SADDR_SADDR_MASK                     (0xFFFFFFFFU)
#define DMA_SADDR_SADDR_SHIFT                    (0U)
/*! SADDR - Source Address */
#define DMA_SADDR_SADDR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_SADDR_SADDR_SHIFT)) & DMA_SADDR_SADDR_MASK)
/*! @} */

/* The count of DMA_SADDR */
#define DMA_SADDR_COUNT                          (32U)

/*! @name SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_SOFF_SOFF_MASK                       (0xFFFFU)
#define DMA_SOFF_SOFF_SHIFT                      (0U)
/*! SOFF - Source address signed offset */
#define DMA_SOFF_SOFF(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_SOFF_SOFF_SHIFT)) & DMA_SOFF_SOFF_MASK)
/*! @} */

/* The count of DMA_SOFF */
#define DMA_SOFF_COUNT                           (32U)

/*! @name ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_ATTR_DSIZE_MASK                      (0x7U)
#define DMA_ATTR_DSIZE_SHIFT                     (0U)
/*! DSIZE - Destination data transfer size */
#define DMA_ATTR_DSIZE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DSIZE_SHIFT)) & DMA_ATTR_DSIZE_MASK)

#define DMA_ATTR_DMOD_MASK                       (0xF8U)
#define DMA_ATTR_DMOD_SHIFT                      (3U)
/*! DMOD - Destination Address Modulo */
#define DMA_ATTR_DMOD(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DMOD_SHIFT)) & DMA_ATTR_DMOD_MASK)

#define DMA_ATTR_SSIZE_MASK                      (0x700U)
#define DMA_ATTR_SSIZE_SHIFT                     (8U)
/*! SSIZE - Source data transfer size
 *  0b000..8-bit
 *  0b001..16-bit
 *  0b010..32-bit
 *  0b011..64-bit
 *  0b100..Reserved
 *  0b101..32-byte burst (4 beats of 64 bits)
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define DMA_ATTR_SSIZE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SSIZE_SHIFT)) & DMA_ATTR_SSIZE_MASK)

#define DMA_ATTR_SMOD_MASK                       (0xF800U)
#define DMA_ATTR_SMOD_SHIFT                      (11U)
/*! SMOD - Source Address Modulo
 *  0b00000..Source address modulo feature is disabled
 *  0b00001-0b11111..Value defines address range used to set up circular data queue
 */
#define DMA_ATTR_SMOD(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SMOD_SHIFT)) & DMA_ATTR_SMOD_MASK)
/*! @} */

/* The count of DMA_ATTR */
#define DMA_ATTR_COUNT                           (32U)

/*! @name NBYTES_MLNO - TCD Minor Byte Count (Minor Loop Mapping Disabled) */
/*! @{ */

#define DMA_NBYTES_MLNO_NBYTES_MASK              (0xFFFFFFFFU)
#define DMA_NBYTES_MLNO_NBYTES_SHIFT             (0U)
/*! NBYTES - Minor Byte Transfer Count */
#define DMA_NBYTES_MLNO_NBYTES(x)                (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLNO_NBYTES_SHIFT)) & DMA_NBYTES_MLNO_NBYTES_MASK)
/*! @} */

/* The count of DMA_NBYTES_MLNO */
#define DMA_NBYTES_MLNO_COUNT                    (32U)

/*! @name NBYTES_MLOFFNO - TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled) */
/*! @{ */

#define DMA_NBYTES_MLOFFNO_NBYTES_MASK           (0x3FFFFFFFU)
#define DMA_NBYTES_MLOFFNO_NBYTES_SHIFT          (0U)
/*! NBYTES - Minor Byte Transfer Count */
#define DMA_NBYTES_MLOFFNO_NBYTES(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_NBYTES_MLOFFNO_DMLOE_MASK            (0x40000000U)
#define DMA_NBYTES_MLOFFNO_DMLOE_SHIFT           (30U)
/*! DMLOE - Destination Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the DADDR
 *  0b1..The minor loop offset is applied to the DADDR
 */
#define DMA_NBYTES_MLOFFNO_DMLOE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_NBYTES_MLOFFNO_SMLOE_MASK            (0x80000000U)
#define DMA_NBYTES_MLOFFNO_SMLOE_SHIFT           (31U)
/*! SMLOE - Source Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the SADDR
 *  0b1..The minor loop offset is applied to the SADDR
 */
#define DMA_NBYTES_MLOFFNO_SMLOE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/* The count of DMA_NBYTES_MLOFFNO */
#define DMA_NBYTES_MLOFFNO_COUNT                 (32U)

/*! @name NBYTES_MLOFFYES - TCD Signed Minor Loop Offset (Minor Loop Mapping and Offset Enabled) */
/*! @{ */

#define DMA_NBYTES_MLOFFYES_NBYTES_MASK          (0x3FFU)
#define DMA_NBYTES_MLOFFYES_NBYTES_SHIFT         (0U)
/*! NBYTES - Minor Byte Transfer Count */
#define DMA_NBYTES_MLOFFYES_NBYTES(x)            (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_NBYTES_MLOFFYES_MLOFF_MASK           (0x3FFFFC00U)
#define DMA_NBYTES_MLOFFYES_MLOFF_SHIFT          (10U)
/*! MLOFF - If SMLOE = 1 or DMLOE = 1, this field represents a sign-extended offset applied to the
 *    source or destination address to form the next-state value after the minor loop completes.
 */
#define DMA_NBYTES_MLOFFYES_MLOFF(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_NBYTES_MLOFFYES_DMLOE_MASK           (0x40000000U)
#define DMA_NBYTES_MLOFFYES_DMLOE_SHIFT          (30U)
/*! DMLOE - Destination Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the DADDR
 *  0b1..The minor loop offset is applied to the DADDR
 */
#define DMA_NBYTES_MLOFFYES_DMLOE(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_NBYTES_MLOFFYES_SMLOE_MASK           (0x80000000U)
#define DMA_NBYTES_MLOFFYES_SMLOE_SHIFT          (31U)
/*! SMLOE - Source Minor Loop Offset Enable
 *  0b0..The minor loop offset is not applied to the SADDR
 *  0b1..The minor loop offset is applied to the SADDR
 */
#define DMA_NBYTES_MLOFFYES_SMLOE(x)             (((uint32_t)(((uint32_t)(x)) << DMA_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/* The count of DMA_NBYTES_MLOFFYES */
#define DMA_NBYTES_MLOFFYES_COUNT                (32U)

/*! @name SLAST - TCD Last Source Address Adjustment */
/*! @{ */

#define DMA_SLAST_SLAST_MASK                     (0xFFFFFFFFU)
#define DMA_SLAST_SLAST_SHIFT                    (0U)
/*! SLAST - Last Source Address Adjustment */
#define DMA_SLAST_SLAST(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_SLAST_SLAST_SHIFT)) & DMA_SLAST_SLAST_MASK)
/*! @} */

/* The count of DMA_SLAST */
#define DMA_SLAST_COUNT                          (32U)

/*! @name DADDR - TCD Destination Address */
/*! @{ */

#define DMA_DADDR_DADDR_MASK                     (0xFFFFFFFFU)
#define DMA_DADDR_DADDR_SHIFT                    (0U)
/*! DADDR - Destination Address */
#define DMA_DADDR_DADDR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DADDR_DADDR_SHIFT)) & DMA_DADDR_DADDR_MASK)
/*! @} */

/* The count of DMA_DADDR */
#define DMA_DADDR_COUNT                          (32U)

/*! @name DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_DOFF_DOFF_MASK                       (0xFFFFU)
#define DMA_DOFF_DOFF_SHIFT                      (0U)
/*! DOFF - Destination Address Signed Offset */
#define DMA_DOFF_DOFF(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_DOFF_DOFF_SHIFT)) & DMA_DOFF_DOFF_MASK)
/*! @} */

/* The count of DMA_DOFF */
#define DMA_DOFF_COUNT                           (32U)

/*! @name CITER_ELINKNO - TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
/*! @{ */

#define DMA_CITER_ELINKNO_CITER_MASK             (0x7FFFU)
#define DMA_CITER_ELINKNO_CITER_SHIFT            (0U)
/*! CITER - Current Major Iteration Count */
#define DMA_CITER_ELINKNO_CITER(x)               (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_CITER_SHIFT)) & DMA_CITER_ELINKNO_CITER_MASK)

#define DMA_CITER_ELINKNO_ELINK_MASK             (0x8000U)
#define DMA_CITER_ELINKNO_ELINK_SHIFT            (15U)
/*! ELINK - Enable channel-to-channel linking on minor-loop complete
 *  0b0..Channel-to-channel linking is disabled
 *  0b1..Channel-to-channel linking is enabled
 */
#define DMA_CITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKNO_ELINK_SHIFT)) & DMA_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/* The count of DMA_CITER_ELINKNO */
#define DMA_CITER_ELINKNO_COUNT                  (32U)

/*! @name CITER_ELINKYES - TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
/*! @{ */

#define DMA_CITER_ELINKYES_CITER_MASK            (0x1FFU)
#define DMA_CITER_ELINKYES_CITER_SHIFT           (0U)
/*! CITER - Current Major Iteration Count */
#define DMA_CITER_ELINKYES_CITER(x)              (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_CITER_SHIFT)) & DMA_CITER_ELINKYES_CITER_MASK)

#define DMA_CITER_ELINKYES_LINKCH_MASK           (0x3E00U)
#define DMA_CITER_ELINKYES_LINKCH_SHIFT          (9U)
/*! LINKCH - Minor Loop Link Channel Number */
#define DMA_CITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_CITER_ELINKYES_LINKCH_MASK)

#define DMA_CITER_ELINKYES_ELINK_MASK            (0x8000U)
#define DMA_CITER_ELINKYES_ELINK_SHIFT           (15U)
/*! ELINK - Enable channel-to-channel linking on minor-loop complete
 *  0b0..Channel-to-channel linking is disabled
 *  0b1..Channel-to-channel linking is enabled
 */
#define DMA_CITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x)) << DMA_CITER_ELINKYES_ELINK_SHIFT)) & DMA_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/* The count of DMA_CITER_ELINKYES */
#define DMA_CITER_ELINKYES_COUNT                 (32U)

/*! @name DLAST_SGA - TCD Last Destination Address Adjustment/Scatter Gather Address */
/*! @{ */

#define DMA_DLAST_SGA_DLASTSGA_MASK              (0xFFFFFFFFU)
#define DMA_DLAST_SGA_DLASTSGA_SHIFT             (0U)
/*! DLASTSGA - Destination last address adjustment, or next memory address TCD for channel (scatter/gather) */
#define DMA_DLAST_SGA_DLASTSGA(x)                (((uint32_t)(((uint32_t)(x)) << DMA_DLAST_SGA_DLASTSGA_SHIFT)) & DMA_DLAST_SGA_DLASTSGA_MASK)
/*! @} */

/* The count of DMA_DLAST_SGA */
#define DMA_DLAST_SGA_COUNT                      (32U)

/*! @name CSR - TCD Control and Status */
/*! @{ */

#define DMA_CSR_START_MASK                       (0x1U)
#define DMA_CSR_START_SHIFT                      (0U)
/*! START - Channel Start
 *  0b0..Channel is not explicitly started
 *  0b1..Channel is explicitly started via a software initiated service request
 */
#define DMA_CSR_START(x)                         (((uint16_t)(((uint16_t)(x)) << DMA_CSR_START_SHIFT)) & DMA_CSR_START_MASK)

#define DMA_CSR_INTMAJOR_MASK                    (0x2U)
#define DMA_CSR_INTMAJOR_SHIFT                   (1U)
/*! INTMAJOR - Enable an interrupt when major iteration count completes.
 *  0b0..End of major loop interrupt is disabled
 *  0b1..End of major loop interrupt is enabled
 */
#define DMA_CSR_INTMAJOR(x)                      (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTMAJOR_SHIFT)) & DMA_CSR_INTMAJOR_MASK)

#define DMA_CSR_INTHALF_MASK                     (0x4U)
#define DMA_CSR_INTHALF_SHIFT                    (2U)
/*! INTHALF - Enable an interrupt when major counter is half complete.
 *  0b0..Half-point interrupt is disabled
 *  0b1..Half-point interrupt is enabled
 */
#define DMA_CSR_INTHALF(x)                       (((uint16_t)(((uint16_t)(x)) << DMA_CSR_INTHALF_SHIFT)) & DMA_CSR_INTHALF_MASK)

#define DMA_CSR_DREQ_MASK                        (0x8U)
#define DMA_CSR_DREQ_SHIFT                       (3U)
/*! DREQ - Disable Request
 *  0b0..The channel's ERQ field is not affected
 *  0b1..The channel's ERQ field value changes to 0 when the major loop is complete
 */
#define DMA_CSR_DREQ(x)                          (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DREQ_SHIFT)) & DMA_CSR_DREQ_MASK)

#define DMA_CSR_ESG_MASK                         (0x10U)
#define DMA_CSR_ESG_SHIFT                        (4U)
/*! ESG - Enable Scatter/Gather Processing
 *  0b0..The current channel's TCD is normal format
 *  0b1..The current channel's TCD specifies a scatter gather format
 */
#define DMA_CSR_ESG(x)                           (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ESG_SHIFT)) & DMA_CSR_ESG_MASK)

#define DMA_CSR_MAJORELINK_MASK                  (0x20U)
#define DMA_CSR_MAJORELINK_SHIFT                 (5U)
/*! MAJORELINK - Enable channel-to-channel linking on major loop complete
 *  0b0..Channel-to-channel linking is disabled
 *  0b1..Channel-to-channel linking is enabled
 */
#define DMA_CSR_MAJORELINK(x)                    (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORELINK_SHIFT)) & DMA_CSR_MAJORELINK_MASK)

#define DMA_CSR_ACTIVE_MASK                      (0x40U)
#define DMA_CSR_ACTIVE_SHIFT                     (6U)
/*! ACTIVE - Channel Active */
#define DMA_CSR_ACTIVE(x)                        (((uint16_t)(((uint16_t)(x)) << DMA_CSR_ACTIVE_SHIFT)) & DMA_CSR_ACTIVE_MASK)

#define DMA_CSR_DONE_MASK                        (0x80U)
#define DMA_CSR_DONE_SHIFT                       (7U)
/*! DONE - Channel Done */
#define DMA_CSR_DONE(x)                          (((uint16_t)(((uint16_t)(x)) << DMA_CSR_DONE_SHIFT)) & DMA_CSR_DONE_MASK)

#define DMA_CSR_MAJORLINKCH_MASK                 (0x1F00U)
#define DMA_CSR_MAJORLINKCH_SHIFT                (8U)
/*! MAJORLINKCH - Major Loop Link Channel Number */
#define DMA_CSR_MAJORLINKCH(x)                   (((uint16_t)(((uint16_t)(x)) << DMA_CSR_MAJORLINKCH_SHIFT)) & DMA_CSR_MAJORLINKCH_MASK)

#define DMA_CSR_BWC_MASK                         (0xC000U)
#define DMA_CSR_BWC_SHIFT                        (14U)
/*! BWC - Bandwidth Control
 *  0b00..No eDMA engine stalls
 *  0b01..Reserved
 *  0b10..eDMA engine stalls for 4 cycles after each R/W
 *  0b11..eDMA engine stalls for 8 cycles after each R/W
 */
#define DMA_CSR_BWC(x)                           (((uint16_t)(((uint16_t)(x)) << DMA_CSR_BWC_SHIFT)) & DMA_CSR_BWC_MASK)
/*! @} */

/* The count of DMA_CSR */
#define DMA_CSR_COUNT                            (32U)

/*! @name BITER_ELINKNO - TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
/*! @{ */

#define DMA_BITER_ELINKNO_BITER_MASK             (0x7FFFU)
#define DMA_BITER_ELINKNO_BITER_SHIFT            (0U)
/*! BITER - Starting Major Iteration Count */
#define DMA_BITER_ELINKNO_BITER(x)               (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_BITER_SHIFT)) & DMA_BITER_ELINKNO_BITER_MASK)

#define DMA_BITER_ELINKNO_ELINK_MASK             (0x8000U)
#define DMA_BITER_ELINKNO_ELINK_SHIFT            (15U)
/*! ELINK - Enables channel-to-channel linking on minor loop complete
 *  0b0..Channel-to-channel linking is disabled
 *  0b1..Channel-to-channel linking is enabled
 */
#define DMA_BITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKNO_ELINK_SHIFT)) & DMA_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/* The count of DMA_BITER_ELINKNO */
#define DMA_BITER_ELINKNO_COUNT                  (32U)

/*! @name BITER_ELINKYES - TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
/*! @{ */

#define DMA_BITER_ELINKYES_BITER_MASK            (0x1FFU)
#define DMA_BITER_ELINKYES_BITER_SHIFT           (0U)
/*! BITER - Starting major iteration count */
#define DMA_BITER_ELINKYES_BITER(x)              (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_BITER_SHIFT)) & DMA_BITER_ELINKYES_BITER_MASK)

#define DMA_BITER_ELINKYES_LINKCH_MASK           (0x3E00U)
#define DMA_BITER_ELINKYES_LINKCH_SHIFT          (9U)
/*! LINKCH - Link Channel Number */
#define DMA_BITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_BITER_ELINKYES_LINKCH_MASK)

#define DMA_BITER_ELINKYES_ELINK_MASK            (0x8000U)
#define DMA_BITER_ELINKYES_ELINK_SHIFT           (15U)
/*! ELINK - Enables channel-to-channel linking on minor loop complete
 *  0b0..Channel-to-channel linking is disabled
 *  0b1..Channel-to-channel linking is enabled
 */
#define DMA_BITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x)) << DMA_BITER_ELINKYES_ELINK_SHIFT)) & DMA_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/* The count of DMA_BITER_ELINKYES */
#define DMA_BITER_ELINKYES_COUNT                 (32U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_DMA_H_ */

