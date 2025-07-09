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
**         CMSIS Peripheral Access Layer for USBPHY
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
 * @file PERI_USBPHY.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for USBPHY
 *
 * CMSIS Peripheral Access Layer for USBPHY
 */

#if !defined(PERI_USBPHY_H_)
#define PERI_USBPHY_H_                           /**< Symbol preventing repeated inclusion */

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
   -- USBPHY Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBPHY_Peripheral_Access_Layer USBPHY Peripheral Access Layer
 * @{
 */

/** USBPHY - Register Layout Typedef */
typedef struct {
  __IO uint32_t PWD;                               /**< USB PHY Power-Down Register, offset: 0x0 */
  __IO uint32_t PWD_SET;                           /**< USB PHY Power-Down Register, offset: 0x4 */
  __IO uint32_t PWD_CLR;                           /**< USB PHY Power-Down Register, offset: 0x8 */
  __IO uint32_t PWD_TOG;                           /**< USB PHY Power-Down Register, offset: 0xC */
  __IO uint32_t TX;                                /**< USB PHY Transmitter Control Register, offset: 0x10 */
  __IO uint32_t TX_SET;                            /**< USB PHY Transmitter Control Register, offset: 0x14 */
  __IO uint32_t TX_CLR;                            /**< USB PHY Transmitter Control Register, offset: 0x18 */
  __IO uint32_t TX_TOG;                            /**< USB PHY Transmitter Control Register, offset: 0x1C */
  __IO uint32_t RX;                                /**< USB PHY Receiver Control Register, offset: 0x20 */
  __IO uint32_t RX_SET;                            /**< USB PHY Receiver Control Register, offset: 0x24 */
  __IO uint32_t RX_CLR;                            /**< USB PHY Receiver Control Register, offset: 0x28 */
  __IO uint32_t RX_TOG;                            /**< USB PHY Receiver Control Register, offset: 0x2C */
  __IO uint32_t CTRL;                              /**< USB PHY General Control Register, offset: 0x30 */
  __IO uint32_t CTRL_SET;                          /**< USB PHY General Control Register, offset: 0x34 */
  __IO uint32_t CTRL_CLR;                          /**< USB PHY General Control Register, offset: 0x38 */
  __IO uint32_t CTRL_TOG;                          /**< USB PHY General Control Register, offset: 0x3C */
  __IO uint32_t STATUS;                            /**< USB PHY Status Register, offset: 0x40 */
       uint8_t RESERVED_0[12];
  __IO uint32_t DEBUGr;                            /**< USB PHY Debug Register, offset: 0x50, 'r' suffix has been added to avoid clash with DEBUG symbolic constant */
  __IO uint32_t DEBUG_SET;                         /**< USB PHY Debug Register, offset: 0x54 */
  __IO uint32_t DEBUG_CLR;                         /**< USB PHY Debug Register, offset: 0x58 */
  __IO uint32_t DEBUG_TOG;                         /**< USB PHY Debug Register, offset: 0x5C */
  __I  uint32_t DEBUG0_STATUS;                     /**< UTMI Debug Status Register 0, offset: 0x60 */
       uint8_t RESERVED_1[12];
  __IO uint32_t DEBUG1;                            /**< UTMI Debug Status Register 1, offset: 0x70 */
  __IO uint32_t DEBUG1_SET;                        /**< UTMI Debug Status Register 1, offset: 0x74 */
  __IO uint32_t DEBUG1_CLR;                        /**< UTMI Debug Status Register 1, offset: 0x78 */
  __IO uint32_t DEBUG1_TOG;                        /**< UTMI Debug Status Register 1, offset: 0x7C */
  __I  uint32_t VERSION;                           /**< UTMI RTL Version, offset: 0x80 */
       uint8_t RESERVED_2[28];
  __IO uint32_t PLL_SIC;                           /**< USB PHY PLL Control/Status Register, offset: 0xA0 */
  __IO uint32_t PLL_SIC_SET;                       /**< USB PHY PLL Control/Status Register, offset: 0xA4 */
  __IO uint32_t PLL_SIC_CLR;                       /**< USB PHY PLL Control/Status Register, offset: 0xA8 */
  __IO uint32_t PLL_SIC_TOG;                       /**< USB PHY PLL Control/Status Register, offset: 0xAC */
       uint8_t RESERVED_3[16];
  __IO uint32_t USB1_VBUS_DETECT;                  /**< USB PHY VBUS Detect Control Register, offset: 0xC0 */
  __IO uint32_t USB1_VBUS_DETECT_SET;              /**< USB PHY VBUS Detect Control Register, offset: 0xC4 */
  __IO uint32_t USB1_VBUS_DETECT_CLR;              /**< USB PHY VBUS Detect Control Register, offset: 0xC8 */
  __IO uint32_t USB1_VBUS_DETECT_TOG;              /**< USB PHY VBUS Detect Control Register, offset: 0xCC */
  __I  uint32_t USB1_VBUS_DET_STAT;                /**< USB PHY VBUS Detector Status Register, offset: 0xD0 */
       uint8_t RESERVED_4[12];
  __IO uint32_t USB1_CHRG_DETECT;                  /**< USB PHY Charger Detect Control Register, offset: 0xE0 */
  __IO uint32_t USB1_CHRG_DETECT_SET;              /**< USB PHY Charger Detect Control Register, offset: 0xE4 */
  __IO uint32_t USB1_CHRG_DETECT_CLR;              /**< USB PHY Charger Detect Control Register, offset: 0xE8 */
  __IO uint32_t USB1_CHRG_DETECT_TOG;              /**< USB PHY Charger Detect Control Register, offset: 0xEC */
  __I  uint32_t USB1_CHRG_DET_STAT;                /**< USB PHY Charger Detect Status Register, offset: 0xF0 */
       uint8_t RESERVED_5[12];
  __IO uint32_t ANACTRL;                           /**< USB PHY Analog Control Register, offset: 0x100 */
  __IO uint32_t ANACTRL_SET;                       /**< USB PHY Analog Control Register, offset: 0x104 */
  __IO uint32_t ANACTRL_CLR;                       /**< USB PHY Analog Control Register, offset: 0x108 */
  __IO uint32_t ANACTRL_TOG;                       /**< USB PHY Analog Control Register, offset: 0x10C */
  __IO uint32_t USB1_LOOPBACK;                     /**< USB PHY Loopback Control/Status Register, offset: 0x110 */
  __IO uint32_t USB1_LOOPBACK_SET;                 /**< USB PHY Loopback Control/Status Register, offset: 0x114 */
  __IO uint32_t USB1_LOOPBACK_CLR;                 /**< USB PHY Loopback Control/Status Register, offset: 0x118 */
  __IO uint32_t USB1_LOOPBACK_TOG;                 /**< USB PHY Loopback Control/Status Register, offset: 0x11C */
  __IO uint32_t USB1_LOOPBACK_HSFSCNT;             /**< USB PHY Loopback Packet Number Select Register, offset: 0x120 */
  __IO uint32_t USB1_LOOPBACK_HSFSCNT_SET;         /**< USB PHY Loopback Packet Number Select Register, offset: 0x124 */
  __IO uint32_t USB1_LOOPBACK_HSFSCNT_CLR;         /**< USB PHY Loopback Packet Number Select Register, offset: 0x128 */
  __IO uint32_t USB1_LOOPBACK_HSFSCNT_TOG;         /**< USB PHY Loopback Packet Number Select Register, offset: 0x12C */
  __IO uint32_t TRIM_OVERRIDE_EN;                  /**< USB PHY Trim Override Enable Register, offset: 0x130 */
  __IO uint32_t TRIM_OVERRIDE_EN_SET;              /**< USB PHY Trim Override Enable Register, offset: 0x134 */
  __IO uint32_t TRIM_OVERRIDE_EN_CLR;              /**< USB PHY Trim Override Enable Register, offset: 0x138 */
  __IO uint32_t TRIM_OVERRIDE_EN_TOG;              /**< USB PHY Trim Override Enable Register, offset: 0x13C */
} USBPHY_Type;

/* ----------------------------------------------------------------------------
   -- USBPHY Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBPHY_Register_Masks USBPHY Register Masks
 * @{
 */

/*! @name PWD - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_TXPWDFS_MASK                  (0x400U)
#define USBPHY_PWD_TXPWDFS_SHIFT                 (10U)
/*! TXPWDFS - TXPWDFS
 *  0b0..Normal operation.
 *  0b1..Power-down the USB full-speed drivers. This turns off the current starvation sources and puts the drivers into high-impedance output
 */
#define USBPHY_PWD_TXPWDFS(x)                    (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TXPWDFS_SHIFT)) & USBPHY_PWD_TXPWDFS_MASK)

#define USBPHY_PWD_TXPWDIBIAS_MASK               (0x800U)
#define USBPHY_PWD_TXPWDIBIAS_SHIFT              (11U)
/*! TXPWDIBIAS - TXPWDIBIAS
 *  0b0..Normal operation
 *  0b1..Power-down the USB PHY current bias block for the transmitter. This bit should be set only when the USB
 *       is in suspend mode. This effectively powers down the entire USB transmit path
 */
#define USBPHY_PWD_TXPWDIBIAS(x)                 (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_TXPWDIBIAS_MASK)

#define USBPHY_PWD_TXPWDV2I_MASK                 (0x1000U)
#define USBPHY_PWD_TXPWDV2I_SHIFT                (12U)
/*! TXPWDV2I - TXPWDV2I
 *  0b0..Normal operation.
 *  0b1..Power-down the USB PHY transmit V-to-I converter and the current mirror
 */
#define USBPHY_PWD_TXPWDV2I(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TXPWDV2I_SHIFT)) & USBPHY_PWD_TXPWDV2I_MASK)

#define USBPHY_PWD_RXPWDENV_MASK                 (0x20000U)
#define USBPHY_PWD_RXPWDENV_SHIFT                (17U)
/*! RXPWDENV - RXPWDENV
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed receiver envelope detector (squelch signal)
 */
#define USBPHY_PWD_RXPWDENV(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWDENV_SHIFT)) & USBPHY_PWD_RXPWDENV_MASK)

#define USBPHY_PWD_RXPWD1PT1_MASK                (0x40000U)
#define USBPHY_PWD_RXPWD1PT1_SHIFT               (18U)
/*! RXPWD1PT1 - RXPWD1PT1
 *  0b0..Normal operation
 *  0b1..Power-down the USB full-speed differential receiver.
 */
#define USBPHY_PWD_RXPWD1PT1(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWD1PT1_SHIFT)) & USBPHY_PWD_RXPWD1PT1_MASK)

#define USBPHY_PWD_RXPWDDIFF_MASK                (0x80000U)
#define USBPHY_PWD_RXPWDDIFF_SHIFT               (19U)
/*! RXPWDDIFF - RXPWDDIFF
 *  0b0..Normal operation.
 *  0b1..Power-down the USB high-speed differential receiver
 */
#define USBPHY_PWD_RXPWDDIFF(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWDDIFF_SHIFT)) & USBPHY_PWD_RXPWDDIFF_MASK)

#define USBPHY_PWD_RXPWDRX_MASK                  (0x100000U)
#define USBPHY_PWD_RXPWDRX_SHIFT                 (20U)
/*! RXPWDRX - RXPWDRX
 *  0b0..Normal operation
 *  0b1..Power-down the entire USB PHY receiver block except for the full-speed differential receiver
 */
#define USBPHY_PWD_RXPWDRX(x)                    (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_RXPWDRX_SHIFT)) & USBPHY_PWD_RXPWDRX_MASK)
/*! @} */

/*! @name PWD_SET - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_SET_TXPWDFS_MASK              (0x400U)
#define USBPHY_PWD_SET_TXPWDFS_SHIFT             (10U)
/*! TXPWDFS - TXPWDFS */
#define USBPHY_PWD_SET_TXPWDFS(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_TXPWDFS_SHIFT)) & USBPHY_PWD_SET_TXPWDFS_MASK)

#define USBPHY_PWD_SET_TXPWDIBIAS_MASK           (0x800U)
#define USBPHY_PWD_SET_TXPWDIBIAS_SHIFT          (11U)
/*! TXPWDIBIAS - TXPWDIBIAS */
#define USBPHY_PWD_SET_TXPWDIBIAS(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_SET_TXPWDIBIAS_MASK)

#define USBPHY_PWD_SET_TXPWDV2I_MASK             (0x1000U)
#define USBPHY_PWD_SET_TXPWDV2I_SHIFT            (12U)
/*! TXPWDV2I - TXPWDV2I */
#define USBPHY_PWD_SET_TXPWDV2I(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_TXPWDV2I_SHIFT)) & USBPHY_PWD_SET_TXPWDV2I_MASK)

#define USBPHY_PWD_SET_RXPWDENV_MASK             (0x20000U)
#define USBPHY_PWD_SET_RXPWDENV_SHIFT            (17U)
/*! RXPWDENV - RXPWDENV */
#define USBPHY_PWD_SET_RXPWDENV(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWDENV_SHIFT)) & USBPHY_PWD_SET_RXPWDENV_MASK)

#define USBPHY_PWD_SET_RXPWD1PT1_MASK            (0x40000U)
#define USBPHY_PWD_SET_RXPWD1PT1_SHIFT           (18U)
/*! RXPWD1PT1 - RXPWD1PT1 */
#define USBPHY_PWD_SET_RXPWD1PT1(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWD1PT1_SHIFT)) & USBPHY_PWD_SET_RXPWD1PT1_MASK)

#define USBPHY_PWD_SET_RXPWDDIFF_MASK            (0x80000U)
#define USBPHY_PWD_SET_RXPWDDIFF_SHIFT           (19U)
/*! RXPWDDIFF - RXPWDDIFF */
#define USBPHY_PWD_SET_RXPWDDIFF(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWDDIFF_SHIFT)) & USBPHY_PWD_SET_RXPWDDIFF_MASK)

#define USBPHY_PWD_SET_RXPWDRX_MASK              (0x100000U)
#define USBPHY_PWD_SET_RXPWDRX_SHIFT             (20U)
/*! RXPWDRX - RXPWDRX */
#define USBPHY_PWD_SET_RXPWDRX(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_SET_RXPWDRX_SHIFT)) & USBPHY_PWD_SET_RXPWDRX_MASK)
/*! @} */

/*! @name PWD_CLR - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_CLR_TXPWDFS_MASK              (0x400U)
#define USBPHY_PWD_CLR_TXPWDFS_SHIFT             (10U)
/*! TXPWDFS - TXPWDFS */
#define USBPHY_PWD_CLR_TXPWDFS(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_TXPWDFS_SHIFT)) & USBPHY_PWD_CLR_TXPWDFS_MASK)

#define USBPHY_PWD_CLR_TXPWDIBIAS_MASK           (0x800U)
#define USBPHY_PWD_CLR_TXPWDIBIAS_SHIFT          (11U)
/*! TXPWDIBIAS - TXPWDIBIAS */
#define USBPHY_PWD_CLR_TXPWDIBIAS(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_CLR_TXPWDIBIAS_MASK)

#define USBPHY_PWD_CLR_TXPWDV2I_MASK             (0x1000U)
#define USBPHY_PWD_CLR_TXPWDV2I_SHIFT            (12U)
/*! TXPWDV2I - TXPWDV2I */
#define USBPHY_PWD_CLR_TXPWDV2I(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_TXPWDV2I_SHIFT)) & USBPHY_PWD_CLR_TXPWDV2I_MASK)

#define USBPHY_PWD_CLR_RXPWDENV_MASK             (0x20000U)
#define USBPHY_PWD_CLR_RXPWDENV_SHIFT            (17U)
/*! RXPWDENV - RXPWDENV */
#define USBPHY_PWD_CLR_RXPWDENV(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWDENV_SHIFT)) & USBPHY_PWD_CLR_RXPWDENV_MASK)

#define USBPHY_PWD_CLR_RXPWD1PT1_MASK            (0x40000U)
#define USBPHY_PWD_CLR_RXPWD1PT1_SHIFT           (18U)
/*! RXPWD1PT1 - RXPWD1PT1 */
#define USBPHY_PWD_CLR_RXPWD1PT1(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWD1PT1_SHIFT)) & USBPHY_PWD_CLR_RXPWD1PT1_MASK)

#define USBPHY_PWD_CLR_RXPWDDIFF_MASK            (0x80000U)
#define USBPHY_PWD_CLR_RXPWDDIFF_SHIFT           (19U)
/*! RXPWDDIFF - RXPWDDIFF */
#define USBPHY_PWD_CLR_RXPWDDIFF(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWDDIFF_SHIFT)) & USBPHY_PWD_CLR_RXPWDDIFF_MASK)

#define USBPHY_PWD_CLR_RXPWDRX_MASK              (0x100000U)
#define USBPHY_PWD_CLR_RXPWDRX_SHIFT             (20U)
/*! RXPWDRX - RXPWDRX */
#define USBPHY_PWD_CLR_RXPWDRX(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_CLR_RXPWDRX_SHIFT)) & USBPHY_PWD_CLR_RXPWDRX_MASK)
/*! @} */

/*! @name PWD_TOG - USB PHY Power-Down Register */
/*! @{ */

#define USBPHY_PWD_TOG_TXPWDFS_MASK              (0x400U)
#define USBPHY_PWD_TOG_TXPWDFS_SHIFT             (10U)
/*! TXPWDFS - TXPWDFS */
#define USBPHY_PWD_TOG_TXPWDFS(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_TXPWDFS_SHIFT)) & USBPHY_PWD_TOG_TXPWDFS_MASK)

#define USBPHY_PWD_TOG_TXPWDIBIAS_MASK           (0x800U)
#define USBPHY_PWD_TOG_TXPWDIBIAS_SHIFT          (11U)
/*! TXPWDIBIAS - TXPWDIBIAS */
#define USBPHY_PWD_TOG_TXPWDIBIAS(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_TXPWDIBIAS_SHIFT)) & USBPHY_PWD_TOG_TXPWDIBIAS_MASK)

#define USBPHY_PWD_TOG_TXPWDV2I_MASK             (0x1000U)
#define USBPHY_PWD_TOG_TXPWDV2I_SHIFT            (12U)
/*! TXPWDV2I - TXPWDV2I */
#define USBPHY_PWD_TOG_TXPWDV2I(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_TXPWDV2I_SHIFT)) & USBPHY_PWD_TOG_TXPWDV2I_MASK)

#define USBPHY_PWD_TOG_RXPWDENV_MASK             (0x20000U)
#define USBPHY_PWD_TOG_RXPWDENV_SHIFT            (17U)
/*! RXPWDENV - RXPWDENV */
#define USBPHY_PWD_TOG_RXPWDENV(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWDENV_SHIFT)) & USBPHY_PWD_TOG_RXPWDENV_MASK)

#define USBPHY_PWD_TOG_RXPWD1PT1_MASK            (0x40000U)
#define USBPHY_PWD_TOG_RXPWD1PT1_SHIFT           (18U)
/*! RXPWD1PT1 - RXPWD1PT1 */
#define USBPHY_PWD_TOG_RXPWD1PT1(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWD1PT1_SHIFT)) & USBPHY_PWD_TOG_RXPWD1PT1_MASK)

#define USBPHY_PWD_TOG_RXPWDDIFF_MASK            (0x80000U)
#define USBPHY_PWD_TOG_RXPWDDIFF_SHIFT           (19U)
/*! RXPWDDIFF - RXPWDDIFF */
#define USBPHY_PWD_TOG_RXPWDDIFF(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWDDIFF_SHIFT)) & USBPHY_PWD_TOG_RXPWDDIFF_MASK)

#define USBPHY_PWD_TOG_RXPWDRX_MASK              (0x100000U)
#define USBPHY_PWD_TOG_RXPWDRX_SHIFT             (20U)
/*! RXPWDRX - RXPWDRX */
#define USBPHY_PWD_TOG_RXPWDRX(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_PWD_TOG_RXPWDRX_SHIFT)) & USBPHY_PWD_TOG_RXPWDRX_MASK)
/*! @} */

/*! @name TX - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_D_CAL_MASK                     (0xFU)
#define USBPHY_TX_D_CAL_SHIFT                    (0U)
/*! D_CAL - D_CAL
 *  0b0000..Maximum current, approximately 19% above nominal.
 *  0b0111..Nominal
 *  0b1111..Minimum current, approximately 19% below nominal.
 */
#define USBPHY_TX_D_CAL(x)                       (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_D_CAL_SHIFT)) & USBPHY_TX_D_CAL_MASK)

#define USBPHY_TX_TXCAL45DN_MASK                 (0xF00U)
#define USBPHY_TX_TXCAL45DN_SHIFT                (8U)
/*! TXCAL45DN - TXCAL45DN */
#define USBPHY_TX_TXCAL45DN(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TXCAL45DN_SHIFT)) & USBPHY_TX_TXCAL45DN_MASK)

#define USBPHY_TX_TXCAL45DP_MASK                 (0xF0000U)
#define USBPHY_TX_TXCAL45DP_SHIFT                (16U)
/*! TXCAL45DP - TXCAL45DP */
#define USBPHY_TX_TXCAL45DP(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TXCAL45DP_SHIFT)) & USBPHY_TX_TXCAL45DP_MASK)
/*! @} */

/*! @name TX_SET - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_SET_D_CAL_MASK                 (0xFU)
#define USBPHY_TX_SET_D_CAL_SHIFT                (0U)
/*! D_CAL - D_CAL */
#define USBPHY_TX_SET_D_CAL(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_D_CAL_SHIFT)) & USBPHY_TX_SET_D_CAL_MASK)

#define USBPHY_TX_SET_TXCAL45DN_MASK             (0xF00U)
#define USBPHY_TX_SET_TXCAL45DN_SHIFT            (8U)
/*! TXCAL45DN - TXCAL45DN */
#define USBPHY_TX_SET_TXCAL45DN(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_TXCAL45DN_SHIFT)) & USBPHY_TX_SET_TXCAL45DN_MASK)

#define USBPHY_TX_SET_TXCAL45DP_MASK             (0xF0000U)
#define USBPHY_TX_SET_TXCAL45DP_SHIFT            (16U)
/*! TXCAL45DP - TXCAL45DP */
#define USBPHY_TX_SET_TXCAL45DP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_SET_TXCAL45DP_SHIFT)) & USBPHY_TX_SET_TXCAL45DP_MASK)
/*! @} */

/*! @name TX_CLR - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_CLR_D_CAL_MASK                 (0xFU)
#define USBPHY_TX_CLR_D_CAL_SHIFT                (0U)
/*! D_CAL - D_CAL */
#define USBPHY_TX_CLR_D_CAL(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_D_CAL_SHIFT)) & USBPHY_TX_CLR_D_CAL_MASK)

#define USBPHY_TX_CLR_TXCAL45DN_MASK             (0xF00U)
#define USBPHY_TX_CLR_TXCAL45DN_SHIFT            (8U)
/*! TXCAL45DN - TXCAL45DN */
#define USBPHY_TX_CLR_TXCAL45DN(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_TXCAL45DN_SHIFT)) & USBPHY_TX_CLR_TXCAL45DN_MASK)

#define USBPHY_TX_CLR_TXCAL45DP_MASK             (0xF0000U)
#define USBPHY_TX_CLR_TXCAL45DP_SHIFT            (16U)
/*! TXCAL45DP - TXCAL45DP */
#define USBPHY_TX_CLR_TXCAL45DP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_CLR_TXCAL45DP_SHIFT)) & USBPHY_TX_CLR_TXCAL45DP_MASK)
/*! @} */

/*! @name TX_TOG - USB PHY Transmitter Control Register */
/*! @{ */

#define USBPHY_TX_TOG_D_CAL_MASK                 (0xFU)
#define USBPHY_TX_TOG_D_CAL_SHIFT                (0U)
/*! D_CAL - D_CAL */
#define USBPHY_TX_TOG_D_CAL(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_D_CAL_SHIFT)) & USBPHY_TX_TOG_D_CAL_MASK)

#define USBPHY_TX_TOG_TXCAL45DN_MASK             (0xF00U)
#define USBPHY_TX_TOG_TXCAL45DN_SHIFT            (8U)
/*! TXCAL45DN - TXCAL45DN */
#define USBPHY_TX_TOG_TXCAL45DN(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_TXCAL45DN_SHIFT)) & USBPHY_TX_TOG_TXCAL45DN_MASK)

#define USBPHY_TX_TOG_TXCAL45DP_MASK             (0xF0000U)
#define USBPHY_TX_TOG_TXCAL45DP_SHIFT            (16U)
/*! TXCAL45DP - TXCAL45DP */
#define USBPHY_TX_TOG_TXCAL45DP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_TX_TOG_TXCAL45DP_SHIFT)) & USBPHY_TX_TOG_TXCAL45DP_MASK)
/*! @} */

/*! @name RX - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_ENVADJ_MASK                    (0x7U)
#define USBPHY_RX_ENVADJ_SHIFT                   (0U)
/*! ENVADJ - ENVADJ
 *  0b000..Trip-Level Voltage is 0.1000 V
 *  0b001..Trip-Level Voltage is 0.1125 V
 *  0b010..Trip-Level Voltage is 0.1250 V
 *  0b011..Trip-Level Voltage is 0.0875 V
 *  0b1xx..Reserved
 */
#define USBPHY_RX_ENVADJ(x)                      (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_ENVADJ_SHIFT)) & USBPHY_RX_ENVADJ_MASK)

#define USBPHY_RX_DISCONADJ_MASK                 (0x70U)
#define USBPHY_RX_DISCONADJ_SHIFT                (4U)
/*! DISCONADJ - DISCONADJ
 *  0b000..Trip-Level Voltage is 0.56875 V
 *  0b001..Trip-Level Voltage is 0.55000 V
 *  0b010..Trip-Level Voltage is 0.58125 V
 *  0b011..Trip-Level Voltage is 0.60000 V
 *  0b1xx..Reserved
 */
#define USBPHY_RX_DISCONADJ(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_DISCONADJ_SHIFT)) & USBPHY_RX_DISCONADJ_MASK)

#define USBPHY_RX_RXDBYPASS_MASK                 (0x400000U)
#define USBPHY_RX_RXDBYPASS_SHIFT                (22U)
/*! RXDBYPASS - RXDBYPASS
 *  0b0..Normal operation.
 *  0b1..Use the output of the USB_DP single-ended receiver in place of the full-speed differential receiver
 */
#define USBPHY_RX_RXDBYPASS(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_RXDBYPASS_SHIFT)) & USBPHY_RX_RXDBYPASS_MASK)
/*! @} */

/*! @name RX_SET - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_SET_ENVADJ_MASK                (0x7U)
#define USBPHY_RX_SET_ENVADJ_SHIFT               (0U)
/*! ENVADJ - ENVADJ */
#define USBPHY_RX_SET_ENVADJ(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_SET_ENVADJ_SHIFT)) & USBPHY_RX_SET_ENVADJ_MASK)

#define USBPHY_RX_SET_DISCONADJ_MASK             (0x70U)
#define USBPHY_RX_SET_DISCONADJ_SHIFT            (4U)
/*! DISCONADJ - DISCONADJ */
#define USBPHY_RX_SET_DISCONADJ(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_SET_DISCONADJ_SHIFT)) & USBPHY_RX_SET_DISCONADJ_MASK)

#define USBPHY_RX_SET_RXDBYPASS_MASK             (0x400000U)
#define USBPHY_RX_SET_RXDBYPASS_SHIFT            (22U)
/*! RXDBYPASS - RXDBYPASS */
#define USBPHY_RX_SET_RXDBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_SET_RXDBYPASS_SHIFT)) & USBPHY_RX_SET_RXDBYPASS_MASK)
/*! @} */

/*! @name RX_CLR - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_CLR_ENVADJ_MASK                (0x7U)
#define USBPHY_RX_CLR_ENVADJ_SHIFT               (0U)
/*! ENVADJ - ENVADJ */
#define USBPHY_RX_CLR_ENVADJ(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_CLR_ENVADJ_SHIFT)) & USBPHY_RX_CLR_ENVADJ_MASK)

#define USBPHY_RX_CLR_DISCONADJ_MASK             (0x70U)
#define USBPHY_RX_CLR_DISCONADJ_SHIFT            (4U)
/*! DISCONADJ - DISCONADJ */
#define USBPHY_RX_CLR_DISCONADJ(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_CLR_DISCONADJ_SHIFT)) & USBPHY_RX_CLR_DISCONADJ_MASK)

#define USBPHY_RX_CLR_RXDBYPASS_MASK             (0x400000U)
#define USBPHY_RX_CLR_RXDBYPASS_SHIFT            (22U)
/*! RXDBYPASS - RXDBYPASS */
#define USBPHY_RX_CLR_RXDBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_CLR_RXDBYPASS_SHIFT)) & USBPHY_RX_CLR_RXDBYPASS_MASK)
/*! @} */

/*! @name RX_TOG - USB PHY Receiver Control Register */
/*! @{ */

#define USBPHY_RX_TOG_ENVADJ_MASK                (0x7U)
#define USBPHY_RX_TOG_ENVADJ_SHIFT               (0U)
/*! ENVADJ - ENVADJ */
#define USBPHY_RX_TOG_ENVADJ(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_TOG_ENVADJ_SHIFT)) & USBPHY_RX_TOG_ENVADJ_MASK)

#define USBPHY_RX_TOG_DISCONADJ_MASK             (0x70U)
#define USBPHY_RX_TOG_DISCONADJ_SHIFT            (4U)
/*! DISCONADJ - DISCONADJ */
#define USBPHY_RX_TOG_DISCONADJ(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_TOG_DISCONADJ_SHIFT)) & USBPHY_RX_TOG_DISCONADJ_MASK)

#define USBPHY_RX_TOG_RXDBYPASS_MASK             (0x400000U)
#define USBPHY_RX_TOG_RXDBYPASS_SHIFT            (22U)
/*! RXDBYPASS - RXDBYPASS */
#define USBPHY_RX_TOG_RXDBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_RX_TOG_RXDBYPASS_SHIFT)) & USBPHY_RX_TOG_RXDBYPASS_MASK)
/*! @} */

/*! @name CTRL - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_ENOTG_ID_CHG_IRQ_MASK        (0x1U)
#define USBPHY_CTRL_ENOTG_ID_CHG_IRQ_SHIFT       (0U)
/*! ENOTG_ID_CHG_IRQ - ENOTG_ID_CHG_IRQ */
#define USBPHY_CTRL_ENOTG_ID_CHG_IRQ(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENOTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_ENOTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_ENHOSTDISCONDETECT_MASK      (0x2U)
#define USBPHY_CTRL_ENHOSTDISCONDETECT_SHIFT     (1U)
/*! ENHOSTDISCONDETECT - ENHOSTDISCONDETECT */
#define USBPHY_CTRL_ENHOSTDISCONDETECT(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_ENIRQHOSTDISCON_MASK         (0x4U)
#define USBPHY_CTRL_ENIRQHOSTDISCON_SHIFT        (2U)
/*! ENIRQHOSTDISCON - ENIRQHOSTDISCON */
#define USBPHY_CTRL_ENIRQHOSTDISCON(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_HOSTDISCONDETECT_IRQ_MASK    (0x8U)
#define USBPHY_CTRL_HOSTDISCONDETECT_IRQ_SHIFT   (3U)
/*! HOSTDISCONDETECT_IRQ - HOSTDISCONDETECT_IRQ */
#define USBPHY_CTRL_HOSTDISCONDETECT_IRQ(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_ENDEVPLUGINDETECT_MASK       (0x10U)
#define USBPHY_CTRL_ENDEVPLUGINDETECT_SHIFT      (4U)
/*! ENDEVPLUGINDETECT - Enables non-standard resistive plugged-in detection
 *  0b0..Disables 200kohm pullup resistors on DP and DN pins
 *  0b1..Enables 200kohm pullup resistors on DP and DN pins
 */
#define USBPHY_CTRL_ENDEVPLUGINDETECT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENDEVPLUGINDETECT_SHIFT)) & USBPHY_CTRL_ENDEVPLUGINDETECT_MASK)

#define USBPHY_CTRL_DEVPLUGIN_POLARITY_MASK      (0x20U)
#define USBPHY_CTRL_DEVPLUGIN_POLARITY_SHIFT     (5U)
/*! DEVPLUGIN_POLARITY - DEVPLUGIN_POLARITY */
#define USBPHY_CTRL_DEVPLUGIN_POLARITY(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_OTG_ID_CHG_IRQ_MASK          (0x40U)
#define USBPHY_CTRL_OTG_ID_CHG_IRQ_SHIFT         (6U)
/*! OTG_ID_CHG_IRQ - OTG_ID_CHG_IRQ */
#define USBPHY_CTRL_OTG_ID_CHG_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_OTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_OTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_ENOTGIDDETECT_MASK           (0x80U)
#define USBPHY_CTRL_ENOTGIDDETECT_SHIFT          (7U)
/*! ENOTGIDDETECT - ENOTGIDDETECT */
#define USBPHY_CTRL_ENOTGIDDETECT(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENOTGIDDETECT_SHIFT)) & USBPHY_CTRL_ENOTGIDDETECT_MASK)

#define USBPHY_CTRL_RESUMEIRQSTICKY_MASK         (0x100U)
#define USBPHY_CTRL_RESUMEIRQSTICKY_SHIFT        (8U)
/*! RESUMEIRQSTICKY - RESUMEIRQSTICKY */
#define USBPHY_CTRL_RESUMEIRQSTICKY(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_ENIRQRESUMEDETECT_MASK       (0x200U)
#define USBPHY_CTRL_ENIRQRESUMEDETECT_SHIFT      (9U)
/*! ENIRQRESUMEDETECT - ENIRQRESUMEDETECT */
#define USBPHY_CTRL_ENIRQRESUMEDETECT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_RESUME_IRQ_MASK              (0x400U)
#define USBPHY_CTRL_RESUME_IRQ_SHIFT             (10U)
/*! RESUME_IRQ - RESUME_IRQ */
#define USBPHY_CTRL_RESUME_IRQ(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_RESUME_IRQ_MASK)

#define USBPHY_CTRL_ENIRQDEVPLUGIN_MASK          (0x800U)
#define USBPHY_CTRL_ENIRQDEVPLUGIN_SHIFT         (11U)
/*! ENIRQDEVPLUGIN - ENIRQDEVPLUGIN */
#define USBPHY_CTRL_ENIRQDEVPLUGIN(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIRQDEVPLUGIN_SHIFT)) & USBPHY_CTRL_ENIRQDEVPLUGIN_MASK)

#define USBPHY_CTRL_DEVPLUGIN_IRQ_MASK           (0x1000U)
#define USBPHY_CTRL_DEVPLUGIN_IRQ_SHIFT          (12U)
/*! DEVPLUGIN_IRQ - DEVPLUGIN_IRQ */
#define USBPHY_CTRL_DEVPLUGIN_IRQ(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_ENUTMILEVEL2_MASK            (0x4000U)
#define USBPHY_CTRL_ENUTMILEVEL2_SHIFT           (14U)
/*! ENUTMILEVEL2 - ENUTMILEVEL2 */
#define USBPHY_CTRL_ENUTMILEVEL2(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_ENUTMILEVEL3_MASK            (0x8000U)
#define USBPHY_CTRL_ENUTMILEVEL3_SHIFT           (15U)
/*! ENUTMILEVEL3 - ENUTMILEVEL3 */
#define USBPHY_CTRL_ENUTMILEVEL3(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_ENIRQWAKEUP_MASK             (0x10000U)
#define USBPHY_CTRL_ENIRQWAKEUP_SHIFT            (16U)
/*! ENIRQWAKEUP - ENIRQWAKEUP */
#define USBPHY_CTRL_ENIRQWAKEUP(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_WAKEUP_IRQ_MASK              (0x20000U)
#define USBPHY_CTRL_WAKEUP_IRQ_SHIFT             (17U)
/*! WAKEUP_IRQ - WAKEUP_IRQ */
#define USBPHY_CTRL_WAKEUP_IRQ(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_AUTORESUME_EN_MASK           (0x40000U)
#define USBPHY_CTRL_AUTORESUME_EN_SHIFT          (18U)
/*! AUTORESUME_EN - AUTORESUME_EN */
#define USBPHY_CTRL_AUTORESUME_EN(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_ENAUTOCLR_CLKGATE_MASK       (0x80000U)
#define USBPHY_CTRL_ENAUTOCLR_CLKGATE_SHIFT      (19U)
/*! ENAUTOCLR_CLKGATE - ENAUTOCLR_CLKGATE */
#define USBPHY_CTRL_ENAUTOCLR_CLKGATE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_ENAUTOCLR_PHY_PWD_MASK       (0x100000U)
#define USBPHY_CTRL_ENAUTOCLR_PHY_PWD_SHIFT      (20U)
/*! ENAUTOCLR_PHY_PWD - ENAUTOCLR_PHY_PWD */
#define USBPHY_CTRL_ENAUTOCLR_PHY_PWD(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_ENDPDMCHG_WKUP_MASK          (0x200000U)
#define USBPHY_CTRL_ENDPDMCHG_WKUP_SHIFT         (21U)
/*! ENDPDMCHG_WKUP - ENDPDMCHG_WKUP */
#define USBPHY_CTRL_ENDPDMCHG_WKUP(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_ENIDCHG_WKUP_MASK            (0x400000U)
#define USBPHY_CTRL_ENIDCHG_WKUP_SHIFT           (22U)
/*! ENIDCHG_WKUP - ENIDCHG_WKUP */
#define USBPHY_CTRL_ENIDCHG_WKUP(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENIDCHG_WKUP_SHIFT)) & USBPHY_CTRL_ENIDCHG_WKUP_MASK)

#define USBPHY_CTRL_ENVBUSCHG_WKUP_MASK          (0x800000U)
#define USBPHY_CTRL_ENVBUSCHG_WKUP_SHIFT         (23U)
/*! ENVBUSCHG_WKUP - ENVBUSCHG_WKUP */
#define USBPHY_CTRL_ENVBUSCHG_WKUP(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_FSDLL_RST_EN_MASK            (0x1000000U)
#define USBPHY_CTRL_FSDLL_RST_EN_SHIFT           (24U)
/*! FSDLL_RST_EN - FSDLL_RST_EN */
#define USBPHY_CTRL_FSDLL_RST_EN(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_FSDLL_RST_EN_SHIFT)) & USBPHY_CTRL_FSDLL_RST_EN_MASK)

#define USBPHY_CTRL_OTG_ID_VALUE_MASK            (0x8000000U)
#define USBPHY_CTRL_OTG_ID_VALUE_SHIFT           (27U)
/*! OTG_ID_VALUE - OTG_ID_VALUE */
#define USBPHY_CTRL_OTG_ID_VALUE(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_OTG_ID_VALUE_SHIFT)) & USBPHY_CTRL_OTG_ID_VALUE_MASK)

#define USBPHY_CTRL_HOST_FORCE_LS_SE0_MASK       (0x10000000U)
#define USBPHY_CTRL_HOST_FORCE_LS_SE0_SHIFT      (28U)
/*! HOST_FORCE_LS_SE0 - HOST_FORCE_LS_SE0 */
#define USBPHY_CTRL_HOST_FORCE_LS_SE0(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_UTMI_SUSPENDM_MASK           (0x20000000U)
#define USBPHY_CTRL_UTMI_SUSPENDM_SHIFT          (29U)
/*! UTMI_SUSPENDM - UTMI_SUSPENDM */
#define USBPHY_CTRL_UTMI_SUSPENDM(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_CLKGATE_MASK                 (0x40000000U)
#define USBPHY_CTRL_CLKGATE_SHIFT                (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_CTRL_CLKGATE(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLKGATE_SHIFT)) & USBPHY_CTRL_CLKGATE_MASK)

#define USBPHY_CTRL_SFTRST_MASK                  (0x80000000U)
#define USBPHY_CTRL_SFTRST_SHIFT                 (31U)
/*! SFTRST - SFTRST */
#define USBPHY_CTRL_SFTRST(x)                    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SFTRST_SHIFT)) & USBPHY_CTRL_SFTRST_MASK)
/*! @} */

/*! @name CTRL_SET - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_SET_ENOTG_ID_CHG_IRQ_MASK    (0x1U)
#define USBPHY_CTRL_SET_ENOTG_ID_CHG_IRQ_SHIFT   (0U)
/*! ENOTG_ID_CHG_IRQ - ENOTG_ID_CHG_IRQ */
#define USBPHY_CTRL_SET_ENOTG_ID_CHG_IRQ(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENOTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_SET_ENOTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK  (0x2U)
#define USBPHY_CTRL_SET_ENHOSTDISCONDETECT_SHIFT (1U)
/*! ENHOSTDISCONDETECT - ENHOSTDISCONDETECT */
#define USBPHY_CTRL_SET_ENHOSTDISCONDETECT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_SET_ENIRQHOSTDISCON_MASK     (0x4U)
#define USBPHY_CTRL_SET_ENIRQHOSTDISCON_SHIFT    (2U)
/*! ENIRQHOSTDISCON - ENIRQHOSTDISCON */
#define USBPHY_CTRL_SET_ENIRQHOSTDISCON(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_SET_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_MASK (0x8U)
#define USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_SHIFT (3U)
/*! HOSTDISCONDETECT_IRQ - HOSTDISCONDETECT_IRQ */
#define USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_SET_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_SET_ENDEVPLUGINDETECT_MASK   (0x10U)
#define USBPHY_CTRL_SET_ENDEVPLUGINDETECT_SHIFT  (4U)
/*! ENDEVPLUGINDETECT - Enables non-standard resistive plugged-in detection */
#define USBPHY_CTRL_SET_ENDEVPLUGINDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENDEVPLUGINDETECT_SHIFT)) & USBPHY_CTRL_SET_ENDEVPLUGINDETECT_MASK)

#define USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_MASK  (0x20U)
#define USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_SHIFT (5U)
/*! DEVPLUGIN_POLARITY - DEVPLUGIN_POLARITY */
#define USBPHY_CTRL_SET_DEVPLUGIN_POLARITY(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_SET_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_SET_OTG_ID_CHG_IRQ_MASK      (0x40U)
#define USBPHY_CTRL_SET_OTG_ID_CHG_IRQ_SHIFT     (6U)
/*! OTG_ID_CHG_IRQ - OTG_ID_CHG_IRQ */
#define USBPHY_CTRL_SET_OTG_ID_CHG_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_OTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_SET_OTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_SET_ENOTGIDDETECT_MASK       (0x80U)
#define USBPHY_CTRL_SET_ENOTGIDDETECT_SHIFT      (7U)
/*! ENOTGIDDETECT - ENOTGIDDETECT */
#define USBPHY_CTRL_SET_ENOTGIDDETECT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENOTGIDDETECT_SHIFT)) & USBPHY_CTRL_SET_ENOTGIDDETECT_MASK)

#define USBPHY_CTRL_SET_RESUMEIRQSTICKY_MASK     (0x100U)
#define USBPHY_CTRL_SET_RESUMEIRQSTICKY_SHIFT    (8U)
/*! RESUMEIRQSTICKY - RESUMEIRQSTICKY */
#define USBPHY_CTRL_SET_RESUMEIRQSTICKY(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_SET_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_SET_ENIRQRESUMEDETECT_MASK   (0x200U)
#define USBPHY_CTRL_SET_ENIRQRESUMEDETECT_SHIFT  (9U)
/*! ENIRQRESUMEDETECT - ENIRQRESUMEDETECT */
#define USBPHY_CTRL_SET_ENIRQRESUMEDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_SET_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_SET_RESUME_IRQ_MASK          (0x400U)
#define USBPHY_CTRL_SET_RESUME_IRQ_SHIFT         (10U)
/*! RESUME_IRQ - RESUME_IRQ */
#define USBPHY_CTRL_SET_RESUME_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_SET_RESUME_IRQ_MASK)

#define USBPHY_CTRL_SET_ENIRQDEVPLUGIN_MASK      (0x800U)
#define USBPHY_CTRL_SET_ENIRQDEVPLUGIN_SHIFT     (11U)
/*! ENIRQDEVPLUGIN - ENIRQDEVPLUGIN */
#define USBPHY_CTRL_SET_ENIRQDEVPLUGIN(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIRQDEVPLUGIN_SHIFT)) & USBPHY_CTRL_SET_ENIRQDEVPLUGIN_MASK)

#define USBPHY_CTRL_SET_DEVPLUGIN_IRQ_MASK       (0x1000U)
#define USBPHY_CTRL_SET_DEVPLUGIN_IRQ_SHIFT      (12U)
/*! DEVPLUGIN_IRQ - DEVPLUGIN_IRQ */
#define USBPHY_CTRL_SET_DEVPLUGIN_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_SET_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_SET_ENUTMILEVEL2_MASK        (0x4000U)
#define USBPHY_CTRL_SET_ENUTMILEVEL2_SHIFT       (14U)
/*! ENUTMILEVEL2 - ENUTMILEVEL2 */
#define USBPHY_CTRL_SET_ENUTMILEVEL2(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_SET_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_SET_ENUTMILEVEL3_MASK        (0x8000U)
#define USBPHY_CTRL_SET_ENUTMILEVEL3_SHIFT       (15U)
/*! ENUTMILEVEL3 - ENUTMILEVEL3 */
#define USBPHY_CTRL_SET_ENUTMILEVEL3(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_SET_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_SET_ENIRQWAKEUP_MASK         (0x10000U)
#define USBPHY_CTRL_SET_ENIRQWAKEUP_SHIFT        (16U)
/*! ENIRQWAKEUP - ENIRQWAKEUP */
#define USBPHY_CTRL_SET_ENIRQWAKEUP(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_SET_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_SET_WAKEUP_IRQ_MASK          (0x20000U)
#define USBPHY_CTRL_SET_WAKEUP_IRQ_SHIFT         (17U)
/*! WAKEUP_IRQ - WAKEUP_IRQ */
#define USBPHY_CTRL_SET_WAKEUP_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_SET_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_SET_AUTORESUME_EN_MASK       (0x40000U)
#define USBPHY_CTRL_SET_AUTORESUME_EN_SHIFT      (18U)
/*! AUTORESUME_EN - AUTORESUME_EN */
#define USBPHY_CTRL_SET_AUTORESUME_EN(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_SET_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK   (0x80000U)
#define USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_SHIFT  (19U)
/*! ENAUTOCLR_CLKGATE - ENAUTOCLR_CLKGATE */
#define USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK   (0x100000U)
#define USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_SHIFT  (20U)
/*! ENAUTOCLR_PHY_PWD - ENAUTOCLR_PHY_PWD */
#define USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_SET_ENDPDMCHG_WKUP_MASK      (0x200000U)
#define USBPHY_CTRL_SET_ENDPDMCHG_WKUP_SHIFT     (21U)
/*! ENDPDMCHG_WKUP - ENDPDMCHG_WKUP */
#define USBPHY_CTRL_SET_ENDPDMCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_SET_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_SET_ENIDCHG_WKUP_MASK        (0x400000U)
#define USBPHY_CTRL_SET_ENIDCHG_WKUP_SHIFT       (22U)
/*! ENIDCHG_WKUP - ENIDCHG_WKUP */
#define USBPHY_CTRL_SET_ENIDCHG_WKUP(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENIDCHG_WKUP_SHIFT)) & USBPHY_CTRL_SET_ENIDCHG_WKUP_MASK)

#define USBPHY_CTRL_SET_ENVBUSCHG_WKUP_MASK      (0x800000U)
#define USBPHY_CTRL_SET_ENVBUSCHG_WKUP_SHIFT     (23U)
/*! ENVBUSCHG_WKUP - ENVBUSCHG_WKUP */
#define USBPHY_CTRL_SET_ENVBUSCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_SET_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_SET_FSDLL_RST_EN_MASK        (0x1000000U)
#define USBPHY_CTRL_SET_FSDLL_RST_EN_SHIFT       (24U)
/*! FSDLL_RST_EN - FSDLL_RST_EN */
#define USBPHY_CTRL_SET_FSDLL_RST_EN(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_FSDLL_RST_EN_SHIFT)) & USBPHY_CTRL_SET_FSDLL_RST_EN_MASK)

#define USBPHY_CTRL_SET_OTG_ID_VALUE_MASK        (0x8000000U)
#define USBPHY_CTRL_SET_OTG_ID_VALUE_SHIFT       (27U)
/*! OTG_ID_VALUE - OTG_ID_VALUE */
#define USBPHY_CTRL_SET_OTG_ID_VALUE(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_OTG_ID_VALUE_SHIFT)) & USBPHY_CTRL_SET_OTG_ID_VALUE_MASK)

#define USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_MASK   (0x10000000U)
#define USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_SHIFT  (28U)
/*! HOST_FORCE_LS_SE0 - HOST_FORCE_LS_SE0 */
#define USBPHY_CTRL_SET_HOST_FORCE_LS_SE0(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_SET_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_SET_UTMI_SUSPENDM_MASK       (0x20000000U)
#define USBPHY_CTRL_SET_UTMI_SUSPENDM_SHIFT      (29U)
/*! UTMI_SUSPENDM - UTMI_SUSPENDM */
#define USBPHY_CTRL_SET_UTMI_SUSPENDM(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_SET_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_SET_CLKGATE_MASK             (0x40000000U)
#define USBPHY_CTRL_SET_CLKGATE_SHIFT            (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_CTRL_SET_CLKGATE(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_CLKGATE_SHIFT)) & USBPHY_CTRL_SET_CLKGATE_MASK)

#define USBPHY_CTRL_SET_SFTRST_MASK              (0x80000000U)
#define USBPHY_CTRL_SET_SFTRST_SHIFT             (31U)
/*! SFTRST - SFTRST */
#define USBPHY_CTRL_SET_SFTRST(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_SET_SFTRST_SHIFT)) & USBPHY_CTRL_SET_SFTRST_MASK)
/*! @} */

/*! @name CTRL_CLR - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_CLR_ENOTG_ID_CHG_IRQ_MASK    (0x1U)
#define USBPHY_CTRL_CLR_ENOTG_ID_CHG_IRQ_SHIFT   (0U)
/*! ENOTG_ID_CHG_IRQ - ENOTG_ID_CHG_IRQ */
#define USBPHY_CTRL_CLR_ENOTG_ID_CHG_IRQ(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENOTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_CLR_ENOTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_MASK  (0x2U)
#define USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_SHIFT (1U)
/*! ENHOSTDISCONDETECT - ENHOSTDISCONDETECT */
#define USBPHY_CTRL_CLR_ENHOSTDISCONDETECT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_CLR_ENIRQHOSTDISCON_MASK     (0x4U)
#define USBPHY_CTRL_CLR_ENIRQHOSTDISCON_SHIFT    (2U)
/*! ENIRQHOSTDISCON - ENIRQHOSTDISCON */
#define USBPHY_CTRL_CLR_ENIRQHOSTDISCON(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_CLR_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_MASK (0x8U)
#define USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_SHIFT (3U)
/*! HOSTDISCONDETECT_IRQ - HOSTDISCONDETECT_IRQ */
#define USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_CLR_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_CLR_ENDEVPLUGINDETECT_MASK   (0x10U)
#define USBPHY_CTRL_CLR_ENDEVPLUGINDETECT_SHIFT  (4U)
/*! ENDEVPLUGINDETECT - Enables non-standard resistive plugged-in detection */
#define USBPHY_CTRL_CLR_ENDEVPLUGINDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENDEVPLUGINDETECT_SHIFT)) & USBPHY_CTRL_CLR_ENDEVPLUGINDETECT_MASK)

#define USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_MASK  (0x20U)
#define USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_SHIFT (5U)
/*! DEVPLUGIN_POLARITY - DEVPLUGIN_POLARITY */
#define USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_CLR_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_CLR_OTG_ID_CHG_IRQ_MASK      (0x40U)
#define USBPHY_CTRL_CLR_OTG_ID_CHG_IRQ_SHIFT     (6U)
/*! OTG_ID_CHG_IRQ - OTG_ID_CHG_IRQ */
#define USBPHY_CTRL_CLR_OTG_ID_CHG_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_OTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_CLR_OTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_CLR_ENOTGIDDETECT_MASK       (0x80U)
#define USBPHY_CTRL_CLR_ENOTGIDDETECT_SHIFT      (7U)
/*! ENOTGIDDETECT - ENOTGIDDETECT */
#define USBPHY_CTRL_CLR_ENOTGIDDETECT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENOTGIDDETECT_SHIFT)) & USBPHY_CTRL_CLR_ENOTGIDDETECT_MASK)

#define USBPHY_CTRL_CLR_RESUMEIRQSTICKY_MASK     (0x100U)
#define USBPHY_CTRL_CLR_RESUMEIRQSTICKY_SHIFT    (8U)
/*! RESUMEIRQSTICKY - RESUMEIRQSTICKY */
#define USBPHY_CTRL_CLR_RESUMEIRQSTICKY(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_CLR_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_MASK   (0x200U)
#define USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_SHIFT  (9U)
/*! ENIRQRESUMEDETECT - ENIRQRESUMEDETECT */
#define USBPHY_CTRL_CLR_ENIRQRESUMEDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_CLR_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_CLR_RESUME_IRQ_MASK          (0x400U)
#define USBPHY_CTRL_CLR_RESUME_IRQ_SHIFT         (10U)
/*! RESUME_IRQ - RESUME_IRQ */
#define USBPHY_CTRL_CLR_RESUME_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_CLR_RESUME_IRQ_MASK)

#define USBPHY_CTRL_CLR_ENIRQDEVPLUGIN_MASK      (0x800U)
#define USBPHY_CTRL_CLR_ENIRQDEVPLUGIN_SHIFT     (11U)
/*! ENIRQDEVPLUGIN - ENIRQDEVPLUGIN */
#define USBPHY_CTRL_CLR_ENIRQDEVPLUGIN(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIRQDEVPLUGIN_SHIFT)) & USBPHY_CTRL_CLR_ENIRQDEVPLUGIN_MASK)

#define USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_MASK       (0x1000U)
#define USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_SHIFT      (12U)
/*! DEVPLUGIN_IRQ - DEVPLUGIN_IRQ */
#define USBPHY_CTRL_CLR_DEVPLUGIN_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_CLR_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_CLR_ENUTMILEVEL2_MASK        (0x4000U)
#define USBPHY_CTRL_CLR_ENUTMILEVEL2_SHIFT       (14U)
/*! ENUTMILEVEL2 - ENUTMILEVEL2 */
#define USBPHY_CTRL_CLR_ENUTMILEVEL2(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_CLR_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_CLR_ENUTMILEVEL3_MASK        (0x8000U)
#define USBPHY_CTRL_CLR_ENUTMILEVEL3_SHIFT       (15U)
/*! ENUTMILEVEL3 - ENUTMILEVEL3 */
#define USBPHY_CTRL_CLR_ENUTMILEVEL3(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_CLR_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_CLR_ENIRQWAKEUP_MASK         (0x10000U)
#define USBPHY_CTRL_CLR_ENIRQWAKEUP_SHIFT        (16U)
/*! ENIRQWAKEUP - ENIRQWAKEUP */
#define USBPHY_CTRL_CLR_ENIRQWAKEUP(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_CLR_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_CLR_WAKEUP_IRQ_MASK          (0x20000U)
#define USBPHY_CTRL_CLR_WAKEUP_IRQ_SHIFT         (17U)
/*! WAKEUP_IRQ - WAKEUP_IRQ */
#define USBPHY_CTRL_CLR_WAKEUP_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_CLR_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_CLR_AUTORESUME_EN_MASK       (0x40000U)
#define USBPHY_CTRL_CLR_AUTORESUME_EN_SHIFT      (18U)
/*! AUTORESUME_EN - AUTORESUME_EN */
#define USBPHY_CTRL_CLR_AUTORESUME_EN(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_CLR_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_MASK   (0x80000U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_SHIFT  (19U)
/*! ENAUTOCLR_CLKGATE - ENAUTOCLR_CLKGATE */
#define USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_CLR_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_MASK   (0x100000U)
#define USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_SHIFT  (20U)
/*! ENAUTOCLR_PHY_PWD - ENAUTOCLR_PHY_PWD */
#define USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_CLR_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_MASK      (0x200000U)
#define USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_SHIFT     (21U)
/*! ENDPDMCHG_WKUP - ENDPDMCHG_WKUP */
#define USBPHY_CTRL_CLR_ENDPDMCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_CLR_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_CLR_ENIDCHG_WKUP_MASK        (0x400000U)
#define USBPHY_CTRL_CLR_ENIDCHG_WKUP_SHIFT       (22U)
/*! ENIDCHG_WKUP - ENIDCHG_WKUP */
#define USBPHY_CTRL_CLR_ENIDCHG_WKUP(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENIDCHG_WKUP_SHIFT)) & USBPHY_CTRL_CLR_ENIDCHG_WKUP_MASK)

#define USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_MASK      (0x800000U)
#define USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_SHIFT     (23U)
/*! ENVBUSCHG_WKUP - ENVBUSCHG_WKUP */
#define USBPHY_CTRL_CLR_ENVBUSCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_CLR_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_CLR_FSDLL_RST_EN_MASK        (0x1000000U)
#define USBPHY_CTRL_CLR_FSDLL_RST_EN_SHIFT       (24U)
/*! FSDLL_RST_EN - FSDLL_RST_EN */
#define USBPHY_CTRL_CLR_FSDLL_RST_EN(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_FSDLL_RST_EN_SHIFT)) & USBPHY_CTRL_CLR_FSDLL_RST_EN_MASK)

#define USBPHY_CTRL_CLR_OTG_ID_VALUE_MASK        (0x8000000U)
#define USBPHY_CTRL_CLR_OTG_ID_VALUE_SHIFT       (27U)
/*! OTG_ID_VALUE - OTG_ID_VALUE */
#define USBPHY_CTRL_CLR_OTG_ID_VALUE(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_OTG_ID_VALUE_SHIFT)) & USBPHY_CTRL_CLR_OTG_ID_VALUE_MASK)

#define USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_MASK   (0x10000000U)
#define USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_SHIFT  (28U)
/*! HOST_FORCE_LS_SE0 - HOST_FORCE_LS_SE0 */
#define USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_CLR_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_CLR_UTMI_SUSPENDM_MASK       (0x20000000U)
#define USBPHY_CTRL_CLR_UTMI_SUSPENDM_SHIFT      (29U)
/*! UTMI_SUSPENDM - UTMI_SUSPENDM */
#define USBPHY_CTRL_CLR_UTMI_SUSPENDM(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_CLR_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_CLR_CLKGATE_MASK             (0x40000000U)
#define USBPHY_CTRL_CLR_CLKGATE_SHIFT            (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_CTRL_CLR_CLKGATE(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_CLKGATE_SHIFT)) & USBPHY_CTRL_CLR_CLKGATE_MASK)

#define USBPHY_CTRL_CLR_SFTRST_MASK              (0x80000000U)
#define USBPHY_CTRL_CLR_SFTRST_SHIFT             (31U)
/*! SFTRST - SFTRST */
#define USBPHY_CTRL_CLR_SFTRST(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_CLR_SFTRST_SHIFT)) & USBPHY_CTRL_CLR_SFTRST_MASK)
/*! @} */

/*! @name CTRL_TOG - USB PHY General Control Register */
/*! @{ */

#define USBPHY_CTRL_TOG_ENOTG_ID_CHG_IRQ_MASK    (0x1U)
#define USBPHY_CTRL_TOG_ENOTG_ID_CHG_IRQ_SHIFT   (0U)
/*! ENOTG_ID_CHG_IRQ - ENOTG_ID_CHG_IRQ */
#define USBPHY_CTRL_TOG_ENOTG_ID_CHG_IRQ(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENOTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_TOG_ENOTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_MASK  (0x2U)
#define USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_SHIFT (1U)
/*! ENHOSTDISCONDETECT - ENHOSTDISCONDETECT */
#define USBPHY_CTRL_TOG_ENHOSTDISCONDETECT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_SHIFT)) & USBPHY_CTRL_TOG_ENHOSTDISCONDETECT_MASK)

#define USBPHY_CTRL_TOG_ENIRQHOSTDISCON_MASK     (0x4U)
#define USBPHY_CTRL_TOG_ENIRQHOSTDISCON_SHIFT    (2U)
/*! ENIRQHOSTDISCON - ENIRQHOSTDISCON */
#define USBPHY_CTRL_TOG_ENIRQHOSTDISCON(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIRQHOSTDISCON_SHIFT)) & USBPHY_CTRL_TOG_ENIRQHOSTDISCON_MASK)

#define USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_MASK (0x8U)
#define USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_SHIFT (3U)
/*! HOSTDISCONDETECT_IRQ - HOSTDISCONDETECT_IRQ */
#define USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_SHIFT)) & USBPHY_CTRL_TOG_HOSTDISCONDETECT_IRQ_MASK)

#define USBPHY_CTRL_TOG_ENDEVPLUGINDETECT_MASK   (0x10U)
#define USBPHY_CTRL_TOG_ENDEVPLUGINDETECT_SHIFT  (4U)
/*! ENDEVPLUGINDETECT - Enables non-standard resistive plugged-in detection */
#define USBPHY_CTRL_TOG_ENDEVPLUGINDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENDEVPLUGINDETECT_SHIFT)) & USBPHY_CTRL_TOG_ENDEVPLUGINDETECT_MASK)

#define USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_MASK  (0x20U)
#define USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_SHIFT (5U)
/*! DEVPLUGIN_POLARITY - DEVPLUGIN_POLARITY */
#define USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_SHIFT)) & USBPHY_CTRL_TOG_DEVPLUGIN_POLARITY_MASK)

#define USBPHY_CTRL_TOG_OTG_ID_CHG_IRQ_MASK      (0x40U)
#define USBPHY_CTRL_TOG_OTG_ID_CHG_IRQ_SHIFT     (6U)
/*! OTG_ID_CHG_IRQ - OTG_ID_CHG_IRQ */
#define USBPHY_CTRL_TOG_OTG_ID_CHG_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_OTG_ID_CHG_IRQ_SHIFT)) & USBPHY_CTRL_TOG_OTG_ID_CHG_IRQ_MASK)

#define USBPHY_CTRL_TOG_ENOTGIDDETECT_MASK       (0x80U)
#define USBPHY_CTRL_TOG_ENOTGIDDETECT_SHIFT      (7U)
/*! ENOTGIDDETECT - ENOTGIDDETECT */
#define USBPHY_CTRL_TOG_ENOTGIDDETECT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENOTGIDDETECT_SHIFT)) & USBPHY_CTRL_TOG_ENOTGIDDETECT_MASK)

#define USBPHY_CTRL_TOG_RESUMEIRQSTICKY_MASK     (0x100U)
#define USBPHY_CTRL_TOG_RESUMEIRQSTICKY_SHIFT    (8U)
/*! RESUMEIRQSTICKY - RESUMEIRQSTICKY */
#define USBPHY_CTRL_TOG_RESUMEIRQSTICKY(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_RESUMEIRQSTICKY_SHIFT)) & USBPHY_CTRL_TOG_RESUMEIRQSTICKY_MASK)

#define USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_MASK   (0x200U)
#define USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_SHIFT  (9U)
/*! ENIRQRESUMEDETECT - ENIRQRESUMEDETECT */
#define USBPHY_CTRL_TOG_ENIRQRESUMEDETECT(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_SHIFT)) & USBPHY_CTRL_TOG_ENIRQRESUMEDETECT_MASK)

#define USBPHY_CTRL_TOG_RESUME_IRQ_MASK          (0x400U)
#define USBPHY_CTRL_TOG_RESUME_IRQ_SHIFT         (10U)
/*! RESUME_IRQ - RESUME_IRQ */
#define USBPHY_CTRL_TOG_RESUME_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_RESUME_IRQ_SHIFT)) & USBPHY_CTRL_TOG_RESUME_IRQ_MASK)

#define USBPHY_CTRL_TOG_ENIRQDEVPLUGIN_MASK      (0x800U)
#define USBPHY_CTRL_TOG_ENIRQDEVPLUGIN_SHIFT     (11U)
/*! ENIRQDEVPLUGIN - ENIRQDEVPLUGIN */
#define USBPHY_CTRL_TOG_ENIRQDEVPLUGIN(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIRQDEVPLUGIN_SHIFT)) & USBPHY_CTRL_TOG_ENIRQDEVPLUGIN_MASK)

#define USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_MASK       (0x1000U)
#define USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_SHIFT      (12U)
/*! DEVPLUGIN_IRQ - DEVPLUGIN_IRQ */
#define USBPHY_CTRL_TOG_DEVPLUGIN_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_SHIFT)) & USBPHY_CTRL_TOG_DEVPLUGIN_IRQ_MASK)

#define USBPHY_CTRL_TOG_ENUTMILEVEL2_MASK        (0x4000U)
#define USBPHY_CTRL_TOG_ENUTMILEVEL2_SHIFT       (14U)
/*! ENUTMILEVEL2 - ENUTMILEVEL2 */
#define USBPHY_CTRL_TOG_ENUTMILEVEL2(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENUTMILEVEL2_SHIFT)) & USBPHY_CTRL_TOG_ENUTMILEVEL2_MASK)

#define USBPHY_CTRL_TOG_ENUTMILEVEL3_MASK        (0x8000U)
#define USBPHY_CTRL_TOG_ENUTMILEVEL3_SHIFT       (15U)
/*! ENUTMILEVEL3 - ENUTMILEVEL3 */
#define USBPHY_CTRL_TOG_ENUTMILEVEL3(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENUTMILEVEL3_SHIFT)) & USBPHY_CTRL_TOG_ENUTMILEVEL3_MASK)

#define USBPHY_CTRL_TOG_ENIRQWAKEUP_MASK         (0x10000U)
#define USBPHY_CTRL_TOG_ENIRQWAKEUP_SHIFT        (16U)
/*! ENIRQWAKEUP - ENIRQWAKEUP */
#define USBPHY_CTRL_TOG_ENIRQWAKEUP(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIRQWAKEUP_SHIFT)) & USBPHY_CTRL_TOG_ENIRQWAKEUP_MASK)

#define USBPHY_CTRL_TOG_WAKEUP_IRQ_MASK          (0x20000U)
#define USBPHY_CTRL_TOG_WAKEUP_IRQ_SHIFT         (17U)
/*! WAKEUP_IRQ - WAKEUP_IRQ */
#define USBPHY_CTRL_TOG_WAKEUP_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_WAKEUP_IRQ_SHIFT)) & USBPHY_CTRL_TOG_WAKEUP_IRQ_MASK)

#define USBPHY_CTRL_TOG_AUTORESUME_EN_MASK       (0x40000U)
#define USBPHY_CTRL_TOG_AUTORESUME_EN_SHIFT      (18U)
/*! AUTORESUME_EN - AUTORESUME_EN */
#define USBPHY_CTRL_TOG_AUTORESUME_EN(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_AUTORESUME_EN_SHIFT)) & USBPHY_CTRL_TOG_AUTORESUME_EN_MASK)

#define USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_MASK   (0x80000U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_SHIFT  (19U)
/*! ENAUTOCLR_CLKGATE - ENAUTOCLR_CLKGATE */
#define USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_SHIFT)) & USBPHY_CTRL_TOG_ENAUTOCLR_CLKGATE_MASK)

#define USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_MASK   (0x100000U)
#define USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_SHIFT  (20U)
/*! ENAUTOCLR_PHY_PWD - ENAUTOCLR_PHY_PWD */
#define USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_SHIFT)) & USBPHY_CTRL_TOG_ENAUTOCLR_PHY_PWD_MASK)

#define USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_MASK      (0x200000U)
#define USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_SHIFT     (21U)
/*! ENDPDMCHG_WKUP - ENDPDMCHG_WKUP */
#define USBPHY_CTRL_TOG_ENDPDMCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_SHIFT)) & USBPHY_CTRL_TOG_ENDPDMCHG_WKUP_MASK)

#define USBPHY_CTRL_TOG_ENIDCHG_WKUP_MASK        (0x400000U)
#define USBPHY_CTRL_TOG_ENIDCHG_WKUP_SHIFT       (22U)
/*! ENIDCHG_WKUP - ENIDCHG_WKUP */
#define USBPHY_CTRL_TOG_ENIDCHG_WKUP(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENIDCHG_WKUP_SHIFT)) & USBPHY_CTRL_TOG_ENIDCHG_WKUP_MASK)

#define USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_MASK      (0x800000U)
#define USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_SHIFT     (23U)
/*! ENVBUSCHG_WKUP - ENVBUSCHG_WKUP */
#define USBPHY_CTRL_TOG_ENVBUSCHG_WKUP(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_SHIFT)) & USBPHY_CTRL_TOG_ENVBUSCHG_WKUP_MASK)

#define USBPHY_CTRL_TOG_FSDLL_RST_EN_MASK        (0x1000000U)
#define USBPHY_CTRL_TOG_FSDLL_RST_EN_SHIFT       (24U)
/*! FSDLL_RST_EN - FSDLL_RST_EN */
#define USBPHY_CTRL_TOG_FSDLL_RST_EN(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_FSDLL_RST_EN_SHIFT)) & USBPHY_CTRL_TOG_FSDLL_RST_EN_MASK)

#define USBPHY_CTRL_TOG_OTG_ID_VALUE_MASK        (0x8000000U)
#define USBPHY_CTRL_TOG_OTG_ID_VALUE_SHIFT       (27U)
/*! OTG_ID_VALUE - OTG_ID_VALUE */
#define USBPHY_CTRL_TOG_OTG_ID_VALUE(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_OTG_ID_VALUE_SHIFT)) & USBPHY_CTRL_TOG_OTG_ID_VALUE_MASK)

#define USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_MASK   (0x10000000U)
#define USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_SHIFT  (28U)
/*! HOST_FORCE_LS_SE0 - HOST_FORCE_LS_SE0 */
#define USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_SHIFT)) & USBPHY_CTRL_TOG_HOST_FORCE_LS_SE0_MASK)

#define USBPHY_CTRL_TOG_UTMI_SUSPENDM_MASK       (0x20000000U)
#define USBPHY_CTRL_TOG_UTMI_SUSPENDM_SHIFT      (29U)
/*! UTMI_SUSPENDM - UTMI_SUSPENDM */
#define USBPHY_CTRL_TOG_UTMI_SUSPENDM(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_UTMI_SUSPENDM_SHIFT)) & USBPHY_CTRL_TOG_UTMI_SUSPENDM_MASK)

#define USBPHY_CTRL_TOG_CLKGATE_MASK             (0x40000000U)
#define USBPHY_CTRL_TOG_CLKGATE_SHIFT            (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_CTRL_TOG_CLKGATE(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_CLKGATE_SHIFT)) & USBPHY_CTRL_TOG_CLKGATE_MASK)

#define USBPHY_CTRL_TOG_SFTRST_MASK              (0x80000000U)
#define USBPHY_CTRL_TOG_SFTRST_SHIFT             (31U)
/*! SFTRST - SFTRST */
#define USBPHY_CTRL_TOG_SFTRST(x)                (((uint32_t)(((uint32_t)(x)) << USBPHY_CTRL_TOG_SFTRST_SHIFT)) & USBPHY_CTRL_TOG_SFTRST_MASK)
/*! @} */

/*! @name STATUS - USB PHY Status Register */
/*! @{ */

#define USBPHY_STATUS_HOSTDISCONDETECT_STATUS_MASK (0x8U)
#define USBPHY_STATUS_HOSTDISCONDETECT_STATUS_SHIFT (3U)
/*! HOSTDISCONDETECT_STATUS - HOSTDISCONDETECT_STATUS
 *  0b0..USB cable disconnect has not been detected at the local host
 *  0b1..USB cable disconnect has been detected at the local host
 */
#define USBPHY_STATUS_HOSTDISCONDETECT_STATUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_HOSTDISCONDETECT_STATUS_SHIFT)) & USBPHY_STATUS_HOSTDISCONDETECT_STATUS_MASK)

#define USBPHY_STATUS_DEVPLUGIN_STATUS_MASK      (0x40U)
#define USBPHY_STATUS_DEVPLUGIN_STATUS_SHIFT     (6U)
/*! DEVPLUGIN_STATUS - Status indicator for non-standard resistive plugged-in detection
 *  0b0..No attachment to a USB host is detected
 *  0b1..Cable attachment to a USB host is detected
 */
#define USBPHY_STATUS_DEVPLUGIN_STATUS(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_DEVPLUGIN_STATUS_SHIFT)) & USBPHY_STATUS_DEVPLUGIN_STATUS_MASK)

#define USBPHY_STATUS_OTGID_STATUS_MASK          (0x100U)
#define USBPHY_STATUS_OTGID_STATUS_SHIFT         (8U)
/*! OTGID_STATUS - OTGID_STATUS */
#define USBPHY_STATUS_OTGID_STATUS(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_OTGID_STATUS_SHIFT)) & USBPHY_STATUS_OTGID_STATUS_MASK)

#define USBPHY_STATUS_RESUME_STATUS_MASK         (0x400U)
#define USBPHY_STATUS_RESUME_STATUS_SHIFT        (10U)
/*! RESUME_STATUS - RESUME_STATUS */
#define USBPHY_STATUS_RESUME_STATUS(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_STATUS_RESUME_STATUS_SHIFT)) & USBPHY_STATUS_RESUME_STATUS_MASK)
/*! @} */

/*! @name DEBUG - USB PHY Debug Register */
/*! @{ */

#define USBPHY_DEBUG_OTGIDPIOLOCK_MASK           (0x1U)
#define USBPHY_DEBUG_OTGIDPIOLOCK_SHIFT          (0U)
/*! OTGIDPIOLOCK - OTGIDPIOLOCK */
#define USBPHY_DEBUG_OTGIDPIOLOCK(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_OTGIDPIOLOCK_SHIFT)) & USBPHY_DEBUG_OTGIDPIOLOCK_MASK)

#define USBPHY_DEBUG_DEBUG_INTERFACE_HOLD_MASK   (0x2U)
#define USBPHY_DEBUG_DEBUG_INTERFACE_HOLD_SHIFT  (1U)
/*! DEBUG_INTERFACE_HOLD - DEBUG_INTERFACE_HOLD */
#define USBPHY_DEBUG_DEBUG_INTERFACE_HOLD(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_DEBUG_INTERFACE_HOLD_SHIFT)) & USBPHY_DEBUG_DEBUG_INTERFACE_HOLD_MASK)

#define USBPHY_DEBUG_HSTPULLDOWN_MASK            (0xCU)
#define USBPHY_DEBUG_HSTPULLDOWN_SHIFT           (2U)
/*! HSTPULLDOWN - HSTPULLDOWN */
#define USBPHY_DEBUG_HSTPULLDOWN(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_HSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_HSTPULLDOWN_MASK)

#define USBPHY_DEBUG_ENHSTPULLDOWN_MASK          (0x30U)
#define USBPHY_DEBUG_ENHSTPULLDOWN_SHIFT         (4U)
/*! ENHSTPULLDOWN - ENHSTPULLDOWN */
#define USBPHY_DEBUG_ENHSTPULLDOWN(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_ENHSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_ENHSTPULLDOWN_MASK)

#define USBPHY_DEBUG_TX2RXCOUNT_MASK             (0xF00U)
#define USBPHY_DEBUG_TX2RXCOUNT_SHIFT            (8U)
/*! TX2RXCOUNT - TX2RXCOUNT */
#define USBPHY_DEBUG_TX2RXCOUNT(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_TX2RXCOUNT_MASK)

#define USBPHY_DEBUG_ENTX2RXCOUNT_MASK           (0x1000U)
#define USBPHY_DEBUG_ENTX2RXCOUNT_SHIFT          (12U)
/*! ENTX2RXCOUNT - ENTX2RXCOUNT */
#define USBPHY_DEBUG_ENTX2RXCOUNT(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_ENTX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_ENTX2RXCOUNT_MASK)

#define USBPHY_DEBUG_SQUELCHRESETCOUNT_MASK      (0x1F0000U)
#define USBPHY_DEBUG_SQUELCHRESETCOUNT_SHIFT     (16U)
/*! SQUELCHRESETCOUNT - SQUELCHRESETCOUNT */
#define USBPHY_DEBUG_SQUELCHRESETCOUNT(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SQUELCHRESETCOUNT_SHIFT)) & USBPHY_DEBUG_SQUELCHRESETCOUNT_MASK)

#define USBPHY_DEBUG_ENSQUELCHRESET_MASK         (0x1000000U)
#define USBPHY_DEBUG_ENSQUELCHRESET_SHIFT        (24U)
/*! ENSQUELCHRESET - ENSQUELCHRESET */
#define USBPHY_DEBUG_ENSQUELCHRESET(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_ENSQUELCHRESET_SHIFT)) & USBPHY_DEBUG_ENSQUELCHRESET_MASK)

#define USBPHY_DEBUG_SQUELCHRESETLENGTH_MASK     (0x1E000000U)
#define USBPHY_DEBUG_SQUELCHRESETLENGTH_SHIFT    (25U)
/*! SQUELCHRESETLENGTH - SQUELCHRESETLENGTH */
#define USBPHY_DEBUG_SQUELCHRESETLENGTH(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SQUELCHRESETLENGTH_SHIFT)) & USBPHY_DEBUG_SQUELCHRESETLENGTH_MASK)

#define USBPHY_DEBUG_HOST_RESUME_DEBUG_MASK      (0x20000000U)
#define USBPHY_DEBUG_HOST_RESUME_DEBUG_SHIFT     (29U)
/*! HOST_RESUME_DEBUG - HOST_RESUME_DEBUG */
#define USBPHY_DEBUG_HOST_RESUME_DEBUG(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_HOST_RESUME_DEBUG_SHIFT)) & USBPHY_DEBUG_HOST_RESUME_DEBUG_MASK)

#define USBPHY_DEBUG_CLKGATE_MASK                (0x40000000U)
#define USBPHY_DEBUG_CLKGATE_SHIFT               (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_DEBUG_CLKGATE(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLKGATE_SHIFT)) & USBPHY_DEBUG_CLKGATE_MASK)
/*! @} */

/*! @name DEBUG_SET - USB PHY Debug Register */
/*! @{ */

#define USBPHY_DEBUG_SET_OTGIDPIOLOCK_MASK       (0x1U)
#define USBPHY_DEBUG_SET_OTGIDPIOLOCK_SHIFT      (0U)
/*! OTGIDPIOLOCK - OTGIDPIOLOCK */
#define USBPHY_DEBUG_SET_OTGIDPIOLOCK(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_OTGIDPIOLOCK_SHIFT)) & USBPHY_DEBUG_SET_OTGIDPIOLOCK_MASK)

#define USBPHY_DEBUG_SET_DEBUG_INTERFACE_HOLD_MASK (0x2U)
#define USBPHY_DEBUG_SET_DEBUG_INTERFACE_HOLD_SHIFT (1U)
/*! DEBUG_INTERFACE_HOLD - DEBUG_INTERFACE_HOLD */
#define USBPHY_DEBUG_SET_DEBUG_INTERFACE_HOLD(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_DEBUG_INTERFACE_HOLD_SHIFT)) & USBPHY_DEBUG_SET_DEBUG_INTERFACE_HOLD_MASK)

#define USBPHY_DEBUG_SET_HSTPULLDOWN_MASK        (0xCU)
#define USBPHY_DEBUG_SET_HSTPULLDOWN_SHIFT       (2U)
/*! HSTPULLDOWN - HSTPULLDOWN */
#define USBPHY_DEBUG_SET_HSTPULLDOWN(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_HSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_SET_HSTPULLDOWN_MASK)

#define USBPHY_DEBUG_SET_ENHSTPULLDOWN_MASK      (0x30U)
#define USBPHY_DEBUG_SET_ENHSTPULLDOWN_SHIFT     (4U)
/*! ENHSTPULLDOWN - ENHSTPULLDOWN */
#define USBPHY_DEBUG_SET_ENHSTPULLDOWN(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_ENHSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_SET_ENHSTPULLDOWN_MASK)

#define USBPHY_DEBUG_SET_TX2RXCOUNT_MASK         (0xF00U)
#define USBPHY_DEBUG_SET_TX2RXCOUNT_SHIFT        (8U)
/*! TX2RXCOUNT - TX2RXCOUNT */
#define USBPHY_DEBUG_SET_TX2RXCOUNT(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_TX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_SET_TX2RXCOUNT_MASK)

#define USBPHY_DEBUG_SET_ENTX2RXCOUNT_MASK       (0x1000U)
#define USBPHY_DEBUG_SET_ENTX2RXCOUNT_SHIFT      (12U)
/*! ENTX2RXCOUNT - ENTX2RXCOUNT */
#define USBPHY_DEBUG_SET_ENTX2RXCOUNT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_ENTX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_SET_ENTX2RXCOUNT_MASK)

#define USBPHY_DEBUG_SET_SQUELCHRESETCOUNT_MASK  (0x1F0000U)
#define USBPHY_DEBUG_SET_SQUELCHRESETCOUNT_SHIFT (16U)
/*! SQUELCHRESETCOUNT - SQUELCHRESETCOUNT */
#define USBPHY_DEBUG_SET_SQUELCHRESETCOUNT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_SQUELCHRESETCOUNT_SHIFT)) & USBPHY_DEBUG_SET_SQUELCHRESETCOUNT_MASK)

#define USBPHY_DEBUG_SET_ENSQUELCHRESET_MASK     (0x1000000U)
#define USBPHY_DEBUG_SET_ENSQUELCHRESET_SHIFT    (24U)
/*! ENSQUELCHRESET - ENSQUELCHRESET */
#define USBPHY_DEBUG_SET_ENSQUELCHRESET(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_ENSQUELCHRESET_SHIFT)) & USBPHY_DEBUG_SET_ENSQUELCHRESET_MASK)

#define USBPHY_DEBUG_SET_SQUELCHRESETLENGTH_MASK (0x1E000000U)
#define USBPHY_DEBUG_SET_SQUELCHRESETLENGTH_SHIFT (25U)
/*! SQUELCHRESETLENGTH - SQUELCHRESETLENGTH */
#define USBPHY_DEBUG_SET_SQUELCHRESETLENGTH(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_SQUELCHRESETLENGTH_SHIFT)) & USBPHY_DEBUG_SET_SQUELCHRESETLENGTH_MASK)

#define USBPHY_DEBUG_SET_HOST_RESUME_DEBUG_MASK  (0x20000000U)
#define USBPHY_DEBUG_SET_HOST_RESUME_DEBUG_SHIFT (29U)
/*! HOST_RESUME_DEBUG - HOST_RESUME_DEBUG */
#define USBPHY_DEBUG_SET_HOST_RESUME_DEBUG(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_HOST_RESUME_DEBUG_SHIFT)) & USBPHY_DEBUG_SET_HOST_RESUME_DEBUG_MASK)

#define USBPHY_DEBUG_SET_CLKGATE_MASK            (0x40000000U)
#define USBPHY_DEBUG_SET_CLKGATE_SHIFT           (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_DEBUG_SET_CLKGATE(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_SET_CLKGATE_SHIFT)) & USBPHY_DEBUG_SET_CLKGATE_MASK)
/*! @} */

/*! @name DEBUG_CLR - USB PHY Debug Register */
/*! @{ */

#define USBPHY_DEBUG_CLR_OTGIDPIOLOCK_MASK       (0x1U)
#define USBPHY_DEBUG_CLR_OTGIDPIOLOCK_SHIFT      (0U)
/*! OTGIDPIOLOCK - OTGIDPIOLOCK */
#define USBPHY_DEBUG_CLR_OTGIDPIOLOCK(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_OTGIDPIOLOCK_SHIFT)) & USBPHY_DEBUG_CLR_OTGIDPIOLOCK_MASK)

#define USBPHY_DEBUG_CLR_DEBUG_INTERFACE_HOLD_MASK (0x2U)
#define USBPHY_DEBUG_CLR_DEBUG_INTERFACE_HOLD_SHIFT (1U)
/*! DEBUG_INTERFACE_HOLD - DEBUG_INTERFACE_HOLD */
#define USBPHY_DEBUG_CLR_DEBUG_INTERFACE_HOLD(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_DEBUG_INTERFACE_HOLD_SHIFT)) & USBPHY_DEBUG_CLR_DEBUG_INTERFACE_HOLD_MASK)

#define USBPHY_DEBUG_CLR_HSTPULLDOWN_MASK        (0xCU)
#define USBPHY_DEBUG_CLR_HSTPULLDOWN_SHIFT       (2U)
/*! HSTPULLDOWN - HSTPULLDOWN */
#define USBPHY_DEBUG_CLR_HSTPULLDOWN(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_HSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_CLR_HSTPULLDOWN_MASK)

#define USBPHY_DEBUG_CLR_ENHSTPULLDOWN_MASK      (0x30U)
#define USBPHY_DEBUG_CLR_ENHSTPULLDOWN_SHIFT     (4U)
/*! ENHSTPULLDOWN - ENHSTPULLDOWN */
#define USBPHY_DEBUG_CLR_ENHSTPULLDOWN(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_ENHSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_CLR_ENHSTPULLDOWN_MASK)

#define USBPHY_DEBUG_CLR_TX2RXCOUNT_MASK         (0xF00U)
#define USBPHY_DEBUG_CLR_TX2RXCOUNT_SHIFT        (8U)
/*! TX2RXCOUNT - TX2RXCOUNT */
#define USBPHY_DEBUG_CLR_TX2RXCOUNT(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_TX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_CLR_TX2RXCOUNT_MASK)

#define USBPHY_DEBUG_CLR_ENTX2RXCOUNT_MASK       (0x1000U)
#define USBPHY_DEBUG_CLR_ENTX2RXCOUNT_SHIFT      (12U)
/*! ENTX2RXCOUNT - ENTX2RXCOUNT */
#define USBPHY_DEBUG_CLR_ENTX2RXCOUNT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_ENTX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_CLR_ENTX2RXCOUNT_MASK)

#define USBPHY_DEBUG_CLR_SQUELCHRESETCOUNT_MASK  (0x1F0000U)
#define USBPHY_DEBUG_CLR_SQUELCHRESETCOUNT_SHIFT (16U)
/*! SQUELCHRESETCOUNT - SQUELCHRESETCOUNT */
#define USBPHY_DEBUG_CLR_SQUELCHRESETCOUNT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_SQUELCHRESETCOUNT_SHIFT)) & USBPHY_DEBUG_CLR_SQUELCHRESETCOUNT_MASK)

#define USBPHY_DEBUG_CLR_ENSQUELCHRESET_MASK     (0x1000000U)
#define USBPHY_DEBUG_CLR_ENSQUELCHRESET_SHIFT    (24U)
/*! ENSQUELCHRESET - ENSQUELCHRESET */
#define USBPHY_DEBUG_CLR_ENSQUELCHRESET(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_ENSQUELCHRESET_SHIFT)) & USBPHY_DEBUG_CLR_ENSQUELCHRESET_MASK)

#define USBPHY_DEBUG_CLR_SQUELCHRESETLENGTH_MASK (0x1E000000U)
#define USBPHY_DEBUG_CLR_SQUELCHRESETLENGTH_SHIFT (25U)
/*! SQUELCHRESETLENGTH - SQUELCHRESETLENGTH */
#define USBPHY_DEBUG_CLR_SQUELCHRESETLENGTH(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_SQUELCHRESETLENGTH_SHIFT)) & USBPHY_DEBUG_CLR_SQUELCHRESETLENGTH_MASK)

#define USBPHY_DEBUG_CLR_HOST_RESUME_DEBUG_MASK  (0x20000000U)
#define USBPHY_DEBUG_CLR_HOST_RESUME_DEBUG_SHIFT (29U)
/*! HOST_RESUME_DEBUG - HOST_RESUME_DEBUG */
#define USBPHY_DEBUG_CLR_HOST_RESUME_DEBUG(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_HOST_RESUME_DEBUG_SHIFT)) & USBPHY_DEBUG_CLR_HOST_RESUME_DEBUG_MASK)

#define USBPHY_DEBUG_CLR_CLKGATE_MASK            (0x40000000U)
#define USBPHY_DEBUG_CLR_CLKGATE_SHIFT           (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_DEBUG_CLR_CLKGATE(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_CLR_CLKGATE_SHIFT)) & USBPHY_DEBUG_CLR_CLKGATE_MASK)
/*! @} */

/*! @name DEBUG_TOG - USB PHY Debug Register */
/*! @{ */

#define USBPHY_DEBUG_TOG_OTGIDPIOLOCK_MASK       (0x1U)
#define USBPHY_DEBUG_TOG_OTGIDPIOLOCK_SHIFT      (0U)
/*! OTGIDPIOLOCK - OTGIDPIOLOCK */
#define USBPHY_DEBUG_TOG_OTGIDPIOLOCK(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_OTGIDPIOLOCK_SHIFT)) & USBPHY_DEBUG_TOG_OTGIDPIOLOCK_MASK)

#define USBPHY_DEBUG_TOG_DEBUG_INTERFACE_HOLD_MASK (0x2U)
#define USBPHY_DEBUG_TOG_DEBUG_INTERFACE_HOLD_SHIFT (1U)
/*! DEBUG_INTERFACE_HOLD - DEBUG_INTERFACE_HOLD */
#define USBPHY_DEBUG_TOG_DEBUG_INTERFACE_HOLD(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_DEBUG_INTERFACE_HOLD_SHIFT)) & USBPHY_DEBUG_TOG_DEBUG_INTERFACE_HOLD_MASK)

#define USBPHY_DEBUG_TOG_HSTPULLDOWN_MASK        (0xCU)
#define USBPHY_DEBUG_TOG_HSTPULLDOWN_SHIFT       (2U)
/*! HSTPULLDOWN - HSTPULLDOWN */
#define USBPHY_DEBUG_TOG_HSTPULLDOWN(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_HSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_TOG_HSTPULLDOWN_MASK)

#define USBPHY_DEBUG_TOG_ENHSTPULLDOWN_MASK      (0x30U)
#define USBPHY_DEBUG_TOG_ENHSTPULLDOWN_SHIFT     (4U)
/*! ENHSTPULLDOWN - ENHSTPULLDOWN */
#define USBPHY_DEBUG_TOG_ENHSTPULLDOWN(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_ENHSTPULLDOWN_SHIFT)) & USBPHY_DEBUG_TOG_ENHSTPULLDOWN_MASK)

#define USBPHY_DEBUG_TOG_TX2RXCOUNT_MASK         (0xF00U)
#define USBPHY_DEBUG_TOG_TX2RXCOUNT_SHIFT        (8U)
/*! TX2RXCOUNT - TX2RXCOUNT */
#define USBPHY_DEBUG_TOG_TX2RXCOUNT(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_TX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_TOG_TX2RXCOUNT_MASK)

#define USBPHY_DEBUG_TOG_ENTX2RXCOUNT_MASK       (0x1000U)
#define USBPHY_DEBUG_TOG_ENTX2RXCOUNT_SHIFT      (12U)
/*! ENTX2RXCOUNT - ENTX2RXCOUNT */
#define USBPHY_DEBUG_TOG_ENTX2RXCOUNT(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_ENTX2RXCOUNT_SHIFT)) & USBPHY_DEBUG_TOG_ENTX2RXCOUNT_MASK)

#define USBPHY_DEBUG_TOG_SQUELCHRESETCOUNT_MASK  (0x1F0000U)
#define USBPHY_DEBUG_TOG_SQUELCHRESETCOUNT_SHIFT (16U)
/*! SQUELCHRESETCOUNT - SQUELCHRESETCOUNT */
#define USBPHY_DEBUG_TOG_SQUELCHRESETCOUNT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_SQUELCHRESETCOUNT_SHIFT)) & USBPHY_DEBUG_TOG_SQUELCHRESETCOUNT_MASK)

#define USBPHY_DEBUG_TOG_ENSQUELCHRESET_MASK     (0x1000000U)
#define USBPHY_DEBUG_TOG_ENSQUELCHRESET_SHIFT    (24U)
/*! ENSQUELCHRESET - ENSQUELCHRESET */
#define USBPHY_DEBUG_TOG_ENSQUELCHRESET(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_ENSQUELCHRESET_SHIFT)) & USBPHY_DEBUG_TOG_ENSQUELCHRESET_MASK)

#define USBPHY_DEBUG_TOG_SQUELCHRESETLENGTH_MASK (0x1E000000U)
#define USBPHY_DEBUG_TOG_SQUELCHRESETLENGTH_SHIFT (25U)
/*! SQUELCHRESETLENGTH - SQUELCHRESETLENGTH */
#define USBPHY_DEBUG_TOG_SQUELCHRESETLENGTH(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_SQUELCHRESETLENGTH_SHIFT)) & USBPHY_DEBUG_TOG_SQUELCHRESETLENGTH_MASK)

#define USBPHY_DEBUG_TOG_HOST_RESUME_DEBUG_MASK  (0x20000000U)
#define USBPHY_DEBUG_TOG_HOST_RESUME_DEBUG_SHIFT (29U)
/*! HOST_RESUME_DEBUG - HOST_RESUME_DEBUG */
#define USBPHY_DEBUG_TOG_HOST_RESUME_DEBUG(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_HOST_RESUME_DEBUG_SHIFT)) & USBPHY_DEBUG_TOG_HOST_RESUME_DEBUG_MASK)

#define USBPHY_DEBUG_TOG_CLKGATE_MASK            (0x40000000U)
#define USBPHY_DEBUG_TOG_CLKGATE_SHIFT           (30U)
/*! CLKGATE - CLKGATE */
#define USBPHY_DEBUG_TOG_CLKGATE(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG_TOG_CLKGATE_SHIFT)) & USBPHY_DEBUG_TOG_CLKGATE_MASK)
/*! @} */

/*! @name DEBUG0_STATUS - UTMI Debug Status Register 0 */
/*! @{ */

#define USBPHY_DEBUG0_STATUS_LOOP_BACK_FAIL_COUNT_MASK (0xFFFFU)
#define USBPHY_DEBUG0_STATUS_LOOP_BACK_FAIL_COUNT_SHIFT (0U)
/*! LOOP_BACK_FAIL_COUNT - LOOP_BACK_FAIL_COUNT */
#define USBPHY_DEBUG0_STATUS_LOOP_BACK_FAIL_COUNT(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG0_STATUS_LOOP_BACK_FAIL_COUNT_SHIFT)) & USBPHY_DEBUG0_STATUS_LOOP_BACK_FAIL_COUNT_MASK)

#define USBPHY_DEBUG0_STATUS_UTMI_RXERROR_FAIL_COUNT_MASK (0x3FF0000U)
#define USBPHY_DEBUG0_STATUS_UTMI_RXERROR_FAIL_COUNT_SHIFT (16U)
/*! UTMI_RXERROR_FAIL_COUNT - UTMI_RXERROR_FAIL_COUNT */
#define USBPHY_DEBUG0_STATUS_UTMI_RXERROR_FAIL_COUNT(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG0_STATUS_UTMI_RXERROR_FAIL_COUNT_SHIFT)) & USBPHY_DEBUG0_STATUS_UTMI_RXERROR_FAIL_COUNT_MASK)

#define USBPHY_DEBUG0_STATUS_SQUELCH_COUNT_MASK  (0xFC000000U)
#define USBPHY_DEBUG0_STATUS_SQUELCH_COUNT_SHIFT (26U)
/*! SQUELCH_COUNT - SQUELCH_COUNT */
#define USBPHY_DEBUG0_STATUS_SQUELCH_COUNT(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG0_STATUS_SQUELCH_COUNT_SHIFT)) & USBPHY_DEBUG0_STATUS_SQUELCH_COUNT_MASK)
/*! @} */

/*! @name DEBUG1 - UTMI Debug Status Register 1 */
/*! @{ */

#define USBPHY_DEBUG1_ENTAILADJVD_MASK           (0x6000U)
#define USBPHY_DEBUG1_ENTAILADJVD_SHIFT          (13U)
/*! ENTAILADJVD - ENTAILADJVD
 *  0b00..Delay is nominal
 *  0b01..Delay is +20%
 *  0b10..Delay is -20%
 *  0b11..Delay is -40%
 */
#define USBPHY_DEBUG1_ENTAILADJVD(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_ENTAILADJVD_SHIFT)) & USBPHY_DEBUG1_ENTAILADJVD_MASK)

#define USBPHY_DEBUG1_USB2_REFBIAS_SELFBIASOFF_MASK (0x8000U)
#define USBPHY_DEBUG1_USB2_REFBIAS_SELFBIASOFF_SHIFT (15U)
/*! USB2_REFBIAS_SELFBIASOFF - Set to 1 to disable self bias, 100 us after power up refbias(usb2_refbias_pwd).This can reduce noise on power. */
#define USBPHY_DEBUG1_USB2_REFBIAS_SELFBIASOFF(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_USB2_REFBIAS_SELFBIASOFF_SHIFT)) & USBPHY_DEBUG1_USB2_REFBIAS_SELFBIASOFF_MASK)

#define USBPHY_DEBUG1_USB2_REFBIAS_PWDVBGUP_MASK (0x10000U)
#define USBPHY_DEBUG1_USB2_REFBIAS_PWDVBGUP_SHIFT (16U)
/*! USB2_REFBIAS_PWDVBGUP - Powers down the bandgap detect logic, will affect vbgup on misc1 register. */
#define USBPHY_DEBUG1_USB2_REFBIAS_PWDVBGUP(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_USB2_REFBIAS_PWDVBGUP_SHIFT)) & USBPHY_DEBUG1_USB2_REFBIAS_PWDVBGUP_MASK)

#define USBPHY_DEBUG1_USB2_REFBIAS_LOWPWR_MASK   (0x20000U)
#define USBPHY_DEBUG1_USB2_REFBIAS_LOWPWR_SHIFT  (17U)
/*! USB2_REFBIAS_LOWPWR - to be added */
#define USBPHY_DEBUG1_USB2_REFBIAS_LOWPWR(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_USB2_REFBIAS_LOWPWR_SHIFT)) & USBPHY_DEBUG1_USB2_REFBIAS_LOWPWR_MASK)

#define USBPHY_DEBUG1_USB2_REFBIAS_VBGADJ_MASK   (0x1C0000U)
#define USBPHY_DEBUG1_USB2_REFBIAS_VBGADJ_SHIFT  (18U)
/*! USB2_REFBIAS_VBGADJ - Adjustment bits on bandgap */
#define USBPHY_DEBUG1_USB2_REFBIAS_VBGADJ(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_DEBUG1_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_DEBUG1_USB2_REFBIAS_TST_MASK      (0x600000U)
#define USBPHY_DEBUG1_USB2_REFBIAS_TST_SHIFT     (21U)
/*! USB2_REFBIAS_TST - Bias current control for usb2_phy */
#define USBPHY_DEBUG1_USB2_REFBIAS_TST(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_USB2_REFBIAS_TST_SHIFT)) & USBPHY_DEBUG1_USB2_REFBIAS_TST_MASK)
/*! @} */

/*! @name DEBUG1_SET - UTMI Debug Status Register 1 */
/*! @{ */

#define USBPHY_DEBUG1_SET_ENTAILADJVD_MASK       (0x6000U)
#define USBPHY_DEBUG1_SET_ENTAILADJVD_SHIFT      (13U)
/*! ENTAILADJVD - ENTAILADJVD */
#define USBPHY_DEBUG1_SET_ENTAILADJVD(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_SET_ENTAILADJVD_SHIFT)) & USBPHY_DEBUG1_SET_ENTAILADJVD_MASK)

#define USBPHY_DEBUG1_SET_USB2_REFBIAS_SELFBIASOFF_MASK (0x8000U)
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_SELFBIASOFF_SHIFT (15U)
/*! USB2_REFBIAS_SELFBIASOFF - Set to 1 to disable self bias, 100 us after power up refbias(usb2_refbias_pwd).This can reduce noise on power. */
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_SELFBIASOFF(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_SET_USB2_REFBIAS_SELFBIASOFF_SHIFT)) & USBPHY_DEBUG1_SET_USB2_REFBIAS_SELFBIASOFF_MASK)

