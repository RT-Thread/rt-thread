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

#ifndef CLOCK_IP_PRIVATE_H
#define CLOCK_IP_PRIVATE_H

/**
*   @file    Clock_Ip_Private.h
*   @version    5.0.0
*
*   @brief   CLOCK IP driver private header file.
*   @details CLOCK IP driver private header file.

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

#include "Clock_Ip.h"

#if defined(CLOCK_IP_PLATFORM_SPECIFIC1)
    #include "Clock_Ip_Specific1.h"         /* For S32R45 */
#elif defined(CLOCK_IP_PLATFORM_SPECIFIC2)
    #include "Clock_Ip_Specific2.h"         /* For S32G3XX */
#else
    #include "Clock_Ip_Specific.h"          /* For S32G2XX and other platforms */
#endif

#ifdef CLOCK_IP_DEV_ERROR_DETECT
#if (STD_ON == CLOCK_IP_DEV_ERROR_DETECT)
    #include "Devassert.h"
#endif /* (STD_ON == CLOCK_IP_DEV_ERROR_DETECT) */
#endif /* #ifdef CLOCK_IP_DEV_ERROR_DETECT */

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CLOCK_IP_PRIVATE_VENDOR_ID                    43
#define CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION     4
#define CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION     7
#define CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION  0
#define CLOCK_IP_PRIVATE_SW_MAJOR_VERSION             5
#define CLOCK_IP_PRIVATE_SW_MINOR_VERSION             0
#define CLOCK_IP_PRIVATE_SW_PATCH_VERSION             0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Private.h file and Clock_Ip.h file are of the same Autosar version */
#if ((CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != CLOCK_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != CLOCK_IP_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION != CLOCK_IP_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip_Private.h and Clock_Ip.h are different"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip.h file have same versions */
#if (CLOCK_IP_PRIVATE_VENDOR_ID  != CLOCK_IP_VENDOR_ID)
    #error "Clock_Ip_Private.h and Clock_Ip.h have different vendor IDs"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip.h file are of the same Software version */
#if ((CLOCK_IP_PRIVATE_SW_MAJOR_VERSION != CLOCK_IP_SW_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_MINOR_VERSION != CLOCK_IP_SW_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_PATCH_VERSION != CLOCK_IP_SW_PATCH_VERSION))
    #error "Software Version Numbers of Clock_Ip_Private.h and Clock_Ip.h are different"
#endif

#if defined(CLOCK_IP_PLATFORM_SPECIFIC1)
/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific1.h file are of the same Autosar version */
#if ((CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != CLOCK_IP_SPECIFIC1_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != CLOCK_IP_SPECIFIC1_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION != CLOCK_IP_SPECIFIC1_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip_Private.h and Clock_Ip_Specific1.h are different"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific1.h file have same versions */
#if (CLOCK_IP_PRIVATE_VENDOR_ID  != CLOCK_IP_SPECIFIC1_VENDOR_ID)
    #error "Clock_Ip_Private.h and Clock_Ip_Specific1.h have different vendor IDs"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific1.h file are of the same Software version */
#if ((CLOCK_IP_PRIVATE_SW_MAJOR_VERSION != CLOCK_IP_SPECIFIC1_SW_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_MINOR_VERSION != CLOCK_IP_SPECIFIC1_SW_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_PATCH_VERSION != CLOCK_IP_SPECIFIC1_SW_PATCH_VERSION))
    #error "Software Version Numbers of Clock_Ip_Private.h and Clock_Ip_Specific1.h are different"
#endif

#elif defined(CLOCK_IP_PLATFORM_SPECIFIC2)
/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific2.h file are of the same Autosar version */
#if ((CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != CLOCK_IP_SPECIFIC2_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != CLOCK_IP_SPECIFIC2_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION != CLOCK_IP_SPECIFIC2_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip_Private.h and Clock_Ip_Specific2.h are different"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific2.h file have same versions */
#if (CLOCK_IP_PRIVATE_VENDOR_ID  != CLOCK_IP_SPECIFIC2_VENDOR_ID)
    #error "Clock_Ip_Private.h and Clock_Ip_Specific2.h have different vendor IDs"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific2.h file are of the same Software version */
