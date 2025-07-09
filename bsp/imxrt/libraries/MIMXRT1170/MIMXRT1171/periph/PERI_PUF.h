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
**         CMSIS Peripheral Access Layer for PUF
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
 * @file PERI_PUF.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for PUF
 *
 * CMSIS Peripheral Access Layer for PUF
 */

#if !defined(PERI_PUF_H_)
#define PERI_PUF_H_                              /**< Symbol preventing repeated inclusion */

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
   -- PUF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PUF_Peripheral_Access_Layer PUF Peripheral Access Layer
 * @{
 */

/** PUF - Size of Registers Arrays */
#define PUF_KEYMASK_COUNT                         2u

/** PUF - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< PUF Control Register, offset: 0x0 */
  __IO uint32_t KEYINDEX;                          /**< PUF Key Index Register, offset: 0x4 */
  __IO uint32_t KEYSIZE;                           /**< PUF Key Size Register, offset: 0x8 */
       uint8_t RESERVED_0[20];
  __I  uint32_t STAT;                              /**< PUF Status Register, offset: 0x20 */
       uint8_t RESERVED_1[4];
  __I  uint32_t ALLOW;                             /**< PUF Allow Register, offset: 0x28 */
       uint8_t RESERVED_2[20];
  __O  uint32_t KEYINPUT;                          /**< PUF Key Input Register, offset: 0x40 */
  __O  uint32_t CODEINPUT;                         /**< PUF Code Input Register, offset: 0x44 */
  __I  uint32_t CODEOUTPUT;                        /**< PUF Code Output Register, offset: 0x48 */
       uint8_t RESERVED_3[20];
  __I  uint32_t KEYOUTINDEX;                       /**< PUF Key Output Index Register, offset: 0x60 */
  __I  uint32_t KEYOUTPUT;                         /**< PUF Key Output Register, offset: 0x64 */
       uint8_t RESERVED_4[116];
  __IO uint32_t IFSTAT;                            /**< PUF Interface Status Register, offset: 0xDC */
       uint8_t RESERVED_5[28];
  __I  uint32_t VERSION;                           /**< PUF Version Register, offset: 0xFC */
  __IO uint32_t INTEN;                             /**< PUF Interrupt Enable, offset: 0x100 */
  __IO uint32_t INTSTAT;                           /**< PUF Interrupt Status, offset: 0x104 */
  __IO uint32_t PWRCTRL;                           /**< PUF Power Control Of RAM, offset: 0x108 */
  __IO uint32_t CFG;                               /**< PUF Configuration Register, offset: 0x10C */
       uint8_t RESERVED_6[240];
  __IO uint32_t KEYLOCK;                           /**< PUF Key Manager Lock, offset: 0x200 */
  __IO uint32_t KEYENABLE;                         /**< PUF Key Manager Enable, offset: 0x204 */
  __O  uint32_t KEYRESET;                          /**< PUF Key Manager Reset, offset: 0x208 */
  __O  uint32_t IDXBLK;                            /**< PUF Index Block Key Output, offset: 0x20C */
  __O  uint32_t IDXBLK_DP;                         /**< PUF Index Block Key Output, offset: 0x210 */
  __O  uint32_t KEYMASK[PUF_KEYMASK_COUNT];        /**< PUF Key Block 0 Mask Enable..PUF Key Block 1 Mask Enable, array offset: 0x214, array step: 0x4 */
       uint8_t RESERVED_7[56];
  __I  uint32_t IDXBLK_STATUS;                     /**< PUF Index Block Setting Status Register, offset: 0x254 */
  __I  uint32_t IDXBLK_SHIFT;                      /**< PUF Key Manager Shift Status, offset: 0x258 */
} PUF_Type;

/* ----------------------------------------------------------------------------
   -- PUF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PUF_Register_Masks PUF Register Masks
 * @{
 */

/*! @name CTRL - PUF Control Register */
/*! @{ */

#define PUF_CTRL_ZEROIZE_MASK                    (0x1U)
#define PUF_CTRL_ZEROIZE_SHIFT                   (0U)
/*! ZEROIZE - Begin Zeroize operation for PUF and go to Error state
 *  0b0..No Zeroize operation in progress
 *  0b1..Zeroize operation in progress
 */
#define PUF_CTRL_ZEROIZE(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_ZEROIZE_SHIFT)) & PUF_CTRL_ZEROIZE_MASK)

#define PUF_CTRL_ENROLL_MASK                     (0x2U)
#define PUF_CTRL_ENROLL_SHIFT                    (1U)
/*! ENROLL - Begin Enroll operation
 *  0b0..No Enroll operation in progress
 *  0b1..Enroll operation in progress
 */
#define PUF_CTRL_ENROLL(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_ENROLL_SHIFT)) & PUF_CTRL_ENROLL_MASK)

#define PUF_CTRL_START_MASK                      (0x4U)
#define PUF_CTRL_START_SHIFT                     (2U)
/*! START - Begin Start operation
 *  0b0..No Start operation in progress
 *  0b1..Start operation in progress
 */
#define PUF_CTRL_START(x)                        (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_START_SHIFT)) & PUF_CTRL_START_MASK)

#define PUF_CTRL_GENERATEKEY_MASK                (0x8U)
#define PUF_CTRL_GENERATEKEY_SHIFT               (3U)
/*! GENERATEKEY - Begin Set Intrinsic Key operation
 *  0b0..No Set Intrinsic Key operation in progress
 *  0b1..Set Intrinsic Key operation in progress
 */
#define PUF_CTRL_GENERATEKEY(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_GENERATEKEY_SHIFT)) & PUF_CTRL_GENERATEKEY_MASK)

#define PUF_CTRL_SETKEY_MASK                     (0x10U)
#define PUF_CTRL_SETKEY_SHIFT                    (4U)
/*! SETKEY - Begin Set User Key operation
 *  0b0..No Set Key operation in progress
 *  0b1..Set Key operation in progress
 */
#define PUF_CTRL_SETKEY(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_SETKEY_SHIFT)) & PUF_CTRL_SETKEY_MASK)

#define PUF_CTRL_GETKEY_MASK                     (0x40U)
#define PUF_CTRL_GETKEY_SHIFT                    (6U)
/*! GETKEY - Begin Get Key operation
 *  0b0..No Get Key operation in progress
 *  0b1..Get Key operation in progress
 */
#define PUF_CTRL_GETKEY(x)                       (((uint32_t)(((uint32_t)(x)) << PUF_CTRL_GETKEY_SHIFT)) & PUF_CTRL_GETKEY_MASK)
/*! @} */

/*! @name KEYINDEX - PUF Key Index Register */
/*! @{ */

