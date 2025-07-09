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
**         CMSIS Peripheral Access Layer for TMPSNS
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
 * @file PERI_TMPSNS.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for TMPSNS
 *
 * CMSIS Peripheral Access Layer for TMPSNS
 */

#if !defined(PERI_TMPSNS_H_)
#define PERI_TMPSNS_H_                           /**< Symbol preventing repeated inclusion */

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
   -- TMPSNS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMPSNS_Peripheral_Access_Layer TMPSNS Peripheral Access Layer
 * @{
 */

/** TMPSNS - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL0;                             /**< Temperature Sensor Control Register 0, offset: 0x0 */
  __IO uint32_t CTRL0_SET;                         /**< Temperature Sensor Control Register 0, offset: 0x4 */
  __IO uint32_t CTRL0_CLR;                         /**< Temperature Sensor Control Register 0, offset: 0x8 */
  __IO uint32_t CTRL0_TOG;                         /**< Temperature Sensor Control Register 0, offset: 0xC */
  __IO uint32_t CTRL1;                             /**< Temperature Sensor Control Register 1, offset: 0x10 */
  __IO uint32_t CTRL1_SET;                         /**< Temperature Sensor Control Register 1, offset: 0x14 */
  __IO uint32_t CTRL1_CLR;                         /**< Temperature Sensor Control Register 1, offset: 0x18 */
  __IO uint32_t CTRL1_TOG;                         /**< Temperature Sensor Control Register 1, offset: 0x1C */
  __IO uint32_t RANGE0;                            /**< Temperature Sensor Range Register 0, offset: 0x20 */
  __IO uint32_t RANGE0_SET;                        /**< Temperature Sensor Range Register 0, offset: 0x24 */
  __IO uint32_t RANGE0_CLR;                        /**< Temperature Sensor Range Register 0, offset: 0x28 */
  __IO uint32_t RANGE0_TOG;                        /**< Temperature Sensor Range Register 0, offset: 0x2C */
  __IO uint32_t RANGE1;                            /**< Temperature Sensor Range Register 1, offset: 0x30 */
  __IO uint32_t RANGE1_SET;                        /**< Temperature Sensor Range Register 1, offset: 0x34 */
  __IO uint32_t RANGE1_CLR;                        /**< Temperature Sensor Range Register 1, offset: 0x38 */
  __IO uint32_t RANGE1_TOG;                        /**< Temperature Sensor Range Register 1, offset: 0x3C */
       uint8_t RESERVED_0[16];
  __IO uint32_t STATUS0;                           /**< Temperature Sensor Status Register 0, offset: 0x50 */
} TMPSNS_Type;

/* ----------------------------------------------------------------------------
   -- TMPSNS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMPSNS_Register_Masks TMPSNS Register Masks
 * @{
 */

/*! @name CTRL0 - Temperature Sensor Control Register 0 */
/*! @{ */

#define TMPSNS_CTRL0_SLOPE_CAL_MASK              (0x3FU)
#define TMPSNS_CTRL0_SLOPE_CAL_SHIFT             (0U)
/*! SLOPE_CAL - Ramp slope calibration control */
#define TMPSNS_CTRL0_SLOPE_CAL(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_SLOPE_CAL_SHIFT)) & TMPSNS_CTRL0_SLOPE_CAL_MASK)

#define TMPSNS_CTRL0_V_SEL_MASK                  (0x300U)
#define TMPSNS_CTRL0_V_SEL_SHIFT                 (8U)
/*! V_SEL - Voltage Select
 *  0b00..Normal temperature measuring mode
 *  0b01-0b10..Reserved
 */
#define TMPSNS_CTRL0_V_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_V_SEL_SHIFT)) & TMPSNS_CTRL0_V_SEL_MASK)

#define TMPSNS_CTRL0_IBIAS_TRIM_MASK             (0xF000U)
#define TMPSNS_CTRL0_IBIAS_TRIM_SHIFT            (12U)
/*! IBIAS_TRIM - Current bias trim value */
#define TMPSNS_CTRL0_IBIAS_TRIM(x)               (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_IBIAS_TRIM_SHIFT)) & TMPSNS_CTRL0_IBIAS_TRIM_MASK)
/*! @} */

/*! @name CTRL0_SET - Temperature Sensor Control Register 0 */
/*! @{ */

