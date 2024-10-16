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

#ifndef PLATFORM_IPW_H_
#define PLATFORM_IPW_H_

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

#include "Platform_Ipw_Cfg.h"
#if (PLATFORM_ENABLE_INT_CTRL == STD_ON)
    #include "IntCtrl_Ip.h"
#endif
#if (PLATFORM_SYS_CFG == STD_ON)
    #include "System_Ip.h"
#endif
#if (PLATFORM_INT_MONITOR == STD_ON)
    #include "Intm_Ip.h"
#endif
#if (PLATFORM_ENABLE_MPU_M7 == STD_ON)
    #include "Mpu_M7_Ip.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_IPW_VENDOR_ID                    43
#define CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION     4
#define CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION     7
#define CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION  0
#define CDD_PLATFORM_IPW_SW_MAJOR_VERSION             5
#define CDD_PLATFORM_IPW_SW_MINOR_VERSION             0
#define CDD_PLATFORM_IPW_SW_PATCH_VERSION             0

/*==================================================================================================
                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Platform_Ipw_Cfg header file are of the same vendor */
#if (CDD_PLATFORM_IPW_VENDOR_ID != CDD_PLATFORM_IPW_CFG_VENDOR_ID)
    #error "Platform_Ipw.h and Platform_Ipw_Cfg.h have different vendor ids"
#endif
/* Check if current file and Platform_Ipw_Cfg header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_IPW_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw.h and Platform_Ipw_Cfg.h are different"
#endif
/* Check if current file and Platform_Ipw_Cfg header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_SW_MAJOR_VERSION != CDD_PLATFORM_IPW_CFG_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_MINOR_VERSION != CDD_PLATFORM_IPW_CFG_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_PATCH_VERSION != CDD_PLATFORM_IPW_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw.h and Platform_Ipw_Cfg.h are different"
#endif

#if (PLATFORM_ENABLE_INT_CTRL == STD_ON)
/* Check if current file and IntCtrl_Ip header file are of the same vendor */
#if (CDD_PLATFORM_IPW_VENDOR_ID != CDD_PLATFORM_INTCTRL_IP_VENDOR_ID)
    #error "Platform_Ipw.h and IntCtrl_Ip.h have different vendor ids"
#endif
/* Check if current file and IntCtrl_Ip.h header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTCTRL_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw.h and IntCtrl_Ip.h are different"
#endif
/* Check if current file and IntCtrl_Ip header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_SW_MAJOR_VERSION != CDD_PLATFORM_INTCTRL_IP_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_MINOR_VERSION != CDD_PLATFORM_INTCTRL_IP_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_PATCH_VERSION != CDD_PLATFORM_INTCTRL_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw.h and IntCtrl_Ip.h are different"
#endif
#endif

#if (PLATFORM_SYS_CFG == STD_ON)
/* Check if current file and System_Ip header file are of the same vendor */
#if (CDD_PLATFORM_IPW_VENDOR_ID != CDD_PLATFORM_SYSTEM_IP_VENDOR_ID)
    #error "Platform_Ipw.h and System_Ip.h have different vendor ids"
#endif
/* Check if current file and System_Ip.h header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw.h and System_Ip.h are different"
#endif
/* Check if current file and System_Ip header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_SW_MAJOR_VERSION != CDD_PLATFORM_SYSTEM_IP_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_MINOR_VERSION != CDD_PLATFORM_SYSTEM_IP_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_PATCH_VERSION != CDD_PLATFORM_SYSTEM_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw.h and System_Ip.h are different"
#endif
#endif

#if (PLATFORM_INT_MONITOR == STD_ON)
/* Check if current file and Intm_Ip header file are of the same vendor */
#if (CDD_PLATFORM_IPW_VENDOR_ID != CDD_PLATFORM_INTM_IP_VENDOR_ID)
    #error "Platform_Ipw.h and Intm_Ip.h have different vendor ids"
#endif
/* Check if current file and Intm_Ip.h header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTM_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTM_IP_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTM_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw.h and Intm_Ip.h are different"
#endif
/* Check if current file and Intm_Ip header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_SW_MAJOR_VERSION != CDD_PLATFORM_INTM_IP_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_MINOR_VERSION != CDD_PLATFORM_INTM_IP_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_PATCH_VERSION != CDD_PLATFORM_INTM_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw.h and Intm__Ip.h are different"
#endif
#endif

#if (PLATFORM_ENABLE_MPU_M7 == STD_ON)
/* Check if current file and Mpu_M7_Ip header file are of the same vendor */
#if (CDD_PLATFORM_IPW_VENDOR_ID != CDD_PLATFORM_MPU_M7_IP_VENDOR_ID)
    #error "Platform_Ipw.h and Mpu_M7_Ip.h have different vendor ids"
