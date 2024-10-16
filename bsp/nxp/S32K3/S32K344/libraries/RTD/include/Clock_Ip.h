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

#ifndef CLOCK_IP_H
#define CLOCK_IP_H

/**
*   @file    Clock_Ip.h
*   @version    5.0.0
*
*   @brief   CLOCK IP driver header file.
*   @details CLOCK IP driver header file.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
*   @{
*/


#if defined(__cplusplus)
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Clock_Ip_Types.h"
#include "Clock_Ip_Cfg.h"
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_VENDOR_ID                       43
#define CLOCK_IP_AR_RELEASE_MAJOR_VERSION        4
#define CLOCK_IP_AR_RELEASE_MINOR_VERSION        7
#define CLOCK_IP_AR_RELEASE_REVISION_VERSION     0
#define CLOCK_IP_SW_MAJOR_VERSION                5
#define CLOCK_IP_SW_MINOR_VERSION                0
#define CLOCK_IP_SW_PATCH_VERSION                0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip.h file and Clock_Ip_Types.h file have same versions */
#if (CLOCK_IP_VENDOR_ID  != CLOCK_IP_TYPES_VENDOR_ID)
    #error "Clock_Ip.h and Clock_Ip_Types.h have different vendor IDs"
#endif

/* Check if Clock_Ip.h file and Clock_Ip_Types.h file are of the same Autosar version */
#if ((CLOCK_IP_AR_RELEASE_MAJOR_VERSION    != CLOCK_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_AR_RELEASE_MINOR_VERSION    != CLOCK_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_AR_RELEASE_REVISION_VERSION != CLOCK_IP_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip.h and Clock_Ip_Types.h are different"
#endif

