/***************************************************************************//**
 * @file
 * @brief Timer/counter (TIMER) Peripheral API
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
#include "em_timer.h"
#include "em_cmu.h"
#include "em_assert.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup TIMER
 * @brief Timer/Counter (TIMER) Peripheral API
 * @details
 *   The timer module consists of three main parts:
 *   @li General timer config and enable control.
 *   @li Compare/capture control.
 *   @li Dead time insertion control (may not be available for all timers).
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */


/** Validation of TIMER register block pointer reference for assert statements. */
#if (TIMER_COUNT == 1)
#define TIMER_REF_VALID(ref)    ((ref) == TIMER0)
#elif (TIMER_COUNT == 2)
#define TIMER_REF_VALID(ref)    (((ref) == TIMER0) || ((ref) == TIMER1))
#elif (TIMER_COUNT == 3)
#define TIMER_REF_VALID(ref)    (((ref) == TIMER0) || \
                                 ((ref) == TIMER1) || \
                                 ((ref) == TIMER2))
#elif (TIMER_COUNT == 4)
#define TIMER_REF_VALID(ref)    (((ref) == TIMER0) || \
                                 ((ref) == TIMER1) || \
                                 ((ref) == TIMER2) || \
                                 ((ref) == TIMER3))
#else
#error Undefined number of timers.
#endif

/** Validation of TIMER compare/capture channel number */
#define TIMER_CH_VALID(ch)    ((ch) < 3)

/** @endcond */


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Start/stop TIMER.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] enable
 *   true to enable counting, false to disable.
 ******************************************************************************/
void TIMER_Enable(TIMER_TypeDef *timer, bool enable)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));

  if (enable)
  {
    timer->CMD = TIMER_CMD_START;
  }
  else
  {
    timer->CMD = TIMER_CMD_STOP;
  }
}


/***************************************************************************//**
 * @brief
 *   Initialize TIMER.
 *
 * @details
 *   Notice that counter top must be configured separately with for instance
 *   TIMER_TopSet(). In addition, compare/capture and dead-time insertion
 *   init must be initialized separately if used. That should probably
 *   be done prior to the use of this function if configuring the TIMER to
 *   start when initialization is completed.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] init
 *   Pointer to TIMER initialization structure.
 ******************************************************************************/
void TIMER_Init(TIMER_TypeDef *timer, const TIMER_Init_TypeDef *init)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));

  /* Stop timer if specified to be disabled (dosn't hurt if already stopped) */
  if (!(init->enable))
  {
    timer->CMD = TIMER_CMD_STOP;
  }

  /* Reset counter */
  timer->CNT = _TIMER_CNT_RESETVALUE;

  timer->CTRL =
    ((uint32_t)(init->prescale) << _TIMER_CTRL_PRESC_SHIFT) |
    ((uint32_t)(init->clkSel) << _TIMER_CTRL_CLKSEL_SHIFT) |
    ((uint32_t)(init->fallAction) << _TIMER_CTRL_FALLA_SHIFT) |
    ((uint32_t)(init->riseAction) << _TIMER_CTRL_RISEA_SHIFT) |
    ((uint32_t)(init->mode) << _TIMER_CTRL_MODE_SHIFT) |
    (init->debugRun               ?   TIMER_CTRL_DEBUGRUN  : 0) |
    (init->dmaClrAct              ?   TIMER_CTRL_DMACLRACT : 0) |
    (init->quadModeX4             ?   TIMER_CTRL_QDM_X4    : 0) |
    (init->oneShot                ?   TIMER_CTRL_OSMEN     : 0) |

#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
    (init->count2x                ?   TIMER_CTRL_X2CNT     : 0) |
    (init->ati                    ?   TIMER_CTRL_ATI       : 0) |
#endif
    (init->sync                   ?   TIMER_CTRL_SYNC      : 0);

  /* Start timer if specified to be enabled (dosn't hurt if already started) */
  if (init->enable)
  {
    timer->CMD = TIMER_CMD_START;
  }
}


/***************************************************************************//**
 * @brief
 *   Initialize TIMER compare/capture channel.
 *
 * @details
 *   Notice that if operating channel in compare mode, the CCV and CCVB register
 *   must be set separately as required.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] ch
 *   Compare/capture channel to init for.
 *
 * @param[in] init
 *   Pointer to TIMER initialization structure.
 ******************************************************************************/
