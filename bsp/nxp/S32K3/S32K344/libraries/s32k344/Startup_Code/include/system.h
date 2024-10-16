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
/*================================================================================================
*   @file    system.h
*   @version 5.0.0
*
*   @brief   AUTOSAR Platform - SYSTEM
*   @details SYSTEM
*            This file contains sample code only. It is not part of the production code deliverables.
*   @addtogroup PLATFORM
*   @{
*
==================================================================================================*/

#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef S32K344
    #include "S32K344_SCB.h"
    #include "S32K344_MPU.h"
    #include "S32K344_MSCM.h"
#endif
#ifdef S32K324
    #include "S32K324_SCB.h"
    #include "S32K324_MPU.h"
    #include "S32K324_MSCM.h"
#endif 
#ifdef S32K314
    #include "S32K314_SCB.h"
    #include "S32K314_MPU.h"
    #include "S32K314_MSCM.h"
#endif
#ifdef S32K312
    #include "S32K312_SCB.h"
    #include "S32K312_MPU.h"
    #include "S32K312_MSCM.h"
#endif
#if defined(S32K396) || defined(S32K394) || defined(S32K364) || defined(S32K366)
    #include "S32K39_SCB.h"
    #include "S32K39_MPU.h"
    #include "S32K39_MSCM.h"
#endif
#if defined(S32K376) || defined(S32K374)
    #include "S32K37_SCB.h"
    #include "S32K37_MPU.h"
    #include "S32K37_MSCM.h"
#endif
#if defined(S32K328) || defined(S32K338) || defined(S32K348) || defined(S32K358)
    #include "S32K358_SCB.h"
    #include "S32K358_MPU.h"
    #include "S32K358_MSCM.h"
#endif
#ifdef S32K388
    #include "S32K388_SCB.h"
    #include "S32K388_MPU.h"
    #include "S32K388_MSCM.h"
#endif
#if defined(S32K311) || defined(S32K310)
    #include "S32K311_SCB.h"
    #include "S32K311_MPU.h"
    #include "S32K311_MSCM.h"
#endif
#if defined(S32M276) || defined(S32M274)
    #include "S32M27x_SCB.h"
    #include "S32M27x_MPU.h"
    #include "S32M27x_MSCM.h"
#endif
#include "Std_Types.h"
#include "Mcal.h"


#define SCB_CCR_DC_MASK               (1UL << 16U)

#define SCB_CCR_IC_MASK               (1UL << 17U)




#define SCB_CCSIDR_NUMSETS_SHIFT            13U

#define SCB_CCSIDR_NUMSETS_MASK       (0x7FFFUL << 13U)

#define SCB_CCSIDR_ASSOCIATIVITY_SHIFT       3U        
#define SCB_CCSIDR_ASSOCIATIVITY_MASK   (0x3FFUL << 3U)

#define SCB_DCISW_SET_SHIFT                   5U
#define SCB_DCISW_SET_MASK                 (0x1FFUL << 5U)


#define SCB_DCISW_WAY_SHIFT                  30U      

#define SCB_DCISW_WAY_MASK                  (3UL << 30U)



/* Cache Size ID Register Macros */
#define CCSIDR_WAYS(x)     (((x) & SCB_CCSIDR_ASSOCIATIVITY_MASK) >> SCB_CCSIDR_ASSOCIATIVITY_SHIFT)
#define CCSIDR_SETS(x)     (((x) & SCB_CCSIDR_NUMSETS_MASK) >> SCB_CCSIDR_NUMSETS_SHIFT)

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"


void SystemInit(void);

/* 
 * @brief Default IRQ handler
 * @param: None
 * 
 * @return: None
 */

void default_interrupt_routine(void);

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
/* 
 * @brief Switch to user mode and return the value passed by u32returnValue
 * @param: [in] u8SwitchToSupervisor - if 0, the function will return the value without switching to user mode,
 *                                     if 1, the function will go to user mode before returning the value
 * @param: [in] u32returnValue       - value to be returned
 * 
 * @return: u32returnValue
 */
uint32 Sys_GoToUser_Return(uint32 u32SwitchToSupervisor, uint32 u32returnValue);

/* 
 * @brief Switch to supervisor mode
 * @param: None
 * 
 * @return: operation result, 1 if switch was done, 0 if the CPU was already in supervisor mode or in handler mode
 */
uint32 Sys_GoToSupervisor(void);

/* 
 * @brief Switch to user mode
 * @param: None
 * 
 * @return: 0
 */
uint32 Sys_GoToUser(void);

/* 
 * @brief Sys_SuspendInterrupts
 * @param: None
 * 
 * @return: none
 */
void Sys_SuspendInterrupts(void);
void Sys_ResumeInterrupts(void);
#endif

/* 
 * @brief Get the hardware id of the currently executing core
 * @param: None
 * 
 * @return: coreId
 */
uint8 Sys_GetCoreID(void);
/* 
 * @brief Enable FPU
 * @param: None
 * 
 * @return: None
 */
void Enable_FPU(void);

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_H */
