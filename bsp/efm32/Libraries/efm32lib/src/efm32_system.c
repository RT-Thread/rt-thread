/***************************************************************************//**
 * @file
 * @brief System Peripheral API for EFM32
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

#include "efm32.h"
#include "efm32_system.h"
#include "efm32_assert.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SYSTEM
 * @brief System Peripheral API for EFM32
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
/** @} (end addtogroup EFM32_Library) */
