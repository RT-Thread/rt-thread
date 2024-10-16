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

#ifndef INTCTRL_IP_TYPESDEF_H_
#define INTCTRL_IP_TYPESDEF_H_

/**
*   @file
*
*   @addtogroup IntCtrl_Ip
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "IntCtrl_Ip_CfgDefines.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTCTRL_IP_TYPESDEF_VENDOR_ID                          43
#define CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_MAJOR_VERSION                   5
#define CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef  PLATFORM_IP_ENABLE_INT_CTRL
#if  (PLATFORM_IP_ENABLE_INT_CTRL == STD_ON)
/* Check if current file and IntCtrl_Ip_CfgDefines header file are of the same vendor */
#if (CDD_PLATFORM_INTCTRL_IP_TYPESDEF_VENDOR_ID != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_VENDOR_ID)
    #error "IntCtrl_Ip_TypesDef.h and IntCtrl_Ip_CfgDefines.h have different vendor ids"
#endif
/* Check if current file and IntCtrl_Ip_CfgDefines header file are of the same Autosar version */
#if ((CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of IntCtrl_Ip_TypesDef.h and IntCtrl_Ip_CfgDefines.h are different"
#endif
/* Check if current file and Fls header file are of the same Software version */
#if ((CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_MAJOR_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_MINOR_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_PATCH_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of IntCtrl_Ip_TypesDef.h and IntCtrl_Ip_CfgDefines.h are different"
#endif
#endif /* PLATFORM_IP_ENABLE_INT_CTRL == STD_ON */
#endif /* PLATFORM_IP_ENABLE_INT_CTRL */

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
#ifdef  PLATFORM_IP_ENABLE_INT_CTRL
#if  (PLATFORM_IP_ENABLE_INT_CTRL == STD_ON)
/**
* @brief          Interrupt handler type.
* @implements     IntCtrl_Ip_IrqHandlerType_typedef
*/
typedef void (*IntCtrl_Ip_IrqHandlerType)(void);

 
/**
* @brief          Structure storing the state and priority configuration for an interrupt request.
* @implements     IntCtrl_Ip_IrqConfigType_typedef
*/
typedef struct
{
    /** @brief Interrupt number */
    IRQn_Type eIrqNumber;
    /** @brief Interrupt state (enabled/disabled) */
    boolean bIrqEnabled;
    /** @brief Interrupt priority */
    uint8 u8IrqPriority;
    /** @brief Interrupt handler */
    IntCtrl_Ip_IrqHandlerType pfHandler;
}IntCtrl_Ip_IrqConfigType;

/**
* @brief          Structure storing the list of state configurations for all configured interrupts.
* @implements     IntCtrl_Ip_CtrlConfigType_typedef
*/
typedef struct
{
    /** @brief Number of configured interrupts */
    uint32 u32ConfigIrqCount;
#if (INT_CTRL_IP_ENABLE_VTOR_CONFIG == STD_ON)
    /** @brief  Vector Table address */
    uint32 u32VectorTableAddress;
#endif /* INT_CTRL_IP_ENABLE_VTOR_CONFIG */
    /** @brief List of interrupts configurations */
    const IntCtrl_Ip_IrqConfigType *aIrqConfig;
}IntCtrl_Ip_CtrlConfigType;

/**
* @brief          Enumeration listing the possible error codes returned by IntCtrl_Ip API.
* @implements     IntCtrl_Ip_StatusType_typedef
*/
typedef enum
{
    /** @brief Status SUCCESS */
    INTCTRL_IP_STATUS_SUCCESS = 0U,
    /** @brief Status ERROR */
    INTCTRL_IP_STATUS_ERROR   = 1U
}IntCtrl_Ip_StatusType;


#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
/**
* @brief          Enumeration listing the available target cores for an inter-core interrupt.
* @implements     IntCtrl_Ip_IrqTargetType_typedef
*/
typedef enum
{
    /** @brief Interrupt request targeted to the same core that triggers it */
    INTCTRL_IP_TARGET_SELF       = -2,
    /** @brief Interrupt request targeted to all the other cores */
    INTCTRL_IP_TARGET_OTHERS     = -1,
    /** @brief Interrupt request targeted to core 0 */
    INTCTRL_IP_TARGET_CP0        =  0,
    /** @brief Interrupt request targeted to core 1 */
    INTCTRL_IP_TARGET_CP1        =  1,
    #if (INT_CTRL_IP_MSI_CORE_CNT > 2)
    /** @brief Interrupt request targeted to core 2 */
    INTCTRL_IP_TARGET_CP2        =  2,
    #endif
    #if (INT_CTRL_IP_MSI_CORE_CNT > 3)
    /** @brief Interrupt request targeted to core 3 */
    INTCTRL_IP_TARGET_CP3        =  3,
    #endif
    #if (INT_CTRL_IP_MSI_CORE_CNT > 4)
    /** @brief Interrupt request targeted to core 4 */
    INTCTRL_IP_TARGET_CP4        =  4,
    #endif
    #if (INT_CTRL_IP_MSI_CORE_CNT > 5)
    /** @brief Interrupt request targeted to core 5 */
    INTCTRL_IP_TARGET_CP5        =  5,
    #endif
    #if (INT_CTRL_IP_MSI_CORE_CNT > 6)
    /** @brief Interrupt request targeted to core 6 */
    INTCTRL_IP_TARGET_CP6        =  6
    #endif
} IntCtrl_Ip_IrqTargetType;
#endif /* (INT_CTRL_IP_MSI_AVAILABLE == STD_ON) */

#endif /* INTCTRL_IP_TYPESDEF_H_ */
#endif /* PLATFORM_IP_ENABLE_INT_CTRL == STD_ON */
#endif /* PLATFORM_IP_ENABLE_INT_CTRL */

/** @} */