#define TMPSNS_CTRL0_SET_SLOPE_CAL_MASK          (0x3FU)
#define TMPSNS_CTRL0_SET_SLOPE_CAL_SHIFT         (0U)
/*! SLOPE_CAL - Ramp slope calibration control */
#define TMPSNS_CTRL0_SET_SLOPE_CAL(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_SET_SLOPE_CAL_SHIFT)) & TMPSNS_CTRL0_SET_SLOPE_CAL_MASK)

#define TMPSNS_CTRL0_SET_V_SEL_MASK              (0x300U)
#define TMPSNS_CTRL0_SET_V_SEL_SHIFT             (8U)
/*! V_SEL - Voltage Select */
#define TMPSNS_CTRL0_SET_V_SEL(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_SET_V_SEL_SHIFT)) & TMPSNS_CTRL0_SET_V_SEL_MASK)

#define TMPSNS_CTRL0_SET_IBIAS_TRIM_MASK         (0xF000U)
#define TMPSNS_CTRL0_SET_IBIAS_TRIM_SHIFT        (12U)
/*! IBIAS_TRIM - Current bias trim value */
#define TMPSNS_CTRL0_SET_IBIAS_TRIM(x)           (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_SET_IBIAS_TRIM_SHIFT)) & TMPSNS_CTRL0_SET_IBIAS_TRIM_MASK)
/*! @} */

/*! @name CTRL0_CLR - Temperature Sensor Control Register 0 */
/*! @{ */

#define TMPSNS_CTRL0_CLR_SLOPE_CAL_MASK          (0x3FU)
#define TMPSNS_CTRL0_CLR_SLOPE_CAL_SHIFT         (0U)
/*! SLOPE_CAL - Ramp slope calibration control */
#define TMPSNS_CTRL0_CLR_SLOPE_CAL(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_CLR_SLOPE_CAL_SHIFT)) & TMPSNS_CTRL0_CLR_SLOPE_CAL_MASK)

#define TMPSNS_CTRL0_CLR_V_SEL_MASK              (0x300U)
#define TMPSNS_CTRL0_CLR_V_SEL_SHIFT             (8U)
/*! V_SEL - Voltage Select */
#define TMPSNS_CTRL0_CLR_V_SEL(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_CLR_V_SEL_SHIFT)) & TMPSNS_CTRL0_CLR_V_SEL_MASK)

#define TMPSNS_CTRL0_CLR_IBIAS_TRIM_MASK         (0xF000U)
#define TMPSNS_CTRL0_CLR_IBIAS_TRIM_SHIFT        (12U)
/*! IBIAS_TRIM - Current bias trim value */
#define TMPSNS_CTRL0_CLR_IBIAS_TRIM(x)           (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_CLR_IBIAS_TRIM_SHIFT)) & TMPSNS_CTRL0_CLR_IBIAS_TRIM_MASK)
/*! @} */

/*! @name CTRL0_TOG - Temperature Sensor Control Register 0 */
/*! @{ */

#define TMPSNS_CTRL0_TOG_SLOPE_CAL_MASK          (0x3FU)
#define TMPSNS_CTRL0_TOG_SLOPE_CAL_SHIFT         (0U)
/*! SLOPE_CAL - Ramp slope calibration control */
#define TMPSNS_CTRL0_TOG_SLOPE_CAL(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_TOG_SLOPE_CAL_SHIFT)) & TMPSNS_CTRL0_TOG_SLOPE_CAL_MASK)

#define TMPSNS_CTRL0_TOG_V_SEL_MASK              (0x300U)
#define TMPSNS_CTRL0_TOG_V_SEL_SHIFT             (8U)
/*! V_SEL - Voltage Select */
#define TMPSNS_CTRL0_TOG_V_SEL(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_TOG_V_SEL_SHIFT)) & TMPSNS_CTRL0_TOG_V_SEL_MASK)

#define TMPSNS_CTRL0_TOG_IBIAS_TRIM_MASK         (0xF000U)
#define TMPSNS_CTRL0_TOG_IBIAS_TRIM_SHIFT        (12U)
/*! IBIAS_TRIM - Current bias trim value */
#define TMPSNS_CTRL0_TOG_IBIAS_TRIM(x)           (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL0_TOG_IBIAS_TRIM_SHIFT)) & TMPSNS_CTRL0_TOG_IBIAS_TRIM_MASK)
/*! @} */

/*! @name CTRL1 - Temperature Sensor Control Register 1 */
/*! @{ */

