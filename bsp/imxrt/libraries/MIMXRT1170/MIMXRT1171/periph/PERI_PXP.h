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
**         CMSIS Peripheral Access Layer for PXP
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
 * @file PERI_PXP.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for PXP
 *
 * CMSIS Peripheral Access Layer for PXP
 */

#if !defined(PERI_PXP_H_)
#define PERI_PXP_H_                              /**< Symbol preventing repeated inclusion */

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
   -- PXP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PXP_Peripheral_Access_Layer PXP Peripheral Access Layer
 * @{
 */

/** PXP - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Control Register 0, offset: 0x0 */
  __IO uint32_t CTRL_SET;                          /**< Control Register 0, offset: 0x4 */
  __IO uint32_t CTRL_CLR;                          /**< Control Register 0, offset: 0x8 */
  __IO uint32_t CTRL_TOG;                          /**< Control Register 0, offset: 0xC */
  __IO uint32_t STAT;                              /**< Status Register, offset: 0x10 */
  __IO uint32_t STAT_SET;                          /**< Status Register, offset: 0x14 */
  __IO uint32_t STAT_CLR;                          /**< Status Register, offset: 0x18 */
  __IO uint32_t STAT_TOG;                          /**< Status Register, offset: 0x1C */
  __IO uint32_t OUT_CTRL;                          /**< Output Buffer Control Register, offset: 0x20 */
  __IO uint32_t OUT_CTRL_SET;                      /**< Output Buffer Control Register, offset: 0x24 */
  __IO uint32_t OUT_CTRL_CLR;                      /**< Output Buffer Control Register, offset: 0x28 */
  __IO uint32_t OUT_CTRL_TOG;                      /**< Output Buffer Control Register, offset: 0x2C */
  __IO uint32_t OUT_BUF;                           /**< Output Frame Buffer Pointer, offset: 0x30 */
       uint8_t RESERVED_0[12];
  __IO uint32_t OUT_BUF2;                          /**< Output Frame Buffer Pointer #2, offset: 0x40 */
       uint8_t RESERVED_1[12];
  __IO uint32_t OUT_PITCH;                         /**< Output Buffer Pitch, offset: 0x50 */
       uint8_t RESERVED_2[12];
  __IO uint32_t OUT_LRC;                           /**< Output Surface Lower Right Coordinate, offset: 0x60 */
       uint8_t RESERVED_3[12];
  __IO uint32_t OUT_PS_ULC;                        /**< Processed Surface Upper Left Coordinate, offset: 0x70 */
       uint8_t RESERVED_4[12];
  __IO uint32_t OUT_PS_LRC;                        /**< Processed Surface Lower Right Coordinate, offset: 0x80 */
       uint8_t RESERVED_5[12];
  __IO uint32_t OUT_AS_ULC;                        /**< Alpha Surface Upper Left Coordinate, offset: 0x90 */
       uint8_t RESERVED_6[12];
  __IO uint32_t OUT_AS_LRC;                        /**< Alpha Surface Lower Right Coordinate, offset: 0xA0 */
       uint8_t RESERVED_7[12];
  __IO uint32_t PS_CTRL;                           /**< Processed Surface (PS) Control Register, offset: 0xB0 */
  __IO uint32_t PS_CTRL_SET;                       /**< Processed Surface (PS) Control Register, offset: 0xB4 */
  __IO uint32_t PS_CTRL_CLR;                       /**< Processed Surface (PS) Control Register, offset: 0xB8 */
  __IO uint32_t PS_CTRL_TOG;                       /**< Processed Surface (PS) Control Register, offset: 0xBC */
  __IO uint32_t PS_BUF;                            /**< PS Input Buffer Address, offset: 0xC0 */
       uint8_t RESERVED_8[12];
  __IO uint32_t PS_UBUF;                           /**< PS U/Cb or 2 Plane UV Input Buffer Address, offset: 0xD0 */
       uint8_t RESERVED_9[12];
  __IO uint32_t PS_VBUF;                           /**< PS V/Cr Input Buffer Address, offset: 0xE0 */
       uint8_t RESERVED_10[12];
  __IO uint32_t PS_PITCH;                          /**< Processed Surface Pitch, offset: 0xF0 */
       uint8_t RESERVED_11[12];
  __IO uint32_t PS_BACKGROUND;                     /**< PS Background Color, offset: 0x100 */
       uint8_t RESERVED_12[12];
  __IO uint32_t PS_SCALE;                          /**< PS Scale Factor Register, offset: 0x110 */
       uint8_t RESERVED_13[12];
  __IO uint32_t PS_OFFSET;                         /**< PS Scale Offset Register, offset: 0x120 */
       uint8_t RESERVED_14[12];
  __IO uint32_t PS_CLRKEYLOW;                      /**< PS Color Key Low, offset: 0x130 */
       uint8_t RESERVED_15[12];
  __IO uint32_t PS_CLRKEYHIGH;                     /**< PS Color Key High, offset: 0x140 */
       uint8_t RESERVED_16[12];
  __IO uint32_t AS_CTRL;                           /**< Alpha Surface Control, offset: 0x150 */
       uint8_t RESERVED_17[12];
  __IO uint32_t AS_BUF;                            /**< Alpha Surface Buffer Pointer, offset: 0x160 */
       uint8_t RESERVED_18[12];
  __IO uint32_t AS_PITCH;                          /**< Alpha Surface Pitch, offset: 0x170 */
       uint8_t RESERVED_19[12];
  __IO uint32_t AS_CLRKEYLOW;                      /**< Overlay Color Key Low, offset: 0x180 */
       uint8_t RESERVED_20[12];
  __IO uint32_t AS_CLRKEYHIGH;                     /**< Overlay Color Key High, offset: 0x190 */
       uint8_t RESERVED_21[12];
  __IO uint32_t CSC1_COEF0;                        /**< Color Space Conversion Coefficient Register 0, offset: 0x1A0 */
       uint8_t RESERVED_22[12];
  __IO uint32_t CSC1_COEF1;                        /**< Color Space Conversion Coefficient Register 1, offset: 0x1B0 */
       uint8_t RESERVED_23[12];
  __IO uint32_t CSC1_COEF2;                        /**< Color Space Conversion Coefficient Register 2, offset: 0x1C0 */
       uint8_t RESERVED_24[348];
  __IO uint32_t POWER;                             /**< PXP Power Control Register, offset: 0x320 */
       uint8_t RESERVED_25[220];
  __IO uint32_t NEXT;                              /**< Next Frame Pointer, offset: 0x400 */
       uint8_t RESERVED_26[60];
  __IO uint32_t PORTER_DUFF_CTRL;                  /**< PXP Alpha Engine A Control Register., offset: 0x440 */
} PXP_Type;

/* ----------------------------------------------------------------------------
   -- PXP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PXP_Register_Masks PXP Register Masks
 * @{
 */

/*! @name CTRL - Control Register 0 */
/*! @{ */

#define PXP_CTRL_ENABLE_MASK                     (0x1U)
#define PXP_CTRL_ENABLE_SHIFT                    (0U)
/*! ENABLE
 *  0b0..PXP is disabled
 *  0b1..PXP is enabled
 */
#define PXP_CTRL_ENABLE(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_ENABLE_SHIFT)) & PXP_CTRL_ENABLE_MASK)

#define PXP_CTRL_IRQ_ENABLE_MASK                 (0x2U)
#define PXP_CTRL_IRQ_ENABLE_SHIFT                (1U)
/*! IRQ_ENABLE
 *  0b0..PXP interrupt is disabled
 *  0b1..PXP interrupt is enabled
 */
#define PXP_CTRL_IRQ_ENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_IRQ_ENABLE_SHIFT)) & PXP_CTRL_IRQ_ENABLE_MASK)

#define PXP_CTRL_NEXT_IRQ_ENABLE_MASK            (0x4U)
#define PXP_CTRL_NEXT_IRQ_ENABLE_SHIFT           (2U)
/*! NEXT_IRQ_ENABLE
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define PXP_CTRL_NEXT_IRQ_ENABLE(x)              (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_NEXT_IRQ_ENABLE_SHIFT)) & PXP_CTRL_NEXT_IRQ_ENABLE_MASK)

#define PXP_CTRL_ENABLE_LCD_HANDSHAKE_MASK       (0x10U)
#define PXP_CTRL_ENABLE_LCD_HANDSHAKE_SHIFT      (4U)
#define PXP_CTRL_ENABLE_LCD_HANDSHAKE(x)         (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_ENABLE_LCD_HANDSHAKE_SHIFT)) & PXP_CTRL_ENABLE_LCD_HANDSHAKE_MASK)

#define PXP_CTRL_ROTATE_MASK                     (0x300U)
#define PXP_CTRL_ROTATE_SHIFT                    (8U)
/*! ROTATE
 *  0b00..ROT_0
 *  0b01..ROT_90
 *  0b10..ROT_180
 *  0b11..ROT_270
 */
#define PXP_CTRL_ROTATE(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_ROTATE_SHIFT)) & PXP_CTRL_ROTATE_MASK)

#define PXP_CTRL_HFLIP_MASK                      (0x400U)
#define PXP_CTRL_HFLIP_SHIFT                     (10U)
/*! HFLIP
 *  0b0..Horizontal Flip is disabled
 *  0b1..Horizontal Flip is enabled
 */
#define PXP_CTRL_HFLIP(x)                        (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_HFLIP_SHIFT)) & PXP_CTRL_HFLIP_MASK)

#define PXP_CTRL_VFLIP_MASK                      (0x800U)
#define PXP_CTRL_VFLIP_SHIFT                     (11U)
/*! VFLIP
 *  0b0..Vertical Flip is disabled
 *  0b1..Vertical Flip is enabled
 */
#define PXP_CTRL_VFLIP(x)                        (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_VFLIP_SHIFT)) & PXP_CTRL_VFLIP_MASK)

#define PXP_CTRL_ROT_POS_MASK                    (0x400000U)
#define PXP_CTRL_ROT_POS_SHIFT                   (22U)
#define PXP_CTRL_ROT_POS(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_ROT_POS_SHIFT)) & PXP_CTRL_ROT_POS_MASK)

#define PXP_CTRL_BLOCK_SIZE_MASK                 (0x800000U)
#define PXP_CTRL_BLOCK_SIZE_SHIFT                (23U)
/*! BLOCK_SIZE
 *  0b0..Process 8x8 pixel blocks.
 *  0b1..Process 16x16 pixel blocks.
 */
#define PXP_CTRL_BLOCK_SIZE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_BLOCK_SIZE_SHIFT)) & PXP_CTRL_BLOCK_SIZE_MASK)

#define PXP_CTRL_EN_REPEAT_MASK                  (0x10000000U)
#define PXP_CTRL_EN_REPEAT_SHIFT                 (28U)
/*! EN_REPEAT
 *  0b0..PXP will complete the process and enter the idle state ready to accept the next frame to be processed
 *  0b1..PXP will repeat based on the current configuration register settings
 */
#define PXP_CTRL_EN_REPEAT(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_EN_REPEAT_SHIFT)) & PXP_CTRL_EN_REPEAT_MASK)

#define PXP_CTRL_CLKGATE_MASK                    (0x40000000U)
#define PXP_CTRL_CLKGATE_SHIFT                   (30U)
/*! CLKGATE
 *  0b0..Normal operation
 *  0b1..All clocks to PXP is gated-off
 */
