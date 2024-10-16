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
*   @file       OsIf_Cfg.c
*   @version 5.0.0
*
*
*   @addtogroup OSIF_DRIVER
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
#include "OsIf_Cfg.h"
#include "OsIf_Cfg_TypesDef.h"

#if defined(USING_OS_AUTOSAROS)
#include "Os.h"
#endif /* defined(USING_OS_AUTOSAROS) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_CFG_VENDOR_ID_C                    43
#define OSIF_CFG_AR_RELEASE_MAJOR_VERSION_C     4
#define OSIF_CFG_AR_RELEASE_MINOR_VERSION_C     7
#define OSIF_CFG_AR_RELEASE_REVISION_VERSION_C  0
#define OSIF_CFG_SW_MAJOR_VERSION_C             5
#define OSIF_CFG_SW_MINOR_VERSION_C             0
#define OSIF_CFG_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf_Cfg.c file and OsIf_Cfg.h file are of the same vendor */
#if (OSIF_CFG_VENDOR_ID_C != OSIF_CFG_VENDOR_ID)
    #error "OsIf_Cfg.c and OsIf_Cfg.h have different vendor ids"
#endif
/* Check if OsIf_Cfg.c file and OsIf_Cfg.h file are of the same Autosar version */
#if ((OSIF_CFG_AR_RELEASE_MAJOR_VERSION_C    != OSIF_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_CFG_AR_RELEASE_MINOR_VERSION_C    != OSIF_CFG_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_CFG_AR_RELEASE_REVISION_VERSION_C != OSIF_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Cfg.c and OsIf_Cfg.h are different"
#endif
/* Check if OsIf_Cfg.c file and OsIf_Cfg.h file are of the same Software version */
#if ((OSIF_CFG_SW_MAJOR_VERSION_C != OSIF_CFG_SW_MAJOR_VERSION) || \
     (OSIF_CFG_SW_MINOR_VERSION_C != OSIF_CFG_SW_MINOR_VERSION) || \
     (OSIF_CFG_SW_PATCH_VERSION_C != OSIF_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Cfg.c and OsIf_Cfg.h are different"
#endif

/* Check if OsIf_Cfg.c file and OsIf_Cfg_TypesDef.h file are of the same vendor */
#if (OSIF_CFG_VENDOR_ID_C != OSIF_CFG_TYPESDEF_VENDOR_ID)
    #error "OsIf_Cfg.c and OsIf_Cfg_TypesDef.h have different vendor ids"
#endif
/* Check if OsIf_Cfg.c file and OsIf_Cfg_TypesDef.h file are of the same Autosar version */
#if ((OSIF_CFG_AR_RELEASE_MAJOR_VERSION_C    != OSIF_CFG_TYPESDEF_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_CFG_AR_RELEASE_MINOR_VERSION_C    != OSIF_CFG_TYPESDEF_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_CFG_AR_RELEASE_REVISION_VERSION_C != OSIF_CFG_TYPESDEF_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Cfg.c and OsIf_Cfg_TypesDef.h are different"
#endif
/* Check if OsIf_Cfg.c file and OsIf_Cfg_TypesDef.h file are of the same Software version */
#if ((OSIF_CFG_SW_MAJOR_VERSION_C != OSIF_CFG_TYPESDEF_SW_MAJOR_VERSION) || \
     (OSIF_CFG_SW_MINOR_VERSION_C != OSIF_CFG_TYPESDEF_SW_MINOR_VERSION) || \
     (OSIF_CFG_SW_PATCH_VERSION_C != OSIF_CFG_TYPESDEF_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Cfg.c and OsIf_Cfg_TypesDef.h are different"
#endif

#if defined(USING_OS_AUTOSAROS)
/* Check if OsIf_Cfg.c file and Os.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_CFG_AR_RELEASE_MAJOR_VERSION_C != OS_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_CFG_AR_RELEASE_MINOR_VERSION_C != OS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Cfg.c and Os.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* defined(USING_OS_AUTOSAROS) */

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */

