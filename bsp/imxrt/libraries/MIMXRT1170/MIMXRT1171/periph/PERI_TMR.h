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
**         CMSIS Peripheral Access Layer for TMR
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
 * @file PERI_TMR.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for TMR
 *
 * CMSIS Peripheral Access Layer for TMR
 */

#if !defined(PERI_TMR_H_)
#define PERI_TMR_H_                              /**< Symbol preventing repeated inclusion */

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
   -- TMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Peripheral_Access_Layer TMR Peripheral Access Layer
 * @{
 */

/** TMR - Size of Registers Arrays */
#define TMR_CHANNEL_COUNT                         4u

/** TMR - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x20 */
    __IO uint16_t COMP1;                             /**< Timer Channel Compare Register 1, array offset: 0x0, array step: 0x20 */
    __IO uint16_t COMP2;                             /**< Timer Channel Compare Register 2, array offset: 0x2, array step: 0x20 */
    __IO uint16_t CAPT;                              /**< Timer Channel Capture Register, array offset: 0x4, array step: 0x20 */
    __IO uint16_t LOAD;                              /**< Timer Channel Load Register, array offset: 0x6, array step: 0x20 */
    __IO uint16_t HOLD;                              /**< Timer Channel Hold Register, array offset: 0x8, array step: 0x20 */
    __IO uint16_t CNTR;                              /**< Timer Channel Counter Register, array offset: 0xA, array step: 0x20 */
    __IO uint16_t CTRL;                              /**< Timer Channel Control Register, array offset: 0xC, array step: 0x20 */
    __IO uint16_t SCTRL;                             /**< Timer Channel Status and Control Register, array offset: 0xE, array step: 0x20 */
    __IO uint16_t CMPLD1;                            /**< Timer Channel Comparator Load Register 1, array offset: 0x10, array step: 0x20 */
    __IO uint16_t CMPLD2;                            /**< Timer Channel Comparator Load Register 2, array offset: 0x12, array step: 0x20 */
    __IO uint16_t CSCTRL;                            /**< Timer Channel Comparator Status and Control Register, array offset: 0x14, array step: 0x20 */
    __IO uint16_t FILT;                              /**< Timer Channel Input Filter Register, array offset: 0x16, array step: 0x20 */
    __IO uint16_t DMA;                               /**< Timer Channel DMA Enable Register, array offset: 0x18, array step: 0x20 */
         uint8_t RESERVED_0[4];
    __IO uint16_t ENBL;                              /**< Timer Channel Enable Register, array offset: 0x1E, array step: 0x20, valid indices: [0] */
  } CHANNEL[TMR_CHANNEL_COUNT];
} TMR_Type;

/* ----------------------------------------------------------------------------
   -- TMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Register_Masks TMR Register Masks
 * @{
 */

/*! @name COMP1 - Timer Channel Compare Register 1 */
/*! @{ */

#define TMR_COMP1_COMPARISON_1_MASK              (0xFFFFU)
#define TMR_COMP1_COMPARISON_1_SHIFT             (0U)
/*! COMPARISON_1 - Comparison Value 1 */
#define TMR_COMP1_COMPARISON_1(x)                (((uint16_t)(((uint16_t)(x)) << TMR_COMP1_COMPARISON_1_SHIFT)) & TMR_COMP1_COMPARISON_1_MASK)
/*! @} */

/* The count of TMR_COMP1 */
#define TMR_COMP1_COUNT                          (4U)

/*! @name COMP2 - Timer Channel Compare Register 2 */
/*! @{ */

#define TMR_COMP2_COMPARISON_2_MASK              (0xFFFFU)
#define TMR_COMP2_COMPARISON_2_SHIFT             (0U)
/*! COMPARISON_2 - Comparison Value 2 */
#define TMR_COMP2_COMPARISON_2(x)                (((uint16_t)(((uint16_t)(x)) << TMR_COMP2_COMPARISON_2_SHIFT)) & TMR_COMP2_COMPARISON_2_MASK)
/*! @} */

/* The count of TMR_COMP2 */
#define TMR_COMP2_COUNT                          (4U)

/*! @name CAPT - Timer Channel Capture Register */
/*! @{ */

#define TMR_CAPT_CAPTURE_MASK                    (0xFFFFU)
#define TMR_CAPT_CAPTURE_SHIFT                   (0U)
/*! CAPTURE - Capture Value */
#define TMR_CAPT_CAPTURE(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CAPT_CAPTURE_SHIFT)) & TMR_CAPT_CAPTURE_MASK)
/*! @} */

/* The count of TMR_CAPT */
#define TMR_CAPT_COUNT                           (4U)

/*! @name LOAD - Timer Channel Load Register */
/*! @{ */

#define TMR_LOAD_LOAD_MASK                       (0xFFFFU)
#define TMR_LOAD_LOAD_SHIFT                      (0U)
/*! LOAD - Timer Load Register */
#define TMR_LOAD_LOAD(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_LOAD_LOAD_SHIFT)) & TMR_LOAD_LOAD_MASK)
/*! @} */

/* The count of TMR_LOAD */
#define TMR_LOAD_COUNT                           (4U)

/*! @name HOLD - Timer Channel Hold Register */
/*! @{ */

#define TMR_HOLD_HOLD_MASK                       (0xFFFFU)
#define TMR_HOLD_HOLD_SHIFT                      (0U)
/*! HOLD - HOLD */
#define TMR_HOLD_HOLD(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_HOLD_HOLD_SHIFT)) & TMR_HOLD_HOLD_MASK)
/*! @} */

/* The count of TMR_HOLD */
#define TMR_HOLD_COUNT                           (4U)

/*! @name CNTR - Timer Channel Counter Register */
/*! @{ */

#define TMR_CNTR_COUNTER_MASK                    (0xFFFFU)
#define TMR_CNTR_COUNTER_SHIFT                   (0U)
/*! COUNTER - COUNTER */
#define TMR_CNTR_COUNTER(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CNTR_COUNTER_SHIFT)) & TMR_CNTR_COUNTER_MASK)
/*! @} */

/* The count of TMR_CNTR */
#define TMR_CNTR_COUNT                           (4U)

/*! @name CTRL - Timer Channel Control Register */
/*! @{ */

#define TMR_CTRL_OUTMODE_MASK                    (0x7U)
#define TMR_CTRL_OUTMODE_SHIFT                   (0U)
/*! OUTMODE - Output Mode
 *  0b000..Asserted while counter is active
 *  0b001..Clear OFLAG output on successful compare
 *  0b010..Set OFLAG output on successful compare
 *  0b011..Toggle OFLAG output on successful compare
 *  0b100..Toggle OFLAG output using alternating compare registers
 *  0b101..Set on compare, cleared on secondary source input edge
 *  0b110..Set on compare, cleared on counter rollover
 *  0b111..Enable gated clock output while counter is active
 */
#define TMR_CTRL_OUTMODE(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_OUTMODE_SHIFT)) & TMR_CTRL_OUTMODE_MASK)

#define TMR_CTRL_COINIT_MASK                     (0x8U)
#define TMR_CTRL_COINIT_SHIFT                    (3U)
/*! COINIT - Co-Channel Initialization
 *  0b0..Co-channel counter/timers cannot force a re-initialization of this counter/timer
 *  0b1..Co-channel counter/timers may force a re-initialization of this counter/timer
 */
#define TMR_CTRL_COINIT(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_COINIT_SHIFT)) & TMR_CTRL_COINIT_MASK)

#define TMR_CTRL_DIR_MASK                        (0x10U)
#define TMR_CTRL_DIR_SHIFT                       (4U)
/*! DIR - Count Direction
 *  0b0..Count up.
 *  0b1..Count down.
 */
#define TMR_CTRL_DIR(x)                          (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_DIR_SHIFT)) & TMR_CTRL_DIR_MASK)