#define PXP_CTRL_CLKGATE(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLKGATE_SHIFT)) & PXP_CTRL_CLKGATE_MASK)

#define PXP_CTRL_SFTRST_MASK                     (0x80000000U)
#define PXP_CTRL_SFTRST_SHIFT                    (31U)
/*! SFTRST
 *  0b0..Normal PXP operation is enabled
 *  0b1..Clocking with PXP is disabled and held in its reset (lowest power) state. This is the default value.
 */
#define PXP_CTRL_SFTRST(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SFTRST_SHIFT)) & PXP_CTRL_SFTRST_MASK)
/*! @} */

/*! @name CTRL_SET - Control Register 0 */
/*! @{ */

#define PXP_CTRL_SET_ENABLE_MASK                 (0x1U)
#define PXP_CTRL_SET_ENABLE_SHIFT                (0U)
/*! ENABLE
 *  0b0..PXP is disabled
 *  0b1..PXP is enabled
 */
#define PXP_CTRL_SET_ENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_ENABLE_SHIFT)) & PXP_CTRL_SET_ENABLE_MASK)

#define PXP_CTRL_SET_IRQ_ENABLE_MASK             (0x2U)
#define PXP_CTRL_SET_IRQ_ENABLE_SHIFT            (1U)
/*! IRQ_ENABLE
 *  0b0..PXP interrupt is disabled
 *  0b1..PXP interrupt is enabled
 */
#define PXP_CTRL_SET_IRQ_ENABLE(x)               (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_IRQ_ENABLE_SHIFT)) & PXP_CTRL_SET_IRQ_ENABLE_MASK)

#define PXP_CTRL_SET_NEXT_IRQ_ENABLE_MASK        (0x4U)
#define PXP_CTRL_SET_NEXT_IRQ_ENABLE_SHIFT       (2U)
/*! NEXT_IRQ_ENABLE
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define PXP_CTRL_SET_NEXT_IRQ_ENABLE(x)          (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_NEXT_IRQ_ENABLE_SHIFT)) & PXP_CTRL_SET_NEXT_IRQ_ENABLE_MASK)

#define PXP_CTRL_SET_ENABLE_LCD_HANDSHAKE_MASK   (0x10U)
#define PXP_CTRL_SET_ENABLE_LCD_HANDSHAKE_SHIFT  (4U)
#define PXP_CTRL_SET_ENABLE_LCD_HANDSHAKE(x)     (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_ENABLE_LCD_HANDSHAKE_SHIFT)) & PXP_CTRL_SET_ENABLE_LCD_HANDSHAKE_MASK)

#define PXP_CTRL_SET_ROTATE_MASK                 (0x300U)
#define PXP_CTRL_SET_ROTATE_SHIFT                (8U)
/*! ROTATE
 *  0b00..ROT_0
 *  0b01..ROT_90
 *  0b10..ROT_180
 *  0b11..ROT_270
 */
#define PXP_CTRL_SET_ROTATE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_ROTATE_SHIFT)) & PXP_CTRL_SET_ROTATE_MASK)

#define PXP_CTRL_SET_HFLIP_MASK                  (0x400U)
#define PXP_CTRL_SET_HFLIP_SHIFT                 (10U)
/*! HFLIP
 *  0b0..Horizontal Flip is disabled
 *  0b1..Horizontal Flip is enabled
 */
#define PXP_CTRL_SET_HFLIP(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_HFLIP_SHIFT)) & PXP_CTRL_SET_HFLIP_MASK)

#define PXP_CTRL_SET_VFLIP_MASK                  (0x800U)
#define PXP_CTRL_SET_VFLIP_SHIFT                 (11U)
/*! VFLIP
 *  0b0..Vertical Flip is disabled
 *  0b1..Vertical Flip is enabled
 */
#define PXP_CTRL_SET_VFLIP(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_VFLIP_SHIFT)) & PXP_CTRL_SET_VFLIP_MASK)

#define PXP_CTRL_SET_ROT_POS_MASK                (0x400000U)
#define PXP_CTRL_SET_ROT_POS_SHIFT               (22U)
#define PXP_CTRL_SET_ROT_POS(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_ROT_POS_SHIFT)) & PXP_CTRL_SET_ROT_POS_MASK)

#define PXP_CTRL_SET_BLOCK_SIZE_MASK             (0x800000U)
#define PXP_CTRL_SET_BLOCK_SIZE_SHIFT            (23U)
/*! BLOCK_SIZE
 *  0b0..Process 8x8 pixel blocks.
 *  0b1..Process 16x16 pixel blocks.
 */
#define PXP_CTRL_SET_BLOCK_SIZE(x)               (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_BLOCK_SIZE_SHIFT)) & PXP_CTRL_SET_BLOCK_SIZE_MASK)

#define PXP_CTRL_SET_EN_REPEAT_MASK              (0x10000000U)
#define PXP_CTRL_SET_EN_REPEAT_SHIFT             (28U)
/*! EN_REPEAT
 *  0b0..PXP will complete the process and enter the idle state ready to accept the next frame to be processed
 *  0b1..PXP will repeat based on the current configuration register settings
 */
#define PXP_CTRL_SET_EN_REPEAT(x)                (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_EN_REPEAT_SHIFT)) & PXP_CTRL_SET_EN_REPEAT_MASK)

#define PXP_CTRL_SET_CLKGATE_MASK                (0x40000000U)
#define PXP_CTRL_SET_CLKGATE_SHIFT               (30U)
/*! CLKGATE
 *  0b0..Normal operation
 *  0b1..All clocks to PXP is gated-off
 */
#define PXP_CTRL_SET_CLKGATE(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_CLKGATE_SHIFT)) & PXP_CTRL_SET_CLKGATE_MASK)

#define PXP_CTRL_SET_SFTRST_MASK                 (0x80000000U)
#define PXP_CTRL_SET_SFTRST_SHIFT                (31U)
/*! SFTRST
 *  0b0..Normal PXP operation is enabled
 *  0b1..Clocking with PXP is disabled and held in its reset (lowest power) state. This is the default value.
 */
#define PXP_CTRL_SET_SFTRST(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_SET_SFTRST_SHIFT)) & PXP_CTRL_SET_SFTRST_MASK)
/*! @} */

/*! @name CTRL_CLR - Control Register 0 */
/*! @{ */

#define PXP_CTRL_CLR_ENABLE_MASK                 (0x1U)
#define PXP_CTRL_CLR_ENABLE_SHIFT                (0U)
/*! ENABLE
 *  0b0..PXP is disabled
 *  0b1..PXP is enabled
 */
#define PXP_CTRL_CLR_ENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_ENABLE_SHIFT)) & PXP_CTRL_CLR_ENABLE_MASK)

#define PXP_CTRL_CLR_IRQ_ENABLE_MASK             (0x2U)
#define PXP_CTRL_CLR_IRQ_ENABLE_SHIFT            (1U)
/*! IRQ_ENABLE
 *  0b0..PXP interrupt is disabled
 *  0b1..PXP interrupt is enabled
 */
#define PXP_CTRL_CLR_IRQ_ENABLE(x)               (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_IRQ_ENABLE_SHIFT)) & PXP_CTRL_CLR_IRQ_ENABLE_MASK)

#define PXP_CTRL_CLR_NEXT_IRQ_ENABLE_MASK        (0x4U)
#define PXP_CTRL_CLR_NEXT_IRQ_ENABLE_SHIFT       (2U)
/*! NEXT_IRQ_ENABLE
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define PXP_CTRL_CLR_NEXT_IRQ_ENABLE(x)          (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_NEXT_IRQ_ENABLE_SHIFT)) & PXP_CTRL_CLR_NEXT_IRQ_ENABLE_MASK)

#define PXP_CTRL_CLR_ENABLE_LCD_HANDSHAKE_MASK   (0x10U)
#define PXP_CTRL_CLR_ENABLE_LCD_HANDSHAKE_SHIFT  (4U)
#define PXP_CTRL_CLR_ENABLE_LCD_HANDSHAKE(x)     (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_ENABLE_LCD_HANDSHAKE_SHIFT)) & PXP_CTRL_CLR_ENABLE_LCD_HANDSHAKE_MASK)

#define PXP_CTRL_CLR_ROTATE_MASK                 (0x300U)
#define PXP_CTRL_CLR_ROTATE_SHIFT                (8U)
/*! ROTATE
 *  0b00..ROT_0
 *  0b01..ROT_90
 *  0b10..ROT_180
 *  0b11..ROT_270
 */
#define PXP_CTRL_CLR_ROTATE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_ROTATE_SHIFT)) & PXP_CTRL_CLR_ROTATE_MASK)

#define PXP_CTRL_CLR_HFLIP_MASK                  (0x400U)
#define PXP_CTRL_CLR_HFLIP_SHIFT                 (10U)
/*! HFLIP
 *  0b0..Horizontal Flip is disabled
 *  0b1..Horizontal Flip is enabled
 */
#define PXP_CTRL_CLR_HFLIP(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_HFLIP_SHIFT)) & PXP_CTRL_CLR_HFLIP_MASK)

#define PXP_CTRL_CLR_VFLIP_MASK                  (0x800U)
#define PXP_CTRL_CLR_VFLIP_SHIFT                 (11U)
/*! VFLIP
 *  0b0..Vertical Flip is disabled
 *  0b1..Vertical Flip is enabled
 */
#define PXP_CTRL_CLR_VFLIP(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_VFLIP_SHIFT)) & PXP_CTRL_CLR_VFLIP_MASK)

#define PXP_CTRL_CLR_ROT_POS_MASK                (0x400000U)
#define PXP_CTRL_CLR_ROT_POS_SHIFT               (22U)
#define PXP_CTRL_CLR_ROT_POS(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_ROT_POS_SHIFT)) & PXP_CTRL_CLR_ROT_POS_MASK)

#define PXP_CTRL_CLR_BLOCK_SIZE_MASK             (0x800000U)
#define PXP_CTRL_CLR_BLOCK_SIZE_SHIFT            (23U)
/*! BLOCK_SIZE
 *  0b0..Process 8x8 pixel blocks.
 *  0b1..Process 16x16 pixel blocks.
 */
#define PXP_CTRL_CLR_BLOCK_SIZE(x)               (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_BLOCK_SIZE_SHIFT)) & PXP_CTRL_CLR_BLOCK_SIZE_MASK)

#define PXP_CTRL_CLR_EN_REPEAT_MASK              (0x10000000U)
#define PXP_CTRL_CLR_EN_REPEAT_SHIFT             (28U)
/*! EN_REPEAT
 *  0b0..PXP will complete the process and enter the idle state ready to accept the next frame to be processed
 *  0b1..PXP will repeat based on the current configuration register settings
 */
#define PXP_CTRL_CLR_EN_REPEAT(x)                (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_EN_REPEAT_SHIFT)) & PXP_CTRL_CLR_EN_REPEAT_MASK)

#define PXP_CTRL_CLR_CLKGATE_MASK                (0x40000000U)
#define PXP_CTRL_CLR_CLKGATE_SHIFT               (30U)
/*! CLKGATE
 *  0b0..Normal operation
 *  0b1..All clocks to PXP is gated-off
 */
#define PXP_CTRL_CLR_CLKGATE(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_CLKGATE_SHIFT)) & PXP_CTRL_CLR_CLKGATE_MASK)

#define PXP_CTRL_CLR_SFTRST_MASK                 (0x80000000U)
#define PXP_CTRL_CLR_SFTRST_SHIFT                (31U)
/*! SFTRST
 *  0b0..Normal PXP operation is enabled
 *  0b1..Clocking with PXP is disabled and held in its reset (lowest power) state. This is the default value.
 */
#define PXP_CTRL_CLR_SFTRST(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_CLR_SFTRST_SHIFT)) & PXP_CTRL_CLR_SFTRST_MASK)
/*! @} */

/*! @name CTRL_TOG - Control Register 0 */
/*! @{ */

#define PXP_CTRL_TOG_ENABLE_MASK                 (0x1U)
#define PXP_CTRL_TOG_ENABLE_SHIFT                (0U)
/*! ENABLE
 *  0b0..PXP is disabled
 *  0b1..PXP is enabled
 */
#define PXP_CTRL_TOG_ENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_ENABLE_SHIFT)) & PXP_CTRL_TOG_ENABLE_MASK)

#define PXP_CTRL_TOG_IRQ_ENABLE_MASK             (0x2U)
#define PXP_CTRL_TOG_IRQ_ENABLE_SHIFT            (1U)
/*! IRQ_ENABLE
 *  0b0..PXP interrupt is disabled
 *  0b1..PXP interrupt is enabled
 */
#define PXP_CTRL_TOG_IRQ_ENABLE(x)               (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_IRQ_ENABLE_SHIFT)) & PXP_CTRL_TOG_IRQ_ENABLE_MASK)

#define PXP_CTRL_TOG_NEXT_IRQ_ENABLE_MASK        (0x4U)
#define PXP_CTRL_TOG_NEXT_IRQ_ENABLE_SHIFT       (2U)
/*! NEXT_IRQ_ENABLE
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define PXP_CTRL_TOG_NEXT_IRQ_ENABLE(x)          (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_NEXT_IRQ_ENABLE_SHIFT)) & PXP_CTRL_TOG_NEXT_IRQ_ENABLE_MASK)

#define PXP_CTRL_TOG_ENABLE_LCD_HANDSHAKE_MASK   (0x10U)
#define PXP_CTRL_TOG_ENABLE_LCD_HANDSHAKE_SHIFT  (4U)
#define PXP_CTRL_TOG_ENABLE_LCD_HANDSHAKE(x)     (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_ENABLE_LCD_HANDSHAKE_SHIFT)) & PXP_CTRL_TOG_ENABLE_LCD_HANDSHAKE_MASK)

#define PXP_CTRL_TOG_ROTATE_MASK                 (0x300U)
#define PXP_CTRL_TOG_ROTATE_SHIFT                (8U)
/*! ROTATE
 *  0b00..ROT_0
 *  0b01..ROT_90
 *  0b10..ROT_180
 *  0b11..ROT_270
 */
#define PXP_CTRL_TOG_ROTATE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_ROTATE_SHIFT)) & PXP_CTRL_TOG_ROTATE_MASK)

#define PXP_CTRL_TOG_HFLIP_MASK                  (0x400U)
#define PXP_CTRL_TOG_HFLIP_SHIFT                 (10U)
/*! HFLIP
 *  0b0..Horizontal Flip is disabled
 *  0b1..Horizontal Flip is enabled
 */
#define PXP_CTRL_TOG_HFLIP(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_HFLIP_SHIFT)) & PXP_CTRL_TOG_HFLIP_MASK)

#define PXP_CTRL_TOG_VFLIP_MASK                  (0x800U)
#define PXP_CTRL_TOG_VFLIP_SHIFT                 (11U)
/*! VFLIP
 *  0b0..Vertical Flip is disabled
 *  0b1..Vertical Flip is enabled
 */
#define PXP_CTRL_TOG_VFLIP(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_VFLIP_SHIFT)) & PXP_CTRL_TOG_VFLIP_MASK)

#define PXP_CTRL_TOG_ROT_POS_MASK                (0x400000U)
#define PXP_CTRL_TOG_ROT_POS_SHIFT               (22U)
#define PXP_CTRL_TOG_ROT_POS(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_ROT_POS_SHIFT)) & PXP_CTRL_TOG_ROT_POS_MASK)

#define PXP_CTRL_TOG_BLOCK_SIZE_MASK             (0x800000U)
#define PXP_CTRL_TOG_BLOCK_SIZE_SHIFT            (23U)
/*! BLOCK_SIZE
 *  0b0..Process 8x8 pixel blocks.
 *  0b1..Process 16x16 pixel blocks.
 */
#define PXP_CTRL_TOG_BLOCK_SIZE(x)               (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_BLOCK_SIZE_SHIFT)) & PXP_CTRL_TOG_BLOCK_SIZE_MASK)

#define PXP_CTRL_TOG_EN_REPEAT_MASK              (0x10000000U)
#define PXP_CTRL_TOG_EN_REPEAT_SHIFT             (28U)
/*! EN_REPEAT
 *  0b0..PXP will complete the process and enter the idle state ready to accept the next frame to be processed
 *  0b1..PXP will repeat based on the current configuration register settings
 */
#define PXP_CTRL_TOG_EN_REPEAT(x)                (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_EN_REPEAT_SHIFT)) & PXP_CTRL_TOG_EN_REPEAT_MASK)

#define PXP_CTRL_TOG_CLKGATE_MASK                (0x40000000U)
#define PXP_CTRL_TOG_CLKGATE_SHIFT               (30U)
/*! CLKGATE
 *  0b0..Normal operation
 *  0b1..All clocks to PXP is gated-off
 */
#define PXP_CTRL_TOG_CLKGATE(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_CLKGATE_SHIFT)) & PXP_CTRL_TOG_CLKGATE_MASK)

#define PXP_CTRL_TOG_SFTRST_MASK                 (0x80000000U)
#define PXP_CTRL_TOG_SFTRST_SHIFT                (31U)
/*! SFTRST
 *  0b0..Normal PXP operation is enabled
 *  0b1..Clocking with PXP is disabled and held in its reset (lowest power) state. This is the default value.
 */
#define PXP_CTRL_TOG_SFTRST(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_CTRL_TOG_SFTRST_SHIFT)) & PXP_CTRL_TOG_SFTRST_MASK)
/*! @} */

/*! @name STAT - Status Register */
/*! @{ */

#define PXP_STAT_IRQ_MASK                        (0x1U)
#define PXP_STAT_IRQ_SHIFT                       (0U)
/*! IRQ
 *  0b0..No interrupt
 *  0b1..Interrupt generated
 */
#define PXP_STAT_IRQ(x)                          (((uint32_t)(((uint32_t)(x)) << PXP_STAT_IRQ_SHIFT)) & PXP_STAT_IRQ_MASK)

#define PXP_STAT_AXI_WRITE_ERROR_MASK            (0x2U)
#define PXP_STAT_AXI_WRITE_ERROR_SHIFT           (1U)
/*! AXI_WRITE_ERROR
 *  0b0..AXI write is normal
 *  0b1..AXI write error has occurred
 */
#define PXP_STAT_AXI_WRITE_ERROR(x)              (((uint32_t)(((uint32_t)(x)) << PXP_STAT_AXI_WRITE_ERROR_SHIFT)) & PXP_STAT_AXI_WRITE_ERROR_MASK)

#define PXP_STAT_AXI_READ_ERROR_MASK             (0x4U)
#define PXP_STAT_AXI_READ_ERROR_SHIFT            (2U)
/*! AXI_READ_ERROR
 *  0b0..AXI read is normal
 *  0b1..AXI read error has occurred
 */
#define PXP_STAT_AXI_READ_ERROR(x)               (((uint32_t)(((uint32_t)(x)) << PXP_STAT_AXI_READ_ERROR_SHIFT)) & PXP_STAT_AXI_READ_ERROR_MASK)

#define PXP_STAT_NEXT_IRQ_MASK                   (0x8U)
#define PXP_STAT_NEXT_IRQ_SHIFT                  (3U)
#define PXP_STAT_NEXT_IRQ(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_STAT_NEXT_IRQ_SHIFT)) & PXP_STAT_NEXT_IRQ_MASK)

#define PXP_STAT_AXI_ERROR_ID_MASK               (0xF0U)
#define PXP_STAT_AXI_ERROR_ID_SHIFT              (4U)
#define PXP_STAT_AXI_ERROR_ID(x)                 (((uint32_t)(((uint32_t)(x)) << PXP_STAT_AXI_ERROR_ID_SHIFT)) & PXP_STAT_AXI_ERROR_ID_MASK)

#define PXP_STAT_LUT_DMA_LOAD_DONE_IRQ_MASK      (0x100U)
#define PXP_STAT_LUT_DMA_LOAD_DONE_IRQ_SHIFT     (8U)
/*! LUT_DMA_LOAD_DONE_IRQ
 *  0b0..LUT DMA LOAD transfer is active
 *  0b1..LUT DMA LOAD transfer is complete
 */
#define PXP_STAT_LUT_DMA_LOAD_DONE_IRQ(x)        (((uint32_t)(((uint32_t)(x)) << PXP_STAT_LUT_DMA_LOAD_DONE_IRQ_SHIFT)) & PXP_STAT_LUT_DMA_LOAD_DONE_IRQ_MASK)

#define PXP_STAT_BLOCKY_MASK                     (0xFF0000U)
#define PXP_STAT_BLOCKY_SHIFT                    (16U)
#define PXP_STAT_BLOCKY(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_STAT_BLOCKY_SHIFT)) & PXP_STAT_BLOCKY_MASK)

#define PXP_STAT_BLOCKX_MASK                     (0xFF000000U)
#define PXP_STAT_BLOCKX_SHIFT                    (24U)
#define PXP_STAT_BLOCKX(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_STAT_BLOCKX_SHIFT)) & PXP_STAT_BLOCKX_MASK)
/*! @} */

/*! @name STAT_SET - Status Register */
/*! @{ */

#define PXP_STAT_SET_IRQ_MASK                    (0x1U)
#define PXP_STAT_SET_IRQ_SHIFT                   (0U)
/*! IRQ
 *  0b0..No interrupt
 *  0b1..Interrupt generated
 */
#define PXP_STAT_SET_IRQ(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_IRQ_SHIFT)) & PXP_STAT_SET_IRQ_MASK)

#define PXP_STAT_SET_AXI_WRITE_ERROR_MASK        (0x2U)
#define PXP_STAT_SET_AXI_WRITE_ERROR_SHIFT       (1U)
/*! AXI_WRITE_ERROR
 *  0b0..AXI write is normal
 *  0b1..AXI write error has occurred
 */
#define PXP_STAT_SET_AXI_WRITE_ERROR(x)          (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_AXI_WRITE_ERROR_SHIFT)) & PXP_STAT_SET_AXI_WRITE_ERROR_MASK)

#define PXP_STAT_SET_AXI_READ_ERROR_MASK         (0x4U)
#define PXP_STAT_SET_AXI_READ_ERROR_SHIFT        (2U)
/*! AXI_READ_ERROR
 *  0b0..AXI read is normal
 *  0b1..AXI read error has occurred
 */
#define PXP_STAT_SET_AXI_READ_ERROR(x)           (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_AXI_READ_ERROR_SHIFT)) & PXP_STAT_SET_AXI_READ_ERROR_MASK)

#define PXP_STAT_SET_NEXT_IRQ_MASK               (0x8U)
#define PXP_STAT_SET_NEXT_IRQ_SHIFT              (3U)
#define PXP_STAT_SET_NEXT_IRQ(x)                 (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_NEXT_IRQ_SHIFT)) & PXP_STAT_SET_NEXT_IRQ_MASK)

