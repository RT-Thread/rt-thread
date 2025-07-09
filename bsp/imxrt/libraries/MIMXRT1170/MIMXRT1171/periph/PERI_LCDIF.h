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
**         CMSIS Peripheral Access Layer for LCDIF
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
 * @file PERI_LCDIF.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for LCDIF
 *
 * CMSIS Peripheral Access Layer for LCDIF
 */

#if !defined(PERI_LCDIF_H_)
#define PERI_LCDIF_H_                            /**< Symbol preventing repeated inclusion */

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
   -- LCDIF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCDIF_Peripheral_Access_Layer LCDIF Peripheral Access Layer
 * @{
 */

/** LCDIF - Size of Registers Arrays */
#define LCDIF_PIGEON_COUNT                        12u

/** LCDIF - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< LCDIF General Control Register, offset: 0x0 */
  __IO uint32_t CTRL_SET;                          /**< LCDIF General Control Register, offset: 0x4 */
  __IO uint32_t CTRL_CLR;                          /**< LCDIF General Control Register, offset: 0x8 */
  __IO uint32_t CTRL_TOG;                          /**< LCDIF General Control Register, offset: 0xC */
  __IO uint32_t CTRL1;                             /**< LCDIF General Control1 Register, offset: 0x10 */
  __IO uint32_t CTRL1_SET;                         /**< LCDIF General Control1 Register, offset: 0x14 */
  __IO uint32_t CTRL1_CLR;                         /**< LCDIF General Control1 Register, offset: 0x18 */
  __IO uint32_t CTRL1_TOG;                         /**< LCDIF General Control1 Register, offset: 0x1C */
  __IO uint32_t CTRL2;                             /**< LCDIF General Control2 Register, offset: 0x20 */
  __IO uint32_t CTRL2_SET;                         /**< LCDIF General Control2 Register, offset: 0x24 */
  __IO uint32_t CTRL2_CLR;                         /**< LCDIF General Control2 Register, offset: 0x28 */
  __IO uint32_t CTRL2_TOG;                         /**< LCDIF General Control2 Register, offset: 0x2C */
  __IO uint32_t TRANSFER_COUNT;                    /**< LCDIF Horizontal and Vertical Valid Data Count Register, offset: 0x30 */
       uint8_t RESERVED_0[12];
  __IO uint32_t CUR_BUF;                           /**< LCD Interface Current Buffer Address Register, offset: 0x40 */
       uint8_t RESERVED_1[12];
  __IO uint32_t NEXT_BUF;                          /**< LCD Interface Next Buffer Address Register, offset: 0x50 */
       uint8_t RESERVED_2[28];
  __IO uint32_t VDCTRL0;                           /**< LCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x70 */
  __IO uint32_t VDCTRL0_SET;                       /**< LCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x74 */
  __IO uint32_t VDCTRL0_CLR;                       /**< LCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x78 */
  __IO uint32_t VDCTRL0_TOG;                       /**< LCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x7C */
  __IO uint32_t VDCTRL1;                           /**< LCDIF VSYNC Mode and Dotclk Mode Control Register1, offset: 0x80 */
       uint8_t RESERVED_3[12];
  __IO uint32_t VDCTRL2;                           /**< LCDIF VSYNC Mode and Dotclk Mode Control Register2, offset: 0x90 */
       uint8_t RESERVED_4[12];
  __IO uint32_t VDCTRL3;                           /**< LCDIF VSYNC Mode and Dotclk Mode Control Register3, offset: 0xA0 */
       uint8_t RESERVED_5[12];
  __IO uint32_t VDCTRL4;                           /**< LCDIF VSYNC Mode and Dotclk Mode Control Register4, offset: 0xB0 */
       uint8_t RESERVED_6[220];
  __IO uint32_t BM_ERROR_STAT;                     /**< Bus Master Error Status Register, offset: 0x190 */
       uint8_t RESERVED_7[12];
  __IO uint32_t CRC_STAT;                          /**< CRC Status Register, offset: 0x1A0 */
       uint8_t RESERVED_8[12];
  __I  uint32_t STAT;                              /**< LCD Interface Status Register, offset: 0x1B0 */
       uint8_t RESERVED_9[76];
  __IO uint32_t THRES;                             /**< LCDIF Threshold Register, offset: 0x200 */
       uint8_t RESERVED_10[380];
  __IO uint32_t PIGEONCTRL0;                       /**< LCDIF Pigeon Mode Control0 Register, offset: 0x380 */
  __IO uint32_t PIGEONCTRL0_SET;                   /**< LCDIF Pigeon Mode Control0 Register, offset: 0x384 */
  __IO uint32_t PIGEONCTRL0_CLR;                   /**< LCDIF Pigeon Mode Control0 Register, offset: 0x388 */
  __IO uint32_t PIGEONCTRL0_TOG;                   /**< LCDIF Pigeon Mode Control0 Register, offset: 0x38C */
  __IO uint32_t PIGEONCTRL1;                       /**< LCDIF Pigeon Mode Control1 Register, offset: 0x390 */
  __IO uint32_t PIGEONCTRL1_SET;                   /**< LCDIF Pigeon Mode Control1 Register, offset: 0x394 */
  __IO uint32_t PIGEONCTRL1_CLR;                   /**< LCDIF Pigeon Mode Control1 Register, offset: 0x398 */
  __IO uint32_t PIGEONCTRL1_TOG;                   /**< LCDIF Pigeon Mode Control1 Register, offset: 0x39C */
  __IO uint32_t PIGEONCTRL2;                       /**< LCDIF Pigeon Mode Control2 Register, offset: 0x3A0 */
  __IO uint32_t PIGEONCTRL2_SET;                   /**< LCDIF Pigeon Mode Control2 Register, offset: 0x3A4 */
  __IO uint32_t PIGEONCTRL2_CLR;                   /**< LCDIF Pigeon Mode Control2 Register, offset: 0x3A8 */
  __IO uint32_t PIGEONCTRL2_TOG;                   /**< LCDIF Pigeon Mode Control2 Register, offset: 0x3AC */
       uint8_t RESERVED_11[1104];
  struct {                                         /* offset: 0x800, array step: 0x40 */
    __IO uint32_t PIGEON_0;                          /**< Panel Interface Signal Generator Register, array offset: 0x800, array step: 0x40 */
         uint8_t RESERVED_0[12];
    __IO uint32_t PIGEON_1;                          /**< Panel Interface Signal Generator Register, array offset: 0x810, array step: 0x40 */
         uint8_t RESERVED_1[12];
    __IO uint32_t PIGEON_2;                          /**< Panel Interface Signal Generator Register, array offset: 0x820, array step: 0x40 */
         uint8_t RESERVED_2[28];
  } PIGEON[LCDIF_PIGEON_COUNT];
  __IO uint32_t LUT_CTRL;                          /**< Look Up Table Control Register, offset: 0xB00 */
       uint8_t RESERVED_12[12];
  __IO uint32_t LUT0_ADDR;                         /**< Lookup Table 0 Index Register, offset: 0xB10 */
       uint8_t RESERVED_13[12];
  __IO uint32_t LUT0_DATA;                         /**< Lookup Table 0 Data Register, offset: 0xB20 */
       uint8_t RESERVED_14[12];
  __IO uint32_t LUT1_ADDR;                         /**< Lookup Table 1 Index Register, offset: 0xB30 */
       uint8_t RESERVED_15[12];
  __IO uint32_t LUT1_DATA;                         /**< Lookup Table 1 Data Register, offset: 0xB40 */
} LCDIF_Type;

/* ----------------------------------------------------------------------------
   -- LCDIF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LCDIF_Register_Masks LCDIF Register Masks
 * @{
 */

/*! @name CTRL - LCDIF General Control Register */
/*! @{ */

#define LCDIF_CTRL_RUN_MASK                      (0x1U)
#define LCDIF_CTRL_RUN_SHIFT                     (0U)
#define LCDIF_CTRL_RUN(x)                        (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_RUN_SHIFT)) & LCDIF_CTRL_RUN_MASK)

#define LCDIF_CTRL_DATA_FORMAT_24_BIT_MASK       (0x2U)
#define LCDIF_CTRL_DATA_FORMAT_24_BIT_SHIFT      (1U)
/*! DATA_FORMAT_24_BIT
 *  0b0..Data input to the block is in 24 bpp format, such that all RGB 888 data is contained in 24 bits.
 *  0b1..Data input to the block is actually RGB 18 bpp, but there is 1 color per byte, hence the upper 2 bits in
 *       each byte do not contain any useful data, and should be dropped.
 */
#define LCDIF_CTRL_DATA_FORMAT_24_BIT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_DATA_FORMAT_24_BIT_SHIFT)) & LCDIF_CTRL_DATA_FORMAT_24_BIT_MASK)

#define LCDIF_CTRL_DATA_FORMAT_18_BIT_MASK       (0x4U)
#define LCDIF_CTRL_DATA_FORMAT_18_BIT_SHIFT      (2U)
/*! DATA_FORMAT_18_BIT
 *  0b0..Data input to the block is in 18 bpp format, such that lower 18 bits contain RGB 666 and upper 14 bits do not contain any useful data.
 *  0b1..Data input to the block is in 18 bpp format, such that upper 18 bits contain RGB 666 and lower 14 bits do not contain any useful data.
 */
#define LCDIF_CTRL_DATA_FORMAT_18_BIT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_DATA_FORMAT_18_BIT_SHIFT)) & LCDIF_CTRL_DATA_FORMAT_18_BIT_MASK)

#define LCDIF_CTRL_DATA_FORMAT_16_BIT_MASK       (0x8U)
#define LCDIF_CTRL_DATA_FORMAT_16_BIT_SHIFT      (3U)
#define LCDIF_CTRL_DATA_FORMAT_16_BIT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_DATA_FORMAT_16_BIT_SHIFT)) & LCDIF_CTRL_DATA_FORMAT_16_BIT_MASK)

#define LCDIF_CTRL_RSRVD0_MASK                   (0x10U)
#define LCDIF_CTRL_RSRVD0_SHIFT                  (4U)
#define LCDIF_CTRL_RSRVD0(x)                     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_RSRVD0_SHIFT)) & LCDIF_CTRL_RSRVD0_MASK)

#define LCDIF_CTRL_MASTER_MASK                   (0x20U)
#define LCDIF_CTRL_MASTER_SHIFT                  (5U)
#define LCDIF_CTRL_MASTER(x)                     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_MASTER_SHIFT)) & LCDIF_CTRL_MASTER_MASK)

#define LCDIF_CTRL_ENABLE_PXP_HANDSHAKE_MASK     (0x40U)
#define LCDIF_CTRL_ENABLE_PXP_HANDSHAKE_SHIFT    (6U)
#define LCDIF_CTRL_ENABLE_PXP_HANDSHAKE(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_ENABLE_PXP_HANDSHAKE_SHIFT)) & LCDIF_CTRL_ENABLE_PXP_HANDSHAKE_MASK)

#define LCDIF_CTRL_WORD_LENGTH_MASK              (0x300U)
#define LCDIF_CTRL_WORD_LENGTH_SHIFT             (8U)
/*! WORD_LENGTH
 *  0b00..Input data is 16 bits per pixel.
 *  0b01..Input data is 8 bits wide.
 *  0b10..Input data is 18 bits per pixel.
 *  0b11..Input data is 24 bits per pixel.
 */
#define LCDIF_CTRL_WORD_LENGTH(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_WORD_LENGTH_SHIFT)) & LCDIF_CTRL_WORD_LENGTH_MASK)

#define LCDIF_CTRL_LCD_DATABUS_WIDTH_MASK        (0xC00U)
#define LCDIF_CTRL_LCD_DATABUS_WIDTH_SHIFT       (10U)
/*! LCD_DATABUS_WIDTH
 *  0b00..16-bit data bus mode.
 *  0b01..8-bit data bus mode.
 *  0b10..18-bit data bus mode.
 *  0b11..24-bit data bus mode.
 */
#define LCDIF_CTRL_LCD_DATABUS_WIDTH(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_LCD_DATABUS_WIDTH_SHIFT)) & LCDIF_CTRL_LCD_DATABUS_WIDTH_MASK)

#define LCDIF_CTRL_CSC_DATA_SWIZZLE_MASK         (0x3000U)
#define LCDIF_CTRL_CSC_DATA_SWIZZLE_SHIFT        (12U)
/*! CSC_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_CSC_DATA_SWIZZLE(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CSC_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_CSC_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_INPUT_DATA_SWIZZLE_MASK       (0xC000U)
#define LCDIF_CTRL_INPUT_DATA_SWIZZLE_SHIFT      (14U)
/*! INPUT_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_INPUT_DATA_SWIZZLE(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_INPUT_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_INPUT_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_DOTCLK_MODE_MASK              (0x20000U)
#define LCDIF_CTRL_DOTCLK_MODE_SHIFT             (17U)
#define LCDIF_CTRL_DOTCLK_MODE(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_DOTCLK_MODE_SHIFT)) & LCDIF_CTRL_DOTCLK_MODE_MASK)

#define LCDIF_CTRL_BYPASS_COUNT_MASK             (0x80000U)
#define LCDIF_CTRL_BYPASS_COUNT_SHIFT            (19U)
#define LCDIF_CTRL_BYPASS_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_BYPASS_COUNT_SHIFT)) & LCDIF_CTRL_BYPASS_COUNT_MASK)

#define LCDIF_CTRL_SHIFT_NUM_BITS_MASK           (0x3E00000U)
#define LCDIF_CTRL_SHIFT_NUM_BITS_SHIFT          (21U)
#define LCDIF_CTRL_SHIFT_NUM_BITS(x)             (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SHIFT_NUM_BITS_SHIFT)) & LCDIF_CTRL_SHIFT_NUM_BITS_MASK)

#define LCDIF_CTRL_DATA_SHIFT_DIR_MASK           (0x4000000U)
#define LCDIF_CTRL_DATA_SHIFT_DIR_SHIFT          (26U)
/*! DATA_SHIFT_DIR
 *  0b0..Data to be transmitted is shifted LEFT by SHIFT_NUM_BITS bits.
 *  0b1..Data to be transmitted is shifted RIGHT by SHIFT_NUM_BITS bits.
 */
#define LCDIF_CTRL_DATA_SHIFT_DIR(x)             (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_DATA_SHIFT_DIR_SHIFT)) & LCDIF_CTRL_DATA_SHIFT_DIR_MASK)

#define LCDIF_CTRL_CLKGATE_MASK                  (0x40000000U)
#define LCDIF_CTRL_CLKGATE_SHIFT                 (30U)
#define LCDIF_CTRL_CLKGATE(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLKGATE_SHIFT)) & LCDIF_CTRL_CLKGATE_MASK)

#define LCDIF_CTRL_SFTRST_MASK                   (0x80000000U)
#define LCDIF_CTRL_SFTRST_SHIFT                  (31U)
#define LCDIF_CTRL_SFTRST(x)                     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SFTRST_SHIFT)) & LCDIF_CTRL_SFTRST_MASK)
/*! @} */

/*! @name CTRL_SET - LCDIF General Control Register */
/*! @{ */

#define LCDIF_CTRL_SET_RUN_MASK                  (0x1U)
#define LCDIF_CTRL_SET_RUN_SHIFT                 (0U)
#define LCDIF_CTRL_SET_RUN(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_RUN_SHIFT)) & LCDIF_CTRL_SET_RUN_MASK)

#define LCDIF_CTRL_SET_DATA_FORMAT_24_BIT_MASK   (0x2U)
#define LCDIF_CTRL_SET_DATA_FORMAT_24_BIT_SHIFT  (1U)
/*! DATA_FORMAT_24_BIT
 *  0b0..Data input to the block is in 24 bpp format, such that all RGB 888 data is contained in 24 bits.
 *  0b1..Data input to the block is actually RGB 18 bpp, but there is 1 color per byte, hence the upper 2 bits in
 *       each byte do not contain any useful data, and should be dropped.
 */
#define LCDIF_CTRL_SET_DATA_FORMAT_24_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_DATA_FORMAT_24_BIT_SHIFT)) & LCDIF_CTRL_SET_DATA_FORMAT_24_BIT_MASK)

#define LCDIF_CTRL_SET_DATA_FORMAT_18_BIT_MASK   (0x4U)
#define LCDIF_CTRL_SET_DATA_FORMAT_18_BIT_SHIFT  (2U)
/*! DATA_FORMAT_18_BIT
 *  0b0..Data input to the block is in 18 bpp format, such that lower 18 bits contain RGB 666 and upper 14 bits do not contain any useful data.
 *  0b1..Data input to the block is in 18 bpp format, such that upper 18 bits contain RGB 666 and lower 14 bits do not contain any useful data.
 */