#define TMPSNS_CTRL1_FREQ_MASK                   (0xFFFFU)
#define TMPSNS_CTRL1_FREQ_SHIFT                  (0U)
/*! FREQ - Temperature Measurement Frequency
 *  0b0000000000000000..Single Reading Mode. New reading available every time CTRL1[START] bit is set to 1 from 0.
 *  0b0000000000000001-0b1111111111111111..Continuous Reading Mode. Next temperature reading taken after programmed number of cycles after current reading is complete.
 */
#define TMPSNS_CTRL1_FREQ(x)                     (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_FREQ_SHIFT)) & TMPSNS_CTRL1_FREQ_MASK)

#define TMPSNS_CTRL1_FINISH_IE_MASK              (0x10000U)
#define TMPSNS_CTRL1_FINISH_IE_SHIFT             (16U)
/*! FINISH_IE - Measurement finished interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define TMPSNS_CTRL1_FINISH_IE(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_FINISH_IE_SHIFT)) & TMPSNS_CTRL1_FINISH_IE_MASK)

#define TMPSNS_CTRL1_LOW_TEMP_IE_MASK            (0x20000U)
#define TMPSNS_CTRL1_LOW_TEMP_IE_SHIFT           (17U)
/*! LOW_TEMP_IE - Low temperature interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define TMPSNS_CTRL1_LOW_TEMP_IE(x)              (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_LOW_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_LOW_TEMP_IE_MASK)

#define TMPSNS_CTRL1_HIGH_TEMP_IE_MASK           (0x40000U)
#define TMPSNS_CTRL1_HIGH_TEMP_IE_SHIFT          (18U)
/*! HIGH_TEMP_IE - High temperature interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define TMPSNS_CTRL1_HIGH_TEMP_IE(x)             (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_HIGH_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_HIGH_TEMP_IE_MASK)

#define TMPSNS_CTRL1_PANIC_TEMP_IE_MASK          (0x80000U)
#define TMPSNS_CTRL1_PANIC_TEMP_IE_SHIFT         (19U)
/*! PANIC_TEMP_IE - Panic temperature interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define TMPSNS_CTRL1_PANIC_TEMP_IE(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_PANIC_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_PANIC_TEMP_IE_MASK)

#define TMPSNS_CTRL1_START_MASK                  (0x400000U)
#define TMPSNS_CTRL1_START_SHIFT                 (22U)
/*! START - Start Temperature Measurement
 *  0b0..No new temperature reading taken
 *  0b1..Initiate a new temperature reading
 */
#define TMPSNS_CTRL1_START(x)                    (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_START_SHIFT)) & TMPSNS_CTRL1_START_MASK)

#define TMPSNS_CTRL1_PWD_MASK                    (0x800000U)
#define TMPSNS_CTRL1_PWD_SHIFT                   (23U)
/*! PWD - Temperature Sensor Power Down
 *  0b0..Sensor is active
 *  0b1..Sensor is powered down
 */
#define TMPSNS_CTRL1_PWD(x)                      (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_PWD_SHIFT)) & TMPSNS_CTRL1_PWD_MASK)

#define TMPSNS_CTRL1_RFU_MASK                    (0x7F000000U)
#define TMPSNS_CTRL1_RFU_SHIFT                   (24U)
/*! RFU - Read/Writeable field. Reserved for future use */
#define TMPSNS_CTRL1_RFU(x)                      (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_RFU_SHIFT)) & TMPSNS_CTRL1_RFU_MASK)

#define TMPSNS_CTRL1_PWD_FULL_MASK               (0x80000000U)
#define TMPSNS_CTRL1_PWD_FULL_SHIFT              (31U)
/*! PWD_FULL - Temperature Sensor Full Power Down
 *  0b0..Sensor is active
 *  0b1..Sensor is powered down
 */
#define TMPSNS_CTRL1_PWD_FULL(x)                 (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_PWD_FULL_SHIFT)) & TMPSNS_CTRL1_PWD_FULL_MASK)
/*! @} */

/*! @name CTRL1_SET - Temperature Sensor Control Register 1 */
/*! @{ */

#define TMPSNS_CTRL1_SET_FREQ_MASK               (0xFFFFU)
#define TMPSNS_CTRL1_SET_FREQ_SHIFT              (0U)
/*! FREQ - Temperature Measurement Frequency */
#define TMPSNS_CTRL1_SET_FREQ(x)                 (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_FREQ_SHIFT)) & TMPSNS_CTRL1_SET_FREQ_MASK)