void TIMER_InitCC(TIMER_TypeDef *timer,
                  unsigned int ch,
                  const TIMER_InitCC_TypeDef *init)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));
  EFM_ASSERT(TIMER_CH_VALID(ch));

  timer->CC[ch].CTRL =
    ((uint32_t)(init->eventCtrl) << _TIMER_CC_CTRL_ICEVCTRL_SHIFT) |
    ((uint32_t)(init->edge) << _TIMER_CC_CTRL_ICEDGE_SHIFT) |
    ((uint32_t)(init->prsSel) << _TIMER_CC_CTRL_PRSSEL_SHIFT) |
    ((uint32_t)(init->cufoa) << _TIMER_CC_CTRL_CUFOA_SHIFT) |
    ((uint32_t)(init->cofoa) << _TIMER_CC_CTRL_COFOA_SHIFT) |
    ((uint32_t)(init->cmoa) << _TIMER_CC_CTRL_CMOA_SHIFT) |
    ((uint32_t)(init->mode) << _TIMER_CC_CTRL_MODE_SHIFT) |
    (init->filter                ?   TIMER_CC_CTRL_FILT_ENABLE : 0) |
    (init->prsInput              ?   TIMER_CC_CTRL_INSEL_PRS   : 0) |
    (init->coist                 ?   TIMER_CC_CTRL_COIST       : 0) |
    (init->outInvert             ?   TIMER_CC_CTRL_OUTINV      : 0);
}

#ifdef TIMER_DTLOCK_LOCKKEY_LOCK
/***************************************************************************//**
 * @brief
 *   Lock the TIMER in order to protect some of its registers against unintended
 *   modification.
 *
 * @details
 *   Please refer to the reference manual for TIMER registers that will be
 *   locked.
 *
 * @note
 *   If locking the TIMER registers, they must be unlocked prior to using any
 *   TIMER API functions modifying TIMER registers protected by the lock.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 ******************************************************************************/
void TIMER_Lock(TIMER_TypeDef *timer)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));

  timer->DTLOCK = TIMER_DTLOCK_LOCKKEY_LOCK;
}
#endif

/***************************************************************************//**
 * @brief
 *   Reset TIMER to same state as after a HW reset.
 *
 * @note
 *   The ROUTE register is NOT reset by this function, in order to allow for
 *   centralized setup of this feature.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 ******************************************************************************/
void TIMER_Reset(TIMER_TypeDef *timer)
{
  int i;

  EFM_ASSERT(TIMER_REF_VALID(timer));

  /* Make sure disabled first, before resetting other registers */
  timer->CMD = TIMER_CMD_STOP;

  timer->CTRL = _TIMER_CTRL_RESETVALUE;
  timer->IEN  = _TIMER_IEN_RESETVALUE;
  timer->IFC  = _TIMER_IFC_MASK;
  timer->TOP  = _TIMER_TOP_RESETVALUE;
  timer->TOPB = _TIMER_TOPB_RESETVALUE;
  timer->CNT  = _TIMER_CNT_RESETVALUE;
  /* Do not reset route register, setting should be done independently */
  /* (Note: ROUTE register may be locked by DTLOCK register.) */

  for (i = 0; TIMER_CH_VALID(i); i++)
  {
    timer->CC[i].CTRL = _TIMER_CC_CTRL_RESETVALUE;
    timer->CC[i].CCV  = _TIMER_CC_CCV_RESETVALUE;
    timer->CC[i].CCVB = _TIMER_CC_CCVB_RESETVALUE;
  }

  /* Reset dead time insertion module, no effect on timers without DTI */

#ifdef TIMER_DTLOCK_LOCKKEY_UNLOCK
  /* Unlock DTI registers first in case locked */
  timer->DTLOCK = TIMER_DTLOCK_LOCKKEY_UNLOCK;

  timer->DTCTRL   = _TIMER_DTCTRL_RESETVALUE;
  timer->DTTIME   = _TIMER_DTTIME_RESETVALUE;
  timer->DTFC     = _TIMER_DTFC_RESETVALUE;
  timer->DTOGEN   = _TIMER_DTOGEN_RESETVALUE;
  timer->DTFAULTC = _TIMER_DTFAULTC_MASK;
#endif
}


#ifdef TIMER_DTLOCK_LOCKKEY_UNLOCK
/***************************************************************************//**
 * @brief
 *   Unlock the TIMER so that writing to locked registers again is possible.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 ******************************************************************************/
void TIMER_Unlock(TIMER_TypeDef *timer)
{
  EFM_ASSERT(TIMER_REF_VALID(timer));

  timer->DTLOCK = TIMER_DTLOCK_LOCKKEY_UNLOCK;
}
#endif


/** @} (end addtogroup TIMER) */
/** @} (end addtogroup EM_Library) */