#define USBPHY_DEBUG1_SET_USB2_REFBIAS_PWDVBGUP_MASK (0x10000U)
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_PWDVBGUP_SHIFT (16U)
/*! USB2_REFBIAS_PWDVBGUP - Powers down the bandgap detect logic, will affect vbgup on misc1 register. */
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_PWDVBGUP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_SET_USB2_REFBIAS_PWDVBGUP_SHIFT)) & USBPHY_DEBUG1_SET_USB2_REFBIAS_PWDVBGUP_MASK)

#define USBPHY_DEBUG1_SET_USB2_REFBIAS_LOWPWR_MASK (0x20000U)
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_LOWPWR_SHIFT (17U)
/*! USB2_REFBIAS_LOWPWR - to be added */
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_LOWPWR(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_SET_USB2_REFBIAS_LOWPWR_SHIFT)) & USBPHY_DEBUG1_SET_USB2_REFBIAS_LOWPWR_MASK)

#define USBPHY_DEBUG1_SET_USB2_REFBIAS_VBGADJ_MASK (0x1C0000U)
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_VBGADJ_SHIFT (18U)
/*! USB2_REFBIAS_VBGADJ - Adjustment bits on bandgap */
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_SET_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_DEBUG1_SET_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_DEBUG1_SET_USB2_REFBIAS_TST_MASK  (0x600000U)
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_TST_SHIFT (21U)
/*! USB2_REFBIAS_TST - Bias current control for usb2_phy */
#define USBPHY_DEBUG1_SET_USB2_REFBIAS_TST(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_SET_USB2_REFBIAS_TST_SHIFT)) & USBPHY_DEBUG1_SET_USB2_REFBIAS_TST_MASK)
/*! @} */

