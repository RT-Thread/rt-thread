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
**         CMSIS Peripheral Access Layer for OCOTP
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
 * @file PERI_OCOTP.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for OCOTP
 *
 * CMSIS Peripheral Access Layer for OCOTP
 */

#if !defined(PERI_OCOTP_H_)
#define PERI_OCOTP_H_                            /**< Symbol preventing repeated inclusion */

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
   -- OCOTP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OCOTP_Peripheral_Access_Layer OCOTP Peripheral Access Layer
 * @{
 */

/** OCOTP - Size of Registers Arrays */
#define OCOTP_READ_FUSE_DATAS_COUNT               4u
#define OCOTP_FUSEN_COUNT                         144u

/** OCOTP - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< OTP Controller Control and Status Register, offset: 0x0 */
  __IO uint32_t CTRL_SET;                          /**< OTP Controller Control and Status Register, offset: 0x4 */
  __IO uint32_t CTRL_CLR;                          /**< OTP Controller Control and Status Register, offset: 0x8 */
  __IO uint32_t CTRL_TOG;                          /**< OTP Controller Control and Status Register, offset: 0xC */
  __IO uint32_t PDN;                               /**< OTP Controller PDN Register, offset: 0x10 */
       uint8_t RESERVED_0[12];
  __IO uint32_t DATA;                              /**< OTP Controller Write Data Register, offset: 0x20 */
       uint8_t RESERVED_1[12];
  __IO uint32_t READ_CTRL;                         /**< OTP Controller Read Control Register, offset: 0x30 */
       uint8_t RESERVED_2[92];
  __IO uint32_t OUT_STATUS;                        /**< 8K OTP Memory STATUS Register, offset: 0x90 */
  __IO uint32_t OUT_STATUS_SET;                    /**< 8K OTP Memory STATUS Register, offset: 0x94 */
  __IO uint32_t OUT_STATUS_CLR;                    /**< 8K OTP Memory STATUS Register, offset: 0x98 */
  __IO uint32_t OUT_STATUS_TOG;                    /**< 8K OTP Memory STATUS Register, offset: 0x9C */
       uint8_t RESERVED_3[16];
  __I  uint32_t VERSION;                           /**< OTP Controller Version Register, offset: 0xB0 */
       uint8_t RESERVED_4[76];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t READ_FUSE_DATA;                    /**< OTP Controller Read Data 0 Register..OTP Controller Read Data 3 Register, array offset: 0x100, array step: 0x10 */
         uint8_t RESERVED_0[12];
  } READ_FUSE_DATAS[OCOTP_READ_FUSE_DATAS_COUNT];
  __IO uint32_t SW_LOCK;                           /**< SW_LOCK Register, offset: 0x140 */
       uint8_t RESERVED_5[12];
  __IO uint32_t BIT_LOCK;                          /**< BIT_LOCK Register, offset: 0x150 */
       uint8_t RESERVED_6[1196];
  __I  uint32_t LOCKED0;                           /**< OTP Controller Program Locked Status 0 Register, offset: 0x600 */
       uint8_t RESERVED_7[12];
  __I  uint32_t LOCKED1;                           /**< OTP Controller Program Locked Status 1 Register, offset: 0x610 */
       uint8_t RESERVED_8[492];
  struct {                                         /* offset: 0x800, array step: 0x10 */
    __I  uint32_t FUSE;                              /**< Value of fuse word 0..Value of fuse word 143, array offset: 0x800, array step: 0x10 */
         uint8_t RESERVED_0[12];
  } FUSEN[OCOTP_FUSEN_COUNT];
} OCOTP_Type;

/* ----------------------------------------------------------------------------
   -- OCOTP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OCOTP_Register_Masks OCOTP Register Masks
 * @{
 */

/*! @name CTRL - OTP Controller Control and Status Register */
/*! @{ */

#define OCOTP_CTRL_ADDR_MASK                     (0x3FFU)
#define OCOTP_CTRL_ADDR_SHIFT                    (0U)
/*! ADDR - OTP write and read access address register
 *  0b0000000000-0b0000001111..Address of one of the 16 supplementary fuse words in OTP memory.
 *  0b0000010000-0b0100001111..Address of one of the 256 user fuse words in OTP memory.
 */
#define OCOTP_CTRL_ADDR(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_ADDR_SHIFT)) & OCOTP_CTRL_ADDR_MASK)

#define OCOTP_CTRL_BUSY_MASK                     (0x400U)
#define OCOTP_CTRL_BUSY_SHIFT                    (10U)
/*! BUSY - OTP controller status bit
 *  0b0..No write or read access to OTP started.
 *  0b1..Write or read access to OTP started.
 */
#define OCOTP_CTRL_BUSY(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_BUSY_SHIFT)) & OCOTP_CTRL_BUSY_MASK)

#define OCOTP_CTRL_ERROR_MASK                    (0x800U)
#define OCOTP_CTRL_ERROR_SHIFT                   (11U)
/*! ERROR - Locked Region Access Error
 *  0b0..No error.
 *  0b1..Error - access to a locked region requested.
 */
#define OCOTP_CTRL_ERROR(x)                      (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_ERROR_SHIFT)) & OCOTP_CTRL_ERROR_MASK)

#define OCOTP_CTRL_RELOAD_SHADOWS_MASK           (0x1000U)
#define OCOTP_CTRL_RELOAD_SHADOWS_SHIFT          (12U)
/*! RELOAD_SHADOWS - Reload Shadow Registers
 *  0b0..Do not force shadow register re-load.
 *  0b1..Force shadow register re-load. This bit is cleared automatically after shadow registers are re-loaded.
 */
#define OCOTP_CTRL_RELOAD_SHADOWS(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_RELOAD_SHADOWS_MASK)

#define OCOTP_CTRL_WORDLOCK_MASK                 (0x8000U)
#define OCOTP_CTRL_WORDLOCK_SHIFT                (15U)
/*! WORDLOCK - Lock fuse word
 *  0b0..No change to LOCK bit when programming a word using redundancy
 *  0b1..LOCK bit for fuse word will be set after successfully programming a word using redundancy
 */
#define OCOTP_CTRL_WORDLOCK(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_WORDLOCK_SHIFT)) & OCOTP_CTRL_WORDLOCK_MASK)

