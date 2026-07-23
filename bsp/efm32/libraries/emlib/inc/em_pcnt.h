/***************************************************************************//**
 * @file
 * @brief Pulse Counter (PCNT) peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
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
#ifndef __EM_PCNT_H
#define __EM_PCNT_H

#include <stdbool.h>
#include "em_part.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup PCNT
 * @{
 ******************************************************************************/

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


#if (defined (_EFM32_TINY_FAMILY) || defined (_EFM32_GIANT_FAMILY))
/** Counter event selection.
 *  Note: unshifted values are being used for enumeration because multiple
 *  configuration structure members use this type definition. */
typedef enum
{
  /** Counts up on up-count and down on down-count events. */
  pcntCntEventBoth = _PCNT_CTRL_CNTEV_BOTH,

  /** Only counts up on up-count events. */
  pcntCntEventUp   = _PCNT_CTRL_CNTEV_UP,

  /** Only counts down on down-count events. */
  pcntCntEventDown = _PCNT_CTRL_CNTEV_DOWN,

  /** Never counts. */
  pcntCntEventNone = _PCNT_CTRL_CNTEV_NONE
} PCNT_CntEvent_TypeDef;


/** PRS sources for @p s0PRS and @p s1PRS. */
typedef enum
{
  pcntPRSCh0 = 0,     /**< PRS channel 0. */
  pcntPRSCh1 = 1,     /**< PRS channel 1. */
  pcntPRSCh2 = 2,     /**< PRS channel 2. */
  pcntPRSCh3 = 3,     /**< PRS channel 3. */
  pcntPRSCh4 = 4,     /**< PRS channel 4. */
  pcntPRSCh5 = 5,     /**< PRS channel 5. */
  pcntPRSCh6 = 6,     /**< PRS channel 6. */
  pcntPRSCh7 = 7      /**< PRS channel 7. */
} PCNT_PRSSel_TypeDef;


/** PRS inputs of PCNT. */
typedef enum
{
  pcntPRSInputS0 = 0, /** PRS input 0. */
  pcntPRSInputS1 = 1  /** PRS input 1. */
} PCNT_PRSInput_TypeDef;
#endif


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** Init structure. */
typedef struct
{
  /** Mode to operate in. */
  PCNT_Mode_TypeDef     mode;

  /** Initial counter value (refer to reference manual for max value allowed).
   * Only used for #pcntModeOvsSingle (and possibly #pcntModeDisable) modes.
   * If using #pcntModeExtSingle or #pcntModeExtQuad modes, the counter
   * value is reset to HW reset value. */
  uint32_t              counter;

  /** Initial top value (refer to reference manual for max value allowed).
   * Only used for #pcntModeOvsSingle (and possibly #pcntModeDisable) modes.
   * If using #pcntModeExtSingle or #pcntModeExtQuad modes, the top
   * value is reset to HW reset value. */
  uint32_t              top;

  /** Polarity of incoming edge.
   * @li #pcntModeExtSingle mode - if false, positive edges are counted,
   *   otherwise negative edges.
   * @li #pcntModeExtQuad mode - if true, counting direction is inverted. */
  bool                  negEdge;

  /** Counting direction, only applicable for #pcntModeOvsSingle and
   * #pcntModeExtSingle modes. */
  bool                  countDown;

  /** Enable filter, only available in #pcntModeOvsSingle mode. */
  bool                  filter;

#if (defined (_EFM32_TINY_FAMILY) || defined (_EFM32_GIANT_FAMILY))
  /** Set to true to enable hysteresis. When its enabled, the PCNT will always
   *  overflow and underflow to TOP/2. */
  bool                  hyst;

  /** Set to true to enable S1 to determine the direction of counting in
   *  OVSSINGLE or EXTCLKSINGLE modes.
   *  When S1 is high, the count direction is given by CNTDIR, and when S1 is
   *  low, the count direction is the opposite. */
  bool                  s1CntDir;

  /** Selects whether the regular counter responds to up-count events,
   *  down-count events, both or none. */
  PCNT_CntEvent_TypeDef cntEvent;

  /** Selects whether the auxiliary counter responds to up-count events,
   *  down-count events, both or none. */
  PCNT_CntEvent_TypeDef auxCntEvent;

  /** Select PRS channel as input to S0IN in PCNTx_INPUT register. */
  PCNT_PRSSel_TypeDef   s0PRS;

  /** Select PRS channel as input to S1IN in PCNTx_INPUT register. */
  PCNT_PRSSel_TypeDef   s1PRS;
#endif
} PCNT_Init_TypeDef;

