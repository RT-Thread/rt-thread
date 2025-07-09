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
**         CMSIS Peripheral Access Layer for GPT
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
 * @file PERI_GPT.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for GPT
 *
 * CMSIS Peripheral Access Layer for GPT
 */

#if !defined(PERI_GPT_H_)
#define PERI_GPT_H_                              /**< Symbol preventing repeated inclusion */

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
   -- GPT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPT_Peripheral_Access_Layer GPT Peripheral Access Layer
 * @{
 */

/** GPT - Size of Registers Arrays */
#define GPT_OCR_COUNT                             3u
#define GPT_ICR_COUNT                             2u

/** GPT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< GPT Control Register, offset: 0x0 */
  __IO uint32_t PR;                                /**< GPT Prescaler Register, offset: 0x4 */
  __IO uint32_t SR;                                /**< GPT Status Register, offset: 0x8 */
  __IO uint32_t IR;                                /**< GPT Interrupt Register, offset: 0xC */
  __IO uint32_t OCR[GPT_OCR_COUNT];                /**< GPT Output Compare Register, array offset: 0x10, array step: 0x4 */
  __I  uint32_t ICR[GPT_ICR_COUNT];                /**< GPT Input Capture Register, array offset: 0x1C, array step: 0x4 */
  __I  uint32_t CNT;                               /**< GPT Counter Register, offset: 0x24 */
} GPT_Type;

/* ----------------------------------------------------------------------------
   -- GPT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPT_Register_Masks GPT Register Masks
 * @{
 */

/*! @name CR - GPT Control Register */
/*! @{ */

#define GPT_CR_EN_MASK                           (0x1U)
#define GPT_CR_EN_SHIFT                          (0U)
/*! EN - GPT Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_CR_EN(x)                             (((uint32_t)(((uint32_t)(x)) << GPT_CR_EN_SHIFT)) & GPT_CR_EN_MASK)

#define GPT_CR_ENMOD_MASK                        (0x2U)
#define GPT_CR_ENMOD_SHIFT                       (1U)
/*! ENMOD - GPT Enable Mode
 *  0b0..Restart counting from their frozen values after GPT is enabled (EN=1).
 *  0b1..Reset counting from 0 after GPT is enabled (EN=1).
 */
#define GPT_CR_ENMOD(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_CR_ENMOD_SHIFT)) & GPT_CR_ENMOD_MASK)

#define GPT_CR_DBGEN_MASK                        (0x4U)
#define GPT_CR_DBGEN_SHIFT                       (2U)
/*! DBGEN - GPT Debug Mode Enable
 *  0b0..Disable in Debug mode
 *  0b1..Enable in Debug mode
 */
#define GPT_CR_DBGEN(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_CR_DBGEN_SHIFT)) & GPT_CR_DBGEN_MASK)

#define GPT_CR_WAITEN_MASK                       (0x8U)
#define GPT_CR_WAITEN_SHIFT                      (3U)
/*! WAITEN - GPT Wait Mode Enable
 *  0b0..Disable in Wait mode
 *  0b1..Enable in Wait mode
 */
#define GPT_CR_WAITEN(x)                         (((uint32_t)(((uint32_t)(x)) << GPT_CR_WAITEN_SHIFT)) & GPT_CR_WAITEN_MASK)

#define GPT_CR_DOZEEN_MASK                       (0x10U)
#define GPT_CR_DOZEEN_SHIFT                      (4U)
/*! DOZEEN - GPT Doze Mode Enable
 *  0b0..Disable in Doze mode
 *  0b1..Enable in Doze mode
 */
#define GPT_CR_DOZEEN(x)                         (((uint32_t)(((uint32_t)(x)) << GPT_CR_DOZEEN_SHIFT)) & GPT_CR_DOZEEN_MASK)

#define GPT_CR_STOPEN_MASK                       (0x20U)
#define GPT_CR_STOPEN_SHIFT                      (5U)
/*! STOPEN - GPT Stop Mode Enable
 *  0b0..Disable in Stop mode
 *  0b1..Enable in Stop mode
 */
#define GPT_CR_STOPEN(x)                         (((uint32_t)(((uint32_t)(x)) << GPT_CR_STOPEN_SHIFT)) & GPT_CR_STOPEN_MASK)

#define GPT_CR_CLKSRC_MASK                       (0x1C0U)
#define GPT_CR_CLKSRC_SHIFT                      (6U)
/*! CLKSRC - Clock Source Select
 *  0b000..No clock
 *  0b001..Peripheral Clock (ipg_clk)
 *  0b010..High Frequency Reference Clock (ipg_clk_highfreq)
 *  0b011..External Clock
 *  0b100..Low Frequency Reference Clock (ipg_clk_32k)
 *  0b101..Oscillator as Reference Clock (ipg_clk_16M)
 */
#define GPT_CR_CLKSRC(x)                         (((uint32_t)(((uint32_t)(x)) << GPT_CR_CLKSRC_SHIFT)) & GPT_CR_CLKSRC_MASK)

#define GPT_CR_FRR_MASK                          (0x200U)
#define GPT_CR_FRR_SHIFT                         (9U)
/*! FRR - Free-Run or Restart Mode
 *  0b0..Restart mode. After a compare event, the counter resets to 0x0000_0000 and resumes counting.
 *  0b1..Free-Run mode. After a compare event, the counter continues counting until 0xFFFF_FFFF and then rolls over to 0.
 */
#define GPT_CR_FRR(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_FRR_SHIFT)) & GPT_CR_FRR_MASK)

#define GPT_CR_EN_24M_MASK                       (0x400U)
#define GPT_CR_EN_24M_SHIFT                      (10U)
/*! EN_24M - Enable Oscillator Clock Input
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_CR_EN_24M(x)                         (((uint32_t)(((uint32_t)(x)) << GPT_CR_EN_24M_SHIFT)) & GPT_CR_EN_24M_MASK)

#define GPT_CR_SWR_MASK                          (0x8000U)
#define GPT_CR_SWR_SHIFT                         (15U)
/*! SWR - Software Reset
 *  0b0..GPT is not in software reset state
 *  0b1..GPT is in software reset state
 */
#define GPT_CR_SWR(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_SWR_SHIFT)) & GPT_CR_SWR_MASK)

#define GPT_CR_IM1_MASK                          (0x30000U)
#define GPT_CR_IM1_SHIFT                         (16U)
/*! IM1 - Input Capture Operating Mode for Channel 1
 *  0b00..Capture disabled
 *  0b01..Capture on rising edge only
 *  0b10..Capture on falling edge only
 *  0b11..Capture on both edges
 */
#define GPT_CR_IM1(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_IM1_SHIFT)) & GPT_CR_IM1_MASK)

#define GPT_CR_IM2_MASK                          (0xC0000U)
#define GPT_CR_IM2_SHIFT                         (18U)
/*! IM2 - Input Capture Operating Mode for Channel 2
 *  0b00..Capture disabled
 *  0b01..Capture on rising edge only
 *  0b10..Capture on falling edge only
 *  0b11..Capture on both edges
 */
#define GPT_CR_IM2(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_IM2_SHIFT)) & GPT_CR_IM2_MASK)

#define GPT_CR_OM1_MASK                          (0x700000U)
#define GPT_CR_OM1_SHIFT                         (20U)
/*! OM1 - Output Compare Operating Mode for Channel 1
 *  0b000..Output disabled. No response on pin.
 *  0b001..Toggle output pin
 *  0b010..Clear output pin
 *  0b011..Set output pin
 *  0b1xx..Generate a low pulse that is one input clock cycle wide on the output pin. When OMn is first programmed
 *         as 1xx, the output pin is set to one immediately on the next input clock (if it was not one already).
 *         "Input clock" here refers to the clock selected by the CLKSRC field of this register.
 */
#define GPT_CR_OM1(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_OM1_SHIFT)) & GPT_CR_OM1_MASK)

#define GPT_CR_OM2_MASK                          (0x3800000U)
#define GPT_CR_OM2_SHIFT                         (23U)
/*! OM2 - Output Compare Operating Mode for Channel 2
 *  0b000..Output disabled. No response on pin.
 *  0b001..Toggle output pin
 *  0b010..Clear output pin
 *  0b011..Set output pin
 *  0b1xx..Generate a low pulse that is one input clock cycle wide on the output pin. When OMn is first programmed
 *         as 1xx, the output pin is set to one immediately on the next input clock (if it was not one already).
 *         "Input clock" here refers to the clock selected by the CLKSRC field of this register.
 */
#define GPT_CR_OM2(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_OM2_SHIFT)) & GPT_CR_OM2_MASK)