#define PUF_KEYINDEX_KEYIDX_MASK                 (0xFU)
#define PUF_KEYINDEX_KEYIDX_SHIFT                (0U)
/*! KEYIDX - PUF Key Index
 *  0b0000..USE INDEX0
 *  0b0001..USE INDEX1
 *  0b0010..USE INDEX2
 *  0b0011..USE INDEX3
 *  0b0100..USE INDEX4
 *  0b0101..USE INDEX5
 *  0b0110..USE INDEX6
 *  0b0111..USE INDEX7
 *  0b1000..USE INDEX8
 *  0b1001..USE INDEX9
 *  0b1010..USE INDEX10
 *  0b1011..USE INDEX11
 *  0b1100..USE INDEX12
 *  0b1101..USE INDEX13
 *  0b1110..USE INDEX14
 *  0b1111..USE INDEX15
 */
#define PUF_KEYINDEX_KEYIDX(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYINDEX_KEYIDX_SHIFT)) & PUF_KEYINDEX_KEYIDX_MASK)
/*! @} */

/*! @name KEYSIZE - PUF Key Size Register */
/*! @{ */

#define PUF_KEYSIZE_KEYSIZE_MASK                 (0x3FU)
#define PUF_KEYSIZE_KEYSIZE_SHIFT                (0U)
/*! KEYSIZE - PUF Key Size
 *  0b000000..Key Size is 512 Bytes and KC Size is 532 Bytes
 *  0b000001..Key Size is 8 Bytes and KC Size is 52 Bytes
 *  0b000010..Key Size is 16 Bytes and KC Size is 52 Bytes
 *  0b000011..Key Size is 24 Bytes and KC Size is 52 Bytes
 *  0b000100..Key Size is 32 Bytes and KC Size is 52 Bytes
 *  0b000101..Key Size is 40 Bytes and KC Size is 84 Bytes
 *  0b000110..Key Size is 48 Bytes and KC Size is 84 Bytes
 *  0b000111..Key Size is 56 Bytes and KC Size is 84 Bytes
 *  0b001000..Key Size is 64 Bytes and KC Size is 84 Bytes
 *  0b001001..Key Size is 72 Bytes and KC Size is 116 Bytes
 *  0b001010..Key Size is 80 Bytes and KC Size is 116 Bytes
 *  0b001011..Key Size is 88 Bytes and KC Size is 116 Bytes
 *  0b001100..Key Size is 96 Bytes and KC Size is 116 Bytes
 *  0b001101..Key Size is 104 Bytes and KC Size is 148 Bytes
 *  0b001110..Key Size is 112 Bytes and KC Size is 148 Bytes
 *  0b001111..Key Size is 120 Bytes and KC Size is 148 Bytes
 *  0b010000..Key Size is 128 Bytes and KC Size is 148 Bytes
 *  0b010001..Key Size is 136 Bytes and KC Size is 180 Bytes
 *  0b010010..Key Size is 144 Bytes and KC Size is 180 Bytes
 *  0b010011..Key Size is 152 Bytes and KC Size is 180 Bytes
 *  0b010100..Key Size is 160 Bytes and KC Size is 180 Bytes
 *  0b010101..Key Size is 168 Bytes and KC Size is 212 Bytes
 *  0b010110..Key Size is 176 Bytes and KC Size is 212 Bytes
 *  0b010111..Key Size is 184 Bytes and KC Size is 212 Bytes
 *  0b011000..Key Size is 192 Bytes and KC Size is 212 Bytes
 *  0b011001..Key Size is 200 Bytes and KC Size is 244 Bytes
 *  0b011010..Key Size is 208 Bytes and KC Size is 244 Bytes
 *  0b011011..Key Size is 216 Bytes and KC Size is 244 Bytes
 *  0b011100..Key Size is 224 Bytes and KC Size is 244 Bytes
 *  0b011101..Key Size is 232 Bytes and KC Size is 276 Bytes
 *  0b011110..Key Size is 240 Bytes and KC Size is 276 Bytes
 *  0b011111..Key Size is 248 Bytes and KC Size is 276 Bytes
 *  0b100000..Key Size is 256 Bytes and KC Size is 276 Bytes
 *  0b100001..Key Size is 264 Bytes and KC Size is 308 Bytes
 *  0b100010..Key Size is 272 Bytes and KC Size is 308 Bytes
 *  0b100011..Key Size is 280 Bytes and KC Size is 308 Bytes
 *  0b100100..Key Size is 288 Bytes and KC Size is 308 Bytes
 *  0b100101..Key Size is 296 Bytes and KC Size is 340 Bytes
 *  0b100110..Key Size is 304 Bytes and KC Size is 340 Bytes
 *  0b100111..Key Size is 312 Bytes and KC Size is 340 Bytes
 *  0b101000..Key Size is 320 Bytes and KC Size is 340 Bytes
 *  0b101001..Key Size is 328 Bytes and KC Size is 372 Bytes
 *  0b101010..Key Size is 336 Bytes and KC Size is 372 Bytes
 *  0b101011..Key Size is 344 Bytes and KC Size is 372 Bytes
 *  0b101100..Key Size is 352 Bytes and KC Size is 372 Bytes
 *  0b101101..Key Size is 360 Bytes and KC Size is 404 Bytes
 *  0b101110..Key Size is 368 Bytes and KC Size is 404 Bytes
 *  0b101111..Key Size is 376 Bytes and KC Size is 404 Bytes
 *  0b110000..Key Size is 384 Bytes and KC Size is 404 Bytes
 *  0b110001..Key Size is 392 Bytes and KC Size is 436 Bytes
 *  0b110010..Key Size is 400 Bytes and KC Size is 436 Bytes
 *  0b110011..Key Size is 408 Bytes and KC Size is 436 Bytes
 *  0b110100..Key Size is 416 Bytes and KC Size is 436 Bytes
 *  0b110101..Key Size is 424 Bytes and KC Size is 468 Bytes
 *  0b110110..Key Size is 432 Bytes and KC Size is 468 Bytes
 *  0b110111..Key Size is 440 Bytes and KC Size is 468 Bytes
 *  0b111000..Key Size is 448 Bytes and KC Size is 468 Bytes
 *  0b111001..Key Size is 456 Bytes and KC Size is 500 Bytes
 *  0b111010..Key Size is 464 Bytes and KC Size is 500 Bytes
 *  0b111011..Key Size is 472 Bytes and KC Size is 500 Bytes
 *  0b111100..Key Size is 480 Bytes and KC Size is 500 Bytes
 *  0b111101..Key Size is 488 Bytes and KC Size is 532 Bytes
 *  0b111110..Key Size is 496 Bytes and KC Size is 532 Bytes
 *  0b111111..Key Size is 504 Bytes and KC Size is 532 Bytes
 */