#define PXP_STAT_SET_AXI_ERROR_ID_MASK           (0xF0U)
#define PXP_STAT_SET_AXI_ERROR_ID_SHIFT          (4U)
#define PXP_STAT_SET_AXI_ERROR_ID(x)             (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_AXI_ERROR_ID_SHIFT)) & PXP_STAT_SET_AXI_ERROR_ID_MASK)

#define PXP_STAT_SET_LUT_DMA_LOAD_DONE_IRQ_MASK  (0x100U)
#define PXP_STAT_SET_LUT_DMA_LOAD_DONE_IRQ_SHIFT (8U)
/*! LUT_DMA_LOAD_DONE_IRQ
 *  0b0..LUT DMA LOAD transfer is active
 *  0b1..LUT DMA LOAD transfer is complete
 */
#define PXP_STAT_SET_LUT_DMA_LOAD_DONE_IRQ(x)    (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_LUT_DMA_LOAD_DONE_IRQ_SHIFT)) & PXP_STAT_SET_LUT_DMA_LOAD_DONE_IRQ_MASK)

#define PXP_STAT_SET_BLOCKY_MASK                 (0xFF0000U)
#define PXP_STAT_SET_BLOCKY_SHIFT                (16U)
#define PXP_STAT_SET_BLOCKY(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_BLOCKY_SHIFT)) & PXP_STAT_SET_BLOCKY_MASK)

#define PXP_STAT_SET_BLOCKX_MASK                 (0xFF000000U)
#define PXP_STAT_SET_BLOCKX_SHIFT                (24U)
#define PXP_STAT_SET_BLOCKX(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_STAT_SET_BLOCKX_SHIFT)) & PXP_STAT_SET_BLOCKX_MASK)
/*! @} */

/*! @name STAT_CLR - Status Register */
/*! @{ */

#define PXP_STAT_CLR_IRQ_MASK                    (0x1U)
#define PXP_STAT_CLR_IRQ_SHIFT                   (0U)
/*! IRQ
 *  0b0..No interrupt
 *  0b1..Interrupt generated
 */
#define PXP_STAT_CLR_IRQ(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_IRQ_SHIFT)) & PXP_STAT_CLR_IRQ_MASK)

#define PXP_STAT_CLR_AXI_WRITE_ERROR_MASK        (0x2U)
#define PXP_STAT_CLR_AXI_WRITE_ERROR_SHIFT       (1U)
/*! AXI_WRITE_ERROR
 *  0b0..AXI write is normal
 *  0b1..AXI write error has occurred
 */
#define PXP_STAT_CLR_AXI_WRITE_ERROR(x)          (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_AXI_WRITE_ERROR_SHIFT)) & PXP_STAT_CLR_AXI_WRITE_ERROR_MASK)

#define PXP_STAT_CLR_AXI_READ_ERROR_MASK         (0x4U)
#define PXP_STAT_CLR_AXI_READ_ERROR_SHIFT        (2U)
/*! AXI_READ_ERROR
 *  0b0..AXI read is normal
 *  0b1..AXI read error has occurred
 */
#define PXP_STAT_CLR_AXI_READ_ERROR(x)           (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_AXI_READ_ERROR_SHIFT)) & PXP_STAT_CLR_AXI_READ_ERROR_MASK)

#define PXP_STAT_CLR_NEXT_IRQ_MASK               (0x8U)
#define PXP_STAT_CLR_NEXT_IRQ_SHIFT              (3U)
#define PXP_STAT_CLR_NEXT_IRQ(x)                 (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_NEXT_IRQ_SHIFT)) & PXP_STAT_CLR_NEXT_IRQ_MASK)

#define PXP_STAT_CLR_AXI_ERROR_ID_MASK           (0xF0U)
#define PXP_STAT_CLR_AXI_ERROR_ID_SHIFT          (4U)
#define PXP_STAT_CLR_AXI_ERROR_ID(x)             (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_AXI_ERROR_ID_SHIFT)) & PXP_STAT_CLR_AXI_ERROR_ID_MASK)

#define PXP_STAT_CLR_LUT_DMA_LOAD_DONE_IRQ_MASK  (0x100U)
#define PXP_STAT_CLR_LUT_DMA_LOAD_DONE_IRQ_SHIFT (8U)
/*! LUT_DMA_LOAD_DONE_IRQ
 *  0b0..LUT DMA LOAD transfer is active
 *  0b1..LUT DMA LOAD transfer is complete
 */
#define PXP_STAT_CLR_LUT_DMA_LOAD_DONE_IRQ(x)    (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_LUT_DMA_LOAD_DONE_IRQ_SHIFT)) & PXP_STAT_CLR_LUT_DMA_LOAD_DONE_IRQ_MASK)

#define PXP_STAT_CLR_BLOCKY_MASK                 (0xFF0000U)
#define PXP_STAT_CLR_BLOCKY_SHIFT                (16U)
#define PXP_STAT_CLR_BLOCKY(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_BLOCKY_SHIFT)) & PXP_STAT_CLR_BLOCKY_MASK)

#define PXP_STAT_CLR_BLOCKX_MASK                 (0xFF000000U)
#define PXP_STAT_CLR_BLOCKX_SHIFT                (24U)
#define PXP_STAT_CLR_BLOCKX(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_STAT_CLR_BLOCKX_SHIFT)) & PXP_STAT_CLR_BLOCKX_MASK)
/*! @} */

/*! @name STAT_TOG - Status Register */
/*! @{ */

#define PXP_STAT_TOG_IRQ_MASK                    (0x1U)
#define PXP_STAT_TOG_IRQ_SHIFT                   (0U)
/*! IRQ
 *  0b0..No interrupt
 *  0b1..Interrupt generated
 */
#define PXP_STAT_TOG_IRQ(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_IRQ_SHIFT)) & PXP_STAT_TOG_IRQ_MASK)

#define PXP_STAT_TOG_AXI_WRITE_ERROR_MASK        (0x2U)
#define PXP_STAT_TOG_AXI_WRITE_ERROR_SHIFT       (1U)
/*! AXI_WRITE_ERROR
 *  0b0..AXI write is normal
 *  0b1..AXI write error has occurred
 */
#define PXP_STAT_TOG_AXI_WRITE_ERROR(x)          (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_AXI_WRITE_ERROR_SHIFT)) & PXP_STAT_TOG_AXI_WRITE_ERROR_MASK)

#define PXP_STAT_TOG_AXI_READ_ERROR_MASK         (0x4U)
#define PXP_STAT_TOG_AXI_READ_ERROR_SHIFT        (2U)
/*! AXI_READ_ERROR
 *  0b0..AXI read is normal
 *  0b1..AXI read error has occurred
 */
#define PXP_STAT_TOG_AXI_READ_ERROR(x)           (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_AXI_READ_ERROR_SHIFT)) & PXP_STAT_TOG_AXI_READ_ERROR_MASK)

#define PXP_STAT_TOG_NEXT_IRQ_MASK               (0x8U)
#define PXP_STAT_TOG_NEXT_IRQ_SHIFT              (3U)
#define PXP_STAT_TOG_NEXT_IRQ(x)                 (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_NEXT_IRQ_SHIFT)) & PXP_STAT_TOG_NEXT_IRQ_MASK)

#define PXP_STAT_TOG_AXI_ERROR_ID_MASK           (0xF0U)
#define PXP_STAT_TOG_AXI_ERROR_ID_SHIFT          (4U)
#define PXP_STAT_TOG_AXI_ERROR_ID(x)             (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_AXI_ERROR_ID_SHIFT)) & PXP_STAT_TOG_AXI_ERROR_ID_MASK)

#define PXP_STAT_TOG_LUT_DMA_LOAD_DONE_IRQ_MASK  (0x100U)
#define PXP_STAT_TOG_LUT_DMA_LOAD_DONE_IRQ_SHIFT (8U)
/*! LUT_DMA_LOAD_DONE_IRQ
 *  0b0..LUT DMA LOAD transfer is active
 *  0b1..LUT DMA LOAD transfer is complete
 */
#define PXP_STAT_TOG_LUT_DMA_LOAD_DONE_IRQ(x)    (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_LUT_DMA_LOAD_DONE_IRQ_SHIFT)) & PXP_STAT_TOG_LUT_DMA_LOAD_DONE_IRQ_MASK)

#define PXP_STAT_TOG_BLOCKY_MASK                 (0xFF0000U)
#define PXP_STAT_TOG_BLOCKY_SHIFT                (16U)
#define PXP_STAT_TOG_BLOCKY(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_BLOCKY_SHIFT)) & PXP_STAT_TOG_BLOCKY_MASK)

#define PXP_STAT_TOG_BLOCKX_MASK                 (0xFF000000U)
#define PXP_STAT_TOG_BLOCKX_SHIFT                (24U)
#define PXP_STAT_TOG_BLOCKX(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_STAT_TOG_BLOCKX_SHIFT)) & PXP_STAT_TOG_BLOCKX_MASK)
/*! @} */

/*! @name OUT_CTRL - Output Buffer Control Register */
/*! @{ */

#define PXP_OUT_CTRL_FORMAT_MASK                 (0x1FU)
#define PXP_OUT_CTRL_FORMAT_SHIFT                (0U)
/*! FORMAT
 *  0b00000..32-bit pixels
 *  0b00100..32-bit pixels (unpacked 24-bit pixel in 32 bit DWORD.)
 *  0b00101..24-bit pixels (packed 24-bit format)
 *  0b01000..16-bit pixels
 *  0b01001..16-bit pixels
 *  0b01100..16-bit pixels
 *  0b01101..16-bit pixels
 *  0b01110..16-bit pixels
 *  0b10000..32-bit pixels (1-plane XYUV unpacked)
 *  0b10010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b10011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b10100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b10101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b11000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b11001..16-bit pixels (2-plane UV)
 *  0b11010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b11011..16-bit pixels (2-plane VU)
 */
#define PXP_OUT_CTRL_FORMAT(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_FORMAT_SHIFT)) & PXP_OUT_CTRL_FORMAT_MASK)

#define PXP_OUT_CTRL_INTERLACED_OUTPUT_MASK      (0x300U)
#define PXP_OUT_CTRL_INTERLACED_OUTPUT_SHIFT     (8U)
/*! INTERLACED_OUTPUT
 *  0b00..All data written in progressive format to the OUTBUF Pointer.
 *  0b01..Interlaced output: only data for field 0 is written to the OUTBUF Pointer.
 *  0b10..Interlaced output: only data for field 1 is written to the OUTBUF2 Pointer.
 *  0b11..Interlaced output: data for field 0 is written to OUTBUF and data for field 1 is written to OUTBUF2.
 */
#define PXP_OUT_CTRL_INTERLACED_OUTPUT(x)        (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_INTERLACED_OUTPUT_SHIFT)) & PXP_OUT_CTRL_INTERLACED_OUTPUT_MASK)

#define PXP_OUT_CTRL_ALPHA_OUTPUT_MASK           (0x800000U)
#define PXP_OUT_CTRL_ALPHA_OUTPUT_SHIFT          (23U)
/*! ALPHA_OUTPUT
 *  0b0..Retain
 *  0b1..Overwritten
 */
#define PXP_OUT_CTRL_ALPHA_OUTPUT(x)             (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_ALPHA_OUTPUT_SHIFT)) & PXP_OUT_CTRL_ALPHA_OUTPUT_MASK)

