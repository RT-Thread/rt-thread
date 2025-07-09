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
**         CMSIS Peripheral Access Layer for CMP
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
 * @file PERI_CMP.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for CMP
 *
 * CMSIS Peripheral Access Layer for CMP
 */

#if !defined(PERI_CMP_H_)
#define PERI_CMP_H_                              /**< Symbol preventing repeated inclusion */

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
   -- CMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Peripheral_Access_Layer CMP Peripheral Access Layer
 * @{
 */

/** CMP - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  __IO uint32_t C0;                                /**< CMP Control Register 0, offset: 0x8 */
  __IO uint32_t C1;                                /**< CMP Control Register 1, offset: 0xC */
  __IO uint32_t C2;                                /**< CMP Control Register 2, offset: 0x10 */
  __IO uint32_t C3;                                /**< CMP Control Register 3, offset: 0x14 */
} CMP_Type;

/* ----------------------------------------------------------------------------
   -- CMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Masks CMP Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */

#define CMP_VERID_FEATURE_MASK                   (0xFFFFU)
#define CMP_VERID_FEATURE_SHIFT                  (0U)
/*! FEATURE - Feature Specification Number. This read only filed returns the feature set number. */
#define CMP_VERID_FEATURE(x)                     (((uint32_t)(((uint32_t)(x)) << CMP_VERID_FEATURE_SHIFT)) & CMP_VERID_FEATURE_MASK)

#define CMP_VERID_MINOR_MASK                     (0xFF0000U)
#define CMP_VERID_MINOR_SHIFT                    (16U)
/*! MINOR - Minor Version Number. This read only field returns the minor version number for the module specification. */
#define CMP_VERID_MINOR(x)                       (((uint32_t)(((uint32_t)(x)) << CMP_VERID_MINOR_SHIFT)) & CMP_VERID_MINOR_MASK)

#define CMP_VERID_MAJOR_MASK                     (0xFF000000U)
#define CMP_VERID_MAJOR_SHIFT                    (24U)
/*! MAJOR - Major Version Number. This read only field returns the major version number for the module specification. */
#define CMP_VERID_MAJOR(x)                       (((uint32_t)(((uint32_t)(x)) << CMP_VERID_MAJOR_SHIFT)) & CMP_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */

#define CMP_PARAM_PARAM_MASK                     (0xFFFFFFFFU)
#define CMP_PARAM_PARAM_SHIFT                    (0U)
/*! PARAM - Parameter Registers. This read only filed returns the feature parameters implemented along with the Version ID register. */
#define CMP_PARAM_PARAM(x)                       (((uint32_t)(((uint32_t)(x)) << CMP_PARAM_PARAM_SHIFT)) & CMP_PARAM_PARAM_MASK)
/*! @} */

/*! @name C0 - CMP Control Register 0 */
/*! @{ */

#define CMP_C0_HYSTCTR_MASK                      (0x3U)
#define CMP_C0_HYSTCTR_SHIFT                     (0U)
/*! HYSTCTR - Comparator hard block hysteresis control. See chip data sheet to get the actual hystersis value with each level
 *  0b00..The hard block output has level 0 hysteresis internally.
 *  0b01..The hard block output has level 1 hysteresis internally.
 *  0b10..The hard block output has level 2 hysteresis internally.
 *  0b11..The hard block output has level 3 hysteresis internally.
 */
#define CMP_C0_HYSTCTR(x)                        (((uint32_t)(((uint32_t)(x)) << CMP_C0_HYSTCTR_SHIFT)) & CMP_C0_HYSTCTR_MASK)

#define CMP_C0_FILTER_CNT_MASK                   (0x70U)
#define CMP_C0_FILTER_CNT_SHIFT                  (4U)
/*! FILTER_CNT - Filter Sample Count
 *  0b000..Filter is disabled. If SE = 1, then COUT is a logic zero (this is not a legal state, and is not recommended). If SE = 0, COUT = COUTA.
 *  0b001..1 consecutive sample must agree (comparator output is simply sampled).
 *  0b010..2 consecutive samples must agree.
 *  0b011..3 consecutive samples must agree.
 *  0b100..4 consecutive samples must agree.
 *  0b101..5 consecutive samples must agree.
 *  0b110..6 consecutive samples must agree.
 *  0b111..7 consecutive samples must agree.
 */
#define CMP_C0_FILTER_CNT(x)                     (((uint32_t)(((uint32_t)(x)) << CMP_C0_FILTER_CNT_SHIFT)) & CMP_C0_FILTER_CNT_MASK)

