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
**         CMSIS Peripheral Access Layer for IEE_APC
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
 * @file PERI_IEE_APC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IEE_APC
 *
 * CMSIS Peripheral Access Layer for IEE_APC
 */

#if !defined(PERI_IEE_APC_H_)
#define PERI_IEE_APC_H_                          /**< Symbol preventing repeated inclusion */

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
   -- IEE_APC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IEE_APC_Peripheral_Access_Layer IEE_APC Peripheral Access Layer
 * @{
 */

/** IEE_APC - Register Layout Typedef */
typedef struct {
  __IO uint32_t REGION0_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x0 */
  __IO uint32_t REGION0_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x4 */
  __IO uint32_t REGION0_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x8 */
  __IO uint32_t REGION0_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0xC */
  __IO uint32_t REGION1_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x10 */
  __IO uint32_t REGION1_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x14 */
  __IO uint32_t REGION1_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x18 */
  __IO uint32_t REGION1_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0x1C */
  __IO uint32_t REGION2_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x20 */
  __IO uint32_t REGION2_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x24 */
  __IO uint32_t REGION2_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x28 */
  __IO uint32_t REGION2_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0x2C */
  __IO uint32_t REGION3_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x30 */
  __IO uint32_t REGION3_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x34 */
  __IO uint32_t REGION3_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x38 */
  __IO uint32_t REGION3_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0x3C */
  __IO uint32_t REGION4_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x40 */
  __IO uint32_t REGION4_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x44 */
  __IO uint32_t REGION4_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x48 */
  __IO uint32_t REGION4_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0x4C */
  __IO uint32_t REGION5_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x50 */
  __IO uint32_t REGION5_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x54 */
  __IO uint32_t REGION5_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x58 */
  __IO uint32_t REGION5_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0x5C */
  __IO uint32_t REGION6_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x60 */
  __IO uint32_t REGION6_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x64 */
  __IO uint32_t REGION6_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x68 */
  __IO uint32_t REGION6_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0x6C */
  __IO uint32_t REGION7_TOP_ADDR;                  /**< End address of IEE region (n), offset: 0x70 */
  __IO uint32_t REGION7_BOT_ADDR;                  /**< Start address of IEE region (n), offset: 0x74 */
  __IO uint32_t REGION7_RDC_D0;                    /**< Region control of core domain 0 for region (n), offset: 0x78 */
  __IO uint32_t REGION7_RDC_D1;                    /**< Region control of core domain 1 for region (n), offset: 0x7C */
} IEE_APC_Type;

/* ----------------------------------------------------------------------------
   -- IEE_APC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IEE_APC_Register_Masks IEE_APC Register Masks
 * @{
 */

/*! @name REGION0_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION0_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION0_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION0_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION0_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION0_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION0_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION0_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION0_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION0_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION0_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION0_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION0_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION0_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION0_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION0_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION0_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION0_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION0_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION0_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION0_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION0_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION0_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION0_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION0_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION0_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION0_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION0_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION0_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION0_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION0_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION0_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION0_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION0_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */

/*! @name REGION1_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION1_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION1_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION1_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION1_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION1_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION1_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION1_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION1_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION1_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION1_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION1_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION1_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION1_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION1_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION1_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION1_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION1_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION1_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION1_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION1_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION1_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION1_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION1_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION1_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION1_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION1_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION1_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION1_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION1_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION1_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION1_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION1_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION1_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */

/*! @name REGION2_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION2_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION2_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION2_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION2_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION2_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION2_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION2_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION2_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION2_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION2_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION2_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION2_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION2_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION2_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION2_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION2_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION2_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION2_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION2_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION2_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION2_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION2_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION2_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION2_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION2_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION2_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION2_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION2_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION2_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION2_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION2_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION2_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION2_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */

/*! @name REGION3_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION3_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION3_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION3_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION3_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION3_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION3_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION3_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION3_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION3_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION3_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION3_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION3_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION3_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION3_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION3_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION3_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION3_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION3_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION3_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION3_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION3_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION3_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION3_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION3_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION3_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION3_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION3_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION3_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION3_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION3_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION3_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION3_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION3_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */

/*! @name REGION4_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION4_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION4_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION4_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION4_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION4_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION4_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION4_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION4_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION4_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION4_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION4_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION4_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION4_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION4_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION4_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION4_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION4_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION4_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION4_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION4_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION4_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION4_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION4_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION4_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION4_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION4_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION4_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION4_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION4_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION4_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION4_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION4_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION4_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */

/*! @name REGION5_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION5_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION5_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION5_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION5_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION5_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION5_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION5_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION5_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION5_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION5_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION5_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION5_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION5_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION5_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION5_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION5_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION5_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION5_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION5_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION5_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION5_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION5_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION5_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION5_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION5_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION5_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION5_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION5_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION5_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION5_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION5_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION5_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION5_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */

/*! @name REGION6_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION6_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION6_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION6_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION6_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION6_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION6_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION6_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION6_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION6_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION6_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION6_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION6_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION6_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION6_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION6_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION6_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION6_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION6_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION6_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION6_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION6_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION6_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION6_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION6_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION6_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION6_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION6_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION6_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION6_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION6_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION6_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION6_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION6_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */

/*! @name REGION7_TOP_ADDR - End address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION7_TOP_ADDR_TOP_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION7_TOP_ADDR_TOP_ADDR_SHIFT  (0U)
/*! TOP_ADDR - End address of IEE region */
#define IEE_APC_REGION7_TOP_ADDR_TOP_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION7_TOP_ADDR_TOP_ADDR_SHIFT)) & IEE_APC_REGION7_TOP_ADDR_TOP_ADDR_MASK)
/*! @} */

/*! @name REGION7_BOT_ADDR - Start address of IEE region (n) */
/*! @{ */

#define IEE_APC_REGION7_BOT_ADDR_BOT_ADDR_MASK   (0x1FFFFFFFU)
#define IEE_APC_REGION7_BOT_ADDR_BOT_ADDR_SHIFT  (0U)
/*! BOT_ADDR - Start address of IEE region */
#define IEE_APC_REGION7_BOT_ADDR_BOT_ADDR(x)     (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION7_BOT_ADDR_BOT_ADDR_SHIFT)) & IEE_APC_REGION7_BOT_ADDR_BOT_ADDR_MASK)
/*! @} */

/*! @name REGION7_RDC_D0 - Region control of core domain 0 for region (n) */
/*! @{ */

#define IEE_APC_REGION7_RDC_D0_RDC_D0_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION7_RDC_D0_RDC_D0_WRITE_DIS_SHIFT (0U)
/*! RDC_D0_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION7_RDC_D0_RDC_D0_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION7_RDC_D0_RDC_D0_WRITE_DIS_SHIFT)) & IEE_APC_REGION7_RDC_D0_RDC_D0_WRITE_DIS_MASK)

#define IEE_APC_REGION7_RDC_D0_RDC_D0_LOCK_MASK  (0x2U)
#define IEE_APC_REGION7_RDC_D0_RDC_D0_LOCK_SHIFT (1U)
/*! RDC_D0_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION7_RDC_D0_RDC_D0_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION7_RDC_D0_RDC_D0_LOCK_SHIFT)) & IEE_APC_REGION7_RDC_D0_RDC_D0_LOCK_MASK)
/*! @} */

/*! @name REGION7_RDC_D1 - Region control of core domain 1 for region (n) */
/*! @{ */

#define IEE_APC_REGION7_RDC_D1_RDC_D1_WRITE_DIS_MASK (0x1U)
#define IEE_APC_REGION7_RDC_D1_RDC_D1_WRITE_DIS_SHIFT (0U)
/*! RDC_D1_WRITE_DIS - Write disable of core domain 1
 *  0b0..Write to TOP_ADDR and BOT_ADDR of this region enabled
 *  0b1..Write to TOP_ADDR and BOT_ADDR of this region disabled
 */
#define IEE_APC_REGION7_RDC_D1_RDC_D1_WRITE_DIS(x) (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION7_RDC_D1_RDC_D1_WRITE_DIS_SHIFT)) & IEE_APC_REGION7_RDC_D1_RDC_D1_WRITE_DIS_MASK)

#define IEE_APC_REGION7_RDC_D1_RDC_D1_LOCK_MASK  (0x2U)
#define IEE_APC_REGION7_RDC_D1_RDC_D1_LOCK_SHIFT (1U)
/*! RDC_D1_LOCK - Lock bit for bit 0
 *  0b0..Bit 0 is unlocked
 *  0b1..Bit 0 is locked
 */
#define IEE_APC_REGION7_RDC_D1_RDC_D1_LOCK(x)    (((uint32_t)(((uint32_t)(x)) << IEE_APC_REGION7_RDC_D1_RDC_D1_LOCK_SHIFT)) & IEE_APC_REGION7_RDC_D1_RDC_D1_LOCK_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group IEE_APC_Register_Masks */


/*!
 * @}
 */ /* end of group IEE_APC_Peripheral_Access_Layer */


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


#endif  /* PERI_IEE_APC_H_ */

