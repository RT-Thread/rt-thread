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
**         CMSIS Peripheral Access Layer for CCM
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
 * @file PERI_CCM.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for CCM
 *
 * CMSIS Peripheral Access Layer for CCM
 */

#if !defined(PERI_CCM_H_)
#define PERI_CCM_H_                              /**< Symbol preventing repeated inclusion */

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
   -- CCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CCM_Peripheral_Access_Layer CCM Peripheral Access Layer
 * @{
 */

/** CCM - Size of Registers Arrays */
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_COUNT  16u
#define CCM_CLOCK_ROOT_COUNT                      79u
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_COUNT 16u
#define CCM_CLOCK_GROUP_COUNT                     2u
#define CCM_GPR_SHARED_COUNT                      8u
#define CCM_OSCPLL_COUNT                          29u
#define CCM_LPCG_COUNT                            138u

/** CCM - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x80 */
    __IO uint32_t CONTROL;                           /**< Clock root control, array offset: 0x0, array step: 0x80 */
    __IO uint32_t CONTROL_SET;                       /**< Clock root control, array offset: 0x4, array step: 0x80 */
    __IO uint32_t CONTROL_CLR;                       /**< Clock root control, array offset: 0x8, array step: 0x80 */
    __IO uint32_t CONTROL_TOG;                       /**< Clock root control, array offset: 0xC, array step: 0x80 */
         uint8_t RESERVED_0[16];
    __I  uint32_t STATUS0;                           /**< Clock root working status, array offset: 0x20, array step: 0x80 */
    __I  uint32_t STATUS1;                           /**< Clock root low power status, array offset: 0x24, array step: 0x80 */
         uint8_t RESERVED_1[4];
    __I  uint32_t CONFIG;                            /**< Clock root configuration, array offset: 0x2C, array step: 0x80 */
    __IO uint32_t AUTHEN;                            /**< Clock root access control, array offset: 0x30, array step: 0x80 */
    __IO uint32_t AUTHEN_SET;                        /**< Clock root access control, array offset: 0x34, array step: 0x80 */
    __IO uint32_t AUTHEN_CLR;                        /**< Clock root access control, array offset: 0x38, array step: 0x80 */
    __IO uint32_t AUTHEN_TOG;                        /**< Clock root access control, array offset: 0x3C, array step: 0x80 */
    __IO uint32_t SETPOINT[CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_COUNT];   /**< Setpoint setting, array offset: 0x40, array step: index*0x80, index2*0x4, valid indices: [0][0-15], [1][0-15], [2][0-15], [3][0-15], [4][0-15], [20][0-15], [21][0-15], [77][0-15], [78][0-15] */
  } CLOCK_ROOT[CCM_CLOCK_ROOT_COUNT];
       uint8_t RESERVED_0[6272];
  struct {                                         /* offset: 0x4000, array step: 0x80 */
    __IO uint32_t CONTROL;                           /**< Clock group control, array offset: 0x4000, array step: 0x80 */
    __IO uint32_t CONTROL_SET;                       /**< Clock group control, array offset: 0x4004, array step: 0x80 */
    __IO uint32_t CONTROL_CLR;                       /**< Clock group control, array offset: 0x4008, array step: 0x80 */
    __IO uint32_t CONTROL_TOG;                       /**< Clock group control, array offset: 0x400C, array step: 0x80 */
         uint8_t RESERVED_0[16];
    __IO uint32_t STATUS0;                           /**< Clock group working status, array offset: 0x4020, array step: 0x80 */
    __I  uint32_t STATUS1;                           /**< Clock group low power/extend status, array offset: 0x4024, array step: 0x80 */
         uint8_t RESERVED_1[4];
    __I  uint32_t CONFIG;                            /**< Clock group configuration, array offset: 0x402C, array step: 0x80 */
    __IO uint32_t AUTHEN;                            /**< Clock group access control, array offset: 0x4030, array step: 0x80 */
    __IO uint32_t AUTHEN_SET;                        /**< Clock group access control, array offset: 0x4034, array step: 0x80 */
    __IO uint32_t AUTHEN_CLR;                        /**< Clock group access control, array offset: 0x4038, array step: 0x80 */
    __IO uint32_t AUTHEN_TOG;                        /**< Clock group access control, array offset: 0x403C, array step: 0x80 */
    __IO uint32_t SETPOINT[CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_COUNT];   /**< Setpoint setting, array offset: 0x4040, array step: index*0x80, index2*0x4 */
  } CLOCK_GROUP[CCM_CLOCK_GROUP_COUNT];
       uint8_t RESERVED_1[1792];
  struct {                                         /* offset: 0x4800, array step: 0x20 */
    __IO uint32_t GPR_SHARED;                        /**< General Purpose Register, array offset: 0x4800, array step: 0x20 */
    __IO uint32_t SET;                               /**< General Purpose Register, array offset: 0x4804, array step: 0x20 */
    __IO uint32_t CLR;                               /**< General Purpose Register, array offset: 0x4808, array step: 0x20 */
    __IO uint32_t TOG;                               /**< General Purpose Register, array offset: 0x480C, array step: 0x20 */
    __IO uint32_t AUTHEN;                            /**< GPR access control, array offset: 0x4810, array step: 0x20 */
    __IO uint32_t AUTHEN_SET;                        /**< GPR access control, array offset: 0x4814, array step: 0x20 */
    __IO uint32_t AUTHEN_CLR;                        /**< GPR access control, array offset: 0x4818, array step: 0x20 */
    __IO uint32_t AUTHEN_TOG;                        /**< GPR access control, array offset: 0x481C, array step: 0x20 */
  } GPR_SHARED[CCM_GPR_SHARED_COUNT];
       uint8_t RESERVED_2[800];
  __IO uint32_t GPR_PRIVATE1;                      /**< General Purpose Register, offset: 0x4C20 */
  __IO uint32_t GPR_PRIVATE1_SET;                  /**< General Purpose Register, offset: 0x4C24 */
  __IO uint32_t GPR_PRIVATE1_CLR;                  /**< General Purpose Register, offset: 0x4C28 */
  __IO uint32_t GPR_PRIVATE1_TOG;                  /**< General Purpose Register, offset: 0x4C2C */
  __IO uint32_t GPR_PRIVATE1_AUTHEN;               /**< GPR access control, offset: 0x4C30 */
  __IO uint32_t GPR_PRIVATE1_AUTHEN_SET;           /**< GPR access control, offset: 0x4C34 */
  __IO uint32_t GPR_PRIVATE1_AUTHEN_CLR;           /**< GPR access control, offset: 0x4C38 */
  __IO uint32_t GPR_PRIVATE1_AUTHEN_TOG;           /**< GPR access control, offset: 0x4C3C */
  __IO uint32_t GPR_PRIVATE2;                      /**< General Purpose Register, offset: 0x4C40 */
  __IO uint32_t GPR_PRIVATE2_SET;                  /**< General Purpose Register, offset: 0x4C44 */
  __IO uint32_t GPR_PRIVATE2_CLR;                  /**< General Purpose Register, offset: 0x4C48 */
  __IO uint32_t GPR_PRIVATE2_TOG;                  /**< General Purpose Register, offset: 0x4C4C */
  __IO uint32_t GPR_PRIVATE2_AUTHEN;               /**< GPR access control, offset: 0x4C50 */
  __IO uint32_t GPR_PRIVATE2_AUTHEN_SET;           /**< GPR access control, offset: 0x4C54 */
  __IO uint32_t GPR_PRIVATE2_AUTHEN_CLR;           /**< GPR access control, offset: 0x4C58 */
  __IO uint32_t GPR_PRIVATE2_AUTHEN_TOG;           /**< GPR access control, offset: 0x4C5C */
  __IO uint32_t GPR_PRIVATE3;                      /**< General Purpose Register, offset: 0x4C60 */
  __IO uint32_t GPR_PRIVATE3_SET;                  /**< General Purpose Register, offset: 0x4C64 */
  __IO uint32_t GPR_PRIVATE3_CLR;                  /**< General Purpose Register, offset: 0x4C68 */
  __IO uint32_t GPR_PRIVATE3_TOG;                  /**< General Purpose Register, offset: 0x4C6C */
  __IO uint32_t GPR_PRIVATE3_AUTHEN;               /**< GPR access control, offset: 0x4C70 */
  __IO uint32_t GPR_PRIVATE3_AUTHEN_SET;           /**< GPR access control, offset: 0x4C74 */
  __IO uint32_t GPR_PRIVATE3_AUTHEN_CLR;           /**< GPR access control, offset: 0x4C78 */
  __IO uint32_t GPR_PRIVATE3_AUTHEN_TOG;           /**< GPR access control, offset: 0x4C7C */
  __IO uint32_t GPR_PRIVATE4;                      /**< General Purpose Register, offset: 0x4C80 */
  __IO uint32_t GPR_PRIVATE4_SET;                  /**< General Purpose Register, offset: 0x4C84 */
  __IO uint32_t GPR_PRIVATE4_CLR;                  /**< General Purpose Register, offset: 0x4C88 */
  __IO uint32_t GPR_PRIVATE4_TOG;                  /**< General Purpose Register, offset: 0x4C8C */
  __IO uint32_t GPR_PRIVATE4_AUTHEN;               /**< GPR access control, offset: 0x4C90 */
  __IO uint32_t GPR_PRIVATE4_AUTHEN_SET;           /**< GPR access control, offset: 0x4C94 */
  __IO uint32_t GPR_PRIVATE4_AUTHEN_CLR;           /**< GPR access control, offset: 0x4C98 */
  __IO uint32_t GPR_PRIVATE4_AUTHEN_TOG;           /**< GPR access control, offset: 0x4C9C */
  __IO uint32_t GPR_PRIVATE5;                      /**< General Purpose Register, offset: 0x4CA0 */
  __IO uint32_t GPR_PRIVATE5_SET;                  /**< General Purpose Register, offset: 0x4CA4 */
  __IO uint32_t GPR_PRIVATE5_CLR;                  /**< General Purpose Register, offset: 0x4CA8 */
  __IO uint32_t GPR_PRIVATE5_TOG;                  /**< General Purpose Register, offset: 0x4CAC */
  __IO uint32_t GPR_PRIVATE5_AUTHEN;               /**< GPR access control, offset: 0x4CB0 */
  __IO uint32_t GPR_PRIVATE5_AUTHEN_SET;           /**< GPR access control, offset: 0x4CB4 */
  __IO uint32_t GPR_PRIVATE5_AUTHEN_CLR;           /**< GPR access control, offset: 0x4CB8 */
  __IO uint32_t GPR_PRIVATE5_AUTHEN_TOG;           /**< GPR access control, offset: 0x4CBC */
  __IO uint32_t GPR_PRIVATE6;                      /**< General Purpose Register, offset: 0x4CC0 */
  __IO uint32_t GPR_PRIVATE6_SET;                  /**< General Purpose Register, offset: 0x4CC4 */
  __IO uint32_t GPR_PRIVATE6_CLR;                  /**< General Purpose Register, offset: 0x4CC8 */
  __IO uint32_t GPR_PRIVATE6_TOG;                  /**< General Purpose Register, offset: 0x4CCC */
  __IO uint32_t GPR_PRIVATE6_AUTHEN;               /**< GPR access control, offset: 0x4CD0 */
  __IO uint32_t GPR_PRIVATE6_AUTHEN_SET;           /**< GPR access control, offset: 0x4CD4 */
  __IO uint32_t GPR_PRIVATE6_AUTHEN_CLR;           /**< GPR access control, offset: 0x4CD8 */
  __IO uint32_t GPR_PRIVATE6_AUTHEN_TOG;           /**< GPR access control, offset: 0x4CDC */
  __IO uint32_t GPR_PRIVATE7;                      /**< General Purpose Register, offset: 0x4CE0 */
  __IO uint32_t GPR_PRIVATE7_SET;                  /**< General Purpose Register, offset: 0x4CE4 */
  __IO uint32_t GPR_PRIVATE7_CLR;                  /**< General Purpose Register, offset: 0x4CE8 */
  __IO uint32_t GPR_PRIVATE7_TOG;                  /**< General Purpose Register, offset: 0x4CEC */
  __IO uint32_t GPR_PRIVATE7_AUTHEN;               /**< GPR access control, offset: 0x4CF0 */
  __IO uint32_t GPR_PRIVATE7_AUTHEN_SET;           /**< GPR access control, offset: 0x4CF4 */
  __IO uint32_t GPR_PRIVATE7_AUTHEN_CLR;           /**< GPR access control, offset: 0x4CF8 */
  __IO uint32_t GPR_PRIVATE7_AUTHEN_TOG;           /**< GPR access control, offset: 0x4CFC */
       uint8_t RESERVED_3[768];
  struct {                                         /* offset: 0x5000, array step: 0x20 */
    __IO uint32_t DIRECT;                            /**< Clock source direct control, array offset: 0x5000, array step: 0x20 */
    __IO uint32_t DOMAINr;                           /**< Clock source domain control, array offset: 0x5004, array step: 0x20, 'r' suffix has been added to avoid clash with DOMAIN symbol in math.h */
    __IO uint32_t SETPOINT;                          /**< Clock source Setpoint setting, array offset: 0x5008, array step: 0x20 */
         uint8_t RESERVED_0[4];
    __I  uint32_t STATUS0;                           /**< Clock source working status, array offset: 0x5010, array step: 0x20 */
    __I  uint32_t STATUS1;                           /**< Clock source low power status, array offset: 0x5014, array step: 0x20 */
    __I  uint32_t CONFIG;                            /**< Clock source configuration, array offset: 0x5018, array step: 0x20 */
    __IO uint32_t AUTHEN;                            /**< Clock source access control, array offset: 0x501C, array step: 0x20 */
  } OSCPLL[CCM_OSCPLL_COUNT];
       uint8_t RESERVED_4[3168];
  struct {                                         /* offset: 0x6000, array step: 0x20 */
    __IO uint32_t DIRECT;                            /**< LPCG direct control, array offset: 0x6000, array step: 0x20 */
    __IO uint32_t DOMAINr;                           /**< LPCG domain control, array offset: 0x6004, array step: 0x20, 'r' suffix has been added to avoid clash with DOMAIN symbol in math.h */
    __IO uint32_t SETPOINT;                          /**< LPCG Setpoint setting, array offset: 0x6008, array step: 0x20, valid indices: [2-12, 14-19, 24-40, 43-48] */
         uint8_t RESERVED_0[4];
    __I  uint32_t STATUS0;                           /**< LPCG working status, array offset: 0x6010, array step: 0x20 */
    __I  uint32_t STATUS1;                           /**< LPCG low power status, array offset: 0x6014, array step: 0x20 */
    __I  uint32_t CONFIG;                            /**< LPCG configuration, array offset: 0x6018, array step: 0x20 */
    __IO uint32_t AUTHEN;                            /**< LPCG access control, array offset: 0x601C, array step: 0x20 */
  } LPCG[CCM_LPCG_COUNT];
} CCM_Type;

/* ----------------------------------------------------------------------------
   -- CCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CCM_Register_Masks CCM Register Masks
 * @{
 */

/*! @name CLOCK_ROOT_CONTROL - Clock root control */
/*! @{ */

#define CCM_CLOCK_ROOT_CONTROL_DIV_MASK          (0xFFU)
#define CCM_CLOCK_ROOT_CONTROL_DIV_SHIFT         (0U)
/*! DIV - Clock divider */
#define CCM_CLOCK_ROOT_CONTROL_DIV(x)            (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_DIV_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_DIV_MASK)

