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

#ifndef INTCTRL_IP_H_
#define INTCTRL_IP_H_

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
#include "IntCtrl_Ip_Cfg.h"
#include "Mcal.h"
#include "Devassert.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTCTRL_IP_VENDOR_ID                          43
#define CDD_PLATFORM_INTCTRL_IP_SW_MAJOR_VERSION                   5
#define CDD_PLATFORM_INTCTRL_IP_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef  PLATFORM_IP_ENABLE_INT_CTRL
#if  (PLATFORM_IP_ENABLE_INT_CTRL == STD_ON)
/* Check if current file and IntCtrl_Ip_Cfg header file are of the same vendor */
#if (CDD_PLATFORM_INTCTRL_IP_VENDOR_ID != CDD_PLATFORM_INTCTRL_IP_CFG_VENDOR_ID)
    #error "IntCtrl_Ip.h and IntCtrl_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and IntCtrl_Ip_Cfg header file are of the same Autosar version */
#if ((CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of IntCtrl_Ip.h and IntCtrl_Ip_Cfg.h are different"
#endif
/* Check if current file and IntCtrl_Ip_Cfg header file are of the same Software version */
#if ((CDD_PLATFORM_INTCTRL_IP_SW_MAJOR_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_SW_MINOR_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_INTCTRL_IP_SW_PATCH_VERSION != CDD_PLATFORM_INTCTRL_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of IntCtrl_Ip.h and IntCtrl_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of IntCtrl_Ip.h and Mcal.h are different"
    #endif
#endif
#endif /* PLATFORM_IP_ENABLE_INT_CTRL == STD_ON */
#endif /* PLATFORM_IP_ENABLE_INT_CTRL */

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

/**
 * @brief         Initializes the configured interrupts at interrupt controller level.
 *
 * @details       This function is non-reentrant and initializes the interrupts.
 *
 * @param[in]     pIntCtrlCtrlConfig: pointer to configuration structure for interrupts.
 * @return        IntCtrl_Ip_StatusType: error code.
 *
 * @api
 *
 * */
IntCtrl_Ip_StatusType IntCtrl_Ip_Init(const IntCtrl_Ip_CtrlConfigType *pIntCtrlCtrlConfig);


/**
 * @brief         Installs a handler for an IRQ.
 *
 * @details       This function is non-reentrant; it installs an new ISR for an interrupt line.
 * @note          This function works only when the interrupt vector table resides in RAM.
 *
 * @param[in]     eIrqNumber: interrupt number.
 * @param[in]     pfNewHandler: function pointer for the new handler.
 * @param[out]    pfOldHandler: stores the address of the old interrupt handler.
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_InstallHandler(IRQn_Type eIrqNumber,
                               const IntCtrl_Ip_IrqHandlerType pfNewHandler,
                               IntCtrl_Ip_IrqHandlerType* const pfOldHandler);

/**
 * @brief         Enables an interrupt request.
 *
 * @details       This function is non-reentrant; it enables the interrupt request at
 *                interrupt controller level.
 *
 * @param[in]     eIrqNumber: interrupt number to be enabled.
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_EnableIrq(IRQn_Type eIrqNumber);

/**
 * @brief         Disables an interrupt request.
 *
 * @details       This function is non-reentrant; it disables the interrupt request at
 *                interrupt controller level.
 *
 * @param[in]     eIrqNumber: interrupt number to be disabled.
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_DisableIrq(IRQn_Type eIrqNumber);

/**
 * @brief         Sets the priority for an interrupt request.
 *
 * @details       This function is non-reentrant; it sets the priority for the
 *                interrupt request.
 *
 * @param[in]     eIrqNumber: interrupt number for which the priority is set.
 * @param[in]     u8Priority: the priority to be set.
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_SetPriority(IRQn_Type eIrqNumber, uint8 u8Priority);

/**
 * @brief         Gets the priority for an interrupt request.
 *
 * @details       This function is non-reentrant; it retrieves the priority for the
 *                interrupt request.
 *
 * @param[in]     eIrqNumber: interrupt number for which the priority is set.
 * @return        uint8: the priority of the interrupt.
 *
 * @api
 *
 * */
uint8 IntCtrl_Ip_GetPriority(IRQn_Type eIrqNumber);

/**
 * @brief         Clears the pending flag for an interrupt request.
 *
 * @details       This function is reentrant; it clears the pending flag for the
 *                interrupt request.
 *
 * @param[in]     eIrqNumber: interrupt number for which the pending flag is cleared.
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_ClearPending(IRQn_Type eIrqNumber);


#if (INT_CTRL_IP_STANDALONE_APIS == STD_ON)
/**
 * @brief         Sets the pending flag for an interrupt request.
 *
 * @details       This function is reentrant; it sets the pending flag for the
 *                interrupt request.
 *
 * @param[in]     eIrqNumber: interrupt number for which the pending flag is set.
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_SetPending(IRQn_Type eIrqNumber);

/**
 * @brief         Gets the pending flag for an interrupt request.
 *
 * @details       This function is reentrant; it retrieves the pending flag for the
 *                interrupt request.
 *
 * @param[in]     eIrqNumber: interrupt number for which the pending flag is returned.
 * @return        boolean: TRUE - pending flag set, FALSE - pending flag cleared.
 *
 * @api
 *
 * */
boolean IntCtrl_Ip_GetPending(IRQn_Type eIrqNumber);

/**
 * @brief         Gets the active flag for an interrupt request.
 *
 * @details       This function is reentrant; it retrieves the active flag for the
 *                interrupt request.
 *
 * @param[in]     eIrqNumber: interrupt number for which the active flag is returned.
 * @return        boolean: TRUE - active flag set, FALSE - active flag cleared.
 *
 * @api
 *
 * */
#if !defined(S32K116) && !defined(S32K118)
boolean IntCtrl_Ip_GetActive(IRQn_Type eIrqNumber);
#endif
#endif /* INT_CTRL_IP_STANDALONE_APIS*/

#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
/**
 * @brief         Clear directed cpu Interrupt interrupt flag.
 *
 * @details       This function is non-reentrant; it is provided for clearing directed cpu Interrupt interrupt flag.
 *
 * @param[in]     eIrqNumber: interrupt number
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_ClearDirectedCpuInterrupt(IRQn_Type eIrqNumber);

/**
 * @brief         Get directed cpu Interrupt interrupt flag.
 *
 * @details       This function is non-reentrant; it is provided for getting directed cpu Interrupt interrupt flag.
 *
 * @param[in]     eIrqNumber: interrupt number
 * @return        boolean: TRUE - flag set, FALSE - flag cleared.
 *
 * @api
 *
 * */
boolean IntCtrl_Ip_GetDirectedCpuInterrupt(IRQn_Type eIrqNumber);

/**
 * @brief         Generates an interrupt request to a CPU target.
 *
 * @details       This function is non-reentrant; it is provided for generating a directed interrupt
 *                to a CPU defined by target parameter.
 *
 * @param[in]     eIrqNumber: interrupt number to be triggered.
 * @param[in]     eCpuTarget: target core for the interrupt request.
 * @return        void.
 *
 * @api
 *
 * */
void IntCtrl_Ip_GenerateDirectedCpuInterrupt(IRQn_Type eIrqNumber, IntCtrl_Ip_IrqTargetType eCpuTarget);
#endif
#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"
#endif /* PLATFORM_IP_ENABLE_INT_CTRL == STD_ON */
#endif /* PLATFORM_IP_ENABLE_INT_CTRL */

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* INTCTRL_IP_H_ */

/** @} */
