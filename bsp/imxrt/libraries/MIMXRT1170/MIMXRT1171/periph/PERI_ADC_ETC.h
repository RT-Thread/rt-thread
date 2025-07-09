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
**         CMSIS Peripheral Access Layer for ADC_ETC
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
 * @file PERI_ADC_ETC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for ADC_ETC
 *
 * CMSIS Peripheral Access Layer for ADC_ETC
 */

#if !defined(PERI_ADC_ETC_H_)
#define PERI_ADC_ETC_H_                          /**< Symbol preventing repeated inclusion */

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
   -- ADC_ETC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_ETC_Peripheral_Access_Layer ADC_ETC Peripheral Access Layer
 * @{
 */

/** ADC_ETC - Size of Registers Arrays */
#define ADC_ETC_TRIG_COUNT                        8u

/** ADC_ETC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< ADC_ETC Global Control Register, offset: 0x0 */
  __IO uint32_t DONE0_1_IRQ;                       /**< ETC DONE0 and DONE1 IRQ State Register, offset: 0x4 */
  __IO uint32_t DONE2_3_ERR_IRQ;                   /**< ETC DONE_2, DONE_3 and DONE_ERR IRQ State Register, offset: 0x8 */
  __IO uint32_t DMA_CTRL;                          /**< ETC DMA control Register, offset: 0xC */
  struct {                                         /* offset: 0x10, array step: 0x28 */
    __IO uint32_t TRIGn_CTRL;                        /**< ETC_TRIG Control Register, array offset: 0x10, array step: 0x28 */
    __IO uint32_t TRIGn_COUNTER;                     /**< ETC_TRIG Counter Register, array offset: 0x14, array step: 0x28 */
    __IO uint32_t TRIGn_CHAIN_1_0;                   /**< ETC_TRIG Chain 0/1 Register, array offset: 0x18, array step: 0x28 */
    __IO uint32_t TRIGn_CHAIN_3_2;                   /**< ETC_TRIG Chain 2/3 Register, array offset: 0x1C, array step: 0x28 */
    __IO uint32_t TRIGn_CHAIN_5_4;                   /**< ETC_TRIG Chain 4/5 Register, array offset: 0x20, array step: 0x28 */
    __IO uint32_t TRIGn_CHAIN_7_6;                   /**< ETC_TRIG Chain 6/7 Register, array offset: 0x24, array step: 0x28 */
    __I  uint32_t TRIGn_RESULT_1_0;                  /**< ETC_TRIG Result Data 1/0 Register, array offset: 0x28, array step: 0x28 */
    __I  uint32_t TRIGn_RESULT_3_2;                  /**< ETC_TRIG Result Data 3/2 Register, array offset: 0x2C, array step: 0x28 */
    __I  uint32_t TRIGn_RESULT_5_4;                  /**< ETC_TRIG Result Data 5/4 Register, array offset: 0x30, array step: 0x28 */
    __I  uint32_t TRIGn_RESULT_7_6;                  /**< ETC_TRIG Result Data 7/6 Register, array offset: 0x34, array step: 0x28 */
  } TRIG[ADC_ETC_TRIG_COUNT];
} ADC_ETC_Type;

/* ----------------------------------------------------------------------------
   -- ADC_ETC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_ETC_Register_Masks ADC_ETC Register Masks
 * @{
 */

/*! @name CTRL - ADC_ETC Global Control Register */
/*! @{ */

#define ADC_ETC_CTRL_TRIG_ENABLE_MASK            (0xFFU)
#define ADC_ETC_CTRL_TRIG_ENABLE_SHIFT           (0U)
/*! TRIG_ENABLE
 *  0b00000000..disable all 8 external XBAR triggers.
 *  0b00000001..enable external XBAR trigger0.
 *  0b00000010..enable external XBAR trigger1.
 *  0b00000011..enable external XBAR trigger0 and trigger1.
 *  0b11111111..enable all 8 external XBAR triggers.
 */
#define ADC_ETC_CTRL_TRIG_ENABLE(x)              (((uint32_t)(((uint32_t)(x)) << ADC_ETC_CTRL_TRIG_ENABLE_SHIFT)) & ADC_ETC_CTRL_TRIG_ENABLE_MASK)

#define ADC_ETC_CTRL_PRE_DIVIDER_MASK            (0xFF0000U)
#define ADC_ETC_CTRL_PRE_DIVIDER_SHIFT           (16U)
#define ADC_ETC_CTRL_PRE_DIVIDER(x)              (((uint32_t)(((uint32_t)(x)) << ADC_ETC_CTRL_PRE_DIVIDER_SHIFT)) & ADC_ETC_CTRL_PRE_DIVIDER_MASK)

#define ADC_ETC_CTRL_DMA_MODE_SEL_MASK           (0x20000000U)
#define ADC_ETC_CTRL_DMA_MODE_SEL_SHIFT          (29U)
/*! DMA_MODE_SEL
 *  0b0..Trig DMA_REQ with latched signal, REQ will be cleared when ACK and source request cleared.
 *  0b1..Trig DMA_REQ with pulsed signal, REQ will be cleared by ACK only.
 */
#define ADC_ETC_CTRL_DMA_MODE_SEL(x)             (((uint32_t)(((uint32_t)(x)) << ADC_ETC_CTRL_DMA_MODE_SEL_SHIFT)) & ADC_ETC_CTRL_DMA_MODE_SEL_MASK)

#define ADC_ETC_CTRL_SOFTRST_MASK                (0x80000000U)
#define ADC_ETC_CTRL_SOFTRST_SHIFT               (31U)
/*! SOFTRST
 *  0b0..ADC_ETC works normally.
 *  0b1..All registers inside ADC_ETC will be reset to the default value.
 */
#define ADC_ETC_CTRL_SOFTRST(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ETC_CTRL_SOFTRST_SHIFT)) & ADC_ETC_CTRL_SOFTRST_MASK)
/*! @} */

