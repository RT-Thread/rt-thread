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
**         CMSIS Peripheral Access Layer for VMBANDGAP
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
 * @file PERI_VMBANDGAP.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for VMBANDGAP
 *
 * CMSIS Peripheral Access Layer for VMBANDGAP
 */

#if !defined(PERI_VMBANDGAP_H_)
#define PERI_VMBANDGAP_H_                        /**< Symbol preventing repeated inclusion */

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
   -- VMBANDGAP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VMBANDGAP_Peripheral_Access_Layer VMBANDGAP Peripheral Access Layer
 * @{
 */

/** VMBANDGAP - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0 */
    __IO uint32_t RW;                                /**< Analog Control Register CTRL0, offset: 0x0 */
    __IO uint32_t SET;                               /**< Analog Control Register CTRL0, offset: 0x4 */
    __IO uint32_t CLR;                               /**< Analog Control Register CTRL0, offset: 0x8 */
    __IO uint32_t TOG;                               /**< Analog Control Register CTRL0, offset: 0xC */
  } CTRL0;
       uint8_t RESERVED_0[64];
  struct {                                         /* offset: 0x50 */
    __I  uint32_t RW;                                /**< Analog Status Register STAT0, offset: 0x50 */
    __I  uint32_t SET;                               /**< Analog Status Register STAT0, offset: 0x54 */
    __I  uint32_t CLR;                               /**< Analog Status Register STAT0, offset: 0x58 */
    __I  uint32_t TOG;                               /**< Analog Status Register STAT0, offset: 0x5C */
  } STAT0;
} VMBANDGAP_Type;

/* ----------------------------------------------------------------------------
   -- VMBANDGAP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VMBANDGAP_Register_Masks VMBANDGAP Register Masks
 * @{
 */

/*! @name CTRL0 - Analog Control Register CTRL0 */
/*! @{ */

#define VMBANDGAP_CTRL0_REFTOP_PWD_MASK          (0x1U)
#define VMBANDGAP_CTRL0_REFTOP_PWD_SHIFT         (0U)
/*! REFTOP_PWD - Master power-down for bandgap module */
#define VMBANDGAP_CTRL0_REFTOP_PWD(x)            (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_CTRL0_REFTOP_PWD_SHIFT)) & VMBANDGAP_CTRL0_REFTOP_PWD_MASK)

#define VMBANDGAP_CTRL0_REFTOP_LINREGREF_PWD_MASK (0x2U)
#define VMBANDGAP_CTRL0_REFTOP_LINREGREF_PWD_SHIFT (1U)
/*! REFTOP_LINREGREF_PWD - Power-down for bandgap voltage-reference buffer */
#define VMBANDGAP_CTRL0_REFTOP_LINREGREF_PWD(x)  (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_CTRL0_REFTOP_LINREGREF_PWD_SHIFT)) & VMBANDGAP_CTRL0_REFTOP_LINREGREF_PWD_MASK)

#define VMBANDGAP_CTRL0_REFTOP_PWDVBGUP_MASK     (0x4U)
#define VMBANDGAP_CTRL0_REFTOP_PWDVBGUP_SHIFT    (2U)
/*! REFTOP_PWDVBGUP - Power-down VBGUP detector in bandgap */
#define VMBANDGAP_CTRL0_REFTOP_PWDVBGUP(x)       (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_CTRL0_REFTOP_PWDVBGUP_SHIFT)) & VMBANDGAP_CTRL0_REFTOP_PWDVBGUP_MASK)

#define VMBANDGAP_CTRL0_REFTOP_LOWPOWER_MASK     (0x8U)
#define VMBANDGAP_CTRL0_REFTOP_LOWPOWER_SHIFT    (3U)
/*! REFTOP_LOWPOWER - Low-power control bit */
#define VMBANDGAP_CTRL0_REFTOP_LOWPOWER(x)       (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_CTRL0_REFTOP_LOWPOWER_SHIFT)) & VMBANDGAP_CTRL0_REFTOP_LOWPOWER_MASK)

#define VMBANDGAP_CTRL0_REFTOP_SELFBIASOFF_MASK  (0x10U)
#define VMBANDGAP_CTRL0_REFTOP_SELFBIASOFF_SHIFT (4U)
/*! REFTOP_SELFBIASOFF - bandgap self-bias control bit */
#define VMBANDGAP_CTRL0_REFTOP_SELFBIASOFF(x)    (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_CTRL0_REFTOP_SELFBIASOFF_SHIFT)) & VMBANDGAP_CTRL0_REFTOP_SELFBIASOFF_MASK)
/*! @} */

/*! @name STAT0 - Analog Status Register STAT0 */
/*! @{ */

#define VMBANDGAP_STAT0_REFTOP_VBGUP_MASK        (0x1U)
#define VMBANDGAP_STAT0_REFTOP_VBGUP_SHIFT       (0U)
/*! REFTOP_VBGUP - Brief description here */
#define VMBANDGAP_STAT0_REFTOP_VBGUP(x)          (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_STAT0_REFTOP_VBGUP_SHIFT)) & VMBANDGAP_STAT0_REFTOP_VBGUP_MASK)

#define VMBANDGAP_STAT0_VDD1_PORB_MASK           (0x2U)
#define VMBANDGAP_STAT0_VDD1_PORB_SHIFT          (1U)
/*! VDD1_PORB - Brief description here */
#define VMBANDGAP_STAT0_VDD1_PORB(x)             (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_STAT0_VDD1_PORB_SHIFT)) & VMBANDGAP_STAT0_VDD1_PORB_MASK)

#define VMBANDGAP_STAT0_VDD2_PORB_MASK           (0x4U)
#define VMBANDGAP_STAT0_VDD2_PORB_SHIFT          (2U)
/*! VDD2_PORB - Brief description here */
#define VMBANDGAP_STAT0_VDD2_PORB(x)             (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_STAT0_VDD2_PORB_SHIFT)) & VMBANDGAP_STAT0_VDD2_PORB_MASK)

#define VMBANDGAP_STAT0_VDD3_PORB_MASK           (0x8U)
#define VMBANDGAP_STAT0_VDD3_PORB_SHIFT          (3U)
/*! VDD3_PORB - Brief description here */
#define VMBANDGAP_STAT0_VDD3_PORB(x)             (((uint32_t)(((uint32_t)(x)) << VMBANDGAP_STAT0_VDD3_PORB_SHIFT)) & VMBANDGAP_STAT0_VDD3_PORB_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group VMBANDGAP_Register_Masks */


/*!
 * @}
 */ /* end of group VMBANDGAP_Peripheral_Access_Layer */


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


#endif  /* PERI_VMBANDGAP_H_ */

