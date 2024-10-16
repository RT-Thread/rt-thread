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
/*==================================================================================================
*   @file    nvic.h
*   @version 5.0.0
*
*   @brief   AUTOSAR Platform - nvic driver
*   @details nvic driver
*            This file contains sample code only. It is not part of the production code deliverables
*
*   @addtogroup BUILD_ENV
*   @{
*
==================================================================================================*/

#ifndef NVIC_H
#define NVIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Mcal.h"

#if defined(S32K311) || defined(S32K310)
    #include "S32K311.h"
#endif
#ifdef S32K344
    #include "S32K344.h"
#endif
#ifdef S32K342
    #include "S32K342.h"
#endif
#ifdef S32K341
    #include "S32K341.h"
#endif
#ifdef S32K324
    #include "S32K324.h"
#endif 
#ifdef S32K314
    #include "S32K314.h"
#endif
#ifdef S32K312
    #include "S32K312.h"
#endif
#ifdef S32K322
    #include "S32K322.h"
#endif
#if defined(S32K396) || defined(S32K394) || defined(S32K364) || defined(S32K366)
    #include "S32K39.h"
#endif
#if defined(S32K374) || defined(S32K376)
    #include "S32K37.h"
#endif
#if defined(S32K328) || defined(S32K338) || defined(S32K348) || defined(S32K358)
    #include "S32K358.h"
#endif
#ifdef S32K388
    #include "S32K388.h"
#endif
#if defined(S32M276) || defined(S32M274)
    #include "S32M27x.h"
#endif
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define NVIC_BASEADDR 0xE000E100
#define NVIC_ISER_OFFSET(id)      (uint32)(((id) >> 5) << 2)
#define NVIC_ICER_OFFSET(id)      (0x80 + (uint32)(((id) >> 5) << 2))
#define NVIC_IPRO_OFFSET(id)      (0x300 + (uint32)(((id) >> 2) << 2))
#define NVIC_IPRO_MASK(id)        (uint32)(0xFFU << (((id) % 4) * 8))
#define NVIC_IPRO_SHIFT(id, prio) (uint32)((prio) << (((id) % 4) * 8))

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

void NVIC_SetPriorityGrouping(uint32 PriorityGroup);
void NVIC_EnableIRQ(uint8 IRQn);
void NVIC_DisableIRQ(uint8 IRQn);
void NVIC_SetPriority(uint8 IRQn, uint8 priority);

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /*NVIC_H*/
