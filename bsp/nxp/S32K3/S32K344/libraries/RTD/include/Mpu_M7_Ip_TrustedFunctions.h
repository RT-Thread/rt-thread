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

#ifndef MPU_M7_IP_TRUSTEDFUNCTIONS_H
#define MPU_M7_IP_TRUSTEDFUNCTIONS_H

/**
*   @file       Mpu_M7_Ip_TrustedFunctions.h
*
*   @defgroup   Mpu_M7_Ip Mpu M7 IPV Driver
*   @ingroup    Platform
*
*   @addtogroup Mpu_M7_Ip
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
#include "Mpu_M7_Ip_Types.h"
#include "Mpu_M7_Ip_Cfg.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_VENDOR_ID                    43
#define CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION     4
#define CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION     7
#define CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION  0
#define CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION             5
#define CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION             0
#define CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mpu_M7_Ip_TypesDef header file are of the same vendor */
#if (CDD_PLATFORM_MPU_M7_IP_TYPES_VENDOR_ID != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_VENDOR_ID)
    #error "Mpu_M7_Ip_TrustedFunctions.h and Mpu_M7_Ip_TypesDef.h have different vendor ids"
#endif
/* Check if current file and Mpu_M7_Ip_TypesDef header file are of the same Autosar version */
#if ((CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mpu_M7_Ip_TrustedFunctions.h and Mpu_M7_Ip_TypesDef.h are different"
#endif
/* Check if current file and Mpu_M7_Ip_TypesDef header file are of the same Software version */
#if ((CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MAJOR_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MINOR_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_SW_PATCH_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mpu_M7_Ip_TrustedFunctions.h and Mpu_M7_Ip_TypesDef.h are different"
#endif

/* Check if current file and Mpu_M7_Ip_Cfg header file are of the same vendor */
#if (CDD_PLATFORM_MPU_M7_IP_CFG_VENDOR_ID != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_VENDOR_ID)
    #error "Mpu_M7_Ip_TrustedFunctions.h and Mpu_M7_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Mpu_M7_Ip_Cfg header file are of the same Autosar version */
#if ((CDD_PLATFORM_MPU_M7_IP_CFG_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_CFG_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_CFG_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mpu_M7_Ip_TrustedFunctions.h and Mpu_M7_Ip_Cfg.h are different"
#endif
/* Check if current file and Mpu_M7_Ip_Cfg header file are of the same Software version */
#if ((CDD_PLATFORM_MPU_M7_IP_CFG_SW_MAJOR_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_CFG_SW_MINOR_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_CFG_SW_PATCH_VERSION != CDD_PLATFORM_MPU_M7_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mpu_M7_Ip_TrustedFunctions.h and Mpu_M7_Ip_Cfg.h are different"
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
#ifdef PLATFORM_IP_ENABLE_MPU_M7
#if (PLATFORM_IP_ENABLE_MPU_M7 == STD_ON)

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

/**
 * @brief         Initializes the Memory Protection Unit general parameters and
 *                region configurations
 *
 * @details       This function is non-reentrant
 *
 * @param[in]     pConfig: pointer to configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
extern void Mpu_M7_Ip_Init_Privileged(const Mpu_M7_Ip_ConfigType * pConfig);

/**
 * @brief         Configures the region selected by u8RegionNum with the data from pUserConfigPtr
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum:    region number
 * @param[in]     pUserConfigPtr: pointer to the region configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
extern void Mpu_M7_Ip_SetRegionConfig_Privileged(uint8 u8RegionNum,
                                                 const Mpu_M7_Ip_RegionConfigType * const pUserConfigPtr
                                                );

/**
 * @brief         Disables the module and resets all region configurations
 *
 * @details       This function is Reentrant
 *
 * @return        void
 *
 * @api
 *
 * @pre
 * */
extern void Mpu_M7_Ip_Deinit_Privileged(void);

/**
 * @brief         Enables or disabled a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     bEnable  : Specifies wheter the region is enabled or disabled
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
extern void Mpu_M7_Ip_EnableRegion_Privileged(uint8 u8RegionNum, boolean bEnable);

/**
 * @brief         Modify the access rights for a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     eRights     : Specifies the new access rights
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
extern void Mpu_M7_Ip_SetAccessRight_Privileged(uint8 u8RegionNum, Mpu_M7_Ip_AccessRightsType eRights);


/**
 * @brief         Retrieve error details
 *
 * @details       This function is Reentrant
 *
 * @param[out]    pErrorDetails : Storage where the data will be saved
 *
 * @return        boolean
 * @retval        TRUE       if an error was present
 * @retval        FALSE      otherwise
 *
 * @api
 *
 * @pre
 *
 * */
extern boolean Mpu_M7_Ip_GetErrorDetails(Mpu_M7_Ip_ErrorDetailsType * pErrorDetails);



#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#endif /* PLATFORM_IP_ENABLE_MPU_M7 == STD_ON */
#endif /* PLATFORM_IP_ENABLE_MPU_M7 */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* MPU_M7_IP_TRUSTEDFUNCTIONS_H */

