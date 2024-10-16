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
*   @file       Power_Ip_AEC.c
*   @version    5.0.0
*
*   @brief
*   @brief   POWER driver implementations.
*   @details POWER driver implementations.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_AEC.h"
#include "Power_Ip_Private.h"

#if (defined(POWER_IP_AECRESETCONFIG_API) && (STD_ON == POWER_IP_AECRESETCONFIG_API))
#include "Aec_Ip.h"
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_AEC_VENDOR_ID_C                      43
#define POWER_IP_AEC_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_AEC_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_AEC_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_AEC_SW_MAJOR_VERSION_C               5
#define POWER_IP_AEC_SW_MINOR_VERSION_C               0
#define POWER_IP_AEC_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if (defined(POWER_IP_AECRESETCONFIG_API) && (STD_ON == POWER_IP_AECRESETCONFIG_API))
/* Check if Power_Ip_AEC.c file and Aec_Ip.h file are of the same vendor */
#if (POWER_IP_AEC_VENDOR_ID_C != AEC_IP_VENDOR_ID)
    #error "Power_Ip_AEC.c and Aec_Ip.h have different vendor ids"
#endif

/* Check if Power_Ip_AEC.c file and Aec_Ip.h file are of the same Autosar version */
#if ((POWER_IP_AEC_AR_RELEASE_MAJOR_VERSION_C != AEC_IP_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AEC_AR_RELEASE_MINOR_VERSION_C != AEC_IP_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AEC_AR_RELEASE_REVISION_VERSION_C != AEC_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_AEC.c and Aec_Ip.h are different"
#endif

/* Check if Power_Ip_AEC.c file and Aec_Ip.h file are of the same Software version */
#if ((POWER_IP_AEC_SW_MAJOR_VERSION_C != AEC_IP_SW_MAJOR_VERSION) || \
     (POWER_IP_AEC_SW_MINOR_VERSION_C != AEC_IP_SW_MINOR_VERSION) || \
     (POWER_IP_AEC_SW_PATCH_VERSION_C != AEC_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_AEC.c and Aec_Ip.h are different"
#endif
#endif

/* Check if Power_Ip_AEC.c file and Power_Ip_AEC.h file are of the same vendor */
#if (POWER_IP_AEC_VENDOR_ID_C != POWER_IP_AEC_VENDOR_ID)
    #error "Power_Ip_AEC.c and Power_Ip_AEC.h have different vendor ids"
#endif

/* Check if Power_Ip_AEC.c file and Power_Ip_AEC.h file are of the same Autosar version */
#if ((POWER_IP_AEC_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_AEC_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AEC_AR_RELEASE_MINOR_VERSION_C != POWER_IP_AEC_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AEC_AR_RELEASE_REVISION_VERSION_C != POWER_IP_AEC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_AEC.c and Power_Ip_AEC.h are different"
#endif

/* Check if Power_Ip_AEC.c file and Power_Ip_AEC.h file are of the same Software version */
#if ((POWER_IP_AEC_SW_MAJOR_VERSION_C != POWER_IP_AEC_SW_MAJOR_VERSION) || \
     (POWER_IP_AEC_SW_MINOR_VERSION_C != POWER_IP_AEC_SW_MINOR_VERSION) || \
     (POWER_IP_AEC_SW_PATCH_VERSION_C != POWER_IP_AEC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_AEC.c and Power_Ip_AEC.h are different"
#endif

/* Check if Power_Ip_AEC.c file and Power_Ip_Private.h file are of the same vendor */
#if (POWER_IP_AEC_VENDOR_ID_C != POWER_IP_PRIVATE_VENDOR_ID)
    #error "Power_Ip_AEC.c and Power_Ip_Private.h have different vendor ids"
#endif

/* Check if Power_Ip_AEC.c file and Power_Ip_Private.h file are of the same Autosar version */
#if ((POWER_IP_AEC_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_AEC_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_AEC_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_AEC.c and Power_Ip_Private.h are different"
#endif

/* Check if Power_Ip_AEC.c file and Power_Ip_Private.h file are of the same Software version */
#if ((POWER_IP_AEC_SW_MAJOR_VERSION_C != POWER_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (POWER_IP_AEC_SW_MINOR_VERSION_C != POWER_IP_PRIVATE_SW_MINOR_VERSION) || \
     (POWER_IP_AEC_SW_PATCH_VERSION_C != POWER_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_AEC.c and Power_Ip_Private.h are different"
#endif


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#if (defined(POWER_IP_AECRESETCONFIG_API) && (STD_ON == POWER_IP_AECRESETCONFIG_API))
/**
* @brief            This function configure reset generator (AEC_AE).
* @details          This function configure reset generator (AEC_AE).
*
* @param[in]        ConfigPtr   Pointer to AEC configuration structure.
*
* @return           void
*
*/
void Power_Ip_AEC_Reset_Config(const Power_Ip_AEC_ConfigType * ConfigPtr)
{
    uint32 TmpAe;

    Aec_Ip_SpiRead((uint32)(&(IP_AEC_AE->RSTGEN_CFG)),POWER_IP_DATAWIDTH_16,&TmpAe);
    TmpAe = (uint16)(TmpAe & (uint16)(~AEC_AE_RSTGEN_CFG_RSTGEN_CFG_MASK));
    TmpAe = (uint16)(TmpAe | (uint16)(ConfigPtr->Rstgencfg));
    Aec_Ip_SpiWrite((uint32)(&(IP_AEC_AE->RSTGEN_CFG)),POWER_IP_DATAWIDTH_16,TmpAe);
}
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