#define LCDIF_CTRL_SET_DATA_FORMAT_18_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_DATA_FORMAT_18_BIT_SHIFT)) & LCDIF_CTRL_SET_DATA_FORMAT_18_BIT_MASK)

#define LCDIF_CTRL_SET_DATA_FORMAT_16_BIT_MASK   (0x8U)
#define LCDIF_CTRL_SET_DATA_FORMAT_16_BIT_SHIFT  (3U)
#define LCDIF_CTRL_SET_DATA_FORMAT_16_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_DATA_FORMAT_16_BIT_SHIFT)) & LCDIF_CTRL_SET_DATA_FORMAT_16_BIT_MASK)

#define LCDIF_CTRL_SET_RSRVD0_MASK               (0x10U)
#define LCDIF_CTRL_SET_RSRVD0_SHIFT              (4U)
#define LCDIF_CTRL_SET_RSRVD0(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_RSRVD0_SHIFT)) & LCDIF_CTRL_SET_RSRVD0_MASK)

#define LCDIF_CTRL_SET_MASTER_MASK               (0x20U)
#define LCDIF_CTRL_SET_MASTER_SHIFT              (5U)
#define LCDIF_CTRL_SET_MASTER(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_MASTER_SHIFT)) & LCDIF_CTRL_SET_MASTER_MASK)

#define LCDIF_CTRL_SET_ENABLE_PXP_HANDSHAKE_MASK (0x40U)
#define LCDIF_CTRL_SET_ENABLE_PXP_HANDSHAKE_SHIFT (6U)
#define LCDIF_CTRL_SET_ENABLE_PXP_HANDSHAKE(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_ENABLE_PXP_HANDSHAKE_SHIFT)) & LCDIF_CTRL_SET_ENABLE_PXP_HANDSHAKE_MASK)

#define LCDIF_CTRL_SET_WORD_LENGTH_MASK          (0x300U)
#define LCDIF_CTRL_SET_WORD_LENGTH_SHIFT         (8U)
/*! WORD_LENGTH
 *  0b00..Input data is 16 bits per pixel.
 *  0b01..Input data is 8 bits wide.
 *  0b10..Input data is 18 bits per pixel.
 *  0b11..Input data is 24 bits per pixel.
 */
#define LCDIF_CTRL_SET_WORD_LENGTH(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_WORD_LENGTH_SHIFT)) & LCDIF_CTRL_SET_WORD_LENGTH_MASK)

#define LCDIF_CTRL_SET_LCD_DATABUS_WIDTH_MASK    (0xC00U)
#define LCDIF_CTRL_SET_LCD_DATABUS_WIDTH_SHIFT   (10U)
/*! LCD_DATABUS_WIDTH
 *  0b00..16-bit data bus mode.
 *  0b01..8-bit data bus mode.
 *  0b10..18-bit data bus mode.
 *  0b11..24-bit data bus mode.
 */
#define LCDIF_CTRL_SET_LCD_DATABUS_WIDTH(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_LCD_DATABUS_WIDTH_SHIFT)) & LCDIF_CTRL_SET_LCD_DATABUS_WIDTH_MASK)

#define LCDIF_CTRL_SET_CSC_DATA_SWIZZLE_MASK     (0x3000U)
#define LCDIF_CTRL_SET_CSC_DATA_SWIZZLE_SHIFT    (12U)
/*! CSC_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_SET_CSC_DATA_SWIZZLE(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_CSC_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_SET_CSC_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_SET_INPUT_DATA_SWIZZLE_MASK   (0xC000U)
#define LCDIF_CTRL_SET_INPUT_DATA_SWIZZLE_SHIFT  (14U)
/*! INPUT_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_SET_INPUT_DATA_SWIZZLE(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_INPUT_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_SET_INPUT_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_SET_DOTCLK_MODE_MASK          (0x20000U)
#define LCDIF_CTRL_SET_DOTCLK_MODE_SHIFT         (17U)
#define LCDIF_CTRL_SET_DOTCLK_MODE(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_DOTCLK_MODE_SHIFT)) & LCDIF_CTRL_SET_DOTCLK_MODE_MASK)

#define LCDIF_CTRL_SET_BYPASS_COUNT_MASK         (0x80000U)
#define LCDIF_CTRL_SET_BYPASS_COUNT_SHIFT        (19U)
#define LCDIF_CTRL_SET_BYPASS_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_BYPASS_COUNT_SHIFT)) & LCDIF_CTRL_SET_BYPASS_COUNT_MASK)

#define LCDIF_CTRL_SET_SHIFT_NUM_BITS_MASK       (0x3E00000U)
#define LCDIF_CTRL_SET_SHIFT_NUM_BITS_SHIFT      (21U)
#define LCDIF_CTRL_SET_SHIFT_NUM_BITS(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_SHIFT_NUM_BITS_SHIFT)) & LCDIF_CTRL_SET_SHIFT_NUM_BITS_MASK)

#define LCDIF_CTRL_SET_DATA_SHIFT_DIR_MASK       (0x4000000U)
#define LCDIF_CTRL_SET_DATA_SHIFT_DIR_SHIFT      (26U)
/*! DATA_SHIFT_DIR
 *  0b0..Data to be transmitted is shifted LEFT by SHIFT_NUM_BITS bits.
 *  0b1..Data to be transmitted is shifted RIGHT by SHIFT_NUM_BITS bits.
 */
#define LCDIF_CTRL_SET_DATA_SHIFT_DIR(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_DATA_SHIFT_DIR_SHIFT)) & LCDIF_CTRL_SET_DATA_SHIFT_DIR_MASK)

#define LCDIF_CTRL_SET_CLKGATE_MASK              (0x40000000U)
#define LCDIF_CTRL_SET_CLKGATE_SHIFT             (30U)
#define LCDIF_CTRL_SET_CLKGATE(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_CLKGATE_SHIFT)) & LCDIF_CTRL_SET_CLKGATE_MASK)

#define LCDIF_CTRL_SET_SFTRST_MASK               (0x80000000U)
#define LCDIF_CTRL_SET_SFTRST_SHIFT              (31U)
#define LCDIF_CTRL_SET_SFTRST(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_SET_SFTRST_SHIFT)) & LCDIF_CTRL_SET_SFTRST_MASK)
/*! @} */

/*! @name CTRL_CLR - LCDIF General Control Register */
/*! @{ */

#define LCDIF_CTRL_CLR_RUN_MASK                  (0x1U)
#define LCDIF_CTRL_CLR_RUN_SHIFT                 (0U)
#define LCDIF_CTRL_CLR_RUN(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_RUN_SHIFT)) & LCDIF_CTRL_CLR_RUN_MASK)

#define LCDIF_CTRL_CLR_DATA_FORMAT_24_BIT_MASK   (0x2U)
#define LCDIF_CTRL_CLR_DATA_FORMAT_24_BIT_SHIFT  (1U)
/*! DATA_FORMAT_24_BIT
 *  0b0..Data input to the block is in 24 bpp format, such that all RGB 888 data is contained in 24 bits.
 *  0b1..Data input to the block is actually RGB 18 bpp, but there is 1 color per byte, hence the upper 2 bits in
 *       each byte do not contain any useful data, and should be dropped.
 */
#define LCDIF_CTRL_CLR_DATA_FORMAT_24_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_DATA_FORMAT_24_BIT_SHIFT)) & LCDIF_CTRL_CLR_DATA_FORMAT_24_BIT_MASK)

#define LCDIF_CTRL_CLR_DATA_FORMAT_18_BIT_MASK   (0x4U)
#define LCDIF_CTRL_CLR_DATA_FORMAT_18_BIT_SHIFT  (2U)
/*! DATA_FORMAT_18_BIT
 *  0b0..Data input to the block is in 18 bpp format, such that lower 18 bits contain RGB 666 and upper 14 bits do not contain any useful data.
 *  0b1..Data input to the block is in 18 bpp format, such that upper 18 bits contain RGB 666 and lower 14 bits do not contain any useful data.
 */
#define LCDIF_CTRL_CLR_DATA_FORMAT_18_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_DATA_FORMAT_18_BIT_SHIFT)) & LCDIF_CTRL_CLR_DATA_FORMAT_18_BIT_MASK)

#define LCDIF_CTRL_CLR_DATA_FORMAT_16_BIT_MASK   (0x8U)
#define LCDIF_CTRL_CLR_DATA_FORMAT_16_BIT_SHIFT  (3U)
#define LCDIF_CTRL_CLR_DATA_FORMAT_16_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_DATA_FORMAT_16_BIT_SHIFT)) & LCDIF_CTRL_CLR_DATA_FORMAT_16_BIT_MASK)

#define LCDIF_CTRL_CLR_RSRVD0_MASK               (0x10U)
#define LCDIF_CTRL_CLR_RSRVD0_SHIFT              (4U)
#define LCDIF_CTRL_CLR_RSRVD0(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_RSRVD0_SHIFT)) & LCDIF_CTRL_CLR_RSRVD0_MASK)

#define LCDIF_CTRL_CLR_MASTER_MASK               (0x20U)
#define LCDIF_CTRL_CLR_MASTER_SHIFT              (5U)
#define LCDIF_CTRL_CLR_MASTER(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_MASTER_SHIFT)) & LCDIF_CTRL_CLR_MASTER_MASK)

#define LCDIF_CTRL_CLR_ENABLE_PXP_HANDSHAKE_MASK (0x40U)
#define LCDIF_CTRL_CLR_ENABLE_PXP_HANDSHAKE_SHIFT (6U)
#define LCDIF_CTRL_CLR_ENABLE_PXP_HANDSHAKE(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_ENABLE_PXP_HANDSHAKE_SHIFT)) & LCDIF_CTRL_CLR_ENABLE_PXP_HANDSHAKE_MASK)

#define LCDIF_CTRL_CLR_WORD_LENGTH_MASK          (0x300U)
#define LCDIF_CTRL_CLR_WORD_LENGTH_SHIFT         (8U)
/*! WORD_LENGTH
 *  0b00..Input data is 16 bits per pixel.
 *  0b01..Input data is 8 bits wide.
 *  0b10..Input data is 18 bits per pixel.
 *  0b11..Input data is 24 bits per pixel.
 */
#define LCDIF_CTRL_CLR_WORD_LENGTH(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_WORD_LENGTH_SHIFT)) & LCDIF_CTRL_CLR_WORD_LENGTH_MASK)

#define LCDIF_CTRL_CLR_LCD_DATABUS_WIDTH_MASK    (0xC00U)
#define LCDIF_CTRL_CLR_LCD_DATABUS_WIDTH_SHIFT   (10U)
/*! LCD_DATABUS_WIDTH
 *  0b00..16-bit data bus mode.
 *  0b01..8-bit data bus mode.
 *  0b10..18-bit data bus mode.
 *  0b11..24-bit data bus mode.
 */
#define LCDIF_CTRL_CLR_LCD_DATABUS_WIDTH(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_LCD_DATABUS_WIDTH_SHIFT)) & LCDIF_CTRL_CLR_LCD_DATABUS_WIDTH_MASK)

#define LCDIF_CTRL_CLR_CSC_DATA_SWIZZLE_MASK     (0x3000U)
#define LCDIF_CTRL_CLR_CSC_DATA_SWIZZLE_SHIFT    (12U)
/*! CSC_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_CLR_CSC_DATA_SWIZZLE(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_CSC_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_CLR_CSC_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_CLR_INPUT_DATA_SWIZZLE_MASK   (0xC000U)
#define LCDIF_CTRL_CLR_INPUT_DATA_SWIZZLE_SHIFT  (14U)
/*! INPUT_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_CLR_INPUT_DATA_SWIZZLE(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_INPUT_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_CLR_INPUT_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_CLR_DOTCLK_MODE_MASK          (0x20000U)
#define LCDIF_CTRL_CLR_DOTCLK_MODE_SHIFT         (17U)
#define LCDIF_CTRL_CLR_DOTCLK_MODE(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_DOTCLK_MODE_SHIFT)) & LCDIF_CTRL_CLR_DOTCLK_MODE_MASK)

#define LCDIF_CTRL_CLR_BYPASS_COUNT_MASK         (0x80000U)
#define LCDIF_CTRL_CLR_BYPASS_COUNT_SHIFT        (19U)
#define LCDIF_CTRL_CLR_BYPASS_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_BYPASS_COUNT_SHIFT)) & LCDIF_CTRL_CLR_BYPASS_COUNT_MASK)

#define LCDIF_CTRL_CLR_SHIFT_NUM_BITS_MASK       (0x3E00000U)
#define LCDIF_CTRL_CLR_SHIFT_NUM_BITS_SHIFT      (21U)
#define LCDIF_CTRL_CLR_SHIFT_NUM_BITS(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_SHIFT_NUM_BITS_SHIFT)) & LCDIF_CTRL_CLR_SHIFT_NUM_BITS_MASK)

#define LCDIF_CTRL_CLR_DATA_SHIFT_DIR_MASK       (0x4000000U)
#define LCDIF_CTRL_CLR_DATA_SHIFT_DIR_SHIFT      (26U)
/*! DATA_SHIFT_DIR
 *  0b0..Data to be transmitted is shifted LEFT by SHIFT_NUM_BITS bits.
 *  0b1..Data to be transmitted is shifted RIGHT by SHIFT_NUM_BITS bits.
 */
#define LCDIF_CTRL_CLR_DATA_SHIFT_DIR(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_DATA_SHIFT_DIR_SHIFT)) & LCDIF_CTRL_CLR_DATA_SHIFT_DIR_MASK)

#define LCDIF_CTRL_CLR_CLKGATE_MASK              (0x40000000U)
#define LCDIF_CTRL_CLR_CLKGATE_SHIFT             (30U)
#define LCDIF_CTRL_CLR_CLKGATE(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_CLKGATE_SHIFT)) & LCDIF_CTRL_CLR_CLKGATE_MASK)

#define LCDIF_CTRL_CLR_SFTRST_MASK               (0x80000000U)
#define LCDIF_CTRL_CLR_SFTRST_SHIFT              (31U)
#define LCDIF_CTRL_CLR_SFTRST(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_CLR_SFTRST_SHIFT)) & LCDIF_CTRL_CLR_SFTRST_MASK)
/*! @} */

/*! @name CTRL_TOG - LCDIF General Control Register */
/*! @{ */

#define LCDIF_CTRL_TOG_RUN_MASK                  (0x1U)
#define LCDIF_CTRL_TOG_RUN_SHIFT                 (0U)
#define LCDIF_CTRL_TOG_RUN(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_RUN_SHIFT)) & LCDIF_CTRL_TOG_RUN_MASK)

#define LCDIF_CTRL_TOG_DATA_FORMAT_24_BIT_MASK   (0x2U)
#define LCDIF_CTRL_TOG_DATA_FORMAT_24_BIT_SHIFT  (1U)
/*! DATA_FORMAT_24_BIT
 *  0b0..Data input to the block is in 24 bpp format, such that all RGB 888 data is contained in 24 bits.
 *  0b1..Data input to the block is actually RGB 18 bpp, but there is 1 color per byte, hence the upper 2 bits in
 *       each byte do not contain any useful data, and should be dropped.
 */
#define LCDIF_CTRL_TOG_DATA_FORMAT_24_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_DATA_FORMAT_24_BIT_SHIFT)) & LCDIF_CTRL_TOG_DATA_FORMAT_24_BIT_MASK)

#define LCDIF_CTRL_TOG_DATA_FORMAT_18_BIT_MASK   (0x4U)
#define LCDIF_CTRL_TOG_DATA_FORMAT_18_BIT_SHIFT  (2U)
/*! DATA_FORMAT_18_BIT
 *  0b0..Data input to the block is in 18 bpp format, such that lower 18 bits contain RGB 666 and upper 14 bits do not contain any useful data.
 *  0b1..Data input to the block is in 18 bpp format, such that upper 18 bits contain RGB 666 and lower 14 bits do not contain any useful data.
 */
#define LCDIF_CTRL_TOG_DATA_FORMAT_18_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_DATA_FORMAT_18_BIT_SHIFT)) & LCDIF_CTRL_TOG_DATA_FORMAT_18_BIT_MASK)

