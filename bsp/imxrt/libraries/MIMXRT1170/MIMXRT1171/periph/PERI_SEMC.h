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
**         CMSIS Peripheral Access Layer for SEMC
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
 * @file PERI_SEMC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for SEMC
 *
 * CMSIS Peripheral Access Layer for SEMC
 */

#if !defined(PERI_SEMC_H_)
#define PERI_SEMC_H_                             /**< Symbol preventing repeated inclusion */

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
   -- SEMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SEMC_Peripheral_Access_Layer SEMC Peripheral Access Layer
 * @{
 */

/** SEMC - Size of Registers Arrays */
#define SEMC_BR_COUNT                             9u

/** SEMC - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Control Register, offset: 0x0 */
  __IO uint32_t IOCR;                              /**< IO MUX Control Register, offset: 0x4 */
  __IO uint32_t BMCR0;                             /**< Bus (AXI) Master Control Register 0, offset: 0x8 */
  __IO uint32_t BMCR1;                             /**< Bus (AXI) Master Control Register 1, offset: 0xC */
  __IO uint32_t BR[SEMC_BR_COUNT];                 /**< Base Register 0..Base Register 8, array offset: 0x10, array step: 0x4 */
  __IO uint32_t DLLCR;                             /**< DLL Control Register, offset: 0x34 */
  __IO uint32_t INTEN;                             /**< Interrupt Enable Register, offset: 0x38 */
  __IO uint32_t INTR;                              /**< Interrupt Register, offset: 0x3C */
  __IO uint32_t SDRAMCR0;                          /**< SDRAM Control Register 0, offset: 0x40 */
  __IO uint32_t SDRAMCR1;                          /**< SDRAM Control Register 1, offset: 0x44 */
  __IO uint32_t SDRAMCR2;                          /**< SDRAM Control Register 2, offset: 0x48 */
  __IO uint32_t SDRAMCR3;                          /**< SDRAM Control Register 3, offset: 0x4C */
  __IO uint32_t NANDCR0;                           /**< NAND Control Register 0, offset: 0x50 */
  __IO uint32_t NANDCR1;                           /**< NAND Control Register 1, offset: 0x54 */
  __IO uint32_t NANDCR2;                           /**< NAND Control Register 2, offset: 0x58 */
  __IO uint32_t NANDCR3;                           /**< NAND Control Register 3, offset: 0x5C */
  __IO uint32_t NORCR0;                            /**< NOR Control Register 0, offset: 0x60 */
  __IO uint32_t NORCR1;                            /**< NOR Control Register 1, offset: 0x64 */
  __IO uint32_t NORCR2;                            /**< NOR Control Register 2, offset: 0x68 */
  __IO uint32_t NORCR3;                            /**< NOR Control Register 3, offset: 0x6C */
  __IO uint32_t SRAMCR0;                           /**< SRAM Control Register 0, offset: 0x70 */
  __IO uint32_t SRAMCR1;                           /**< SRAM Control Register 1, offset: 0x74 */
  __IO uint32_t SRAMCR2;                           /**< SRAM Control Register 2, offset: 0x78 */
       uint32_t SRAMCR3;                           /**< SRAM Control Register 3, offset: 0x7C */
  __IO uint32_t DBICR0;                            /**< DBI-B Control Register 0, offset: 0x80 */
  __IO uint32_t DBICR1;                            /**< DBI-B Control Register 1, offset: 0x84 */
  __IO uint32_t DBICR2;                            /**< DBI-B Control Register 2, offset: 0x88 */
       uint8_t RESERVED_0[4];
  __IO uint32_t IPCR0;                             /**< IP Command Control Register 0, offset: 0x90 */
  __IO uint32_t IPCR1;                             /**< IP Command Control Register 1, offset: 0x94 */
  __IO uint32_t IPCR2;                             /**< IP Command Control Register 2, offset: 0x98 */
  __IO uint32_t IPCMD;                             /**< IP Command Register, offset: 0x9C */
  __IO uint32_t IPTXDAT;                           /**< TX DATA Register, offset: 0xA0 */
       uint8_t RESERVED_1[12];
  __I  uint32_t IPRXDAT;                           /**< RX DATA Register, offset: 0xB0 */
       uint8_t RESERVED_2[12];
  __I  uint32_t STS0;                              /**< Status Register 0, offset: 0xC0 */
       uint32_t STS1;                              /**< Status Register 1, offset: 0xC4 */
  __I  uint32_t STS2;                              /**< Status Register 2, offset: 0xC8 */
       uint32_t STS3;                              /**< Status Register 3, offset: 0xCC */
       uint32_t STS4;                              /**< Status Register 4, offset: 0xD0 */
       uint32_t STS5;                              /**< Status Register 5, offset: 0xD4 */
       uint32_t STS6;                              /**< Status Register 6, offset: 0xD8 */
       uint32_t STS7;                              /**< Status Register 7, offset: 0xDC */
       uint32_t STS8;                              /**< Status Register 8, offset: 0xE0 */
       uint32_t STS9;                              /**< Status Register 9, offset: 0xE4 */
       uint32_t STS10;                             /**< Status Register 10, offset: 0xE8 */
       uint32_t STS11;                             /**< Status Register 11, offset: 0xEC */
  __I  uint32_t STS12;                             /**< Status Register 12, offset: 0xF0 */
  __I  uint32_t STS13;                             /**< Status Register 13, offset: 0xF4 */
       uint32_t STS14;                             /**< Status Register 14, offset: 0xF8 */
       uint32_t STS15;                             /**< Status Register 15, offset: 0xFC */
  __IO uint32_t BR9;                               /**< Base Register 9, offset: 0x100 */
  __IO uint32_t BR10;                              /**< Base Register 10, offset: 0x104 */
  __IO uint32_t BR11;                              /**< Base Register 11, offset: 0x108 */
       uint8_t RESERVED_3[20];
  __IO uint32_t SRAMCR4;                           /**< SRAM Control Register 4, offset: 0x120 */
  __IO uint32_t SRAMCR5;                           /**< SRAM Control Register 5, offset: 0x124 */
  __IO uint32_t SRAMCR6;                           /**< SRAM Control Register 6, offset: 0x128 */
       uint8_t RESERVED_4[36];
  __IO uint32_t DCCR;                              /**< Delay Chain Control Register, offset: 0x150 */
} SEMC_Type;

/* ----------------------------------------------------------------------------
   -- SEMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SEMC_Register_Masks SEMC Register Masks
 * @{
 */

/*! @name MCR - Module Control Register */
/*! @{ */

#define SEMC_MCR_SWRST_MASK                      (0x1U)
#define SEMC_MCR_SWRST_SHIFT                     (0U)
/*! SWRST - Software Reset
 *  0b0..No reset
 *  0b1..Reset
 */
#define SEMC_MCR_SWRST(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_SWRST_SHIFT)) & SEMC_MCR_SWRST_MASK)

#define SEMC_MCR_MDIS_MASK                       (0x2U)
#define SEMC_MCR_MDIS_SHIFT                      (1U)
/*! MDIS - Module Disable
 *  0b0..Module enabled
 *  0b1..Module disabled
 */
#define SEMC_MCR_MDIS(x)                         (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_MDIS_SHIFT)) & SEMC_MCR_MDIS_MASK)

#define SEMC_MCR_DQSMD_MASK                      (0x4U)
#define SEMC_MCR_DQSMD_SHIFT                     (2U)
/*! DQSMD - DQS (read strobe) mode
 *  0b0..Dummy read strobe loopbacked internally
 *  0b1..Dummy read strobe loopbacked from DQS pad
 */
#define SEMC_MCR_DQSMD(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_DQSMD_SHIFT)) & SEMC_MCR_DQSMD_MASK)

#define SEMC_MCR_WPOL0_MASK                      (0x40U)
#define SEMC_MCR_WPOL0_SHIFT                     (6U)
/*! WPOL0 - WAIT/RDY polarity for SRAM/NOR
 *  0b0..WAIT/RDY polarity is not changed.
 *  0b1..WAIT/RDY polarity is inverted.
 */
#define SEMC_MCR_WPOL0(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_WPOL0_SHIFT)) & SEMC_MCR_WPOL0_MASK)

#define SEMC_MCR_WPOL1_MASK                      (0x80U)
#define SEMC_MCR_WPOL1_SHIFT                     (7U)
/*! WPOL1 - R/B# polarity for NAND device
 *  0b0..R/B# polarity is not changed.
 *  0b1..R/B# polarity is inverted.
 */
#define SEMC_MCR_WPOL1(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_WPOL1_SHIFT)) & SEMC_MCR_WPOL1_MASK)

#define SEMC_MCR_CTO_MASK                        (0xFF0000U)
#define SEMC_MCR_CTO_SHIFT                       (16U)
/*! CTO - Command Execution timeout cycles */
#define SEMC_MCR_CTO(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_CTO_SHIFT)) & SEMC_MCR_CTO_MASK)

#define SEMC_MCR_BTO_MASK                        (0x1F000000U)
#define SEMC_MCR_BTO_SHIFT                       (24U)
/*! BTO - Bus timeout cycles
 *  0b00000..255*1
 *  0b00001..255*2
 *  0b11111..255*2^31
 */
#define SEMC_MCR_BTO(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_MCR_BTO_SHIFT)) & SEMC_MCR_BTO_MASK)
/*! @} */

/*! @name IOCR - IO MUX Control Register */
/*! @{ */

#define SEMC_IOCR_MUX_A8_MASK                    (0xFU)
#define SEMC_IOCR_MUX_A8_SHIFT                   (0U)
/*! MUX_A8 - SEMC_ADDR08 output selection
 *  0b0000-0b0011..SDRAM Address bit 8 (A8) or NOR/SRAM Address bit 24 (A24) in ADMUX 16bit mode
 *  0b0100..NAND CE#
 *  0b0101..NOR CE#
 *  0b0110..SRAM CE# 0
 *  0b0111..DBI CSX
 *  0b1000..SRAM CE# 1
 *  0b1001..SRAM CE# 2
 *  0b1010..SRAM CE# 3
 *  0b1011-0b1111..SDRAM Address bit 8 (A8) or NOR/SRAM Address bit 24 (A24) in ADMUX 16bit mode
 */
#define SEMC_IOCR_MUX_A8(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_A8_SHIFT)) & SEMC_IOCR_MUX_A8_MASK)

#define SEMC_IOCR_MUX_CSX0_MASK                  (0xF0U)
#define SEMC_IOCR_MUX_CSX0_SHIFT                 (4U)
/*! MUX_CSX0 - SEMC_CSX0 output selection
 *  0b0000..NOR/SRAM Address bit 24 (A24) in Non-ADMUX mode
 *  0b0001..SDRAM CS1
 *  0b0010..SDRAM CS2
 *  0b0011..SDRAM CS3
 *  0b0100..NAND CE#
 *  0b0101..NOR CE#
 *  0b0110..SRAM CE# 0
 *  0b0111..DBI CSX
 *  0b1000..SRAM CE# 1
 *  0b1001..SRAM CE# 2
 *  0b1010..SRAM CE# 3
 *  0b1011-0b1111..NOR/SRAM Address bit 24 (A24) in Non-ADMUX mode
 */
#define SEMC_IOCR_MUX_CSX0(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX0_SHIFT)) & SEMC_IOCR_MUX_CSX0_MASK)

#define SEMC_IOCR_MUX_CSX1_MASK                  (0xF00U)
#define SEMC_IOCR_MUX_CSX1_SHIFT                 (8U)
/*! MUX_CSX1 - SEMC_CSX1 output selection
 *  0b0000..NOR/SRAM Address bit 25 (A25) in Non-ADMUX mode
 *  0b0001..SDRAM CS1
 *  0b0010..SDRAM CS2
 *  0b0011..SDRAM CS3
 *  0b0100..NAND CE#
 *  0b0101..NOR CE#
 *  0b0110..SRAM CE# 0
 *  0b0111..DBI CSX
 *  0b1000..SRAM CE# 1
 *  0b1001..SRAM CE# 2
 *  0b1010..SRAM CE# 3
 *  0b1011-0b1111..NOR/SRAM Address bit 25 (A25) in Non-ADMUX mode
 */
#define SEMC_IOCR_MUX_CSX1(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX1_SHIFT)) & SEMC_IOCR_MUX_CSX1_MASK)