#define CMP_C0_EN_MASK                           (0x100U)
#define CMP_C0_EN_SHIFT                          (8U)
/*! EN - Comparator Module Enable
 *  0b0..Analog Comparator is disabled.
 *  0b1..Analog Comparator is enabled.
 */
#define CMP_C0_EN(x)                             (((uint32_t)(((uint32_t)(x)) << CMP_C0_EN_SHIFT)) & CMP_C0_EN_MASK)

#define CMP_C0_OPE_MASK                          (0x200U)
#define CMP_C0_OPE_SHIFT                         (9U)
/*! OPE - Comparator Output Pin Enable
 *  0b0..When OPE is 0, the comparator output (after window/filter settings dependent on software configuration) is not available to a packaged pin.
 *  0b1..When OPE is 1, and if the software has configured the comparator to own a packaged pin, the comparator is available in a packaged pin.
 */
#define CMP_C0_OPE(x)                            (((uint32_t)(((uint32_t)(x)) << CMP_C0_OPE_SHIFT)) & CMP_C0_OPE_MASK)

#define CMP_C0_COS_MASK                          (0x400U)
#define CMP_C0_COS_SHIFT                         (10U)
/*! COS - Comparator Output Select
 *  0b0..Set CMPO to equal COUT (filtered comparator output).
 *  0b1..Set CMPO to equal COUTA (unfiltered comparator output).
 */
#define CMP_C0_COS(x)                            (((uint32_t)(((uint32_t)(x)) << CMP_C0_COS_SHIFT)) & CMP_C0_COS_MASK)

#define CMP_C0_INVT_MASK                         (0x800U)
#define CMP_C0_INVT_SHIFT                        (11U)
/*! INVT - Comparator invert
 *  0b0..Does not invert the comparator output.
 *  0b1..Inverts the comparator output.
 */
#define CMP_C0_INVT(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C0_INVT_SHIFT)) & CMP_C0_INVT_MASK)

#define CMP_C0_PMODE_MASK                        (0x1000U)
#define CMP_C0_PMODE_SHIFT                       (12U)
/*! PMODE - Power Mode Select
 *  0b0..Low Speed (LS) comparison mode is selected.
 *  0b1..High Speed (HS) comparison mode is selected.
 */
#define CMP_C0_PMODE(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C0_PMODE_SHIFT)) & CMP_C0_PMODE_MASK)

#define CMP_C0_WE_MASK                           (0x4000U)
#define CMP_C0_WE_SHIFT                          (14U)
/*! WE - Windowing Enable
 *  0b0..Windowing mode is not selected.
 *  0b1..Windowing mode is selected.
 */
#define CMP_C0_WE(x)                             (((uint32_t)(((uint32_t)(x)) << CMP_C0_WE_SHIFT)) & CMP_C0_WE_MASK)

#define CMP_C0_SE_MASK                           (0x8000U)
#define CMP_C0_SE_SHIFT                          (15U)
/*! SE - Sample Enable
 *  0b0..Sampling mode is not selected.
 *  0b1..Sampling mode is selected.
 */
#define CMP_C0_SE(x)                             (((uint32_t)(((uint32_t)(x)) << CMP_C0_SE_SHIFT)) & CMP_C0_SE_MASK)

#define CMP_C0_FPR_MASK                          (0xFF0000U)
#define CMP_C0_FPR_SHIFT                         (16U)
/*! FPR - Filter Sample Period */
#define CMP_C0_FPR(x)                            (((uint32_t)(((uint32_t)(x)) << CMP_C0_FPR_SHIFT)) & CMP_C0_FPR_MASK)

#define CMP_C0_COUT_MASK                         (0x1000000U)
#define CMP_C0_COUT_SHIFT                        (24U)
/*! COUT - Analog Comparator Output */
#define CMP_C0_COUT(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C0_COUT_SHIFT)) & CMP_C0_COUT_MASK)

#define CMP_C0_CFF_MASK                          (0x2000000U)
#define CMP_C0_CFF_SHIFT                         (25U)
/*! CFF - Analog Comparator Flag Falling
 *  0b0..A falling edge has not been detected on COUT.
 *  0b1..A falling edge on COUT has occurred.
 */
#define CMP_C0_CFF(x)                            (((uint32_t)(((uint32_t)(x)) << CMP_C0_CFF_SHIFT)) & CMP_C0_CFF_MASK)