#if ((CLOCK_IP_PRIVATE_SW_MAJOR_VERSION != CLOCK_IP_SPECIFIC2_SW_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_MINOR_VERSION != CLOCK_IP_SPECIFIC2_SW_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_PATCH_VERSION != CLOCK_IP_SPECIFIC2_SW_PATCH_VERSION))
    #error "Software Version Numbers of Clock_Ip_Private.h and Clock_Ip_Specific2.h are different"
#endif

#else
/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific.h file are of the same Autosar version */
#if ((CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != CLOCK_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != CLOCK_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION != CLOCK_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip_Private.h and Clock_Ip_Specific.h are different"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific.h file have same versions */
#if (CLOCK_IP_PRIVATE_VENDOR_ID  != CLOCK_IP_SPECIFIC_VENDOR_ID)
    #error "Clock_Ip_Private.h and Clock_Ip_Specific.h have different vendor IDs"
#endif

/* Check if Clock_Ip_Private.h file and Clock_Ip_Specific.h file are of the same Software version */
#if ((CLOCK_IP_PRIVATE_SW_MAJOR_VERSION != CLOCK_IP_SPECIFIC_SW_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_MINOR_VERSION != CLOCK_IP_SPECIFIC_SW_MINOR_VERSION) || \
     (CLOCK_IP_PRIVATE_SW_PATCH_VERSION != CLOCK_IP_SPECIFIC_SW_PATCH_VERSION))
    #error "Software Version Numbers of Clock_Ip_Private.h and Clock_Ip_Specific.h are different"
#endif

#endif /* #if defined(CLOCK_IP_PLATFORM_SPECIFIC2) */

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#ifdef CLOCK_IP_DEV_ERROR_DETECT
#if (STD_ON == CLOCK_IP_DEV_ERROR_DETECT)
/* Check if Clock_Ip_Private.h file and Devassert.h file are of the same Autosar version */
#if ((CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION    != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION    != DEVASSERT_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Clock_Ip_Private.h and Devassert.h are different"
#endif
#endif /* (STD_ON == CLOCK_IP_DEV_ERROR_DETECT) */
#endif /* #ifdef CLOCK_IP_DEV_ERROR_DETECT */
#endif /* #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Total number of clocks */
#define CLOCK_IP_NAMES_NO                    CLOCK_IP_FEATURE_NAMES_NO
/* Total number of producer clocks */
#define CLOCK_IP_PRODUCERS_NO                CLOCK_IP_FEATURE_PRODUCERS_NO

/* Define clock features */
#define CLOCK_IP_MODULE_INSTANCE       0U              /* Instance of the module where clock element is implemented. */
#define CLOCK_IP_CALLBACK              1U              /* Actions to be done for different implementations of a clock element. */
#define CLOCK_IP_EXTENSION_INDEX             2U              /* Specific clock feature extension */
#define CLOCK_IP_POWER_MODE_INDEX            3U              /* Index of power mode for multiplexed clock option */
#define CLOCK_IP_SELECTOR_INDEX              4U              /* Selector index. */
#define CLOCK_IP_DIVIDER_INDEX               5U              /* Divider index. */
#define CLOCK_IP_GATE_INDEX                  6U              /* Gate index */
#define CLOCK_IP_PCFS_INDEX                  7U              /* Pcfs index */
#define CLOCK_IP_CMU_INDEX                   8U              /* Cmu index */




/* Maximum number of clock features for each clock name */
#define CLOCK_IP_FEATURES_NO           9U

/* Size of the hardware plls array */
#if CLOCK_IP_NUMBER_OF_HARDWARE_PLL > 0U
    #define CLOCK_IP_HARDWARE_PLL_ARRAY_SIZE  CLOCK_IP_NUMBER_OF_HARDWARE_PLL