#define SEMC_IOCR_MUX_CSX2_MASK                  (0xF000U)
#define SEMC_IOCR_MUX_CSX2_SHIFT                 (12U)
/*! MUX_CSX2 - SEMC_CSX2 output selection
 *  0b0000..NOR/SRAM Address bit 26 (A26) in Non-ADMUX mode
 *  0b0001..SDRAM CS1
 *  0b0010..SDRAM CS2
 *  0b0011..SDRAM CS3
 *  0b0100..NAND CE#
 *  0b0101..NOR CE#
 *  0b0110..SRAM CE# 0
 *  0b0111..DBI CSX
 *  0b1000..SRAM CE# 1
 *  0b1001..SRAM CE# 2
 *  0b1010..SRAM CE# 3
 *  0b1011-0b1111..NOR/SRAM Address bit 26 (A26) in Non-ADMUX mode
 */
#define SEMC_IOCR_MUX_CSX2(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX2_SHIFT)) & SEMC_IOCR_MUX_CSX2_MASK)

#define SEMC_IOCR_MUX_CSX3_MASK                  (0xF0000U)
#define SEMC_IOCR_MUX_CSX3_SHIFT                 (16U)
/*! MUX_CSX3 - SEMC_CSX3 output selection
 *  0b0000..NOR/SRAM Address bit 27 (A27) in Non-ADMUX mode
 *  0b0001..SDRAM CS1
 *  0b0010..SDRAM CS2
 *  0b0011..SDRAM CS3
 *  0b0100..NAND CE#
 *  0b0101..NOR CE#
 *  0b0110..SRAM CE# 0
 *  0b0111..DBI CSX
 *  0b1000..SRAM CE# 1
 *  0b1001..SRAM CE# 2
 *  0b1010..SRAM CE# 3
 *  0b1011-0b1111..NOR/SRAM Address bit 27 (A27) in Non-ADMUX mode
 */
#define SEMC_IOCR_MUX_CSX3(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CSX3_SHIFT)) & SEMC_IOCR_MUX_CSX3_MASK)

#define SEMC_IOCR_MUX_RDY_MASK                   (0xF00000U)
#define SEMC_IOCR_MUX_RDY_SHIFT                  (20U)
/*! MUX_RDY - SEMC_RDY function selection
 *  0b0000..NAND R/B# input
 *  0b0001..SDRAM CS1
 *  0b0010..SDRAM CS2
 *  0b0011..SDRAM CS3
 *  0b0100..NOR/SRAM Address bit 27 (A27) in Non-ADMUX mode
 *  0b0101..NOR CE#
 *  0b0110..SRAM CE# 0
 *  0b0111..DBI CSX
 *  0b1000..SRAM CE# 1
 *  0b1001..SRAM CE# 2
 *  0b1010..SRAM CE# 3
 *  0b1011-0b1111..NOR/SRAM Address bit 27 in Non-ADMUX mode
 */
#define SEMC_IOCR_MUX_RDY(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_RDY_SHIFT)) & SEMC_IOCR_MUX_RDY_MASK)

#define SEMC_IOCR_MUX_CLKX0_MASK                 (0x3000000U)
#define SEMC_IOCR_MUX_CLKX0_SHIFT                (24U)
/*! MUX_CLKX0 - SEMC_CLKX0 function selection
 *  0b00..Keep low
 *  0b01..NOR clock
 *  0b10..SRAM clock
 *  0b11..NOR and SRAM clock, suitable for Multi-Chip Product package
 */
#define SEMC_IOCR_MUX_CLKX0(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CLKX0_SHIFT)) & SEMC_IOCR_MUX_CLKX0_MASK)

#define SEMC_IOCR_MUX_CLKX1_MASK                 (0xC000000U)
#define SEMC_IOCR_MUX_CLKX1_SHIFT                (26U)
/*! MUX_CLKX1 - SEMC_CLKX1 function selection
 *  0b00..Keep low
 *  0b01..NOR clock
 *  0b10..SRAM clock
 *  0b11..NOR and SRAM clock, suitable for Multi-Chip Product package
 */
#define SEMC_IOCR_MUX_CLKX1(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_MUX_CLKX1_SHIFT)) & SEMC_IOCR_MUX_CLKX1_MASK)

#define SEMC_IOCR_CLKX0_AO_MASK                  (0x10000000U)
#define SEMC_IOCR_CLKX0_AO_SHIFT                 (28U)
/*! CLKX0_AO - SEMC_CLKX0 Always On
 *  0b0..SEMC_CLKX0 is controlled by MUX_CLKX0
 *  0b1..SEMC_CLKX0 is always on
 */
#define SEMC_IOCR_CLKX0_AO(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_CLKX0_AO_SHIFT)) & SEMC_IOCR_CLKX0_AO_MASK)

#define SEMC_IOCR_CLKX1_AO_MASK                  (0x20000000U)
#define SEMC_IOCR_CLKX1_AO_SHIFT                 (29U)
/*! CLKX1_AO - SEMC_CLKX1 Always On
 *  0b0..SEMC_CLKX1 is controlled by MUX_CLKX1
 *  0b1..SEMC_CLKX1 is always on
 */
#define SEMC_IOCR_CLKX1_AO(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_IOCR_CLKX1_AO_SHIFT)) & SEMC_IOCR_CLKX1_AO_MASK)
/*! @} */

/*! @name BMCR0 - Bus (AXI) Master Control Register 0 */
/*! @{ */

#define SEMC_BMCR0_WQOS_MASK                     (0xFU)
#define SEMC_BMCR0_WQOS_SHIFT                    (0U)
/*! WQOS - Weight of QOS */
#define SEMC_BMCR0_WQOS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WQOS_SHIFT)) & SEMC_BMCR0_WQOS_MASK)

#define SEMC_BMCR0_WAGE_MASK                     (0xF0U)
#define SEMC_BMCR0_WAGE_SHIFT                    (4U)
/*! WAGE - Weight of AGE */
#define SEMC_BMCR0_WAGE(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WAGE_SHIFT)) & SEMC_BMCR0_WAGE_MASK)

#define SEMC_BMCR0_WSH_MASK                      (0xFF00U)
#define SEMC_BMCR0_WSH_SHIFT                     (8U)
/*! WSH - Weight of Slave Hit without read/write switch */
#define SEMC_BMCR0_WSH(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WSH_SHIFT)) & SEMC_BMCR0_WSH_MASK)

#define SEMC_BMCR0_WRWS_MASK                     (0xFF0000U)
#define SEMC_BMCR0_WRWS_SHIFT                    (16U)
/*! WRWS - Weight of slave hit with Read/Write Switch */
#define SEMC_BMCR0_WRWS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR0_WRWS_SHIFT)) & SEMC_BMCR0_WRWS_MASK)
/*! @} */

/*! @name BMCR1 - Bus (AXI) Master Control Register 1 */
/*! @{ */

#define SEMC_BMCR1_WQOS_MASK                     (0xFU)
#define SEMC_BMCR1_WQOS_SHIFT                    (0U)
/*! WQOS - Weight of QOS */
#define SEMC_BMCR1_WQOS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WQOS_SHIFT)) & SEMC_BMCR1_WQOS_MASK)

#define SEMC_BMCR1_WAGE_MASK                     (0xF0U)
#define SEMC_BMCR1_WAGE_SHIFT                    (4U)
/*! WAGE - Weight of AGE */
#define SEMC_BMCR1_WAGE(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WAGE_SHIFT)) & SEMC_BMCR1_WAGE_MASK)

#define SEMC_BMCR1_WPH_MASK                      (0xFF00U)
#define SEMC_BMCR1_WPH_SHIFT                     (8U)
/*! WPH - Weight of Page Hit */
#define SEMC_BMCR1_WPH(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WPH_SHIFT)) & SEMC_BMCR1_WPH_MASK)

#define SEMC_BMCR1_WRWS_MASK                     (0xFF0000U)
#define SEMC_BMCR1_WRWS_SHIFT                    (16U)
/*! WRWS - Weight of slave hit without Read/Write Switch */
#define SEMC_BMCR1_WRWS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WRWS_SHIFT)) & SEMC_BMCR1_WRWS_MASK)

#define SEMC_BMCR1_WBR_MASK                      (0xFF000000U)
#define SEMC_BMCR1_WBR_SHIFT                     (24U)
/*! WBR - Weight of Bank Rotation */
#define SEMC_BMCR1_WBR(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_BMCR1_WBR_SHIFT)) & SEMC_BMCR1_WBR_MASK)
/*! @} */

/*! @name BR - Base Register 0..Base Register 8 */
/*! @{ */

#define SEMC_BR_VLD_MASK                         (0x1U)
#define SEMC_BR_VLD_SHIFT                        (0U)
/*! VLD - Valid
 *  0b0..The memory is invalid, can not be accessed.
 *  0b1..The memory is valid, can be accessed.
 */
#define SEMC_BR_VLD(x)                           (((uint32_t)(((uint32_t)(x)) << SEMC_BR_VLD_SHIFT)) & SEMC_BR_VLD_MASK)

#define SEMC_BR_MS_MASK                          (0x3EU)
#define SEMC_BR_MS_SHIFT                         (1U)
/*! MS - Memory size
 *  0b00000..4KB
 *  0b00001..8KB
 *  0b00010..16KB
 *  0b00011..32KB
 *  0b00100..64KB
 *  0b00101..128KB
 *  0b00110..256KB
 *  0b00111..512KB
 *  0b01000..1MB
 *  0b01001..2MB
 *  0b01010..4MB
 *  0b01011..8MB
 *  0b01100..16MB
 *  0b01101..32MB
 *  0b01110..64MB
 *  0b01111..128MB
 *  0b10000..256MB
 *  0b10001..512MB
 *  0b10010..1GB
 *  0b10011..2GB
 *  0b10100-0b11111..4GB
 */
#define SEMC_BR_MS(x)                            (((uint32_t)(((uint32_t)(x)) << SEMC_BR_MS_SHIFT)) & SEMC_BR_MS_MASK)

#define SEMC_BR_BA_MASK                          (0xFFFFF000U)
#define SEMC_BR_BA_SHIFT                         (12U)
/*! BA - Base Address */
#define SEMC_BR_BA(x)                            (((uint32_t)(((uint32_t)(x)) << SEMC_BR_BA_SHIFT)) & SEMC_BR_BA_MASK)
/*! @} */

/*! @name DLLCR - DLL Control Register */
/*! @{ */

#define SEMC_DLLCR_DLLEN_MASK                    (0x1U)
#define SEMC_DLLCR_DLLEN_SHIFT                   (0U)
/*! DLLEN - DLL calibration enable
 *  0b0..DLL calibration is disabled.
 *  0b1..DLL calibration is enabled.
 */
#define SEMC_DLLCR_DLLEN(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_DLLCR_DLLEN_SHIFT)) & SEMC_DLLCR_DLLEN_MASK)

#define SEMC_DLLCR_DLLRESET_MASK                 (0x2U)
#define SEMC_DLLCR_DLLRESET_SHIFT                (1U)
/*! DLLRESET - DLL Reset
 *  0b0..DLL is not reset.
 *  0b1..DLL is reset.
 */
#define SEMC_DLLCR_DLLRESET(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_DLLCR_DLLRESET_SHIFT)) & SEMC_DLLCR_DLLRESET_MASK)

#define SEMC_DLLCR_SLVDLYTARGET_MASK             (0x78U)
#define SEMC_DLLCR_SLVDLYTARGET_SHIFT            (3U)
/*! SLVDLYTARGET - Delay Target for Slave */
#define SEMC_DLLCR_SLVDLYTARGET(x)               (((uint32_t)(((uint32_t)(x)) << SEMC_DLLCR_SLVDLYTARGET_SHIFT)) & SEMC_DLLCR_SLVDLYTARGET_MASK)

#define SEMC_DLLCR_OVRDEN_MASK                   (0x100U)
#define SEMC_DLLCR_OVRDEN_SHIFT                  (8U)
/*! OVRDEN - Override Enable
 *  0b0..The delay cell number is not overridden.
 *  0b1..The delay cell number is overridden.
 */
#define SEMC_DLLCR_OVRDEN(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_DLLCR_OVRDEN_SHIFT)) & SEMC_DLLCR_OVRDEN_MASK)

