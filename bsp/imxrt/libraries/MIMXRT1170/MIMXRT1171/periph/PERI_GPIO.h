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
**         CMSIS Peripheral Access Layer for GPIO
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
 * @file PERI_GPIO.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for GPIO
 *
 * CMSIS Peripheral Access Layer for GPIO
 */

#if !defined(PERI_GPIO_H_)
#define PERI_GPIO_H_                             /**< Symbol preventing repeated inclusion */

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
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t DR;                                /**< GPIO data register, offset: 0x0 */
  __IO uint32_t GDIR;                              /**< GPIO direction register, offset: 0x4 */
  __I  uint32_t PSR;                               /**< GPIO pad status register, offset: 0x8 */
  __IO uint32_t ICR1;                              /**< GPIO interrupt configuration register1, offset: 0xC */
  __IO uint32_t ICR2;                              /**< GPIO interrupt configuration register2, offset: 0x10 */
  __IO uint32_t IMR;                               /**< GPIO interrupt mask register, offset: 0x14 */
  __IO uint32_t ISR;                               /**< GPIO interrupt status register, offset: 0x18 */
  __IO uint32_t EDGE_SEL;                          /**< GPIO edge select register, offset: 0x1C */
       uint8_t RESERVED_0[100];
  __O  uint32_t DR_SET;                            /**< GPIO data register SET, offset: 0x84 */
  __O  uint32_t DR_CLEAR;                          /**< GPIO data register CLEAR, offset: 0x88 */
  __O  uint32_t DR_TOGGLE;                         /**< GPIO data register TOGGLE, offset: 0x8C */
} GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name DR - GPIO data register */
/*! @{ */

#define GPIO_DR_DR_MASK                          (0xFFFFFFFFU)
#define GPIO_DR_DR_SHIFT                         (0U)
/*! DR - DR data bits */
#define GPIO_DR_DR(x)                            (((uint32_t)(((uint32_t)(x)) << GPIO_DR_DR_SHIFT)) & GPIO_DR_DR_MASK)
/*! @} */

/*! @name GDIR - GPIO direction register */
/*! @{ */

#define GPIO_GDIR_GDIR_MASK                      (0xFFFFFFFFU)
#define GPIO_GDIR_GDIR_SHIFT                     (0U)
/*! GDIR - GPIO direction bits */
#define GPIO_GDIR_GDIR(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_GDIR_GDIR_SHIFT)) & GPIO_GDIR_GDIR_MASK)
/*! @} */

/*! @name PSR - GPIO pad status register */
/*! @{ */

#define GPIO_PSR_PSR_MASK                        (0xFFFFFFFFU)
#define GPIO_PSR_PSR_SHIFT                       (0U)
/*! PSR - GPIO pad status bits */
#define GPIO_PSR_PSR(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_PSR_PSR_SHIFT)) & GPIO_PSR_PSR_MASK)
/*! @} */

/*! @name ICR1 - GPIO interrupt configuration register1 */
/*! @{ */