#define PXP_OUT_CTRL_ALPHA_MASK                  (0xFF000000U)
#define PXP_OUT_CTRL_ALPHA_SHIFT                 (24U)
#define PXP_OUT_CTRL_ALPHA(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_ALPHA_SHIFT)) & PXP_OUT_CTRL_ALPHA_MASK)
/*! @} */

/*! @name OUT_CTRL_SET - Output Buffer Control Register */
/*! @{ */

#define PXP_OUT_CTRL_SET_FORMAT_MASK             (0x1FU)
#define PXP_OUT_CTRL_SET_FORMAT_SHIFT            (0U)
/*! FORMAT
 *  0b00000..32-bit pixels
 *  0b00100..32-bit pixels (unpacked 24-bit pixel in 32 bit DWORD.)
 *  0b00101..24-bit pixels (packed 24-bit format)
 *  0b01000..16-bit pixels
 *  0b01001..16-bit pixels
 *  0b01100..16-bit pixels
 *  0b01101..16-bit pixels
 *  0b01110..16-bit pixels
 *  0b10000..32-bit pixels (1-plane XYUV unpacked)
 *  0b10010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b10011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b10100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b10101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b11000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b11001..16-bit pixels (2-plane UV)
 *  0b11010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b11011..16-bit pixels (2-plane VU)
 */
#define PXP_OUT_CTRL_SET_FORMAT(x)               (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_SET_FORMAT_SHIFT)) & PXP_OUT_CTRL_SET_FORMAT_MASK)

#define PXP_OUT_CTRL_SET_INTERLACED_OUTPUT_MASK  (0x300U)
#define PXP_OUT_CTRL_SET_INTERLACED_OUTPUT_SHIFT (8U)
/*! INTERLACED_OUTPUT
 *  0b00..All data written in progressive format to the OUTBUF Pointer.
 *  0b01..Interlaced output: only data for field 0 is written to the OUTBUF Pointer.
 *  0b10..Interlaced output: only data for field 1 is written to the OUTBUF2 Pointer.
 *  0b11..Interlaced output: data for field 0 is written to OUTBUF and data for field 1 is written to OUTBUF2.
 */
#define PXP_OUT_CTRL_SET_INTERLACED_OUTPUT(x)    (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_SET_INTERLACED_OUTPUT_SHIFT)) & PXP_OUT_CTRL_SET_INTERLACED_OUTPUT_MASK)

#define PXP_OUT_CTRL_SET_ALPHA_OUTPUT_MASK       (0x800000U)
#define PXP_OUT_CTRL_SET_ALPHA_OUTPUT_SHIFT      (23U)
/*! ALPHA_OUTPUT
 *  0b0..Retain
 *  0b1..Overwritten
 */
#define PXP_OUT_CTRL_SET_ALPHA_OUTPUT(x)         (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_SET_ALPHA_OUTPUT_SHIFT)) & PXP_OUT_CTRL_SET_ALPHA_OUTPUT_MASK)

#define PXP_OUT_CTRL_SET_ALPHA_MASK              (0xFF000000U)
#define PXP_OUT_CTRL_SET_ALPHA_SHIFT             (24U)
#define PXP_OUT_CTRL_SET_ALPHA(x)                (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_SET_ALPHA_SHIFT)) & PXP_OUT_CTRL_SET_ALPHA_MASK)
/*! @} */

/*! @name OUT_CTRL_CLR - Output Buffer Control Register */
/*! @{ */

#define PXP_OUT_CTRL_CLR_FORMAT_MASK             (0x1FU)
#define PXP_OUT_CTRL_CLR_FORMAT_SHIFT            (0U)
/*! FORMAT
 *  0b00000..32-bit pixels
 *  0b00100..32-bit pixels (unpacked 24-bit pixel in 32 bit DWORD.)
 *  0b00101..24-bit pixels (packed 24-bit format)
 *  0b01000..16-bit pixels
 *  0b01001..16-bit pixels
 *  0b01100..16-bit pixels
 *  0b01101..16-bit pixels
 *  0b01110..16-bit pixels
 *  0b10000..32-bit pixels (1-plane XYUV unpacked)
 *  0b10010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b10011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b10100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b10101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b11000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b11001..16-bit pixels (2-plane UV)
 *  0b11010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b11011..16-bit pixels (2-plane VU)
 */
#define PXP_OUT_CTRL_CLR_FORMAT(x)               (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_CLR_FORMAT_SHIFT)) & PXP_OUT_CTRL_CLR_FORMAT_MASK)

#define PXP_OUT_CTRL_CLR_INTERLACED_OUTPUT_MASK  (0x300U)
#define PXP_OUT_CTRL_CLR_INTERLACED_OUTPUT_SHIFT (8U)
/*! INTERLACED_OUTPUT
 *  0b00..All data written in progressive format to the OUTBUF Pointer.
 *  0b01..Interlaced output: only data for field 0 is written to the OUTBUF Pointer.
 *  0b10..Interlaced output: only data for field 1 is written to the OUTBUF2 Pointer.
 *  0b11..Interlaced output: data for field 0 is written to OUTBUF and data for field 1 is written to OUTBUF2.
 */
#define PXP_OUT_CTRL_CLR_INTERLACED_OUTPUT(x)    (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_CLR_INTERLACED_OUTPUT_SHIFT)) & PXP_OUT_CTRL_CLR_INTERLACED_OUTPUT_MASK)

#define PXP_OUT_CTRL_CLR_ALPHA_OUTPUT_MASK       (0x800000U)
#define PXP_OUT_CTRL_CLR_ALPHA_OUTPUT_SHIFT      (23U)
/*! ALPHA_OUTPUT
 *  0b0..Retain
 *  0b1..Overwritten
 */
#define PXP_OUT_CTRL_CLR_ALPHA_OUTPUT(x)         (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_CLR_ALPHA_OUTPUT_SHIFT)) & PXP_OUT_CTRL_CLR_ALPHA_OUTPUT_MASK)

#define PXP_OUT_CTRL_CLR_ALPHA_MASK              (0xFF000000U)
#define PXP_OUT_CTRL_CLR_ALPHA_SHIFT             (24U)
#define PXP_OUT_CTRL_CLR_ALPHA(x)                (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_CLR_ALPHA_SHIFT)) & PXP_OUT_CTRL_CLR_ALPHA_MASK)
/*! @} */

/*! @name OUT_CTRL_TOG - Output Buffer Control Register */
/*! @{ */

#define PXP_OUT_CTRL_TOG_FORMAT_MASK             (0x1FU)
#define PXP_OUT_CTRL_TOG_FORMAT_SHIFT            (0U)
/*! FORMAT
 *  0b00000..32-bit pixels
 *  0b00100..32-bit pixels (unpacked 24-bit pixel in 32 bit DWORD.)
 *  0b00101..24-bit pixels (packed 24-bit format)
 *  0b01000..16-bit pixels
 *  0b01001..16-bit pixels
 *  0b01100..16-bit pixels
 *  0b01101..16-bit pixels
 *  0b01110..16-bit pixels
 *  0b10000..32-bit pixels (1-plane XYUV unpacked)
 *  0b10010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b10011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b10100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b10101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b11000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b11001..16-bit pixels (2-plane UV)
 *  0b11010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b11011..16-bit pixels (2-plane VU)
 */
#define PXP_OUT_CTRL_TOG_FORMAT(x)               (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_TOG_FORMAT_SHIFT)) & PXP_OUT_CTRL_TOG_FORMAT_MASK)

#define PXP_OUT_CTRL_TOG_INTERLACED_OUTPUT_MASK  (0x300U)
#define PXP_OUT_CTRL_TOG_INTERLACED_OUTPUT_SHIFT (8U)
/*! INTERLACED_OUTPUT
 *  0b00..All data written in progressive format to the OUTBUF Pointer.
 *  0b01..Interlaced output: only data for field 0 is written to the OUTBUF Pointer.
 *  0b10..Interlaced output: only data for field 1 is written to the OUTBUF2 Pointer.
 *  0b11..Interlaced output: data for field 0 is written to OUTBUF and data for field 1 is written to OUTBUF2.
 */
#define PXP_OUT_CTRL_TOG_INTERLACED_OUTPUT(x)    (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_TOG_INTERLACED_OUTPUT_SHIFT)) & PXP_OUT_CTRL_TOG_INTERLACED_OUTPUT_MASK)

#define PXP_OUT_CTRL_TOG_ALPHA_OUTPUT_MASK       (0x800000U)
#define PXP_OUT_CTRL_TOG_ALPHA_OUTPUT_SHIFT      (23U)
/*! ALPHA_OUTPUT
 *  0b0..Retain
 *  0b1..Overwritten
 */
#define PXP_OUT_CTRL_TOG_ALPHA_OUTPUT(x)         (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_TOG_ALPHA_OUTPUT_SHIFT)) & PXP_OUT_CTRL_TOG_ALPHA_OUTPUT_MASK)

#define PXP_OUT_CTRL_TOG_ALPHA_MASK              (0xFF000000U)
#define PXP_OUT_CTRL_TOG_ALPHA_SHIFT             (24U)
#define PXP_OUT_CTRL_TOG_ALPHA(x)                (((uint32_t)(((uint32_t)(x)) << PXP_OUT_CTRL_TOG_ALPHA_SHIFT)) & PXP_OUT_CTRL_TOG_ALPHA_MASK)
/*! @} */

/*! @name OUT_BUF - Output Frame Buffer Pointer */
/*! @{ */

#define PXP_OUT_BUF_ADDR_MASK                    (0xFFFFFFFFU)
#define PXP_OUT_BUF_ADDR_SHIFT                   (0U)
#define PXP_OUT_BUF_ADDR(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_BUF_ADDR_SHIFT)) & PXP_OUT_BUF_ADDR_MASK)
/*! @} */

/*! @name OUT_BUF2 - Output Frame Buffer Pointer #2 */
/*! @{ */

#define PXP_OUT_BUF2_ADDR_MASK                   (0xFFFFFFFFU)
#define PXP_OUT_BUF2_ADDR_SHIFT                  (0U)
#define PXP_OUT_BUF2_ADDR(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_OUT_BUF2_ADDR_SHIFT)) & PXP_OUT_BUF2_ADDR_MASK)
/*! @} */

/*! @name OUT_PITCH - Output Buffer Pitch */
/*! @{ */

#define PXP_OUT_PITCH_PITCH_MASK                 (0xFFFFU)
#define PXP_OUT_PITCH_PITCH_SHIFT                (0U)
#define PXP_OUT_PITCH_PITCH(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_OUT_PITCH_PITCH_SHIFT)) & PXP_OUT_PITCH_PITCH_MASK)
/*! @} */

/*! @name OUT_LRC - Output Surface Lower Right Coordinate */
/*! @{ */

#define PXP_OUT_LRC_Y_MASK                       (0x3FFFU)
#define PXP_OUT_LRC_Y_SHIFT                      (0U)
#define PXP_OUT_LRC_Y(x)                         (((uint32_t)(((uint32_t)(x)) << PXP_OUT_LRC_Y_SHIFT)) & PXP_OUT_LRC_Y_MASK)

#define PXP_OUT_LRC_X_MASK                       (0x3FFF0000U)
#define PXP_OUT_LRC_X_SHIFT                      (16U)
#define PXP_OUT_LRC_X(x)                         (((uint32_t)(((uint32_t)(x)) << PXP_OUT_LRC_X_SHIFT)) & PXP_OUT_LRC_X_MASK)
/*! @} */