#define LCDIF_CTRL_TOG_DATA_FORMAT_16_BIT_MASK   (0x8U)
#define LCDIF_CTRL_TOG_DATA_FORMAT_16_BIT_SHIFT  (3U)
#define LCDIF_CTRL_TOG_DATA_FORMAT_16_BIT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_DATA_FORMAT_16_BIT_SHIFT)) & LCDIF_CTRL_TOG_DATA_FORMAT_16_BIT_MASK)

#define LCDIF_CTRL_TOG_RSRVD0_MASK               (0x10U)
#define LCDIF_CTRL_TOG_RSRVD0_SHIFT              (4U)
#define LCDIF_CTRL_TOG_RSRVD0(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_RSRVD0_SHIFT)) & LCDIF_CTRL_TOG_RSRVD0_MASK)

#define LCDIF_CTRL_TOG_MASTER_MASK               (0x20U)
#define LCDIF_CTRL_TOG_MASTER_SHIFT              (5U)
#define LCDIF_CTRL_TOG_MASTER(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_MASTER_SHIFT)) & LCDIF_CTRL_TOG_MASTER_MASK)

#define LCDIF_CTRL_TOG_ENABLE_PXP_HANDSHAKE_MASK (0x40U)
#define LCDIF_CTRL_TOG_ENABLE_PXP_HANDSHAKE_SHIFT (6U)
#define LCDIF_CTRL_TOG_ENABLE_PXP_HANDSHAKE(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_ENABLE_PXP_HANDSHAKE_SHIFT)) & LCDIF_CTRL_TOG_ENABLE_PXP_HANDSHAKE_MASK)

#define LCDIF_CTRL_TOG_WORD_LENGTH_MASK          (0x300U)
#define LCDIF_CTRL_TOG_WORD_LENGTH_SHIFT         (8U)
/*! WORD_LENGTH
 *  0b00..Input data is 16 bits per pixel.
 *  0b01..Input data is 8 bits wide.
 *  0b10..Input data is 18 bits per pixel.
 *  0b11..Input data is 24 bits per pixel.
 */
#define LCDIF_CTRL_TOG_WORD_LENGTH(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_WORD_LENGTH_SHIFT)) & LCDIF_CTRL_TOG_WORD_LENGTH_MASK)

#define LCDIF_CTRL_TOG_LCD_DATABUS_WIDTH_MASK    (0xC00U)
#define LCDIF_CTRL_TOG_LCD_DATABUS_WIDTH_SHIFT   (10U)
/*! LCD_DATABUS_WIDTH
 *  0b00..16-bit data bus mode.
 *  0b01..8-bit data bus mode.
 *  0b10..18-bit data bus mode.
 *  0b11..24-bit data bus mode.
 */
#define LCDIF_CTRL_TOG_LCD_DATABUS_WIDTH(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_LCD_DATABUS_WIDTH_SHIFT)) & LCDIF_CTRL_TOG_LCD_DATABUS_WIDTH_MASK)

#define LCDIF_CTRL_TOG_CSC_DATA_SWIZZLE_MASK     (0x3000U)
#define LCDIF_CTRL_TOG_CSC_DATA_SWIZZLE_SHIFT    (12U)
/*! CSC_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_TOG_CSC_DATA_SWIZZLE(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_CSC_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_TOG_CSC_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_TOG_INPUT_DATA_SWIZZLE_MASK   (0xC000U)
#define LCDIF_CTRL_TOG_INPUT_DATA_SWIZZLE_SHIFT  (14U)
/*! INPUT_DATA_SWIZZLE
 *  0b00..Little Endian byte ordering (same as NO_SWAP).
 *  0b00..No byte swapping.(Little endian)
 *  0b01..Big Endian swap (swap bytes 0,3 and 1,2).
 *  0b01..Swizzle all bytes, swap bytes 0,3 and 1,2 (aka Big Endian).
 *  0b10..Swap half-words.
 *  0b11..Swap bytes within each half-word.
 */
#define LCDIF_CTRL_TOG_INPUT_DATA_SWIZZLE(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_INPUT_DATA_SWIZZLE_SHIFT)) & LCDIF_CTRL_TOG_INPUT_DATA_SWIZZLE_MASK)

#define LCDIF_CTRL_TOG_DOTCLK_MODE_MASK          (0x20000U)
#define LCDIF_CTRL_TOG_DOTCLK_MODE_SHIFT         (17U)
#define LCDIF_CTRL_TOG_DOTCLK_MODE(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_DOTCLK_MODE_SHIFT)) & LCDIF_CTRL_TOG_DOTCLK_MODE_MASK)

#define LCDIF_CTRL_TOG_BYPASS_COUNT_MASK         (0x80000U)
#define LCDIF_CTRL_TOG_BYPASS_COUNT_SHIFT        (19U)
#define LCDIF_CTRL_TOG_BYPASS_COUNT(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_BYPASS_COUNT_SHIFT)) & LCDIF_CTRL_TOG_BYPASS_COUNT_MASK)

#define LCDIF_CTRL_TOG_SHIFT_NUM_BITS_MASK       (0x3E00000U)
#define LCDIF_CTRL_TOG_SHIFT_NUM_BITS_SHIFT      (21U)
#define LCDIF_CTRL_TOG_SHIFT_NUM_BITS(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_SHIFT_NUM_BITS_SHIFT)) & LCDIF_CTRL_TOG_SHIFT_NUM_BITS_MASK)

#define LCDIF_CTRL_TOG_DATA_SHIFT_DIR_MASK       (0x4000000U)
#define LCDIF_CTRL_TOG_DATA_SHIFT_DIR_SHIFT      (26U)
/*! DATA_SHIFT_DIR
 *  0b0..Data to be transmitted is shifted LEFT by SHIFT_NUM_BITS bits.
 *  0b1..Data to be transmitted is shifted RIGHT by SHIFT_NUM_BITS bits.
 */
#define LCDIF_CTRL_TOG_DATA_SHIFT_DIR(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_DATA_SHIFT_DIR_SHIFT)) & LCDIF_CTRL_TOG_DATA_SHIFT_DIR_MASK)

#define LCDIF_CTRL_TOG_CLKGATE_MASK              (0x40000000U)
#define LCDIF_CTRL_TOG_CLKGATE_SHIFT             (30U)
#define LCDIF_CTRL_TOG_CLKGATE(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_CLKGATE_SHIFT)) & LCDIF_CTRL_TOG_CLKGATE_MASK)

#define LCDIF_CTRL_TOG_SFTRST_MASK               (0x80000000U)
#define LCDIF_CTRL_TOG_SFTRST_SHIFT              (31U)
#define LCDIF_CTRL_TOG_SFTRST(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL_TOG_SFTRST_SHIFT)) & LCDIF_CTRL_TOG_SFTRST_MASK)
/*! @} */

/*! @name CTRL1 - LCDIF General Control1 Register */
/*! @{ */

#define LCDIF_CTRL1_RSRVD0_MASK                  (0xF8U)
#define LCDIF_CTRL1_RSRVD0_SHIFT                 (3U)
#define LCDIF_CTRL1_RSRVD0(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_RSRVD0_SHIFT)) & LCDIF_CTRL1_RSRVD0_MASK)

#define LCDIF_CTRL1_VSYNC_EDGE_IRQ_MASK          (0x100U)
#define LCDIF_CTRL1_VSYNC_EDGE_IRQ_SHIFT         (8U)
/*! VSYNC_EDGE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_VSYNC_EDGE_IRQ(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_VSYNC_EDGE_IRQ_SHIFT)) & LCDIF_CTRL1_VSYNC_EDGE_IRQ_MASK)

#define LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_MASK      (0x200U)
#define LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_SHIFT     (9U)
/*! CUR_FRAME_DONE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_CUR_FRAME_DONE_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_SHIFT)) & LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_MASK)

#define LCDIF_CTRL1_UNDERFLOW_IRQ_MASK           (0x400U)
#define LCDIF_CTRL1_UNDERFLOW_IRQ_SHIFT          (10U)
/*! UNDERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_UNDERFLOW_IRQ(x)             (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_UNDERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_UNDERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_OVERFLOW_IRQ_MASK            (0x800U)
#define LCDIF_CTRL1_OVERFLOW_IRQ_SHIFT           (11U)
/*! OVERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_OVERFLOW_IRQ(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_OVERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_OVERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_VSYNC_EDGE_IRQ_EN_MASK       (0x1000U)
#define LCDIF_CTRL1_VSYNC_EDGE_IRQ_EN_SHIFT      (12U)
#define LCDIF_CTRL1_VSYNC_EDGE_IRQ_EN(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_VSYNC_EDGE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_VSYNC_EDGE_IRQ_EN_MASK)

#define LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_EN_MASK   (0x2000U)
#define LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_EN_SHIFT  (13U)
#define LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_EN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_CUR_FRAME_DONE_IRQ_EN_MASK)

#define LCDIF_CTRL1_UNDERFLOW_IRQ_EN_MASK        (0x4000U)
#define LCDIF_CTRL1_UNDERFLOW_IRQ_EN_SHIFT       (14U)
#define LCDIF_CTRL1_UNDERFLOW_IRQ_EN(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_UNDERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_UNDERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_OVERFLOW_IRQ_EN_MASK         (0x8000U)
#define LCDIF_CTRL1_OVERFLOW_IRQ_EN_SHIFT        (15U)
#define LCDIF_CTRL1_OVERFLOW_IRQ_EN(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_OVERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_OVERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_BYTE_PACKING_FORMAT_MASK     (0xF0000U)
#define LCDIF_CTRL1_BYTE_PACKING_FORMAT_SHIFT    (16U)
#define LCDIF_CTRL1_BYTE_PACKING_FORMAT(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_BYTE_PACKING_FORMAT_SHIFT)) & LCDIF_CTRL1_BYTE_PACKING_FORMAT_MASK)

#define LCDIF_CTRL1_IRQ_ON_ALTERNATE_FIELDS_MASK (0x100000U)
#define LCDIF_CTRL1_IRQ_ON_ALTERNATE_FIELDS_SHIFT (20U)
#define LCDIF_CTRL1_IRQ_ON_ALTERNATE_FIELDS(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_IRQ_ON_ALTERNATE_FIELDS_SHIFT)) & LCDIF_CTRL1_IRQ_ON_ALTERNATE_FIELDS_MASK)

#define LCDIF_CTRL1_FIFO_CLEAR_MASK              (0x200000U)
#define LCDIF_CTRL1_FIFO_CLEAR_SHIFT             (21U)
#define LCDIF_CTRL1_FIFO_CLEAR(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_FIFO_CLEAR_SHIFT)) & LCDIF_CTRL1_FIFO_CLEAR_MASK)

#define LCDIF_CTRL1_START_INTERLACE_FROM_SECOND_FIELD_MASK (0x400000U)
#define LCDIF_CTRL1_START_INTERLACE_FROM_SECOND_FIELD_SHIFT (22U)
#define LCDIF_CTRL1_START_INTERLACE_FROM_SECOND_FIELD(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_START_INTERLACE_FROM_SECOND_FIELD_SHIFT)) & LCDIF_CTRL1_START_INTERLACE_FROM_SECOND_FIELD_MASK)

#define LCDIF_CTRL1_INTERLACE_FIELDS_MASK        (0x800000U)
#define LCDIF_CTRL1_INTERLACE_FIELDS_SHIFT       (23U)
#define LCDIF_CTRL1_INTERLACE_FIELDS(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_INTERLACE_FIELDS_SHIFT)) & LCDIF_CTRL1_INTERLACE_FIELDS_MASK)

#define LCDIF_CTRL1_RECOVER_ON_UNDERFLOW_MASK    (0x1000000U)
#define LCDIF_CTRL1_RECOVER_ON_UNDERFLOW_SHIFT   (24U)
#define LCDIF_CTRL1_RECOVER_ON_UNDERFLOW(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_RECOVER_ON_UNDERFLOW_SHIFT)) & LCDIF_CTRL1_RECOVER_ON_UNDERFLOW_MASK)

#define LCDIF_CTRL1_BM_ERROR_IRQ_MASK            (0x2000000U)
#define LCDIF_CTRL1_BM_ERROR_IRQ_SHIFT           (25U)
/*! BM_ERROR_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_BM_ERROR_IRQ(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_BM_ERROR_IRQ_SHIFT)) & LCDIF_CTRL1_BM_ERROR_IRQ_MASK)

#define LCDIF_CTRL1_BM_ERROR_IRQ_EN_MASK         (0x4000000U)
#define LCDIF_CTRL1_BM_ERROR_IRQ_EN_SHIFT        (26U)
#define LCDIF_CTRL1_BM_ERROR_IRQ_EN(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_BM_ERROR_IRQ_EN_SHIFT)) & LCDIF_CTRL1_BM_ERROR_IRQ_EN_MASK)

#define LCDIF_CTRL1_CS_OUT_SELECT_MASK           (0x40000000U)
#define LCDIF_CTRL1_CS_OUT_SELECT_SHIFT          (30U)
#define LCDIF_CTRL1_CS_OUT_SELECT(x)             (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CS_OUT_SELECT_SHIFT)) & LCDIF_CTRL1_CS_OUT_SELECT_MASK)

#define LCDIF_CTRL1_IMAGE_DATA_SELECT_MASK       (0x80000000U)
#define LCDIF_CTRL1_IMAGE_DATA_SELECT_SHIFT      (31U)
#define LCDIF_CTRL1_IMAGE_DATA_SELECT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_IMAGE_DATA_SELECT_SHIFT)) & LCDIF_CTRL1_IMAGE_DATA_SELECT_MASK)
/*! @} */

/*! @name CTRL1_SET - LCDIF General Control1 Register */
/*! @{ */

#define LCDIF_CTRL1_SET_RSRVD0_MASK              (0xF8U)
#define LCDIF_CTRL1_SET_RSRVD0_SHIFT             (3U)
#define LCDIF_CTRL1_SET_RSRVD0(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_RSRVD0_SHIFT)) & LCDIF_CTRL1_SET_RSRVD0_MASK)