#define GPIO_ICR1_ICR0_MASK                      (0x3U)
#define GPIO_ICR1_ICR0_SHIFT                     (0U)
/*! ICR0 - Interrupt configuration field for GPIO interrupt 0
 *  0b00..Interrupt 0 is low-level sensitive.
 *  0b01..Interrupt 0 is high-level sensitive.
 *  0b10..Interrupt 0 is rising-edge sensitive.
 *  0b11..Interrupt 0 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR0(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR0_SHIFT)) & GPIO_ICR1_ICR0_MASK)

#define GPIO_ICR1_ICR1_MASK                      (0xCU)
#define GPIO_ICR1_ICR1_SHIFT                     (2U)
/*! ICR1 - Interrupt configuration field for GPIO interrupt 1
 *  0b00..Interrupt 1 is low-level sensitive.
 *  0b01..Interrupt 1 is high-level sensitive.
 *  0b10..Interrupt 1 is rising-edge sensitive.
 *  0b11..Interrupt 1 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR1(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR1_SHIFT)) & GPIO_ICR1_ICR1_MASK)

#define GPIO_ICR1_ICR2_MASK                      (0x30U)
#define GPIO_ICR1_ICR2_SHIFT                     (4U)
/*! ICR2 - Interrupt configuration field for GPIO interrupt 2
 *  0b00..Interrupt 2 is low-level sensitive.
 *  0b01..Interrupt 2 is high-level sensitive.
 *  0b10..Interrupt 2 is rising-edge sensitive.
 *  0b11..Interrupt 2 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR2(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR2_SHIFT)) & GPIO_ICR1_ICR2_MASK)

#define GPIO_ICR1_ICR3_MASK                      (0xC0U)
#define GPIO_ICR1_ICR3_SHIFT                     (6U)
/*! ICR3 - Interrupt configuration field for GPIO interrupt 3
 *  0b00..Interrupt 3 is low-level sensitive.
 *  0b01..Interrupt 3 is high-level sensitive.
 *  0b10..Interrupt 3 is rising-edge sensitive.
 *  0b11..Interrupt 3 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR3(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR3_SHIFT)) & GPIO_ICR1_ICR3_MASK)

#define GPIO_ICR1_ICR4_MASK                      (0x300U)
#define GPIO_ICR1_ICR4_SHIFT                     (8U)
/*! ICR4 - Interrupt configuration field for GPIO interrupt 4
 *  0b00..Interrupt 4 is low-level sensitive.
 *  0b01..Interrupt 4 is high-level sensitive.
 *  0b10..Interrupt 4 is rising-edge sensitive.
 *  0b11..Interrupt 4 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR4(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR4_SHIFT)) & GPIO_ICR1_ICR4_MASK)

#define GPIO_ICR1_ICR5_MASK                      (0xC00U)
#define GPIO_ICR1_ICR5_SHIFT                     (10U)
/*! ICR5 - Interrupt configuration field for GPIO interrupt 5
 *  0b00..Interrupt 5 is low-level sensitive.
 *  0b01..Interrupt 5 is high-level sensitive.
 *  0b10..Interrupt 5 is rising-edge sensitive.
 *  0b11..Interrupt 5 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR5(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR5_SHIFT)) & GPIO_ICR1_ICR5_MASK)

#define GPIO_ICR1_ICR6_MASK                      (0x3000U)
#define GPIO_ICR1_ICR6_SHIFT                     (12U)
/*! ICR6 - Interrupt configuration field for GPIO interrupt 6
 *  0b00..Interrupt 6 is low-level sensitive.
 *  0b01..Interrupt 6 is high-level sensitive.
 *  0b10..Interrupt 6 is rising-edge sensitive.
 *  0b11..Interrupt 6 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR6(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR6_SHIFT)) & GPIO_ICR1_ICR6_MASK)

#define GPIO_ICR1_ICR7_MASK                      (0xC000U)
#define GPIO_ICR1_ICR7_SHIFT                     (14U)
/*! ICR7 - Interrupt configuration field for GPIO interrupt 7
 *  0b00..Interrupt 7 is low-level sensitive.
 *  0b01..Interrupt 7 is high-level sensitive.
 *  0b10..Interrupt 7 is rising-edge sensitive.
 *  0b11..Interrupt 7 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR7(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR7_SHIFT)) & GPIO_ICR1_ICR7_MASK)

#define GPIO_ICR1_ICR8_MASK                      (0x30000U)
#define GPIO_ICR1_ICR8_SHIFT                     (16U)
/*! ICR8 - Interrupt configuration field for GPIO interrupt 8
 *  0b00..Interrupt 8 is low-level sensitive.
 *  0b01..Interrupt 8 is high-level sensitive.
 *  0b10..Interrupt 8 is rising-edge sensitive.
 *  0b11..Interrupt 8 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR8(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR8_SHIFT)) & GPIO_ICR1_ICR8_MASK)

#define GPIO_ICR1_ICR9_MASK                      (0xC0000U)
#define GPIO_ICR1_ICR9_SHIFT                     (18U)
/*! ICR9 - Interrupt configuration field for GPIO interrupt 9
 *  0b00..Interrupt 9 is low-level sensitive.
 *  0b01..Interrupt 9 is high-level sensitive.
 *  0b10..Interrupt 9 is rising-edge sensitive.
 *  0b11..Interrupt 9 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR9(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR9_SHIFT)) & GPIO_ICR1_ICR9_MASK)

#define GPIO_ICR1_ICR10_MASK                     (0x300000U)
#define GPIO_ICR1_ICR10_SHIFT                    (20U)
/*! ICR10 - Interrupt configuration field for GPIO interrupt 10
 *  0b00..Interrupt 10 is low-level sensitive.
 *  0b01..Interrupt 10 is high-level sensitive.
 *  0b10..Interrupt 10 is rising-edge sensitive.
 *  0b11..Interrupt 10 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR10(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR10_SHIFT)) & GPIO_ICR1_ICR10_MASK)

#define GPIO_ICR1_ICR11_MASK                     (0xC00000U)
#define GPIO_ICR1_ICR11_SHIFT                    (22U)
/*! ICR11 - Interrupt configuration field for GPIO interrupt 11
 *  0b00..Interrupt 11 is low-level sensitive.
 *  0b01..Interrupt 11 is high-level sensitive.
 *  0b10..Interrupt 11 is rising-edge sensitive.
 *  0b11..Interrupt 11 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR11(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR11_SHIFT)) & GPIO_ICR1_ICR11_MASK)

#define GPIO_ICR1_ICR12_MASK                     (0x3000000U)
#define GPIO_ICR1_ICR12_SHIFT                    (24U)
/*! ICR12 - Interrupt configuration field for GPIO interrupt 12
 *  0b00..Interrupt 12 is low-level sensitive.
 *  0b01..Interrupt 12 is high-level sensitive.
 *  0b10..Interrupt 12 is rising-edge sensitive.
 *  0b11..Interrupt 12 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR12(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR12_SHIFT)) & GPIO_ICR1_ICR12_MASK)

#define GPIO_ICR1_ICR13_MASK                     (0xC000000U)
#define GPIO_ICR1_ICR13_SHIFT                    (26U)
/*! ICR13 - Interrupt configuration field for GPIO interrupt 13
 *  0b00..Interrupt 13 is low-level sensitive.
 *  0b01..Interrupt 13 is high-level sensitive.
 *  0b10..Interrupt 13 is rising-edge sensitive.
 *  0b11..Interrupt 13 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR13(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR13_SHIFT)) & GPIO_ICR1_ICR13_MASK)

#define GPIO_ICR1_ICR14_MASK                     (0x30000000U)
#define GPIO_ICR1_ICR14_SHIFT                    (28U)
/*! ICR14 - Interrupt configuration field for GPIO interrupt 14
 *  0b00..Interrupt 14 is low-level sensitive.
 *  0b01..Interrupt 14 is high-level sensitive.
 *  0b10..Interrupt 14 is rising-edge sensitive.
 *  0b11..Interrupt 14 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR14(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR14_SHIFT)) & GPIO_ICR1_ICR14_MASK)

#define GPIO_ICR1_ICR15_MASK                     (0xC0000000U)
#define GPIO_ICR1_ICR15_SHIFT                    (30U)
/*! ICR15 - Interrupt configuration field for GPIO interrupt 15
 *  0b00..Interrupt 15 is low-level sensitive.
 *  0b01..Interrupt 15 is high-level sensitive.
 *  0b10..Interrupt 15 is rising-edge sensitive.
 *  0b11..Interrupt 15 is falling-edge sensitive.
 */
