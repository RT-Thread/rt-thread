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
**         CMSIS Peripheral Access Layer for LMEM
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
 * @file PERI_LMEM.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for LMEM
 *
 * CMSIS Peripheral Access Layer for LMEM
 */

#if !defined(PERI_LMEM_H_)
#define PERI_LMEM_H_                             /**< Symbol preventing repeated inclusion */

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
   -- LMEM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LMEM_Peripheral_Access_Layer LMEM Peripheral Access Layer
 * @{
 */

/** LMEM - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCCCR;                             /**< PC bus Cache control register, offset: 0x0 */
  __IO uint32_t PCCLCR;                            /**< PC bus Cache line control register, offset: 0x4 */
  __IO uint32_t PCCSAR;                            /**< PC bus Cache search address register, offset: 0x8 */
  __IO uint32_t PCCCVR;                            /**< PC bus Cache read/write value register, offset: 0xC */
       uint8_t RESERVED_0[2032];
  __IO uint32_t PSCCR;                             /**< PS bus Cache control register, offset: 0x800 */
  __IO uint32_t PSCLCR;                            /**< PS bus Cache line control register, offset: 0x804 */
  __IO uint32_t PSCSAR;                            /**< PS bus Cache search address register, offset: 0x808 */
  __IO uint32_t PSCCVR;                            /**< PS bus Cache read/write value register, offset: 0x80C */
} LMEM_Type;

/* ----------------------------------------------------------------------------
   -- LMEM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LMEM_Register_Masks LMEM Register Masks
 * @{
 */

/*! @name PCCCR - PC bus Cache control register */
/*! @{ */

#define LMEM_PCCCR_ENCACHE_MASK                  (0x1U)
#define LMEM_PCCCR_ENCACHE_SHIFT                 (0U)
/*! ENCACHE - Cache enable
 *  0b0..Cache disabled
 *  0b1..Cache enabled
 */
#define LMEM_PCCCR_ENCACHE(x)                    (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_ENCACHE_SHIFT)) & LMEM_PCCCR_ENCACHE_MASK)

#define LMEM_PCCCR_ENWRBUF_MASK                  (0x2U)
#define LMEM_PCCCR_ENWRBUF_SHIFT                 (1U)
/*! ENWRBUF - Enable Write Buffer
 *  0b0..Write buffer disabled
 *  0b1..Write buffer enabled
 */
#define LMEM_PCCCR_ENWRBUF(x)                    (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_ENWRBUF_SHIFT)) & LMEM_PCCCR_ENWRBUF_MASK)

#define LMEM_PCCCR_PCCR2_MASK                    (0x4U)
#define LMEM_PCCCR_PCCR2_SHIFT                   (2U)
/*! PCCR2 - Forces all cacheable spaces to write through
 *  0b0..Does NOT force all cacheable spaces to write through
 *  0b1..Forces all cacheable spaces to write through
 */
#define LMEM_PCCCR_PCCR2(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_PCCR2_SHIFT)) & LMEM_PCCCR_PCCR2_MASK)

#define LMEM_PCCCR_PCCR3_MASK                    (0x8U)
#define LMEM_PCCCR_PCCR3_SHIFT                   (3U)
/*! PCCR3 - Forces no allocation on cache misses
 *  0b0..Allocation on cache misses
 *  0b1..Forces no allocation on cache misses (must also have PCCR2 asserted)
 */
#define LMEM_PCCCR_PCCR3(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_PCCR3_SHIFT)) & LMEM_PCCCR_PCCR3_MASK)

#define LMEM_PCCCR_INVW0_MASK                    (0x1000000U)
#define LMEM_PCCCR_INVW0_SHIFT                   (24U)
/*! INVW0 - Invalidate Way 0
 *  0b0..No operation
 *  0b1..When setting the GO bit, invalidate all lines in way 0.
 */
#define LMEM_PCCCR_INVW0(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_INVW0_SHIFT)) & LMEM_PCCCR_INVW0_MASK)

#define LMEM_PCCCR_PUSHW0_MASK                   (0x2000000U)
#define LMEM_PCCCR_PUSHW0_SHIFT                  (25U)
/*! PUSHW0 - Push Way 0
 *  0b0..No operation
 *  0b1..When setting the GO bit, push all modified lines in way 0
 */
#define LMEM_PCCCR_PUSHW0(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_PUSHW0_SHIFT)) & LMEM_PCCCR_PUSHW0_MASK)

