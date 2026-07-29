/***************************************************************************//**
 * @file
 * @brief System Peripheral API
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
#include "em_part.h"
#include "em_system.h"
#include "em_assert.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SYSTEM
 * @brief System Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get chip major/minor revision.
 *
 * @param[out] rev
 *   Location to place chip revision info.
 ******************************************************************************/
void SYSTEM_ChipRevisionGet(SYSTEM_ChipRevision_TypeDef *rev)
{
  uint8_t tmp;

  EFM_ASSERT(rev);

  rev->major = (ROMTABLE->PID0 & _ROMTABLE_PID0_REVMAJOR_MASK) >> _ROMTABLE_PID0_REVMAJOR_SHIFT;

  tmp        = (ROMTABLE->PID2 & _ROMTABLE_PID2_REVMINORMSB_MASK);
  tmp       |= ((ROMTABLE->PID3 & _ROMTABLE_PID3_REVMINORLSB_MASK) >> _ROMTABLE_PID3_REVMINORLSB_SHIFT);
  rev->minor = tmp;
}

/***************************************************************************//**
 * @brief
 *    Get factory calibration value for a given peripheral register.
 *
 * @param[in] regAddress
 *    Address of register to get a calibration value for.
 *
 * @return
 *    Calibration value for the requested register.
 ******************************************************************************/
uint32_t SYSTEM_GetCalibrationValue(volatile uint32_t *regAddress)
{
  int               regCount;
  CALIBRATE_TypeDef *p;

  regCount = 1;
  p        = CALIBRATE;

  for (;; )
  {
    if ((regCount > CALIBRATE_MAX_REGISTERS) ||
        (p->VALUE == 0xFFFFFFFF))
    {
      EFM_ASSERT(false);
      return 0;                 /* End of device calibration table reached. */
    }

    if (p->ADDRESS == (uint32_t)regAddress)
    {
      return p->VALUE;          /* Calibration value found ! */
    }

    p++;
    regCount++;
  }
}

/** @} (end addtogroup SYSTEM) */
/** @} (end addtogroup EM_Library) */