/*! @name OUT_PS_ULC - Processed Surface Upper Left Coordinate */
/*! @{ */

#define PXP_OUT_PS_ULC_Y_MASK                    (0x3FFFU)
#define PXP_OUT_PS_ULC_Y_SHIFT                   (0U)
#define PXP_OUT_PS_ULC_Y(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_PS_ULC_Y_SHIFT)) & PXP_OUT_PS_ULC_Y_MASK)

#define PXP_OUT_PS_ULC_X_MASK                    (0x3FFF0000U)
#define PXP_OUT_PS_ULC_X_SHIFT                   (16U)
#define PXP_OUT_PS_ULC_X(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_PS_ULC_X_SHIFT)) & PXP_OUT_PS_ULC_X_MASK)
/*! @} */

/*! @name OUT_PS_LRC - Processed Surface Lower Right Coordinate */
/*! @{ */

#define PXP_OUT_PS_LRC_Y_MASK                    (0x3FFFU)
#define PXP_OUT_PS_LRC_Y_SHIFT                   (0U)
#define PXP_OUT_PS_LRC_Y(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_PS_LRC_Y_SHIFT)) & PXP_OUT_PS_LRC_Y_MASK)

#define PXP_OUT_PS_LRC_X_MASK                    (0x3FFF0000U)
#define PXP_OUT_PS_LRC_X_SHIFT                   (16U)
#define PXP_OUT_PS_LRC_X(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_PS_LRC_X_SHIFT)) & PXP_OUT_PS_LRC_X_MASK)
/*! @} */

/*! @name OUT_AS_ULC - Alpha Surface Upper Left Coordinate */
/*! @{ */

#define PXP_OUT_AS_ULC_Y_MASK                    (0x3FFFU)
#define PXP_OUT_AS_ULC_Y_SHIFT                   (0U)
#define PXP_OUT_AS_ULC_Y(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_AS_ULC_Y_SHIFT)) & PXP_OUT_AS_ULC_Y_MASK)

#define PXP_OUT_AS_ULC_X_MASK                    (0x3FFF0000U)
#define PXP_OUT_AS_ULC_X_SHIFT                   (16U)
#define PXP_OUT_AS_ULC_X(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_AS_ULC_X_SHIFT)) & PXP_OUT_AS_ULC_X_MASK)
/*! @} */

/*! @name OUT_AS_LRC - Alpha Surface Lower Right Coordinate */
/*! @{ */

#define PXP_OUT_AS_LRC_Y_MASK                    (0x3FFFU)
#define PXP_OUT_AS_LRC_Y_SHIFT                   (0U)
#define PXP_OUT_AS_LRC_Y(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_AS_LRC_Y_SHIFT)) & PXP_OUT_AS_LRC_Y_MASK)

#define PXP_OUT_AS_LRC_X_MASK                    (0x3FFF0000U)
#define PXP_OUT_AS_LRC_X_SHIFT                   (16U)
#define PXP_OUT_AS_LRC_X(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_OUT_AS_LRC_X_SHIFT)) & PXP_OUT_AS_LRC_X_MASK)
/*! @} */

/*! @name PS_CTRL - Processed Surface (PS) Control Register */
/*! @{ */

#define PXP_PS_CTRL_FORMAT_MASK                  (0x3FU)
#define PXP_PS_CTRL_FORMAT_SHIFT                 (0U)
/*! FORMAT
 *  0b000100..32-bit pixels (unpacked 24-bit format with/without alpha at high 8bits)
 *  0b001100..16-bit pixels with/without alpha at high 1bit
 *  0b001101..16-bit pixels with/without alpha at high 4 bits
 *  0b001110..16-bit pixels
 *  0b010000..32-bit pixels (1-plane XYUV unpacked)
 *  0b010010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b010011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b010100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b010101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b011000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b011001..16-bit pixels (2-plane UV)
 *  0b011010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b011011..16-bit pixels (2-plane VU)
 *  0b011110..16-bit pixels (3-plane format)
 *  0b011111..16-bit pixels (3-plane format)
 *  0b100100..2-bit pixels with alpha at the low 8 bits
 *  0b101100..16-bit pixels with alpha at the low 1bits
 *  0b101101..16-bit pixels with alpha at the low 4 bits
 */
#define PXP_PS_CTRL_FORMAT(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_FORMAT_SHIFT)) & PXP_PS_CTRL_FORMAT_MASK)

#define PXP_PS_CTRL_WB_SWAP_MASK                 (0x40U)
#define PXP_PS_CTRL_WB_SWAP_SHIFT                (6U)
/*! WB_SWAP
 *  0b0..Byte swap is disabled
 *  0b1..Byte swap is enabled
 */
#define PXP_PS_CTRL_WB_SWAP(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_WB_SWAP_SHIFT)) & PXP_PS_CTRL_WB_SWAP_MASK)

#define PXP_PS_CTRL_DECY_MASK                    (0x300U)
#define PXP_PS_CTRL_DECY_SHIFT                   (8U)
/*! DECY
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_DECY(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_DECY_SHIFT)) & PXP_PS_CTRL_DECY_MASK)

#define PXP_PS_CTRL_DECX_MASK                    (0xC00U)
#define PXP_PS_CTRL_DECX_SHIFT                   (10U)
/*! DECX
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_DECX(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_DECX_SHIFT)) & PXP_PS_CTRL_DECX_MASK)
/*! @} */

/*! @name PS_CTRL_SET - Processed Surface (PS) Control Register */
/*! @{ */

#define PXP_PS_CTRL_SET_FORMAT_MASK              (0x3FU)
#define PXP_PS_CTRL_SET_FORMAT_SHIFT             (0U)
/*! FORMAT
 *  0b000100..32-bit pixels (unpacked 24-bit format with/without alpha at high 8bits)
 *  0b001100..16-bit pixels with/without alpha at high 1bit
 *  0b001101..16-bit pixels with/without alpha at high 4 bits
 *  0b001110..16-bit pixels
 *  0b010000..32-bit pixels (1-plane XYUV unpacked)
 *  0b010010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b010011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b010100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b010101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b011000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b011001..16-bit pixels (2-plane UV)
 *  0b011010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b011011..16-bit pixels (2-plane VU)
 *  0b011110..16-bit pixels (3-plane format)
 *  0b011111..16-bit pixels (3-plane format)
 *  0b100100..2-bit pixels with alpha at the low 8 bits
 *  0b101100..16-bit pixels with alpha at the low 1bits
 *  0b101101..16-bit pixels with alpha at the low 4 bits
 */
#define PXP_PS_CTRL_SET_FORMAT(x)                (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_SET_FORMAT_SHIFT)) & PXP_PS_CTRL_SET_FORMAT_MASK)

#define PXP_PS_CTRL_SET_WB_SWAP_MASK             (0x40U)
#define PXP_PS_CTRL_SET_WB_SWAP_SHIFT            (6U)
/*! WB_SWAP
 *  0b0..Byte swap is disabled
 *  0b1..Byte swap is enabled
 */
#define PXP_PS_CTRL_SET_WB_SWAP(x)               (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_SET_WB_SWAP_SHIFT)) & PXP_PS_CTRL_SET_WB_SWAP_MASK)

#define PXP_PS_CTRL_SET_DECY_MASK                (0x300U)
#define PXP_PS_CTRL_SET_DECY_SHIFT               (8U)
/*! DECY
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_SET_DECY(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_SET_DECY_SHIFT)) & PXP_PS_CTRL_SET_DECY_MASK)

#define PXP_PS_CTRL_SET_DECX_MASK                (0xC00U)
#define PXP_PS_CTRL_SET_DECX_SHIFT               (10U)
/*! DECX
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_SET_DECX(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_SET_DECX_SHIFT)) & PXP_PS_CTRL_SET_DECX_MASK)
/*! @} */

/*! @name PS_CTRL_CLR - Processed Surface (PS) Control Register */
/*! @{ */

#define PXP_PS_CTRL_CLR_FORMAT_MASK              (0x3FU)
#define PXP_PS_CTRL_CLR_FORMAT_SHIFT             (0U)
/*! FORMAT
 *  0b000100..32-bit pixels (unpacked 24-bit format with/without alpha at high 8bits)
 *  0b001100..16-bit pixels with/without alpha at high 1bit
 *  0b001101..16-bit pixels with/without alpha at high 4 bits
 *  0b001110..16-bit pixels
 *  0b010000..32-bit pixels (1-plane XYUV unpacked)
 *  0b010010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b010011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b010100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b010101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b011000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b011001..16-bit pixels (2-plane UV)
 *  0b011010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b011011..16-bit pixels (2-plane VU)
 *  0b011110..16-bit pixels (3-plane format)
 *  0b011111..16-bit pixels (3-plane format)
 *  0b100100..2-bit pixels with alpha at the low 8 bits
 *  0b101100..16-bit pixels with alpha at the low 1bits
 *  0b101101..16-bit pixels with alpha at the low 4 bits
 */
#define PXP_PS_CTRL_CLR_FORMAT(x)                (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_CLR_FORMAT_SHIFT)) & PXP_PS_CTRL_CLR_FORMAT_MASK)

#define PXP_PS_CTRL_CLR_WB_SWAP_MASK             (0x40U)
#define PXP_PS_CTRL_CLR_WB_SWAP_SHIFT            (6U)
/*! WB_SWAP
 *  0b0..Byte swap is disabled
 *  0b1..Byte swap is enabled
 */
#define PXP_PS_CTRL_CLR_WB_SWAP(x)               (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_CLR_WB_SWAP_SHIFT)) & PXP_PS_CTRL_CLR_WB_SWAP_MASK)

#define PXP_PS_CTRL_CLR_DECY_MASK                (0x300U)
#define PXP_PS_CTRL_CLR_DECY_SHIFT               (8U)
/*! DECY
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_CLR_DECY(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_CLR_DECY_SHIFT)) & PXP_PS_CTRL_CLR_DECY_MASK)

#define PXP_PS_CTRL_CLR_DECX_MASK                (0xC00U)
#define PXP_PS_CTRL_CLR_DECX_SHIFT               (10U)
/*! DECX
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_CLR_DECX(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_CLR_DECX_SHIFT)) & PXP_PS_CTRL_CLR_DECX_MASK)
/*! @} */

/*! @name PS_CTRL_TOG - Processed Surface (PS) Control Register */
/*! @{ */

#define PXP_PS_CTRL_TOG_FORMAT_MASK              (0x3FU)
#define PXP_PS_CTRL_TOG_FORMAT_SHIFT             (0U)
/*! FORMAT
 *  0b000100..32-bit pixels (unpacked 24-bit format with/without alpha at high 8bits)
 *  0b001100..16-bit pixels with/without alpha at high 1bit
 *  0b001101..16-bit pixels with/without alpha at high 4 bits
 *  0b001110..16-bit pixels
 *  0b010000..32-bit pixels (1-plane XYUV unpacked)
 *  0b010010..16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
 *  0b010011..16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
 *  0b010100..8-bit monochrome pixels (1-plane Y luma output)
 *  0b010101..4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
 *  0b011000..16-bit pixels (2-plane UV interleaved bytes)
 *  0b011001..16-bit pixels (2-plane UV)
 *  0b011010..16-bit pixels (2-plane VU interleaved bytes)
 *  0b011011..16-bit pixels (2-plane VU)
 *  0b011110..16-bit pixels (3-plane format)
 *  0b011111..16-bit pixels (3-plane format)
 *  0b100100..2-bit pixels with alpha at the low 8 bits
 *  0b101100..16-bit pixels with alpha at the low 1bits
 *  0b101101..16-bit pixels with alpha at the low 4 bits
 */