/*! @name DEBUG1_CLR - UTMI Debug Status Register 1 */
/*! @{ */

#define USBPHY_DEBUG1_CLR_ENTAILADJVD_MASK       (0x6000U)
#define USBPHY_DEBUG1_CLR_ENTAILADJVD_SHIFT      (13U)
/*! ENTAILADJVD - ENTAILADJVD */
#define USBPHY_DEBUG1_CLR_ENTAILADJVD(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_CLR_ENTAILADJVD_SHIFT)) & USBPHY_DEBUG1_CLR_ENTAILADJVD_MASK)

#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_SELFBIASOFF_MASK (0x8000U)
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_SELFBIASOFF_SHIFT (15U)
/*! USB2_REFBIAS_SELFBIASOFF - Set to 1 to disable self bias, 100 us after power up refbias(usb2_refbias_pwd).This can reduce noise on power. */
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_SELFBIASOFF(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_CLR_USB2_REFBIAS_SELFBIASOFF_SHIFT)) & USBPHY_DEBUG1_CLR_USB2_REFBIAS_SELFBIASOFF_MASK)

#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_PWDVBGUP_MASK (0x10000U)
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_PWDVBGUP_SHIFT (16U)
/*! USB2_REFBIAS_PWDVBGUP - Powers down the bandgap detect logic, will affect vbgup on misc1 register. */
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_PWDVBGUP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_CLR_USB2_REFBIAS_PWDVBGUP_SHIFT)) & USBPHY_DEBUG1_CLR_USB2_REFBIAS_PWDVBGUP_MASK)