#endif
/* Check if current file and Mpu_M7_Ip header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw.h and Mpu_M7_Ip.h are different"
#endif
/* Check if current file and Mpu_M7_Ip header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_SW_MAJOR_VERSION != CDD_PLATFORM_MPU_M7_IP_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_MINOR_VERSION != CDD_PLATFORM_MPU_M7_IP_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_PATCH_VERSION != CDD_PLATFORM_MPU_M7_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw.h and Mpu_M7_Ip.h are different"
#endif
#endif

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/
#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

#if (PLATFORM_ENABLE_MPU_M7 == STD_ON)
typedef Mpu_M7_Ip_RegionConfigType Platform_Mpu_M7_RegionConfigType;
typedef Mpu_M7_Ip_AccessRightsType Platform_Mpu_M7_AccessRightsType;
typedef Mpu_M7_Ip_ErrorDetailsType Platform_Mpu_M7_ErrorDetailsType;

void Platform_Ipw_Mpu_M7_Init(const Platform_Ipw_ConfigType * pIpwConfig);
void Platform_Ipw_Mpu_M7_SetRegionConfig(uint8 u8RegionNum,
                               const Platform_Mpu_M7_RegionConfigType * const pUserConfigPtr);
void Platform_Ipw_Mpu_M7_EnableRegion(uint8 u8RegionNum,
                            boolean bEnable);
void Platform_Ipw_Mpu_M7_SetAccessRight(uint8 u8RegionNum, Platform_Mpu_M7_AccessRightsType eRights);
boolean Platform_Ipw_Mpu_M7_GetErrorDetails(Platform_Mpu_M7_ErrorDetailsType * pErrorDetails);

#endif /* #if (STD_ON == PLATFORM_ENABLE_MPU_M7)  */



/**
 * @internal
 * @brief         Initializes the platform settings based on user configuration.
 */
void Platform_Ipw_Init(const Platform_Ipw_ConfigType *pConfig);


#if (PLATFORM_ENABLE_INT_CTRL == STD_ON)
/**
 * @internal
 * @brief         Enables/disables an interrupt by calling the Interrupt Controller IP layer.
 */
static inline void Platform_Ipw_SetIrq(IRQn_Type eIrqNumber, boolean bEnable)
{
    if (bEnable)
    {
        IntCtrl_Ip_EnableIrq(eIrqNumber);
    }
    else
    {
        IntCtrl_Ip_DisableIrq(eIrqNumber);
    }
}

/**
 * @internal
 * @brief         Sets the priority of an interrupt by calling the Interrupt Controller IP layer.
 */
static inline void Platform_Ipw_SetIrqPriority(IRQn_Type eIrqNumber, uint8 u8Priority)
{
    IntCtrl_Ip_SetPriority(eIrqNumber, u8Priority);
}

/**
 * @internal
 * @brief         Returns the priority of an interrupt by calling the Interrupt Controller IP layer.
 */
static inline uint8 Platform_Ipw_GetIrqPriority(IRQn_Type eIrqNumber)
{
    return IntCtrl_Ip_GetPriority(eIrqNumber);
}

/**
 * @internal
 * @brief         Installs a new interrupt handler by calling the Interrupt Controller IP layer.
 */
static inline void Platform_Ipw_InstallIrqHandler(IRQn_Type eIrqNumber,
                                                  const IntCtrl_Ip_IrqHandlerType pfNewHandler,
                                                  IntCtrl_Ip_IrqHandlerType* const pfOldHandler)
{
    IntCtrl_Ip_InstallHandler(eIrqNumber, pfNewHandler, pfOldHandler);
}
#endif

#if (PLATFORM_INT_MONITOR == STD_ON)
/**
 * @internal
 * @brief         Enables/disables interrupt monitoring feature by calling the Interrupt Monitor IP layer.
 */
void Platform_Ipw_SetIrqMonitor(boolean bEnable);


/**
 * @internal
 * @brief         Acknowledges a monitored interrupt by calling the Interrupt Monitor IP layer.
 */
#define Platform_Ipw_AckIrq(eIrqNumber) Intm_Ip_AckIrq(eIrqNumber)


/**
 * @internal
 * @brief         Selects an interrupt to be monitored by calling the Interrupt Monitor IP layer.
 */
void Platform_Ipw_SelectMonitoredIrq(const Platform_Ipw_ConfigType *pConfig,
                                                uint8 u8Channel,
                                                IRQn_Type eIrqNumber);

/**
 * @internal
 * @brief         Selects an accepted latency for a monitored interrupt
 *                by calling the Interrupt Monitor IP layer.
 */
void Platform_Ipw_SetMonitoredIrqLatency(const Platform_Ipw_ConfigType *pConfig,
                                                    uint8 u8Channel,
                                                    uint32 u32Latency);


/**
 * @internal
 * @brief         Resets an interrupt monitor timer by calling the Interrupt Monitor IP layer.
 */
void Platform_Ipw_ResetIrqMonitorTimer(const Platform_Ipw_ConfigType *pConfig,
                                                    uint8 u8Channel);

/**
 * @internal
 * @brief         Returns the status of an interrupt monitor by calling the Interrupt Monitor IP layer.
 */
boolean Platform_Ipw_GetIrqMonitorStatus(const Platform_Ipw_ConfigType *pConfig,
                                                        uint8 u8Channel);

/**
 * @internal
 * @brief         Returns the validation result for given logical channel.
 */
Std_ReturnType Platform_Ipw_ValidateChannelIntm(const Platform_Ipw_ConfigType *pConfig,
                                                    uint8 u8Channel);
/**
 * @internal
 * @brief         Returns the the possibility of setting interrupt monitor enabling.
 */
    
Std_ReturnType Platform_Ipw_ValidateSetIrqMonitor(const Platform_Ipw_ConfigType *pConfig);

#endif

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"


#endif /* PLATFORM_IPW_H_ */
