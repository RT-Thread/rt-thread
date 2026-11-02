/***************************************************************************//**
 * @file
 * @brief Reset Management Unit (RMU) peripheral module peripheral API
 *
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
#include "em_rmu.h"
#include "em_emu.h"
#include "em_bitband.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup RMU
 * @brief Reset Management Unit (RMU) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Disable/enable reset for various peripherals and signal sources
 *
 * @param[in] enable
 *   @li false - Disable reset signal or flag
 *   @li true - Enable reset signal or flag
 ******************************************************************************/
void RMU_ResetControl(RMU_Reset_TypeDef reset, bool enable)
{
  BITBAND_Peripheral(&(RMU->CTRL), (uint32_t)reset, (uint32_t)enable);
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
 *   RMU_ResetCauseClear(). This function call will return the main cause for
 *   reset, which can be a bit mask (several causes), and clear away "noise".
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
 *   @li RMU_RSTCAUSE_EM4RST - Set if the system has been in EM4
 *   @li RMU_RSTCAUSE_EM4WURST - Set if the system woke up on a pin from EM4
 *   @li RMU_RSTCAUSE_BODAVDD0 - Analog power domain 0 brown out detector reset
 *   @li RMU_RSTCAUSE_BODAVDD1 - Analog power domain 1 brown out detector reset
 *   @li RMU_RSTCAUSE_BUBODVDDDREG - Backup BOD on VDDD_REG triggered
 *   @li RMU_RSTCAUSE_BUBODBUVIN - Backup BOD on BU_VIN triggered
 *   @li RMU_RSTCAUSE_BUBODUNREG - Backup BOD on unregulated power triggered
 *   @li RMU_RSTCAUSE_BUBODREG - Backup BOD on regulated powered has triggered
 *   @li RMU_RSTCAUSE_BUMODERST - System has been in Backup mode
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
#endif
  if (ret & RMU_RSTCAUSE_PORST)
  {
    ret = RMU_RSTCAUSE_PORST;
  }
  else if ((ret & 0x83) == RMU_RSTCAUSE_BODUNREGRST)
  {
    ret = RMU_RSTCAUSE_BODUNREGRST;
  }
  else if ((ret & 0x1f) == RMU_RSTCAUSE_BODREGRST)
  {
    ret = RMU_RSTCAUSE_BODREGRST;
  }
  /* Both external and watchdog reset may occur at the same time */
  else if ((ret & 0x1b) & (RMU_RSTCAUSE_EXTRST | RMU_RSTCAUSE_WDOGRST))
  {
    ret &= RMU_RSTCAUSE_EXTRST | RMU_RSTCAUSE_WDOGRST;
  }
  /* Both lockup and system reset may occur at the same time */
  else if ((ret & 0x7ff) & (RMU_RSTCAUSE_LOCKUPRST | RMU_RSTCAUSE_SYSREQRST))
  {
    ret &= RMU_RSTCAUSE_LOCKUPRST | RMU_RSTCAUSE_SYSREQRST;
  }
  /* EM4 wake up and pin retention support */
#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
  else if (ret & RMU_RSTCAUSE_BODAVDD0)
  {
    ret = RMU_RSTCAUSE_BODAVDD0;
  }
  else if (ret & RMU_RSTCAUSE_BODAVDD1)
  {
    ret = RMU_RSTCAUSE_BODAVDD1;
  }
  else if (ret & (RMU_RSTCAUSE_EM4WURST|RMU_RSTCAUSE_EM4RST))
  {
    ret &= (RMU_RSTCAUSE_EM4WURST|
#if defined(_EFM32_GIANT_FAMILY)
            RMU_RSTCAUSE_BUMODERST|
#endif
            RMU_RSTCAUSE_EM4RST);
  }
  else if (ret & (RMU_RSTCAUSE_EM4RST|RMU_RSTCAUSE_EXTRST))
  {
    ret &= (RMU_RSTCAUSE_EM4RST|RMU_RSTCAUSE_EXTRST);
  }
#endif
  /* Backup power domain support */
#if defined(_EFM32_GIANT_FAMILY)
  else if (ret & (RMU_RSTCAUSE_BUBODVDDDREG))
  {
    /* Keep backup mode flag, will only be present in this scenario */
    ret &= (RMU_RSTCAUSE_BUBODVDDDREG|RMU_RSTCAUSE_BUMODERST);
  }
  else if (ret & (RMU_RSTCAUSE_BUBODBUVIN))
  {
    ret &= (RMU_RSTCAUSE_BUBODBUVIN);
  }
  else if (ret & (RMU_RSTCAUSE_BUBODUNREG))
  {
    ret &= (RMU_RSTCAUSE_BUBODUNREG);
  }
  else if (ret & (RMU_RSTCAUSE_BUBODREG))
  {
    ret &= (RMU_RSTCAUSE_BUBODREG);
  }
#endif
  else
  {
    ret = 0;
  }
  return ret;
}


/** @} (end addtogroup RMU) */
/** @} (end addtogroup EM_Library) */