#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_LOWPWR_MASK (0x20000U)
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_LOWPWR_SHIFT (17U)
/*! USB2_REFBIAS_LOWPWR - to be added */
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_LOWPWR(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_CLR_USB2_REFBIAS_LOWPWR_SHIFT)) & USBPHY_DEBUG1_CLR_USB2_REFBIAS_LOWPWR_MASK)

#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_VBGADJ_MASK (0x1C0000U)
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_VBGADJ_SHIFT (18U)
/*! USB2_REFBIAS_VBGADJ - Adjustment bits on bandgap */
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_CLR_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_DEBUG1_CLR_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_TST_MASK  (0x600000U)
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_TST_SHIFT (21U)
/*! USB2_REFBIAS_TST - Bias current control for usb2_phy */
#define USBPHY_DEBUG1_CLR_USB2_REFBIAS_TST(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_CLR_USB2_REFBIAS_TST_SHIFT)) & USBPHY_DEBUG1_CLR_USB2_REFBIAS_TST_MASK)
/*! @} */

/*! @name DEBUG1_TOG - UTMI Debug Status Register 1 */
/*! @{ */

#define USBPHY_DEBUG1_TOG_ENTAILADJVD_MASK       (0x6000U)
#define USBPHY_DEBUG1_TOG_ENTAILADJVD_SHIFT      (13U)
/*! ENTAILADJVD - ENTAILADJVD */
#define USBPHY_DEBUG1_TOG_ENTAILADJVD(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_TOG_ENTAILADJVD_SHIFT)) & USBPHY_DEBUG1_TOG_ENTAILADJVD_MASK)