#define OCOTP_CTRL_WR_UNLOCK_MASK                (0xFFFF0000U)
#define OCOTP_CTRL_WR_UNLOCK_SHIFT               (16U)
/*! WR_UNLOCK - Write unlock
 *  0b0000000000000000..OTP write access is locked.
 *  0b0011111001110111..OTP write access is unlocked.
 */
#define OCOTP_CTRL_WR_UNLOCK(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_WR_UNLOCK_MASK)
/*! @} */

/*! @name CTRL_SET - OTP Controller Control and Status Register */
/*! @{ */

#define OCOTP_CTRL_SET_ADDR_MASK                 (0x3FFU)
#define OCOTP_CTRL_SET_ADDR_SHIFT                (0U)
/*! ADDR - OTP write and read access address register */
#define OCOTP_CTRL_SET_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_ADDR_SHIFT)) & OCOTP_CTRL_SET_ADDR_MASK)

#define OCOTP_CTRL_SET_BUSY_MASK                 (0x400U)
#define OCOTP_CTRL_SET_BUSY_SHIFT                (10U)
/*! BUSY - OTP controller status bit */
#define OCOTP_CTRL_SET_BUSY(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_BUSY_SHIFT)) & OCOTP_CTRL_SET_BUSY_MASK)

#define OCOTP_CTRL_SET_ERROR_MASK                (0x800U)
#define OCOTP_CTRL_SET_ERROR_SHIFT               (11U)
/*! ERROR - Locked Region Access Error */
#define OCOTP_CTRL_SET_ERROR(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_ERROR_SHIFT)) & OCOTP_CTRL_SET_ERROR_MASK)

#define OCOTP_CTRL_SET_RELOAD_SHADOWS_MASK       (0x1000U)
#define OCOTP_CTRL_SET_RELOAD_SHADOWS_SHIFT      (12U)
/*! RELOAD_SHADOWS - Reload Shadow Registers */
#define OCOTP_CTRL_SET_RELOAD_SHADOWS(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_SET_RELOAD_SHADOWS_MASK)

#define OCOTP_CTRL_SET_WORDLOCK_MASK             (0x8000U)
#define OCOTP_CTRL_SET_WORDLOCK_SHIFT            (15U)
/*! WORDLOCK - Lock fuse word */
#define OCOTP_CTRL_SET_WORDLOCK(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_WORDLOCK_SHIFT)) & OCOTP_CTRL_SET_WORDLOCK_MASK)

#define OCOTP_CTRL_SET_WR_UNLOCK_MASK            (0xFFFF0000U)
#define OCOTP_CTRL_SET_WR_UNLOCK_SHIFT           (16U)
/*! WR_UNLOCK - Write unlock */
#define OCOTP_CTRL_SET_WR_UNLOCK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_SET_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_SET_WR_UNLOCK_MASK)
/*! @} */

/*! @name CTRL_CLR - OTP Controller Control and Status Register */
/*! @{ */

#define OCOTP_CTRL_CLR_ADDR_MASK                 (0x3FFU)
#define OCOTP_CTRL_CLR_ADDR_SHIFT                (0U)
/*! ADDR - OTP write and read access address register */
#define OCOTP_CTRL_CLR_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_ADDR_SHIFT)) & OCOTP_CTRL_CLR_ADDR_MASK)

#define OCOTP_CTRL_CLR_BUSY_MASK                 (0x400U)
#define OCOTP_CTRL_CLR_BUSY_SHIFT                (10U)
/*! BUSY - OTP controller status bit */
#define OCOTP_CTRL_CLR_BUSY(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_BUSY_SHIFT)) & OCOTP_CTRL_CLR_BUSY_MASK)

#define OCOTP_CTRL_CLR_ERROR_MASK                (0x800U)
#define OCOTP_CTRL_CLR_ERROR_SHIFT               (11U)
/*! ERROR - Locked Region Access Error */
#define OCOTP_CTRL_CLR_ERROR(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_ERROR_SHIFT)) & OCOTP_CTRL_CLR_ERROR_MASK)

#define OCOTP_CTRL_CLR_RELOAD_SHADOWS_MASK       (0x1000U)
#define OCOTP_CTRL_CLR_RELOAD_SHADOWS_SHIFT      (12U)
/*! RELOAD_SHADOWS - Reload Shadow Registers */
#define OCOTP_CTRL_CLR_RELOAD_SHADOWS(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_CLR_RELOAD_SHADOWS_MASK)

#define OCOTP_CTRL_CLR_WORDLOCK_MASK             (0x8000U)
#define OCOTP_CTRL_CLR_WORDLOCK_SHIFT            (15U)
/*! WORDLOCK - Lock fuse word */
#define OCOTP_CTRL_CLR_WORDLOCK(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_WORDLOCK_SHIFT)) & OCOTP_CTRL_CLR_WORDLOCK_MASK)

#define OCOTP_CTRL_CLR_WR_UNLOCK_MASK            (0xFFFF0000U)
#define OCOTP_CTRL_CLR_WR_UNLOCK_SHIFT           (16U)
/*! WR_UNLOCK - Write unlock */
#define OCOTP_CTRL_CLR_WR_UNLOCK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_CLR_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_CLR_WR_UNLOCK_MASK)
/*! @} */

/*! @name CTRL_TOG - OTP Controller Control and Status Register */
/*! @{ */

#define OCOTP_CTRL_TOG_ADDR_MASK                 (0x3FFU)
#define OCOTP_CTRL_TOG_ADDR_SHIFT                (0U)
/*! ADDR - OTP write and read access address register */
#define OCOTP_CTRL_TOG_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_ADDR_SHIFT)) & OCOTP_CTRL_TOG_ADDR_MASK)

#define OCOTP_CTRL_TOG_BUSY_MASK                 (0x400U)
#define OCOTP_CTRL_TOG_BUSY_SHIFT                (10U)
/*! BUSY - OTP controller status bit */
#define OCOTP_CTRL_TOG_BUSY(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_BUSY_SHIFT)) & OCOTP_CTRL_TOG_BUSY_MASK)