#define SEMC_DLLCR_OVRDVAL_MASK                  (0x7E00U)
#define SEMC_DLLCR_OVRDVAL_SHIFT                 (9U)
/*! OVRDVAL - Override Value */
#define SEMC_DLLCR_OVRDVAL(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_DLLCR_OVRDVAL_SHIFT)) & SEMC_DLLCR_OVRDVAL_MASK)
/*! @} */

/*! @name INTEN - Interrupt Enable Register */
/*! @{ */

#define SEMC_INTEN_IPCMDDONEEN_MASK              (0x1U)
#define SEMC_INTEN_IPCMDDONEEN_SHIFT             (0U)
/*! IPCMDDONEEN - IP command done interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_IPCMDDONEEN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_IPCMDDONEEN_SHIFT)) & SEMC_INTEN_IPCMDDONEEN_MASK)

#define SEMC_INTEN_IPCMDERREN_MASK               (0x2U)
#define SEMC_INTEN_IPCMDERREN_SHIFT              (1U)
/*! IPCMDERREN - IP command error interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_IPCMDERREN(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_IPCMDERREN_SHIFT)) & SEMC_INTEN_IPCMDERREN_MASK)

#define SEMC_INTEN_AXICMDERREN_MASK              (0x4U)
#define SEMC_INTEN_AXICMDERREN_SHIFT             (2U)
/*! AXICMDERREN - AXI command error interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_AXICMDERREN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_AXICMDERREN_SHIFT)) & SEMC_INTEN_AXICMDERREN_MASK)

#define SEMC_INTEN_AXIBUSERREN_MASK              (0x8U)
#define SEMC_INTEN_AXIBUSERREN_SHIFT             (3U)
/*! AXIBUSERREN - AXI bus error interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_AXIBUSERREN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_AXIBUSERREN_SHIFT)) & SEMC_INTEN_AXIBUSERREN_MASK)

#define SEMC_INTEN_NDPAGEENDEN_MASK              (0x10U)
#define SEMC_INTEN_NDPAGEENDEN_SHIFT             (4U)
/*! NDPAGEENDEN - NAND page end interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_NDPAGEENDEN(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_NDPAGEENDEN_SHIFT)) & SEMC_INTEN_NDPAGEENDEN_MASK)

#define SEMC_INTEN_NDNOPENDEN_MASK               (0x20U)
#define SEMC_INTEN_NDNOPENDEN_SHIFT              (5U)
/*! NDNOPENDEN - NAND no pending AXI access interrupt enable
 *  0b0..Interrupt is disabled
 *  0b1..Interrupt is enabled
 */
#define SEMC_INTEN_NDNOPENDEN(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_INTEN_NDNOPENDEN_SHIFT)) & SEMC_INTEN_NDNOPENDEN_MASK)
/*! @} */

/*! @name INTR - Interrupt Register */
/*! @{ */

#define SEMC_INTR_IPCMDDONE_MASK                 (0x1U)
#define SEMC_INTR_IPCMDDONE_SHIFT                (0U)
/*! IPCMDDONE - IP command normal done interrupt
 *  0b0..IP command is not done.
 *  0b1..IP command is done.
 */
#define SEMC_INTR_IPCMDDONE(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_IPCMDDONE_SHIFT)) & SEMC_INTR_IPCMDDONE_MASK)

#define SEMC_INTR_IPCMDERR_MASK                  (0x2U)
#define SEMC_INTR_IPCMDERR_SHIFT                 (1U)
/*! IPCMDERR - IP command error done interrupt
 *  0b0..No IP command error.
 *  0b1..IP command error occurs.
 */
#define SEMC_INTR_IPCMDERR(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_IPCMDERR_SHIFT)) & SEMC_INTR_IPCMDERR_MASK)

#define SEMC_INTR_AXICMDERR_MASK                 (0x4U)
#define SEMC_INTR_AXICMDERR_SHIFT                (2U)
/*! AXICMDERR - AXI command error interrupt
 *  0b0..No AXI command error.
 *  0b1..AXI command error occurs.
 */
#define SEMC_INTR_AXICMDERR(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_AXICMDERR_SHIFT)) & SEMC_INTR_AXICMDERR_MASK)

#define SEMC_INTR_AXIBUSERR_MASK                 (0x8U)
#define SEMC_INTR_AXIBUSERR_SHIFT                (3U)
/*! AXIBUSERR - AXI bus error interrupt
 *  0b0..No AXI bus error.
 *  0b1..AXI bus error occurs.
 */
#define SEMC_INTR_AXIBUSERR(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_AXIBUSERR_SHIFT)) & SEMC_INTR_AXIBUSERR_MASK)

#define SEMC_INTR_NDPAGEEND_MASK                 (0x10U)
#define SEMC_INTR_NDPAGEEND_SHIFT                (4U)
/*! NDPAGEEND - NAND page end interrupt
 *  0b0..The last address of main space in the NAND is not written by AXI command.
 *  0b1..The last address of main space in the NAND is written by AXI command.
 */
#define SEMC_INTR_NDPAGEEND(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_NDPAGEEND_SHIFT)) & SEMC_INTR_NDPAGEEND_MASK)

#define SEMC_INTR_NDNOPEND_MASK                  (0x20U)
#define SEMC_INTR_NDNOPEND_SHIFT                 (5U)
/*! NDNOPEND - NAND no pending AXI write transaction interrupt
 *  0b0..At least one NAND AXI write transaction is pending or no NAND write transaction is sent to the queue.
 *  0b1..All NAND AXI write pending transactions are finished.
 */
#define SEMC_INTR_NDNOPEND(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_INTR_NDNOPEND_SHIFT)) & SEMC_INTR_NDNOPEND_MASK)
/*! @} */

/*! @name SDRAMCR0 - SDRAM Control Register 0 */
/*! @{ */

#define SEMC_SDRAMCR0_PS_MASK                    (0x3U)
#define SEMC_SDRAMCR0_PS_SHIFT                   (0U)
/*! PS - Port Size
 *  0b00..8bit
 *  0b01..16bit
 *  0b10..32bit
 *  0b11..Reserved
 */
#define SEMC_SDRAMCR0_PS(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_PS_SHIFT)) & SEMC_SDRAMCR0_PS_MASK)

#define SEMC_SDRAMCR0_BL_MASK                    (0x70U)
#define SEMC_SDRAMCR0_BL_SHIFT                   (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..8
 *  0b101..8
 *  0b110..8
 *  0b111..8
 */
#define SEMC_SDRAMCR0_BL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_BL_SHIFT)) & SEMC_SDRAMCR0_BL_MASK)

#define SEMC_SDRAMCR0_COL8_MASK                  (0x80U)
#define SEMC_SDRAMCR0_COL8_SHIFT                 (7U)
/*! COL8 - Column 8 selection
 *  0b0..Column address bit number is decided by COL field.
 *  0b1..Column address bit number is 8. COL field is ignored.
 */
#define SEMC_SDRAMCR0_COL8(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_COL8_SHIFT)) & SEMC_SDRAMCR0_COL8_MASK)

#define SEMC_SDRAMCR0_COL_MASK                   (0x300U)
#define SEMC_SDRAMCR0_COL_SHIFT                  (8U)
/*! COL - Column address bit number
 *  0b00..12
 *  0b01..11
 *  0b10..10
 *  0b11..9
 */
#define SEMC_SDRAMCR0_COL(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_COL_SHIFT)) & SEMC_SDRAMCR0_COL_MASK)

#define SEMC_SDRAMCR0_CL_MASK                    (0xC00U)
#define SEMC_SDRAMCR0_CL_SHIFT                   (10U)
/*! CL - CAS Latency
 *  0b00..1
 *  0b01..1
 *  0b10..2
 *  0b11..3
 */
#define SEMC_SDRAMCR0_CL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_CL_SHIFT)) & SEMC_SDRAMCR0_CL_MASK)

#define SEMC_SDRAMCR0_BANK2_MASK                 (0x4000U)
#define SEMC_SDRAMCR0_BANK2_SHIFT                (14U)
/*! BANK2 - 2 Bank selection bit
 *  0b0..SDRAM device has 4 banks.
 *  0b1..SDRAM device has 2 banks.
 */
#define SEMC_SDRAMCR0_BANK2(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR0_BANK2_SHIFT)) & SEMC_SDRAMCR0_BANK2_MASK)
/*! @} */

/*! @name SDRAMCR1 - SDRAM Control Register 1 */
/*! @{ */

#define SEMC_SDRAMCR1_PRE2ACT_MASK               (0xFU)
#define SEMC_SDRAMCR1_PRE2ACT_SHIFT              (0U)
/*! PRE2ACT - PRECHARGE to ACTIVE/REFRESH command wait time */
#define SEMC_SDRAMCR1_PRE2ACT(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_PRE2ACT_SHIFT)) & SEMC_SDRAMCR1_PRE2ACT_MASK)

#define SEMC_SDRAMCR1_ACT2RW_MASK                (0xF0U)
#define SEMC_SDRAMCR1_ACT2RW_SHIFT               (4U)
/*! ACT2RW - ACTIVE to READ/WRITE delay */
#define SEMC_SDRAMCR1_ACT2RW(x)                  (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_ACT2RW_SHIFT)) & SEMC_SDRAMCR1_ACT2RW_MASK)

#define SEMC_SDRAMCR1_RFRC_MASK                  (0x1F00U)
#define SEMC_SDRAMCR1_RFRC_SHIFT                 (8U)
/*! RFRC - REFRESH recovery time */
#define SEMC_SDRAMCR1_RFRC(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_RFRC_SHIFT)) & SEMC_SDRAMCR1_RFRC_MASK)

#define SEMC_SDRAMCR1_WRC_MASK                   (0xE000U)
#define SEMC_SDRAMCR1_WRC_SHIFT                  (13U)
/*! WRC - WRITE recovery time */
#define SEMC_SDRAMCR1_WRC(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_WRC_SHIFT)) & SEMC_SDRAMCR1_WRC_MASK)

#define SEMC_SDRAMCR1_CKEOFF_MASK                (0xF0000U)
#define SEMC_SDRAMCR1_CKEOFF_SHIFT               (16U)
/*! CKEOFF - CKE off minimum time */
#define SEMC_SDRAMCR1_CKEOFF(x)                  (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_CKEOFF_SHIFT)) & SEMC_SDRAMCR1_CKEOFF_MASK)

#define SEMC_SDRAMCR1_ACT2PRE_MASK               (0xF00000U)
#define SEMC_SDRAMCR1_ACT2PRE_SHIFT              (20U)
/*! ACT2PRE - ACTIVE to PRECHARGE minimum time */
#define SEMC_SDRAMCR1_ACT2PRE(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR1_ACT2PRE_SHIFT)) & SEMC_SDRAMCR1_ACT2PRE_MASK)
/*! @} */

/*! @name SDRAMCR2 - SDRAM Control Register 2 */
/*! @{ */

#define SEMC_SDRAMCR2_SRRC_MASK                  (0xFFU)
#define SEMC_SDRAMCR2_SRRC_SHIFT                 (0U)
/*! SRRC - SELF REFRESH recovery time */
#define SEMC_SDRAMCR2_SRRC(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_SRRC_SHIFT)) & SEMC_SDRAMCR2_SRRC_MASK)

#define SEMC_SDRAMCR2_REF2REF_MASK               (0xFF00U)
#define SEMC_SDRAMCR2_REF2REF_SHIFT              (8U)
/*! REF2REF - REFRESH to REFRESH delay */
#define SEMC_SDRAMCR2_REF2REF(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_REF2REF_SHIFT)) & SEMC_SDRAMCR2_REF2REF_MASK)

#define SEMC_SDRAMCR2_ACT2ACT_MASK               (0xFF0000U)
#define SEMC_SDRAMCR2_ACT2ACT_SHIFT              (16U)
/*! ACT2ACT - ACTIVE to ACTIVE delay */
#define SEMC_SDRAMCR2_ACT2ACT(x)                 (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_ACT2ACT_SHIFT)) & SEMC_SDRAMCR2_ACT2ACT_MASK)

#define SEMC_SDRAMCR2_ITO_MASK                   (0xFF000000U)
#define SEMC_SDRAMCR2_ITO_SHIFT                  (24U)
/*! ITO - SDRAM idle timeout
 *  0b00000000..IDLE timeout period is 256*Prescale period.
 *  0b00000001-0b11111111..IDLE timeout period is ITO*Prescale period.
 */
#define SEMC_SDRAMCR2_ITO(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR2_ITO_SHIFT)) & SEMC_SDRAMCR2_ITO_MASK)
/*! @} */

/*! @name SDRAMCR3 - SDRAM Control Register 3 */
/*! @{ */

#define SEMC_SDRAMCR3_REN_MASK                   (0x1U)
#define SEMC_SDRAMCR3_REN_SHIFT                  (0U)
/*! REN - Refresh enable
 *  0b0..The SEMC does not send AUTO REFRESH command automatically
 *  0b1..The SEMC sends AUTO REFRESH command automatically
 */
#define SEMC_SDRAMCR3_REN(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_REN_SHIFT)) & SEMC_SDRAMCR3_REN_MASK)

#define SEMC_SDRAMCR3_REBL_MASK                  (0xEU)
#define SEMC_SDRAMCR3_REBL_SHIFT                 (1U)
/*! REBL - Refresh burst length
 *  0b000..1
 *  0b001..2
 *  0b010..3
 *  0b011..4
 *  0b100..5
 *  0b101..6
 *  0b110..7
 *  0b111..8
 */
#define SEMC_SDRAMCR3_REBL(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_REBL_SHIFT)) & SEMC_SDRAMCR3_REBL_MASK)

#define SEMC_SDRAMCR3_PRESCALE_MASK              (0xFF00U)
#define SEMC_SDRAMCR3_PRESCALE_SHIFT             (8U)
/*! PRESCALE - Prescaler period
 *  0b00000000..(256*16+1) clock cycles
 *  0b00000001-0b11111111..(PRESCALE*16+1) clock cycles
 */
#define SEMC_SDRAMCR3_PRESCALE(x)                (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_PRESCALE_SHIFT)) & SEMC_SDRAMCR3_PRESCALE_MASK)

#define SEMC_SDRAMCR3_RT_MASK                    (0xFF0000U)
#define SEMC_SDRAMCR3_RT_SHIFT                   (16U)
/*! RT - Refresh timer period
 *  0b00000000..(256+1)*(Prescaler period)
 *  0b00000001-0b11111111..(RT+1)*(Prescaler period)
 */
#define SEMC_SDRAMCR3_RT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_RT_SHIFT)) & SEMC_SDRAMCR3_RT_MASK)

#define SEMC_SDRAMCR3_UT_MASK                    (0xFF000000U)
#define SEMC_SDRAMCR3_UT_SHIFT                   (24U)
/*! UT - Urgent refresh threshold
 *  0b00000000..256*(Prescaler period)
 *  0b00000001-0b11111111..UT*(Prescaler period)
 */
#define SEMC_SDRAMCR3_UT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SDRAMCR3_UT_SHIFT)) & SEMC_SDRAMCR3_UT_MASK)
/*! @} */

/*! @name NANDCR0 - NAND Control Register 0 */
/*! @{ */

#define SEMC_NANDCR0_PS_MASK                     (0x1U)
#define SEMC_NANDCR0_PS_SHIFT                    (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_NANDCR0_PS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_PS_SHIFT)) & SEMC_NANDCR0_PS_MASK)

#define SEMC_NANDCR0_SYNCEN_MASK                 (0x2U)
#define SEMC_NANDCR0_SYNCEN_SHIFT                (1U)
/*! SYNCEN - Synchronous Mode Enable
 *  0b0..Asynchronous mode is enabled.
 *  0b1..Synchronous mode is enabled.
 */
#define SEMC_NANDCR0_SYNCEN(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_SYNCEN_SHIFT)) & SEMC_NANDCR0_SYNCEN_MASK)

#define SEMC_NANDCR0_BL_MASK                     (0x70U)
#define SEMC_NANDCR0_BL_SHIFT                    (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_NANDCR0_BL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_BL_SHIFT)) & SEMC_NANDCR0_BL_MASK)

#define SEMC_NANDCR0_EDO_MASK                    (0x80U)
#define SEMC_NANDCR0_EDO_SHIFT                   (7U)
/*! EDO - EDO mode enabled
 *  0b0..EDO mode disabled
 *  0b1..EDO mode enabled
 */
#define SEMC_NANDCR0_EDO(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_EDO_SHIFT)) & SEMC_NANDCR0_EDO_MASK)

#define SEMC_NANDCR0_COL_MASK                    (0x700U)
#define SEMC_NANDCR0_COL_SHIFT                   (8U)
/*! COL - Column address bit number
 *  0b000..16
 *  0b001..15
 *  0b010..14
 *  0b011..13
 *  0b100..12
 *  0b101..11
 *  0b110..10
 *  0b111..9
 */
#define SEMC_NANDCR0_COL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR0_COL_SHIFT)) & SEMC_NANDCR0_COL_MASK)
/*! @} */

/*! @name NANDCR1 - NAND Control Register 1 */
/*! @{ */

#define SEMC_NANDCR1_CES_MASK                    (0xFU)
#define SEMC_NANDCR1_CES_SHIFT                   (0U)
/*! CES - CE# setup time */
#define SEMC_NANDCR1_CES(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_CES_SHIFT)) & SEMC_NANDCR1_CES_MASK)

#define SEMC_NANDCR1_CEH_MASK                    (0xF0U)
#define SEMC_NANDCR1_CEH_SHIFT                   (4U)
/*! CEH - CE# hold time */
#define SEMC_NANDCR1_CEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_CEH_SHIFT)) & SEMC_NANDCR1_CEH_MASK)

#define SEMC_NANDCR1_WEL_MASK                    (0xF00U)
#define SEMC_NANDCR1_WEL_SHIFT                   (8U)
/*! WEL - WE# low time */
#define SEMC_NANDCR1_WEL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_WEL_SHIFT)) & SEMC_NANDCR1_WEL_MASK)

#define SEMC_NANDCR1_WEH_MASK                    (0xF000U)
#define SEMC_NANDCR1_WEH_SHIFT                   (12U)
/*! WEH - WE# high time */
#define SEMC_NANDCR1_WEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_WEH_SHIFT)) & SEMC_NANDCR1_WEH_MASK)

#define SEMC_NANDCR1_REL_MASK                    (0xF0000U)
#define SEMC_NANDCR1_REL_SHIFT                   (16U)
/*! REL - RE# low time */
#define SEMC_NANDCR1_REL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_REL_SHIFT)) & SEMC_NANDCR1_REL_MASK)

#define SEMC_NANDCR1_REH_MASK                    (0xF00000U)
#define SEMC_NANDCR1_REH_SHIFT                   (20U)
/*! REH - RE# high time */
#define SEMC_NANDCR1_REH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_REH_SHIFT)) & SEMC_NANDCR1_REH_MASK)

#define SEMC_NANDCR1_TA_MASK                     (0xF000000U)
#define SEMC_NANDCR1_TA_SHIFT                    (24U)
/*! TA - Turnaround time */
#define SEMC_NANDCR1_TA(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_TA_SHIFT)) & SEMC_NANDCR1_TA_MASK)

#define SEMC_NANDCR1_CEITV_MASK                  (0xF0000000U)
#define SEMC_NANDCR1_CEITV_SHIFT                 (28U)
/*! CEITV - CE# interval time */
#define SEMC_NANDCR1_CEITV(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR1_CEITV_SHIFT)) & SEMC_NANDCR1_CEITV_MASK)
/*! @} */

/*! @name NANDCR2 - NAND Control Register 2 */
/*! @{ */

#define SEMC_NANDCR2_TWHR_MASK                   (0x3FU)
#define SEMC_NANDCR2_TWHR_SHIFT                  (0U)
/*! TWHR - WE# high to RE# low time */
#define SEMC_NANDCR2_TWHR(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TWHR_SHIFT)) & SEMC_NANDCR2_TWHR_MASK)

#define SEMC_NANDCR2_TRHW_MASK                   (0xFC0U)
#define SEMC_NANDCR2_TRHW_SHIFT                  (6U)
/*! TRHW - RE# high to WE# low time */
#define SEMC_NANDCR2_TRHW(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TRHW_SHIFT)) & SEMC_NANDCR2_TRHW_MASK)

#define SEMC_NANDCR2_TADL_MASK                   (0x3F000U)
#define SEMC_NANDCR2_TADL_SHIFT                  (12U)
/*! TADL - Address cycle to data loading time */
#define SEMC_NANDCR2_TADL(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TADL_SHIFT)) & SEMC_NANDCR2_TADL_MASK)

#define SEMC_NANDCR2_TRR_MASK                    (0xFC0000U)
#define SEMC_NANDCR2_TRR_SHIFT                   (18U)
/*! TRR - Ready to RE# low time */
#define SEMC_NANDCR2_TRR(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TRR_SHIFT)) & SEMC_NANDCR2_TRR_MASK)

#define SEMC_NANDCR2_TWB_MASK                    (0x3F000000U)
#define SEMC_NANDCR2_TWB_SHIFT                   (24U)
/*! TWB - WE# high to busy time */
#define SEMC_NANDCR2_TWB(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR2_TWB_SHIFT)) & SEMC_NANDCR2_TWB_MASK)
/*! @} */

/*! @name NANDCR3 - NAND Control Register 3 */
/*! @{ */

#define SEMC_NANDCR3_NDOPT1_MASK                 (0x1U)
#define SEMC_NANDCR3_NDOPT1_SHIFT                (0U)
/*! NDOPT1 - NAND option bit 1 */
#define SEMC_NANDCR3_NDOPT1(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_NDOPT1_SHIFT)) & SEMC_NANDCR3_NDOPT1_MASK)

#define SEMC_NANDCR3_NDOPT2_MASK                 (0x2U)
#define SEMC_NANDCR3_NDOPT2_SHIFT                (1U)
/*! NDOPT2 - NAND option bit 2 */
#define SEMC_NANDCR3_NDOPT2(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_NDOPT2_SHIFT)) & SEMC_NANDCR3_NDOPT2_MASK)

#define SEMC_NANDCR3_NDOPT3_MASK                 (0x4U)
#define SEMC_NANDCR3_NDOPT3_SHIFT                (2U)
/*! NDOPT3 - NAND option bit 3 */
#define SEMC_NANDCR3_NDOPT3(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_NDOPT3_SHIFT)) & SEMC_NANDCR3_NDOPT3_MASK)

#define SEMC_NANDCR3_CLE_MASK                    (0x8U)
#define SEMC_NANDCR3_CLE_SHIFT                   (3U)
/*! CLE - NAND CLE Option */
#define SEMC_NANDCR3_CLE(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_CLE_SHIFT)) & SEMC_NANDCR3_CLE_MASK)

#define SEMC_NANDCR3_RDS_MASK                    (0xF0000U)
#define SEMC_NANDCR3_RDS_SHIFT                   (16U)
/*! RDS - Read Data Setup time */
#define SEMC_NANDCR3_RDS(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_RDS_SHIFT)) & SEMC_NANDCR3_RDS_MASK)

#define SEMC_NANDCR3_RDH_MASK                    (0xF00000U)
#define SEMC_NANDCR3_RDH_SHIFT                   (20U)
/*! RDH - Read Data Hold time */
#define SEMC_NANDCR3_RDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_RDH_SHIFT)) & SEMC_NANDCR3_RDH_MASK)

#define SEMC_NANDCR3_WDS_MASK                    (0xF000000U)
#define SEMC_NANDCR3_WDS_SHIFT                   (24U)
/*! WDS - Write Data Setup time */
#define SEMC_NANDCR3_WDS(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_WDS_SHIFT)) & SEMC_NANDCR3_WDS_MASK)

#define SEMC_NANDCR3_WDH_MASK                    (0xF0000000U)
#define SEMC_NANDCR3_WDH_SHIFT                   (28U)
/*! WDH - Write Data Hold time */
#define SEMC_NANDCR3_WDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NANDCR3_WDH_SHIFT)) & SEMC_NANDCR3_WDH_MASK)
/*! @} */

/*! @name NORCR0 - NOR Control Register 0 */
/*! @{ */

#define SEMC_NORCR0_PS_MASK                      (0x1U)
#define SEMC_NORCR0_PS_SHIFT                     (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_NORCR0_PS(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_PS_SHIFT)) & SEMC_NORCR0_PS_MASK)

#define SEMC_NORCR0_SYNCEN_MASK                  (0x2U)
#define SEMC_NORCR0_SYNCEN_SHIFT                 (1U)
/*! SYNCEN - Synchronous Mode Enable
 *  0b0..Asynchronous mode is enabled.
 *  0b1..Synchronous mode is enabled. Only fixed latency mode is supported.
 */