#define GPIO_ICR1_ICR15(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR1_ICR15_SHIFT)) & GPIO_ICR1_ICR15_MASK)
/*! @} */

/*! @name ICR2 - GPIO interrupt configuration register2 */
/*! @{ */

#define GPIO_ICR2_ICR16_MASK                     (0x3U)
#define GPIO_ICR2_ICR16_SHIFT                    (0U)
/*! ICR16 - Interrupt configuration field for GPIO interrupt 16
 *  0b00..Interrupt 16 is low-level sensitive.
 *  0b01..Interrupt 16 is high-level sensitive.
 *  0b10..Interrupt 16 is rising-edge sensitive.
 *  0b11..Interrupt 16 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR16(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR16_SHIFT)) & GPIO_ICR2_ICR16_MASK)

#define GPIO_ICR2_ICR17_MASK                     (0xCU)
#define GPIO_ICR2_ICR17_SHIFT                    (2U)
/*! ICR17 - Interrupt configuration field for GPIO interrupt 17
 *  0b00..Interrupt 17 is low-level sensitive.
 *  0b01..Interrupt 17 is high-level sensitive.
 *  0b10..Interrupt 17 is rising-edge sensitive.
 *  0b11..Interrupt 17 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR17(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR17_SHIFT)) & GPIO_ICR2_ICR17_MASK)

#define GPIO_ICR2_ICR18_MASK                     (0x30U)
#define GPIO_ICR2_ICR18_SHIFT                    (4U)
/*! ICR18 - Interrupt configuration field for GPIO interrupt 18
 *  0b00..Interrupt 18 is low-level sensitive.
 *  0b01..Interrupt 18 is high-level sensitive.
 *  0b10..Interrupt 18 is rising-edge sensitive.
 *  0b11..Interrupt 18 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR18(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR18_SHIFT)) & GPIO_ICR2_ICR18_MASK)

#define GPIO_ICR2_ICR19_MASK                     (0xC0U)
#define GPIO_ICR2_ICR19_SHIFT                    (6U)
/*! ICR19 - Interrupt configuration field for GPIO interrupt 19
 *  0b00..Interrupt 19 is low-level sensitive.
 *  0b01..Interrupt 19 is high-level sensitive.
 *  0b10..Interrupt 19 is rising-edge sensitive.
 *  0b11..Interrupt 19 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR19(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR19_SHIFT)) & GPIO_ICR2_ICR19_MASK)

#define GPIO_ICR2_ICR20_MASK                     (0x300U)
#define GPIO_ICR2_ICR20_SHIFT                    (8U)
/*! ICR20 - Interrupt configuration field for GPIO interrupt 20
 *  0b00..Interrupt 20 is low-level sensitive.
 *  0b01..Interrupt 20 is high-level sensitive.
 *  0b10..Interrupt 20 is rising-edge sensitive.
 *  0b11..Interrupt 20 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR20(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR20_SHIFT)) & GPIO_ICR2_ICR20_MASK)

#define GPIO_ICR2_ICR21_MASK                     (0xC00U)
#define GPIO_ICR2_ICR21_SHIFT                    (10U)
/*! ICR21 - Interrupt configuration field for GPIO interrupt 21
 *  0b00..Interrupt 21 is low-level sensitive.
 *  0b01..Interrupt 21 is high-level sensitive.
 *  0b10..Interrupt 21 is rising-edge sensitive.
 *  0b11..Interrupt 21 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR21(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR21_SHIFT)) & GPIO_ICR2_ICR21_MASK)

#define GPIO_ICR2_ICR22_MASK                     (0x3000U)
#define GPIO_ICR2_ICR22_SHIFT                    (12U)
/*! ICR22 - Interrupt configuration field for GPIO interrupt 22
 *  0b00..Interrupt 22 is low-level sensitive.
 *  0b01..Interrupt 22 is high-level sensitive.
 *  0b10..Interrupt 22 is rising-edge sensitive.
 *  0b11..Interrupt 22 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR22(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR22_SHIFT)) & GPIO_ICR2_ICR22_MASK)

#define GPIO_ICR2_ICR23_MASK                     (0xC000U)
#define GPIO_ICR2_ICR23_SHIFT                    (14U)
/*! ICR23 - Interrupt configuration field for GPIO interrupt 23
 *  0b00..Interrupt 23 is low-level sensitive.
 *  0b01..Interrupt 23 is high-level sensitive.
 *  0b10..Interrupt 23 is rising-edge sensitive.
 *  0b11..Interrupt 23 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR23(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR23_SHIFT)) & GPIO_ICR2_ICR23_MASK)

#define GPIO_ICR2_ICR24_MASK                     (0x30000U)
#define GPIO_ICR2_ICR24_SHIFT                    (16U)
/*! ICR24 - Interrupt configuration field for GPIO interrupt 24
 *  0b00..Interrupt 24 is low-level sensitive.
 *  0b01..Interrupt 24 is high-level sensitive.
 *  0b10..Interrupt 24 is rising-edge sensitive.
 *  0b11..Interrupt 24 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR24(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR24_SHIFT)) & GPIO_ICR2_ICR24_MASK)

#define GPIO_ICR2_ICR25_MASK                     (0xC0000U)
#define GPIO_ICR2_ICR25_SHIFT                    (18U)
/*! ICR25 - Interrupt configuration field for GPIO interrupt 25
 *  0b00..Interrupt 25 is low-level sensitive.
 *  0b01..Interrupt 25 is high-level sensitive.
 *  0b10..Interrupt 25 is rising-edge sensitive.
 *  0b11..Interrupt 25 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR25(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR25_SHIFT)) & GPIO_ICR2_ICR25_MASK)

#define GPIO_ICR2_ICR26_MASK                     (0x300000U)
#define GPIO_ICR2_ICR26_SHIFT                    (20U)
/*! ICR26 - Interrupt configuration field for GPIO interrupt 26
 *  0b00..Interrupt 26 is low-level sensitive.
 *  0b01..Interrupt 26 is high-level sensitive.
 *  0b10..Interrupt 26 is rising-edge sensitive.
 *  0b11..Interrupt 26 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR26(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR26_SHIFT)) & GPIO_ICR2_ICR26_MASK)

#define GPIO_ICR2_ICR27_MASK                     (0xC00000U)
#define GPIO_ICR2_ICR27_SHIFT                    (22U)
/*! ICR27 - Interrupt configuration field for GPIO interrupt 27
 *  0b00..Interrupt 27 is low-level sensitive.
 *  0b01..Interrupt 27 is high-level sensitive.
 *  0b10..Interrupt 27 is rising-edge sensitive.
 *  0b11..Interrupt 27 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR27(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR27_SHIFT)) & GPIO_ICR2_ICR27_MASK)

#define GPIO_ICR2_ICR28_MASK                     (0x3000000U)
#define GPIO_ICR2_ICR28_SHIFT                    (24U)
/*! ICR28 - Interrupt configuration field for GPIO interrupt 28
 *  0b00..Interrupt 28 is low-level sensitive.
 *  0b01..Interrupt 28 is high-level sensitive.
 *  0b10..Interrupt 28 is rising-edge sensitive.
 *  0b11..Interrupt 28 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR28(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR28_SHIFT)) & GPIO_ICR2_ICR28_MASK)

#define GPIO_ICR2_ICR29_MASK                     (0xC000000U)
#define GPIO_ICR2_ICR29_SHIFT                    (26U)
/*! ICR29 - Interrupt configuration field for GPIO interrupt 29
 *  0b00..Interrupt 29 is low-level sensitive.
 *  0b01..Interrupt 29 is high-level sensitive.
 *  0b10..Interrupt 29 is rising-edge sensitive.
 *  0b11..Interrupt 29 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR29(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR29_SHIFT)) & GPIO_ICR2_ICR29_MASK)

#define GPIO_ICR2_ICR30_MASK                     (0x30000000U)
#define GPIO_ICR2_ICR30_SHIFT                    (28U)
/*! ICR30 - Interrupt configuration field for GPIO interrupt 30
 *  0b00..Interrupt 30 is low-level sensitive.
 *  0b01..Interrupt 30 is high-level sensitive.
 *  0b10..Interrupt 30 is rising-edge sensitive.
 *  0b11..Interrupt 30 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR30(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR30_SHIFT)) & GPIO_ICR2_ICR30_MASK)

#define GPIO_ICR2_ICR31_MASK                     (0xC0000000U)
#define GPIO_ICR2_ICR31_SHIFT                    (30U)
/*! ICR31 - Interrupt configuration field for GPIO interrupt 31
 *  0b00..Interrupt 31 is low-level sensitive.
 *  0b01..Interrupt 31 is high-level sensitive.
 *  0b10..Interrupt 31 is rising-edge sensitive.
 *  0b11..Interrupt 31 is falling-edge sensitive.
 */
