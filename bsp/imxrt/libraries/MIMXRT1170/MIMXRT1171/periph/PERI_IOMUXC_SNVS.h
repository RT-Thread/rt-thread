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
**         CMSIS Peripheral Access Layer for IOMUXC_SNVS
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
 * @file PERI_IOMUXC_SNVS.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IOMUXC_SNVS
 *
 * CMSIS Peripheral Access Layer for IOMUXC_SNVS
 */

#if !defined(PERI_IOMUXC_SNVS_H_)
#define PERI_IOMUXC_SNVS_H_                      /**< Symbol preventing repeated inclusion */

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
   -- IOMUXC_SNVS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_SNVS_Peripheral_Access_Layer IOMUXC_SNVS Peripheral Access Layer
 * @{
 */

/** IOMUXC_SNVS - Register Layout Typedef */
typedef struct {
  __IO uint32_t SW_MUX_CTL_PAD_WAKEUP_DIG;         /**< SW_MUX_CTL_PAD_WAKEUP_DIG SW MUX Control Register, offset: 0x0 */
  __IO uint32_t SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG;    /**< SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG SW MUX Control Register, offset: 0x4 */
  __IO uint32_t SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG;  /**< SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG SW MUX Control Register, offset: 0x8 */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG SW MUX Control Register, offset: 0xC */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG SW MUX Control Register, offset: 0x10 */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG SW MUX Control Register, offset: 0x14 */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG SW MUX Control Register, offset: 0x18 */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG SW MUX Control Register, offset: 0x1C */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG SW MUX Control Register, offset: 0x20 */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG SW MUX Control Register, offset: 0x24 */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG SW MUX Control Register, offset: 0x28 */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG SW MUX Control Register, offset: 0x2C */
  __IO uint32_t SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG;   /**< SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG SW MUX Control Register, offset: 0x30 */
  __IO uint32_t SW_PAD_CTL_PAD_TEST_MODE_DIG;      /**< SW_PAD_CTL_PAD_TEST_MODE_DIG SW PAD Control Register, offset: 0x34 */
  __IO uint32_t SW_PAD_CTL_PAD_POR_B_DIG;          /**< SW_PAD_CTL_PAD_POR_B_DIG SW PAD Control Register, offset: 0x38 */
  __IO uint32_t SW_PAD_CTL_PAD_ONOFF_DIG;          /**< SW_PAD_CTL_PAD_ONOFF_DIG SW PAD Control Register, offset: 0x3C */
  __IO uint32_t SW_PAD_CTL_PAD_WAKEUP_DIG;         /**< SW_PAD_CTL_PAD_WAKEUP_DIG SW PAD Control Register, offset: 0x40 */
  __IO uint32_t SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG;    /**< SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG SW PAD Control Register, offset: 0x44 */
  __IO uint32_t SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG;  /**< SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG SW PAD Control Register, offset: 0x48 */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG SW PAD Control Register, offset: 0x4C */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG SW PAD Control Register, offset: 0x50 */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG SW PAD Control Register, offset: 0x54 */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG SW PAD Control Register, offset: 0x58 */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG SW PAD Control Register, offset: 0x5C */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG SW PAD Control Register, offset: 0x60 */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG SW PAD Control Register, offset: 0x64 */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG SW PAD Control Register, offset: 0x68 */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG SW PAD Control Register, offset: 0x6C */
  __IO uint32_t SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG;   /**< SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG SW PAD Control Register, offset: 0x70 */
} IOMUXC_SNVS_Type;

/* ----------------------------------------------------------------------------
   -- IOMUXC_SNVS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOMUXC_SNVS_Register_Masks IOMUXC_SNVS Register Masks
 * @{
 */

/*! @name SW_MUX_CTL_PAD_WAKEUP_DIG - SW_MUX_CTL_PAD_WAKEUP_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO00 of instance: GPIO13
 *  0b111..Select mux mode: ALT7 mux port: NMI_GLUE_NMI of instance: NMI_GLUE
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad WAKEUP_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG - SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_LP_PMIC_ON_REQ of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO01 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad PMIC_ON_REQ_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG - SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: CCM_PMIC_VSTBY_REQ of instance: CCM
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO02 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad PMIC_STBY_REQ_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER0 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO03 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_00_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_00_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER1 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO04 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_01_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_01_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER2 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO05 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_02_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_02_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER3 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO06 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_03_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_03_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER4 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO07 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_04_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_04_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER5 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO08 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_05_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_05_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER6 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO09 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_06_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_06_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER7 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO10 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_07_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_07_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER8 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO11 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_08_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_08_DIG_SION_MASK)
/*! @} */

/*! @name SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG - SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG SW MUX Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_MUX_MODE_MASK (0x7U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_MUX_MODE_SHIFT (0U)
/*! MUX_MODE - MUX Mode Select Field.
 *  0b000..Select mux mode: ALT0 mux port: SNVS_TAMPER9 of instance: SNVS_LP
 *  0b101..Select mux mode: ALT5 mux port: GPIO13_IO12 of instance: GPIO13
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_MUX_MODE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_MUX_MODE_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_MUX_MODE_MASK)

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_SION_MASK (0x10U)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_SION_SHIFT (4U)
/*! SION - Software Input On Field.
 *  0b0..Input Path is determined by functionality
 *  0b1..Force input path of pad GPIO_SNVS_09_DIG
 */
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_SION(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_SION_SHIFT)) & IOMUXC_SNVS_SW_MUX_CTL_PAD_GPIO_SNVS_09_DIG_SION_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_TEST_MODE_DIG - SW_PAD_CTL_PAD_TEST_MODE_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_POR_B_DIG - SW_PAD_CTL_PAD_POR_B_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_ONOFF_DIG - SW_PAD_CTL_PAD_ONOFF_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_WAKEUP_DIG - SW_PAD_CTL_PAD_WAKEUP_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG - SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG - SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_00_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_01_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_02_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_03_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_04_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_05_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_06_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_07_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_08_DIG_DWP_LOCK_MASK)
/*! @} */