#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_SELFBIASOFF_MASK (0x8000U)
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_SELFBIASOFF_SHIFT (15U)
/*! USB2_REFBIAS_SELFBIASOFF - Set to 1 to disable self bias, 100 us after power up refbias(usb2_refbias_pwd).This can reduce noise on power. */
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_SELFBIASOFF(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_TOG_USB2_REFBIAS_SELFBIASOFF_SHIFT)) & USBPHY_DEBUG1_TOG_USB2_REFBIAS_SELFBIASOFF_MASK)

#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_PWDVBGUP_MASK (0x10000U)
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_PWDVBGUP_SHIFT (16U)
/*! USB2_REFBIAS_PWDVBGUP - Powers down the bandgap detect logic, will affect vbgup on misc1 register. */
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_PWDVBGUP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_TOG_USB2_REFBIAS_PWDVBGUP_SHIFT)) & USBPHY_DEBUG1_TOG_USB2_REFBIAS_PWDVBGUP_MASK)

#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_LOWPWR_MASK (0x20000U)
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_LOWPWR_SHIFT (17U)
/*! USB2_REFBIAS_LOWPWR - to be added */
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_LOWPWR(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_TOG_USB2_REFBIAS_LOWPWR_SHIFT)) & USBPHY_DEBUG1_TOG_USB2_REFBIAS_LOWPWR_MASK)

#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_VBGADJ_MASK (0x1C0000U)
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_VBGADJ_SHIFT (18U)
/*! USB2_REFBIAS_VBGADJ - Adjustment bits on bandgap */
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_TOG_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_DEBUG1_TOG_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_TST_MASK  (0x600000U)
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_TST_SHIFT (21U)
/*! USB2_REFBIAS_TST - Bias current control for usb2_phy */
#define USBPHY_DEBUG1_TOG_USB2_REFBIAS_TST(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_DEBUG1_TOG_USB2_REFBIAS_TST_SHIFT)) & USBPHY_DEBUG1_TOG_USB2_REFBIAS_TST_MASK)
/*! @} */

