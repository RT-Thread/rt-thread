/***************************************************************************//**
 * @file
 * @brief Pulse Counter (PCNT) peripheral API for EFM32.
 * @author Energy Micro AS
 * @version 1.3.0
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
#ifndef __EFM32_PCNT_H
#define __EFM32_PCNT_H

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
 * @addtogroup PCNT
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** PCNT counter width mask. */
/* TBD: Remove use with efm32 include file defines when corrected */
#define PCNT_WIDTH_MASK    0xff

/** @endcond (DO_NOT_INCLUDE_WITH_DOXYGEN) */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Mode selection. */
typedef enum
{
  /** Disable pulse counter. */
  pcntModeDisable   = _PCNT_CTRL_MODE_DISABLE,

  /** Single input LFACLK oversampling mode (available in EM0-EM2). */
  pcntModeOvsSingle = _PCNT_CTRL_MODE_OVSSINGLE,

  /** Externally clocked single input counter mode (available in EM0-EM3). */
  pcntModeExtSingle = _PCNT_CTRL_MODE_EXTCLKSINGLE,

  /** Externally clocked quadrature decoder mode (available in EM0-EM3). */
  pcntModeExtQuad   = _PCNT_CTRL_MODE_EXTCLKQUAD
} PCNT_Mode_TypeDef;


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** Init structure. */
typedef struct
{
  /** Mode to operate in. */
  PCNT_Mode_TypeDef mode;

  /**
   * Initial counter value (refer to reference manual for max value allowed).
   * Only used for #pcntModeOvsSingle (and possibly #pcntModeDisable) modes.
   * If using #pcntModeExtSingle or #pcntModeExtQuad modes, the counter
   * value is reset to HW reset value.
   */
  uint32_t counter;

  /**
   * Initial top value (refer to reference manual for max value allowed).
   * Only used for #pcntModeOvsSingle (and possibly #pcntModeDisable) modes.
   * If using #pcntModeExtSingle or #pcntModeExtQuad modes, the top
   * value is reset to HW reset value.
   */
  uint32_t top;

  /**
   * Polarity of incoming edge.
   * @li #pcntModeExtSingle mode - if false, positive edges are counted,
   *   otherwise negative edges.
   * @li #pcntModeExtQuad mode - if true, counting direction is inverted.
   */
  bool negEdge;

  /**
   * Counting direction, only applicable for #pcntModeOvsSingle and
   * #pcntModeExtSingle modes.
   */
  bool countDown;

  /** Enable filter, only available in #pcntModeOvsSingle mode. */
  bool filter;
} PCNT_Init_TypeDef;

/** Default config for PCNT init structure. */
/* TBD: Remove PCNT_WIDTH_MASK use when _PCNT_TOP_RESETVALUE corrected */
#define PCNT_INIT_DEFAULT                                                           \
  { pcntModeDisable,                          /* Disabled by default. */            \
    _PCNT_CNT_RESETVALUE,                     /* Default counter HW reset value. */ \
    _PCNT_TOP_RESETVALUE & PCNT_WIDTH_MASK,   /* Default counter HW reset value. */ \
    false,                                    /* Use positive edge. */              \
    false,                                    /* Up-counting. */                    \
    false                                     /* Filter disabled. */                \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get pulse counter value.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @return
 *   Current pulse counter value.
 ******************************************************************************/
static __INLINE uint32_t PCNT_CounterGet(PCNT_TypeDef *pcnt)
{
  return(pcnt->CNT);
}

void PCNT_CounterReset(PCNT_TypeDef *pcnt);
void PCNT_CounterTopSet(PCNT_TypeDef *pcnt, uint32_t count, uint32_t top);


/***************************************************************************//**
 * @brief
 *   Set counter value.
 *
 * @details
 *   The pulse counter is disabled while changing counter value, and reenabled
 *   (if originally enabled) when counter value has been set.
 *
 * @note
 *   This function will stall until synchronization to low frequency domain is
 *   completed. For that reason, it should normally not be used when using
 *   an external clock to clock the PCNT module, since stall time may be
 *   undefined in that case. The counter should normally only be set when
 *   operating in (or about to enable) #pcntModeOvsSingle mode.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @param[in] count
 *   Value to set in counter register.
 ******************************************************************************/
static __INLINE void PCNT_CounterSet(PCNT_TypeDef *pcnt, uint32_t count)
{
  PCNT_CounterTopSet(pcnt, count, pcnt->TOP);
}


void PCNT_Enable(PCNT_TypeDef *pcnt, PCNT_Mode_TypeDef mode);
void PCNT_FreezeEnable(PCNT_TypeDef *pcnt, bool enable);
void PCNT_Init(PCNT_TypeDef *pcnt, PCNT_Init_TypeDef *init);


/***************************************************************************//**
 * @brief
 *   Clear one or more pending PCNT interrupts.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @param[in] flags
 *   Pending PCNT interrupt source to clear. Use a logical OR combination
 *   of valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
static __INLINE void PCNT_IntClear(PCNT_TypeDef *pcnt, uint32_t flags)
{
  pcnt->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more PCNT interrupts.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @param[in] flags
 *   PCNT interrupt sources to disable. Use a logical OR combination of
 *   valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
static __INLINE void PCNT_IntDisable(PCNT_TypeDef *pcnt, uint32_t flags)
{
  pcnt->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more PCNT interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using PCNT_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @param[in] flags
 *   PCNT interrupt sources to enable. Use a logical OR combination of
 *   valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
static __INLINE void PCNT_IntEnable(PCNT_TypeDef *pcnt, uint32_t flags)
{
  pcnt->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending PCNT interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @return
 *   PCNT interrupt sources pending. A logical OR combination of valid
 *   interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
static __INLINE uint32_t PCNT_IntGet(PCNT_TypeDef *pcnt)
{
  return(pcnt->IF);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending PCNT interrupts from SW.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @param[in] flags
 *   PCNT interrupt sources to set to pending. Use a logical OR combination
 *   of valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
static __INLINE void PCNT_IntSet(PCNT_TypeDef *pcnt, uint32_t flags)
{
  pcnt->IFS = flags;
}

void PCNT_Reset(PCNT_TypeDef *pcnt);


/***************************************************************************//**
 * @brief
 *   Get pulse counter top buffer value.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @return
 *   Current pulse counter top buffer value.
 ******************************************************************************/
static __INLINE uint32_t PCNT_TopBufferGet(PCNT_TypeDef *pcnt)
{
  return(pcnt->TOPB);
}

void PCNT_TopBufferSet(PCNT_TypeDef *pcnt, uint32_t val);

/***************************************************************************//**
 * @brief
 *   Get pulse counter top value.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @return
 *   Current pulse counter top value.
 ******************************************************************************/
static __INLINE uint32_t PCNT_TopGet(PCNT_TypeDef *pcnt)
{
  return(pcnt->TOP);
}

void PCNT_TopSet(PCNT_TypeDef *pcnt, uint32_t val);


/** @} (end addtogroup PCNT) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_PCNT_H */
