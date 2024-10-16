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
#ifndef OSIF_CFG_TYPESDEF_H
#define OSIF_CFG_TYPESDEF_H

/**
*   @file       OsIf_Cfg_TypesDef.h
*   @version 5.0.0
*
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
#include "OsIf_Cfg.h"

#if STD_ON == OSIF_DEV_ERROR_DETECT
#if (defined(USING_OS_AUTOSAROS) || defined(USING_OS_FREERTOS))
#include "Det.h"
#endif /* (defined(USING_OS_AUTOSAROS) || defined(USING_OS_FREERTOS)) */
#include "Devassert.h"
#define OSIF_DEV_ASSERT(x) DevAssert(x)
#else
#define OSIF_DEV_ASSERT(x) (void)(x)
#endif /* STD_ON == OSIF_DEV_ERROR_DETECT */

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_CFG_TYPESDEF_VENDOR_ID                    43
#define OSIF_CFG_TYPESDEF_AR_RELEASE_MAJOR_VERSION     4
#define OSIF_CFG_TYPESDEF_AR_RELEASE_MINOR_VERSION     7
#define OSIF_CFG_TYPESDEF_AR_RELEASE_REVISION_VERSION  0
#define OSIF_CFG_TYPESDEF_SW_MAJOR_VERSION             5
#define OSIF_CFG_TYPESDEF_SW_MINOR_VERSION             0
#define OSIF_CFG_TYPESDEF_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf_Cfg_TypesDef.h file and OsIf_Cfg.h file are of the same vendor */
#if (OSIF_CFG_TYPESDEF_VENDOR_ID != OSIF_CFG_VENDOR_ID)
    #error "OsIf_Cfg_TypesDef.h and OsIf_Cfg.h have different vendor ids"
#endif
/* Check if OsIf_Cfg_TypesDef.h file and OsIf_Cfg.h file are of the same Autosar version */
#if ((OSIF_CFG_TYPESDEF_AR_RELEASE_MAJOR_VERSION    != OSIF_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_CFG_TYPESDEF_AR_RELEASE_MINOR_VERSION    != OSIF_CFG_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_CFG_TYPESDEF_AR_RELEASE_REVISION_VERSION != OSIF_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Cfg_TypesDef.h and OsIf_Cfg.h are different"
#endif
/* Check if OsIf_Cfg_TypesDef.h file and OsIf_Cfg.h file are of the same Software version */
#if ((OSIF_CFG_TYPESDEF_SW_MAJOR_VERSION != OSIF_CFG_SW_MAJOR_VERSION) || \
     (OSIF_CFG_TYPESDEF_SW_MINOR_VERSION != OSIF_CFG_SW_MINOR_VERSION) || \
     (OSIF_CFG_TYPESDEF_SW_PATCH_VERSION != OSIF_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Cfg_TypesDef.h and OsIf_Cfg.h are different"
#endif

/* Check if OsIf_Cfg_TypesDef.h file and Std_Types.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_CFG_TYPESDEF_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_CFG_TYPESDEF_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Cfg_TypesDef.h and Std_Types.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

#if (STD_ON == OSIF_DEV_ERROR_DETECT)
#if (defined(USING_OS_AUTOSAROS) || defined(USING_OS_FREERTOS))
/* Check if OsIf_Cfg_TypesDef.h file and Det.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_CFG_TYPESDEF_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_CFG_TYPESDEF_AR_RELEASE_MINOR_VERSION != DET_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Cfg_TypesDef.h and Det.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* (defined(USING_OS_AUTOSAROS) || defined(USING_OS_FREERTOS)) */

/* Check if OsIf_Cfg_TypesDef.h file and Devassert.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_CFG_TYPESDEF_AR_RELEASE_MAJOR_VERSION != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_CFG_TYPESDEF_AR_RELEASE_MINOR_VERSION != DEVASSERT_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Cfg_TypesDef.h and Devassert.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* (STD_ON == OSIF_DEV_ERROR_DETECT) */

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* OSIF Service IDs */
#define OSIF_SID_INIT                    (0x01U)
#define OSIF_SID_GETCOUNTER              (0x02U)
#define OSIF_SID_GETELAPSED              (0x03U)
#define OSIF_SID_SETTIMERFREQ            (0x04U)
#define OSIF_SID_US2TICKS                (0x05U)
#define OSIF_SID_RESUMEALLINT            (0x06U)

/* OSIF DET Error Codes */
#define OSIF_E_UNINIT                    (0x01U)
#define OSIF_E_INV_API                   (0x02U)
#define OSIF_E_INV_CORE_IDX              (0x03U)
#define OSIF_E_INIT_FAILED               (0x04U)
#define OSIF_E_INV_CALL                  (0x05U)

/* OSIF Os Application Invalid Or Missing Partition Reference */
#define OSIF_INVALID_PART_ID             (255U)

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/*!
 * @brief OsIF configuration type.
 */
typedef struct
{
    uint32 counterId;
    uint32 counterFrequency;
} OsIf_ConfigType;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/** @} */

#endif /* OSIF_CFG_TYPESDEF_H */