#else
    #define CLOCK_IP_HARDWARE_PLL_ARRAY_SIZE  1U
#endif

/* Size of the hardware plls array */
#if CLOCK_IP_NUMBER_OF_HARDWARE_DFS > 0U
    #define CLOCK_IP_HARDWARE_DFS_ARRAY_SIZE  CLOCK_IP_NUMBER_OF_HARDWARE_DFS
#else
    #define CLOCK_IP_HARDWARE_DFS_ARRAY_SIZE  1U
#endif

#if (defined(CLOCK_IP_REGISTER_VALUES_COUNT))
#if (CLOCK_IP_REGISTER_VALUES_COUNT > 0)
#define CLOCK_IP_REGISTER_VALUES_OPTIMIZATION (STD_ON)
#else
#define CLOCK_IP_REGISTER_VALUES_OPTIMIZATION (STD_OFF)
#endif
#else
#define CLOCK_IP_REGISTER_VALUES_OPTIMIZATION (STD_OFF)
#endif

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
    #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
#define CLOCK_IP_IRCOSC_OBJECT                 (1UL << 0U)
#define CLOCK_IP_XOSC_OBJECT                   (1UL << 1U)
#define CLOCK_IP_PLL_OBJECT                    (1UL << 2U)
#define CLOCK_IP_SELECTOR_OBJECT               (1UL << 3U)
#define CLOCK_IP_DIVIDER_OBJECT                (1UL << 4U)
#define CLOCK_IP_DIVIDER_TRIGGER_OBJECT        (1UL << 5U)
#define CLOCK_IP_FRAC_DIV_OBJECT               (1UL << 6U)
#define CLOCK_IP_EXT_SIG_OBJECT                (1UL << 7U)
#define CLOCK_IP_GATE_OBJECT                   (1UL << 8U)
#define CLOCK_IP_PCFS_OBJECT                   (1UL << 9U)
#define CLOCK_IP_CMU_OBJECT                    (1UL << 10U)
    #endif
#endif /* CLOCK_IP_DEV_ERROR_DETECT */

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
  #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
    #define CLOCK_IP_DEV_ASSERT(x)      DevAssert(x)
  #else
    #define CLOCK_IP_DEV_ASSERT(x)
  #endif
#else
    #define CLOCK_IP_DEV_ASSERT(x)
#endif
/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
/*! @brief Clock ip source type.
 */
typedef enum
{
    /* Generic error codes */
    UKNOWN_TYPE                                    = 0x00U,    /*!< Clock path from source to this clock name has at least one selector. */
    IRCOSC_TYPE                                    = 0x01U,    /*!< Source is an internal oscillator. */
    XOSC_TYPE                                      = 0x02U,    /*!< Source is an external oscillator. */
    PLL_TYPE                                       = 0x03U,    /*!< Source is a pll. */
    EXT_CLK_TYPE                                   = 0x04U,    /*!< Source is an external clock. */
    SERDES_TYPE                                    = 0x04U,    /*!< Source is a SERDES. */

} Clock_Ip_ClockNameSourceType;

/*! @brief Clock pll status return codes.
 */
typedef enum
{
    STATUS_PLL_NOT_ENABLED                         = 0x00U,    /*!< Not enabled */
    STATUS_PLL_UNLOCKED                            = 0x01U,    /*!< Unlocked */
    STATUS_PLL_LOCKED                              = 0x02U,    /*!< Locked */

} Clock_Ip_PllStatusReturnType;

/*! @brief Clock dfs status return codes.
 */
typedef enum
{
    STATUS_DFS_NOT_ENABLED                         = 0x00U,    /*!< Not enabled */
    STATUS_DFS_UNLOCKED                            = 0x01U,    /*!< Unlocked */
    STATUS_DFS_LOCKED                              = 0x02U,    /*!< Locked */

} Clock_Ip_DfsStatusType;

