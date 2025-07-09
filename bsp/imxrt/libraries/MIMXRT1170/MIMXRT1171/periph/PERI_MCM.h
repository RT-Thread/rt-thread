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
**         CMSIS Peripheral Access Layer for MCM
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
 * @file PERI_MCM.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for MCM
 *
 * CMSIS Peripheral Access Layer for MCM
 */

#if !defined(PERI_MCM_H_)
#define PERI_MCM_H_                              /**< Symbol preventing repeated inclusion */

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
   -- MCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral_Access_Layer MCM Peripheral Access Layer
 * @{
 */

/** MCM - Size of Registers Arrays */
#define MCM_LMDR_COUNT                            4u

/** MCM - Register Layout Typedef */
typedef struct {
  __I  uint16_t PLREV;                             /**< SoC-defined platform revision, offset: 0x0, available only on: MCM (missing on CM7_MCM) */
  __I  uint16_t PCT;                               /**< Processor core type, offset: 0x2, available only on: MCM (missing on CM7_MCM) */
  __I  uint32_t MEMCFG;                            /**< Memory configuration, offset: 0x4, available only on: MCM (missing on CM7_MCM) */
  __I  uint16_t PLASC;                             /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8, available only on: MCM (missing on CM7_MCM) */
  __I  uint16_t PLAMC;                             /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA, available only on: MCM (missing on CM7_MCM) */
  __IO uint32_t CR;                                /**< Control Register, offset: 0xC, available only on: MCM (missing on CM7_MCM) */
  __IO uint32_t ISCR;                              /**< Interrupt Status and Control Register, offset: 0x10 */
       uint8_t RESERVED_0[12];
  __I  uint32_t FADR;                              /**< Fault address register, offset: 0x20, available only on: MCM (missing on CM7_MCM) */
  __I  uint32_t FATR;                              /**< Fault attributes register, offset: 0x24, available only on: MCM (missing on CM7_MCM) */
  __I  uint32_t FDR;                               /**< Fault data register, offset: 0x28, available only on: MCM (missing on CM7_MCM) */
       uint8_t RESERVED_1[980];
  __IO uint32_t LMDR[MCM_LMDR_COUNT];              /**< Local Memory Descriptor Register, array offset: 0x400, array step: 0x4, available only on: MCM (missing on CM7_MCM) */
       uint8_t RESERVED_2[112];
  __IO uint32_t LMPECR;                            /**< LMEM Parity & ECC Control Register, offset: 0x480, available only on: MCM (missing on CM7_MCM) */
       uint8_t RESERVED_3[4];
  __IO uint32_t LMPEIR;                            /**< LMEM Parity & ECC Interrupt Register, offset: 0x488, available only on: MCM (missing on CM7_MCM) */
       uint8_t RESERVED_4[4];
  __I  uint32_t LMFAR;                             /**< LMEM Fault Address Register, offset: 0x490, available only on: MCM (missing on CM7_MCM) */
  __IO uint32_t LMFATR;                            /**< LMEM Fault Attribute Register, offset: 0x494, available only on: MCM (missing on CM7_MCM) */
       uint8_t RESERVED_5[8];
  __I  uint32_t LMFDHR;                            /**< LMEM Fault Data High Register, offset: 0x4A0, available only on: MCM (missing on CM7_MCM) */
  __I  uint32_t LMFDLR;                            /**< LMEM Fault Data Low Register, offset: 0x4A4, available only on: MCM (missing on CM7_MCM) */
} MCM_Type;

/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/*! @name PLREV - SoC-defined platform revision */
/*! @{ */

#define MCM_PLREV_PLREV_MASK                     (0xFFFFU)
#define MCM_PLREV_PLREV_SHIFT                    (0U)
/*! PLREV - The PLREV[15:0] field is specified by an platform input signal to define a software-visible revision number. */
#define MCM_PLREV_PLREV(x)                       (((uint16_t)(((uint16_t)(x)) << MCM_PLREV_PLREV_SHIFT)) & MCM_PLREV_PLREV_MASK)
/*! @} */

/*! @name PCT - Processor core type */
/*! @{ */

#define MCM_PCT_PCT_MASK                         (0xFFFFU)
#define MCM_PCT_PCT_SHIFT                        (0U)
/*! PCT - This MCM design supports the ARM Cortex M4 core. The following value identifies this core complex.
 *  0b1010110001000000..ARM Cortex M4
 */
#define MCM_PCT_PCT(x)                           (((uint16_t)(((uint16_t)(x)) << MCM_PCT_PCT_SHIFT)) & MCM_PCT_PCT_MASK)
/*! @} */

/*! @name MEMCFG - Memory configuration */
/*! @{ */

#define MCM_MEMCFG_TCRAMUSZ_MASK                 (0x3CU)
#define MCM_MEMCFG_TCRAMUSZ_SHIFT                (2U)
/*! TCRAMUSZ - TCRAMU size */
#define MCM_MEMCFG_TCRAMUSZ(x)                   (((uint32_t)(((uint32_t)(x)) << MCM_MEMCFG_TCRAMUSZ_SHIFT)) & MCM_MEMCFG_TCRAMUSZ_MASK)

#define MCM_MEMCFG_TCRAMLSZ_MASK                 (0xF00U)
#define MCM_MEMCFG_TCRAMLSZ_SHIFT                (8U)
/*! TCRAMLSZ - TCRAML size */
#define MCM_MEMCFG_TCRAMLSZ(x)                   (((uint32_t)(((uint32_t)(x)) << MCM_MEMCFG_TCRAMLSZ_SHIFT)) & MCM_MEMCFG_TCRAMLSZ_MASK)
/*! @} */

/*! @name PLASC - Crossbar Switch (AXBS) Slave Configuration */
/*! @{ */

#define MCM_PLASC_ASC_MASK                       (0xFFU)
#define MCM_PLASC_ASC_SHIFT                      (0U)
/*! ASC - Each bit in the ASC field indicates whether there is a corresponding connection to the
 *    crossbar switch's slave input port.
 *  0b00000000..A bus slave connection to AXBS input port n is absent
 *  0b00000001..A bus slave connection to AXBS input port n is present
 */
#define MCM_PLASC_ASC(x)                         (((uint16_t)(((uint16_t)(x)) << MCM_PLASC_ASC_SHIFT)) & MCM_PLASC_ASC_MASK)
/*! @} */

/*! @name PLAMC - Crossbar Switch (AXBS) Master Configuration */
/*! @{ */

#define MCM_PLAMC_AMC_MASK                       (0xFFU)
#define MCM_PLAMC_AMC_SHIFT                      (0U)
/*! AMC - Each bit in the AMC field indicates whether there is a corresponding connection to the AXBS master input port.
 *  0b00000000..A bus master connection to AXBS input port n is absent
 *  0b00000001..A bus master connection to AXBS input port n is present
 */
#define MCM_PLAMC_AMC(x)                         (((uint16_t)(((uint16_t)(x)) << MCM_PLAMC_AMC_SHIFT)) & MCM_PLAMC_AMC_MASK)
/*! @} */

/*! @name CR - Control Register */
/*! @{ */

#define MCM_CR_STATUS_MASK                       (0x1FFU)
#define MCM_CR_STATUS_SHIFT                      (0U)
/*! STATUS - Status bits */
#define MCM_CR_STATUS(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_CR_STATUS_SHIFT)) & MCM_CR_STATUS_MASK)

#define MCM_CR_CBRR_MASK                         (0x200U)
#define MCM_CR_CBRR_SHIFT                        (9U)
/*! CBRR - Crossbar round-robin arbitration enable
 *  0b0..Fixed-priority arbitration
 *  0b1..Round-robin arbitration
 */
#define MCM_CR_CBRR(x)                           (((uint32_t)(((uint32_t)(x)) << MCM_CR_CBRR_SHIFT)) & MCM_CR_CBRR_MASK)

#define MCM_CR_STCMAP_MASK                       (0x3000000U)
#define MCM_CR_STCMAP_SHIFT                      (24U)
/*! STCMAP - System TCM arbitration priority
 *  0b00..Round robin
 *  0b01..Special round robin (favors TCM backoor accesses over the processor)
 *  0b10..Fixed priority. Processor has highest, backdoor has lowest
 *  0b11..Fixed priority. Backdoor has highest, processor has lowest
 */
#define MCM_CR_STCMAP(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_CR_STCMAP_SHIFT)) & MCM_CR_STCMAP_MASK)

#define MCM_CR_STCMWP_MASK                       (0x4000000U)
#define MCM_CR_STCMWP_SHIFT                      (26U)
/*! STCMWP - System TCM write protect */
#define MCM_CR_STCMWP(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_CR_STCMWP_SHIFT)) & MCM_CR_STCMWP_MASK)

#define MCM_CR_CTCMAP_MASK                       (0x30000000U)
#define MCM_CR_CTCMAP_SHIFT                      (28U)
/*! CTCMAP - Code TCM arbitration priority
 *  0b00..Round robin
 *  0b01..Special round robin (favors TCM backoor accesses over the processor)
 *  0b10..Fixed priority. Processor has highest, backdoor has lowest
 *  0b11..Fixed priority. Backdoor has highest, processor has lowest
 */
#define MCM_CR_CTCMAP(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_CR_CTCMAP_SHIFT)) & MCM_CR_CTCMAP_MASK)

#define MCM_CR_CTCMWP_MASK                       (0x40000000U)
#define MCM_CR_CTCMWP_SHIFT                      (30U)
/*! CTCMWP - Code TCM Write Protect */
#define MCM_CR_CTCMWP(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_CR_CTCMWP_SHIFT)) & MCM_CR_CTCMWP_MASK)
/*! @} */

/*! @name ISCR - Interrupt Status and Control Register */
/*! @{ */

#define MCM_ISCR_CWBER_MASK                      (0x10U)
#define MCM_ISCR_CWBER_SHIFT                     (4U)
/*! CWBER - Cache write buffer error status
 *  0b0..No error
 *  0b1..Error occurred
 */
#define MCM_ISCR_CWBER(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_CWBER_SHIFT)) & MCM_ISCR_CWBER_MASK)

#define MCM_ISCR_WABS_MASK                       (0x20U)
#define MCM_ISCR_WABS_SHIFT                      (5U)
/*! WABS - Write Abort on Slave
 *  0b0..No abort
 *  0b1..Abort
 */
#define MCM_ISCR_WABS(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_WABS_SHIFT)) & MCM_ISCR_WABS_MASK)

#define MCM_ISCR_WABSO_MASK                      (0x40U)
#define MCM_ISCR_WABSO_SHIFT                     (6U)
/*! WABSO - Write Abort on Slave Overrun
 *  0b0..No write abort overrun
 *  0b1..Write abort overrun occurred
 */
#define MCM_ISCR_WABSO(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_WABSO_SHIFT)) & MCM_ISCR_WABSO_MASK)

#define MCM_ISCR_FIOC_MASK                       (0x100U)
#define MCM_ISCR_FIOC_SHIFT                      (8U)
/*! FIOC - FPU invalid operation interrupt status
 *  0b0..No interrupt
 *  0b1..Interrupt occurred
 */
#define MCM_ISCR_FIOC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIOC_SHIFT)) & MCM_ISCR_FIOC_MASK)

#define MCM_ISCR_FDZC_MASK                       (0x200U)
#define MCM_ISCR_FDZC_SHIFT                      (9U)
/*! FDZC - FPU divide-by-zero interrupt status
 *  0b0..No interrupt
 *  0b1..Interrupt occurred
 */
#define MCM_ISCR_FDZC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FDZC_SHIFT)) & MCM_ISCR_FDZC_MASK)

#define MCM_ISCR_FOFC_MASK                       (0x400U)
#define MCM_ISCR_FOFC_SHIFT                      (10U)
/*! FOFC - FPU overflow interrupt status
 *  0b0..No interrupt
 *  0b1..Interrupt occurred
 */
#define MCM_ISCR_FOFC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FOFC_SHIFT)) & MCM_ISCR_FOFC_MASK)

#define MCM_ISCR_FUFC_MASK                       (0x800U)
#define MCM_ISCR_FUFC_SHIFT                      (11U)
/*! FUFC - FPU underflow interrupt status
 *  0b0..No interrupt
 *  0b1..Interrupt occurred
 */
#define MCM_ISCR_FUFC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FUFC_SHIFT)) & MCM_ISCR_FUFC_MASK)

#define MCM_ISCR_FIXC_MASK                       (0x1000U)
#define MCM_ISCR_FIXC_SHIFT                      (12U)
/*! FIXC - FPU inexact interrupt status
 *  0b0..No interrupt
 *  0b1..Interrupt occurred
 */
#define MCM_ISCR_FIXC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIXC_SHIFT)) & MCM_ISCR_FIXC_MASK)

#define MCM_ISCR_FIDC_MASK                       (0x8000U)
#define MCM_ISCR_FIDC_SHIFT                      (15U)
/*! FIDC - FPU input denormal interrupt status
 *  0b0..No interrupt
 *  0b1..Interrupt occurred
 */
#define MCM_ISCR_FIDC(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIDC_SHIFT)) & MCM_ISCR_FIDC_MASK)

#define MCM_ISCR_CWBEE_MASK                      (0x100000U)
#define MCM_ISCR_CWBEE_SHIFT                     (20U)
/*! CWBEE - Cache write buffer error enable
 *  0b0..Disable error interrupt
 *  0b1..Enable error interrupt
 */
#define MCM_ISCR_CWBEE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_CWBEE_SHIFT)) & MCM_ISCR_CWBEE_MASK)

#define MCM_ISCR_WABE_MASK                       (0x200000U)
#define MCM_ISCR_WABE_SHIFT                      (21U)
/*! WABE - TCM Write Abort Interrupt enable
 *  0b0..Disable interrupt
 *  0b1..Enable interrupt
 */
#define MCM_ISCR_WABE(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_WABE_SHIFT)) & MCM_ISCR_WABE_MASK)

#define MCM_ISCR_FIOCE_MASK                      (0x1000000U)
#define MCM_ISCR_FIOCE_SHIFT                     (24U)
/*! FIOCE - FPU invalid operation interrupt enable
 *  0b0..Disable interrupt
 *  0b1..Enable interrupt
 */
#define MCM_ISCR_FIOCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIOCE_SHIFT)) & MCM_ISCR_FIOCE_MASK)

#define MCM_ISCR_FDZCE_MASK                      (0x2000000U)
#define MCM_ISCR_FDZCE_SHIFT                     (25U)
/*! FDZCE - FPU divide-by-zero interrupt enable
 *  0b0..Disable interrupt
 *  0b1..Enable interrupt
 */
#define MCM_ISCR_FDZCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FDZCE_SHIFT)) & MCM_ISCR_FDZCE_MASK)

#define MCM_ISCR_FOFCE_MASK                      (0x4000000U)
#define MCM_ISCR_FOFCE_SHIFT                     (26U)
/*! FOFCE - FPU overflow interrupt enable
 *  0b0..Disable interrupt
 *  0b1..Enable interrupt
 */
#define MCM_ISCR_FOFCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FOFCE_SHIFT)) & MCM_ISCR_FOFCE_MASK)

#define MCM_ISCR_FUFCE_MASK                      (0x8000000U)
#define MCM_ISCR_FUFCE_SHIFT                     (27U)
/*! FUFCE - FPU underflow interrupt enable
 *  0b0..Disable interrupt
 *  0b1..Enable interrupt
 */
#define MCM_ISCR_FUFCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FUFCE_SHIFT)) & MCM_ISCR_FUFCE_MASK)

#define MCM_ISCR_FIXCE_MASK                      (0x10000000U)
#define MCM_ISCR_FIXCE_SHIFT                     (28U)
/*! FIXCE - FPU inexact interrupt enable
 *  0b0..Disable interrupt
 *  0b1..Enable interrupt
 */
#define MCM_ISCR_FIXCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIXCE_SHIFT)) & MCM_ISCR_FIXCE_MASK)

#define MCM_ISCR_FIDCE_MASK                      (0x80000000U)
#define MCM_ISCR_FIDCE_SHIFT                     (31U)
/*! FIDCE - FPU input denormal interrupt enable
 *  0b0..Disable interrupt
 *  0b1..Enable interrupt
 */
#define MCM_ISCR_FIDCE(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_ISCR_FIDCE_SHIFT)) & MCM_ISCR_FIDCE_MASK)
/*! @} */

/*! @name FADR - Fault address register */
/*! @{ */

#define MCM_FADR_ADDRESS_MASK                    (0xFFFFFFFFU)
#define MCM_FADR_ADDRESS_SHIFT                   (0U)
/*! ADDRESS - Fault address */
#define MCM_FADR_ADDRESS(x)                      (((uint32_t)(((uint32_t)(x)) << MCM_FADR_ADDRESS_SHIFT)) & MCM_FADR_ADDRESS_MASK)
/*! @} */

/*! @name FATR - Fault attributes register */
/*! @{ */

#define MCM_FATR_BEDA_MASK                       (0x1U)
#define MCM_FATR_BEDA_SHIFT                      (0U)
/*! BEDA - Bus error access type
 *  0b0..Instruction
 *  0b1..Data
 */
#define MCM_FATR_BEDA(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_FATR_BEDA_SHIFT)) & MCM_FATR_BEDA_MASK)

#define MCM_FATR_BEMD_MASK                       (0x2U)
#define MCM_FATR_BEMD_SHIFT                      (1U)
/*! BEMD - Bus error privilege level
 *  0b0..User mode
 *  0b1..Supervisor/privileged mode
 */
#define MCM_FATR_BEMD(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_FATR_BEMD_SHIFT)) & MCM_FATR_BEMD_MASK)

#define MCM_FATR_BESZ_MASK                       (0x30U)
#define MCM_FATR_BESZ_SHIFT                      (4U)
/*! BESZ - Bus error size
 *  0b00..8-bit access
 *  0b01..16-bit access
 *  0b10..32-bit access
 *  0b11..Reserved
 */
#define MCM_FATR_BESZ(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_FATR_BESZ_SHIFT)) & MCM_FATR_BESZ_MASK)

#define MCM_FATR_BEWT_MASK                       (0x80U)
#define MCM_FATR_BEWT_SHIFT                      (7U)
/*! BEWT - Bus error write
 *  0b0..Read access
 *  0b1..Write access
 */
#define MCM_FATR_BEWT(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_FATR_BEWT_SHIFT)) & MCM_FATR_BEWT_MASK)

#define MCM_FATR_BEMN_MASK                       (0xF00U)
#define MCM_FATR_BEMN_SHIFT                      (8U)
/*! BEMN - Bus error master number */
#define MCM_FATR_BEMN(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_FATR_BEMN_SHIFT)) & MCM_FATR_BEMN_MASK)

#define MCM_FATR_BEOVR_MASK                      (0x80000000U)
#define MCM_FATR_BEOVR_SHIFT                     (31U)
/*! BEOVR - Bus error overrun
 *  0b0..No bus error overrun
 *  0b1..Bus error overrun occurred. The FADR and FDR registers and the other FATR bits are not updated to reflect this new bus error.
 */
#define MCM_FATR_BEOVR(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_FATR_BEOVR_SHIFT)) & MCM_FATR_BEOVR_MASK)
/*! @} */

/*! @name FDR - Fault data register */
/*! @{ */

#define MCM_FDR_DATA_MASK                        (0xFFFFFFFFU)
#define MCM_FDR_DATA_SHIFT                       (0U)
/*! DATA - Fault data */
#define MCM_FDR_DATA(x)                          (((uint32_t)(((uint32_t)(x)) << MCM_FDR_DATA_SHIFT)) & MCM_FDR_DATA_MASK)
/*! @} */

/*! @name LMDR - Local Memory Descriptor Register */
/*! @{ */

#define MCM_LMDR_CF0_MASK                        (0xFU)
#define MCM_LMDR_CF0_SHIFT                       (0U)
/*! CF0 - Control Field 0 */
#define MCM_LMDR_CF0(x)                          (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_CF0_SHIFT)) & MCM_LMDR_CF0_MASK)

#define MCM_LMDR_CF1_MASK                        (0xF0U)
#define MCM_LMDR_CF1_SHIFT                       (4U)
/*! CF1 - Control Field 1 - for Cache Parity control functions */
#define MCM_LMDR_CF1(x)                          (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_CF1_SHIFT)) & MCM_LMDR_CF1_MASK)

#define MCM_LMDR_MT_MASK                         (0xE000U)
#define MCM_LMDR_MT_SHIFT                        (13U)
/*! MT - Memory Type
 *  0b000..code TCM
 *  0b001..system TCM
 *  0b010..PC Cache
 *  0b011..PS Cache
 */
#define MCM_LMDR_MT(x)                           (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_MT_SHIFT)) & MCM_LMDR_MT_MASK)

#define MCM_LMDR_RO_MASK                         (0x10000U)
#define MCM_LMDR_RO_SHIFT                        (16U)
/*! RO
 *  0b0..Writes to the LMDRn[7:0] are allowed.
 *  0b1..Writes to the LMDRn[7:0] are ignored.
 */
#define MCM_LMDR_RO(x)                           (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_RO_SHIFT)) & MCM_LMDR_RO_MASK)

#define MCM_LMDR_DPW_MASK                        (0xE0000U)
#define MCM_LMDR_DPW_SHIFT                       (17U)
/*! DPW
 *  0b000-0b001..Reserved
 *  0b010..LMEMn 32-bits wide
 *  0b011..LMEMn 64-bits wide
 *  0b100-0b111..Reserved
 */
#define MCM_LMDR_DPW(x)                          (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_DPW_SHIFT)) & MCM_LMDR_DPW_MASK)

#define MCM_LMDR_WY_MASK                         (0xF00000U)
#define MCM_LMDR_WY_SHIFT                        (20U)
/*! WY - Level 1 Cache Ways
 *  0b0000..No Cache
 *  0b0010..2-Way Set Associative
 *  0b0100..4-Way Set Associative
 */
#define MCM_LMDR_WY(x)                           (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_WY_SHIFT)) & MCM_LMDR_WY_MASK)

#define MCM_LMDR_LMSZ_MASK                       (0xF000000U)
#define MCM_LMDR_LMSZ_SHIFT                      (24U)
/*! LMSZ
 *  0b0000..no LMEMn (0 KB)
 *  0b0001..1 KB LMEMn
 *  0b0010..2 KB LMEMn
 *  0b0011..4 KB LMEMn
 *  0b0100..8 KB LMEMn
 *  0b0101..16 KB LMEMn
 *  0b0110..32 KB LMEMn
 *  0b0111..64 KB LMEMn
 *  0b1000..128 KB LMEMn
 *  0b1001..256 KB LMEMn
 *  0b1010..512 KB LMEMn
 *  0b1011..1024 KB LMEMn
 *  0b1100..2048 KB LMEMn
 *  0b1101..4096 KB LMEMn
 *  0b1110..8192 KB LMEMn
 *  0b1111..16384 KB LMEMn
 */
#define MCM_LMDR_LMSZ(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_LMSZ_SHIFT)) & MCM_LMDR_LMSZ_MASK)

#define MCM_LMDR_LMSZH_MASK                      (0x10000000U)
#define MCM_LMDR_LMSZH_SHIFT                     (28U)
/*! LMSZH
 *  0b0..LMEMn is a power-of-2 capacity.
 *  0b1..LMEMn is not a power-of-2, with a capacity is 0.75 * LMSZ.
 */
#define MCM_LMDR_LMSZH(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_LMSZH_SHIFT)) & MCM_LMDR_LMSZH_MASK)

#define MCM_LMDR_V_MASK                          (0x80000000U)
#define MCM_LMDR_V_SHIFT                         (31U)
/*! V
 *  0b0..LMEMn is not present.
 *  0b1..LMEMn is present.
 */
#define MCM_LMDR_V(x)                            (((uint32_t)(((uint32_t)(x)) << MCM_LMDR_V_SHIFT)) & MCM_LMDR_V_MASK)
/*! @} */

/*! @name LMPECR - LMEM Parity & ECC Control Register */
/*! @{ */

#define MCM_LMPECR_ERNCR_MASK                    (0x1U)
#define MCM_LMPECR_ERNCR_SHIFT                   (0U)
/*! ERNCR - Enable RAM ECC Non-correctable Reporting
 *  0b0..reporting enabled
 *  0b1..reporting disabled
 */
#define MCM_LMPECR_ERNCR(x)                      (((uint32_t)(((uint32_t)(x)) << MCM_LMPECR_ERNCR_SHIFT)) & MCM_LMPECR_ERNCR_MASK)

#define MCM_LMPECR_ERNCI_MASK                    (0x2U)
#define MCM_LMPECR_ERNCI_SHIFT                   (1U)
/*! ERNCI
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define MCM_LMPECR_ERNCI(x)                      (((uint32_t)(((uint32_t)(x)) << MCM_LMPECR_ERNCI_SHIFT)) & MCM_LMPECR_ERNCI_MASK)

#define MCM_LMPECR_ER1BR_MASK                    (0x100U)
#define MCM_LMPECR_ER1BR_SHIFT                   (8U)
/*! ER1BR - Enable RAM ECC 1-bit Reporting
 *  0b0..reporting enabled
 *  0b1..reporting disabled
 */
#define MCM_LMPECR_ER1BR(x)                      (((uint32_t)(((uint32_t)(x)) << MCM_LMPECR_ER1BR_SHIFT)) & MCM_LMPECR_ER1BR_MASK)

#define MCM_LMPECR_ER1BI_MASK                    (0x200U)
#define MCM_LMPECR_ER1BI_SHIFT                   (9U)
/*! ER1BI - Enable RAM ECC 1-bit Interrupt
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define MCM_LMPECR_ER1BI(x)                      (((uint32_t)(((uint32_t)(x)) << MCM_LMPECR_ER1BI_SHIFT)) & MCM_LMPECR_ER1BI_MASK)

#define MCM_LMPECR_ECPR_MASK                     (0x100000U)
#define MCM_LMPECR_ECPR_SHIFT                    (20U)
/*! ECPR - Enable Cache Parity Reporting
 *  0b0..reporting enabled
 *  0b1..reporting disabled
 */
#define MCM_LMPECR_ECPR(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_LMPECR_ECPR_SHIFT)) & MCM_LMPECR_ECPR_MASK)

#define MCM_LMPECR_ECPI_MASK                     (0x200000U)
#define MCM_LMPECR_ECPI_SHIFT                    (21U)
/*! ECPI - Enable Cache Parity IRQ
 *  0b0..enabled
 *  0b1..disabled
 */
#define MCM_LMPECR_ECPI(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_LMPECR_ECPI_SHIFT)) & MCM_LMPECR_ECPI_MASK)
/*! @} */

/*! @name LMPEIR - LMEM Parity & ECC Interrupt Register */
/*! @{ */

#define MCM_LMPEIR_ENC_MASK                      (0xFFU)
#define MCM_LMPEIR_ENC_SHIFT                     (0U)
/*! ENC - ENCn = ECC Non-correctable Error n */
#define MCM_LMPEIR_ENC(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_LMPEIR_ENC_SHIFT)) & MCM_LMPEIR_ENC_MASK)

#define MCM_LMPEIR_E1B_MASK                      (0xFF00U)
#define MCM_LMPEIR_E1B_SHIFT                     (8U)
/*! E1B - E1Bn = ECC 1-bit Error n */
#define MCM_LMPEIR_E1B(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_LMPEIR_E1B_SHIFT)) & MCM_LMPEIR_E1B_MASK)

#define MCM_LMPEIR_PE_MASK                       (0xFF0000U)
#define MCM_LMPEIR_PE_SHIFT                      (16U)
/*! PE - Parity Error */
#define MCM_LMPEIR_PE(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_LMPEIR_PE_SHIFT)) & MCM_LMPEIR_PE_MASK)

#define MCM_LMPEIR_PEELOC_MASK                   (0x1F000000U)
#define MCM_LMPEIR_PEELOC_SHIFT                  (24U)
#define MCM_LMPEIR_PEELOC(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_LMPEIR_PEELOC_SHIFT)) & MCM_LMPEIR_PEELOC_MASK)

#define MCM_LMPEIR_V_MASK                        (0x80000000U)
#define MCM_LMPEIR_V_SHIFT                       (31U)
/*! V - Valid bit */
#define MCM_LMPEIR_V(x)                          (((uint32_t)(((uint32_t)(x)) << MCM_LMPEIR_V_SHIFT)) & MCM_LMPEIR_V_MASK)
/*! @} */

/*! @name LMFAR - LMEM Fault Address Register */
/*! @{ */

#define MCM_LMFAR_EFADD_MASK                     (0xFFFFFFFFU)
#define MCM_LMFAR_EFADD_SHIFT                    (0U)
/*! EFADD - ECC Fault Address */
#define MCM_LMFAR_EFADD(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_LMFAR_EFADD_SHIFT)) & MCM_LMFAR_EFADD_MASK)
/*! @} */

/*! @name LMFATR - LMEM Fault Attribute Register */
/*! @{ */

#define MCM_LMFATR_PEFPRT_MASK                   (0xFU)
#define MCM_LMFATR_PEFPRT_SHIFT                  (0U)
#define MCM_LMFATR_PEFPRT(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_LMFATR_PEFPRT_SHIFT)) & MCM_LMFATR_PEFPRT_MASK)

#define MCM_LMFATR_PEFSIZE_MASK                  (0x70U)
#define MCM_LMFATR_PEFSIZE_SHIFT                 (4U)
#define MCM_LMFATR_PEFSIZE(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_LMFATR_PEFSIZE_SHIFT)) & MCM_LMFATR_PEFSIZE_MASK)

#define MCM_LMFATR_PEFW_MASK                     (0x80U)
#define MCM_LMFATR_PEFW_SHIFT                    (7U)
#define MCM_LMFATR_PEFW(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_LMFATR_PEFW_SHIFT)) & MCM_LMFATR_PEFW_MASK)

#define MCM_LMFATR_PEFMST_MASK                   (0xFF00U)
#define MCM_LMFATR_PEFMST_SHIFT                  (8U)
#define MCM_LMFATR_PEFMST(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_LMFATR_PEFMST_SHIFT)) & MCM_LMFATR_PEFMST_MASK)

#define MCM_LMFATR_WORDID_MASK                   (0x1000000U)
#define MCM_LMFATR_WORDID_SHIFT                  (24U)
#define MCM_LMFATR_WORDID(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_LMFATR_WORDID_SHIFT)) & MCM_LMFATR_WORDID_MASK)

#define MCM_LMFATR_OVR_MASK                      (0x80000000U)
#define MCM_LMFATR_OVR_SHIFT                     (31U)
/*! OVR - Overrun */
#define MCM_LMFATR_OVR(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_LMFATR_OVR_SHIFT)) & MCM_LMFATR_OVR_MASK)
/*! @} */

/*! @name LMFDHR - LMEM Fault Data High Register */
/*! @{ */

#define MCM_LMFDHR_PEFDH_MASK                    (0xFFFFFFFFU)
#define MCM_LMFDHR_PEFDH_SHIFT                   (0U)
#define MCM_LMFDHR_PEFDH(x)                      (((uint32_t)(((uint32_t)(x)) << MCM_LMFDHR_PEFDH_SHIFT)) & MCM_LMFDHR_PEFDH_MASK)
/*! @} */

/*! @name LMFDLR - LMEM Fault Data Low Register */
/*! @{ */

#define MCM_LMFDLR_PEFDL_MASK                    (0xFFFFFFFFU)
#define MCM_LMFDLR_PEFDL_SHIFT                   (0U)
#define MCM_LMFDLR_PEFDL(x)                      (((uint32_t)(((uint32_t)(x)) << MCM_LMFDLR_PEFDL_SHIFT)) & MCM_LMFDLR_PEFDL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/*!
 * @}
 */ /* end of group MCM_Peripheral_Access_Layer */


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


#endif  /* PERI_MCM_H_ */

