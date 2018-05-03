/***************************************************************************//**
 * @file
 * @brief Analog Comparator (ACMP) Peripheral API
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
#include <stdbool.h>
#include "em_acmp.h"
#include "em_bitband.h"
#include "em_assert.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup ACMP
 * @brief Analog comparator (ACMP) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */


/** Validation of ACMP register block pointer reference
 *  for assert statements. */
#if (ACMP_COUNT == 1)
#define ACMP_REF_VALID(ref)    ((ref) == ACMP0)
#elif (ACMP_COUNT == 2)
#define ACMP_REF_VALID(ref)    (((ref) == ACMP0) || ((ref) == ACMP1))
#else
#error Undefined number of analog comparators (ACMP).
#endif

/** @endcond */

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Sets up the ACMP for use in capacative sense applications.
 *
 * @details
 *   This function sets up the ACMP for use in capacacitve sense applications.
 *   To use the capacative sense functionality in the ACMP you need to use
 *   the PRS output of the ACMP module to count the number of oscillations
 *   in the capacative sense circuit (possibly using a TIMER).
 *
 * @note
 *   A basic example of capacative sensing can be found in the STK BSP
 *   (capsense demo).
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 *
 * @param[in] init
 *   Pointer to initialization structure used to configure ACMP for capacative
 *   sensing operation.
 ******************************************************************************/
void ACMP_CapsenseInit(ACMP_TypeDef *acmp, const ACMP_CapsenseInit_TypeDef *init)
{
  /* Make sure the module exists on the selected chip */
  EFM_ASSERT(ACMP_REF_VALID(acmp));

  /* Make sure that vddLevel is within bounds */
  EFM_ASSERT(init->vddLevel < 64);

  /* Make sure biasprog is within bounds */
  EFM_ASSERT(init->biasProg < 16);

  /* Set control register. No need to set interrupt modes */
  acmp->CTRL = (init->fullBias << _ACMP_CTRL_FULLBIAS_SHIFT)
               | (init->halfBias << _ACMP_CTRL_HALFBIAS_SHIFT)
               | (init->biasProg << _ACMP_CTRL_BIASPROG_SHIFT)
               | (init->warmTime << _ACMP_CTRL_WARMTIME_SHIFT)
               | (init->hysteresisLevel << _ACMP_CTRL_HYSTSEL_SHIFT);

  /* Select capacative sensing mode by selecting a resistor and enabling it */
  acmp->INPUTSEL = (init->resistor << _ACMP_INPUTSEL_CSRESSEL_SHIFT)
                   | ACMP_INPUTSEL_CSRESEN
                   | (init->lowPowerReferenceEnabled << _ACMP_INPUTSEL_LPREF_SHIFT)
                   | (init->vddLevel << _ACMP_INPUTSEL_VDDLEVEL_SHIFT)
                   | ACMP_INPUTSEL_NEGSEL_CAPSENSE;

  /* Enable ACMP if requested.
   * Note: BITBAND_Peripheral() function is used for setting/clearing single
   * bit peripheral register bitfields. */
  BITBAND_Peripheral(&(acmp->CTRL),
                     (uint32_t)_ACMP_CTRL_EN_SHIFT,
                     (uint32_t)init->enable);
}

/***************************************************************************//**
 * @brief
 *   Sets the ACMP channel used for capacative sensing.
 *
 * @note
 *   A basic example of capacative sensing can be found in the STK BSP
 *   (capsense demo).
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 *
 * @param[in] channel
 *   The ACMP channel to use for capacative sensing (Possel).
 ******************************************************************************/
