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
**         CMSIS Peripheral Access Layer for SSARC_HP
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
 * @file PERI_SSARC_HP.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for SSARC_HP
 *
 * CMSIS Peripheral Access Layer for SSARC_HP
 */

#if !defined(PERI_SSARC_HP_H_)
#define PERI_SSARC_HP_H_                         /**< Symbol preventing repeated inclusion */

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
   -- SSARC_HP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SSARC_HP_Peripheral_Access_Layer SSARC_HP Peripheral Access Layer
 * @{
 */

/** SSARC_HP - Size of Registers Arrays */
#define SSARC_HP_DESC_COUNT                       1024u

/** SSARC_HP - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x10 */
    __IO uint32_t SRAM0;                             /**< Description Address Register, array offset: 0x0, array step: 0x10 */
    __IO uint32_t SRAM1;                             /**< Description Data Register, array offset: 0x4, array step: 0x10 */
    __IO uint32_t SRAM2;                             /**< Description Control Register, array offset: 0x8, array step: 0x10 */
         uint8_t RESERVED_0[4];
  } DESC[SSARC_HP_DESC_COUNT];
} SSARC_HP_Type;

/* ----------------------------------------------------------------------------
   -- SSARC_HP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SSARC_HP_Register_Masks SSARC_HP Register Masks
 * @{
 */

/*! @name SRAM0 - Description Address Register */
/*! @{ */

#define SSARC_HP_SRAM0_ADDR_MASK                 (0xFFFFFFFFU)
#define SSARC_HP_SRAM0_ADDR_SHIFT                (0U)
/*! ADDR - Address field */
#define SSARC_HP_SRAM0_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) << SSARC_HP_SRAM0_ADDR_SHIFT)) & SSARC_HP_SRAM0_ADDR_MASK)
/*! @} */

/* The count of SSARC_HP_SRAM0 */
#define SSARC_HP_SRAM0_COUNT                     (1024U)

/*! @name SRAM1 - Description Data Register */
/*! @{ */

#define SSARC_HP_SRAM1_DATA_MASK                 (0xFFFFFFFFU)
#define SSARC_HP_SRAM1_DATA_SHIFT                (0U)
/*! DATA - Data field */
#define SSARC_HP_SRAM1_DATA(x)                   (((uint32_t)(((uint32_t)(x)) << SSARC_HP_SRAM1_DATA_SHIFT)) & SSARC_HP_SRAM1_DATA_MASK)
/*! @} */

/* The count of SSARC_HP_SRAM1 */
#define SSARC_HP_SRAM1_COUNT                     (1024U)

/*! @name SRAM2 - Description Control Register */
/*! @{ */

#define SSARC_HP_SRAM2_TYPE_MASK                 (0x7U)
#define SSARC_HP_SRAM2_TYPE_SHIFT                (0U)
/*! TYPE - Type field
 *  0b000..SR
 *  0b001..WO
 *  0b010..RMW_OR
 *  0b011..RMW_AND
 *  0b100..DELAY
 *  0b101..POLLING_0
 *  0b110..POLLING_1
 *  0b111..Reserved
 */
#define SSARC_HP_SRAM2_TYPE(x)                   (((uint32_t)(((uint32_t)(x)) << SSARC_HP_SRAM2_TYPE_SHIFT)) & SSARC_HP_SRAM2_TYPE_MASK)

#define SSARC_HP_SRAM2_SV_EN_MASK                (0x10U)
#define SSARC_HP_SRAM2_SV_EN_SHIFT               (4U)
/*! SV_EN - Save Enable
 *  0b0..Do not use this descriptor in the save operation
 *  0b1..Use this descriptor in the save operation
 */
#define SSARC_HP_SRAM2_SV_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SSARC_HP_SRAM2_SV_EN_SHIFT)) & SSARC_HP_SRAM2_SV_EN_MASK)

#define SSARC_HP_SRAM2_RT_EN_MASK                (0x20U)
#define SSARC_HP_SRAM2_RT_EN_SHIFT               (5U)
/*! RT_EN - Restore Enable
 *  0b0..Do not use this descriptor for the restore operation
 *  0b1..Use this descriptor for the restore operation
 */
#define SSARC_HP_SRAM2_RT_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SSARC_HP_SRAM2_RT_EN_SHIFT)) & SSARC_HP_SRAM2_RT_EN_MASK)

#define SSARC_HP_SRAM2_SIZE_MASK                 (0xC0U)
#define SSARC_HP_SRAM2_SIZE_SHIFT                (6U)
/*! SIZE - Size field
 *  0b00..8-bit
 *  0b01..16-bit
 *  0b10..32-bit
 *  0b11..Reserved
 */
#define SSARC_HP_SRAM2_SIZE(x)                   (((uint32_t)(((uint32_t)(x)) << SSARC_HP_SRAM2_SIZE_SHIFT)) & SSARC_HP_SRAM2_SIZE_MASK)
/*! @} */

/* The count of SSARC_HP_SRAM2 */
#define SSARC_HP_SRAM2_COUNT                     (1024U)


/*!
 * @}
 */ /* end of group SSARC_HP_Register_Masks */


/*!
 * @}
 */ /* end of group SSARC_HP_Peripheral_Access_Layer */


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


#endif  /* PERI_SSARC_HP_H_ */