#define OCOTP_CTRL_TOG_ERROR_MASK                (0x800U)
#define OCOTP_CTRL_TOG_ERROR_SHIFT               (11U)
/*! ERROR - Locked Region Access Error */
#define OCOTP_CTRL_TOG_ERROR(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_ERROR_SHIFT)) & OCOTP_CTRL_TOG_ERROR_MASK)

#define OCOTP_CTRL_TOG_RELOAD_SHADOWS_MASK       (0x1000U)
#define OCOTP_CTRL_TOG_RELOAD_SHADOWS_SHIFT      (12U)
/*! RELOAD_SHADOWS - Reload Shadow Registers */
#define OCOTP_CTRL_TOG_RELOAD_SHADOWS(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_RELOAD_SHADOWS_SHIFT)) & OCOTP_CTRL_TOG_RELOAD_SHADOWS_MASK)

#define OCOTP_CTRL_TOG_WORDLOCK_MASK             (0x8000U)
#define OCOTP_CTRL_TOG_WORDLOCK_SHIFT            (15U)
/*! WORDLOCK - Lock fuse word */
#define OCOTP_CTRL_TOG_WORDLOCK(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_WORDLOCK_SHIFT)) & OCOTP_CTRL_TOG_WORDLOCK_MASK)

#define OCOTP_CTRL_TOG_WR_UNLOCK_MASK            (0xFFFF0000U)
#define OCOTP_CTRL_TOG_WR_UNLOCK_SHIFT           (16U)
/*! WR_UNLOCK - Write unlock */
#define OCOTP_CTRL_TOG_WR_UNLOCK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_CTRL_TOG_WR_UNLOCK_SHIFT)) & OCOTP_CTRL_TOG_WR_UNLOCK_MASK)
/*! @} */

/*! @name PDN - OTP Controller PDN Register */
/*! @{ */

#define OCOTP_PDN_PDN_MASK                       (0x1U)
#define OCOTP_PDN_PDN_SHIFT                      (0U)
/*! PDN - PDN value
 *  0b0..OTP memory is not powered
 *  0b1..OTP memory is powered
 */
#define OCOTP_PDN_PDN(x)                         (((uint32_t)(((uint32_t)(x)) << OCOTP_PDN_PDN_SHIFT)) & OCOTP_PDN_PDN_MASK)
/*! @} */

/*! @name DATA - OTP Controller Write Data Register */
/*! @{ */

#define OCOTP_DATA_DATA_MASK                     (0xFFFFFFFFU)
#define OCOTP_DATA_DATA_SHIFT                    (0U)
/*! DATA - Data */
#define OCOTP_DATA_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_DATA_DATA_SHIFT)) & OCOTP_DATA_DATA_MASK)
/*! @} */

/*! @name READ_CTRL - OTP Controller Read Control Register */
/*! @{ */

#define OCOTP_READ_CTRL_READ_FUSE_MASK           (0x1U)
#define OCOTP_READ_CTRL_READ_FUSE_SHIFT          (0U)
/*! READ_FUSE - Read Fuse
 *  0b0..Do not initiate a read from OTP
 *  0b1..Initiate a read from OTP
 */
#define OCOTP_READ_CTRL_READ_FUSE(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_CTRL_READ_FUSE_SHIFT)) & OCOTP_READ_CTRL_READ_FUSE_MASK)

#define OCOTP_READ_CTRL_READ_FUSE_CNTR_MASK      (0x6U)
#define OCOTP_READ_CTRL_READ_FUSE_CNTR_SHIFT     (1U)
/*! READ_FUSE_CNTR - Number of words to read.
 *  0b00..1 word
 *  0b01..2 words
 *  0b10..3 words
 *  0b11..4 words
 */
#define OCOTP_READ_CTRL_READ_FUSE_CNTR(x)        (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_CTRL_READ_FUSE_CNTR_SHIFT)) & OCOTP_READ_CTRL_READ_FUSE_CNTR_MASK)

#define OCOTP_READ_CTRL_READ_FUSE_DONE_INTR_ENA_MASK (0x8U)
#define OCOTP_READ_CTRL_READ_FUSE_DONE_INTR_ENA_SHIFT (3U)
/*! READ_FUSE_DONE_INTR_ENA - Enable read-done interrupt
 *  0b0..Disable
 *  0b1..Enable
 */
#define OCOTP_READ_CTRL_READ_FUSE_DONE_INTR_ENA(x) (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_CTRL_READ_FUSE_DONE_INTR_ENA_SHIFT)) & OCOTP_READ_CTRL_READ_FUSE_DONE_INTR_ENA_MASK)

#define OCOTP_READ_CTRL_READ_FUSE_ERROR_INTR_ENA_MASK (0x10U)
#define OCOTP_READ_CTRL_READ_FUSE_ERROR_INTR_ENA_SHIFT (4U)
/*! READ_FUSE_ERROR_INTR_ENA - Enable read-error interrupt
 *  0b0..Disable
 *  0b1..Enable
 */
#define OCOTP_READ_CTRL_READ_FUSE_ERROR_INTR_ENA(x) (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_CTRL_READ_FUSE_ERROR_INTR_ENA_SHIFT)) & OCOTP_READ_CTRL_READ_FUSE_ERROR_INTR_ENA_MASK)
/*! @} */

/*! @name OUT_STATUS - 8K OTP Memory STATUS Register */
/*! @{ */

#define OCOTP_OUT_STATUS_SEC_MASK                (0x200U)
#define OCOTP_OUT_STATUS_SEC_SHIFT               (9U)
/*! SEC - Single Error Correct */
#define OCOTP_OUT_STATUS_SEC(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SEC_SHIFT)) & OCOTP_OUT_STATUS_SEC_MASK)

#define OCOTP_OUT_STATUS_DED_MASK                (0x400U)
#define OCOTP_OUT_STATUS_DED_SHIFT               (10U)
/*! DED - Double error detect */
#define OCOTP_OUT_STATUS_DED(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_DED_SHIFT)) & OCOTP_OUT_STATUS_DED_MASK)

#define OCOTP_OUT_STATUS_LOCKED_MASK             (0x800U)
#define OCOTP_OUT_STATUS_LOCKED_SHIFT            (11U)
/*! LOCKED - Word Locked */
#define OCOTP_OUT_STATUS_LOCKED(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_LOCKED_SHIFT)) & OCOTP_OUT_STATUS_LOCKED_MASK)