#define CCM_CLOCK_ROOT_CONTROL_MUX_MASK          (0x700U)
#define CCM_CLOCK_ROOT_CONTROL_MUX_SHIFT         (8U)
/*! MUX - Clock multiplexer */
#define CCM_CLOCK_ROOT_CONTROL_MUX(x)            (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_MUX_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_MUX_MASK)

#define CCM_CLOCK_ROOT_CONTROL_OFF_MASK          (0x1000000U)
#define CCM_CLOCK_ROOT_CONTROL_OFF_SHIFT         (24U)
/*! OFF - OFF
 *  0b0..Turn on clock
 *  0b1..Turn off clock
 */
#define CCM_CLOCK_ROOT_CONTROL_OFF(x)            (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_OFF_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_CONTROL */
#define CCM_CLOCK_ROOT_CONTROL_COUNT             (79U)

/*! @name CLOCK_ROOT_CONTROL_SET - Clock root control */
/*! @{ */

#define CCM_CLOCK_ROOT_CONTROL_SET_DIV_MASK      (0xFFU)
#define CCM_CLOCK_ROOT_CONTROL_SET_DIV_SHIFT     (0U)
/*! DIV - Clock divider */
#define CCM_CLOCK_ROOT_CONTROL_SET_DIV(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_SET_DIV_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_SET_DIV_MASK)

#define CCM_CLOCK_ROOT_CONTROL_SET_MUX_MASK      (0x700U)
#define CCM_CLOCK_ROOT_CONTROL_SET_MUX_SHIFT     (8U)
/*! MUX - Clock multiplexer */
#define CCM_CLOCK_ROOT_CONTROL_SET_MUX(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_SET_MUX_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_SET_MUX_MASK)

#define CCM_CLOCK_ROOT_CONTROL_SET_OFF_MASK      (0x1000000U)
#define CCM_CLOCK_ROOT_CONTROL_SET_OFF_SHIFT     (24U)
/*! OFF - OFF */
#define CCM_CLOCK_ROOT_CONTROL_SET_OFF(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_SET_OFF_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_SET_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_CONTROL_SET */
#define CCM_CLOCK_ROOT_CONTROL_SET_COUNT         (79U)

/*! @name CLOCK_ROOT_CONTROL_CLR - Clock root control */
/*! @{ */

#define CCM_CLOCK_ROOT_CONTROL_CLR_DIV_MASK      (0xFFU)
#define CCM_CLOCK_ROOT_CONTROL_CLR_DIV_SHIFT     (0U)
/*! DIV - Clock divider */
#define CCM_CLOCK_ROOT_CONTROL_CLR_DIV(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_CLR_DIV_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_CLR_DIV_MASK)

#define CCM_CLOCK_ROOT_CONTROL_CLR_MUX_MASK      (0x700U)
#define CCM_CLOCK_ROOT_CONTROL_CLR_MUX_SHIFT     (8U)
/*! MUX - Clock multiplexer */
#define CCM_CLOCK_ROOT_CONTROL_CLR_MUX(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_CLR_MUX_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_CLR_MUX_MASK)

#define CCM_CLOCK_ROOT_CONTROL_CLR_OFF_MASK      (0x1000000U)
#define CCM_CLOCK_ROOT_CONTROL_CLR_OFF_SHIFT     (24U)
/*! OFF - OFF */
#define CCM_CLOCK_ROOT_CONTROL_CLR_OFF(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_CLR_OFF_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_CLR_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_CONTROL_CLR */
#define CCM_CLOCK_ROOT_CONTROL_CLR_COUNT         (79U)

/*! @name CLOCK_ROOT_CONTROL_TOG - Clock root control */
/*! @{ */

#define CCM_CLOCK_ROOT_CONTROL_TOG_DIV_MASK      (0xFFU)
#define CCM_CLOCK_ROOT_CONTROL_TOG_DIV_SHIFT     (0U)
/*! DIV - Clock divider */
#define CCM_CLOCK_ROOT_CONTROL_TOG_DIV(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_TOG_DIV_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_TOG_DIV_MASK)

#define CCM_CLOCK_ROOT_CONTROL_TOG_MUX_MASK      (0x700U)
#define CCM_CLOCK_ROOT_CONTROL_TOG_MUX_SHIFT     (8U)
/*! MUX - Clock multiplexer */
#define CCM_CLOCK_ROOT_CONTROL_TOG_MUX(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_TOG_MUX_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_TOG_MUX_MASK)

#define CCM_CLOCK_ROOT_CONTROL_TOG_OFF_MASK      (0x1000000U)
#define CCM_CLOCK_ROOT_CONTROL_TOG_OFF_SHIFT     (24U)
/*! OFF - OFF */
#define CCM_CLOCK_ROOT_CONTROL_TOG_OFF(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONTROL_TOG_OFF_SHIFT)) & CCM_CLOCK_ROOT_CONTROL_TOG_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_CONTROL_TOG */
#define CCM_CLOCK_ROOT_CONTROL_TOG_COUNT         (79U)

/*! @name CLOCK_ROOT_STATUS0 - Clock root working status */
/*! @{ */

#define CCM_CLOCK_ROOT_STATUS0_DIV_MASK          (0xFFU)
#define CCM_CLOCK_ROOT_STATUS0_DIV_SHIFT         (0U)
/*! DIV - Current clock root DIV setting */
#define CCM_CLOCK_ROOT_STATUS0_DIV(x)            (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_DIV_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_DIV_MASK)

#define CCM_CLOCK_ROOT_STATUS0_MUX_MASK          (0x700U)
#define CCM_CLOCK_ROOT_STATUS0_MUX_SHIFT         (8U)
/*! MUX - Current clock root MUX setting */
#define CCM_CLOCK_ROOT_STATUS0_MUX(x)            (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_MUX_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_MUX_MASK)

#define CCM_CLOCK_ROOT_STATUS0_OFF_MASK          (0x1000000U)
#define CCM_CLOCK_ROOT_STATUS0_OFF_SHIFT         (24U)
/*! OFF - Current clock root OFF setting
 *  0b0..Clock is running
 *  0b1..Clock is disabled/off
 */
#define CCM_CLOCK_ROOT_STATUS0_OFF(x)            (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_OFF_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_OFF_MASK)

#define CCM_CLOCK_ROOT_STATUS0_POWERDOWN_MASK    (0x8000000U)
#define CCM_CLOCK_ROOT_STATUS0_POWERDOWN_SHIFT   (27U)
/*! POWERDOWN - Current clock root POWERDOWN setting
 *  0b0..Clock root is running
 *  0b1..Clock root is Powered Down
 */
#define CCM_CLOCK_ROOT_STATUS0_POWERDOWN(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_POWERDOWN_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_POWERDOWN_MASK)

#define CCM_CLOCK_ROOT_STATUS0_SLICE_BUSY_MASK   (0x10000000U)
#define CCM_CLOCK_ROOT_STATUS0_SLICE_BUSY_SHIFT  (28U)
/*! SLICE_BUSY - Internal updating in generation logic
 *  0b0..Clock generation logic is not busy
 *  0b1..Clock generation logic is applying the new setting
 */
#define CCM_CLOCK_ROOT_STATUS0_SLICE_BUSY(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_SLICE_BUSY_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_SLICE_BUSY_MASK)

#define CCM_CLOCK_ROOT_STATUS0_UPDATE_FORWARD_MASK (0x20000000U)
#define CCM_CLOCK_ROOT_STATUS0_UPDATE_FORWARD_SHIFT (29U)
/*! UPDATE_FORWARD - Internal status synchronization to clock generation logic
 *  0b0..Synchronization not in process
 *  0b1..Synchronization in process
 */
#define CCM_CLOCK_ROOT_STATUS0_UPDATE_FORWARD(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_UPDATE_FORWARD_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_UPDATE_FORWARD_MASK)

#define CCM_CLOCK_ROOT_STATUS0_UPDATE_REVERSE_MASK (0x40000000U)
#define CCM_CLOCK_ROOT_STATUS0_UPDATE_REVERSE_SHIFT (30U)
/*! UPDATE_REVERSE - Internal status synchronization from clock generation logic
 *  0b0..Synchronization not in process
 *  0b1..Synchronization in process
 */
#define CCM_CLOCK_ROOT_STATUS0_UPDATE_REVERSE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_UPDATE_REVERSE_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_UPDATE_REVERSE_MASK)

#define CCM_CLOCK_ROOT_STATUS0_CHANGING_MASK     (0x80000000U)
#define CCM_CLOCK_ROOT_STATUS0_CHANGING_SHIFT    (31U)
/*! CHANGING - Internal updating in clock root
 *  0b0..Clock Status is not updating currently
 *  0b1..Clock generation logic is updating currently
 */
#define CCM_CLOCK_ROOT_STATUS0_CHANGING(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS0_CHANGING_SHIFT)) & CCM_CLOCK_ROOT_STATUS0_CHANGING_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_STATUS0 */
#define CCM_CLOCK_ROOT_STATUS0_COUNT             (79U)

/*! @name CLOCK_ROOT_STATUS1 - Clock root low power status */
/*! @{ */

#define CCM_CLOCK_ROOT_STATUS1_TARGET_SETPOINT_MASK (0xF0000U)
#define CCM_CLOCK_ROOT_STATUS1_TARGET_SETPOINT_SHIFT (16U)
/*! TARGET_SETPOINT - Target Setpoint */
#define CCM_CLOCK_ROOT_STATUS1_TARGET_SETPOINT(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS1_TARGET_SETPOINT_SHIFT)) & CCM_CLOCK_ROOT_STATUS1_TARGET_SETPOINT_MASK)

#define CCM_CLOCK_ROOT_STATUS1_CURRENT_SETPOINT_MASK (0xF00000U)
#define CCM_CLOCK_ROOT_STATUS1_CURRENT_SETPOINT_SHIFT (20U)
/*! CURRENT_SETPOINT - Current Setpoint */
#define CCM_CLOCK_ROOT_STATUS1_CURRENT_SETPOINT(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS1_CURRENT_SETPOINT_SHIFT)) & CCM_CLOCK_ROOT_STATUS1_CURRENT_SETPOINT_MASK)

#define CCM_CLOCK_ROOT_STATUS1_DOWN_REQUEST_MASK (0x1000000U)
#define CCM_CLOCK_ROOT_STATUS1_DOWN_REQUEST_SHIFT (24U)
/*! DOWN_REQUEST - Clock frequency decrease request
 *  0b0..Frequency decrease not requested
 *  0b1..Frequency decrease requested
 */
#define CCM_CLOCK_ROOT_STATUS1_DOWN_REQUEST(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS1_DOWN_REQUEST_SHIFT)) & CCM_CLOCK_ROOT_STATUS1_DOWN_REQUEST_MASK)

#define CCM_CLOCK_ROOT_STATUS1_DOWN_DONE_MASK    (0x2000000U)
#define CCM_CLOCK_ROOT_STATUS1_DOWN_DONE_SHIFT   (25U)
/*! DOWN_DONE - Clock frequency decrease finish
 *  0b0..Frequency decrease not completed
 *  0b1..Frequency decrease completed
 */
#define CCM_CLOCK_ROOT_STATUS1_DOWN_DONE(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS1_DOWN_DONE_SHIFT)) & CCM_CLOCK_ROOT_STATUS1_DOWN_DONE_MASK)

#define CCM_CLOCK_ROOT_STATUS1_UP_REQUEST_MASK   (0x4000000U)
#define CCM_CLOCK_ROOT_STATUS1_UP_REQUEST_SHIFT  (26U)
/*! UP_REQUEST - Clock frequency increase request
 *  0b0..Frequency increase not requested
 *  0b1..Frequency increase requested
 */
#define CCM_CLOCK_ROOT_STATUS1_UP_REQUEST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS1_UP_REQUEST_SHIFT)) & CCM_CLOCK_ROOT_STATUS1_UP_REQUEST_MASK)

#define CCM_CLOCK_ROOT_STATUS1_UP_DONE_MASK      (0x8000000U)
#define CCM_CLOCK_ROOT_STATUS1_UP_DONE_SHIFT     (27U)
/*! UP_DONE - Clock frequency increase finish
 *  0b0..Frequency increase not completed
 *  0b1..Frequency increase completed
 */
#define CCM_CLOCK_ROOT_STATUS1_UP_DONE(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_STATUS1_UP_DONE_SHIFT)) & CCM_CLOCK_ROOT_STATUS1_UP_DONE_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_STATUS1 */
#define CCM_CLOCK_ROOT_STATUS1_COUNT             (79U)

/*! @name CLOCK_ROOT_CONFIG - Clock root configuration */
/*! @{ */

#define CCM_CLOCK_ROOT_CONFIG_SETPOINT_PRESENT_MASK (0x10U)
#define CCM_CLOCK_ROOT_CONFIG_SETPOINT_PRESENT_SHIFT (4U)
/*! SETPOINT_PRESENT - Setpoint present
 *  0b0..Setpoint is not implemented.
 *  0b1..Setpoint is implemented.
 */
#define CCM_CLOCK_ROOT_CONFIG_SETPOINT_PRESENT(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CONFIG_SETPOINT_PRESENT_SHIFT)) & CCM_CLOCK_ROOT_CONFIG_SETPOINT_PRESENT_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_CONFIG */
#define CCM_CLOCK_ROOT_CONFIG_COUNT              (79U)

/*! @name CLOCK_ROOT_AUTHEN - Clock root access control */
/*! @{ */

#define CCM_CLOCK_ROOT_AUTHEN_TZ_USER_MASK       (0x1U)
#define CCM_CLOCK_ROOT_AUTHEN_TZ_USER_SHIFT      (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode
 *  0b1..Clock can be changed in user mode
 */
#define CCM_CLOCK_ROOT_AUTHEN_TZ_USER(x)         (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TZ_USER_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TZ_USER_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TZ_NS_MASK         (0x2U)
#define CCM_CLOCK_ROOT_AUTHEN_TZ_NS_SHIFT        (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode
 *  0b1..Can be changed in Non-secure mode
 */
#define CCM_CLOCK_ROOT_AUTHEN_TZ_NS(x)           (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TZ_NS_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TZ_NS_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_LOCK_TZ_MASK       (0x10U)
#define CCM_CLOCK_ROOT_AUTHEN_LOCK_TZ_SHIFT      (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked
 *  0b1..Trustzone setting is locked
 */
#define CCM_CLOCK_ROOT_AUTHEN_LOCK_TZ(x)         (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_LOCK_TZ_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_LOCK_TZ_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST_MASK    (0xF00U)
#define CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST_SHIFT   (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock
 *  0b0001..This domain is allowed to change clock
 */
#define CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_WHITE_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_LOCK_LIST_MASK     (0x1000U)
#define CCM_CLOCK_ROOT_AUTHEN_LOCK_LIST_SHIFT    (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked
 *  0b1..Whitelist is locked
 */
#define CCM_CLOCK_ROOT_AUTHEN_LOCK_LIST(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_LOCK_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_LOCK_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE_MASK   (0x10000U)
#define CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE_SHIFT  (16U)
/*! DOMAIN_MODE - Low power and access control by domain
 *  0b0..Clock does NOT work in Domain Mode
 *  0b1..Clock works in Domain Mode
 */
#define CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint
 *  0b0..Clock does NOT work in Setpoint Mode
 *  0b1..Clock works in Setpoint Mode
 */
