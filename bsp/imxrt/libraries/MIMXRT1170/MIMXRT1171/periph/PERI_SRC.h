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
**         CMSIS Peripheral Access Layer for SRC
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
 * @file PERI_SRC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for SRC
 *
 * CMSIS Peripheral Access Layer for SRC
 */

#if !defined(PERI_SRC_H_)
#define PERI_SRC_H_                              /**< Symbol preventing repeated inclusion */

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
   -- SRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SRC_Peripheral_Access_Layer SRC Peripheral Access Layer
 * @{
 */

/** SRC - Size of Registers Arrays */
#define SRC_GPR_COUNT                             20u

/** SRC - Register Layout Typedef */
typedef struct {
  __IO uint32_t SCR;                               /**< SRC Control Register, offset: 0x0 */
  __IO uint32_t SRMR;                              /**< SRC Reset Mode Register, offset: 0x4 */
  __I  uint32_t SBMR1;                             /**< SRC Boot Mode Register 1, offset: 0x8 */
  __I  uint32_t SBMR2;                             /**< SRC Boot Mode Register 2, offset: 0xC */
  __IO uint32_t SRSR;                              /**< SRC Reset Status Register, offset: 0x10 */
  __IO uint32_t GPR[SRC_GPR_COUNT];                /**< SRC General Purpose Register, array offset: 0x14, array step: 0x4 */
       uint8_t RESERVED_0[412];
  __IO uint32_t AUTHEN_MEGA;                       /**< Slice Authentication Register, offset: 0x200 */
  __IO uint32_t CTRL_MEGA;                         /**< Slice Control Register, offset: 0x204 */
  __IO uint32_t SETPOINT_MEGA;                     /**< Slice Setpoint Config Register, offset: 0x208 */
  __IO uint32_t DOMAIN_MEGA;                       /**< Slice Domain Config Register, offset: 0x20C */
  __IO uint32_t STAT_MEGA;                         /**< Slice Status Register, offset: 0x210 */
       uint8_t RESERVED_1[12];
  __IO uint32_t AUTHEN_DISPLAY;                    /**< Slice Authentication Register, offset: 0x220 */
  __IO uint32_t CTRL_DISPLAY;                      /**< Slice Control Register, offset: 0x224 */
  __IO uint32_t SETPOINT_DISPLAY;                  /**< Slice Setpoint Config Register, offset: 0x228 */
  __IO uint32_t DOMAIN_DISPLAY;                    /**< Slice Domain Config Register, offset: 0x22C */
  __IO uint32_t STAT_DISPLAY;                      /**< Slice Status Register, offset: 0x230 */
       uint8_t RESERVED_2[12];
  __IO uint32_t AUTHEN_WAKEUP;                     /**< Slice Authentication Register, offset: 0x240 */
  __IO uint32_t CTRL_WAKEUP;                       /**< Slice Control Register, offset: 0x244 */
  __IO uint32_t SETPOINT_WAKEUP;                   /**< Slice Setpoint Config Register, offset: 0x248 */
  __IO uint32_t DOMAIN_WAKEUP;                     /**< Slice Domain Config Register, offset: 0x24C */
  __IO uint32_t STAT_WAKEUP;                       /**< Slice Status Register, offset: 0x250 */
       uint8_t RESERVED_3[44];
  __IO uint32_t AUTHEN_M4CORE;                     /**< Slice Authentication Register, offset: 0x280 */
  __IO uint32_t CTRL_M4CORE;                       /**< Slice Control Register, offset: 0x284 */
  __IO uint32_t SETPOINT_M4CORE;                   /**< Slice Setpoint Config Register, offset: 0x288 */
  __IO uint32_t DOMAIN_M4CORE;                     /**< Slice Domain Config Register, offset: 0x28C */
  __IO uint32_t STAT_M4CORE;                       /**< Slice Status Register, offset: 0x290 */
       uint8_t RESERVED_4[12];
  __IO uint32_t AUTHEN_M7CORE;                     /**< Slice Authentication Register, offset: 0x2A0 */
  __IO uint32_t CTRL_M7CORE;                       /**< Slice Control Register, offset: 0x2A4 */
  __IO uint32_t SETPOINT_M7CORE;                   /**< Slice Setpoint Config Register, offset: 0x2A8 */
  __IO uint32_t DOMAIN_M7CORE;                     /**< Slice Domain Config Register, offset: 0x2AC */
  __IO uint32_t STAT_M7CORE;                       /**< Slice Status Register, offset: 0x2B0 */
       uint8_t RESERVED_5[12];
  __IO uint32_t AUTHEN_M4DEBUG;                    /**< Slice Authentication Register, offset: 0x2C0 */
  __IO uint32_t CTRL_M4DEBUG;                      /**< Slice Control Register, offset: 0x2C4 */
  __IO uint32_t SETPOINT_M4DEBUG;                  /**< Slice Setpoint Config Register, offset: 0x2C8 */
  __IO uint32_t DOMAIN_M4DEBUG;                    /**< Slice Domain Config Register, offset: 0x2CC */
  __IO uint32_t STAT_M4DEBUG;                      /**< Slice Status Register, offset: 0x2D0 */
       uint8_t RESERVED_6[12];
  __IO uint32_t AUTHEN_M7DEBUG;                    /**< Slice Authentication Register, offset: 0x2E0 */
  __IO uint32_t CTRL_M7DEBUG;                      /**< Slice Control Register, offset: 0x2E4 */
  __IO uint32_t SETPOINT_M7DEBUG;                  /**< Slice Setpoint Config Register, offset: 0x2E8 */
  __IO uint32_t DOMAIN_M7DEBUG;                    /**< Slice Domain Config Register, offset: 0x2EC */
  __IO uint32_t STAT_M7DEBUG;                      /**< Slice Status Register, offset: 0x2F0 */
       uint8_t RESERVED_7[12];
  __IO uint32_t AUTHEN_USBPHY1;                    /**< Slice Authentication Register, offset: 0x300 */
  __IO uint32_t CTRL_USBPHY1;                      /**< Slice Control Register, offset: 0x304 */
  __IO uint32_t SETPOINT_USBPHY1;                  /**< Slice Setpoint Config Register, offset: 0x308 */
  __IO uint32_t DOMAIN_USBPHY1;                    /**< Slice Domain Config Register, offset: 0x30C */
  __IO uint32_t STAT_USBPHY1;                      /**< Slice Status Register, offset: 0x310 */
       uint8_t RESERVED_8[12];
  __IO uint32_t AUTHEN_USBPHY2;                    /**< Slice Authentication Register, offset: 0x320 */
  __IO uint32_t CTRL_USBPHY2;                      /**< Slice Control Register, offset: 0x324 */
  __IO uint32_t SETPOINT_USBPHY2;                  /**< Slice Setpoint Config Register, offset: 0x328 */
  __IO uint32_t DOMAIN_USBPHY2;                    /**< Slice Domain Config Register, offset: 0x32C */
  __IO uint32_t STAT_USBPHY2;                      /**< Slice Status Register, offset: 0x330 */
} SRC_Type;

/* ----------------------------------------------------------------------------
   -- SRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SRC_Register_Masks SRC Register Masks
 * @{
 */

/*! @name SCR - SRC Control Register */
/*! @{ */

#define SRC_SCR_BT_RELEASE_M4_MASK               (0x1U)
#define SRC_SCR_BT_RELEASE_M4_SHIFT              (0U)
/*! BT_RELEASE_M4
 *  0b0..cm4 core reset is asserted
 *  0b1..cm4 core reset is released
 */
#define SRC_SCR_BT_RELEASE_M4(x)                 (((uint32_t)(((uint32_t)(x)) << SRC_SCR_BT_RELEASE_M4_SHIFT)) & SRC_SCR_BT_RELEASE_M4_MASK)

#define SRC_SCR_BT_RELEASE_M7_MASK               (0x2U)
#define SRC_SCR_BT_RELEASE_M7_SHIFT              (1U)
/*! BT_RELEASE_M7
 *  0b0..cm7 core reset is asserted
 *  0b1..cm7 core reset is released
 */
#define SRC_SCR_BT_RELEASE_M7(x)                 (((uint32_t)(((uint32_t)(x)) << SRC_SCR_BT_RELEASE_M7_SHIFT)) & SRC_SCR_BT_RELEASE_M7_MASK)
/*! @} */

/*! @name SRMR - SRC Reset Mode Register */
/*! @{ */

#define SRC_SRMR_WDOG_RESET_MODE_MASK            (0x3U)
#define SRC_SRMR_WDOG_RESET_MODE_SHIFT           (0U)
/*! WDOG_RESET_MODE - Wdog reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_WDOG_RESET_MODE(x)              (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_WDOG_RESET_MODE_SHIFT)) & SRC_SRMR_WDOG_RESET_MODE_MASK)

#define SRC_SRMR_WDOG3_RESET_MODE_MASK           (0xCU)
#define SRC_SRMR_WDOG3_RESET_MODE_SHIFT          (2U)
/*! WDOG3_RESET_MODE - Wdog3 reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_WDOG3_RESET_MODE(x)             (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_WDOG3_RESET_MODE_SHIFT)) & SRC_SRMR_WDOG3_RESET_MODE_MASK)

#define SRC_SRMR_WDOG4_RESET_MODE_MASK           (0x30U)
#define SRC_SRMR_WDOG4_RESET_MODE_SHIFT          (4U)
/*! WDOG4_RESET_MODE - Wdog4 reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_WDOG4_RESET_MODE(x)             (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_WDOG4_RESET_MODE_SHIFT)) & SRC_SRMR_WDOG4_RESET_MODE_MASK)

#define SRC_SRMR_M4LOCKUP_RESET_MODE_MASK        (0xC0U)
#define SRC_SRMR_M4LOCKUP_RESET_MODE_SHIFT       (6U)
/*! M4LOCKUP_RESET_MODE - M4 core lockup reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_M4LOCKUP_RESET_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_M4LOCKUP_RESET_MODE_SHIFT)) & SRC_SRMR_M4LOCKUP_RESET_MODE_MASK)

#define SRC_SRMR_M7LOCKUP_RESET_MODE_MASK        (0x300U)
#define SRC_SRMR_M7LOCKUP_RESET_MODE_SHIFT       (8U)
/*! M7LOCKUP_RESET_MODE - M7 core lockup reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_M7LOCKUP_RESET_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_M7LOCKUP_RESET_MODE_SHIFT)) & SRC_SRMR_M7LOCKUP_RESET_MODE_MASK)

#define SRC_SRMR_M4REQ_RESET_MODE_MASK           (0xC00U)
#define SRC_SRMR_M4REQ_RESET_MODE_SHIFT          (10U)
/*! M4REQ_RESET_MODE - M4 request reset configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_M4REQ_RESET_MODE(x)             (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_M4REQ_RESET_MODE_SHIFT)) & SRC_SRMR_M4REQ_RESET_MODE_MASK)

#define SRC_SRMR_M7REQ_RESET_MODE_MASK           (0x3000U)
#define SRC_SRMR_M7REQ_RESET_MODE_SHIFT          (12U)
/*! M7REQ_RESET_MODE - M7 request reset configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_M7REQ_RESET_MODE(x)             (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_M7REQ_RESET_MODE_SHIFT)) & SRC_SRMR_M7REQ_RESET_MODE_MASK)

#define SRC_SRMR_TEMPSENSE_RESET_MODE_MASK       (0xC000U)
#define SRC_SRMR_TEMPSENSE_RESET_MODE_SHIFT      (14U)
/*! TEMPSENSE_RESET_MODE - Tempsense reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_TEMPSENSE_RESET_MODE(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_TEMPSENSE_RESET_MODE_SHIFT)) & SRC_SRMR_TEMPSENSE_RESET_MODE_MASK)

#define SRC_SRMR_CSU_RESET_MODE_MASK             (0x30000U)
#define SRC_SRMR_CSU_RESET_MODE_SHIFT            (16U)
/*! CSU_RESET_MODE - CSU reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_CSU_RESET_MODE(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_CSU_RESET_MODE_SHIFT)) & SRC_SRMR_CSU_RESET_MODE_MASK)

#define SRC_SRMR_JTAGSW_RESET_MODE_MASK          (0xC0000U)
#define SRC_SRMR_JTAGSW_RESET_MODE_SHIFT         (18U)
/*! JTAGSW_RESET_MODE - Jtag SW reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_JTAGSW_RESET_MODE(x)            (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_JTAGSW_RESET_MODE_SHIFT)) & SRC_SRMR_JTAGSW_RESET_MODE_MASK)

#define SRC_SRMR_OVERVOLT_RESET_MODE_MASK        (0x300000U)
#define SRC_SRMR_OVERVOLT_RESET_MODE_SHIFT       (20U)
/*! OVERVOLT_RESET_MODE - Jtag SW reset mode configuration
 *  0b00..reset system
 *  0b01..reserved
 *  0b10..reserved
 *  0b11..do not reset anything
 */
#define SRC_SRMR_OVERVOLT_RESET_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SRMR_OVERVOLT_RESET_MODE_SHIFT)) & SRC_SRMR_OVERVOLT_RESET_MODE_MASK)
/*! @} */

/*! @name SBMR1 - SRC Boot Mode Register 1 */
/*! @{ */

#define SRC_SBMR1_BOOT_CFG1_MASK                 (0xFFU)
#define SRC_SBMR1_BOOT_CFG1_SHIFT                (0U)
#define SRC_SBMR1_BOOT_CFG1(x)                   (((uint32_t)(((uint32_t)(x)) << SRC_SBMR1_BOOT_CFG1_SHIFT)) & SRC_SBMR1_BOOT_CFG1_MASK)

#define SRC_SBMR1_BOOT_CFG2_MASK                 (0xFF00U)
#define SRC_SBMR1_BOOT_CFG2_SHIFT                (8U)
#define SRC_SBMR1_BOOT_CFG2(x)                   (((uint32_t)(((uint32_t)(x)) << SRC_SBMR1_BOOT_CFG2_SHIFT)) & SRC_SBMR1_BOOT_CFG2_MASK)

#define SRC_SBMR1_BOOT_CFG3_MASK                 (0xFF0000U)
#define SRC_SBMR1_BOOT_CFG3_SHIFT                (16U)
#define SRC_SBMR1_BOOT_CFG3(x)                   (((uint32_t)(((uint32_t)(x)) << SRC_SBMR1_BOOT_CFG3_SHIFT)) & SRC_SBMR1_BOOT_CFG3_MASK)

#define SRC_SBMR1_BOOT_CFG4_MASK                 (0xFF000000U)
#define SRC_SBMR1_BOOT_CFG4_SHIFT                (24U)
#define SRC_SBMR1_BOOT_CFG4(x)                   (((uint32_t)(((uint32_t)(x)) << SRC_SBMR1_BOOT_CFG4_SHIFT)) & SRC_SBMR1_BOOT_CFG4_MASK)
/*! @} */

/*! @name SBMR2 - SRC Boot Mode Register 2 */
/*! @{ */

#define SRC_SBMR2_SEC_CONFIG_MASK                (0x3U)
#define SRC_SBMR2_SEC_CONFIG_SHIFT               (0U)
#define SRC_SBMR2_SEC_CONFIG(x)                  (((uint32_t)(((uint32_t)(x)) << SRC_SBMR2_SEC_CONFIG_SHIFT)) & SRC_SBMR2_SEC_CONFIG_MASK)

#define SRC_SBMR2_BT_FUSE_SEL_MASK               (0x10U)
#define SRC_SBMR2_BT_FUSE_SEL_SHIFT              (4U)
#define SRC_SBMR2_BT_FUSE_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SRC_SBMR2_BT_FUSE_SEL_SHIFT)) & SRC_SBMR2_BT_FUSE_SEL_MASK)

#define SRC_SBMR2_BMOD_MASK                      (0x3000000U)
#define SRC_SBMR2_BMOD_SHIFT                     (24U)
#define SRC_SBMR2_BMOD(x)                        (((uint32_t)(((uint32_t)(x)) << SRC_SBMR2_BMOD_SHIFT)) & SRC_SBMR2_BMOD_MASK)
/*! @} */

/*! @name SRSR - SRC Reset Status Register */
/*! @{ */

#define SRC_SRSR_IPP_RESET_B_M7_MASK             (0x1U)
#define SRC_SRSR_IPP_RESET_B_M7_SHIFT            (0U)
/*! IPP_RESET_B_M7
 *  0b0..Reset is not a result of ipp_reset_b pin.
 *  0b1..Reset is a result of ipp_reset_b pin.
 */
#define SRC_SRSR_IPP_RESET_B_M7(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_IPP_RESET_B_M7_SHIFT)) & SRC_SRSR_IPP_RESET_B_M7_MASK)

#define SRC_SRSR_M7_REQUEST_M7_MASK              (0x2U)
#define SRC_SRSR_M7_REQUEST_M7_SHIFT             (1U)
/*! M7_REQUEST_M7
 *  0b0..Reset is not a result of m7 reset request.
 *  0b1..Reset is a result of m7 reset request.
 */
#define SRC_SRSR_M7_REQUEST_M7(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M7_REQUEST_M7_SHIFT)) & SRC_SRSR_M7_REQUEST_M7_MASK)

#define SRC_SRSR_M7_LOCKUP_M7_MASK               (0x4U)
#define SRC_SRSR_M7_LOCKUP_M7_SHIFT              (2U)
/*! M7_LOCKUP_M7
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_M7_LOCKUP_M7(x)                 (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M7_LOCKUP_M7_SHIFT)) & SRC_SRSR_M7_LOCKUP_M7_MASK)

#define SRC_SRSR_CSU_RESET_B_M7_MASK             (0x8U)
#define SRC_SRSR_CSU_RESET_B_M7_SHIFT            (3U)
/*! CSU_RESET_B_M7
 *  0b0..Reset is not a result of the csu_reset_b event.
 *  0b1..Reset is a result of the csu_reset_b event.
 */
#define SRC_SRSR_CSU_RESET_B_M7(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_CSU_RESET_B_M7_SHIFT)) & SRC_SRSR_CSU_RESET_B_M7_MASK)

#define SRC_SRSR_IPP_USER_RESET_B_M7_MASK        (0x10U)
#define SRC_SRSR_IPP_USER_RESET_B_M7_SHIFT       (4U)
/*! IPP_USER_RESET_B_M7
 *  0b0..Reset is not a result of the ipp_user_reset_b qualified as COLD reset event.
 *  0b1..Reset is a result of the ipp_user_reset_b qualified as COLD reset event.
 */
#define SRC_SRSR_IPP_USER_RESET_B_M7(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_IPP_USER_RESET_B_M7_SHIFT)) & SRC_SRSR_IPP_USER_RESET_B_M7_MASK)

#define SRC_SRSR_WDOG_RST_B_M7_MASK              (0x20U)
#define SRC_SRSR_WDOG_RST_B_M7_SHIFT             (5U)
/*! WDOG_RST_B_M7
 *  0b0..Reset is not a result of the watchdog time-out event.
 *  0b1..Reset is a result of the watchdog time-out event.
 */
#define SRC_SRSR_WDOG_RST_B_M7(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_WDOG_RST_B_M7_SHIFT)) & SRC_SRSR_WDOG_RST_B_M7_MASK)

#define SRC_SRSR_JTAG_RST_B_M7_MASK              (0x40U)
#define SRC_SRSR_JTAG_RST_B_M7_SHIFT             (6U)
/*! JTAG_RST_B_M7
 *  0b0..Reset is not a result of HIGH-Z reset from JTAG.
 *  0b1..Reset is a result of HIGH-Z reset from JTAG.
 */
#define SRC_SRSR_JTAG_RST_B_M7(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_JTAG_RST_B_M7_SHIFT)) & SRC_SRSR_JTAG_RST_B_M7_MASK)

#define SRC_SRSR_JTAG_SW_RST_M7_MASK             (0x80U)
#define SRC_SRSR_JTAG_SW_RST_M7_SHIFT            (7U)
/*! JTAG_SW_RST_M7
 *  0b0..Reset is not a result of software reset from JTAG.
 *  0b1..Reset is a result of software reset from JTAG.
 */
#define SRC_SRSR_JTAG_SW_RST_M7(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_JTAG_SW_RST_M7_SHIFT)) & SRC_SRSR_JTAG_SW_RST_M7_MASK)

#define SRC_SRSR_WDOG3_RST_B_M7_MASK             (0x100U)
#define SRC_SRSR_WDOG3_RST_B_M7_SHIFT            (8U)
/*! WDOG3_RST_B_M7
 *  0b0..Reset is not a result of the watchdog3 time-out event.
 *  0b1..Reset is a result of the watchdog3 time-out event.
 */
#define SRC_SRSR_WDOG3_RST_B_M7(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_WDOG3_RST_B_M7_SHIFT)) & SRC_SRSR_WDOG3_RST_B_M7_MASK)

#define SRC_SRSR_WDOG4_RST_B_M7_MASK             (0x200U)
#define SRC_SRSR_WDOG4_RST_B_M7_SHIFT            (9U)
/*! WDOG4_RST_B_M7
 *  0b0..Reset is not a result of the watchdog4 time-out event.
 *  0b1..Reset is a result of the watchdog4 time-out event.
 */
#define SRC_SRSR_WDOG4_RST_B_M7(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_WDOG4_RST_B_M7_SHIFT)) & SRC_SRSR_WDOG4_RST_B_M7_MASK)

#define SRC_SRSR_TEMPSENSE_RST_B_M7_MASK         (0x400U)
#define SRC_SRSR_TEMPSENSE_RST_B_M7_SHIFT        (10U)
/*! TEMPSENSE_RST_B_M7
 *  0b0..Reset is not a result of software reset from Temperature Sensor.
 *  0b1..Reset is a result of software reset from Temperature Sensor.
 */
#define SRC_SRSR_TEMPSENSE_RST_B_M7(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_TEMPSENSE_RST_B_M7_SHIFT)) & SRC_SRSR_TEMPSENSE_RST_B_M7_MASK)

#define SRC_SRSR_M4_REQUEST_M7_MASK              (0x800U)
#define SRC_SRSR_M4_REQUEST_M7_SHIFT             (11U)
/*! M4_REQUEST_M7
 *  0b0..Reset is not a result of m4 reset request.
 *  0b1..Reset is a result of m4 reset request.
 */
#define SRC_SRSR_M4_REQUEST_M7(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M4_REQUEST_M7_SHIFT)) & SRC_SRSR_M4_REQUEST_M7_MASK)

#define SRC_SRSR_M4_LOCKUP_M7_MASK               (0x1000U)
#define SRC_SRSR_M4_LOCKUP_M7_SHIFT              (12U)
/*! M4_LOCKUP_M7
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_M4_LOCKUP_M7(x)                 (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M4_LOCKUP_M7_SHIFT)) & SRC_SRSR_M4_LOCKUP_M7_MASK)

#define SRC_SRSR_OVERVOLT_RST_M7_MASK            (0x2000U)
#define SRC_SRSR_OVERVOLT_RST_M7_SHIFT           (13U)
/*! OVERVOLT_RST_M7
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_OVERVOLT_RST_M7(x)              (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_OVERVOLT_RST_M7_SHIFT)) & SRC_SRSR_OVERVOLT_RST_M7_MASK)

#define SRC_SRSR_CDOG_RST_M7_MASK                (0x4000U)
#define SRC_SRSR_CDOG_RST_M7_SHIFT               (14U)
/*! CDOG_RST_M7
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_CDOG_RST_M7(x)                  (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_CDOG_RST_M7_SHIFT)) & SRC_SRSR_CDOG_RST_M7_MASK)

#define SRC_SRSR_IPP_RESET_B_M4_MASK             (0x10000U)
#define SRC_SRSR_IPP_RESET_B_M4_SHIFT            (16U)
/*! IPP_RESET_B_M4
 *  0b0..Reset is not a result of ipp_reset_b pin.
 *  0b1..Reset is a result of ipp_reset_b pin.
 */
#define SRC_SRSR_IPP_RESET_B_M4(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_IPP_RESET_B_M4_SHIFT)) & SRC_SRSR_IPP_RESET_B_M4_MASK)

#define SRC_SRSR_M4_REQUEST_M4_MASK              (0x20000U)
#define SRC_SRSR_M4_REQUEST_M4_SHIFT             (17U)
/*! M4_REQUEST_M4
 *  0b0..Reset is not a result of m4 reset request.
 *  0b1..Reset is a result of m4 reset request.
 */
#define SRC_SRSR_M4_REQUEST_M4(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M4_REQUEST_M4_SHIFT)) & SRC_SRSR_M4_REQUEST_M4_MASK)

#define SRC_SRSR_M4_LOCKUP_M4_MASK               (0x40000U)
#define SRC_SRSR_M4_LOCKUP_M4_SHIFT              (18U)
/*! M4_LOCKUP_M4
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_M4_LOCKUP_M4(x)                 (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M4_LOCKUP_M4_SHIFT)) & SRC_SRSR_M4_LOCKUP_M4_MASK)

#define SRC_SRSR_CSU_RESET_B_M4_MASK             (0x80000U)
#define SRC_SRSR_CSU_RESET_B_M4_SHIFT            (19U)
/*! CSU_RESET_B_M4
 *  0b0..Reset is not a result of the csu_reset_b event.
 *  0b1..Reset is a result of the csu_reset_b event.
 */
#define SRC_SRSR_CSU_RESET_B_M4(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_CSU_RESET_B_M4_SHIFT)) & SRC_SRSR_CSU_RESET_B_M4_MASK)

#define SRC_SRSR_IPP_USER_RESET_B_M4_MASK        (0x100000U)
#define SRC_SRSR_IPP_USER_RESET_B_M4_SHIFT       (20U)
/*! IPP_USER_RESET_B_M4
 *  0b0..Reset is not a result of the ipp_user_reset_b qualified as COLD reset event.
 *  0b1..Reset is a result of the ipp_user_reset_b qualified as COLD reset event.
 */
#define SRC_SRSR_IPP_USER_RESET_B_M4(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_IPP_USER_RESET_B_M4_SHIFT)) & SRC_SRSR_IPP_USER_RESET_B_M4_MASK)

#define SRC_SRSR_WDOG_RST_B_M4_MASK              (0x200000U)
#define SRC_SRSR_WDOG_RST_B_M4_SHIFT             (21U)
/*! WDOG_RST_B_M4
 *  0b0..Reset is not a result of the watchdog time-out event.
 *  0b1..Reset is a result of the watchdog time-out event.
 */
#define SRC_SRSR_WDOG_RST_B_M4(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_WDOG_RST_B_M4_SHIFT)) & SRC_SRSR_WDOG_RST_B_M4_MASK)

#define SRC_SRSR_JTAG_RST_B_M4_MASK              (0x400000U)
#define SRC_SRSR_JTAG_RST_B_M4_SHIFT             (22U)
/*! JTAG_RST_B_M4
 *  0b0..Reset is not a result of HIGH-Z reset from JTAG.
 *  0b1..Reset is a result of HIGH-Z reset from JTAG.
 */
#define SRC_SRSR_JTAG_RST_B_M4(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_JTAG_RST_B_M4_SHIFT)) & SRC_SRSR_JTAG_RST_B_M4_MASK)

#define SRC_SRSR_JTAG_SW_RST_M4_MASK             (0x800000U)
#define SRC_SRSR_JTAG_SW_RST_M4_SHIFT            (23U)
/*! JTAG_SW_RST_M4
 *  0b0..Reset is not a result of software reset from JTAG.
 *  0b1..Reset is a result of software reset from JTAG.
 */
#define SRC_SRSR_JTAG_SW_RST_M4(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_JTAG_SW_RST_M4_SHIFT)) & SRC_SRSR_JTAG_SW_RST_M4_MASK)

#define SRC_SRSR_WDOG3_RST_B_M4_MASK             (0x1000000U)
#define SRC_SRSR_WDOG3_RST_B_M4_SHIFT            (24U)
/*! WDOG3_RST_B_M4
 *  0b0..Reset is not a result of the watchdog3 time-out event.
 *  0b1..Reset is a result of the watchdog3 time-out event.
 */
#define SRC_SRSR_WDOG3_RST_B_M4(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_WDOG3_RST_B_M4_SHIFT)) & SRC_SRSR_WDOG3_RST_B_M4_MASK)

#define SRC_SRSR_WDOG4_RST_B_M4_MASK             (0x2000000U)
#define SRC_SRSR_WDOG4_RST_B_M4_SHIFT            (25U)
/*! WDOG4_RST_B_M4
 *  0b0..Reset is not a result of the watchdog4 time-out event.
 *  0b1..Reset is a result of the watchdog4 time-out event.
 */
#define SRC_SRSR_WDOG4_RST_B_M4(x)               (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_WDOG4_RST_B_M4_SHIFT)) & SRC_SRSR_WDOG4_RST_B_M4_MASK)

#define SRC_SRSR_TEMPSENSE_RST_B_M4_MASK         (0x4000000U)
#define SRC_SRSR_TEMPSENSE_RST_B_M4_SHIFT        (26U)
/*! TEMPSENSE_RST_B_M4
 *  0b0..Reset is not a result of software reset from Temperature Sensor.
 *  0b1..Reset is a result of software reset from Temperature Sensor.
 */
#define SRC_SRSR_TEMPSENSE_RST_B_M4(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_TEMPSENSE_RST_B_M4_SHIFT)) & SRC_SRSR_TEMPSENSE_RST_B_M4_MASK)

#define SRC_SRSR_M7_REQUEST_M4_MASK              (0x8000000U)
#define SRC_SRSR_M7_REQUEST_M4_SHIFT             (27U)
/*! M7_REQUEST_M4
 *  0b0..Reset is not a result of m7 reset request.
 *  0b1..Reset is a result of m7 reset request.
 */
#define SRC_SRSR_M7_REQUEST_M4(x)                (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M7_REQUEST_M4_SHIFT)) & SRC_SRSR_M7_REQUEST_M4_MASK)

#define SRC_SRSR_M7_LOCKUP_M4_MASK               (0x10000000U)
#define SRC_SRSR_M7_LOCKUP_M4_SHIFT              (28U)
/*! M7_LOCKUP_M4
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_M7_LOCKUP_M4(x)                 (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_M7_LOCKUP_M4_SHIFT)) & SRC_SRSR_M7_LOCKUP_M4_MASK)

#define SRC_SRSR_OVERVOLT_RST_M4_MASK            (0x20000000U)
#define SRC_SRSR_OVERVOLT_RST_M4_SHIFT           (29U)
/*! OVERVOLT_RST_M4
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_OVERVOLT_RST_M4(x)              (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_OVERVOLT_RST_M4_SHIFT)) & SRC_SRSR_OVERVOLT_RST_M4_MASK)

#define SRC_SRSR_CDOG_RST_M4_MASK                (0x40000000U)
#define SRC_SRSR_CDOG_RST_M4_SHIFT               (30U)
/*! CDOG_RST_M4
 *  0b0..Reset is not a result of the mentioned case.
 *  0b1..Reset is a result of the mentioned case.
 */
#define SRC_SRSR_CDOG_RST_M4(x)                  (((uint32_t)(((uint32_t)(x)) << SRC_SRSR_CDOG_RST_M4_SHIFT)) & SRC_SRSR_CDOG_RST_M4_MASK)
/*! @} */

/*! @name GPR - SRC General Purpose Register */
/*! @{ */

#define SRC_GPR_GPR_MASK                         (0xFFFFFFFFU)
#define SRC_GPR_GPR_SHIFT                        (0U)
/*! GPR - General Purpose Register. */
#define SRC_GPR_GPR(x)                           (((uint32_t)(((uint32_t)(x)) << SRC_GPR_GPR_SHIFT)) & SRC_GPR_GPR_MASK)
/*! @} */

/*! @name AUTHEN_MEGA - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_MEGA_DOMAIN_MODE_MASK         (0x1U)
#define SRC_AUTHEN_MEGA_DOMAIN_MODE_SHIFT        (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_MEGA_DOMAIN_MODE(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_MEGA_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_MEGA_SETPOINT_MODE_MASK       (0x2U)
#define SRC_AUTHEN_MEGA_SETPOINT_MODE_SHIFT      (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_MEGA_SETPOINT_MODE(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_MEGA_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_MEGA_LOCK_MODE_MASK           (0x80U)
#define SRC_AUTHEN_MEGA_LOCK_MODE_SHIFT          (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_MEGA_LOCK_MODE(x)             (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_LOCK_MODE_SHIFT)) & SRC_AUTHEN_MEGA_LOCK_MODE_MASK)

#define SRC_AUTHEN_MEGA_ASSIGN_LIST_MASK         (0xF00U)
#define SRC_AUTHEN_MEGA_ASSIGN_LIST_SHIFT        (8U)
#define SRC_AUTHEN_MEGA_ASSIGN_LIST(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_MEGA_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_MEGA_LOCK_ASSIGN_MASK         (0x8000U)
#define SRC_AUTHEN_MEGA_LOCK_ASSIGN_SHIFT        (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_MEGA_LOCK_ASSIGN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_MEGA_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_MEGA_WHITE_LIST_MASK          (0xF0000U)
#define SRC_AUTHEN_MEGA_WHITE_LIST_SHIFT         (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_MEGA_WHITE_LIST(x)            (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_WHITE_LIST_SHIFT)) & SRC_AUTHEN_MEGA_WHITE_LIST_MASK)

#define SRC_AUTHEN_MEGA_LOCK_LIST_MASK           (0x800000U)
#define SRC_AUTHEN_MEGA_LOCK_LIST_SHIFT          (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_MEGA_LOCK_LIST(x)             (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_LOCK_LIST_SHIFT)) & SRC_AUTHEN_MEGA_LOCK_LIST_MASK)

#define SRC_AUTHEN_MEGA_USER_MASK                (0x1000000U)
#define SRC_AUTHEN_MEGA_USER_SHIFT               (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_MEGA_USER(x)                  (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_USER_SHIFT)) & SRC_AUTHEN_MEGA_USER_MASK)

#define SRC_AUTHEN_MEGA_NONSECURE_MASK           (0x2000000U)
#define SRC_AUTHEN_MEGA_NONSECURE_SHIFT          (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_MEGA_NONSECURE(x)             (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_NONSECURE_SHIFT)) & SRC_AUTHEN_MEGA_NONSECURE_MASK)

#define SRC_AUTHEN_MEGA_LOCK_SETTING_MASK        (0x80000000U)
#define SRC_AUTHEN_MEGA_LOCK_SETTING_SHIFT       (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_MEGA_LOCK_SETTING(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_MEGA_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_MEGA_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_MEGA - Slice Control Register */
/*! @{ */

#define SRC_CTRL_MEGA_SW_RESET_MASK              (0x1U)
#define SRC_CTRL_MEGA_SW_RESET_SHIFT             (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_MEGA_SW_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_MEGA_SW_RESET_SHIFT)) & SRC_CTRL_MEGA_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_MEGA - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_MEGA_SETPOINT0_MASK         (0x1U)
#define SRC_SETPOINT_MEGA_SETPOINT0_SHIFT        (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT0(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT0_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT0_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT1_MASK         (0x2U)
#define SRC_SETPOINT_MEGA_SETPOINT1_SHIFT        (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT1(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT1_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT1_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT2_MASK         (0x4U)
#define SRC_SETPOINT_MEGA_SETPOINT2_SHIFT        (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT2(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT2_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT2_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT3_MASK         (0x8U)
#define SRC_SETPOINT_MEGA_SETPOINT3_SHIFT        (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT3(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT3_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT3_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT4_MASK         (0x10U)
#define SRC_SETPOINT_MEGA_SETPOINT4_SHIFT        (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT4(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT4_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT4_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT5_MASK         (0x20U)
#define SRC_SETPOINT_MEGA_SETPOINT5_SHIFT        (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT5(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT5_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT5_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT6_MASK         (0x40U)
#define SRC_SETPOINT_MEGA_SETPOINT6_SHIFT        (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT6(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT6_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT6_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT7_MASK         (0x80U)
#define SRC_SETPOINT_MEGA_SETPOINT7_SHIFT        (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT7(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT7_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT7_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT8_MASK         (0x100U)
#define SRC_SETPOINT_MEGA_SETPOINT8_SHIFT        (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT8(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT8_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT8_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT9_MASK         (0x200U)
#define SRC_SETPOINT_MEGA_SETPOINT9_SHIFT        (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT9(x)           (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT9_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT9_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT10_MASK        (0x400U)
#define SRC_SETPOINT_MEGA_SETPOINT10_SHIFT       (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT10(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT10_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT10_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT11_MASK        (0x800U)
#define SRC_SETPOINT_MEGA_SETPOINT11_SHIFT       (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT11(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT11_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT11_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT12_MASK        (0x1000U)
#define SRC_SETPOINT_MEGA_SETPOINT12_SHIFT       (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT12(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT12_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT12_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT13_MASK        (0x2000U)
#define SRC_SETPOINT_MEGA_SETPOINT13_SHIFT       (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT13(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT13_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT13_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT14_MASK        (0x4000U)
#define SRC_SETPOINT_MEGA_SETPOINT14_SHIFT       (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT14(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT14_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT14_MASK)

#define SRC_SETPOINT_MEGA_SETPOINT15_MASK        (0x8000U)
#define SRC_SETPOINT_MEGA_SETPOINT15_SHIFT       (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_MEGA_SETPOINT15(x)          (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_MEGA_SETPOINT15_SHIFT)) & SRC_SETPOINT_MEGA_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_MEGA - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_MEGA_CPU0_RUN_MASK            (0x1U)
#define SRC_DOMAIN_MEGA_CPU0_RUN_SHIFT           (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_MEGA_CPU0_RUN(x)              (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU0_RUN_SHIFT)) & SRC_DOMAIN_MEGA_CPU0_RUN_MASK)

#define SRC_DOMAIN_MEGA_CPU0_WAIT_MASK           (0x2U)
#define SRC_DOMAIN_MEGA_CPU0_WAIT_SHIFT          (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_MEGA_CPU0_WAIT(x)             (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_MEGA_CPU0_WAIT_MASK)

#define SRC_DOMAIN_MEGA_CPU0_STOP_MASK           (0x4U)
#define SRC_DOMAIN_MEGA_CPU0_STOP_SHIFT          (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_MEGA_CPU0_STOP(x)             (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU0_STOP_SHIFT)) & SRC_DOMAIN_MEGA_CPU0_STOP_MASK)

#define SRC_DOMAIN_MEGA_CPU0_SUSP_MASK           (0x8U)
#define SRC_DOMAIN_MEGA_CPU0_SUSP_SHIFT          (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_MEGA_CPU0_SUSP(x)             (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_MEGA_CPU0_SUSP_MASK)

#define SRC_DOMAIN_MEGA_CPU1_RUN_MASK            (0x10U)
#define SRC_DOMAIN_MEGA_CPU1_RUN_SHIFT           (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_MEGA_CPU1_RUN(x)              (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU1_RUN_SHIFT)) & SRC_DOMAIN_MEGA_CPU1_RUN_MASK)

#define SRC_DOMAIN_MEGA_CPU1_WAIT_MASK           (0x20U)
#define SRC_DOMAIN_MEGA_CPU1_WAIT_SHIFT          (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_MEGA_CPU1_WAIT(x)             (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_MEGA_CPU1_WAIT_MASK)

#define SRC_DOMAIN_MEGA_CPU1_STOP_MASK           (0x40U)
#define SRC_DOMAIN_MEGA_CPU1_STOP_SHIFT          (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_MEGA_CPU1_STOP(x)             (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU1_STOP_SHIFT)) & SRC_DOMAIN_MEGA_CPU1_STOP_MASK)

#define SRC_DOMAIN_MEGA_CPU1_SUSP_MASK           (0x80U)
#define SRC_DOMAIN_MEGA_CPU1_SUSP_SHIFT          (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_MEGA_CPU1_SUSP(x)             (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_MEGA_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_MEGA_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_MEGA - Slice Status Register */
/*! @{ */

#define SRC_STAT_MEGA_UNDER_RST_MASK             (0x1U)
#define SRC_STAT_MEGA_UNDER_RST_SHIFT            (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_MEGA_UNDER_RST(x)               (((uint32_t)(((uint32_t)(x)) << SRC_STAT_MEGA_UNDER_RST_SHIFT)) & SRC_STAT_MEGA_UNDER_RST_MASK)

#define SRC_STAT_MEGA_RST_BY_HW_MASK             (0x4U)
#define SRC_STAT_MEGA_RST_BY_HW_SHIFT            (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_MEGA_RST_BY_HW(x)               (((uint32_t)(((uint32_t)(x)) << SRC_STAT_MEGA_RST_BY_HW_SHIFT)) & SRC_STAT_MEGA_RST_BY_HW_MASK)

#define SRC_STAT_MEGA_RST_BY_SW_MASK             (0x8U)
#define SRC_STAT_MEGA_RST_BY_SW_SHIFT            (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_MEGA_RST_BY_SW(x)               (((uint32_t)(((uint32_t)(x)) << SRC_STAT_MEGA_RST_BY_SW_SHIFT)) & SRC_STAT_MEGA_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_DISPLAY - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_DISPLAY_DOMAIN_MODE_MASK      (0x1U)
#define SRC_AUTHEN_DISPLAY_DOMAIN_MODE_SHIFT     (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_DISPLAY_DOMAIN_MODE(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_DISPLAY_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_DISPLAY_SETPOINT_MODE_MASK    (0x2U)
#define SRC_AUTHEN_DISPLAY_SETPOINT_MODE_SHIFT   (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_DISPLAY_SETPOINT_MODE(x)      (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_DISPLAY_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_DISPLAY_LOCK_MODE_MASK        (0x80U)
#define SRC_AUTHEN_DISPLAY_LOCK_MODE_SHIFT       (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_DISPLAY_LOCK_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_LOCK_MODE_SHIFT)) & SRC_AUTHEN_DISPLAY_LOCK_MODE_MASK)

#define SRC_AUTHEN_DISPLAY_ASSIGN_LIST_MASK      (0xF00U)
#define SRC_AUTHEN_DISPLAY_ASSIGN_LIST_SHIFT     (8U)
#define SRC_AUTHEN_DISPLAY_ASSIGN_LIST(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_DISPLAY_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_DISPLAY_LOCK_ASSIGN_MASK      (0x8000U)
#define SRC_AUTHEN_DISPLAY_LOCK_ASSIGN_SHIFT     (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_DISPLAY_LOCK_ASSIGN(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_DISPLAY_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_DISPLAY_WHITE_LIST_MASK       (0xF0000U)
#define SRC_AUTHEN_DISPLAY_WHITE_LIST_SHIFT      (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_DISPLAY_WHITE_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_WHITE_LIST_SHIFT)) & SRC_AUTHEN_DISPLAY_WHITE_LIST_MASK)

#define SRC_AUTHEN_DISPLAY_LOCK_LIST_MASK        (0x800000U)
#define SRC_AUTHEN_DISPLAY_LOCK_LIST_SHIFT       (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_DISPLAY_LOCK_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_LOCK_LIST_SHIFT)) & SRC_AUTHEN_DISPLAY_LOCK_LIST_MASK)

#define SRC_AUTHEN_DISPLAY_USER_MASK             (0x1000000U)
#define SRC_AUTHEN_DISPLAY_USER_SHIFT            (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_DISPLAY_USER(x)               (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_USER_SHIFT)) & SRC_AUTHEN_DISPLAY_USER_MASK)

#define SRC_AUTHEN_DISPLAY_NONSECURE_MASK        (0x2000000U)
#define SRC_AUTHEN_DISPLAY_NONSECURE_SHIFT       (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_DISPLAY_NONSECURE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_NONSECURE_SHIFT)) & SRC_AUTHEN_DISPLAY_NONSECURE_MASK)

#define SRC_AUTHEN_DISPLAY_LOCK_SETTING_MASK     (0x80000000U)
#define SRC_AUTHEN_DISPLAY_LOCK_SETTING_SHIFT    (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_DISPLAY_LOCK_SETTING(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_DISPLAY_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_DISPLAY_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_DISPLAY - Slice Control Register */
/*! @{ */

#define SRC_CTRL_DISPLAY_SW_RESET_MASK           (0x1U)
#define SRC_CTRL_DISPLAY_SW_RESET_SHIFT          (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_DISPLAY_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_DISPLAY_SW_RESET_SHIFT)) & SRC_CTRL_DISPLAY_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_DISPLAY - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_DISPLAY_SETPOINT0_MASK      (0x1U)
#define SRC_SETPOINT_DISPLAY_SETPOINT0_SHIFT     (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT0(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT0_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT0_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT1_MASK      (0x2U)
#define SRC_SETPOINT_DISPLAY_SETPOINT1_SHIFT     (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT1(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT1_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT1_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT2_MASK      (0x4U)
#define SRC_SETPOINT_DISPLAY_SETPOINT2_SHIFT     (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT2(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT2_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT2_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT3_MASK      (0x8U)
#define SRC_SETPOINT_DISPLAY_SETPOINT3_SHIFT     (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT3(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT3_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT3_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT4_MASK      (0x10U)
#define SRC_SETPOINT_DISPLAY_SETPOINT4_SHIFT     (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT4(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT4_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT4_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT5_MASK      (0x20U)
#define SRC_SETPOINT_DISPLAY_SETPOINT5_SHIFT     (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT5(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT5_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT5_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT6_MASK      (0x40U)
#define SRC_SETPOINT_DISPLAY_SETPOINT6_SHIFT     (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT6(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT6_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT6_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT7_MASK      (0x80U)
#define SRC_SETPOINT_DISPLAY_SETPOINT7_SHIFT     (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT7(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT7_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT7_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT8_MASK      (0x100U)
#define SRC_SETPOINT_DISPLAY_SETPOINT8_SHIFT     (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT8(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT8_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT8_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT9_MASK      (0x200U)
#define SRC_SETPOINT_DISPLAY_SETPOINT9_SHIFT     (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT9(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT9_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT9_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT10_MASK     (0x400U)
#define SRC_SETPOINT_DISPLAY_SETPOINT10_SHIFT    (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT10(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT10_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT10_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT11_MASK     (0x800U)
#define SRC_SETPOINT_DISPLAY_SETPOINT11_SHIFT    (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT11(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT11_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT11_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT12_MASK     (0x1000U)
#define SRC_SETPOINT_DISPLAY_SETPOINT12_SHIFT    (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT12(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT12_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT12_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT13_MASK     (0x2000U)
#define SRC_SETPOINT_DISPLAY_SETPOINT13_SHIFT    (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT13(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT13_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT13_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT14_MASK     (0x4000U)
#define SRC_SETPOINT_DISPLAY_SETPOINT14_SHIFT    (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT14(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT14_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT14_MASK)

#define SRC_SETPOINT_DISPLAY_SETPOINT15_MASK     (0x8000U)
#define SRC_SETPOINT_DISPLAY_SETPOINT15_SHIFT    (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_DISPLAY_SETPOINT15(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_DISPLAY_SETPOINT15_SHIFT)) & SRC_SETPOINT_DISPLAY_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_DISPLAY - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_DISPLAY_CPU0_RUN_MASK         (0x1U)
#define SRC_DOMAIN_DISPLAY_CPU0_RUN_SHIFT        (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_DISPLAY_CPU0_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU0_RUN_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU0_RUN_MASK)

#define SRC_DOMAIN_DISPLAY_CPU0_WAIT_MASK        (0x2U)
#define SRC_DOMAIN_DISPLAY_CPU0_WAIT_SHIFT       (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_DISPLAY_CPU0_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU0_WAIT_MASK)

#define SRC_DOMAIN_DISPLAY_CPU0_STOP_MASK        (0x4U)
#define SRC_DOMAIN_DISPLAY_CPU0_STOP_SHIFT       (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_DISPLAY_CPU0_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU0_STOP_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU0_STOP_MASK)

#define SRC_DOMAIN_DISPLAY_CPU0_SUSP_MASK        (0x8U)
#define SRC_DOMAIN_DISPLAY_CPU0_SUSP_SHIFT       (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_DISPLAY_CPU0_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU0_SUSP_MASK)

#define SRC_DOMAIN_DISPLAY_CPU1_RUN_MASK         (0x10U)
#define SRC_DOMAIN_DISPLAY_CPU1_RUN_SHIFT        (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_DISPLAY_CPU1_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU1_RUN_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU1_RUN_MASK)

#define SRC_DOMAIN_DISPLAY_CPU1_WAIT_MASK        (0x20U)
#define SRC_DOMAIN_DISPLAY_CPU1_WAIT_SHIFT       (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_DISPLAY_CPU1_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU1_WAIT_MASK)

#define SRC_DOMAIN_DISPLAY_CPU1_STOP_MASK        (0x40U)
#define SRC_DOMAIN_DISPLAY_CPU1_STOP_SHIFT       (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_DISPLAY_CPU1_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU1_STOP_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU1_STOP_MASK)

#define SRC_DOMAIN_DISPLAY_CPU1_SUSP_MASK        (0x80U)
#define SRC_DOMAIN_DISPLAY_CPU1_SUSP_SHIFT       (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_DISPLAY_CPU1_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_DISPLAY_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_DISPLAY_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_DISPLAY - Slice Status Register */
/*! @{ */

#define SRC_STAT_DISPLAY_UNDER_RST_MASK          (0x1U)
#define SRC_STAT_DISPLAY_UNDER_RST_SHIFT         (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_DISPLAY_UNDER_RST(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_DISPLAY_UNDER_RST_SHIFT)) & SRC_STAT_DISPLAY_UNDER_RST_MASK)

#define SRC_STAT_DISPLAY_RST_BY_HW_MASK          (0x4U)
#define SRC_STAT_DISPLAY_RST_BY_HW_SHIFT         (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_DISPLAY_RST_BY_HW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_DISPLAY_RST_BY_HW_SHIFT)) & SRC_STAT_DISPLAY_RST_BY_HW_MASK)

#define SRC_STAT_DISPLAY_RST_BY_SW_MASK          (0x8U)
#define SRC_STAT_DISPLAY_RST_BY_SW_SHIFT         (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_DISPLAY_RST_BY_SW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_DISPLAY_RST_BY_SW_SHIFT)) & SRC_STAT_DISPLAY_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_WAKEUP - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_WAKEUP_DOMAIN_MODE_MASK       (0x1U)
#define SRC_AUTHEN_WAKEUP_DOMAIN_MODE_SHIFT      (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_WAKEUP_DOMAIN_MODE(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_WAKEUP_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_WAKEUP_SETPOINT_MODE_MASK     (0x2U)
#define SRC_AUTHEN_WAKEUP_SETPOINT_MODE_SHIFT    (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_WAKEUP_SETPOINT_MODE(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_WAKEUP_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_WAKEUP_LOCK_MODE_MASK         (0x80U)
#define SRC_AUTHEN_WAKEUP_LOCK_MODE_SHIFT        (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_WAKEUP_LOCK_MODE(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_LOCK_MODE_SHIFT)) & SRC_AUTHEN_WAKEUP_LOCK_MODE_MASK)

#define SRC_AUTHEN_WAKEUP_ASSIGN_LIST_MASK       (0xF00U)
#define SRC_AUTHEN_WAKEUP_ASSIGN_LIST_SHIFT      (8U)
#define SRC_AUTHEN_WAKEUP_ASSIGN_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_WAKEUP_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_WAKEUP_LOCK_ASSIGN_MASK       (0x8000U)
#define SRC_AUTHEN_WAKEUP_LOCK_ASSIGN_SHIFT      (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_WAKEUP_LOCK_ASSIGN(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_WAKEUP_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_WAKEUP_WHITE_LIST_MASK        (0xF0000U)
#define SRC_AUTHEN_WAKEUP_WHITE_LIST_SHIFT       (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_WAKEUP_WHITE_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_WHITE_LIST_SHIFT)) & SRC_AUTHEN_WAKEUP_WHITE_LIST_MASK)

#define SRC_AUTHEN_WAKEUP_LOCK_LIST_MASK         (0x800000U)
#define SRC_AUTHEN_WAKEUP_LOCK_LIST_SHIFT        (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_WAKEUP_LOCK_LIST(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_LOCK_LIST_SHIFT)) & SRC_AUTHEN_WAKEUP_LOCK_LIST_MASK)

#define SRC_AUTHEN_WAKEUP_USER_MASK              (0x1000000U)
#define SRC_AUTHEN_WAKEUP_USER_SHIFT             (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_WAKEUP_USER(x)                (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_USER_SHIFT)) & SRC_AUTHEN_WAKEUP_USER_MASK)

#define SRC_AUTHEN_WAKEUP_NONSECURE_MASK         (0x2000000U)
#define SRC_AUTHEN_WAKEUP_NONSECURE_SHIFT        (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_WAKEUP_NONSECURE(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_NONSECURE_SHIFT)) & SRC_AUTHEN_WAKEUP_NONSECURE_MASK)

#define SRC_AUTHEN_WAKEUP_LOCK_SETTING_MASK      (0x80000000U)
#define SRC_AUTHEN_WAKEUP_LOCK_SETTING_SHIFT     (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_WAKEUP_LOCK_SETTING(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_WAKEUP_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_WAKEUP_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_WAKEUP - Slice Control Register */
/*! @{ */

#define SRC_CTRL_WAKEUP_SW_RESET_MASK            (0x1U)
#define SRC_CTRL_WAKEUP_SW_RESET_SHIFT           (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_WAKEUP_SW_RESET(x)              (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_WAKEUP_SW_RESET_SHIFT)) & SRC_CTRL_WAKEUP_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_WAKEUP - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_WAKEUP_SETPOINT0_MASK       (0x1U)
#define SRC_SETPOINT_WAKEUP_SETPOINT0_SHIFT      (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT0(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT0_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT0_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT1_MASK       (0x2U)
#define SRC_SETPOINT_WAKEUP_SETPOINT1_SHIFT      (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT1(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT1_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT1_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT2_MASK       (0x4U)
#define SRC_SETPOINT_WAKEUP_SETPOINT2_SHIFT      (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT2(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT2_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT2_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT3_MASK       (0x8U)
#define SRC_SETPOINT_WAKEUP_SETPOINT3_SHIFT      (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT3(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT3_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT3_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT4_MASK       (0x10U)
#define SRC_SETPOINT_WAKEUP_SETPOINT4_SHIFT      (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT4(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT4_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT4_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT5_MASK       (0x20U)
#define SRC_SETPOINT_WAKEUP_SETPOINT5_SHIFT      (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT5(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT5_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT5_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT6_MASK       (0x40U)
#define SRC_SETPOINT_WAKEUP_SETPOINT6_SHIFT      (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT6(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT6_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT6_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT7_MASK       (0x80U)
#define SRC_SETPOINT_WAKEUP_SETPOINT7_SHIFT      (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT7(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT7_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT7_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT8_MASK       (0x100U)
#define SRC_SETPOINT_WAKEUP_SETPOINT8_SHIFT      (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT8(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT8_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT8_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT9_MASK       (0x200U)
#define SRC_SETPOINT_WAKEUP_SETPOINT9_SHIFT      (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT9(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT9_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT9_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT10_MASK      (0x400U)
#define SRC_SETPOINT_WAKEUP_SETPOINT10_SHIFT     (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT10(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT10_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT10_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT11_MASK      (0x800U)
#define SRC_SETPOINT_WAKEUP_SETPOINT11_SHIFT     (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT11(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT11_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT11_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT12_MASK      (0x1000U)
#define SRC_SETPOINT_WAKEUP_SETPOINT12_SHIFT     (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT12(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT12_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT12_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT13_MASK      (0x2000U)
#define SRC_SETPOINT_WAKEUP_SETPOINT13_SHIFT     (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT13(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT13_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT13_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT14_MASK      (0x4000U)
#define SRC_SETPOINT_WAKEUP_SETPOINT14_SHIFT     (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT14(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT14_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT14_MASK)

#define SRC_SETPOINT_WAKEUP_SETPOINT15_MASK      (0x8000U)
#define SRC_SETPOINT_WAKEUP_SETPOINT15_SHIFT     (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_WAKEUP_SETPOINT15(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_WAKEUP_SETPOINT15_SHIFT)) & SRC_SETPOINT_WAKEUP_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_WAKEUP - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_WAKEUP_CPU0_RUN_MASK          (0x1U)
#define SRC_DOMAIN_WAKEUP_CPU0_RUN_SHIFT         (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_WAKEUP_CPU0_RUN(x)            (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU0_RUN_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU0_RUN_MASK)

#define SRC_DOMAIN_WAKEUP_CPU0_WAIT_MASK         (0x2U)
#define SRC_DOMAIN_WAKEUP_CPU0_WAIT_SHIFT        (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_WAKEUP_CPU0_WAIT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU0_WAIT_MASK)

#define SRC_DOMAIN_WAKEUP_CPU0_STOP_MASK         (0x4U)
#define SRC_DOMAIN_WAKEUP_CPU0_STOP_SHIFT        (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_WAKEUP_CPU0_STOP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU0_STOP_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU0_STOP_MASK)

#define SRC_DOMAIN_WAKEUP_CPU0_SUSP_MASK         (0x8U)
#define SRC_DOMAIN_WAKEUP_CPU0_SUSP_SHIFT        (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_WAKEUP_CPU0_SUSP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU0_SUSP_MASK)

#define SRC_DOMAIN_WAKEUP_CPU1_RUN_MASK          (0x10U)
#define SRC_DOMAIN_WAKEUP_CPU1_RUN_SHIFT         (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_WAKEUP_CPU1_RUN(x)            (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU1_RUN_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU1_RUN_MASK)

#define SRC_DOMAIN_WAKEUP_CPU1_WAIT_MASK         (0x20U)
#define SRC_DOMAIN_WAKEUP_CPU1_WAIT_SHIFT        (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_WAKEUP_CPU1_WAIT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU1_WAIT_MASK)

#define SRC_DOMAIN_WAKEUP_CPU1_STOP_MASK         (0x40U)
#define SRC_DOMAIN_WAKEUP_CPU1_STOP_SHIFT        (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_WAKEUP_CPU1_STOP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU1_STOP_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU1_STOP_MASK)

#define SRC_DOMAIN_WAKEUP_CPU1_SUSP_MASK         (0x80U)
#define SRC_DOMAIN_WAKEUP_CPU1_SUSP_SHIFT        (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_WAKEUP_CPU1_SUSP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_WAKEUP_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_WAKEUP_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_WAKEUP - Slice Status Register */
/*! @{ */

#define SRC_STAT_WAKEUP_UNDER_RST_MASK           (0x1U)
#define SRC_STAT_WAKEUP_UNDER_RST_SHIFT          (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_WAKEUP_UNDER_RST(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_WAKEUP_UNDER_RST_SHIFT)) & SRC_STAT_WAKEUP_UNDER_RST_MASK)

#define SRC_STAT_WAKEUP_RST_BY_HW_MASK           (0x4U)
#define SRC_STAT_WAKEUP_RST_BY_HW_SHIFT          (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_WAKEUP_RST_BY_HW(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_WAKEUP_RST_BY_HW_SHIFT)) & SRC_STAT_WAKEUP_RST_BY_HW_MASK)

#define SRC_STAT_WAKEUP_RST_BY_SW_MASK           (0x8U)
#define SRC_STAT_WAKEUP_RST_BY_SW_SHIFT          (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_WAKEUP_RST_BY_SW(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_WAKEUP_RST_BY_SW_SHIFT)) & SRC_STAT_WAKEUP_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_M4CORE - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_M4CORE_DOMAIN_MODE_MASK       (0x1U)
#define SRC_AUTHEN_M4CORE_DOMAIN_MODE_SHIFT      (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_M4CORE_DOMAIN_MODE(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_M4CORE_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_M4CORE_SETPOINT_MODE_MASK     (0x2U)
#define SRC_AUTHEN_M4CORE_SETPOINT_MODE_SHIFT    (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_M4CORE_SETPOINT_MODE(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_M4CORE_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_M4CORE_LOCK_MODE_MASK         (0x80U)
#define SRC_AUTHEN_M4CORE_LOCK_MODE_SHIFT        (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_M4CORE_LOCK_MODE(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_LOCK_MODE_SHIFT)) & SRC_AUTHEN_M4CORE_LOCK_MODE_MASK)

#define SRC_AUTHEN_M4CORE_ASSIGN_LIST_MASK       (0xF00U)
#define SRC_AUTHEN_M4CORE_ASSIGN_LIST_SHIFT      (8U)
#define SRC_AUTHEN_M4CORE_ASSIGN_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_M4CORE_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_M4CORE_LOCK_ASSIGN_MASK       (0x8000U)
#define SRC_AUTHEN_M4CORE_LOCK_ASSIGN_SHIFT      (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_M4CORE_LOCK_ASSIGN(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_M4CORE_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_M4CORE_WHITE_LIST_MASK        (0xF0000U)
#define SRC_AUTHEN_M4CORE_WHITE_LIST_SHIFT       (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_M4CORE_WHITE_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_WHITE_LIST_SHIFT)) & SRC_AUTHEN_M4CORE_WHITE_LIST_MASK)

#define SRC_AUTHEN_M4CORE_LOCK_LIST_MASK         (0x800000U)
#define SRC_AUTHEN_M4CORE_LOCK_LIST_SHIFT        (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_M4CORE_LOCK_LIST(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_LOCK_LIST_SHIFT)) & SRC_AUTHEN_M4CORE_LOCK_LIST_MASK)

#define SRC_AUTHEN_M4CORE_USER_MASK              (0x1000000U)
#define SRC_AUTHEN_M4CORE_USER_SHIFT             (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_M4CORE_USER(x)                (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_USER_SHIFT)) & SRC_AUTHEN_M4CORE_USER_MASK)

#define SRC_AUTHEN_M4CORE_NONSECURE_MASK         (0x2000000U)
#define SRC_AUTHEN_M4CORE_NONSECURE_SHIFT        (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_M4CORE_NONSECURE(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_NONSECURE_SHIFT)) & SRC_AUTHEN_M4CORE_NONSECURE_MASK)

#define SRC_AUTHEN_M4CORE_LOCK_SETTING_MASK      (0x80000000U)
#define SRC_AUTHEN_M4CORE_LOCK_SETTING_SHIFT     (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_M4CORE_LOCK_SETTING(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4CORE_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_M4CORE_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_M4CORE - Slice Control Register */
/*! @{ */

#define SRC_CTRL_M4CORE_SW_RESET_MASK            (0x1U)
#define SRC_CTRL_M4CORE_SW_RESET_SHIFT           (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_M4CORE_SW_RESET(x)              (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_M4CORE_SW_RESET_SHIFT)) & SRC_CTRL_M4CORE_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_M4CORE - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_M4CORE_SETPOINT0_MASK       (0x1U)
#define SRC_SETPOINT_M4CORE_SETPOINT0_SHIFT      (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT0(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT0_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT0_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT1_MASK       (0x2U)
#define SRC_SETPOINT_M4CORE_SETPOINT1_SHIFT      (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT1(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT1_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT1_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT2_MASK       (0x4U)
#define SRC_SETPOINT_M4CORE_SETPOINT2_SHIFT      (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT2(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT2_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT2_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT3_MASK       (0x8U)
#define SRC_SETPOINT_M4CORE_SETPOINT3_SHIFT      (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT3(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT3_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT3_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT4_MASK       (0x10U)
#define SRC_SETPOINT_M4CORE_SETPOINT4_SHIFT      (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT4(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT4_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT4_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT5_MASK       (0x20U)
#define SRC_SETPOINT_M4CORE_SETPOINT5_SHIFT      (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT5(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT5_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT5_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT6_MASK       (0x40U)
#define SRC_SETPOINT_M4CORE_SETPOINT6_SHIFT      (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT6(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT6_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT6_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT7_MASK       (0x80U)
#define SRC_SETPOINT_M4CORE_SETPOINT7_SHIFT      (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT7(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT7_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT7_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT8_MASK       (0x100U)
#define SRC_SETPOINT_M4CORE_SETPOINT8_SHIFT      (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT8(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT8_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT8_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT9_MASK       (0x200U)
#define SRC_SETPOINT_M4CORE_SETPOINT9_SHIFT      (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT9(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT9_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT9_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT10_MASK      (0x400U)
#define SRC_SETPOINT_M4CORE_SETPOINT10_SHIFT     (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT10(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT10_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT10_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT11_MASK      (0x800U)
#define SRC_SETPOINT_M4CORE_SETPOINT11_SHIFT     (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT11(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT11_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT11_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT12_MASK      (0x1000U)
#define SRC_SETPOINT_M4CORE_SETPOINT12_SHIFT     (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT12(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT12_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT12_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT13_MASK      (0x2000U)
#define SRC_SETPOINT_M4CORE_SETPOINT13_SHIFT     (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT13(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT13_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT13_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT14_MASK      (0x4000U)
#define SRC_SETPOINT_M4CORE_SETPOINT14_SHIFT     (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT14(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT14_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT14_MASK)

#define SRC_SETPOINT_M4CORE_SETPOINT15_MASK      (0x8000U)
#define SRC_SETPOINT_M4CORE_SETPOINT15_SHIFT     (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4CORE_SETPOINT15(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4CORE_SETPOINT15_SHIFT)) & SRC_SETPOINT_M4CORE_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_M4CORE - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_M4CORE_CPU0_RUN_MASK          (0x1U)
#define SRC_DOMAIN_M4CORE_CPU0_RUN_SHIFT         (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_M4CORE_CPU0_RUN(x)            (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU0_RUN_SHIFT)) & SRC_DOMAIN_M4CORE_CPU0_RUN_MASK)

#define SRC_DOMAIN_M4CORE_CPU0_WAIT_MASK         (0x2U)
#define SRC_DOMAIN_M4CORE_CPU0_WAIT_SHIFT        (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_M4CORE_CPU0_WAIT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_M4CORE_CPU0_WAIT_MASK)

#define SRC_DOMAIN_M4CORE_CPU0_STOP_MASK         (0x4U)
#define SRC_DOMAIN_M4CORE_CPU0_STOP_SHIFT        (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_M4CORE_CPU0_STOP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU0_STOP_SHIFT)) & SRC_DOMAIN_M4CORE_CPU0_STOP_MASK)

#define SRC_DOMAIN_M4CORE_CPU0_SUSP_MASK         (0x8U)
#define SRC_DOMAIN_M4CORE_CPU0_SUSP_SHIFT        (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_M4CORE_CPU0_SUSP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_M4CORE_CPU0_SUSP_MASK)

#define SRC_DOMAIN_M4CORE_CPU1_RUN_MASK          (0x10U)
#define SRC_DOMAIN_M4CORE_CPU1_RUN_SHIFT         (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_M4CORE_CPU1_RUN(x)            (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU1_RUN_SHIFT)) & SRC_DOMAIN_M4CORE_CPU1_RUN_MASK)

#define SRC_DOMAIN_M4CORE_CPU1_WAIT_MASK         (0x20U)
#define SRC_DOMAIN_M4CORE_CPU1_WAIT_SHIFT        (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_M4CORE_CPU1_WAIT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_M4CORE_CPU1_WAIT_MASK)

#define SRC_DOMAIN_M4CORE_CPU1_STOP_MASK         (0x40U)
#define SRC_DOMAIN_M4CORE_CPU1_STOP_SHIFT        (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_M4CORE_CPU1_STOP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU1_STOP_SHIFT)) & SRC_DOMAIN_M4CORE_CPU1_STOP_MASK)

#define SRC_DOMAIN_M4CORE_CPU1_SUSP_MASK         (0x80U)
#define SRC_DOMAIN_M4CORE_CPU1_SUSP_SHIFT        (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_M4CORE_CPU1_SUSP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4CORE_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_M4CORE_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_M4CORE - Slice Status Register */
/*! @{ */

#define SRC_STAT_M4CORE_UNDER_RST_MASK           (0x1U)
#define SRC_STAT_M4CORE_UNDER_RST_SHIFT          (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_M4CORE_UNDER_RST(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M4CORE_UNDER_RST_SHIFT)) & SRC_STAT_M4CORE_UNDER_RST_MASK)

#define SRC_STAT_M4CORE_RST_BY_HW_MASK           (0x4U)
#define SRC_STAT_M4CORE_RST_BY_HW_SHIFT          (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_M4CORE_RST_BY_HW(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M4CORE_RST_BY_HW_SHIFT)) & SRC_STAT_M4CORE_RST_BY_HW_MASK)

#define SRC_STAT_M4CORE_RST_BY_SW_MASK           (0x8U)
#define SRC_STAT_M4CORE_RST_BY_SW_SHIFT          (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_M4CORE_RST_BY_SW(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M4CORE_RST_BY_SW_SHIFT)) & SRC_STAT_M4CORE_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_M7CORE - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_M7CORE_DOMAIN_MODE_MASK       (0x1U)
#define SRC_AUTHEN_M7CORE_DOMAIN_MODE_SHIFT      (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_M7CORE_DOMAIN_MODE(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_M7CORE_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_M7CORE_SETPOINT_MODE_MASK     (0x2U)
#define SRC_AUTHEN_M7CORE_SETPOINT_MODE_SHIFT    (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_M7CORE_SETPOINT_MODE(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_M7CORE_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_M7CORE_LOCK_MODE_MASK         (0x80U)
#define SRC_AUTHEN_M7CORE_LOCK_MODE_SHIFT        (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_M7CORE_LOCK_MODE(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_LOCK_MODE_SHIFT)) & SRC_AUTHEN_M7CORE_LOCK_MODE_MASK)

#define SRC_AUTHEN_M7CORE_ASSIGN_LIST_MASK       (0xF00U)
#define SRC_AUTHEN_M7CORE_ASSIGN_LIST_SHIFT      (8U)
#define SRC_AUTHEN_M7CORE_ASSIGN_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_M7CORE_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_M7CORE_LOCK_ASSIGN_MASK       (0x8000U)
#define SRC_AUTHEN_M7CORE_LOCK_ASSIGN_SHIFT      (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_M7CORE_LOCK_ASSIGN(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_M7CORE_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_M7CORE_WHITE_LIST_MASK        (0xF0000U)
#define SRC_AUTHEN_M7CORE_WHITE_LIST_SHIFT       (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_M7CORE_WHITE_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_WHITE_LIST_SHIFT)) & SRC_AUTHEN_M7CORE_WHITE_LIST_MASK)

#define SRC_AUTHEN_M7CORE_LOCK_LIST_MASK         (0x800000U)
#define SRC_AUTHEN_M7CORE_LOCK_LIST_SHIFT        (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_M7CORE_LOCK_LIST(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_LOCK_LIST_SHIFT)) & SRC_AUTHEN_M7CORE_LOCK_LIST_MASK)

#define SRC_AUTHEN_M7CORE_USER_MASK              (0x1000000U)
#define SRC_AUTHEN_M7CORE_USER_SHIFT             (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_M7CORE_USER(x)                (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_USER_SHIFT)) & SRC_AUTHEN_M7CORE_USER_MASK)

#define SRC_AUTHEN_M7CORE_NONSECURE_MASK         (0x2000000U)
#define SRC_AUTHEN_M7CORE_NONSECURE_SHIFT        (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_M7CORE_NONSECURE(x)           (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_NONSECURE_SHIFT)) & SRC_AUTHEN_M7CORE_NONSECURE_MASK)

#define SRC_AUTHEN_M7CORE_LOCK_SETTING_MASK      (0x80000000U)
#define SRC_AUTHEN_M7CORE_LOCK_SETTING_SHIFT     (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_M7CORE_LOCK_SETTING(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7CORE_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_M7CORE_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_M7CORE - Slice Control Register */
/*! @{ */

#define SRC_CTRL_M7CORE_SW_RESET_MASK            (0x1U)
#define SRC_CTRL_M7CORE_SW_RESET_SHIFT           (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_M7CORE_SW_RESET(x)              (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_M7CORE_SW_RESET_SHIFT)) & SRC_CTRL_M7CORE_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_M7CORE - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_M7CORE_SETPOINT0_MASK       (0x1U)
#define SRC_SETPOINT_M7CORE_SETPOINT0_SHIFT      (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT0(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT0_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT0_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT1_MASK       (0x2U)
#define SRC_SETPOINT_M7CORE_SETPOINT1_SHIFT      (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT1(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT1_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT1_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT2_MASK       (0x4U)
#define SRC_SETPOINT_M7CORE_SETPOINT2_SHIFT      (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT2(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT2_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT2_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT3_MASK       (0x8U)
#define SRC_SETPOINT_M7CORE_SETPOINT3_SHIFT      (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT3(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT3_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT3_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT4_MASK       (0x10U)
#define SRC_SETPOINT_M7CORE_SETPOINT4_SHIFT      (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT4(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT4_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT4_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT5_MASK       (0x20U)
#define SRC_SETPOINT_M7CORE_SETPOINT5_SHIFT      (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT5(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT5_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT5_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT6_MASK       (0x40U)
#define SRC_SETPOINT_M7CORE_SETPOINT6_SHIFT      (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT6(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT6_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT6_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT7_MASK       (0x80U)
#define SRC_SETPOINT_M7CORE_SETPOINT7_SHIFT      (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT7(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT7_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT7_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT8_MASK       (0x100U)
#define SRC_SETPOINT_M7CORE_SETPOINT8_SHIFT      (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT8(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT8_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT8_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT9_MASK       (0x200U)
#define SRC_SETPOINT_M7CORE_SETPOINT9_SHIFT      (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT9(x)         (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT9_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT9_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT10_MASK      (0x400U)
#define SRC_SETPOINT_M7CORE_SETPOINT10_SHIFT     (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT10(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT10_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT10_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT11_MASK      (0x800U)
#define SRC_SETPOINT_M7CORE_SETPOINT11_SHIFT     (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT11(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT11_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT11_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT12_MASK      (0x1000U)
#define SRC_SETPOINT_M7CORE_SETPOINT12_SHIFT     (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT12(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT12_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT12_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT13_MASK      (0x2000U)
#define SRC_SETPOINT_M7CORE_SETPOINT13_SHIFT     (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT13(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT13_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT13_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT14_MASK      (0x4000U)
#define SRC_SETPOINT_M7CORE_SETPOINT14_SHIFT     (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT14(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT14_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT14_MASK)

#define SRC_SETPOINT_M7CORE_SETPOINT15_MASK      (0x8000U)
#define SRC_SETPOINT_M7CORE_SETPOINT15_SHIFT     (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7CORE_SETPOINT15(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7CORE_SETPOINT15_SHIFT)) & SRC_SETPOINT_M7CORE_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_M7CORE - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_M7CORE_CPU0_RUN_MASK          (0x1U)
#define SRC_DOMAIN_M7CORE_CPU0_RUN_SHIFT         (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_M7CORE_CPU0_RUN(x)            (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU0_RUN_SHIFT)) & SRC_DOMAIN_M7CORE_CPU0_RUN_MASK)

#define SRC_DOMAIN_M7CORE_CPU0_WAIT_MASK         (0x2U)
#define SRC_DOMAIN_M7CORE_CPU0_WAIT_SHIFT        (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_M7CORE_CPU0_WAIT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_M7CORE_CPU0_WAIT_MASK)

#define SRC_DOMAIN_M7CORE_CPU0_STOP_MASK         (0x4U)
#define SRC_DOMAIN_M7CORE_CPU0_STOP_SHIFT        (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_M7CORE_CPU0_STOP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU0_STOP_SHIFT)) & SRC_DOMAIN_M7CORE_CPU0_STOP_MASK)

#define SRC_DOMAIN_M7CORE_CPU0_SUSP_MASK         (0x8U)
#define SRC_DOMAIN_M7CORE_CPU0_SUSP_SHIFT        (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_M7CORE_CPU0_SUSP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_M7CORE_CPU0_SUSP_MASK)

#define SRC_DOMAIN_M7CORE_CPU1_RUN_MASK          (0x10U)
#define SRC_DOMAIN_M7CORE_CPU1_RUN_SHIFT         (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_M7CORE_CPU1_RUN(x)            (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU1_RUN_SHIFT)) & SRC_DOMAIN_M7CORE_CPU1_RUN_MASK)

#define SRC_DOMAIN_M7CORE_CPU1_WAIT_MASK         (0x20U)
#define SRC_DOMAIN_M7CORE_CPU1_WAIT_SHIFT        (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_M7CORE_CPU1_WAIT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_M7CORE_CPU1_WAIT_MASK)

#define SRC_DOMAIN_M7CORE_CPU1_STOP_MASK         (0x40U)
#define SRC_DOMAIN_M7CORE_CPU1_STOP_SHIFT        (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_M7CORE_CPU1_STOP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU1_STOP_SHIFT)) & SRC_DOMAIN_M7CORE_CPU1_STOP_MASK)

#define SRC_DOMAIN_M7CORE_CPU1_SUSP_MASK         (0x80U)
#define SRC_DOMAIN_M7CORE_CPU1_SUSP_SHIFT        (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_M7CORE_CPU1_SUSP(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7CORE_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_M7CORE_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_M7CORE - Slice Status Register */
/*! @{ */

#define SRC_STAT_M7CORE_UNDER_RST_MASK           (0x1U)
#define SRC_STAT_M7CORE_UNDER_RST_SHIFT          (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_M7CORE_UNDER_RST(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M7CORE_UNDER_RST_SHIFT)) & SRC_STAT_M7CORE_UNDER_RST_MASK)

#define SRC_STAT_M7CORE_RST_BY_HW_MASK           (0x4U)
#define SRC_STAT_M7CORE_RST_BY_HW_SHIFT          (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_M7CORE_RST_BY_HW(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M7CORE_RST_BY_HW_SHIFT)) & SRC_STAT_M7CORE_RST_BY_HW_MASK)

#define SRC_STAT_M7CORE_RST_BY_SW_MASK           (0x8U)
#define SRC_STAT_M7CORE_RST_BY_SW_SHIFT          (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_M7CORE_RST_BY_SW(x)             (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M7CORE_RST_BY_SW_SHIFT)) & SRC_STAT_M7CORE_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_M4DEBUG - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_M4DEBUG_DOMAIN_MODE_MASK      (0x1U)
#define SRC_AUTHEN_M4DEBUG_DOMAIN_MODE_SHIFT     (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_M4DEBUG_DOMAIN_MODE(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_M4DEBUG_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_M4DEBUG_SETPOINT_MODE_MASK    (0x2U)
#define SRC_AUTHEN_M4DEBUG_SETPOINT_MODE_SHIFT   (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_M4DEBUG_SETPOINT_MODE(x)      (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_M4DEBUG_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_M4DEBUG_LOCK_MODE_MASK        (0x80U)
#define SRC_AUTHEN_M4DEBUG_LOCK_MODE_SHIFT       (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_M4DEBUG_LOCK_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_LOCK_MODE_SHIFT)) & SRC_AUTHEN_M4DEBUG_LOCK_MODE_MASK)

#define SRC_AUTHEN_M4DEBUG_ASSIGN_LIST_MASK      (0xF00U)
#define SRC_AUTHEN_M4DEBUG_ASSIGN_LIST_SHIFT     (8U)
#define SRC_AUTHEN_M4DEBUG_ASSIGN_LIST(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_M4DEBUG_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_M4DEBUG_LOCK_ASSIGN_MASK      (0x8000U)
#define SRC_AUTHEN_M4DEBUG_LOCK_ASSIGN_SHIFT     (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_M4DEBUG_LOCK_ASSIGN(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_M4DEBUG_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_M4DEBUG_WHITE_LIST_MASK       (0xF0000U)
#define SRC_AUTHEN_M4DEBUG_WHITE_LIST_SHIFT      (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_M4DEBUG_WHITE_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_WHITE_LIST_SHIFT)) & SRC_AUTHEN_M4DEBUG_WHITE_LIST_MASK)

#define SRC_AUTHEN_M4DEBUG_LOCK_LIST_MASK        (0x800000U)
#define SRC_AUTHEN_M4DEBUG_LOCK_LIST_SHIFT       (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_M4DEBUG_LOCK_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_LOCK_LIST_SHIFT)) & SRC_AUTHEN_M4DEBUG_LOCK_LIST_MASK)

#define SRC_AUTHEN_M4DEBUG_USER_MASK             (0x1000000U)
#define SRC_AUTHEN_M4DEBUG_USER_SHIFT            (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_M4DEBUG_USER(x)               (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_USER_SHIFT)) & SRC_AUTHEN_M4DEBUG_USER_MASK)

#define SRC_AUTHEN_M4DEBUG_NONSECURE_MASK        (0x2000000U)
#define SRC_AUTHEN_M4DEBUG_NONSECURE_SHIFT       (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_M4DEBUG_NONSECURE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_NONSECURE_SHIFT)) & SRC_AUTHEN_M4DEBUG_NONSECURE_MASK)

#define SRC_AUTHEN_M4DEBUG_LOCK_SETTING_MASK     (0x80000000U)
#define SRC_AUTHEN_M4DEBUG_LOCK_SETTING_SHIFT    (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_M4DEBUG_LOCK_SETTING(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M4DEBUG_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_M4DEBUG_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_M4DEBUG - Slice Control Register */
/*! @{ */

#define SRC_CTRL_M4DEBUG_SW_RESET_MASK           (0x1U)
#define SRC_CTRL_M4DEBUG_SW_RESET_SHIFT          (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_M4DEBUG_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_M4DEBUG_SW_RESET_SHIFT)) & SRC_CTRL_M4DEBUG_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_M4DEBUG - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_M4DEBUG_SETPOINT0_MASK      (0x1U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT0_SHIFT     (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT0(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT0_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT0_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT1_MASK      (0x2U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT1_SHIFT     (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT1(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT1_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT1_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT2_MASK      (0x4U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT2_SHIFT     (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT2(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT2_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT2_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT3_MASK      (0x8U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT3_SHIFT     (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT3(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT3_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT3_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT4_MASK      (0x10U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT4_SHIFT     (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT4(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT4_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT4_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT5_MASK      (0x20U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT5_SHIFT     (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT5(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT5_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT5_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT6_MASK      (0x40U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT6_SHIFT     (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT6(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT6_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT6_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT7_MASK      (0x80U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT7_SHIFT     (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT7(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT7_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT7_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT8_MASK      (0x100U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT8_SHIFT     (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT8(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT8_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT8_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT9_MASK      (0x200U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT9_SHIFT     (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT9(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT9_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT9_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT10_MASK     (0x400U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT10_SHIFT    (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT10(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT10_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT10_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT11_MASK     (0x800U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT11_SHIFT    (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT11(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT11_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT11_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT12_MASK     (0x1000U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT12_SHIFT    (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT12(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT12_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT12_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT13_MASK     (0x2000U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT13_SHIFT    (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT13(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT13_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT13_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT14_MASK     (0x4000U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT14_SHIFT    (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT14(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT14_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT14_MASK)

#define SRC_SETPOINT_M4DEBUG_SETPOINT15_MASK     (0x8000U)
#define SRC_SETPOINT_M4DEBUG_SETPOINT15_SHIFT    (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M4DEBUG_SETPOINT15(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M4DEBUG_SETPOINT15_SHIFT)) & SRC_SETPOINT_M4DEBUG_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_M4DEBUG - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_M4DEBUG_CPU0_RUN_MASK         (0x1U)
#define SRC_DOMAIN_M4DEBUG_CPU0_RUN_SHIFT        (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU0_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU0_RUN_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU0_RUN_MASK)

#define SRC_DOMAIN_M4DEBUG_CPU0_WAIT_MASK        (0x2U)
#define SRC_DOMAIN_M4DEBUG_CPU0_WAIT_SHIFT       (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU0_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU0_WAIT_MASK)

#define SRC_DOMAIN_M4DEBUG_CPU0_STOP_MASK        (0x4U)
#define SRC_DOMAIN_M4DEBUG_CPU0_STOP_SHIFT       (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU0_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU0_STOP_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU0_STOP_MASK)

#define SRC_DOMAIN_M4DEBUG_CPU0_SUSP_MASK        (0x8U)
#define SRC_DOMAIN_M4DEBUG_CPU0_SUSP_SHIFT       (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU0_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU0_SUSP_MASK)

#define SRC_DOMAIN_M4DEBUG_CPU1_RUN_MASK         (0x10U)
#define SRC_DOMAIN_M4DEBUG_CPU1_RUN_SHIFT        (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU1_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU1_RUN_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU1_RUN_MASK)

#define SRC_DOMAIN_M4DEBUG_CPU1_WAIT_MASK        (0x20U)
#define SRC_DOMAIN_M4DEBUG_CPU1_WAIT_SHIFT       (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU1_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU1_WAIT_MASK)

#define SRC_DOMAIN_M4DEBUG_CPU1_STOP_MASK        (0x40U)
#define SRC_DOMAIN_M4DEBUG_CPU1_STOP_SHIFT       (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU1_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU1_STOP_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU1_STOP_MASK)

#define SRC_DOMAIN_M4DEBUG_CPU1_SUSP_MASK        (0x80U)
#define SRC_DOMAIN_M4DEBUG_CPU1_SUSP_SHIFT       (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_M4DEBUG_CPU1_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M4DEBUG_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_M4DEBUG_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_M4DEBUG - Slice Status Register */
/*! @{ */

#define SRC_STAT_M4DEBUG_UNDER_RST_MASK          (0x1U)
#define SRC_STAT_M4DEBUG_UNDER_RST_SHIFT         (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_M4DEBUG_UNDER_RST(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M4DEBUG_UNDER_RST_SHIFT)) & SRC_STAT_M4DEBUG_UNDER_RST_MASK)

#define SRC_STAT_M4DEBUG_RST_BY_HW_MASK          (0x4U)
#define SRC_STAT_M4DEBUG_RST_BY_HW_SHIFT         (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_M4DEBUG_RST_BY_HW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M4DEBUG_RST_BY_HW_SHIFT)) & SRC_STAT_M4DEBUG_RST_BY_HW_MASK)

#define SRC_STAT_M4DEBUG_RST_BY_SW_MASK          (0x8U)
#define SRC_STAT_M4DEBUG_RST_BY_SW_SHIFT         (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_M4DEBUG_RST_BY_SW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M4DEBUG_RST_BY_SW_SHIFT)) & SRC_STAT_M4DEBUG_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_M7DEBUG - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_M7DEBUG_DOMAIN_MODE_MASK      (0x1U)
#define SRC_AUTHEN_M7DEBUG_DOMAIN_MODE_SHIFT     (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_M7DEBUG_DOMAIN_MODE(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_M7DEBUG_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_M7DEBUG_SETPOINT_MODE_MASK    (0x2U)
#define SRC_AUTHEN_M7DEBUG_SETPOINT_MODE_SHIFT   (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_M7DEBUG_SETPOINT_MODE(x)      (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_M7DEBUG_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_M7DEBUG_LOCK_MODE_MASK        (0x80U)
#define SRC_AUTHEN_M7DEBUG_LOCK_MODE_SHIFT       (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_M7DEBUG_LOCK_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_LOCK_MODE_SHIFT)) & SRC_AUTHEN_M7DEBUG_LOCK_MODE_MASK)

#define SRC_AUTHEN_M7DEBUG_ASSIGN_LIST_MASK      (0xF00U)
#define SRC_AUTHEN_M7DEBUG_ASSIGN_LIST_SHIFT     (8U)
#define SRC_AUTHEN_M7DEBUG_ASSIGN_LIST(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_M7DEBUG_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_M7DEBUG_LOCK_ASSIGN_MASK      (0x8000U)
#define SRC_AUTHEN_M7DEBUG_LOCK_ASSIGN_SHIFT     (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_M7DEBUG_LOCK_ASSIGN(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_M7DEBUG_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_M7DEBUG_WHITE_LIST_MASK       (0xF0000U)
#define SRC_AUTHEN_M7DEBUG_WHITE_LIST_SHIFT      (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_M7DEBUG_WHITE_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_WHITE_LIST_SHIFT)) & SRC_AUTHEN_M7DEBUG_WHITE_LIST_MASK)

#define SRC_AUTHEN_M7DEBUG_LOCK_LIST_MASK        (0x800000U)
#define SRC_AUTHEN_M7DEBUG_LOCK_LIST_SHIFT       (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_M7DEBUG_LOCK_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_LOCK_LIST_SHIFT)) & SRC_AUTHEN_M7DEBUG_LOCK_LIST_MASK)

#define SRC_AUTHEN_M7DEBUG_USER_MASK             (0x1000000U)
#define SRC_AUTHEN_M7DEBUG_USER_SHIFT            (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_M7DEBUG_USER(x)               (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_USER_SHIFT)) & SRC_AUTHEN_M7DEBUG_USER_MASK)

#define SRC_AUTHEN_M7DEBUG_NONSECURE_MASK        (0x2000000U)
#define SRC_AUTHEN_M7DEBUG_NONSECURE_SHIFT       (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_M7DEBUG_NONSECURE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_NONSECURE_SHIFT)) & SRC_AUTHEN_M7DEBUG_NONSECURE_MASK)

#define SRC_AUTHEN_M7DEBUG_LOCK_SETTING_MASK     (0x80000000U)
#define SRC_AUTHEN_M7DEBUG_LOCK_SETTING_SHIFT    (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_M7DEBUG_LOCK_SETTING(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_M7DEBUG_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_M7DEBUG_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_M7DEBUG - Slice Control Register */
/*! @{ */

#define SRC_CTRL_M7DEBUG_SW_RESET_MASK           (0x1U)
#define SRC_CTRL_M7DEBUG_SW_RESET_SHIFT          (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_M7DEBUG_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_M7DEBUG_SW_RESET_SHIFT)) & SRC_CTRL_M7DEBUG_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_M7DEBUG - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_M7DEBUG_SETPOINT0_MASK      (0x1U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT0_SHIFT     (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT0(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT0_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT0_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT1_MASK      (0x2U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT1_SHIFT     (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT1(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT1_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT1_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT2_MASK      (0x4U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT2_SHIFT     (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT2(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT2_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT2_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT3_MASK      (0x8U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT3_SHIFT     (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT3(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT3_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT3_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT4_MASK      (0x10U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT4_SHIFT     (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT4(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT4_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT4_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT5_MASK      (0x20U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT5_SHIFT     (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT5(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT5_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT5_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT6_MASK      (0x40U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT6_SHIFT     (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT6(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT6_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT6_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT7_MASK      (0x80U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT7_SHIFT     (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT7(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT7_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT7_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT8_MASK      (0x100U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT8_SHIFT     (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT8(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT8_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT8_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT9_MASK      (0x200U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT9_SHIFT     (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT9(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT9_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT9_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT10_MASK     (0x400U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT10_SHIFT    (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT10(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT10_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT10_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT11_MASK     (0x800U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT11_SHIFT    (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT11(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT11_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT11_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT12_MASK     (0x1000U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT12_SHIFT    (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT12(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT12_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT12_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT13_MASK     (0x2000U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT13_SHIFT    (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT13(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT13_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT13_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT14_MASK     (0x4000U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT14_SHIFT    (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT14(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT14_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT14_MASK)

#define SRC_SETPOINT_M7DEBUG_SETPOINT15_MASK     (0x8000U)
#define SRC_SETPOINT_M7DEBUG_SETPOINT15_SHIFT    (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_M7DEBUG_SETPOINT15(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_M7DEBUG_SETPOINT15_SHIFT)) & SRC_SETPOINT_M7DEBUG_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_M7DEBUG - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_M7DEBUG_CPU0_RUN_MASK         (0x1U)
#define SRC_DOMAIN_M7DEBUG_CPU0_RUN_SHIFT        (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU0_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU0_RUN_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU0_RUN_MASK)

#define SRC_DOMAIN_M7DEBUG_CPU0_WAIT_MASK        (0x2U)
#define SRC_DOMAIN_M7DEBUG_CPU0_WAIT_SHIFT       (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU0_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU0_WAIT_MASK)

#define SRC_DOMAIN_M7DEBUG_CPU0_STOP_MASK        (0x4U)
#define SRC_DOMAIN_M7DEBUG_CPU0_STOP_SHIFT       (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU0_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU0_STOP_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU0_STOP_MASK)

#define SRC_DOMAIN_M7DEBUG_CPU0_SUSP_MASK        (0x8U)
#define SRC_DOMAIN_M7DEBUG_CPU0_SUSP_SHIFT       (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU0_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU0_SUSP_MASK)

#define SRC_DOMAIN_M7DEBUG_CPU1_RUN_MASK         (0x10U)
#define SRC_DOMAIN_M7DEBUG_CPU1_RUN_SHIFT        (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU1_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU1_RUN_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU1_RUN_MASK)

#define SRC_DOMAIN_M7DEBUG_CPU1_WAIT_MASK        (0x20U)
#define SRC_DOMAIN_M7DEBUG_CPU1_WAIT_SHIFT       (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU1_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU1_WAIT_MASK)

#define SRC_DOMAIN_M7DEBUG_CPU1_STOP_MASK        (0x40U)
#define SRC_DOMAIN_M7DEBUG_CPU1_STOP_SHIFT       (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU1_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU1_STOP_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU1_STOP_MASK)

#define SRC_DOMAIN_M7DEBUG_CPU1_SUSP_MASK        (0x80U)
#define SRC_DOMAIN_M7DEBUG_CPU1_SUSP_SHIFT       (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_M7DEBUG_CPU1_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_M7DEBUG_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_M7DEBUG_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_M7DEBUG - Slice Status Register */
/*! @{ */

#define SRC_STAT_M7DEBUG_UNDER_RST_MASK          (0x1U)
#define SRC_STAT_M7DEBUG_UNDER_RST_SHIFT         (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_M7DEBUG_UNDER_RST(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M7DEBUG_UNDER_RST_SHIFT)) & SRC_STAT_M7DEBUG_UNDER_RST_MASK)

#define SRC_STAT_M7DEBUG_RST_BY_HW_MASK          (0x4U)
#define SRC_STAT_M7DEBUG_RST_BY_HW_SHIFT         (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_M7DEBUG_RST_BY_HW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M7DEBUG_RST_BY_HW_SHIFT)) & SRC_STAT_M7DEBUG_RST_BY_HW_MASK)

#define SRC_STAT_M7DEBUG_RST_BY_SW_MASK          (0x8U)
#define SRC_STAT_M7DEBUG_RST_BY_SW_SHIFT         (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_M7DEBUG_RST_BY_SW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_M7DEBUG_RST_BY_SW_SHIFT)) & SRC_STAT_M7DEBUG_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_USBPHY1 - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_USBPHY1_DOMAIN_MODE_MASK      (0x1U)
#define SRC_AUTHEN_USBPHY1_DOMAIN_MODE_SHIFT     (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_USBPHY1_DOMAIN_MODE(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_USBPHY1_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_USBPHY1_SETPOINT_MODE_MASK    (0x2U)
#define SRC_AUTHEN_USBPHY1_SETPOINT_MODE_SHIFT   (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_USBPHY1_SETPOINT_MODE(x)      (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_USBPHY1_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_USBPHY1_LOCK_MODE_MASK        (0x80U)
#define SRC_AUTHEN_USBPHY1_LOCK_MODE_SHIFT       (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_USBPHY1_LOCK_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_LOCK_MODE_SHIFT)) & SRC_AUTHEN_USBPHY1_LOCK_MODE_MASK)

#define SRC_AUTHEN_USBPHY1_ASSIGN_LIST_MASK      (0xF00U)
#define SRC_AUTHEN_USBPHY1_ASSIGN_LIST_SHIFT     (8U)
#define SRC_AUTHEN_USBPHY1_ASSIGN_LIST(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_USBPHY1_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_USBPHY1_LOCK_ASSIGN_MASK      (0x8000U)
#define SRC_AUTHEN_USBPHY1_LOCK_ASSIGN_SHIFT     (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_USBPHY1_LOCK_ASSIGN(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_USBPHY1_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_USBPHY1_WHITE_LIST_MASK       (0xF0000U)
#define SRC_AUTHEN_USBPHY1_WHITE_LIST_SHIFT      (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_USBPHY1_WHITE_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_WHITE_LIST_SHIFT)) & SRC_AUTHEN_USBPHY1_WHITE_LIST_MASK)

#define SRC_AUTHEN_USBPHY1_LOCK_LIST_MASK        (0x800000U)
#define SRC_AUTHEN_USBPHY1_LOCK_LIST_SHIFT       (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_USBPHY1_LOCK_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_LOCK_LIST_SHIFT)) & SRC_AUTHEN_USBPHY1_LOCK_LIST_MASK)

#define SRC_AUTHEN_USBPHY1_USER_MASK             (0x1000000U)
#define SRC_AUTHEN_USBPHY1_USER_SHIFT            (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_USBPHY1_USER(x)               (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_USER_SHIFT)) & SRC_AUTHEN_USBPHY1_USER_MASK)

#define SRC_AUTHEN_USBPHY1_NONSECURE_MASK        (0x2000000U)
#define SRC_AUTHEN_USBPHY1_NONSECURE_SHIFT       (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_USBPHY1_NONSECURE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_NONSECURE_SHIFT)) & SRC_AUTHEN_USBPHY1_NONSECURE_MASK)

#define SRC_AUTHEN_USBPHY1_LOCK_SETTING_MASK     (0x80000000U)
#define SRC_AUTHEN_USBPHY1_LOCK_SETTING_SHIFT    (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_USBPHY1_LOCK_SETTING(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY1_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_USBPHY1_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_USBPHY1 - Slice Control Register */
/*! @{ */

#define SRC_CTRL_USBPHY1_SW_RESET_MASK           (0x1U)
#define SRC_CTRL_USBPHY1_SW_RESET_SHIFT          (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_USBPHY1_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_USBPHY1_SW_RESET_SHIFT)) & SRC_CTRL_USBPHY1_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_USBPHY1 - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_USBPHY1_SETPOINT0_MASK      (0x1U)
#define SRC_SETPOINT_USBPHY1_SETPOINT0_SHIFT     (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT0(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT0_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT0_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT1_MASK      (0x2U)
#define SRC_SETPOINT_USBPHY1_SETPOINT1_SHIFT     (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT1(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT1_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT1_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT2_MASK      (0x4U)
#define SRC_SETPOINT_USBPHY1_SETPOINT2_SHIFT     (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT2(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT2_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT2_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT3_MASK      (0x8U)
#define SRC_SETPOINT_USBPHY1_SETPOINT3_SHIFT     (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT3(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT3_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT3_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT4_MASK      (0x10U)
#define SRC_SETPOINT_USBPHY1_SETPOINT4_SHIFT     (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT4(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT4_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT4_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT5_MASK      (0x20U)
#define SRC_SETPOINT_USBPHY1_SETPOINT5_SHIFT     (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT5(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT5_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT5_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT6_MASK      (0x40U)
#define SRC_SETPOINT_USBPHY1_SETPOINT6_SHIFT     (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT6(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT6_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT6_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT7_MASK      (0x80U)
#define SRC_SETPOINT_USBPHY1_SETPOINT7_SHIFT     (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT7(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT7_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT7_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT8_MASK      (0x100U)
#define SRC_SETPOINT_USBPHY1_SETPOINT8_SHIFT     (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT8(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT8_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT8_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT9_MASK      (0x200U)
#define SRC_SETPOINT_USBPHY1_SETPOINT9_SHIFT     (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT9(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT9_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT9_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT10_MASK     (0x400U)
#define SRC_SETPOINT_USBPHY1_SETPOINT10_SHIFT    (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT10(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT10_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT10_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT11_MASK     (0x800U)
#define SRC_SETPOINT_USBPHY1_SETPOINT11_SHIFT    (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT11(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT11_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT11_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT12_MASK     (0x1000U)
#define SRC_SETPOINT_USBPHY1_SETPOINT12_SHIFT    (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT12(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT12_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT12_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT13_MASK     (0x2000U)
#define SRC_SETPOINT_USBPHY1_SETPOINT13_SHIFT    (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT13(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT13_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT13_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT14_MASK     (0x4000U)
#define SRC_SETPOINT_USBPHY1_SETPOINT14_SHIFT    (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT14(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT14_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT14_MASK)

#define SRC_SETPOINT_USBPHY1_SETPOINT15_MASK     (0x8000U)
#define SRC_SETPOINT_USBPHY1_SETPOINT15_SHIFT    (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY1_SETPOINT15(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY1_SETPOINT15_SHIFT)) & SRC_SETPOINT_USBPHY1_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_USBPHY1 - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_USBPHY1_CPU0_RUN_MASK         (0x1U)
#define SRC_DOMAIN_USBPHY1_CPU0_RUN_SHIFT        (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_USBPHY1_CPU0_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU0_RUN_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU0_RUN_MASK)

#define SRC_DOMAIN_USBPHY1_CPU0_WAIT_MASK        (0x2U)
#define SRC_DOMAIN_USBPHY1_CPU0_WAIT_SHIFT       (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_USBPHY1_CPU0_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU0_WAIT_MASK)

#define SRC_DOMAIN_USBPHY1_CPU0_STOP_MASK        (0x4U)
#define SRC_DOMAIN_USBPHY1_CPU0_STOP_SHIFT       (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_USBPHY1_CPU0_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU0_STOP_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU0_STOP_MASK)

#define SRC_DOMAIN_USBPHY1_CPU0_SUSP_MASK        (0x8U)
#define SRC_DOMAIN_USBPHY1_CPU0_SUSP_SHIFT       (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_USBPHY1_CPU0_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU0_SUSP_MASK)

#define SRC_DOMAIN_USBPHY1_CPU1_RUN_MASK         (0x10U)
#define SRC_DOMAIN_USBPHY1_CPU1_RUN_SHIFT        (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_USBPHY1_CPU1_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU1_RUN_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU1_RUN_MASK)

#define SRC_DOMAIN_USBPHY1_CPU1_WAIT_MASK        (0x20U)
#define SRC_DOMAIN_USBPHY1_CPU1_WAIT_SHIFT       (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_USBPHY1_CPU1_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU1_WAIT_MASK)

#define SRC_DOMAIN_USBPHY1_CPU1_STOP_MASK        (0x40U)
#define SRC_DOMAIN_USBPHY1_CPU1_STOP_SHIFT       (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_USBPHY1_CPU1_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU1_STOP_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU1_STOP_MASK)

#define SRC_DOMAIN_USBPHY1_CPU1_SUSP_MASK        (0x80U)
#define SRC_DOMAIN_USBPHY1_CPU1_SUSP_SHIFT       (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_USBPHY1_CPU1_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY1_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_USBPHY1_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_USBPHY1 - Slice Status Register */
/*! @{ */

#define SRC_STAT_USBPHY1_UNDER_RST_MASK          (0x1U)
#define SRC_STAT_USBPHY1_UNDER_RST_SHIFT         (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_USBPHY1_UNDER_RST(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_USBPHY1_UNDER_RST_SHIFT)) & SRC_STAT_USBPHY1_UNDER_RST_MASK)

#define SRC_STAT_USBPHY1_RST_BY_HW_MASK          (0x4U)
#define SRC_STAT_USBPHY1_RST_BY_HW_SHIFT         (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_USBPHY1_RST_BY_HW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_USBPHY1_RST_BY_HW_SHIFT)) & SRC_STAT_USBPHY1_RST_BY_HW_MASK)

#define SRC_STAT_USBPHY1_RST_BY_SW_MASK          (0x8U)
#define SRC_STAT_USBPHY1_RST_BY_SW_SHIFT         (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_USBPHY1_RST_BY_SW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_USBPHY1_RST_BY_SW_SHIFT)) & SRC_STAT_USBPHY1_RST_BY_SW_MASK)
/*! @} */

/*! @name AUTHEN_USBPHY2 - Slice Authentication Register */
/*! @{ */

#define SRC_AUTHEN_USBPHY2_DOMAIN_MODE_MASK      (0x1U)
#define SRC_AUTHEN_USBPHY2_DOMAIN_MODE_SHIFT     (0U)
/*! DOMAIN_MODE
 *  0b0..slice hardware reset will NOT be triggered by CPU power mode transition
 *  0b1..slice hardware reset will be triggered by CPU power mode transition. Do not set this bit and SETPOINT_MODE at the same time.
 */
#define SRC_AUTHEN_USBPHY2_DOMAIN_MODE(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_DOMAIN_MODE_SHIFT)) & SRC_AUTHEN_USBPHY2_DOMAIN_MODE_MASK)

#define SRC_AUTHEN_USBPHY2_SETPOINT_MODE_MASK    (0x2U)
#define SRC_AUTHEN_USBPHY2_SETPOINT_MODE_SHIFT   (1U)
/*! SETPOINT_MODE
 *  0b0..slice hardware reset will NOT be triggered by Setpoint transition
 *  0b1..slice hardware reset will be triggered by Setpoint transition. Do not set this bit and DOMAIN_MODE at the same time.
 */
#define SRC_AUTHEN_USBPHY2_SETPOINT_MODE(x)      (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_SETPOINT_MODE_SHIFT)) & SRC_AUTHEN_USBPHY2_SETPOINT_MODE_MASK)

#define SRC_AUTHEN_USBPHY2_LOCK_MODE_MASK        (0x80U)
#define SRC_AUTHEN_USBPHY2_LOCK_MODE_SHIFT       (7U)
/*! LOCK_MODE - Domain/Setpoint mode lock */
#define SRC_AUTHEN_USBPHY2_LOCK_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_LOCK_MODE_SHIFT)) & SRC_AUTHEN_USBPHY2_LOCK_MODE_MASK)

#define SRC_AUTHEN_USBPHY2_ASSIGN_LIST_MASK      (0xF00U)
#define SRC_AUTHEN_USBPHY2_ASSIGN_LIST_SHIFT     (8U)
#define SRC_AUTHEN_USBPHY2_ASSIGN_LIST(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_ASSIGN_LIST_SHIFT)) & SRC_AUTHEN_USBPHY2_ASSIGN_LIST_MASK)

#define SRC_AUTHEN_USBPHY2_LOCK_ASSIGN_MASK      (0x8000U)
#define SRC_AUTHEN_USBPHY2_LOCK_ASSIGN_SHIFT     (15U)
/*! LOCK_ASSIGN - Assign list lock */
#define SRC_AUTHEN_USBPHY2_LOCK_ASSIGN(x)        (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_LOCK_ASSIGN_SHIFT)) & SRC_AUTHEN_USBPHY2_LOCK_ASSIGN_MASK)

#define SRC_AUTHEN_USBPHY2_WHITE_LIST_MASK       (0xF0000U)
#define SRC_AUTHEN_USBPHY2_WHITE_LIST_SHIFT      (16U)
/*! WHITE_LIST - Domain ID white list */
#define SRC_AUTHEN_USBPHY2_WHITE_LIST(x)         (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_WHITE_LIST_SHIFT)) & SRC_AUTHEN_USBPHY2_WHITE_LIST_MASK)

#define SRC_AUTHEN_USBPHY2_LOCK_LIST_MASK        (0x800000U)
#define SRC_AUTHEN_USBPHY2_LOCK_LIST_SHIFT       (23U)
/*! LOCK_LIST - White list lock */
#define SRC_AUTHEN_USBPHY2_LOCK_LIST(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_LOCK_LIST_SHIFT)) & SRC_AUTHEN_USBPHY2_LOCK_LIST_MASK)

#define SRC_AUTHEN_USBPHY2_USER_MASK             (0x1000000U)
#define SRC_AUTHEN_USBPHY2_USER_SHIFT            (24U)
/*! USER - Allow user mode access */
#define SRC_AUTHEN_USBPHY2_USER(x)               (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_USER_SHIFT)) & SRC_AUTHEN_USBPHY2_USER_MASK)

#define SRC_AUTHEN_USBPHY2_NONSECURE_MASK        (0x2000000U)
#define SRC_AUTHEN_USBPHY2_NONSECURE_SHIFT       (25U)
/*! NONSECURE - Allow non-secure mode access */
#define SRC_AUTHEN_USBPHY2_NONSECURE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_NONSECURE_SHIFT)) & SRC_AUTHEN_USBPHY2_NONSECURE_MASK)

#define SRC_AUTHEN_USBPHY2_LOCK_SETTING_MASK     (0x80000000U)
#define SRC_AUTHEN_USBPHY2_LOCK_SETTING_SHIFT    (31U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define SRC_AUTHEN_USBPHY2_LOCK_SETTING(x)       (((uint32_t)(((uint32_t)(x)) << SRC_AUTHEN_USBPHY2_LOCK_SETTING_SHIFT)) & SRC_AUTHEN_USBPHY2_LOCK_SETTING_MASK)
/*! @} */

/*! @name CTRL_USBPHY2 - Slice Control Register */
/*! @{ */

#define SRC_CTRL_USBPHY2_SW_RESET_MASK           (0x1U)
#define SRC_CTRL_USBPHY2_SW_RESET_SHIFT          (0U)
/*! SW_RESET
 *  0b0..do not assert slice software reset
 *  0b1..assert slice software reset
 */
#define SRC_CTRL_USBPHY2_SW_RESET(x)             (((uint32_t)(((uint32_t)(x)) << SRC_CTRL_USBPHY2_SW_RESET_SHIFT)) & SRC_CTRL_USBPHY2_SW_RESET_MASK)
/*! @} */

/*! @name SETPOINT_USBPHY2 - Slice Setpoint Config Register */
/*! @{ */

#define SRC_SETPOINT_USBPHY2_SETPOINT0_MASK      (0x1U)
#define SRC_SETPOINT_USBPHY2_SETPOINT0_SHIFT     (0U)
/*! SETPOINT0 - SETPOINT0
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT0(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT0_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT0_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT1_MASK      (0x2U)
#define SRC_SETPOINT_USBPHY2_SETPOINT1_SHIFT     (1U)
/*! SETPOINT1 - SETPOINT1
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT1(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT1_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT1_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT2_MASK      (0x4U)
#define SRC_SETPOINT_USBPHY2_SETPOINT2_SHIFT     (2U)
/*! SETPOINT2 - SETPOINT2
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT2(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT2_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT2_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT3_MASK      (0x8U)
#define SRC_SETPOINT_USBPHY2_SETPOINT3_SHIFT     (3U)
/*! SETPOINT3 - SETPOINT3
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT3(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT3_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT3_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT4_MASK      (0x10U)
#define SRC_SETPOINT_USBPHY2_SETPOINT4_SHIFT     (4U)
/*! SETPOINT4 - SETPOINT4
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT4(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT4_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT4_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT5_MASK      (0x20U)
#define SRC_SETPOINT_USBPHY2_SETPOINT5_SHIFT     (5U)
/*! SETPOINT5 - SETPOINT5
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT5(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT5_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT5_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT6_MASK      (0x40U)
#define SRC_SETPOINT_USBPHY2_SETPOINT6_SHIFT     (6U)
/*! SETPOINT6 - SETPOINT6
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT6(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT6_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT6_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT7_MASK      (0x80U)
#define SRC_SETPOINT_USBPHY2_SETPOINT7_SHIFT     (7U)
/*! SETPOINT7 - SETPOINT7
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT7(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT7_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT7_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT8_MASK      (0x100U)
#define SRC_SETPOINT_USBPHY2_SETPOINT8_SHIFT     (8U)
/*! SETPOINT8 - SETPOINT8
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT8(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT8_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT8_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT9_MASK      (0x200U)
#define SRC_SETPOINT_USBPHY2_SETPOINT9_SHIFT     (9U)
/*! SETPOINT9 - SETPOINT9
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT9(x)        (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT9_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT9_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT10_MASK     (0x400U)
#define SRC_SETPOINT_USBPHY2_SETPOINT10_SHIFT    (10U)
/*! SETPOINT10 - SETPOINT10
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT10(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT10_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT10_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT11_MASK     (0x800U)
#define SRC_SETPOINT_USBPHY2_SETPOINT11_SHIFT    (11U)
/*! SETPOINT11 - SETPOINT11
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT11(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT11_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT11_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT12_MASK     (0x1000U)
#define SRC_SETPOINT_USBPHY2_SETPOINT12_SHIFT    (12U)
/*! SETPOINT12 - SETPOINT12
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT12(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT12_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT12_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT13_MASK     (0x2000U)
#define SRC_SETPOINT_USBPHY2_SETPOINT13_SHIFT    (13U)
/*! SETPOINT13 - SETPOINT13
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT13(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT13_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT13_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT14_MASK     (0x4000U)
#define SRC_SETPOINT_USBPHY2_SETPOINT14_SHIFT    (14U)
/*! SETPOINT14 - SETPOINT14
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT14(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT14_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT14_MASK)

#define SRC_SETPOINT_USBPHY2_SETPOINT15_MASK     (0x8000U)
#define SRC_SETPOINT_USBPHY2_SETPOINT15_SHIFT    (15U)
/*! SETPOINT15 - SETPOINT15
 *  0b0..Slice reset will be de-asserted when system in Setpoint n
 *  0b1..Slice reset will be asserted when system in Setpoint n
 */
#define SRC_SETPOINT_USBPHY2_SETPOINT15(x)       (((uint32_t)(((uint32_t)(x)) << SRC_SETPOINT_USBPHY2_SETPOINT15_SHIFT)) & SRC_SETPOINT_USBPHY2_SETPOINT15_MASK)
/*! @} */

/*! @name DOMAIN_USBPHY2 - Slice Domain Config Register */
/*! @{ */

#define SRC_DOMAIN_USBPHY2_CPU0_RUN_MASK         (0x1U)
#define SRC_DOMAIN_USBPHY2_CPU0_RUN_SHIFT        (0U)
/*! CPU0_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU0 in RUN mode
 *  0b1..Slice reset will be asserted when CPU0 in RUN mode
 */
#define SRC_DOMAIN_USBPHY2_CPU0_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU0_RUN_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU0_RUN_MASK)

#define SRC_DOMAIN_USBPHY2_CPU0_WAIT_MASK        (0x2U)
#define SRC_DOMAIN_USBPHY2_CPU0_WAIT_SHIFT       (1U)
/*! CPU0_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU0 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU0 in WAIT mode
 */
#define SRC_DOMAIN_USBPHY2_CPU0_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU0_WAIT_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU0_WAIT_MASK)

#define SRC_DOMAIN_USBPHY2_CPU0_STOP_MASK        (0x4U)
#define SRC_DOMAIN_USBPHY2_CPU0_STOP_SHIFT       (2U)
/*! CPU0_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU0 in STOP mode
 *  0b1..Slice reset will be asserted when CPU0 in STOP mode
 */
#define SRC_DOMAIN_USBPHY2_CPU0_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU0_STOP_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU0_STOP_MASK)

#define SRC_DOMAIN_USBPHY2_CPU0_SUSP_MASK        (0x8U)
#define SRC_DOMAIN_USBPHY2_CPU0_SUSP_SHIFT       (3U)
/*! CPU0_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU0 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU0 in SUSPEND mode
 */
#define SRC_DOMAIN_USBPHY2_CPU0_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU0_SUSP_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU0_SUSP_MASK)

#define SRC_DOMAIN_USBPHY2_CPU1_RUN_MASK         (0x10U)
#define SRC_DOMAIN_USBPHY2_CPU1_RUN_SHIFT        (4U)
/*! CPU1_RUN - CPU mode setting for RUN
 *  0b0..Slice reset will be de-asserted when CPU1 in RUN mode
 *  0b1..Slice reset will be asserted when CPU1 in RUN mode
 */
#define SRC_DOMAIN_USBPHY2_CPU1_RUN(x)           (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU1_RUN_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU1_RUN_MASK)

#define SRC_DOMAIN_USBPHY2_CPU1_WAIT_MASK        (0x20U)
#define SRC_DOMAIN_USBPHY2_CPU1_WAIT_SHIFT       (5U)
/*! CPU1_WAIT - CPU mode setting for WAIT
 *  0b0..Slice reset will be de-asserted when CPU1 in WAIT mode
 *  0b1..Slice reset will be asserted when CPU1 in WAIT mode
 */
#define SRC_DOMAIN_USBPHY2_CPU1_WAIT(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU1_WAIT_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU1_WAIT_MASK)

#define SRC_DOMAIN_USBPHY2_CPU1_STOP_MASK        (0x40U)
#define SRC_DOMAIN_USBPHY2_CPU1_STOP_SHIFT       (6U)
/*! CPU1_STOP - CPU mode setting for STOP
 *  0b0..Slice reset will be de-asserted when CPU1 in STOP mode
 *  0b1..Slice reset will be asserted when CPU1 in STOP mode
 */
#define SRC_DOMAIN_USBPHY2_CPU1_STOP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU1_STOP_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU1_STOP_MASK)

#define SRC_DOMAIN_USBPHY2_CPU1_SUSP_MASK        (0x80U)
#define SRC_DOMAIN_USBPHY2_CPU1_SUSP_SHIFT       (7U)
/*! CPU1_SUSP - CPU mode setting for SUSPEND
 *  0b0..Slice reset will be de-asserted when CPU1 in SUSPEND mode
 *  0b1..Slice reset will be asserted when CPU1 in SUSPEND mode
 */
#define SRC_DOMAIN_USBPHY2_CPU1_SUSP(x)          (((uint32_t)(((uint32_t)(x)) << SRC_DOMAIN_USBPHY2_CPU1_SUSP_SHIFT)) & SRC_DOMAIN_USBPHY2_CPU1_SUSP_MASK)
/*! @} */

/*! @name STAT_USBPHY2 - Slice Status Register */
/*! @{ */

#define SRC_STAT_USBPHY2_UNDER_RST_MASK          (0x1U)
#define SRC_STAT_USBPHY2_UNDER_RST_SHIFT         (0U)
/*! UNDER_RST
 *  0b0..the reset is finished
 *  0b1..the reset is in process
 */
#define SRC_STAT_USBPHY2_UNDER_RST(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_USBPHY2_UNDER_RST_SHIFT)) & SRC_STAT_USBPHY2_UNDER_RST_MASK)

#define SRC_STAT_USBPHY2_RST_BY_HW_MASK          (0x4U)
#define SRC_STAT_USBPHY2_RST_BY_HW_SHIFT         (2U)
/*! RST_BY_HW
 *  0b0..the reset is not caused by the power mode transfer
 *  0b1..the reset is caused by the power mode transfer
 */
#define SRC_STAT_USBPHY2_RST_BY_HW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_USBPHY2_RST_BY_HW_SHIFT)) & SRC_STAT_USBPHY2_RST_BY_HW_MASK)

#define SRC_STAT_USBPHY2_RST_BY_SW_MASK          (0x8U)
#define SRC_STAT_USBPHY2_RST_BY_SW_SHIFT         (3U)
/*! RST_BY_SW
 *  0b0..the reset is not caused by software setting
 *  0b1..the reset is caused by software setting
 */
#define SRC_STAT_USBPHY2_RST_BY_SW(x)            (((uint32_t)(((uint32_t)(x)) << SRC_STAT_USBPHY2_RST_BY_SW_SHIFT)) & SRC_STAT_USBPHY2_RST_BY_SW_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SRC_Register_Masks */


/*!
 * @}
 */ /* end of group SRC_Peripheral_Access_Layer */


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


#endif  /* PERI_SRC_H_ */

