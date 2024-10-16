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
#ifndef OSIF_TIMER_CUSTOM_H
#define OSIF_TIMER_CUSTOM_H

/**
*   @file
*
*   @addtogroup osif_drv
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_TIMER_CUSTOM_VENDOR_ID                    43
#define OSIF_TIMER_CUSTOM_AR_RELEASE_MAJOR_VERSION     4
#define OSIF_TIMER_CUSTOM_AR_RELEASE_MINOR_VERSION     7
#define OSIF_TIMER_CUSTOM_AR_RELEASE_REVISION_VERSION  0
#define OSIF_TIMER_CUSTOM_SW_MAJOR_VERSION             5
#define OSIF_TIMER_CUSTOM_SW_MINOR_VERSION             0
#define OSIF_TIMER_CUSTOM_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Std_Types.h */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_TIMER_CUSTOM_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_TIMER_CUSTOM_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Timer_Custom.h and Std_Types.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

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
#define BASENXP_START_SEC_CODE
#include "BaseNXP_MemMap.h"

/*!
 * @brief Initialize the custom timer.
 *
 * This function initialize the custom timer.
 */
void OsIf_Timer_Custom_Init(void);

/*!
 * @brief Get counter value from custom timer.
 *
 * This function get counter value from custom timer.
 *
 * @return Counter value
 */
uint32 OsIf_Timer_Custom_GetCounter(void);

/*!
 * @brief Get elapsed value from custom timer.
 *
 * This function get elapsed value from custom timer.
 *
 * @param[in] CurrentRef The pointer to current reference point
 * @return Elapsed value
 */
uint32 OsIf_Timer_Custom_GetElapsed(uint32 * const CurrentRef);

/*!
 * @brief Set custom timer frequency.
 *
 * This function set custom timer frequency.
 *
 * @param[in] Freq Frequency value
 */
void OsIf_Timer_Custom_SetTimerFrequency(uint32 Freq);

/*!
 * @brief Convert micro second to ticks based on custom timer frequency.
 *
 * This function Convert micro second to ticks based on custom timer frequency.
 *
 * @param[in] Micros Micro second
 * @return Ticks
 */
uint32 OsIf_Timer_Custom_MicrosToTicks(uint32 Micros);

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* OSIF_TIMER_CUSTOM_H */