#define SEMC_NORCR0_SYNCEN(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_SYNCEN_SHIFT)) & SEMC_NORCR0_SYNCEN_MASK)

#define SEMC_NORCR0_BL_MASK                      (0x70U)
#define SEMC_NORCR0_BL_SHIFT                     (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_NORCR0_BL(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_BL_SHIFT)) & SEMC_NORCR0_BL_MASK)

#define SEMC_NORCR0_AM_MASK                      (0x300U)
#define SEMC_NORCR0_AM_SHIFT                     (8U)
/*! AM - Address Mode
 *  0b00..Address/Data MUX mode (ADMUX)
 *  0b01..Advanced Address/Data MUX mode (AADM)
 *  0b10..Address/Data non-MUX mode (Non-ADMUX)
 *  0b11..Address/Data non-MUX mode (Non-ADMUX)
 */
#define SEMC_NORCR0_AM(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_AM_SHIFT)) & SEMC_NORCR0_AM_MASK)

#define SEMC_NORCR0_ADVP_MASK                    (0x400U)
#define SEMC_NORCR0_ADVP_SHIFT                   (10U)
/*! ADVP - ADV# Polarity
 *  0b0..ADV# is active low.
 *  0b1..ADV# is active high.
 */
#define SEMC_NORCR0_ADVP(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_ADVP_SHIFT)) & SEMC_NORCR0_ADVP_MASK)

#define SEMC_NORCR0_ADVH_MASK                    (0x800U)
#define SEMC_NORCR0_ADVH_SHIFT                   (11U)
/*! ADVH - ADV# level control during address hold state
 *  0b0..ADV# is high during address hold state.
 *  0b1..ADV# is low during address hold state.
 */
#define SEMC_NORCR0_ADVH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_ADVH_SHIFT)) & SEMC_NORCR0_ADVH_MASK)

#define SEMC_NORCR0_COL_MASK                     (0xF000U)
#define SEMC_NORCR0_COL_SHIFT                    (12U)
/*! COL - Column Address bit width
 *  0b0000..12 Bits
 *  0b0001..11 Bits
 *  0b0010..10 Bits
 *  0b0011..9 Bits
 *  0b0100..8 Bits
 *  0b0101..7 Bits
 *  0b0110..6 Bits
 *  0b0111..5 Bits
 *  0b1000..4 Bits
 *  0b1001..3 Bits
 *  0b1010..2 Bits
 *  0b1011..12 Bits
 *  0b1100..12 Bits
 *  0b1101..12 Bits
 *  0b1110..12 Bits
 *  0b1111..12 Bits
 */
#define SEMC_NORCR0_COL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR0_COL_SHIFT)) & SEMC_NORCR0_COL_MASK)
/*! @} */

/*! @name NORCR1 - NOR Control Register 1 */
/*! @{ */

#define SEMC_NORCR1_CES_MASK                     (0xFU)
#define SEMC_NORCR1_CES_SHIFT                    (0U)
/*! CES - CE setup time */
#define SEMC_NORCR1_CES(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_CES_SHIFT)) & SEMC_NORCR1_CES_MASK)

#define SEMC_NORCR1_CEH_MASK                     (0xF0U)
#define SEMC_NORCR1_CEH_SHIFT                    (4U)
/*! CEH - CE hold time */
#define SEMC_NORCR1_CEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_CEH_SHIFT)) & SEMC_NORCR1_CEH_MASK)

#define SEMC_NORCR1_AS_MASK                      (0xF00U)
#define SEMC_NORCR1_AS_SHIFT                     (8U)
/*! AS - Address setup time */
#define SEMC_NORCR1_AS(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_AS_SHIFT)) & SEMC_NORCR1_AS_MASK)

#define SEMC_NORCR1_AH_MASK                      (0xF000U)
#define SEMC_NORCR1_AH_SHIFT                     (12U)
/*! AH - Address hold time */
#define SEMC_NORCR1_AH(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_AH_SHIFT)) & SEMC_NORCR1_AH_MASK)

#define SEMC_NORCR1_WEL_MASK                     (0xF0000U)
#define SEMC_NORCR1_WEL_SHIFT                    (16U)
/*! WEL - WE low time */
#define SEMC_NORCR1_WEL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_WEL_SHIFT)) & SEMC_NORCR1_WEL_MASK)

#define SEMC_NORCR1_WEH_MASK                     (0xF00000U)
#define SEMC_NORCR1_WEH_SHIFT                    (20U)
/*! WEH - WE high time */
#define SEMC_NORCR1_WEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_WEH_SHIFT)) & SEMC_NORCR1_WEH_MASK)

#define SEMC_NORCR1_REL_MASK                     (0xF000000U)
#define SEMC_NORCR1_REL_SHIFT                    (24U)
/*! REL - RE low time */
#define SEMC_NORCR1_REL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_REL_SHIFT)) & SEMC_NORCR1_REL_MASK)

#define SEMC_NORCR1_REH_MASK                     (0xF0000000U)
#define SEMC_NORCR1_REH_SHIFT                    (28U)
/*! REH - RE high time */
#define SEMC_NORCR1_REH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR1_REH_SHIFT)) & SEMC_NORCR1_REH_MASK)
/*! @} */

/*! @name NORCR2 - NOR Control Register 2 */
/*! @{ */

#define SEMC_NORCR2_TA_MASK                      (0xF00U)
#define SEMC_NORCR2_TA_SHIFT                     (8U)
/*! TA - Turnaround time */
#define SEMC_NORCR2_TA(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_TA_SHIFT)) & SEMC_NORCR2_TA_MASK)

#define SEMC_NORCR2_AWDH_MASK                    (0xF000U)
#define SEMC_NORCR2_AWDH_SHIFT                   (12U)
/*! AWDH - Address to write data hold time */
#define SEMC_NORCR2_AWDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_AWDH_SHIFT)) & SEMC_NORCR2_AWDH_MASK)

#define SEMC_NORCR2_LC_MASK                      (0xF0000U)
#define SEMC_NORCR2_LC_SHIFT                     (16U)
/*! LC - Latency count */
#define SEMC_NORCR2_LC(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_LC_SHIFT)) & SEMC_NORCR2_LC_MASK)

#define SEMC_NORCR2_RD_MASK                      (0xF00000U)
#define SEMC_NORCR2_RD_SHIFT                     (20U)
/*! RD - Read time */
#define SEMC_NORCR2_RD(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_RD_SHIFT)) & SEMC_NORCR2_RD_MASK)

#define SEMC_NORCR2_CEITV_MASK                   (0xF000000U)
#define SEMC_NORCR2_CEITV_SHIFT                  (24U)
/*! CEITV - CE# interval time */
#define SEMC_NORCR2_CEITV(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_CEITV_SHIFT)) & SEMC_NORCR2_CEITV_MASK)

#define SEMC_NORCR2_RDH_MASK                     (0xF0000000U)
#define SEMC_NORCR2_RDH_SHIFT                    (28U)
/*! RDH - Read hold time */
#define SEMC_NORCR2_RDH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR2_RDH_SHIFT)) & SEMC_NORCR2_RDH_MASK)
/*! @} */

/*! @name NORCR3 - NOR Control Register 3 */
/*! @{ */

#define SEMC_NORCR3_ASSR_MASK                    (0xFU)
#define SEMC_NORCR3_ASSR_SHIFT                   (0U)
/*! ASSR - Address setup time for SYNC read */
#define SEMC_NORCR3_ASSR(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR3_ASSR_SHIFT)) & SEMC_NORCR3_ASSR_MASK)

#define SEMC_NORCR3_AHSR_MASK                    (0xF0U)
#define SEMC_NORCR3_AHSR_SHIFT                   (4U)
/*! AHSR - Address hold time for SYNC read */
#define SEMC_NORCR3_AHSR(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_NORCR3_AHSR_SHIFT)) & SEMC_NORCR3_AHSR_MASK)
/*! @} */

/*! @name SRAMCR0 - SRAM Control Register 0 */
/*! @{ */

#define SEMC_SRAMCR0_PS_MASK                     (0x1U)
#define SEMC_SRAMCR0_PS_SHIFT                    (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_SRAMCR0_PS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_PS_SHIFT)) & SEMC_SRAMCR0_PS_MASK)

#define SEMC_SRAMCR0_SYNCEN_MASK                 (0x2U)
#define SEMC_SRAMCR0_SYNCEN_SHIFT                (1U)
/*! SYNCEN - Synchronous Mode Enable
 *  0b0..Asynchronous mode is enabled.
 *  0b1..Synchronous mode is enabled. Only fixed latency mode is supported.
 */
#define SEMC_SRAMCR0_SYNCEN(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_SYNCEN_SHIFT)) & SEMC_SRAMCR0_SYNCEN_MASK)

#define SEMC_SRAMCR0_WAITEN_MASK                 (0x4U)
#define SEMC_SRAMCR0_WAITEN_SHIFT                (2U)
/*! WAITEN - Wait Enable
 *  0b0..The SEMC does not monitor wait pin.
 *  0b1..The SEMC monitors wait pin. The SEMC does not transfer/receive data when wait pin is asserted.
 */
#define SEMC_SRAMCR0_WAITEN(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_WAITEN_SHIFT)) & SEMC_SRAMCR0_WAITEN_MASK)

#define SEMC_SRAMCR0_WAITSP_MASK                 (0x8U)
#define SEMC_SRAMCR0_WAITSP_SHIFT                (3U)
/*! WAITSP - Wait Sample
 *  0b0..Wait pin is directly used by the SEMC.
 *  0b1..Wait pin is sampled by internal clock before it is used.
 */
#define SEMC_SRAMCR0_WAITSP(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_WAITSP_SHIFT)) & SEMC_SRAMCR0_WAITSP_MASK)

#define SEMC_SRAMCR0_BL_MASK                     (0x70U)
#define SEMC_SRAMCR0_BL_SHIFT                    (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_SRAMCR0_BL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_BL_SHIFT)) & SEMC_SRAMCR0_BL_MASK)

#define SEMC_SRAMCR0_AM_MASK                     (0x300U)
#define SEMC_SRAMCR0_AM_SHIFT                    (8U)
/*! AM - Address Mode
 *  0b00..Address/Data MUX mode (ADMUX)
 *  0b01..Advanced Address/Data MUX mode (AADM)
 *  0b10..Address/Data non-MUX mode (Non-ADMUX)
 *  0b11..Address/Data non-MUX mode (Non-ADMUX)
 */
#define SEMC_SRAMCR0_AM(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_AM_SHIFT)) & SEMC_SRAMCR0_AM_MASK)

#define SEMC_SRAMCR0_ADVP_MASK                   (0x400U)
#define SEMC_SRAMCR0_ADVP_SHIFT                  (10U)
/*! ADVP - ADV# polarity
 *  0b0..ADV# is active low.
 *  0b1..ADV# is active high.
 */
#define SEMC_SRAMCR0_ADVP(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_ADVP_SHIFT)) & SEMC_SRAMCR0_ADVP_MASK)

#define SEMC_SRAMCR0_ADVH_MASK                   (0x800U)
#define SEMC_SRAMCR0_ADVH_SHIFT                  (11U)
/*! ADVH - ADV# level control during address hold state
 *  0b0..ADV# is high during address hold state.
 *  0b1..ADV# is low during address hold state.
 */
#define SEMC_SRAMCR0_ADVH(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_ADVH_SHIFT)) & SEMC_SRAMCR0_ADVH_MASK)

#define SEMC_SRAMCR0_COL_MASK                    (0xF000U)
#define SEMC_SRAMCR0_COL_SHIFT                   (12U)
/*! COL - Column Address bit width
 *  0b0000..12 Bits
 *  0b0001..11 Bits
 *  0b0010..10 Bits
 *  0b0011..9 Bits
 *  0b0100..8 Bits
 *  0b0101..7 Bits
 *  0b0110..6 Bits
 *  0b0111..5 Bits
 *  0b1000..4 Bits
 *  0b1001..3 Bits
 *  0b1010..2 Bits
 *  0b1011..12 Bits
 *  0b1100..12 Bits
 *  0b1101..12 Bits
 *  0b1110..12 Bits
 *  0b1111..12 Bits
 */
#define SEMC_SRAMCR0_COL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR0_COL_SHIFT)) & SEMC_SRAMCR0_COL_MASK)
/*! @} */