#define TMR_CTRL_LENGTH_MASK                     (0x20U)
#define TMR_CTRL_LENGTH_SHIFT                    (5U)
/*! LENGTH - Count Length
 *  0b0..Count until roll over at $FFFF and continue from $0000.
 *  0b1..Count until compare, then re-initialize. If counting up, a successful compare occurs when the counter
 *       reaches a COMP1 value. If counting down, a successful compare occurs when the counter reaches a COMP2 value.
 *       When output mode $4 is used, alternating values of COMP1 and COMP2 are used to generate successful
 *       comparisons. For example, the counter counts until a COMP1 value is reached, re-initializes, counts until COMP2
 *       value is reached, re-initializes, counts until COMP1 value is reached, and so on.
 */
#define TMR_CTRL_LENGTH(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_LENGTH_SHIFT)) & TMR_CTRL_LENGTH_MASK)

#define TMR_CTRL_ONCE_MASK                       (0x40U)
#define TMR_CTRL_ONCE_SHIFT                      (6U)
/*! ONCE - Count Once
 *  0b0..Count repeatedly.
 *  0b1..Count until compare and then stop. If counting up, a successful compare occurs when the counter reaches a
 *       COMP1 value. If counting down, a successful compare occurs when the counter reaches a COMP2 value. When
 *       output mode $4 is used, the counter re-initializes after reaching the COMP1 value, continues to count to
 *       the COMP2 value, and then stops.
 */
#define TMR_CTRL_ONCE(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_ONCE_SHIFT)) & TMR_CTRL_ONCE_MASK)

#define TMR_CTRL_SCS_MASK                        (0x180U)
#define TMR_CTRL_SCS_SHIFT                       (7U)
/*! SCS - Secondary Count Source
 *  0b00..Counter 0 input pin
 *  0b01..Counter 1 input pin
 *  0b10..Counter 2 input pin
 *  0b11..Counter 3 input pin
 */
#define TMR_CTRL_SCS(x)                          (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_SCS_SHIFT)) & TMR_CTRL_SCS_MASK)

#define TMR_CTRL_PCS_MASK                        (0x1E00U)
#define TMR_CTRL_PCS_SHIFT                       (9U)
/*! PCS - Primary Count Source
 *  0b0000..Counter 0 input pin
 *  0b0001..Counter 1 input pin
 *  0b0010..Counter 2 input pin
 *  0b0011..Counter 3 input pin
 *  0b0100..Counter 0 output
 *  0b0101..Counter 1 output
 *  0b0110..Counter 2 output
 *  0b0111..Counter 3 output
 *  0b1000..IP bus clock divide by 1 prescaler
 *  0b1001..IP bus clock divide by 2 prescaler
 *  0b1010..IP bus clock divide by 4 prescaler
 *  0b1011..IP bus clock divide by 8 prescaler
 *  0b1100..IP bus clock divide by 16 prescaler
 *  0b1101..IP bus clock divide by 32 prescaler
 *  0b1110..IP bus clock divide by 64 prescaler
 *  0b1111..IP bus clock divide by 128 prescaler
 */
#define TMR_CTRL_PCS(x)                          (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_PCS_SHIFT)) & TMR_CTRL_PCS_MASK)

#define TMR_CTRL_CM_MASK                         (0xE000U)
#define TMR_CTRL_CM_SHIFT                        (13U)
/*! CM - Count Mode
 *  0b000..No operation
 *  0b001..Count rising edges of primary sourceRising edges are counted only when SCTRL[IPS] = 0. Falling edges
 *         are counted when SCTRL[IPS] = 1. If the primary count source is IP bus clock divide by 1, only rising
 *         edges are counted regardless of the value of SCTRL[IPS].
 *  0b010..Count rising and falling edges of primary sourceIP bus clock divide by 1 cannot be used as a primary count source in edge count mode.
 *  0b011..Count rising edges of primary source while secondary input high active
 *  0b100..Quadrature count mode, uses primary and secondary sources
 *  0b101..Count rising edges of primary source; secondary source specifies directionRising edges are counted only
 *         when SCTRL[IPS] = 0. Falling edges are counted when SCTRL[IPS] = 1.
 *  0b110..Edge of secondary source triggers primary count until compare
 *  0b111..Cascaded counter mode (up/down)The primary count source must be set to one of the counter outputs.
 */
#define TMR_CTRL_CM(x)                           (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_CM_SHIFT)) & TMR_CTRL_CM_MASK)
/*! @} */

