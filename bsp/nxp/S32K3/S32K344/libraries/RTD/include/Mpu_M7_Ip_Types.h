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
#ifndef MPU_M7_IP_TYPES_H_
#define MPU_M7_IP_TYPES_H_

/**
*   @file       Mpu_M7_Ip_Types.h
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
*                                        INCLUDE FILES
==================================================================================================*/
#include "Mpu_M7_Ip_Cfg_Defines.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_MPU_M7_IP_TYPES_VENDOR_ID                      43
#define CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MAJOR_VERSION       4
#define CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MINOR_VERSION       7
#define CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_REVISION_VERSION    0
#define CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MAJOR_VERSION               5
#define CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MINOR_VERSION               0
#define CDD_PLATFORM_MPU_M7_IP_TYPES_SW_PATCH_VERSION               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if Mpu_M7_Ip_Types.h and Mpu_M7_Ip_Cfg_Defines.h are of the same vendor */
#if (CDD_PLATFORM_MPU_M7_IP_TYPES_VENDOR_ID != CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_VENDOR_ID)
    #error "Mpu_M7_Ip_Types.h and Mpu_M7_Ip_Cfg_Defines.h have different vendor ids"
#endif
/* Check if Mpu_M7_Ip_Types.h file and Mpu_M7_Ip_Cfg_Defines.h file are of the same Autosar version */
#if ((CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Mpu_M7_Ip_Types.h and Mpu_M7_Ip_Cfg_Defines.h are different"
#endif
/* Check if Mpu_M7_Ip_Types.h file and Mpu_M7_Ip_Cfg_Defines.h file are of the same Software version */
#if ((CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MAJOR_VERSION != CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MINOR_VERSION != CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_TYPES_SW_PATCH_VERSION != CDD_PLATFORM_MPU_M7_IP_CFG_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mpu_M7_Ip_Types.h and Mpu_M7_Ip_Cfg_Defines.h are different"
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
#ifdef PLATFORM_IP_ENABLE_MPU_M7
#if (PLATFORM_IP_ENABLE_MPU_M7 == STD_ON)

/**
* @brief          Enumeration listing the outer and inner cache policies when RASR[TEX] == 0x1XX
*/
/* @implements     Mpu_M7_Ip_CachePolicyType_enum */
typedef enum
{
    MPU_M7_CACHE_POLICY_NO_CACHE                = 0UL,  /*!< Non-cacheable */
    MPU_M7_CACHE_POLICY_W_BACK_WR_ALLOCATE      = 1UL,  /*!< Write-back, write and read allocate */
    MPU_M7_CACHE_POLICY_W_THROUGH_NO_W_ALLOCATE = 2UL,  /*!< Write-through, no write allocate */
    MPU_M7_CACHE_POLICY_W_BACK_NO_W_ALLOCATE    = 3UL   /*!< Write-back, no write allocate */
} Mpu_M7_Ip_CachePolicyType;

/**
* @brief          Enumeration listing the memory and cache attributes when RASR[TEX] == 0x0XX
*/
/* @implements    Mpu_M7_Ip_MemoryType_enum */
typedef enum
{
    MPU_M7_MEM_STRONG_ORDER                 = 0U,  /*!< Strongly ordered */
    MPU_M7_MEM_DEVICE_SHARED                = 1U,  /*!< Shared device */
    MPU_M7_MEM_NORMAL_IO_WR_THROUGH         = 2U,  /*!< Outer and inner write-through, no write allocate */
    MPU_M7_MEM_NORMAL_IO_WR_BACK1           = 3U,  /*!< Outer and inner write-back, no write allocate */
    MPU_M7_MEM_NORMAL_IO_NO_CACHE           = 4U,  /*!< Outer and inner Non-cacheable */
    MPU_M7_MEM_NORMAL_IO_WR_BACK2           = 5U,  /*!< Outer and inner write-back; write and read allocate */
    MPU_M7_MEM_DEVICE_NOSHARE               = 6U,  /*!< Non-shared device */
    MPU_M7_MEM_NORMAL_CACHEABLE             = 7U,  /*!< Normal Memory Cache policy enabled */
    MPU_M7_MEM_NO
} Mpu_M7_Ip_MemoryType;