#define LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_MASK      (0x100U)
#define LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_SHIFT     (8U)
/*! VSYNC_EDGE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_SHIFT)) & LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_MASK)

#define LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_MASK  (0x200U)
#define LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_SHIFT (9U)
/*! CUR_FRAME_DONE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ(x)    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_SHIFT)) & LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_MASK)

#define LCDIF_CTRL1_SET_UNDERFLOW_IRQ_MASK       (0x400U)
#define LCDIF_CTRL1_SET_UNDERFLOW_IRQ_SHIFT      (10U)
/*! UNDERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_SET_UNDERFLOW_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_UNDERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_SET_UNDERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_SET_OVERFLOW_IRQ_MASK        (0x800U)
#define LCDIF_CTRL1_SET_OVERFLOW_IRQ_SHIFT       (11U)
/*! OVERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_SET_OVERFLOW_IRQ(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_OVERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_SET_OVERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_EN_MASK   (0x1000U)
#define LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_EN_SHIFT  (12U)
#define LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_EN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_SET_VSYNC_EDGE_IRQ_EN_MASK)

#define LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_EN_MASK (0x2000U)
#define LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_EN_SHIFT (13U)
#define LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_EN(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_SET_CUR_FRAME_DONE_IRQ_EN_MASK)

#define LCDIF_CTRL1_SET_UNDERFLOW_IRQ_EN_MASK    (0x4000U)
#define LCDIF_CTRL1_SET_UNDERFLOW_IRQ_EN_SHIFT   (14U)
#define LCDIF_CTRL1_SET_UNDERFLOW_IRQ_EN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_UNDERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_SET_UNDERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_SET_OVERFLOW_IRQ_EN_MASK     (0x8000U)
#define LCDIF_CTRL1_SET_OVERFLOW_IRQ_EN_SHIFT    (15U)
#define LCDIF_CTRL1_SET_OVERFLOW_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_OVERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_SET_OVERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_SET_BYTE_PACKING_FORMAT_MASK (0xF0000U)
#define LCDIF_CTRL1_SET_BYTE_PACKING_FORMAT_SHIFT (16U)
#define LCDIF_CTRL1_SET_BYTE_PACKING_FORMAT(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_BYTE_PACKING_FORMAT_SHIFT)) & LCDIF_CTRL1_SET_BYTE_PACKING_FORMAT_MASK)

#define LCDIF_CTRL1_SET_IRQ_ON_ALTERNATE_FIELDS_MASK (0x100000U)
#define LCDIF_CTRL1_SET_IRQ_ON_ALTERNATE_FIELDS_SHIFT (20U)
#define LCDIF_CTRL1_SET_IRQ_ON_ALTERNATE_FIELDS(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_IRQ_ON_ALTERNATE_FIELDS_SHIFT)) & LCDIF_CTRL1_SET_IRQ_ON_ALTERNATE_FIELDS_MASK)

#define LCDIF_CTRL1_SET_FIFO_CLEAR_MASK          (0x200000U)
#define LCDIF_CTRL1_SET_FIFO_CLEAR_SHIFT         (21U)
#define LCDIF_CTRL1_SET_FIFO_CLEAR(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_FIFO_CLEAR_SHIFT)) & LCDIF_CTRL1_SET_FIFO_CLEAR_MASK)

#define LCDIF_CTRL1_SET_START_INTERLACE_FROM_SECOND_FIELD_MASK (0x400000U)
#define LCDIF_CTRL1_SET_START_INTERLACE_FROM_SECOND_FIELD_SHIFT (22U)
#define LCDIF_CTRL1_SET_START_INTERLACE_FROM_SECOND_FIELD(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_START_INTERLACE_FROM_SECOND_FIELD_SHIFT)) & LCDIF_CTRL1_SET_START_INTERLACE_FROM_SECOND_FIELD_MASK)

#define LCDIF_CTRL1_SET_INTERLACE_FIELDS_MASK    (0x800000U)
#define LCDIF_CTRL1_SET_INTERLACE_FIELDS_SHIFT   (23U)
#define LCDIF_CTRL1_SET_INTERLACE_FIELDS(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_INTERLACE_FIELDS_SHIFT)) & LCDIF_CTRL1_SET_INTERLACE_FIELDS_MASK)

#define LCDIF_CTRL1_SET_RECOVER_ON_UNDERFLOW_MASK (0x1000000U)
#define LCDIF_CTRL1_SET_RECOVER_ON_UNDERFLOW_SHIFT (24U)
#define LCDIF_CTRL1_SET_RECOVER_ON_UNDERFLOW(x)  (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_RECOVER_ON_UNDERFLOW_SHIFT)) & LCDIF_CTRL1_SET_RECOVER_ON_UNDERFLOW_MASK)

#define LCDIF_CTRL1_SET_BM_ERROR_IRQ_MASK        (0x2000000U)
#define LCDIF_CTRL1_SET_BM_ERROR_IRQ_SHIFT       (25U)
/*! BM_ERROR_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_SET_BM_ERROR_IRQ(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_BM_ERROR_IRQ_SHIFT)) & LCDIF_CTRL1_SET_BM_ERROR_IRQ_MASK)

#define LCDIF_CTRL1_SET_BM_ERROR_IRQ_EN_MASK     (0x4000000U)
#define LCDIF_CTRL1_SET_BM_ERROR_IRQ_EN_SHIFT    (26U)
#define LCDIF_CTRL1_SET_BM_ERROR_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_BM_ERROR_IRQ_EN_SHIFT)) & LCDIF_CTRL1_SET_BM_ERROR_IRQ_EN_MASK)

#define LCDIF_CTRL1_SET_CS_OUT_SELECT_MASK       (0x40000000U)
#define LCDIF_CTRL1_SET_CS_OUT_SELECT_SHIFT      (30U)
#define LCDIF_CTRL1_SET_CS_OUT_SELECT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_CS_OUT_SELECT_SHIFT)) & LCDIF_CTRL1_SET_CS_OUT_SELECT_MASK)

#define LCDIF_CTRL1_SET_IMAGE_DATA_SELECT_MASK   (0x80000000U)
#define LCDIF_CTRL1_SET_IMAGE_DATA_SELECT_SHIFT  (31U)
#define LCDIF_CTRL1_SET_IMAGE_DATA_SELECT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_SET_IMAGE_DATA_SELECT_SHIFT)) & LCDIF_CTRL1_SET_IMAGE_DATA_SELECT_MASK)
/*! @} */

/*! @name CTRL1_CLR - LCDIF General Control1 Register */
/*! @{ */

#define LCDIF_CTRL1_CLR_RSRVD0_MASK              (0xF8U)
#define LCDIF_CTRL1_CLR_RSRVD0_SHIFT             (3U)
#define LCDIF_CTRL1_CLR_RSRVD0(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_RSRVD0_SHIFT)) & LCDIF_CTRL1_CLR_RSRVD0_MASK)

#define LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_MASK      (0x100U)
#define LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_SHIFT     (8U)
/*! VSYNC_EDGE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_SHIFT)) & LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_MASK)

#define LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_MASK  (0x200U)
#define LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_SHIFT (9U)
/*! CUR_FRAME_DONE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ(x)    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_SHIFT)) & LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_MASK)

#define LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_MASK       (0x400U)
#define LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_SHIFT      (10U)
/*! UNDERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_CLR_UNDERFLOW_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_CLR_OVERFLOW_IRQ_MASK        (0x800U)
#define LCDIF_CTRL1_CLR_OVERFLOW_IRQ_SHIFT       (11U)
/*! OVERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_CLR_OVERFLOW_IRQ(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_OVERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_CLR_OVERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_EN_MASK   (0x1000U)
#define LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_EN_SHIFT  (12U)
#define LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_EN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_CLR_VSYNC_EDGE_IRQ_EN_MASK)

#define LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_EN_MASK (0x2000U)
#define LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_EN_SHIFT (13U)
#define LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_EN(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_CLR_CUR_FRAME_DONE_IRQ_EN_MASK)

#define LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_EN_MASK    (0x4000U)
#define LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_EN_SHIFT   (14U)
#define LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_EN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_CLR_UNDERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_CLR_OVERFLOW_IRQ_EN_MASK     (0x8000U)
#define LCDIF_CTRL1_CLR_OVERFLOW_IRQ_EN_SHIFT    (15U)
#define LCDIF_CTRL1_CLR_OVERFLOW_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_OVERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_CLR_OVERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_CLR_BYTE_PACKING_FORMAT_MASK (0xF0000U)
#define LCDIF_CTRL1_CLR_BYTE_PACKING_FORMAT_SHIFT (16U)
#define LCDIF_CTRL1_CLR_BYTE_PACKING_FORMAT(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_BYTE_PACKING_FORMAT_SHIFT)) & LCDIF_CTRL1_CLR_BYTE_PACKING_FORMAT_MASK)

#define LCDIF_CTRL1_CLR_IRQ_ON_ALTERNATE_FIELDS_MASK (0x100000U)
#define LCDIF_CTRL1_CLR_IRQ_ON_ALTERNATE_FIELDS_SHIFT (20U)
#define LCDIF_CTRL1_CLR_IRQ_ON_ALTERNATE_FIELDS(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_IRQ_ON_ALTERNATE_FIELDS_SHIFT)) & LCDIF_CTRL1_CLR_IRQ_ON_ALTERNATE_FIELDS_MASK)

#define LCDIF_CTRL1_CLR_FIFO_CLEAR_MASK          (0x200000U)
#define LCDIF_CTRL1_CLR_FIFO_CLEAR_SHIFT         (21U)
#define LCDIF_CTRL1_CLR_FIFO_CLEAR(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_FIFO_CLEAR_SHIFT)) & LCDIF_CTRL1_CLR_FIFO_CLEAR_MASK)

#define LCDIF_CTRL1_CLR_START_INTERLACE_FROM_SECOND_FIELD_MASK (0x400000U)
#define LCDIF_CTRL1_CLR_START_INTERLACE_FROM_SECOND_FIELD_SHIFT (22U)
#define LCDIF_CTRL1_CLR_START_INTERLACE_FROM_SECOND_FIELD(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_START_INTERLACE_FROM_SECOND_FIELD_SHIFT)) & LCDIF_CTRL1_CLR_START_INTERLACE_FROM_SECOND_FIELD_MASK)

#define LCDIF_CTRL1_CLR_INTERLACE_FIELDS_MASK    (0x800000U)
#define LCDIF_CTRL1_CLR_INTERLACE_FIELDS_SHIFT   (23U)
#define LCDIF_CTRL1_CLR_INTERLACE_FIELDS(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_INTERLACE_FIELDS_SHIFT)) & LCDIF_CTRL1_CLR_INTERLACE_FIELDS_MASK)

#define LCDIF_CTRL1_CLR_RECOVER_ON_UNDERFLOW_MASK (0x1000000U)
#define LCDIF_CTRL1_CLR_RECOVER_ON_UNDERFLOW_SHIFT (24U)
#define LCDIF_CTRL1_CLR_RECOVER_ON_UNDERFLOW(x)  (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_RECOVER_ON_UNDERFLOW_SHIFT)) & LCDIF_CTRL1_CLR_RECOVER_ON_UNDERFLOW_MASK)

#define LCDIF_CTRL1_CLR_BM_ERROR_IRQ_MASK        (0x2000000U)
#define LCDIF_CTRL1_CLR_BM_ERROR_IRQ_SHIFT       (25U)
/*! BM_ERROR_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_CLR_BM_ERROR_IRQ(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_BM_ERROR_IRQ_SHIFT)) & LCDIF_CTRL1_CLR_BM_ERROR_IRQ_MASK)

#define LCDIF_CTRL1_CLR_BM_ERROR_IRQ_EN_MASK     (0x4000000U)
#define LCDIF_CTRL1_CLR_BM_ERROR_IRQ_EN_SHIFT    (26U)
#define LCDIF_CTRL1_CLR_BM_ERROR_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_BM_ERROR_IRQ_EN_SHIFT)) & LCDIF_CTRL1_CLR_BM_ERROR_IRQ_EN_MASK)

#define LCDIF_CTRL1_CLR_CS_OUT_SELECT_MASK       (0x40000000U)
#define LCDIF_CTRL1_CLR_CS_OUT_SELECT_SHIFT      (30U)
#define LCDIF_CTRL1_CLR_CS_OUT_SELECT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_CS_OUT_SELECT_SHIFT)) & LCDIF_CTRL1_CLR_CS_OUT_SELECT_MASK)

#define LCDIF_CTRL1_CLR_IMAGE_DATA_SELECT_MASK   (0x80000000U)
#define LCDIF_CTRL1_CLR_IMAGE_DATA_SELECT_SHIFT  (31U)
#define LCDIF_CTRL1_CLR_IMAGE_DATA_SELECT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_CLR_IMAGE_DATA_SELECT_SHIFT)) & LCDIF_CTRL1_CLR_IMAGE_DATA_SELECT_MASK)
/*! @} */

/*! @name CTRL1_TOG - LCDIF General Control1 Register */
/*! @{ */

#define LCDIF_CTRL1_TOG_RSRVD0_MASK              (0xF8U)
#define LCDIF_CTRL1_TOG_RSRVD0_SHIFT             (3U)
#define LCDIF_CTRL1_TOG_RSRVD0(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_RSRVD0_SHIFT)) & LCDIF_CTRL1_TOG_RSRVD0_MASK)

#define LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_MASK      (0x100U)
#define LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_SHIFT     (8U)
/*! VSYNC_EDGE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_SHIFT)) & LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_MASK)

#define LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_MASK  (0x200U)
#define LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_SHIFT (9U)
/*! CUR_FRAME_DONE_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ(x)    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_SHIFT)) & LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_MASK)

#define LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_MASK       (0x400U)
#define LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_SHIFT      (10U)
/*! UNDERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_TOG_UNDERFLOW_IRQ(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_TOG_OVERFLOW_IRQ_MASK        (0x800U)
#define LCDIF_CTRL1_TOG_OVERFLOW_IRQ_SHIFT       (11U)
/*! OVERFLOW_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_TOG_OVERFLOW_IRQ(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_OVERFLOW_IRQ_SHIFT)) & LCDIF_CTRL1_TOG_OVERFLOW_IRQ_MASK)

#define LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_EN_MASK   (0x1000U)
#define LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_EN_SHIFT  (12U)
#define LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_EN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_TOG_VSYNC_EDGE_IRQ_EN_MASK)

#define LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_EN_MASK (0x2000U)
#define LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_EN_SHIFT (13U)
#define LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_EN(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_EN_SHIFT)) & LCDIF_CTRL1_TOG_CUR_FRAME_DONE_IRQ_EN_MASK)

#define LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_EN_MASK    (0x4000U)
#define LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_EN_SHIFT   (14U)
#define LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_EN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_TOG_UNDERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_TOG_OVERFLOW_IRQ_EN_MASK     (0x8000U)
#define LCDIF_CTRL1_TOG_OVERFLOW_IRQ_EN_SHIFT    (15U)
#define LCDIF_CTRL1_TOG_OVERFLOW_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_OVERFLOW_IRQ_EN_SHIFT)) & LCDIF_CTRL1_TOG_OVERFLOW_IRQ_EN_MASK)

#define LCDIF_CTRL1_TOG_BYTE_PACKING_FORMAT_MASK (0xF0000U)
#define LCDIF_CTRL1_TOG_BYTE_PACKING_FORMAT_SHIFT (16U)
#define LCDIF_CTRL1_TOG_BYTE_PACKING_FORMAT(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_BYTE_PACKING_FORMAT_SHIFT)) & LCDIF_CTRL1_TOG_BYTE_PACKING_FORMAT_MASK)

#define LCDIF_CTRL1_TOG_IRQ_ON_ALTERNATE_FIELDS_MASK (0x100000U)
#define LCDIF_CTRL1_TOG_IRQ_ON_ALTERNATE_FIELDS_SHIFT (20U)
#define LCDIF_CTRL1_TOG_IRQ_ON_ALTERNATE_FIELDS(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_IRQ_ON_ALTERNATE_FIELDS_SHIFT)) & LCDIF_CTRL1_TOG_IRQ_ON_ALTERNATE_FIELDS_MASK)

#define LCDIF_CTRL1_TOG_FIFO_CLEAR_MASK          (0x200000U)
#define LCDIF_CTRL1_TOG_FIFO_CLEAR_SHIFT         (21U)
#define LCDIF_CTRL1_TOG_FIFO_CLEAR(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_FIFO_CLEAR_SHIFT)) & LCDIF_CTRL1_TOG_FIFO_CLEAR_MASK)

#define LCDIF_CTRL1_TOG_START_INTERLACE_FROM_SECOND_FIELD_MASK (0x400000U)
#define LCDIF_CTRL1_TOG_START_INTERLACE_FROM_SECOND_FIELD_SHIFT (22U)
#define LCDIF_CTRL1_TOG_START_INTERLACE_FROM_SECOND_FIELD(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_START_INTERLACE_FROM_SECOND_FIELD_SHIFT)) & LCDIF_CTRL1_TOG_START_INTERLACE_FROM_SECOND_FIELD_MASK)

#define LCDIF_CTRL1_TOG_INTERLACE_FIELDS_MASK    (0x800000U)
#define LCDIF_CTRL1_TOG_INTERLACE_FIELDS_SHIFT   (23U)
#define LCDIF_CTRL1_TOG_INTERLACE_FIELDS(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_INTERLACE_FIELDS_SHIFT)) & LCDIF_CTRL1_TOG_INTERLACE_FIELDS_MASK)

#define LCDIF_CTRL1_TOG_RECOVER_ON_UNDERFLOW_MASK (0x1000000U)
#define LCDIF_CTRL1_TOG_RECOVER_ON_UNDERFLOW_SHIFT (24U)
#define LCDIF_CTRL1_TOG_RECOVER_ON_UNDERFLOW(x)  (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_RECOVER_ON_UNDERFLOW_SHIFT)) & LCDIF_CTRL1_TOG_RECOVER_ON_UNDERFLOW_MASK)

#define LCDIF_CTRL1_TOG_BM_ERROR_IRQ_MASK        (0x2000000U)
#define LCDIF_CTRL1_TOG_BM_ERROR_IRQ_SHIFT       (25U)
/*! BM_ERROR_IRQ
 *  0b0..No Interrupt Request Pending.
 *  0b1..Interrupt Request Pending.
 */
#define LCDIF_CTRL1_TOG_BM_ERROR_IRQ(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_BM_ERROR_IRQ_SHIFT)) & LCDIF_CTRL1_TOG_BM_ERROR_IRQ_MASK)

#define LCDIF_CTRL1_TOG_BM_ERROR_IRQ_EN_MASK     (0x4000000U)
#define LCDIF_CTRL1_TOG_BM_ERROR_IRQ_EN_SHIFT    (26U)
#define LCDIF_CTRL1_TOG_BM_ERROR_IRQ_EN(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_BM_ERROR_IRQ_EN_SHIFT)) & LCDIF_CTRL1_TOG_BM_ERROR_IRQ_EN_MASK)