/* The count of TMR_CTRL */
#define TMR_CTRL_COUNT                           (4U)

/*! @name SCTRL - Timer Channel Status and Control Register */
/*! @{ */

#define TMR_SCTRL_OEN_MASK                       (0x1U)
#define TMR_SCTRL_OEN_SHIFT                      (0U)
/*! OEN - Output Enable
 *  0b0..The external pin is configured as an input.
 *  0b1..The OFLAG output signal is driven on the external pin. Other timer groups using this external pin as
 *       their input see the driven value. The polarity of the signal is determined by OPS.
 */
#define TMR_SCTRL_OEN(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_OEN_SHIFT)) & TMR_SCTRL_OEN_MASK)

#define TMR_SCTRL_OPS_MASK                       (0x2U)
#define TMR_SCTRL_OPS_SHIFT                      (1U)
/*! OPS - Output Polarity Select
 *  0b0..True polarity.
 *  0b1..Inverted polarity.
 */
#define TMR_SCTRL_OPS(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_OPS_SHIFT)) & TMR_SCTRL_OPS_MASK)

#define TMR_SCTRL_FORCE_MASK                     (0x4U)
#define TMR_SCTRL_FORCE_SHIFT                    (2U)
/*! FORCE - Force OFLAG Output */
#define TMR_SCTRL_FORCE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_FORCE_SHIFT)) & TMR_SCTRL_FORCE_MASK)

#define TMR_SCTRL_VAL_MASK                       (0x8U)
#define TMR_SCTRL_VAL_SHIFT                      (3U)
/*! VAL - Forced OFLAG Value */
#define TMR_SCTRL_VAL(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_VAL_SHIFT)) & TMR_SCTRL_VAL_MASK)

#define TMR_SCTRL_EEOF_MASK                      (0x10U)
#define TMR_SCTRL_EEOF_SHIFT                     (4U)
/*! EEOF - Enable External OFLAG Force */
#define TMR_SCTRL_EEOF(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_EEOF_SHIFT)) & TMR_SCTRL_EEOF_MASK)

#define TMR_SCTRL_MSTR_MASK                      (0x20U)
#define TMR_SCTRL_MSTR_SHIFT                     (5U)
/*! MSTR - Master Mode */
#define TMR_SCTRL_MSTR(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_MSTR_SHIFT)) & TMR_SCTRL_MSTR_MASK)

#define TMR_SCTRL_CAPTURE_MODE_MASK              (0xC0U)
#define TMR_SCTRL_CAPTURE_MODE_SHIFT             (6U)
/*! CAPTURE_MODE - Input Capture Mode
 *  0b00..Capture function is disabled
 *  0b01..Load capture register on rising edge (when IPS=0) or falling edge (when IPS=1) of input
 *  0b10..Load capture register on falling edge (when IPS=0) or rising edge (when IPS=1) of input
 *  0b11..Load capture register on both edges of input
 */
#define TMR_SCTRL_CAPTURE_MODE(x)                (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_CAPTURE_MODE_SHIFT)) & TMR_SCTRL_CAPTURE_MODE_MASK)

#define TMR_SCTRL_INPUT_MASK                     (0x100U)
#define TMR_SCTRL_INPUT_SHIFT                    (8U)
/*! INPUT - External Input Signal */
#define TMR_SCTRL_INPUT(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_INPUT_SHIFT)) & TMR_SCTRL_INPUT_MASK)

#define TMR_SCTRL_IPS_MASK                       (0x200U)
#define TMR_SCTRL_IPS_SHIFT                      (9U)
/*! IPS - Input Polarity Select */
#define TMR_SCTRL_IPS(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_IPS_SHIFT)) & TMR_SCTRL_IPS_MASK)

#define TMR_SCTRL_IEFIE_MASK                     (0x400U)
#define TMR_SCTRL_IEFIE_SHIFT                    (10U)
/*! IEFIE - Input Edge Flag Interrupt Enable */
#define TMR_SCTRL_IEFIE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_IEFIE_SHIFT)) & TMR_SCTRL_IEFIE_MASK)

