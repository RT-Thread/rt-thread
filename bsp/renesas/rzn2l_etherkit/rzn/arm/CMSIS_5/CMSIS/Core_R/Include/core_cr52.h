/**************************************************************************//**
 * @file     core_cr52.h
 * @brief    CMSIS Cortex-R52 Core Peripheral Access Layer Header File
 * @date     31. August 2021
 ******************************************************************************/
/*
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates. All Rights Reserved.
 *
 * This file is based on the "\CMSIS\Core\Include\core_armv8mml.h"
 *
 * Changes:
 * Renesas Electronics Corporation on 2021-08-31
 *    - Changed to be related to Cortex-R52 by
 */
/*
 * Copyright (c) 2009-2020 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined ( __ICCARM__ )
 #pragma system_include  /* treat file as system include file for MISRA check */
#endif

#ifndef __CORE_CR52_H_GENERIC
#define __CORE_CR52_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
  \page CMSIS_MISRA_Exceptions  MISRA-C:2004 Compliance Exceptions
  CMSIS violates the following MISRA-C:2004 rules:

   \li Required Rule 8.5, object/function definition in header file.<br>
     Function definitions in header files are used to allow 'inlining'.

   \li Required Rule 18.4, declaration of union type or object of union type: '{...}'.<br>
     Unions are used for effective representation of core registers.

   \li Advisory Rule 19.7, Function-like macro defined.<br>
     Function-like macros are used to allow more efficient code.
 */


/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
/**
  \ingroup Cortex_R52
  @{
 */

#if defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
      #define __FPU_D32        1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __ICCARM__ )
  #if defined __ARMVFP__
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
      #ifndef __ARMVFP_D16__
        #define __FPU_D32      1U
      #endif
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif
#endif

#include "cmsis_version.h"

/* CMSIS CR52 definitions */
#define __CR52_CMSIS_VERSION_MAIN  (__CM_CMSIS_VERSION_MAIN)                  /*!< \deprecated [31:16] CMSIS HAL main version */
#define __CR52_CMSIS_VERSION_SUB   ( __CM_CMSIS_VERSION_SUB)                  /*!< \deprecated [15:0]  CMSIS HAL sub version */
#define __CR52_CMSIS_VERSION       ((__CR52_CMSIS_VERSION_MAIN << 16U) | \
                                    __CR52_CMSIS_VERSION_SUB           )      /*!< \deprecated CMSIS HAL version number */

#define __CORTEX_R                 (52U)                                      /*!< Cortex-R Core                    */

#include "cmsis_compiler.h"               /* CMSIS compiler specific defines */


#ifdef __cplusplus
}
#endif

#endif /* __CORE_CR52_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CR52_H_DEPENDANT
#define __CORE_CR52_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif


/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/*@} end of group Cortex_R52 */



/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
 ******************************************************************************/