/** Default config for PCNT init structure. */
#if defined (_EFM32_GECKO_FAMILY)
#define PCNT_INIT_DEFAULT                                                           \
  { pcntModeDisable,                          /* Disabled by default. */            \
    _PCNT_CNT_RESETVALUE,                     /* Default counter HW reset value. */ \
    _PCNT_TOP_RESETVALUE,                     /* Default counter HW reset value. */ \
    false,                                    /* Use positive edge. */              \
    false,                                    /* Up-counting. */                    \
    false                                     /* Filter disabled. */                \
  }
#elif (defined (_EFM32_TINY_FAMILY) || defined (_EFM32_GIANT_FAMILY))
#define PCNT_INIT_DEFAULT                                                                        \
  { pcntModeDisable,                          /* Disabled by default. */                         \
    _PCNT_CNT_RESETVALUE,                     /* Default counter HW reset value. */              \
    _PCNT_TOP_RESETVALUE,                     /* Default counter HW reset value. */              \
    false,                                    /* Use positive edge. */                           \
    false,                                    /* Up-counting. */                                 \
    false,                                    /* Filter disabled. */                             \
    false,                                    /* Hysteresis disabled. */                         \
    true,                                     /* Counter direction is given by CNTDIR. */        \
    pcntCntEventUp,                           /* Regular counter counts up on upcount events. */ \
    pcntCntEventNone,                         /* Auxiliary counter doesn't respond to events. */ \
    pcntPRSCh0,                               /* PRS channel 0 selected as S0IN. */              \
    pcntPRSCh0                                /* PRS channel 0 selected as S1IN. */              \
  }
#endif


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
__STATIC_INLINE uint32_t PCNT_CounterGet(PCNT_TypeDef *pcnt)
{
  return pcnt->CNT;
}


#if (defined (_EFM32_TINY_FAMILY) || defined (_EFM32_GIANT_FAMILY))
/***************************************************************************//**
 * @brief
 *   Get auxiliary counter value.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @return
 *   Current auxiliary counter value.
 ******************************************************************************/
__STATIC_INLINE uint32_t PCNT_AuxCounterGet(PCNT_TypeDef *pcnt)
{
  return pcnt->AUXCNT;
}
#endif


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
__STATIC_INLINE void PCNT_CounterSet(PCNT_TypeDef *pcnt, uint32_t count)
{
  PCNT_CounterTopSet(pcnt, count, pcnt->TOP);
}


void PCNT_Enable(PCNT_TypeDef *pcnt, PCNT_Mode_TypeDef mode);
void PCNT_FreezeEnable(PCNT_TypeDef *pcnt, bool enable);
void PCNT_Init(PCNT_TypeDef *pcnt, const PCNT_Init_TypeDef *init);

#if (defined (_EFM32_TINY_FAMILY) || defined (_EFM32_GIANT_FAMILY))
void PCNT_PRSInputEnable(PCNT_TypeDef *pcnt,
                         PCNT_PRSInput_TypeDef prsInput,
                         bool enable);
#endif


/***************************************************************************//**
 * @brief
 *   Clear one or more pending PCNT interrupts.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @param[in] flags
 *   Pending PCNT interrupt source to clear. Use a bitwise logic OR combination
 *   of valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void PCNT_IntClear(PCNT_TypeDef *pcnt, uint32_t flags)
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
 *   PCNT interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void PCNT_IntDisable(PCNT_TypeDef *pcnt, uint32_t flags)
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
 *   PCNT interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void PCNT_IntEnable(PCNT_TypeDef *pcnt, uint32_t flags)
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
 *   PCNT interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t PCNT_IntGet(PCNT_TypeDef *pcnt)
{
  return pcnt->IF;
}


/***************************************************************************//**
 * @brief
 *   Get enabled and pending PCNT interrupt flags.
 *
 * @details
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @return
 *   Pending and enabled PCNT interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in PCNT_IEN_nnn
 *   register (PCNT_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the PCNT module
 *   (PCNT_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t PCNT_IntGetEnabled(PCNT_TypeDef *pcnt)
{
  uint32_t tmp = 0U;


  /* Store pcnt->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  tmp = pcnt->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return pcnt->IF & tmp;
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending PCNT interrupts from SW.
 *
 * @param[in] pcnt
 *   Pointer to PCNT peripheral register block.
 *
 * @param[in] flags
 *   PCNT interrupt sources to set to pending. Use a bitwise logic OR combination
 *   of valid interrupt flags for the PCNT module (PCNT_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void PCNT_IntSet(PCNT_TypeDef *pcnt, uint32_t flags)
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
__STATIC_INLINE uint32_t PCNT_TopBufferGet(PCNT_TypeDef *pcnt)
{
  return pcnt->TOPB;
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
__STATIC_INLINE uint32_t PCNT_TopGet(PCNT_TypeDef *pcnt)
{
  return pcnt->TOP;
}

void PCNT_TopSet(PCNT_TypeDef *pcnt, uint32_t val);


/** @} (end addtogroup PCNT) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_PCNT_H */