#define PUF_KEYSIZE_KEYSIZE(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYSIZE_KEYSIZE_SHIFT)) & PUF_KEYSIZE_KEYSIZE_MASK)
/*! @} */

/*! @name STAT - PUF Status Register */
/*! @{ */

#define PUF_STAT_BUSY_MASK                       (0x1U)
#define PUF_STAT_BUSY_SHIFT                      (0U)
/*! BUSY - puf_busy
 *  0b0..IDLE
 *  0b1..BUSY
 */
#define PUF_STAT_BUSY(x)                         (((uint32_t)(((uint32_t)(x)) << PUF_STAT_BUSY_SHIFT)) & PUF_STAT_BUSY_MASK)

#define PUF_STAT_SUCCESS_MASK                    (0x2U)
#define PUF_STAT_SUCCESS_SHIFT                   (1U)
/*! SUCCESS - puf_ok
 *  0b0..Last operation was unsuccessful
 *  0b1..Last operation was successful
 */
#define PUF_STAT_SUCCESS(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_STAT_SUCCESS_SHIFT)) & PUF_STAT_SUCCESS_MASK)

#define PUF_STAT_ERROR_MASK                      (0x4U)
#define PUF_STAT_ERROR_SHIFT                     (2U)
/*! ERROR - puf_error
 *  0b0..PUF is not in the Error state
 *  0b1..PUF is in the Error state
 */
#define PUF_STAT_ERROR(x)                        (((uint32_t)(((uint32_t)(x)) << PUF_STAT_ERROR_SHIFT)) & PUF_STAT_ERROR_MASK)

#define PUF_STAT_KEYINREQ_MASK                   (0x10U)
#define PUF_STAT_KEYINREQ_SHIFT                  (4U)
/*! KEYINREQ - KI_ir
 *  0b0..No request for next part of key
 *  0b1..Request for next part of key in KEYINPUT register
 */
#define PUF_STAT_KEYINREQ(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_STAT_KEYINREQ_SHIFT)) & PUF_STAT_KEYINREQ_MASK)

#define PUF_STAT_KEYOUTAVAIL_MASK                (0x20U)
#define PUF_STAT_KEYOUTAVAIL_SHIFT               (5U)
/*! KEYOUTAVAIL - KO_or
 *  0b0..Next part of key is not available
 *  0b1..Next part of key is available in KEYOUTPUT register
 */
#define PUF_STAT_KEYOUTAVAIL(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_STAT_KEYOUTAVAIL_SHIFT)) & PUF_STAT_KEYOUTAVAIL_MASK)

#define PUF_STAT_CODEINREQ_MASK                  (0x40U)
#define PUF_STAT_CODEINREQ_SHIFT                 (6U)
/*! CODEINREQ - CI_ir
 *  0b0..No request for next part of Activation Code/Key Code
 *  0b1..request for next part of Activation Code/Key Code in CODEINPUT register
 */
#define PUF_STAT_CODEINREQ(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_STAT_CODEINREQ_SHIFT)) & PUF_STAT_CODEINREQ_MASK)

#define PUF_STAT_CODEOUTAVAIL_MASK               (0x80U)
#define PUF_STAT_CODEOUTAVAIL_SHIFT              (7U)
/*! CODEOUTAVAIL - CO_or
 *  0b0..Next part of Activation Code/Key Code is not available
 *  0b1..Next part of Activation Code/Key Code is available in CODEOUTPUT register
 */
#define PUF_STAT_CODEOUTAVAIL(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_STAT_CODEOUTAVAIL_SHIFT)) & PUF_STAT_CODEOUTAVAIL_MASK)
/*! @} */

/*! @name ALLOW - PUF Allow Register */
/*! @{ */

#define PUF_ALLOW_ALLOWENROLL_MASK               (0x1U)
#define PUF_ALLOW_ALLOWENROLL_SHIFT              (0U)
/*! ALLOWENROLL - Allow Enroll operation
 *  0b0..Specified operation is not currently allowed
 *  0b1..Specified operation is allowed
 */
#define PUF_ALLOW_ALLOWENROLL(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWENROLL_SHIFT)) & PUF_ALLOW_ALLOWENROLL_MASK)

#define PUF_ALLOW_ALLOWSTART_MASK                (0x2U)
#define PUF_ALLOW_ALLOWSTART_SHIFT               (1U)
/*! ALLOWSTART - Allow Start operation
 *  0b0..Specified operation is not currently allowed
 *  0b1..Specified operation is allowed
 */
#define PUF_ALLOW_ALLOWSTART(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWSTART_SHIFT)) & PUF_ALLOW_ALLOWSTART_MASK)

#define PUF_ALLOW_ALLOWSETKEY_MASK               (0x4U)
#define PUF_ALLOW_ALLOWSETKEY_SHIFT              (2U)
/*! ALLOWSETKEY - Allow Set Key operations
 *  0b0..Specified operation is not currently allowed
 *  0b1..Specified operation is allowed
 */
#define PUF_ALLOW_ALLOWSETKEY(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWSETKEY_SHIFT)) & PUF_ALLOW_ALLOWSETKEY_MASK)

#define PUF_ALLOW_ALLOWGETKEY_MASK               (0x8U)
#define PUF_ALLOW_ALLOWGETKEY_SHIFT              (3U)
/*! ALLOWGETKEY - Allow Get Key operation
 *  0b0..Specified operation is not currently allowed
 *  0b1..Specified operation is allowed
 */
#define PUF_ALLOW_ALLOWGETKEY(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_ALLOW_ALLOWGETKEY_SHIFT)) & PUF_ALLOW_ALLOWGETKEY_MASK)
/*! @} */

/*! @name KEYINPUT - PUF Key Input Register */
/*! @{ */

#define PUF_KEYINPUT_KEYIN_MASK                  (0xFFFFFFFFU)
#define PUF_KEYINPUT_KEYIN_SHIFT                 (0U)
/*! KEYIN - Key input data */
#define PUF_KEYINPUT_KEYIN(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_KEYINPUT_KEYIN_SHIFT)) & PUF_KEYINPUT_KEYIN_MASK)
/*! @} */

/*! @name CODEINPUT - PUF Code Input Register */
/*! @{ */

#define PUF_CODEINPUT_CODEIN_MASK                (0xFFFFFFFFU)
#define PUF_CODEINPUT_CODEIN_SHIFT               (0U)
/*! CODEIN - AC/KC input data */
#define PUF_CODEINPUT_CODEIN(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_CODEINPUT_CODEIN_SHIFT)) & PUF_CODEINPUT_CODEIN_MASK)
/*! @} */