/*! @brief Clock ip specific commands
 */
typedef enum
{
    CLOCK_IP_RESERVED_COMMAND                              = 0x00U,    /*!< Reserved command */
    CLOCK_IP_INITIALIZE_PLATFORM_COMMAND                   = 0x01U,    /*!< Specific platform objects */
    CLOCK_IP_INITIALIZE_CLOCK_OBJECTS_COMMAND              = 0x02U,    /*!< Initialize clock objects */
    CLOCK_IP_SET_USER_ACCESS_ALLOWED_COMMAND               = 0x03U,    /*!< User access allowed */
    CLOCK_IP_DISABLE_SAFE_CLOCK_COMMAND                    = 0x04U,    /*!< Disable safe clock */

} Clock_Ip_CommandType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

typedef void (*intOscSetCallback)(Clock_Ip_IrcoscConfigType const * Config);
typedef void (*intOscDisableCallback)(Clock_Ip_NameType IrcoscName);
typedef void (*intOscEnableCallback)(Clock_Ip_IrcoscConfigType const * Config);
typedef struct
{
    intOscSetCallback Set;
    intOscEnableCallback Enable;
    intOscDisableCallback Disable;

}Clock_Ip_IntOscCallbackType;

typedef void (*extOscSetCallback)(Clock_Ip_XoscConfigType const * Config);
typedef void (*extOscResetCallback)(Clock_Ip_XoscConfigType const * Config);
typedef void (*extOscDisableCallback)(Clock_Ip_NameType ExtoscName);
typedef void (*extOscEnableCallback)(Clock_Ip_XoscConfigType const * Config);

typedef struct
{
    extOscResetCallback Reset;
    extOscSetCallback Set;
    extOscSetCallback Complete;
    extOscEnableCallback Enable;

}Clock_Ip_ExtOscCallbackType;


typedef void (*dividerSetCallback)(Clock_Ip_DividerConfigType const * Config);
typedef struct
{
    dividerSetCallback Set;

}Clock_Ip_DividerCallbackType;

typedef void (*dividerConfigureCallback)(Clock_Ip_DividerTriggerConfigType const * Config);
typedef void (*dividerTriggerUpdateCallback)(Clock_Ip_DividerTriggerConfigType const * Config);
typedef struct
{
    dividerConfigureCallback Configure;
    dividerTriggerUpdateCallback TriggerUpdate;

}Clock_Ip_DividerTriggerCallbackType;


typedef void (*fracDivSetCallback)(Clock_Ip_FracDivConfigType const * Config);
typedef void (*fracDivResetCallback)(Clock_Ip_FracDivConfigType const * Config);
typedef Clock_Ip_DfsStatusType (*fracDivCompleteCallback)(Clock_Ip_NameType DfsName);
typedef struct
{
    fracDivResetCallback Reset;
    fracDivSetCallback Set;
    fracDivCompleteCallback Complete;

}Clock_Ip_FracDivCallbackType;

typedef void (*pllSetCallback)(Clock_Ip_PllConfigType const * Config);
typedef void (*pllResetCallback)(Clock_Ip_PllConfigType const * Config);
typedef Clock_Ip_PllStatusReturnType (*pllCompleteCallback)(Clock_Ip_NameType PllName);
typedef void (*pllEnableCallback)(Clock_Ip_PllConfigType const * Config);
typedef void (*pllDisableCallback)(Clock_Ip_NameType PllName);
typedef struct
{
    pllResetCallback Reset;
    pllSetCallback Set;
    pllCompleteCallback Complete;
    pllEnableCallback Enable;
    pllDisableCallback Disable;

}Clock_Ip_PllCallbackType;

typedef void (*selectorSetCallback)(Clock_Ip_SelectorConfigType const * Config);
typedef void (*selectorResetCallback)(Clock_Ip_SelectorConfigType const * Config);
typedef struct
{
    selectorResetCallback Reset;
    selectorSetCallback Set;

}Clock_Ip_SelectorCallbackType;

typedef void (*gateSetCallback)(Clock_Ip_GateConfigType const * Config);
typedef void (*gateUpdateCallback)(Clock_Ip_NameType ClockName, boolean Gate);
typedef struct
{
    gateSetCallback Set;
    gateUpdateCallback Update;

}Clock_Ip_GateCallbackType;

typedef void (*clockMonitorSetCallback)(Clock_Ip_CmuConfigType const * Config, uint32 Index);
typedef void (*clockMonitorResetCallback)(Clock_Ip_CmuConfigType const * Config);
typedef void (*clockMonitorDisableCallback)(Clock_Ip_NameType Name);
typedef void (*clockMonitorEnableCallback)(Clock_Ip_CmuConfigType const * Config);
typedef struct
{
    clockMonitorResetCallback Reset;
    clockMonitorSetCallback Set;
    clockMonitorDisableCallback Disable;
    clockMonitorEnableCallback Enable;

}Clock_Ip_ClockMonitorCallbackType;


typedef void (*pcfsSetCallback)(Clock_Ip_PcfsConfigType const * Config, uint32 Index);
typedef struct
{
    pcfsSetCallback Set;

}Clock_Ip_PcfsCallbackType;


/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_8
#include "Mcu_MemMap.h"

extern const uint8 Clock_Ip_au8XoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8DividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8DividerTriggerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8FractionalDividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8PllCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8SelectorCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8IrcoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8CmuCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8GateCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8PcfsCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT];
extern const uint8 Clock_Ip_au8ClockFeatures[CLOCK_IP_NAMES_NO][CLOCK_IP_FEATURES_NO];

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_8
#include "Mcu_MemMap.h"



/* Clock start constant section data */
#define MCU_START_SEC_CONST_32
#include "Mcu_MemMap.h"

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
    #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
extern const uint32 Clock_Ip_au8ClockNameTypes[CLOCK_IP_NAMES_NO];
    #endif
#endif

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_32
#include "Mcu_MemMap.h"




/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

extern const Clock_Ip_ExtOscCallbackType Clock_Ip_axExtOscCallbacks[CLOCK_IP_XOSC_CALLBACKS_COUNT];

extern const Clock_Ip_DividerCallbackType Clock_Ip_axDividerCallbacks[CLOCK_IP_DIVIDER_CALLBACKS_COUNT];

extern const Clock_Ip_DividerTriggerCallbackType Clock_Ip_axDividerTriggerCallbacks[CLOCK_IP_DIVIDERTRIGGER_CALLBACKS_COUNT];

extern const Clock_Ip_FracDivCallbackType Clock_Ip_axFracDivCallbacks[CLOCK_IP_FRACTIONAL_DIVIDER_CALLBACKS_COUNT];

extern const Clock_Ip_PllCallbackType Clock_Ip_axPllCallbacks[CLOCK_IP_PLL_CALLBACKS_COUNT];

extern const Clock_Ip_NameType Clock_Ip_aeHwPllName[CLOCK_IP_HARDWARE_PLL_ARRAY_SIZE];
extern const Clock_Ip_NameType Clock_Ip_aeHwDfsName[CLOCK_IP_HARDWARE_DFS_ARRAY_SIZE];

extern const Clock_Ip_SelectorCallbackType Clock_Ip_axSelectorCallbacks[CLOCK_IP_SELECTOR_CALLBACKS_COUNT];

extern const Clock_Ip_IntOscCallbackType Clock_Ip_axIntOscCallbacks[CLOCK_IP_IRCOSC_CALLBACKS_COUNT];

extern const Clock_Ip_ClockMonitorCallbackType Clock_Ip_axCmuCallbacks[CLOCK_IP_CMU_CALLBACKS_COUNT];

extern const Clock_Ip_GateCallbackType Clock_Ip_axGateCallbacks[CLOCK_IP_GATE_CALLBACKS_COUNT];

extern const Clock_Ip_PcfsCallbackType Clock_Ip_axPcfsCallbacks[CLOCK_IP_PCFS_CALLBACKS_COUNT];

extern const Clock_Ip_ClockNameSourceType Clock_Ip_aeSourceTypeClockName[CLOCK_IP_PRODUCERS_NO];

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"

#if (CLOCK_IP_CMU_INFO_SIZE > 0U) || defined(CLOCK_IP_CGU_INTERRUPT)
extern const Clock_Ip_ClockConfigType *Clock_Ip_pxConfig;
#endif

#define MCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#include "Mcu_MemMap.h"

#if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 0U

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_CLEARED_8
#include "Mcu_MemMap.h"

extern uint8 Clock_Ip_FreqIds[CLOCK_IP_FEATURE_NAMES_NO];

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_CLEARED_8
#include "Mcu_MemMap.h"

#endif /* CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 0U */
/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef CLOCK_IP_POWER_NOTIFICATIONS
#if (CLOCK_IP_POWER_NOTIFICATIONS == STD_ON)
void Clock_Ip_ClockPowerNotifications(Clock_Ip_PowerModesType PowerMode,
                                    Clock_Ip_PowerNotificationType Notification);
#endif
#endif
void Clock_Ip_ReportClockErrors(Clock_Ip_NotificationType Error,
                                Clock_Ip_NameType ClockName);
void Clock_Ip_SetExternalSignalFrequency(Clock_Ip_NameType SignalName,
                                         uint64 Frequency);
#if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON))
uint64 Clock_Ip_GetFreq(Clock_Ip_NameType ClockName);
void Clock_Ip_SetExternalOscillatorFrequency(Clock_Ip_NameType ExtOscName,
                                             uint64 Frequency);
#endif
#if CLOCK_IP_CMU_INFO_SIZE > 0U
void Clock_Ip_CMU_ClockFailInt(void);
#endif
#if defined(CLOCK_IP_CGU_INTERRUPT)
void Clock_Ip_CGU_ClockDetectInt(void);
#endif
#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES
    void Clock_Ip_SetRamWaitStates(void);
#endif
#ifdef CLOCK_IP_HAS_FLASH_WAIT_STATES
    void Clock_Ip_SetFlashWaitStates(void);
#endif
#if (defined(CLOCK_IP_REGISTER_VALUES_OPTIMIZATION) && (CLOCK_IP_REGISTER_VALUES_OPTIMIZATION == STD_ON))
void Clock_Ip_WriteRegisterValues(const Clock_Ip_RegisterIndexType *Indexes);
#endif
void Clock_Ip_Command(Clock_Ip_ClockConfigType const * Config,
                    Clock_Ip_CommandType Command);
/*!
 * @brief Initializes a starting reference point for timeout
 *
 * @param[out] StartTimeOut    The starting time from which elapsed time is measured
 * @param[out] ElapsedTimeOut  The elapsed time to be passed to Clock_Ip_TimeoutExpired
 * @param[out] TimeoutTicksOut The timeout value (in ticks) to be passed to Clock_Ip_TimeoutExpired
 * @param[in]  TimeoutUs       The timeout value (in microseconds)
 */
void Clock_Ip_StartTimeout(uint32 *StartTimeOut,
                       uint32 *ElapsedTimeOut,
                       uint32 *TimeoutTicksOut,
                       uint32 TimeoutUs);
/*!
 * @brief Checks for timeout condition.
 *
 * @param[in,out] StartTimeInOut    The starting time from which elapsed time is measured
 * @param[in,out] ElapsedTimeInOut  The accumulated elapsed time from the starting time reference
 * @param[in]     TimeoutTicks      The timeout limit (in ticks)
 */
boolean Clock_Ip_TimeoutExpired(uint32 *StartTimeInOut,
                            uint32 *ElapsedTimeInOut,
                            uint32 TimeoutTicks);

/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_IP_PRIVATE_H */

