/***************************************************************************//**
 * @file
 * @brief Real Time Counter (RTC) peripheral API for EFM32.
 * @author Energy Micro AS
 * @version 2.3.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __EFM32_RTC_H
#define __EFM32_RTC_H

#include <stdbool.h>
#include "efm32.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup RTC
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** RTC initialization structure. */
typedef struct
{
  bool enable;   /**< Start counting when init completed. */
  bool debugRun; /**< Counter shall keep running during debug halt. */
  bool comp0Top; /**< Use compare register 0 as max count value. */
} RTC_Init_TypeDef;

/** Suggested default config for RTC init structure. */
#define RTC_INIT_DEFAULT                                       \
  { true,    /* Start counting when init done */               \
    false,   /* Disable updating during debug halt */          \
    true     /* Restart counting from 0 when reaching COMP0 */ \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

uint32_t RTC_CompareGet(unsigned int comp);
void RTC_CompareSet(unsigned int comp, uint32_t value);

/***************************************************************************//**
 * @brief
 *   Get RTC counter value.
 *
 * @return
 *   Current RTC counter value.
 ******************************************************************************/
static __INLINE uint32_t RTC_CounterGet(void)
{
  return(RTC->CNT);
}

void RTC_CounterReset(void);
void RTC_Enable(bool enable);
void RTC_FreezeEnable(bool enable);
void RTC_Init(const RTC_Init_TypeDef *init);

/***************************************************************************//**
 * @brief
 *   Clear one or more pending RTC interrupts.
 *
 * @param[in] flags
 *   RTC interrupt sources to clear. Use a set of interrupt flags OR-ed
 *   together to clear multiple interrupt sources for the RTC module
 *   (RTC_IFS_nnn).
 ******************************************************************************/
static __INLINE void RTC_IntClear(uint32_t flags)
{
  RTC->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more RTC interrupts.
 *
 * @param[in] flags
 *   RTC interrupt sources to disable. Use a set of interrupt flags OR-ed
 *   together to disable multiple interrupt sources for the RTC module
 *   (RTC_IFS_nnn).
 ******************************************************************************/
static __INLINE void RTC_IntDisable(uint32_t flags)
{
  RTC->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more RTC interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using RTC_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] flags
 *   RTC interrupt sources to enable. Use a set of interrupt flags OR-ed
 *   together to set multiple interrupt sources for the RTC module
 *   (RTC_IFS_nnn).
 ******************************************************************************/
static __INLINE void RTC_IntEnable(uint32_t flags)
{
  RTC->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending RTC interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   Pending RTC interrupt sources. Returns a set of interrupt flags OR-ed
 *   together for multiple interrupt sources in the RTC module (RTC_IFS_nnn).
 ******************************************************************************/
static __INLINE uint32_t RTC_IntGet(void)
{
  return(RTC->IF);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending RTC interrupts from SW.
 *
 * @param[in] flags
 *   RTC interrupt sources to set to pending. Use a set of interrupt flags
 *   OR-ed together to set multiple interrupt sources for the RTC module
 *   (RTC_IFS_nnn).
 ******************************************************************************/
static __INLINE void RTC_IntSet(uint32_t flags)
{
  RTC->IFS = flags;
}

void RTC_Reset(void);

/** @} (end addtogroup RTC) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_RTC_H */
