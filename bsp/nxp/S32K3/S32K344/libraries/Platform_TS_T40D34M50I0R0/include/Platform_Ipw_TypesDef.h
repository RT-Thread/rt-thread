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

#ifndef IPW_PLATFORM_IPW_TYPESDEF_H_
#define IPW_PLATFORM_IPW_TYPESDEF_H_

/**
*   @file
*
*   @internal
*   @addtogroup Platform_Ipw
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "Platform_CfgDefines.h"
#if (PLATFORM_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif
#if (PLATFORM_ENABLE_INT_CTRL == STD_ON)
    #include "IntCtrl_Ip_TypesDef.h"
#endif
#if (PLATFORM_SYS_CFG == STD_ON)
    #include "System_Ip_CfgDefines.h"
#endif
#if (PLATFORM_INT_MONITOR == STD_ON)
    #include "Intm_Ip_CfgDefines.h"
#endif
#if (PLATFORM_ENABLE_MPU_M7 == STD_ON)
    #include "Mpu_M7_Ip_Types.h"
#endif
/*==================================================================================================
*                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CDD_PLATFORM_IPW_TYPESDEF_VENDOR_ID                       43
#define CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MAJOR_VERSION        4
#define CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MINOR_VERSION        7
#define CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_REVISION_VERSION     0
#define CDD_PLATFORM_IPW_TYPESDEF_SW_MAJOR_VERSION                5
#define CDD_PLATFORM_IPW_TYPESDEF_SW_MINOR_VERSION                0
#define CDD_PLATFORM_IPW_TYPESDEF_SW_PATCH_VERSION                0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Platform_CfgDefines header file are of the same vendor */
#if (CDD_PLATFORM_IPW_TYPESDEF_VENDOR_ID != CDD_PLATFORM_CFGDEFINES_VENDOR_ID)
    #error "Platform_Ipw_TypesDef.h and Platform_CfgDefines.h have different vendor ids"
#endif
/* Check if current file and Platform_CfgDefines header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_CFGDEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_CFGDEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_CFGDEFINES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw_TypesDef.h and Platform_CfgDefines.h are different"
#endif

/* Check if current file and Platform_CfgDefines header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_SW_MAJOR_VERSION != CDD_PLATFORM_CFGDEFINES_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_MINOR_VERSION != CDD_PLATFORM_CFGDEFINES_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_PATCH_VERSION != CDD_PLATFORM_CFGDEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw_TypesDef.h and Platform_CfgDefines.h are different"
#endif

#if (PLATFORM_ENABLE_INT_CTRL == STD_ON)
/* Check if current file and IntCtrl_Ip_TypesDef header file are of the same vendor */
#if (CDD_PLATFORM_IPW_TYPESDEF_VENDOR_ID != CDD_PLATFORM_INTCTRL_IP_TYPESDEF_VENDOR_ID)
    #error "Platform_Ipw_TypesDef.c and IntCtrl_Ip_TypesDef.h have different vendor ids"
#endif
/* Check if current file and IntCtrl_Ip_TypesDef header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTCTRL_IP_TYPESDEF_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw_TypesDef.h and IntCtrl_Ip_TypesDef.h are different"
#endif
/* Check if current file and IntCtrl_Ip_TypesDef header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_SW_MAJOR_VERSION != CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_MINOR_VERSION != CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_PATCH_VERSION != CDD_PLATFORM_INTCTRL_IP_TYPESDEF_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw_TypesDef.h and IntCtrl_Ip_TypesDef.h are different"
#endif
#endif

#if (PLATFORM_SYS_CFG == STD_ON)
/* Check if current file and System_Ip_CfgDefines header file are of the same vendor */
#if (CDD_PLATFORM_IPW_TYPESDEF_VENDOR_ID != CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_VENDOR_ID)
    #error "Platform_Ipw_TypesDef.c and System_Ip_CfgDefines.h have different vendor ids"
#endif
/* Check if current file and System_Ip_CfgDefines header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_SW_MAJOR_VERSION != CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_MINOR_VERSION != CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_PATCH_VERSION != CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw_TypesDef.h and System_Ip_CfgDefines.h are different"
#endif
/* Check if current file and System_Ip_CfgDefines header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw_TypesDef.h and System_Ip_CfgDefines.h are different"
#endif
#endif

#if (PLATFORM_INT_MONITOR == STD_ON)
/* Check if current file and Intmp_Ip_CfgDefines header file are of the same vendor */
#if (CDD_PLATFORM_IPW_TYPESDEF_VENDOR_ID != CDD_PLATFORM_INTM_IP_CFG_DEFINES_VENDOR_ID)
    #error "Platform_Ipw_TypesDef.c and Intmp_Ip_CfgDefines.h have different vendor ids"
#endif
/* Check if current file and Intmp_Ip_CfgDefines header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_SW_MAJOR_VERSION != CDD_PLATFORM_INTM_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_MINOR_VERSION != CDD_PLATFORM_INTM_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_PATCH_VERSION != CDD_PLATFORM_INTM_IP_CFG_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw_TypesDef.h and Intmp_Ip_CfgDefines.h are different"
#endif
/* Check if current file and Intmp_Ip_CfgDefines header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTM_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTM_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTM_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw_TypesDef.h and Intmp_Ip_CfgDefines.h are different"
#endif
#endif

#if (PLATFORM_ENABLE_MPU_M7 == STD_ON)
/* Check if Platform_Ipw_TypesDef.h and Mpu_M7_Ip_Types.h are of the same vendor */
#if (CDD_PLATFORM_IPW_TYPESDEF_VENDOR_ID != CDD_PLATFORM_MPU_M7_IP_TYPES_VENDOR_ID)
    #error "Platform_Ipw_TypesDef.h and Mpu_M7_Ip_Types.h have different vendor ids"
#endif
/* Check if Platform_Ipw_TypesDef.h file and Mpu_M7_Ip_Types.h file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_MPU_M7_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw_TypesDef.h and Mpu_M7_Ip_Types.h are different"
#endif
/* Check if Platform_Ipw_TypesDef.h file and Mpu_M7_Ip_Types.h file are of the same Software version */
#if ((CDD_PLATFORM_IPW_TYPESDEF_SW_MAJOR_VERSION != CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_MINOR_VERSION != CDD_PLATFORM_MPU_M7_IP_TYPES_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_TYPESDEF_SW_PATCH_VERSION != CDD_PLATFORM_MPU_M7_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw_TypesDef.h and Mpu_M7_Ip_Types.h are different"
#endif
#endif

/*==================================================================================================
 *                              TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

#if (PLATFORM_SYS_CFG == STD_ON)
/**
 * @internal
 * @brief          Configuration structure core-related interrupt requests.
 */
typedef struct
{
    System_Ip_IrqType eIrq;
    boolean bEnable;
}Platform_SystemIrqConfigType;

/**
 * @internal
 * @brief          Configuration structure system settings.
 */
typedef struct
{
    const Platform_SystemIrqConfigType *aSystemIrqs;
    uint8 u8SysIrqsCount;
    boolean bAhbSlavePriority;
}Platform_SystemConfigType;
#endif


#if (PLATFORM_INT_MONITOR == STD_ON)
/**
 * @internal
 * @brief          Configuration structure channel interrupt monitors.
 */
typedef struct
{
    Intm_Ip_MonitorType eMonitor;
    IRQn_Type eMonitoredIrq;
    uint32 u32AcceptedLatency;
}Platform_IntmChannelConfigType;

/**
 * @internal
 * @brief          Configuration structure generic interrupt monitors.
 */
typedef struct
{
    boolean bEnableIntMonitor;
}Platform_IntmGenericConfigType;

/**
 * @internal
 * @brief          Configuration structure interrupt monitors.
 */
typedef struct
{
    /** @brief number of aIntmChannelConfig */
    uint8 u8NumChannel;
    /** @brief configuration for a logic channel */
    const Platform_IntmChannelConfigType *aIntmChannelConfig;
    /** @brief configuration generic part, just en/disable */
    const Platform_IntmGenericConfigType *pIntmGenericConfig;
    /** @brief channel index in each partition map table*/
    const uint8                 (*Platform_IndexChannelMap)[];
    
}Platform_IntmConfigType;
#endif

/**
 * @internal
 * @brief          Configuration structure for PLATFORM IP wrapper.
 */
typedef struct
{
#if (PLATFORM_ENABLE_INT_CTRL == STD_ON)
    const IntCtrl_Ip_CtrlConfigType *pIntCtrlConfig;
#endif /* PLATFORM_ENABLE_INT_CTRL == STD_ON */
#if (PLATFORM_SYS_CFG == STD_ON)
    const Platform_SystemConfigType *aSystemConfig;
#endif /* PLATFORM_SYS_CFG == STD_ON */
#if (PLATFORM_INT_MONITOR == STD_ON)
    const Platform_IntmConfigType * pIntMonitor;
#endif /* PLATFORM_INT_MONITOR == STD_ON */
#if (PLATFORM_ENABLE_MPU_M7 == STD_ON)
    const Mpu_M7_Ip_ConfigType *Platform_Ipw_pMpuConfig;
#endif /* PLATFORM_ENABLE_MPU_M7 == STD_ON */
} Platform_Ipw_ConfigType;

#endif /* IPW_PLATFORM_IPW_TYPESDEF_H_ */