#define CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SETPOINT_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_LOCK_MODE_MASK     (0x100000U)
#define CCM_CLOCK_ROOT_AUTHEN_LOCK_MODE_SHIFT    (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked
 *  0b1..MODE is locked
 */
#define CCM_CLOCK_ROOT_AUTHEN_LOCK_MODE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_LOCK_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_AUTHEN */
#define CCM_CLOCK_ROOT_AUTHEN_COUNT              (79U)

/*! @name CLOCK_ROOT_AUTHEN_SET - Clock root access control */
/*! @{ */

#define CCM_CLOCK_ROOT_AUTHEN_SET_TZ_USER_MASK   (0x1U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_TZ_USER_SHIFT  (0U)
/*! TZ_USER - User access */
#define CCM_CLOCK_ROOT_AUTHEN_SET_TZ_USER(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_TZ_USER_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SET_TZ_NS_MASK     (0x2U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_TZ_NS_SHIFT    (1U)
/*! TZ_NS - Non-secure access */
#define CCM_CLOCK_ROOT_AUTHEN_SET_TZ_NS(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_TZ_NS_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_TZ_MASK   (0x10U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_TZ_SHIFT  (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_TZ(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_CLOCK_ROOT_AUTHEN_SET_WHITE_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_LIST(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_CLOCK_ROOT_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SET_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint */
#define CCM_CLOCK_ROOT_AUTHEN_SET_SETPOINT_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_SETPOINT_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_AUTHEN_SET */
#define CCM_CLOCK_ROOT_AUTHEN_SET_COUNT          (79U)

/*! @name CLOCK_ROOT_AUTHEN_CLR - Clock root access control */
/*! @{ */