#define OCOTP_OUT_STATUS_PROGFAIL_MASK           (0x1000U)
#define OCOTP_OUT_STATUS_PROGFAIL_SHIFT          (12U)
/*! PROGFAIL - Programming failed */
#define OCOTP_OUT_STATUS_PROGFAIL(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_PROGFAIL_SHIFT)) & OCOTP_OUT_STATUS_PROGFAIL_MASK)

#define OCOTP_OUT_STATUS_ACK_MASK                (0x2000U)
#define OCOTP_OUT_STATUS_ACK_SHIFT               (13U)
/*! ACK - Acknowledge */
#define OCOTP_OUT_STATUS_ACK(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_ACK_SHIFT)) & OCOTP_OUT_STATUS_ACK_MASK)

#define OCOTP_OUT_STATUS_PWOK_MASK               (0x4000U)
#define OCOTP_OUT_STATUS_PWOK_SHIFT              (14U)
/*! PWOK - Power OK */
#define OCOTP_OUT_STATUS_PWOK(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_PWOK_SHIFT)) & OCOTP_OUT_STATUS_PWOK_MASK)

#define OCOTP_OUT_STATUS_FLAGSTATE_MASK          (0x78000U)
#define OCOTP_OUT_STATUS_FLAGSTATE_SHIFT         (15U)
/*! FLAGSTATE - Flag state */
#define OCOTP_OUT_STATUS_FLAGSTATE(x)            (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_FLAGSTATE_SHIFT)) & OCOTP_OUT_STATUS_FLAGSTATE_MASK)

#define OCOTP_OUT_STATUS_SEC_RELOAD_MASK         (0x80000U)
#define OCOTP_OUT_STATUS_SEC_RELOAD_SHIFT        (19U)
/*! SEC_RELOAD - Indicates single error correction occured on reload */
#define OCOTP_OUT_STATUS_SEC_RELOAD(x)           (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SEC_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_SEC_RELOAD_MASK)

#define OCOTP_OUT_STATUS_DED_RELOAD_MASK         (0x100000U)
#define OCOTP_OUT_STATUS_DED_RELOAD_SHIFT        (20U)
/*! DED_RELOAD - Indicates double error detection occured on reload */
#define OCOTP_OUT_STATUS_DED_RELOAD(x)           (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_DED_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_DED_RELOAD_MASK)

#define OCOTP_OUT_STATUS_CALIBRATED_MASK         (0x200000U)
#define OCOTP_OUT_STATUS_CALIBRATED_SHIFT        (21U)
/*! CALIBRATED - Calibrated status */
#define OCOTP_OUT_STATUS_CALIBRATED(x)           (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CALIBRATED_SHIFT)) & OCOTP_OUT_STATUS_CALIBRATED_MASK)

#define OCOTP_OUT_STATUS_READ_DONE_INTR_MASK     (0x400000U)
#define OCOTP_OUT_STATUS_READ_DONE_INTR_SHIFT    (22U)
/*! READ_DONE_INTR - Read fuse done */
#define OCOTP_OUT_STATUS_READ_DONE_INTR(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_READ_DONE_INTR_SHIFT)) & OCOTP_OUT_STATUS_READ_DONE_INTR_MASK)

#define OCOTP_OUT_STATUS_READ_ERROR_INTR_MASK    (0x800000U)
#define OCOTP_OUT_STATUS_READ_ERROR_INTR_SHIFT   (23U)
/*! READ_ERROR_INTR - Fuse read error
 *  0b0..Read operation finished with out any error
 *  0b1..Read operation finished with an error
 */
#define OCOTP_OUT_STATUS_READ_ERROR_INTR(x)      (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_READ_ERROR_INTR_SHIFT)) & OCOTP_OUT_STATUS_READ_ERROR_INTR_MASK)

#define OCOTP_OUT_STATUS_DED0_MASK               (0x1000000U)
#define OCOTP_OUT_STATUS_DED0_SHIFT              (24U)
/*! DED0 - Double error detect */
#define OCOTP_OUT_STATUS_DED0(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_DED0_SHIFT)) & OCOTP_OUT_STATUS_DED0_MASK)

#define OCOTP_OUT_STATUS_DED1_MASK               (0x2000000U)
#define OCOTP_OUT_STATUS_DED1_SHIFT              (25U)
/*! DED1 - Double error detect */
#define OCOTP_OUT_STATUS_DED1(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_DED1_SHIFT)) & OCOTP_OUT_STATUS_DED1_MASK)

#define OCOTP_OUT_STATUS_DED2_MASK               (0x4000000U)
#define OCOTP_OUT_STATUS_DED2_SHIFT              (26U)
/*! DED2 - Double error detect */
#define OCOTP_OUT_STATUS_DED2(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_DED2_SHIFT)) & OCOTP_OUT_STATUS_DED2_MASK)

#define OCOTP_OUT_STATUS_DED3_MASK               (0x8000000U)
#define OCOTP_OUT_STATUS_DED3_SHIFT              (27U)
/*! DED3 - Double error detect */
#define OCOTP_OUT_STATUS_DED3(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_DED3_SHIFT)) & OCOTP_OUT_STATUS_DED3_MASK)
/*! @} */

/*! @name OUT_STATUS_SET - 8K OTP Memory STATUS Register */
/*! @{ */

#define OCOTP_OUT_STATUS_SET_SEC_MASK            (0x200U)
#define OCOTP_OUT_STATUS_SET_SEC_SHIFT           (9U)
/*! SEC - Single Error Correct */
#define OCOTP_OUT_STATUS_SET_SEC(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_SEC_SHIFT)) & OCOTP_OUT_STATUS_SET_SEC_MASK)

#define OCOTP_OUT_STATUS_SET_DED_MASK            (0x400U)
#define OCOTP_OUT_STATUS_SET_DED_SHIFT           (10U)
/*! DED - Double error detect */
#define OCOTP_OUT_STATUS_SET_DED(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_DED_SHIFT)) & OCOTP_OUT_STATUS_SET_DED_MASK)