/*! @name VERSION - UTMI RTL Version */
/*! @{ */

#define USBPHY_VERSION_STEP_MASK                 (0xFFFFU)
#define USBPHY_VERSION_STEP_SHIFT                (0U)
/*! STEP - STEP */
#define USBPHY_VERSION_STEP(x)                   (((uint32_t)(((uint32_t)(x)) << USBPHY_VERSION_STEP_SHIFT)) & USBPHY_VERSION_STEP_MASK)

#define USBPHY_VERSION_MINOR_MASK                (0xFF0000U)
#define USBPHY_VERSION_MINOR_SHIFT               (16U)
/*! MINOR - MINOR */
#define USBPHY_VERSION_MINOR(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_VERSION_MINOR_SHIFT)) & USBPHY_VERSION_MINOR_MASK)

#define USBPHY_VERSION_MAJOR_MASK                (0xFF000000U)
#define USBPHY_VERSION_MAJOR_SHIFT               (24U)
/*! MAJOR - MAJOR */
#define USBPHY_VERSION_MAJOR(x)                  (((uint32_t)(((uint32_t)(x)) << USBPHY_VERSION_MAJOR_SHIFT)) & USBPHY_VERSION_MAJOR_MASK)
/*! @} */

/*! @name PLL_SIC - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_PLL_POSTDIV_MASK          (0x1CU)
#define USBPHY_PLL_SIC_PLL_POSTDIV_SHIFT         (2U)
/*! PLL_POSTDIV - PLL_POSTDIV */
#define USBPHY_PLL_SIC_PLL_POSTDIV(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_POSTDIV_SHIFT)) & USBPHY_PLL_SIC_PLL_POSTDIV_MASK)

#define USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK      (0x40U)
#define USBPHY_PLL_SIC_PLL_EN_USB_CLKS_SHIFT     (6U)
/*! PLL_EN_USB_CLKS - PLL_EN_USB_CLKS */
#define USBPHY_PLL_SIC_PLL_EN_USB_CLKS(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_PLL_POWER_MASK            (0x1000U)
#define USBPHY_PLL_SIC_PLL_POWER_SHIFT           (12U)
/*! PLL_POWER - PLL_POWER */
#define USBPHY_PLL_SIC_PLL_POWER(x)              (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_PLL_ENABLE_MASK           (0x2000U)
#define USBPHY_PLL_SIC_PLL_ENABLE_SHIFT          (13U)
/*! PLL_ENABLE - PLL_ENABLE */
#define USBPHY_PLL_SIC_PLL_ENABLE(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_PLL_BYPASS_MASK           (0x10000U)
#define USBPHY_PLL_SIC_PLL_BYPASS_SHIFT          (16U)
/*! PLL_BYPASS - PLL_BYPASS */
#define USBPHY_PLL_SIC_PLL_BYPASS(x)             (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_BYPASS_SHIFT)) & USBPHY_PLL_SIC_PLL_BYPASS_MASK)

#define USBPHY_PLL_SIC_REFBIAS_PWD_SEL_MASK      (0x80000U)
#define USBPHY_PLL_SIC_REFBIAS_PWD_SEL_SHIFT     (19U)
/*! REFBIAS_PWD_SEL - REFBIAS_PWD_SEL
 *  0b0..Selects PLL_POWER to control the reference bias
 *  0b1..Selects REFBIAS_PWD to control the reference bias.
 */
#define USBPHY_PLL_SIC_REFBIAS_PWD_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_REFBIAS_PWD_MASK          (0x100000U)
#define USBPHY_PLL_SIC_REFBIAS_PWD_SHIFT         (20U)
/*! REFBIAS_PWD - Power down the reference bias */
#define USBPHY_PLL_SIC_REFBIAS_PWD(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK       (0x200000U)
#define USBPHY_PLL_SIC_PLL_REG_ENABLE_SHIFT      (21U)
/*! PLL_REG_ENABLE - PLL_REG_ENABLE */
#define USBPHY_PLL_SIC_PLL_REG_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_PLL_DIV_SEL_MASK          (0x1C00000U)
#define USBPHY_PLL_SIC_PLL_DIV_SEL_SHIFT         (22U)
/*! PLL_DIV_SEL - PLL_DIV_SEL
 *  0b000..Divide by 13
 *  0b001..Divide by 15
 *  0b010..Divide by 16
 *  0b011..Divide by 20
 *  0b100..Divide by 22
 *  0b101..Divide by 25
 *  0b110..Divide by 30
 *  0b111..Divide by 240
 */
#define USBPHY_PLL_SIC_PLL_DIV_SEL(x)            (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_PLL_LOCK_MASK             (0x80000000U)
#define USBPHY_PLL_SIC_PLL_LOCK_SHIFT            (31U)
/*! PLL_LOCK - PLL_LOCK
 *  0b0..PLL is not currently locked
 *  0b1..PLL is currently locked
 */
#define USBPHY_PLL_SIC_PLL_LOCK(x)               (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_PLL_LOCK_MASK)
/*! @} */

/*! @name PLL_SIC_SET - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_SET_PLL_POSTDIV_MASK      (0x1CU)
#define USBPHY_PLL_SIC_SET_PLL_POSTDIV_SHIFT     (2U)
/*! PLL_POSTDIV - PLL_POSTDIV */
#define USBPHY_PLL_SIC_SET_PLL_POSTDIV(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_POSTDIV_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_POSTDIV_MASK)

#define USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_MASK  (0x40U)
#define USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_SHIFT (6U)
/*! PLL_EN_USB_CLKS - PLL_EN_USB_CLKS */
#define USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_SET_PLL_POWER_MASK        (0x1000U)
#define USBPHY_PLL_SIC_SET_PLL_POWER_SHIFT       (12U)
/*! PLL_POWER - PLL_POWER */
#define USBPHY_PLL_SIC_SET_PLL_POWER(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_SET_PLL_ENABLE_MASK       (0x2000U)
#define USBPHY_PLL_SIC_SET_PLL_ENABLE_SHIFT      (13U)
/*! PLL_ENABLE - PLL_ENABLE */
#define USBPHY_PLL_SIC_SET_PLL_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_SET_PLL_BYPASS_MASK       (0x10000U)
#define USBPHY_PLL_SIC_SET_PLL_BYPASS_SHIFT      (16U)
/*! PLL_BYPASS - PLL_BYPASS */
#define USBPHY_PLL_SIC_SET_PLL_BYPASS(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_BYPASS_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_BYPASS_MASK)

#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_MASK  (0x80000U)
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_SHIFT (19U)
/*! REFBIAS_PWD_SEL - REFBIAS_PWD_SEL */
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_SET_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_MASK      (0x100000U)
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD_SHIFT     (20U)
/*! REFBIAS_PWD - Power down the reference bias */
#define USBPHY_PLL_SIC_SET_REFBIAS_PWD(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_SET_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_MASK   (0x200000U)
#define USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_SHIFT  (21U)
/*! PLL_REG_ENABLE - PLL_REG_ENABLE */
#define USBPHY_PLL_SIC_SET_PLL_REG_ENABLE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_SET_PLL_DIV_SEL_MASK      (0x1C00000U)
#define USBPHY_PLL_SIC_SET_PLL_DIV_SEL_SHIFT     (22U)
/*! PLL_DIV_SEL - PLL_DIV_SEL */
#define USBPHY_PLL_SIC_SET_PLL_DIV_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_SET_PLL_LOCK_MASK         (0x80000000U)
#define USBPHY_PLL_SIC_SET_PLL_LOCK_SHIFT        (31U)
/*! PLL_LOCK - PLL_LOCK */
#define USBPHY_PLL_SIC_SET_PLL_LOCK(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_SET_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_SET_PLL_LOCK_MASK)
/*! @} */

/*! @name PLL_SIC_CLR - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_CLR_PLL_POSTDIV_MASK      (0x1CU)
#define USBPHY_PLL_SIC_CLR_PLL_POSTDIV_SHIFT     (2U)
/*! PLL_POSTDIV - PLL_POSTDIV */
#define USBPHY_PLL_SIC_CLR_PLL_POSTDIV(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_POSTDIV_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_POSTDIV_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_MASK  (0x40U)
#define USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_SHIFT (6U)
/*! PLL_EN_USB_CLKS - PLL_EN_USB_CLKS */
#define USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_POWER_MASK        (0x1000U)
#define USBPHY_PLL_SIC_CLR_PLL_POWER_SHIFT       (12U)
/*! PLL_POWER - PLL_POWER */
#define USBPHY_PLL_SIC_CLR_PLL_POWER(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_ENABLE_MASK       (0x2000U)
#define USBPHY_PLL_SIC_CLR_PLL_ENABLE_SHIFT      (13U)
/*! PLL_ENABLE - PLL_ENABLE */
#define USBPHY_PLL_SIC_CLR_PLL_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_BYPASS_MASK       (0x10000U)
#define USBPHY_PLL_SIC_CLR_PLL_BYPASS_SHIFT      (16U)
/*! PLL_BYPASS - PLL_BYPASS */
#define USBPHY_PLL_SIC_CLR_PLL_BYPASS(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_BYPASS_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_BYPASS_MASK)

#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_MASK  (0x80000U)
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_SHIFT (19U)
/*! REFBIAS_PWD_SEL - REFBIAS_PWD_SEL */
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_MASK      (0x100000U)
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SHIFT     (20U)
/*! REFBIAS_PWD - Power down the reference bias */
#define USBPHY_PLL_SIC_CLR_REFBIAS_PWD(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_CLR_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_MASK   (0x200000U)
#define USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_SHIFT  (21U)
/*! PLL_REG_ENABLE - PLL_REG_ENABLE */
#define USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_MASK      (0x1C00000U)
#define USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_SHIFT     (22U)
/*! PLL_DIV_SEL - PLL_DIV_SEL */
#define USBPHY_PLL_SIC_CLR_PLL_DIV_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_CLR_PLL_LOCK_MASK         (0x80000000U)
#define USBPHY_PLL_SIC_CLR_PLL_LOCK_SHIFT        (31U)
/*! PLL_LOCK - PLL_LOCK */
#define USBPHY_PLL_SIC_CLR_PLL_LOCK(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_CLR_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_CLR_PLL_LOCK_MASK)
/*! @} */

/*! @name PLL_SIC_TOG - USB PHY PLL Control/Status Register */
/*! @{ */

#define USBPHY_PLL_SIC_TOG_PLL_POSTDIV_MASK      (0x1CU)
#define USBPHY_PLL_SIC_TOG_PLL_POSTDIV_SHIFT     (2U)
/*! PLL_POSTDIV - PLL_POSTDIV */
#define USBPHY_PLL_SIC_TOG_PLL_POSTDIV(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_POSTDIV_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_POSTDIV_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_MASK  (0x40U)
#define USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_SHIFT (6U)
/*! PLL_EN_USB_CLKS - PLL_EN_USB_CLKS */
#define USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_EN_USB_CLKS_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_POWER_MASK        (0x1000U)
#define USBPHY_PLL_SIC_TOG_PLL_POWER_SHIFT       (12U)
/*! PLL_POWER - PLL_POWER */
#define USBPHY_PLL_SIC_TOG_PLL_POWER(x)          (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_POWER_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_POWER_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_ENABLE_MASK       (0x2000U)
#define USBPHY_PLL_SIC_TOG_PLL_ENABLE_SHIFT      (13U)
/*! PLL_ENABLE - PLL_ENABLE */
#define USBPHY_PLL_SIC_TOG_PLL_ENABLE(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_ENABLE_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_ENABLE_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_BYPASS_MASK       (0x10000U)
#define USBPHY_PLL_SIC_TOG_PLL_BYPASS_SHIFT      (16U)
/*! PLL_BYPASS - PLL_BYPASS */
#define USBPHY_PLL_SIC_TOG_PLL_BYPASS(x)         (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_BYPASS_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_BYPASS_MASK)

#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_MASK  (0x80000U)
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_SHIFT (19U)
/*! REFBIAS_PWD_SEL - REFBIAS_PWD_SEL */
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_SHIFT)) & USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SEL_MASK)

#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_MASK      (0x100000U)
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SHIFT     (20U)
/*! REFBIAS_PWD - Power down the reference bias */
#define USBPHY_PLL_SIC_TOG_REFBIAS_PWD(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_REFBIAS_PWD_SHIFT)) & USBPHY_PLL_SIC_TOG_REFBIAS_PWD_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_MASK   (0x200000U)
#define USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_SHIFT  (21U)
/*! PLL_REG_ENABLE - PLL_REG_ENABLE */
#define USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_REG_ENABLE_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_MASK      (0x1C00000U)
#define USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_SHIFT     (22U)
/*! PLL_DIV_SEL - PLL_DIV_SEL */
#define USBPHY_PLL_SIC_TOG_PLL_DIV_SEL(x)        (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_DIV_SEL_MASK)

#define USBPHY_PLL_SIC_TOG_PLL_LOCK_MASK         (0x80000000U)
#define USBPHY_PLL_SIC_TOG_PLL_LOCK_SHIFT        (31U)
/*! PLL_LOCK - PLL_LOCK */
#define USBPHY_PLL_SIC_TOG_PLL_LOCK(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_PLL_SIC_TOG_PLL_LOCK_SHIFT)) & USBPHY_PLL_SIC_TOG_PLL_LOCK_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH - VBUSVALID_THRESH
 *  0b000..4.0 V
 *  0b001..4.1 V
 *  0b010..4.2 V
 *  0b011..4.3 V
 *  0b100..4.4 V (Default)
 *  0b101..4.5 V
 *  0b110..4.6 V
 *  0b111..4.7 V
 */
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN - VBUS detect signal override enable
 *  0b0..Use the results of the internal VBUS_VALID and Session Valid comparators for VBUS_VALID, AVALID, BVALID, and SESSEND (Default)
 *  0b1..Use the override values for VBUS_VALID, AVALID, BVALID, and SESSEND
 */
#define USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_SHIFT (4U)
/*! SESSEND_OVERRIDE - Override value for SESSEND */
#define USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_SHIFT (5U)
/*! BVALID_OVERRIDE - Override value for B-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_SHIFT (6U)
/*! AVALID_OVERRIDE - Override value for A-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_SHIFT (7U)
/*! VBUSVALID_OVERRIDE - Override value for VBUS_VALID signal sent to USB controller */
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller
 *  0b0..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b1..Use the VBUS_VALID_3V detector results for signal reported to the USB controller
 */
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller
 *  0b00..Use the VBUS_VALID comparator results for signal reported to the USB controller (Default)
 *  0b01..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b10..Use the Session Valid comparator results for signal reported to the USB controller
 *  0b11..Reserved, do not use
 */
#define USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_SHIFT (11U)
/*! ID_OVERRIDE_EN - TBA */
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_SHIFT (12U)
/*! ID_OVERRIDE - TBA */
#define USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID - Selects the comparator used for VBUS_VALID
 *  0b0..Use the VBUS_VALID comparator for VBUS_VALID results
 *  0b1..Use the Session End comparator for VBUS_VALID results. The Session End threshold is >0.8V and <4.0V.
 */
#define USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_MASK  (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS - Enables the VBUS_VALID comparator
 *  0b000..Powers down the VBUS_VALID comparator
 *  0b001..Enables the SESS_VALID comparator (default)
 *  0b010..Enables the 3Vdetect (default)
 */
#define USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS - Controls VBUS discharge resistor
 *  0b0..VBUS discharge resistor is disabled (Default)
 *  0b1..VBUS discharge resistor is enabled
 */
#define USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_DISCHARGE_VBUS_MASK)

#define USBPHY_USB1_VBUS_DETECT_EN_CHARGER_RESISTOR_MASK (0x80000000U)
#define USBPHY_USB1_VBUS_DETECT_EN_CHARGER_RESISTOR_SHIFT (31U)
/*! EN_CHARGER_RESISTOR - Enables resistors used for an older method of resistive battery charger detection
 *  0b0..Disable resistive charger detection resistors on DP and DP
 *  0b1..Enable resistive charger detection resistors on DP and DP
 */
#define USBPHY_USB1_VBUS_DETECT_EN_CHARGER_RESISTOR(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_EN_CHARGER_RESISTOR_SHIFT)) & USBPHY_USB1_VBUS_DETECT_EN_CHARGER_RESISTOR_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT_SET - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH - VBUSVALID_THRESH */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN - VBUS detect signal override enable */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_SHIFT (4U)
/*! SESSEND_OVERRIDE - Override value for SESSEND */
#define USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_SHIFT (5U)
/*! BVALID_OVERRIDE - Override value for B-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_SHIFT (6U)
/*! AVALID_OVERRIDE - Override value for A-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_SHIFT (7U)
/*! VBUSVALID_OVERRIDE - Override value for VBUS_VALID signal sent to USB controller */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_SHIFT (11U)
/*! ID_OVERRIDE_EN - TBA */
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_SHIFT (12U)
/*! ID_OVERRIDE - TBA */
#define USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID - Selects the comparator used for VBUS_VALID */
#define USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_MASK (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS - Enables the VBUS_VALID comparator */
#define USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS - Controls VBUS discharge resistor */
#define USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_DISCHARGE_VBUS_MASK)

#define USBPHY_USB1_VBUS_DETECT_SET_EN_CHARGER_RESISTOR_MASK (0x80000000U)
#define USBPHY_USB1_VBUS_DETECT_SET_EN_CHARGER_RESISTOR_SHIFT (31U)
/*! EN_CHARGER_RESISTOR - Enables resistors used for an older method of resistive battery charger detection */
#define USBPHY_USB1_VBUS_DETECT_SET_EN_CHARGER_RESISTOR(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_SET_EN_CHARGER_RESISTOR_SHIFT)) & USBPHY_USB1_VBUS_DETECT_SET_EN_CHARGER_RESISTOR_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT_CLR - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH - VBUSVALID_THRESH */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN - VBUS detect signal override enable */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_SHIFT (4U)
/*! SESSEND_OVERRIDE - Override value for SESSEND */
#define USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_SHIFT (5U)
/*! BVALID_OVERRIDE - Override value for B-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_SHIFT (6U)
/*! AVALID_OVERRIDE - Override value for A-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_SHIFT (7U)
/*! VBUSVALID_OVERRIDE - Override value for VBUS_VALID signal sent to USB controller */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_SHIFT (11U)
/*! ID_OVERRIDE_EN - TBA */
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_SHIFT (12U)
/*! ID_OVERRIDE - TBA */
#define USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID - Selects the comparator used for VBUS_VALID */
#define USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_MASK (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS - Enables the VBUS_VALID comparator */
#define USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS - Controls VBUS discharge resistor */
#define USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_DISCHARGE_VBUS_MASK)

#define USBPHY_USB1_VBUS_DETECT_CLR_EN_CHARGER_RESISTOR_MASK (0x80000000U)
#define USBPHY_USB1_VBUS_DETECT_CLR_EN_CHARGER_RESISTOR_SHIFT (31U)
/*! EN_CHARGER_RESISTOR - Enables resistors used for an older method of resistive battery charger detection */
#define USBPHY_USB1_VBUS_DETECT_CLR_EN_CHARGER_RESISTOR(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_CLR_EN_CHARGER_RESISTOR_SHIFT)) & USBPHY_USB1_VBUS_DETECT_CLR_EN_CHARGER_RESISTOR_MASK)
/*! @} */

