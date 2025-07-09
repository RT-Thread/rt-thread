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
**         CMSIS Peripheral Access Layer for SSARC_LP
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
 * @file PERI_SSARC_LP.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for SSARC_LP
 *
 * CMSIS Peripheral Access Layer for SSARC_LP
 */

#if !defined(PERI_SSARC_LP_H_)
#define PERI_SSARC_LP_H_                         /**< Symbol preventing repeated inclusion */

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
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
#if !defined(SSARC_POWER_DOMAIN_NAME_T_)
#define SSARC_POWER_DOMAIN_NAME_T_
/*!
 * @addtogroup ssarc_mapping
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the SSARC mapping
 *
 * The name of power domain.
 */

typedef enum _ssarc_power_domain_name
{
    kSSARC_MEGAMIXPowerDomain       = 0U,          /**< MEGAMIX Power Domain, request from BPC0. */
    kSSARC_DISPLAYMIXPowerDomain    = 1U,          /**< DISPLAYMIX Power Domain, request from BPC1. */
    kSSARC_WAKEUPMIXPowerDomain     = 2U,          /**< WAKEUPMIX Power Domain, request from BPC2. */
    kSSARC_LPSRMIXPowerDomain       = 3U,          /**< LPSRMIX Power Domain, request from BPC3. */
    kSSARC_PowerDomain4             = 4U,          /**< MIPI PHY Power Domain, request from BPC4. */
    kSSARC_PowerDomain5             = 5U,          /**< Virtual power domain, request from BPC5. */
    kSSARC_PowerDomain6             = 6U,          /**< Virtual power domain, request from BPC6. */
    kSSARC_PowerDomain7             = 7U,          /**< Virtual power domain, request from BPC7. */
} ssarc_power_domain_name_t;
#endif /* SSARC_POWER_DOMAIN_NAME_T_ */

#if !defined(SSARC_CPU_DOMAIN_NAME_T_)
#define SSARC_CPU_DOMAIN_NAME_T_
 /*
 * @brief The name of cpu domain.
 */
typedef enum _ssarc_cpu_domain_name
{
    kSSARC_CM7Core                  = 0U,          /**< CM7 Core domain. */
    kSSARC_CM4Core                  = 1U,          /**< CM4 Core domain. */
} ssarc_cpu_domain_name_t;

/* @} */
#endif /* SSARC_CPU_DOMAIN_NAME_T_ */


/*!
 * @}
 */ /* end of group Mapping_Information */


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
   -- SSARC_LP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SSARC_LP_Peripheral_Access_Layer SSARC_LP Peripheral Access Layer
 * @{
 */

/** SSARC_LP - Size of Registers Arrays */
#define SSARC_LP_GROUPS_COUNT                     16u

/** SSARC_LP - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x20 */
    __IO uint32_t DESC_CTRL0;                        /**< Descriptor Control0 0 Register..Descriptor Control0 15 Register, array offset: 0x0, array step: 0x20 */
    __IO uint32_t DESC_CTRL1;                        /**< Descriptor Control1 0 Register..Descriptor Control1 15 Register, array offset: 0x4, array step: 0x20 */
    __IO uint32_t DESC_ADDR_UP;                      /**< Descriptor Address Up 0 Register..Descriptor Address Up 15 Register, array offset: 0x8, array step: 0x20 */
    __IO uint32_t DESC_ADDR_DOWN;                    /**< Descriptor Address Down 0 Register..Descriptor Address Down 15 Register, array offset: 0xC, array step: 0x20 */
         uint8_t RESERVED_0[16];
  } GROUPS[SSARC_LP_GROUPS_COUNT];
  __IO uint32_t CTRL;                              /**< Control Register, offset: 0x200 */
  __IO uint32_t INT_STATUS;                        /**< Interrupt Status Register, offset: 0x204 */
       uint8_t RESERVED_0[4];
  __IO uint32_t HP_TIMEOUT;                        /**< HP Timeout Register, offset: 0x20C */
       uint8_t RESERVED_1[12];
  __I  uint32_t HW_GROUP_PENDING;                  /**< Hardware Request Pending Register, offset: 0x21C */
  __I  uint32_t SW_GROUP_PENDING;                  /**< Software Request Pending Register, offset: 0x220 */
} SSARC_LP_Type;