/*! @name CODEOUTPUT - PUF Code Output Register */
/*! @{ */

#define PUF_CODEOUTPUT_CODEOUT_MASK              (0xFFFFFFFFU)
#define PUF_CODEOUTPUT_CODEOUT_SHIFT             (0U)
/*! CODEOUT - AC/KC output data */
#define PUF_CODEOUTPUT_CODEOUT(x)                (((uint32_t)(((uint32_t)(x)) << PUF_CODEOUTPUT_CODEOUT_SHIFT)) & PUF_CODEOUTPUT_CODEOUT_MASK)
/*! @} */

/*! @name KEYOUTINDEX - PUF Key Output Index Register */
/*! @{ */

#define PUF_KEYOUTINDEX_KEYOUTIDX_MASK           (0xFFFFFFFFU)
#define PUF_KEYOUTINDEX_KEYOUTIDX_SHIFT          (0U)
/*! KEYOUTIDX - Output Key index */
#define PUF_KEYOUTINDEX_KEYOUTIDX(x)             (((uint32_t)(((uint32_t)(x)) << PUF_KEYOUTINDEX_KEYOUTIDX_SHIFT)) & PUF_KEYOUTINDEX_KEYOUTIDX_MASK)
/*! @} */

/*! @name KEYOUTPUT - PUF Key Output Register */
/*! @{ */

#define PUF_KEYOUTPUT_KEYOUT_MASK                (0xFFFFFFFFU)
#define PUF_KEYOUTPUT_KEYOUT_SHIFT               (0U)
/*! KEYOUT - Key output data from a Get Key operation */
#define PUF_KEYOUTPUT_KEYOUT(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_KEYOUTPUT_KEYOUT_SHIFT)) & PUF_KEYOUTPUT_KEYOUT_MASK)
/*! @} */

/*! @name IFSTAT - PUF Interface Status Register */
/*! @{ */

#define PUF_IFSTAT_ERROR_MASK                    (0x1U)
#define PUF_IFSTAT_ERROR_SHIFT                   (0U)
/*! ERROR - APB error has occurred
 *  0b0..NOERROR
 *  0b1..ERROR
 */
#define PUF_IFSTAT_ERROR(x)                      (((uint32_t)(((uint32_t)(x)) << PUF_IFSTAT_ERROR_SHIFT)) & PUF_IFSTAT_ERROR_MASK)
/*! @} */

/*! @name VERSION - PUF Version Register */
/*! @{ */

#define PUF_VERSION_VERSION_MASK                 (0xFFFFFFFFU)
#define PUF_VERSION_VERSION_SHIFT                (0U)
/*! VERSION - Version of PUF */
#define PUF_VERSION_VERSION(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_VERSION_VERSION_SHIFT)) & PUF_VERSION_VERSION_MASK)
/*! @} */

/*! @name INTEN - PUF Interrupt Enable */
/*! @{ */

#define PUF_INTEN_READYEN_MASK                   (0x1U)
#define PUF_INTEN_READYEN_SHIFT                  (0U)
/*! READYEN - PUF Ready Interrupt Enable
 *  0b0..PUF ready interrupt disabled
 *  0b1..PUF ready interrupt enabled
 */
#define PUF_INTEN_READYEN(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_READYEN_SHIFT)) & PUF_INTEN_READYEN_MASK)

#define PUF_INTEN_SUCCESSEN_MASK                 (0x2U)
#define PUF_INTEN_SUCCESSEN_SHIFT                (1U)
/*! SUCCESSEN - PUF_OK Interrupt Enable
 *  0b0..PUF successful interrupt disabled
 *  0b1..PUF successful interrupt enabled
 */
#define PUF_INTEN_SUCCESSEN(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_SUCCESSEN_SHIFT)) & PUF_INTEN_SUCCESSEN_MASK)

#define PUF_INTEN_ERROREN_MASK                   (0x4U)
#define PUF_INTEN_ERROREN_SHIFT                  (2U)
/*! ERROREN - PUF Error Interrupt Enable
 *  0b0..PUF error interrupt disabled
 *  0b1..PUF error interrupt enabled
 */
#define PUF_INTEN_ERROREN(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_ERROREN_SHIFT)) & PUF_INTEN_ERROREN_MASK)

#define PUF_INTEN_KEYINREQEN_MASK                (0x10U)
#define PUF_INTEN_KEYINREQEN_SHIFT               (4U)
/*! KEYINREQEN - PUF Key Input Register Interrupt Enable
 *  0b0..Key interrupt request disabled
 *  0b1..Key interrupt request enabled
 */
#define PUF_INTEN_KEYINREQEN(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_KEYINREQEN_SHIFT)) & PUF_INTEN_KEYINREQEN_MASK)

#define PUF_INTEN_KEYOUTAVAILEN_MASK             (0x20U)
#define PUF_INTEN_KEYOUTAVAILEN_SHIFT            (5U)
/*! KEYOUTAVAILEN - PUF Key Output Register Interrupt Enable
 *  0b0..Key available interrupt disabled
 *  0b1..Key available interrupt enabled
 */
#define PUF_INTEN_KEYOUTAVAILEN(x)               (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_KEYOUTAVAILEN_SHIFT)) & PUF_INTEN_KEYOUTAVAILEN_MASK)

#define PUF_INTEN_CODEINREQEN_MASK               (0x40U)
#define PUF_INTEN_CODEINREQEN_SHIFT              (6U)
/*! CODEINREQEN - PUF Code Input Register Interrupt Enable
 *  0b0..AC/KC interrupt request disabled
 *  0b1..AC/KC interrupt request enabled
 */
#define PUF_INTEN_CODEINREQEN(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_CODEINREQEN_SHIFT)) & PUF_INTEN_CODEINREQEN_MASK)

#define PUF_INTEN_CODEOUTAVAILEN_MASK            (0x80U)
#define PUF_INTEN_CODEOUTAVAILEN_SHIFT           (7U)
/*! CODEOUTAVAILEN - PUF Code Output Register Interrupt Enable
 *  0b0..AC/KC available interrupt disabled
 *  0b1..AC/KC available interrupt enabled
 */
#define PUF_INTEN_CODEOUTAVAILEN(x)              (((uint32_t)(((uint32_t)(x)) << PUF_INTEN_CODEOUTAVAILEN_SHIFT)) & PUF_INTEN_CODEOUTAVAILEN_MASK)
/*! @} */

/*! @name INTSTAT - PUF Interrupt Status */
/*! @{ */