#define LMEM_PCCCR_INVW1_MASK                    (0x4000000U)
#define LMEM_PCCCR_INVW1_SHIFT                   (26U)
/*! INVW1 - Invalidate Way 1
 *  0b0..No operation
 *  0b1..When setting the GO bit, invalidate all lines in way 1
 */
#define LMEM_PCCCR_INVW1(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_INVW1_SHIFT)) & LMEM_PCCCR_INVW1_MASK)

#define LMEM_PCCCR_PUSHW1_MASK                   (0x8000000U)
#define LMEM_PCCCR_PUSHW1_SHIFT                  (27U)
/*! PUSHW1 - Push Way 1
 *  0b0..No operation
 *  0b1..When setting the GO bit, push all modified lines in way 1
 */
#define LMEM_PCCCR_PUSHW1(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_PUSHW1_SHIFT)) & LMEM_PCCCR_PUSHW1_MASK)

#define LMEM_PCCCR_GO_MASK                       (0x80000000U)
#define LMEM_PCCCR_GO_SHIFT                      (31U)
/*! GO - Initiate Cache Command
 *  0b0..Write: no effect. Read: no cache command active.
 *  0b1..Write: initiate command indicated by bits 27-24. Read: cache command active.
 */
#define LMEM_PCCCR_GO(x)                         (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCR_GO_SHIFT)) & LMEM_PCCCR_GO_MASK)
/*! @} */

/*! @name PCCLCR - PC bus Cache line control register */
/*! @{ */

#define LMEM_PCCLCR_LGO_MASK                     (0x1U)
#define LMEM_PCCLCR_LGO_SHIFT                    (0U)
/*! LGO - Initiate Cache Line Command
 *  0b0..Write: no effect. Read: no line command active.
 *  0b1..Write: initiate line command indicated by bits 27-24. Read: line command active.
 */
#define LMEM_PCCLCR_LGO(x)                       (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_LGO_SHIFT)) & LMEM_PCCLCR_LGO_MASK)

#define LMEM_PCCLCR_CACHEADDR_MASK               (0x3FFCU)
#define LMEM_PCCLCR_CACHEADDR_SHIFT              (2U)
/*! CACHEADDR - Cache address */
#define LMEM_PCCLCR_CACHEADDR(x)                 (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_CACHEADDR_SHIFT)) & LMEM_PCCLCR_CACHEADDR_MASK)

#define LMEM_PCCLCR_WSEL_MASK                    (0x4000U)
#define LMEM_PCCLCR_WSEL_SHIFT                   (14U)
/*! WSEL - Way select
 *  0b0..Way 0
 *  0b1..Way 1
 */
#define LMEM_PCCLCR_WSEL(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_WSEL_SHIFT)) & LMEM_PCCLCR_WSEL_MASK)

#define LMEM_PCCLCR_TDSEL_MASK                   (0x10000U)
#define LMEM_PCCLCR_TDSEL_SHIFT                  (16U)
/*! TDSEL - Tag/Data Select
 *  0b0..Data
 *  0b1..Tag
 */
#define LMEM_PCCLCR_TDSEL(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_TDSEL_SHIFT)) & LMEM_PCCLCR_TDSEL_MASK)

#define LMEM_PCCLCR_LCIVB_MASK                   (0x100000U)
#define LMEM_PCCLCR_LCIVB_SHIFT                  (20U)
/*! LCIVB - Line Command Initial Valid Bit */
#define LMEM_PCCLCR_LCIVB(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_LCIVB_SHIFT)) & LMEM_PCCLCR_LCIVB_MASK)

#define LMEM_PCCLCR_LCIMB_MASK                   (0x200000U)
#define LMEM_PCCLCR_LCIMB_SHIFT                  (21U)
/*! LCIMB - Line Command Initial Modified Bit */
#define LMEM_PCCLCR_LCIMB(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_LCIMB_SHIFT)) & LMEM_PCCLCR_LCIMB_MASK)

#define LMEM_PCCLCR_LCWAY_MASK                   (0x400000U)
#define LMEM_PCCLCR_LCWAY_SHIFT                  (22U)
/*! LCWAY - Line Command Way */
#define LMEM_PCCLCR_LCWAY(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_LCWAY_SHIFT)) & LMEM_PCCLCR_LCWAY_MASK)