#define TMPSNS_CTRL1_SET_FINISH_IE_MASK          (0x10000U)
#define TMPSNS_CTRL1_SET_FINISH_IE_SHIFT         (16U)
/*! FINISH_IE - Measurement finished interrupt enable */
#define TMPSNS_CTRL1_SET_FINISH_IE(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_FINISH_IE_SHIFT)) & TMPSNS_CTRL1_SET_FINISH_IE_MASK)

#define TMPSNS_CTRL1_SET_LOW_TEMP_IE_MASK        (0x20000U)
#define TMPSNS_CTRL1_SET_LOW_TEMP_IE_SHIFT       (17U)
/*! LOW_TEMP_IE - Low temperature interrupt enable */
#define TMPSNS_CTRL1_SET_LOW_TEMP_IE(x)          (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_LOW_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_SET_LOW_TEMP_IE_MASK)

#define TMPSNS_CTRL1_SET_HIGH_TEMP_IE_MASK       (0x40000U)
#define TMPSNS_CTRL1_SET_HIGH_TEMP_IE_SHIFT      (18U)
/*! HIGH_TEMP_IE - High temperature interrupt enable */
#define TMPSNS_CTRL1_SET_HIGH_TEMP_IE(x)         (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_HIGH_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_SET_HIGH_TEMP_IE_MASK)

#define TMPSNS_CTRL1_SET_PANIC_TEMP_IE_MASK      (0x80000U)
#define TMPSNS_CTRL1_SET_PANIC_TEMP_IE_SHIFT     (19U)
/*! PANIC_TEMP_IE - Panic temperature interrupt enable */
#define TMPSNS_CTRL1_SET_PANIC_TEMP_IE(x)        (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_PANIC_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_SET_PANIC_TEMP_IE_MASK)

#define TMPSNS_CTRL1_SET_START_MASK              (0x400000U)
#define TMPSNS_CTRL1_SET_START_SHIFT             (22U)
/*! START - Start Temperature Measurement */
#define TMPSNS_CTRL1_SET_START(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_START_SHIFT)) & TMPSNS_CTRL1_SET_START_MASK)

#define TMPSNS_CTRL1_SET_PWD_MASK                (0x800000U)
#define TMPSNS_CTRL1_SET_PWD_SHIFT               (23U)
/*! PWD - Temperature Sensor Power Down */
#define TMPSNS_CTRL1_SET_PWD(x)                  (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_PWD_SHIFT)) & TMPSNS_CTRL1_SET_PWD_MASK)

#define TMPSNS_CTRL1_SET_RFU_MASK                (0x7F000000U)
#define TMPSNS_CTRL1_SET_RFU_SHIFT               (24U)
/*! RFU - Read/Writeable field. Reserved for future use */
#define TMPSNS_CTRL1_SET_RFU(x)                  (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_RFU_SHIFT)) & TMPSNS_CTRL1_SET_RFU_MASK)

#define TMPSNS_CTRL1_SET_PWD_FULL_MASK           (0x80000000U)
#define TMPSNS_CTRL1_SET_PWD_FULL_SHIFT          (31U)
/*! PWD_FULL - Temperature Sensor Full Power Down */
#define TMPSNS_CTRL1_SET_PWD_FULL(x)             (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_SET_PWD_FULL_SHIFT)) & TMPSNS_CTRL1_SET_PWD_FULL_MASK)
/*! @} */

/*! @name CTRL1_CLR - Temperature Sensor Control Register 1 */
/*! @{ */

#define TMPSNS_CTRL1_CLR_FREQ_MASK               (0xFFFFU)
#define TMPSNS_CTRL1_CLR_FREQ_SHIFT              (0U)
/*! FREQ - Temperature Measurement Frequency */
#define TMPSNS_CTRL1_CLR_FREQ(x)                 (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_FREQ_SHIFT)) & TMPSNS_CTRL1_CLR_FREQ_MASK)

#define TMPSNS_CTRL1_CLR_FINISH_IE_MASK          (0x10000U)
#define TMPSNS_CTRL1_CLR_FINISH_IE_SHIFT         (16U)
/*! FINISH_IE - Measurement finished interrupt enable */
#define TMPSNS_CTRL1_CLR_FINISH_IE(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_FINISH_IE_SHIFT)) & TMPSNS_CTRL1_CLR_FINISH_IE_MASK)