#define PUF_INTSTAT_READY_MASK                   (0x1U)
#define PUF_INTSTAT_READY_SHIFT                  (0U)
/*! READY - PUF_FINISH Interrupt Status
 *  0b0..Indicates that last operation not finished
 *  0b1..Indicates that last operation is finished
 */
#define PUF_INTSTAT_READY(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_READY_SHIFT)) & PUF_INTSTAT_READY_MASK)

#define PUF_INTSTAT_SUCCESS_MASK                 (0x2U)
#define PUF_INTSTAT_SUCCESS_SHIFT                (1U)
/*! SUCCESS - PUF_OK Interrupt Status
 *  0b0..Indicates that last operation was not successful
 *  0b1..Indicates that last operation was successful
 */
#define PUF_INTSTAT_SUCCESS(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_SUCCESS_SHIFT)) & PUF_INTSTAT_SUCCESS_MASK)

#define PUF_INTSTAT_ERROR_MASK                   (0x4U)
#define PUF_INTSTAT_ERROR_SHIFT                  (2U)
/*! ERROR - PUF_ERROR Interrupt Status
 *  0b0..PUF is not in the Error state and operations can be performed
 *  0b1..PUF is in the Error state and no operations can be performed
 */
#define PUF_INTSTAT_ERROR(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_ERROR_SHIFT)) & PUF_INTSTAT_ERROR_MASK)

#define PUF_INTSTAT_KEYINREQ_MASK                (0x10U)
#define PUF_INTSTAT_KEYINREQ_SHIFT               (4U)
/*! KEYINREQ - PUF Key Input Register Interrupt Status
 *  0b0..No request for next part of key
 *  0b1..Request for next part of key
 */
#define PUF_INTSTAT_KEYINREQ(x)                  (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_KEYINREQ_SHIFT)) & PUF_INTSTAT_KEYINREQ_MASK)

#define PUF_INTSTAT_KEYOUTAVAIL_MASK             (0x20U)
#define PUF_INTSTAT_KEYOUTAVAIL_SHIFT            (5U)
/*! KEYOUTAVAIL - PUF Key Output Register Interrupt Status
 *  0b0..Next part of key is not available
 *  0b1..Next part of key is available
 */
#define PUF_INTSTAT_KEYOUTAVAIL(x)               (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_KEYOUTAVAIL_SHIFT)) & PUF_INTSTAT_KEYOUTAVAIL_MASK)

#define PUF_INTSTAT_CODEINREQ_MASK               (0x40U)
#define PUF_INTSTAT_CODEINREQ_SHIFT              (6U)
/*! CODEINREQ - PUF Code Input Register Interrupt Status
 *  0b0..No request for next part of AC/KC
 *  0b1..Request for next part of AC/KC
 */
#define PUF_INTSTAT_CODEINREQ(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_CODEINREQ_SHIFT)) & PUF_INTSTAT_CODEINREQ_MASK)

#define PUF_INTSTAT_CODEOUTAVAIL_MASK            (0x80U)
#define PUF_INTSTAT_CODEOUTAVAIL_SHIFT           (7U)
/*! CODEOUTAVAIL - PUF Code Output Register Interrupt Status
 *  0b0..Next part of AC/KC is not available
 *  0b1..Next part of AC/KC is available
 */
#define PUF_INTSTAT_CODEOUTAVAIL(x)              (((uint32_t)(((uint32_t)(x)) << PUF_INTSTAT_CODEOUTAVAIL_SHIFT)) & PUF_INTSTAT_CODEOUTAVAIL_MASK)
/*! @} */

/*! @name PWRCTRL - PUF Power Control Of RAM */
/*! @{ */

#define PUF_PWRCTRL_RAM_ON_MASK                  (0x1U)
#define PUF_PWRCTRL_RAM_ON_SHIFT                 (0U)
/*! RAM_ON - PUF RAM on
 *  0b0..PUF RAM is in sleep mode (PUF operation disabled)
 *  0b1..PUF RAM is awake (normal PUF operation enabled)
 */
#define PUF_PWRCTRL_RAM_ON(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_PWRCTRL_RAM_ON_SHIFT)) & PUF_PWRCTRL_RAM_ON_MASK)

#define PUF_PWRCTRL_CK_DIS_MASK                  (0x4U)
#define PUF_PWRCTRL_CK_DIS_SHIFT                 (2U)
/*! CK_DIS - Clock disable
 *  0b0..PUF RAM is clocked (normal PUF operation enabled)
 *  0b1..PUF RAM clock is gated/disabled (PUF operation disabled)
 */
#define PUF_PWRCTRL_CK_DIS(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_PWRCTRL_CK_DIS_SHIFT)) & PUF_PWRCTRL_CK_DIS_MASK)

#define PUF_PWRCTRL_RAM_INITN_MASK               (0x8U)
#define PUF_PWRCTRL_RAM_INITN_SHIFT              (3U)
/*! RAM_INITN - RAM initialization
 *  0b0..Reset the PUF RAM (PUF operation disabled)
 *  0b1..Do not reset the PUF RAM (normal PUF operation enabled)
 */
#define PUF_PWRCTRL_RAM_INITN(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_PWRCTRL_RAM_INITN_SHIFT)) & PUF_PWRCTRL_RAM_INITN_MASK)

#define PUF_PWRCTRL_RAM_PSW_MASK                 (0xF0U)
#define PUF_PWRCTRL_RAM_PSW_SHIFT                (4U)
/*! RAM_PSW - PUF RAM power switches */
#define PUF_PWRCTRL_RAM_PSW(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_PWRCTRL_RAM_PSW_SHIFT)) & PUF_PWRCTRL_RAM_PSW_MASK)
/*! @} */

/*! @name CFG - PUF Configuration Register */
/*! @{ */

#define PUF_CFG_PUF_BLOCK_SET_KEY_MASK           (0x1U)
#define PUF_CFG_PUF_BLOCK_SET_KEY_SHIFT          (0U)
/*! PUF_BLOCK_SET_KEY - PUF Block Set Key Disable
 *  0b0..Enable the Set Key state
 *  0b1..Disable the Set Key state
 */
#define PUF_CFG_PUF_BLOCK_SET_KEY(x)             (((uint32_t)(((uint32_t)(x)) << PUF_CFG_PUF_BLOCK_SET_KEY_SHIFT)) & PUF_CFG_PUF_BLOCK_SET_KEY_MASK)

#define PUF_CFG_PUF_BLOCK_ENROLL_MASK            (0x2U)
#define PUF_CFG_PUF_BLOCK_ENROLL_SHIFT           (1U)
/*! PUF_BLOCK_ENROLL - PUF Block Enroll Disable
 *  0b0..Enable the Enrollment state
 *  0b1..Disable the Enrollment state
 */
