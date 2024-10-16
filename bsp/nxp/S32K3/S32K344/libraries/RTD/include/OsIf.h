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
#ifndef OSIF_H
#define OSIF_H

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
#include "OsIf_Internal.h"
#include "OsIf_Cfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_VENDOR_ID                    43
#define OSIF_AR_RELEASE_MAJOR_VERSION     4
#define OSIF_AR_RELEASE_MINOR_VERSION     7
#define OSIF_AR_RELEASE_REVISION_VERSION  0
#define OSIF_SW_MAJOR_VERSION             5
#define OSIF_SW_MINOR_VERSION             0
#define OSIF_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf.h file and OsIf_Internal.h file are of the same vendor */
#if (OSIF_VENDOR_ID != OSIF_INTERNAL_VENDOR_ID)
    #error "OsIf.h and OsIf_Internal.h have different vendor ids"
#endif
/* Check if OsIf.h file and OsIf_Internal.h file are of the same Autosar version */
#if ((OSIF_AR_RELEASE_MAJOR_VERSION    != OSIF_INTERNAL_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_AR_RELEASE_MINOR_VERSION    != OSIF_INTERNAL_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_AR_RELEASE_REVISION_VERSION != OSIF_INTERNAL_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf.h and OsIf_Internal.h are different"
#endif
/* Check if OsIf.h file and OsIf_Internal.h file are of the same Software version */
#if ((OSIF_SW_MAJOR_VERSION != OSIF_INTERNAL_SW_MAJOR_VERSION) || \
     (OSIF_SW_MINOR_VERSION != OSIF_INTERNAL_SW_MINOR_VERSION) || \
     (OSIF_SW_PATCH_VERSION != OSIF_INTERNAL_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf.h and OsIf_Internal.h are different"
#endif

/* Check if OsIf.h file and OsIf_Cfg.h file are of the same vendor */
#if (OSIF_VENDOR_ID != OSIF_CFG_VENDOR_ID)
    #error "OsIf.h and OsIf_Cfg.h have different vendor ids"
#endif
/* Check if OsIf.h file and OsIf_Cfg.h file are of the same Autosar version */
#if ((OSIF_AR_RELEASE_MAJOR_VERSION    != OSIF_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_AR_RELEASE_MINOR_VERSION    != OSIF_CFG_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_AR_RELEASE_REVISION_VERSION != OSIF_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf.h and OsIf_Cfg.h are different"
#endif
/* Check if OsIf.h file and OsIf_Cfg.h file are of the same Software version */
#if ((OSIF_SW_MAJOR_VERSION != OSIF_CFG_SW_MAJOR_VERSION) || \
     (OSIF_SW_MINOR_VERSION != OSIF_CFG_SW_MINOR_VERSION) || \
     (OSIF_SW_PATCH_VERSION != OSIF_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf.h and OsIf_Cfg.h are different"
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
/*!
 * @brief OsIf Counter type
 *
 * Counter type.
 *
 * The dummy counter of Osif is meant as a loop-counter timeout mechanism that requirement no
 * additional resource (hardware and software). It was meant to replace the typical loop timeout of decrementing
 * a variable each time the loop was executed until the counter reaches zero. The dummy counter is implemented 
 * in order to have a dummy implementation for the timeout mechanisms used in the drivers without changing the RTD code
 *
   @latexonly
    \begin{left}
    \includegraphics[scale=0.4]{OsIf_CounterDummyType.png}
    \end{left}
   @endlatexonly
 *
 * The system counter of Osif is a loop-counter timeout mechanism that uses real system resources(hardware and software).
 * By using the system counter a typical loop timeout mechanism is used, decrementing a variable each time the loop is executed
 * until the counter reaches zero. The system counter is meant to be used in an OS-specific environment.
 *
   @latexonly
    \begin{left}
    \includegraphics[scale=0.4]{OsIf_CounterSystemType.png}
    \end{left}
   @endlatexonly
 *
 * The custom counter of Osif is meant as a loop-counter timeout mechanism that gives the possibility for the user
 * to define it's own time counter system. The user will have to define his own APIs to cover the necessary functionalities.
 * The necessary APIs to be implemented can be found in the header file OsIf_Timer_Custom.h
 *
   @latexonly
    \begin{left}
    \includegraphics[scale=0.4]{OsIf_CounterCustomType.png}
    \end{left}
   @endlatexonly
 *
 * Enumerator
 *
   @latexonly
    \begin{left}
    \includegraphics[scale=0.3]{OsIf_CounterType.png}
    \end{left}
   @endlatexonly
 */
typedef enum
{
/*! @cond */
    OSIF_COUNTER_DUMMY, /**< dummy counter */
#if (OSIF_USE_SYSTEM_TIMER == STD_ON) 
    OSIF_COUNTER_SYSTEM, /**< system counter */
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */
#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
    OSIF_COUNTER_CUSTOM /**< custom counter */
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */
/*! @endcond */
} OsIf_CounterType;

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
 * @brief Initialize OsIf
 *
 * This function initializes the OsIf module and should be called during startup, before every
 * other intialization other than Mcu.
 *
 */
void OsIf_Init(const void* Config);

/*!
 * @brief Get the current value counter
 *
 * This function returns the current value of the counter.
 *
 * @param[in] SelectedCounter the type of counter to use
 * @return the current value of the counter
 */
uint32 OsIf_GetCounter(OsIf_CounterType SelectedCounter);

/*!
 * @brief Get the elapsed value from a reference point
 *
 * This function returns the delta time in ticks compared to a reference, and updates the reference.
 *
 * @param[inout] CurrentRef reference counter value, updated to current counter value
 * @param[in] SelectedCounter the type of counter to use
 * @return the elapsed time
 */
uint32 OsIf_GetElapsed(uint32 * const CurrentRef, OsIf_CounterType SelectedCounter);

/*!
 * @brief Set a new frequency used for time conversion (microseconds to ticks)
 *
 * This function stores a new timer frequency used for time conversion computations
 *
 * @param[in] Freq the new frequency
 * @param[in] SelectedCounter the type of counter to use
 */
void OsIf_SetTimerFrequency(uint32 Freq, OsIf_CounterType SelectedCounter);

/*!
 * @brief Convert microseconds to ticks
 *
 * This function converts a value from microsecond units to ticks units.
 *
 * @param[in] Micros microseconds value
 * @param[in] SelectedCounter the type of counter to use
 * @return the equivalent value in ticks
 */
uint32 OsIf_MicrosToTicks(uint32 Micros, OsIf_CounterType SelectedCounter);

/*!
 * @brief Get physical core id
 *
 * This function gets physical core id.
 *
 * @param[in] void
 * @return the physical core id
 */
#ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE
#if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON)
uint8 OsIf_GetPhysicalCoreId(void);
#endif /* #ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE */
#endif /* #if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON) */

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* OSIF_H */