/* Check if Clock_Ip.h file and Clock_Ip_Types.h file are of the same Software version */
#if ((CLOCK_IP_SW_MAJOR_VERSION != CLOCK_IP_TYPES_SW_MAJOR_VERSION) || \
     (CLOCK_IP_SW_MINOR_VERSION != CLOCK_IP_TYPES_SW_MINOR_VERSION) || \
     (CLOCK_IP_SW_PATCH_VERSION != CLOCK_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Clock_Ip.h and Clock_Ip_Types.h are different"
#endif

/* Check if Clock_Ip.h file and Clock_Ip_Cfg.h file have same versions */
#if (CLOCK_IP_VENDOR_ID  != CLOCK_IP_CFG_VENDOR_ID)
    #error "Clock_Ip.h and Clock_Ip_Cfg.h have different vendor IDs"
#endif

/* Check if Clock_Ip.h file and Clock_Ip_Cfg.h file are of the same Autosar version */
#if ((CLOCK_IP_AR_RELEASE_MAJOR_VERSION    != CLOCK_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_AR_RELEASE_MINOR_VERSION    != CLOCK_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_AR_RELEASE_REVISION_VERSION != CLOCK_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip.h and Clock_Ip_Cfg.h are different"
#endif

/* Check if Clock_Ip.h file and Clock_Ip_Cfg.h file are of the same Software version */
#if ((CLOCK_IP_SW_MAJOR_VERSION != CLOCK_IP_CFG_SW_MAJOR_VERSION) || \
     (CLOCK_IP_SW_MINOR_VERSION != CLOCK_IP_CFG_SW_MINOR_VERSION) || \
     (CLOCK_IP_SW_PATCH_VERSION != CLOCK_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Clock_Ip.h and Clock_Ip_Cfg.h are different"
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

/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"


/*!
 * @brief Set clock configuration according to pre-defined structure.
 *
 * This function sets system to target clock configuration; It sets the
 * clock modules registers for clock mode change.
 *
 * @param[in] Config  Pointer to configuration structure.
 *
 * @return void
 *
 * @note If external clock is used in the target mode, please make sure it is
 * enabled, for example, if the external oscillator is used, please setup correctly.
 */
Clock_Ip_StatusType Clock_Ip_Init(Clock_Ip_ClockConfigType const * Config);

/*!
 * @brief Set the PLL and other MCU specific clock options.
 *
 * This function initializes the PLL and other MCU specific clock options.
 * The clock configuration parameters are provided via the configuration structure.
 *
 * This function shall start the PLL lock procedure (if PLL
 * shall be initialized) and shall return without waiting until the PLL is locked.
 *
 * @param[in] Config  Pointer to configuration structure.
 *
 * @return void
 */
void Clock_Ip_InitClock(Clock_Ip_ClockConfigType const * Config);

/*!
 * @brief Returns the lock status of the PLL.
 *
 * This function returns status of the PLL: undefined, unlocked or locked.
 * This function returns undefined status if this function is called prior
 * to calling of the function Clock_Ip_InitClock
 *
 * @return Status.  Pll lock status
 */
Clock_Ip_PllStatusType Clock_Ip_GetPllStatus(void);

/*!
 * @brief Activates the PLL in MCU clock distribution.
 *
 * This function activates the PLL clock to
 * the MCU clock distribution.
 *
 * This function removes the current clock source
 * (for example internal oscillator clock) from MCU clock distribution.
 *
 * Application layer calls this function after the status of the PLL has been detected as
 * locked by the function Clock_Ip_GetPllStatus.
 *
 * The function Clock_Ip_DistributePll shall return without affecting
 * the MCU hardware if the PLL clock has been automatically activated by the MCU
 * hardware.
 *
 * @return void
 */
void Clock_Ip_DistributePll(void);



/*!
 * @brief Install a clock notifications callback
 *
 * This function installs a callback for
 * reporting notifications from clock driver
 *
 *
 * @param[in] Clock_Ip_NotificationsCallbackType  notifications callback
 *
 * @return void
 *
 * @implements Clock_Ip_InstallNotificationsCallback_Activity
 */
void Clock_Ip_InstallNotificationsCallback(Clock_Ip_NotificationsCallbackType Callback);
/*!
 * @brief Disables a clock monitor.
 *
 * This function disables a clock monitor.
 *
 * @param[in] ClockName  Clock Name.
 *
 * @return void
 */
void Clock_Ip_DisableClockMonitor(Clock_Ip_NameType ClockName);
/*!
 * @brief Disables clock for a peripheral.
 *
 * This function disables clock for a peripheral.
 *
 * @param[in] ClockName  Clock Name.
 *
 * @return void
 */
void Clock_Ip_DisableModuleClock(Clock_Ip_NameType ClockName);

/*!
 * @brief Enables clock for a peripheral.
 *
 * This function enables clock for a peripheral.
 *
 * @param[in] ClockName  Clock Name.
 *
 * @return void
 */
void Clock_Ip_EnableModuleClock(Clock_Ip_NameType ClockName);


#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
void Clock_Ip_SetUserAccessAllowed(void);
  #endif
#endif


#if (defined(CLOCK_IP_GET_FREQUENCY_API))
  #if (CLOCK_IP_GET_FREQUENCY_API == STD_ON)


 /*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in Clock_Ip_NameType.
 * Clock modules must be properly configured before using this function.
 * See features.h for supported clock names for different chip families.
 * The returned value is in Hertz. If frequency is required for a peripheral and the
 * module is not clocked, then 0 Hz frequency is returned.
 *
 * @param[in] ClockName Clock names defined in Clock_Ip_NameType
 * @return frequency    Returned clock frequency value in Hertz
 */
uint64 Clock_Ip_GetClockFrequency(Clock_Ip_NameType ClockName);
  #endif
#endif


#ifdef CLOCK_IP_HAS_FIRC_STDBY_CLOCK_DISABLE
/*!
 * @brief Disables FIRC in STANDBY mode.
 *
 * @param[in] void.
 *
 * @return void
 */
void Clock_Ip_DisableFircInStandby(void);
#endif


#ifdef CLOCK_IP_HAS_FIRC_STDBY_CLOCK_ENABLE
/*!
 * @brief Enables FIRC in STANDBY mode.
 *
 * @param[in] void.
 *
 * @return void
 */
void Clock_Ip_EnableFircInStandby(void);
#endif


#ifdef CLOCK_IP_HAS_SIRC_STDBY_CLOCK_DISABLE
/*!
 * @brief Disables SIRC in STANDBY mode.
 *
 * @param[in] void.
 *
 * @return void
 */
void Clock_Ip_DisableSircInStandby(void);
#endif


#ifdef CLOCK_IP_HAS_SIRC_STDBY_CLOCK_ENABLE
/*!
 * @brief Enables SIRC in STANDBY mode.
 *
 * @param[in] void.
 *
 * @return void
 */
void Clock_Ip_EnableSircInStandby(void);
#endif


/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_IP_H */

