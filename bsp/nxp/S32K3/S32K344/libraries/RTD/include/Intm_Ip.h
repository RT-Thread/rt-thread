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

#ifndef INTM_IP_H_
#define INTM_IP_H_

/**
*   @file
*
*   @defgroup   Intm_Ip Interrupt Monitor IP
*   @ingroup    Platform
*
*   @addtogroup Intm_Ip
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Intm_Ip_Cfg.h"
#include "Devassert.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTM_IP_VENDOR_ID                          43
#define CDD_PLATFORM_INTM_IP_SW_MAJOR_VERSION                   5
#define CDD_PLATFORM_INTM_IP_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTM_IP_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_INTM_IP_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTM_IP_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_INTM_IP_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Intm_Ip_Cfg header file are of the same vendor */
#if (CDD_PLATFORM_INTM_IP_VENDOR_ID != CDD_PLATFORM_INTM_IP_CFG_TYPES_VENDOR_ID)
    #error "Intm_Ip.h and Intm_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Intm_Ip_Cfg header file are of the same Autosar version */
#if ((CDD_PLATFORM_INTM_IP_AR_RELEASE_MAJOR_VERSION    != CDD_PLATFORM_INTM_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTM_IP_AR_RELEASE_MINOR_VERSION    != CDD_PLATFORM_INTM_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_INTM_IP_AR_RELEASE_REVISION_VERSION != CDD_PLATFORM_INTM_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Intm_Ip.h and Intm_Ip_Cfg.h are different"
#endif
/* Check if current file and Intm_Ip_Cfg header file are of the same Software version */
#if ((CDD_PLATFORM_INTM_IP_SW_MAJOR_VERSION != CDD_PLATFORM_INTM_IP_CFG_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_INTM_IP_SW_MINOR_VERSION != CDD_PLATFORM_INTM_IP_CFG_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_INTM_IP_SW_PATCH_VERSION != CDD_PLATFORM_INTM_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Intm_Ip.h and Intm_Ip_Cfg.h are different"
#endif


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

/**
 * @brief         Enables interrupt monitoring feature.
 *
 * @details       This function is non-reentrant and enables the interrupt monitors.
 *
 * @return        void
 *
 * @api
 *
 * @implements    Intm_Ip_EnableMonitor_Activity
 *
 * */
static inline void Intm_Ip_EnableMonitor(void)
{
    IP_INTM->INTM_MM |= INTM_INTM_MM_MM_MASK;
}

/**
 * @brief         Disables interrupt monitoring feature.
 *
 * @details       This function is non-reentrant and disables the interrupt monitors.
 *
 * @return        void
 *
 * @api
 *
 * @implements    Intm_Ip_DisableMonitor_Activity
 *
 * */
static inline void Intm_Ip_DisableMonitor(void)
{
    IP_INTM->INTM_MM &= ~(INTM_INTM_MM_MM_MASK);
}

/**
 * @brief         Acknowledges a monitored interrupt.
 *
 * @details       This function is reentrant; it acknowledges that a monitored interrupt
 *                has been been served.
 *
 * @param[in]     eIrqNumber: The interrupt vector acknowledged.
 * @return void
 *
 * @api
 *
 * @implements    Intm_Ip_AckIrq_Activity
 *
 * */
static inline void Intm_Ip_AckIrq(IRQn_Type eIrqNumber)
{
    IP_INTM->INTM_IACK = ((uint32)eIrqNumber) & INTM_INTM_IACK_IRQ_MASK;
}

/**
 * @brief         Selects an interrupt to monitor.
 *
 * @details       This function is reentrant; it selects which interrupt is monitored on
 *                a specific interrupt monitor.
 *
 * @param[in]     eMonitorIdx: The index of the interrupt monitor used.
 * @param[in]     eIrqNumber: The interrupt vector to be monitored.
 * @return void
 *
 * @api
 *
 * @implements    Intm_Ip_SelectMonitoredIrq_Activity
 *
 * */
static inline void Intm_Ip_SelectMonitoredIrq(Intm_Ip_MonitorType eMonitorIdx, IRQn_Type eIrqNumber)
{
    IP_INTM->MON[(uint8)eMonitorIdx].INTM_IRQSEL = ((uint32)eIrqNumber) & INTM_INTM_IRQSEL_IRQ_MASK;
}

/**
 * @brief         Sets the latency for a monitored interrupt.
 *
 * @details       This function is reentrant; it sets the accepted latency for the
 *                monitored interrupt.
 *
 * @param[in]     eMonitorIdx: The index of the interrupt monitor used.
 * @param[in]     u32Latency: The accepted latency for the monitored interrupt.
 * @return void
 *
 * @api
 *
 * @implements    Intm_Ip_SetLatency_Activity
 *
 * */
static inline void Intm_Ip_SetLatency(Intm_Ip_MonitorType eMonitorIdx, uint32 u32Latency)
{
    IP_INTM->MON[(uint8)eMonitorIdx].INTM_LATENCY = (u32Latency & INTM_INTM_LATENCY_LAT_MASK);
}

/**
 * @brief         Resets the timer for an interrupt monitor.
 *
 * @details       This function is reentrant; it resets the timer for the interrupt monitor.
 *
 * @param[in]     eMonitorIdx: The index of the interrupt monitor used.
 * @return void
 *
 * @api
 *
 * @implements    Intm_Ip_ResetTimer_Activity
 *
 * */
static inline void Intm_Ip_ResetTimer(Intm_Ip_MonitorType eMonitorIdx)
{
    IP_INTM->MON[(uint8)eMonitorIdx].INTM_TIMER = 0UL;
}

/**
 * @brief         Returns the status of an interrupt monitor.
 *
 * @details       This function is reentrant; it returns the status of an interrupt monitor:
 *                0 - latency not exceeded; 1 - timer exceeded latency.
 *
 * @param[in]     eMonitorIdx: The index of the interrupt monitor used.
 * @return        uint8: 0 - latency not exceeded; 1 - timer exceeded latency.
 *
 * @api
 *
 * @implements    Intm_Ip_GetStatus_Activity
 *
 * */
static inline uint8 Intm_Ip_GetStatus(Intm_Ip_MonitorType eMonitorIdx)
{
    return (uint8)(IP_INTM->MON[(uint8)eMonitorIdx].INTM_STATUS);
}

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#endif /* INTM_IP_H_ */

/** @} */
