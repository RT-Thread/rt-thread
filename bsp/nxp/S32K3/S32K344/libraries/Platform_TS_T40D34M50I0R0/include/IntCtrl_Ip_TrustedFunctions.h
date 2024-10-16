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

#ifndef INTCTRL_IP_TRUSTEDFUNCTIONS_H_
#define INTCTRL_IP_TRUSTEDFUNCTIONS_H_

/**
*   @file
*
*   @defgroup   IntCtrl_Ip Interrupt Controller IP
*   @ingroup    Platform
*
*   @addtogroup IntCtrl_Ip
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "IntCtrl_Ip_CfgDefines.h"
#include "Devassert.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_VENDOR_ID                          43
#define CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION                   5
#define CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and IntCtrl_Ip_CfgDefines header file are of the same vendor */
#if (CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_VENDOR_ID != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_VENDOR_ID)
    #error "IntCtrl_Ip_TrustedFunctions.h and IntCtrl_Ip_CfgDefines.h have different vendor ids"
#endif
/* Check if current file and IntCtrl_Ip_CfgDefines header file are of the same Autosar version */
#if ((CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of IntCtrl_Ip_TypesDef.H and IntCtrl_Ip_CfgDefines.h are different"
#endif
/* Check if current file and IntCtrl_Ip_CfgDefines header file are of the same Software version */
#if ((CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of IntCtrl_Ip_TrustedFunctions.h and IntCtrl_Ip_CfgDefines.h are different"
#endif

/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

#ifdef  PLATFORM_IP_ENABLE_INT_CTRL
#if  (PLATFORM_IP_ENABLE_INT_CTRL == STD_ON)
#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

#if ((STD_ON == INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT) && (defined (MCAL_ENABLE_USER_MODE_SUPPORT)))
/**
 * @internal
 * @brief         Installs a handler for an IRQ.
 */
extern void IntCtrl_Ip_InstallHandlerPrivileged(IRQn_Type eIrqNumber,
                               const IntCtrl_Ip_IrqHandlerType pfNewHandler,
                               IntCtrl_Ip_IrqHandlerType* const pfOldHandler);
/**
 * @internal
 * @brief         Enables an interrupt request.
 */                               
extern void IntCtrl_Ip_EnableIrqPrivileged(IRQn_Type eIrqNumber);
/**
 * @internal
 * @brief         Disables an interrupt request.
 */
extern void IntCtrl_Ip_DisableIrqPrivileged(IRQn_Type eIrqNumber);
/**
 * @internal
 * @brief         Sets the priority for an interrupt request.
 */
extern void IntCtrl_Ip_SetPriorityPrivileged(IRQn_Type eIrqNumber, uint8 u8Priority);
/**
 * @internal
 * @brief         Gets the priority for an interrupt request.
 */
extern uint8 IntCtrl_Ip_GetPriorityPrivileged(IRQn_Type eIrqNumber);
/**
 * @internal
 * @brief         Clears the pending flag for an interrupt request.
 */
extern void IntCtrl_Ip_ClearPendingPrivileged(IRQn_Type eIrqNumber);


#if (INT_CTRL_IP_STANDALONE_APIS == STD_ON)
/**
 * @internal
 * @brief         Sets the pending flag for an interrupt request.
 */
extern void IntCtrl_Ip_SetPendingPrivileged(IRQn_Type eIrqNumber);
/**
 * @internal
 * @brief         Gets the pending flag for an interrupt request.
 */
extern boolean IntCtrl_Ip_GetPendingPrivileged(IRQn_Type eIrqNumber);
#if ((INT_CTRL_IP_CORTEXM == STD_ON) && (INT_CTRL_IP_CORTEXM0PLUS == STD_OFF))
/**
 * @internal
 * @brief         Gets the active flag for an interrupt request.
 */    
extern boolean IntCtrl_Ip_GetActivePrivileged(IRQn_Type eIrqNumber);
#endif
#endif
#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
/**
 * @internal
 * @brief         Get directed cpu Interrupt interrupt flag.
 */    
extern void IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged(IRQn_Type eIrqNumber, IntCtrl_Ip_IrqTargetType eCpuTarget);
/**
 * @internal
 * @brief         Clear directed cpu Interrupt interrupt flag.
 */
extern void IntCtrl_Ip_ClearDirectedCpuInterruptPrivileged(IRQn_Type eIrqNumber);
/**
 * @internal
 * @brief         Get directed cpu Interrupt interrupt flag.
 */
extern boolean IntCtrl_Ip_GetDirectedCpuInterruptPrivileged(IRQn_Type eIrqNumber);
#endif

#endif /* INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT == STD_ON */

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#endif /* PLATFORM_IP_ENABLE_INT_CTRL == STD_ON */
#endif /* PLATFORM_IP_ENABLE_INT_CTRL */
#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* INTCTRL_IP_TRUSTEDFUNCTIONS_H_ */

/** @} */