#define CMP_C0_CFR_MASK                          (0x4000000U)
#define CMP_C0_CFR_SHIFT                         (26U)
/*! CFR - Analog Comparator Flag Rising
 *  0b0..A rising edge has not been detected on COUT.
 *  0b1..A rising edge on COUT has occurred.
 */
#define CMP_C0_CFR(x)                            (((uint32_t)(((uint32_t)(x)) << CMP_C0_CFR_SHIFT)) & CMP_C0_CFR_MASK)

#define CMP_C0_IEF_MASK                          (0x8000000U)
#define CMP_C0_IEF_SHIFT                         (27U)
/*! IEF - Comparator Interrupt Enable Falling
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_C0_IEF(x)                            (((uint32_t)(((uint32_t)(x)) << CMP_C0_IEF_SHIFT)) & CMP_C0_IEF_MASK)

#define CMP_C0_IER_MASK                          (0x10000000U)
#define CMP_C0_IER_SHIFT                         (28U)
/*! IER - Comparator Interrupt Enable Rising
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_C0_IER(x)                            (((uint32_t)(((uint32_t)(x)) << CMP_C0_IER_SHIFT)) & CMP_C0_IER_MASK)

#define CMP_C0_DMAEN_MASK                        (0x40000000U)
#define CMP_C0_DMAEN_SHIFT                       (30U)
/*! DMAEN - DMA Enable
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled.
 */
#define CMP_C0_DMAEN(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C0_DMAEN_SHIFT)) & CMP_C0_DMAEN_MASK)

#define CMP_C0_LINKEN_MASK                       (0x80000000U)
#define CMP_C0_LINKEN_SHIFT                      (31U)
/*! LINKEN - CMP to DAC link enable.
 *  0b0..CMP to DAC link is disabled
 *  0b1..CMP to DAC link is enabled.
 */
#define CMP_C0_LINKEN(x)                         (((uint32_t)(((uint32_t)(x)) << CMP_C0_LINKEN_SHIFT)) & CMP_C0_LINKEN_MASK)
/*! @} */

/*! @name C1 - CMP Control Register 1 */
/*! @{ */

#define CMP_C1_VOSEL_MASK                        (0xFFU)
#define CMP_C1_VOSEL_SHIFT                       (0U)
/*! VOSEL - DAC Output Voltage Select */
#define CMP_C1_VOSEL(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C1_VOSEL_SHIFT)) & CMP_C1_VOSEL_MASK)

#define CMP_C1_DMODE_MASK                        (0x100U)
#define CMP_C1_DMODE_SHIFT                       (8U)
/*! DMODE - DAC Mode Selection
 *  0b0..DAC is selected to work in low speed and low power mode.
 *  0b1..DAC is selected to work in high speed high power mode.
 */
#define CMP_C1_DMODE(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C1_DMODE_SHIFT)) & CMP_C1_DMODE_MASK)

#define CMP_C1_VRSEL_MASK                        (0x200U)
#define CMP_C1_VRSEL_SHIFT                       (9U)
/*! VRSEL - Supply Voltage Reference Source Select
 *  0b0..Vin1 is selected as resistor ladder network supply reference Vin. Vin1 is from internal PMC.
 *  0b1..Vin2 is selected as resistor ladder network supply reference Vin. Vin2 is from PAD.
 */
#define CMP_C1_VRSEL(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C1_VRSEL_SHIFT)) & CMP_C1_VRSEL_MASK)

#define CMP_C1_DACEN_MASK                        (0x400U)
#define CMP_C1_DACEN_SHIFT                       (10U)
/*! DACEN - DAC Enable
 *  0b0..DAC is disabled.
 *  0b1..DAC is enabled.
 */
#define CMP_C1_DACEN(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C1_DACEN_SHIFT)) & CMP_C1_DACEN_MASK)

#define CMP_C1_CHN0_MASK                         (0x10000U)
#define CMP_C1_CHN0_SHIFT                        (16U)
/*! CHN0 - Channel 0 input enable */
#define CMP_C1_CHN0(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_CHN0_SHIFT)) & CMP_C1_CHN0_MASK)

#define CMP_C1_CHN1_MASK                         (0x20000U)
#define CMP_C1_CHN1_SHIFT                        (17U)
/*! CHN1 - Channel 1 input enable */
#define CMP_C1_CHN1(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_CHN1_SHIFT)) & CMP_C1_CHN1_MASK)