#define LCDIF_CTRL1_TOG_CS_OUT_SELECT_MASK       (0x40000000U)
#define LCDIF_CTRL1_TOG_CS_OUT_SELECT_SHIFT      (30U)
#define LCDIF_CTRL1_TOG_CS_OUT_SELECT(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_CS_OUT_SELECT_SHIFT)) & LCDIF_CTRL1_TOG_CS_OUT_SELECT_MASK)

#define LCDIF_CTRL1_TOG_IMAGE_DATA_SELECT_MASK   (0x80000000U)
#define LCDIF_CTRL1_TOG_IMAGE_DATA_SELECT_SHIFT  (31U)
#define LCDIF_CTRL1_TOG_IMAGE_DATA_SELECT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL1_TOG_IMAGE_DATA_SELECT_SHIFT)) & LCDIF_CTRL1_TOG_IMAGE_DATA_SELECT_MASK)
/*! @} */

/*! @name CTRL2 - LCDIF General Control2 Register */
/*! @{ */

#define LCDIF_CTRL2_RSRVD0_MASK                  (0xFFFU)
#define LCDIF_CTRL2_RSRVD0_SHIFT                 (0U)
#define LCDIF_CTRL2_RSRVD0(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_RSRVD0_SHIFT)) & LCDIF_CTRL2_RSRVD0_MASK)

#define LCDIF_CTRL2_EVEN_LINE_PATTERN_MASK       (0x7000U)
#define LCDIF_CTRL2_EVEN_LINE_PATTERN_SHIFT      (12U)
/*! EVEN_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_EVEN_LINE_PATTERN(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_EVEN_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_EVEN_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_RSRVD3_MASK                  (0x8000U)
#define LCDIF_CTRL2_RSRVD3_SHIFT                 (15U)
#define LCDIF_CTRL2_RSRVD3(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_RSRVD3_SHIFT)) & LCDIF_CTRL2_RSRVD3_MASK)

#define LCDIF_CTRL2_ODD_LINE_PATTERN_MASK        (0x70000U)
#define LCDIF_CTRL2_ODD_LINE_PATTERN_SHIFT       (16U)
/*! ODD_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_ODD_LINE_PATTERN(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_ODD_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_ODD_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_RSRVD4_MASK                  (0x80000U)
#define LCDIF_CTRL2_RSRVD4_SHIFT                 (19U)
#define LCDIF_CTRL2_RSRVD4(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_RSRVD4_SHIFT)) & LCDIF_CTRL2_RSRVD4_MASK)

#define LCDIF_CTRL2_BURST_LEN_8_MASK             (0x100000U)
#define LCDIF_CTRL2_BURST_LEN_8_SHIFT            (20U)
#define LCDIF_CTRL2_BURST_LEN_8(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_BURST_LEN_8_SHIFT)) & LCDIF_CTRL2_BURST_LEN_8_MASK)

#define LCDIF_CTRL2_OUTSTANDING_REQS_MASK        (0xE00000U)
#define LCDIF_CTRL2_OUTSTANDING_REQS_SHIFT       (21U)
/*! OUTSTANDING_REQS
 *  0b000..REQ_1
 *  0b001..REQ_2
 *  0b010..REQ_4
 *  0b011..REQ_8
 *  0b100..REQ_16
 */
#define LCDIF_CTRL2_OUTSTANDING_REQS(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_OUTSTANDING_REQS_SHIFT)) & LCDIF_CTRL2_OUTSTANDING_REQS_MASK)

#define LCDIF_CTRL2_RSRVD5_MASK                  (0xFF000000U)
#define LCDIF_CTRL2_RSRVD5_SHIFT                 (24U)
#define LCDIF_CTRL2_RSRVD5(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_RSRVD5_SHIFT)) & LCDIF_CTRL2_RSRVD5_MASK)
/*! @} */

/*! @name CTRL2_SET - LCDIF General Control2 Register */
/*! @{ */

#define LCDIF_CTRL2_SET_RSRVD0_MASK              (0xFFFU)
#define LCDIF_CTRL2_SET_RSRVD0_SHIFT             (0U)
#define LCDIF_CTRL2_SET_RSRVD0(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_RSRVD0_SHIFT)) & LCDIF_CTRL2_SET_RSRVD0_MASK)

#define LCDIF_CTRL2_SET_EVEN_LINE_PATTERN_MASK   (0x7000U)
#define LCDIF_CTRL2_SET_EVEN_LINE_PATTERN_SHIFT  (12U)
/*! EVEN_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_SET_EVEN_LINE_PATTERN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_EVEN_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_SET_EVEN_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_SET_RSRVD3_MASK              (0x8000U)
#define LCDIF_CTRL2_SET_RSRVD3_SHIFT             (15U)
#define LCDIF_CTRL2_SET_RSRVD3(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_RSRVD3_SHIFT)) & LCDIF_CTRL2_SET_RSRVD3_MASK)

#define LCDIF_CTRL2_SET_ODD_LINE_PATTERN_MASK    (0x70000U)
#define LCDIF_CTRL2_SET_ODD_LINE_PATTERN_SHIFT   (16U)
/*! ODD_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_SET_ODD_LINE_PATTERN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_ODD_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_SET_ODD_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_SET_RSRVD4_MASK              (0x80000U)
#define LCDIF_CTRL2_SET_RSRVD4_SHIFT             (19U)
#define LCDIF_CTRL2_SET_RSRVD4(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_RSRVD4_SHIFT)) & LCDIF_CTRL2_SET_RSRVD4_MASK)

#define LCDIF_CTRL2_SET_BURST_LEN_8_MASK         (0x100000U)
#define LCDIF_CTRL2_SET_BURST_LEN_8_SHIFT        (20U)
#define LCDIF_CTRL2_SET_BURST_LEN_8(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_BURST_LEN_8_SHIFT)) & LCDIF_CTRL2_SET_BURST_LEN_8_MASK)

#define LCDIF_CTRL2_SET_OUTSTANDING_REQS_MASK    (0xE00000U)
#define LCDIF_CTRL2_SET_OUTSTANDING_REQS_SHIFT   (21U)
/*! OUTSTANDING_REQS
 *  0b000..REQ_1
 *  0b001..REQ_2
 *  0b010..REQ_4
 *  0b011..REQ_8
 *  0b100..REQ_16
 */
#define LCDIF_CTRL2_SET_OUTSTANDING_REQS(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_OUTSTANDING_REQS_SHIFT)) & LCDIF_CTRL2_SET_OUTSTANDING_REQS_MASK)

#define LCDIF_CTRL2_SET_RSRVD5_MASK              (0xFF000000U)
#define LCDIF_CTRL2_SET_RSRVD5_SHIFT             (24U)
#define LCDIF_CTRL2_SET_RSRVD5(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_SET_RSRVD5_SHIFT)) & LCDIF_CTRL2_SET_RSRVD5_MASK)
/*! @} */

/*! @name CTRL2_CLR - LCDIF General Control2 Register */
/*! @{ */

#define LCDIF_CTRL2_CLR_RSRVD0_MASK              (0xFFFU)
#define LCDIF_CTRL2_CLR_RSRVD0_SHIFT             (0U)
#define LCDIF_CTRL2_CLR_RSRVD0(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_RSRVD0_SHIFT)) & LCDIF_CTRL2_CLR_RSRVD0_MASK)

#define LCDIF_CTRL2_CLR_EVEN_LINE_PATTERN_MASK   (0x7000U)
#define LCDIF_CTRL2_CLR_EVEN_LINE_PATTERN_SHIFT  (12U)
/*! EVEN_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_CLR_EVEN_LINE_PATTERN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_EVEN_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_CLR_EVEN_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_CLR_RSRVD3_MASK              (0x8000U)
#define LCDIF_CTRL2_CLR_RSRVD3_SHIFT             (15U)
#define LCDIF_CTRL2_CLR_RSRVD3(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_RSRVD3_SHIFT)) & LCDIF_CTRL2_CLR_RSRVD3_MASK)

#define LCDIF_CTRL2_CLR_ODD_LINE_PATTERN_MASK    (0x70000U)
#define LCDIF_CTRL2_CLR_ODD_LINE_PATTERN_SHIFT   (16U)
/*! ODD_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_CLR_ODD_LINE_PATTERN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_ODD_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_CLR_ODD_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_CLR_RSRVD4_MASK              (0x80000U)
#define LCDIF_CTRL2_CLR_RSRVD4_SHIFT             (19U)
#define LCDIF_CTRL2_CLR_RSRVD4(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_RSRVD4_SHIFT)) & LCDIF_CTRL2_CLR_RSRVD4_MASK)

#define LCDIF_CTRL2_CLR_BURST_LEN_8_MASK         (0x100000U)
#define LCDIF_CTRL2_CLR_BURST_LEN_8_SHIFT        (20U)
#define LCDIF_CTRL2_CLR_BURST_LEN_8(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_BURST_LEN_8_SHIFT)) & LCDIF_CTRL2_CLR_BURST_LEN_8_MASK)

#define LCDIF_CTRL2_CLR_OUTSTANDING_REQS_MASK    (0xE00000U)
#define LCDIF_CTRL2_CLR_OUTSTANDING_REQS_SHIFT   (21U)
/*! OUTSTANDING_REQS
 *  0b000..REQ_1
 *  0b001..REQ_2
 *  0b010..REQ_4
 *  0b011..REQ_8
 *  0b100..REQ_16
 */
#define LCDIF_CTRL2_CLR_OUTSTANDING_REQS(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_OUTSTANDING_REQS_SHIFT)) & LCDIF_CTRL2_CLR_OUTSTANDING_REQS_MASK)

#define LCDIF_CTRL2_CLR_RSRVD5_MASK              (0xFF000000U)
#define LCDIF_CTRL2_CLR_RSRVD5_SHIFT             (24U)
#define LCDIF_CTRL2_CLR_RSRVD5(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_CLR_RSRVD5_SHIFT)) & LCDIF_CTRL2_CLR_RSRVD5_MASK)
/*! @} */

/*! @name CTRL2_TOG - LCDIF General Control2 Register */
/*! @{ */

#define LCDIF_CTRL2_TOG_RSRVD0_MASK              (0xFFFU)
#define LCDIF_CTRL2_TOG_RSRVD0_SHIFT             (0U)
#define LCDIF_CTRL2_TOG_RSRVD0(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_RSRVD0_SHIFT)) & LCDIF_CTRL2_TOG_RSRVD0_MASK)

#define LCDIF_CTRL2_TOG_EVEN_LINE_PATTERN_MASK   (0x7000U)
#define LCDIF_CTRL2_TOG_EVEN_LINE_PATTERN_SHIFT  (12U)
/*! EVEN_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_TOG_EVEN_LINE_PATTERN(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_EVEN_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_TOG_EVEN_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_TOG_RSRVD3_MASK              (0x8000U)
#define LCDIF_CTRL2_TOG_RSRVD3_SHIFT             (15U)
#define LCDIF_CTRL2_TOG_RSRVD3(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_RSRVD3_SHIFT)) & LCDIF_CTRL2_TOG_RSRVD3_MASK)

#define LCDIF_CTRL2_TOG_ODD_LINE_PATTERN_MASK    (0x70000U)
#define LCDIF_CTRL2_TOG_ODD_LINE_PATTERN_SHIFT   (16U)
/*! ODD_LINE_PATTERN
 *  0b000..RGB
 *  0b001..RBG
 *  0b010..GBR
 *  0b011..GRB
 *  0b100..BRG
 *  0b101..BGR
 */
#define LCDIF_CTRL2_TOG_ODD_LINE_PATTERN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_ODD_LINE_PATTERN_SHIFT)) & LCDIF_CTRL2_TOG_ODD_LINE_PATTERN_MASK)

#define LCDIF_CTRL2_TOG_RSRVD4_MASK              (0x80000U)
#define LCDIF_CTRL2_TOG_RSRVD4_SHIFT             (19U)
#define LCDIF_CTRL2_TOG_RSRVD4(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_RSRVD4_SHIFT)) & LCDIF_CTRL2_TOG_RSRVD4_MASK)

#define LCDIF_CTRL2_TOG_BURST_LEN_8_MASK         (0x100000U)
#define LCDIF_CTRL2_TOG_BURST_LEN_8_SHIFT        (20U)
#define LCDIF_CTRL2_TOG_BURST_LEN_8(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_BURST_LEN_8_SHIFT)) & LCDIF_CTRL2_TOG_BURST_LEN_8_MASK)

#define LCDIF_CTRL2_TOG_OUTSTANDING_REQS_MASK    (0xE00000U)
#define LCDIF_CTRL2_TOG_OUTSTANDING_REQS_SHIFT   (21U)
/*! OUTSTANDING_REQS
 *  0b000..REQ_1
 *  0b001..REQ_2
 *  0b010..REQ_4
 *  0b011..REQ_8
 *  0b100..REQ_16
 */
#define LCDIF_CTRL2_TOG_OUTSTANDING_REQS(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_OUTSTANDING_REQS_SHIFT)) & LCDIF_CTRL2_TOG_OUTSTANDING_REQS_MASK)

#define LCDIF_CTRL2_TOG_RSRVD5_MASK              (0xFF000000U)
#define LCDIF_CTRL2_TOG_RSRVD5_SHIFT             (24U)
#define LCDIF_CTRL2_TOG_RSRVD5(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_CTRL2_TOG_RSRVD5_SHIFT)) & LCDIF_CTRL2_TOG_RSRVD5_MASK)
/*! @} */

/*! @name TRANSFER_COUNT - LCDIF Horizontal and Vertical Valid Data Count Register */
/*! @{ */

#define LCDIF_TRANSFER_COUNT_H_COUNT_MASK        (0xFFFFU)
#define LCDIF_TRANSFER_COUNT_H_COUNT_SHIFT       (0U)
#define LCDIF_TRANSFER_COUNT_H_COUNT(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_TRANSFER_COUNT_H_COUNT_SHIFT)) & LCDIF_TRANSFER_COUNT_H_COUNT_MASK)

#define LCDIF_TRANSFER_COUNT_V_COUNT_MASK        (0xFFFF0000U)
#define LCDIF_TRANSFER_COUNT_V_COUNT_SHIFT       (16U)
#define LCDIF_TRANSFER_COUNT_V_COUNT(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_TRANSFER_COUNT_V_COUNT_SHIFT)) & LCDIF_TRANSFER_COUNT_V_COUNT_MASK)
/*! @} */

/*! @name CUR_BUF - LCD Interface Current Buffer Address Register */
/*! @{ */

#define LCDIF_CUR_BUF_ADDR_MASK                  (0xFFFFFFFFU)
#define LCDIF_CUR_BUF_ADDR_SHIFT                 (0U)
#define LCDIF_CUR_BUF_ADDR(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_CUR_BUF_ADDR_SHIFT)) & LCDIF_CUR_BUF_ADDR_MASK)
/*! @} */

/*! @name NEXT_BUF - LCD Interface Next Buffer Address Register */
/*! @{ */

#define LCDIF_NEXT_BUF_ADDR_MASK                 (0xFFFFFFFFU)
#define LCDIF_NEXT_BUF_ADDR_SHIFT                (0U)
#define LCDIF_NEXT_BUF_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << LCDIF_NEXT_BUF_ADDR_SHIFT)) & LCDIF_NEXT_BUF_ADDR_MASK)
/*! @} */

/*! @name VDCTRL0 - LCDIF VSYNC Mode and Dotclk Mode Control Register0 */
/*! @{ */

#define LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_MASK     (0x3FFFFU)
#define LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_SHIFT    (0U)
#define LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_SHIFT)) & LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_MASK)

#define LCDIF_VDCTRL0_HALF_LINE_MODE_MASK        (0x40000U)
#define LCDIF_VDCTRL0_HALF_LINE_MODE_SHIFT       (18U)
#define LCDIF_VDCTRL0_HALF_LINE_MODE(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_HALF_LINE_MODE_SHIFT)) & LCDIF_VDCTRL0_HALF_LINE_MODE_MASK)

#define LCDIF_VDCTRL0_HALF_LINE_MASK             (0x80000U)
#define LCDIF_VDCTRL0_HALF_LINE_SHIFT            (19U)
#define LCDIF_VDCTRL0_HALF_LINE(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_HALF_LINE_SHIFT)) & LCDIF_VDCTRL0_HALF_LINE_MASK)

#define LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_UNIT_MASK (0x100000U)
#define LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_UNIT_SHIFT (20U)
#define LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_UNIT(x)  (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_UNIT_SHIFT)) & LCDIF_VDCTRL0_VSYNC_PULSE_WIDTH_UNIT_MASK)