#define CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_USER_MASK   (0x1U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_USER_SHIFT  (0U)
/*! TZ_USER - User access */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_USER(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_NS_MASK     (0x2U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_NS_SHIFT    (1U)
/*! TZ_NS - Non-secure access */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_NS(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_TZ_MASK   (0x10U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_TZ_SHIFT  (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_TZ(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_WHITE_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_LIST(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_CLR_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_SETPOINT_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_SETPOINT_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_AUTHEN_CLR */
#define CCM_CLOCK_ROOT_AUTHEN_CLR_COUNT          (79U)

/*! @name CLOCK_ROOT_AUTHEN_TOG - Clock root access control */
/*! @{ */

#define CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_USER_MASK   (0x1U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_USER_SHIFT  (0U)
/*! TZ_USER - User access */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_USER(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_NS_MASK     (0x2U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_NS_SHIFT    (1U)
/*! TZ_NS - Non-secure access */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_NS(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_TZ_MASK   (0x10U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_TZ_SHIFT  (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_TZ(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_WHITE_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_LIST(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TOG_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_SETPOINT_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_SETPOINT_MODE_MASK)

#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_CLOCK_ROOT_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_AUTHEN_TOG */
#define CCM_CLOCK_ROOT_AUTHEN_TOG_COUNT          (79U)

/*! @name CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT - Setpoint setting */
/*! @{ */

#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_DIV_MASK (0xFFU)
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_DIV_SHIFT (0U)
/*! DIV - Clock divider */
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_DIV(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_DIV_SHIFT)) & CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_DIV_MASK)

#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_MUX_MASK (0x700U)
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_MUX_SHIFT (8U)
/*! MUX - Clock multiplexer */
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_MUX(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_MUX_SHIFT)) & CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_MUX_MASK)

#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_OFF_MASK (0x1000000U)
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_OFF_SHIFT (24U)
/*! OFF - OFF
 *  0b0..ON
 *  0b1..OFF
 */
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_OFF(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_OFF_SHIFT)) & CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_OFF_MASK)

#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_GRADE_MASK (0xF0000000U)
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_GRADE_SHIFT (28U)
/*! GRADE - Grade */
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_GRADE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_GRADE_SHIFT)) & CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_GRADE_MASK)
/*! @} */

/* The count of CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT */
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_COUNT (79U)

/* The count of CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT */
#define CCM_CLOCK_ROOT_CLOCK_ROOT_SETPOINT_SETPOINT_COUNT2 (16U)

/*! @name CLOCK_GROUP_CONTROL - Clock group control */
/*! @{ */

#define CCM_CLOCK_GROUP_CONTROL_DIV0_MASK        (0xFU)
#define CCM_CLOCK_GROUP_CONTROL_DIV0_SHIFT       (0U)
/*! DIV0 - Clock divider0 */
#define CCM_CLOCK_GROUP_CONTROL_DIV0(x)          (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_DIV0_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_DIV0_MASK)

#define CCM_CLOCK_GROUP_CONTROL_RSTDIV_MASK      (0xFF0000U)
#define CCM_CLOCK_GROUP_CONTROL_RSTDIV_SHIFT     (16U)
/*! RSTDIV - Clock group global restart count */
#define CCM_CLOCK_GROUP_CONTROL_RSTDIV(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_RSTDIV_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_RSTDIV_MASK)

#define CCM_CLOCK_GROUP_CONTROL_OFF_MASK         (0x1000000U)
#define CCM_CLOCK_GROUP_CONTROL_OFF_SHIFT        (24U)
/*! OFF - OFF
 *  0b0..Clock is running
 *  0b1..Turn off clock
 */
#define CCM_CLOCK_GROUP_CONTROL_OFF(x)           (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_OFF_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_CONTROL */
#define CCM_CLOCK_GROUP_CONTROL_COUNT            (2U)

/*! @name CLOCK_GROUP_CONTROL_SET - Clock group control */
/*! @{ */

#define CCM_CLOCK_GROUP_CONTROL_SET_DIV0_MASK    (0xFU)
#define CCM_CLOCK_GROUP_CONTROL_SET_DIV0_SHIFT   (0U)
/*! DIV0 - Clock divider0 */
#define CCM_CLOCK_GROUP_CONTROL_SET_DIV0(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_SET_DIV0_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_SET_DIV0_MASK)

#define CCM_CLOCK_GROUP_CONTROL_SET_RSTDIV_MASK  (0xFF0000U)
#define CCM_CLOCK_GROUP_CONTROL_SET_RSTDIV_SHIFT (16U)
/*! RSTDIV - Clock group global restart count */
#define CCM_CLOCK_GROUP_CONTROL_SET_RSTDIV(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_SET_RSTDIV_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_SET_RSTDIV_MASK)

#define CCM_CLOCK_GROUP_CONTROL_SET_OFF_MASK     (0x1000000U)
#define CCM_CLOCK_GROUP_CONTROL_SET_OFF_SHIFT    (24U)
/*! OFF - OFF */
#define CCM_CLOCK_GROUP_CONTROL_SET_OFF(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_SET_OFF_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_SET_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_CONTROL_SET */
#define CCM_CLOCK_GROUP_CONTROL_SET_COUNT        (2U)

/*! @name CLOCK_GROUP_CONTROL_CLR - Clock group control */
/*! @{ */

#define CCM_CLOCK_GROUP_CONTROL_CLR_DIV0_MASK    (0xFU)
#define CCM_CLOCK_GROUP_CONTROL_CLR_DIV0_SHIFT   (0U)
/*! DIV0 - Clock divider0 */
#define CCM_CLOCK_GROUP_CONTROL_CLR_DIV0(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_CLR_DIV0_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_CLR_DIV0_MASK)

#define CCM_CLOCK_GROUP_CONTROL_CLR_RSTDIV_MASK  (0xFF0000U)
#define CCM_CLOCK_GROUP_CONTROL_CLR_RSTDIV_SHIFT (16U)
/*! RSTDIV - Clock group global restart count */
#define CCM_CLOCK_GROUP_CONTROL_CLR_RSTDIV(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_CLR_RSTDIV_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_CLR_RSTDIV_MASK)

#define CCM_CLOCK_GROUP_CONTROL_CLR_OFF_MASK     (0x1000000U)
#define CCM_CLOCK_GROUP_CONTROL_CLR_OFF_SHIFT    (24U)
/*! OFF - OFF */
#define CCM_CLOCK_GROUP_CONTROL_CLR_OFF(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_CLR_OFF_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_CLR_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_CONTROL_CLR */
#define CCM_CLOCK_GROUP_CONTROL_CLR_COUNT        (2U)

/*! @name CLOCK_GROUP_CONTROL_TOG - Clock group control */
/*! @{ */

#define CCM_CLOCK_GROUP_CONTROL_TOG_DIV0_MASK    (0xFU)
#define CCM_CLOCK_GROUP_CONTROL_TOG_DIV0_SHIFT   (0U)
/*! DIV0 - Clock divider0 */
#define CCM_CLOCK_GROUP_CONTROL_TOG_DIV0(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_TOG_DIV0_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_TOG_DIV0_MASK)

#define CCM_CLOCK_GROUP_CONTROL_TOG_RSTDIV_MASK  (0xFF0000U)
#define CCM_CLOCK_GROUP_CONTROL_TOG_RSTDIV_SHIFT (16U)
/*! RSTDIV - Clock group global restart count */
#define CCM_CLOCK_GROUP_CONTROL_TOG_RSTDIV(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_TOG_RSTDIV_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_TOG_RSTDIV_MASK)

#define CCM_CLOCK_GROUP_CONTROL_TOG_OFF_MASK     (0x1000000U)
#define CCM_CLOCK_GROUP_CONTROL_TOG_OFF_SHIFT    (24U)
/*! OFF - OFF */
#define CCM_CLOCK_GROUP_CONTROL_TOG_OFF(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONTROL_TOG_OFF_SHIFT)) & CCM_CLOCK_GROUP_CONTROL_TOG_OFF_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_CONTROL_TOG */
#define CCM_CLOCK_GROUP_CONTROL_TOG_COUNT        (2U)

/*! @name CLOCK_GROUP_STATUS0 - Clock group working status */
/*! @{ */

#define CCM_CLOCK_GROUP_STATUS0_DIV0_MASK        (0xFU)
#define CCM_CLOCK_GROUP_STATUS0_DIV0_SHIFT       (0U)
/*! DIV0 - Clock divider */
#define CCM_CLOCK_GROUP_STATUS0_DIV0(x)          (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_DIV0_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_DIV0_MASK)

#define CCM_CLOCK_GROUP_STATUS0_RSTDIV_MASK      (0xFF0000U)
#define CCM_CLOCK_GROUP_STATUS0_RSTDIV_SHIFT     (16U)
/*! RSTDIV - Clock divider */
#define CCM_CLOCK_GROUP_STATUS0_RSTDIV(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_RSTDIV_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_RSTDIV_MASK)

#define CCM_CLOCK_GROUP_STATUS0_OFF_MASK         (0x1000000U)
#define CCM_CLOCK_GROUP_STATUS0_OFF_SHIFT        (24U)
/*! OFF - OFF
 *  0b0..Clock is running.
 *  0b1..Turn off clock.
 */
#define CCM_CLOCK_GROUP_STATUS0_OFF(x)           (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_OFF_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_OFF_MASK)

#define CCM_CLOCK_GROUP_STATUS0_POWERDOWN_MASK   (0x8000000U)
#define CCM_CLOCK_GROUP_STATUS0_POWERDOWN_SHIFT  (27U)
/*! POWERDOWN - Current clock root POWERDOWN setting
 *  0b0..Clock root is running
 *  0b1..Clock root is Powered Down
 */
#define CCM_CLOCK_GROUP_STATUS0_POWERDOWN(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_POWERDOWN_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_POWERDOWN_MASK)

#define CCM_CLOCK_GROUP_STATUS0_SLICE_BUSY_MASK  (0x10000000U)
#define CCM_CLOCK_GROUP_STATUS0_SLICE_BUSY_SHIFT (28U)
/*! SLICE_BUSY - Internal updating in generation logic
 *  0b0..Clock generation logic is not busy
 *  0b1..Clock generation logic is applying the new setting
 */
#define CCM_CLOCK_GROUP_STATUS0_SLICE_BUSY(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_SLICE_BUSY_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_SLICE_BUSY_MASK)

#define CCM_CLOCK_GROUP_STATUS0_UPDATE_FORWARD_MASK (0x20000000U)
#define CCM_CLOCK_GROUP_STATUS0_UPDATE_FORWARD_SHIFT (29U)
/*! UPDATE_FORWARD - Internal status synchronization to clock generation logic
 *  0b0..Synchronization not in process
 *  0b1..Synchronization in process
 */
#define CCM_CLOCK_GROUP_STATUS0_UPDATE_FORWARD(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_UPDATE_FORWARD_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_UPDATE_FORWARD_MASK)

#define CCM_CLOCK_GROUP_STATUS0_UPDATE_REVERSE_MASK (0x40000000U)
#define CCM_CLOCK_GROUP_STATUS0_UPDATE_REVERSE_SHIFT (30U)
/*! UPDATE_REVERSE - Internal status synchronization from clock generation logic
 *  0b0..Synchronization not in process
 *  0b1..Synchronization in process
 */
#define CCM_CLOCK_GROUP_STATUS0_UPDATE_REVERSE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_UPDATE_REVERSE_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_UPDATE_REVERSE_MASK)

#define CCM_CLOCK_GROUP_STATUS0_CHANGING_MASK    (0x80000000U)
#define CCM_CLOCK_GROUP_STATUS0_CHANGING_SHIFT   (31U)
/*! CHANGING - Internal updating in clock group
 *  0b0..Clock root is not updating currently
 *  0b1..Clock root logic is updating currently
 */
#define CCM_CLOCK_GROUP_STATUS0_CHANGING(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS0_CHANGING_SHIFT)) & CCM_CLOCK_GROUP_STATUS0_CHANGING_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_STATUS0 */
#define CCM_CLOCK_GROUP_STATUS0_COUNT            (2U)

/*! @name CLOCK_GROUP_STATUS1 - Clock group low power/extend status */
/*! @{ */

#define CCM_CLOCK_GROUP_STATUS1_TARGET_SETPOINT_MASK (0xF0000U)
#define CCM_CLOCK_GROUP_STATUS1_TARGET_SETPOINT_SHIFT (16U)
/*! TARGET_SETPOINT - Next Setpoint to change to */
#define CCM_CLOCK_GROUP_STATUS1_TARGET_SETPOINT(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS1_TARGET_SETPOINT_SHIFT)) & CCM_CLOCK_GROUP_STATUS1_TARGET_SETPOINT_MASK)

#define CCM_CLOCK_GROUP_STATUS1_CURRENT_SETPOINT_MASK (0xF00000U)
#define CCM_CLOCK_GROUP_STATUS1_CURRENT_SETPOINT_SHIFT (20U)
/*! CURRENT_SETPOINT - Current Setpoint */
#define CCM_CLOCK_GROUP_STATUS1_CURRENT_SETPOINT(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS1_CURRENT_SETPOINT_SHIFT)) & CCM_CLOCK_GROUP_STATUS1_CURRENT_SETPOINT_MASK)

#define CCM_CLOCK_GROUP_STATUS1_DOWN_REQUEST_MASK (0x1000000U)
#define CCM_CLOCK_GROUP_STATUS1_DOWN_REQUEST_SHIFT (24U)
/*! DOWN_REQUEST - Clock frequency decrease request
 *  0b0..No handshake signal is not requested
 *  0b1..Handshake signal with GPC status indicating frequency decrease is requested
 */
#define CCM_CLOCK_GROUP_STATUS1_DOWN_REQUEST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS1_DOWN_REQUEST_SHIFT)) & CCM_CLOCK_GROUP_STATUS1_DOWN_REQUEST_MASK)

#define CCM_CLOCK_GROUP_STATUS1_DOWN_DONE_MASK   (0x2000000U)
#define CCM_CLOCK_GROUP_STATUS1_DOWN_DONE_SHIFT  (25U)
/*! DOWN_DONE - Clock frequency decrease complete
 *  0b0..Handshake signal with GPC status indicating frequency decrease is not complete
 *  0b1..Handshake signal with GPC status indicating frequency decrease is complete
 */
#define CCM_CLOCK_GROUP_STATUS1_DOWN_DONE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS1_DOWN_DONE_SHIFT)) & CCM_CLOCK_GROUP_STATUS1_DOWN_DONE_MASK)

#define CCM_CLOCK_GROUP_STATUS1_UP_REQUEST_MASK  (0x4000000U)
#define CCM_CLOCK_GROUP_STATUS1_UP_REQUEST_SHIFT (26U)
/*! UP_REQUEST - Clock frequency increase request
 *  0b0..No handshake signal is not requested
 *  0b1..Handshake signal with GPC status indicating frequency increase is requested
 */
#define CCM_CLOCK_GROUP_STATUS1_UP_REQUEST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS1_UP_REQUEST_SHIFT)) & CCM_CLOCK_GROUP_STATUS1_UP_REQUEST_MASK)

#define CCM_CLOCK_GROUP_STATUS1_UP_DONE_MASK     (0x8000000U)
#define CCM_CLOCK_GROUP_STATUS1_UP_DONE_SHIFT    (27U)
/*! UP_DONE - Clock frequency increase complete
 *  0b0..Handshake signal with GPC status indicating frequency increase is not complete
 *  0b1..Handshake signal with GPC status indicating frequency increase is complete
 */
#define CCM_CLOCK_GROUP_STATUS1_UP_DONE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_STATUS1_UP_DONE_SHIFT)) & CCM_CLOCK_GROUP_STATUS1_UP_DONE_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_STATUS1 */
#define CCM_CLOCK_GROUP_STATUS1_COUNT            (2U)

/*! @name CLOCK_GROUP_CONFIG - Clock group configuration */
/*! @{ */

#define CCM_CLOCK_GROUP_CONFIG_SETPOINT_PRESENT_MASK (0x10U)
#define CCM_CLOCK_GROUP_CONFIG_SETPOINT_PRESENT_SHIFT (4U)
/*! SETPOINT_PRESENT - Setpoint present
 *  0b0..Setpoint is not implemented.
 *  0b1..Setpoint is implemented.
 */
#define CCM_CLOCK_GROUP_CONFIG_SETPOINT_PRESENT(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CONFIG_SETPOINT_PRESENT_SHIFT)) & CCM_CLOCK_GROUP_CONFIG_SETPOINT_PRESENT_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_CONFIG */
#define CCM_CLOCK_GROUP_CONFIG_COUNT             (2U)

/*! @name CLOCK_GROUP_AUTHEN - Clock group access control */
/*! @{ */

#define CCM_CLOCK_GROUP_AUTHEN_TZ_USER_MASK      (0x1U)
#define CCM_CLOCK_GROUP_AUTHEN_TZ_USER_SHIFT     (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_CLOCK_GROUP_AUTHEN_TZ_USER(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TZ_USER_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TZ_USER_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TZ_NS_MASK        (0x2U)
#define CCM_CLOCK_GROUP_AUTHEN_TZ_NS_SHIFT       (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_CLOCK_GROUP_AUTHEN_TZ_NS(x)          (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TZ_NS_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TZ_NS_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_LOCK_TZ_MASK      (0x10U)
#define CCM_CLOCK_GROUP_AUTHEN_LOCK_TZ_SHIFT     (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_CLOCK_GROUP_AUTHEN_LOCK_TZ(x)        (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_LOCK_TZ_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_LOCK_TZ_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_WHITE_LIST_MASK   (0xF00U)
#define CCM_CLOCK_GROUP_AUTHEN_WHITE_LIST_SHIFT  (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_CLOCK_GROUP_AUTHEN_WHITE_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_WHITE_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_WHITE_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_LOCK_LIST_MASK    (0x1000U)
#define CCM_CLOCK_GROUP_AUTHEN_LOCK_LIST_SHIFT   (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_CLOCK_GROUP_AUTHEN_LOCK_LIST(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_LOCK_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_LOCK_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_DOMAIN_MODE_MASK  (0x10000U)
#define CCM_CLOCK_GROUP_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain
 *  0b0..Clock does not work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_CLOCK_GROUP_AUTHEN_DOMAIN_MODE(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_GROUP_AUTHEN_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint */
#define CCM_CLOCK_GROUP_AUTHEN_SETPOINT_MODE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SETPOINT_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_LOCK_MODE_MASK    (0x100000U)
#define CCM_CLOCK_GROUP_AUTHEN_LOCK_MODE_SHIFT   (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_CLOCK_GROUP_AUTHEN_LOCK_MODE(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_LOCK_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_AUTHEN */
#define CCM_CLOCK_GROUP_AUTHEN_COUNT             (2U)

/*! @name CLOCK_GROUP_AUTHEN_SET - Clock group access control */
/*! @{ */

#define CCM_CLOCK_GROUP_AUTHEN_SET_TZ_USER_MASK  (0x1U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_CLOCK_GROUP_AUTHEN_SET_TZ_USER(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_TZ_USER_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SET_TZ_NS_MASK    (0x2U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_TZ_NS_SHIFT   (1U)
/*! TZ_NS - Non-secure access */
#define CCM_CLOCK_GROUP_AUTHEN_SET_TZ_NS(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_TZ_NS_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_TZ_MASK  (0x10U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_TZ(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_CLOCK_GROUP_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_CLOCK_GROUP_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SET_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint */
#define CCM_CLOCK_GROUP_AUTHEN_SET_SETPOINT_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_SETPOINT_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_MODE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_AUTHEN_SET */
#define CCM_CLOCK_GROUP_AUTHEN_SET_COUNT         (2U)

/*! @name CLOCK_GROUP_AUTHEN_CLR - Clock group access control */
/*! @{ */

#define CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_USER_MASK  (0x1U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_USER(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_NS_MASK    (0x2U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_NS_SHIFT   (1U)
/*! TZ_NS - Non-secure access */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_NS(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_TZ_MASK  (0x10U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_TZ(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_CLR_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_SETPOINT_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_SETPOINT_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_MODE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_AUTHEN_CLR */
#define CCM_CLOCK_GROUP_AUTHEN_CLR_COUNT         (2U)

/*! @name CLOCK_GROUP_AUTHEN_TOG - Clock group access control */
/*! @{ */

#define CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_USER_MASK  (0x1U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_USER(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_NS_MASK    (0x2U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_NS_SHIFT   (1U)
/*! TZ_NS - Non-secure access */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_NS(x)      (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_TZ_MASK  (0x10U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_TZ(x)    (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TOG_SETPOINT_MODE_MASK (0x20000U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_SETPOINT_MODE_SHIFT (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_SETPOINT_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_SETPOINT_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_SETPOINT_MODE_MASK)

#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_MODE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_CLOCK_GROUP_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_AUTHEN_TOG */
#define CCM_CLOCK_GROUP_AUTHEN_TOG_COUNT         (2U)

/*! @name CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT - Setpoint setting */
/*! @{ */

#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_DIV0_MASK (0xFU)
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_DIV0_SHIFT (0U)
/*! DIV0 - Clock divider
 *  0b0000..Direct output.
 *  0b0001..Divide by 2.
 *  0b0010..Divide by 3.
 *  0b0011..Divide by 4.
 *  0b1111..Divide by 16.
 */
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_DIV0(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_DIV0_SHIFT)) & CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_DIV0_MASK)

#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_RSTDIV_MASK (0xFF0000U)
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_RSTDIV_SHIFT (16U)
/*! RSTDIV - Clock group global restart count */
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_RSTDIV(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_RSTDIV_SHIFT)) & CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_RSTDIV_MASK)

#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_OFF_MASK (0x1000000U)
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_OFF_SHIFT (24U)
/*! OFF - OFF
 *  0b0..Clock is running.
 *  0b1..Turn off clock.
 */
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_OFF(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_OFF_SHIFT)) & CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_OFF_MASK)

#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_GRADE_MASK (0xF0000000U)
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_GRADE_SHIFT (28U)
/*! GRADE - Grade */
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_GRADE(x) (((uint32_t)(((uint32_t)(x)) << CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_GRADE_SHIFT)) & CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_GRADE_MASK)
/*! @} */

/* The count of CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT */
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_COUNT (2U)

/* The count of CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT */
#define CCM_CLOCK_GROUP_CLOCK_GROUP_SETPOINT_SETPOINT_COUNT2 (16U)

/*! @name GPR_SHARED - General Purpose Register */
/*! @{ */

#define CCM_GPR_SHARED_GPR_MASK                  (0xFFFFFFFFU)
#define CCM_GPR_SHARED_GPR_SHIFT                 (0U)
/*! GPR - GP register */
#define CCM_GPR_SHARED_GPR(x)                    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_GPR_SHIFT)) & CCM_GPR_SHARED_GPR_MASK)
/*! @} */

/*! @name GPR_SHARED_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_SHARED_SET_GPR_MASK              (0xFFFFFFFFU)
#define CCM_GPR_SHARED_SET_GPR_SHIFT             (0U)
/*! GPR - GP register */
#define CCM_GPR_SHARED_SET_GPR(x)                (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_SET_GPR_SHIFT)) & CCM_GPR_SHARED_SET_GPR_MASK)
/*! @} */

/* The count of CCM_GPR_SHARED_SET */
#define CCM_GPR_SHARED_SET_COUNT                 (8U)

/*! @name GPR_SHARED_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_SHARED_CLR_GPR_MASK              (0xFFFFFFFFU)
#define CCM_GPR_SHARED_CLR_GPR_SHIFT             (0U)
/*! GPR - GP register */
#define CCM_GPR_SHARED_CLR_GPR(x)                (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_CLR_GPR_SHIFT)) & CCM_GPR_SHARED_CLR_GPR_MASK)
/*! @} */

/* The count of CCM_GPR_SHARED_CLR */
#define CCM_GPR_SHARED_CLR_COUNT                 (8U)

/*! @name GPR_SHARED_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_SHARED_TOG_GPR_MASK              (0xFFFFFFFFU)
#define CCM_GPR_SHARED_TOG_GPR_SHIFT             (0U)
/*! GPR - GP register */
#define CCM_GPR_SHARED_TOG_GPR(x)                (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_TOG_GPR_SHIFT)) & CCM_GPR_SHARED_TOG_GPR_MASK)
/*! @} */

/* The count of CCM_GPR_SHARED_TOG */
#define CCM_GPR_SHARED_TOG_COUNT                 (8U)

/*! @name GPR_SHARED_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_SHARED_AUTHEN_TZ_USER_MASK       (0x1U)
#define CCM_GPR_SHARED_AUTHEN_TZ_USER_SHIFT      (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_SHARED_AUTHEN_TZ_USER(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_SHARED_AUTHEN_TZ_NS_MASK         (0x2U)
#define CCM_GPR_SHARED_AUTHEN_TZ_NS_SHIFT        (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_SHARED_AUTHEN_TZ_NS(x)           (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_SHARED_AUTHEN_LOCK_TZ_MASK       (0x10U)
#define CCM_GPR_SHARED_AUTHEN_LOCK_TZ_SHIFT      (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_SHARED_AUTHEN_LOCK_TZ(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_SHARED_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_SHARED_AUTHEN_WHITE_LIST_MASK    (0xF00U)
#define CCM_GPR_SHARED_AUTHEN_WHITE_LIST_SHIFT   (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_SHARED_AUTHEN_WHITE_LIST(x)      (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_LOCK_LIST_MASK     (0x1000U)
#define CCM_GPR_SHARED_AUTHEN_LOCK_LIST_SHIFT    (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_SHARED_AUTHEN_LOCK_LIST(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_DOMAIN_MODE_MASK   (0x10000U)
#define CCM_GPR_SHARED_AUTHEN_DOMAIN_MODE_SHIFT  (16U)
/*! DOMAIN_MODE - Low power and access control by domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_SHARED_AUTHEN_DOMAIN_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_SHARED_AUTHEN_LOCK_MODE_MASK     (0x100000U)
#define CCM_GPR_SHARED_AUTHEN_LOCK_MODE_SHIFT    (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_SHARED_AUTHEN_LOCK_MODE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_GPR_SHARED_AUTHEN */
#define CCM_GPR_SHARED_AUTHEN_COUNT              (8U)

/*! @name GPR_SHARED_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_SHARED_AUTHEN_SET_TZ_USER_MASK   (0x1U)
#define CCM_GPR_SHARED_AUTHEN_SET_TZ_USER_SHIFT  (0U)
/*! TZ_USER - User access */
#define CCM_GPR_SHARED_AUTHEN_SET_TZ_USER(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_SHARED_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_SHARED_AUTHEN_SET_TZ_NS_MASK     (0x2U)
#define CCM_GPR_SHARED_AUTHEN_SET_TZ_NS_SHIFT    (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_SHARED_AUTHEN_SET_TZ_NS(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_SHARED_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_TZ_MASK   (0x10U)
#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_TZ_SHIFT  (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_TZ(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_SHARED_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_SHARED_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_SHARED_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_SHARED_AUTHEN_SET_WHITE_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_LIST(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_SHARED_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_GPR_SHARED_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_SHARED_AUTHEN_SET_LOCK_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_GPR_SHARED_AUTHEN_SET */
#define CCM_GPR_SHARED_AUTHEN_SET_COUNT          (8U)

/*! @name GPR_SHARED_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_SHARED_AUTHEN_CLR_TZ_USER_MASK   (0x1U)
#define CCM_GPR_SHARED_AUTHEN_CLR_TZ_USER_SHIFT  (0U)
/*! TZ_USER - User access */
#define CCM_GPR_SHARED_AUTHEN_CLR_TZ_USER(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_SHARED_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_SHARED_AUTHEN_CLR_TZ_NS_MASK     (0x2U)
#define CCM_GPR_SHARED_AUTHEN_CLR_TZ_NS_SHIFT    (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_SHARED_AUTHEN_CLR_TZ_NS(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_SHARED_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_TZ_MASK   (0x10U)
#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_TZ_SHIFT  (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_TZ(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_SHARED_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_SHARED_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_SHARED_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_SHARED_AUTHEN_CLR_WHITE_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_LIST(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_SHARED_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_GPR_SHARED_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_SHARED_AUTHEN_CLR_LOCK_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_GPR_SHARED_AUTHEN_CLR */
#define CCM_GPR_SHARED_AUTHEN_CLR_COUNT          (8U)

/*! @name GPR_SHARED_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_SHARED_AUTHEN_TOG_TZ_USER_MASK   (0x1U)
#define CCM_GPR_SHARED_AUTHEN_TOG_TZ_USER_SHIFT  (0U)
/*! TZ_USER - User access */
#define CCM_GPR_SHARED_AUTHEN_TOG_TZ_USER(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_SHARED_AUTHEN_TOG_TZ_NS_MASK     (0x2U)
#define CCM_GPR_SHARED_AUTHEN_TOG_TZ_NS_SHIFT    (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_SHARED_AUTHEN_TOG_TZ_NS(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_TZ_MASK   (0x10U)
#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_TZ_SHIFT  (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_TZ(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_SHARED_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_SHARED_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_SHARED_AUTHEN_TOG_WHITE_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_LIST(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_SHARED_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_SHARED_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_GPR_SHARED_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_SHARED_AUTHEN_TOG_LOCK_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_SHARED_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_SHARED_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_GPR_SHARED_AUTHEN_TOG */
#define CCM_GPR_SHARED_AUTHEN_TOG_COUNT          (8U)

/*! @name GPR_PRIVATE1 - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE1_GPR_MASK                (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE1_GPR_SHIFT               (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE1_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_GPR_SHIFT)) & CCM_GPR_PRIVATE1_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE1_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE1_SET_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE1_SET_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE1_SET_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_SET_GPR_SHIFT)) & CCM_GPR_PRIVATE1_SET_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE1_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE1_CLR_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE1_CLR_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE1_CLR_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_CLR_GPR_SHIFT)) & CCM_GPR_PRIVATE1_CLR_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE1_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE1_TOG_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE1_TOG_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE1_TOG_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_TOG_GPR_SHIFT)) & CCM_GPR_PRIVATE1_TOG_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE1_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE1_AUTHEN_TZ_USER_MASK     (0x1U)
#define CCM_GPR_PRIVATE1_AUTHEN_TZ_USER_SHIFT    (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_PRIVATE1_AUTHEN_TZ_USER(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_TZ_NS_MASK       (0x2U)
#define CCM_GPR_PRIVATE1_AUTHEN_TZ_NS_SHIFT      (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_PRIVATE1_AUTHEN_TZ_NS(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_TZ_MASK     (0x10U)
#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_TZ_SHIFT    (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_TZ(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_WHITE_LIST_MASK  (0xF00U)
#define CCM_GPR_PRIVATE1_AUTHEN_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_PRIVATE1_AUTHEN_WHITE_LIST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_LIST_MASK   (0x1000U)
#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_LIST_SHIFT  (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE1_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_PRIVATE1_AUTHEN_DOMAIN_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_MODE_MASK   (0x100000U)
#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_MODE_SHIFT  (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_PRIVATE1_AUTHEN_LOCK_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE1_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE1_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE1_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE1_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE1_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE1_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE1_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE1_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE2 - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE2_GPR_MASK                (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE2_GPR_SHIFT               (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE2_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_GPR_SHIFT)) & CCM_GPR_PRIVATE2_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE2_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE2_SET_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE2_SET_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE2_SET_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_SET_GPR_SHIFT)) & CCM_GPR_PRIVATE2_SET_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE2_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE2_CLR_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE2_CLR_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE2_CLR_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_CLR_GPR_SHIFT)) & CCM_GPR_PRIVATE2_CLR_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE2_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE2_TOG_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE2_TOG_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE2_TOG_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_TOG_GPR_SHIFT)) & CCM_GPR_PRIVATE2_TOG_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE2_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE2_AUTHEN_TZ_USER_MASK     (0x1U)
#define CCM_GPR_PRIVATE2_AUTHEN_TZ_USER_SHIFT    (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_PRIVATE2_AUTHEN_TZ_USER(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_TZ_NS_MASK       (0x2U)
#define CCM_GPR_PRIVATE2_AUTHEN_TZ_NS_SHIFT      (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_PRIVATE2_AUTHEN_TZ_NS(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_TZ_MASK     (0x10U)
#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_TZ_SHIFT    (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_TZ(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_WHITE_LIST_MASK  (0xF00U)
#define CCM_GPR_PRIVATE2_AUTHEN_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_PRIVATE2_AUTHEN_WHITE_LIST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_LIST_MASK   (0x1000U)
#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_LIST_SHIFT  (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE2_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_PRIVATE2_AUTHEN_DOMAIN_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_MODE_MASK   (0x100000U)
#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_MODE_SHIFT  (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_PRIVATE2_AUTHEN_LOCK_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE2_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE2_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE2_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE2_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE2_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE2_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE2_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE2_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE3 - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE3_GPR_MASK                (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE3_GPR_SHIFT               (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE3_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_GPR_SHIFT)) & CCM_GPR_PRIVATE3_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE3_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE3_SET_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE3_SET_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE3_SET_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_SET_GPR_SHIFT)) & CCM_GPR_PRIVATE3_SET_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE3_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE3_CLR_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE3_CLR_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE3_CLR_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_CLR_GPR_SHIFT)) & CCM_GPR_PRIVATE3_CLR_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE3_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE3_TOG_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE3_TOG_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE3_TOG_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_TOG_GPR_SHIFT)) & CCM_GPR_PRIVATE3_TOG_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE3_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE3_AUTHEN_TZ_USER_MASK     (0x1U)
#define CCM_GPR_PRIVATE3_AUTHEN_TZ_USER_SHIFT    (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_PRIVATE3_AUTHEN_TZ_USER(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_TZ_NS_MASK       (0x2U)
#define CCM_GPR_PRIVATE3_AUTHEN_TZ_NS_SHIFT      (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_PRIVATE3_AUTHEN_TZ_NS(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_TZ_MASK     (0x10U)
#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_TZ_SHIFT    (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_TZ(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_WHITE_LIST_MASK  (0xF00U)
#define CCM_GPR_PRIVATE3_AUTHEN_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_PRIVATE3_AUTHEN_WHITE_LIST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_LIST_MASK   (0x1000U)
#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_LIST_SHIFT  (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE3_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_PRIVATE3_AUTHEN_DOMAIN_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_MODE_MASK   (0x100000U)
#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_MODE_SHIFT  (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_PRIVATE3_AUTHEN_LOCK_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE3_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE3_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE3_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE3_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE3_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE3_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE3_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE3_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE4 - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE4_GPR_MASK                (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE4_GPR_SHIFT               (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE4_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_GPR_SHIFT)) & CCM_GPR_PRIVATE4_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE4_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE4_SET_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE4_SET_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE4_SET_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_SET_GPR_SHIFT)) & CCM_GPR_PRIVATE4_SET_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE4_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE4_CLR_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE4_CLR_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE4_CLR_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_CLR_GPR_SHIFT)) & CCM_GPR_PRIVATE4_CLR_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE4_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE4_TOG_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE4_TOG_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE4_TOG_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_TOG_GPR_SHIFT)) & CCM_GPR_PRIVATE4_TOG_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE4_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE4_AUTHEN_TZ_USER_MASK     (0x1U)
#define CCM_GPR_PRIVATE4_AUTHEN_TZ_USER_SHIFT    (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_PRIVATE4_AUTHEN_TZ_USER(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_TZ_NS_MASK       (0x2U)
#define CCM_GPR_PRIVATE4_AUTHEN_TZ_NS_SHIFT      (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_PRIVATE4_AUTHEN_TZ_NS(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_TZ_MASK     (0x10U)
#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_TZ_SHIFT    (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_TZ(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_WHITE_LIST_MASK  (0xF00U)
#define CCM_GPR_PRIVATE4_AUTHEN_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_PRIVATE4_AUTHEN_WHITE_LIST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_LIST_MASK   (0x1000U)
#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_LIST_SHIFT  (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE4_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_PRIVATE4_AUTHEN_DOMAIN_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_MODE_MASK   (0x100000U)
#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_MODE_SHIFT  (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_PRIVATE4_AUTHEN_LOCK_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE4_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE4_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE4_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE4_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE4_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE4_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE4_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE4_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE5 - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE5_GPR_MASK                (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE5_GPR_SHIFT               (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE5_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_GPR_SHIFT)) & CCM_GPR_PRIVATE5_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE5_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE5_SET_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE5_SET_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE5_SET_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_SET_GPR_SHIFT)) & CCM_GPR_PRIVATE5_SET_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE5_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE5_CLR_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE5_CLR_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE5_CLR_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_CLR_GPR_SHIFT)) & CCM_GPR_PRIVATE5_CLR_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE5_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE5_TOG_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE5_TOG_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE5_TOG_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_TOG_GPR_SHIFT)) & CCM_GPR_PRIVATE5_TOG_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE5_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE5_AUTHEN_TZ_USER_MASK     (0x1U)
#define CCM_GPR_PRIVATE5_AUTHEN_TZ_USER_SHIFT    (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_PRIVATE5_AUTHEN_TZ_USER(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_TZ_NS_MASK       (0x2U)
#define CCM_GPR_PRIVATE5_AUTHEN_TZ_NS_SHIFT      (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_PRIVATE5_AUTHEN_TZ_NS(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_TZ_MASK     (0x10U)
#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_TZ_SHIFT    (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_TZ(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_WHITE_LIST_MASK  (0xF00U)
#define CCM_GPR_PRIVATE5_AUTHEN_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_PRIVATE5_AUTHEN_WHITE_LIST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_LIST_MASK   (0x1000U)
#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_LIST_SHIFT  (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE5_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_PRIVATE5_AUTHEN_DOMAIN_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_MODE_MASK   (0x100000U)
#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_MODE_SHIFT  (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_PRIVATE5_AUTHEN_LOCK_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE5_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE5_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE5_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE5_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE5_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE5_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE5_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE5_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE6 - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE6_GPR_MASK                (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE6_GPR_SHIFT               (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE6_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_GPR_SHIFT)) & CCM_GPR_PRIVATE6_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE6_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE6_SET_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE6_SET_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE6_SET_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_SET_GPR_SHIFT)) & CCM_GPR_PRIVATE6_SET_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE6_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE6_CLR_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE6_CLR_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE6_CLR_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_CLR_GPR_SHIFT)) & CCM_GPR_PRIVATE6_CLR_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE6_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE6_TOG_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE6_TOG_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE6_TOG_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_TOG_GPR_SHIFT)) & CCM_GPR_PRIVATE6_TOG_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE6_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE6_AUTHEN_TZ_USER_MASK     (0x1U)
#define CCM_GPR_PRIVATE6_AUTHEN_TZ_USER_SHIFT    (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_PRIVATE6_AUTHEN_TZ_USER(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_TZ_NS_MASK       (0x2U)
#define CCM_GPR_PRIVATE6_AUTHEN_TZ_NS_SHIFT      (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_PRIVATE6_AUTHEN_TZ_NS(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_TZ_MASK     (0x10U)
#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_TZ_SHIFT    (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_TZ(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_WHITE_LIST_MASK  (0xF00U)
#define CCM_GPR_PRIVATE6_AUTHEN_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_PRIVATE6_AUTHEN_WHITE_LIST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_LIST_MASK   (0x1000U)
#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_LIST_SHIFT  (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE6_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_PRIVATE6_AUTHEN_DOMAIN_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_MODE_MASK   (0x100000U)
#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_MODE_SHIFT  (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_PRIVATE6_AUTHEN_LOCK_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE6_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE6_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE6_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE6_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE6_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE6_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE6_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE6_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE7 - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE7_GPR_MASK                (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE7_GPR_SHIFT               (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE7_GPR(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_GPR_SHIFT)) & CCM_GPR_PRIVATE7_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE7_SET - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE7_SET_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE7_SET_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE7_SET_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_SET_GPR_SHIFT)) & CCM_GPR_PRIVATE7_SET_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE7_CLR - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE7_CLR_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE7_CLR_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE7_CLR_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_CLR_GPR_SHIFT)) & CCM_GPR_PRIVATE7_CLR_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE7_TOG - General Purpose Register */
/*! @{ */

#define CCM_GPR_PRIVATE7_TOG_GPR_MASK            (0xFFFFFFFFU)
#define CCM_GPR_PRIVATE7_TOG_GPR_SHIFT           (0U)
/*! GPR - GP register */
#define CCM_GPR_PRIVATE7_TOG_GPR(x)              (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_TOG_GPR_SHIFT)) & CCM_GPR_PRIVATE7_TOG_GPR_MASK)
/*! @} */

/*! @name GPR_PRIVATE7_AUTHEN - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE7_AUTHEN_TZ_USER_MASK     (0x1U)
#define CCM_GPR_PRIVATE7_AUTHEN_TZ_USER_SHIFT    (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_GPR_PRIVATE7_AUTHEN_TZ_USER(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TZ_USER_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_TZ_NS_MASK       (0x2U)
#define CCM_GPR_PRIVATE7_AUTHEN_TZ_NS_SHIFT      (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_GPR_PRIVATE7_AUTHEN_TZ_NS(x)         (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TZ_NS_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_TZ_MASK     (0x10U)
#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_TZ_SHIFT    (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_TZ(x)       (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_WHITE_LIST_MASK  (0xF00U)
#define CCM_GPR_PRIVATE7_AUTHEN_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist
 *  0b0000..This domain is NOT allowed to change clock.
 *  0b0001..This domain is allowed to change clock.
 */
#define CCM_GPR_PRIVATE7_AUTHEN_WHITE_LIST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_LIST_MASK   (0x1000U)
#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_LIST_SHIFT  (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE7_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain
 *  0b0..Clock does NOT work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_GPR_PRIVATE7_AUTHEN_DOMAIN_MODE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_MODE_MASK   (0x100000U)
#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_MODE_SHIFT  (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_GPR_PRIVATE7_AUTHEN_LOCK_MODE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE7_AUTHEN_SET - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_USER_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_SET_TZ_NS_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE7_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE7_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE7_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE7_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE7_AUTHEN_CLR - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/*! @name GPR_PRIVATE7_AUTHEN_TOG - GPR access control */
/*! @{ */

#define CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_USER_MASK (0x1U)
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_USER(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_NS_MASK   (0x2U)
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_NS_SHIFT  (1U)
/*! TZ_NS - Non-secure access */
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_NS(x)     (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_TZ_MASK (0x10U)
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_TZ(x)   (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock Whitelist */
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by Domain */
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_GPR_PRIVATE7_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/*! @name OSCPLL_DIRECT - Clock source direct control */
/*! @{ */

#define CCM_OSCPLL_DIRECT_ON_MASK                (0x1U)
#define CCM_OSCPLL_DIRECT_ON_SHIFT               (0U)
/*! ON - turn on clock source
 *  0b0..OSCPLL is OFF
 *  0b1..OSCPLL is ON
 */
#define CCM_OSCPLL_DIRECT_ON(x)                  (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_DIRECT_ON_SHIFT)) & CCM_OSCPLL_DIRECT_ON_MASK)
/*! @} */

/* The count of CCM_OSCPLL_DIRECT */
#define CCM_OSCPLL_DIRECT_COUNT                  (29U)

/*! @name OSCPLL_DOMAIN - Clock source domain control */
/*! @{ */

#define CCM_OSCPLL_DOMAIN_LEVEL_MASK             (0x7U)
#define CCM_OSCPLL_DOMAIN_LEVEL_SHIFT            (0U)
/*! LEVEL - Current dependence level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_OSCPLL_DOMAIN_LEVEL(x)               (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_DOMAIN_LEVEL_SHIFT)) & CCM_OSCPLL_DOMAIN_LEVEL_MASK)

#define CCM_OSCPLL_DOMAIN_LEVEL0_MASK            (0x70000U)
#define CCM_OSCPLL_DOMAIN_LEVEL0_SHIFT           (16U)
/*! LEVEL0 - Dependence level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_OSCPLL_DOMAIN_LEVEL0(x)              (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_DOMAIN_LEVEL0_SHIFT)) & CCM_OSCPLL_DOMAIN_LEVEL0_MASK)

#define CCM_OSCPLL_DOMAIN_LEVEL1_MASK            (0x700000U)
#define CCM_OSCPLL_DOMAIN_LEVEL1_SHIFT           (20U)
/*! LEVEL1 - Depend level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_OSCPLL_DOMAIN_LEVEL1(x)              (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_DOMAIN_LEVEL1_SHIFT)) & CCM_OSCPLL_DOMAIN_LEVEL1_MASK)

#define CCM_OSCPLL_DOMAIN_LEVEL2_MASK            (0x7000000U)
#define CCM_OSCPLL_DOMAIN_LEVEL2_SHIFT           (24U)
/*! LEVEL2 - Depend level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_OSCPLL_DOMAIN_LEVEL2(x)              (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_DOMAIN_LEVEL2_SHIFT)) & CCM_OSCPLL_DOMAIN_LEVEL2_MASK)

#define CCM_OSCPLL_DOMAIN_LEVEL3_MASK            (0x70000000U)
#define CCM_OSCPLL_DOMAIN_LEVEL3_SHIFT           (28U)
/*! LEVEL3 - Depend level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_OSCPLL_DOMAIN_LEVEL3(x)              (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_DOMAIN_LEVEL3_SHIFT)) & CCM_OSCPLL_DOMAIN_LEVEL3_MASK)
/*! @} */

/* The count of CCM_OSCPLL_DOMAIN */
#define CCM_OSCPLL_DOMAIN_COUNT                  (29U)

/*! @name OSCPLL_SETPOINT - Clock source Setpoint setting */
/*! @{ */

#define CCM_OSCPLL_SETPOINT_SETPOINT_MASK        (0xFFFFU)
#define CCM_OSCPLL_SETPOINT_SETPOINT_SHIFT       (0U)
/*! SETPOINT - Setpoint */
#define CCM_OSCPLL_SETPOINT_SETPOINT(x)          (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_SETPOINT_SETPOINT_SHIFT)) & CCM_OSCPLL_SETPOINT_SETPOINT_MASK)

#define CCM_OSCPLL_SETPOINT_STANDBY_MASK         (0xFFFF0000U)
#define CCM_OSCPLL_SETPOINT_STANDBY_SHIFT        (16U)
/*! STANDBY - Standby */
#define CCM_OSCPLL_SETPOINT_STANDBY(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_SETPOINT_STANDBY_SHIFT)) & CCM_OSCPLL_SETPOINT_STANDBY_MASK)
/*! @} */

/* The count of CCM_OSCPLL_SETPOINT */
#define CCM_OSCPLL_SETPOINT_COUNT                (29U)

/*! @name OSCPLL_STATUS0 - Clock source working status */
/*! @{ */

#define CCM_OSCPLL_STATUS0_ON_MASK               (0x1U)
#define CCM_OSCPLL_STATUS0_ON_SHIFT              (0U)
/*! ON - Clock source current state
 *  0b0..Clock source is OFF
 *  0b1..Clock source is ON
 */
#define CCM_OSCPLL_STATUS0_ON(x)                 (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS0_ON_SHIFT)) & CCM_OSCPLL_STATUS0_ON_MASK)

#define CCM_OSCPLL_STATUS0_STATUS_EARLY_MASK     (0x10U)
#define CCM_OSCPLL_STATUS0_STATUS_EARLY_SHIFT    (4U)
/*! STATUS_EARLY - Clock source active
 *  0b0..Clock source is not active
 *  0b1..Clock source is active
 */
#define CCM_OSCPLL_STATUS0_STATUS_EARLY(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS0_STATUS_EARLY_SHIFT)) & CCM_OSCPLL_STATUS0_STATUS_EARLY_MASK)

#define CCM_OSCPLL_STATUS0_STATUS_LATE_MASK      (0x20U)
#define CCM_OSCPLL_STATUS0_STATUS_LATE_SHIFT     (5U)
/*! STATUS_LATE - Clock source ready
 *  0b0..Clock source is not ready to use
 *  0b1..Clock source is ready to use
 */
#define CCM_OSCPLL_STATUS0_STATUS_LATE(x)        (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS0_STATUS_LATE_SHIFT)) & CCM_OSCPLL_STATUS0_STATUS_LATE_MASK)

#define CCM_OSCPLL_STATUS0_ACTIVE_DOMAIN_MASK    (0xF00U)
#define CCM_OSCPLL_STATUS0_ACTIVE_DOMAIN_SHIFT   (8U)
/*! ACTIVE_DOMAIN - Domains that own this clock source
 *  0b0000..Clock not owned by any domain
 *  0b0001..Clock owned by Domain0
 *  0b0010..Clock owned by Domain1
 *  0b0011..Clock owned by Domain0 and Domain1
 *  0b0100..Clock owned by Domain2
 *  0b0101..Clock owned by Domain0 and Domain2
 *  0b0110..Clock owned by Domain1 and Domain2
 *  0b0111..Clock owned by Domain0, Domain1 and Domain 2
 *  0b1000..Clock owned by Domain3
 *  0b1001..Clock owned by Domain0 and Domain3
 *  0b1010..Clock owned by Domain1 and Domain3
 *  0b1011..Clock owned by Domain2 and Domain3
 *  0b1100..Clock owned by Domain0, Domain 1, and Domain3
 *  0b1101..Clock owned by Domain0, Domain 2, and Domain3
 *  0b1110..Clock owned by Domain1, Domain 2, and Domain3
 *  0b1111..Clock owned by all domains
 */
#define CCM_OSCPLL_STATUS0_ACTIVE_DOMAIN(x)      (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS0_ACTIVE_DOMAIN_SHIFT)) & CCM_OSCPLL_STATUS0_ACTIVE_DOMAIN_MASK)

#define CCM_OSCPLL_STATUS0_DOMAIN_ENABLE_MASK    (0xF000U)
#define CCM_OSCPLL_STATUS0_DOMAIN_ENABLE_SHIFT   (12U)
/*! DOMAIN_ENABLE - Enable status from each domain
 *  0b0000..No domain request
 *  0b0001..Request from Domain0
 *  0b0010..Request from Domain1
 *  0b0011..Request from Domain0 and Domain1
 *  0b0100..Request from Domain2
 *  0b0101..Request from Domain0 and Domain2
 *  0b0110..Request from Domain1 and Domain2
 *  0b0111..Request from Domain0, Domain1 and Domain 2
 *  0b1000..Request from Domain3
 *  0b1001..Request from Domain0 and Domain3
 *  0b1010..Request from Domain1 and Domain3
 *  0b1011..Request from Domain2 and Domain3
 *  0b1100..Request from Domain0, Domain 1, and Domain3
 *  0b1101..Request from Domain0, Domain 2, and Domain3
 *  0b1110..Request from Domain1, Domain 2, and Domain3
 *  0b1111..Request from all domains
 */
#define CCM_OSCPLL_STATUS0_DOMAIN_ENABLE(x)      (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS0_DOMAIN_ENABLE_SHIFT)) & CCM_OSCPLL_STATUS0_DOMAIN_ENABLE_MASK)

#define CCM_OSCPLL_STATUS0_IN_USE_MASK           (0x10000000U)
#define CCM_OSCPLL_STATUS0_IN_USE_SHIFT          (28U)
/*! IN_USE - In use
 *  0b0..Clock source is not being used by clock roots
 *  0b1..Clock source is being used by clock roots
 */
#define CCM_OSCPLL_STATUS0_IN_USE(x)             (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS0_IN_USE_SHIFT)) & CCM_OSCPLL_STATUS0_IN_USE_MASK)
/*! @} */

/* The count of CCM_OSCPLL_STATUS0 */
#define CCM_OSCPLL_STATUS0_COUNT                 (29U)

/*! @name OSCPLL_STATUS1 - Clock source low power status */
/*! @{ */

#define CCM_OSCPLL_STATUS1_CPU0_MODE_MASK        (0x3U)
#define CCM_OSCPLL_STATUS1_CPU0_MODE_SHIFT       (0U)
/*! CPU0_MODE - Domain0 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_OSCPLL_STATUS1_CPU0_MODE(x)          (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU0_MODE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU0_MODE_MASK)

#define CCM_OSCPLL_STATUS1_CPU0_MODE_REQUEST_MASK (0x4U)
#define CCM_OSCPLL_STATUS1_CPU0_MODE_REQUEST_SHIFT (2U)
/*! CPU0_MODE_REQUEST - Domain0 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_OSCPLL_STATUS1_CPU0_MODE_REQUEST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU0_MODE_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_CPU0_MODE_REQUEST_MASK)

#define CCM_OSCPLL_STATUS1_CPU0_MODE_DONE_MASK   (0x8U)
#define CCM_OSCPLL_STATUS1_CPU0_MODE_DONE_SHIFT  (3U)
/*! CPU0_MODE_DONE - Domain0 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_OSCPLL_STATUS1_CPU0_MODE_DONE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU0_MODE_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU0_MODE_DONE_MASK)

#define CCM_OSCPLL_STATUS1_CPU1_MODE_MASK        (0x30U)
#define CCM_OSCPLL_STATUS1_CPU1_MODE_SHIFT       (4U)
/*! CPU1_MODE - Domain1 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_OSCPLL_STATUS1_CPU1_MODE(x)          (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU1_MODE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU1_MODE_MASK)

#define CCM_OSCPLL_STATUS1_CPU1_MODE_REQUEST_MASK (0x40U)
#define CCM_OSCPLL_STATUS1_CPU1_MODE_REQUEST_SHIFT (6U)
/*! CPU1_MODE_REQUEST - Domain1 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_OSCPLL_STATUS1_CPU1_MODE_REQUEST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU1_MODE_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_CPU1_MODE_REQUEST_MASK)

#define CCM_OSCPLL_STATUS1_CPU1_MODE_DONE_MASK   (0x80U)
#define CCM_OSCPLL_STATUS1_CPU1_MODE_DONE_SHIFT  (7U)
/*! CPU1_MODE_DONE - Domain1 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_OSCPLL_STATUS1_CPU1_MODE_DONE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU1_MODE_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU1_MODE_DONE_MASK)

#define CCM_OSCPLL_STATUS1_CPU2_MODE_MASK        (0x300U)
#define CCM_OSCPLL_STATUS1_CPU2_MODE_SHIFT       (8U)
/*! CPU2_MODE - Domain2 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_OSCPLL_STATUS1_CPU2_MODE(x)          (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU2_MODE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU2_MODE_MASK)

#define CCM_OSCPLL_STATUS1_CPU2_MODE_REQUEST_MASK (0x400U)
#define CCM_OSCPLL_STATUS1_CPU2_MODE_REQUEST_SHIFT (10U)
/*! CPU2_MODE_REQUEST - Domain2 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_OSCPLL_STATUS1_CPU2_MODE_REQUEST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU2_MODE_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_CPU2_MODE_REQUEST_MASK)

#define CCM_OSCPLL_STATUS1_CPU2_MODE_DONE_MASK   (0x800U)
#define CCM_OSCPLL_STATUS1_CPU2_MODE_DONE_SHIFT  (11U)
/*! CPU2_MODE_DONE - Domain2 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_OSCPLL_STATUS1_CPU2_MODE_DONE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU2_MODE_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU2_MODE_DONE_MASK)

#define CCM_OSCPLL_STATUS1_CPU3_MODE_MASK        (0x3000U)
#define CCM_OSCPLL_STATUS1_CPU3_MODE_SHIFT       (12U)
/*! CPU3_MODE - Domain3 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_OSCPLL_STATUS1_CPU3_MODE(x)          (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU3_MODE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU3_MODE_MASK)

#define CCM_OSCPLL_STATUS1_CPU3_MODE_REQUEST_MASK (0x4000U)
#define CCM_OSCPLL_STATUS1_CPU3_MODE_REQUEST_SHIFT (14U)
/*! CPU3_MODE_REQUEST - Domain3 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_OSCPLL_STATUS1_CPU3_MODE_REQUEST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU3_MODE_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_CPU3_MODE_REQUEST_MASK)

#define CCM_OSCPLL_STATUS1_CPU3_MODE_DONE_MASK   (0x8000U)
#define CCM_OSCPLL_STATUS1_CPU3_MODE_DONE_SHIFT  (15U)
/*! CPU3_MODE_DONE - Domain3 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_OSCPLL_STATUS1_CPU3_MODE_DONE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CPU3_MODE_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_CPU3_MODE_DONE_MASK)

#define CCM_OSCPLL_STATUS1_TARGET_SETPOINT_MASK  (0xF0000U)
#define CCM_OSCPLL_STATUS1_TARGET_SETPOINT_SHIFT (16U)
/*! TARGET_SETPOINT - Next Setpoint to change to */
#define CCM_OSCPLL_STATUS1_TARGET_SETPOINT(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_TARGET_SETPOINT_SHIFT)) & CCM_OSCPLL_STATUS1_TARGET_SETPOINT_MASK)

#define CCM_OSCPLL_STATUS1_CURRENT_SETPOINT_MASK (0xF00000U)
#define CCM_OSCPLL_STATUS1_CURRENT_SETPOINT_SHIFT (20U)
/*! CURRENT_SETPOINT - Current Setpoint */
#define CCM_OSCPLL_STATUS1_CURRENT_SETPOINT(x)   (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_CURRENT_SETPOINT_SHIFT)) & CCM_OSCPLL_STATUS1_CURRENT_SETPOINT_MASK)

#define CCM_OSCPLL_STATUS1_SETPOINT_OFF_REQUEST_MASK (0x1000000U)
#define CCM_OSCPLL_STATUS1_SETPOINT_OFF_REQUEST_SHIFT (24U)
/*! SETPOINT_OFF_REQUEST - Clock gate turn off request from GPC Setpoint
 *  0b0..No request
 *  0b1..Clock gate requested to be turned off
 */
#define CCM_OSCPLL_STATUS1_SETPOINT_OFF_REQUEST(x) (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_SETPOINT_OFF_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_SETPOINT_OFF_REQUEST_MASK)

#define CCM_OSCPLL_STATUS1_SETPOINT_OFF_DONE_MASK (0x2000000U)
#define CCM_OSCPLL_STATUS1_SETPOINT_OFF_DONE_SHIFT (25U)
/*! SETPOINT_OFF_DONE - Clock source turn off finish from GPC Setpoint
 *  0b0..Clock source is not turned off
 *  0b1..Clock source is turned off
 */
#define CCM_OSCPLL_STATUS1_SETPOINT_OFF_DONE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_SETPOINT_OFF_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_SETPOINT_OFF_DONE_MASK)

#define CCM_OSCPLL_STATUS1_SETPOINT_ON_REQUEST_MASK (0x4000000U)
#define CCM_OSCPLL_STATUS1_SETPOINT_ON_REQUEST_SHIFT (26U)
/*! SETPOINT_ON_REQUEST - Clock gate turn on request from GPC Setpoint
 *  0b0..No request
 *  0b1..Clock gate requested to be turned on
 */
#define CCM_OSCPLL_STATUS1_SETPOINT_ON_REQUEST(x) (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_SETPOINT_ON_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_SETPOINT_ON_REQUEST_MASK)

#define CCM_OSCPLL_STATUS1_SETPOINT_ON_DONE_MASK (0x8000000U)
#define CCM_OSCPLL_STATUS1_SETPOINT_ON_DONE_SHIFT (27U)
/*! SETPOINT_ON_DONE - Clock gate turn on finish from GPC Setpoint
 *  0b0..No request
 *  0b1..Request to turn on clock gate
 */
#define CCM_OSCPLL_STATUS1_SETPOINT_ON_DONE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_SETPOINT_ON_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_SETPOINT_ON_DONE_MASK)

#define CCM_OSCPLL_STATUS1_STANDBY_IN_REQUEST_MASK (0x10000000U)
#define CCM_OSCPLL_STATUS1_STANDBY_IN_REQUEST_SHIFT (28U)
/*! STANDBY_IN_REQUEST - Clock gate turn off request from GPC standby
 *  0b0..No request
 *  0b1..Clock gate requested to be turned off
 */
#define CCM_OSCPLL_STATUS1_STANDBY_IN_REQUEST(x) (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_STANDBY_IN_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_STANDBY_IN_REQUEST_MASK)

#define CCM_OSCPLL_STATUS1_STANDBY_IN_DONE_MASK  (0x20000000U)
#define CCM_OSCPLL_STATUS1_STANDBY_IN_DONE_SHIFT (29U)
/*! STANDBY_IN_DONE - Clock source turn off finish from GPC standby
 *  0b0..Clock source is not turned off
 *  0b1..Clock source is turned off
 */
#define CCM_OSCPLL_STATUS1_STANDBY_IN_DONE(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_STANDBY_IN_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_STANDBY_IN_DONE_MASK)

#define CCM_OSCPLL_STATUS1_STANDBY_OUT_DONE_MASK (0x40000000U)
#define CCM_OSCPLL_STATUS1_STANDBY_OUT_DONE_SHIFT (30U)
/*! STANDBY_OUT_DONE - Clock gate turn on finish from GPC standby
 *  0b0..Request to turn on Clock gate is not complete
 *  0b1..Request to turn on Clock gate is complete
 */
#define CCM_OSCPLL_STATUS1_STANDBY_OUT_DONE(x)   (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_STANDBY_OUT_DONE_SHIFT)) & CCM_OSCPLL_STATUS1_STANDBY_OUT_DONE_MASK)

#define CCM_OSCPLL_STATUS1_STANDBY_OUT_REQUEST_MASK (0x80000000U)
#define CCM_OSCPLL_STATUS1_STANDBY_OUT_REQUEST_SHIFT (31U)
/*! STANDBY_OUT_REQUEST - Clock gate turn on request from GPC standby
 *  0b0..No request
 *  0b1..Clock gate requested to be turned on
 */
#define CCM_OSCPLL_STATUS1_STANDBY_OUT_REQUEST(x) (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_STATUS1_STANDBY_OUT_REQUEST_SHIFT)) & CCM_OSCPLL_STATUS1_STANDBY_OUT_REQUEST_MASK)
/*! @} */

/* The count of CCM_OSCPLL_STATUS1 */
#define CCM_OSCPLL_STATUS1_COUNT                 (29U)

/*! @name OSCPLL_CONFIG - Clock source configuration */
/*! @{ */

#define CCM_OSCPLL_CONFIG_AUTOMODE_PRESENT_MASK  (0x2U)
#define CCM_OSCPLL_CONFIG_AUTOMODE_PRESENT_SHIFT (1U)
/*! AUTOMODE_PRESENT - Automode Present
 *  0b0..Not present
 *  0b1..Present
 */
#define CCM_OSCPLL_CONFIG_AUTOMODE_PRESENT(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_CONFIG_AUTOMODE_PRESENT_SHIFT)) & CCM_OSCPLL_CONFIG_AUTOMODE_PRESENT_MASK)

#define CCM_OSCPLL_CONFIG_SETPOINT_PRESENT_MASK  (0x10U)
#define CCM_OSCPLL_CONFIG_SETPOINT_PRESENT_SHIFT (4U)
/*! SETPOINT_PRESENT - Setpoint present
 *  0b0..Setpoint is not implemented.
 *  0b1..Setpoint is implemented.
 */
#define CCM_OSCPLL_CONFIG_SETPOINT_PRESENT(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_CONFIG_SETPOINT_PRESENT_SHIFT)) & CCM_OSCPLL_CONFIG_SETPOINT_PRESENT_MASK)
/*! @} */

/* The count of CCM_OSCPLL_CONFIG */
#define CCM_OSCPLL_CONFIG_COUNT                  (29U)

/*! @name OSCPLL_AUTHEN - Clock source access control */
/*! @{ */

#define CCM_OSCPLL_AUTHEN_TZ_USER_MASK           (0x1U)
#define CCM_OSCPLL_AUTHEN_TZ_USER_SHIFT          (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_OSCPLL_AUTHEN_TZ_USER(x)             (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_TZ_USER_SHIFT)) & CCM_OSCPLL_AUTHEN_TZ_USER_MASK)

#define CCM_OSCPLL_AUTHEN_TZ_NS_MASK             (0x2U)
#define CCM_OSCPLL_AUTHEN_TZ_NS_SHIFT            (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_OSCPLL_AUTHEN_TZ_NS(x)               (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_TZ_NS_SHIFT)) & CCM_OSCPLL_AUTHEN_TZ_NS_MASK)

#define CCM_OSCPLL_AUTHEN_LOCK_TZ_MASK           (0x10U)
#define CCM_OSCPLL_AUTHEN_LOCK_TZ_SHIFT          (4U)
/*! LOCK_TZ - lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_OSCPLL_AUTHEN_LOCK_TZ(x)             (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_LOCK_TZ_SHIFT)) & CCM_OSCPLL_AUTHEN_LOCK_TZ_MASK)

#define CCM_OSCPLL_AUTHEN_WHITE_LIST_MASK        (0xF00U)
#define CCM_OSCPLL_AUTHEN_WHITE_LIST_SHIFT       (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_OSCPLL_AUTHEN_WHITE_LIST(x)          (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_WHITE_LIST_SHIFT)) & CCM_OSCPLL_AUTHEN_WHITE_LIST_MASK)

#define CCM_OSCPLL_AUTHEN_LOCK_LIST_MASK         (0x1000U)
#define CCM_OSCPLL_AUTHEN_LOCK_LIST_SHIFT        (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_OSCPLL_AUTHEN_LOCK_LIST(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_LOCK_LIST_SHIFT)) & CCM_OSCPLL_AUTHEN_LOCK_LIST_MASK)

#define CCM_OSCPLL_AUTHEN_DOMAIN_MODE_MASK       (0x10000U)
#define CCM_OSCPLL_AUTHEN_DOMAIN_MODE_SHIFT      (16U)
/*! DOMAIN_MODE - Low power and access control by domain
 *  0b0..Clock does not work in Domain Mode.
 *  0b1..Clock works in Domain Mode.
 */
#define CCM_OSCPLL_AUTHEN_DOMAIN_MODE(x)         (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_OSCPLL_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_OSCPLL_AUTHEN_SETPOINT_MODE_MASK     (0x20000U)
#define CCM_OSCPLL_AUTHEN_SETPOINT_MODE_SHIFT    (17U)
/*! SETPOINT_MODE - LPCG works in Setpoint controlled Mode. */
#define CCM_OSCPLL_AUTHEN_SETPOINT_MODE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_SETPOINT_MODE_SHIFT)) & CCM_OSCPLL_AUTHEN_SETPOINT_MODE_MASK)

#define CCM_OSCPLL_AUTHEN_CPULPM_MASK            (0x40000U)
#define CCM_OSCPLL_AUTHEN_CPULPM_SHIFT           (18U)
/*! CPULPM - CPU Low Power Mode
 *  0b0..PLL does not function in Low power Mode
 *  0b1..PLL functions in Low Power Mode
 */
#define CCM_OSCPLL_AUTHEN_CPULPM(x)              (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_CPULPM_SHIFT)) & CCM_OSCPLL_AUTHEN_CPULPM_MASK)

#define CCM_OSCPLL_AUTHEN_LOCK_MODE_MASK         (0x100000U)
#define CCM_OSCPLL_AUTHEN_LOCK_MODE_SHIFT        (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_OSCPLL_AUTHEN_LOCK_MODE(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OSCPLL_AUTHEN_LOCK_MODE_SHIFT)) & CCM_OSCPLL_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_OSCPLL_AUTHEN */
#define CCM_OSCPLL_AUTHEN_COUNT                  (29U)

/*! @name LPCG_DIRECT - LPCG direct control */
/*! @{ */

#define CCM_LPCG_DIRECT_ON_MASK                  (0x1U)
#define CCM_LPCG_DIRECT_ON_SHIFT                 (0U)
/*! ON - LPCG on
 *  0b0..LPCG is OFF.
 *  0b1..LPCG is ON.
 */
#define CCM_LPCG_DIRECT_ON(x)                    (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_DIRECT_ON_SHIFT)) & CCM_LPCG_DIRECT_ON_MASK)
/*! @} */

/* The count of CCM_LPCG_DIRECT */
#define CCM_LPCG_DIRECT_COUNT                    (138U)

/*! @name LPCG_DOMAIN - LPCG domain control */
/*! @{ */

#define CCM_LPCG_DOMAIN_LEVEL_MASK               (0x7U)
#define CCM_LPCG_DOMAIN_LEVEL_SHIFT              (0U)
/*! LEVEL - Current dependence level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_LPCG_DOMAIN_LEVEL(x)                 (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_DOMAIN_LEVEL_SHIFT)) & CCM_LPCG_DOMAIN_LEVEL_MASK)

#define CCM_LPCG_DOMAIN_LEVEL0_MASK              (0x70000U)
#define CCM_LPCG_DOMAIN_LEVEL0_SHIFT             (16U)
/*! LEVEL0 - Depend level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_LPCG_DOMAIN_LEVEL0(x)                (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_DOMAIN_LEVEL0_SHIFT)) & CCM_LPCG_DOMAIN_LEVEL0_MASK)

#define CCM_LPCG_DOMAIN_LEVEL1_MASK              (0x700000U)
#define CCM_LPCG_DOMAIN_LEVEL1_SHIFT             (20U)
/*! LEVEL1 - Depend level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_LPCG_DOMAIN_LEVEL1(x)                (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_DOMAIN_LEVEL1_SHIFT)) & CCM_LPCG_DOMAIN_LEVEL1_MASK)

#define CCM_LPCG_DOMAIN_LEVEL2_MASK              (0x7000000U)
#define CCM_LPCG_DOMAIN_LEVEL2_SHIFT             (24U)
/*! LEVEL2 - Depend level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_LPCG_DOMAIN_LEVEL2(x)                (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_DOMAIN_LEVEL2_SHIFT)) & CCM_LPCG_DOMAIN_LEVEL2_MASK)

#define CCM_LPCG_DOMAIN_LEVEL3_MASK              (0x70000000U)
#define CCM_LPCG_DOMAIN_LEVEL3_SHIFT             (28U)
/*! LEVEL3 - Depend level
 *  0b000..This clock source is not needed in any mode, and can be turned off
 *  0b001..This clock source is needed in RUN mode, but not needed in WAIT, STOP mode
 *  0b010..This clock source is needed in RUN and WAIT mode, but not needed in STOP mode
 *  0b011..This clock source is needed in RUN, WAIT and STOP mode
 *  0b100..This clock source is always on in any mode (including SUSPEND)
 *  0b101, 0b110, 0b111..Reserved
 */
#define CCM_LPCG_DOMAIN_LEVEL3(x)                (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_DOMAIN_LEVEL3_SHIFT)) & CCM_LPCG_DOMAIN_LEVEL3_MASK)
/*! @} */

/* The count of CCM_LPCG_DOMAIN */
#define CCM_LPCG_DOMAIN_COUNT                    (138U)

/*! @name LPCG_SETPOINT - LPCG Setpoint setting */
/*! @{ */

#define CCM_LPCG_SETPOINT_SETPOINT_MASK          (0xFFFFU)
#define CCM_LPCG_SETPOINT_SETPOINT_SHIFT         (0U)
/*! SETPOINT - Setpoints */
#define CCM_LPCG_SETPOINT_SETPOINT(x)            (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_SETPOINT_SETPOINT_SHIFT)) & CCM_LPCG_SETPOINT_SETPOINT_MASK)

#define CCM_LPCG_SETPOINT_STANDBY_MASK           (0xFFFF0000U)
#define CCM_LPCG_SETPOINT_STANDBY_SHIFT          (16U)
/*! STANDBY - Standby */
#define CCM_LPCG_SETPOINT_STANDBY(x)             (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_SETPOINT_STANDBY_SHIFT)) & CCM_LPCG_SETPOINT_STANDBY_MASK)
/*! @} */

/* The count of CCM_LPCG_SETPOINT */
#define CCM_LPCG_SETPOINT_COUNT                  (138U)

/*! @name LPCG_STATUS0 - LPCG working status */
/*! @{ */

#define CCM_LPCG_STATUS0_ON_MASK                 (0x1U)
#define CCM_LPCG_STATUS0_ON_SHIFT                (0U)
/*! ON - LPCG current state
 *  0b0..LPCG is OFF.
 *  0b1..LPCG is ON.
 */
#define CCM_LPCG_STATUS0_ON(x)                   (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS0_ON_SHIFT)) & CCM_LPCG_STATUS0_ON_MASK)

#define CCM_LPCG_STATUS0_ACTIVE_DOMAIN_MASK      (0xF00U)
#define CCM_LPCG_STATUS0_ACTIVE_DOMAIN_SHIFT     (8U)
/*! ACTIVE_DOMAIN - Domains that own this clock gate
 *  0b0000..Clock not owned by any domain
 *  0b0001..Clock owned by Domain0
 *  0b0010..Clock owned by Domain1
 *  0b0011..Clock owned by Domain0 and Domain1
 *  0b0100..Clock owned by Domain2
 *  0b0101..Clock owned by Domain0 and Domain2
 *  0b0110..Clock owned by Domain1 and Domain2
 *  0b0111..Clock owned by Domain0, Domain1 and Domain 2
 *  0b1000..Clock owned by Domain3
 *  0b1001..Clock owned by Domain0 and Domain3
 *  0b1010..Clock owned by Domain1 and Domain3
 *  0b1011..Clock owned by Domain2 and Domain3
 *  0b1100..Clock owned by Domain0, Domain 1, and Domain3
 *  0b1101..Clock owned by Domain0, Domain 2, and Domain3
 *  0b1110..Clock owned by Domain1, Domain 2, and Domain3
 *  0b1111..Clock owned by all domains
 */
#define CCM_LPCG_STATUS0_ACTIVE_DOMAIN(x)        (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS0_ACTIVE_DOMAIN_SHIFT)) & CCM_LPCG_STATUS0_ACTIVE_DOMAIN_MASK)

#define CCM_LPCG_STATUS0_DOMAIN_ENABLE_MASK      (0xF000U)
#define CCM_LPCG_STATUS0_DOMAIN_ENABLE_SHIFT     (12U)
/*! DOMAIN_ENABLE - Enable status from each domain
 *  0b0000..No domain request
 *  0b0001..Request from Domain0
 *  0b0010..Request from Domain1
 *  0b0011..Request from Domain0 and Domain1
 *  0b0100..Request from Domain2
 *  0b0101..Request from Domain0 and Domain2
 *  0b0110..Request from Domain1 and Domain2
 *  0b0111..Request from Domain0, Domain1 and Domain 2
 *  0b1000..Request from Domain3
 *  0b1001..Request from Domain0 and Domain3
 *  0b1010..Request from Domain1 and Domain3
 *  0b1011..Request from Domain2 and Domain3
 *  0b1100..Request from Domain0, Domain 1, and Domain3
 *  0b1101..Request from Domain0, Domain 2, and Domain3
 *  0b1110..Request from Domain1, Domain 2, and Domain3
 *  0b1111..Request from all domains
 */
#define CCM_LPCG_STATUS0_DOMAIN_ENABLE(x)        (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS0_DOMAIN_ENABLE_SHIFT)) & CCM_LPCG_STATUS0_DOMAIN_ENABLE_MASK)
/*! @} */

/* The count of CCM_LPCG_STATUS0 */
#define CCM_LPCG_STATUS0_COUNT                   (138U)

/*! @name LPCG_STATUS1 - LPCG low power status */
/*! @{ */

#define CCM_LPCG_STATUS1_CPU0_MODE_MASK          (0x3U)
#define CCM_LPCG_STATUS1_CPU0_MODE_SHIFT         (0U)
/*! CPU0_MODE - Domain0 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_LPCG_STATUS1_CPU0_MODE(x)            (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU0_MODE_SHIFT)) & CCM_LPCG_STATUS1_CPU0_MODE_MASK)

#define CCM_LPCG_STATUS1_CPU0_MODE_REQUEST_MASK  (0x4U)
#define CCM_LPCG_STATUS1_CPU0_MODE_REQUEST_SHIFT (2U)
/*! CPU0_MODE_REQUEST - Domain0 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_LPCG_STATUS1_CPU0_MODE_REQUEST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU0_MODE_REQUEST_SHIFT)) & CCM_LPCG_STATUS1_CPU0_MODE_REQUEST_MASK)

#define CCM_LPCG_STATUS1_CPU0_MODE_DONE_MASK     (0x8U)
#define CCM_LPCG_STATUS1_CPU0_MODE_DONE_SHIFT    (3U)
/*! CPU0_MODE_DONE - Domain0 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_LPCG_STATUS1_CPU0_MODE_DONE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU0_MODE_DONE_SHIFT)) & CCM_LPCG_STATUS1_CPU0_MODE_DONE_MASK)

#define CCM_LPCG_STATUS1_CPU1_MODE_MASK          (0x30U)
#define CCM_LPCG_STATUS1_CPU1_MODE_SHIFT         (4U)
/*! CPU1_MODE - Domain1 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_LPCG_STATUS1_CPU1_MODE(x)            (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU1_MODE_SHIFT)) & CCM_LPCG_STATUS1_CPU1_MODE_MASK)

#define CCM_LPCG_STATUS1_CPU1_MODE_REQUEST_MASK  (0x40U)
#define CCM_LPCG_STATUS1_CPU1_MODE_REQUEST_SHIFT (6U)
/*! CPU1_MODE_REQUEST - Domain1 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_LPCG_STATUS1_CPU1_MODE_REQUEST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU1_MODE_REQUEST_SHIFT)) & CCM_LPCG_STATUS1_CPU1_MODE_REQUEST_MASK)

#define CCM_LPCG_STATUS1_CPU1_MODE_DONE_MASK     (0x80U)
#define CCM_LPCG_STATUS1_CPU1_MODE_DONE_SHIFT    (7U)
/*! CPU1_MODE_DONE - Domain1 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_LPCG_STATUS1_CPU1_MODE_DONE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU1_MODE_DONE_SHIFT)) & CCM_LPCG_STATUS1_CPU1_MODE_DONE_MASK)

#define CCM_LPCG_STATUS1_CPU2_MODE_MASK          (0x300U)
#define CCM_LPCG_STATUS1_CPU2_MODE_SHIFT         (8U)
/*! CPU2_MODE - Domain2 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_LPCG_STATUS1_CPU2_MODE(x)            (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU2_MODE_SHIFT)) & CCM_LPCG_STATUS1_CPU2_MODE_MASK)

#define CCM_LPCG_STATUS1_CPU2_MODE_REQUEST_MASK  (0x400U)
#define CCM_LPCG_STATUS1_CPU2_MODE_REQUEST_SHIFT (10U)
/*! CPU2_MODE_REQUEST - Domain2 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_LPCG_STATUS1_CPU2_MODE_REQUEST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU2_MODE_REQUEST_SHIFT)) & CCM_LPCG_STATUS1_CPU2_MODE_REQUEST_MASK)

#define CCM_LPCG_STATUS1_CPU2_MODE_DONE_MASK     (0x800U)
#define CCM_LPCG_STATUS1_CPU2_MODE_DONE_SHIFT    (11U)
/*! CPU2_MODE_DONE - Domain2 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_LPCG_STATUS1_CPU2_MODE_DONE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU2_MODE_DONE_SHIFT)) & CCM_LPCG_STATUS1_CPU2_MODE_DONE_MASK)

#define CCM_LPCG_STATUS1_CPU3_MODE_MASK          (0x3000U)
#define CCM_LPCG_STATUS1_CPU3_MODE_SHIFT         (12U)
/*! CPU3_MODE - Domain3 Low Power Mode
 *  0b00..Run
 *  0b01..Wait
 *  0b10..Stop
 *  0b11..Suspend
 */
#define CCM_LPCG_STATUS1_CPU3_MODE(x)            (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU3_MODE_SHIFT)) & CCM_LPCG_STATUS1_CPU3_MODE_MASK)

#define CCM_LPCG_STATUS1_CPU3_MODE_REQUEST_MASK  (0x4000U)
#define CCM_LPCG_STATUS1_CPU3_MODE_REQUEST_SHIFT (14U)
/*! CPU3_MODE_REQUEST - Domain3 request enter Low Power Mode
 *  0b0..No request
 *  0b1..Request from domain to enter Low Power Mode
 */
#define CCM_LPCG_STATUS1_CPU3_MODE_REQUEST(x)    (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU3_MODE_REQUEST_SHIFT)) & CCM_LPCG_STATUS1_CPU3_MODE_REQUEST_MASK)

#define CCM_LPCG_STATUS1_CPU3_MODE_DONE_MASK     (0x8000U)
#define CCM_LPCG_STATUS1_CPU3_MODE_DONE_SHIFT    (15U)
/*! CPU3_MODE_DONE - Domain3 Low Power Mode task done
 *  0b0..Clock is not gated
 *  0b1..Clock is gated-off
 */
#define CCM_LPCG_STATUS1_CPU3_MODE_DONE(x)       (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CPU3_MODE_DONE_SHIFT)) & CCM_LPCG_STATUS1_CPU3_MODE_DONE_MASK)

#define CCM_LPCG_STATUS1_TARGET_SETPOINT_MASK    (0xF0000U)
#define CCM_LPCG_STATUS1_TARGET_SETPOINT_SHIFT   (16U)
/*! TARGET_SETPOINT - Next Setpoint to change to */
#define CCM_LPCG_STATUS1_TARGET_SETPOINT(x)      (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_TARGET_SETPOINT_SHIFT)) & CCM_LPCG_STATUS1_TARGET_SETPOINT_MASK)

#define CCM_LPCG_STATUS1_CURRENT_SETPOINT_MASK   (0xF00000U)
#define CCM_LPCG_STATUS1_CURRENT_SETPOINT_SHIFT  (20U)
/*! CURRENT_SETPOINT - Current Setpoint */
#define CCM_LPCG_STATUS1_CURRENT_SETPOINT(x)     (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_CURRENT_SETPOINT_SHIFT)) & CCM_LPCG_STATUS1_CURRENT_SETPOINT_MASK)

#define CCM_LPCG_STATUS1_SETPOINT_OFF_REQUEST_MASK (0x1000000U)
#define CCM_LPCG_STATUS1_SETPOINT_OFF_REQUEST_SHIFT (24U)
/*! SETPOINT_OFF_REQUEST - Clock gate turn off request from GPC Setpoint
 *  0b0..No request
 *  0b1..Clock gate requested to be turned off
 */
#define CCM_LPCG_STATUS1_SETPOINT_OFF_REQUEST(x) (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_SETPOINT_OFF_REQUEST_SHIFT)) & CCM_LPCG_STATUS1_SETPOINT_OFF_REQUEST_MASK)

#define CCM_LPCG_STATUS1_SETPOINT_OFF_DONE_MASK  (0x2000000U)
#define CCM_LPCG_STATUS1_SETPOINT_OFF_DONE_SHIFT (25U)
/*! SETPOINT_OFF_DONE - Clock gate turn off finish from GPC Setpoint
 *  0b0..Clock gate is not turned off
 *  0b1..Clock gate is turned off
 */
#define CCM_LPCG_STATUS1_SETPOINT_OFF_DONE(x)    (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_SETPOINT_OFF_DONE_SHIFT)) & CCM_LPCG_STATUS1_SETPOINT_OFF_DONE_MASK)

#define CCM_LPCG_STATUS1_SETPOINT_ON_REQUEST_MASK (0x4000000U)
#define CCM_LPCG_STATUS1_SETPOINT_ON_REQUEST_SHIFT (26U)
/*! SETPOINT_ON_REQUEST - Clock gate turn on request from GPC Setpoint
 *  0b0..No request
 *  0b1..Clock gate requested to be turned on
 */
#define CCM_LPCG_STATUS1_SETPOINT_ON_REQUEST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_SETPOINT_ON_REQUEST_SHIFT)) & CCM_LPCG_STATUS1_SETPOINT_ON_REQUEST_MASK)

#define CCM_LPCG_STATUS1_SETPOINT_ON_DONE_MASK   (0x8000000U)
#define CCM_LPCG_STATUS1_SETPOINT_ON_DONE_SHIFT  (27U)
/*! SETPOINT_ON_DONE - Clock gate turn on finish from GPC Setpoint
 *  0b0..Clock gate is not turned on
 *  0b1..Clock gate is turned on
 */
#define CCM_LPCG_STATUS1_SETPOINT_ON_DONE(x)     (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_STATUS1_SETPOINT_ON_DONE_SHIFT)) & CCM_LPCG_STATUS1_SETPOINT_ON_DONE_MASK)
/*! @} */

/* The count of CCM_LPCG_STATUS1 */
#define CCM_LPCG_STATUS1_COUNT                   (138U)

/*! @name LPCG_CONFIG - LPCG configuration */
/*! @{ */

#define CCM_LPCG_CONFIG_SETPOINT_PRESENT_MASK    (0x10U)
#define CCM_LPCG_CONFIG_SETPOINT_PRESENT_SHIFT   (4U)
/*! SETPOINT_PRESENT - Setpoint present
 *  0b0..Setpoint is not implemented.
 *  0b1..Setpoint is implemented.
 */
#define CCM_LPCG_CONFIG_SETPOINT_PRESENT(x)      (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_CONFIG_SETPOINT_PRESENT_SHIFT)) & CCM_LPCG_CONFIG_SETPOINT_PRESENT_MASK)
/*! @} */

/* The count of CCM_LPCG_CONFIG */
#define CCM_LPCG_CONFIG_COUNT                    (138U)

/*! @name LPCG_AUTHEN - LPCG access control */
/*! @{ */

#define CCM_LPCG_AUTHEN_TZ_USER_MASK             (0x1U)
#define CCM_LPCG_AUTHEN_TZ_USER_SHIFT            (0U)
/*! TZ_USER - User access
 *  0b0..LPCG cannot be changed in user mode.
 *  0b1..LPCG can be changed in user mode.
 */
#define CCM_LPCG_AUTHEN_TZ_USER(x)               (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_TZ_USER_SHIFT)) & CCM_LPCG_AUTHEN_TZ_USER_MASK)

#define CCM_LPCG_AUTHEN_TZ_NS_MASK               (0x2U)
#define CCM_LPCG_AUTHEN_TZ_NS_SHIFT              (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_LPCG_AUTHEN_TZ_NS(x)                 (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_TZ_NS_SHIFT)) & CCM_LPCG_AUTHEN_TZ_NS_MASK)

#define CCM_LPCG_AUTHEN_LOCK_TZ_MASK             (0x10U)
#define CCM_LPCG_AUTHEN_LOCK_TZ_SHIFT            (4U)
/*! LOCK_TZ - lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_LPCG_AUTHEN_LOCK_TZ(x)               (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_LOCK_TZ_SHIFT)) & CCM_LPCG_AUTHEN_LOCK_TZ_MASK)

#define CCM_LPCG_AUTHEN_WHITE_LIST_MASK          (0xF00U)
#define CCM_LPCG_AUTHEN_WHITE_LIST_SHIFT         (8U)
/*! WHITE_LIST - Whitelist */
#define CCM_LPCG_AUTHEN_WHITE_LIST(x)            (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_WHITE_LIST_SHIFT)) & CCM_LPCG_AUTHEN_WHITE_LIST_MASK)

#define CCM_LPCG_AUTHEN_LOCK_LIST_MASK           (0x1000U)
#define CCM_LPCG_AUTHEN_LOCK_LIST_SHIFT          (12U)
/*! LOCK_LIST - Lock Whitelist
 *  0b0..Whitelist is not locked.
 *  0b1..Whitelist is locked.
 */
#define CCM_LPCG_AUTHEN_LOCK_LIST(x)             (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_LOCK_LIST_SHIFT)) & CCM_LPCG_AUTHEN_LOCK_LIST_MASK)

#define CCM_LPCG_AUTHEN_DOMAIN_MODE_MASK         (0x10000U)
#define CCM_LPCG_AUTHEN_DOMAIN_MODE_SHIFT        (16U)
/*! DOMAIN_MODE - Low power and access control by domain
 *  0b0..Clock does not work in Domain Mode
 *  0b1..Clock works in Domain Mode
 */
#define CCM_LPCG_AUTHEN_DOMAIN_MODE(x)           (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_LPCG_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_LPCG_AUTHEN_SETPOINT_MODE_MASK       (0x20000U)
#define CCM_LPCG_AUTHEN_SETPOINT_MODE_SHIFT      (17U)
/*! SETPOINT_MODE - Low power and access control by Setpoint
 *  0b0..LPCG is not functioning in Setpoint controlled Mode
 *  0b1..LPCG is functioning in Setpoint controlled Mode
 */
#define CCM_LPCG_AUTHEN_SETPOINT_MODE(x)         (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_SETPOINT_MODE_SHIFT)) & CCM_LPCG_AUTHEN_SETPOINT_MODE_MASK)

#define CCM_LPCG_AUTHEN_CPULPM_MASK              (0x40000U)
#define CCM_LPCG_AUTHEN_CPULPM_SHIFT             (18U)
/*! CPULPM - CPU Low Power Mode
 *  0b0..LPCG is not functioning in Low power Mode
 *  0b1..LPCG is functioning in Low Power Mode
 */
#define CCM_LPCG_AUTHEN_CPULPM(x)                (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_CPULPM_SHIFT)) & CCM_LPCG_AUTHEN_CPULPM_MASK)

#define CCM_LPCG_AUTHEN_LOCK_MODE_MASK           (0x100000U)
#define CCM_LPCG_AUTHEN_LOCK_MODE_SHIFT          (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_LPCG_AUTHEN_LOCK_MODE(x)             (((uint32_t)(((uint32_t)(x)) << CCM_LPCG_AUTHEN_LOCK_MODE_SHIFT)) & CCM_LPCG_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_LPCG_AUTHEN */
#define CCM_LPCG_AUTHEN_COUNT                    (138U)


/*!
 * @}
 */ /* end of group CCM_Register_Masks */


/*!
 * @}
 */ /* end of group CCM_Peripheral_Access_Layer */


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


#endif  /* PERI_CCM_H_ */