/* ----------------------------------------------------------------------------
   -- SSARC_LP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SSARC_LP_Register_Masks SSARC_LP Register Masks
 * @{
 */

/*! @name DESC_CTRL0 - Descriptor Control0 0 Register..Descriptor Control0 15 Register */
/*! @{ */

#define SSARC_LP_DESC_CTRL0_START_MASK           (0x3FFU)
#define SSARC_LP_DESC_CTRL0_START_SHIFT          (0U)
/*! START - Start index */
#define SSARC_LP_DESC_CTRL0_START(x)             (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL0_START_SHIFT)) & SSARC_LP_DESC_CTRL0_START_MASK)

#define SSARC_LP_DESC_CTRL0_END_MASK             (0xFFC00U)
#define SSARC_LP_DESC_CTRL0_END_SHIFT            (10U)
/*! END - End index */
#define SSARC_LP_DESC_CTRL0_END(x)               (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL0_END_SHIFT)) & SSARC_LP_DESC_CTRL0_END_MASK)

#define SSARC_LP_DESC_CTRL0_SV_ORDER_MASK        (0x100000U)
#define SSARC_LP_DESC_CTRL0_SV_ORDER_SHIFT       (20U)
/*! SV_ORDER - Save Order
 *  0b0..Descriptors within the group are processed from start to end
 *  0b1..Descriptors within the group are processed from end to start
 */
#define SSARC_LP_DESC_CTRL0_SV_ORDER(x)          (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL0_SV_ORDER_SHIFT)) & SSARC_LP_DESC_CTRL0_SV_ORDER_MASK)

#define SSARC_LP_DESC_CTRL0_RT_ORDER_MASK        (0x200000U)
#define SSARC_LP_DESC_CTRL0_RT_ORDER_SHIFT       (21U)
/*! RT_ORDER - Restore order
 *  0b0..Descriptors within the group are processed from start to end
 *  0b1..Descriptors within the group are processed from end to start
 */
#define SSARC_LP_DESC_CTRL0_RT_ORDER(x)          (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL0_RT_ORDER_SHIFT)) & SSARC_LP_DESC_CTRL0_RT_ORDER_MASK)
/*! @} */

/* The count of SSARC_LP_DESC_CTRL0 */
#define SSARC_LP_DESC_CTRL0_COUNT                (16U)

/*! @name DESC_CTRL1 - Descriptor Control1 0 Register..Descriptor Control1 15 Register */
/*! @{ */

#define SSARC_LP_DESC_CTRL1_SW_TRIG_SV_MASK      (0x1U)
#define SSARC_LP_DESC_CTRL1_SW_TRIG_SV_SHIFT     (0U)
/*! SW_TRIG_SV - Software trigger save
 *  0b0..No software save request/software restore request complete
 *  0b1..Request a software save operation/software restore operation in progress
 */
#define SSARC_LP_DESC_CTRL1_SW_TRIG_SV(x)        (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_SW_TRIG_SV_SHIFT)) & SSARC_LP_DESC_CTRL1_SW_TRIG_SV_MASK)

#define SSARC_LP_DESC_CTRL1_SW_TRIG_RT_MASK      (0x2U)
#define SSARC_LP_DESC_CTRL1_SW_TRIG_RT_SHIFT     (1U)
/*! SW_TRIG_RT - Software trigger restore
 *  0b0..No software restore request/software restore request complete
 *  0b1..Request a software restore operation/software restore operation in progress
 */
