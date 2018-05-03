/***************************************************************************//**
 * @file
 * @brief Low Energy Timer (LETIMER) Peripheral API
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
#include "em_letimer.h"
#include "em_cmu.h"
#include "em_assert.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup LETIMER
 * @brief Low Energy Timer (LETIMER) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** Validation of valid comparator register for assert statements. */
#define LETIMER_COMP_REG_VALID(reg)    (((reg) <= 1))

/** Validation of LETIMER register block pointer reference for assert statements. */
#define LETIMER_REF_VALID(ref)         ((ref) == LETIMER0)

/** Validation of valid repeat counter register for assert statements. */
#define LETIMER_REP_REG_VALID(reg)     (((reg) <= 1))

/** @endcond */


/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

#if defined(_EFM32_GECKO_FAMILY)
/***************************************************************************//**
 * @brief
 *   Wait for ongoing sync of register(s) to low frequency domain to complete.
 *
 * @note
 *   This only applies to the Gecko Family, see the reference manual
 *   chapter about Access to Low Energy Peripherals (Asynchronos Registers)
 *   for details.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block
 *
 * @param[in] mask
 *   Bitmask corresponding to SYNCBUSY register defined bits, indicating
 *   registers that must complete any ongoing synchronization.
 ******************************************************************************/
__STATIC_INLINE void LETIMER_Sync(LETIMER_TypeDef *letimer, uint32_t mask)
{
  /* Avoid deadlock if modifying the same register twice when freeze mode is */
  /* activated. */
  if (letimer->FREEZE & LETIMER_FREEZE_REGFREEZE)
    return;

  /* Wait for any pending previous write operation to have been completed */
  /* in low frequency domain, only required for Gecko Family of devices  */
  while (letimer->SYNCBUSY & mask)
    ;
}
#endif

/** @endcond */

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get LETIMER compare register value.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block
 *
 * @param[in] comp
 *   Compare register to get, either 0 or 1
 *
 * @return
 *   Compare register value, 0 if invalid register selected.
 ******************************************************************************/
uint32_t LETIMER_CompareGet(LETIMER_TypeDef *letimer, unsigned int comp)
{
  uint32_t ret;

  EFM_ASSERT(LETIMER_REF_VALID(letimer) && LETIMER_COMP_REG_VALID(comp));

  /* Initialize selected compare value */
  switch (comp)
  {
  case 0:
    ret = letimer->COMP0;
    break;

  case 1:
    ret = letimer->COMP1;
    break;

  default:
    /* Unknown compare register selected */
    ret = 0;
    break;
  }

  return(ret);
}


/***************************************************************************//**
 * @brief
 *   Set LETIMER compare register value.
 *
 * @note
 *   The setting of a compare register requires synchronization into the
 *   low frequency domain. If the same register is modified before a previous
 *   update has completed, this function will stall until the previous
 *   synchronization has completed. This only applies to the Gecko Family, see
 *   comment in the LETIMER_Sync() internal function call.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block
 *
 * @param[in] comp
 *   Compare register to set, either 0 or 1
 *
 * @param[in] value
 *   Initialization value (<= 0x0000ffff)
 ******************************************************************************/
void LETIMER_CompareSet(LETIMER_TypeDef *letimer,
                        unsigned int comp,
                        uint32_t value)
{
  volatile uint32_t *compReg;
  uint32_t          syncbusy;

  EFM_ASSERT(LETIMER_REF_VALID(letimer) &&
             LETIMER_COMP_REG_VALID(comp) &&
             ((value & ~(_LETIMER_COMP0_COMP0_MASK >> _LETIMER_COMP0_COMP0_SHIFT)) == 0));

  /* Initialize selected compare value */
  switch (comp)
  {
  case 0:
    compReg  = &(letimer->COMP0);
    syncbusy = LETIMER_SYNCBUSY_COMP0;
    break;

  case 1:
    compReg  = &(letimer->COMP1);
    syncbusy = LETIMER_SYNCBUSY_COMP1;
    break;

  default:
    /* Unknown compare register selected, abort */
    return;
  }

#if defined(_EFM32_GECKO_FAMILY)
  /* LF register about to be modified require sync. busy check */
  LETIMER_Sync(letimer, syncbusy);
#endif

  *compReg = value;
}


/***************************************************************************//**
 * @brief
 *   Start/stop LETIMER.
 *
 * @note
 *   The enabling/disabling of the LETIMER modifies the LETIMER CMD register
 *   which requires synchronization into the low frequency domain. If this
 *   register is modified before a previous update to the same register has
 *   completed, this function will stall until the previous synchronization has
 *   completed. This only applies to the Gecko Family, see comment in the
 *   LETIMER_Sync() internal function call.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block.
 *
 * @param[in] enable
 *   true to enable counting, false to disable.
 ******************************************************************************/