/*! @name SRAMCR1 - SRAM Control Register 1 */
/*! @{ */

#define SEMC_SRAMCR1_CES_MASK                    (0xFU)
#define SEMC_SRAMCR1_CES_SHIFT                   (0U)
/*! CES - CE setup time */
#define SEMC_SRAMCR1_CES(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_CES_SHIFT)) & SEMC_SRAMCR1_CES_MASK)

#define SEMC_SRAMCR1_CEH_MASK                    (0xF0U)
#define SEMC_SRAMCR1_CEH_SHIFT                   (4U)
/*! CEH - CE hold time */
#define SEMC_SRAMCR1_CEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_CEH_SHIFT)) & SEMC_SRAMCR1_CEH_MASK)

#define SEMC_SRAMCR1_AS_MASK                     (0xF00U)
#define SEMC_SRAMCR1_AS_SHIFT                    (8U)
/*! AS - Address setup time */
#define SEMC_SRAMCR1_AS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_AS_SHIFT)) & SEMC_SRAMCR1_AS_MASK)

#define SEMC_SRAMCR1_AH_MASK                     (0xF000U)
#define SEMC_SRAMCR1_AH_SHIFT                    (12U)
/*! AH - Address hold time */
#define SEMC_SRAMCR1_AH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_AH_SHIFT)) & SEMC_SRAMCR1_AH_MASK)

#define SEMC_SRAMCR1_WEL_MASK                    (0xF0000U)
#define SEMC_SRAMCR1_WEL_SHIFT                   (16U)
/*! WEL - WE low time */
#define SEMC_SRAMCR1_WEL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_WEL_SHIFT)) & SEMC_SRAMCR1_WEL_MASK)

#define SEMC_SRAMCR1_WEH_MASK                    (0xF00000U)
#define SEMC_SRAMCR1_WEH_SHIFT                   (20U)
/*! WEH - WE high time */
#define SEMC_SRAMCR1_WEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_WEH_SHIFT)) & SEMC_SRAMCR1_WEH_MASK)

#define SEMC_SRAMCR1_REL_MASK                    (0xF000000U)
#define SEMC_SRAMCR1_REL_SHIFT                   (24U)
/*! REL - RE low time */
#define SEMC_SRAMCR1_REL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_REL_SHIFT)) & SEMC_SRAMCR1_REL_MASK)

#define SEMC_SRAMCR1_REH_MASK                    (0xF0000000U)
#define SEMC_SRAMCR1_REH_SHIFT                   (28U)
/*! REH - RE high time */
#define SEMC_SRAMCR1_REH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR1_REH_SHIFT)) & SEMC_SRAMCR1_REH_MASK)
/*! @} */

/*! @name SRAMCR2 - SRAM Control Register 2 */
/*! @{ */

#define SEMC_SRAMCR2_WDS_MASK                    (0xFU)
#define SEMC_SRAMCR2_WDS_SHIFT                   (0U)
/*! WDS - Write Data setup time */
#define SEMC_SRAMCR2_WDS(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_WDS_SHIFT)) & SEMC_SRAMCR2_WDS_MASK)

#define SEMC_SRAMCR2_WDH_MASK                    (0xF0U)
#define SEMC_SRAMCR2_WDH_SHIFT                   (4U)
/*! WDH - Write Data hold time */
#define SEMC_SRAMCR2_WDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_WDH_SHIFT)) & SEMC_SRAMCR2_WDH_MASK)

#define SEMC_SRAMCR2_TA_MASK                     (0xF00U)
#define SEMC_SRAMCR2_TA_SHIFT                    (8U)
/*! TA - Turnaround time */
#define SEMC_SRAMCR2_TA(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_TA_SHIFT)) & SEMC_SRAMCR2_TA_MASK)

#define SEMC_SRAMCR2_AWDH_MASK                   (0xF000U)
#define SEMC_SRAMCR2_AWDH_SHIFT                  (12U)
/*! AWDH - Address to write data hold time */
#define SEMC_SRAMCR2_AWDH(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_AWDH_SHIFT)) & SEMC_SRAMCR2_AWDH_MASK)

#define SEMC_SRAMCR2_LC_MASK                     (0xF0000U)
#define SEMC_SRAMCR2_LC_SHIFT                    (16U)
/*! LC - Latency count */
#define SEMC_SRAMCR2_LC(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_LC_SHIFT)) & SEMC_SRAMCR2_LC_MASK)

#define SEMC_SRAMCR2_RD_MASK                     (0xF00000U)
#define SEMC_SRAMCR2_RD_SHIFT                    (20U)
/*! RD - Read time */
#define SEMC_SRAMCR2_RD(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_RD_SHIFT)) & SEMC_SRAMCR2_RD_MASK)

#define SEMC_SRAMCR2_CEITV_MASK                  (0xF000000U)
#define SEMC_SRAMCR2_CEITV_SHIFT                 (24U)
/*! CEITV - CE# interval time */
#define SEMC_SRAMCR2_CEITV(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_CEITV_SHIFT)) & SEMC_SRAMCR2_CEITV_MASK)

#define SEMC_SRAMCR2_RDH_MASK                    (0xF0000000U)
#define SEMC_SRAMCR2_RDH_SHIFT                   (28U)
/*! RDH - Read hold time */
#define SEMC_SRAMCR2_RDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR2_RDH_SHIFT)) & SEMC_SRAMCR2_RDH_MASK)
/*! @} */

/*! @name DBICR0 - DBI-B Control Register 0 */
/*! @{ */

#define SEMC_DBICR0_PS_MASK                      (0x1U)
#define SEMC_DBICR0_PS_SHIFT                     (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_DBICR0_PS(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR0_PS_SHIFT)) & SEMC_DBICR0_PS_MASK)

#define SEMC_DBICR0_BL_MASK                      (0x70U)
#define SEMC_DBICR0_BL_SHIFT                     (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_DBICR0_BL(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR0_BL_SHIFT)) & SEMC_DBICR0_BL_MASK)

#define SEMC_DBICR0_COL_MASK                     (0xF000U)
#define SEMC_DBICR0_COL_SHIFT                    (12U)
/*! COL - Column Address bit width
 *  0b0000..12 Bits
 *  0b0001..11 Bits
 *  0b0010..10 Bits
 *  0b0011..9 Bits
 *  0b0100..8 Bits
 *  0b0101..7 Bits
 *  0b0110..6 Bits
 *  0b0111..5 Bits
 *  0b1000..4 Bits
 *  0b1001..3 Bits
 *  0b1010..2 Bits
 *  0b1011..12 Bits
 *  0b1100..12 Bits
 *  0b1101..12 Bits
 *  0b1110..12 Bits
 *  0b1111..12 Bits
 */
#define SEMC_DBICR0_COL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR0_COL_SHIFT)) & SEMC_DBICR0_COL_MASK)
/*! @} */

/*! @name DBICR1 - DBI-B Control Register 1 */
/*! @{ */

#define SEMC_DBICR1_CES_MASK                     (0xFU)
#define SEMC_DBICR1_CES_SHIFT                    (0U)
/*! CES - CSX Setup Time */
#define SEMC_DBICR1_CES(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_CES_SHIFT)) & SEMC_DBICR1_CES_MASK)

#define SEMC_DBICR1_CEH_MASK                     (0xF0U)
#define SEMC_DBICR1_CEH_SHIFT                    (4U)
/*! CEH - CSX Hold Time */
#define SEMC_DBICR1_CEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_CEH_SHIFT)) & SEMC_DBICR1_CEH_MASK)

#define SEMC_DBICR1_WEL_MASK                     (0xF00U)
#define SEMC_DBICR1_WEL_SHIFT                    (8U)
/*! WEL - WRX Low Time */
#define SEMC_DBICR1_WEL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_WEL_SHIFT)) & SEMC_DBICR1_WEL_MASK)

#define SEMC_DBICR1_WEH_MASK                     (0xF000U)
#define SEMC_DBICR1_WEH_SHIFT                    (12U)
/*! WEH - WRX High Time */
#define SEMC_DBICR1_WEH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_WEH_SHIFT)) & SEMC_DBICR1_WEH_MASK)

#define SEMC_DBICR1_REL_MASK                     (0x7F0000U)
#define SEMC_DBICR1_REL_SHIFT                    (16U)
/*! REL - RDX Low Time */
#define SEMC_DBICR1_REL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_REL_SHIFT)) & SEMC_DBICR1_REL_MASK)

#define SEMC_DBICR1_REH_MASK                     (0x7F000000U)
#define SEMC_DBICR1_REH_SHIFT                    (24U)
/*! REH - RDX High Time */
#define SEMC_DBICR1_REH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR1_REH_SHIFT)) & SEMC_DBICR1_REH_MASK)
/*! @} */

/*! @name DBICR2 - DBI-B Control Register 2 */
/*! @{ */

#define SEMC_DBICR2_CEITV_MASK                   (0xFU)
#define SEMC_DBICR2_CEITV_SHIFT                  (0U)
/*! CEITV - CSX interval time */
#define SEMC_DBICR2_CEITV(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_DBICR2_CEITV_SHIFT)) & SEMC_DBICR2_CEITV_MASK)
/*! @} */

/*! @name IPCR0 - IP Command Control Register 0 */
/*! @{ */

#define SEMC_IPCR0_SA_MASK                       (0xFFFFFFFFU)
#define SEMC_IPCR0_SA_SHIFT                      (0U)
/*! SA - Slave address */
#define SEMC_IPCR0_SA(x)                         (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR0_SA_SHIFT)) & SEMC_IPCR0_SA_MASK)
/*! @} */

/*! @name IPCR1 - IP Command Control Register 1 */
/*! @{ */

#define SEMC_IPCR1_DATSZ_MASK                    (0x7U)
#define SEMC_IPCR1_DATSZ_SHIFT                   (0U)
/*! DATSZ - Data Size in Byte
 *  0b000..4
 *  0b001..1
 *  0b010..2
 *  0b011..3
 *  0b100..4
 *  0b101..4
 *  0b110..4
 *  0b111..4
 */
#define SEMC_IPCR1_DATSZ(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR1_DATSZ_SHIFT)) & SEMC_IPCR1_DATSZ_MASK)

#define SEMC_IPCR1_NAND_EXT_ADDR_MASK            (0xFF00U)
#define SEMC_IPCR1_NAND_EXT_ADDR_SHIFT           (8U)
/*! NAND_EXT_ADDR - NAND Extended Address */
#define SEMC_IPCR1_NAND_EXT_ADDR(x)              (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR1_NAND_EXT_ADDR_SHIFT)) & SEMC_IPCR1_NAND_EXT_ADDR_MASK)
/*! @} */

/*! @name IPCR2 - IP Command Control Register 2 */
/*! @{ */

#define SEMC_IPCR2_BM0_MASK                      (0x1U)
#define SEMC_IPCR2_BM0_SHIFT                     (0U)
/*! BM0 - Byte Mask for Byte 0 (IPTXDAT bit 7:0)
 *  0b0..Byte is unmasked
 *  0b1..Byte is masked
 */
#define SEMC_IPCR2_BM0(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM0_SHIFT)) & SEMC_IPCR2_BM0_MASK)

#define SEMC_IPCR2_BM1_MASK                      (0x2U)
#define SEMC_IPCR2_BM1_SHIFT                     (1U)
/*! BM1 - Byte Mask for Byte 1 (IPTXDAT bit 15:8)
 *  0b0..Byte is unmasked
 *  0b1..Byte is masked
 */
#define SEMC_IPCR2_BM1(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM1_SHIFT)) & SEMC_IPCR2_BM1_MASK)

#define SEMC_IPCR2_BM2_MASK                      (0x4U)
#define SEMC_IPCR2_BM2_SHIFT                     (2U)
/*! BM2 - Byte Mask for Byte 2 (IPTXDAT bit 23:16)
 *  0b0..Byte is unmasked
 *  0b1..Byte is masked
 */
#define SEMC_IPCR2_BM2(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM2_SHIFT)) & SEMC_IPCR2_BM2_MASK)

#define SEMC_IPCR2_BM3_MASK                      (0x8U)
#define SEMC_IPCR2_BM3_SHIFT                     (3U)
/*! BM3 - Byte Mask for Byte 3 (IPTXDAT bit 31:24)
 *  0b0..Byte is unmasked
 *  0b1..Byte is masked
 */