void ACMP_CapsenseChannelSet(ACMP_TypeDef *acmp, ACMP_Channel_TypeDef channel)
{
  /* Make sure that only external channels are used */
  EFM_ASSERT(channel < _ACMP_INPUTSEL_NEGSEL_1V25);

  /* Set channel as positive channel in ACMP */
  SET_BIT_FIELD(acmp->INPUTSEL, _ACMP_INPUTSEL_POSSEL_MASK, channel,
                _ACMP_INPUTSEL_POSSEL_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Disables the ACMP.
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 ******************************************************************************/
void ACMP_Disable(ACMP_TypeDef *acmp)
{
  acmp->CTRL &= ~ACMP_CTRL_EN;
}

/***************************************************************************//**
 * @brief
 *   Enables the ACMP.
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 ******************************************************************************/
void ACMP_Enable(ACMP_TypeDef *acmp)
{
  acmp->CTRL |= ACMP_CTRL_EN;
}

/***************************************************************************//**
 * @brief
 *   Reset ACMP to same state as after a HW reset.
 *
 * @note
 *   The ROUTE register is NOT reset by this function, in order to allow for
 *   centralized setup of this feature.
 *
 * @param[in] acmp
 *   Pointer to the ACMP peripheral register block.
 ******************************************************************************/
void ACMP_Reset(ACMP_TypeDef *acmp)
{
  /* Make sure the module exists on the selected chip */
  EFM_ASSERT(ACMP_REF_VALID(acmp));

  acmp->CTRL     = _ACMP_CTRL_RESETVALUE;
  acmp->INPUTSEL = _ACMP_INPUTSEL_RESETVALUE;
  acmp->IEN      = _ACMP_IEN_RESETVALUE;
  acmp->IFC      = _ACMP_IF_MASK;
}

/***************************************************************************//**
 * @brief
 *   Sets up GPIO output from the ACMP.
 *
 * @note
 *    GPIO must be enabled in the CMU before this function call, i.e.
 * @verbatim CMU_ClockEnable(cmuClock_GPIO, true); @endverbatim
 *
 * @param[in] acmp
 *   Pointer to the ACMP peripheral register block.
 *
 * @param location
 *   The pin location to use. See the datasheet for location to pin mappings.
 *
 * @param enable
 *   Enable or disable pin output.
 *
 * @param invert
 *   Invert output.
 ******************************************************************************/
void ACMP_GPIOSetup(ACMP_TypeDef *acmp, uint32_t location, bool enable, bool invert)
{
  /* Sanity checking of location */
  EFM_ASSERT(location < 4);

  /* Set GPIO inversion */
  SET_BIT_FIELD(acmp->CTRL, _ACMP_CTRL_GPIOINV_MASK, invert,
                _ACMP_CTRL_GPIOINV_SHIFT);

  acmp->ROUTE = (location << _ACMP_ROUTE_LOCATION_SHIFT)
                | (enable << _ACMP_ROUTE_ACMPPEN_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Sets which channels should be used in ACMP comparisons.
 *
 * @param[in] acmp
 *   Pointer to the ACMP peripheral register block.
 *
 * @param negSel
 *   Channel to use on the negative input to the ACMP.
 *
 * @param posSel
 *   Channel to use on the positive input to the ACMP.
 ******************************************************************************/
void ACMP_ChannelSet(ACMP_TypeDef *acmp, ACMP_Channel_TypeDef negSel,
                     ACMP_Channel_TypeDef posSel)
{
  /* Make sure that only external channels are used as ACMP positive input */
  EFM_ASSERT(posSel < _ACMP_INPUTSEL_NEGSEL_1V25);
  /* Sanity checking of ACMP negative input */
  EFM_ASSERT(negSel <= _ACMP_INPUTSEL_NEGSEL_VDD);

  acmp->INPUTSEL = (acmp->INPUTSEL & ~(_ACMP_INPUTSEL_POSSEL_MASK |
                                       _ACMP_INPUTSEL_NEGSEL_MASK))
                   | (negSel << _ACMP_INPUTSEL_NEGSEL_SHIFT)
                   | (posSel << _ACMP_INPUTSEL_POSSEL_SHIFT);
}

/***************************************************************************//**
 * @brief
 *
 *
 * @param[in] acmp
 *   Pointer to the ACMP peripheral register block.
 *
 * @param[in] init
 *   Pointer to initialization structure used to configure ACMP for capacative
 *   sensing operation.
 ******************************************************************************/
void ACMP_Init(ACMP_TypeDef *acmp, const ACMP_Init_TypeDef *init)
{
  /* Make sure the module exists on the selected chip */
  EFM_ASSERT(ACMP_REF_VALID(acmp));

  /* Make sure biasprog is within bounds */
  EFM_ASSERT(init->biasProg < 16);

  /* Set control register. No need to set interrupt modes */
  acmp->CTRL = (init->fullBias << _ACMP_CTRL_FULLBIAS_SHIFT)
               | (init->halfBias << _ACMP_CTRL_HALFBIAS_SHIFT)
               | (init->biasProg << _ACMP_CTRL_BIASPROG_SHIFT)
               | (init->interruptOnFallingEdge << _ACMP_CTRL_IFALL_SHIFT)
               | (init->interruptOnRisingEdge << _ACMP_CTRL_IRISE_SHIFT)
               | (init->warmTime << _ACMP_CTRL_WARMTIME_SHIFT)
               | (init->hysteresisLevel << _ACMP_CTRL_HYSTSEL_SHIFT)
               | (init->inactiveValue << _ACMP_CTRL_INACTVAL_SHIFT);

  acmp->INPUTSEL = (init->lowPowerReferenceEnabled << _ACMP_INPUTSEL_LPREF_SHIFT)
                   | (init->vddLevel << _ACMP_INPUTSEL_VDDLEVEL_SHIFT);

  /* Enable ACMP if requested.
   * Note: BITBAND_Peripheral() function is used for setting/clearing single
   * bit peripheral register bitfields. */
  BITBAND_Peripheral(&(acmp->CTRL),
                     (uint32_t)_ACMP_CTRL_EN_SHIFT,
                     (uint32_t)init->enable);
}


/** @} (end addtogroup ACMP) */
/** @} (end addtogroup EM_Library) */