#define LMEM_PCCLCR_LCMD_MASK                    (0x3000000U)
#define LMEM_PCCLCR_LCMD_SHIFT                   (24U)
/*! LCMD - Line Command
 *  0b00..Search and read or write
 *  0b01..Invalidate
 *  0b10..Push
 *  0b11..Clear
 */
#define LMEM_PCCLCR_LCMD(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_LCMD_SHIFT)) & LMEM_PCCLCR_LCMD_MASK)

#define LMEM_PCCLCR_LADSEL_MASK                  (0x4000000U)
#define LMEM_PCCLCR_LADSEL_SHIFT                 (26U)
/*! LADSEL - Line Address Select
 *  0b0..Cache address
 *  0b1..Physical address
 */
#define LMEM_PCCLCR_LADSEL(x)                    (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_LADSEL_SHIFT)) & LMEM_PCCLCR_LADSEL_MASK)

#define LMEM_PCCLCR_LACC_MASK                    (0x8000000U)
#define LMEM_PCCLCR_LACC_SHIFT                   (27U)
/*! LACC - Line access type
 *  0b0..Read
 *  0b1..Write
 */
#define LMEM_PCCLCR_LACC(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCLCR_LACC_SHIFT)) & LMEM_PCCLCR_LACC_MASK)
/*! @} */

/*! @name PCCSAR - PC bus Cache search address register */
/*! @{ */

#define LMEM_PCCSAR_LGO_MASK                     (0x1U)
#define LMEM_PCCSAR_LGO_SHIFT                    (0U)
/*! LGO - Initiate Cache Line Command
 *  0b0..Write: no effect. Read: no line command active.
 *  0b1..Write: initiate line command indicated by bits CLCR[27:24]. Read: line command active.
 */
#define LMEM_PCCSAR_LGO(x)                       (((uint32_t)(((uint32_t)(x)) << LMEM_PCCSAR_LGO_SHIFT)) & LMEM_PCCSAR_LGO_MASK)

#define LMEM_PCCSAR_PHYADDR_MASK                 (0xFFFFFFFEU)
#define LMEM_PCCSAR_PHYADDR_SHIFT                (1U)
/*! PHYADDR - Physical Address */
#define LMEM_PCCSAR_PHYADDR(x)                   (((uint32_t)(((uint32_t)(x)) << LMEM_PCCSAR_PHYADDR_SHIFT)) & LMEM_PCCSAR_PHYADDR_MASK)
/*! @} */

/*! @name PCCCVR - PC bus Cache read/write value register */
/*! @{ */

#define LMEM_PCCCVR_DATA_MASK                    (0xFFFFFFFFU)
#define LMEM_PCCCVR_DATA_SHIFT                   (0U)
/*! DATA - Cache read/write Data */
#define LMEM_PCCCVR_DATA(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PCCCVR_DATA_SHIFT)) & LMEM_PCCCVR_DATA_MASK)
/*! @} */

/*! @name PSCCR - PS bus Cache control register */
/*! @{ */

#define LMEM_PSCCR_ENCACHE_MASK                  (0x1U)
#define LMEM_PSCCR_ENCACHE_SHIFT                 (0U)
/*! ENCACHE - Cache enable
 *  0b0..Cache disabled
 *  0b1..Cache enabled
 */
#define LMEM_PSCCR_ENCACHE(x)                    (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_ENCACHE_SHIFT)) & LMEM_PSCCR_ENCACHE_MASK)

#define LMEM_PSCCR_ENWRBUF_MASK                  (0x2U)
#define LMEM_PSCCR_ENWRBUF_SHIFT                 (1U)
/*! ENWRBUF - Enable Write Buffer
 *  0b0..Write buffer disabled
 *  0b1..Write buffer enabled
 */
#define LMEM_PSCCR_ENWRBUF(x)                    (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_ENWRBUF_SHIFT)) & LMEM_PSCCR_ENWRBUF_MASK)

#define LMEM_PSCCR_PSCR2_MASK                    (0x4U)
#define LMEM_PSCCR_PSCR2_SHIFT                   (2U)
/*! PSCR2 - Forces all cacheable spaces to write through
 *  0b0..Does NOT force all cacheable spaces to write through
 *  0b1..Forces all cacheable spaces to write through
 */
#define LMEM_PSCCR_PSCR2(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_PSCR2_SHIFT)) & LMEM_PSCCR_PSCR2_MASK)

