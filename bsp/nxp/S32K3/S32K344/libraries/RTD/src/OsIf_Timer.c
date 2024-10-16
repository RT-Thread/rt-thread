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
#include "OsIf.h"
#include "OsIf_Cfg.h"
#include "OsIf_Cfg_TypesDef.h"

#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
/* Defines the Hw Timer functions to be implemented in OS-specific environments */
#include "OsIf_Timer_System.h"
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */

#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
/* API functions to be implemented by user */
#include "OsIf_Timer_Custom.h"
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_TIMER_VENDOR_ID_C                    43
#define OSIF_TIMER_AR_RELEASE_MAJOR_VERSION_C     4
#define OSIF_TIMER_AR_RELEASE_MINOR_VERSION_C     7
#define OSIF_TIMER_AR_RELEASE_REVISION_VERSION_C  0
#define OSIF_TIMER_SW_MAJOR_VERSION_C             5
#define OSIF_TIMER_SW_MINOR_VERSION_C             0
#define OSIF_TIMER_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf_Timer.c file and OsIf.h file are of the same vendor */
#if (OSIF_TIMER_VENDOR_ID_C != OSIF_VENDOR_ID)
    #error "OsIf_Timer.c and OsIf.h have different vendor ids"
#endif
/* Check if OsIf_Timer.c file and OsIf.h file are of the same Autosar version */
#if ((OSIF_TIMER_AR_RELEASE_MAJOR_VERSION_C    != OSIF_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_MINOR_VERSION_C    != OSIF_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_REVISION_VERSION_C != OSIF_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Timer.c and OsIf.h are different"
#endif
/* Check if OsIf_Timer.c file and OsIf.h file are of the same Software version */
#if ((OSIF_TIMER_SW_MAJOR_VERSION_C != OSIF_SW_MAJOR_VERSION) || \
     (OSIF_TIMER_SW_MINOR_VERSION_C != OSIF_SW_MINOR_VERSION) || \
     (OSIF_TIMER_SW_PATCH_VERSION_C != OSIF_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Timer.c and OsIf.h are different"
#endif

/* Check if OsIf_Timer.c file and OsIf_Cfg.h file are of the same vendor */
#if (OSIF_TIMER_VENDOR_ID_C != OSIF_CFG_VENDOR_ID)
    #error "OsIf_Timer.c and OsIf_Cfg.h have different vendor ids"
#endif
/* Check if OsIf_Timer.c file and OsIf_Cfg.h file are of the same Autosar version */
#if ((OSIF_TIMER_AR_RELEASE_MAJOR_VERSION_C    != OSIF_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_MINOR_VERSION_C    != OSIF_CFG_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_REVISION_VERSION_C != OSIF_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Timer.c and OsIf_Cfg.h are different"
#endif
/* Check if OsIf_Timer.c file and OsIf_Cfg.h file are of the same Software version */
#if ((OSIF_TIMER_SW_MAJOR_VERSION_C != OSIF_CFG_SW_MAJOR_VERSION) || \
     (OSIF_TIMER_SW_MINOR_VERSION_C != OSIF_CFG_SW_MINOR_VERSION) || \
     (OSIF_TIMER_SW_PATCH_VERSION_C != OSIF_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Timer.c and OsIf_Cfg.h are different"
#endif

/* Check if OsIf_Timer.c file and OsIf_Cfg_TypesDef.h file are of the same vendor */
#if (OSIF_TIMER_VENDOR_ID_C != OSIF_CFG_TYPESDEF_VENDOR_ID)
    #error "OsIf_Timer.c and OsIf_Cfg_TypesDef.h have different vendor ids"
#endif
/* Check if OsIf_Timer.c file and OsIf_Cfg_TypesDef.h file are of the same Autosar version */
#if ((OSIF_TIMER_AR_RELEASE_MAJOR_VERSION_C    != OSIF_CFG_TYPESDEF_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_MINOR_VERSION_C    != OSIF_CFG_TYPESDEF_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_REVISION_VERSION_C != OSIF_CFG_TYPESDEF_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Timer_System.c and OsIf_Cfg_TypesDef.h are different"
#endif
/* Check if OsIf_Timer.c file and OsIf_Cfg_TypesDef.h file are of the same Software version */
#if ((OSIF_TIMER_SW_MAJOR_VERSION_C != OSIF_CFG_TYPESDEF_SW_MAJOR_VERSION) || \
     (OSIF_TIMER_SW_MINOR_VERSION_C != OSIF_CFG_TYPESDEF_SW_MINOR_VERSION) || \
     (OSIF_TIMER_SW_PATCH_VERSION_C != OSIF_CFG_TYPESDEF_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Timer.c and OsIf_Cfg_TypesDef.h are different"
#endif

#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
/* Check if OsIf_Timer.c file and OsIf_Timer_System.h file are of the same vendor */
#if (OSIF_TIMER_VENDOR_ID_C != OSIF_TIMER_SYSTEM_VENDOR_ID)
    #error "OsIf_Timer.c and OsIf_Timer_System.h have different vendor ids"
#endif
/* Check if OsIf_Timer.c file and OsIf_Timer_System.h file are of the same Autosar version */
#if ((OSIF_TIMER_AR_RELEASE_MAJOR_VERSION_C    != OSIF_TIMER_SYSTEM_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_MINOR_VERSION_C    != OSIF_TIMER_SYSTEM_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_REVISION_VERSION_C != OSIF_TIMER_SYSTEM_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Timer.c and OsIf_Timer_System.h are different"
#endif
/* Check if OsIf_Timer.c file and OsIf_Timer_System.h file are of the same Software version */
#if ((OSIF_TIMER_SW_MAJOR_VERSION_C != OSIF_TIMER_SYSTEM_SW_MAJOR_VERSION) || \
     (OSIF_TIMER_SW_MINOR_VERSION_C != OSIF_TIMER_SYSTEM_SW_MINOR_VERSION) || \
     (OSIF_TIMER_SW_PATCH_VERSION_C != OSIF_TIMER_SYSTEM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Timer.c and OsIf_Timer_System.h are different"
#endif
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */

#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
/* Check if OsIf_Timer.c file and OsIf_Timer_Custom.h file are of the same vendor */
#if (OSIF_TIMER_VENDOR_ID_C != OSIF_TIMER_CUSTOM_VENDOR_ID)
    #error "OsIf_Timer.c and OsIf_Timer_Custom.h have different vendor ids"
#endif
/* Check if OsIf_Timer.c file and OsIf_Timer_Custom.h file are of the same Autosar version */
#if ((OSIF_TIMER_AR_RELEASE_MAJOR_VERSION_C    != OSIF_TIMER_CUSTOM_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_MINOR_VERSION_C    != OSIF_TIMER_CUSTOM_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_TIMER_AR_RELEASE_REVISION_VERSION_C != OSIF_TIMER_CUSTOM_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Timer.c and OsIf_Timer_Custom.h are different"
#endif
/* Check if OsIf_Timer.c file and OsIf_Timer_Custom.h file are of the same Software version */
#if ((OSIF_TIMER_SW_MAJOR_VERSION_C != OSIF_TIMER_CUSTOM_SW_MAJOR_VERSION) || \
     (OSIF_TIMER_SW_MINOR_VERSION_C != OSIF_TIMER_CUSTOM_SW_MINOR_VERSION) || \
     (OSIF_TIMER_SW_PATCH_VERSION_C != OSIF_TIMER_CUSTOM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Timer.c and OsIf_Timer_Custom.h are different"
#endif
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/
#ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE
#if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON)
#if ((STD_ON == OSIF_ENABLE_USER_MODE_SUPPORT) && (defined (MCAL_ENABLE_USER_MODE_SUPPORT)))
    #define Call_OsIf_GetPhysicalCoreIdPrivileged()  \
                OsIf_Trusted_Call_Return(OsIf_GetPhysicalCoreIdPrivileged)
#else
    #define Call_OsIf_GetPhysicalCoreIdPrivileged()  \
                OsIf_GetPhysicalCoreIdPrivileged()
#endif
#endif
#endif

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define BASENXP_START_SEC_CODE
#include "BaseNXP_MemMap.h"

static inline uint32 OsIf_Timer_Dummy_GetCounter(void);
static inline uint32 OsIf_Timer_Dummy_GetElapsed(const uint32 * const CurrentRef);
static inline void OsIf_Timer_Dummy_SetTimerFrequency(uint32 Freq);
static inline uint32 OsIf_Timer_Dummy_MicrosToTicks(uint32 Micros);
#ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE
#if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON)
static uint8 OsIf_GetPhysicalCoreIdPrivileged(void);
#endif /* #ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE */
#endif /* #if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON) */

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#define BASENXP_START_SEC_CODE
#include "BaseNXP_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Timer_Dummy_GetCounter.
 * Description   : Get counter value.
 * 
 *END**************************************************************************/
static inline uint32 OsIf_Timer_Dummy_GetCounter(void)
{
    return 0U;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Timer_Dummy_GetElapsed.
 * Description   : Get elapsed value.
 * 
 *END**************************************************************************/
static inline uint32 OsIf_Timer_Dummy_GetElapsed(const uint32 * const CurrentRef)
{
    (void)CurrentRef;
    return 1U;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Timer_Dummy_SetTimerFrequency.
 * Description   : Set timer frequency.
 * 
 *END**************************************************************************/
static inline void OsIf_Timer_Dummy_SetTimerFrequency(uint32 Freq)
{
    (void)Freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Timer_Dummy_MicrosToTicks.
 * Description   : Convert micro second to ticks.
 * 
 *END**************************************************************************/
static inline uint32 OsIf_Timer_Dummy_MicrosToTicks(uint32 Micros)
{
    return Micros;
}

#ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE
#if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON)
static uint8 OsIf_GetPhysicalCoreIdPrivileged(void)
{
    uint8 coreId = 0U;
#if (OSIF_GET_PHYSICAL_CORE_ID_RUNTIME == STD_ON)
    coreId = ((uint8)(IP_MSCM->CPXNUM & MSCM_CPXNUM_CPN_MASK));
#else
    /* OSIF_PHYSICAL_CORE_ID is generated base on OsIfPhysicalCoreId configuration */
    coreId = OSIF_PHYSICAL_CORE_ID;
#endif

    return coreId;
}
#endif /* #ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE */
#endif /* #if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON) */

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"
/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define BASENXP_START_SEC_CODE
#include "BaseNXP_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Init.
 * Description   : OsIf initialization.
 * @implements OsIf_Init_Activity
 * 
 *END**************************************************************************/
void OsIf_Init(const void* Config)
{
#if (STD_ON == OSIF_DEV_ERROR_DETECT)
    if (Config != NULL_PTR)
    {
    #if defined(USING_OS_AUTOSAROS)
        (void)Det_ReportError(OSIF_MODULE_ID, OSIF_DRIVER_INSTANCE, OSIF_SID_INIT, OSIF_E_INIT_FAILED);
    #else
        OSIF_DEV_ASSERT(FALSE);
    #endif /* defined(USING_OS_AUTOSAROS) */
    }
#else
    (void)Config;
#endif /* (STD_ON == OSIF_DEV_ERROR_DETECT) */

#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
    OsIf_Timer_System_Init();
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */
#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
    OsIf_Timer_Custom_Init();
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_GetCounter.
 * Description   : Get counter value.
 * @implements OsIf_GetCounter_Activity
 * 
 *END**************************************************************************/
uint32 OsIf_GetCounter(OsIf_CounterType SelectedCounter)
{
    uint32 Value = 0U;

    switch (SelectedCounter){
        case OSIF_COUNTER_DUMMY:
            Value = OsIf_Timer_Dummy_GetCounter();
            break;
#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
        case OSIF_COUNTER_SYSTEM:
            Value = OsIf_Timer_System_GetCounter();
            break;
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */
#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
        case OSIF_COUNTER_CUSTOM:
            Value = OsIf_Timer_Custom_GetCounter();
            break;
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */
        default:
            /* impossible */
            break;
    }

    return Value;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_GetElapsed.
 * Description   : Get elapsed value.
 * @implements OsIf_GetElapsed_Activity
 * 
 *END**************************************************************************/
uint32 OsIf_GetElapsed(uint32 * const CurrentRef, OsIf_CounterType SelectedCounter)
{
    uint32 Value = 0U;

    switch (SelectedCounter){
        case OSIF_COUNTER_DUMMY:
            Value = OsIf_Timer_Dummy_GetElapsed(CurrentRef);
            break;
#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
        case OSIF_COUNTER_SYSTEM:
            Value = OsIf_Timer_System_GetElapsed(CurrentRef);
            break;
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */
#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
        case OSIF_COUNTER_CUSTOM:
            Value = OsIf_Timer_Custom_GetElapsed(CurrentRef);
            break;
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */
        default:
            /* impossible */
            break;
    }

    return Value;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_SetTimerFrequency.
 * Description   : Set timer frequency.
 * @implements OsIf_SetTimerFrequency_Activity
 * 
 *END**************************************************************************/
/* @implements OsIf_SetTimerFrequency_Activity */
void OsIf_SetTimerFrequency(uint32 Freq, OsIf_CounterType SelectedCounter)
{
    switch (SelectedCounter){
        case OSIF_COUNTER_DUMMY:
            OsIf_Timer_Dummy_SetTimerFrequency(Freq);
            break;
#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
        case OSIF_COUNTER_SYSTEM:
            OsIf_Timer_System_SetTimerFrequency(Freq);
            break;
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */
#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
        case OSIF_COUNTER_CUSTOM:
            OsIf_Timer_Custom_SetTimerFrequency(Freq);
            break;
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */
        default:
            /* impossible */
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_MicrosToTicks.
 * Description   : Convert micro second to ticks.
 * @implements OsIf_MicrosToTicks_Activity
 * 
 *END**************************************************************************/
uint32 OsIf_MicrosToTicks(uint32 Micros, OsIf_CounterType SelectedCounter)
{
    uint32 Value = 0U;

    switch (SelectedCounter){
        case OSIF_COUNTER_DUMMY:
            Value = OsIf_Timer_Dummy_MicrosToTicks(Micros);
            break;
#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
        case OSIF_COUNTER_SYSTEM:
            Value = OsIf_Timer_System_MicrosToTicks(Micros);
            break;
#endif /* (OSIF_USE_SYSTEM_TIMER == STD_ON) */
#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
        case OSIF_COUNTER_CUSTOM:
            Value = OsIf_Timer_Custom_MicrosToTicks(Micros);
            break;
#endif /* (OSIF_USE_CUSTOM_TIMER == STD_ON) */
        default:
            /* impossible */
            break;
    }

    return Value;
}

#ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE
#if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_GetPhysicalCoreId.
 * Description   : Get physical Core ID
 * @implements OsIf_GetPhysicalCoreId_Activity
 *
 *END**************************************************************************/
uint8 OsIf_GetPhysicalCoreId(void)
{
    uint8 coreId = 0U;

    coreId = Call_OsIf_GetPhysicalCoreIdPrivileged();

    return coreId;
}
#endif /* #ifdef OSIF_GET_PHYSICAL_CORE_ID_ENABLE */
#endif /* #if (OSIF_GET_PHYSICAL_CORE_ID_ENABLE == STD_ON) */

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