#define OCOTP_OUT_STATUS_SET_LOCKED_MASK         (0x800U)
#define OCOTP_OUT_STATUS_SET_LOCKED_SHIFT        (11U)
/*! LOCKED - Word Locked */
#define OCOTP_OUT_STATUS_SET_LOCKED(x)           (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_LOCKED_SHIFT)) & OCOTP_OUT_STATUS_SET_LOCKED_MASK)

#define OCOTP_OUT_STATUS_SET_PROGFAIL_MASK       (0x1000U)
#define OCOTP_OUT_STATUS_SET_PROGFAIL_SHIFT      (12U)
/*! PROGFAIL - Programming failed */
#define OCOTP_OUT_STATUS_SET_PROGFAIL(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_PROGFAIL_SHIFT)) & OCOTP_OUT_STATUS_SET_PROGFAIL_MASK)

#define OCOTP_OUT_STATUS_SET_ACK_MASK            (0x2000U)
#define OCOTP_OUT_STATUS_SET_ACK_SHIFT           (13U)
/*! ACK - Acknowledge */
#define OCOTP_OUT_STATUS_SET_ACK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_ACK_SHIFT)) & OCOTP_OUT_STATUS_SET_ACK_MASK)

#define OCOTP_OUT_STATUS_SET_PWOK_MASK           (0x4000U)
#define OCOTP_OUT_STATUS_SET_PWOK_SHIFT          (14U)
/*! PWOK - Power OK */
#define OCOTP_OUT_STATUS_SET_PWOK(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_PWOK_SHIFT)) & OCOTP_OUT_STATUS_SET_PWOK_MASK)

#define OCOTP_OUT_STATUS_SET_FLAGSTATE_MASK      (0x78000U)
#define OCOTP_OUT_STATUS_SET_FLAGSTATE_SHIFT     (15U)
/*! FLAGSTATE - Flag state */
#define OCOTP_OUT_STATUS_SET_FLAGSTATE(x)        (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_FLAGSTATE_SHIFT)) & OCOTP_OUT_STATUS_SET_FLAGSTATE_MASK)

#define OCOTP_OUT_STATUS_SET_SEC_RELOAD_MASK     (0x80000U)
#define OCOTP_OUT_STATUS_SET_SEC_RELOAD_SHIFT    (19U)
/*! SEC_RELOAD - Indicates single error correction occured on reload */
#define OCOTP_OUT_STATUS_SET_SEC_RELOAD(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_SEC_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_SET_SEC_RELOAD_MASK)

#define OCOTP_OUT_STATUS_SET_DED_RELOAD_MASK     (0x100000U)
#define OCOTP_OUT_STATUS_SET_DED_RELOAD_SHIFT    (20U)
/*! DED_RELOAD - Indicates double error detection occured on reload */
#define OCOTP_OUT_STATUS_SET_DED_RELOAD(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_DED_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_SET_DED_RELOAD_MASK)

#define OCOTP_OUT_STATUS_SET_CALIBRATED_MASK     (0x200000U)
#define OCOTP_OUT_STATUS_SET_CALIBRATED_SHIFT    (21U)
/*! CALIBRATED - Calibrated status */
#define OCOTP_OUT_STATUS_SET_CALIBRATED(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_CALIBRATED_SHIFT)) & OCOTP_OUT_STATUS_SET_CALIBRATED_MASK)

#define OCOTP_OUT_STATUS_SET_READ_DONE_INTR_MASK (0x400000U)
#define OCOTP_OUT_STATUS_SET_READ_DONE_INTR_SHIFT (22U)
/*! READ_DONE_INTR - Read fuse done */
#define OCOTP_OUT_STATUS_SET_READ_DONE_INTR(x)   (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_READ_DONE_INTR_SHIFT)) & OCOTP_OUT_STATUS_SET_READ_DONE_INTR_MASK)

#define OCOTP_OUT_STATUS_SET_READ_ERROR_INTR_MASK (0x800000U)
#define OCOTP_OUT_STATUS_SET_READ_ERROR_INTR_SHIFT (23U)
/*! READ_ERROR_INTR - Fuse read error */
#define OCOTP_OUT_STATUS_SET_READ_ERROR_INTR(x)  (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_READ_ERROR_INTR_SHIFT)) & OCOTP_OUT_STATUS_SET_READ_ERROR_INTR_MASK)

#define OCOTP_OUT_STATUS_SET_DED0_MASK           (0x1000000U)
#define OCOTP_OUT_STATUS_SET_DED0_SHIFT          (24U)
/*! DED0 - Double error detect */
#define OCOTP_OUT_STATUS_SET_DED0(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_DED0_SHIFT)) & OCOTP_OUT_STATUS_SET_DED0_MASK)

#define OCOTP_OUT_STATUS_SET_DED1_MASK           (0x2000000U)
#define OCOTP_OUT_STATUS_SET_DED1_SHIFT          (25U)
/*! DED1 - Double error detect */
#define OCOTP_OUT_STATUS_SET_DED1(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_DED1_SHIFT)) & OCOTP_OUT_STATUS_SET_DED1_MASK)

#define OCOTP_OUT_STATUS_SET_DED2_MASK           (0x4000000U)
#define OCOTP_OUT_STATUS_SET_DED2_SHIFT          (26U)
/*! DED2 - Double error detect */
#define OCOTP_OUT_STATUS_SET_DED2(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_DED2_SHIFT)) & OCOTP_OUT_STATUS_SET_DED2_MASK)

#define OCOTP_OUT_STATUS_SET_DED3_MASK           (0x8000000U)
#define OCOTP_OUT_STATUS_SET_DED3_SHIFT          (27U)
/*! DED3 - Double error detect */
#define OCOTP_OUT_STATUS_SET_DED3(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_SET_DED3_SHIFT)) & OCOTP_OUT_STATUS_SET_DED3_MASK)
/*! @} */

/*! @name OUT_STATUS_CLR - 8K OTP Memory STATUS Register */
/*! @{ */

#define OCOTP_OUT_STATUS_CLR_SEC_MASK            (0x200U)
#define OCOTP_OUT_STATUS_CLR_SEC_SHIFT           (9U)
/*! SEC - Single Error Correct */
#define OCOTP_OUT_STATUS_CLR_SEC(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_SEC_SHIFT)) & OCOTP_OUT_STATUS_CLR_SEC_MASK)