#define TMPSNS_CTRL1_CLR_LOW_TEMP_IE_MASK        (0x20000U)
#define TMPSNS_CTRL1_CLR_LOW_TEMP_IE_SHIFT       (17U)
/*! LOW_TEMP_IE - Low temperature interrupt enable */
#define TMPSNS_CTRL1_CLR_LOW_TEMP_IE(x)          (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_LOW_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_CLR_LOW_TEMP_IE_MASK)

#define TMPSNS_CTRL1_CLR_HIGH_TEMP_IE_MASK       (0x40000U)
#define TMPSNS_CTRL1_CLR_HIGH_TEMP_IE_SHIFT      (18U)
/*! HIGH_TEMP_IE - High temperature interrupt enable */
#define TMPSNS_CTRL1_CLR_HIGH_TEMP_IE(x)         (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_HIGH_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_CLR_HIGH_TEMP_IE_MASK)

#define TMPSNS_CTRL1_CLR_PANIC_TEMP_IE_MASK      (0x80000U)
#define TMPSNS_CTRL1_CLR_PANIC_TEMP_IE_SHIFT     (19U)
/*! PANIC_TEMP_IE - Panic temperature interrupt enable */
#define TMPSNS_CTRL1_CLR_PANIC_TEMP_IE(x)        (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_PANIC_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_CLR_PANIC_TEMP_IE_MASK)

#define TMPSNS_CTRL1_CLR_START_MASK              (0x400000U)
#define TMPSNS_CTRL1_CLR_START_SHIFT             (22U)
/*! START - Start Temperature Measurement */
#define TMPSNS_CTRL1_CLR_START(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_START_SHIFT)) & TMPSNS_CTRL1_CLR_START_MASK)

#define TMPSNS_CTRL1_CLR_PWD_MASK                (0x800000U)
#define TMPSNS_CTRL1_CLR_PWD_SHIFT               (23U)
/*! PWD - Temperature Sensor Power Down */
#define TMPSNS_CTRL1_CLR_PWD(x)                  (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_PWD_SHIFT)) & TMPSNS_CTRL1_CLR_PWD_MASK)

#define TMPSNS_CTRL1_CLR_RFU_MASK                (0x7F000000U)
#define TMPSNS_CTRL1_CLR_RFU_SHIFT               (24U)
/*! RFU - Read/Writeable field. Reserved for future use */
#define TMPSNS_CTRL1_CLR_RFU(x)                  (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_RFU_SHIFT)) & TMPSNS_CTRL1_CLR_RFU_MASK)

#define TMPSNS_CTRL1_CLR_PWD_FULL_MASK           (0x80000000U)
#define TMPSNS_CTRL1_CLR_PWD_FULL_SHIFT          (31U)
/*! PWD_FULL - Temperature Sensor Full Power Down */
#define TMPSNS_CTRL1_CLR_PWD_FULL(x)             (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_CLR_PWD_FULL_SHIFT)) & TMPSNS_CTRL1_CLR_PWD_FULL_MASK)
/*! @} */

/*! @name CTRL1_TOG - Temperature Sensor Control Register 1 */
/*! @{ */

#define TMPSNS_CTRL1_TOG_FREQ_MASK               (0xFFFFU)
#define TMPSNS_CTRL1_TOG_FREQ_SHIFT              (0U)
/*! FREQ - Temperature Measurement Frequency */
#define TMPSNS_CTRL1_TOG_FREQ(x)                 (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_FREQ_SHIFT)) & TMPSNS_CTRL1_TOG_FREQ_MASK)

#define TMPSNS_CTRL1_TOG_FINISH_IE_MASK          (0x10000U)
#define TMPSNS_CTRL1_TOG_FINISH_IE_SHIFT         (16U)
/*! FINISH_IE - Measurement finished interrupt enable */
#define TMPSNS_CTRL1_TOG_FINISH_IE(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_FINISH_IE_SHIFT)) & TMPSNS_CTRL1_TOG_FINISH_IE_MASK)