#define CMP_C1_CHN2_MASK                         (0x40000U)
#define CMP_C1_CHN2_SHIFT                        (18U)
/*! CHN2 - Channel 2 input enable */
#define CMP_C1_CHN2(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_CHN2_SHIFT)) & CMP_C1_CHN2_MASK)

#define CMP_C1_CHN3_MASK                         (0x80000U)
#define CMP_C1_CHN3_SHIFT                        (19U)
/*! CHN3 - Channel 3 input enable */
#define CMP_C1_CHN3(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_CHN3_SHIFT)) & CMP_C1_CHN3_MASK)

#define CMP_C1_CHN4_MASK                         (0x100000U)
#define CMP_C1_CHN4_SHIFT                        (20U)
/*! CHN4 - Channel 4 input enable */
#define CMP_C1_CHN4(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_CHN4_SHIFT)) & CMP_C1_CHN4_MASK)

#define CMP_C1_CHN5_MASK                         (0x200000U)
#define CMP_C1_CHN5_SHIFT                        (21U)
/*! CHN5 - Channel 5 input enable */
#define CMP_C1_CHN5(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_CHN5_SHIFT)) & CMP_C1_CHN5_MASK)

#define CMP_C1_MSEL_MASK                         (0x7000000U)
#define CMP_C1_MSEL_SHIFT                        (24U)
/*! MSEL - Minus Input MUX Control
 *  0b000..Internal Negative Input 0 for Minus Channel -- Internal Minus Input
 *  0b001..External Input 1 for Minus Channel -- Reference Input 0
 *  0b010..External Input 2 for Minus Channel -- Reference Input 1
 *  0b011..External Input 3 for Minus Channel -- Reference Input 2
 *  0b100..External Input 4 for Minus Channel -- Reference Input 3
 *  0b101..External Input 5 for Minus Channel -- Reference Input 4
 *  0b110..External Input 6 for Minus Channel -- Reference Input 5
 *  0b111..Internal 8b DAC output
 */
#define CMP_C1_MSEL(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_MSEL_SHIFT)) & CMP_C1_MSEL_MASK)

#define CMP_C1_PSEL_MASK                         (0x70000000U)
#define CMP_C1_PSEL_SHIFT                        (28U)
/*! PSEL - Plus Input MUX Control
 *  0b000..Internal Positive Input 0 for Plus Channel -- Internal Plus Input
 *  0b001..External Input 1 for Plus Channel -- Reference Input 0
 *  0b010..External Input 2 for Plus Channel -- Reference Input 1
 *  0b011..External Input 3 for Plus Channel -- Reference Input 2
 *  0b100..External Input 4 for Plus Channel -- Reference Input 3
 *  0b101..External Input 5 for Plus Channel -- Reference Input 4
 *  0b110..External Input 6 for Plus Channel -- Reference Input 5
 *  0b111..Internal 8b DAC output
 */
#define CMP_C1_PSEL(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C1_PSEL_SHIFT)) & CMP_C1_PSEL_MASK)
/*! @} */

/*! @name C2 - CMP Control Register 2 */
/*! @{ */

#define CMP_C2_ACOn_MASK                         (0x3FU)
#define CMP_C2_ACOn_SHIFT                        (0U)
/*! ACOn - ACOn */
#define CMP_C2_ACOn(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_ACOn_SHIFT)) & CMP_C2_ACOn_MASK)

#define CMP_C2_INITMOD_MASK                      (0x3F00U)
#define CMP_C2_INITMOD_SHIFT                     (8U)
/*! INITMOD - Comparator and DAC initialization delay modulus. */
#define CMP_C2_INITMOD(x)                        (((uint32_t)(((uint32_t)(x)) << CMP_C2_INITMOD_SHIFT)) & CMP_C2_INITMOD_MASK)

#define CMP_C2_NSAM_MASK                         (0xC000U)
#define CMP_C2_NSAM_SHIFT                        (14U)
/*! NSAM - Number of sample clocks
 *  0b00..The comparison result is sampled as soon as the active channel is scanned in one round-robin clock.
 *  0b01..The sampling takes place 1 round-robin clock cycle after the next cycle of the round-robin clock.
 *  0b10..The sampling takes place 2 round-robin clock cycles after the next cycle of the round-robin clock.
 *  0b11..The sampling takes place 3 round-robin clock cycles after the next cycle of the round-robin clock.
 */
#define CMP_C2_NSAM(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_NSAM_SHIFT)) & CMP_C2_NSAM_MASK)

