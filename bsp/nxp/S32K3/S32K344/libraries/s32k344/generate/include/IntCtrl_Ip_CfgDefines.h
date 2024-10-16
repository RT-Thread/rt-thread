/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef INTCTRL_IP_CFG_DEFINES_H_
#define INTCTRL_IP_CFG_DEFINES_H_

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_VENDOR_ID                          43
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MAJOR_VERSION                   5
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

    /* CPU to CPU interrupt (MSI) routing through MSCM */
    #define INT_CTRL_IP_MSI_AVAILABLE                 (STD_ON)
    #include "S32K344_NVIC.h"
#include "S32K344_MSCM.h"
#include "S32K344_SCB.h"
#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
    typedef struct {
        __IO uint32_t IntStatusR;  /**< Interrupt Router CPn Interruptx Status Register; array offset: 0x200; index*0x20; index2*0x8 */
        __O  uint32_t IGR;  /**< Interrupt Router CPn Interruptx Generation Register; array offset: 0x204; index*0x20; index2*0x8 */
    } MSCM_IRCP_IR_Type;

    typedef struct {
        MSCM_IRCP_IR_Type IRCPnIRx[4][4];
    } MSCM_IRCPnIRx_Type;

#define MSCM_IRCPnIRx ((volatile MSCM_IRCPnIRx_Type*)&IP_MSCM->IRCP0ISR0)
#endif
        
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/* Development error detection */
    #define INT_CTRL_MCAL_ARM_MARCH_SMU      (STD_OFF)
    /*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define INT_CTRL_IP_DEV_ERROR_DETECT              (STD_ON)
#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
/* MSI target core count */
#define INT_CTRL_IP_MSI_CORE_CNT                   (2U)
/* MSI vector min */
#define INT_CTRL_IP_DIRECTED_CPU_INT_MIN           (INT0_IRQn)
/* MSI vector max */
#define INT_CTRL_IP_DIRECTED_CPU_INT_MAX           (INT3_IRQn)
#endif

/* VTOR address configuration enable */
#define INT_CTRL_IP_ENABLE_VTOR_CONFIG             (STD_OFF)

/* IP standalone APIs  */
#define INT_CTRL_IP_STANDALONE_APIS               (STD_OFF)
/* First implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MIN                       (INT0_IRQn)
/* Last implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MAX                       (SoC_PLL_IRQn)
/* The interrupt counter value*/
#define INT_CTRL_IP_IRQ_COUNT                     (146U)
/* Arm Cortex M */
#define INT_CTRL_IP_CORTEXM                       (STD_ON)
/* Arm Cortex M0+ */
#define INT_CTRL_IP_CORTEXM0PLUS                  (STD_OFF)
/* Arm Cortex R */
#define INT_CTRL_IP_CORTEXR                       (STD_OFF)
/* Arm Cortex A */
#define INT_CTRL_IP_CORTEXA                       (STD_OFF)

/* Number of nvic priority bits implemented */
#define INT_CTRL_IP_NVIC_PRIO_BITS                (4U)

/*Interrupt Router Shared Peripheral Routing Control Register*/
#define INT_CTRL_IP_ROUTING_CONTROL_REGISTER      (STD_ON)

/* This instruction invalidates the entire instruction cache or caches */
#define INT_CTRL_IP_INVALIDATE_CACHE              (STD_OFF)

/* User mode support */
#define INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT (STD_OFF)

/**
* @brief Interrupt Controller feature enablement.
*/
#define PLATFORM_IP_ENABLE_INT_CTRL (STD_ON)
#endif /* INTCTRL_IP_CFG_DEFINES_H_ */