#define SSARC_LP_DESC_CTRL1_SW_TRIG_RT(x)        (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_SW_TRIG_RT_SHIFT)) & SSARC_LP_DESC_CTRL1_SW_TRIG_RT_MASK)

#define SSARC_LP_DESC_CTRL1_POWER_DOMAIN_MASK    (0x70U)
#define SSARC_LP_DESC_CTRL1_POWER_DOMAIN_SHIFT   (4U)
/*! POWER_DOMAIN
 *  0b000..PGMC_BPC0
 *  0b001..PGMC_BPC1
 *  0b010..PGMC_BPC2
 *  0b011..PGMC_BPC3
 *  0b100..PGMC_BPC4
 *  0b101..PGMC_BPC5
 *  0b110..PGMC_BPC6
 *  0b111..PGMC_BPC7
 */
#define SSARC_LP_DESC_CTRL1_POWER_DOMAIN(x)      (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_POWER_DOMAIN_SHIFT)) & SSARC_LP_DESC_CTRL1_POWER_DOMAIN_MASK)

#define SSARC_LP_DESC_CTRL1_GP_EN_MASK           (0x80U)
#define SSARC_LP_DESC_CTRL1_GP_EN_SHIFT          (7U)
/*! GP_EN - Group Enable
 *  0b0..Group disabled
 *  0b1..Group enabled
 */
#define SSARC_LP_DESC_CTRL1_GP_EN(x)             (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_GP_EN_SHIFT)) & SSARC_LP_DESC_CTRL1_GP_EN_MASK)

#define SSARC_LP_DESC_CTRL1_SV_PRIORITY_MASK     (0xF00U)
#define SSARC_LP_DESC_CTRL1_SV_PRIORITY_SHIFT    (8U)
/*! SV_PRIORITY - Save Priority */
#define SSARC_LP_DESC_CTRL1_SV_PRIORITY(x)       (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_SV_PRIORITY_SHIFT)) & SSARC_LP_DESC_CTRL1_SV_PRIORITY_MASK)

#define SSARC_LP_DESC_CTRL1_RT_PRIORITY_MASK     (0xF000U)
#define SSARC_LP_DESC_CTRL1_RT_PRIORITY_SHIFT    (12U)
/*! RT_PRIORITY - Restore Priority */
#define SSARC_LP_DESC_CTRL1_RT_PRIORITY(x)       (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_RT_PRIORITY_SHIFT)) & SSARC_LP_DESC_CTRL1_RT_PRIORITY_MASK)

#define SSARC_LP_DESC_CTRL1_CPUD_MASK            (0x30000U)
#define SSARC_LP_DESC_CTRL1_CPUD_SHIFT           (16U)
/*! CPUD - CPU Domain */
#define SSARC_LP_DESC_CTRL1_CPUD(x)              (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_CPUD_SHIFT)) & SSARC_LP_DESC_CTRL1_CPUD_MASK)

#define SSARC_LP_DESC_CTRL1_RL_MASK              (0x40000U)
#define SSARC_LP_DESC_CTRL1_RL_SHIFT             (18U)
/*! RL - Read Lock
 *  0b0..Group is unlocked (read access allowed)
 *  0b1..Group is locked (read access not allowed)
 */
#define SSARC_LP_DESC_CTRL1_RL(x)                (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_RL_SHIFT)) & SSARC_LP_DESC_CTRL1_RL_MASK)

#define SSARC_LP_DESC_CTRL1_WL_MASK              (0x80000U)
#define SSARC_LP_DESC_CTRL1_WL_SHIFT             (19U)
/*! WL - Write Lock
 *  0b0..Group is unlocked (write access allowed)
 *  0b1..Group is locked (write access not allowed)
 */
#define SSARC_LP_DESC_CTRL1_WL(x)                (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_WL_SHIFT)) & SSARC_LP_DESC_CTRL1_WL_MASK)