#define PXP_PS_CTRL_TOG_FORMAT(x)                (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_TOG_FORMAT_SHIFT)) & PXP_PS_CTRL_TOG_FORMAT_MASK)

#define PXP_PS_CTRL_TOG_WB_SWAP_MASK             (0x40U)
#define PXP_PS_CTRL_TOG_WB_SWAP_SHIFT            (6U)
/*! WB_SWAP
 *  0b0..Byte swap is disabled
 *  0b1..Byte swap is enabled
 */
#define PXP_PS_CTRL_TOG_WB_SWAP(x)               (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_TOG_WB_SWAP_SHIFT)) & PXP_PS_CTRL_TOG_WB_SWAP_MASK)

#define PXP_PS_CTRL_TOG_DECY_MASK                (0x300U)
#define PXP_PS_CTRL_TOG_DECY_SHIFT               (8U)
/*! DECY
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_TOG_DECY(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_TOG_DECY_SHIFT)) & PXP_PS_CTRL_TOG_DECY_MASK)

#define PXP_PS_CTRL_TOG_DECX_MASK                (0xC00U)
#define PXP_PS_CTRL_TOG_DECX_SHIFT               (10U)
/*! DECX
 *  0b00..Disable pre-decimation filter.
 *  0b01..Decimate PS by 2.
 *  0b10..Decimate PS by 4.
 *  0b11..Decimate PS by 8.
 */
#define PXP_PS_CTRL_TOG_DECX(x)                  (((uint32_t)(((uint32_t)(x)) << PXP_PS_CTRL_TOG_DECX_SHIFT)) & PXP_PS_CTRL_TOG_DECX_MASK)
/*! @} */

/*! @name PS_BUF - PS Input Buffer Address */
/*! @{ */

#define PXP_PS_BUF_ADDR_MASK                     (0xFFFFFFFFU)
#define PXP_PS_BUF_ADDR_SHIFT                    (0U)
#define PXP_PS_BUF_ADDR(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_PS_BUF_ADDR_SHIFT)) & PXP_PS_BUF_ADDR_MASK)
/*! @} */

/*! @name PS_UBUF - PS U/Cb or 2 Plane UV Input Buffer Address */
/*! @{ */

#define PXP_PS_UBUF_ADDR_MASK                    (0xFFFFFFFFU)
#define PXP_PS_UBUF_ADDR_SHIFT                   (0U)
#define PXP_PS_UBUF_ADDR(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_PS_UBUF_ADDR_SHIFT)) & PXP_PS_UBUF_ADDR_MASK)
/*! @} */

/*! @name PS_VBUF - PS V/Cr Input Buffer Address */
/*! @{ */

#define PXP_PS_VBUF_ADDR_MASK                    (0xFFFFFFFFU)
#define PXP_PS_VBUF_ADDR_SHIFT                   (0U)
#define PXP_PS_VBUF_ADDR(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_PS_VBUF_ADDR_SHIFT)) & PXP_PS_VBUF_ADDR_MASK)
/*! @} */

/*! @name PS_PITCH - Processed Surface Pitch */
/*! @{ */

#define PXP_PS_PITCH_PITCH_MASK                  (0xFFFFU)
#define PXP_PS_PITCH_PITCH_SHIFT                 (0U)
#define PXP_PS_PITCH_PITCH(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_PS_PITCH_PITCH_SHIFT)) & PXP_PS_PITCH_PITCH_MASK)
/*! @} */

/*! @name PS_BACKGROUND - PS Background Color */
/*! @{ */

#define PXP_PS_BACKGROUND_COLOR_MASK             (0xFFFFFFU)
#define PXP_PS_BACKGROUND_COLOR_SHIFT            (0U)
#define PXP_PS_BACKGROUND_COLOR(x)               (((uint32_t)(((uint32_t)(x)) << PXP_PS_BACKGROUND_COLOR_SHIFT)) & PXP_PS_BACKGROUND_COLOR_MASK)
/*! @} */

/*! @name PS_SCALE - PS Scale Factor Register */
/*! @{ */

#define PXP_PS_SCALE_XSCALE_MASK                 (0x7FFFU)
#define PXP_PS_SCALE_XSCALE_SHIFT                (0U)
#define PXP_PS_SCALE_XSCALE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_PS_SCALE_XSCALE_SHIFT)) & PXP_PS_SCALE_XSCALE_MASK)

#define PXP_PS_SCALE_YSCALE_MASK                 (0x7FFF0000U)
#define PXP_PS_SCALE_YSCALE_SHIFT                (16U)
#define PXP_PS_SCALE_YSCALE(x)                   (((uint32_t)(((uint32_t)(x)) << PXP_PS_SCALE_YSCALE_SHIFT)) & PXP_PS_SCALE_YSCALE_MASK)
/*! @} */

/*! @name PS_OFFSET - PS Scale Offset Register */
/*! @{ */

#define PXP_PS_OFFSET_XOFFSET_MASK               (0xFFFU)
#define PXP_PS_OFFSET_XOFFSET_SHIFT              (0U)
#define PXP_PS_OFFSET_XOFFSET(x)                 (((uint32_t)(((uint32_t)(x)) << PXP_PS_OFFSET_XOFFSET_SHIFT)) & PXP_PS_OFFSET_XOFFSET_MASK)

#define PXP_PS_OFFSET_YOFFSET_MASK               (0xFFF0000U)
#define PXP_PS_OFFSET_YOFFSET_SHIFT              (16U)
#define PXP_PS_OFFSET_YOFFSET(x)                 (((uint32_t)(((uint32_t)(x)) << PXP_PS_OFFSET_YOFFSET_SHIFT)) & PXP_PS_OFFSET_YOFFSET_MASK)
/*! @} */

/*! @name PS_CLRKEYLOW - PS Color Key Low */
/*! @{ */

#define PXP_PS_CLRKEYLOW_PIXEL_MASK              (0xFFFFFFU)
#define PXP_PS_CLRKEYLOW_PIXEL_SHIFT             (0U)
#define PXP_PS_CLRKEYLOW_PIXEL(x)                (((uint32_t)(((uint32_t)(x)) << PXP_PS_CLRKEYLOW_PIXEL_SHIFT)) & PXP_PS_CLRKEYLOW_PIXEL_MASK)
/*! @} */

/*! @name PS_CLRKEYHIGH - PS Color Key High */
/*! @{ */

#define PXP_PS_CLRKEYHIGH_PIXEL_MASK             (0xFFFFFFU)
#define PXP_PS_CLRKEYHIGH_PIXEL_SHIFT            (0U)
#define PXP_PS_CLRKEYHIGH_PIXEL(x)               (((uint32_t)(((uint32_t)(x)) << PXP_PS_CLRKEYHIGH_PIXEL_SHIFT)) & PXP_PS_CLRKEYHIGH_PIXEL_MASK)
/*! @} */

/*! @name AS_CTRL - Alpha Surface Control */
/*! @{ */

#define PXP_AS_CTRL_ALPHA_CTRL_MASK              (0x6U)
#define PXP_AS_CTRL_ALPHA_CTRL_SHIFT             (1U)
/*! ALPHA_CTRL
 *  0b00..Indicates that the AS pixel alpha value will be used to blend the AS with PS. The ALPHA field is ignored.
 *  0b01..Indicates that the value in the ALPHA field should be used instead of the alpha values present in the input pixels.
 *  0b10..Indicates that the value in the ALPHA field should be used to scale all pixel alpha values. Each pixel
 *        alpha is multiplied by the value in the ALPHA field.
 *  0b11..Enable ROPs. The ROP field indicates an operation to be performed on the alpha surface and PS pixels.
 */
#define PXP_AS_CTRL_ALPHA_CTRL(x)                (((uint32_t)(((uint32_t)(x)) << PXP_AS_CTRL_ALPHA_CTRL_SHIFT)) & PXP_AS_CTRL_ALPHA_CTRL_MASK)

#define PXP_AS_CTRL_ENABLE_COLORKEY_MASK         (0x8U)
#define PXP_AS_CTRL_ENABLE_COLORKEY_SHIFT        (3U)
/*! ENABLE_COLORKEY
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define PXP_AS_CTRL_ENABLE_COLORKEY(x)           (((uint32_t)(((uint32_t)(x)) << PXP_AS_CTRL_ENABLE_COLORKEY_SHIFT)) & PXP_AS_CTRL_ENABLE_COLORKEY_MASK)

#define PXP_AS_CTRL_FORMAT_MASK                  (0xF0U)
#define PXP_AS_CTRL_FORMAT_SHIFT                 (4U)
/*! FORMAT
 *  0b0000..32-bit pixels with alpha
 *  0b0001..2-bit pixel with alpha at low 8 bits
 *  0b0100..32-bit pixels without alpha (unpacked 24-bit format)
 *  0b1000..16-bit pixels with alpha
 *  0b1001..16-bit pixels with alpha
 *  0b1010..16-bit pixel with alpha at low 1 bit
 *  0b1011..16-bit pixel with alpha at low 4 bits
 *  0b1100..16-bit pixels without alpha
 *  0b1101..16-bit pixels without alpha
 *  0b1110..16-bit pixels without alpha
 */
#define PXP_AS_CTRL_FORMAT(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_AS_CTRL_FORMAT_SHIFT)) & PXP_AS_CTRL_FORMAT_MASK)

#define PXP_AS_CTRL_ALPHA_MASK                   (0xFF00U)
#define PXP_AS_CTRL_ALPHA_SHIFT                  (8U)
#define PXP_AS_CTRL_ALPHA(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_AS_CTRL_ALPHA_SHIFT)) & PXP_AS_CTRL_ALPHA_MASK)

#define PXP_AS_CTRL_ROP_MASK                     (0xF0000U)
#define PXP_AS_CTRL_ROP_SHIFT                    (16U)
/*! ROP
 *  0b0000..AS AND PS
 *  0b0001..nAS AND PS
 *  0b0010..AS AND nPS
 *  0b0011..AS OR PS
 *  0b0100..nAS OR PS
 *  0b0101..AS OR nPS
 *  0b0110..nAS
 *  0b0111..nPS
 *  0b1000..AS NAND PS
 *  0b1001..AS NOR PS
 *  0b1010..AS XOR PS
 *  0b1011..AS XNOR PS
 */
#define PXP_AS_CTRL_ROP(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_AS_CTRL_ROP_SHIFT)) & PXP_AS_CTRL_ROP_MASK)

#define PXP_AS_CTRL_ALPHA_INVERT_MASK            (0x100000U)
#define PXP_AS_CTRL_ALPHA_INVERT_SHIFT           (20U)
/*! ALPHA_INVERT
 *  0b0..Not inverted
 *  0b1..Inverted
 */
#define PXP_AS_CTRL_ALPHA_INVERT(x)              (((uint32_t)(((uint32_t)(x)) << PXP_AS_CTRL_ALPHA_INVERT_SHIFT)) & PXP_AS_CTRL_ALPHA_INVERT_MASK)
/*! @} */

/*! @name AS_BUF - Alpha Surface Buffer Pointer */
/*! @{ */