#define TMPSNS_CTRL1_TOG_LOW_TEMP_IE_MASK        (0x20000U)
#define TMPSNS_CTRL1_TOG_LOW_TEMP_IE_SHIFT       (17U)
/*! LOW_TEMP_IE - Low temperature interrupt enable */
#define TMPSNS_CTRL1_TOG_LOW_TEMP_IE(x)          (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_LOW_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_TOG_LOW_TEMP_IE_MASK)

#define TMPSNS_CTRL1_TOG_HIGH_TEMP_IE_MASK       (0x40000U)
#define TMPSNS_CTRL1_TOG_HIGH_TEMP_IE_SHIFT      (18U)
/*! HIGH_TEMP_IE - High temperature interrupt enable */
#define TMPSNS_CTRL1_TOG_HIGH_TEMP_IE(x)         (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_HIGH_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_TOG_HIGH_TEMP_IE_MASK)

#define TMPSNS_CTRL1_TOG_PANIC_TEMP_IE_MASK      (0x80000U)
#define TMPSNS_CTRL1_TOG_PANIC_TEMP_IE_SHIFT     (19U)
/*! PANIC_TEMP_IE - Panic temperature interrupt enable */
#define TMPSNS_CTRL1_TOG_PANIC_TEMP_IE(x)        (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_PANIC_TEMP_IE_SHIFT)) & TMPSNS_CTRL1_TOG_PANIC_TEMP_IE_MASK)

#define TMPSNS_CTRL1_TOG_START_MASK              (0x400000U)
#define TMPSNS_CTRL1_TOG_START_SHIFT             (22U)
/*! START - Start Temperature Measurement */
#define TMPSNS_CTRL1_TOG_START(x)                (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_START_SHIFT)) & TMPSNS_CTRL1_TOG_START_MASK)

#define TMPSNS_CTRL1_TOG_PWD_MASK                (0x800000U)
#define TMPSNS_CTRL1_TOG_PWD_SHIFT               (23U)
/*! PWD - Temperature Sensor Power Down */
#define TMPSNS_CTRL1_TOG_PWD(x)                  (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_PWD_SHIFT)) & TMPSNS_CTRL1_TOG_PWD_MASK)

#define TMPSNS_CTRL1_TOG_RFU_MASK                (0x7F000000U)
#define TMPSNS_CTRL1_TOG_RFU_SHIFT               (24U)
/*! RFU - Read/Writeable field. Reserved for future use */
#define TMPSNS_CTRL1_TOG_RFU(x)                  (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_RFU_SHIFT)) & TMPSNS_CTRL1_TOG_RFU_MASK)

#define TMPSNS_CTRL1_TOG_PWD_FULL_MASK           (0x80000000U)
#define TMPSNS_CTRL1_TOG_PWD_FULL_SHIFT          (31U)
/*! PWD_FULL - Temperature Sensor Full Power Down */
#define TMPSNS_CTRL1_TOG_PWD_FULL(x)             (((uint32_t)(((uint32_t)(x)) << TMPSNS_CTRL1_TOG_PWD_FULL_SHIFT)) & TMPSNS_CTRL1_TOG_PWD_FULL_MASK)
/*! @} */

/*! @name RANGE0 - Temperature Sensor Range Register 0 */
/*! @{ */

#define TMPSNS_RANGE0_LOW_TEMP_VAL_MASK          (0xFFFU)
#define TMPSNS_RANGE0_LOW_TEMP_VAL_SHIFT         (0U)
/*! LOW_TEMP_VAL - Low temperature threshold value */
#define TMPSNS_RANGE0_LOW_TEMP_VAL(x)            (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_LOW_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_LOW_TEMP_VAL_MASK)

#define TMPSNS_RANGE0_HIGH_TEMP_VAL_MASK         (0xFFF0000U)
#define TMPSNS_RANGE0_HIGH_TEMP_VAL_SHIFT        (16U)
/*! HIGH_TEMP_VAL - High temperature threshold value */
#define TMPSNS_RANGE0_HIGH_TEMP_VAL(x)           (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_HIGH_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_HIGH_TEMP_VAL_MASK)
/*! @} */

/*! @name RANGE0_SET - Temperature Sensor Range Register 0 */
/*! @{ */

#define TMPSNS_RANGE0_SET_LOW_TEMP_VAL_MASK      (0xFFFU)
#define TMPSNS_RANGE0_SET_LOW_TEMP_VAL_SHIFT     (0U)
/*! LOW_TEMP_VAL - Low temperature threshold value */
#define TMPSNS_RANGE0_SET_LOW_TEMP_VAL(x)        (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_SET_LOW_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_SET_LOW_TEMP_VAL_MASK)