#define GPIO_ICR2_ICR31(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_ICR2_ICR31_SHIFT)) & GPIO_ICR2_ICR31_MASK)
/*! @} */

/*! @name IMR - GPIO interrupt mask register */
/*! @{ */

#define GPIO_IMR_IMR_MASK                        (0xFFFFFFFFU)
#define GPIO_IMR_IMR_SHIFT                       (0U)
/*! IMR - Interrupt Mask bits */
#define GPIO_IMR_IMR(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_IMR_IMR_SHIFT)) & GPIO_IMR_IMR_MASK)
/*! @} */

/*! @name ISR - GPIO interrupt status register */
/*! @{ */

#define GPIO_ISR_ISR_MASK                        (0xFFFFFFFFU)
#define GPIO_ISR_ISR_SHIFT                       (0U)
/*! ISR - Interrupt status bits */
#define GPIO_ISR_ISR(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_ISR_ISR_SHIFT)) & GPIO_ISR_ISR_MASK)
/*! @} */

/*! @name EDGE_SEL - GPIO edge select register */
/*! @{ */

#define GPIO_EDGE_SEL_GPIO_EDGE_SEL_MASK         (0xFFFFFFFFU)
#define GPIO_EDGE_SEL_GPIO_EDGE_SEL_SHIFT        (0U)
/*! GPIO_EDGE_SEL - Edge select */
#define GPIO_EDGE_SEL_GPIO_EDGE_SEL(x)           (((uint32_t)(((uint32_t)(x)) << GPIO_EDGE_SEL_GPIO_EDGE_SEL_SHIFT)) & GPIO_EDGE_SEL_GPIO_EDGE_SEL_MASK)
/*! @} */