#define CMP_C2_CH0F_MASK                         (0x10000U)
#define CMP_C2_CH0F_SHIFT                        (16U)
/*! CH0F - CH0F */
#define CMP_C2_CH0F(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_CH0F_SHIFT)) & CMP_C2_CH0F_MASK)

#define CMP_C2_CH1F_MASK                         (0x20000U)
#define CMP_C2_CH1F_SHIFT                        (17U)
/*! CH1F - CH1F */
#define CMP_C2_CH1F(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_CH1F_SHIFT)) & CMP_C2_CH1F_MASK)

#define CMP_C2_CH2F_MASK                         (0x40000U)
#define CMP_C2_CH2F_SHIFT                        (18U)
/*! CH2F - CH2F */
#define CMP_C2_CH2F(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_CH2F_SHIFT)) & CMP_C2_CH2F_MASK)

#define CMP_C2_CH3F_MASK                         (0x80000U)
#define CMP_C2_CH3F_SHIFT                        (19U)
/*! CH3F - CH3F */
#define CMP_C2_CH3F(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_CH3F_SHIFT)) & CMP_C2_CH3F_MASK)

#define CMP_C2_CH4F_MASK                         (0x100000U)
#define CMP_C2_CH4F_SHIFT                        (20U)
/*! CH4F - CH4F */
#define CMP_C2_CH4F(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_CH4F_SHIFT)) & CMP_C2_CH4F_MASK)

#define CMP_C2_CH5F_MASK                         (0x200000U)
#define CMP_C2_CH5F_SHIFT                        (21U)
/*! CH5F - CH5F */
#define CMP_C2_CH5F(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_CH5F_SHIFT)) & CMP_C2_CH5F_MASK)

#define CMP_C2_FXMXCH_MASK                       (0xE000000U)
#define CMP_C2_FXMXCH_SHIFT                      (25U)
/*! FXMXCH - Fixed channel selection
 *  0b000..External Reference Input 0 is selected as the fixed reference input for the fixed mux port.
 *  0b001..External Reference Input 1 is selected as the fixed reference input for the fixed mux port.
 *  0b010..External Reference Input 2 is selected as the fixed reference input for the fixed mux port.
 *  0b011..External Reference Input 3 is selected as the fixed reference input for the fixed mux port.
 *  0b100..External Reference Input 4 is selected as the fixed reference input for the fixed mux port.
 *  0b101..External Reference Input 5 is selected as the fixed reference input for the fixed mux port.
 *  0b110..Reserved.
 *  0b111..The 8bit DAC is selected as the fixed reference input for the fixed mux port.
 */
#define CMP_C2_FXMXCH(x)                         (((uint32_t)(((uint32_t)(x)) << CMP_C2_FXMXCH_SHIFT)) & CMP_C2_FXMXCH_MASK)

#define CMP_C2_FXMP_MASK                         (0x20000000U)
#define CMP_C2_FXMP_SHIFT                        (29U)
/*! FXMP - Fixed MUX Port
 *  0b0..The Plus port is fixed. Only the inputs to the Minus port are swept in each round.
 *  0b1..The Minus port is fixed. Only the inputs to the Plus port are swept in each round.
 */
#define CMP_C2_FXMP(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_FXMP_SHIFT)) & CMP_C2_FXMP_MASK)

#define CMP_C2_RRIE_MASK                         (0x40000000U)
#define CMP_C2_RRIE_SHIFT                        (30U)
/*! RRIE - Round-Robin interrupt enable
 *  0b0..The round-robin interrupt is disabled.
 *  0b1..The round-robin interrupt is enabled when a comparison result changes from the last sample.
 */
#define CMP_C2_RRIE(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C2_RRIE_SHIFT)) & CMP_C2_RRIE_MASK)
/*! @} */

/*! @name C3 - CMP Control Register 3 */
/*! @{ */

#define CMP_C3_ACPH2TC_MASK                      (0x70U)
#define CMP_C3_ACPH2TC_SHIFT                     (4U)
/*! ACPH2TC - Analog Comparator Phase2 Timing Control.
 *  0b000..Phase2 active time in one sampling period equals to T
 *  0b001..Phase2 active time in one sampling period equals to 2*T
 *  0b010..Phase2 active time in one sampling period equals to 4*T
 *  0b011..Phase2 active time in one sampling period equals to 8*T
 *  0b100..Phase2 active time in one sampling period equals to 16*T
 *  0b101..Phase2 active time in one sampling period equals to 32*T
 *  0b110..Phase2 active time in one sampling period equals to 64*T
 *  0b111..Phase2 active time in one sampling period equals to 16*T
 */