#define SSARC_LP_DESC_CTRL1_DL_MASK              (0x100000U)
#define SSARC_LP_DESC_CTRL1_DL_SHIFT             (20U)
/*! DL - Domain lock
 *  0b0..Unlock
 *  0b1..Lock
 */
#define SSARC_LP_DESC_CTRL1_DL(x)                (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_CTRL1_DL_SHIFT)) & SSARC_LP_DESC_CTRL1_DL_MASK)
/*! @} */

/* The count of SSARC_LP_DESC_CTRL1 */
#define SSARC_LP_DESC_CTRL1_COUNT                (16U)

/*! @name DESC_ADDR_UP - Descriptor Address Up 0 Register..Descriptor Address Up 15 Register */
/*! @{ */

#define SSARC_LP_DESC_ADDR_UP_ADDR_UP_MASK       (0xFFFFFFFFU)
#define SSARC_LP_DESC_ADDR_UP_ADDR_UP_SHIFT      (0U)
/*! ADDR_UP - Address field (High) */
#define SSARC_LP_DESC_ADDR_UP_ADDR_UP(x)         (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_ADDR_UP_ADDR_UP_SHIFT)) & SSARC_LP_DESC_ADDR_UP_ADDR_UP_MASK)
/*! @} */

/* The count of SSARC_LP_DESC_ADDR_UP */
#define SSARC_LP_DESC_ADDR_UP_COUNT              (16U)

/*! @name DESC_ADDR_DOWN - Descriptor Address Down 0 Register..Descriptor Address Down 15 Register */
/*! @{ */

#define SSARC_LP_DESC_ADDR_DOWN_ADDR_DOWN_MASK   (0xFFFFFFFFU)
#define SSARC_LP_DESC_ADDR_DOWN_ADDR_DOWN_SHIFT  (0U)
/*! ADDR_DOWN - Address field (Low) */
#define SSARC_LP_DESC_ADDR_DOWN_ADDR_DOWN(x)     (((uint32_t)(((uint32_t)(x)) << SSARC_LP_DESC_ADDR_DOWN_ADDR_DOWN_SHIFT)) & SSARC_LP_DESC_ADDR_DOWN_ADDR_DOWN_MASK)
/*! @} */

/* The count of SSARC_LP_DESC_ADDR_DOWN */
#define SSARC_LP_DESC_ADDR_DOWN_COUNT            (16U)

/*! @name CTRL - Control Register */
/*! @{ */

#define SSARC_LP_CTRL_DIS_HW_REQ_MASK            (0x8000000U)
#define SSARC_LP_CTRL_DIS_HW_REQ_SHIFT           (27U)
/*! DIS_HW_REQ - Save/Restore request disable
 *  0b0..PGMC save/restore requests enabled
 *  0b1..PGMC save/restore requests disabled
 */
#define SSARC_LP_CTRL_DIS_HW_REQ(x)              (((uint32_t)(((uint32_t)(x)) << SSARC_LP_CTRL_DIS_HW_REQ_SHIFT)) & SSARC_LP_CTRL_DIS_HW_REQ_MASK)

#define SSARC_LP_CTRL_SW_RESET_MASK              (0x80000000U)
#define SSARC_LP_CTRL_SW_RESET_SHIFT             (31U)
/*! SW_RESET - Software reset */
#define SSARC_LP_CTRL_SW_RESET(x)                (((uint32_t)(((uint32_t)(x)) << SSARC_LP_CTRL_SW_RESET_SHIFT)) & SSARC_LP_CTRL_SW_RESET_MASK)
/*! @} */

/*! @name INT_STATUS - Interrupt Status Register */
/*! @{ */

#define SSARC_LP_INT_STATUS_ERR_INDEX_MASK       (0x3FFU)
#define SSARC_LP_INT_STATUS_ERR_INDEX_SHIFT      (0U)
/*! ERR_INDEX - Error Index */
#define SSARC_LP_INT_STATUS_ERR_INDEX(x)         (((uint32_t)(((uint32_t)(x)) << SSARC_LP_INT_STATUS_ERR_INDEX_SHIFT)) & SSARC_LP_INT_STATUS_ERR_INDEX_MASK)