#define PUF_CFG_PUF_BLOCK_ENROLL(x)              (((uint32_t)(((uint32_t)(x)) << PUF_CFG_PUF_BLOCK_ENROLL_SHIFT)) & PUF_CFG_PUF_BLOCK_ENROLL_MASK)
/*! @} */

/*! @name KEYLOCK - PUF Key Manager Lock */
/*! @{ */

#define PUF_KEYLOCK_LOCK0_MASK                   (0x3U)
#define PUF_KEYLOCK_LOCK0_SHIFT                  (0U)
/*! LOCK0 - Lock Block 0
 *  0b00..SNVS Key block locked
 *  0b01..SNVS Key block locked
 *  0b10..SNVS Key block unlocked
 *  0b11..SNVS Key block locked
 */
#define PUF_KEYLOCK_LOCK0(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_KEYLOCK_LOCK0_SHIFT)) & PUF_KEYLOCK_LOCK0_MASK)

#define PUF_KEYLOCK_LOCK1_MASK                   (0xCU)
#define PUF_KEYLOCK_LOCK1_SHIFT                  (2U)
/*! LOCK1 - Lock Block 1
 *  0b00..OTFAD Key block locked
 *  0b01..OTFAD Key block locked
 *  0b10..OTFAD Key block unlocked
 *  0b11..OTFAD Key block locked
 */
#define PUF_KEYLOCK_LOCK1(x)                     (((uint32_t)(((uint32_t)(x)) << PUF_KEYLOCK_LOCK1_SHIFT)) & PUF_KEYLOCK_LOCK1_MASK)
/*! @} */

/*! @name KEYENABLE - PUF Key Manager Enable */
/*! @{ */

#define PUF_KEYENABLE_ENABLE0_MASK               (0x3U)
#define PUF_KEYENABLE_ENABLE0_SHIFT              (0U)
/*! ENABLE0 - Enable Block 0
 *  0b00..Key block 0 disabled
 *  0b01..Key block 0 disabled
 *  0b10..Key block 0 enabled
 *  0b11..Key block 0 disabled
 */
#define PUF_KEYENABLE_ENABLE0(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_KEYENABLE_ENABLE0_SHIFT)) & PUF_KEYENABLE_ENABLE0_MASK)

#define PUF_KEYENABLE_ENABLE1_MASK               (0xCU)
#define PUF_KEYENABLE_ENABLE1_SHIFT              (2U)
/*! ENABLE1 - Enable Block 1
 *  0b00..Key block 1 disabled
 *  0b01..Key block 1 disabled
 *  0b10..Key block 1 enabled
 *  0b11..Key block 1 disabled
 */
#define PUF_KEYENABLE_ENABLE1(x)                 (((uint32_t)(((uint32_t)(x)) << PUF_KEYENABLE_ENABLE1_SHIFT)) & PUF_KEYENABLE_ENABLE1_MASK)
/*! @} */

/*! @name KEYRESET - PUF Key Manager Reset */
/*! @{ */

#define PUF_KEYRESET_RESET0_MASK                 (0x3U)
#define PUF_KEYRESET_RESET0_SHIFT                (0U)
/*! RESET0 - Reset Block 0
 *  0b00..Do not reset key block 0
 *  0b01..Do not reset key block 0
 *  0b10..Reset key block 0
 *  0b11..Do not reset key block 0
 */
#define PUF_KEYRESET_RESET0(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYRESET_RESET0_SHIFT)) & PUF_KEYRESET_RESET0_MASK)

#define PUF_KEYRESET_RESET1_MASK                 (0xCU)
#define PUF_KEYRESET_RESET1_SHIFT                (2U)
/*! RESET1 - Reset Block 1
 *  0b00..Do not reset key block 1
 *  0b01..Do not reset key block 1
 *  0b10..Reset key block 1
 *  0b11..Do not reset key block 1
 */
#define PUF_KEYRESET_RESET1(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYRESET_RESET1_SHIFT)) & PUF_KEYRESET_RESET1_MASK)
/*! @} */

/*! @name IDXBLK - PUF Index Block Key Output */
/*! @{ */

#define PUF_IDXBLK_IDXBLK0_MASK                  (0x3U)
#define PUF_IDXBLK_IDXBLK0_SHIFT                 (0U)
/*! IDXBLK0 - idxblk0 */
#define PUF_IDXBLK_IDXBLK0(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK0_SHIFT)) & PUF_IDXBLK_IDXBLK0_MASK)

#define PUF_IDXBLK_IDXBLK1_MASK                  (0xCU)
#define PUF_IDXBLK_IDXBLK1_SHIFT                 (2U)
/*! IDXBLK1 - idxblk1 */
#define PUF_IDXBLK_IDXBLK1(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK1_SHIFT)) & PUF_IDXBLK_IDXBLK1_MASK)

#define PUF_IDXBLK_IDXBLK2_MASK                  (0x30U)
#define PUF_IDXBLK_IDXBLK2_SHIFT                 (4U)
/*! IDXBLK2 - idxblk2 */
#define PUF_IDXBLK_IDXBLK2(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK2_SHIFT)) & PUF_IDXBLK_IDXBLK2_MASK)

#define PUF_IDXBLK_IDXBLK3_MASK                  (0xC0U)
#define PUF_IDXBLK_IDXBLK3_SHIFT                 (6U)
/*! IDXBLK3 - idxblk3 */
#define PUF_IDXBLK_IDXBLK3(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK3_SHIFT)) & PUF_IDXBLK_IDXBLK3_MASK)

#define PUF_IDXBLK_IDXBLK4_MASK                  (0x300U)
#define PUF_IDXBLK_IDXBLK4_SHIFT                 (8U)
/*! IDXBLK4 - idxblk4 */
#define PUF_IDXBLK_IDXBLK4(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK4_SHIFT)) & PUF_IDXBLK_IDXBLK4_MASK)

#define PUF_IDXBLK_IDXBLK5_MASK                  (0xC00U)
#define PUF_IDXBLK_IDXBLK5_SHIFT                 (10U)
/*! IDXBLK5 - idxblk5 */
#define PUF_IDXBLK_IDXBLK5(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK5_SHIFT)) & PUF_IDXBLK_IDXBLK5_MASK)

#define PUF_IDXBLK_IDXBLK6_MASK                  (0x3000U)
#define PUF_IDXBLK_IDXBLK6_SHIFT                 (12U)
/*! IDXBLK6 - idxblk6 */
#define PUF_IDXBLK_IDXBLK6(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK6_SHIFT)) & PUF_IDXBLK_IDXBLK6_MASK)

