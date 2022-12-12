/**************************************************************************//**
 * @file     timer.h
 * @brief    N9H30 series TIMER driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_TIMER_H__
#define __NU_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "N9H30.h"

#define TIMER_COUNTER_ENABLE      (1UL << 30)     /*!< Timer counter enable  */
#define TIMER_INTERRUPT_ENABLE    (1UL << 29)     /*!< Timer interrupt enable  */

#define TIMER_ONESHOT_MODE        (0UL)           /*!< Timer working in one shot mode   */
#define TIMER_PERIODIC_MODE       (1UL << 27)     /*!< Timer working in periodic mode   */
#define TIMER_CONTINUOUS_MODE     (3UL << 27)     /*!< Timer working in continuous mode */

#define TIMER_COUNTER_RESET       (1UL << 26)     /*!< Timer reset counter */
#define TIMER_IS_ALIVE            (1UL << 25)     /*!< Timer is alive */

static __inline void TIMER_ClearIntFlag(uint32_t timer)
{
    outpw(REG_TMR_ISR, (1 << timer));
}

static __inline uint32_t TIMER_GetIntFlag(uint32_t timer)
{
    return inpw(REG_TMR_ISR) & (1 << timer);
}

void TIMER_SET_CMP_VALUE(uint32_t timer, uint32_t u32Cmpr);
void TIMER_SET_OPMODE(uint32_t timer, uint32_t u32OpMode);
void TIMER_SET_PRESCALE_VALUE(uint32_t timer, uint32_t u32PreScale);
uint32_t TIMER_GetModuleClock(uint32_t timer);
void TIMER_Start(uint32_t timer);
void TIMER_Stop(uint32_t timer);
void TIMER_ClearCounter(uint32_t timer);
uint32_t TIMER_GetCounter(uint32_t timer);
uint32_t TIMER_GetCompareData(uint32_t timer);
void TIMER_EnableInt(uint32_t timer);
void TIMER_DisableInt(uint32_t timer);
void TIMER_Close(uint32_t timer);
uint32_t TIMER_Open(uint32_t timer, uint32_t u32Mode, uint32_t u32Freq);
__inline void TIMER_ClearIntFlag(uint32_t timer);
__inline uint32_t TIMER_GetIntFlag(uint32_t timer);

#ifdef __cplusplus
}
#endif

#endif //__NU_TIMER_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