#define SSARC_LP_INT_STATUS_AHB_RESP_MASK        (0xC00U)
#define SSARC_LP_INT_STATUS_AHB_RESP_SHIFT       (10U)
/*! AHB_RESP - AHB Bus response field */
#define SSARC_LP_INT_STATUS_AHB_RESP(x)          (((uint32_t)(((uint32_t)(x)) << SSARC_LP_INT_STATUS_AHB_RESP_SHIFT)) & SSARC_LP_INT_STATUS_AHB_RESP_MASK)

#define SSARC_LP_INT_STATUS_GROUP_CONFLICT_MASK  (0x8000000U)
#define SSARC_LP_INT_STATUS_GROUP_CONFLICT_SHIFT (27U)
/*! GROUP_CONFLICT - Group Conflict field
 *  0b0..No group conflict error
 *  0b1..A group conflict error has occurred
 */
#define SSARC_LP_INT_STATUS_GROUP_CONFLICT(x)    (((uint32_t)(((uint32_t)(x)) << SSARC_LP_INT_STATUS_GROUP_CONFLICT_SHIFT)) & SSARC_LP_INT_STATUS_GROUP_CONFLICT_MASK)

#define SSARC_LP_INT_STATUS_TIMEOUT_MASK         (0x10000000U)
#define SSARC_LP_INT_STATUS_TIMEOUT_SHIFT        (28U)
/*! TIMEOUT - Timeout field
 *  0b0..No timeout event
 *  0b1..A timeout event has occurred
 */
#define SSARC_LP_INT_STATUS_TIMEOUT(x)           (((uint32_t)(((uint32_t)(x)) << SSARC_LP_INT_STATUS_TIMEOUT_SHIFT)) & SSARC_LP_INT_STATUS_TIMEOUT_MASK)

#define SSARC_LP_INT_STATUS_SW_REQ_DONE_MASK     (0x20000000U)
#define SSARC_LP_INT_STATUS_SW_REQ_DONE_SHIFT    (29U)
/*! SW_REQ_DONE - Software Request Done
 *  0b0..No software triggered requests or software triggered request still in progress
 *  0b1..Atleast one software triggered has been complete
 */
#define SSARC_LP_INT_STATUS_SW_REQ_DONE(x)       (((uint32_t)(((uint32_t)(x)) << SSARC_LP_INT_STATUS_SW_REQ_DONE_SHIFT)) & SSARC_LP_INT_STATUS_SW_REQ_DONE_MASK)

#define SSARC_LP_INT_STATUS_AHB_ERR_MASK         (0x40000000U)
#define SSARC_LP_INT_STATUS_AHB_ERR_SHIFT        (30U)
/*! AHB_ERR - AHB Error field
 *  0b0..No AHB error
 *  0b1..An AHB error has occurred
 */
#define SSARC_LP_INT_STATUS_AHB_ERR(x)           (((uint32_t)(((uint32_t)(x)) << SSARC_LP_INT_STATUS_AHB_ERR_SHIFT)) & SSARC_LP_INT_STATUS_AHB_ERR_MASK)

#define SSARC_LP_INT_STATUS_ADDR_ERR_MASK        (0x80000000U)
#define SSARC_LP_INT_STATUS_ADDR_ERR_SHIFT       (31U)
/*! ADDR_ERR - Address Error field
 *  0b0..No address error
 *  0b1..An address error has occurred
 */
#define SSARC_LP_INT_STATUS_ADDR_ERR(x)          (((uint32_t)(((uint32_t)(x)) << SSARC_LP_INT_STATUS_ADDR_ERR_SHIFT)) & SSARC_LP_INT_STATUS_ADDR_ERR_MASK)
/*! @} */