#define CMP_C3_ACPH2TC(x)                        (((uint32_t)(((uint32_t)(x)) << CMP_C3_ACPH2TC_SHIFT)) & CMP_C3_ACPH2TC_MASK)

#define CMP_C3_ACPH1TC_MASK                      (0x700U)
#define CMP_C3_ACPH1TC_SHIFT                     (8U)
/*! ACPH1TC - Analog Comparator Phase1 Timing Control.
 *  0b000..Phase1 active time in one sampling period equals to T
 *  0b001..Phase1 active time in one sampling period equals to 2*T
 *  0b010..Phase1 active time in one sampling period equals to 4*T
 *  0b011..Phase1 active time in one sampling period equals to 8*T
 *  0b100..Phase1 active time in one sampling period equals to T
 *  0b101..Phase1 active time in one sampling period equals to T
 *  0b110..Phase1 active time in one sampling period equals to T
 *  0b111..Phase1 active time in one sampling period equals to 0
 */
#define CMP_C3_ACPH1TC(x)                        (((uint32_t)(((uint32_t)(x)) << CMP_C3_ACPH1TC_SHIFT)) & CMP_C3_ACPH1TC_MASK)

#define CMP_C3_ACSAT_MASK                        (0x7000U)
#define CMP_C3_ACSAT_SHIFT                       (12U)
/*! ACSAT - Analog Comparator Sampling Time control.
 *  0b000..The sampling time equals to T
 *  0b001..The sampling time equasl to 2*T
 *  0b010..The sampling time equasl to 4*T
 *  0b011..The sampling time equasl to 8*T
 *  0b100..The sampling time equasl to 16*T
 *  0b101..The sampling time equasl to 32*T
 *  0b110..The sampling time equasl to 64*T
 *  0b111..The sampling time equasl to 256*T
 */
#define CMP_C3_ACSAT(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C3_ACSAT_SHIFT)) & CMP_C3_ACSAT_MASK)

#define CMP_C3_DMCS_MASK                         (0x10000U)
#define CMP_C3_DMCS_SHIFT                        (16U)
/*! DMCS - Discrete Mode Clock Selection
 *  0b0..Slow clock is selected for the timing generation.
 *  0b1..Fast clock is selected for the timing generation.
 */
#define CMP_C3_DMCS(x)                           (((uint32_t)(((uint32_t)(x)) << CMP_C3_DMCS_SHIFT)) & CMP_C3_DMCS_MASK)

#define CMP_C3_RDIVE_MASK                        (0x100000U)
#define CMP_C3_RDIVE_SHIFT                       (20U)
/*! RDIVE - Resistor Divider Enable
 *  0b0..The resistor is not enabled even when either NCHEN or PCHEN is set to1 but the actual input is in the range of 0 - 1.8v.
 *  0b1..The resistor is enabled because the inputs are above 1.8v.
 */
#define CMP_C3_RDIVE(x)                          (((uint32_t)(((uint32_t)(x)) << CMP_C3_RDIVE_SHIFT)) & CMP_C3_RDIVE_MASK)

#define CMP_C3_NCHCTEN_MASK                      (0x1000000U)
#define CMP_C3_NCHCTEN_SHIFT                     (24U)
/*! NCHCTEN - Negative Channel Continuous Mode Enable.
 *  0b0..Negative channel is in Discrete Mode and special timing needs to be configured.
 *  0b1..Negative channel is in Continuous Mode and no special timing is requried.
 */
#define CMP_C3_NCHCTEN(x)                        (((uint32_t)(((uint32_t)(x)) << CMP_C3_NCHCTEN_SHIFT)) & CMP_C3_NCHCTEN_MASK)

#define CMP_C3_PCHCTEN_MASK                      (0x10000000U)
#define CMP_C3_PCHCTEN_SHIFT                     (28U)
/*! PCHCTEN - Positive Channel Continuous Mode Enable.
 *  0b0..Positive channel is in Discrete Mode and special timing needs to be configured.
 *  0b1..Positive channel is in Continuous Mode and no special timing is requried.
 */
#define CMP_C3_PCHCTEN(x)                        (((uint32_t)(((uint32_t)(x)) << CMP_C3_PCHCTEN_SHIFT)) & CMP_C3_PCHCTEN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CMP_Register_Masks */


/*!
 * @}
 */ /* end of group CMP_Peripheral_Access_Layer */


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


#endif  /* PERI_CMP_H_ */

