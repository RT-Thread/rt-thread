/***************************************************************************//**
 * @file
 * @brief Memory Protection Unit (MPU) Peripheral API for EFM32.
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
#include "efm32_mpu.h"
#include "efm32_assert.h"


/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/


/***************************************************************************//**
 * @addtogroup MPU
 * @brief Memory Protection Unit (MPU) Peripheral API for EFM32
 * @details
 *  This module contains functions to enable, disable and setup the MPU.
 *  The MPU is used to control access attributes and permissions in the
 *  memory map. The settings that can be controlled are:
 *
 *  @li Executable attribute.
 *  @li Cachable, bufferable and shareable attributes.
 *  @li Cache policy.
 *  @li Access permissions: Priviliged or User state, read or write access,
 *      and combinations of all these.
 *
 *  The MPU can be activated and deactivated with functions:
 *  @verbatim
 *  MPU_Enable(..);
 *  MPU_Disable();@endverbatim
 *  The MPU can control 8 memory regions with individual access control
 *  settings. Section attributes and permissions are set with:
 *  @verbatim
 *  MPU_ConfigureRegion(..);@endverbatim
 *  It is advisable to disable the MPU when altering region settings.
 *
 *
 * @{
 ******************************************************************************/


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/


/***************************************************************************//**
 * @brief
 *   Configure an MPU region.
 *
 * @details
 *   Writes to MPU RBAR and RASR registers.
 *   Refer to Cortex-M3 Reference Manual, MPU chapter for further details.
 *   To disable a region it is only required to set init->regionNo to the
 *   desired value and init->regionEnable = false.
 *
 * @param[in] init
 *   Pointer to a structure containing MPU region init information.
 ******************************************************************************/
void MPU_ConfigureRegion(const MPU_RegionInit_TypeDef *init)
{
  EFM_ASSERT(init->regionNo < ((MPU->TYPE & MPU_TYPE_DREGION_Msk) >>
                                MPU_TYPE_DREGION_Pos));

  MPU->RNR = init->regionNo;

  if (init->regionEnable)
  {
    EFM_ASSERT(!(init->baseAddress & ~MPU_RBAR_ADDR_Msk));
    EFM_ASSERT(init->tex <= 0x7);

    MPU->RBAR = init->baseAddress;
    MPU->RASR = ((init->disableExec ? 1 : 0) << MPU_RASR_XN_Pos)   |
                (init->accessPermission      << MPU_RASR_AP_Pos)   |
                (init->tex                   << MPU_RASR_TEX_Pos)  |
                ((init->shareable   ? 1 : 0) << MPU_RASR_S_Pos)    |
                ((init->cacheable   ? 1 : 0) << MPU_RASR_C_Pos)    |
                ((init->bufferable  ? 1 : 0) << MPU_RASR_B_Pos)    |
                (init->srd                   << MPU_RASR_SRD_Pos)  |
                (init->size                  << MPU_RASR_SIZE_Pos) |
                (1                           << MPU_RASR_ENA_Pos);
  }
  else
  {
    MPU->RBAR = 0;
    MPU->RASR = 0;
  }
}


/** @} (end addtogroup CMU) */
/** @} (end addtogroup EFM32_Library) */