/*! @name DONE0_1_IRQ - ETC DONE0 and DONE1 IRQ State Register */
/*! @{ */

#define ADC_ETC_DONE0_1_IRQ_TRIG0_DONE0_MASK     (0x1U)
#define ADC_ETC_DONE0_1_IRQ_TRIG0_DONE0_SHIFT    (0U)
/*! TRIG0_DONE0
 *  0b0..No TRIG0_DONE0 interrupt detected
 *  0b1..TRIG0_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG0_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG0_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG0_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG1_DONE0_MASK     (0x2U)
#define ADC_ETC_DONE0_1_IRQ_TRIG1_DONE0_SHIFT    (1U)
/*! TRIG1_DONE0
 *  0b0..No TRIG1_DONE0 interrupt detected
 *  0b1..TRIG1_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG1_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG1_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG1_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG2_DONE0_MASK     (0x4U)
#define ADC_ETC_DONE0_1_IRQ_TRIG2_DONE0_SHIFT    (2U)
/*! TRIG2_DONE0
 *  0b0..No TRIG2_DONE0 interrupt detected
 *  0b1..TRIG2_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG2_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG2_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG2_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG3_DONE0_MASK     (0x8U)
#define ADC_ETC_DONE0_1_IRQ_TRIG3_DONE0_SHIFT    (3U)
/*! TRIG3_DONE0
 *  0b0..No TRIG3_DONE0 interrupt detected
 *  0b1..TRIG3_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG3_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG3_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG3_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG4_DONE0_MASK     (0x10U)
#define ADC_ETC_DONE0_1_IRQ_TRIG4_DONE0_SHIFT    (4U)
/*! TRIG4_DONE0
 *  0b0..No TRIG4_DONE0 interrupt detected
 *  0b1..TRIG4_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG4_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG4_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG4_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG5_DONE0_MASK     (0x20U)
#define ADC_ETC_DONE0_1_IRQ_TRIG5_DONE0_SHIFT    (5U)
/*! TRIG5_DONE0
 *  0b0..No TRIG5_DONE0 interrupt detected
 *  0b1..TRIG5_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG5_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG5_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG5_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG6_DONE0_MASK     (0x40U)
#define ADC_ETC_DONE0_1_IRQ_TRIG6_DONE0_SHIFT    (6U)
/*! TRIG6_DONE0
 *  0b0..No TRIG6_DONE0 interrupt detected
 *  0b1..TRIG6_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG6_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG6_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG6_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG7_DONE0_MASK     (0x80U)
#define ADC_ETC_DONE0_1_IRQ_TRIG7_DONE0_SHIFT    (7U)
/*! TRIG7_DONE0
 *  0b0..No TRIG7_DONE0 interrupt detected
 *  0b1..TRIG7_DONE0 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG7_DONE0(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG7_DONE0_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG7_DONE0_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG0_DONE1_MASK     (0x10000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG0_DONE1_SHIFT    (16U)
/*! TRIG0_DONE1
 *  0b0..No TRIG0_DONE1 interrupt detected
 *  0b1..TRIG0_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG0_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG0_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG0_DONE1_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG1_DONE1_MASK     (0x20000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG1_DONE1_SHIFT    (17U)
/*! TRIG1_DONE1
 *  0b0..No TRIG1_DONE1 interrupt detected
 *  0b1..TRIG1_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG1_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG1_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG1_DONE1_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG2_DONE1_MASK     (0x40000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG2_DONE1_SHIFT    (18U)
/*! TRIG2_DONE1
 *  0b0..No TRIG2_DONE1 interrupt detected
 *  0b1..TRIG2_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG2_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG2_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG2_DONE1_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG3_DONE1_MASK     (0x80000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG3_DONE1_SHIFT    (19U)
/*! TRIG3_DONE1
 *  0b0..No TRIG3_DONE1 interrupt detected
 *  0b1..TRIG3_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG3_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG3_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG3_DONE1_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG4_DONE1_MASK     (0x100000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG4_DONE1_SHIFT    (20U)
/*! TRIG4_DONE1
 *  0b0..No TRIG4_DONE1 interrupt detected
 *  0b1..TRIG4_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG4_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG4_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG4_DONE1_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG5_DONE1_MASK     (0x200000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG5_DONE1_SHIFT    (21U)
/*! TRIG5_DONE1
 *  0b0..No TRIG5_DONE1 interrupt detected
 *  0b1..TRIG5_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG5_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG5_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG5_DONE1_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG6_DONE1_MASK     (0x400000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG6_DONE1_SHIFT    (22U)
/*! TRIG6_DONE1
 *  0b0..No TRIG6_DONE1 interrupt detected
 *  0b1..TRIG6_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG6_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG6_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG6_DONE1_MASK)

#define ADC_ETC_DONE0_1_IRQ_TRIG7_DONE1_MASK     (0x800000U)
#define ADC_ETC_DONE0_1_IRQ_TRIG7_DONE1_SHIFT    (23U)
/*! TRIG7_DONE1
 *  0b0..No TRIG7_DONE1 interrupt detected
 *  0b1..TRIG7_DONE1 interrupt detected
 */
#define ADC_ETC_DONE0_1_IRQ_TRIG7_DONE1(x)       (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE0_1_IRQ_TRIG7_DONE1_SHIFT)) & ADC_ETC_DONE0_1_IRQ_TRIG7_DONE1_MASK)
/*! @} */