#define OCOTP_OUT_STATUS_CLR_DED_MASK            (0x400U)
#define OCOTP_OUT_STATUS_CLR_DED_SHIFT           (10U)
/*! DED - Double error detect */
#define OCOTP_OUT_STATUS_CLR_DED(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_DED_SHIFT)) & OCOTP_OUT_STATUS_CLR_DED_MASK)

#define OCOTP_OUT_STATUS_CLR_LOCKED_MASK         (0x800U)
#define OCOTP_OUT_STATUS_CLR_LOCKED_SHIFT        (11U)
/*! LOCKED - Word Locked */
#define OCOTP_OUT_STATUS_CLR_LOCKED(x)           (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_LOCKED_SHIFT)) & OCOTP_OUT_STATUS_CLR_LOCKED_MASK)

#define OCOTP_OUT_STATUS_CLR_PROGFAIL_MASK       (0x1000U)
#define OCOTP_OUT_STATUS_CLR_PROGFAIL_SHIFT      (12U)
/*! PROGFAIL - Programming failed */
#define OCOTP_OUT_STATUS_CLR_PROGFAIL(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_PROGFAIL_SHIFT)) & OCOTP_OUT_STATUS_CLR_PROGFAIL_MASK)

#define OCOTP_OUT_STATUS_CLR_ACK_MASK            (0x2000U)
#define OCOTP_OUT_STATUS_CLR_ACK_SHIFT           (13U)
/*! ACK - Acknowledge */
#define OCOTP_OUT_STATUS_CLR_ACK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_ACK_SHIFT)) & OCOTP_OUT_STATUS_CLR_ACK_MASK)

#define OCOTP_OUT_STATUS_CLR_PWOK_MASK           (0x4000U)
#define OCOTP_OUT_STATUS_CLR_PWOK_SHIFT          (14U)
/*! PWOK - Power OK */
#define OCOTP_OUT_STATUS_CLR_PWOK(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_PWOK_SHIFT)) & OCOTP_OUT_STATUS_CLR_PWOK_MASK)

#define OCOTP_OUT_STATUS_CLR_FLAGSTATE_MASK      (0x78000U)
#define OCOTP_OUT_STATUS_CLR_FLAGSTATE_SHIFT     (15U)
/*! FLAGSTATE - Flag state */
#define OCOTP_OUT_STATUS_CLR_FLAGSTATE(x)        (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_FLAGSTATE_SHIFT)) & OCOTP_OUT_STATUS_CLR_FLAGSTATE_MASK)

#define OCOTP_OUT_STATUS_CLR_SEC_RELOAD_MASK     (0x80000U)
#define OCOTP_OUT_STATUS_CLR_SEC_RELOAD_SHIFT    (19U)
/*! SEC_RELOAD - Indicates single error correction occured on reload */
#define OCOTP_OUT_STATUS_CLR_SEC_RELOAD(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_SEC_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_CLR_SEC_RELOAD_MASK)

#define OCOTP_OUT_STATUS_CLR_DED_RELOAD_MASK     (0x100000U)
#define OCOTP_OUT_STATUS_CLR_DED_RELOAD_SHIFT    (20U)
/*! DED_RELOAD - Indicates double error detection occured on reload */
#define OCOTP_OUT_STATUS_CLR_DED_RELOAD(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_DED_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_CLR_DED_RELOAD_MASK)

#define OCOTP_OUT_STATUS_CLR_CALIBRATED_MASK     (0x200000U)
#define OCOTP_OUT_STATUS_CLR_CALIBRATED_SHIFT    (21U)
/*! CALIBRATED - Calibrated status */
#define OCOTP_OUT_STATUS_CLR_CALIBRATED(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_CALIBRATED_SHIFT)) & OCOTP_OUT_STATUS_CLR_CALIBRATED_MASK)

#define OCOTP_OUT_STATUS_CLR_READ_DONE_INTR_MASK (0x400000U)
#define OCOTP_OUT_STATUS_CLR_READ_DONE_INTR_SHIFT (22U)
/*! READ_DONE_INTR - Read fuse done */
#define OCOTP_OUT_STATUS_CLR_READ_DONE_INTR(x)   (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_READ_DONE_INTR_SHIFT)) & OCOTP_OUT_STATUS_CLR_READ_DONE_INTR_MASK)

#define OCOTP_OUT_STATUS_CLR_READ_ERROR_INTR_MASK (0x800000U)
#define OCOTP_OUT_STATUS_CLR_READ_ERROR_INTR_SHIFT (23U)
/*! READ_ERROR_INTR - Fuse read error */
#define OCOTP_OUT_STATUS_CLR_READ_ERROR_INTR(x)  (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_READ_ERROR_INTR_SHIFT)) & OCOTP_OUT_STATUS_CLR_READ_ERROR_INTR_MASK)

#define OCOTP_OUT_STATUS_CLR_DED0_MASK           (0x1000000U)
#define OCOTP_OUT_STATUS_CLR_DED0_SHIFT          (24U)
/*! DED0 - Double error detect */
#define OCOTP_OUT_STATUS_CLR_DED0(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_DED0_SHIFT)) & OCOTP_OUT_STATUS_CLR_DED0_MASK)

#define OCOTP_OUT_STATUS_CLR_DED1_MASK           (0x2000000U)
#define OCOTP_OUT_STATUS_CLR_DED1_SHIFT          (25U)
/*! DED1 - Double error detect */
#define OCOTP_OUT_STATUS_CLR_DED1(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_DED1_SHIFT)) & OCOTP_OUT_STATUS_CLR_DED1_MASK)

#define OCOTP_OUT_STATUS_CLR_DED2_MASK           (0x4000000U)
#define OCOTP_OUT_STATUS_CLR_DED2_SHIFT          (26U)
/*! DED2 - Double error detect */
#define OCOTP_OUT_STATUS_CLR_DED2(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_DED2_SHIFT)) & OCOTP_OUT_STATUS_CLR_DED2_MASK)