#define GPT_CR_OM3_MASK                          (0x1C000000U)
#define GPT_CR_OM3_SHIFT                         (26U)
/*! OM3 - Output Compare Operating Mode for Channel 3
 *  0b000..Output disabled. No response on pin.
 *  0b001..Toggle output pin
 *  0b010..Clear output pin
 *  0b011..Set output pin
 *  0b1xx..Generate a low pulse that is one input clock cycle wide on the output pin. When OMn is first programmed
 *         as 1xx, the output pin is set to one immediately on the next input clock (if it was not one already).
 *         "Input clock" here refers to the clock selected by the CLKSRC field of this register.
 */
#define GPT_CR_OM3(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_OM3_SHIFT)) & GPT_CR_OM3_MASK)

#define GPT_CR_FO1_MASK                          (0x20000000U)
#define GPT_CR_FO1_SHIFT                         (29U)
/*! FO1 - Force Output Compare for Channel 1
 *  0b0..No effect
 *  0b1..Trigger the programmed response on the pin
 */
#define GPT_CR_FO1(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_FO1_SHIFT)) & GPT_CR_FO1_MASK)

#define GPT_CR_FO2_MASK                          (0x40000000U)
#define GPT_CR_FO2_SHIFT                         (30U)
/*! FO2 - Force Output Compare for Channel 2
 *  0b0..No effect
 *  0b1..Trigger the programmed response on the pin
 */
#define GPT_CR_FO2(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_FO2_SHIFT)) & GPT_CR_FO2_MASK)

#define GPT_CR_FO3_MASK                          (0x80000000U)
#define GPT_CR_FO3_SHIFT                         (31U)
/*! FO3 - Force Output Compare for Channel 3
 *  0b0..No effect
 *  0b1..Trigger the programmed response on the pin
 */
#define GPT_CR_FO3(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_CR_FO3_SHIFT)) & GPT_CR_FO3_MASK)
/*! @} */

/*! @name PR - GPT Prescaler Register */
/*! @{ */

#define GPT_PR_PRESCALER_MASK                    (0xFFFU)
#define GPT_PR_PRESCALER_SHIFT                   (0U)
/*! PRESCALER - Prescaler divide value
 *  0b000000000000..Divide by 1
 *  0b000000000001..Divide by 2
 *  0b111111111111..Divide by 4096
 */
#define GPT_PR_PRESCALER(x)                      (((uint32_t)(((uint32_t)(x)) << GPT_PR_PRESCALER_SHIFT)) & GPT_PR_PRESCALER_MASK)

#define GPT_PR_PRESCALER24M_MASK                 (0xF000U)
#define GPT_PR_PRESCALER24M_SHIFT                (12U)
/*! PRESCALER24M - Prescaler divide value for the oscillator clock
 *  0b0000..Divide by 1
 *  0b0001..Divide by 2
 *  0b1111..Divide by 16
 */
#define GPT_PR_PRESCALER24M(x)                   (((uint32_t)(((uint32_t)(x)) << GPT_PR_PRESCALER24M_SHIFT)) & GPT_PR_PRESCALER24M_MASK)
/*! @} */

/*! @name SR - GPT Status Register */
/*! @{ */

#define GPT_SR_OF1_MASK                          (0x1U)
#define GPT_SR_OF1_SHIFT                         (0U)
/*! OF1 - Output Compare Flag for Channel 1
 *  0b0..Compare event has not occurred.
 *  0b1..Compare event has occurred.
 */
#define GPT_SR_OF1(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_SR_OF1_SHIFT)) & GPT_SR_OF1_MASK)

#define GPT_SR_OF2_MASK                          (0x2U)
#define GPT_SR_OF2_SHIFT                         (1U)
/*! OF2 - Output Compare Flag for Channel 2
 *  0b0..Compare event has not occurred.
 *  0b1..Compare event has occurred.
 */
#define GPT_SR_OF2(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_SR_OF2_SHIFT)) & GPT_SR_OF2_MASK)

#define GPT_SR_OF3_MASK                          (0x4U)
#define GPT_SR_OF3_SHIFT                         (2U)
/*! OF3 - Output Compare Flag for Channel 3
 *  0b0..Compare event has not occurred.
 *  0b1..Compare event has occurred.
 */
#define GPT_SR_OF3(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_SR_OF3_SHIFT)) & GPT_SR_OF3_MASK)

#define GPT_SR_IF1_MASK                          (0x8U)
#define GPT_SR_IF1_SHIFT                         (3U)
/*! IF1 - Input Capture Flag for Channel 1
 *  0b0..Capture event has not occurred.
 *  0b1..Capture event has occurred.
 */