/*! @name DONE2_3_ERR_IRQ - ETC DONE_2, DONE_3 and DONE_ERR IRQ State Register */
/*! @{ */

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE2_MASK (0x1U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE2_SHIFT (0U)
/*! TRIG0_DONE2
 *  0b0..No TRIG0_DONE2 interrupt detected
 *  0b1..TRIG0_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE2_MASK (0x2U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE2_SHIFT (1U)
/*! TRIG1_DONE2
 *  0b0..No TRIG1_DONE2 interrupt detected
 *  0b1..TRIG1_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE2_MASK (0x4U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE2_SHIFT (2U)
/*! TRIG2_DONE2
 *  0b0..No TRIG2_DONE2 interrupt detected
 *  0b1..TRIG2_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE2_MASK (0x8U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE2_SHIFT (3U)
/*! TRIG3_DONE2
 *  0b0..No TRIG3_DONE2 interrupt detected
 *  0b1..TRIG3_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE2_MASK (0x10U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE2_SHIFT (4U)
/*! TRIG4_DONE2
 *  0b0..No TRIG4_DONE2 interrupt detected
 *  0b1..TRIG4_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE2_MASK (0x20U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE2_SHIFT (5U)
/*! TRIG5_DONE2
 *  0b0..No TRIG5_DONE2 interrupt detected
 *  0b1..TRIG5_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE2_MASK (0x40U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE2_SHIFT (6U)
/*! TRIG6_DONE2
 *  0b0..No TRIG6_DONE2 interrupt detected
 *  0b1..TRIG6_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE2_MASK (0x80U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE2_SHIFT (7U)
/*! TRIG7_DONE2
 *  0b0..No TRIG7_DONE2 interrupt detected
 *  0b1..TRIG7_DONE2 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE2(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE2_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE2_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE3_MASK (0x100U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE3_SHIFT (8U)
/*! TRIG0_DONE3
 *  0b0..No TRIG0_DONE3 interrupt detected
 *  0b1..TRIG0_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE3_MASK (0x200U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE3_SHIFT (9U)
/*! TRIG1_DONE3
 *  0b0..No TRIG1_DONE3 interrupt detected
 *  0b1..TRIG1_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE3_MASK (0x400U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE3_SHIFT (10U)
/*! TRIG2_DONE3
 *  0b0..No TRIG2_DONE3 interrupt detected
 *  0b1..TRIG2_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE3_MASK (0x800U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE3_SHIFT (11U)
/*! TRIG3_DONE3
 *  0b0..No TRIG3_DONE3 interrupt detected
 *  0b1..TRIG3_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE3_MASK (0x1000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE3_SHIFT (12U)
/*! TRIG4_DONE3
 *  0b0..No TRIG4_DONE3 interrupt detected
 *  0b1..TRIG4_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE3_MASK (0x2000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE3_SHIFT (13U)
/*! TRIG5_DONE3
 *  0b0..No TRIG5_DONE3 interrupt detected
 *  0b1..TRIG5_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE3_MASK (0x4000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE3_SHIFT (14U)
/*! TRIG6_DONE3
 *  0b0..No TRIG6_DONE3 interrupt detected
 *  0b1..TRIG6_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE3_MASK (0x8000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE3_SHIFT (15U)
/*! TRIG7_DONE3
 *  0b0..No TRIG7_DONE3 interrupt detected
 *  0b1..TRIG7_DONE3 interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE3(x)   (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE3_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_DONE3_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_ERR_MASK   (0x10000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_ERR_SHIFT  (16U)
/*! TRIG0_ERR
 *  0b0..No TRIG0_ERR interrupt detected
 *  0b1..TRIG0_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG0_ERR_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_ERR_MASK   (0x20000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_ERR_SHIFT  (17U)
/*! TRIG1_ERR
 *  0b0..No TRIG1_ERR interrupt detected
 *  0b1..TRIG1_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG1_ERR_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_ERR_MASK   (0x40000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_ERR_SHIFT  (18U)
/*! TRIG2_ERR
 *  0b0..No TRIG2_ERR interrupt detected
 *  0b1..TRIG2_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG2_ERR_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_ERR_MASK   (0x80000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_ERR_SHIFT  (19U)
/*! TRIG3_ERR
 *  0b0..No TRIG3_ERR interrupt detected
 *  0b1..TRIG3_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG3_ERR_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_ERR_MASK   (0x100000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_ERR_SHIFT  (20U)
/*! TRIG4_ERR
 *  0b0..No TRIG4_ERR interrupt detected
 *  0b1..TRIG4_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG4_ERR_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_ERR_MASK   (0x200000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_ERR_SHIFT  (21U)
/*! TRIG5_ERR
 *  0b0..No TRIG5_ERR interrupt detected
 *  0b1..TRIG5_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG5_ERR_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_ERR_MASK   (0x400000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_ERR_SHIFT  (22U)
/*! TRIG6_ERR
 *  0b0..No TRIG6_ERR interrupt detected
 *  0b1..TRIG6_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG6_ERR_MASK)

#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_ERR_MASK   (0x800000U)
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_ERR_SHIFT  (23U)
/*! TRIG7_ERR
 *  0b0..No TRIG7_ERR interrupt detected
 *  0b1..TRIG7_ERR interrupt detected
 */
#define ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_ERR(x)     (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_ERR_SHIFT)) & ADC_ETC_DONE2_3_ERR_IRQ_TRIG7_ERR_MASK)
/*! @} */

/*! @name DMA_CTRL - ETC DMA control Register */
/*! @{ */

#define ADC_ETC_DMA_CTRL_TRIG0_ENABLE_MASK       (0x1U)
#define ADC_ETC_DMA_CTRL_TRIG0_ENABLE_SHIFT      (0U)
/*! TRIG0_ENABLE
 *  0b0..TRIG0 DMA request disabled.
 *  0b1..TRIG0 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG0_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG0_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG0_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG1_ENABLE_MASK       (0x2U)
#define ADC_ETC_DMA_CTRL_TRIG1_ENABLE_SHIFT      (1U)
/*! TRIG1_ENABLE
 *  0b0..TRIG1 DMA request disabled.
 *  0b1..TRIG1 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG1_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG1_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG1_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG2_ENABLE_MASK       (0x4U)
#define ADC_ETC_DMA_CTRL_TRIG2_ENABLE_SHIFT      (2U)
/*! TRIG2_ENABLE
 *  0b0..TRIG2 DMA request disabled.
 *  0b1..TRIG2 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG2_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG2_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG2_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG3_ENABLE_MASK       (0x8U)
#define ADC_ETC_DMA_CTRL_TRIG3_ENABLE_SHIFT      (3U)
/*! TRIG3_ENABLE
 *  0b0..TRIG3 DMA request disabled.
 *  0b1..TRIG3 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG3_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG3_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG3_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG4_ENABLE_MASK       (0x10U)
#define ADC_ETC_DMA_CTRL_TRIG4_ENABLE_SHIFT      (4U)
/*! TRIG4_ENABLE
 *  0b0..TRIG4 DMA request disabled.
 *  0b1..TRIG4 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG4_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG4_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG4_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG5_ENABLE_MASK       (0x20U)
#define ADC_ETC_DMA_CTRL_TRIG5_ENABLE_SHIFT      (5U)
/*! TRIG5_ENABLE
 *  0b0..TRIG5 DMA request disabled.
 *  0b1..TRIG5 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG5_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG5_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG5_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG6_ENABLE_MASK       (0x40U)
#define ADC_ETC_DMA_CTRL_TRIG6_ENABLE_SHIFT      (6U)
/*! TRIG6_ENABLE
 *  0b0..TRIG6 DMA request disabled.
 *  0b1..TRIG6 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG6_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG6_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG6_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG7_ENABLE_MASK       (0x80U)
#define ADC_ETC_DMA_CTRL_TRIG7_ENABLE_SHIFT      (7U)
/*! TRIG7_ENABLE
 *  0b0..TRIG7 DMA request disabled.
 *  0b1..TRIG7 DMA request enabled.
 */
#define ADC_ETC_DMA_CTRL_TRIG7_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG7_ENABLE_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG7_ENABLE_MASK)

#define ADC_ETC_DMA_CTRL_TRIG0_REQ_MASK          (0x10000U)
#define ADC_ETC_DMA_CTRL_TRIG0_REQ_SHIFT         (16U)
/*! TRIG0_REQ
 *  0b0..TRIG0_REQ not detected.
 *  0b1..TRIG0_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG0_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG0_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG0_REQ_MASK)

#define ADC_ETC_DMA_CTRL_TRIG1_REQ_MASK          (0x20000U)
#define ADC_ETC_DMA_CTRL_TRIG1_REQ_SHIFT         (17U)
/*! TRIG1_REQ
 *  0b0..TRIG1_REQ not detected.
 *  0b1..TRIG1_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG1_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG1_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG1_REQ_MASK)

#define ADC_ETC_DMA_CTRL_TRIG2_REQ_MASK          (0x40000U)
#define ADC_ETC_DMA_CTRL_TRIG2_REQ_SHIFT         (18U)
/*! TRIG2_REQ
 *  0b0..TRIG2_REQ not detected.
 *  0b1..TRIG2_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG2_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG2_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG2_REQ_MASK)

#define ADC_ETC_DMA_CTRL_TRIG3_REQ_MASK          (0x80000U)
#define ADC_ETC_DMA_CTRL_TRIG3_REQ_SHIFT         (19U)
/*! TRIG3_REQ
 *  0b0..TRIG3_REQ not detected.
 *  0b1..TRIG3_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG3_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG3_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG3_REQ_MASK)

#define ADC_ETC_DMA_CTRL_TRIG4_REQ_MASK          (0x100000U)
#define ADC_ETC_DMA_CTRL_TRIG4_REQ_SHIFT         (20U)
/*! TRIG4_REQ
 *  0b0..TRIG4_REQ not detected.
 *  0b1..TRIG4_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG4_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG4_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG4_REQ_MASK)

#define ADC_ETC_DMA_CTRL_TRIG5_REQ_MASK          (0x200000U)
#define ADC_ETC_DMA_CTRL_TRIG5_REQ_SHIFT         (21U)
/*! TRIG5_REQ
 *  0b0..TRIG5_REQ not detected.
 *  0b1..TRIG5_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG5_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG5_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG5_REQ_MASK)

#define ADC_ETC_DMA_CTRL_TRIG6_REQ_MASK          (0x400000U)
#define ADC_ETC_DMA_CTRL_TRIG6_REQ_SHIFT         (22U)
/*! TRIG6_REQ
 *  0b0..TRIG6_REQ not detected.
 *  0b1..TRIG6_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG6_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG6_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG6_REQ_MASK)

#define ADC_ETC_DMA_CTRL_TRIG7_REQ_MASK          (0x800000U)
#define ADC_ETC_DMA_CTRL_TRIG7_REQ_SHIFT         (23U)
/*! TRIG7_REQ
 *  0b0..TRIG7_REQ not detected.
 *  0b1..TRIG7_REQ detected.
 */
#define ADC_ETC_DMA_CTRL_TRIG7_REQ(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_DMA_CTRL_TRIG7_REQ_SHIFT)) & ADC_ETC_DMA_CTRL_TRIG7_REQ_MASK)
/*! @} */

/*! @name TRIGn_CTRL - ETC_TRIG Control Register */
/*! @{ */

#define ADC_ETC_TRIGn_CTRL_SW_TRIG_MASK          (0x1U)
#define ADC_ETC_TRIGn_CTRL_SW_TRIG_SHIFT         (0U)
/*! SW_TRIG
 *  0b0..No software trigger event generated.
 *  0b1..Software trigger event generated.
 */
#define ADC_ETC_TRIGn_CTRL_SW_TRIG(x)            (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CTRL_SW_TRIG_SHIFT)) & ADC_ETC_TRIGn_CTRL_SW_TRIG_MASK)

#define ADC_ETC_TRIGn_CTRL_TRIG_MODE_MASK        (0x10U)
#define ADC_ETC_TRIGn_CTRL_TRIG_MODE_SHIFT       (4U)
/*! TRIG_MODE
 *  0b0..Hardware trigger. The softerware trigger will be ignored.
 *  0b1..Software trigger. The hardware trigger will be ignored.
 */
#define ADC_ETC_TRIGn_CTRL_TRIG_MODE(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CTRL_TRIG_MODE_SHIFT)) & ADC_ETC_TRIGn_CTRL_TRIG_MODE_MASK)

#define ADC_ETC_TRIGn_CTRL_TRIG_CHAIN_MASK       (0x700U)
#define ADC_ETC_TRIGn_CTRL_TRIG_CHAIN_SHIFT      (8U)
/*! TRIG_CHAIN
 *  0b000..Trigger chain length is 1
 *  0b001..Trigger chain length is 2
 *  0b010..Trigger chain length is 3
 *  0b011..Trigger chain length is 4
 *  0b100..Trigger chain length is 5
 *  0b101..Trigger chain length is 6
 *  0b110..Trigger chain length is 7
 *  0b111..Trigger chain length is 8
 */
#define ADC_ETC_TRIGn_CTRL_TRIG_CHAIN(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CTRL_TRIG_CHAIN_SHIFT)) & ADC_ETC_TRIGn_CTRL_TRIG_CHAIN_MASK)

#define ADC_ETC_TRIGn_CTRL_TRIG_PRIORITY_MASK    (0x7000U)
#define ADC_ETC_TRIGn_CTRL_TRIG_PRIORITY_SHIFT   (12U)
#define ADC_ETC_TRIGn_CTRL_TRIG_PRIORITY(x)      (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CTRL_TRIG_PRIORITY_SHIFT)) & ADC_ETC_TRIGn_CTRL_TRIG_PRIORITY_MASK)

#define ADC_ETC_TRIGn_CTRL_SYNC_MODE_MASK        (0x10000U)
#define ADC_ETC_TRIGn_CTRL_SYNC_MODE_SHIFT       (16U)
/*! SYNC_MODE
 *  0b0..Synchronization mode disabled, TRIGa and TRIG(a+4) are triggered independently.
 *  0b1..Synchronization mode enabled, TRIGa and TRIG(a+4) are triggered by TRIGa source synchronously.
 */
#define ADC_ETC_TRIGn_CTRL_SYNC_MODE(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CTRL_SYNC_MODE_SHIFT)) & ADC_ETC_TRIGn_CTRL_SYNC_MODE_MASK)

#define ADC_ETC_TRIGn_CTRL_CHAINx_DONE_MASK      (0xFF000000U)
#define ADC_ETC_TRIGn_CTRL_CHAINx_DONE_SHIFT     (24U)
/*! CHAINx_DONE
 *  0b00000000..segment x done not detected.
 *  0b00000001..segment x done detected.
 */
#define ADC_ETC_TRIGn_CTRL_CHAINx_DONE(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CTRL_CHAINx_DONE_SHIFT)) & ADC_ETC_TRIGn_CTRL_CHAINx_DONE_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_CTRL */
#define ADC_ETC_TRIGn_CTRL_COUNT                 (8U)

/*! @name TRIGn_COUNTER - ETC_TRIG Counter Register */
/*! @{ */

#define ADC_ETC_TRIGn_COUNTER_INIT_DELAY_MASK    (0xFFFFU)
#define ADC_ETC_TRIGn_COUNTER_INIT_DELAY_SHIFT   (0U)
#define ADC_ETC_TRIGn_COUNTER_INIT_DELAY(x)      (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_COUNTER_INIT_DELAY_SHIFT)) & ADC_ETC_TRIGn_COUNTER_INIT_DELAY_MASK)

#define ADC_ETC_TRIGn_COUNTER_SAMPLE_INTERVAL_MASK (0xFFFF0000U)
#define ADC_ETC_TRIGn_COUNTER_SAMPLE_INTERVAL_SHIFT (16U)
#define ADC_ETC_TRIGn_COUNTER_SAMPLE_INTERVAL(x) (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_COUNTER_SAMPLE_INTERVAL_SHIFT)) & ADC_ETC_TRIGn_COUNTER_SAMPLE_INTERVAL_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_COUNTER */
#define ADC_ETC_TRIGn_COUNTER_COUNT              (8U)

/*! @name TRIGn_CHAIN_1_0 - ETC_TRIG Chain 0/1 Register */
/*! @{ */

#define ADC_ETC_TRIGn_CHAIN_1_0_CSEL0_MASK       (0xFU)
#define ADC_ETC_TRIGn_CHAIN_1_0_CSEL0_SHIFT      (0U)
/*! CSEL0
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_CSEL0(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_CSEL0_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_CSEL0_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_HWTS0_MASK       (0xFF0U)
#define ADC_ETC_TRIGn_CHAIN_1_0_HWTS0_SHIFT      (4U)
/*! HWTS0
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_HWTS0(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_HWTS0_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_HWTS0_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_B2B0_MASK        (0x1000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_B2B0_SHIFT       (12U)
/*! B2B0
 *  0b0..Disable B2B. Wait until delay value defined by TRIG0_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_B2B0(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_B2B0_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_B2B0_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_IE0_MASK         (0x6000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_IE0_SHIFT        (13U)
/*! IE0
 *  0b00..Generate interrupt on Done0 when segment 0 finish.
 *  0b01..Generate interrupt on Done1 when segment 0 finish.
 *  0b10..Generate interrupt on Done2 when segment 0 finish.
 *  0b11..Generate interrupt on Done3 when segment 0 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_IE0(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_IE0_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_IE0_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_IE0_EN_MASK      (0x8000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_IE0_EN_SHIFT     (15U)
/*! IE0_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 0 finish, an interrupt will be generated on the specific port configured by the IE0.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_IE0_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_IE0_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_IE0_EN_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_CSEL1_MASK       (0xF0000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_CSEL1_SHIFT      (16U)
/*! CSEL1
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_CSEL1(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_CSEL1_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_CSEL1_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_HWTS1_MASK       (0xFF00000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_HWTS1_SHIFT      (20U)
/*! HWTS1
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_HWTS1(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_HWTS1_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_HWTS1_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_B2B1_MASK        (0x10000000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_B2B1_SHIFT       (28U)
/*! B2B1
 *  0b0..Disable B2B. Wait until delay value defined by TRIG1_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_B2B1(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_B2B1_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_B2B1_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_IE1_MASK         (0x60000000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_IE1_SHIFT        (29U)
/*! IE1
 *  0b00..Generate interrupt on Done0 when Segment 1 finish.
 *  0b01..Generate interrupt on Done1 when Segment 1 finish.
 *  0b10..Generate interrupt on Done2 when Segment 1 finish.
 *  0b11..Generate interrupt on Done3 when Segment 1 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_IE1(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_IE1_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_IE1_MASK)

#define ADC_ETC_TRIGn_CHAIN_1_0_IE1_EN_MASK      (0x80000000U)
#define ADC_ETC_TRIGn_CHAIN_1_0_IE1_EN_SHIFT     (31U)
/*! IE1_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 1 finish, an interrupt will be generated on the specific port configured by the IE1.
 */
#define ADC_ETC_TRIGn_CHAIN_1_0_IE1_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_1_0_IE1_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_1_0_IE1_EN_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_CHAIN_1_0 */
#define ADC_ETC_TRIGn_CHAIN_1_0_COUNT            (8U)

/*! @name TRIGn_CHAIN_3_2 - ETC_TRIG Chain 2/3 Register */
/*! @{ */

#define ADC_ETC_TRIGn_CHAIN_3_2_CSEL2_MASK       (0xFU)
#define ADC_ETC_TRIGn_CHAIN_3_2_CSEL2_SHIFT      (0U)
/*! CSEL2
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_CSEL2(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_CSEL2_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_CSEL2_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_HWTS2_MASK       (0xFF0U)
#define ADC_ETC_TRIGn_CHAIN_3_2_HWTS2_SHIFT      (4U)
/*! HWTS2
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_HWTS2(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_HWTS2_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_HWTS2_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_B2B2_MASK        (0x1000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_B2B2_SHIFT       (12U)
/*! B2B2
 *  0b0..Disable B2B. Wait until delay value defined by TRIG2_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_B2B2(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_B2B2_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_B2B2_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_IE2_MASK         (0x6000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_IE2_SHIFT        (13U)
/*! IE2
 *  0b00..Generate interrupt on Done0 when segment 2 finish.
 *  0b01..Generate interrupt on Done1 when segment 2 finish.
 *  0b10..Generate interrupt on Done2 when segment 2 finish.
 *  0b11..Generate interrupt on Done3 when segment 2 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_IE2(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_IE2_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_IE2_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_IE2_EN_MASK      (0x8000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_IE2_EN_SHIFT     (15U)
/*! IE2_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 2 finish, an interrupt will be generated on the specific port configured by the IE2.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_IE2_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_IE2_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_IE2_EN_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_CSEL3_MASK       (0xF0000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_CSEL3_SHIFT      (16U)
/*! CSEL3
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_CSEL3(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_CSEL3_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_CSEL3_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_HWTS3_MASK       (0xFF00000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_HWTS3_SHIFT      (20U)
/*! HWTS3
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_HWTS3(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_HWTS3_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_HWTS3_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_B2B3_MASK        (0x10000000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_B2B3_SHIFT       (28U)
/*! B2B3
 *  0b0..Disable B2B. Wait until delay value defined by TRIG3_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_B2B3(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_B2B3_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_B2B3_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_IE3_MASK         (0x60000000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_IE3_SHIFT        (29U)
/*! IE3
 *  0b00..Generate interrupt on Done0 when segment 3 finish.
 *  0b01..Generate interrupt on Done1 when segment 3 finish.
 *  0b10..Generate interrupt on Done2 when segment 3 finish.
 *  0b11..Generate interrupt on Done3 when segment 3 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_IE3(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_IE3_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_IE3_MASK)

#define ADC_ETC_TRIGn_CHAIN_3_2_IE3_EN_MASK      (0x80000000U)
#define ADC_ETC_TRIGn_CHAIN_3_2_IE3_EN_SHIFT     (31U)
/*! IE3_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 3 finish, an interrupt will be generated on the specific port configured by the IE3.
 */
#define ADC_ETC_TRIGn_CHAIN_3_2_IE3_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_3_2_IE3_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_3_2_IE3_EN_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_CHAIN_3_2 */
#define ADC_ETC_TRIGn_CHAIN_3_2_COUNT            (8U)

/*! @name TRIGn_CHAIN_5_4 - ETC_TRIG Chain 4/5 Register */
/*! @{ */

#define ADC_ETC_TRIGn_CHAIN_5_4_CSEL4_MASK       (0xFU)
#define ADC_ETC_TRIGn_CHAIN_5_4_CSEL4_SHIFT      (0U)
/*! CSEL4
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_CSEL4(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_CSEL4_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_CSEL4_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_HWTS4_MASK       (0xFF0U)
#define ADC_ETC_TRIGn_CHAIN_5_4_HWTS4_SHIFT      (4U)
/*! HWTS4
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_HWTS4(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_HWTS4_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_HWTS4_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_B2B4_MASK        (0x1000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_B2B4_SHIFT       (12U)
/*! B2B4
 *  0b0..Disable B2B. Wait until delay value defined by TRIG4_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_B2B4(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_B2B4_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_B2B4_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_IE4_MASK         (0x6000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_IE4_SHIFT        (13U)
/*! IE4
 *  0b00..Generate interrupt on Done0 when segment 4 finish.
 *  0b01..Generate interrupt on Done1 when segment 4 finish.
 *  0b10..Generate interrupt on Done2 when segment 4 finish.
 *  0b11..Generate interrupt on Done3 when segment 4 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_IE4(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_IE4_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_IE4_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_IE4_EN_MASK      (0x8000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_IE4_EN_SHIFT     (15U)
/*! IE4_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 4 finish, an interrupt will be generated on the specific port configured by the IE4.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_IE4_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_IE4_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_IE4_EN_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_CSEL5_MASK       (0xF0000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_CSEL5_SHIFT      (16U)
/*! CSEL5
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_CSEL5(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_CSEL5_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_CSEL5_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_HWTS5_MASK       (0xFF00000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_HWTS5_SHIFT      (20U)
/*! HWTS5
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_HWTS5(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_HWTS5_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_HWTS5_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_B2B5_MASK        (0x10000000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_B2B5_SHIFT       (28U)
/*! B2B5
 *  0b0..Disable B2B. Wait until delay value defined by TRIG5_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_B2B5(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_B2B5_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_B2B5_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_IE5_MASK         (0x60000000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_IE5_SHIFT        (29U)
/*! IE5
 *  0b00..Generate interrupt on Done0 when segment 5 finish.
 *  0b01..Generate interrupt on Done1 when segment 5 finish.
 *  0b10..Generate interrupt on Done2 when segment 5 finish.
 *  0b11..Generate interrupt on Done3 when segment 5 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_IE5(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_IE5_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_IE5_MASK)

#define ADC_ETC_TRIGn_CHAIN_5_4_IE5_EN_MASK      (0x80000000U)
#define ADC_ETC_TRIGn_CHAIN_5_4_IE5_EN_SHIFT     (31U)
/*! IE5_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 5 finish, an interrupt will be generated on the specific port configured by the IE5.
 */
#define ADC_ETC_TRIGn_CHAIN_5_4_IE5_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_5_4_IE5_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_5_4_IE5_EN_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_CHAIN_5_4 */
#define ADC_ETC_TRIGn_CHAIN_5_4_COUNT            (8U)

/*! @name TRIGn_CHAIN_7_6 - ETC_TRIG Chain 6/7 Register */
/*! @{ */

#define ADC_ETC_TRIGn_CHAIN_7_6_CSEL6_MASK       (0xFU)
#define ADC_ETC_TRIGn_CHAIN_7_6_CSEL6_SHIFT      (0U)
/*! CSEL6
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_CSEL6(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_CSEL6_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_CSEL6_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_HWTS6_MASK       (0xFF0U)
#define ADC_ETC_TRIGn_CHAIN_7_6_HWTS6_SHIFT      (4U)
/*! HWTS6
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_HWTS6(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_HWTS6_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_HWTS6_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_B2B6_MASK        (0x1000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_B2B6_SHIFT       (12U)
/*! B2B6
 *  0b0..Disable B2B. Wait until delay value defined by TRIG6_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_B2B6(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_B2B6_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_B2B6_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_IE6_MASK         (0x6000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_IE6_SHIFT        (13U)
/*! IE6
 *  0b00..Generate interrupt on Done0 when segment 6 finish.
 *  0b01..Generate interrupt on Done1 when segment 6 finish.
 *  0b10..Generate interrupt on Done2 when segment 6 finish.
 *  0b11..Generate interrupt on Done3 when segment 6 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_IE6(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_IE6_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_IE6_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_IE6_EN_MASK      (0x8000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_IE6_EN_SHIFT     (15U)
/*! IE6_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 6 finish, an interrupt will be generated on the specific port configured by the IE6.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_IE6_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_IE6_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_IE6_EN_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_CSEL7_MASK       (0xF0000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_CSEL7_SHIFT      (16U)
/*! CSEL7
 *  0b0000..Not a valid selection from the command buffer. Trigger event is ignored.
 *  0b0001..ADC CMD1 selected.
 *  0b0010..ADC CMD2 selected.
 *  0b0011..ADC CMD3 selected.
 *  0b0100..ADC CMD4 selected.
 *  0b0101..ADC CMD5 selected.
 *  0b0110..ADC CMD6 selected.
 *  0b0111..ADC CMD7 selected.
 *  0b1000..ADC CMD8 selected.
 *  0b1001..ADC CMD9 selected.
 *  0b1010..ADC CMD10 selected.
 *  0b1011..ADC CMD11 selected.
 *  0b1100..ADC CMD12 selected.
 *  0b1101..ADC CMD13 selected.
 *  0b1110..ADC CMD14 selected.
 *  0b1111..ADC CMD15 selected.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_CSEL7(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_CSEL7_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_CSEL7_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_HWTS7_MASK       (0xFF00000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_HWTS7_SHIFT      (20U)
/*! HWTS7
 *  0b00000000..no trigger selected
 *  0b00000001..ADC TRIG0 selected
 *  0b00000010..ADC TRIG1 selected
 *  0b00000100..ADC TRIG2 selected
 *  0b00001000..ADC TRIG3 selected
 *  0b00010000..ADC TRIG4 selected
 *  0b00100000..ADC TRIG5 selected
 *  0b01000000..ADC TRIG6 selected
 *  0b10000000..ADC TRIG7 selected
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_HWTS7(x)         (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_HWTS7_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_HWTS7_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_B2B7_MASK        (0x10000000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_B2B7_SHIFT       (28U)
/*! B2B7
 *  0b0..Disable B2B. Wait until delay value defined by TRIG7_COUNTER[SAMPLE_INTERVAL] is reached
 *  0b1..Enable B2B. When Segment 0 finished (ADC COCO) then automatically trigger next ADC conversion, no need to wait until interval delay reached.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_B2B7(x)          (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_B2B7_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_B2B7_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_IE7_MASK         (0x60000000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_IE7_SHIFT        (29U)
/*! IE7
 *  0b00..Generate interrupt on Done0 when segment 7 finish.
 *  0b01..Generate interrupt on Done1 when segment 7 finish.
 *  0b10..Generate interrupt on Done2 when segment 7 finish.
 *  0b11..Generate interrupt on Done3 when segment 7 finish.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_IE7(x)           (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_IE7_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_IE7_MASK)

#define ADC_ETC_TRIGn_CHAIN_7_6_IE7_EN_MASK      (0x80000000U)
#define ADC_ETC_TRIGn_CHAIN_7_6_IE7_EN_SHIFT     (31U)
/*! IE7_EN
 *  0b0..Interrupt DONE disabled.
 *  0b1..Interrupt DONE enabled. When segment 7 finish, an interrupt will be generated on the specific port configured by the IE7.
 */
#define ADC_ETC_TRIGn_CHAIN_7_6_IE7_EN(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_CHAIN_7_6_IE7_EN_SHIFT)) & ADC_ETC_TRIGn_CHAIN_7_6_IE7_EN_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_CHAIN_7_6 */
#define ADC_ETC_TRIGn_CHAIN_7_6_COUNT            (8U)

/*! @name TRIGn_RESULT_1_0 - ETC_TRIG Result Data 1/0 Register */
/*! @{ */

#define ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK      (0xFFFU)
#define ADC_ETC_TRIGn_RESULT_1_0_DATA0_SHIFT     (0U)
#define ADC_ETC_TRIGn_RESULT_1_0_DATA0(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_1_0_DATA0_SHIFT)) & ADC_ETC_TRIGn_RESULT_1_0_DATA0_MASK)

#define ADC_ETC_TRIGn_RESULT_1_0_DATA1_MASK      (0xFFF0000U)
#define ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT     (16U)
#define ADC_ETC_TRIGn_RESULT_1_0_DATA1(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_1_0_DATA1_SHIFT)) & ADC_ETC_TRIGn_RESULT_1_0_DATA1_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_RESULT_1_0 */
#define ADC_ETC_TRIGn_RESULT_1_0_COUNT           (8U)

/*! @name TRIGn_RESULT_3_2 - ETC_TRIG Result Data 3/2 Register */
/*! @{ */

#define ADC_ETC_TRIGn_RESULT_3_2_DATA2_MASK      (0xFFFU)
#define ADC_ETC_TRIGn_RESULT_3_2_DATA2_SHIFT     (0U)
#define ADC_ETC_TRIGn_RESULT_3_2_DATA2(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_3_2_DATA2_SHIFT)) & ADC_ETC_TRIGn_RESULT_3_2_DATA2_MASK)

#define ADC_ETC_TRIGn_RESULT_3_2_DATA3_MASK      (0xFFF0000U)
#define ADC_ETC_TRIGn_RESULT_3_2_DATA3_SHIFT     (16U)
#define ADC_ETC_TRIGn_RESULT_3_2_DATA3(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_3_2_DATA3_SHIFT)) & ADC_ETC_TRIGn_RESULT_3_2_DATA3_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_RESULT_3_2 */
#define ADC_ETC_TRIGn_RESULT_3_2_COUNT           (8U)

/*! @name TRIGn_RESULT_5_4 - ETC_TRIG Result Data 5/4 Register */
/*! @{ */

#define ADC_ETC_TRIGn_RESULT_5_4_DATA4_MASK      (0xFFFU)
#define ADC_ETC_TRIGn_RESULT_5_4_DATA4_SHIFT     (0U)
#define ADC_ETC_TRIGn_RESULT_5_4_DATA4(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_5_4_DATA4_SHIFT)) & ADC_ETC_TRIGn_RESULT_5_4_DATA4_MASK)

#define ADC_ETC_TRIGn_RESULT_5_4_DATA5_MASK      (0xFFF0000U)
#define ADC_ETC_TRIGn_RESULT_5_4_DATA5_SHIFT     (16U)
#define ADC_ETC_TRIGn_RESULT_5_4_DATA5(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_5_4_DATA5_SHIFT)) & ADC_ETC_TRIGn_RESULT_5_4_DATA5_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_RESULT_5_4 */
#define ADC_ETC_TRIGn_RESULT_5_4_COUNT           (8U)

/*! @name TRIGn_RESULT_7_6 - ETC_TRIG Result Data 7/6 Register */
/*! @{ */

#define ADC_ETC_TRIGn_RESULT_7_6_DATA6_MASK      (0xFFFU)
#define ADC_ETC_TRIGn_RESULT_7_6_DATA6_SHIFT     (0U)
#define ADC_ETC_TRIGn_RESULT_7_6_DATA6(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_7_6_DATA6_SHIFT)) & ADC_ETC_TRIGn_RESULT_7_6_DATA6_MASK)

#define ADC_ETC_TRIGn_RESULT_7_6_DATA7_MASK      (0xFFF0000U)
#define ADC_ETC_TRIGn_RESULT_7_6_DATA7_SHIFT     (16U)
#define ADC_ETC_TRIGn_RESULT_7_6_DATA7(x)        (((uint32_t)(((uint32_t)(x)) << ADC_ETC_TRIGn_RESULT_7_6_DATA7_SHIFT)) & ADC_ETC_TRIGn_RESULT_7_6_DATA7_MASK)
/*! @} */

/* The count of ADC_ETC_TRIGn_RESULT_7_6 */
#define ADC_ETC_TRIGn_RESULT_7_6_COUNT           (8U)


/*!
 * @}
 */ /* end of group ADC_ETC_Register_Masks */


/*!
 * @}
 */ /* end of group ADC_ETC_Peripheral_Access_Layer */


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


#endif  /* PERI_ADC_ETC_H_ */

