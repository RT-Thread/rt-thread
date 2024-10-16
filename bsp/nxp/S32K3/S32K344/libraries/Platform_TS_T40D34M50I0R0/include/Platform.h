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

#ifndef PLATFORM_H_
#define PLATFORM_H_

/**
 *   @file
 *
 *   @addtogroup Platform
 *   @{
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "Platform_Cfg.h"
#include "Platform_Ipw.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_VENDOR_ID                     43
#define CDD_PLATFORM_MODULE_ID                     255
#define CDD_PLATFORM_AR_RELEASE_MAJOR_VERSION      4
#define CDD_PLATFORM_AR_RELEASE_MINOR_VERSION      7
#define CDD_PLATFORM_AR_RELEASE_REVISION_VERSION   0
#define CDD_PLATFORM_SW_MAJOR_VERSION              5
#define CDD_PLATFORM_SW_MINOR_VERSION              0
#define CDD_PLATFORM_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Platform_Cfg header file are of the same vendor */
#if (CDD_PLATFORM_VENDOR_ID != CDD_PLATFORM_CFG_VENDOR_ID)
    #error "Platform.h and Platform_Cfg.h have different vendor ids"
#endif
/* Check if current file and Platform_Cfg header file are of the same Autosar version */
#if ((CDD_PLATFORM_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_CFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform.h and Platform_Cfg.h are different"
#endif
/* Check if current file and Platform_Cfg header file are of the same Software version */
#if ((CDD_PLATFORM_SW_MAJOR_VERSION != CDD_PLATFORM_CFG_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_SW_MINOR_VERSION != CDD_PLATFORM_CFG_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_SW_PATCH_VERSION != CDD_PLATFORM_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform.h and Platform_Cfg.h are different"
#endif

/* Check if current file and Platform_Iwp header file are of the same vendor */
#if (CDD_PLATFORM_VENDOR_ID != CDD_PLATFORM_IPW_VENDOR_ID)
    #error "Platform.h and Platform_Iwp.h have different vendor ids"
#endif
/* Check if current file and Platform_Cfg header file are of the same Autosar version */
#if ((CDD_PLATFORM_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform.h and Platform_Ipw.h are different"
#endif
/* Check if current file and Platform_Cfg header file are of the same Software version */
#if ((CDD_PLATFORM_SW_MAJOR_VERSION != CDD_PLATFORM_IPW_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_SW_MINOR_VERSION != CDD_PLATFORM_IPW_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_SW_PATCH_VERSION != CDD_PLATFORM_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform.h and Platform_Ipw.h are different"
#endif
/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"


/**
 * @brief         Initializes the paltform settings based on user configuration.
 *
 * @details       This function is non-reentrant; it initializes the interrupts,
 *                interrupt monitors (if available), as well as other platform specific settings
 *                as defined for each SoC.
 *
 * @param[in]     pConfig: pointer to platform configuration structure.
 * @return        void
 *
 * @api
 *
 * */
void Platform_Init(const Platform_ConfigType *pConfig);

#ifdef  PLATFORM_ENABLE_INT_CTRL
#if  (PLATFORM_ENABLE_INT_CTRL == STD_ON)
/**
 * @brief         Configures (enables/disables) an interrupt request.
 *
 * @details       This function is non-reentrant; it enables/disables the selected interrupt.
 *
 * @param[in]     eIrqNumber: interrupt to be configured.
 * @param[in]     bEnable: TRUE - enable interrupt, FALSE - disable interrupt.
 * @return        Std_ReturnType: E_OK/E_NOT_OK; specific errors are reported through DET.
 *
 * @api
 *
 * */
Std_ReturnType Platform_SetIrq(IRQn_Type eIrqNumber, boolean bEnable);

/**
 * @brief         Configures the priority of an interrupt request.
 *
 * @details       This function is non-reentrant; it sets the priority for the selected interrupt.
 *
 * @param[in]     eIrqNumber: interrupt number for which priority is configured.
 * @param[in]     u8Priority: desired priority of the interrupt.
 * @return        Std_ReturnType: E_OK/E_NOT_OK; specific errors are reported through DET.
 *
 * @api
 *
 * */
Std_ReturnType Platform_SetIrqPriority(IRQn_Type eIrqNumber, uint8 u8Priority);

/**
 * @brief         Returns the priority of an interrupt request.
 *
 * @details       This function is non-reentrant; it retrieves the current priority of
 *                the selected interrupt.
 *
 * @param[in]     eIrqNumber: interrupt number for which priority is returned.
 * @param[out]    u8Priority: output parameter storing the priority of the interrupt.
 * @return        Std_ReturnType: E_OK/E_NOT_OK; specific errors are reported through DET.
 *
 * @api
 *
 * */
Std_ReturnType Platform_GetIrqPriority(IRQn_Type eIrqNumber, uint8 * u8Priority);