#define LMEM_PSCCR_PSCR3_MASK                    (0x8U)
#define LMEM_PSCCR_PSCR3_SHIFT                   (3U)
/*! PSCR3 - Forces no allocation on cache misses
 *  0b0..Allocation on cache misses
 *  0b1..Forces no allocation on cache misses (must also have PSCR2 asserted)
 */
#define LMEM_PSCCR_PSCR3(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_PSCR3_SHIFT)) & LMEM_PSCCR_PSCR3_MASK)

#define LMEM_PSCCR_INVW0_MASK                    (0x1000000U)
#define LMEM_PSCCR_INVW0_SHIFT                   (24U)
/*! INVW0 - Invalidate Way 0
 *  0b0..No operation
 *  0b1..When setting the GO bit, invalidate all lines in way 0.
 */
#define LMEM_PSCCR_INVW0(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_INVW0_SHIFT)) & LMEM_PSCCR_INVW0_MASK)

#define LMEM_PSCCR_PUSHW0_MASK                   (0x2000000U)
#define LMEM_PSCCR_PUSHW0_SHIFT                  (25U)
/*! PUSHW0 - Push Way 0
 *  0b0..No operation
 *  0b1..When setting the GO bit, push all modified lines in way 0
 */
#define LMEM_PSCCR_PUSHW0(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_PUSHW0_SHIFT)) & LMEM_PSCCR_PUSHW0_MASK)

#define LMEM_PSCCR_INVW1_MASK                    (0x4000000U)
#define LMEM_PSCCR_INVW1_SHIFT                   (26U)
/*! INVW1 - Invalidate Way 1
 *  0b0..No operation
 *  0b1..When setting the GO bit, invalidate all lines in way 1
 */
#define LMEM_PSCCR_INVW1(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_INVW1_SHIFT)) & LMEM_PSCCR_INVW1_MASK)

#define LMEM_PSCCR_PUSHW1_MASK                   (0x8000000U)
#define LMEM_PSCCR_PUSHW1_SHIFT                  (27U)
/*! PUSHW1 - Push Way 1
 *  0b0..No operation
 *  0b1..When setting the GO bit, push all modified lines in way 1
 */
#define LMEM_PSCCR_PUSHW1(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_PUSHW1_SHIFT)) & LMEM_PSCCR_PUSHW1_MASK)

#define LMEM_PSCCR_GO_MASK                       (0x80000000U)
#define LMEM_PSCCR_GO_SHIFT                      (31U)
/*! GO - Initiate Cache Command
 *  0b0..Write: no effect. Read: no cache command active.
 *  0b1..Write: initiate command indicated by bits 27-24. Read: cache command active.
 */
#define LMEM_PSCCR_GO(x)                         (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCR_GO_SHIFT)) & LMEM_PSCCR_GO_MASK)
/*! @} */

/*! @name PSCLCR - PS bus Cache line control register */
/*! @{ */

#define LMEM_PSCLCR_LGO_MASK                     (0x1U)
#define LMEM_PSCLCR_LGO_SHIFT                    (0U)
/*! LGO - Initiate Cache Line Command
 *  0b0..Write: no effect. Read: no line command active.
 *  0b1..Write: initiate line command indicated by bits 27-24. Read: line command active.
 */
#define LMEM_PSCLCR_LGO(x)                       (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_LGO_SHIFT)) & LMEM_PSCLCR_LGO_MASK)

#define LMEM_PSCLCR_CACHEADDR_MASK               (0x3FFCU)
#define LMEM_PSCLCR_CACHEADDR_SHIFT              (2U)
/*! CACHEADDR - Cache address */
#define LMEM_PSCLCR_CACHEADDR(x)                 (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_CACHEADDR_SHIFT)) & LMEM_PSCLCR_CACHEADDR_MASK)

#define LMEM_PSCLCR_WSEL_MASK                    (0x4000U)
#define LMEM_PSCLCR_WSEL_SHIFT                   (14U)
/*! WSEL - Way select
 *  0b0..Way 0
 *  0b1..Way 1
 */
#define LMEM_PSCLCR_WSEL(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_WSEL_SHIFT)) & LMEM_PSCLCR_WSEL_MASK)

#define LMEM_PSCLCR_TDSEL_MASK                   (0x10000U)
#define LMEM_PSCLCR_TDSEL_SHIFT                  (16U)
/*! TDSEL - Tag/Data Select
 *  0b0..Data
 *  0b1..Tag
 */