#define OCOTP_OUT_STATUS_CLR_DED3_MASK           (0x8000000U)
#define OCOTP_OUT_STATUS_CLR_DED3_SHIFT          (27U)
/*! DED3 - Double error detect */
#define OCOTP_OUT_STATUS_CLR_DED3(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_CLR_DED3_SHIFT)) & OCOTP_OUT_STATUS_CLR_DED3_MASK)
/*! @} */

/*! @name OUT_STATUS_TOG - 8K OTP Memory STATUS Register */
/*! @{ */

#define OCOTP_OUT_STATUS_TOG_SEC_MASK            (0x200U)
#define OCOTP_OUT_STATUS_TOG_SEC_SHIFT           (9U)
/*! SEC - Single Error Correct */
#define OCOTP_OUT_STATUS_TOG_SEC(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_SEC_SHIFT)) & OCOTP_OUT_STATUS_TOG_SEC_MASK)

#define OCOTP_OUT_STATUS_TOG_DED_MASK            (0x400U)
#define OCOTP_OUT_STATUS_TOG_DED_SHIFT           (10U)
/*! DED - Double error detect */
#define OCOTP_OUT_STATUS_TOG_DED(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_DED_SHIFT)) & OCOTP_OUT_STATUS_TOG_DED_MASK)

#define OCOTP_OUT_STATUS_TOG_LOCKED_MASK         (0x800U)
#define OCOTP_OUT_STATUS_TOG_LOCKED_SHIFT        (11U)
/*! LOCKED - Word Locked */
#define OCOTP_OUT_STATUS_TOG_LOCKED(x)           (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_LOCKED_SHIFT)) & OCOTP_OUT_STATUS_TOG_LOCKED_MASK)

#define OCOTP_OUT_STATUS_TOG_PROGFAIL_MASK       (0x1000U)
#define OCOTP_OUT_STATUS_TOG_PROGFAIL_SHIFT      (12U)
/*! PROGFAIL - Programming failed */
#define OCOTP_OUT_STATUS_TOG_PROGFAIL(x)         (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_PROGFAIL_SHIFT)) & OCOTP_OUT_STATUS_TOG_PROGFAIL_MASK)

#define OCOTP_OUT_STATUS_TOG_ACK_MASK            (0x2000U)
#define OCOTP_OUT_STATUS_TOG_ACK_SHIFT           (13U)
/*! ACK - Acknowledge */
#define OCOTP_OUT_STATUS_TOG_ACK(x)              (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_ACK_SHIFT)) & OCOTP_OUT_STATUS_TOG_ACK_MASK)

#define OCOTP_OUT_STATUS_TOG_PWOK_MASK           (0x4000U)
#define OCOTP_OUT_STATUS_TOG_PWOK_SHIFT          (14U)
/*! PWOK - Power OK */
#define OCOTP_OUT_STATUS_TOG_PWOK(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_PWOK_SHIFT)) & OCOTP_OUT_STATUS_TOG_PWOK_MASK)

#define OCOTP_OUT_STATUS_TOG_FLAGSTATE_MASK      (0x78000U)
#define OCOTP_OUT_STATUS_TOG_FLAGSTATE_SHIFT     (15U)
/*! FLAGSTATE - Flag state */
#define OCOTP_OUT_STATUS_TOG_FLAGSTATE(x)        (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_FLAGSTATE_SHIFT)) & OCOTP_OUT_STATUS_TOG_FLAGSTATE_MASK)

#define OCOTP_OUT_STATUS_TOG_SEC_RELOAD_MASK     (0x80000U)
#define OCOTP_OUT_STATUS_TOG_SEC_RELOAD_SHIFT    (19U)
/*! SEC_RELOAD - Indicates single error correction occured on reload */
#define OCOTP_OUT_STATUS_TOG_SEC_RELOAD(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_SEC_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_TOG_SEC_RELOAD_MASK)

#define OCOTP_OUT_STATUS_TOG_DED_RELOAD_MASK     (0x100000U)
#define OCOTP_OUT_STATUS_TOG_DED_RELOAD_SHIFT    (20U)
/*! DED_RELOAD - Indicates double error detection occured on reload */
#define OCOTP_OUT_STATUS_TOG_DED_RELOAD(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_DED_RELOAD_SHIFT)) & OCOTP_OUT_STATUS_TOG_DED_RELOAD_MASK)

#define OCOTP_OUT_STATUS_TOG_CALIBRATED_MASK     (0x200000U)
#define OCOTP_OUT_STATUS_TOG_CALIBRATED_SHIFT    (21U)
/*! CALIBRATED - Calibrated status */
#define OCOTP_OUT_STATUS_TOG_CALIBRATED(x)       (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_CALIBRATED_SHIFT)) & OCOTP_OUT_STATUS_TOG_CALIBRATED_MASK)

#define OCOTP_OUT_STATUS_TOG_READ_DONE_INTR_MASK (0x400000U)
#define OCOTP_OUT_STATUS_TOG_READ_DONE_INTR_SHIFT (22U)
/*! READ_DONE_INTR - Read fuse done */
#define OCOTP_OUT_STATUS_TOG_READ_DONE_INTR(x)   (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_READ_DONE_INTR_SHIFT)) & OCOTP_OUT_STATUS_TOG_READ_DONE_INTR_MASK)

#define OCOTP_OUT_STATUS_TOG_READ_ERROR_INTR_MASK (0x800000U)
#define OCOTP_OUT_STATUS_TOG_READ_ERROR_INTR_SHIFT (23U)
/*! READ_ERROR_INTR - Fuse read error */
#define OCOTP_OUT_STATUS_TOG_READ_ERROR_INTR(x)  (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_READ_ERROR_INTR_SHIFT)) & OCOTP_OUT_STATUS_TOG_READ_ERROR_INTR_MASK)

#define OCOTP_OUT_STATUS_TOG_DED0_MASK           (0x1000000U)
#define OCOTP_OUT_STATUS_TOG_DED0_SHIFT          (24U)
/*! DED0 - Double error detect */
#define OCOTP_OUT_STATUS_TOG_DED0(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_DED0_SHIFT)) & OCOTP_OUT_STATUS_TOG_DED0_MASK)