/**
  \defgroup CMSIS_core_register Defines and Type Definitions
  \brief Type definitions and defines for Cortex-M processor based devices.
*/

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_GIC  Generic Interrupt Controller (GIC)
  \brief      Type definitions for the GIC Registers
  @{
*/

 /**
  \brief  Structure type to access the Generic Interrupt Controller (GIC) for GICD.
 */
typedef struct
{
  __IOM uint32_t GICD_CTLR;                  /*!< Offset: 0x0000 (R/W)  Distributor Control Register */
  __IM  uint32_t GICD_TYPER;                 /*!< Offset: 0x0004 (R/ )  Interrupt Controller Type Register */
  __IM  uint32_t GICD_IIDR;                  /*!< Offset: 0x0008 (R/ )  Distributor Implementer Identification Register */
        uint32_t RESERVED0[30U];
  __IOM uint32_t GICD_IGROUPR[30U];          /*!< Offset: 0x0084 (R/W)  Interrupt Group Registers 1 - 30 */
        uint32_t RESERVED1[2U];
  __IOM uint32_t GICD_ISENABLER[30U];        /*!< Offset: 0x0104 (R/W)  Interrupt Set-Enable Registers 1 - 30 */
        uint32_t RESERVED2[2U];
  __IOM uint32_t GICD_ICENABLER[30U];        /*!< Offset: 0x0184 (R/W)  Interrupt Clear-Enable Registers 1 - 30 */
        uint32_t RESERVED3[2U];
  __IOM uint32_t GICD_ISPENDR[30U];          /*!< Offset: 0x0204 (R/W)  Interrupt Set-Pending Registers 1 - 30 */
        uint32_t RESERVED4[2U];
  __IOM uint32_t GICD_ICPENDR[30U];          /*!< Offset: 0x0284 (R/W)  Interrupt Clear-Pending Registers 1 - 30 */
        uint32_t RESERVED5[2U];
  __IOM uint32_t GICD_ISACTIVER[30U];        /*!< Offset: 0x0304 (R/W)  Interrupt Set-Active Registers 1 - 30 */
        uint32_t RESERVED6[2U];
  __IOM uint32_t GICD_ICACTIVER[30U];        /*!< Offset: 0x0384 (R/W)  Interrupt Clear-Active Registers 1 - 30 */
        uint32_t RESERVED7[9U];
  __IOM uint32_t GICD_IPRIORITYR[240U];      /*!< Offset: 0x0420 (R/W)  Interrupt Priority Registers 8 - 247 */
        uint32_t RESERVED8[266U];
  __IOM uint32_t GICD_ICFGR[60U];            /*!< Offset: 0x0C08 (R/W)  Interrupt Configuration Registers 2 - 61 */
}  GICD_Type;

 /**
  \brief  Structure type to access the Generic Interrupt Controller (GIC) for GICR for Control target.
 */
typedef struct
{
  __IM  uint32_t GICR_CTLR;                  /*!< Offset: 0x0000 (R/ )  Redistributor Control Register */
  __IM  uint32_t GICR_IIDR;                  /*!< Offset: 0x0004 (R/ )  Redistributor Implementer Identification Register */
  __IM  uint32_t GICR_TYPER[2];              /*!< Offset: 0x0008 (R/ )  Redistributor Type Register */
        uint32_t RESERVED0;
  __IOM uint32_t GICR_WAKER;                 /*!< Offset: 0x0014 (R/W)  Redistributor Wake Register */
}  GICR_CONTROL_TARGET_Type;

 /**
  \brief  Structure type to access the Generic Interrupt Controller (GIC) for GICR for SGI and PPI.
 */
typedef struct
{
        uint32_t RESERVED0[32];
  __IOM uint32_t GICR_IGROUPR0;              /*!< Offset: 0x0080 (R/W)  Interrupt Group Register 0 */
        uint32_t RESERVED1[31];
  __IOM uint32_t GICR_ISENABLER0;            /*!< Offset: 0x0100 (R/W)  Interrupt Set-Enable Register 0 */
        uint32_t RESERVED2[31];
  __IOM uint32_t GICR_ICENABLER0;            /*!< Offset: 0x0180 (R/W)  Interrupt Clear-Enable Register 0 */
        uint32_t RESERVED3[31];
  __IOM uint32_t GICR_ISPENDR0;              /*!< Offset: 0x0200 (R/W)  Interrupt Set-Pending Register 0 */
        uint32_t RESERVED4[31];
  __IOM uint32_t GICR_ICPENDR0;              /*!< Offset: 0x0280 (R/W)  Interrupt Clear-Pending Register 0 */
        uint32_t RESERVED5[31];
  __IOM uint32_t GICR_ISACTIVER0;            /*!< Offset: 0x0300 (R/W)  Interrupt Set-Active Register 0 */
        uint32_t RESERVED6[31];
  __IOM uint32_t GICR_ICACTIVER0;            /*!< Offset: 0x0380 (R/W)  Interrupt Clear-Active Register 0 */
        uint32_t RESERVED7[31];
  __IOM uint32_t GICR_IPRIORITYR[8];         /*!< Offset: 0x0400 (R/W)  Interrupt Priority Registers 0 - 7 */
        uint32_t RESERVED8[504];
  __IM  uint32_t GICR_ICFGR0;                /*!< Offset: 0x0C00 (R/ )  Interrupt Configuration Register 0 */
  __IOM uint32_t GICR_ICFGR1;                /*!< Offset: 0x0C04 (R/W)  Interrupt Configuration Register 1 */
}  GICR_SGI_PPI_Type;

/*@} end of group CMSIS_GIC */


/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */

/* Memory mapping of Core Hardware */
#define GIC0_BASE                     (0x94000000UL)              /*!< GIC0 Base Address */
#define GIC1_BASE                     (0x9C000000UL)              /*!< GIC1 Base Address */
#define GICR_TARGET0_BASE             (0x00100000UL)              /*!< GICR Base Address (for Control target 0) */
#define GICR_TARGET0_SGI_PPI_BASE     (0x00110000UL)              /*!< GICR Base Address (for SGI and PPI target 0) */

#define GICD0                         ((GICD_Type *) GIC0_BASE )   /*!< GICD configuration struct */
#define GICD1                         ((GICD_Type *) GIC1_BASE )   /*!< GICD configuration struct */
#define GICR0_TARGET0_IFREG           ((GICR_CONTROL_TARGET_Type *) (GIC0_BASE + GICR_TARGET0_BASE) )    /*!< GICR configuration struct for Control target 0 */
#define GICR1_TARGET0_IFREG           ((GICR_CONTROL_TARGET_Type *) (GIC1_BASE + GICR_TARGET0_BASE) )    /*!< GICR configuration struct for Control target 0 */
#define GICR0_TARGET0_INTREG          ((GICR_SGI_PPI_Type *) (GIC0_BASE + GICR_TARGET0_SGI_PPI_BASE) )   /*!< GICR configuration struct for SGI and PPI target 0 */
#define GICR1_TARGET0_INTREG          ((GICR_SGI_PPI_Type *) (GIC1_BASE + GICR_TARGET0_SGI_PPI_BASE) )   /*!< GICR configuration struct for SGI and PPI target 0 */

/*@} */


/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */


#if   defined ( __CC_ARM ) /*------------------RealView Compiler -----------------*/
/* ARM armcc specific functions */

#if (__ARMCC_VERSION < 400677)
  #error "Please use ARM Compiler Toolchain V4.0.677 or later!"
#endif


/** \brief  Get CPSR Register

    This function returns the content of the CPSR Register.

    \return               CPSR Register value
 */
__STATIC_INLINE uint32_t __get_CPSR(void)
{
  register uint32_t __regCPSR          __ASM("cpsr");
  return(__regCPSR);
}


#elif (defined (__ICCARM__)) /*---------------- ICC Compiler ---------------------*/


#include <intrinsics.h>


#endif


#ifdef __cplusplus
}
#endif


#endif /* __CORE_CR52_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */
