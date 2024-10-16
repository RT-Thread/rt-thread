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
/**
*   @file       Clock_Ip_FracDiv.c
*   @version    5.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
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



#include "Clock_Ip_Private.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_FRACDIV_VENDOR_ID_C                      43
#define CLOCK_IP_FRACDIV_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_FRACDIV_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_FRACDIV_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_FRACDIV_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_FRACDIV_SW_MINOR_VERSION_C               0
#define CLOCK_IP_FRACDIV_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_FracDiv.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_FRACDIV_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_FracDiv.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_FracDiv.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_FRACDIV_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_FRACDIV_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_FRACDIV_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_FracDiv.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_FracDiv.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_FRACDIV_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_FRACDIV_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_FRACDIV_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_FracDiv.c and Clock_Ip_Private.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

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
*                                    GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/



/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

static void Clock_Ip_CallbackFracDivEmpty(Clock_Ip_FracDivConfigType const* Config);
static Clock_Ip_DfsStatusType Clock_Ip_CallbackFracDivEmptyComplete(Clock_Ip_NameType DfsName);



/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

static void Clock_Ip_CallbackFracDivEmpty(Clock_Ip_FracDivConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}

static Clock_Ip_DfsStatusType Clock_Ip_CallbackFracDivEmptyComplete(Clock_Ip_NameType DfsName)
{
    (void)DfsName;
    /* No implementation */
    return STATUS_DFS_NOT_ENABLED;
}




/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/



/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/
/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

const Clock_Ip_FracDivCallbackType Clock_Ip_axFracDivCallbacks[CLOCK_IP_FRACTIONAL_DIVIDER_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_CallbackFracDivEmpty,            /* Reset */
        &Clock_Ip_CallbackFracDivEmpty,            /* Set */
        &Clock_Ip_CallbackFracDivEmptyComplete,    /* Complete */
    },


};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