#define LMEM_PSCLCR_TDSEL(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_TDSEL_SHIFT)) & LMEM_PSCLCR_TDSEL_MASK)

#define LMEM_PSCLCR_LCIVB_MASK                   (0x100000U)
#define LMEM_PSCLCR_LCIVB_SHIFT                  (20U)
/*! LCIVB - Line Command Initial Valid Bit */
#define LMEM_PSCLCR_LCIVB(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_LCIVB_SHIFT)) & LMEM_PSCLCR_LCIVB_MASK)

#define LMEM_PSCLCR_LCIMB_MASK                   (0x200000U)
#define LMEM_PSCLCR_LCIMB_SHIFT                  (21U)
/*! LCIMB - Line Command Initial Modified Bit */
#define LMEM_PSCLCR_LCIMB(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_LCIMB_SHIFT)) & LMEM_PSCLCR_LCIMB_MASK)

#define LMEM_PSCLCR_LCWAY_MASK                   (0x400000U)
#define LMEM_PSCLCR_LCWAY_SHIFT                  (22U)
/*! LCWAY - Line Command Way */
#define LMEM_PSCLCR_LCWAY(x)                     (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_LCWAY_SHIFT)) & LMEM_PSCLCR_LCWAY_MASK)

#define LMEM_PSCLCR_LCMD_MASK                    (0x3000000U)
#define LMEM_PSCLCR_LCMD_SHIFT                   (24U)
/*! LCMD - Line Command
 *  0b00..Search and read or write
 *  0b01..Invalidate
 *  0b10..Push
 *  0b11..Clear
 */
#define LMEM_PSCLCR_LCMD(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_LCMD_SHIFT)) & LMEM_PSCLCR_LCMD_MASK)

#define LMEM_PSCLCR_LADSEL_MASK                  (0x4000000U)
#define LMEM_PSCLCR_LADSEL_SHIFT                 (26U)
/*! LADSEL - Line Address Select
 *  0b0..Cache address
 *  0b1..Physical address
 */
#define LMEM_PSCLCR_LADSEL(x)                    (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_LADSEL_SHIFT)) & LMEM_PSCLCR_LADSEL_MASK)

#define LMEM_PSCLCR_LACC_MASK                    (0x8000000U)
#define LMEM_PSCLCR_LACC_SHIFT                   (27U)
/*! LACC - Line access type
 *  0b0..Read
 *  0b1..Write
 */
#define LMEM_PSCLCR_LACC(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCLCR_LACC_SHIFT)) & LMEM_PSCLCR_LACC_MASK)
/*! @} */

/*! @name PSCSAR - PS bus Cache search address register */
/*! @{ */

#define LMEM_PSCSAR_LGO_MASK                     (0x1U)
#define LMEM_PSCSAR_LGO_SHIFT                    (0U)
/*! LGO - Initiate Cache Line Command
 *  0b0..Write: no effect. Read: no line command active.
 *  0b1..Write: initiate line command indicated by bits CLCR[27:24]. Read: line command active.
 */
#define LMEM_PSCSAR_LGO(x)                       (((uint32_t)(((uint32_t)(x)) << LMEM_PSCSAR_LGO_SHIFT)) & LMEM_PSCSAR_LGO_MASK)

#define LMEM_PSCSAR_PHYADDR_MASK                 (0xFFFFFFFEU)
#define LMEM_PSCSAR_PHYADDR_SHIFT                (1U)
/*! PHYADDR - Physical Address */
#define LMEM_PSCSAR_PHYADDR(x)                   (((uint32_t)(((uint32_t)(x)) << LMEM_PSCSAR_PHYADDR_SHIFT)) & LMEM_PSCSAR_PHYADDR_MASK)
/*! @} */

/*! @name PSCCVR - PS bus Cache read/write value register */
/*! @{ */

#define LMEM_PSCCVR_DATA_MASK                    (0xFFFFFFFFU)
#define LMEM_PSCCVR_DATA_SHIFT                   (0U)
/*! DATA - Cache read/write Data */
#define LMEM_PSCCVR_DATA(x)                      (((uint32_t)(((uint32_t)(x)) << LMEM_PSCCVR_DATA_SHIFT)) & LMEM_PSCCVR_DATA_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LMEM_Register_Masks */


/*!
 * @}
 */ /* end of group LMEM_Peripheral_Access_Layer */


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


#endif  /* PERI_LMEM_H_ */