#define PUF_IDXBLK_IDXBLK7_MASK                  (0xC000U)
#define PUF_IDXBLK_IDXBLK7_SHIFT                 (14U)
/*! IDXBLK7 - idxblk7 */
#define PUF_IDXBLK_IDXBLK7(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK7_SHIFT)) & PUF_IDXBLK_IDXBLK7_MASK)

#define PUF_IDXBLK_IDXBLK8_MASK                  (0x30000U)
#define PUF_IDXBLK_IDXBLK8_SHIFT                 (16U)
/*! IDXBLK8 - idxblk8 */
#define PUF_IDXBLK_IDXBLK8(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK8_SHIFT)) & PUF_IDXBLK_IDXBLK8_MASK)

#define PUF_IDXBLK_IDXBLK9_MASK                  (0xC0000U)
#define PUF_IDXBLK_IDXBLK9_SHIFT                 (18U)
/*! IDXBLK9 - idxblk9 */
#define PUF_IDXBLK_IDXBLK9(x)                    (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK9_SHIFT)) & PUF_IDXBLK_IDXBLK9_MASK)

#define PUF_IDXBLK_IDXBLK10_MASK                 (0x300000U)
#define PUF_IDXBLK_IDXBLK10_SHIFT                (20U)
/*! IDXBLK10 - idxblk10 */
#define PUF_IDXBLK_IDXBLK10(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK10_SHIFT)) & PUF_IDXBLK_IDXBLK10_MASK)

#define PUF_IDXBLK_IDXBLK11_MASK                 (0xC00000U)
#define PUF_IDXBLK_IDXBLK11_SHIFT                (22U)
/*! IDXBLK11 - idxblk11 */
#define PUF_IDXBLK_IDXBLK11(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK11_SHIFT)) & PUF_IDXBLK_IDXBLK11_MASK)

#define PUF_IDXBLK_IDXBLK12_MASK                 (0x3000000U)
#define PUF_IDXBLK_IDXBLK12_SHIFT                (24U)
/*! IDXBLK12 - idxblk12 */
#define PUF_IDXBLK_IDXBLK12(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK12_SHIFT)) & PUF_IDXBLK_IDXBLK12_MASK)

#define PUF_IDXBLK_IDXBLK13_MASK                 (0xC000000U)
#define PUF_IDXBLK_IDXBLK13_SHIFT                (26U)
/*! IDXBLK13 - idxblk13 */
#define PUF_IDXBLK_IDXBLK13(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK13_SHIFT)) & PUF_IDXBLK_IDXBLK13_MASK)

#define PUF_IDXBLK_IDXBLK14_MASK                 (0x30000000U)
#define PUF_IDXBLK_IDXBLK14_SHIFT                (28U)
/*! IDXBLK14 - idxblk14 */
#define PUF_IDXBLK_IDXBLK14(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK14_SHIFT)) & PUF_IDXBLK_IDXBLK14_MASK)

#define PUF_IDXBLK_IDXBLK15_MASK                 (0xC0000000U)
#define PUF_IDXBLK_IDXBLK15_SHIFT                (30U)
/*! IDXBLK15 - idxblk15 */
#define PUF_IDXBLK_IDXBLK15(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_IDXBLK15_SHIFT)) & PUF_IDXBLK_IDXBLK15_MASK)
/*! @} */

/*! @name IDXBLK_DP - PUF Index Block Key Output */
/*! @{ */

#define PUF_IDXBLK_DP_IDXBLK_DP0_MASK            (0x3U)
#define PUF_IDXBLK_DP_IDXBLK_DP0_SHIFT           (0U)
/*! IDXBLK_DP0 - idxblk_dp0 */
#define PUF_IDXBLK_DP_IDXBLK_DP0(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP0_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP0_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP1_MASK            (0xCU)
#define PUF_IDXBLK_DP_IDXBLK_DP1_SHIFT           (2U)
/*! IDXBLK_DP1 - idxblk_dp1 */
#define PUF_IDXBLK_DP_IDXBLK_DP1(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP1_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP1_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP2_MASK            (0x30U)
#define PUF_IDXBLK_DP_IDXBLK_DP2_SHIFT           (4U)
/*! IDXBLK_DP2 - idxblk_dp2 */
#define PUF_IDXBLK_DP_IDXBLK_DP2(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP2_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP2_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP3_MASK            (0xC0U)
#define PUF_IDXBLK_DP_IDXBLK_DP3_SHIFT           (6U)
/*! IDXBLK_DP3 - idxblk_dp3 */
#define PUF_IDXBLK_DP_IDXBLK_DP3(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP3_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP3_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP4_MASK            (0x300U)
#define PUF_IDXBLK_DP_IDXBLK_DP4_SHIFT           (8U)
/*! IDXBLK_DP4 - idxblk_dp4 */
#define PUF_IDXBLK_DP_IDXBLK_DP4(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP4_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP4_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP5_MASK            (0xC00U)
#define PUF_IDXBLK_DP_IDXBLK_DP5_SHIFT           (10U)
/*! IDXBLK_DP5 - idxblk_dp5 */
#define PUF_IDXBLK_DP_IDXBLK_DP5(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP5_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP5_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP6_MASK            (0x3000U)
#define PUF_IDXBLK_DP_IDXBLK_DP6_SHIFT           (12U)
/*! IDXBLK_DP6 - idxblk_dp6 */
#define PUF_IDXBLK_DP_IDXBLK_DP6(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP6_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP6_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP7_MASK            (0xC000U)
#define PUF_IDXBLK_DP_IDXBLK_DP7_SHIFT           (14U)
/*! IDXBLK_DP7 - idxblk_dp7 */
#define PUF_IDXBLK_DP_IDXBLK_DP7(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP7_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP7_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP8_MASK            (0x30000U)
#define PUF_IDXBLK_DP_IDXBLK_DP8_SHIFT           (16U)
/*! IDXBLK_DP8 - idxblk_dp8 */
#define PUF_IDXBLK_DP_IDXBLK_DP8(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP8_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP8_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP9_MASK            (0xC0000U)
#define PUF_IDXBLK_DP_IDXBLK_DP9_SHIFT           (18U)
/*! IDXBLK_DP9 - idxblk_dp9 */
#define PUF_IDXBLK_DP_IDXBLK_DP9(x)              (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP9_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP9_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP10_MASK           (0x300000U)
#define PUF_IDXBLK_DP_IDXBLK_DP10_SHIFT          (20U)
/*! IDXBLK_DP10 - idxblk_dp10 */
#define PUF_IDXBLK_DP_IDXBLK_DP10(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP10_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP10_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP11_MASK           (0xC00000U)
#define PUF_IDXBLK_DP_IDXBLK_DP11_SHIFT          (22U)
/*! IDXBLK_DP11 - idxblk_dp11 */
#define PUF_IDXBLK_DP_IDXBLK_DP11(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP11_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP11_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP12_MASK           (0x3000000U)
#define PUF_IDXBLK_DP_IDXBLK_DP12_SHIFT          (24U)
/*! IDXBLK_DP12 - idxblk_dp12 */
#define PUF_IDXBLK_DP_IDXBLK_DP12(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP12_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP12_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP13_MASK           (0xC000000U)
#define PUF_IDXBLK_DP_IDXBLK_DP13_SHIFT          (26U)
/*! IDXBLK_DP13 - idxblk_dp13 */
#define PUF_IDXBLK_DP_IDXBLK_DP13(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP13_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP13_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP14_MASK           (0x30000000U)
#define PUF_IDXBLK_DP_IDXBLK_DP14_SHIFT          (28U)
/*! IDXBLK_DP14 - idxblk_dp14 */
#define PUF_IDXBLK_DP_IDXBLK_DP14(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP14_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP14_MASK)