/*! @name SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG - SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG SW PAD Control Register */
/*! @{ */

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUE_MASK (0x4U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUE_SHIFT (2U)
/*! PUE - Pull / Keep Select Field
 *  0b0..Pull Disable
 *  0b1..Pull Enable
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUE(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUE_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUE_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUS_MASK (0x8U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUS_SHIFT (3U)
/*! PUS - Pull Up / Down Config. Field
 *  0b0..Weak pull down
 *  0b1..Weak pull up
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_PUS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_ODE_SNVS_MASK (0x40U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_ODE_SNVS_SHIFT (6U)
/*! ODE_SNVS - Open Drain SNVS Field
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_ODE_SNVS(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_ODE_SNVS_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_ODE_SNVS_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_MASK (0x30000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_SHIFT (28U)
/*! DWP - Domain write protection
 *  0b00..Both cores are allowed
 *  0b01..CM7 is forbidden
 *  0b10..CM4 is forbidden
 *  0b11..Both cores are forbidden
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_MASK)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_LOCK_MASK (0xC0000000U)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_LOCK_SHIFT (30U)
/*! DWP_LOCK - Domain write protection lock
 *  0b00..Neither of DWP bits is locked
 *  0b01..The lower DWP bit is locked
 *  0b10..The higher DWP bit is locked
 *  0b11..Both DWP bits are locked
 */
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_LOCK(x) (((uint32_t)(((uint32_t)(x)) << IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_LOCK_SHIFT)) & IOMUXC_SNVS_SW_PAD_CTL_PAD_GPIO_SNVS_09_DIG_DWP_LOCK_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group IOMUXC_SNVS_Register_Masks */


/*!
 * @}
 */ /* end of group IOMUXC_SNVS_Peripheral_Access_Layer */


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


#endif  /* PERI_IOMUXC_SNVS_H_ */