void LETIMER_Enable(LETIMER_TypeDef *letimer, bool enable)
{
  EFM_ASSERT(LETIMER_REF_VALID(letimer));

#if defined(_EFM32_GECKO_FAMILY)
  /* LF register about to be modified require sync. busy check */
  LETIMER_Sync(letimer, LETIMER_SYNCBUSY_CMD);
#endif

  if (enable)
  {
    letimer->CMD = LETIMER_CMD_START;
  }
  else
  {
    letimer->CMD = LETIMER_CMD_STOP;
  }
}


/***************************************************************************//**
 * @brief
 *   LETIMER register synchronization freeze control.
 *
 * @details
 *   Some LETIMER registers require synchronization into the low frequency (LF)
 *   domain. The freeze feature allows for several such registers to be
 *   modified before passing them to the LF domain simultaneously (which
 *   takes place when the freeze mode is disabled).
 *
 * @note
 *   When enabling freeze mode, this function will wait for all current
 *   ongoing LETIMER synchronization to LF domain to complete (Normally
 *   synchronization will not be in progress.) However for this reason, when
 *   using freeze mode, modifications of registers requiring LF synchronization
 *   should be done within one freeze enable/disable block to avoid unecessary
 *   stalling.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block.
 *
 * @param[in] enable
 *   @li true - enable freeze, modified registers are not propagated to the
 *       LF domain
 *   @li false - disables freeze, modified registers are propagated to LF
 *       domain
 ******************************************************************************/
void LETIMER_FreezeEnable(LETIMER_TypeDef *letimer, bool enable)
{
  if (enable)
  {
    /*
     * Wait for any ongoing LF synchronization to complete. This is just to
     * protect against the rare case when a user
     * - modifies a register requiring LF sync
     * - then enables freeze before LF sync completed
     * - then modifies the same register again
     * since modifying a register while it is in sync progress should be
     * avoided.
     */
    while (letimer->SYNCBUSY)
      ;

    letimer->FREEZE = LETIMER_FREEZE_REGFREEZE;
  }
  else
  {
    letimer->FREEZE = 0;
  }
}


/***************************************************************************//**
 * @brief
 *   Initialize LETIMER.
 *
 * @details
 *   Note that the compare/repeat values must be set separately with
 *   LETIMER_CompareSet() and LETIMER_RepeatSet(). That should probably be done
 *   prior to the use of this function if configuring the LETIMER to start when
 *   initialization is completed.
 *
 * @note
 *   The initialization of the LETIMER modifies the LETIMER CTRL/CMD registers
 *   which require synchronization into the low frequency domain. If any of those
 *   registers are modified before a previous update to the same register has
 *   completed, this function will stall until the previous synchronization has
 *   completed. This only applies to the Gecko Family, see comment in the
 *   LETIMER_Sync() internal function call.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block.
 *
 * @param[in] init
 *   Pointer to LETIMER initialization structure.
 ******************************************************************************/
void LETIMER_Init(LETIMER_TypeDef *letimer, const LETIMER_Init_TypeDef *init)
{
  uint32_t tmp = 0;

  EFM_ASSERT(LETIMER_REF_VALID(letimer));

  /* Stop timer if specified to be disabled and running */
  if (!(init->enable) && (letimer->STATUS & LETIMER_STATUS_RUNNING))
  {
#if defined(_EFM32_GECKO_FAMILY)
    /* LF register about to be modified require sync. busy check */
    LETIMER_Sync(letimer, LETIMER_SYNCBUSY_CMD);
#endif
    letimer->CMD = LETIMER_CMD_STOP;
  }

  /* Configure DEBUGRUN flag, sets whether or not counter should be
   * updated when debugger is active */
  if (init->debugRun)
  {
    tmp |= LETIMER_CTRL_DEBUGRUN;
  }

  if (init->rtcComp0Enable)
  {
    tmp |= LETIMER_CTRL_RTCC0TEN;
  }

  if (init->rtcComp1Enable)
  {
    tmp |= LETIMER_CTRL_RTCC1TEN;
  }

  if (init->comp0Top)
  {
    tmp |= LETIMER_CTRL_COMP0TOP;
  }

  if (init->bufTop)
  {
    tmp |= LETIMER_CTRL_BUFTOP;
  }

  if (init->out0Pol)
  {
    tmp |= LETIMER_CTRL_OPOL0;
  }

  if (init->out1Pol)
  {
    tmp |= LETIMER_CTRL_OPOL1;
  }

  tmp |= init->ufoa0 << _LETIMER_CTRL_UFOA0_SHIFT;
  tmp |= init->ufoa1 << _LETIMER_CTRL_UFOA1_SHIFT;
  tmp |= init->repMode << _LETIMER_CTRL_REPMODE_SHIFT;

#if defined(_EFM32_GECKO_FAMILY)
  /* LF register about to be modified require sync. busy check */
  LETIMER_Sync(letimer, LETIMER_SYNCBUSY_CTRL);
#endif
  letimer->CTRL = tmp;

  /* Start timer if specified to be enabled and not already running */
  if (init->enable && !(letimer->STATUS & LETIMER_STATUS_RUNNING))
  {
#if defined(_EFM32_GECKO_FAMILY)
    /* LF register about to be modified require sync. busy check */
    LETIMER_Sync(letimer, LETIMER_SYNCBUSY_CMD);
#endif
    letimer->CMD = LETIMER_CMD_START;
  }
}