#define SEMC_IPCR2_BM3(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCR2_BM3_SHIFT)) & SEMC_IPCR2_BM3_MASK)
/*! @} */

/*! @name IPCMD - IP Command Register */
/*! @{ */

#define SEMC_IPCMD_CMD_MASK                      (0xFFFFU)
#define SEMC_IPCMD_CMD_SHIFT                     (0U)
#define SEMC_IPCMD_CMD(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCMD_CMD_SHIFT)) & SEMC_IPCMD_CMD_MASK)

#define SEMC_IPCMD_KEY_MASK                      (0xFFFF0000U)
#define SEMC_IPCMD_KEY_SHIFT                     (16U)
#define SEMC_IPCMD_KEY(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_IPCMD_KEY_SHIFT)) & SEMC_IPCMD_KEY_MASK)
/*! @} */

/*! @name IPTXDAT - TX DATA Register */
/*! @{ */

#define SEMC_IPTXDAT_DAT_MASK                    (0xFFFFFFFFU)
#define SEMC_IPTXDAT_DAT_SHIFT                   (0U)
#define SEMC_IPTXDAT_DAT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IPTXDAT_DAT_SHIFT)) & SEMC_IPTXDAT_DAT_MASK)
/*! @} */

/*! @name IPRXDAT - RX DATA Register */
/*! @{ */

#define SEMC_IPRXDAT_DAT_MASK                    (0xFFFFFFFFU)
#define SEMC_IPRXDAT_DAT_SHIFT                   (0U)
#define SEMC_IPRXDAT_DAT(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_IPRXDAT_DAT_SHIFT)) & SEMC_IPRXDAT_DAT_MASK)
/*! @} */

/*! @name STS0 - Status Register 0 */
/*! @{ */

#define SEMC_STS0_IDLE_MASK                      (0x1U)
#define SEMC_STS0_IDLE_SHIFT                     (0U)
/*! IDLE - Indicating whether the SEMC is in idle state. */
#define SEMC_STS0_IDLE(x)                        (((uint32_t)(((uint32_t)(x)) << SEMC_STS0_IDLE_SHIFT)) & SEMC_STS0_IDLE_MASK)

#define SEMC_STS0_NARDY_MASK                     (0x2U)
#define SEMC_STS0_NARDY_SHIFT                    (1U)
/*! NARDY - Indicating NAND device Ready/WAIT# pin level.
 *  0b0..NAND device is not ready
 *  0b1..NAND device is ready
 */
#define SEMC_STS0_NARDY(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_STS0_NARDY_SHIFT)) & SEMC_STS0_NARDY_MASK)
/*! @} */

/*! @name STS2 - Status Register 2 */
/*! @{ */

#define SEMC_STS2_NDWRPEND_MASK                  (0x8U)
#define SEMC_STS2_NDWRPEND_SHIFT                 (3U)
/*! NDWRPEND - This field indicating whether there is pending AXI command (write) to NAND device.
 *  0b0..No pending
 *  0b1..Pending
 */
#define SEMC_STS2_NDWRPEND(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_STS2_NDWRPEND_SHIFT)) & SEMC_STS2_NDWRPEND_MASK)
/*! @} */

/*! @name STS12 - Status Register 12 */
/*! @{ */

#define SEMC_STS12_NDADDR_MASK                   (0xFFFFFFFFU)
#define SEMC_STS12_NDADDR_SHIFT                  (0U)
/*! NDADDR - This field indicating the last write address (AXI command) to NAND device (without base address in SEMC_BR4). */
#define SEMC_STS12_NDADDR(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_STS12_NDADDR_SHIFT)) & SEMC_STS12_NDADDR_MASK)
/*! @} */

/*! @name STS13 - Status Register 13 */
/*! @{ */

#define SEMC_STS13_SLVLOCK_MASK                  (0x1U)
#define SEMC_STS13_SLVLOCK_SHIFT                 (0U)
/*! SLVLOCK - Sample clock slave delay line locked.
 *  0b0..Slave delay line is not locked.
 *  0b1..Slave delay line is locked.
 */
#define SEMC_STS13_SLVLOCK(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_STS13_SLVLOCK_SHIFT)) & SEMC_STS13_SLVLOCK_MASK)

#define SEMC_STS13_REFLOCK_MASK                  (0x2U)
#define SEMC_STS13_REFLOCK_SHIFT                 (1U)
/*! REFLOCK - Sample clock reference delay line locked.
 *  0b0..Reference delay line is not locked.
 *  0b1..Reference delay line is locked.
 */
#define SEMC_STS13_REFLOCK(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_STS13_REFLOCK_SHIFT)) & SEMC_STS13_REFLOCK_MASK)

#define SEMC_STS13_SLVSEL_MASK                   (0xFCU)
#define SEMC_STS13_SLVSEL_SHIFT                  (2U)
/*! SLVSEL - Sample clock slave delay line delay cell number selection. */
#define SEMC_STS13_SLVSEL(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_STS13_SLVSEL_SHIFT)) & SEMC_STS13_SLVSEL_MASK)

#define SEMC_STS13_REFSEL_MASK                   (0x3F00U)
#define SEMC_STS13_REFSEL_SHIFT                  (8U)
/*! REFSEL - Sample clock reference delay line delay cell number selection. */
#define SEMC_STS13_REFSEL(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_STS13_REFSEL_SHIFT)) & SEMC_STS13_REFSEL_MASK)
/*! @} */

/*! @name BR9 - Base Register 9 */
/*! @{ */

#define SEMC_BR9_VLD_MASK                        (0x1U)
#define SEMC_BR9_VLD_SHIFT                       (0U)
/*! VLD - Valid
 *  0b0..The memory is invalid, can not be accessed.
 *  0b1..The memory is valid, can be accessed.
 */
#define SEMC_BR9_VLD(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_BR9_VLD_SHIFT)) & SEMC_BR9_VLD_MASK)

#define SEMC_BR9_MS_MASK                         (0x3EU)
#define SEMC_BR9_MS_SHIFT                        (1U)
/*! MS - Memory size
 *  0b00000..4KB
 *  0b00001..8KB
 *  0b00010..16KB
 *  0b00011..32KB
 *  0b00100..64KB
 *  0b00101..128KB
 *  0b00110..256KB
 *  0b00111..512KB
 *  0b01000..1MB
 *  0b01001..2MB
 *  0b01010..4MB
 *  0b01011..8MB
 *  0b01100..16MB
 *  0b01101..32MB
 *  0b01110..64MB
 *  0b01111..128MB
 *  0b10000..256MB
 *  0b10001..512MB
 *  0b10010..1GB
 *  0b10011..2GB
 *  0b10100-0b11111..4GB
 */
#define SEMC_BR9_MS(x)                           (((uint32_t)(((uint32_t)(x)) << SEMC_BR9_MS_SHIFT)) & SEMC_BR9_MS_MASK)

#define SEMC_BR9_BA_MASK                         (0xFFFFF000U)
#define SEMC_BR9_BA_SHIFT                        (12U)
/*! BA - Base Address */
#define SEMC_BR9_BA(x)                           (((uint32_t)(((uint32_t)(x)) << SEMC_BR9_BA_SHIFT)) & SEMC_BR9_BA_MASK)
/*! @} */

/*! @name BR10 - Base Register 10 */
/*! @{ */

#define SEMC_BR10_VLD_MASK                       (0x1U)
#define SEMC_BR10_VLD_SHIFT                      (0U)
/*! VLD - Valid
 *  0b0..The memory is invalid, can not be accessed.
 *  0b1..The memory is valid, can be accessed.
 */
#define SEMC_BR10_VLD(x)                         (((uint32_t)(((uint32_t)(x)) << SEMC_BR10_VLD_SHIFT)) & SEMC_BR10_VLD_MASK)

#define SEMC_BR10_MS_MASK                        (0x3EU)
#define SEMC_BR10_MS_SHIFT                       (1U)
/*! MS - Memory size
 *  0b00000..4KB
 *  0b00001..8KB
 *  0b00010..16KB
 *  0b00011..32KB
 *  0b00100..64KB
 *  0b00101..128KB
 *  0b00110..256KB
 *  0b00111..512KB
 *  0b01000..1MB
 *  0b01001..2MB
 *  0b01010..4MB
 *  0b01011..8MB
 *  0b01100..16MB
 *  0b01101..32MB
 *  0b01110..64MB
 *  0b01111..128MB
 *  0b10000..256MB
 *  0b10001..512MB
 *  0b10010..1GB
 *  0b10011..2GB
 *  0b10100-0b11111..4GB
 */
#define SEMC_BR10_MS(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_BR10_MS_SHIFT)) & SEMC_BR10_MS_MASK)

#define SEMC_BR10_BA_MASK                        (0xFFFFF000U)
#define SEMC_BR10_BA_SHIFT                       (12U)
/*! BA - Base Address */
#define SEMC_BR10_BA(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_BR10_BA_SHIFT)) & SEMC_BR10_BA_MASK)
/*! @} */

/*! @name BR11 - Base Register 11 */
/*! @{ */

#define SEMC_BR11_VLD_MASK                       (0x1U)
#define SEMC_BR11_VLD_SHIFT                      (0U)
/*! VLD - Valid
 *  0b0..The memory is invalid, can not be accessed.
 *  0b1..The memory is valid, can be accessed.
 */
#define SEMC_BR11_VLD(x)                         (((uint32_t)(((uint32_t)(x)) << SEMC_BR11_VLD_SHIFT)) & SEMC_BR11_VLD_MASK)

#define SEMC_BR11_MS_MASK                        (0x3EU)
#define SEMC_BR11_MS_SHIFT                       (1U)
/*! MS - Memory size
 *  0b00000..4KB
 *  0b00001..8KB
 *  0b00010..16KB
 *  0b00011..32KB
 *  0b00100..64KB
 *  0b00101..128KB
 *  0b00110..256KB
 *  0b00111..512KB
 *  0b01000..1MB
 *  0b01001..2MB
 *  0b01010..4MB
 *  0b01011..8MB
 *  0b01100..16MB
 *  0b01101..32MB
 *  0b01110..64MB
 *  0b01111..128MB
 *  0b10000..256MB
 *  0b10001..512MB
 *  0b10010..1GB
 *  0b10011..2GB
 *  0b10100-0b11111..4GB
 */
#define SEMC_BR11_MS(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_BR11_MS_SHIFT)) & SEMC_BR11_MS_MASK)

#define SEMC_BR11_BA_MASK                        (0xFFFFF000U)
#define SEMC_BR11_BA_SHIFT                       (12U)
/*! BA - Base Address */
#define SEMC_BR11_BA(x)                          (((uint32_t)(((uint32_t)(x)) << SEMC_BR11_BA_SHIFT)) & SEMC_BR11_BA_MASK)
/*! @} */

/*! @name SRAMCR4 - SRAM Control Register 4 */
/*! @{ */

#define SEMC_SRAMCR4_PS_MASK                     (0x1U)
#define SEMC_SRAMCR4_PS_SHIFT                    (0U)
/*! PS - Port Size
 *  0b0..8bit
 *  0b1..16bit
 */
#define SEMC_SRAMCR4_PS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_PS_SHIFT)) & SEMC_SRAMCR4_PS_MASK)

#define SEMC_SRAMCR4_SYNCEN_MASK                 (0x2U)
#define SEMC_SRAMCR4_SYNCEN_SHIFT                (1U)
/*! SYNCEN - Synchronous Mode Enable
 *  0b0..Asynchronous mode is enabled.
 *  0b1..Synchronous mode is enabled. Only fixed latency mode is supported.
 */
#define SEMC_SRAMCR4_SYNCEN(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_SYNCEN_SHIFT)) & SEMC_SRAMCR4_SYNCEN_MASK)

#define SEMC_SRAMCR4_WAITEN_MASK                 (0x4U)
#define SEMC_SRAMCR4_WAITEN_SHIFT                (2U)
/*! WAITEN - Wait Enable
 *  0b0..The SEMC does not monitor wait pin.
 *  0b1..The SEMC monitors wait pin. The SEMC does not transfer/receive data when wait pin is asserted.
 */
#define SEMC_SRAMCR4_WAITEN(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_WAITEN_SHIFT)) & SEMC_SRAMCR4_WAITEN_MASK)

#define SEMC_SRAMCR4_WAITSP_MASK                 (0x8U)
#define SEMC_SRAMCR4_WAITSP_SHIFT                (3U)
/*! WAITSP - Wait Sample
 *  0b0..Wait pin is directly used by the SEMC.
 *  0b1..Wait pin is sampled by internal clock before it is used.
 */