#define LCDIF_VDCTRL0_VSYNC_PERIOD_UNIT_MASK     (0x200000U)
#define LCDIF_VDCTRL0_VSYNC_PERIOD_UNIT_SHIFT    (21U)
#define LCDIF_VDCTRL0_VSYNC_PERIOD_UNIT(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_VSYNC_PERIOD_UNIT_SHIFT)) & LCDIF_VDCTRL0_VSYNC_PERIOD_UNIT_MASK)

#define LCDIF_VDCTRL0_RSRVD1_MASK                (0xC00000U)
#define LCDIF_VDCTRL0_RSRVD1_SHIFT               (22U)
#define LCDIF_VDCTRL0_RSRVD1(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_RSRVD1_SHIFT)) & LCDIF_VDCTRL0_RSRVD1_MASK)

#define LCDIF_VDCTRL0_ENABLE_POL_MASK            (0x1000000U)
#define LCDIF_VDCTRL0_ENABLE_POL_SHIFT           (24U)
#define LCDIF_VDCTRL0_ENABLE_POL(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_ENABLE_POL_SHIFT)) & LCDIF_VDCTRL0_ENABLE_POL_MASK)

#define LCDIF_VDCTRL0_DOTCLK_POL_MASK            (0x2000000U)
#define LCDIF_VDCTRL0_DOTCLK_POL_SHIFT           (25U)
#define LCDIF_VDCTRL0_DOTCLK_POL(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_DOTCLK_POL_SHIFT)) & LCDIF_VDCTRL0_DOTCLK_POL_MASK)

#define LCDIF_VDCTRL0_HSYNC_POL_MASK             (0x4000000U)
#define LCDIF_VDCTRL0_HSYNC_POL_SHIFT            (26U)
#define LCDIF_VDCTRL0_HSYNC_POL(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_HSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_HSYNC_POL_MASK)

#define LCDIF_VDCTRL0_VSYNC_POL_MASK             (0x8000000U)
#define LCDIF_VDCTRL0_VSYNC_POL_SHIFT            (27U)
#define LCDIF_VDCTRL0_VSYNC_POL(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_VSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_VSYNC_POL_MASK)

#define LCDIF_VDCTRL0_ENABLE_PRESENT_MASK        (0x10000000U)
#define LCDIF_VDCTRL0_ENABLE_PRESENT_SHIFT       (28U)
#define LCDIF_VDCTRL0_ENABLE_PRESENT(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_ENABLE_PRESENT_SHIFT)) & LCDIF_VDCTRL0_ENABLE_PRESENT_MASK)

#define LCDIF_VDCTRL0_VSYNC_OEB_MASK             (0x20000000U)
#define LCDIF_VDCTRL0_VSYNC_OEB_SHIFT            (29U)
/*! VSYNC_OEB
 *  0b0..The VSYNC pin is in the output mode and the VSYNC signal has to be generated by the LCDIF block.
 *  0b1..The VSYNC pin is in the input mode and the LCD controller sends the VSYNC signal to the block.
 */
#define LCDIF_VDCTRL0_VSYNC_OEB(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_VSYNC_OEB_SHIFT)) & LCDIF_VDCTRL0_VSYNC_OEB_MASK)

#define LCDIF_VDCTRL0_RSRVD2_MASK                (0xC0000000U)
#define LCDIF_VDCTRL0_RSRVD2_SHIFT               (30U)
#define LCDIF_VDCTRL0_RSRVD2(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_RSRVD2_SHIFT)) & LCDIF_VDCTRL0_RSRVD2_MASK)
/*! @} */

/*! @name VDCTRL0_SET - LCDIF VSYNC Mode and Dotclk Mode Control Register0 */
/*! @{ */

#define LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_MASK (0x3FFFFU)
#define LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_SHIFT (0U)
#define LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_SHIFT)) & LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_MASK)

#define LCDIF_VDCTRL0_SET_HALF_LINE_MODE_MASK    (0x40000U)
#define LCDIF_VDCTRL0_SET_HALF_LINE_MODE_SHIFT   (18U)
#define LCDIF_VDCTRL0_SET_HALF_LINE_MODE(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_HALF_LINE_MODE_SHIFT)) & LCDIF_VDCTRL0_SET_HALF_LINE_MODE_MASK)

#define LCDIF_VDCTRL0_SET_HALF_LINE_MASK         (0x80000U)
#define LCDIF_VDCTRL0_SET_HALF_LINE_SHIFT        (19U)
#define LCDIF_VDCTRL0_SET_HALF_LINE(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_HALF_LINE_SHIFT)) & LCDIF_VDCTRL0_SET_HALF_LINE_MASK)

#define LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_UNIT_MASK (0x100000U)
#define LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_UNIT_SHIFT (20U)
#define LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_UNIT(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_UNIT_SHIFT)) & LCDIF_VDCTRL0_SET_VSYNC_PULSE_WIDTH_UNIT_MASK)

#define LCDIF_VDCTRL0_SET_VSYNC_PERIOD_UNIT_MASK (0x200000U)
#define LCDIF_VDCTRL0_SET_VSYNC_PERIOD_UNIT_SHIFT (21U)
#define LCDIF_VDCTRL0_SET_VSYNC_PERIOD_UNIT(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_VSYNC_PERIOD_UNIT_SHIFT)) & LCDIF_VDCTRL0_SET_VSYNC_PERIOD_UNIT_MASK)

#define LCDIF_VDCTRL0_SET_RSRVD1_MASK            (0xC00000U)
#define LCDIF_VDCTRL0_SET_RSRVD1_SHIFT           (22U)
#define LCDIF_VDCTRL0_SET_RSRVD1(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_RSRVD1_SHIFT)) & LCDIF_VDCTRL0_SET_RSRVD1_MASK)

#define LCDIF_VDCTRL0_SET_ENABLE_POL_MASK        (0x1000000U)
#define LCDIF_VDCTRL0_SET_ENABLE_POL_SHIFT       (24U)
#define LCDIF_VDCTRL0_SET_ENABLE_POL(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_ENABLE_POL_SHIFT)) & LCDIF_VDCTRL0_SET_ENABLE_POL_MASK)

#define LCDIF_VDCTRL0_SET_DOTCLK_POL_MASK        (0x2000000U)
#define LCDIF_VDCTRL0_SET_DOTCLK_POL_SHIFT       (25U)
#define LCDIF_VDCTRL0_SET_DOTCLK_POL(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_DOTCLK_POL_SHIFT)) & LCDIF_VDCTRL0_SET_DOTCLK_POL_MASK)

#define LCDIF_VDCTRL0_SET_HSYNC_POL_MASK         (0x4000000U)
#define LCDIF_VDCTRL0_SET_HSYNC_POL_SHIFT        (26U)
#define LCDIF_VDCTRL0_SET_HSYNC_POL(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_HSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_SET_HSYNC_POL_MASK)

#define LCDIF_VDCTRL0_SET_VSYNC_POL_MASK         (0x8000000U)
#define LCDIF_VDCTRL0_SET_VSYNC_POL_SHIFT        (27U)
#define LCDIF_VDCTRL0_SET_VSYNC_POL(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_VSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_SET_VSYNC_POL_MASK)

#define LCDIF_VDCTRL0_SET_ENABLE_PRESENT_MASK    (0x10000000U)
#define LCDIF_VDCTRL0_SET_ENABLE_PRESENT_SHIFT   (28U)
#define LCDIF_VDCTRL0_SET_ENABLE_PRESENT(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_ENABLE_PRESENT_SHIFT)) & LCDIF_VDCTRL0_SET_ENABLE_PRESENT_MASK)

#define LCDIF_VDCTRL0_SET_VSYNC_OEB_MASK         (0x20000000U)
#define LCDIF_VDCTRL0_SET_VSYNC_OEB_SHIFT        (29U)
/*! VSYNC_OEB
 *  0b0..The VSYNC pin is in the output mode and the VSYNC signal has to be generated by the LCDIF block.
 *  0b1..The VSYNC pin is in the input mode and the LCD controller sends the VSYNC signal to the block.
 */
#define LCDIF_VDCTRL0_SET_VSYNC_OEB(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_VSYNC_OEB_SHIFT)) & LCDIF_VDCTRL0_SET_VSYNC_OEB_MASK)

#define LCDIF_VDCTRL0_SET_RSRVD2_MASK            (0xC0000000U)
#define LCDIF_VDCTRL0_SET_RSRVD2_SHIFT           (30U)
#define LCDIF_VDCTRL0_SET_RSRVD2(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_SET_RSRVD2_SHIFT)) & LCDIF_VDCTRL0_SET_RSRVD2_MASK)
/*! @} */

/*! @name VDCTRL0_CLR - LCDIF VSYNC Mode and Dotclk Mode Control Register0 */
/*! @{ */

#define LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_MASK (0x3FFFFU)
#define LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_SHIFT (0U)
#define LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_SHIFT)) & LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_MASK)

#define LCDIF_VDCTRL0_CLR_HALF_LINE_MODE_MASK    (0x40000U)
#define LCDIF_VDCTRL0_CLR_HALF_LINE_MODE_SHIFT   (18U)
#define LCDIF_VDCTRL0_CLR_HALF_LINE_MODE(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_HALF_LINE_MODE_SHIFT)) & LCDIF_VDCTRL0_CLR_HALF_LINE_MODE_MASK)

#define LCDIF_VDCTRL0_CLR_HALF_LINE_MASK         (0x80000U)
#define LCDIF_VDCTRL0_CLR_HALF_LINE_SHIFT        (19U)
#define LCDIF_VDCTRL0_CLR_HALF_LINE(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_HALF_LINE_SHIFT)) & LCDIF_VDCTRL0_CLR_HALF_LINE_MASK)

#define LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_UNIT_MASK (0x100000U)
#define LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_UNIT_SHIFT (20U)
#define LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_UNIT(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_UNIT_SHIFT)) & LCDIF_VDCTRL0_CLR_VSYNC_PULSE_WIDTH_UNIT_MASK)

#define LCDIF_VDCTRL0_CLR_VSYNC_PERIOD_UNIT_MASK (0x200000U)
#define LCDIF_VDCTRL0_CLR_VSYNC_PERIOD_UNIT_SHIFT (21U)
#define LCDIF_VDCTRL0_CLR_VSYNC_PERIOD_UNIT(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_VSYNC_PERIOD_UNIT_SHIFT)) & LCDIF_VDCTRL0_CLR_VSYNC_PERIOD_UNIT_MASK)

#define LCDIF_VDCTRL0_CLR_RSRVD1_MASK            (0xC00000U)
#define LCDIF_VDCTRL0_CLR_RSRVD1_SHIFT           (22U)
#define LCDIF_VDCTRL0_CLR_RSRVD1(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_RSRVD1_SHIFT)) & LCDIF_VDCTRL0_CLR_RSRVD1_MASK)

#define LCDIF_VDCTRL0_CLR_ENABLE_POL_MASK        (0x1000000U)
#define LCDIF_VDCTRL0_CLR_ENABLE_POL_SHIFT       (24U)
#define LCDIF_VDCTRL0_CLR_ENABLE_POL(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_ENABLE_POL_SHIFT)) & LCDIF_VDCTRL0_CLR_ENABLE_POL_MASK)

#define LCDIF_VDCTRL0_CLR_DOTCLK_POL_MASK        (0x2000000U)
#define LCDIF_VDCTRL0_CLR_DOTCLK_POL_SHIFT       (25U)
#define LCDIF_VDCTRL0_CLR_DOTCLK_POL(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_DOTCLK_POL_SHIFT)) & LCDIF_VDCTRL0_CLR_DOTCLK_POL_MASK)

#define LCDIF_VDCTRL0_CLR_HSYNC_POL_MASK         (0x4000000U)
#define LCDIF_VDCTRL0_CLR_HSYNC_POL_SHIFT        (26U)
#define LCDIF_VDCTRL0_CLR_HSYNC_POL(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_HSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_CLR_HSYNC_POL_MASK)

#define LCDIF_VDCTRL0_CLR_VSYNC_POL_MASK         (0x8000000U)
#define LCDIF_VDCTRL0_CLR_VSYNC_POL_SHIFT        (27U)
#define LCDIF_VDCTRL0_CLR_VSYNC_POL(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_VSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_CLR_VSYNC_POL_MASK)

#define LCDIF_VDCTRL0_CLR_ENABLE_PRESENT_MASK    (0x10000000U)
#define LCDIF_VDCTRL0_CLR_ENABLE_PRESENT_SHIFT   (28U)
#define LCDIF_VDCTRL0_CLR_ENABLE_PRESENT(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_ENABLE_PRESENT_SHIFT)) & LCDIF_VDCTRL0_CLR_ENABLE_PRESENT_MASK)

#define LCDIF_VDCTRL0_CLR_VSYNC_OEB_MASK         (0x20000000U)
#define LCDIF_VDCTRL0_CLR_VSYNC_OEB_SHIFT        (29U)
/*! VSYNC_OEB
 *  0b0..The VSYNC pin is in the output mode and the VSYNC signal has to be generated by the LCDIF block.
 *  0b1..The VSYNC pin is in the input mode and the LCD controller sends the VSYNC signal to the block.
 */
#define LCDIF_VDCTRL0_CLR_VSYNC_OEB(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_VSYNC_OEB_SHIFT)) & LCDIF_VDCTRL0_CLR_VSYNC_OEB_MASK)

#define LCDIF_VDCTRL0_CLR_RSRVD2_MASK            (0xC0000000U)
#define LCDIF_VDCTRL0_CLR_RSRVD2_SHIFT           (30U)
#define LCDIF_VDCTRL0_CLR_RSRVD2(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_CLR_RSRVD2_SHIFT)) & LCDIF_VDCTRL0_CLR_RSRVD2_MASK)
/*! @} */

/*! @name VDCTRL0_TOG - LCDIF VSYNC Mode and Dotclk Mode Control Register0 */
/*! @{ */

#define LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_MASK (0x3FFFFU)
#define LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_SHIFT (0U)
#define LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_SHIFT)) & LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_MASK)

#define LCDIF_VDCTRL0_TOG_HALF_LINE_MODE_MASK    (0x40000U)
#define LCDIF_VDCTRL0_TOG_HALF_LINE_MODE_SHIFT   (18U)
#define LCDIF_VDCTRL0_TOG_HALF_LINE_MODE(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_HALF_LINE_MODE_SHIFT)) & LCDIF_VDCTRL0_TOG_HALF_LINE_MODE_MASK)

#define LCDIF_VDCTRL0_TOG_HALF_LINE_MASK         (0x80000U)
#define LCDIF_VDCTRL0_TOG_HALF_LINE_SHIFT        (19U)
#define LCDIF_VDCTRL0_TOG_HALF_LINE(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_HALF_LINE_SHIFT)) & LCDIF_VDCTRL0_TOG_HALF_LINE_MASK)

#define LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_UNIT_MASK (0x100000U)
#define LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_UNIT_SHIFT (20U)
#define LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_UNIT(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_UNIT_SHIFT)) & LCDIF_VDCTRL0_TOG_VSYNC_PULSE_WIDTH_UNIT_MASK)

#define LCDIF_VDCTRL0_TOG_VSYNC_PERIOD_UNIT_MASK (0x200000U)
#define LCDIF_VDCTRL0_TOG_VSYNC_PERIOD_UNIT_SHIFT (21U)
#define LCDIF_VDCTRL0_TOG_VSYNC_PERIOD_UNIT(x)   (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_VSYNC_PERIOD_UNIT_SHIFT)) & LCDIF_VDCTRL0_TOG_VSYNC_PERIOD_UNIT_MASK)

#define LCDIF_VDCTRL0_TOG_RSRVD1_MASK            (0xC00000U)
#define LCDIF_VDCTRL0_TOG_RSRVD1_SHIFT           (22U)
#define LCDIF_VDCTRL0_TOG_RSRVD1(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_RSRVD1_SHIFT)) & LCDIF_VDCTRL0_TOG_RSRVD1_MASK)

#define LCDIF_VDCTRL0_TOG_ENABLE_POL_MASK        (0x1000000U)
#define LCDIF_VDCTRL0_TOG_ENABLE_POL_SHIFT       (24U)
#define LCDIF_VDCTRL0_TOG_ENABLE_POL(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_ENABLE_POL_SHIFT)) & LCDIF_VDCTRL0_TOG_ENABLE_POL_MASK)