#define TMPSNS_RANGE0_SET_HIGH_TEMP_VAL_MASK     (0xFFF0000U)
#define TMPSNS_RANGE0_SET_HIGH_TEMP_VAL_SHIFT    (16U)
/*! HIGH_TEMP_VAL - High temperature threshold value */
#define TMPSNS_RANGE0_SET_HIGH_TEMP_VAL(x)       (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_SET_HIGH_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_SET_HIGH_TEMP_VAL_MASK)
/*! @} */

/*! @name RANGE0_CLR - Temperature Sensor Range Register 0 */
/*! @{ */

#define TMPSNS_RANGE0_CLR_LOW_TEMP_VAL_MASK      (0xFFFU)
#define TMPSNS_RANGE0_CLR_LOW_TEMP_VAL_SHIFT     (0U)
/*! LOW_TEMP_VAL - Low temperature threshold value */
#define TMPSNS_RANGE0_CLR_LOW_TEMP_VAL(x)        (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_CLR_LOW_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_CLR_LOW_TEMP_VAL_MASK)

#define TMPSNS_RANGE0_CLR_HIGH_TEMP_VAL_MASK     (0xFFF0000U)
#define TMPSNS_RANGE0_CLR_HIGH_TEMP_VAL_SHIFT    (16U)
/*! HIGH_TEMP_VAL - High temperature threshold value */
#define TMPSNS_RANGE0_CLR_HIGH_TEMP_VAL(x)       (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_CLR_HIGH_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_CLR_HIGH_TEMP_VAL_MASK)
/*! @} */

/*! @name RANGE0_TOG - Temperature Sensor Range Register 0 */
/*! @{ */

#define TMPSNS_RANGE0_TOG_LOW_TEMP_VAL_MASK      (0xFFFU)
#define TMPSNS_RANGE0_TOG_LOW_TEMP_VAL_SHIFT     (0U)
/*! LOW_TEMP_VAL - Low temperature threshold value */
#define TMPSNS_RANGE0_TOG_LOW_TEMP_VAL(x)        (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_TOG_LOW_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_TOG_LOW_TEMP_VAL_MASK)

#define TMPSNS_RANGE0_TOG_HIGH_TEMP_VAL_MASK     (0xFFF0000U)
#define TMPSNS_RANGE0_TOG_HIGH_TEMP_VAL_SHIFT    (16U)
/*! HIGH_TEMP_VAL - High temperature threshold value */
#define TMPSNS_RANGE0_TOG_HIGH_TEMP_VAL(x)       (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE0_TOG_HIGH_TEMP_VAL_SHIFT)) & TMPSNS_RANGE0_TOG_HIGH_TEMP_VAL_MASK)
/*! @} */

/*! @name RANGE1 - Temperature Sensor Range Register 1 */
/*! @{ */

#define TMPSNS_RANGE1_PANIC_TEMP_VAL_MASK        (0xFFFU)
#define TMPSNS_RANGE1_PANIC_TEMP_VAL_SHIFT       (0U)
/*! PANIC_TEMP_VAL - Panic temperature threshold value */
#define TMPSNS_RANGE1_PANIC_TEMP_VAL(x)          (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE1_PANIC_TEMP_VAL_SHIFT)) & TMPSNS_RANGE1_PANIC_TEMP_VAL_MASK)
/*! @} */

/*! @name RANGE1_SET - Temperature Sensor Range Register 1 */
/*! @{ */

#define TMPSNS_RANGE1_SET_PANIC_TEMP_VAL_MASK    (0xFFFU)
#define TMPSNS_RANGE1_SET_PANIC_TEMP_VAL_SHIFT   (0U)
/*! PANIC_TEMP_VAL - Panic temperature threshold value */
#define TMPSNS_RANGE1_SET_PANIC_TEMP_VAL(x)      (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE1_SET_PANIC_TEMP_VAL_SHIFT)) & TMPSNS_RANGE1_SET_PANIC_TEMP_VAL_MASK)
/*! @} */

/*! @name RANGE1_CLR - Temperature Sensor Range Register 1 */
/*! @{ */