#define SEMC_SRAMCR4_WAITSP(x)                   (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_WAITSP_SHIFT)) & SEMC_SRAMCR4_WAITSP_MASK)

#define SEMC_SRAMCR4_BL_MASK                     (0x70U)
#define SEMC_SRAMCR4_BL_SHIFT                    (4U)
/*! BL - Burst Length
 *  0b000..1
 *  0b001..2
 *  0b010..4
 *  0b011..8
 *  0b100..16
 *  0b101..32
 *  0b110..64
 *  0b111..64
 */
#define SEMC_SRAMCR4_BL(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_BL_SHIFT)) & SEMC_SRAMCR4_BL_MASK)

#define SEMC_SRAMCR4_AM_MASK                     (0x300U)
#define SEMC_SRAMCR4_AM_SHIFT                    (8U)
/*! AM - Address Mode
 *  0b00..Address/Data MUX mode (ADMUX)
 *  0b01..Advanced Address/Data MUX mode (AADM)
 *  0b10..Address/Data non-MUX mode (Non-ADMUX)
 *  0b11..Address/Data non-MUX mode (Non-ADMUX)
 */
#define SEMC_SRAMCR4_AM(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_AM_SHIFT)) & SEMC_SRAMCR4_AM_MASK)

#define SEMC_SRAMCR4_ADVP_MASK                   (0x400U)
#define SEMC_SRAMCR4_ADVP_SHIFT                  (10U)
/*! ADVP - ADV# polarity
 *  0b0..ADV# is active low.
 *  0b1..ADV# is active high.
 */
#define SEMC_SRAMCR4_ADVP(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_ADVP_SHIFT)) & SEMC_SRAMCR4_ADVP_MASK)

#define SEMC_SRAMCR4_ADVH_MASK                   (0x800U)
#define SEMC_SRAMCR4_ADVH_SHIFT                  (11U)
/*! ADVH - ADV# level control during address hold state
 *  0b0..ADV# is high during address hold state.
 *  0b1..ADV# is low during address hold state.
 */
#define SEMC_SRAMCR4_ADVH(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_ADVH_SHIFT)) & SEMC_SRAMCR4_ADVH_MASK)

#define SEMC_SRAMCR4_COL_MASK                    (0xF000U)
#define SEMC_SRAMCR4_COL_SHIFT                   (12U)
/*! COL - Column Address bit width
 *  0b0000..12 Bits
 *  0b0001..11 Bits
 *  0b0010..10 Bits
 *  0b0011..9 Bits
 *  0b0100..8 Bits
 *  0b0101..7 Bits
 *  0b0110..6 Bits
 *  0b0111..5 Bits
 *  0b1000..4 Bits
 *  0b1001..3 Bits
 *  0b1010..2 Bits
 *  0b1011..12 Bits
 *  0b1100..12 Bits
 *  0b1101..12 Bits
 *  0b1110..12 Bits
 *  0b1111..12 Bits
 */
#define SEMC_SRAMCR4_COL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR4_COL_SHIFT)) & SEMC_SRAMCR4_COL_MASK)
/*! @} */

/*! @name SRAMCR5 - SRAM Control Register 5 */
/*! @{ */

#define SEMC_SRAMCR5_CES_MASK                    (0xFU)
#define SEMC_SRAMCR5_CES_SHIFT                   (0U)
/*! CES - CE setup time */
#define SEMC_SRAMCR5_CES(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_CES_SHIFT)) & SEMC_SRAMCR5_CES_MASK)

#define SEMC_SRAMCR5_CEH_MASK                    (0xF0U)
#define SEMC_SRAMCR5_CEH_SHIFT                   (4U)
/*! CEH - CE hold time */
#define SEMC_SRAMCR5_CEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_CEH_SHIFT)) & SEMC_SRAMCR5_CEH_MASK)

#define SEMC_SRAMCR5_AS_MASK                     (0xF00U)
#define SEMC_SRAMCR5_AS_SHIFT                    (8U)
/*! AS - Address setup time */
#define SEMC_SRAMCR5_AS(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_AS_SHIFT)) & SEMC_SRAMCR5_AS_MASK)

#define SEMC_SRAMCR5_AH_MASK                     (0xF000U)
#define SEMC_SRAMCR5_AH_SHIFT                    (12U)
/*! AH - Address hold time */
#define SEMC_SRAMCR5_AH(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_AH_SHIFT)) & SEMC_SRAMCR5_AH_MASK)

#define SEMC_SRAMCR5_WEL_MASK                    (0xF0000U)
#define SEMC_SRAMCR5_WEL_SHIFT                   (16U)
/*! WEL - WE low time */
#define SEMC_SRAMCR5_WEL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_WEL_SHIFT)) & SEMC_SRAMCR5_WEL_MASK)

#define SEMC_SRAMCR5_WEH_MASK                    (0xF00000U)
#define SEMC_SRAMCR5_WEH_SHIFT                   (20U)
/*! WEH - WE high time */
#define SEMC_SRAMCR5_WEH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_WEH_SHIFT)) & SEMC_SRAMCR5_WEH_MASK)

#define SEMC_SRAMCR5_REL_MASK                    (0xF000000U)
#define SEMC_SRAMCR5_REL_SHIFT                   (24U)
/*! REL - RE low time */
#define SEMC_SRAMCR5_REL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_REL_SHIFT)) & SEMC_SRAMCR5_REL_MASK)

#define SEMC_SRAMCR5_REH_MASK                    (0xF0000000U)
#define SEMC_SRAMCR5_REH_SHIFT                   (28U)
/*! REH - RE high time */
#define SEMC_SRAMCR5_REH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR5_REH_SHIFT)) & SEMC_SRAMCR5_REH_MASK)
/*! @} */

/*! @name SRAMCR6 - SRAM Control Register 6 */
/*! @{ */

#define SEMC_SRAMCR6_WDS_MASK                    (0xFU)
#define SEMC_SRAMCR6_WDS_SHIFT                   (0U)
/*! WDS - Write Data setup time */
#define SEMC_SRAMCR6_WDS(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_WDS_SHIFT)) & SEMC_SRAMCR6_WDS_MASK)

#define SEMC_SRAMCR6_WDH_MASK                    (0xF0U)
#define SEMC_SRAMCR6_WDH_SHIFT                   (4U)
/*! WDH - Write Data hold time */
#define SEMC_SRAMCR6_WDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_WDH_SHIFT)) & SEMC_SRAMCR6_WDH_MASK)

#define SEMC_SRAMCR6_TA_MASK                     (0xF00U)
#define SEMC_SRAMCR6_TA_SHIFT                    (8U)
/*! TA - Turnaround time */
#define SEMC_SRAMCR6_TA(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_TA_SHIFT)) & SEMC_SRAMCR6_TA_MASK)

#define SEMC_SRAMCR6_AWDH_MASK                   (0xF000U)
#define SEMC_SRAMCR6_AWDH_SHIFT                  (12U)
/*! AWDH - Address to write data hold time */
#define SEMC_SRAMCR6_AWDH(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_AWDH_SHIFT)) & SEMC_SRAMCR6_AWDH_MASK)

#define SEMC_SRAMCR6_LC_MASK                     (0xF0000U)
#define SEMC_SRAMCR6_LC_SHIFT                    (16U)
/*! LC - Latency count */
#define SEMC_SRAMCR6_LC(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_LC_SHIFT)) & SEMC_SRAMCR6_LC_MASK)

#define SEMC_SRAMCR6_RD_MASK                     (0xF00000U)
#define SEMC_SRAMCR6_RD_SHIFT                    (20U)
/*! RD - Read time */
#define SEMC_SRAMCR6_RD(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_RD_SHIFT)) & SEMC_SRAMCR6_RD_MASK)

#define SEMC_SRAMCR6_CEITV_MASK                  (0xF000000U)
#define SEMC_SRAMCR6_CEITV_SHIFT                 (24U)
/*! CEITV - CE# interval time */
#define SEMC_SRAMCR6_CEITV(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_CEITV_SHIFT)) & SEMC_SRAMCR6_CEITV_MASK)

#define SEMC_SRAMCR6_RDH_MASK                    (0xF0000000U)
#define SEMC_SRAMCR6_RDH_SHIFT                   (28U)
/*! RDH - Read hold time */
#define SEMC_SRAMCR6_RDH(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_SRAMCR6_RDH_SHIFT)) & SEMC_SRAMCR6_RDH_MASK)
/*! @} */

/*! @name DCCR - Delay Chain Control Register */
/*! @{ */

#define SEMC_DCCR_SDRAMEN_MASK                   (0x1U)
#define SEMC_DCCR_SDRAMEN_SHIFT                  (0U)
/*! SDRAMEN - Delay chain insertion enable for SRAM device.
 *  0b0..Delay chain is not inserted.
 *  0b1..Delay chain is inserted.
 */
#define SEMC_DCCR_SDRAMEN(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_SDRAMEN_SHIFT)) & SEMC_DCCR_SDRAMEN_MASK)

#define SEMC_DCCR_SDRAMVAL_MASK                  (0x3EU)
#define SEMC_DCCR_SDRAMVAL_SHIFT                 (1U)
/*! SDRAMVAL - Clock delay line delay cell number selection value for SDRAM device. */
#define SEMC_DCCR_SDRAMVAL(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_SDRAMVAL_SHIFT)) & SEMC_DCCR_SDRAMVAL_MASK)

#define SEMC_DCCR_NOREN_MASK                     (0x100U)
#define SEMC_DCCR_NOREN_SHIFT                    (8U)
/*! NOREN - Delay chain insertion enable for NOR device.
 *  0b0..Delay chain is not inserted.
 *  0b1..Delay chain is inserted.
 */
#define SEMC_DCCR_NOREN(x)                       (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_NOREN_SHIFT)) & SEMC_DCCR_NOREN_MASK)

#define SEMC_DCCR_NORVAL_MASK                    (0x3E00U)
#define SEMC_DCCR_NORVAL_SHIFT                   (9U)
/*! NORVAL - Clock delay line delay cell number selection value for NOR device. */
#define SEMC_DCCR_NORVAL(x)                      (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_NORVAL_SHIFT)) & SEMC_DCCR_NORVAL_MASK)

#define SEMC_DCCR_SRAM0EN_MASK                   (0x10000U)
#define SEMC_DCCR_SRAM0EN_SHIFT                  (16U)
/*! SRAM0EN - Delay chain insertion enable for SRAM device 0.
 *  0b0..Delay chain is not inserted.
 *  0b1..Delay chain is inserted.
 */
#define SEMC_DCCR_SRAM0EN(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_SRAM0EN_SHIFT)) & SEMC_DCCR_SRAM0EN_MASK)

#define SEMC_DCCR_SRAM0VAL_MASK                  (0x3E0000U)
#define SEMC_DCCR_SRAM0VAL_SHIFT                 (17U)
/*! SRAM0VAL - Clock delay line delay cell number selection value for SRAM device 0. */
#define SEMC_DCCR_SRAM0VAL(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_SRAM0VAL_SHIFT)) & SEMC_DCCR_SRAM0VAL_MASK)

#define SEMC_DCCR_SRAMXEN_MASK                   (0x1000000U)
#define SEMC_DCCR_SRAMXEN_SHIFT                  (24U)
/*! SRAMXEN - Delay chain insertion enable for SRAM device 1-3.
 *  0b0..Delay chain is not inserted.
 *  0b1..Delay chain is inserted.
 */
#define SEMC_DCCR_SRAMXEN(x)                     (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_SRAMXEN_SHIFT)) & SEMC_DCCR_SRAMXEN_MASK)

#define SEMC_DCCR_SRAMXVAL_MASK                  (0x3E000000U)
#define SEMC_DCCR_SRAMXVAL_SHIFT                 (25U)
/*! SRAMXVAL - Clock delay line delay cell number selection value for SRAM device 1-3. */
#define SEMC_DCCR_SRAMXVAL(x)                    (((uint32_t)(((uint32_t)(x)) << SEMC_DCCR_SRAMXVAL_SHIFT)) & SEMC_DCCR_SRAMXVAL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SEMC_Register_Masks */


/*!
 * @}
 */ /* end of group SEMC_Peripheral_Access_Layer */


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


#endif  /* PERI_SEMC_H_ */