#define TMR_SCTRL_IEF_MASK                       (0x800U)
#define TMR_SCTRL_IEF_SHIFT                      (11U)
/*! IEF - Input Edge Flag */
#define TMR_SCTRL_IEF(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_IEF_SHIFT)) & TMR_SCTRL_IEF_MASK)

#define TMR_SCTRL_TOFIE_MASK                     (0x1000U)
#define TMR_SCTRL_TOFIE_SHIFT                    (12U)
/*! TOFIE - Timer Overflow Flag Interrupt Enable */
#define TMR_SCTRL_TOFIE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TOFIE_SHIFT)) & TMR_SCTRL_TOFIE_MASK)

#define TMR_SCTRL_TOF_MASK                       (0x2000U)
#define TMR_SCTRL_TOF_SHIFT                      (13U)
/*! TOF - Timer Overflow Flag */
#define TMR_SCTRL_TOF(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TOF_SHIFT)) & TMR_SCTRL_TOF_MASK)

#define TMR_SCTRL_TCFIE_MASK                     (0x4000U)
#define TMR_SCTRL_TCFIE_SHIFT                    (14U)
/*! TCFIE - Timer Compare Flag Interrupt Enable */
#define TMR_SCTRL_TCFIE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TCFIE_SHIFT)) & TMR_SCTRL_TCFIE_MASK)

#define TMR_SCTRL_TCF_MASK                       (0x8000U)
#define TMR_SCTRL_TCF_SHIFT                      (15U)
/*! TCF - Timer Compare Flag */
#define TMR_SCTRL_TCF(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TCF_SHIFT)) & TMR_SCTRL_TCF_MASK)
/*! @} */

/* The count of TMR_SCTRL */
#define TMR_SCTRL_COUNT                          (4U)

/*! @name CMPLD1 - Timer Channel Comparator Load Register 1 */
/*! @{ */

#define TMR_CMPLD1_COMPARATOR_LOAD_1_MASK        (0xFFFFU)
#define TMR_CMPLD1_COMPARATOR_LOAD_1_SHIFT       (0U)
/*! COMPARATOR_LOAD_1 - COMPARATOR_LOAD_1 */
#define TMR_CMPLD1_COMPARATOR_LOAD_1(x)          (((uint16_t)(((uint16_t)(x)) << TMR_CMPLD1_COMPARATOR_LOAD_1_SHIFT)) & TMR_CMPLD1_COMPARATOR_LOAD_1_MASK)
/*! @} */

/* The count of TMR_CMPLD1 */
#define TMR_CMPLD1_COUNT                         (4U)

/*! @name CMPLD2 - Timer Channel Comparator Load Register 2 */
/*! @{ */

#define TMR_CMPLD2_COMPARATOR_LOAD_2_MASK        (0xFFFFU)
#define TMR_CMPLD2_COMPARATOR_LOAD_2_SHIFT       (0U)
/*! COMPARATOR_LOAD_2 - COMPARATOR_LOAD_2 */
#define TMR_CMPLD2_COMPARATOR_LOAD_2(x)          (((uint16_t)(((uint16_t)(x)) << TMR_CMPLD2_COMPARATOR_LOAD_2_SHIFT)) & TMR_CMPLD2_COMPARATOR_LOAD_2_MASK)
/*! @} */

/* The count of TMR_CMPLD2 */
#define TMR_CMPLD2_COUNT                         (4U)

/*! @name CSCTRL - Timer Channel Comparator Status and Control Register */
/*! @{ */

#define TMR_CSCTRL_CL1_MASK                      (0x3U)
#define TMR_CSCTRL_CL1_SHIFT                     (0U)
/*! CL1 - Compare Load Control 1
 *  0b00..Never preload
 *  0b01..Load upon successful compare with the value in COMP1
 *  0b10..Load upon successful compare with the value in COMP2
 *  0b11..Reserved
 */
#define TMR_CSCTRL_CL1(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_CL1_SHIFT)) & TMR_CSCTRL_CL1_MASK)

