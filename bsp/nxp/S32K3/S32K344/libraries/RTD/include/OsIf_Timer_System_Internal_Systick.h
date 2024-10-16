/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
#ifndef OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "OsIf_Cfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_VENDOR_ID                    43
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_AR_RELEASE_MAJOR_VERSION     4
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_AR_RELEASE_MINOR_VERSION     7
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_AR_RELEASE_REVISION_VERSION  0
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_SW_MAJOR_VERSION             5
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_SW_MINOR_VERSION             0
#define OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf_Timer_System_Internal_Systick.h file and OsIf_Cfg.h file are of the same vendor */
#if (OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_VENDOR_ID != OSIF_CFG_VENDOR_ID)
    #error "OsIf_Timer_System_Internal_Systick.h and OsIf_Cfg.h have different vendor ids"
#endif
/* Check if OsIf_Timer_System_Internal_Systick.h file and OsIf_Cfg.h file are of the same Autosar version */
#if ((OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_AR_RELEASE_MAJOR_VERSION    != OSIF_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_AR_RELEASE_MINOR_VERSION    != OSIF_CFG_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_AR_RELEASE_REVISION_VERSION != OSIF_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Timer_System_Internal_Systick.h and OsIf_Cfg.h are different"
#endif
/* Check if OsIf_Timer_System_Internal_Systick.h file and OsIf_Cfg.h file are of the same Software version */
#if ((OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_SW_MAJOR_VERSION != OSIF_CFG_SW_MAJOR_VERSION) || \
     (OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_SW_MINOR_VERSION != OSIF_CFG_SW_MINOR_VERSION) || \
     (OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK_SW_PATCH_VERSION != OSIF_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Timer_System_Internal_Systick.h and OsIf_Cfg.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
#if defined(OSIF_USE_SYSTICK)
#if (OSIF_USE_SYSTICK == STD_ON)

#define BASENXP_START_SEC_CODE
#include "BaseNXP_MemMap.h"
/*!
 * @brief Initialize SysTick timer
 *
 * This function initializes SysTick timer
 *
 * @param[in] SystemCounterFreq     Systick's frequency
 * @return void
 */
void OsIf_Timer_System_Internal_Init(uint32 SystemCounterFreq);

/*!
 * @brief Get current counter value of SysTick timer
 *
 * This function gets current counter value of SysTick timer
 *
 * @param[in] void
 * @return current counter value
 */
uint32 OsIf_Timer_System_Internal_GetCounter(void);

/*!
 * @brief Get elapsed time
 *
 * This function gets elapsed time
 *
 * @param[in] CurrentRef - pointer to old counter value
 * @return elapsed time
 */
uint32 OsIf_Timer_System_Internal_GetElapsed(uint32 * const CurrentRef);

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"

#endif /* (OSIF_USE_SYSTICK == STD_ON) */
#endif /* defined(OSIF_USE_SYSTICK) */

#ifdef __cplusplus
}
#endif

#endif /* OSIF_TIMER_SYSTEM_INTERNAL_SYSTICK */