#define PXP_AS_BUF_ADDR_MASK                     (0xFFFFFFFFU)
#define PXP_AS_BUF_ADDR_SHIFT                    (0U)
#define PXP_AS_BUF_ADDR(x)                       (((uint32_t)(((uint32_t)(x)) << PXP_AS_BUF_ADDR_SHIFT)) & PXP_AS_BUF_ADDR_MASK)
/*! @} */

/*! @name AS_PITCH - Alpha Surface Pitch */
/*! @{ */

#define PXP_AS_PITCH_PITCH_MASK                  (0xFFFFU)
#define PXP_AS_PITCH_PITCH_SHIFT                 (0U)
#define PXP_AS_PITCH_PITCH(x)                    (((uint32_t)(((uint32_t)(x)) << PXP_AS_PITCH_PITCH_SHIFT)) & PXP_AS_PITCH_PITCH_MASK)
/*! @} */

/*! @name AS_CLRKEYLOW - Overlay Color Key Low */
/*! @{ */

#define PXP_AS_CLRKEYLOW_PIXEL_MASK              (0xFFFFFFU)
#define PXP_AS_CLRKEYLOW_PIXEL_SHIFT             (0U)
#define PXP_AS_CLRKEYLOW_PIXEL(x)                (((uint32_t)(((uint32_t)(x)) << PXP_AS_CLRKEYLOW_PIXEL_SHIFT)) & PXP_AS_CLRKEYLOW_PIXEL_MASK)
/*! @} */

/*! @name AS_CLRKEYHIGH - Overlay Color Key High */
/*! @{ */

#define PXP_AS_CLRKEYHIGH_PIXEL_MASK             (0xFFFFFFU)
#define PXP_AS_CLRKEYHIGH_PIXEL_SHIFT            (0U)
#define PXP_AS_CLRKEYHIGH_PIXEL(x)               (((uint32_t)(((uint32_t)(x)) << PXP_AS_CLRKEYHIGH_PIXEL_SHIFT)) & PXP_AS_CLRKEYHIGH_PIXEL_MASK)
/*! @} */

/*! @name CSC1_COEF0 - Color Space Conversion Coefficient Register 0 */
/*! @{ */

#define PXP_CSC1_COEF0_Y_OFFSET_MASK             (0x1FFU)
#define PXP_CSC1_COEF0_Y_OFFSET_SHIFT            (0U)
#define PXP_CSC1_COEF0_Y_OFFSET(x)               (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF0_Y_OFFSET_SHIFT)) & PXP_CSC1_COEF0_Y_OFFSET_MASK)

#define PXP_CSC1_COEF0_UV_OFFSET_MASK            (0x3FE00U)
#define PXP_CSC1_COEF0_UV_OFFSET_SHIFT           (9U)
#define PXP_CSC1_COEF0_UV_OFFSET(x)              (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF0_UV_OFFSET_SHIFT)) & PXP_CSC1_COEF0_UV_OFFSET_MASK)

#define PXP_CSC1_COEF0_C0_MASK                   (0x1FFC0000U)
#define PXP_CSC1_COEF0_C0_SHIFT                  (18U)
#define PXP_CSC1_COEF0_C0(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF0_C0_SHIFT)) & PXP_CSC1_COEF0_C0_MASK)

#define PXP_CSC1_COEF0_BYPASS_MASK               (0x40000000U)
#define PXP_CSC1_COEF0_BYPASS_SHIFT              (30U)
#define PXP_CSC1_COEF0_BYPASS(x)                 (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF0_BYPASS_SHIFT)) & PXP_CSC1_COEF0_BYPASS_MASK)

#define PXP_CSC1_COEF0_YCBCR_MODE_MASK           (0x80000000U)
#define PXP_CSC1_COEF0_YCBCR_MODE_SHIFT          (31U)
/*! YCBCR_MODE
 *  0b0..YUV to RGB
 *  0b1..YCbCr to RGB
 */
#define PXP_CSC1_COEF0_YCBCR_MODE(x)             (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF0_YCBCR_MODE_SHIFT)) & PXP_CSC1_COEF0_YCBCR_MODE_MASK)
/*! @} */

/*! @name CSC1_COEF1 - Color Space Conversion Coefficient Register 1 */
/*! @{ */

#define PXP_CSC1_COEF1_C4_MASK                   (0x7FFU)
#define PXP_CSC1_COEF1_C4_SHIFT                  (0U)
#define PXP_CSC1_COEF1_C4(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF1_C4_SHIFT)) & PXP_CSC1_COEF1_C4_MASK)

#define PXP_CSC1_COEF1_C1_MASK                   (0x7FF0000U)
#define PXP_CSC1_COEF1_C1_SHIFT                  (16U)
#define PXP_CSC1_COEF1_C1(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF1_C1_SHIFT)) & PXP_CSC1_COEF1_C1_MASK)
/*! @} */

/*! @name CSC1_COEF2 - Color Space Conversion Coefficient Register 2 */
/*! @{ */

#define PXP_CSC1_COEF2_C3_MASK                   (0x7FFU)
#define PXP_CSC1_COEF2_C3_SHIFT                  (0U)
#define PXP_CSC1_COEF2_C3(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF2_C3_SHIFT)) & PXP_CSC1_COEF2_C3_MASK)

#define PXP_CSC1_COEF2_C2_MASK                   (0x7FF0000U)
#define PXP_CSC1_COEF2_C2_SHIFT                  (16U)
#define PXP_CSC1_COEF2_C2(x)                     (((uint32_t)(((uint32_t)(x)) << PXP_CSC1_COEF2_C2_SHIFT)) & PXP_CSC1_COEF2_C2_MASK)
/*! @} */

/*! @name POWER - PXP Power Control Register */
/*! @{ */

#define PXP_POWER_ROT_MEM_LP_STATE_MASK          (0xE00U)
#define PXP_POWER_ROT_MEM_LP_STATE_SHIFT         (9U)
/*! ROT_MEM_LP_STATE
 *  0b000..Memory is not in low power state.
 *  0b001..Light Sleep Mode. Low leakage mode, maintain memory contents.
 *  0b010..Deep Sleep Mode. Low leakage mode, maintain memory contents.
 *  0b100..Shut Down Mode. Shut Down periphery and core, no memory retention.
 */
#define PXP_POWER_ROT_MEM_LP_STATE(x)            (((uint32_t)(((uint32_t)(x)) << PXP_POWER_ROT_MEM_LP_STATE_SHIFT)) & PXP_POWER_ROT_MEM_LP_STATE_MASK)
/*! @} */

/*! @name NEXT - Next Frame Pointer */
/*! @{ */

#define PXP_NEXT_ENABLED_MASK                    (0x1U)
#define PXP_NEXT_ENABLED_SHIFT                   (0U)
#define PXP_NEXT_ENABLED(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_NEXT_ENABLED_SHIFT)) & PXP_NEXT_ENABLED_MASK)

#define PXP_NEXT_POINTER_MASK                    (0xFFFFFFFCU)
#define PXP_NEXT_POINTER_SHIFT                   (2U)
#define PXP_NEXT_POINTER(x)                      (((uint32_t)(((uint32_t)(x)) << PXP_NEXT_POINTER_SHIFT)) & PXP_NEXT_POINTER_MASK)
/*! @} */

/*! @name PORTER_DUFF_CTRL - PXP Alpha Engine A Control Register. */
/*! @{ */

#define PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE_MASK (0x1U)
#define PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE_SHIFT (0U)
/*! PORTER_DUFF_ENABLE
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE_SHIFT)) & PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE_MASK)

#define PXP_PORTER_DUFF_CTRL_S0_S1_FACTOR_MODE_MASK (0x6U)
#define PXP_PORTER_DUFF_CTRL_S0_S1_FACTOR_MODE_SHIFT (1U)
/*! S0_S1_FACTOR_MODE
 *  0b00..1
 *  0b01..0
 *  0b10..Straight alpha
 *  0b11..Inverse alpha
 */
#define PXP_PORTER_DUFF_CTRL_S0_S1_FACTOR_MODE(x) (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S0_S1_FACTOR_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S0_S1_FACTOR_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MODE_MASK (0x18U)
#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MODE_SHIFT (3U)
/*! S0_GLOBAL_ALPHA_MODE
 *  0b00..Global alpha
 *  0b01..Local alpha
 *  0b10..Scaled alpha
 *  0b11..Scaled alpha
 */
#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MODE(x) (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S0_ALPHA_MODE_MASK  (0x20U)
#define PXP_PORTER_DUFF_CTRL_S0_ALPHA_MODE_SHIFT (5U)
/*! S0_ALPHA_MODE
 *  0b0..Straight mode
 *  0b1..Inverted mode
 */
#define PXP_PORTER_DUFF_CTRL_S0_ALPHA_MODE(x)    (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S0_ALPHA_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S0_ALPHA_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S0_COLOR_MODE_MASK  (0x40U)
#define PXP_PORTER_DUFF_CTRL_S0_COLOR_MODE_SHIFT (6U)
/*! S0_COLOR_MODE
 *  0b0..Original pixel
 *  0b1..Scaled pixel
 */
#define PXP_PORTER_DUFF_CTRL_S0_COLOR_MODE(x)    (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S0_COLOR_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S0_COLOR_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S1_S0_FACTOR_MODE_MASK (0x300U)
#define PXP_PORTER_DUFF_CTRL_S1_S0_FACTOR_MODE_SHIFT (8U)
/*! S1_S0_FACTOR_MODE
 *  0b00..1
 *  0b01..0
 *  0b10..Straight alpha
 *  0b11..Inverse alpha
 */
#define PXP_PORTER_DUFF_CTRL_S1_S0_FACTOR_MODE(x) (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S1_S0_FACTOR_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S1_S0_FACTOR_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MODE_MASK (0xC00U)
#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MODE_SHIFT (10U)
/*! S1_GLOBAL_ALPHA_MODE
 *  0b00..Global alpha
 *  0b01..Local alpha
 *  0b10..Scaled alpha
 *  0b11..Scaled alpha
 */
#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MODE(x) (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S1_ALPHA_MODE_MASK  (0x1000U)
#define PXP_PORTER_DUFF_CTRL_S1_ALPHA_MODE_SHIFT (12U)
/*! S1_ALPHA_MODE
 *  0b0..Straight mode
 *  0b1..Inverted mode
 */
#define PXP_PORTER_DUFF_CTRL_S1_ALPHA_MODE(x)    (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S1_ALPHA_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S1_ALPHA_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S1_COLOR_MODE_MASK  (0x2000U)
#define PXP_PORTER_DUFF_CTRL_S1_COLOR_MODE_SHIFT (13U)
/*! S1_COLOR_MODE
 *  0b0..Original pixel
 *  0b1..Scaled pixel
 */
#define PXP_PORTER_DUFF_CTRL_S1_COLOR_MODE(x)    (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S1_COLOR_MODE_SHIFT)) & PXP_PORTER_DUFF_CTRL_S1_COLOR_MODE_MASK)

#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MASK (0xFF0000U)
#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_SHIFT (16U)
#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA(x)  (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_SHIFT)) & PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MASK)

#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MASK (0xFF000000U)
#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_SHIFT (24U)
#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA(x)  (((uint32_t)(((uint32_t)(x)) << PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_SHIFT)) & PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PXP_Register_Masks */


/*!
 * @}
 */ /* end of group PXP_Peripheral_Access_Layer */


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


#endif  /* PERI_PXP_H_ */