#define TMR_CSCTRL_CL2_MASK                      (0xCU)
#define TMR_CSCTRL_CL2_SHIFT                     (2U)
/*! CL2 - Compare Load Control 2
 *  0b00..Never preload
 *  0b01..Load upon successful compare with the value in COMP1
 *  0b10..Load upon successful compare with the value in COMP2
 *  0b11..Reserved
 */
#define TMR_CSCTRL_CL2(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_CL2_SHIFT)) & TMR_CSCTRL_CL2_MASK)

#define TMR_CSCTRL_TCF1_MASK                     (0x10U)
#define TMR_CSCTRL_TCF1_SHIFT                    (4U)
/*! TCF1 - Timer Compare 1 Interrupt Flag */
#define TMR_CSCTRL_TCF1(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF1_SHIFT)) & TMR_CSCTRL_TCF1_MASK)

#define TMR_CSCTRL_TCF2_MASK                     (0x20U)
#define TMR_CSCTRL_TCF2_SHIFT                    (5U)
/*! TCF2 - Timer Compare 2 Interrupt Flag */
#define TMR_CSCTRL_TCF2(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF2_SHIFT)) & TMR_CSCTRL_TCF2_MASK)

#define TMR_CSCTRL_TCF1EN_MASK                   (0x40U)
#define TMR_CSCTRL_TCF1EN_SHIFT                  (6U)
/*! TCF1EN - Timer Compare 1 Interrupt Enable */
#define TMR_CSCTRL_TCF1EN(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF1EN_SHIFT)) & TMR_CSCTRL_TCF1EN_MASK)

#define TMR_CSCTRL_TCF2EN_MASK                   (0x80U)
#define TMR_CSCTRL_TCF2EN_SHIFT                  (7U)
/*! TCF2EN - Timer Compare 2 Interrupt Enable */
#define TMR_CSCTRL_TCF2EN(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF2EN_SHIFT)) & TMR_CSCTRL_TCF2EN_MASK)

#define TMR_CSCTRL_OFLAG_MASK                    (0x100U)
#define TMR_CSCTRL_OFLAG_SHIFT                   (8U)
/*! OFLAG - Output flag */
#define TMR_CSCTRL_OFLAG(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_OFLAG_SHIFT)) & TMR_CSCTRL_OFLAG_MASK)

#define TMR_CSCTRL_UP_MASK                       (0x200U)
#define TMR_CSCTRL_UP_SHIFT                      (9U)
/*! UP - Counting Direction Indicator
 *  0b0..The last count was in the DOWN direction.
 *  0b1..The last count was in the UP direction.
 */
#define TMR_CSCTRL_UP(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_UP_SHIFT)) & TMR_CSCTRL_UP_MASK)

#define TMR_CSCTRL_TCI_MASK                      (0x400U)
#define TMR_CSCTRL_TCI_SHIFT                     (10U)
/*! TCI - Triggered Count Initialization Control
 *  0b0..Stop the counter upon receiving a second trigger event while still counting from the first trigger event.
 *  0b1..Reload the counter upon receiving a second trigger event while still counting from the first trigger event.
 */
#define TMR_CSCTRL_TCI(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCI_SHIFT)) & TMR_CSCTRL_TCI_MASK)

#define TMR_CSCTRL_ROC_MASK                      (0x800U)
#define TMR_CSCTRL_ROC_SHIFT                     (11U)
/*! ROC - Reload on Capture
 *  0b0..Disables
 *  0b1..Enables
 */
#define TMR_CSCTRL_ROC(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_ROC_SHIFT)) & TMR_CSCTRL_ROC_MASK)

#define TMR_CSCTRL_ALT_LOAD_MASK                 (0x1000U)
#define TMR_CSCTRL_ALT_LOAD_SHIFT                (12U)
/*! ALT_LOAD - Alternative Load Enable
 *  0b0..Counter can be re-initialized only with the LOAD register.
 *  0b1..Counter can be re-initialized with the LOAD or CMPLD2 registers depending on count direction.
 */
#define TMR_CSCTRL_ALT_LOAD(x)                   (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_ALT_LOAD_SHIFT)) & TMR_CSCTRL_ALT_LOAD_MASK)