#define LCDIF_VDCTRL0_TOG_DOTCLK_POL_MASK        (0x2000000U)
#define LCDIF_VDCTRL0_TOG_DOTCLK_POL_SHIFT       (25U)
#define LCDIF_VDCTRL0_TOG_DOTCLK_POL(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_DOTCLK_POL_SHIFT)) & LCDIF_VDCTRL0_TOG_DOTCLK_POL_MASK)

#define LCDIF_VDCTRL0_TOG_HSYNC_POL_MASK         (0x4000000U)
#define LCDIF_VDCTRL0_TOG_HSYNC_POL_SHIFT        (26U)
#define LCDIF_VDCTRL0_TOG_HSYNC_POL(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_HSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_TOG_HSYNC_POL_MASK)

#define LCDIF_VDCTRL0_TOG_VSYNC_POL_MASK         (0x8000000U)
#define LCDIF_VDCTRL0_TOG_VSYNC_POL_SHIFT        (27U)
#define LCDIF_VDCTRL0_TOG_VSYNC_POL(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_VSYNC_POL_SHIFT)) & LCDIF_VDCTRL0_TOG_VSYNC_POL_MASK)

#define LCDIF_VDCTRL0_TOG_ENABLE_PRESENT_MASK    (0x10000000U)
#define LCDIF_VDCTRL0_TOG_ENABLE_PRESENT_SHIFT   (28U)
#define LCDIF_VDCTRL0_TOG_ENABLE_PRESENT(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_ENABLE_PRESENT_SHIFT)) & LCDIF_VDCTRL0_TOG_ENABLE_PRESENT_MASK)

#define LCDIF_VDCTRL0_TOG_VSYNC_OEB_MASK         (0x20000000U)
#define LCDIF_VDCTRL0_TOG_VSYNC_OEB_SHIFT        (29U)
/*! VSYNC_OEB
 *  0b0..The VSYNC pin is in the output mode and the VSYNC signal has to be generated by the LCDIF block.
 *  0b1..The VSYNC pin is in the input mode and the LCD controller sends the VSYNC signal to the block.
 */
#define LCDIF_VDCTRL0_TOG_VSYNC_OEB(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_VSYNC_OEB_SHIFT)) & LCDIF_VDCTRL0_TOG_VSYNC_OEB_MASK)

#define LCDIF_VDCTRL0_TOG_RSRVD2_MASK            (0xC0000000U)
#define LCDIF_VDCTRL0_TOG_RSRVD2_SHIFT           (30U)
#define LCDIF_VDCTRL0_TOG_RSRVD2(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL0_TOG_RSRVD2_SHIFT)) & LCDIF_VDCTRL0_TOG_RSRVD2_MASK)
/*! @} */

/*! @name VDCTRL1 - LCDIF VSYNC Mode and Dotclk Mode Control Register1 */
/*! @{ */

#define LCDIF_VDCTRL1_VSYNC_PERIOD_MASK          (0xFFFFFFFFU)
#define LCDIF_VDCTRL1_VSYNC_PERIOD_SHIFT         (0U)
#define LCDIF_VDCTRL1_VSYNC_PERIOD(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL1_VSYNC_PERIOD_SHIFT)) & LCDIF_VDCTRL1_VSYNC_PERIOD_MASK)
/*! @} */

/*! @name VDCTRL2 - LCDIF VSYNC Mode and Dotclk Mode Control Register2 */
/*! @{ */

#define LCDIF_VDCTRL2_HSYNC_PERIOD_MASK          (0x3FFFFU)
#define LCDIF_VDCTRL2_HSYNC_PERIOD_SHIFT         (0U)
#define LCDIF_VDCTRL2_HSYNC_PERIOD(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL2_HSYNC_PERIOD_SHIFT)) & LCDIF_VDCTRL2_HSYNC_PERIOD_MASK)

#define LCDIF_VDCTRL2_HSYNC_PULSE_WIDTH_MASK     (0xFFFC0000U)
#define LCDIF_VDCTRL2_HSYNC_PULSE_WIDTH_SHIFT    (18U)
#define LCDIF_VDCTRL2_HSYNC_PULSE_WIDTH(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL2_HSYNC_PULSE_WIDTH_SHIFT)) & LCDIF_VDCTRL2_HSYNC_PULSE_WIDTH_MASK)
/*! @} */

/*! @name VDCTRL3 - LCDIF VSYNC Mode and Dotclk Mode Control Register3 */
/*! @{ */

#define LCDIF_VDCTRL3_VERTICAL_WAIT_CNT_MASK     (0xFFFFU)
#define LCDIF_VDCTRL3_VERTICAL_WAIT_CNT_SHIFT    (0U)
#define LCDIF_VDCTRL3_VERTICAL_WAIT_CNT(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL3_VERTICAL_WAIT_CNT_SHIFT)) & LCDIF_VDCTRL3_VERTICAL_WAIT_CNT_MASK)

#define LCDIF_VDCTRL3_HORIZONTAL_WAIT_CNT_MASK   (0xFFF0000U)
#define LCDIF_VDCTRL3_HORIZONTAL_WAIT_CNT_SHIFT  (16U)
#define LCDIF_VDCTRL3_HORIZONTAL_WAIT_CNT(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL3_HORIZONTAL_WAIT_CNT_SHIFT)) & LCDIF_VDCTRL3_HORIZONTAL_WAIT_CNT_MASK)

#define LCDIF_VDCTRL3_VSYNC_ONLY_MASK            (0x10000000U)
#define LCDIF_VDCTRL3_VSYNC_ONLY_SHIFT           (28U)
#define LCDIF_VDCTRL3_VSYNC_ONLY(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL3_VSYNC_ONLY_SHIFT)) & LCDIF_VDCTRL3_VSYNC_ONLY_MASK)

#define LCDIF_VDCTRL3_MUX_SYNC_SIGNALS_MASK      (0x20000000U)
#define LCDIF_VDCTRL3_MUX_SYNC_SIGNALS_SHIFT     (29U)
#define LCDIF_VDCTRL3_MUX_SYNC_SIGNALS(x)        (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL3_MUX_SYNC_SIGNALS_SHIFT)) & LCDIF_VDCTRL3_MUX_SYNC_SIGNALS_MASK)

#define LCDIF_VDCTRL3_RSRVD0_MASK                (0xC0000000U)
#define LCDIF_VDCTRL3_RSRVD0_SHIFT               (30U)
#define LCDIF_VDCTRL3_RSRVD0(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL3_RSRVD0_SHIFT)) & LCDIF_VDCTRL3_RSRVD0_MASK)
/*! @} */

/*! @name VDCTRL4 - LCDIF VSYNC Mode and Dotclk Mode Control Register4 */
/*! @{ */

#define LCDIF_VDCTRL4_DOTCLK_H_VALID_DATA_CNT_MASK (0x3FFFFU)
#define LCDIF_VDCTRL4_DOTCLK_H_VALID_DATA_CNT_SHIFT (0U)
#define LCDIF_VDCTRL4_DOTCLK_H_VALID_DATA_CNT(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL4_DOTCLK_H_VALID_DATA_CNT_SHIFT)) & LCDIF_VDCTRL4_DOTCLK_H_VALID_DATA_CNT_MASK)

#define LCDIF_VDCTRL4_SYNC_SIGNALS_ON_MASK       (0x40000U)
#define LCDIF_VDCTRL4_SYNC_SIGNALS_ON_SHIFT      (18U)
#define LCDIF_VDCTRL4_SYNC_SIGNALS_ON(x)         (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL4_SYNC_SIGNALS_ON_SHIFT)) & LCDIF_VDCTRL4_SYNC_SIGNALS_ON_MASK)

#define LCDIF_VDCTRL4_RSRVD0_MASK                (0x1FF80000U)
#define LCDIF_VDCTRL4_RSRVD0_SHIFT               (19U)
#define LCDIF_VDCTRL4_RSRVD0(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL4_RSRVD0_SHIFT)) & LCDIF_VDCTRL4_RSRVD0_MASK)

#define LCDIF_VDCTRL4_DOTCLK_DLY_SEL_MASK        (0xE0000000U)
#define LCDIF_VDCTRL4_DOTCLK_DLY_SEL_SHIFT       (29U)
#define LCDIF_VDCTRL4_DOTCLK_DLY_SEL(x)          (((uint32_t)(((uint32_t)(x)) << LCDIF_VDCTRL4_DOTCLK_DLY_SEL_SHIFT)) & LCDIF_VDCTRL4_DOTCLK_DLY_SEL_MASK)
/*! @} */

/*! @name BM_ERROR_STAT - Bus Master Error Status Register */
/*! @{ */

#define LCDIF_BM_ERROR_STAT_ADDR_MASK            (0xFFFFFFFFU)
#define LCDIF_BM_ERROR_STAT_ADDR_SHIFT           (0U)
#define LCDIF_BM_ERROR_STAT_ADDR(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_BM_ERROR_STAT_ADDR_SHIFT)) & LCDIF_BM_ERROR_STAT_ADDR_MASK)
/*! @} */

/*! @name CRC_STAT - CRC Status Register */
/*! @{ */

#define LCDIF_CRC_STAT_CRC_VALUE_MASK            (0xFFFFFFFFU)
#define LCDIF_CRC_STAT_CRC_VALUE_SHIFT           (0U)
#define LCDIF_CRC_STAT_CRC_VALUE(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_CRC_STAT_CRC_VALUE_SHIFT)) & LCDIF_CRC_STAT_CRC_VALUE_MASK)
/*! @} */

/*! @name STAT - LCD Interface Status Register */
/*! @{ */

#define LCDIF_STAT_LFIFO_COUNT_MASK              (0x1FFU)
#define LCDIF_STAT_LFIFO_COUNT_SHIFT             (0U)
#define LCDIF_STAT_LFIFO_COUNT(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_LFIFO_COUNT_SHIFT)) & LCDIF_STAT_LFIFO_COUNT_MASK)

#define LCDIF_STAT_RSRVD0_MASK                   (0x1FFFE00U)
#define LCDIF_STAT_RSRVD0_SHIFT                  (9U)
#define LCDIF_STAT_RSRVD0(x)                     (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_RSRVD0_SHIFT)) & LCDIF_STAT_RSRVD0_MASK)

#define LCDIF_STAT_TXFIFO_EMPTY_MASK             (0x4000000U)
#define LCDIF_STAT_TXFIFO_EMPTY_SHIFT            (26U)
#define LCDIF_STAT_TXFIFO_EMPTY(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_TXFIFO_EMPTY_SHIFT)) & LCDIF_STAT_TXFIFO_EMPTY_MASK)

#define LCDIF_STAT_TXFIFO_FULL_MASK              (0x8000000U)
#define LCDIF_STAT_TXFIFO_FULL_SHIFT             (27U)
#define LCDIF_STAT_TXFIFO_FULL(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_TXFIFO_FULL_SHIFT)) & LCDIF_STAT_TXFIFO_FULL_MASK)

#define LCDIF_STAT_LFIFO_EMPTY_MASK              (0x10000000U)
#define LCDIF_STAT_LFIFO_EMPTY_SHIFT             (28U)
#define LCDIF_STAT_LFIFO_EMPTY(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_LFIFO_EMPTY_SHIFT)) & LCDIF_STAT_LFIFO_EMPTY_MASK)

#define LCDIF_STAT_LFIFO_FULL_MASK               (0x20000000U)
#define LCDIF_STAT_LFIFO_FULL_SHIFT              (29U)
#define LCDIF_STAT_LFIFO_FULL(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_LFIFO_FULL_SHIFT)) & LCDIF_STAT_LFIFO_FULL_MASK)

#define LCDIF_STAT_DMA_REQ_MASK                  (0x40000000U)
#define LCDIF_STAT_DMA_REQ_SHIFT                 (30U)
#define LCDIF_STAT_DMA_REQ(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_DMA_REQ_SHIFT)) & LCDIF_STAT_DMA_REQ_MASK)

#define LCDIF_STAT_PRESENT_MASK                  (0x80000000U)
#define LCDIF_STAT_PRESENT_SHIFT                 (31U)
#define LCDIF_STAT_PRESENT(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_STAT_PRESENT_SHIFT)) & LCDIF_STAT_PRESENT_MASK)
/*! @} */

/*! @name THRES - LCDIF Threshold Register */
/*! @{ */

#define LCDIF_THRES_RSRVD_MASK                   (0x1FFU)
#define LCDIF_THRES_RSRVD_SHIFT                  (0U)
#define LCDIF_THRES_RSRVD(x)                     (((uint32_t)(((uint32_t)(x)) << LCDIF_THRES_RSRVD_SHIFT)) & LCDIF_THRES_RSRVD_MASK)

#define LCDIF_THRES_RSRVD1_MASK                  (0xFE00U)
#define LCDIF_THRES_RSRVD1_SHIFT                 (9U)
#define LCDIF_THRES_RSRVD1(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_THRES_RSRVD1_SHIFT)) & LCDIF_THRES_RSRVD1_MASK)

#define LCDIF_THRES_FASTCLOCK_MASK               (0x1FF0000U)
#define LCDIF_THRES_FASTCLOCK_SHIFT              (16U)
#define LCDIF_THRES_FASTCLOCK(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_THRES_FASTCLOCK_SHIFT)) & LCDIF_THRES_FASTCLOCK_MASK)

#define LCDIF_THRES_RSRVD2_MASK                  (0xFE000000U)
#define LCDIF_THRES_RSRVD2_SHIFT                 (25U)
#define LCDIF_THRES_RSRVD2(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_THRES_RSRVD2_SHIFT)) & LCDIF_THRES_RSRVD2_MASK)
/*! @} */

/*! @name PIGEONCTRL0 - LCDIF Pigeon Mode Control0 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL0_FD_PERIOD_MASK         (0xFFFU)
#define LCDIF_PIGEONCTRL0_FD_PERIOD_SHIFT        (0U)
#define LCDIF_PIGEONCTRL0_FD_PERIOD(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_FD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_FD_PERIOD_MASK)

#define LCDIF_PIGEONCTRL0_LD_PERIOD_MASK         (0xFFF0000U)
#define LCDIF_PIGEONCTRL0_LD_PERIOD_SHIFT        (16U)
#define LCDIF_PIGEONCTRL0_LD_PERIOD(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_LD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_LD_PERIOD_MASK)
/*! @} */

/*! @name PIGEONCTRL0_SET - LCDIF Pigeon Mode Control0 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL0_SET_FD_PERIOD_MASK     (0xFFFU)
#define LCDIF_PIGEONCTRL0_SET_FD_PERIOD_SHIFT    (0U)
#define LCDIF_PIGEONCTRL0_SET_FD_PERIOD(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_SET_FD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_SET_FD_PERIOD_MASK)

#define LCDIF_PIGEONCTRL0_SET_LD_PERIOD_MASK     (0xFFF0000U)
#define LCDIF_PIGEONCTRL0_SET_LD_PERIOD_SHIFT    (16U)
#define LCDIF_PIGEONCTRL0_SET_LD_PERIOD(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_SET_LD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_SET_LD_PERIOD_MASK)
/*! @} */

/*! @name PIGEONCTRL0_CLR - LCDIF Pigeon Mode Control0 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL0_CLR_FD_PERIOD_MASK     (0xFFFU)
#define LCDIF_PIGEONCTRL0_CLR_FD_PERIOD_SHIFT    (0U)
#define LCDIF_PIGEONCTRL0_CLR_FD_PERIOD(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_CLR_FD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_CLR_FD_PERIOD_MASK)

#define LCDIF_PIGEONCTRL0_CLR_LD_PERIOD_MASK     (0xFFF0000U)
#define LCDIF_PIGEONCTRL0_CLR_LD_PERIOD_SHIFT    (16U)
#define LCDIF_PIGEONCTRL0_CLR_LD_PERIOD(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_CLR_LD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_CLR_LD_PERIOD_MASK)
/*! @} */

/*! @name PIGEONCTRL0_TOG - LCDIF Pigeon Mode Control0 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL0_TOG_FD_PERIOD_MASK     (0xFFFU)
#define LCDIF_PIGEONCTRL0_TOG_FD_PERIOD_SHIFT    (0U)
#define LCDIF_PIGEONCTRL0_TOG_FD_PERIOD(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_TOG_FD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_TOG_FD_PERIOD_MASK)

#define LCDIF_PIGEONCTRL0_TOG_LD_PERIOD_MASK     (0xFFF0000U)
#define LCDIF_PIGEONCTRL0_TOG_LD_PERIOD_SHIFT    (16U)
#define LCDIF_PIGEONCTRL0_TOG_LD_PERIOD(x)       (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL0_TOG_LD_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL0_TOG_LD_PERIOD_MASK)
/*! @} */

