/***************************************************************************//**
 * @file
 * @brief Reset Management Unit (RMU) peripheral module peripheral API
 *   for EFM32.
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

#include "efm32_rmu.h"
#include "efm32_emu.h"
#include "efm32_bitband.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup RMU
 * @brief Reset Management Unit (RMU) Peripheral API for EFM32
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Disable/enable the lockup signal from the Cortex M-3.
 *
 * @param[in] disable
 *   @li false - Allow lockup signal to reset.
 *   @li true - Do not allow lockup signal to reset.
 ******************************************************************************/
void RMU_LockupResetDisable(bool disable)
{
  BITBAND_Peripheral(&(RMU->CTRL), _RMU_CTRL_LOCKUPRDIS_SHIFT, (unsigned int)disable);
}


/***************************************************************************//**
 * @brief
 *   Clear the reset cause register.
 ******************************************************************************/
void RMU_ResetCauseClear(void)
{
  uint32_t locked;

  RMU->CMD = RMU_CMD_RCCLR;

  /* Clear some reset causes not cleared with RMU CMD register */
  /* (If EMU registers locked, they must be unlocked first) */
  locked = EMU->LOCK & EMU_LOCK_LOCKKEY_LOCKED;
  if (locked)
  {
    EMU_Unlock();
  }

  BITBAND_Peripheral(&(EMU->AUXCTRL), 0, 1);
  BITBAND_Peripheral(&(EMU->AUXCTRL), 0, 0);

  if (locked)
  {
    EMU_Lock();
  }
}


/***************************************************************************//**
 * @brief
 *   Get the cause of the last reset.
 *
 * @details
 *   In order to be useful, the reset cause must be cleared by SW before a new
 *   reset occurs, otherwise reset causes may accumulate. See
 *   RMU_ResetCauseClear().
 *
 * @return
 *   The reset cause, a bit mask of (typically, but not always, only one) of:
 *   @li RMU_RSTCAUSE_PORST - Power on reset
 *   @li RMU_RSTCAUSE_BODUNREGRST - Brown out detector, unregulated power
 *   @li RMU_RSTCAUSE_BODREGRST - Brown out detector, regulated power
 *   @li RMU_RSTCAUSE_EXTRST - External reset
 *   @li RMU_RSTCAUSE_WDOGRST - Watchdog reset
 *   @li RMU_RSTCAUSE_LOCKUPRST - Cortex-M3 lockup reset
 *   @li RMU_RSTCAUSE_SYSREQRST - Cortex-M3 system request reset
 ******************************************************************************/
uint32_t RMU_ResetCauseGet(void)
{
  uint32_t ret = RMU->RSTCAUSE;

  /* Inspect and decode bits. The decoding must be done in correct order, */
  /* since some reset causes may trigger other reset causes due to internal */
  /* design. We are only interested in the main cause. */
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
  /* Clear "stray" bits if EM4 bit is set, they will always be active */
  if (ret & RMU_RSTCAUSE_EM4RST)
  {
    ret &= ~(RMU_RSTCAUSE_BODREGRST|
             RMU_RSTCAUSE_BODUNREGRST|
             RMU_RSTCAUSE_LOCKUPRST|
             RMU_RSTCAUSE_SYSREQRST);
  }
  if (ret == RMU_RSTCAUSE_BODAVDD0)
  {
    ret = RMU_RSTCAUSE_BODAVDD0;
  }
  else if (ret == RMU_RSTCAUSE_BODAVDD1)
  {
    ret = RMU_RSTCAUSE_BODAVDD1;
  }
  else if (ret == (RMU_RSTCAUSE_EM4WURST|RMU_RSTCAUSE_EM4RST))
  {
    ret &= (RMU_RSTCAUSE_EM4WURST|RMU_RSTCAUSE_EM4RST);
  }
  else if (ret & (RMU_RSTCAUSE_EM4RST|RMU_RSTCAUSE_EXTRST))
  {
    ret &= (RMU_RSTCAUSE_EM4RST|RMU_RSTCAUSE_EXTRST);
  }
  else
#endif
  if (ret & RMU_RSTCAUSE_PORST)
  {
    ret = RMU_RSTCAUSE_PORST;
  }
  else if (ret & RMU_RSTCAUSE_BODUNREGRST)
  {
    ret = RMU_RSTCAUSE_BODUNREGRST;
  }
  else if ((ret & 0x1f) == RMU_RSTCAUSE_BODREGRST)
  {
    ret = RMU_RSTCAUSE_BODREGRST;
  }
  /* Both external and watchdog reset may occur at the same time */
  else if (ret & (RMU_RSTCAUSE_EXTRST | RMU_RSTCAUSE_WDOGRST))
  {
    ret &= RMU_RSTCAUSE_EXTRST | RMU_RSTCAUSE_WDOGRST;
  }
  /* Both lockup and system reset may occur at the same time */
  else if (ret & (RMU_RSTCAUSE_LOCKUPRST | RMU_RSTCAUSE_SYSREQRST))
  {
    ret &= RMU_RSTCAUSE_LOCKUPRST | RMU_RSTCAUSE_SYSREQRST;
  }
  else 
  {
    ret = 0;
  }
  return ret;
}


/** @} (end addtogroup RMU) */
/** @} (end addtogroup EFM32_Library) */