#define TMPSNS_RANGE1_CLR_PANIC_TEMP_VAL_MASK    (0xFFFU)
#define TMPSNS_RANGE1_CLR_PANIC_TEMP_VAL_SHIFT   (0U)
/*! PANIC_TEMP_VAL - Panic temperature threshold value */
#define TMPSNS_RANGE1_CLR_PANIC_TEMP_VAL(x)      (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE1_CLR_PANIC_TEMP_VAL_SHIFT)) & TMPSNS_RANGE1_CLR_PANIC_TEMP_VAL_MASK)
/*! @} */

/*! @name RANGE1_TOG - Temperature Sensor Range Register 1 */
/*! @{ */

#define TMPSNS_RANGE1_TOG_PANIC_TEMP_VAL_MASK    (0xFFFU)
#define TMPSNS_RANGE1_TOG_PANIC_TEMP_VAL_SHIFT   (0U)
/*! PANIC_TEMP_VAL - Panic temperature threshold value */
#define TMPSNS_RANGE1_TOG_PANIC_TEMP_VAL(x)      (((uint32_t)(((uint32_t)(x)) << TMPSNS_RANGE1_TOG_PANIC_TEMP_VAL_SHIFT)) & TMPSNS_RANGE1_TOG_PANIC_TEMP_VAL_MASK)
/*! @} */

/*! @name STATUS0 - Temperature Sensor Status Register 0 */
/*! @{ */

#define TMPSNS_STATUS0_TEMP_VAL_MASK             (0xFFFU)
#define TMPSNS_STATUS0_TEMP_VAL_SHIFT            (0U)
/*! TEMP_VAL - Measured temperature value */
#define TMPSNS_STATUS0_TEMP_VAL(x)               (((uint32_t)(((uint32_t)(x)) << TMPSNS_STATUS0_TEMP_VAL_SHIFT)) & TMPSNS_STATUS0_TEMP_VAL_MASK)

#define TMPSNS_STATUS0_FINISH_MASK               (0x10000U)
#define TMPSNS_STATUS0_FINISH_SHIFT              (16U)
/*! FINISH - Temperature measurement complete
 *  0b0..Temperature sensor is busy (if CTRL1[START] = 1)or no new reading has been initiated (if CTRL1[START] = 0)
 *  0b1..Temperature reading is complete and new temperature value available for reading
 */
#define TMPSNS_STATUS0_FINISH(x)                 (((uint32_t)(((uint32_t)(x)) << TMPSNS_STATUS0_FINISH_SHIFT)) & TMPSNS_STATUS0_FINISH_MASK)

#define TMPSNS_STATUS0_LOW_TEMP_MASK             (0x20000U)
#define TMPSNS_STATUS0_LOW_TEMP_SHIFT            (17U)
/*! LOW_TEMP - Low temperature alarm bit
 *  0b0..No Low temperature alert
 *  0b1..Low temperature alert
 */
#define TMPSNS_STATUS0_LOW_TEMP(x)               (((uint32_t)(((uint32_t)(x)) << TMPSNS_STATUS0_LOW_TEMP_SHIFT)) & TMPSNS_STATUS0_LOW_TEMP_MASK)

#define TMPSNS_STATUS0_HIGH_TEMP_MASK            (0x40000U)
#define TMPSNS_STATUS0_HIGH_TEMP_SHIFT           (18U)
/*! HIGH_TEMP - High temperature alarm bit
 *  0b0..No High temperature alert
 *  0b1..High temperature alert
 */
#define TMPSNS_STATUS0_HIGH_TEMP(x)              (((uint32_t)(((uint32_t)(x)) << TMPSNS_STATUS0_HIGH_TEMP_SHIFT)) & TMPSNS_STATUS0_HIGH_TEMP_MASK)

#define TMPSNS_STATUS0_PANIC_TEMP_MASK           (0x80000U)
#define TMPSNS_STATUS0_PANIC_TEMP_SHIFT          (19U)
/*! PANIC_TEMP - Panic temperature alarm bit
 *  0b0..No Panic temperature alert
 *  0b1..Panic temperature alert
 */
#define TMPSNS_STATUS0_PANIC_TEMP(x)             (((uint32_t)(((uint32_t)(x)) << TMPSNS_STATUS0_PANIC_TEMP_SHIFT)) & TMPSNS_STATUS0_PANIC_TEMP_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group TMPSNS_Register_Masks */


/*!
 * @}
 */ /* end of group TMPSNS_Peripheral_Access_Layer */


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


#endif  /* PERI_TMPSNS_H_ */