/*! @name PIGEONCTRL1 - LCDIF Pigeon Mode Control1 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL1_FRAME_CNT_PERIOD_MASK  (0xFFFU)
#define LCDIF_PIGEONCTRL1_FRAME_CNT_PERIOD_SHIFT (0U)
#define LCDIF_PIGEONCTRL1_FRAME_CNT_PERIOD(x)    (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_FRAME_CNT_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL1_FRAME_CNT_PERIOD_MASK)

#define LCDIF_PIGEONCTRL1_FRAME_CNT_CYCLES_MASK  (0xFFF0000U)
#define LCDIF_PIGEONCTRL1_FRAME_CNT_CYCLES_SHIFT (16U)
#define LCDIF_PIGEONCTRL1_FRAME_CNT_CYCLES(x)    (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_FRAME_CNT_CYCLES_SHIFT)) & LCDIF_PIGEONCTRL1_FRAME_CNT_CYCLES_MASK)
/*! @} */

/*! @name PIGEONCTRL1_SET - LCDIF Pigeon Mode Control1 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL1_SET_FRAME_CNT_PERIOD_MASK (0xFFFU)
#define LCDIF_PIGEONCTRL1_SET_FRAME_CNT_PERIOD_SHIFT (0U)
#define LCDIF_PIGEONCTRL1_SET_FRAME_CNT_PERIOD(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_SET_FRAME_CNT_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL1_SET_FRAME_CNT_PERIOD_MASK)

#define LCDIF_PIGEONCTRL1_SET_FRAME_CNT_CYCLES_MASK (0xFFF0000U)
#define LCDIF_PIGEONCTRL1_SET_FRAME_CNT_CYCLES_SHIFT (16U)
#define LCDIF_PIGEONCTRL1_SET_FRAME_CNT_CYCLES(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_SET_FRAME_CNT_CYCLES_SHIFT)) & LCDIF_PIGEONCTRL1_SET_FRAME_CNT_CYCLES_MASK)
/*! @} */

/*! @name PIGEONCTRL1_CLR - LCDIF Pigeon Mode Control1 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_PERIOD_MASK (0xFFFU)
#define LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_PERIOD_SHIFT (0U)
#define LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_PERIOD(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_PERIOD_MASK)

#define LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_CYCLES_MASK (0xFFF0000U)
#define LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_CYCLES_SHIFT (16U)
#define LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_CYCLES(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_CYCLES_SHIFT)) & LCDIF_PIGEONCTRL1_CLR_FRAME_CNT_CYCLES_MASK)
/*! @} */

/*! @name PIGEONCTRL1_TOG - LCDIF Pigeon Mode Control1 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_PERIOD_MASK (0xFFFU)
#define LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_PERIOD_SHIFT (0U)
#define LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_PERIOD(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_PERIOD_SHIFT)) & LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_PERIOD_MASK)

#define LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_CYCLES_MASK (0xFFF0000U)
#define LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_CYCLES_SHIFT (16U)
#define LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_CYCLES(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_CYCLES_SHIFT)) & LCDIF_PIGEONCTRL1_TOG_FRAME_CNT_CYCLES_MASK)
/*! @} */

/*! @name PIGEONCTRL2 - LCDIF Pigeon Mode Control2 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL2_PIGEON_DATA_EN_MASK    (0x1U)
#define LCDIF_PIGEONCTRL2_PIGEON_DATA_EN_SHIFT   (0U)
#define LCDIF_PIGEONCTRL2_PIGEON_DATA_EN(x)      (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_PIGEON_DATA_EN_SHIFT)) & LCDIF_PIGEONCTRL2_PIGEON_DATA_EN_MASK)

#define LCDIF_PIGEONCTRL2_PIGEON_CLK_GATE_MASK   (0x2U)
#define LCDIF_PIGEONCTRL2_PIGEON_CLK_GATE_SHIFT  (1U)
#define LCDIF_PIGEONCTRL2_PIGEON_CLK_GATE(x)     (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_PIGEON_CLK_GATE_SHIFT)) & LCDIF_PIGEONCTRL2_PIGEON_CLK_GATE_MASK)
/*! @} */

/*! @name PIGEONCTRL2_SET - LCDIF Pigeon Mode Control2 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL2_SET_PIGEON_DATA_EN_MASK (0x1U)
#define LCDIF_PIGEONCTRL2_SET_PIGEON_DATA_EN_SHIFT (0U)
#define LCDIF_PIGEONCTRL2_SET_PIGEON_DATA_EN(x)  (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_SET_PIGEON_DATA_EN_SHIFT)) & LCDIF_PIGEONCTRL2_SET_PIGEON_DATA_EN_MASK)

#define LCDIF_PIGEONCTRL2_SET_PIGEON_CLK_GATE_MASK (0x2U)
#define LCDIF_PIGEONCTRL2_SET_PIGEON_CLK_GATE_SHIFT (1U)
#define LCDIF_PIGEONCTRL2_SET_PIGEON_CLK_GATE(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_SET_PIGEON_CLK_GATE_SHIFT)) & LCDIF_PIGEONCTRL2_SET_PIGEON_CLK_GATE_MASK)
/*! @} */

/*! @name PIGEONCTRL2_CLR - LCDIF Pigeon Mode Control2 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL2_CLR_PIGEON_DATA_EN_MASK (0x1U)
#define LCDIF_PIGEONCTRL2_CLR_PIGEON_DATA_EN_SHIFT (0U)
#define LCDIF_PIGEONCTRL2_CLR_PIGEON_DATA_EN(x)  (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_CLR_PIGEON_DATA_EN_SHIFT)) & LCDIF_PIGEONCTRL2_CLR_PIGEON_DATA_EN_MASK)

#define LCDIF_PIGEONCTRL2_CLR_PIGEON_CLK_GATE_MASK (0x2U)
#define LCDIF_PIGEONCTRL2_CLR_PIGEON_CLK_GATE_SHIFT (1U)
#define LCDIF_PIGEONCTRL2_CLR_PIGEON_CLK_GATE(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_CLR_PIGEON_CLK_GATE_SHIFT)) & LCDIF_PIGEONCTRL2_CLR_PIGEON_CLK_GATE_MASK)
/*! @} */

/*! @name PIGEONCTRL2_TOG - LCDIF Pigeon Mode Control2 Register */
/*! @{ */

#define LCDIF_PIGEONCTRL2_TOG_PIGEON_DATA_EN_MASK (0x1U)
#define LCDIF_PIGEONCTRL2_TOG_PIGEON_DATA_EN_SHIFT (0U)
#define LCDIF_PIGEONCTRL2_TOG_PIGEON_DATA_EN(x)  (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_TOG_PIGEON_DATA_EN_SHIFT)) & LCDIF_PIGEONCTRL2_TOG_PIGEON_DATA_EN_MASK)

#define LCDIF_PIGEONCTRL2_TOG_PIGEON_CLK_GATE_MASK (0x2U)
#define LCDIF_PIGEONCTRL2_TOG_PIGEON_CLK_GATE_SHIFT (1U)
#define LCDIF_PIGEONCTRL2_TOG_PIGEON_CLK_GATE(x) (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEONCTRL2_TOG_PIGEON_CLK_GATE_SHIFT)) & LCDIF_PIGEONCTRL2_TOG_PIGEON_CLK_GATE_MASK)
/*! @} */

/*! @name PIGEON_0 - Panel Interface Signal Generator Register */
/*! @{ */

#define LCDIF_PIGEON_0_EN_MASK                   (0x1U)
#define LCDIF_PIGEON_0_EN_SHIFT                  (0U)
#define LCDIF_PIGEON_0_EN(x)                     (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_0_EN_SHIFT)) & LCDIF_PIGEON_0_EN_MASK)

#define LCDIF_PIGEON_0_POL_MASK                  (0x2U)
#define LCDIF_PIGEON_0_POL_SHIFT                 (1U)
/*! POL
 *  0b0..Normal Signal (Active high)
 *  0b1..Inverted signal (Active low)
 */
#define LCDIF_PIGEON_0_POL(x)                    (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_0_POL_SHIFT)) & LCDIF_PIGEON_0_POL_MASK)

#define LCDIF_PIGEON_0_INC_SEL_MASK              (0xCU)
#define LCDIF_PIGEON_0_INC_SEL_SHIFT             (2U)
/*! INC_SEL
 *  0b00..pclk
 *  0b01..Line start pulse
 *  0b10..Frame start pulse
 *  0b11..Use another signal as tick event
 */
#define LCDIF_PIGEON_0_INC_SEL(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_0_INC_SEL_SHIFT)) & LCDIF_PIGEON_0_INC_SEL_MASK)

#define LCDIF_PIGEON_0_OFFSET_MASK               (0xF0U)
#define LCDIF_PIGEON_0_OFFSET_SHIFT              (4U)
#define LCDIF_PIGEON_0_OFFSET(x)                 (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_0_OFFSET_SHIFT)) & LCDIF_PIGEON_0_OFFSET_MASK)

#define LCDIF_PIGEON_0_MASK_CNT_SEL_MASK         (0xF00U)
#define LCDIF_PIGEON_0_MASK_CNT_SEL_SHIFT        (8U)
/*! MASK_CNT_SEL
 *  0b0000..pclk counter within one hscan state
 *  0b0001..pclk cycle within one hscan state
 *  0b0010..line counter within one vscan state
 *  0b0011..line cycle within one vscan state
 *  0b0100..frame counter
 *  0b0101..frame cycle
 *  0b0110..horizontal counter (pclk counter within one line )
 *  0b0111..vertical counter (line counter within one frame)
 */
#define LCDIF_PIGEON_0_MASK_CNT_SEL(x)           (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_0_MASK_CNT_SEL_SHIFT)) & LCDIF_PIGEON_0_MASK_CNT_SEL_MASK)

#define LCDIF_PIGEON_0_MASK_CNT_MASK             (0xFFF000U)
#define LCDIF_PIGEON_0_MASK_CNT_SHIFT            (12U)
#define LCDIF_PIGEON_0_MASK_CNT(x)               (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_0_MASK_CNT_SHIFT)) & LCDIF_PIGEON_0_MASK_CNT_MASK)

#define LCDIF_PIGEON_0_STATE_MASK_MASK           (0xFF000000U)
#define LCDIF_PIGEON_0_STATE_MASK_SHIFT          (24U)
/*! STATE_MASK
 *  0b00000001..FRAME SYNC
 *  0b00000010..FRAME BEGIN
 *  0b00000100..FRAME DATA
 *  0b00001000..FRAME END
 *  0b00010000..LINE SYNC
 *  0b00100000..LINE BEGIN
 *  0b01000000..LINE DATA
 *  0b10000000..LINE END
 */
#define LCDIF_PIGEON_0_STATE_MASK(x)             (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_0_STATE_MASK_SHIFT)) & LCDIF_PIGEON_0_STATE_MASK_MASK)
/*! @} */

/* The count of LCDIF_PIGEON_0 */
#define LCDIF_PIGEON_0_COUNT                     (12U)

/*! @name PIGEON_1 - Panel Interface Signal Generator Register */
/*! @{ */

#define LCDIF_PIGEON_1_SET_CNT_MASK              (0xFFFFU)
#define LCDIF_PIGEON_1_SET_CNT_SHIFT             (0U)
/*! SET_CNT
 *  0b0000000000000000..Start as active
 */
#define LCDIF_PIGEON_1_SET_CNT(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_1_SET_CNT_SHIFT)) & LCDIF_PIGEON_1_SET_CNT_MASK)

#define LCDIF_PIGEON_1_CLR_CNT_MASK              (0xFFFF0000U)
#define LCDIF_PIGEON_1_CLR_CNT_SHIFT             (16U)
/*! CLR_CNT
 *  0b0000000000000000..Keep active until mask off
 */
#define LCDIF_PIGEON_1_CLR_CNT(x)                (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_1_CLR_CNT_SHIFT)) & LCDIF_PIGEON_1_CLR_CNT_MASK)
/*! @} */

/* The count of LCDIF_PIGEON_1 */
#define LCDIF_PIGEON_1_COUNT                     (12U)

/*! @name PIGEON_2 - Panel Interface Signal Generator Register */
/*! @{ */

#define LCDIF_PIGEON_2_SIG_LOGIC_MASK            (0xFU)
#define LCDIF_PIGEON_2_SIG_LOGIC_SHIFT           (0U)
/*! SIG_LOGIC
 *  0b0000..No logic operation
 *  0b0001..sigout = sig_another AND this_sig
 *  0b0010..sigout = sig_another OR this_sig
 *  0b0011..mask = sig_another AND other_masks
 */
#define LCDIF_PIGEON_2_SIG_LOGIC(x)              (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_2_SIG_LOGIC_SHIFT)) & LCDIF_PIGEON_2_SIG_LOGIC_MASK)

#define LCDIF_PIGEON_2_SIG_ANOTHER_MASK          (0x1F0U)
#define LCDIF_PIGEON_2_SIG_ANOTHER_SHIFT         (4U)
/*! SIG_ANOTHER
 *  0b00000..Keep active until mask off
 */
#define LCDIF_PIGEON_2_SIG_ANOTHER(x)            (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_2_SIG_ANOTHER_SHIFT)) & LCDIF_PIGEON_2_SIG_ANOTHER_MASK)

#define LCDIF_PIGEON_2_RSVD_MASK                 (0xFFFFFE00U)
#define LCDIF_PIGEON_2_RSVD_SHIFT                (9U)
#define LCDIF_PIGEON_2_RSVD(x)                   (((uint32_t)(((uint32_t)(x)) << LCDIF_PIGEON_2_RSVD_SHIFT)) & LCDIF_PIGEON_2_RSVD_MASK)
/*! @} */

/* The count of LCDIF_PIGEON_2 */
#define LCDIF_PIGEON_2_COUNT                     (12U)

/*! @name LUT_CTRL - Look Up Table Control Register */
/*! @{ */

#define LCDIF_LUT_CTRL_LUT_BYPASS_MASK           (0x1U)
#define LCDIF_LUT_CTRL_LUT_BYPASS_SHIFT          (0U)
#define LCDIF_LUT_CTRL_LUT_BYPASS(x)             (((uint32_t)(((uint32_t)(x)) << LCDIF_LUT_CTRL_LUT_BYPASS_SHIFT)) & LCDIF_LUT_CTRL_LUT_BYPASS_MASK)
/*! @} */

/*! @name LUT0_ADDR - Lookup Table 0 Index Register */
/*! @{ */

#define LCDIF_LUT0_ADDR_ADDR_MASK                (0xFFU)
#define LCDIF_LUT0_ADDR_ADDR_SHIFT               (0U)
#define LCDIF_LUT0_ADDR_ADDR(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_LUT0_ADDR_ADDR_SHIFT)) & LCDIF_LUT0_ADDR_ADDR_MASK)
/*! @} */

/*! @name LUT0_DATA - Lookup Table 0 Data Register */
/*! @{ */

#define LCDIF_LUT0_DATA_DATA_MASK                (0xFFFFFFFFU)
#define LCDIF_LUT0_DATA_DATA_SHIFT               (0U)
#define LCDIF_LUT0_DATA_DATA(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_LUT0_DATA_DATA_SHIFT)) & LCDIF_LUT0_DATA_DATA_MASK)
/*! @} */

/*! @name LUT1_ADDR - Lookup Table 1 Index Register */
/*! @{ */

#define LCDIF_LUT1_ADDR_ADDR_MASK                (0xFFU)
#define LCDIF_LUT1_ADDR_ADDR_SHIFT               (0U)
#define LCDIF_LUT1_ADDR_ADDR(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_LUT1_ADDR_ADDR_SHIFT)) & LCDIF_LUT1_ADDR_ADDR_MASK)
/*! @} */

/*! @name LUT1_DATA - Lookup Table 1 Data Register */
/*! @{ */

#define LCDIF_LUT1_DATA_DATA_MASK                (0xFFFFFFFFU)
#define LCDIF_LUT1_DATA_DATA_SHIFT               (0U)
#define LCDIF_LUT1_DATA_DATA(x)                  (((uint32_t)(((uint32_t)(x)) << LCDIF_LUT1_DATA_DATA_SHIFT)) & LCDIF_LUT1_DATA_DATA_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LCDIF_Register_Masks */


/*!
 * @}
 */ /* end of group LCDIF_Peripheral_Access_Layer */


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


#endif  /* PERI_LCDIF_H_ */