#define GPT_SR_IF1(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_SR_IF1_SHIFT)) & GPT_SR_IF1_MASK)

#define GPT_SR_IF2_MASK                          (0x10U)
#define GPT_SR_IF2_SHIFT                         (4U)
/*! IF2 - Input Capture Flag for Channel 2
 *  0b0..Capture event has not occurred.
 *  0b1..Capture event has occurred.
 */
#define GPT_SR_IF2(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_SR_IF2_SHIFT)) & GPT_SR_IF2_MASK)

#define GPT_SR_ROV_MASK                          (0x20U)
#define GPT_SR_ROV_SHIFT                         (5U)
/*! ROV - Rollover Flag
 *  0b0..Rollover has not occurred.
 *  0b1..Rollover has occurred.
 */
#define GPT_SR_ROV(x)                            (((uint32_t)(((uint32_t)(x)) << GPT_SR_ROV_SHIFT)) & GPT_SR_ROV_MASK)
/*! @} */

/*! @name IR - GPT Interrupt Register */
/*! @{ */

#define GPT_IR_OF1IE_MASK                        (0x1U)
#define GPT_IR_OF1IE_SHIFT                       (0U)
/*! OF1IE - Output Compare Flag for Channel 1 Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_IR_OF1IE(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_IR_OF1IE_SHIFT)) & GPT_IR_OF1IE_MASK)

#define GPT_IR_OF2IE_MASK                        (0x2U)
#define GPT_IR_OF2IE_SHIFT                       (1U)
/*! OF2IE - Output Compare Flag for Channel 2 Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_IR_OF2IE(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_IR_OF2IE_SHIFT)) & GPT_IR_OF2IE_MASK)

#define GPT_IR_OF3IE_MASK                        (0x4U)
#define GPT_IR_OF3IE_SHIFT                       (2U)
/*! OF3IE - Output Compare Flag for Channel 3 Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_IR_OF3IE(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_IR_OF3IE_SHIFT)) & GPT_IR_OF3IE_MASK)

#define GPT_IR_IF1IE_MASK                        (0x8U)
#define GPT_IR_IF1IE_SHIFT                       (3U)
/*! IF1IE - Input Capture Flag for Channel 1 Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_IR_IF1IE(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_IR_IF1IE_SHIFT)) & GPT_IR_IF1IE_MASK)

#define GPT_IR_IF2IE_MASK                        (0x10U)
#define GPT_IR_IF2IE_SHIFT                       (4U)
/*! IF2IE - Input Capture Flag for Channel 2 Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_IR_IF2IE(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_IR_IF2IE_SHIFT)) & GPT_IR_IF2IE_MASK)

#define GPT_IR_ROVIE_MASK                        (0x20U)
#define GPT_IR_ROVIE_SHIFT                       (5U)
/*! ROVIE - Rollover Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define GPT_IR_ROVIE(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_IR_ROVIE_SHIFT)) & GPT_IR_ROVIE_MASK)
/*! @} */

/*! @name OCR - GPT Output Compare Register */
/*! @{ */

#define GPT_OCR_COMP_MASK                        (0xFFFFFFFFU)
#define GPT_OCR_COMP_SHIFT                       (0U)
/*! COMP - Compare Value */
#define GPT_OCR_COMP(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_OCR_COMP_SHIFT)) & GPT_OCR_COMP_MASK)
/*! @} */

/*! @name ICR - GPT Input Capture Register */
/*! @{ */

#define GPT_ICR_CAPT_MASK                        (0xFFFFFFFFU)
#define GPT_ICR_CAPT_SHIFT                       (0U)
/*! CAPT - Capture Value */
#define GPT_ICR_CAPT(x)                          (((uint32_t)(((uint32_t)(x)) << GPT_ICR_CAPT_SHIFT)) & GPT_ICR_CAPT_MASK)
/*! @} */

/*! @name CNT - GPT Counter Register */
/*! @{ */

#define GPT_CNT_COUNT_MASK                       (0xFFFFFFFFU)
#define GPT_CNT_COUNT_SHIFT                      (0U)
/*! COUNT - Counter Value */
#define GPT_CNT_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << GPT_CNT_COUNT_SHIFT)) & GPT_CNT_COUNT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GPT_Register_Masks */


/*!
 * @}
 */ /* end of group GPT_Peripheral_Access_Layer */


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


#endif  /* PERI_GPT_H_ */