#define OCOTP_OUT_STATUS_TOG_DED1_MASK           (0x2000000U)
#define OCOTP_OUT_STATUS_TOG_DED1_SHIFT          (25U)
/*! DED1 - Double error detect */
#define OCOTP_OUT_STATUS_TOG_DED1(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_DED1_SHIFT)) & OCOTP_OUT_STATUS_TOG_DED1_MASK)

#define OCOTP_OUT_STATUS_TOG_DED2_MASK           (0x4000000U)
#define OCOTP_OUT_STATUS_TOG_DED2_SHIFT          (26U)
/*! DED2 - Double error detect */
#define OCOTP_OUT_STATUS_TOG_DED2(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_DED2_SHIFT)) & OCOTP_OUT_STATUS_TOG_DED2_MASK)

#define OCOTP_OUT_STATUS_TOG_DED3_MASK           (0x8000000U)
#define OCOTP_OUT_STATUS_TOG_DED3_SHIFT          (27U)
/*! DED3 - Double error detect */
#define OCOTP_OUT_STATUS_TOG_DED3(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_OUT_STATUS_TOG_DED3_SHIFT)) & OCOTP_OUT_STATUS_TOG_DED3_MASK)
/*! @} */

/*! @name VERSION - OTP Controller Version Register */
/*! @{ */

#define OCOTP_VERSION_STEP_MASK                  (0xFFFFU)
#define OCOTP_VERSION_STEP_SHIFT                 (0U)
/*! STEP - RTL Version Stepping */
#define OCOTP_VERSION_STEP(x)                    (((uint32_t)(((uint32_t)(x)) << OCOTP_VERSION_STEP_SHIFT)) & OCOTP_VERSION_STEP_MASK)

#define OCOTP_VERSION_MINOR_MASK                 (0xFF0000U)
#define OCOTP_VERSION_MINOR_SHIFT                (16U)
/*! MINOR - Minor RTL Version */
#define OCOTP_VERSION_MINOR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_VERSION_MINOR_SHIFT)) & OCOTP_VERSION_MINOR_MASK)

#define OCOTP_VERSION_MAJOR_MASK                 (0xFF000000U)
#define OCOTP_VERSION_MAJOR_SHIFT                (24U)
/*! MAJOR - Major RTL Version */
#define OCOTP_VERSION_MAJOR(x)                   (((uint32_t)(((uint32_t)(x)) << OCOTP_VERSION_MAJOR_SHIFT)) & OCOTP_VERSION_MAJOR_MASK)
/*! @} */

/*! @name READ_FUSE_DATA - OTP Controller Read Data 0 Register..OTP Controller Read Data 3 Register */
/*! @{ */

#define OCOTP_READ_FUSE_DATA_DATA_MASK           (0xFFFFFFFFU)
#define OCOTP_READ_FUSE_DATA_DATA_SHIFT          (0U)
/*! DATA - Data */
#define OCOTP_READ_FUSE_DATA_DATA(x)             (((uint32_t)(((uint32_t)(x)) << OCOTP_READ_FUSE_DATA_DATA_SHIFT)) & OCOTP_READ_FUSE_DATA_DATA_MASK)
/*! @} */

/* The count of OCOTP_READ_FUSE_DATA */
#define OCOTP_READ_FUSE_DATA_COUNT               (4U)

/*! @name SW_LOCK - SW_LOCK Register */
/*! @{ */

#define OCOTP_SW_LOCK_SW_LOCK_MASK               (0xFFFFFFFFU)
#define OCOTP_SW_LOCK_SW_LOCK_SHIFT              (0U)
#define OCOTP_SW_LOCK_SW_LOCK(x)                 (((uint32_t)(((uint32_t)(x)) << OCOTP_SW_LOCK_SW_LOCK_SHIFT)) & OCOTP_SW_LOCK_SW_LOCK_MASK)
/*! @} */

/*! @name BIT_LOCK - BIT_LOCK Register */
/*! @{ */

#define OCOTP_BIT_LOCK_BIT_LOCK_MASK             (0xFFFFFFFFU)
#define OCOTP_BIT_LOCK_BIT_LOCK_SHIFT            (0U)
#define OCOTP_BIT_LOCK_BIT_LOCK(x)               (((uint32_t)(((uint32_t)(x)) << OCOTP_BIT_LOCK_BIT_LOCK_SHIFT)) & OCOTP_BIT_LOCK_BIT_LOCK_MASK)
/*! @} */

/*! @name LOCKED0 - OTP Controller Program Locked Status 0 Register */
/*! @{ */

#define OCOTP_LOCKED0_LOCKED_MASK                (0xFFFFU)
#define OCOTP_LOCKED0_LOCKED_SHIFT               (0U)
#define OCOTP_LOCKED0_LOCKED(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCKED0_LOCKED_SHIFT)) & OCOTP_LOCKED0_LOCKED_MASK)
/*! @} */

/*! @name LOCKED1 - OTP Controller Program Locked Status 1 Register */
/*! @{ */

#define OCOTP_LOCKED1_LOCKED_MASK                (0xFFFFFFFFU)
#define OCOTP_LOCKED1_LOCKED_SHIFT               (0U)
#define OCOTP_LOCKED1_LOCKED(x)                  (((uint32_t)(((uint32_t)(x)) << OCOTP_LOCKED1_LOCKED_SHIFT)) & OCOTP_LOCKED1_LOCKED_MASK)
/*! @} */

/*! @name FUSE - Value of fuse word 0..Value of fuse word 143 */
/*! @{ */

#define OCOTP_FUSE_BITS_MASK                     (0xFFFFFFFFU)
#define OCOTP_FUSE_BITS_SHIFT                    (0U)
/*! BITS - Reflects value of the fuse word */
#define OCOTP_FUSE_BITS(x)                       (((uint32_t)(((uint32_t)(x)) << OCOTP_FUSE_BITS_SHIFT)) & OCOTP_FUSE_BITS_MASK)
/*! @} */

/* The count of OCOTP_FUSE */
#define OCOTP_FUSE_COUNT                         (144U)


/*!
 * @}
 */ /* end of group OCOTP_Register_Masks */


/*!
 * @}
 */ /* end of group OCOTP_Peripheral_Access_Layer */


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


#endif  /* PERI_OCOTP_H_ */