/*! @name USB1_VBUS_DETECT_TOG - USB PHY VBUS Detect Control Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_MASK (0x7U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_SHIFT (0U)
/*! VBUSVALID_THRESH - VBUSVALID_THRESH */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_THRESH_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_MASK (0x8U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_SHIFT (3U)
/*! VBUS_OVERRIDE_EN - VBUS detect signal override enable */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUS_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_MASK (0x10U)
#define USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_SHIFT (4U)
/*! SESSEND_OVERRIDE - Override value for SESSEND */
#define USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_SESSEND_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_MASK (0x20U)
#define USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_SHIFT (5U)
/*! BVALID_OVERRIDE - Override value for B-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_BVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_MASK (0x40U)
#define USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_SHIFT (6U)
/*! AVALID_OVERRIDE - Override value for A-Device Session Valid */
#define USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_AVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_MASK (0x80U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_SHIFT (7U)
/*! VBUSVALID_OVERRIDE - Override value for VBUS_VALID signal sent to USB controller */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_MASK (0x100U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_SHIFT (8U)
/*! VBUSVALID_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_MASK (0x600U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_SHIFT (9U)
/*! VBUS_SOURCE_SEL - Selects the source of the VBUS_VALID signal reported to the USB controller */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUS_SOURCE_SEL_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_MASK (0x800U)
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_SHIFT (11U)
/*! ID_OVERRIDE_EN - TBA */
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_EN_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_MASK (0x1000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_SHIFT (12U)
/*! ID_OVERRIDE - TBA */
#define USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_ID_OVERRIDE_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_MASK (0x40000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_SHIFT (18U)
/*! VBUSVALID_TO_SESSVALID - Selects the comparator used for VBUS_VALID */
#define USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_VBUSVALID_TO_SESSVALID_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_MASK (0x700000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_SHIFT (20U)
/*! PWRUP_CMPS - Enables the VBUS_VALID comparator */
#define USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_PWRUP_CMPS_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_MASK (0x4000000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_SHIFT (26U)
/*! DISCHARGE_VBUS - Controls VBUS discharge resistor */
#define USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_DISCHARGE_VBUS_MASK)

#define USBPHY_USB1_VBUS_DETECT_TOG_EN_CHARGER_RESISTOR_MASK (0x80000000U)
#define USBPHY_USB1_VBUS_DETECT_TOG_EN_CHARGER_RESISTOR_SHIFT (31U)
/*! EN_CHARGER_RESISTOR - Enables resistors used for an older method of resistive battery charger detection */
#define USBPHY_USB1_VBUS_DETECT_TOG_EN_CHARGER_RESISTOR(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DETECT_TOG_EN_CHARGER_RESISTOR_SHIFT)) & USBPHY_USB1_VBUS_DETECT_TOG_EN_CHARGER_RESISTOR_MASK)
/*! @} */

/*! @name USB1_VBUS_DET_STAT - USB PHY VBUS Detector Status Register */
/*! @{ */

#define USBPHY_USB1_VBUS_DET_STAT_SESSEND_MASK   (0x1U)
#define USBPHY_USB1_VBUS_DET_STAT_SESSEND_SHIFT  (0U)
/*! SESSEND - Session End indicator
 *  0b0..The VBUS voltage is above the Session Valid threshold
 *  0b1..The VBUS voltage is below the Session Valid threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_SESSEND(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_SESSEND_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_SESSEND_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_BVALID_MASK    (0x2U)
#define USBPHY_USB1_VBUS_DET_STAT_BVALID_SHIFT   (1U)
/*! BVALID - B-Device Session Valid status
 *  0b0..The VBUS voltage is below the Session Valid threshold
 *  0b1..The VBUS voltage is above the Session Valid threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_BVALID(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_BVALID_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_BVALID_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_AVALID_MASK    (0x4U)
#define USBPHY_USB1_VBUS_DET_STAT_AVALID_SHIFT   (2U)
/*! AVALID - A-Device Session Valid status
 *  0b0..The VBUS voltage is below the Session Valid threshold
 *  0b1..The VBUS voltage is above the Session Valid threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_AVALID(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_AVALID_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_AVALID_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_MASK (0x8U)
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_SHIFT (3U)
/*! VBUS_VALID - VBUS voltage status
 *  0b0..VBUS is below the comparator threshold
 *  0b1..VBUS is above the comparator threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_MASK)

#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_MASK (0x10U)
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_SHIFT (4U)
/*! VBUS_VALID_3V - VBUS_VALID_3V detector status
 *  0b0..VBUS voltage is below VBUS_VALID_3V threshold
 *  0b1..VBUS voltage is above VBUS_VALID_3V threshold
 */
#define USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_SHIFT)) & USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_MASK)
/*! @} */

/*! @name USB1_CHRG_DETECT - USB PHY Charger Detect Control Register */
/*! @{ */

#define USBPHY_USB1_CHRG_DETECT_PULLUP_DP_MASK   (0x4U)
#define USBPHY_USB1_CHRG_DETECT_PULLUP_DP_SHIFT  (2U)
/*! PULLUP_DP - PULLUP_DP */
#define USBPHY_USB1_CHRG_DETECT_PULLUP_DP(x)     (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_PULLUP_DP_SHIFT)) & USBPHY_USB1_CHRG_DETECT_PULLUP_DP_MASK)

#define USBPHY_USB1_CHRG_DETECT_BGR_BIAS_MASK    (0x800000U)
#define USBPHY_USB1_CHRG_DETECT_BGR_BIAS_SHIFT   (23U)
/*! BGR_BIAS - BGR_BIAS
 *  0b0..Use local bias powered from USB1_VBUS for 10uA reference (Default)
 *  0b1..Use bandgap bias powered from VREGIN0/VREGIN1 for 10uA reference
 */
#define USBPHY_USB1_CHRG_DETECT_BGR_BIAS(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_BGR_BIAS_SHIFT)) & USBPHY_USB1_CHRG_DETECT_BGR_BIAS_MASK)
/*! @} */

/*! @name USB1_CHRG_DETECT_SET - USB PHY Charger Detect Control Register */
/*! @{ */

#define USBPHY_USB1_CHRG_DETECT_SET_PULLUP_DP_MASK (0x4U)
#define USBPHY_USB1_CHRG_DETECT_SET_PULLUP_DP_SHIFT (2U)
/*! PULLUP_DP - PULLUP_DP */
#define USBPHY_USB1_CHRG_DETECT_SET_PULLUP_DP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_SET_PULLUP_DP_SHIFT)) & USBPHY_USB1_CHRG_DETECT_SET_PULLUP_DP_MASK)

#define USBPHY_USB1_CHRG_DETECT_SET_BGR_BIAS_MASK (0x800000U)
#define USBPHY_USB1_CHRG_DETECT_SET_BGR_BIAS_SHIFT (23U)
/*! BGR_BIAS - BGR_BIAS */
#define USBPHY_USB1_CHRG_DETECT_SET_BGR_BIAS(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_SET_BGR_BIAS_SHIFT)) & USBPHY_USB1_CHRG_DETECT_SET_BGR_BIAS_MASK)
/*! @} */

/*! @name USB1_CHRG_DETECT_CLR - USB PHY Charger Detect Control Register */
/*! @{ */

#define USBPHY_USB1_CHRG_DETECT_CLR_PULLUP_DP_MASK (0x4U)
#define USBPHY_USB1_CHRG_DETECT_CLR_PULLUP_DP_SHIFT (2U)
/*! PULLUP_DP - PULLUP_DP */
#define USBPHY_USB1_CHRG_DETECT_CLR_PULLUP_DP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_CLR_PULLUP_DP_SHIFT)) & USBPHY_USB1_CHRG_DETECT_CLR_PULLUP_DP_MASK)

#define USBPHY_USB1_CHRG_DETECT_CLR_BGR_BIAS_MASK (0x800000U)
#define USBPHY_USB1_CHRG_DETECT_CLR_BGR_BIAS_SHIFT (23U)
/*! BGR_BIAS - BGR_BIAS */
#define USBPHY_USB1_CHRG_DETECT_CLR_BGR_BIAS(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_CLR_BGR_BIAS_SHIFT)) & USBPHY_USB1_CHRG_DETECT_CLR_BGR_BIAS_MASK)
/*! @} */

/*! @name USB1_CHRG_DETECT_TOG - USB PHY Charger Detect Control Register */
/*! @{ */

#define USBPHY_USB1_CHRG_DETECT_TOG_PULLUP_DP_MASK (0x4U)
#define USBPHY_USB1_CHRG_DETECT_TOG_PULLUP_DP_SHIFT (2U)
/*! PULLUP_DP - PULLUP_DP */
#define USBPHY_USB1_CHRG_DETECT_TOG_PULLUP_DP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_TOG_PULLUP_DP_SHIFT)) & USBPHY_USB1_CHRG_DETECT_TOG_PULLUP_DP_MASK)

#define USBPHY_USB1_CHRG_DETECT_TOG_BGR_BIAS_MASK (0x800000U)
#define USBPHY_USB1_CHRG_DETECT_TOG_BGR_BIAS_SHIFT (23U)
/*! BGR_BIAS - BGR_BIAS */
#define USBPHY_USB1_CHRG_DETECT_TOG_BGR_BIAS(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DETECT_TOG_BGR_BIAS_SHIFT)) & USBPHY_USB1_CHRG_DETECT_TOG_BGR_BIAS_MASK)
/*! @} */

/*! @name USB1_CHRG_DET_STAT - USB PHY Charger Detect Status Register */
/*! @{ */

#define USBPHY_USB1_CHRG_DET_STAT_PLUG_CONTACT_MASK (0x1U)
#define USBPHY_USB1_CHRG_DET_STAT_PLUG_CONTACT_SHIFT (0U)
/*! PLUG_CONTACT - Battery Charging Data Contact Detection phase output
 *  0b0..No USB cable attachment has been detected
 *  0b1..A USB cable attachment between the device and host has been detected
 */
#define USBPHY_USB1_CHRG_DET_STAT_PLUG_CONTACT(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DET_STAT_PLUG_CONTACT_SHIFT)) & USBPHY_USB1_CHRG_DET_STAT_PLUG_CONTACT_MASK)

#define USBPHY_USB1_CHRG_DET_STAT_CHRG_DETECTED_MASK (0x2U)
#define USBPHY_USB1_CHRG_DET_STAT_CHRG_DETECTED_SHIFT (1U)
/*! CHRG_DETECTED - Battery Charging Primary Detection phase output
 *  0b0..Standard Downstream Port (SDP) has been detected
 *  0b1..Charging Port has been detected
 */
#define USBPHY_USB1_CHRG_DET_STAT_CHRG_DETECTED(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DET_STAT_CHRG_DETECTED_SHIFT)) & USBPHY_USB1_CHRG_DET_STAT_CHRG_DETECTED_MASK)

#define USBPHY_USB1_CHRG_DET_STAT_DN_STATE_MASK  (0x4U)
#define USBPHY_USB1_CHRG_DET_STAT_DN_STATE_SHIFT (2U)
/*! DN_STATE - DN_STATE
 *  0b0..DN pin voltage is < 0.8V
 *  0b1..DN pin voltage is > 2.0V
 */
#define USBPHY_USB1_CHRG_DET_STAT_DN_STATE(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DET_STAT_DN_STATE_SHIFT)) & USBPHY_USB1_CHRG_DET_STAT_DN_STATE_MASK)

#define USBPHY_USB1_CHRG_DET_STAT_DP_STATE_MASK  (0x8U)
#define USBPHY_USB1_CHRG_DET_STAT_DP_STATE_SHIFT (3U)
/*! DP_STATE - DP_STATE
 *  0b0..DP pin voltage is < 0.8V
 *  0b1..DP pin voltage is > 2.0V
 */
#define USBPHY_USB1_CHRG_DET_STAT_DP_STATE(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DET_STAT_DP_STATE_SHIFT)) & USBPHY_USB1_CHRG_DET_STAT_DP_STATE_MASK)

#define USBPHY_USB1_CHRG_DET_STAT_SECDET_DCP_MASK (0x10U)
#define USBPHY_USB1_CHRG_DET_STAT_SECDET_DCP_SHIFT (4U)
/*! SECDET_DCP - Battery Charging Secondary Detection phase output
 *  0b0..Charging Downstream Port (CDP) has been detected
 *  0b1..Downstream Charging Port (DCP) has been detected
 */
#define USBPHY_USB1_CHRG_DET_STAT_SECDET_DCP(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_CHRG_DET_STAT_SECDET_DCP_SHIFT)) & USBPHY_USB1_CHRG_DET_STAT_SECDET_DCP_MASK)
/*! @} */

/*! @name ANACTRL - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_DEV_PULLDOWN_MASK         (0x400U)
#define USBPHY_ANACTRL_DEV_PULLDOWN_SHIFT        (10U)
/*! DEV_PULLDOWN - DEV_PULLDOWN
 *  0b0..The 15kohm nominal pulldowns on the DP and DN pinsare disabled in device mode.
 *  0b1..The 15kohm nominal pulldowns on the DP and DN pinsare enabled in device mode.
 */
#define USBPHY_ANACTRL_DEV_PULLDOWN(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_DEV_PULLDOWN_MASK)
/*! @} */

/*! @name ANACTRL_SET - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_SET_DEV_PULLDOWN_MASK     (0x400U)
#define USBPHY_ANACTRL_SET_DEV_PULLDOWN_SHIFT    (10U)
/*! DEV_PULLDOWN - DEV_PULLDOWN */
#define USBPHY_ANACTRL_SET_DEV_PULLDOWN(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_SET_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_SET_DEV_PULLDOWN_MASK)
/*! @} */

/*! @name ANACTRL_CLR - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_CLR_DEV_PULLDOWN_MASK     (0x400U)
#define USBPHY_ANACTRL_CLR_DEV_PULLDOWN_SHIFT    (10U)
/*! DEV_PULLDOWN - DEV_PULLDOWN */
#define USBPHY_ANACTRL_CLR_DEV_PULLDOWN(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_CLR_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_CLR_DEV_PULLDOWN_MASK)
/*! @} */

/*! @name ANACTRL_TOG - USB PHY Analog Control Register */
/*! @{ */

#define USBPHY_ANACTRL_TOG_DEV_PULLDOWN_MASK     (0x400U)
#define USBPHY_ANACTRL_TOG_DEV_PULLDOWN_SHIFT    (10U)
/*! DEV_PULLDOWN - DEV_PULLDOWN */
#define USBPHY_ANACTRL_TOG_DEV_PULLDOWN(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_ANACTRL_TOG_DEV_PULLDOWN_SHIFT)) & USBPHY_ANACTRL_TOG_DEV_PULLDOWN_MASK)
/*! @} */

/*! @name USB1_LOOPBACK - USB PHY Loopback Control/Status Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_MASK (0x1U)
#define USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_SHIFT (0U)
/*! UTMI_TESTSTART - UTMI_TESTSTART */
#define USBPHY_USB1_LOOPBACK_UTMI_TESTSTART(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_SHIFT)) & USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_MASK)

#define USBPHY_USB1_LOOPBACK_UTMI_DIG_TST0_MASK  (0x2U)
#define USBPHY_USB1_LOOPBACK_UTMI_DIG_TST0_SHIFT (1U)
/*! UTMI_DIG_TST0 - UTMI_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_UTMI_DIG_TST0(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_UTMI_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_UTMI_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_UTMI_DIG_TST1_MASK  (0x4U)
#define USBPHY_USB1_LOOPBACK_UTMI_DIG_TST1_SHIFT (2U)
/*! UTMI_DIG_TST1 - UTMI_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_UTMI_DIG_TST1(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_UTMI_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_UTMI_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_TSTI_TX_HS_MODE_MASK (0x8U)
#define USBPHY_USB1_LOOPBACK_TSTI_TX_HS_MODE_SHIFT (3U)
/*! TSTI_TX_HS_MODE - TSTI_TX_HS_MODE */
#define USBPHY_USB1_LOOPBACK_TSTI_TX_HS_MODE(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TSTI_TX_HS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_TSTI_TX_HS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_TSTI_TX_LS_MODE_MASK (0x10U)
#define USBPHY_USB1_LOOPBACK_TSTI_TX_LS_MODE_SHIFT (4U)
/*! TSTI_TX_LS_MODE - TSTI_TX_LS_MODE */
#define USBPHY_USB1_LOOPBACK_TSTI_TX_LS_MODE(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TSTI_TX_LS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_TSTI_TX_LS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_TSTI_TX_EN_MASK     (0x20U)
#define USBPHY_USB1_LOOPBACK_TSTI_TX_EN_SHIFT    (5U)
/*! TSTI_TX_EN - TSTI_TX_EN */
#define USBPHY_USB1_LOOPBACK_TSTI_TX_EN(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TSTI_TX_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_TSTI_TX_EN_MASK)

#define USBPHY_USB1_LOOPBACK_TSTI_TX_HIZ_MASK    (0x40U)
#define USBPHY_USB1_LOOPBACK_TSTI_TX_HIZ_SHIFT   (6U)
/*! TSTI_TX_HIZ - TSTI_TX_HIZ */
#define USBPHY_USB1_LOOPBACK_TSTI_TX_HIZ(x)      (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TSTI_TX_HIZ_SHIFT)) & USBPHY_USB1_LOOPBACK_TSTI_TX_HIZ_MASK)

#define USBPHY_USB1_LOOPBACK_UTMO_DIG_TST0_MASK  (0x80U)
#define USBPHY_USB1_LOOPBACK_UTMO_DIG_TST0_SHIFT (7U)
/*! UTMO_DIG_TST0 - UTMO_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_UTMO_DIG_TST0(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_UTMO_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_UTMO_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_UTMO_DIG_TST1_MASK  (0x100U)
#define USBPHY_USB1_LOOPBACK_UTMO_DIG_TST1_SHIFT (8U)
/*! UTMO_DIG_TST1 - UTMO_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_UTMO_DIG_TST1(x)    (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_UTMO_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_UTMO_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_TSTI_HSFS_MODE_EN_MASK (0x8000U)
#define USBPHY_USB1_LOOPBACK_TSTI_HSFS_MODE_EN_SHIFT (15U)
/*! TSTI_HSFS_MODE_EN - TSTI_HSFS_MODE_EN */
#define USBPHY_USB1_LOOPBACK_TSTI_HSFS_MODE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TSTI_HSFS_MODE_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_TSTI_HSFS_MODE_EN_MASK)

#define USBPHY_USB1_LOOPBACK_TSTPKT_MASK         (0xFF0000U)
#define USBPHY_USB1_LOOPBACK_TSTPKT_SHIFT        (16U)
/*! TSTPKT - TSTPKT */
#define USBPHY_USB1_LOOPBACK_TSTPKT(x)           (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TSTPKT_SHIFT)) & USBPHY_USB1_LOOPBACK_TSTPKT_MASK)
/*! @} */

/*! @name USB1_LOOPBACK_SET - USB PHY Loopback Control/Status Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_SET_UTMI_TESTSTART_MASK (0x1U)
#define USBPHY_USB1_LOOPBACK_SET_UTMI_TESTSTART_SHIFT (0U)
/*! UTMI_TESTSTART - UTMI_TESTSTART */
#define USBPHY_USB1_LOOPBACK_SET_UTMI_TESTSTART(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_UTMI_TESTSTART_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_UTMI_TESTSTART_MASK)

#define USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST0_MASK (0x2U)
#define USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST0_SHIFT (1U)
/*! UTMI_DIG_TST0 - UTMI_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST0(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST1_MASK (0x4U)
#define USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST1_SHIFT (2U)
/*! UTMI_DIG_TST1 - UTMI_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST1(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_UTMI_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HS_MODE_MASK (0x8U)
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HS_MODE_SHIFT (3U)
/*! TSTI_TX_HS_MODE - TSTI_TX_HS_MODE */
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HS_MODE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_LS_MODE_MASK (0x10U)
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_LS_MODE_SHIFT (4U)
/*! TSTI_TX_LS_MODE - TSTI_TX_LS_MODE */
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_LS_MODE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_TSTI_TX_LS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_TSTI_TX_LS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_EN_MASK (0x20U)
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_EN_SHIFT (5U)
/*! TSTI_TX_EN - TSTI_TX_EN */
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_EN(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_TSTI_TX_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_TSTI_TX_EN_MASK)

#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HIZ_MASK (0x40U)
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HIZ_SHIFT (6U)
/*! TSTI_TX_HIZ - TSTI_TX_HIZ */
#define USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HIZ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HIZ_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_TSTI_TX_HIZ_MASK)

#define USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST0_MASK (0x80U)
#define USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST0_SHIFT (7U)
/*! UTMO_DIG_TST0 - UTMO_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST0(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST1_MASK (0x100U)
#define USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST1_SHIFT (8U)
/*! UTMO_DIG_TST1 - UTMO_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST1(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_UTMO_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_SET_TSTI_HSFS_MODE_EN_MASK (0x8000U)
#define USBPHY_USB1_LOOPBACK_SET_TSTI_HSFS_MODE_EN_SHIFT (15U)
/*! TSTI_HSFS_MODE_EN - TSTI_HSFS_MODE_EN */
#define USBPHY_USB1_LOOPBACK_SET_TSTI_HSFS_MODE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_TSTI_HSFS_MODE_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_TSTI_HSFS_MODE_EN_MASK)

#define USBPHY_USB1_LOOPBACK_SET_TSTPKT_MASK     (0xFF0000U)
#define USBPHY_USB1_LOOPBACK_SET_TSTPKT_SHIFT    (16U)
/*! TSTPKT - TSTPKT */
#define USBPHY_USB1_LOOPBACK_SET_TSTPKT(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_SET_TSTPKT_SHIFT)) & USBPHY_USB1_LOOPBACK_SET_TSTPKT_MASK)
/*! @} */

/*! @name USB1_LOOPBACK_CLR - USB PHY Loopback Control/Status Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_CLR_UTMI_TESTSTART_MASK (0x1U)
#define USBPHY_USB1_LOOPBACK_CLR_UTMI_TESTSTART_SHIFT (0U)
/*! UTMI_TESTSTART - UTMI_TESTSTART */
#define USBPHY_USB1_LOOPBACK_CLR_UTMI_TESTSTART(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_UTMI_TESTSTART_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_UTMI_TESTSTART_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST0_MASK (0x2U)
#define USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST0_SHIFT (1U)
/*! UTMI_DIG_TST0 - UTMI_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST0(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST1_MASK (0x4U)
#define USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST1_SHIFT (2U)
/*! UTMI_DIG_TST1 - UTMI_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST1(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_UTMI_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HS_MODE_MASK (0x8U)
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HS_MODE_SHIFT (3U)
/*! TSTI_TX_HS_MODE - TSTI_TX_HS_MODE */
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HS_MODE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_LS_MODE_MASK (0x10U)
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_LS_MODE_SHIFT (4U)
/*! TSTI_TX_LS_MODE - TSTI_TX_LS_MODE */
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_LS_MODE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_LS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_LS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_EN_MASK (0x20U)
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_EN_SHIFT (5U)
/*! TSTI_TX_EN - TSTI_TX_EN */
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_EN(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_EN_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HIZ_MASK (0x40U)
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HIZ_SHIFT (6U)
/*! TSTI_TX_HIZ - TSTI_TX_HIZ */
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HIZ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HIZ_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_TSTI_TX_HIZ_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST0_MASK (0x80U)
#define USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST0_SHIFT (7U)
/*! UTMO_DIG_TST0 - UTMO_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST0(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST1_MASK (0x100U)
#define USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST1_SHIFT (8U)
/*! UTMO_DIG_TST1 - UTMO_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST1(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_UTMO_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_TSTI_HSFS_MODE_EN_MASK (0x8000U)
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_HSFS_MODE_EN_SHIFT (15U)
/*! TSTI_HSFS_MODE_EN - TSTI_HSFS_MODE_EN */
#define USBPHY_USB1_LOOPBACK_CLR_TSTI_HSFS_MODE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_TSTI_HSFS_MODE_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_TSTI_HSFS_MODE_EN_MASK)

#define USBPHY_USB1_LOOPBACK_CLR_TSTPKT_MASK     (0xFF0000U)
#define USBPHY_USB1_LOOPBACK_CLR_TSTPKT_SHIFT    (16U)
/*! TSTPKT - TSTPKT */
#define USBPHY_USB1_LOOPBACK_CLR_TSTPKT(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_CLR_TSTPKT_SHIFT)) & USBPHY_USB1_LOOPBACK_CLR_TSTPKT_MASK)
/*! @} */

/*! @name USB1_LOOPBACK_TOG - USB PHY Loopback Control/Status Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_TOG_UTMI_TESTSTART_MASK (0x1U)
#define USBPHY_USB1_LOOPBACK_TOG_UTMI_TESTSTART_SHIFT (0U)
/*! UTMI_TESTSTART - UTMI_TESTSTART */
#define USBPHY_USB1_LOOPBACK_TOG_UTMI_TESTSTART(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_UTMI_TESTSTART_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_UTMI_TESTSTART_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST0_MASK (0x2U)
#define USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST0_SHIFT (1U)
/*! UTMI_DIG_TST0 - UTMI_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST0(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST1_MASK (0x4U)
#define USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST1_SHIFT (2U)
/*! UTMI_DIG_TST1 - UTMI_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST1(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_UTMI_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HS_MODE_MASK (0x8U)
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HS_MODE_SHIFT (3U)
/*! TSTI_TX_HS_MODE - TSTI_TX_HS_MODE */
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HS_MODE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_LS_MODE_MASK (0x10U)
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_LS_MODE_SHIFT (4U)
/*! TSTI_TX_LS_MODE - TSTI_TX_LS_MODE */
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_LS_MODE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_LS_MODE_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_LS_MODE_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_EN_MASK (0x20U)
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_EN_SHIFT (5U)
/*! TSTI_TX_EN - TSTI_TX_EN */
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_EN(x)   (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_EN_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HIZ_MASK (0x40U)
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HIZ_SHIFT (6U)
/*! TSTI_TX_HIZ - TSTI_TX_HIZ */
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HIZ(x)  (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HIZ_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_TSTI_TX_HIZ_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST0_MASK (0x80U)
#define USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST0_SHIFT (7U)
/*! UTMO_DIG_TST0 - UTMO_DIG_TST0 */
#define USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST0(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST0_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST0_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST1_MASK (0x100U)
#define USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST1_SHIFT (8U)
/*! UTMO_DIG_TST1 - UTMO_DIG_TST1 */
#define USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST1(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST1_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_UTMO_DIG_TST1_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_TSTI_HSFS_MODE_EN_MASK (0x8000U)
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_HSFS_MODE_EN_SHIFT (15U)
/*! TSTI_HSFS_MODE_EN - TSTI_HSFS_MODE_EN */
#define USBPHY_USB1_LOOPBACK_TOG_TSTI_HSFS_MODE_EN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_TSTI_HSFS_MODE_EN_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_TSTI_HSFS_MODE_EN_MASK)

#define USBPHY_USB1_LOOPBACK_TOG_TSTPKT_MASK     (0xFF0000U)
#define USBPHY_USB1_LOOPBACK_TOG_TSTPKT_SHIFT    (16U)
/*! TSTPKT - TSTPKT */
#define USBPHY_USB1_LOOPBACK_TOG_TSTPKT(x)       (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_TOG_TSTPKT_SHIFT)) & USBPHY_USB1_LOOPBACK_TOG_TSTPKT_MASK)
/*! @} */

/*! @name USB1_LOOPBACK_HSFSCNT - USB PHY Loopback Packet Number Select Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_HS_NUMBER_MASK (0xFFFFU)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_HS_NUMBER_SHIFT (0U)
/*! TSTI_HS_NUMBER - TSTI_HS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_HS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_HS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_HS_NUMBER_MASK)

#define USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_FS_NUMBER_MASK (0xFFFF0000U)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_FS_NUMBER_SHIFT (16U)
/*! TSTI_FS_NUMBER - TSTI_FS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_FS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_FS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_TSTI_FS_NUMBER_MASK)
/*! @} */

/*! @name USB1_LOOPBACK_HSFSCNT_SET - USB PHY Loopback Packet Number Select Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_HS_NUMBER_MASK (0xFFFFU)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_HS_NUMBER_SHIFT (0U)
/*! TSTI_HS_NUMBER - TSTI_HS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_HS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_HS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_HS_NUMBER_MASK)

#define USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_FS_NUMBER_MASK (0xFFFF0000U)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_FS_NUMBER_SHIFT (16U)
/*! TSTI_FS_NUMBER - TSTI_FS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_FS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_FS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_SET_TSTI_FS_NUMBER_MASK)
/*! @} */

/*! @name USB1_LOOPBACK_HSFSCNT_CLR - USB PHY Loopback Packet Number Select Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_HS_NUMBER_MASK (0xFFFFU)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_HS_NUMBER_SHIFT (0U)
/*! TSTI_HS_NUMBER - TSTI_HS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_HS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_HS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_HS_NUMBER_MASK)

#define USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_FS_NUMBER_MASK (0xFFFF0000U)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_FS_NUMBER_SHIFT (16U)
/*! TSTI_FS_NUMBER - TSTI_FS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_FS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_FS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_CLR_TSTI_FS_NUMBER_MASK)
/*! @} */

/*! @name USB1_LOOPBACK_HSFSCNT_TOG - USB PHY Loopback Packet Number Select Register */
/*! @{ */

#define USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_HS_NUMBER_MASK (0xFFFFU)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_HS_NUMBER_SHIFT (0U)
/*! TSTI_HS_NUMBER - TSTI_HS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_HS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_HS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_HS_NUMBER_MASK)

#define USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_FS_NUMBER_MASK (0xFFFF0000U)
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_FS_NUMBER_SHIFT (16U)
/*! TSTI_FS_NUMBER - TSTI_FS_NUMBER */
#define USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_FS_NUMBER(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_FS_NUMBER_SHIFT)) & USBPHY_USB1_LOOPBACK_HSFSCNT_TOG_TSTI_FS_NUMBER_MASK)
/*! @} */

/*! @name TRIM_OVERRIDE_EN - USB PHY Trim Override Enable Register */
/*! @{ */

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_DIV_SEL_OVERRIDE_MASK (0x1U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_DIV_SEL_OVERRIDE_SHIFT (0U)
/*! TRIM_DIV_SEL_OVERRIDE - TRIM_DIV_SEL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_DIV_SEL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_DIV_SEL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_DIV_SEL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK (0x2U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT (1U)
/*! TRIM_ENV_TAIL_ADJ_VD_OVERRIDE - TRIM_ENV_TAIL_ADJ_VD_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_D_CAL_OVERRIDE_MASK (0x4U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_D_CAL_OVERRIDE_SHIFT (2U)
/*! TRIM_TX_D_CAL_OVERRIDE - TRIM_TX_D_CAL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_D_CAL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_D_CAL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_D_CAL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DP_OVERRIDE_MASK (0x8U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DP_OVERRIDE_SHIFT (3U)
/*! TRIM_TX_CAL45DP_OVERRIDE - TRIM_TX_CAL45DP_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DP_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DP_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DP_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DN_OVERRIDE_MASK (0x10U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DN_OVERRIDE_SHIFT (4U)
/*! TRIM_TX_CAL45DN_OVERRIDE - TRIM_TX_CAL45DN_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DN_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DN_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_TX_CAL45DN_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK (0x20U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT (5U)
/*! TRIM_REFBIAS_VBGADJ_OVERRIDE - Override enable for bandgap adjustment. */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_VBGADJ_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_TST_OVERRIDE_MASK (0x40U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_TST_OVERRIDE_SHIFT (6U)
/*! TRIM_REFBIAS_TST_OVERRIDE - Override enable for bias current control */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_TST_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_TST_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_REFBIAS_TST_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_VBGADJ_MASK (0x1C00U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_VBGADJ_SHIFT (10U)
/*! TRIM_USB2_REFBIAS_VBGADJ - TRIM_USB2_REFBIAS_VBGADJ */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_TST_MASK (0x6000U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_TST_SHIFT (13U)
/*! TRIM_USB2_REFBIAS_TST - TRIM_USB2_REFBIAS_TST */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_TST(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_TST_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_USB2_REFBIAS_TST_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_PLL_CTRL0_DIV_SEL_MASK (0x38000U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_PLL_CTRL0_DIV_SEL_SHIFT (15U)
/*! TRIM_PLL_CTRL0_DIV_SEL - TRIM_PLL_CTRL0_DIV_SEL */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_PLL_CTRL0_DIV_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_PLL_CTRL0_DIV_SEL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_PLL_CTRL0_DIV_SEL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK (0xC0000U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT (18U)
/*! TRIM_USB_REG_ENV_TAIL_ADJ_VD - TRIM_USB_REG_ENV_TAIL_ADJ_VD */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USB_REG_ENV_TAIL_ADJ_VD(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_D_CAL_MASK (0xF00000U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_D_CAL_SHIFT (20U)
/*! TRIM_USBPHY_TX_D_CAL - TRIM_USBPHY_TX_D_CAL */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_D_CAL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_D_CAL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_D_CAL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DP_MASK (0xF000000U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DP_SHIFT (24U)
/*! TRIM_USBPHY_TX_CAL45DP - TRIM_USBPHY_TX_CAL45DP */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DP_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DP_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DN_MASK (0xF0000000U)
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DN_SHIFT (28U)
/*! TRIM_USBPHY_TX_CAL45DN - TRIM_USBPHY_TX_CAL45DN */
#define USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DN_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TRIM_USBPHY_TX_CAL45DN_MASK)
/*! @} */

/*! @name TRIM_OVERRIDE_EN_SET - USB PHY Trim Override Enable Register */
/*! @{ */

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_DIV_SEL_OVERRIDE_MASK (0x1U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_DIV_SEL_OVERRIDE_SHIFT (0U)
/*! TRIM_DIV_SEL_OVERRIDE - TRIM_DIV_SEL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_DIV_SEL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_DIV_SEL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_DIV_SEL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK (0x2U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT (1U)
/*! TRIM_ENV_TAIL_ADJ_VD_OVERRIDE - TRIM_ENV_TAIL_ADJ_VD_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_D_CAL_OVERRIDE_MASK (0x4U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_D_CAL_OVERRIDE_SHIFT (2U)
/*! TRIM_TX_D_CAL_OVERRIDE - TRIM_TX_D_CAL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_D_CAL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_D_CAL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_D_CAL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DP_OVERRIDE_MASK (0x8U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DP_OVERRIDE_SHIFT (3U)
/*! TRIM_TX_CAL45DP_OVERRIDE - TRIM_TX_CAL45DP_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DP_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DP_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DP_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DN_OVERRIDE_MASK (0x10U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DN_OVERRIDE_SHIFT (4U)
/*! TRIM_TX_CAL45DN_OVERRIDE - TRIM_TX_CAL45DN_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DN_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DN_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_TX_CAL45DN_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK (0x20U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT (5U)
/*! TRIM_REFBIAS_VBGADJ_OVERRIDE - Override enable for bandgap adjustment. */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_VBGADJ_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_TST_OVERRIDE_MASK (0x40U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_TST_OVERRIDE_SHIFT (6U)
/*! TRIM_REFBIAS_TST_OVERRIDE - Override enable for bias current control */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_TST_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_TST_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_REFBIAS_TST_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_VBGADJ_MASK (0x1C00U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_VBGADJ_SHIFT (10U)
/*! TRIM_USB2_REFBIAS_VBGADJ - TRIM_USB2_REFBIAS_VBGADJ */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_TST_MASK (0x6000U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_TST_SHIFT (13U)
/*! TRIM_USB2_REFBIAS_TST - TRIM_USB2_REFBIAS_TST */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_TST(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_TST_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB2_REFBIAS_TST_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_PLL_CTRL0_DIV_SEL_MASK (0x38000U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_PLL_CTRL0_DIV_SEL_SHIFT (15U)
/*! TRIM_PLL_CTRL0_DIV_SEL - TRIM_PLL_CTRL0_DIV_SEL */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_PLL_CTRL0_DIV_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_PLL_CTRL0_DIV_SEL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_PLL_CTRL0_DIV_SEL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK (0xC0000U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT (18U)
/*! TRIM_USB_REG_ENV_TAIL_ADJ_VD - TRIM_USB_REG_ENV_TAIL_ADJ_VD */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB_REG_ENV_TAIL_ADJ_VD(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_D_CAL_MASK (0xF00000U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_D_CAL_SHIFT (20U)
/*! TRIM_USBPHY_TX_D_CAL - TRIM_USBPHY_TX_D_CAL */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_D_CAL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_D_CAL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_D_CAL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DP_MASK (0xF000000U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DP_SHIFT (24U)
/*! TRIM_USBPHY_TX_CAL45DP - TRIM_USBPHY_TX_CAL45DP */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DP_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DP_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DN_MASK (0xF0000000U)
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DN_SHIFT (28U)
/*! TRIM_USBPHY_TX_CAL45DN - TRIM_USBPHY_TX_CAL45DN */
#define USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DN_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_SET_TRIM_USBPHY_TX_CAL45DN_MASK)
/*! @} */

/*! @name TRIM_OVERRIDE_EN_CLR - USB PHY Trim Override Enable Register */
/*! @{ */

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_DIV_SEL_OVERRIDE_MASK (0x1U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_DIV_SEL_OVERRIDE_SHIFT (0U)
/*! TRIM_DIV_SEL_OVERRIDE - TRIM_DIV_SEL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_DIV_SEL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_DIV_SEL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_DIV_SEL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK (0x2U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT (1U)
/*! TRIM_ENV_TAIL_ADJ_VD_OVERRIDE - TRIM_ENV_TAIL_ADJ_VD_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_D_CAL_OVERRIDE_MASK (0x4U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_D_CAL_OVERRIDE_SHIFT (2U)
/*! TRIM_TX_D_CAL_OVERRIDE - TRIM_TX_D_CAL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_D_CAL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_D_CAL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_D_CAL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DP_OVERRIDE_MASK (0x8U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DP_OVERRIDE_SHIFT (3U)
/*! TRIM_TX_CAL45DP_OVERRIDE - TRIM_TX_CAL45DP_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DP_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DP_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DP_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DN_OVERRIDE_MASK (0x10U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DN_OVERRIDE_SHIFT (4U)
/*! TRIM_TX_CAL45DN_OVERRIDE - TRIM_TX_CAL45DN_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DN_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DN_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_TX_CAL45DN_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK (0x20U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT (5U)
/*! TRIM_REFBIAS_VBGADJ_OVERRIDE - Override enable for bandgap adjustment. */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_VBGADJ_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_TST_OVERRIDE_MASK (0x40U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_TST_OVERRIDE_SHIFT (6U)
/*! TRIM_REFBIAS_TST_OVERRIDE - Override enable for bias current control */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_TST_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_TST_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_REFBIAS_TST_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_VBGADJ_MASK (0x1C00U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_VBGADJ_SHIFT (10U)
/*! TRIM_USB2_REFBIAS_VBGADJ - TRIM_USB2_REFBIAS_VBGADJ */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_TST_MASK (0x6000U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_TST_SHIFT (13U)
/*! TRIM_USB2_REFBIAS_TST - TRIM_USB2_REFBIAS_TST */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_TST(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_TST_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB2_REFBIAS_TST_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_PLL_CTRL0_DIV_SEL_MASK (0x38000U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_PLL_CTRL0_DIV_SEL_SHIFT (15U)
/*! TRIM_PLL_CTRL0_DIV_SEL - TRIM_PLL_CTRL0_DIV_SEL */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_PLL_CTRL0_DIV_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_PLL_CTRL0_DIV_SEL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_PLL_CTRL0_DIV_SEL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK (0xC0000U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT (18U)
/*! TRIM_USB_REG_ENV_TAIL_ADJ_VD - TRIM_USB_REG_ENV_TAIL_ADJ_VD */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB_REG_ENV_TAIL_ADJ_VD(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_D_CAL_MASK (0xF00000U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_D_CAL_SHIFT (20U)
/*! TRIM_USBPHY_TX_D_CAL - TRIM_USBPHY_TX_D_CAL */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_D_CAL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_D_CAL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_D_CAL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DP_MASK (0xF000000U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DP_SHIFT (24U)
/*! TRIM_USBPHY_TX_CAL45DP - TRIM_USBPHY_TX_CAL45DP */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DP_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DP_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DN_MASK (0xF0000000U)
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DN_SHIFT (28U)
/*! TRIM_USBPHY_TX_CAL45DN - TRIM_USBPHY_TX_CAL45DN */
#define USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DN_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_CLR_TRIM_USBPHY_TX_CAL45DN_MASK)
/*! @} */

/*! @name TRIM_OVERRIDE_EN_TOG - USB PHY Trim Override Enable Register */
/*! @{ */

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_DIV_SEL_OVERRIDE_MASK (0x1U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_DIV_SEL_OVERRIDE_SHIFT (0U)
/*! TRIM_DIV_SEL_OVERRIDE - TRIM_DIV_SEL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_DIV_SEL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_DIV_SEL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_DIV_SEL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK (0x2U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT (1U)
/*! TRIM_ENV_TAIL_ADJ_VD_OVERRIDE - TRIM_ENV_TAIL_ADJ_VD_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_ENV_TAIL_ADJ_VD_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_D_CAL_OVERRIDE_MASK (0x4U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_D_CAL_OVERRIDE_SHIFT (2U)
/*! TRIM_TX_D_CAL_OVERRIDE - TRIM_TX_D_CAL_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_D_CAL_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_D_CAL_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_D_CAL_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DP_OVERRIDE_MASK (0x8U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DP_OVERRIDE_SHIFT (3U)
/*! TRIM_TX_CAL45DP_OVERRIDE - TRIM_TX_CAL45DP_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DP_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DP_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DP_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DN_OVERRIDE_MASK (0x10U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DN_OVERRIDE_SHIFT (4U)
/*! TRIM_TX_CAL45DN_OVERRIDE - TRIM_TX_CAL45DN_OVERRIDE */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DN_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DN_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_TX_CAL45DN_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK (0x20U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT (5U)
/*! TRIM_REFBIAS_VBGADJ_OVERRIDE - Override enable for bandgap adjustment. */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_VBGADJ_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_VBGADJ_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_VBGADJ_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_TST_OVERRIDE_MASK (0x40U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_TST_OVERRIDE_SHIFT (6U)
/*! TRIM_REFBIAS_TST_OVERRIDE - Override enable for bias current control */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_TST_OVERRIDE(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_TST_OVERRIDE_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_REFBIAS_TST_OVERRIDE_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_VBGADJ_MASK (0x1C00U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_VBGADJ_SHIFT (10U)
/*! TRIM_USB2_REFBIAS_VBGADJ - TRIM_USB2_REFBIAS_VBGADJ */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_VBGADJ(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_VBGADJ_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_VBGADJ_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_TST_MASK (0x6000U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_TST_SHIFT (13U)
/*! TRIM_USB2_REFBIAS_TST - TRIM_USB2_REFBIAS_TST */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_TST(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_TST_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB2_REFBIAS_TST_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_PLL_CTRL0_DIV_SEL_MASK (0x38000U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_PLL_CTRL0_DIV_SEL_SHIFT (15U)
/*! TRIM_PLL_CTRL0_DIV_SEL - TRIM_PLL_CTRL0_DIV_SEL */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_PLL_CTRL0_DIV_SEL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_PLL_CTRL0_DIV_SEL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_PLL_CTRL0_DIV_SEL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK (0xC0000U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT (18U)
/*! TRIM_USB_REG_ENV_TAIL_ADJ_VD - TRIM_USB_REG_ENV_TAIL_ADJ_VD */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB_REG_ENV_TAIL_ADJ_VD(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB_REG_ENV_TAIL_ADJ_VD_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USB_REG_ENV_TAIL_ADJ_VD_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_D_CAL_MASK (0xF00000U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_D_CAL_SHIFT (20U)
/*! TRIM_USBPHY_TX_D_CAL - TRIM_USBPHY_TX_D_CAL */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_D_CAL(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_D_CAL_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_D_CAL_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DP_MASK (0xF000000U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DP_SHIFT (24U)
/*! TRIM_USBPHY_TX_CAL45DP - TRIM_USBPHY_TX_CAL45DP */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DP(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DP_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DP_MASK)

#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DN_MASK (0xF0000000U)
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DN_SHIFT (28U)
/*! TRIM_USBPHY_TX_CAL45DN - TRIM_USBPHY_TX_CAL45DN */
#define USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DN(x) (((uint32_t)(((uint32_t)(x)) << USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DN_SHIFT)) & USBPHY_TRIM_OVERRIDE_EN_TOG_TRIM_USBPHY_TX_CAL45DN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USBPHY_Register_Masks */


/*!
 * @}
 */ /* end of group USBPHY_Peripheral_Access_Layer */


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


#endif  /* PERI_USBPHY_H_ */