/*! @name HP_TIMEOUT - HP Timeout Register */
/*! @{ */

#define SSARC_LP_HP_TIMEOUT_TIMEOUT_VALUE_MASK   (0xFFFFFFFFU)
#define SSARC_LP_HP_TIMEOUT_TIMEOUT_VALUE_SHIFT  (0U)
/*! TIMEOUT_VALUE - Time out value */
#define SSARC_LP_HP_TIMEOUT_TIMEOUT_VALUE(x)     (((uint32_t)(((uint32_t)(x)) << SSARC_LP_HP_TIMEOUT_TIMEOUT_VALUE_SHIFT)) & SSARC_LP_HP_TIMEOUT_TIMEOUT_VALUE_MASK)
/*! @} */

/*! @name HW_GROUP_PENDING - Hardware Request Pending Register */
/*! @{ */

#define SSARC_LP_HW_GROUP_PENDING_HW_SAVE_PENDING_MASK (0xFFFFU)
#define SSARC_LP_HW_GROUP_PENDING_HW_SAVE_PENDING_SHIFT (0U)
/*! HW_SAVE_PENDING - This field indicates which groups are pending for save from hardware request */
#define SSARC_LP_HW_GROUP_PENDING_HW_SAVE_PENDING(x) (((uint32_t)(((uint32_t)(x)) << SSARC_LP_HW_GROUP_PENDING_HW_SAVE_PENDING_SHIFT)) & SSARC_LP_HW_GROUP_PENDING_HW_SAVE_PENDING_MASK)

#define SSARC_LP_HW_GROUP_PENDING_HW_RESTORE_PENDING_MASK (0xFFFF0000U)
#define SSARC_LP_HW_GROUP_PENDING_HW_RESTORE_PENDING_SHIFT (16U)
/*! HW_RESTORE_PENDING - This field indicates which groups are pending for restore from hardware request */
#define SSARC_LP_HW_GROUP_PENDING_HW_RESTORE_PENDING(x) (((uint32_t)(((uint32_t)(x)) << SSARC_LP_HW_GROUP_PENDING_HW_RESTORE_PENDING_SHIFT)) & SSARC_LP_HW_GROUP_PENDING_HW_RESTORE_PENDING_MASK)
/*! @} */

/*! @name SW_GROUP_PENDING - Software Request Pending Register */
/*! @{ */

#define SSARC_LP_SW_GROUP_PENDING_SW_SAVE_PENDING_MASK (0xFFFFU)
#define SSARC_LP_SW_GROUP_PENDING_SW_SAVE_PENDING_SHIFT (0U)
/*! SW_SAVE_PENDING - This field indicates which groups are pending for save from software request */
#define SSARC_LP_SW_GROUP_PENDING_SW_SAVE_PENDING(x) (((uint32_t)(((uint32_t)(x)) << SSARC_LP_SW_GROUP_PENDING_SW_SAVE_PENDING_SHIFT)) & SSARC_LP_SW_GROUP_PENDING_SW_SAVE_PENDING_MASK)

#define SSARC_LP_SW_GROUP_PENDING_SW_RESTORE_PENDING_MASK (0xFFFF0000U)
#define SSARC_LP_SW_GROUP_PENDING_SW_RESTORE_PENDING_SHIFT (16U)
/*! SW_RESTORE_PENDING - This field indicates which groups are pending for restore from software request */
#define SSARC_LP_SW_GROUP_PENDING_SW_RESTORE_PENDING(x) (((uint32_t)(((uint32_t)(x)) << SSARC_LP_SW_GROUP_PENDING_SW_RESTORE_PENDING_SHIFT)) & SSARC_LP_SW_GROUP_PENDING_SW_RESTORE_PENDING_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SSARC_LP_Register_Masks */


/*!
 * @}
 */ /* end of group SSARC_LP_Peripheral_Access_Layer */


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


#endif  /* PERI_SSARC_LP_H_ */