#define PUF_IDXBLK_DP_IDXBLK_DP15_MASK           (0xC0000000U)
#define PUF_IDXBLK_DP_IDXBLK_DP15_SHIFT          (30U)
/*! IDXBLK_DP15 - idxblk_dp15 */
#define PUF_IDXBLK_DP_IDXBLK_DP15(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_DP_IDXBLK_DP15_SHIFT)) & PUF_IDXBLK_DP_IDXBLK_DP15_MASK)
/*! @} */

/*! @name KEYMASK - PUF Key Block 0 Mask Enable..PUF Key Block 1 Mask Enable */
/*! @{ */

#define PUF_KEYMASK_KEYMASK_MASK                 (0xFFFFFFFFU)
#define PUF_KEYMASK_KEYMASK_SHIFT                (0U)
/*! KEYMASK - KEYMASK1 */
#define PUF_KEYMASK_KEYMASK(x)                   (((uint32_t)(((uint32_t)(x)) << PUF_KEYMASK_KEYMASK_SHIFT)) & PUF_KEYMASK_KEYMASK_MASK)
/*! @} */

/*! @name IDXBLK_STATUS - PUF Index Block Setting Status Register */
/*! @{ */

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS0_MASK    (0x3U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS0_SHIFT   (0U)
/*! IDXBLK_STATUS0 - idxblk_status0 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS0(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS0_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS0_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS1_MASK    (0xCU)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS1_SHIFT   (2U)
/*! IDXBLK_STATUS1 - idxblk_status1 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS1(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS1_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS1_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS2_MASK    (0x30U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS2_SHIFT   (4U)
/*! IDXBLK_STATUS2 - idxblk_status2 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS2(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS2_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS2_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS3_MASK    (0xC0U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS3_SHIFT   (6U)
/*! IDXBLK_STATUS3 - idxblk_status3 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS3(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS3_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS3_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS4_MASK    (0x300U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS4_SHIFT   (8U)
/*! IDXBLK_STATUS4 - idxblk_status4 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS4(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS4_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS4_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS5_MASK    (0xC00U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS5_SHIFT   (10U)
/*! IDXBLK_STATUS5 - idxblk_status5 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS5(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS5_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS5_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS6_MASK    (0x3000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS6_SHIFT   (12U)
/*! IDXBLK_STATUS6 - idxblk_status6 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS6(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS6_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS6_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS7_MASK    (0xC000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS7_SHIFT   (14U)
/*! IDXBLK_STATUS7 - idxblk_status7 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS7(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS7_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS7_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS8_MASK    (0x30000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS8_SHIFT   (16U)
/*! IDXBLK_STATUS8 - idxblk_status8 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS8(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS8_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS8_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS9_MASK    (0xC0000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS9_SHIFT   (18U)
/*! IDXBLK_STATUS9 - idxblk_status9 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS9(x)      (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS9_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS9_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS10_MASK   (0x300000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS10_SHIFT  (20U)
/*! IDXBLK_STATUS10 - idxblk_status10 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS10(x)     (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS10_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS10_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS11_MASK   (0xC00000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS11_SHIFT  (22U)
/*! IDXBLK_STATUS11 - idxblk_status11 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS11(x)     (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS11_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS11_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS12_MASK   (0x3000000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS12_SHIFT  (24U)
/*! IDXBLK_STATUS12 - idxblk_status12 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS12(x)     (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS12_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS12_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS13_MASK   (0xC000000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS13_SHIFT  (26U)
/*! IDXBLK_STATUS13 - idxblk_status13 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS13(x)     (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS13_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS13_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS14_MASK   (0x30000000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS14_SHIFT  (28U)
/*! IDXBLK_STATUS14 - idxblk_status14 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS14(x)     (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS14_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS14_MASK)

#define PUF_IDXBLK_STATUS_IDXBLK_STATUS15_MASK   (0xC0000000U)
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS15_SHIFT  (30U)
/*! IDXBLK_STATUS15 - idxblk_status15 */
#define PUF_IDXBLK_STATUS_IDXBLK_STATUS15(x)     (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_STATUS_IDXBLK_STATUS15_SHIFT)) & PUF_IDXBLK_STATUS_IDXBLK_STATUS15_MASK)
/*! @} */

/*! @name IDXBLK_SHIFT - PUF Key Manager Shift Status */
/*! @{ */

#define PUF_IDXBLK_SHIFT_IND_KEY0_MASK           (0xFU)
#define PUF_IDXBLK_SHIFT_IND_KEY0_SHIFT          (0U)
/*! IND_KEY0 - Index of key space in block 0 */
#define PUF_IDXBLK_SHIFT_IND_KEY0(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_SHIFT_IND_KEY0_SHIFT)) & PUF_IDXBLK_SHIFT_IND_KEY0_MASK)

#define PUF_IDXBLK_SHIFT_IND_KEY1_MASK           (0xF0U)
#define PUF_IDXBLK_SHIFT_IND_KEY1_SHIFT          (4U)
/*! IND_KEY1 - Index of key space in block 1 */
#define PUF_IDXBLK_SHIFT_IND_KEY1(x)             (((uint32_t)(((uint32_t)(x)) << PUF_IDXBLK_SHIFT_IND_KEY1_SHIFT)) & PUF_IDXBLK_SHIFT_IND_KEY1_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PUF_Register_Masks */


/*!
 * @}
 */ /* end of group PUF_Peripheral_Access_Layer */


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


#endif  /* PERI_PUF_H_ */

