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
**         CMSIS Peripheral Access Layer for ENC
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
 * @file PERI_ENC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for ENC
 *
 * CMSIS Peripheral Access Layer for ENC
 */

#if !defined(PERI_ENC_H_)
#define PERI_ENC_H_                              /**< Symbol preventing repeated inclusion */

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
   -- ENC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENC_Peripheral_Access_Layer ENC Peripheral Access Layer
 * @{
 */

/** ENC - Register Layout Typedef */
typedef struct {
  __IO uint16_t CTRL;                              /**< Control, offset: 0x0 */
  __IO uint16_t FILT;                              /**< Input Filter, offset: 0x2 */
  __IO uint16_t WTR;                               /**< Watchdog Timeout, offset: 0x4 */
  __IO uint16_t POSD;                              /**< Position Difference Counter, offset: 0x6 */
  __I  uint16_t POSDH;                             /**< Position Difference Hold, offset: 0x8 */
  __IO uint16_t REV;                               /**< Revolution Counter, offset: 0xA */
  __I  uint16_t REVH;                              /**< Revolution Hold, offset: 0xC */
  __IO uint16_t UPOS;                              /**< Upper Position Counter, offset: 0xE */
  __IO uint16_t LPOS;                              /**< Lower Position Counter, offset: 0x10 */
  __I  uint16_t UPOSH;                             /**< Upper Position Hold, offset: 0x12 */
  __I  uint16_t LPOSH;                             /**< Lower Position Hold, offset: 0x14 */
  __IO uint16_t UINIT;                             /**< Upper Initialization, offset: 0x16 */
  __IO uint16_t LINIT;                             /**< Lower Initialization, offset: 0x18 */
  __I  uint16_t IMR;                               /**< Input Monitor, offset: 0x1A */
  __IO uint16_t TST;                               /**< Test, offset: 0x1C */
  __IO uint16_t CTRL2;                             /**< Control 2, offset: 0x1E */
  __IO uint16_t UMOD;                              /**< Upper Modulus, offset: 0x20 */
  __IO uint16_t LMOD;                              /**< Lower Modulus, offset: 0x22 */
  __IO uint16_t UCOMP;                             /**< Upper Position Compare, offset: 0x24 */
  __IO uint16_t LCOMP;                             /**< Lower Position Compare, offset: 0x26 */
  __I  uint16_t LASTEDGE;                          /**< Last Edge Time, offset: 0x28 */
  __I  uint16_t LASTEDGEH;                         /**< Last Edge Time Hold, offset: 0x2A */
  __I  uint16_t POSDPER;                           /**< Position Difference Period Counter, offset: 0x2C */
  __I  uint16_t POSDPERBFR;                        /**< Position Difference Period Buffer, offset: 0x2E */
  __I  uint16_t POSDPERH;                          /**< Position Difference Period Hold, offset: 0x30 */
  __IO uint16_t CTRL3;                             /**< Control 3, offset: 0x32 */
} ENC_Type;

/* ----------------------------------------------------------------------------
   -- ENC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ENC_Register_Masks ENC Register Masks
 * @{
 */

/*! @name CTRL - Control */
/*! @{ */

#define ENC_CTRL_CMPIE_MASK                      (0x1U)
#define ENC_CTRL_CMPIE_SHIFT                     (0U)
/*! CMPIE - Compare Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL_CMPIE(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_CMPIE_SHIFT)) & ENC_CTRL_CMPIE_MASK)

#define ENC_CTRL_CMPIRQ_MASK                     (0x2U)
#define ENC_CTRL_CMPIRQ_SHIFT                    (1U)
/*! CMPIRQ - Compare Interrupt Request
 *  0b0..No match has occurred
 *  0b1..COMP match has occurred
 */
#define ENC_CTRL_CMPIRQ(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_CMPIRQ_SHIFT)) & ENC_CTRL_CMPIRQ_MASK)

#define ENC_CTRL_WDE_MASK                        (0x4U)
#define ENC_CTRL_WDE_SHIFT                       (2U)
/*! WDE - Watchdog Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL_WDE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_WDE_SHIFT)) & ENC_CTRL_WDE_MASK)

#define ENC_CTRL_DIE_MASK                        (0x8U)
#define ENC_CTRL_DIE_SHIFT                       (3U)
/*! DIE - Watchdog Timeout Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL_DIE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_DIE_SHIFT)) & ENC_CTRL_DIE_MASK)

#define ENC_CTRL_DIRQ_MASK                       (0x10U)
#define ENC_CTRL_DIRQ_SHIFT                      (4U)
/*! DIRQ - Watchdog Timeout Interrupt Request
 *  0b0..Not occurred
 *  0b1..Occurred
 */
#define ENC_CTRL_DIRQ(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_DIRQ_SHIFT)) & ENC_CTRL_DIRQ_MASK)

#define ENC_CTRL_XNE_MASK                        (0x20U)
#define ENC_CTRL_XNE_SHIFT                       (5U)
/*! XNE - Select Positive and Negative Edge of INDEX Pulse
 *  0b0..Use positive edge
 *  0b1..Use negative edge
 */
#define ENC_CTRL_XNE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XNE_SHIFT)) & ENC_CTRL_XNE_MASK)

#define ENC_CTRL_XIP_MASK                        (0x40U)
#define ENC_CTRL_XIP_SHIFT                       (6U)
/*! XIP - INDEX Triggered Initialization of Position Counters UPOS and LPOS
 *  0b0..Does not initialize
 *  0b1..Initializes
 */
#define ENC_CTRL_XIP(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XIP_SHIFT)) & ENC_CTRL_XIP_MASK)

#define ENC_CTRL_XIE_MASK                        (0x80U)
#define ENC_CTRL_XIE_SHIFT                       (7U)
/*! XIE - INDEX Pulse Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL_XIE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XIE_SHIFT)) & ENC_CTRL_XIE_MASK)

#define ENC_CTRL_XIRQ_MASK                       (0x100U)
#define ENC_CTRL_XIRQ_SHIFT                      (8U)
/*! XIRQ - INDEX Pulse Interrupt Request
 *  0b0..Not occurred
 *  0b1..Occurred
 */
#define ENC_CTRL_XIRQ(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_XIRQ_SHIFT)) & ENC_CTRL_XIRQ_MASK)

#define ENC_CTRL_PH1_MASK                        (0x200U)
#define ENC_CTRL_PH1_SHIFT                       (9U)
/*! PH1 - Enable Signal Phase Count Mode
 *  0b0..Uses the standard quadrature decoder, where PHASEA and PHASEB represent a two-phase quadrature signal.
 *  0b1..Bypasses the quadrature decoder. A positive transition of the PHASEA input generates a count signal.
 *       PHASEB input and CTRL[REV] controls the counter direction. If the value of CTRL[REV] and PHASEB are identical;
 *       then count is up. If the value of CTRL[REV] and PHASEB is different, then count is down.
 */
#define ENC_CTRL_PH1(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_PH1_SHIFT)) & ENC_CTRL_PH1_MASK)

#define ENC_CTRL_REV_MASK                        (0x400U)
#define ENC_CTRL_REV_SHIFT                       (10U)
/*! REV - Enable Reverse Direction Counting
 *  0b0..Counts normally
 *  0b1..Counts in the reverse direction
 */
#define ENC_CTRL_REV(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_REV_SHIFT)) & ENC_CTRL_REV_MASK)

#define ENC_CTRL_SWIP_MASK                       (0x800U)
#define ENC_CTRL_SWIP_SHIFT                      (11U)
/*! SWIP - Software-Triggered Initialization of Position Counters UPOS and LPOS
 *  0b0..No action
 *  0b1..Initialize position counter
 */
#define ENC_CTRL_SWIP(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_SWIP_SHIFT)) & ENC_CTRL_SWIP_MASK)

#define ENC_CTRL_HNE_MASK                        (0x1000U)
#define ENC_CTRL_HNE_SHIFT                       (12U)
/*! HNE - Use Negative Edge of HOME Input
 *  0b0..Use positive-going edge-to-trigger initialization of position counters UPOS and LPOS
 *  0b1..Use negative-going edge-to-trigger initialization of position counters UPOS and LPOS
 */
#define ENC_CTRL_HNE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HNE_SHIFT)) & ENC_CTRL_HNE_MASK)

#define ENC_CTRL_HIP_MASK                        (0x2000U)
#define ENC_CTRL_HIP_SHIFT                       (13U)
/*! HIP - Enable HOME to Initialize Position Counters UPOS and LPOS
 *  0b0..No action
 *  0b1..HOME signal initializes the position counter
 */
#define ENC_CTRL_HIP(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HIP_SHIFT)) & ENC_CTRL_HIP_MASK)

#define ENC_CTRL_HIE_MASK                        (0x4000U)
#define ENC_CTRL_HIE_SHIFT                       (14U)
/*! HIE - HOME Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL_HIE(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HIE_SHIFT)) & ENC_CTRL_HIE_MASK)

#define ENC_CTRL_HIRQ_MASK                       (0x8000U)
#define ENC_CTRL_HIRQ_SHIFT                      (15U)
/*! HIRQ - HOME Signal Transition Interrupt Request
 *  0b0..Not occurred
 *  0b1..Occurred
 */
#define ENC_CTRL_HIRQ(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL_HIRQ_SHIFT)) & ENC_CTRL_HIRQ_MASK)
/*! @} */

/*! @name FILT - Input Filter */
/*! @{ */

#define ENC_FILT_FILT_PER_MASK                   (0xFFU)
#define ENC_FILT_FILT_PER_SHIFT                  (0U)
/*! FILT_PER - Input Filter Sample Period */
#define ENC_FILT_FILT_PER(x)                     (((uint16_t)(((uint16_t)(x)) << ENC_FILT_FILT_PER_SHIFT)) & ENC_FILT_FILT_PER_MASK)

#define ENC_FILT_FILT_CNT_MASK                   (0x700U)
#define ENC_FILT_FILT_CNT_SHIFT                  (8U)
/*! FILT_CNT - Input Filter Sample Count */
#define ENC_FILT_FILT_CNT(x)                     (((uint16_t)(((uint16_t)(x)) << ENC_FILT_FILT_CNT_SHIFT)) & ENC_FILT_FILT_CNT_MASK)

#define ENC_FILT_FILT_PRSC_MASK                  (0xE000U)
#define ENC_FILT_FILT_PRSC_SHIFT                 (13U)
/*! FILT_PRSC - Prescaler Divide IPBus Clock to FILT Clock */
#define ENC_FILT_FILT_PRSC(x)                    (((uint16_t)(((uint16_t)(x)) << ENC_FILT_FILT_PRSC_SHIFT)) & ENC_FILT_FILT_PRSC_MASK)
/*! @} */

/*! @name WTR - Watchdog Timeout */
/*! @{ */

#define ENC_WTR_WDOG_MASK                        (0xFFFFU)
#define ENC_WTR_WDOG_SHIFT                       (0U)
/*! WDOG - WDOG */
#define ENC_WTR_WDOG(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_WTR_WDOG_SHIFT)) & ENC_WTR_WDOG_MASK)
/*! @} */

/*! @name POSD - Position Difference Counter */
/*! @{ */

#define ENC_POSD_POSD_MASK                       (0xFFFFU)
#define ENC_POSD_POSD_SHIFT                      (0U)
/*! POSD - POSD */
#define ENC_POSD_POSD(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_POSD_POSD_SHIFT)) & ENC_POSD_POSD_MASK)
/*! @} */

/*! @name POSDH - Position Difference Hold */
/*! @{ */

#define ENC_POSDH_POSDH_MASK                     (0xFFFFU)
#define ENC_POSDH_POSDH_SHIFT                    (0U)
/*! POSDH - POSDH */
#define ENC_POSDH_POSDH(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_POSDH_POSDH_SHIFT)) & ENC_POSDH_POSDH_MASK)
/*! @} */

/*! @name REV - Revolution Counter */
/*! @{ */

#define ENC_REV_REV_MASK                         (0xFFFFU)
#define ENC_REV_REV_SHIFT                        (0U)
/*! REV - REV */
#define ENC_REV_REV(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_REV_REV_SHIFT)) & ENC_REV_REV_MASK)
/*! @} */

/*! @name REVH - Revolution Hold */
/*! @{ */

#define ENC_REVH_REVH_MASK                       (0xFFFFU)
#define ENC_REVH_REVH_SHIFT                      (0U)
/*! REVH - REVH */
#define ENC_REVH_REVH(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_REVH_REVH_SHIFT)) & ENC_REVH_REVH_MASK)
/*! @} */

/*! @name UPOS - Upper Position Counter */
/*! @{ */

#define ENC_UPOS_POS_MASK                        (0xFFFFU)
#define ENC_UPOS_POS_SHIFT                       (0U)
/*! POS - POS */
#define ENC_UPOS_POS(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_UPOS_POS_SHIFT)) & ENC_UPOS_POS_MASK)
/*! @} */

/*! @name LPOS - Lower Position Counter */
/*! @{ */

#define ENC_LPOS_POS_MASK                        (0xFFFFU)
#define ENC_LPOS_POS_SHIFT                       (0U)
/*! POS - POS */
#define ENC_LPOS_POS(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_LPOS_POS_SHIFT)) & ENC_LPOS_POS_MASK)
/*! @} */

/*! @name UPOSH - Upper Position Hold */
/*! @{ */

#define ENC_UPOSH_POSH_MASK                      (0xFFFFU)
#define ENC_UPOSH_POSH_SHIFT                     (0U)
/*! POSH - POSH */
#define ENC_UPOSH_POSH(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_UPOSH_POSH_SHIFT)) & ENC_UPOSH_POSH_MASK)
/*! @} */

/*! @name LPOSH - Lower Position Hold */
/*! @{ */

#define ENC_LPOSH_POSH_MASK                      (0xFFFFU)
#define ENC_LPOSH_POSH_SHIFT                     (0U)
/*! POSH - POSH */
#define ENC_LPOSH_POSH(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_LPOSH_POSH_SHIFT)) & ENC_LPOSH_POSH_MASK)
/*! @} */

/*! @name UINIT - Upper Initialization */
/*! @{ */

#define ENC_UINIT_INIT_MASK                      (0xFFFFU)
#define ENC_UINIT_INIT_SHIFT                     (0U)
/*! INIT - INIT */
#define ENC_UINIT_INIT(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_UINIT_INIT_SHIFT)) & ENC_UINIT_INIT_MASK)
/*! @} */

/*! @name LINIT - Lower Initialization */
/*! @{ */

#define ENC_LINIT_INIT_MASK                      (0xFFFFU)
#define ENC_LINIT_INIT_SHIFT                     (0U)
/*! INIT - INIT */
#define ENC_LINIT_INIT(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_LINIT_INIT_SHIFT)) & ENC_LINIT_INIT_MASK)
/*! @} */

/*! @name IMR - Input Monitor */
/*! @{ */

#define ENC_IMR_HOME_MASK                        (0x1U)
#define ENC_IMR_HOME_SHIFT                       (0U)
/*! HOME - HOME */
#define ENC_IMR_HOME(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_HOME_SHIFT)) & ENC_IMR_HOME_MASK)

#define ENC_IMR_INDEX_MASK                       (0x2U)
#define ENC_IMR_INDEX_SHIFT                      (1U)
/*! INDEX - INDEX */
#define ENC_IMR_INDEX(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_IMR_INDEX_SHIFT)) & ENC_IMR_INDEX_MASK)

#define ENC_IMR_PHB_MASK                         (0x4U)
#define ENC_IMR_PHB_SHIFT                        (2U)
/*! PHB - PHB */
#define ENC_IMR_PHB(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_IMR_PHB_SHIFT)) & ENC_IMR_PHB_MASK)

#define ENC_IMR_PHA_MASK                         (0x8U)
#define ENC_IMR_PHA_SHIFT                        (3U)
/*! PHA - PHA */
#define ENC_IMR_PHA(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_IMR_PHA_SHIFT)) & ENC_IMR_PHA_MASK)

#define ENC_IMR_FHOM_MASK                        (0x10U)
#define ENC_IMR_FHOM_SHIFT                       (4U)
/*! FHOM - FHOM */
#define ENC_IMR_FHOM(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FHOM_SHIFT)) & ENC_IMR_FHOM_MASK)

#define ENC_IMR_FIND_MASK                        (0x20U)
#define ENC_IMR_FIND_SHIFT                       (5U)
/*! FIND - FIND */
#define ENC_IMR_FIND(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FIND_SHIFT)) & ENC_IMR_FIND_MASK)

#define ENC_IMR_FPHB_MASK                        (0x40U)
#define ENC_IMR_FPHB_SHIFT                       (6U)
/*! FPHB - FPHB */
#define ENC_IMR_FPHB(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FPHB_SHIFT)) & ENC_IMR_FPHB_MASK)

#define ENC_IMR_FPHA_MASK                        (0x80U)
#define ENC_IMR_FPHA_SHIFT                       (7U)
/*! FPHA - FPHA */
#define ENC_IMR_FPHA(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_IMR_FPHA_SHIFT)) & ENC_IMR_FPHA_MASK)
/*! @} */

/*! @name TST - Test */
/*! @{ */

#define ENC_TST_TEST_COUNT_MASK                  (0xFFU)
#define ENC_TST_TEST_COUNT_SHIFT                 (0U)
/*! TEST_COUNT - TEST_COUNT */
#define ENC_TST_TEST_COUNT(x)                    (((uint16_t)(((uint16_t)(x)) << ENC_TST_TEST_COUNT_SHIFT)) & ENC_TST_TEST_COUNT_MASK)

#define ENC_TST_TEST_PERIOD_MASK                 (0x1F00U)
#define ENC_TST_TEST_PERIOD_SHIFT                (8U)
/*! TEST_PERIOD - TEST_PERIOD */
#define ENC_TST_TEST_PERIOD(x)                   (((uint16_t)(((uint16_t)(x)) << ENC_TST_TEST_PERIOD_SHIFT)) & ENC_TST_TEST_PERIOD_MASK)

#define ENC_TST_QDN_MASK                         (0x2000U)
#define ENC_TST_QDN_SHIFT                        (13U)
/*! QDN - Quadrature Decoder Negative Signal
 *  0b0..Positive quadrature decoder signal
 *  0b1..Negative quadrature decoder signal
 */
#define ENC_TST_QDN(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_TST_QDN_SHIFT)) & ENC_TST_QDN_MASK)

#define ENC_TST_TCE_MASK                         (0x4000U)
#define ENC_TST_TCE_SHIFT                        (14U)
/*! TCE - Test Counter Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_TST_TCE(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_TST_TCE_SHIFT)) & ENC_TST_TCE_MASK)

#define ENC_TST_TEN_MASK                         (0x8000U)
#define ENC_TST_TEN_SHIFT                        (15U)
/*! TEN - Test Mode Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_TST_TEN(x)                           (((uint16_t)(((uint16_t)(x)) << ENC_TST_TEN_SHIFT)) & ENC_TST_TEN_MASK)
/*! @} */

/*! @name CTRL2 - Control 2 */
/*! @{ */

#define ENC_CTRL2_UPDHLD_MASK                    (0x1U)
#define ENC_CTRL2_UPDHLD_SHIFT                   (0U)
/*! UPDHLD - Update Hold Registers
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL2_UPDHLD(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_UPDHLD_SHIFT)) & ENC_CTRL2_UPDHLD_MASK)

#define ENC_CTRL2_UPDPOS_MASK                    (0x2U)
#define ENC_CTRL2_UPDPOS_SHIFT                   (1U)
/*! UPDPOS - Update Position Registers
 *  0b0..No action
 *  0b1..Clear
 */
#define ENC_CTRL2_UPDPOS(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_UPDPOS_SHIFT)) & ENC_CTRL2_UPDPOS_MASK)

#define ENC_CTRL2_MOD_MASK                       (0x4U)
#define ENC_CTRL2_MOD_SHIFT                      (2U)
/*! MOD - Enable Modulo Counting
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL2_MOD(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_MOD_SHIFT)) & ENC_CTRL2_MOD_MASK)

#define ENC_CTRL2_DIR_MASK                       (0x8U)
#define ENC_CTRL2_DIR_SHIFT                      (3U)
/*! DIR - Count Direction Flag
 *  0b0..Down direction
 *  0b1..Up direction
 */
#define ENC_CTRL2_DIR(x)                         (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_DIR_SHIFT)) & ENC_CTRL2_DIR_MASK)

#define ENC_CTRL2_RUIE_MASK                      (0x10U)
#define ENC_CTRL2_RUIE_SHIFT                     (4U)
/*! RUIE - Roll-under Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL2_RUIE(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_RUIE_SHIFT)) & ENC_CTRL2_RUIE_MASK)

#define ENC_CTRL2_RUIRQ_MASK                     (0x20U)
#define ENC_CTRL2_RUIRQ_SHIFT                    (5U)
/*! RUIRQ - Roll-under Interrupt Request
 *  0b0..No roll-under has occurred
 *  0b1..Roll-under has occurred
 */
#define ENC_CTRL2_RUIRQ(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_RUIRQ_SHIFT)) & ENC_CTRL2_RUIRQ_MASK)

#define ENC_CTRL2_ROIE_MASK                      (0x40U)
#define ENC_CTRL2_ROIE_SHIFT                     (6U)
/*! ROIE - Roll-over Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL2_ROIE(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_ROIE_SHIFT)) & ENC_CTRL2_ROIE_MASK)

#define ENC_CTRL2_ROIRQ_MASK                     (0x80U)
#define ENC_CTRL2_ROIRQ_SHIFT                    (7U)
/*! ROIRQ - Roll-over Interrupt Request
 *  0b0..Did not occur
 *  0b1..Occurred
 */
#define ENC_CTRL2_ROIRQ(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_ROIRQ_SHIFT)) & ENC_CTRL2_ROIRQ_MASK)

#define ENC_CTRL2_REVMOD_MASK                    (0x100U)
#define ENC_CTRL2_REVMOD_SHIFT                   (8U)
/*! REVMOD - Revolution Counter Modulus Enable
 *  0b0..Use INDEX pulse
 *  0b1..Use modulus counting roll-over or roll-under
 */
#define ENC_CTRL2_REVMOD(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_REVMOD_SHIFT)) & ENC_CTRL2_REVMOD_MASK)

#define ENC_CTRL2_OUTCTL_MASK                    (0x200U)
#define ENC_CTRL2_OUTCTL_SHIFT                   (9U)
/*! OUTCTL - Output Control
 *  0b0..POSMATCH pulses when a match occurs between the position counters (POS) and the corresponding compare value (COMP )
 *  0b1..POSMATCH pulses when the UPOS, LPOS, REV, or POSD registers are read
 */
#define ENC_CTRL2_OUTCTL(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_OUTCTL_SHIFT)) & ENC_CTRL2_OUTCTL_MASK)

#define ENC_CTRL2_SABIE_MASK                     (0x400U)
#define ENC_CTRL2_SABIE_SHIFT                    (10U)
/*! SABIE - Simultaneous PHASEA and PHASEB Change Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ENC_CTRL2_SABIE(x)                       (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_SABIE_SHIFT)) & ENC_CTRL2_SABIE_MASK)

#define ENC_CTRL2_SABIRQ_MASK                    (0x800U)
#define ENC_CTRL2_SABIRQ_SHIFT                   (11U)
/*! SABIRQ - Simultaneous PHASEA and PHASEB Change Interrupt Request
 *  0b0..No simultaneous change has occurred
 *  0b1..A simultaneous change has occurred
 */
#define ENC_CTRL2_SABIRQ(x)                      (((uint16_t)(((uint16_t)(x)) << ENC_CTRL2_SABIRQ_SHIFT)) & ENC_CTRL2_SABIRQ_MASK)
/*! @} */

/*! @name UMOD - Upper Modulus */
/*! @{ */

#define ENC_UMOD_MOD_MASK                        (0xFFFFU)
#define ENC_UMOD_MOD_SHIFT                       (0U)
/*! MOD - MOD */
#define ENC_UMOD_MOD(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_UMOD_MOD_SHIFT)) & ENC_UMOD_MOD_MASK)
/*! @} */

/*! @name LMOD - Lower Modulus */
/*! @{ */

#define ENC_LMOD_MOD_MASK                        (0xFFFFU)
#define ENC_LMOD_MOD_SHIFT                       (0U)
/*! MOD - MOD */
#define ENC_LMOD_MOD(x)                          (((uint16_t)(((uint16_t)(x)) << ENC_LMOD_MOD_SHIFT)) & ENC_LMOD_MOD_MASK)
/*! @} */

/*! @name UCOMP - Upper Position Compare */
/*! @{ */

#define ENC_UCOMP_COMP_MASK                      (0xFFFFU)
#define ENC_UCOMP_COMP_SHIFT                     (0U)
/*! COMP - COMP */
#define ENC_UCOMP_COMP(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_UCOMP_COMP_SHIFT)) & ENC_UCOMP_COMP_MASK)
/*! @} */

/*! @name LCOMP - Lower Position Compare */
/*! @{ */

#define ENC_LCOMP_COMP_MASK                      (0xFFFFU)
#define ENC_LCOMP_COMP_SHIFT                     (0U)
/*! COMP - COMP */
#define ENC_LCOMP_COMP(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_LCOMP_COMP_SHIFT)) & ENC_LCOMP_COMP_MASK)
/*! @} */

/*! @name LASTEDGE - Last Edge Time */
/*! @{ */

#define ENC_LASTEDGE_LASTEDGE_MASK               (0xFFFFU)
#define ENC_LASTEDGE_LASTEDGE_SHIFT              (0U)
/*! LASTEDGE - Last Edge Time Counter */
#define ENC_LASTEDGE_LASTEDGE(x)                 (((uint16_t)(((uint16_t)(x)) << ENC_LASTEDGE_LASTEDGE_SHIFT)) & ENC_LASTEDGE_LASTEDGE_MASK)
/*! @} */

/*! @name LASTEDGEH - Last Edge Time Hold */
/*! @{ */

#define ENC_LASTEDGEH_LASTEDGEH_MASK             (0xFFFFU)
#define ENC_LASTEDGEH_LASTEDGEH_SHIFT            (0U)
/*! LASTEDGEH - Last Edge Time Hold */
#define ENC_LASTEDGEH_LASTEDGEH(x)               (((uint16_t)(((uint16_t)(x)) << ENC_LASTEDGEH_LASTEDGEH_SHIFT)) & ENC_LASTEDGEH_LASTEDGEH_MASK)
/*! @} */

/*! @name POSDPER - Position Difference Period Counter */
/*! @{ */

#define ENC_POSDPER_POSDPER_MASK                 (0xFFFFU)
#define ENC_POSDPER_POSDPER_SHIFT                (0U)
/*! POSDPER - Position difference period */
#define ENC_POSDPER_POSDPER(x)                   (((uint16_t)(((uint16_t)(x)) << ENC_POSDPER_POSDPER_SHIFT)) & ENC_POSDPER_POSDPER_MASK)
/*! @} */

/*! @name POSDPERBFR - Position Difference Period Buffer */
/*! @{ */

#define ENC_POSDPERBFR_POSDPERBFR_MASK           (0xFFFFU)
#define ENC_POSDPERBFR_POSDPERBFR_SHIFT          (0U)
/*! POSDPERBFR - Position difference period buffer */
#define ENC_POSDPERBFR_POSDPERBFR(x)             (((uint16_t)(((uint16_t)(x)) << ENC_POSDPERBFR_POSDPERBFR_SHIFT)) & ENC_POSDPERBFR_POSDPERBFR_MASK)
/*! @} */

/*! @name POSDPERH - Position Difference Period Hold */
/*! @{ */

#define ENC_POSDPERH_POSDPERH_MASK               (0xFFFFU)
#define ENC_POSDPERH_POSDPERH_SHIFT              (0U)
/*! POSDPERH - Position difference period hold */
#define ENC_POSDPERH_POSDPERH(x)                 (((uint16_t)(((uint16_t)(x)) << ENC_POSDPERH_POSDPERH_SHIFT)) & ENC_POSDPERH_POSDPERH_MASK)
/*! @} */

/*! @name CTRL3 - Control 3 */
/*! @{ */

#define ENC_CTRL3_PMEN_MASK                      (0x1U)
#define ENC_CTRL3_PMEN_SHIFT                     (0U)
/*! PMEN - Period Measurement Function Enable
 *  0b0..Not used
 *  0b1..Used
 */
#define ENC_CTRL3_PMEN(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL3_PMEN_SHIFT)) & ENC_CTRL3_PMEN_MASK)

#define ENC_CTRL3_PRSC_MASK                      (0xF0U)
#define ENC_CTRL3_PRSC_SHIFT                     (4U)
/*! PRSC - Prescaler */
#define ENC_CTRL3_PRSC(x)                        (((uint16_t)(((uint16_t)(x)) << ENC_CTRL3_PRSC_SHIFT)) & ENC_CTRL3_PRSC_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ENC_Register_Masks */


/*!
 * @}
 */ /* end of group ENC_Peripheral_Access_Layer */


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


#endif  /* PERI_ENC_H_ */