/**
* @brief          Enumeration listing access permisions
*/
/* @implements    Mpu_M7_Ip_AccessRightsType_enum */
typedef enum
{
    /* Format: X_R_APP
     * X  = 1 bit : Execute Allow or not
     * R  = 1 bit : Reserved
     *APP = 3 bit : Define Privileged & Uprivileged Access Right
     */
    MPU_M7_PRIV_UNPRIV_NONE        = 0x00U,    /*!< 0b00000000U : ---|--- */
    MPU_M7_PRIV_RW_UNPRIV_NONE     = 0x01U,    /*!< 0b00000001U : rw-|--- */
    MPU_M7_PRIV_RWX_UNPRIV_NONE    = 0x11U,    /*!< 0b00010001U : rwx|--- */
    MPU_M7_PRIV_RW_UNPRIV_R        = 0x02U,    /*!< 0b00000010U : rw-|r-- */
    MPU_M7_PRIV_RWX_UNPRIV_RX      = 0x12U,    /*!< 0b00010010U : rwx|r-x */
    MPU_M7_PRIV_RW_UNPRIV_RW       = 0x03U,    /*!< 0b00000011U : rw-|rw- */
    MPU_M7_PRIV_RWX_UNPRIV_RWX     = 0x13U,    /*!< 0b00010011U : rwx|rwx */
    MPU_M7_PRIV_R_UNPRIV_NONE      = 0x05U,    /*!< 0b00000101U : r--|--- */
    MPU_M7_PRIV_RX_UNPRIV_NONE     = 0x15U,    /*!< 0b00010101U : r-x|--- */
    MPU_M7_PRIV_R_UNPRIV_R         = 0x06U,    /*!< 0b00000110U : r--|r-- */
    MPU_M7_PRIV_RX_UNPRIV_RX       = 0x16U,    /*!< 0b00010110U : r-x|r-x */
} Mpu_M7_Ip_AccessRightsType;

/**
* @brief          Enumeration listing the possible access errors
*/
/* @implements    Mpu_M7_Ip_ErrorType_enum */
typedef enum
{
    MPU_M7_MEMMAN_ERROR_INSTRUCTION_ACCESS,  /*! IACCVIOL  Instruction access violation */
    MPU_M7_MEMMAN_ERROR_DATA_ACCESS,         /*! DACCVIOL  Data access violation */
    MPU_M7_MEMMAN_ERROR_STACK,               /*! MUNSTKERR MemManage fault on unstacking for a return from exception */
    MPU_M7_MEMMAN_ERROR_UNSTACK,             /*! MSTKERR   MemManage fault on stacking for exception entry*/
    MPU_M7_MEMMAN_ERROR_FLOATING_POINT,      /*! MLSPERR   MemManage fault during floating point lazy state preservation*/
    MPU_M7_MEMMAN_ERROR_MULTIPLE,            /*! MemManage fault Multiple Errors detected */
    MPU_M7_MEMMAN_ERROR_NONE
} Mpu_M7_Ip_ErrorType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          Configuration structure containing the region configuration
*/
/* @implements    Mpu_M7_Ip_RegionConfigType_struct */
typedef struct
{
    uint8                       u8RegionNum;          /*!< Region number                    */
    uint32                      u32StartAddr;         /*!< Memory region start address      */
    uint32                      u32EndAddr;           /*!< Memory region end address        */
    Mpu_M7_Ip_MemoryType        eMemType;             /*!< Memory Type for region           */
    Mpu_M7_Ip_AccessRightsType  eAccessRight;         /*!< Access permission for region     */
    Mpu_M7_Ip_CachePolicyType   eOuterCachePolicy;    /*!< Outer Cache Policy               */
    Mpu_M7_Ip_CachePolicyType   eInnerCachePolicy;    /*!< Inner Cache Policy               */
    uint8                       u8SubRegMask;         /*!< SubRegion Disable Mask           */
    boolean                     bShareable;           /*!< Enables or disables shareability */
} Mpu_M7_Ip_RegionConfigType;

typedef enum
{
    Cortex_M7_Core0 = 0,
    Cortex_M7_Core1 = 1,
    Cortex_M7_Core2 = 2,
    Cortex_M7_Core3 = 3,
    Cortex_M7_CRS   = 4,
    Cortex_M7_FSS   = 5
} Mpu_M7_Ip_CoreType;

/**
* @brief          IP configuration structure
*/
/* @implements     Mpu_M7_Ip_ConfigType_struct */
typedef struct
{
    Mpu_M7_Ip_CoreType ConfigCore;                                   /*!< Core Id number */
    boolean bDefaultMapEn;                                           /*!< Enables the default memory map background region */
    boolean bEnableRunHFNMI;                                         /*!< Enables use of the MPU when in the hard fault, non-maskable interrupt, and FAULTMASK escalated handlers  */
    boolean bEnMemManageInterrupt;                                   /*!< Enable Memory Manage Fault Exception Handler */
    uint8 u8RegionCnt;                                               /*!< Region Count */
    const Mpu_M7_Ip_RegionConfigType * pRegionConfigArr;             /*!< Region configuration array */
} Mpu_M7_Ip_ConfigType;

/**
* @brief          Structure used to retrieve violation details
*/
/* @implements     Mpu_M7_Ip_ErrorDetailsType_struct */
typedef struct
{
    uint32 u32Address;          /*!< Violation address */
    Mpu_M7_Ip_ErrorType eType;  /*!< Type of violation */
} Mpu_M7_Ip_ErrorDetailsType;

#endif /* PLATFORM_IP_ENABLE_MPU_M7 == STD_ON */
#endif /* PLATFORM_IP_ENABLE_MPU_M7 */
/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* MPU_M7_IP_TYPES_H_ */