/**
 * @brief         Installs a new handler for an interrupt request.
 *
 * @details       This function is non-reentrant; it replaces the current interrupt handler
 *                for the selected interrupt with the new function provided as the second
 *                parameter. The address of the old handler can be optionally stored in the third
 *                parameter.
 *
 * @param[in]     eIrqNumber: interrupt number for which priority is returned.
 * @param[in]     pfNewHandler: function pointer for the new handler.
 * @param[out]    pfOldHandler: function pointer that will store the address of the old handler
 *                @note - this parameter can be passed as NULL if not needed.
 * @return        pfOldHandler: E_OK/E_NOT_OK; specific errors are reported through DET.
 *
 * @api
 *
 * */
Std_ReturnType Platform_InstallIrqHandler(IRQn_Type eIrqNumber,
                                          const Platform_IrqHandlerType pfNewHandler,
                                          Platform_IrqHandlerType* const pfOldHandler);

#endif /* PLATFORM_ENABLE_INT_CTRL == STD_ON */
#endif /* PLATFORM_ENABLE_INT_CTRL*/

#if (PLATFORM_INT_MONITOR == STD_ON)

/**
 * @brief         Configures (enables/disables) the interrupt monitor.
 *
 * @details       This function is reentrant; it enables/disables the interrupt monitoring feature.
 *
 * @param[in]     bEnable: TRUE - enable interrupt monitoring, FALSE - disable interrupt monitoring.
 * @return        void
 *
 * @api
 *
 * */
void Platform_SetIrqMonitor(boolean bEnable);

/**
 * @brief         Acknowledges a monitored interrupt has been served.
 *
 * @details       This function is reentrant; it confirms that a monitored interrupt has been served.
 *
 * @param[in]     bEnable: enable or disable monitoring, TRUE-enable FALSE-disablw.
 * @return        void.
 *
 * @api
 *
 * */
void Platform_AckIrq(IRQn_Type eIrqNumber);

/**
 * @brief         Selects an interrupt to monitor.
 *
 * @details       This function is reentrant; it selects which interrupt is monitored on which
 *                interrupt monitor.
 *
 * @param[in]     u8Channel: Logical channel of interrupt monitor used.
 * @param[in]     eIrqNumber: the interrupt vector to be monitored.
 * @return        void.
 *
 * @api
 *
 * */
void Platform_SelectMonitoredIrq(uint8 u8Channel , IRQn_Type eIrqNumber);

/**
 * @brief         Sets the latency for a monitored interrupt.
 *
 * @details       This function is reentrant; it sets the accepted latency for the
 *                monitored interrupt.
 *
 * @param[in]     u8Channel: Logical channel of interrupt monitor used.
 * @param[in]     u32Latency: The accepted latency for the monitored interrupt.
 * @return        void.
 *
 * @api
 *
 * */
void Platform_SetMonitoredIrqLatency(uint8 u8Channel, uint32 u32Latency);

/**
 * @brief         Resets the timer for an interrupt monitor.
 *
 * @details       This function is reentrant; it resets the timer for the interrupt monitor.
 *
 * @param[in]     u8Channel: Logical channel of interrupt monitor used.
 * @return        void.
 *
 * @api
 *
 * */
void Platform_ResetIrqMonitorTimer(uint8 u8Channel);

/**
 * @brief         Retrieves the status of an interrupt monitor.
 *
 * @details       This function shall return whether the accepted latency for the  monitored IRQs *                has been exceeded.
 *
 * @param[in]     u8Channel        : Logical channel of interrupt monitor used.
 * @param[out]    bLatencyExceeded : output status parameter: TRUE - latency exceeded, FALSE *                latency not exceeded
 * @return        Std_ReturnType: E_OK/E_NOT_OK; specific errors are reported through DET.
 *
 * @api
 *
 * */
Std_ReturnType Platform_GetIrqMonitorStatus(uint8 u8Channel, boolean *bLatencyExceeded);
#endif




#if (PLATFORM_ENABLE_MPU_M7 == STD_ON)
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
void Platform_Mpu_M7_SetRegionConfig(uint8 u8RegionNum, const Platform_Mpu_M7_RegionConfigType * const pUserConfigPtr);

/**
 * @brief         Enables or disabled a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum       Region to be modified 
 * @param[in]     bEnable           Specifies wheter the region is enabled or disabled
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void Platform_Mpu_M7_EnableRegion(uint8 u8RegionNum, boolean bEnable);

/**
 * @brief         Modify the access rights for a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum      Region to be modified 
 * @param[in]     eRights          Specifies the new access rights
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void Platform_Mpu_M7_SetAccessRight(uint8 u8RegionNum, Platform_Mpu_M7_AccessRightsType eRights);

/**
 * @brief         Retrieve error details
 *
 * @details       This function is Reentrant
 *
 * @param[out]    pErrorDetails : Storage where the data will be saved 
 *
 * @return        Std_ReturnType
 * @retval        E_OK                    if an error was present
 * @retval        E_NOT_OK                otherwise
 * @api
 *
 * @pre
 *
 * */
Std_ReturnType Platform_Mpu_M7_GetErrorDetails(Platform_Mpu_M7_ErrorDetailsType * pErrorDetails);


#endif /* #if (STD_ON == PLATFORM_ENABLE_MPU_M7)  */



#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* PLATFORM_H_ */

/** @} */