/*! @name DR_SET - GPIO data register SET */
/*! @{ */

#define GPIO_DR_SET_DR_SET_MASK                  (0xFFFFFFFFU)
#define GPIO_DR_SET_DR_SET_SHIFT                 (0U)
/*! DR_SET - Set */
#define GPIO_DR_SET_DR_SET(x)                    (((uint32_t)(((uint32_t)(x)) << GPIO_DR_SET_DR_SET_SHIFT)) & GPIO_DR_SET_DR_SET_MASK)
/*! @} */

/*! @name DR_CLEAR - GPIO data register CLEAR */
/*! @{ */

#define GPIO_DR_CLEAR_DR_CLEAR_MASK              (0xFFFFFFFFU)
#define GPIO_DR_CLEAR_DR_CLEAR_SHIFT             (0U)
/*! DR_CLEAR - Clear */
#define GPIO_DR_CLEAR_DR_CLEAR(x)                (((uint32_t)(((uint32_t)(x)) << GPIO_DR_CLEAR_DR_CLEAR_SHIFT)) & GPIO_DR_CLEAR_DR_CLEAR_MASK)
/*! @} */

/*! @name DR_TOGGLE - GPIO data register TOGGLE */
/*! @{ */

#define GPIO_DR_TOGGLE_DR_TOGGLE_MASK            (0xFFFFFFFFU)
#define GPIO_DR_TOGGLE_DR_TOGGLE_SHIFT           (0U)
/*! DR_TOGGLE - Toggle */
#define GPIO_DR_TOGGLE_DR_TOGGLE(x)              (((uint32_t)(((uint32_t)(x)) << GPIO_DR_TOGGLE_DR_TOGGLE_SHIFT)) & GPIO_DR_TOGGLE_DR_TOGGLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */


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


#endif  /* PERI_GPIO_H_ */