/***************************************************************************//**
 * @brief
 *   Get LETIMER repeat register value.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block
 *
 * @param[in] rep
 *   Repeat register to get, either 0 or 1
 *
 * @return
 *   Repeat register value, 0 if invalid register selected.
 ******************************************************************************/
uint32_t LETIMER_RepeatGet(LETIMER_TypeDef *letimer, unsigned int rep)
{
  uint32_t ret;

  EFM_ASSERT(LETIMER_REF_VALID(letimer) && LETIMER_REP_REG_VALID(rep));

  /* Initialize selected compare value */
  switch (rep)
  {
  case 0:
    ret = letimer->REP0;
    break;

  case 1:
    ret = letimer->REP1;
    break;

  default:
    /* Unknown compare register selected */
    ret = 0;
    break;
  }

  return(ret);
}


/***************************************************************************//**
 * @brief
 *   Set LETIMER repeat counter register value.
 *
 * @note
 *   The setting of a repeat counter register requires synchronization into the
 *   low frequency domain. If the same register is modified before a previous
 *   update has completed, this function will stall until the previous
 *   synchronization has completed. This only applies to the Gecko Family, see
 *   comment in the LETIMER_Sync() internal function call.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block
 *
 * @param[in] rep
 *   Repeat counter register to set, either 0 or 1
 *
 * @param[in] value
 *   Initialization value (<= 0x0000ffff)
 ******************************************************************************/
void LETIMER_RepeatSet(LETIMER_TypeDef *letimer,
                       unsigned int rep,
                       uint32_t value)
{
  volatile uint32_t *repReg;
#if defined(_EFM32_GECKO_FAMILY)
  uint32_t          syncbusy;
#endif
  EFM_ASSERT(LETIMER_REF_VALID(letimer) &&
             LETIMER_REP_REG_VALID(rep) &&
             ((value & ~(_LETIMER_REP0_REP0_MASK >> _LETIMER_REP0_REP0_SHIFT)) == 0));

  /* Initialize selected compare value */
  switch (rep)
  {
  case 0:
    repReg = &(letimer->REP0);
#if defined(_EFM32_GECKO_FAMILY)
    syncbusy = LETIMER_SYNCBUSY_REP0;
#endif
    break;

  case 1:
    repReg = &(letimer->REP1);
#if defined(_EFM32_GECKO_FAMILY)
    syncbusy = LETIMER_SYNCBUSY_REP1;
#endif
    break;

  default:
    /* Unknown compare register selected, abort */
    return;
  }

#if defined(_EFM32_GECKO_FAMILY)
  /* LF register about to be modified require sync. busy check */
  LETIMER_Sync(letimer, syncbusy);
#endif

  *repReg = value;
}


/***************************************************************************//**
 * @brief
 *   Reset LETIMER to same state as after a HW reset.
 *
 * @note
 *   The ROUTE register is NOT reset by this function, in order to allow for
 *   centralized setup of this feature.
 *
 * @param[in] letimer
 *   Pointer to LETIMER peripheral register block.
 ******************************************************************************/
void LETIMER_Reset(LETIMER_TypeDef *letimer)
{
  /* Freeze registers to avoid stalling for LF synchronization */
  LETIMER_FreezeEnable(letimer, true);

  /* Make sure disabled first, before resetting other registers */
  letimer->CMD = LETIMER_CMD_STOP | LETIMER_CMD_CLEAR |
                 LETIMER_CMD_CTO0 | LETIMER_CMD_CTO1;
  letimer->CTRL  = _LETIMER_CTRL_RESETVALUE;
  letimer->COMP0 = _LETIMER_COMP0_RESETVALUE;
  letimer->COMP1 = _LETIMER_COMP1_RESETVALUE;
  letimer->REP0  = _LETIMER_REP0_RESETVALUE;
  letimer->REP1  = _LETIMER_REP1_RESETVALUE;
  letimer->IEN   = _LETIMER_IEN_RESETVALUE;
  letimer->IFC   = _LETIMER_IFC_MASK;
  /* Do not reset route register, setting should be done independently */

  /* Unfreeze registers, pass new settings on to LETIMER */
  LETIMER_FreezeEnable(letimer, false);
}


/** @} (end addtogroup LETIMER) */
/** @} (end addtogroup EM_Library) */