#define TMR_CSCTRL_FAULT_MASK                    (0x2000U)
#define TMR_CSCTRL_FAULT_SHIFT                   (13U)
/*! FAULT - Fault Enable
 *  0b0..Disables
 *  0b1..Enables
 */
#define TMR_CSCTRL_FAULT(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_FAULT_SHIFT)) & TMR_CSCTRL_FAULT_MASK)

#define TMR_CSCTRL_DBG_EN_MASK                   (0xC000U)
#define TMR_CSCTRL_DBG_EN_SHIFT                  (14U)
/*! DBG_EN - Debug Actions Enable
 *  0b00..Continue with normal operation during debug mode. (default)
 *  0b01..Halt TMR counter during debug mode.
 *  0b10..Force TMR output to logic 0 (prior to consideration of SCTRL[OPS]).
 *  0b11..Both halt counter and force output to 0 during debug mode.
 */
#define TMR_CSCTRL_DBG_EN(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_DBG_EN_SHIFT)) & TMR_CSCTRL_DBG_EN_MASK)
/*! @} */

/* The count of TMR_CSCTRL */
#define TMR_CSCTRL_COUNT                         (4U)

/*! @name FILT - Timer Channel Input Filter Register */
/*! @{ */

#define TMR_FILT_FILT_PER_MASK                   (0xFFU)
#define TMR_FILT_FILT_PER_SHIFT                  (0U)
/*! FILT_PER - Input Filter Sample Period */
#define TMR_FILT_FILT_PER(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_FILT_FILT_PER_SHIFT)) & TMR_FILT_FILT_PER_MASK)

#define TMR_FILT_FILT_CNT_MASK                   (0x700U)
#define TMR_FILT_FILT_CNT_SHIFT                  (8U)
/*! FILT_CNT - Input Filter Sample Count */
#define TMR_FILT_FILT_CNT(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_FILT_FILT_CNT_SHIFT)) & TMR_FILT_FILT_CNT_MASK)
/*! @} */

/* The count of TMR_FILT */
#define TMR_FILT_COUNT                           (4U)

/*! @name DMA - Timer Channel DMA Enable Register */
/*! @{ */

#define TMR_DMA_IEFDE_MASK                       (0x1U)
#define TMR_DMA_IEFDE_SHIFT                      (0U)
/*! IEFDE - Input Edge Flag DMA Enable */
#define TMR_DMA_IEFDE(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_DMA_IEFDE_SHIFT)) & TMR_DMA_IEFDE_MASK)

#define TMR_DMA_CMPLD1DE_MASK                    (0x2U)
#define TMR_DMA_CMPLD1DE_SHIFT                   (1U)
/*! CMPLD1DE - Comparator Preload Register 1 DMA Enable */
#define TMR_DMA_CMPLD1DE(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_DMA_CMPLD1DE_SHIFT)) & TMR_DMA_CMPLD1DE_MASK)

#define TMR_DMA_CMPLD2DE_MASK                    (0x4U)
#define TMR_DMA_CMPLD2DE_SHIFT                   (2U)
/*! CMPLD2DE - Comparator Preload Register 2 DMA Enable */
#define TMR_DMA_CMPLD2DE(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_DMA_CMPLD2DE_SHIFT)) & TMR_DMA_CMPLD2DE_MASK)
/*! @} */

/* The count of TMR_DMA */
#define TMR_DMA_COUNT                            (4U)

/*! @name ENBL - Timer Channel Enable Register */
/*! @{ */

#define TMR_ENBL_ENBL_MASK                       (0xFU)
#define TMR_ENBL_ENBL_SHIFT                      (0U)
/*! ENBL - Timer Channel Enable
 *  0b0000..Disables the timer channel.
 *  0b0001..Enables the timer channel. (default)
 */
#define TMR_ENBL_ENBL(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_ENBL_ENBL_SHIFT)) & TMR_ENBL_ENBL_MASK)
/*! @} */

/* The count of TMR_ENBL */
#define TMR_ENBL_COUNT                           (4U)


/*!
 * @}
 */ /* end of group TMR_Register_Masks */


/*!
 * @}
 */ /* end of group TMR_Peripheral_Access_Layer */


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


#endif  /* PERI_TMR_H_ */

